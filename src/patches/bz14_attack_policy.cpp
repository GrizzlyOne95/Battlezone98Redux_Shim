// ============================================================================
// bz14_attack_policy.cpp - Battlezone 1.4 AttackTask tactical-policy
// compatibility layer for Redux (GOG layout).
//
// Restores the provable 1.4-vs-1.5/Redux behavioral deltas inside
// AttackTask::DoState (0x00478A50) without replacing any Redux subsystem.
// Evidence: reverse_engineering/bz14_attacktask_recovery_20260824.md.
//
// Mechanics: stock DoState runs unmodified through a trampoline. In every
// divergent site stock performs the current state's behavior and only
// RECORDS nextState (+0x0C); UnitProcess::Execute applies any nonzero value
// afterwards (CleanState -> curState = nextState -> InitState, then clears).
// This hook evaluates the recovered 1.4 conditions after stock ran and, only
// where they differ, rewrites the recorded transition (0 = stay). Where
// stock's gating skipped its own DoSlide while 1.4 would keep sliding, the
// game's DoSlide primitive runs so a suppressed transition cannot stall the
// duel cycle. State-entry timestamps (+0x100) are temporarily freshened
// around the trampoline in states 7/9 so stock's 10 s / 3 s timer bounds
// never fire and never skip movement primitives; originals are restored
// before returning.
//
// Configuration (openshim.ini):
//   [AI] Legacy14AttackBehavior = 0|1  master switch, default off
//   [AI] Legacy14AttackShadow   = 0|1  evaluate + log both policies, apply
//                                      none (divergence measurement mode)
//   Env aliases: OPENSHIM_LEGACY14_ATTACK / OPENSHIM_LEGACY14_ATTACK_SHADOW
// Diagnostics: OPENSHIM_TRACE_AI_BZ14=<budget> enables divergence logging.
// ============================================================================

#include "bz14_attack_policy.h"
#include "bz14_attack_redux.h"

#include "bzr_options_ui.h"
#include "patcher.h"

#include <cstdlib>

namespace bz14
{
    bool OwnsAttackTaskDetour();
    bool InstallPolicyHookIfPossible();
    void ReportPolicyStats();

    namespace
    {
        using BZROpenShim::EnvFlagEnabled;
        using BZROpenShim::ExpectedBytesMatchAt;
        using BZROpenShim::InlineDetour32;
        using BZROpenShim::InstallInlineDetour32;
        using BZROpenShim::Log;
        using BZROpenShim::TryGetUserConfigBool;

        // GOG-layout anchors (byte-validated; fails closed on mismatch).
        constexpr uintptr_t kAttackTaskDoStateEntry = 0x00478A50;
        constexpr size_t kDoStateDetourLen = 9;
        const uint8_t kDoStateExpectedBytes[kDoStateDetourLen] = {
            0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x7C, 0x89, 0x4D, 0xFC};

        // UnitTask::DoSlide (state-7 primitive), SidewaysAndClose and the
        // game-time getter stock uses for its slide/flee windows.
        constexpr uintptr_t kUnitTaskDoSlide = 0x00606E20;
        constexpr uintptr_t kSidewaysAndClose = 0x004788D0;
        constexpr uintptr_t kGetGameTime = 0x00822D80;

        // Stock timer windows this layer neutralizes (values shared by all
        // three builds; only their existence differs).
        constexpr float kStockSlideWindow = 10.0f; // 1.5+ hard slide cap
        constexpr float kStockFleeWindow = 3.0f;   // 1.5+ flee re-evaluation

        // 1.4 slide-arrival force length (DoState case 7, _DAT_005E6E9C).
        constexpr float kSlideArriveLen = 5.0f;

        // Local player net id (0 = single-player). Like every other
        // simulation-affecting shim setting, the legacy attack behavior is
        // inert in network games regardless of configuration.
        constexpr uintptr_t kLocalPlayerNetIdAddr = 0x009180D4;

        bool SinglePlayerSession()
        {
            __try
            {
                return *reinterpret_cast<volatile const uint16_t*>(
                           kLocalPlayerNetIdAddr) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                // Unreadable game state: fail closed to stock behavior.
                return false;
            }
        }

        bool g_hookInstalled = false;
        bool g_ownsDetour = false;
        bool g_policyActive = false; // apply legacy transitions
        bool g_shadowMode = false;   // evaluate + log both, apply none
        bool g_configLoaded = false;

        long g_traceBudget = 0;
        long g_tickBudget = 0;
        unsigned long g_hookCalls = 0;
        unsigned long g_evaluations = 0;
        unsigned long g_skipsNone = 0;
        unsigned long g_overrides = 0;
        unsigned long g_divergences = 0;

        InlineDetour32 g_doStateDetour;

        void LoadConfig()
        {
            if (g_configLoaded)
                return;
            g_configLoaded = true;

            bool enabled = false;
            bool shadow = false;
            // Tri-state reads: absent keys leave the defaults untouched.
            TryGetUserConfigBool("AI", "Legacy14AttackBehavior", enabled);
            TryGetUserConfigBool("AI", "Legacy14AttackShadow", shadow);
            if (EnvFlagEnabled("OPENSHIM_LEGACY14_ATTACK"))
                enabled = true;
            if (EnvFlagEnabled("OPENSHIM_LEGACY14_ATTACK_SHADOW"))
                shadow = true;

            // Apply wins over shadow; shadow evaluates without applying.
            g_shadowMode = shadow && !enabled;
            g_policyActive = enabled;

            char env[64] = {};
            if (GetEnvironmentVariableA("OPENSHIM_TRACE_AI_BZ14", env,
                                        sizeof(env)) > 0)
            {
                const long budget = static_cast<long>(atol(env));
                g_traceBudget = budget > 0 ? budget : 0;
            }
            char tickEnv[64] = {};
            if (GetEnvironmentVariableA("OPENSHIM_TRACE_AI_BZ14_TICKS",
                                        tickEnv, sizeof(tickEnv)) > 0)
            {
                const long budget = static_cast<long>(atol(tickEnv));
                g_tickBudget = budget > 0 ? budget : 0;
            }
        }

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
        // recorded transition was rewritten.
        bool ApplySimple(uint8_t* task, const AttackFacts& f)
        {
            const Bz14Decision d = DecideAttackTick(f);
            if (Bz14Defer(d))
                return false;
            LogDivergence(task, f, d);
            if (!g_policyActive)
                return false;
            ++g_overrides;
            return SehWriteNextState(task, d.targetState);
        }

        // Slide-state evaluation: needs SaC / enemy activity / arrival.
        bool ApplySlide(uint8_t* task, AttackFacts f, uint8_t* craft,
                        uint8_t* him)
        {
            if (!TryEnemyActivityState(him, f.enemyTaskState))
                f.enemyTaskState = -1;
            // Unavailable activity state reads as non-engaged: 1.4 kept
            // sliding unless SaC fired; genuine arrivals are still honored
            // via the force-length test below.
            f.sidewaysAndClose = TrySidewaysAndClose(craft, him);

            float fx = 0.0f, fy = 0.0f, fz = 0.0f;
            if (SehReadFloat(task, kTaskForceVec, fx) &&
                SehReadFloat(task, kTaskForceVec + 4, fy) &&
                SehReadFloat(task, kTaskForceVec + 8, fz))
            {
                f.slideArrived =
                    std::sqrt(fx * fx + fy * fy + fz * fz) < kSlideArriveLen;
            }

            const Bz14Decision d = DecideAttackTick(f);
            if (Bz14Defer(d))
                return false;
            LogDivergence(task, f, d);
            if (!g_policyActive)
                return false;

            ++g_overrides;
            if (d.kind == Bz14Decision::StayButRunSlide)
            {
                // Stock skipped its DoSlide this tick; run the identical
                // primitive now and honor the 1.4 arrival rule (< 5 -> 10).
                TryRunDoSlide(task);
                float ax = 0.0f, ay = 0.0f, az = 0.0f;
                bool arrived = false;
                if (SehReadFloat(task, kTaskForceVec, ax) &&
                    SehReadFloat(task, kTaskForceVec + 4, ay) &&
                    SehReadFloat(task, kTaskForceVec + 8, az))
                {
                    arrived = std::sqrt(ax * ax + ay * ay + az * az) <
                              kSlideArriveLen;
                }
                return SehWriteNextState(
                    task, arrived ? StateBlastHold : StateNone);
            }
            return SehWriteNextState(
                task,
                d.kind == Bz14Decision::Stay ? StateNone : d.targetState);
        }

        // Returns true when a recorded-transition override was applied.
        bool EvaluateAndApply(uint8_t* task)
        {
            int cur = 0, stockNext = 0;
            uint8_t* craft = nullptr;
            uint8_t* him = nullptr;
            if (!SehReadTaskHead(task, cur, stockNext, craft, him))
                return false;

            if (stockNext == StateNone || stockNext == StateDone ||
                stockNext == cur || stockNext == StateUnstuck)
            {
                ++g_skipsNone;
                return false; // stays, aborts, stuck and re-entry requests:
                              // identical in 1.4, nothing to compare.
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
            SehReadAbleToHit(task, f.ableToHit);
            if (!TryDistSqObjects(craft, him, f.distSq))
                return false;
            if (!SehReadFloat(task, kTaskRangeSq, f.rangeSq))
                return false;

            float damageTime = 0.0f, entryTime = 0.0f;
            const bool haveTimes =
                SehReadFloat(craft, kCraftLastDamageTime, damageTime) &&
                SehReadFloat(task, kTaskStateEntry, entryTime);
            f.freshHit = haveTimes && damageTime > entryTime;

            if (cur == StateSlide)
                return ApplySlide(task, f, craft, him);
            return ApplySimple(task, f);
        }

        void __fastcall AttackTaskDoStateLegacy14Hook(void* task,
                                                      void* /*edx*/)
        {
            if (!g_doStateDetour.trampoline || !task)
                return;

            ++g_hookCalls;

            uint8_t* taskBytes = reinterpret_cast<uint8_t*>(task);
            const bool sp = SinglePlayerSession();
            const bool evaluate = (g_policyActive || g_shadowMode) && sp;
            int cur = 0, next0 = 0;
            uint8_t* craft = nullptr;
            uint8_t* him = nullptr;
            const bool haveHead =
                evaluate &&
                SehReadTaskHead(taskBytes, cur, next0, craft, him);
            if (g_tickBudget > 0)
            {
                const long remaining = InterlockedDecrement(&g_tickBudget);
                if (remaining >= 0)
                    Log(L"[BZ14h] enter sp=%d head=%d st=%d nxt=%d\n",
                        sp ? 1 : 0, haveHead ? 1 : 0,
                        haveHead ? cur : -1, haveHead ? next0 : -1);
            }

            // Neutralize stock's 10 s slide / 3 s flee window for this tick
            // so the bounded branches cannot skip movement primitives.
            float savedEntry = 0.0f;
            bool entryFreshened = false;
            if (haveHead && (cur == StateSlide || cur == StateFlee))
            {
                float entry = 0.0f;
                if (SehReadFloat(taskBytes, kTaskStateEntry, entry))
                {
                    const float bound = cur == StateSlide
                                            ? kStockSlideWindow
                                            : kStockFleeWindow;
                    const float now = GameTime();
                    if (now > entry + bound)
                    {
                        if (SehWriteFloat(taskBytes, kTaskStateEntry,
                                          now - bound * 0.5f))
                        {
                            savedEntry = entry;
                            entryFreshened = true;
                        }
                    }
                }
            }

            using FnDoState = void(__thiscall*)(void*);
            reinterpret_cast<FnDoState>(g_doStateDetour.trampoline)(task);

            if (entryFreshened)
                SehWriteFloat(taskBytes, kTaskStateEntry, savedEntry);

            if (!haveHead)
                return;

            __try
            {
                EvaluateAndApply(taskBytes);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }
    } // namespace

    bool OwnsAttackTaskDetour()
    {
        LoadConfig();
        return g_ownsDetour;
    }

    bool InstallPolicyHookIfPossible()
    {
        LoadConfig();
        if (!g_policyActive && !g_shadowMode)
            return false;
        if (g_hookInstalled)
            return true;

        if (!ExpectedBytesMatchAt(kAttackTaskDoStateEntry,
                                  kDoStateExpectedBytes,
                                  sizeof(kDoStateExpectedBytes)))
        {
            Log(L"[BZ14] AttackTask::DoState entry bytes mismatch at 0x%08X; "
                L"legacy attack policy unavailable\n",
                static_cast<uint32_t>(kAttackTaskDoStateEntry));
            return false;
        }

        g_GetTime = reinterpret_cast<FnGetTime>(kGetGameTime);
        g_DoSlide = reinterpret_cast<FnDoSlide>(kUnitTaskDoSlide);
        g_SaC = reinterpret_cast<FnSaC>(kSidewaysAndClose);

        if (!InstallInlineDetour32(g_doStateDetour, kAttackTaskDoStateEntry,
                                   reinterpret_cast<void*>(
                                       AttackTaskDoStateLegacy14Hook),
                                   kDoStateDetourLen, kDoStateExpectedBytes,
                                   sizeof(kDoStateExpectedBytes)))
        {
            Log(L"[BZ14] Failed installing AttackTask::DoState hook at "
                L"0x%08X\n",
                static_cast<uint32_t>(kAttackTaskDoStateEntry));
            return false;
        }

        g_hookInstalled = true;
        g_ownsDetour = true;
        Log(L"[BZ14] Legacy 1.4 attack policy %s at DoState=0x%08X "
            L"trampoline=0x%08X\n",
            g_policyActive ? L"ENABLED" : L"SHADOW",
            static_cast<uint32_t>(kAttackTaskDoStateEntry),
            static_cast<uint32_t>(
                reinterpret_cast<uintptr_t>(g_doStateDetour.trampoline)));
        return true;
    }

    void ReportPolicyStats()
    {
        if (!g_hookInstalled)
            return;
        Log(L"[BZ14] ticks=%lu overrides=%lu divergences=%lu mode=%s\n",
            g_hookCalls, g_overrides, g_divergences,
            g_policyActive ? L"apply"
                           : (g_shadowMode ? L"shadow" : L"off"));
    }

} // namespace bz14
