#pragma once

// Runtime surface of the OpenShim-owned renderer-profile subsystem. The pure
// decision core lives in render_profile.h/cpp; this layer owns process state,
// openshim.ini persistence, backend observation, the game viewport scheme
// takeover, companion-DLL exports, and lifecycle integration.

#include "render_profile.h"

namespace BZROpenShim::RenderProfiles
{
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
    // rewrite + Glow compositor assertion). Returns true when at least one
    // active viewport was found and processed. THREADING CONTRACT: mutates
    // Ogre state, so it must only run on the game/render thread. Off-thread
    // requesters set s_reapplyPending instead; the viewport scheme hook drains
    // it here on the engine's thread at its next setMaterialScheme call.
    bool ReapplyEffectiveProfileToViewports(const char* context);

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
