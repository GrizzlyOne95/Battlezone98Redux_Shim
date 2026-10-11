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
    }
}
