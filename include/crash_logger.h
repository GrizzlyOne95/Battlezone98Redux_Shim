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
    //   OPENSHIM_DISABLE_CRASH_DUMP=1    - skip minidump writing ([Diagnostics]
    //                                      CrashMinidumps = 0; default on, newest 3 kept)
    //   OPENSHIM_DISABLE_CRASH_CRT_HANDLERS=1 - skip the purecall / invalid parameter /
    //                                      terminate / SIGABRT handlers
    // A stack overflow is reported from a watcher thread made here.
    void InstallCrashLogger();

    // For a deliberate fail-closed exit (no exception, no dump): appends
    // "<time> FAIL-CLOSED [component]: reason" to logs\openshim_crash.log and
    // keeps a dated openshim_crash_YYYYMMDD_HHMMSS.log copy, as a crash does.
    // Does nothing when the crash logger is not installed.
    void WriteCrashLogFailClosed(const char* component, const char* reason);
}
