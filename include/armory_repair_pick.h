// armory_repair_pick.h
// BZR Open Shim - let a guest pick an allied damaged building for RKIT repair
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // Redirects the one current-health call in the Armory target validator's
    // RKIT branch so a guest's remote copy of a host building reads as damaged
    // when its synced health ratio says so. Always on; fails closed.
    void InitializeArmoryRepairPick();
}
