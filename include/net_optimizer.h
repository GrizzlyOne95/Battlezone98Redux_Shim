#pragma once

namespace BZROpenShim
{
    // Installs optional Winsock IAT hooks and socket mitigations.
    // Safe to call once from the shim worker thread after process attach.
    void InitializeNetworkOptimizer();

    // Flushes optional network diagnostics before the shim unloads.
    void ShutdownNetworkOptimizer();

    // Drop the live BZRNet control WebSocket (TCP peer port 1337) so stock
    // reconnects and sends a fresh Authorization. Lounge nickname recycle
    // uses this; in-match callers must not. False if no such socket was open
    // or Winsock hooks are not installed.
    bool RecycleBzrNetWebSocket();
}
