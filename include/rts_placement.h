// rts_placement.h
// BZR Open Shim - RTS placement aids (rts_placement.cpp), local visuals only:
//  * [Gameplay] RtsBuildGhost: a see-through copy of the picked building where
//    the stock placement quad shows, tinted like it; plus neutral ghosts at
//    every listed nav while the Go To Nav submenu offers Build at Nav.
//  * [Gameplay] RtsPowerRange: while a ghost of a COMM/TURR/SHLD class shows,
//    the power radius of every allied power plant (drawn by rts_markers.cpp).
//  * [Gameplay] RtsWaypointLines: the destination reader for the waypoint
//    lines rts_markers.cpp draws.
// Nothing is sent, saved or written to the engine. See Docs/RTS_MARKERS.md.
#pragma once

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
    namespace Hooks
    {
        // Patch thread, from InstallAiTuningHooksIfPossible (ai_odf_tuning.cpp),
        // retried: binds the rows and patches ConstructionRig vtable slot 12
        // (GetCommand) with a pass-through post-hook. Fails closed.
        void InstallRtsPlacementIfPossible();
        void ReloadRtsPlacementConfig();

        // While true, the GetCommand post-hook records nothing: Build at Nav
        // validates a nav with its own GetCommand call (game thread).
        void SuppressRtsGhostRecord(bool suppress);

        // Game thread, from the RTS marker tick (rts_markers.cpp), outside
        // render-queue traversal, with the live SceneManager and the render
        // origin (sim -> render). Places, retints and hides the ghosts and
        // gathers the power rings for RtsPowerRingsThisTick.
        void TickRtsPlacement(void* sceneManager, const float renderOrigin[3]);
        // Hides every ghost and drops the power rings (HUD hidden, no scene).
        void HideRtsPlacement();
        // Scene teardown: drop the Ogre pointers without an Ogre call.
        void ForgetRtsPlacementSceneResources(const wchar_t* reason);
        // SceneManager::destroyAllEntities, before the original runs
        // (lifecycle_seams.cpp): destroys the ghost entities of that scene
        // manager and forgets them; the nodes survive. Also forgets the
        // classes whose mesh failed.
        void DestroyRtsPlacementSceneObjects(void* sceneManager, const wchar_t* reason);
        // Leaving the simulation: hide and forget the last preview.
        void DeactivateRtsPlacement(const wchar_t* reason);
        // Any of the three options on (the marker tick runs for them too).
        bool RtsPlacementAnyEnabled();
        bool RtsWaypointLinesEnabled();

        struct RtsPowerRing
        {
            float centre[3];
            float radius;
        };
        // The rings gathered by the last TickRtsPlacement (0 when no ghost
        // of a powered class shows, or RtsPowerRange is off).
        size_t RtsPowerRingsThisTick(RtsPowerRing* out, size_t capacity);

        // Destination (sim x, z) of the object's current (pending = false,
        // GameObject +0xA8) or pending (+0xC8) command record: the last point
        // of its AiPath. False when idle, pathless, unreadable or when the
        // rows did not bind. Game thread.
        bool ReadRtsCommandDestination(void* gameObject, bool pending, int& what, float& x, float& z);
    }
}
