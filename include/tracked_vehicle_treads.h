#pragma once

// Engine-independent tread visual and sound math for the classLabel =
// "tracked" vehicle class (src/patches/tracked_vehicle_class.cpp,
// Docs/TRACKED_VEHICLES.md).
//
// Sides follow BZCC: "L" is the driver's left (-x in Redux's left-handed
// frame, x right, y up, z front), "R" the right. A tread speed is the
// commanded ground speed of that tread in m/s, positive when it drives the
// hull forward; a pivot to the left (+omega.y) gives L < 0 < R.

#include "gpu_skinning.h"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>

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

    // ---- tread texture scroll (Docs/TRACKED_VEHICLES.md) --------------------
    //
    // Renderable custom parameter index the scroll phase is written to; the
    // Enhanced vertex shader reads it as osTreadUV (1400..1410 are local
    // damage, include/local_damage_policy.h).
    constexpr unsigned kTreadScrollParameter = 1411;
    // |treadScrollU| above this is clamped: more than this many texture loops
    // per tread cycle is not a believable belt.
    constexpr float kMaxScrollU = 64.0f;

    // [TrackedClass] treadScrollU: texture loops per treadCycleLength metres
    // of tread travel. 0, NaN or infinity is off; negative flips direction.
    inline float SanitizeScrollU(float loops)
    {
        if (!FiniteF(loops))
            return 0.0f;
        if (loops > kMaxScrollU)
            return kMaxScrollU;
        if (loops < -kMaxScrollU)
            return -kMaxScrollU;
        return loops;
    }

    // Wraps a phase into [0, 1). floor, not fmod, so a negative phase (a
    // reversing tread) wraps to the same place on the belt: -0.25 -> 0.75.
    inline float WrapPhase(float phase)
    {
        if (!FiniteF(phase))
            return 0.0f;
        const float wrapped = phase - std::floor(phase);
        // -1e-9f - floor(-1e-9f) rounds to exactly 1.0f.
        return (wrapped >= 1.0f || wrapped < 0.0f) ? 0.0f : wrapped;
    }

    // Advances one side's U phase by its signed tread speed, so a reversing
    // unit scrolls its belts backward and a pivot scrolls them in opposite
    // directions. Wrapped every step so float precision holds over a long
    // session. Garbage input holds the phase; scroll off returns 0.
    inline float StepScrollPhase(float phase, float speed, float dt, float scrollU, float cycleLength)
    {
        const float loops = SanitizeScrollU(scrollU);
        if (loops == 0.0f)
            return 0.0f;
        if (!FiniteF(speed) || !FiniteF(dt) || dt <= 0.0f)
            return WrapPhase(phase);
        return WrapPhase(WrapPhase(phase) + speed * dt * loops / SanitizeCycleLength(cycleLength));
    }

    // [TrackedClass] treadMaterialL / treadMaterialR: buffer for one material
    // name, terminator included. A longer name is refused (scroll off).
    constexpr size_t kTreadMaterialBytes = 128;

    enum class TreadSide
    {
        None,
        Left,
        Right,
    };

    // Whether a SubEntity's current material `current` is the ODF-named
    // tread material `configured`: the same name, or the GPU skinning clone
    // of it (gpu_skinning.cpp names clones
    // "OpenShim/GpuSkin/<generation>/<tag>/<source>"). Its shadow caster
    // clones (".../<tag>/caster/<source>") never match: they draw no UV.
    inline bool MatchesTreadMaterial(const char* current, const char* configured)
    {
        if (!current || !configured || !configured[0])
            return false;
        if (std::strcmp(current, configured) == 0)
            return true;
        const size_t rootLength = std::strlen(kGpuSkinCloneRoot);
        if (std::strncmp(current, kGpuSkinCloneRoot, rootLength) != 0)
            return false;
        const char* p = current + rootLength;
        // <generation>: one or more digits, then '/'.
        const char* digits = p;
        while (*p >= '0' && *p <= '9')
            ++p;
        if (p == digits || *p != '/')
            return false;
        ++p;
        // <tag>: no '/', then '/'.
        const char* tag = p;
        while (*p && *p != '/')
            ++p;
        if (p == tag || *p != '/')
            return false;
        ++p;
        if (std::strncmp(p, "caster/", 7) == 0)
            return false;
        return std::strcmp(p, configured) == 0;
    }

    // Left wins when both keys name the same material (the sides then cannot
    // be told apart; Docs/TRACKED_VEHICLES.md asks for two materials).
    inline TreadSide ClassifyTreadMaterial(const char* current, const char* left, const char* right)
    {
        if (MatchesTreadMaterial(current, left))
            return TreadSide::Left;
        if (MatchesTreadMaterial(current, right))
            return TreadSide::Right;
        return TreadSide::None;
    }

    // FNV-1a of a material name. With the pointer it tells a material this
    // unit already bound from a new one later allocated at the same address.
    inline uint32_t MaterialNameHash(const char* name)
    {
        uint32_t hash = 2166136261u;
        for (; name && *name; ++name)
            hash = (hash ^ static_cast<uint8_t>(*name)) * 16777619u;
        return hash;
    }

    // The treadMaterialL/R names of every tracked ODF with a scroll, for
    // gpu_skinning.cpp, which builds no instanced twin for their clones (a
    // twin draws without the per-unit 1411 binding). Names only grow for
    // the process; Add refuses a full set so the caller can fail closed.
    constexpr size_t kMaxRegisteredTreadMaterials = 64;
    class TreadMaterialSet
    {
    public:
        // True when the name is in the set afterwards; false for an empty or
        // over-long name or a full set.
        bool Add(const char* name)
        {
            const size_t length = name ? std::strlen(name) : 0;
            if (length == 0 || length >= kTreadMaterialBytes)
                return false;
            if (Contains(name))
                return true;
            if (count_ >= kMaxRegisteredTreadMaterials)
                return false;
            std::memcpy(names_[count_++], name, length + 1);
            ++revision_;
            return true;
        }

        // Both names or neither (an empty name is skipped), so a refused ODF
        // leaves no name behind to lose its twin for nothing. False when a
        // name is over-long, both are empty, or the new ones do not fit.
        bool AddBoth(const char* first, const char* second)
        {
            const char* names[2] = { first, second };
            size_t needed = 0;
            bool any = false;
            for (int i = 0; i < 2; ++i)
            {
                const char* name = names[i];
                const size_t length = name ? std::strlen(name) : 0;
                if (length == 0)
                    continue;
                if (length >= kTreadMaterialBytes)
                    return false;
                any = true;
                const bool repeat = i == 1 && first && std::strcmp(first, name) == 0;
                if (!repeat && !Contains(name))
                    ++needed;
            }
            if (!any || count_ + needed > kMaxRegisteredTreadMaterials)
                return false;
            for (const char* name : names)
                if (name && name[0])
                    Add(name);
            return true;
        }

        // Exact name: callers pass the source material, never a clone name.
        bool Contains(const char* name) const
        {
            if (!name || !name[0])
                return false;
            for (size_t i = 0; i < count_; ++i)
                if (std::strcmp(names_[i], name) == 0)
                    return true;
            return false;
        }

        // Bumped once per new name.
        uint32_t Revision() const { return revision_; }
        size_t Count() const { return count_; }

    private:
        char names_[kMaxRegisteredTreadMaterials][kTreadMaterialBytes] = {};
        size_t count_ = 0;
        uint32_t revision_ = 0;
    };

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
