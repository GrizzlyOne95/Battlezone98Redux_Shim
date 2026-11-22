#pragma once
// fp_trap_log.h
// BZR Open Shim - opt-in floating-point trap logger (src/patches/fp_trap_log.cpp).
//
//   [Diagnostics]
//   FpTrapLog = 0   ; OPENSHIM_FP_TRAP_LOG / BZR_FP_TRAP_LOG win when set
//
// When on: once per frame the main thread unmasks SSE invalid-operation and
// divide-by-zero and x87 divide-by-zero (fp_trap_log_policy.h says why x87
// invalid stays masked). The first trap of the frame is recorded by address,
// recovered so the instruction produces its stock NaN/inf, and the thread
// stays masked until the next frame. New sites are logged at the next frame
// as [FPTRAP] lines; a summary table is logged at game exit. Off installs
// nothing.

namespace BZROpenShim
{
    // Reads the switch; when on, self-tests the recovery on the calling
    // thread and installs the vectored handler. Fails closed.
    void InitializeFpTrapLog();

    // Main thread, once per frame (Ogre frameStarted in
    // scene_mutation_drain.cpp). The first call names the main thread.
    void FpTrapLogFrameTick();

    // Game exit (Ogre Root destructor seam, main thread) and plugin shutdown:
    // stop unmasking and log the summary once.
    void ShutdownFpTrapLog(const char* reason);
}
