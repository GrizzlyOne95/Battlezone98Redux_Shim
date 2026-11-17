// local_damage_policy.h
//
// SPDX-License-Identifier: MIT
//
// Pure math for the localized damage scorch (Docs/LOCAL_DAMAGE.md): mark
// size from health lost, the per-unit ring with merge, ember heat decay,
// the repair reset, and the sim-world -> entity-local conversion the
// Enhanced shader reconstructs with surfaceViewToLocal. No engine or Ogre
// types; host-tested in tests/local_damage_policy_tests.cpp.
#pragma once

#include <cmath>

namespace BZROpenShim::LocalDamage
{
    constexpr int kMaxMarks = 8;
    constexpr int kMaxUnits = 256;

    // Ogre Renderable custom parameter indices the OSE programs bind
    // (param_named_auto osMark<i> custom <index>).
    constexpr int kMarkParameterBase = 1400;  // 1400..1407: osMark0..7 (local xyz, radius)
    constexpr int kHeatParameterBase = 1408;  // 1408..1409: osMarkHeat0..1 (heat of marks 0-3, 4-7)
    constexpr int kParameterCount = 10;
    // 1410: osMarkKey = the main camera's position in the Entity's local
    // space (xyz), w = 1. The shader applies marks only when its own camera
    // position (from surfaceViewToLocal) matches, so values a Renderable
    // inherits from another object's draw of the same pass never show.
    constexpr int kKeyParameter = 1410;

    constexpr float kMinRadius = 0.9f;
    constexpr float kMaxRadius = 2.4f;
    // A hit within this fraction of an existing mark's radius merges into it.
    constexpr float kMergeFraction = 0.5f;
    // A merged hit grows the mark by this factor, up to kMaxRadius.
    constexpr float kMergeGrowth = 1.1f;
    // Health ratio above which a rising ratio counts as repaired.
    constexpr float kRepairClearRatio = 0.9f;
    // Splash/bullet points are pulled onto a sphere of this fraction of the
    // entity's bounding radius (or kFallbackHullRadius) so the mark lands on
    // the hull side facing the hit instead of in the air beside it.
    constexpr float kHullFraction = 0.6f;
    constexpr float kFallbackHullRadius = 3.0f;

    constexpr int kDefaultMaxMarks = 8;
    constexpr float kDefaultEmberSeconds = 6.0f;

    struct Mark
    {
        float x = 0.0f, y = 0.0f, z = 0.0f;
        float radius = 0.0f;  // 0 = unused
        float heat = 0.0f;    // 0..1
    };

    struct UnitMarks
    {
        Mark marks[kMaxMarks];
        int next = 0;

        bool Any() const
        {
            for (const Mark& m : marks)
                if (m.radius > 0.0f) return true;
            return false;
        }
        bool AnyHeat() const
        {
            for (const Mark& m : marks)
                if (m.radius > 0.0f && m.heat > 0.0f) return true;
            return false;
        }
        void Clear() { *this = UnitMarks{}; }
    };

    inline float Saturate(float v) { return v < 0.0f ? 0.0f : (v > 1.0f ? 1.0f : v); }

    inline int ClampMaxMarks(int value) { return value < 1 ? 1 : (value > kMaxMarks ? kMaxMarks : value); }

    inline float ClampEmberSeconds(float value)
    {
        if (!std::isfinite(value)) return kDefaultEmberSeconds;
        return value < 0.5f ? 0.5f : (value > 60.0f ? 60.0f : value);
    }

    // `lost` is the health ratio lost to this hit (before - after).
    inline float RadiusFromHealthLost(float lost)
    {
        if (!std::isfinite(lost)) lost = 0.0f;
        return kMinRadius + (kMaxRadius - kMinRadius) * Saturate(lost * 5.0f);
    }

    // Adds a fresh (heat 1) mark at a local point. A hit within kMergeFraction
    // of an existing mark's radius merges into the nearest such mark instead:
    // it grows a little (capped) and is reheated, so sustained fire on one
    // spot does not eat the ring. Otherwise the ring slot `next` is replaced.
    // Radii are kept in metres; `localPerMetre` (1 / the node's largest
    // scale) converts them to the local units the positions are in.
    // Returns true when the hit merged.
    inline bool AddMark(UnitMarks& unit, const float local[3], float radius, int maxMarks, float localPerMetre = 1.0f)
    {
        if (!(localPerMetre > 0.0f) || !std::isfinite(localPerMetre)) localPerMetre = 1.0f;
        maxMarks = ClampMaxMarks(maxMarks);
        radius = radius < kMinRadius ? kMinRadius : (radius > kMaxRadius ? kMaxRadius : radius);
        int best = -1;
        float bestDistance = 0.0f;
        for (int i = 0; i < maxMarks; ++i)
        {
            const Mark& m = unit.marks[i];
            if (m.radius <= 0.0f) continue;
            const float dx = local[0] - m.x, dy = local[1] - m.y, dz = local[2] - m.z;
            const float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
            if (distance < kMergeFraction * m.radius * localPerMetre &&(best < 0 || distance < bestDistance))
            {
                best = i;
                bestDistance = distance;
            }
        }
        if (best >= 0)
        {
            Mark& m = unit.marks[best];
            const float grown = (m.radius > radius ? m.radius : radius) * kMergeGrowth;
            m.radius = grown > kMaxRadius ? kMaxRadius : grown;
            m.heat = 1.0f;
            return true;
        }
        const int slot = (unit.next % maxMarks + maxMarks) % maxMarks;
        unit.marks[slot] = Mark{local[0], local[1], local[2], radius, 1.0f};
        unit.next = (slot + 1) % maxMarks;
        return false;
    }

    // Cools every mark linearly from 1 to 0 over emberSeconds. Returns true
    // when any mark was still warm, i.e. the GPU values changed.
    inline bool DecayHeat(UnitMarks& unit, float dtSeconds, float emberSeconds)
    {
        if (!(dtSeconds > 0.0f)) return false;
        const float step = dtSeconds / ClampEmberSeconds(emberSeconds);
        bool changed = false;
        for (Mark& m : unit.marks)
        {
            if (m.heat <= 0.0f) continue;
            m.heat = m.heat > step ? m.heat - step : 0.0f;
            changed = true;
        }
        return changed;
    }

    // Repair resets the hull: the ratio rose since the last reading and now
    // sits above kRepairClearRatio. A fresh hit that leaves a nearly full
    // unit above 0.9 does not clear, because the ratio fell.
    inline bool RepairClears(float previous, float current)
    {
        return std::isfinite(previous) && std::isfinite(current) &&
               current > kRepairClearRatio && current > previous + 1e-4f;
    }

    // Shader layout: out[i] = osMark<i> for i < 8, out[8..9] = osMarkHeat0..1.
    // Slots at or past maxMarks are written as zero so a lowered setting can
    // never leave a stale mark visible. Radii go out in local units.
    inline void PackParameters(const UnitMarks& unit, int maxMarks, float out[kParameterCount][4], float localPerMetre = 1.0f)
    {
        maxMarks = ClampMaxMarks(maxMarks);
        if (!(localPerMetre > 0.0f) || !std::isfinite(localPerMetre)) localPerMetre = 1.0f;
        for (int i = 0; i < kParameterCount; ++i)
            out[i][0] = out[i][1] = out[i][2] = out[i][3] = 0.0f;
        for (int i = 0; i < maxMarks; ++i)
        {
            const Mark& m = unit.marks[i];
            if (m.radius <= 0.0f) continue;
            out[i][0] = m.x;
            out[i][1] = m.y;
            out[i][2] = m.z;
            out[i][3] = m.radius * localPerMetre;
            out[8 + i / 4][i % 4] = Saturate(m.heat);
        }
    }

    // ---- Spaces ------------------------------------------------------------
    // Sim (game) world -> Ogre render world: Redux recentres the render world
    // on a per-map origin and mirrors Z (WorldRenderOrigin row; the same
    // conversion as EXU OgreRenderSpace::SimPositionToRender).
    inline void SimToRender(const double sim[3], const float origin[3], float out[3])
    {
        out[0] = static_cast<float>(sim[0] - origin[0]);
        out[1] = static_cast<float>(sim[1] - origin[1]);
        out[2] = static_cast<float>(-sim[2] - origin[2]);
    }

    inline void SimDirectionToRender(const float sim[3], float out[3])
    {
        out[0] = sim[0];
        out[1] = sim[1];
        out[2] = -sim[2];
    }

    // Render-world point -> the parent SceneNode's local space, inverting the
    // node's derived position, orientation (w, x, y, z) and scale. Ported
    // from EXU SurfacePointMath::ToLocal, the conversion EntityLocalPoint
    // feeds CR's surfaceImpact masks.
    inline bool ToLocal(const float point[3], const float origin[3], const float q[4], const float scale[3], float out[3])
    {
        float delta[3];
        for (int i = 0; i < 3; ++i)
        {
            if (!std::isfinite(point[i]) || !std::isfinite(origin[i]) || !std::isfinite(scale[i]) || std::fabs(scale[i]) < 1e-6f)
                return false;
            delta[i] = point[i] - origin[i];
        }
        float norm = 0;
        for (int i = 0; i < 4; ++i)
        {
            if (!std::isfinite(q[i])) return false;
            norm += q[i] * q[i];
        }
        if (norm < 0.5f || norm > 1.5f) return false;
        const float x = -q[1], y = -q[2], z = -q[3], w = q[0];
        const float t[3] = {2 * (y * delta[2] - z * delta[1]), 2 * (z * delta[0] - x * delta[2]), 2 * (x * delta[1] - y * delta[0])};
        const float cross[3] = {y * t[2] - z * t[1], z * t[0] - x * t[2], x * t[1] - y * t[0]};
        for (int i = 0; i < 3; ++i) out[i] = (delta[i] + (w * t[i] + cross[i]) / norm) / scale[i];
        return true;
    }

    // 1 / the largest absolute node scale: metres -> local units. 1 when the
    // scale is unusable.
    inline float LocalPerMetre(const float scale[3])
    {
        float largest = 0.0f;
        for (int i = 0; i < 3; ++i)
        {
            if (!std::isfinite(scale[i])) return 1.0f;
            const float s = std::fabs(scale[i]);
            largest = s > largest ? s : largest;
        }
        return largest > 1e-6f ? 1.0f / largest : 1.0f;
    }

    // The shader's key test (ose_local_scorch), mirrored for tests: marks
    // apply only when the draw's camera, in local space, is where the CPU
    // put it. The tolerance grows with distance (0.2%, at least 5 cm) so
    // float precision at 1-2 km never rejects the right object.
    inline bool KeyMatches(const float cameraLocal[3], const float key[4])
    {
        if (!(key[3] > 0.5f)) return false;
        float dd = 0.0f, kk = 0.0f;
        for (int i = 0; i < 3; ++i)
        {
            const float d = cameraLocal[i] - key[i];
            dd += d * d;
            kk += key[i] * key[i];
        }
        const float scaled = 0.002f * std::sqrt(kk);
        const float tolerance = scaled > 0.05f ? scaled : 0.05f;
        return std::sqrt(dd) < tolerance;
    }

    // Moves a local hit point outside the hull sphere (radius `hull`) onto it:
    // along the impact direction to where that line enters the sphere, or,
    // when the line misses it, straight toward the centre. A point already
    // inside is kept.
    inline bool PlaceOnHull(const float point[3], const float direction[3], float hull, float out[3])
    {
        if (!(hull > 0.0f)) return false;
        for (int i = 0; i < 3; ++i)
            if (!std::isfinite(point[i])) return false;
        const float pp = point[0] * point[0] + point[1] * point[1] + point[2] * point[2];
        if (pp <= hull * hull)
        {
            out[0] = point[0]; out[1] = point[1]; out[2] = point[2];
            return true;
        }
        float d[3] = {direction[0], direction[1], direction[2]};
        const float dd = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
        if (std::isfinite(dd) && dd > 1e-8f)
        {
            const float inv = 1.0f / std::sqrt(dd);
            d[0] *= inv; d[1] *= inv; d[2] *= inv;
            const float b = point[0] * d[0] + point[1] * d[1] + point[2] * d[2];
            const float disc = b * b - (pp - hull * hull);
            if (b < 0.0f && disc >= 0.0f)
            {
                const float t = -b - std::sqrt(disc);
                for (int i = 0; i < 3; ++i) out[i] = point[i] + d[i] * t;
                return true;
            }
        }
        const float scale = hull / std::sqrt(pp);
        for (int i = 0; i < 3; ++i) out[i] = point[i] * scale;
        return true;
    }
}
