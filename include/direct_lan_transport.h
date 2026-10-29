#pragma once
#include "direct_lan_session.h"
#include <memory>

namespace BZROpenShim::DirectLan
{
    struct Address { uint32_t ipv4 = 0; uint16_t port = 0; };
    bool ParseIPv4(const std::string&, uint32_t& hostOrder);
    std::string FormatIPv4(uint32_t hostOrder);
    bool RandomId(Id&); // called explicitly, never from DLL load
    Time Now();

    // One Node belongs to one participating game process. Hosting opens the
    // game client's own TCP socket; there is no service process, WebSocket,
    // account provider or external endpoint. Gameplay is not carried here.
    class Node
    {
    public:
        Node(Id, std::string name, Compatibility, uint16_t gameplayPort);
        ~Node();
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        bool Host(Config, Id session, uint32_t bindAddress, uint16_t controlPort = 0);
        bool Join(Address, Id advertisedSession = {});
        bool EnableDiscovery(uint16_t port = 21338);
        uint16_t DiscoveryPort() const;
        void Poll(); // nonblocking, bounded per-channel work
        void Close(); // closes only this object's sockets
        Session& Control();
        const Session& Control() const;
        uint16_t ControlPort() const;
        size_t Connections() const;
        const std::string& Error() const;
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
