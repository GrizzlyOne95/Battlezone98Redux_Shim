// openshim_bootstrap_api.cpp
// BZR Open Shim - the private bootstrap service table. See the header.
//
// Only winmm.dll compiles this. plugins/openshim.dll resolves
// OpenShimBootstrap_GetApi once during BZPlugin_Load, which is already
// outside the loader lock.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "openshim_bootstrap_api.h"

#include "shim_log_sink.h"
#include "startup_backend_seam.h"

namespace
{
    void __cdecl BootstrapLogMessage(
        uint32_t level, const char* component, const char* message)
    {
        // Already formatted by the caller; this only reaches the sink that
        // owns openshim.log.
        BZROpenShim::ShimLogSinkWrite(level, component, message);
    }

    int32_t __cdecl BootstrapCopyStartupRendererResult(void* out, uint32_t capacity)
    {
        return BZROpenShim::StartupSeam::CopyStartupRendererResult(out, capacity)
                   ? 1
                   : 0;
    }

    void __cdecl BootstrapClearStartupPendingMarker(void)
    {
        BZROpenShim::StartupSeam::ClearPendingMarker();
    }

    // Static, so handing it out is a pointer return with no allocation and no
    // lifetime question: winmm.dll is pinned for the process.
    const OpenShimBootstrapApiV1 g_Api = {
        sizeof(OpenShimBootstrapApiV1),
        OPENSHIM_BOOTSTRAP_API_V1,
        BootstrapLogMessage,
        BootstrapCopyStartupRendererResult,
        BootstrapClearStartupPendingMarker,
    };
}

extern "C" __declspec(dllexport) const OpenShimBootstrapApiV1* __cdecl
OpenShimBootstrap_GetApi(uint32_t version)
{
    // An unsupported version gets nothing rather than a partially compatible
    // table, the same rule OpenShimGetApi follows for the public SDK.
    if (version != 0u && version != OPENSHIM_BOOTSTRAP_API_V1)
        return nullptr;
    return &g_Api;
}
