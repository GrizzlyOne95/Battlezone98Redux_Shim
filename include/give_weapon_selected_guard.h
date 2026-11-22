// give_weapon_selected_guard.h -- engine-independent logic for the GiveWeapon
// selected-mask fix (src/patches/give_weapon_selected_guard.cpp).
//
// GiveWeapon (GOG Redux 2.2.301 0x00612F10, __cdecl(GameObject*, WeaponClass*,
// slot), returns al; Lua GiveWeapon reaches it through 0x005CB0D0) has two
// defects:
//
// 1. Its nil-weapon arm clears the weapon pointer and the hardpoint bit
//    (carrier+0x2C, through 0x004A77A0) and the enabled bit (carrier+0x34,
//    0x004D9950), but never the selected bit (carrier+0x30). Only the player's
//    craft rebuilds its selection afterwards (0x0060B650). Any other craft
//    keeps a selected bit for an empty slot, and readers that walk the
//    selected mask then dereference GetWeapon(i) == null, for example the
//    guided-missile scan 0x004F86A0 ([weapon+8] at once) and the person sniper
//    scan in Person::Simulate.
//    Fix: after the nil arm's own clears, Carrier::SetSelected (0x004D9880)
//    is called with the selected mask minus the slot's bit. SetSelected masks
//    with the hardpoint bits and calls Select/Deselect only on non-null
//    weapons, so the emptied slot gets no call.
//
// 2. Its slot test is `slot < 0 && slot >= 5` (cmp [ebp+10h],0 / jge ok /
//    cmp [ebp+10h],5 / jl ok / fail at 0x00612F23), which never rejects. Lua
//    GiveWeapon passes any non-negative slot unchecked (0x00503520 sends a
//    negative slot to the slot-less path 0x005CB050), so slot 5 or more reads
//    a weapon pointer as the hardpoint (carrier+4+slot*4) and builds a weapon
//    on it. Fix: the first jcc becomes `jl fail` (7D 0D -> 7C 06), which makes
//    the test `slot < 0 || slot >= 5`.
//
// Header-only and free of Windows and engine dependencies so that
// tests/give_weapon_selected_guard_tests.cpp can drive it.
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace BZROpenShim
{
namespace GiveWeaponSelected
{
    constexpr int kSlotCount = 5;
    constexpr uint32_t kCarrierSelectedOffset = 0x30;

    inline bool SlotInRange(int slot) { return slot >= 0 && slot < kSlotCount; }

    // The selected mask the nil arm should leave. False when nothing needs
    // writing: slot outside 0..4, or its bit is already clear.
    inline bool SelectedMaskAfterNilGive(uint32_t selected, int slot, uint32_t& out)
    {
        out = selected;
        if (!SlotInRange(slot))
            return false;
        const uint32_t bit = 1u << static_cast<uint32_t>(slot);
        if ((selected & bit) == 0)
            return false;
        out = selected & ~bit;
        return true;
    }

    // Slot range test at 0x00612F23 (19 bytes):
    //   +0  83 7D 10 00     cmp dword ptr [ebp+10h], 0
    //   +4  7D 0D           jge +0Dh  -> +0x13 (0x00612F36, continue)
    //   +6  83 7D 10 05     cmp dword ptr [ebp+10h], 5
    //   +10 7C 07           jl  +07h  -> +0x13 (continue)
    //   +12 32 C0           xor al, al (reject)
    //   +14 E9 rel32        jmp epilogue
    constexpr uint32_t kRangeCheckJccOffset = 4;
    constexpr uint8_t kRangeCheckStockJcc[2] = { 0x7D, 0x0D };  // jge continue
    constexpr uint8_t kRangeCheckFixedJcc[2] = { 0x7C, 0x06 };  // jl  reject (+12)

    // Follows the site's two conditional jumps for a slot, with the first jcc
    // as given. True when the function would reject the slot. Lets the tests
    // prove the 2-byte rewrite without hand-copying its meaning.
    inline bool RangeCheckRejects(const uint8_t (&firstJcc)[2], int slot)
    {
        constexpr int kContinue = 0x13;
        constexpr int kReject = 12;
        // First jcc: compare with 0, ends at +6.
        const bool taken1 = firstJcc[0] == 0x7D ? (slot >= 0) : firstJcc[0] == 0x7C ? (slot < 0) : false;
        int pc = 6;
        if (taken1)
            pc = 6 + static_cast<int8_t>(firstJcc[1]);
        if (pc == kContinue)
            return false;
        if (pc == kReject)
            return true;
        // pc == 6: cmp slot,5 / jl continue (ends at +12).
        if (slot < 5)
            return false;
        return true;
    }
}
}
