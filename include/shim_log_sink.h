// shim_log_sink.h
// BZR Open Shim - where a formatted log line is finally written.
//
// The logger is split because openshim.log has exactly one owner. winmm.dll
// opens it, writes the session header, and closes it; it has to, because it
// logs long before OpenShim exists. plugins/openshim.dll formats its own
// messages and hands the finished text over.
//
// Everything above this line -- LogShimA/W/VA/VW, the format strings, the
// hundreds of call sites -- is unchanged and lives in shim_log_client.cpp.
// All that moves across the module boundary is a completed UTF-8 string.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

// The sink pointer is an ABI detail shared with the C bootstrap table, so it
// must be __cdecl on the shipping Win32 build. The Linux test lane compiles
// these headers to run the engine-independent suites and has no such keyword.
#ifdef _WIN32
#define BZRO_SINK_CALL __cdecl
#else
#define BZRO_SINK_CALL
#endif

namespace BZROpenShim
{
    // Receives one already-formatted, already-trimmed UTF-8 line. Levels are
    // the numeric LogLevel space (0=Debug, 1=Info, 2=Warn, 3=Error), so this
    // signature is usable straight from the C bootstrap API table.
    using ShimLogSinkFn = void(BZRO_SINK_CALL*)(
        uint32_t level, const char* component, const char* message);

    // Installs the sink the client routes to.
    //
    // In winmm.dll the sink translation unit registers itself during static
    // initialisation, so the bootstrap is wired before DllMain's own code
    // runs. In plugins/openshim.dll there is no sink, and BZPlugin_Load
    // installs a bridge that forwards to the bootstrap API instead.
    //
    // With no sink installed, lines still reach the debugger through
    // OutputDebugString and are not written to any file.
    void SetShimLogSink(ShimLogSinkFn sink);
    ShimLogSinkFn GetShimLogSink();

    // The bootstrap's own sink: owns openshim.log, its lock, the session
    // header and footer. Only winmm.dll compiles the implementation.
    void ShimLogSinkWrite(uint32_t level, const char* component, const char* message);
}
