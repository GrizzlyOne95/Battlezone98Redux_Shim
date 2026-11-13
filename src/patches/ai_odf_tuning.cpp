// ai_odf_tuning.cpp
// BZR Open Shim - AI ODF tuning and the legacy AI behaviours it drives:
// attack-task kiting and stuck recovery, scrap path scoring, scavenger
// retarget, CalcRange(Craft) and the DoSubTask retarget period, with the
// per-ODF readers behind them, split out of bzr_hooks.cpp.
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
    FnCalcRangeCraft g_BzrFn_CalcRangeCraft = nullptr;
    FnAttackTaskDoState g_BzrFn_AttackTaskDoState = nullptr;
    FnTerrainGetIntersection g_BzrFn_TerrainGetIntersection = nullptr;
    FnProcessDoSubTask g_BzrFn_OffensiveProcessDoSubTask = nullptr;
    FnProcessDoSubTask g_BzrFn_GunTowerProcessDoSubTask = nullptr;
    FnProcessDoSubTask g_BzrFn_TurretTankProcessDoSubTask = nullptr;
    FnGetGameTime g_BzrFn_GetGameTime = nullptr;
    FnFindPlanForObject g_BzrFn_FindPlanForObject = nullptr;
    FnAiPathGetLength g_BzrFn_AiPathGetLength = nullptr;
    FnAiPathDelete g_BzrFn_AiPathDelete = nullptr;
    FnRecycleTaskDoGotoScrap g_BzrFn_RecycleTaskDoGotoScrap = nullptr;

    // Trace switches consulted on per-unit, per-tick AI paths (the DoSubTask
    // path read three of them per unit per tick). EnvFlagEnabled reads the
    // process environment, which nothing changes after startup, so each is
    // read once and latched.
    static bool TraceLegacyAiEnabled()
    {
        static const bool s_value = EnvFlagEnabled("OPENSHIM_TRACE_LEGACY_AI");
        return s_value;
    }

    // Legacy transitions fire per craft per tick, so cap the trace.
    static volatile long g_LegacyAiTraceBudget = 2000;
    static bool LegacyAiTraceAllowed()
    {
        return TraceLegacyAiEnabled() && InterlockedDecrement(&g_LegacyAiTraceBudget) >= 0;
    }

    static bool TraceAiRangeEnabled()
    {
        static const bool s_value = EnvFlagEnabled("OPENSHIM_TRACE_AI_RANGE");
        return s_value;
    }

    static bool TraceAiUnitTuningEnabled()
    {
        static const bool s_value = EnvFlagEnabled("OPENSHIM_TRACE_AI_UNIT_TUNING");
        return s_value;
    }

    static bool TraceBomberRangeEnabled()
    {
        static const bool s_value = EnvFlagEnabled("OPENSHIM_TRACE_BOMBER_RANGE");
        return s_value;
    }

    static bool TraceArtilleryMaskEnabled()
    {
        static const bool s_value = EnvFlagEnabled("OPENSHIM_TRACE_ARTILLERY_MASK");
        return s_value;
    }

    static bool TraceWeaponMaskEnabled()
    {
        static const bool s_value = EnvFlagEnabled("OPENSHIM_TRACE_WEAPON_MASK");
        return s_value;
    }

    namespace Hooks
    {
        AiTuningCache g_AiTuningCache = {};
        bool g_CalcRangeCraftHookInstalled = false;
        bool g_ScrapPathScoreHookInstalled = false;
        InlineDetour32 g_RecycleTaskDoGotoScrapDetour = {};
        bool g_ScrapRetargetHookInstalled = false;
        InlineDetour32 g_AttackTaskDoStateDetour = {};
        bool g_AttackTaskDoStateHookInstalled = false;
        bool g_RetargetPeriodHooksInstalled = false;
        std::unordered_map<uintptr_t, RetargetPeriodState> g_RetargetPeriodStateByProcess = {};
        std::unordered_map<uintptr_t, ScrapPathFailureState> g_ScrapPathFailuresByObject = {};
        std::unordered_map<uintptr_t, ScrapRetargetState> g_ScrapRetargetStateByTask = {};
        std::unordered_map<uintptr_t, AiUnitTuningOverride> g_AiUnitTuningOverridesByObject = {};
        std::unordered_map<uintptr_t, CombatKiteState> g_CombatKiteStateByObject = {};
        volatile long g_AiUnitTuningTraceBudget = 64;
        volatile long g_CombatKiteTraceBudget = 256;
        volatile long g_ScrapPathTraceBudget = 128;

        constexpr size_t kCalcRangeCraftDetourLen = 9;

        // RecycleTask::InitLookingForScrap computes a stock squared-distance
        // score at this one call site after all team/material/region filters.
        // Replacing only this call keeps the rest of the Redux task intact.
        uint32_t g_RecycleTaskScrapDistanceCallAddr = 0;

        uint32_t g_Dist3DSquaredAddr = 0;

        uint32_t g_FindPlanForObjectAddr = 0;

        uint32_t g_AiPathGetLengthAddr = 0;

        uint32_t g_AiPathDeleteAddr = 0;

        uint32_t g_RecycleTaskDoGotoScrapAddr = 0;

        constexpr size_t kRecycleTaskDoGotoScrapDetourLen = 7;

        constexpr size_t kRecycleTaskOwnerOffset = 0x2C;

        constexpr size_t kRecycleTaskSubtaskOffset = 0x30;

        constexpr size_t kRecycleTaskScrapHandleOffset = 0x40;

        constexpr size_t kRecycleTaskNextStateOffset = 0x4C;

        constexpr size_t kRecycleTaskCallerThisLocalOffset = 0x20;

        constexpr size_t kRecycleTaskCallerCandidateLocalOffset = 0x28;

        constexpr size_t kAiPathTypeOffset = 0x10;

        constexpr int kAiPathBadPathType = 3;

        constexpr float kScrapRejectedScore = 1.0e30f;

        constexpr float kScrapRetargetPickupGuardDistance = 20.0f;

        uint32_t g_AttackTaskDoStateEntryAddr = 0;

        constexpr size_t kAttackTaskDoStateDetourLen = 9;

        constexpr size_t kAttackTaskCurStateOffset = 0x08;

        constexpr size_t kAttackTaskNextStateOffset = 0x0C;

        constexpr size_t kAttackTaskCraftOffset = 0x10;

        constexpr size_t kAttackTaskTargetOffset = 0x18;

        constexpr size_t kAttackTaskCloseSqOffset = 0x9C;

        constexpr size_t kAttackTaskRangeSqOffset = 0xA0;

        constexpr int kAttackTaskFiringState = 5;

        // AttackTask states the legacy (1.4) profile rewrites. Numbers are
        // the same in 1.4 (FUN_0040cde0) and Redux (FUN_00478a50).
        constexpr int kAttackTaskSearchState = 2;

        constexpr int kAttackTaskStuckState = 3;

        constexpr int kAttackTaskSlideState = 7;

        constexpr int kAttackTaskStandState = 8;

        constexpr int kAttackTaskFleeState = 9;

        constexpr int kAttackTaskBlastState = 10;

        constexpr int kAttackTaskDoneState = 13;

        // Written to the current state while stock runs the legacy flee tick:
        // outside the switch's 2..12 range, so stock runs only its prolog and
        // its tail, and the tail holds fire because the prolog cleared +0xC4.
        constexpr int kAttackTaskLegacyPlaceholderState = 100;

        constexpr int kAttackTaskNextUnsetSentinel = 0x4C454731;

        constexpr size_t kAttackTaskSlideForceOffset = 0x4C;

        constexpr size_t kAttackTaskAbleToHitOffset = 0xC4;

        constexpr size_t kAttackTaskStartTimeOffset = 0x100;

        constexpr size_t kAttackTaskFleeFromHandleOffset = 0x13C;

        // Read by the getter FUN_0046d040 that stock stand and blast compare
        // with the task start time to detect a fresh hit.
        constexpr size_t kCraftLastDamageTimeOffset = 0x1E8;

        // 1.4 and Redux share these: 1.4 _DAT_005e6e9c = 5.0 and
        // _DAT_005e6ea4 = 5625.0; Redux 0x8a285c = 5.0 and 0x8a2e00 = 5625.0.
        constexpr float kLegacySlideMinForce = 5.0f;

        constexpr float kLegacyFleeRangeSq = 5625.0f;

        // Process vtables are rows, each checked by RTTI name below before its
        // slot is touched. Slot 11
        // owns the target-acquisition state method which schedules the stock
        // 7-10 second retry after a failed enemy search.
        constexpr size_t kProcessDoSubTaskVtableSlot = 11;

        constexpr float kGlobalRetargetPeriod = 0.75f;

        uint32_t g_ArtilleryProcessVtableAddr = 0;

        uint32_t g_BomberProcessVtableAddr = 0;

        uint32_t g_GechProcessVtableAddr = 0;

        uint32_t g_OffensiveProcessVtableAddr = 0;

        uint32_t g_PersonProcessVtableAddr = 0;

        uint32_t g_RocketTankProcessVtableAddr = 0;

        uint32_t g_ScoutProcessVtableAddr = 0;

        uint32_t g_SoldierProcessVtableAddr = 0;

        uint32_t g_TankProcessVtableAddr = 0;

        uint32_t g_WingmanProcessVtableAddr = 0;

        uint32_t g_GunTowerProcessVtableAddr = 0;

        uint32_t g_TurretTankProcessVtableAddr = 0;

        uint32_t g_OffensiveProcessDoSubTaskAddr = 0;

        uint32_t g_GunTowerProcessDoSubTaskAddr = 0;

        uint32_t g_TurretTankProcessDoSubTaskAddr = 0;

        uint32_t g_GetGameTimeAddr = 0;

        // Stock ODFs name the *Friend/*Enemy subclasses (aiName/aiName2), and
        // each subclass has its own vtable copy, so the base vtables above
        // alone never reach a stock unit. Slot 11 of each is its base's
        // DoSubTask (ai_subclass_retarget_20261103.md). TurretTankFriend/Enemy
        // are hooked by the turret range refresh below.
        struct AiSubclassVtable
        {
            const char* row;
            const wchar_t* label;
            const char* rttiName;
            bool gunTower;
        };
        constexpr AiSubclassVtable kRetargetSubclassVtables[] =
        {
            { "GunTowerFriendVtable", L"GunTowerFriend", ".?AVGunTowerFriend@@", true },
            { "GunTowerEnemyVtable", L"GunTowerEnemy", ".?AVGunTowerEnemy@@", true },
            { "TankFriendVtable", L"TankFriend", ".?AVTankFriend@@", false },
            { "TankEnemyVtable", L"TankEnemy", ".?AVTankEnemy@@", false },
            { "RocketTankFriendVtable", L"RocketTankFriend", ".?AVRocketTankFriend@@", false },
            { "RocketTankEnemyVtable", L"RocketTankEnemy", ".?AVRocketTankEnemy@@", false },
            { "ScoutFriendVtable", L"ScoutFriend", ".?AVScoutFriend@@", false },
            { "ScoutEnemyVtable", L"ScoutEnemy", ".?AVScoutEnemy@@", false },
            { "PersonFriendVtable", L"PersonFriend", ".?AVPersonFriend@@", false },
            { "PersonEnemyVtable", L"PersonEnemy", ".?AVPersonEnemy@@", false },
            { "SoldierFriendVtable", L"SoldierFriend", ".?AVSoldierFriend@@", false },
            { "SoldierEnemyVtable", L"SoldierEnemy", ".?AVSoldierEnemy@@", false },
            { "ArtilleryFriendVtable", L"ArtilleryFriend", ".?AVArtilleryFriend@@", false },
            { "ArtilleryEnemyVtable", L"ArtilleryEnemy", ".?AVArtilleryEnemy@@", false },
            { "GechFriendVtable", L"GechFriend", ".?AVGechFriend@@", false },
            { "GechEnemyVtable", L"GechEnemy", ".?AVGechEnemy@@", false },
            { "BomberFriendVtable", L"BomberFriend", ".?AVBomberFriend@@", false },
            { "BomberEnemyVtable", L"BomberEnemy", ".?AVBomberEnemy@@", false },
        };
        constexpr size_t kRetargetSubclassCount =
            sizeof(kRetargetSubclassVtables) / sizeof(kRetargetSubclassVtables[0]);
        uint32_t g_RetargetSubclassVtableAddrs[kRetargetSubclassCount] = {};

        // TurretTankProcess (and its Friend/Enemy subclasses) caches its
        // engage range only in Init/PostLoad. UnitTask::Execute re-runs
        // CalcRange whenever the craft's weapon signature changes; the
        // turret refresh below does the same. Offsets are from Init
        // 0x005F6B50 (turret_charge_range_cache_20261103.md).
        using FnCraftWeaponSignature = uint32_t(__cdecl*)(void* craft);
        FnCraftWeaponSignature g_BzrFn_CraftWeaponSignature = nullptr;
        uint32_t g_CraftWeaponSignatureAddr = 0;
        uint32_t g_TurretTankFriendVtableAddr = 0;
        uint32_t g_TurretTankEnemyVtableAddr = 0;
        bool g_TurretRangeRefreshHooksInstalled = false;
        std::unordered_map<uintptr_t, uint32_t> g_TurretRangeSignatureByProcess = {};

        constexpr size_t kTurretCloseSqOffset = 0x68;
        constexpr size_t kTurretRangeSqOffset = 0x6C;
        constexpr size_t kTurretTimeOffset = 0x70;
        constexpr size_t kTurretWeaponOffset = 0x74;
        constexpr size_t kTurretRangePerTimeOffset = 0x78;
        constexpr size_t kTurretTimePerRangeOffset = 0x7C;

        constexpr size_t kUnitProcessNextEnemyCheckOffset = 0x30;

        constexpr size_t kUnitProcessObjectOffset = 0x34;

        static volatile long g_ArtilleryMaskTraceBudget = 400;

        static volatile long g_BomberRangeTraceBudget = 200;

        static InlineDetour32 g_CalcRangeCraftDetour = {};

        // The AttackTask endpoints are GameObjects; their world transform lives
        // on the _OBJ76 the GameObject points at, not inline. Reading it inline
        // returned a constant (0, 0, -1) for every craft, so the craft-target
        // distance was always zero and kiting never engaged.
        static bool TryGetGameObjectPosition(void* objectPtr,
                                             double& outX,
                                             double& outY,
                                             double& outZ)
        {
            float position[3] = {};
            if (!TryGetGameObjectWorldPosition(objectPtr, position))
                return false;
            outX = position[0];
            outY = position[1];
            outZ = position[2];
            return std::isfinite(outX) && std::isfinite(outY) && std::isfinite(outZ);
        }

        static bool TryReadAttackTaskEndpoints(const uint8_t* taskBytes,
                                               void*& craft,
                                               void*& target)
        {
            craft = nullptr;
            target = nullptr;
            if (!taskBytes)
                return false;
            __try
            {
                craft = *reinterpret_cast<void* const*>(taskBytes + kAttackTaskCraftOffset);
                target = *reinterpret_cast<void* const*>(taskBytes + kAttackTaskTargetOffset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                craft = nullptr;
                target = nullptr;
                return false;
            }
        }

        static bool TryRaiseAttackTaskRangeSq(uint8_t* taskBytes,
                                              float engageSq,
                                              float& previousRangeSq,
                                              bool& changed)
        {
            previousRangeSq = 0.0f;
            changed = false;
            if (!taskBytes)
                return false;
            __try
            {
                float& rangeSq = *reinterpret_cast<float*>(
                    taskBytes + kAttackTaskRangeSqOffset);
                previousRangeSq = rangeSq;
                if (!std::isfinite(rangeSq) || rangeSq < engageSq)
                {
                    rangeSq = engageSq;
                    changed = true;
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryReadAttackTaskRangeSq(const uint8_t* taskBytes, float& rangeSq)
        {
            rangeSq = 0.0f;
            if (!taskBytes)
                return false;
            __try
            {
                rangeSq = *reinterpret_cast<const float*>(
                    taskBytes + kAttackTaskRangeSqOffset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                rangeSq = 0.0f;
                return false;
            }
        }

        static bool TryApplyAttackTaskFiringOverride(uint8_t* taskBytes,
                                                     float movementCloseSq,
                                                     float& savedCloseSq)
        {
            savedCloseSq = 0.0f;
            if (!taskBytes)
                return false;
            __try
            {
                savedCloseSq = *reinterpret_cast<float*>(
                    taskBytes + kAttackTaskCloseSqOffset);
                *reinterpret_cast<float*>(taskBytes + kAttackTaskCloseSqOffset) =
                    movementCloseSq;
                *reinterpret_cast<int*>(taskBytes + kAttackTaskCurStateOffset) =
                    kAttackTaskFiringState;
                *reinterpret_cast<int*>(taskBytes + kAttackTaskNextStateOffset) =
                    kAttackTaskFiringState;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryRestoreAttackTaskFiringOverride(uint8_t* taskBytes,
                                                       float savedCloseSq)
        {
            if (!taskBytes)
                return false;
            __try
            {
                *reinterpret_cast<float*>(taskBytes + kAttackTaskCloseSqOffset) =
                    savedCloseSq;
                *reinterpret_cast<int*>(taskBytes + kAttackTaskNextStateOffset) =
                    kAttackTaskFiringState;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void TryApplyAttackTaskStrafeControl(void* craft,
                                                    int strafeDirection,
                                                    float kiteStrafe,
                                                    bool reverseLos)
        {
            if (!craft)
                return;
            __try
            {
                void* vehicle = *reinterpret_cast<void**>(
                    reinterpret_cast<uint8_t*>(craft) + 0x230);
                if (!vehicle)
                    return;
                float* control = reinterpret_cast<float*>(
                    reinterpret_cast<uint8_t*>(vehicle) + 0xC4);
                if (std::fabs(control[2]) > 0.001f || std::fabs(control[3]) > 0.001f)
                {
                    control[2] = static_cast<float>(strafeDirection) * kiteStrafe;
                    if (!reverseLos)
                        control[3] = 0.0f;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        // Legacy14 helper: determine if this craft should use 1.4 semantics.
        // Checks per-unit override first, then per-ODF aiName legacy flag.
        static bool IsLegacyAiCraft(void* craft)
        {
            if (!craft) return false;
            const auto unitIt = g_AiUnitTuningOverridesByObject.find(reinterpret_cast<uintptr_t>(craft));
            if (unitIt != g_AiUnitTuningOverridesByObject.end() && unitIt->second.hasLegacyAi)
                return unitIt->second.legacyAi;
            AiTuningConfig odfCfg = {};
            const bool hasOdfCfg = TryGetAiTuningForObject(craft, odfCfg);
            if (hasOdfCfg && odfCfg.legacyAiRole)
                return true;
            // The global option covers every AttackTask user, as 1.4 did.
            // odfCfg is filled even when parsed is false (opt-out only).
            if (!g_LegacyTankAiActive || odfCfg.legacyAiOptOut)
                return false;
            if (!g_LegacyTankAiAiTeamsOnly)
                return true;
            // Mode 2 skips the local player's team; an unreadable craft team
            // counts as not the player's.
            int playerTeam = 1;
            if (g_BzrFn_GetPlayerHandle && g_BzrFn_GetTeamNum)
            {
                const int playerHandle = g_BzrFn_GetPlayerHandle();
                const int team = playerHandle > 0 ? g_BzrFn_GetTeamNum(playerHandle) : 0;
                if (team > 0)
                    playerTeam = team;
            }
            const int craftTeam = GetGameObjectActualTeam(craft);
            return craftTeam == INT_MIN || craftTeam != playerTeam;
        }

        static bool TryGetTaskState(uint8_t* taskBytes, int& outState, int& outNextState, float& outStartTime)
        {
            if (!taskBytes) return false;
            __try
            {
                outState = *reinterpret_cast<int*>(taskBytes + kAttackTaskCurStateOffset);
                outNextState = *reinterpret_cast<int*>(taskBytes + kAttackTaskNextStateOffset);
                // startTime is at +0x100 in Redux (was +0xD4 in 1.4)
                outStartTime = *reinterpret_cast<float*>(taskBytes + kAttackTaskStartTimeOffset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Entity::GetPosition, vtable slot 3 of the interface at object+0x18.
        // Stock IsStuck and ProximityMine::Simulate both read positions this way.
        using FnEntityGetPosition = const float*(__thiscall*)(void* entity);
        const float* TryCallEntityGetPosition(void* gameObject)
        {
            if (!gameObject)
                return nullptr;
            __try
            {
                void* entity = reinterpret_cast<uint8_t*>(gameObject) + 0x18;
                void** vtable = *reinterpret_cast<void***>(entity);
                if (!vtable || !vtable[3])
                    return nullptr;
                return reinterpret_cast<FnEntityGetPosition>(vtable[3])(entity);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        // The AttackTask helpers the 1.4 slide and flee call. Each comes from
        // an engine_addresses row; if any row fails to bind, the legacy slide
        // and flee stay stock.
        using FnAttackTaskThiscallBool = bool(__thiscall*)(void* task);
        using FnAttackTaskThiscallVoid = void(__thiscall*)(void* task);
        using FnSidewaysAndClose = bool(__cdecl*)(void* craftInfo, void* targetInfo);
        using FnIsBuildingClass = int(__cdecl*)(void* targetInfo);
        using FnDistanceSquared2D = float(__cdecl*)(const float* a, const float* b);

        struct LegacyAttackHelpers
        {
            FnAttackTaskThiscallBool isStuck = nullptr;
            FnAttackTaskThiscallVoid doSlide = nullptr;
            FnAttackTaskThiscallVoid doFlee = nullptr;
            FnSidewaysAndClose sidewaysAndClose = nullptr;
            FnIsBuildingClass isBuilding = nullptr;
            FnDistanceSquared2D distanceSquared2D = nullptr;
        };

        static const LegacyAttackHelpers* GetLegacyAttackHelpers()
        {
            static LegacyAttackHelpers s_helpers;
            static int s_bound = -1;
            if (s_bound < 0)
            {
                s_helpers.isStuck = reinterpret_cast<FnAttackTaskThiscallBool>(
                    HookEngine::EngineAddress("AttackTaskIsStuck"));
                s_helpers.doSlide = reinterpret_cast<FnAttackTaskThiscallVoid>(
                    HookEngine::EngineAddress("AttackTaskDoSlide"));
                s_helpers.doFlee = reinterpret_cast<FnAttackTaskThiscallVoid>(
                    HookEngine::EngineAddress("AttackTaskDoFlee"));
                s_helpers.sidewaysAndClose = reinterpret_cast<FnSidewaysAndClose>(
                    HookEngine::EngineAddress("AttackTaskSidewaysAndClose"));
                s_helpers.isBuilding = reinterpret_cast<FnIsBuildingClass>(
                    HookEngine::EngineAddress("AttackTaskIsBuildingClass"));
                s_helpers.distanceSquared2D = reinterpret_cast<FnDistanceSquared2D>(
                    HookEngine::EngineAddress("DistanceSquared2D"));
                s_bound = s_helpers.isStuck && s_helpers.doSlide && s_helpers.doFlee &&
                    s_helpers.sidewaysAndClose && s_helpers.isBuilding && s_helpers.distanceSquared2D;
                if (!s_bound)
                {
                    Log(L"[LEGACY] 1.4 slide and flee disabled: an AttackTask helper row does not bind\n");
                    MarkOptionHookFailed("LegacyTankAi", "Unavailable: Legacy tank AI did not hook on this game build (see openshim.log).");
                }
            }
            return s_bound ? &s_helpers : nullptr;
        }

        // Entity vtable slot 12 (+0x30) of the interface at object+0x18: the
        // class info stock passes to SidewaysAndClose and IsBuildingClass.
        void* TryCallEntityClassInfo(void* gameObject)
        {
            if (!gameObject)
                return nullptr;
            __try
            {
                void* entity = reinterpret_cast<uint8_t*>(gameObject) + 0x18;
                void** vtable = *reinterpret_cast<void***>(entity);
                if (!vtable || !vtable[12])
                    return nullptr;
                using FnEntityClassInfo = void*(__thiscall*)(void* entity);
                return reinterpret_cast<FnEntityClassInfo>(vtable[12])(entity);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        static void SetAttackTaskNextState(uint8_t* taskBytes, int next)
        {
            *reinterpret_cast<int*>(taskBytes + kAttackTaskNextStateOffset) = next;
        }

        // 1.4 slide (FUN_0040cde0 case 7) keeps sliding while it can hit and
        // blasts only once the slide force drops under 5. Redux slide (case 7
        // at 0x00478cec) blasts as soon as it can hit and leaves for search
        // after 10 s. Stock has already run this tick, firing if able, so
        // finish the two branches where they differ:
        //   next 2 while in range and not a building: the 10 s timeout. 1.4
        //     has none, so carry on with its stuck, sideways and slide tests.
        //   next 10 with the able flag set and not a building: stock's able,
        //     not stuck, not sideways branch. Slide instead.
        // Out of range (2), target class (10), stuck (3), sideways (8) and
        // the not-able slide already match 1.4. 1.4's class test is
        // 1.4 never branches on the able flag here, so the timeout branch
        // tests sideways whether or not it can hit, as 1.4 does.
        // Not ported: Redux's class test (0x00477D70) also takes class 10,
        // where 1.4's takes {2,5,7}, so class-10 targets keep Redux's blast;
        // and within 10 s, a craft that cannot hit slides on without 1.4's
        // sideways test.
        static void ApplyLegacySlide(const LegacyAttackHelpers& helpers,
                                     uint8_t* taskBytes,
                                     void* taskPtr,
                                     void* craft,
                                     int nextAfter)
        {
            if (nextAfter != kAttackTaskSearchState && nextAfter != kAttackTaskBlastState)
                return;

            void* target = *reinterpret_cast<void**>(taskBytes + kAttackTaskTargetOffset);
            void* targetInfo = TryCallEntityClassInfo(target);
            void* craftInfo = TryCallEntityClassInfo(craft);
            if (!targetInfo || !craftInfo || helpers.isBuilding(targetInfo) != 0)
                return;

            if (nextAfter == kAttackTaskSearchState)
            {
                const float* craftPos = TryCallEntityGetPosition(craft);
                const float* targetPos = TryCallEntityGetPosition(target);
                if (!craftPos || !targetPos)
                    return;
                const float rangeSq = *reinterpret_cast<float*>(taskBytes + kAttackTaskRangeSqOffset);
                if (helpers.distanceSquared2D(craftPos, targetPos) > rangeSq)
                    return;
                if (helpers.isStuck(taskPtr))
                {
                    SetAttackTaskNextState(taskBytes, kAttackTaskStuckState);
                    return;
                }
                if (helpers.sidewaysAndClose(craftInfo, targetInfo))
                {
                    SetAttackTaskNextState(taskBytes, kAttackTaskStandState);
                    return;
                }
            }
            else if (*(taskBytes + kAttackTaskAbleToHitOffset) == 0)
            {
                return;
            }

            helpers.doSlide(taskPtr);
            const auto* force = reinterpret_cast<const float*>(taskBytes + kAttackTaskSlideForceOffset);
            const float forceSq = force[0] * force[0] + force[1] * force[1] + force[2] * force[2];
            const int next = forceSq < kLegacySlideMinForce * kLegacySlideMinForce
                ? kAttackTaskBlastState
                : kAttackTaskSlideState;
            SetAttackTaskNextState(taskBytes, next);
            if (next != kAttackTaskSlideState && LegacyAiTraceAllowed())
                Log(L"[LEGACY] slide craft=0x%08X stock next %d => %d\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)), nextAfter, next);
        }

        static void CallStockAttackTaskDoState(void* taskPtr);

        // Redux UnitTask::DoStand (0x006057e0) pushes the craft away from the
        // target while targetDistSq < closeSq; 1.4 stand (FUN_0046e6b0) has no
        // such term, so a legacy craft reversed briefly before sliding. The
        // DoState stand call site is redirected here, and the legacy path names
        // its task around its stock call so closeSq reads 0 inside DoStand
        // only; UpdateWeapon's closeSq checks after the switch are unchanged.
        using FnUnitTaskDoStand = void(__thiscall*)(void* task);
        static FnUnitTaskDoStand g_BzrFn_UnitTaskDoStand = nullptr;
        static void* g_LegacyStandNoBackOffTask = nullptr;

        static void __fastcall AttackTaskDoStandSiteHook(void* task)
        {
            if (task != g_LegacyStandNoBackOffTask)
            {
                g_BzrFn_UnitTaskDoStand(task);
                return;
            }
            auto* closeSq = reinterpret_cast<float*>(
                static_cast<uint8_t*>(task) + kAttackTaskCloseSqOffset);
            const float savedCloseSq = *closeSq;
            *closeSq = 0.0f;
            g_BzrFn_UnitTaskDoStand(task);
            *closeSq = savedCloseSq;
        }

        static void InstallLegacyStandSiteHook()
        {
            uint32_t doStand = 0, standSite = 0;
            const HookEngine::EngineRow rows[] = {
                { "UnitTaskDoStand", &doStand },
                { "AttackTaskDoStandCall", &standSite },
            };
            if (!HookEngine::BindEngineRows("Legacy stand", rows))
                return;
            // The row starts at "mov ecx,[ebp-4]"; the call is 3 bytes in.
            g_BzrFn_UnitTaskDoStand = reinterpret_cast<FnUnitTaskDoStand>(doStand);
            if (!RedirectCallTarget(standSite + 3u, doStand,
                                    reinterpret_cast<uintptr_t>(&AttackTaskDoStandSiteHook)))
            {
                g_BzrFn_UnitTaskDoStand = nullptr;
                Log(L"[LEGACY] stand call site 0x%08X did not match; stand keeps the Redux back-off\n",
                    standSite + 3u);
            }
        }

        // 1.4 flee (FUN_0040cde0 case 9) holds fire and has no timer: it
        // leaves when the attacker is gone or 75 m away (to slide) or when
        // stuck (to blast). Redux flee (case 9 at 0x00478f5c) shoots the
        // attacker and gives up after 3 s. Run stock with a placeholder state
        // so only its prolog (target, avoidance, done checks) and its tail
        // (weapon update, holding fire) run, then do the 1.4 flee.
        static void RunLegacyFlee(const LegacyAttackHelpers& helpers,
                                  uint8_t* taskBytes,
                                  void* taskPtr,
                                  void* craft)
        {
            auto* cur = reinterpret_cast<int*>(taskBytes + kAttackTaskCurStateOffset);
            auto* next = reinterpret_cast<int*>(taskBytes + kAttackTaskNextStateOffset);
            const int nextBefore = *next;
            *cur = kAttackTaskLegacyPlaceholderState;
            *next = kAttackTaskNextUnsetSentinel;
            CallStockAttackTaskDoState(taskPtr);
            if (*cur == kAttackTaskLegacyPlaceholderState)
                *cur = kAttackTaskFleeState;
            if (*next != kAttackTaskNextUnsetSentinel)
                return; // the prolog decided (target gone, task done)
            *next = nextBefore;
            if (*cur == kAttackTaskDoneState)
                return;

            const int fleeFromHandle = *reinterpret_cast<int*>(taskBytes + kAttackTaskFleeFromHandleOffset);
            void* fleeFrom = GameObjectFromHandleGog(fleeFromHandle);
            const float* craftPos = TryCallEntityGetPosition(craft);
            const float* fleeFromPos = TryCallEntityGetPosition(fleeFrom);
            const char* exitReason = nullptr;
            float fleeDistSq = -1.0f;
            if (fleeFrom && craftPos && fleeFromPos)
                fleeDistSq = helpers.distanceSquared2D(craftPos, fleeFromPos);
            if (!fleeFrom || !craftPos || !fleeFromPos)
            {
                *next = kAttackTaskSlideState;
                exitReason = "attacker gone";
            }
            else if (fleeDistSq > kLegacyFleeRangeSq)
            {
                *next = kAttackTaskSlideState;
                exitReason = "75 m clear";
            }
            else if (helpers.isStuck(taskPtr))
            {
                *next = kAttackTaskBlastState;
                exitReason = "stuck";
            }
            if (exitReason)
            {
                if (LegacyAiTraceAllowed())
                {
                    char odfToken[kProducerBuildMenuTokenLen + 1] = {};
                    if (fleeFrom)
                        TryGetObjectOdfToken(fleeFrom, odfToken);
                    Log(L"[LEGACY] flee craft=0x%08X from=0x%08X odf=%hs dist=%.1f %S => %d\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                        static_cast<uint32_t>(fleeFromHandle), odfToken[0] ? odfToken : "-",
                        static_cast<double>(fleeDistSq >= 0.0f ? std::sqrt(fleeDistSq) : -1.0f),
                        exitReason, *next);
                }
                return;
            }
            // Stock points the task's target at the attacker before DoFlee;
            // the next tick's prolog resolves the real target again.
            *reinterpret_cast<void**>(taskBytes + kAttackTaskTargetOffset) = fleeFrom;
            helpers.doFlee(taskPtr);
        }

        // OPENSHIM_PROFILE_ATTACK_TASK=1: splits this hook's time into the
        // stock DoState it wraps and OpenShim's own work, logged every 5 s.
        // Latched at install so the disabled path is one branch.
        static bool g_AttackTaskProfileEnabled = false;
        static LONGLONG g_AttackTaskProfileStockTicks = 0;

        static void CallStockAttackTaskDoState(void* taskPtr)
        {
            if (!g_AttackTaskProfileEnabled)
            {
                g_BzrFn_AttackTaskDoState(taskPtr);
                return;
            }
            LARGE_INTEGER before;
            LARGE_INTEGER after;
            QueryPerformanceCounter(&before);
            g_BzrFn_AttackTaskDoState(taskPtr);
            QueryPerformanceCounter(&after);
            g_AttackTaskProfileStockTicks += after.QuadPart - before.QuadPart;
        }

        static void ReadLegacySnapshotFields(uint8_t* taskBytes, void* craft, float& lastDamage,
                                             float& forceMag, int& able, float& range)
        {
            __try
            {
                lastDamage = *reinterpret_cast<float*>(
                    reinterpret_cast<uint8_t*>(craft) + kCraftLastDamageTimeOffset);
                const auto* force = reinterpret_cast<const float*>(taskBytes + kAttackTaskSlideForceOffset);
                forceMag = std::sqrt(force[0] * force[0] + force[1] * force[1] + force[2] * force[2]);
                able = *(taskBytes + kAttackTaskAbleToHitOffset);
                range = std::sqrt(*reinterpret_cast<float*>(taskBytes + kAttackTaskRangeSqOffset));
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
        }

        // OPENSHIM_TRACE_LEGACY_AI: one line per legacy craft every 0.5 s with
        // what the state machine reads, so a stuck state can be explained.
        static void TraceLegacySnapshot(const LegacyAttackHelpers* helpers,
                                        uint8_t* taskBytes,
                                        void* craft,
                                        int curBefore,
                                        int nextStock)
        {
            static volatile long s_budget = 1500;
            static std::unordered_map<uintptr_t, float> s_lastLogByCraft;
            if (!TraceLegacyAiEnabled() || !g_BzrFn_GetGameTime || s_budget <= 0)
                return;
            const float now = g_BzrFn_GetGameTime();
            float& last = s_lastLogByCraft[reinterpret_cast<uintptr_t>(craft)];
            if (now - last < 0.5f && now >= last)
                return;
            last = now;
            if (InterlockedDecrement(&s_budget) < 0)
                return;

            int cur = 0, next = 0;
            float start = 0.0f;
            TryGetTaskState(taskBytes, cur, next, start);
            float lastDamage = -1.0f, forceMag = -1.0f, dist = -1.0f, range = -1.0f;
            int able = -1;
            ReadLegacySnapshotFields(taskBytes, craft, lastDamage, forceMag, able, range);
            void* target = *reinterpret_cast<void**>(taskBytes + kAttackTaskTargetOffset);
            const float* craftPos = TryCallEntityGetPosition(craft);
            const float* targetPos = TryCallEntityGetPosition(target);
            if (helpers && craftPos && targetPos)
                dist = std::sqrt(helpers->distanceSquared2D(craftPos, targetPos));
            char odfToken[kProducerBuildMenuTokenLen + 1] = {};
            TryGetObjectOdfToken(craft, odfToken);
            Log(L"[LEGACY] snap craft=0x%08X odf=%hs cur %d->%d stock %d final %d able=%d force=%.2f "
                L"dist=%.1f range=%.1f start=%.2f now=%.2f hit=%.2f\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                odfToken[0] ? odfToken : "-", curBefore, cur, nextStock, next, able,
                static_cast<double>(forceMag), static_cast<double>(dist), static_cast<double>(range),
                static_cast<double>(start), static_cast<double>(now), static_cast<double>(lastDamage));
        }

        static void AttackTaskDoStateTuningBody(void* taskPtr)
        {
            if (!g_BzrFn_AttackTaskDoState || !taskPtr)
                return;

            auto* taskBytes = reinterpret_cast<uint8_t*>(taskPtr);
            void* craft = nullptr;
            void* target = nullptr;
            if (!TryReadAttackTaskEndpoints(taskBytes, craft, target))
            {
                CallStockAttackTaskDoState(taskPtr);
                return;
            }

            // Legacy14 check is per-craft, not per-target. We need it even when no per-unit kite tuning exists.
            const bool isLegacyCraft = IsLegacyAiCraft(craft);

            // Preserve legacy path even when kite tuning absent.
            // Kite path still requires per-unit tuning; legacy does not.
            const auto tuningIt = g_AiUnitTuningOverridesByObject.find(
                reinterpret_cast<uintptr_t>(craft));
            const bool hasKiteTuning = tuningIt != g_AiUnitTuningOverridesByObject.end() && tuningIt->second.hasKiteRanges;

            // If neither legacy nor kite, run stock and exit early (preserve original early-out)
            if (!isLegacyCraft && (!craft || !target || tuningIt == g_AiUnitTuningOverridesByObject.end()))
            {
                g_CombatKiteStateByObject.erase(reinterpret_cast<uintptr_t>(craft));
                CallStockAttackTaskDoState(taskPtr);
                return;
            }

            // Legacy-only fast path (no kite tuning, but legacy flag set)
            if (isLegacyCraft && !hasKiteTuning)
            {
                // The port is partial, and a modder who sets legacyAI=1 should
                // be able to read which parts of 1.4 they are getting.
                const LegacyAttackHelpers* helpers = GetLegacyAttackHelpers();
                static volatile LONG s_legacyPartialLogged = 0;
                if (InterlockedCompareExchange(&s_legacyPartialLogged, 1, 0) == 0)
                {
                    Log(L"[LEGACY] 1.4 AI profile active (first craft 0x%08X): search able-to-hit -> slide, "
                        L"stand timeout -> slide, %s; not ported: sideways check while unable to hit\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                        helpers ? L"slide while able to hit, flee without firing or the 3 s cap"
                                : L"slide and flee follow stock Redux (helper rows missing)");
                }
                int curBefore = 0, nextBefore = 0;
                float startBefore = 0.0f;
                TryGetTaskState(taskBytes, curBefore, nextBefore, startBefore);
                if (helpers && curBefore == kAttackTaskFleeState)
                {
                    RunLegacyFlee(*helpers, taskBytes, taskPtr, craft);
                    TraceLegacySnapshot(helpers, taskBytes, craft, curBefore, -1);
                    return;
                }
                g_LegacyStandNoBackOffTask =
                    g_BzrFn_UnitTaskDoStand && curBefore == kAttackTaskStandState ? taskPtr : nullptr;
                CallStockAttackTaskDoState(taskPtr);
                g_LegacyStandNoBackOffTask = nullptr;
                int curAfter = 0, nextAfter = 0;
                float startAfter = 0.0f;
                TryGetTaskState(taskBytes, curAfter, nextAfter, startAfter);
                if (helpers && curBefore == kAttackTaskSlideState)
                    ApplyLegacySlide(*helpers, taskBytes, taskPtr, craft, nextAfter);
                // Search: 1.4 goes to slide when able to hit; Redux goes to blast.
                if (curBefore == kAttackTaskSearchState && nextAfter == kAttackTaskBlastState)
                {
                    SetAttackTaskNextState(taskBytes, kAttackTaskSlideState);
                    if (LegacyAiTraceAllowed())
                        Log(L"[LEGACY] search craft=0x%08X next 10 => 7\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)));
                }
                // Stand: both builds flee on a fresh hit, but on the 8 s timeout
                // 1.4 slides where Redux flees. Stock's fresh-hit test is
                // craft last-damage time > task start (FUN_0046d040, jbe).
                if (curBefore == kAttackTaskStandState && nextAfter == kAttackTaskFleeState)
                {
                    bool isFreshHit = true;
                    __try
                    {
                        const float lastDamage = *reinterpret_cast<float*>(
                            reinterpret_cast<uint8_t*>(craft) + kCraftLastDamageTimeOffset);
                        isFreshHit = lastDamage > startBefore;
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER) {}
                    if (!isFreshHit)
                        SetAttackTaskNextState(taskBytes, kAttackTaskSlideState);
                    if (LegacyAiTraceAllowed())
                        Log(isFreshHit
                                ? L"[LEGACY] stand hit craft=0x%08X => flee 9\n"
                                : L"[LEGACY] stand timeout craft=0x%08X next 9 => 7\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)));
                }
                TraceLegacySnapshot(helpers, taskBytes, craft, curBefore, nextAfter);
                return;
            }

            const AiUnitTuningOverride& tuning = tuningIt->second;

            // CalcRange initializes rangeSq when AttackTask is constructed. Lua
            // discovery can legitimately push a per-unit policy afterward (for
            // example, a freshly spawned bomber may already have its attack
            // task and the dispenser's cached 50 m range). Keep the live task's
            // fire range synchronized with the configured floor so behavior is
            // independent of spawn/command ordering. Never reduce a range the
            // engine or another tuning source has already made larger.
            if (tuning.hasEngageRange && std::isfinite(tuning.engageRange))
            {
                const float engageSq = tuning.engageRange * tuning.engageRange;
                float previousRangeSq = 0.0f;
                bool rangeChanged = false;
                if (std::isfinite(engageSq) &&
                    TryRaiseAttackTaskRangeSq(
                        taskBytes, engageSq, previousRangeSq, rangeChanged) &&
                    rangeChanged &&
                    (TraceAiRangeEnabled() ||
                     EnvFlagEnabled("OPENSHIM_TRACE_AI_KITE")))
                {
                    const long remaining = InterlockedDecrement(
                        &g_AiUnitTuningTraceBudget);
                    if (remaining >= 0)
                    {
                        char odfToken[kProducerBuildMenuTokenLen + 1] = {};
                        TryGetObjectOdfToken(craft, odfToken);
                        const float previousRange =
                            std::isfinite(previousRangeSq) && previousRangeSq > 0.0f
                                ? std::sqrt(previousRangeSq)
                                : 0.0f;
                        Log(L"[AIUNIT] live-task craft=0x%08X odf=%hs range=%.2f->%.2f remaining=%ld\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                            odfToken[0] ? odfToken : "-",
                            static_cast<double>(previousRange),
                            static_cast<double>(tuning.engageRange),
                            remaining);
                    }
                }
            }

            if (!tuning.hasKiteRanges)
            {
                g_CombatKiteStateByObject.erase(reinterpret_cast<uintptr_t>(craft));
                CallStockAttackTaskDoState(taskPtr);
                return;
            }

            double craftX = 0.0;
            double craftY = 0.0;
            double craftZ = 0.0;
            double targetX = 0.0;
            double targetY = 0.0;
            double targetZ = 0.0;
            if (!TryGetGameObjectPosition(craft, craftX, craftY, craftZ) ||
                !TryGetGameObjectPosition(target, targetX, targetY, targetZ))
            {
                CallStockAttackTaskDoState(taskPtr);
                return;
            }

            const double dx = craftX - targetX;
            const double dy = craftY - targetY;
            const double dz = craftZ - targetZ;
            const double horizontalSq = (dx * dx) + (dz * dz);
            const double distanceSqD = horizontalSq + (dy * dy);
            if (!std::isfinite(distanceSqD) || distanceSqD <= 0.0001 || horizontalSq <= 0.0001)
            {
                CallStockAttackTaskDoState(taskPtr);
                return;
            }

            const float distance = static_cast<float>(std::sqrt(distanceSqD));
            CombatKiteState& state = g_CombatKiteStateByObject[reinterpret_cast<uintptr_t>(craft)];
            if (state.target != reinterpret_cast<uintptr_t>(target))
            {
                state.target = reinterpret_cast<uintptr_t>(target);
                state.retreating = false;
                state.strafeDirection =
                    (reinterpret_cast<uintptr_t>(craft) & 0x10u) ? 1 : -1;
                state.nextStrafeSwitchMs = 0;
                // One line per target acquisition: proves the tuned craft reaches
                // this hook even when it never closes to kiteEnterRange.
                if (EnvFlagEnabled("OPENSHIM_TRACE_AI_KITE") || TraceAiRangeEnabled())
                {
                    const long remaining = InterlockedDecrement(&g_CombatKiteTraceBudget);
                    if (remaining >= 0)
                    {
                        char odfToken[kProducerBuildMenuTokenLen + 1] = {};
                        TryGetObjectOdfToken(craft, odfToken);
                        Log(L"[AIKITE] track craft=0x%08X odf=%hs target=0x%08X dist=%.2f enter=%.2f exit=%.2f remaining=%ld\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                            odfToken[0] ? odfToken : "-",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(target)),
                            distance,
                            static_cast<double>(tuning.kiteEnterRange),
                            static_cast<double>(tuning.kiteExitRange),
                            remaining);
                    }
                }
            }

            const bool wasRetreating = state.retreating;
            if (!state.retreating && distance <= tuning.kiteEnterRange)
                state.retreating = true;
            else if (state.retreating && distance >= tuning.kiteExitRange)
                state.retreating = false;

            bool applied = false;
            bool currentLos = false;
            bool reverseLos = true;
            bool lateralLos = false;
            float savedCloseSq = 0.0f;
            float movementCloseSq = 0.0f;
            if (state.retreating)
            {
                // Match stock AbleToHit's terrain-only visibility check, while
                // sampling from the craft body because weapon mount transforms
                // are not stable across all craft classes.
                currentLos = HasTerrainLineOfSight(craftX,
                                                   craftY + 2.0,
                                                   craftZ,
                                                   targetX,
                                                   targetY + 2.0,
                                                   targetZ);

                float rangeSq = 0.0f;
                TryReadAttackTaskRangeSq(taskBytes, rangeSq);

                if (currentLos && std::isfinite(rangeSq) && distanceSqD <= rangeSq)
                {
                    if (tuning.kitePreserveLos)
                    {
                        const double horizontalLength = std::sqrt(horizontalSq);
                        constexpr double kReverseLosLookaheadMeters = 12.0;
                        const double candidateX = craftX + (dx / horizontalLength) * kReverseLosLookaheadMeters;
                        const double candidateZ = craftZ + (dz / horizontalLength) * kReverseLosLookaheadMeters;
                        reverseLos = HasTerrainLineOfSight(candidateX,
                                                           craftY + 2.0,
                                                           candidateZ,
                                                           targetX,
                                                           targetY + 2.0,
                                                           targetZ);
                    }

                    if (tuning.kiteStrafe > 0.0f)
                    {
                        const ULONGLONG nowMs = GetTickCount64();
                        const ULONGLONG switchMs = static_cast<ULONGLONG>(
                            (std::max)(tuning.kiteSwitchPeriod, 0.5f) * 1000.0f);
                        if (state.nextStrafeSwitchMs == 0)
                            state.nextStrafeSwitchMs = nowMs + switchMs;
                        else if (nowMs >= state.nextStrafeSwitchMs)
                        {
                            state.strafeDirection = -state.strafeDirection;
                            state.nextStrafeSwitchMs = nowMs + switchMs;
                        }

                        const double horizontalLength = std::sqrt(horizontalSq);
                        constexpr double kLateralLosLookaheadMeters = 10.0;
                        for (int attempt = 0; attempt < 2 && !lateralLos; ++attempt)
                        {
                            const double side = static_cast<double>(state.strafeDirection);
                            const double candidateX = craftX + (-dz / horizontalLength) * side * kLateralLosLookaheadMeters;
                            const double candidateZ = craftZ + (dx / horizontalLength) * side * kLateralLosLookaheadMeters;
                            lateralLos = HasTerrainLineOfSight(candidateX,
                                                               craftY + 2.0,
                                                               candidateZ,
                                                               targetX,
                                                               targetY + 2.0,
                                                               targetZ);
                            if (!lateralLos)
                                state.strafeDirection = -state.strafeDirection;
                        }
                    }

                    movementCloseSq = reverseLos
                        ? tuning.kiteDesiredRange * tuning.kiteDesiredRange
                        : 0.0f;
                    applied = TryApplyAttackTaskFiringOverride(
                        taskBytes, movementCloseSq, savedCloseSq);
                }
            }

            CallStockAttackTaskDoState(taskPtr);

            if (applied)
            {
                // The temporary closeSq is a movement potential only. Fire
                // permission remains governed by rangeSq + stock AbleToHit.
                const bool restored = TryRestoreAttackTaskFiringOverride(
                    taskBytes, savedCloseSq);

                // Preserve the stock terrain/obstacle stop: only add the
                // lateral component when DoBlast produced movement of its own
                // and the projected side-step retains terrain LOS.
                if (restored && lateralLos && tuning.kiteStrafe > 0.0f)
                {
                    TryApplyAttackTaskStrafeControl(
                        craft, state.strafeDirection, tuning.kiteStrafe, reverseLos);
                }
            }

            if ((wasRetreating != state.retreating || (applied && !reverseLos)) &&
                (EnvFlagEnabled("OPENSHIM_TRACE_AI_KITE") ||
                 TraceAiRangeEnabled()))
            {
                const long remaining = InterlockedDecrement(&g_CombatKiteTraceBudget);
                if (remaining >= 0)
                {
                    char odfToken[kProducerBuildMenuTokenLen + 1] = {};
                    TryGetObjectOdfToken(craft, odfToken);
                    Log(L"[AIKITE] craft=0x%08X odf=%hs target=0x%08X dist=%.2f retreat=%hs transition=%hs los=%hs reverseLos=%hs lateralLos=%hs strafe=%.2f dir=%d movementClose=%.2f desired=%.2f enter=%.2f exit=%.2f remaining=%ld\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                        odfToken[0] ? odfToken : "-",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(target)),
                        distance,
                        BoolText(state.retreating),
                        wasRetreating == state.retreating ? "hold" : (state.retreating ? "enter" : "exit"),
                        BoolText(currentLos),
                        BoolText(reverseLos),
                        BoolText(lateralLos),
                        static_cast<double>(tuning.kiteStrafe),
                        state.strafeDirection,
                        static_cast<double>(movementCloseSq > 0.0f ? std::sqrt(movementCloseSq) : 0.0f),
                        static_cast<double>(tuning.kiteDesiredRange),
                        static_cast<double>(tuning.kiteEnterRange),
                        static_cast<double>(tuning.kiteExitRange),
                        remaining);
                }
            }
        }

        void __fastcall AttackTaskDoStateTuningHook(void* taskPtr, void* /*edx*/)
        {
            if (!g_AttackTaskProfileEnabled)
            {
                AttackTaskDoStateTuningBody(taskPtr);
                return;
            }

            static LONGLONG s_totalTicks = 0;
            static unsigned long s_calls = 0;
            static ULONGLONG s_windowStartMs = 0;
            static LONGLONG s_frequency = 0;
            if (!s_frequency)
            {
                LARGE_INTEGER frequency;
                QueryPerformanceFrequency(&frequency);
                s_frequency = frequency.QuadPart > 0 ? frequency.QuadPart : 1;
            }

            LARGE_INTEGER before;
            LARGE_INTEGER after;
            QueryPerformanceCounter(&before);
            AttackTaskDoStateTuningBody(taskPtr);
            QueryPerformanceCounter(&after);
            s_totalTicks += after.QuadPart - before.QuadPart;
            ++s_calls;

            const ULONGLONG nowMs = GetTickCount64();
            if (!s_windowStartMs)
                s_windowStartMs = nowMs;
            if (nowMs - s_windowStartMs < 5000)
                return;

            const double toMs = 1000.0 / static_cast<double>(s_frequency);
            const double totalMs = static_cast<double>(s_totalTicks) * toMs;
            const double stockMs = static_cast<double>(g_AttackTaskProfileStockTicks) * toMs;
            const double windowMs = static_cast<double>(nowMs - s_windowStartMs);
            Log(L"[AIKITE] profile window=%.0fms calls=%lu total=%.3fms stock=%.3fms shim=%.3fms shim/call=%.2fus\n",
                windowMs, s_calls, totalMs, stockMs, totalMs - stockMs,
                s_calls ? (totalMs - stockMs) * 1000.0 / s_calls : 0.0);
            s_totalTicks = 0;
            g_AttackTaskProfileStockTicks = 0;
            s_calls = 0;
            s_windowStartMs = nowMs;
        }

        static void InstallAttackTaskKiteHookIfPossible()
        {
            if (g_AttackTaskDoStateHookInstalled)
                return;

            if (g_AttackTaskDoStateDetour.trampoline && g_BzrFn_AttackTaskDoState)
            {
                g_AttackTaskDoStateHookInstalled = true;
                return;
            }

            static const uint8_t kExpectedAttackTaskDoStateBytes[kAttackTaskDoStateDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x7C, 0x89, 0x4D, 0xFC
            };

            g_AttackTaskDoStateEntryAddr = HookEngine::EngineAddress("AttackTaskDoState");
            if (g_AttackTaskDoStateEntryAddr == 0 || TerrainGetIntersectionAddr() == 0)
            {
                MarkOptionHookFailed("LegacyTankAi", "Unavailable: Legacy tank AI did not hook on this game build (see openshim.log).");
                return;
            }

            if (!ExpectedBytesMatchAt(g_AttackTaskDoStateEntryAddr,
                                      kExpectedAttackTaskDoStateBytes,
                                      sizeof(kExpectedAttackTaskDoStateBytes)))
            {
                MarkOptionHookFailed("LegacyTankAi", "Unavailable: Legacy tank AI did not hook on this game build (see openshim.log).");
                return;
            }

            if (!InstallInlineDetour32(g_AttackTaskDoStateDetour,
                                       g_AttackTaskDoStateEntryAddr,
                                       reinterpret_cast<void*>(AttackTaskDoStateTuningHook),
                                       kAttackTaskDoStateDetourLen,
                                       kExpectedAttackTaskDoStateBytes,
                                       sizeof(kExpectedAttackTaskDoStateBytes)))
            {
                Log(L"[AIKITE] Failed installing AttackTask::DoState hook at 0x%08X\n",
                    static_cast<uint32_t>(g_AttackTaskDoStateEntryAddr));
                MarkOptionHookFailed("LegacyTankAi", "Unavailable: Legacy tank AI did not hook on this game build (see openshim.log).");
                return;
            }

            g_BzrFn_AttackTaskDoState = reinterpret_cast<FnAttackTaskDoState>(
                g_AttackTaskDoStateDetour.trampoline);
            g_BzrFn_TerrainGetIntersection = reinterpret_cast<FnTerrainGetIntersection>(
                TerrainGetIntersectionAddr());
            g_AttackTaskDoStateHookInstalled =
                g_BzrFn_AttackTaskDoState && g_BzrFn_TerrainGetIntersection;
            if (g_AttackTaskDoStateHookInstalled)
            {
                InstallLegacyStandSiteHook();
                g_AttackTaskProfileEnabled = EnvFlagEnabled("OPENSHIM_PROFILE_ATTACK_TASK");
                Log(L"[AIKITE] Installed AttackTask::DoState hook entry=0x%08X trampoline=0x%08X terrainLos=0x%08X\n",
                    static_cast<uint32_t>(g_AttackTaskDoStateEntryAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_AttackTaskDoStateDetour.trampoline)),
                    static_cast<uint32_t>(TerrainGetIntersectionAddr()));
            }
        }

        struct ScrapScoreVector3
        {
            float x;
            float y;
            float z;
        };

        static bool ShouldTraceScrapPathing()
        {
            return EnvFlagEnabled("OPENSHIM_TRACE_SCAVENGER_PATH") ||
                   EnvFlagEnabled("OPENSHIM_TRACE_AI_SCAVENGER") ||
                   EnvFlagEnabled("BZR_TRACE_AI_SCAVENGER");
        }

        static void TraceScrapPathScore(const char* result,
                                        void* craft,
                                        void* scrap,
                                        float straightDistance,
                                        float pathLength,
                                        float score)
        {
            if (!ShouldTraceScrapPathing())
                return;

            const long remaining = InterlockedDecrement(&g_ScrapPathTraceBudget);
            if (remaining < 0)
                return;

            Log(L"[SCAVPATH] result=%hs craft=0x%08X scrap=0x%08X straight=%.2f path=%.2f score=%.2f remaining=%ld\n",
                result,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(scrap)),
                static_cast<double>(straightDistance),
                static_cast<double>(pathLength),
                static_cast<double>(score),
                remaining);
        }

        // This helper is reached through a naked call-site thunk. originalStack
        // points at the stock CALL return address followed by two VECTOR_3D
        // values (candidate, scavenger); callerFrame is InitLookingForScrap's
        // EBP and exposes only the task/candidate locals validated for 2.2.301.
        // SEH leaves for the scavenger score hook. The caller owns checked
        // unordered_map iterators in Debug, so no __try may remain in it.
        static bool TryReadScrapScorePositions(const uint8_t* originalStack,
                                               ScrapScoreVector3& candidatePosition,
                                               ScrapScoreVector3& scavengerPosition)
        {
            if (!originalStack)
                return false;
            __try
            {
                candidatePosition = *reinterpret_cast<const ScrapScoreVector3*>(originalStack + 4);
                scavengerPosition = *reinterpret_cast<const ScrapScoreVector3*>(originalStack + 16);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryReadScrapScoreContext(const uint8_t* callerFrame,
                                             void*& recycleTask,
                                             void*& candidateObject,
                                             void*& craft)
        {
            recycleTask = nullptr;
            candidateObject = nullptr;
            craft = nullptr;
            if (!callerFrame)
                return false;
            __try
            {
                recycleTask = *reinterpret_cast<void* const*>(
                    callerFrame - kRecycleTaskCallerThisLocalOffset);
                candidateObject = *reinterpret_cast<void* const*>(
                    callerFrame - kRecycleTaskCallerCandidateLocalOffset);
                if (recycleTask)
                {
                    craft = *reinterpret_cast<void* const*>(
                        reinterpret_cast<const uint8_t*>(recycleTask) + kRecycleTaskOwnerOffset);
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                recycleTask = nullptr;
                candidateObject = nullptr;
                craft = nullptr;
                return false;
            }
        }

        static bool TryProbeScrapPath(void* craft,
                                      float targetX,
                                      float targetZ,
                                      void*& path,
                                      bool& badPath,
                                      float& pathLength)
        {
            path = nullptr;
            badPath = true;
            pathLength = 0.0f;
            __try
            {
                path = g_BzrFn_FindPlanForObject(craft, targetX, targetZ);
                if (path)
                {
                    badPath =
                        *reinterpret_cast<const int*>(
                            reinterpret_cast<const uint8_t*>(path) + kAiPathTypeOffset) ==
                        kAiPathBadPathType;
                    if (!badPath)
                        pathLength = g_BzrFn_AiPathGetLength(path);
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                badPath = true;
                pathLength = 0.0f;
                return false;
            }
        }

        static void TryDeleteScrapProbePath(void* path)
        {
            if (!path || !g_BzrFn_AiPathDelete)
                return;
            __try
            {
                g_BzrFn_AiPathDelete(path, 1);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                // The score hook must fail soft; the stock task still owns its
                // independently-created validation path.
            }
        }

        static __declspec(noinline) float __cdecl ScoreScrapCandidateFromCallsite(
            const uint8_t* callerFrame,
            const uint8_t* originalStack)
        {
            if (!callerFrame || !originalStack)
                return kScrapRejectedScore;

            ScrapScoreVector3 candidatePosition = {};
            ScrapScoreVector3 scavengerPosition = {};
            void* recycleTask = nullptr;
            void* candidateObject = nullptr;
            void* craft = nullptr;
            if (!TryReadScrapScorePositions(
                    originalStack, candidatePosition, scavengerPosition))
            {
                return kScrapRejectedScore;
            }

            const float dx = candidatePosition.x - scavengerPosition.x;
            const float dy = candidatePosition.y - scavengerPosition.y;
            const float dz = candidatePosition.z - scavengerPosition.z;
            const float straightSquared = dx * dx + dy * dy + dz * dz;
            if (!std::isfinite(straightSquared))
                return kScrapRejectedScore;

            if (!TryReadScrapScoreContext(
                    callerFrame, recycleTask, candidateObject, craft))
            {
                return straightSquared;
            }

            if (!craft || !candidateObject || ReadLocalPlayerNetIdValue() != 0)
                return straightSquared;

            AiTuningConfig tuning = {};
            const bool hasTuning =
                g_AiOdfGameplayTuningActive && TryGetAiTuningForObject(craft, tuning);
            bool pathingEnabled = g_SmartScavengerPathingEnabled;
            if (g_AiOdfGameplayTuningActive && hasTuning && tuning.hasScrapPathingAI)
                pathingEnabled = tuning.scrapPathingAI;
            if (!pathingEnabled)
            {
                return straightSquared;
            }

            const float straightDistance = std::sqrt((std::max)(straightSquared, 0.0f));
            if (tuning.hasScrapSearchRadiusAI &&
                std::isfinite(tuning.scrapSearchRadiusAI) &&
                tuning.scrapSearchRadiusAI > 0.0f &&
                straightDistance > tuning.scrapSearchRadiusAI)
            {
                TraceScrapPathScore("radius-reject", craft, candidateObject,
                                    straightDistance, 0.0f, kScrapRejectedScore);
                return kScrapRejectedScore;
            }

            float now = 0.0f;
            if (g_BzrFn_GetGameTime)
                now = g_BzrFn_GetGameTime();

            const uintptr_t candidateKey = reinterpret_cast<uintptr_t>(candidateObject);
            auto failureIt = g_ScrapPathFailuresByObject.find(candidateKey);
            if (failureIt != g_ScrapPathFailuresByObject.end())
            {
                const ScrapPathFailureState& failure = failureIt->second;
                const bool sameObjectPosition =
                    std::fabs(failure.x - candidatePosition.x) < 1.0f &&
                    std::fabs(failure.z - candidatePosition.z) < 1.0f;
                if (std::isfinite(now) && sameObjectPosition && now < failure.retryAfter)
                {
                    TraceScrapPathScore("cooldown-reject", craft, candidateObject,
                                        straightDistance, 0.0f, kScrapRejectedScore);
                    return kScrapRejectedScore;
                }
                g_ScrapPathFailuresByObject.erase(failureIt);
            }

            const float pathWeight =
                (tuning.hasScrapPathLengthWeightAI &&
                 std::isfinite(tuning.scrapPathLengthWeightAI))
                    ? (std::max)(tuning.scrapPathLengthWeightAI, 0.0f)
                    : 1.0f;
            const float straightWeight =
                (tuning.hasScrapStraightDistanceWeightAI &&
                 std::isfinite(tuning.scrapStraightDistanceWeightAI))
                    ? (std::max)(tuning.scrapStraightDistanceWeightAI, 0.0f)
                    : 0.05f;
            const float failPenalty =
                (tuning.hasScrapPathFailPenaltyAI &&
                 std::isfinite(tuning.scrapPathFailPenaltyAI))
                    ? (std::max)(tuning.scrapPathFailPenaltyAI, 0.0f)
                    : 250.0f;

            if (!g_BzrFn_FindPlanForObject ||
                !g_BzrFn_AiPathGetLength ||
                !g_BzrFn_AiPathDelete)
            {
                return straightSquared;
            }

            void* path = nullptr;
            float pathLength = 0.0f;
            bool badPath = true;
            const bool pathProbeSucceeded = TryProbeScrapPath(
                craft, candidatePosition.x, candidatePosition.z,
                path, badPath, pathLength);

            TryDeleteScrapProbePath(path);

            if (!pathProbeSucceeded)
            {
                TraceScrapPathScore("probe-fallback", craft, candidateObject,
                                    straightDistance, 0.0f, straightSquared);
                return straightSquared;
            }

            if (badPath || !std::isfinite(pathLength))
            {
                const float cooldown =
                    (tuning.hasScrapHardToGetCooldownAI &&
                     std::isfinite(tuning.scrapHardToGetCooldownAI))
                        ? (std::max)(tuning.scrapHardToGetCooldownAI, 0.0f)
                        : 10.0f;
                if (cooldown > 0.0f && std::isfinite(now))
                {
                    g_ScrapPathFailuresByObject[candidateKey] =
                        { now + cooldown, candidatePosition.x, candidatePosition.z };
                }

                const float failedScore = failPenalty + straightDistance * straightWeight;
                const float safeFailedScore = std::isfinite(failedScore)
                    ? (std::min)(failedScore, kScrapRejectedScore)
                    : kScrapRejectedScore;
                TraceScrapPathScore("bad-path", craft, candidateObject,
                                    straightDistance, 0.0f, safeFailedScore);
                return safeFailedScore;
            }

            float score = pathLength * pathWeight + straightDistance * straightWeight;
            bool incumbentBonusApplied = false;
            const uintptr_t taskKey = reinterpret_cast<uintptr_t>(recycleTask);
            auto retargetIt = g_ScrapRetargetStateByTask.find(taskKey);
            if (retargetIt != g_ScrapRetargetStateByTask.end() &&
                retargetIt->second.owner == reinterpret_cast<uintptr_t>(craft) &&
                retargetIt->second.rescorePending)
            {
                ScrapRetargetState& retarget = retargetIt->second;
                if (!std::isfinite(now) || now > retarget.pendingUntil)
                {
                    retarget.rescorePending = false;
                }
                else if (g_BzrFn_GameObjectGetObjByHandle && retarget.incumbentHandle != 0)
                {
                    void* incumbent = g_BzrFn_GameObjectGetObjByHandle(retarget.incumbentHandle);
                    if (incumbent == candidateObject)
                    {
                        const float minImprovement =
                            (tuning.hasScrapRetargetMinImprovementAI &&
                             std::isfinite(tuning.scrapRetargetMinImprovementAI))
                                ? (std::max)(tuning.scrapRetargetMinImprovementAI, 0.0f)
                                : kScrapRetargetMinImprovementDefault;
                        score -= minImprovement;
                        incumbentBonusApplied = true;
                    }
                }
            }

            const float safeScore = std::isfinite(score)
                ? (std::min)((std::max)(score, 0.0f), kScrapRejectedScore)
                : kScrapRejectedScore;
            TraceScrapPathScore(incumbentBonusApplied ? "path-incumbent" : "path",
                                craft, candidateObject,
                                straightDistance, pathLength, safeScore);
            return safeScore;
        }

#if defined(_M_IX86)
        static __declspec(naked) void ScrapCandidateScoreCallsiteHook()
        {
            __asm
            {
                mov eax, esp
                push eax
                push ebp
                call ScoreScrapCandidateFromCallsite
                add esp, 8
                ret
            }
        }
#endif

        static void InstallScrapPathScoreHookIfPossible()
        {
            if (g_ScrapPathScoreHookInstalled)
                return;

#if !defined(_M_IX86)
            return;
#else
            static int s_bound = 0;
            if (s_bound == 0)
            {
                const HookEngine::EngineRow rows[] = {
                    { "RecycleTaskScrapDistanceCall", &g_RecycleTaskScrapDistanceCallAddr },
                    { "Dist3DSquared", &g_Dist3DSquaredAddr },
                    { "FindPlanForObject", &g_FindPlanForObjectAddr },
                    { "AiPathGetLength", &g_AiPathGetLengthAddr },
                    { "AiPathDelete", &g_AiPathDeleteAddr },
                    { "GetGameTime", &g_GetGameTimeAddr },
                };
                s_bound = HookEngine::BindEngineRows("Path-scored scrap selection", rows) ? 1 : -1;
            }
            if (s_bound < 0)
                return;
            g_BzrFn_FindPlanForObject =
                reinterpret_cast<FnFindPlanForObject>(g_FindPlanForObjectAddr);
            g_BzrFn_AiPathGetLength =
                reinterpret_cast<FnAiPathGetLength>(g_AiPathGetLengthAddr);
            g_BzrFn_AiPathDelete =
                reinterpret_cast<FnAiPathDelete>(g_AiPathDeleteAddr);
            g_BzrFn_GetGameTime = reinterpret_cast<FnGetGameTime>(g_GetGameTimeAddr);
            if (!g_BzrFn_GameObjectGetObjByHandle)
            {
                g_BzrFn_GameObjectGetObjByHandle =
                    &GameObjectFromHandleGog; // was 0x0046B160 (wrong fn; crashed)
            }

            // The rows' guards stand for the helper prologues; the call site
            // must still target Dist3DSquared (or already be ours).
            auto* callBytes = reinterpret_cast<uint8_t*>(g_RecycleTaskScrapDistanceCallAddr);
            uintptr_t currentTarget = 0;
            if (callBytes[0] == 0xE8)
            {
                int32_t currentRelative = 0;
                std::memcpy(&currentRelative, callBytes + 1, sizeof(currentRelative));
                currentTarget =
                    g_RecycleTaskScrapDistanceCallAddr + 5 + currentRelative;
                if (currentTarget == reinterpret_cast<uintptr_t>(ScrapCandidateScoreCallsiteHook))
                {
                    g_ScrapPathScoreHookInstalled = true;
                    return;
                }
            }

            if (currentTarget != g_Dist3DSquaredAddr)
            {
                Log(L"[SCAVPATH] Redux helper/call-site bytes mismatch; path-scored scrap selection disabled\n");
                MarkOptionHookFailed("SmartScavengerPathing", "Unavailable: Smart scavenger pathing did not hook on this game build (see openshim.log).");
                return;
            }

            uint8_t patch[5] = { 0xE8, 0, 0, 0, 0 };
            const int32_t relative =
                static_cast<int32_t>(reinterpret_cast<uintptr_t>(ScrapCandidateScoreCallsiteHook)) -
                static_cast<int32_t>(g_RecycleTaskScrapDistanceCallAddr + 5);
            std::memcpy(patch + 1, &relative, sizeof(relative));
            if (!WritePatchBytes(g_RecycleTaskScrapDistanceCallAddr, patch, sizeof(patch)))
            {
                Log(L"[SCAVPATH] Failed patching scrap score call at 0x%08X\n",
                    static_cast<uint32_t>(g_RecycleTaskScrapDistanceCallAddr));
                return;
            }

            g_ScrapPathScoreHookInstalled = true;
            Log(L"[SCAVPATH] Installed path-scored scrap selector call=0x%08X FindPlan=0x%08X GetLength=0x%08X\n",
                static_cast<uint32_t>(g_RecycleTaskScrapDistanceCallAddr),
                static_cast<uint32_t>(g_FindPlanForObjectAddr),
                static_cast<uint32_t>(g_AiPathGetLengthAddr));
#endif
        }

        static void ApplyScavengerRetargetAfterGotoScrap(void* recycleTask)
        {
            if (!recycleTask || !g_BzrFn_GetGameTime || ReadLocalPlayerNetIdValue() != 0)
                return;

            auto* taskBytes = reinterpret_cast<uint8_t*>(recycleTask);
            void* craft = nullptr;
            void* subtask = nullptr;
            int currentHandle = 0;
            int nextState = 0;
            __try
            {
                craft = *reinterpret_cast<void**>(taskBytes + kRecycleTaskOwnerOffset);
                subtask = *reinterpret_cast<void**>(taskBytes + kRecycleTaskSubtaskOffset);
                currentHandle = *reinterpret_cast<int*>(taskBytes + kRecycleTaskScrapHandleOffset);
                nextState = *reinterpret_cast<int*>(taskBytes + kRecycleTaskNextStateOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return;
            }

            const uintptr_t taskKey = reinterpret_cast<uintptr_t>(recycleTask);
            AiTuningConfig tuning = {};
            const bool hasTuning =
                craft && g_AiOdfGameplayTuningActive &&
                TryGetAiTuningForObject(craft, tuning);
            bool pathingEnabled = g_SmartScavengerPathingEnabled;
            if (g_AiOdfGameplayTuningActive && hasTuning && tuning.hasScrapPathingAI)
                pathingEnabled = tuning.scrapPathingAI;
            if (!craft || !pathingEnabled)
            {
                g_ScrapRetargetStateByTask.erase(taskKey);
                return;
            }

            const float period =
                (tuning.hasScrapRetargetPeriodAI &&
                 std::isfinite(tuning.scrapRetargetPeriodAI))
                    ? tuning.scrapRetargetPeriodAI
                    : kScrapRetargetPeriodDefault;
            if (!std::isfinite(period) || period <= 0.0f)
            {
                g_ScrapRetargetStateByTask.erase(taskKey);
                return;
            }

            const float now = g_BzrFn_GetGameTime();
            if (!std::isfinite(now))
                return;

            ScrapRetargetState& state = g_ScrapRetargetStateByTask[taskKey];
            const uintptr_t craftKey = reinterpret_cast<uintptr_t>(craft);
            if (state.owner != craftKey)
            {
                state = {};
                state.owner = craftKey;
            }
            if (state.rescorePending)
            {
                TraceScrapPathScore(
                    currentHandle == state.incumbentHandle
                        ? "retarget-keep"
                        : "retarget-switch",
                    craft,
                    g_BzrFn_GameObjectGetObjByHandle
                        ? g_BzrFn_GameObjectGetObjByHandle(currentHandle)
                        : nullptr,
                    0.0f,
                    0.0f,
                    0.0f);
                state.rescorePending = false;
            }

            // Stock uses 8 as the no-transition sentinel. If the subtask has
            // completed or already requested another state, preserve it.
            if (!subtask || nextState != 8)
                return;

            if (state.nextCheck <= 0.0f)
            {
                state.nextCheck = now + period;
                return;
            }
            if (now < state.nextCheck)
                return;

            state.nextCheck = now + period;

            void* currentScrap = g_BzrFn_GameObjectGetObjByHandle
                ? g_BzrFn_GameObjectGetObjByHandle(currentHandle)
                : nullptr;
            double craftX = 0.0;
            double craftY = 0.0;
            double craftZ = 0.0;
            double scrapX = 0.0;
            double scrapY = 0.0;
            double scrapZ = 0.0;
            if (currentScrap &&
                TryGetGameObjectPosition(craft, craftX, craftY, craftZ) &&
                TryGetGameObjectPosition(currentScrap, scrapX, scrapY, scrapZ))
            {
                const double dx = scrapX - craftX;
                const double dy = scrapY - craftY;
                const double dz = scrapZ - craftZ;
                const double distanceSquared = dx * dx + dy * dy + dz * dz;
                if (std::isfinite(distanceSquared) &&
                    distanceSquared <=
                        static_cast<double>(kScrapRetargetPickupGuardDistance) *
                        static_cast<double>(kScrapRetargetPickupGuardDistance))
                {
                    return;
                }
            }

            state.incumbentHandle = currentHandle;
            state.pendingUntil = now + (std::max)(period, 1.0f);
            state.rescorePending = true;
            __try
            {
                *reinterpret_cast<int*>(taskBytes + kRecycleTaskNextStateOffset) = 1;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                state.rescorePending = false;
                return;
            }

            TraceScrapPathScore("retarget-request", craft, currentScrap,
                                0.0f, 0.0f, 0.0f);
        }

        static void __fastcall RecycleTaskDoGotoScrapHook(
            void* recycleTask,
            void* /*unusedEdx*/)
        {
            if (g_BzrFn_RecycleTaskDoGotoScrap)
                g_BzrFn_RecycleTaskDoGotoScrap(recycleTask);
            ApplyScavengerRetargetAfterGotoScrap(recycleTask);
        }

        static void InstallScavengerRetargetHookIfPossible()
        {
            if (g_ScrapRetargetHookInstalled)
                return;

            if (g_RecycleTaskDoGotoScrapDetour.trampoline)
            {
                g_BzrFn_RecycleTaskDoGotoScrap =
                    reinterpret_cast<FnRecycleTaskDoGotoScrap>(
                        g_RecycleTaskDoGotoScrapDetour.trampoline);
                g_ScrapRetargetHookInstalled =
                    (g_BzrFn_RecycleTaskDoGotoScrap != nullptr);
                return;
            }

            static const uint8_t kExpectedBytes[kRecycleTaskDoGotoScrapDetourLen] =
                { 0x55, 0x8B, 0xEC, 0x51, 0x89, 0x4D, 0xFC };
            g_RecycleTaskDoGotoScrapAddr = HookEngine::EngineAddress("RecycleTaskDoGotoScrap");
            g_GetGameTimeAddr = HookEngine::EngineAddress("GetGameTime");
            if (g_RecycleTaskDoGotoScrapAddr == 0 || g_GetGameTimeAddr == 0)
                return;
            if (!ExpectedBytesMatchAt(g_RecycleTaskDoGotoScrapAddr,
                                      kExpectedBytes,
                                      sizeof(kExpectedBytes)))
            {
                Log(L"[SCAVPATH] RecycleTask::DoGotoScrap bytes mismatch at 0x%08X; en-route retargeting disabled\n",
                    static_cast<uint32_t>(g_RecycleTaskDoGotoScrapAddr));
                MarkOptionHookFailed("SmartScavengerPathing", "Unavailable: Smart scavenger pathing did not hook on this game build (see openshim.log).");
                return;
            }

            if (!InstallInlineDetour32(g_RecycleTaskDoGotoScrapDetour,
                                       g_RecycleTaskDoGotoScrapAddr,
                                       reinterpret_cast<void*>(RecycleTaskDoGotoScrapHook),
                                       kRecycleTaskDoGotoScrapDetourLen,
                                       kExpectedBytes,
                                       sizeof(kExpectedBytes)))
            {
                Log(L"[SCAVPATH] Failed installing RecycleTask::DoGotoScrap retarget hook at 0x%08X\n",
                    static_cast<uint32_t>(g_RecycleTaskDoGotoScrapAddr));
                MarkOptionHookFailed("SmartScavengerPathing", "Unavailable: Smart scavenger pathing did not hook on this game build (see openshim.log).");
                return;
            }

            g_BzrFn_RecycleTaskDoGotoScrap =
                reinterpret_cast<FnRecycleTaskDoGotoScrap>(
                    g_RecycleTaskDoGotoScrapDetour.trampoline);
            g_ScrapRetargetHookInstalled =
                (g_BzrFn_RecycleTaskDoGotoScrap != nullptr);
            if (g_ScrapRetargetHookInstalled)
            {
                Log(L"[SCAVPATH] Installed en-route scrap retarget hook entry=0x%08X trampoline=0x%08X periodDefault=%.2f improveDefault=%.2f\n",
                    static_cast<uint32_t>(g_RecycleTaskDoGotoScrapAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(
                        g_RecycleTaskDoGotoScrapDetour.trampoline)),
                    static_cast<double>(kScrapRetargetPeriodDefault),
                    static_cast<double>(kScrapRetargetMinImprovementDefault));
            }
        }

        void __cdecl CalcRangeCraftHook(void* craft,
                                        float* closeRange,
                                        float* range,
                                        float* time,
                                        void** weapon)
        {
            if (g_BzrFn_CalcRangeCraft)
                g_BzrFn_CalcRangeCraft(craft, closeRange, range, time, weapon);

            if (!craft || !range)
                return;

            const float originalRange = *range;
            const float originalCloseRange = closeRange ? *closeRange : -1.0f;

            if (TraceAiRangeEnabled())
            {
                static volatile long s_CalcRangeProbeBudget = 24;
                const long remaining = InterlockedDecrement(&s_CalcRangeProbeBudget);
                if (remaining >= 0)
                {
                    char odfToken[kProducerBuildMenuTokenLen + 1] = {};
                    const bool haveOdf = TryGetObjectOdfToken(craft, odfToken);
                    Log(L"[AIODF] CalcRange probe craft=0x%08X odf=%hs active=%hs close=%.2f range=%.2f time=%.2f weapon=0x%08X remaining=%ld\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                        haveOdf ? odfToken : "-",
                        BoolText(g_AiOdfGameplayTuningActive),
                        closeRange ? *closeRange : -1.0f,
                        *range,
                        time ? *time : -1.0f,
                        weapon && *weapon
                            ? static_cast<uint32_t>(reinterpret_cast<uintptr_t>(*weapon))
                            : 0u,
                        remaining);
                }
            }

            const AiUnitTuningOverride* unitTuning = nullptr;
            if (!g_AiUnitTuningOverridesByObject.empty())
            {
                const auto unitIt =
                    g_AiUnitTuningOverridesByObject.find(reinterpret_cast<uintptr_t>(craft));
                if (unitIt != g_AiUnitTuningOverridesByObject.end())
                    unitTuning = &unitIt->second;
            }

            AiTuningConfig tuning = {};
            const bool hasOdfTuning = TryGetAiTuningForObject(craft, tuning);
            if (!hasOdfTuning && !unitTuning)
                return;

            AiRangePolicy::Inputs policy = {};
            policy.closeRange = closeRange ? *closeRange : 0.0f;
            policy.range = *range;
            policy.time = time ? *time : 0.0f;

            bool hasOdfOuterRangeFloor = false;
            bool hasOdfCloseRangeFloor = false;
            bool hasUnitOuterRangeFloor = false;
            bool hasUnitCloseRangeFloor = false;
            if (hasOdfTuning &&
                g_AiOdfGameplayTuningActive &&
                tuning.hasEngageRangeAI)
            {
                hasOdfOuterRangeFloor =
                    AiRangePolicy::AccumulatePositiveFloor(
                        policy.hasOuterRangeFloor,
                        policy.outerRangeFloor,
                        tuning.engageRangeAI) || hasOdfOuterRangeFloor;
            }
            const bool useAuthoredWeaponRange =
                g_AiOdfGameplayTuningActive &&
                tuning.hasWeaponRangeMinAI &&
                !tuning.derivedBomberWeaponRangeAI;
            const bool useDerivedBomberRange =
                g_AiOdfGameplayTuningActive &&
                tuning.bomberAiRole &&
                tuning.hasWeaponRangeMinAI &&
                tuning.derivedBomberWeaponRangeAI;
            if (hasOdfTuning && useAuthoredWeaponRange)
            {
                hasOdfCloseRangeFloor =
                    AiRangePolicy::AccumulatePositiveFloor(
                        policy.hasCloseRangeFloor,
                        policy.closeRangeFloor,
                        tuning.weaponRangeMinAI) || hasOdfCloseRangeFloor;
            }
            if (hasOdfTuning && useDerivedBomberRange)
            {
                // Preserve the inherited bomber fallback as an outer weapon
                // range floor. It is not an authored wingman standoff ring.
                hasOdfOuterRangeFloor =
                    AiRangePolicy::AccumulatePositiveFloor(
                        policy.hasOuterRangeFloor,
                        policy.outerRangeFloor,
                        tuning.weaponRangeMinAI) || hasOdfOuterRangeFloor;
            }

            // Per-unit overrides win over ODF tuning and ignore the master toggle.
            if (unitTuning && unitTuning->hasEngageRange)
            {
                hasUnitOuterRangeFloor =
                    AiRangePolicy::AccumulatePositiveFloor(
                        policy.hasOuterRangeFloor,
                        policy.outerRangeFloor,
                        unitTuning->engageRange) || hasUnitOuterRangeFloor;
            }
            if (unitTuning && unitTuning->hasWeaponRangeMin && closeRange)
            {
                hasUnitCloseRangeFloor =
                    AiRangePolicy::AccumulatePositiveFloor(
                        policy.hasCloseRangeFloor,
                        policy.closeRangeFloor,
                        unitTuning->weaponRangeMin) || hasUnitCloseRangeFloor;
            }

            // CalcRange is the stock weapon-aware source for both the outer
            // firing range and UnitTask's closeSq/"too close" threshold.
            // Authored engageRangeAI floors only the former; authored
            // weaponRangeMinAI floors only the latter and is capped just under
            // the final outer range so a firing window remains.
            const AiRangePolicy::Result policyResult = AiRangePolicy::Apply(policy);
            *range = policyResult.range;
            if (closeRange)
                *closeRange = policyResult.closeRange;
            if (time)
                *time = policyResult.time;

            const bool hasOdfRangePolicy =
                hasOdfOuterRangeFloor || hasOdfCloseRangeFloor;
            const bool hasUnitRangePolicy =
                hasUnitOuterRangeFloor || hasUnitCloseRangeFloor;

            if (hasOdfTuning && hasOdfRangePolicy &&
                TraceAiRangeEnabled())
            {
                static volatile long s_OdfRangeTraceBudget = 24;
                const long remaining = InterlockedDecrement(&s_OdfRangeTraceBudget);
                if (remaining >= 0)
                {
                    char odfToken[kProducerBuildMenuTokenLen + 1] = {};
                    TryGetObjectOdfToken(craft, odfToken);
                    Log(L"[AIODF] Range policy craft=0x%08X odf=%hs range=%.2f->%.2f outerFloor=%hs%.2f close=%.2f->%.2f closeFloor=%hs%.2f remaining=%ld\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                        odfToken[0] ? odfToken : "-",
                        originalRange,
                        *range,
                        hasOdfOuterRangeFloor ? "" : "-",
                        policyResult.appliedOuterRangeFloor,
                        originalCloseRange,
                        closeRange ? *closeRange : -1.0f,
                        hasOdfCloseRangeFloor ? "" : "-",
                        policyResult.appliedCloseRangeFloor,
                        remaining);
                }
            }

            if (unitTuning &&
                hasUnitRangePolicy &&
                (policyResult.rangeChanged || policyResult.closeRangeChanged) &&
                (TraceAiRangeEnabled() ||
                 TraceAiUnitTuningEnabled()))
            {
                const long remaining = InterlockedDecrement(&g_AiUnitTuningTraceBudget);
                if (remaining >= 0)
                {
                    char odfToken[kProducerBuildMenuTokenLen + 1] = {};
                    TryGetObjectOdfToken(craft, odfToken);
                    Log(L"[AIUNIT] tuning craft=0x%08X odf=%hs range=%.2f->%.2f close=%.2f engage=%hs%.2f standoff=%hs%.2f remaining=%ld\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                        odfToken[0] ? odfToken : "-",
                        originalRange,
                        *range,
                        closeRange ? *closeRange : -1.0f,
                        unitTuning->hasEngageRange ? "" : "-",
                        unitTuning->engageRange,
                        unitTuning->hasWeaponRangeMin ? "" : "-",
                        unitTuning->weaponRangeMin,
                        remaining);
                }
            }

            if (tuning.bomberAiRole &&
                (TraceBomberRangeEnabled() ||
                 TraceAiRangeEnabled()))
            {
                const long remaining = InterlockedDecrement(&g_BomberRangeTraceBudget);
                if (remaining >= 0)
                {
                    char odfToken[kProducerBuildMenuTokenLen + 1] = {};
                    TryGetObjectOdfToken(craft, odfToken);
                    Log(L"[BOMBERRANGE] craft=0x%08X odf=%hs original=%.2f final=%.2f outerFloor=%.2f engage=%hs%.2f weaponMin=%hs%.2f derived=%hs close=%.2f closeFloor=%.2f time=%.2f weapon=0x%08X remaining=%ld\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                        odfToken[0] ? odfToken : "-",
                        originalRange,
                        *range,
                        policyResult.appliedOuterRangeFloor,
                        tuning.hasEngageRangeAI ? "" : "-",
                        tuning.engageRangeAI,
                        tuning.hasWeaponRangeMinAI ? "" : "-",
                        tuning.weaponRangeMinAI,
                        tuning.derivedBomberWeaponRangeAI ? "true" : "false",
                        closeRange ? *closeRange : -1.0f,
                        policyResult.appliedCloseRangeFloor,
                        time ? *time : -1.0f,
                        weapon && *weapon ? static_cast<uint32_t>(reinterpret_cast<uintptr_t>(*weapon)) : 0u,
                        remaining);
                }
            }
        }

        static void ApplyRetargetPeriodAfterDoSubTask(void* processPtr)
        {
            if (!processPtr)
                return;

            auto* processBytes = reinterpret_cast<uint8_t*>(processPtr);
            void* objectPtr = *reinterpret_cast<void**>(processBytes + kUnitProcessObjectOffset);
            if (!objectPtr)
                return;

            if (TraceAiRangeEnabled())
            {
                static volatile long s_RetargetProbeBudget = 24;
                const long remaining = InterlockedDecrement(&s_RetargetProbeBudget);
                if (remaining >= 0)
                {
                    char odfToken[kProducerBuildMenuTokenLen + 1] = {};
                    const bool haveOdf = TryGetObjectOdfToken(objectPtr, odfToken);
                    Log(L"[AIODF] Retarget probe process=0x%08X object=0x%08X odf=%hs active=%hs remaining=%ld\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(processPtr)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectPtr)),
                        haveOdf ? odfToken : "-",
                        BoolText(g_AiOdfGameplayTuningActive),
                        remaining);
                }
            }

            // Global upgrade applies to every covered combat process. Per-unit
            // tuning wins, followed by an enabled ODF override. An explicit
            // non-positive ODF value disables the global upgrade for that unit.
            float retargetPeriod = kGlobalRetargetPeriod;
            bool hasUnitRetargetPeriod = false;
            if (!g_AiUnitTuningOverridesByObject.empty())
            {
                const auto unitIt =
                    g_AiUnitTuningOverridesByObject.find(reinterpret_cast<uintptr_t>(objectPtr));
                if (unitIt != g_AiUnitTuningOverridesByObject.end() &&
                    unitIt->second.hasRetargetPeriod)
                {
                    retargetPeriod = unitIt->second.retargetPeriod;
                    hasUnitRetargetPeriod = true;
                }
            }

            if (!hasUnitRetargetPeriod && g_AiOdfGameplayTuningActive)
            {
                AiTuningConfig tuning = {};
                if (TryGetAiTuningForObject(objectPtr, tuning) && tuning.hasRetargetPeriodAI)
                {
                    retargetPeriod = tuning.retargetPeriodAI;
                }
            }

            // The global/ODF period is simulation-affecting, so single player
            // only like the rest of this section (it reaches every stock unit
            // now). A per-unit period a mission set from Lua still applies.
            const uintptr_t processKey = reinterpret_cast<uintptr_t>(processPtr);
            if (!std::isfinite(retargetPeriod) ||
                retargetPeriod <= 0.0f ||
                !g_BzrFn_GetGameTime ||
                (!hasUnitRetargetPeriod && ReadLocalPlayerNetIdValue() != 0))
            {
                g_RetargetPeriodStateByProcess.erase(processKey);
                return;
            }

            float& nextEnemyCheck =
                *reinterpret_cast<float*>(processBytes + kUnitProcessNextEnemyCheckOffset);
            const float now = g_BzrFn_GetGameTime();
            if (!std::isfinite(now) ||
                !std::isfinite(nextEnemyCheck) ||
                nextEnemyCheck <= now)
            {
                g_RetargetPeriodStateByProcess.erase(processKey);
                return;
            }

            const float clampedPeriod = (std::max)(retargetPeriod, 0.01f);
            const auto stateIt = g_RetargetPeriodStateByProcess.find(processKey);
            if (stateIt != g_RetargetPeriodStateByProcess.end() &&
                nextEnemyCheck == stateIt->second.appliedDeadline &&
                clampedPeriod == stateIt->second.period)
                return;

            // A changed future deadline means stock just scheduled another
            // failed-search retry. Replace that 7-10 second deadline with the
            // per-unit/ODF period while retaining the game's pause-aware clock.
            nextEnemyCheck = now + clampedPeriod;
            g_RetargetPeriodStateByProcess[processKey] =
                { nextEnemyCheck, clampedPeriod };
        }

		// The two Howitzer vtables are rows; 0 when they do not bind.
		static uint32_t HowitzerVtableRow(bool secondary)
		{
			static const uint32_t primary = HookEngine::EngineAddress("HowitzerVtable");
			static const uint32_t second = HookEngine::EngineAddress("HowitzerSecondaryVtable");
			return secondary ? second : primary;
		}

		// Stock howitzers run ArtilleryFriend/ArtilleryEnemy, not the base.
		static bool IsArtilleryProcessVtable(uint32_t vtable)
		{
			if (vtable == 0)
				return false;
			if (vtable == g_ArtilleryProcessVtableAddr)
				return true;
			for (size_t i = 0; i < kRetargetSubclassCount; ++i)
			{
				const char* row = kRetargetSubclassVtables[i].row;
				if (vtable == g_RetargetSubclassVtableAddrs[i] &&
					(std::strcmp(row, "ArtilleryFriendVtable") == 0 ||
					 std::strcmp(row, "ArtilleryEnemyVtable") == 0))
					return true;
			}
			return false;
		}

		static bool SuppressUndeployedHowitzerSniperRetaliation(
			void* processPtr,
			void** outCraft,
			void** outDamageOrdnance)
		{
			if (outCraft)
				*outCraft = nullptr;
			if (outDamageOrdnance)
				*outDamageOrdnance = nullptr;
			if (!g_HowitzerUndeployedRetaliationFixActive || !processPtr ||
				!outCraft || !outDamageOrdnance)
				return false;

			const uint32_t kHowitzerPrimaryVtable = HowitzerVtableRow(false);
			const uint32_t kHowitzerSecondaryVtable = HowitzerVtableRow(true);
			if (!kHowitzerPrimaryVtable || !kHowitzerSecondaryVtable || !g_ArtilleryProcessVtableAddr)
				return false;

			__try
			{
				constexpr size_t kCraftDeployState = 0x228;
				constexpr int32_t kDeployed = 2;
				constexpr size_t kLastDamageOrdnance = 0x98;
				constexpr size_t kOrdnanceClassSignature = 0x0C;
				constexpr uint32_t kSniperSignature = 0x534E4950u; // 'SNIP'

				if (!IsArtilleryProcessVtable(*reinterpret_cast<const uint32_t*>(processPtr)))
					return false;

				auto* process = static_cast<uint8_t*>(processPtr);
				auto* craft = *reinterpret_cast<uint8_t**>(
					process + kProcessOwnerObjectOffset);
				if (!craft)
					return false;

				const uint32_t craftVtable =
					*reinterpret_cast<const uint32_t*>(craft);
				if (craftVtable != kHowitzerPrimaryVtable &&
					craftVtable != kHowitzerSecondaryVtable)
					return false;

				if (*reinterpret_cast<const int32_t*>(craft + kCraftDeployState) ==
					kDeployed)
					return false;

				void* damageOrdnance =
					*reinterpret_cast<void**>(craft + kLastDamageOrdnance);
				if (!damageOrdnance ||
					*reinterpret_cast<const uint32_t*>(
						static_cast<const uint8_t*>(damageOrdnance) +
						kOrdnanceClassSignature) != kSniperSignature)
					return false;

				// OffensiveProcess::DoSubTask has a dedicated recent-SNIP override
				// sourced only from craft+0x98. Hide that source for this one call;
				// follow/go processing and ordinary target acquisition remain stock.
				*reinterpret_cast<void**>(craft + kLastDamageOrdnance) = nullptr;
				*outCraft = craft;
				*outDamageOrdnance = damageOrdnance;
				return true;
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				return false;
			}
		}

		static void RestoreSuppressedSniperDamageOrdnance(
			void* craft,
			void* damageOrdnance)
		{
			if (!craft || !damageOrdnance)
				return;

			__try
			{
				constexpr size_t kLastDamageOrdnance = 0x98;
				auto** slot = reinterpret_cast<void**>(
					static_cast<uint8_t*>(craft) + kLastDamageOrdnance);
				if (*slot == nullptr)
					*slot = damageOrdnance;
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
			}
		}

		bool __fastcall OffensiveProcessDoSubTaskHook(void* thisPtr, void* /*edx*/)
		{
			// A held craft (OpenShimSetAiHold) never switches to SUBATTACK.
			if (IsAiHeldProcess(thisPtr))
				return false;

			void* suppressedCraft = nullptr;
			void* suppressedDamageOrdnance = nullptr;
			const bool suppressed = SuppressUndeployedHowitzerSniperRetaliation(
				thisPtr, &suppressedCraft, &suppressedDamageOrdnance);

			bool result = false;
			__try
			{
				result = g_BzrFn_OffensiveProcessDoSubTask
					? g_BzrFn_OffensiveProcessDoSubTask(thisPtr)
					: false;
			}
			__finally
			{
				if (suppressed)
					RestoreSuppressedSniperDamageOrdnance(
						suppressedCraft, suppressedDamageOrdnance);
			}

			if (suppressed &&
				(TraceArtilleryMaskEnabled() ||
				 TraceWeaponMaskEnabled()))
			{
				const long remaining = InterlockedDecrement(&g_ArtilleryMaskTraceBudget);
				if (remaining >= 0)
					Log(L"[ARTYDEPLOY] Suppressed recent-SNIP target override for undeployed howitzer process=0x%08X craft=0x%08X remaining=%ld\n",
						static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)),
						static_cast<uint32_t>(reinterpret_cast<uintptr_t>(suppressedCraft)),
						remaining);
			}
			RevealProcessOwnerPerceivedTeam(thisPtr, "offensive_post_subtask");
			ApplyRetargetPeriodAfterDoSubTask(thisPtr);
			return result;
        }

        bool __fastcall GunTowerProcessDoSubTaskHook(void* thisPtr, void* /*edx*/)
        {
            const bool result =
                g_BzrFn_GunTowerProcessDoSubTask
                    ? g_BzrFn_GunTowerProcessDoSubTask(thisPtr)
                    : false;
            RevealProcessOwnerPerceivedTeam(thisPtr, "guntower_post_subtask");
            ApplyRetargetPeriodAfterDoSubTask(thisPtr);
            return result;
        }

        // Re-runs the turret's Init range computation when the craft's weapon
        // signature changed (weapon mounted after Init, charge level moved).
        static bool TryReadTurretWeaponSignature(void* processPtr,
                                                 void*& outCraft,
                                                 uint32_t& outSignature)
        {
            __try
            {
                outCraft = *reinterpret_cast<void**>(
                    static_cast<uint8_t*>(processPtr) + kUnitProcessObjectOffset);
                if (!outCraft)
                    return false;
                outSignature = g_BzrFn_CraftWeaponSignature(outCraft);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Same defaults and post-processing as Init 0x005F6B50.
        static bool TryRecomputeTurretRange(void* processPtr,
                                            void* craft,
                                            float& outOldRange,
                                            float& outRange)
        {
            __try
            {
                auto* process = static_cast<uint8_t*>(processPtr);
                float& rangeSq = *reinterpret_cast<float*>(process + kTurretRangeSqOffset);
                outOldRange = std::sqrt((std::max)(rangeSq, 0.0f));

                // Same seeds as Init; compute into locals so a rejected or faulting
                // call leaves the process untouched.
                float close = 0.0f;
                float range = 150.0f;
                float newTime = 1.0f;
                void* weapon = nullptr;
                CalcRangeCraftHook(craft, &close, &range, &newTime, &weapon);
                if (!std::isfinite(range) || !std::isfinite(newTime) ||
                    range <= 0.0f || newTime <= 0.0f)
                    return false;

                *reinterpret_cast<void**>(process + kTurretWeaponOffset) = weapon;
                *reinterpret_cast<float*>(process + kTurretTimeOffset) = newTime;
                *reinterpret_cast<float*>(process + kTurretRangePerTimeOffset) = range / newTime;
                *reinterpret_cast<float*>(process + kTurretTimePerRangeOffset) = newTime / range;
                *reinterpret_cast<float*>(process + kTurretCloseSqOffset) = close * close;
                rangeSq = range * range;
                outRange = range;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void RefreshTurretRangeIfWeaponsChanged(void* processPtr)
        {
            if (!processPtr || !g_AiOdfGameplayTuningActive ||
                !g_BzrFn_CraftWeaponSignature || !g_CalcRangeCraftHookInstalled)
                return;

            void* craft = nullptr;
            uint32_t signature = 0;
            if (!TryReadTurretWeaponSignature(processPtr, craft, signature))
                return;

            const uintptr_t processKey = reinterpret_cast<uintptr_t>(processPtr);
            const auto it = g_TurretRangeSignatureByProcess.find(processKey);
            if (it != g_TurretRangeSignatureByProcess.end() && it->second == signature)
                return;

            float oldRange = 0.0f;
            float range = 0.0f;
            if (!TryRecomputeTurretRange(processPtr, craft, oldRange, range))
                return;
            g_TurretRangeSignatureByProcess[processKey] = signature;

            if (TraceAiRangeEnabled() && range != oldRange)
            {
                static volatile long s_TurretRangeTraceBudget = 64;
                const long remaining = InterlockedDecrement(&s_TurretRangeTraceBudget);
                if (remaining >= 0)
                {
                    char odfToken[kProducerBuildMenuTokenLen + 1] = {};
                    const bool haveOdf = TryGetObjectOdfToken(craft, odfToken);
                    Log(L"[AIODF] Turret range refresh process=0x%08X odf=%hs signature=0x%08X range=%.2f->%.2f remaining=%ld\n",
                        static_cast<uint32_t>(processKey),
                        haveOdf ? odfToken : "-",
                        signature, oldRange, range, remaining);
                }
            }
        }

        bool __fastcall TurretTankProcessDoSubTaskHook(void* thisPtr, void* /*edx*/)
        {
            RefreshTurretRangeIfWeaponsChanged(thisPtr);
            const bool result =
                g_BzrFn_TurretTankProcessDoSubTask
                    ? g_BzrFn_TurretTankProcessDoSubTask(thisPtr)
                    : false;
            RevealProcessOwnerPerceivedTeam(thisPtr, "turrettank_post_subtask");
            ApplyRetargetPeriodAfterDoSubTask(thisPtr);
            return result;
        }

        // TurretTankProcess's own slot is hooked by the retarget table below;
        // this binds the signature function and hooks the Friend/Enemy
        // subclasses, whose slot 11 is the same TurretTankProcess::DoSubTask,
        // with the same hook (range refresh, then retarget period).
        static void InstallTurretRangeRefreshHooksIfPossible()
        {
            if (g_TurretRangeRefreshHooksInstalled)
                return;

            static int s_bound = 0;
            if (s_bound == 0)
            {
                const HookEngine::EngineRow rows[] = {
                    { "CraftWeaponSignature", &g_CraftWeaponSignatureAddr },
                    { "TurretTankFriendVtable", &g_TurretTankFriendVtableAddr },
                    { "TurretTankEnemyVtable", &g_TurretTankEnemyVtableAddr },
                    { "TurretTankProcessDoSubTask", &g_TurretTankProcessDoSubTaskAddr },
                };
                s_bound = HookEngine::BindEngineRows("AI turret range refresh", rows) ? 1 : -1;
            }
            if (s_bound < 0)
            {
                MarkOptionHookFailed("AiOdfGameplayTuning", "Unavailable: AI turret range refresh did not hook on this game build (see openshim.log).");
                return;
            }

            g_BzrFn_TurretTankProcessDoSubTask =
                reinterpret_cast<FnProcessDoSubTask>(g_TurretTankProcessDoSubTaskAddr);

            const struct { const wchar_t* label; const char* rttiName; uintptr_t vtable; } specs[] =
            {
                { L"TurretTankFriend", ".?AVTurretTankFriend@@", g_TurretTankFriendVtableAddr },
                { L"TurretTankEnemy", ".?AVTurretTankEnemy@@", g_TurretTankEnemyVtableAddr },
            };

            void* const hook = reinterpret_cast<void*>(TurretTankProcessDoSubTaskHook);
            bool allInstalled = true;
            for (const auto& spec : specs)
            {
                const uintptr_t slotAddress =
                    spec.vtable + kProcessDoSubTaskVtableSlot * sizeof(void*);
                if (!VtableTypeNameMatches(spec.vtable, spec.rttiName))
                {
                    Log(L"[AIODF] %ls RTTI mismatch vtable=0x%08X; turret range refresh disabled\n",
                        spec.label, static_cast<uint32_t>(spec.vtable));
                    allInstalled = false;
                    continue;
                }

                void* current = nullptr;
                __try
                {
                    current = *reinterpret_cast<void**>(slotAddress);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    current = nullptr;
                }

                if (current != hook &&
                    current != reinterpret_cast<void*>(g_TurretTankProcessDoSubTaskAddr))
                {
                    Log(L"[AIODF] %ls::DoSubTask vtable mismatch slot=0x%08X current=0x%08X expected=0x%08X\n",
                        spec.label,
                        static_cast<uint32_t>(slotAddress),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                        g_TurretTankProcessDoSubTaskAddr);
                    allInstalled = false;
                    continue;
                }

                if (current != hook && !WritePointerValue(slotAddress, hook))
                {
                    Log(L"[AIODF] Failed installing %ls::DoSubTask vtable hook slot=0x%08X\n",
                        spec.label, static_cast<uint32_t>(slotAddress));
                    allInstalled = false;
                    continue;
                }
            }

            if (!allInstalled)
            {
                MarkOptionHookFailed("AiOdfGameplayTuning", "Unavailable: AI turret range refresh did not hook on this game build (see openshim.log).");
                return;
            }

            g_BzrFn_CraftWeaponSignature =
                reinterpret_cast<FnCraftWeaponSignature>(g_CraftWeaponSignatureAddr);
            g_TurretRangeRefreshHooksInstalled = true;
            Log(L"[AIODF] Turret range refresh active signature=0x%08X friend=0x%08X enemy=0x%08X\n",
                g_CraftWeaponSignatureAddr,
                g_TurretTankFriendVtableAddr,
                g_TurretTankEnemyVtableAddr);
        }

		void InstallAiTuningHooksIfPossible()
        {
            InstallAiNativeOrdersHooksIfPossible();
            InstallTurretAttackOrdersHooksIfPossible();
            InstallProducerRallyPointsIfPossible();
            InstallAutoGroupNewUnitsIfPossible();
            InstallAttackTaskKiteHookIfPossible();
            InstallScrapPathScoreHookIfPossible();
            InstallScavengerRetargetHookIfPossible();
            // These installs are retried, so a hook that lands on a later
            // pass takes back an earlier Unavailable mark.
            if (g_AttackTaskDoStateHookInstalled && GetLegacyAttackHelpers())
                ClearOptionHookFailed("LegacyTankAi");
            if (g_ScrapPathScoreHookInstalled && g_ScrapRetargetHookInstalled)
                ClearOptionHookFailed("SmartScavengerPathing");

            if (g_CalcRangeCraftHookInstalled &&
                g_RetargetPeriodHooksInstalled &&
                g_TurretRangeRefreshHooksInstalled &&
                g_AttackTaskDoStateHookInstalled &&
                g_ScrapPathScoreHookInstalled &&
                g_ScrapRetargetHookInstalled)
                return;

            if (g_CalcRangeCraftDetour.trampoline && g_BzrFn_CalcRangeCraft)
            {
                g_CalcRangeCraftHookInstalled = true;
                ClearOptionHookFailed("AiOdfGameplayTuning");
            }

            if (!g_CalcRangeCraftHookInstalled)
            {
                static const uint8_t kExpectedCalcRangeCraftBytes[kCalcRangeCraftDetourLen] =
                {
                    0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x1C, 0x8B, 0x45, 0x0C
                };
                const uintptr_t calcRangeCraftEntryAddr =
                    static_cast<uintptr_t>(
                        HookEngine::ResolveNamedAddress("CalcRange(Craft)"));

                if (calcRangeCraftEntryAddr == 0)
                {
                    Log(L"[AIODF] CalcRange(Craft) resolver failed; AI ODF range tuning disabled\n");
                    MarkOptionHookFailed("AiOdfGameplayTuning", "Unavailable: AI ODF range tuning did not hook on this game build (see openshim.log).");
                }
                else if (!ExpectedBytesMatchAt(calcRangeCraftEntryAddr,
                                          kExpectedCalcRangeCraftBytes,
                                          sizeof(kExpectedCalcRangeCraftBytes)))
                {
                    Log(L"[AIODF] CalcRange(Craft) entry bytes mismatch at 0x%08X; AI ODF range tuning disabled\n",
                        static_cast<uint32_t>(calcRangeCraftEntryAddr));
                    MarkOptionHookFailed("AiOdfGameplayTuning", "Unavailable: AI ODF range tuning did not hook on this game build (see openshim.log).");
                }
                else if (!InstallInlineDetour32(g_CalcRangeCraftDetour,
                                                calcRangeCraftEntryAddr,
                                                reinterpret_cast<void*>(CalcRangeCraftHook),
                                                kCalcRangeCraftDetourLen,
                                                kExpectedCalcRangeCraftBytes,
                                                sizeof(kExpectedCalcRangeCraftBytes)))
                {
                    Log(L"[AIODF] Failed installing CalcRange(Craft) hook at 0x%08X\n",
                        static_cast<uint32_t>(calcRangeCraftEntryAddr));
                    MarkOptionHookFailed("AiOdfGameplayTuning", "Unavailable: AI ODF range tuning did not hook on this game build (see openshim.log).");
                }
                else
                {
                    g_BzrFn_CalcRangeCraft =
                        reinterpret_cast<FnCalcRangeCraft>(g_CalcRangeCraftDetour.trampoline);
                    g_CalcRangeCraftHookInstalled = (g_BzrFn_CalcRangeCraft != nullptr);
                    if (g_CalcRangeCraftHookInstalled)
                    {
                        ClearOptionHookFailed("AiOdfGameplayTuning");
                        Log(L"[AIODF] Installed CalcRange(Craft) hook entry=0x%08X trampoline=0x%08X\n",
                            static_cast<uint32_t>(calcRangeCraftEntryAddr),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_CalcRangeCraftDetour.trampoline)));
                    }
                }
            }

            InstallTurretRangeRefreshHooksIfPossible();

            if (g_RetargetPeriodHooksInstalled)
                return;

            static int s_retargetBound = 0;
            if (s_retargetBound == 0)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ArtilleryProcessVtable", &g_ArtilleryProcessVtableAddr },
                    { "BomberProcessVtable", &g_BomberProcessVtableAddr },
                    { "GechProcessVtable", &g_GechProcessVtableAddr },
                    { "OffensiveProcessVtable", &g_OffensiveProcessVtableAddr },
                    { "PersonProcessVtable", &g_PersonProcessVtableAddr },
                    { "RocketTankProcessVtable", &g_RocketTankProcessVtableAddr },
                    { "ScoutProcessVtable", &g_ScoutProcessVtableAddr },
                    { "SoldierProcessVtable", &g_SoldierProcessVtableAddr },
                    { "TankProcessVtable", &g_TankProcessVtableAddr },
                    { "WingmanProcessVtable", &g_WingmanProcessVtableAddr },
                    { "GunTowerProcessVtable", &g_GunTowerProcessVtableAddr },
                    { "TurretTankProcessVtable", &g_TurretTankProcessVtableAddr },
                    { "OffensiveProcessDoSubTask", &g_OffensiveProcessDoSubTaskAddr },
                    { "GunTowerProcessDoSubTask", &g_GunTowerProcessDoSubTaskAddr },
                    { "TurretTankProcessDoSubTask", &g_TurretTankProcessDoSubTaskAddr },
                    { "GetGameTime", &g_GetGameTimeAddr },
                };
                s_retargetBound = HookEngine::BindEngineRows("AI retarget period", rows) ? 1 : -1;
                // One row at a time: an unbound subclass stays 0 and is
                // skipped below without costing the others.
                for (size_t i = 0; s_retargetBound > 0 && i < kRetargetSubclassCount; ++i)
                {
                    const HookEngine::EngineRow row =
                        { kRetargetSubclassVtables[i].row, &g_RetargetSubclassVtableAddrs[i] };
                    if (!HookEngine::BindEngineRows("AI retarget period subclasses", &row, 1))
                        g_RetargetSubclassVtableAddrs[i] = 0;
                }
            }
            if (s_retargetBound < 0)
                return;

            g_BzrFn_GetGameTime = reinterpret_cast<FnGetGameTime>(g_GetGameTimeAddr);

            struct RetargetVtableHookSpec
            {
                const wchar_t* label;
                const char* rttiName;
                uintptr_t vtableAddress;
                uintptr_t originalAddress;
                void* hook;
                FnProcessDoSubTask* original;
            };

            // The 12 base classes, then kRetargetSubclassVtables. A fixed
            // array: this function uses __try, so no unwinding objects.
            constexpr size_t kRetargetBaseCount = 12;
            RetargetVtableHookSpec hooks[kRetargetBaseCount + kRetargetSubclassCount] =
            {
                { L"ArtilleryProcess", ".?AVArtilleryProcess@@", g_ArtilleryProcessVtableAddr,
                  g_OffensiveProcessDoSubTaskAddr, reinterpret_cast<void*>(OffensiveProcessDoSubTaskHook),
                  &g_BzrFn_OffensiveProcessDoSubTask },
                { L"BomberProcess", ".?AVBomberProcess@@", g_BomberProcessVtableAddr,
                  g_OffensiveProcessDoSubTaskAddr, reinterpret_cast<void*>(OffensiveProcessDoSubTaskHook),
                  &g_BzrFn_OffensiveProcessDoSubTask },
                { L"GechProcess", ".?AVGechProcess@@", g_GechProcessVtableAddr,
                  g_OffensiveProcessDoSubTaskAddr, reinterpret_cast<void*>(OffensiveProcessDoSubTaskHook),
                  &g_BzrFn_OffensiveProcessDoSubTask },
                { L"OffensiveProcess", ".?AVOffensiveProcess@@", g_OffensiveProcessVtableAddr,
                  g_OffensiveProcessDoSubTaskAddr, reinterpret_cast<void*>(OffensiveProcessDoSubTaskHook),
                  &g_BzrFn_OffensiveProcessDoSubTask },
                { L"PersonProcess", ".?AVPersonProcess@@", g_PersonProcessVtableAddr,
                  g_OffensiveProcessDoSubTaskAddr, reinterpret_cast<void*>(OffensiveProcessDoSubTaskHook),
                  &g_BzrFn_OffensiveProcessDoSubTask },
                { L"RocketTankProcess", ".?AVRocketTankProcess@@", g_RocketTankProcessVtableAddr,
                  g_OffensiveProcessDoSubTaskAddr, reinterpret_cast<void*>(OffensiveProcessDoSubTaskHook),
                  &g_BzrFn_OffensiveProcessDoSubTask },
                { L"ScoutProcess", ".?AVScoutProcess@@", g_ScoutProcessVtableAddr,
                  g_OffensiveProcessDoSubTaskAddr, reinterpret_cast<void*>(OffensiveProcessDoSubTaskHook),
                  &g_BzrFn_OffensiveProcessDoSubTask },
                { L"SoldierProcess", ".?AVSoldierProcess@@", g_SoldierProcessVtableAddr,
                  g_OffensiveProcessDoSubTaskAddr, reinterpret_cast<void*>(OffensiveProcessDoSubTaskHook),
                  &g_BzrFn_OffensiveProcessDoSubTask },
                { L"TankProcess", ".?AVTankProcess@@", g_TankProcessVtableAddr,
                  g_OffensiveProcessDoSubTaskAddr, reinterpret_cast<void*>(OffensiveProcessDoSubTaskHook),
                  &g_BzrFn_OffensiveProcessDoSubTask },
                { L"WingmanProcess", ".?AVWingmanProcess@@", g_WingmanProcessVtableAddr,
                  g_OffensiveProcessDoSubTaskAddr, reinterpret_cast<void*>(OffensiveProcessDoSubTaskHook),
                  &g_BzrFn_OffensiveProcessDoSubTask },
                { L"GunTowerProcess", ".?AVGunTowerProcess@@",
                  g_GunTowerProcessVtableAddr, g_GunTowerProcessDoSubTaskAddr,
                  reinterpret_cast<void*>(GunTowerProcessDoSubTaskHook),
                  &g_BzrFn_GunTowerProcessDoSubTask },
                { L"TurretTankProcess", ".?AVTurretTankProcess@@",
                  g_TurretTankProcessVtableAddr, g_TurretTankProcessDoSubTaskAddr,
                  reinterpret_cast<void*>(TurretTankProcessDoSubTaskHook),
                  &g_BzrFn_TurretTankProcessDoSubTask },
            };
            for (size_t i = 0; i < kRetargetSubclassCount; ++i)
            {
                const AiSubclassVtable& sub = kRetargetSubclassVtables[i];
                RetargetVtableHookSpec& spec = hooks[kRetargetBaseCount + i];
                spec.label = sub.label;
                spec.rttiName = sub.rttiName;
                spec.vtableAddress = g_RetargetSubclassVtableAddrs[i];
                if (sub.gunTower)
                {
                    spec.originalAddress = g_GunTowerProcessDoSubTaskAddr;
                    spec.hook = reinterpret_cast<void*>(GunTowerProcessDoSubTaskHook);
                    spec.original = &g_BzrFn_GunTowerProcessDoSubTask;
                }
                else
                {
                    spec.originalAddress = g_OffensiveProcessDoSubTaskAddr;
                    spec.hook = reinterpret_cast<void*>(OffensiveProcessDoSubTaskHook);
                    spec.original = &g_BzrFn_OffensiveProcessDoSubTask;
                }
            }

            bool allInstalled = true;
            for (RetargetVtableHookSpec& spec : hooks)
            {
                *spec.original = reinterpret_cast<FnProcessDoSubTask>(spec.originalAddress);
                const uintptr_t slotAddress =
                    spec.vtableAddress + kProcessDoSubTaskVtableSlot * sizeof(void*);

                if (spec.vtableAddress == 0 ||
                    !VtableTypeNameMatches(spec.vtableAddress, spec.rttiName))
                {
                    Log(L"[AIODF] %ls unbound or RTTI mismatch vtable=0x%08X; retarget tuning disabled there\n",
                        spec.label, static_cast<uint32_t>(spec.vtableAddress));
                    allInstalled = false;
                    continue;
                }

                void* current = nullptr;
                __try
                {
                    current = *reinterpret_cast<void**>(slotAddress);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    current = nullptr;
                }

                if (current != spec.hook &&
                    current != reinterpret_cast<void*>(spec.originalAddress))
                {
                    Log(L"[AIODF] %ls::DoSubTask vtable mismatch slot=0x%08X current=0x%08X expected=0x%08X\n",
                        spec.label,
                        static_cast<uint32_t>(slotAddress),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                        static_cast<uint32_t>(spec.originalAddress));
                    allInstalled = false;
                    continue;
                }

                const bool patched =
                    current == spec.hook || WritePointerValue(slotAddress, spec.hook);
                if (!patched)
                {
                    Log(L"[AIODF] Failed installing %ls::DoSubTask vtable hook slot=0x%08X\n",
                        spec.label, static_cast<uint32_t>(slotAddress));
                    allInstalled = false;
                    continue;
                }

                if (current != spec.hook)
                {
                    Log(L"[AIODF] Installed %ls::DoSubTask vtable hook slot=0x%08X original=0x%08X\n",
                        spec.label,
                        static_cast<uint32_t>(slotAddress),
                        static_cast<uint32_t>(spec.originalAddress));
                }
            }

            g_RetargetPeriodHooksInstalled = allInstalled;
            if (allInstalled)
            {
                Log(L"[AIODF] Global retarget upgrade active period=%.2f classes=%u\n",
                    kGlobalRetargetPeriod,
                    static_cast<unsigned>(sizeof(hooks) / sizeof(hooks[0])));
            }
        }

        static bool TryReadOrdnanceRangeFromOdfFile(const char* ordnanceToken, float& outRange)
        {
            outRange = 0.0f;

            std::filesystem::path resolvedPath;
            if (!TryResolveOdfFilePath(ordnanceToken, resolvedPath))
                return false;

            FILE* file = nullptr;
            if (fopen_s(&file, resolvedPath.string().c_str(), "r") != 0 || !file)
                return false;

            float shotSpeed = 0.0f;
            float lifeSpan = 0.0f;
            bool haveShotSpeed = false;
            bool haveLifeSpan = false;
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

                float parsedFloat = 0.0f;
                if (_stricmp(key, "shotSpeed") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    shotSpeed = parsedFloat;
                    haveShotSpeed = true;
                }
                else if (_stricmp(key, "lifeSpan") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    lifeSpan = parsedFloat;
                    haveLifeSpan = true;
                }
            }

            std::fclose(file);

            if (!haveShotSpeed || !haveLifeSpan || shotSpeed <= 0.0f || lifeSpan <= 0.0f)
                return false;

            outRange = (std::max)(shotSpeed * lifeSpan - 1.0f, 0.0f);
            return std::isfinite(outRange) && outRange > 0.0f;
        }

        static bool TryReadWeaponRangeFromOdfFile(const char* weaponToken, float& outRange)
        {
            outRange = 0.0f;

            std::filesystem::path resolvedPath;
            if (!TryResolveOdfFilePath(weaponToken, resolvedPath))
                return false;

            FILE* file = nullptr;
            if (fopen_s(&file, resolvedPath.string().c_str(), "r") != 0 || !file)
                return false;

            ProducerBuildMenuEntry ordnanceToken = {};
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

                if (_stricmp(key, "ordName") == 0)
                {
                    ordnanceToken = NormalizeQuotedOdfToken(value);
                    break;
                }
            }

            std::fclose(file);

            if (!ordnanceToken.hasValue)
                return false;

            return TryReadOrdnanceRangeFromOdfFile(ordnanceToken.token, outRange);
        }

        static bool TryReadAiTuningFromOdfFile(const char* odfToken, AiTuningConfig& outConfig)
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
            bool bomberAiRole = false;
            ProducerBuildMenuEntry weaponTokens[5] = {};
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

                float parsedFloat = 0.0f;
                bool parsedBool = false;

                if (_stricmp(key, "engageRangeAI") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    outConfig.hasEngageRangeAI = true;
                    outConfig.engageRangeAI = parsedFloat;
                    foundAny = true;
                }
                else if (_stricmp(key, "weaponRangeMinAI") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    outConfig.hasWeaponRangeMinAI = true;
                    outConfig.weaponRangeMinAI = parsedFloat;
                    foundAny = true;
                }
                else if (_stricmp(key, "retargetPeriodAI") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    outConfig.hasRetargetPeriodAI = true;
                    outConfig.retargetPeriodAI = parsedFloat;
                    foundAny = true;
                }
                else if (_stricmp(key, "stuckCheckPeriodAI") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    outConfig.hasStuckCheckPeriodAI = true;
                    outConfig.stuckCheckPeriodAI = parsedFloat;
                    foundAny = true;
                }
                else if (_stricmp(key, "stuckReverseTimeAI") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    outConfig.hasStuckReverseTimeAI = true;
                    outConfig.stuckReverseTimeAI = parsedFloat;
                    foundAny = true;
                }
                else if (_stricmp(key, "stuckStrafeTimeAI") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    outConfig.hasStuckStrafeTimeAI = true;
                    outConfig.stuckStrafeTimeAI = parsedFloat;
                    foundAny = true;
                }
                else if (_stricmp(key, "scrapPathingAI") == 0 && TryParseBoolValue(value, parsedBool))
                {
                    outConfig.hasScrapPathingAI = true;
                    outConfig.scrapPathingAI = parsedBool;
                    foundAny = true;
                }
                else if (_stricmp(key, "scrapPathLengthWeightAI") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    outConfig.hasScrapPathLengthWeightAI = true;
                    outConfig.scrapPathLengthWeightAI = parsedFloat;
                    foundAny = true;
                }
                else if (_stricmp(key, "scrapStraightDistanceWeightAI") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    outConfig.hasScrapStraightDistanceWeightAI = true;
                    outConfig.scrapStraightDistanceWeightAI = parsedFloat;
                    foundAny = true;
                }
                else if (_stricmp(key, "scrapPathFailPenaltyAI") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    outConfig.hasScrapPathFailPenaltyAI = true;
                    outConfig.scrapPathFailPenaltyAI = parsedFloat;
                    foundAny = true;
                }
                else if (_stricmp(key, "scrapHardToGetCooldownAI") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    outConfig.hasScrapHardToGetCooldownAI = true;
                    outConfig.scrapHardToGetCooldownAI = parsedFloat;
                    foundAny = true;
                }
                else if (_stricmp(key, "scrapSearchRadiusAI") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    outConfig.hasScrapSearchRadiusAI = true;
                    outConfig.scrapSearchRadiusAI = parsedFloat;
                    foundAny = true;
                }
                else if (_stricmp(key, "scrapRetargetPeriodAI") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    outConfig.hasScrapRetargetPeriodAI = true;
                    outConfig.scrapRetargetPeriodAI = parsedFloat;
                    foundAny = true;
                }
                else if (_stricmp(key, "scrapRetargetMinImprovementAI") == 0 && TryParseFloatValue(value, parsedFloat))
                {
                    outConfig.hasScrapRetargetMinImprovementAI = true;
                    outConfig.scrapRetargetMinImprovementAI = parsedFloat;
                    foundAny = true;
                }
                else if (_stricmp(key, "aiName") == 0 || _stricmp(key, "aiName2") == 0)
                {
                    char normalizedAiName[64] = {};
                    if (TryNormalizeQuotedStringValue(value, normalizedAiName, sizeof(normalizedAiName)))
                    {
                        if (strcmp(normalizedAiName, "bomberfriend") == 0 ||
                            strcmp(normalizedAiName, "bomberenemy") == 0)
                        {
                            bomberAiRole = true;
                            outConfig.bomberAiRole = true;
                        }
                        if (strcmp(normalizedAiName, "tanklegacyfriend") == 0 ||
                            strcmp(normalizedAiName, "tanklegacyenemy") == 0 ||
                            strcmp(normalizedAiName, "tanklegacy") == 0)
                        {
                            outConfig.legacyAiRole = true;
                            foundAny = true;
                        }
                    }
                }
                else if (_stricmp(key, "legacyAI") == 0 || _stricmp(key, "legacyAi") == 0 ||
                         _stricmp(key, "legacy14") == 0 || _stricmp(key, "legacy14AI") == 0)
                {
                    bool parsedLegacy = false;
                    if (TryParseBoolValue(value, parsedLegacy))
                    {
                        outConfig.legacyAiRole = parsedLegacy;
                        outConfig.legacyAiOptOut = !parsedLegacy;
                        // An opt-out alone is not tuning: the ODF keeps the
                        // stock range path, as before the global option.
                        if (parsedLegacy)
                            foundAny = true;
                    }
                    else
                    {
                        float parsedFloatLegacy = 0.0f;
                        if (TryParseFloatValue(value, parsedFloatLegacy) && parsedFloatLegacy != 0.0f)
                        {
                            outConfig.legacyAiRole = true;
                            foundAny = true;
                        }
                    }
                }
                else if (_strnicmp(key, "weaponName", 10) == 0 &&
                         std::isdigit(static_cast<unsigned char>(key[10])) &&
                         key[11] == '\0')
                {
                    const int index = key[10] - '1';
                    if (index >= 0 && index < 5)
                        weaponTokens[index] = NormalizeQuotedOdfToken(value);
                }
            }

            std::fclose(file);

            if (bomberAiRole && !outConfig.hasEngageRangeAI && !outConfig.hasWeaponRangeMinAI)
            {
                float derivedRange = 0.0f;
                bool haveDerivedRange = false;
                for (const auto& weaponToken : weaponTokens)
                {
                    if (!weaponToken.hasValue)
                        continue;

                    float weaponRange = 0.0f;
                    if (!TryReadWeaponRangeFromOdfFile(weaponToken.token, weaponRange))
                        continue;

                    if (!haveDerivedRange || weaponRange > derivedRange)
                    {
                        derivedRange = weaponRange;
                        haveDerivedRange = true;
                    }
                }

                if (haveDerivedRange)
                {
                    outConfig.hasWeaponRangeMinAI = true;
                    outConfig.weaponRangeMinAI = derivedRange;
                    outConfig.derivedBomberWeaponRangeAI = true;
                    foundAny = true;
                }
            }

            if (foundAny)
            {
                outConfig.parsed = true;
                Log(L"[AIODF] Loaded tuning odf=%hs engage=%hs%.2f weaponMin=%hs%.2f retarget=%hs%.2f bomberDerived=%hs scrapPathing=%hs pathWeight=%hs%.3f straightWeight=%hs%.3f scrapRetarget=%hs%.2f improve=%hs%.2f file=%hs\n",
                    odfKey.token,
                    outConfig.hasEngageRangeAI ? "" : "-",
                    outConfig.engageRangeAI,
                    outConfig.hasWeaponRangeMinAI ? "" : "-",
                    outConfig.weaponRangeMinAI,
                    outConfig.hasRetargetPeriodAI ? "" : "-",
                    outConfig.retargetPeriodAI,
                    outConfig.derivedBomberWeaponRangeAI ? "true" : "false",
                    outConfig.scrapPathingAI ? "true" : "false",
                    outConfig.hasScrapPathLengthWeightAI ? "" : "-",
                    outConfig.scrapPathLengthWeightAI,
                    outConfig.hasScrapStraightDistanceWeightAI ? "" : "-",
                    outConfig.scrapStraightDistanceWeightAI,
                    outConfig.hasScrapRetargetPeriodAI ? "" : "default:",
                    outConfig.scrapRetargetPeriodAI,
                    outConfig.hasScrapRetargetMinImprovementAI ? "" : "default:",
                    outConfig.scrapRetargetMinImprovementAI,
                    resolvedPath.string().c_str());
            }

            return foundAny;
        }

        bool TryGetAiTuningForObject(void* objectPtr, AiTuningConfig& outConfig)
        {
            outConfig = {};

            char odfToken[kProducerBuildMenuTokenLen + 1] = {};
            if (!TryGetObjectOdfToken(objectPtr, odfToken))
                return false;

            const auto cached = g_AiTuningCache.odfEntries.find(odfToken);
            if (cached != g_AiTuningCache.odfEntries.end())
            {
                outConfig = cached->second;
                return outConfig.parsed;
            }

            AiTuningConfig loaded = {};
            TryReadAiTuningFromOdfFile(odfToken, loaded);
            g_AiTuningCache.odfEntries[odfToken] = loaded;
            outConfig = loaded;
            return outConfig.parsed;
        }
    }

}
