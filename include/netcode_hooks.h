// netcode_hooks.h
// BZR Open Shim - netcode socket buffer enhancement
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Applies startup-time socket buffer hooks configured by netcode_manifest.json.

#pragma once
#include <cstdint>

namespace BZROpenShim
{
    // Default buffer sizes (used when no manifest is present)
    static constexpr int DEFAULT_SEND_BUFFER  = 524288;   // 512 KB
    static constexpr int DEFAULT_RECV_BUFFER  = 4194304;  // 4 MB

    // Legacy compatibility entry point for older call sites.
    // Netcode initialization is now owned by net_optimizer.cpp.
    void ApplyNetcodeHooks();
}
