#pragma once

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
}
