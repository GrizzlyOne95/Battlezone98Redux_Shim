// scene_mutation_drain_policy.h
//
// Pure gate for moving Ogre scene mutation out of the render-queue traversal.
//
// Why: LegacyWorldUpdateRenderQueueHook (src/patches/bzr_hooks.cpp) is the
// game world's MovableObject::_updateRenderQueue. Ogre calls it from inside
// SceneManager::_findVisibleObjects, after other renderables are already in
// the render queue and the frame's light list is already built. Creating or
// destroying an Entity, SceneNode or Light there (or attaching/detaching one)
// leaves Ogre holding freed renderables: crash dump 20980 shows the queue's
// depth sort calling getSquaredViewDepth through the freed SubEntity vtables
// of an EXU mesh muzzle flash cancelled from this hook. In a release build the
// same stale renderables can bind freed buffers and remove the D3D11 device.
//
// Design (smallest that removes the hazard): the hook keeps its per-camera
// work (poses, visibility, transforms) and only *notes* that a create or
// destroy is due. An Ogre FrameListener's frameStarted, which Root fires from
// renderOneFrame before any scene traversal, performs those mutations once per
// frame. No separate command queue is kept: each feature's own state is the
// queue (a weapon whose flash is not yet created, a beam not yet built), so
// mission teardown, which already resets that state through the lifecycle
// seams, cannot leave a queued destroy pointing at a freed object. A destroy
// is therefore at most one frame late, which only lets an already-queued
// flash render once more.
//
// Fail closed: only until the listener is installed, or if it cannot be
// installed, does the hook mutate inline exactly as it did before this gate
// existed. Once installed the hook always defers, even if frameStarted stops
// firing (a render path that bypasses Root::renderOneFrame): inline mutation
// is the crash path, so a stall never re-enables it. Instead the stall is
// logged once per episode and the simulation tick (ChunkEffect::Simulate,
// also outside any traversal) runs the deferred work as a fallback drain
// until frameStarted resumes.
//
// No Win32, no Ogre. Host-tested in tests/scene_mutation_drain_policy_tests.cpp.
#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

namespace BZROpenShim::SceneMutationDrain
{
    // Render-queue calls with no frameStarted in between before the drain is
    // treated as stalled. The hook runs once per camera/viewport, a handful of
    // times per frame, so this is many frames of a silent listener.
    constexpr uint32_t kStallRenderQueueCalls = 240;

    struct RenderQueueDecision
    {
        // True: leave every create/destroy for a drain (frameStarted, or the
        // sim-tick fallback while frameStarted is stalled).
        bool defer = false;
        // True once per stall episode, on the call that first finds it.
        bool reportStall = false;
    };

    // One scene object a render-time caller may have to defer. Allow() is the
    // create-or-request decision; Take() is the drain's side. Value-reset with
    // its owner's state, so scene teardown drops the request with the handles.
    struct DeferredCreate
    {
        bool requested = false;

        // True: create now. False inside a deferring render callback, which
        // records the request instead.
        bool Allow(bool insideDeferringCallback)
        {
            if (!insideDeferringCallback)
                return true;
            requested = true;
            return false;
        }

        bool Take()
        {
            const bool was = requested;
            requested = false;
            return was;
        }
    };

    // Slot indices whose objects a render-time caller asked for, each with the
    // occupant it was asked for, so a slot released and reused before the
    // drain is not built for its new occupant by mistake. Bounded by the pool.
    template <typename Identity>
    class SlotRequests
    {
    public:
        // False when the index is outside the pool (nothing is recorded).
        bool Request(size_t index, Identity identity, size_t poolSize)
        {
            if (index >= poolSize)
                return false;
            for (const auto& entry : entries_)
                if (entry.first == index && entry.second == identity)
                    return true;
            if (entries_.size() >= poolSize)
                return false;
            entries_.emplace_back(index, identity);
            return true;
        }

        // Calls build(index) for every request whose slot still holds the
        // occupant it was made for (current(index) == identity), then empties.
        template <typename Current, typename Build>
        void Drain(size_t poolSize, Current current, Build build)
        {
            std::vector<std::pair<size_t, Identity>> pending;
            pending.swap(entries_);
            for (const auto& entry : pending)
                if (entry.first < poolSize && current(entry.first) == entry.second)
                    build(entry.first);
        }

        void Clear() { entries_.clear(); }
        bool Empty() const { return entries_.empty(); }
        size_t Size() const { return entries_.size(); }

    private:
        std::vector<std::pair<size_t, Identity>> entries_;
    };

    class Gate
    {
    public:
        enum class Install : uint8_t { Pending, Installed, Unavailable };

        Install InstallState() const { return install_; }
        void NoteInstalled() { install_ = Install::Installed; }
        void NoteUnavailable() { install_ = Install::Unavailable; }
        // True once the listener is installed: from then on nothing may be
        // created or destroyed inside the traversal.
        bool Deferring() const { return install_ == Install::Installed; }

        // Once per render-queue hook entry.
        RenderQueueDecision OnRenderQueue()
        {
            RenderQueueDecision decision;
            if (!Deferring())
                return decision;
            decision.defer = true;
            workDue_ = true;
            if (callsSinceFrameStarted_ <= kStallRenderQueueCalls)
                ++callsSinceFrameStarted_; // saturates one past the threshold
            if (Stalled() && !stallReported_)
            {
                stallReported_ = true;
                decision.reportStall = true;
            }
            return decision;
        }

        // A deferred request from a render callback other than the world hook
        // (the engine flame submit): makes the next drain run without counting
        // toward the stall threshold.
        void OnRequest()
        {
            if (Deferring())
                workDue_ = true;
        }

        // Once per frameStarted. True when a world was rendered since the last
        // drain, so its deferred work is due; a shell or loading frame with no
        // world queue runs nothing. Ends any stall episode.
        bool OnFrameStarted()
        {
            callsSinceFrameStarted_ = 0;
            stallReported_ = false;
            return TakeWork();
        }

        // Once per simulation tick. True only while frameStarted is stalled
        // and work is due: the fallback drain.
        bool OnSimTick()
        {
            return Deferring() && Stalled() && TakeWork();
        }

        // Scene teardown (clearScene, destroyAllMovableObjects,
        // destroyAllEntities): whatever the last world frame left due belongs
        // to a scene that is going away.
        void OnSceneTeardown() { workDue_ = false; }

        bool Stalled() const { return callsSinceFrameStarted_ > kStallRenderQueueCalls; }
        bool StallReported() const { return stallReported_; }

    private:
        bool TakeWork()
        {
            const bool due = workDue_;
            workDue_ = false;
            return due;
        }

        Install install_ = Install::Pending;
        uint32_t callsSinceFrameStarted_ = 0;
        bool workDue_ = false;
        bool stallReported_ = false;
    };
}
