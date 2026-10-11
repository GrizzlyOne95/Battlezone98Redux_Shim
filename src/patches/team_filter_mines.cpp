// team_filter_mines.cpp
// BZR Open Shim - ODF team filters for the shield tower, magnet mine and
// proximity mine (with the magnet zero-range guard and the stock-style
// proximity detonation), split out of bzr_hooks.cpp.
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
    FnShieldTowerSimulate g_BzrFn_ShieldTowerSimulateOriginal = nullptr;
    FnShieldTowerSimulate g_BzrFn_BuildingSimulate = nullptr;
    FnMagnetMineSimulate g_BzrFn_MagnetMineSimulateOriginal = nullptr;
    FnProximityMineSimulate g_BzrFn_ProximityMineSimulateOriginal = nullptr;
    FnProximityMineSimulate g_BzrFn_MineSimulate = nullptr;
    FnShieldTowerPowerUpdate g_BzrFn_ShieldTowerPowerUpdate = nullptr;
    FnGameObjectRelation g_BzrFn_GameObjectFriendP = nullptr;
    FnGameObjectRelation g_BzrFn_GameObjectEnemyP = nullptr;
    FnMatrixInverse g_BzrFn_MatrixInverse = nullptr;
    FnVectorTransform g_BzrFn_VectorTransform = nullptr;
    FnRangeSearch g_BzrFn_CollisionRangeSearch = nullptr;
    FnRangeResultsGetNext g_BzrFn_RangeResultsGetNext = nullptr;

    namespace Hooks
    {
        TeamFilterCache g_ShieldTowerTeamFilterCache = {};
        TeamFilterCache g_MagnetMineTeamFilterCache = {};
        TeamFilterCache g_ProximityMineTeamFilterCache = {};
        bool g_ShieldTowerSimulateHookInstalled = false;
        bool g_MagnetMineSimulateHookInstalled = false;
        bool g_ProximityMineSimulateHookInstalled = false;
        bool g_MagnetZeroRangeGuardEnabled = true;
        volatile long g_MagnetZeroRangeLogBudget = 8;

        constexpr size_t kOrdnanceSpeedOffset = 0x20;

        constexpr size_t kOrdnanceInvSpeedOffset = 0x24;

        constexpr size_t kOrdnanceVelocityOffset = 0x30;

        // Verified byte-for-byte against the shipped GOG v2.2.301 exe
        // (ImageBase 0x00400000). Ordnance is the class in
        // fun3d\OrdnanceClass.cpp: vtable 0x00884E60, with that source-path
        // literal sitting immediately after it at 0x00884E84; an instance is
        // 0xE0 bytes (its factory does `push 0xE0` at 0x00586F88), and the
        // derived "bullet" ordnance (vtable 0x00876720, name string at
        // 0x00876744) is 0xE8. Ordnance::Init is vtable slot 1 = 0x00584FE0,
        // and stores its second argument -- the creator handle -- straight
        // into this field:
        //     0x00585289  mov edx, [ebp-0xA8]    ; edx = this
        //     0x0058528F  mov eax, [ebp+0x0C]    ; eax = creator arg
        //     0x00585292  mov [edx+0xD8], eax
        // That argument is an obj76, not a GameObject: the same Init masks its
        // +0x14 flags into the ordnance's OWN obj76 +0x14 (0x00585001 ..
        // 0x00585016 -- same field at the same offset), and passes it to
        // 0x0062CF50, which walks +0x7C/+0x80 sibling/child links, i.e. the
        // obj76 node links TryReadChunkObjectLinks already reads. So
        // kObj76GameObjectOffset is the correct second hop; the GameObject ctor
        // writes that back-pointer at 0x004DA183 (`mov [obj76+0x8C], this`)
        // right after storing the obj76 at GameObject+0xF4 (0x004DA14B).
        // This constant was 0xCC, which is an unrelated scalar: the same Init
        // zeroes it at 0x005854DC, wedged between an `fstp [this+0xC8]` and a
        // zero store to [this+0xD0], and no ordnance code anywhere reads it.
        // The bad read therefore always yielded 0, TryGetGameObjectFromObj76
        // rejected the null, and TeamFilterShouldAffectOrdnance failed closed --
        // a shield tower or magnet mine with a one-sided team filter silently
        // skipped every ordnance in the list. It stayed invisible because
        // TeamFilterConfig defaults affectAllies/affectEnemies both true, which
        // short-circuits to true before the read is ever reached.
        //
        // The ordnance list itself is the std::list<Ordnance*> the Ordnance
        // ctor/dtor maintain (0x009C908C on 2.2.301). It is taken from the
        // `mov ecx, offset list` that stock ShieldTower::Simulate's own
        // ordnance scan opens with (the ShieldTowerOrdnanceScan row). The
        // literal that used to stand here, 0x0072665C, pointed into .text in
        // the middle of an instruction, so the filtered path's ordnance pass
        // read garbage and faulted into its __except: team-filtered shield
        // towers never deflected ordnance and team-filtered magnet mines never
        // attracted it.
        uint32_t g_OrdnanceListAddr = 0;

        constexpr size_t kShieldTowerClassShieldMinXOffset = 0x160;

        constexpr size_t kShieldTowerClassShieldMaxXOffset = 0x16C;

        constexpr size_t kShieldTowerClassObjPushOffset = 0x178;

        constexpr size_t kShieldTowerClassObjDragOffset = 0x17C;

        constexpr size_t kShieldTowerClassOrdPushOffset = 0x180;

        constexpr size_t kShieldTowerClassOrdDragOffset = 0x184;

        constexpr size_t kShieldTowerPowerSourceOffset = 0x238;

        constexpr size_t kMagnetMineArmingTimerOffset = 0x238;

        constexpr size_t kProximityMineArmingTimerOffset = 0x240;

        constexpr size_t kMagnetMineClassTotalLifeOffset = 0x160;

        constexpr size_t kMagnetMineClassArmingDelayOffset = 0x168;

        constexpr size_t kMagnetMineClassRangeOffset = 0x16C;

        constexpr size_t kMagnetMineClassObjPull1Offset = 0x170;

        constexpr size_t kMagnetMineClassObjPull2Offset = 0x174;

        constexpr size_t kMagnetMineClassObjRotPullOffset = 0x178;

        constexpr size_t kMagnetMineClassOrdPull1Offset = 0x17C;

        constexpr size_t kMagnetMineClassOrdPull2Offset = 0x180;

        constexpr size_t kMagnetMineClassOrdRotPullOffset = 0x184;

        constexpr size_t kProximityMineClassRangeOffset = 0x168;

        constexpr size_t kProximityMineClassScanPeriodOffset = 0x16C;

        constexpr size_t kProximityMineClassExplosionOffset = 0x170;

        constexpr size_t kProximityMinePositionOffset = 0x108;

        // Calls in stock ProximityMine::Simulate's detonation block
        // (FUN_005b0e40, 0x005B1067-0x005B1247), read from the GOG image.
        // Debris: thiscall on the global at 0x00950190 (const double pos[3],
        // const float vel[3], int 0), ret 0xC, run 20 times.
        uint32_t g_ProximityMineDebrisAddr = 0;

        uint32_t g_ProximityMineDebrisOwnerAddr = 0;

        // cdecl (float x, float z, float 3.0).
        uint32_t g_ProximityMineGroundFxAddr = 0;

        // double cdecl (double x, double z): terrain height; stock stores it
        // into obj+0x50 before building the explosion.
        uint32_t g_TerrainHeightAtAddr = 0;

        // thiscall (mine): the damage owner, or null.
        uint32_t g_GameObjectDamageOwnerAddr = 0;

        // ExplosionClass::Build, thiscall (explosionClass, obj+0x20, owner obj), ret 8.
        uint32_t g_ExplosionClassBuildAddr = 0;

        // Returns a global flag; when set, stock calls the next one on mine+0x18.
        uint32_t g_ProximityMineNetFlagAddr = 0;

        uint32_t g_ProximityMineNetNotifyAddr = 0;

        uint32_t g_ShieldTowerSimulateAddr = 0;

        uint32_t g_MagnetMineSimulateAddr = 0;

        uint32_t g_ProximityMineSimulateAddr = 0;

        uint32_t g_MineSimulateAddr = 0;

        uint32_t g_ShieldTowerPowerUpdateAddr = 0;

        // GameObject::FriendP/EnemyP(GameObject*) — bool __thiscall(this, other).
        // Verified on live GOG exe by disassembly (int3-padded prologue; null-checks
        // other, calls other vtable[1]=GetTeamNum, then the int-overload FriendP/EnemyP
        // at 0x4DB560/0x4DB600 → Team::FriendP/EnemyP at 0x5E1310/0x5E1350). Matches the
        // 1.5 decomp bodies exactly. Previous values (0x0046BF40/0x0046BFD0) were WRONG —
        // they land mid-instruction, same failure class as the fixed GetObjByHandle.
        uint32_t g_GameObjectFriendPAddr = 0;

        uint32_t g_GameObjectEnemyPAddr = 0;

        uint32_t g_GameObjectAddVelocityAddr = 0;

        uint32_t g_MatrixInverseAddr = 0;

        uint32_t g_VectorTransformAddr = 0;

        uint32_t g_ShieldTowerSimulateVtableSlotAddr = 0;

        uint32_t g_MagnetMineSimulateVtableSlotAddr = 0;

        uint32_t g_ProximityMineSimulateVtableSlotAddr = 0;

        struct ShieldTowerRangeSearchResults
        {
            uint8_t storage[48] = {};
        };

        struct ListPtrValue
        {
            ListNodePtrValue* head = nullptr;
            size_t size = 0;
        };

        struct ShieldTowerRuntimeParams
        {
            float minX = 0.0f;
            float maxX = 0.0f;
            float minY = 0.0f;
            float maxY = 0.0f;
            float minZ = 0.0f;
            float maxZ = 0.0f;
            float objPush = 0.0f;
            float objDrag = 0.0f;
            float ordPush = 0.0f;
            float ordDrag = 0.0f;
        };

        // The grid query and its iterator, from patches.json; null when
        // unresolved, which keeps the filter hooks from reporting installed.
        static void ResolveCollisionGridQuery()
        {
            if (!g_BzrFn_CollisionRangeSearch)
                g_BzrFn_CollisionRangeSearch = reinterpret_cast<FnRangeSearch>(
                    static_cast<uintptr_t>(HookEngine::ResolveNamedAddress("CollisionGrid::RangeQuery")));
            if (!g_BzrFn_RangeResultsGetNext)
                g_BzrFn_RangeResultsGetNext = reinterpret_cast<FnRangeResultsGetNext>(
                    static_cast<uintptr_t>(HookEngine::ResolveNamedAddress("CollisionGrid::RangeNext")));
        }

        // The craft collision grid (1.5 collision_range_search), the same set
        // stock ShieldTower queries and stock Magnet/ProximityMine walk as the
        // craft list. Null before the grid exists or when unresolved.
        static void* ReadCraftCollisionGrid()
        {
            const uintptr_t slot = EngineGlobals::CraftCollisionGridSlot();
            if (slot == 0)
                return nullptr;
            __try
            {
                return *reinterpret_cast<void**>(slot);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        void __fastcall ShieldTowerSimulateTeamFilterHook(void* thisPtr, void* /*edx*/, float dt)
        {
            RunShieldTowerFilteredSimulate(thisPtr, dt);
        }

        static bool TryGetUnsafeMagnetRange(void* magnetMinePtr, float& outRange)
        {
            outRange = 0.0f;
            if (!magnetMinePtr)
                return false;

            __try
            {
                auto* mineBytes = reinterpret_cast<const uint8_t*>(magnetMinePtr);
                const void* mineClass = *reinterpret_cast<void* const*>(
                    mineBytes + kGameObjectClassOffset);
                if (!mineClass)
                    return false;

                outRange = *reinterpret_cast<const float*>(
                    reinterpret_cast<const uint8_t*>(mineClass) +
                    kMagnetMineClassRangeOffset);
                return !std::isfinite(outRange) || outRange <= 0.0f;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void __fastcall MagnetMineSimulateTeamFilterHook(void* thisPtr, void* /*edx*/, float dt)
        {
            float range = 0.0f;
            if (g_MagnetZeroRangeGuardEnabled && TryGetUnsafeMagnetRange(thisPtr, range))
            {
                const long remaining = InterlockedDecrement(&g_MagnetZeroRangeLogBudget);
                if (remaining >= 0)
                {
                    Log(L"[MAGNET] Skipped attraction for invalid range=%.6g mine=0x%08X; base Mine::Simulate preserved (remaining=%ld)\n",
                        static_cast<double>(range),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)),
                        remaining);
                }

                // MagnetMine::Simulate eventually delegates to Mine::Simulate.
                // Preserve that lifetime/removal behavior while bypassing the
                // invalid attraction bounds that trigger the zero-range fault.
                if (g_BzrFn_MineSimulate)
                    g_BzrFn_MineSimulate(thisPtr, dt);
                else if (g_BzrFn_MagnetMineSimulateOriginal)
                    g_BzrFn_MagnetMineSimulateOriginal(thisPtr, dt);
                return;
            }

            RunMagnetMineFilteredSimulate(thisPtr, dt);
        }

        void __fastcall ProximityMineSimulateTeamFilterHook(void* thisPtr, void* /*edx*/, float dt)
        {
            RunProximityMineFilteredSimulate(thisPtr, dt);
        }

        uint32_t g_BuildingSimulateAddr = 0;

        // Simulate is slot 15 of each class's vtable; the vtables are rows
        // checked by RTTI name, so the slot addresses follow the build.
        constexpr size_t kSimulateVtableIndex = 15;

        static bool BindSimulateSlot(uint32_t vtable, const char* rttiName, uint32_t& outSlot)
        {
            if (!VtableTypeNameMatches(vtable, rttiName))
            {
                Log(L"[SHIELDODF] %hs vtable RTTI mismatch at 0x%08X; team filters stand down\n",
                    rttiName, vtable);
                return false;
            }
            outSlot = vtable + static_cast<uint32_t>(kSimulateVtableIndex * sizeof(void*));
            return true;
        }

        static bool TeamFilterAddressesBound()
        {
            static const bool bound = [] {
                uint32_t shieldVtable = 0, magnetVtable = 0, proximityVtable = 0, ordnanceScan = 0;
                const HookEngine::EngineRow rows[] = {
                    { "ShieldTowerSimulate", &g_ShieldTowerSimulateAddr },
                    { "MagnetMineSimulate", &g_MagnetMineSimulateAddr },
                    { "ProximityMineSimulate", &g_ProximityMineSimulateAddr },
                    { "MineSimulate", &g_MineSimulateAddr },
                    { "BuildingSimulate", &g_BuildingSimulateAddr },
                    { "ShieldTowerPowerUpdate", &g_ShieldTowerPowerUpdateAddr },
                    { "GameObjectFriendP", &g_GameObjectFriendPAddr },
                    { "GameObjectEnemyP", &g_GameObjectEnemyPAddr },
                    { "GameObjectAddVelocity", &g_GameObjectAddVelocityAddr },
                    { "MatrixInverse", &g_MatrixInverseAddr },
                    { "VectorTransform", &g_VectorTransformAddr },
                    { "ShieldTowerVtable", &shieldVtable },
                    { "MagnetMineVtable", &magnetVtable },
                    { "ProximityMineVtable", &proximityVtable },
                    { "ShieldTowerOrdnanceScan", &ordnanceScan },
                };
                if (!HookEngine::BindEngineRows("Team filter (shield towers, mines)", rows))
                    return false;
                if (!BindSimulateSlot(shieldVtable, ".?AVShieldTower@@", g_ShieldTowerSimulateVtableSlotAddr) ||
                    !BindSimulateSlot(magnetVtable, ".?AVMagnetMine@@", g_MagnetMineSimulateVtableSlotAddr) ||
                    !BindSimulateSlot(proximityVtable, ".?AVProximityMine@@", g_ProximityMineSimulateVtableSlotAddr))
                    return false;
                const auto* scan = reinterpret_cast<const uint8_t*>(ordnanceScan);
                if (scan[0] != 0xB9)
                    return false;
                g_OrdnanceListAddr = *reinterpret_cast<const uint32_t*>(scan + 1);
                return true;
            }();
            return bound;
        }

        void InstallShieldTowerTeamFilterHookIfPossible()
        {
            if (g_ShieldTowerSimulateHookInstalled)
                return;
            if (!TeamFilterAddressesBound())
                return;

            if (!g_BzrFn_ShieldTowerSimulateOriginal)
                g_BzrFn_ShieldTowerSimulateOriginal =
                    reinterpret_cast<FnShieldTowerSimulate>(g_ShieldTowerSimulateAddr);
            if (!g_BzrFn_BuildingSimulate)
                g_BzrFn_BuildingSimulate =
                    reinterpret_cast<FnShieldTowerSimulate>(g_BuildingSimulateAddr);
            if (!g_BzrFn_ShieldTowerPowerUpdate)
                g_BzrFn_ShieldTowerPowerUpdate =
                    reinterpret_cast<FnShieldTowerPowerUpdate>(g_ShieldTowerPowerUpdateAddr);
            if (!g_BzrFn_GameObjectFriendP)
                g_BzrFn_GameObjectFriendP =
                    reinterpret_cast<FnGameObjectRelation>(g_GameObjectFriendPAddr);
            if (!g_BzrFn_GameObjectEnemyP)
                g_BzrFn_GameObjectEnemyP =
                    reinterpret_cast<FnGameObjectRelation>(g_GameObjectEnemyPAddr);
            if (!g_BzrFn_GameObjectGetObjByHandle)
                g_BzrFn_GameObjectGetObjByHandle =
                    &GameObjectFromHandleGog; // was 0x0046B160 (wrong fn; crashed)
            if (!g_BzrFn_MatrixInverse)
                g_BzrFn_MatrixInverse =
                    reinterpret_cast<FnMatrixInverse>(g_MatrixInverseAddr);
            if (!g_BzrFn_VectorTransform)
                g_BzrFn_VectorTransform =
                    reinterpret_cast<FnVectorTransform>(g_VectorTransformAddr);
            ResolveCollisionGridQuery();

            void* current = nullptr;
            __try
            {
                current = *reinterpret_cast<void**>(g_ShieldTowerSimulateVtableSlotAddr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                current = nullptr;
            }

            if (current != reinterpret_cast<void*>(ShieldTowerSimulateTeamFilterHook) &&
                current != reinterpret_cast<void*>(g_ShieldTowerSimulateAddr))
            {
                Log(L"[SHIELDODF] ShieldTower::Simulate vtable mismatch slot=0x%08X current=0x%08X expected=0x%08X\n",
                    static_cast<uint32_t>(g_ShieldTowerSimulateVtableSlotAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                    static_cast<uint32_t>(g_ShieldTowerSimulateAddr));
                return;
            }

            const bool patched =
                (current == reinterpret_cast<void*>(ShieldTowerSimulateTeamFilterHook)) ||
                WritePointerValue(g_ShieldTowerSimulateVtableSlotAddr,
                                  reinterpret_cast<void*>(ShieldTowerSimulateTeamFilterHook));
            g_ShieldTowerSimulateHookInstalled =
                patched &&
                g_BzrFn_ShieldTowerSimulateOriginal &&
                g_BzrFn_BuildingSimulate &&
                g_BzrFn_ShieldTowerPowerUpdate &&
                g_BzrFn_GameObjectFriendP &&
                g_BzrFn_GameObjectEnemyP &&
                g_BzrFn_GameObjectGetObjByHandle &&
                g_BzrFn_MatrixInverse &&
                g_BzrFn_VectorTransform &&
                g_BzrFn_CollisionRangeSearch &&
                g_BzrFn_RangeResultsGetNext;

            if (g_ShieldTowerSimulateHookInstalled)
            {
                Log(L"[SHIELDODF] Installed ShieldTower team filter hook slot=0x%08X original=0x%08X\n",
                    static_cast<uint32_t>(g_ShieldTowerSimulateVtableSlotAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_ShieldTowerSimulateOriginal)));
            }
        }
        void InstallMineTeamFilterHooksIfPossible()
        {
            if (g_MagnetMineSimulateHookInstalled && g_ProximityMineSimulateHookInstalled)
                return;
            if (!TeamFilterAddressesBound())
                return;

            if (!g_BzrFn_MagnetMineSimulateOriginal)
                g_BzrFn_MagnetMineSimulateOriginal =
                    reinterpret_cast<FnMagnetMineSimulate>(g_MagnetMineSimulateAddr);
            if (!g_BzrFn_ProximityMineSimulateOriginal)
                g_BzrFn_ProximityMineSimulateOriginal =
                    reinterpret_cast<FnProximityMineSimulate>(g_ProximityMineSimulateAddr);
            if (!g_BzrFn_MineSimulate)
                g_BzrFn_MineSimulate =
                    reinterpret_cast<FnProximityMineSimulate>(g_MineSimulateAddr);

            if (!g_BzrFn_GameObjectFriendP)
                g_BzrFn_GameObjectFriendP =
                    reinterpret_cast<FnGameObjectRelation>(g_GameObjectFriendPAddr);
            if (!g_BzrFn_GameObjectEnemyP)
                g_BzrFn_GameObjectEnemyP =
                    reinterpret_cast<FnGameObjectRelation>(g_GameObjectEnemyPAddr);
            if (!g_BzrFn_GameObjectGetObjByHandle)
                g_BzrFn_GameObjectGetObjByHandle =
                    &GameObjectFromHandleGog; // was 0x0046B160 (wrong fn; crashed)
            ResolveCollisionGridQuery();

            if (!g_MagnetMineSimulateHookInstalled)
            {
                void* current = nullptr;
                __try { current = *reinterpret_cast<void**>(g_MagnetMineSimulateVtableSlotAddr); }
                __except (EXCEPTION_EXECUTE_HANDLER) { current = nullptr; }

                if (current != reinterpret_cast<void*>(MagnetMineSimulateTeamFilterHook) &&
                    current != reinterpret_cast<void*>(g_MagnetMineSimulateAddr))
                {
                    Log(L"[MAGNETODF] MagnetMine::Simulate vtable mismatch slot=0x%08X current=0x%08X expected=0x%08X\n",
                        static_cast<uint32_t>(g_MagnetMineSimulateVtableSlotAddr),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                        static_cast<uint32_t>(g_MagnetMineSimulateAddr));
                }
                else
                {
                    const bool patched =
                        (current == reinterpret_cast<void*>(MagnetMineSimulateTeamFilterHook)) ||
                        WritePointerValue(g_MagnetMineSimulateVtableSlotAddr,
                                          reinterpret_cast<void*>(MagnetMineSimulateTeamFilterHook));
                    g_MagnetMineSimulateHookInstalled =
                        patched &&
                        g_BzrFn_MagnetMineSimulateOriginal &&
                        g_BzrFn_MineSimulate &&
                        g_BzrFn_GameObjectFriendP &&
                        g_BzrFn_GameObjectEnemyP &&
                        g_BzrFn_GameObjectGetObjByHandle &&
                        g_BzrFn_CollisionRangeSearch &&
                        g_BzrFn_RangeResultsGetNext;

                    if (g_MagnetMineSimulateHookInstalled)
                    {
                        Log(L"[MAGNETODF] Installed MagnetMine team filter hook slot=0x%08X original=0x%08X\n",
                            static_cast<uint32_t>(g_MagnetMineSimulateVtableSlotAddr),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_MagnetMineSimulateOriginal)));
                    }
                }
            }

            if (!g_ProximityMineSimulateHookInstalled)
            {
                void* current = nullptr;
                __try { current = *reinterpret_cast<void**>(g_ProximityMineSimulateVtableSlotAddr); }
                __except (EXCEPTION_EXECUTE_HANDLER) { current = nullptr; }

                if (current != reinterpret_cast<void*>(ProximityMineSimulateTeamFilterHook) &&
                    current != reinterpret_cast<void*>(g_ProximityMineSimulateAddr))
                {
                    Log(L"[PROXODF] ProximityMine::Simulate vtable mismatch slot=0x%08X current=0x%08X expected=0x%08X\n",
                        static_cast<uint32_t>(g_ProximityMineSimulateVtableSlotAddr),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                        static_cast<uint32_t>(g_ProximityMineSimulateAddr));
                }
                else
                {
                    const bool patched =
                        (current == reinterpret_cast<void*>(ProximityMineSimulateTeamFilterHook)) ||
                        WritePointerValue(g_ProximityMineSimulateVtableSlotAddr,
                                          reinterpret_cast<void*>(ProximityMineSimulateTeamFilterHook));
                    g_ProximityMineSimulateHookInstalled =
                        patched &&
                        g_BzrFn_ProximityMineSimulateOriginal &&
                        g_BzrFn_MineSimulate &&
                        g_BzrFn_GameObjectFriendP &&
                        g_BzrFn_GameObjectEnemyP &&
                        g_BzrFn_GameObjectGetObjByHandle &&
                        g_BzrFn_CollisionRangeSearch &&
                        g_BzrFn_RangeResultsGetNext;

                    if (g_ProximityMineSimulateHookInstalled)
                    {
                        Log(L"[PROXODF] Installed ProximityMine team filter hook slot=0x%08X original=0x%08X\n",
                            static_cast<uint32_t>(g_ProximityMineSimulateVtableSlotAddr),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_ProximityMineSimulateOriginal)));
                    }
                }
            }
        }

        static bool TryParseTeamFilterValue(const char* value,
                                                       bool& outAffectAllies,
                                                       bool& outAffectEnemies)
        {
            char normalized[64] = {};
            if (!TryNormalizeQuotedStringValue(value, normalized, sizeof(normalized)))
                return false;

            if (strcmp(normalized, "all") == 0 ||
                strcmp(normalized, "both") == 0 ||
                strcmp(normalized, "default") == 0)
            {
                outAffectAllies = true;
                outAffectEnemies = true;
                return true;
            }

            if (strcmp(normalized, "allies") == 0 ||
                strcmp(normalized, "ally") == 0 ||
                strcmp(normalized, "friendly") == 0 ||
                strcmp(normalized, "friendlies") == 0)
            {
                outAffectAllies = true;
                outAffectEnemies = false;
                return true;
            }

            if (strcmp(normalized, "enemies") == 0 ||
                strcmp(normalized, "enemy") == 0 ||
                strcmp(normalized, "hostile") == 0 ||
                strcmp(normalized, "hostiles") == 0)
            {
                outAffectAllies = false;
                outAffectEnemies = true;
                return true;
            }

            if (strcmp(normalized, "none") == 0 ||
                strcmp(normalized, "off") == 0 ||
                strcmp(normalized, "disabled") == 0)
            {
                outAffectAllies = false;
                outAffectEnemies = false;
                return true;
            }

            return false;
        }

        static bool TryReadTeamFilterFromOdfFile(const char* odfToken,
                                                 TeamFilterConfig& outConfig,
                                                 const char* logTag)
        {
            outConfig = {};

            std::filesystem::path resolvedPath;
            if (!TryResolveOdfFilePath(odfToken, resolvedPath))
                return false;

            const ProducerBuildMenuEntry odfKey = NormalizeQuotedOdfToken(odfToken);
            if (!odfKey.hasValue)
                return false;

            FILE* file = nullptr;
            if (fopen_s(&file, resolvedPath.string().c_str(), "r") != 0 || !file)
                return false;

            bool foundAny = false;
            bool affectAllies = true;
            bool affectEnemies = true;
            char line[256] = {};
            while (std::fgets(line, static_cast<int>(sizeof(line)), file))
            {
                char* trimmed = TrimAsciiInPlace(line);
                if (*trimmed == '\0' || *trimmed == ';' || *trimmed == '#')
                    continue;

                if (*trimmed == '[')
                    continue;

                char* equals = std::strchr(trimmed, '=');
                if (!equals)
                    continue;

                *equals = '\0';
                char* key = TrimAsciiInPlace(trimmed);
                char* value = TrimAsciiInPlace(equals + 1);
                if (!key || !*key || !value || !*value)
                    continue;

                bool parsedBool = false;
                bool parsedAllies = false;
                bool parsedEnemies = false;
                if (_stricmp(key, "teamFilter") == 0 &&
                    TryParseTeamFilterValue(value, parsedAllies, parsedEnemies))
                {
                    affectAllies = parsedAllies;
                    affectEnemies = parsedEnemies;
                    foundAny = true;
                }
                else if (_stricmp(key, "affectAllies") == 0 && TryParseBoolValue(value, parsedBool))
                {
                    affectAllies = parsedBool;
                    foundAny = true;
                }
                else if (_stricmp(key, "affectEnemies") == 0 && TryParseBoolValue(value, parsedBool))
                {
                    affectEnemies = parsedBool;
                    foundAny = true;
                }
            }

            std::fclose(file);

            if (!foundAny)
                return false;

            outConfig.parsed = true;
            outConfig.affectAllies = affectAllies;
            outConfig.affectEnemies = affectEnemies;
            Log(L"[%hs] Loaded team filter odf=%hs allies=%hs enemies=%hs file=%hs\n",
                logTag ? logTag : "TEAMODF",
                odfKey.token,
                affectAllies ? "true" : "false",
                affectEnemies ? "true" : "false",
                resolvedPath.string().c_str());
            return true;
        }

        bool TryGetTeamFilterForObject(void* objectPtr, TeamFilterConfig& outConfig, TeamFilterCache& cache, const char* logTag)
        {
            outConfig = {};

            char odfToken[kProducerBuildMenuTokenLen + 1] = {};
            if (!TryGetObjectOdfToken(objectPtr, odfToken))
                return false;

            const auto cached = cache.odfEntries.find(odfToken);
            if (cached != cache.odfEntries.end())
            {
                outConfig = cached->second;
                return outConfig.parsed;
            }

            TeamFilterConfig loaded = {};
            TryReadTeamFilterFromOdfFile(odfToken, loaded, logTag);
            cache.odfEntries[odfToken] = loaded;
            outConfig = loaded;
            return outConfig.parsed;
        }

        static bool TeamFilterNeedsCustomPath(const TeamFilterConfig& config)
        {
            return config.parsed && !(config.affectAllies && config.affectEnemies);
        }

        static bool TryGetOrdnanceWorldPosition(void* ordnance, float (&outPosition)[3])
        {
            outPosition[0] = 0.0f;
            outPosition[1] = 0.0f;
            outPosition[2] = 0.0f;
            if (!ordnance)
                return false;

            __try
            {
                void* obj76 =
                    *reinterpret_cast<void* const*>(reinterpret_cast<const uint8_t*>(ordnance) + kOrdnanceObjOffset);
                return TryGetObjectWorldPositionFromObj76(obj76, outPosition);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryGetOrdnanceOwnerGameObject(void* ordnance, void*& outOwner)
        {
            outOwner = nullptr;
            if (!ordnance)
                return false;

            __try
            {
                void* ownerObj76 =
                    *reinterpret_cast<void* const*>(reinterpret_cast<const uint8_t*>(ordnance) + kOrdnanceOwnerObjOffset);
                return TryGetGameObjectFromObj76(ownerObj76, outOwner);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outOwner = nullptr;
                return false;
            }
        }

        static bool TryReadShieldTowerRuntimeParams(void* shieldTowerPtr,
                                                    ShieldTowerRuntimeParams& outParams,
                                                    void*& outTowerObj76,
                                                    LegacyMat3*& outTowerMatrix,
                                                    LegacyMat3& outInverseMatrix)
        {
            outParams = {};
            outTowerObj76 = nullptr;
            outTowerMatrix = nullptr;
            std::memset(&outInverseMatrix, 0, sizeof(outInverseMatrix));
            if (!shieldTowerPtr)
                return false;

            __try
            {
                const auto* shieldBytes = reinterpret_cast<const uint8_t*>(shieldTowerPtr);
                outTowerObj76 = *reinterpret_cast<void* const*>(shieldBytes + kGameObjectObjOffset);
                auto* shieldClass = *reinterpret_cast<void* const*>(shieldBytes + kGameObjectClassOffset);
                if (!outTowerObj76 || !shieldClass)
                    return false;

                outTowerMatrix = reinterpret_cast<LegacyMat3*>(
                    reinterpret_cast<uint8_t*>(outTowerObj76) + kObj76TransformOffset);
                if (!outTowerMatrix)
                    return false;

                outParams.minX = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassShieldMinXOffset + 0x00);
                outParams.minY = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassShieldMinXOffset + 0x04);
                outParams.minZ = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassShieldMinXOffset + 0x08);
                outParams.maxX = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassShieldMaxXOffset + 0x00);
                outParams.maxY = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassShieldMaxXOffset + 0x04);
                outParams.maxZ = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassShieldMaxXOffset + 0x08);
                outParams.objPush = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassObjPushOffset);
                outParams.objDrag = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassObjDragOffset);
                outParams.ordPush = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassOrdPushOffset);
                outParams.ordDrag = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassOrdDragOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outTowerObj76 = nullptr;
                outTowerMatrix = nullptr;
                return false;
            }

            if (!g_BzrFn_MatrixInverse)
                return false;

            g_BzrFn_MatrixInverse(&outInverseMatrix, outTowerMatrix);
            return true;
        }

        static bool ShieldTowerContainsLocalPosition(const float (&localPosition)[3],
                                                     const ShieldTowerRuntimeParams& params)
        {
            return (params.minX < localPosition[0] && localPosition[0] < params.maxX) &&
                   (params.minY < localPosition[1] && localPosition[1] < params.maxY) &&
                   (params.minZ < localPosition[2] && localPosition[2] < params.maxZ);
        }

        static bool TeamFilterShouldAffectObject(void* shieldTowerPtr,
                                                  void* targetObject,
                                                  const TeamFilterConfig& config)
        {
            if (!shieldTowerPtr || !targetObject)
                return false;

            if (config.affectAllies && config.affectEnemies)
                return true;

            bool allow = false;
            if (config.affectAllies && g_BzrFn_GameObjectFriendP)
                allow = g_BzrFn_GameObjectFriendP(shieldTowerPtr, targetObject);
            if (!allow && config.affectEnemies && g_BzrFn_GameObjectEnemyP)
                allow = g_BzrFn_GameObjectEnemyP(shieldTowerPtr, targetObject);
            return allow;
        }

        static bool TeamFilterShouldAffectOrdnance(void* shieldTowerPtr,
                                                    void* ordnance,
                                                    const TeamFilterConfig& config)
        {
            if (config.affectAllies && config.affectEnemies)
                return true;

            void* ownerObject = nullptr;
            if (!TryGetOrdnanceOwnerGameObject(ordnance, ownerObject))
                return false;

            return TeamFilterShouldAffectObject(shieldTowerPtr, ownerObject, config);
        }

        static void ShieldTowerApplyObjectForce(void* shieldTowerPtr,
                                                void* targetObject,
                                                const LegacyMat3& towerMatrix,
                                                const ShieldTowerRuntimeParams& params,
                                                float dt)
        {
            if (!shieldTowerPtr || !targetObject)
                return;

            __try
            {
                float delta[3] =
                {
                    towerMatrix.front_x * (params.objPush * dt) -
                        *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(targetObject) + 0x12C) * (params.objDrag * dt),
                    towerMatrix.front_y * (params.objPush * dt) -
                        *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(targetObject) + 0x130) * (params.objDrag * dt),
                    towerMatrix.front_z * (params.objPush * dt) -
                        *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(targetObject) + 0x134) * (params.objDrag * dt)
                };
                reinterpret_cast<void(__thiscall*)(void*, const float*)>(g_GameObjectAddVelocityAddr)(targetObject, delta);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        static void ShieldTowerApplyOrdnanceForce(void* ordnance,
                                                  const LegacyMat3& towerMatrix,
                                                  const ShieldTowerRuntimeParams& params,
                                                  float dt)
        {
            if (!ordnance)
                return;

            __try
            {
                auto* ordBytes = reinterpret_cast<uint8_t*>(ordnance);
                auto* velocity = reinterpret_cast<float*>(ordBytes + kOrdnanceVelocityOffset);
                velocity[0] += towerMatrix.front_x * (params.ordPush * dt) - velocity[0] * (params.ordDrag * dt);
                velocity[1] += towerMatrix.front_y * (params.ordPush * dt) - velocity[1] * (params.ordDrag * dt);
                velocity[2] += towerMatrix.front_z * (params.ordPush * dt) - velocity[2] * (params.ordDrag * dt);

                const float speed = std::sqrt(
                    velocity[0] * velocity[0] +
                    velocity[1] * velocity[1] +
                    velocity[2] * velocity[2]);
                *reinterpret_cast<float*>(ordBytes + kOrdnanceSpeedOffset) = speed;
                *reinterpret_cast<float*>(ordBytes + kOrdnanceInvSpeedOffset) =
                    (speed == 0.0f) ? 1.0e30f : (1.0f / speed);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        void RunShieldTowerFilteredSimulate(void* shieldTowerPtr, float dt)
        {
            if (!shieldTowerPtr || !g_BzrFn_ShieldTowerPowerUpdate || !g_BzrFn_BuildingSimulate ||
                !g_BzrFn_VectorTransform || !g_BzrFn_CollisionRangeSearch || !g_BzrFn_RangeResultsGetNext ||
                !g_BzrFn_GameObjectGetObjByHandle || !g_BzrFn_GameObjectFriendP || !g_BzrFn_GameObjectEnemyP)
            {
                if (g_BzrFn_ShieldTowerSimulateOriginal)
                    g_BzrFn_ShieldTowerSimulateOriginal(shieldTowerPtr, dt);
                return;
            }

            ShieldTowerRuntimeParams params = {};
            void* towerObj76 = nullptr;
            LegacyMat3* towerMatrix = nullptr;
            LegacyMat3 inverseMatrix = {};

            TeamFilterConfig filter = {};
            const bool hasFilter = TryGetTeamFilterForObject(shieldTowerPtr, filter, g_ShieldTowerTeamFilterCache, "SHIELDODF");
            if (!hasFilter || !TeamFilterNeedsCustomPath(filter))
            {
                if (g_BzrFn_ShieldTowerSimulateOriginal)
                    g_BzrFn_ShieldTowerSimulateOriginal(shieldTowerPtr, dt);
                return;
            }

            g_BzrFn_ShieldTowerPowerUpdate(shieldTowerPtr);

            if (!TryReadShieldTowerRuntimeParams(shieldTowerPtr, params, towerObj76, towerMatrix, inverseMatrix))
            {
                if (g_BzrFn_ShieldTowerSimulateOriginal)
                    g_BzrFn_ShieldTowerSimulateOriginal(shieldTowerPtr, dt);
                return;
            }

            if (*reinterpret_cast<const int*>(reinterpret_cast<const uint8_t*>(shieldTowerPtr) + kShieldTowerPowerSourceOffset) != 0)
            {
                float worldCorners[24] =
                {
                    params.minX, params.minY, params.minZ,
                    params.maxX, params.minY, params.minZ,
                    params.minX, params.minY, params.maxZ,
                    params.maxX, params.minY, params.maxZ,
                    params.minX, params.maxY, params.minZ,
                    params.maxX, params.maxY, params.minZ,
                    params.minX, params.maxY, params.maxZ,
                    params.maxX, params.maxY, params.maxZ
                };

                g_BzrFn_VectorTransform(worldCorners, worldCorners, 8, towerMatrix);

                float minWorldX = 1.0e30f;
                float minWorldZ = 1.0e30f;
                float maxWorldX = -1.0e30f;
                float maxWorldZ = -1.0e30f;
                for (size_t i = 0; i < 8; ++i)
                {
                    const float worldX = worldCorners[i * 3 + 0];
                    const float worldZ = worldCorners[i * 3 + 2];
                    minWorldX = (std::min)(minWorldX, worldX);
                    minWorldZ = (std::min)(minWorldZ, worldZ);
                    maxWorldX = (std::max)(maxWorldX, worldX);
                    maxWorldZ = (std::max)(maxWorldZ, worldZ);
                }

                void* collisionRangeSearch = ReadCraftCollisionGrid();
                if (collisionRangeSearch && g_BzrFn_CollisionRangeSearch && g_BzrFn_RangeResultsGetNext)
                {
                    ShieldTowerRangeSearchResults results = {};
                    g_BzrFn_CollisionRangeSearch(
                        collisionRangeSearch,
                        static_cast<double>(minWorldX),
                        static_cast<double>(minWorldZ),
                        static_cast<double>(maxWorldX),
                        static_cast<double>(maxWorldZ),
                        &results);

                    uint32_t* handlePtr = nullptr;
                    while (g_BzrFn_RangeResultsGetNext(&results, &handlePtr) != 0)
                    {
                        if (!handlePtr)
                            continue;

                        void* targetObject = g_BzrFn_GameObjectGetObjByHandle(static_cast<int>(*handlePtr));
                        if (!targetObject || !TeamFilterShouldAffectObject(shieldTowerPtr, targetObject, filter))
                            continue;

                        float targetWorld[3] = {};
                        if (!TryGetGameObjectWorldPosition(targetObject, targetWorld))
                            continue;

                        float targetLocal[3] = { targetWorld[0], targetWorld[1], targetWorld[2] };
                        g_BzrFn_VectorTransform(targetLocal, targetLocal, 1, &inverseMatrix);
                        if (!ShieldTowerContainsLocalPosition(targetLocal, params))
                            continue;

                        ShieldTowerApplyObjectForce(shieldTowerPtr, targetObject, *towerMatrix, params, dt);
                    }
                }

                const auto* list = reinterpret_cast<const ListPtrValue*>(g_OrdnanceListAddr);
                __try
                {
                    if (list && list->head)
                    {
                        for (ListNodePtrValue* node = list->head->next;
                             node && node != list->head;
                             node = node->next)
                        {
                            void* ordnance = node->value;
                            if (!ordnance || !TeamFilterShouldAffectOrdnance(shieldTowerPtr, ordnance, filter))
                                continue;

                            float ordWorld[3] = {};
                            if (!TryGetOrdnanceWorldPosition(ordnance, ordWorld))
                                continue;

                            float ordLocal[3] = { ordWorld[0], ordWorld[1], ordWorld[2] };
                            g_BzrFn_VectorTransform(ordLocal, ordLocal, 1, &inverseMatrix);
                            if (!ShieldTowerContainsLocalPosition(ordLocal, params))
                                continue;

                            ShieldTowerApplyOrdnanceForce(ordnance, *towerMatrix, params, dt);
                        }
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            g_BzrFn_BuildingSimulate(shieldTowerPtr, dt);
        }
        void RunMagnetMineFilteredSimulate(void* magnetMinePtr, float dt)
        {
            if (!magnetMinePtr || !g_BzrFn_GameObjectGetObjByHandle || !g_BzrFn_GameObjectFriendP || !g_BzrFn_GameObjectEnemyP)
            {
                if (g_BzrFn_MagnetMineSimulateOriginal)
                    g_BzrFn_MagnetMineSimulateOriginal(magnetMinePtr, dt);
                return;
            }

            TeamFilterConfig filter = {};
            const bool hasFilter = TryGetTeamFilterForObject(magnetMinePtr, filter, g_MagnetMineTeamFilterCache, "MAGNETODF");
            if (!hasFilter || !TeamFilterNeedsCustomPath(filter))
            {
                if (g_BzrFn_MagnetMineSimulateOriginal)
                    g_BzrFn_MagnetMineSimulateOriginal(magnetMinePtr, dt);
                return;
            }

            __try
            {
                auto* mineBytes = reinterpret_cast<uint8_t*>(magnetMinePtr);
                void* mineClass = *reinterpret_cast<void**>(mineBytes + kGameObjectClassOffset);
                // No class, no attraction, but the base Mine::Simulate below
                // still has to run: it is what expires and removes the mine.
                if (!mineClass) __leave;

                float armingTimer = *reinterpret_cast<float*>(mineBytes + kMagnetMineArmingTimerOffset);
                float totalLife = *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassTotalLifeOffset);
                float armingDelay = *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassArmingDelayOffset);

                float elapsed = totalLife - armingTimer;
                if (elapsed >= armingDelay)
                {
                    float range = *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassRangeOffset);
                    float minePos[3] = {
                        *reinterpret_cast<float*>(mineBytes + 0x108),
                        *reinterpret_cast<float*>(mineBytes + 0x10C),
                        *reinterpret_cast<float*>(mineBytes + 0x110)
                    };

                    // Proximity scan for objects
                    void* collisionRangeSearch = ReadCraftCollisionGrid();
                    if (collisionRangeSearch && g_BzrFn_CollisionRangeSearch && g_BzrFn_RangeResultsGetNext)
                    {
                        ShieldTowerRangeSearchResults results = {};
                        g_BzrFn_CollisionRangeSearch(
                            collisionRangeSearch,
                            static_cast<double>(minePos[0] - range),
                            static_cast<double>(minePos[2] - range),
                            static_cast<double>(minePos[0] + range),
                            static_cast<double>(minePos[2] + range),
                            &results);

                        uint32_t* handlePtr = nullptr;
                        while (g_BzrFn_RangeResultsGetNext(&results, &handlePtr) != 0)
                        {
                            if (!handlePtr) continue;
                            void* target = g_BzrFn_GameObjectGetObjByHandle(static_cast<int>(*handlePtr));
                            if (!target || target == magnetMinePtr) continue;

                            // ORIGINAL check: vtable[+0x2c] targets? and distance.
                            // We add TeamFilter check.
                            if (!TeamFilterShouldAffectObject(magnetMinePtr, target, filter))
                                continue;

                            float targetPos[3] = {};
                            if (TryGetGameObjectWorldPosition(target, targetPos))
                            {
                                float dx = targetPos[0] - minePos[0];
                                float dy = targetPos[1] - minePos[1];
                                float dz = targetPos[2] - minePos[2];
                                float distSq = dx * dx + dy * dy + dz * dz;

                                if (distSq < range * range)
                                {
                                    float dist = std::sqrt(distSq + 0.0001f);
                                    float pull = (dist * *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassObjPull1Offset) +
                                                  *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassObjPull2Offset)) * dt;
                                    float rotPull = dt * *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassObjRotPullOffset);

                                    float velDelta[3] = {
                                        dx * pull - (*reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(target) + 0x12C) * rotPull),
                                        dy * pull - (*reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(target) + 0x130) * rotPull),
                                        dz * pull - (*reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(target) + 0x134) * rotPull)
                                    };
                                    reinterpret_cast<void(__thiscall*)(void*, const float*)>(g_GameObjectAddVelocityAddr)(target, velDelta);
                                }
                            }
                        }
                    }

                    // Proximity scan for ordnance
                    const auto* ordList = reinterpret_cast<const ListPtrValue*>(g_OrdnanceListAddr);
                    if (ordList && ordList->head)
                    {
                        for (ListNodePtrValue* node = ordList->head->next; node && node != ordList->head; node = node->next)
                        {
                            void* ordnance = node->value;
                            if (!ordnance || !TeamFilterShouldAffectOrdnance(magnetMinePtr, ordnance, filter))
                                continue;

                            float ordPos[3] = {};
                            if (TryGetOrdnanceWorldPosition(ordnance, ordPos))
                            {
                                float dx = ordPos[0] - minePos[0];
                                float dy = ordPos[1] - minePos[1];
                                float dz = ordPos[2] - minePos[2];
                                float distSq = dx * dx + dy * dy + dz * dz;

                                if (distSq < range * range)
                                {
                                    float dist = std::sqrt(distSq + 0.0001f);
                                    float pull = (dist * *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassOrdPull1Offset) +
                                                  *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassOrdPull2Offset)) * dt;
                                    float rotPull = dt * *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassOrdRotPullOffset);

                                    auto* ordBytes = reinterpret_cast<uint8_t*>(ordnance);
                                    auto* velocity = reinterpret_cast<float*>(ordBytes + kOrdnanceVelocityOffset);
                                    velocity[0] += dx * pull - velocity[0] * rotPull;
                                    velocity[1] += dy * pull - velocity[1] * rotPull;
                                    velocity[2] += dz * pull - velocity[2] * rotPull;

                                    const float speed = std::sqrt(velocity[0] * velocity[0] + velocity[1] * velocity[1] + velocity[2] * velocity[2]);
                                    *reinterpret_cast<float*>(ordBytes + kOrdnanceSpeedOffset) = speed;
                                    *reinterpret_cast<float*>(ordBytes + kOrdnanceInvSpeedOffset) = (speed == 0.0f) ? 1.0e30f : (1.0f / speed);
                                }
                            }
                        }
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            if (g_BzrFn_MineSimulate)
                g_BzrFn_MineSimulate(magnetMinePtr, dt);
        }

        // Resolved once: the filtered path reproduces stock's detonation block
        // and must not run it on an image where those calls have moved.
        static bool ProximityMineDetonationSitesVerified()
        {
            static int s_verified = -1;
            if (s_verified >= 0)
                return s_verified != 0;

            // Each callee is a guarded row (the debris spawner is the
            // ChunkEffect::CreateChunklet row, called on the ChunkEffect
            // instance); terrain height comes from its resolve pattern.
            const HookEngine::EngineRow rows[] = {
                { "ChunkEffectCreateChunklet", &g_ProximityMineDebrisAddr },
                { "ChunkEffectInstance", &g_ProximityMineDebrisOwnerAddr },
                { "ProximityMineGroundFx", &g_ProximityMineGroundFxAddr },
                { "GameObjectDamageOwner", &g_GameObjectDamageOwnerAddr },
                { "ExplosionClassBuild", &g_ExplosionClassBuildAddr },
                { "ProximityMineNetFlag", &g_ProximityMineNetFlagAddr },
                { "ProximityMineNetNotify", &g_ProximityMineNetNotifyAddr },
            };
            g_TerrainHeightAtAddr = HookEngine::ResolveNamedAddress("Terrain::HeightAt");
            s_verified = (g_TerrainHeightAtAddr != 0 &&
                          HookEngine::BindEngineRows("Proximity mine team filter", rows)) ? 1 : 0;
            if (!s_verified)
            {
                Log(L"[PROXODF] teamFilter disabled: detonation calls do not bind on this build; "
                    L"filtered proximity mines use stock targeting\n");
            }
            return s_verified != 0;
        }

        // Stock ProximityMine::Simulate's detonation block, call for call.
        static void DetonateProximityMineLikeStock(void* proximityMinePtr)
        {
            using FnDebris = void(__thiscall*)(void* owner, const void* position, const float* velocity, int flags);
            using FnGroundFx = void(__cdecl*)(float x, float z, float radius);
            using FnTerrainHeightAt = double(__cdecl*)(double x, double z);
            using FnDamageOwner = void*(__thiscall*)(void* gameObject);
            using FnOwnerObj = void*(__thiscall*)(void* entity);
            using FnExplosionBuild = void(__thiscall*)(void* explosionClass, void* matrix, void* ownerObj);
            using FnNetFlag = bool(__cdecl*)();
            using FnNetNotify = void(__thiscall*)(void* entity);

            __try
            {
                auto* mineBytes = reinterpret_cast<uint8_t*>(proximityMinePtr);
                auto* obj = *reinterpret_cast<uint8_t**>(mineBytes + kGameObjectObjOffset);
                auto* mineClass = *reinterpret_cast<uint8_t**>(mineBytes + kGameObjectClassOffset);
                if (!obj || !mineClass)
                    return;

                double position[3] = {};
                std::memcpy(position, obj + 0x48, sizeof(position));
                const float debrisVelocity[3] = { 0.0f, 15.0f, 0.0f };
                auto debris = reinterpret_cast<FnDebris>(g_ProximityMineDebrisAddr);
                for (int i = 0; i < 20; ++i)
                    debris(reinterpret_cast<void*>(g_ProximityMineDebrisOwnerAddr), position, debrisVelocity, 0);

                const double x = *reinterpret_cast<double*>(obj + 0x48);
                const double z = *reinterpret_cast<double*>(obj + 0x58);
                reinterpret_cast<FnGroundFx>(g_ProximityMineGroundFxAddr)(
                    static_cast<float>(x), static_cast<float>(z), 3.0f);
                *reinterpret_cast<double*>(obj + 0x50) =
                    reinterpret_cast<FnTerrainHeightAt>(g_TerrainHeightAtAddr)(x, z);

                void* ownerObj = obj;
                auto* damageOwner = static_cast<uint8_t*>(
                    reinterpret_cast<FnDamageOwner>(g_GameObjectDamageOwnerAddr)(proximityMinePtr));
                if (damageOwner)
                {
                    void* entity = damageOwner + 0x18;
                    void** vtable = *reinterpret_cast<void***>(entity);
                    ownerObj = reinterpret_cast<FnOwnerObj>(vtable[0x30 / sizeof(void*)])(entity);
                }

                void* explosionClass = *reinterpret_cast<void**>(mineClass + kProximityMineClassExplosionOffset);
                if (explosionClass)
                    reinterpret_cast<FnExplosionBuild>(g_ExplosionClassBuildAddr)(explosionClass, obj + 0x20, ownerObj);

                *reinterpret_cast<uint32_t*>(obj + 0x14) |= 0x280;
                if (reinterpret_cast<FnNetFlag>(g_ProximityMineNetFlagAddr)())
                    reinterpret_cast<FnNetNotify>(g_ProximityMineNetNotifyAddr)(mineBytes + 0x18);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        void RunProximityMineFilteredSimulate(void* proximityMinePtr, float dt)
        {
            if (!proximityMinePtr || !g_BzrFn_GameObjectGetObjByHandle || !g_BzrFn_GameObjectFriendP || !g_BzrFn_GameObjectEnemyP)
            {
                if (g_BzrFn_ProximityMineSimulateOriginal)
                    g_BzrFn_ProximityMineSimulateOriginal(proximityMinePtr, dt);
                return;
            }

            TeamFilterConfig filter = {};
            const bool hasFilter = TryGetTeamFilterForObject(proximityMinePtr, filter, g_ProximityMineTeamFilterCache, "PROXODF");
            if (!hasFilter || !TeamFilterNeedsCustomPath(filter))
            {
                if (g_BzrFn_ProximityMineSimulateOriginal)
                    g_BzrFn_ProximityMineSimulateOriginal(proximityMinePtr, dt);
                return;
            }

            if (!ProximityMineDetonationSitesVerified())
            {
                if (g_BzrFn_ProximityMineSimulateOriginal)
                    g_BzrFn_ProximityMineSimulateOriginal(proximityMinePtr, dt);
                return;
            }

            // Stock ProximityMine::Simulate with the team filter in place of
            // its friend test. Stock: every scan period, a friend in range
            // holds fire, and any other object in range that is moving away
            // from the mine (offset . velocity > 0) sets it off. Here, an
            // object the filter affects can set it off, and an object it
            // spares holds fire only where stock would (a friend).
            bool detonate = false;
            __try
            {
                auto* mineBytes = reinterpret_cast<uint8_t*>(proximityMinePtr);
                float* scanTimer = reinterpret_cast<float*>(mineBytes + kProximityMineArmingTimerOffset);
                *scanTimer -= dt;
                auto* mineObj = *reinterpret_cast<uint8_t**>(mineBytes + kGameObjectObjOffset);
                auto* mineClass = *reinterpret_cast<uint8_t**>(mineBytes + kGameObjectClassOffset);
                if (*scanTimer <= 0.0f && *scanTimer != 0.0f && mineObj && mineClass &&
                    (*reinterpret_cast<uint32_t*>(mineObj + 0x14) & 0x200) == 0)
                {
                    *scanTimer += *reinterpret_cast<float*>(mineClass + kProximityMineClassScanPeriodOffset);
                    const float range = *reinterpret_cast<float*>(mineClass + kProximityMineClassRangeOffset);
                    const float rangeSq = range * range;
                    const float* minePos = reinterpret_cast<float*>(mineBytes + kProximityMinePositionOffset);

                    void* collisionRangeSearch = ReadCraftCollisionGrid();
                    if (collisionRangeSearch && g_BzrFn_CollisionRangeSearch && g_BzrFn_RangeResultsGetNext)
                    {
                        ShieldTowerRangeSearchResults results = {};
                        g_BzrFn_CollisionRangeSearch(
                            collisionRangeSearch,
                            static_cast<double>(minePos[0] - range),
                            static_cast<double>(minePos[2] - range),
                            static_cast<double>(minePos[0] + range),
                            static_cast<double>(minePos[2] + range),
                            &results);

                        uint32_t* handlePtr = nullptr;
                        while (g_BzrFn_RangeResultsGetNext(&results, &handlePtr) != 0)
                        {
                            if (!handlePtr)
                                continue;
                            auto* target = static_cast<uint8_t*>(
                                g_BzrFn_GameObjectGetObjByHandle(static_cast<int>(*handlePtr)));
                            if (!target || target == mineBytes)
                                continue;
                            auto* targetObj = *reinterpret_cast<uint8_t**>(target + kGameObjectObjOffset);
                            if (!targetObj || (*reinterpret_cast<uint32_t*>(targetObj + 0x14) & 0x200) != 0)
                                continue;
                            const float* targetPos = TryCallEntityGetPosition(target);
                            if (!targetPos)
                                continue;
                            const float offset[3] = {
                                targetPos[0] - minePos[0],
                                targetPos[1] - minePos[1],
                                targetPos[2] - minePos[2]
                            };
                            if (offset[0] * offset[0] + offset[1] * offset[1] + offset[2] * offset[2] > rangeSq)
                                continue;

                            if (TeamFilterShouldAffectObject(proximityMinePtr, target, filter))
                            {
                                const float* velocity = reinterpret_cast<float*>(target + kGameObjectVelocityOffset);
                                if (offset[0] * velocity[0] + offset[1] * velocity[1] + offset[2] * velocity[2] > 0.0f)
                                    detonate = true;
                            }
                            else if (g_BzrFn_GameObjectFriendP(proximityMinePtr, target))
                            {
                                detonate = false;
                                break;
                            }
                        }
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                detonate = false;
            }

            if (detonate)
                DetonateProximityMineLikeStock(proximityMinePtr);

            if (g_BzrFn_MineSimulate)
                g_BzrFn_MineSimulate(proximityMinePtr, dt);
        }
    }

}
