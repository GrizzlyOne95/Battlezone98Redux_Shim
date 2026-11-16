#pragma once
// soak_telemetry_policy.h
// BZR Open Shim - pure decisions behind the opt-in soak telemetry
// (src/patches/soak_telemetry.cpp): stall episodes, sudden lighting steps and
// the per-field / capture rate limits. No Windows or engine dependency, so it
// is host-tested (tests/soak_telemetry_policy_tests.cpp).

#include <cmath>
#include <cstdint>

namespace BZROpenShim::SoakTelemetry
{
    // A lighting value "jumps" when it steps by more than these between two
    // consecutive sampled frames; slow drift never crosses them.
    inline constexpr float kColourChannelStep = 0.08f;
    inline constexpr float kDirectionStepDegrees = 5.0f;
    inline constexpr float kFogDistanceStepFraction = 0.10f;

    inline constexpr uint64_t kFieldLogIntervalMs = 2000;
    inline constexpr uint64_t kCaptureIntervalMs = 10000;
    inline constexpr unsigned kCaptureLimit = 30;

    // Any of r, g, b moved by more than kColourChannelStep.
    inline bool ColourJumped(const float before[3], const float after[3])
    {
        for (int i = 0; i < 3; ++i)
        {
            if (std::fabs(after[i] - before[i]) > kColourChannelStep)
                return true;
        }
        return false;
    }

    // The angle between the two directions exceeds kDirectionStepDegrees.
    // A zero-length direction only counts as a jump when the other is not.
    inline bool DirectionJumped(const float before[3], const float after[3])
    {
        const double lb = std::sqrt(double(before[0]) * before[0] + double(before[1]) * before[1] +
                                    double(before[2]) * before[2]);
        const double la = std::sqrt(double(after[0]) * after[0] + double(after[1]) * after[1] +
                                    double(after[2]) * after[2]);
        constexpr double kTiny = 1e-6;
        if (lb < kTiny || la < kTiny)
            return (lb < kTiny) != (la < kTiny);
        double cosine = (double(before[0]) * after[0] + double(before[1]) * after[1] +
                         double(before[2]) * after[2]) / (lb * la);
        if (cosine > 1.0)
            cosine = 1.0;
        if (cosine < -1.0)
            cosine = -1.0;
        const double degrees = std::acos(cosine) * (180.0 / 3.14159265358979323846);
        return degrees > kDirectionStepDegrees;
    }

    // Fog start/end moved by more than kFogDistanceStepFraction of the old
    // value. From 0, any move of at least one world unit counts.
    inline bool FogDistanceJumped(float before, float after)
    {
        const float delta = std::fabs(after - before);
        const float base = std::fabs(before);
        if (base < 1.0f)
            return delta >= 1.0f;
        return delta > base * kFogDistanceStepFraction;
    }

    // At most one line per field per kFieldLogIntervalMs.
    struct FieldRateLimit
    {
        bool logged = false;
        uint64_t lastMs = 0;

        bool Allow(uint64_t nowMs)
        {
            if (logged && nowMs - lastMs < kFieldLogIntervalMs)
                return false;
            logged = true;
            lastMs = nowMs;
            return true;
        }
    };

    // At most kCaptureLimit captures per process, one per kCaptureIntervalMs.
    struct CaptureBudget
    {
        unsigned taken = 0;
        uint64_t lastMs = 0;

        bool Allow(uint64_t nowMs)
        {
            if (taken >= kCaptureLimit || (taken > 0 && nowMs - lastMs < kCaptureIntervalMs))
                return false;
            ++taken;
            lastMs = nowMs;
            return true;
        }
    };

    // One stall episode at a time over a monotonically increasing progress
    // counter (a GPU fence's completed value, or the render-thread frame
    // number). "pending" says whether there is outstanding work the counter
    // should reach; with nothing pending the clock restarts every tick.
    enum class StallEvent
    {
        None,
        Began,  // stalledMs = how long the counter had not moved
        Ended,  // stalledMs = the whole episode, from the last progress
    };

    struct StallTracker
    {
        bool primed = false;
        bool inEpisode = false;
        uint64_t lastValue = 0;
        uint64_t lastProgressMs = 0;

        void Reset(uint64_t nowMs)
        {
            primed = false;
            inEpisode = false;
            lastValue = 0;
            lastProgressMs = nowMs;
        }

        StallEvent Tick(uint64_t nowMs, uint64_t value, bool pending, uint64_t thresholdMs,
                        uint64_t& stalledMs)
        {
            stalledMs = 0;
            const bool moved = !primed || value != lastValue;
            primed = true;
            lastValue = value;
            if (moved || !pending)
            {
                const uint64_t since = lastProgressMs;
                lastProgressMs = nowMs;
                if (inEpisode)
                {
                    inEpisode = false;
                    stalledMs = nowMs - since;
                    return StallEvent::Ended;
                }
                return StallEvent::None;
            }
            if (!inEpisode && nowMs - lastProgressMs >= thresholdMs)
            {
                inEpisode = true;
                stalledMs = nowMs - lastProgressMs;
                return StallEvent::Began;
            }
            return StallEvent::None;
        }
    };
}
