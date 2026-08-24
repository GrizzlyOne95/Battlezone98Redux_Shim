// sun_flash_tests.cpp
// Host-side checks for the sun whiteout model documented in include/sun_flash.h.
//
// These pin the two claims the opt-out rests on:
//   1. the angular term is a narrow dot^32 window, so the flash is an
//      almost-on-axis effect and not general sun brightness;
//   2. the flash value saturates ScreenFlash::Render's clamp for any realistic
//      occlusion-query pixel count, which is why partial occlusion does not
//      visibly dim it.
//
// The address constants are checked too, so an accidental edit to the patch
// target is caught here rather than at runtime on a player's machine.

#include "sun_flash.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace BZROpenShim;

namespace
{
    int g_Failures = 0;

    void Check(bool condition, const char* message)
    {
        if (!condition)
        {
            std::fprintf(stderr, "sun_flash_tests: %s\n", message);
            ++g_Failures;
        }
    }

    void CheckNear(double actual, double expected, double tolerance, const char* message)
    {
        if (!(std::fabs(actual - expected) <= tolerance))
        {
            std::fprintf(stderr,
                         "sun_flash_tests: %s (actual=%.6f expected=%.6f)\n",
                         message, actual, expected);
            ++g_Failures;
        }
    }

    float DotAtDegrees(double degrees)
    {
        return static_cast<float>(std::cos(degrees * 3.14159265358979323846 / 180.0));
    }

    void TestAngularWindowIsNarrow()
    {
        // Dead on axis the term is 1 by construction.
        CheckNear(SunFlash::AngularTerm(1.0f), 1.0, 1e-6, "dot=1 must give 1");

        // The numbers quoted in sun_flash.h.
        CheckNear(SunFlash::AngularTerm(DotAtDegrees(15.0)), 0.33, 0.02,
                  "15 degrees off axis should be about a third");
        CheckNear(SunFlash::AngularTerm(DotAtDegrees(30.0)), 0.0097, 0.002,
                  "30 degrees off axis should be about one percent");

        // Monotone falloff across the window, so "sweep across the sun and the
        // flash rises then falls" is a property of the model, not an accident
        // of one sample.
        float previous = SunFlash::AngularTerm(DotAtDegrees(0.0));
        for (double degrees = 1.0; degrees <= 45.0; degrees += 1.0)
        {
            const float current = SunFlash::AngularTerm(DotAtDegrees(degrees));
            Check(current <= previous, "angular term must not rise as the sun moves off axis");
            previous = current;
        }
        Check(previous < 1e-4f, "the term must be negligible 45 degrees off axis");
    }

    void TestFlashSaturatesOnRealisticPixelCounts()
    {
        // ScreenFlash::Render clamps at 1.0 and scales by 224.
        Check(SunFlash::WhiteoutAlpha(0.0f) == 0, "no pending flash means no quad");
        Check(SunFlash::WhiteoutAlpha(-1.0f) == 0, "a negative pending flash means no quad");
        Check(SunFlash::WhiteoutAlpha(1.0f) == SunFlash::kScreenFlashMaxAlpha,
              "pending of exactly 1 is the ceiling");
        Check(SunFlash::WhiteoutAlpha(50.0f) == SunFlash::kScreenFlashMaxAlpha,
              "anything above 1 clamps to the ceiling");
        Check(SunFlash::WhiteoutAlpha(0.5f) == SunFlash::kScreenFlashMaxAlpha / 2,
              "below the clamp the alpha is linear");

        // A visible sun covers thousands of query pixels. Even 10 degrees off
        // axis, and even with a scale small enough to be plausible, the product
        // is far past the clamp -- that is the whole reason it reads as a
        // flashbang rather than a glow.
        const float onAxis = SunFlash::FlashAmount(1.0f, 4000, 0.01f);
        Check(onAxis > 1.0f, "on axis the flash must be past the clamp");
        Check(SunFlash::WhiteoutAlpha(onAxis) == SunFlash::kScreenFlashMaxAlpha,
              "on axis the quad must be at full white");

        const float offAxis = SunFlash::FlashAmount(DotAtDegrees(10.0), 4000, 0.01f);
        Check(offAxis > 1.0f, "10 degrees off axis is still past the clamp");

        // Halving the visible pixels halves a saturated value, which is still
        // saturated: this is the occlusion observation stated in the header.
        const float halfOccluded = SunFlash::FlashAmount(1.0f, 2000, 0.01f);
        Check(SunFlash::WhiteoutAlpha(halfOccluded) == SunFlash::kScreenFlashMaxAlpha,
              "half-occluded sun must still saturate");

        // Far enough off axis it genuinely goes away, so the effect is bounded.
        const float wellOffAxis = SunFlash::FlashAmount(DotAtDegrees(40.0), 4000, 0.01f);
        Check(SunFlash::WhiteoutAlpha(wellOffAxis) < SunFlash::kScreenFlashMaxAlpha,
              "40 degrees off axis must not saturate");
    }

    void TestPatchTargetsAreTheOnesDocumented()
    {
        Check(SunFlash::kAddFlashCallOperandAddr == SunFlash::kAddFlashCallOpcodeAddr + 1,
              "the rel32 operand must sit immediately after the CALL opcode");
        Check(SunFlash::kAddFlashCallOpcodeAddr == 0x004F9FD3ul,
              "call site moved without the header being updated");
        Check(SunFlash::kScreenFlashAddFlashAddr == 0x0049B4C0ul,
              "ScreenFlash::AddFlash moved without the header being updated");
        Check(SunFlash::kScreenFlashInstanceAddr == 0x0097838Cul,
              "the global ScreenFlash moved without the header being updated");

        // The stock operand bytes E8 14 FA FF are the little-endian encoding of
        // that call's displacement.
        const long long rel = static_cast<long long>(0xFFFA14E8u) - 0x100000000LL;
        const long long resolved =
            static_cast<long long>(SunFlash::kAddFlashCallOperandAddr) + 4 + rel;
        Check(resolved == static_cast<long long>(SunFlash::kScreenFlashAddFlashAddr),
              "the guard bytes in scripts/patches.json must encode the stock target");
    }
}

int main()
{
    TestAngularWindowIsNarrow();
    TestFlashSaturatesOnRealisticPixelCounts();
    TestPatchTargetsAreTheOnesDocumented();

    if (g_Failures != 0)
    {
        std::fprintf(stderr, "sun_flash_tests: %d check(s) failed\n", g_Failures);
        return EXIT_FAILURE;
    }
    std::printf("sun_flash_tests: all checks passed\n");
    return EXIT_SUCCESS;
}
