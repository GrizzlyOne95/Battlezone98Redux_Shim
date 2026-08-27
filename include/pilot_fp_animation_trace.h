#pragma once

namespace BZROpenShim
{
    // Returns true when the first-person pilot Ogre animation trace is enabled.
    // The trace defaults on through [Diagnostics] TracePilotFPAnimations and can
    // be disabled with either the INI key or OPENSHIM_TRACE_PILOT_FP_ANIMATIONS=0.
    bool IsPilotFpAnimationTraceRequested();

    // Starts the local-Person animation observer. The worker waits for
    // OgreMain.dll, resolves the retail Ogre exports by semantic name, and binds
    // AnimationState traffic only when the calling Ogre Entity is the current
    // local userObject's Person render entity.
    //
    // v1 was strictly read-only. v2 retains read-only-by-default semantics but
    // adds gated diagnostic extensions for controlled investigation:
    //   - caller RVA capture via _ReturnAddress() for controller attribution
    //   - transition-filtered logging (enabled/loop/weight change) + dt throttling
    //   - periodic inventory poll (bound states + hasAnimSet existence)
    //   - dormant manipulation gate (freeze/forceWeight) behind
    //     [Diagnostics] PilotFPAnimManip / OPENSHIM_PILOT_FP_MANIP
    // The manipulation gate is fail-closed and dormant unless explicitly enabled
    // for isolated lcbench testing; it never alters stock behavior otherwise.
    void InitializePilotFpAnimationTrace();

    // Stops trace collection. Installed process-lifetime observers become
    // pass-through hooks after shutdown, matching the existing Ogre profiler.
    void ShutdownPilotFpAnimationTrace();
}
