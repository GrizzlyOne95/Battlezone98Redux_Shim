// armory_repair_pick_policy.h
// BZR Open Shim - health value the Armory repair pick compares (pure logic)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cmath>

namespace BZROpenShim
{
    // The Armory target validator's RKIT branch asks "current health < max
    // health". On a guest's copy of a host-owned building the current health
    // (+0x204) stays at max while the synced health ratio (+0x200) moves, so
    // the stock test never passes. Returns the lower of the stored current
    // health and the health implied by the ratio; the stored value alone when
    // the ratio or max cannot be trusted.
    inline float ArmoryRepairPickHealth(float current, float ratio, float maxHealth)
    {
        if (!(maxHealth > 0.0f) || !(ratio > 0.0f) || !std::isfinite(ratio) || !std::isfinite(maxHealth))
            return current;
        const float derived = ratio >= 1.0f ? maxHealth : ratio * maxHealth;
        return derived < current ? derived : current;
    }
}
