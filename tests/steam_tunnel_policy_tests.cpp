#include "steam_tunnel_policy.h"
#include "community_key.h"
#include <cstdlib>
#include <iostream>
using namespace BZROpenShim::SocketTunnel;
void Check(bool ok) { if (!ok) { std::cerr << "Steam tunnel policy failure\n"; std::exit(1); } }
int main()
{
    uint64_t id = 0;
    const uint64_t first = 76561198000000000ull;
    Check(ParseSteamId(std::to_string(first), id) && id == first);
    for (const auto* bad : {"", "0", "-1", " 76561198000000000", "76561198000000000 ",
                           "76561198000000000junk", "18446744073709551616", "9999999999999999999999999",
                           "480", "103582791429521412"}) Check(!ParseSteamId(bad, id));
    Check(!IndividualSteamId(first + (1ull << 56)));
    const auto a = SteamCommunityEndpoint(first), b = SteamCommunityEndpoint(first + 1);
    Check(!a.empty() && a != b && SteamCommunityEndpoint(0).empty());
    Check(BZROpenShim::CanonicalCommunityHost(a) == a);
    const unsigned char secret[BZROpenShim::kCommunitySecretBytes] = {1, 2, 3};
    Check(BZROpenShim::DeriveCommunityKey(secret, sizeof(secret), a).size() == 64);
    Check(BZROpenShim::DeriveCommunityKey(secret, sizeof(secret), a) !=
          BZROpenShim::DeriveCommunityKey(secret, sizeof(secret), b));
    SteamIdentityMap map;
    Check(map.Assign(first, "127.0.0.2") == 1);
    Check(map.Assign(first + 1, "127.0.0.2") == 2);
    Check(map.Assign(first, "127.0.0.2") == 1);
    Check(map.Assign(first, "127.0.1.1") == 0);
    const auto saved = map.Save();
    SteamIdentityMap restarted;
    Check(restarted.Load(saved));
    Check(restarted.Assign(first + 1, "127.0.0.2") == 2);
    Check(restarted.Assign(first, "127.0.0.2") == 1);
    for (const auto& bad : {std::string("bad\n"), std::string("BZRSteamPeers1\nnot-id 1\n"),
            saved + std::to_string(first) + " 3\n", saved + std::to_string(first + 2) + " 1\n",
            saved + std::to_string(first + 2) + " 255\n", saved + std::to_string(first + 2) + " -1\n",
            saved + std::to_string(first + 2) + " 3 trailing\n", std::string(16385, 'x')})
    {
        Check(!restarted.Load(bad));
        Check(restarted.Find(first) == 1); // failure never replaces prior state
    }
    for (unsigned i = 2; i < 254; ++i) Check(map.Assign(first + i, "127.0.0.2") == i + 1);
    Check(map.Assign(first + 254, "127.0.0.2") == 0 && map.slots.size() == 254);
    SteamIdentityMap skip;
    Check(skip.Assign(first, "127.0.1.1") == 2);
    std::cout << "SteamID validation, stable restart mapping, corrupt/duplicate state and capacity checks passed\n";
}
