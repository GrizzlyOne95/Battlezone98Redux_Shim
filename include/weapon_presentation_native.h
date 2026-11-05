#pragma once
#include "weapon_convergence.h"

namespace BZROpenShim::Hooks
{
    // Candidate native adapter is compiled, but installation stays closed
    // until the Windows qualification checklist in the implementation doc is
    // completed. Defaults and MP policy are independent gates.
    void InstallWeaponPresentationNativeIfRequested() noexcept;
    void RefreshWeaponPresentationNativePoses() noexcept;
    void RetireWeaponPresentationNativeBindings() noexcept;
    void WeaponPresentationNativeSceneBegin() noexcept;
    void WeaponPresentationNativeSceneComplete() noexcept;
    bool WeaponPresentationNativeThreadAllowed() noexcept;
    // 0 absent, 1 fitted port, -1 malformed/ambiguous authored port (suppress).
    int ResolveCraftCasingPort(void* weapon, void* ownerObj76,
        WeaponConvergence::Vec3& offset, WeaponConvergence::Vec3& direction) noexcept;
}
