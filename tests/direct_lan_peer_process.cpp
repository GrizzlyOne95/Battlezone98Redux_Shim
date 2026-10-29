// Standalone session-layer qualification client, not a game/server/helper.
// Every process runs the same native Node intended for the eventual adapter.
#include "direct_lan_discovery.h"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <thread>
#ifdef _WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

using namespace BZROpenShim::DirectLan;
namespace
{
    // Reserve a real, unique endpoint for each fixture. No gameplay packets
    // are sent; the eventual adapter must supply the engine's bound socket.
    struct GameplayEndpoint
    {
#ifdef _WIN32
        WSADATA data{};
        bool initialized = WSAStartup(MAKEWORD(2, 2), &data) == 0;
        SOCKET socket = initialized ? ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) : INVALID_SOCKET;
#else
        int socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#endif
        uint16_t port = 0;
        GameplayEndpoint()
        {
            sockaddr_in address{}; address.sin_family = AF_INET; address.sin_addr.s_addr = htonl(0x7F000001);
#ifdef _WIN32
            int size = sizeof(address);
#else
            socklen_t size = sizeof(address);
#endif
            if (!bind(socket, reinterpret_cast<const sockaddr*>(&address), sizeof(address)) &&
                !getsockname(socket, reinterpret_cast<sockaddr*>(&address), &size)) port = ntohs(address.sin_port);
        }
        ~GameplayEndpoint()
        {
#ifdef _WIN32
            if (socket != INVALID_SOCKET) closesocket(socket);
            if (initialized) WSACleanup();
#else
            if (socket >= 0) close(socket);
#endif
        }
    };
}
int main(int argc, char** argv)
{
    bool host = false, depart = false, mismatch = false;
    uint16_t port = 0, discovery = 0; size_t players = 3;
    for (int i = 1; i < argc; ++i)
    {
        const std::string arg = argv[i];
        if (arg == "--host") host = true;
        else if (arg == "--depart") depart = true;
        else if (arg == "--mismatch") mismatch = true;
        else if (arg == "--port" && i + 1 < argc) port = uint16_t(std::strtoul(argv[++i], nullptr, 10));
        else if (arg == "--discover" && i + 1 < argc) discovery = uint16_t(std::strtoul(argv[++i], nullptr, 10));
        else if (arg == "--players" && i + 1 < argc) players = std::strtoul(argv[++i], nullptr, 10);
        else return 2;
    }
    Id local, session;
    if (!RandomId(local) || !RandomId(session) || players < 2 || players > kMaxMembers) return 3;
    Compatibility compatibility; compatibility.gameBuild = "2.2.301"; compatibility.content[0] = mismatch ? 43 : 42;
    GameplayEndpoint gameplay;
    if (!gameplay.port) return 13;
    Node node(local, host ? "Host" : "Guest", compatibility, gameplay.port);
    if (host)
    {
        Config config{compatibility, "Client-owned LAN", "testmap", {1, 2}, uint8_t(players)};
        if (!node.Host(config, session, 0x7F000001) || !node.EnableDiscovery(0)) return 4;
        std::printf("LISTEN %u %u\n", node.ControlPort(), node.DiscoveryPort()); std::fflush(stdout);
    }
    else
    {
        Address target{0x7F000001, port}; Id expected;
        if (discovery)
        {
            Browser browser;
            if (!browser.Start(discovery, {0x7F000001})) return 5;
            while (browser.Searching() && browser.Results().empty())
            { browser.Poll(); std::this_thread::sleep_for(std::chrono::milliseconds(1)); }
            if (browser.Results().empty()) return 6;
            target = browser.Results()[0].control; expected = browser.Results()[0].session;
            std::puts("DISCOVERED"); std::fflush(stdout);
        }
        if (!node.Join(target, expected)) return 7;
    }
    const Time began = Now(); Time runningAt = 0; uint64_t readyRevision = 0;
    bool started = false;
    while (Now() - began < 15000)
    {
        node.Poll(); const auto& view = node.Control().State();
        if (view.phase == Phase::Closed)
        {
            std::printf("CLOSED %s\n", view.reason.c_str()); std::fflush(stdout);
            return (started || (mismatch && view.reason == "Game build or content differs")) ? 0 : 8;
        }
        if (view.phase == Phase::Lobby && view.members.size() == players)
        {
            if (readyRevision != view.revision)
            { if (!node.Control().SetReady(true)) return 9; readyRevision = view.revision; }
            if (host && std::all_of(view.members.begin(), view.members.end(), [](const Member& m) { return m.ready; }))
                if (!node.Control().RequestStart(Now())) return 10;
        }
        for (const auto& event : node.Control().TakeEvents())
        {
            if (event.type == EventType::Prepare)
            {
                // Session-layer barrier qualification only. The game adapter
                // must wait for actual native peer readiness before this call.
                if (!node.Control().Prepared()) return 11;
            }
            if (event.type == EventType::Started)
            {
                started = true; runningAt = Now();
                std::printf("RUNNING %zu\n", event.state.members.size()); std::fflush(stdout);
                if (depart) return 0; // abrupt transport close, without a Leave message
            }
        }
        if (host && started && Now() - runningAt >= 500)
        {
            std::printf("ROSTER %zu\n", view.members.size());
            node.Control().Leave();
            for (int i = 0; i < 100 && node.Connections(); ++i)
            { node.Poll(); std::this_thread::sleep_for(std::chrono::milliseconds(1)); }
            std::puts("HOST_ENDED"); std::fflush(stdout); return 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::fprintf(stderr, "timeout, phase %u, %zu members, transport: %s\n", unsigned(node.Control().State().phase),
        node.Control().State().members.size(), node.Error().c_str());
    return 12;
}
