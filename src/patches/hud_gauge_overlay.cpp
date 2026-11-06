// hud_gauge_overlay.cpp
// BZR Open Shim - shared paint point after the stock scrap/pilot gauge draw
//
// Copyright (C) 2025-2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Extracted from autosave_notice.cpp, which used to own this detour alone, so
// the kill ticker can draw on the same frame-thread HUD pass.
//
// Evidence (decompile functions named FUN_<address>):
//   FUN_005c6f70  scrap/pilot gauge draw, run each gameplay HUD frame; it
//                 prints through FUN_004c0100 with DAT_00917580 (pane
//                 buffer), DAT_00917550 (text style), DAT_0091755c (colour).
//   FUN_004c0100  cdecl text draw, 12 stack args: buffer, x, y, &w, &h, text,
//                 style, colour, fillColour (-1 = none), fillMode, alignX
//                 (1 = centre on x, 0 = x is the left edge), alignY (0 = y is
//                 the top). It stores the colour into the style's first dword
//                 (FUN_00689950), and on return *w/*h hold the right/bottom
//                 edge, not the size.
//   FUN_00689ab0  cdecl (style, text, &w, &h) text measure (UiTextMeasure).
//   FUN_0068afb0  HudFillRect cdecl (buffer, x1, y1, x2, y2, colour, mode);
//                 FUN_0068ac50 leaves the colour, alpha included, untouched
//                 in mode 0.
//   DAT_00920ef4  ambient sprite depth; FUN_004c0100 adds 0.01 to it around
//                 its own background fill so the fill sits behind the text.

#include "hud_gauge_overlay.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <atomic>
#include <cstdint>

namespace BZROpenShim::HudGaugeOverlay
{
    namespace
    {
        using GaugeFn = void(__fastcall*)(void*, void*);

        constexpr float kBackingZStep = 0.01f;
        constexpr size_t kSlots = static_cast<size_t>(Slot::Count);

        struct Addresses
        {
            uint32_t gauge = 0, text = 0, measure = 0, fill = 0;
            uint32_t viewportWidth = 0, viewportHeight = 0;
            uint32_t spriteZ = 0, style = 0, pane = 0;
        };

        Addresses g_addr;
        InlineDetour32 g_detour;
        void* volatile g_trampoline = nullptr;
        int g_state = 0; // 0 untried, 1 installed, -1 unavailable; game thread only
        std::atomic<Painter> g_painters[kSlots] = {};
        std::atomic<bool> g_faulted[kSlots] = {};

        bool ReadFrame(Frame& frame) noexcept
        {
            __try
            {
                frame.pane = *reinterpret_cast<void* const*>(g_addr.pane);
                frame.style = *reinterpret_cast<void* const*>(g_addr.style);
                frame.viewW = *reinterpret_cast<const int*>(g_addr.viewportWidth);
                frame.viewH = *reinterpret_cast<const int*>(g_addr.viewportHeight);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            frame.text = reinterpret_cast<TextFn>(g_addr.text);
            frame.measure = reinterpret_cast<MeasureFn>(g_addr.measure);
            frame.fill = reinterpret_cast<FillFn>(g_addr.fill);
            frame.spriteZ = reinterpret_cast<float*>(g_addr.spriteZ);
            return frame.pane && frame.style && frame.viewW > 0 && frame.viewH > 0;
        }

        void __fastcall GaugeHook(void* self, void* edx)
        {
            const auto original = reinterpret_cast<GaugeFn>(g_trampoline);
            if (!original)
                return;
            original(self, edx);

            Frame frame;
            bool frameRead = false;
            for (size_t i = 0; i < kSlots; ++i)
            {
                const Painter painter = g_painters[i].load(std::memory_order_acquire);
                if (!painter || g_faulted[i].load(std::memory_order_relaxed))
                    continue;
                if (!frameRead)
                {
                    if (!ReadFrame(frame))
                        return;
                    frameRead = true;
                }
                if (!painter(frame))
                {
                    g_faulted[i].store(true, std::memory_order_relaxed);
                    LogShimA(LogLevel::Warn, "hudoverlay",
                             "HUD overlay slot %u faulted; it is disabled for this run",
                             static_cast<unsigned>(i));
                }
            }
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
            if (!HookEngine::BindEngineRows("HUD gauge overlay", rows))
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
                LogShimA(LogLevel::Warn, "hudoverlay", "gauge detour failed");
                return false;
            }
            LogShimA(LogLevel::Info, "hudoverlay", "HUD overlay installed on the gauge draw");
            return true;
        }
    }

    bool Ensure() noexcept
    {
        if (g_state == 0)
        {
            g_state = TryInstall() ? 1 : -1;
            if (g_state < 0)
                LogShimA(LogLevel::Info, "hudoverlay", "HUD overlay unavailable; overlays stay hidden");
        }
        return g_state > 0;
    }

    void SetPainter(Slot slot, Painter painter) noexcept
    {
        const size_t index = static_cast<size_t>(slot);
        if (index < kSlots)
            g_painters[index].store(painter, std::memory_order_release);
    }

    // Plain data only: this holds the __try, so nothing here may need
    // unwinding.
    bool DrawPanelText(const Frame& frame, int x1, int y1, int x2, int y2, uint32_t panelArgb,
                       int textX, int textY, const char* text, uint32_t textArgb, int alignX) noexcept
    {
        float savedZ = 0.0f;
        bool zRaised = false;
        uint32_t* styleColor = nullptr;
        uint32_t savedColor = 0;
        bool colorChanged = false;
        __try
        {
            if ((panelArgb >> 24) != 0 && x2 >= x1 && y2 >= y1)
            {
                savedZ = *frame.spriteZ;
                *frame.spriteZ = savedZ + kBackingZStep;
                zRaised = true;
                frame.fill(frame.pane, x1, y1, x2, y2, panelArgb, 0);
                *frame.spriteZ = savedZ;
                zRaised = false;
            }

            // The text call writes its colour into the shared style, so put
            // the previous one back for whoever draws next.
            styleColor = static_cast<uint32_t*>(frame.style);
            savedColor = *styleColor;
            colorChanged = true;
            float edgeX = 0.0f, edgeY = 0.0f;
            frame.text(frame.pane, textX, textY, &edgeX, &edgeY, text, frame.style,
                       textArgb, -1, 0, alignX, 0);
            *styleColor = savedColor;
            colorChanged = false;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            __try
            {
                if (zRaised)
                    *frame.spriteZ = savedZ;
                if (colorChanged)
                    *styleColor = savedColor;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return false;
        }
    }
}
