// netcode_hooks.h
// BZR Open Shim - netcode socket buffer enhancement
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Applies byte patches from netcode_manifest.json to modify the game's
// built-in socket buffer size constants directly in memory.

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
