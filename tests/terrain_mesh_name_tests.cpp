#include "terrain_mesh_name.h"

#include <climits>
#include <cstdio>
#include <string>
#include "test_check.h"

#ifdef _MSC_VER
#define OPENSHIM_TEST_SSCANF sscanf_s
#else
#define OPENSHIM_TEST_SSCANF std::sscanf
#endif

using OpenShimTest::Check;
using BZROpenShim::TerrainMeshName::IsCanonical;

namespace
{
    // The original check in ResolveClusterCandidate.
    bool SscanfMatches(const std::string& name, int zx, int zz, int cx, int cz)
    {
        int a = 0, b = 0, c = 0, d = 0, consumed = 0;
        return OPENSHIM_TEST_SSCANF(name.c_str(), "RenderableTileCluster_%dx%d_%dx%d%n", &a, &b, &c, &d, &consumed) == 4 &&
            consumed == static_cast<int>(name.size()) && a == zx && b == zz && c == cx && d == cz;
    }
}

int main()
{
    Check(IsCanonical("RenderableTileCluster_3x-2_1x0", 3, -2, 1, 0), "stock spelling matches");
    Check(IsCanonical("RenderableTileCluster_0x0_0x0", 0, 0, 0, 0), "zero coordinates match");
    Check(!IsCanonical("RenderableTileCluster_3x-2_1x0", 3, -2, 1, 1), "different cluster rejected");
    Check(!IsCanonical("RenderableTileCluster_3x-2_1x0 ", 3, -2, 1, 0), "trailing text rejected");
    Check(!IsCanonical("RenderableTileCluster_3x-2_1x", 3, -2, 1, 0), "truncated name rejected");
    Check(!IsCanonical("RenderableTileCluster_03x-2_1x0", 3, -2, 1, 0), "non-canonical spelling left to sscanf");
    Check(!IsCanonical("", 0, 0, 0, 0), "empty name rejected");
    const std::string extreme = "RenderableTileCluster_" + std::to_string(INT_MIN) + "x" +
        std::to_string(INT_MAX) + "_" + std::to_string(INT_MIN) + "x" + std::to_string(INT_MAX);
    Check(IsCanonical(extreme, INT_MIN, INT_MAX, INT_MIN, INT_MAX), "longest values fit the buffer");

    // A fast-path accept must always be a sscanf accept with the same values,
    // and on stock names the two agree in both directions.
    const char* odd[] = { "RenderableTileCluster_+1x2_3x0", "RenderableTileCluster_ 1x2_3x0",
        "RenderableTileCluster_1x2_3x0x", "renderableTileCluster_1x2_3x0" };
    for (const char* name : odd)
        Check(!IsCanonical(name, 1, 2, 3, 0), "odd spelling never takes the fast path");
    for (int zx = -12; zx <= 12; ++zx)
    for (int zz = -12; zz <= 12; ++zz)
    for (int cx = 0; cx < 4; ++cx)
    for (int cz = 0; cz < 4; ++cz)
    {
        char name[96];
        std::snprintf(name, sizeof(name), "RenderableTileCluster_%dx%d_%dx%d", zx, zz, cx, cz);
        Check(IsCanonical(name, zx, zz, cx, cz) && SscanfMatches(name, zx, zz, cx, cz),
            "stock names agree with sscanf");
        Check(IsCanonical(name, zx, zz, cx, (cz + 1) % 4) == SscanfMatches(name, zx, zz, cx, (cz + 1) % 4),
            "mismatched slot agrees with sscanf");
    }
    return OpenShimTest::ExitCode();
}
