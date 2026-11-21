// rts_range_labels.h
// BZR Open Shim - the HUD text of the RTS range rings (rts_range_labels.cpp):
// each ring's name, drawn letter by letter along its projected arc in the
// ring's colour. rts_markers.cpp publishes the rings once per tick; a HUD
// painter (HudGaugeOverlay::Slot::RangeLabels) draws them. Local draw only.
// Rules and maths: rts_range_rings_policy.h. Docs/RTS_RANGE_RINGS.md.
#pragma once

#include <cstddef>
#include <cstdint>

#include "rts_range_rings_policy.h"

namespace BZROpenShim
{
    namespace Hooks
    {
        struct RangeLabelRing
        {
            RtsRangeRings::Kind kind = RtsRangeRings::Kind::Weapon;
            uint32_t argb = 0xFFFFFFFFu; // text colour (the ring's, alpha raised)
            float centre[3] = {};        // sim space
            // World samples around the ring at terrain height (+ lift), sim space.
            float arc[RtsRangeRings::kLabelArcPoints][3] = {};
        };

        // Game thread. Replaces the published set; count 0 clears it (labels
        // hidden). Installs the HUD painter on the first non-empty call.
        void PublishRangeLabels(const RangeLabelRing* rings, size_t count);
    }
}
