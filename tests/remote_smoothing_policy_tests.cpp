#include "remote_smoothing_policy.h"

#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <limits>

namespace
{
    using namespace BZROpenShim::RemoteSmoothing;

    int g_failures = 0;
    void check(bool ok, const char* text)
    {
        if (!ok)
        {
            std::fprintf(stderr, "FAIL: %s\n", text);
            ++g_failures;
        }
    }
    bool near(double a, double b, double tol = 1e-5) { return std::fabs(a - b) <= tol; }

    // Rotation about Y by `radians`, row-major.
    Transform Yaw(double radians, double x, double y, double z)
    {
        const float c = static_cast<float>(std::cos(radians));
        const float s = static_cast<float>(std::sin(radians));
        Transform t{};
        const float m[9] = {c, 0, -s, 0, 1, 0, s, 0, c};
        for (int i = 0; i < 9; ++i) t.m[i] = m[i];
        t.p[0] = x; t.p[1] = y; t.p[2] = z;
        return t;
    }

    double YawOf(const Transform& t) { return std::atan2(t.m[6], t.m[0]); }
}

int main()
{
    // Settings clamp.
    check(ClampTauMs(-5) == 0, "negative tau clamps to 0");
    check(ClampTauMs(100) == 100, "in-range tau kept");
    check(ClampTauMs(9999) == 300, "large tau clamps to 300");

    // Alpha.
    check(BlendAlpha(0.016, 0.0) == 1.0, "tau 0 means no smoothing");
    check(BlendAlpha(0.0, 0.1) == 0.0, "zero dt does not move");
    check(BlendAlpha(std::numeric_limits<double>::quiet_NaN(), 0.1) == 0.0, "NaN dt does not move");
    check(near(BlendAlpha(0.1, 0.1), 1.0 - std::exp(-1.0)), "dt == tau gives 1 - 1/e");
    check(BlendAlpha(5.0, 0.1) == BlendAlpha(kMaxStepSeconds, 0.1), "a hitch is clamped");

    // Frame-rate independence: 0.2 s at 200 fps and at 25 fps lands at the same spot.
    {
        const double tau = 0.1;
        double fast = 0.0, slow = 0.0;
        for (int i = 0; i < 40; ++i) fast += (1.0 - fast) * BlendAlpha(0.005, tau);
        for (int i = 0; i < 5; ++i) slow += (1.0 - slow) * BlendAlpha(0.04, tau);
        check(near(fast, slow, 1e-9), "same elapsed time, same progress at any frame rate");
        check(near(fast, 1.0 - std::exp(-2.0), 1e-9), "progress is 1 - exp(-t/tau)");
    }

    // Rotation validation.
    check(IsRotation(Yaw(0.7, 0, 0, 0).m), "a yaw is a rotation");
    {
        Transform t = Yaw(0.0, 0, 0, 0);
        t.m[0] = -1.0f;  // reflection
        check(!IsRotation(t.m), "a reflection is not a rotation");
        Transform z{};
        check(!IsRotation(z.m), "all zeros is not a rotation");
        Transform n = Yaw(0.0, 0, 0, 0);
        n.m[4] = std::numeric_limits<float>::infinity();
        check(!IsRotation(n.m), "non-finite is not a rotation");
    }

    // Quaternion round trip, including the non-trace branches (yaw near 180).
    for (double a : {0.0, 0.5, 1.5, 3.0, 3.14159, -2.5})
    {
        const Transform t = Yaw(a, 0, 0, 0);
        Transform r = t;
        QuatToMatrix(MatrixToQuat(t.m), r.m);
        bool same = true;
        for (int i = 0; i < 9; ++i) same = same && near(t.m[i], r.m[i], 1e-5);
        check(same, "matrix -> quat -> matrix round trip");
    }

    // Blend.
    {
        const Transform prev = Yaw(0.0, 0, 0, 0);
        Transform target = Yaw(1.0, 4, 0, 0);
        target.pad = 7.0f;
        Transform out{};
        const double dt = 0.02, tau = 0.1;
        check(Blend(prev, target, dt, tau, out) == Outcome::Blended, "small correction blends");
        const double a = BlendAlpha(dt, tau);
        check(near(out.p[0], 4.0 * a), "position moves by alpha");
        check(near(YawOf(out), 1.0 * BlendAlpha(dt, tau / kRotationTauDivisor), 1e-4),
              "rotation moves by the faster alpha");
        check(IsRotation(out.m), "blended matrix is a rotation");
        check(out.pad == target.pad, "pad copied from target");
    }
    {
        Transform out{};
        check(Blend(Yaw(0, 0, 0, 0), Yaw(0, 20, 0, 0), 0.02, 0.1, out) == Outcome::Snapped, "over 15 m snaps");
        check(out.p[0] == 20.0, "snap lands on the target");
    }
    {
        Transform out{};
        Transform bad = Yaw(0, 0, 0, 0);
        bad.p[1] = std::numeric_limits<double>::quiet_NaN();
        check(Blend(Yaw(0, 0, 0, 0), bad, 0.02, 0.1, out) == Outcome::Skipped, "NaN position skips");
        Transform z{};
        check(Blend(z, Yaw(0, 1, 0, 0), 0.02, 0.1, out) == Outcome::Skipped, "garbage matrix skips");
    }
    {
        // Shortest arc: +170 deg to -170 deg passes through 180, not 0.
        const double deg = 3.14159265358979 / 180.0;
        Transform out{};
        Blend(Yaw(170 * deg, 0, 0, 0), Yaw(-170 * deg, 0, 0, 0), 1.0, 0.0, out);
        check(near(std::fabs(YawOf(out)), 170 * deg, 1e-4), "alpha 1 reaches the target");
        Blend(Yaw(170 * deg, 0, 0, 0), Yaw(-170 * deg, 0, 0, 0), 0.0001, 1.0e9, out);
        check(std::fabs(YawOf(out)) > 169 * deg, "tiny step stays near 170, never sweeps through 0");
    }

    return g_failures ? 1 : 0;
}
