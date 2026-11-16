// local_damage_policy_tests.cpp
//
// Pins the pure math of the localized damage scorch
// (include/local_damage_policy.h, Docs/LOCAL_DAMAGE.md): mark size, the
// per-unit ring with merge, ember decay, the repair reset, the shader
// parameter layout and the sim-world -> entity-local conversion.

#include "local_damage_policy.h"

#include <cmath>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::LocalDamage;

namespace
{
    bool Near(float a, float b, float epsilon = 1e-4f)
    {
        return std::fabs(a - b) <= epsilon;
    }

    void Radius()
    {
        Check(Near(RadiusFromHealthLost(0.0f), kMinRadius), "no loss: minimum radius");
        Check(Near(RadiusFromHealthLost(0.1f), 1.65f), "10% lost: halfway (lerp 0.9..2.4 by lost*5)");
        Check(Near(RadiusFromHealthLost(0.2f), kMaxRadius), "20% lost: maximum radius");
        Check(Near(RadiusFromHealthLost(0.9f), kMaxRadius), "large loss: clamped");
        Check(Near(RadiusFromHealthLost(-1.0f), kMinRadius), "negative loss: minimum");
        Check(Near(RadiusFromHealthLost(NAN), kMinRadius), "NaN loss: minimum");
    }

    void Settings()
    {
        Check(ClampMaxMarks(0) == 1 && ClampMaxMarks(9) == 8 && ClampMaxMarks(5) == 5, "MaxMarksPerUnit clamps 1..8");
        Check(Near(ClampEmberSeconds(0.0f), 0.5f) && Near(ClampEmberSeconds(100.0f), 60.0f) &&
              Near(ClampEmberSeconds(NAN), kDefaultEmberSeconds), "EmberSeconds clamps 0.5..60, NaN -> default");
    }

    void RingAndMerge()
    {
        UnitMarks unit;
        const float a[3] = {0.0f, 0.0f, 0.0f};
        Check(!AddMark(unit, a, 2.0f, 8), "first hit adds a mark");
        Check(unit.Any() && unit.next == 1 && Near(unit.marks[0].heat, 1.0f), "fresh mark is hot in slot 0");

        unit.marks[0].heat = 0.2f;
        const float close[3] = {0.5f, 0.0f, 0.0f};  // 0.5 < 0.5 * 2.0
        Check(AddMark(unit, close, 1.0f, 8), "hit within half the radius merges");
        Check(Near(unit.marks[0].radius, 2.2f) && Near(unit.marks[0].heat, 1.0f) && unit.next == 1,
              "merge grows by 1.1 and reheats without using a slot");
        for (int i = 0; i < 4; ++i)
            AddMark(unit, close, 1.0f, 8);
        Check(Near(unit.marks[0].radius, kMaxRadius), "growth caps at the maximum radius");

        const float far[3] = {1.3f, 0.0f, 0.0f};  // 1.3 >= 0.5 * 2.4
        Check(!AddMark(unit, far, 1.0f, 8), "hit outside half the radius is a new mark");
        Check(unit.next == 2 && Near(unit.marks[1].x, 1.3f), "new mark takes the next slot");

        UnitMarks ring;
        for (int i = 0; i < 5; ++i)
        {
            const float p[3] = {static_cast<float>(i) * 10.0f, 0.0f, 0.0f};
            AddMark(ring, p, 1.0f, 3);
        }
        Check(Near(ring.marks[0].x, 30.0f) && Near(ring.marks[1].x, 40.0f) && Near(ring.marks[2].x, 20.0f) &&
              ring.marks[3].radius == 0.0f, "MaxMarksPerUnit 3: the oldest of three is replaced");
    }

    void Heat()
    {
        UnitMarks unit;
        const float p[3] = {0.0f, 0.0f, 0.0f};
        AddMark(unit, p, 1.0f, 8);
        Check(DecayHeat(unit, 3.0f, 6.0f) && Near(unit.marks[0].heat, 0.5f), "half the ember time: half heat");
        Check(DecayHeat(unit, 10.0f, 6.0f) && unit.marks[0].heat == 0.0f, "cools to zero, never below");
        Check(!DecayHeat(unit, 1.0f, 6.0f), "cold marks report no change (no GPU write)");
        Check(!DecayHeat(unit, 0.0f, 6.0f), "zero time step changes nothing");
        Check(unit.Any() && !unit.AnyHeat(), "cold mark stays as char");
    }

    void Repair()
    {
        Check(RepairClears(0.5f, 0.95f), "repaired above 0.9 clears");
        Check(!RepairClears(0.5f, 0.85f), "partial repair keeps the marks");
        Check(!RepairClears(1.0f, 0.95f), "a hit leaving the unit above 0.9 does not clear");
        Check(!RepairClears(0.95f, 0.95f), "steady health does not clear");
        Check(!RepairClears(NAN, 0.95f), "unreadable previous health does not clear");
    }

    void Packing()
    {
        UnitMarks unit;
        const float p0[3] = {1.0f, 2.0f, 3.0f};
        const float p5[3] = {9.0f, 0.0f, 0.0f};
        AddMark(unit, p0, 1.5f, 8);
        unit.next = 5;
        AddMark(unit, p5, 2.0f, 8);
        unit.marks[5].heat = 0.25f;
        float out[kParameterCount][4];
        PackParameters(unit, 8, out);
        Check(Near(out[0][0], 1.0f) && Near(out[0][1], 2.0f) && Near(out[0][2], 3.0f) && Near(out[0][3], 1.5f),
              "osMark0 = local xyz, radius");
        Check(Near(out[8][0], 1.0f) && Near(out[9][1], 0.25f), "osMarkHeat0.x = mark 0, osMarkHeat1.y = mark 5");
        Check(out[1][3] == 0.0f && out[8][1] == 0.0f, "unused slots are zero");
        PackParameters(unit, 4, out);
        Check(out[5][3] == 0.0f && out[9][1] == 0.0f, "slots past MaxMarksPerUnit are written as zero");
        Check(kMarkParameterBase == 1400 && kHeatParameterBase == 1408 && kParameterCount == 10,
              "custom parameter indices match the .program bindings");
    }

    void Spaces()
    {
        const double sim[3] = {100.0, 20.0, 50.0};
        const float origin[3] = {10.0f, 0.0f, -5.0f};
        float render[3];
        SimToRender(sim, origin, render);
        Check(Near(render[0], 90.0f) && Near(render[1], 20.0f) && Near(render[2], -45.0f),
              "sim -> render: subtract the origin, mirror Z");
        const float dir[3] = {0.0f, 0.0f, 1.0f};
        float rdir[3];
        SimDirectionToRender(dir, rdir);
        Check(Near(rdir[2], -1.0f), "directions mirror Z");

        const float identity[4] = {1.0f, 0.0f, 0.0f, 0.0f};
        const float one[3] = {1.0f, 1.0f, 1.0f};
        const float node[3] = {5.0f, 0.0f, 0.0f};
        const float point[3] = {6.0f, 2.0f, 3.0f};
        float local[3];
        Check(ToLocal(point, node, identity, one, local) && Near(local[0], 1.0f) && Near(local[1], 2.0f) &&
              Near(local[2], 3.0f), "identity orientation: translate only");

        // 90 degrees about +Y: local +X maps to world -Z, so world -Z is local +X.
        const float half = std::sqrt(0.5f);
        const float yaw[4] = {half, 0.0f, half, 0.0f};
        const float zero[3] = {0.0f, 0.0f, 0.0f};
        const float worldMinusZ[3] = {0.0f, 0.0f, -1.0f};
        Check(ToLocal(worldMinusZ, zero, yaw, one, local) && Near(local[0], 1.0f) && Near(local[2], 0.0f),
              "rotation is inverted");
        const float two[3] = {2.0f, 2.0f, 2.0f};
        const float scaled[3] = {4.0f, 0.0f, 0.0f};
        Check(ToLocal(scaled, zero, identity, two, local) && Near(local[0], 2.0f), "scale is divided out");
        const float bad[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        Check(!ToLocal(point, node, bad, one, local), "degenerate quaternion is refused");
        const float flat[3] = {1.0f, 0.0f, 1.0f};
        Check(!ToLocal(point, node, identity, flat, local), "zero scale is refused");
    }

    void Scale()
    {
        const float two[3] = {1.0f, -2.0f, 0.5f};
        Check(Near(LocalPerMetre(two), 0.5f), "largest absolute scale converts metres to local units");
        const float bad[3] = {NAN, 1.0f, 1.0f};
        const float zero[3] = {0.0f, 0.0f, 0.0f};
        Check(Near(LocalPerMetre(bad), 1.0f) && Near(LocalPerMetre(zero), 1.0f), "unusable scale: 1");

        UnitMarks unit;
        const float a[3] = {0.0f, 0.0f, 0.0f};
        AddMark(unit, a, 2.0f, 8, 0.5f);
        const float b[3] = {0.6f, 0.0f, 0.0f};  // 0.6 local >= 0.5 * 2.0 m * 0.5
        Check(!AddMark(unit, b, 2.0f, 8, 0.5f), "merge distance is compared in local units");
        float out[kParameterCount][4];
        PackParameters(unit, 8, out, 0.5f);
        Check(Near(out[0][3], 1.0f) && Near(unit.marks[0].radius, 2.0f), "radius stays metres, goes out local");
    }

    void Key()
    {
        const float key[4] = {1500.0f, 20.0f, -800.0f, 1.0f};
        const float jitter[3] = {1500.5f, 20.2f, -800.3f};  // ~0.6 m off at 1.7 km
        Check(KeyMatches(jitter, key), "float error at 1-2 km stays inside 0.2% of the distance");
        const float other[3] = {1530.0f, 20.0f, -800.0f};  // another object's view of the camera
        Check(!KeyMatches(other, key), "a camera 30 m off in local space is another object");
        const float nearKey[4] = {0.0f, 2.0f, 5.0f, 1.0f};
        const float nearOk[3] = {0.0f, 2.0f, 5.03f};
        const float nearBad[3] = {0.0f, 2.0f, 5.2f};
        Check(KeyMatches(nearOk, nearKey) && !KeyMatches(nearBad, nearKey), "close range: 5 cm floor");
        const float unset[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        const float origin[3] = {0.0f, 0.0f, 0.0f};
        Check(!KeyMatches(origin, unset), "a zeroed key (w = 0) never matches");
        Check(kKeyParameter == 1410, "key index matches the .program binding");
    }

    void Hull()
    {
        float out[3];
        const float inside[3] = {1.0f, 0.0f, 0.0f};
        const float any[3] = {1.0f, 0.0f, 0.0f};
        Check(PlaceOnHull(inside, any, 3.0f, out) && Near(out[0], 1.0f), "a point inside the hull is kept");

        const float outside[3] = {-10.0f, 0.0f, 0.0f};
        const float towards[3] = {1.0f, 0.0f, 0.0f};
        Check(PlaceOnHull(outside, towards, 3.0f, out) && Near(out[0], -3.0f) && Near(out[1], 0.0f),
              "travelling inward: where the line enters the sphere");

        const float graze[3] = {-10.0f, 5.0f, 0.0f};
        Check(PlaceOnHull(graze, towards, 3.0f, out) && Near(std::sqrt(out[0] * out[0] + out[1] * out[1]), 3.0f) &&
              out[1] > 0.0f, "line misses the sphere: radial clamp onto it");
        const float away[3] = {-1.0f, 0.0f, 0.0f};
        Check(PlaceOnHull(outside, away, 3.0f, out) && Near(out[0], -3.0f), "travelling away: radial clamp");
        Check(!PlaceOnHull(outside, towards, 0.0f, out), "no hull radius: refused");
    }
}

int main()
{
    Radius();
    Settings();
    RingAndMerge();
    Heat();
    Repair();
    Packing();
    Spaces();
    Scale();
    Key();
    Hull();
    return OpenShimTest::ExitCode();
}
