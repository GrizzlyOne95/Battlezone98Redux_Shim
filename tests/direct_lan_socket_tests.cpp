#include "direct_lan_transport.h"
#include "direct_lan_discovery.h"
#include "test_check.h"
#include <chrono>
#include <thread>

using namespace BZROpenShim::DirectLan;
namespace
{
    Compatibility Compatible() { Compatibility c; c.gameBuild = "2.2.301"; c.content[0] = 42; return c; }
    Config Configuration() { return {Compatible(), "Direct LAN socket test", "testmap", {1}, 4}; }
    Id Random() { Id id; OpenShimTest::Require(RandomId(id), "random local id"); return id; }
    template<class Condition> bool Until(Node& host, Node& a, Node& b, Condition condition, Time timeout = 3000)
    {
        const Time since = Now();
        do
        {
            host.Poll(); a.Poll(); b.Poll();
            if (condition()) return true;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        } while (Now() - since < timeout);
        return false;
    }
}
int main()
{
    uint32_t ip = 0;
    CHECK(ParseIPv4("127.0.0.1", ip) && ip == 0x7F000001);
    CHECK(FormatIPv4(ip) == "127.0.0.1");
    for (const auto text : {"127.1", "example.com", "127.0.0.256", "127.0.0.1:1", "-1.0.0.1", ".1.1.1", "127.0.0.1."})
        CHECK(!ParseIPv4(text, ip));
    const Id session = Random();
    Node host(Random(), "Host", Compatible(), 21000);
    Node a(Random(), "Guest A", Compatible(), 21001);
    Node b(Random(), "Guest B", Compatible(), 21002);
    OpenShimTest::Require(host.Host(Configuration(), session, 0x7F000001), "host listen socket");
    CHECK(host.ControlPort() != 0);
    CHECK(host.EnableDiscovery(0));
    Browser browser; CHECK(browser.Start(host.DiscoveryPort(), {0x7F000001}));
    CHECK(Until(host, a, b, [&] { browser.Poll(); return !browser.Results().empty(); }));
    CHECK(browser.Results().size() == 1 && browser.Results()[0].session == session &&
        browser.Results()[0].control.port == host.ControlPort());
#ifndef _WIN32
    // A unicast UDP bind passes the test above but misses LAN broadcasts.
    Browser broadcast; CHECK(broadcast.Start(host.DiscoveryPort(), {0x7FFFFFFF}));
    CHECK(Until(host, a, b, [&] { broadcast.Poll(); return !broadcast.Results().empty(); }));
#endif
    const auto query = DiscoveryQuery(session);
    std::vector<uint8_t> response;
    CHECK(DiscoveryReply(query, host.Control().State(), host.ControlPort(), response));
    CHECK(response.size() < query.size());
    Advertisement advertised;
    CHECK(ReadAdvertisement(response.data(), response.size(), session, 0x7F000001, advertised));
    for (size_t size = 0; size < response.size(); ++size)
        CHECK(!ReadAdvertisement(response.data(), size, session, 0x7F000001, advertised));
    auto wrong = session; wrong.bytes[0] ^= 1;
    CHECK(!ReadAdvertisement(response.data(), response.size(), wrong, 0x7F000001, advertised));
    CHECK(!ReadAdvertisement(response.data(), response.size(), session, 0x08080808, advertised));
    auto invalid = query; invalid.back() = 1;
    CHECK(!DiscoveryReply(invalid, host.Control().State(), host.ControlPort(), response));
    Node conflict(Random(), "Conflict", Compatible(), 21003);
    CHECK(!conflict.Host(Configuration(), Random(), 0x7F000001, host.ControlPort()));
    CHECK(host.Control().State().phase == Phase::Lobby);
    CHECK(a.Join({0x7F000001, host.ControlPort()}, session));
    CHECK(b.Join({0x7F000001, host.ControlPort()})); // manual IP join has no advertisement token
    OpenShimTest::Require(Until(host, a, b, [&] { return a.Control().State().members.size() == 3 && b.Control().State().members.size() == 3; }), "three connected clients");
    CHECK(a.Control().State().owner == host.Control().LocalId());
    CHECK(host.Control().SetReady(true)); CHECK(a.Control().SetReady(true)); CHECK(b.Control().SetReady(true));
    OpenShimTest::Require(Until(host, a, b, [&]
    {
        const auto& members = b.Control().State().members;
        return members.size() == 3 && members[0].ready && members[1].ready && members[2].ready;
    }), "ready state distribution");
    CHECK(host.Control().RequestStart(Now()));
    OpenShimTest::Require(Until(host, a, b, [&] { return a.Control().State().phase == Phase::Preparing && b.Control().State().phase == Phase::Preparing; }), "prepare barrier");
    CHECK(host.Control().Prepared()); CHECK(a.Control().Prepared());
    for (int i = 0; i < 20; ++i) { host.Poll(); a.Poll(); b.Poll(); }
    CHECK(host.Control().State().phase == Phase::Preparing);
    CHECK(b.Control().Prepared());
    OpenShimTest::Require(Until(host, a, b, [&] { return a.Control().State().phase == Phase::Running && b.Control().State().phase == Phase::Running; }), "commit barrier");
    a.Close();
    CHECK(Until(host, a, b, [&] { return host.Control().State().members.size() == 2 && b.Control().State().members.size() == 2; }));
    host.Control().Leave();
    CHECK(Until(host, a, b, [&] { return b.Control().State().phase == Phase::Closed && host.Connections() == 0; }));
    CHECK(b.Control().State().reason == "Host ended the session");
    host.Close(); b.Close();
    CHECK(host.ControlPort() == 0 && host.Connections() == 0 && b.Connections() == 0);
    DiscoveryHost reopened; CHECK(reopened.Open(0x7F000001, 0));
    const auto oldPort = reopened.Port();
    CHECK(!reopened.Open(0x08080808, 0) && reopened.Port() == 0);
    DiscoveryHost replacement; CHECK(replacement.Open(0x7F000001, oldPort));
    std::printf("direct_lan_socket_tests: %d checks; no service, helper or account provider loaded\n", OpenShimTest::CheckCount());
    return OpenShimTest::ExitCode();
}
