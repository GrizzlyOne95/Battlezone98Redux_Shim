// precise_timestep.h
// BZR Open Shim - QPC-precise simulation step (experimental, single player)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace BZROpenShim
{
    // Redux's SetLoopTimes (GOG 0x00822AE0) measures each frame in whole
    // milliseconds of system time and hands the sim `dt * 0.001` unsmoothed,
    // so at 144 fps the step alternates 6 and 7 ms. When
    // [Experimental] PreciseTimestep = 1 (or OPENSHIM_PRECISE_TIMESTEP=1) the
    // per-frame call to it is redirected through a wrapper that replaces only
    // the float step with the QPC-measured frame interval. The integer
    // millisecond clocks are left untouched, so game time, timers and
    // networking are unchanged. Network games, pauses, the 200 ms clamp and
    // any interval that disagrees with the engine's own by more than a
    // tolerance all keep the engine value.
    void InitializePreciseTimestep();

    // The step the engine will use for the current frame, for telemetry.
    // False when the globals could not be resolved on this build.
    struct TimestepSample
    {
        uint32_t rawMs;        // integer ms before the 200 ms clamp
        float stepSeconds;     // the float step the sim reads
        bool precise;          // this frame's step was written by the wrapper
    };
    bool ReadTimestepSample(TimestepSample& out);
}
