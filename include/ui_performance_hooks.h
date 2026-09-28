#pragma once
// ui_performance_hooks.h
// BZR Open Shim - UI performance hook glue (Ogre, file scan, workshop).
// Declares helpers that wire existing shim interception points into UiPerf
// without requiring broad engine code changes.
//
// SPDX-License-Identifier: MIT

namespace BZROpenShim::UiPerfHooks
{
    // Install all UiPerf hooks that have a known address.  Safe to call
    // multiple times; subsequent calls are no-ops.  Reads UiPerformanceLogging
    // to decide whether to arm each hook (install remains cheap when disabled).
    void Install();

    // Joins the idle trigger helper and restores the window procedure and
    // PeekMessage import seam installed by Install().
    void Shutdown() noexcept;

    // Ogre ResourceGroup wrappers, called from the clearResourceGroup and
    // initialiseResourceGroup IAT detours Install() places.  Each records
    // elapsed and emits [UIPERF][OGRE] lines when UiPerf is enabled.
    void OnOgreInitialiseResourceGroup_Begin(const char* group);
    void OnOgreInitialiseResourceGroup_End(const char* group);

    void OnOgreClearResourceGroup_Begin(const char* group);
    void OnOgreClearResourceGroup_End(const char* group);
} // namespace BZROpenShim::UiPerfHooks
