// Standalone session-layer qualification client, not a game/server/helper.
// Every process runs the same native Node intended for the eventual adapter.
#include "direct_lan_discovery.h"
#include "direct_lan_redux_peer.h"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <thread>

using namespace BZROpenShim::DirectLan;
namespace
{
    struct Received
    {
        Redux::Adapter& adapter;
        Id local;
        std::vector<std::pair<Id, uint8_t>> messages;
        bool invalid = false;
        static void Packet(void* context, void*, const Redux::Identity& from, const uint8_t* bytes, uint32_t count)
        {
            auto& self = *static_cast<Received*>(context); const auto sender = self.adapter.Find(from);
            if (!sender || count != 33 || (bytes[0] != 0x7A && bytes[0] != 0x23) ||
                std::memcmp(bytes + 1, sender->local.bytes.data(), 16) || std::memcmp(bytes + 17, self.local.bytes.data(), 16))
            { self.invalid = true; return; }
            const auto key = std::make_pair(sender->local, bytes[0]);
            if (std::find(self.messages.begin(), self.messages.end(), key) == self.messages.end()) self.messages.push_back(key);
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
    Mesh mesh(local);
    if (!mesh.Open(0x7F000001)) { std::fprintf(stderr, "mesh open: %s\n", mesh.Error().c_str()); return 13; }
    Node node(local, host ? "Host" : "Guest", compatibility, mesh.Port());
    Redux::Adapter adapter(local);
    Redux::PeerBridge bridge(adapter, mesh);
    Received received{adapter, local, {}, false};
    bridge.SetHandler(0x7A, &Received::Packet, &received); bridge.SetHandler(0x23, &Received::Packet, &received);
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
    const Time began = Now(); Time runningAt = 0, lastUdp = 0; uint64_t readyRevision = 0, sentLaunch = 0, observedLaunch = 0;
    bool started = false, prepared = false;
    // Hostile-input qualification intentionally spends five seconds on a
    // stalled greeting before the real guest starts. Keep the overall
    // fixture budget separate from the production connection deadlines.
    while (Now() - began < 30000)
    {
        node.Poll(); const auto& view = node.Control().State();
        if ((view.phase == Phase::Lobby || view.phase == Phase::Preparing || view.phase == Phase::Running || view.phase == Phase::Closed) &&
            (!adapter.Apply(view) || !mesh.Apply(view)))
        { std::fprintf(stderr, "adapter projection failed: %s; mesh: %s\n", adapter.Error().c_str(), mesh.Error().c_str()); return 14; }
        if (view.phase == Phase::Closed)
        {
            std::printf("CLOSED %s\n", view.reason.c_str()); std::fflush(stdout);
            return (started || (mismatch && view.reason == "Game build or content differs")) ? 0 : 8;
        }
        if (view.phase == Phase::Preparing && observedLaunch != view.launch)
        { observedLaunch = view.launch; received.messages.clear(); prepared = false; }
        bridge.Pump();
        if (received.invalid) return 16;
        if (view.phase == Phase::Lobby && view.members.size() == players && mesh.Ready())
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
                if (!adapter.HasLobby() || adapter.Members() != view.members.size()) return 15;
            }
            if (event.type == EventType::Started)
            {
                started = true; runningAt = Now();
                std::printf("RUNNING %zu\n", event.state.members.size()); std::fflush(stdout);
                Redux::Identity mine, owner;
                const auto lobby = adapter.Lobby();
                adapter.Local(&mine); adapter.Owner(&owner, lobby);
                std::printf("NATIVE %u:%u %u:%u %u:%u\n", lobby.word12, lobby.word8,
                    owner.word12, owner.word8, mine.word12, mine.word8); std::fflush(stdout);
                if (depart) return 0; // abrupt transport close, without a Leave message
            }
        }
        if (view.phase == Phase::Preparing && mesh.Ready())
        {
            const bool reliable = sentLaunch != view.launch;
            const bool unreliable = Now() - lastUdp >= 100;
            if (reliable || unreliable)
            {
                for (int32_t i = 0; size_t(i) < adapter.Members(); ++i)
                {
                    Redux::Identity target; adapter.Member(&target, adapter.Lobby(), i);
                    const auto peer = adapter.Find(target); if (!peer || peer->local == local) continue;
                    uint8_t bytes[33]{}; std::memcpy(bytes + 1, local.bytes.data(), 16); std::memcpy(bytes + 17, peer->local.bytes.data(), 16);
                    if (reliable) { bytes[0] = 0x7A; if (!bridge.Send(target, bytes, sizeof(bytes), true)) return 17; }
                    if (unreliable) { bytes[0] = 0x23; if (!bridge.Send(target, bytes, sizeof(bytes), false)) return 18; }
                }
                if (reliable) sentLaunch = view.launch;
                if (unreliable) lastUdp = Now();
            }
            if (!prepared && received.messages.size() == 2 * (players - 1))
            {
                // Every direct TCP/UDP peer path exchanged payloads through
                // the adapter. Native game/player readiness is still pending.
                std::printf("P2P %zu\n", received.messages.size()); std::fflush(stdout);
                if (!node.Control().Prepared()) return 11;
                prepared = true;
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
    std::fprintf(stderr, "timeout, phase %u, %zu members, transport: %s; mesh ready=%u, mesh: %s\n", unsigned(node.Control().State().phase),
        node.Control().State().members.size(), node.Error().c_str(), unsigned(mesh.Ready()), mesh.Error().c_str());
    return 12;
}
