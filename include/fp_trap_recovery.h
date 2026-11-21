#pragma once
// fp_trap_recovery.h
// BZR Open Shim - the Win32/x86 half of [Diagnostics] FpTrapLog: reading and
// writing the thread's FPU masks, and recovering a trapped thread inside its
// CONTEXT so it continues with the stock (masked) NaN/inf result.
// Shared by src/patches/fp_trap_log.cpp and tests/fp_trap_recovery_win32_tests.cpp,
// which proves the recovery on the real OS. Bit policy: fp_trap_log_policy.h.
//
// SSE: the fault is precise (EIP = faulting instruction, nothing written).
// Masking MXCSR in ExtendedRegisters and continuing re-runs it masked.
//
// x87: the exception surfaces at the next waiting x87 instruction (EIP), and
// the faulting one (FPU instruction pointer = FloatSave.ErrorOffset) left TOP
// and its operands unchanged (Intel SDM vol. 1, 8.5.3: an unmasked
// divide-by-zero "TOP and source operands remain unchanged"). Continuing at
// EIP would skip it: its destination would keep the old value and a popping
// form would leave the stack one deeper. So the faulting instruction is
// re-run in a stub against the trapped thread's own FXSAVE image, masked,
// with any memory operand rewritten to the recorded FPU data pointer; the
// resulting x87 state is written back (FXSAVE and FNSAVE layouts) and the
// thread continues at EIP. When the stub cannot be used but the instruction
// was decoded, matched the recorded FOP, and nothing ran between the fault
// and the report, EIP is moved back to the faulting instruction instead.
// Anything else is Unrecovered: the faulting instruction is skipped, which
// changes game state (FpTrapLog then stops for the session).
//
// Known limit of the x87 re-run: when other code ran between the fault and
// the report (non-adjacent), the memory operand is re-read at recovery time.
// A store to that address in between would make the re-run use the new
// value. The stub refuses an operand below the trapped ESP (exception
// dispatch has overwritten it); a store elsewhere cannot be detected.
//
// Known limit of the deferral itself: a pending x87 exception that first
// meets a NON-waiting x87 instruction is lost silently. FNCLEX (including the
// logger's own Unmask/MaskCurrentThread in the frame tick and at shutdown),
// FNINIT, FNSAVE and FXRSTOR discard it, so the faulting op stays skipped
// (TOP and destination unchanged) with no trap and no warning. FNSTENV masks
// the control word, so the later trap is classified Raised and logged as
// "raised" rather than as a skip. Both need a fault still pending across a
// function boundary, which is rare.
//
// Software raises (Kind::Raised): the CRT math-error path calls
// RaiseException with a float code after clearing the flags. Nothing is
// pending; masking both units in the CONTEXT and continuing returns from
// RaiseException and the CRT hands back the stock result.
//
// No access faults inside the handler: code bytes and memory operands are
// checked with VirtualQuery before they are touched, so a handled trap never
// produces a first-chance access violation (or a crash report from one).

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error fp_trap_recovery.h is x86 MSVC only
#endif

#include "fp_trap_log_policy.h"

#include <Windows.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
namespace FpTrap
{
    enum class RecoverResult : uint8_t
    {
        Recovered,        // x87 via the stub, or SSE re-run
        RecoveredInPlace, // x87: EIP moved back to the adjacent faulting instruction
        RaisedMasked,     // software raise: masked and continued after RaiseException
        NoContextState,   // CONTEXT lacks FLOATING_POINT / EXTENDED_REGISTERS
        Unrecovered,      // x87 could not be re-run; continued at EIP (op skipped)
    };

    inline const char* RecoverResultName(RecoverResult r)
    {
        switch (r)
        {
        case RecoverResult::Recovered: return "recovered";
        case RecoverResult::RecoveredInPlace: return "recovered-in-place";
        case RecoverResult::RaisedMasked: return "raised-masked";
        case RecoverResult::NoContextState: return "no-context-state";
        case RecoverResult::Unrecovered: return "unrecovered";
        }
        return "?";
    }

    struct TrapReport
    {
        Kind kind = Kind::None;
        uint8_t flags = 0;
        uint32_t address = 0; // faulting instruction
        uint32_t eip = 0;     // where the exception was reported
        bool adjacent = false;
        RecoverResult result = RecoverResult::NoContextState;
    };

    // One per recovering thread (FpTrapLog only recovers the main thread).
    struct RecoveryScratch
    {
        alignas(16) uint8_t own[512];
        alignas(16) uint8_t image[512];
        uint8_t legacy[108];
        uint8_t* stub = nullptr;
    };

    inline bool AllocateRecoveryStub(RecoveryScratch& s)
    {
        if (s.stub)
            return true;
        s.stub = static_cast<uint8_t*>(
            VirtualAlloc(nullptr, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
        return s.stub != nullptr;
    }

    // ---- live thread state --------------------------------------------------

    inline void UnmaskCurrentThread()
    {
        uint16_t cw = 0;
        uint32_t mxcsr = 0;
        __asm
        {
            fnclex
            fnstcw cw
            stmxcsr mxcsr
        }
        ControlState s;
        s.x87Control = cw;
        s.x87Status = 0;
        s.mxcsr = mxcsr;
        s = Unmasked(s);
        cw = s.x87Control;
        mxcsr = s.mxcsr;
        __asm
        {
            fldcw cw
            ldmxcsr mxcsr
        }
    }

    // FNCLEX first: masking with a flag already pending must not leave ES set.
    inline void MaskCurrentThread()
    {
        uint16_t cw = 0;
        uint32_t mxcsr = 0;
        __asm
        {
            fnclex
            fnstcw cw
            stmxcsr mxcsr
        }
        ControlState s;
        s.x87Control = cw;
        s.mxcsr = mxcsr;
        s = Masked(s);
        cw = s.x87Control;
        mxcsr = s.mxcsr;
        __asm
        {
            fldcw cw
            ldmxcsr mxcsr
        }
    }

    // ---- saved (CONTEXT) state ------------------------------------------------

    inline bool HasFpContext(const CONTEXT* c)
    {
        return (c->ContextFlags & CONTEXT_FLOATING_POINT) == CONTEXT_FLOATING_POINT &&
               (c->ContextFlags & CONTEXT_EXTENDED_REGISTERS) == CONTEXT_EXTENDED_REGISTERS;
    }

    inline ControlState ReadContextState(const CONTEXT* c)
    {
        ControlState s;
        s.x87Control = static_cast<uint16_t>(c->FloatSave.ControlWord);
        s.x87Status = static_cast<uint16_t>(c->FloatSave.StatusWord);
        std::memcpy(&s.mxcsr, c->ExtendedRegisters + kFxsaveMxcsrOffset, sizeof(s.mxcsr));
        return s;
    }

    // Writes the control/status words to both save areas (whichever one the
    // OS restores from) and MXCSR to the FXSAVE image.
    inline void WriteContextState(CONTEXT* c, const ControlState& s)
    {
        c->FloatSave.ControlWord = (c->FloatSave.ControlWord & 0xFFFF0000u) | s.x87Control;
        c->FloatSave.StatusWord = (c->FloatSave.StatusWord & 0xFFFF0000u) | s.x87Status;
        std::memcpy(c->ExtendedRegisters + kFxsaveFcwOffset, &s.x87Control, sizeof(uint16_t));
        std::memcpy(c->ExtendedRegisters + kFxsaveFswOffset, &s.x87Status, sizeof(uint16_t));
        std::memcpy(c->ExtendedRegisters + kFxsaveMxcsrOffset, &s.mxcsr, sizeof(uint32_t));
    }

    // EBP walk of the trapped (current) thread's stack. Every page in
    // [StackLimit, StackBase) is committed and WalkEbpFrames keeps each read
    // inside it, so no read can fault.
    inline uint8_t WalkCurrentStack(const CONTEXT* c, uint32_t* out)
    {
        const NT_TIB* tib = reinterpret_cast<const NT_TIB*>(NtCurrentTeb());
        const uint32_t low = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(tib->StackLimit));
        const uint32_t high = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(tib->StackBase));
        auto read = [](uint32_t address, uint32_t& value) {
            value = *reinterpret_cast<const volatile uint32_t*>(static_cast<uintptr_t>(address));
            return true;
        };
        return static_cast<uint8_t>(WalkEbpFrames(c->Ebp, low, high, read, out, kStackDepth));
    }

    // Image ranges of the CRT and system DLLs a software raise passes
    // through, captured once at start-up (GetModuleHandleA: no load, no
    // refcount). The handler then only compares ranges -- no loader call, no
    // loader lock inside the exception handler. A static CRT lives in the exe
    // and is not covered (FirstCallerOutside then falls back to frame 0).
    struct SystemModules
    {
        static constexpr size_t kMax = 16;
        uint32_t base[kMax] = {};
        uint32_t end[kMax] = {};
        size_t count = 0;

        void Add(HMODULE module)
        {
            if (!module || count == kMax)
                return;
            const uint8_t* image = reinterpret_cast<const uint8_t*>(module);
            const IMAGE_DOS_HEADER* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(image);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return;
            const IMAGE_NT_HEADERS32* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(image + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return;
            const uint32_t b = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(module));
            base[count] = b;
            end[count] = b + nt->OptionalHeader.SizeOfImage;
            ++count;
        }

        void Capture()
        {
            static const char* const kNames[] = {
                "ntdll.dll",      "kernelbase.dll", "kernel32.dll",  "ucrtbase.dll",
                "vcruntime140.dll", "msvcrt.dll",   "msvcr120.dll",  "msvcr110.dll",
                "msvcr100.dll",   "msvcr90.dll",    "msvcr80.dll",   "msvcr71.dll",
            };
            count = 0;
            for (const char* name : kNames)
                Add(GetModuleHandleA(name));
        }

        bool Contains(uint32_t address) const
        {
            for (size_t i = 0; i < count; ++i)
            {
                if (address >= base[i] && address < end[i])
                    return true;
            }
            return false;
        }
    };

    namespace Detail
    {
        // VirtualQuery-checked access, so the handler never takes an access
        // fault (and never triggers a first-chance crash report) probing.
        inline bool Readable(DWORD protect)
        {
            if (protect & (PAGE_GUARD | PAGE_NOACCESS))
                return false;
            return (protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ |
                               PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)) != 0;
        }

        inline bool Writable(DWORD protect)
        {
            if (protect & (PAGE_GUARD | PAGE_NOACCESS))
                return false;
            return (protect & (PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE |
                               PAGE_EXECUTE_WRITECOPY)) != 0;
        }

        // Bytes from `address` (up to `size`) that are committed and readable
        // (and writable when `write`), across region boundaries.
        // Open (very rare): the memory operand is checked as a flat address,
        // but the stub keeps segment prefixes (e.g. fs:). A TLS-based x87
        // operand then fails this check (Unrecovered) or faults in the stub;
        // RunStub's __except catches that, but a crash logger's first-chance
        // handler still sees the fault.
        inline size_t AccessibleBytes(uint32_t address, size_t size, bool write)
        {
            size_t done = 0;
            while (done < size)
            {
                MEMORY_BASIC_INFORMATION mbi = {};
                const uintptr_t at = static_cast<uintptr_t>(address) + done;
                if (VirtualQuery(reinterpret_cast<LPCVOID>(at), &mbi, sizeof(mbi)) == 0)
                    break;
                if (mbi.State != MEM_COMMIT || !(write ? Writable(mbi.Protect) : Readable(mbi.Protect)))
                    break;
                const uintptr_t end = reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
                if (end <= at)
                    break;
                const size_t span = static_cast<size_t>(end - at);
                done += span < size - done ? span : size - done;
            }
            return done;
        }

        // own = this thread's state (restored at the end); image = the trapped
        // thread's FXSAVE image (loaded, the stub run, saved again); legacy =
        // the same x87 state in FNSAVE layout for CONTEXT.FloatSave. The
        // operand was checked accessible first; the __except is a backstop.
        inline bool RunStub(RecoveryScratch& s)
        {
            uint8_t* own = s.own;
            uint8_t* image = s.image;
            uint8_t* legacy = s.legacy;
            uint8_t* stub = s.stub;
            __try
            {
                __asm
                {
                    fnclex
                    mov eax, own
                    fxsave [eax]
                    mov eax, image
                    fxrstor [eax]
                    mov eax, stub
                    call eax
                    mov eax, image
                    fxsave [eax]
                    mov eax, legacy
                    fnsave [eax]
                    mov eax, own
                    fxrstor [eax]
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                __asm
                {
                    mov eax, own
                    fxrstor [eax]
                }
                return false;
            }
        }

        // `verified` is set once the faulting instruction is decoded and its
        // FOP matches: only then may the caller move EIP back to it.
        inline bool RecoverX87ViaStub(CONTEXT* c, RecoveryScratch& s, const ControlState& state,
                                      TrapReport& r, bool& verified)
        {
            verified = false;
            if (r.address == 0)
                return false;
            uint8_t code[15] = {};
            const size_t readable = AccessibleBytes(r.address, sizeof(code), false);
            if (readable < 2)
                return false;
            std::memcpy(code, reinterpret_cast<const void*>(static_cast<uintptr_t>(r.address)), readable);
            const X87Decoded d = DecodeX87(code, readable);
            if (!d.ok)
                return false;
            r.adjacent = r.address + d.length == r.eip;
            uint16_t fop = 0;
            std::memcpy(&fop, c->ExtendedRegisters + kFxsaveFopOffset, sizeof(fop));
            if (!MatchesFop(d, fop))
                return false;
            verified = true;
            if (!s.stub)
                return false;
            const uint32_t dataOffset = c->FloatSave.DataOffset;
            if (d.memory)
            {
                if (dataOffset == 0)
                    return false;
                if (AccessibleBytes(dataOffset, d.operandSize, d.store) < d.operandSize)
                    return false;
                // Non-adjacent: the operand is re-read now, and the stack
                // below the trapped ESP has been overwritten by dispatch.
                const NT_TIB* tib = reinterpret_cast<const NT_TIB*>(NtCurrentTeb());
                const uint32_t stackLimit = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(tib->StackLimit));
                if (!r.adjacent && OverlapsBelowStack(dataOffset, d.operandSize, stackLimit, c->Esp))
                    return false;
            }
            const size_t length = BuildAbsoluteX87(code, d, dataOffset, s.stub, 15);
            if (length == 0)
                return false;
            s.stub[length] = 0xC3; // ret
            FlushInstructionCache(GetCurrentProcess(), s.stub, length + 1);

            std::memcpy(s.image, c->ExtendedRegisters, sizeof(s.image));
            const ControlState masked = RecoveryState(state);
            std::memcpy(s.image + kFxsaveFcwOffset, &masked.x87Control, sizeof(uint16_t));
            std::memcpy(s.image + kFxsaveFswOffset, &masked.x87Status, sizeof(uint16_t));
            std::memcpy(s.image + kFxsaveMxcsrOffset, &masked.mxcsr, sizeof(uint32_t));
            if (!RunStub(s))
                return false;
            std::memcpy(c->ExtendedRegisters, s.image, sizeof(s.image));
            std::memcpy(&c->FloatSave, s.legacy, sizeof(s.legacy)); // Cr0NpxState kept
            return true;
        }
    }

    // Classifies the trap in `c` and recovers in place: the thread continues
    // with both units masked for the trap bits and the stock result (the
    // faulting instruction re-run masked, or, for a software raise, the
    // return from RaiseException with the CRT's own result).
    //
    // The OS leaves the x87 exception pending in the live FPU while the
    // handler runs (verified on Windows 11 WOW64), so the first waiting x87
    // instruction in the handler would raise it again -- including the FWAIT
    // MSVC emits at the start of a __try block in a function with x87 code.
    // Recover therefore clears the live state before anything else; call it
    // before any other x87 instruction or __try in the handler.
    inline RecoverResult Recover(uint32_t code, CONTEXT* c, RecoveryScratch& s, TrapReport& r)
    {
        __asm fnclex
        r = TrapReport();
        r.eip = c->Eip;
        if (!HasFpContext(c))
            return r.result = RecoverResult::NoContextState;
        const ControlState state = ReadContextState(c);
        uint32_t pending = 0;
        r.kind = Classify(state, pending);
        r.flags = static_cast<uint8_t>(pending);
        if (r.kind == Kind::None)
        {
            // Nothing pending: RaiseException from software (the CRT). Taken
            // whatever the saved masks say: the CRT raises from its own view
            // of the control word, and on a repeat call (after it restored
            // its saved, unmasked word) the CONTEXT can already read masked.
            // The caller names the site from the stack walk.
            r.kind = Kind::Raised;
            r.flags = FlagsFromCode(code);
            r.address = c->Eip;
            r.adjacent = true;
            WriteContextState(c, RecoveryState(state));
            return r.result = RecoverResult::RaisedMasked;
        }

        if (r.kind == Kind::Sse)
        {
            r.address = c->Eip;
            r.adjacent = true;
            WriteContextState(c, RecoveryState(state));
            return r.result = RecoverResult::Recovered;
        }

        r.address = c->FloatSave.ErrorOffset;
        bool verified = false;
        if (Detail::RecoverX87ViaStub(c, s, state, r, verified))
            return r.result = RecoverResult::Recovered;
        WriteContextState(c, RecoveryState(state));
        if (verified && r.adjacent)
        {
            c->Eip = r.address;
            return r.result = RecoverResult::RecoveredInPlace;
        }
        return r.result = RecoverResult::Unrecovered;
    }
}
}
