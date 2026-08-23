// native_cpu_sampler.h
// BZR Open Shim - process-wide sampling CPU profiler (diagnostic only)
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // Returns true when OPENSHIM_PROFILE_NATIVE_CPU asks for the sampler.
    // The sampler is dormant unless explicitly requested; normal gameplay and
    // every other diagnostic are unaffected when it is off.
    bool IsNativeCpuSamplerRequested();

    // Starts the sampler thread. The sampler never writes to game memory and
    // installs no detours: it periodically suspends the other threads of this
    // process, reads EIP plus a bounded EBP chain, resumes them, and appends
    // the raw samples to a binary file under logs\. Attribution from raw
    // addresses to functions happens entirely offline.
    void InitializeNativeCpuSampler();

    // Stops the sampler thread and flushes the sample file.
    void ShutdownNativeCpuSampler();
}
