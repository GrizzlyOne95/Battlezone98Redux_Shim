#include "producer_badges_policy.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <limits>
#include <vector>

#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::ProducerBadgesPolicy;

namespace
{
    Candidate Cand(uint32_t handle, const char* odf)
    {
        Candidate c;
        c.handle = handle;
        CopyOdf(odf, kOdfChars, c.odf);
        return c;
    }

    void TestProgress()
    {
        Check(ClampProgress(0.5f) == 0.5f, "mid progress kept");
        Check(ClampProgress(-0.2f) == 0.0f, "negative clamps to 0");
        Check(ClampProgress(1.7f) == 1.0f, "over 1 clamps to 1");
        Check(ClampProgress(std::numeric_limits<float>::quiet_NaN()) == 0.0f, "NaN reads as 0");
        Check(ClampProgress(std::numeric_limits<float>::infinity()) == 0.0f, "inf reads as 0");
        Check(ProgressPercent(0.0f) == 0, "0%");
        Check(ProgressPercent(0.456f) == 45, "rounded down");
        Check(ProgressPercent(0.999f) == 99, "100 only when complete");
        Check(ProgressPercent(1.0f) == 100 && ProgressPercent(2.0f) == 100, "clamped to 100");
        {
            char buf[40];
            FormatBadgeText("Tank", 45, buf, sizeof(buf));
            Check(std::strcmp(buf, "Tank 45%") == 0, "label and percent");
            FormatBadgeText("Tank", 0, buf, sizeof(buf));
            Check(std::strcmp(buf, "Tank 0%") == 0, "single digit");
            FormatBadgeText("Tank", 100, buf, sizeof(buf));
            Check(std::strcmp(buf, "Tank 100%") == 0, "three digits");
            char small[8];
            FormatBadgeText("Scavenger", 45, small, sizeof(small));
            Check(std::strcmp(small, "Sca 45%") == 0, "label cut, percent kept");
            FormatBadgeText(nullptr, 7, buf, sizeof(buf));
            Check(std::strcmp(buf, " 7%") == 0, "null label");
        }
    }

    void TestBuildingClass()
    {
        Check(BuildingClass(false, 0, 0, 0) == 0, "idle producer");
        Check(BuildingClass(false, 0x1234, 0, 0x9999) == 0x1234, "producer uses +0x300");
        Check(BuildingClass(true, 0, 0, 0) == 0, "idle rig");
        Check(BuildingClass(true, 0x1234, 0, 0x9999) == 0x1234, "rig without +0x3BC uses +0x300");
        Check(BuildingClass(true, 0x1234, 1, 0x9999) == 0x9999, "rig with +0x3BC uses +0x370");
        Check(BuildingClass(true, 0, 1, 0) == 0, "rig flag set but no class is idle");
    }

    void TestLabel()
    {
        char out[16];
        FormatLabel("Scavenger", "ivscav", out, sizeof(out));
        Check(std::strcmp(out, "Scavenger") == 0, "display name wins");
        FormatLabel("", "ivscav", out, sizeof(out));
        Check(std::strcmp(out, "ivscav") == 0, "ODF fallback");
        FormatLabel(nullptr, nullptr, out, sizeof(out));
        Check(std::strcmp(out, "?") == 0, "last resort");
        FormatLabel("A very long unit name", "x", out, 6);
        Check(std::strcmp(out, "A ver") == 0, "truncates to the buffer");
        char odf[kOdfChars + 1];
        CopyOdf("ivtankXYZ", kOdfChars, odf);
        Check(std::strcmp(odf, "ivtankXY") == 0, "ODF copy stops at 8 chars");
        CopyOdf("ab", kOdfChars, odf);
        Check(std::strcmp(odf, "ab") == 0, "short ODF copied whole");
    }

    void TestLayout()
    {
        const Layout l = ComputeLayout(400, 300, 30);
        Check(l.textX == 400 && l.textY == 300 - kRise, "text above the producer");
        Check(l.panel.x1 == 370 && l.panel.x2 == 430, "panel centred");
        Check(l.panel.y1 == l.textY + kPanelTop && l.panel.y2 == l.textY + kPanelBottom, "panel around the text row");
    }

    struct Log
    {
        int added = 0, changed = 0, removed = 0;
    };

    void TestTable()
    {
        Entry table[kMaxBadges];
        size_t count = 0;
        Log log;
        auto report = [&](Change c, const Entry&) {
            if (c == Change::Added) ++log.added;
            else if (c == Change::Changed) ++log.changed;
            else ++log.removed;
        };

        Candidate a[] = { Cand(1, "ivrecy"), Cand(2, "ivfact") };
        count = Reconcile(table, count, a, 2, report);
        Check(count == 2 && log.added == 2, "two producers added");
        Check(table[0].label[0] == '\0', "new entry has no label yet");
        FormatLabel("Recycler", "", table[0].label, sizeof(table[0].label));

        count = Reconcile(table, count, a, 2, report);
        Check(count == 2 && log.added == 2 && log.changed == 0 && log.removed == 0, "unchanged scan is quiet");
        Check(std::strcmp(table[0].label, "Recycler") == 0, "label kept");

        Candidate b[] = { Cand(1, "ivscav") };
        count = Reconcile(table, count, b, 1, report);
        Check(count == 1 && log.changed == 1 && log.removed == 1, "other item changes label, vanished one dropped");
        Check(table[0].handle == 1 && table[0].label[0] == '\0', "changed ODF clears the label");

        count = Reconcile(table, count, nullptr, 0, report);
        Check(count == 0 && log.removed == 2, "all dropped on an empty scan");

        std::vector<Candidate> many;
        for (uint32_t h = 1; h <= kMaxBadges + 4; ++h)
            many.push_back(Cand(h, "x"));
        count = Reconcile(table, count, many.data(), many.size(), report);
        Check(count == kMaxBadges, "table capped");
    }
}

int main()
{
    TestProgress();
    TestBuildingClass();
    TestLabel();
    TestLayout();
    TestTable();
    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "producer_badges_policy_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("producer_badges_policy_tests: all checks passed\n");
    return 0;
}
