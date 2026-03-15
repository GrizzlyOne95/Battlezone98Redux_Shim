// d3d_startup_hooks.h
// BZR Open Shim - early Direct3D startup hooks
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // Installs startup-time IAT hooks for Direct3DCreate9 / Direct3DCreate9Ex
    // so addon DLLs can be loaded before the game creates its real D3D device.
    void ApplyD3DStartupHooks();
}
