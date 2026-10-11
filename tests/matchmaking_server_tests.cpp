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
    }

    void TestCustomHostRejected()
    {
        std::string host = "stale";
        CHECK(Validate("", host) == MS::HostStatus::Empty && host.empty());
        CHECK(Validate("   ", host) == MS::HostStatus::Empty);
        CHECK(Validate("ws://example.org", host) == MS::HostStatus::Invalid);
        CHECK(Validate("example.org/path", host) == MS::HostStatus::Invalid);
        CHECK(Validate("exa mple.org", host) == MS::HostStatus::Invalid);
        CHECK(Validate("user@example.org", host) == MS::HostStatus::Invalid);
        CHECK(Validate("example..org", host) == MS::HostStatus::Invalid);
        CHECK(Validate(".example.org", host) == MS::HostStatus::Invalid);
        CHECK(Validate("exa$mple.org", host) == MS::HostStatus::Invalid);
        CHECK(Validate("example.org:", host) == MS::HostStatus::Invalid);
        CHECK(Validate("example.org:abc", host) == MS::HostStatus::Invalid);
        CHECK(Validate(":1337", host) == MS::HostStatus::Invalid);
        CHECK(Validate("a:1:2", host) == MS::HostStatus::Invalid);
        CHECK(Validate("example.org:8080", host) == MS::HostStatus::UnsupportedPort);
        CHECK(Validate("example.org:1338", host) == MS::HostStatus::UnsupportedPort);
        CHECK(host.empty());
    }

    void TestResolveSavedHost()
    {
        CHECK(MS::ResolveSavedHost(MS::Mode::None, "x.example") == "");
        CHECK(MS::ResolveSavedHost(MS::Mode::Rebellion, "x.example") == MS::kRebellionHost);
        CHECK(MS::ResolveSavedHost(MS::Mode::Custom, "x.example:1337") == "x.example");
        CHECK(MS::ResolveSavedHost(MS::Mode::Custom, "ws://x.example") == "");
        CHECK(MS::ResolveSavedHost(MS::Mode::Custom, "") == "");
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
}

int main()
{
    TestModeParsing();
    TestCustomHostAccepted();
    TestCustomHostRejected();
    TestResolveSavedHost();
    TestLaunchHost();
    if (OpenShimTest::FailureCount() == 0)
        std::printf("matchmaking_server_tests: all passed\n");
    return OpenShimTest::ExitCode();
}
