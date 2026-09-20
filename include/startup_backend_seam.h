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
// sufficiently, then publishes a POD record. OpenShim reads that record when
// it initialises and seeds its runtime state from it rather than
// recomputing what already happened.
//
// This is OpenShim-bootstrap plumbing, deliberately NOT part of the BZLoader
// plugin ABI: third-party plugins have no business depending on it.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

#include "backend_selection.h"
#include "render_profile.h"

namespace BZROpenShim::StartupSeam
{
    inline constexpr uint32_t kStartupRendererResultVersion = 1u;

    // Write-once snapshot of what the bootstrap decided and did. Plain data
    // only: no std::string, no locks, no renderer-profile runtime state, and
    // nothing with a destructor. Append-only, guarded by structSize on the
    // same terms as the other tables in this codebase.
    struct StartupRendererResult
    {
        uint32_t version;
        uint32_t structSize;

        // The request this boot resolved to, and where it came from.
        RenderProfiles::RendererBackend requested;
        BackendSelection::RequestSource source;

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
    };

    // The record. Never null; fields are meaningless until selectionRan is 1.
    const StartupRendererResult* GetStartupRendererResult();

    // Previous-boot evidence marker, owned by the bootstrap because the
    // bootstrap is what writes it. The runtime clears it once it has seen a
    // renderer established.
    void ClearPendingMarker();

    // Human-readable arm status for the runtime's diagnostics.
    const char* ArmStatusText();

    // Runs the startup decision and the Ogre.cfg transport exactly as the
    // intercepted ConfigFile::load does, minus the call-site proof. The gate
    // is the only production caller; this is exposed so the path that matters
    // most -- no plugin loaded, nothing else initialised -- can be exercised
    // offline instead of only in a live game. Not idempotent: it performs the
    // transport, so a test must control the working directory.
    void RunStartupSelectionForTest();
}

namespace BZROpenShim::RenderProfiles
{
    // Bridges used by the seam's own public wrappers. Not for general use.
    const StartupSeam::StartupRendererResult& SeamResultForPublication();
    void ClearPendingMarkerFromRuntime();
    const char* SeamArmStatusTextForPublication();
    void RunStartupSelectionForTestImpl();
}
