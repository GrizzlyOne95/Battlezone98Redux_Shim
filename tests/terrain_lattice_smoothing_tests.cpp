// CPU reference of TerrainTessellationSmoothing (include/terrain_lattice_smoothing.h):
// the clamped separable Catmull-Rom surface the terrain domain shader evaluates,
// the lattice <-> world mapping and the dirty-cluster windows.
#include "terrain_lattice_smoothing.h"
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <random>
#include <stdexcept>
using namespace BZROpenShim;
static void check(bool ok, const char* message) { if (!ok) throw std::runtime_error(message); }

static TerrainLattice::Grid RandomGrid(int width, int height, unsigned seed, int range)
{
    TerrainLattice::Grid grid{width, height, {}};
    grid.units.resize(std::size_t(width) * height);
    std::mt19937 random(seed);
    std::uniform_int_distribution<int> units(0, range);
    for (auto& unit : grid.units) unit = uint16_t(units(random));
    return grid;
}

// At every lattice sample the surface is the sample itself (interpolating).
static void TestExactAtSamples()
{
    const auto grid = RandomGrid(12, 10, 1, 4000);
    for (int z = 0; z < grid.height; ++z)
    for (int x = 0; x < grid.width; ++x)
    {
        const auto s = TerrainLattice::Evaluate(grid, float(x), float(z));
        check(s.h == grid(x, z), "surface not exact at a lattice sample");
    }
}

// Inside a cell the height never leaves the range of its four corners.
static void TestNoOvershoot()
{
    const auto grid = RandomGrid(16, 16, 2, 8191);
    std::mt19937 random(3);
    std::uniform_real_distribution<float> where(1.0f, 14.0f);
    for (int i = 0; i < 20000; ++i)
    {
        const float gx = where(random), gz = where(random);
        const int x = int(std::floor(gx)), z = int(std::floor(gz));
        const float lo = std::min({grid(x, z), grid(x + 1, z), grid(x, z + 1), grid(x + 1, z + 1)});
        const float hi = std::max({grid(x, z), grid(x + 1, z), grid(x, z + 1), grid(x + 1, z + 1)});
        const auto s = TerrainLattice::Evaluate(grid, gx, gz);
        check(std::isfinite(s.h) && std::isfinite(s.dx) && std::isfinite(s.dz), "non-finite surface");
        check(s.h >= lo - 1e-3f && s.h <= hi + 1e-3f, "surface overshoots the central 2x2 range");
    }
    // A single cliff step: the bicubic rings without the clamp.
    TerrainLattice::Grid cliff{8, 8, std::vector<uint16_t>(64, 0)};
    for (int z = 0; z < 8; ++z) for (int x = 4; x < 8; ++x) cliff.units[z * 8 + x] = 400;
    for (float gx = 2.0f; gx <= 5.0f; gx += 0.125f)
    {
        const float h = TerrainLattice::Evaluate(cliff, gx, 3.5f).h;
        check(h >= 0.0f && h <= 40.0f, "cliff step overshoots");
        if (gx < 3.0f || gx > 4.0f) check(h == (gx < 3.0f ? 0.0f : 40.0f), "flat side of a cliff moved");
    }
}

// Mirroring the lattice mirrors the surface (no axis or direction bias).
static void TestSymmetric()
{
    const auto grid = RandomGrid(9, 9, 4, 3000);
    TerrainLattice::Grid mirrorX = grid, mirrorZ = grid, transposed = grid;
    for (int z = 0; z < 9; ++z)
    for (int x = 0; x < 9; ++x)
    {
        mirrorX.units[z * 9 + x] = grid.units[z * 9 + (8 - x)];
        mirrorZ.units[z * 9 + x] = grid.units[(8 - z) * 9 + x];
    }
    for (float gz = 2.1f; gz <= 6.0f; gz += 0.23f)
    for (float gx = 2.1f; gx <= 6.0f; gx += 0.23f)
    {
        const auto s = TerrainLattice::Evaluate(grid, gx, gz);
        const auto x = TerrainLattice::Evaluate(mirrorX, 8.0f - gx, gz);
        const auto z = TerrainLattice::Evaluate(mirrorZ, gx, 8.0f - gz);
        check(std::abs(s.h - x.h) < 2e-3f && std::abs(s.dx + x.dx) < 1e-2f, "surface not symmetric in x");
        check(std::abs(s.h - z.h) < 2e-3f && std::abs(s.dz + z.dz) < 1e-2f, "surface not symmetric in z");
    }
}

// Approaching a cell border from either side gives the same height.
static void TestContinuousAcrossCells()
{
    const auto grid = RandomGrid(12, 12, 5, 2000);
    const float e = 1.0f / 4096.0f;
    float worst = 0.0f;
    for (int border = 2; border <= 9; ++border)
    for (float t = 2.0f; t <= 9.0f; t += 0.0625f)
    {
        const float b = float(border);
        const float along = TerrainLattice::Evaluate(grid, b, t).h;
        const float xl = TerrainLattice::Evaluate(grid, b - e, t).h, xr = TerrainLattice::Evaluate(grid, b + e, t).h;
        const float zl = TerrainLattice::Evaluate(grid, t, b - e).h, zr = TerrainLattice::Evaluate(grid, t, b + e).h;
        const float across = TerrainLattice::Evaluate(grid, t, b).h;
        const float gap = std::max({std::abs(xl - along), std::abs(xr - along), std::abs(zl - across), std::abs(zr - across)});
        // A continuous surface moves at most its steepest slope near the
        // border times the step (+ float rounding at ~200 m); a jump does not.
        float slope = 0.0f;
        for (const float d : {-e, 0.0f, e})
        {
            const auto sx = TerrainLattice::Evaluate(grid, b + d, t), sz = TerrainLattice::Evaluate(grid, t, b + d);
            slope = std::max({slope, std::abs(sx.dx), std::abs(sx.dz), std::abs(sz.dx), std::abs(sz.dz)});
        }
        const float tolerance = 1.25f * slope * e + 1e-4f;
        if (gap > tolerance)
        {
            std::fprintf(stderr, "border %d t %.4f gap %.6f tolerance %.6f\n", border, t, gap, tolerance);
            check(false, "surface jumps at a cell border");
        }
        worst = std::max(worst, gap);
    }
    check(worst < 0.1f, "surface border gaps implausibly large");
    // The slopes are the derivatives of the height (finite differences). On
    // smooth monotone ground no pass clamps; where a clamp engages the surface
    // is only C0 (a slope kink at the clamp line), so random data is not used.
    TerrainLattice::Grid smooth{12, 12, std::vector<uint16_t>(144)};
    for (int z = 0; z < 12; ++z) for (int x = 0; x < 12; ++x)
        smooth.units[z * 12 + x] = uint16_t(3 * x * x + 2 * x * z + 5 * z * z + 40 * x);
    for (float gz = 2.05f; gz < 9.0f; gz += 0.41f)
    for (float gx = 2.1f; gx < 9.0f; gx += 0.37f)
    {
        const float h = 1e-2f;
        const auto s = TerrainLattice::Evaluate(smooth, gx, gz);
        const float fd = (TerrainLattice::Evaluate(smooth, gx + h, gz).h - TerrainLattice::Evaluate(smooth, gx - h, gz).h) / (2 * h);
        const float fz = (TerrainLattice::Evaluate(smooth, gx, gz + h).h - TerrainLattice::Evaluate(smooth, gx, gz - h).h) / (2 * h);
        check(std::abs(fd - s.dx) < 0.02f * (1.0f + std::abs(fd)), "x slope does not match the surface");
        check(std::abs(fz - s.dz) < 0.02f * (1.0f + std::abs(fz)), "z slope does not match the surface");
    }
}

static void TestFlatAndPlanarAreUnchanged()
{
    TerrainLattice::Grid flat{6, 6, std::vector<uint16_t>(36, 1234)};
    TerrainLattice::Grid ramp{6, 6, std::vector<uint16_t>(36)};
    for (int z = 0; z < 6; ++z) for (int x = 0; x < 6; ++x) ramp.units[z * 6 + x] = uint16_t(100 + 30 * x + 7 * z);
    for (float g = 1.0f; g < 4.0f; g += 0.125f)
    {
        const auto f = TerrainLattice::Evaluate(flat, g, 5.0f - g);
        check(std::abs(f.h - 123.4f) < 1e-4f, "flat lattice not flat");
        check(f.dx == 0.0f && f.dz == 0.0f, "flat lattice has slope");
        // A plane is reproduced exactly (Catmull-Rom reproduces linear data).
        const auto r = TerrainLattice::Evaluate(ramp, g, 4.0f - g * 0.5f);
        const float expected = (100.0f + 30.0f * g + 7.0f * (4.0f - g * 0.5f)) * 0.1f;
        check(std::abs(r.h - expected) < 1e-3f, "planar lattice not reproduced");
        check(std::abs(r.dx - 3.0f) < 1e-3f && std::abs(r.dz - 0.7f) < 1e-3f, "planar slope wrong");
    }
    check(TerrainLattice::Delta(10.0f, 3.0f, 4.0f) == 4.0f && TerrainLattice::Delta(-10.0f, 3.0f, 4.0f) == -4.0f &&
        TerrainLattice::Delta(5.0f, 4.0f, 4.0f) == 1.0f && TerrainLattice::Delta(NAN, 0.0f, 4.0f) == 0.0f, "delta clamp wrong");
    check(TerrainLattice::ClampMax(0.1f) == 0.5f && TerrainLattice::ClampMax(40.0f) == 12.0f &&
        TerrainLattice::ClampMax(NAN) == 4.0f && TerrainLattice::ClampMax(6.0f) == 6.0f, "max clamp wrong");
}

// Docs/terrain-paint.md native frame: texel (tx, tz) is world X = 5 (tx - 128
// columns), Z = -5 (tz - 128 rows); world slopes follow.
static void TestMappingAndWindows()
{
    const TerrainLattice::Mapping m{5, 3};
    check(m.Width() == 1280 && m.Height() == 768, "lattice size");
    for (int tz = 0; tz < m.Height(); tz += 37)
    for (int tx = 0; tx < m.Width(); tx += 41)
    {
        const float worldX = 5.0f * float(tx - 128 * 5), worldZ = -5.0f * float(tz - 128 * 3);
        check(m.LatticeX(worldX) == float(tx) && m.LatticeZ(worldZ) == float(tz), "mapping is not the documented frame");
    }
    TerrainLattice::Grid ramp{m.Width(), m.Height(), std::vector<uint16_t>(std::size_t(m.Width()) * m.Height())};
    for (int z = 0; z < m.Height(); ++z) for (int x = 0; x < m.Width(); ++x) ramp.units[std::size_t(z) * m.Width() + x] = uint16_t(x + 2 * z);
    // Height rises 0.1 m per texel in +x (+X) and 0.2 m per texel in +z (-Z).
    const auto s = TerrainLattice::EvaluateWorld(ramp, m, 12.5f, -40.0f);
    check(std::abs(s.dx - 0.02f) < 1e-4f && std::abs(s.dz + 0.04f) < 1e-4f, "world slopes wrong");
    const auto corner = TerrainLattice::ClusterWindow(m, 0, 0, 0, 0);
    check(corner.left == 0 && corner.top == 0 && corner.right == 81 && corner.bottom == 81, "corner window not clipped");
    const auto inner = TerrainLattice::ClusterWindow(m, 2, 1, 1, 3);
    check(inner.left == 512 + 64 - 16 && inner.right == inner.left + 97 && inner.top == 256 + 192 - 16 &&
        inner.bottom == inner.top + 97, "inner window wrong");
    const auto edge = TerrainLattice::ClusterWindow(m, 4, 2, 3, 3);
    check(edge.right == m.Width() && edge.bottom == m.Height() && !TerrainLattice::Empty(edge), "edge window not clipped");
}

int main()
{
    try
    {
        TestExactAtSamples();
        TestNoOvershoot();
        TestSymmetric();
        TestContinuousAcrossCells();
        TestFlatAndPlanarAreUnchanged();
        TestMappingAndWindows();
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << "\n";
        return 1;
    }
    std::cout << "terrain_lattice_smoothing_tests passed\n";
    return 0;
}
