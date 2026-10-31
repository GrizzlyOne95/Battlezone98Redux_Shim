#pragma once
#include <cstdint>
#include <string>

namespace BZROpenShim::LanNoAuth
{
    void SelectEndpoint(const char* endpoint, bool lanSelection);
    bool Enabled();
    // Installs only when Network/NoAuthLan was explicitly enabled. Every native
    // boundary is qualified before local identity/readiness can be enabled.
    void InstallIfPossible(bool authorizationHookReady);
    bool Requested();
    bool Available();
    bool Ready();
    // Last readiness computed on the main thread by PumpMainThread; safe from any thread.
    bool ReadyCached();
    bool Identity(std::string& id, std::string& name);
    // Called only by shell ticks, never the background diagnostic watcher.
    void PumpMainThread();
    uintptr_t PlatformReadyCode(uintptr_t originalSite);
}
