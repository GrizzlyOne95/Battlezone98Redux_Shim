// DX11: open the game window on the primary monitor.
//
// Why: Ogre 1.10's D3D11RenderWindowHwnd::create defaults the window's left
// and top to INT_MAX when the game passes no position (it never does), then
// asks MonitorFromPoint((INT_MAX, INT_MAX), MONITOR_DEFAULTTONEAREST) which
// monitor to use. That is the monitor furthest right and down, so on a
// multi-monitor desk the DX11 game opens on a side monitor while DX9 (which
// stores the monitor in "Rendering Device=Monitor-N-...") opens on the primary.
//
// What: RenderSystem_Direct3D11.dll's user32 import of MonitorFromPoint is
// wrapped. A call with exactly that (INT_MAX, INT_MAX) sentinel returns the
// primary monitor; every other call is forwarded unchanged. Fullscreen uses
// the same monitor, so it moves to the primary monitor too.
//
// Config: [Graphics] D3D11PrimaryMonitor (default 1);
// OPENSHIM_DISABLE_D3D11_PRIMARY_MONITOR=1 turns it off.
#include "bool_token.h"
#include "d3d11_primary_monitor.h"
#include "diagnostic_switch.h"
#include "iat_patch.h"
#include "shim_log.h"

#include <Windows.h>
#include <process.h>

#include <atomic>
#include <climits>
#include <string>

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "D3D11PrimaryMonitor";
        // The renderer loads seconds before Root::initialise creates the
        // window; poll often enough to win that comfortably.
        constexpr unsigned kDiscoveryAttempts = 3000;  // 3000 x 20 ms
        constexpr DWORD kDiscoverySleepMs = 20;

        using FnMonitorFromPoint = HMONITOR(WINAPI*)(POINT, DWORD);
        FnMonitorFromPoint g_RealMonitorFromPoint = nullptr;
        std::atomic<bool> g_LoggedRedirect{false};
        uintptr_t g_DiscoveryThread = 0;

        HMONITOR WINAPI HookMonitorFromPoint(POINT pt, DWORD flags)
        {
            if (pt.x == INT_MAX && pt.y == INT_MAX)
            {
                HMONITOR primary = g_RealMonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
                if (!g_LoggedRedirect.exchange(true))
                    LogShimA(LogLevel::Info, kComponent,
                             "[DX11 Monitor] window had no position; placed on the primary monitor");
                return primary;
            }
            return g_RealMonitorFromPoint(pt, flags);
        }

        unsigned __stdcall DiscoveryThreadProc(void*)
        {
            for (unsigned attempt = 0; attempt < kDiscoveryAttempts; ++attempt)
            {
                HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
                if (renderer)
                {
                    IatPatch::WaitForModuleLoadToFinish(renderer, nullptr);
                    for (unsigned retry = 0; retry < 20; ++retry)
                    {
                        const auto result = IatPatch::PatchImport(
                            renderer, "user32.dll", "MonitorFromPoint",
                            reinterpret_cast<void*>(&HookMonitorFromPoint),
                            reinterpret_cast<void**>(&g_RealMonitorFromPoint));
                        if (result == IatPatch::Result::Patched)
                        {
                            LogShimA(LogLevel::Info, kComponent,
                                     "[DX11 Monitor] installed: an unpositioned DX11 window opens on the primary monitor");
                            return 0;
                        }
                        if (result == IatPatch::Result::NotFound)
                        {
                            LogShimA(LogLevel::Warn, kComponent,
                                     "[DX11 Monitor] renderer has no user32 MonitorFromPoint import; not installed");
                            return 0;
                        }
                        Sleep(50);
                    }
                    LogShimA(LogLevel::Warn, kComponent,
                             "[DX11 Monitor] could not write the renderer's MonitorFromPoint import; not installed");
                    return 0;
                }
                Sleep(kDiscoverySleepMs);
            }
            return 0;  // DX9, or the renderer never loaded: nothing to do.
        }
    }

    void InitializeD3D11PrimaryMonitor()
    {
        if (g_DiscoveryThread)
            return;
        char value[16] = {};
        const DWORD n = GetEnvironmentVariableA("OPENSHIM_DISABLE_D3D11_PRIMARY_MONITOR", value,
                                                static_cast<DWORD>(sizeof(value)));
        if (n > 0 && n < sizeof(value) && BoolToken::IsTruthy(value, n))
            return;
        const std::string ini = DiagnosticSwitch::OpenShimIniPath();
        if (GetPrivateProfileIntA("Graphics", "D3D11PrimaryMonitor", 1, ini.c_str()) == 0)
            return;
        g_DiscoveryThread = _beginthreadex(nullptr, 0, DiscoveryThreadProc, nullptr, 0, nullptr);
    }
}
