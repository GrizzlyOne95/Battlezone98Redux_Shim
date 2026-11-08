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

    // RUN_STARTED fires before the world loader writes the new TRN name and
    // builds the terrain vertex buffer, so the boundary only arms the blend.
    // The world render queue keeps running (and still holds the previous
    // mission's TRN name) during the load, so a render tick may apply only
    // after the terrain proxy has selected a zone of the new world. A sim
    // tick implies the new world is loaded and may always apply.
    void RequestTerrainTileBlendAtFirstSimTick();
    void NotifyTerrainTileBlendWorldReady();
    void TerrainTileBlendSimTick();
    void TerrainTileBlendRenderTick();
    void ApplyTerrainTileBlendForCurrentMission();
}
