// Tests for the Daywrecker fall-on-spawn and drop-rate rules (include/daywrecker_spawn_policy.h).

#include "daywrecker_spawn_policy.h"

#include "test_check.h"

#include <cmath>
#include <string>

using OpenShimTest::Check;

namespace
{
    using namespace BZROpenShim::DayWreckerSpawnPolicy;

    void TestKey()
    {
        Check(ParseKey("1") && ParseKey("true") && ParseKey(" yes "), "truthy values arm");
        Check(!ParseKey("0") && !ParseKey("false") && !ParseKey("off"), "falsy values do not");
        Check(!ParseKey(nullptr) && !ParseKey("") && !ParseKey("maybe"), "absent or junk is off");
        Check(std::string(kSection) == "DayWreckerClass" && std::string(kKey) == "fallOnSpawn", "key names");
    }

    void TestArm()
    {
        Check(ShouldArm(true, true, 0), "fresh Daywrecker with the key, single player: arm");
        Check(!ShouldArm(false, true, 0), "network game: never (replicas use the same constructor)");
        Check(!ShouldArm(true, false, 0), "no key: stock");
        Check(!ShouldArm(true, true, kFlagAirborne), "already airborne: leave it");
        Check(!ShouldArm(true, true, kFlagAirborne | kFlagOwnerSafe), "an Armory drop's flags: leave it");
        Check(!ShouldArm(true, true, kFlagDetonated), "already blown: leave it");
        Check(ShouldArm(true, true, kFlagLanded), "other bits do not block");
        Check(ArmedFlags(0) == kFlagAirborne, "arming sets only the airborne bit");
        Check(ArmedFlags(kFlagLanded) == (kFlagLanded | kFlagAirborne), "arming keeps the other bits");
        // The Armory lobber ORs 0xC after construction; arming first must
        // not change what it ends with.
        Check((ArmedFlags(0) | 0xCu) == 0xCu, "an armed Armory drop ends as stock (0xC)");
    }

    bool Near(float a, float b)
    {
        return a - b < 1e-5f && b - a < 1e-5f;
    }

    void TestDropRateParse()
    {
        Check(std::string(kDropRateKey) == "dropRate", "key name");
        Check(Near(ParseDropRate("2"), 2.0f) && Near(ParseDropRate(" 1.5 "), 1.5f), "plain values");
        Check(Near(ParseDropRate("0.5"), 0.5f) && Near(ParseDropRate(".5"), 0.5f), "fractions");
        Check(Near(ParseDropRate("2 ; faster"), 2.0f) && Near(ParseDropRate("2// note"), 2.0f), "trailing comment");
        Check(Near(ParseDropRate("+2"), 2.0f), "leading plus");
        Check(Near(ParseDropRate("10"), kDropRateMax) && Near(ParseDropRate("0.01"), kDropRateMin), "clamped");
        Check(Near(ParseDropRate(nullptr), 1.0f) && Near(ParseDropRate(""), 1.0f), "absent is stock");
        Check(Near(ParseDropRate("fast"), 1.0f) && Near(ParseDropRate("1,5"), 1.0f), "junk (and comma decimals) is stock");
        Check(Near(ParseDropRate("0"), 1.0f) && Near(ParseDropRate("-2"), 1.0f), "zero or negative is stock");
        Check(Near(ParseDropRate("2x"), 1.0f), "trailing junk is stock");
    }

    void TestScaledStep()
    {
        const float dt = 0.1f;
        Check(Near(ScaledStep(true, 2.0f, kFlagAirborne, dt), 0.2f), "airborne, single player: scaled");
        Check(Near(ScaledStep(true, 2.0f, kFlagAirborne | kFlagOwnerSafe | kFlagLanded, dt), 0.2f),
              "whole flight, ascent and descent");
        Check(Near(ScaledStep(true, 0.5f, kFlagAirborne, dt), 0.05f), "slower drops too");
        Check(Near(ScaledStep(false, 2.0f, kFlagAirborne, dt), dt), "network game: stock");
        Check(Near(ScaledStep(true, 1.0f, kFlagAirborne, dt), dt), "stock rate: stock");
        Check(Near(ScaledStep(true, 2.0f, 0, dt), dt), "grounded (the detonation tick): stock");
        Check(Near(ScaledStep(true, 2.0f, kFlagAirborne | kFlagDetonated, dt), dt), "detonated: stock");
    }

    // The claim the key rests on: a larger step is fast-forward, so the
    // flight lands where the stock step lands it, sooner in wall time. Model:
    // gravity plus the descent's 0.1 * vy^2 drag (PowerUp::Simulate), at a
    // 10 Hz sim step.
    void TestTimeScaleKeepsPath()
    {
        auto fly = [](double rate, double& wallTime) {
            double x = 0.0, y = 0.0, vx = 30.0, vy = 50.0;
            const double dt = 0.1;
            wallTime = 0.0;
            for (int i = 0; i < 100000; ++i)
            {
                const double h = dt * rate;
                double ay = -9.8;
                if (vy < 0.0)
                    ay += 0.1 * vy * vy;
                vy += ay * h;
                x += vx * h;
                y += vy * h;
                wallTime += dt;
                if (y <= 0.0)
                    break;
            }
            return x;
        };
        double t1 = 0.0, t2 = 0.0, t3 = 0.0;
        const double x1 = fly(1.0, t1);
        const double x2 = fly(2.0, t2);
        const double x3 = fly(kDropRateMax, t3);
        Check(x1 > 100.0, "the model flies");
        Check(std::fabs(x2 - x1) < 0.05 * x1, "2x lands within 5% of the stock point");
        Check(std::fabs(x3 - x1) < 0.10 * x1, "the cap lands within 10%");
        Check(t2 < t1 * 0.6 && t3 < t1 * 0.45, "and arrives sooner");
    }

    void TestCache()
    {
        ClassCache<2> cache;
        const int a = 0, b = 0, c = 0;
        const ClassKey ka{ &a, 0x61646177u, 0x6B637277u };
        const ClassKey kb{ &b, 1, 2 };
        const ClassKey kc{ &c, 3, 4 };
        bool v = false;
        Check(!cache.Find(ka, v), "empty cache misses");
        cache.Put(ka, true);
        Check(cache.Find(ka, v) && v, "hit after put");
        const ClassKey reused{ &a, 9, 9 };
        Check(!cache.Find(reused, v), "same address, another ODF: miss");
        cache.Put(kb, false);
        Check(cache.Find(kb, v) && !v, "second entry");
        cache.Put(kc, true);
        Check(cache.Find(kc, v) && v, "a third entry replaces one");
        Check(cache.count == 2, "capacity holds");
        cache.Put(kc, false);
        Check(cache.Find(kc, v) && !v && cache.count == 2, "put on an existing key updates in place");
        cache.Clear();
        Check(!cache.Find(kc, v), "clear empties it");
    }

    void TestSettingsCache()
    {
        ClassCache<4, ClassSettings> cache;
        const int a = 0;
        const ClassKey ka{ &a, 1, 2 };
        ClassSettings s;
        s.dropRate = 2.0f;
        cache.Put(ka, s);
        ClassSettings got;
        Check(cache.Find(ka, got) && !got.fallOnSpawn && Near(got.dropRate, 2.0f), "settings round-trip");
        Check(!ClassSettings{}.fallOnSpawn && Near(ClassSettings{}.dropRate, 1.0f), "defaults are stock");
    }
}

int main()
{
    TestKey();
    TestArm();
    TestDropRateParse();
    TestScaledStep();
    TestTimeScaleKeepsPath();
    TestCache();
    TestSettingsCache();
    return OpenShimTest::ExitCode();
}
