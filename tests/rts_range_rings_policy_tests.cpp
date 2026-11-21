// RtsRangeRings' engine-independent logic: radius validity, the direct-fire
// reach, the radar and mine sanity windows, the mine show rule and nearest-N
// pick, the slot layout, the option gating, and the ring label maths (letter
// spacing along a projected arc, centring on the bottom of the screen, the
// hide rules and behind-camera rejection).
#include "rts_range_rings_policy.h"
#include "rts_markers_policy.h"
#include "test_check.h"

#include <cmath>
#include <vector>

using namespace BZROpenShim::RtsRangeRings;
namespace RM = BZROpenShim::RtsMarkers;
using OpenShimTest::Check;

namespace
{
    bool Near(float a, float b, float epsilon = 0.01f)
    {
        return std::fabs(a - b) <= epsilon;
    }

    void RadiusTests()
    {
        Check(ValidRadius(5.0f) && ValidRadius(300.0f) && ValidRadius(1500.0f), "radii inside the window are valid");
        Check(!ValidRadius(4.9f) && !ValidRadius(1500.1f) && !ValidRadius(0.0f) && !ValidRadius(-10.0f),
              "radii outside the window are rejected");
        Check(!ValidRadius(std::nanf("")) && !ValidRadius(INFINITY), "NaN and infinity are rejected");

        Check(Near(DirectFireRange(75.0f, 3.0f), 224.0f), "direct fire is shotSpeed x lifeSpan - 1");
        Check(Near(DirectFireRange(130.0f, 1.5f), 194.0f), "a rocket-like shot");
        Check(DirectFireRange(0.0f, 3.0f) == 0.0f && DirectFireRange(75.0f, 0.0f) == 0.0f &&
                  DirectFireRange(-5.0f, 3.0f) == 0.0f && DirectFireRange(std::nanf(""), 3.0f) == 0.0f,
              "unusable speed or lifeSpan gives no range");
        Check(DirectFireRange(0.5f, 1.0f) == 0.0f, "a shot that dies inside 1 m has no ring");

        Check(SaneRadarRange(500.0f) && SaneRadarRange(10.0f) && SaneRadarRange(5000.0f), "stock radar ranges are sane");
        Check(!SaneRadarRange(9.9f) && !SaneRadarRange(5000.1f) && !SaneRadarRange(std::nanf("")) &&
                  !SaneRadarRange(-300.0f),
              "a runtime read outside 10..5000 or non-finite is rejected");
        Check(SaneMineRadius(30.0f) && !SaneMineRadius(0.5f) && !SaneMineRadius(501.0f) && !SaneMineRadius(INFINITY),
              "mine radius window 1..500");
    }

    void MineTests()
    {
        Check(MineNearUnit(0.0f, 49.0f, 30.0f), "inside searchRadius + 20 m shows");
        Check(MineNearUnit(30.0f, 40.0f, 30.0f), "exactly 50 m shows");
        Check(!MineNearUnit(0.0f, 50.5f, 30.0f), "just beyond 50 m is hidden");
        Check(!MineNearUnit(0.0f, 0.0f, std::nanf("")) && !MineNearUnit(std::nanf(""), 0.0f, 30.0f),
              "nonsense input hides");

        std::vector<NearItem> items;
        for (size_t i = 0; i < 40; ++i)
            items.push_back({static_cast<float>(40 - i), i}); // later ids are nearer
        const size_t kept = KeepNearest(items.data(), items.size(), RM::kMaxMineRingSlots);
        Check(kept == 24, "nearest-N keeps 24");
        Check(items[0].id == 39 && items[23].id == 16, "nearest first, the 24 nearest are the last 24 ids");
        std::vector<NearItem> few = {{3.0f, 0}, {1.0f, 1}};
        Check(KeepNearest(few.data(), few.size(), 24) == 2 && few[0].id == 1, "fewer than the cap keeps all");
        std::vector<NearItem> ties = {{2.0f, 7}, {2.0f, 8}, {2.0f, 9}};
        KeepNearest(ties.data(), ties.size(), 2);
        Check(ties[0].id == 7 && ties[1].id == 8, "ties keep input order");
    }

    void LayoutTests()
    {
        Check(RM::kMaxWeaponRingSlots == 16 && RM::kMaxRadarRingSlots == 16 && RM::kMaxMineRingSlots == 24,
              "caps: 16 weapon, 16 radar, 24 mine");
        Check(RM::kFirstWeaponRingSlot == RM::kFirstQueueRingSlot + RM::kMaxQueueRingSlots &&
                  RM::kFirstRadarRingSlot == RM::kFirstWeaponRingSlot + RM::kMaxWeaponRingSlots &&
                  RM::kFirstMineRingSlot == RM::kFirstRadarRingSlot + RM::kMaxRadarRingSlots &&
                  RM::kSlotCount == RM::kFirstMineRingSlot + RM::kMaxMineRingSlots,
              "the range slot ranges follow the queue rings and are disjoint");
        Check(RM::kSlotCount == 167 + 56, "pool grew by 56 slots (167 with the queue slots, 223 now)");
        Check(RM::kMaxArtilleryRings + RM::kMaxWeaponRingSlots + RM::kMaxRadarRingSlots + RM::kMaxMineRingSlots ==
                  kMaxLabelRings,
              "one label ring per ring that can carry a label");
        Check(RM::kDirectFireColour.a > 0.0f && RM::kDirectFireColour.a < 1.0f && RM::kRadarColour.a < 1.0f &&
                  RM::kMineColour.a < 1.0f,
              "range ring colours are translucent");
        const auto differs = [](const RM::Colour& a, const RM::Colour& b) {
            return std::fabs(a.r - b.r) + std::fabs(a.g - b.g) + std::fabs(a.b - b.b) > 0.25f;
        };
        Check(differs(RM::kMineColour, RM::kPowerColour) && differs(RM::kMineColour, RM::kNeutralColour) &&
                  differs(RM::kMineColour, RM::kRadarColour) && differs(RM::kMineColour, RM::kGoColour) &&
                  differs(RM::kRadarColour, RM::kGoColour) && differs(RM::kDirectFireColour, RM::kRangeColour),
              "the new colours differ from their neighbours");
    }

    void GatingTests()
    {
        Check(RingShown(true, false) && !RingShown(false, false) && !RingShown(true, true) && !RingShown(false, true),
              "a ring needs its option on and the HUD up");
        Check(LabelsShown(true, true, false), "ring and label options on: labels show");
        Check(!LabelsShown(false, true, false), "label option alone shows nothing (Reset to Stock leaves no label)");
        Check(!LabelsShown(true, false, false), "label option off hides labels");
        Check(!LabelsShown(true, true, true), "labels hide with the HUD");
    }

    // A circle on the screen: point i at angle 2*pi*i/n (y grows downward, so
    // angle pi/2 is the bottom of the screen).
    std::vector<ScreenPoint> Circle(float cx, float cy, float rx, float ry, size_t n = kLabelArcPoints)
    {
        std::vector<ScreenPoint> pts(n);
        for (size_t i = 0; i < n; ++i)
        {
            const float a = 2.0f * RM::kPi * static_cast<float>(i) / static_cast<float>(n);
            pts[i] = {cx + rx * std::cos(a), cy + ry * std::sin(a), true};
        }
        return pts;
    }

    std::vector<float> Widths(size_t n, float w)
    {
        return std::vector<float>(n, w);
    }

    void LabelTests()
    {
        const float viewW = 1280.0f, viewH = 720.0f;
        {
            const std::vector<float> w = {8, 6, 10};
            Check(Near(TextWidth(w.data(), w.size(), 1.0f), 26.0f), "text width = glyphs + spacing between them");
            Check(TextWidth(nullptr, 0) == 0.0f, "no text has no width");
        }
        {
            const auto ring = Circle(640, 300, 200, 100);
            Check(Near(ProjectedCircumference(ring.data(), ring.size()), 965.0f, 8.0f), "ellipse circumference");
            const size_t anchor = BottomAnchor(ring.data(), ring.size(), viewW, viewH, kLabelMarginPx);
            Check(anchor == 16, "the bottom of the screen is the largest y (angle pi/2 = index 16)");
        }
        // Spacing and centring.
        {
            const auto ring = Circle(640, 300, 200, 100);
            const auto w = Widths(12, 10.0f);
            GlyphPos out[12];
            Check(PlaceArcText(ring.data(), ring.size(), w.data(), w.size(), viewW, viewH, out) == LabelResult::Placed,
                  "a 12-letter label fits a 400x200 ellipse");
            Check(Near(out[0].x + out[11].x, 2.0f * 640.0f, 1.5f), "the text is centred on the bottom point");
            bool increasing = true;
            for (int i = 1; i < 12; ++i)
                increasing = increasing && out[i].x > out[i - 1].x;
            Check(increasing, "letters run left to right");
            bool evenSpacing = true;
            for (int i = 1; i < 12; ++i)
            {
                const float d = std::hypot(out[i].x - out[i - 1].x, out[i].y - out[i - 1].y);
                // 10 px glyph + 1 px spacing along the arc; chords are a hair shorter on a curve.
                evenSpacing = evenSpacing && d > 10.0f && d < 11.1f;
            }
            Check(evenSpacing, "letters are spaced by glyph width plus spacing along the arc");
            Check(out[5].y > 380.0f && out[0].y < out[5].y, "letters curve up away from the bottom point");
        }
        // Reversed point order still reads left to right.
        {
            auto ring = Circle(640, 300, 200, 100);
            std::vector<ScreenPoint> rev(ring.rbegin(), ring.rend());
            const auto w = Widths(8, 10.0f);
            GlyphPos out[8];
            Check(PlaceArcText(rev.data(), rev.size(), w.data(), w.size(), viewW, viewH, out) == LabelResult::Placed &&
                      out[7].x > out[0].x,
                  "text reads left to right whatever the sample order");
        }
        // Variable glyph widths: a wide glyph takes more arc.
        {
            const auto ring = Circle(640, 300, 200, 100);
            const std::vector<float> w = {4, 20, 4};
            GlyphPos out[3];
            Check(PlaceArcText(ring.data(), ring.size(), w.data(), w.size(), viewW, viewH, out) == LabelResult::Placed,
                  "variable widths place");
            Check((out[1].x - out[0].x) > 10.0f && Near(out[1].x - out[0].x, out[2].x - out[1].x, 0.5f),
                  "centre-to-centre distance follows the measured widths");
        }
        // Too short: a tiny ring cannot carry the text.
        {
            const auto ring = Circle(640, 300, 20, 10);
            const auto w = Widths(12, 10.0f);
            GlyphPos out[12];
            Check(PlaceArcText(ring.data(), ring.size(), w.data(), w.size(), viewW, viewH, out) == LabelResult::TooShort,
                  "a ring whose circumference is under twice the text is hidden");
        }
        // Behind the camera.
        {
            auto ring = Circle(640, 300, 200, 100);
            for (auto& p : ring)
                p.valid = false;
            const auto w = Widths(6, 10.0f);
            GlyphPos out[6];
            Check(PlaceArcText(ring.data(), ring.size(), w.data(), w.size(), viewW, viewH, out) ==
                      LabelResult::BehindCamera,
                  "every point behind the camera hides the label");
            ring = Circle(640, 300, 200, 100);
            for (size_t i = 12; i <= 20; ++i)
                ring[i].valid = false; // the bottom arc is behind the camera
            const LabelResult r = PlaceArcText(ring.data(), ring.size(), w.data(), w.size(), viewW, viewH, out);
            Check(r != LabelResult::Placed, "a text span through points behind the camera is hidden");
        }
        // Off screen.
        {
            const auto ring = Circle(640, 300, 200, 100);
            const auto w = Widths(12, 10.0f);
            GlyphPos out[12];
            Check(PlaceArcText(ring.data(), ring.size(), w.data(), w.size(), 100.0f, 100.0f, out) ==
                      LabelResult::OffScreen,
                  "a ring wholly off the screen is hidden");
            // Bottom of the ring runs off the bottom edge of the screen.
            const auto low = Circle(640, 700, 200, 100);
            const auto r = PlaceArcText(low.data(), low.size(), w.data(), w.size(), viewW, viewH, out);
            Check(r == LabelResult::OffScreen, "a span running off the screen edge is hidden");
        }
        // Degenerate input.
        {
            GlyphPos out[1];
            const float w1[1] = {10.0f};
            Check(PlaceArcText(nullptr, 0, w1, 1, viewW, viewH, out) == LabelResult::NoText ||
                      PlaceArcText(nullptr, 0, w1, 1, viewW, viewH, out) == LabelResult::BehindCamera,
                  "no ring places nothing");
            const auto ring = Circle(640, 300, 200, 100);
            Check(PlaceArcText(ring.data(), ring.size(), w1, 0, viewW, viewH, out) == LabelResult::NoText,
                  "no glyphs is NoText");
            const float zero[1] = {0.0f};
            Check(PlaceArcText(ring.data(), ring.size(), zero, 1, viewW, viewH, out) == LabelResult::NoText,
                  "zero-width text is NoText");
        }
        Check(kMaxLabels == 24, "at most 24 labels a frame");
    }
}

int main()
{
    RadiusTests();
    MineTests();
    LayoutTests();
    GatingTests();
    LabelTests();
    return OpenShimTest::ExitCode();
}
