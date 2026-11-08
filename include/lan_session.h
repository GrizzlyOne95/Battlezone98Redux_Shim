#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace BZROpenShim::LanSession
{
    enum class HostState { Stopped, Starting, Running, Stopping, Failed };
    struct Host { std::string address, name; uint16_t port = 1337; };
    struct Snapshot
    {
        HostState state = HostState::Stopped;
        bool scanning = false;
        std::string hostAddress, hostMessage, scanMessage;
        std::vector<Host> hosts;
    };

    // UI-thread only. No socket/process work at DLL load, no worker thread,
    // no shell/PATH execution. The optional helper lives at tools/lan/BZRServer.exe.
    // bindAddress empty: the routed private LAN IPv4. Otherwise it must be a
    // numeric 127.x.y.z address: a host reachable only through the in-game
    // Steam bridge (SteamTunnelBridge=auto), not by other LAN PCs.
    bool StartHost(const std::wstring& gameRoot, bool inProcess = false,
        const std::string& bindAddress = {});
    void StopHost();
    bool StartScan();
    void StopScan();
    void Tick();
    Snapshot Status();
}
