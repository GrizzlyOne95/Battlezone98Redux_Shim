// Renderer-profile resolution core tests. Pure logic: no engine, no game.
// Build+run via scripts/run_render_profile_tests.ps1.

#include "render_profile.h"

#include <cstdio>
#include <cstring>
#include <string>
#include "test_check.h"

using OpenShimTest::Check;

using namespace BZROpenShim::RenderProfiles;

namespace
{
    void ExpectEq(uint32_t actual, uint32_t expected, const char* what)
    {
        if (actual != expected)
        {
            OpenShimTest::Fail("%s (actual=%u expected=%u)", what, actual, expected);
        }
    }

    void ExpectReason(const ResolverResult& result, const char* needle)
    {
        if (std::strstr(result.reason, needle) == nullptr)
        {
            OpenShimTest::Fail("reason '%s' missing substring '%s'", result.reason, needle);
        }
    }

    ResolverInput Baseline()
    {
        ResolverInput input;
        input.requestedBackend = RendererBackend::Auto;
        input.detectedBackend = ActiveBackend::DX11;
        input.userProfile = Profile::Redux;
        input.contentOverridePresent = false;
        input.capabilityMask = CapabilitiesForBackend(ActiveBackend::DX11) |
                               static_cast<uint32_t>(CapIblResources) |
                               static_cast<uint32_t>(CapEnhancedResources);
        return input;
    }
}

void TestCleanReduxBaseline()
{
    std::printf("TestCleanReduxBaseline\n");
    const ResolverResult result = ResolveRenderProfile(Baseline());
    Check(!result.fellBack, "no fallback");
    ExpectEq(static_cast<uint32_t>(result.effectiveProfile), static_cast<uint32_t>(Profile::Redux), "profile");
    ExpectEq(static_cast<uint32_t>(result.effectiveBackend), static_cast<uint32_t>(ActiveBackend::DX11), "backend");
}

void TestContentOverrideWinsOverUser()
{
    std::printf("TestContentOverrideWinsOverUser\n");
    ResolverInput input = Baseline();
    input.userProfile = Profile::Redux;
    input.contentOverridePresent = true;
    input.contentOverride = ContentRequest::Enhanced;
    const ResolverResult result = ResolveRenderProfile(input);
    ExpectEq(static_cast<uint32_t>(result.effectiveProfile), static_cast<uint32_t>(Profile::Enhanced), "enhanced wins");

    ResolverInput inverse = Baseline();
    inverse.userProfile = Profile::Enhanced;
    inverse.contentOverridePresent = true;
    inverse.contentOverride = ContentRequest::Redux;
    const ResolverResult inverseResult = ResolveRenderProfile(inverse);
    ExpectEq(static_cast<uint32_t>(inverseResult.effectiveProfile), static_cast<uint32_t>(Profile::Redux), "redux override wins over user enhanced");
    Check(!inverseResult.fellBack, "override is intent honored, not a fallback");
}

void TestInheritFollowsUserPreference()
{
    std::printf("TestInheritFollowsUserPreference\n");
    ResolverInput input = Baseline();
    input.userProfile = Profile::Enhanced;
    input.contentOverridePresent = true;
    input.contentOverride = ContentRequest::Inherit;
    const ResolverResult result = ResolveRenderProfile(input);
    ExpectEq(static_cast<uint32_t>(result.effectiveProfile), static_cast<uint32_t>(Profile::Enhanced), "inherit -> user enhanced");

    ResolverInput absent = Baseline();
    absent.userProfile = Profile::Retro;
    absent.contentOverridePresent = false;
    const ResolverResult absentResult = ResolveRenderProfile(absent);
    ExpectEq(static_cast<uint32_t>(absentResult.effectiveProfile), static_cast<uint32_t>(Profile::Retro), "absent override -> user retro");
}

void TestDx9EnhancedIsCapabilityDependentNotFallback()
{
    std::printf("TestDx9EnhancedIsCapabilityDependentNotFallback\n");
    ResolverInput dx9 = Baseline();
    dx9.requestedBackend = RendererBackend::Auto;
    dx9.detectedBackend = ActiveBackend::DX9;
    dx9.userProfile = Profile::Enhanced;
    // Mandatory resource set verified: DX9 Enhanced is supported-but-limited.
    // It must remain effective rather than silently degrading to Redux. The
    // capability report is where the reduced feature set is visible
    // (sharpening yes, modern pssm no). The broken-deployment counterpart is
    // covered by TestDx9EnhancedAlsoRequiresMandatoryResources.
    dx9.capabilityMask = CapabilitiesForBackend(ActiveBackend::DX9) |
                         static_cast<uint32_t>(CapEnhancedResources);

    const ResolverResult legacy = ResolveRenderProfile(dx9);
    // DX9 Enhanced is supported-but-limited: it must remain effective rather
    // than silently degrading to Redux. The capability report is where the
    // reduced feature set is visible (sharpening yes, modern pssm no).
    ExpectEq(static_cast<uint32_t>(legacy.effectiveProfile), static_cast<uint32_t>(Profile::Enhanced), "dx9 enhanced stays effective");
    Check(HasCapability(dx9.capabilityMask, CapNormalSharpening), "legacy sharpening bit present");
    Check(!HasCapability(dx9.capabilityMask, CapModernPssm), "modern pssm bit absent on dx9");
    Check(!HasCapability(dx9.capabilityMask, CapLinearLighting), "linear lighting bit absent on dx9");

    // A mission requesting Enhanced on DX9 gets the same treatment as the
    // user preference path: effective Enhanced with the legacy feature set.
    dx9.contentOverridePresent = true;
    dx9.contentOverride = ContentRequest::Enhanced;
    const ResolverResult requested = ResolveRenderProfile(dx9);
    ExpectEq(static_cast<uint32_t>(requested.effectiveProfile), static_cast<uint32_t>(Profile::Enhanced), "dx9 content enhanced stays effective");
}

void TestSchemeLayerLossFallsBackWithReason()
{
    std::printf("TestSchemeLayerLossFallsBackWithReason\n");
    ResolverInput input = Baseline();
    input.userProfile = Profile::Enhanced;
    input.capabilityMask &= ~static_cast<uint32_t>(CapSchemeRewrite);
    const ResolverResult result = ResolveRenderProfile(input);
    ExpectEq(static_cast<uint32_t>(result.effectiveProfile), static_cast<uint32_t>(Profile::Redux), "falls back to redux");
    Check(result.fellBack, "fallback reported");
    ExpectReason(result, "scheme policy layer inactive");
}

void TestRequestedBackendMismatchIsReportedNotApplied()
{
    std::printf("TestRequestedBackendMismatchIsReportedNotApplied\n");
    ResolverInput input = Baseline();
    input.requestedBackend = RendererBackend::DX9; // player picked DX9, session on DX11
    const ResolverResult result = ResolveRenderProfile(input);
    ExpectEq(static_cast<uint32_t>(result.effectiveBackend), static_cast<uint32_t>(ActiveBackend::DX11), "session backend unchanged");
    Check(result.fellBack, "restart-required divergence reported");
    ExpectReason(result, "restart required");
}

void TestOverrideClearReturnsToUser()
{
    std::printf("TestOverrideClearReturnsToUser\n");
    ResolverInput during = Baseline();
    during.userProfile = Profile::Redux;
    during.contentOverridePresent = true;
    during.contentOverride = ContentRequest::Enhanced;
    ExpectEq(static_cast<uint32_t>(ResolveRenderProfile(during).effectiveProfile),
             static_cast<uint32_t>(Profile::Enhanced), "mission override active");

    ResolverInput after = during;
    after.contentOverridePresent = false;
    ExpectEq(static_cast<uint32_t>(ResolveRenderProfile(after).effectiveProfile),
             static_cast<uint32_t>(Profile::Redux), "user preference restored");
}

void TestInvalidInputsResolveDeterministically()
{
    printf("TestInvalidInputsResolveDeterministically\n");
    ResolverInput garbage = Baseline();
    garbage.userProfile = static_cast<Profile>(99);
    garbage.contentOverridePresent = true;
    garbage.contentOverride = static_cast<ContentRequest>(77);
    garbage.requestedBackend = static_cast<RendererBackend>(42);
    garbage.detectedBackend = static_cast<ActiveBackend>(9);
    const ResolverResult result = ResolveRenderProfile(garbage);
    ExpectEq(static_cast<uint32_t>(result.effectiveProfile), static_cast<uint32_t>(Profile::Redux), "garbage profile -> redux");
    ExpectEq(static_cast<uint32_t>(result.effectiveBackend), static_cast<uint32_t>(ActiveBackend::DX9), "garbage backend -> dx9 baseline");
    Check(result.fellBack, "corrupt state explained");
}

void TestSchemePolicyMapping()
{
    std::printf("TestSchemePolicyMapping\n");
    char buffer[64] = {};

    Check(BuildMaterialSchemeForProfile(Profile::Redux, "high-pssm", buffer, sizeof(buffer)), "redux build");
    Check(std::string(buffer) == "high-pssm", "redux passthrough");
    Check(BuildMaterialSchemeForProfile(Profile::Enhanced, "high-pssm", buffer, sizeof(buffer)), "enhanced build");
    Check(std::string(buffer) == "en-high-pssm", "enhanced prefix");
    Check(BuildMaterialSchemeForProfile(Profile::Retro, "low-noshadow", buffer, sizeof(buffer)), "retro build");
    Check(std::string(buffer) == "og-low-noshadow", "retro prefix");

    Check(IsModernMaterialScheme("medium"), "medium is modern");
    Check(!IsModernMaterialScheme("en-medium"), "prefixed not modern");
    Check(!IsModernMaterialScheme("my-cool-mod"), "custom not modern");

    ExpectEq(static_cast<uint32_t>(ProfileForMaterialScheme("en-high")), static_cast<uint32_t>(Profile::Enhanced), "classify en");
    ExpectEq(static_cast<uint32_t>(ProfileForMaterialScheme("og-high")), static_cast<uint32_t>(Profile::Retro), "classify og");
    ExpectEq(static_cast<uint32_t>(ProfileForMaterialScheme("high")), static_cast<uint32_t>(Profile::Redux), "classify modern");

    Check(NormalizeModernMaterialScheme("en-medium-pssm") == "medium-pssm", "strip en prefix");
    Check(NormalizeModernMaterialScheme("og-low") == "low", "strip og prefix");
    Check(NormalizeModernMaterialScheme("") == DefaultModernMaterialScheme(), "empty -> default");
    Check(NormalizeModernMaterialScheme("", "lowest") == "lowest", "empty -> lastModern");
    Check(NormalizeModernMaterialScheme("weird") == DefaultModernMaterialScheme(), "unknown -> default");
}

// The explicit viewport reapply (boot, ini reload, EXU request) must follow
// the same fail-open rule as the setMaterialScheme hook: a scheme that is
// neither engine-native nor ours is left alone, and the Glow compositor is
// only ever switched off by Retro or switched back on after Retro.
void TestViewportReapplyFailsOpen()
{
    std::printf("TestViewportReapplyFailsOpen\n");

    for (const Profile profile : { Profile::Redux, Profile::Enhanced, Profile::Retro })
    {
        const ViewportReapplyDecision custom = DecideViewportSchemeReapply(profile, "my-cool-mod", "high-pssm");
        Check(custom.foreignScheme && !custom.rewriteScheme, "a custom scheme is left alone");
        const ViewportReapplyDecision empty = DecideViewportSchemeReapply(profile, "", "high-pssm");
        Check(empty.foreignScheme && !empty.rewriteScheme, "an empty scheme is left alone");
        const ViewportReapplyDecision ogreDefault = DecideViewportSchemeReapply(profile, "Default", {});
        Check(ogreDefault.foreignScheme && !ogreDefault.rewriteScheme, "Ogre's Default scheme is left alone");
    }

    ViewportReapplyDecision d = DecideViewportSchemeReapply(Profile::Enhanced, "high-pssm", {});
    Check(!d.foreignScheme && d.rewriteScheme && std::string(d.scheme) == "en-high-pssm", "enhanced prefixes a native base");
    d = DecideViewportSchemeReapply(Profile::Enhanced, "en-high-pssm", {});
    Check(!d.foreignScheme && !d.rewriteScheme, "already enhanced: nothing to write");
    d = DecideViewportSchemeReapply(Profile::Redux, "en-medium-noshadow", {});
    Check(d.rewriteScheme && std::string(d.scheme) == "medium-noshadow", "redux strips our prefix");
    d = DecideViewportSchemeReapply(Profile::Redux, "high-pssm", {});
    Check(!d.foreignScheme && !d.rewriteScheme, "redux on a native base: nothing to write");
    d = DecideViewportSchemeReapply(Profile::Retro, "medium-noshadow", {});
    Check(d.rewriteScheme && std::string(d.scheme) == "og-medium-noshadow", "retro prefixes a native base");
    d = DecideViewportSchemeReapply(Profile::Enhanced, "og-low", {});
    Check(d.rewriteScheme && std::string(d.scheme) == "en-low", "retro to enhanced swaps the prefix");
    d = DecideViewportSchemeReapply(Profile::Enhanced, "en-weird", "medium-pssm");
    Check(d.rewriteScheme && std::string(d.scheme) == "en-medium-pssm", "our prefix on an unknown base falls back to the last modern base");

    ExpectEq(static_cast<uint32_t>(DecideGlowCompositor(Profile::Retro, false)), static_cast<uint32_t>(GlowAction::Disable), "retro disables glow");
    ExpectEq(static_cast<uint32_t>(DecideGlowCompositor(Profile::Retro, true)), static_cast<uint32_t>(GlowAction::Disable), "retro keeps glow off");
    ExpectEq(static_cast<uint32_t>(DecideGlowCompositor(Profile::Redux, true)), static_cast<uint32_t>(GlowAction::Restore), "leaving retro restores glow");
    ExpectEq(static_cast<uint32_t>(DecideGlowCompositor(Profile::Enhanced, true)), static_cast<uint32_t>(GlowAction::Restore), "enhanced after retro restores glow");
    ExpectEq(static_cast<uint32_t>(DecideGlowCompositor(Profile::Redux, false)), static_cast<uint32_t>(GlowAction::LeaveAlone), "redux leaves the engine's glow alone");
    ExpectEq(static_cast<uint32_t>(DecideGlowCompositor(Profile::Enhanced, false)), static_cast<uint32_t>(GlowAction::LeaveAlone), "enhanced leaves the engine's glow alone");
}

void TestMandatoryResourceLossFallsBackToRedux()
{
    std::printf("TestMandatoryResourceLossFallsBackToRedux\n");
    // A deployment whose mandatory Enhanced resource set failed validation
    // (any one program/shader/texture missing or empty) must degrade
    // Enhanced to Redux even though the scheme layer itself is healthy.
    ResolverInput input = Baseline();
    input.userProfile = Profile::Enhanced;
    input.capabilityMask &= ~static_cast<uint32_t>(CapEnhancedResources);
    const ResolverResult result = ResolveRenderProfile(input);
    ExpectEq(static_cast<uint32_t>(result.effectiveProfile),
             static_cast<uint32_t>(Profile::Redux), "falls back to redux");
    Check(result.fellBack, "fallback reported");
    ExpectReason(result, "resource");

    // Same contract for a mission override: content cannot resurrect the
    // missing files.
    input.contentOverridePresent = true;
    input.contentOverride = ContentRequest::Enhanced;
    const ResolverResult overrideResult = ResolveRenderProfile(input);
    ExpectEq(static_cast<uint32_t>(overrideResult.effectiveProfile),
             static_cast<uint32_t>(Profile::Redux), "override cannot bypass resource gate");
}

void TestDx9EnhancedAlsoRequiresMandatoryResources()
{
    std::printf("TestDx9EnhancedAlsoRequiresMandatoryResources\n");
    // The mandatory set covers the SM3 delegates too, so the gate is
    // backend-independent: DX9 Enhanced falls back exactly like DX11 when
    // the deployment is broken.
    ResolverInput dx9 = Baseline();
    dx9.detectedBackend = ActiveBackend::DX9;
    dx9.userProfile = Profile::Enhanced;
    dx9.capabilityMask = CapabilitiesForBackend(ActiveBackend::DX9) |
                         static_cast<uint32_t>(CapEnhancedResources);
    ExpectEq(static_cast<uint32_t>(ResolveRenderProfile(dx9).effectiveProfile),
             static_cast<uint32_t>(Profile::Enhanced), "dx9 enhanced with valid resources stays");

    dx9.capabilityMask &= ~static_cast<uint32_t>(CapEnhancedResources);
    const ResolverResult broken = ResolveRenderProfile(dx9);
    ExpectEq(static_cast<uint32_t>(broken.effectiveProfile),
             static_cast<uint32_t>(Profile::Redux), "dx9 enhanced falls back without resources");
}

void TestOptionalIblIsIndependentOfEnhancedGate()
{
    std::printf("TestOptionalIblIsIndependentOfEnhancedGate\n");
    // IBL is an OPTIONAL extra: its absence removes only the CapIblResources
    // bit and must NOT gate the profile.
    ResolverInput input = Baseline();
    input.userProfile = Profile::Enhanced;
    input.capabilityMask &= ~static_cast<uint32_t>(CapIblResources);
    const ResolverResult result = ResolveRenderProfile(input);
    ExpectEq(static_cast<uint32_t>(result.effectiveProfile),
             static_cast<uint32_t>(Profile::Enhanced), "enhanced survives ibl loss");
    Check(!result.fellBack, "ibl loss is not a fallback");
}

void TestProfileRequirementsMetSharedGate()
{
    std::printf("TestProfileRequirementsMetSharedGate\n");
    const uint32_t full = static_cast<uint32_t>(CapSchemeRewrite) |
                          static_cast<uint32_t>(CapEnhancedResources);
    const uint32_t noResources = static_cast<uint32_t>(CapSchemeRewrite);
    const uint32_t noScheme = static_cast<uint32_t>(CapEnhancedResources);

    // The shared gate used by BOTH ResolveRenderProfile and the runtime's
    // SupportsRenderProfile must keep the two in exact agreement.
    Check(ProfileRequirementsMet(Profile::Enhanced, full), "enhanced needs both");
    Check(!ProfileRequirementsMet(Profile::Enhanced, noResources), "enhanced rejects missing resources");
    Check(!ProfileRequirementsMet(Profile::Enhanced, noScheme), "enhanced rejects missing scheme layer");
    Check(ProfileRequirementsMet(Profile::Retro, noResources), "retro needs only scheme layer");
    Check(!ProfileRequirementsMet(Profile::Retro, noScheme), "retro rejects missing scheme layer");
    Check(ProfileRequirementsMet(Profile::Redux, 0u), "redux always available");
}

void TestStableAbiRoundTrip()
{
    std::printf("TestStableAbiRoundTrip\n");
    ExpectEq(Abi::kRequestInherit, 0u, "inherit abi value frozen");
    ExpectEq(Abi::kRequestRetro, 1u, "retro abi value frozen");
    ExpectEq(Abi::kRequestRedux, 2u, "redux abi value frozen");
    ExpectEq(Abi::kRequestEnhanced, 3u, "enhanced abi value frozen");

    Profile profile = Profile::Redux;
    Check(Abi::ProfileFromAbi(Abi::kProfileEnhanced, profile), "parse enhanced");
    ExpectEq(static_cast<uint32_t>(profile), static_cast<uint32_t>(Profile::Enhanced), "parsed value");

    uint32_t abi = 0;
    Check(Abi::ProfileToAbi(Profile::Retro, abi) && abi == Abi::kProfileRetro, "roundtrip retro");
    Check(!Abi::ProfileFromAbi(42u, profile), "reject unknown profile");
    ContentRequest request = ContentRequest::Inherit;
    Check(!Abi::RequestFromAbi(999u, request), "reject unknown request");
    Check(Abi::RequestFromAbi(3u, request) && request == ContentRequest::Enhanced, "parse request enhanced");

    // Request-status values are frozen ABI: AppliedLive=0 keeps the
    // "success" reading older companions may assume; the others must not
    // collide with it.
    ExpectEq(Abi::kRequestStatusAppliedLive, 0u, "applied-live frozen");
    ExpectEq(Abi::kRequestStatusStoredDeferred, 1u, "stored-deferred frozen");
    ExpectEq(Abi::kRequestStatusRejectedValue, 2u, "rejected-value frozen");
    ExpectEq(Abi::kRequestStatusUnsupportedBuild, 3u, "unsupported-build frozen");
}

int main()
{
    TestCleanReduxBaseline();
    TestContentOverrideWinsOverUser();
    TestInheritFollowsUserPreference();
    TestDx9EnhancedIsCapabilityDependentNotFallback();
    TestSchemeLayerLossFallsBackWithReason();
    TestMandatoryResourceLossFallsBackToRedux();
    TestDx9EnhancedAlsoRequiresMandatoryResources();
    TestOptionalIblIsIndependentOfEnhancedGate();
    TestProfileRequirementsMetSharedGate();
    TestRequestedBackendMismatchIsReportedNotApplied();
    TestOverrideClearReturnsToUser();
    TestInvalidInputsResolveDeterministically();
    TestSchemePolicyMapping();
    TestViewportReapplyFailsOpen();
    TestStableAbiRoundTrip();

    if (OpenShimTest::FailureCount() != 0)
    {
        std::printf("\nrender_profile_tests FAILED (%d)\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("\nrender_profile_tests passed\n");
    return 0;
}
