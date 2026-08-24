#pragma once

// ============================================================================
// bz14_attack_policy.h - recovered Battlezone 1.4 AttackTask tactical policy
//
// Pure decision core reconstructed from the 1.4 runtime-unpacked image
// (AttackTask::ChooseState 0x40C7F0, AttackTask::DoState 0x40CDE0) and the
// PDB-named 1.5 source tree. See
// reverse_engineering/bz14_attacktask_recovery_20260824.md for evidence.
//
// Engine-independent: operates on a caller-populated fact snapshot so the
// decision logic is unit-testable without the game running. The engine-facing
// hook lives in src/patches/bz14_attack_policy.cpp; it collects facts from the
// live Redux task object (SEH-guarded), lets stock Redux DoState run, then
// applies the verdict by rewriting task+0x0C (nextState) at the sites where
// 1.4 and Redux provably diverge.
//
// STATUS (2026-08-24 audit): EXPERIMENTAL / QUARANTINED. Runtime census
// proved the detour target, generic AttackTask::DoState @0x00478A50, executes
// live for fighter/scout engagements (full 1.4 duel machine observed) but
// NEVER for tank-family combat, which runs reduced family-specific task
// skeletons instead (see reverse_engineering/bz14_attacktask_recovery_20260824.md
// §6.4). Enabling this feature therefore restores 1.4 behavior only for some
// unit families while others stay on Redux - a historically inconsistent mix.
// It ships as developer-only research instrumentation (environment-variable
// activation, no ini keys) until family-complete restoration exists.
//
// Redux object layouts remain authoritative: no 1.4 memory is injected and
// movement/steering/navigation/weapon systems are not replaced. The only
// game primitive the compatibility path may invoke directly is UnitTask::
// DoSlide (FUN_00606E20, zero-extra-arg __thiscall), mirroring the exact
// call stock Redux performs inside state 7.
// ============================================================================

#include <cmath>

namespace bz14
{
    // AttackTask state ids - identical numbering across 1.4, 1.5 and Redux
    // (PROVEN: same switch labels in all three builds).
    enum AttackState : int
    {
        StateNone = 0,          // "NO_STATE": no transition requested (stay)
        StateInit = 1,
        StateApproach = 2,
        StateUnstuck = 3,
        StateFollow = 4,
        StateBlast = 5,
        StateWait = 6,
        StateSlide = 7,
        StateStand = 8,
        StateFlee = 9,
        StateBlastHold = 10,
        StateTravel = 11,
        StateFollowTravel = 12,
        StateDone = 13
    };

    // 1.4 slide-exit engagement predicate (DoState case 7 @0x40CF97): the
    // opponent's own activity state in {2 APPROACH, 5 BLAST, 7 SLIDE} marks
    // an engaged enemy -> blast-hold (10). Redux FUN_00477D70 tests the same
    // field but additionally treats {10 BLAST-HOLD} as engaged; 1.4 did not.
    inline bool EnemyEngaged14(int enemyTaskState)
    {
        return enemyTaskState == StateApproach ||
               enemyTaskState == StateBlast ||
               enemyTaskState == StateSlide;
    }

    // SidewaysAndClose abeam octants (get_weapon_quad @1.5 0x004ECBAC):
    // quad = floor((rel + 2pi + pi/8) * 4/pi) & 7, rel wrapped to [0,2pi).
    // Quads 2 / 6 are the abeam sectors (+-67.5..112.5 degrees).
    inline bool QuadIsAbeam(int quad)
    {
        return quad == 2 || quad == 6;
    }

    // Octant replication of get_weapon_quad for tests/tools. The live hook
    // calls the game's own SidewaysAndClose instead of this helper.
    inline int WeaponQuad(double heading, double bearing)
    {
        const double kTwoPi = 6.283185307179586477;
        constexpr double kBias = 6.6758842;  // stock literal = 2pi + pi/8
        constexpr double kScale = 1.2732395; // stock literal ~ 4/pi
        double rel = bearing - heading;
        rel -= kTwoPi * std::floor(rel / kTwoPi);
        return static_cast<int>(std::floor((rel + kBias) * kScale)) & 7;
    }

    // Fact snapshot collected by the engine hook for one AttackTask tick.
    struct AttackFacts
    {
        int curState = 0;         // task+0x08
        int stockNextState = 0;   // task+0x0C after stock DoState ran
        bool ableToHit = false;   // task+0xC4 latch (fresh this tick)
        float distSq = 0.0f;      // horizontal craft<->target distance^2
        float rangeSq = 1.0f;     // task+0xA0 weapon/slide ring
        bool freshHit = false;    // damaged after current state was entered
        bool sidewaysAndClose = false;  // engine SidewaysAndClose(him, me)
        bool slideArrived = false;      // VecLen(task+0x4C..54) < 5.0
        int enemyTaskState = -1;        // slot12(him)+0x84; <0 = unavailable
    };

    // Decision produced for one tick.
    struct Bz14Decision
    {
        enum Kind
        {
            DeferToStock,   // 1.4 and Redux agree (or inputs unavailable)
            Stay,           // suppress stock's recorded transition (write 0)
            TransitionTo,   // force this recorded transition
            StayButRunSlide // stay sliding; hook must run DoSlide itself and
                            // may upgrade to BlastHold on arrival
        };
        Kind kind = DeferToStock;
        int targetState = 0;
    };

    inline bool Bz14Defer(const Bz14Decision& d)
    {
        return d.kind == Bz14Decision::DeferToStock;
    }

    // Recovered 1.4 recorded-transition policy for the four divergent sites.
    // Only Approach(2), Slide(7), Stand(8) and BlastHold(10) can diverge from
    // Redux; every other state defers unconditionally.
    inline Bz14Decision DecideAttackTick(const AttackFacts& f)
    {
        switch (f.curState)
        {
        case StateApproach:
        {
            // D1: 1.4 routes an acquired firing solution into the strafe duel
            // (SLIDE); 1.5/Redux park in BLAST-HOLD. 1.4 site 0x40D190 vs
            // 1.5 LAB_0040F59D / Redux case-0 head. Everything else matches.
            if (f.stockNextState == StateBlastHold)
                return {Bz14Decision::TransitionTo, StateSlide};
            return {Bz14Decision::DeferToStock, 0};
        }
        case StateSlide:
        {
            if (f.stockNextState == StateApproach ||
                f.stockNextState == StateUnstuck ||
                f.stockNextState == StateDone)
            {
                // Range-exceed, stuck and abort paths are identical.
                return {Bz14Decision::DeferToStock, 0};
            }
            if (EnemyEngaged14(f.enemyTaskState))
            {
                // Legacy predicate is a strict subset of Redux's; when it
                // fires Redux also chose BLAST-HOLD. Agreement.
                return {Bz14Decision::DeferToStock, 0};
            }
            if (f.sidewaysAndClose)
            {
                // 1.4 checks SaC regardless of the firing solution (D2c);
                // Redux gates it on ableToHit.
                return f.stockNextState == StateStand
                           ? Bz14Decision{Bz14Decision::DeferToStock, 0}
                           : Bz14Decision{Bz14Decision::TransitionTo,
                                          StateStand};
            }
            if (f.stockNextState == StateBlastHold)
            {
                // Premature blast-hold: enemy only "engaged" via Redux's
                // extra {10} arm, or aTH-without-SaC short-circuit. 1.4
                // keeps dueling unless the slide force collapsed (< 5).
                if (f.slideArrived)
                    return {Bz14Decision::DeferToStock, 0};
                return {Bz14Decision::StayButRunSlide, 0};
            }
            // stockNext == NONE (kept sliding) or STAND handled above.
            return {Bz14Decision::DeferToStock, 0};
        }
        case StateStand:
        {
            // D4: stand-window expiry (>8s) rotates back to SLIDE in 1.4;
            // 1.5/Redux flee from the target instead. Fresh-hit flees are
            // identical in both builds and defer.
            if (f.stockNextState == StateFlee && !f.freshHit)
                return {Bz14Decision::TransitionTo, StateSlide};
            return {Bz14Decision::DeferToStock, 0};
        }
        case StateBlastHold:
        {
            // D5: lost firing solution. 1.4 always returns to SLIDE; Redux
            // re-approaches (2) when its extended predicate says engaged.
            if (f.stockNextState == StateApproach && !f.freshHit &&
                !f.ableToHit)
                return {Bz14Decision::TransitionTo, StateSlide};
            return {Bz14Decision::DeferToStock, 0};
        }
        default:
            return {Bz14Decision::DeferToStock, 0};
        }
    }
} // namespace bz14

// ---------------------------------------------------------------------------
// Engine-integration surface (implemented in src/patches/bz14_attack_policy.cpp).
// QUARANTINED, developer-only: configuration comes exclusively from the
// OPENSHIM_LEGACY14_* environment variables (no openshim.ini keys) so the
// feature can never ship enabled to end users while its target is
// execution-dead. bzr_hooks.cpp arbitrates the shared AttackTask::DoState
// detour site and passes ownership in; AIKITE always wins by default because
// an instrumentation mode must never silently disable a working feature.
// ---------------------------------------------------------------------------
namespace bz14
{
    // True when this layer would own (or owns) the DoState detour.
    bool OwnsAttackTaskDetour();

    // True when developer environment controls request either mode. Read
    // BEFORE the AIKITE kite installer runs so an exclusive reservation can
    // leave the shared AttackTask::DoState site free for this layer instead
    // of trying to displace an already-installed detour.
    bool PolicyHookRequested();

    // Attempts installation. attackTaskSiteTaken must be true when another
    // OpenShim feature already detours AttackTask::DoState (AIKITE kite
    // tuning). This layer ALWAYS defers in that case - shadow because pure
    // measurement must stay behavior-neutral, apply because displacing an
    // installed inline detour cannot be done safely or validably. A
    // developer who wants the legacy policy exclusively sets
    // OPENSHIM_LEGACY14_EXCLUSIVE=1 (and bzr_hooks.cpp then leaves the site
    // free at install time); nothing displaces anything at runtime. Returns
    // true when installed or already live.
    bool InstallPolicyHookIfPossible(bool attackTaskSiteTaken);

    // One-shot session summary via [BZ14] log line (call at shutdown).
    void ReportPolicyStats();
} // namespace bz14
