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
