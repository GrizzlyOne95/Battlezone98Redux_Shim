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

namespace
{
    using namespace BZROpenShim::SceneDepth;

    int g_failures = 0;

    void Require(bool condition, const char* message)
    {
        if (!condition)
        {
            std::printf("FAIL: %s\n", message);
            ++g_failures;
        }
    }

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
        Require(IsDepthCandidate(Native::kBindDepthStencil), "a depth-stencil bind is a depth candidate");
        Require(!IsDepthCandidate(Native::kBindShaderResource), "a shader-resource bind alone is not");
        Require(!IsDepthCandidate(0), "no bind flags is not a depth candidate");

        // The point of reading bind flags rather than format: BZR's depth
        // surface is R32_TYPELESS, a format a colour target could also use.
        TextureFacts colour = ColourTarget(0x1000);
        Require(!IsDepthCandidate(colour.bindFlags), "a colour target is never a depth candidate");

        Require(!IsShaderReadable(ShippedMainDepth(0x2000).bindFlags),
            "the shipped FSAA=8 depth surface is not shader readable; Phase B depends on this");
        Require(IsShaderReadable(ShadowMap(0x3000).bindFlags),
            "a shadow map is shader readable");

        Require(IsMultisampled(ShippedMainDepth(0x2000)), "FSAA=8 depth is multisampled");
        Require(!IsMultisampled(ShadowMap(0x3000)), "a shadow map is single sampled");
    }

    void TestFormatNames()
    {
        Require(std::strcmp(FormatName(Native::kFormatR32Typeless), "R32_TYPELESS") == 0,
            "R32_TYPELESS renders by name");
        Require(std::strcmp(DsvDimensionName(Native::kDsvDimensionTexture2DMs), "TEXTURE2DMS") == 0,
            "the multisampled DSV dimension renders by name");

        // An unrecognised value must be reported as null so the caller prints
        // the number. A capture that silently renders every unknown format as
        // "UNKNOWN" cannot be used to qualify anything.
        Require(FormatName(0xDEAD) == nullptr, "an unknown format is not given a name");
        Require(DsvDimensionName(0xBEEF) == nullptr, "an unknown DSV dimension is not given a name");
    }

    void TestIgnoresNonDepth()
    {
        Registry registry;
        Require(registry.Observe(ColourTarget(0x1000)) == Registry::Event::Ignored,
            "a colour target is ignored");
        Require(registry.Size() == 0, "an ignored resource is not recorded");

        TextureFacts nullAddress = ShippedMainDepth(0);
        Require(registry.Observe(nullAddress) == Registry::Event::Ignored,
            "a null resource address is ignored");
    }

    void TestAddAndRecognise()
    {
        Registry registry;
        uint32_t serial = 0;

        Require(registry.Observe(ShippedMainDepth(0x4000), &serial) == Registry::Event::Added,
            "a new depth surface is added");
        Require(serial == 1, "the first surface gets serial 1");
        Require(registry.Size() == 1, "one surface recorded");

        uint32_t again = 0;
        Require(registry.Observe(ShippedMainDepth(0x4000), &again) == Registry::Event::Known,
            "the same surface at the same address is already known");
        Require(again == serial, "a known surface keeps its serial");
        Require(registry.Size() == 1, "a known surface does not add a second entry");
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
        Require(before != nullptr && before->bindCount == 2, "binds accumulate on a live surface");

        // Same address, different surface: a mission change or a resolution
        // change, seen from inside CreateTexture2D.
        TextureFacts resized = ShippedMainDepth(0x5000);
        resized.width = 2560;
        resized.height = 1440;

        uint32_t second = 0;
        Require(registry.Observe(resized, &second) == Registry::Event::Recreated,
            "a reused address carrying a different surface is a recreate");
        Require(second != first, "a recreated surface gets a fresh serial");
        Require(registry.Size() == 1, "a recreate reuses the entry rather than adding one");

        const Observation* after = registry.Find(0x5000);
        Require(after != nullptr, "the recreated surface is findable");
        if (after)
        {
            Require(after->generation == 1, "the generation counts address reuse");
            Require(after->bindCount == 0, "a recreate must not inherit the old bind count");
            Require(after->dsvCount == 0, "a recreate must not inherit the old views");
            Require(after->facts.width == 2560, "the recreated surface carries the new facts");
            Require(!after->everBoundWithRenderTarget, "a recreate starts with no bind history");
        }
    }

    void TestViewsAndBinds()
    {
        Registry registry;
        registry.Observe(ShippedMainDepth(0x6000));

        Require(registry.NoteDepthStencilView(0x6000, Native::kFormatD32Float, Native::kDsvDimensionTexture2DMs),
            "a view over a tracked surface is recorded");
        Require(!registry.NoteDepthStencilView(0x9999, Native::kFormatD32Float, Native::kDsvDimensionTexture2D),
            "a view over an untracked surface is refused rather than invented");
        Require(!registry.NoteBind(0x9999, 1920, 1080, 1),
            "a bind of an untracked surface is refused");

        const Observation* entry = registry.Find(0x6000);
        Require(entry != nullptr && entry->dsvCount == 1, "one view recorded");
        Require(entry != nullptr && entry->dsvDimension == Native::kDsvDimensionTexture2DMs,
            "the view dimension is what tells an MSAA depth view from a plain one");

        // A depth-only pass - a shadow map - binds no render target at all.
        // Keeping that distinct from "bound alongside a full-size target" is
        // the observation the main-view question actually turns on.
        registry.NoteBind(0x6000, 0, 0, 0);
        entry = registry.Find(0x6000);
        Require(entry != nullptr && entry->bindCount == 1, "a depth-only bind still counts as a bind");
        Require(entry != nullptr && !entry->everBoundWithRenderTarget,
            "a depth-only bind must not be recorded as having a render target");

        registry.NoteBind(0x6000, 1920, 1080, 1);
        entry = registry.Find(0x6000);
        Require(entry != nullptr && entry->everBoundWithRenderTarget,
            "a bind alongside a render target is recorded as such");
        Require(entry != nullptr && entry->lastRtWidth == 1920, "the render target size is kept");
    }

    void TestDistinctSurfacesCoexist()
    {
        Registry registry;
        uint32_t mainSerial = 0;
        uint32_t shadowSerial = 0;
        registry.Observe(ShippedMainDepth(0x7000), &mainSerial);
        registry.Observe(ShadowMap(0x7100), &shadowSerial);

        Require(registry.Size() == 2, "two distinct depth surfaces are both tracked");
        Require(mainSerial != shadowSerial, "distinct surfaces get distinct serials");

        registry.NoteBind(0x7000, 1920, 1080, 1);
        registry.NoteBind(0x7100, 0, 0, 0);

        const Observation* main = registry.Find(0x7000);
        const Observation* shadow = registry.Find(0x7100);
        Require(main != nullptr && shadow != nullptr, "both are findable");
        Require(main != nullptr && main->everBoundWithRenderTarget,
            "the main surface is bound with a render target");
        Require(shadow != nullptr && !shadow->everBoundWithRenderTarget,
            "the shadow surface is not");
    }

    void TestOverflowIsReportedNotAbsorbed()
    {
        Registry registry;
        for (size_t i = 0; i < Registry::kCapacity; ++i)
        {
            const uint64_t address = 0x8000 + (static_cast<uint64_t>(i) * 0x100);
            Require(registry.Observe(ShippedMainDepth(address)) == Registry::Event::Added,
                "every surface up to capacity is added");
        }

        Require(registry.Size() == Registry::kCapacity, "the registry fills to capacity");
        Require(!registry.Overflowed(), "a full registry has not yet overflowed");

        Require(registry.Observe(ShippedMainDepth(0xF0000)) == Registry::Event::Overflow,
            "one past capacity overflows");
        Require(registry.Overflowed(), "overflow is recorded so the capture can say so");
        Require(registry.Size() == Registry::kCapacity, "an overflowing surface is not stored");

        // A surface already in the table must still be recognised after
        // overflow, or the capture would go blind exactly when it matters most.
        Require(registry.Observe(ShippedMainDepth(0x8000)) == Registry::Event::Known,
            "a known surface is still recognised after an overflow");

        registry.Clear();
        Require(registry.Size() == 0 && !registry.Overflowed(), "clear resets the registry");
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

    if (g_failures != 0)
    {
        std::printf("scene_depth_facts_tests: %d failure(s)\n", g_failures);
        return 1;
    }

    std::printf("scene_depth_facts_tests: all checks passed\n");
    return 0;
}
