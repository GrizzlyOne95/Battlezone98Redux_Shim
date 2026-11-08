#include "steam_ban_list.h"

#include <cstdio>
#include <fstream>
#include <string>
#include "test_check.h"

namespace
{
    using BZROpenShim::SocketTunnel::SteamBanList;

    void TestParseKeepsOnlySteamIds()
    {
        SteamBanList bans;
        bans.Parse(
            "; OpenShim ban list\n"
            "S76561198000000001 Griefer\n"
            "s76561198000000002\n"
            "GABC123 gog player\n"
            "S0\n"
            "S\n"
            "S12x34\n"
            "S18446744073709551615\n"
            "S18446744073709551616\n"
            "S99999999999999999999\n");
        CHECK(bans.Banned(76561198000000001ull));
        CHECK(bans.Banned(76561198000000002ull));
        CHECK(bans.Banned(18446744073709551615ull));
        CHECK(!bans.Banned(0));
        CHECK(!bans.Banned(12));
        CHECK(bans.Size() == 3);
    }

    void WriteText(const std::wstring& path, const std::string& text)
    {
        std::ofstream file(path, std::ios::binary | std::ios::trunc);
        file << text;
    }

    void TestRefreshFollowsTheFile()
    {
        wchar_t dir[MAX_PATH]{};
        CHECK(GetTempPathW(MAX_PATH, dir) != 0);
        const std::wstring path = std::wstring(dir) + L"openshim_steam_ban_list_test_" +
            std::to_wstring(GetCurrentProcessId()) + L".cfg";
        DeleteFileW(path.c_str());

        SteamBanList bans;
        CHECK(!bans.Refresh(L""));
        CHECK(!bans.Refresh(path)); // missing, nothing loaded yet
        CHECK(bans.Size() == 0);

        WriteText(path, "S76561198000000001 a\n");
        CHECK(bans.Refresh(path));
        CHECK(bans.Banned(76561198000000001ull));
        CHECK(!bans.Refresh(path)); // unchanged

        WriteText(path, "S76561198000000001 a\nS76561198000000002 bb\n");
        CHECK(bans.Refresh(path));
        CHECK(bans.Size() == 2);

        WriteText(path, ""); // truncated mid-write: keep the last list
        CHECK(!bans.Refresh(path));
        CHECK(bans.Size() == 2);

        CHECK(DeleteFileW(path.c_str()) != 0);
        CHECK(bans.Refresh(path)); // unbanned everyone
        CHECK(bans.Size() == 0);
        CHECK(!bans.Refresh(path));
    }
}

int main()
{
    TestParseKeepsOnlySteamIds();
    TestRefreshFollowsTheFile();
    if (OpenShimTest::FailureCount() == 0)
        std::printf("steam_ban_list_tests: all passed\n");
    return OpenShimTest::ExitCode();
}
