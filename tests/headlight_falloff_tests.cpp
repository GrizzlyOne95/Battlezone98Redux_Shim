// Regression tests for the player headlight's falloff repair.
//
// The two hard terminators these pin are the ones measured live by the
// [HEADLIGHT-PROBE] instrument on BZR 2.2.301 GOG:
//   * a cone edge collapsed into 1.9% of the penumbra by a 0.35 falloff
//     exponent, and
//   * an attenuation-range clamp that still deleted 13/255 of light in one
//     step because the shim's colour override lifted the whole curve.
// Both are asserted here as measured quantities, so a regression is a number
// that moved rather than a screenshot somebody has to squint at.

#include "headlight_falloff.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>

namespace
{
    using namespace BZROpenShim::HeadlightFalloff;

    [[noreturn]] void Fail(const char* message)
    {
        std::fprintf(stderr, "headlight_falloff_tests: %s\n", message);
        std::exit(1);
    }

    void Require(bool condition, const char* message)
    {
        if (!condition)
            Fail(message);
    }

    void RequireNear(double actual, double expected, double tolerance, const char* message)
    {
        if (!(std::fabs(actual - expected) <= tolerance))
        {
            std::fprintf(stderr,
                "headlight_falloff_tests: %s (actual=%.6f expected=%.6f)\n",
                message, actual, expected);
            std::exit(1);
        }
    }

    // Exactly what Ogre::Light::setAttenuation is given at 0x0067F599.
    Attenuation StockCurve()
    {
        Attenuation stock = {};
        stock.range = 600.0f;
        stock.constant = 1.0f;
        stock.linear = 0.007f;
        stock.quadratic = 0.0002f;
        return stock;
    }

    // Peak diffuse the shim writes for HeadlightColor=White at each beam:
    // 5.0 scaled by the per-beam multiplier.
    constexpr float kWidePeak = 4.0f;      // 5.0 * 0.8
    constexpr float kFocusedPeak = 10.0f;  // 5.0 * 2.0
    constexpr float kStockPeak = 1.0f;

    void TestStockCurveMatchesTheLiveMeasurement()
    {
        const Attenuation stock = StockCurve();
        // Values the probe printed for the untouched engine headlight.
        RequireNear(EdgeIntensity(stock, kStockPeak), 0.012953, 1e-5,
            "stock edge intensity drifted from the measured 0.01295");
        RequireNear(EdgeIntensity(stock, kWidePeak), 0.051813, 1e-5,
            "wide-beam edge intensity drifted from the measured 0.05181");

        // And that the wide-beam value really is a step a player can see.
        Require(EdgeIntensity(stock, kWidePeak) > kDisplayFloor * 10.0f,
            "the pre-fix range terminator is no longer above the display floor, "
            "so this regression guard is meaningless");
    }

    void TestShippedFalloffExponentWasAHardEdge()
    {
        // 0.35 is what the shim used to write for both Focused and Wide.
        const float shipped = VisibleRampFraction(kWidePeak, 0.35f);
        Require(shipped < 0.03f,
            "the 0.35 exponent no longer collapses the cone ramp, so this "
            "regression guard is meaningless");
        RequireNear(shipped, 0.019f, 0.005,
            "the measured pre-fix ramp fraction moved");

        // Even stock's linear exponent is only marginal at these brightnesses,
        // which is why the repair does not simply restore 1.0.
        Require(VisibleRampFraction(kWidePeak, 1.0f) < kMinAcceptableRampFraction * 3.0f,
            "linear falloff unexpectedly produces a wide ramp");
    }

    void TestSmoothFalloffWidensTheConeRamp()
    {
        for (const float peak : { kStockPeak, kWidePeak, kFocusedPeak })
        {
            Require(VisibleRampFraction(peak, kSmoothSpotFalloff) >= kMinAcceptableRampFraction,
                "the smooth exponent left the cone ramp below the acceptable width");
        }

        // At peak 1.0 nothing is clipped, so even the 0.35 exponent already
        // spans the penumbra and there is nothing to widen. The overbright
        // cases are the ones that were reading as a hard line.
        for (const float peak : { kWidePeak, kFocusedPeak })
        {
            Require(VisibleRampFraction(peak, kSmoothSpotFalloff) >
                        VisibleRampFraction(peak, 0.35f) * 5.0f,
                "the smooth exponent did not materially widen the cone ramp");
        }
    }

    void TestSolvedRangeHidesTheAttenuationTerminator()
    {
        const Attenuation stock = StockCurve();
        for (const float peak : { kStockPeak, kWidePeak, kFocusedPeak })
        {
            Attenuation solved = stock;
            solved.range = SolveInvisibleRange(stock, peak);

            Require(solved.range >= stock.range,
                "the solved range shrank below stock");
            Require(solved.range <= kMaxRange,
                "the solved range exceeded the clamp");
            // Focused clamps at kMaxRange, so allow the clamp to bite while
            // still requiring the step to be at most one display level.
            Require(EdgeIntensity(solved, peak) <= kDisplayFloor * 2.05f,
                "the solved range still leaves a visible step at the cutoff");
        }
    }

    void TestSolvedRangeIsNotAFudgeFactor()
    {
        // The point of solving rather than picking a constant: the radius has
        // to track intensity. A brighter headlight must push the cutoff out.
        const Attenuation stock = StockCurve();
        const float dimRange = SolveInvisibleRange(stock, kStockPeak);
        const float wideRange = SolveInvisibleRange(stock, kWidePeak);
        const float focusedRange = SolveInvisibleRange(stock, kFocusedPeak);

        Require(dimRange < wideRange, "a 4x brighter light did not move the cutoff out");
        Require(wideRange <= focusedRange, "a 10x brighter light did not move the cutoff out");

        // Even at stock brightness the curve only reaches the display floor at
        // about 1110 m, so stock's own 600 m cutoff was already deleting
        // 3.3/255 in one step -- invisible inside a 20-degree cone, plainly not
        // invisible once the shim opens that cone to 86 degrees. The solve
        // therefore moves it out even here.
        RequireNear(dimRange, 1109.6, 1.0, "stock-brightness solve moved");
        Require(dimRange > kMinRange, "stock brightness should still clear its own cutoff");
    }

    void TestNearFieldIsUntouched()
    {
        // The repair changes only the truncation radius, never the curve, so
        // every distance a player actually drives through must be bit-identical.
        const Attenuation stock = StockCurve();
        Attenuation repaired = stock;
        repaired.range = SolveInvisibleRange(stock, kWidePeak);

        RequireNear(repaired.constant, stock.constant, 0.0, "constant term changed");
        RequireNear(repaired.linear, stock.linear, 0.0, "linear term changed");
        RequireNear(repaired.quadratic, stock.quadratic, 0.0, "quadratic term changed");

        for (const float distance : { 0.0f, 5.0f, 25.0f, 50.0f, 100.0f, 200.0f, 400.0f })
        {
            RequireNear(
                IntensityAt(repaired, kWidePeak, distance),
                IntensityAt(stock, kWidePeak, distance),
                0.0,
                "the repair changed the near/mid-field intensity");
        }
    }

    void TestPlanReportsBothTerminators()
    {
        const Plan plan = BuildPlan(StockCurve(), kWidePeak, 0.35f);

        RequireNear(plan.rangeBefore, 600.0, 0.0, "plan lost the original range");
        Require(plan.attenuation.range > plan.rangeBefore,
            "plan did not move the cutoff for an overbright light");
        Require(plan.edgeIntensityBefore > kDisplayFloor,
            "plan did not see the pre-fix range terminator");
        // The solve lands the edge exactly on the floor, so allow float slack.
        Require(plan.edgeIntensityAfter <= kDisplayFloor * 1.05f,
            "plan did not clear the range terminator");
        Require(plan.rampFractionAfter > plan.rampFractionBefore * 5.0f,
            "plan did not widen the cone ramp");
        RequireNear(plan.falloff, kSmoothSpotFalloff, 0.0, "plan used an unexpected exponent");
    }

    void TestDegenerateInputsAreRefusedNotPropagated()
    {
        Attenuation broken = {};
        broken.range = 0.0f;
        Require(!IsUsable(broken), "a zero range was accepted");

        Attenuation notFinite = StockCurve();
        notFinite.quadratic = std::nanf("");
        Require(!IsUsable(notFinite), "a non-finite curve was accepted");

        Attenuation zeroed = StockCurve();
        zeroed.constant = 0.0f;
        zeroed.linear = 0.0f;
        zeroed.quadratic = 0.0f;
        Require(!IsUsable(zeroed), "an all-zero denominator was accepted");

        // A usable curve with a nonsense peak must fall back to the input range
        // rather than emit a garbage radius.
        const Attenuation stock = StockCurve();
        RequireNear(SolveInvisibleRange(stock, -1.0f), stock.range, 0.0,
            "a negative peak did not fall back to the input range");
        RequireNear(SolveInvisibleRange(stock, std::nanf("")), stock.range, 0.0,
            "a non-finite peak did not fall back to the input range");

        Require(VisibleRampFraction(0.0f, kSmoothSpotFalloff) == 0.0f,
            "a zero peak did not report a zero ramp");
        Require(VisibleRampFraction(kWidePeak, 0.0f) == 0.0f,
            "a zero exponent did not report a zero ramp");
    }

    void TestLinearOnlyAndConstantOnlyCurves()
    {
        // Other BZR lights use different curve shapes; the solver must not
        // divide by a zero quadratic term.
        Attenuation linearOnly = {};
        linearOnly.range = 100.0f;
        linearOnly.constant = 1.0f;
        linearOnly.linear = 0.05f;
        linearOnly.quadratic = 0.0f;
        const float solved = SolveInvisibleRange(linearOnly, 2.0f, 10.0f, 100000.0f);
        RequireNear(IntensityAt(linearOnly, 2.0f, solved), kDisplayFloor, 1e-4,
            "the linear-only solve missed the display floor");

        Attenuation constantOnly = {};
        constantOnly.range = 100.0f;
        constantOnly.constant = 1.0f;
        constantOnly.linear = 0.0f;
        constantOnly.quadratic = 0.0f;
        // Never decays, so the solve has to clamp rather than loop or diverge.
        RequireNear(SolveInvisibleRange(constantOnly, 2.0f, 10.0f, 5000.0f), 5000.0, 0.0,
            "a non-decaying curve did not clamp to the maximum range");
    }
}

int main()
{
    TestStockCurveMatchesTheLiveMeasurement();
    TestShippedFalloffExponentWasAHardEdge();
    TestSmoothFalloffWidensTheConeRamp();
    TestSolvedRangeHidesTheAttenuationTerminator();
    TestSolvedRangeIsNotAFudgeFactor();
    TestNearFieldIsUntouched();
    TestPlanReportsBothTerminators();
    TestDegenerateInputsAreRefusedNotPropagated();
    TestLinearOnlyAndConstantOnlyCurves();
    std::printf("headlight_falloff_tests: all checks passed\n");
    return 0;
}
