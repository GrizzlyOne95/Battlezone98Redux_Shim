// Tests for the render-effect intent layer.
//
// The thing worth pinning down here is the requested / supported / effective
// contract. Collapsing those three into one boolean is the mistake this ABI
// exists to avoid: "the mission asked for SSAO", "this build can do SSAO" and
// "SSAO is on screen right now" are three different facts, and a companion
// that can only see one of them cannot tell a DX9 machine from a machine where
// nobody enabled the effect.
//
// A fake provider stands in for the renderer, so every path - including the
// one where no renderer exists at all, which is today's real state - is
// exercised with no game, no D3D11 and no Ogre.

#include "render_effect_intent.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <limits>

namespace
{
    using namespace BZROpenShim::RenderEffects;

    int g_failures = 0;

    void Require(bool condition, const char* message)
    {
        if (!condition)
        {
            std::fprintf(stderr, "render_effect_intent_tests: %s\n", message);
            ++g_failures;
        }
    }

    void RequireEqual(uint32_t actual, uint32_t expected, const char* message)
    {
        if (actual != expected)
        {
            std::fprintf(
                stderr,
                "render_effect_intent_tests: %s (expected %u, got %u)\n",
                message,
                expected,
                actual);
            ++g_failures;
        }
    }

    void RequireNear(float actual, float expected, const char* message)
    {
        if (!(std::fabs(actual - expected) < 1e-5f))
        {
            std::fprintf(
                stderr,
                "render_effect_intent_tests: %s (expected %f, got %f)\n",
                message,
                static_cast<double>(expected),
                static_cast<double>(actual));
            ++g_failures;
        }
    }

    // Stands in for a renderer feature. `supported` and `effective` are what
    // the test drives; the apply counters are how we check the intent really
    // reached it.
    struct FakeProvider
    {
        bool supported = true;
        bool effective = true;
        uint32_t unsupportedReason = Abi::kReasonSceneDepthUnavailable;

        bool lastEnabled = false;
        int enabledCalls = 0;

        uint32_t lastParamId = 0;
        float lastValue = 0.0f;
        int floatCalls = 0;
    };

    bool FakeIsSupported(void* context)
    {
        return static_cast<FakeProvider*>(context)->supported;
    }

    uint32_t FakeUnsupportedReason(void* context)
    {
        return static_cast<FakeProvider*>(context)->unsupportedReason;
    }

    void FakeApplyEnabled(void* context, bool enabled)
    {
        auto* fake = static_cast<FakeProvider*>(context);
        fake->lastEnabled = enabled;
        ++fake->enabledCalls;
    }

    void FakeApplyFloat(void* context, uint32_t paramId, float value)
    {
        auto* fake = static_cast<FakeProvider*>(context);
        fake->lastParamId = paramId;
        fake->lastValue = value;
        ++fake->floatCalls;
    }

    bool FakeIsEffective(void* context)
    {
        return static_cast<FakeProvider*>(context)->effective;
    }

    Provider MakeProvider(FakeProvider& fake)
    {
        Provider provider{};
        provider.IsSupported = &FakeIsSupported;
        provider.UnsupportedReason = &FakeUnsupportedReason;
        provider.ApplyEnabled = &FakeApplyEnabled;
        provider.ApplyFloat = &FakeApplyFloat;
        provider.IsEffective = &FakeIsEffective;
        provider.context = &fake;
        return provider;
    }

    Abi::StatusV1 QueryStatus(uint32_t effectId)
    {
        Abi::StatusV1 status{};
        status.size = sizeof(Abi::StatusV1);
        Require(GetStatus(effectId, &status), "GetStatus should succeed for a sized struct");
        return status;
    }

    // -----------------------------------------------------------------------

    // Today's real state: the ABI ships, nothing implements it. A mission must
    // be able to ask and be told no, without anything going wrong.
    void TestNoProviderIsNotImplemented()
    {
        ResetForTesting();

        RequireEqual(SetEnabled(Abi::kEffectSsao, true), Abi::kResultAccepted,
            "a request is accepted even with no renderer behind it");

        const Abi::StatusV1 status = QueryStatus(Abi::kEffectSsao);
        RequireEqual(static_cast<uint32_t>(status.requested), 1u,
            "the request is remembered");
        RequireEqual(static_cast<uint32_t>(status.supported), 0u,
            "nothing is supported without a provider");
        RequireEqual(static_cast<uint32_t>(status.effective), 0u,
            "nothing is effective without a provider");
        RequireEqual(status.reasonCode, Abi::kReasonNotImplemented,
            "the reason says the feature does not exist yet");
        RequireEqual(status.version, Abi::kStatusVersion, "the status carries its version");
        RequireEqual(status.size, static_cast<uint32_t>(sizeof(Abi::StatusV1)),
            "the status reports its own size back");
    }

    void TestUnknownEffectIsRejected()
    {
        ResetForTesting();

        RequireEqual(SetEnabled(0u, true), Abi::kResultRejectedEffect,
            "effect id 0 is not a valid effect");
        RequireEqual(SetEnabled(9999u, true), Abi::kResultRejectedEffect,
            "an out-of-range effect id is rejected");
        RequireEqual(SetFloat(9999u, Abi::kParamStrength, 1.0f), Abi::kResultRejectedEffect,
            "SetFloat rejects an unknown effect before looking at the parameter");

        const Abi::StatusV1 status = QueryStatus(9999u);
        RequireEqual(status.reasonCode, Abi::kReasonUnknownEffect,
            "an unknown effect reports why rather than looking merely unsupported");
    }

    void TestUnknownParameterIsRejected()
    {
        ResetForTesting();
        RequireEqual(SetFloat(Abi::kEffectSsao, 0u, 1.0f), Abi::kResultRejectedParam,
            "parameter id 0 is not valid");
        RequireEqual(SetFloat(Abi::kEffectSsao, 9999u, 1.0f), Abi::kResultRejectedParam,
            "an out-of-range parameter id is rejected");
    }

    // A wrong number should be visible as a wrong number, not quietly turned
    // into a plausible one.
    void TestNonFiniteValuesAreRejected()
    {
        ResetForTesting();
        const float infinity = std::numeric_limits<float>::infinity();
        RequireEqual(SetFloat(Abi::kEffectSsao, Abi::kParamStrength, infinity),
            Abi::kResultRejectedValue, "infinity is rejected");
        RequireEqual(SetFloat(Abi::kEffectSsao, Abi::kParamStrength, -infinity),
            Abi::kResultRejectedValue, "negative infinity is rejected");
        RequireEqual(SetFloat(Abi::kEffectSsao, Abi::kParamStrength,
            std::numeric_limits<float>::quiet_NaN()),
            Abi::kResultRejectedValue, "NaN is rejected");
    }

    void TestParametersAreClamped()
    {
        RequireNear(ClampParameter(Abi::kParamStrength, -5.0f), 0.0f,
            "strength cannot go negative");
        RequireNear(ClampParameter(Abi::kParamStrength, 100.0f), 4.0f,
            "strength is capped");
        RequireNear(ClampParameter(Abi::kParamStrength, 0.65f), 0.65f,
            "an in-range strength is untouched");
        RequireNear(ClampParameter(Abi::kParamRadius, 0.0f), 0.01f,
            "radius cannot be zero");
        RequireNear(ClampParameter(Abi::kParamQuality, 9.0f), 3.0f,
            "quality is capped at the highest tier");
    }

    void TestSupportedProviderReceivesIntent()
    {
        ResetForTesting();
        FakeProvider fake;
        Require(RegisterProvider(Abi::kEffectSsao, MakeProvider(fake)),
            "a complete provider registers");

        RequireEqual(SetEnabled(Abi::kEffectSsao, true), Abi::kResultAccepted,
            "enabling is accepted");
        Require(fake.lastEnabled, "the provider was told to turn on");

        RequireEqual(SetFloat(Abi::kEffectSsao, Abi::kParamStrength, 0.65f),
            Abi::kResultAccepted, "a tuning value is accepted");
        RequireEqual(fake.lastParamId, Abi::kParamStrength, "the parameter id is passed through");
        RequireNear(fake.lastValue, 0.65f, "the value is passed through");

        // The clamp happens before the provider sees it, so a provider never
        // has to defend itself against an out-of-range mission script.
        SetFloat(Abi::kEffectSsao, Abi::kParamStrength, 500.0f);
        RequireNear(fake.lastValue, 4.0f, "the provider receives the clamped value");

        const Abi::StatusV1 status = QueryStatus(Abi::kEffectSsao);
        RequireEqual(static_cast<uint32_t>(status.requested), 1u, "requested");
        RequireEqual(static_cast<uint32_t>(status.supported), 1u, "supported");
        RequireEqual(static_cast<uint32_t>(status.effective), 1u, "effective");
        RequireEqual(status.reasonCode, Abi::kReasonEffective, "and the reason says so");
    }

    // The DX9 case from the design note.
    void TestUnsupportedProviderReportsItsReason()
    {
        ResetForTesting();
        FakeProvider fake;
        fake.supported = false;
        fake.unsupportedReason = Abi::kReasonUnsupportedRenderer;
        RegisterProvider(Abi::kEffectSsao, MakeProvider(fake));

        SetEnabled(Abi::kEffectSsao, true);
        Require(fake.enabledCalls == 0,
            "an unsupported provider is never pushed intent");

        const Abi::StatusV1 status = QueryStatus(Abi::kEffectSsao);
        RequireEqual(static_cast<uint32_t>(status.requested), 1u,
            "the request is still recorded on an unsupported renderer");
        RequireEqual(static_cast<uint32_t>(status.supported), 0u, "not supported");
        RequireEqual(status.reasonCode, Abi::kReasonUnsupportedRenderer,
            "the provider's reason reaches the caller");
    }

    // Capability exists, nobody asked. Must not look the same as a refusal.
    void TestSupportedButNotRequested()
    {
        ResetForTesting();
        FakeProvider fake;
        RegisterProvider(Abi::kEffectSsao, MakeProvider(fake));

        const Abi::StatusV1 status = QueryStatus(Abi::kEffectSsao);
        RequireEqual(static_cast<uint32_t>(status.requested), 0u, "not requested");
        RequireEqual(static_cast<uint32_t>(status.supported), 1u, "but supported");
        RequireEqual(static_cast<uint32_t>(status.effective), 0u, "so not effective");
        RequireEqual(status.reasonCode, Abi::kReasonNotRequested,
            "and the reason distinguishes this from a refusal");
    }

    // Asked for, possible, but not yet running.
    void TestRequestedAndSupportedButNotEffective()
    {
        ResetForTesting();
        FakeProvider fake;
        fake.effective = false;
        fake.unsupportedReason = Abi::kReasonPending;
        RegisterProvider(Abi::kEffectSsao, MakeProvider(fake));

        SetEnabled(Abi::kEffectSsao, true);
        const Abi::StatusV1 status = QueryStatus(Abi::kEffectSsao);
        RequireEqual(static_cast<uint32_t>(status.requested), 1u, "requested");
        RequireEqual(static_cast<uint32_t>(status.supported), 1u, "supported");
        RequireEqual(static_cast<uint32_t>(status.effective), 0u, "not yet effective");
        RequireEqual(status.reasonCode, Abi::kReasonPending, "reported as pending");
    }

    // A provider that invents a reason code must not be able to put an
    // unrecognised value in front of a companion.
    void TestUnknownProviderReasonIsNormalised()
    {
        ResetForTesting();
        FakeProvider fake;
        fake.supported = false;
        fake.unsupportedReason = 0xDEADBEEFu;
        RegisterProvider(Abi::kEffectSsao, MakeProvider(fake));

        const Abi::StatusV1 status = QueryStatus(Abi::kEffectSsao);
        RequireEqual(status.reasonCode, Abi::kReasonNotImplemented,
            "a bogus provider reason is normalised to a known code");
    }

    // The ordering that matters most: a mission asks for an effect before the
    // renderer is ready. When the renderer registers, the request has to be
    // replayed or it stays silently off forever.
    void TestRegistrationReplaysStoredIntent()
    {
        ResetForTesting();

        SetEnabled(Abi::kEffectSsao, true);
        SetFloat(Abi::kEffectSsao, Abi::kParamRadius, 1.25f);

        FakeProvider fake;
        RegisterProvider(Abi::kEffectSsao, MakeProvider(fake));

        Require(fake.enabledCalls == 1, "the stored enable was replayed on registration");
        Require(fake.lastEnabled, "and it was replayed as on");
        Require(fake.floatCalls == 1, "the stored parameter was replayed too");
        RequireEqual(fake.lastParamId, Abi::kParamRadius, "with the right parameter id");
        RequireNear(fake.lastValue, 1.25f, "and the right value");
    }

    void TestIncompleteProviderIsRefused()
    {
        ResetForTesting();
        FakeProvider fake;

        Provider partial = MakeProvider(fake);
        partial.IsEffective = nullptr;
        Require(!RegisterProvider(Abi::kEffectSsao, partial),
            "a provider missing a callback is refused rather than half-registered");

        const Abi::StatusV1 status = QueryStatus(Abi::kEffectSsao);
        RequireEqual(status.reasonCode, Abi::kReasonNotImplemented,
            "a refused provider leaves the effect unimplemented");
    }

    void TestUnregisterKeepsIntent()
    {
        ResetForTesting();
        FakeProvider fake;
        RegisterProvider(Abi::kEffectSsao, MakeProvider(fake));
        SetEnabled(Abi::kEffectSsao, true);

        Require(UnregisterProvider(Abi::kEffectSsao), "unregister succeeds");

        Abi::StatusV1 status = QueryStatus(Abi::kEffectSsao);
        RequireEqual(static_cast<uint32_t>(status.requested), 1u,
            "intent outlives the provider, so a renderer restart resumes it");
        RequireEqual(status.reasonCode, Abi::kReasonNotImplemented,
            "but nothing is supported while unregistered");

        // Re-registering must pick the request back up.
        FakeProvider second;
        RegisterProvider(Abi::kEffectSsao, MakeProvider(second));
        Require(second.lastEnabled, "the surviving request is replayed into the new provider");
    }

    // Mission scoping: this is what stops one mission's SSAO request following
    // the player into the shell.
    void TestResetClearsIntentAndTurnsProvidersOff()
    {
        ResetForTesting();
        FakeProvider fake;
        RegisterProvider(Abi::kEffectSsao, MakeProvider(fake));
        SetEnabled(Abi::kEffectSsao, true);
        SetFloat(Abi::kEffectSsao, Abi::kParamStrength, 0.9f);

        Reset();

        Require(!fake.lastEnabled, "the provider was told to turn off");

        const Abi::StatusV1 status = QueryStatus(Abi::kEffectSsao);
        RequireEqual(static_cast<uint32_t>(status.requested), 0u, "the request is cleared");

        // The provider survives, because it belongs to the renderer's lifetime
        // rather than the mission's.
        RequireEqual(static_cast<uint32_t>(status.supported), 1u,
            "the provider is still registered after a mission reset");

        // And the cleared parameters must not be replayed by a later re-register.
        FakeProvider second;
        RegisterProvider(Abi::kEffectSsao, MakeProvider(second));
        Require(second.floatCalls == 0, "cleared parameters are not replayed");
        Require(!second.lastEnabled, "and the effect comes back off");
    }

    void TestEffectsAreIndependent()
    {
        ResetForTesting();
        FakeProvider ssao;
        RegisterProvider(Abi::kEffectSsao, MakeProvider(ssao));

        SetEnabled(Abi::kEffectSsao, true);
        SetEnabled(Abi::kEffectDepthHaze, true);

        const Abi::StatusV1 ssaoStatus = QueryStatus(Abi::kEffectSsao);
        const Abi::StatusV1 hazeStatus = QueryStatus(Abi::kEffectDepthHaze);

        RequireEqual(static_cast<uint32_t>(ssaoStatus.supported), 1u,
            "SSAO has a provider");
        RequireEqual(static_cast<uint32_t>(hazeStatus.supported), 0u,
            "depth haze does not, and does not inherit SSAO's");
        RequireEqual(static_cast<uint32_t>(hazeStatus.requested), 1u,
            "but its own request is tracked separately");
    }

    void TestStatusRejectsBadBuffers()
    {
        ResetForTesting();
        Require(!GetStatus(Abi::kEffectSsao, nullptr), "a null status pointer is refused");

        Abi::StatusV1 undersized{};
        undersized.size = sizeof(Abi::StatusV1) - 1;
        Require(!GetStatus(Abi::kEffectSsao, &undersized),
            "a caller claiming a smaller struct than V1 is refused");

        // A caller from a future, larger V2 is fine: it says it has more room
        // than we need, and gets a V1 written into the front of it.
        Abi::StatusV1 oversized{};
        oversized.size = sizeof(Abi::StatusV1) + 64;
        Require(GetStatus(Abi::kEffectSsao, &oversized),
            "a caller with a larger struct is accepted");
        RequireEqual(oversized.version, Abi::kStatusVersion,
            "and is told which version it actually got");
    }

    void TestApiVersion()
    {
        RequireEqual(GetApiVersion(), Abi::kRenderEffectApiVersion,
            "the API version is reported");
        Require(IsKnownEffect(Abi::kEffectSoftParticles), "soft particles is a known effect");
        Require(!IsKnownEffect(4u), "effect 4 is not allocated yet");
        Require(IsKnownParameter(Abi::kParamQuality), "quality is a known parameter");
        Require(!IsKnownParameter(6u), "parameter 6 is not allocated yet");
    }
}

int main()
{
    TestNoProviderIsNotImplemented();
    TestUnknownEffectIsRejected();
    TestUnknownParameterIsRejected();
    TestNonFiniteValuesAreRejected();
    TestParametersAreClamped();
    TestSupportedProviderReceivesIntent();
    TestUnsupportedProviderReportsItsReason();
    TestSupportedButNotRequested();
    TestRequestedAndSupportedButNotEffective();
    TestUnknownProviderReasonIsNormalised();
    TestRegistrationReplaysStoredIntent();
    TestIncompleteProviderIsRefused();
    TestUnregisterKeepsIntent();
    TestResetClearsIntentAndTurnsProvidersOff();
    TestEffectsAreIndependent();
    TestStatusRejectsBadBuffers();
    TestApiVersion();

    if (g_failures != 0)
    {
        std::fprintf(stderr, "render_effect_intent_tests: %d failure(s)\n", g_failures);
        return EXIT_FAILURE;
    }

    std::puts("render_effect_intent_tests: all checks passed");
    return EXIT_SUCCESS;
}
