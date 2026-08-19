#pragma once

#include "BZROpenShim.h"

#include <cstdint>

namespace BZROpenShim
{
    // Returns the native UI sub-API for the requested version (0 = latest).
    // Availability is runtime-gated by the compatible Redux build and the
    // already-resolved cUI constructor/mutation bindings.
    const OpenShimNativeUiApiV1* GetOpenShimNativeUiApi(uint32_t requestedVersion);

    // Process-shutdown bookkeeping only. Engine-owned cUI children are not
    // destructed here; their owning Redux screen tears them down normally.
    void ShutdownNativeUi();
}
