#pragma once
#include "hud_feedback_policy.h"
#include <vector>

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

    namespace DamageShape
    {
        inline bool Overlaps(const Rect& a, const Rect& b)
        {
            return a.left <= b.right && b.left <= a.right && a.top <= b.bottom && b.top <= a.bottom;
        }

        // Appends `r` minus everything already in `all`, as disjoint pieces.
        inline void AddDisjoint(std::vector<Rect>& all, const Rect& r)
        {
            if (r.left > r.right || r.top > r.bottom) return;
            std::vector<Rect> pieces{r};
            for (const Rect& cut : all)
            {
                for (size_t i = 0; i < pieces.size();)
                {
                    const Rect p = pieces[i];
                    if (!Overlaps(p, cut)) { ++i; continue; }
                    pieces[i] = pieces.back();
                    pieces.pop_back();
                    if (p.top < cut.top) pieces.push_back({p.left, p.top, p.right, cut.top - 1, p.color});
                    if (p.bottom > cut.bottom) pieces.push_back({p.left, cut.bottom + 1, p.right, p.bottom, p.color});
                    const int top = std::max(p.top, cut.top), bottom = std::min(p.bottom, cut.bottom);
                    if (p.left < cut.left) pieces.push_back({p.left, top, cut.left - 1, bottom, p.color});
                    if (p.right > cut.right) pieces.push_back({cut.right + 1, top, p.right, bottom, p.color});
                }
                if (pieces.empty()) return;
            }
            all.insert(all.end(), pieces.begin(), pieces.end());
        }

        // A path of n (2..16) pixel-space centres drawn as abutting strips:
        // each strip spans halfway to its neighbours along the axis the path
        // mostly moves in, and the cross-axis thickness (tw wide, th tall) is
        // one whole-pixel size for the entire path, so it cannot shimmer.
        inline void AddStrips(std::vector<Rect>& all, const Rect& clip, const float* cx, const float* cy,
                              int n, float tw, float th, uint32_t color)
        {
            if (n < 2 || n > 16) return;
            float ex[17], ey[17];
            ex[0] = cx[0] - (cx[1] - cx[0]) * 0.5f;
            ey[0] = cy[0] - (cy[1] - cy[0]) * 0.5f;
            for (int i = 1; i < n; ++i)
            {
                ex[i] = (cx[i - 1] + cx[i]) * 0.5f;
                ey[i] = (cy[i - 1] + cy[i]) * 0.5f;
            }
            ex[n] = cx[n - 1] + (cx[n - 1] - cx[n - 2]) * 0.5f;
            ey[n] = cy[n - 1] + (cy[n - 1] - cy[n - 2]) * 0.5f;
            const int width = std::max(1, static_cast<int>(std::lround(tw)));
            const int height = std::max(1, static_cast<int>(std::lround(th)));
            for (int i = 0; i < n; ++i)
            {
                const int x0 = static_cast<int>(std::lround(ex[i])), x1 = static_cast<int>(std::lround(ex[i + 1]));
                const int y0 = static_cast<int>(std::lround(ey[i])), y1 = static_cast<int>(std::lround(ey[i + 1]));
                Rect r;
                r.color = color;
                if (std::abs(ex[i + 1] - ex[i]) >= std::abs(ey[i + 1] - ey[i]))
                {
                    r.left = std::min(x0, x1);
                    r.right = std::max(x0, x1) - 1;
                    r.top = static_cast<int>(std::lround(cy[i] - height * 0.5f));
                    r.bottom = r.top + height - 1;
                }
                else
                {
                    r.top = std::min(y0, y1);
                    r.bottom = std::max(y0, y1) - 1;
                    r.left = static_cast<int>(std::lround(cx[i] - width * 0.5f));
                    r.right = r.left + width - 1;
                }
                r.left = std::max(r.left, clip.left);
                r.top = std::max(r.top, clip.top);
                r.right = std::min(r.right, clip.right - 1);
                r.bottom = std::min(r.bottom, clip.bottom - 1);
                AddDisjoint(all, r);
            }
        }

        // Joins same-colour rectangles that share a full edge; the union is
        // unchanged, only the rectangle count drops.
        inline void MergeRects(std::vector<Rect>& v)
        {
            for (bool changed = true; changed;)
            {
                changed = false;
                for (size_t i = 0; i < v.size(); ++i)
                    for (size_t j = i + 1; j < v.size();)
                    {
                        Rect& a = v[i];
                        const Rect b = v[j];
                        const bool sameRows = a.top == b.top && a.bottom == b.bottom &&
                            (a.right + 1 == b.left || b.right + 1 == a.left);
                        const bool sameColumns = a.left == b.left && a.right == b.right &&
                            (a.bottom + 1 == b.top || b.bottom + 1 == a.top);
                        if (a.color == b.color && (sameRows || sameColumns))
                        {
                            a.left = std::min(a.left, b.left);
                            a.top = std::min(a.top, b.top);
                            a.right = std::max(a.right, b.right);
                            a.bottom = std::max(a.bottom, b.bottom);
                            v.erase(v.begin() + static_cast<std::ptrdiff_t>(j));
                            changed = true;
                            j = i + 1;
                        }
                        else
                            ++j;
                    }
            }
        }
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
        // The arc is a chain of abutting strips and each tick a short chain of
        // strips, all snapped to whole pixels. Every rectangle in the plan is
        // disjoint from every other one, so translucent alpha never stacks
        // where pieces meet, and the black edge is only the ring outside the
        // fill (never underneath it, which would darken the fill colour).
        std::vector<Rect> all;
        all.reserve(128);
        const uint32_t fillRgb = settings.color & 0xFFFFFFu;
        const uint32_t arcAlpha = static_cast<uint32_t>(alpha);
        {
            float cx[16], cy[16];
            for (int step = 0; step < 16; ++step)
            {
                const float a = angle + (step - 7.5f) * 0.055f;
                cx[step] = static_cast<float>(x) + std::sin(a) * radius * sx;
                cy[step] = static_cast<float>(y) - std::cos(a) * radius * sy;
            }
            DamageShape::AddStrips(all, clip, cx, cy, 16, thickness * sx, thickness * sy, (arcAlpha << 24) | fillRgb);
        }

        const size_t ownerCount = std::min(owners.count, owners.strengths.size());
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
            float cx[4], cy[4];
            for (int step = 0; step < 4; ++step)
            {
                const float r = radius + (-2.0f + 2.0f * step) * scale;
                cx[step] = static_cast<float>(x) + std::sin(a) * r * sx;
                cy[step] = static_cast<float>(y) - std::cos(a) * r * sy;
            }
            DamageShape::AddStrips(all, clip, cx, cy, 4, 1.5f * scale * sx, 1.5f * scale * sy,
                                   (tickAlpha << 24) | fillRgb);
        }

        // Edges last: each is the one-pixel ring around a fill, minus anything
        // already drawn. Fills come first in the plan so a full plan loses
        // edges before it loses any fill.
        const size_t fillEnd = all.size();
        for (size_t i = 0; i < fillEnd; ++i)
        {
            Rect edge = all[i];
            edge.left = std::max(edge.left - 1, clip.left);
            edge.top = std::max(edge.top - 1, clip.top);
            edge.right = std::min(edge.right + 1, clip.right - 1);
            edge.bottom = std::min(edge.bottom + 1, clip.bottom - 1);
            edge.color &= 0xFF000000u;
            DamageShape::AddDisjoint(all, edge);
        }
        DamageShape::MergeRects(all);
        for (const Rect& r : all)
        {
            if (plan.count == plan.rects.size()) break;
            plan.rects[plan.count++] = r;
        }
        return plan;
    }
}
