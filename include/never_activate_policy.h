#pragma once
// never_activate_policy.h
// Pure decision rules for OPENSHIM_NEVER_ACTIVATE. No Windows calls, so
// tests/never_activate_policy_tests.cpp can exercise them directly.

#include <cstdint>

namespace BZROpenShim
{
    namespace NeverActivatePolicy
    {
        // ShowWindow command values (WinUser.h), spelled out to stay header-free.
        constexpr int kSwHide = 0;
        constexpr int kSwShowNormal = 1;
        constexpr int kSwShowMinimized = 2;
        constexpr int kSwShowMaximized = 3;
        constexpr int kSwShowNoActivate = 4;
        constexpr int kSwShow = 5;
        constexpr int kSwMinimize = 6;
        constexpr int kSwShowMinNoActive = 7;
        constexpr int kSwShowNa = 8;
        constexpr int kSwRestore = 9;
        constexpr int kSwShowDefault = 10;
        constexpr int kSwForceMinimize = 11;

        constexpr std::uint32_t kSwpNoActivate = 0x0010;

        constexpr std::uint32_t kWsMinimize = 0x20000000;
        constexpr std::uint32_t kWsVisible = 0x10000000;
        constexpr std::uint32_t kWsChild = 0x40000000;

        // Activating show commands become their non-activating equivalent;
        // SW_HIDE and the already-passive commands are unchanged.
        inline int NoActivateShowCommand(int cmd)
        {
            switch (cmd)
            {
            case kSwShowNormal: // == SW_NORMAL
            case kSwShow:
            case kSwRestore:
            case kSwShowDefault:
            case kSwShowMaximized: // == SW_MAXIMIZE
                return kSwShowNoActivate;
            case kSwShowMinimized:
            case kSwMinimize:
                return kSwShowMinNoActive;
            default:
                return cmd;
            }
        }

        // SetWindowPos always runs with SWP_NOACTIVATE (also covers
        // SWP_SHOWWINDOW and SWP_FRAMECHANGED, which otherwise activate).
        inline std::uint32_t NoActivateWindowPosFlags(std::uint32_t flags)
        {
            return flags | kSwpNoActivate;
        }

        // CreateWindowEx with WS_VISIBLE on a top-level window activates it.
        // Create it hidden and show it with SW_SHOWNOACTIVATE instead.
        inline bool ShouldDeferVisibleCreate(std::uint32_t style)
        {
            return (style & kWsVisible) != 0 && (style & kWsChild) == 0;
        }

        inline std::uint32_t StyleWithoutVisible(std::uint32_t style)
        {
            return style & ~kWsVisible;
        }

        inline int DeferredShowCommand(std::uint32_t style)
        {
            return (style & kWsMinimize) ? kSwShowMinNoActive : kSwShowNoActivate;
        }

        // SetFocus on a window whose top-level ancestor is not the foreground
        // window activates that top-level window. Block it; allow SetFocus(NULL)
        // and focus changes inside the window that already is the foreground
        // (which only happens when the user clicked it).
        inline bool ShouldBlockSetFocus(bool hasTarget, std::uintptr_t targetRoot, std::uintptr_t foreground)
        {
            return hasTarget && targetRoot != foreground;
        }

        // ---- z-order: never cover the user's foreground app ----------------
        // SW_SHOWNOACTIVATE / SWP_NOACTIVATE still place a window at the top
        // of the z-order, which paints it over a borderless fullscreen game.
        // Top-level windows are therefore always pushed to HWND_BOTTOM.
        constexpr std::uintptr_t kHwndBottom = 1;     // (HWND)1
        constexpr std::uintptr_t kHwndTop = 0;        // (HWND)0
        // HWND_NOTOPMOST (-2) also lands on top of every non-topmost window.

        constexpr std::uint32_t kSwpNoSize = 0x0001;
        constexpr std::uint32_t kSwpNoMove = 0x0002;
        constexpr std::uint32_t kSwpNoZOrder = 0x0004;
        constexpr std::uint32_t kSwpShowWindow = 0x0040;
        constexpr std::uint32_t kSwpNoOwnerZOrder = 0x0200;
        constexpr std::uint32_t kWsExTopmost = 0x00000008;

        // Flags for the follow-up "send to bottom" call.
        constexpr std::uint32_t BottomPushFlags()
        {
            return kSwpNoMove | kSwpNoSize | kSwpNoActivate | kSwpNoOwnerZOrder;
        }

        inline std::uint32_t StyleExWithoutTopmost(std::uint32_t exStyle)
        {
            return exStyle & ~kWsExTopmost;
        }

        // A ShowWindow command that makes the window visible needs a push.
        inline bool ShowCommandNeedsBottomPush(int mappedCmd)
        {
            return mappedCmd != kSwHide;
        }

        // SetWindowPos z-order rewrite: any insert-after other than HWND_BOTTOM
        // becomes HWND_BOTTOM, unless the caller asked to keep the z-order.
        inline std::uintptr_t RewriteInsertAfter(std::uintptr_t insertAfter, std::uint32_t flags, bool topLevel)
        {
            if (!topLevel || (flags & kSwpNoZOrder) != 0)
                return insertAfter;
            return kHwndBottom;
        }

        // SWP_SHOWWINDOW with SWP_NOZORDER can still surface a freshly shown window.
        inline bool SetPosNeedsBottomPush(std::uint32_t flags, bool topLevel)
        {
            return topLevel && (flags & kSwpShowWindow) != 0 && (flags & kSwpNoZOrder) != 0;
        }

        // ---- app-active gate -------------------------------------------------
        // The game's "app active" flag (exe global read by the main loop)
        // is seeded from GetActiveWindow() == gameWindow && !IsIconic(gameWindow)
        // and flipped by WM_ACTIVATEAPP. A never-activated window gets neither,
        // so the single-player sim idles. The exe's own GetActiveWindow import
        // reports the game window as the thread's active window instead.
        // Keyboard and raw mouse still arrive only through the real foreground
        // window (WM_INPUT is registered without RIDEV_INPUTSINK).
        inline std::uintptr_t ReportedActiveWindow(std::uintptr_t real, std::uintptr_t gameWindow, bool gameWindowValid)
        {
            if (real != 0 || gameWindow == 0 || !gameWindowValid)
                return real;
            return gameWindow;
        }

        // ---- WS_EX_NOACTIVATE: the OS must not activate the window either ----
        // Hooks stop the game from activating itself, but when the user's
        // foreground window closes or minimizes, Windows activates the next
        // top-level window in z-order, which is our bottom-most game window.
        // WS_EX_NOACTIVATE makes a top-level window ineligible.
        constexpr std::uint32_t kWsExToolWindow = 0x00000080;
        constexpr std::uint32_t kWsExAppWindow = 0x00040000;
        constexpr std::uint32_t kWsExNoActivate = 0x08000000;
        constexpr int kGwlExStyle = -20;

        // The extended style a top-level window must carry. Children are untouched.
        inline std::uint32_t ExStyleWithNoActivate(std::uint32_t exStyle, bool topLevel)
        {
            return topLevel ? (exStyle | kWsExNoActivate) : exStyle;
        }

        // WS_EX_NOACTIVATE drops the taskbar button; WS_EX_APPWINDOW restores
        // it. Only for windows that would have had one: unowned, not a tool window.
        inline bool ShouldAddAppWindow(std::uint32_t exStyle, bool topLevel, bool hasOwner)
        {
            return topLevel && !hasOwner && (exStyle & kWsExToolWindow) == 0;
        }

        // CreateWindowEx: NOACTIVATE (plus APPWINDOW where a button existed).
        inline std::uint32_t CreateExStyle(std::uint32_t exStyle, std::uint32_t style, bool hasOwner)
        {
            const bool topLevel = (style & kWsChild) == 0;
            const bool appWindow = ShouldAddAppWindow(exStyle, topLevel, hasOwner);
            std::uint32_t result = ExStyleWithNoActivate(exStyle, topLevel);
            return appWindow ? (result | kWsExAppWindow) : result;
        }

        // SetWindowLong: only GWL_EXSTYLE writes on a top-level window are rewritten,
        // so the bit cannot be cleared later. The APPWINDOW bit is left as written.
        inline std::uint32_t SetWindowLongValue(int index, std::uint32_t value, bool topLevel)
        {
            return index == kGwlExStyle ? ExStyleWithNoActivate(value, topLevel) : value;
        }

        // ---- intentional user click ------------------------------------------
        // A real click on the game window is the user asking for it: from then
        // on activation is allowed for the rest of the session. Posted clicks
        // (BZRWindowInput.ps1 uses PostMessage) must not count; they leave the
        // physical button state and the cursor untouched, so a click counts only
        // when the button is physically down AND the cursor is over the window.
        constexpr std::uint32_t kWmLButtonDown = 0x0201;
        constexpr std::uint32_t kWmRButtonDown = 0x0204;
        constexpr std::uint32_t kWmMButtonDown = 0x0207;
        constexpr std::uint32_t kWmNcLButtonDown = 0x00A1;
        constexpr std::uint32_t kWmNcRButtonDown = 0x00A4;
        constexpr std::uint32_t kWmNcMButtonDown = 0x00A7;

        inline bool IsButtonDownMessage(std::uint32_t msg)
        {
            return msg == kWmLButtonDown || msg == kWmRButtonDown || msg == kWmMButtonDown ||
                   msg == kWmNcLButtonDown || msg == kWmNcRButtonDown || msg == kWmNcMButtonDown;
        }

        inline bool IsUserClick(std::uint32_t msg, bool targetIsGameWindow, bool cursorInsideWindow, bool buttonPhysicallyDown)
        {
            return IsButtonDownMessage(msg) && targetIsGameWindow && cursorInsideWindow && buttonPhysicallyDown;
        }

        // Virtual key to poll for the physical state of a button-down message.
        inline int ButtonVirtualKey(std::uint32_t msg)
        {
            switch (msg)
            {
            case kWmLButtonDown:
            case kWmNcLButtonDown:
                return 0x01; // VK_LBUTTON
            case kWmRButtonDown:
            case kWmNcRButtonDown:
                return 0x02; // VK_RBUTTON
            case kWmMButtonDown:
            case kWmNcMButtonDown:
                return 0x04; // VK_MBUTTON
            default:
                return 0;
            }
        }

        // Once the user has clicked in, every suppression stands down.
        inline bool ShouldSuppress(bool userActivated)
        {
            return !userActivated;
        }

        // Which window is "the game window": prefer an Ogre-class window,
        // otherwise the first top-level window shown. Never replace an Ogre one.
        inline bool ShouldRecordGameWindow(bool currentIsSet, bool currentIsOgre, bool candidateIsOgre)
        {
            if (!currentIsSet)
                return true;
            return !currentIsOgre && candidateIsOgre;
        }
    }
}
