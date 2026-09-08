#include "fog_wake_runtime.h"

#include <algorithm>
#include <cmath>

namespace BZROpenShim::FogWake
{
    namespace
    {
        bool FinitePoint(Point p) noexcept
        {
            return std::isfinite(p.x) && std::isfinite(p.z)
                && std::abs(p.x) <= 1e9 && std::abs(p.z) <= 1e9;
        }

        double Distance(Point a, Point b) noexcept
        {
            return std::hypot(b.x - a.x, b.z - a.z);
        }
    }

    bool Runtime::Configure(const RuntimeConfig& config)
    {
        if (!std::isfinite(config.simulationHz) || config.simulationHz <= 0
            || config.simulationHz > 1000
            || !std::isfinite(config.maxCatchUpSeconds) || config.maxCatchUpSeconds <= 0
            || config.maxCatchUpSeconds > 60
            || !std::isfinite(config.radius) || config.radius <= 0 || config.radius > 1e4
            || !std::isfinite(config.strength) || config.strength < 0 || config.strength > 1
            || !std::isfinite(config.maxSpeed) || config.maxSpeed <= 0 || config.maxSpeed > 1e6
            || !std::isfinite(config.forgetAfterSeconds) || config.forgetAfterSeconds <= 0
            || config.maxEmitters == 0 || config.maxEmitters > 4096)
        {
            enabled_ = false;
            return false;
        }

        // Configure the field before adopting anything: a rejected field
        // configuration must leave the runtime disabled rather than running with
        // a region the caller did not ask for.
        if (!field_.Configure(config.field))
        {
            enabled_ = false;
            return false;
        }

        config_ = config;
        stepSeconds_ = 1.0 / config.simulationHz;
        emitters_.clear();
        emitters_.reserve(config.maxEmitters);
        stats_ = Stats{};
        accumulator_ = 0;
        clock_ = 0;
        haveClock_ = false;
        paused_ = false;
        enabled_ = true;
        return true;
    }

    void Runtime::BeginSession(double nowSeconds) noexcept
    {
        emitters_.clear();
        field_.Reset();
        accumulator_ = 0;
        paused_ = false;
        // A session boundary is also a clock discontinuity: the engine's timer
        // may restart, run backwards relative to the previous mission, or jump
        // by the length of a load. Re-seed rather than measuring across it.
        haveClock_ = std::isfinite(nowSeconds);
        clock_ = haveClock_ ? nowSeconds : 0.0;
    }

    void Runtime::Shutdown() noexcept
    {
        emitters_.clear();
        field_.Reset();
        accumulator_ = 0;
        haveClock_ = false;
        paused_ = false;
        enabled_ = false;
    }

    Runtime::Emitter* Runtime::Find(const void* key) noexcept
    {
        for (auto& emitter : emitters_)
        {
            if (emitter.key == key)
                return &emitter;
        }
        return nullptr;
    }

    bool Runtime::Observe(const void* emitter, Point position, double nowSeconds)
    {
        if (!enabled_ || emitter == nullptr || !FinitePoint(position)
            || !std::isfinite(nowSeconds))
        {
            ++stats_.rejected;
            return false;
        }

        if (Emitter* tracked = Find(emitter))
        {
            tracked->latest = position;
            tracked->lastSeen = nowSeconds;
            return true;
        }

        // The ceiling is a hard refusal rather than an eviction of somebody
        // else's history: silently recycling a slot would attribute one
        // vehicle's wake to another. Stale entries are reclaimed on each step.
        if (emitters_.size() >= config_.maxEmitters)
        {
            ++stats_.rejected;
            return false;
        }

        Emitter fresh;
        fresh.key = emitter;
        fresh.previous = position;
        fresh.latest = position;
        fresh.lastSeen = nowSeconds;
        // A brand new emitter has no history, so its first step stamps a point
        // rather than a streak from wherever it happened to be created.
        fresh.seeded = true;
        emitters_.push_back(fresh);
        return true;
    }

    void Runtime::Forget(const void* emitter) noexcept
    {
        const auto it = std::find_if(emitters_.begin(), emitters_.end(),
            [emitter](const Emitter& e) { return e.key == emitter; });
        if (it != emitters_.end())
        {
            emitters_.erase(it);
            ++stats_.forgotten;
        }
    }

    void Runtime::SetPaused(bool paused, double nowSeconds) noexcept
    {
        if (paused_ == paused)
            return;

        paused_ = paused;
        if (!paused && std::isfinite(nowSeconds))
        {
            // Resume from now, not from when the pause started, so the pause
            // does not bank a backlog that discharges into the field at once.
            clock_ = nowSeconds;
            haveClock_ = true;
            accumulator_ = 0;
        }
    }

    void Runtime::DropStale(double nowSeconds)
    {
        const auto stale = [&](const Emitter& e) {
            return (nowSeconds - e.lastSeen) > config_.forgetAfterSeconds;
        };
        const auto it = std::remove_if(emitters_.begin(), emitters_.end(), stale);
        if (it != emitters_.end())
        {
            stats_.forgotten += static_cast<std::uint64_t>(
                std::distance(it, emitters_.end()));
            emitters_.erase(it, emitters_.end());
        }
    }

    void Runtime::StepOnce(Point wind)
    {
        // Recovery and transport first, then this tick's sweeps, so a wake is
        // written at full strength and decays from the following tick rather
        // than being decayed on the tick that created it.
        field_.Advance(stepSeconds_, wind);

        const double teleportDistance = config_.maxSpeed * stepSeconds_;
        for (auto& emitter : emitters_)
        {
            const Point from = emitter.previous;
            const Point to = emitter.latest;

            if (!emitter.seeded || Distance(from, to) > teleportDistance)
            {
                // A discontinuity is not a wake. Reseed so the *next* tick
                // measures from where the emitter actually is: leaving the old
                // origin in place would draw the rejected streak one tick later.
                emitter.previous = to;
                emitter.seeded = true;
                ++stats_.teleports;
                continue;
            }

            if (field_.Stamp(from, to, config_.radius, config_.strength))
                ++stats_.stamps;

            emitter.previous = to;
        }

        ++stats_.steps;
    }

    std::size_t Runtime::AdvanceTo(double nowSeconds, Point wind)
    {
        if (!enabled_ || !std::isfinite(nowSeconds) || !FinitePoint(wind))
            return 0;

        if (!haveClock_)
        {
            clock_ = nowSeconds;
            haveClock_ = true;
            return 0;
        }

        const double elapsed = nowSeconds - clock_;
        clock_ = nowSeconds;

        if (paused_)
            return 0;

        // A clock that went backwards is a discontinuity, not negative time.
        if (elapsed <= 0)
            return 0;

        accumulator_ += elapsed;
        if (accumulator_ > config_.maxCatchUpSeconds)
        {
            // A stall -- a load, a breakpoint, a long alt-tab -- must not be
            // repaid as a burst of ticks. Drop the excess and carry on.
            accumulator_ = config_.maxCatchUpSeconds;
        }

        std::size_t steps = 0;
        while (accumulator_ >= stepSeconds_)
        {
            accumulator_ -= stepSeconds_;
            if (steps == 0)
                DropStale(nowSeconds);
            StepOnce(wind);
            ++steps;
        }
        return steps;
    }
}
