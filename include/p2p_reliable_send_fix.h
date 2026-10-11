#pragma once
#include "hook_engine.h"
#include <vector>

namespace BZROpenShim {
namespace Hooks {
// Fill only uniquely verified registry sites; the normal patch engine owns
// byte guards, thread suspension and memory writes.
void ConfigureP2PReliablePatches(std::vector<HookEngine::PatchDef>& patches);
}
}
