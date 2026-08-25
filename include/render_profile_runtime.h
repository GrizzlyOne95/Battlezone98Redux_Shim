#pragma once

// Runtime surface of the OpenShim-owned renderer-profile subsystem. The pure
// decision core lives in render_profile.h/cpp; this layer owns process state,
// openshim.ini persistence, backend observation, the game viewport scheme
// takeover, companion-DLL exports, and lifecycle integration.

#include "render_profile.h"

namespace BZROpenShim::RenderProfiles
{
    // Captures the process command line into an internal fixed buffer. MUST be
    // called from DllMain (DLL_PROCESS_ATTACH), i.e. before game main can run:
    // stock's command-line parser strtok()s the GetCommandLineA() buffer in
    // place, destroying tokens after the first argument for any later reader.
    // The backend-selection seam reads this snapshot instead of the live PEB.
    void CaptureCommandLineSnapshot();

    // Snapshot taken by CaptureCommandLineSnapshot(); nullptr when capture has
    // not happened yet (callers may fall back to GetCommandLineA).
    const char* GetCapturedCommandLine();

    // Seam A arming entry point. MUST be called from DllMain
    // (DLL_PROCESS_ATTACH) — process init is single-threaded then, which makes
    // the IAT swap race-free. Loader-lock-bounded by contract: executable
    // identity checks plus one protected pointer swap; no filesystem, no CRT
    // containers, no waits, no .text reads (SteamStub-safe). The backend
    // transport itself is executed later, on the game thread, from inside the
    // intercepted startup Ogre::ConfigFile::load — strictly before stock reads
    // "Render System=", exactly once per process. Idempotent.
    //
    // Returns true when the seam was armed. Any validation miss fails closed:
    // nothing is hooked and backend selection is pure stock behavior.
    bool InstallStartupBackendSeam();

    // Loads [Graphics] Renderer/RenderProfile from openshim.ini, starts backend
    // observation, evaluates the resolver, installs the viewport scheme-policy
    // takeover when the supported build is present, and validates the deployed
    // Enhanced renderer-resource set. Safe to call before the compatibility
    // gate: address-dependent work fails closed on unsupported builds.
    void InitializeOgreRenderProfiles();

    // Re-reads openshim.ini and re-resolves. Called by the settings UI after a
    // lossless ini write (ShimSettingApplyGroup::RenderProfile).
    void ReloadRenderProfileConfig();

    // Authoritative mission-lifecycle seam: clears any content override so it
    // cannot leak into unrelated subsequent content. Wired into
    // ResetMissionHookOverridesFromBridge(); also exported for companions.
    void ClearContentRenderProfileOverride(const char* context);

    // Applies the effective profile to currently active viewports (scheme
    // rewrite + Glow compositor assertion). THREADING CONTRACT: mutates Ogre
    // state, so it must only run on the game/render thread. Off-thread
    // requesters set s_reapplyPending instead; the viewport scheme hook drains
    // it here on the engine's thread at its next setMaterialScheme call.
    void ReapplyEffectiveProfileToViewports(const char* context);

    namespace Exports
    {
        uint32_t GetRenderApiVersion();
        uint32_t RequestRenderProfile(uint32_t abiRequest);
        uint32_t GetUserRenderProfile();
        uint32_t GetRequestedContentRenderProfile();
        uint32_t GetEffectiveRenderProfile();
        uint32_t GetActiveBackend();
        uint32_t GetRenderCapabilities();
        int SupportsRenderProfile(uint32_t abiProfile);
    }
}
