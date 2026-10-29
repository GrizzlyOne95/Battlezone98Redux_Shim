#pragma once
#include "direct_lan_transport.h"

namespace BZROpenShim::DirectLan
{
    inline constexpr std::array<uint8_t, 8> kPeerFrameMagic{'B','Z','L','A','N','M','0','1'};
    struct PeerPacket
    {
        Id sender;
        std::vector<uint8_t> bytes;
        bool reliable = false;
    };
    // One game process owns a TCP and UDP socket at its advertised gameplay
    // port. Reliable payloads use direct TCP; unreliable payloads use direct
    // UDP. Session control is separate; the host never forwards peer traffic.
    // This is a new OpenShim transport, not stock BZRNet packet framing.
    class Mesh
    {
    public:
        explicit Mesh(Id local);
        ~Mesh();
        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;
        bool Open(uint32_t bindAddress, uint16_t port = 0);
        bool Apply(const View&); // accepted roster, including bound endpoints
        void Poll(); // nonblocking, bounded queues/work; caller's thread only
        bool Ready() const; // transport links only, not native engine readiness
        bool Send(Id target, const uint8_t*, size_t, bool reliable);
        std::vector<PeerPacket> TakeReceived();
        void Close();
        uint16_t Port() const;
        const std::string& Error() const;
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
