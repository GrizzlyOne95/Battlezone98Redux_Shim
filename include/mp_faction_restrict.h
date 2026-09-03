#pragma once
// mp_faction_restrict.h — optional host-style restriction of the multiplayer
// starting-vehicle list to the stock balanced factions (NSDF + CCA).
//
// This restores the *useful half* of the Battlezone 1.5 "Any Nation" host rule.
// 1.5 shipped two pool files and picked between them:
//     SimpleVehicleList::SimpleVehicleList @1.5 0x00556A2A
//         if (Net::bNations && ItemExists("netveh1.odf")) load "netveh1.odf";
//         else                                            load "netveh.odf";
// `netveh.odf` (Any Nation OFF) was the *restricted* pool; `netveh1.odf` (ON)
// added the CRA craft. Redux 2.2.301 merged the two files into one 43-entry
// all-faction `netveh.odf` and deleted the toggle, so a Redux host has no way
// to get the restricted pool back short of shipping a custom .vxt per map.
//
// See reverse_engineering/any_nation_redux_resolution_20260902.md for the full
// evidence chain, and mp_faction_restrict.cpp for what is actually patched.
//
// Scope: local list construction only. It is NOT synchronized — see the header
// comment in the .cpp. Default OFF, so stock behaviour is untouched.

#include <cstdint>

namespace BZROpenShim { namespace MpFactionRestrict {

    // Nation bucket indices, as the engine itself assigns them from the first
    // character of each ODF name (loader switch at 0x00766C93..0x00766D13).
    enum Nation : int {
        Nation_NSDF     = 0, // 'a'
        Nation_CCA      = 1, // 's'
        Nation_BlackDog = 2, // 'b'
        Nation_CRA      = 3, // 'c'
        Nation_Other    = 4, // anything else (mod/custom factions)
        Nation_Count    = 5
    };

    // True when [Network] StockFactionsOnly is enabled.
    bool IsEnabled();

    // Bitmask of nations that survive pruning, from [Network] StockFactionSet.
    // Default: (1<<Nation_NSDF) | (1<<Nation_CCA).
    uint32_t AllowedNationMask();

    // Resolves the two loader call sites and redirects them. Safe to call more
    // than once; fails closed and logs when anything does not verify.
    void InstallMpFactionRestrictIfPossible();

}} // namespace BZROpenShim::MpFactionRestrict
