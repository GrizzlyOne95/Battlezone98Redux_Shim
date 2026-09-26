// radar_layout.cpp
// BZR Open Shim - radar layout and radar size scale (Display tier) and the
// radar size bridge accessors, split out of bzr_hooks.cpp. Configured from
// there; shared helpers come from bzr_hooks_internal.h.
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
        // --- Radar layout (Display tier) ---------------------------------------
        // Redux keeps the radar in two independent coordinate systems, both
        // written by the layout builder at 0x00492EC0 (EXU calls it
        // BZR::Radar::RefreshLayout), with (sx, sy) the live UI scale:
        //
        //   projRadius  0x009173C0 = (int)(0x008E7754 * sx / 2)                  base 245
        //   projCentreX 0x008E7924 = (W*0x009173C4)/2 + (int)(0x008E7918*sx/2)   base 275
        //   projCentreY 0x008E7928 = screenHeight     - (int)(0x008E77B4*sy/2)   base 170
        //   backdropX   0x008E77A8 = (W*0x009173C4)/2 + (int)(0x009782A0*sx/2)   base 10
        //   backdropY   0x008E77AC = viewportH        - (int)(0x008E77B0*325*sy/2)
        //
        // Everything drawn on the radar -- the wireframe grid, blips, markers --
        // is projected through FUN_00493330, which reads only projRadius and
        // projCentre. The backdrop sprite (FUN_00493D40) reads only backdropX/Y
        // and the size scale at 0x008E77B0. Nothing ties the two together.
        //
        // Stock never needs a tie because 0x00492DC0 only ever installs two
        // hand-tuned, internally consistent presets: the normal one above, and a
        // 2/3-size variant flagged by 0x009173C4. There is no general scale path.
        // So any other scale desynchronises them -- the backdrop honours
        // 0x008E77B0 in both size and bottom anchoring while the projection
        // keeps the stock 275/170 bases. At 190% on a 2160p screen at UI scale 2
        // that leaves the grid 239 px left and 153 px below the backdrop centre.
        //
        // The builder has two call sites: 0x0049325F on mission load and
        // 0x0049405B inside CockpitRadar::Render, which runs every frame. A
        // correction applied at the load site alone is overwritten by the very
        // next frame, so this detours the builder itself and covers both.
        constexpr uintptr_t kRadarLayoutBuilderAddr = 0x00492EC0;
        constexpr size_t kRadarLayoutDetourLen = 6;
        constexpr uint8_t kRadarLayoutExpectedBytes[kRadarLayoutDetourLen] = {
            0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x10
        };
        constexpr uintptr_t kRadarProjRadiusAddr = 0x009173C0;
        constexpr uintptr_t kRadarProjCentreXAddr = 0x008E7924;
        constexpr uintptr_t kRadarProjCentreYAddr = 0x008E7928;
        constexpr uintptr_t kRadarBackdropXAddr = 0x008E77A8;
        constexpr uintptr_t kRadarBackdropYAddr = 0x008E77AC;
        constexpr uintptr_t kRadarSizeScaleAddr = 0x008E77B0;
        constexpr uintptr_t kRadarCompactModeAddr = 0x009173C4;
        constexpr uintptr_t kRadarUiScaleXAddr = 0x02BF041C;
        constexpr uintptr_t kRadarUiScaleYAddr = 0x02BF0420;
        // Stock normal-preset bases, from the `param_1 != 2` branch of
        // 0x00492DC0. Read as constants rather than from the live globals
        // because a scale provider may already have scaled 0x008E7754 in place;
        // deriving from the stock bases keeps this idempotent.
        constexpr double kRadarStockProjRadiusBase = 245.0;
        constexpr double kRadarStockProjCentreXBase = 275.0;
        constexpr double kRadarStockProjCentreYBase = 170.0;
        constexpr double kRadarStockBackdropXBase = 10.0;
        constexpr double kRadarStockBackdropYBase = 325.0;
        constexpr float kRadarScaleMin = 0.05f;
        constexpr float kRadarScaleMax = 16.0f;

        using FnRadarRefreshLayout = void(__cdecl*)(int screenHeight);
        static FnRadarRefreshLayout g_BzrFn_RadarRefreshLayoutOriginal = nullptr;
        static InlineDetour32 g_RadarLayoutDetour = {};
        bool g_RadarLayoutHookInstalled = false;
        static bool g_RadarLayoutMismatchLogged = false;
        static float g_RadarLayoutLoggedScale = 0.0f;

        // Re-anchors the projection to the backdrop the builder just laid out.
        // The backdrop already honours the scale in both size and bottom
        // anchoring, and the centre-to-anchor vector scales linearly whether the
        // sprite's anchor is its top-left or its middle, so this holds without
        // depending on which.
        static void ApplyRadarScaleGeometry(int screenHeight)
        {
            __try
            {
                // The compact preset ships its own consistent base set.
                if (*reinterpret_cast<const int*>(kRadarCompactModeAddr) != 0)
                    return;

                const float scale = *reinterpret_cast<const float*>(kRadarSizeScaleAddr);
                if (!(scale > kRadarScaleMin) || !(scale < kRadarScaleMax))
                    return;
                // The stock preset is already internally consistent.
                if (std::fabs(scale - 1.0f) < 1.0e-4f)
                    return;

                const double uiScaleX = *reinterpret_cast<const float*>(kRadarUiScaleXAddr);
                const double uiScaleY = *reinterpret_cast<const float*>(kRadarUiScaleYAddr);
                if (!(uiScaleX > 0.05) || !(uiScaleY > 0.05))
                    return;

                const int viewportHeight =
                    *reinterpret_cast<const int*>(kScrapPilotHudViewportHeightAddr);
                if (viewportHeight <= 0)
                    return;

                // The scale-1 reference layout, rebuilt exactly as the stock
                // builder would. Normal mode means 0x009173C4 is 0, so the
                // viewport term in the two x expressions drops out.
                const int radiusRef =
                    static_cast<int>(kRadarStockProjRadiusBase * uiScaleX / 2.0);
                const int centreXRef =
                    static_cast<int>(kRadarStockProjCentreXBase * uiScaleX / 2.0);
                const int centreYRef = screenHeight -
                    static_cast<int>(kRadarStockProjCentreYBase * uiScaleY / 2.0);
                const int backdropXRef =
                    static_cast<int>(kRadarStockBackdropXBase * uiScaleX / 2.0);
                const int backdropYRef = viewportHeight -
                    static_cast<int>(kRadarStockBackdropYBase * uiScaleY / 2.0);

                const int backdropX = *reinterpret_cast<const int*>(kRadarBackdropXAddr);
                const int backdropY = *reinterpret_cast<const int*>(kRadarBackdropYAddr);

                const int radius =
                    static_cast<int>(std::lround(scale * radiusRef));
                const int centreX = backdropX +
                    static_cast<int>(std::lround(scale * (centreXRef - backdropXRef)));
                const int centreY = backdropY +
                    static_cast<int>(std::lround(scale * (centreYRef - backdropYRef)));

                *reinterpret_cast<int*>(kRadarProjRadiusAddr) = radius;
                *reinterpret_cast<int*>(kRadarProjCentreXAddr) = centreX;
                *reinterpret_cast<int*>(kRadarProjCentreYAddr) = centreY;

                // Once per scale change: the builder runs every frame.
                if (g_RadarLayoutLoggedScale != scale)
                {
                    g_RadarLayoutLoggedScale = scale;
                    Log(L"[RADAR] scale=%.4f ui=%.2f/%.2f backdrop=(%d,%d) "
                        L"centre=(%d,%d) radius=%d (stock centre would be (%d,%d) r=%d)\n",
                        static_cast<double>(scale),
                        uiScaleX,
                        uiScaleY,
                        backdropX,
                        backdropY,
                        centreX,
                        centreY,
                        radius,
                        centreXRef,
                        centreYRef,
                        radiusRef);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        static void __cdecl RadarRefreshLayoutHook(int screenHeight)
        {
            if (g_BzrFn_RadarRefreshLayoutOriginal)
                g_BzrFn_RadarRefreshLayoutOriginal(screenHeight);
            ApplyRadarScaleGeometry(screenHeight);
        }

        void InstallRadarLayoutHookIfPossible()
        {
            if (g_RadarLayoutHookInstalled)
                return;

            if (!ExpectedBytesMatchAt(kRadarLayoutBuilderAddr,
                                      kRadarLayoutExpectedBytes,
                                      sizeof(kRadarLayoutExpectedBytes)))
            {
                if (!g_RadarLayoutMismatchLogged)
                {
                    g_RadarLayoutMismatchLogged = true;
                    Log(L"[RADAR] Layout builder entry at 0x%08X does not match; "
                        L"radar scale correction stands down\n",
                        static_cast<uint32_t>(kRadarLayoutBuilderAddr));
                }
                return;
            }

            if (!InstallInlineDetour32(g_RadarLayoutDetour,
                                       kRadarLayoutBuilderAddr,
                                       reinterpret_cast<void*>(RadarRefreshLayoutHook),
                                       kRadarLayoutDetourLen,
                                       kRadarLayoutExpectedBytes,
                                       sizeof(kRadarLayoutExpectedBytes)))
            {
                if (!g_RadarLayoutMismatchLogged)
                {
                    g_RadarLayoutMismatchLogged = true;
                    Log(L"[RADAR] Failed installing the radar layout hook\n");
                }
                return;
            }

            g_BzrFn_RadarRefreshLayoutOriginal =
                reinterpret_cast<FnRadarRefreshLayout>(g_RadarLayoutDetour.trampoline);
            g_RadarLayoutHookInstalled = true;
            Log(L"[RADAR] Layout hook installed at 0x%08X; projection now tracks "
                L"the backdrop at any radar scale\n",
                static_cast<uint32_t>(kRadarLayoutBuilderAddr));
        }

        // --- Radar size scale: the player-facing setting ------------------------
        //
        // The geometry correction above already exists and is the hard half: it
        // re-anchors the projection to the backdrop at any scale, deriving its
        // reference layout from the stock bases rather than from the live
        // globals, which is what keeps it idempotent across repeated applies and
        // mission loads. What was missing is anything that actually SETS the
        // scale: nothing in the shim ever wrote 0x008E77B0, so the correction
        // only did something when an external provider (EXU) scaled the radar.
        // This is that provider, so the feature stands on its own.
        //
        // Local HUD geometry only, so it is not multiplayer-gated -- it reveals
        // nothing a stock peer cannot see.
        float g_RadarSizeScale = 1.0f;
        float g_RadarSizeScaleBaseline = 1.0f;
        static bool g_RadarSizeScaleWriteFailureLogged = false;
        static bool g_RadarSizeScaleWriteRefusedLogged = false;

        float ClampRadarSizeScaleSetting(float scale)
        {
            if (!std::isfinite(scale) || scale <= 0.0f)
                return 1.0f;
            // Stay inside the window ApplyRadarScaleGeometry is willing to act
            // on; a value it rejects would scale the backdrop while leaving the
            // projection stock, which looks like a broken radar.
            return (std::clamp)(scale, 0.25f, 4.0f);
        }

        void RefreshRadarSizeScaleState()
        {
            const float desired = ClampRadarSizeScaleSetting(g_RadarSizeScale);
            g_RadarSizeScale = desired;

            // At stock, write nothing at all. The shim is not the only writer of
            // this global -- a mission script can scale the radar through the EXU
            // bridge -- so publishing our own 1.0 here would silently stomp a
            // scripted value with "stock" merely because the ini key is absent.
            // Absent key means "leave the radar alone", not "force it to 1.0".
            if (std::fabs(desired - 1.0f) < 0.001f)
                return;

            // The correction hook has to be live before the scale is visible,
            // otherwise the backdrop scales and the projection does not.
            InstallRadarLayoutHookIfPossible();

            // The byte-guarded builder is also the identity proof for the
            // neighbouring globals. Without it 0x008E77B0 is just an address:
            // writing it on a build where the guard failed scales whatever
            // lives there, and the SEH below only catches an unmapped page.
            if (!g_RadarLayoutHookInstalled)
            {
                if (!g_RadarSizeScaleWriteRefusedLogged)
                {
                    g_RadarSizeScaleWriteRefusedLogged = true;
                    Log(L"[RADAR] size scale %.3f not written: the layout hook is not installed on this build\n",
                        static_cast<double>(desired));
                }
                return;
            }

            __try
            {
                *reinterpret_cast<float*>(kRadarSizeScaleAddr) = desired;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                if (!g_RadarSizeScaleWriteFailureLogged)
                {
                    g_RadarSizeScaleWriteFailureLogged = true;
                    Log(L"[RADAR] Could not write the size scale at 0x%08X\n",
                        static_cast<uint32_t>(kRadarSizeScaleAddr));
                }
            }
        }

        void RevertRadarSizeScaleToBaseline()
        {
            g_RadarSizeScale = g_RadarSizeScaleBaseline;
            RefreshRadarSizeScaleState();
        }
    }

    using namespace Hooks;

    float GetRadarSizeScaleFromBridge()
    {
        // Until the byte-guarded layout hook has identified this build, the
        // engine global is only an address; answer with the shim's own value.
        if (!g_RadarLayoutHookInstalled)
            return g_RadarSizeScale;
        __try
        {
            const float current = *reinterpret_cast<const float*>(kRadarSizeScaleAddr);
            return std::isfinite(current) && current > 0.0f
                ? current
                : g_RadarSizeScale;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return g_RadarSizeScale;
        }
    }

    bool SetRadarSizeScaleFromBridge(float scale)
    {
        if (!std::isfinite(scale) || scale <= 0.0f)
            return false;

        const float clamped = ClampRadarSizeScaleSetting(scale);
        InstallRadarLayoutHookIfPossible();
        // Same identity rule as RefreshRadarSizeScaleState: no verified
        // builder, no write. The shim's own value is left alone too, so a
        // later read does not claim a scale that never reached the engine.
        if (!g_RadarLayoutHookInstalled)
        {
            Log(L"[MISSIONHOOK] radar size requested=%.3f refused: the layout hook is not installed on this build\n",
                static_cast<double>(scale));
            return false;
        }
        g_RadarSizeScale = clamped;
        __try
        {
            *reinterpret_cast<float*>(kRadarSizeScaleAddr) = clamped;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
        Log(L"[MISSIONHOOK] radar size requested=%.3f applied=%.3f\n",
            static_cast<double>(scale), static_cast<double>(clamped));
        return true;
    }
}
