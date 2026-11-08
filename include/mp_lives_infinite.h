// mp_lives_infinite.h
// BZR Open Shim - "Infinite" as the sixth step of the multiplayer Lives button.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// The match-setup Lives button cycles 1..5 and wraps. This module adds a sixth
// step shown as "Infinite"; a match launched with lives = 6 gets 99 lives. Five
// sites in scripts/patches.json, always on and all-or-nothing (the step itself
// is the opt-in, so there is no ini key):
//   Infinite Lives Click Max     cycle maximum 5 -> 6 (BYTES)
//   Infinite Lives Config Clamp  multi.ini load clamp 5 -> 6 (BYTES)
//   Infinite Lives Host Label    host click label text (REL32 over a std::string ctor call)
//   Infinite Lives Lobby Label   lobby refresh label text (REL32 over the same ctor)
//   Infinite Lives Launch Fill   launch block lives 6 -> 99 (JMP5)
// Static analysis only; not live-tested.

#pragma once
#include <vector>

#include "hook_engine.h"

namespace BZROpenShim
{
    namespace MpLivesInfinite
    {
        constexpr int kSiteCount = 5;

        bool IsPatchName(const char* name);

        // Verifies the group and writes the REL32/JMP5 payloads, or marks every
        // site unverified so none is applied. Returns nullptr when armed, else a
        // short reason.
        const char* Arm(std::vector<HookEngine::PatchDef>& patches, bool isSteam);
    }
}
