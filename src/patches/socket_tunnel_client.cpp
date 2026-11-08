#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iphlpapi.h>
#include "socket_tunnel.h"
#include "shim_log.h"
#include "iat_patch.h"
#include <cstdio>
#include <iterator>
#include <vector>

namespace BZROpenShim::SocketTunnel
{
namespace
{
    std::atomic<bool> requested{false}, stop{false};
    std::atomic<int> ready{0};
    Config config;      // written only under configLock exclusive with no worker running
    HANDLE thread = nullptr;
    bool shutDown = false; // Stop() is final: the game's Steam session is going away
    SRWLOCK shutdownLock = SRWLOCK_INIT; // guards thread, shutDown and every (re)start
    SRWLOCK configLock = SRWLOCK_INIT;
    void Log(const char* message) { LogShimA(LogLevel::Info, "net", "[SocketTunnel] %s", message); }
    DWORD WINAPI Worker(void*) { return DWORD(Run(config, stop, ready, Log)); }
    // Host bridge (SteamTunnelBridge): written once in Configure, before its worker starts.
    std::atomic<bool> bridgeStop{false};
    std::atomic<int> bridgeReady{0};
    Config bridgeConfig;
    HANDLE bridgeThread = nullptr;
    void BridgeLog(const char* message) { LogShimA(LogLevel::Info, "net", "[SteamBridge] %s", message); }
    DWORD WINAPI BridgeWorker(void*) { return DWORD(Run(bridgeConfig, bridgeStop, bridgeReady, BridgeLog)); }
    bool BridgeRunning() { return bridgeThread && WaitForSingleObject(bridgeThread, 0) == WAIT_TIMEOUT; }
    // Same file the standalone bridge keeps beside its exe: a peer keeps its
    // loopback address (and any server ban) across bridge restarts.
    std::string PeersPath()
    {
        wchar_t path[32768]{};
        const DWORD n = GetModuleFileNameW(nullptr, path, DWORD(std::size(path)));
        if (!n || n >= std::size(path)) return {};
        std::wstring wide(path, n); wide.resize(wide.find_last_of(L"\\/") + 1); wide += L"steam_tunnel_peers.txt";
        const int size = WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, nullptr, 0, nullptr, nullptr);
        if (size <= 1) return {};
        std::string text(size_t(size), 0);
        WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, text.data(), size, nullptr, nullptr);
        text.resize(size_t(size - 1)); return text;
    }
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
    // Game thread (startup or live switch); idempotent.
    bool EnsureSteamShutdownGuard()
    {
        static int state = 0; // 0 untried, 1 guarded or not needed, -1 failed
        if (state) return state > 0;
        const auto hook = IatPatch::PatchImport(GetModuleHandleW(nullptr), "steam_api.dll", "SteamAPI_Shutdown",
            reinterpret_cast<void*>(&HookSteamShutdown), reinterpret_cast<void**>(&originalSteamShutdown));
        // NotFound: this exe never imports steam_api, so no game shutdown can race the worker.
        if (hook == IatPatch::Result::Faulted || (hook == IatPatch::Result::Patched && !originalSteamShutdown))
        { state = -1; Log("could not hook game SteamAPI_Shutdown; Steam tunnel blocked (exit would fault)"); return false; }
        Log(hook == IatPatch::Result::Patched ? "game SteamAPI_Shutdown hooked (exit stops tunnel first)"
                                              : "exe does not import SteamAPI_Shutdown; no exit guard installed");
        state = 1; return true;
    }
    void JoinWorker()
    {
        if (thread) { WaitForSingleObject(thread, INFINITE); CloseHandle(thread); thread = nullptr; }
    }
    // Caller holds shutdownLock (or runs before any other tunnel thread).
    void StopBridgeLocked()
    {
        if (!bridgeThread) return;
        bridgeStop = true; WaitForSingleObject(bridgeThread, INFINITE);
        CloseHandle(bridgeThread); bridgeThread = nullptr; bridgeStop = false;
    }
    bool LaunchBridgeLocked(const std::string& server)
    {
        bridgeConfig = Config{};
        bridgeConfig.bridge = bridgeConfig.steam = true; // borrow game init and callback pump
        bridgeConfig.server = server;
        bridgeConfig.identityMap = PeersPath();
        if (bridgeConfig.identityMap.empty()) { bridgeReady = -1; BridgeLog("game path unavailable for the peer map; host bridge not started"); return false; }
        bridgeReady = 0;
        bridgeThread = CreateThread(nullptr, 0, BridgeWorker, nullptr, 0, nullptr);
        if (!bridgeThread) { bridgeReady = -1; BridgeLog("worker creation failed; host bridge not started"); return false; }
        char text[160]; std::snprintf(text, sizeof(text),
            "hosting the Steam bridge in this game toward %s: Steam friends reach the server here while the game runs", server.c_str());
        BridgeLog(text); return true;
    }
    void StartBridge(const std::string& server, bool agentRequested)
    {
        if (agentRequested)
        { bridgeReady = -1; BridgeLog("SteamTunnelBridge cannot run with SteamTunnelHost or TunnelUdpBridge (one Steam tunnel per game); host bridge not started"); return; }
        if (!IsLoopback(server))
        { bridgeReady = -1; BridgeLog("SteamTunnelBridge must be auto or the numeric loopback IPv4 of a server on this PC (e.g. 127.0.0.2); host bridge not started"); return; }
        if (!EnsureSteamShutdownGuard()) { bridgeReady = -1; return; }
        AcquireSRWLockExclusive(&shutdownLock);
        LaunchBridgeLocked(server);
        ReleaseSRWLockExclusive(&shutdownLock);
    }
    // ---- SteamTunnelBridge=auto -------------------------------------------
    LocalServerSource autoSource = nullptr;
    HANDLE autoThread = nullptr, autoWake = nullptr;
    std::atomic<bool> autoQuit{false};
    // True when a TCP socket listens on ip:1337 (or 0.0.0.0:1337) on this PC.
    // Reads the TCP table instead of connecting, so the server sees no probes.
    bool LocalListener(const std::string& ip)
    {
        using GetTcpTableFn = ULONG (WINAPI*)(PMIB_TCPTABLE, PULONG, BOOL);
        static const GetTcpTableFn getTable = [] // resolved once, never retried
        {
            HMODULE module = LoadLibraryExW(L"iphlpapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
            return module ? reinterpret_cast<GetTcpTableFn>(GetProcAddress(module, "GetTcpTable")) : nullptr;
        }();
        IN_ADDR want{};
        if (!getTable || inet_pton(AF_INET, ip.c_str(), &want) != 1) return false;
        std::vector<unsigned char> buffer(16 * 1024);
        for (int attempt = 0;; ++attempt)
        {
            ULONG size = ULONG(buffer.size());
            const ULONG result = getTable(reinterpret_cast<PMIB_TCPTABLE>(buffer.data()), &size, FALSE);
            if (result == NO_ERROR) break;
            if (result != ERROR_INSUFFICIENT_BUFFER || attempt == 2) return false;
            buffer.resize(size_t(size) + 4096);
        }
        const auto* table = reinterpret_cast<const MIB_TCPTABLE*>(buffer.data());
        for (DWORD i = 0; i < table->dwNumEntries; ++i)
        {
            const MIB_TCPROW& row = table->table[i];
            if (row.dwState == MIB_TCP_STATE_LISTEN && ntohs(u_short(row.dwLocalPort)) == 1337 &&
                (row.dwLocalAddr == want.s_addr || row.dwLocalAddr == INADDR_ANY)) return true;
        }
        return false;
    }
    DWORD WINAPI AutoWorker(void*)
    {
        std::string current; int misses = 0; ULONGLONG retryAfter = 0;
        while (WaitForSingleObject(autoWake, 2000) == WAIT_TIMEOUT && !autoQuit)
        {
            std::string host;
            const bool want = autoSource(host) && host.find(':') == std::string::npos &&
                              IsLoopback(host) && LocalListener(host);
            // Stop() joins this thread while holding the lock: never block on it.
            if (!TryAcquireSRWLockExclusive(&shutdownLock)) continue;
            if (shutDown) { ReleaseSRWLockExclusive(&shutdownLock); break; }
            if (bridgeThread && !BridgeRunning()) // the worker failed on its own
            {
                StopBridgeLocked(); current.clear(); retryAfter = GetTickCount64() + 60000;
                BridgeLog("auto: host bridge stopped on an error; retrying in 60 s");
            }
            const bool alive = bridgeThread != nullptr;
            if (want && !requested && (!alive || current != host) && GetTickCount64() >= retryAfter)
            {
                StopBridgeLocked(); misses = 0;
                current = LaunchBridgeLocked(host) ? host : std::string();
                if (current.empty()) retryAfter = GetTickCount64() + 60000; // no 2 s log spam
            }
            else if (alive && !want && ++misses >= 2) // two polls: ride out a server restart blip
            {
                StopBridgeLocked(); current.clear(); misses = 0;
                BridgeLog("auto: no local server on 1337 any more; host bridge stopped");
            }
            else if (want) misses = 0;
            ReleaseSRWLockExclusive(&shutdownLock);
        }
        return 0;
    }
    void StartAuto(LocalServerSource source, bool agentRequested)
    {
        // A guest config, a GOG build or a test host: stay off, say why once.
        if (agentRequested) { BridgeLog("auto: this game joins through SteamTunnelHost/TunnelUdpBridge; host bridge off"); return; }
        if (!source) { BridgeLog("auto: no server selection available; host bridge off"); return; }
        if (!GetModuleHandleW(L"steam_api.dll")) { BridgeLog("auto: not the Steam build (no steam_api.dll); host bridge off"); return; }
        if (!EnsureSteamShutdownGuard()) return;
        autoSource = source;
        autoWake = CreateEventW(nullptr, TRUE, FALSE, nullptr);
        if (autoWake) autoThread = CreateThread(nullptr, 0, AutoWorker, nullptr, 0, nullptr);
        if (!autoThread) { BridgeLog("auto: supervisor creation failed; host bridge off"); return; }
        BridgeLog("auto: hosting the Steam bridge whenever this game points at a server running on this PC");
    }
}
    void Configure(const std::string& steamHost, const std::string& udpBridge, const std::string& steamBridge,
                   LocalServerSource localServer)
    {
        const bool agentRequested = !steamHost.empty() || !udpBridge.empty();
        if (_stricmp(steamBridge.c_str(), "auto") == 0) StartAuto(localServer, agentRequested);
        else if (!steamBridge.empty()) StartBridge(steamBridge, agentRequested);
        requested = !steamHost.empty() || !udpBridge.empty();
        if (!requested) return;
        if (!steamHost.empty())
        {
            if (!udpBridge.empty() || !ParseSteamId(steamHost, config.steamHost))
            { ready = -1; Log("Steam tunnel host invalid or both transports selected; connection blocked"); return; }
            config.steam = true; // borrow game init and callback pump
            if (!EnsureSteamShutdownGuard()) { ready = -1; return; }
        }
        else if (!ParseEndpoint(udpBridge, config.remote, config.port))
        {
            ready = -1; Log("invalid TunnelUdpBridge (expected numeric IPv4:port); connection blocked"); return;
        }
        thread = CreateThread(nullptr, 0, Worker, nullptr, 0, nullptr);
        if (!thread) { ready = -1; Log("worker creation failed; connection blocked"); }
    }
    bool SwitchSteamHost(uint64_t steamHost)
    {
        if (steamHost && !IndividualSteamId(steamHost)) return false;
        AcquireSRWLockExclusive(&shutdownLock);
        if (steamHost && BridgeRunning()) // under the lock: Stop() closes the handle
        {
            ReleaseSRWLockExclusive(&shutdownLock);
            Log("this game hosts the Steam bridge (SteamTunnelBridge); joining another host's tunnel is refused"); return false;
        }
        const bool ok = !shutDown && (!steamHost || EnsureSteamShutdownGuard());
        if (ok)
        {
            stop = true; JoinWorker(); // the worker closes its sockets before returning
            AcquireSRWLockExclusive(&configLock);
            config = Config{}; config.steam = steamHost != 0; config.steamHost = steamHost;
            ReleaseSRWLockExclusive(&configLock);
            ready = 0; stop = false; requested = steamHost != 0;
            if (steamHost)
            {
                thread = CreateThread(nullptr, 0, Worker, nullptr, 0, nullptr);
                if (!thread) { ready = -1; Log("worker creation failed; connection blocked"); }
            }
            char text[96]; std::snprintf(text, sizeof(text), "Steam tunnel switched to host %llu",
                static_cast<unsigned long long>(steamHost));
            Log(steamHost ? text : "Steam tunnel switched off");
        }
        ReleaseSRWLockExclusive(&shutdownLock);
        return ok;
    }
    uint64_t SteamHost()
    {
        AcquireSRWLockShared(&configLock);
        const uint64_t host = requested.load() && config.steam ? config.steamHost : 0;
        ReleaseSRWLockShared(&configLock);
        return host;
    }
    bool UdpBridgeConfigured()
    {
        AcquireSRWLockShared(&configLock);
        const bool udp = requested.load() && !config.steam;
        ReleaseSRWLockShared(&configLock);
        return udp;
    }
    bool Failed() { return ready.load() < 0; }
    bool Requested() { return requested.load(); }
    bool Ready() { return ready.load() == 1 && !stop.load(); }
    std::string CommunityEndpoint()
    {
        if (!requested) return {};
        AcquireSRWLockShared(&configLock);
        std::string endpoint = config.steam ? SteamCommunityEndpoint(config.steamHost)
            : "udp." + config.remote + "." + std::to_string(config.port) + ".openshim.invalid:1337";
        ReleaseSRWLockShared(&configLock);
        return endpoint;
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
        stop = true; bridgeStop = true; autoQuit = true; shutDown = true;
        if (autoWake) SetEvent(autoWake);
        // Called by the existing explicit optimizer shutdown, outside loader
        // lock. Every socket is nonblocking; the worker owns their destruction.
        JoinWorker();
        // The supervisor only try-locks, so joining it under the lock is safe.
        if (autoThread) { WaitForSingleObject(autoThread, INFINITE); CloseHandle(autoThread); autoThread = nullptr; }
        if (bridgeThread) { WaitForSingleObject(bridgeThread, INFINITE); CloseHandle(bridgeThread); bridgeThread = nullptr; }
        ReleaseSRWLockExclusive(&shutdownLock);
    }
}
