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
    // What the platform readiness gate (0x00764870) answers while this
    // module's detour sits on it: the LAN admission when LAN is requested,
    // otherwise the stock code through the trampoline. -1 when the gate is not
    // detoured. The detour's jump also fails that site's byte guard, so
    // QueryStockIsNetworkInit asks here first. Main thread only, as the gate.
    int DetouredPlatformReady();
}
