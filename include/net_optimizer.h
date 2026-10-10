#pragma once

#include <cstddef>

namespace BZROpenShim
{
    // Installs optional Winsock IAT hooks and socket mitigations.
    // Safe to call once from the shim worker thread after process attach.
    void InitializeNetworkOptimizer();

    // Flushes optional network diagnostics before the shim unloads.
    void ShutdownNetworkOptimizer();

    // Drop the live BZRNet control WebSocket (TCP peer port 1337) so stock
    // reconnects and sends a fresh Authorization. Lounge nickname recycle
    // uses this; in-match callers must not. False if no such socket was open
    // or Winsock hooks are not installed.
    bool RecycleBzrNetWebSocket();

    // The host BZRNet matchmaking lookups are redirected to (net.ini
    // [OpenShimSocket] MatchmakingRedirectAddress or the BZ_/OPENSHIM_
    // environment override), as the socket layer actually applies it. False,
    // with out empty, when no redirect is active.
    bool GetMatchmakingRedirectTarget(char* out, size_t outSize);

    // Matchmaking server selection (pre-lobby Rebellion / Custom). Precedence,
    // highest first: the test redirect above, then this override, then the
    // /bzrserver= launch host, then the official host.
    //
    // The host the client connects to when nothing overrides it: /bzrserver=
    // from the command line if present, else the official host.
    bool GetLaunchServerHost(char* out, size_t outSize);
    // The live override host, applied to lookups of the launch host by the
    // getaddrinfo hook (not while a test redirect is set). Seeded at startup
    // from [Network] Server / CustomServer; empty or null clears it. Takes
    // effect on the next lookup, i.e. the next BZRNet reconnect; follow with
    // RecycleBzrNetWebSocket to reconnect now. Thread-safe.
    void SetMatchmakingServerOverride(const char* host);
    // False, with out empty, when no override is set.
    bool GetMatchmakingServerOverride(char* out, size_t outSize);
}
