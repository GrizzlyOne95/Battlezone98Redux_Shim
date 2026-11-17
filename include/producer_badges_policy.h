#pragma once
// producer_badges_policy.h
// Pure rules for [Gameplay] RtsProducerBadges, the HUD badge over each busy
// own producer: the name of the item being built and its build percent. No
// Windows or engine calls, so tests/producer_badges_policy_tests.cpp can run
// them directly. The engine side is src/patches/producer_badges.cpp; the
// evidence is in Docs/PRODUCER_BADGES.md.

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace ProducerBadgesPolicy
    {
        constexpr size_t kMaxBadges = 16;
        // GameObjectClass ODF name: char[8] at class +0x30, not necessarily
        // NUL-terminated.
        constexpr size_t kOdfChars = 8;
        constexpr size_t kLabelChars = 40;

        // Screen pixels from the projected producer position up to the text
        // row of the badge.
        constexpr int kRise = 40;
        // The text row, as the rally label (producer_rally_points.cpp): the
        // panel runs from textY - 1 to textY + 13.
        constexpr int kPanelTop = -1;
        constexpr int kPanelBottom = 13;

        // The stock getter's value as a drawable fraction: [0, 1]; a
        // non-finite value reads as 0.
        inline float ClampProgress(float p)
        {
            if (!std::isfinite(p))
                return 0.0f;
            return p < 0.0f ? 0.0f : (p > 1.0f ? 1.0f : p);
        }

        // Whole percent, rounded down, so 100 shows only when the build is
        // complete.
        inline int ProgressPercent(float progress)
        {
            const int pct = static_cast<int>(ClampProgress(progress) * 100.0f);
            return pct < 0 ? 0 : (pct > 100 ? 100 : pct);
        }

        // "<label> <pct>%" into out (always NUL-terminated); the label is cut
        // first if out is too small.
        inline void FormatBadgeText(const char* label, int pct, char* out, size_t outSize)
        {
            if (!out || outSize == 0)
                return;
            char tail[8];
            size_t t = 0;
            tail[t++] = ' ';
            if (pct < 0)
                pct = 0;
            if (pct > 100)
                pct = 100;
            if (pct >= 100)
                tail[t++] = '1';
            if (pct >= 10)
                tail[t++] = static_cast<char>('0' + (pct / 10) % 10);
            tail[t++] = static_cast<char>('0' + pct % 10);
            tail[t++] = '%';
            const char* src = label ? label : "";
            size_t room = outSize - 1;
            size_t keep = room > t ? room - t : 0;
            size_t i = 0;
            for (; src[i] != '\0' && i < keep; ++i)
                out[i] = src[i];
            for (size_t k = 0; k < t && i < room; ++k)
                out[i++] = tail[k];
            out[i] = '\0';
        }

        // The class being built, as the engine value, or 0 when the producer
        // is idle. Recycler/Factory/Armory: +0x300. ConstructionRig: when
        // +0x3BC is set the class is at +0x370, else +0x300 (the stock getter
        // 0x0049CCF0 makes the same choice).
        inline uint32_t BuildingClass(bool isRig, uint32_t at300, uint32_t at3BC, uint32_t at370)
        {
            if (isRig && at3BC != 0)
                return at370;
            return at300;
        }

        // Copies up to `max` ODF characters (stops at NUL) into out, always
        // NUL-terminated. out must hold max + 1.
        inline void CopyOdf(const char* raw, size_t max, char* out)
        {
            size_t i = 0;
            for (; i < max && raw[i] != '\0'; ++i)
                out[i] = raw[i];
            out[i] = '\0';
        }

        // The badge text: the localized name, else the ODF name, else "?".
        inline void FormatLabel(const char* displayName, const char* odf, char* out, size_t outSize)
        {
            if (!out || outSize == 0)
                return;
            const char* src = (displayName && displayName[0]) ? displayName : ((odf && odf[0]) ? odf : "?");
            size_t i = 0;
            for (; src[i] != '\0' && i + 1 < outSize; ++i)
                out[i] = src[i];
            out[i] = '\0';
        }

        struct Rect
        {
            int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        };

        struct Layout
        {
            Rect panel;       // translucent backing of the name
            int textX = 0;    // centred on this x
            int textY = 0;
        };

        // sx, sy: projected producer position. halfWidth: half the panel
        // width.
        inline Layout ComputeLayout(int sx, int sy, int halfWidth)
        {
            Layout l;
            l.textX = sx;
            l.textY = sy - kRise;
            l.panel = { sx - halfWidth, l.textY + kPanelTop, sx + halfWidth, l.textY + kPanelBottom };
            return l;
        }

        // ---- the badge table ------------------------------------------------

        struct Entry
        {
            uint32_t handle = 0;
            char odf[kOdfChars + 1] = {};
            char label[kLabelChars] = {};
        };

        struct Candidate
        {
            uint32_t handle = 0;
            char odf[kOdfChars + 1] = {};
        };

        enum class Change { Added, Changed, Removed };

        // Reconciles `table` (count entries) with the producers found this
        // scan. Kept: same handle and same ODF (label kept). Same handle with
        // another ODF: label cleared, reported Changed. Missing from `found`:
        // dropped, reported Removed. New: appended while there is room, label
        // cleared, reported Added. `report(Change, const Entry&)` is called
        // after the entry is final (for Removed, the dropped entry). The
        // caller fills every cleared label. Returns the new count.
        template <typename Report>
        size_t Reconcile(Entry (&table)[kMaxBadges], size_t count, const Candidate* found, size_t foundCount,
                         Report report)
        {
            // Drop what vanished (compacting, order kept).
            size_t kept = 0;
            for (size_t i = 0; i < count; ++i)
            {
                bool still = false;
                for (size_t j = 0; j < foundCount; ++j)
                    if (found[j].handle == table[i].handle)
                    {
                        still = true;
                        break;
                    }
                if (!still)
                {
                    report(Change::Removed, table[i]);
                    continue;
                }
                if (kept != i)
                    table[kept] = table[i];
                ++kept;
            }
            count = kept;
            for (size_t j = 0; j < foundCount; ++j)
            {
                Entry* hit = nullptr;
                for (size_t i = 0; i < count; ++i)
                    if (table[i].handle == found[j].handle)
                    {
                        hit = &table[i];
                        break;
                    }
                if (hit)
                {
                    if (std::strncmp(hit->odf, found[j].odf, kOdfChars) != 0)
                    {
                        std::memcpy(hit->odf, found[j].odf, sizeof(hit->odf));
                        hit->label[0] = '\0';
                        report(Change::Changed, *hit);
                    }
                    continue;
                }
                if (count >= kMaxBadges)
                    continue;
                Entry& e = table[count++];
                e = Entry{};
                e.handle = found[j].handle;
                std::memcpy(e.odf, found[j].odf, sizeof(e.odf));
                report(Change::Added, e);
            }
            return count;
        }
    }
}
