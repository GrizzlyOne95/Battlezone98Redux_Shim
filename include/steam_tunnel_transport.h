#pragma once
#include "socket_tunnel.h"
#include <memory>
#include <vector>

namespace BZROpenShim::SocketTunnel
{
    enum class SteamSend { Sent, Busy, Failed };
    struct SteamEvent { uint32_t connection; uint64_t identity; bool connected; };
    // SDK types stay inside the implementation. All methods run on the tunnel
    // worker; status callbacks only enqueue under a lock and never touch sockets.
    class SteamTransport
    {
    public:
        SteamTransport();
        ~SteamTransport();
        SteamTransport(const SteamTransport&) = delete;
        void Start(const Config&, std::atomic<bool>& stop, Logger);
        std::vector<SteamEvent> Poll(uint64_t now);
        SteamSend Send(uint32_t connection, const std::vector<uint8_t>&, bool reliable);
        // 1 message, 0 empty, -1 transport failure. Bounded native receive.
        int Receive(uint32_t connection, std::vector<uint8_t>&, bool& reliable);
        void Close(uint32_t connection);
        int SelfTest(); // real SDK socket pair; never a remote P2P acceptance claim
    private:
        struct Impl;
        std::unique_ptr<Impl> impl;
    };
}
