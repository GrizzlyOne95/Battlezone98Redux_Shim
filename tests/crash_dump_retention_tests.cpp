#include "crash_dump_retention.h"

#include "test_check.h"

namespace
{
    using BZROpenShim::CrashDumpRetention::IsCrashDumpName;
    using BZROpenShim::CrashDumpRetention::NewestKeeper;

    void TestNamePattern()
    {
        CHECK(IsCrashDumpName("openshim_crash_20261121_195800.dmp"));
        CHECK(IsCrashDumpName("OPENSHIM_CRASH_20261121_195800.DMP"));
        CHECK(!IsCrashDumpName("openshim_crash_20261121_195800.log"));
        CHECK(!IsCrashDumpName("openshim_crash.log"));
        CHECK(!IsCrashDumpName("openshim_crash_.dmp"));
        CHECK(!IsCrashDumpName("openshim_crash_test.dmp"));
        CHECK(!IsCrashDumpName("openshim_crash_zzzzzzzz_zzzzzz.dmp"));
        CHECK(!IsCrashDumpName("openshim_crash_20261121_19580.dmp"));
        CHECK(!IsCrashDumpName("openshim_crash_20261121-195800.dmp"));
        CHECK(!IsCrashDumpName("openshim_crash_20261121_195800.dmp.bak"));
        CHECK(!IsCrashDumpName("other_crash_20261121_195800.dmp"));
        CHECK(!IsCrashDumpName("battlezone98redux.dmp"));
        CHECK(!IsCrashDumpName("..\\openshim_crash_1.dmp"));
        CHECK(!IsCrashDumpName("OPENSH~1.DMP"));
        CHECK(!IsCrashDumpName(nullptr));
    }

    void TestKeepsNewestThree()
    {
        const char* names[] = {
            "openshim_crash_20261101_000000.dmp",
            "openshim_crash_20261120_120000.dmp",
            "openshim_crash_20261103_000000.dmp",
            "openshim_crash_20261121_000000.dmp",
            "openshim_crash_20261102_000000.dmp",
            "openshim_crash_20261121_000000.log",
            "openshim.log",
        };
        NewestKeeper keeper;
        for (const char* name : names)
            keeper.Offer(name);
        CHECK(keeper.ShouldDelete("openshim_crash_20261101_000000.dmp"));
        CHECK(keeper.ShouldDelete("openshim_crash_20261102_000000.dmp"));
        CHECK(!keeper.ShouldDelete("openshim_crash_20261103_000000.dmp"));
        CHECK(!keeper.ShouldDelete("openshim_crash_20261120_120000.dmp"));
        CHECK(!keeper.ShouldDelete("openshim_crash_20261121_000000.dmp"));
        // Files outside the pattern are never deleted.
        CHECK(!keeper.ShouldDelete("openshim_crash_20261121_000000.log"));
        CHECK(!keeper.ShouldDelete("openshim.log"));
    }

    void TestFewerThanThreeKeepsAll()
    {
        NewestKeeper keeper;
        keeper.Offer("openshim_crash_20261101_000000.dmp");
        keeper.Offer("openshim_crash_20261102_000000.dmp");
        CHECK(!keeper.ShouldDelete("openshim_crash_20261101_000000.dmp"));
        CHECK(!keeper.ShouldDelete("openshim_crash_20261102_000000.dmp"));
    }

    void TestDuplicatesAndCase()
    {
        NewestKeeper keeper;
        keeper.Offer("openshim_crash_20261101_000000.dmp");
        keeper.Offer("OPENSHIM_CRASH_20261101_000000.DMP");
        keeper.Offer("openshim_crash_20261102_000000.dmp");
        keeper.Offer("openshim_crash_20261103_000000.dmp");
        CHECK(!keeper.ShouldDelete("openshim_crash_20261101_000000.dmp"));
        keeper.Offer("openshim_crash_20261104_000000.dmp");
        CHECK(keeper.ShouldDelete("openshim_crash_20261101_000000.dmp"));
        CHECK(!keeper.ShouldDelete("openshim_crash_20261104_000000.dmp"));
    }

    void TestNonStampedNamesNeverCrowdOut()
    {
        NewestKeeper keeper;
        keeper.Offer("openshim_crash_test.dmp");
        keeper.Offer("openshim_crash_zzzz.dmp");
        keeper.Offer("openshim_crash_zzzzz.dmp");
        keeper.Offer("openshim_crash_20261101_000000.dmp");
        CHECK(!keeper.ShouldDelete("openshim_crash_20261101_000000.dmp"));
        CHECK(!keeper.ShouldDelete("openshim_crash_test.dmp"));
    }

    void TestProtectedDumpSurvivesClockGoingBack()
    {
        NewestKeeper keeper;
        const char* fresh = "openshim_crash_20250101_000000.dmp"; // clock went back
        keeper.Protect(fresh);
        keeper.Offer("openshim_crash_20261101_000000.dmp");
        keeper.Offer("openshim_crash_20261102_000000.dmp");
        keeper.Offer("openshim_crash_20261103_000000.dmp");
        keeper.Offer(fresh);
        CHECK(!keeper.ShouldDelete(fresh));
        CHECK(!keeper.ShouldDelete("openshim_crash_20261101_000000.dmp"));
    }

    void TestOrderIndependent()
    {
        NewestKeeper forward;
        NewestKeeper backward;
        const char* names[] = {
            "openshim_crash_20261101_000000.dmp", "openshim_crash_20261102_000000.dmp",
            "openshim_crash_20261103_000000.dmp", "openshim_crash_20261104_000000.dmp",
            "openshim_crash_20261105_000000.dmp",
        };
        for (int i = 0; i < 5; ++i)
            forward.Offer(names[i]);
        for (int i = 4; i >= 0; --i)
            backward.Offer(names[i]);
        for (const char* name : names)
            CHECK(forward.ShouldDelete(name) == backward.ShouldDelete(name));
        CHECK(forward.ShouldDelete(names[1]) && !forward.ShouldDelete(names[2]));
    }
}

int main()
{
    TestNamePattern();
    TestKeepsNewestThree();
    TestFewerThanThreeKeepsAll();
    TestDuplicatesAndCase();
    TestNonStampedNamesNeverCrowdOut();
    TestProtectedDumpSurvivesClockGoingBack();
    TestOrderIndependent();
    return OpenShimTest::ExitCode();
}
