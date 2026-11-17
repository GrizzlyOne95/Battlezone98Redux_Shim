// rts_markers_policy.h
// BZR Open Shim - RTS markers: the engine-independent rules behind the ground
// rings (rts_markers.cpp). Header-only and free of Windows and Ogre, so the
// unit tests check the same math the shim runs. See Docs/RTS_MARKERS.md.
//
//  - Ring geometry: a flat band (inner/outer radius) as a triangle strip,
//    sampled at SegmentsFor(radius) points around the circle.
//  - Command pings: which order gets which ping, and how a ping shrinks and
//    fades over its life.
//  - Artillery: the flat-ground maximum range of a gravity shell, shortened
//    by its lifeSpan, and the reach test with a height difference. The reach
//    test is the engine's own discriminant (Mortar 0x0056AF20; see the doc).
#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>

#include "laser_sight_policy.h"

namespace BZROpenShim
{
    namespace RtsMarkers
    {
        // ---- AiCommand values (BZ1 AiCommand enum; Docs/RTS_MARKERS.md) ----
        constexpr int kCmdNone = 0;
        constexpr int kCmdSelect = 1;
        constexpr int kCmdStop = 2;
        constexpr int kCmdGo = 3;
        constexpr int kCmdAttack = 4;
        constexpr int kCmdLast = 26; // CMD_LAY_MINES, the last command

        // ---- Pool layout -----------------------------------------------------
        constexpr size_t kMaxArtilleryRings = 16;
        constexpr size_t kMaxPings = 6;
        constexpr size_t kCursorSlot = kMaxArtilleryRings;
        constexpr size_t kFirstPingSlot = kCursorSlot + 1;
        constexpr size_t kPoolSize = kFirstPingSlot + kMaxPings;

        // ---- Ring geometry ---------------------------------------------------
        constexpr unsigned kMinSegments = 48;
        constexpr unsigned kMaxSegments = 96;
        constexpr float kSegmentLength = 4.0f;  // metres of arc per segment, before the clamp
        constexpr float kLift = 0.4f;           // metres above the sampled terrain
        constexpr float kPi = 3.14159265358979f;

        // Enough segments that a small ring is round and a large one stays
        // within the 96-segment budget.
        inline unsigned SegmentsFor(float radius)
        {
            if (!(radius > 0.0f) || !std::isfinite(radius))
                return kMinSegments;
            const float wanted = std::ceil(2.0f * kPi * radius / kSegmentLength);
            if (wanted <= static_cast<float>(kMinSegments))
                return kMinSegments;
            if (wanted >= static_cast<float>(kMaxSegments))
                return kMaxSegments;
            return static_cast<unsigned>(wanted);
        }

        // Band width: thin on a ping, wider on a long range ring so it still
        // reads from the satellite view.
        inline float RingWidthFor(float radius)
        {
            if (!(radius > 0.0f) || !std::isfinite(radius))
                return 0.5f;
            return std::min(2.5f, std::max(0.5f, 0.5f + radius * 0.006f));
        }

        struct Band
        {
            float inner = 0.0f;
            float outer = 0.0f;
        };

        inline Band RingBand(float radius, float width)
        {
            Band band;
            const float half = std::max(0.0f, width) * 0.5f;
            band.inner = std::max(0.0f, radius - half);
            band.outer = std::max(band.inner, radius + half);
            return band;
        }

        // Strip vertices: an inner/outer pair per point, the first point
        // repeated at the end to close the loop.
        inline unsigned StripVertexCount(unsigned segments)
        {
            return 2u * (segments + 1u);
        }

        // Unit direction of point i around the ring (x, z in sim space).
        // i == segments returns exactly the i == 0 direction, so the strip
        // closes without a seam.
        inline void RingDirection(unsigned i, unsigned segments, float& dx, float& dz)
        {
            if (segments == 0)
            {
                dx = 1.0f;
                dz = 0.0f;
                return;
            }
            const unsigned k = i % segments;
            const float angle = 2.0f * kPi * static_cast<float>(k) / static_cast<float>(segments);
            dx = std::cos(angle);
            dz = std::sin(angle);
        }

        // A vertex's height relative to the ring's node, which sits at the
        // ring centre: the terrain under the vertex plus the lift.
        inline float LocalVertexY(float terrainHeight, float centreY)
        {
            return terrainHeight + kLift - centreY;
        }

        // ---- Colours ---------------------------------------------------------
        struct Colour
        {
            float r = 1.0f;
            float g = 1.0f;
            float b = 1.0f;
            float a = 1.0f;
        };

        constexpr Colour kGoColour = {0.30f, 1.00f, 0.40f, 0.90f};
        constexpr Colour kAttackColour = {1.00f, 0.22f, 0.16f, 0.90f};
        constexpr Colour kNeutralColour = {1.00f, 0.86f, 0.30f, 0.90f};
        constexpr Colour kRangeColour = {0.55f, 0.85f, 1.00f, 0.50f};
        constexpr Colour kReachableColour = {0.30f, 1.00f, 0.40f, 0.85f};
        constexpr Colour kUnreachableColour = {1.00f, 0.25f, 0.20f, 0.85f};

        // ---- Command pings ---------------------------------------------------
        enum class PingKind : uint8_t
        {
            None,
            Go,      // green, shrinks onto the ground point
            Attack,  // red, around the target, follows it
            Neutral, // yellow, any other targeted order
        };

        // `onObject`: the order went through the object broadcaster (a target
        // GameObject) rather than the ground one (a point).
        inline PingKind ClassifyPing(int what, bool onObject)
        {
            if (what <= kCmdStop || what > kCmdLast)
                return PingKind::None; // none, select, stop and unknown values
            if (what == kCmdGo)
                return PingKind::Go;
            if (what == kCmdAttack && onObject)
                return PingKind::Attack;
            return PingKind::Neutral;
        }

        struct PingStyle
        {
            Colour colour;
            float startScale = 1.0f; // of the base radius
            float endScale = 1.0f;
            float duration = 0.0f;   // seconds of sim time
        };

        inline PingStyle StyleFor(PingKind kind)
        {
            PingStyle style;
            switch (kind)
            {
            case PingKind::Go:
                style.colour = kGoColour;
                style.startScale = 1.0f;
                style.endScale = 0.3f;
                style.duration = 0.9f;
                break;
            case PingKind::Attack:
                style.colour = kAttackColour;
                style.startScale = 1.3f;
                style.endScale = 1.0f;
                style.duration = 1.0f;
                break;
            case PingKind::Neutral:
                style.colour = kNeutralColour;
                style.startScale = 1.0f;
                style.endScale = 0.4f;
                style.duration = 0.9f;
                break;
            case PingKind::None:
            default:
                break;
            }
            return style;
        }

        constexpr float kGroundPingRadius = 6.0f;
        constexpr float kDefaultTargetRadius = 6.0f;
        constexpr float kMinTargetRadius = 3.0f;
        constexpr float kMaxTargetRadius = 40.0f;
        constexpr float kTargetRingMargin = 1.0f;

        // The ring around a target: its bounding radius, clamped, plus a
        // margin. Unreadable or nonsense radii take the default.
        inline float TargetRingRadius(float boundingRadius)
        {
            float r = kDefaultTargetRadius;
            if (std::isfinite(boundingRadius) && boundingRadius > 0.0f)
                r = std::min(kMaxTargetRadius, std::max(kMinTargetRadius, boundingRadius));
            return r + kTargetRingMargin;
        }

        struct PingFrame
        {
            float radius = 0.0f;
            float alpha = 0.0f;
            bool alive = false;
        };

        // Ease-out shrink and a smoothstep fade to zero at the end of the
        // ping's life.
        inline PingFrame EvaluatePing(const PingStyle& style, float baseRadius, float age)
        {
            PingFrame frame;
            if (!(style.duration > 0.0f) || !(baseRadius > 0.0f) || !std::isfinite(age))
                return frame;
            if (age < 0.0f)
                age = 0.0f;
            if (age >= style.duration)
                return frame;
            const float t = age / style.duration;
            const float ease = 1.0f - (1.0f - t) * (1.0f - t);
            const float fade = 1.0f - t * t * (3.0f - 2.0f * t);
            frame.radius = baseRadius * (style.startScale + (style.endScale - style.startScale) * ease);
            frame.alpha = style.colour.a * fade;
            frame.alive = frame.radius > 0.0f && frame.alpha > 0.0f;
            return frame;
        }

        // Fixed ping slots: a new ping takes a free slot, else the oldest.
        struct PingSlot
        {
            bool active = false;
            PingKind kind = PingKind::None;
            float age = 0.0f;
            float baseRadius = 0.0f;
            float pos[3] = {0.0f, 0.0f, 0.0f}; // sim space; refreshed while following
            uint32_t targetHandle = 0;         // 0: a ground point
        };

        template <size_t N>
        struct PingQueue
        {
            PingSlot slots[N];

            size_t Push(const PingSlot& ping)
            {
                size_t pick = 0;
                bool found = false;
                for (size_t i = 0; i < N; ++i)
                {
                    if (!slots[i].active)
                    {
                        pick = i;
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    for (size_t i = 1; i < N; ++i)
                        if (slots[i].age > slots[pick].age)
                            pick = i;
                }
                slots[pick] = ping;
                slots[pick].active = true;
                slots[pick].age = 0.0f;
                return pick;
            }

            // Ages every ping by dt and retires the expired ones.
            void Advance(float dt)
            {
                if (!(dt > 0.0f) || !std::isfinite(dt))
                    return;
                for (PingSlot& slot : slots)
                {
                    if (!slot.active)
                        continue;
                    slot.age += dt;
                    if (slot.age >= StyleFor(slot.kind).duration)
                        slot = PingSlot{};
                }
            }

            void Clear()
            {
                for (PingSlot& slot : slots)
                    slot = PingSlot{};
            }

            size_t ActiveCount() const
            {
                size_t n = 0;
                for (const PingSlot& slot : slots)
                    if (slot.active)
                        ++n;
                return n;
            }
        };

        // ---- Artillery -------------------------------------------------------
        // Engine gravity for shells: Grenade::Simulate subtracts dt * 4.9 from
        // velocity.y twice per step (LaserArcGrenadeGravity row), i.e. 9.8.
        constexpr float kGravity = 9.8f;

        // Flat-ground maximum range of a shell fired at `speed` that lives
        // `lifeSpan` seconds. Without a lifeSpan limit the best pitch is 45
        // degrees and the range v^2/g. When the shell dies before a 45-degree
        // flight lands (T < v*sqrt(2)/g), the longest range is the pitch whose
        // flight time is exactly T: sin(theta) = g*T / (2v).
        inline float FlatMaxRange(float speed, float lifeSpan, float gravity = kGravity)
        {
            if (!std::isfinite(speed) || !(speed > 0.0f) || !std::isfinite(gravity) || !(gravity > 0.0f) ||
                !std::isfinite(lifeSpan) || !(lifeSpan > 0.0f))
                return 0.0f;
            const double v = speed, g = gravity, T = lifeSpan;
            const double full = v * v / g;
            const double t45 = v * std::sqrt(2.0) / g;
            if (T >= t45)
                return static_cast<float>(full);
            const double s = std::min(1.0, g * T / (2.0 * v));
            const double theta = std::asin(s);
            return static_cast<float>(full * std::sin(2.0 * theta));
        }

        // Can a shell fired at `speed` land at horizontal distance `distance`
        // and height difference `dy` (target minus muzzle, + is uphill)?
        // The discriminant is the engine's (Mortar 0x0056AF20 lines 48-56):
        // (v^2 - g*dy)^2 - g^2*(d^2 + dy^2) = v^4 - 2g*dy*v^2 - g^2*d^2. On
        // top of it, the faster (low) arc must land within lifeSpan; the
        // engine function does not check lifeSpan.
        inline bool CanReach(float speed, float lifeSpan, float distance, float dy, float gravity = kGravity)
        {
            if (!std::isfinite(speed) || !(speed > 0.0f) || !std::isfinite(distance) || !std::isfinite(dy) ||
                !std::isfinite(gravity) || !(gravity > 0.0f))
                return false;
            const double v2 = static_cast<double>(speed) * speed;
            const double g = gravity;
            const double d = std::fabs(static_cast<double>(distance));
            const double h = dy;
            const double a = v2 - g * h;
            const double disc = a * a - g * g * (d * d + h * h);
            if (disc < 0.0)
                return false;
            const double denom = a + std::sqrt(disc);
            if (!(denom > 0.0))
                return false;
            const double t2 = 2.0 * (d * d + h * h) / denom;
            if (std::isfinite(lifeSpan) && lifeSpan > 0.0f &&
                t2 > static_cast<double>(lifeSpan) * lifeSpan * (1.0 + 1e-6))
                return false;
            return true;
        }

        // ---- Weapon filter ---------------------------------------------------
        // A gravity-ordnance cannon or howitzer: a weapon class whose fire path
        // applies a shot pitch (Cannon or Mortar) loaded with ballistic
        // ordnance (Grenade, SprayBomb, BounceBomb, Popper). LaserSight's
        // signatures and rules, so both features agree on what is ballistic.
        inline bool IsArtilleryWeapon(uint32_t weaponSig, uint32_t ordnanceSig)
        {
            return LaserSight::AppliesShotPitch(weaponSig) && LaserSight::IsBallisticOrdnance(ordnanceSig);
        }

        // Shown only when its option is on and the HUD is not hidden.
        inline bool ShouldDraw(bool optionOn, bool hudHidden)
        {
            return optionOn && !hudHidden;
        }
    }
}
