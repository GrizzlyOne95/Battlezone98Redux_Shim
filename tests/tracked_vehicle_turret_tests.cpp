// Tests for the classLabel=tracked turret math (include/tracked_vehicle_turret.h).

#include "tracked_vehicle_turret.h"

#include <cmath>
#include <cstdio>
#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    using namespace BZROpenShim::TrackedTurret;
    namespace TP = BZROpenShim::TrackedPhysics;

    void CheckNear(double actual, double expected, double tolerance, const char* message)
    {
        if (!(std::fabs(actual - expected) <= tolerance))
        {
            OpenShimTest::Fail("%s (actual=%.6f expected=%.6f)", message, actual, expected);
        }
    }

    void CheckVec(Vec3 actual, Vec3 expected, double tolerance, const char* message)
    {
        CheckNear(actual.x, expected.x, tolerance, message);
        CheckNear(actual.y, expected.y, tolerance, message);
        CheckNear(actual.z, expected.z, tolerance, message);
    }

    void CheckMat(const Mat3& a, const Mat3& b, double tolerance, const char* message)
    {
        CheckVec(a.right, b.right, tolerance, message);
        CheckVec(a.up, b.up, tolerance, message);
        CheckVec(a.front, b.front, tolerance, message);
    }

    void TestConfigIsSanitized()
    {
        const Config d = Sanitize(Config{});
        CheckNear(d.yawRate, kDefaultYawRate, 1e-6, "default rate");
        CheckNear(d.yawAlpha, kDefaultYawAlpha, 1e-6, "default alpha");
        Check(!d.limited, "no limits by default");

        Config raw;
        raw.yawRate = NAN;
        raw.yawAlpha = -1.0f;
        const Config bad = Sanitize(raw);
        CheckNear(bad.yawRate, kDefaultYawRate, 1e-6, "NaN rate is the default");
        CheckNear(bad.yawAlpha, kDefaultYawAlpha, 1e-6, "negative alpha is the default");

        raw = Config{};
        raw.yawRate = 1000.0f;
        raw.yawAlpha = 0.0001f;
        const Config clamped = Sanitize(raw);
        CheckNear(clamped.yawRate, kMaxYawRate, 1e-6, "huge rate clamps");
        CheckNear(clamped.yawAlpha, kMinYawAlpha, 1e-6, "tiny alpha clamps");

        raw = Config{};
        raw.yawMax = 1.6f;
        const Config half = Sanitize(raw);
        Check(half.limited, "one limit limits");
        CheckNear(half.yawMax, 1.6, 1e-6, "max kept");
        CheckNear(half.yawMin, -kPi, 1e-6, "unset min is -pi");

        raw = Config{};
        raw.yawMin = 0.5f;
        raw.yawMax = 1.0f;
        Check(!Sanitize(raw).limited, "limits that exclude straight ahead are dropped");
    }

    void TestSlewIsRateAndAlphaLimited()
    {
        Config c = Sanitize(Config{});  // 2 rad/s, 5 rad/s^2
        CheckNear(SlewRate(c, 0.0f, 1.0f, 0.0f, 0.1f), 0.5, 1e-6, "accelerates at yawAlpha");
        CheckNear(SlewRate(c, 1.9f, 1.0f, 0.0f, 0.1f), 2.0, 1e-6, "lands on yawRate");
        CheckNear(SlewRate(c, 2.0f, 5.0f, 0.0f, 0.1f), 2.0, 1e-6, "command clamps to 1");
        CheckNear(SlewRate(c, 2.0f, 0.0f, 0.0f, 0.1f), 1.5, 1e-6, "decelerates at yawAlpha");
        CheckNear(SlewRate(c, -2.0f, 1.0f, 0.0f, 0.1f), -1.5, 1e-6, "reversal is alpha limited");
        CheckNear(SlewRate(c, 0.3f, NAN, 0.0f, 0.1f), 0.0, 1e-6, "NaN command eases toward hold");
        CheckNear(SlewRate(c, 0.3f, 1.0f, 0.0f, 0.0f), 0.3, 1e-6, "zero dt holds");

        // Turning at yawRate for a second covers yawRate radians.
        float delta = 0.0f;
        float rate = 2.0f;
        for (int i = 0; i < 100; ++i)
        {
            rate = SlewRate(c, rate, 1.0f, delta, 0.01f);
            delta = AdvanceDelta(c, delta, rate, 0.01f);
        }
        CheckNear(delta, 2.0, 1e-4, "one second at full rate");

        // Unlimited delta wraps to (-pi, pi].
        CheckNear(AdvanceDelta(c, 3.0f, 2.0f, 0.1f), 3.2 - 2.0 * kPi, 1e-5, "wraps past pi");
    }

    void TestLimitsStopTheTurret()
    {
        Config raw;
        raw.yawMin = -0.5f;
        raw.yawMax = 0.5f;
        const Config c = Sanitize(raw);
        float delta = 0.45f;
        const float rate = SlewRate(c, 2.0f, 1.0f, delta, 0.1f);
        CheckNear(rate, 0.5, 1e-5, "rate stops at the limit within the step");
        delta = AdvanceDelta(c, delta, rate, 0.1f);
        CheckNear(delta, 0.5, 1e-5, "delta reaches the limit");
        CheckNear(SlewRate(c, 0.0f, 1.0f, delta, 0.1f), 0.0, 1e-5, "no further at the limit");
        CheckNear(SlewRate(c, 0.0f, -1.0f, delta, 0.1f), -0.5, 1e-5, "leaves the limit");
        CheckNear(AdvanceDelta(c, 0.5f, 10.0f, 0.1f), 0.5, 1e-6, "delta clamps");
    }

    void TestHullAxesAndOmegaRoundTrip()
    {
        const Vec3 r{ 1.0f, 0.0f, 0.0f };
        const Vec3 f{ 0.0f, 0.0f, 1.0f };
        Vec3 hr, hf;
        HullAxes(r, f, 0.0f, hr, hf);
        CheckVec(hf, f, 1e-6, "zero delta: hull is the root");
        // Turret 90 degrees left of the hull: the hull faces the root's right.
        HullAxes(r, f, kPi * 0.5f, hr, hf);
        CheckVec(hf, r, 1e-6, "hull front is root right");
        CheckVec(hr, { 0.0f, 0.0f, -1.0f }, 1e-6, "hull right is root back");
        // The hull axes match Yaw(delta) rows in root-local terms.
        const Mat3 y = Yaw(0.7f);
        HullAxes(r, f, 0.7f, hr, hf);
        CheckVec(hf, y.front, 1e-6, "hull front is Yaw(delta).front");
        CheckVec(hr, y.right, 1e-6, "hull right is Yaw(delta).right");

        // Pitch about the root right is pitch about the hull right only at
        // zero delta; at 90 degrees it is roll for the hull.
        const Vec3 pitch{ 1.0f, 0.0f, 0.0f };
        const Vec3 hull = RootToHullOmega(pitch, kPi * 0.5f, 0.0f);
        CheckNear(hull.x, 0.0, 1e-6, "no hull pitch");
        CheckNear(std::fabs(hull.z), 1.0, 1e-6, "all hull roll");

        // The world angular velocity is preserved: root omega expressed on
        // the hull axes and back.
        const Vec3 omega{ 0.3f, 0.8f, -0.2f };
        const float delta = 0.9f;
        const Vec3 h = RootToHullOmega(omega, delta, 0.5f);
        CheckNear(h.y, 0.3, 1e-6, "hull yaw rate is root less slew");
        const Vec3 back = HullToRootAlpha(h, delta, 0.0f, 0.1f);
        CheckNear(back.x, omega.x, 1e-6, "pitch round trip");
        CheckNear(back.z, omega.z, 1e-6, "roll round trip");
        // The world vector of the pitch/roll part matches.
        HullAxes(r, f, delta, hr, hf);
        const Vec3 worldRoot = TP::Add(TP::Scale(r, omega.x), TP::Scale(f, omega.z));
        const Vec3 worldHull = TP::Add(TP::Scale(hr, h.x), TP::Scale(hf, h.z));
        CheckVec(worldHull, worldRoot, 1e-6, "same world pitch/roll vector");
        CheckNear(HullToRootAlpha({ 0.0f, 1.0f, 0.0f }, 0.0f, 0.5f, 0.1f).y, 6.0, 1e-5, "slew change adds to yaw alpha");
    }

    void TestPlayerHull()
    {
        const HullCommand right = PlayerHull(1.0f, 1.0f);
        CheckNear(right.throttle, 1.0, 1e-6, "throttle drives the hull");
        CheckNear(right.steer, -1.0, 1e-6, "strafe right turns the hull right");
        const HullCommand bad = PlayerHull(NAN, 5.0f);
        CheckNear(bad.throttle, 0.0, 1e-6, "NaN throttle is 0");
        CheckNear(bad.steer, -1.0, 1e-6, "strafe clamps");
    }

    void TestAiHull()
    {
        // Aligned: straight through.
        HullCommand c = AiHull(1.0f, 0.0f, 0.0f);
        CheckNear(c.throttle, 1.0, 1e-6, "aligned drives");
        CheckNear(c.steer, 0.0, 1e-6, "aligned holds course");
        // Idle: hold.
        c = AiHull(0.01f, 0.0f, 1.0f);
        CheckNear(c.throttle, 0.0, 1e-6, "dead zone holds");
        CheckNear(c.steer, 0.0, 1e-6, "dead zone no turn");
        // Turret 90 degrees left, AI wants to go along the turret: pivot left.
        c = AiHull(1.0f, 0.0f, kPi * 0.5f);
        CheckNear(c.steer, 1.0, 1e-6, "pivot left toward the turret heading");
        CheckNear(c.throttle, 0.0, 1e-5, "no drive at 90 degrees");
        // Small error: drives and turns gently left.
        c = AiHull(1.0f, 0.0f, 0.2f);
        CheckNear(c.steer, 0.4, 1e-5, "steer is gain * error");
        CheckNear(c.throttle, std::cos(0.2), 1e-5, "throttle eases with the error");
        // Turret 90 left, AI strafes right: that is straight ahead for the hull.
        c = AiHull(0.0f, 1.0f, kPi * 0.5f);
        CheckNear(c.steer, 0.0, 1e-5, "root right is hull front");
        CheckNear(c.throttle, 1.0, 1e-5, "drives along it");
        // Reversing straight back.
        c = AiHull(-1.0f, 0.0f, 0.0f);
        CheckNear(c.throttle, -1.0, 1e-6, "reverse backs up");
        CheckNear(c.steer, 0.0, 1e-6, "reverse holds course");
        Check(std::isfinite(AiHull(NAN, NAN, NAN).steer), "garbage stays finite");
    }

    void TestTurretPoseKeepsRestRelativeToRoot()
    {
        // Parent chain at rest: a tilted parent (pitch then yaw), turret
        // rest local a small yaw. With the root child yawed by delta, the
        // turret's world (root-relative) rotation must stay at rest.
        Mat3 pitch;
        pitch.up = { 0.0f, std::cos(0.1f), std::sin(0.1f) };
        pitch.front = { 0.0f, -std::sin(0.1f), std::cos(0.1f) };
        const Mat3 parent = Mul(Mul(Yaw(0.3f), pitch), Yaw(0.4f));
        const Mat3 rest = Yaw(-0.2f);
        const Mat3 restRelRoot = Mul(rest, parent);
        for (float delta : { 0.0f, 0.5f, -1.2f, 2.9f })
        {
            const Mat3 parentNow = Mul(parent, Yaw(delta));  // root child * Yaw(delta) at the top
            const Mat3 local = TurretRotation(rest, parent, delta);
            CheckMat(Mul(local, parentNow), restRelRoot, 1e-5, "turret stays at its rest heading");
        }
        // A root child yawed by delta: its front is rest front turned by delta.
        const Mat3 child = HullChildRotation(Mat3{}, 0.6f);
        CheckVec(child.front, Yaw(0.6f).front, 1e-6, "root child yaws with the hull");
    }
}

int main()
{
    TestConfigIsSanitized();
    TestSlewIsRateAndAlphaLimited();
    TestLimitsStopTheTurret();
    TestHullAxesAndOmegaRoundTrip();
    TestPlayerHull();
    TestAiHull();
    TestTurretPoseKeepsRestRelativeToRoot();
    if (OpenShimTest::ExitCode() == 0)
        std::printf("tracked_vehicle_turret_tests: all checks passed\n");
    return OpenShimTest::ExitCode();
}
