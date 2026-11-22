// Proves include/fp_trap_recovery.h on the real OS (x86 MSVC, WOW64 on a
// 64-bit Windows): unmask, raise a divide-by-zero or invalid operation, let a
// vectored handler recover through FpTrap::Recover, and check that execution
// continued with the stock masked result, the x87 stack depth is unchanged,
// integer code between an x87 fault and its report ran exactly once, and the
// thread is masked again afterwards.
#include "fp_trap_recovery.h"

#include <cmath>
#include <cstdio>
#include <cstring>

#include "test_check.h"

namespace
{
    using namespace BZROpenShim::FpTrap;

    RecoveryScratch g_Scratch;
    volatile LONG g_Live = 0;
    DWORD g_Thread = 0;
    int g_Hits = 0;
    DWORD g_LastCode = 0;
    TrapReport g_Last;
    bool g_SkipMode = false; // mask and continue at EIP without re-running

    int g_AccessViolations = 0;
    SystemModules g_System;
    uint32_t g_LastSite = 0;

    LONG CALLBACK Handler(EXCEPTION_POINTERS* p)
    {
        if (p->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && GetCurrentThreadId() == g_Thread)
            ++g_AccessViolations;
        if (!ShouldConsider(p->ExceptionRecord->ExceptionCode, GetCurrentThreadId(), g_Thread))
            return EXCEPTION_CONTINUE_SEARCH;
        if (g_SkipMode)
        {
            __asm fnclex
            WriteContextState(p->ContextRecord, RecoveryState(ReadContextState(p->ContextRecord)));
            g_Live = 0;
            ++g_Hits;
            return EXCEPTION_CONTINUE_EXECUTION;
        }
        TrapReport r;
        const RecoverResult result = Recover(p->ExceptionRecord->ExceptionCode, p->ContextRecord, g_Scratch, r);
        if (result == RecoverResult::NoContextState)
        {
            g_Last = r;
            return EXCEPTION_CONTINUE_SEARCH;
        }
        g_Live = 0;
        ++g_Hits;
        g_LastCode = p->ExceptionRecord->ExceptionCode;
        g_Last = r;
        if (r.kind == Kind::Raised)
        {
            // Same site rule as the plugin (fp_trap_log.cpp).
            uint32_t stack[kStackDepth] = {};
            const uint8_t depth = WalkCurrentStack(p->ContextRecord, stack);
            g_LastSite = FirstCallerOutside(stack, depth, [](uint32_t a) { return g_System.Contains(a); });
        }
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    void Arm()
    {
        g_Hits = 0;
        g_Last = TrapReport();
        g_LastCode = 0;
        g_Live = 1;
        UnmaskCurrentThread();
    }

    uint32_t Bits(float f)
    {
        uint32_t u = 0;
        std::memcpy(&u, &f, sizeof(u));
        return u;
    }

    // x87 tag word all-empty (0xFFFF in the FNSTENV image) = stack depth 0.
    bool X87StackEmpty()
    {
        uint8_t env[28] = {};
        uint8_t* p = env;
        __asm
        {
            mov eax, p
            fnstenv [eax]
            fldcw [eax] // fnstenv masks everything; put the control word back
        }
        uint16_t tag = 0;
        std::memcpy(&tag, env + 8, sizeof(tag));
        return tag == 0xFFFF;
    }

    bool ThreadMasked()
    {
        uint16_t cw = 0;
        uint32_t mxcsr = 0;
        __asm
        {
            fnstcw cw
            stmxcsr mxcsr
        }
        return (cw & kX87TrapBits) == kX87TrapBits &&
               (mxcsr & (kSseTrapBits << kMxcsrMaskShift)) == (kSseTrapBits << kMxcsrMaskShift);
    }

    const float kOne = 1.0f;
    const float kZero = 0.0f;
    const float kMinusOne = -1.0f;

    // fdivp immediately followed by the waiting fstp (adjacent).
    __declspec(noinline) void X87DividePop(float* dst)
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

    // fdiv m32 through [esi], then integer code that changes esi and counts,
    // then the waiting fstp: the stub must use the recorded data pointer and
    // the integer code must run once.
    __declspec(noinline) void X87DivideMemoryNonAdjacent(float* dst, int* counter)
    {
        const float* zero = &kZero;
        __asm
        {
            mov eax, dst
            mov ecx, counter
            mov esi, zero
            fld1
            fdiv dword ptr [esi]
            mov esi, 0
            add dword ptr [ecx], 1
            fstp dword ptr [eax]
        }
    }

    // fdiv m32 with a SIB operand and disp8, adjacent.
    __declspec(noinline) void X87DivideSib(float* dst)
    {
        const float* zeroMinus4 = reinterpret_cast<const float*>(reinterpret_cast<const char*>(&kZero) - 4);
        __asm
        {
            mov eax, dst
            mov edx, zeroMinus4
            xor ecx, ecx
            fld1
            fdiv dword ptr [edx + ecx * 4 + 4]
            fstp dword ptr [eax]
        }
    }

    // fdiv m32 on a slot below ESP, then integer code, then the waiting fstp:
    // exception dispatch overwrites that slot before the handler runs, so the
    // re-run must be refused (Unrecovered: fdiv skipped, st0 stays 1.0).
    __declspec(noinline) void X87DivideBelowEspNonAdjacent(float* dst, int* counter)
    {
        __asm
        {
            mov eax, dst
            mov ecx, counter
            mov dword ptr [esp - 16], 0
            fld1
            fdiv dword ptr [esp - 16]
            add dword ptr [ecx], 1
            fstp dword ptr [eax]
        }
    }

    // x87 invalid (0/0) stays masked by policy: no trap, stock NaN.
    __declspec(noinline) void X87ZeroOverZero(float* dst)
    {
        __asm
        {
            mov eax, dst
            fldz
            fldz
            fdivp st(1), st
            fstp dword ptr [eax]
        }
    }

    __declspec(noinline) void SseDivide(float* dst)
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

    __declspec(noinline) void SseSqrtNegative(float* dst)
    {
        __asm
        {
            mov eax, dst
            movss xmm0, kMinusOne
            sqrtss xmm0, xmm0
            movss [eax], xmm0
        }
    }

    __declspec(noinline) int SseTruncateHuge()
    {
        const float huge = 3.0e9f;
        int result = 0;
        __asm
        {
            movss xmm0, huge
            cvttss2si eax, xmm0
            mov result, eax
        }
        return result;
    }

    void TestX87DividePop()
    {
        float r = 0.0f;
        Arm();
        X87DividePop(&r);
        CHECK(g_Hits == 1);
        CHECK(g_Last.kind == Kind::X87);
        CHECK(g_Last.flags == kX87ZeroDivide);
        CHECK(g_Last.result == RecoverResult::Recovered);
        CHECK(g_Last.adjacent);
        CHECK(Bits(r) == 0x7F800000u);
        CHECK(X87StackEmpty());
        CHECK(ThreadMasked());
        const uint8_t* site = reinterpret_cast<const uint8_t*>(static_cast<uintptr_t>(g_Last.address));
        CHECK(g_Last.address != 0 && site[0] == 0xDE && site[1] == 0xF9);
        CHECK(g_Last.eip == g_Last.address + 2);
        std::printf("x87 fdivp: code=0x%08lX addr=0x%08X eip=0x%08X result=%s\n", g_LastCode, g_Last.address,
                    g_Last.eip, RecoverResultName(g_Last.result));
    }

    // Why the stub exists: continuing at EIP skips the faulting fdivp. Its
    // operands are untouched (st0 = 0 divisor, st1 = 1), so the fstp stores
    // 0.0 instead of inf and one value is left on the x87 stack.
    void TestX87SkipWouldLoseResult()
    {
        float r = -1.0f;
        g_SkipMode = true;
        Arm();
        X87DividePop(&r);
        g_SkipMode = false;
        CHECK(g_Hits == 1);
        CHECK(Bits(r) == 0x00000000u);
        CHECK(!X87StackEmpty());
        __asm fstp st(0)
        CHECK(X87StackEmpty());
    }

    void TestX87DivideMemoryNonAdjacent()
    {
        float r = 0.0f;
        int counter = 0;
        Arm();
        X87DivideMemoryNonAdjacent(&r, &counter);
        CHECK(g_Hits == 1);
        CHECK(g_Last.kind == Kind::X87);
        CHECK(g_Last.result == RecoverResult::Recovered);
        CHECK(!g_Last.adjacent);
        CHECK(Bits(r) == 0x7F800000u);
        CHECK(counter == 1);
        CHECK(X87StackEmpty());
        std::printf("x87 fdiv m32 non-adjacent: addr=0x%08X eip=0x%08X counter=%d\n", g_Last.address, g_Last.eip,
                    counter);
    }

    void TestX87DivideSib()
    {
        float r = 0.0f;
        Arm();
        X87DivideSib(&r);
        CHECK(g_Hits == 1);
        CHECK(g_Last.result == RecoverResult::Recovered);
        CHECK(Bits(r) == 0x7F800000u);
        CHECK(X87StackEmpty());
    }

    void TestX87InvalidStaysMasked()
    {
        float r = 0.0f;
        Arm();
        X87ZeroOverZero(&r);
        CHECK(g_Hits == 0);
        CHECK(Bits(r) == 0xFFC00000u); // QNaN floating-point indefinite
        CHECK(X87StackEmpty());
        g_Live = 0;
        MaskCurrentThread();
    }

    void TestSseDivide()
    {
        float r = 0.0f;
        Arm();
        SseDivide(&r);
        CHECK(g_Hits == 1);
        CHECK(g_Last.kind == Kind::Sse);
        CHECK(g_Last.flags == kMxcsrZeroDivide);
        CHECK(g_Last.result == RecoverResult::Recovered);
        CHECK(Bits(r) == 0x7F800000u);
        CHECK(ThreadMasked());
        const uint8_t* site = reinterpret_cast<const uint8_t*>(static_cast<uintptr_t>(g_Last.address));
        CHECK(site[0] == 0xF3 && site[1] == 0x0F && site[2] == 0x5E);
        std::printf("sse divss: code=0x%08lX addr=0x%08X\n", g_LastCode, g_Last.address);
    }

    void TestSseInvalid()
    {
        float r = 0.0f;
        Arm();
        SseSqrtNegative(&r);
        CHECK(g_Hits == 1);
        CHECK(g_Last.flags == kMxcsrInvalid);
        CHECK(Bits(r) == 0xFFC00000u);
        std::printf("sse sqrtss(-1): code=0x%08lX\n", g_LastCode);

        Arm();
        const int truncated = SseTruncateHuge();
        CHECK(g_Hits == 1);
        CHECK(g_Last.flags == kMxcsrInvalid);
        CHECK(static_cast<uint32_t>(truncated) == 0x80000000u);
    }

    void TestMaskedIsUntouched()
    {
        float r = 0.0f;
        g_Hits = 0;
        g_Live = 0;
        MaskCurrentThread();
        X87DividePop(&r);
        SseDivide(&r);
        CHECK(g_Hits == 0);
        CHECK(Bits(r) == 0x7F800000u);
    }

    // Another thread's trap is not considered: its own SEH frame sees it.
    DWORD WINAPI OtherThread(void*)
    {
        float r = 0.0f;
        UnmaskCurrentThread();
        __try
        {
            SseDivide(&r);
        }
        __except (GetExceptionCode() == STATUS_FLOAT_MULTIPLE_TRAPS ||
                          GetExceptionCode() == STATUS_FLOAT_DIVIDE_BY_ZERO
                      ? EXCEPTION_EXECUTE_HANDLER
                      : EXCEPTION_CONTINUE_SEARCH)
        {
            MaskCurrentThread();
            return 7;
        }
        MaskCurrentThread();
        return 0;
    }

    void TestOtherThreadIgnored()
    {
        g_Hits = 0;
        g_Live = 1; // live, but for g_Thread only
        HANDLE t = CreateThread(nullptr, 0, OtherThread, nullptr, 0, nullptr);
        OpenShimTest::Require(t != nullptr, "CreateThread");
        WaitForSingleObject(t, 5000);
        DWORD code = 0;
        GetExitCodeThread(t, &code);
        CloseHandle(t);
        g_Live = 0;
        CHECK(g_Hits == 0);
        CHECK(code == 7);
    }

    // The MSVC CRT math-error path: with ZM unmasked, log(0) and pow(0,-1)
    // clear the flags and call RaiseException(STATUS_FLOAT_DIVIDE_BY_ZERO)
    // themselves. Nothing is pending in the saved state; the handler must
    // still take it (mask and continue) or the process dies. The CRT may put
    // its saved (unmasked) control word back afterwards, so the later calls
    // also prove the gate does not depend on the unmask still being live.
    // Two game-side callers of log(0). The inline asm keeps an EBP frame in
    // each, so the walk reaches them past the CRT and KernelBase frames.
    __declspec(noinline) double LogCallerA(volatile double* zero)
    {
        __asm nop
        return std::log(*zero);
    }

    __declspec(noinline) double LogCallerB(volatile double* zero)
    {
        __asm nop
        return std::log(*zero) + 0.0;
    }

    // A software raise is keyed on its first caller outside the CRT and
    // system DLLs, so two callers give two sites (not one inside the CRT).
    void TestRaisedSitesPerCaller()
    {
        volatile double zero = 0.0;
        Arm();
        g_LastSite = 0;
        const double a = LogCallerA(&zero);
        const uint32_t siteA = g_LastSite;
        Arm();
        g_LastSite = 0;
        const double b = LogCallerB(&zero);
        const uint32_t siteB = g_LastSite;
        g_Live = 0;
        MaskCurrentThread();

        CHECK(g_System.count >= 3); // ntdll, kernelbase, kernel32 at least
        CHECK(std::isinf(a) && std::isinf(b));
        CHECK(siteA != 0 && siteB != 0);
        CHECK(siteA != siteB);
        CHECK(!g_System.Contains(siteA) && !g_System.Contains(siteB));
        const uint32_t exe = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr)));
        std::printf("raised sites: A=exe+0x%X B=exe+0x%X (system modules %u)\n", siteA - exe, siteB - exe,
                    static_cast<unsigned>(g_System.count));
    }

    // Overflow unmasked by a third party, on top of the logger's bits.
    void UnmaskOverflowToo()
    {
        uint16_t cw = 0;
        uint32_t mxcsr = 0;
        __asm
        {
            fnclex
            fnstcw cw
            stmxcsr mxcsr
        }
        cw = static_cast<uint16_t>(cw & ~0x0008);
        mxcsr &= ~(0x0008u | (0x0008u << kMxcsrMaskShift));
        __asm
        {
            fldcw cw
            ldmxcsr mxcsr
        }
    }

    void MaskOverflow()
    {
        uint16_t cw = 0;
        uint32_t mxcsr = 0;
        __asm
        {
            fnclex
            fnstcw cw
            stmxcsr mxcsr
        }
        cw = static_cast<uint16_t>(cw | 0x0008);
        mxcsr = (mxcsr | (0x0008u << kMxcsrMaskShift)) & ~0x003Fu;
        __asm
        {
            fldcw cw
            ldmxcsr mxcsr
        }
    }

    const double kHugeDouble = 1.0e300;
    const float kHugeFloat = 3.0e38f;

    // fstp m32 of 1e300 overflows; reported at the fwait.
    __declspec(noinline) void X87StoreOverflow(float* dst)
    {
        __asm
        {
            mov eax, dst
            fld qword ptr kHugeDouble
            fstp dword ptr [eax]
            fwait
        }
    }

    __declspec(noinline) void SseMultiplyOverflow(float* dst)
    {
        __asm
        {
            mov eax, dst
            movss xmm0, kHugeFloat
            mulss xmm0, xmm0
            movss [eax], xmm0
        }
    }

    // A pending bit outside the trap bits (here OE) must be masked for the
    // re-run too; otherwise the re-run faults again and the thread loops
    // forever (the CTest TIMEOUT would catch that).
    void TestThirdPartyOverflowTerminates()
    {
        float x = 0.0f;
        Arm();
        UnmaskOverflowToo();
        X87StoreOverflow(&x);
        const int x87Hits = g_Hits;
        const TrapReport x87Report = g_Last;
        MaskOverflow();

        float s = 0.0f;
        Arm();
        UnmaskOverflowToo();
        SseMultiplyOverflow(&s);
        const int sseHits = g_Hits;
        const TrapReport sseReport = g_Last;
        MaskOverflow();
        g_Live = 0;
        MaskCurrentThread();

        CHECK(x87Hits == 1);
        CHECK(x87Report.kind == Kind::X87 && (x87Report.flags & 0x08) != 0);
        CHECK(x87Report.result == RecoverResult::Recovered);
        CHECK(Bits(x) == 0x7F800000u);
        CHECK(X87StackEmpty());
        CHECK(sseHits == 1);
        CHECK(sseReport.kind == Kind::Sse && (sseReport.flags & 0x08) != 0);
        CHECK(Bits(s) == 0x7F800000u);
    }

    void TestCrtRaised()
    {
        volatile double zero = 0.0;
        volatile double minusOne = -1.0;
        volatile float zeroF = 0.0f;
        Arm();
        const double a = std::log(zero);
        const int logHits = g_Hits;
        const TrapReport logReport = g_Last;
        const DWORD logCode = g_LastCode;
        const bool maskedAfterLog = ThreadMasked();
        const double b = std::log(zero);
        const float c = std::log(static_cast<float>(zeroF));
        const double d = std::pow(zero, minusOne);
        const int totalHits = g_Hits;
        g_Live = 0;
        MaskCurrentThread();

        CHECK(logHits == 1);
        CHECK(logReport.kind == Kind::Raised);
        CHECK(logReport.result == RecoverResult::RaisedMasked);
        CHECK(logReport.flags == kX87ZeroDivide);
        CHECK(std::isinf(a) && std::signbit(a));
        CHECK(std::isinf(b) && std::signbit(b));
        CHECK(std::isinf(c) && std::signbit(c));
        CHECK(std::isinf(d) && !std::signbit(d));
        std::printf("crt log(0): code=0x%08lX eip=0x%08X result=%s maskedAfter=%d totalHits=%d\n", logCode,
                    logReport.eip, RecoverResultName(logReport.result), maskedAfterLog ? 1 : 0, totalHits);
    }

    // On the target thread every float code is taken, even with every trap
    // bit masked (the CRT's repeat raise looks exactly like that).
    void TestRaisedWhileMaskedIsTaken()
    {
        g_Hits = 0;
        g_Last = TrapReport();
        g_Live = 0;
        MaskCurrentThread();
        volatile bool caught = false;
        __try
        {
            RaiseException(STATUS_FLOAT_DIVIDE_BY_ZERO, 0, 0, nullptr);
        }
        __except (GetExceptionCode() == STATUS_FLOAT_DIVIDE_BY_ZERO ? EXCEPTION_EXECUTE_HANDLER
                                                                     : EXCEPTION_CONTINUE_SEARCH)
        {
            caught = true;
        }
        CHECK(!caught);
        CHECK(g_Hits == 1);
        CHECK(g_Last.kind == Kind::Raised);
        CHECK(g_Last.result == RecoverResult::RaisedMasked);
        CHECK(ThreadMasked());
    }

    void TestBelowEspRefused()
    {
        float r = 0.0f;
        int counter = 0;
        Arm();
        X87DivideBelowEspNonAdjacent(&r, &counter);
        CHECK(g_Hits == 1);
        CHECK(g_Last.kind == Kind::X87);
        CHECK(g_Last.result == RecoverResult::Unrecovered);
        CHECK(!g_Last.adjacent);
        CHECK(counter == 1);
        CHECK(Bits(r) == 0x3F800000u); // fdiv skipped: st0 stayed 1.0
        CHECK(X87StackEmpty());
        CHECK(ThreadMasked());
    }

    // A synthetic x87 divide-by-zero CONTEXT (no real trap) whose faulting
    // instruction is at `address` and reported at `eip`.
    void MakeX87Context(CONTEXT& c, uint32_t address, uint32_t eip, uint16_t fop)
    {
        std::memset(&c, 0, sizeof(c));
        c.ContextFlags = CONTEXT_FLOATING_POINT | CONTEXT_EXTENDED_REGISTERS;
        c.FloatSave.ControlWord = 0x037F & ~kX87ZeroDivide;
        c.FloatSave.StatusWord = kX87ErrorSummary | kX87ZeroDivide;
        c.FloatSave.ErrorOffset = address;
        c.Eip = eip;
        const uint32_t mxcsr = 0x1F80;
        std::memcpy(c.ExtendedRegisters + kFxsaveMxcsrOffset, &mxcsr, sizeof(mxcsr));
        std::memcpy(c.ExtendedRegisters + kFxsaveFopOffset, &fop, sizeof(fop));
    }

    // EIP moves back only for a decoded, FOP-matched, adjacent instruction;
    // unreadable code is checked with VirtualQuery, never probed by faulting.
    void TestInPlaceNeedsVerifiedDecode()
    {
        static RecoveryScratch noStub; // stub == nullptr: forces the fallback
        const int avBefore = g_AccessViolations;
        uint8_t* pages = static_cast<uint8_t*>(VirtualAlloc(nullptr, 8192, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
        OpenShimTest::Require(pages != nullptr, "VirtualAlloc");
        DWORD old = 0;
        OpenShimTest::Require(VirtualProtect(pages + 4096, 4096, PAGE_NOACCESS, &old) != 0, "VirtualProtect");
        uint8_t* fdivp = pages + 4096 - 2; // DE F9 ends exactly at the page end
        fdivp[0] = 0xDE;
        fdivp[1] = 0xF9;
        const uint32_t at = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(fdivp));
        CONTEXT c;
        TrapReport r;

        MakeX87Context(c, at, at + 2, 0x06F9);
        CHECK(Recover(0xC000008Eu, &c, noStub, r) == RecoverResult::RecoveredInPlace);
        CHECK(c.Eip == at);
        CHECK((c.FloatSave.ControlWord & kX87ZeroDivide) != 0);

        MakeX87Context(c, at, at + 2, 0x0123); // FOP names another instruction
        CHECK(Recover(0xC000008Eu, &c, noStub, r) == RecoverResult::Unrecovered);
        CHECK(c.Eip == at + 2);

        fdivp[0] = 0x90; // not x87: decode fails
        fdivp[1] = 0x90;
        MakeX87Context(c, at, at + 2, 0);
        CHECK(Recover(0xC000008Eu, &c, noStub, r) == RecoverResult::Unrecovered);
        CHECK(c.Eip == at + 2);

        const uint32_t noAccess = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(pages + 4096));
        MakeX87Context(c, noAccess, noAccess + 2, 0);
        CHECK(Recover(0xC000008Eu, &c, noStub, r) == RecoverResult::Unrecovered);
        MakeX87Context(c, 0x00001000u, 0x00001002u, 0);
        CHECK(Recover(0xC000008Eu, &c, noStub, r) == RecoverResult::Unrecovered);

        CHECK(g_AccessViolations == avBefore);
        VirtualFree(pages, 0, MEM_RELEASE);
    }
}

int main()
{
    std::setvbuf(stdout, nullptr, _IONBF, 0); // output survives a crash
    OpenShimTest::Require(AllocateRecoveryStub(g_Scratch), "stub allocation");
    g_System.Capture();
    g_Thread = GetCurrentThreadId();
    PVOID veh = AddVectoredExceptionHandler(1, Handler);
    OpenShimTest::Require(veh != nullptr, "AddVectoredExceptionHandler");

    TestX87DividePop();
    TestX87SkipWouldLoseResult();
    TestX87DivideMemoryNonAdjacent();
    TestX87DivideSib();
    TestX87InvalidStaysMasked();
    TestSseDivide();
    TestSseInvalid();
    TestMaskedIsUntouched();
    TestOtherThreadIgnored();
    TestCrtRaised();
    TestRaisedWhileMaskedIsTaken();
    TestBelowEspRefused();
    TestInPlaceNeedsVerifiedDecode();
    TestRaisedSitesPerCaller();
    TestThirdPartyOverflowTerminates();

    g_Live = 0;
    MaskCurrentThread();
    RemoveVectoredExceptionHandler(veh);
    if (OpenShimTest::ExitCode() == 0)
        std::printf("fp_trap_recovery_win32_tests passed\n");
    return OpenShimTest::ExitCode();
}
