// thread_scheduling.h
// BZR Open Shim - main-thread MMCSS registration and power-throttling opt-out
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // Unless [Fixes] ThreadScheduling = 0 (or OPENSHIM_DISABLE_THREAD_SCHEDULING=1):
    //  - the process opts out of Windows power throttling (EcoQoS execution
    //    speed and timer-resolution throttling), and
    //  - the thread that runs the frame loop registers with MMCSS under the
    //    "Games" task the first time it calls Ogre::Root::renderOneFrame.
    // Both APIs are resolved at runtime (avrt.dll is loaded from System32 on
    // demand, SetProcessInformation through GetProcAddress), so Windows builds
    // or Wine/Proton prefixes that lack them log the failure and carry on.
    // Neither touches the simulation, so there is no multiplayer gate.
    void InitializeThreadScheduling();
    void ShutdownThreadScheduling();
}
