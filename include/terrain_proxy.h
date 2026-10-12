#pragma once
struct ID3D11DeviceContext;

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
    // capture is configured or an authored normal atlas awaits its resource
    // group. Parity captures use a reproducible frame index; deferred surface
    // installation stays on the game thread.
    void TerrainProxyRenderFrameTick();
    // Read-only immediate-context draw evidence. Fails closed if the terrain
    // owner cannot be locked or the actual PS resource differs from our atlas.
    bool TerrainSurfaceNormalBound(ID3D11DeviceContext* context);
}
