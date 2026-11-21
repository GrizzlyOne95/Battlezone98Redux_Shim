#include "anchor_drag_guard.h"

#include <cmath>
#include <cstring>
#include <limits>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::AnchorDrag;

    // What the stock scale branch does with the drag it is handed.
    float StockFactor(float speed, float drag) { return 1.0f - drag / speed; }

    float Denormal()
    {
        const unsigned bits = 0x00000100u;  // a positive denormal
        float f = 0.0f;
        std::memcpy(&f, &bits, sizeof(f));
        return f;
    }

    void TestPositiveDragUnchanged()
    {
        // Brake below the speed: stock scale branch with stock drag.
        Decision d = Decide(10.0f, 0.5f, kLinearBoostCap);
        CHECK(!d.zero);
        CHECK(d.drag == 0.5f);
        // Brake at or above the speed: stock zero branch.
        d = Decide(0.5f, 0.5f, kLinearBoostCap);
        CHECK(d.zero);
        d = Decide(0.2f, 0.5f, kLinearBoostCap);
        CHECK(d.zero);
        // Stationary target with stock drag: zero branch, as stock.
        d = Decide(0.0f, 0.5f, kLinearBoostCap);
        CHECK(d.zero);
        // A real speed far above the cap with positive drag is untouched.
        d = Decide(500.0f, 2.0f, kLinearBoostCap);
        CHECK(!d.zero);
        CHECK(d.drag == 2.0f);
        // Tiny positive drag on a tiny speed above it: stock scales.
        d = Decide(5e-5f, 1e-6f, kLinearBoostCap);
        CHECK(!d.zero);
        CHECK(d.drag == 1e-6f);
        // Zero drag on a small normal speed: stock factor 1, unchanged.
        d = Decide(1e-5f, 0.0f, kLinearBoostCap);
        CHECK(!d.zero);
        // Zero drag on a denormal speed: flushed divide is 0/0, zero branch.
        CHECK(Decide(Denormal(), 0.0f, kLinearBoostCap).zero);
    }

    void TestNonRealSpeedTakesZeroBranch()
    {
        const float nan = std::numeric_limits<float>::quiet_NaN();
        // Negative drag: stock falls through and divides by these.
        CHECK(Decide(0.0f, -0.5f, kLinearBoostCap).zero);
        CHECK(Decide(Denormal(), -0.5f, kLinearBoostCap).zero);
        CHECK(Decide(1e-20f, -0.5f, kLinearBoostCap).zero);
        CHECK(Decide(nan, -0.5f, kLinearBoostCap).zero);
        CHECK(Decide(kMinSpeed, -0.5f, kAngularBoostCap).zero);
        // NaN drag: stock already jumps (unordered compare).
        CHECK(Decide(5.0f, nan, kLinearBoostCap).zero);
    }

    void TestBoostBelowCapIsStock()
    {
        // 10 m/s, drag -2: stock result 12 m/s, under the 100 m/s cap.
        const Decision d = Decide(10.0f, -2.0f, kLinearBoostCap);
        CHECK(!d.zero);
        CHECK(d.drag == -2.0f);
        // Spin 1 rad/s, drag -0.5: 1.5 rad/s, under 10 rad/s.
        const Decision s = Decide(1.0f, -0.5f, kAngularBoostCap);
        CHECK(!s.zero);
        CHECK(s.drag == -0.5f);
    }

    void TestBoostClampedAtCap()
    {
        // 90 m/s, drag -50: stock 140 m/s, capped to 100 m/s.
        const Decision d = Decide(90.0f, -50.0f, kLinearBoostCap);
        CHECK(!d.zero);
        const float result = 90.0f * StockFactor(90.0f, d.drag);
        CHECK(std::fabs(result - kLinearBoostCap) < 1e-3f);

        // Spin 8 rad/s, drag -5: 13 rad/s, capped to 10 rad/s.
        const Decision s = Decide(8.0f, -5.0f, kAngularBoostCap);
        CHECK(!s.zero);
        const float spin = 8.0f * StockFactor(8.0f, s.drag);
        CHECK(std::fabs(spin - kAngularBoostCap) < 1e-4f);

        // Infinite negative drag is capped too.
        const Decision inf = Decide(5.0f, -std::numeric_limits<float>::infinity(), kLinearBoostCap);
        CHECK(!inf.zero);
        CHECK(std::fabs(5.0f * StockFactor(5.0f, inf.drag) - kLinearBoostCap) < 1e-3f);
    }

    void TestAlreadyAboveCapHolds()
    {
        // 150 m/s with a boost: factor exactly 1 (no boost, no brake).
        const Decision d = Decide(150.0f, -10.0f, kLinearBoostCap);
        CHECK(!d.zero);
        CHECK(d.drag == 0.0f);
        CHECK(StockFactor(150.0f, d.drag) == 1.0f);

        const Decision s = Decide(12.0f, -1.0f, kAngularBoostCap);
        CHECK(!s.zero);
        CHECK(StockFactor(12.0f, s.drag) == 1.0f);
    }
}

int main()
{
    TestPositiveDragUnchanged();
    TestNonRealSpeedTakesZeroBranch();
    TestBoostBelowCapIsStock();
    TestBoostClampedAtCap();
    TestAlreadyAboveCapHolds();
    return OpenShimTest::ExitCode();
}
