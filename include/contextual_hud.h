#pragma once
#include "contextual_hud_policy.h"

namespace BZROpenShim::ContextualHud
{
    bool ReloadConfig();
    const char* UnavailableReason();
    void Tick();
    void ResetMission() noexcept;
    bool ResourceDrawAdaptersNeeded() noexcept;
    float BeginDraw(Group group) noexcept;
    void EndDraw(float previous) noexcept;
    // Direct radar grid geometry bypasses the normal sprite/fill color helpers.
    float RadarDrawOpacity() noexcept;
    // External presentation lease. Adapters suppress only the claimed native
    // draws and bypass OpenShim styling/fading, while command input stays native.
    uint32_t ExternalOwnership() noexcept;
    bool ExternallyOwned(Group group) noexcept;
    uint32_t SetExternalOwnership(uint32_t mask);
}
