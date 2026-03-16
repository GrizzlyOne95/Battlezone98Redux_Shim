// netcode_hooks.cpp
// BZR Open Shim - legacy netcode compatibility wrapper
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "netcode_hooks.h"
#include "net_optimizer.h"
#include "shim_log.h"

namespace BZROpenShim
{
    void ApplyNetcodeHooks()
    {
        LogShimA(LogLevel::Info, "net", "[OpenShimNet] ApplyNetcodeHooks called; delegating to InitializeNetworkOptimizer()");
        InitializeNetworkOptimizer();
    }
}
