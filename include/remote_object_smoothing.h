// remote_object_smoothing.h
// BZR Open Shim - frame-rate-independent smoothing of remote objects (opt-in)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // With [Network] RemoteSmoothingMs > 0, detours GameObject::Simulate
    // (GOG 0x004DEEC0) so a remote object's displayed transform approaches its
    // dead-reckoned state with a time constant instead of stock's fixed
    // per-frame factors. Client-local and display-only: physics, authority and
    // the wire format are unchanged. 0 (the default) installs nothing.
    void InitializeRemoteObjectSmoothing();
}
