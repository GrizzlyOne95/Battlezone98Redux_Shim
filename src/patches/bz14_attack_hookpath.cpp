// ============================================================================
// bz14_attack_hookpath.cpp - post-stock tick pipeline for the Battlezone 1.4
// AttackTask compatibility layer.
//
// Split out of bz14_attack_policy.cpp so the EXACT path the live DoState hook
// executes (early-outs, fact collection, pure policy, verdict application)
// is also callable from the integration regression tests against synthetic
// task memory. The live hook body, configuration, install arbitration and
// session stats remain in bz14_attack_policy.cpp; this TU owns everything
// between "trampoline returned" and "verdict applied".
//
// Fail-closed contract (PR #57 review): apply mode may only rewrite a
// recorded transition when every input the recovered rule consumes was
// actually readable this tick. Unreadable enemy state, an unavailable
// SidewaysAndClose helper, or a force vector that failed to read defer to
// stock instead of being folded into synthesized values.
// ============================================================================

#include "bz14_attack_policy.h"
#include "bz14_attack_redux.h"

#include "patcher.h"

#include <Windows.h>

#include <cmath>

namespace bz14
{
    namespace
    {
        using BZROpenShim::Log;

        // 1.4 slide-arrival force length (DoState case 7, _DAT_005E6E9C).
        constexpr float kSlideArriveLen = 5.0f;

        long g_traceBudget = 0;
        long g_tickBudget = 0;

        unsigned long g_evaluations = 0;
        unsigned long g_skipsNone = 0;
        // Attempted vs successful mutation are tracked separately: the
        // audit's core lesson is that these claims are not interchangeable.
        unsigned long g_overrideAttempts = 0;   // policy diverged from stock
        unsigned long g_transitionWrites = 0;   // SehWriteNextState succeeded
        unsigned long g_doSlideCalls = 0;       // DoSlide primitive invoked
        unsigned long g_divergences = 0;

        const wchar_t* StateName(int s)
        {
            switch (s)
            {
            case StateNone: return L"none";
            case StateApproach: return L"approach";
            case StateUnstuck: return L"unstuck";
            case StateFollow: return L"follow";
            case StateBlast: return L"blast";
            case StateWait: return L"wait";
            case StateSlide: return L"slide";
            case StateStand: return L"stand";
            case StateFlee: return L"flee";
            case StateBlastHold: return L"blasthold";
            case StateTravel: return L"travel";
            case StateFollowTravel: return L"followtravel";
            case StateDone: return L"done";
            default: return L"?";
            }
        }

        void LogDivergence(const uint8_t* task, const AttackFacts& facts,
                           const Bz14Decision& decision)
        {
            ++g_divergences;
            if (g_traceBudget <= 0)
                return;
            const long remaining = InterlockedDecrement(&g_traceBudget);
            if (remaining < 0)
                return;
            Log(L"[BZ14] task=0x%08X st=%s stock=%s policy=%s "
                L"d2=%.0f rng2=%.0f aTH=%s enemy=%d sac=%s arr=%s\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(task)),
                StateName(facts.curState),
                StateName(facts.stockNextState),
                decision.kind == Bz14Decision::Stay ||
                        decision.kind == Bz14Decision::StayButRunSlide
                    ? L"stay"
                    : StateName(decision.targetState),
                static_cast<double>(facts.distSq),
                static_cast<double>(facts.rangeSq),
                facts.ableToHit ? L"y" : L"n",
                facts.enemyTaskState,
                facts.sidewaysAndClose ? L"y" : L"n",
                facts.slideArrived ? L"y" : L"n");
        }

        // Applies the verdict for non-slide states. Returns true when a
        // recorded transition was successfully rewritten.
        bool ApplySimple(uint8_t* task, const AttackFacts& f)
        {
            const Bz14Decision d = DecideAttackTick(f);
            if (Bz14Defer(d))
                return false;
            LogDivergence(task, f, d);
            if (!PolicyApplyModeRequested())
                return false;
            ++g_overrideAttempts;
            if (SehWriteNextState(task, d.targetState))
            {
                ++g_transitionWrites;
                return true;
            }
            return false;
        }

        // Slide-state evaluation: needs SaC / enemy activity / arrival.
        // Each input records its availability; the pure policy defers on any
        // unknown it would otherwise have to guess about.
        bool ApplySlide(uint8_t* task, AttackFacts f, uint8_t* craft,
                        uint8_t* him)
        {
            f.enemyTaskStateValid =
                TryEnemyActivityState(him, f.enemyTaskState);
            if (!f.enemyTaskStateValid)
            {
                // Keep -1 purely as the logged placeholder; the policy never
                // consumes it while enemyTaskStateValid is false.
                f.enemyTaskState = -1;
            }

            // Success and value are distinct now: an unreadable predicate is
            // not a false predicate (fail-closed, PR #57 review).
            f.sidewaysAndCloseValid =
                TrySidewaysAndCloseValue(craft, him, f.sidewaysAndClose);

            float fx = 0.0f, fy = 0.0f, fz = 0.0f;
            f.slideArrivedValid =
                SehReadFloat(task, kTaskForceVec, fx) &&
                SehReadFloat(task, kTaskForceVec + 4, fy) &&
                SehReadFloat(task, kTaskForceVec + 8, fz);
            if (f.slideArrivedValid)
            {
                f.slideArrived =
                    std::sqrt(fx * fx + fy * fy + fz * fz) < kSlideArriveLen;
            }

            const Bz14Decision d = DecideAttackTick(f);
            if (Bz14Defer(d))
                return false;
            LogDivergence(task, f, d);
            if (!PolicyApplyModeRequested())
                return false;

            ++g_overrideAttempts;
            if (d.kind == Bz14Decision::StayButRunSlide)
            {
                // Stock skipped its DoSlide this tick; run the identical
                // primitive now and honor the 1.4 arrival rule (< 5 -> 10).
                if (TryRunDoSlide(task))
                    ++g_doSlideCalls;
                float ax = 0.0f, ay = 0.0f, az = 0.0f;
                bool arrived = false;
                if (SehReadFloat(task, kTaskForceVec, ax) &&
                    SehReadFloat(task, kTaskForceVec + 4, ay) &&
                    SehReadFloat(task, kTaskForceVec + 8, az))
                {
                    arrived = std::sqrt(ax * ax + ay * ay + az * az) <
                              kSlideArriveLen;
                }
                const int recorded =
                    arrived ? StateBlastHold : StateNone;
                if (SehWriteNextState(task, recorded))
                {
                    ++g_transitionWrites;
                    return true;
                }
                return false;
            }
            const int recorded =
                d.kind == Bz14Decision::Stay ? StateNone : d.targetState;
            if (SehWriteNextState(task, recorded))
            {
                ++g_transitionWrites;
                return true;
            }
            return false;
        }
    } // namespace

    void ConfigureBz14Tracing(long traceBudget, long tickBudget)
    {
        g_traceBudget = traceBudget > 0 ? traceBudget : 0;
        g_tickBudget = tickBudget > 0 ? tickBudget : 0;
    }

    void Bz14TickEntryLog(int sp, int haveHead, int curState, int nextState)
    {
        if (g_tickBudget <= 0)
            return;
        const long remaining = InterlockedDecrement(&g_tickBudget);
        if (remaining < 0)
            return;
        Log(L"[BZ14h] enter sp=%d head=%d st=%d nxt=%d\n",
            sp, haveHead, curState, nextState);
    }

    void CollectBz14HookPathStats(Bz14HookPathStats& out)
    {
        out.evaluations = g_evaluations;
        out.skipsNone = g_skipsNone;
        out.overrideAttempts = g_overrideAttempts;
        out.transitionWrites = g_transitionWrites;
        out.doSlideCalls = g_doSlideCalls;
        out.divergences = g_divergences;
    }

    // Returns true when a recorded-transition override was applied.
    bool EvaluateHookTick(uint8_t* task)
    {
        int cur = 0, stockNext = 0;
        uint8_t* craft = nullptr;
        uint8_t* him = nullptr;
        if (!SehReadTaskHead(task, cur, stockNext, craft, him))
            return false;

        if (stockNext == StateDone || stockNext == StateUnstuck)
        {
            ++g_skipsNone;
            return false; // aborts and stuck re-entry: identical in 1.4.
        }

        // D2c reachability (PR #57 review C1): stock recording NONE or cur
        // usually means "stay", which is identical in 1.4 - EXCEPT in the
        // slide state. Redux only routes an abeam-and-close target to STAND
        // when ableToHit latched; recovered 1.4 checked SidewaysAndClose
        // regardless of the firing solution, so its keep-sliding record
        // (NONE) can still diverge to STAND. Slide ticks therefore always
        // reach the pure policy, which defers by itself wherever the builds
        // agreed. All other states keep the original short-circuit.
        if ((stockNext == StateNone || stockNext == cur) &&
            cur != StateSlide)
        {
            ++g_skipsNone;
            return false;
        }

        ++g_evaluations;
        if (g_tickBudget > 0)
        {
            const long remaining = InterlockedDecrement(&g_tickBudget);
            if (remaining >= 0)
            {
                AttackFacts dbg;
                dbg.curState = cur;
                dbg.stockNextState = stockNext;
                SehReadAbleToHit(task, dbg.ableToHit);
                TryDistSqObjects(craft, him, dbg.distSq);
                SehReadFloat(task, kTaskRangeSq, dbg.rangeSq);
                Log(L"[BZ14t] eval st=%s stock=%s aTH=%d d2=%.0f rng2=%.0f\n",
                    StateName(cur), StateName(stockNext),
                    dbg.ableToHit ? 1 : 0,
                    static_cast<double>(dbg.distSq),
                    static_cast<double>(dbg.rangeSq));
            }
        }

        if (cur != StateApproach && cur != StateSlide &&
            cur != StateStand && cur != StateBlastHold)
            return false; // only these four states diverge.

        AttackFacts f;
        f.curState = cur;
        f.stockNextState = stockNext;
        // Success and value kept distinct: an unreadable aTH latch must not
        // read as "no firing solution" inside D5-style rules.
        f.ableToHitValid = SehReadAbleToHit(task, f.ableToHit);
        if (!TryDistSqObjects(craft, him, f.distSq))
            return false;
        if (!SehReadFloat(task, kTaskRangeSq, f.rangeSq))
            return false;

        float damageTime = 0.0f, entryTime = 0.0f;
        f.freshHitValid =
            SehReadFloat(craft, kCraftLastDamageTime, damageTime) &&
            SehReadFloat(task, kTaskStateEntry, entryTime);
        f.freshHit = f.freshHitValid && damageTime > entryTime;

        if (cur == StateSlide)
            return ApplySlide(task, f, craft, him);
        return ApplySimple(task, f);
    }

} // namespace bz14
