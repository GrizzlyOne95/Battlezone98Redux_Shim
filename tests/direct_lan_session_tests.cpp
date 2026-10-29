#include "direct_lan_session.h"
#include "test_check.h"
#include <algorithm>
#include <cstring>

using namespace BZROpenShim::DirectLan;
namespace
{
    Id ID(uint8_t byte) { Id id; id.bytes.back() = byte; return id; }
    Compatibility Compatible() { Compatibility c; c.gameBuild = "2.2.301"; c.content[0] = 42; return c; }
    Config Configuration() { return {Compatible(), "LAN game", "testmap", {1, 2, 3}, 4}; }
    Packet RoundTrip(const Packet& packet)
    {
        std::vector<uint8_t> bytes; CHECK(Encode(packet, bytes));
        Decoder decoder; std::vector<Packet> result;
        for (auto byte : bytes) CHECK(decoder.Feed(&byte, 1, result));
        OpenShimTest::Require(result.size() == 1, "one decoded frame");
        return result[0];
    }
    struct Trio
    {
        Session host{ID(1), "Host", Compatible(), 21000};
        Session a{ID(2), "Guest A", Compatible(), 21001};
        Session b{ID(3), "Guest B", Compatible(), 21002};
        Time now = 100;
        Trio()
        {
            CHECK(host.Host(Configuration(), ID(99), 0x7F000001, now));
            CHECK(a.Join(1, ID(99), now)); CHECK(b.Join(1, ID(99), now)); Pump();
        }
        void Pump()
        {
            for (int round = 0; round < 20; ++round)
            {
                bool sent = false;
                for (auto item : host.TakeOutbound())
                { (item.connection == 11 ? a : b).Receive(1, 0x7F000001, RoundTrip(item.packet), now); sent = true; }
                for (auto item : a.TakeOutbound())
                { host.Receive(11, 0x7F000001, RoundTrip(item.packet), now); sent = true; }
                for (auto item : b.TakeOutbound())
                { host.Receive(12, 0x7F000001, RoundTrip(item.packet), now); sent = true; }
                if (!sent) return;
            }
            CHECK(false);
        }
        void Ready()
        { CHECK(host.SetReady(true)); CHECK(a.SetReady(true)); CHECK(b.SetReady(true)); Pump(); }
        void Start()
        { Ready(); CHECK(host.RequestStart(now)); Pump(); CHECK(host.Prepared()); CHECK(a.Prepared()); CHECK(b.Prepared()); Pump(); }
    };
    void Wire()
    {
        Packet packet{Type::Hello, {}, ID(1), 1, {0, 1, 2, 0, 255}};
        CHECK(RoundTrip(packet).payload == packet.payload);
        std::vector<uint8_t> frame; CHECK(Encode(packet, frame));
        for (size_t split = 0; split <= frame.size(); ++split)
        {
            Decoder decoder; std::vector<Packet> out;
            CHECK(decoder.Feed(frame.data(), split, out));
            CHECK(decoder.Feed(frame.data() + split, frame.size() - split, out));
            CHECK(out.size() == 1 && out[0].sender == ID(1));
        }
        auto both = frame; both.insert(both.end(), frame.begin(), frame.end());
        Decoder decoder; std::vector<Packet> out; CHECK(decoder.Feed(both.data(), both.size(), out)); CHECK(out.size() == 2);
        for (size_t badOffset : {size_t(4), size_t(12), size_t(13)})
        {
            auto bad = frame; bad[badOffset] = 255;
            Decoder reject; std::vector<Packet> empty;
            CHECK(!reject.Feed(bad.data(), bad.size(), empty) && reject.Failed());
            CHECK(!reject.Feed(frame.data(), frame.size(), empty));
        }
        for (const std::vector<uint8_t>& bad : {std::vector<uint8_t>{0, 0, 0, 0}, {0, 0, 16, 1}})
        { Decoder reject; std::vector<Packet> empty; CHECK(!reject.Feed(bad.data(), bad.size(), empty)); }
        packet.payload.resize(kMaxFrame); CHECK(!Encode(packet, frame));
        packet.payload.clear(); packet.sender = {}; CHECK(!Encode(packet, frame));
        packet.sender = ID(1); packet.serial = 0; CHECK(!Encode(packet, frame));
    }
    void Lifecycle()
    {
        Trio t;
        CHECK(t.host.State().members.size() == 3 && t.a.State().members.size() == 3 && t.b.State().members.size() == 3);
        CHECK(t.a.State().members[1].endpoint.ipv4 == 0x7F000001);
        CHECK(!t.host.RequestStart(t.now));
        t.Ready(); CHECK(t.host.RequestStart(t.now)); t.Pump();
        CHECK(t.host.State().phase == Phase::Preparing && t.a.State().phase == Phase::Preparing);
        CHECK(t.host.Prepared()); CHECK(t.a.Prepared()); t.Pump();
        CHECK(t.host.State().phase == Phase::Preparing); // no launch before every native adapter is ready
        CHECK(t.b.Prepared()); t.Pump();
        CHECK(t.host.State().phase == Phase::Running && t.a.State().phase == Phase::Running && t.b.State().phase == Phase::Running);
        CHECK(!t.host.SetConfig(Configuration()) && !t.a.SetReady(false));
        t.a.Leave(); t.Pump();
        CHECK(t.host.State().members.size() == 2 && t.b.State().members.size() == 2);
        const auto events = t.b.TakeEvents();
        const auto started = std::find_if(events.begin(), events.end(), [](const Event& e) { return e.type == EventType::Started; });
        CHECK(started != events.end() && started->state.phase == Phase::Running && started->state.members.size() == 3);
        t.host.Leave(); t.Pump(); CHECK(t.b.State().phase == Phase::Closed);
    }
    void Invalidation()
    {
        Trio t; t.Ready();
        CHECK(t.a.SetReady(true)); const auto stale = t.a.TakeOutbound();
        const auto previous = t.host.State().revision;
        auto config = Configuration(); config.settings = {4, 5}; CHECK(t.host.SetConfig(config));
        for (const auto& item : stale) t.host.Receive(11, 0x7F000001, item.packet, t.now);
        t.Pump();
        CHECK(t.host.State().revision > previous);
        CHECK(std::none_of(t.host.State().members.begin(), t.host.State().members.end(), [](const Member& m) { return m.ready; }));
        CHECK(!t.host.RequestStart(t.now));
        t.Ready(); CHECK(t.host.RequestStart(t.now)); t.Pump();
        CHECK(t.a.Prepared()); auto oldAck = t.a.TakeOutbound();
        t.host.Disconnected(12); t.Pump();
        CHECK(t.host.State().phase == Phase::Lobby && t.a.State().phase == Phase::Lobby);
        for (const auto& item : oldAck) t.host.Receive(11, 0x7F000001, item.packet, t.now);
        CHECK(t.host.State().phase == Phase::Lobby && !t.host.State().members[1].prepared);
    }
    void Rejection()
    {
        auto reject = [](Id peer, Compatibility compatibility, Id session, bool running, uint32_t ip)
        {
            Trio t; if (running) t.Start();
            Session extra(peer, "Extra", compatibility, 20000); CHECK(extra.Join(1, session, t.now));
            for (auto item : extra.TakeOutbound()) t.host.Receive(20, ip, item.packet, t.now);
            for (auto item : t.host.TakeOutbound()) if (item.connection == 20) extra.Receive(1, ip, item.packet, t.now);
            CHECK(extra.State().phase == Phase::Closed && !extra.State().reason.empty());
            CHECK(t.host.State().members.size() == 3);
        };
        reject(ID(1), Compatible(), ID(99), false, 0x7F000001);
        reject(ID(2), Compatible(), ID(99), false, 0x7F000001);
        auto incompatible = Compatible(); incompatible.content[1] = 1;
        reject(ID(4), incompatible, ID(99), false, 0x7F000001);
        reject(ID(4), Compatible(), ID(90), false, 0x7F000001);
        reject(ID(4), Compatible(), ID(99), true, 0x7F000001);
        reject(ID(4), Compatible(), ID(99), false, 0x08080808);
        Trio full; auto config = Configuration(); config.capacity = 3; CHECK(full.host.SetConfig(config)); full.Pump();
        Session extra(ID(4), "Extra", Compatible(), 20000); CHECK(extra.Join(1, {}, full.now));
        for (auto item : extra.TakeOutbound()) full.host.Receive(20, 0x7F000001, item.packet, full.now);
        for (auto item : full.host.TakeOutbound()) if (item.connection == 20) extra.Receive(1, 0x7F000001, item.packet, full.now);
        CHECK(extra.State().phase == Phase::Closed && extra.State().reason == "Session is full");
        Trio collision;
        Session sameEndpoint(ID(4), "Endpoint collision", Compatible(), 21000);
        CHECK(sameEndpoint.Join(1, {}, collision.now));
        for (const auto& item : sameEndpoint.TakeOutbound()) collision.host.Receive(20, 0x7F000001, item.packet, collision.now);
        for (const auto& item : collision.host.TakeOutbound()) if (item.connection == 20) sameEndpoint.Receive(1, 0x7F000001, item.packet, collision.now);
        CHECK(sameEndpoint.State().phase == Phase::Closed && sameEndpoint.State().reason == "Gameplay endpoint already in use");
    }
    void TimeoutsAndForgery()
    {
        Trio t;
        CHECK(t.a.SetReady(true)); auto ready = t.a.TakeOutbound();
        auto forged = ready[0].packet; forged.sender = ID(3);
        t.host.Receive(11, 0x7F000001, forged, t.now);
        CHECK(!t.host.State().members[1].ready);
        t.host.Receive(11, 0x7F000001, ready[0].packet, t.now);
        CHECK(t.host.State().members[1].ready);
        CHECK(t.a.SetReady(false)); auto later = t.a.TakeOutbound();
        t.host.Receive(11, 0x7F000001, later[0].packet, t.now);
        t.host.Receive(11, 0x7F000001, ready[0].packet, t.now); // stale control state
        CHECK(!t.host.State().members[1].ready);
        t.a.Tick(t.now + 5001); CHECK(t.a.State().phase == Phase::Closed);
        t.host.Tick(t.now + 5001); CHECK(t.host.State().members.size() == 1);
        Session invalid({}, "No identity", Compatible(), 1); CHECK(!invalid.Host(Configuration(), ID(99), 0x7F000001, 0));
        auto unknown = Compatible(); unknown.content.fill(0);
        Session noHash(ID(4), "No content hash", unknown, 1); CHECK(!noHash.Join(1, {}, 0));
    }
}
int main()
{
    Wire(); Lifecycle(); Invalidation(); Rejection(); TimeoutsAndForgery();
    std::printf("direct_lan_session_tests: %d checks\n", OpenShimTest::CheckCount());
    return OpenShimTest::ExitCode();
}
