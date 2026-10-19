#pragma once

namespace BZROpenShim::HudFeedback
{
    bool ReloadConfig();
    const char* UnavailableReason();
    void Tick();
    void ResetMission() noexcept;
}
