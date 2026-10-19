#pragma once
#include "hud_feedback_policy.h"

namespace BZROpenShim::HudFeedback
{
    struct DamageIndicatorSettings
    {
        bool enabled = false;
        uint32_t color = 0xFFFF4040u;
        int sizePercent = 100;
        int opacity = 75;
        int durationMs = 600;
    };

    struct Direction { float x = 0, y = 0, z = 0; };

    inline bool Normalize(Direction& d)
    {
        const float length = std::sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
        if (!std::isfinite(length) || length < 0.01f) return false;
        d.x /= length; d.y /= length; d.z /= length;
        return true;
    }

    inline bool ConfirmsIncoming(const DamageSample& s, bool localVictim)
    {
        auto outgoing = s;
        outgoing.localAttacker = localVictim;
        return ConfirmsHit(outgoing);
    }

    struct IncomingPulse
    {
        Pulse pulse;
        Direction direction; // source minus victim at impact, never a tracked object
        float severity = 0;
        int victim = 0;
    };

    struct IncomingPulses
    {
        std::array<IncomingPulse, 8> entries{};
        void Reset() { entries = {}; }
        void Add(uint64_t now, int durationMs, int victim, Direction direction, float healthLoss)
        {
            if (!victim || !Normalize(direction) || !std::isfinite(healthLoss) || healthLoss <= 0) return;
            IncomingPulse* selected = nullptr;
            for (auto& entry : entries)
            {
                const bool active = entry.victim == victim && entry.pulse.Strength(now, durationMs) > 0;
                if (active && entry.direction.x * direction.x + entry.direction.y * direction.y +
                    entry.direction.z * direction.z > 0.94f)
                {
                    selected = &entry;
                    break;
                }
                if (!active && !selected) selected = &entry;
            }
            if (!selected)
                selected = &*std::min_element(entries.begin(), entries.end(),
                    [](const auto& a, const auto& b) { return a.pulse.started < b.pulse.started; });
            selected->direction = direction;
            selected->severity = std::clamp(healthLoss / 0.2f, 0.0f, 1.0f);
            selected->victim = victim;
            selected->pulse.Start(now);
        }
    };

    // The released camera record stores its inverse rotation in the first
    // nine floats of MAT_3D at +0x40, column major. Positive view Z is forward.
    // The arcs represent horizontal bearing: front=top, right=right, rear=bottom.
    inline bool ViewBearing(Direction world, const std::array<float, 9>& inverse, float& angle)
    {
        if (!Normalize(world)) return false;
        for (float f : inverse) if (!std::isfinite(f) || std::abs(f) > 1.01f) return false;
        for (int column = 0; column < 3; ++column)
        {
            const int i = column * 3;
            const float length = inverse[i] * inverse[i] + inverse[i + 1] * inverse[i + 1] + inverse[i + 2] * inverse[i + 2];
            if (length < 0.9f || length > 1.1f) return false;
            for (int other = column + 1; other < 3; ++other)
            {
                const int j = other * 3;
                if (std::abs(inverse[i] * inverse[j] + inverse[i + 1] * inverse[j + 1] + inverse[i + 2] * inverse[j + 2]) > 0.05f)
                    return false;
            }
        }
        const float right = inverse[0] * world.x + inverse[3] * world.y + inverse[6] * world.z;
        const float front = inverse[2] * world.x + inverse[5] * world.y + inverse[8] * world.z;
        if (right * right + front * front < 0.0001f) return false;
        angle = std::atan2(right, front);
        return std::isfinite(angle);
    }

    inline DrawPlan MakeDamageIndicatorPlan(const DamageIndicatorSettings& settings, int x, int y,
        float sx, float sy, Rect clip, float angle, float strength, float severity)
    {
        DrawPlan plan;
        if (!std::isfinite(angle) || !std::isfinite(strength) || !std::isfinite(severity) || strength <= 0 ||
            !std::isfinite(sx) || !std::isfinite(sy) || sx < 0.1f || sy < 0.1f || sx > 8 || sy > 8 ||
            clip.left < -65535 || clip.top < -65535 || clip.right > 65535 || clip.bottom > 65535 ||
            clip.right <= clip.left || clip.bottom <= clip.top ||
            x < clip.left || x >= clip.right || y < clip.top || y >= clip.bottom) return plan;
        const float scale = std::clamp(settings.sizePercent, 50, 200) * 0.01f;
        const float weight = std::clamp(severity, 0.0f, 1.0f);
        const int alpha = static_cast<int>(255 * std::clamp(settings.opacity, 25, 100) * 0.01f *
            std::min(strength, 1.0f) * (0.55f + 0.45f * weight));
        if (!alpha) return plan;
        const float radius = 34 * scale;
        const float thickness = (2 + 2 * weight) * scale;
        // Sixteen small quads approximate a 48-degree arc, with a black edge.
        for (int step = 0; step < 16; ++step)
        {
            const float a = angle + (step - 7.5f) * 0.055f;
            const float px = std::sin(a) * radius;
            const float py = -std::cos(a) * radius;
            const int l = x + static_cast<int>(std::lround((px - thickness / 2) * sx));
            const int t = y + static_cast<int>(std::lround((py - thickness / 2) * sy));
            const int r = x + static_cast<int>(std::lround((px + thickness / 2) * sx));
            const int b = y + static_cast<int>(std::lround((py + thickness / 2) * sy));
            const auto add = [&](int left, int top, int right, int bottom, uint32_t color) {
                left = std::max(left, clip.left); top = std::max(top, clip.top);
                right = std::min(right, clip.right - 1); bottom = std::min(bottom, clip.bottom - 1);
                if (left <= right && top <= bottom && plan.count < plan.rects.size())
                    plan.rects[plan.count++] = {left, top, right, bottom, color};
            };
            // Put outlines first so adjacent quads do not erase their color.
            add(l - 1, t - 1, r + 1, b + 1, static_cast<uint32_t>(alpha) << 24);
        }
        for (int step = 0; step < 16; ++step)
        {
            // Recompute the fill separately: clipping an outline must not
            // shrink the fill at the pane boundary.
            const float a = angle + (step - 7.5f) * 0.055f;
            const float px = std::sin(a) * radius, py = -std::cos(a) * radius;
            const int l = std::max(clip.left, x + static_cast<int>(std::lround((px - thickness / 2) * sx)));
            const int t = std::max(clip.top, y + static_cast<int>(std::lround((py - thickness / 2) * sy)));
            const int r = std::min(clip.right - 1, x + static_cast<int>(std::lround((px + thickness / 2) * sx)));
            const int b = std::min(clip.bottom - 1, y + static_cast<int>(std::lround((py + thickness / 2) * sy)));
            if (l <= r && t <= b) plan.rects[plan.count++] = {l,t,r,b,(static_cast<uint32_t>(alpha) << 24) | (settings.color & 0xFFFFFFu)};
        }
        return plan;
    }
}
