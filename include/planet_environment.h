#pragma once

#include <string>

namespace BZROpenShim
{
    // Records the world prefix of a terrain detail-atlas open
    // ("...\\ma_detail_atlas.csv" -> "ma"). Thread-safe; ignores any other
    // name. Called from the file-open hooks while the map loads.
    void RecordTerrainWorldCodeFromAtlasPath(const std::string& path);

    // Last recorded world prefix, lowercase; empty before any map load.
    std::string LastTerrainWorldCode();

    // Called at the RUN_STARTED mission boundary. Requests the swap; the
    // render tick performs it.
    void ApplyPlanetEnvironmentForCurrentMission();

    // Render-thread tick. When a swap is pending and the neutral IBL cubemaps
    // are loaded, in the Enhanced profile on Direct3D 11, copies the world's
    // openshim_env_<code>_{prefilter,irradiance}.dds into them, or restores
    // the neutral contents when the world has no such files.
    void PlanetEnvironmentRenderFrameTick();
}
