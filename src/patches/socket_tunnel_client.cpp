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
        // M1 deliberately refuses Steam mode; never silently fall back to an
        // unauthenticated UDP route or the official matchmaking server.
        if (!steamHost.empty())
        {
            ready = -1; Log("SteamTunnelHost is reserved for M2; connection blocked in this M1 build"); return;
        }
        if (!ParseEndpoint(udpBridge, config.remote, config.port))
        {
            ready = -1; Log("invalid TunnelUdpBridge (expected numeric IPv4:port); connection blocked"); return;
        }
        thread = CreateThread(nullptr, 0, Worker, nullptr, 0, nullptr);
        if (!thread) { ready = -1; Log("worker creation failed; connection blocked"); }
    }
    bool Requested() { return requested.load(); }
    bool Ready() { return ready.load() == 1 && !stop.load(); }
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
