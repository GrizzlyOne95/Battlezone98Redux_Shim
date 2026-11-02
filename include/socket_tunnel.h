#pragma once
#include <atomic>
#include <cstdint>
#include <string>

namespace BZROpenShim::SocketTunnel
{
    struct Config
    {
        bool bridge = false;
        // All addresses are numeric IPv4. Defaults never expose a LAN listener.
        std::string listen = "127.0.0.1";
        uint16_t port = 27030;
        std::string remote = "127.0.0.1";
        std::string allow = "127.0.0.1";
        std::string server = "127.0.0.2";
    };
    using Logger = void (*)(const char*);
    // Owns WSAStartup/WSACleanup and every socket on the calling worker.
    // ready: 0 pending, 1 all listeners bound, -1 initialization/run failure.
    int Run(const Config&, std::atomic<bool>& stop, std::atomic<int>& ready, Logger);
    bool ParseEndpoint(const std::string&, std::string& ip, uint16_t& port);
    bool IsLoopback(const std::string&);
    // OpenShim lifecycle wrapper; configured once before Winsock hooks install.
    void Configure(const std::string& steamHost, const std::string& udpBridge);
    bool Requested();
    bool Ready();
    // Bound the first resolver wait while the worker binds its local ports.
    bool WaitReady(unsigned timeoutMs = 1000);
    void Stop();
}
