#pragma once

// Falloff math for the player headlight.
//
// Kept free of Windows and of Ogre so it can be exercised on the host by
// tests/headlight_falloff_tests.cpp. bzr_hooks.cpp reads the live Ogre::Light
// parameters, asks these functions what to write, and writes them back.
//
// Measured stock headlight (BZR 2.2.301 GOG, created at 0x0067F599 and never
// revisited; confirmed live by the [HEADLIGHT-PROBE] instrument):
//
//   type            2 (LT_SPOTLIGHT)
//   diffuse         (1, 1, 1)
//   attenuation     range 600, constant 1.0, linear 0.007, quadratic 0.0002
//   spotlight       inner 10 deg, outer 20 deg, falloff 1.0
//   castShadows     no
//
// Two independent things turn that into a hard bright/dark terrain boundary
// once the shim overrides the headlight:
//
//  1. Cone terminator. The spot factor is
//       spot = ((cos(theta) - cos(outer/2)) / (cos(inner/2) - cos(outer/2)))^falloff
//     clamped to [0, 1] -- identical in D3D9's fixed-function pipeline
//     (D3DLIGHT9.Falloff) and in the DX11 Enhanced HLSL. The shim was writing
//     falloff = 0.35. An exponent below 1 is concave, so the factor leaves zero
//     almost vertically: with a peak of 4 the whole 0 -> saturated ramp fits
//     into 1.9% of the penumbra, which is a step, not a gradient. See
//     VisibleRampFraction.
//
//  2. Range terminator. Attenuation range is a hard clamp, not part of the
//     curve -- past it the light contributes exactly nothing. Stock's 600 m was
//     chosen for a peak of 1.0, where the curve is down to 0.013 there. The
//     shim's colour override multiplies the whole curve, tail included, so at
//     600 m a "White"/"Wide" headlight still delivers 0.052, i.e. 13/255: a
//     visible step, spread over an 86-degree cone.
//
// Note that no (constant, linear, quadratic) triple fixes (2) at a fixed range:
// requiring the near field to stay put pins two points of the denominator, and
// the third then forces a negative linear term. The truncation radius is a
// function of peak intensity, so the honest fix is to recompute it for the
// intensity actually in use rather than to leave stock's radius in place. That
// is what SolveInvisibleRange does -- it is not a "make it big enough to hide
// the seam" constant, and the curve it truncates is untouched.

#include <algorithm>
#include <cmath>

namespace BZROpenShim::HeadlightFalloff
{
    // One 8-bit display step. Below this a light contributes nothing a player
    // can see, so a cutoff there is invisible by construction.
    inline constexpr float kDisplayFloor = 1.0f / 255.0f;

    // Quadratic approach to zero at the outer cone. Stock's 1.0 is linear and
    // already far better than 0.35, but it leaves a first-derivative
    // discontinuity right where the terminator lands; 2.0 removes that and
    // spreads the visible ramp across roughly half the penumbra at the
    // brightness levels the shim uses. The inner cone is unaffected either way,
    // so the strong near-field pool is unchanged.
    inline constexpr float kSmoothSpotFalloff = 2.0f;

    // Never shrink below stock, and never let the solved radius run away: past
    // a few kilometres the light is in every renderable's candidate list for no
    // visible gain.
    inline constexpr float kMinRange = 600.0f;
    // 3600 is the smallest bound that lets the solve land exactly for every
    // headlight the documented palette can produce: the brightest is
    // HeadlightColor=White under HeadlightBeam=Focused, peak 10.0, which needs
    // 3517 m. A hand-set custom colour brighter than that clamps here and the
    // repair log says so rather than pretending the terminator is gone.
    inline constexpr float kMaxRange = 3600.0f;

    struct Attenuation
    {
        float range = 600.0f;
        float constant = 1.0f;
        float linear = 0.007f;
        float quadratic = 0.0002f;
    };

    inline bool IsUsable(const Attenuation& value)
    {
        return std::isfinite(value.range) && value.range > 0.0f &&
               std::isfinite(value.constant) &&
               std::isfinite(value.linear) &&
               std::isfinite(value.quadratic) &&
               value.constant >= 0.0f && value.linear >= 0.0f &&
               value.quadratic >= 0.0f &&
               (value.constant + value.linear + value.quadratic) > 0.0f;
    }

    // Ogre's attenuation curve, before the range clamp.
    inline float IntensityAt(const Attenuation& value, float peakDiffuse, float distance)
    {
        const float denominator =
            value.constant + distance * (value.linear + distance * value.quadratic);
        if (!(denominator > 0.0f) || !std::isfinite(denominator))
            return 0.0f;
        return peakDiffuse / denominator;
    }

    // How much light the range clamp deletes in one step. Anything above
    // kDisplayFloor is a terminator a player can see.
    inline float EdgeIntensity(const Attenuation& value, float peakDiffuse)
    {
        return IntensityAt(value, peakDiffuse, value.range);
    }

    // Smallest distance at which this curve has decayed below the display
    // floor for the given peak. Solves
    //   quadratic*d^2 + linear*d + constant = peakDiffuse / kDisplayFloor
    // and clamps the result into [kMinRange, kMaxRange].
    inline float SolveInvisibleRange(
        const Attenuation& curve,
        float peakDiffuse,
        float minRange = kMinRange,
        float maxRange = kMaxRange)
    {
        if (!IsUsable(curve) || !std::isfinite(peakDiffuse) || peakDiffuse <= 0.0f)
            return (std::max)(minRange, (std::min)(maxRange, curve.range));

        const float target = peakDiffuse / kDisplayFloor;
        const float c = curve.constant - target;
        if (c >= 0.0f)
        {
            // Already below the floor at zero distance; stock range is ample.
            return (std::max)(minRange, (std::min)(maxRange, curve.range));
        }

        float solved = maxRange;
        if (curve.quadratic > 0.0f)
        {
            const float discriminant =
                curve.linear * curve.linear - 4.0f * curve.quadratic * c;
            if (discriminant > 0.0f)
            {
                solved = (-curve.linear + std::sqrt(discriminant)) /
                         (2.0f * curve.quadratic);
            }
        }
        else if (curve.linear > 0.0f)
        {
            solved = -c / curve.linear;
        }

        if (!std::isfinite(solved) || solved <= 0.0f)
            solved = maxRange;
        return (std::max)(minRange, (std::min)(maxRange, solved));
    }

    // Fraction of the cone penumbra over which the spot factor carries the
    // light from the display floor up to saturation -- i.e. the width of the
    // gradient a player actually sees at the cone edge. A value near zero is a
    // hard line; the shipped 0.35 exponent scored 0.019 at peak 4.
    inline float VisibleRampFraction(float peakDiffuse, float falloff)
    {
        if (!std::isfinite(peakDiffuse) || peakDiffuse <= 0.0f ||
            !std::isfinite(falloff) || falloff <= 0.0f)
        {
            return 0.0f;
        }

        const float inverseFalloff = 1.0f / falloff;
        const float saturationT = std::pow((std::min)(1.0f, 1.0f / peakDiffuse), inverseFalloff);
        const float floorT = std::pow(kDisplayFloor / peakDiffuse, inverseFalloff);
        const float ramp = saturationT - floorT;
        return (ramp > 0.0f) ? ramp : 0.0f;
    }

    // A terminator reads as an edge rather than a gradient once the ramp is
    // squeezed into a few percent of the penumbra.
    inline constexpr float kMinAcceptableRampFraction = 0.10f;

    struct Plan
    {
        Attenuation attenuation = {};
        float falloff = kSmoothSpotFalloff;
        // Diagnostics: what the plan achieves versus what it replaced.
        float rangeBefore = 0.0f;
        float edgeIntensityBefore = 0.0f;
        float edgeIntensityAfter = 0.0f;
        float rampFractionBefore = 0.0f;
        float rampFractionAfter = 0.0f;
    };

    // Reach: an optional steeper distance curve for a headlight that lights
    // the ground ahead instead of the whole valley. Stock's curve is so shallow
    // (half intensity at 55 m, 27% left at 100 m) that any colour override
    // bright enough to show on grazing terrain also clips every surface facing
    // the craft out to 100 m and beyond.
    //
    // The shape is the one BZCC's stock spotlights carry (attenuation 1 / 0 /
    // 15 in effects\lights\spot*.odf), read with distance as a fraction of the
    // reach: intensity = peak / (1 + 15 * (d / reach)^2). That is half at
    // 0.26 * reach and 1/16 at the reach itself. Treating BZCC's distance as
    // range-normalised is an assumption (the CPU side was not found in the
    // decompile); the numbers below are what this function guarantees.
    inline constexpr float kReachEdgeDivisor = 15.0f;
    inline constexpr float kMinReach = 30.0f;
    // 250 keeps the truncation solve exact (inside kMaxRange) for the brightest
    // documented headlight, White under Focused at peak 10: 250 * sqrt(2549 / 15)
    // = 3259 m. Its half-strength point, 65 m, is already past stock's 55 m.
    inline constexpr float kMaxReach = 250.0f;
    // HeadlightBeam=Natural when HeadlightReach is absent.
    inline constexpr float kNaturalReach = 120.0f;

    inline float ClampReach(float reach)
    {
        return (std::max)(kMinReach, (std::min)(kMaxReach, reach));
    }

    // The truncation radius is left for SolveInvisibleRange, as for stock.
    inline Attenuation ReachCurve(float reach)
    {
        const float clamped = ClampReach(reach);
        Attenuation curve = {};
        curve.range = clamped;
        curve.constant = 1.0f;
        curve.linear = 0.0f;
        curve.quadratic = kReachEdgeDivisor / (clamped * clamped);
        return curve;
    }

    // `stock` is the curve the engine created; `peakDiffuse` is the brightest
    // channel the shim is about to write. With `reach` 0 the returned plan
    // keeps the stock curve shape exactly -- only the truncation radius and
    // the cone exponent change. A positive `reach` (metres) swaps in
    // ReachCurve and solves its truncation radius the same way.
    inline Plan BuildPlan(
        const Attenuation& stock,
        float peakDiffuse,
        float previousFalloff,
        float reach = 0.0f)
    {
        Plan plan = {};
        const bool useReach = std::isfinite(reach) && reach > 0.0f;
        plan.attenuation = useReach ? ReachCurve(reach) : stock;
        plan.attenuation.range = SolveInvisibleRange(plan.attenuation, peakDiffuse);
        plan.falloff = kSmoothSpotFalloff;
        plan.rangeBefore = stock.range;
        plan.edgeIntensityBefore = EdgeIntensity(stock, peakDiffuse);
        plan.edgeIntensityAfter = EdgeIntensity(plan.attenuation, peakDiffuse);
        plan.rampFractionBefore = VisibleRampFraction(peakDiffuse, previousFalloff);
        plan.rampFractionAfter = VisibleRampFraction(peakDiffuse, plan.falloff);
        return plan;
    }
}
