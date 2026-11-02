#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include "socket_tunnel.h"
#include "shim_log.h"

namespace BZROpenShim::SocketTunnel
{
namespace
{
    std::atomic<bool> requested{false}, stop{false};
    std::atomic<int> ready{0};
    Config config;
    HANDLE thread = nullptr;
    SRWLOCK shutdownLock = SRWLOCK_INIT;
    void Log(const char* message) { LogShimA(LogLevel::Info, "net", "[SocketTunnel] %s", message); }
    DWORD WINAPI Worker(void*) { return DWORD(Run(config, stop, ready, Log)); }
}
    void Configure(const std::string& steamHost, const std::string& udpBridge)
    {
        requested = !steamHost.empty() || !udpBridge.empty();
        if (!requested) return;
        if (!steamHost.empty())
        {
            if (!udpBridge.empty() || !ParseSteamId(steamHost, config.steamHost))
            { ready = -1; Log("Steam tunnel host invalid or both transports selected; connection blocked"); return; }
            config.steam = true; // borrow game init and callback pump
        }
        else if (!ParseEndpoint(udpBridge, config.remote, config.port))
        {
            ready = -1; Log("invalid TunnelUdpBridge (expected numeric IPv4:port); connection blocked"); return;
        }
        thread = CreateThread(nullptr, 0, Worker, nullptr, 0, nullptr);
        if (!thread) { ready = -1; Log("worker creation failed; connection blocked"); }
    }
    bool Requested() { return requested.load(); }
    bool Ready() { return ready.load() == 1 && !stop.load(); }
    std::string CommunityEndpoint()
    {
        if (!requested) return {};
        if (config.steam) return SteamCommunityEndpoint(config.steamHost);
        return "udp." + config.remote + "." + std::to_string(config.port) + ".openshim.invalid:1337";
    }
    bool WaitReady(unsigned timeoutMs)
    {
        const auto deadline = GetTickCount64() + timeoutMs;
        while (requested.load() && ready.load() == 0 && !stop.load() && GetTickCount64() < deadline)
            Sleep(5);
        return Ready(); // ports bound only; not remote bridge qualification
    }
    void Stop()
    {
        AcquireSRWLockExclusive(&shutdownLock);
        stop = true;
        // Called by the existing explicit optimizer shutdown, outside loader
        // lock. Every socket is nonblocking; the worker owns their destruction.
        if (thread) { WaitForSingleObject(thread, INFINITE); CloseHandle(thread); thread = nullptr; }
        ReleaseSRWLockExclusive(&shutdownLock);
    }
}
