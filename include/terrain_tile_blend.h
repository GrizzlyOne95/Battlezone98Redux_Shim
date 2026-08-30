#pragma once

#include <cstdint>

namespace BZROpenShim
{
    // Public TRN semantics: 1.0 is Redux's normal five-unit seam fade and
    // 0.0 makes every terrain patch fully opaque up to its edge.
    inline constexpr float NormalizeTerrainTileBlend(float value) noexcept
    {
        if (value != value) // NaN: preserve stock behavior.
            return 1.0f;
        if (value <= 0.0f)
            return 0.0f;
        if (value >= 1.0f)
            return 1.0f;
        return value;
    }

    inline constexpr std::uint8_t TerrainTileBlendEdgeAlpha(float value) noexcept
    {
        const float blend = NormalizeTerrainTileBlend(value);
        return static_cast<std::uint8_t>((1.0f - blend) * 255.0f + 0.5f);
    }

    // Called at the proven RUN_STARTED mission boundary, after Redux has
    // loaded the current TRN and constructed its shared terrain vertex buffer.
    void ApplyTerrainTileBlendForCurrentMission();
}
