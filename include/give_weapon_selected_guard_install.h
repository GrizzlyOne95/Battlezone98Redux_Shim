#pragma once
// Installer for the GiveWeapon selected-mask fix. See give_weapon_selected_guard.h.

namespace BZROpenShim
{
    namespace GiveWeaponSelected
    {
        // GiveWeapon(h, nil, slot) also clears the slot's selected bit, and
        // GiveWeapon rejects slots outside 0..4. Fail-closed: any byte-guard
        // mismatch leaves the engine untouched. Safe to call repeatedly.
        void InstallGiveWeaponSelectedGuardIfPossible();
    }
}
