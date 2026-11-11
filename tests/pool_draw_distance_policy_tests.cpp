#include "pool_draw_distance_policy.h"

#include <cmath>
#include <cstdio>
#include <limits>

namespace
{
    using namespace BZROpenShim::PoolDrawDistance;

    int g_failures = 0;
    void check(bool ok, const char* text)
    {
        if (!ok)
        {
            std::fprintf(stderr, "FAIL: %s\n", text);
            ++g_failures;
        }
    }
}

int main()
{
    const float nan = std::numeric_limits<float>::quiet_NaN();
    const float inf = std::numeric_limits<float>::infinity();

    // Setting clamp.
    check(ClampDrawDistanceMetres(-5.0) == 0, "negative clamps to off");
    check(ClampDrawDistanceMetres(0.0) == 0, "zero is off");
    check(ClampDrawDistanceMetres(0.5) == 0, "below one metre truncates to off");
    check(ClampDrawDistanceMetres(70.0) == 70, "in range kept");
    check(ClampDrawDistanceMetres(150.9) == 150, "fraction truncates");
    check(ClampDrawDistanceMetres(1.0e9) == kMaxDrawDistanceMetres, "too large clamps");
    check(ClampDrawDistanceMetres(std::numeric_limits<double>::quiet_NaN()) == 0, "NaN is off");
    check(kDefaultGibDrawDistanceMetres == ClampDrawDistanceMetres(kDefaultGibDrawDistanceMetres),
          "gib default is in range");
    check(kDefaultCasingDrawDistanceMetres == ClampDrawDistanceMetres(kDefaultCasingDrawDistanceMetres),
          "casing default is in range");
    check(kDefaultCasingDrawDistanceMetres < kDefaultGibDrawDistanceMetres, "casings cull nearer than gibs");

    // Distance test.
    check(!IsBeyondDrawDistance(1.0e6f, 0), "off never culls");
    check(!IsBeyondDrawDistance(1.0e6f, -1), "negative never culls");
    check(!IsBeyondDrawDistance(100.0f * 100.0f, 100), "exactly at threshold keeps");
    check(IsBeyondDrawDistance(100.1f * 100.1f, 100), "just past threshold culls");
    check(!IsBeyondDrawDistance(50.0f * 50.0f, 100), "inside keeps");
    check(!IsBeyondDrawDistance(nan, 100), "NaN keeps");
    check(IsBeyondDrawDistance(inf, 100), "infinite distance culls");

    const float origin[3] = {0.0f, 0.0f, 0.0f};
    const float p[3] = {3.0f, 4.0f, 12.0f};
    check(DistanceSquared(origin, p) == 169.0f, "distance squared");
    check(DistanceSquared(p, origin) == 169.0f, "distance squared is symmetric");

    // Transitions. Far = past 100 m, near = inside.
    const float far = 200.0f * 200.0f;
    const float near = 10.0f * 10.0f;
    check(Decide(false, true, far, 100) == Transition::Hide, "visible piece going far hides");
    check(Decide(true, true, far, 100) == Transition::Keep, "culled piece still far stays hidden, no call");
    check(Decide(true, true, near, 100) == Transition::Show, "culled piece coming back shows");
    check(Decide(false, true, near, 100) == Transition::Keep, "visible piece inside: no call");
    check(Decide(false, false, far, 100) == Transition::Keep, "unknown camera never hides");
    check(Decide(true, false, near, 100) == Transition::Keep, "unknown camera never shows (no flicker)");
    check(Decide(false, true, far, 0) == Transition::Keep, "off never hides");
    check(Decide(true, true, far, 0) == Transition::Show, "off shows a piece left culled");
    check(Decide(false, true, nan, 100) == Transition::Keep, "NaN distance never hides");
    check(Decide(true, true, nan, 100) == Transition::Show, "NaN distance shows a culled piece");

    const float pi = 3.14159265f;
    check(std::fabs(ZoomDistanceScale(pi / 3.0f) - 1.0f) < 1e-4f, "reference 60 degree FOV: plain distance");
    check(ZoomDistanceScale(pi / 2.0f) == 1.0f, "wider FOV never culls closer");
    check(std::fabs(ZoomDistanceScale(2.0f * std::atan(0.57735027f / 4.0f)) - 0.25f) < 1e-4f, "4x zoom quarters the distance");
    check(ZoomDistanceScale(0.0f) == 1.0f && ZoomDistanceScale(-1.0f) == 1.0f, "bad FOV: plain distance");
    check(ZoomDistanceScale(nan) == 1.0f && ZoomDistanceScale(3.2f) == 1.0f, "NaN or degenerate FOV: plain distance");
    {
        const float d = 400.0f; // 400 m through a 4x scope looks like 100 m
        const float z = ZoomDistanceScale(2.0f * std::atan(0.57735027f / 4.0f));
        check(Decide(false, true, d * d * z * z, 150) == Transition::Keep, "zoomed: far piece stays drawn");
        check(Decide(false, true, d * d, 150) == Transition::Hide, "same piece unzoomed hides");
    }

    if (g_failures)
    {
        std::fprintf(stderr, "%d failure(s)\n", g_failures);
        return 1;
    }
    std::puts("pool_draw_distance_policy_tests: all passed");
    return 0;
}
