#pragma once
#include <charconv>
#include <cstring>
#include <string>

namespace BZROpenShim::TerrainMeshName
{
    // True when name is exactly the stock spelling the engine gives a terrain
    // cluster mesh, "RenderableTileCluster_<zoneX>x<zoneZ>_<clusterX>x<clusterZ>"
    // with plain decimal integers. Any name this accepts also passes the
    // general "%dx%d_%dx%d%n" sscanf check with the same four values, so a
    // caller can use it as a fast path and fall back to sscanf only on a miss.
    // It runs for 16 clusters per zone per frame, where sscanf showed up in
    // CPU samples; this formats into a stack buffer and compares.
    inline bool IsCanonical(const std::string& name, int zoneX, int zoneZ, int clusterX, int clusterZ)
    {
        static constexpr char kPrefix[] = "RenderableTileCluster_";
        char buffer[sizeof(kPrefix) + 4 * 12];
        char* at = buffer;
        char* const end = buffer + sizeof(buffer);
        std::memcpy(at, kPrefix, sizeof(kPrefix) - 1);
        at += sizeof(kPrefix) - 1;
        const int values[4] = { zoneX, zoneZ, clusterX, clusterZ };
        const char separators[3] = { 'x', '_', 'x' };
        for (int i = 0; i < 4; ++i)
        {
            if (i > 0) *at++ = separators[i - 1];
            const auto result = std::to_chars(at, end, values[i]);
            if (result.ec != std::errc()) return false;
            at = result.ptr;
        }
        const size_t length = static_cast<size_t>(at - buffer);
        return name.size() == length && std::memcmp(name.data(), buffer, length) == 0;
    }
}
