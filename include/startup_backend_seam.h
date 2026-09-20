// startup_backend_seam.h
// BZR Open Shim - the bootstrap startup renderer seam.
//
// Unlike the file-I/O seam, this one cannot defer its decision to a provider
// that arrives later. The intercepted Ogre::ConfigFile::load *is* the game's
// read of Ogre.cfg, and the graphics bootstrap reads
// getSetting("Render System") immediately afterwards. A missing plugin cannot
// mean "stock for now, catch up later" -- by then the decision point is gone
// for this boot, and on a warm-cache Steam start the load can be reached in
// about a second, well before any plugin could be hosted.
//
// So the bootstrap owns the whole startup decision and runs it self-
// sufficiently, then publishes a POD record. OpenShim copies that record when
// it initialises and seeds its runtime state from it rather than recomputing
// what already happened.
//
// This is OpenShim-bootstrap plumbing, deliberately NOT part of the BZLoader
// plugin ABI: third-party plugins have no business depending on it. It
// reaches OpenShim through OpenShimBootstrapApi (openshim_bootstrap_api.h).
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace BZROpenShim::StartupSeam
{
    inline constexpr uint32_t kStartupRendererResultVersion = 1u;

    // Write-once snapshot of what the bootstrap decided and did.
    //
    // Every field is a fixed-width integer, on purpose. C++ enum types are
    // perfectly correct while this is one binary, but this record crosses a
    // DLL boundary: the two sides can be built at different times, and an
    // enum whose underlying type or enumerator values drifted would corrupt
    // the reading side silently. The numeric spaces below are the contract;
    // OpenShim converts back to its own enums after copying.
    //
    // Append-only, guarded by structSize. No std::string, no locks, no
    // renderer runtime state, nothing with a destructor.
    struct StartupRendererResult
    {
        uint32_t version;
        uint32_t structSize;

        // RenderProfiles::RendererBackend: 0=Auto, 1=DX9, 2=DX11.
        uint32_t requestedBackend;
        // BackendSelection::RequestSource: 0=None, 1=Persistent, 2=CliOverride.
        uint32_t requestSource;
        // Seam arm outcome, in the order BackendSeamArmStatus declares it.
        // Carried as a number so the runtime renders its own diagnostic text
        // instead of calling back into the bootstrap for a string.
        uint32_t armStatus;

        uint8_t dx9Present;
        uint8_t dx11Present;
        // Whether the Ogre.cfg transport was actually written this boot. The
        // runtime needs this to tell a burned transport from an untouched one
        // when it classifies the observed backend.
        uint8_t transportWritten;
        // Whether the startup selection ran at all. Zero means the seam never
        // reached its call site -- a different build, a failed arm, or a boot
        // that did not go through the qualified path.
        uint8_t selectionRan;
        // The IAT interception was installed at process attach.
        uint8_t seamArmed;
        // The call-site proof passed at the gate: return address, the six
        // post-SteamStub bytes, and an Ogre.cfg argument.
        uint8_t startupSiteValidated;
        uint8_t reserved0;
        uint8_t reserved1;
    };

    static_assert(sizeof(StartupRendererResult) == 28,
                  "StartupRendererResult is a fixed-layout cross-module POD");

    // The numeric spaces above, named so both sides agree without sharing an
    // enum definition.
    inline constexpr uint32_t kBackendAuto = 0u;
    inline constexpr uint32_t kBackendDx9 = 1u;
    inline constexpr uint32_t kBackendDx11 = 2u;

    inline constexpr uint32_t kSourceNone = 0u;
    inline constexpr uint32_t kSourcePersistent = 1u;
    inline constexpr uint32_t kSourceCliOverride = 2u;

    inline constexpr uint32_t kArmNotAttempted = 0u;
    inline constexpr uint32_t kArmArmed = 1u;

    // Diagnostic text for an armStatus value. A pure mapping over the numeric
    // space, so both modules compile it and nothing crosses the boundary just
    // to render a log line.
    const char* ArmStatusText(uint32_t armStatus);

    // Copies the record into the caller's buffer. Returns false when that
    // buffer is smaller than the mandatory prefix.
    //
    // A copy rather than a pointer into bootstrap memory: winmm.dll is pinned
    // so a pointer would be safe, but copying makes the ownership obvious --
    //   bootstrap decides -> publishes once -> plugin copies -> runtime owns.
    bool CopyStartupRendererResult(void* out, uint32_t capacity);

    // Previous-boot evidence marker, owned by the bootstrap because the
    // bootstrap is what writes it. The runtime clears it once it has seen a
    // renderer established. This stays a real call back into the bootstrap.
    void ClearPendingMarker();

    // Runs the startup decision and the Ogre.cfg transport exactly as the
    // intercepted ConfigFile::load does, minus the call-site proof. The gate
    // is the only production caller; this exists so the path that matters
    // most -- no plugin loaded, nothing else initialised -- can be exercised
    // offline. Bootstrap-internal: deliberately NOT part of the bootstrap API
    // table. Not idempotent, because it performs the transport.
    void RunStartupSelectionForTest();
}

namespace BZROpenShim::RenderProfiles
{
    // Bridges used by the seam's own public wrappers. Not for general use.
    const StartupSeam::StartupRendererResult& SeamResultForPublication();
    void ClearPendingMarkerFromRuntime();
    void RunStartupSelectionForTestImpl();
}
