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
// The control panel (ControlPanel render, GOG 0x004A08E0; BZ 1.5
// ControlPanel_Render 0x004C4998) has the same 3 colours in a static
// itemColor table (0x02CC2B8C, filled at 0x004A16CD) and indexes it with the
// item team with no clamp at all: the menu title at 0x004A1745 and each child
// item at 0x004A1A5E. Each load is moved into a thunk that clamps the team to
// 0..2 first, the same mapping as the DrawBuildMenu fix.
//
// The team is BuildItem.team from the menu ODF (InitBuildItem 0x0049F5C0 reads
// it unclamped; leaves inherit it from their parent), so any value a mod ODF
// sets, negative included, reaches both sites. Stock content stays in 0..2.
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

    // Control panel itemColor loads. Each row pins the load plus context; the
    // patched span is the 7-byte `mov reg, [edx*4 + itemColor]`.
    constexpr uint32_t kColorLoadLength = 7;
    constexpr uint32_t kTitleLoadOffset = 3;     // in ControlPanelTitleColorRead
    constexpr uint32_t kChildLoadOffset = 0x10;  // in ControlPanelChildColorRead
    constexpr uint32_t kLoadTableDispOffset = 3; // disp32 inside the load
    constexpr uint32_t kInitTableStoreOffset = 8; // disp32 of the first store in the init row

    // Stock control panel index: none, the raw team.
    inline int StockControlPanelIndex(int team) { return team; }
    // Fixed: the thunk's clamp, the same as the fixed DrawBuildMenu mapping.
    inline int FixedControlPanelIndex(int team) { return ColorIndex(team, kFixedClampMax); }
}
}
