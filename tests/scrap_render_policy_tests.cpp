#include "scrap_render_policy.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <limits>

namespace
{
    using namespace BZROpenShim::ScrapRender;

    int g_failures = 0;
    void check(bool ok, const char* text)
    {
        if (!ok)
        {
            std::fprintf(stderr, "FAIL: %s\n", text);
            ++g_failures;
        }
    }

    bool Name(const char* text) { return IsScrapMeshName(text, std::strlen(text)); }
}

int main()
{
    // Setting clamp.
    check(ClampShadowDistanceMetres(-5) == 0, "negative clamps to off");
    check(ClampShadowDistanceMetres(0) == 0, "zero is off");
    check(ClampShadowDistanceMetres(100) == 100, "in range kept");
    check(ClampShadowDistanceMetres(100000) == kMaxShadowDistanceMetres, "too large clamps");

    // Mesh names.
    check(Name("npscr1.mesh"), "npscr1.mesh");
    check(Name("npscr2.mesh"), "npscr2.mesh");
    check(Name("npscr3"), "npscr3 without extension");
    check(Name("NPSCR3.MESH"), "case-insensitive");
    check(Name("npscr12.mesh"), "multi-digit");
    check(!Name("npscr.mesh"), "no digit");
    check(!Name("npscr"), "bare prefix");
    check(!Name("npscr1a.mesh"), "trailing letter");
    check(!Name("npscrap.mesh"), "letters after prefix");
    check(!Name("avtank.mesh"), "craft mesh");
    check(!Name("xnpscr1.mesh"), "prefix must lead");
    check(!Name(".mesh"), "extension only");
    check(!Name(""), "empty");
    check(!IsScrapMeshName(nullptr, 4), "null");

    // Distance decision.
    check(!ShouldSkipShadowCaster(1.0e6f, 0), "off never skips");
    check(!ShouldSkipShadowCaster(1.0e6f, -1), "negative never skips");
    check(!ShouldSkipShadowCaster(100.0f * 100.0f, 100), "exactly at threshold keeps");
    check(ShouldSkipShadowCaster(100.1f * 100.1f, 100), "just past threshold skips");
    check(!ShouldSkipShadowCaster(50.0f * 50.0f, 100), "inside keeps");
    check(!ShouldSkipShadowCaster(std::numeric_limits<float>::quiet_NaN(), 100), "NaN keeps");
    check(ShouldSkipShadowCaster(std::numeric_limits<float>::infinity(), 100), "infinite distance skips");

    // [Fixes] ScrapDrawDistance: clamp and decision.
    check(ClampDrawDistanceMetres(-5) == 0, "draw: negative clamps to off");
    check(ClampDrawDistanceMetres(0) == 0, "draw: zero is off");
    check(ClampDrawDistanceMetres(400) == 400, "draw: in range kept");
    check(ClampDrawDistanceMetres(100000) == kMaxDrawDistanceMetres, "draw: too large clamps");
    check(!ShouldSkipScrapDraw(1.0e6f, 0), "draw: off never skips");
    check(!ShouldSkipScrapDraw(400.0f * 400.0f, 400), "draw: exactly at threshold keeps");
    check(ShouldSkipScrapDraw(400.5f * 400.5f, 400), "draw: just past threshold skips");
    check(!ShouldSkipScrapDraw(std::numeric_limits<float>::quiet_NaN(), 400), "draw: NaN keeps");

    const float a[3] = {0.0f, 0.0f, 0.0f};
    const float b[3] = {3.0f, 4.0f, 12.0f};
    check(DistanceSquared(a, b) == 169.0f, "distance squared");

    // Mesh set.
    ScrapMeshSet<2> set;
    int m1 = 0, m2 = 0, m3 = 0;
    check(!set.Contains(&m1), "empty set");
    check(!set.Add(nullptr), "null not added");
    check(set.Add(&m1) && set.Add(&m1) && set.Live() == 1, "add is idempotent");
    check(set.Add(&m2) && set.Live() == 2, "second add");
    check(!set.Add(&m3) && !set.Contains(&m3), "full set refuses");
    check(set.Remove(&m1) && !set.Contains(&m1) && set.Live() == 1, "remove");
    check(!set.Remove(&m1), "remove twice");
    check(set.Add(&m3) && set.Contains(&m3) && set.Contains(&m2), "slot reused");

    // Cascade order (telemetry only).
    ShadowCameraOrder order;
    int c0 = 0, c1 = 0, c2 = 0, c3 = 0;
    check(order.IndexFor(&c0) == 0, "first camera");
    check(order.IndexFor(&c0) == 0, "repeat first camera");
    check(order.IndexFor(&c1) == 1, "second camera");
    check(order.IndexFor(&c2) == 2, "third camera");
    check(order.IndexFor(&c3) == kTrackedCascades, "overflow bucket");
    check(order.IndexFor(&c1) == 1, "earlier camera keeps index");
    order.Reset();
    check(order.IndexFor(&c2) == 0, "reset renumbers");

    // [Fixes] ScrapGlow parsing: override only on a parsed value.
    bool glow = true;
    check(TryParseScrapGlowSetting("0", glow) && !glow, "0 is off");
    check(TryParseScrapGlowSetting(" 1", glow) && glow, "1 is on");
    check(TryParseScrapGlowSetting("00", glow) && !glow, "00 is off");
    check(TryParseScrapGlowSetting("2", glow) && glow, "non-zero is on");
    glow = false;
    check(!TryParseScrapGlowSetting("", glow) && !glow, "empty leaves value");
    check(!TryParseScrapGlowSetting("off", glow) && !glow, "text leaves value");
    check(!TryParseScrapGlowSetting(nullptr, glow) && !glow, "null leaves value");

    // Glow pass identification.
    check(IsGlowPass(true, false, "glow"), "main camera, other viewport, glow scheme");
    check(!IsGlowPass(true, true, "glow"), "main viewport is not glow");
    check(!IsGlowPass(false, false, "glow"), "other camera is not glow");
    check(!IsGlowPass(true, false, "Default"), "other scheme is not glow");
    check(!IsGlowPass(true, false, "glowx"), "longer scheme is not glow");
    check(!IsGlowPass(true, false, nullptr), "null scheme is not glow");

    // Skip only scrap, only in the glow pass, only when the setting is off.
    check(ShouldSkipGlowSubmission(false, true, true), "off + scrap + glow skips");
    check(!ShouldSkipGlowSubmission(true, true, true), "stock never skips");
    check(!ShouldSkipGlowSubmission(false, false, true), "non-scrap kept");
    check(!ShouldSkipGlowSubmission(false, true, false), "main view kept");

    if (g_failures)
    {
        std::fprintf(stderr, "%d failure(s)\n", g_failures);
        return 1;
    }
    std::printf("scrap_render_policy_tests: all passed\n");
    return 0;
}
