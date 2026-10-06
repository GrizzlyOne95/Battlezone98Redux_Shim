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

        // AttackTask flee (state 9) and blast (state 10), and the stuck sample
        // IsStuck (FUN_006027f0) keeps on the task: FUN_00602920 rewrites the
        // sample time to now + 5 and the sample position to the craft's
        // position whenever the window has elapsed.
        constexpr int kAttackTaskFleeState = 9;

        constexpr int kAttackTaskBlastState = 10;

        constexpr size_t kAttackTaskStuckSampleTimeOffset = 0x84;

        constexpr size_t kAttackTaskStuckSamplePosOffset = 0x88;

        constexpr size_t kCraftVehicleOffset = 0x230;

        constexpr size_t kVehicleStuckFlagsOffset = 0x114;

        // IsStuck's first test: bool __cdecl(const float* position), true on
        // terrain cell types 5 and 6. It only reads the terrain.
        uint32_t g_TerrainBlocksCraftAddr = 0;

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

        constexpr size_t kUnitProcessNextEnemyCheckOffset = 0x30;

        constexpr size_t kUnitProcessObjectOffset = 0x34;

        static volatile long g_ArtilleryMaskTraceBudget = 400;

        static volatile long g_BomberRangeTraceBudget = 200;

        static InlineDetour32 g_CalcRangeCraftDetour = {};

        static bool TryGetGameObjectPosition(void* objectPtr,
                                             double& outX,
                                             double& outY,
                                             double& outZ)
        {
            if (!objectPtr)
                return false;

            __try
            {
                const auto* transform = reinterpret_cast<const LegacyMat3*>(
                    reinterpret_cast<const uint8_t*>(objectPtr) + kObj76TransformOffset);
                outX = transform->posit_x;
                outY = transform->posit_y;
                outZ = transform->posit_z;
                return std::isfinite(outX) && std::isfinite(outY) && std::isfinite(outZ);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
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
            if (unitIt != g_AiUnitTuningOverridesByObject.end() && unitIt->second.hasLegacyAi && unitIt->second.legacyAi)
                return true;
            AiTuningConfig odfCfg = {};
            if (TryGetAiTuningForObject(craft, odfCfg) && odfCfg.legacyAiRole)
                return true;
            // Also check ODF-driven legacy via direct aiName string fallback (if map not yet populated)
            // The TryGetAiTuningForObject path already reads aiName, so above is sufficient.
            return false;
        }

        static bool TryGetTaskState(uint8_t* taskBytes, int& outState, int& outNextState, float& outStartTime)
        {
            if (!taskBytes) return false;
            __try
            {
                outState = *reinterpret_cast<int*>(taskBytes + kAttackTaskCurStateOffset);
                outNextState = *reinterpret_cast<int*>(taskBytes + kAttackTaskNextStateOffset);
                // startTime is at +0x100 in Redux (was +0xD4 in 1.4)
                outStartTime = *reinterpret_cast<float*>(taskBytes + 0x100);
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

        static bool TryReadAttackTaskStuckSample(uint8_t* taskBytes, float& outTime, float (&outPos)[3])
        {
            if (!taskBytes)
                return false;
            __try
            {
                outTime = *reinterpret_cast<float*>(taskBytes + kAttackTaskStuckSampleTimeOffset);
                const auto* pos = reinterpret_cast<float*>(taskBytes + kAttackTaskStuckSamplePosOffset);
                outPos[0] = pos[0];
                outPos[1] = pos[1];
                outPos[2] = pos[2];
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Stock flee (FUN_00478a50, state 9) leaves for blast either because
        // IsStuck returned true or because the 3 s timeout ran out. Work out
        // which after the fact, without calling IsStuck again: a second call
        // would take a fresh stuck sample. If the sample window elapsed during
        // the stock call, IsStuck compared the old sample with the new one
        // (stuck when under 5 m). If it did not, only its terrain test could
        // have said stuck, and that test has no side effects, so repeat it.
        // Returns false when the verdict cannot be read; the caller then keeps
        // stock behaviour.
        static bool TryJudgeLegacyFleeExitWasStuck(uint8_t* taskBytes,
                                                   void* craft,
                                                   float sampleTimeBefore,
                                                   const float (&samplePosBefore)[3],
                                                   bool& outStuck)
        {
            outStuck = true;
            float sampleTimeAfter = 0.0f;
            float samplePosAfter[3] = {};
            if (!TryReadAttackTaskStuckSample(taskBytes, sampleTimeAfter, samplePosAfter))
                return false;

            if (sampleTimeAfter != sampleTimeBefore)
            {
                const float dx = samplePosAfter[0] - samplePosBefore[0];
                const float dy = samplePosAfter[1] - samplePosBefore[1];
                const float dz = samplePosAfter[2] - samplePosBefore[2];
                outStuck = (dx * dx + dy * dy + dz * dz) < 25.0f;
                return true;
            }

            static int s_terrainTestVerified = -1;
            if (s_terrainTestVerified < 0)
            {
                g_TerrainBlocksCraftAddr = HookEngine::EngineAddress("TerrainBlocksCraft");
                s_terrainTestVerified = g_TerrainBlocksCraftAddr != 0 ? 1 : 0;
                if (!s_terrainTestVerified)
                    Log(L"[LEGACY] D3 disabled: terrain test row does not bind; legacy flee follows stock\n");
            }
            if (!s_terrainTestVerified)
                return false;

            __try
            {
                void* vehicle = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(craft) + kCraftVehicleOffset);
                if (!vehicle)
                    return false;
                const uint32_t flags = *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint8_t*>(vehicle) + kVehicleStuckFlagsOffset);
                if ((flags & 4) != 0)
                {
                    outStuck = false;
                    return true;
                }
                const float* position = TryCallEntityGetPosition(craft);
                if (!position)
                    return false;
                using FnTerrainBlocksCraft = bool(__cdecl*)(const float* position);
                outStuck = reinterpret_cast<FnTerrainBlocksCraft>(g_TerrainBlocksCraftAddr)(position);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void __fastcall AttackTaskDoStateTuningHook(void* taskPtr, void* /*edx*/)
        {
            if (!g_BzrFn_AttackTaskDoState || !taskPtr)
                return;

            auto* taskBytes = reinterpret_cast<uint8_t*>(taskPtr);
            void* craft = nullptr;
            void* target = nullptr;
            if (!TryReadAttackTaskEndpoints(taskBytes, craft, target))
            {
                g_BzrFn_AttackTaskDoState(taskPtr);
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
                g_BzrFn_AttackTaskDoState(taskPtr);
                return;
            }

            // Legacy-only fast path (no kite tuning, but legacy flag set)
            if (isLegacyCraft && !hasKiteTuning)
            {
                // The port is partial, and a modder who sets legacyAI=1 should
                // be able to read which parts of 1.4 they are getting.
                static volatile LONG s_legacyPartialLogged = 0;
                if (InterlockedCompareExchange(&s_legacyPartialLogged, 1, 0) == 0)
                {
                    Log(L"[LEGACY] 1.4 AI profile active (first craft 0x%08X): D1 (able-to-hit -> slide), "
                        L"D3 (flee without the 3 s cap) and D4 (stand timeout -> slide) apply; D2 (slide exit) "
                        L"is not ported, so slide exits follow stock Redux\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)));
                }
                int curBefore = 0, nextBefore = 0;
                float startBefore = 0.0f;
                TryGetTaskState(taskBytes, curBefore, nextBefore, startBefore);
                float stuckSampleTimeBefore = 0.0f;
                float stuckSamplePosBefore[3] = {};
                const bool haveStuckSample =
                    curBefore == kAttackTaskFleeState &&
                    TryReadAttackTaskStuckSample(taskBytes, stuckSampleTimeBefore, stuckSamplePosBefore);
                g_BzrFn_AttackTaskDoState(taskPtr);
                int curAfter = 0, nextAfter = 0;
                float startAfter = 0.0f;
                TryGetTaskState(taskBytes, curAfter, nextAfter, startAfter);
                // Apply legacy D1, D3, D4 post-hoc. D2 requires enemy state read.
                // D1: case 2 AbleToHit -> slide (7) not blast (10)
                if (curBefore == 2 && nextAfter == 10)
                {
                    // Stock 1.5/Redux goes to blast; 1.4 goes to slide
                    *reinterpret_cast<int*>(taskBytes + kAttackTaskNextStateOffset) = 7;
                    if (TraceLegacyAiEnabled() || TraceAiRangeEnabled())
                    {
                        Log(L"[LEGACY] D1 override craft=0x%08X cur=2 next 10->7\n", static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)));
                    }
                }
                // D4: case 8 stand expiry (>8s) -> slide (7) not flee (9)
                // Detect 8->9 transition; distinguish hit vs timeout via damage time vs start
                if (curBefore == 8 && nextAfter == 9)
                {
                    // Check if this was timeout (not fresh hit). Fresh hit would also be 8->9 but we want to keep hit as 9.
                    // Use craft damage time vs task start: if lastDamageTime > startAfter (fresh), keep 9.
                    bool isFreshHit = false;
                    __try
                    {
                        // craft damage fields: +0x1E0 time, task start at +0x100 (Redux)
                        float* craftDamageTime = reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(craft) + 0x1E0);
                        float* taskStart = reinterpret_cast<float*>(taskBytes + 0x100);
                        if (craftDamageTime && taskStart && *craftDamageTime > *taskStart)
                            isFreshHit = true;
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER) {}
                    if (!isFreshHit)
                    {
                        *reinterpret_cast<int*>(taskBytes + kAttackTaskNextStateOffset) = 7;
                        if (TraceLegacyAiEnabled())
                            Log(L"[LEGACY] D4 override craft=0x%08X 8->9 => 8->7 (timeout)\n", static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)));
                    }
                }
                // D3: 1.4 flee has no 3 s bound. Stock leaves flee (9) for blast
                // (10) on IsStuck or on the timeout; keep only the stuck exit so
                // a stuck legacy craft still gets out. Leaving the 75 m band
                // (9 -> 7) is untouched.
                if (curBefore == kAttackTaskFleeState && nextAfter == kAttackTaskBlastState && haveStuckSample)
                {
                    bool stuck = true;
                    if (TryJudgeLegacyFleeExitWasStuck(taskBytes, craft, stuckSampleTimeBefore,
                                                       stuckSamplePosBefore, stuck) &&
                        !stuck)
                    {
                        *reinterpret_cast<int*>(taskBytes + kAttackTaskNextStateOffset) = kAttackTaskFleeState;
                        if (TraceLegacyAiEnabled())
                            Log(L"[LEGACY] D3 override craft=0x%08X 9->10 => stay 9 (timeout, not stuck)\n",
                                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)));
                    }
                }
                // D2: case 7 slide-exit enemy state {2,5,7} uncapped vs IsBuilding+10s
                // TODO: implement enemy task state read: handle at +0x14 -> object -> +0x30 -> state at +0x08
                // Not ported: slide exits follow stock Redux.
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
                g_BzrFn_AttackTaskDoState(taskPtr);
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
                g_BzrFn_AttackTaskDoState(taskPtr);
                return;
            }

            const double dx = craftX - targetX;
            const double dy = craftY - targetY;
            const double dz = craftZ - targetZ;
            const double horizontalSq = (dx * dx) + (dz * dz);
            const double distanceSqD = horizontalSq + (dy * dy);
            if (!std::isfinite(distanceSqD) || distanceSqD <= 0.0001 || horizontalSq <= 0.0001)
            {
                g_BzrFn_AttackTaskDoState(taskPtr);
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

            g_BzrFn_AttackTaskDoState(taskPtr);

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
                return;

            if (!ExpectedBytesMatchAt(g_AttackTaskDoStateEntryAddr,
                                      kExpectedAttackTaskDoStateBytes,
                                      sizeof(kExpectedAttackTaskDoStateBytes)))
            {
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
                g_BomberAiRangeActive &&
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

            const uintptr_t processKey = reinterpret_cast<uintptr_t>(processPtr);
            if (!std::isfinite(retargetPeriod) ||
                retargetPeriod <= 0.0f ||
                !g_BzrFn_GetGameTime)
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

				if (*reinterpret_cast<const uint32_t*>(processPtr) !=
					static_cast<uint32_t>(g_ArtilleryProcessVtableAddr))
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

        bool __fastcall TurretTankProcessDoSubTaskHook(void* thisPtr, void* /*edx*/)
        {
            const bool result =
                g_BzrFn_TurretTankProcessDoSubTask
                    ? g_BzrFn_TurretTankProcessDoSubTask(thisPtr)
                    : false;
            RevealProcessOwnerPerceivedTeam(thisPtr, "turrettank_post_subtask");
            ApplyRetargetPeriodAfterDoSubTask(thisPtr);
            return result;
        }

		void InstallAiTuningHooksIfPossible()
        {
            InstallAttackTaskKiteHookIfPossible();
            InstallScrapPathScoreHookIfPossible();
            InstallScavengerRetargetHookIfPossible();

            if (g_CalcRangeCraftHookInstalled &&
                g_RetargetPeriodHooksInstalled &&
                g_AttackTaskDoStateHookInstalled &&
                g_ScrapPathScoreHookInstalled &&
                g_ScrapRetargetHookInstalled)
                return;

            if (g_CalcRangeCraftDetour.trampoline && g_BzrFn_CalcRangeCraft)
            {
                g_CalcRangeCraftHookInstalled = true;
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
                }
                else if (!ExpectedBytesMatchAt(calcRangeCraftEntryAddr,
                                          kExpectedCalcRangeCraftBytes,
                                          sizeof(kExpectedCalcRangeCraftBytes)))
                {
                    Log(L"[AIODF] CalcRange(Craft) entry bytes mismatch at 0x%08X; AI ODF range tuning disabled\n",
                        static_cast<uint32_t>(calcRangeCraftEntryAddr));
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
                }
                else
                {
                    g_BzrFn_CalcRangeCraft =
                        reinterpret_cast<FnCalcRangeCraft>(g_CalcRangeCraftDetour.trampoline);
                    g_CalcRangeCraftHookInstalled = (g_BzrFn_CalcRangeCraft != nullptr);
                    if (g_CalcRangeCraftHookInstalled)
                    {
                        Log(L"[AIODF] Installed CalcRange(Craft) hook entry=0x%08X trampoline=0x%08X\n",
                            static_cast<uint32_t>(calcRangeCraftEntryAddr),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_CalcRangeCraftDetour.trampoline)));
                    }
                }
            }

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

            RetargetVtableHookSpec hooks[] =
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

            bool allInstalled = true;
            for (RetargetVtableHookSpec& spec : hooks)
            {
                *spec.original = reinterpret_cast<FnProcessDoSubTask>(spec.originalAddress);
                const uintptr_t slotAddress =
                    spec.vtableAddress + kProcessDoSubTaskVtableSlot * sizeof(void*);

                if (!VtableTypeNameMatches(spec.vtableAddress, spec.rttiName))
                {
                    Log(L"[AIODF] %ls RTTI mismatch vtable=0x%08X; retarget tuning disabled there\n",
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
                    if (TryParseBoolValue(value, parsedLegacy) && parsedLegacy)
                    {
                        outConfig.legacyAiRole = true;
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
