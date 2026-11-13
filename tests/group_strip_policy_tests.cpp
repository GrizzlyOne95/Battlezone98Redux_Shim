#include "group_strip_policy.h"

#include <cstdio>
#include <cstring>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::GroupStripPolicy;

namespace
{
    // A fake world. Handles >= 0x900 are dead; below 0x100 is class 1
    // "Tank", 0x100-0x1FF class 2 "Bomber", anything else class 3 "Turret".
    bool FakeResolve(uint32_t handle, MemberInfo& info)
    {
        if (handle == 0 || handle >= 0x900)
            return false;
        info.classKey = handle < 0x100 ? 1 : handle < 0x200 ? 2 : 3;
        const char* name = info.classKey == 1 ? "Tank" : info.classKey == 2 ? "Bomber" : "Turret";
        std::snprintf(info.name, sizeof(info.name), "%s", name);
        return true;
    }

    // 8 px per character, 12 px high, like a small HUD font.
    bool FakeMeasure(const char* text, int& w, int& h)
    {
        w = static_cast<int>(std::strlen(text)) * 8;
        h = 12;
        return true;
    }

    StripGroup Make(int group, int count, const char* name, bool mixed = false)
    {
        StripGroup g;
        g.group = group;
        g.liveCount = count;
        g.mixed = mixed;
        std::snprintf(g.name, sizeof(g.name), "%s", name);
        return g;
    }

    void TestSummarize()
    {
        const uint32_t tanks[] = { 0x10, 0x20, 0x901, 0, 0x30 };
        StripGroup g = SummarizeGroup(0, tanks, 5, FakeResolve);
        Check(g.group == 0 && g.liveCount == 3, "dead and empty handles are not counted");
        Check(!g.mixed && std::strcmp(g.name, "Tank") == 0, "same class: not mixed, first name");

        const uint32_t mixed[] = { 0x901, 0x110, 0x10 };
        g = SummarizeGroup(2, mixed, 3, FakeResolve);
        Check(g.liveCount == 2 && g.mixed, "another class marks the group mixed");
        Check(std::strcmp(g.name, "Bomber") == 0, "named after the first live member");

        const uint32_t dead[] = { 0x901, 0x902 };
        g = SummarizeGroup(4, dead, 2, FakeResolve);
        Check(g.liveCount == 0 && g.name[0] == '\0', "all dead: empty");

        Check(SummarizeGroup(1, tanks, -3, FakeResolve).liveCount == 0, "negative count is empty");
        Check(SummarizeGroup(1, nullptr, 3, FakeResolve).liveCount == 0, "no handles is empty");

        uint32_t many[kGroupCapacity + 5];
        for (uint32_t& h : many)
            h = 0x10;
        Check(SummarizeGroup(0, many, kGroupCapacity + 5, FakeResolve).liveCount == kGroupCapacity,
              "stored count clamps to the group capacity");
    }

    void TestDisplayName()
    {
        char out[kNameBufferSize];
        ChooseDisplayName("  Tank ", 32, "avtank", out, sizeof(out));
        Check(std::strcmp(out, "Tank") == 0, "unitName trimmed");
        ChooseDisplayName("", 32, "avtank", out, sizeof(out));
        Check(std::strcmp(out, "avtank") == 0, "empty unitName falls back to the ODF");
        ChooseDisplayName(nullptr, 32, "", out, sizeof(out));
        Check(std::strcmp(out, "Unit") == 0, "nothing readable reads Unit");
        ChooseDisplayName("Ta\x01nk\x7F", 32, "x", out, sizeof(out));
        Check(std::strcmp(out, "Ta nk") == 0, "control bytes become spaces");
        const char unterminated[4] = { 'A', 'B', 'C', 'D' };
        ChooseDisplayName(unterminated, sizeof(unterminated), "x", out, sizeof(out));
        Check(std::strcmp(out, "ABCD") == 0, "reads no further than the field size");
    }

    void TestFormat()
    {
        char out[64];
        FormatEntry(Make(0, 4, "Tank"), kFullNameChars, out, sizeof(out));
        Check(std::strcmp(out, "F1 4xTank") == 0, "group 0 is F1, count and name");
        FormatEntry(Make(2, 3, "Tank", true), kFullNameChars, out, sizeof(out));
        Check(std::strcmp(out, "F3 3xTank+") == 0, "mixed group gets +");
        FormatEntry(Make(6, 12, "Assault Tank"), 6, out, sizeof(out));
        Check(std::strcmp(out, "F7 12xAssau.") == 0, "long name shortened with a dot");
        FormatEntry(Make(1, 2, "Big Gun Tank"), 5, out, sizeof(out));
        Check(std::strcmp(out, "F2 2xBig.") == 0, "no space left before the dot");
        FormatEntry(Make(1, 2, "Bomber", true), 0, out, sizeof(out));
        Check(std::strcmp(out, "F2 2+") == 0, "name limit 0 drops the name");
        Check(FormatEntry(Make(0, 4, "Tank"), 16, out, 4) == 0 && out[0] == '\0', "too small a buffer writes nothing");
    }

    void TestBuild()
    {
        const StripGroup groups[] = { Make(0, 4, "Tank"), Make(1, 2, "Bomber"), Make(4, 1, "Turret") };
        char out[kTextBufferSize];
        BuildStripText(groups, 3, kFullNameChars, 3, out, sizeof(out));
        Check(std::strcmp(out, "F1 4xTank  F2 2xBomber  F5 1xTurret") == 0, "entries joined");
        BuildStripText(groups, 3, kFullNameChars, 2, out, sizeof(out));
        Check(std::strcmp(out, "F1 4xTank  F2 2xBomber  ...") == 0, "left-out groups marked");
        Check(BuildStripText(groups, 3, kFullNameChars, 0, out, sizeof(out)) == 0, "no entries, no text");
        Check(BuildStripText(groups, 3, kFullNameChars, 3, out, 12) == 0 && out[0] == '\0', "overflow writes nothing");
    }

    void TestFit()
    {
        const StripGroup groups[] = { Make(0, 4, "Heavy Assault Tank"), Make(1, 2, "Bomber"),
                                      Make(4, 1, "Turret", true) };
        char out[kTextBufferSize];
        FitResult fit = FitStrip(groups, 3, 2000, FakeMeasure, out, sizeof(out));
        Check(fit.fits && fit.entries == 3 && fit.nameLimit == kFullNameChars, "wide budget keeps 16-char names");
        Check(std::strstr(out, "Heavy Assault T.") != nullptr, "18-char name cut to 16");

        fit = FitStrip(groups, 3, 8 * 40, FakeMeasure, out, sizeof(out));
        Check(fit.fits && fit.entries == 3 && fit.nameLimit < kFullNameChars, "narrower budget shortens names");
        Check(fit.width <= 8 * 40, "fits the budget");

        fit = FitStrip(groups, 3, 8 * 12, FakeMeasure, out, sizeof(out));
        Check(fit.fits && fit.entries < 3 && fit.nameLimit == 0, "tight budget drops groups");
        Check(std::strstr(out, "...") != nullptr, "dropped groups marked");

        fit = FitStrip(groups, 3, 8, FakeMeasure, out, sizeof(out));
        Check(!fit.fits && out[0] == '\0', "nothing fits: no text");
        Check(!FitStrip(groups, 0, 1000, FakeMeasure, out, sizeof(out)).fits, "no groups: nothing");
    }

    // Points as FUN_005c6cf0 builds them at scale s for width W.
    void StockPoints(int W, double s, int (&p)[kGaugePointCount * 2])
    {
        const int scrapX = W / 2 - static_cast<int>(88 * s);
        const int pilotX = W / 2;
        const int top = static_cast<int>(5 * s);
        const int title = top + static_cast<int>(5 * s);
        const int value = top + static_cast<int>(9 * s) + static_cast<int>(5 * s);
        const int pts[] = { scrapX + static_cast<int>(50 * s), title, scrapX + static_cast<int>(50 * s), value,
                            pilotX + static_cast<int>(40 * s), title, pilotX + static_cast<int>(40 * s), value,
                            scrapX, top, pilotX, top };
        for (size_t i = 0; i < kGaugePointCount * 2; ++i)
            p[i] = pts[i];
    }

    void TestGaugeAndLayout()
    {
        const StripGroup groups[] = { Make(0, 4, "Tank"), Make(1, 2, "Bomber"), Make(4, 1, "Turret") };
        struct Case { int w, h; double s; int textH; };
        const Case cases[] = { { 640, 480, 1.0, 10 }, { 1280, 720, 1.0, 12 }, { 1920, 1080, 1.5, 16 },
                               { 2560, 1440, 2.0, 20 }, { 3840, 2160, 3.0, 30 } };
        for (const Case& c : cases)
        {
            int pts[kGaugePointCount * 2];
            StockPoints(c.w, c.s, pts);
            const double s = ScaleFromPoints(pts);
            Check(s >= c.s && s < c.s + 0.3, "scale recovered from the stock points, never low");
            const Rect gauge = GaugeRectFromPoints(pts, c.textH);
            // The stock plates: scrap at W/2-88s, pilot at W/2, 90x32 design each.
            Check(gauge.x1 <= c.w / 2 - static_cast<int>(88 * c.s) && gauge.x2 >= c.w / 2 + static_cast<int>(90 * c.s),
                  "gauge rect covers both plates horizontally");
            Check(gauge.y2 >= static_cast<int>(37 * c.s), "gauge rect covers the plates vertically");

            auto measure = [&](const char* t, int& w, int& h) {
                w = static_cast<int>(std::strlen(t)) * c.textH * 6 / 10;
                h = c.textH;
                return true;
            };
            char out[kTextBufferSize];
            const Layout layout = ChooseLayout(groups, 3, c.w, c.h, gauge, c.textH, measure, out, sizeof(out));
            Check(layout.placement != Placement::None, "strip placed at every resolution");
            Check(!Overlaps(layout.panel, gauge), "strip never overlaps the gauge");
            Check(layout.panel.x1 >= 0 && layout.panel.x2 <= c.w && layout.panel.y1 >= 0 && layout.panel.y2 <= c.h / 3,
                  "strip on screen, in the top third");
            Check(layout.fit.entries == 3, "all three groups shown");
        }

        // 640x480 with long names: no room on the right, so it goes below.
        int pts[kGaugePointCount * 2];
        StockPoints(640, 1.0, pts);
        const Rect gauge = GaugeRectFromPoints(pts, 10);
        const StripGroup longGroups[] = { Make(0, 9, "Heavy Assault Tank"), Make(1, 9, "Rocket Tank Mk2"),
                                          Make(2, 9, "Mobile Artillery"), Make(3, 9, "Bomber"),
                                          Make(5, 9, "Scout", true), Make(6, 9, "Turret") };
        auto measure = [](const char* t, int& w, int& h) {
            w = static_cast<int>(std::strlen(t)) * 6;
            h = 10;
            return true;
        };
        char out[kTextBufferSize];
        const Layout layout = ChooseLayout(longGroups, 6, 640, 480, gauge, 10, measure, out, sizeof(out));
        Check(layout.placement == Placement::BelowGauge, "crowded small screen: below the gauge");
        Check(!Overlaps(layout.panel, gauge) && layout.panel.x2 <= 640, "below placement is clear and on screen");

        // Legacy layout: plates stacked at the top left, scale reads high.
        int legacy[kGaugePointCount * 2] = { 171, 11, 171, 21, 171, 38, 171, 48, 166, 0, 166, 34 };
        const Rect legacyGauge = GaugeRectFromPoints(legacy, 10);
        Check(legacyGauge.x1 <= 166 && legacyGauge.y1 <= 0 && legacyGauge.y2 >= 58, "legacy block covered");
        const Layout legacyLayout = ChooseLayout(longGroups, 3, 1280, 720, legacyGauge, 10, measure, out, sizeof(out));
        Check(legacyLayout.placement == Placement::RightOfGauge && !Overlaps(legacyLayout.panel, legacyGauge),
              "legacy: right of the block");

        const Rect est = EstimatedStockGaugeRect(1920, 1080);
        Check(est.x1 < 960 && est.x2 > 960 && est.y2 > 37, "estimated stock gauge straddles the centre");

        Check(ChooseLayout(groups, 0, 1280, 720, gauge, 10, measure, out, sizeof(out)).placement == Placement::None,
              "no groups: nothing placed");
    }
}

int main()
{
    TestSummarize();
    TestDisplayName();
    TestFormat();
    TestBuild();
    TestFit();
    TestGaugeAndLayout();
    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "group_strip_policy_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("group_strip_policy_tests: all checks passed\n");
    return 0;
}
