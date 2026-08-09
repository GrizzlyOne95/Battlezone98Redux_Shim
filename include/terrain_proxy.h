#pragma once

namespace BZROpenShim
{
    // Starts the disabled-by-default Phase 2 terrain proxy/capture worker.
    // The worker installs no hooks unless an opt-in setting is present and
    // both the executable and OgreMain.dll match the pinned release build.
    void InitializeTerrainProxyPhase2();

    // Stops discovery and makes the process-lifetime detours inert. Ogre
    // scene resources are normally released by the game's teardown path.
    void ShutdownTerrainProxyPhase2();

    // Called by the existing SceneManager teardown detours. Calls can nest
    // because clearScene invokes destroyAllMovableObjects internally.
    void TerrainProxySceneTeardownBegin(void* sceneManager, bool clearScene);
    void TerrainProxySceneTeardownComplete(void* sceneManager, bool clearScene);
}
