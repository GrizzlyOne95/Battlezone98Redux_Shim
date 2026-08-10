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
    // Redux never reaches either seam; they are kept for other builds and for
    // the record they produce if one ever fires.
    void TerrainProxySceneTeardownBegin(void* sceneManager, bool clearScene);
    void TerrainProxySceneTeardownComplete(void* sceneManager, bool clearScene);

    // Called by the mission lifetime seam in bzr_hooks (Redux's SetRunning).
    // Leaving RUN_STARTED is the point at which the mission stops being
    // simulated while its scene is still alive. No-op unless Phase 2 is active.
    void TerrainProxyMissionRunStateChanged(int previousState, int currentState);

    // Called once per rendered world frame from the existing legacy world
    // render-queue detour. Does nothing unless the opt-in Phase 3A frame
    // capture is configured; it exists so parity captures can be taken at a
    // reproducible frame index rather than at an arbitrary wall-clock moment.
    void TerrainProxyRenderFrameTick();
}
