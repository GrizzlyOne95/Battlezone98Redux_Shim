#pragma once
#include "lan_discovery.h"
#include "matchmaking_server.h"
#include <cstdint>
#include <string>
#include <string_view>

namespace BZROpenShim::LanNoAuth
{
    // Deliberately numeric: a hostname must never turn an offline selection
    // into a public connection after DNS or configuration changes.
    inline bool PrivateEndpoint(std::string_view text, std::string& canonical)
    {
        std::string host;
        unsigned port = 0;
        canonical.clear();
        if (!MatchmakingServer::SplitServer(text, host, port)) return false;
        uint32_t ip = 0;
        size_t at = 0;
        for (unsigned part = 0; part < 4; ++part)
        {
            unsigned value = 0, digits = 0;
            while (at < host.size() && host[at] >= '0' && host[at] <= '9')
            {
                if (++digits > 3) return false;
                value = value * 10 + unsigned(host[at++] - '0');
            }
            if (!digits || value > 255) return false;
            ip = (ip << 8) | value;
            if (part < 3 && (at == host.size() || host[at++] != '.')) return false;
        }
        if (at != host.size() || !LanDiscovery::IsLocalIPv4(ip) ||
            (ip & 255) == 255 || (ip >> 24) == 0) return false;
        canonical = std::to_string(ip >> 24) + "." + std::to_string((ip >> 16) & 255) +
            "." + std::to_string((ip >> 8) & 255) + "." + std::to_string(ip & 255) +
            ":" + std::to_string(port);
        return true;
    }

    inline bool NativeIdentityMatches(uint32_t kind, uint64_t value, uint64_t local)
    {
        // B is Redux's service/local namespace, not a Steam or Galaxy ID.
        return kind == 3 && local != 0 && value == local;
    }
}
