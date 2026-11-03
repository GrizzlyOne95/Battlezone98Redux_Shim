// autosave_notice_layout.h
// BZR Open Shim - screen placement of the autosave HUD notice
//
// Copyright (C) 2025-2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Pure arithmetic, kept out of autosave_notice.cpp so it can be unit tested
// without the engine. All values are screen pixels in the HUD viewport.

#pragma once

#include <algorithm>

namespace BZROpenShim::AutoSaveNotice
{
    // Campaign Reimagined's old overlay: a panel 16% of the viewport wide,
    // about 2.1 text heights tall, resting 3% above the bottom edge.
    inline constexpr float kPanelWidthFraction = 0.16f;
    inline constexpr float kPanelHeightInTextLines = 2.1f;
    inline constexpr float kBottomMarginFraction = 0.03f;

    struct Layout
    {
        // Inclusive corners, as HudFillRect takes them.
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        // Centre column and top row for the text (centre-aligned on x).
        int textCentreX = 0, textTop = 0;
    };

    // False when any input is unusable; the notice is then skipped.
    inline bool ComputeLayout(int viewW, int viewH, float textW, float textH, Layout& out)
    {
        if (viewW <= 0 || viewH <= 0 || !(textW > 0.0f) || !(textH > 0.0f))
            return false;

        // Never narrower than the text plus half a line either side.
        const float width = (std::min)(
            static_cast<float>(viewW),
            (std::max)(kPanelWidthFraction * static_cast<float>(viewW), textW + textH));
        const float height = kPanelHeightInTextLines * textH;
        const float bottom = static_cast<float>(viewH) * (1.0f - kBottomMarginFraction);
        const float top = bottom - height;
        const float left = (static_cast<float>(viewW) - width) * 0.5f;
        if (top < 0.0f)
            return false;

        out.x1 = static_cast<int>(left);
        out.x2 = static_cast<int>(left + width) - 1;
        out.y1 = static_cast<int>(top);
        out.y2 = static_cast<int>(bottom) - 1;
        out.textCentreX = viewW / 2;
        out.textTop = static_cast<int>(top + (height - textH) * 0.5f);
        return out.x2 >= out.x1 && out.y2 >= out.y1;
    }
}
