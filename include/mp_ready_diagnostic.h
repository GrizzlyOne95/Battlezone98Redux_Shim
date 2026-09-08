#pragma once
// mp_ready_diagnostic.h -- explains the main menu's "Not Ready" multiplayer entry.
//
// The stock shell tells the player nothing. The main-menu refresh at
// 0x0078EB50 asks cNetFriends for a readiness code and, for anything other
// than 3, writes the localized string multi_common/"not ready" onto the
// multiplayer button and disables it. It *does* have tooltips for two specific
// causes -- multi_message/"no inet" for code 1 and "no auth" for code 2 -- but
// the getter that feeds it (0x00753810, vtable slot +0x20, shared by
// cNetFriends, cNetFriendsGog and cNetFriendsSteam alike) only ever returns 3
// or 0. Codes 1 and 2 are unreachable, so those tooltips are dead code and the
// player always gets a bare "Not Ready" with no reason attached.
//
// This module reproduces the engine's own decision from the same globals and
// logs *which* term failed, so a user report can be acted on instead of
// guessed at. It patches nothing: every read is byte-guarded against the
// instruction that references the global and wrapped in SEH, and a guard
// mismatch stands the whole diagnostic down rather than reporting a value it
// cannot vouch for.
//
// See reverse_engineering/mp_not_ready_readiness_chain.md for the derivation.

namespace BZROpenShim
{
    // Starts the readiness watcher. Safe to call more than once. Honours
    // [Diagnostics] LogMultiplayerReadiness (default on) and the
    // OPENSHIM_NO_MP_READY_DIAGNOSTIC environment escape hatch.
    void InitializeMpReadyDiagnostic();
}
