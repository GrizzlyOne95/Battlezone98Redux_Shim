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

    void TestScrollUIsSanitized()
    {
        CheckNear(SanitizeScrollU(1.5f), 1.5, 1e-6, "in range kept");
        CheckNear(SanitizeScrollU(-2.0f), -2.0, 1e-6, "negative kept: flips direction");
        CheckNear(SanitizeScrollU(0.0f), 0.0, 1e-6, "zero is off");
        CheckNear(SanitizeScrollU(NAN), 0.0, 1e-6, "NaN is off");
        CheckNear(SanitizeScrollU(INFINITY), 0.0, 1e-6, "infinity is off");
        CheckNear(SanitizeScrollU(1.0e6f), kMaxScrollU, 1e-6, "huge clamps down");
        CheckNear(SanitizeScrollU(-1.0e6f), -kMaxScrollU, 1e-6, "huge negative clamps up");
    }

    void TestPhaseWrapsIntoUnitRange()
    {
        CheckNear(WrapPhase(0.25f), 0.25, 1e-6, "in range kept");
        CheckNear(WrapPhase(1.25f), 0.25, 1e-6, "wraps down past 1");
        CheckNear(WrapPhase(-0.25f), 0.75, 1e-6, "negative wraps up, not to -0.25 (fmod)");
        CheckNear(WrapPhase(-1.75f), 0.25, 1e-6, "more than one loop negative");
        CheckNear(WrapPhase(1.0f), 0.0, 1e-6, "1 is 0");
        Check(WrapPhase(-1.0e-9f) < 1.0f, "tiny negative never rounds to 1");
        CheckNear(WrapPhase(NAN), 0.0, 1e-6, "NaN restarts at 0");
    }

    void TestScrollPhaseFollowsSignedSpeed()
    {
        // 2 m/s for 0.5 s on a 4 m cycle at one loop per cycle: a quarter loop.
        CheckNear(StepScrollPhase(0.0f, 2.0f, 0.5f, 1.0f, 4.0f), 0.25, 1e-6, "forward quarter loop");
        CheckNear(StepScrollPhase(0.5f, -2.0f, 0.5f, 1.0f, 4.0f), 0.25, 1e-6, "reverse runs backward");
        CheckNear(StepScrollPhase(0.0f, 2.0f, 0.5f, -1.0f, 4.0f), 0.75, 1e-6, "negative scrollU flips");
        CheckNear(StepScrollPhase(0.0f, 2.0f, 0.5f, 2.0f, 4.0f), 0.5, 1e-6, "two loops per cycle");

        // Wrap across 0 in both directions.
        CheckNear(StepScrollPhase(0.9f, 2.0f, 0.1f, 1.0f, 1.0f), 0.1, 1e-5, "forward wraps past 1");
        CheckNear(StepScrollPhase(0.1f, -2.0f, 0.1f, 1.0f, 1.0f), 0.9, 1e-5, "reverse wraps below 0");

        // A sustained reverse keeps decreasing (mod 1) and stays in range.
        float phase = 0.0f;
        for (int i = 0; i < 1000; ++i)
        {
            phase = StepScrollPhase(phase, -7.3f, 0.016f, 1.0f, 1.3f);
            if (!(phase >= 0.0f && phase < 1.0f))
            {
                OpenShimTest::Fail("reverse phase left [0,1) at step %d: %f", i, phase);
                break;
            }
        }
        const double travelled = -7.3 * 0.016 * 1000.0 / 1.3;
        CheckNear(phase, travelled - std::floor(travelled), 2e-3, "long reverse lands where the belt moved");

        // Pivot: L backward, R forward, from the same start.
        const float left = StepScrollPhase(0.5f, -3.0f, 0.05f, 1.0f, 1.0f);
        const float right = StepScrollPhase(0.5f, 3.0f, 0.05f, 1.0f, 1.0f);
        CheckNear(left, 0.35, 1e-5, "pivot: L scrolls back");
        CheckNear(right, 0.65, 1e-5, "pivot: R scrolls forward");

        // Off and garbage.
        CheckNear(StepScrollPhase(0.4f, 2.0f, 0.5f, 0.0f, 4.0f), 0.0, 1e-6, "scroll off is 0");
        CheckNear(StepScrollPhase(0.4f, NAN, 0.5f, 1.0f, 4.0f), 0.4, 1e-6, "NaN speed holds");
        CheckNear(StepScrollPhase(0.4f, 2.0f, 0.0f, 1.0f, 4.0f), 0.4, 1e-6, "zero dt holds");
        CheckNear(StepScrollPhase(0.0f, 1.0f, 0.25f, 1.0f, 0.0f), 0.25, 1e-6, "bad cycle uses the 1 m default");
        CheckNear(StepScrollPhase(NAN, 1.0f, 0.25f, 1.0f, 1.0f), 0.25, 1e-6, "NaN phase restarts at 0");
    }

    void TestTreadMaterialSet()
    {
        static TreadMaterialSet set;  // 8 KB; keep it off the stack
        Check(set.Count() == 0 && set.Revision() == 0, "starts empty");
        Check(!set.Contains("svtank_treadL"), "empty set contains nothing");
        Check(set.Add("svtank_treadL"), "adds a name");
        Check(set.Revision() == 1, "a new name bumps the revision");
        Check(set.Add("svtank_treadL") && set.Revision() == 1, "a repeat is accepted without a bump");
        Check(set.Contains("svtank_treadL"), "contains the added name");
        Check(!set.Contains("SVTANK_TREADL"), "case-sensitive like Ogre names");
        Check(!set.Contains("OpenShim/GpuSkin/3/w4/svtank_treadL"), "clone names are not source names");
        Check(!set.Contains("") && !set.Contains(nullptr), "empty or null never matches");
        Check(!set.Add("") && !set.Add(nullptr), "empty or null is refused");
        char longName[kTreadMaterialBytes + 1];
        std::memset(longName, 'a', kTreadMaterialBytes);
        longName[kTreadMaterialBytes] = 0;
        Check(!set.Add(longName), "an over-long name is refused");
        char name[16];
        for (size_t i = set.Count(); i < kMaxRegisteredTreadMaterials; ++i)
        {
            std::snprintf(name, sizeof(name), "tread%u", static_cast<unsigned>(i));
            set.Add(name);
        }
        Check(set.Count() == kMaxRegisteredTreadMaterials, "fills to the cap");
        Check(!set.Add("one_too_many"), "a full set refuses a new name (caller fails closed)");
        Check(set.Add("svtank_treadL"), "a full set still accepts a known name");
        Check(set.Revision() == kMaxRegisteredTreadMaterials, "one bump per distinct name");

        // AddBoth: all or nothing.
        static TreadMaterialSet pair;
        char fill[16];
        for (size_t i = 0; i + 1 < kMaxRegisteredTreadMaterials; ++i)
        {
            std::snprintf(fill, sizeof(fill), "fill%u", static_cast<unsigned>(i));
            pair.Add(fill);
        }
        const uint32_t before = pair.Revision();
        Check(!pair.AddBoth("newL", "newR"), "two new names with one free slot are refused");
        Check(!pair.Contains("newL") && !pair.Contains("newR") && pair.Revision() == before,
              "a refused pair adds neither name");
        Check(pair.AddBoth("fill0", "newL"), "a known name plus one new name fits the last slot");
        Check(pair.Contains("fill0") && pair.Contains("newL"), "both are present");
        Check(!pair.AddBoth("newR", ""), "a full set refuses a new single name");
        Check(pair.AddBoth("fill1", "newL"), "two known names still pass when full");
        Check(pair.AddBoth("", "fill2"), "an empty side is skipped");
        Check(!pair.AddBoth("", ""), "two empty names are refused");
        Check(!pair.AddBoth(nullptr, nullptr), "two null names are refused");
        Check(!pair.AddBoth("fill0", longName), "an over-long side refuses the pair");
        static TreadMaterialSet same;
        Check(same.AddBoth("tread", "tread") && same.Count() == 1, "equal names take one slot");

        Check(MaterialNameHash("OpenShim/GpuSkin/3/w4/a") != MaterialNameHash("OpenShim/GpuSkin/4/w4/a"),
              "a new skinning generation hashes differently");
        Check(MaterialNameHash("a") == MaterialNameHash("a"), "hash is stable");
    }

    void TestTreadMaterialMatching()
    {
        Check(MatchesTreadMaterial("svtank_treadL", "svtank_treadL"), "exact name matches");
        Check(!MatchesTreadMaterial("svtank_treadL2", "svtank_treadL"), "longer name does not");
        Check(!MatchesTreadMaterial("svtank_tread", "svtank_treadL"), "shorter name does not");
        Check(!MatchesTreadMaterial("SVTANK_TREADL", "svtank_treadL"), "Ogre names are case-sensitive");
        Check(MatchesTreadMaterial("OpenShim/GpuSkin/3/w4/svtank_treadL", "svtank_treadL"), "skinning clone matches");
        Check(MatchesTreadMaterial("OpenShim/GpuSkin/12/w2b128/svtank_treadL", "svtank_treadL"),
              "wide-palette clone matches");
        Check(!MatchesTreadMaterial("OpenShim/GpuSkin/3/w4/caster/svtank_treadL", "svtank_treadL"),
              "caster clone does not");
        Check(!MatchesTreadMaterial("OpenShim/GpuSkin/3/w4/other/svtank_treadL", "svtank_treadL"),
              "a suffix after an extra path part does not");
        Check(!MatchesTreadMaterial("OpenShim/GpuSkin/x/w4/svtank_treadL", "svtank_treadL"),
              "generation must be digits");
        Check(!MatchesTreadMaterial("OpenShim/GpuSkin/3/svtank_treadL", "svtank_treadL"), "tag required");
        Check(!MatchesTreadMaterial("Other/3/w4/svtank_treadL", "svtank_treadL"), "other prefixes do not");
        Check(MatchesTreadMaterial("OpenShim/GpuSkin/3/w4/my/tread", "my/tread"), "names with '/' still match");
        Check(!MatchesTreadMaterial("svtank_treadL", ""), "empty key is off");
        Check(!MatchesTreadMaterial(nullptr, "a"), "null current");
        Check(!MatchesTreadMaterial("a", nullptr), "null key");

        Check(ClassifyTreadMaterial("tL", "tL", "tR") == TreadSide::Left, "left");
        Check(ClassifyTreadMaterial("OpenShim/GpuSkin/1/w4/tR", "tL", "tR") == TreadSide::Right, "right clone");
        Check(ClassifyTreadMaterial("hull", "tL", "tR") == TreadSide::None, "hull is neither");
        Check(ClassifyTreadMaterial("t", "t", "t") == TreadSide::Left, "same name for both: left wins");
        Check(ClassifyTreadMaterial("tR", "", "tR") == TreadSide::Right, "right alone works");
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
    TestScrollUIsSanitized();
    TestPhaseWrapsIntoUnitRange();
    TestScrollPhaseFollowsSignedSpeed();
    TestTreadMaterialMatching();
    TestTreadMaterialSet();
    if (OpenShimTest::ExitCode() == 0)
        std::printf("tracked_vehicle_treads_tests: all checks passed\n");
    return OpenShimTest::ExitCode();
}
