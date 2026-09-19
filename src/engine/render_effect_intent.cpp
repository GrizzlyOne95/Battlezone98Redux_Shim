// Render-effect intent store. See include/render_effect_intent.h for the
// contract and for why no effect is supported yet.
//
// Everything here is engine-independent on purpose: the whole
// requested/supported/effective decision is testable without a game, a
// renderer or Windows. tests/render_effect_intent_tests.cpp is the coverage.

#include "render_effect_intent.h"

#include <array>
#include <cmath>
#include <mutex>

namespace BZROpenShim::RenderEffects
{
    namespace
    {
        constexpr size_t kEffectCount = 3;   // Ssao, DepthHaze, SoftParticles
        constexpr size_t kParamCount = 5;    // Strength, Radius, FadeStart, FadeEnd, Quality

        struct EffectState
        {
            bool requested = false;
            Provider provider{};
            bool hasProvider = false;
            std::array<float, kParamCount> params{};
            std::array<bool, kParamCount> paramSet{};
        };

        // The exports are called from mission script threads while a renderer
        // may be reading the same state from the engine thread. Provider
        // callbacks are always invoked with this released so a provider can
        // call back in without deadlocking.
        std::mutex g_lock;
        std::array<EffectState, kEffectCount> g_effects{};

        // Effect and parameter ids are 1-based and contiguous, which keeps the
        // store a flat array instead of a map. The bounds checks below are what
        // makes that safe against an arbitrary uint32_t from a companion.
        bool EffectIndex(uint32_t effectId, size_t& outIndex)
        {
            if (effectId < Abi::kEffectSsao || effectId > Abi::kEffectSoftParticles)
            {
                return false;
            }
            outIndex = static_cast<size_t>(effectId - Abi::kEffectSsao);
            return true;
        }

        bool ParamIndex(uint32_t paramId, size_t& outIndex)
        {
            if (paramId < Abi::kParamStrength || paramId > Abi::kParamQuality)
            {
                return false;
            }
            outIndex = static_cast<size_t>(paramId - Abi::kParamStrength);
            return true;
        }

        bool ProviderIsComplete(const Provider& provider)
        {
            // A partial provider would mean the status query has to guess, so
            // registration is all-or-nothing.
            return provider.IsSupported != nullptr
                && provider.UnsupportedReason != nullptr
                && provider.ApplyEnabled != nullptr
                && provider.ApplyFloat != nullptr
                && provider.IsEffective != nullptr;
        }

        uint32_t NormaliseReason(uint32_t reason)
        {
            // A provider that invents a code must not be able to put an
            // unrecognised value in front of a companion.
            switch (reason)
            {
            case Abi::kReasonEffective:
            case Abi::kReasonNotRequested:
            case Abi::kReasonUnsupportedRenderer:
            case Abi::kReasonSceneDepthUnavailable:
            case Abi::kReasonUnsupportedBuild:
            case Abi::kReasonNotImplemented:
            case Abi::kReasonUnknownEffect:
            case Abi::kReasonPending:
                return reason;
            default:
                return Abi::kReasonNotImplemented;
            }
        }
    }

    float ClampParameter(uint32_t paramId, float value)
    {
        // Ranges are generous: they exist to keep a typo or a runaway mission
        // script from handing a renderer a value that would produce a
        // pathological cost, not to express taste. A provider is free to
        // narrow them further.
        switch (paramId)
        {
        case Abi::kParamStrength:
            return value < 0.0f ? 0.0f : (value > 4.0f ? 4.0f : value);
        case Abi::kParamRadius:
            return value < 0.01f ? 0.01f : (value > 64.0f ? 64.0f : value);
        case Abi::kParamFadeStart:
        case Abi::kParamFadeEnd:
            return value < 0.0f ? 0.0f : (value > 100000.0f ? 100000.0f : value);
        case Abi::kParamQuality:
            return value < 0.0f ? 0.0f : (value > 3.0f ? 3.0f : value);
        default:
            return value;
        }
    }

    bool IsKnownEffect(uint32_t effectId)
    {
        size_t index = 0;
        return EffectIndex(effectId, index);
    }

    bool IsKnownParameter(uint32_t paramId)
    {
        size_t index = 0;
        return ParamIndex(paramId, index);
    }

    uint32_t GetApiVersion()
    {
        return Abi::kRenderEffectApiVersion;
    }

    bool RegisterProvider(uint32_t effectId, const Provider& provider)
    {
        size_t index = 0;
        if (!EffectIndex(effectId, index) || !ProviderIsComplete(provider))
        {
            return false;
        }

        // Whatever the mission already asked for has to be replayed into the
        // new provider, or an effect requested before the renderer was ready
        // would stay silently off forever.
        bool requested = false;
        std::array<float, kParamCount> params{};
        std::array<bool, kParamCount> paramSet{};
        {
            std::lock_guard<std::mutex> guard(g_lock);
            EffectState& state = g_effects[index];
            state.provider = provider;
            state.hasProvider = true;
            requested = state.requested;
            params = state.params;
            paramSet = state.paramSet;
        }

        if (provider.IsSupported(provider.context))
        {
            for (size_t i = 0; i < kParamCount; ++i)
            {
                if (paramSet[i])
                {
                    provider.ApplyFloat(
                        provider.context,
                        static_cast<uint32_t>(Abi::kParamStrength + i),
                        params[i]);
                }
            }
            provider.ApplyEnabled(provider.context, requested);
        }

        return true;
    }

    bool UnregisterProvider(uint32_t effectId)
    {
        size_t index = 0;
        if (!EffectIndex(effectId, index))
        {
            return false;
        }

        std::lock_guard<std::mutex> guard(g_lock);
        g_effects[index].provider = Provider{};
        g_effects[index].hasProvider = false;
        return true;
    }

    uint32_t SetEnabled(uint32_t effectId, bool enabled)
    {
        size_t index = 0;
        if (!EffectIndex(effectId, index))
        {
            return Abi::kResultRejectedEffect;
        }

        Provider provider{};
        bool hasProvider = false;
        {
            std::lock_guard<std::mutex> guard(g_lock);
            EffectState& state = g_effects[index];
            state.requested = enabled;
            provider = state.provider;
            hasProvider = state.hasProvider;
        }

        if (hasProvider && provider.IsSupported(provider.context))
        {
            provider.ApplyEnabled(provider.context, enabled);
        }

        // Accepted means recorded. Whether it is now running is a separate
        // question with a separate answer.
        return Abi::kResultAccepted;
    }

    uint32_t SetFloat(uint32_t effectId, uint32_t paramId, float value)
    {
        size_t effectIndex = 0;
        if (!EffectIndex(effectId, effectIndex))
        {
            return Abi::kResultRejectedEffect;
        }

        size_t paramIndex = 0;
        if (!ParamIndex(paramId, paramIndex))
        {
            return Abi::kResultRejectedParam;
        }

        // NaN and infinity are rejected rather than clamped: they mean the
        // caller computed something wrong, and silently substituting a number
        // would hide it.
        if (!std::isfinite(value))
        {
            return Abi::kResultRejectedValue;
        }

        const float clamped = ClampParameter(paramId, value);

        Provider provider{};
        bool hasProvider = false;
        {
            std::lock_guard<std::mutex> guard(g_lock);
            EffectState& state = g_effects[effectIndex];
            state.params[paramIndex] = clamped;
            state.paramSet[paramIndex] = true;
            provider = state.provider;
            hasProvider = state.hasProvider;
        }

        if (hasProvider && provider.IsSupported(provider.context))
        {
            provider.ApplyFloat(provider.context, paramId, clamped);
        }

        return Abi::kResultAccepted;
    }

    bool GetStatus(uint32_t effectId, Abi::StatusV1* status)
    {
        if (status == nullptr || status->size < sizeof(Abi::StatusV1))
        {
            return false;
        }

        status->size = sizeof(Abi::StatusV1);
        status->version = Abi::kStatusVersion;
        status->requested = 0;
        status->supported = 0;
        status->effective = 0;
        status->reasonCode = Abi::kReasonUnknownEffect;

        size_t index = 0;
        if (!EffectIndex(effectId, index))
        {
            return true;
        }

        bool requested = false;
        Provider provider{};
        bool hasProvider = false;
        {
            std::lock_guard<std::mutex> guard(g_lock);
            const EffectState& state = g_effects[index];
            requested = state.requested;
            provider = state.provider;
            hasProvider = state.hasProvider;
        }

        status->requested = requested ? 1 : 0;

        if (!hasProvider)
        {
            // Nothing implements this yet. The request is still remembered.
            status->reasonCode = Abi::kReasonNotImplemented;
            return true;
        }

        const bool supported = provider.IsSupported(provider.context);
        status->supported = supported ? 1 : 0;

        if (!supported)
        {
            status->reasonCode = NormaliseReason(provider.UnsupportedReason(provider.context));
            return true;
        }

        if (!requested)
        {
            // Capability exists, nobody asked for it. Distinct from "asked for
            // and refused", which is the whole point of not collapsing these
            // three flags into one boolean.
            status->reasonCode = Abi::kReasonNotRequested;
            return true;
        }

        const bool effective = provider.IsEffective(provider.context);
        status->effective = effective ? 1 : 0;
        status->reasonCode = effective
            ? Abi::kReasonEffective
            : NormaliseReason(provider.UnsupportedReason(provider.context));
        return true;
    }

    void Reset()
    {
        std::array<Provider, kEffectCount> providers{};
        std::array<bool, kEffectCount> hasProvider{};
        {
            std::lock_guard<std::mutex> guard(g_lock);
            for (size_t i = 0; i < kEffectCount; ++i)
            {
                EffectState& state = g_effects[i];
                state.requested = false;
                state.params.fill(0.0f);
                state.paramSet.fill(false);
                providers[i] = state.provider;
                hasProvider[i] = state.hasProvider;
            }
        }

        // Providers survive a reset - they belong to the renderer's lifetime,
        // not the mission's - but anything they were told to do does not.
        for (size_t i = 0; i < kEffectCount; ++i)
        {
            if (hasProvider[i] && providers[i].IsSupported(providers[i].context))
            {
                providers[i].ApplyEnabled(providers[i].context, false);
            }
        }
    }

    void ResetForTesting()
    {
        std::lock_guard<std::mutex> guard(g_lock);
        for (EffectState& state : g_effects)
        {
            state = EffectState{};
        }
    }
}
