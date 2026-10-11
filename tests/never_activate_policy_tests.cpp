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

    void TestZOrder()
    {
        Check(RewriteInsertAfter(kHwndTop, 0, true) == kHwndBottom, "HWND_TOP becomes HWND_BOTTOM");
        Check(RewriteInsertAfter(static_cast<std::uintptr_t>(-1), 0, true) == kHwndBottom, "HWND_TOPMOST becomes HWND_BOTTOM");
        Check(RewriteInsertAfter(static_cast<std::uintptr_t>(-2), 0, true) == kHwndBottom, "HWND_NOTOPMOST becomes HWND_BOTTOM");
        Check(RewriteInsertAfter(0x1234, 0, true) == kHwndBottom, "an arbitrary sibling becomes HWND_BOTTOM");
        Check(RewriteInsertAfter(kHwndBottom, 0, true) == kHwndBottom, "HWND_BOTTOM is kept");
        Check(RewriteInsertAfter(kHwndTop, kSwpNoZOrder, true) == kHwndTop, "SWP_NOZORDER leaves the argument alone");
        Check(RewriteInsertAfter(kHwndTop, 0, false) == kHwndTop, "child windows are left alone");
        Check(SetPosNeedsBottomPush(kSwpShowWindow | kSwpNoZOrder, true), "SHOWWINDOW+NOZORDER needs a push");
        Check(!SetPosNeedsBottomPush(kSwpShowWindow, true), "SHOWWINDOW alone is already rewritten");
        Check(!SetPosNeedsBottomPush(kSwpShowWindow | kSwpNoZOrder, false), "child windows need no push");
        Check((BottomPushFlags() & kSwpNoActivate) != 0, "bottom push never activates");
        Check((BottomPushFlags() & kSwpNoMove) != 0 && (BottomPushFlags() & kSwpNoSize) != 0, "bottom push keeps geometry");
        Check((BottomPushFlags() & kSwpNoZOrder) == 0, "bottom push changes z-order");
        Check(StyleExWithoutTopmost(0x08040008) == 0x08040000, "WS_EX_TOPMOST is stripped, other bits kept");
        Check(ShowCommandNeedsBottomPush(kSwShowNoActivate), "visible show needs a push");
        Check(ShowCommandNeedsBottomPush(kSwShowMinNoActive), "min-no-active show needs a push");
        Check(!ShowCommandNeedsBottomPush(kSwHide), "SW_HIDE needs no push");
    }

    void TestActiveWindow()
    {
        Check(ReportedActiveWindow(0, 0x500, true) == 0x500, "no active window reports the game window");
        Check(ReportedActiveWindow(0x77, 0x500, true) == 0x77, "a real active window is kept");
        Check(ReportedActiveWindow(0, 0x500, false) == 0, "a destroyed game window is not reported");
        Check(ReportedActiveWindow(0, 0, true) == 0, "no recorded game window reports nothing");
        Check(ShouldRecordGameWindow(false, false, false), "first window is recorded");
        Check(ShouldRecordGameWindow(true, false, true), "an Ogre window replaces a non-Ogre one");
        Check(!ShouldRecordGameWindow(true, true, true), "an Ogre window is never replaced");
        Check(!ShouldRecordGameWindow(true, false, false), "a later non-Ogre window does not replace");
    }
}

int main()
{
    TestShowCommands();
    TestWindowPosFlags();
    TestCreateStyle();
    TestSetFocus();
    TestZOrder();
    TestActiveWindow();
    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "never_activate_policy_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("never_activate_policy_tests: all checks passed\n");
    return 0;
}
