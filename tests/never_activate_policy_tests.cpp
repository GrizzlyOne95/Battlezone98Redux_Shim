#include "never_activate_policy.h"

#include <cstdio>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::NeverActivatePolicy;

namespace
{
    void TestShowCommands()
    {
        Check(NoActivateShowCommand(kSwShowNormal) == kSwShowNoActivate, "SW_SHOWNORMAL does not activate");
        Check(NoActivateShowCommand(kSwShow) == kSwShowNoActivate, "SW_SHOW does not activate");
        Check(NoActivateShowCommand(kSwRestore) == kSwShowNoActivate, "SW_RESTORE does not activate");
        Check(NoActivateShowCommand(kSwShowDefault) == kSwShowNoActivate, "SW_SHOWDEFAULT does not activate");
        Check(NoActivateShowCommand(kSwShowMaximized) == kSwShowNoActivate, "SW_SHOWMAXIMIZED does not activate");
        Check(NoActivateShowCommand(kSwShowMinimized) == kSwShowMinNoActive, "SW_SHOWMINIMIZED maps to MINNOACTIVE");
        Check(NoActivateShowCommand(kSwMinimize) == kSwShowMinNoActive, "SW_MINIMIZE maps to MINNOACTIVE");
        Check(NoActivateShowCommand(kSwHide) == kSwHide, "SW_HIDE is unchanged");
        Check(NoActivateShowCommand(kSwShowNoActivate) == kSwShowNoActivate, "SW_SHOWNOACTIVATE is unchanged");
        Check(NoActivateShowCommand(kSwShowMinNoActive) == kSwShowMinNoActive, "SW_SHOWMINNOACTIVE is unchanged");
        Check(NoActivateShowCommand(kSwShowNa) == kSwShowNa, "SW_SHOWNA is unchanged");
        Check(NoActivateShowCommand(kSwForceMinimize) == kSwForceMinimize, "SW_FORCEMINIMIZE is unchanged");
    }

    void TestWindowPosFlags()
    {
        const std::uint32_t swpShowWindow = 0x0040;
        const std::uint32_t swpFrameChanged = 0x0020;
        const std::uint32_t flags = NoActivateWindowPosFlags(swpShowWindow | swpFrameChanged);
        Check((flags & kSwpNoActivate) != 0, "SWP_NOACTIVATE is added");
        Check((flags & swpShowWindow) != 0 && (flags & swpFrameChanged) != 0, "other flags are kept");
        Check(NoActivateWindowPosFlags(kSwpNoActivate) == kSwpNoActivate, "already passive is idempotent");
    }

    void TestCreateStyle()
    {
        const std::uint32_t reduxStyle = 0x16CA0000; // observed updateWindowStyle value
        Check(ShouldDeferVisibleCreate(reduxStyle), "visible top-level window is deferred");
        Check(!ShouldDeferVisibleCreate(StyleWithoutVisible(reduxStyle)), "hidden window is not deferred");
        Check((StyleWithoutVisible(reduxStyle) & kWsVisible) == 0, "WS_VISIBLE is stripped");
        Check((StyleWithoutVisible(reduxStyle) | kWsVisible) == reduxStyle, "no other style bit is lost");
        Check(!ShouldDeferVisibleCreate(kWsVisible | kWsChild), "visible child window is left alone");
        Check(!ShouldDeferVisibleCreate(0), "invisible window is left alone");
        Check(DeferredShowCommand(reduxStyle) == kSwShowNoActivate, "normal window is shown no-activate");
        Check(DeferredShowCommand(reduxStyle | kWsMinimize) == kSwShowMinNoActive, "minimized window is shown min-no-active");
    }

    void TestSetFocus()
    {
        Check(ShouldBlockSetFocus(true, 0x100, 0x200), "focus on a background top-level window is blocked");
        Check(ShouldBlockSetFocus(true, 0x100, 0), "focus with no foreground window is blocked");
        Check(!ShouldBlockSetFocus(true, 0x100, 0x100), "focus inside the foreground window passes");
        Check(!ShouldBlockSetFocus(false, 0, 0x200), "SetFocus(NULL) passes");
    }
}

int main()
{
    TestShowCommands();
    TestWindowPosFlags();
    TestCreateStyle();
    TestSetFocus();
    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "never_activate_policy_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("never_activate_policy_tests: all checks passed\n");
    return 0;
}
