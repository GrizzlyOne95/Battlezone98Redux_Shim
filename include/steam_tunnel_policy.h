#pragma once
#include <cstdint>
#include <limits>
#include <map>
#include <sstream>
#include <string>

namespace BZROpenShim::SocketTunnel
{
    inline bool IndividualSteamId(uint64_t id)
    {
        // Public universe, individual account, desktop instance, nonzero account.
        return (id >> 56) == 1 && ((id >> 52) & 15) == 1 &&
               ((id >> 32) & 0xfffff) == 1 && uint32_t(id) != 0;
    }
    inline bool ParseSteamId(const std::string& text, uint64_t& result)
    {
        if (text.empty() || text.size() > 20) return false;
        uint64_t value = 0;
        for (char c : text)
        {
            if (c < '0' || c > '9' || value > ((std::numeric_limits<uint64_t>::max)() - unsigned(c - '0')) / 10) return false;
            value = value * 10 + unsigned(c - '0');
        }
        if (!IndividualSteamId(value)) return false;
        result = value; return true;
    }
    inline std::string SteamCommunityEndpoint(uint64_t id)
    { return IndividualSteamId(id) ? "steam." + std::to_string(id) + ".openshim.invalid:1337" : ""; }
    // Mapping never reuses an assigned slot. Bans remain attached to the same
    // authenticated Steam identity, including across bridge restarts. Exhaustion
    // or corrupt state rejects new peers rather than recycling someone's IP.
    struct SteamIdentityMap
    {
        std::map<uint64_t, unsigned> slots;
        static std::string Ip(unsigned slot) { return "127.0.1." + std::to_string(slot); }
        unsigned Find(uint64_t id) const
        { auto it = slots.find(id); return it == slots.end() ? 0 : it->second; }
        unsigned Assign(uint64_t id, const std::string& server)
        {
            if (!IndividualSteamId(id)) return 0;
            if (auto slot = Find(id)) return Ip(slot) == server ? 0 : slot;
            for (unsigned slot = 1; slot <= 254; ++slot)
            {
                bool used = Ip(slot) == server;
                for (const auto& entry : slots) if (entry.second == slot) used = true;
                if (!used) { slots.emplace(id, slot); return slot; }
            }
            return 0;
        }
        std::string Save() const
        {
            std::ostringstream out; out << "BZRSteamPeers1\n";
            for (const auto& entry : slots) out << entry.first << ' ' << entry.second << '\n';
            return out.str();
        }
        bool Load(const std::string& text)
        {
            if (text.size() > 16384) return false;
            SteamIdentityMap parsed;
            std::istringstream input(text); std::string line;
            if (!std::getline(input, line) || line != "BZRSteamPeers1") return false;
            while (std::getline(input, line))
            {
                std::istringstream row(line); std::string idText, slotText, extra;
                uint64_t id = 0;
                if (!(row >> idText >> slotText) || (row >> extra) || !ParseSteamId(idText, id) || slotText.size() > 3) return false;
                unsigned slot = 0;
                for (char c : slotText) { if (c < '0' || c > '9') return false; slot = slot * 10 + unsigned(c - '0'); }
                if (!slot || slot > 254 || parsed.slots.count(id)) return false;
                for (const auto& entry : parsed.slots) if (entry.second == slot) return false;
                parsed.slots.emplace(id, slot);
            }
            slots = std::move(parsed.slots); return true;
        }
    };
}
