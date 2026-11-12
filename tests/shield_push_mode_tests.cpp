#include "shield_push_mode.h"

#include <cmath>
#include <cstdio>
#include "test_check.h"

namespace
{
    using BZROpenShim::ShieldPushMode::Mode;
    using BZROpenShim::ShieldPushMode::ParseOrFront;
    using BZROpenShim::ShieldPushMode::RadialObjectVelocityDelta;
    using BZROpenShim::ShieldPushMode::RadialOrdnanceVelocity;
    using BZROpenShim::ShieldPushMode::RadialOutwardDirection;
    using BZROpenShim::ShieldPushMode::TryParse;

    bool Near(float a, float b)
    {
        return std::fabs(a - b) < 1.0e-4f;
    }

    void TestMissingOrGarbageIsFront()
    {
        CHECK(ParseOrFront(nullptr) == Mode::Front);
        CHECK(ParseOrFront("") == Mode::Front);
        CHECK(ParseOrFront("   ") == Mode::Front);
        CHECK(ParseOrFront("\"\"") == Mode::Front);
        CHECK(ParseOrFront("sphere") == Mode::Front);
        CHECK(ParseOrFront("radiall") == Mode::Front);
        CHECK(ParseOrFront("radia") == Mode::Front);
        CHECK(ParseOrFront("1") == Mode::Front);
        CHECK(ParseOrFront("\"radial") == Mode::Front);
    }

    void TestFrontWords()
    {
        for (const char* word : {"front", "\"front\"", "FRONT", "default", "stock"})
            CHECK(ParseOrFront(word) == Mode::Front);

        Mode mode = Mode::Radial;
        CHECK(TryParse("front", mode));
        CHECK(mode == Mode::Front);
    }

    void TestRadialAndAliases()
    {
        for (const char* word : {"radial", "outward", "bubble", "\"radial\"", "'bubble'",
                                 "  \"Outward\"  ", "RADIAL", "radial\r\n"})
            CHECK(ParseOrFront(word) == Mode::Radial);
    }

    void TestUnrecognizedLeavesOutputAlone()
    {
        Mode mode = Mode::Radial;
        CHECK(!TryParse("nonsense", mode));
        CHECK(mode == Mode::Radial);
        CHECK(!TryParse(nullptr, mode));
        CHECK(mode == Mode::Radial);
    }

    void TestOutwardIsHorizontalAndNormalised()
    {
        const float tower[3] = {100.0f, 20.0f, -50.0f};
        const float front[3] = {0.0f, 0.0f, 1.0f};
        float out[3] = {};

        // Due east of the tower, and well above it: Y is ignored.
        const float east[3] = {110.0f, 45.0f, -50.0f};
        RadialOutwardDirection(tower, east, front, out);
        CHECK(Near(out[0], 1.0f) && Near(out[1], 0.0f) && Near(out[2], 0.0f));

        // Behind the tower (negative Z): pushed further back, not along front.
        const float behind[3] = {100.0f, 20.0f, -80.0f};
        RadialOutwardDirection(tower, behind, front, out);
        CHECK(Near(out[0], 0.0f) && Near(out[2], -1.0f));

        // Diagonal: unit length in XZ.
        const float diagonal[3] = {103.0f, 0.0f, -46.0f};
        RadialOutwardDirection(tower, diagonal, front, out);
        CHECK(Near(out[0], 0.6f) && Near(out[1], 0.0f) && Near(out[2], 0.8f));
    }

    void TestNearAxisFallsBackToFront()
    {
        const float tower[3] = {0.0f, 0.0f, 0.0f};
        const float front[3] = {0.6f, 0.0f, 0.8f};
        float out[3] = {};

        const float onAxis[3] = {0.0f, 30.0f, 0.0f};
        RadialOutwardDirection(tower, onAxis, front, out);
        CHECK(Near(out[0], 0.6f) && Near(out[1], 0.0f) && Near(out[2], 0.8f));

        const float justInside[3] = {0.3f, 0.0f, -0.3f};
        RadialOutwardDirection(tower, justInside, front, out);
        CHECK(Near(out[0], 0.6f) && Near(out[2], 0.8f));

        const float justOutside[3] = {0.0f, 0.0f, -0.6f};
        RadialOutwardDirection(tower, justOutside, front, out);
        CHECK(Near(out[0], 0.0f) && Near(out[2], -1.0f));
    }

    void TestObjectDeltaUsesMagnitudeOfPushAndKeepsDrag()
    {
        const float outward[3] = {1.0f, 0.0f, 0.0f};
        const float velocity[3] = {2.0f, -4.0f, 10.0f};
        float negative[3] = {};
        float positive[3] = {};

        // CR's stock value is negative; both signs repel by the same amount.
        RadialObjectVelocityDelta(outward, -160.0f, 0.5f, velocity, 0.1f, negative);
        RadialObjectVelocityDelta(outward, 160.0f, 0.5f, velocity, 0.1f, positive);
        CHECK(Near(negative[0], 16.0f - 0.1f));
        CHECK(Near(negative[1], 0.2f));
        CHECK(Near(negative[2], -0.5f));
        for (int i = 0; i < 3; ++i)
            CHECK(Near(negative[i], positive[i]));
    }

    void TestInboundShotLosesItsInwardComponent()
    {
        // Shot east of the tower flying straight at it (west), with some
        // tangential (Z) and vertical (Y) motion.
        const float outward[3] = {1.0f, 0.0f, 0.0f};
        float velocity[3] = {-200.0f, 5.0f, 30.0f};
        RadialOrdnanceVelocity(outward, -300.0f, 0.0f, 0.1f, velocity);

        // Inward component cancelled, then pushed outward by |push| * dt.
        CHECK(Near(velocity[0], 30.0f));
        CHECK(Near(velocity[1], 5.0f));
        CHECK(Near(velocity[2], 30.0f));
    }

    void TestOutboundShotIsOnlyPushedAndDamped()
    {
        const float outward[3] = {0.0f, 0.0f, -1.0f};
        float velocity[3] = {10.0f, 0.0f, -100.0f};
        RadialOrdnanceVelocity(outward, -300.0f, 1.0f, 0.1f, velocity);

        // v += outward * 30 - v * 0.1
        CHECK(Near(velocity[0], 10.0f - 1.0f));
        CHECK(Near(velocity[2], -100.0f - 30.0f + 10.0f));
    }

    void TestZeroPushDoesNotDeflect()
    {
        const float outward[3] = {1.0f, 0.0f, 0.0f};
        float velocity[3] = {-200.0f, 0.0f, 0.0f};
        RadialOrdnanceVelocity(outward, 0.0f, 0.0f, 0.1f, velocity);
        CHECK(Near(velocity[0], -200.0f));
    }

    void TestReflectMirrorsAboutNormalAndKeepsSpeed()
    {
        using BZROpenShim::ShieldPushMode::Length;
        using BZROpenShim::ShieldPushMode::ReflectVelocity;

        const float outward[3] = {0.6f, 0.0f, 0.8f};
        float velocity[3] = {-150.0f, 10.0f, -50.0f};
        const float before = Length(velocity);
        // dot = -90 - 40 = -130; v' = v + 260 * n
        ReflectVelocity(outward, velocity);
        CHECK(Near(velocity[0], -150.0f + 156.0f));
        CHECK(Near(velocity[1], 10.0f));
        CHECK(Near(velocity[2], -50.0f + 208.0f));
        CHECK(std::fabs(Length(velocity) - before) < 1.0e-2f);

        // Head-on shot comes straight back.
        const float east[3] = {1.0f, 0.0f, 0.0f};
        float headOn[3] = {-300.0f, 0.0f, 0.0f};
        ReflectVelocity(east, headOn);
        CHECK(Near(headOn[0], 300.0f) && Near(headOn[1], 0.0f) && Near(headOn[2], 0.0f));
    }

    void TestRicochetThreshold()
    {
        using BZROpenShim::ShieldPushMode::IsRicochetCandidate;
        using BZROpenShim::ShieldPushMode::kDefaultReflectSpeed;

        CHECK(Near(kDefaultReflectSpeed, 120.0f));
        const float outward[3] = {1.0f, 0.0f, 0.0f};
        const float slow[3] = {-119.0f, 0.0f, 0.0f};
        const float exact[3] = {-120.0f, 0.0f, 0.0f};
        const float fast[3] = {-90.0f, 0.0f, 90.0f}; // |v| ~ 127
        CHECK(!IsRicochetCandidate(slow, outward, 120.0f));
        CHECK(IsRicochetCandidate(exact, outward, 120.0f));
        CHECK(IsRicochetCandidate(fast, outward, 120.0f));
        // 0 or negative turns ricochet off.
        CHECK(!IsRicochetCandidate(fast, outward, 0.0f));
        CHECK(!IsRicochetCandidate(fast, outward, -5.0f));
    }

    void TestOutboundShotIsNotReflected()
    {
        using BZROpenShim::ShieldPushMode::ShouldRicochet;

        const float outward[3] = {1.0f, 0.0f, 0.0f};
        const float outbound[3] = {300.0f, 0.0f, 0.0f};
        const float tangential[3] = {0.0f, 0.0f, 300.0f};
        CHECK(!ShouldRicochet(outbound, outward, 120.0f, true, true));
        CHECK(!ShouldRicochet(tangential, outward, 120.0f, true, true));
    }

    void TestPredictedStepTriggersRicochet()
    {
        using BZROpenShim::ShieldPushMode::PredictNextPosition;
        using BZROpenShim::ShieldPushMode::ShouldRicochet;

        // A 12 m half-width box centred on the tower at the origin; a 400 m/s
        // shot 15 m east, outside it, will be at 11 m after a 0.01 s step.
        const float tower[3] = {0.0f, 0.0f, 0.0f};
        const float front[3] = {0.0f, 0.0f, 1.0f};
        const float position[3] = {15.0f, 1.0f, 0.0f};
        const float velocity[3] = {-400.0f, 0.0f, 0.0f};
        float outward[3] = {};
        RadialOutwardDirection(tower, position, front, outward);

        float next[3] = {};
        PredictNextPosition(position, velocity, 0.01f, next);
        CHECK(Near(next[0], 11.0f) && Near(next[1], 1.0f) && Near(next[2], 0.0f));

        const bool insideNow = std::fabs(position[0]) < 12.0f;
        const bool insideNext = std::fabs(next[0]) < 12.0f;
        CHECK(!insideNow);
        CHECK(insideNext);
        CHECK(ShouldRicochet(velocity, outward, 120.0f, insideNow, insideNext));
        // Neither now nor next inside: no ricochet.
        CHECK(!ShouldRicochet(velocity, outward, 120.0f, false, false));
    }
}

int main()
{
    TestMissingOrGarbageIsFront();
    TestFrontWords();
    TestRadialAndAliases();
    TestUnrecognizedLeavesOutputAlone();
    TestOutwardIsHorizontalAndNormalised();
    TestNearAxisFallsBackToFront();
    TestObjectDeltaUsesMagnitudeOfPushAndKeepsDrag();
    TestInboundShotLosesItsInwardComponent();
    TestOutboundShotIsOnlyPushedAndDamped();
    TestZeroPushDoesNotDeflect();
    TestReflectMirrorsAboutNormalAndKeepsSpeed();
    TestRicochetThreshold();
    TestOutboundShotIsNotReflected();
    TestPredictedStepTriggersRicochet();
    if (OpenShimTest::FailureCount() == 0)
        std::printf("shield_push_mode_tests: all passed\n");
    return OpenShimTest::ExitCode();
}
