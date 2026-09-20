// openshim_plugin_bootstrap.h
// BZR Open Shim - the plugin's handle on the bootstrap service table.
//
// Resolved once in BZPlugin_Load and then constant for the life of the
// process. Only plugins/openshim.dll compiles the implementation.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include "openshim_bootstrap_api.h"

namespace BZROpenShim::Plugin
{
    // Null until BZPlugin_Load has resolved it, and null forever after if
    // winmm.dll turned out not to export the table. Callers must handle null
    // rather than assume the bootstrap is there.
    const OpenShimBootstrapApiV1* BootstrapApi();

    // Resolves OpenShimBootstrap_GetApi from the already-loaded winmm.dll and
    // stores the table. Never calls LoadLibrary: the proxy is what loaded us,
    // so it is in the module list by definition.
    bool AcquireBootstrapApi();
}
