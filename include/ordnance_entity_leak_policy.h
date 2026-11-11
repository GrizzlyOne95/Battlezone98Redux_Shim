// ordnance_entity_leak_policy.h
//
// SPDX-License-Identifier: MIT
//
// Pure decision for [Fixes] OrdnanceEntityLeak (ordnance_entity_leak.cpp).
//
// Stock ordnance teardown (GOG 0x00680620) calls node->detachAllObjects() on
// the Ordnance's SceneNode (+0xD0) and then destroys the node through the
// helper at 0x0067E550, which only destroys objects still attached to it. The
// Ogre Entity at +0xCC was detached one step earlier, so it is never
// destroyed: every round fired leaks one Entity in the SceneManager. The fix
// destroys that Entity after the stock teardown, only when it is provably the
// same object, still registered in the live scene and no longer attached, so
// a path that already destroyed or re-used it is never touched twice.
//
// Stock SceneManager::destroyAllEntities (mission end, save load, replay)
// frees every Entity while ordnance keeps pointing at them, so a pointer is
// only trusted while it is in the live set the creation hook fills and that
// teardown clears. An untracked pointer is never dereferenced.
//
// Host-tested in tests/ordnance_entity_leak_policy_tests.cpp.
#pragma once

namespace BZROpenShim
{
    namespace OrdnanceEntityLeak
    {
        // Snapshot taken around the stock teardown call.
        struct TeardownObservation
        {
            const void* entityBefore = nullptr; // Ordnance +0xCC before the call
            // entityBefore is in the live set: created by the hooked creator
            // and not freed by destroyAllEntities since. Checked before any
            // Ogre call touches the pointer.
            bool tracked = false;
            const void* entityAfter = nullptr;  // Ordnance +0xCC after the call
            bool hasRuntimeScene = false;       // the live SceneManager is known
            bool queryOk = false;               // the Ogre queries ran without faulting
            // getEntity(entity->getName()) == entity in the live SceneManager.
            // A destroyed Entity has left that map, so this is the liveness proof.
            bool registeredInRuntimeScene = false;
            bool stillAttached = false;         // MovableObject::isAttached()
        };

        enum class Decision
        {
            NothingToDo,     // no Entity was recorded
            SkipUntracked,   // not in the live set: maybe freed, never dereferenced
            Destroy,         // stock orphaned it: destroy, then clear the fields
            SkipChanged,     // the slot no longer holds the same pointer
            SkipNoScene,     // no live SceneManager to check against
            SkipQueryFailed, // an Ogre query faulted or threw
            SkipNotRegistered, // already destroyed, or made in another scene
            SkipAttached,    // something still owns it
        };

        inline Decision Decide(const TeardownObservation& o)
        {
            if (!o.entityBefore)
                return Decision::NothingToDo;
            if (!o.tracked)
                return Decision::SkipUntracked;
            if (o.entityAfter != o.entityBefore)
                return Decision::SkipChanged;
            if (!o.hasRuntimeScene)
                return Decision::SkipNoScene;
            if (!o.queryOk)
                return Decision::SkipQueryFailed;
            if (!o.registeredInRuntimeScene)
                return Decision::SkipNotRegistered;
            if (o.stillAttached)
                return Decision::SkipAttached;
            return Decision::Destroy;
        }
    }
}
