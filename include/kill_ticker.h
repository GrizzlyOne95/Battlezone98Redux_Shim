// kill_ticker.h
// BZR Open Shim - kill ticker ("-Tank" above the weapon list)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Visual only. Detection rides the four DamageAlloc wrappers owned by
// hud_feedback.cpp; drawing rides the shared gauge-draw overlay. See
// Docs/KILL_TICKER.md and include/kill_ticker_policy.h.

#pragma once

#include "kill_ticker_policy.h"

namespace BZROpenShim::KillTicker
{
    // Applies [Display] KillTicker. Installs the overlay painter and the
    // weapon-list anchor observer when enabled; clears everything when not.
    // Frame/UI thread. False when the overlay could not be installed.
    bool Configure(bool enabled);
    bool Enabled() noexcept;

    // One damage application, from the DamageAlloc wrappers after the
    // original returned. Copies only; never draws or reads files. `odf` is
    // the victim's ODF name when the attacker is the local player, else "".
    void NoteDamage(const KillSample& sample, const char* odf, bool singlePlayer) noexcept;

    // Frame thread, once per frame: resolves network candidates, turns
    // verified kills into lines (reading unit names) and expires old lines.
    void Tick();

    // Mission/session change: drops lines, candidates and the name cache.
    void ResetMission() noexcept;
}
