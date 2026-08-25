// ============================================================================
// bz14_attack_integration_tests.cpp - hook-path regression tests for the 1.4
// AttackTask compatibility layer.
//
// These drive bz14::EvaluateHookTick - the EXACT post-stock function the live
// DoState hook calls - against synthetic task/craft/target memory, with the
// three game-address-backed helpers (SidewaysAndClose, DoSlide) bound to
// deterministic stubs. This is the same path used by the actual hook, not a
// parallel reimplementation, so reachability fixes here prove reachability in
// gameplay.
//
// PR #57 review coverage:
//   C1: SLIDE + stockNext=NONE + SidewaysAndClose=true => STAND write is
//       reachable end-to-end (previously killed by the NONE early-out).
//   C2: every required runtime input has an explicit failure-injection case
//       proving apply mode leaves nextState untouched when evidence is
//       unavailable (fail-closed).
// ============================================================================

#include "bz14_attack_policy.h"
#include "bz14_attack_redux.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>

using namespace bz14;

// ---- test-provided seams ---------------------------------------------------
//
// The integration suite links the real hook-path TU but deliberately does NOT
// link the install/config TU or the shim logging backend. The two external
// seams are instead provided here with deterministic behavior:
//   - bz14::PolicyApplyModeRequested is test-controlled, so cases can prove
//     the shadow/deferred path writes nothing even when the pure policy would
//     override;
//   - BZROpenShim::Log discards (pipeline logging stays code-identical but
//     produces no output under test).

namespace bz14
{
    bool PolicyApplyModeRequested();
}

namespace
{
    // Test-controlled apply/shadow switch consumed via the seam above.
    bool g_applyMode = true;
}

namespace bz14
{
    bool PolicyApplyModeRequested()
    {
        return g_applyMode;
    }
}

namespace BZROpenShim
{
    void Log(const wchar_t* /*fmt*/, ...)
    {
    }
}

namespace
{
    int g_failures = 0;

    void Check(bool cond, const char* what)
    {
        if (!cond)
        {
            std::printf("  FAIL: %s\n", what);
            ++g_failures;
        }
    }

    // ---- deterministic helper stubs ---------------------------------------

    // Slot-12 self accessor stand-in: returns its this-pointer, exactly what
    // the engine's embedded interface accessor does.
    static void* __fastcall SlotSelfThunk(void* iface, void* /*edx*/)
    {
        return iface;
    }

    static int s_sacValue = 0;
    static bool __cdecl SaCStub(void* /*craftSelf*/, void* /*himSelf*/)
    {
        return s_sacValue != 0;
    }

    static unsigned long s_doSlideCalls = 0;
    // g_DoSlide is FnDoSlide (__thiscall); on MSVC x86 a zero-stack-arg
    // __thiscall is ABI-equivalent to __fastcall (this in ecx, edx unused),
    // so the thunk is reached through a reinterpret_cast exactly like the
    // engine-side install code binds raw addresses.
    static void __fastcall DoSlideThunk(void* /*task*/, void* /*edx*/)
    {
        ++s_doSlideCalls;
    }

    struct Bindings
    {
        Bindings()
        {
            g_SaC = &SaCStub;
            s_sacValue = 0;
            // g_DoSlide is FnDoSlide (__thiscall); bind through a matching
            // signature wrapper by casting the fastcall thunk is NOT valid,
            // so provide a real __thiscall via member-free trick: MSVC x86
            // __thiscall == __fastcall with hidden first arg in ecx only.
            // Use the thunk directly cast to FnDoSlide.
            g_DoSlide = reinterpret_cast<FnDoSlide>(&DoSlideThunk);
            s_doSlideCalls = 0;
        }
    };

    // ---- synthetic memory builders ----------------------------------------

    constexpr size_t kBufSize = 0x280;

    struct FakeBuffers
    {
        uint8_t task[kBufSize] = {};
        uint8_t craft[kBufSize] = {};
        uint8_t him[kBufSize] = {};
        void* craftVt[16] = {};
        void* himVt[16] = {};

        template <typename T>
        static void Poke(uint8_t* base, size_t offset, T value)
        {
            std::memcpy(base + offset, &value, sizeof(T));
        }

        void Build()
        {
            std::memset(task, 0, sizeof(task));
            std::memset(craft, 0, sizeof(craft));
            std::memset(him, 0, sizeof(him));

            // Embedded interface at obj+0x18 -> vptr -> slot 12 thunk.
            for (void*& slot : craftVt)
                slot = nullptr;
            craftVt[12] = reinterpret_cast<void*>(&SlotSelfThunk);
            Poke(craft, 0x18, static_cast<void*>(craftVt));
            himVt[12] = reinterpret_cast<void*>(&SlotSelfThunk);
            Poke(him, 0x18, static_cast<void*>(himVt));

            // Horizontal positions (doubles): craft at origin-ish,
            // target ~30 units east -> inside any slide ring.
            const double cx = 100.0, cz = 100.0;
            const double hx = 130.0, hz = 100.0;
            Poke(craft, 0x20 + 0x28, cx);
            Poke(craft, 0x20 + 0x28 + 0x10, cz);
            Poke(him, 0x20 + 0x28, hx);
            Poke(him, 0x20 + 0x28 + 0x10, hz);

            // Task head fields.
            Poke(task, 0x10, static_cast<void*>(craft));
            Poke(task, 0x18, static_cast<void*>(him));
            Poke(task, 0xA0, 2500.0f); // rangeSq = 50^2

            // Slide force vector far above arrival (<5) by default.
            Poke(task, 0x4C, 40.0f);
            Poke(task, 0x50, 0.0f);
            Poke(task, 0x54, 0.0f);
        }

        void SetStates(int cur, int next)
        {
            Poke(task, 0x08, cur);
            Poke(task, 0x0C, next);
        }

        void SetEnemyActivity(int state)
        {
            // self == obj+0x18; field at self+0x84 -> obj+0x9C.
            Poke(him, 0x18 + 0x84, state);
        }

        void BreakHimIface()
        {
            Poke(him, 0x18, static_cast<void*>(nullptr));
        }

        int NextState() const
        {
            int v = 0;
            std::memcpy(&v, task + 0x0C, sizeof(v));
            return v;
        }

        void SetAbleToHit(bool v)
        {
            Poke(task, 0xC4, static_cast<uint8_t>(v ? 1 : 0));
        }
    };

    Bz14HookPathStats Delta(const Bz14HookPathStats& before,
                            const Bz14HookPathStats& after)
    {
        Bz14HookPathStats d;
        d.evaluations = after.evaluations - before.evaluations;
        d.skipsNone = after.skipsNone - before.skipsNone;
        d.overrideAttempts = after.overrideAttempts - before.overrideAttempts;
        d.transitionWrites = after.transitionWrites - before.transitionWrites;
        d.doSlideCalls = after.doSlideCalls - before.doSlideCalls;
        d.divergences = after.divergences - before.divergences;
        return d;
    }
}

int main()
{
    ConfigureBz14Tracing(0, 0); // silent pipeline under test
    Bindings bindings;

    // ---- C1 regression: SLIDE + NONE + SaC => STAND through the hook path --
    {
        std::printf("IntegrationD2cReachability\n");
        FakeBuffers b;
        b.Build();
        b.SetStates(StateSlide, StateNone);
        b.SetEnemyActivity(StateWait); // readable, non-engaged in both builds
        b.SetAbleToHit(false);         // Redux kept sliding BECAUSE no aTH
        s_sacValue = 1;                // abeam and close

        Bz14HookPathStats before;
        CollectBz14HookPathStats(before);
        const bool changed = EvaluateHookTick(b.task);
        Bz14HookPathStats after;
        CollectBz14HookPathStats(after);
        const Bz14HookPathStats d = Delta(before, after);

        Check(changed, "override applied");
        Check(b.NextState() == StateStand, "nextState rewritten to STAND");
        Check(d.transitionWrites == 1, "one successful transition write");
        Check(d.overrideAttempts == 1, "exactly one attempt");
    }

    // ---- C2 failure injection: SidewaysAndClose unavailable ----------------
    {
        std::printf("FailClosedSacUnavailable\n");
        FakeBuffers b;
        b.Build();
        b.SetStates(StateSlide, StateNone);
        b.SetEnemyActivity(StateWait);
        b.SetAbleToHit(false);

        FnSaC saved = g_SaC;
        g_SaC = nullptr; // helper unbound = evidence unavailable
        Bz14HookPathStats before;
        CollectBz14HookPathStats(before);
        const bool changed = EvaluateHookTick(b.task);
        Bz14HookPathStats after;
        CollectBz14HookPathStats(after);
        g_SaC = saved;

        Check(!changed, "unavailable SaC defers");
        Check(b.NextState() == StateNone, "stock record untouched");
        Check(Delta(before, after).overrideAttempts == 0, "no attempt recorded");
    }

    // ---- C2 failure injection: enemy interface unreadable ------------------
    {
        std::printf("FailClosedEnemyUnreadable\n");
        FakeBuffers b;
        b.Build();
        b.SetStates(StateSlide, StateBlastHold);
        b.BreakHimIface(); // slot-12 chain faults -> enemy state unknown
        s_sacValue = 0;

        const bool changed = EvaluateHookTick(b.task);
        Check(!changed, "unreadable enemy state defers");
        Check(b.NextState() == StateBlastHold, "stock blast-hold untouched");
    }

    // ---- C2 failure injection: force vector unreadable ---------------------
    {
        std::printf("FailClosedForceVecUnreadable\n");
        FakeBuffers b;
        b.Build();
        b.SetStates(StateSlide, StateBlastHold);
        b.SetEnemyActivity(StateWait);
        s_sacValue = 0;
        b.Poke(b.task, 0x4C, std::nanf("")); // non-finite force -> read fails

        const bool changed = EvaluateHookTick(b.task);
        Check(!changed, "unreadable force vector defers");
        Check(b.NextState() == StateBlastHold, "stock record untouched");
    }

    // ---- early-out preserved for unrelated states --------------------------
    {
        std::printf("EarlyOutIntactForNonSlide\n");
        FakeBuffers b;
        b.Build();
        b.SetStates(StateApproach, StateNone);
        s_sacValue = 1;

        Bz14HookPathStats before;
        CollectBz14HookPathStats(before);
        const bool changed = EvaluateHookTick(b.task);
        Bz14HookPathStats after;
        CollectBz14HookPathStats(after);
        const Bz14HookPathStats d = Delta(before, after);

        Check(!changed, "approach stay still short-circuits");
        Check(d.skipsNone == 1, "counted as identical-outcome skip");
        Check(b.NextState() == StateNone, "no write performed");
    }

    // ---- StayButRunSlide path runs DoSlide through the same path -----------
    {
        std::printf("StayButRunSlideInvokesDoSlide\n");
        FakeBuffers b;
        b.Build();
        b.SetStates(StateSlide, StateBlastHold);
        b.SetEnemyActivity(StateBlastHold); // Redux-only engaged arm; 1.4: no
        s_sacValue = 0;                     // not abeam

        const bool changed = EvaluateHookTick(b.task);
        Check(changed, "keep-dueling override applied");
        Check(s_doSlideCalls == 1, "DoSlide primitive invoked once");
        Check(b.NextState() == StateNone, "recorded keep-sliding (NONE)");
    }

    // ---- shadow mode: divergence evaluated, nothing written ----------------
    {
        std::printf("ShadowModeWritesNothing\n");
        FakeBuffers b;
        b.Build();
        b.SetStates(StateSlide, StateNone);
        b.SetEnemyActivity(StateWait);
        b.SetAbleToHit(false);
        s_sacValue = 1;

        const bool savedApply = g_applyMode;
        g_applyMode = false;
        Bz14HookPathStats before;
        CollectBz14HookPathStats(before);
        const bool changed = EvaluateHookTick(b.task);
        Bz14HookPathStats after;
        CollectBz14HookPathStats(after);
        g_applyMode = savedApply;
        const Bz14HookPathStats d = Delta(before, after);

        Check(!changed, "shadow mode never reports an applied override");
        Check(b.NextState() == StateNone, "stock record untouched in shadow");
        Check(d.divergences == 1, "divergence still measured");
        Check(d.overrideAttempts == 0 && d.transitionWrites == 0,
              "no mutation attempted in shadow mode");
    }

    if (g_failures == 0)
    {
        std::printf("bz14_hook_integration_tests: all passed\n");
        return 0;
    }
    std::printf("bz14_hook_integration_tests: %d failure(s)\n", g_failures);
    return 1;
}
