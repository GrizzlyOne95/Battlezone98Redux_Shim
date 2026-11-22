// build_menu_team_color.h -- engine-independent logic for the build menu team
// colour fix (src/patches/build_menu_team_color.cpp).
//
// PathDisplay::DrawBuildMenu (GOG Redux 2.2.301 0x0059B550) colours each build
// item by its team (+0x14 of the 0x20-byte item) from a 3-entry local array
// at [ebp-10h]: white (0x0091755C), green (0x009175B0), red (0x0091757C),
// stored at 0x0059B649. It clamps the team with Clamp(team, 0, 3) (0x00453D10,
// push 3 at 0x0059B6F6), so team 3 or more reads [ebp-4], the stack cookie,
// as a font colour. BZ 1.5 had the same off-by-one (local_28[3], clamp to 3).
// Fix: the clamp maximum becomes 2, so team 3 and up draw red like team 2.
//
// Header-only and free of engine dependencies for
// tests/build_menu_team_color_tests.cpp.
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace BZROpenShim
{
namespace BuildMenuTeamColor
{
    constexpr int kColorCount = 3;
    constexpr uint8_t kStockClampMax = 3;
    constexpr uint8_t kFixedClampMax = 2;
    // The clamp maximum is the imm8 of `push 3` (6A 03) at the row start.
    constexpr uint32_t kClampMaxImmOffset = 1;

    // 0x00453D10: Clamp(value, lo, hi) -- below lo gives lo, above hi gives hi.
    inline int EngineClamp(int value, int lo, int hi)
    {
        if (value < lo)
            return lo;
        if (value > hi)
            return hi;
        return value;
    }

    inline int ColorIndex(int team, int clampMax) { return EngineClamp(team, 0, clampMax); }
}
}
