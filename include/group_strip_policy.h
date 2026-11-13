#pragma once
// group_strip_policy.h
// Pure rules for [Gameplay] GroupStrip, the HUD row that lists the F1-F7
// unit groups (BZCC-style), e.g. "F1 4xTank  F2 2xBomber  F5 1xTurret".
// No Windows or engine calls, so tests/group_strip_policy_tests.cpp can run
// them directly. The engine side is src/patches/group_strip.cpp; the
// behaviour and evidence are in Docs/PRODUCER_RALLY_POINTS.md ("Group strip").

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
    namespace GroupStripPolicy
    {
        // Groups 0-6 are the keyed ones: stock input.map binds
        // group_select_0..6 to F1-F7 (see auto_group_policy.h), so group n is
        // shown as F(n+1). Groups 7-9 have no key and are never shown.
        constexpr int kKeyedGroupCount = 7;
        // 0x16C bytes per stored group (ControlPanel, FUN_004a6f00).
        constexpr int kGroupCapacity = 0x16C / 4;
        // GameObjectClass::unitName is char[0x20] (FUN_004e0450 line 89 reads
        // it with FUN_004cbc10, which passes 0x20 to FUN_00589a10).
        constexpr size_t kNameBufferSize = 0x20 + 1;
        constexpr size_t kTextBufferSize = 256;
        // Longest name a strip shows before it starts shortening names.
        constexpr size_t kFullNameChars = 16;
        constexpr char kEntrySeparator[] = "  ";
        constexpr char kOverflowMark[] = "  ...";

        // One keyed group as the strip shows it.
        struct StripGroup
        {
            int group = -1;      // 0..6
            int liveCount = 0;   // members whose handle still resolves
            bool mixed = false;  // a live member of another class than the first
            char name[kNameBufferSize] = {}; // the first live member's display name
        };

        // What the engine side read for one member.
        struct MemberInfo
        {
            uintptr_t classKey = 0;              // GameObjectClass*, the "same type" key
            char name[kNameBufferSize] = {};     // display name (unitName, else ODF)
        };

        // Copies the printable part of `src` (at most srcMax bytes, stopping at
        // the first NUL) into out, trimming leading/trailing spaces. Bytes
        // below 0x20 and 0x7F become spaces so a corrupt name cannot inject
        // control codes into the HUD text.
        inline void CopyPrintable(const char* src, size_t srcMax, char* out, size_t outSize)
        {
            if (!out || outSize == 0)
                return;
            out[0] = '\0';
            if (!src)
                return;
            size_t n = 0;
            bool started = false;
            for (size_t i = 0; i < srcMax && src[i] != '\0' && n + 1 < outSize; ++i)
            {
                char c = src[i];
                const unsigned char u = static_cast<unsigned char>(c);
                if (u < 0x20 || u == 0x7F)
                    c = ' ';
                if (!started && c == ' ')
                    continue;
                started = true;
                out[n++] = c;
            }
            while (n > 0 && out[n - 1] == ' ')
                --n;
            out[n] = '\0';
        }

        // The label of one member: its ODF unitName, else its ODF file name,
        // else "Unit".
        inline void ChooseDisplayName(const char* unitName, size_t unitNameMax, const char* odf,
                                      char* out, size_t outSize)
        {
            CopyPrintable(unitName, unitNameMax, out, outSize);
            if (out && outSize != 0 && out[0] == '\0')
                CopyPrintable(odf, 16, out, outSize);
            if (out && outSize != 0 && out[0] == '\0')
                CopyPrintable("Unit", 4, out, outSize);
        }

        // Walks one stored group. resolve(handle, MemberInfo&) returns false
        // for a dead handle (not counted, like stock SelectGroup
        // FUN_004a6dd0 lines 14-24) and otherwise fills the member's class and
        // name. The first live member names the group; any later live member
        // of another class marks it mixed.
        template <typename Resolve>
        StripGroup SummarizeGroup(int group, const uint32_t* handles, int storedCount, Resolve&& resolve)
        {
            StripGroup out;
            out.group = group;
            if (!handles || storedCount <= 0)
                return out;
            if (storedCount > kGroupCapacity)
                storedCount = kGroupCapacity;
            uintptr_t firstClass = 0;
            for (int i = 0; i < storedCount; ++i)
            {
                if (handles[i] == 0)
                    continue;
                MemberInfo info;
                if (!resolve(handles[i], info))
                    continue;
                info.name[kNameBufferSize - 1] = '\0';
                if (out.liveCount == 0)
                {
                    firstClass = info.classKey;
                    std::memcpy(out.name, info.name, sizeof(out.name));
                }
                else if (info.classKey != firstClass)
                {
                    out.mixed = true;
                }
                ++out.liveCount;
            }
            return out;
        }

        // Writes one entry: "F<n> <count>x<name>[+]". nameLimit caps the name
        // length; a longer name keeps nameLimit-1 characters and a '.'.
        // nameLimit 0 leaves the name out ("F1 4", "F3 3+"). Returns the
        // length written (0 when it does not fit in outSize).
        inline size_t FormatEntry(const StripGroup& g, size_t nameLimit, char* out, size_t outSize)
        {
            if (!out || outSize == 0)
                return 0;
            out[0] = '\0';
            char name[kNameBufferSize] = {};
            size_t len = 0;
            while (len < sizeof(name) - 1 && g.name[len] != '\0')
                ++len;
            if (nameLimit > sizeof(name) - 1)
                nameLimit = sizeof(name) - 1;
            if (nameLimit != 0 && len > 0)
            {
                if (len > nameLimit)
                {
                    size_t keep = nameLimit > 1 ? nameLimit - 1 : 0;
                    while (keep > 0 && g.name[keep - 1] == ' ')
                        --keep;
                    std::memcpy(name, g.name, keep);
                    name[keep] = '.';
                    name[keep + 1] = '\0';
                }
                else
                {
                    std::memcpy(name, g.name, len);
                    name[len] = '\0';
                }
            }
            const int written = name[0] != '\0'
                ? std::snprintf(out, outSize, "F%d %dx%s%s", g.group + 1, g.liveCount, name, g.mixed ? "+" : "")
                : std::snprintf(out, outSize, "F%d %d%s", g.group + 1, g.liveCount, g.mixed ? "+" : "");
            if (written < 0 || static_cast<size_t>(written) >= outSize)
            {
                out[0] = '\0';
                return 0;
            }
            return static_cast<size_t>(written);
        }

        // Joins the first `entries` groups with kEntrySeparator, adding
        // kOverflowMark when groups were left out. Returns the length (0 when
        // nothing fits).
        inline size_t BuildStripText(const StripGroup* groups, size_t count, size_t nameLimit, size_t entries,
                                     char* out, size_t outSize)
        {
            if (!out || outSize == 0)
                return 0;
            out[0] = '\0';
            if (!groups || entries == 0)
                return 0;
            if (entries > count)
                entries = count;
            size_t used = 0;
            for (size_t i = 0; i < entries; ++i)
            {
                char entry[64];
                const size_t n = FormatEntry(groups[i], nameLimit, entry, sizeof(entry));
                const size_t sep = i == 0 ? 0 : sizeof(kEntrySeparator) - 1;
                if (n == 0 || used + sep + n + 1 > outSize)
                {
                    out[0] = '\0';
                    return 0;
                }
                if (sep)
                    std::memcpy(out + used, kEntrySeparator, sep);
                std::memcpy(out + used + sep, entry, n);
                used += sep + n;
            }
            if (entries < count)
            {
                const size_t mark = sizeof(kOverflowMark) - 1;
                if (used + mark + 1 > outSize)
                {
                    out[0] = '\0';
                    return 0;
                }
                std::memcpy(out + used, kOverflowMark, mark);
                used += mark;
            }
            out[used] = '\0';
            return used;
        }

        struct FitResult
        {
            bool fits = false;
            int width = 0;
            int height = 0;
            size_t entries = 0;
            size_t nameLimit = 0;
        };

        // Fits the strip into budgetPx: first every group with names cut to
        // 16, 10, 6 and then 0 characters, then fewer groups (names left out)
        // with "..." marking the rest. measure(text, w, h) gives the drawn
        // size in pixels and returns false on failure. `out` holds the
        // chosen text when fits is true.
        template <typename Measure>
        FitResult FitStrip(const StripGroup* groups, size_t count, int budgetPx, Measure&& measure,
                           char* out, size_t outSize)
        {
            FitResult result;
            if (!groups || count == 0 || budgetPx <= 0 || !out || outSize == 0)
                return result;
            const size_t limits[] = { kFullNameChars, 10, 6, 0 };
            auto tryFit = [&](size_t limit, size_t entries) {
                if (BuildStripText(groups, count, limit, entries, out, outSize) == 0)
                    return false;
                int w = 0, h = 0;
                if (!measure(out, w, h) || w <= 0 || w > budgetPx)
                    return false;
                result.fits = true;
                result.width = w;
                result.height = h;
                result.entries = entries < count ? entries : count;
                result.nameLimit = limit;
                return true;
            };
            for (const size_t limit : limits)
                if (tryFit(limit, count))
                    return result;
            for (size_t entries = count - 1; entries > 0; --entries)
                if (tryFit(0, entries))
                    return result;
            out[0] = '\0';
            return FitResult{};
        }

        // ---- placement -----------------------------------------------------

        struct Rect
        {
            int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        };

        // The six scrap/pilot layout points the stock gauge draws at (x, y
        // pairs, the ScrapHud*Point rows): scrap title, scrap value, pilot
        // title, pilot value, scrap plate, pilot plate. Built by
        // FUN_005c6cf0 and drawn by FUN_005c6f70; legacy layout and the
        // mission bridge move them, so the strip reads them live.
        constexpr size_t kGaugePointCount = 6;
        constexpr size_t kScrapValuePoint = 1;
        constexpr size_t kScrapPlatePoint = 4;
        constexpr size_t kPilotPlatePoint = 5;
        // Plate sprite size in design units: scrap_panel and pilot_panel are
        // 180 x 64 in spritea.st and FUN_005c6f70 lines 50-52 / 75-77 draw
        // them at (w * scale / 2, h * scale / 2).
        constexpr double kPlateDesignW = 90.0;
        constexpr double kPlateDesignH = 32.0;
        // FUN_005c6cf0: scrap plate y = 10*s/2 (line 22, stored line 47) and
        // scrap value y = that + 18*s/2 + 10*s/2 (line 38), so the drop is 14*s.
        constexpr double kStockValueDrop = 14.0;
        // Half-width allowed for a gauge string around its x (stock centres
        // them; legacy draws them left-aligned from x).
        constexpr double kTextDesignHalfW = 40.0;

        inline double ClampScale(double s)
        {
            return s < 0.25 ? 0.25 : (s > 16.0 ? 16.0 : s);
        }

        // HUD scale from the live points: value drop / 14. The drop is the sum
        // of two truncated terms (9s and 5s), so it can read up to 2 px short;
        // adding those 2 px back makes the estimate never smaller than the
        // real scale. Legacy layout reads high (21/14), which only makes the
        // reserved gauge area bigger.
        inline double ScaleFromPoints(const int (&points)[kGaugePointCount * 2])
        {
            const int drop = points[kScrapValuePoint * 2 + 1] - points[kScrapPlatePoint * 2 + 1];
            return drop > 0 ? ClampScale((drop + 2) / kStockValueDrop) : 1.0;
        }

        inline int Round(double v)
        {
            return static_cast<int>(v < 0 ? v - 0.5 : v + 0.5);
        }

        // Screen area the scrap/pilot gauge can cover. Each plate is reserved
        // 90 x 32 design units from its point; the scrap plate is reserved
        // twice that width because in the alternate command-menu layout
        // (FUN_005c6f70 lines 72-74) the pilot plate is drawn right after it
        // instead of at its own point. Each string gets +/-40 units around its
        // x and textH below its y.
        inline Rect GaugeRectFromPoints(const int (&points)[kGaugePointCount * 2], int textH)
        {
            const double s = ScaleFromPoints(points);
            Rect r;
            bool any = false;
            auto add = [&](int x1, int y1, int x2, int y2) {
                if (!any)
                {
                    r = { x1, y1, x2, y2 };
                    any = true;
                    return;
                }
                if (x1 < r.x1) r.x1 = x1;
                if (y1 < r.y1) r.y1 = y1;
                if (x2 > r.x2) r.x2 = x2;
                if (y2 > r.y2) r.y2 = y2;
            };
            const int plateW = Round(kPlateDesignW * s);
            const int plateH = Round(kPlateDesignH * s);
            const int halfText = Round(kTextDesignHalfW * s);
            for (size_t p = 0; p < kGaugePointCount; ++p)
            {
                const int x = points[p * 2];
                const int y = points[p * 2 + 1];
                if (p == kScrapPlatePoint)
                    add(x, y, x + 2 * plateW, y + plateH);
                else if (p == kPilotPlatePoint)
                    add(x, y, x + plateW, y + plateH);
                else
                    add(x - halfText, y, x + halfText, y + (textH > 0 ? textH : plateH / 2));
            }
            return r;
        }

        // Where the stock layout would put the gauge when its points cannot
        // be read: FUN_005c6cf0 lines 20/34/39 put the plates at W/2 - 88s and
        // W/2, 5s down. The scale is not known then, so it assumes
        // max(1, H/480), larger than the stock HUD scale at common sizes.
        inline Rect EstimatedStockGaugeRect(int viewW, int viewH)
        {
            const double s = ClampScale(viewH > 480 ? viewH / 480.0 : 1.0);
            Rect r;
            r.x1 = viewW / 2 - Round(88.0 * s);
            r.y1 = 0;
            r.x2 = viewW / 2 + Round(92.0 * s);
            r.y2 = Round((5.0 + kPlateDesignH) * s);
            return r;
        }

        enum class Placement
        {
            None,
            RightOfGauge, // same top as the gauge, after its right edge
            BelowGauge,   // centred under the gauge
        };

        struct Spacing
        {
            int margin = 4; // from the screen edges
            int gap = 6;    // from the gauge
            int pad = 3;    // text inside the panel
        };

        // Scales the spacing with the text height so 640x480 and 4K both look
        // right.
        inline Spacing SpacingFor(int viewW, int textH)
        {
            Spacing sp;
            sp.margin = viewW / 320 > 4 ? viewW / 320 : 4;
            sp.gap = textH / 2 > 6 ? textH / 2 : 6;
            sp.pad = textH / 4 > 3 ? textH / 4 : 3;
            return sp;
        }

        struct Layout
        {
            Placement placement = Placement::None;
            Rect panel;
            int textX = 0, textY = 0;
            FitResult fit;
        };

        // Chooses the strip text and position. Right of the gauge when every
        // group fits there with names of at least 6 characters; otherwise
        // centred below it at whatever the full screen width allows. Below
        // must stay in the top third of the screen. `out` holds the text.
        template <typename Measure>
        Layout ChooseLayout(const StripGroup* groups, size_t count, int viewW, int viewH, const Rect& gauge,
                            int textH, Measure&& measure, char* out, size_t outSize)
        {
            Layout layout;
            if (!groups || count == 0 || viewW <= 0 || viewH <= 0)
                return layout;
            const Spacing sp = SpacingFor(viewW, textH);

            const int rightX1 = gauge.x2 + sp.gap;
            const int rightBudget = viewW - sp.margin - rightX1 - 2 * sp.pad;
            if (rightBudget > 0)
            {
                FitResult fit = FitStrip(groups, count, rightBudget, measure, out, outSize);
                if (fit.fits && fit.entries == count && fit.nameLimit >= 6)
                {
                    layout.placement = Placement::RightOfGauge;
                    layout.fit = fit;
                    const int top = gauge.y1 > sp.margin / 2 ? gauge.y1 : sp.margin / 2;
                    layout.panel = { rightX1, top, rightX1 + fit.width + 2 * sp.pad,
                                     top + fit.height + 2 * sp.pad };
                    layout.textX = rightX1 + sp.pad;
                    layout.textY = top + sp.pad;
                    return layout;
                }
            }

            const int belowBudget = viewW - 2 * sp.margin - 2 * sp.pad;
            const FitResult fit = FitStrip(groups, count, belowBudget, measure, out, outSize);
            if (!fit.fits)
                return Layout{};
            const int w = fit.width + 2 * sp.pad;
            const int h = fit.height + 2 * sp.pad;
            int x1 = (gauge.x1 + gauge.x2) / 2 - w / 2;
            if (x1 + w > viewW - sp.margin)
                x1 = viewW - sp.margin - w;
            if (x1 < sp.margin)
                x1 = sp.margin;
            const int y1 = gauge.y2 + sp.gap;
            if (y1 + h > viewH / 3)
            {
                out[0] = '\0';
                return Layout{};
            }
            layout.placement = Placement::BelowGauge;
            layout.fit = fit;
            layout.panel = { x1, y1, x1 + w, y1 + h };
            layout.textX = x1 + sp.pad;
            layout.textY = y1 + sp.pad;
            return layout;
        }

        inline bool Overlaps(const Rect& a, const Rect& b)
        {
            return a.x1 < b.x2 && b.x1 < a.x2 && a.y1 < b.y2 && b.y1 < a.y2;
        }
    }
}
