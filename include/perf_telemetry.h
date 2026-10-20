// perf_telemetry.h
// BZR Open Shim - frame-hitch and address-space telemetry (diagnostic only)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // True when OPENSHIM_PERF_TELEMETRY asks for it, or when the native CPU
    // sampler is on (a sampled capture is only attributable to hitches when
    // the frame boundaries are recorded next to it).
    bool IsPerfTelemetryRequested();

    // Redirects the executable's import of Ogre::Root::renderOneFrame to time
    // every frame, and starts the address-space reporter thread. Dormant
    // unless requested. Writes logs\openshim_frames_<label>_<pid>.bin and
    // logs\openshim_va_<label>_<pid>.csv, and summary lines to openshim.log.
    void InitializePerfTelemetry();

    // Called from the SetRunning mission seam on every run-state change.
    // Cheap and safe when telemetry is off.
    void PerfTelemetryMissionRunStateChanged(int previous, int current);

    // Stops the reporter thread and flushes the frame file.
    void ShutdownPerfTelemetry();
}
