#pragma once

#include <cstddef>
#include <vector>

namespace BZROpenShim::FogWake
{
    struct Point { double x = 0; double z = 0; };

    struct Config
    {
        std::size_t width = 128;
        std::size_t height = 128;
        double cellSize = 1;
        Point origin; // Lower corner of the fixed world-space region.
        double recoverySeconds = 4; // Clearance falls to 1/e after this time.
        double maxSegmentLength = 64; // Longer moves are treated as teleports.
    };

    // CPU reference implementation. Stores clearance (0 = undisturbed fog,
    // 1 = fully cleared), not opacity. No engine pointers, GPU resources or Lua.
    // All calls belong to one owning thread. Configure/Reset start a new region;
    // the caller must also discard previous vehicle positions at session changes.
    class Field
    {
    public:
        // Invalid configuration leaves the previous region unchanged.
        bool Configure(const Config& config);
        void Reset() noexcept;
        // Swept capsule with a soft radial edge; strength is clamped to [0,1].
        // Stationary stamps are supported for a future hover/downwash emitter.
        bool Stamp(Point previous, Point current, double radius, double strength);
        // Semi-Lagrangian wind transport + exponential refill. Outside the
        // region is undisturbed fog. Invalid inputs leave the field unchanged.
        bool Advance(double seconds, Point wind);
        float Sample(Point world) const noexcept;
        const Config& Settings() const noexcept { return config_; }
        // Row-major z * width + x, sampled at cell centres. For future upload.
        const std::vector<float>& Clearance() const noexcept { return cells_; }

    private:
        Config config_;
        std::vector<float> cells_;
        std::vector<float> scratch_;
    };
}
