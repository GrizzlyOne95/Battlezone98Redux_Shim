#include "fog_wake_runtime.h"

#include <cmath>
#include <cstdio>
#include <limits>

using namespace BZROpenShim::FogWake;

namespace {
    int failures = 0;
    void Check(bool value, const char* message) {
        if (!value) { std::fprintf(stderr, "FAIL: %s\n", message); ++failures; }
    }

    // Two emitter identities. The runtime keys on the pointer value only; it
    // never dereferences these, exactly as it never dereferences an engine
    // object pointer.
    const int kCraftA = 0;
    const int kCraftB = 0;
    const void* CraftA() { return &kCraftA; }
    const void* CraftB() { return &kCraftB; }

    RuntimeConfig MakeConfig() {
        RuntimeConfig config;
        config.field.width = 64;
        config.field.height = 64;
        config.field.cellSize = 1;
        config.field.origin = {-32, -32};
        config.field.recoverySeconds = 1000; // Slow, so tests measure stamping.
        // 8 Hz gives a 0.125 s tick, which is exact in binary. A decimal cadence
        // makes assertions on per-call tick counts measure double rounding
        // instead of the runtime: 0.3 - 0.2 is a hair under 0.1.
        config.simulationHz = 8;
        config.maxCatchUpSeconds = 4;        // Room for the cadence tests.
        config.radius = 3;
        config.strength = 1;
        config.maxSpeed = 40;                // 5 m per tick.
        config.forgetAfterSeconds = 1;
        return config;
    }
}

int main()
{
    // --- fails closed -------------------------------------------------------
    {
        Runtime runtime;
        Check(!runtime.Enabled(), "a runtime is disabled until configured");
        Check(!runtime.Observe(CraftA(), {0, 0}, 0), "a disabled runtime refuses observations");
        Check(runtime.AdvanceTo(1, {}) == 0, "a disabled runtime does not simulate");

        RuntimeConfig bad = MakeConfig();
        bad.simulationHz = 0;
        Check(!runtime.Configure(bad), "a zero cadence is refused");
        Check(!runtime.Enabled(), "a refused configuration leaves the runtime disabled");

        bad = MakeConfig();
        bad.field.width = 0;
        Check(!runtime.Configure(bad), "an invalid field is refused");
        Check(!runtime.Enabled(), "a refused field leaves the runtime disabled");

        bad = MakeConfig();
        bad.strength = 2;
        Check(!runtime.Configure(bad), "clearance strength above one is refused");
    }

    // --- observation never simulates ---------------------------------------
    // The engine hooks that report emitters can run any number of times per
    // simulation step, including once per camera. Advancing on observation
    // would make the wake depend on the number of cameras and on frame rate.
    {
        Runtime runtime;
        Check(runtime.Configure(MakeConfig()), "configure the runtime");
        runtime.BeginSession(0);
        for (int i = 0; i < 100; ++i)
            runtime.Observe(CraftA(), {0, 0}, 0);
        Check(runtime.GetStats().steps == 0, "observation alone never steps the simulation");
        Check(runtime.GetField().Sample({0, 0}) == 0, "observation alone never stamps");
        Check(runtime.TrackedEmitters() == 1, "repeat observations track one emitter");
    }

    // --- a fixed cadence, whatever the caller does --------------------------
    {
        Runtime runtime;
        Check(runtime.Configure(MakeConfig()), "configure the runtime");
        runtime.BeginSession(0);
        runtime.Observe(CraftA(), {0.5, 0.5}, 0);

        // Called once per camera at the same instant: only the first can step.
        Check(runtime.AdvanceTo(1.0, {}) == 8, "one second at 8 Hz is eight ticks");
        Check(runtime.AdvanceTo(1.0, {}) == 0, "a repeated timestamp adds no ticks");
        Check(runtime.AdvanceTo(1.0, {}) == 0, "a third camera adds no ticks either");
        Check(runtime.GetStats().steps == 8,
            "per-camera calls do not multiply the simulation rate");

        // A partial tick is banked, not dropped or rounded up.
        Check(runtime.AdvanceTo(1.0625, {}) == 0, "half a tick does not step");
        Check(runtime.AdvanceTo(1.125, {}) == 1, "the banked remainder completes a tick");
    }

    // --- a stall does not repay itself as a burst ---------------------------
    {
        RuntimeConfig config = MakeConfig();
        config.maxCatchUpSeconds = 0.25; // At 8 Hz, at most two ticks.
        Runtime runtime;
        Check(runtime.Configure(config), "configure the runtime");
        runtime.BeginSession(0);
        Check(runtime.AdvanceTo(60.0, {}) <= 2, "a one minute stall is clamped, not replayed");
    }

    // --- a clock that goes backwards is not negative time -------------------
    {
        Runtime runtime;
        Check(runtime.Configure(MakeConfig()), "configure the runtime");
        runtime.BeginSession(100);
        Check(runtime.AdvanceTo(50, {}) == 0, "a backwards clock simulates nothing");
        Check(runtime.AdvanceTo(51, {}) == 8, "and the runtime resumes from the new clock");
    }

    // --- pause freezes simulation time --------------------------------------
    {
        Runtime runtime;
        Check(runtime.Configure(MakeConfig()), "configure the runtime");
        runtime.BeginSession(0);
        runtime.Observe(CraftA(), {0.5, 0.5}, 0);
        runtime.AdvanceTo(0.5, {});
        const auto beforePause = runtime.GetStats().steps;
        Check(beforePause == 4, "half a second at 8 Hz is four ticks");

        runtime.SetPaused(true, 0.5);
        Check(runtime.AdvanceTo(30.0, {}) == 0, "a paused runtime does not simulate");
        Check(runtime.GetStats().steps == beforePause, "a pause freezes simulation time");

        runtime.SetPaused(false, 30.0);
        Check(runtime.AdvanceTo(30.0625, {}) == 0,
            "resuming does not discharge the paused interval as catch-up");
    }

    // --- a sweep carves a continuous corridor -------------------------------
    {
        Runtime runtime;
        Check(runtime.Configure(MakeConfig()), "configure the runtime");
        runtime.BeginSession(0);

        // 4 m per 0.125 s tick, under the 5 m teleport threshold.
        double t = 0;
        for (int i = 0; i <= 5; ++i) {
            runtime.Observe(CraftA(), {-10.5 + 4.0 * i, 0.5}, t);
            t += 0.125;
            runtime.AdvanceTo(t, {});
        }
        Check(runtime.GetStats().stamps >= 5, "each tick stamps the distance travelled");
        for (double x = -10.5; x <= 9.5; x += 1.0)
            Check(runtime.GetField().Sample({x, 0.5}) > 0.9,
                "the corridor is continuous between observations");
        Check(runtime.GetField().Sample({-10.5, 8.5}) == 0, "fog beside the corridor is untouched");
    }

    // --- a teleport is rejected but still reseeds ---------------------------
    // The doc calls this out specifically: dropping the sweep without moving the
    // origin only delays the bogus streak by one tick.
    {
        Runtime runtime;
        Check(runtime.Configure(MakeConfig()), "configure the runtime");
        runtime.BeginSession(0);

        runtime.Observe(CraftA(), {-20.5, 0.5}, 0);
        runtime.AdvanceTo(0.125, {});

        runtime.Observe(CraftA(), {20.5, 0.5}, 0.125); // 41 m in one tick.
        runtime.AdvanceTo(0.25, {});
        Check(runtime.GetStats().teleports == 1, "a jump beyond max speed is rejected");
        Check(runtime.GetField().Sample({0.5, 0.5}) == 0, "a teleport carves no trail");

        // The very next tick must measure from the destination.
        runtime.Observe(CraftA(), {22.5, 0.5}, 0.25);
        runtime.AdvanceTo(0.375, {});
        Check(runtime.GetStats().teleports == 1, "the tick after a teleport is an ordinary sweep");
        Check(runtime.GetField().Sample({21.5, 0.5}) > 0.5, "and it stamps from the destination");
        Check(runtime.GetField().Sample({0.5, 0.5}) == 0, "the rejected streak never appears late");
    }

    // --- handle reuse looks like a teleport, not a streak -------------------
    {
        Runtime runtime;
        Check(runtime.Configure(MakeConfig()), "configure the runtime");
        runtime.BeginSession(0);
        runtime.Observe(CraftA(), {-25.5, 10.5}, 0);
        runtime.AdvanceTo(0.125, {});

        // Same pointer, different object: the engine recycled the allocation.
        runtime.Observe(CraftA(), {25.5, 10.5}, 0.125);
        runtime.AdvanceTo(0.25, {});
        Check(runtime.GetField().Sample({0.5, 10.5}) == 0,
            "a recycled handle does not draw a wake across the map");
    }

    // --- stale emitters are dropped -----------------------------------------
    {
        Runtime runtime;
        Check(runtime.Configure(MakeConfig()), "configure the runtime");
        runtime.BeginSession(0);
        runtime.Observe(CraftA(), {0.5, 0.5}, 0);
        runtime.Observe(CraftB(), {5.5, 5.5}, 0);
        Check(runtime.TrackedEmitters() == 2, "two emitters tracked");

        // B keeps reporting; A goes quiet past the staleness window.
        double t = 0;
        for (int i = 0; i < 20; ++i) {
            t += 0.125;
            runtime.Observe(CraftB(), {5.5, 5.5}, t);
            runtime.AdvanceTo(t, {});
        }
        Check(runtime.TrackedEmitters() == 1, "an emitter that stopped reporting is dropped");
        Check(runtime.GetStats().forgotten >= 1, "and the drop is counted");
    }

    // --- explicit destruction -----------------------------------------------
    {
        Runtime runtime;
        Check(runtime.Configure(MakeConfig()), "configure the runtime");
        runtime.BeginSession(0);
        runtime.Observe(CraftA(), {0.5, 0.5}, 0);
        runtime.Forget(CraftA());
        Check(runtime.TrackedEmitters() == 0, "a destroyed emitter is forgotten immediately");
        runtime.Forget(CraftA());
        Check(runtime.TrackedEmitters() == 0, "forgetting an unknown emitter is harmless");
    }

    // --- the emitter ceiling refuses rather than recycles --------------------
    {
        RuntimeConfig config = MakeConfig();
        config.maxEmitters = 1;
        Runtime runtime;
        Check(runtime.Configure(config), "configure the runtime");
        runtime.BeginSession(0);
        Check(runtime.Observe(CraftA(), {0.5, 0.5}, 0), "the first emitter is tracked");
        Check(!runtime.Observe(CraftB(), {5.5, 5.5}, 0), "the ceiling refuses a new emitter");
        Check(runtime.TrackedEmitters() == 1,
            "and does not evict the emitter whose history it already holds");
    }

    // --- session transitions -------------------------------------------------
    {
        Runtime runtime;
        Check(runtime.Configure(MakeConfig()), "configure the runtime");
        runtime.BeginSession(0);
        runtime.Observe(CraftA(), {0.5, 0.5}, 0);
        runtime.AdvanceTo(0.125, {});
        Check(runtime.GetField().Sample({0.5, 0.5}) > 0, "a wake exists before the transition");

        runtime.BeginSession(500);
        Check(runtime.GetField().Sample({0.5, 0.5}) == 0, "a new session starts in undisturbed fog");
        Check(runtime.TrackedEmitters() == 0, "a new session tracks no emitters");
        Check(runtime.AdvanceTo(500.0625, {}) == 0,
            "and the session clock does not treat the gap as elapsed time");
    }

    // --- malformed input -----------------------------------------------------
    {
        Runtime runtime;
        Check(runtime.Configure(MakeConfig()), "configure the runtime");
        runtime.BeginSession(0);
        const double nan = std::numeric_limits<double>::quiet_NaN();
        const double inf = std::numeric_limits<double>::infinity();
        Check(!runtime.Observe(nullptr, {0, 0}, 0), "a null emitter is refused");
        Check(!runtime.Observe(CraftA(), {nan, 0}, 0), "a NaN position is refused");
        Check(!runtime.Observe(CraftA(), {0, inf}, 0), "an infinite position is refused");
        Check(!runtime.Observe(CraftA(), {0, 0}, nan), "a NaN timestamp is refused");
        Check(runtime.TrackedEmitters() == 0, "no malformed observation is tracked");
        Check(runtime.AdvanceTo(nan, {}) == 0, "a NaN clock simulates nothing");
        Check(runtime.AdvanceTo(1.0, {inf, 0}) == 0, "an infinite wind simulates nothing");
    }

    // --- shutdown ------------------------------------------------------------
    {
        Runtime runtime;
        Check(runtime.Configure(MakeConfig()), "configure the runtime");
        runtime.BeginSession(0);
        runtime.Observe(CraftA(), {0.5, 0.5}, 0);
        runtime.AdvanceTo(0.125, {});
        runtime.Shutdown();
        Check(!runtime.Enabled(), "shutdown disables the runtime");
        Check(runtime.GetField().Sample({0.5, 0.5}) == 0, "shutdown clears the field");
        Check(!runtime.Observe(CraftA(), {0.5, 0.5}, 0), "a shut down runtime refuses observations");
    }

    if (!failures) std::puts("fog wake runtime tests passed");
    return failures ? 1 : 0;
}
