// Unit tests for include/nearest_vehicle_scan.h, the body of the shim's
// UnitTask::NearestVehicle replacement. A fake engine records every accessor
// call so the tests can pin the stock call order as well as the result.
#include "nearest_vehicle_scan.h"
#include "test_check.h"

#include <cmath>
#include <cstdio>
#include <limits>
#include <string>
#include <vector>

using namespace BZROpenShim::NearestVehicleScan;
using OpenShimTest::Check;

namespace
{
    struct Obj
    {
        int id;
        uint32_t sig;
        uint32_t label;
        bool cargo;
        Vec3 pos;
    };

    struct FakeEngine
    {
        std::vector<Obj*> list;
        std::string log;
        int endCalls = 0;

        Obj* const* Begin() { return list.data(); }
        Obj* const* End()
        {
            ++endCalls;
            return list.data() + list.size();
        }
        bool IsCargo(Obj* o) { return o->cargo; }
        uint32_t ClassSig(Obj* o)
        {
            log += "S" + std::to_string(o->id) + " ";
            return o->sig;
        }
        uint32_t ClassLabel(Obj* o)
        {
            log += "L" + std::to_string(o->id) + " ";
            return o->label;
        }
        const Vec3* Position(Obj* o)
        {
            log += "P" + std::to_string(o->id) + " ";
            return &o->pos;
        }
    };

    constexpr uint32_t kSigTank = 0x4B4E4154u;
    constexpr uint32_t kLabelVehicle = 1u;

    Obj Make(int id, float x, uint32_t sig = kSigTank, uint32_t label = kLabelVehicle)
    {
        Obj o = { id, sig, label, false, { x, 0.0f, 0.0f } };
        return o;
    }

    void TestCallOrderAndFilters()
    {
        Obj craft = Make(0, 0.0f);
        Obj cargo = Make(1, 1.0f);
        cargo.cargo = true;
        Obj label5 = Make(2, 1.0f, kSigTank, 5);
        Obj label3 = Make(3, 1.0f, kSigTank, 3);
        Obj torp = Make(4, 9.0f, kSigTorpedo, 3);
        Obj far = Make(5, 5.0f);
        FakeEngine e;
        e.list = { &craft, &cargo, &label5, &label3, &torp, &far };
        const Vec3 at = { 0.0f, 0.0f, 0.0f };
        Obj* got = Scan(e, &craft, &at);
        Check(got == &far, "labels 5 and 3 (non-torpedo) are skipped; the nearer survivor wins");
        // Self and cargo make no virtual calls; label is read with a second
        // class call; position only for objects that pass every filter.
        Check(e.log == "S2 L2 S3 L3 S4 L4 P4 S5 L5 P5 ", "accessor calls follow stock order: " + e.log);
        Check(e.endCalls == 7, "End() is re-read on every loop test");
    }

    void TestOtherSkippedLabels()
    {
        Obj craft = Make(0, 0.0f);
        Obj l7 = Make(1, 1.0f, kSigTank, 7);
        Obj l2 = Make(2, 1.0f, kSigTank, 2);
        Obj l10 = Make(3, 1.0f, kSigTank, 10);
        FakeEngine e;
        e.list = { &l7, &craft, &l2, &l10 };
        const Vec3 at = { 0.0f, 0.0f, 0.0f };
        Check(Scan(e, &craft, &at) == nullptr, "labels 7, 2 and 10 are skipped; nothing found returns null");
    }

    void TestTugRecyclerRule()
    {
        Obj recycler = Make(0, 0.0f, kSigRecycler);
        Obj tug = Make(1, 1.0f, kSigTug);
        Obj tank = Make(2, 3.0f);
        FakeEngine e;
        e.list = { &recycler, &tug, &tank };
        const Vec3 at = { 0.0f, 0.0f, 0.0f };
        Check(Scan(e, &recycler, &at) == &tank, "a recycler never picks a tug");
        Check(e.log == "S1 S0 S2 L2 P2 ", "the craft class is read only for a tug: " + e.log);

        Obj tankCraft = Make(3, 0.0f);
        FakeEngine e2;
        e2.list = { &tankCraft, &tug, &tank };
        Check(Scan(e2, &tankCraft, &at) == &tug, "any other craft can pick a tug");
    }

    void TestFirstMinimumWins()
    {
        Obj craft = Make(0, 0.0f);
        Obj a = Make(1, 2.0f);
        Obj b = Make(2, -2.0f);
        FakeEngine e;
        e.list = { &craft, &a, &b };
        const Vec3 at = { 0.0f, 0.0f, 0.0f };
        Check(Scan(e, &craft, &at) == &a, "equal distances keep the first in list order");
    }

    void TestNaNAndFarNeverWin()
    {
        const float nan = std::numeric_limits<float>::quiet_NaN();
        Obj craft = Make(0, 0.0f);
        Obj bad = Make(1, nan);
        Obj huge = Make(2, 2e15f); // squared 4e30 > 1e30, never taken
        Obj ok = Make(3, 4.0f);
        FakeEngine e;
        e.list = { &craft, &bad, &huge };
        const Vec3 at = { 0.0f, 0.0f, 0.0f };
        Check(Scan(e, &craft, &at) == nullptr, "a NaN or beyond-1e30 distance is never taken");
        e.list.push_back(&ok);
        Check(Scan(e, &craft, &at) == &ok, "a NaN does not poison later objects");
        Check(!Closer(1.0f, nan) && !Closer(nan, 1.0f), "comparisons with NaN are false (ordered comiss)");
    }

    void TestDistSquaredOrder()
    {
        // (dx*dx + dy*dy) + dz*dz in single precision. With these values the
        // other grouping, dx*dx + (dy*dy + dz*dz), rounds differently.
        const Vec3 a = { 1.0f, 2e-4f, 2e-4f };
        const Vec3 b = { 0.0f, 0.0f, 0.0f };
        volatile float dx = 1.0f, dy = 2e-4f, dz = 2e-4f;
        volatile float xx = dx * dx, yy = dy * dy, zz = dz * dz;
        volatile float xy = xx + yy;
        volatile float expected = xy + zz;
        volatile float yz = yy + zz;
        volatile float other = xx + yz;
        Check(expected != other, "the test values tell the two groupings apart");
        const float got = DistSquared(a, b);
        Check(got == expected, "DistSquared adds x and y first, then z");

        const Vec3 p = { 3.0f, -4.0f, 12.0f };
        const Vec3 q = { 0.0f, 0.0f, 0.0f };
        Check(DistSquared(p, q) == 169.0f, "DistSquared of (3,-4,12) is 169");
        Check(DistSquared(q, p) == 169.0f, "DistSquared subtracts a - b per axis");
    }

    void TestEmptyAndOnlySelf()
    {
        Obj craft = Make(0, 0.0f);
        FakeEngine e;
        const Vec3 at = { 0.0f, 0.0f, 0.0f };
        Check(Scan(e, &craft, &at) == nullptr, "an empty list returns null");
        e.list = { &craft };
        Check(Scan(e, &craft, &at) == nullptr, "a list of only the craft returns null");
        Check(e.log.empty(), "the craft itself makes no class or position calls");
    }

    void TestPositionArgumentUsed()
    {
        Obj craft = Make(0, 0.0f);
        Obj a = Make(1, 10.0f);
        Obj b = Make(2, -1.0f);
        FakeEngine e;
        e.list = { &a, &craft, &b };
        const Vec3 at = { 9.0f, 0.0f, 0.0f };
        Check(Scan(e, &craft, &at) == &a, "distance is measured from the position argument, not the craft");
    }
}

int main()
{
    TestCallOrderAndFilters();
    TestOtherSkippedLabels();
    TestTugRecyclerRule();
    TestFirstMinimumWins();
    TestNaNAndFarNeverWin();
    TestDistSquaredOrder();
    TestEmptyAndOnlySelf();
    TestPositionArgumentUsed();
    std::printf("nearest_vehicle_scan_tests: %d checks\n", OpenShimTest::CheckCount());
    return OpenShimTest::ExitCode();
}
