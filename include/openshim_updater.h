#pragma once

#include <cstdint>
#include <string>

namespace BZROpenShim
{
    enum class OpenShimUpdateState : uint8_t
    {
        Idle,
        WaitingForWorkshop,
        Validating,
        UpToDate,
        Staged,
        Unsupported,
        Failed,
    };

    struct OpenShimUpdateSnapshot
    {
        OpenShimUpdateState state = OpenShimUpdateState::Idle;
        uint64_t generation = 0;
        std::string message;
        bool busy = false;
    };

    // Begin and Poll must run on the game/UI thread because they call the
    // game's SteamUGC-backed Workshop interface. Validation and staging run on
    // an OpenShim worker after the item reports ready.
    bool BeginOpenShimUpdateCheck();
    void PollOpenShimUpdateCheck();
    OpenShimUpdateSnapshot GetOpenShimUpdateSnapshot();
    void CancelOpenShimUpdateCheck(const char* reason);
    void ShutdownOpenShimUpdater();
}
