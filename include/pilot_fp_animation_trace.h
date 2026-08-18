#pragma once

namespace BZROpenShim
{
    // Returns true when the first-person pilot Ogre animation trace is enabled.
    // The trace defaults on through [Diagnostics] TracePilotFPAnimations and can
    // be disabled with either the INI key or OPENSHIM_TRACE_PILOT_FP_ANIMATIONS=0.
    bool IsPilotFpAnimationTraceRequested();

    // Starts the read-only aspilo_fp animation observer. The worker waits for
    // OgreMain.dll, resolves the retail Ogre exports by semantic name, and
    // installs only exact call/IAT observers. It never changes animation state.
    void InitializePilotFpAnimationTrace();

    // Stops trace collection. Installed process-lifetime observers become
    // pass-through hooks after shutdown, matching the existing Ogre profiler.
    void ShutdownPilotFpAnimationTrace();
}
