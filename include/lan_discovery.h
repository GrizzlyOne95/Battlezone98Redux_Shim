#pragma once
// OpenShim LAN discovery v1. Discovery is a hint, not authentication. The
// connection address always comes from the UDP source, never the payload.
#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <string_view>

namespace BZROpenShim::LanDiscovery
{
    inline constexpr uint16_t kPort = 21337;
    inline constexpr size_t kMaxHosts = 32;
    using Nonce = std::array<uint8_t, 8>;
    using Query = std::array<uint8_t, 96>;

    inline Query MakeQuery(const Nonce& nonce)
    {
        Query query{};
        std::memcpy(query.data(), "BZRLAN1?", 8);
        std::memcpy(query.data() + 8, nonce.data(), 8);
        return query;
    }

    inline bool IsLocalIPv4(uint32_t hostOrder)
    {
        return (hostOrder >> 24) == 10 || (hostOrder >> 24) == 127 ||
            (hostOrder >> 20) == 0xAC1 || (hostOrder >> 16) == 0xC0A8 ||
            (hostOrder >> 16) == 0xA9FE;
    }

    struct Reply
    {
        uint16_t port = 0;
        std::string name;
    };

    inline bool ParseReply(std::string_view packet, const Nonce& nonce, Reply& out)
    {
        out = {};
        if (packet.size() < 19 || packet.size() > 82 ||
            packet.substr(0, 8) != "BZRLAN1!" ||
            std::memcmp(packet.data() + 8, nonce.data(), 8) != 0)
            return false;
        const auto port = (static_cast<uint8_t>(packet[16]) << 8) |
            static_cast<uint8_t>(packet[17]);
        if (port == 0 || port > 65534)
            return false; // Redux's endpoint probe uses port + 1.
        for (size_t i = 18; i < packet.size(); ++i)
            if (static_cast<uint8_t>(packet[i]) < 32 ||
                static_cast<uint8_t>(packet[i]) > 126)
                return false;
        out.port = static_cast<uint16_t>(port);
        out.name.assign(packet.substr(18));
        return true;
    }

    inline std::string Endpoint(std::string_view address, uint16_t port)
    {
        return std::string(address) + (port == 1337 ? "" : ":" + std::to_string(port));
    }
}
