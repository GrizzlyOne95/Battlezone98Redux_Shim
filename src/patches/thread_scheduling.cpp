// thread_scheduling.cpp
// BZR Open Shim - main-thread MMCSS registration and power-throttling opt-out
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Frame-hitch telemetry (perf_telemetry.cpp) shows most hitches are waits on
// Present. These two changes do not raise the average frame rate; they keep
// the scheduler from parking or slowing the frame thread:
//  - MMCSS "Games" gives the frame loop a priority boost while it runs, so
//    background work does not preempt it for a whole quantum.
//  - The power-throttling opt-out stops Windows from placing the process on
//    efficiency cores / reduced clocks (EcoQoS) when it judges it background,
//    and from coarsening its timer resolution while minimised or occluded.
// The frame thread is found by hooking the executable's renderOneFrame import
// and registering from inside the first call, not from the patch thread.

#include "thread_scheduling.h"

#include "bzr_hooks_internal.h"
#include "iat_patch.h"
#include "shim_log.h"

#include <Windows.h>

#include <atomic>
#include <cstdint>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "thread-sched";
        constexpr char kRenderOneFrameExport[] = "?renderOneFrame@Root@Ogre@@QAE_NXZ";

        // processthreadsapi.h names, defined locally because older SDKs lack
        // PROCESS_POWER_THROTTLING_IGNORE_TIMER_RESOLUTION.
        constexpr int kProcessPowerThrottling = 4;   // PROCESS_INFORMATION_CLASS
        constexpr ULONG kPowerThrottlingVersion = 1;
        constexpr ULONG kThrottleExecutionSpeed = 0x1;
        constexpr ULONG kThrottleIgnoreTimerResolution = 0x4;

        struct PowerThrottlingState
        {
            ULONG version;
            ULONG controlMask;
            ULONG stateMask;
        };

        using FnSetProcessInformation = BOOL(WINAPI*)(HANDLE, int, LPVOID, DWORD);
        using FnAvSetMmThreadCharacteristicsW = HANDLE(WINAPI*)(LPCWSTR, LPDWORD);
        using FnAvRevertMmThreadCharacteristics = BOOL(WINAPI*)(HANDLE);
        using FnRenderOneFrame = bool(__thiscall*)(void*);

        void* g_RealRenderOneFrame = nullptr;
        void** g_RenderOneFrameSlot = nullptr;
        FnAvSetMmThreadCharacteristicsW g_AvSet = nullptr;
        FnAvRevertMmThreadCharacteristics g_AvRevert = nullptr;
        HMODULE g_Avrt = nullptr;

        std::atomic<bool> g_PendingRegistration{false};
        HANDLE g_MmcssHandle = nullptr;
        DWORD g_MmcssThreadId = 0;

        void OptOutOfPowerThrottling()
        {
            HMODULE kernel32 = GetModuleHandleW(L"kernel32.dll");
            const auto setInfo = kernel32
                ? reinterpret_cast<FnSetProcessInformation>(GetProcAddress(kernel32, "SetProcessInformation"))
                : nullptr;
            if (!setInfo)
            {
                LogShimA(LogLevel::Info, kComponent,
                         "[ThreadScheduling] SetProcessInformation unavailable; power throttling left as is");
                return;
            }

            PowerThrottlingState state{kPowerThrottlingVersion,
                                       kThrottleExecutionSpeed | kThrottleIgnoreTimerResolution, 0};
            if (setInfo(GetCurrentProcess(), kProcessPowerThrottling, &state, sizeof(state)))
            {
                LogShimA(LogLevel::Info, kComponent,
                         "[ThreadScheduling] power throttling opt-out OK (execution speed + timer resolution)");
                return;
            }
            // Windows 10 before 21H2 rejects the timer-resolution bit; keep the
            // execution-speed half on its own.
            const DWORD fullError = GetLastError();
            state.controlMask = kThrottleExecutionSpeed;
            if (setInfo(GetCurrentProcess(), kProcessPowerThrottling, &state, sizeof(state)))
            {
                LogShimA(LogLevel::Info, kComponent,
                         "[ThreadScheduling] power throttling opt-out OK (execution speed only; timer bit error %lu)",
                         fullError);
                return;
            }
            LogShimA(LogLevel::Info, kComponent,
                     "[ThreadScheduling] power throttling opt-out failed (error %lu / %lu); left as is",
                     fullError, GetLastError());
        }

        void RegisterCurrentThreadWithMmcss()
        {
            DWORD taskIndex = 0;
            HANDLE handle = g_AvSet(L"Games", &taskIndex);
            if (!handle)
            {
                LogShimA(LogLevel::Info, kComponent,
                         "[ThreadScheduling] AvSetMmThreadCharacteristicsW(Games) failed on thread %lu (error %lu)",
                         GetCurrentThreadId(), GetLastError());
                return;
            }
            g_MmcssHandle = handle;
            g_MmcssThreadId = GetCurrentThreadId();
            LogShimA(LogLevel::Info, kComponent,
                     "[ThreadScheduling] MMCSS Games registration OK on frame thread %lu (task index %lu)",
                     g_MmcssThreadId, taskIndex);
        }

        bool __fastcall RenderOneFrameHook(void* self, void* /*edx*/)
        {
            if (g_PendingRegistration.load(std::memory_order_acquire) &&
                g_PendingRegistration.exchange(false, std::memory_order_acq_rel))
            {
                RegisterCurrentThreadWithMmcss();
            }
            return reinterpret_cast<FnRenderOneFrame>(g_RealRenderOneFrame)(self);
        }

        bool ResolveAvrt()
        {
            // System32 only: never pick up an avrt.dll from the game folder.
            g_Avrt = LoadLibraryExW(L"avrt.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
            if (!g_Avrt)
                g_Avrt = LoadLibraryW(L"avrt.dll");   // pre-KB2533623 Windows 7
            if (!g_Avrt)
                return false;
            g_AvSet = reinterpret_cast<FnAvSetMmThreadCharacteristicsW>(
                GetProcAddress(g_Avrt, "AvSetMmThreadCharacteristicsW"));
            g_AvRevert = reinterpret_cast<FnAvRevertMmThreadCharacteristics>(
                GetProcAddress(g_Avrt, "AvRevertMmThreadCharacteristics"));
            return g_AvSet && g_AvRevert;
        }

        // [Fixes] ThreadScheduling, default ON. The kill-switch name maps to
        // the inverted ini key in openshim_env_mapping.cpp.
        bool ReadEnabledSetting()
        {
            return !EnvFlagEnabled("OPENSHIM_DISABLE_THREAD_SCHEDULING");
        }
    }

    void InitializeThreadScheduling()
    {
        if (!ReadEnabledSetting())
        {
            LogShimA(LogLevel::Info, kComponent, "[ThreadScheduling] disabled by [Fixes] ThreadScheduling = 0");
            return;
        }

        OptOutOfPowerThrottling();

        if (!ResolveAvrt())
        {
            LogShimA(LogLevel::Info, kComponent,
                     "[ThreadScheduling] avrt.dll or its MMCSS exports unavailable (error %lu); no MMCSS registration",
                     GetLastError());
            return;
        }

        // Chains whatever already owns the slot (perf telemetry installs its
        // own renderOneFrame hook earlier in the patch stage).
        g_PendingRegistration.store(true, std::memory_order_release);
        const IatPatch::Result result = IatPatch::PatchImport(
            GetModuleHandleW(nullptr), "OgreMain.dll", kRenderOneFrameExport,
            reinterpret_cast<void*>(&RenderOneFrameHook), &g_RealRenderOneFrame,
            &g_RenderOneFrameSlot);
        if (result != IatPatch::Result::Patched || !g_RealRenderOneFrame)
        {
            g_PendingRegistration.store(false, std::memory_order_release);
            LogShimA(LogLevel::Warn, kComponent,
                     "[ThreadScheduling] import %s not redirected (result=%d); no MMCSS registration",
                     kRenderOneFrameExport, static_cast<int>(result));
            return;
        }
        LogShimA(LogLevel::Info, kComponent,
                 "[ThreadScheduling] waiting for the first frame to register the frame thread with MMCSS");
    }

    void ShutdownThreadScheduling()
    {
        g_PendingRegistration.store(false, std::memory_order_release);
        // The import slot keeps pointing at the hook, which is a plain
        // pass-through once registration is done.
        if (!g_MmcssHandle || !g_AvRevert)
            return;
        const BOOL reverted = g_AvRevert(g_MmcssHandle);
        LogShimA(LogLevel::Info, kComponent,
                 "[ThreadScheduling] AvRevertMmThreadCharacteristics %s (frame thread %lu, caller %lu, error %lu)",
                 reverted ? "OK" : "failed", g_MmcssThreadId, GetCurrentThreadId(),
                 reverted ? 0ul : GetLastError());
        g_MmcssHandle = nullptr;
    }
}
