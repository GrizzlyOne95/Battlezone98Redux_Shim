// rts_range_rings_policy.h
// BZR Open Shim - RTS range rings: the engine-independent rules behind the
// direct-fire weapon, radar and mine-trigger rings and their text labels
// (rts_markers.cpp, rts_range_labels.cpp). Header-only, free of Windows and
// Ogre, so the unit tests check the same math the shim runs.
// See Docs/RTS_RANGE_RINGS.md.
//
//  - Radii: validity, the direct-fire reach (shotSpeed * lifeSpan - 1, as
//    ai_odf_tuning.cpp), sanity windows for the radar and mine reads.
//  - Mines: which mines show (within searchRadius + 20 m of a selected unit)
//    and the nearest-N pick.
//  - Labels: letters placed one by one along a ring's projected arc, centred
//    on the point nearest the bottom of the screen, upright, with the hide
//    rules (too short, off screen, behind the camera).
#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>

#include "rts_markers_policy.h"

namespace BZROpenShim
{
    namespace RtsRangeRings
    {
        using RtsMarkers::Colour;

        // ---- Radii -----------------------------------------------------------
        constexpr float kMinRingRadius = 5.0f;
        constexpr float kMaxRingRadius = 1500.0f;

        // A ring is drawn only for a finite radius inside the window.
        inline bool ValidRadius(float radius)
        {
            return std::isfinite(radius) && radius >= kMinRingRadius && radius <= kMaxRingRadius;
        }

        // Straight-flying ordnance reach: shotSpeed * lifeSpan, less 1 m, the
        // value ai_odf_tuning.cpp uses. 0 for anything unusable.
        inline float DirectFireRange(float shotSpeed, float lifeSpan)
        {
            if (!std::isfinite(shotSpeed) || !std::isfinite(lifeSpan) || !(shotSpeed > 0.0f) || !(lifeSpan > 0.0f))
                return 0.0f;
            const float range = std::max(shotSpeed * lifeSpan - 1.0f, 0.0f);
            return std::isfinite(range) ? range : 0.0f;
        }

        // The runtime CraftClass +0x150 read is UNVERIFIED: accept it only when
        // it looks like a scan range.
        constexpr float kMinSaneRadarRange = 10.0f;
        constexpr float kMaxSaneRadarRange = 5000.0f;
        inline bool SaneRadarRange(float value)
        {
            return std::isfinite(value) && value >= kMinSaneRadarRange && value <= kMaxSaneRadarRange;
        }

        // ProximityMineClass +0x168 (searchRadius; stock 30).
        constexpr float kMinSaneMineRadius = 1.0f;
        constexpr float kMaxSaneMineRadius = 500.0f;
        inline bool SaneMineRadius(float value)
        {
            return std::isfinite(value) && value >= kMinSaneMineRadius && value <= kMaxSaneMineRadius;
        }

        // ---- Mines -----------------------------------------------------------
        constexpr float kMineShowMargin = 20.0f;

        // A mine shows when a selected unit is within its searchRadius plus the
        // margin (horizontal distance).
        inline bool MineNearUnit(float dx, float dz, float searchRadius)
        {
            if (!std::isfinite(dx) || !std::isfinite(dz) || !SaneMineRadius(searchRadius))
                return false;
            const float reach = searchRadius + kMineShowMargin;
            return dx * dx + dz * dz <= reach * reach;
        }

        struct NearItem
        {
            float distance = 0.0f;
            size_t id = 0; // the caller's own index
        };

        // Keeps the `cap` nearest at the front of `items` (ties keep input
        // order) and returns how many remain.
        inline size_t KeepNearest(NearItem* items, size_t count, size_t cap)
        {
            std::stable_sort(items, items + count,
                             [](const NearItem& a, const NearItem& b) { return a.distance < b.distance; });
            return std::min(count, cap);
        }

        // Shown only while its option is on and the HUD is up.
        inline bool RingShown(bool optionOn, bool hudHidden)
        {
            return optionOn && !hudHidden;
        }

        // Labels also need their own option.
        inline bool LabelsShown(bool ringOptionOn, bool labelOptionOn, bool hudHidden)
        {
            return ringOptionOn && labelOptionOn && !hudHidden;
        }

        // ---- Labels ----------------------------------------------------------
        enum class Kind : uint8_t
        {
            Artillery,
            Weapon,
            Radar,
            Mine,
        };

        constexpr size_t kMaxLabels = 24;      // drawn per frame, nearest first
        constexpr size_t kMaxLabelRings = 72;  // published per tick (16 + 16 + 16 + 24)
        constexpr size_t kLabelArcPoints = 64; // world samples around a ring
        constexpr size_t kMaxLabelChars = 24;
        constexpr float kLabelMarginPx = 12.0f; // screen margin and the spare arc a label needs
        constexpr float kLabelSpacingPx = 1.0f; // added between glyphs

        struct ScreenPoint
        {
            float x = 0.0f;
            float y = 0.0f;
            bool valid = false; // false: behind the camera or not finite
        };

        struct GlyphPos
        {
            float x = 0.0f; // glyph centre, screen pixels
            float y = 0.0f;
        };

        enum class LabelResult : uint8_t
        {
            Placed,
            NoText,
            TooShort,
            OffScreen,
            BehindCamera,
        };

        inline bool OnScreen(const ScreenPoint& p, float viewW, float viewH, float margin)
        {
            return p.valid && p.x >= margin && p.y >= margin && p.x <= viewW - margin && p.y <= viewH - margin;
        }

        // Length of the closed projected polyline, counting only segments whose
        // both ends are valid (a lower bound when part of the ring is behind
        // the camera).
        inline float ProjectedCircumference(const ScreenPoint* ring, size_t n)
        {
            if (!ring || n < 3)
                return 0.0f;
            float total = 0.0f;
            for (size_t i = 0; i < n; ++i)
            {
                const ScreenPoint& a = ring[i];
                const ScreenPoint& b = ring[(i + 1) % n];
                if (a.valid && b.valid)
                    total += std::hypot(b.x - a.x, b.y - a.y);
            }
            return total;
        }

        // Width of the whole text: glyph widths plus spacing between them.
        inline float TextWidth(const float* glyphWidths, size_t count, float spacing = kLabelSpacingPx)
        {
            if (!glyphWidths || count == 0)
                return 0.0f;
            float w = 0.0f;
            for (size_t i = 0; i < count; ++i)
                w += std::max(0.0f, glyphWidths[i]);
            return w + spacing * static_cast<float>(count - 1);
        }

        // The index of the on-screen valid point lowest on the screen (largest
        // y): the part of the ring nearest the viewer. n when there is none.
        inline size_t BottomAnchor(const ScreenPoint* ring, size_t n, float viewW, float viewH, float margin)
        {
            size_t best = n;
            for (size_t i = 0; i < n; ++i)
                if (OnScreen(ring[i], viewW, viewH, margin) && (best == n || ring[i].y > ring[best].y))
                    best = i;
            return best;
        }

        // The point `distance` px along the polyline from vertex `anchor` in
        // direction `dir` (+1 / -1 around the loop). False when the walk
        // reaches a vertex that is behind the camera, off screen, or goes
        // more than once round; `blocked` says whether the cause was an
        // invalid (behind-camera) vertex.
        inline bool WalkArc(const ScreenPoint* ring, size_t n, size_t anchor, int dir, float distance, float viewW,
                            float viewH, float margin, GlyphPos& out, bool& behind)
        {
            behind = false;
            size_t i = anchor;
            float remaining = distance;
            for (size_t step = 0; step <= n; ++step)
            {
                const size_t j = dir > 0 ? (i + 1) % n : (i + n - 1) % n;
                const ScreenPoint& a = ring[i];
                const ScreenPoint& b = ring[j];
                if (!a.valid || !b.valid)
                {
                    behind = true;
                    return false;
                }
                if (!OnScreen(a, viewW, viewH, margin) || !OnScreen(b, viewW, viewH, margin))
                    return false;
                const float seg = std::hypot(b.x - a.x, b.y - a.y);
                if (remaining <= seg || seg <= 0.0f)
                {
                    const float t = seg > 0.0f ? remaining / seg : 0.0f;
                    out.x = a.x + (b.x - a.x) * t;
                    out.y = a.y + (b.y - a.y) * t;
                    return true;
                }
                remaining -= seg;
                i = j;
            }
            return false;
        }

        // Places `glyphCount` letters (centres into `out`) along the projected
        // ring `ring[0..n)` (a closed loop of world samples at terrain height).
        // The text is centred on the vertex nearest the bottom of the screen
        // and runs left to right; glyphs stay upright. Hidden (non-Placed)
        // when:
        //  - there is no text;
        //  - the projected circumference is under twice the text width plus a
        //    margin (the text would wrap round the ring);
        //  - every vertex is behind the camera, or the span the text needs
        //    runs through a vertex behind it (BehindCamera);
        //  - no vertex is on screen, or the span runs off screen (OffScreen).
        inline LabelResult PlaceArcText(const ScreenPoint* ring, size_t n, const float* glyphWidths, size_t glyphCount,
                                        float viewW, float viewH, GlyphPos* out, float margin = kLabelMarginPx,
                                        float spacing = kLabelSpacingPx)
        {
            if (!ring || !glyphWidths || !out || glyphCount == 0)
                return LabelResult::NoText;
            if (n < 3)
                return LabelResult::BehindCamera;
            const float width = TextWidth(glyphWidths, glyphCount, spacing);
            if (!(width > 0.0f))
                return LabelResult::NoText;
            size_t validCount = 0;
            for (size_t i = 0; i < n; ++i)
                if (ring[i].valid)
                    ++validCount;
            if (validCount == 0)
                return LabelResult::BehindCamera;
            if (ProjectedCircumference(ring, n) < 2.0f * width + margin)
                return LabelResult::TooShort;
            const size_t anchor = BottomAnchor(ring, n, viewW, viewH, margin);
            if (anchor == n)
                return LabelResult::OffScreen;
            // Read left to right along the bottom of the loop.
            const ScreenPoint& prev = ring[(anchor + n - 1) % n];
            const ScreenPoint& next = ring[(anchor + 1) % n];
            const int dir = (next.valid && prev.valid) ? (next.x >= prev.x ? 1 : -1) : 1;

            float cursor = 0.0f; // start of the next glyph along the text
            for (size_t g = 0; g < glyphCount; ++g)
            {
                const float w = std::max(0.0f, glyphWidths[g]);
                const float offset = cursor + w * 0.5f - width * 0.5f; // from the anchor, + along dir
                cursor += w + spacing;
                bool behind = false;
                const bool ok = offset >= 0.0f ? WalkArc(ring, n, anchor, dir, offset, viewW, viewH, margin, out[g], behind)
                                               : WalkArc(ring, n, anchor, -dir, -offset, viewW, viewH, margin, out[g], behind);
                if (!ok)
                    return behind ? LabelResult::BehindCamera : LabelResult::OffScreen;
            }
            return LabelResult::Placed;
        }
    }
}
