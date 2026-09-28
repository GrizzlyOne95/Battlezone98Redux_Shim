// Tests for the scene-depth qualification bookkeeping.
//
// The thing worth pinning down here is resource identity across time. COM hands
// back addresses it has used before, so "I have seen this pointer" is not the
// same statement as "this is the same depth surface", and getting that wrong in
// either direction ruins the capture Phase A exists to produce: treat a reused
// address as the same surface and a shadow map inherits the main view's bind
// count; treat every sighting as new and a single surface looks like a leak.
//
// No D3D11 and no game: every fact arrives as a plain integer.

#include "scene_depth_facts.h"

#include <cstdio>
#include <cstring>
#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    using namespace BZROpenShim::SceneDepth;


    // BZR's shipped main depth surface as the fog qualification described it:
    // typeless, multisampled at the normal FSAA=8 setting, and NOT shader
    // readable. That last flag is the whole reason Phase B exists.
    TextureFacts ShippedMainDepth(uint64_t address)
    {
        TextureFacts facts;
        facts.resource = address;
        facts.width = 1920;
        facts.height = 1080;
        facts.format = Native::kFormatR32Typeless;
        facts.sampleCount = 8;
        facts.sampleQuality = 0;
        facts.bindFlags = Native::kBindDepthStencil;
        facts.arraySize = 1;
        facts.mipLevels = 1;
        return facts;
    }

    TextureFacts ShadowMap(uint64_t address)
    {
        TextureFacts facts;
        facts.resource = address;
        facts.width = 1024;
        facts.height = 1024;
        facts.format = Native::kFormatR32Typeless;
        facts.sampleCount = 1;
        facts.bindFlags = Native::kBindDepthStencil | Native::kBindShaderResource;
        facts.arraySize = 1;
        facts.mipLevels = 1;
        return facts;
    }

    TextureFacts ColourTarget(uint64_t address)
    {
        TextureFacts facts;
        facts.resource = address;
        facts.width = 1920;
        facts.height = 1080;
        facts.format = 28;                              // R8G8B8A8_UNORM
        facts.bindFlags = 0x20u | Native::kBindShaderResource;  // RENDER_TARGET
        facts.arraySize = 1;
        facts.mipLevels = 1;
        return facts;
    }

    void TestPredicates()
    {
        Check(IsDepthCandidate(Native::kBindDepthStencil), "a depth-stencil bind is a depth candidate");
        Check(!IsDepthCandidate(Native::kBindShaderResource), "a shader-resource bind alone is not");
        Check(!IsDepthCandidate(0), "no bind flags is not a depth candidate");

        // The point of reading bind flags rather than format: BZR's depth
        // surface is R32_TYPELESS, a format a colour target could also use.
        TextureFacts colour = ColourTarget(0x1000);
        Check(!IsDepthCandidate(colour.bindFlags), "a colour target is never a depth candidate");

        Check(!IsShaderReadable(ShippedMainDepth(0x2000).bindFlags),
            "the shipped FSAA=8 depth surface is not shader readable; Phase B depends on this");
        Check(IsShaderReadable(ShadowMap(0x3000).bindFlags),
            "a shadow map is shader readable");

        Check(IsMultisampled(ShippedMainDepth(0x2000)), "FSAA=8 depth is multisampled");
        Check(!IsMultisampled(ShadowMap(0x3000)), "a shadow map is single sampled");
    }

    void TestFormatNames()
    {
        Check(std::strcmp(FormatName(Native::kFormatR32Typeless), "R32_TYPELESS") == 0,
            "R32_TYPELESS renders by name");
        Check(std::strcmp(DsvDimensionName(Native::kDsvDimensionTexture2DMs), "TEXTURE2DMS") == 0,
            "the multisampled DSV dimension renders by name");

        // An unrecognised value must be reported as null so the caller prints
        // the number. A capture that silently renders every unknown format as
        // "UNKNOWN" cannot be used to qualify anything.
        Check(FormatName(0xDEAD) == nullptr, "an unknown format is not given a name");
        Check(DsvDimensionName(0xBEEF) == nullptr, "an unknown DSV dimension is not given a name");
    }

    void TestIgnoresNonDepth()
    {
        Registry registry;
        Check(registry.Observe(ColourTarget(0x1000)) == Registry::Event::Ignored,
            "a colour target is ignored");
        Check(registry.Size() == 0, "an ignored resource is not recorded");

        TextureFacts nullAddress = ShippedMainDepth(0);
        Check(registry.Observe(nullAddress) == Registry::Event::Ignored,
            "a null resource address is ignored");
    }

    void TestAddAndRecognise()
    {
        Registry registry;
        uint32_t serial = 0;

        Check(registry.Observe(ShippedMainDepth(0x4000), &serial) == Registry::Event::Added,
            "a new depth surface is added");
        Check(serial == 1, "the first surface gets serial 1");
        Check(registry.Size() == 1, "one surface recorded");

        uint32_t again = 0;
        Check(registry.Observe(ShippedMainDepth(0x4000), &again) == Registry::Event::Known,
            "the same surface at the same address is already known");
        Check(again == serial, "a known surface keeps its serial");
        Check(registry.Size() == 1, "a known surface does not add a second entry");
    }

    void TestAddressReuseIsARecreate()
    {
        Registry registry;
        uint32_t first = 0;
        registry.Observe(ShippedMainDepth(0x5000), &first);
        registry.NoteDepthStencilView(0x5000, Native::kFormatD32Float, Native::kDsvDimensionTexture2DMs);
        registry.NoteBind(0x5000, 1920, 1080, 1);
        registry.NoteBind(0x5000, 1920, 1080, 1);

        const Observation* before = registry.Find(0x5000);
        Check(before != nullptr && before->bindCount == 2, "binds accumulate on a live surface");

        // Same address, different surface: a mission change or a resolution
        // change, seen from inside CreateTexture2D.
        TextureFacts resized = ShippedMainDepth(0x5000);
        resized.width = 2560;
        resized.height = 1440;

        uint32_t second = 0;
        Check(registry.Observe(resized, &second) == Registry::Event::Recreated,
            "a reused address carrying a different surface is a recreate");
        Check(second != first, "a recreated surface gets a fresh serial");
        Check(registry.Size() == 1, "a recreate reuses the entry rather than adding one");

        const Observation* after = registry.Find(0x5000);
        Check(after != nullptr, "the recreated surface is findable");
        if (after)
        {
            Check(after->generation == 1, "the generation counts address reuse");
            Check(after->bindCount == 0, "a recreate must not inherit the old bind count");
            Check(after->dsvCount == 0, "a recreate must not inherit the old views");
            Check(after->facts.width == 2560, "the recreated surface carries the new facts");
            Check(!after->everBoundWithRenderTarget, "a recreate starts with no bind history");
        }
    }

    void TestViewsAndBinds()
    {
        Registry registry;
        registry.Observe(ShippedMainDepth(0x6000));

        Check(registry.NoteDepthStencilView(0x6000, Native::kFormatD32Float, Native::kDsvDimensionTexture2DMs),
            "a view over a tracked surface is recorded");
        Check(!registry.NoteDepthStencilView(0x9999, Native::kFormatD32Float, Native::kDsvDimensionTexture2D),
            "a view over an untracked surface is refused rather than invented");
        Check(!registry.NoteBind(0x9999, 1920, 1080, 1),
            "a bind of an untracked surface is refused");

        const Observation* entry = registry.Find(0x6000);
        Check(entry != nullptr && entry->dsvCount == 1, "one view recorded");
        Check(entry != nullptr && entry->dsvDimension == Native::kDsvDimensionTexture2DMs,
            "the view dimension is what tells an MSAA depth view from a plain one");

        // A depth-only pass - a shadow map - binds no render target at all.
        // Keeping that distinct from "bound alongside a full-size target" is
        // the observation the main-view question actually turns on.
        registry.NoteBind(0x6000, 0, 0, 0);
        entry = registry.Find(0x6000);
        Check(entry != nullptr && entry->bindCount == 1, "a depth-only bind still counts as a bind");
        Check(entry != nullptr && !entry->everBoundWithRenderTarget,
            "a depth-only bind must not be recorded as having a render target");

        registry.NoteBind(0x6000, 1920, 1080, 1);
        entry = registry.Find(0x6000);
        Check(entry != nullptr && entry->everBoundWithRenderTarget,
            "a bind alongside a render target is recorded as such");
        Check(entry != nullptr && entry->lastRtWidth == 1920, "the render target size is kept");
    }

    void TestDistinctSurfacesCoexist()
    {
        Registry registry;
        uint32_t mainSerial = 0;
        uint32_t shadowSerial = 0;
        registry.Observe(ShippedMainDepth(0x7000), &mainSerial);
        registry.Observe(ShadowMap(0x7100), &shadowSerial);

        Check(registry.Size() == 2, "two distinct depth surfaces are both tracked");
        Check(mainSerial != shadowSerial, "distinct surfaces get distinct serials");

        registry.NoteBind(0x7000, 1920, 1080, 1);
        registry.NoteBind(0x7100, 0, 0, 0);

        const Observation* main = registry.Find(0x7000);
        const Observation* shadow = registry.Find(0x7100);
        Check(main != nullptr && shadow != nullptr, "both are findable");
        Check(main != nullptr && main->everBoundWithRenderTarget,
            "the main surface is bound with a render target");
        Check(shadow != nullptr && !shadow->everBoundWithRenderTarget,
            "the shadow surface is not");
    }

    void TestOverflowIsReportedNotAbsorbed()
    {
        Registry registry;
        for (size_t i = 0; i < Registry::kCapacity; ++i)
        {
            const uint64_t address = 0x8000 + (static_cast<uint64_t>(i) * 0x100);
            Check(registry.Observe(ShippedMainDepth(address)) == Registry::Event::Added,
                "every surface up to capacity is added");
        }

        Check(registry.Size() == Registry::kCapacity, "the registry fills to capacity");
        Check(!registry.Overflowed(), "a full registry has not yet overflowed");

        Check(registry.Observe(ShippedMainDepth(0xF0000)) == Registry::Event::Overflow,
            "one past capacity overflows");
        Check(registry.Overflowed(), "overflow is recorded so the capture can say so");
        Check(registry.Size() == Registry::kCapacity, "an overflowing surface is not stored");

        // A surface already in the table must still be recognised after
        // overflow, or the capture would go blind exactly when it matters most.
        Check(registry.Observe(ShippedMainDepth(0x8000)) == Registry::Event::Known,
            "a known surface is still recognised after an overflow");

        registry.Clear();
        Check(registry.Size() == 0 && !registry.Overflowed(), "clear resets the registry");
    }
}

int main()
{
    TestPredicates();
    TestFormatNames();
    TestIgnoresNonDepth();
    TestAddAndRecognise();
    TestAddressReuseIsARecreate();
    TestViewsAndBinds();
    TestDistinctSurfacesCoexist();
    TestOverflowIsReportedNotAbsorbed();

    if (OpenShimTest::FailureCount() != 0)
    {
        std::printf("scene_depth_facts_tests: %d failure(s)\n", OpenShimTest::FailureCount());
        return 1;
    }

    std::printf("scene_depth_facts_tests: all checks passed\n");
    return 0;
}
