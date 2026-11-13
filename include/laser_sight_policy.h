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
}
