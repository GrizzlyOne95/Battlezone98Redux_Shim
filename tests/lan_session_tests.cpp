#include "lan_session.h"
#include "test_check.h"
#include <windows.h>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>

namespace LAN = BZROpenShim::LanSession;
namespace fs = std::filesystem;
#define REQUIRE(c) ::OpenShimTest::Require((c), #c)

bool Wait(LAN::HostState state, DWORD timeout = 10000)
{
    const auto since = GetTickCount64();
    do
    {
        LAN::Tick();
        if (LAN::Status().state == state) return true;
        Sleep(10);
    } while (GetTickCount64() - since < timeout);
    return false;
}

int wmain(int argc, wchar_t** argv)
{
    if (argc > 1 && std::wstring(argv[1]) == L"--lan-discovery")
    {
        // Lifecycle fixture is our own executable, launched exactly like the
        // packaged helper. Flood stderr before READY: it must be a file, not
        // an undrained pipe that hangs the server once a mission starts.
        wchar_t mode[32]{};
        GetEnvironmentVariableW(L"OPENSHIM_LAN_TEST_MODE", mode, 32);
        if (std::wstring(mode) == L"exit")
        {
            std::fputs("OSError: [WinError 10048] bind 1337: address already in use\n", stderr);
            std::fflush(stderr); return 7;
        }
        // Every service must bind to the displayed adapter, never all interfaces.
        for (int i = 2; i + 1 < argc; ++i)
            if (std::wstring(argv[i]) == L"--ws-host" || std::wstring(argv[i]) == L"--udp-host" ||
                std::wstring(argv[i]) == L"--relay-host")
                if (std::wstring(argv[i + 1]) == L"0.0.0.0") return 9;
        for (int i = 0; i < 2000; ++i) std::fputs("fixture stderr padding padding padding padding padding padding\n", stderr);
        std::fflush(stderr);
        std::puts("BZRLAN_READY 1337"); std::fflush(stdout);
        std::string line;
        std::getline(std::cin, line);
        return line == "stop" ? 0 : 8;
    }

    // Optional real-helper integration lane, run explicitly with a scratch
    // game-shaped root containing tools/lan/BZRServer.exe. No game is loaded.
    if (argc == 3 && (std::wstring(argv[1]) == L"--real-helper" || std::wstring(argv[1]) == L"--owner-exit"))
    {
        REQUIRE(LAN::StartHost(argv[2]));
        CHECK(Wait(LAN::HostState::Running, 30000));
        if (std::wstring(argv[1]) == L"--owner-exit")
        {
            std::puts("READY: owner exits with its managed helper running");
            return OpenShimTest::ExitCode(); // kernel job teardown must close the helper
        }
        REQUIRE(LAN::StartScan());
        const auto since = GetTickCount64();
        do { LAN::Tick(); Sleep(10); } while (LAN::Status().scanning && GetTickCount64() - since < 5000);
        const auto result = LAN::Status();
        CHECK(!result.scanning && !result.hosts.empty());
        std::printf("Real helper: %zu host endpoints discovered\n", result.hosts.size());
        for (const auto& host : result.hosts) CHECK(host.port == 1337 && !host.name.empty());
        LAN::StopHost(); CHECK(Wait(LAN::HostState::Stopped));
        std::puts("Real helper: managed startup, discovery and graceful stop complete");
        LAN::StopScan();
        return OpenShimTest::ExitCode();
    }

    wchar_t temp[MAX_PATH]{}; REQUIRE(GetTempPathW(MAX_PATH, temp) != 0);
    const fs::path root = fs::path(temp) / (L"OpenShim LAN test \u03a9 " + std::to_wstring(GetCurrentProcessId()));
    REQUIRE(fs::create_directories(root / "tools" / "lan"));
    wchar_t self[32768]{}; REQUIRE(GetModuleFileNameW(nullptr, self, DWORD(std::size(self))) != 0);
    const auto helper = root / "tools" / "lan" / "BZRServer.exe";
    fs::copy_file(self, helper);
    if (!LAN::StartHost(root.wstring()) && LAN::Status().hostAddress.empty())
    {
        std::puts("SKIP: no active private IPv4 adapter for LAN host lifecycle test");
        fs::remove(helper); fs::remove(helper.parent_path()); fs::remove(root / "tools"); fs::remove(root);
        return 77;
    }
    REQUIRE(Wait(LAN::HostState::Running));
    CHECK(LAN::StartHost(root.wstring())); // repeated click owns just one process
    const auto first = LAN::Status().hostAddress;
    LAN::StopHost(); CHECK(LAN::Status().state == LAN::HostState::Stopping);
    CHECK(!LAN::StartHost(root.wstring())); // cannot spawn a second while stopping
    CHECK(Wait(LAN::HostState::Stopped));
    CHECK(LAN::StartScan());
    LAN::StopScan(); CHECK(!LAN::Status().scanning);
    SetEnvironmentVariableW(L"OPENSHIM_LAN_TEST_MODE", L"exit");
    CHECK(LAN::StartHost(root.wstring())); CHECK(Wait(LAN::HostState::Failed));
    CHECK(LAN::Status().hostMessage.find("10048") != std::string::npos);
    SetEnvironmentVariableW(L"OPENSHIM_LAN_TEST_MODE", nullptr);
    CHECK(LAN::StartHost(root.wstring())); CHECK(Wait(LAN::HostState::Running));
    CHECK(LAN::Status().hostAddress == first);
    LAN::StopHost(); CHECK(Wait(LAN::HostState::Stopped));
    fs::remove(helper);
    CHECK(!LAN::StartHost(root.wstring()));
    CHECK(LAN::Status().hostMessage.find("helper missing") != std::string::npos);
    fs::remove(root / "openshim" / "lan" / "host.log");
    fs::remove(root / "openshim" / "lan"); fs::remove(root / "openshim");
    fs::remove(root / "tools" / "lan"); fs::remove(root / "tools"); fs::remove(root);
    return OpenShimTest::ExitCode();
}
