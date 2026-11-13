// mission_hook_bridges.cpp
// BZR Open Shim - mission hook bridge setters: the SDK-facing per-mission
// overrides (AI ODF gameplay tuning, per-unit AI tuning, legacy tank AI,
// turret aim pitch), the mission-reset that restores them, and the
// mission-running query, split out of bzr_hooks.cpp.
#include "native_hud_runtime.h"
#include "hud_feedback.h"
#include "bzr_hooks.h"
#include "env_switch_table.h"
#include "bool_token.h"
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
#include "memory_access.h"
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
    using namespace Hooks;

    bool SetLegacyTankAiEnabledFromBridge(bool enabled)
    {
        RetryDeferredRuntimeHooks();
        g_LegacyTankAiEnabled = enabled ? 1 : 0;
        RefreshLegacyTankAiState();
        Log(L"[MISSIONHOOK] legacy tank AI override %hs (active=%hs)\n",
            enabled ? "enabled" : "disabled",
            BoolText(g_LegacyTankAiActive));
        return true;
    }

    bool SetLegacyTankAiModeFromBridge(int mode)
    {
        if (mode < 0 || mode > 2)
            return false;
        RetryDeferredRuntimeHooks();
        g_LegacyTankAiEnabled = mode;
        RefreshLegacyTankAiState();
        Log(L"[MISSIONHOOK] legacy tank AI override mode %d (active=%hs)\n",
            mode,
            BoolText(g_LegacyTankAiActive));
        return true;
    }

    bool SetAiFollowEngageEnabledFromBridge(bool enabled)
    {
        RetryDeferredRuntimeHooks();
        const bool inPlace = SetAiFollowEngageEnabled(enabled);
        Log(L"[MISSIONHOOK] AI follow-as-formation %hs (in place=%hs)\n",
            enabled ? "enabled" : "disabled", BoolText(inPlace));
        return inPlace;
    }

    bool SetAiDefendRefreshEnabledFromBridge(bool enabled)
    {
        RetryDeferredRuntimeHooks();
        const bool inPlace = SetAiDefendRefreshEnabled(enabled);
        Log(L"[MISSIONHOOK] AI defend refresh %hs (in place=%hs)\n",
            enabled ? "enabled" : "disabled", BoolText(inPlace));
        return inPlace;
    }

    bool SetAiHoldFromBridge(int handle, bool hold)
    {
        RetryDeferredRuntimeHooks();
        return SetAiHold(handle, hold);
    }

    bool SetRallyPointsAllowedInNetworkFromBridge(bool allowed)
    {
        return SetProducerRallyPointsNetworkAllowed(allowed);
    }

    bool SetBomberAiRangeEnabledFromBridge(bool enabled)
    {
        // Bomber range is now part of AI ODF gameplay tuning; the export
        // stays for old callers and does nothing.
        Log(L"[MISSIONHOOK] bomber AI range override %hs ignored: folded into AI ODF gameplay tuning\n",
            enabled ? "enabled" : "disabled");
        return true;
    }

    bool SetAiOdfGameplayTuningEnabledFromBridge(bool enabled)
    {
        RetryDeferredRuntimeHooks();
        g_AiOdfGameplayTuningEnabled = enabled;
        RefreshAiOdfGameplayTuningState();
        if (!enabled)
        {
            g_ScrapPathFailuresByObject.clear();
            g_ScrapRetargetStateByTask.clear();
        }
        Log(L"[MISSIONHOOK] AI ODF gameplay tuning %hs\n", enabled ? "enabled" : "disabled");
        return true;
    }

    bool SetAiUnitTuningFromBridge(void* objectPtr,
                                   float engageRange,
                                   float weaponRangeMin,
                                   float retargetPeriod,
                                   float kiteDesiredRange,
                                   float kiteEnterRange,
                                   float kiteExitRange,
                                   bool kitePreserveLos,
                                   float kiteStrafe,
                                   float kiteSwitchPeriod)
    {
        if (!objectPtr)
            return false;

        // The range/retarget detours are usually installed by mission setup, but a
        // per-unit call can arrive first; retry once if neither hook is live yet.
        if (!g_CalcRangeCraftHookInstalled ||
            !g_RetargetPeriodHooksInstalled ||
            !g_AttackTaskDoStateHookInstalled)
            RetryDeferredRuntimeHooks();

        AiUnitTuningOverride entry = {};
        if (std::isfinite(engageRange) && engageRange > 0.0f)
        {
            entry.hasEngageRange = true;
            entry.engageRange = engageRange;
        }
        if (std::isfinite(weaponRangeMin) && weaponRangeMin > 0.0f)
        {
            entry.hasWeaponRangeMin = true;
            entry.weaponRangeMin = weaponRangeMin;
        }
        if (std::isfinite(retargetPeriod) && retargetPeriod > 0.0f)
        {
            entry.hasRetargetPeriod = true;
            entry.retargetPeriod = retargetPeriod;
        }
        if (std::isfinite(kiteDesiredRange) && kiteDesiredRange > 0.0f &&
            std::isfinite(kiteEnterRange) && kiteEnterRange > 0.0f &&
            std::isfinite(kiteExitRange) && kiteExitRange > kiteEnterRange &&
            kiteDesiredRange > kiteEnterRange && kiteDesiredRange < kiteExitRange)
        {
            entry.hasKiteRanges = true;
            entry.kiteDesiredRange = kiteDesiredRange;
            entry.kiteEnterRange = kiteEnterRange;
            entry.kiteExitRange = kiteExitRange;
            entry.kitePreserveLos = kitePreserveLos;
            if (std::isfinite(kiteStrafe) && kiteStrafe > 0.0f)
                entry.kiteStrafe = (std::min)(kiteStrafe, 1.0f);
            if (std::isfinite(kiteSwitchPeriod) && kiteSwitchPeriod > 0.0f)
                entry.kiteSwitchPeriod = kiteSwitchPeriod;
        }

        const uintptr_t key = reinterpret_cast<uintptr_t>(objectPtr);
        if (!entry.hasEngageRange && !entry.hasWeaponRangeMin &&
            !entry.hasRetargetPeriod && !entry.hasKiteRanges)
        {
            g_AiUnitTuningOverridesByObject.erase(key);
            g_CombatKiteStateByObject.erase(key);
            return true;
        }

        g_AiUnitTuningOverridesByObject[key] = entry;
        if (EnvFlagEnabled("OPENSHIM_TRACE_AI_KITE") ||
            EnvFlagEnabled("OPENSHIM_TRACE_AI_UNIT_TUNING"))
        {
            Log(L"[AIUNIT] set craft=0x%08X engage=%.2f weaponMin=%.2f retarget=%.2f kite=%hs desired=%.2f enter=%.2f exit=%.2f strafe=%.2f\n",
                static_cast<uint32_t>(key),
                static_cast<double>(entry.engageRange),
                static_cast<double>(entry.weaponRangeMin),
                static_cast<double>(entry.retargetPeriod),
                entry.hasKiteRanges ? "on" : "off",
                static_cast<double>(entry.kiteDesiredRange),
                static_cast<double>(entry.kiteEnterRange),
                static_cast<double>(entry.kiteExitRange),
                static_cast<double>(entry.kiteStrafe));
        }
        if (!entry.hasKiteRanges)
            g_CombatKiteStateByObject.erase(key);
        return true;
    }

    bool ClearAiUnitTuningFromBridge(void* objectPtr)
    {
        if (!objectPtr)
            return false;
        const uintptr_t key = reinterpret_cast<uintptr_t>(objectPtr);
        g_AiUnitTuningOverridesByObject.erase(key);
        g_CombatKiteStateByObject.erase(key);
        return true;
    }

    bool ClearAllAiUnitTuningFromBridge()
    {
        if (!g_AiUnitTuningOverridesByObject.empty())
        {
            Log(L"[AIUNIT] cleared %u per-unit tuning overrides\n",
                static_cast<uint32_t>(g_AiUnitTuningOverridesByObject.size()));
        }
        g_AiUnitTuningOverridesByObject.clear();
        g_CombatKiteStateByObject.clear();
        return true;
    }

    bool SetTurretAimPitchEnabledFromBridge(bool enabled)
    {
        g_TurretAimPitchEnabled = enabled;
        RefreshTurretAimPitchState();
        Log(L"[MISSIONHOOK] turret aim pitch override %hs active=%.3f\n",
            enabled ? "enabled" : "disabled",
            static_cast<double>(g_TurretAimPitchMultiplier));
        return true;
    }

    bool ResetMissionHookOverridesFromBridge()
    {
        RetryDeferredRuntimeHooks();
        g_LegacyTankAiEnabled = g_LegacyTankAiBaselineEnabled;
        RefreshLegacyTankAiState();
        ResetAiNativeOrders();
        ResetTurretAttackOrders();
        ResetProducerRallyPoints();
        ResetAutoGroupNewUnits();
        ResetGroupStrip();
        // Content render-profile requests are mission/session scoped: the
        // authoritative lifecycle seam clears them so an EXU override from one
        // mission can never leak into the shell or unrelated content.
        RenderProfiles::ClearContentRenderProfileOverride("mission reset");
        // Renderer-effect intent is mission scoped for the same reason:
        // a mission that asked for SSAO must not leave it asked-for in the
        // shell or in whatever loads next. Clearing here rather than
        // relying on the companion means a script that crashes or forgets
        // to tear down still cannot leak a request.
        RenderEffects::Reset();
        NativeHud::Runtime::ResetMission();
        HudFeedback::ResetMission();
        g_HowitzerVolleyEnabled = kHowitzerVolleyEnabledDefault;
        g_WeaponMaskCarrierBiasEnabled = kWeaponMaskCarrierBiasEnabledDefault;
        g_AttackRevealEnabled = kAttackRevealEnabledDefault;
        g_AttackRevealTraceBudget = kAttackRevealTraceBudgetDefault;
        g_PilotCarrierNullLoggedObjects.clear();
        g_NeutralAttackOrderLogBudget = 16;
        g_AipResolveTraceBudget = 512;
        g_AipPrereqCensusEmitted = 0;
        g_AiExtraMakerPairs.clear();
        g_AiMultiProducerMakerLogBudget = 64;
        g_AiUnitTuningOverridesByObject.clear();
        g_CombatKiteStateByObject.clear();
        g_ScrapPathFailuresByObject.clear();
        g_ScrapRetargetStateByTask.clear();
        g_AiUnitTuningTraceBudget = 64;
        g_CombatKiteTraceBudget = 256;
        g_ScrapPathTraceBudget = 128;
        // Registered features revert to their resting state. Gameplay features
        // drop to their INI baseline + re-apply the MP gate; Display
        // preferences revert to the user's openshim.ini baseline, not a hardcoded
        // default, so global config still governs the next mission / Instant
        // Action once a script-set mission ends.
        RevertRegisteredFeaturesToBaseline();
        Log(L"[MISSIONHOOK] restored mission hook overrides to defaults\n");
        return true;
    }

    bool IsMissionSimulationActiveFromBridge()
    {
        int state = kBzrRunStateUnknown;
        return TryReadBzrRunState(state) && state == kBzrRunStateStarted;
    }
}
