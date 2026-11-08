#pragma once

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
    }
}
