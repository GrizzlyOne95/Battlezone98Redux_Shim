#include "lan_discovery.h"
#ifndef _WIN32
// Inspect screen identifiers without importing a Windows compiler keyword.
#define __cdecl
#endif
#include "shell_screens.h"
#include "menu_theme.h"
#include "test_check.h"

using namespace BZROpenShim::LanDiscovery;
int main()
{
    CHECK(BZROpenShim::ShellScreens::kLanScreenId != BZROpenShim::MenuTheme::ScreenId);
    CHECK(BZROpenShim::ShellScreens::kLanScreenId < BZROpenShim::ShellScreens::kOptionsCategoryScreenIdBase);
    const Nonce nonce{0, 1, 2, 3, 4, 5, 6, 255};
    const auto query = MakeQuery(nonce);
    CHECK(query.size() == 96);
    CHECK(std::memcmp(query.data(), "BZRLAN1?", 8) == 0);
    for (size_t i = 16; i < query.size(); ++i) CHECK(query[i] == 0);
    std::string packet("BZRLAN1!");
    packet.append(reinterpret_cast<const char*>(nonce.data()), nonce.size());
    packet += char(1337 >> 8); packet += char(1337 & 255);
    packet += "Host PC";
    Reply out;
    CHECK(ParseReply(packet, nonce, out) && out.port == 1337 && out.name == "Host PC");
    CHECK(Endpoint("192.168.1.7", out.port) == "192.168.1.7");
    CHECK(Endpoint("10.0.0.1", 1437) == "10.0.0.1:1437");
    // Wrong request/version/nonce, truncation, terminal controls, oversized
    // labels and invalid probe-overflow ports must never become join targets.
    for (size_t i = 0; i < packet.size(); ++i)
        if (i < 19) CHECK(!ParseReply(std::string_view(packet).substr(0, i), nonce, out));
    auto bad = packet; bad[0] = 'x'; CHECK(!ParseReply(bad, nonce, out));
    bad = packet; bad[9] ^= 1; CHECK(!ParseReply(bad, nonce, out));
    bad = packet; bad[18] = '\n'; CHECK(!ParseReply(bad, nonce, out));
    bad = packet; bad[18] = char(-1); CHECK(!ParseReply(bad, nonce, out));
    bad = packet.substr(0, 18) + std::string(65, 'a'); CHECK(!ParseReply(bad, nonce, out));
    bad.pop_back(); CHECK(ParseReply(bad, nonce, out));
    bad[16] = 0; bad[17] = 0; CHECK(!ParseReply(bad, nonce, out));
    bad[16] = char(-1); bad[17] = char(-1); CHECK(!ParseReply(bad, nonce, out));
    CHECK(out.port == 0 && out.name.empty());
    CHECK(IsLocalIPv4(0x0A000001)); CHECK(IsLocalIPv4(0xAC100001));
    CHECK(IsLocalIPv4(0xAC1FFFFE)); CHECK(IsLocalIPv4(0xC0A80101));
    CHECK(IsLocalIPv4(0x7F000001)); CHECK(IsLocalIPv4(0xA9FE0101));
    CHECK(!IsLocalIPv4(0xAC200001)); CHECK(!IsLocalIPv4(0x08080808));
    CHECK(!IsLocalIPv4(0xFFFFFFFF)); CHECK(!IsLocalIPv4(0));
    return OpenShimTest::ExitCode();
}
