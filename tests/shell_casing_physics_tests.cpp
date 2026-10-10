// Unit tests for the engine-independent ShellCasings math
// (include/shell_casing_physics.h): eject vector, terrain normal, bounce,
// object contact, sim/render conversion, sizes and the class filter.
#include "shell_casing_physics.h"
#include "test_check.h"

#include <cmath>
#include <string>

using namespace BZROpenShim::ShellCasings;
using OpenShimTest::Check;

namespace
{
    bool Near(float a, float b, float eps = 1e-4f) { return std::fabs(a - b) <= eps; }
    bool Near(Vec3 a, Vec3 b, float eps = 1e-4f) { return Near(a.x, b.x, eps) && Near(a.y, b.y, eps) && Near(a.z, b.z, eps); }

    void TestEject()
    {
        MuzzleFrame frame;
        frame.position = {10, 2, 5};
        EjectParams p;
        p.barrelLength = 2.0f;
        p.breechFraction = 0.5f;
        p.portUp = 0.1f;
        p.speed = 4.0f;
        p.jitter = 0.0f;
        const EjectState e = ComputeEject(frame, p, {0, 0, 0}, 0, 0, 0);
        Check(Near(e.position, {10, 2.1f, 4}), "port sits back along the barrel by barrelLength * fraction, raised by portUp");
        Check(Near(Length(e.direction), 1.0f), "eject direction is unit length");
        Check(e.direction.x > 0.0f && e.direction.y > 0.0f && e.direction.z < 0.0f,
              "casings leave to the right, upward and slightly backward");
        Check(Near(Length(e.velocity), 4.0f), "no jitter: speed equals the configured speed");

        const EjectState moving = ComputeEject(frame, p, {0, 0, 20}, 0, 0, 0);
        Check(Near(Sub(moving.velocity, e.velocity), {0, 0, 20}), "the shooter's velocity is inherited");

        p.jitter = 0.25f;
        const EjectState jittered = ComputeEject(frame, p, {0, 0, 0}, 1, -1, 1);
        Check(Near(Sub(jittered.velocity, e.velocity), {1, -1, 1}), "jitter is +-fraction of speed per axis");

        // A rotated weapon: yawed 90 degrees, so front is +X and right is -Z.
        MuzzleFrame yawed;
        yawed.right = {0, 0, -1};
        yawed.front = {1, 0, 0};
        p.jitter = 0.0f;
        const EjectState y = ComputeEject(yawed, p, {0, 0, 0}, 0, 0, 0);
        Check(y.direction.z < 0.0f && y.direction.x < 0.0f, "ejection follows the weapon frame");

        // Degenerate frames fall back to sane axes instead of NaN.
        MuzzleFrame broken;
        broken.right = {0, 0, 0};
        broken.up = {0, 0, 0};
        broken.front = {0, 0, 0};
        Check(Finite(ComputeEject(broken, p, {0, 0, 0}, 0, 0, 0).velocity), "degenerate frame stays finite");
    }

    void TestGroundNormal()
    {
        Check(Near(GroundNormalFromHeights(1, 1, 1, 1, 0.25f), {0, 1, 0}), "flat ground is straight up");
        // Height rises toward +X by 1 per metre: the normal leans toward -X.
        const Vec3 slope = GroundNormalFromHeights(-0.25f, 0.25f, 0, 0, 0.25f);
        Check(Near(Length(slope), 1.0f) && slope.x < 0.0f && Near(slope.x, -slope.y, 1e-4f),
              "45-degree slope normal leans away from the rise");
        const Vec3 zslope = GroundNormalFromHeights(0, 0, 0.5f, -0.5f, 0.25f);
        Check(zslope.z > 0.0f && zslope.y > 0.0f, "Z slope tilts toward the downhill side");
    }

    void TestBounce()
    {
        ContactResponse r;
        r.restitution = 0.5f;
        r.friction = 0.25f;
        r.spinDamp = 0.5f;
        Vec3 v = {4, -10, 0};
        Vec3 w = {2, 2, 2};
        const float impact = Bounce(v, w, {0, 1, 0}, {0, 0, 0}, r);
        Check(Near(impact, 10.0f), "closing speed is the normal speed");
        Check(Near(v, {3, 5, 0}), "normal speed reflected with restitution, tangent reduced by friction");
        Check(Near(w, {1, 1, 1}), "spin damped per bounce");

        Vec3 away = {0, 3, 0};
        Vec3 spin = {1, 0, 0};
        Check(Bounce(away, spin, {0, 1, 0}, {0, 0, 0}, r) == 0.0f && Near(away, {0, 3, 0}),
              "separating contact is left alone");

        // A surface moving up at 5 m/s meets a casing at rest: it is struck.
        Vec3 rest = {0, 0, 0};
        Vec3 none = {0, 0, 0};
        const float hit = Bounce(rest, none, {0, 1, 0}, {0, 5, 0}, r);
        Check(Near(hit, 5.0f) && Near(rest.y, 7.5f), "moving surfaces bounce relative to their own velocity");
    }

    void TestObb()
    {
        // A hull 4 x 2 x 6 centred at (0, 1, 0), unrotated.
        const Obb box = ObbFromNode({-2, -1, -3}, {2, 1, 3}, {0, 1, 0}, {1, 0, 0, 0}, {1, 1, 1});
        Check(Near(box.center, {0, 1, 0}) && Near(box.half, {2, 1, 3}), "node-placed AABB becomes an OBB");

        const Contact above = SphereVsObb({0, 2.05f, 0}, 0.1f, box);
        Check(above.hit && Near(above.normal, {0, 1, 0}) && Near(above.depth, 0.05f), "touching the deck from above");

        const Contact clear = SphereVsObb({0, 2.5f, 0}, 0.1f, box);
        Check(!clear.hit, "a sphere above the deck does not touch");

        const Contact side = SphereVsObb({2.05f, 1, 0}, 0.1f, box);
        Check(side.hit && Near(side.normal, {1, 0, 0}), "side contact pushes outward along X");

        const Contact corner = SphereVsObb({2.05f, 2.05f, 0}, 0.1f, box);
        Check(corner.hit && corner.normal.x > 0.0f && corner.normal.y > 0.0f && Near(Length(corner.normal), 1.0f),
              "edge contact normal points diagonally away from the edge");

        const Contact inside = SphereVsObb({0, 1.8f, 0}, 0.1f, box);
        Check(inside.hit && Near(inside.normal, {0, 1, 0}) && Near(inside.depth, 0.3f),
              "a centre inside leaves through the nearest face (the deck here)");

        // Rotated 90 degrees about Y with scale 2: local X becomes world -Z.
        const float s = std::sqrt(0.5f);
        const Obb turned = ObbFromNode({-1, -1, -1}, {1, 1, 1}, {10, 0, 0}, {s, 0, s, 0}, {2, 2, 2});
        Check(Near(turned.half, {2, 2, 2}) && Near(turned.axis[0], {0, 0, -1}), "node rotation and scale reach the OBB");
        Check(PointInsideObb({10, 0, 1.9f}, turned) && !PointInsideObb({10, 0, 2.2f}, turned),
              "inside test honours the scaled extents");
        Check(PointInsideObb({10, 0, 2.2f}, turned, 0.25f), "inside test margin");

        // Offset bounds: the box centre is the node-transformed bounds centre.
        const Obb offset = ObbFromNode({0, 0, 0}, {2, 2, 2}, {5, 0, 0}, {1, 0, 0, 0}, {1, 1, 1});
        Check(Near(offset.center, {6, 1, 1}), "bounds not centred on the node origin");
    }

    void TestSpace()
    {
        const Vec3 origin = {1280, 0, -1280};
        const Vec3 sim = {665, 32, 710};
        const Vec3 render = SimToRenderPoint(sim, origin);
        Check(Near(render, {-615, 32, 570}), "sim -> render matches the logged gib pair (origin 1280,0,-1280)");
        Check(Near(RenderToSimPoint(render, origin), sim), "render -> sim round-trips");
        Check(Near(SimToRenderDir({1, 2, 3}), {1, 2, -3}), "directions only mirror Z");
    }

    void TestOrientation()
    {
        const Quat q = OrientAlong({1, 0, 0}, {0, 1, 0});
        Check(Near(Rotate(q, {0, 0, 1}), {1, 0, 0}), "casing axis (local +Z) follows the barrel");
        Check(Near(Rotate(q, {0, 1, 0}), {0, 1, 0}), "casing up follows the weapon up");
        const Quat steep = OrientAlong({0, 1, 0}, {0, 1, 0});
        Check(Near(Rotate(steep, {0, 0, 1}), {0, 1, 0}) && Near(Length(Rotate(steep, {0, 1, 0})), 1.0f),
              "axis parallel to up still yields a valid frame");
        const Quat spun = IntegrateSpin({1, 0, 0, 0}, {0, 3.14159265f, 0}, 0.001f);
        Check(Near(spun.w * spun.w + spun.x * spun.x + spun.y * spun.y + spun.z * spun.z, 1.0f) && spun.y > 0.0f,
              "spin integration stays normalised and turns the right way");
    }

    void TestSizesAndKinds()
    {
        Check(WeaponKindFromRtti(".?AVCannon@@") == WeaponKind::Cannon &&
                  WeaponKindFromRtti(".?AVMortar@@") == WeaponKind::Mortar &&
                  WeaponKindFromRtti(".?AVMachineGun@@") == WeaponKind::MachineGun &&
                  WeaponKindFromRtti(".?AVSniperGun@@") == WeaponKind::SniperGun &&
                  WeaponKindFromRtti(".?AVLauncher@@") == WeaponKind::Unknown && WeaponKindFromRtti(nullptr) == WeaponKind::Unknown,
              "native weapon classes map to kinds");
        Check(std::string(WeaponKindLabel(WeaponKind::MachineGun)) == "machinegun", "kind labels are the ODF classLabels");
        Check(Near(AmmoSizeFactor(0), 0.8f) && Near(AmmoSizeFactor(1000000), 1.5f) && Near(AmmoSizeFactor(-5), 0.8f),
              "ammo factor is clamped to [0.8, 1.5]");
        Check(AmmoSizeFactor(2) < AmmoSizeFactor(9) && AmmoSizeFactor(9) < AmmoSizeFactor(50), "ammo factor grows with cost");
        Check(CasingLength(WeaponKind::MachineGun, 2) < CasingLength(WeaponKind::Cannon, 9) &&
                  CasingLength(WeaponKind::Cannon, 9) < CasingLength(WeaponKind::Mortar, 50),
              "minigun < cannon < mortar casings for stock costs");
        Check(Near(SinkScale(0, 1.5f), 1.0f) && Near(SinkScale(1.5f, 1.5f), 0.0f) && SinkScale(0.75f, 1.5f) > 0.5f &&
                  Near(SinkScale(1, 0), 0.0f),
              "sink scale shrinks from 1 to 0");
    }

    void TestFilter()
    {
        const ClassFilter def = ParseClassFilter(DefaultClassList());
        Check(FilterAllows(def, "cannon", "gatstab.odf"), "default: cannon ODFs eject");
        Check(FilterAllows(def, "machinegun", "gminigun"), "default: miniguns eject");
        Check(FilterAllows(def, "mortar", "GMORTAR.ODF"), "default: mortars eject, case-insensitive");
        Check(FilterAllows(def, "snipergun", "gsnipe.odf"), "default: sniper rifles eject");
        Check(!FilterAllows(def, "cannon", "gquake.odf") && !FilterAllows(def, "cannon", "gsandbag"),
              "default: seismic and sandbag cannons do not");
        Check(!FilterAllows(def, "unknown", "glaser.odf"), "unlisted classes never eject");

        const ClassFilter custom = ParseClassFilter(" \"cannon; -gblast.odf , gminigun\" ");
        Check(FilterAllows(custom, "cannon", "gatstab") && !FilterAllows(custom, "cannon", "gblast.odf"),
              "exclusions win over a class include");
        Check(FilterAllows(custom, "machinegun", "gminigun.odf") && !FilterAllows(custom, "machinegun", "gminigna"),
              "a single ODF can be enabled without its class");

        const ClassFilter all = ParseClassFilter("all,-machinegun");
        Check(FilterAllows(all, "mortar", "x") && !FilterAllows(all, "machinegun", "gminigun"), "all with a class exclusion");
        Check(!FilterAllows(ParseClassFilter(""), "cannon", "gatstab"), "an empty list disables every weapon");
        Check(NormalizeToken("GQuake.ODF") == "gquake" && NormalizeToken(".odf") == ".odf", "token normalisation");
    }
}

int main()
{
    TestEject();
    TestGroundNormal();
    TestBounce();
    TestObb();
    TestSpace();
    TestOrientation();
    TestSizesAndKinds();
    TestFilter();
    return OpenShimTest::ExitCode();
}
