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
}
