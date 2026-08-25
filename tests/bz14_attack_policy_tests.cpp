// ============================================================================
// bz14_attack_policy_tests.cpp - unit tests for the recovered 1.4 AttackTask
// decision core (include/bz14_attack_policy.h). No engine required: every
// case feeds a synthetic AttackFacts snapshot and checks the verdict.
//
// Expectations are derived from the recovered 1.4 state machine
// (AttackTask::DoState @0x40CDE0) and the 1.5/Redux divergence table in
// reverse_engineering/bz14_attacktask_recovery_20260824.md.
// ============================================================================

#include "bz14_attack_policy.h"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <initializer_list> // MSVC: braced-init-list range-for needs this
                            // declared explicitly on newer toolchains

using namespace bz14;

namespace
{
    int g_failures = 0;
    // 2pi used as a heading to exercise wrap equivalence in quad math.
    constexpr double kTwoPiHead = 6.283185307179586477;

    void Check(bool cond, const char* what)
    {
        if (!cond)
        {
            std::fprintf(stderr, "FAIL: %s\n", what);
            ++g_failures;
        }
    }

    Bz14Decision Decide(const AttackFacts& f)
    {
        return DecideAttackTick(f);
    }

    AttackFacts Base(int cur, int stockNext)
    {
        AttackFacts f;
        f.curState = cur;
        f.stockNextState = stockNext;
        f.distSq = 100.0f;   // well inside any ring
        f.rangeSq = 2500.0f; // 50^2 slide ring
        f.ableToHit = false;
        f.freshHit = false;
        f.sidewaysAndClose = false;
        f.slideArrived = false;
        f.enemyTaskState = StateUnstuck; // non-engaged by both predicates
        // Healthy evidence by default: the fail-closed contract tests below
        // explicitly strip individual flags.
        f.ableToHitValid = true;
        f.freshHitValid = true;
        f.sidewaysAndCloseValid = true;
        f.slideArrivedValid = true;
        f.enemyTaskStateValid = true;
        return f;
    }

    void TestApproachD1()
    {
        // Stock routes an acquired solution to BLAST-HOLD; 1.4 goes SLIDE.
        AttackFacts f = Base(StateApproach, StateBlastHold);
        f.ableToHit = true;
        const Bz14Decision d = Decide(f);
        Check(d.kind == Bz14Decision::TransitionTo && d.targetState == StateSlide,
              "approach+aTH -> slide");

        // Without a firing solution stock's approach outcome (goto/re-enter)
        // is identical: defer.
        f.ableToHit = false;
        f.stockNextState = StateNone;
        Check(Bz14Defer(Decide(f)), "approach stay defers");

        f.stockNextState = StateUnstuck;
        Check(Bz14Defer(Decide(f)), "approach stuck defers");
    }

    void TestSlideEngagementPredicate()
    {
        // Enemy actively maneuvering {2,5,7}: both builds choose BLAST-HOLD.
        for (const int enemy : {StateApproach, StateBlast, StateSlide})
        {
            AttackFacts f = Base(StateSlide, StateBlastHold);
            f.enemyTaskState = enemy;
            Check(Bz14Defer(Decide(f)),
                  "engaged enemy {2,5,7} agrees on blast-hold");
        }
        // Redux-only extension: enemy BLAST-HOLD(10). 1.4 keeps dueling.
        {
            AttackFacts f = Base(StateSlide, StateBlastHold);
            f.enemyTaskState = StateBlastHold;
            f.slideArrived = true; // genuine arrival: both agree on 10
            Check(Bz14Defer(Decide(f)), "enemy-10 with arrival stays agreed");
            f.slideArrived = false;
            const Bz14Decision d = Decide(f);
            Check(d.kind == Bz14Decision::StayButRunSlide,
                  "enemy-10 without arrival keeps sliding");
        }
        // Range exceed and stuck are identical transitions.
        {
            AttackFacts f = Base(StateSlide, StateApproach);
            f.distSq = f.rangeSq * 2.0f;
            Check(Bz14Defer(Decide(f)), "slide range-exceed defers");
        }
        {
            AttackFacts f = Base(StateSlide, StateUnstuck);
            Check(Bz14Defer(Decide(f)), "slide stuck defers");
        }
    }

    void TestSlideAbeam()
    {
        // D2c: SaC fires even without a firing solution in 1.4.
        {
            AttackFacts f = Base(StateSlide, StateNone);
            f.sidewaysAndClose = true;
            const Bz14Decision d = Decide(f);
            Check(d.kind == Bz14Decision::TransitionTo &&
                      d.targetState == StateStand,
                  "SaC without aTH still stands (D2c)");
        }
        // With a firing solution both builds already agree.
        {
            AttackFacts f = Base(StateSlide, StateStand);
            f.ableToHit = true;
            f.sidewaysAndClose = true;
            Check(Bz14Defer(Decide(f)), "SaC with aTH agrees");
        }
        // Premature blast-hold from the aTH-no-SaC short circuit.
        {
            AttackFacts f = Base(StateSlide, StateBlastHold);
            f.ableToHit = true;
            const Bz14Decision d = Decide(f);
            Check(d.kind == Bz14Decision::StayButRunSlide,
                  "aTH && !SaC keeps the duel alive");
        }
        // Plain continue-sliding stays suppressed.
        {
            AttackFacts f = Base(StateSlide, StateNone);
            const Bz14Decision d = Decide(f);
            Check(d.kind == Bz14Decision::DeferToStock,
                  "stock keep-sliding defers");
        }
    }

    void TestStandExpiry()
    {
        // D4: expiry rotates to SLIDE in 1.4, Redux flees.
        {
            AttackFacts f = Base(StateStand, StateFlee);
            f.freshHit = false;
            const Bz14Decision d = Decide(f);
            Check(d.kind == Bz14Decision::TransitionTo &&
                      d.targetState == StateSlide,
                  "stand expiry -> slide (D4)");
        }
        // Fresh-hit flee is identical behavior: defer.
        {
            AttackFacts f = Base(StateStand, StateFlee);
            f.freshHit = true;
            Check(Bz14Defer(Decide(f)), "fresh-hit flee defers");
        }
        // Unknown freshness (times unreadable): the expiry divergence is
        // unproven, stock wins (fail-closed).
        {
            AttackFacts f = Base(StateStand, StateFlee);
            f.freshHitValid = false;
            Check(Bz14Defer(Decide(f)), "unknown freshness defers (D4)");
        }
    }

    void TestBlastHoldLostShot()
    {
        // D5: lost shot always returns to SLIDE in 1.4; Redux re-approaches
        // when only its extended predicate fired.
        {
            AttackFacts f = Base(StateBlastHold, StateApproach);
            f.ableToHit = false;
            const Bz14Decision d = Decide(f);
            Check(d.kind == Bz14Decision::TransitionTo &&
                      d.targetState == StateSlide,
                  "blast-hold lost shot -> slide (D5)");
        }
        // D5 requires a genuinely lost shot: a fresh-hit flee recorded by
        // stock is identical behavior in both builds and must defer even
        // though the recorded transition is APPROACH-shaped elsewhere.
        {
            AttackFacts f = Base(StateBlastHold, StateFlee);
            f.freshHit = true;
            Check(Bz14Defer(Decide(f)), "blast-hold fresh-hit defers");
        }
        // A fresh hit while stock records APPROACH still defers: the
        // recovered 1.4 machine routes fresh hits to FLEE before the
        // lost-shot rule applies, and fresh-hit routing is identical.
        {
            AttackFacts f = Base(StateBlastHold, StateApproach);
            f.ableToHit = false;
            f.freshHit = true;
            Check(Bz14Defer(Decide(f)),
                  "blast-hold fresh-hit approach defers (freshness wins)");
        }
        // Regained firing solution blasts in both: defer.
        {
            AttackFacts f = Base(StateBlastHold, StateNone);
            f.ableToHit = true;
            Check(Bz14Defer(Decide(f)), "blast-hold firing defers");
        }
        // Unknown aTH latch: the "lost shot" premise is unproven even with
        // freshness known-false; stock wins (fail-closed D5).
        {
            AttackFacts f = Base(StateBlastHold, StateApproach);
            f.ableToHitValid = false;
            Check(Bz14Defer(Decide(f)), "unknown aTH defers (D5)");
        }
    }

    void TestSlidePredicateOrder()
    {
        // Recovered order inside SLIDE: range-exceed and stuck exit first,
        // then the engagement predicate, then SaC. An engaged enemy plus SaC
        // therefore agrees on BLAST-HOLD (engagement checked first), which
        // is exactly what both builds record.
        {
            AttackFacts f = Base(StateSlide, StateBlastHold);
            f.enemyTaskState = StateSlide;
            f.sidewaysAndClose = true;
            Check(Bz14Defer(Decide(f)),
                  "engaged enemy wins over SaC (order preserved)");
        }
        // Non-engaged enemy plus SaC without a firing solution: 1.4 stands
        // regardless of the firing solution (D2c).
        {
            AttackFacts f = Base(StateSlide, StateNone);
            f.enemyTaskState = StateWait; // non-engaged in both predicates
            f.sidewaysAndClose = true;
            const Bz14Decision d = Decide(f);
            Check(d.kind == Bz14Decision::TransitionTo &&
                      d.targetState == StateStand,
                  "non-engaged + SaC stands (D2c)");
        }
        // Enemy state UNAVAILABLE is not "non-engaged" (PR #57 review C2,
        // fail-closed): the recovered machine reads the field before
        // choosing, so an unreadable field leaves the divergence unproven
        // and stock must win.
        {
            AttackFacts f = Base(StateSlide, StateBlastHold);
            f.enemyTaskState = -1;
            f.enemyTaskStateValid = false;
            Check(Bz14Defer(Decide(f)),
                  "unavailable enemy state defers (fail-closed)");
        }
        // SidewaysAndClose unavailable: D2c and the keep-dueling arm both
        // depend on it; without evidence stock wins even with the enemy
        // state readable.
        {
            AttackFacts f = Base(StateSlide, StateNone);
            f.sidewaysAndClose = false;
            f.sidewaysAndCloseValid = false;
            Check(Bz14Defer(Decide(f)),
                  "unavailable SaC defers on keep-sliding record");
        }
        {
            AttackFacts f = Base(StateSlide, StateBlastHold);
            f.ableToHit = true;
            f.slideArrivedValid = false; // force vector unreadable
            Check(Bz14Defer(Decide(f)),
                  "unreadable force vector cannot prove collapse");
        }
        // Genuine slide arrival agrees with stock's BLAST-HOLD even when no
        // enemy activity was observable... provided the OTHER inputs were
        // readable; here enemy state is valid-but-unengaged and SaC false.
        {
            AttackFacts f = Base(StateSlide, StateBlastHold);
            f.enemyTaskState = StateWait;
            f.slideArrived = true;
            Check(Bz14Defer(Decide(f)),
                  "arrival honors stock blast-hold");
        }
    }

    void TestOtherStatesNeverDiverge()
    {
        for (const int cur :
             {StateInit, StateUnstuck, StateFollow, StateBlast, StateWait,
              StateTravel, StateFollowTravel})
        {
            AttackFacts f = Base(cur, StateDone);
            Check(Bz14Defer(Decide(f)), "non-combat state defers");
        }
    }

    void TestNoThrashAtRingBoundary()
    {
        // The recovered policy has no added smoothing: hysteresis comes from
        // 1.4 itself (state persistence + timer windows). Simulate the worst
        // case - distance oscillating around rangeSq - and verify decisions
        // remain stable per side of the boundary rather than inventing
        // transitions inside one side.
        for (int i = 0; i <= 16; ++i)
        {
            AttackFacts f = Base(StateSlide, StateNone);
            f.distSq = f.rangeSq + (i % 2 ? 1.0f : -1.0f);
            const Bz14Decision d = Decide(f);
            if (f.distSq > f.rangeSq)
            {
                // Above the ring stock records APPROACH and we defer; below
                // it stock stays and we defer. Neither side thrashes.
                f.stockNextState =
                    f.distSq > f.rangeSq ? StateApproach : StateNone;
                Check(Bz14Defer(Decide(f)), "ring boundary defers");
            }
            else
            {
                Check(Bz14Defer(d), "inside ring keeps stock stay");
            }
        }
    }

    void TestQuadMath()
    {
        // get_weapon_quad replication: quad 0 dead ahead, 2/6 abeam,
        // 4 dead behind (sector edges at +-22.5 degrees).
        const double kDeg = 3.14159265358979323846 / 180.0;
        Check(WeaponQuad(0.0, 0.0) == 0, "quad ahead");
        Check(WeaponQuad(0.0, 90.0 * kDeg) == 2, "quad right abeam");
        Check(WeaponQuad(0.0, -90.0 * kDeg) == 6, "quad left abeam");
        Check(WeaponQuad(0.0, 180.0 * kDeg) == 4, "quad behind");
        Check(WeaponQuad(0.0, 22.4 * kDeg) == 0 ||
                  WeaponQuad(0.0, 22.6 * kDeg) == 1,
              "sector edge near half-octant");
        // Bearing wraps into [0,2pi): -90 degrees must equal +270.
        Check(WeaponQuad(0.0, 270.0 * kDeg) ==
                  WeaponQuad(0.0, -90.0 * kDeg),
              "bearing wrap equivalence");
        // Heading wrap: 2*pi is the same heading as 0 -> target ahead.
        Check(WeaponQuad(kTwoPiHead, 0.0) == 0 &&
                  WeaponQuad(0.0, 0.0) == 0,
              "heading wrap equivalence");
        Check(QuadIsAbeam(2) && QuadIsAbeam(6) && !QuadIsAbeam(0),
              "abeam set is {2,6}");
        Check(!EnemyEngaged14(StateBlastHold) &&
                  EnemyEngaged14(StateSlide),
              "legacy engagement set excludes blast-hold");
    }
} // namespace

int main()
{
    TestApproachD1();
    TestSlideEngagementPredicate();
    TestSlideAbeam();
    TestSlidePredicateOrder();
    TestStandExpiry();
    TestBlastHoldLostShot();
    TestOtherStatesNeverDiverge();
    TestNoThrashAtRingBoundary();
    TestQuadMath();

    if (g_failures == 0)
    {
        std::printf("bz14_attack_policy_tests: all passed\n");
        return 0;
    }
    std::printf("bz14_attack_policy_tests: %d failure(s)\n", g_failures);
    return 1;
}
