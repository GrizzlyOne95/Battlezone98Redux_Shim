// lobby_team_commands_tests.cpp
// Host-side checks for the /team, /swap and /host parser in
// include/lobby_team_commands.h. The engine half (AssignTeam, SetLobbyOwner)
// needs a live lobby; see Docs/LOBBY_TEAM_HOST_COMMANDS.md for that test.

#include "lobby_team_commands.h"

#include "test_check.h"

using OpenShimTest::Check;

using namespace BZROpenShim;

namespace
{
    LobbyCommandRequest Parse(const char* text)
    {
        return ParseLobbyTeamCommand(text);
    }

    void TestOtherCommandsFallThrough()
    {
        Check(Parse(nullptr).kind == LobbyCommandKind::None, "null is not a lobby command");
        Check(Parse("").kind == LobbyCommandKind::None, "empty is not a lobby command");
        Check(Parse("/kick").kind == LobbyCommandKind::None, "/kick falls through");
        Check(Parse("/teams 2").kind == LobbyCommandKind::None, "/teams is a different verb");
        Check(Parse("/hostage").kind == LobbyCommandKind::None, "/hostage is a different verb");
        Check(Parse("team 2").kind == LobbyCommandKind::None, "chat text without a slash falls through");
    }

    void TestTeam()
    {
        LobbyCommandRequest r = Parse("/team 3");
        Check(r.kind == LobbyCommandKind::Team && r.teamA == 3 && r.name.empty(), "/team 3 targets the selection");

        r = Parse("/TEAM\t 12 ");
        Check(r.kind == LobbyCommandKind::Team && r.teamA == 12, "verb is case-insensitive and blanks are trimmed");

        r = Parse("/team Big Bob 2");
        Check(r.kind == LobbyCommandKind::Team && r.teamA == 2 && r.name == "Big Bob",
              "a name may contain spaces; the last token is the team");

        r = Parse("/team 7 4");
        Check(r.kind == LobbyCommandKind::Team && r.teamA == 4 && r.name == "7", "a numeric name is still a name");

        Check(Parse("/team").kind == LobbyCommandKind::Usage, "/team alone prints usage");
        Check(Parse("/team 0").kind == LobbyCommandKind::Usage, "team 0 is rejected");
        Check(Parse("/team 16").kind == LobbyCommandKind::Usage, "team 16 is rejected (AssignTeam takes < 16)");
        Check(Parse("/team 15").kind == LobbyCommandKind::Team, "team 15 is accepted");
        Check(Parse("/team -1").kind == LobbyCommandKind::Usage, "signed team is rejected");
        Check(Parse("/team Bob").kind == LobbyCommandKind::Usage, "a name without a team prints usage");
        Check(Parse("/team 2x").kind == LobbyCommandKind::Usage, "trailing junk is rejected");
        Check(Parse("/team 002").kind == LobbyCommandKind::Usage, "three digits are rejected");
    }

    void TestSwap()
    {
        LobbyCommandRequest r = Parse("/swap 1 2");
        Check(r.kind == LobbyCommandKind::Swap && r.teamA == 1 && r.teamB == 2, "/swap 1 2");

        Check(Parse("/swap 2 2").kind == LobbyCommandKind::Usage, "swapping a team with itself is rejected");
        Check(Parse("/swap 2").kind == LobbyCommandKind::Usage, "one team prints usage");
        Check(Parse("/swap 1 2 3").kind == LobbyCommandKind::Usage, "three teams print usage");
        Check(Parse("/swap Bob 2").kind == LobbyCommandKind::Usage, "names are not accepted by /swap");
        Check(Parse("/swap 1 16").kind == LobbyCommandKind::Usage, "out-of-range team is rejected");
    }

    void TestHost()
    {
        LobbyCommandRequest r = Parse("/host");
        Check(r.kind == LobbyCommandKind::Host && r.name.empty(), "/host targets the selection");

        r = Parse("/Host  Big Bob ");
        Check(r.kind == LobbyCommandKind::Host && r.name == "Big Bob", "/host <name> keeps inner spaces");
    }
}

int main()
{
    TestOtherCommandsFallThrough();
    TestTeam();
    TestSwap();
    TestHost();
    return OpenShimTest::ExitCode();
}
