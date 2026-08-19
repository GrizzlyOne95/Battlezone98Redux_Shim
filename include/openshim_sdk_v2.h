#pragma once

#include "BZROpenShim.h"

#include <cstdint>

namespace BZROpenShim
{
    // Runtime lifecycle for the v2 SDK/event subsystem. Initialization is
    // intentionally independent of the game's compatibility gate so companion
    // DLLs can query status even when a future/unsupported executable is
    // detected. Version-specific data remains fail-closed in the individual
    // snapshot/event producers.
    void InitializeOpenShimSdkV2();
    void ShutdownOpenShimSdkV2();

    // Internal producer side of the public polling queue. Native hooks should
    // publish compact copied values only; consumers drain them later from a
    // thread/context they control. This keeps arbitrary companion/Lua callbacks
    // out of engine detours.
    void PublishOpenShimEvent(OpenShimEventType type,
                              uint64_t arg0 = 0,
                              uint64_t arg1 = 0,
                              const char* text = nullptr);

    uint64_t GetOpenShimCapabilityMask();

    // Shared implementation used by the exported C entry point and the v2
    // function table.
    bool CaptureDeveloperSnapshot(OpenShimDeveloperSnapshot& outSnapshot);
    bool LogDeveloperSnapshot();
}
