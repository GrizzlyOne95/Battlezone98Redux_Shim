#pragma once

#include "fog_wake.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace BZROpenShim::FogWake
{
    struct RuntimeConfig
    {
        Config field;                     // Clearance region; see fog_wake.h.
        double simulationHz = 30;         // Fixed cadence, independent of frame rate.
        double maxCatchUpSeconds = 0.25;  // Ceiling on one AdvanceTo's backlog.
        double radius = 4;                // Wake half-width in metres.
        double strength = 1;              // Clearance a full-strength pass leaves.
        double maxSpeed = 120;            // Above this a move is treated as a teleport.
        double forgetAfterSeconds = 2;    // Unobserved emitters are dropped.
        std::size_t maxEmitters = 256;    // Hard ceiling on tracked emitters.
    };

    // Drives a Field from live emitter observations.
    //
    // The engine reports emitter positions from hooks that may run any number of
    // times per simulation step -- once per camera, or not at all on a frame with
    // no emission -- so the runtime deliberately does not advance on observation.
    // Observations only record where an emitter is now; AdvanceTo consumes a
    // monotonic clock and steps the simulation a whole number of fixed ticks.
    // Calling it twice with the same timestamp, or once per camera, is therefore
    // harmless by construction rather than by the caller's discipline.
    //
    // Disabled until Configure succeeds, and Configure fails closed: an invalid
    // configuration leaves the runtime disabled rather than half-built. Single
    // owner thread, like Field.
    class Runtime
    {
    public:
        struct Stats
        {
            std::uint64_t steps = 0;       // Fixed ticks simulated.
            std::uint64_t stamps = 0;      // Sweeps written into the field.
            std::uint64_t teleports = 0;   // Sweeps rejected as discontinuous.
            std::uint64_t forgotten = 0;   // Emitters dropped as stale or evicted.
            std::uint64_t rejected = 0;    // Observations refused outright.
        };

        bool Configure(const RuntimeConfig& config);
        bool Enabled() const noexcept { return enabled_; }

        // Drops every emitter and clears the field. Call on mission load, mission
        // end, and anything else that invalidates engine object identity: an
        // emitter key is a raw engine pointer, and the allocator reuses those.
        void BeginSession(double nowSeconds) noexcept;
        void Shutdown() noexcept;

        // Records where an emitter is now. Never advances the simulation and
        // never stamps; a caller running once per camera costs one map write.
        // Returns false when the observation was refused.
        bool Observe(const void* emitter, Point position, double nowSeconds);
        void Forget(const void* emitter) noexcept;

        // While paused, wall-clock time passes without simulating and without
        // banking a backlog, so resuming does not discharge a burst of catch-up
        // steps into the field.
        void SetPaused(bool paused, double nowSeconds) noexcept;
        bool Paused() const noexcept { return paused_; }

        // Steps whole fixed ticks up to nowSeconds. Each tick advances recovery
        // and wind first, then stamps the sweep each emitter travelled during
        // that tick. Returns the number of ticks simulated.
        std::size_t AdvanceTo(double nowSeconds, Point wind);

        const Field& GetField() const noexcept { return field_; }
        const Stats& GetStats() const noexcept { return stats_; }
        std::size_t TrackedEmitters() const noexcept { return emitters_.size(); }

    private:
        struct Emitter
        {
            const void* key = nullptr;
            Point previous;      // Where its last stamp ended.
            Point latest;        // Most recent observation.
            double lastSeen = 0; // Observation clock, for staleness.
            bool seeded = false; // False until the first stamp origin is known.
        };

        Emitter* Find(const void* key) noexcept;
        void StepOnce(Point wind);
        void DropStale(double nowSeconds);

        RuntimeConfig config_;
        Field field_;
        std::vector<Emitter> emitters_;
        Stats stats_;
        double stepSeconds_ = 0;
        double accumulator_ = 0;
        double clock_ = 0;
        bool haveClock_ = false;
        bool enabled_ = false;
        bool paused_ = false;
    };
}
