// scene_mutation_drain.h
//
// Runtime side of include/scene_mutation_drain_policy.h (see there for why).
// src/patches/scene_mutation_drain.cpp owns the Ogre FrameListener; the work
// it drains lives with the features that own it.
#pragma once

namespace BZROpenShim::Hooks
{
    // Call once at the top of the world render-queue hook. Installs the
    // frameStarted listener on first use. True: the caller must not create or
    // destroy scene objects now, a drain will. False only while the listener
    // is not (or cannot be) installed: mutate inline, the pre-drain behaviour.
    bool BeginRenderQueueSceneAccess() noexcept;
    // Held for the whole of LegacyWorldUpdateRenderQueueHook and of the engine
    // flame submit (both render-queue callbacks), so code that runs inside
    // them with no parameter for it (TickLaserSight, the chunk mesh proxies,
    // weapon ctor/dtor/SetWeapon hooks) can tell.
    class RenderQueueHookScope
    {
    public:
        RenderQueueHookScope() noexcept;
        ~RenderQueueHookScope();
        RenderQueueHookScope(const RenderQueueHookScope&) = delete;
        RenderQueueHookScope& operator=(const RenderQueueHookScope&) = delete;
    };
    // Inside such a callback and the drain is installed: create/destroy must
    // wait for a drain and is only requested.
    bool InsideRenderQueueHookWithDeferral() noexcept;

    // A request made from inside such a callback: the next drain must run even
    // if the world render-queue hook did not (the flame-driven chunk proxies).
    void NoteSceneMutationRequested() noexcept;

    // Simulation tick (ChunkEffectSimulateHook): runs the deferred work only
    // while frameStarted is stalled, so features keep working without ever
    // mutating inside the traversal.
    void RunSceneMutationFallbackDrain() noexcept;

    // Scene teardown seam (lifecycle_seams.cpp): drop work due for the dying scene.
    void SceneMutationDrainSceneTeardown() noexcept;

    // The drained work, run from frameStarted (or the sim-tick fallback)
    // outside any scene traversal and only after a world render-queue call. Defined in
    // bzr_hooks.cpp beside the hook so the two lists stay side by side.
    void RunDeferredSceneMutations() noexcept;

    // laser_sight.cpp: builds the beam/arc objects the last render-queue tick
    // asked for. A no-op when nothing was asked for.
    void PrepareLaserSightSceneObjects();
    // chunk_proxy_render.cpp: creates the mesh proxy objects that render-time
    // ticks asked for. A no-op when nothing was asked for.
    void CreateRequestedChunkMeshProxyObjects();
}
