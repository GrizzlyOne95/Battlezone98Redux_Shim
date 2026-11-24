// Trail uniformity: a craft driving a straight line must leave one smooth,
// even trail at any speed and observation rate, not a row of round patches.
//
// Uses the shipping field settings (2 m cells, 7 m radius, 6 s recovery,
// 30 Hz, 120 m/s ceiling). The craft is observed either every tick or only
// every few ticks, since the emitter hook follows flame emission rather than
// the simulation. Pass: along the centreline, no two consecutive samples
// 0.5 m apart differ by more than 10%. The trail still fades from head to
// tail as it refills; that is gradual, so it passes, while a gap does not.
#include "fog_wake_runtime.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include "test_check.h"

using OpenShimTest::Check;

using namespace BZROpenShim::FogWake;

namespace {
    const int kCraft = 0;

    RuntimeConfig ShippingConfig() {
        RuntimeConfig config;
        config.field.width = 256;
        config.field.height = 256;
        config.field.cellSize = 2;
        config.field.origin = {-256, -256};
        config.field.recoverySeconds = 6;
        config.simulationHz = 30;
        config.radius = 7;
        config.strength = 1;
        config.maxSpeed = 120;
        return config;
    }

    struct Result {
        double worstStep = 0; // Largest |a - b| / max(a, b) between neighbours.
        double lowest = 1;    // Lowest sample; the oldest end has refilled most.
        double peak = 0;
    };

    // Drives from x = -length/2 to +length/2 along z = 0.3 (off the cell
    // centres, so the bilinear sample is exercised) and samples the body of
    // the trail as soon as the pass ends. The first and last radius are the
    // rounded ends of the trail, so they are left out.
    Result Drive(double speed, int ticksPerObservation) {
        Runtime runtime;
        Check(runtime.Configure(ShippingConfig()), "configure the runtime");
        runtime.BeginSession(0);
        const double dt = 1.0 / 30.0;
        const double length = 160;
        const double z = 0.3;
        double t = 0;
        double x = -length / 2;
        int tick = 0;
        while (x <= length / 2) {
            if (tick % ticksPerObservation == 0)
                runtime.Observe(&kCraft, {x, z}, t);
            ++tick;
            t = tick * dt;
            x = -length / 2 + speed * t;
            runtime.AdvanceTo(t, {});
        }
        runtime.Observe(&kCraft, {x, z}, t);
        runtime.AdvanceTo(t + dt, {});

        Check(runtime.GetStats().teleports == 0, "a steady pass is never rejected as a teleport");

        Result r;
        const double radius = ShippingConfig().radius;
        double previous = -1;
        for (double s = -length / 2 + radius; s <= length / 2 - radius; s += 0.5) {
            const double v = runtime.GetField().Sample({s, z});
            r.peak = (std::max)(r.peak, v);
            r.lowest = (std::min)(r.lowest, v);
            if (previous >= 0) {
                const double m = (std::max)(v, previous);
                if (m > 0)
                    r.worstStep = (std::max)(r.worstStep, std::abs(v - previous) / m);
            }
            previous = v;
        }
        return r;
    }
}

int main()
{
    // 30 Hz is every tick; 4 and 8 ticks are 7.5 Hz and 3.75 Hz observations.
    for (const double speed : { 5.0, 20.0, 40.0 }) {
        for (const int every : { 1, 4, 8 }) {
            const Result r = Drive(speed, every);
            std::printf("speed=%.0f m/s observe every %d ticks: worst step %.1f%%, lowest %.3f, peak %.3f\n",
                        speed, every, r.worstStep * 100.0, r.lowest, r.peak);
            Check(r.peak > 0.5, "the pass clears the fog");
            Check(r.worstStep <= 0.10, "no dip over 10% between consecutive centreline samples");
        }
    }

    if (!OpenShimTest::FailureCount()) std::puts("fog wake trail tests passed");
    return OpenShimTest::ExitCode();
}
