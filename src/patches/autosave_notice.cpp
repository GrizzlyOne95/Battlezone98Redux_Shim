// autosave_notice.cpp
// BZR Open Shim - "Game autosaved." HUD notice
//
// Copyright (C) 2025-2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Draws a dark translucent panel with centred light-green text at the bottom
// of the HUD for a few seconds after a successful autosave, using the stock
// HUD primitives, so it needs neither EXU nor an Ogre overlay. It paints
// through the shared gauge-draw overlay (hud_gauge_overlay.cpp), which owns
// the detour and documents the native primitives.
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
#include "hud_gauge_overlay.h"
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
        constexpr ULONGLONG kShowMs = 3000;
        constexpr char kText[] = "Game autosaved.";
        // ARGB: black at alpha 0.55, and the old overlay's (0.82, 1, 0.82).
        constexpr uint32_t kPanelColor = 0x8C000000u;
        constexpr uint32_t kTextColor = 0xFFD1FFD1u;

        int g_state = 0;                       // 0 untried, 1 installed, -1 unavailable
        // 0 = not showing, kPending = shown but not drawn yet; the timer starts on
        // the first frame that draws it, so a pause or hidden HUD does not eat it.
        constexpr ULONGLONG kPending = 1;
        std::atomic<ULONGLONG> g_expiresAt{0};

        bool MeasureText(const HudGaugeOverlay::Frame& frame, float& textW, float& textH) noexcept
        {
            __try
            {
                frame.measure(frame.style, kText, &textW, &textH);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Runs after the stock gauge draw, on the frame thread.
        bool PaintNotice(const HudGaugeOverlay::Frame& frame) noexcept
        {
            ULONGLONG expires = g_expiresAt.load(std::memory_order_relaxed);
            if (expires == 0)
                return true;
            if (expires == kPending)
            {
                expires = GetTickCount64() + kShowMs;
                g_expiresAt.store(expires, std::memory_order_relaxed);
            }
            if (GetTickCount64() >= expires)
            {
                g_expiresAt.store(0, std::memory_order_relaxed);
                return true;
            }

            float textW = 0.0f, textH = 0.0f;
            if (!MeasureText(frame, textW, textH))
            {
                g_expiresAt.store(0, std::memory_order_relaxed);
                return false;
            }
            Layout layout;
            if (!ComputeLayout(frame.viewW, frame.viewH, textW, textH, layout))
                return true;
            if (!HudGaugeOverlay::DrawPanelText(frame, layout.x1, layout.y1, layout.x2, layout.y2,
                                                kPanelColor, layout.textCentreX, layout.textTop,
                                                kText, kTextColor, 1))
            {
                g_expiresAt.store(0, std::memory_order_relaxed);
                return false;
            }
            return true;
        }
    }

    void Show() noexcept
    {
        if (g_state == 0)
        {
            g_state = HudGaugeOverlay::Ensure() ? 1 : -1;
            if (g_state > 0)
                HudGaugeOverlay::SetPainter(HudGaugeOverlay::Slot::AutoSaveNotice, &PaintNotice);
            else
                LogShimA(LogLevel::Info, "autosave", "HUD notice unavailable; saves are unaffected");
        }
        if (g_state > 0)
            g_expiresAt.store(kPending, std::memory_order_relaxed);
    }

    void Hide() noexcept
    {
        g_expiresAt.store(0, std::memory_order_relaxed);
    }
}
