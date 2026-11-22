#pragma once
// Installer for the render-sync vtable guard. See render_sync_guard_policy.h.

namespace BZROpenShim
{
    namespace RenderSyncGuard
    {
        // Redirects the rel32 call at 0x004DB498 (GameObject::UpdatePosition
        // -> render-node sync FUN_00680BD0) to a guard that skips the sync
        // when the object's Ogre Entity or SceneNode is already destroyed.
        // Fail-closed: any byte-guard mismatch or unresolved Ogre vtable
        // leaves the call untouched. Safe to call repeatedly.
        void InstallRenderSyncGuardIfPossible();
    }
}
