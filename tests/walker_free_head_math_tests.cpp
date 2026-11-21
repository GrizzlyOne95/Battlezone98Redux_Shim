// Tests for the walker free-turning head math (include/walker_free_head_math.h).

#include "walker_free_head_math.h"

#include <cmath>
#include <cstdio>
#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    using namespace BZROpenShim::WalkerFreeHead;
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

    void TestConfigDefaultsAndSanitize()
    {
        const TU::Config d = SanitizeConfig(DefaultConfig());
        CheckNear(d.yawRate, kDefaultYawRate, 1e-6, "default yawRate");
        CheckNear(d.yawAlpha, kDefaultYawAlpha, 1e-6, "default yawAlpha");
        Check(!d.limited, "unlimited unless yawMin/yawMax are set");

        TU::Config bad;
        bad.yawRate = -1.0f;
        bad.yawAlpha = NAN;
        const TU::Config b = SanitizeConfig(bad);
        CheckNear(b.yawRate, kDefaultYawRate, 1e-6, "bad yawRate falls back to the walker default");
        CheckNear(b.yawAlpha, kDefaultYawAlpha, 1e-6, "bad yawAlpha falls back to the walker default");

        TU::Config fast = DefaultConfig();
        fast.yawRate = 100.0f;
        CheckNear(SanitizeConfig(fast).yawRate, TU::kMaxYawRate, 1e-6, "yawRate clamped like the tank");

        TU::Config limits = DefaultConfig();
        limits.yawMin = -1.6f;
        limits.yawMax = 1.6f;
        const TU::Config l = SanitizeConfig(limits);
        Check(l.limited, "limits kept when they bracket 0");
        CheckNear(l.yawMin, -1.6, 1e-6, "yawMin kept");
        CheckNear(l.yawMax, 1.6, 1e-6, "yawMax kept");

        TU::Config excludesZero = DefaultConfig();
        excludesZero.yawMin = 0.2f;
        excludesZero.yawMax = 1.0f;
        Check(!SanitizeConfig(excludesZero).limited, "a limit that excludes 0 is dropped");
    }

    void TestMouseCommand()
    {
        CheckNear(MouseCommand(0), 0.0, 1e-9, "idle axis");
        CheckNear(MouseCommand(32768), 0.5, 1e-6, "16.16 scaling");
        CheckNear(MouseCommand(-65536), -1.0, 1e-6, "full left/right");
        CheckNear(MouseCommand(10 * 65536), 1.0, 1e-6, "clamped to +1");
        CheckNear(MouseCommand(-10 * 65536), -1.0, 1e-6, "clamped to -1");
    }

    void TestLegTurnCommand()
    {
        CheckNear(LegTurnCommand(0, 0, 0.0f), 0.0, 1e-9, "no keys");
        CheckNear(LegTurnCommand(1, 0, 0.0f), 1.0, 1e-9, "left arrow turns the legs left");
        CheckNear(LegTurnCommand(0, 1, 0.0f), -1.0, 1e-9, "right arrow turns the legs right");
        CheckNear(LegTurnCommand(1, 1, 0.0f), 0.0, 1e-9, "both arrows cancel");
        CheckNear(LegTurnCommand(0, 0, -1.0f), 1.0, 1e-9, "A (strafe -1) turns the legs left");
        CheckNear(LegTurnCommand(0, 0, 0.4f), -0.4, 1e-6, "D (strafe +, low-passed) turns right");
        CheckNear(LegTurnCommand(1, 0, -1.0f), 1.0, 1e-9, "arrow plus A clamps to 1");
        CheckNear(LegTurnCommand(0, 0, NAN), 0.0, 1e-9, "garbage strafe ignored");
    }

    void TestSwapRoundTrip()
    {
        const Vec3 up{ 0.0f, 1.0f, 0.0f };
        for (float head : { 0.0f, 0.7f, -2.5f })
        {
            const TU::Mat3 h = TU::Yaw(head);
            for (float delta : { 0.0f, 0.4f, -1.3f, 3.0f })
            {
                Vec3 lr, lf;
                LegsAxes(h.right, h.front, delta, lr, lf);
                // The legs are the head turned right by delta (head left of the legs).
                CheckVec(lf, TU::Yaw(head + delta).front, 1e-5, "legs front is the head yawed by -delta (left sense)");
                CheckNear(YawChangeLeft(h.front, lf, up), -delta, 1e-5, "legs sit delta to the right of the head");
                CheckNear(TP::Dot(lr, lf), 0.0, 1e-6, "legs axes stay orthogonal");
                Vec3 hr, hf;
                HeadAxes(lr, lf, delta, hr, hf);
                CheckVec(hr, h.right, 1e-5, "swap out restores the head right");
                CheckVec(hf, h.front, 1e-5, "swap out restores the head front");
            }
        }
    }

    void TestYawChangeLeft()
    {
        const Vec3 up{ 0.0f, 1.0f, 0.0f };
        CheckNear(YawChangeLeft(TU::Yaw(0.0f).front, TU::Yaw(0.3f).front, up), -0.3, 1e-5, "turn right is negative");
        CheckNear(YawChangeLeft(TU::Yaw(0.3f).front, TU::Yaw(0.0f).front, up), 0.3, 1e-5, "turn left is positive");
        CheckNear(YawChangeLeft(TU::Yaw(3.0f).front, TU::Yaw(-3.0f).front, up), -(2.0 * TU::kPi - 6.0), 1e-4,
                  "the short way across +-pi");
        // A tilted up: the change is measured about the given up axis.
        const Vec3 tiltedUp = TP::NormalizeOr(Vec3{ 0.0f, 1.0f, 0.2f }, up);
        CheckNear(YawChangeLeft(Vec3{ 0.0f, 0.0f, 1.0f }, Vec3{ 0.0f, 0.0f, 1.0f }, tiltedUp), 0.0, 1e-6,
                  "no turn about a tilted up");
        CheckNear(YawChangeLeft(Vec3{ 0.0f, 0.0f, 0.0f }, Vec3{ 0.0f, 0.0f, 1.0f }, up), 0.0, 1e-9,
                  "degenerate input is 0");
    }

    void TestNextDelta()
    {
        const TU::Config free = SanitizeConfig(DefaultConfig());
        CheckNear(NextDelta(free, 0.0f, 0.1f, 0.0f), 0.1, 1e-6, "head slew adds to delta");
        CheckNear(NextDelta(free, 0.0f, 0.0f, 0.2f), -0.2, 1e-6, "legs turning left leave the head to their right");
        CheckNear(NextDelta(free, 0.5f, 0.0f, 0.5f), 0.0, 1e-6, "legs catching up with the head close delta");
        CheckNear(NextDelta(free, 3.0f, 0.3f, 0.0f), 3.3 - 2.0 * TU::kPi, 1e-5, "unlimited delta wraps");
        CheckNear(NextDelta(free, NAN, NAN, NAN), 0.0, 1e-9, "garbage resets to 0");

        TU::Config limitsIn = DefaultConfig();
        limitsIn.yawMin = -1.0f;
        limitsIn.yawMax = 1.0f;
        const TU::Config limited = SanitizeConfig(limitsIn);
        CheckNear(NextDelta(limited, 0.9f, 0.3f, 0.0f), 1.0, 1e-6, "clamped at yawMax");
        CheckNear(NextDelta(limited, -0.9f, 0.0f, 0.5f), -1.0, 1e-6, "legs turning drag the head at yawMin");
    }

    void TestSteerTracksMouse()
    {
        Check(SteerTracksMouse(0.0f, 0.0f), "both idle");
        Check(SteerTracksMouse(0.6f, 0.3f), "same sign while the low-pass catches up");
        Check(!SteerTracksMouse(0.6f, -0.3f), "opposite sign");
        Check(!SteerTracksMouse(0.6f, 0.0f), "steer idle while the mouse moves");
        Check(SteerTracksMouse(0.0f, 0.06f), "steer decaying after the mouse stopped");
        Check(!SteerTracksMouse(NAN, 0.0f), "garbage never tracks");
    }
}

int main()
{
    TestConfigDefaultsAndSanitize();
    TestMouseCommand();
    TestLegTurnCommand();
    TestSwapRoundTrip();
    TestYawChangeLeft();
    TestNextDelta();
    TestSteerTracksMouse();
    if (OpenShimTest::ExitCode() == 0)
        std::printf("walker_free_head_math_tests: all checks passed\n");
    return OpenShimTest::ExitCode();
}
