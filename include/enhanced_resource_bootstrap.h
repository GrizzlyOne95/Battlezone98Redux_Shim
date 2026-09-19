#pragma once

// OpenShim-owned Enhanced resource bootstrap policy.
//
// Pure engine module: no Win32, no Ogre, no process state. The Ogre half
// (resolving ResourceGroupManager exports, creating the group, adding the
// location, initialising it) lives in src/patches/ogre_render_profile.cpp;
// everything here is a deterministic function of its inputs so the state
// machine can be unit-tested without launching the game.
//
// Why this exists
// ---------------
// OpenShim ships the Enhanced renderer payload (the OSE_* .program
// declarations, their HLSL/GLSL sources and the IBL DDS files), but nothing
// registered that payload with Ogre. `bz_resources.cfg` names only
// ./BZ_ASSETS and ./BZ_ASSETS_CORE, so on an install without Campaign
// Reimagined the files sit on disk unparsed and every OSE_* program name is
// absent at runtime -- proved on a live DX11 run where all 81 synthesis
// attempts declined with reason=program-absent. CR's own resource config is
// what pulled the directory in, which is exactly the dependency
// Docs/ENHANCED_RENDERER_MATERIAL_OWNERSHIP.md says must not exist.
//
// The location is NOT hardcoded. `Assets::ProbeEnhancedResourcesAt` already
// searches the game-root developer deployment, addon/, mods/,
// packaged_mods/ and Steam Workshop content, and returns the directory that
// actually validated; the bootstrap registers whatever that probe resolved.

#include <cstdint>
#include <string>
#include <string_view>

namespace BZROpenShim::RenderProfiles::EnhancedBootstrap
{
    // Explicit state machine so the bootstrap runs at most once per process.
    // Attempting prevents concurrent duplicate registration; a failed attempt
    // is as final as a successful one because retrying per draw or per
    // material is exactly the behaviour this must not have.
    enum class BootstrapState : uint8_t
    {
        NotAttempted = 0,
        Attempting,   // one thread owns registration; other callers fail closed
        Ready,        // group registered, initialised, OSE programs resolve
        Unavailable,  // attempted and failed; dependent features stay off
    };

    const char* BootstrapStateName(BootstrapState state) noexcept;

    // Observations the runtime feeds back after each step. Every one is
    // "did this actually succeed", never "should we try".
    struct BootstrapObservations
    {
        bool probeResolvedDirectory = false; // ProbeEnhancedResourcesAt returned a dir
        bool ogreApiResolved = false;        // ResourceGroupManager exports present
        bool groupRegistered = false;        // create + addResourceLocation + initialise
        bool canonicalProgramResolved = false; // an OSE_* program is really there
    };

    // The whole point: Ready requires ALL FOUR, because any one of them
    // failing leaves the OSE namespace absent, and a synthesis path that
    // believes otherwise binds names that do not exist.
    BootstrapState DecideBootstrapState(
        const BootstrapObservations& observations) noexcept;

    // Idempotency gate. Only NotAttempted may run the Ogre work.
    bool ShouldAttemptBootstrap(BootstrapState current) noexcept;

    // Capability gate for dependent features (Enhanced/OSE synthesis).
    bool IsEnhancedCapabilityAvailable(BootstrapState current) noexcept;

    // The Ogre resource group OpenShim owns.
    //
    // Deliberately NOT "Modable": the game clears and re-initialises that
    // group on every mod staging cycle, which would drop OpenShim's payload
    // mid-session. A private group is untouched by that lifecycle.
    const char* ResourceGroupName() noexcept;

    // Ogre archive type for a plain directory.
    const char* ResourceLocationType() noexcept;

    // A program that must exist once the payload is parsed. Verifying one
    // real name is what separates "the group initialised" from "the payload
    // actually declares what we are about to bind": an empty or wrong
    // directory still creates and initialises a group perfectly happily.
    const char* CanonicalProbeProgram() noexcept;

    // Single-line ASCII diagnostics, one per outcome, for once-only logging.
    std::string FormatBootstrapReadyLog(std::string_view resourceDir);
    std::string FormatBootstrapFailedLog(const BootstrapObservations& observations,
                                         std::string_view detail);
} // namespace BZROpenShim::RenderProfiles::EnhancedBootstrap
