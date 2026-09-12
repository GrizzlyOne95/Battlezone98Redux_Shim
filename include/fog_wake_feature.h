#pragma once

namespace BZROpenShim
{
    // Engine-facing glue for the interactive fog wake simulation.
    //
    // Off unless [Experimental] InteractiveFogWakes = 1 (or the
    // OPENSHIM_INTERACTIVE_FOG_WAKES environment name). Nothing renders yet:
    // this milestone only maintains the clearance field so its behaviour can be
    // observed and qualified before any GPU work is attempted. With the feature
    // disabled every entry point below is a single atomic read.
    //
    // See Docs/INTERACTIVE_FOG_WAKES.md.

    bool FogWakeFeatureEnabled();

    // Mission run-state transitions. Emitter identity is a raw engine pointer,
    // so a session boundary must discard tracking as well as the field.
    void FogWakeNotifyMissionRunStateChanged(bool running, void* sceneManager);

    // Reports where an emitter is now, in world XZ. Never simulates: safe from a
    // hook that runs more than once per simulation step.
    void FogWakeObserveEmitter(const void* emitter, float worldX, float worldZ);

    // Advances the simulation to the current time. Safe to call once per camera:
    // the runtime steps a fixed cadence off a monotonic clock, so extra calls
    // within one tick do nothing.
    void FogWakeRenderFrameTick(void* sceneManager);
}
