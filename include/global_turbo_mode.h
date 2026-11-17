#pragma once

// global_turbo_mode.h
// Pure rules for [SinglePlayer] Turbo, the global turbo team filter. No
// Windows or engine calls, so tests/global_turbo_mode_tests.cpp can include
// it. The engine side is src/patches/global_turbo.cpp.
//
//   Turbo = 0  off
//   Turbo = 1  every team
//   Turbo = 2  enemy teams only: teams hostile to the local player, by the
//              engine's own alliance test (GameObject::EnemyP). Allies and
//              team 0 never count.
//   Turbo = 3  my team only (the local player's own team)
//
// true/false and the other BoolToken words still read as 1/0, so ini files
// written when Turbo was a bool keep working.

#include "bool_token.h"

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
namespace GlobalTurboMode
{
    enum class Mode : int
    {
        Off = 0,
        AllTeams = 1,
        EnemyTeams = 2,
        MyTeam = 3,
    };

    // How the turbo block's three patch sites are laid out.
    //   Stock    stock bytes; no unit turbos (beyond stock rules).
    //   StaticOn every unit turbos: tolerance operand -> shim constant, jbe
    //            NOP'd (the EXU GlobalTurbo patch).
    //   PerUnit  both absolute operands point at shim cells the per-unit
    //            begin hook fills for each unit; the jbe stays stock. Data
    //            only: no code byte changes per unit.
    enum class Layout : int
    {
        Stock = 0,
        StaticOn = 1,
        PerUnit = 2,
    };

    // Engine teams are 0-15.
    constexpr int kTeamCount = 16;

    // Sets `out` and returns true for 0-3 or a BoolToken word (true reads as
    // AllTeams). Leaves `out` untouched and returns false otherwise.
    inline bool TryParse(const char* text, size_t length, Mode& out)
    {
        if (!text)
            return false;
        size_t begin = 0;
        size_t end = length;
        while (begin < end && BoolToken::Detail::IsAsciiSpace(text[begin]))
            ++begin;
        while (end > begin && BoolToken::Detail::IsAsciiSpace(text[end - 1]))
            --end;
        if (end - begin == 1 && text[begin] >= '0' && text[begin] <= '3')
        {
            out = static_cast<Mode>(text[begin] - '0');
            return true;
        }
        bool token = false;
        if (!BoolToken::TryParse(text + begin, end - begin, token))
            return false;
        out = token ? Mode::AllTeams : Mode::Off;
        return true;
    }

    // Modes 2 and 3 decide per unit; 0 and 1 are one state for every unit.
    inline bool IsTeamFiltered(Mode mode)
    {
        return mode == Mode::EnemyTeams || mode == Mode::MyTeam;
    }

    // True when `team` is hostile to the player. `hostileMask` bit t is the
    // engine's EnemyP(t) for the player object; team 0 and the player's own
    // team never count, whatever the mask says.
    inline bool IsHostileTeam(int team, int playerTeam, uint32_t hostileMask)
    {
        if (team <= 0 || team >= kTeamCount || team == playerTeam)
            return false;
        return ((hostileMask >> team) & 1u) != 0;
    }

    // Whether the mode gives turbo to a unit on `unitTeam`. An unreadable
    // unit team never matches a filter mode: doubt never adds turbo.
    inline bool TeamMatches(Mode mode, bool unitTeamKnown, int unitTeam, int playerTeam,
                            uint32_t hostileMask)
    {
        switch (mode)
        {
        case Mode::Off: return false;
        case Mode::AllTeams: return true;
        case Mode::EnemyTeams:
            return unitTeamKnown && IsHostileTeam(unitTeam, playerTeam, hostileMask);
        case Mode::MyTeam: return unitTeamKnown && unitTeam == playerTeam;
        }
        return false;
    }

    // The per-unit decision. A per-unit EXU override (exu.SetUnitTurbo)
    // always wins over the mode. Network games never turbo.
    inline bool UnitWantsTurbo(Mode mode,
                               bool singlePlayer,
                               bool hasOverride,
                               bool overrideValue,
                               bool unitTeamKnown,
                               int unitTeam,
                               int playerTeam,
                               uint32_t hostileMask)
    {
        if (!singlePlayer)
            return false;
        if (hasOverride)
            return overrideValue;
        return TeamMatches(mode, unitTeamKnown, unitTeam, playerTeam, hostileMask);
    }

    // Whether the mode or a live per-unit override needs the per-unit path.
    inline bool NeedsPerUnit(Mode mode, bool singlePlayer, bool anyOverride)
    {
        return singlePlayer && (IsTeamFiltered(mode) || anyOverride);
    }

    // The site layout for the current state. Modes 0/1 with no override keep
    // the static layouts. When the per-unit path is needed but its hook is
    // not installed, fall back to the static layout of the mode: every team
    // for mode 1, off for 0, 2 and 3 (a filter never widens to every team).
    inline Layout ChooseLayout(Mode mode, bool singlePlayer, bool anyOverride,
                               bool unitHooksInstalled)
    {
        if (!singlePlayer)
            return Layout::Stock;
        if (NeedsPerUnit(mode, singlePlayer, anyOverride) && unitHooksInstalled)
            return Layout::PerUnit;
        return mode == Mode::AllTeams ? Layout::StaticOn : Layout::Stock;
    }

    // FLT_MAX as IEEE-754 bits.
    constexpr uint32_t kFloatMaxBits = 0x7F7FFFFFu;

    struct ThresholdBits
    {
        uint32_t tolerance;  // read by `comiss throttle, [tol]`
        uint32_t gate;       // read by `movss xmm0, [gate]` before `comiss xmm0, [ebp-0x54]`
    };

    // The two cells for one unit, as float bit patterns (the hook runs with
    // an x87 value pending, so it copies bits rather than doing float work).
    // Turbo: the shim tolerance, and FLT_MAX for the gate so `jbe` falls
    // through for any ordered [ebp-0x54] below FLT_MAX. Stock: the values the
    // stock operands point at.
    inline ThresholdBits UnitThresholdBits(bool turbo, uint32_t turboToleranceBits,
                                           uint32_t stockToleranceBits, uint32_t stockGateBits)
    {
        if (turbo)
            return { turboToleranceBits, kFloatMaxBits };
        return { stockToleranceBits, stockGateBits };
    }

    // Log name of a mode.
    inline const char* Name(Mode mode)
    {
        switch (mode)
        {
        case Mode::Off: return "off";
        case Mode::AllTeams: return "all";
        case Mode::EnemyTeams: return "enemy";
        case Mode::MyTeam: return "mine";
        }
        return "?";
    }

    // Log name of a layout.
    inline const char* Name(Layout layout)
    {
        switch (layout)
        {
        case Layout::Stock: return "stock";
        case Layout::StaticOn: return "static-on";
        case Layout::PerUnit: return "per-unit";
        }
        return "?";
    }
}
}
