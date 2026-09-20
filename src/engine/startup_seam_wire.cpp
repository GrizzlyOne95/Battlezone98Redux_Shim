// startup_seam_wire.cpp
// BZR Open Shim - the parts of the startup seam contract that are pure.
//
// Compiled into BOTH winmm.dll and plugins/openshim.dll. That is safe and
// intended: this is a mapping over the numeric wire space and holds no state,
// so a second copy cannot disagree with the first about anything. Keeping it
// here is what stops the runtime having to call back across the module
// boundary just to render a diagnostic string.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "startup_backend_seam.h"
#include "render_profile_runtime.h"

namespace BZROpenShim::StartupSeam
{
    const char* ArmStatusText(uint32_t armStatus)
    {
        // Order matches BackendSeamArmStatus in startup_backend_seam.cpp. The
        // numbers are the contract; the enum is an implementation detail of
        // the bootstrap side.
        switch (armStatus)
        {
        case 0:  return "not-attempted";
        case 1:  return "armed";
        case 2:  return "no-main-module";
        case 3:  return "unsupported-executable";
        case 4:  return "bad-dos-signature";
        case 5:  return "bad-nt-signature";
        case 6:  return "unsupported-image-size";
        case 7:  return "marker-mismatch";
        case 8:  return "ogremain-absent";
        case 9:  return "config-load-export-absent";
        case 10: return "iat-binding-mismatch";
        case 11: return "iat-protect-failed";
        case 12: return "iat-write-faulted";
        default: return "unknown";
        }
    }
}

namespace BZROpenShim::RenderProfiles
{
    // Pure mapping, so both modules compile it rather than calling
    // across the boundary for a four-line switch.
    const char* RequestedBackendName(RendererBackend backend)
    {
        return backend == RendererBackend::DX11 ? "DX11"
               : backend == RendererBackend::DX9 ? "DX9"
                                                 : "Auto";
    }
}
