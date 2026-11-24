#pragma once

namespace BZROpenShim
{
    // Engine-facing glue for the interactive fog wake simulation.
    //
    // Off unless [Experimental] InteractiveFogWakes = 1 (or the
    // OPENSHIM_INTERACTIVE_FOG_WAKES environment name). Rendering is an
    // in-shader ground-fog spike on DX11 Enhanced (fog_wake_shader.cpp). With the feature
    // disabled every entry point below is a single atomic read.
    //
    // See Docs/INTERACTIVE_FOG_WAKES.md.

    // The multiplayer gate: the option only takes effect in a single player
    // session, because the trail would reveal where enemy craft went.
    inline bool FogWakeGateAllows(bool configured, bool singlePlayer)
    {
        return configured && singlePlayer;
    }

    bool FogWakeFeatureEnabled();

    // Mission run-state transitions. Emitter identity is a raw engine pointer,
    // so a session boundary must discard tracking as well as the field.
    void FogWakeNotifyMissionRunStateChanged(bool running);

    // Reports where an emitter is now, in world XZ. Never simulates: safe from a
    // hook that runs more than once per simulation step.
    void FogWakeObserveEmitter(const void* emitter, float worldX, float worldZ);

    // Advances the simulation to the current time. Safe to call once per camera:
    // the runtime steps a fixed cadence off a monotonic clock, so extra calls
    // within one tick do nothing.
    void FogWakeRenderFrameTick();

    // Render-side view of the clearance bank, for the in-shader ground fog
    // (src/patches/fog_wake_shader.cpp). Valid only while a bank is placed.
    // Coordinates are sim world XZ; clearance is row-major z * width + x.
    struct FogWakeRenderView
    {
        const float* clearance = nullptr;
        unsigned width = 0;
        unsigned height = 0;
        double originX = 0;
        double originZ = 0;
        double cellSize = 0;
        unsigned long long steps = 0;
        unsigned bankGeneration = 0;
    };
    bool FogWakeGetRenderView(FogWakeRenderView& out);

    // Places the bank around a sim XZ point when none is placed yet (a scene
    // without thrusting craft still gets fog around the player). Never stamps.
    // Returns true when a bank is placed after the call.
    bool FogWakePlaceBankIfAbsent(float worldX, float worldZ);

    // In-shader ground fog (DX11 Enhanced only). Called from
    // FogWakeRenderFrameTick on the render thread; binds or unbinds the
    // per-frame shader resources. Implemented in fog_wake_shader.cpp.
    void FogWakeShaderFrameTick(bool active);
}
