// redux_compatibility.h
// Guarded compatibility patches for confirmed Redux 2.2.301 defects.

#pragma once

#include "hook_engine.h"

#include <string>
#include <vector>

namespace BZROpenShim
{
    struct ReduxCompatibilityGate
    {
        bool steam = false;
        bool supportedHash = false;
        bool settledBytes = false;
        uint32_t moduleBase = 0;
        uint32_t imageSize = 0;
        uint64_t fileSize = 0;
        std::string sha256;
    };

    bool IsReduxCompatibilityPatchName(const char* name);
    ReduxCompatibilityGate PrepareReduxCompatibilityGate(bool steam);

    // Applies the locale call site independently and the two TRN producer
    // sites as one guarded group. Returns the number of written patch sites.
    int ApplyReduxCompatibilityPatches(
        std::vector<HookEngine::PatchDef>& patches,
        const ReduxCompatibilityGate& gate);
}
