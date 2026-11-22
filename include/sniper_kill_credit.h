// sniper_kill_credit.h -- engine-independent decision logic for the sniper
// kill credit fix (src/patches/sniper_kill_credit.cpp).
//
// SniperShell::Hit (GOG Redux 2.2.301, 0x005D6E00, vtable 0x00887BB4 slot 5)
// runs only on the machine that owns the shell. After it has killed the
// victim's pilot it credits the kill one of two ways:
//   - remote victim (IsRemote, call 0x005D6FA3): SendSnipe 0x00573BB0 tells
//     the victim's owner, whose receive handler 0x00573AE0 sets record flag 4,
//     calls DistributedObject::RecordDeath 0x004B9BA0 and KillMessage
//     0x00626470 ('S');
//   - local victim (IsLocal, call 0x005D6FF7): only shell flags are set; no
//     RecordDeath and no KillMessage, so the kill never reaches the scoreboard.
// The fix wraps the IsLocal call and, for a local victim in a network game,
// does what the receive handler would have done on this machine.
//
// Header-only and free of Windows and engine dependencies so that
// tests/sniper_kill_credit_tests.cpp can drive it.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace BZROpenShim
{
namespace SniperKillCredit
{
    // GameObject layout (GOG Redux 2.2.301).
    constexpr uint32_t kDistributedObjectOffset = 0x18; // GameObject -> DistributedObject
    // Shell -> owner OBJ76 (FUN_0046D000 returns [shell+0xD8]).
    constexpr uint32_t kShellOwnerObjOffset = 0xD8;
    // OBJ76 -> GameObject (FUN_00479F30 returns [obj+0x8C]).
    constexpr uint32_t kObjGameObjectOffset = 0x8C;
    // DistributedObject vtable: +0x04 GetTeam, +0x30 the OBJ76 record.
    constexpr uint32_t kDoVtblGetTeam = 0x04;
    constexpr uint32_t kDoVtblGetRecord = 0x30;
    // Record flags at OBJ76+0x14; bit 4 marks a death already credited
    // (the snipe receive handler and the pilot-kill path both test and set it).
    constexpr uint32_t kRecordFlagsOffset = 0x14;
    constexpr uint32_t kDeathRecordedFlag = 0x4;
    // KillMessage type for a snipe (receive handler pushes 0x53).
    constexpr char kSnipeKillType = 'S';

    enum class Decision
    {
        Stock,           // victim not local: nothing to add (remote path or no-op)
        NotNetGame,      // single player has no kill credit path at all
        NoShooter,       // shell has no owner: stock sends nothing either
        Unreadable,      // a pointer could not be read: leave it alone
        AlreadyRecorded, // record flag 4 already set: credited elsewhere
        Credit,          // set flag 4, RecordDeath, KillMessage
    };

    inline const char* DecisionName(Decision d)
    {
        switch (d)
        {
        case Decision::Stock: return "stock";
        case Decision::NotNetGame: return "not-net-game";
        case Decision::NoShooter: return "no-shooter";
        case Decision::Unreadable: return "unreadable";
        case Decision::AlreadyRecorded: return "already-recorded";
        case Decision::Credit: return "credit";
        }
        return "?";
    }

    struct Inputs
    {
        bool victimLocal = false;  // stock IsLocal result
        bool netGame = false;      // IsNetGameFlag byte
        bool readOk = false;       // shooter and record reads succeeded
        bool haveShooter = false;  // shell owner OBJ76 non-null (stock SendSnipe gate)
        uint32_t recordFlags = 0;  // victim OBJ76+0x14
    };

    inline Decision Decide(const Inputs& in)
    {
        if (!in.victimLocal)
            return Decision::Stock;
        if (!in.netGame)
            return Decision::NotNetGame;
        if (!in.readOk)
            return Decision::Unreadable;
        if (!in.haveShooter)
            return Decision::NoShooter;
        if ((in.recordFlags & kDeathRecordedFlag) != 0)
            return Decision::AlreadyRecorded;
        return Decision::Credit;
    }
}
}
