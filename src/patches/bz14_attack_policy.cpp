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
// The post-stock pipeline in bz14_attack_hookpath.cpp evaluates the
// recovered 1.4 conditions and, only where they differ, rewrites the
// recorded transition (0 = stay). Where stock's gating skipped its own
// DoSlide while 1.4 would keep sliding, the game's DoSlide primitive runs so
// a suppressed transition cannot stall the duel cycle. State-entry
// timestamps (+0x100) are temporarily freshened around the trampoline in
// states 7/9 so stock's 10 s / 3 s timer bounds never fire and never skip
// movement primitives; originals are restored before returning.
//
// QUARANTINED EXPERIMENT (2026-08-24 audit): live census proved the generic
// AttackTask::DoState @0x00478A50 executes for fighter/scout engagements
// (full 1.4 duel machine observed) but is never reached by the tested
// tank-family combat, which runs reduced family-specific task skeletons
// instead (recovery report §6.4). Enabling this layer therefore restores 1.4
// behavior for some unit families while others stay on Redux. It is
// developer-only research instrumentation:
//
//   OPENSHIM_LEGACY14_ATTACK=1        apply-mode (sim-affecting, SP only)
//   OPENSHIM_LEGACY14_ATTACK_SHADOW=1 measure-only mode; runs untouched
//                                     stock behavior, evaluates/logs the
//                                     hypothetical 1.4 decision, performs
//                                     no writes or sim-affecting calls
//   OPENSHIM_LEGACY14_EXCLUSIVE=1     with APPLY mode requested, reserves
//                                     the DoState site BEFORE AIKITE
//                                     installs (AIKITE skips its install
//                                     that session); nothing displaces an
//                                     installed detour at runtime
//   OPENSHIM_TRACE_AI_BZ14=<budget>   divergence logging budget
//   OPENSHIM_TRACE_AI_BZ14_TICKS=<n>  per-tick entry/eval logging budget
//
// There are deliberately NO openshim.ini keys for this feature: it must not
// look like a working user-facing restoration while it covers only some
// unit families. Telemetry distinguishes all four validation claims
// separately - byte-valid, hook-installed, hook-executing, and
// behavior-affecting derived from SUCCESSFUL mutations (transition writes,
// DoSlide invocations), never from attempts.
// ============================================================================

#include "bz14_attack_policy.h"
#include "bz14_attack_redux.h"

#include "bzr_options_ui.h"
#include "patcher.h"

#include <cstdlib>

namespace bz14
{
    namespace
    {
        using BZROpenShim::EnvFlagEnabled;
        using BZROpenShim::ExpectedBytesMatchAt;
        using BZROpenShim::InlineDetour32;
        using BZROpenShim::InstallInlineDetour32;
        using BZROpenShim::Log;

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
        bool g_bytesValidated = false;
        bool g_siteDeferralLogged = false;
        bool g_firstExecutionLogged = false;

        unsigned long g_hookCalls = 0;
        unsigned long g_timerFreshens = 0;      // entry-time freshened

        InlineDetour32 g_doStateDetour;

        void LoadConfig()
        {
            if (g_configLoaded)
                return;
            g_configLoaded = true;

            // Quarantined feature: environment-only activation. There are no
            // openshim.ini keys on purpose (see file header).
            bool enabled = EnvFlagEnabled("OPENSHIM_LEGACY14_ATTACK");
            bool shadow = EnvFlagEnabled("OPENSHIM_LEGACY14_ATTACK_SHADOW");

            // Apply wins over shadow; shadow evaluates without applying.
            g_shadowMode = shadow && !enabled;
            g_policyActive = enabled;

            char env[64] = {};
            long traceBudget = 0;
            if (GetEnvironmentVariableA("OPENSHIM_TRACE_AI_BZ14", env,
                                        sizeof(env)) > 0)
            {
                traceBudget = static_cast<long>(atol(env));
            }
            char tickEnv[64] = {};
            long tickBudget = 0;
            if (GetEnvironmentVariableA("OPENSHIM_TRACE_AI_BZ14_TICKS",
                                        tickEnv, sizeof(tickEnv)) > 0)
            {
                tickBudget = static_cast<long>(atol(tickEnv));
            }
            ConfigureBz14Tracing(traceBudget, tickBudget);
        }

        void __fastcall AttackTaskDoStateLegacy14Hook(void* task,
                                                      void* /*edx*/)
        {
            if (!g_doStateDetour.trampoline || !task)
                return;

            ++g_hookCalls;
            if (!g_firstExecutionLogged)
            {
                // First actual execution: this is the only proof that the
                // detour target is live code. Byte-valid + install logs prove
                // strictly less and must never be conflated with this.
                g_firstExecutionLogged = true;
                Log(L"[BZ14] hook-executing: first DoState entry observed "
                    L"task=0x%08X\n",
                    static_cast<uint32_t>(
                        reinterpret_cast<uintptr_t>(task)));
            }

            uint8_t* taskBytes = reinterpret_cast<uint8_t*>(task);
            const bool sp = SinglePlayerSession();
            const bool evaluate = (g_policyActive || g_shadowMode) && sp;
            int cur = 0, next0 = 0;
            uint8_t* craft = nullptr;
            uint8_t* him = nullptr;
            const bool haveHead =
                evaluate &&
                SehReadTaskHead(taskBytes, cur, next0, craft, him);
            Bz14TickEntryLog(sp ? 1 : 0, haveHead ? 1 : 0,
                             haveHead ? cur : -1, haveHead ? next0 : -1);
            if (!haveHead)
            {
                using FnDoState = void(__thiscall*)(void*);
                reinterpret_cast<FnDoState>(g_doStateDetour.trampoline)(task);
                return;
            }

            // Neutralize stock's 10 s slide / 3 s flee window for this tick
            // so the bounded branches cannot skip movement primitives.
            // APPLY MODE ONLY: shadow mode must observe untouched stock
            // behavior. Restoring the value after the trampoline does not
            // make this passive - stock would already have executed with
            // the synthetic timestamp - so measurement never writes here.
            //
            // Recovered-evidence note (PR #57 review C3): freshening here is
            // NOT a behavioral invention. It suppresses the 1.5+/Redux timer
            // caps for states where recovered evidence says 1.4 had none:
            // state 9 FLEE has no 3-second re-evaluation timeout in 1.4
            // (Redux added it), and state 7 SLIDE has no hard cap at all.
            // Removing either freshen would silently reintroduce a 1.5 rule.
            float savedEntry = 0.0f;
            bool entryFreshened = false;
            if (g_policyActive &&
                (cur == StateSlide || cur == StateFlee))
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
                            ++g_timerFreshens;
                        }
                    }
                }
            }

            using FnDoState = void(__thiscall*)(void*);
            reinterpret_cast<FnDoState>(g_doStateDetour.trampoline)(task);

            if (entryFreshened)
                SehWriteFloat(taskBytes, kTaskStateEntry, savedEntry);

            // Shared post-stock path with the integration tests: early-outs,
            // fact collection, pure policy, verdict application. SEH-wrapped
            // so a faulting game structure degrades to stock for this tick.
            __try
            {
                EvaluateHookTick(taskBytes);
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

    bool PolicyHookRequested()
    {
        LoadConfig();
        return g_policyActive || g_shadowMode;
    }

    bool PolicyApplyModeRequested()
    {
        LoadConfig();
        return g_policyActive;
    }

    bool InstallPolicyHookIfPossible(bool attackTaskSiteTaken)
    {
        LoadConfig();
        if (!g_policyActive && !g_shadowMode)
            return false;
        if (g_hookInstalled)
            return true;

        if (attackTaskSiteTaken)
        {
            // Another OpenShim feature already detours this entry. Runtime
            // displacement cannot be done safely (the owner's patch has
            // replaced the bytes we would validate and copy) and shadow
            // mode must stay behavior-neutral regardless, so both modes
            // defer. The exclusive path is decided at install order in
            // bzr_hooks.cpp: OPENSHIM_LEGACY14_EXCLUSIVE=1 leaves the site
            // free for us INSTEAD of AIKITE before anything installs.
            if (!g_siteDeferralLogged)
            {
                g_siteDeferralLogged = true;
                Log(L"[BZ14] AttackTask::DoState detour site owned by "
                    L"another OpenShim feature; legacy policy %s stays "
                    L"inert%s\n",
                    g_policyActive ? L"apply" : L"shadow",
                    g_policyActive
                        ? L" (set OPENSHIM_LEGACY14_EXCLUSIVE=1 to give "
                          L"it the site instead of AIKITE at next launch)"
                        : L"");
            }
            return false;
        }

        if (!ExpectedBytesMatchAt(kAttackTaskDoStateEntry,
                                  kDoStateExpectedBytes,
                                  sizeof(kDoStateExpectedBytes)))
        {
            Log(L"[BZ14] byte-valid=NO: AttackTask::DoState entry bytes "
                L"mismatch at 0x%08X; legacy attack policy unavailable\n",
                static_cast<uint32_t>(kAttackTaskDoStateEntry));
            return false;
        }
        g_bytesValidated = true;

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
        // Byte-valid and hook-installed are recorded here. Hook-executing is
        // proven by the first-entry log in the hook body; behavior-affecting
        // is derived from successful mutations (writes + DoSlide calls) at
        // shutdown.
        Log(L"[BZ14] byte-valid=YES hook-installed=%s at DoState=0x%08X "
            L"trampoline=0x%08X mode=%s (experimental: reaches live combat "
            L"only where generic AttackTask runs - fighter/scout proven; "
            L"tank families use other task bodies)\n",
            L"YES",
            static_cast<uint32_t>(kAttackTaskDoStateEntry),
            static_cast<uint32_t>(
                reinterpret_cast<uintptr_t>(g_doStateDetour.trampoline)),
            g_policyActive ? L"apply" : L"shadow");
        return true;
    }

    void ReportPolicyStats()
    {
        if (!g_configLoaded)
            LoadConfig();
        // One-shot session summary making all four validation claims
        // separately visible, with behavior-affecting derived from SUCCESSFUL
        // mutations only (attempted != applied).
        Bz14HookPathStats stats;
        CollectBz14HookPathStats(stats);
        const unsigned long successful =
            stats.transitionWrites + stats.doSlideCalls;
        Log(L"[BZ14] byte-valid=%s hook-installed=%s hook-calls=%lu "
            L"affecting=%s attempts=%lu writes=%lu doslide=%lu "
            L"freshens=%lu divergences=%lu mode=%s\n",
            g_bytesValidated ? L"yes" : L"no",
            g_hookInstalled ? L"yes" : L"no",
            g_hookCalls,
            successful > 0 ? L"yes" : L"no",
            stats.overrideAttempts,
            stats.transitionWrites,
            stats.doSlideCalls,
            g_timerFreshens,
            stats.divergences,
            g_policyActive ? L"apply"
                           : (g_shadowMode ? L"shadow" : L"off"));
    }

} // namespace bz14
