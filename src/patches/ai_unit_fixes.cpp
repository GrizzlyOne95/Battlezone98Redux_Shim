// ai_unit_fixes.cpp
// BZR Open Shim - AI and unit fixes reached through engine call-site hooks:
// the AIP prerequisite resolve probe (diagnostic), AI multi-producer makers,
// the three pilot null-carrier guards and neutral attack orders, split out
// of bzr_hooks.cpp.
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
    static FnCarrierGetSelectedMask g_BzrFn_CarrierGetSelectedMask = nullptr;

    // Carrier::GetWeapon(int) at 0x00417F60 -- see FnCarrierGetWeapon above,
    // and kCarrierGetWeaponAddr, which already names this function. Resolved by
    // signature here rather than by literal address so the guard stands down
    // instead of hooking the wrong bytes if the build moves.
    static FnCarrierGetWeapon g_BzrFn_CarrierGetWeapon = nullptr;

    static FnTeamEnemyPInt g_BzrFn_ControlPanelEnemyP = nullptr;

    static FnPrereqWhatIs g_BzrFn_PrereqWhatIs = nullptr;

    static FnAiFindObjectClass g_BzrFn_AiFindObjectClass = nullptr;

    static FnAiUnitsInit g_BzrFn_AiUnitsInit = nullptr;

    static FnAiIsBuilding g_BzrFn_AiIsBuilding = nullptr;

    static FnAiClass2UnitType g_BzrFn_AiClass2UnitType = nullptr;

    static FnAiClass2BuildingType g_BzrFn_AiClass2BuildingType = nullptr;

    static FnAiGetPrereq g_BzrFn_AiGetPrereq = nullptr;

    using namespace Hooks;

    void SetPersonCarrierGetWeaponOriginal(void* target)
    {
        g_BzrFn_CarrierGetWeapon = reinterpret_cast<FnCarrierGetWeapon>(target);
    }

    void SetPersonCarrierGetSelectedOriginal(void* target)
    {
        g_BzrFn_CarrierGetSelectedMask =
            reinterpret_cast<FnCarrierGetSelectedMask>(target);
    }

    void SetControlPanelEnemyPOriginal(void* target)
    {
        g_BzrFn_ControlPanelEnemyP = reinterpret_cast<FnTeamEnemyPInt>(target);
    }

    void SetAipPrereqWhatIsOriginal(void* target)
    {
        g_BzrFn_PrereqWhatIs = reinterpret_cast<FnPrereqWhatIs>(target);
    }

    namespace Hooks
    {
        // PREREQ_WhatIs walks a flat table of 0x9C-byte entries. Each entry
        // carries a kind byte at +0x00 and a pointer to the underlying
        // unit/building type at +0x04; the type's ODF name sits at +0x14 for a
        // unit and +0x40 for a building. Rather than hard-code the two globals
        // that hold the table pointer and its length, read them back out of the
        // resolved function body, so a build whose data layout moved simply
        // fails the byte guard and skips the census.
        constexpr size_t kPrereqEntryStride = 0x9C;
        constexpr size_t kPrereqUnitNameOffset = 0x14;
        constexpr size_t kPrereqBuildingNameOffset = 0x40;
        constexpr int kPrereqCensusMaxEntries = 4096;

        bool TryReadPrereqTableGlobals(const uint8_t* fn,
                                       const int32_t*& outMaxAssigned,
                                       const uint8_t* const*& outTable)
        {
            outMaxAssigned = nullptr;
            outTable = nullptr;
            if (!fn)
                return false;

            // cmp ecx, ds:[PREREQ_maxassigned]  ->  3B 0D <disp32> at +27
            // mov eax, ds:[PREREQ_table]        ->  A1    <disp32> at +46
            if (fn[27] != 0x3B || fn[28] != 0x0D || fn[46] != 0xA1)
                return false;

            uint32_t maxAssignedAddr = 0;
            uint32_t tableAddr = 0;
            memcpy(&maxAssignedAddr, fn + 29, sizeof(maxAssignedAddr));
            memcpy(&tableAddr, fn + 47, sizeof(tableAddr));
            if (!maxAssignedAddr || !tableAddr)
                return false;

            outMaxAssigned = reinterpret_cast<const int32_t*>(maxAssignedAddr);
            outTable = reinterpret_cast<const uint8_t* const*>(tableAddr);
            return true;
        }

        // Dumps every name the strategic AI can resolve. This is the whole
        // point of the probe: an AIP item name that is absent here can never be
        // selected, because AIP_Load_Account discards the node at load time.
        void EmitPrereqUniverseCensus()
        {
            const int32_t* maxAssigned = nullptr;
            const uint8_t* const* table = nullptr;
            if (!TryReadPrereqTableGlobals(
                    reinterpret_cast<const uint8_t*>(g_BzrFn_PrereqWhatIs),
                    maxAssigned,
                    table))
            {
                Log(L"[AIPRES] prereq table globals not recognised in this build; "
                    L"census skipped\n");
                return;
            }

            int count = 0;
            const uint8_t* base = nullptr;
            __try
            {
                count = *maxAssigned;
                base = *table;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[AIPRES] prereq table unreadable; census skipped\n");
                return;
            }

            if (!base || count <= 1 || count > kPrereqCensusMaxEntries)
            {
                Log(L"[AIPRES] prereq universe not populated (count=%d table=%p)\n",
                    count, base);
                return;
            }

            Log(L"[AIPRES] prereq universe: count=%d\n", count - 1);
            for (int i = 1; i < count; ++i)
            {
                const uint8_t* entry = base + static_cast<size_t>(i) * kPrereqEntryStride;
                unsigned kind = 0xFFu;
                const char* name = nullptr;
                __try
                {
                    kind = entry[0];
                    const uint8_t* data = *reinterpret_cast<const uint8_t* const*>(entry + 4);
                    if (data)
                    {
                        if (kind == 0u)
                            name = reinterpret_cast<const char*>(data + kPrereqUnitNameOffset);
                        else if (kind == 1u)
                            name = reinterpret_cast<const char*>(data + kPrereqBuildingNameOffset);
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    name = nullptr;
                }

                Log(L"[AIPRES]   id=%d kind=%hs name='%hs'\n",
                    i,
                    kind == 0u ? "unit" : (kind == 1u ? "building" : "?"),
                    name ? name : "<unreadable>");
            }
        }
    }

    namespace Hooks
    {
        // Pure pass-through: the stock return value is handed back untouched
        // whether or not the trace is enabled, so no build decision moves.
        // `site` names which AIP loader asked, because a miss is discarded
        // differently in each (a construction-program node is dropped, a
        // matching entry is simply never matched).
        uint16_t AipPrereqWhatIsCore(const char* itemName, const wchar_t* site)
        {
            if (!g_BzrFn_PrereqWhatIs)
                return 0;

            const uint16_t resolved = g_BzrFn_PrereqWhatIs(itemName);
            if (!g_AipResolveTraceEnabled)
                return resolved;

            if (InterlockedCompareExchange(&g_AipPrereqCensusEmitted, 1, 0) == 0)
                EmitPrereqUniverseCensus();

            if (InterlockedDecrement(&g_AipResolveTraceBudget) >= 0)
            {
                Log(L"[AIPRES] %s item='%hs' -> id=%u%s\n",
                    site,
                    itemName ? itemName : "<null>",
                    static_cast<unsigned>(resolved),
                    resolved == 0 ? L"  MISS (entry discarded)" : L"");
            }
            return resolved;
        }
    }

    // AIP_Load_Account: one call per unit_construction_program item. A zero
    // here means the node never reaches the account at all.
    uint16_t __cdecl AipPrereqWhatIsProbe(const char* itemName)
    {
        return AipPrereqWhatIsCore(itemName, L"account");
    }

    uint16_t __cdecl AipPrereqWhatIsProbeForceMatching(const char* itemName)
    {
        return AipPrereqWhatIsCore(itemName, L"force_matching");
    }

    uint16_t __cdecl AipPrereqWhatIsProbeBuildingMatching(const char* itemName)
    {
        return AipPrereqWhatIsCore(itemName, L"building_matching");
    }

    void SetAiFindObjectClassOriginal(void* t)
    { g_BzrFn_AiFindObjectClass = reinterpret_cast<FnAiFindObjectClass>(t); }
    void SetAiUnitsInitOriginal(void* t)
    { g_BzrFn_AiUnitsInit = reinterpret_cast<FnAiUnitsInit>(t); }
    void SetAiMakerHelperOriginals(void* isBuilding, void* class2Unit,
                                   void* class2Building, void* getPrereq)
    {
        g_BzrFn_AiIsBuilding = reinterpret_cast<FnAiIsBuilding>(isBuilding);
        g_BzrFn_AiClass2UnitType = reinterpret_cast<FnAiClass2UnitType>(class2Unit);
        g_BzrFn_AiClass2BuildingType = reinterpret_cast<FnAiClass2BuildingType>(class2Building);
        g_BzrFn_AiGetPrereq = reinterpret_cast<FnAiGetPrereq>(getPrereq);
    }

    namespace Hooks
    {
        // makers[] is four ushorts wide in both type structs, and PREREQ_Init
        // copies all four into the prereq table behind a zero terminator that
        // PREREQ_CanThisMakeThat walks. So slots 1..3 are already consumed by
        // stock code; nothing but SetMaker's single write was stopping them
        // from being populated.
        constexpr size_t kAiMakersCount = 4;
        constexpr size_t kAiUnitTypeMakersOffset = 0x66;
        constexpr size_t kAiBuildingTypeMakersOffset = 0x16;

        uint16_t* AiMakersArrayFor(void* objClass)
        {
            if (!objClass || !g_BzrFn_AiIsBuilding ||
                !g_BzrFn_AiClass2UnitType || !g_BzrFn_AiClass2BuildingType)
                return nullptr;

            uint8_t* base = nullptr;
            size_t offset = 0;
            __try
            {
                if (g_BzrFn_AiIsBuilding(objClass) != 0)
                {
                    base = static_cast<uint8_t*>(g_BzrFn_AiClass2BuildingType(objClass, 0));
                    offset = kAiBuildingTypeMakersOffset;
                }
                else
                {
                    base = static_cast<uint8_t*>(g_BzrFn_AiClass2UnitType(objClass));
                    offset = kAiUnitTypeMakersOffset;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
            return base ? reinterpret_cast<uint16_t*>(base + offset) : nullptr;
        }

        // Appends one maker, keeping stock's first-writer-wins ordering in
        // slot 0 so PREREQ_Init's canmake flag is computed exactly as before.
        bool AiAppendMaker(void* objClass, uint16_t makerId)
        {
            uint16_t* makers = AiMakersArrayFor(objClass);
            if (!makers || makerId == 0)
                return false;

            __try
            {
                for (size_t i = 0; i < kAiMakersCount; ++i)
                {
                    if (makers[i] == makerId)
                        return false;       // already known, nothing to do
                    if (makers[i] == 0)
                    {
                        makers[i] = makerId;
                        return true;
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return false;                    // all four slots taken; leave stock
        }

        void AiApplyExtraMakers()
        {
            if (!g_BzrFn_AiGetPrereq)
                return;

            size_t applied = 0;
            for (const AiExtraMakerPair& pair : g_AiExtraMakerPairs)
            {
                uint16_t makerId = 0;
                __try
                {
                    makerId = g_BzrFn_AiGetPrereq(pair.buildClass);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    continue;
                }
                if (AiAppendMaker(pair.objClass, makerId))
                {
                    ++applied;
                    if (InterlockedDecrement(&g_AiMultiProducerMakerLogBudget) >= 0)
                    {
                        Log(L"[AIMAKER] objClass=%p gained maker prereq=%u from buildClass=%p\n",
                            pair.objClass, static_cast<unsigned>(makerId), pair.buildClass);
                    }
                }
            }
            Log(L"[AIMAKER] %zu extra producer/item pair(s) seen, %zu maker(s) added\n",
                g_AiExtraMakerPairs.size(), applied);
        }
    }

    // AddObjectClass's duplicate test. It matches on the built class alone, so
    // a true return with a non-null buildClass is exactly the case stock drops:
    // this producer can make this item, but the item is already spoken for.
    uint32_t __cdecl AiFindObjectClassCollectHook(void* objClass, void* buildClass)
    {
        if (!g_BzrFn_AiFindObjectClass)
            return 0;

        const uint32_t found = g_BzrFn_AiFindObjectClass(objClass, buildClass);
        if (g_AiMultiProducerMakersEnabled && (found & 0xFFu) != 0 &&
            objClass && buildClass && objClass != buildClass &&
            g_AiExtraMakerPairs.size() < 4096)
        {
            const bool known = std::any_of(
                g_AiExtraMakerPairs.begin(), g_AiExtraMakerPairs.end(),
                [objClass, buildClass](const AiExtraMakerPair& p) {
                    return p.objClass == objClass && p.buildClass == buildClass;
                });
            if (!known)
                g_AiExtraMakerPairs.push_back({ objClass, buildClass });
        }
        return found;
    }

    // Runs immediately after stock Units_Init has written makers[0] for every
    // pair the class list did accept, and before PREREQ_Init copies makers[]
    // into the prereq table.
    void __cdecl AiUnitsInitMultiMakerHook()
    {
        if (g_BzrFn_AiUnitsInit)
            g_BzrFn_AiUnitsInit();
        if (g_AiMultiProducerMakersEnabled && !g_AiExtraMakerPairs.empty())
            AiApplyExtraMakers();
        g_AiExtraMakerPairs.clear();
    }

    // Production patch: Pilot hardpoint ODF ordering crash — null-carrier guard.
    // What malformed state is possible: a pilot ODF that places weaponHard1/
    // weaponName1 outside [GameObjectClass] (e.g. inside a late CraftClass
    // section before PersonClass, after PersonClass, or reversed) is parsed
    // but does NOT allocate the Person's Carrier object. GameObject::GameObject
    // only allocates the carrier when weaponHard is non-empty in the
    // GameObjectClass data; misplaced keys are ignored, leaving Person+0x1A0
    // null. Stock 1.5 and Redux both then read it unconditionally.
    // Why the guard is required: Person::Simulate at 0x0059D340 calls
    // Carrier::GetSelected (0x00417F90, returns [this+0x30]) with that null
    // carrier. The call was observed 3/3 in lcbench pilot-ordering
    // (pcrft/paftr/prevs) as EIP 0x00417F9A reading [EAX+0x30] with EAX=0,
    // caller return 0x0059D771. The process dies on its first simulation
    // frame even though BuildObject succeeded.
    // Why mask=0 is preferable: the selected mask is only used to classify
    // the on-foot animation (which weapon is selected). A missing carrier is
    // semantically "no weapon selected" — mask 0. Returning 0 and continuing
    // Simulate preserves the real animation/state machine and avoids crashing
    // on trivial authoring errors. This is safer than early-returning from
    // Simulate or synthesising a carrier.
    uint32_t __fastcall PersonCarrierGetSelectedGuard(void* carrier, void* person)
    {
        if (carrier && g_BzrFn_CarrierGetSelectedMask)
            return g_BzrFn_CarrierGetSelectedMask(carrier);

        if (!carrier)
        {
            const uintptr_t objectKey = reinterpret_cast<uintptr_t>(person);
            if (g_PilotCarrierNullLoggedObjects.insert(objectKey).second)
            {
                Log(L"[PILOTSAFE] Person=%p has null carrier at +0x%X; "
                    L"using selectedMask=0 and continuing Person::Simulate\n",
                    person,
                    static_cast<unsigned>(kPersonCarrierOffset));
            }
        }

        return LcbenchSafetyPolicy::SelectedMaskForMissingCarrier();
    }

    // Production patch: the SECOND null-carrier crash site.
    //
    // PersonCarrierGetSelectedGuard above covers Carrier::GetSelected, which
    // Person::Simulate calls on Person+0x1A0. That is not the only accessor
    // reached through that pointer. A five-slot loop at 0x005A1362 does
    //
    //     for (i = 0; i < 5; i++)
    //         weapon = person->carrier->GetWeapon(i);   // carrier NOT checked
    //
    // and Carrier::GetWeapon (0x00417F60) faults on its own first instruction,
    // AND EAX,[ECX+0x2C], when that carrier is null -- the same malformed-ODF
    // state the sibling guard documents, on a different call site, so fixing
    // one left the other live.
    //
    // Found loading the Hell Gate II addon mission on GOG Redux 2.2.301: its
    // sshg01.odf is the player's own pilot and declares weaponHard1/weaponName1
    // under [CraftClass] instead of [GameObjectClass], so GameObject::GameObject
    // never allocates the Carrier. The mission reached "Playing" and died on the
    // first simulation frame, which is why it presented as an instant crash.
    //
    // Returning null is not a substitute value invented here: it is what the
    // callee itself returns for an empty hardpoint, and the caller stores the
    // result and branches on null immediately afterwards at 0x005A138D. A pilot
    // with no carrier genuinely has no weapon in any slot, so every slot reading
    // empty is the accurate answer as well as the safe one.
    void* __fastcall PersonCarrierGetWeaponGuard(void* carrier, void* /*edx*/, int slot)
    {
        if (carrier && g_BzrFn_CarrierGetWeapon)
            return g_BzrFn_CarrierGetWeapon(carrier, slot);

        if (!carrier)
        {
            const uintptr_t objectKey = reinterpret_cast<uintptr_t>(carrier);
            if (g_PilotCarrierNullLoggedObjects.insert(objectKey ^ 0x1u).second)
            {
                Log(L"[PILOTSAFE] null carrier at +0x%X in the weapon-slot loop; "
                    L"reporting slot %d empty and continuing. The pilot ODF most "
                    L"likely declares weaponHard1 outside [GameObjectClass].\n",
                    static_cast<unsigned>(kPersonCarrierOffset),
                    slot);
            }
        }

        return nullptr;
    }

    // Production patch: the THIRD Carrier::GetWeapon site in Person::Simulate.
    //
    // Person::Simulate (0x0059D340) decides whether a person crouches by
    // walking the selected-weapon mask:
    //
    //     mask = carrier->GetSelected();            // Pilot Carrier Null Guard
    //     for (i = 0; i < 5; i++)
    //         if (mask & (1 << i))
    //             if (carrier->GetWeapon(i)->cls->sig == 'SNIP')  // no null test
    //                 sniper = true;
    //
    // GetWeapon returns null when the hardpoint mask at [carrier+0x2C] lacks
    // the bit, but nothing keeps the selected mask at [carrier+0x30] inside
    // the hardpoint mask. Lua GiveWeapon(h, nil, slot) empties a hardpoint
    // and leaves its selected bit set, so the next frame reads [null+8] at
    // 0x0059D7D4. Found in ISDF Chronicles isdfms10: wildlife.lua mounts a
    // bite weapon on a jak person in range and removes it again past range.
    //
    // The caller keeps the result only for that one SNIP test (the local at
    // [ebp-0x4B4] has no other reader), so an empty slot gets a static
    // stand-in whose class signature is zero. "Not a sniper weapon" is the
    // accurate answer for an empty hardpoint, and the stock loop continues.
    namespace Hooks
    {
        struct SniperScanEmptyWeaponClass
        {
            uint8_t bytes[0x10];            // +0x0C: signature, zero here
        };
        struct SniperScanEmptyWeapon
        {
            void* unused0;
            void* unused4;
            const SniperScanEmptyWeaponClass* cls;  // +0x08
        };
        const SniperScanEmptyWeaponClass g_SniperScanEmptyClass = {};
        const SniperScanEmptyWeapon g_SniperScanEmptyWeapon = {
            nullptr, nullptr, &g_SniperScanEmptyClass };
        static_assert(offsetof(SniperScanEmptyWeapon, cls) == 0x08,
            "Person::Simulate reads the weapon class at +0x08");
        volatile long g_SniperScanEmptyLogBudget = 8;
    }

    void* __fastcall PersonSniperScanGetWeaponGuard(void* carrier, void* /*edx*/, int slot)
    {
        void* weapon = (carrier && g_BzrFn_CarrierGetWeapon)
            ? g_BzrFn_CarrierGetWeapon(carrier, slot)
            : nullptr;
        if (weapon)
            return weapon;

        if (InterlockedDecrement(&g_SniperScanEmptyLogBudget) >= 0)
        {
            Log(L"[PILOTSAFE] carrier=%p selects empty slot %d in the sniper "
                L"scan; treating it as not a sniper weapon. A script most "
                L"likely removed the selected weapon without clearing the "
                L"weapon mask.\n",
                carrier,
                slot);
        }
        return const_cast<SniperScanEmptyWeapon*>(&g_SniperScanEmptyWeapon);
    }

    // Production patch: HoverCraft::UpdateSounds' turbo-stop lookup.
    //
    // HoverCraft::UpdateSounds (0x004EEA20) starts three looping sounds and
    // caches them on the craft:
    //
    //     craft+0x2C0  thrust  (class soundThrust)
    //     craft+0x2C4  turbo   (class soundTurbo)
    //     craft+0x2CC  third loop
    //
    // When the throttle drops under the turbo gate it does not stop its own
    // +0x2C4 sound. It stops Sound::Find(soundTurbo, owner) and nulls +0x2C4.
    // Sound::Find returns the first live sound with that owner and filename,
    // so when soundThrust and soundTurbo name the same wav it frees the THRUST
    // loop. +0x2C0 is left dangling, the turbo loop plays on orphaned, and the
    // next frame's SetSoundParams writes volume/flags/frequency into freed heap.
    // ISDF Chronicles ships about 40 units with a shared thrust/turbo wav, and
    // global turbo makes craft cross the gate constantly. Dump
    // battlezone98redux.exe.6812.dmp shows the result: the freed 0x84-byte
    // record was reused for an Ogre SubMesh whose parent became 9.
    //
    // The guard answers the lookup with the craft's cached turbo sound while
    // it is still in the live list. Otherwise it gives the stock first match,
    // skipping the craft's thrust loop. If the list walk faults it falls back
    // to stock Sound::Find.
    namespace Hooks
    {
        using FnSoundFind = void*(__cdecl*)(const char* name, void* owner);
        using FnSoundListHead = uint8_t*(__cdecl*)();
        static FnSoundFind g_BzrFn_SoundFind = nullptr;
        static FnSoundListHead g_BzrFn_SoundListHead = nullptr;
        constexpr size_t kHoverCraftThrustSoundOffset = 0x2C0;
        constexpr size_t kHoverCraftTurboSoundOffset = 0x2C4;
        constexpr size_t kSoundNameOffset = 0x04;
        constexpr size_t kSoundOwnerOffset = 0x58;
        constexpr size_t kMaxLiveSoundWalk = 4096;
        static volatile long g_TurboSoundStopLogBudget = 8;

        struct TurboSoundStopScan
        {
            uint8_t* stockFirst;    // what stock Sound::Find would return
            uint8_t* safeFirst;     // first match that is not the thrust loop
            bool turboLive;
        };

        // No C++ objects in this frame: __try cannot coexist with unwinding.
        static bool ScanLiveSoundsForTurboStop(
            const char* name,
            const void* owner,
            const uint8_t* thrust,
            const uint8_t* turbo,
            TurboSoundStopScan* out)
        {
            __try
            {
                size_t walked = 0;
                for (uint8_t* sound = g_BzrFn_SoundListHead();
                     sound && walked < kMaxLiveSoundWalk;
                     sound = *reinterpret_cast<uint8_t**>(sound), ++walked)
                {
                    if (sound == turbo)
                        out->turboLive = true;
                    if (*reinterpret_cast<void**>(sound + kSoundOwnerOffset) != owner)
                        continue;
                    if (name && _stricmp(reinterpret_cast<const char*>(sound + kSoundNameOffset), name) != 0)
                        continue;
                    if (!out->stockFirst)
                        out->stockFirst = sound;
                    if (!out->safeFirst && sound != thrust)
                        out->safeFirst = sound;
                }
                return walked < kMaxLiveSoundWalk;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }
    }

    void SetHoverCraftTurboSoundResolves(void* soundFind, void* soundListHead)
    {
        g_BzrFn_SoundFind = reinterpret_cast<FnSoundFind>(soundFind);
        g_BzrFn_SoundListHead = reinterpret_cast<FnSoundListHead>(soundListHead);
    }

    static void* __cdecl HoverCraftTurboSoundStopFind(
        const char* name, void* owner, const uint8_t* craft)
    {
        if (!craft || !g_BzrFn_SoundListHead)
            return g_BzrFn_SoundFind ? g_BzrFn_SoundFind(name, owner) : nullptr;

        const uint8_t* const thrust =
            *reinterpret_cast<uint8_t* const*>(craft + kHoverCraftThrustSoundOffset);
        const uint8_t* const turbo =
            *reinterpret_cast<uint8_t* const*>(craft + kHoverCraftTurboSoundOffset);

        TurboSoundStopScan scan = {};
        if (!ScanLiveSoundsForTurboStop(name, owner, thrust, turbo, &scan))
            return g_BzrFn_SoundFind ? g_BzrFn_SoundFind(name, owner) : nullptr;

        void* const result = (turbo && scan.turboLive)
            ? const_cast<uint8_t*>(turbo)
            : scan.safeFirst;

        if (thrust && scan.stockFirst == thrust &&
            InterlockedDecrement(&g_TurboSoundStopLogBudget) >= 0)
        {
            Log(L"[SNDFIX] craft=%p turbo stop: stock lookup of '%hs' would have "
                L"freed the thrust loop %p; stopping turbo %p instead. The ODF "
                L"uses one wav for soundThrust and soundTurbo.\n",
                craft,
                name ? name : "<null>",
                thrust,
                result);
        }
        return result;
    }

    // Replaces the E8 at the turbo-stop Sound::Find call. The stock caller
    // pushed (owner, name) and cleans them itself; the craft is the caller's
    // `this` at [ebp-0xE0], which the patch pattern pins.
    __declspec(naked) void HoverCraftTurboSoundStopFindThunk()
    {
        __asm
        {
            mov eax, [ebp - 0xE0]
            push eax                        // craft
            push dword ptr [esp + 0x0C]     // owner
            push dword ptr [esp + 0x0C]     // name
            call HoverCraftTurboSoundStopFind
            add esp, 0x0C
            ret
        }
    }

    // Compatibility toggle: neutral-unit attack/order asymmetry.
    // Stock 1.5 and Redux both exclude team 0 from the UI attack-target list.
    // ControlPanel::Render enumerates candidates and keeps only those where
    // Team::EnemyP(targetTeam) is true. Team::EnemyP(@0x005E1350) explicitly
    // returns false for targetTeam <= 0, so neutral objects are never inserted
    // into the at-most-10 attack list and a click never emits CMD_ATTACK. The
    // underlying Attack() AI task itself DOES damage neutral (a2n and n2p both
    // show ammo/health deltas via Lua). This hook preserves the stock result
    // everywhere except the single patched ControlPanel call: when
    // [Gameplay] AllowNeutralAttackOrders=1 it additionally allows team 0 as an
    // explicit player-ordered target. It does not change Team::EnemyP globally,
    // diplomacy, autonomous acquisition, or network serialization. Default 0
    // keeps legacy/Redux compatibility; enabled gives symmetric
    // player↔neutral orders where appropriate.
    bool __fastcall ControlPanelEnemyPAttackOrderHook(
        void* team, void* /*edx*/, int targetTeam)
    {
        const bool stockEnemy =
            g_BzrFn_ControlPanelEnemyP &&
            g_BzrFn_ControlPanelEnemyP(team, targetTeam);
        const bool allowed = LcbenchSafetyPolicy::AllowExplicitAttackTarget(
            stockEnemy,
            targetTeam,
            g_AllowNeutralAttackOrders);

        if (allowed && !stockEnemy && targetTeam == 0 &&
            InterlockedDecrement(&g_NeutralAttackOrderLogBudget) >= 0)
        {
            Log(L"[NEUTORDER] ControlPanel admitted team-0 explicit attack target "
                L"(team=%p option=enabled)\n",
                team);
        }
        return allowed;
    }
}
