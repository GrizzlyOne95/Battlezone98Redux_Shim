#pragma once
// ui_performance_hooks.h
// BZR Open Shim - UI performance hook glue (Ogre, file scan, workshop).
// Declares helpers that wire existing shim interception points into UiPerf
// without requiring broad engine code changes.
//
// SPDX-License-Identifier: MIT

#include <cstdint>

namespace BZROpenShim::UiPerfHooks
{
    // Install all UiPerf hooks that have a known address.  Safe to call
    // multiple times; subsequent calls are no-ops.  Reads UiPerformanceLogging
    // to decide whether to arm each hook (install remains cheap when disabled).
    void Install();

    // Ogre ResourceGroup wrappers - call from the detoured Ogre functions or
    // from the polling path that already knows group names.  Each records
    // elapsed and emits [UIPERF][OGRE] lines when UiPerf is enabled.
    void OnOgreInitialiseResourceGroup_Begin(const char* group);
    void OnOgreInitialiseResourceGroup_End(const char* group);

    void OnOgreLoadResourceGroup_Begin(const char* group);
    void OnOgreLoadResourceGroup_End(const char* group);

    void OnOgreUnloadResourceGroup_Begin(const char* group);
    void OnOgreUnloadResourceGroup_End(const char* group);

    void OnOgreClearResourceGroup_Begin(const char* group);
    void OnOgreClearResourceGroup_End(const char* group);

    void OnOgreDestroyResourceGroup_Begin(const char* group);
    void OnOgreDestroyResourceGroup_End(const char* group);

    void OnOgreParseScripts_Begin(const char* group);
    void OnOgreParseScripts_End(const char* group, uint32_t scriptsParsed = 0);

    // File/mod discovery helpers.  Wrap FindFirstFile / recursive directory
    // iteration sites and ODF/BZN enumeration.
    void OnModDiscovery_Begin(const char* context);
    void OnModDiscovery_End();

    void OnWorkshopScan_Begin();
    void OnWorkshopScan_End();

    // Shell/menu transition hooks - called from the shell seams in bzr_hooks.
    void OnShellRequest(int screenId);
    void OnShellTransitionUpdate(); // called each time FUN_007c7070 completes

    // Multiplayer teardown hooks.
    void OnMultiplayerShutdown_Begin(const char* phase);
    void OnMultiplayerShutdown_End(const char* phase);
} // namespace BZROpenShim::UiPerfHooks
