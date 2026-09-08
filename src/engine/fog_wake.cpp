#include "fog_wake.h"

#include <algorithm>
#include <cmath>

namespace BZROpenShim::FogWake
{
    namespace
    {
        bool ValidPoint(Point p) noexcept
        {
            // Bound arithmetic as well as rejecting NaN/Inf.
            return std::isfinite(p.x) && std::isfinite(p.z)
                && std::abs(p.x) <= 1e9 && std::abs(p.z) <= 1e9;
        }
    }

    bool Field::Configure(const Config& c)
    {
        if (c.width == 0 || c.height == 0 || c.width > 1024 || c.height > 1024
            || !ValidPoint(c.origin) || !std::isfinite(c.cellSize)
            || c.cellSize < 0.01 || c.cellSize > 10000
            || !std::isfinite(c.recoverySeconds) || c.recoverySeconds <= 0
            || !std::isfinite(c.maxSegmentLength) || c.maxSegmentLength <= 0
            || c.maxSegmentLength > 1e6)
            return false;
        std::vector<float> cells(c.width * c.height, 0);
        std::vector<float> scratch(c.width * c.height, 0);
        cells_.swap(cells);
        scratch_.swap(scratch);
        config_ = c;
        return true;
    }

    void Field::Reset() noexcept
    {
        std::fill(cells_.begin(), cells_.end(), 0.0f);
        std::fill(scratch_.begin(), scratch_.end(), 0.0f);
    }

    float Field::Sample(Point p) const noexcept
    {
        if (cells_.empty() || !ValidPoint(p)) return 0;
        const double gx = (p.x - config_.origin.x) / config_.cellSize - 0.5;
        const double gz = (p.z - config_.origin.z) / config_.cellSize - 0.5;
        if (gx <= -1 || gz <= -1 || gx >= config_.width || gz >= config_.height)
            return 0;
        const int x = static_cast<int>(std::floor(gx));
        const int z = static_cast<int>(std::floor(gz));
        const double fx = gx - x, fz = gz - z;
        const auto at = [&](int ix, int iz) -> double {
            if (ix < 0 || iz < 0 || ix >= static_cast<int>(config_.width)
                || iz >= static_cast<int>(config_.height)) return 0;
            return cells_[static_cast<std::size_t>(iz) * config_.width + ix];
        };
        return static_cast<float>((at(x,z)*(1-fx)+at(x+1,z)*fx)*(1-fz)
            + (at(x,z+1)*(1-fx)+at(x+1,z+1)*fx)*fz);
    }

    bool Field::Stamp(Point a, Point b, double radius, double strength)
    {
        if (cells_.empty() || !ValidPoint(a) || !ValidPoint(b)
            || !std::isfinite(radius) || radius <= 0 || radius > 1e6
            || !std::isfinite(strength)) return false;
        const double dx = b.x-a.x, dz = b.z-a.z;
        const double lengthSquared = dx*dx+dz*dz;
        if (lengthSquared > config_.maxSegmentLength * config_.maxSegmentLength)
            return false;
        strength = std::clamp(strength, 0.0, 1.0);
        // Clamp in floating point before integer conversion, including stamps
        // wholly outside the region. Work is bounded by the capsule's AABB.
        const auto bound = [&](double world, double origin, std::size_t size) {
            return static_cast<std::size_t>(std::clamp(
                std::floor((world-origin)/config_.cellSize), 0.0, double(size)));
        };
        const auto x0 = bound(std::min(a.x,b.x)-radius, config_.origin.x, config_.width);
        const auto z0 = bound(std::min(a.z,b.z)-radius, config_.origin.z, config_.height);
        const auto x1 = bound(std::max(a.x,b.x)+radius+config_.cellSize, config_.origin.x, config_.width);
        const auto z1 = bound(std::max(a.z,b.z)+radius+config_.cellSize, config_.origin.z, config_.height);
        for (std::size_t z=z0; z<z1; ++z)
            for (std::size_t x=x0; x<x1; ++x)
            {
                const double px = config_.origin.x+(x+0.5)*config_.cellSize-a.x;
                const double pz = config_.origin.z+(z+0.5)*config_.cellSize-a.z;
                const double t = lengthSquared > 0
                    ? std::clamp((px*dx+pz*dz)/lengthSquared, 0.0, 1.0) : 0;
                const double distance = std::hypot(px-t*dx, pz-t*dz);
                const double u = std::clamp(1-distance/radius, 0.0, 1.0);
                const float cleared = static_cast<float>(strength*u*u*(3-2*u));
                auto& cell = cells_[z*config_.width+x];
                // Repeated observations must not amplify clearance with FPS.
                cell = std::max(cell, cleared);
            }
        return true;
    }

    bool Field::Advance(double seconds, Point wind)
    {
        if (cells_.empty() || !std::isfinite(seconds) || seconds < 0
            || !ValidPoint(wind)) return false;
        if (seconds == 0) return true;
        const double decay = std::exp(-seconds/config_.recoverySeconds);
        if (decay < 1e-8) { Reset(); return true; }
        const double shiftX = wind.x*seconds, shiftZ = wind.z*seconds;
        if (!std::isfinite(shiftX) || !std::isfinite(shiftZ)) return false;
        for (std::size_t z=0; z<config_.height; ++z)
            for (std::size_t x=0; x<config_.width; ++x)
                scratch_[z*config_.width+x] = static_cast<float>(decay * Sample({
                    config_.origin.x+(x+0.5)*config_.cellSize-shiftX,
                    config_.origin.z+(z+0.5)*config_.cellSize-shiftZ}));
        cells_.swap(scratch_);
        return true;
    }
}
