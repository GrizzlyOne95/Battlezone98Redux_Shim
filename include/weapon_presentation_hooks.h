#pragma once

#include "weapon_presentation.h"

namespace BZROpenShim::Hooks
{
    // Internal only: no SDK export, public shot event or multiplayer API.
    // The native adapter calls this only after its call ABI, signature,
    // ownership and renderer update ordering have been qualified. Its backend
    // must remain alive for the process lifetime, including retryable cleanup.
    // Its installer stays closed pending the documented Windows qualification.
    bool RegisterQualifiedWeaponPresentationBackend(
        WeaponPresentation::Backend& backend, WeaponPresentation::Settings settings);
    WeaponPresentation::Runtime* TryGetSingleplayerWeaponPresentationRuntime() noexcept;

    void RefreshWeaponPresentationState() noexcept;
    void WeaponPresentationMissionRunStateChanged(bool running) noexcept;
    void WeaponPresentationSceneTeardownBegin() noexcept;
    void WeaponPresentationSceneTeardownComplete() noexcept;
    void ResetWeaponPresentationState() noexcept;
}
