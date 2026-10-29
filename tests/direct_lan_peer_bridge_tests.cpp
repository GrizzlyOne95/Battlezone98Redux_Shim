#include "direct_lan_redux_peer.h"
#include "test_check.h"
#include <algorithm>
#include <chrono>
#include <cstring>
#include <thread>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

using namespace BZROpenShim::DirectLan;
namespace R = BZROpenShim::DirectLan::Redux;
namespace
{
    Id ID(uint8_t n) { Id id; id.bytes[0] = n; return id; }
    struct Sink
    {
        std::vector<std::vector<uint8_t>> messages;
        std::vector<R::Identity> senders;
        R::PeerBridge* clear = nullptr;
        static void Receive(void* context, void*, const R::Identity& sender, const uint8_t* bytes, uint32_t count)
        {
            auto& self = *static_cast<Sink*>(context);
            self.messages.emplace_back(bytes, bytes + count); self.senders.push_back(sender);
            if (self.clear) { self.clear->Pump(); self.clear->ClearHandlers(); }
        }
    };
    template<class Condition, class Pump> bool Until(Condition condition, Pump pump, Time timeout = 4000)
    {
        const auto began = Now();
        do { pump(); if (condition()) return true; std::this_thread::sleep_for(std::chrono::milliseconds(1)); } while (Now() - began < timeout);
        return false;
    }
    struct Pair
    {
        Mesh a{ID(1)}, b{ID(2)};
        R::Adapter aa{ID(1)}, ba{ID(2)};
        R::PeerBridge ab{aa, a}, bb{ba, b};
        View view;
        R::Identity ai, bi;
        Pair()
        {
            OpenShimTest::Require(a.Open(0x7F000001) && b.Open(0x7F000001), "gameplay mesh sockets");
            view.session = ID(99); view.owner = ID(1); view.phase = Phase::Lobby; view.revision = 1; view.config.capacity = 4;
            view.members = {{ID(1), 0, "A", {0x7F000001, a.Port()}}, {ID(2), 1, "B", {0x7F000001, b.Port()}}};
            CHECK(aa.Apply(view) && ba.Apply(view) && a.Apply(view) && b.Apply(view));
            aa.Local(&ai); ba.Local(&bi);
            OpenShimTest::Require(Until([&] { return a.Ready() && b.Ready(); }, [&] { ab.Pump(); bb.Pump(); }), "direct gameplay peer greeting");
        }
        void Pump() { ab.Pump(); bb.Pump(); }
    };
    void Exchange()
    {
        Pair p; Sink specific, fallback;
        p.bb.SetHandler(0x7A, &Sink::Receive, &specific); p.bb.SetDefaultHandler(&Sink::Receive, &fallback);
        const uint8_t reliable[] = {0x7A, 1, 2, 3}, unreliable[] = {0x23, 9, 8, 7};
        CHECK(p.ab.Send(p.bi, reliable, sizeof(reliable), true));
        CHECK(p.ab.Send(p.bi, unreliable, sizeof(unreliable), false));
        CHECK(Until([&] { return specific.messages.size() == 1 && fallback.messages.size() == 1; }, [&] { p.Pump(); }));
        CHECK(specific.messages[0] == std::vector<uint8_t>(reliable, reliable + sizeof(reliable)));
        CHECK(fallback.messages[0] == std::vector<uint8_t>(unreliable, unreliable + sizeof(unreliable)));
        CHECK(R::Equal(specific.senders[0], p.ai) && R::Equal(fallback.senders[0], p.ai));
        p.bb.RemoveHandler(0x7A, &Sink::Receive, &fallback); // old owner cannot unregister a replacement
        std::vector<uint8_t> maximum(1152, 0x7A); maximum[1] = 0x55;
        CHECK(p.ab.Send(p.bi, maximum.data(), uint32_t(maximum.size()), true));
        CHECK(Until([&] { return specific.messages.size() == 2; }, [&] { p.Pump(); })); CHECK(specific.messages.back() == maximum);
        maximum.push_back(0); CHECK(!p.ab.Send(p.bi, maximum.data(), uint32_t(maximum.size()), true));
        CHECK(!p.ab.Send(p.bi, nullptr, 1, true) && !p.ab.Send(p.bi, reliable, 0, true));
        CHECK(!p.ab.Send({}, reliable, sizeof(reliable), true));
        CHECK(!p.ab.Send(p.ai, reliable, sizeof(reliable), true));
        // Stock's ping request gets a reliable pong and still reaches handler 0.
        Sink ping, pong; p.bb.SetHandler(0, &Sink::Receive, &ping); p.ab.SetHandler(0, &Sink::Receive, &pong);
        const uint8_t request[] = {0, 0}; CHECK(p.ab.Send(p.bi, request, 2, true));
        CHECK(Until([&] { return ping.messages.size() == 1 && pong.messages.size() == 1; }, [&] { p.Pump(); }));
        CHECK(pong.messages[0] == std::vector<uint8_t>({0, 1}));
        // One-byte kind 0 is safe and is not mistaken for a two-byte ping.
        CHECK(p.ab.Send(p.bi, request, 1, true));
        CHECK(Until([&] { return ping.messages.size() == 2; }, [&] { p.Pump(); }));
        CHECK(pong.messages.size() == 1);
    }
    void BackpressureAndReentrancy()
    {
        Pair p; Sink received;
        p.bb.SetHandler(0x7A, &Sink::Receive, &received);
        std::vector<uint8_t> bytes(1152, 0x7A); size_t accepted = 0;
        while (accepted < 500 && p.ab.Send(p.bi, bytes.data(), uint32_t(bytes.size()), true)) ++accepted;
        CHECK(accepted > 1 && accepted < 500);
        CHECK(Until([&] { return received.messages.size() == accepted; }, [&] { p.Pump(); }));
        CHECK(std::all_of(received.messages.begin(), received.messages.end(), [&](const auto& m) { return m == bytes; }));
        received.messages.clear(); received.clear = &p.bb;
        CHECK(p.ab.Send(p.bi, bytes.data(), 3, true)); CHECK(p.ab.Send(p.bi, bytes.data(), 3, true));
        CHECK(Until([&] { return !received.messages.empty(); }, [&] { p.Pump(); }));
        for (int i = 0; i < 10; ++i) p.Pump();
        CHECK(received.messages.size() == 1); // handler cleared during callback, reentrant Pump ignored
        p.b.Close();
        CHECK(Until([&] { return !p.a.Ready(); }, [&] { p.a.Poll(); }));
        CHECK(!p.ab.Send(p.bi, bytes.data(), 3, true));
        CHECK(p.a.Apply(p.view));
        for (int i = 0; i < 10; ++i) p.a.Poll();
        CHECK(!p.a.Ready()); // no silent reconnect of a broken reliable stream
    }
    void Membership()
    {
        Pair p; Mesh c(ID(3)); CHECK(c.Open(0x7F000001));
        auto view = p.view; view.members.push_back({ID(3), 2, "C", {0x7F000001, c.Port()}}); ++view.revision;
        CHECK(p.a.Apply(view) && p.b.Apply(view) && c.Apply(view));
        CHECK(Until([&] { return p.a.Ready() && p.b.Ready() && c.Ready(); }, [&] { p.a.Poll(); p.b.Poll(); c.Poll(); }));
        // Remove A: B and C retain their direct link independently of A's sockets.
        view.members.erase(view.members.begin()); view.owner = ID(2); view.members[0].slot = 0; ++view.revision;
        CHECK(p.b.Apply(view) && c.Apply(view)); p.a.Close();
        const uint8_t bytes[] = {0x23, 42}; CHECK(p.b.Send(ID(3), bytes, sizeof(bytes), true));
        std::vector<PeerPacket> received;
        CHECK(Until([&] { auto packets = c.TakeReceived(); received.insert(received.end(), packets.begin(), packets.end()); return !received.empty(); },
            [&] { p.b.Poll(); c.Poll(); }));
        CHECK(received.size() == 1 && received[0].sender == ID(2) && received[0].reliable);
        CHECK(received[0].bytes == std::vector<uint8_t>({0x23, 42}));
        // This is transport independence, not implemented session host migration.
        Mesh conflict(ID(4)); CHECK(!conflict.Open(0x7F000001, p.b.Port()));
        Mesh invalid(ID(5)); CHECK(!invalid.Open(0x08080808));
    }
    void RejectForeignUdp()
    {
        Pair p; Sink sink; p.bb.SetDefaultHandler(&Sink::Receive, &sink);
        auto socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        sockaddr_in target{}; target.sin_family = AF_INET; target.sin_addr.s_addr = htonl(0x7F000001); target.sin_port = htons(p.b.Port());
        std::vector<uint8_t> bytes;
        Packet packet{Type::Ready, p.view.session, ID(1), 999999, {0x23, 42}};
        CHECK(Encode(packet, bytes, kPeerFrameMagic));
        // Correct session and a real member ID, but an unadvertised UDP
        // source port. It must not reach the native callback or consume the
        // real peer's sequence window.
        CHECK(sendto(socket, reinterpret_cast<const char*>(bytes.data()), int(bytes.size()), 0,
            reinterpret_cast<const sockaddr*>(&target), sizeof(target)) == int(bytes.size()));
        for (int i = 0; i < 20; ++i) { p.Pump(); std::this_thread::sleep_for(std::chrono::milliseconds(1)); }
        CHECK(sink.messages.empty());
        const uint8_t valid[] = {0x23, 7}; CHECK(p.ab.Send(p.bi, valid, sizeof(valid), false));
        CHECK(Until([&] { return sink.messages.size() == 1; }, [&] { p.Pump(); }));
#ifdef _WIN32
        closesocket(socket);
#else
        close(socket);
#endif
    }
#if defined(_MSC_VER) && defined(_M_IX86)
    struct NativeSink
    {
        uintptr_t* table;
        Sink sink;
        static void __fastcall Receive(NativeSink* self, void*, void* peer, const R::Identity* sender, const uint8_t* bytes, uint32_t count)
        { Sink::Receive(&self->sink, peer, *sender, bytes, count); }
    };
    void NativeAbi()
    {
        Pair p;
        uintptr_t table[] = {0, reinterpret_cast<uintptr_t>(&NativeSink::Receive)};
        NativeSink sink{table, {}}; p.bb.SetNativeHandler(0x7A, &sink);
        void* object = p.ab.QualificationObject(); const auto vtable = *static_cast<uintptr_t**>(object);
        using Send = bool(__thiscall*)(void*, const R::Identity*, const void*, uint32_t, int);
        using Pump = void(__thiscall*)(void*);
        const auto send = reinterpret_cast<Send>(vtable[3]); const auto pump = reinterpret_cast<Pump>(vtable[2]);
        uintptr_t before = 0, after = 0;
        for (int i = 0; i < 10000; ++i)
        {
            __asm mov before, esp
            CHECK(!send(object, &p.bi, nullptr, 0, 1)); pump(object);
            __asm mov after, esp
            CHECK(before == after);
        }
        const uint8_t bytes[] = {0x7A, 1, 2};
        CHECK(send(object, &p.bi, bytes, sizeof(bytes), 1));
        CHECK(Until([&] { return sink.sink.messages.size() == 1; }, [&] { p.Pump(); }));
        CHECK(R::Equal(sink.sink.senders[0], p.ai));
        p.bb.RemoveNativeHandler(0x7A, object); // wrong owner leaves the registration intact
        CHECK(send(object, &p.bi, bytes, sizeof(bytes), 1));
        CHECK(Until([&] { return sink.sink.messages.size() == 2; }, [&] { p.Pump(); }));
        CHECK(send(object, &p.bi, bytes, sizeof(bytes), 9)); // stock treats every nonzero value as reliable
        CHECK(Until([&] { return sink.sink.messages.size() == 3; }, [&] { p.Pump(); }));
        p.bb.RemoveNativeHandler(0x7A, &sink);
        CHECK(send(object, &p.bi, bytes, sizeof(bytes), 1));
        for (int i = 0; i < 20; ++i) { p.Pump(); std::this_thread::sleep_for(std::chrono::milliseconds(1)); }
        CHECK(sink.sink.messages.size() == 3);
        using Destroy = void*(__thiscall*)(void*, uint32_t);
        CHECK(reinterpret_cast<Destroy>(vtable[0])(object, 1) == object);
        CHECK(!send(object, &p.bi, bytes, sizeof(bytes), 1));
    }
#endif
}
int main()
{
    Exchange(); BackpressureAndReentrancy(); Membership(); RejectForeignUdp();
#if defined(_MSC_VER) && defined(_M_IX86)
    NativeAbi();
#endif
    std::printf("direct_lan_peer_bridge_tests: %d checks\n", OpenShimTest::CheckCount());
    return OpenShimTest::ExitCode();
}
