// Host tests for include/explosion_flash.h: the Soft cap arithmetic and the
// call-site constants, without a running game.

#include "explosion_flash.h"
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
    using ExplosionFlash::kSoftPendingCap;
    using ExplosionFlash::SoftPendingAfter;

    // A close explosion that would saturate stock is held at the cap.
    Check(SoftPendingAfter(0.0f, 7.5f) == kSoftPendingCap, "saturating flash is capped");
    // A distant one passes through unchanged.
    Check(SoftPendingAfter(0.0f, 0.1f) == 0.1f, "small flash passes through");
    // Several explosions in one frame still never exceed the cap.
    float pending = 0.0f;
    for (int i = 0; i < 5; ++i)
        pending = SoftPendingAfter(pending, 0.2f);
    Check(pending == kSoftPendingCap, "stacked explosions stop at the cap");
    // A larger value already pending (the sun, in stock mode) is left alone.
    Check(SoftPendingAfter(0.9f, 0.5f) == 0.9f, "existing larger pending is not reduced");
    // Garbage in never makes the quad brighter.
    Check(SoftPendingAfter(0.0f, -1.0f) == 0.0f, "negative flash adds nothing");
    Check(SoftPendingAfter(0.0f, std::numeric_limits<float>::quiet_NaN()) == 0.0f,
          "NaN flash adds nothing");
    Check(SoftPendingAfter(0.0f, std::numeric_limits<float>::infinity()) == 0.0f,
          "infinite flash adds nothing");

    // The cap renders as a faint flicker, well under the 224/255 ceiling.
    Check(SunFlash::WhiteoutAlpha(kSoftPendingCap) == 56, "soft cap is 56/255 alpha");

    // Both sites call the same ScreenFlash::AddFlash the sun site does.
    Check(ExplosionFlash::kScreenFlashAddFlashAddr == SunFlash::kScreenFlashAddFlashAddr,
          "explosion and sun share AddFlash");
    Check(ExplosionFlash::kScreenFlashInstanceAddr == SunFlash::kScreenFlashInstanceAddr,
          "explosion and sun share the ScreenFlash instance");

    // The rel32 operands recorded in scripts/patches.json resolve to AddFlash.
    const std::int32_t rels[ExplosionFlash::kCallSiteCount] = {
        0x0001BEB6,                        // B6 BE 01 00
        static_cast<std::int32_t>(0xFFFEE1F9u), // F9 E1 FE FF
    };
    for (unsigned long i = 0; i < ExplosionFlash::kCallSiteCount; ++i)
    {
        const long long resolved =
            static_cast<long long>(ExplosionFlash::kCallOpcodeAddrs[i]) + 5 + rels[i];
        Check(resolved == static_cast<long long>(ExplosionFlash::kScreenFlashAddFlashAddr),
              "recorded call site resolves to ScreenFlash::AddFlash");
    }

    if (g_Failures != 0)
        return EXIT_FAILURE;
    std::puts("explosion_flash_tests passed");
    return EXIT_SUCCESS;
}
