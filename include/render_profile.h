#pragma once

// OpenShim renderer-profile ownership model.
//
// OpenShim owns renderer CAPABILITY and POLICY state: which backend is active,
// which visual profile (Retro/Redux/Enhanced) is effective, and why any
// fallback happened. EXU owns content INTENT and forwards it across the
// optional winmm bridge; Campaign Reimagined owns art direction and simply
// requests profiles where desired. Requested state and effective state are
// deliberately distinct: nothing here silently conflates what someone asked
// for with what the process can actually honor.
//
// The resolution core in src/engine/render_profile.cpp is intentionally free
// of Win32/Ogre dependencies so the decision table stays unit-testable
// (tests/render_profile_tests.cpp, scripts/run_render_profile_tests.ps1).
//
// Stable companion-DLL ABI values live at the bottom of this file; they mirror
// the pattern used by OpenShimGetBzrDistribution/OpenShimSetBZRNetNickname and
// must never be renumbered once EXU learns them.

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace BZROpenShim::RenderProfiles
{
    // User-selectable backend preference. Auto means "use whatever the game
    // picks this session" and is the safe default; explicit selections are
    // restart-scoped preferences recorded in openshim.ini, not live switches.
    enum class RendererBackend : uint8_t
    {
        Auto = 0,
        DX9 = 1,
        DX11 = 2,
    };

    // The backend actually observed in the process. Never Auto.
    enum class ActiveBackend : uint8_t
    {
        DX9 = 0,
        DX11 = 1,
    };

    // Rendering policy layered over the selected backend.
    //
    // Redux preserves stock Battlezone 98 Redux rendering behavior as closely
    // as practical on the selected backend; it is the compatibility baseline.
    //
    // Enhanced is the canonical OpenShim graphics upgrade. It is supported on
    // BOTH backends and is capability-dependent rather than all-or-nothing:
    // DX11 carries the primary modern feature set (linear lighting, enhanced
    // terrain/object shader paths, modern PSSM behavior, contribution-ranked
    // light selection), while DX9 retains its proven legacy enhancements
    // (normal-map sharpening and the SM3 enhanced technique delegates).
    // DX9 Enhanced is feature-frozen except for correctness/crash fixes; new
    // visual development targets DX11 first.
    //
    // Retro deliberately reproduces a more classic Battlezone presentation via
    // the og-* material scheme family. It inherits whatever those schemes
    // define; see Docs/OPENSHIM_RENDER_PROFILE_ARCHITECTURE.md for its current
    // experimental status.
    enum class Profile : uint8_t
    {
        Retro = 0,
        Redux = 1,
        Enhanced = 2,
    };

    // Content-facing request space (EXU bridge ABI). Inherit means "follow the
    // user's openshim.ini preference"; anything else is a mission/session-
    // scoped override that OpenShim clears on the authoritative mission
    // lifecycle seam so it can never leak into unrelated content.
    enum class ContentRequest : uint8_t
    {
        Inherit = 0,
        Retro = 1,
        Redux = 2,
        Enhanced = 3,
    };

    // Per-feature Enhanced capability bits (stable ABI order). Append-only:
    // never renumber or remove an existing bit once companions ship.
    enum EnhancedCapability : uint32_t
    {
        CapNone = 0u,
        CapSchemeRewrite = 1u << 0,   // profile-driven en-/og- scheme policy active
        CapNormalSharpening = 1u << 1, // distance-faded normal-map sharpening
        CapLinearLighting = 1u << 2,   // linear-space lighting/colorspace path
        CapTerrainEnhanced = 1u << 3,  // enhanced terrain shader family
        CapObjectEnhanced = 1u << 4,   // enhanced object/base shader family
        CapModernPssm = 1u << 5,       // cascade blending/comparison PCF/bias strategy
        CapLightSelection = 1u << 6,   // contribution-ranked enhanced light ordering
        CapIblResources = 1u << 7,     // neutral IBL/BRDF-LUT resource set resolvable

        // MANDATORY Enhanced renderer-resource set verified on disk (programs,
        // shader sources, textures under openshim\renderer\enhanced). This is
        // the hard gate: without it Enhanced cannot render as designed and
        // must fall back to Redux regardless of backend. Distinct from
        // CapIblResources, which reflects the OPTIONAL image-based lighting
        // extras whose absence only disables IBL-specific visuals.
        CapEnhancedResources = 1u << 8,
    };

    struct ResolverInput
    {
        RendererBackend requestedBackend = RendererBackend::Auto;
        ActiveBackend detectedBackend = ActiveBackend::DX9;

        Profile userProfile = Profile::Redux;

        bool contentOverridePresent = false;
        ContentRequest contentOverride = ContentRequest::Inherit;

        // Capability mask for the DETECTED backend plus resource validation
        // results; produced by CapabilitiesForBackend() optionally OR'd with
        // runtime resource findings before resolution.
        uint32_t capabilityMask = 0;
    };

    struct ResolverResult
    {
        ActiveBackend effectiveBackend = ActiveBackend::DX9;
        Profile effectiveProfile = Profile::Redux;

        // True when something had to give: either the requested backend was
        // not the active one this session, or the winning profile could not
        // be honored and degraded to Redux. Never set for a clean match.
        bool fellBack = false;

        // Human-readable fallback reason; empty when fellBack is false.
        // Always ASCII, bounded, suitable for one log line / UI status.
        char reason[160] = {};
    };

    // Pure resolution core. Hard compatibility/safety constraints win first
    // (an impossible backend request is reported, an unhonorable profile
    // falls back to Redux with a reason), then the EXU content override wins
    // over the user's openshim.ini preference. Invalid enum inputs resolve
    // deterministically to their documented resting values instead of UB.
    ResolverResult ResolveRenderProfile(const ResolverInput& input);

    // Capability sets. These encode what each backend can honor TODAY given
    // the shipped renderer resources; runtime resource problems REMOVE bits
    // (they are never added here). DX9 reports its frozen legacy set; DX11
    // reports the full modern set minus anything resource validation dropped.
    uint32_t CapabilitiesForBackend(ActiveBackend backend);

    inline bool HasCapability(uint32_t mask, EnhancedCapability cap) noexcept
    {
        return (mask & static_cast<uint32_t>(cap)) != 0u;
    }

    // Enhanced is only honorable when BOTH hard requirements hold: the scheme
    // policy layer must be installed AND the mandatory resource set verified.
    // Retro requires only the scheme layer. Shared by the resolver and the
    // runtime's SupportsRenderProfile so both can never disagree.
    inline bool ProfileRequirementsMet(Profile profile, uint32_t mask) noexcept
    {
        switch (profile)
        {
        case Profile::Enhanced:
            return HasCapability(mask, CapSchemeRewrite) &&
                   HasCapability(mask, CapEnhancedResources);
        case Profile::Retro:
            return HasCapability(mask, CapSchemeRewrite);
        case Profile::Redux:
        default:
            return true;
        }
    }

    // --- material-scheme policy (shared by the runtime hook and tests) -----

    // The engine's native quality schemes. Everything else is either prefixed
    // by us (en-/og-) or foreign (custom mods), and foreign schemes must fail
    // open untouched.
    bool IsModernMaterialScheme(std::string_view scheme);

    // Strips a recognized en-/og- prefix and validates the remainder against
    // the known modern families; empty/unknown input yields lastModern when
    // provided (mirrors the engine habit of reasserting the previous quality),
    // otherwise kDefaultModernScheme.
    std::string_view NormalizeModernMaterialScheme(std::string_view scheme,
                                                   std::string_view lastModern = {});

    std::string_view DefaultModernMaterialScheme();

    // Policy mapping: which prefix (if any) the effective profile adds.
    // Redux -> none ("high-pssm"), Enhanced -> "en-", Retro -> "og-".
    // Returns the composed scheme into outScheme; false when the modern base
    // was unrecognized (caller must pass the original through unchanged).
    bool BuildMaterialSchemeForProfile(Profile profile,
                                       std::string_view modernBase,
                                       char* outScheme,
                                       size_t outCapacity);

    // Classifies a full scheme name back to its owning profile; unknown or
    // unprefixed modern names report Redux (the engine-native baseline).
    Profile ProfileForMaterialScheme(std::string_view scheme);

    // --- stable companion-DLL ABI ------------------------------------------
    //
    // Mirrored independently by ExtraUtilities' src/OpenShimBridge.h; do not
    // link companions against these headers and do not renumber.
    namespace Abi
    {
        constexpr uint32_t kRenderApiVersion = 1;

        // Content request space (OpenShimRequestRenderProfile argument).
        constexpr uint32_t kRequestInherit = 0u;
        constexpr uint32_t kRequestRetro = 1u;
        constexpr uint32_t kRequestRedux = 2u;
        constexpr uint32_t kRequestEnhanced = 3u;

        // Profile getter results (OpenShimGet*RenderProfile).
        constexpr uint32_t kProfileUnknown = 0u;
        constexpr uint32_t kProfileRetro = 1u;
        constexpr uint32_t kProfileRedux = 2u;
        constexpr uint32_t kProfileEnhanced = 3u;

        // OpenShimRequestRenderProfile results. Semantics are TRUTHFUL
        // application states, never viewport-existence guesses:
        //   AppliedLive      - the engine-thread deferred-apply drain has run
        //                      WITH this request's publish epoch included and
        //                      found viewports to apply to.
        //   StoredDeferred   - request accepted and stored; the engine-thread
        //                      hook has not yet performed the apply pass (no
        //                      drain ran yet, or none found a viewport).
        //   RejectedValue    - the ABI value is not a known ContentRequest.
        //   UnsupportedBuild - stored for coherence, but this profile can
        //                      never drive rendering on the current build
        //                      (scheme-policy layer inactive); Enhanced/Retro
        //                      requests on unsupported builds receive this.
        // Callers must treat any unknown nonzero value as not-applied.
        constexpr uint32_t kRequestStatusAppliedLive = 0u;
        constexpr uint32_t kRequestStatusStoredDeferred = 1u; // awaiting engine-thread apply
        constexpr uint32_t kRequestStatusRejectedValue = 2u;
        constexpr uint32_t kRequestStatusUnsupportedBuild = 3u;

        bool ProfileToAbi(Profile profile, uint32_t& outValue);
        bool ProfileFromAbi(uint32_t value, Profile& outProfile);
        bool RequestFromAbi(uint32_t value, ContentRequest& outRequest);
    }
}
