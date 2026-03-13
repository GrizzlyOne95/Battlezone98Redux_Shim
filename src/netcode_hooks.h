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
    static constexpr int DEFAULT_RECV_BUFFER  = 2097152;  // 2 MB

    // Apply netcode patches from netcode_manifest.json.
    // Call this from RunPatcher() after the main patches are applied.
    void ApplyNetcodeHooks();
}
