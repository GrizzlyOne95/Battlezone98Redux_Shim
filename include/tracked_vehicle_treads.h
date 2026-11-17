#pragma once

// Engine-independent tread visual and sound math for the classLabel =
// "tracked" vehicle class (src/patches/tracked_vehicle_class.cpp,
// Docs/TRACKED_VEHICLES.md).
//
// Sides follow BZCC: "L" is the driver's left (-x in Redux's left-handed
// frame, x right, y up, z front), "R" the right. A tread speed is the
// commanded ground speed of that tread in m/s, positive when it drives the
// hull forward; a pivot to the left (+omega.y) gives L < 0 < R.

#include <cmath>

namespace BZROpenShim::TrackedTreads
{
    // Below this share of velocForward the tread loop is silent; stock
    // HoverCraft drops its fly sound at the same 0.05 gate.
    constexpr float kSoundOnFraction = 0.05f;
    constexpr float kDefaultCycleLength = 1.0f;
    constexpr float kMinCycleLength = 0.05f;
    constexpr float kMaxCycleLength = 100.0f;

    inline bool FiniteF(float v)
    {
        return std::isfinite(v);
    }

    // Metres of tread travel per loop of the tread clip.
    inline float SanitizeCycleLength(float metres)
    {
        if (!FiniteF(metres) || metres <= 0.0f)
            return kDefaultCycleLength;
        if (metres < kMinCycleLength)
            return kMinCycleLength;
        if (metres > kMaxCycleLength)
            return kMaxCycleLength;
        return metres;
    }

    // Moves a visual tread speed toward its commanded speed: at accelThrust
    // while it gains magnitude in the same direction, at accelBrake while it
    // slows or reverses, the same split the contact model uses for the hull.
    inline float StepTreadSpeed(float current, float target, float accelThrust, float accelBrake, float dt)
    {
        if (!FiniteF(current))
            current = 0.0f;
        if (!FiniteF(target) || !FiniteF(dt) || dt <= 0.0f)
            return current;
        const bool speeding = std::fabs(target) > std::fabs(current) &&
            (current == 0.0f || (current > 0.0f) == (target > 0.0f));
        float rate = speeding ? accelThrust : accelBrake;
        if (!FiniteF(rate) || rate < 0.0f)
            rate = 0.0f;
        const float maxDelta = rate * dt;
        const float delta = target - current;
        if (delta > maxDelta)
            return current + maxDelta;
        if (delta < -maxDelta)
            return current - maxDelta;
        return target;
    }

    // The faster tread's share of velocForward, 0..1; drives the loop's
    // pitch and volume.
    inline float SpeedFraction(float left, float right, float velocForward)
    {
        if (!FiniteF(left) || !FiniteF(right) || !FiniteF(velocForward) || velocForward <= 0.0f)
            return 0.0f;
        const float fastest = std::fabs(left) > std::fabs(right) ? std::fabs(left) : std::fabs(right);
        const float fraction = fastest / velocForward;
        return fraction > 1.0f ? 1.0f : fraction;
    }

    // Seconds to add to a looping clip of clipLength seconds so it plays one
    // loop per cycleLength metres of tread travel; negative runs it backward.
    inline float ClipAdvance(float speed, float dt, float clipLength, float cycleLength)
    {
        if (!FiniteF(speed) || !FiniteF(dt) || dt <= 0.0f || !FiniteF(clipLength) || clipLength <= 0.0f)
            return 0.0f;
        const float advance = speed * dt * clipLength / SanitizeCycleLength(cycleLength);
        // Never more than one loop per step, so a wild speed cannot spin it.
        if (advance > clipLength)
            return clipLength;
        if (advance < -clipLength)
            return -clipLength;
        return advance;
    }

    // A playing loop is kept, muted, until the treads have been under the
    // sound gate for holdSeconds in a row, so an AI easing its throttle
    // around the gate does not restart the loop over and over. Counted in
    // time, not calls, because the sim step rate varies.
    inline bool KeepLoop(bool play, float& quietSeconds, float dt, float holdSeconds)
    {
        if (play)
        {
            quietSeconds = 0.0f;
            return true;
        }
        if (!FiniteF(quietSeconds) || quietSeconds < 0.0f)
            quietSeconds = 0.0f;
        if (FiniteF(dt) && dt > 0.0f && quietSeconds < holdSeconds)
            quietSeconds += dt;
        return quietSeconds < holdSeconds;
    }

    struct SoundLevel
    {
        bool play = false;
        int volume = 0;
        int rate = 0;
    };

    // Mirrors the stock HoverCraft thrust loop (HoverCraft::UpdateSounds
    // 0x004EEA20 on GOG Redux 2.2.301): playback rate 11025 + 5512.5 * t Hz,
    // volume 5 + 5 * t for the user's craft and five times that for AI craft.
    inline SoundLevel TreadSound(float fraction, bool userCraft)
    {
        SoundLevel level;
        if (!FiniteF(fraction) || fraction <= kSoundOnFraction)
            return level;
        const float t = fraction > 1.0f ? 1.0f : fraction;
        const float volume = (5.0f + 5.0f * t) * (userCraft ? 1.0f : 5.0f);
        level.play = true;
        level.volume = static_cast<int>(volume + 0.5f);
        level.rate = static_cast<int>(11025.0f + 5512.5f * t + 0.5f);
        return level;
    }
}
