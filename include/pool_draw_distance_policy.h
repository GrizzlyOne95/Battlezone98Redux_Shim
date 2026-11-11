// pool_draw_distance_policy.h
//
// SPDX-License-Identifier: MIT
//
// Pure logic for [General] SkinnedGibsDrawDistance and ShellCasingsDrawDistance
// (skinned_gibs.cpp, shell_casings.cpp). Pool entities hang off the root scene
// node and are drawn by Ogre's own traversal, so a piece hidden with
// setVisible(false) costs no main, glow or shadow submission. Each pool tick a
// live piece farther than the threshold from the main view camera is hidden,
// and shown again (with its current transform) once it comes back inside.
// Render-only: the piece keeps simulating, sinking and expiring as before.
//
// The cull state is tracked per slot apart from the pools' own visibility
// (free slots hidden for reuse, recycled slots): those paths reset it, and
// a culled slot is the only one this logic ever hides or shows.
//
// Host-tested in tests/pool_draw_distance_policy_tests.cpp.
#pragma once

#include <cmath>

namespace BZROpenShim
{
    namespace PoolDrawDistance
    {
        // Accepted setting range in metres; 0 = off (every piece is drawn).
        constexpr int kMaxDrawDistanceMetres = 2000;

        // Defaults, chosen by on-screen size at 1080p assuming roughly a 60
        // degree vertical FOV (about 1080 / (2 * d * tan 30) pixels per metre,
        // ~6 px/m at 150 m, ~13 px/m at 70 m):
        //  - Gibs (limbs about 0.3-0.8 m): at 150 m a 0.5 m limb is ~3 px, so
        //    hiding it is invisible in practice. FractureOnePiece pieces share
        //    the pool and are larger (1-5 m, ~6-30 px there); a player
        //    watching a building die from farther away sees its pieces go
        //    early, and can raise the key.
        //  - Casings (about 0.25 m): at 70 m a casing is ~3 px. They are the
        //    smallest pool objects and the most numerous in a firefight.
        constexpr int kDefaultGibDrawDistanceMetres = 150;
        constexpr int kDefaultCasingDrawDistanceMetres = 70;

        // Non-positive or NaN -> 0 (off); above the maximum -> the maximum.
        inline int ClampDrawDistanceMetres(double value)
        {
            if (!(value > 0.0))
                return 0;
            if (value >= static_cast<double>(kMaxDrawDistanceMetres))
                return kMaxDrawDistanceMetres;
            return static_cast<int>(value);
        }

        // Strictly farther than the threshold. Off (<= 0) never culls; NaN
        // never culls, because NaN > x is false.
        inline bool IsBeyondDrawDistance(float distanceSquared, int thresholdMetres)
        {
            if (thresholdMetres <= 0)
                return false;
            const float threshold = static_cast<float>(thresholdMetres);
            return distanceSquared > threshold * threshold;
        }

        // tan(30 degrees): half the reference vertical FOV the defaults assume.
        constexpr float kReferenceHalfFovTan = 0.57735027f;

        // Factor applied to the camera distance before the threshold test, so
        // a piece stays drawn while it is still a few pixels wide. Zooming in
        // (a scope, a narrower FOV) shrinks it and pushes the cull out with
        // the zoom; a wider-than-reference FOV never culls closer than the
        // setting. Bad or degenerate FOV -> 1 (plain distance).
        inline float ZoomDistanceScale(float fovYRadians)
        {
            if (!(fovYRadians > 0.0f) || !(fovYRadians < 3.1f))
                return 1.0f;
            const float scale = std::tan(fovYRadians * 0.5f) / kReferenceHalfFovTan;
            return scale < 1.0f ? scale : 1.0f;
        }

        inline float DistanceSquared(const float a[3], const float b[3])
        {
            const float dx = a[0] - b[0];
            const float dy = a[1] - b[1];
            const float dz = a[2] - b[2];
            return dx * dx + dy * dy + dz * dz;
        }

        enum class Transition
        {
            Keep, // no visibility call this tick
            Hide, // setVisible(false), mark culled, skip the transform push
            Show, // push the transform (it makes the entity visible), clear culled
        };

        // One live slot's decision for this tick. `culled` is the slot's own
        // distance-cull flag. An unknown camera keeps whatever state the slot
        // has, so a camera read that fails for a tick never flickers pieces.
        // With the feature off nothing is ever culled, and a slot left culled
        // (cannot happen in practice: the threshold is fixed at startup) is
        // shown.
        inline Transition Decide(bool culled, bool cameraKnown, float distanceSquared, int thresholdMetres)
        {
            if (thresholdMetres <= 0)
                return culled ? Transition::Show : Transition::Keep;
            if (!cameraKnown)
                return Transition::Keep;
            const bool beyond = IsBeyondDrawDistance(distanceSquared, thresholdMetres);
            if (beyond == culled)
                return Transition::Keep;
            return beyond ? Transition::Hide : Transition::Show;
        }
    }
}
