// window_unclamp.cpp
// BZR Open Shim - OPENSHIM_UNCLAMP_WINDOW: let a windowed test client open at
// its Ogre.cfg size on a desktop smaller than that.
#include "bzr_hooks.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include <Windows.h>

namespace BZROpenShim
{
    namespace
    {
        // Ogre's windowed D3D render window shrinks itself to the monitor's work
        // area (GetMonitorInfo rcWork) before CreateWindowEx. Windows itself
        // does not clamp an oversized window. A disconnected remote-desktop
        // session runs a 640x480 virtual display, and that display refuses mode
        // changes, so a headless capture run (OPENSHIM_FRAME_CAPTURE) would
        // render the menus at about 624x393 whatever Ogre.cfg asks for.
        //
        // With the flag set, GetMonitorInfoA/W report a work area and monitor
        // rect at least kMinWidth x kMinHeight, so the window keeps its
        // configured size. Test-only and process-wide; off by default, and with
        // the flag unset nothing is patched.
        constexpr LONG kMinWidth = 7680;
        constexpr LONG kMinHeight = 4320;

        // mov edi,edi; push ebp; mov ebp,esp: the hot-patch prologue both
        // exports have in the 32-bit user32.
        const uint8_t kPrologue[] = {0x8B, 0xFF, 0x55, 0x8B, 0xEC};

        using FnGetMonitorInfo = BOOL(WINAPI*)(HMONITOR, LPMONITORINFO);
        InlineDetour32 s_detourA;
        InlineDetour32 s_detourW;
        FnGetMonitorInfo volatile s_realA = nullptr;
        FnGetMonitorInfo volatile s_realW = nullptr;

        void Grow(RECT& r)
        {
            if (r.right - r.left < kMinWidth)
                r.right = r.left + kMinWidth;
            if (r.bottom - r.top < kMinHeight)
                r.bottom = r.top + kMinHeight;
        }

        BOOL Unclamped(FnGetMonitorInfo real, HMONITOR monitor, LPMONITORINFO info)
        {
            const BOOL ok = real(monitor, info);
            if (ok && info)
            {
                Grow(info->rcMonitor);
                Grow(info->rcWork);
            }
            return ok;
        }

        BOOL WINAPI GetMonitorInfoAHook(HMONITOR monitor, LPMONITORINFO info)
        {
            return Unclamped(s_realA, monitor, info);
        }

        BOOL WINAPI GetMonitorInfoWHook(HMONITOR monitor, LPMONITORINFO info)
        {
            return Unclamped(s_realW, monitor, info);
        }

        bool Detour(InlineDetour32& detour, HMODULE user32, const char* name, void* hook,
                    FnGetMonitorInfo volatile* real)
        {
            const auto target = reinterpret_cast<uintptr_t>(GetProcAddress(user32, name));
            return target && InstallInlineDetour32(detour, target, hook, sizeof(kPrologue), kPrologue,
                                                   sizeof(kPrologue), reinterpret_cast<void* volatile*>(real));
        }
    }

    void InstallWindowUnclampIfRequested()
    {
        static bool attempted = false;
        if (attempted || !EnvFlagEnabled("OPENSHIM_UNCLAMP_WINDOW"))
            return;
        attempted = true;

        const HMODULE user32 = GetModuleHandleW(L"user32.dll");
        const bool a = user32 && Detour(s_detourA, user32, "GetMonitorInfoA", &GetMonitorInfoAHook, &s_realA);
        const bool w = user32 && Detour(s_detourW, user32, "GetMonitorInfoW", &GetMonitorInfoWHook, &s_realW);
        Log(L"[UNCLAMP-WINDOW] GetMonitorInfoA %hs, GetMonitorInfoW %hs\n",
            a ? "hooked" : "unchanged", w ? "hooked" : "unchanged");
    }
}
