#pragma once
// Public Steam listing of OpenShim servers reachable through a Steam tunnel
// bridge. A host that opts in owns a public Steam lobby (appid 301650) whose
// data names its bridge SteamID; other OpenShim players find it with a lobby
// search and join by switching their tunnel to that bridge. Nobody joins the
// Steam lobby itself: it is only an advert. The server's own password and
// bans stay the only gate. Steam build only; kill switch
// OPENSHIM_DISABLE_STEAM_PUBLIC_LISTING.
#include <cstdint>
#include <string>
#include <vector>

namespace BZROpenShim
{
    namespace SteamPublicListing
    {
        struct Game
        {
            uint64_t bridge = 0;
            std::string name;
        };

        // steam_api.dll is loaded and the kill switch is not set.
        bool Available();
        // Game thread. This game's own SteamID64, 0 until Steam is up.
        uint64_t LocalSteamId();

        // Host opt-in, persisted as openshim.ini [Network] SteamPublicListing.
        bool HostListingOn();
        void SetHostListing(bool on);
        // One line for the LAN screen, e.g. "Listed on Steam".
        std::string HostListingText();

        // Joiner: start a worldwide search (replaces the previous results).
        void StartBrowse();
        const std::vector<Game>& Games();
        std::string BrowseText();

        // Game thread, every frame: host advert and search polling.
        void Tick();
    }
}
