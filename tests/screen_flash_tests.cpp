// Host tests for include/screen_flash.h: the Soft cap arithmetic and the
// call-site constants, without a running game.

#include "screen_flash.h"
#include "sun_flash.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <limits>

namespace
{
    int g_Failures = 0;

    void Check(bool condition, const char* message)
    {
        if (!condition)
        {
            std::fprintf(stderr, "FAIL: %s\n", message);
            ++g_Failures;
        }
    }
}

int main()
{
    using namespace BZROpenShim;
    using ScreenFlash::kSoftExplosionPendingCap;
    using ScreenFlash::SoftPendingAfter;

    // A close explosion that would saturate stock is held at the cap.
    Check(SoftPendingAfter(0.0f, 7.5f) == kSoftExplosionPendingCap, "saturating flash is capped");
    // A distant one passes through unchanged.
    Check(SoftPendingAfter(0.0f, 0.1f) == 0.1f, "small flash passes through");
    // Several explosions in one frame still never exceed the cap.
    float pending = 0.0f;
    for (int i = 0; i < 5; ++i)
        pending = SoftPendingAfter(pending, 0.2f);
    Check(pending == kSoftExplosionPendingCap, "stacked explosions stop at the cap");
    // A larger value already pending (the sun, in stock mode) is left alone.
    Check(SoftPendingAfter(0.9f, 0.5f) == 0.9f, "existing larger pending is not reduced");
    // Garbage in never makes the quad brighter.
    Check(SoftPendingAfter(0.0f, -1.0f) == 0.0f, "negative flash adds nothing");
    Check(SoftPendingAfter(0.0f, std::numeric_limits<float>::quiet_NaN()) == 0.0f,
          "NaN flash adds nothing");
    Check(SoftPendingAfter(0.0f, std::numeric_limits<float>::infinity()) == 0.0f,
          "infinite flash adds nothing");

    // The cap renders as a faint flicker, well under the 224/255 ceiling.
    Check(SunFlash::WhiteoutAlpha(kSoftExplosionPendingCap) == 56, "soft cap is 56/255 alpha");
    Check(ScreenFlash::kSoftDamageScale > 0.0f && ScreenFlash::kSoftDamageScale < 1.0f,
          "soft damage scale reduces without removing");

    // The explosion sites call the same ScreenFlash::AddFlash the sun site does.
    Check(ScreenFlash::kAddFlashAddr == SunFlash::kScreenFlashAddFlashAddr,
          "explosion and sun share AddFlash");
    Check(ScreenFlash::kInstanceAddr == SunFlash::kScreenFlashInstanceAddr,
          "explosion and sun share the ScreenFlash instance");

    // The rel32 operands recorded in scripts/patches.json resolve to the
    // method each site expects.
    const std::int32_t rels[ScreenFlash::kCallSiteCount] = {
        0x0001BEB6,                              // B6 BE 01 00
        static_cast<std::int32_t>(0xFFFEE1F9u),  // F9 E1 FE FF
        static_cast<std::int32_t>(0xFFFF0D30u),  // 30 0D FF FF
        static_cast<std::int32_t>(0xFFFF01B3u),  // B3 01 FF FF
        static_cast<std::int32_t>(0xFFEFA6D4u),  // D4 A6 EF FF
    };
    for (unsigned long i = 0; i < ScreenFlash::kCallSiteCount; ++i)
    {
        const auto& site = ScreenFlash::kCallSites[i];
        const long long resolved = static_cast<long long>(site.opcodeAddr) + 5 + rels[i];
        Check(resolved == static_cast<long long>(site.callee),
              "recorded call site resolves to its ScreenFlash method");
        Check(site.callee == (site.effect == ScreenFlash::Effect::Explosion
                                  ? ScreenFlash::kAddFlashAddr
                                  : ScreenFlash::kAddColorFlashAddr),
              "each effect hooks its own ScreenFlash method");
        Check(ScreenFlash::CallSiteIndex(site.patchName) == static_cast<int>(i),
              "patch name maps back to its site");
    }
    Check(ScreenFlash::CallSiteIndex("Explosion Screen Flash Hook 3/2") == -1,
          "unknown patch name maps to no site");
    Check(ScreenFlash::CallSiteIndex(nullptr) == -1, "null patch name maps to no site");

    if (g_Failures != 0)
        return EXIT_FAILURE;
    std::puts("screen_flash_tests passed");
    return EXIT_SUCCESS;
}
