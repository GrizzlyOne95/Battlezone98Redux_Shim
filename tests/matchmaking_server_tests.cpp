#include "matchmaking_server.h"

#include <cstdio>
#include <string>
#include "test_check.h"

namespace
{
    namespace MS = BZROpenShim::MatchmakingServer;

    MS::HostStatus Validate(const char* text, std::string& host)
    {
        return MS::ValidateCustomHost(text, host);
    }

    std::string Launch(const wchar_t* commandLine)
    {
        std::string host;
        if (!MS::ExtractLaunchHost(commandLine, host))
            return "<none>";
        return host;
    }

    void TestModeParsing()
    {
        MS::Mode mode = MS::Mode::Custom;
        CHECK(MS::ParseMode("", mode) && mode == MS::Mode::None);
        CHECK(MS::ParseMode("  rebellion ", mode) && mode == MS::Mode::Rebellion);
        CHECK(MS::ParseMode("CUSTOM", mode) && mode == MS::Mode::Custom);
        CHECK(MS::ParseMode(" local", mode) && mode == MS::Mode::Local);
        CHECK(MS::ParseMode(" LAN ", mode) && mode == MS::Mode::Lan);
        CHECK(std::string(MS::ModeName(mode)) == "LAN");
        CHECK(MS::ResolveSavedHost(mode, "192.168.1.7:1437") == "192.168.1.7:1437");
        CHECK(MS::ResolveSavedHost(mode, "http://bad") == "");
        CHECK(!MS::ParseMode("official", mode) && mode == MS::Mode::None);
    }

    void TestCustomHostAccepted()
    {
        std::string host;
        CHECK(Validate("192.168.0.192", host) == MS::HostStatus::Ok && host == "192.168.0.192");
        CHECK(Validate("  play.example.org ", host) == MS::HostStatus::Ok && host == "play.example.org");
        CHECK(Validate("Host-1.example.com:1337", host) == MS::HostStatus::Ok &&
              host == "Host-1.example.com");
        CHECK(Validate("localhost:01337", host) == MS::HostStatus::Ok && host == "localhost");
        CHECK(Validate("example.org:8080", host) == MS::HostStatus::Ok && host == "example.org:8080");
        CHECK(Validate("10.0.0.5:01437", host) == MS::HostStatus::Ok && host == "10.0.0.5:1437");
        CHECK(Validate("x.example:65534", host) == MS::HostStatus::Ok && host == "x.example:65534");
    }

    void TestCustomHostUrl()
    {
        std::string host;
        CHECK(Validate("ws://bzr.battlezonecommunity.com:1337/", host) == MS::HostStatus::Ok &&
              host == "bzr.battlezonecommunity.com");
        CHECK(Validate("  WS://Play.Example.org/ ", host) == MS::HostStatus::Ok && host == "Play.Example.org");
        CHECK(Validate("ws://example.org:8080", host) == MS::HostStatus::Ok && host == "example.org:8080");
        CHECK(Validate("wss://example.org/", host) == MS::HostStatus::Invalid && host.empty());
        CHECK(Validate("ws://example.org//", host) == MS::HostStatus::Invalid);
        CHECK(Validate("ws://example.org/lobby", host) == MS::HostStatus::Invalid);
        CHECK(Validate("ws://example.org/?a=1", host) == MS::HostStatus::Invalid);
        CHECK(Validate("ws://", host) == MS::HostStatus::Invalid);
        CHECK(Validate("ws:///", host) == MS::HostStatus::Invalid);
        CHECK(Validate("http://example.org", host) == MS::HostStatus::Invalid);
    }

    void TestCustomHostRejected()
    {
        std::string host = "stale";
        CHECK(Validate("", host) == MS::HostStatus::Empty && host.empty());
        CHECK(Validate("   ", host) == MS::HostStatus::Empty);
        CHECK(Validate("ftp://example.org", host) == MS::HostStatus::Invalid);
        CHECK(Validate("example.org/path", host) == MS::HostStatus::Invalid);
        CHECK(Validate("exa mple.org", host) == MS::HostStatus::Invalid);
        CHECK(Validate("user@example.org", host) == MS::HostStatus::Invalid);
        CHECK(Validate("example..org", host) == MS::HostStatus::Invalid);
        CHECK(Validate(".example.org", host) == MS::HostStatus::Invalid);
        CHECK(Validate("exa$mple.org", host) == MS::HostStatus::Invalid);
        CHECK(Validate("example.org:", host) == MS::HostStatus::Invalid);
        CHECK(Validate("example.org:abc", host) == MS::HostStatus::Invalid);
        // A control code stored by the entry (stock AppendChar keeps Ctrl+V's
        // 0x16) stays Invalid; the entry hook filters it before it gets here.
        CHECK(Validate("\x16host.example", host) == MS::HostStatus::Invalid && host.empty());
        CHECK(Validate(":1337", host) == MS::HostStatus::Invalid);
        CHECK(Validate("a:1:2", host) == MS::HostStatus::Invalid);
        CHECK(Validate("example.org:0", host) == MS::HostStatus::UnsupportedPort);
        CHECK(Validate("example.org:65535", host) == MS::HostStatus::UnsupportedPort);
        CHECK(Validate("example.org:99999", host) == MS::HostStatus::UnsupportedPort);
        CHECK(host.empty());
    }

    void TestSplitServer()
    {
        std::string host;
        unsigned port = 0;
        CHECK(MS::SplitServer("x.example", host, port) && host == "x.example" && port == MS::kPort);
        CHECK(MS::SplitServer("10.0.0.5:1437", host, port) && host == "10.0.0.5" && port == 1437);
        CHECK(!MS::SplitServer("x.example:0", host, port));
        CHECK(!MS::SplitServer("x.example:65535", host, port));
        CHECK(!MS::SplitServer("x.example:", host, port));
        CHECK(!MS::SplitServer(":1437", host, port));
        CHECK(!MS::SplitServer("", host, port));
    }

    void TestResolveSavedHost()
    {
        CHECK(MS::ResolveSavedHost(MS::Mode::None, "x.example") == "");
        CHECK(MS::ResolveSavedHost(MS::Mode::Rebellion, "x.example") == MS::kRebellionHost);
        CHECK(MS::ResolveSavedHost(MS::Mode::Local, "x.example") == MS::kLocalHost);
        CHECK(MS::ResolveSavedHost(MS::Mode::Custom, "x.example:1337") == "x.example");
        CHECK(MS::ResolveSavedHost(MS::Mode::Custom, "x.example:1437") == "x.example:1437");
        CHECK(MS::ResolveSavedHost(MS::Mode::Custom, "http://x.example") == "");
        CHECK(MS::ResolveSavedHost(MS::Mode::Custom, "") == "");
        CHECK(MS::ResolveSavedHost(MS::Mode::Custom, "x.example") == "x.example");
        std::string community;
        CHECK(MS::ValidateCustomHost(MS::kCommunityServerHost, community) == MS::HostStatus::Ok &&
              community == MS::kCommunityServerHost);
    }

    void TestLaunchHost()
    {
        CHECK(Launch(L"battlezone98redux.exe /bzrserver=ws://192.168.0.192:1337/") == "192.168.0.192");
        CHECK(Launch(L"\"C:/Games/bz.exe\" /BZRSERVER=ws://Play.Example.org/ /nosplash") ==
              "Play.Example.org");
        CHECK(Launch(L"bz.exe -bzrserver=ws://host.example:1337") == "host.example");
        CHECK(Launch(L"bz.exe /bzrserver=\"ws://quoted.example:1337/x\" /y") == "quoted.example");
        CHECK(Launch(L"bz.exe /bzrserver=bare.example") == "bare.example");
        CHECK(Launch(L"bz.exe /bzrserver=ws://[::1]:1337/") == "::1");
        CHECK(Launch(L"bz.exe /nosplash") == "<none>");
        CHECK(Launch(L"bz.exe /bzrserver=") == "<none>");
        CHECK(Launch(L"bz.exe /bzrserver=ws://:1337/") == "<none>");
        // Not a switch of its own: embedded in another argument.
        CHECK(Launch(L"bz.exe /xbzrserver=ws://a.example/") == "<none>");
    }

    unsigned LaunchPort(const wchar_t* commandLine)
    {
        std::string host;
        unsigned port = 12345;
        if (!MS::ExtractLaunchServer(commandLine, host, port))
            return 99999;
        return port;
    }

    void TestLaunchPort()
    {
        CHECK(LaunchPort(L"bz.exe /bzrserver=ws://127.0.0.1:1337/") == 1337);
        CHECK(LaunchPort(L"bz.exe /bzrserver=ws://127.0.0.1:2000/") == 2000);
        CHECK(LaunchPort(L"bz.exe /bzrserver=ws://127.0.0.1/") == 80);
        CHECK(LaunchPort(L"bz.exe /bzrserver=wss://h.example/") == 443);
        CHECK(LaunchPort(L"bz.exe /bzrserver=bare.example") == MS::kPort);
        CHECK(LaunchPort(L"bz.exe /bzrserver=ws://[::1]:1444/") == 1444);
        CHECK(LaunchPort(L"bz.exe /bzrserver=ws://h.example:99999/") == 0);
        CHECK(LaunchPort(L"bz.exe /nosplash") == 99999);
        // "host:" with no digits keeps the scheme default; schemes ignore case.
        CHECK(LaunchPort(L"bz.exe /bzrserver=ws://community.example:/") == 80);
        CHECK(LaunchPort(L"bz.exe /bzrserver=wss://community.example:/") == 443);
        CHECK(LaunchPort(L"bz.exe /bzrserver=WS://127.0.0.1/") == 80);
        CHECK(LaunchPort(L"bz.exe /bzrserver=WSS://h.example/") == 443);
        CHECK(LaunchPort(L"bz.exe /bzrserver=ws://h.example?x=1") == 80);
        // Not a websocket scheme: the official port stays the default.
        CHECK(LaunchPort(L"bz.exe /bzrserver=http://h.example/") == MS::kPort);
        std::string host;
        unsigned port = 0;
        CHECK(MS::ExtractLaunchServer(L"bz.exe /bzrserver=ws://h.example?x=1", host, port) && host == "h.example");
        CHECK(MS::ExtractLaunchServer(L"bz.exe /bzrserver=WS://h.example:/", host, port) && host == "h.example" && port == 80);
        CHECK(MS::ExtractLaunchServer(L"bz.exe /bzrserver=http://h.example:2000/", host, port) && host == "h.example" && port == 2000);
    }

    // The game's own lookup is (host, service); host alone is not enough.
    void TestGameServerLookup()
    {
        const char* official = MS::kRebellionHost;

        // Loopback /bzrserver=ws://127.0.0.1:1337/: GOG Galaxy's own peer
        // lookup on the same host is not BZRNet; the game's lookup is.
        CHECK(!MS::IsGameServerLookup("127.0.0.1", "9977", official, "127.0.0.1", 1337));
        CHECK(MS::IsGameServerLookup("127.0.0.1", "1337", official, "127.0.0.1", 1337));
        // No service names no port: the host decides, as before.
        CHECK(MS::IsGameServerLookup("127.0.0.1", nullptr, official, "127.0.0.1", 1337));
        CHECK(MS::IsGameServerLookup("127.0.0.1", "", official, "127.0.0.1", 1337));
        CHECK(MS::IsGameServerLookup(official, nullptr, official, "127.0.0.1", 1337));
        CHECK(!MS::IsGameServerLookup("127.0.0.2", nullptr, official, "127.0.0.1", 1337));

        // Custom /bzrserver= port: BZRNet only on that port.
        CHECK(MS::IsGameServerLookup("127.0.0.1", "2000", official, "127.0.0.1", 2000));
        CHECK(!MS::IsGameServerLookup("127.0.0.1", "1337", official, "127.0.0.1", 2000));
        CHECK(!MS::IsGameServerLookup("127.0.0.1", "9977", official, "127.0.0.1", 2000));
        CHECK(!MS::IsGameServerLookup("127.0.0.1", "20000", official, "127.0.0.1", 2000));

        // LAN IP server: unchanged for the game's lookup; other hosts never match.
        CHECK(MS::IsGameServerLookup("192.168.0.44", "1337", official, "192.168.0.44", 1337));
        CHECK(!MS::IsGameServerLookup("127.0.0.1", "9977", official, "192.168.0.44", 1337));
        CHECK(!MS::IsGameServerLookup("192.168.0.45", "1337", official, "192.168.0.44", 1337));

        // The official host stays BZRNet on 1337 whatever the launch server.
        CHECK(MS::IsGameServerLookup(official, "1337", official, official, 1337));
        CHECK(MS::IsGameServerLookup("BATTLEZONE98MP.webdev.rebellion.co.uk", "1337", official, "127.0.0.1", 1337));
        CHECK(!MS::IsGameServerLookup(official, "443", official, official, 1337));
        CHECK(!MS::IsGameServerLookup(nullptr, "1337", official, official, 1337));

        CHECK(MS::ServiceMatchesPort("01337", 1337));
        CHECK(!MS::ServiceMatchesPort("1337x", 1337));
        CHECK(!MS::ServiceMatchesPort("http", 80));
        CHECK(!MS::ServiceMatchesPort("1337", 0));
    }
}

int main()
{
    TestModeParsing();
    TestCustomHostAccepted();
    TestCustomHostUrl();
    TestCustomHostRejected();
    TestSplitServer();
    TestResolveSavedHost();
    TestLaunchHost();
    TestLaunchPort();
    TestGameServerLookup();
    if (OpenShimTest::FailureCount() == 0)
        std::printf("matchmaking_server_tests: all passed\n");
    return OpenShimTest::ExitCode();
}
