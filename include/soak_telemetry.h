#pragma once
// soak_telemetry.h
// BZR Open Shim - opt-in soak telemetry (src/patches/soak_telemetry.cpp).
//
//   [Diagnostics]
//   SoakTelemetry = 0       ; OPENSHIM_SOAK_TELEMETRY=1 wins when set
//   SoakGpuStallMs = 1000   ; OPENSHIM_SOAK_GPU_STALL_MS wins when set
//
// When on: a D3D11.4 fence signalled at render-queue-group ends, frame start
// and before Present, watched from a worker thread ([GPUWATCH] stall /
// resumed); a [SOAK] heartbeat and main-loop stall detector on the same
// thread; and a once-per-frame [LIGHTING] sudden-change monitor with
// rate-limited frame captures. Off installs nothing. Line formats are
// documented in AGENT_TOOLING.md ("Soak telemetry"); the CR soak runner
// parses them, so keep them exact.
//
// Test only (environment): OPENSHIM_SOAK_TEST_STALL_MS=<n> makes the
// watchdog treat the fence as stuck for n ms once, about 30 s after the first
// mission frame. It never stalls the real GPU.

namespace BZROpenShim
{
    // Reads the toggle and starts the watchdog thread when it is on.
    void InitializeSoakTelemetry();

    // Main-thread seams (shell screen factory, world render queue update).
    // Installs the Ogre frame listener once Root exists; one branch after.
    void SoakTelemetryRenderTick();

    // Stops the watchdog thread. The fence and its device references are
    // left to the OS, like the render system itself at exit.
    void ShutdownSoakTelemetry();

    namespace SoakTelemetryDetail
    {
        extern bool g_TrackPasses;
        extern const void* g_LastPass;
    }

    // Called by the shaderless-draw guard's renderSingleObject detour for
    // every draw: the last Ogre::Pass submitted names the material of the
    // next fence signal. Render thread only; one branch when telemetry is off.
    inline void SoakTelemetryNotePass(const void* pass) noexcept
    {
        if (SoakTelemetryDetail::g_TrackPasses)
            SoakTelemetryDetail::g_LastPass = pass;
    }
}
