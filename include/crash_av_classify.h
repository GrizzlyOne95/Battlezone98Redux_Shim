// Decides whether a first-chance access violation is certainly fatal, so the
// crash logger can write its [CRASH] record and minidump before the search
// continues. Some runtimes (seen under Proton, issue #942) end the process
// before the unhandled filter runs, which loses the dump.
//
// Certainly fatal means the CPU tried to run code that is not there: an
// execute (DEP) fault, eip equal to the faulting address, or eip outside
// committed executable memory. Read and write faults with eip in real code
// are never early-dumped: memory probes and guarded reads make those and
// recover.
//
// One case could recover: an OpenShim __try guard around a call through a
// possibly dead pointer. The caller reports shimGuardedCall when the return
// address at esp and the nearest SEH handler are both in an OpenShim module,
// and the early dump is skipped. Bad calls from game or Ogre code, and shim
// calls with no guard of their own, still dump.
//
// Known residual misfire: a third-party VEH registered after ours that
// deliberately runs no-access pages and recovers would use up the one dump.
//
// Pure logic, no Windows calls, so it can be unit tested.

#pragma once

#include <cstdint>

namespace BZROpenShim
{
namespace CrashAvClassify
{
    constexpr uint32_t kAccessViolation = 0xC0000005u;
    constexpr uintptr_t kExecuteFault = 8;

    struct FaultFacts
    {
        uint32_t code;
        uint32_t numberParameters;   // ExceptionRecord::NumberParameters
        uintptr_t accessKind;        // ExceptionInformation[0]
        uintptr_t faultAddress;      // ExceptionInformation[1]
        uintptr_t eip;               // ExceptionAddress
        bool eipExecutable;          // eip page committed with PAGE_EXECUTE*
        bool shimGuardedCall;        // shim call under a shim __try guard
    };

    inline bool IsCertainlyFatalAv(const FaultFacts& f)
    {
        if (f.code != kAccessViolation) return false;
        if (f.shimGuardedCall) return false;
        if (!f.eipExecutable) return true;
        if (f.numberParameters < 2) return false;
        if (f.accessKind == kExecuteFault) return true;
        return f.faultAddress == f.eip;
    }
}
}
