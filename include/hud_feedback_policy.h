#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <initializer_list>
#include <string_view>

namespace BZROpenShim::HudFeedback
{
    enum class Style { Stock, Cross, Dot, CrossDot };

    struct Settings
    {
        Style style = Style::Stock;
        uint32_t color = 0xFFFFFFFFu;
        int sizePercent = 100;
        int thickness = 2;
        int opacity = 100;
        bool outline = false;
        bool reactive = false;
        bool hits = false;
        int hitDurationMs = 120;
        uint32_t hitColor = 0xFFFFFFFFu;
        int hitSizePercent = 100;
        int hitOpacity = 100;
        bool NeedsDraw() const { return style != Style::Stock || reactive || hits; }
    };

    inline bool TokenEquals(std::string_view a, std::string_view b)
    {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i)
        {
            const char c = a[i] >= 'A' && a[i] <= 'Z' ? static_cast<char>(a[i] + ('a' - 'A')) : a[i];
            const char d = b[i] >= 'A' && b[i] <= 'Z' ? static_cast<char>(b[i] + ('a' - 'A')) : b[i];
            if (c != d) return false;
        }
        return true;
    }

    inline Style ParseStyle(std::string_view text)
    {
        if (TokenEquals(text, "Cross")) return Style::Cross;
        if (TokenEquals(text, "Dot")) return Style::Dot;
        if (TokenEquals(text, "CrossDot")) return Style::CrossDot;
        return Style::Stock;
    }

    inline uint32_t ParseColor(std::string_view text)
    {
        if (TokenEquals(text, "Green")) return 0xFF40FF40u;
        if (TokenEquals(text, "Cyan")) return 0xFF40FFFFu;
        if (TokenEquals(text, "Amber")) return 0xFFFFC040u;
        return 0xFFFFFFFFu;
    }

    struct DamageSample
    {
        int victim = 0;
        int attacker = 0;
        float before = 0;
        float after = 0;
        bool sameLifetime = false;
        bool localAttacker = false;
        bool weaponSource = false;
        bool singlePlayer = false;
    };

    inline bool ConfirmsHit(const DamageSample& s)
    {
        return s.singlePlayer && s.localAttacker && s.weaponSource && s.sameLifetime &&
            s.victim != 0 && s.attacker != 0 && s.victim != s.attacker &&
            std::isfinite(s.before) && std::isfinite(s.after) &&
            s.before > 0.0f && s.after < s.before;
    }

    // How the local player relates to the stock reticle's current object.
    // None means no classification (no contact, ambiguous or disguised).
    enum class Relation { None, Neutral, Friend, Enemy };

    inline constexpr uint32_t kFriendColor = 0xFF40FF40u;
    inline constexpr uint32_t kEnemyColor = 0xFFFF4040u;

    inline uint32_t RelationColor(Relation relation, uint32_t fallback)
    {
        if (relation == Relation::Friend) return kFriendColor;
        if (relation == Relation::Enemy) return kEnemyColor;
        return fallback;
    }

    struct Pulse
    {
        uint64_t started = 0;
        bool active = false;
        // Distinct victims confirmed recently, so splash hitting several
        // objects reads larger than one. Full handles; never object pointers.
        std::array<int, 8> victims{};
        std::array<uint64_t, 8> victimTicks{};
        void Start(uint64_t now) { started = now; active = true; }
        void Start(uint64_t now, int victim)
        {
            Start(now);
            if (!victim) return;
            size_t slot = 0;
            for (size_t i = 0; i < victims.size(); ++i)
            {
                if (victims[i] == victim) { slot = i; break; }
                if (victimTicks[i] < victimTicks[slot]) slot = i;
            }
            victims[slot] = victim;
            victimTicks[slot] = now;
        }
        void Reset() { active = false; victims = {}; victimTicks = {}; }
        float Strength(uint64_t now, int durationMs) const
        {
            if (!active || now < started || durationMs <= 0) return 0;
            const uint64_t elapsed = now - started;
            if (elapsed >= static_cast<uint64_t>(durationMs)) return 0;
            return std::min(1.0f, 2.0f * (1.0f - static_cast<float>(elapsed) / durationMs));
        }
        // 1 at the confirming hit, easing to 0 over the first 45 percent of
        // the duration: the marker pops outward and settles while it holds.
        float Kick(uint64_t now, int durationMs) const
        {
            if (!active || now < started || durationMs <= 0) return 0;
            const float progress = static_cast<float>(now - started) / durationMs;
            if (progress >= 0.45f) return 0;
            const float k = 1.0f - progress / 0.45f;
            return k * k;
        }
        int Targets(uint64_t now, int durationMs) const
        {
            if (Strength(now, durationMs) <= 0) return 0;
            int count = 0;
            for (size_t i = 0; i < victims.size(); ++i)
                if (victims[i] && victimTicks[i] <= now && now - victimTicks[i] < static_cast<uint64_t>(durationMs)) ++count;
            return std::max(count, 1);
        }
    };

    struct Rect { int left = 0, top = 0, right = 0, bottom = 0; uint32_t color = 0; };
    struct DrawPlan
    {
        std::array<Rect, 96> rects = {};
        size_t count = 0;
        bool replacesStock = false;
    };

    inline DrawPlan MakeDrawPlan(const Settings& settings, int x, int y, float scaleX, float scaleY,
                                Rect clip, bool contact, float hitStrength,
                                Relation relation = Relation::None, float hitKick = 0, int hitTargets = 1)
    {
        DrawPlan plan;
        // Reject corrupt/stale panes and unreasonable scales before rounding.
        if (clip.right <= clip.left || clip.bottom <= clip.top ||
            clip.left < -65535 || clip.top < -65535 || clip.right > 65535 || clip.bottom > 65535 ||
            !std::isfinite(scaleX) || !std::isfinite(scaleY) || scaleX < 0.1f || scaleY < 0.1f ||
            scaleX > 8.0f || scaleY > 8.0f || x < clip.left || x >= clip.right || y < clip.top || y >= clip.bottom)
            return plan;
        const int percent = std::clamp(settings.sizePercent, 50, 200);
        const float sx = scaleX * percent * 0.01f;
        const float sy = scaleY * percent * 0.01f;
        const int width = std::clamp(settings.thickness, 1, 3);
        const uint32_t alpha = static_cast<uint32_t>(std::clamp(settings.opacity, 25, 100) * 255 / 100);
        const auto add = [&](int l, int t, int r, int b, uint32_t color) {
            l = std::max(l, clip.left); t = std::max(t, clip.top);
            r = std::min(r, clip.right - 1); b = std::min(b, clip.bottom - 1);
            if (l <= r && t <= b && plan.count < plan.rects.size())
                plan.rects[plan.count++] = {l, t, r, b, color};
        };
        const auto rect = [&](float l, float t, float r, float b, uint32_t rgb, uint32_t a) {
            const int left = x + static_cast<int>(std::lround(l * sx));
            const int top = y + static_cast<int>(std::lround(t * sy));
            const int right = x + static_cast<int>(std::lround(r * sx)) - 1;
            const int bottom = y + static_cast<int>(std::lround(b * sy)) - 1;
            if (left > right || top > bottom || a == 0) return;
            if (settings.outline) add(left - 1, top - 1, right + 1, bottom + 1, a << 24);
            add(left, top, right, bottom, (a << 24) | (rgb & 0xFFFFFFu));
        };
        const bool reacts = settings.reactive && contact;
        // Reactive feedback tints the reticle by team relation; an
        // unclassified or neutral contact keeps the configured color.
        const uint32_t color = reacts ? RelationColor(relation, settings.color) : settings.color;
        const float gap = reacts ? 1.0f : 3.0f;
        const float half = width * 0.5f;
        if (settings.style == Style::Cross || settings.style == Style::CrossDot)
        {
            rect(-8, -half, -gap, half, color, alpha);
            rect(gap, -half, 8, half, color, alpha);
            rect(-half, -8, half, -gap, color, alpha);
            rect(-half, gap, half, 8, color, alpha);
        }
        if (settings.style == Style::Dot || settings.style == Style::CrossDot)
            rect(-half, -half, half, half, color, alpha);
        // Contact brackets also work with the unmodified stock sprite.
        if (reacts)
        {
            for (const int sign : {-1, 1})
            {
                const float side = sign * 11.0f;
                rect(side - half, -3, side + half, 3, color, alpha);
            }
        }
        if (std::isfinite(hitStrength) && hitStrength > 0)
        {
            const uint32_t hitAlpha = static_cast<uint32_t>(
                std::clamp(settings.hitOpacity, 25, 100) * 255 / 100 * std::min(hitStrength, 1.0f));
            const float hitSize = static_cast<float>(std::clamp(settings.hitSizePercent, 50, 200)) / percent;
            const float kick = std::isfinite(hitKick) ? std::clamp(hitKick, 0.0f, 1.0f) : 0.0f;
            // More targets confirmed in one window (splash, sweeps) read as
            // a bigger, longer marker: up to four targets add 30 percent each.
            const int targets = std::clamp(hitTargets, 1, 4);
            const float boost = 1.0f + 0.3f * static_cast<float>(targets - 1);
            const float push = kick * 5.0f * boost;
            const float tick = half * (1.0f + 0.5f * kick);
            const int steps = 4 + (targets - 1);
            for (const int dx : {-1, 1}) for (const int dy : {-1, 1})
                for (int step = 0; step < steps; ++step)
                {
                    const float px = dx * (11.0f + push + step);
                    const float py = dy * (11.0f + push + step);
                    rect((px - tick) * hitSize, (py - tick) * hitSize,
                         (px + tick) * hitSize, (py + tick) * hitSize, settings.hitColor, hitAlpha);
                }
        }
        plan.replacesStock = settings.style != Style::Stock && plan.count != 0;
        return plan;
    }
}
