// fp_trap_log.cpp
// BZR Open Shim - opt-in floating-point trap logger (diagnostic only)
//
// Why: Redux masks every floating-point exception (FUN_00618C10 only sets
// _DN_FLUSH), so a NaN or infinity is produced silently and only seen later
// as a corrupt transform or a vanished object. This finds the instructions
// that produce them.
//
// How ([Diagnostics] FpTrapLog = 1, or OPENSHIM_FP_TRAP_LOG / BZR_FP_TRAP_LOG):
//   - Startup: a self-test on the patch thread raises one x87 and one SSE
//     divide-by-zero through the real handler and checks both continue with
//     +inf. Any mismatch (an OS that does not hand over the FPU state this
//     relies on) leaves the logger off. Then a first-in-line vectored
//     handler is installed and the module pinned so the handler outlives it.
//   - Frame tick (Ogre frameStarted, scene_mutation_drain.cpp): the first
//     call names the main thread. Each call logs any new sites the previous
//     frame recorded, then unmasks (fp_trap_log_policy.h: SSE IM+ZM, x87 ZM).
//   - Handler: every float exception code on the main thread (even after the
//     unmask ended: code that restores a saved control word can leave it
//     unmasked). It recovers (fp_trap_recovery.h: SSE re-runs masked; x87
//     re-runs the faulting instruction in a stub; a CRT RaiseException, as
//     from log(0), is masked and continued), records the site with no allocation,
//     no lock and no logging, and leaves the thread masked until the next
//     frame tick. At most one trap per frame.
//   - Game exit (Ogre Root destructor seam) or plugin shutdown: masks the
//     main thread, stops unmasking and logs the summary table once.
//
// Cost when on: a few instructions per frame plus one exception round trip
// on a frame that traps. Off installs nothing (one branch in the frame tick).
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "fp_trap_log.h"

#include "diagnostic_switch.h"
#include "fp_trap_log_policy.h"
#include "fp_trap_recovery.h"
#include "shim_log.h"

#include <Windows.h>

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
    namespace
    {
        using FpTrap::Kind;
        using FpTrap::RecoverResult;
        using FpTrap::TrapReport;
        using FpTrap::TrapSite;

        constexpr const char* kComponent = "fptrap";
        constexpr size_t kTableSize = 256;
        constexpr int kNewSiteLogBudget = 64;

        std::atomic<bool> g_Enabled{false};
        std::atomic<bool> g_Stopped{false};
        std::atomic<bool> g_SummaryWritten{false};
        PVOID g_Handler = nullptr;

        // Written by the frame tick and the handler, both on the target thread
        // (the main thread, or the patch thread during the self-test).
        volatile DWORD g_TargetThread = 0;
        volatile LONG g_UnmaskLive = 0;
        bool g_SelfTest = false;
        int g_SelfTestHits = 0;
        TrapReport g_SelfTestReport;

        FpTrap::RecoveryScratch g_Scratch;
        FpTrap::TrapTable<kTableSize> g_Table;
        uint32_t g_Frame = 0;
        uint32_t g_InPlace = 0;
        uint32_t g_Unrecovered = 0;
        uint32_t g_Raised = 0;
        bool g_UnrecoveredWarned = false;
        int g_LogBudget = kNewSiteLogBudget;
        bool g_BudgetNoted = false;

        FpTrap::SystemModules g_SystemModules; // captured before the handler is installed

        // Gate: float codes on the target thread only (FpTrap::ShouldConsider);
        // g_TargetThread is zero unless the logger is on or self-testing.
        LONG CALLBACK FpTrapHandler(EXCEPTION_POINTERS* pointers)
        {
            const uint32_t code = pointers->ExceptionRecord->ExceptionCode;
            if (!FpTrap::ShouldConsider(code, GetCurrentThreadId(), g_TargetThread))
                return EXCEPTION_CONTINUE_SEARCH;
            CONTEXT* const c = pointers->ContextRecord;
            TrapReport report;
            // First: clears the still-pending live x87 exception before any
            // x87 instruction or __try below (fp_trap_recovery.h).
            const RecoverResult result = FpTrap::Recover(code, c, g_Scratch, report);
            if (result == RecoverResult::NoContextState)
            {
                if (g_SelfTest)
                    g_SelfTestReport = report;
                return EXCEPTION_CONTINUE_SEARCH;
            }
            g_UnmaskLive = 0;

            if (g_SelfTest)
            {
                ++g_SelfTestHits;
                g_SelfTestReport = report;
                return EXCEPTION_CONTINUE_EXECUTION;
            }
            if (result == RecoverResult::RecoveredInPlace)
                ++g_InPlace;
            else if (result == RecoverResult::RaisedMasked)
                ++g_Raised;
            else if (result == RecoverResult::Unrecovered)
            {
                // The faulting x87 instruction was skipped, so game state now
                // differs from stock: stop unmasking for the session.
                ++g_Unrecovered;
                g_Stopped.store(true, std::memory_order_release);
            }

            uint32_t stack[FpTrap::kStackDepth] = {};
            const uint8_t depth = FpTrap::WalkCurrentStack(c, stack);
            // A software raise reports EIP inside RaiseException; the site is
            // the first caller outside the CRT and system DLLs.
            const uint32_t address =
                report.kind == Kind::Raised && depth > 0
                    ? FpTrap::FirstCallerOutside(stack, depth,
                                                 [](uint32_t a) { return g_SystemModules.Contains(a); })
                    : report.address;
            bool isNew = false;
            TrapSite* site = g_Table.Record(address, report.kind, isNew);
            if (site && isNew)
            {
                site->firstEip = report.eip;
                site->firstFrame = g_Frame;
                site->flags = report.flags;
                site->adjacent = report.adjacent;
                std::memcpy(site->stack, stack, sizeof(stack));
                site->stackDepth = depth;
            }
            return EXCEPTION_CONTINUE_EXECUTION;
        }

        void DescribeAddress(uint32_t address, char* out, size_t size)
        {
            HMODULE module = nullptr;
            char path[MAX_PATH] = {};
            if (address != 0 &&
                GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                       GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                   reinterpret_cast<LPCSTR>(static_cast<uintptr_t>(address)), &module) &&
                module && GetModuleFileNameA(module, path, MAX_PATH) != 0)
            {
                const char* name = std::strrchr(path, '\\');
                name = name ? name + 1 : path;
                std::snprintf(out, size, "%s+0x%X", name,
                              address - static_cast<uint32_t>(reinterpret_cast<uintptr_t>(module)));
                return;
            }
            std::snprintf(out, size, "?");
        }

        void FormatStack(const TrapSite& site, char* out, size_t size)
        {
            size_t at = 0;
            out[0] = '\0';
            for (uint8_t i = 0; i < site.stackDepth && at + 12 < size; ++i)
            {
                const int n = std::snprintf(out + at, size - at, i ? ",0x%08X" : "0x%08X", site.stack[i]);
                if (n <= 0)
                    break;
                at += static_cast<size_t>(n);
            }
            if (site.stackDepth == 0)
                std::snprintf(out, size, "-");
        }

        void LogSite(const char* prefix, const TrapSite& site)
        {
            char where[MAX_PATH + 16];
            char stack[128];
            DescribeAddress(site.address, where, sizeof(where));
            FormatStack(site, stack, sizeof(stack));
            LogShimA(LogLevel::Info, kComponent,
                     "[FPTRAP] %s %s %s addr=0x%08X (%s) count=%u firstFrame=%u eip=0x%08X%s stack=%s", prefix,
                     FpTrap::KindName(site.kind), FpTrap::FlagsName(site.flags), site.address, where, site.count,
                     site.firstFrame, site.firstEip, site.kind == Kind::X87 && !site.adjacent ? " nonadjacent" : "",
                     stack);
        }

        void LogNewSites()
        {
            if (g_Unrecovered != 0 && !g_UnrecoveredWarned)
            {
                g_UnrecoveredWarned = true;
                LogShimA(LogLevel::Warn, kComponent,
                         "[FPTRAP] WARNING: an x87 trap could not be recovered. Its faulting instruction was "
                         "SKIPPED, so game state now differs from stock (a wrong value or a deeper x87 stack). "
                         "FpTrapLog stopped unmasking; restart the game before trusting this session.");
            }
            for (size_t i = 0; i < g_Table.Size(); ++i)
            {
                TrapSite& site = g_Table.At(i);
                if (site.logged)
                    continue;
                site.logged = true;
                if (g_LogBudget > 0)
                {
                    --g_LogBudget;
                    LogSite("new site", site);
                }
                else if (!g_BudgetNoted)
                {
                    g_BudgetNoted = true;
                    LogShimA(LogLevel::Info, kComponent,
                             "[FPTRAP] new-site log budget (%d) spent; the exit summary lists the rest",
                             kNewSiteLogBudget);
                }
            }
        }

        void WriteSummary(const char* reason)
        {
            if (g_SummaryWritten.exchange(true, std::memory_order_acq_rel))
                return;
            LogShimA(g_Unrecovered != 0 ? LogLevel::Warn : LogLevel::Info, kComponent,
                     "[FPTRAP] summary (%s): frames=%u traps=%u sites=%u dropped=%u inPlace=%u raised=%u "
                     "unrecovered=%u%s",
                     reason ? reason : "?", g_Frame, g_Table.Total(), static_cast<unsigned>(g_Table.Size()),
                     g_Table.Dropped(), g_InPlace, g_Raised, g_Unrecovered,
                     g_Unrecovered != 0 ? " -- WARNING: skipped x87 instructions changed game state" : "");
            static uint16_t order[kTableSize];
            const size_t n = g_Table.SortedByCount(order, kTableSize);
            char prefix[16];
            for (size_t i = 0; i < n; ++i)
            {
                std::snprintf(prefix, sizeof(prefix), "#%u", static_cast<unsigned>(i + 1));
                LogSite(prefix, g_Table.At(order[i]));
            }
        }

        bool SwitchRequested()
        {
            char value[8] = {};
            if (GetEnvironmentVariableA("OPENSHIM_FP_TRAP_LOG", value, sizeof(value)) == 0 &&
                GetEnvironmentVariableA("BZR_FP_TRAP_LOG", value, sizeof(value)) != 0)
                return DiagnosticSwitch::Requested("BZR_FP_TRAP_LOG", "Diagnostics", "FpTrapLog");
            return DiagnosticSwitch::Requested("OPENSHIM_FP_TRAP_LOG", "Diagnostics", "FpTrapLog");
        }

        const float kOne = 1.0f;
        const float kZero = 0.0f;

        __declspec(noinline) void SelfTestX87(float* dst)
        {
            __asm
            {
                mov eax, dst
                fld1
                fldz
                fdivp st(1), st
                fstp dword ptr [eax]
            }
        }

        __declspec(noinline) void SelfTestSse(float* dst)
        {
            __asm
            {
                mov eax, dst
                movss xmm0, kOne
                movss xmm1, kZero
                divss xmm0, xmm1
                movss [eax], xmm0
            }
        }

        // A trap the handler declined (for example a CONTEXT without the
        // extended registers) lands here instead of leaving the patch stage.
        bool GuardedRun(void (*fn)(float*), float* dst)
        {
            __try
            {
                fn(dst);
                return true;
            }
            __except (FpTrap::IsFloatExceptionCode(GetExceptionCode()) ? EXCEPTION_EXECUTE_HANDLER
                                                                        : EXCEPTION_CONTINUE_SEARCH)
            {
                FpTrap::MaskCurrentThread();
                return false;
            }
        }

        uint32_t Bits(float f)
        {
            uint32_t u = 0;
            std::memcpy(&u, &f, sizeof(u));
            return u;
        }

        // Runs both trap kinds through the installed handler on this thread.
        bool SelfTest(char* why, size_t size)
        {
            float x87 = 0.0f;
            float sse = 0.0f;
            // The patch thread gets its exact FPU/SSE state back afterwards
            // (control words, sticky flags, registers).
            alignas(16) static uint8_t saved[512];
            uint8_t* savedPtr = saved;
            __asm
            {
                mov eax, savedPtr
                fxsave [eax]
            }
            g_SelfTest = true;
            g_TargetThread = GetCurrentThreadId();

            g_SelfTestHits = 0;
            g_UnmaskLive = 1;
            FpTrap::UnmaskCurrentThread();
            const bool x87Ran = GuardedRun(&SelfTestX87, &x87);
            const int x87Hits = g_SelfTestHits;
            const TrapReport x87Report = g_SelfTestReport;

            g_SelfTestHits = 0;
            g_UnmaskLive = 1;
            FpTrap::UnmaskCurrentThread();
            const bool sseRan = GuardedRun(&SelfTestSse, &sse);
            const int sseHits = g_SelfTestHits;
            const TrapReport sseReport = g_SelfTestReport;

            g_UnmaskLive = 0;
            FpTrap::MaskCurrentThread();
            g_TargetThread = 0;
            g_SelfTest = false;
            __asm
            {
                mov eax, savedPtr
                fxrstor [eax]
            }

            const bool x87Ok = x87Ran && x87Hits == 1 && x87Report.kind == Kind::X87 &&
                               x87Report.result == RecoverResult::Recovered && Bits(x87) == 0x7F800000u;
            const bool sseOk = sseRan && sseHits == 1 && sseReport.kind == Kind::Sse &&
                               sseReport.result == RecoverResult::Recovered && Bits(sse) == 0x7F800000u;
            std::snprintf(why, size, "x87 hits=%d %s result=0x%08X; sse hits=%d %s result=0x%08X", x87Hits,
                          FpTrap::RecoverResultName(x87Report.result), Bits(x87), sseHits,
                          FpTrap::RecoverResultName(sseReport.result), Bits(sse));
            return x87Ok && sseOk;
        }
    }

    void InitializeFpTrapLog()
    {
        if (!SwitchRequested())
            return;
        if (!IsProcessorFeaturePresent(PF_XMMI_INSTRUCTIONS_AVAILABLE))
        {
            LogShimA(LogLevel::Warn, kComponent, "[FPTRAP] off: no SSE");
            return;
        }
        if (!FpTrap::AllocateRecoveryStub(g_Scratch))
        {
            LogShimA(LogLevel::Warn, kComponent, "[FPTRAP] off: stub allocation failed (%lu)", GetLastError());
            return;
        }
        HMODULE self = nullptr;
        if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN,
                                reinterpret_cast<LPCSTR>(&FpTrapHandler), &self))
        {
            LogShimA(LogLevel::Warn, kComponent, "[FPTRAP] off: could not pin the module (%lu)", GetLastError());
            return;
        }
        g_SystemModules.Capture();
        g_Handler = AddVectoredExceptionHandler(1, FpTrapHandler);
        if (!g_Handler)
        {
            LogShimA(LogLevel::Warn, kComponent, "[FPTRAP] off: AddVectoredExceptionHandler failed");
            return;
        }
        char why[160] = {};
        if (!SelfTest(why, sizeof(why)))
        {
            RemoveVectoredExceptionHandler(g_Handler);
            g_Handler = nullptr;
            LogShimA(LogLevel::Warn, kComponent, "[FPTRAP] off: recovery self-test failed (%s)", why);
            return;
        }
        g_Enabled.store(true, std::memory_order_release);
        LogShimA(LogLevel::Info, kComponent,
                 "[FPTRAP] on: self-test passed (%s); unmasks SSE IE/ZE and x87 ZE on the main thread once per "
                 "frame, first trap per frame recovered and recorded",
                 why);
    }

    void FpTrapLogFrameTick()
    {
        if (!g_Enabled.load(std::memory_order_acquire))
            return;
        const DWORD thread = GetCurrentThreadId();
        if (g_TargetThread == 0)
        {
            g_TargetThread = thread;
            LogShimA(LogLevel::Info, kComponent, "[FPTRAP] armed on main thread %lu", thread);
        }
        if (thread != g_TargetThread)
            return;
        ++g_Frame;
        LogNewSites();
        if (g_Stopped.load(std::memory_order_acquire))
            return;
        g_UnmaskLive = 1;
        FpTrap::UnmaskCurrentThread();
    }

    // Open: g_UnmaskLive is cleared by the handler even when the CRT has
    // re-unmasked the thread (it restores its saved control word after a
    // raise), so a shutdown on a non-main thread can write the summary while
    // the main thread is still recording. That can only garble the log.
    void ShutdownFpTrapLog(const char* reason)
    {
        if (!g_Enabled.load(std::memory_order_acquire))
            return;
        g_Stopped.store(true, std::memory_order_release);
        // Only the main thread can mask itself. From another thread the
        // handler stays installed (module pinned) and still recovers a trap
        // until the main thread stops calling the frame tick.
        if (g_TargetThread != 0 && GetCurrentThreadId() == g_TargetThread)
        {
            FpTrap::MaskCurrentThread();
            g_UnmaskLive = 0;
            LogNewSites();
            WriteSummary(reason);
        }
        else if (g_TargetThread == 0)
        {
            WriteSummary(reason);
        }
        else
        {
            // Another thread: the table belongs to the main thread, which may
            // still be running. Summarise only when it can no longer trap.
            if (g_UnmaskLive == 0)
                WriteSummary(reason);
        }
    }
}
