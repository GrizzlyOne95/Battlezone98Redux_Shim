#pragma once
#include <cstdint>

namespace BZROpenShim {
namespace Hooks {
// [Network] AllyLockSurvivesStart: the REL32 call site named
// "Ally Lock Survives UI Rebuild" in scripts/patches.json.
bool IsAllyLockKeepPatchName(const char* name);
// Checks that the stock call at `site` targets AllyEditor::Init and returns the
// wrapper to redirect it to, or 0 to leave the stock call in place.
uint32_t PrepareAllyLockKeepHook(const char* name, uint32_t site, void* original);
}
}
