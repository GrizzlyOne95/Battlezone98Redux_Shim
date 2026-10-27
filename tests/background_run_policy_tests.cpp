#include "background_run_policy.h"

#include <cstdio>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::BackgroundRunPolicy;

namespace
{
    void TestActiveGate()
    {
        Check(Active(true, false, false), "enabled windowed single-player is active");
        Check(!Active(false, false, false), "disabled toggle is inert");
        Check(!Active(true, true, false), "multiplayer is inert");
        Check(!Active(true, false, true), "fullscreen is inert");
    }

    void TestSwallow()
    {
        Check(ShouldSwallowMessage(true, kWmActivateApp, 0), "deactivate is swallowed");
        Check(!ShouldSwallowMessage(true, kWmActivateApp, 1), "activate passes through");
        Check(!ShouldSwallowMessage(true, 0x0005, 0), "other messages pass through");
        Check(!ShouldSwallowMessage(false, kWmActivateApp, 0), "inactive passes through");
        Check(ShouldSwallowMessage(true, kWmActivate, 0), "WA_INACTIVE is swallowed");
        Check(ShouldSwallowMessage(true, kWmActivate, 0x00010000u), "WA_INACTIVE while minimized is swallowed");
        Check(!ShouldSwallowMessage(true, kWmActivate, 1), "WA_ACTIVE passes through");
        Check(!ShouldSwallowMessage(true, kWmActivate, 2), "WA_CLICKACTIVE passes through");
        Check(!ShouldSwallowMessage(false, kWmActivate, 0), "WA_INACTIVE passes through when off");
    }

    void TestForceFlag()
    {
        Check(ShouldForceActiveFlag(true, 0, false), "flag forced on at init");
        Check(!ShouldForceActiveFlag(true, 1, false), "already on is left alone");
        Check(!ShouldForceActiveFlag(true, 0, true), "minimized window is not forced");
        Check(!ShouldForceActiveFlag(false, 0, false), "inactive never forces");
    }

    void TestCursorSuppression()
    {
        Check(ShouldSuppressCursorCall(true, true, false), "background cursor calls suppressed");
        Check(!ShouldSuppressCursorCall(true, true, true), "foreground passes through");
        Check(!ShouldSuppressCursorCall(true, false, false), "unknown window passes through");
        Check(!ShouldSuppressCursorCall(false, true, false), "disabled passes through");
    }
}

int main()
{
    TestActiveGate();
    TestSwallow();
    TestForceFlag();
    TestCursorSuppression();
    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "background_run_policy_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("background_run_policy_tests: all checks passed\n");
    return 0;
}
