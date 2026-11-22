#include "crash_av_classify.h"

#include "test_check.h"

namespace
{
    using BZROpenShim::CrashAvClassify::FaultFacts;
    using BZROpenShim::CrashAvClassify::IsCertainlyFatalAv;

    FaultFacts Av(uintptr_t kind, uintptr_t fault, uintptr_t eip, bool executable)
    {
        return FaultFacts{0xC0000005u, 2, kind, fault, eip, executable, false};
    }

    // Issue #942: a call through a dead vtable landed on ASCII "boos".
    void TestDeadVtableCallIsFatal()
    {
        CHECK(IsCertainlyFatalAv(Av(8, 0x736F6F62, 0x736F6F62, false)));
        CHECK(IsCertainlyFatalAv(Av(0, 0x736F6F62, 0x736F6F62, false)));
    }

    void TestExecuteFaultIsFatal()
    {
        CHECK(IsCertainlyFatalAv(Av(8, 0x00A00000, 0x00A00000, true)));
    }

    void TestEipEqualsFaultIsFatal()
    {
        CHECK(IsCertainlyFatalAv(Av(0, 0x10001000, 0x10001000, true)));
    }

    void TestNonExecutableEipIsFatal()
    {
        CHECK(IsCertainlyFatalAv(Av(0, 0x00000010, 0x00400000, false)));
        // Missing parameters still decide on eip alone.
        FaultFacts noParams = Av(0, 0, 0x12345678, false);
        noParams.numberParameters = 0;
        CHECK(IsCertainlyFatalAv(noParams));
    }

    // Probes and guarded reads fault with eip in real code; never early-dump.
    void TestReadWriteFaultsInCodeAreNotFatal()
    {
        CHECK(!IsCertainlyFatalAv(Av(0, 0x00000000, 0x0067CFC5, true)));
        CHECK(!IsCertainlyFatalAv(Av(0, 0xDEADBEEF, 0x0067CFC5, true)));
        CHECK(!IsCertainlyFatalAv(Av(1, 0x00000004, 0x76A01234, true)));
        FaultFacts noParams = Av(0, 0, 0x00401000, true);
        noParams.numberParameters = 0;
        CHECK(!IsCertainlyFatalAv(noParams));
    }

    void TestShimGuardSuppresses()
    {
        FaultFacts guarded = Av(8, 0x736F6F62, 0x736F6F62, false);
        guarded.shimGuardedCall = true;
        CHECK(!IsCertainlyFatalAv(guarded));
    }

    void TestOtherCodesAreNotClassified()
    {
        FaultFacts f = Av(8, 0x736F6F62, 0x736F6F62, false);
        f.code = 0xC000001Du;   // illegal instruction
        CHECK(!IsCertainlyFatalAv(f));
        f.code = 0xE06D7363u;   // C++ exception (Ogre)
        CHECK(!IsCertainlyFatalAv(f));
        f.code = 0x80000001u;   // guard page
        CHECK(!IsCertainlyFatalAv(f));
    }
}

int main()
{
    TestDeadVtableCallIsFatal();
    TestExecuteFaultIsFatal();
    TestEipEqualsFaultIsFatal();
    TestNonExecutableEipIsFatal();
    TestReadWriteFaultsInCodeAreNotFatal();
    TestShimGuardSuppresses();
    TestOtherCodesAreNotClassified();
    return OpenShimTest::ExitCode();
}
