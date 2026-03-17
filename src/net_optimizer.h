#pragma once

namespace BZROpenShim
{
    // Installs optional Winsock IAT hooks and socket mitigations.
    // Safe to call once from the shim worker thread after process attach.
    void InitializeNetworkOptimizer();

    // Flushes optional network diagnostics before the shim unloads.
    void ShutdownNetworkOptimizer();
}
