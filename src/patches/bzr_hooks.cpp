#include "native_hud_runtime.h"
#include "geometry_contact_test.h"
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
#include "ogre_script_import_cache.h"
#include "resource_walk_stat_cache.h"
#include "ogre_enhanced_light_selection.h"
#include "render_effect_intent.h"
#include "render_profile_runtime.h"
#include "native_ui.h"
#include "../engine/native_ui_validation.h"
#include "ogre_animation_profiler.h"
#include "ogre_profiler_algorithms.h"
#include "weapon_convergence.h"
#include "weapon_presentation_hooks.h"
#include "weapon_presentation_native.h"
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

    void* g_BzrnetHostObj   = nullptr;
    void* g_BzrnetClientObj = nullptr;

    uint32_t g_BanFlag = 0;
    float g_TurretAimPitchMultiplier = 0.5f;
    float g_TurretAimPitchMultiplierEnhanced = 0.95f;

    void* g_BzrFn_VehicleFixPre = nullptr;
    void* g_BzrFn_VehicleFixOrig = nullptr;

    BzrString g_BzrnetLabel1 = {};
    BzrString g_BzrnetLabel2 = {};
    BzrString g_BzrnetLabel3 = {};
    BzrString g_BzrnetLabel4 = {};

    using FnAutoLoadShellGame = int(__cdecl*)();
    using FnLoadGameByPath = int(__cdecl*)(const char* path, char* outName, int outNameLen);
    using FnFinalizeQueuedLoad = void(__cdecl*)();
    using FnChunkEffectSimulate = void(__thiscall*)(void* self, float dt);

    void** g_BzrPtr_945478 = nullptr;
    void** g_BzrPtr_94548C = nullptr;
    void** g_BzrPtr_94555C = nullptr;
    void** g_BzrPtr_9456D0 = nullptr;
    void** g_BzrPtr_94557C = nullptr;
    void** g_BzrPtr_920168 = nullptr;
    uint8_t* g_BzrPtr_CurrentUser = nullptr;

    FnVehicleListSet g_BzrFn_VehicleListSet = nullptr;      // 0x0076B7A0
    FnVehicleListFinalize g_BzrFn_VehicleListFinalize = nullptr; // 0x0076BA00
    FnVehicleListLoad g_BzrFn_VehicleListLoad = nullptr;    // 0x00766900
    FnVehicleListStep g_BzrFn_VehicleListRefresh1 = nullptr; // 0x007A3F80
    FnVehicleListStep g_BzrFn_VehicleListRefresh2 = nullptr; // 0x007A4070

    FnUiButtonCtor g_BzrFn_ButtonCtor = nullptr; // 0x007C2480
    FnUiLabelCtor g_BzrFn_LabelCtor  = nullptr; // 0x007CC390
    FnUiOverlayCtor g_BzrFn_OverlayCtor = nullptr; // 0x007D1CC0
    FnUiTextEntryCtor g_BzrFn_TextEntryCtor = nullptr; // 0x007CF410
    FnUiSelectlistCtor g_BzrFn_SelectlistCtor = nullptr; // 0x007C9DE0
    FnUiSelectlistSetItem g_BzrFn_SelectlistSetItem = nullptr; // 0x007CABF0
    FnUiSetCb g_BzrFn_TextEntrySetEnterCb = nullptr; // 0x007CF940
    FnUiSetStr g_BzrFn_TextEntryAppendText = nullptr; // 0x007CF980
    FnUiTextEntryAppendChar g_BzrFn_TextEntryAppendChar = nullptr; // 0x007CFA70
    FnUiTextEntryClear g_BzrFn_TextEntryClear = nullptr; // 0x007CF9F0
    void (__thiscall* g_BzrFn_TextEntrySetInputLimit)(void*, int) = nullptr; // 0x00795BD0
    FnUiSetCb g_BzrFn_SelectlistSetOnSelect = nullptr; // 0x007CB3E0
    FnUiSetStr g_BzrFn_SetTextureOff = nullptr; // 0x007D2870
    FnUiSetStr g_BzrFn_SetTextureOver = nullptr; // 0x007C2F10
    FnUiSetStr g_BzrFn_SetTextureOn = nullptr; // 0x007C2E80
    FnUiSetStr g_BzrFn_SetButtonLabel = nullptr; // 0x007C2950
    FnUiSetFloat g_BzrFn_SetButtonTextScale = nullptr; // 0x007C30E0 (stock options buttons use 1.3)
    FnUiSetStr g_BzrFn_SetTooltip = nullptr; // 0x007CC660
    FnUiSetInt g_BzrFn_LabelState = nullptr; // 0x007CC5C0
    FnUiSetCb g_BzrFn_SetOnClick = nullptr; // 0x007C23E0
    FnUiSetCb g_BzrFn_SetOnHover = nullptr; // 0x007C23C0
    FnUiSetActive g_BzrFn_UiSetActive = nullptr; // 0x007D3310
    FnUiAddChild g_BzrFn_AddChild = nullptr; // 0x007D2110
    FnUiDialogAction g_BzrFn_UiDialogSetEnabled = nullptr; // 0x007C9170
    FnUiDialogAction g_BzrFn_UiDialogAdvance = nullptr; // 0x007C7930

    FnGetSelected g_BzrFn_GetSelected = nullptr; // 0x007CB1A0
    FnCommandHandler g_BzrFn_CommandHandler = nullptr; // 0x006247A0
    FnHelpLog g_BzrFn_HelpLog = nullptr; // 0x00821390
    FnHelpUi g_BzrFn_HelpUi = nullptr;   // 0x007A47B0
    FnBanLookup g_BzrFn_BanLookup = nullptr; // 0x005771B0
    FnIsHost g_BzrFn_IsHost = nullptr; // 0x00572A60
    static FnAutoLoadShellGame g_BzrFn_AutoLoadShellGame = nullptr; // 0x004FDAB0
    static FnLoadGameByPath g_BzrFn_LoadGameByPath = nullptr; // 0x004FDFE0 (_load_bzone_game)
    FnLoadScreenPrep g_BzrFn_LoadScreenPrep = nullptr; // 0x0078BB00
    static FnFinalizeQueuedLoad g_BzrFn_FinalizeQueuedLoad = nullptr; // 0x005D4980
    FnSetShellState g_BzrFn_SetShellState = nullptr; // 0x00434170
    FnBzrStringCtorFromCStr g_BzrFn_BzrStringCtorFromCStr = nullptr; // 0x00416EF0
    FnBzrStringDtor g_BzrFn_BzrStringDtor = nullptr; // 0x00416F30
    FnLoadScreenClearSelection g_BzrFn_LoadScreenClearSelection = nullptr; // 0x00482860
    FnChunkResolve g_BzrFn_ChunkResolve = nullptr; // 0x004E3620
    FnGetLocalPlayerNetId g_BzrFn_GetLocalPlayerNetId = nullptr;
    FnNetPlayerSetData g_BzrFn_NetPlayerSetData = nullptr;
    FnNetPlayerSetFlagBuffer g_BzrFn_NetPlayerSetFlagBuffer = nullptr;
    FnSetMyFlag g_BzrFn_SetMyFlag = nullptr;
    FnBuildItemInit g_BzrFn_InitBuildItem = nullptr; // 0x0049F5C0
    FnBuildItemCleanup g_BzrFn_CleanupBuildItem = nullptr; // 0x0049F880
    FnEngineFlameAddFlame g_BzrFn_EngineFlameAddFlame = nullptr;
    FnEngineFlameControl g_BzrFn_EngineFlameControl = nullptr;
    FnEngineFlameSubmit g_BzrFn_EngineFlameSubmit = nullptr;
    FnEngineFlameResolveTexture g_BzrFn_EngineFlameResolveTexture = nullptr;
    FnHudSpriteLookup g_BzrFn_HudSpriteLookup = nullptr;
    FnGetTeamNum g_BzrFn_GetTeamNum = nullptr;
    static FnChunkEffectSimulate g_BzrFn_ChunkEffectSimulate = nullptr;
    FnLegacyWorldUpdateRenderQueue g_BzrFn_LegacyWorldUpdateRenderQueue = nullptr;
    // GameObject::GetHandle, resolved by ResolveBzrHooks from scripts/patches.json
    // ("GameObject::GetHandle"); 0 until then, and every caller stands down on 0.
    uintptr_t g_GameObjectGetHandleAddr = 0;

    // Resolved by ResolveBzrHooks from scripts/patches.json
    // ("GameObject::FromObj76"); null until then, and every caller checks.
    FnResolveObj76GameObject g_BzrFn_ResolveObj76GameObject = nullptr;
    FnKeyConfigSetKey g_BzrFn_KeyConfigSetKey = nullptr;
    static FnWriteInputMapKey g_BzrFn_WriteInputMapKey = nullptr;
    FnMapKeyNameFromCode g_BzrFn_MapKeyNameFromCode = nullptr;
    FnReloadGameKeyMap g_BzrFn_ReloadGameKeyMap = nullptr;
    FnAIBuildConstructionEnd g_BzrFn_AIBuildConstructionEnd = nullptr;
    FnAIBuildReservedAreaRemove g_BzrFn_AIBuildReservedAreaRemove = nullptr;
    FnAISpentCreditRefund g_BzrFn_AISpentCreditRefund = nullptr;
    FnUnitsSOrderStop g_BzrFn_UnitsSOrderStop = nullptr;
    FnAIBuildUnassignedCCAdd g_BzrFn_AIBuildUnassignedCCAdd = nullptr;
    BuildItem* g_BzrBuildMenuRoot = nullptr;
    bool g_IsSteamExe = false;

    // Formerly an anonymous namespace. A named one plus the using-directive
    // after its closing brace keeps every lookup identical, and lets the
    // translation units split out of this file (declared in
    // bzr_hooks_internal.h) share what they need. Anything meant to stay
    // file-local is `static`.
    namespace Hooks
    {

		constexpr long kQuakeReplayFadeSecondsMin = 1;
		constexpr long kQuakeReplayFadeSecondsMax = 60;

        constexpr ULONGLONG kSteamChunkCreateHookSettleDelayMs = 15000;

        static constexpr uintptr_t kChunkEffectVtableSimulateSlotAddr = 0x0087708C;
        static constexpr DWORD kVehicleSkinningTraceIntervalMsDefault = 5000;
        static constexpr DWORD kVehicleSkinningTraceIntervalMsMin = 100;
        static constexpr DWORD kVehicleSkinningTraceIntervalMsMax = 60000;
        static constexpr long kVehicleSkinningTraceBudgetDefault = 64;
        // Resolved by ResolveBzrHooks from scripts/patches.json
        // ("PlayGlobalSound"); null until then, and the caller checks.
        FnPlayGlobalSound g_BzrFn_PlayGlobalSound = nullptr;

        static uint32_t ClampChunkProxyCapacity(long value)
        {
            if (value < 8)
                return 8;
            if (value > 512)
                return 512;
            return static_cast<uint32_t>(value);
        }

        static float ClampChunkProxySize(float value)
        {
            if (value < 0.25f)
                return 0.25f;
            if (value > 20.0f)
                return 20.0f;
            return value;
        }

        static uint32_t ClampChunkTraceEntryLimit(long value)
        {
            if (value < 1)
                return 1;
            if (value > 32)
                return 32;
            return static_cast<uint32_t>(value);
        }

        static uint32_t ClampSatelliteVisibilityObjectLimit(long value)
        {
            if (value < 8)
                return 8;
            if (value > 256)
                return 256;
            return static_cast<uint32_t>(value);
        }

        static DWORD ClampSatelliteVisibilityLogInterval(long value)
        {
            if (value < 100)
                return 100;
            if (value > 10000)
                return 10000;
            return static_cast<DWORD>(value);
        }

        static constexpr long kDamageRevealTraceBudgetDefault = 400;

        static constexpr long kPlayerKillTraceBudgetDefault = 256;
        static constexpr long kPlayerKillTraceBudgetMax = 4096;

        // The event layer's per-frame driver. Order matters: session
        // transitions and derived kills are published first so they land in the
        // same drain as everything the engine published during this frame.
        static void TickOpenShimEventLayer()
        {
            TickCareerSessionState();
            TickCareerPendingVictims();
            DispatchPendingEvents();
        }

    }
    using namespace Hooks;

    // Puts every piece of per-process hook state back to its resting value
    // before ResolveBzrHooks binds addresses and reads configuration.
    // Also re-derives the pointers that come from already-installed detour
    // trampolines. Runs after g_IsSteamExe is set.
    void ResetBzrHookRuntimeState()
    {
        NativeHud::Runtime::SetAdapterCapabilities(0);
        ResetWeaponPresentationState();
        GeometryContactTest::Clear();
        g_BzrFn_EngineFlameAddFlame = nullptr;
        g_BzrFn_EngineFlameControl = nullptr;
        g_BzrFn_EngineFlameSubmit = nullptr;
        g_BzrFn_EngineFlameResolveTexture = nullptr;
        g_BzrFn_GetTeamNum = nullptr;
        g_BzrFn_ChunkEffectSimulate = nullptr;
        g_BzrFn_DynamicGeometryPrepare = g_DynamicGeometryPrepareDetour.trampoline
            ? reinterpret_cast<FnDynamicGeometryPrepare>(
                g_DynamicGeometryPrepareDetour.trampoline)
            : nullptr;
        g_BzrFn_LegacyWorldUpdateRenderQueue = nullptr;
        g_BzrFn_GetPlayerHandle = nullptr;
        g_BzrFn_GameObjectGetObjByHandle = nullptr;
        g_BzrFn_PersonSimulate = nullptr;
        g_BzrFn_ShieldTowerSimulateOriginal = nullptr;
        g_BzrFn_MagnetMineSimulateOriginal = nullptr;
        g_BzrFn_ProximityMineSimulateOriginal = nullptr;
        g_BzrFn_MineSimulate = nullptr;
        g_BzrFn_BuildingSimulate = nullptr;
        g_BzrFn_SprayBuildingSimulateOriginal = nullptr;
        g_BzrFn_ShieldTowerPowerUpdate = nullptr;
        g_BzrFn_GameObjectFriendP = nullptr;
        g_BzrFn_GameObjectEnemyP = nullptr;
        g_BzrFn_MatrixInverse = nullptr;
        g_BzrFn_VectorTransform = nullptr;
        g_BzrFn_CollisionRangeSearch = nullptr;
        g_BzrFn_RangeResultsGetNext = nullptr;
        g_BzrFn_OverlayCtor = nullptr;
        g_BzrFn_UiSetActive = nullptr;
        ResetOptionsUiResolvedState();
        g_BzrFn_KeyConfigSetKey = nullptr;
        g_BzrFn_WriteInputMapKey = nullptr;
        g_BzrFn_MapKeyNameFromCode = nullptr;
        g_BzrFn_ReloadGameKeyMap = nullptr;
        g_BzrFn_RecordDeath = g_RecordDeathDetour.trampoline
            ? reinterpret_cast<FnRecordDeath>(g_RecordDeathDetour.trampoline)
            : nullptr;
        g_BzrFn_ChunkEffectCreateChunk = g_ChunkEffectCreateChunkDetour.trampoline
            ? reinterpret_cast<FnChunkEffectCreateChunk>(g_ChunkEffectCreateChunkDetour.trampoline)
            : nullptr;
        g_BzrFn_ChunkEffectCreateChunklet = g_ChunkEffectCreateChunkletDetour.trampoline
            ? reinterpret_cast<FnChunkEffectCreateChunklet>(g_ChunkEffectCreateChunkletDetour.trampoline)
            : nullptr;
        g_BzrFn_ChunkEffectPartialFragment = g_ChunkEffectPartialFragmentDetour.trampoline
            ? reinterpret_cast<FnChunkEffectFragmentObject>(g_ChunkEffectPartialFragmentDetour.trampoline)
            : nullptr;
        g_BzrFn_ChunkEffectFullFragment = g_ChunkEffectFullFragmentDetour.trampoline
            ? reinterpret_cast<FnChunkEffectFragmentObject>(g_ChunkEffectFullFragmentDetour.trampoline)
            : nullptr;
        g_JumpSnipeProbeInstalled = false;
        g_EngineFlamePrimaryManager = nullptr;
        g_EngineFlameSecondaryManager = nullptr;
        g_EngineFlameVtableHooksInstalled = false;
        g_BzrFn_FlagDisplaySubmitOriginal = nullptr;
        g_MultiplayerFlagRenderHookInstalled = false;
        g_MultiplayerFlagRenderHookFailureLogged = false;
        g_MultiplayerFlagRendererLoggedReady = false;
        g_MultiplayerFlagRenderSets.clear();
        g_EngineFlameVariantsInitialized = false;
        g_EngineFlameVariantsInitAttempted = false;
        g_EngineFlamePrimaryBlueTexture = 0;
        g_EngineFlamePrimaryRedTexture = 0;
        g_EngineFlamePrimaryGreenTexture = 0;
        g_EngineFlamePrimaryOrangeTexture = 0;
        g_EngineFlamePrimaryBlackDogTexture = 0;
        g_LoggedEngineFlameTargetFailure = false;
        g_LoggedEngineFlameVtableHook = false;
        g_BzrFn_InitBuildItem = nullptr;
        g_BzrFn_CleanupBuildItem = nullptr;
        g_BzrBuildMenuRoot = nullptr;
        g_BzrFn_GetLocalPlayerNetId = nullptr;
        g_BzrFn_NetPlayerSetData = nullptr;
        g_CareerStatsMpHookInstalled = (g_RecordDeathDetour.trampoline != nullptr);
        g_CareerStatsMpHookInstallAttempted = g_CareerStatsMpHookInstalled;
        g_CareerStatsMpHookMismatchLogged = false;
        g_CareerStatsMpHookFirstAttemptTick = 0;
        g_CareerStatsMpHookLastAttemptTick = 0;
        g_JumpSnipeProbeLogState = {};
        g_ProducerBuildMenuConfig = {};
        ResetProducerBuildMenuRuntime();
        g_AiTuningCache = {};
        g_ShieldTowerTeamFilterCache = {};
        g_MagnetMineTeamFilterCache = {};
        g_ProximityMineTeamFilterCache = {};
        g_CalcRangeCraftHookInstalled = false;
        g_ScrapPathScoreHookInstalled = false;
        g_BzrFn_RecycleTaskDoGotoScrap =
            g_RecycleTaskDoGotoScrapDetour.trampoline
                ? reinterpret_cast<FnRecycleTaskDoGotoScrap>(
                    g_RecycleTaskDoGotoScrapDetour.trampoline)
                : nullptr;
        g_ScrapRetargetHookInstalled =
            (g_BzrFn_RecycleTaskDoGotoScrap != nullptr);
        g_BzrFn_CalcRangeCraft = nullptr;
        g_BzrFn_AttackTaskDoState = g_AttackTaskDoStateDetour.trampoline
            ? reinterpret_cast<FnAttackTaskDoState>(g_AttackTaskDoStateDetour.trampoline)
            : nullptr;
        g_BzrFn_TerrainGetIntersection = g_BzrFn_AttackTaskDoState
            ? reinterpret_cast<FnTerrainGetIntersection>(kGogTerrainGetIntersectionAddr)
            : nullptr;
        g_AttackTaskDoStateHookInstalled =
            g_BzrFn_AttackTaskDoState && g_BzrFn_TerrainGetIntersection;
        g_RetargetPeriodHooksInstalled = false;
        g_ConstructorRemoteBuildFixMismatchLogged = false;
        g_BzrFn_OffensiveProcessDoSubTask = nullptr;
        g_BzrFn_GunTowerProcessDoSubTask = nullptr;
        g_BzrFn_TurretTankProcessDoSubTask = nullptr;
        g_BzrFn_GetGameTime = nullptr;
        g_BzrFn_FindPlanForObject = nullptr;
        g_BzrFn_AiPathGetLength = nullptr;
        g_BzrFn_AiPathDelete = nullptr;
        g_BzrFn_AIUnitRemove = nullptr;
        g_BzrFn_AIBuildConstructionEnd = nullptr;
        g_BzrFn_AIBuildReservedAreaRemove = nullptr;
        g_BzrFn_AISpentCreditRefund = nullptr;
        g_BzrFn_UnitsSOrderStop = nullptr;
        g_BzrFn_AIBuildUnassignedCCAdd = nullptr;
        g_ChunkEffectCreateHooksInstalled =
            g_ChunkEffectCreateChunkDetour.trampoline &&
            g_BzrFn_ChunkEffectCreateChunk &&
            g_ChunkEffectCreateChunkletDetour.trampoline &&
            g_BzrFn_ChunkEffectCreateChunklet;
        g_ChunkEffectCreateHooksLogged = false;
        g_AllowUnsafeSteamChunkCreateHooks =
            EnvFlagEnabled("OPENSHIM_UNSAFE_CHUNK_CREATE_HOOKS") ||
            EnvFlagEnabled("BZR_UNSAFE_CHUNK_CREATE_HOOKS");
        g_ChunkEffectCreateHooksWaitLogged = false;
        g_ChunkEffectCreateHooksMismatchLogged = false;
        g_ChunkEffectCreateHooksReadyTick =
            GetTickCount64() + (g_IsSteamExe ? kSteamChunkCreateHookSettleDelayMs : 0);
        g_ConstructorRemoteBuildFixInstalled = false;
        g_ShieldTowerSimulateHookInstalled = false;
        g_MagnetMineSimulateHookInstalled = false;
        g_ProximityMineSimulateHookInstalled = false;
        g_BzrFn_ScriptCanBuildOriginal = g_ScriptCanBuildDetour.trampoline
            ? reinterpret_cast<FnScriptProducerPredicate>(g_ScriptCanBuildDetour.trampoline)
            : nullptr;
        g_BzrFn_ScriptIsBusyOriginal = g_ScriptIsBusyDetour.trampoline
            ? reinterpret_cast<FnScriptProducerPredicate>(g_ScriptIsBusyDetour.trampoline)
            : nullptr;
        g_ProducerScriptPredicateHooksInstalled =
            g_BzrFn_ScriptCanBuildOriginal && g_BzrFn_ScriptIsBusyOriginal;
		g_BriefingScrollFixInstalled = false;
		g_MultiRenderCountClampLogBudget = 8;
		g_MagnetZeroRangeLogBudget = 8;
		g_QuakeReplayFadeInstalled = false;
		g_QuakeReplayArmed = 0;
		g_BzrFn_EarthQuakeSimulateOriginal = g_EarthQuakeSimulateDetour.trampoline
			? reinterpret_cast<FnEarthQuakeSimulate>(g_EarthQuakeSimulateDetour.trampoline)
			: nullptr;
		g_TargetCamSatelliteFixInstalled = false;
		g_TargetCamSatelliteLogBudget = 8;
		g_CinematicSatelliteZoomFixInstalled = false;
		g_CinematicSatelliteZoomLogBudget = 8;
		g_SprayBuildingSimulateHookInstalled = false;
		g_BzrFn_SprayEmitterBuildOriginal = nullptr;
		g_TugCargoPostLoadFixInstalled = false;
		g_TugCargoPostLoadLogBudget = 16;
		g_ConstructorRecycleStaleTargetFixInstalled = false;
		g_ConstructorRecycleStaleTargetMismatchLogged = false;
		g_ConstructorRecycleStaleTargetLogBudget = 16;
		g_ApcAlliedTargetDeployFixInstalled = false;
        g_AttackRevealTraceBudget = kAttackRevealTraceBudgetDefault;
        g_PilotCarrierNullLoggedObjects.clear();
        g_NeutralAttackOrderLogBudget = 16;
        g_AipResolveTraceBudget = 512;
        g_AipPrereqCensusEmitted = 0;
        g_AiExtraMakerPairs.clear();
        g_AiMultiProducerMakerLogBudget = 64;
        g_LastKnownQueuedMissionName[0] = '\0';
        g_HudSpriteRectTableBase = nullptr;
        g_HudSpriteRectTableDiscoveryAttempted = false;
        g_HudSpriteRectTableDiscoveryLastTick = 0;
        g_HudSpriteOriginalEntries.clear();
        g_HudSpriteHiddenEntries.clear();
        g_HudSpriteOriginalEntriesByAddress.clear();
        g_HudSpriteHiddenAddresses.clear();
        g_HudSpriteCachedPanelAddresses.clear();
        g_HudSpriteFallbackDiscoveryAttempted = false;
        g_HudSpriteFallbackDiscoveryLastTick = 0;
        g_HudSpriteRectTableDiscoveryBackoffMs = 0;
        g_HudSpriteFallbackDiscoveryBackoffMs = 0;
        g_BomberAiRangeEnabled = kBomberAiRangeEnabledDefault;
        g_HowitzerVolleyEnabled = kHowitzerVolleyEnabledDefault;
        g_HowitzerUndeployedRetaliationFixEnabled =
            !(EnvFlagEnabled("OPENSHIM_DISABLE_HOWITZER_DEPLOY_FIX") ||
              EnvFlagEnabled("BZR_DISABLE_HOWITZER_DEPLOY_FIX"));
        RefreshHowitzerUndeployedRetaliationFixState();
        g_OwnedObjectRevealFixEnabled = kOwnedObjectRevealFixEnabledDefault;
        RefreshOwnedObjectRevealFixState();
        g_OwnedObjectRevealTraceBudget = kOwnedObjectRevealTraceBudgetDefault;
        g_WeaponMaskCarrierBiasEnabled = kWeaponMaskCarrierBiasEnabledDefault;
        g_TurretAimPitchEnabled = kTurretAimPitchEnabledDefault;
        g_AttackRevealEnabled = kAttackRevealEnabledDefault;
        ClearCareerPendingVictims();
        ResetInProcessEventQueue();
        // Registered features revert to their resting state (jump-snipe enable
        // -> default + MP-gated re-apply; Display prefs -> openshim.ini baseline).
        RevertRegisteredFeaturesToBaseline();
        g_ConstructorRemoteBuildFixEnabled = kConstructorRemoteBuildFixEnabledDefault;
        RefreshConstructorRemoteBuildFixState();
        g_SplinterUndeadFixEnabled = kSplinterUndeadFixEnabledDefault;
        RefreshSplinterUndeadFixState();
        g_SplinterUndeadTraceBudget = kSplinterUndeadTraceBudgetDefault;
        InitializeMpauthConfig();
        g_MpauthHooksInstalled = false;
        g_MpauthInstallRetryBudget = 8;
        g_MpauthInOrdnanceReceive = false;
        g_MpauthSplHitCounts.clear();
        // Recent DW removed ids are cleared per map; keep tick map bounded
        g_MpauthRecentDwRemovedIds.clear();
        g_MpauthDwRemoveTick.clear();
        g_MpauthDwDeletedRecord.clear();
        // Bounded cleanup for hit counts: clear on map reset to avoid (source,ordid) reuse confusion over long sessions
        g_MpauthSplHitCounts.clear();
        // Keep budgets as configured by InitializeMpauthConfig
        g_TurretAimPitchMultiplier = 0.5f;
        g_TurretAimPitchMultiplierEnhanced = 0.95f;
        g_RetargetPeriodStateByProcess.clear();
        g_ScrapPathFailuresByObject.clear();
        g_ScrapRetargetStateByTask.clear();
        g_AiUnitTuningOverridesByObject.clear();
        g_CombatKiteStateByObject.clear();
        g_AiUnitTuningTraceBudget = 64;
        g_CombatKiteTraceBudget = 256;
        g_ScrapPathTraceBudget = 128;
        g_VehicleSkinningTraceEnabled = false;
        g_VehicleSkinningTraceIntervalMs = kVehicleSkinningTraceIntervalMsDefault;
        g_VehicleSkinningTraceLastTick = 0;
        g_VehicleSkinningTraceBudget = kVehicleSkinningTraceBudgetDefault;
        g_VehicleSkinningTraceFingerprints.clear();
    }

    // The per-feature state lines ResolveBzrHooks logs once configuration
    // has been read and the init-time hooks installed.
    void LogBzrHookStatus(bool rawInputActive, const char* rawInputSource)
    {
        LogChunkDiagnostic("chunk", L"[CHUNK] Force-first-geo fallback: %hs\n",
            g_EnableChunkRenderFallback ? "enabled" : "disabled");
        LogChunkDiagnostic("chunk", L"[CHUNK] Trace logging: %hs%hs%hs budget=%ld entryLimit=%u\n",
            g_TraceChunkRender ? "enabled" : "disabled",
            g_TraceChunkRenderVerbose ? " verbose" : "",
            g_ChunkEventLogging ? " events" : " events=off (set OPENSHIM_CHUNK_TRACE=1)",
            static_cast<long>(g_ChunkRenderLogBudget),
            g_ChunkTraceEntryLimit);
        LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] Placeholder proxy debug: %hs cap=%u size=%.2f\n",
            g_EnableChunkProxyDebug ? "enabled" : "disabled",
            g_ChunkProxyCapacity,
            g_ChunkProxyDebugSize);
        LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Chunk mesh proxy: %hs genericBatch=%hs stockRoot=%hs modRelative=%hs|%hs\n",
            g_EnableChunkMeshProxy ? "enabled" : "disabled",
            g_EnableGenericChunkBatch ? "enabled" : "disabled",
            GetChunkPayloadStockResourceDirectory().string().c_str(),
            kChunkPayloadModRelativeDirName,
            kChunkPayloadModRelativeDirNameAlt);
        // Terrain HD: explicit AssetFeature::TerrainHd now exists for UI/diagnostics.
        // LoadTerrainHdManifest() remains the complete filesystem gate (soft-fails to stock atlas),
        // so no live behavior change is required; this log proves the centralized probe agrees.
        {
            const auto caps = Assets::GetAssetCapabilities();
            Log(L"[TERRAIN] HD terrain capability terrainHd=%d scanMs=%llu problem=%hs\n",
                caps.terrainHd ? 1 : 0,
                (unsigned long long)caps.lastScanDurationMs,
                caps.problem.c_str());
        }
        Log(L"[SKINNING] Vehicle diagnostics: %hs interval=%lums detailBudget=%ld optIn=OPENSHIM_TRACE_VEHICLE_SKINNING\n",
            g_VehicleSkinningTraceEnabled ? "enabled" : "disabled",
            static_cast<unsigned long>(g_VehicleSkinningTraceIntervalMs),
            static_cast<long>(g_VehicleSkinningTraceBudget));
        LogChunkDiagnostic("chunkeffect", L"[CHUNKEFFECT] Runtime manager trace: %hs vtableSlot=0x%08X orig=0x%08X\n",
            g_TraceChunkEffectRuntime ? "enabled" : "disabled",
            static_cast<uint32_t>(kChunkEffectVtableSimulateSlotAddr),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_ChunkEffectSimulate)));
        LogChunkDiagnostic("chunkspawn", L"[CHUNKSPAWN] Create-path hooks: %hs create=0x%08X chunklet=0x%08X\n",
            g_ChunkEffectCreateHooksInstalled ? "enabled" : "disabled",
            static_cast<uint32_t>(kGogChunkEffectCreateChunkAddr),
            static_cast<uint32_t>(kGogChunkEffectCreateChunkletAddr));
        if (g_IsSteamExe && !g_AllowUnsafeSteamChunkCreateHooks)
        {
            LogChunkDiagnostic("chunkspawn", L"[CHUNKSPAWN] Steam safety gate active; creator hooks will install after settled-byte verification and delay\n");
        }
        Log(L"[SATVIS] Satellite visibility trace: %hs budget=%ld interval=%lums objectLimit=%u viewRecord=0x%08X userObject=0x%08X arena=0x%08X\n",
            g_TraceSatelliteVisibility ? "enabled" : "disabled",
            g_SatelliteVisibilityLogBudget,
            static_cast<unsigned long>(g_SatelliteVisibilityLogIntervalMs),
            g_SatelliteVisibilityObjectLimit,
            static_cast<uint32_t>(GetMainModuleBase() + kViewRecordRva),
            static_cast<uint32_t>(EngineGlobals::UserObjectSlot()),
            static_cast<uint32_t>(EngineGlobals::GameObjectArena()));
        // Record the layout the sample lines were produced with, so a captured
        // log stays interpretable if these offsets are ever revised again.
        Log(L"[SATVIS]   offsets illum=+0x%03X isVisible=+0x%03X seen=+0x%03X team=+0x%03X perceivedTeam=+0x%03X objective=+0x%03X currentView=%ld expects=%ld\n",
            static_cast<unsigned>(kGameObjectIlluminationOffset),
            static_cast<unsigned>(kGameObjectIsVisibleOffset),
            static_cast<unsigned>(kGameObjectSeenOffset),
            static_cast<unsigned>(kGameObjectActualTeamOffset),
            static_cast<unsigned>(kGameObjectPerceivedTeamOffset),
            static_cast<unsigned>(kGameObjectIsObjectiveOffset),
            IsSatelliteOverviewActive() ? kCameraTypeOverView : -1L,
            kCameraTypeOverView);
        Log(L"[MAGNET] Zero/non-finite range guard: %hs hook=%hs\n",
            g_MagnetZeroRangeGuardEnabled ? "enabled" : "disabled",
            g_MagnetMineSimulateHookInstalled ? "installed" : "pending");
        Log(L"[RAWINPUT] Raw mouse input: %hs source=%hs signatures=%hs guard=%hs trace=%hs\n"
            L"[RAWINPUT]   flag=0x%08X process=0x%08X (stock command-line tokens: rawinput/norawinput)\n",
            rawInputActive ? "enabled" : "disabled",
            rawInputSource,
            g_RawMouseInputSignaturesMatch ? "verified" : "mismatch",
            g_RawMouseInputProcessHookInstalled ? "installed" : "absent",
            ShouldTraceRawMouseInput() ? "enabled" : "disabled",
            static_cast<uint32_t>(kRawMouseInputEnabledAddr),
            static_cast<uint32_t>(kRawMouseInputProcessAddr));
        Log(L"[PRODSCRIPT] PROD CanBuild/IsBusy fix: %hs\n",
            g_ProducerScriptPredicateHooksInstalled ? "installed" : "pending");
		Log(L"[ARTYDEPLOY] Undeployed howitzer sniper-retaliation fix: %hs offensiveSubTaskHook=%hs\n",
			g_HowitzerUndeployedRetaliationFixEnabled ? "enabled" : "disabled",
			g_RetargetPeriodHooksInstalled ? "installed" : "pending");
        Log(L"[BRIEFSCROLL] Mission briefing/archive scroll fix: %hs hook=%hs\n",
            g_BriefingScrollFixEnabled ? "enabled" : "disabled",
            g_BriefingScrollFixInstalled ? "installed" : "pending");
        Log(L"[RENDERCOUNT] draw_multi renderCount clamp: %hs hook=%hs max=%d\n",
            g_MultiRenderCountClampEnabled ? "enabled" : "disabled",
            g_MultiRenderCountClampInstalled ? "installed" : "pending",
            kMultiRenderCountMax);
        Log(L"[BMPFIX] Undecodable thumbnail guard: %hs hook=%hs optOut=OPENSHIM_DISABLE_BMP_GUARD\n",
            g_ThumbnailBmpGuardEnabled ? "enabled" : "disabled",
            g_ThumbnailBmpGuardInstalled ? "installed" : "pending");
        Log(L"[QUAKEFADE] Post-load quake replay fade: %hs hook=%hs fadeSeconds=%ld\n",
            g_QuakeReplayFadeEnabled ? "enabled" : "disabled",
            g_QuakeReplayFadeInstalled ? "installed" : "pending",
            g_QuakeReplayFadeSeconds);
        Log(L"[TARGETCAM] Satellite/F9 stale target camera fix: %hs hook=%hs\n",
            g_TargetCamSatelliteFixEnabled ? "enabled" : "disabled",
            g_TargetCamSatelliteFixInstalled ? "installed" : "pending");
        Log(L"[CINECAM] Cinematic-from-satellite zoom fix: %hs hook=%hs\n",
            g_CinematicSatelliteZoomFixEnabled ? "enabled" : "disabled",
            g_CinematicSatelliteZoomFixInstalled ? "installed" : "pending");
        Log(L"[TURRET] Aim pitch multiplier: %.3f%s\n",
            static_cast<double>(g_TurretAimPitchMultiplier),
            g_TurretAimPitchMultiplier >= 0.999f ? " (full range)" : "");
        Log(L"[AICONSTRUCT] Constructor death cleanup fix: %hs entry=0x%08X trace=%hs budget=%ld\n",
            g_ConstructorRemoteBuildFixEnabled ? "enabled" : "disabled",
            static_cast<uint32_t>(kGogAIUnitRemoveEntryAddr),
            ShouldTraceConstructorRemoteBuildFix() ? "enabled" : "disabled",
            g_ConstructorRemoteBuildTraceBudget);
        Log(L"[AGGRO] Attack reveal fix: %hs trace=%hs budget=%ld\n",
            g_AttackRevealEnabled ? "enabled" : "disabled",
            ShouldTraceAttackReveal() ? "enabled" : "disabled",
            g_AttackRevealTraceBudget);
        Log(L"[OWNREVEAL] owned-object reveal fix: configured=%hs active=%hs trace=%hs budget=%ld\n",
            BoolText(g_OwnedObjectRevealFixEnabled),
            BoolText(g_OwnedObjectRevealFixActive),
            BoolText(ShouldTraceOwnedObjectReveal()),
            g_OwnedObjectRevealTraceBudget);
    }

    // The fixed engine addresses ResolveBzrHooks binds. The addresses and the
    // bytes that must be at them live in the "engine_addresses" array of
    // scripts/patches.json; this table only maps each row name to the
    // pointer it fills. A code row whose guard bytes do not match, or a name
    // with no row, leaves its pointer null, and every feature built on it
    // stands down (fail closed). Every slot is a pointer-sized global, so
    // each row writes through void**.
    struct EngineAddressRow
    {
        const char* name;
        void** slot;
    };

    void BindEngineAddresses()
    {
        static const EngineAddressRow kRows[] = {
            {"VehicleListSelection", reinterpret_cast<void**>(&g_BzrPtr_945478)},
            {"VehicleListManager", reinterpret_cast<void**>(&g_BzrPtr_94548C)},
            {"MapListObject", reinterpret_cast<void**>(&g_BzrPtr_94555C)},
            {"LobbyHostPlayerList", reinterpret_cast<void**>(&g_BzrPtr_9456D0)},
            {"LobbyClientPlayerList", reinterpret_cast<void**>(&g_BzrPtr_94557C)},
            {"HelpObject", reinterpret_cast<void**>(&g_BzrPtr_920168)},
            {"CurrentUser", reinterpret_cast<void**>(&g_BzrPtr_CurrentUser)},
            {"VehicleListSet", reinterpret_cast<void**>(&g_BzrFn_VehicleListSet)},
            {"VehicleListFinalize", reinterpret_cast<void**>(&g_BzrFn_VehicleListFinalize)},
            {"VehicleListLoad", reinterpret_cast<void**>(&g_BzrFn_VehicleListLoad)},
            {"VehicleListRefresh1", reinterpret_cast<void**>(&g_BzrFn_VehicleListRefresh1)},
            {"VehicleListRefresh2", reinterpret_cast<void**>(&g_BzrFn_VehicleListRefresh2)},
            {"ButtonCtor", reinterpret_cast<void**>(&g_BzrFn_ButtonCtor)},
            {"LabelCtor", reinterpret_cast<void**>(&g_BzrFn_LabelCtor)},
            {"OverlayCtor", reinterpret_cast<void**>(&g_BzrFn_OverlayCtor)},
            {"TextEntryCtor", reinterpret_cast<void**>(&g_BzrFn_TextEntryCtor)},
            {"SelectlistCtor", reinterpret_cast<void**>(&g_BzrFn_SelectlistCtor)},
            {"SelectlistSetItem", reinterpret_cast<void**>(&g_BzrFn_SelectlistSetItem)},
            {"TextEntrySetEnterCb", reinterpret_cast<void**>(&g_BzrFn_TextEntrySetEnterCb)},
            {"TextEntryAppendText", reinterpret_cast<void**>(&g_BzrFn_TextEntryAppendText)},
            {"TextEntryAppendChar", reinterpret_cast<void**>(&g_BzrFn_TextEntryAppendChar)},
            {"TextEntryClear", reinterpret_cast<void**>(&g_BzrFn_TextEntryClear)},
            {"TextEntrySetInputLimit", reinterpret_cast<void**>(&g_BzrFn_TextEntrySetInputLimit)},
            {"SelectlistSetOnSelect", reinterpret_cast<void**>(&g_BzrFn_SelectlistSetOnSelect)},
            {"SetTextureOff", reinterpret_cast<void**>(&g_BzrFn_SetTextureOff)},
            {"SetTextureOver", reinterpret_cast<void**>(&g_BzrFn_SetTextureOver)},
            {"SetTextureOn", reinterpret_cast<void**>(&g_BzrFn_SetTextureOn)},
            {"SetButtonLabel", reinterpret_cast<void**>(&g_BzrFn_SetButtonLabel)},
            {"SetButtonTextScale", reinterpret_cast<void**>(&g_BzrFn_SetButtonTextScale)},
            {"SetTooltip", reinterpret_cast<void**>(&g_BzrFn_SetTooltip)},
            {"LabelState", reinterpret_cast<void**>(&g_BzrFn_LabelState)},
            {"SetOnClick", reinterpret_cast<void**>(&g_BzrFn_SetOnClick)},
            {"SetOnHover", reinterpret_cast<void**>(&g_BzrFn_SetOnHover)},
            {"UiSetActive", reinterpret_cast<void**>(&g_BzrFn_UiSetActive)},
            {"AddChild", reinterpret_cast<void**>(&g_BzrFn_AddChild)},
            {"UiDialogSetEnabled", reinterpret_cast<void**>(&g_BzrFn_UiDialogSetEnabled)},
            {"KeyConfigSetKey", reinterpret_cast<void**>(&g_BzrFn_KeyConfigSetKey)},
            {"WriteInputMapKey", reinterpret_cast<void**>(&g_BzrFn_WriteInputMapKey)},
            {"MapKeyNameFromCode", reinterpret_cast<void**>(&g_BzrFn_MapKeyNameFromCode)},
            {"ReloadGameKeyMap", reinterpret_cast<void**>(&g_BzrFn_ReloadGameKeyMap)},
            {"GetSelected", reinterpret_cast<void**>(&g_BzrFn_GetSelected)},
            {"CommandHandler", reinterpret_cast<void**>(&g_BzrFn_CommandHandler)},
            {"HelpLog", reinterpret_cast<void**>(&g_BzrFn_HelpLog)},
            {"HelpUi", reinterpret_cast<void**>(&g_BzrFn_HelpUi)},
            {"BanLookup", reinterpret_cast<void**>(&g_BzrFn_BanLookup)},
            {"IsHost", reinterpret_cast<void**>(&g_BzrFn_IsHost)},
            {"AutoLoadShellGame", reinterpret_cast<void**>(&g_BzrFn_AutoLoadShellGame)},
            {"LoadGameByPath", reinterpret_cast<void**>(&g_BzrFn_LoadGameByPath)},
            {"LoadScreenPrep", reinterpret_cast<void**>(&g_BzrFn_LoadScreenPrep)},
            {"FinalizeQueuedLoad", reinterpret_cast<void**>(&g_BzrFn_FinalizeQueuedLoad)},
            {"SetShellState", reinterpret_cast<void**>(&g_BzrFn_SetShellState)},
            {"BzrStringCtorFromCStr", reinterpret_cast<void**>(&g_BzrFn_BzrStringCtorFromCStr)},
            {"BzrStringDtor", reinterpret_cast<void**>(&g_BzrFn_BzrStringDtor)},
            {"LoadScreenClearSelection", reinterpret_cast<void**>(&g_BzrFn_LoadScreenClearSelection)},
            {"ChunkResolve", reinterpret_cast<void**>(&g_BzrFn_ChunkResolve)},
            {"VehicleFixPre", reinterpret_cast<void**>(&g_BzrFn_VehicleFixPre)},
            {"VehicleFixOrig", reinterpret_cast<void**>(&g_BzrFn_VehicleFixOrig)},
            // The multiplayer flag helpers map at the same settled addresses on
            // current GOG and Steam builds.
            {"NetPlayerSetData", reinterpret_cast<void**>(&g_BzrFn_NetPlayerSetData)},
            {"NetPlayerSetFlagBuffer", reinterpret_cast<void**>(&g_BzrFn_NetPlayerSetFlagBuffer)},
            {"SetMyFlag", reinterpret_cast<void**>(&g_BzrFn_SetMyFlag)},
            {"EngineFlameControl", reinterpret_cast<void**>(&g_BzrFn_EngineFlameControl)},
            {"EngineFlameSubmit", reinterpret_cast<void**>(&g_BzrFn_EngineFlameSubmit)},
            {"ChunkEffectSimulate", reinterpret_cast<void**>(&g_BzrFn_ChunkEffectSimulate)},
            // FUN_00679570: _updateRenderQueue override of the game's world
            // renderable container — the only exe-side caller of
            // Ogre::RenderQueue::addRenderable. Vtable slot 0x00892728.
            {"LegacyWorldUpdateRenderQueue", reinterpret_cast<void**>(&g_BzrFn_LegacyWorldUpdateRenderQueue)},
            {"AIBuildConstructionEnd", reinterpret_cast<void**>(&g_BzrFn_AIBuildConstructionEnd)},
            {"AIBuildReservedAreaRemove", reinterpret_cast<void**>(&g_BzrFn_AIBuildReservedAreaRemove)},
            {"AISpentCreditRefund", reinterpret_cast<void**>(&g_BzrFn_AISpentCreditRefund)},
            {"UnitsSOrderStop", reinterpret_cast<void**>(&g_BzrFn_UnitsSOrderStop)},
            {"AIBuildUnassignedCCAdd", reinterpret_cast<void**>(&g_BzrFn_AIBuildUnassignedCCAdd)},
            {"InitBuildItem", reinterpret_cast<void**>(&g_BzrFn_InitBuildItem)},
            {"CleanupBuildItem", reinterpret_cast<void**>(&g_BzrFn_CleanupBuildItem)},
            {"BuildMenuRoot", reinterpret_cast<void**>(&g_BzrBuildMenuRoot)},
            // Producer nested build menus: the stock targets of the replaced
            // vtable slots, the vtables that name the producer type, and the
            // class loader's asset-preload flag.
            {"ProducerUpdateModeList", reinterpret_cast<void**>(&g_BzrFn_ProducerUpdateModeList)},
            {"ProducerSetActiveMode", reinterpret_cast<void**>(&g_BzrFn_ProducerSetActiveMode)},
            {"GameObjectDeselect", reinterpret_cast<void**>(&g_BzrFn_GameObjectDeselect)},
            {"ConstructionRigUpdateModeList", reinterpret_cast<void**>(&g_BzrFn_ConstructionRigUpdateModeList)},
            {"ConstructionRigSetActiveMode", reinterpret_cast<void**>(&g_BzrFn_ConstructionRigSetActiveMode)},
            {"ConstructionRigDeselect", reinterpret_cast<void**>(&g_BzrFn_ConstructionRigDeselect)},
            {"ControlPanelPostLoad", reinterpret_cast<void**>(&g_BzrFn_ControlPanelPostLoad)},
            {"ControlPanelCleanup", reinterpret_cast<void**>(&g_BzrFn_ControlPanelCleanup)},
            {"ModeListSetMode", reinterpret_cast<void**>(&g_BzrFn_ModeListSetMode)},
            {"ProducerVtable", reinterpret_cast<void**>(&g_BzrVtbl_Producer)},
            {"RecyclerVtable", reinterpret_cast<void**>(&g_BzrVtbl_Recycler)},
            {"FactoryVtable", reinterpret_cast<void**>(&g_BzrVtbl_Factory)},
            {"ConstructionRigVtable", reinterpret_cast<void**>(&g_BzrVtbl_ConstructionRig)},
            {"ClassLoadAssetsFlag", reinterpret_cast<void**>(&g_BzrPtr_ClassLoadAssetsFlag)},
        };
        constexpr size_t kRowCount = sizeof(kRows) / sizeof(kRows[0]);
        HookEngine::EngineAddressStatus status[kRowCount] = {};

        const auto bind = [&](size_t i) {
            uint32_t address = 0;
            status[i] = HookEngine::ResolveEngineAddress(kRows[i].name, address);
            *kRows[i].slot = reinterpret_cast<void*>(static_cast<uintptr_t>(address));
        };
        for (size_t i = 0; i < kRowCount; ++i)
            bind(i);

        // On Steam a mismatch can be SteamStub still rewriting the page, so a
        // mismatched row gets a bounded second look (about one second) before
        // it counts as failed. GOG maps its image once; there is nothing to
        // wait for.
        if (g_IsSteamExe)
        {
            for (int attempt = 0; attempt < 100; ++attempt)
            {
                bool pending = false;
                for (size_t i = 0; i < kRowCount; ++i)
                    pending = pending || status[i] == HookEngine::EngineAddressStatus::Mismatch;
                if (!pending)
                    break;
                Sleep(10);
                for (size_t i = 0; i < kRowCount; ++i)
                {
                    if (status[i] == HookEngine::EngineAddressStatus::Mismatch)
                        bind(i);
                }
            }
        }

        unsigned bound = 0;
        unsigned data = 0;
        unsigned failed = 0;
        for (size_t i = 0; i < kRowCount; ++i)
        {
            switch (status[i])
            {
            case HookEngine::EngineAddressStatus::Bound:
                ++bound;
                break;
            case HookEngine::EngineAddressStatus::BoundData:
                ++data;
                break;
            default:
            {
                ++failed;
                const char* why =
                    status[i] == HookEngine::EngineAddressStatus::Missing ? "has no engine_addresses row" :
                    status[i] == HookEngine::EngineAddressStatus::Mismatch ? "guard bytes differ" :
                    "is unreadable";
                LogShimA(LogLevel::Warn, "resolve",
                    "[ADDR] %s %s; pointer left null, dependent features stand down",
                    kRows[i].name, why);
                break;
            }
            }
        }
        LogShimA(failed ? LogLevel::Warn : LogLevel::Info, "resolve",
            "[ADDR] engine addresses: verified=%u data=%u failed=%u of %u",
            bound, data, failed, static_cast<unsigned>(kRowCount));
    }

    // One entry in an ordered list of init calls. The name is for reading
    // (and a debugger); RunInitSteps calls the entries in table order.
    struct InitStep
    {
        const char* name;
        void (*run)();
    };

    template <size_t N>
    void RunInitSteps(const InitStep (&steps)[N])
    {
        for (const InitStep& step : steps)
            step.run();
    }

    const char* FindUnboundEngineHelperForPatch(const char* patchName)
    {
        if (!patchName)
            return nullptr;
        struct Need
        {
            const char* label;
            const void* pointer;
        };
        const auto firstMissing = [](std::initializer_list<Need> needs) -> const char* {
            for (const Need& need : needs)
            {
                if (!need.pointer)
                    return need.label;
            }
            return nullptr;
        };
        const std::string_view name(patchName);
        // 1/4's trampoline calls both helpers unchecked; the four parts are
        // one fix and are not applied piecemeal.
        if (name.rfind("Vehicle List Mod Fix ", 0) == 0)
        {
            return firstMissing({{"VehicleFixPre", g_BzrFn_VehicleFixPre},
                                 {"VehicleFixOrig", g_BzrFn_VehicleFixOrig}});
        }
        // Hooks that replace a stock call and forward to the original.
        if (name == "Chunk Render Resolve Hook")
            return firstMissing({{"ChunkResolve", reinterpret_cast<const void*>(g_BzrFn_ChunkResolve)}});
        if (name == "Engine Flame Control VTable Hook" || name == "Engine Flame Submit VTable Hook")
        {
            return firstMissing({{"EngineFlameControl", reinterpret_cast<const void*>(g_BzrFn_EngineFlameControl)},
                                 {"EngineFlameSubmit", reinterpret_cast<const void*>(g_BzrFn_EngineFlameSubmit)}});
        }
        // Every producer-menu slot needs the whole set: a SetActiveMode
        // replacement with no UpdateModeList partner is harmless, but the
        // reverse would let a menu stub reach the stock build command.
        if (IsProducerBuildMenuPatchName(patchName))
        {
            return firstMissing({{"InitBuildItem", reinterpret_cast<const void*>(g_BzrFn_InitBuildItem)},
                                 {"CleanupBuildItem", reinterpret_cast<const void*>(g_BzrFn_CleanupBuildItem)},
                                 {"ModeListSetMode", reinterpret_cast<const void*>(g_BzrFn_ModeListSetMode)},
                                 {"ProducerUpdateModeList", reinterpret_cast<const void*>(g_BzrFn_ProducerUpdateModeList)},
                                 {"ProducerSetActiveMode", reinterpret_cast<const void*>(g_BzrFn_ProducerSetActiveMode)},
                                 {"GameObjectDeselect", reinterpret_cast<const void*>(g_BzrFn_GameObjectDeselect)},
                                 {"ConstructionRigUpdateModeList", reinterpret_cast<const void*>(g_BzrFn_ConstructionRigUpdateModeList)},
                                 {"ConstructionRigSetActiveMode", reinterpret_cast<const void*>(g_BzrFn_ConstructionRigSetActiveMode)},
                                 {"ConstructionRigDeselect", reinterpret_cast<const void*>(g_BzrFn_ConstructionRigDeselect)},
                                 {"ControlPanelPostLoad", reinterpret_cast<const void*>(g_BzrFn_ControlPanelPostLoad)},
                                 {"ControlPanelCleanup", reinterpret_cast<const void*>(g_BzrFn_ControlPanelCleanup)},
                                 {"ProducerVtable", g_BzrVtbl_Producer},
                                 {"RecyclerVtable", g_BzrVtbl_Recycler},
                                 {"FactoryVtable", g_BzrVtbl_Factory},
                                 {"ConstructionRigVtable", g_BzrVtbl_ConstructionRig},
                                 {"ClassLoadAssetsFlag", g_BzrPtr_ClassLoadAssetsFlag}});
        }
        if (name == "Chunk Effect Simulate VTable Hook")
            return firstMissing({{"ChunkEffectSimulate", reinterpret_cast<const void*>(g_BzrFn_ChunkEffectSimulate)}});
        if (name == "Legacy World Update RenderQueue VTable Hook")
        {
            return firstMissing({{"LegacyWorldUpdateRenderQueue",
                                  reinterpret_cast<const void*>(g_BzrFn_LegacyWorldUpdateRenderQueue)}});
        }
        return nullptr;
    }

    void ResolveBzrHooks(bool isSteam)
    {
        g_IsSteamExe = isSteam;
        ResetBzrHookRuntimeState();

        BindEngineAddresses();

        g_BzrFn_UiDialogAdvance = reinterpret_cast<FnUiDialogAction>(
            HookEngine::ResolveNamedAddress("ShellRequest")); // the same site ui_performance_hooks resolves

        // The live Redux runtime maps these multiplayer flag helpers at the
        // same settled addresses on current GOG and Steam builds.
        g_BzrFn_GetLocalPlayerNetId = reinterpret_cast<FnGetLocalPlayerNetId>(
            HookEngine::ResolveNamedAddress("GetLocalPlayerNetId"));
        // Called addresses that used to be literals in this file (audit P1-1,
        // first slice). The table's scan verifies each fallback; a miss
        // leaves the pointer null or the address 0, and every caller treats
        // that as "stand down".
        g_BzrFn_ResolveObj76GameObject = reinterpret_cast<FnResolveObj76GameObject>(
            HookEngine::ResolveNamedAddress("GameObject::FromObj76"));
        g_BzrFn_PlayGlobalSound = reinterpret_cast<FnPlayGlobalSound>(
            HookEngine::ResolveNamedAddress("PlayGlobalSound"));
        g_GameObjectGetHandleAddr = HookEngine::ResolveNamedAddress("GameObject::GetHandle");

        // Steam's wrapped executable still maps these helpers at the same live
        // runtime addresses as GOG on the current 2.2.301 build.
        //
        // AddFlame, ResolveTexture and GetTeamNum come from the "resolves"
        // array in scripts/patches.json, which carries those same addresses as
        // `fallback`. Resolving here instead of seeding a literal is what makes
        // their signatures run at all: seeding first left
        // ResolveEngineFlameRuntimeTargets() returning early in every process,
        // so the scan below it had never once executed. "prefer": "fallback"
        // keeps the address identical to the constant until a live [RESOLVE]
        // line reports agree=yes.
        g_BzrFn_EngineFlameAddFlame = reinterpret_cast<FnEngineFlameAddFlame>(
            HookEngine::ResolveNamedAddress("EngineFlame::AddFlame"));
        // One function in two roles; resolve once and share it.
        const uint32_t resolveTexture =
            HookEngine::ResolveNamedAddress("EngineFlame::ResolveTexture");
        g_BzrFn_EngineFlameResolveTexture =
            reinterpret_cast<FnEngineFlameResolveTexture>(resolveTexture);
        g_BzrFn_HudSpriteLookup = reinterpret_cast<FnHudSpriteLookup>(resolveTexture);
        g_BzrFn_GetTeamNum = reinterpret_cast<FnGetTeamNum>(
            HookEngine::ResolveNamedAddress("GetTeamNum"));
        InstallDynamicGeometryHooks();

        // Init-time hooks that need nothing from the switches read below.
        // InstallEntityFrustumCullingIfEnabled is not here: it runs further
        // down, once its two switches have been read (here it saw both false
        // and did nothing).
        static const InitStep kEarlyInstallSteps[] = {
            {"InstallJumpSnipingProbeIfRequested", &InstallJumpSnipingProbeIfRequested},
            {"InstallCareerStatsMpHookIfPossible", &InstallCareerStatsMpHookIfPossible},
            {"InstallUnitVoQueueHooksIfPossible", &InstallUnitVoQueueHooksIfPossible},
            {"InstallParticleTemplateDedupeHookIfPossible", &InstallParticleTemplateDedupeHookIfPossible},
            {"InstallOgreScriptImportCacheIfPossible", &InstallOgreScriptImportCacheIfPossible},
            {"InstallResourceWalkStatCacheIfPossible", &InstallResourceWalkStatCacheIfPossible},
            {"InstallUiManualObjectDedupeHookIfPossible", &InstallUiManualObjectDedupeHookIfPossible},
            {"InstallSceneTeardownForgetHooksIfPossible", &InstallSceneTeardownForgetHooksIfPossible},
            {"InstallEntityReloadLifetimeHookIfPossible", &InstallEntityReloadLifetimeHookIfPossible},
            {"InstallMissionTransitionSeamIfPossible", &InstallMissionTransitionSeamIfPossible},
            {"PinDirect3DModulesForShutdown", &PinDirect3DModulesForShutdown},
            {"InstallMultiplayerFlagRenderHookIfPossible", &InstallMultiplayerFlagRenderHookIfPossible},
            {"InstallNicknameTextEntryInputHookIfPossible", &InstallNicknameTextEntryInputHookIfPossible},
            {"StartCareerStatsMpSessionWorker", &StartCareerStatsMpSessionWorker},
            {"InstallShieldTowerTeamFilterHookIfPossible", &InstallShieldTowerTeamFilterHookIfPossible},
            {"InstallMineTeamFilterHooksIfPossible", &InstallMineTeamFilterHooksIfPossible},
        };
        RunInitSteps(kEarlyInstallSteps);
        // Kill switches for the gameplay fixes: each is on unless either
        // name is set. Read here, ahead of the Install* calls below; each
        // Refresh*State() reads only its own flag.
        static const EnvSwitches::EnvSwitch kFixKillSwitches[] = {
            {&g_MagnetZeroRangeGuardEnabled, EnvSwitches::Kind::KillSwitch,
             "OPENSHIM_DISABLE_MAGNET_ZERO_RANGE_FIX", "BZR_DISABLE_MAGNET_ZERO_RANGE_FIX"},
            {&g_UnfocusedMouseReleaseEnabled, EnvSwitches::Kind::KillSwitch,
             "OPENSHIM_DISABLE_UNFOCUSED_MOUSE_RELEASE", "BZR_DISABLE_UNFOCUSED_MOUSE_RELEASE"},
            {&g_BriefingScrollFixEnabled, EnvSwitches::Kind::KillSwitch,
             "OPENSHIM_DISABLE_BRIEFING_SCROLL_FIX", "BZR_DISABLE_BRIEFING_SCROLL_FIX"},
            {&g_MultiRenderCountClampEnabled, EnvSwitches::Kind::KillSwitch,
             "OPENSHIM_DISABLE_RENDERCOUNT_CLAMP", "BZR_DISABLE_RENDERCOUNT_CLAMP"},
            {&g_ThumbnailBmpGuardEnabled, EnvSwitches::Kind::KillSwitch,
             "OPENSHIM_DISABLE_BMP_GUARD", "BZR_DISABLE_BMP_GUARD"},
            {&g_ProducerScriptPredicateHooksEnabled, EnvSwitches::Kind::KillSwitch,
             "OPENSHIM_DISABLE_PRODUCER_SCRIPT_PREDICATES", "BZR_DISABLE_PRODUCER_SCRIPT_PREDICATES"},
            {&g_TugCargoPostLoadFixEnabled, EnvSwitches::Kind::KillSwitch,
             "OPENSHIM_DISABLE_TUG_CARGO_FIX", "BZR_DISABLE_TUG_CARGO_FIX"},
            {&g_ConstructorRecycleStaleTargetFixEnabled, EnvSwitches::Kind::KillSwitch,
             "OPENSHIM_DISABLE_CONSTRUCTOR_RECYCLE_FIX", "BZR_DISABLE_CONSTRUCTOR_RECYCLE_FIX"},
            {&g_ApcAlliedTargetDeployFixEnabled, EnvSwitches::Kind::KillSwitch,
             "OPENSHIM_DISABLE_APC_DEPLOY_FIX", "BZR_DISABLE_APC_DEPLOY_FIX"},
            {&g_QuakeReplayFadeEnabled, EnvSwitches::Kind::KillSwitch,
             "OPENSHIM_DISABLE_QUAKE_FADE", "BZR_DISABLE_QUAKE_FADE"},
            {&g_TargetCamSatelliteFixEnabled, EnvSwitches::Kind::KillSwitch,
             "OPENSHIM_DISABLE_TARGETCAM_FIX", "BZR_DISABLE_TARGETCAM_FIX"},
            {&g_CinematicSatelliteZoomFixEnabled, EnvSwitches::Kind::KillSwitch,
             "OPENSHIM_DISABLE_CINECAM_FIX", "BZR_DISABLE_CINECAM_FIX"},
        };
        EnvSwitches::Apply(kFixKillSwitches, EnvFlagEnabled);
        RefreshTugCargoPostLoadFixState();
        RefreshConstructorRecycleStaleTargetFixState();
        RefreshApcAlliedTargetDeployFixState();

        g_OwnedObjectRevealFixEnabled = kOwnedObjectRevealFixEnabledDefault;
        bool ownedObjectRevealConfig = kOwnedObjectRevealFixEnabledDefault;
        if (TryGetUserConfigBool(kUserConfigFixesSection,
                                 "OwnedObjectReveal",
                                 ownedObjectRevealConfig))
        {
            g_OwnedObjectRevealFixEnabled = ownedObjectRevealConfig;
        }
        if (EnvFlagEnabled("OPENSHIM_DISABLE_OWNED_OBJECT_REVEAL") ||
            EnvFlagEnabled("BZR_DISABLE_OWNED_OBJECT_REVEAL"))
        {
            g_OwnedObjectRevealFixEnabled = false;
        }
        RefreshOwnedObjectRevealFixState();
        g_OwnedObjectRevealTraceBudget = kOwnedObjectRevealTraceBudgetDefault;
		{
			long quakeFadeSeconds = kQuakeReplayFadeSecondsDefault;
			if (TryGetEnvLong("OPENSHIM_QUAKE_FADE_SECONDS", quakeFadeSeconds))
			{
				if (quakeFadeSeconds < kQuakeReplayFadeSecondsMin)
					quakeFadeSeconds = kQuakeReplayFadeSecondsMin;
				if (quakeFadeSeconds > kQuakeReplayFadeSecondsMax)
					quakeFadeSeconds = kQuakeReplayFadeSecondsMax;
			}
			g_QuakeReplayFadeSeconds = quakeFadeSeconds;
		}
        // The gameplay-fix installs. Each reads its enable flag, so these run
        // after the kill-switch table above. InstallSplinterUndeadFixIfPossible
        // sees the splinter default here; its env override is read further
        // down and applied by RefreshSplinterUndeadFixState().
        static const InitStep kFixInstallSteps[] = {
            {"InstallProducerScriptPredicateHooksIfPossible", &InstallProducerScriptPredicateHooksIfPossible},
            {"InstallBriefingScrollFixIfPossible", &InstallBriefingScrollFixIfPossible},
            {"InstallMultiRenderCountClampIfPossible", &InstallMultiRenderCountClampIfPossible},
            {"InstallThumbnailBmpGuardIfPossible", &InstallThumbnailBmpGuardIfPossible},
            {"InstallSplinterUndeadFixIfPossible", &InstallSplinterUndeadFixIfPossible},
            {"InstallMpauthHooksIfPossible", &InstallMpauthHooksIfPossible},
            {"InstallTugCargoPostLoadFixIfPossible", &InstallTugCargoPostLoadFixIfPossible},
            {"InstallConstructorRecycleStaleTargetFixIfPossible", &InstallConstructorRecycleStaleTargetFixIfPossible},
            {"InstallApcAlliedTargetDeployFixIfPossible", &InstallApcAlliedTargetDeployFixIfPossible},
            {"InstallQuakeReplayFadeIfPossible", &InstallQuakeReplayFadeIfPossible},
            {"InstallTargetCamSatelliteFixIfPossible", &InstallTargetCamSatelliteFixIfPossible},
            {"InstallCinematicSatelliteZoomFixIfPossible", &InstallCinematicSatelliteZoomFixIfPossible},
            {"InstallUnfocusedMouseReleaseIfPossible", &InstallUnfocusedMouseReleaseIfPossible},
        };
        RunInitSteps(kFixInstallSteps);

        // Retry for whichever of the three resolved to 0 above. This used to
        // be gated on g_IsSteamExe, from when the scan was Steam's path and
        // GOG relied on the literals; both storefronts now take the same
        // route, and on GOG this was the only init-time caller.
        ResolveEngineFlameRuntimeTargets();

        g_EnableChunkRenderFallback =
            EnvFlagEnabled("BZR_CHUNK_FORCE_FIRST_GEO") ||
            EnvFlagEnabled("OPENSHIM_CHUNK_FORCE_FIRST_GEO");
        g_EnableChunkProxyDebug =
            EnvFlagEnabled("OPENSHIM_CHUNK_PROXY_DEBUG") ||
            EnvFlagEnabled("OPENSHIM_CHUNK_PLACEHOLDER_PROXY");
        // Centralized asset-pack detection. Refresh early so chunk-mesh and
        // other asset-backed features can be gated on filesystem-validated
        // capabilities rather than config alone. This is the single authority
        // for "do the destruction chunk payloads exist?" — individual call
        // sites query IsAssetFeatureAvailable() instead of probing the
        // filesystem themselves.
        Assets::RefreshAssetCapabilities();
        const bool chunkAssetsAvailable =
            Assets::IsAssetFeatureAvailable(Assets::AssetFeature::DestructionChunks);
        const bool configWantsChunkMeshProxy =
            !(EnvFlagEnabled("OPENSHIM_DISABLE_CHUNK_MESH_PROXY") ||
              EnvFlagEnabled("BZR_DISABLE_CHUNK_MESH_PROXY"));
        // Mesh pieces can now be generated from the source Ogre resource.
        // External payload packs remain a fallback, not a prerequisite.
        g_EnableChunkMeshProxy = configWantsChunkMeshProxy;
        PruneNativeChunkCache();
        WarmNativeChunkCaches();
        if (configWantsChunkMeshProxy && !chunkAssetsAvailable)
        {
            static bool s_logged = false;
            if (!s_logged)
            {
                s_logged = true;
                const auto caps = Assets::GetAssetCapabilities();
                Log(L"[CHUNKMESH] External payloads unavailable; using native mesh extraction state=%hs installed=%hs problem=%hs\n",
                    Assets::AssetPackStateName(caps.state),
                    caps.installedVersion.c_str(),
                    caps.problem.c_str());
            }
        }
        g_EnableGenericChunkBatch =
            g_EnableChunkMeshProxy &&
            !(EnvFlagEnabled("OPENSHIM_DISABLE_GENERIC_CHUNK_BATCH") ||
              EnvFlagEnabled("BZR_DISABLE_GENERIC_CHUNK_BATCH"));
        static const EnvSwitches::EnvSwitch kFrustumSwitches[] = {
            // Restores the per-object frustum test that Redux's
            // DefaultSceneManager never performs. Measured: 20 tanks 50 m
            // behind the camera cost exactly as many main-view submissions
            // as 20 tanks in front of it.
            {&g_EntityFrustumCullEnabled, EnvSwitches::Kind::KillSwitch,
             "OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING", "BZR_DISABLE_ENTITY_FRUSTUM_CULLING"},
            {&g_FrustumCullCensusEnabled, EnvSwitches::Kind::OptIn,
             "OPENSHIM_FRUSTUM_CULL_CENSUS", "BZR_FRUSTUM_CULL_CENSUS"},
            // Second, independent repair experiment: restore finite Ogre
            // bounds on the shared craft meshes instead of emulating the
            // frustum test privately. Opt-in, and it stands the private cull
            // down by default so the two mechanisms are never measured on
            // top of each other. Set OPENSHIM_FRUSTUM_CULL_WITH_RESTORE=1 to
            // run both deliberately.
            {&g_RestoreCraftBoundsEnabled, EnvSwitches::Kind::OptIn,
             "OPENSHIM_RESTORE_CRAFT_BOUNDS", "BZR_RESTORE_CRAFT_BOUNDS"},
            {&g_BoundsTraceEnabled, EnvSwitches::Kind::OptIn,
             "OPENSHIM_BOUNDS_TRACE", "BZR_BOUNDS_TRACE"},
        };
        EnvSwitches::Apply(kFrustumSwitches, EnvFlagEnabled);
        if (g_RestoreCraftBoundsEnabled &&
            !(EnvFlagEnabled("OPENSHIM_FRUSTUM_CULL_WITH_RESTORE") ||
              EnvFlagEnabled("BZR_FRUSTUM_CULL_WITH_RESTORE")))
        {
            g_EntityFrustumCullEnabled = false;
        }
        // Both switches are known now. The earlier call in this function ran
        // before they were computed and did nothing, leaving the deferred
        // retry to install the feature; installing here keeps the retry as
        // the OgreMain-not-yet-loaded fallback it is meant to be.
        InstallEntityFrustumCullingIfEnabled();
        // Diagnostic/regression seam, not a gameplay policy. It exists so the
        // batch-failure fallback can be proven at runtime rather than argued
        // from the source; see RehydrateGenericChunkBatchSlotsToEntities().
        g_ForceGenericChunkBatchFailure =
            EnvFlagEnabled("OPENSHIM_FORCE_GENERIC_CHUNK_BATCH_FAILURE") ||
            EnvFlagEnabled("BZR_FORCE_GENERIC_CHUNK_BATCH_FAILURE");
        if (g_ForceGenericChunkBatchFailure)
        {
            LogChunkDiagnostic(
                "chunkbatch",
                L"[CHUNKBATCH] DIAGNOSTIC: forced generic chunk batch failure is ENABLED\n");
        }
        // Opt-in measurement seam. The game drives its _updateRenderQueue
        // override more than once per rendered frame, so the number of batch
        // rebuilds per frame has to be counted rather than assumed. Off by
        // default: when disabled not even the counters are touched.
        g_GenericChunkBatchRateDiagnostics =
            EnvFlagEnabled("OPENSHIM_CHUNK_BATCH_RATE_DIAGNOSTICS") ||
            EnvFlagEnabled("BZR_CHUNK_BATCH_RATE_DIAGNOSTICS");
        if (g_GenericChunkBatchRateDiagnostics)
        {
            LogChunkDiagnostic(
                "chunkbatch",
                L"[CHUNKBATCH] DIAGNOSTIC: batch submit-rate counters are ENABLED\n");
        }
        // Reuse is on by default; the opt-out restores the pre-optimization
        // behaviour of re-emitting the geometry on every traversal, and observe
        // mode takes the decision without acting on it so the baseline and the
        // dedup opportunity can be measured from one binary.
        g_GenericChunkBatchReuseEnabled =
            !(EnvFlagEnabled("OPENSHIM_DISABLE_CHUNK_BATCH_REUSE") ||
              EnvFlagEnabled("BZR_DISABLE_CHUNK_BATCH_REUSE"));
        g_GenericChunkBatchReuseObserveOnly =
            EnvFlagEnabled("OPENSHIM_CHUNK_BATCH_REUSE_OBSERVE") ||
            EnvFlagEnabled("BZR_CHUNK_BATCH_REUSE_OBSERVE");
        {
            bool configured = false;
            if (TryGetUserConfigBool("Diagnostics", "ChunkBatchReuse", configured))
                g_GenericChunkBatchReuseEnabled = configured;
            if (TryGetUserConfigBool("Diagnostics", "ChunkBatchReuseObserve", configured))
                g_GenericChunkBatchReuseObserveOnly = configured;
        }
        LogChunkDiagnostic(
            "chunkbatch",
            L"[CHUNKBATCH] generic batch state-version reuse=%hs observeOnly=%hs\n",
            g_GenericChunkBatchReuseEnabled ? "on" : "off",
            g_GenericChunkBatchReuseObserveOnly ? "yes" : "no");
        g_ForceGenericChunkNonUnitScale =
            EnvFlagEnabled("OPENSHIM_FORCE_GENERIC_CHUNK_NON_UNIT_SCALE") ||
            EnvFlagEnabled("BZR_FORCE_GENERIC_CHUNK_NON_UNIT_SCALE");
        if (g_ForceGenericChunkNonUnitScale)
        {
            LogChunkDiagnostic(
                "chunkbatch",
                L"[CHUNKBATCH] DIAGNOSTIC: forced non-unit generic chunk scale is ENABLED\n");
        }
        g_EnablePartialFragmentBoneCollapse =
            !(EnvFlagEnabled("OPENSHIM_DISABLE_PARTIAL_FRAGMENT_BONE_COLLAPSE") ||
              EnvFlagEnabled("BZR_DISABLE_PARTIAL_FRAGMENT_BONE_COLLAPSE"));
        // This walks every live Ogre entity and invokes best-effort metadata
        // probes. It was accidentally left on for every production session;
        // invalid/stale candidates are SEH-guarded, but still generate costly
        // first-chance AVs (especially under Wine/Proton). Diagnostics are
        // opt-in like the other runtime research traces.
        g_VehicleSkinningTraceEnabled =
            (EnvFlagEnabled("OPENSHIM_TRACE_VEHICLE_SKINNING") ||
             EnvFlagEnabled("BZR_TRACE_VEHICLE_SKINNING")) &&
            !(EnvFlagEnabled("OPENSHIM_DISABLE_VEHICLE_SKINNING_DIAGNOSTICS") ||
              EnvFlagEnabled("OPENSHIM_DISABLE_SKINNING_DIAGNOSTICS") ||
              EnvFlagEnabled("OPENSHIM_DISABLE_VEHICLE_SKINNING_TRACE") ||
              EnvFlagEnabled("BZR_DISABLE_VEHICLE_SKINNING_DIAGNOSTICS"));
        long vehicleSkinningTraceInterval =
            static_cast<long>(kVehicleSkinningTraceIntervalMsDefault);
        if (TryGetEnvLong("OPENSHIM_TRACE_VEHICLE_SKINNING_INTERVAL_MS", vehicleSkinningTraceInterval) ||
            TryGetEnvLong("OPENSHIM_TRACE_SKINNING_INTERVAL_MS", vehicleSkinningTraceInterval))
        {
            if (vehicleSkinningTraceInterval < static_cast<long>(kVehicleSkinningTraceIntervalMsMin))
                vehicleSkinningTraceInterval = kVehicleSkinningTraceIntervalMsMin;
            if (vehicleSkinningTraceInterval > static_cast<long>(kVehicleSkinningTraceIntervalMsMax))
                vehicleSkinningTraceInterval = kVehicleSkinningTraceIntervalMsMax;
        }
        g_VehicleSkinningTraceIntervalMs = static_cast<DWORD>(vehicleSkinningTraceInterval);
        long vehicleSkinningTraceBudget = kVehicleSkinningTraceBudgetDefault;
        if (TryGetEnvLong("OPENSHIM_TRACE_VEHICLE_SKINNING_BUDGET", vehicleSkinningTraceBudget) ||
            TryGetEnvLong("OPENSHIM_TRACE_SKINNING_BUDGET", vehicleSkinningTraceBudget))
        {
            if (vehicleSkinningTraceBudget < 0)
                vehicleSkinningTraceBudget = 0;
            if (vehicleSkinningTraceBudget > 4096)
                vehicleSkinningTraceBudget = 4096;
        }
        g_VehicleSkinningTraceBudget = vehicleSkinningTraceBudget;
        // Normal gameplay needs only a few lifecycle samples. Thousands of
        // synchronous, duplicated log writes can stall a destruction burst.
        // Explicit diagnostic overrides still permit a larger capture.
        long chunkLogBudget = 12;
        const bool chunkLogBudgetSpecified =
            TryGetEnvLong("BZR_CHUNK_LOG_BUDGET", chunkLogBudget) ||
            TryGetEnvLong("OPENSHIM_CHUNK_LOG_BUDGET", chunkLogBudget);
        if (chunkLogBudgetSpecified)
        {
            if (chunkLogBudget < 0)
                chunkLogBudget = 0;
        }
        g_ChunkRenderLogBudget = chunkLogBudget;
        g_ChunkObservedClassIds.clear();
        g_LastChunkEffectLoggedCount = UINT32_MAX;
        long chunkTraceEntryLimit = 32;
        const bool chunkTraceEntryLimitSpecified =
            TryGetEnvLong("BZR_CHUNK_TRACE_ENTRY_LIMIT", chunkTraceEntryLimit) ||
            TryGetEnvLong("OPENSHIM_CHUNK_TRACE_ENTRY_LIMIT", chunkTraceEntryLimit);
        if (chunkTraceEntryLimitSpecified)
        {
            g_ChunkTraceEntryLimit = ClampChunkTraceEntryLimit(chunkTraceEntryLimit);
        }
        else
        {
            g_ChunkTraceEntryLimit = ClampChunkTraceEntryLimit(chunkTraceEntryLimit);
        }
        const bool disableChunkTrace =
            EnvFlagEnabled("BZR_DISABLE_CHUNK_TRACE") ||
            EnvFlagEnabled("OPENSHIM_DISABLE_CHUNK_TRACE");
        g_TraceChunkRender =
            !disableChunkTrace &&
            (g_EnableChunkRenderFallback ||
             g_EnableChunkProxyDebug ||
             g_EnableChunkMeshProxy ||
             EnvFlagEnabled("BZR_CHUNK_TRACE") ||
             EnvFlagEnabled("OPENSHIM_CHUNK_TRACE") ||
             chunkLogBudgetSpecified ||
             chunkTraceEntryLimitSpecified);
        g_TraceChunkRenderVerbose =
            EnvFlagEnabled("BZR_CHUNK_TRACE_VERBOSE") ||
            EnvFlagEnabled("OPENSHIM_CHUNK_TRACE_VERBOSE");
        const bool disableChunkEffectTrace =
            EnvFlagEnabled("BZR_DISABLE_CHUNK_EFFECT_TRACE") ||
            EnvFlagEnabled("OPENSHIM_DISABLE_CHUNK_EFFECT_TRACE");
        // Opt-in only: the per-frame [CHUNKEFFECT] sampler exhausts the shared
        // chunk log budget within seconds and silences lifecycle logging.
        g_TraceChunkEffectRuntime =
            !disableChunkEffectTrace &&
            (EnvFlagEnabled("BZR_TRACE_CHUNK_EFFECT") ||
             EnvFlagEnabled("OPENSHIM_TRACE_CHUNK_EFFECT") ||
             EnvFlagEnabled("OPENSHIM_CHUNK_EFFECT_TRACE"));
        // g_TraceChunkRender above is also switched on by ChunkMeshes alone
        // (it arms the hooks the mesh proxy depends on), which used to make
        // every debris piece emit ~5 flushed lines: ~2000 lines/s in a
        // minigun fight until the 4000-line budget ran dry. Per-chunk lines
        // now need an explicit trace or chunk-debug request.
        g_ChunkEventLogging =
            (!disableChunkTrace &&
             (g_EnableChunkRenderFallback ||
              g_EnableChunkProxyDebug ||
              EnvFlagEnabled("BZR_CHUNK_TRACE") ||
              EnvFlagEnabled("OPENSHIM_CHUNK_TRACE") ||
              g_TraceChunkRenderVerbose ||
              chunkLogBudgetSpecified ||
              chunkTraceEntryLimitSpecified)) ||
            g_TraceChunkEffectRuntime;
        InstallChunkEffectCreateHooksIfRequested();
        InstallChunkFragmentWalkHooksIfRequested();
        // Satellite fog-of-war investigation (feature item 24). Defaulted ON
        // for now so an ordinary session produces a scoreable capture with no
        // launch-time setup; see
        // reverse_engineering/satellite_fow_root_cause_20260817.md. Revert to
        // default-OFF once the regression is characterised.
        //
        // Back to default OFF. It was temporarily default-ON only while the
        // satellite fog-of-war regression was being characterised; that work is
        // finished and the fix is validated, so its per-object sampling is now
        // just noise in every normal session. The bounded [SATVISCHK] capture
        // (OPENSHIM_SATVIS_VALIDATE) is the tool for re-scoring the fix.
        //
        // Precedence, most specific first:
        //   1. [Diagnostics] TraceSatelliteVisibility  (explicit, either way)
        //   2. the positive TRACE_* env aliases
        //   3. OFF
        {
            bool satelliteVisibilityConfig = false;
            if (TryGetUserConfigBool("Diagnostics", "TraceSatelliteVisibility",
                                     satelliteVisibilityConfig))
            {
                g_TraceSatelliteVisibility = satelliteVisibilityConfig;
            }
            else
            {
                g_TraceSatelliteVisibility =
                    EnvFlagEnabled("OPENSHIM_TRACE_SAT_VIS") ||
                    EnvFlagEnabled("OPENSHIM_TRACE_SATELLITE_VISIBILITY") ||
                    EnvFlagEnabled("BZR_TRACE_SAT_VIS");
            }
        }
        // Read-only damage-reveal probe. Default OFF: it is an investigation
        // tool, and its per-hit logging is far too chatty for normal play.
        {
            bool damageRevealConfig = false;
            if (TryGetUserConfigBool("Diagnostics", "TraceDamageReveal", damageRevealConfig))
                g_TraceDamageReveal = damageRevealConfig;
            else
                g_TraceDamageReveal = EnvFlagEnabled("OPENSHIM_TRACE_DAMAGE_REVEAL") ||
                                      EnvFlagEnabled("BZR_TRACE_DAMAGE_REVEAL");
            g_DamageRevealTraceBudget = kDamageRevealTraceBudgetDefault;
        }

        // Player-kill research trace init (opt-in). Mirrors damage-reveal
        // pattern: ini key [Diagnostics] TracePlayerKills, env
        // OPENSHIM_TRACE_PLAYER_KILLS / BZR_TRACE_PLAYER_KILLS.
        {
            bool playerKillConfig = false;
            if (TryGetUserConfigBool("Diagnostics", "TracePlayerKills", playerKillConfig))
                g_TracePlayerKills = playerKillConfig;
            else
                g_TracePlayerKills = EnvFlagEnabled("OPENSHIM_TRACE_PLAYER_KILLS") ||
                                     EnvFlagEnabled("BZR_TRACE_PLAYER_KILLS");
            long budget = kPlayerKillTraceBudgetDefault;
            if (TryGetEnvLong("OPENSHIM_TRACE_PLAYER_KILLS_BUDGET", budget) ||
                TryGetEnvLong("BZR_TRACE_PLAYER_KILLS_BUDGET", budget))
            {
                if (budget < 0) budget = 0;
                if (budget > kPlayerKillTraceBudgetMax) budget = kPlayerKillTraceBudgetMax;
            }
            g_PlayerKillTraceBudget = budget;
            if (g_TracePlayerKills)
                Log(L"[PKTRACE] Player-kill trace enabled budget=%ld\n", budget);
        }

        InitializeCareerStatsConfig();

        InitializeHopOutAttackAlertConfig();

        InitializeSatelliteVisibilityFixConfig(true);
        {
            // Validation fixture (see g_SatVisTestPreHideEnabled). Environment
            // only -- deliberately absent from openshim.ini so it cannot be
            // switched on by a user config.
            long preHideTeam = 0;
            g_SatVisTestPreHideEnabled =
                TryGetEnvLong("OPENSHIM_SATVIS_TEST_PREHIDE_TEAM", preHideTeam) &&
                preHideTeam >= 0 && preHideTeam <= 15;
            g_SatVisTestPreHideTeam =
                g_SatVisTestPreHideEnabled ? static_cast<int>(preHideTeam) : 0;
            g_SatVisTestPreHidden.clear();
            if (g_SatVisTestPreHideEnabled)
            {
                Log(L"[SATVISFIX] validation pre-hide fixture armed for team %d\n",
                    g_SatVisTestPreHideTeam);
            }

            g_SatVisValidateEnabled = EnvFlagEnabled("OPENSHIM_SATVIS_VALIDATE");
            long validateBudget = kSatVisValidateBudgetDefault;
            if (!TryGetEnvLong("OPENSHIM_SATVIS_VALIDATE_BUDGET", validateBudget) ||
                validateBudget <= 0 || validateBudget > 100000)
            {
                validateBudget = kSatVisValidateBudgetDefault;
            }
            g_SatVisValidateBudget = validateBudget;
            g_SatVisValidateLastTick = 0;
            if (g_SatVisValidateEnabled)
            {
                Log(L"[SATVISCHK] validation capture armed: budget=%ld interval=%lums\n",
                    validateBudget,
                    static_cast<unsigned long>(kSatVisValidateIntervalMs));
            }
        }

        // Attack reveal. Effective for the first time as of 2026-08-17: it had
        // been writing the actual-team field back over itself, so it always
        // short-circuited on "already_revealed". Now that it reaches the real
        // perceivedTeam it needs a kill switch that is not the exported bridge
        // API, because this is the first build in which turning it off can
        // actually change anything.
        //
        // Migration ordering / fail-closed: preset migration must happen
        // before this read (or the loader must reload the migrated file).
        // TryMigratePlayerPresetOnStartup is invoked early from the patcher
        // thread before any Initialize* runs, so a corrected file is already
        // on disk for this boot where practical. If the game directory cannot
        // be written, migration logs the failure but runtime must still fail
        // closed for the quarantined hook; MigrationRequiresSafeFallback…()
        // forces the safe default for this boot even though the file still
        // holds the old 1.
        {
            bool attackRevealConfig = false;
            if (MigrationRequiresSafeFallbackForAttackReveal())
            {
                g_AttackRevealEnabled = false;
                Log(L"[CONFIG] preset migration requires safe AttackReveal fallback; forcing disabled for this boot\n");
            }
            else if (TryGetUserConfigBool("SinglePlayer", "AttackRevealPerceivedTeam",
                                     attackRevealConfig))
            {
                g_AttackRevealEnabled = attackRevealConfig;
            }
            else if (EnvFlagEnabled("OPENSHIM_DISABLE_ATTACK_REVEAL") ||
                     EnvFlagEnabled("BZR_DISABLE_ATTACK_REVEAL"))
            {
                g_AttackRevealEnabled = false;
            }
            else
            {
                g_AttackRevealEnabled = kAttackRevealEnabledDefault;
            }
            RefreshAttackRevealState();
        }
        g_ConstructorRemoteBuildFixEnabled =
            !(EnvFlagEnabled("OPENSHIM_DISABLE_CONSTRUCTOR_REMOTE_BUILD_FIX") ||
              EnvFlagEnabled("BZR_DISABLE_CONSTRUCTOR_REMOTE_BUILD_FIX"));
        RefreshConstructorRemoteBuildFixState();
        long constructorCleanupTraceBudget = kConstructorRemoteBuildTraceBudgetDefault;
        if (TryGetEnvLong("OPENSHIM_TRACE_CONSTRUCTOR_REMOTE_BUILD_BUDGET", constructorCleanupTraceBudget) ||
            TryGetEnvLong("BZR_TRACE_CONSTRUCTOR_REMOTE_BUILD_BUDGET", constructorCleanupTraceBudget))
        {
            if (constructorCleanupTraceBudget < 0)
                constructorCleanupTraceBudget = 0;
        }
        g_ConstructorRemoteBuildTraceBudget = constructorCleanupTraceBudget;
        g_SplinterUndeadFixEnabled =
            !(EnvFlagEnabled("OPENSHIM_DISABLE_SPLINTER_UNDEAD_FIX") ||
              EnvFlagEnabled("BZR_DISABLE_SPLINTER_UNDEAD_FIX"));
        RefreshSplinterUndeadFixState();
        long splinterUndeadTraceBudget = kSplinterUndeadTraceBudgetDefault;
        if (TryGetEnvLong("OPENSHIM_TRACE_SPLINTER_UNDEAD_BUDGET", splinterUndeadTraceBudget) ||
            TryGetEnvLong("BZR_TRACE_SPLINTER_UNDEAD_BUDGET", splinterUndeadTraceBudget))
        {
            if (splinterUndeadTraceBudget < 0)
                splinterUndeadTraceBudget = 0;
        }
        g_SplinterUndeadTraceBudget = splinterUndeadTraceBudget;
        long chunkProxyCapacity = static_cast<long>(g_ChunkProxyCapacity);
        if (TryGetEnvLong("OPENSHIM_CHUNK_PROXY_CAP", chunkProxyCapacity) ||
            TryGetEnvLong("OPENSHIM_CHUNK_PROXY_CAPACITY", chunkProxyCapacity))
        {
            g_ChunkProxyCapacity = ClampChunkProxyCapacity(chunkProxyCapacity);
        }
        else
        {
            g_ChunkProxyCapacity = 256;
        }
        float chunkProxySize = g_ChunkProxyDebugSize;
        if (TryGetEnvFloat("OPENSHIM_CHUNK_PROXY_SIZE", chunkProxySize) ||
            TryGetEnvFloat("OPENSHIM_CHUNK_PROXY_DEBUG_SIZE", chunkProxySize))
        {
            g_ChunkProxyDebugSize = ClampChunkProxySize(chunkProxySize);
        }
        else
        {
            g_ChunkProxyDebugSize = 2.5f;
        }
        long satelliteVisibilityBudget = g_SatelliteVisibilityLogBudget;
        if (TryGetEnvLong("OPENSHIM_SAT_VIS_BUDGET", satelliteVisibilityBudget) ||
            TryGetEnvLong("BZR_SAT_VIS_BUDGET", satelliteVisibilityBudget))
        {
            if (satelliteVisibilityBudget < 0)
                satelliteVisibilityBudget = 0;
        }
        g_SatelliteVisibilityLogBudget = satelliteVisibilityBudget;
        long satelliteVisibilityObjectLimit = static_cast<long>(g_SatelliteVisibilityObjectLimit);
        if (TryGetEnvLong("OPENSHIM_SAT_VIS_OBJECT_LIMIT", satelliteVisibilityObjectLimit) ||
            TryGetEnvLong("BZR_SAT_VIS_OBJECT_LIMIT", satelliteVisibilityObjectLimit))
        {
            g_SatelliteVisibilityObjectLimit =
                ClampSatelliteVisibilityObjectLimit(satelliteVisibilityObjectLimit);
        }
        else
        {
            g_SatelliteVisibilityObjectLimit = ClampSatelliteVisibilityObjectLimit(satelliteVisibilityObjectLimit);
        }
        long satelliteVisibilityInterval = static_cast<long>(g_SatelliteVisibilityLogIntervalMs);
        if (TryGetEnvLong("OPENSHIM_SAT_VIS_INTERVAL_MS", satelliteVisibilityInterval) ||
            TryGetEnvLong("BZR_SAT_VIS_INTERVAL_MS", satelliteVisibilityInterval))
        {
            g_SatelliteVisibilityLogIntervalMs =
                ClampSatelliteVisibilityLogInterval(satelliteVisibilityInterval);
        }
        else
        {
            g_SatelliteVisibilityLogIntervalMs =
                ClampSatelliteVisibilityLogInterval(satelliteVisibilityInterval);
        }
        g_SatelliteVisibilityLastTick = 0;
        g_ChunkProxyLastRetryTick = 0;
        g_ChunkProxyInitLogged = false;
        g_ChunkProxyFailureLogged = false;
        g_ChunkProxyWaitLogged = false;
        g_ChunkMeshProxyLastRetryTick = 0;
        g_ChunkMeshProxyInitLogged = false;
        g_ChunkMeshProxyFailureLogged = false;
        g_ChunkMeshProxyWaitLogged = false;
        g_ChunkPayloadResourceLocationsAttempted = false;
        g_ChunkPayloadResourceLocationsReady = false;
        g_ChunkPayloadResourceLocationsLogged = false;
        g_ChunkPayloadResourceLocationsFailureLogged = false;
        g_ChunkProxyBillboardSet = nullptr;
        g_ChunkProxySlots.clear();
        g_GenericChunkBatchManualObject = nullptr;
        // The recorded visibility described the object just dropped.
        g_GenericChunkBatchVisible = false;
        g_GenericChunkBatchSceneNode = nullptr;
        g_GenericChunkBatchSceneManager = nullptr;
        g_GenericChunkBatchSectionCreated = false;
        // Process/scene shutdown drops the cached geometry with the object it
        // lived in, so reuse can never straddle a lifetime boundary.
        g_GenericChunkBatchBuiltVersion = ChunkBatchInvalidation::kUnbuiltVersion;
        g_GenericChunkBatchBuiltMaterial.clear();
        g_GenericChunkBatchRuntimeAvailable = true;
        g_GenericChunkBatchEligibility[0] = -1;
        g_GenericChunkBatchEligibility[1] = -1;
        g_StockFallbackBatchEligibility[0] = -1;
        g_StockFallbackBatchEligibility[1] = -1;
        g_GenericChunkBatchLastLogTick = 0;
        g_ChunkPayloadResourceDirectories.clear();
        g_ChunkPayloadMeshExistsCache.clear();
        g_ChunkPayloadResolveFailureLogCache.clear();
        g_ChunkResolvedBindingCache.clear();
        ResetNativeChunkPayloads();
        g_ChunkResolvedBindingLastPruneTick = 0;
        InitializeGlobalImprovementConfig();
        const char* rawInputSource = "default";
        const bool rawInputRequested = ResolveRawMouseInputPreference(rawInputSource);
        g_RawMouseInputTraceBudget = ShouldTraceRawMouseInput() ? 256 : 0;
        bool rawInputActive = false;
        if (!RawMouseInputSignaturesMatch())
        {
            // RawMouseInputSignaturesMatch already logged which site failed.
            rawInputActive = false;
        }
        else if (rawInputRequested)
        {
            rawInputActive = GetRawMouseInputEnabledFromBridge() ||
                             SetRawMouseInputEnabledFromBridge(true);
            if (rawInputActive)
                InstallRawMouseInputProcessHookIfPossible();
        }
        else if (GetRawMouseInputEnabledFromBridge())
        {
            // The stock parser saw `rawinput` but configuration says otherwise;
            // the explicit token already won in ResolveRawMouseInputPreference,
            // so reaching here means an env or ini opt-out has to undo it.
            SetRawMouseInputEnabledFromBridge(false);
        }
        LogBzrHookStatus(rawInputActive, rawInputSource);
        // Late per-feature configuration and the UI scaffolds, after the
        // status log.
        static const InitStep kLateInitSteps[] = {
            {"InitializeUnderAttackAlertConfig", &InitializeUnderAttackAlertConfig},
            {"InitializeTargetReticlePopupConfig", &InitializeTargetReticlePopupConfig},
            {"InitializeGlobalTurboConfig", &InitializeGlobalTurboConfig},
            {"InitializeHeadlightConfig", &InitializeHeadlightConfig},
            {"InitializePilotFlashlightConfig", &InitializePilotFlashlightConfig},
            {"InstallWeaponPresentationNativeIfRequested", &InstallWeaponPresentationNativeIfRequested},
            {"InitializeVehicleGeometryContact", &GeometryContactTest::InitializeGlobal},
            {"InstallEmissionLightFixIfPossible", &InstallEmissionLightFixIfPossible},
            {"VerifyExpectedOgreExportsIfPossible", &VerifyExpectedOgreExportsIfPossible},
            {"InitializeJetFlamesConfig", &InitializeJetFlamesConfig},
            {"InitializeUnitVoConfig", &InitializeUnitVoConfig},
            // Must run before the game reaches BZRNet init: the requested UDP port
            // is only honoured while the P2P socket is still closed.
            {"InitializeBzrNetConfig", &InitializeBzrNetConfig},
            {"InstallBzrNetRouteObserverIfPossible", &InstallBzrNetRouteObserverIfPossible},
            {"InstallMapFilterExtrasIfEnabled", &InstallMapFilterExtrasIfEnabled},
            {"EnsureInputBindingPopulateHookScaffold", &EnsureInputBindingPopulateHookScaffold},
            {"EnsureOptionsParentCtorHookScaffold", &EnsureOptionsParentCtorHookScaffold},
            {"EnsureNativeUiMainMenuDiagnosticScaffold", &EnsureNativeUiMainMenuDiagnosticScaffold},
            {"LogShimSettingsUiStatus", &LogShimSettingsUiStatus},
            {"InstallBackgroundRunIfRequested", &InstallBackgroundRunIfRequested},
        };
        RunInitSteps(kLateInitSteps);
        Log(L"[MAPTRACE] Map refresh trace: %hs\n",
            (EnvFlagEnabled("OPENSHIM_TRACE_MAP_REFRESH") ||
             EnvFlagEnabled("OPENSHIM_TRACE_STEAM_MAP_REFRESH")) ? "enabled" : "disabled");
        Log(L"[PRODMENU] Engine helpers: %hs\n",
            (g_BzrFn_InitBuildItem && g_BzrFn_CleanupBuildItem && g_BzrFn_ModeListSetMode &&
             g_BzrFn_ProducerUpdateModeList && g_BzrFn_ProducerSetActiveMode &&
             g_BzrFn_ConstructionRigUpdateModeList && g_BzrFn_ConstructionRigSetActiveMode &&
             g_BzrFn_ControlPanelPostLoad && g_BzrFn_ControlPanelCleanup)
                ? "bound"
                : "incomplete; producer menu slots stand down");
        Log(L"[FLAG] Multiplayer flag UI: %hs\n",
            ShouldEnableMultiplayerFlagUi() ? "enabled" : "disabled");
        EnsureBansConfigLoaded();
        {
            const std::string bansConfigPath = GetBansConfigPath().string();
            Log(L"[BAN] Ban list path=%hs entries=%u\n",
                bansConfigPath.c_str(),
                static_cast<unsigned>(g_BanRecords.size()));
        }
    }

    void RetryDeferredRuntimeHooks()
    {
        // Called from the patch thread's settle loop and from SDK bridges on
        // the game thread. The installers below latch on plain bools, so two
        // callers used to be able to pass one latch together; under the lock
        // the second caller finds the first one's work done.
        HookEngine::CodePatchLock lock;
        InstallPondClassLabelSupportIfPossible();
        InstallEnhancedLightSelectionIfPossible();
        InstallShadowFarOverrideIfPossible();
        InstallJumpSnipingProbeIfRequested();
        InstallUnitTurboHooksIfPossible();
        InstallCareerStatsMpHookIfPossible();
        InstallUnitVoQueueHooksIfPossible();
        InstallParticleTemplateDedupeHookIfPossible();
        InstallOgreScriptImportCacheIfPossible();
        InstallResourceWalkStatCacheIfPossible();
        InstallUiManualObjectDedupeHookIfPossible();
        InstallEmissionLightFixIfPossible();
        VerifyExpectedOgreExportsIfPossible();
        InstallSceneTeardownForgetHooksIfPossible();
        InstallEntityReloadLifetimeHookIfPossible();
        InstallEntityFrustumCullingIfEnabled();
        InstallMissionTransitionSeamIfPossible();
        PinDirect3DModulesForShutdown();
        InstallMultiplayerFlagRenderHookIfPossible();
        InstallNicknameTextEntryInputHookIfPossible();
        InstallMultiCreatePreviewFixIfPossible();
        InstallShieldTowerTeamFilterHookIfPossible();
        InstallMineTeamFilterHooksIfPossible();
        InstallProducerScriptPredicateHooksIfPossible();
		InstallBriefingScrollFixIfPossible();
		InstallThumbnailBmpGuardIfPossible();
		InstallSplinterUndeadFixIfPossible();
		InstallTugCargoPostLoadFixIfPossible();
		InstallConstructorRecycleStaleTargetFixIfPossible();
		InstallApcAlliedTargetDeployFixIfPossible();
		InstallQuakeReplayFadeIfPossible();
		InstallTargetCamSatelliteFixIfPossible();
		InstallCinematicSatelliteZoomFixIfPossible();
		InstallUnfocusedMouseReleaseIfPossible();
        InstallAiTuningHooksIfPossible();
        InstallConstructorRemoteBuildFixIfPossible();
        EnsureInputBindingPopulateHookScaffold();
        EnsureOptionsParentCtorHookScaffold();
        EnsureNativeUiMainMenuDiagnosticScaffold();
    }

    bool AreRequiredDeferredRuntimeHooksInstalled()
    {
        const bool splinterReady =
            !g_SplinterUndeadFixEnabled || g_SprayBuildingSimulateHookInstalled;
        const bool constructorReady =
            !g_ConstructorRemoteBuildFixEnabled || g_ConstructorRemoteBuildFixInstalled;
        return splinterReady && constructorReady &&
            IsPondClassLabelSupportInstalled();
    }

    void InitBzrHookStrings()
    {
        BzrStringInitEmpty(&g_BzrnetLabel1);
        BzrStringInitEmpty(&g_BzrnetLabel2);
        BzrStringInitEmpty(&g_BzrnetLabel3);
        BzrStringInitEmpty(&g_BzrnetLabel4);
    }

    void __fastcall LegacyWorldUpdateRenderQueueHook(void* thisPtr, void* /*edx*/, void* renderQueue)
    {
        // Keep one owner per camera/material traversal. Flame callbacks can
        // precede this Ogre traversal, so call-stack nesting alone does not
        // exclude duplicate submissions. A recent observed world callback
        // proves this driver is live; the flame fallback resumes if it stalls.
        ObserveChunkWorldQueueDriver();
        if (g_BzrFn_LegacyWorldUpdateRenderQueue && thisPtr)
        {
            if (!RunLegacyWorldQueueWithDynamicGeometryCounters(thisPtr, renderQueue))
                g_BzrFn_LegacyWorldUpdateRenderQueue(thisPtr, renderQueue);
        }

        // This Ogre callback is continuous while a world is rendered; unlike
        // ChunkEffect::Simulate it does not depend on active debris/effects.
        // RefreshHeadlightState is internally throttled to one object scan per
        // 200 ms and also owns the live SP/MP + EXU authority gate.
        RefreshHeadlightState();

        // Same cadence and the same gate: the pilot flashlight is created and
        // destroyed here because this is the only callback guaranteed to run
        // while a world is rendered, on or off foot.
        RefreshPilotFlashlightState();

        // Uses the existing SP gate; no allocation/work until a qualified
        // presentation backend is registered. Never advance simulation here.
        RefreshWeaponPresentationState();
        GeometryContactTest::Tick();

        // Same driver again, and for the same reason: the packed team has to be
        // repaired while the player is still on foot, because the value is read
        // during the boarding call itself. Two field reads per frame when the
        // feature is on, and an immediate return when it is off.
        RefreshPilotTeamRestoreState();

        // For the same reason, this is the primary driver of the multiplayer
        // gate: every SinglePlayer-tier feature is reconciled here rather than
        // waiting on the first chunk effect of the match. Internally throttled.
        TickMpGateReconcile();

        // The native event layer's known-safe dispatch point. Producers queue
        // from arbitrary engine hook contexts; this is the only place sinks
        // ever run. See include/openshim_events.h.
        TickOpenShimEventLayer();

        // Sample after the stock world queue update, when Ogre has evaluated
        // the entity materials and its hardware-animation decision is current.
        RefreshVehicleSkinningDiagnosticsIfNeeded();

        // Repairs the multiplayer Create Game vehicle preview, which renders
        // black on DX11 because its viewport keeps Ogre's default scheme and
        // falls back to a PSSM technique that reads NaN shadow matrices.
        MpVehiclePreviewFixTick();

        static volatile long s_FiredLogBudget = 4;
        if (InterlockedDecrement(&s_FiredLogBudget) >= 0)
        {
            LogChunkDiagnostic(
                "chunkmesh",
                L"[CHUNKMESH] world-rq-hook fired this=0x%08X queue=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(renderQueue)));
        }

        TickChunkProxyDebug(nullptr, false);
        SubmitChunkProxiesToRenderQueue(renderQueue);
        // Independent of ChunkMeshes: gibs have their own pool and gate.
        SubmitSkinnedGibsToRenderQueue(renderQueue);
        SubmitShellCasingsToRenderQueue(renderQueue);

        // Opt-in Phase 3A parity capture. Inert unless a semantic frame
        // capture count is configured.
        TerrainProxyRenderFrameTick();

        // This runs once per camera. The fog wake runtime steps a fixed cadence
        // off a monotonic clock, so the extra calls cost a clock read rather
        // than extra simulation.
        FogWakeRenderFrameTick();
    }

    void __fastcall ChunkEffectSimulateHook(void* thisPtr, void* /*edx*/, float dt)
    {
        if (!g_BzrFn_ChunkEffectSimulate || !thisPtr)
            return;

        if (!g_JumpSnipeProbeInstalled)
            InstallJumpSnipingProbeIfRequested();
        // Secondary driver for the multiplayer guard, kept so the gate still
        // reconciles if the Ogre world-queue hook (the primary driver, see
        // LegacyWorldUpdateRenderQueueHook) failed to install. Shares
        // TickMpGateReconcile's throttle, so this is not duplicate work.
        TickMpGateReconcile();
        // Multiplayer vehicle flags: render from the sim tick whenever the
        // engine is not dispatching the hooked FlagDisplay::Submit slot.
        MaybeDriveMultiplayerFlagRenderFallback();
        OgreShaderCacheTick();
        MaybeLogDx11EnhancedLightingState();
        if (BZROpenShim::UiPerf::IsEnabled())
            BZROpenShim::UiPerf::Heartbeat("SimTick");
        if (!g_CareerStatsMpHookInstalled)
            InstallCareerStatsMpHookIfPossible();
        if (ShouldTracePlayerKills() && !g_DistributedRecordDeathIntHookInstalled)
            InstallDistributedRecordDeathIntHookIfPossible();
        if (g_MpauthEnabled && !g_MpauthHooksInstalled)
            InstallMpauthHooksIfPossible();
        if (!g_RadarLayoutHookInstalled)
            InstallRadarLayoutHookIfPossible();
        if (!g_ChunkEffectCreateHooksInstalled)
            InstallChunkEffectCreateHooksIfRequested();
        if (!g_ChunkEffectFragmentHooksInstalled)
            InstallChunkFragmentWalkHooksIfRequested();

        MaybeSuppressStaleHopOutAttackAlert();
        SyncSatelliteVisibility();
        LogSatelliteVisibilityValidationSample();
        MaybeLogSatelliteVisibilitySample();
        RefreshChunkObjectIdentityCacheIfNeeded();
        TrackChunkEffectActiveEntries(thisPtr);
        // Keep proxy lifecycle (expiry, transform mirroring) ticking from the
        // simulate hook so it survives even when the render hooks are not
        // running, but never manual-submit from sim time: the render queue is
        // rebuilt each frame, so submissions here would be discarded — or worse,
        // outlive a released slot. Render-time submission happens in
        // LegacyWorldUpdateRenderQueueHook, invoked by Ogre with the live
        // render queue every rendered frame.
        TickChunkProxyDebug(nullptr, false);
        LogChunkEffectRuntimeSample(thisPtr, dt);
        if (IsOgreAnimationProfilerCollecting())
        {
            uint32_t activeChunks = 0;
            TryReadChunkEffectCount(
                reinterpret_cast<const uint8_t*>(thisPtr),
                activeChunks);
            LARGE_INTEGER start{};
            LARGE_INTEGER end{};
            QueryPerformanceCounter(&start);
            g_BzrFn_ChunkEffectSimulate(thisPtr, dt);
            QueryPerformanceCounter(&end);
            RecordNativeChunkSimulationSample(
                activeChunks,
                static_cast<uint64_t>(end.QuadPart - start.QuadPart));
        }
        else
        {
            g_BzrFn_ChunkEffectSimulate(thisPtr, dt);
        }
        // Chunks the stock simulate just retired give their memory back to
        // the object pool; drop their proxies before anything can reuse it.
        ReleaseChunkProxiesMissingFromActiveList(thisPtr);
        // Shim-owned person gibs: integrated on the engine's own dt, after the
        // stock simulate (the only engine time source). No-op when disabled.
        TickSkinnedGibs(thisPtr, dt);
        // Shim-owned shell casings, same clock. No-op when disabled.
        TickShellCasings(dt);
    }

}
