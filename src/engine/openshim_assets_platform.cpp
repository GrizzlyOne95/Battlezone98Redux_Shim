// Win32 adapter for the asset-capability service.
//
// src/engine/openshim_assets.cpp is deliberately OS-independent so the Linux
// CTest workflow can build and run it. The two facts that core cannot discover
// on its own live here: where the game is installed, and what openshim.ini
// configured for the HD terrain manifest.
//
// The manifest value is read through GetEnvironmentVariableA, which
// openshim_env_config.h force-includes and redirects to the openshim.ini
// resolver ([Terrain] TerrainHdManifest, with the real process environment as
// the fallback). That is exactly the resolution terrain_proxy.cpp performs, so
// the capability probe and LoadTerrainHdManifest() always agree on which file
// is authoritative.

#include "openshim_assets.h"

#if defined(_WIN32)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

namespace BZROpenShim::Assets
{

AssetRuntimeEnvironment ResolveAssetRuntimeEnvironment()
{
    AssetRuntimeEnvironment env;

    char modulePath[MAX_PATH] = {};
    const DWORD len = GetModuleFileNameA(nullptr, modulePath, MAX_PATH);
    if (len != 0 && len < MAX_PATH)
        env.gameDir = std::filesystem::path(modulePath).parent_path();

    char manifest[MAX_PATH] = {};
    const DWORD manifestLen =
        GetEnvironmentVariableA("OPENSHIM_TERRAIN_HD_MANIFEST", manifest, MAX_PATH);
    if (manifestLen != 0 && manifestLen < MAX_PATH)
        env.terrainHdManifest.assign(manifest, manifestLen);

    return env;
}

} // namespace BZROpenShim::Assets

#endif // _WIN32
