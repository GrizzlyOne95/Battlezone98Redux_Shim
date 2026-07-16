#pragma once

namespace BZROpenShim
{
    // Installs the process crash logger: an unhandled-exception filter that
    // writes a text report (registers, module+RVA, stack scan) to
    // logs\openshim_crash.log and a minidump beside it, plus an optional
    // first-chance vectored logger for fatal exception codes.
    //
    // Opt-outs:
    //   OPENSHIM_DISABLE_CRASH_LOGGER=1  - install nothing
    //   OPENSHIM_DISABLE_CRASH_VEH=1     - skip the first-chance vectored logger
    //   OPENSHIM_DISABLE_CRASH_DUMP=1    - skip minidump writing
    void InstallCrashLogger();
}
