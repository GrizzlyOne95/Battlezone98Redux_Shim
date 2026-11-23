#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <vector>

namespace BZROpenShim
{
    // Engine-facing glue for the interactive fog wake simulation.
    //
    // Off unless [Experimental] InteractiveFogWakes = 1 (or the
    // OPENSHIM_INTERACTIVE_FOG_WAKES environment name; an ini value, even 0,
    // wins over the environment). Maintains the clearance field; the render
    // spike (fog_wake_render.cpp) draws it as DX11 ground-fog layers. With the
    // feature disabled every entry point below is a single atomic read.
    //
    // See Docs/INTERACTIVE_FOG_WAKES.md.

    bool FogWakeFeatureEnabled();

    // Mission run-state transitions. Emitter identity is a raw engine pointer,
    // so a session boundary must discard tracking as well as the field.
    void FogWakeNotifyMissionRunStateChanged(bool running);

    // Reports where an emitter is now, in world XZ. Never simulates: safe from a
    // hook that runs more than once per simulation step.
    void FogWakeObserveEmitter(const void* emitter, float worldX, float worldZ);

    // Places the bank around a world XZ point when none is placed yet, without
    // observing an emitter (nothing is carved). For scenes with no emitter.
    void FogWakePlaceBankIfAbsent(float worldX, float worldZ);

    // Advances the simulation to the current time. Safe to call once per camera:
    // the runtime steps a fixed cadence off a monotonic clock, so extra calls
    // within one tick do nothing.
    void FogWakeRenderFrameTick();

    // Render spike (fog_wake_render.cpp): a read-only view of the current
    // bank. `bankGeneration` changes each time a bank is placed; `steps`
    // changes each simulation tick. False when no bank is placed.
    struct FogWakeRenderView
    {
        const float* clearance = nullptr; // row-major z * width + x
        std::size_t width = 0;
        std::size_t height = 0;
        double originX = 0;  // sim x of the lower corner
        double originZ = 0;  // sim z of the lower corner
        double cellSize = 0;
        std::uint64_t steps = 0;
        std::uint32_t bankGeneration = 0;
    };
    bool FogWakeGetRenderView(FogWakeRenderView& out);

    namespace Hooks
    {
        // Game thread, from ChunkEffect::Simulate after TickRtsMarkers; never
        // inside render-queue traversal. Builds the layer mesh for a new
        // bank and uploads the clearance grid after each simulation tick.
        void TickFogWakeRender();
        // destroyAllEntities (mission end): destroy the layers while valid.
        void DestroyFogWakeSceneObjects(void* sceneManager, const wchar_t* reason);
        // clearScene / destroyAllMovableObjects: Ogre frees them; forget.
        void ForgetFogWakeSceneResources(const wchar_t* reason);
        // Writes the layer shader and material into the chunk cache root.
        void EnsureFogWakeRenderAssets(
            const std::filesystem::path& cacheRoot,
            const std::vector<std::filesystem::path>& payloadDirectories);
    }
}
