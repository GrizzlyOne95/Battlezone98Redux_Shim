// perceived_team_reveal.cpp
// BZR Open Shim - perceived-team reveal fixes: the attack reveal on attack
// state entry and the owned-object reveal chain after damage (with the
// spray-emitter owner propagation and the SetDamageFlags probe that feed
// it), split out of bzr_hooks.cpp.
#include "bzr_hooks.h"
#include "bzr_object_layout.h"
#include "bzr_hooks_internal.h"
#include "engine_globals.h"
#include "game_state.h"
#include "openshim_ini.h"
#include "openshim_preset_migration.h"
#include "openshim_assets.h"
#include "terrain_proxy.h"
#include "terrain_tile_blend.h"
#include "bzr_options_ui.h"
#include "remembered_mesh_bounds_table.h"
#include "patches.h"
#include "patcher.h"
#include "fog_wake_feature.h"
#include "mp_vehicle_preview_fix.h"
#include "shim_log.h"
#include "x86_length.h"
#include "ogre_shader_cache.h"
#include "ogre_enhanced_light_selection.h"
#include "render_effect_intent.h"
#include "render_profile_runtime.h"
#include "native_ui.h"
#include "../engine/native_ui_validation.h"
#include "ogre_animation_profiler.h"
#include "ogre_profiler_algorithms.h"
#include "weapon_convergence.h"
#include "headlight_falloff.h"
#include "shadow_far_distance.h"
#include "sun_flash.h"
#include "chunk_batch_invalidation.h"
#include "ai_range_policy.h"
#include "lcbench_safety_policy.h"
#include "hook_engine.h"
#include "ui_performance.h"
#include "openshim_events.h"
#include "player_kill_trace.h"
#include "net_optimizer.h"
#include "pond_class_label.h"
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <array>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <intrin.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <exception>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <new>
#include <string>
#include <string_view>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    static bool TraceAttackRevealEnabled()
    {
        static const bool s_value = EnvFlagEnabled("OPENSHIM_TRACE_ATTACK_REVEAL");
        return s_value;
    }

    static bool TraceAttackRevealLegacyEnabled()
    {
        static const bool s_value = EnvFlagEnabled("BZR_TRACE_ATTACK_REVEAL");
        return s_value;
    }

    namespace Hooks
    {
        // GameObject::SetDamageFlags, and the obj76 -> GameObject accessor it
        // uses itself (0x00479F30). Both are read straight from the shipped
        // image; nothing about the DAMAGE layout is assumed beyond the two
        // fields SetDamageFlags itself reads ([0] damager, [1] dmg_source).
        constexpr uintptr_t kGogSetDamageFlagsAddr = 0x004DC130;

        // Configured value AND'd with the single-player gate. perceivedTeam is
        // simulation state -- it drives AI target selection, radar and the
        // satellite view -- so the reveal must never run in a network game, no
        // matter which source (INI, env, or the EXU bridge) turned it on.
        static bool g_AttackRevealActive = false;

        void RefreshAttackRevealState()
        {
            g_AttackRevealActive =
                g_AttackRevealEnabled && IsSinglePlayerSession();
        }

        void RevertAttackRevealToBaseline()
        {
            g_AttackRevealEnabled = kAttackRevealEnabledDefault;
            RefreshAttackRevealState();
        }

        void RefreshOwnedObjectRevealFixState()
        {
            g_OwnedObjectRevealFixActive =
                g_OwnedObjectRevealFixEnabled && IsSinglePlayerSession();
        }

        bool ShouldTraceOwnedObjectReveal()
        {
            return EnvFlagEnabled("OPENSHIM_TRACE_OWNED_OBJECT_REVEAL") ||
                   EnvFlagEnabled("BZR_TRACE_OWNED_OBJECT_REVEAL");
        }
        bool ShouldTraceAttackReveal()
        {
            return TraceAttackRevealEnabled() ||
                   TraceAttackRevealLegacyEnabled();
        }

        static void TraceAttackRevealEvent(const char* action,
                                           const char* reason,
                                           const char* sourceTag,
                                           void* processPtr,
                                           void* objectPtr,
                                           int perceivedTeam,
                                           int actualTeam)
        {
            if (!ShouldTraceAttackReveal())
                return;

            const long remaining = InterlockedDecrement(&g_AttackRevealTraceBudget);
            if (remaining < 0)
                return;

            Log(L"[AGGRO] trace remaining=%ld action=%hs reason=%hs source=%hs process=0x%08X object=0x%08X perceived=%d actual=%d enabled=%hs\n",
                remaining,
                action ? action : "unknown",
                reason ? reason : "unspecified",
                sourceTag ? sourceTag : "unknown",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(processPtr)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectPtr)),
                perceivedTeam,
                actualTeam,
                BoolText(g_AttackRevealActive));
        }

        void RevealProcessOwnerPerceivedTeam(void* processPtr, const char* sourceTag)
        {
            // g_AttackRevealActive, not g_AttackRevealEnabled: the reveal writes
            // perceivedTeam, which is simulation state, so it is hard-gated on
            // the net id like every other [SinglePlayer] feature. The three
            // DoSubTask detours that call this stay installed either way.
            if (!g_AttackRevealActive || !processPtr)
                return;

            __try
            {
                auto* processBytes = reinterpret_cast<uint8_t*>(processPtr);
                void* const objectPtr =
                    *reinterpret_cast<void**>(processBytes + kProcessOwnerObjectOffset);
                if (!objectPtr)
                {
                    TraceAttackRevealEvent("skip", "missing_owner", sourceTag, processPtr, nullptr, INT_MIN, INT_MIN);
                    return;
                }

                const int actualTeam = GetGameObjectTeamForLog(objectPtr);
                if (actualTeam < kGameTeamMin || actualTeam > kGameTeamMax)
                {
                    TraceAttackRevealEvent("skip", "team_out_of_range", sourceTag, processPtr, objectPtr, INT_MIN, actualTeam);
                    return;
                }

                auto* objectBytes = reinterpret_cast<uint8_t*>(objectPtr);
                // This wrote the ACTUAL team field until 2026-08-17, because
                // kGameObjectPerceivedTeamOffset was 0x174. actualTeam above is
                // read from that same +0x174, so the equality check below
                // always succeeded and the function returned "already_revealed"
                // every time without ever writing: the reveal has never once
                // run, despite defaulting to enabled.
                //
                // Now pointed at the real perceivedTeam. Stock only reveals an
                // attacker once its damage lands -- SetDamageFlags' tail does
                // damager->SetPerceivedTeam(damager->GetTeam()) in both 1.5 and
                // Redux -- so an enemy that fires and misses stays disguised.
                // Closing that is what this feature was added for, and it can
                // only do so by writing the field the satellite/radar actually
                // reads.
                int& perceivedTeam =
                    *reinterpret_cast<int*>(objectBytes + kGameObjectPerceivedTeamOffset);
                const int previousPerceivedTeam = perceivedTeam;
                if (previousPerceivedTeam == actualTeam)
                {
                    TraceAttackRevealEvent("noop", "already_revealed", sourceTag, processPtr, objectPtr, previousPerceivedTeam, actualTeam);
                    return;
                }

                perceivedTeam = actualTeam;
                TraceAttackRevealEvent("write", "revealed", sourceTag, processPtr, objectPtr, previousPerceivedTeam, actualTeam);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                TraceAttackRevealEvent("fault", "access_fault", sourceTag, processPtr, nullptr, INT_MIN, INT_MIN);
            }
        }

        struct DamageRevealSnapshot
        {
            void* gameObject = nullptr;
            int team = INT_MIN;
            int perceivedTeam = INT_MIN;
            char className[96] = {};
        };

        static void CaptureDamageRevealSnapshot(void* gameObject, DamageRevealSnapshot& out)
        {
            out.gameObject = gameObject;
            TryGetRttiClassName(gameObject, out.className, sizeof(out.className));
            uint8_t* base = nullptr;
            if (!TryGetGameObjectFieldBase(gameObject, base))
                return;
            __try
            {
                out.team = *reinterpret_cast<const int*>(base + kGameObjectActualTeamOffset);
                out.perceivedTeam = *reinterpret_cast<const int*>(base + kGameObjectPerceivedTeamOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }
    }

    using namespace Hooks;

    bool SetAttackRevealEnabledFromBridge(bool enabled)
    {
        RetryDeferredRuntimeHooks();
        g_AttackRevealEnabled = enabled;
        RefreshAttackRevealState();
        Log(L"[MISSIONHOOK] attack reveal %hs (active=%hs)\n",
            enabled ? "enabled" : "disabled",
            BoolText(g_AttackRevealActive));
        return true;
    }

    // Redirected from all four GameObject::SetDamageFlags call sites (the
    // *::DamageAlloc family). Read-only: it records state, calls the stock
    // function, and records state again. The confirmed owned-object fix now
    // also runs here after stock: direct hits remain stock, while a damager's
    // GameObject owner chain is revealed after the hit has actually landed.
    //
    // The question this exists to answer: when a disguised captured craft lands
    // a shot, which object does the reveal tail actually operate on? 1.5's
    // Explosion::Init puts the OWNER (the firing craft) in damage.damager while
    // damage.dmg_source is the explosion itself, so 1.5 reveals the craft. If
    // Redux instead reaches the reveal with an ordnance/explosion object, the
    // craft keeps its disguise -- which is BZ98ReduxBugTracker #38 ("Owned
    // objects will not cause your unit to lose PerceivedTeam").
    //
    // The class names come from RTTI, so the log says Craft vs Explosion vs
    // Ordnance outright rather than leaving it to be inferred from an address.
    static void TraceOwnedObjectReveal(const wchar_t* action,
                                       const wchar_t* kind,
                                       void* child,
                                       void* owner,
                                       int ownerHandle,
                                       int previousPerceivedTeam,
                                       int actualTeam,
                                       int depth)
    {
        if (!ShouldTraceOwnedObjectReveal())
            return;
        const long remaining = InterlockedDecrement(&g_OwnedObjectRevealTraceBudget);
        if (remaining < 0)
            return;
        Log(L"[OWNREVEAL] action=%ls kind=%ls child=0x%08X owner=0x%08X handle=0x%08X depth=%d pt=%d->%d active=%hs remaining=%ld\n",
            action ? action : L"unknown",
            kind ? kind : L"unknown",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(child)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(owner)),
            static_cast<uint32_t>(ownerHandle),
            depth,
            previousPerceivedTeam,
            actualTeam,
            BoolText(g_OwnedObjectRevealFixActive),
            remaining);
    }

    // Stock SetDamageFlags reveals only damage.damager. For a comet, deployed
    // soldier, mine or another owned GameObject, that is the child object, not
    // the craft whose GameObject::ownerHandle it carries. Walk the bounded,
    // validated handle chain and apply the same stock reveal operation to each
    // owner. This runs only for the non-collision branch stock treats as a shot.
    static void RevealOwnedObjectChainAfterDamage(void* victim, void* damage)
    {
        if (!g_OwnedObjectRevealFixActive || !victim || !damage)
            return;

        void* damagerObj76 = nullptr;
        void* sourceObj76 = nullptr;
        __try
        {
            auto* fields = reinterpret_cast<void* const*>(damage);
            damagerObj76 = fields[0];
            sourceObj76 = fields[1];
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return;
        }

        // Mirrors SetDamageFlags: equal non-null values are collision damage;
        // a null source is its no-source timing path. Neither reveals an owner.
        if (!damagerObj76 || !sourceObj76 || damagerObj76 == sourceObj76 ||
            !g_BzrFn_ResolveObj76GameObject)
            return;

        void* child = nullptr;
        __try
        {
            child = g_BzrFn_ResolveObj76GameObject(damagerObj76);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            child = nullptr;
        }
        if (!child || child == victim)
            return;

        // Eight levels is far beyond every stock ownership topology while
        // bounding corrupt/cyclic custom content. Each handle is generation-
        // checked by GameObjectFromHandleGog before any object field is read.
        void* visited[8] = {};
        size_t visitedCount = 0;
        void* current = child;
        for (int depth = 1; depth <= 8; ++depth)
        {
            uint8_t* currentBytes = nullptr;
            if (!TryGetGameObjectFieldBase(current, currentBytes))
                return;

            int ownerHandle = 0;
            __try
            {
                ownerHandle = *reinterpret_cast<const int*>(
                    currentBytes + kGameObjectOwnerHandleOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return;
            }
            if (ownerHandle == 0)
            {
                // Only the first hop is traced. Depth 1 with a zero owner is
                // the ordinary direct-fire case stock already handles, and is
                // also what a wrong owner offset looks like, so the live matrix
                // needs to see it; deeper hops would just repeat the terminator
                // once per chain and burn the budget.
                if (depth == 1)
                    TraceOwnedObjectReveal(L"stop", L"no-owner", child,
                                           nullptr, 0, 0, 0, depth);
                return;
            }

            void* owner = GameObjectFromHandleGog(ownerHandle);
            if (!owner || owner == current || owner == victim)
                return;
            for (size_t i = 0; i < visitedCount; ++i)
            {
                if (visited[i] == owner)
                    return;
            }
            visited[visitedCount++] = owner;

            uint8_t* ownerBytes = nullptr;
            if (!TryGetGameObjectFieldBase(owner, ownerBytes))
                return;

            __try
            {
                const int actualTeam = *reinterpret_cast<const int*>(
                    ownerBytes + kGameObjectActualTeamOffset);
                if (actualTeam < kGameTeamMin || actualTeam > kGameTeamMax)
                    return;
                int& perceivedTeam = *reinterpret_cast<int*>(
                    ownerBytes + kGameObjectPerceivedTeamOffset);
                const int previous = perceivedTeam;
                if (previous != actualTeam)
                {
                    perceivedTeam = actualTeam;
                    TraceOwnedObjectReveal(L"write", L"damage-owner", child,
                                           owner, ownerHandle, previous,
                                           actualTeam, depth);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return;
            }

            current = owner;
        }
    }

    // SprayBomb::Hit's class-build call at 0x005DB37F creates the deployed
    // SprayBuilding with ownerHandle=0. Its payload later records that emitter
    // as damage.damager, so the otherwise-general owner walk stops there. The
    // call-site wrapper below preserves the SprayBomb's verified +0xD8 creator
    // on the returned emitter. callerFrame is SprayBomb::Hit's EBP; its
    // local_1B0 is the live SprayBomb pointer in exact Redux 2.2.301.
    //
    // Both frame facts re-verified against the shipped GOG image 2026-09-19:
    //   0x005DB095 mov [ebp-0x1B0], ecx   -- SprayBomb `this` on entry
    //   0x005DB37F call 0x004E1190        -- the patched GameObjectClass::Build
    //   0x005DB384 mov [ebp-0x1D0], eax   -- the returned SprayBuilding
    // and the payload side that makes the emitter the damager at all:
    //   0x005DAB62 mov eax, [SprayBuilding+0xF4]   -- its obj76
    //   0x005DAB73 call 0x00586FF0                 -- OrdnanceClass::Build(mat, obj76)
    //   0x005DAB84 mov [payload+0x80], 0           -- bSend, the never-replicated marker
    // with Ordnance::Init storing that owner obj76 at +0xD8 (0x00585292) and
    // its handle at +0xDC (0x005852A4).
    static void* __cdecl PreserveSprayEmitterOwner(void* deployedEmitter,
                                                   void* callerFrame)
    {
        if (!g_OwnedObjectRevealFixActive || !deployedEmitter || !callerFrame ||
            !g_BzrFn_ResolveObj76GameObject)
            return deployedEmitter;

        void* sprayBomb = nullptr;
        void* creatorObj76 = nullptr;
        void* owner = nullptr;
        int ownerHandle = 0;
        int previousOwnerHandle = 0;
        __try
        {
            sprayBomb = *reinterpret_cast<void**>(
                reinterpret_cast<uint8_t*>(callerFrame) - 0x1B0);
            if (!sprayBomb)
                return deployedEmitter;
            creatorObj76 = *reinterpret_cast<void**>(
                reinterpret_cast<uint8_t*>(sprayBomb) + kOrdnanceOwnerObjOffset);
            if (!creatorObj76)
                return deployedEmitter;
            owner = g_BzrFn_ResolveObj76GameObject(creatorObj76);
            if (!owner || owner == deployedEmitter)
                return deployedEmitter;
            previousOwnerHandle = *reinterpret_cast<const int*>(
                reinterpret_cast<const uint8_t*>(deployedEmitter) +
                kGameObjectOwnerHandleOffset);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return deployedEmitter;
        }

        // Traced, not silent: a live run has to be able to tell "the call-site
        // patch never installed" apart from "it installed and declined", which
        // is exactly the distinction the 0x220 offset bug hid. A stock emitter
        // is built with a zero owner, so a non-zero read here means the field
        // is not the one this code thinks it is.
        if (previousOwnerHandle != 0)
        {
            TraceOwnedObjectReveal(L"skip", L"emitter-owner-not-empty",
                                   deployedEmitter, owner, previousOwnerHandle,
                                   0, 0, 0);
            return deployedEmitter;
        }
        if (!TryGetGameObjectHandleValue(owner, ownerHandle))
        {
            TraceOwnedObjectReveal(L"skip", L"emitter-owner-unhandled",
                                   deployedEmitter, owner, 0, 0, 0, 0);
            return deployedEmitter;
        }

        __try
        {
            *reinterpret_cast<int*>(
                reinterpret_cast<uint8_t*>(deployedEmitter) +
                kGameObjectOwnerHandleOffset) = ownerHandle;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return deployedEmitter;
        }

        TraceOwnedObjectReveal(L"link", L"splinter-emitter", deployedEmitter,
                               owner, ownerHandle, 0, 0, 0);
        return deployedEmitter;
    }

    void SetSprayEmitterBuildOriginal(void* original)
    {
        g_BzrFn_SprayEmitterBuildOriginal =
            reinterpret_cast<FnGameObjectClassBuild>(original);
    }

#if defined(_M_IX86)
    __declspec(naked) void* SprayEmitterBuildOwnerHook()
    {
        __asm
        {
            // Rebuild the original thiscall using copies of its five stack
            // arguments. Saving EBP exposes SprayBomb::Hit's frame to the
            // post-call helper without changing the game's caller frame.
            push ebp
            mov  ebp, esp
            sub  esp, 4
            mov  dword ptr [ebp - 4], ecx
            push dword ptr [ebp + 0x18]
            push dword ptr [ebp + 0x14]
            push dword ptr [ebp + 0x10]
            push dword ptr [ebp + 0x0C]
            push dword ptr [ebp + 0x08]
            mov  ecx, dword ptr [ebp - 4]
            call dword ptr [g_BzrFn_SprayEmitterBuildOriginal]
            push dword ptr [ebp]
            push eax
            call PreserveSprayEmitterOwner
            add  esp, 8
            mov  esp, ebp
            pop  ebp
            ret  0x14
        }
    }
#else
    void* SprayEmitterBuildOwnerHook()
    {
        return nullptr;
    }
#endif

    void __fastcall DamageRevealProbeHook(void* victim, void* /*edx*/, void* damage)
    {
        using FnSetDamageFlags = void(__fastcall*)(void*, void*, void*);
        auto stock = reinterpret_cast<FnSetDamageFlags>(kGogSetDamageFlagsAddr);

        // These four call sites are the engine's four damage handlers, shared
        // by single player and network games, so this is where the native event
        // layer gets its universal damage/kill attribution. Publishing is a
        // couple of guarded GetHandle calls plus a queue copy, and it
        // short-circuits entirely when nothing is subscribed.
        PublishDamageForCareerStatsFromProbe(victim, damage);

        if (!g_TraceDamageReveal || InterlockedDecrement(&g_DamageRevealTraceBudget) < 0)
        {
            if (stock) stock(victim, nullptr, damage);
            RevealOwnedObjectChainAfterDamage(victim, damage);
            return;
        }

        void* damagerObj76 = nullptr;
        void* sourceObj76 = nullptr;
        __try
        {
            auto* fields = reinterpret_cast<void* const*>(damage);
            damagerObj76 = fields[0];
            sourceObj76 = fields[1];
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }

        // Resolve obj76 -> GameObject with the engine's own accessor, the same
        // one SetDamageFlags uses, so no offset is assumed here.
        void* damagerGameObj = nullptr;
        void* sourceGameObj = nullptr;
        if (g_BzrFn_ResolveObj76GameObject)
        {
            __try
            {
                if (damagerObj76) damagerGameObj = g_BzrFn_ResolveObj76GameObject(damagerObj76);
                if (sourceObj76) sourceGameObj = g_BzrFn_ResolveObj76GameObject(sourceObj76);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        DamageRevealSnapshot victimBefore = {}, damagerBefore = {}, sourceBefore = {};
        CaptureDamageRevealSnapshot(victim, victimBefore);
        CaptureDamageRevealSnapshot(damagerGameObj, damagerBefore);
        CaptureDamageRevealSnapshot(sourceGameObj, sourceBefore);

        if (stock)
            stock(victim, nullptr, damage);
        RevealOwnedObjectChainAfterDamage(victim, damage);

        DamageRevealSnapshot victimAfter = {}, damagerAfter = {}, sourceAfter = {};
        CaptureDamageRevealSnapshot(victim, victimAfter);
        CaptureDamageRevealSnapshot(damagerGameObj, damagerAfter);
        CaptureDamageRevealSnapshot(sourceGameObj, sourceAfter);

        const bool collision = (damagerObj76 != nullptr) && (damagerObj76 == sourceObj76);
        Log(L"[DMGREVEAL] %hs victim=0x%08X(%hs) team=%d pt=%d->%d\n"
            L"[DMGREVEAL]   damager obj76=0x%08X gameObj=0x%08X(%hs) team=%d pt=%d->%d%hs\n"
            L"[DMGREVEAL]   source  obj76=0x%08X gameObj=0x%08X(%hs) team=%d pt=%d->%d\n",
            collision ? "collide" : "shot",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(victim)),
            victimBefore.className, victimBefore.team,
            victimBefore.perceivedTeam, victimAfter.perceivedTeam,
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(damagerObj76)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(damagerGameObj)),
            damagerBefore.className, damagerBefore.team,
            damagerBefore.perceivedTeam, damagerAfter.perceivedTeam,
            (damagerAfter.perceivedTeam != damagerBefore.perceivedTeam) ? "  <== REVEALED" : "",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceObj76)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceGameObj)),
            sourceBefore.className, sourceBefore.team,
            sourceBefore.perceivedTeam, sourceAfter.perceivedTeam);

        // Empirical owner chain: which fields of the damager point at another
        // live GameObject. If the damager is ordnance owned by the firing
        // craft, the craft shows up here as a concrete offset.
        LogArenaPointerFields(L"damager", damagerGameObj, 0x400);
        LogArenaPointerFields(L"source", sourceGameObj, 0x400);
    }

    void __cdecl RevealProcessOwnerPerceivedTeamOnAttackStateEntry(void* processPtr)
    {
        RevealProcessOwnerPerceivedTeam(processPtr, "attack_state_entry");
    }
}
