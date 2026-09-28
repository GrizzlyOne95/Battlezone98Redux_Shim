#include "terrain_tile_blend.h"

#include <cstdio>
#include <limits>
#include "test_check.h"

using OpenShimTest::Check;

using namespace BZROpenShim;


int main()
{
    Check(NormalizeTerrainTileBlend(-2.0f) == 0.0f, "negative values clamp to zero");
    Check(NormalizeTerrainTileBlend(2.0f) == 1.0f, "values above one clamp to one");
    Check(NormalizeTerrainTileBlend(std::numeric_limits<float>::quiet_NaN()) == 1.0f,
        "NaN preserves stock behavior");
    Check(TerrainTileBlendEdgeAlpha(0.0f) == 255, "zero blend is fully opaque");
    Check(TerrainTileBlendEdgeAlpha(0.5f) == 128, "half blend rounds to alpha 128");
    Check(TerrainTileBlendEdgeAlpha(1.0f) == 0, "one blend preserves stock zero edge alpha");

    if (OpenShimTest::FailureCount() == 0)
        std::puts("terrain tile blend tests passed");
    return OpenShimTest::ExitCode();
}
