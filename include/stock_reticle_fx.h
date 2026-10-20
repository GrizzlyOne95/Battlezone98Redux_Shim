#pragma once

#include "hud_feedback_policy.h"

#include <cstdint>

// Shader path for the stock sprite reticle (ReticleStyle=Stock). The reticle's
// own atlas material is cloned with OpenShim_ReticleFx_fragmentHLSL4 and the
// stock atlas cell is drawn through the native sized-sprite submitter, so only
// the visible reticle changes. Frame thread only.
namespace BZROpenShim::HudFeedback::StockReticleFx
{
    struct Frame
    {
        int sprite = 0;
        int x = 0, y = 0;          // the stock call's (pane-relative) aim point
        uint32_t flags = 0;        // the stock call's flags
        float scale = 1;           // the stock call's scale
        float uiScaleX = 1, uiScaleY = 1;
        GhostPlan ghost;
        uint32_t ringRgb = 0xFFFFFF;
        uint32_t tintRgb = 0xFFFFFF;
        float tintAmount = 0;
        float flash = 0;
    };

    // Draws the stock reticle through the shader material. Returns false,
    // having drawn nothing, whenever the material is unavailable; the caller
    // then draws the stock sprite itself.
    bool Draw(void* viewport, const Frame& frame) noexcept;

    // Drops cached materials so the next draw clones from the current
    // sprite table; called on mission reset, where Modable can be rebuilt.
    void Invalidate() noexcept;
}
