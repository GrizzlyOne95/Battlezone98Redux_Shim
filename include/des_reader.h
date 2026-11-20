#pragma once
// Shared reader for mission briefing pages (<stem>.des, <stem>_N.des) and
// their page images, used by the lobby Briefing overlay (lobby_briefing.cpp)
// and the Database screen's Briefings tab (database_screen.cpp). The page
// rules themselves are LobbyBriefingPolicy / BriefingPagesPolicy.
//
// Internal API. Not part of the plugin SDK.

#include <cstddef>
#include <string>

namespace BZROpenShim::DesReader
{
    // Binds DescriptionFileLoad and Music::ResourceSize (the text half) and
    // the Ogre resource lookup (images). Idempotent. False when the text half
    // is unavailable; images are optional (ImagesAvailable).
    bool Bind();
    bool ImagesAvailable();

    // True when the game's file system holds `name` (a .des page). Names
    // longer than BriefingPagesPolicy::kMaxNameLength are never found.
    bool ResourceExists(const std::string& name);
    // The size of `name` in bytes as the game's file system reports it; 0
    // when absent (same name rule as ResourceExists).
    size_t ResourceSize(const std::string& name);
    // True when an Ogre resource group holds `name` (a page image).
    bool ImageExists(const std::string& name);
    // The page text, as the stock loader reads it, clipped to what the
    // scrolling text block holds (LobbyBriefingPolicy::ClipPageText).
    std::string LoadPage(const std::string& file);
}
