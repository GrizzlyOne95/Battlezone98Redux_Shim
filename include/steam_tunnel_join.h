#pragma once
#include <cstdint>
#include <string>

namespace BZROpenShim
{
    namespace SteamTunnelJoin
    {
        // Friend side: detours the rich-presence join handler. Host side is
        // enabled here too and runs from Tick(). Kill switch:
        // OPENSHIM_DISABLE_STEAM_TUNNEL_JOIN.
        void InstallSteamTunnelJoinIfPossible();
        // Game thread, every frame (shell and mission); throttled to 2 s.
        void Tick();
        // SteamID announced by a bridge running on this PC, or 0.
        uint64_t AnnouncedBridge();
        // Menus, game thread: point the tunnel at a bridge SteamID and
        // reconnect BZRNet. false with a short reason in note when refused.
        bool JoinBridge(uint64_t bridge, std::string& note);
        // Game thread. Points the tunnel back where it was at startup, if a
        // join of ours moved it. False (with note) if it cannot be moved now.
        bool RestoreStartup(std::string& note);
    }
}
