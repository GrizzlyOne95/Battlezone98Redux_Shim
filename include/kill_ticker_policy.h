// kill_ticker_policy.h
// BZR Open Shim - kill ticker: engine-independent decisions.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// The kill ticker shows a short "-Tank" / "-Scout" line above the weapon list
// for each object the local player verifiably destroyed. Everything that
// decides whether a kill counts, how lines stack, fade and are placed, and
// how a unit's display name is read from its ODF lives here so the host tests
// exercise the same code the native adapter runs. No engine pointers, no
// allocation in the hot path, no Windows dependency.

#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string>
#include <string_view>

namespace BZROpenShim::KillTicker
{
    // The four released DamageAlloc wrappers, in hud_feedback.cpp's order.
    enum class DamageKind : uint8_t { Building = 0, Craft = 1, Person = 2, Powerup = 3 };

    // One damage application, sampled across the original DamageAlloc call.
    // `before`/`after` are the victim's healthRatio (complete+0x200). The
    // engine's own death test is `ratio <= 0 && ratio != 0`, i.e. strictly
    // negative, so exactly 0.0 is alive.
    struct KillSample
    {
        int victim = 0;
        int attacker = 0;
        float before = 0.0f;
        float after = 0.0f;
        bool sameLifetime = false;  // the victim handle still names the same object afterwards
        bool localAttacker = false; // attacker == local player handle, sampled at damage time
        bool alliedVictim = false;  // victim is on the player's team or an allied team
        DamageKind kind = DamageKind::Craft;
    };

    // Powerups (crates, daywreckers) are depleted, not killed.
    inline bool CountsAsKillTarget(DamageKind kind) { return kind != DamageKind::Powerup; }

    // A verified kill: this exact damage application came from the local
    // player and is the one that took a live victim across the engine's death
    // line. Any later damage to an already-dead object fails `before >= 0`, so
    // the credit goes to whoever landed the killing blow and to nobody else.
    inline bool ConfirmsKill(const KillSample& s)
    {
        return s.localAttacker && s.sameLifetime && !s.alliedVictim && CountsAsKillTarget(s.kind) &&
            s.victim != 0 && s.attacker != 0 && s.victim != s.attacker &&
            std::isfinite(s.before) && std::isfinite(s.after) &&
            s.before >= 0.0f && s.after < 0.0f;
    }

    // Damage that changed the victim's health locally proves this peer
    // simulates that victim's health, so the exact rule above is the whole
    // answer for it.
    inline bool HealthChangedLocally(const KillSample& s)
    {
        return s.sameLifetime && std::isfinite(s.before) && std::isfinite(s.after) && s.before != s.after;
    }

    // ------------------------------------------------------------------
    // Network games: victims this peer does not own.
    //
    // Craft/Building DamageAlloc only change health when the target is not
    // remote (Docs/MP_EXPLOSIVE_AUTHORITY_QUALIFICATION.md), so a remote
    // victim's death arrives later by replication and the exact rule never
    // sees it. Every peer still runs the wrappers for every hit, so this peer
    // sees who hit the victim last. A remote candidate is credited only when:
    //   - the local player's hit is the most recent hit any attacker landed,
    //   - no hit on it changed health here (otherwise the exact rule owns it),
    //   - the victim was still alive here when that hit landed,
    //   - the victim's replicated health is then observed below zero within
    //     kRemoteWindowMs of that hit.
    // A victim that merely disappears (removed, entered a craft, recycled) is
    // never credited, and the object-state 0x200 bit is deliberately not a
    // death signal here: RemoteDelete sets it (0x280) for plain removals.
    // The ticker prefers a missed line to a wrong one.
    // ------------------------------------------------------------------
    inline constexpr uint64_t kRemoteWindowMs = 1500;
    inline constexpr size_t kRemoteCapacity = 32;
    inline constexpr size_t kOdfChars = 8;

    enum class Probe { Alive, Dead, Gone };

    struct RemoteCandidate
    {
        bool inUse = false;
        bool lastHitLocal = false;
        int victim = 0;
        uint64_t lastLocalHitMs = 0;
        char odf[kOdfChars + 1] = {};
    };

    struct ConfirmedKill
    {
        int victim = 0;
        char odf[kOdfChars + 1] = {};
    };

    inline void CopyOdf(char (&out)[kOdfChars + 1], const char* odf)
    {
        size_t i = 0;
        for (; odf && i < kOdfChars && odf[i]; ++i) out[i] = odf[i];
        out[i] = '\0';
    }

    class RemoteCandidates
    {
    public:
        void Reset() { m_entries = {}; }

        // One damage application in a network game. `odf` is only read for
        // a local, non-allied, kill-eligible hit.
        void NoteDamage(const KillSample& s, const char* odf, uint64_t nowMs)
        {
            if (s.victim == 0) return;
            // Already dead here: whatever killed it landed earlier, so this
            // hit can neither earn nor clear the credit.
            if (!std::isfinite(s.before) || s.before < 0.0f) return;
            RemoteCandidate* entry = Find(s.victim);
            if (HealthChangedLocally(s))
            {
                // This peer simulates the victim; the exact rule decides it.
                if (entry) *entry = {};
                return;
            }
            if (!s.localAttacker || s.attacker == 0 || s.attacker == s.victim)
            {
                // Somebody else (or something else) hit it after us.
                if (entry) entry->lastHitLocal = false;
                return;
            }
            if (s.alliedVictim || !CountsAsKillTarget(s.kind)) return;
            if (!entry) entry = Allocate();
            entry->inUse = true;
            entry->victim = s.victim;
            entry->lastHitLocal = true;
            entry->lastLocalHitMs = nowMs;
            CopyOdf(entry->odf, odf);
        }

        // Exact-rule credit for this victim: never credit it twice.
        void Forget(int victim)
        {
            if (RemoteCandidate* entry = Find(victim)) *entry = {};
        }

        // Once per frame. `probe(victim)` reports the victim's current state.
        // Writes up to `capacity` confirmed kills and returns how many.
        template <class ProbeFn>
        size_t Resolve(uint64_t nowMs, ProbeFn&& probe, ConfirmedKill* out, size_t capacity)
        {
            size_t count = 0;
            for (auto& entry : m_entries)
            {
                if (count >= capacity) break; // the rest resolve next frame
                if (!entry.inUse) continue;
                if (nowMs < entry.lastLocalHitMs || nowMs - entry.lastLocalHitMs > kRemoteWindowMs)
                {
                    entry = {};
                    continue;
                }
                const Probe state = probe(entry.victim);
                if (state == Probe::Alive) continue;
                if (state == Probe::Dead && entry.lastHitLocal)
                {
                    out[count].victim = entry.victim;
                    CopyOdf(out[count].odf, entry.odf);
                    ++count;
                }
                entry = {};
            }
            return count;
        }

        size_t Active() const
        {
            size_t n = 0;
            for (const auto& entry : m_entries) n += entry.inUse ? 1u : 0u;
            return n;
        }

    private:
        RemoteCandidate* Find(int victim)
        {
            for (auto& entry : m_entries)
                if (entry.inUse && entry.victim == victim) return &entry;
            return nullptr;
        }

        // A full table evicts the stalest local hit: it is the one least
        // likely to resolve inside the window.
        RemoteCandidate* Allocate()
        {
            RemoteCandidate* oldest = nullptr;
            for (auto& entry : m_entries)
            {
                if (!entry.inUse) return &entry;
                if (!oldest || entry.lastLocalHitMs < oldest->lastLocalHitMs) oldest = &entry;
            }
            *oldest = {};
            return oldest;
        }

        std::array<RemoteCandidate, kRemoteCapacity> m_entries{};
    };

    // ------------------------------------------------------------------
    // The visible feed.
    // ------------------------------------------------------------------
    inline constexpr size_t kMaxLines = 4;
    inline constexpr size_t kNameChars = 31;
    inline constexpr uint64_t kShowMs = 3000;
    inline constexpr uint64_t kFadeMs = 600;
    // A second kill of the same unit type while its line is still young
    // becomes "-Tank x2" instead of another line.
    inline constexpr uint64_t kCoalesceMs = 2000;
    // A line whose clock never started (HUD hidden, pause menu) is dropped
    // rather than shown long after the fact.
    inline constexpr uint64_t kMaxPendingMs = 5000;
    inline constexpr int kMaxCount = 99;

    struct Line
    {
        char name[kNameChars + 1] = {};
        int count = 0;
        uint64_t queuedMs = 0;  // when the kill was credited
        uint64_t shownMs = 0;   // first frame it drew; 0 until then
    };

    inline bool SameName(const char* a, const char* b)
    {
        for (size_t i = 0; i <= kNameChars; ++i)
        {
            char ca = a[i], cb = b[i];
            if (ca >= 'A' && ca <= 'Z') ca = static_cast<char>(ca - 'A' + 'a');
            if (cb >= 'A' && cb <= 'Z') cb = static_cast<char>(cb - 'A' + 'a');
            if (ca != cb) return false;
            if (!ca) return true;
        }
        return true;
    }

    // "-Tank", or "-Tank x3" for coalesced kills. Always NUL-terminated.
    inline void FormatLine(const Line& line, char* out, size_t outSize)
    {
        if (!out || outSize == 0) return;
        if (line.count > 1)
            std::snprintf(out, outSize, "-%s x%d", line.name, line.count);
        else
            std::snprintf(out, outSize, "-%s", line.name);
    }

    class Feed
    {
    public:
        void Reset() { m_count = 0; m_lines = {}; }
        size_t Count() const { return m_count; }
        // Index 0 is the oldest line; Count()-1 the newest.
        const Line& At(size_t index) const { return m_lines[index]; }
        Line& At(size_t index) { return m_lines[index]; }

        void Push(std::string_view name, uint64_t nowMs)
        {
            if (name.empty()) return;
            char copy[kNameChars + 1] = {};
            const size_t n = (std::min)(name.size(), kNameChars);
            for (size_t i = 0; i < n; ++i) copy[i] = name[i];
            if (m_count > 0)
            {
                Line& newest = m_lines[m_count - 1];
                const uint64_t since = newest.shownMs ? newest.shownMs : newest.queuedMs;
                if (SameName(newest.name, copy) && nowMs >= since && nowMs - since < kCoalesceMs)
                {
                    newest.count = (std::min)(newest.count + 1, kMaxCount);
                    // Restart its clock so the bumped count is readable.
                    newest.queuedMs = nowMs;
                    newest.shownMs = 0;
                    return;
                }
            }
            if (m_count == kMaxLines)
            {
                for (size_t i = 1; i < kMaxLines; ++i) m_lines[i - 1] = m_lines[i];
                --m_count;
            }
            Line& line = m_lines[m_count++];
            line = {};
            for (size_t i = 0; i <= kNameChars; ++i) line.name[i] = copy[i];
            line.count = 1;
            line.queuedMs = nowMs;
        }

        // Starts the clock of every line that has not drawn yet. Call on a
        // frame that is about to draw the feed.
        void MarkShown(uint64_t nowMs)
        {
            for (size_t i = 0; i < m_count; ++i)
                if (!m_lines[i].shownMs) m_lines[i].shownMs = nowMs ? nowMs : 1;
        }

        void Expire(uint64_t nowMs)
        {
            size_t kept = 0;
            for (size_t i = 0; i < m_count; ++i)
            {
                const Line& line = m_lines[i];
                const bool expired = line.shownMs
                    ? (nowMs >= line.shownMs && nowMs - line.shownMs >= kShowMs)
                    : (nowMs >= line.queuedMs && nowMs - line.queuedMs >= kMaxPendingMs);
                if (!expired) m_lines[kept++] = line;
            }
            for (size_t i = kept; i < m_count; ++i) m_lines[i] = {};
            m_count = kept;
        }

        // 1 while holding, then linear to 0 over the last kFadeMs.
        static float Opacity(const Line& line, uint64_t nowMs)
        {
            if (!line.shownMs || nowMs <= line.shownMs) return 1.0f;
            const uint64_t age = nowMs - line.shownMs;
            if (age >= kShowMs) return 0.0f;
            const uint64_t fadeStart = kShowMs - kFadeMs;
            if (age <= fadeStart) return 1.0f;
            return 1.0f - static_cast<float>(age - fadeStart) / static_cast<float>(kFadeMs);
        }

    private:
        std::array<Line, kMaxLines> m_lines{};
        size_t m_count = 0;
    };

    // Scales the alpha byte of an ARGB colour.
    inline uint32_t WithOpacity(uint32_t argb, float opacity)
    {
        if (!(opacity > 0.0f)) return argb & 0x00FFFFFFu;
        if (opacity >= 1.0f) return argb;
        const uint32_t alpha = static_cast<uint32_t>(std::lround(static_cast<float>(argb >> 24) * opacity));
        return (argb & 0x00FFFFFFu) | ((alpha > 255u ? 255u : alpha) << 24);
    }

    // ------------------------------------------------------------------
    // Placement. Screen pixels in the HUD viewport, the space both the
    // weapon-list backdrop submit and HudFillRect/HudFadeText use.
    // ------------------------------------------------------------------
    struct Anchor
    {
        bool valid = false;
        int x = 0, y = 0, w = 0, h = 0; // the stock weapon-list backdrop as submitted
    };

    // Without a fresh, plausible weapon-list rectangle the feed sits at the
    // right edge, its lowest line ending this far down the viewport.
    inline constexpr float kFallbackBottomFraction = 0.70f;
    inline constexpr float kFallbackRightMarginFraction = 0.02f;

    // The backdrop must be on screen and in the lower-right quadrant; any
    // other shape means a different HUD layout and the fallback is safer.
    inline bool PlausibleAnchor(const Anchor& a, int viewW, int viewH)
    {
        if (!a.valid || viewW <= 0 || viewH <= 0 || a.w <= 0 || a.h <= 0) return false;
        const int64_t right = static_cast<int64_t>(a.x) + a.w;
        const int64_t bottom = static_cast<int64_t>(a.y) + a.h;
        return a.x >= 0 && a.y >= 0 && right <= viewW && bottom <= viewH &&
            right > viewW / 2 && a.y > viewH / 2;
    }

    struct LineRect
    {
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0; // inclusive backing panel, as HudFillRect takes it
        int textLeft = 0, textTop = 0;      // left-aligned text origin (alignX 0, alignY 0)
    };

    // `fromBottom` 0 is the newest line, directly above the weapon list.
    inline bool ComputeLine(int viewW, int viewH, const Anchor& anchor, float textW, float textH,
                            size_t fromBottom, LineRect& out)
    {
        if (viewW <= 0 || viewH <= 0 || !(textW > 0.0f) || !(textH > 0.0f) ||
            !std::isfinite(textW) || !std::isfinite(textH) || textH > viewH || textW > viewW)
            return false;
        const bool anchored = PlausibleAnchor(anchor, viewW, viewH);
        const int padX = static_cast<int>(std::lround(textH * 0.45f));
        const int padY = static_cast<int>(std::lround(textH * 0.15f));
        const int gap = static_cast<int>(std::lround(textH * 0.35f));
        const int spacing = (std::max)(1, static_cast<int>(std::lround(textH * 0.20f)));
        const int lineH = static_cast<int>(std::ceil(textH)) + 2 * padY;
        const int panelW = static_cast<int>(std::ceil(textW)) + 2 * padX;
        const int right = anchored ? anchor.x + anchor.w
            : viewW - static_cast<int>(std::lround(viewW * kFallbackRightMarginFraction));
        const int bottom = anchored ? anchor.y - gap
            : static_cast<int>(std::lround(viewH * kFallbackBottomFraction));
        const int64_t y2 = static_cast<int64_t>(bottom) - 1 -
            static_cast<int64_t>(fromBottom) * (lineH + spacing);
        const int64_t y1 = y2 - lineH + 1;
        const int64_t x2 = static_cast<int64_t>(right) - 1;
        const int64_t x1 = x2 - panelW + 1;
        if (y1 < 0 || x1 < 0 || y2 >= viewH || x2 >= viewW) return false;
        out.x1 = static_cast<int>(x1);
        out.y1 = static_cast<int>(y1);
        out.x2 = static_cast<int>(x2);
        out.y2 = static_cast<int>(y2);
        out.textLeft = out.x1 + padX;
        out.textTop = out.y1 + padY;
        return true;
    }

    // ------------------------------------------------------------------
    // Display name: [GameObjectClass] unitName from the ODF text.
    // ------------------------------------------------------------------
    inline std::string_view TrimView(std::string_view text)
    {
        while (!text.empty() && (text.front() == ' ' || text.front() == '\t' || text.front() == '\r')) text.remove_prefix(1);
        while (!text.empty() && (text.back() == ' ' || text.back() == '\t' || text.back() == '\r')) text.remove_suffix(1);
        return text;
    }

    inline bool EqualsNoCase(std::string_view a, std::string_view b)
    {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i)
        {
            char ca = a[i], cb = b[i];
            if (ca >= 'A' && ca <= 'Z') ca = static_cast<char>(ca - 'A' + 'a');
            if (cb >= 'A' && cb <= 'Z') cb = static_cast<char>(cb - 'A' + 'a');
            if (ca != cb) return false;
        }
        return true;
    }

    // Keeps characters the HUD font can draw; control bytes become nothing,
    // runs of spaces collapse, and the result is capped at kNameChars.
    inline std::string SanitizeName(std::string_view raw)
    {
        std::string out;
        bool space = false;
        for (const char c : raw)
        {
            const unsigned char u = static_cast<unsigned char>(c);
            if (u < 0x20 || u == 0x7F) continue;
            if (c == ' ')
            {
                if (out.empty() || space) continue;
                space = true;
                out.push_back(' ');
                continue;
            }
            space = false;
            out.push_back(c);
            if (out.size() >= kNameChars) break;
        }
        while (!out.empty() && out.back() == ' ') out.pop_back();
        return out;
    }

    // The value of unitName in [GameObjectClass], quotes removed. Comments
    // (// and ;) outside quotes are ignored; the first occurrence wins.
    // Empty when absent or blank.
    inline std::string ParseUnitName(std::string_view text)
    {
        if (text.size() >= 3 && text.substr(0, 3) == "\xEF\xBB\xBF") text.remove_prefix(3);
        bool inSection = false;
        while (!text.empty())
        {
            const size_t eol = text.find('\n');
            std::string_view line = text.substr(0, eol);
            text = eol == std::string_view::npos ? std::string_view{} : text.substr(eol + 1);
            bool quoted = false;
            for (size_t i = 0; i < line.size(); ++i)
            {
                if (line[i] == '"') quoted = !quoted;
                else if (!quoted && (line[i] == ';' || (line[i] == '/' && i + 1 < line.size() && line[i + 1] == '/')))
                {
                    line = line.substr(0, i);
                    break;
                }
            }
            line = TrimView(line);
            if (line.empty()) continue;
            if (line.front() == '[')
            {
                const size_t close = line.find(']');
                inSection = close != std::string_view::npos &&
                    EqualsNoCase(TrimView(line.substr(1, close - 1)), "GameObjectClass");
                continue;
            }
            if (!inSection) continue;
            const size_t equals = line.find('=');
            if (equals == std::string_view::npos) continue;
            if (!EqualsNoCase(TrimView(line.substr(0, equals)), "unitName")) continue;
            std::string_view value = TrimView(line.substr(equals + 1));
            if (value.size() >= 2 && (value.front() == '"' || value.front() == '\'') && value.back() == value.front())
                value = value.substr(1, value.size() - 2);
            return SanitizeName(value);
        }
        return {};
    }

    // What the line says: the ODF's unitName, else the ODF name itself, so a
    // unit is never reported as something it is not.
    inline std::string DisplayName(std::string_view unitName, std::string_view odf)
    {
        std::string name = SanitizeName(unitName);
        if (name.empty()) name = SanitizeName(odf);
        return name;
    }
}
