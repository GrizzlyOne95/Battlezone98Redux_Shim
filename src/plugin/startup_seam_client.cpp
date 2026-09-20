// startup_seam_client.cpp
// BZR Open Shim - the plugin's side of the startup seam.
//
// plugins/openshim.dll does not own the startup decision and never makes it;
// the bootstrap already did, before this module existed. These two functions
// carry the same names the runtime already calls, so the renderer code does
// not care that the answer now comes from another module.
//
// Only compiled into the plugin. winmm.dll has the real implementations in
// startup_backend_seam.cpp.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "startup_backend_seam.h"

#include "openshim_bootstrap_api.h"
#include "openshim_plugin_bootstrap.h"

#include <cstring>

namespace BZROpenShim::StartupSeam
{
    bool CopyStartupRendererResult(void* out, uint32_t capacity)
    {
        const OpenShimBootstrapApiV1* api = Plugin::BootstrapApi();
        if (api == nullptr || api->copyStartupRendererResult == nullptr)
        {
            // No bootstrap table means the plugin is running somewhere it was
            // not supposed to. Report failure rather than a zeroed record that
            // would read as a real "Auto, nothing written" decision.
            return false;
        }
        return api->copyStartupRendererResult(out, capacity) != 0;
    }

    void ClearPendingMarker()
    {
        const OpenShimBootstrapApiV1* api = Plugin::BootstrapApi();
        if (api != nullptr && api->clearStartupPendingMarker != nullptr)
            api->clearStartupPendingMarker();
    }
}
