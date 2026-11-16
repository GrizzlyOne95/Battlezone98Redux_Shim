#include "soak_telemetry_policy.h"

#include <cstdio>

namespace
{
    using namespace BZROpenShim::SoakTelemetry;

    int g_failures = 0;
    void check(bool ok, const char* text)
    {
        if (!ok)
        {
            std::fprintf(stderr, "FAIL: %s\n", text);
            ++g_failures;
        }
    }

    void TestColour()
    {
        const float a[3] = {0.5f, 0.5f, 0.5f};
        const float drift[3] = {0.55f, 0.45f, 0.57f};
        const float step[3] = {0.5f, 0.6f, 0.5f};
        check(!ColourJumped(a, a), "identical colour is not a jump");
        check(!ColourJumped(a, drift), "deltas <= 0.08 are drift");
        check(ColourJumped(a, step), "a 0.1 channel step is a jump");
    }

    void TestDirection()
    {
        const float x[3] = {1, 0, 0};
        const float small[3] = {1, 0.05f, 0};   // ~2.9 degrees
        const float large[3] = {1, 0.1f, 0};    // ~5.7 degrees
        const float scaled[3] = {3, 0, 0};
        const float zero[3] = {0, 0, 0};
        check(!DirectionJumped(x, small), "under 5 degrees is drift");
        check(DirectionJumped(x, large), "over 5 degrees is a jump");
        check(!DirectionJumped(x, scaled), "length alone is not a direction change");
        check(DirectionJumped(x, zero), "a direction collapsing to zero is a jump");
        check(!DirectionJumped(zero, zero), "zero to zero is not a jump");
    }

    void TestFog()
    {
        check(!FogDistanceJumped(100.0f, 109.0f), "9% fog move is drift");
        check(FogDistanceJumped(100.0f, 111.0f), "11% fog move is a jump");
        check(FogDistanceJumped(100.0f, 50.0f), "halving is a jump");
        check(!FogDistanceJumped(0.0f, 0.5f), "sub-unit move from 0 is drift");
        check(FogDistanceJumped(0.0f, 200.0f), "fog appearing from 0 is a jump");
    }

    void TestRateLimits()
    {
        FieldRateLimit field;
        check(field.Allow(1000), "first field line passes");
        check(!field.Allow(2999), "second line inside 2 s is held");
        check(field.Allow(3000), "line after 2 s passes");

        CaptureBudget budget;
        check(budget.Allow(0), "first capture passes");
        check(!budget.Allow(9999), "capture inside 10 s is held");
        unsigned taken = 1;
        for (uint64_t t = 10000; t < 10000ull * 100; t += 10000)
        {
            if (budget.Allow(t))
                ++taken;
        }
        check(taken == kCaptureLimit, "captures are capped per process");
    }

    void TestStall()
    {
        StallTracker tracker;
        uint64_t ms = 0;
        tracker.Reset(0);
        check(tracker.Tick(0, 5, true, 1000, ms) == StallEvent::None, "first sample primes");
        check(tracker.Tick(100, 6, true, 1000, ms) == StallEvent::None, "progress is not a stall");
        check(tracker.Tick(900, 6, true, 1000, ms) == StallEvent::None, "800 ms is under threshold");
        check(tracker.Tick(1100, 6, true, 1000, ms) == StallEvent::Began && ms == 1000,
              "1000 ms without progress begins one episode");
        check(tracker.Tick(1500, 6, true, 1000, ms) == StallEvent::None, "one line per episode");
        check(tracker.Tick(2600, 7, true, 1000, ms) == StallEvent::Ended && ms == 2500,
              "progress ends the episode with its full length");
        check(tracker.Tick(2700, 7, false, 1000, ms) == StallEvent::None, "idle is not a stall");
        check(tracker.Tick(5000, 7, false, 1000, ms) == StallEvent::None, "long idle is not a stall");
        check(tracker.Tick(5100, 7, true, 1000, ms) == StallEvent::None,
              "the clock restarts when work appears after idle");
        check(tracker.Tick(6100, 7, true, 1000, ms) == StallEvent::Began && ms == 1100,
              "stall measured from the last idle tick");
        check(tracker.Tick(6200, 7, false, 1000, ms) == StallEvent::Ended && ms == 1200,
              "catching up (nothing pending) ends the episode");

        tracker.Reset(7000);
        check(!tracker.inEpisode, "reset clears an episode");
        check(tracker.Tick(7000, 1, true, 1000, ms) == StallEvent::None, "reset re-primes");
    }
}

int main()
{
    TestColour();
    TestDirection();
    TestFog();
    TestRateLimits();
    TestStall();
    if (g_failures)
    {
        std::fprintf(stderr, "%d soak telemetry policy check(s) failed\n", g_failures);
        return 1;
    }
    std::printf("soak telemetry policy tests passed\n");
    return 0;
}
