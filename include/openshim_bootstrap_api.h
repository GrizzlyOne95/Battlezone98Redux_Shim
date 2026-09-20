// openshim_bootstrap_api.h
// BZR Open Shim - the private bootstrap service table.
//
// The one channel from plugins/openshim.dll back into winmm.dll. There are
// only two things the runtime genuinely cannot own, and they are here rather
// than spread across four or five independent exports:
//
//   * logging, because the bootstrap has to log before OpenShim exists and
//     two modules opening openshim.log would mean two session headers, two
//     sharing modes, and an ordering question at every line;
//   * the startup renderer decision, because it is made before the plugin is
//     loaded (see startup_backend_seam.h), plus the pending marker the
//     bootstrap writes as part of it.
//
// This is NOT BZPluginHostApi. BZLoader's host API belongs to the loader and
// its log callback writes bzloader.log; loader diagnostics and OpenShim
// diagnostics stay separate files. A third-party BZLoader plugin has no
// business calling anything here, which is why this table is resolved by name
// from winmm.dll rather than handed out by the loader.
//
// Rules for everything in the table: C linkage, fixed-width scalars, no
// va_list, no variadics, no std::string, no FILE*, no CRT object of any kind
// crossing the boundary. Only a fully formatted UTF-8 message travels.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OPENSHIM_BOOTSTRAP_API_V1 1u

// Levels match BZROpenShim::LogLevel: 0=Debug, 1=Info, 2=Warn, 3=Error.
typedef struct OpenShimBootstrapApiV1
{
    uint32_t structSize;
    uint32_t version;

    // `message` is already formatted and NUL-terminated UTF-8. The caller
    // does the formatting on its own side precisely so no va_list or CRT
    // state crosses. The sink adds the timestamp, pid/tid and level.
    void(__cdecl* logMessage)(
        uint32_t level,
        const char* component,
        const char* message);

    // Copies StartupSeam::StartupRendererResult into the caller's buffer.
    // Returns 0 when `capacity` is under the mandatory prefix. The caller
    // owns the copy; nothing here hands out a pointer into bootstrap memory.
    int32_t(__cdecl* copyStartupRendererResult)(
        void* out,
        uint32_t capacity);

    // Clears the previous-boot evidence marker, which the bootstrap owns
    // because the bootstrap is what writes it.
    void(__cdecl* clearStartupPendingMarker)(void);
} OpenShimBootstrapApiV1;

// The single export winmm.dll publishes for this. Returns NULL for a version
// it cannot satisfy, rather than a partially compatible table.
__declspec(dllexport) const OpenShimBootstrapApiV1* __cdecl
OpenShimBootstrap_GetApi(uint32_t version);

typedef const OpenShimBootstrapApiV1*(__cdecl* OpenShimBootstrap_GetApiFn)(
    uint32_t version);

#ifdef __cplusplus
}
#endif
