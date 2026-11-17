// rts_markers.h
// BZR Open Shim - RTS markers (rts_markers.cpp): terrain-conforming ground
// rings for the local player's orders ([Gameplay] RtsCommandPings) and for
// artillery range ([Gameplay] RtsArtilleryRange). Local visuals only: nothing
// is sent, saved or written to the engine. See Docs/RTS_MARKERS.md.
#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

namespace BZROpenShim
{
    namespace Hooks
    {
        // Patcher seam for "RTS Markers Object Command Hook", the entry detour
        // of ControlPanel::BroadcastCommand(what, GameObject* target)
        // 0x004A7050. Prepare checks the prologue and builds the trampoline
        // (null: do not write the hook); Note records that the JMP5 landed.
        bool IsRtsMarkersObjectCommandHook(const char* patchName);
        void* PrepareRtsMarkersObjectCommandHook(uint32_t site);
        void NoteRtsMarkersObjectCommandHookInstalled();

        // An order on an object that did not go through BroadcastCommand:
        // rts_commands.cpp's per-unit unit-menu dispatch (ExecuteMode) and
        // its smart Defend-target pick. Game thread, while the local
        // ControlPanel still has the selection; one call per order. Queues
        // the same ping the broadcast detour would (RtsCommandPings; local
        // panel with units selected), or nothing.
        void NotifyRtsMarkersCommand(int what, void* target);

        // Game thread, from ChunkEffect::Simulate (bzr_hooks.cpp) after the
        // rally beacons, on the engine's dt. Places, rebuilds and hides the
        // ring pool. Never runs inside render-queue traversal.
        void TickRtsMarkers(float dt);
        void ReloadRtsMarkersConfig();
        // Scene teardown (clearScene / destroyAllMovableObjects): Ogre frees
        // the ManualObjects and nodes; drop the pointers without an Ogre call.
        void ForgetRtsMarkersSceneResources(const wchar_t* reason);
        // Leaving the simulation: hide every ring and drop pending pings.
        void DeactivateRtsMarkers(const wchar_t* reason);
        // Writes the generated ring material and shader into the chunk cache
        // root. Must run before the payload group initialises.
        void EnsureRtsMarkerAssets(
            const std::filesystem::path& cacheRoot,
            const std::vector<std::filesystem::path>& payloadDirectories);
    }
}
