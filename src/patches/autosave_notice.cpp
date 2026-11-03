// autosave_notice.cpp
// BZR Open Shim - "Game autosaved." HUD notice
//
// Copyright (C) 2025-2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Draws a dark translucent panel with centred light-green text at the bottom
// of the HUD for a few seconds after a successful autosave, using the stock
// HUD primitives, so it needs neither EXU nor an Ogre overlay.
//
// Evidence (decompile functions named FUN_<address>):
//   FUN_005c6f70  scrap/pilot gauge draw, run each gameplay HUD frame; it
//                 prints through FUN_004c0100 with DAT_00917580 (pane
//                 buffer), DAT_00917550 (text style), DAT_0091755c (colour).
//   FUN_004c0100  cdecl text draw, 12 stack args: buffer, x, y, &w, &h, text,
//                 style, colour, fillColour (-1 = none), fillMode, alignX
//                 (1 = centre on x), alignY (0 = y is the top). It stores the
//                 colour into the style's first dword (FUN_00689950), and on
//                 return *w/*h hold the right/bottom edge, not the size.
//   FUN_00689ab0  cdecl (style, text, &w, &h) text measure (UiTextMeasure).
//   FUN_0068afb0  HudFillRect cdecl (buffer, x1, y1, x2, y2, colour, mode);
//                 FUN_0068ac50 leaves the colour, alpha included, untouched
//                 in mode 0.
//   DAT_00920ef4  ambient sprite depth; FUN_004c0100 adds 0.01 to it around
//                 its own background fill so the fill sits behind the text.

#include "autosave_notice.h"
#include "autosave_notice_layout.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <atomic>
#include <cstdint>

namespace BZROpenShim::AutoSaveNotice
{
    namespace
    {
        using TextFn = void(__cdecl*)(void*, int, int, float*, float*, const char*, void*,
                                      uint32_t, int, int, int, int);
        using MeasureFn = void(__cdecl*)(void*, const char*, float*, float*);
        using FillFn = void(__cdecl*)(void*, int, int, int, int, uint32_t, int);
        using GaugeFn = void(__fastcall*)(void*, void*);

        constexpr ULONGLONG kShowMs = 3000;
        constexpr char kText[] = "Game autosaved.";
        // ARGB: black at alpha 0.55, and the old overlay's (0.82, 1, 0.82).
        constexpr uint32_t kPanelColor = 0x8C000000u;
        constexpr uint32_t kTextColor = 0xFFD1FFD1u;
        constexpr float kBackingZStep = 0.01f;

        struct Addresses
        {
            uint32_t gauge = 0, text = 0, measure = 0, fill = 0;
            uint32_t viewportWidth = 0, viewportHeight = 0;
            uint32_t spriteZ = 0, style = 0, pane = 0;
        };

        Addresses g_addr;
        InlineDetour32 g_detour;
        void* volatile g_trampoline = nullptr;
        int g_state = 0;                       // 0 untried, 1 installed, -1 unavailable
        // 0 = not showing, kPending = shown but not drawn yet; the timer starts on
        // the first frame that draws it, so a pause or hidden HUD does not eat it.
        constexpr ULONGLONG kPending = 1;
        std::atomic<ULONGLONG> g_expiresAt{0};
        std::atomic<bool> g_drawFaulted{false};

        // Plain data only: this holds the __try, so nothing here may need
        // unwinding.
        void DrawNotice() noexcept
        {
            float savedZ = 0.0f;
            bool zRaised = false;
            uint32_t* styleColor = nullptr;
            uint32_t savedColor = 0;
            bool colorChanged = false;
            __try
            {
                void* const pane = *reinterpret_cast<void* const*>(g_addr.pane);
                void* const style = *reinterpret_cast<void* const*>(g_addr.style);
                if (!pane || !style)
                    return;
                const int viewW = *reinterpret_cast<const int*>(g_addr.viewportWidth);
                const int viewH = *reinterpret_cast<const int*>(g_addr.viewportHeight);

                float textW = 0.0f, textH = 0.0f;
                reinterpret_cast<MeasureFn>(g_addr.measure)(style, kText, &textW, &textH);

                Layout layout;
                if (!ComputeLayout(viewW, viewH, textW, textH, layout))
                    return;

                float* const z = reinterpret_cast<float*>(g_addr.spriteZ);
                savedZ = *z;
                *z = savedZ + kBackingZStep;
                zRaised = true;
                reinterpret_cast<FillFn>(g_addr.fill)(
                    pane, layout.x1, layout.y1, layout.x2, layout.y2, kPanelColor, 0);
                *z = savedZ;
                zRaised = false;

                // The text call writes its colour into the shared style, so put
                // the previous one back for whoever draws next.
                styleColor = static_cast<uint32_t*>(style);
                savedColor = *styleColor;
                colorChanged = true;
                float edgeX = 0.0f, edgeY = 0.0f;
                reinterpret_cast<TextFn>(g_addr.text)(
                    pane, layout.textCentreX, layout.textTop, &edgeX, &edgeY,
                    kText, style, kTextColor, -1, 0, 1, 0);
                *styleColor = savedColor;
                colorChanged = false;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_drawFaulted.store(true, std::memory_order_relaxed);
                g_expiresAt.store(0, std::memory_order_relaxed);
                __try
                {
                    if (zRaised)
                        *reinterpret_cast<float*>(g_addr.spriteZ) = savedZ;
                    if (colorChanged)
                        *styleColor = savedColor;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }
        }

        void __fastcall GaugeHook(void* self, void* edx)
        {
            const auto original = reinterpret_cast<GaugeFn>(g_trampoline);
            if (!original)
                return;
            original(self, edx);

            ULONGLONG expires = g_expiresAt.load(std::memory_order_relaxed);
            if (expires == 0 || g_drawFaulted.load(std::memory_order_relaxed))
                return;
            if (expires == kPending)
            {
                expires = GetTickCount64() + kShowMs;
                g_expiresAt.store(expires, std::memory_order_relaxed);
            }
            if (GetTickCount64() >= expires)
            {
                g_expiresAt.store(0, std::memory_order_relaxed);
                return;
            }
            DrawNotice();
            if (g_drawFaulted.load(std::memory_order_relaxed))
                LogShimA(LogLevel::Warn, "autosave", "HUD notice draw faulted; notice disabled for this run");
        }

        bool TryInstall()
        {
            const HookEngine::EngineRow rows[] = {
                { "AutoSaveNoticeHudGauge", &g_addr.gauge },
                { "HudFadeText", &g_addr.text },
                { "UiTextMeasure", &g_addr.measure },
                { "HudFillRect", &g_addr.fill },
                { "HudViewportWidth", &g_addr.viewportWidth },
                { "HudViewportHeight", &g_addr.viewportHeight },
                { "HudSpriteZ", &g_addr.spriteZ },
                { "HudTextStyle", &g_addr.style },
                { "HudPaneBuffer", &g_addr.pane },
            };
            if (!HookEngine::BindEngineRows("Autosave HUD notice", rows))
                return false;

            // Prologue of FUN_005c6f70: push ebp; mov ebp,esp; sub esp,0x74 are
            // the six whole instructions the detour moves. The detour accepts at
            // most patchLen expected bytes; the patches.json row checks the
            // longer guard.
            static const uint8_t expected[] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x74 };
            HookEngine::FrameThreadSitesScope frameSites;
            HookEngine::CodePatchLock lock;
            if (!InstallInlineDetour32(g_detour, g_addr.gauge,
                                       reinterpret_cast<void*>(&GaugeHook), 6,
                                       expected, sizeof(expected), &g_trampoline))
            {
                LogShimA(LogLevel::Warn, "autosave", "HUD notice: gauge detour failed");
                return false;
            }
            LogShimA(LogLevel::Info, "autosave", "HUD notice installed on the gauge draw");
            return true;
        }
    }

    void Show() noexcept
    {
        if (g_state == 0)
        {
            g_state = TryInstall() ? 1 : -1;
            if (g_state < 0)
                LogShimA(LogLevel::Info, "autosave", "HUD notice unavailable; saves are unaffected");
        }
        if (g_state > 0 && !g_drawFaulted.load(std::memory_order_relaxed))
            g_expiresAt.store(kPending, std::memory_order_relaxed);
    }

    void Hide() noexcept
    {
        g_expiresAt.store(0, std::memory_order_relaxed);
    }
}
