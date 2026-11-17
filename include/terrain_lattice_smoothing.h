#pragma once
// TerrainTessellationSmoothing: a smooth surface through the native 5 m height
// lattice, evaluated by the terrain domain shader. This header is the CPU
// reference of the shader curve (tests/terrain_lattice_smoothing_tests.cpp and
// the WARP test compare against it) and of the lattice <-> world mapping.
// Visual only: nothing here writes gameplay heights.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

namespace BZROpenShim::TerrainLattice
{
    constexpr float kSampleMeters = 5.0f;
    constexpr float kHeightUnitMeters = 0.1f;
    // Height bits as the engine's own readers mask them (live paint, 0.1 m units).
    constexpr uint16_t kHeightMask = 0x1FFF;
    constexpr int kZoneSamples = 256;
    constexpr int kClusterSamples = 64;
    constexpr int kClusterAxisCount = 4;
    // A dirty cluster re-reads its 65x65 window plus this margin per side, so
    // the overlapping native patches and the 4x4 neighbourhood stay covered.
    constexpr int kDirtyMargin = 16;
    // Per-axis cap (16 runtime zones, 20 km): 32 MB of CPU copy at most in the
    // 32-bit process. Larger maps decline smoothing.
    constexpr int kMaxTextureSize = 4096; // at 4096^2: 32 MB R16 texture + a 32 MB CPU copy (units) in the 32-bit process
    constexpr float kDefaultMax = 4.0f, kMinimumMax = 0.5f, kMaximumMax = 12.0f;

    inline float ClampMax(float value)
    {
        return std::isfinite(value) ? std::clamp(value, kMinimumMax, kMaximumMax) : kDefaultMax;
    }

    // The runtime zone rectangle (one zone more per axis than the file). Texel
    // (tx, tz) holds storage sample (baseX + tx, baseZ + tz) with
    // baseX = minZoneX * 256 + originX - 128 (the lowest zone's first sample).
    // File sample sx = tx - 128 sits at world X = 5 (sx - 128 fileZonesX) and
    // rows run toward -Z (Docs/terrain-paint.md, "Native terrain frame"), so
    // X = 5 (tx - 128 columns) and Z = -5 (tz - 128 rows). The install checks
    // this against a live cluster's vertex heights before smoothing is used.
    struct Mapping
    {
        int columns = 0, rows = 0;
        int Width() const { return columns * kZoneSamples; }
        int Height() const { return rows * kZoneSamples; }
        float OffsetX() const { return 128.0f * float(columns); }
        float OffsetZ() const { return 128.0f * float(rows); }
        // Same expression and order as the shader (TerrainLatticeSurface).
        float LatticeX(float worldX) const { return worldX * 0.2f + OffsetX(); }
        float LatticeZ(float worldZ) const { return OffsetZ() - worldZ * 0.2f; }
    };

    struct Rect { int left = 0, top = 0, right = 0, bottom = 0; }; // half-open
    inline bool Empty(const Rect& r) { return r.right <= r.left || r.bottom <= r.top; }

    // Texels a dirty cluster can change: its 65x65 window plus the margin,
    // clipped to the texture. zoneColumn/zoneRow count from the lowest zone.
    inline Rect ClusterWindow(const Mapping& m, int zoneColumn, int zoneRow, int clusterX, int clusterZ)
    {
        const int x0 = zoneColumn * kZoneSamples + clusterX * kClusterSamples - kDirtyMargin;
        const int z0 = zoneRow * kZoneSamples + clusterZ * kClusterSamples - kDirtyMargin;
        const int span = kClusterSamples + 1 + 2 * kDirtyMargin;
        Rect r;
        r.left = std::clamp(x0, 0, m.Width()); r.right = std::clamp(x0 + span, 0, m.Width());
        r.top = std::clamp(z0, 0, m.Height()); r.bottom = std::clamp(z0 + span, 0, m.Height());
        return r;
    }

    // One Catmull-Rom segment between p1 (t = 0) and p2 (t = 1), clamped to
    // [min(p1,p2), max(p1,p2)]. Exact at t = 0. clampedTo is 1 or 2 when the
    // clamp holds the value at that endpoint (the slope is then 0).
    struct Segment { float h = 0, slope = 0; int clampedTo = 0; };
    inline Segment CatmullRom(float p0, float p1, float p2, float p3, float t)
    {
        const float a = (-p0 + 3.0f * p1) + (p3 - 3.0f * p2);
        const float b = (2.0f * p0 - 5.0f * p1) + (4.0f * p2 - p3);
        const float c = p2 - p0;
        Segment s;
        s.h = 0.5f * (((a * t + b) * t + c) * t) + p1;
        s.slope = 0.5f * ((3.0f * a * t + 2.0f * b) * t + c);
        const float lo = (std::min)(p1, p2), hi = (std::max)(p1, p2);
        if (s.h < lo || s.h > hi)
        {
            const bool low = s.h < lo;
            s.h = low ? lo : hi;
            s.clampedTo = (low ? p1 <= p2 : p1 > p2) ? 1 : 2;
            s.slope = 0.0f;
        }
        return s;
    }

    // Catmull-Rom basis weights of p0..p3 at t (they sum to 1).
    inline void CatmullRomWeights(float t, float w[4])
    {
        const float t2 = t * t, t3 = t2 * t;
        w[0] = 0.5f * (-t + 2.0f * t2 - t3);
        w[1] = 0.5f * (2.0f - 5.0f * t2 + 3.0f * t3);
        w[2] = 0.5f * (t + 4.0f * t2 - 3.0f * t3);
        w[3] = 0.5f * (t3 - t2);
    }

    // Height (metres) and slope per lattice texel along +x and +z.
    struct Surface { float h = 0, dx = 0, dz = 0; };

    // Separable bicubic: Catmull-Rom along x for the four rows, then along z.
    // Each 1D pass clamps to its own segment, so the result never leaves the
    // central 2x2 range and stays continuous across cell borders (both cells
    // agree on the shared row/column). fetch(x, z) returns metres for any
    // integer texel; callers clamp indices at the texture edge.
    template<class Fetch>
    Surface Evaluate(const Fetch& fetch, float gx, float gz)
    {
        const float cx = std::floor(gx), cz = std::floor(gz);
        const int ix = int(cx), iz = int(cz);
        const float tx = gx - cx, tz = gz - cz;
        float row[4], rowSlope[4];
        for (int r = 0; r < 4; ++r)
        {
            const int z = iz - 1 + r;
            const Segment s = CatmullRom(fetch(ix - 1, z), fetch(ix, z), fetch(ix + 1, z), fetch(ix + 2, z), tx);
            row[r] = s.h; rowSlope[r] = s.slope;
        }
        const Segment column = CatmullRom(row[0], row[1], row[2], row[3], tz);
        Surface out;
        out.h = column.h;
        out.dz = column.slope;
        if (column.clampedTo) out.dx = rowSlope[column.clampedTo];
        else
        {
            float w[4]; CatmullRomWeights(tz, w);
            out.dx = w[0] * rowSlope[0] + w[1] * rowSlope[1] + w[2] * rowSlope[2] + w[3] * rowSlope[3];
        }
        return out;
    }

    // Reference over a row-major texture of masked height units, with edge
    // clamping like the shader's Load.
    struct Grid
    {
        int width = 0, height = 0;
        std::vector<uint16_t> units;
        float operator()(int x, int z) const
        {
            x = std::clamp(x, 0, width - 1); z = std::clamp(z, 0, height - 1);
            return float(units[std::size_t(z) * width + x]) * kHeightUnitMeters;
        }
    };

    // World-space result: height and slope per world metre.
    inline Surface EvaluateWorld(const Grid& grid, const Mapping& m, float worldX, float worldZ)
    {
        Surface s = Evaluate(grid, m.LatticeX(worldX), m.LatticeZ(worldZ));
        s.dx *= 0.2f; s.dz *= -0.2f;
        return s;
    }

    // Visual offset relative to the stock (linear) surface, clamped to max.
    inline float Delta(float smooth, float linear, float max)
    {
        const float d = smooth - linear;
        return std::isfinite(d) ? std::clamp(d, -max, max) : 0.0f;
    }
}
