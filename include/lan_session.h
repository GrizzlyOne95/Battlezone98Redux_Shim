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
    bool StartHost(const std::wstring& gameRoot, bool inProcess = false);
    void StopHost();
    bool StartScan();
    void StopScan();
    void Tick();
    Snapshot Status();
}
