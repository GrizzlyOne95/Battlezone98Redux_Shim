#include "ai_range_policy.h"

#include <cmath>
#include <cstdio>
#include <limits>

using namespace BZROpenShim;

namespace
{
    int g_Failures = 0;

    void Check(bool condition, const char* what)
    {
        if (condition)
            return;
        std::fprintf(stderr, "FAIL: %s\n", what);
        ++g_Failures;
    }

    bool Near(float actual, float expected)
    {
        return std::fabs(actual - expected) <= 0.001f;
    }

    AiRangePolicy::Inputs Stock(float closeRange = 10.0f,
                                float range = 155.0f,
                                float time = 0.5f)
    {
        AiRangePolicy::Inputs inputs = {};
        inputs.closeRange = closeRange;
        inputs.range = range;
        inputs.time = time;
        return inputs;
    }

    void TestNoAuthoredPolicyIsExactPassThrough()
    {
        const AiRangePolicy::Inputs inputs = Stock();
        const AiRangePolicy::Result result = AiRangePolicy::Apply(inputs);
        Check(result.closeRange == inputs.closeRange, "stock close range must stay exact");
        Check(result.range == inputs.range, "stock outer range must stay exact");
        Check(result.time == inputs.time, "stock weapon time must stay exact");
        Check(!result.rangeChanged && !result.closeRangeChanged && !result.timeChanged,
              "stock pass-through must report no mutations");
    }

    void TestEngageRangeFloorsOuterWeaponRange()
    {
        AiRangePolicy::Inputs inputs = Stock();
        AiRangePolicy::AccumulatePositiveFloor(
            inputs.hasOuterRangeFloor, inputs.outerRangeFloor, 240.0f);
        const AiRangePolicy::Result result = AiRangePolicy::Apply(inputs);
        Check(Near(result.range, 240.0f), "engageRangeAI must raise 155 to 240");
        Check(result.closeRange == inputs.closeRange,
              "engageRangeAI must not invent a close/standoff ring");

        inputs = Stock();
        AiRangePolicy::AccumulatePositiveFloor(
            inputs.hasOuterRangeFloor, inputs.outerRangeFloor, 120.0f);
        const AiRangePolicy::Result lower = AiRangePolicy::Apply(inputs);
        Check(lower.range == 155.0f,
              "engageRangeAI below the stock weapon range must preserve stock maximum");
    }

    void TestWeaponMinimumFloorsNativeCloseRange()
    {
        AiRangePolicy::Inputs inputs = Stock();
        AiRangePolicy::AccumulatePositiveFloor(
            inputs.hasCloseRangeFloor, inputs.closeRangeFloor, 60.0f);
        const AiRangePolicy::Result result = AiRangePolicy::Apply(inputs);
        Check(result.range == 155.0f,
              "weaponRangeMinAI must not replace the stock outer weapon range");
        Check(Near(result.closeRange, 60.0f),
              "weaponRangeMinAI must floor the native too-close threshold");

        inputs = Stock();
        AiRangePolicy::AccumulatePositiveFloor(
            inputs.hasCloseRangeFloor, inputs.closeRangeFloor, 240.0f);
        const AiRangePolicy::Result capped = AiRangePolicy::Apply(inputs);
        Check(Near(capped.closeRange, 139.5f),
              "the close floor must stay at most 90 percent of the outer range");
    }

    void TestCombinedPolicyAndBomberCompatibility()
    {
        AiRangePolicy::Inputs combined = Stock();
        AiRangePolicy::AccumulatePositiveFloor(
            combined.hasOuterRangeFloor, combined.outerRangeFloor, 240.0f);
        AiRangePolicy::AccumulatePositiveFloor(
            combined.hasCloseRangeFloor, combined.closeRangeFloor, 200.0f);
        const AiRangePolicy::Result result = AiRangePolicy::Apply(combined);
        Check(Near(result.range, 240.0f) && Near(result.closeRange, 200.0f),
              "engage and close floors must form one non-empty native firing band");

        // The inherited BomberFriend/BomberEnemy ordnance fallback remains an
        // outer range floor. This is deliberately separate from authored
        // weaponRangeMinAI wingman standoff behavior.
        AiRangePolicy::Inputs bomber = Stock(15.0f, 50.0f, 0.5f);
        AiRangePolicy::AccumulatePositiveFloor(
            bomber.hasOuterRangeFloor, bomber.outerRangeFloor, 299.0f);
        const AiRangePolicy::Result bomberResult = AiRangePolicy::Apply(bomber);
        Check(Near(bomberResult.range, 299.0f),
              "the inherited bomber ordnance fallback must remain 299 m");
        Check(bomberResult.closeRange == 15.0f,
              "the inherited bomber fallback must not become new wingman standoff work");
    }

    void TestInvalidFloorsFailClosed()
    {
        AiRangePolicy::Inputs inputs = Stock(10.0f, 155.0f, 0.0f);
        Check(!AiRangePolicy::AccumulatePositiveFloor(
                  inputs.hasOuterRangeFloor,
                  inputs.outerRangeFloor,
                  std::numeric_limits<float>::quiet_NaN()),
              "NaN range floors must be rejected");
        Check(!AiRangePolicy::AccumulatePositiveFloor(
                  inputs.hasCloseRangeFloor, inputs.closeRangeFloor, -20.0f),
              "non-positive close floors must be rejected");
        const AiRangePolicy::Result result = AiRangePolicy::Apply(inputs);
        Check(result.range == 155.0f && result.closeRange == 10.0f && result.time == 0.0f,
              "invalid authored floors must leave all stock outputs untouched");

        AiRangePolicy::AccumulatePositiveFloor(
            inputs.hasOuterRangeFloor, inputs.outerRangeFloor, 200.0f);
        const AiRangePolicy::Result valid = AiRangePolicy::Apply(inputs);
        Check(valid.time == 1.0f && valid.timeChanged,
              "a valid range policy must retain the existing positive-time fallback");
    }
}

int main()
{
    TestNoAuthoredPolicyIsExactPassThrough();
    TestEngageRangeFloorsOuterWeaponRange();
    TestWeaponMinimumFloorsNativeCloseRange();
    TestCombinedPolicyAndBomberCompatibility();
    TestInvalidFloorsFailClosed();

    if (g_Failures != 0)
    {
        std::fprintf(stderr, "ai_range_policy_tests: %d check(s) failed\n", g_Failures);
        return 1;
    }
    std::printf("ai_range_policy_tests: all checks passed\n");
    return 0;
}
