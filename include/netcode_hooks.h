// netcode_hooks.h
// BZR Open Shim - netcode socket buffer defaults
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Default socket buffer sizes consumed by net_optimizer.cpp. Netcode
// initialization itself is owned by InitializeNetworkOptimizer(); the former
// ApplyNetcodeHooks() forwarder had no callers and was removed.

#pragma once
#include <cstdint>

namespace BZROpenShim
{
    // Default buffer sizes (used when no manifest is present)
    static constexpr int DEFAULT_SEND_BUFFER  = 524288;   // 512 KB
    static constexpr int DEFAULT_RECV_BUFFER  = 4194304;  // 4 MB
}
