#pragma once
#include <atomic>
#include <cstdint>
#include <string>
#include "steam_tunnel_policy.h"

namespace BZROpenShim::SocketTunnel
{
    struct Config
    {
        bool bridge = false;
        uint64_t steamHost = 0; // nonzero selects Steam on agent
        bool steam = false;
        bool ownSteam = false; // standalone only: init/pump/shutdown our own Steam session
        std::string identityMap; // bridge: durable SteamID -> loopback source mapping
        std::string banList; // bridge: bans.cfg; refuse/close S<steamid64> peers (empty = no gate)
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
    // Thread-safe. True when ip is a 127.0.1.<slot> source that a Steam bridge
    // in this process assigned to a Steam-authenticated peer; fills its SteamID64.
    bool BridgedSteamId(const std::string& ip, uint64_t& steamId);
    // OpenShim lifecycle wrapper; configured once before Winsock hooks install.
    // steamBridge hosts the Steam bridge inside this game process on the
    // game's own Steam session, so friends join without socket_tunnel.exe:
    //   ""            off
    //   "auto"        only while localServer() names a numeric loopback IPv4
    //                 (no port) with a TCP listener on 1337, i.e. this game
    //                 points at a dedicated server running on this PC
    //   "127.0.0.x"   always, toward that server
    // Exclusive with the agent keys: one Steam tunnel transport per process.
    using LocalServerSource = bool (*)(std::string& host);
    void Configure(const std::string& steamHost, const std::string& udpBridge,
                   const std::string& steamBridge = {}, LocalServerSource localServer = nullptr);
    bool Requested();
    bool Ready();
    // Logical server identity for community-key derivation. Never resolve this
    // name: it namespaces distinct tunnels that share physical 127.0.0.1.
    std::string CommunityEndpoint();
    // Bound the first resolver wait while the worker binds its local ports.
    bool WaitReady(unsigned timeoutMs = 1000);
    // Steam Join Game: restart the agent toward another bridge (0 = off), on
    // the game thread. Waits for the old worker. False after Stop() or when
    // the exit guard cannot be installed. Replaces a UDP-bridge config.
    bool SwitchSteamHost(uint64_t steamHost);
    uint64_t SteamHost(); // 0 when not tunnelling over Steam
    bool Failed(); // the worker stopped on an error (e.g. port 1337 occupied)
    bool UdpBridgeConfigured();
    void Stop(); // final
}
