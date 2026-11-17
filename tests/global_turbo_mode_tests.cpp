#include "global_turbo_mode.h"

#include <cfloat>
#include <cstdio>
#include <cstring>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::GlobalTurboMode;

    // -1 = unrecognized, else the parsed mode.
    int Parse(const char* text)
    {
        Mode mode = Mode::MyTeam;
        if (!TryParse(text, std::strlen(text), mode))
            return -1;
        return static_cast<int>(mode);
    }

    uint32_t Bits(float value)
    {
        uint32_t bits = 0;
        std::memcpy(&bits, &value, sizeof(bits));
        return bits;
    }

    float FromBits(uint32_t bits)
    {
        float value = 0.0f;
        std::memcpy(&value, &bits, sizeof(value));
        return value;
    }

    // Every team but 0 hostile: the player's own team is never hostile.
    constexpr uint32_t kAllHostile = 0xFFFEu;

    void TestDigits()
    {
        CHECK(Parse("0") == 0);
        CHECK(Parse("1") == 1);
        CHECK(Parse("2") == 2);
        CHECK(Parse("3") == 3);
        CHECK(Parse(" 2 ") == 2);
        CHECK(Parse("\t3\r\n") == 3);
    }

    void TestOldBoolValuesStillRead()
    {
        CHECK(Parse("true") == 1);
        CHECK(Parse("TRUE") == 1);
        CHECK(Parse("on") == 1);
        CHECK(Parse("yes") == 1);
        CHECK(Parse("false") == 0);
        CHECK(Parse("off") == 0);
        CHECK(Parse(" no ") == 0);
    }

    void TestOtherTextIsUnrecognized()
    {
        CHECK(Parse("4") == -1);
        CHECK(Parse("-1") == -1);
        CHECK(Parse("22") == -1);
        CHECK(Parse("enemy") == -1);
        CHECK(Parse("") == -1);
        CHECK(Parse("  ") == -1);
        Mode mode = Mode::EnemyTeams;
        CHECK(!TryParse(nullptr, 0, mode));
        CHECK(!TryParse("9", 1, mode));
        CHECK(mode == Mode::EnemyTeams);
    }

    void TestLengthIsHonored()
    {
        Mode mode = Mode::Off;
        CHECK(TryParse("23", 1, mode) && mode == Mode::EnemyTeams);
    }

    void TestTeamFilteredModes()
    {
        CHECK(!IsTeamFiltered(Mode::Off));
        CHECK(!IsTeamFiltered(Mode::AllTeams));
        CHECK(IsTeamFiltered(Mode::EnemyTeams));
        CHECK(IsTeamFiltered(Mode::MyTeam));
    }

    void TestHostileTeam()
    {
        // Team 0, the player's own team and out-of-range teams never count.
        CHECK(!IsHostileTeam(0, 1, 0xFFFFFFFFu));
        CHECK(!IsHostileTeam(1, 1, 0xFFFFFFFFu));
        CHECK(!IsHostileTeam(-1, 1, 0xFFFFFFFFu));
        CHECK(!IsHostileTeam(16, 1, 0xFFFFFFFFu));
        CHECK(IsHostileTeam(2, 1, 1u << 2));
        // An ally (bit clear) is not hostile.
        CHECK(!IsHostileTeam(3, 1, 1u << 2));
    }

    void TestTeamMatches()
    {
        const int player = 1;
        for (int team = 0; team <= 15; ++team)
        {
            CHECK(!TeamMatches(Mode::Off, true, team, player, kAllHostile));
            CHECK(TeamMatches(Mode::AllTeams, true, team, player, kAllHostile));
            CHECK(TeamMatches(Mode::EnemyTeams, true, team, player, kAllHostile) ==
                  (team != player && team != 0));
            CHECK(TeamMatches(Mode::MyTeam, true, team, player, kAllHostile) == (team == player));
        }
        // Enemy mode follows the alliance mask, not "not my team": team 3
        // allied to the player gets no turbo; team 2 hostile does.
        const uint32_t hostile = 1u << 2;
        CHECK(TeamMatches(Mode::EnemyTeams, true, 2, player, hostile));
        CHECK(!TeamMatches(Mode::EnemyTeams, true, 3, player, hostile));
        // An ally is not on "my team" either.
        CHECK(!TeamMatches(Mode::MyTeam, true, 3, player, hostile));
        // A player on another team (for example after a team swap).
        CHECK(!TeamMatches(Mode::EnemyTeams, true, 3, 3, kAllHostile));
        CHECK(TeamMatches(Mode::EnemyTeams, true, 1, 3, kAllHostile));
        CHECK(TeamMatches(Mode::MyTeam, true, 3, 3, kAllHostile));
        // An unreadable team never matches a filter mode.
        CHECK(!TeamMatches(Mode::EnemyTeams, false, 2, 1, kAllHostile));
        CHECK(!TeamMatches(Mode::MyTeam, false, 1, 1, kAllHostile));
        CHECK(TeamMatches(Mode::AllTeams, false, 0, 1, 0));
        CHECK(!TeamMatches(Mode::Off, false, 0, 1, kAllHostile));
        // An empty mask (alliance test unavailable) turbos no enemy.
        for (int team = 0; team <= 15; ++team)
            CHECK(!TeamMatches(Mode::EnemyTeams, true, team, player, 0));
    }

    void TestOverrideWins()
    {
        const Mode modes[] = { Mode::Off, Mode::AllTeams, Mode::EnemyTeams, Mode::MyTeam };
        for (Mode mode : modes)
        {
            for (int team = 0; team <= 3; ++team)
            {
                CHECK(UnitWantsTurbo(mode, true, true, true, true, team, 1, kAllHostile));
                CHECK(!UnitWantsTurbo(mode, true, true, false, true, team, 1, kAllHostile));
            }
        }
    }

    void TestNetworkGamesNeverTurbo()
    {
        const Mode modes[] = { Mode::Off, Mode::AllTeams, Mode::EnemyTeams, Mode::MyTeam };
        for (Mode mode : modes)
        {
            CHECK(!UnitWantsTurbo(mode, false, false, false, true, 2, 1, kAllHostile));
            CHECK(!UnitWantsTurbo(mode, false, true, true, true, 2, 1, kAllHostile));
        }
    }

    void TestNoOverrideFollowsFilter()
    {
        CHECK(UnitWantsTurbo(Mode::EnemyTeams, true, false, false, true, 2, 1, kAllHostile));
        CHECK(!UnitWantsTurbo(Mode::EnemyTeams, true, false, false, true, 1, 1, kAllHostile));
        CHECK(UnitWantsTurbo(Mode::MyTeam, true, false, false, true, 1, 1, kAllHostile));
        CHECK(!UnitWantsTurbo(Mode::MyTeam, true, false, false, true, 2, 1, kAllHostile));
        CHECK(UnitWantsTurbo(Mode::AllTeams, true, false, false, true, 2, 1, kAllHostile));
        CHECK(!UnitWantsTurbo(Mode::Off, true, false, false, true, 2, 1, kAllHostile));
    }

    void TestNeedsPerUnit()
    {
        CHECK(!NeedsPerUnit(Mode::Off, true, false));
        CHECK(!NeedsPerUnit(Mode::AllTeams, true, false));
        CHECK(NeedsPerUnit(Mode::EnemyTeams, true, false));
        CHECK(NeedsPerUnit(Mode::MyTeam, true, false));
        CHECK(NeedsPerUnit(Mode::Off, true, true));
        CHECK(NeedsPerUnit(Mode::AllTeams, true, true));
        CHECK(!NeedsPerUnit(Mode::EnemyTeams, false, true));
    }

    void TestChooseLayout()
    {
        // Modes 0/1 with no override keep the static layouts.
        CHECK(ChooseLayout(Mode::Off, true, false, true) == Layout::Stock);
        CHECK(ChooseLayout(Mode::AllTeams, true, false, true) == Layout::StaticOn);
        CHECK(ChooseLayout(Mode::Off, true, false, false) == Layout::Stock);
        CHECK(ChooseLayout(Mode::AllTeams, true, false, false) == Layout::StaticOn);
        // Filters or overrides use the per-unit layout when the hook is in.
        CHECK(ChooseLayout(Mode::EnemyTeams, true, false, true) == Layout::PerUnit);
        CHECK(ChooseLayout(Mode::MyTeam, true, false, true) == Layout::PerUnit);
        CHECK(ChooseLayout(Mode::Off, true, true, true) == Layout::PerUnit);
        CHECK(ChooseLayout(Mode::AllTeams, true, true, true) == Layout::PerUnit);
        // Without the hook: the static layout of the mode; filters never widen.
        CHECK(ChooseLayout(Mode::EnemyTeams, true, false, false) == Layout::Stock);
        CHECK(ChooseLayout(Mode::MyTeam, true, true, false) == Layout::Stock);
        CHECK(ChooseLayout(Mode::Off, true, true, false) == Layout::Stock);
        CHECK(ChooseLayout(Mode::AllTeams, true, true, false) == Layout::StaticOn);
        // Network games: stock bytes whatever else is set.
        const Mode modes[] = { Mode::Off, Mode::AllTeams, Mode::EnemyTeams, Mode::MyTeam };
        for (Mode mode : modes)
        {
            CHECK(ChooseLayout(mode, false, false, true) == Layout::Stock);
            CHECK(ChooseLayout(mode, false, true, true) == Layout::Stock);
        }
    }

    // Model of the engine decision with the two cells: comiss sets CF and ZF
    // on unordered, so jb/jbe are taken for NaN.
    bool EngineTurbo(float throttle, float gateInput, ThresholdBits bits)
    {
        if (!(throttle >= FromBits(bits.tolerance)))
            return false;
        return FromBits(bits.gate) > gateInput;
    }

    void TestThresholdBits()
    {
        CHECK(kFloatMaxBits == Bits(FLT_MAX));
        const uint32_t turboTol = Bits(0.9f);
        const uint32_t stockTol = Bits(1.0f);
        const uint32_t stockGate = Bits(0.8f);

        const ThresholdBits on = UnitThresholdBits(true, turboTol, stockTol, stockGate);
        CHECK(on.tolerance == turboTol && on.gate == kFloatMaxBits);
        const ThresholdBits off = UnitThresholdBits(false, turboTol, stockTol, stockGate);
        CHECK(off.tolerance == stockTol && off.gate == stockGate);

        // Turbo: near-full throttle turbos whatever the gate input.
        CHECK(EngineTurbo(0.95f, 0.99f, on));
        CHECK(EngineTurbo(0.95f, 1000.0f, on));
        CHECK(!EngineTurbo(0.5f, 0.0f, on));
        // Stock: full throttle and gate input below 0.8.
        CHECK(!EngineTurbo(0.95f, 0.0f, off));
        CHECK(EngineTurbo(1.0f, 0.5f, off));
        CHECK(!EngineTurbo(1.0f, 0.9f, off));
        // The one difference from the NOP'd jbe: a NaN gate input does not
        // turbo under FLT_MAX, as in stock.
        const float nan = FromBits(0x7FC00000u);
        CHECK(!EngineTurbo(1.0f, nan, on));
        CHECK(!EngineTurbo(1.0f, nan, off));
    }

    void TestNames()
    {
        CHECK(std::strcmp(Name(Mode::Off), "off") == 0);
        CHECK(std::strcmp(Name(Mode::AllTeams), "all") == 0);
        CHECK(std::strcmp(Name(Mode::EnemyTeams), "enemy") == 0);
        CHECK(std::strcmp(Name(Mode::MyTeam), "mine") == 0);
        CHECK(std::strcmp(Name(Layout::Stock), "stock") == 0);
        CHECK(std::strcmp(Name(Layout::StaticOn), "static-on") == 0);
        CHECK(std::strcmp(Name(Layout::PerUnit), "per-unit") == 0);
    }
}

int main()
{
    TestDigits();
    TestOldBoolValuesStillRead();
    TestOtherTextIsUnrecognized();
    TestLengthIsHonored();
    TestTeamFilteredModes();
    TestHostileTeam();
    TestTeamMatches();
    TestOverrideWins();
    TestNetworkGamesNeverTurbo();
    TestNoOverrideFollowsFilter();
    TestNeedsPerUnit();
    TestChooseLayout();
    TestThresholdBits();
    TestNames();
    if (OpenShimTest::FailureCount() == 0)
        std::printf("global_turbo_mode_tests: all passed\n");
    return OpenShimTest::ExitCode();
}
