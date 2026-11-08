#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include "socket_tunnel.h"
#include "shim_log.h"
#include "iat_patch.h"

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
    // The Steam path borrows the game's Steam API session. The game tears it
    // down in its single SteamAPI_Shutdown call (GOG FUN_007657b0, call at
    // 0x007658EE) long before CRT exit reaches ShutdownNetworkOptimizer, and a
    // worker still polling SteamNetworkingSockets then faults in steamclient.dll.
    // Stop the worker first, on the game's own thread, then let Steam go.
    using SteamShutdownFn = void (__cdecl*)();
    SteamShutdownFn originalSteamShutdown = nullptr;
    void __cdecl HookSteamShutdown()
    {
        Log("game SteamAPI_Shutdown: stopping tunnel before Steam goes away");
        Stop();
        if (originalSteamShutdown) originalSteamShutdown();
    }
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
            const auto hook = IatPatch::PatchImport(GetModuleHandleW(nullptr), "steam_api.dll", "SteamAPI_Shutdown",
                reinterpret_cast<void*>(&HookSteamShutdown), reinterpret_cast<void**>(&originalSteamShutdown));
            // NotFound: this exe never imports steam_api, so no game shutdown can race the worker.
            if (hook == IatPatch::Result::Faulted || (hook == IatPatch::Result::Patched && !originalSteamShutdown))
            { ready = -1; Log("could not hook game SteamAPI_Shutdown; Steam tunnel blocked (exit would fault)"); return; }
            Log(hook == IatPatch::Result::Patched ? "game SteamAPI_Shutdown hooked (exit stops tunnel first)"
                                                  : "exe does not import SteamAPI_Shutdown; no exit guard installed");
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
