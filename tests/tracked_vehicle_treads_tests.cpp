// Tests for the classLabel=tracked tread visual and sound math
// (include/tracked_vehicle_treads.h).

#include "tracked_vehicle_treads.h"
#include "tracked_vehicle_physics.h"

#include <cmath>
#include <cstdio>
#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    using namespace BZROpenShim::TrackedTreads;
    namespace TP = BZROpenShim::TrackedPhysics;

    void CheckNear(double actual, double expected, double tolerance, const char* message)
    {
        if (!(std::fabs(actual - expected) <= tolerance))
        {
            OpenShimTest::Fail("%s (actual=%.6f expected=%.6f)", message, actual, expected);
        }
    }

    void TestCycleLengthIsSanitized()
    {
        CheckNear(SanitizeCycleLength(2.5f), 2.5, 1e-6, "in range kept");
        CheckNear(SanitizeCycleLength(0.0f), kDefaultCycleLength, 1e-6, "zero is the default");
        CheckNear(SanitizeCycleLength(-3.0f), kDefaultCycleLength, 1e-6, "negative is the default");
        CheckNear(SanitizeCycleLength(NAN), kDefaultCycleLength, 1e-6, "NaN is the default");
        CheckNear(SanitizeCycleLength(0.001f), kMinCycleLength, 1e-6, "tiny clamps up");
        CheckNear(SanitizeCycleLength(1.0e6f), kMaxCycleLength, 1e-6, "huge clamps down");
    }

    void TestTreadSpeedIsRateLimited()
    {
        // Speeding up from rest at accelThrust.
        CheckNear(StepTreadSpeed(0.0f, 20.0f, 20.0f, 75.0f, 0.1f), 2.0, 1e-5, "gains at accelThrust");
        CheckNear(StepTreadSpeed(0.0f, -10.0f, 20.0f, 75.0f, 0.1f), -2.0, 1e-5, "reverse gains at accelThrust");
        // Slowing and reversing at accelBrake.
        CheckNear(StepTreadSpeed(20.0f, 0.0f, 20.0f, 75.0f, 0.1f), 12.5, 1e-5, "slows at accelBrake");
        CheckNear(StepTreadSpeed(5.0f, -5.0f, 20.0f, 75.0f, 0.1f), -2.5, 1e-5, "reversal brakes");
        // Reaches the target without overshoot.
        CheckNear(StepTreadSpeed(19.5f, 20.0f, 20.0f, 75.0f, 0.1f), 20.0, 1e-6, "lands on target");
        CheckNear(StepTreadSpeed(0.5f, 0.0f, 20.0f, 75.0f, 0.1f), 0.0, 1e-6, "stops at rest");
        // Garbage in keeps the current value or resets it.
        CheckNear(StepTreadSpeed(3.0f, NAN, 20.0f, 75.0f, 0.1f), 3.0, 1e-6, "NaN target holds");
        CheckNear(StepTreadSpeed(NAN, 1.0f, 20.0f, 75.0f, 0.1f), 1.0, 1e-6, "NaN current restarts at 0");
        CheckNear(StepTreadSpeed(3.0f, 1.0f, 20.0f, 75.0f, 0.0f), 3.0, 1e-6, "zero dt holds");
        CheckNear(StepTreadSpeed(3.0f, 10.0f, -1.0f, 75.0f, 0.1f), 3.0, 1e-6, "negative rate holds");
    }

    void TestPhysicsTreadSignsDriveTheClips()
    {
        // The contact model's commanded tread speeds: forward drives both
        // clips forward, a left pivot runs L backward and R forward.
        TP::Config config;
        TP::Footprint footprint;
        TP::Drive drive;
        TP::Body body;
        body.py = 0.5;
        auto flat = [](void*, double, double, double, double& h, TP::Vec3& n) {
            h = 0.0;
            n = { 0.0f, 1.0f, 0.0f };
            return true;
        };
        TP::Inputs forward;
        forward.throttle = 1.0f;
        const TP::Result f = TP::Step(config, footprint, drive, body, forward, 0.02f, flat, nullptr);
        Check(f.leftTread > 0.0f && f.rightTread > 0.0f, "forward: both treads positive");
        Check(ClipAdvance(f.leftTread, 0.02f, 1.0f, 1.0f) > 0.0f, "forward: L clip runs forward");

        TP::Inputs pivot;
        pivot.steer = 1.0f;  // +1 turns left
        const TP::Result p = TP::Step(config, footprint, drive, body, pivot, 0.02f, flat, nullptr);
        Check(p.leftTread < 0.0f && p.rightTread > 0.0f, "left pivot: L backward, R forward");
        CheckNear(p.leftTread, -p.rightTread, 1e-4, "pivot treads are equal and opposite");

        const TP::Result rest = TP::Step(config, footprint, drive, body, TP::Inputs{}, 0.02f, flat, nullptr);
        CheckNear(rest.leftTread, 0.0, 1e-6, "rest: L still");
        CheckNear(rest.rightTread, 0.0, 1e-6, "rest: R still");
    }

    void TestSpeedFraction()
    {
        CheckNear(SpeedFraction(10.0f, 5.0f, 20.0f), 0.5, 1e-6, "faster tread over velocForward");
        CheckNear(SpeedFraction(-8.0f, 8.0f, 20.0f), 0.4, 1e-6, "pivot counts magnitude");
        CheckNear(SpeedFraction(40.0f, 0.0f, 20.0f), 1.0, 1e-6, "capped at 1");
        CheckNear(SpeedFraction(5.0f, 5.0f, 0.0f), 0.0, 1e-6, "no velocForward is silent");
        CheckNear(SpeedFraction(NAN, 5.0f, 20.0f), 0.0, 1e-6, "NaN is silent");
    }

    void TestClipAdvance()
    {
        // 2 m/s for 0.5 s on a 4 m cycle is a quarter loop of a 2 s clip.
        CheckNear(ClipAdvance(2.0f, 0.5f, 2.0f, 4.0f), 0.5, 1e-6, "quarter loop");
        CheckNear(ClipAdvance(-2.0f, 0.5f, 2.0f, 4.0f), -0.5, 1e-6, "reverse runs backward");
        CheckNear(ClipAdvance(0.0f, 0.5f, 2.0f, 4.0f), 0.0, 1e-6, "still at rest");
        CheckNear(ClipAdvance(1000.0f, 1.0f, 2.0f, 1.0f), 2.0, 1e-6, "at most one loop per step");
        CheckNear(ClipAdvance(-1000.0f, 1.0f, 2.0f, 1.0f), -2.0, 1e-6, "and one loop backward");
        CheckNear(ClipAdvance(2.0f, 0.5f, 0.0f, 4.0f), 0.0, 1e-6, "empty clip does not move");
        CheckNear(ClipAdvance(2.0f, 0.5f, 2.0f, 0.0f), 2.0, 1e-6, "bad cycle uses the 1 m default");
        CheckNear(ClipAdvance(NAN, 0.5f, 2.0f, 4.0f), 0.0, 1e-6, "NaN speed does not move");
    }

    void TestTreadSoundMirrorsStockThrust()
    {
        const SoundLevel off = TreadSound(0.05f, true);
        Check(!off.play, "silent at the 0.05 gate");
        Check(!TreadSound(NAN, false).play, "NaN is silent");

        const SoundLevel userHalf = TreadSound(0.5f, true);
        Check(userHalf.play, "plays above the gate");
        Check(userHalf.volume == 8, "user volume 5 + 5t, rounded");
        Check(userHalf.rate == 13781, "rate 11025 + 5512.5t, rounded");

        const SoundLevel aiFull = TreadSound(1.0f, false);
        Check(aiFull.volume == 50, "AI volume is five times the user's");
        Check(aiFull.rate == 16538, "full-speed rate");

        Check(TreadSound(2.0f, true).rate == aiFull.rate, "fraction capped at 1");
        Check(TreadSound(0.2f, true).rate < TreadSound(0.8f, true).rate, "pitch rises with speed");
    }

    void TestLoopIsHeldThroughShortDips()
    {
        float quiet = 0.0f;
        Check(KeepLoop(true, quiet, 0.5f, 1.5f) && quiet == 0.0f, "playing keeps the loop");
        Check(KeepLoop(false, quiet, 0.5f, 1.5f), "0.5 s quiet keeps it");
        Check(KeepLoop(false, quiet, 0.5f, 1.5f), "1.0 s quiet keeps it");
        Check(KeepLoop(true, quiet, 0.5f, 1.5f) && quiet == 0.0f, "speeding up again resets the hold");
        // Many short steps add up the same as few long ones.
        for (int i = 0; i < 289; ++i)
            KeepLoop(false, quiet, 0.005f, 1.5f);
        Check(KeepLoop(false, quiet, 0.005f, 1.5f), "1.45 s of short quiet steps still keeps it");
        for (int i = 0; i < 19; ++i)
            KeepLoop(false, quiet, 0.005f, 1.5f);
        Check(!KeepLoop(false, quiet, 0.005f, 1.5f), "1.55 s of short quiet steps stops it");
        Check(quiet < 1.6f, "and the timer stops growing");
        float bad = NAN;
        Check(KeepLoop(false, bad, 0.1f, 1.5f) && bad == 0.1f, "a NaN timer restarts");
        Check(KeepLoop(false, bad, NAN, 1.5f) && bad == 0.1f, "a NaN dt adds nothing");
        float none = 0.0f;
        Check(!KeepLoop(false, none, 0.1f, 0.0f), "no hold stops at once");
    }
}

int main()
{
    TestLoopIsHeldThroughShortDips();
    TestCycleLengthIsSanitized();
    TestTreadSpeedIsRateLimited();
    TestPhysicsTreadSignsDriveTheClips();
    TestSpeedFraction();
    TestClipAdvance();
    TestTreadSoundMirrorsStockThrust();
    if (OpenShimTest::ExitCode() == 0)
        std::printf("tracked_vehicle_treads_tests: all checks passed\n");
    return OpenShimTest::ExitCode();
}
