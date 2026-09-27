// ai_weapon_mask.cpp
// BZR Open Shim - AI weapon-mask hardpoint selection (WMASK): artillery and
// minelayer selection at the point of use, the synchronized volley, their
// reconcilers, and the retired carrier-bias helpers and inert bridge
// setters kept only as symbols, split out of bzr_hooks.cpp.
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
#include "render_queue_trace.h"
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
    namespace Hooks
    {
        // Configured value AND'd with the single-player gate. Every call
        // redirect stays installed either way; when the matching flag is false
        // each one passes straight through to the stock engine routine, so the
        // observable behaviour is byte-for-byte stock.
        static bool g_AiWeaponMaskArtilleryActive = false;

        static bool g_AiWeaponMaskMinelayerActive = false;

        void RefreshAiWeaponMaskArtilleryState()
        {
            g_AiWeaponMaskArtilleryActive =
                g_AiWeaponMaskArtilleryEnabled && ReadLocalPlayerNetIdValue() == 0;
        }

        void RevertAiWeaponMaskArtilleryToBaseline()
        {
            g_AiWeaponMaskArtilleryEnabled = kAiWeaponMaskArtilleryEnabledDefault;
            g_AiWeaponMaskArtilleryActive = false;
        }

        void RefreshAiWeaponMaskMinelayerState()
        {
            g_AiWeaponMaskMinelayerActive =
                g_AiWeaponMaskMinelayerEnabled && ReadLocalPlayerNetIdValue() == 0;
        }

        void RevertAiWeaponMaskMinelayerToBaseline()
        {
            g_AiWeaponMaskMinelayerEnabled = kAiWeaponMaskMinelayerEnabledDefault;
            g_AiWeaponMaskMinelayerActive = false;
        }
    }

    using namespace Hooks;

    bool SetHowitzerVolleyEnabledFromBridge(bool enabled)
    {
        g_HowitzerVolleyEnabled = false;
        if (enabled)
        {
            Log(L"[MISSIONHOOK] howitzer volley override requested but unavailable; unsafe ArtilleryProcess::DoAttack replay remains disabled\n");
            return false;
        }

        Log(L"[MISSIONHOOK] howitzer volley override disabled\n");
        return true;
    }

    bool SetWeaponMaskCarrierBiasEnabledFromBridge(bool enabled)
    {
        g_WeaponMaskCarrierBiasEnabled = enabled;
        Log(L"[MISSIONHOOK] weapon-mask carrier bias %hs\n", enabled ? "enabled" : "disabled");
        return true;
    }

    // Retired, and removed on 2026-09-27 together with its two getter hooks
    // (0x00417C80, 0x0046DD70), which only called it and then redid the stock
    // getter. It reordered Carrier::weapon[]/hardpoint[] and the
    // existant/selected/enabled bitfields to trick the stock "first slot" AI
    // into picking a different weapon. The setter above remains only because
    // OpenShimSetWeaponMaskCarrierBiasEnabled is a published export; the flag
    // it sets has no reader.
    //
    // It must not be revived as written. Three reasons, in order of severity:
    //
    //  1. It reached the carrier through kGameObjectCarrierOffset (0x198) and
    //     read the mask from kGameObjectWeaponMaskOffset (0x210). Both are the
    //     BZ 1.5 offsets. Redux is +0x1A0 and +0x218 -- confirmed from
    //     GameObject::GetWeaponMask (0x00462510), GameObject::SetWeaponMask
    //     (0x005C7450) and the ODF digit decode in the ctor (0x004DA0B0). The
    //     0x198 read yields a non-carrier pointer that this code then *wrote
    //     through*, which the __except cannot catch because a wrong-but-mapped
    //     pointer does not fault.
    //  2. The rawMask ^ 0x33333333 decode is spurious. Redux's weapon mask is a
    //     plain load; the obfuscated field at +0x210 is an unrelated 0..3 enum.
    //  3. Even with correct offsets, permuting carrier slots mutates simulation
    //     state that UpdateWeaponAim, GetRank, the HUD, save/load and the
    //     slot-ordered weapon hash at 0x005FED30 all read.
    //
    // The supported replacement selects the weapon at the point of use without
    // writing to the carrier -- see ResolveAiPreferredHardpoint below.

    namespace Hooks
    {
        // ------------------------------------------------------------------
        // AI weapon-mask hardpoint selection.
        //
        // NOT a regression fix. BZ 1.5 behaves exactly as stock Redux does:
        // ArtilleryProcess::DoAttack (1.5 0x0040D498 / Redux 0x00475B30) takes
        // the first existant weapon in slots 0..4, and LayMinesTask::DoArrived
        // (1.5 0x0041D5B2 / Redux 0x005128D0) hard-codes hardpoint 0 and
        // selected-mask 1. Neither reads weaponMask in either build. This is a
        // deliberate enhancement, off by default.
        //
        // Full derivation:
        // reverse_engineering/howitzer_minelayer_weapon_mask_root_cause_20260817.md
        // ------------------------------------------------------------------

        // Redux GameObject / Carrier layout. Do not substitute the 1.5 values;
        // GameObject gained eight bytes between the builds (0x198 -> 0x1A0,
        // 0x210 -> 0x218) and UnitProcess gained the same eight (0x2C -> 0x34).
        constexpr size_t kReduxGameObjectCarrierOffset = 0x1A0;
        constexpr size_t kReduxGameObjectWeaponMaskOffset = 0x218;
        constexpr size_t kReduxCarrierExistantOffset = 0x2C;
        // Proved from Carrier::GetWeapon (0x00417F60): `1 << slot` is tested
        // against +0x2C and the weapon is read from +0x18 + slot*4. The
        // selected/enabled pair at +0x30/+0x34 is proved from
        // Carrier::SetSelected (0x004D9880) and Carrier::TriggerSelected
        // (0x00511FC0), which fires every bit of `selected & enabled`.
        constexpr size_t kReduxCarrierWeaponArrayOffset = 0x18;
        constexpr size_t kReduxCarrierSelectedOffset = 0x30;
        constexpr size_t kReduxCarrierEnabledOffset = 0x34;
        constexpr size_t kReduxUnitProcessMeOffset = 0x34;
        constexpr size_t kReduxLayMinesTaskMeOffset = 0x10;

        constexpr uintptr_t kReduxCarrierGetWeaponAddr = 0x00417F60;
        constexpr uintptr_t kReduxCarrierSetSelectedAddr = 0x004D9880;

        // Both are __thiscall: `this` in ecx, one stack argument, callee-cleaned.
        // __fastcall with an ignored second parameter is the exact same ABI.
        using FnCarrierGetWeaponThiscall = void* (__fastcall*)(void*, void*, int);
        using FnCarrierSetSelectedThiscall = void (__fastcall*)(void*, void*, uint32_t);

        static volatile long g_WMaskArtilleryLogBudget = 200;
        static volatile long g_WMaskLayMinesLogBudget = 200;

        // Returns the hardpoint the AI should prefer, or -1 to leave stock
        // behaviour completely untouched.
        //
        // The rule is lowest_set_bit(weaponMask & existant). With the default
        // ODF mask 11111 (0x1F) that is precisely the first existant slot --
        // exactly what stock picks -- so this is a bit-exact no-op for every
        // unit that does not carry an explicit non-default mask.
        // The per-craft-type gate now lives at each call site, so both
        // resolvers answer purely from memory and never decide policy.
        int ResolveAiPreferredHardpoint(void* carrier, void* craft)
        {
            if (!carrier || !craft)
                return -1;

            __try
            {
                // The craft is recovered from the AI routine's stack frame, so
                // verify the round trip before trusting either pointer: the
                // craft we found must be the owner of the carrier we were
                // handed. Any frame drift in a future build fails this and
                // falls back to stock instead of reading arbitrary memory.
                const auto* craftBytes = reinterpret_cast<const uint8_t*>(craft);
                if (*reinterpret_cast<void* const*>(craftBytes + kReduxGameObjectCarrierOffset) != carrier)
                    return -1;

                const uint32_t mask =
                    *reinterpret_cast<const uint32_t*>(craftBytes + kReduxGameObjectWeaponMaskOffset);
                const uint32_t existant = *reinterpret_cast<const uint32_t*>(
                    reinterpret_cast<const uint8_t*>(carrier) + kReduxCarrierExistantOffset);

                const uint32_t desired = mask & existant & 0x1Fu;
                if (desired == 0)
                    return -1;  // mask selects nothing fitted -> stock

                for (int slot = 0; slot < 5; ++slot)
                {
                    if (desired & (1u << slot))
                        return slot;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            return -1;
        }

        void* ReadAiOwnerCraft(void* aiState, size_t meOffset)
        {
            if (!aiState)
                return nullptr;

            __try
            {
                return *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(aiState) + meOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        // The full set of hardpoints weaponMask names and the craft actually
        // carries: `weaponMask & existant`. Zero means "leave stock alone",
        // which covers a missing craft, a carrier that does not round-trip, a
        // mask that selects nothing fitted, and every read that faults.
        //
        // `enabled` is deliberately *not* folded in here. The artillery path
        // never consults it in stock, and Carrier::TriggerSelected applies it
        // itself on the lay-mines path, so ANDing it in twice would let a
        // transiently cleared bit silently shrink the volley.
        uint32_t ResolveAiVolleyMask(void* carrier, void* craft)
        {
            if (!carrier || !craft)
                return 0;

            __try
            {
                const auto* craftBytes = reinterpret_cast<const uint8_t*>(craft);
                if (*reinterpret_cast<void* const*>(craftBytes + kReduxGameObjectCarrierOffset) != carrier)
                    return 0;

                const uint32_t mask =
                    *reinterpret_cast<const uint32_t*>(craftBytes + kReduxGameObjectWeaponMaskOffset);
                const uint32_t existant = *reinterpret_cast<const uint32_t*>(
                    reinterpret_cast<const uint8_t*>(carrier) + kReduxCarrierExistantOffset);

                return mask & existant & 0x1Fu;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            return 0;
        }

        // Weapon::Trigger is vtable slot 2 (+8) -- the same slot
        // Carrier::TriggerSelected calls at 0x00512014 and the same slot the
        // four artillery sites call. It is a __thiscall taking no stack
        // argument, so __fastcall with an ignored edx is the identical ABI.
        bool TriggerWeaponObject(void* weapon)
        {
            if (!weapon)
                return false;

            __try
            {
                auto* vtbl = *reinterpret_cast<void***>(weapon);
                auto trigger = reinterpret_cast<void(__fastcall*)(void*, void*)>(vtbl[2]);
                trigger(weapon, nullptr);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            return false;
        }

        int FindCarrierSlotForWeapon(void* carrier, void* weapon)
        {
            if (!carrier || !weapon)
                return -1;

            __try
            {
                auto* slots = reinterpret_cast<void**>(
                    reinterpret_cast<uint8_t*>(carrier) + kReduxCarrierWeaponArrayOffset);
                for (int slot = 0; slot < 5; ++slot)
                {
                    if (slots[slot] == weapon)
                        return slot;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            return -1;
        }

        void* ReadCarrierWeaponSlot(void* carrier, int slot)
        {
            if (!carrier || slot < 0 || slot >= 5)
                return nullptr;

            __try
            {
                return reinterpret_cast<void**>(
                    reinterpret_cast<uint8_t*>(carrier) + kReduxCarrierWeaponArrayOffset)[slot];
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            return nullptr;
        }

        static volatile long g_WMaskVolleyLogBudget = 200;

        int PopCount5(uint32_t mask)
        {
            int count = 0;
            for (int bit = 0; bit < 5; ++bit)
                if (mask & (1u << bit))
                    ++count;
            return count;
        }
    }

    // Replaces the single `call Carrier::GetWeapon` inside the artillery slot
    // loop at 0x00475DDB. Stock walks slots 0..4 and keeps the first non-null
    // result; we answer the very first probe with the mask-preferred weapon so
    // the loop converges there immediately, and pass every other probe through
    // untouched.
    //
    // Instrumented to prove single-trigger semantics: for weaponMask=00010 the
    // preferred hardpoint is 1, but the loop must still invoke GetWeapon only
    // once with a non-null result (at slot 0 returning weapon 1) and terminate.
    // Returning the preferred weapon on every iteration (slot 1..4) would cause
    // the stock loop to trigger the same weapon 5 times or to advance past the
    // selected slot. The `slot != 0` guard ensures exactly one non-null return.
    void* __cdecl OpenShimArtillerySelectWeapon(void* carrier, int slot, void* process)
    {
        auto getWeapon = reinterpret_cast<FnCarrierGetWeaponThiscall>(kReduxCarrierGetWeaponAddr);

        if (!g_AiWeaponMaskArtilleryActive)
            return getWeapon(carrier, nullptr, slot);

        // Fast-path for non-zero loop indices: stock behavior, no mask logic.
        // This is the critical guard that prevents duplicate triggers: we only
        // substitute on the very first loop iteration (slot 0). Every later
        // iteration (1..4) is never reached when the first returns non-null,
        // but if it were (e.g. preferred was -1 and slot 0 was empty), the
        // stock scan must continue normally.
        if (slot != 0) {
            void* ret = getWeapon(carrier, nullptr, slot);
            if (InterlockedDecrement(&g_WMaskArtilleryLogBudget) >= 0) {
                Log(L"[WMASK][ARTY] slot=%d passthrough ret=%p craft=%p\n", slot, ret, ReadAiOwnerCraft(process, kReduxUnitProcessMeOffset));
            }
            return ret;
        }

        void* craft = ReadAiOwnerCraft(process, kReduxUnitProcessMeOffset);
        const int preferred = ResolveAiPreferredHardpoint(carrier, craft);
        const int selectedSlot = preferred >= 0 ? preferred : 0;
        void* ret = getWeapon(carrier, nullptr, selectedSlot);

        if (InterlockedDecrement(&g_WMaskArtilleryLogBudget) >= 0) {
            uint32_t mask = 0, existant = 0;
            __try {
                if (craft) mask = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(craft) + kReduxGameObjectWeaponMaskOffset);
                if (carrier) existant = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(carrier) + kReduxCarrierExistantOffset);
            } __except (EXCEPTION_EXECUTE_HANDLER) {}
            Log(L"[WMASK][ARTY] loop0 slot=%d pref=%d sel=%d mask=0x%02X exist=0x%02X ret=%p craft=%p carrier=%p\n",
                slot, preferred, selectedSlot, mask, existant, ret, craft, carrier);
        }
        return ret;
    }

    // Replaces the `call Carrier::GetWeapon` at 0x005128F6, whose slot argument
    // is the literal 0 pushed at 0x005128F1. Stock always passes 0; we
    // substitute the preferred slot when the mask selects one. Because stock
    // only ever calls this once per lay-mine arrival, returning preferred here
    // is a single substitution, not a per-iteration loop.
    void* __cdecl OpenShimLayMinesGetWeapon(void* carrier, int slot, void* task)
    {
        auto getWeapon = reinterpret_cast<FnCarrierGetWeaponThiscall>(kReduxCarrierGetWeaponAddr);

        if (!g_AiWeaponMaskMinelayerActive)
            return getWeapon(carrier, nullptr, slot);

        void* craft = ReadAiOwnerCraft(task, kReduxLayMinesTaskMeOffset);
        const int preferred = ResolveAiPreferredHardpoint(carrier, craft);
        const int sel = preferred >= 0 ? preferred : slot;
        void* ret = getWeapon(carrier, nullptr, sel);

        if (InterlockedDecrement(&g_WMaskLayMinesLogBudget) >= 0) {
            uint32_t mask = 0, existant = 0;
            __try {
                if (craft) mask = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(craft) + kReduxGameObjectWeaponMaskOffset);
                if (carrier) existant = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(carrier) + kReduxCarrierExistantOffset);
            } __except (EXCEPTION_EXECUTE_HANDLER) {}
            Log(L"[WMASK][MINE-GET] slot=%d pref=%d sel=%d mask=0x%02X exist=0x%02X ret=%p craft=%p\n",
                slot, preferred, sel, mask, existant, ret, craft);
        }
        return ret;
    }

    // Replaces the `call Carrier::SetSelected` at 0x00512921, whose mask
    // argument is the literal 1 pushed at 0x0051291C.
    //
    // SetSelected takes a MASK, not a hardpoint index. Proved from the routine
    // itself at 0x004D9880: its first act is `and ecx, [eax+0x2C]` -- the
    // argument is ANDed with the `existant` bitfield and the result stored to
    // `selected` (+0x30). An index would never be ANDed with a bitfield.
    //
    // Carrier::TriggerSelected (0x00511FC0), which DoArrived calls immediately
    // afterwards at 0x00512929, then loops slots 0..4 and triggers *every* bit
    // of `selected & enabled`. So the engine already supports a synchronized
    // multi-hardpoint drop natively: handing it the whole `weaponMask &
    // existant` set is all that is required, and every mine leaves in the same
    // frame from its own hardpoint.
    //
    // Stock pushes the literal 1 (== 1<<0), which is why stock lays exactly one
    // mine from hardpoint 0 regardless of the mask.
    void __cdecl OpenShimLayMinesSetSelected(void* carrier, uint32_t mask, void* task)
    {
        auto setSelected = reinterpret_cast<FnCarrierSetSelectedThiscall>(kReduxCarrierSetSelectedAddr);

        if (!g_AiWeaponMaskMinelayerActive)
        {
            setSelected(carrier, nullptr, mask);
            return;
        }

        void* craft = ReadAiOwnerCraft(task, kReduxLayMinesTaskMeOffset);
        const int preferred = ResolveAiPreferredHardpoint(carrier, craft);
        const uint32_t volleyMask = ResolveAiVolleyMask(carrier, craft);
        const uint32_t outMask = volleyMask != 0 ? volleyMask : mask;
        setSelected(carrier, nullptr, outMask);

        if (InterlockedDecrement(&g_WMaskLayMinesLogBudget) >= 0) {
            uint32_t inMask = mask, existant = 0, wMask = 0, selected = 0, enabled = 0;
            __try {
                if (craft) wMask = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(craft) + kReduxGameObjectWeaponMaskOffset);
                if (carrier) {
                    existant = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(carrier) + kReduxCarrierExistantOffset);
                    selected = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(carrier) + 0x30);
                    enabled = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(carrier) + 0x34);
                }
            } __except (EXCEPTION_EXECUTE_HANDLER) {}
            Log(L"[WMASK][MINE-SEL] inMask=0x%X outMask=0x%X volley=0x%02X bits=%d wMask=0x%02X exist=0x%02X sel=0x%X en=0x%X pref=%d craft=%p\n",
                inMask, outMask, volleyMask, PopCount5(outMask), wMask, existant, selected, enabled, preferred, craft);
        }
    }

    // Synchronized multi-hardpoint artillery volley.
    //
    // Replaces the four `mov r32,[weaponVtbl+8]; call r32` Trigger sites inside
    // ArtilleryProcess::DoAttack (0x00476AB5, 0x00476DAC, 0x00476F0B,
    // 0x00476F74). Each is exactly five bytes with the weapon already in ecx,
    // so a CALL rel32 fits the window with no instruction straddling.
    //
    // Why a second hook is needed at all: unlike the lay-mines path, DoAttack
    // does not go through Carrier::TriggerSelected. Its slot loop at 0x00475DAA
    // stops at the first non-null Carrier::GetWeapon result, stores that single
    // weapon at [ebp-0x254], and every downstream branch triggers that one
    // object directly. Choosing a different slot at the GetWeapon call site can
    // therefore only ever move which single mortar fires -- it can never fire
    // more than one. This hook adds the remaining masked hardpoints in the same
    // frame, using the aim solution DoAttack already computed.
    //
    // The four sites are mutually exclusive branches, so exactly one of them
    // runs per DoAttack and this executes at most once per firing cycle.
    //
    // Ordering: the weapon the loop selected always fires first and always
    // fires exactly once, so with the feature off, a mask that resolves to a
    // single bit, or any failed pointer round trip, the observable behaviour is
    // byte-for-byte stock.
    void __cdecl OpenShimArtilleryTriggerVolley(void* weapon, void* process)
    {
        if (!weapon)
            return;

        void* craft = nullptr;
        void* carrier = nullptr;
        uint32_t volleyMask = 0;
        int primarySlot = -1;

        if (g_AiWeaponMaskArtilleryActive)
        {
            craft = ReadAiOwnerCraft(process, kReduxUnitProcessMeOffset);
            carrier = ReadAiOwnerCraft(craft, kReduxGameObjectCarrierOffset);
            volleyMask = ResolveAiVolleyMask(carrier, craft);
            primarySlot = FindCarrierSlotForWeapon(carrier, weapon);
        }

        // Only extend the shot when the volley set is a clean superset of the
        // weapon DoAttack already picked. If the primary is not itself in the
        // mask the two hooks disagree about this craft, and the safe reading of
        // that is stock: fire the one weapon and nothing else.
        const bool volley =
            volleyMask != 0 &&
            primarySlot >= 0 &&
            (volleyMask & (1u << primarySlot)) != 0 &&
            PopCount5(volleyMask) > 1;

        const bool primaryFired = TriggerWeaponObject(weapon);

        int fired = primaryFired ? 1 : 0;
        if (volley)
        {
            for (int slot = 0; slot < 5; ++slot)
            {
                if (slot == primarySlot)
                    continue;
                if (!(volleyMask & (1u << slot)))
                    continue;

                void* extra = ReadCarrierWeaponSlot(carrier, slot);
                if (!extra || extra == weapon)
                    continue;

                if (TriggerWeaponObject(extra))
                    ++fired;
            }
        }

        if (InterlockedDecrement(&g_WMaskVolleyLogBudget) >= 0)
        {
            uint32_t wMask = 0, existant = 0, enabled = 0, selected = 0;
            __try
            {
                if (craft)
                    wMask = *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint8_t*>(craft) + kReduxGameObjectWeaponMaskOffset);
                if (carrier)
                {
                    auto* carrierBytes = reinterpret_cast<uint8_t*>(carrier);
                    existant = *reinterpret_cast<uint32_t*>(carrierBytes + kReduxCarrierExistantOffset);
                    selected = *reinterpret_cast<uint32_t*>(carrierBytes + kReduxCarrierSelectedOffset);
                    enabled = *reinterpret_cast<uint32_t*>(carrierBytes + kReduxCarrierEnabledOffset);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            Log(L"[WMASK][ARTY-VOLLEY] volley=%hs mask=0x%02X exist=0x%02X en=0x%02X sel=0x%02X "
                L"volleyMask=0x%02X primarySlot=%d triggers=%d weapon=%p carrier=%p craft=%p\n",
                volley ? "yes" : "no", wMask, existant, enabled, selected,
                volleyMask, primarySlot, fired, weapon, carrier, craft);
        }
    }
}
