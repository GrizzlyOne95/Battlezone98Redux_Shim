// Tests for the Daywrecker / Comet AI defence rules (include/daywrecker_defence_policy.h).

#include "daywrecker_defence_policy.h"

#include "test_check.h"

#include <cmath>

using OpenShimTest::Check;

namespace
{
    using namespace BZROpenShim::DaywreckerDefencePolicy;

    bool Near(float a, float b, float eps = 1e-4f)
    {
        return a - b < eps && b - a < eps;
    }

    Frame Identity()
    {
        Frame f;
        f.right = Make(1, 0, 0);
        f.up = Make(0, 1, 0);
        f.front = Make(0, 0, 1);
        return f;
    }

    void TestOfferAttack()
    {
        Check(ShouldOfferAttack(true, true, true, true, true), "enemy bomb, armed, on, SP: Attack");
        Check(!ShouldOfferAttack(true, true, true, false, true), "option off: stock");
        Check(!ShouldOfferAttack(true, true, true, true, false), "multiplayer: stock");
        Check(!ShouldOfferAttack(true, false, true, true, true), "own-team bomb: stock Go To");
        Check(!ShouldOfferAttack(true, true, false, true, true), "unarmed: stock (as Craft::GetCommand)");
        Check(!ShouldOfferAttack(false, true, true, true, true), "not a bomb (a real powerup): stock");
        Check(OfferedCommand(kCmdGo, true, true, true, true, true) == kCmdAttack, "GO becomes ATTACK");
        Check(OfferedCommand(kCmdGo, true, true, true, false, true) == kCmdGo, "off keeps GO");
        Check(OfferedCommand(0, true, true, true, true, true) == 0, "only GO is rewritten (NONE stays)");
        Check(OfferedCommand(5, true, true, true, true, true) == 5, "only GO is rewritten (FOLLOW stays)");
    }

    void TestDetect()
    {
        const Vec3 unit = Make(0, 0, 0);
        const Vec3 front = Make(0, 0, 1);
        Check(Detects(unit, front, Make(0, 0, 70)), "70 m ahead: at the edge (4900), seen");
        Check(!Detects(unit, front, Make(0, 0, 70.01f)), "just past 70 m: not seen");
        Check(Detects(unit, front, Make(0, 500, 10)), "high above, ahead: XZ distance only");
        Check(Detects(unit, front, Make(60, 0, 0)), "abeam: front . d == 0 is in the half-space");
        Check(!Detects(unit, front, Make(0, 0, -10)), "behind: not seen");
        Check(!Detects(unit, front, Make(50, 0, 50)), "diagonal 70.7 m: out of range");
    }

    void TestScan()
    {
        Check(InRadius(150, 0, kScanRadius) && !InRadius(150, 1, kScanRadius), "radius edge on XZ");
        Check(InRadius(0, 0, kScanRadius), "zero distance");
        Check(ScanDue(1.0f, 0.5f, kScanInterval) && !ScanDue(0.9f, 0.5f, kScanInterval), "0.5 s throttle");
        Check(ScanDue(0.1f, 5.0f, kScanInterval), "clock went back (new mission): due");
        Check(CooldownReady(0.0f, 0.0f, false, kUnitCooldown), "never ordered: ready");
        Check(!CooldownReady(2.9f, 0.0f, true, kUnitCooldown) && CooldownReady(3.0f, 0.0f, true, kUnitCooldown),
              "3 s cooldown");

        CooldownTable<4> t;
        Check(t.Ready(7, 0.0f, kUnitCooldown), "unknown unit: ready");
        t.Mark(7, 10.0f);
        Check(!t.Ready(7, 11.0f, kUnitCooldown) && t.Ready(7, 13.0f, kUnitCooldown), "marked unit cools down");
        Check(t.Ready(8, 11.0f, kUnitCooldown), "other unit unaffected");
        for (uint32_t u = 1; u <= 5; ++u)
            t.Mark(100 + u, 20.0f + static_cast<float>(u));
        Check(t.Ready(7, 11.0f, kUnitCooldown), "full table evicts the oldest");
        Check(!t.Ready(105, 25.5f, kUnitCooldown), "newest kept");
        t.Clear();
        Check(t.Ready(105, 25.5f, kUnitCooldown), "clear forgets");
    }

    UnitView IdleArmedEnemy()
    {
        UnitView u;
        u.isCraft = true;
        u.hasWeapon = true;
        u.enemy = true;
        return u;
    }

    void TestTarget()
    {
        const uint32_t bomb = 0x1234;
        UnitView u = IdleArmedEnemy();
        Check(ShouldTargetBomb(u, bomb, 0, true, true, true), "idle armed enemy craft: target");
        Check(!ShouldTargetBomb(u, bomb, 0, true, false, true), "option off: no");
        Check(!ShouldTargetBomb(u, bomb, 0, true, true, false), "multiplayer: no");
        Check(!ShouldTargetBomb(u, bomb, kMaxUnitsPerBomb, true, true, true), "cap of 4 reached: no");
        Check(ShouldTargetBomb(u, bomb, kMaxUnitsPerBomb - 1, true, true, true), "below cap: yes");
        Check(!ShouldTargetBomb(u, bomb, 0, false, true, true), "cooling down: no");
        Check(!ShouldTargetBomb(u, 0, 0, true, true, true), "no bomb handle: no");

        UnitView v = u;
        v.hasWeapon = false;
        Check(!ShouldTargetBomb(v, bomb, 0, true, true, true), "unarmed: no (evades instead)");
        v = u;
        v.isPlayer = true;
        Check(!ShouldTargetBomb(v, bomb, 0, true, true, true), "player craft: never");
        v = u;
        v.isCraft = false;
        Check(!ShouldTargetBomb(v, bomb, 0, true, true, true), "not a craft: no");
        v = u;
        v.enemy = false;
        Check(!ShouldTargetBomb(v, bomb, 0, true, true, true), "own bomb: no");
        v = u;
        v.isCargo = true;
        Check(!ShouldTargetBomb(v, bomb, 0, true, true, true), "cargo: no");

        v = u;
        v.curWhat = kCmdDefend;
        Check(ShouldTargetBomb(v, bomb, 0, true, true, true), "defending: may be interrupted");
        v.curWhat = kCmdGo;
        Check(!ShouldTargetBomb(v, bomb, 0, true, true, true), "player/AIP GO order: never overridden");
        v.curWhat = 5;
        Check(!ShouldTargetBomb(v, bomb, 0, true, true, true), "FOLLOW: never overridden");
        v.curWhat = kCmdAttack;
        v.curWho = 0x9999;
        Check(!ShouldTargetBomb(v, bomb, 0, true, true, true), "active attack on something else: kept");
        v = u;
        v.nextWhat = kCmdGo;
        Check(!ShouldTargetBomb(v, bomb, 0, true, true, true), "pending order: never overridden");

        v = u;
        v.target = bomb;
        Check(TargetsBomb(v, bomb) && !ShouldTargetBomb(v, bomb, 0, true, true, true), "already aiming: no repeat");
        v = u;
        v.curWhat = kCmdAttack;
        v.curWho = bomb;
        Check(TargetsBomb(v, bomb), "attacking the bomb counts");
        v = u;
        v.nextWhat = kCmdAttack;
        v.nextWho = bomb;
        Check(TargetsBomb(v, bomb), "ordered onto the bomb counts");
        Check(!TargetsBomb(u, bomb) && !TargetsBomb(u, 0), "idle unit does not target");
    }

    void TestShouldEvade()
    {
        Check(ShouldEvade(true, true, false, false, true, true, true), "AI unit, detected, not targeting: evade");
        Check(!ShouldEvade(true, true, false, true, true, true, true), "a unit targeting the bomb does not evade it");
        Check(!ShouldEvade(true, true, true, false, true, true, true), "player craft: never touched");
        Check(!ShouldEvade(true, true, false, false, false, true, true), "not detected: no");
        Check(!ShouldEvade(true, false, false, false, true, true, true), "own bomb: no");
        Check(!ShouldEvade(false, true, false, false, true, true, true), "not a bomb: no");
        Check(!ShouldEvade(true, true, false, false, true, false, true), "option off: stock");
        Check(!ShouldEvade(true, true, false, false, true, true, false), "multiplayer: stock");
    }

    void TestEvadeForce()
    {
        const Frame f = Identity();
        const Vec3 zero = Make(0, 0, 0);
        // Bomb 50 m ahead, closing at 10 m/s along z, passing 3 m to the right.
        // r1 = 2 + 1 = 3, miss 3 -> factor Min(2.5 - 1, 1) = 1; t = 5.
        EvadeResult r = EvadeForce(zero, zero, f, 2.0f, Make(3, 0, 50), Make(0, 0, -10), 1.0f, 60.0f);
        Check(r.threat, "head-on near miss is a threat");
        Check(Near(r.force.x, -10.0f) && Near(r.force.y, 0.0f) && Near(r.force.z, 0.0f),
              "force away from the miss point, weight/(t+1)=10");

        // Outside 200 m (3D).
        r = EvadeForce(zero, zero, f, 2.0f, Make(0, 0, 200.01f), Make(0, 0, -10), 1.0f, 60.0f);
        Check(!r.threat, "beyond 200 m: ignored");
        r = EvadeForce(zero, zero, f, 2.0f, Make(0, 0, 200.0f), Make(0, 0, -10), 1.0f, 60.0f);
        Check(r.threat, "exactly 200 m (40000): kept");

        // Cone: z >= |x| and z >= 1.5|y|.
        r = EvadeForce(zero, zero, f, 2.0f, Make(10, 0, 10), Make(-1, 0, -1), 1.0f, 60.0f);
        Check(r.threat, "cone edge z == |x|: inside");
        r = EvadeForce(zero, zero, f, 2.0f, Make(10.01f, 0, 10), Make(-1, 0, -1), 1.0f, 60.0f);
        Check(!r.threat, "just outside x cone: ignored");
        r = EvadeForce(zero, zero, f, 2.0f, Make(0, 10, 15), Make(0, -2, -3), 1.0f, 60.0f);
        Check(r.threat, "cone edge z == 1.5|y|: inside");
        r = EvadeForce(zero, zero, f, 2.0f, Make(0, 10.01f, 15), Make(0, -2, -3), 1.0f, 60.0f);
        Check(!r.threat, "just outside y cone: ignored");
        r = EvadeForce(zero, zero, f, 2.0f, Make(0, 0, -20), Make(0, 0, 10), 1.0f, 60.0f);
        Check(!r.threat, "behind: ignored");

        // t <= 0 (moving away) and no relative speed.
        r = EvadeForce(zero, zero, f, 2.0f, Make(0, 0, 20), Make(0, 0, 10), 1.0f, 60.0f);
        Check(!r.threat, "receding (t < 0): ignored");
        r = EvadeForce(zero, zero, f, 2.0f, Make(0, 0, 20), Make(0, 10, 0), 1.0f, 60.0f);
        Check(!r.threat, "crossing with t == 0: ignored");
        r = EvadeForce(zero, Make(0, 0, 5), f, 2.0f, Make(0, 0, 20), Make(0, 0, 5), 1.0f, 60.0f);
        Check(!r.threat, "no relative velocity: ignored");

        // Miss distance boundary: 2.5 r1 is not a threat, just inside is.
        r = EvadeForce(zero, zero, f, 2.0f, Make(7.5f, 0, 50), Make(0, 0, -10), 1.0f, 60.0f);
        Check(!r.threat, "miss exactly 2.5 radii: not a threat");
        r = EvadeForce(zero, zero, f, 2.0f, Make(7.4f, 0, 50), Make(0, 0, -10), 1.0f, 60.0f);
        Check(r.threat && Near(r.force.x, -10.0f * (2.5f - 7.4f / 3.0f)), "factor 2.5 - miss/r1 near the edge");
        r = EvadeForce(zero, zero, f, 2.0f, Make(4.5f, 0, 50), Make(0, 0, -10), 1.0f, 60.0f);
        Check(r.threat && Near(r.force.x, -10.0f), "factor capped at 1 at 1.5 radii");
        r = EvadeForce(zero, zero, f, 2.0f, Make(6.0f, 0, 50), Make(0, 0, -10), 1.0f, 60.0f);
        Check(r.threat && Near(r.force.x, -5.0f), "factor 0.5 at 2 radii");
        r = EvadeForce(zero, zero, f, 2.0f, Make(3, 0, 50), Make(0, 0, -10), 1.0f, 0.0f);
        Check(!r.threat, "zero weight: no threat");

        // Unit frame turned 90 degrees: front = +x.
        Frame turned;
        turned.right = Make(0, 0, -1);
        turned.up = Make(0, 1, 0);
        turned.front = Make(1, 0, 0);
        r = EvadeForce(zero, zero, turned, 2.0f, Make(50, 0, 0), Make(-10, 0, 0), 1.0f, 60.0f);
        // Dead-centre: miss 0, as stock a threat with a zero force (the
        // direction scale is -1 / (0 + epsilon) times a zero vector).
        Check(r.threat && Near(r.force.x, 0.0f) && Near(r.force.z, 0.0f), "turned frame, dead-centre: threat, no push");
        r = EvadeForce(zero, zero, turned, 2.0f, Make(0, 0, 50), Make(0, 0, -10), 1.0f, 60.0f);
        Check(!r.threat, "turned frame: +z is now abeam, outside the cone");
    }

    void TestCombine()
    {
        Vec3 f = Combine(Make(3, 0, 4), true, Make(0, 0, 0), false);
        Check(Near(f.x, 3) && Near(f.z, 4), "small force kept");
        f = Combine(Make(30, 0, 0), false, Make(0, 0, 0), false);
        Check(Near(f.x, 30), "no threat recorded with a large force: no normalise");
        f = Combine(Make(30, 0, 0), true, Make(0, 0, 0), false);
        Check(Near(f.x, 20), "stock threat: normalised to 20");
        f = Combine(Make(0, 0, 0), false, Make(0, 0, 50), true);
        Check(Near(f.z, 20), "bomb threat: normalised to 20");
        f = Combine(Make(12, 0, 0), true, Make(0, 0, 16), true);
        Check(Near(f.x, 12) && Near(f.z, 16), "|F| == 20 exactly (400): not rescaled");
        f = Combine(Make(12, 0, 0), true, Make(0, 0, 17), true);
        Check(Near(std::sqrt(f.x * f.x + f.z * f.z), 20.0f), "just over 20: rescaled");
    }

    void TestRegistry()
    {
        BombRegistry<3> reg;
        Check(reg.Refresh(0, 1.0f) == nullptr, "handle 0 rejected");
        BombEntry* a = reg.Refresh(11, 1.0f);
        Check(a && a->handle == 11 && reg.Count() == 1, "add");
        a->assigned = 2;
        BombEntry* again = reg.Refresh(11, 1.1f);
        Check(again == a && again->assigned == 2 && Near(again->lastSeen, 1.1f), "refresh keeps state");
        reg.Refresh(12, 1.1f);
        reg.Refresh(13, 1.1f);
        Check(reg.Refresh(14, 1.1f) == nullptr, "full: refused");
        Check(reg.Prune(1.3f) == 0 && reg.Count() == 3, "0.2 s old: kept");
        reg.Refresh(12, 1.4f);
        Check(reg.Prune(1.4f) == 2 && reg.Count() == 1, "older than 0.25 s: dropped");
        Check(reg.Refresh(14, 1.4f) != nullptr, "freed slot reused");
        Check(reg.Remove(12) && !reg.Remove(12) && reg.Count() == 1, "remove on death/explode");
        Check(reg.Prune(0.5f) == 1, "clock went back: everything stale");
        reg.Refresh(20, 2.0f);
        reg.Clear();
        Check(reg.Count() == 0, "clear");
        Check(IsStale(1.26f, 1.0f) && !IsStale(1.25f, 1.0f), "stale boundary");
    }
}

int main()
{
    TestOfferAttack();
    TestDetect();
    TestScan();
    TestTarget();
    TestShouldEvade();
    TestEvadeForce();
    TestCombine();
    TestRegistry();
    return OpenShimTest::ExitCode();
}
