// satellite_view_limits.cpp
// BZR Open Shim - satellite view limits (max zoom-out and pan speed,
// SinglePlayer tier), split out of bzr_hooks.cpp. Its baselines are parsed
// by InitializeGlobalImprovementConfig there.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
    namespace Hooks
    {
        // --- Satellite view limits ---------------------------------------------
        //
        // Traced statically against the shipped GOG v2.2.301 executable. The two
        // zoom bounds are identified by the comparisons that enforce them:
        //   0x00587E68  comiss [sat+0x40],[0x008723F4] ; jbe -> clamp down,
        //               so 0x008723F4 is the MAXIMUM zoom
        //   0x00587EBA  comiss [0x00872400],[sat+0x40] ; jbe -> clamp up,
        //               so 0x00872400 is the MINIMUM zoom
        // Both sit in .rdata (0x00869000 + 0x7D218), so their pages are mapped
        // read-only and every write needs VirtualProtect. Pan speed at
        // 0x009C91D0 is ordinary .data and needs no such dance.
        //
        // Expressed as multipliers of whatever the build ships rather than as
        // absolute distances, so the setting keeps its meaning if a future patch
        // retunes the stock values.
        //
        // Gated to single player: a shim player who can pull further out than a
        // stock peer sees more of the map, which is the same reasoning that
        // keeps SatelliteVisibilityFix single-player only.
        constexpr uintptr_t kSatelliteMaxZoomAddr = 0x008723F4;
        constexpr uintptr_t kSatelliteMinZoomAddr = 0x00872400;
        constexpr uintptr_t kSatellitePanSpeedAddr = 0x009C91D0;
        constexpr float kSatelliteMultiplierMin = 0.25f;
        constexpr float kSatelliteMultiplierMax = 8.0f;

        float g_SatelliteZoomOutMultiplier = 1.0f;
        float g_SatelliteZoomOutMultiplierBaseline = 1.0f;
        float g_SatellitePanSpeedMultiplier = 1.0f;
        float g_SatellitePanSpeedMultiplierBaseline = 1.0f;
        static float g_SatelliteStockMaxZoom = 0.0f;
        static float g_SatelliteStockPanSpeed = 0.0f;
        static bool g_SatelliteStockCaptured = false;
        static bool g_SatelliteApplied = false;
        static bool g_SatelliteWriteFailureLogged = false;

        float ClampSatelliteMultiplier(float value)
        {
            if (!std::isfinite(value) || value <= 0.0f)
                return 1.0f;
            return (std::clamp)(value, kSatelliteMultiplierMin, kSatelliteMultiplierMax);
        }

        // Writes a float into a page the loader mapped read-only (.rdata).
        static bool WriteReadOnlyFloat(uintptr_t address, float value)
        {
            auto* target = reinterpret_cast<uint8_t*>(address);
            DWORD oldProtect = 0;
            if (!VirtualProtect(target, sizeof(float), PAGE_READWRITE, &oldProtect))
                return false;
            bool ok = true;
            __try
            {
                *reinterpret_cast<float*>(target) = value;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ok = false;
            }
            DWORD restoreProtect = 0;
            VirtualProtect(target, sizeof(float), oldProtect, &restoreProtect);
            return ok;
        }

        // Snapshot the shipped values before anything writes over them, so the
        // multipliers always compose against stock rather than against whatever
        // was applied last.
        static bool TryCaptureSatelliteStockValues()
        {
            if (g_SatelliteStockCaptured)
                return true;

            __try
            {
                const float maxZoom = *reinterpret_cast<const float*>(kSatelliteMaxZoomAddr);
                const float panSpeed = *reinterpret_cast<const float*>(kSatellitePanSpeedAddr);
                if (!std::isfinite(maxZoom) || maxZoom <= 0.0f ||
                    !std::isfinite(panSpeed) || panSpeed <= 0.0f)
                {
                    return false;
                }
                g_SatelliteStockMaxZoom = maxZoom;
                g_SatelliteStockPanSpeed = panSpeed;
                g_SatelliteStockCaptured = true;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void RefreshSatelliteViewState()
        {
            const bool singlePlayer = IsSinglePlayerSession();
            const float zoomOut =
                singlePlayer ? ClampSatelliteMultiplier(g_SatelliteZoomOutMultiplier) : 1.0f;
            const float panSpeed =
                singlePlayer ? ClampSatelliteMultiplier(g_SatellitePanSpeedMultiplier) : 1.0f;

            const bool wantStock =
                std::fabs(zoomOut - 1.0f) < 0.001f && std::fabs(panSpeed - 1.0f) < 0.001f;

            // Never touch the globals just to write their own stock values back:
            // until something has actually been applied there is nothing to undo.
            if (wantStock && !g_SatelliteApplied)
                return;
            if (!TryCaptureSatelliteStockValues())
                return;

            // Only the maximum moves. Raising it lets the player pull further
            // out; the minimum stays stock so the closest zoom is unchanged.
            bool ok = WriteReadOnlyFloat(kSatelliteMaxZoomAddr,
                                         g_SatelliteStockMaxZoom * zoomOut);
            __try
            {
                *reinterpret_cast<float*>(kSatellitePanSpeedAddr) =
                    g_SatelliteStockPanSpeed * panSpeed;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ok = false;
            }

            if (!ok)
            {
                if (!g_SatelliteWriteFailureLogged)
                {
                    g_SatelliteWriteFailureLogged = true;
                    Log(L"[SATELLITE] Could not write view limits at 0x%08X / 0x%08X\n",
                        static_cast<uint32_t>(kSatelliteMaxZoomAddr),
                        static_cast<uint32_t>(kSatellitePanSpeedAddr));
                }
                return;
            }

            g_SatelliteApplied = !wantStock;
        }

        void RevertSatelliteViewToBaseline()
        {
            g_SatelliteZoomOutMultiplier = g_SatelliteZoomOutMultiplierBaseline;
            g_SatellitePanSpeedMultiplier = g_SatellitePanSpeedMultiplierBaseline;
            RefreshSatelliteViewState();
        }
    }
}
