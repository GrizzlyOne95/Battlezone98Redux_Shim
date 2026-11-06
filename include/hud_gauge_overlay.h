// hud_gauge_overlay.h
// BZR Open Shim - shared paint point after the stock scrap/pilot gauge draw
//
// Copyright (C) 2025-2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// One inline detour on the gauge draw (FUN_005c6f70, the
// AutoSaveNoticeHudGauge row) runs every gameplay HUD frame. Several small
// HUD overlays need to draw text there, and a site can only carry one
// detour, so this module owns it and calls a fixed set of painters after the
// stock gauge returns. Painters receive the bound HUD text/fill primitives.

#pragma once

#include <cstdint>

namespace BZROpenShim::HudGaugeOverlay
{
    using TextFn = void(__cdecl*)(void*, int, int, float*, float*, const char*, void*,
                                  uint32_t, int, int, int, int);
    using MeasureFn = void(__cdecl*)(void*, const char*, float*, float*);
    using FillFn = void(__cdecl*)(void*, int, int, int, int, uint32_t, int);

    // Everything a painter needs for one frame. Valid only during the call.
    struct Frame
    {
        void* pane = nullptr;   // *HudPaneBuffer
        void* style = nullptr;  // *HudTextStyle
        int viewW = 0, viewH = 0;
        TextFn text = nullptr;
        MeasureFn measure = nullptr;
        FillFn fill = nullptr;
        float* spriteZ = nullptr;
    };

    enum class Slot : uint32_t { AutoSaveNotice = 0, KillTicker = 1, Count = 2 };

    // A painter returns false when it faulted; the overlay then stops calling
    // that slot for the rest of the run. Painters run on the frame thread
    // inside the HUD pass and must not allocate or block.
    using Painter = bool (*)(const Frame&) noexcept;

    // Binds the rows and installs the detour once. Game/frame thread only.
    // False when any row is missing or mismatched (logged once); later calls
    // return the same answer without retrying.
    bool Ensure() noexcept;

    // Sets or clears (nullptr) one slot. Safe from any thread.
    void SetPainter(Slot slot, Painter painter) noexcept;

    // Draws one translucent backing rectangle then left/centre-aligned text,
    // restoring the shared ambient sprite depth and text-style colour.
    // alignX: 0 = x is the left edge, 1 = centre on x. Returns false on fault.
    bool DrawPanelText(const Frame& frame, int x1, int y1, int x2, int y2, uint32_t panelArgb,
                       int textX, int textY, const char* text, uint32_t textArgb, int alignX) noexcept;
}
