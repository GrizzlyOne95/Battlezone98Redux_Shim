// laser_sight_policy.h
// BZR Open Shim - LaserSight: the engine-independent part of the laser-sight
// beam (enable gate, export mode, terrain and object ray tests, beam
// transform), kept header-only so the unit tests exercise exactly the code
// the shim runs. See Docs/LASER_SIGHT.md.
//
// Everything here works in Ogre render space (right-handed, Y up), the same
// space as shell_casing_physics.h. laser_sight.cpp converts the muzzle
// matrix into it once per recompute and converts back only to sample the
// terrain and to query the collision grid.
#pragma once

#include "shell_casing_physics.h"

#include <cmath>
#include <cstddef>
#include <cstdint>

namespace BZROpenShim::LaserSight
{
    using Vec3 = ShellCasings::Vec3;
    using Quat = ShellCasings::Quat;
    using Obb = ShellCasings::Obb;

    // OpenShimSetLaserSightMode values. Anything else is rejected and leaves
    // the current mode unchanged.
    enum class Mode : int
    {
        Default = 0,            // [General] LaserSight, forced off in a network game
        AllowInMultiplayer = 1, // [General] LaserSight, also in a network game
    };

    inline bool IsValidMode(int mode) noexcept
    {
        return mode == static_cast<int>(Mode::Default) || mode == static_cast<int>(Mode::AllowInMultiplayer);
    }

    // The effective state. The user's option always wins when it is off; a
    // network game closes the gate unless an external owner (EXU or a mod)
    // set AllowInMultiplayer.
    inline bool Enabled(bool userOption, bool isNetGame, int mode) noexcept
    {
        if (!userOption)
            return false;
        if (!isNetGame)
            return true;
        return mode == static_cast<int>(Mode::AllowInMultiplayer);
    }

    // The selected weapon of a Carrier: the engine's selection mask (bit i =
    // slot i, several bits when weapons are linked). v1 draws one beam, from
    // the lowest selected slot. Returns -1 when nothing in slots 0..4 is set.
    inline int FirstSelectedSlot(uint32_t mask) noexcept
    {
        for (int slot = 0; slot < 5; ++slot)
            if (mask & (1u << slot))
                return slot;
        return -1;
    }

    // ---- Terrain ----------------------------------------------------------
    struct TerrainMarch
    {
        float coarseStep = 8.0f;   // metres between ground samples
        int refineIterations = 6;  // bisections of the crossing segment (8 m / 64)
    };

    // First point where the ray (origin + t * dir, |dir| = 1) meets the ground
    // within maxDistance. heightAt(x, z, outHeight) returns false where the
    // terrain cannot be sampled; the march stops there with no hit. A muzzle
    // already under the ground hits at t = 0. Cost: maxDistance / coarseStep
    // samples plus refineIterations.
    template <class HeightAt>
    bool MarchTerrain(Vec3 origin, Vec3 dir, float maxDistance, const TerrainMarch& march, HeightAt&& heightAt,
                      float& outT)
    {
        if (!(maxDistance > 0.0f) || !(march.coarseStep > 0.0f))
            return false;
        auto above = [&](float t, float& clearance) {
            const Vec3 p = {origin.x + dir.x * t, origin.y + dir.y * t, origin.z + dir.z * t};
            float ground = 0.0f;
            if (!heightAt(p.x, p.z, ground) || !std::isfinite(ground))
                return false;
            clearance = p.y - ground;
            return true;
        };
        float clearance = 0.0f;
        if (!above(0.0f, clearance))
            return false;
        if (clearance <= 0.0f)
        {
            outT = 0.0f;
            return true;
        }
        float previous = 0.0f;
        for (float t = march.coarseStep;; t += march.coarseStep)
        {
            const float at = t < maxDistance ? t : maxDistance;
            if (!above(at, clearance))
                return false;
            if (clearance <= 0.0f)
            {
                float lo = previous, hi = at;
                for (int i = 0; i < march.refineIterations; ++i)
                {
                    const float mid = 0.5f * (lo + hi);
                    float c = 0.0f;
                    if (!above(mid, c))
                        break;
                    (c <= 0.0f ? hi : lo) = mid;
                }
                outT = hi;
                return true;
            }
            if (at >= maxDistance)
                return false;
            previous = at;
        }
    }

    // ---- Objects ------------------------------------------------------------
    // Ray against an oriented box (slab test in the box frame). On a hit,
    // outT is the entry distance, or 0 when the origin is inside the box.
    inline bool RayObb(Vec3 origin, Vec3 dir, const Obb& box, float maxDistance, float& outT) noexcept
    {
        const Vec3 d = ShellCasings::Sub(origin, box.center);
        const float half[3] = {box.half.x, box.half.y, box.half.z};
        float tMin = 0.0f, tMax = maxDistance;
        for (int i = 0; i < 3; ++i)
        {
            const float o = ShellCasings::Dot(d, box.axis[i]);
            const float v = ShellCasings::Dot(dir, box.axis[i]);
            if (std::fabs(v) < 1e-8f)
            {
                if (o < -half[i] || o > half[i])
                    return false;
                continue;
            }
            float t0 = (-half[i] - o) / v, t1 = (half[i] - o) / v;
            if (t0 > t1)
            {
                const float swap = t0;
                t0 = t1;
                t1 = swap;
            }
            if (t0 > tMin)
                tMin = t0;
            if (t1 < tMax)
                tMax = t1;
            if (tMin > tMax)
                return false;
        }
        outT = tMin;
        return true;
    }

    // The object pass walks the beam in segments and stops after the first
    // segment whose end lies past the nearest hit so far: objects are only
    // gathered from grid cells the beam has reached.
    inline constexpr float kObjectSegment = 50.0f;

    inline int SegmentCount(float length, float segment = kObjectSegment) noexcept
    {
        if (!(length > 0.0f) || !(segment > 0.0f))
            return 0;
        return static_cast<int>(std::ceil(length / segment));
    }

    // ---- Beam transform -----------------------------------------------------
    // The beam mesh is a unit tube along local +Z from z = 0 (muzzle) to
    // z = 1 (far end), radius 1 at the muzzle. The node scales it: x/y by the
    // beam radius, z by the length.
    struct BeamTransform
    {
        float position[3];
        float orientation[4]; // w, x, y, z
        float scale[3];
    };

    inline BeamTransform MakeBeamTransform(Vec3 muzzle, Vec3 dir, Vec3 up, float length, float radius) noexcept
    {
        const Quat q = ShellCasings::OrientAlong(dir, up);
        BeamTransform out = {};
        out.position[0] = muzzle.x;
        out.position[1] = muzzle.y;
        out.position[2] = muzzle.z;
        out.orientation[0] = q.w;
        out.orientation[1] = q.x;
        out.orientation[2] = q.y;
        out.orientation[3] = q.z;
        out.scale[0] = radius;
        out.scale[1] = radius;
        out.scale[2] = length > 1e-3f ? length : 1e-3f;
        return out;
    }

    // Shortest beam worth drawing; anything shorter is hidden (muzzle buried
    // in terrain or pressed against a hull).
    inline constexpr float kMinBeamLength = 0.5f;
    inline constexpr float kMaxBeamLength = 500.0f;

    // ---- Ballistic arc ------------------------------------------------------
    // Gravity ordnance (Grenade and the classes built on it) flies an exact
    // parabola, so for those weapons the beam follows the predicted mean
    // trajectory instead of a straight line. Facts and citations:
    // Docs/LASER_SIGHT.md, "Ballistic arc".

    // OrdnanceClass +0x0C signatures of the gravity ordnance classes.
    inline constexpr uint32_t kOrdnanceSigGrenade = 0x4752454Eu;    // 'GREN'
    inline constexpr uint32_t kOrdnanceSigSprayBomb = 0x53424D42u;  // 'SBMB'
    inline constexpr uint32_t kOrdnanceSigBounceBomb = 0x42424D42u; // 'BBMB'
    inline constexpr uint32_t kOrdnanceSigPopper = 0x504F5052u;     // 'POPR'
    // WeaponClass +0x0C signatures whose fire path (Cannon::Simulate) applies
    // shotPitch (WeaponClass +0x90).
    inline constexpr uint32_t kWeaponSigMortar = 0x4D4F5254u; // 'MORT'
    inline constexpr uint32_t kWeaponSigCannon = 0x43414E4Eu; // 'CANN'
    // Grenade::Simulate: vy -= 4.9 * dt before and after the move, which is
    // y(t) = y0 + vy0 * t - 4.9 * t^2 exactly (g = 9.8 on -Y). Render space
    // keeps Y up, so the same holds there.
    inline constexpr float kHalfGravity = 4.9f;

    inline bool IsBallisticOrdnance(uint32_t ordnanceSig) noexcept
    {
        return ordnanceSig == kOrdnanceSigGrenade || ordnanceSig == kOrdnanceSigSprayBomb ||
               ordnanceSig == kOrdnanceSigBounceBomb || ordnanceSig == kOrdnanceSigPopper;
    }

    inline bool AppliesShotPitch(uint32_t weaponSig) noexcept
    {
        return weaponSig == kWeaponSigMortar || weaponSig == kWeaponSigCannon;
    }

    // Cannon::Simulate fires along R(yaw = r * variance, pitch = r * variance -
    // shotPitch) composed onto the muzzle; the random terms average zero, so
    // the mean shot leaves along the muzzle front pitched up by shotPitch
    // (radians, positive = up).
    inline Vec3 PitchedFireDirection(Vec3 front, Vec3 up, float shotPitch) noexcept
    {
        const float c = std::cos(shotPitch), s = std::sin(shotPitch);
        return ShellCasings::Normalize(ShellCasings::Add(ShellCasings::Scale(front, c), ShellCasings::Scale(up, s)),
                                       front);
    }

    // Bullet::Init: velocity = shotSpeed * fire direction, no carrier velocity.
    struct Arc
    {
        Vec3 origin = {0, 0, 0};
        Vec3 velocity = {0, 0, 0};
        float lifeSpan = 0.0f; // seconds
    };

    inline Vec3 ArcPoint(const Arc& arc, float t) noexcept
    {
        return {arc.origin.x + arc.velocity.x * t, arc.origin.y + arc.velocity.y * t - kHalfGravity * t * t,
                arc.origin.z + arc.velocity.z * t};
    }

    inline Vec3 ArcVelocity(const Arc& arc, float t) noexcept
    {
        return {arc.velocity.x, arc.velocity.y - 2.0f * kHalfGravity * t, arc.velocity.z};
    }

    struct ArcMarch
    {
        float terrainStep = 8.0f;           // metres of path between ground samples (as the straight beam)
        int refineIterations = 6;           // bisections in time of the crossing step
        float maxStepTime = 0.5f;           // bounds the chord-to-parabola gap to g * dt^2 / 8 = 0.31 m
        float maxPathLength = kMaxBeamLength;
        float objectSpan = kObjectSegment;  // metres of path per collision-grid query
    };
    // Hard bounds on one march, whatever the inputs: ground samples (the path
    // limit normally ends it far earlier) and points per object span.
    inline constexpr int kMaxArcSamples = 128;
    inline constexpr int kMaxArcSpanPoints = 16;

    struct ArcSample
    {
        float t;
        Vec3 p;
    };

    enum class ArcEnd : uint8_t
    {
        Terrain,   // met the ground
        Object,    // met an object box
        LifeSpan,  // the ordnance expires in flight
        PathLimit, // maxPathLength or the sample budget
        Unsampled, // the ground cannot be sampled (off the map)
        Invalid,   // bad inputs
    };

    struct ArcResult
    {
        float endT = 0.0f;
        ArcEnd end = ArcEnd::Invalid;
        int samples = 0; // ground samples taken
        int spans = 0;   // object-span callbacks made
    };

    // First hit of a box along the polyline points[0..count), in arc time,
    // interpolated inside the chord. Chords are tested in order, so the
    // first hit is the nearest.
    inline bool PolylineObbHit(const ArcSample* points, int count, const Obb& box, float& outT) noexcept
    {
        for (int i = 0; i + 1 < count; ++i)
        {
            const Vec3 d = ShellCasings::Sub(points[i + 1].p, points[i].p);
            const float length = ShellCasings::Length(d);
            if (!(length > 1e-6f))
                continue;
            float s = 0.0f;
            if (RayObb(points[i].p, ShellCasings::Scale(d, 1.0f / length), box, length, s))
            {
                outT = points[i].t + (points[i + 1].t - points[i].t) * (s / length);
                return true;
            }
        }
        return false;
    }

    // Walks the arc from t = 0 to the first ground or object hit, the
    // ordnance's lifeSpan, the path limit, or the edge of the sampled ground.
    //  - Ground: one sample per terrainStep metres of path (time steps sized
    //    from the current speed, at most maxStepTime), the crossing refined
    //    by bisection on the parabola itself, as MarchTerrain does on a line.
    //    heightAt(x, z, outHeight) returns false where the ground cannot be
    //    sampled; the arc ends at the last sampled point.
    //  - Objects: the sampled points are grouped into spans of about
    //    objectSpan metres (at most kMaxArcSpanPoints points); spanHit(points,
    //    count, outT) is called once per span, in order, and returns the first
    //    hit time inside it. The walk stops at the first span with a hit.
    template <class HeightAt, class SpanHit>
    ArcResult MarchArc(const Arc& arc, const ArcMarch& march, HeightAt&& heightAt, SpanHit&& spanHit)
    {
        ArcResult result;
        if (!ShellCasings::Finite(arc.origin) || !ShellCasings::Finite(arc.velocity) || !(arc.lifeSpan > 0.0f) ||
            !(march.terrainStep > 0.0f) || !(march.maxStepTime > 0.0f) || !(march.maxPathLength > 0.0f) ||
            !(march.objectSpan > 0.0f))
            return result;
        auto clearance = [&](float t, float& out) {
            const Vec3 p = ArcPoint(arc, t);
            float ground = 0.0f;
            ++result.samples;
            if (!heightAt(p.x, p.z, ground) || !std::isfinite(ground))
                return false;
            out = p.y - ground;
            return true;
        };

        ArcSample span[kMaxArcSpanPoints];
        int spanCount = 0;
        float spanLength = 0.0f;
        // Tests the span gathered so far; true when an object ends the arc.
        auto flushSpan = [&]() {
            if (spanCount < 2)
                return false;
            ++result.spans;
            float hitT = 0.0f;
            const bool hit = spanHit(static_cast<const ArcSample*>(span), spanCount, hitT) &&
                             hitT >= span[0].t && hitT <= span[spanCount - 1].t;
            if (hit)
            {
                result.endT = hitT;
                result.end = ArcEnd::Object;
                return true;
            }
            span[0] = span[spanCount - 1];
            spanCount = 1;
            spanLength = 0.0f;
            return false;
        };
        // Appends a point; flushes a full span. True when an object ends the arc.
        auto push = [&](float t) {
            const ArcSample s = {t, ArcPoint(arc, t)};
            if (spanCount > 0)
                spanLength += ShellCasings::Length(ShellCasings::Sub(s.p, span[spanCount - 1].p));
            span[spanCount++] = s;
            if (spanCount == kMaxArcSpanPoints || spanLength >= march.objectSpan)
                return flushSpan();
            return false;
        };
        // Ends the arc at t (its last point already pushed) after the
        // objects of the final partial span.
        auto finish = [&](float t, ArcEnd end) {
            if (!flushSpan())
            {
                result.endT = t;
                result.end = end;
            }
            return result;
        };

        float c = 0.0f;
        if (!clearance(0.0f, c))
        {
            result.end = ArcEnd::Unsampled;
            return result;
        }
        if (c <= 0.0f)
        {
            result.end = ArcEnd::Terrain; // buried muzzle: endT 0
            return result;
        }
        push(0.0f);
        float t = 0.0f, path = 0.0f;
        Vec3 previous = arc.origin;
        while (true)
        {
            if (result.samples >= kMaxArcSamples || path >= march.maxPathLength)
                return finish(t, ArcEnd::PathLimit);
            if (t >= arc.lifeSpan)
                return finish(t, ArcEnd::LifeSpan);
            const float speed = ShellCasings::Length(ArcVelocity(arc, t));
            float dt = speed > 1e-3f ? march.terrainStep / speed : march.maxStepTime;
            if (dt > march.maxStepTime)
                dt = march.maxStepTime;
            const float next = t + dt < arc.lifeSpan ? t + dt : arc.lifeSpan;
            if (!clearance(next, c))
                return finish(t, ArcEnd::Unsampled);
            if (c <= 0.0f)
            {
                float lo = t, hi = next;
                for (int i = 0; i < march.refineIterations; ++i)
                {
                    const float mid = 0.5f * (lo + hi);
                    float m = 0.0f;
                    if (!clearance(mid, m))
                        break;
                    (m <= 0.0f ? hi : lo) = mid;
                }
                if (push(hi))
                    return result;
                return finish(hi, ArcEnd::Terrain);
            }
            const Vec3 p = ArcPoint(arc, next);
            path += ShellCasings::Length(ShellCasings::Sub(p, previous));
            previous = p;
            t = next;
            if (push(t))
                return result;
        }
    }

    // The drawn arc: kArcSegments straight pieces, equal in time from the
    // muzzle to endT. Piece k uses section mesh k, whose radius and texture v
    // carry on from piece k - 1, so the pieces read as one tapering beam.
    inline constexpr unsigned kArcSegments = 16;

    inline void ArcSegment(const Arc& arc, float endT, unsigned k, unsigned segments, Vec3& outStart, Vec3& outEnd)
    {
        const float n = static_cast<float>(segments ? segments : 1);
        outStart = ArcPoint(arc, endT * static_cast<float>(k) / n);
        outEnd = ArcPoint(arc, endT * static_cast<float>(k + 1) / n);
    }

    // A roll reference perpendicular to every chord of the arc: the arc lies
    // in the vertical plane of its launch velocity, so the horizontal normal
    // of that plane works. A vertical shot has no such plane; use fallback.
    inline Vec3 ArcSideVector(const Arc& arc, Vec3 fallback) noexcept
    {
        const Vec3 side = {arc.velocity.z, 0.0f, -arc.velocity.x};
        const float length = ShellCasings::Length(side);
        return length > 1e-4f ? ShellCasings::Scale(side, 1.0f / length) : fallback;
    }
}
