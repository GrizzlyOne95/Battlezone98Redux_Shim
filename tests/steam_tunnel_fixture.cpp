// Test-only replacement for SteamTransport. Exercises the REAL tunnel runtime
// with an ordered message service, Busy sends, disconnects and reconnects.
// No Steam DLL, authentication or SDR is simulated as acceptance evidence.
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include "steam_tunnel_transport.h"
#include "socket_tunnel_protocol.h"
#include <array>
#include <deque>
#include <filesystem>
#include <mutex>
#include <thread>
#include <utility>
#include <cstdio>
#include <stdexcept>

namespace BZROpenShim::SocketTunnel
{
namespace { std::mutex mutex; constexpr uint64_t kHost = 76561198000000001ull, kClient = 76561198000000002ull; }
struct SteamTransport::Impl
{
    bool bridge = false;
    uint32_t connection = 0;
    unsigned calls = 0;
    std::string control;
    bool disconnected = false, corrupt = false;
    std::deque<std::pair<std::vector<uint8_t>, bool>> incoming;
    std::vector<SteamEvent> events;
    static Impl* ends[2];
    static uint32_t generation;
    void Join()
    {
        if (!ends[0] || !ends[1] || ends[0]->connection || ends[1]->connection) return;
        ++generation;
        for (unsigned i = 0; i < 2; ++i)
        {
            ends[i]->connection = generation;
            ends[i]->events.push_back({generation, i ? kClient : kHost, true});
        }
    }
};
SteamTransport::Impl* SteamTransport::Impl::ends[2]{};
uint32_t SteamTransport::Impl::generation = 0;
SteamTransport::SteamTransport() : impl(new Impl) {}
SteamTransport::~SteamTransport()
{
    Close(impl->connection);
    std::lock_guard<std::mutex> lock(mutex);
    if (Impl::ends[impl->bridge] == impl.get()) Impl::ends[impl->bridge] = nullptr;
}
void SteamTransport::Start(const Config& cfg, std::atomic<bool>&, Logger)
{
    std::lock_guard<std::mutex> lock(mutex);
    impl->bridge = cfg.bridge;
    if (cfg.bridge) impl->control = cfg.identityMap;
    if (Impl::ends[cfg.bridge]) throw std::runtime_error("duplicate fixture side");
    Impl::ends[cfg.bridge] = impl.get(); impl->Join();
}
std::vector<SteamEvent> SteamTransport::Poll(uint64_t)
{
    if (impl->bridge && !impl->disconnected && std::filesystem::exists(impl->control + ".disconnect"))
    { impl->disconnected = true; Close(impl->connection); }
    std::lock_guard<std::mutex> lock(mutex);
    impl->Join(); return std::exchange(impl->events, {});
}
SteamSend SteamTransport::Send(uint32_t connection, const std::vector<uint8_t>& bytes, bool reliable)
{
    std::lock_guard<std::mutex> lock(mutex);
    auto other = Impl::ends[!impl->bridge];
    if (!connection || impl->connection != connection || !other) return SteamSend::Failed;
    Frame f;
    if (!Decode(bytes.data(), bytes.size(), f) || reliable != (Reliable(f.kind) || f.kind == Kind::Hello || f.kind == Kind::Welcome))
        throw std::runtime_error("runtime chose wrong native reliability");
    if (f.kind == Kind::Ack) throw std::runtime_error("native path sent UDP ACK");
    // Every fifth stream submission stalls once; no retransmission is needed
    // after success, and the byte-exact echo catches duplicate submissions.
    if (Reliable(f.kind) && (++impl->calls % 5) == 0) return SteamSend::Busy;
    if (other->incoming.size() >= 128) return SteamSend::Busy;
    other->incoming.emplace_back(bytes, reliable); return SteamSend::Sent;
}
int SteamTransport::Receive(uint32_t connection, std::vector<uint8_t>& bytes, bool& reliable)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (impl->connection != connection) return -1;
    if (impl->incoming.empty()) return 0;
    auto packet = std::move(impl->incoming.front()); impl->incoming.pop_front();
    bytes = std::move(packet.first); reliable = packet.second;
    auto host = Impl::ends[1];
    if (!impl->bridge && host && !host->corrupt && bytes[4] == uint8_t(Kind::Data) &&
        std::filesystem::exists(host->control + ".bad-reliability"))
    { host->corrupt = true; reliable = false; }
    return 1;
}
void SteamTransport::Close(uint32_t connection)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (!connection || connection != impl->connection) return;
    for (unsigned i = 0; i < 2; ++i)
        if (auto end = Impl::ends[i])
        { end->connection = 0; end->incoming.clear(); end->events.push_back({connection, i ? kClient : kHost, false}); }
}
int SteamTransport::SelfTest() { return 2; }
}

static void Log(const char* text) { std::printf("%s\n", text); std::fflush(stdout); }
int main(int argc, char** argv)
{
    using namespace BZROpenShim::SocketTunnel;
    if (argc != 3) return 2;
    Config bridge; bridge.steam = bridge.bridge = true; bridge.identityMap = argv[1];
    Config agent; agent.steam = true; agent.steamHost = kHost;
    std::atomic<bool> stop{false}; std::atomic<int> bridgeReady{0}, agentReady{0};
    int bridgeResult = 0, agentResult = 0;
    std::thread host([&] { bridgeResult = Run(bridge, stop, bridgeReady, Log); });
    std::thread client([&] { agentResult = Run(agent, stop, agentReady, Log); });
    const auto deadline = GetTickCount64() + 30000;
    while (GetTickCount64() < deadline && bridgeReady >= 0 && agentReady >= 0 && !std::filesystem::exists(argv[2])) Sleep(10);
    stop = true; host.join(); client.join(); return bridgeResult || agentResult ? 2 : 0;
}
