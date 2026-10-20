// deferred_modable_rebuild.h
// BZR Open Shim - menu transitions without a Modable rebuild.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Every shell screen that changes the content mount (main menu, Instant
// Action, Multiplayer, Custom Campaigns) clears and re-initialises the Ogre
// "Modable" resource group, recompiling ~250-1100 material scripts: 0.6-5 s
// per screen change, only to show lists, text and preview images. This module
// keeps the mounts but defers that rebuild while Ogre holds the base (main
// menu) set, and catches up where content is really needed:
//   - the mission mount (0x007647C0 -> 0x0076E6C0), which every mission,
//     instant action, multiplayer and load-game start passes through;
//   - the multiplayer game room (screen 0xF), whose vehicle preview draws
//     mod craft.
// Any transition the module cannot prove safe keeps the stock rebuild: coming
// back from mission content (mount mode 0), an unreadable mode, or a group
// that already holds something other than the base set.
//
// Ten sites in scripts/patches.json, all-or-nothing:
//   Deferred Modable Rebuild {Main,IA,MP,List} Store   mov [ecx+8Ch],N (JMP5)
//   Deferred Modable Rebuild {Main,IA,MP,List} Gate    clear+initialise block (JMP5)
//   Deferred Modable Rebuild Mission Mount Call         call 0x0076E6C0 (REL32)
//   Deferred Modable Rebuild MP Room Mount Call         call 0x0076A240 (REL32)
// Disabled by [General] FastMenuTransitions = 0
// (OPENSHIM_DISABLE_FAST_MENU_TRANSITIONS).

#pragma once
#include <cstddef>
#include <cstdint>
#include <string>

namespace BZROpenShim
{
    namespace DeferredModableRebuild
    {
        constexpr int kSiteCount = 10;

        bool IsPatchName(const char* name);

        // Validates one site and returns the address its payload targets:
        // for JMP5 sites the detour (stolenLen = bytes it replaces), for REL32
        // sites the replacement callee (stolenLen = 4). nullptr stands it down.
        void* PrepareSite(const std::string& name, uint32_t address, size_t& stolenLen);

        // Cross-site checks once every site is prepared (each gate belongs to
        // its store's setter, the MP room call reaches the MP setter, the
        // rebuild helpers resolve). False stands the whole module down.
        bool FinalizeSites();
    }
}
