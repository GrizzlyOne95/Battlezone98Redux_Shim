#pragma once
#include "hud_feedback_policy.h"

namespace BZROpenShim::HudFeedback
{
    bool ReloadConfig();
    const char* UnavailableReason();
    void Tick();
    void ResetMission() noexcept;
    Settings PreviewSettings(); // copied appearance; does not publish game events
}
