#pragma once
#include <cstdint>

namespace BZROpenShim {
namespace Hooks {
// [Network] LobbyDropKeepsMatch: the two REL32 call sites named
// "Lobby Drop Keeps Match ..." in scripts/patches.json.
bool IsLobbyDropKeepsMatchPatchName(const char* name);
// Checks that the stock call at `site` targets the expected engine routine and
// returns the hook to redirect it to, or 0 to leave the stock call in place.
uint32_t PrepareLobbyDropKeepsMatchHook(const char* name, uint32_t site, void* original);
}
}
