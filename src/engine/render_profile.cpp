// Pure renderer-profile resolution core. No Win32, no Ogre, no process state:
// everything here is a deterministic function of its inputs so the decision
// table can be unit-tested without launching the game.

#include "render_profile.h"

#include <cstdarg>
#include <cstdio>

namespace BZROpenShim::RenderProfiles
{
    namespace
    {
        constexpr std::string_view kModernSchemes[] = {
            "high-pssm", "high", "high-noshadow",
            "medium-pssm", "medium", "medium-noshadow",
            "low-pssm", "low", "low-noshadow",
            "lowest-pssm", "lowest", "lowest-noshadow",
        };

        void SetReason(ResolverResult& result, const char* fmt, ...)
        {
            va_list args;
            va_start(args, fmt);
            std::vsnprintf(result.reason, sizeof(result.reason), fmt, args);
            va_end(args);
        }

        bool IsValidEnum(uint8_t value, uint8_t maxValue)
        {
            return value <= maxValue;
        }
    }

    bool IsModernMaterialScheme(std::string_view scheme)
    {
        for (const std::string_view candidate : kModernSchemes)
        {
            if (scheme == candidate)
            {
                return true;
            }
        }
        return false;
    }

    std::string_view DefaultModernMaterialScheme()
    {
        return kModernSchemes[0]; // "high-pssm": the engine's default quality
    }

    std::string_view NormalizeModernMaterialScheme(std::string_view scheme,
                                                   std::string_view lastModern)
    {
        if (scheme.empty())
        {
            return !lastModern.empty() && IsModernMaterialScheme(lastModern)
                ? lastModern
                : DefaultModernMaterialScheme();
        }

        if (scheme.size() > 3 && (scheme.starts_with("og-") || scheme.starts_with("en-")))
        {
            scheme.remove_prefix(3);
        }

        if (IsModernMaterialScheme(scheme))
        {
            return scheme;
        }

        return !lastModern.empty() && IsModernMaterialScheme(lastModern)
            ? lastModern
            : DefaultModernMaterialScheme();
    }

    Profile ProfileForMaterialScheme(std::string_view scheme)
    {
        if (scheme.starts_with("en-"))
        {
            return Profile::Enhanced;
        }
        if (scheme.starts_with("og-"))
        {
            return Profile::Retro;
        }
        // Unprefixed modern and foreign schemes alike render through the
        // engine-native baseline; only our prefixes are policy-owned.
        return Profile::Redux;
    }

    bool BuildMaterialSchemeForProfile(Profile profile,
                                       std::string_view modernBase,
                                       char* outScheme,
                                       size_t outCapacity)
    {
        if (outScheme == nullptr || outCapacity == 0)
        {
            return false;
        }

        switch (profile)
        {
        case Profile::Enhanced:
        case Profile::Retro:
        {
            const std::string_view prefix = (profile == Profile::Enhanced) ? "en-" : "og-";
            if (prefix.size() + modernBase.size() + 1 > outCapacity)
            {
                return false;
            }
            std::snprintf(outScheme, outCapacity, "%.*s%.*s",
                          static_cast<int>(prefix.size()), prefix.data(),
                          static_cast<int>(modernBase.size()), modernBase.data());
            return true;
        }
        case Profile::Redux:
        default:
            if (modernBase.size() + 1 > outCapacity)
            {
                return false;
            }
            std::snprintf(outScheme, outCapacity, "%.*s",
                          static_cast<int>(modernBase.size()), modernBase.data());
            return true;
        }
    }

    uint32_t CapabilitiesForBackend(ActiveBackend backend)
    {
        // Both backends carry the distance-faded normal-map sharpening and the
        // scheme-policy layer: the en-/og- techniques resolve to SM4 delegates
        // on DX11 and SM3 delegates on DX9.
        uint32_t mask = static_cast<uint32_t>(CapSchemeRewrite) |
                        static_cast<uint32_t>(CapNormalSharpening);

        if (backend == ActiveBackend::DX11)
        {
            mask |= static_cast<uint32_t>(CapLinearLighting) |
                    static_cast<uint32_t>(CapTerrainEnhanced) |
                    static_cast<uint32_t>(CapObjectEnhanced) |
                    static_cast<uint32_t>(CapModernPssm) |
                    static_cast<uint32_t>(CapLightSelection);
        }

        // CapIblResources is deliberately NOT granted here: it reflects a
        // runtime resource-validation finding, not a backend property. The
        // runtime ORs it in when the deployed Enhanced resource set verifies.
        return mask;
    }

    ResolverResult ResolveRenderProfile(const ResolverInput& input)
    {
        ResolverResult result;

        // --- backend: requested preference vs observed reality -------------
        result.effectiveBackend = input.detectedBackend;

        const bool requestedValid =
            IsValidEnum(static_cast<uint8_t>(input.requestedBackend),
                        static_cast<uint8_t>(RendererBackend::DX11));
        const bool detectedValid =
            IsValidEnum(static_cast<uint8_t>(input.detectedBackend), 1u);

        if (!detectedValid)
        {
            // Corrupt runtime state must never escalate into an invalid enum
            // leaving this unit; DX9 is the engine's historical baseline.
            result.effectiveBackend = ActiveBackend::DX9;
            result.fellBack = true;
            SetReason(result, "invalid detected backend state; assuming DX9");
        }
        else if (requestedValid &&
                 input.requestedBackend != RendererBackend::Auto &&
                 (input.requestedBackend == RendererBackend::DX9) !=
                     (input.detectedBackend == ActiveBackend::DX9))
        {
            // The preference is honored at the next launch (restart-scoped);
            // report the divergence instead of hiding it behind the effective
            // value. Not a failure: the active session simply has not caught
            // up yet.
            result.fellBack = true;
            SetReason(result, "%s renderer requested; restart required to apply (session is on %s)",
                      input.requestedBackend == RendererBackend::DX11 ? "DX11" : "DX9",
                      input.detectedBackend == ActiveBackend::DX11 ? "DX11" : "DX9");
        }

        // --- profile: hard constraints, then content intent, then user -----
        Profile winning = Profile::Redux;

        const bool overridePresent =
            input.contentOverridePresent &&
            IsValidEnum(static_cast<uint8_t>(input.contentOverride), 3u);

        if (!overridePresent || input.contentOverride == ContentRequest::Inherit)
        {
            winning = IsValidEnum(static_cast<uint8_t>(input.userProfile), 2u)
                ? input.userProfile
                : Profile::Redux;
        }
        else
        {
            switch (input.contentOverride)
            {
            case ContentRequest::Retro:
                winning = Profile::Retro;
                break;
            case ContentRequest::Enhanced:
                winning = Profile::Enhanced;
                break;
            case ContentRequest::Redux:
            case ContentRequest::Inherit:
            default:
                winning = Profile::Redux;
                break;
            }
        }

        // Capability validation applies regardless of who asked: a mission
        // cannot resurrect a capability the session lacks.
        if (winning == Profile::Enhanced &&
            !HasCapability(input.capabilityMask, CapSchemeRewrite))
        {
            result.fellBack = true;
            SetReason(result, "Enhanced unavailable: scheme policy layer inactive");
            winning = Profile::Redux;
        }

        result.effectiveProfile = winning;
        return result;
    }

    namespace Abi
    {
        bool ProfileToAbi(Profile profile, uint32_t& outValue)
        {
            switch (profile)
            {
            case Profile::Retro:
                outValue = kProfileRetro;
                return true;
            case Profile::Redux:
                outValue = kProfileRedux;
                return true;
            case Profile::Enhanced:
                outValue = kProfileEnhanced;
                return true;
            default:
                outValue = kProfileUnknown;
                return false;
            }
        }

        bool ProfileFromAbi(uint32_t value, Profile& outProfile)
        {
            switch (value)
            {
            case kProfileRetro:
                outProfile = Profile::Retro;
                return true;
            case kProfileRedux:
                outProfile = Profile::Redux;
                return true;
            case kProfileEnhanced:
                outProfile = Profile::Enhanced;
                return true;
            default:
                return false;
            }
        }

        bool RequestFromAbi(uint32_t value, ContentRequest& outRequest)
        {
            switch (value)
            {
            case kRequestInherit:
                outRequest = ContentRequest::Inherit;
                return true;
            case kRequestRetro:
                outRequest = ContentRequest::Retro;
                return true;
            case kRequestRedux:
                outRequest = ContentRequest::Redux;
                return true;
            case kRequestEnhanced:
                outRequest = ContentRequest::Enhanced;
                return true;
            default:
                return false;
            }
        }
    }
}
