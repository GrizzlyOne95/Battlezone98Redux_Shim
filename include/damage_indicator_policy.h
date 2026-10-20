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
        int attacker = 0; // full generation-bearing handle, never an arena slot
    };

    struct IncomingPulses
    {
        std::array<IncomingPulse, 8> entries{};
        void Reset() { entries = {}; }
        void Add(uint64_t now, int durationMs, int victim, int attacker, Direction direction, float healthLoss)
        {
            if (!victim || !attacker || victim == attacker || !Normalize(direction) ||
                !std::isfinite(healthLoss) || healthLoss <= 0) return;
            IncomingPulse* selected = nullptr;
            for (auto& entry : entries)
            {
                const bool active = entry.victim == victim && entry.pulse.Strength(now, durationMs) > 0;
                if (entry.victim == victim && entry.attacker == attacker)
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
            selected->attacker = attacker;
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

    struct OwnerTicks
    {
        std::array<float, 8> strengths{};
        size_t count = 0;
    };

    struct IncomingArc
    {
        float angle = 0, strength = 0, severity = 0;
        float kick = 0; // freshest hit in this direction; 1 at impact
        OwnerTicks owners;
    };

    struct IncomingArcs
    {
        std::array<IncomingArc, 8> entries{};
        size_t count = 0;
        size_t attackers = 0; // distinct recent damaging owners, all directions
    };

    inline IncomingArcs GroupIncomingArcs(const IncomingPulses& pulses, uint64_t now, int durationMs,
        int victim, const std::array<float, 9>& inverse)
    {
        IncomingArcs result;
        if (!victim) return result;
        for (const auto& pulse : pulses.entries)
        {
            const float strength = pulse.pulse.Strength(now, durationMs);
            float angle = 0;
            if (pulse.victim != victim || !pulse.attacker || strength <= 0 ||
                !ViewBearing(pulse.direction, inverse, angle)) continue;
            IncomingArc* selected = nullptr;
            for (size_t i = 0; i < result.count; ++i)
            {
                // Compare projected bearings, including across the +/-pi seam.
                if (std::cos(angle - result.entries[i].angle) > 0.94f)
                {
                    selected = &result.entries[i];
                    break;
                }
            }
            if (!selected)
            {
                if (result.count == result.entries.size()) continue;
                selected = &result.entries[result.count++];
                selected->angle = angle;
            }
            selected->strength = std::max(selected->strength, strength);
            selected->severity = std::max(selected->severity, pulse.severity);
            selected->kick = std::max(selected->kick, pulse.pulse.Kick(now, durationMs));
            ++result.attackers;
            if (selected->owners.count < selected->owners.strengths.size())
                selected->owners.strengths[selected->owners.count++] = strength;
        }
        return result;
    }

    inline DrawPlan MakeDamageIndicatorPlan(const DamageIndicatorSettings& settings, int x, int y,
        float sx, float sy, Rect clip, float angle, float strength, float severity, const OwnerTicks& owners = {},
        float kick = 0, size_t attackers = 1)
    {
        DrawPlan plan;
        if (!std::isfinite(kick)) kick = 0;
        kick = std::clamp(kick, 0.0f, 1.0f);
        // Pressure: each additional active attacker (up to four) makes every
        // arc heavier and brighter, so being focused reads differently.
        const float pressure = 1.0f + 0.2f * static_cast<float>(std::clamp<size_t>(attackers, 1, 4) - 1);
        if (!std::isfinite(angle) || !std::isfinite(strength) || !std::isfinite(severity) || strength <= 0 ||
            !std::isfinite(sx) || !std::isfinite(sy) || sx < 0.1f || sy < 0.1f || sx > 8 || sy > 8 ||
            clip.left < -65535 || clip.top < -65535 || clip.right > 65535 || clip.bottom > 65535 ||
            clip.right <= clip.left || clip.bottom <= clip.top ||
            x < clip.left || x >= clip.right || y < clip.top || y >= clip.bottom) return plan;
        const float scale = std::clamp(settings.sizePercent, 50, 200) * 0.01f;
        const float weight = std::clamp(severity, 0.0f, 1.0f);
        const int alpha = std::min(255, static_cast<int>(255 * std::clamp(settings.opacity, 25, 100) * 0.01f *
            std::min(strength, 1.0f) * std::min(1.0f, (0.55f + 0.45f * weight) * (pressure + 0.35f * kick))));
        if (!alpha) return plan;
        // Each new hit kicks the arc outward and thicker, then it settles.
        const float radius = 34 * scale * (1.0f + 0.12f * kick);
        const float thickness = (2 + 2 * weight) * scale * pressure * (1.0f + 0.6f * kick);
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
        const size_t ownerCount = std::min(owners.count, owners.strengths.size());
        // Draw all tick edges before their fills so dense ticks remain clear.
        for (int pass = 0; pass < 2; ++pass)
        for (size_t owner = 0; owner < ownerCount; ++owner)
        {
            const float fade = owners.strengths[owner];
            if (!std::isfinite(fade) || fade <= 0) continue;
            const uint32_t tickAlpha = static_cast<uint32_t>(255 * std::clamp(settings.opacity, 25, 100) *
                0.01f * std::min(fade, 1.0f));
            if (!tickAlpha) continue;
            // One short radial stroke per attacker, spaced along the arc.
            // Same-owner hits update one record, so pellets cannot add ticks.
            const float offset = ownerCount == 1 ? 0 :
                -0.28f + 0.56f * static_cast<float>(owner) / static_cast<float>(ownerCount - 1);
            const float a = angle + offset;
            for (int step = 0; step < 4; ++step)
            {
                const float r = radius + (-2.0f + 2.0f * step) * scale;
                const float px = std::sin(a) * r, py = -std::cos(a) * r;
                const int l = x + static_cast<int>(std::lround((px - 0.75f * scale) * sx));
                const int t = y + static_cast<int>(std::lround((py - 0.75f * scale) * sy));
                const int right = x + static_cast<int>(std::lround((px + 0.75f * scale) * sx));
                const int b = y + static_cast<int>(std::lround((py + 0.75f * scale) * sy));
                const auto add = [&](int left, int top, int rr, int bottom, uint32_t color) {
                    left = std::max(left, clip.left); top = std::max(top, clip.top);
                    rr = std::min(rr, clip.right - 1); bottom = std::min(bottom, clip.bottom - 1);
                    if (left <= rr && top <= bottom && plan.count < plan.rects.size())
                        plan.rects[plan.count++] = {left,top,rr,bottom,color};
                };
                if (pass == 0) add(l-1,t-1,right+1,b+1,tickAlpha << 24);
                else add(l,t,right,b,(tickAlpha << 24) | (settings.color & 0xFFFFFFu));
            }
        }
        return plan;
    }
}
