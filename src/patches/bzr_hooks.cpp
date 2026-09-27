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

    uint8_t g_MapFilterFlag11 = 0;
    uint8_t g_MapFilterFlag12 = 0;

    void* g_BzrFn_MapFilter8Check = nullptr;
    void* g_BzrFn_MapFilterCreate = nullptr;
    void* g_MapFilterListPtr = nullptr;
    const char* (__cdecl* g_BzrFn_Localize)(const char* section, const char* key) = nullptr;

    void* g_BzrFn_VehicleFixPre = nullptr;
    void* g_BzrFn_VehicleFixOrig = nullptr;

    BzrString g_BzrnetLabel1 = {};
    BzrString g_BzrnetLabel2 = {};
    BzrString g_BzrnetLabel3 = {};
    BzrString g_BzrnetLabel4 = {};



    using FnAutoLoadShellGame = int(__cdecl*)();
    using FnLoadGameByPath = int(__cdecl*)(const char* path, char* outName, int outNameLen);
    using FnFinalizeQueuedLoad = void(__cdecl*)();
    using FnMapFilter6 = uint32_t(__thiscall*)(void* thisPtr);
    using FnMapFilterScroll = void(__thiscall*)(void* self);
    using FnGameObjectGetTeam = int(__thiscall*)(void* thisPtr);
    using FnChunkEffectSimulate = void(__thiscall*)(void* self, float dt);
    // Redux's ArtilleryProcess::DoAttack is not the zero-stack-argument method
    // described by the legacy 1.5 PDB. At the machine ABI it consumes four
    // stack words (the first is the hidden/result destination) and returns with
    // `ret 0x10`. Preserve all four words when replaying the stock routine.
    using FnArtilleryDoAttack = uint32_t(__thiscall*)(void* thisPtr,
                                                      uint32_t arg0,
                                                      uint32_t arg1,
                                                      uint32_t arg2,
                                                      uint32_t arg3);

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
    static FnMapFilter6 g_BzrFn_MapFilter6 = nullptr; // 0x004200B0
    FnChunkResolve g_BzrFn_ChunkResolve = nullptr; // 0x004E3620
    static FnMapFilterScroll g_BzrFn_MapFilterScrollUp = nullptr; // 0x007CB500
    static FnMapFilterScroll g_BzrFn_MapFilterScrollDown = nullptr; // 0x007CB540
    FnGetLocalPlayerNetId g_BzrFn_GetLocalPlayerNetId = nullptr;
    FnNetPlayerSetData g_BzrFn_NetPlayerSetData = nullptr;
    FnNetPlayerSetFlagBuffer g_BzrFn_NetPlayerSetFlagBuffer = nullptr;
    FnSetMyFlag g_BzrFn_SetMyFlag = nullptr;
    FnBuildItemInit g_BzrFn_InitBuildItem = nullptr; // 0x0049F5C0
    FnBuildItemCleanup g_BzrFn_CleanupBuildItem = nullptr; // 0x0049F880
    FnProducerModeCall g_BzrFn_ProducerModeCallOriginal = nullptr;
    FnEngineFlameAddFlame g_BzrFn_EngineFlameAddFlame = nullptr;
    FnEngineFlameControl g_BzrFn_EngineFlameControl = nullptr;
    FnEngineFlameSubmit g_BzrFn_EngineFlameSubmit = nullptr;
    FnEngineFlameResolveTexture g_BzrFn_EngineFlameResolveTexture = nullptr;
    FnHudSpriteLookup g_BzrFn_HudSpriteLookup = nullptr;
    FnGetTeamNum g_BzrFn_GetTeamNum = nullptr;
    static FnChunkEffectSimulate g_BzrFn_ChunkEffectSimulate = nullptr;
    FnLegacyWorldUpdateRenderQueue g_BzrFn_LegacyWorldUpdateRenderQueue = nullptr;
    FnGetPlayerHandle g_BzrFn_GetPlayerHandle = nullptr;
    FnGameObjectGetObjByHandle g_BzrFn_GameObjectGetObjByHandle = nullptr;
    static volatile long g_StaleGameObjectHandleLogBudget = 16;
    // GameObject::GetHandle, resolved by ResolveBzrHooks from scripts/patches.json
    // ("GameObject::GetHandle"); 0 until then, and every caller stands down on 0.
    uintptr_t g_GameObjectGetHandleAddr = 0;


    // Correct GOG handle->object conversion. The engine's GameObject pool is a
    // fixed 0x1000-slot table (patches.json "GameObject::Arena", 0x0260DB20 on
    // GOG) with a 0x400-byte stride; a
    // handle's slot index is its top 12 bits (handle >> 0x14). Verified live: a
    // craft pointer satisfies (ptr - 0x0260DB20) == slot * 0x400 exactly. The
    // former binding (kGogGameObjectGetObjByHandleAddr = 0x0046B160) actually
    // pointed into an unrelated ODF class-dispatch routine, so every call
    // crashed (deterministic null+0x19 fault via the scavenger retarget hook,
    // 2026-07-14). Round-trips through GetHandle (0x00462380) to reject stale or
    // empty slots; the pool memory is always mapped so the probe read is safe.
    void* __cdecl GameObjectFromHandleGog(int handle)
    {
        if (handle == 0)
            return nullptr;
        const uintptr_t arena = EngineGlobals::GameObjectArena();
        if (arena == 0)
            return nullptr;
        const uint32_t slot = (static_cast<uint32_t>(handle) >> 0x14) & 0xFFFu;
        void* obj = reinterpret_cast<void*>(
            static_cast<uintptr_t>(slot) * 0x400u + arena);
        using GetHandleThiscallFn = uint32_t(__thiscall*)(void*);
        if (g_GameObjectGetHandleAddr == 0)
            return nullptr;
        __try
        {
            if (reinterpret_cast<GetHandleThiscallFn>(g_GameObjectGetHandleAddr)(obj) ==
                static_cast<uint32_t>(handle))
                return obj;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
        return nullptr;
    }

    void* __cdecl GameObjectHandleGetObjHardened(int handle)
    {
        // GameObject::GetObj validates the low 20-bit generation against the
        // selected pool slot, but generation zero is also the empty-slot value.
        // A stale handle whose generation bits are zero therefore passes the
        // stock check and returns a completely empty GameObject slot. The stock
        // GameObjectHandle::GetObj wrapper immediately dereferences +0xF4 on
        // that slot to test the dead bit and crashes.
        //
        // battlezone98redux.exe.16444.dmp captured this in PathSpawn::Execute
        // owned by Inst4XMission. Redux reconstructs PathSpawn through a load
        // constructor that initializes only its AiProcess base, allowing cached
        // derived-state handles to be stale. Handle 0xBF800000 selected slot
        // 0xBF8, whose generation and object pointer were both zero.
        // Round-tripping through GetHandle rejects that slot because an empty
        // object returns handle 0.
        void* object = GameObjectFromHandleGog(handle);
        if (!object)
        {
            if (handle != 0 &&
                InterlockedDecrement(&g_StaleGameObjectHandleLogBudget) >= 0)
            {
                Log(L"[SAVELOAD] Rejected stale GameObject handle=0x%08X before object-state access\n",
                    static_cast<uint32_t>(handle));
            }
            return nullptr;
        }

        void* objectState = nullptr;
        uint32_t flags = 0;
        __try
        {
            objectState = *reinterpret_cast<void**>(
                reinterpret_cast<uint8_t*>(object) + 0xF4u);
            if (objectState)
            {
                flags = *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint8_t*>(objectState) + 0x14u);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            objectState = nullptr;
        }

        if (!objectState)
        {
            if (InterlockedDecrement(&g_StaleGameObjectHandleLogBudget) >= 0)
            {
                Log(L"[SAVELOAD] Rejected incomplete GameObject handle=0x%08X object=%p\n",
                    static_cast<uint32_t>(handle), object);
            }
            return nullptr;
        }

        return (flags & 0x200u) == 0 ? object : nullptr;
    }

    FnPersonSimulate g_BzrFn_PersonSimulate = nullptr;

    std::unordered_set<uintptr_t> g_PilotCarrierNullLoggedObjects = {};
    volatile long g_NeutralAttackOrderLogBudget = 16;
    volatile long g_AipResolveTraceBudget = 512;
    volatile long g_AipPrereqCensusEmitted = 0;

    std::vector<AiExtraMakerPair> g_AiExtraMakerPairs = {};
    volatile long g_AiMultiProducerMakerLogBudget = 64;
    FnShieldTowerSimulate g_BzrFn_ShieldTowerSimulateOriginal = nullptr;
    FnShieldTowerSimulate g_BzrFn_BuildingSimulate = nullptr;
    FnMagnetMineSimulate g_BzrFn_MagnetMineSimulateOriginal = nullptr;
    FnProximityMineSimulate g_BzrFn_ProximityMineSimulateOriginal = nullptr;
    FnProximityMineSimulate g_BzrFn_MineSimulate = nullptr;
	FnSprayBuildingSimulate g_BzrFn_SprayBuildingSimulateOriginal = nullptr;
    FnGameObjectClassBuild g_BzrFn_SprayEmitterBuildOriginal = nullptr;
    FnShieldTowerPowerUpdate g_BzrFn_ShieldTowerPowerUpdate = nullptr;
    // Resolved by ResolveBzrHooks from scripts/patches.json
    // ("GameObject::FromObj76"); null until then, and every caller checks.
    FnResolveObj76GameObject g_BzrFn_ResolveObj76GameObject = nullptr;
    FnGameObjectRelation g_BzrFn_GameObjectFriendP = nullptr;
    FnGameObjectRelation g_BzrFn_GameObjectEnemyP = nullptr;
    FnMatrixInverse g_BzrFn_MatrixInverse = nullptr;
    FnVectorTransform g_BzrFn_VectorTransform = nullptr;
    FnRangeSearch g_BzrFn_CollisionRangeSearch = nullptr;
    FnRangeResultsGetNext g_BzrFn_RangeResultsGetNext = nullptr;
    FnKeyConfigSetKey g_BzrFn_KeyConfigSetKey = nullptr;
    static FnWriteInputMapKey g_BzrFn_WriteInputMapKey = nullptr;
    FnMapKeyNameFromCode g_BzrFn_MapKeyNameFromCode = nullptr;
    FnReloadGameKeyMap g_BzrFn_ReloadGameKeyMap = nullptr;
    FnRecordDeath g_BzrFn_RecordDeath = nullptr;
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
    FnAIUnitRemove g_BzrFn_AIUnitRemove = nullptr;
    FnAIBuildConstructionEnd g_BzrFn_AIBuildConstructionEnd = nullptr;
    FnAIBuildReservedAreaRemove g_BzrFn_AIBuildReservedAreaRemove = nullptr;
    FnAISpentCreditRefund g_BzrFn_AISpentCreditRefund = nullptr;
    FnUnitsSOrderStop g_BzrFn_UnitsSOrderStop = nullptr;
    FnAIBuildUnassignedCCAdd g_BzrFn_AIBuildUnassignedCCAdd = nullptr;
    FnChunkEffectCreateChunk g_BzrFn_ChunkEffectCreateChunk = nullptr;
    FnChunkEffectCreateChunklet g_BzrFn_ChunkEffectCreateChunklet = nullptr;
    FnChunkEffectFragmentObject g_BzrFn_ChunkEffectPartialFragment = nullptr;
    FnChunkEffectFragmentObject g_BzrFn_ChunkEffectFullFragment = nullptr;
    BuildItem* g_BzrBuildMenuRoot = nullptr;
    bool g_IsSteamExe = false;



    // Formerly an anonymous namespace. A named one plus the using-directive
    // after its closing brace keeps every lookup identical, and lets the
    // translation units split out of this file (declared in
    // bzr_hooks_internal.h) share what they need. Anything meant to stay
    // file-local is `static`.
    namespace Hooks
    {

        constexpr uintptr_t kBuildMenuRootAddr = 0x009174C4;
        static_assert(
            kGameObjectDistributedObjectOffset == kGameObjectClassSubObjOffset,
            "GameObject +0x18 interface aliases diverged");
        constexpr size_t kHudSpriteRectEntrySize = 0x24;
        constexpr size_t kObj76GameObjectOffset = 0x8C;
        static_assert(kGameObjectObjOffset == ObjectLayout::kGameObjectObj76,
                      "obj76 offset disagrees with bzr_object_layout.h");
        static_assert(kObj76GameObjectOffset == ObjectLayout::kObj76GameObject,
                      "obj76 back-pointer disagrees with bzr_object_layout.h");
        constexpr size_t kMagnetMineSoundHandleOffset = 0x230;
        constexpr uintptr_t kGogDayWreckerCtorAddr = 0x004B0420;
        constexpr uintptr_t kDayWreckerSimulateVtableSlotAddr = 0x00878544;
        constexpr uintptr_t kDayWreckerExplodeVtableSlotAddr = 0x00878588;
        constexpr uintptr_t kGogDayWreckerRemoveBookkeepingAddr = 0x004B7AB0;
        constexpr uintptr_t kGogDayWreckerDeletedIdAddr = 0x004B7BD0;
        constexpr uintptr_t kGogDistributedDtorAddr = 0x004B79F0;
        constexpr uintptr_t kGogDistributedCreateAddr = 0x004B9350;
        constexpr uintptr_t kGogOrdnanceBundledDispatchAddr = 0x00570500;
        constexpr uintptr_t kGogOrdnanceRemoveCheckAddr = 0x00583DC0;
		constexpr uint32_t kCraftDeployStateUndeployed = 0;
		constexpr long kQuakeReplayFadeSecondsDefault = 5;
		constexpr long kQuakeReplayFadeSecondsMin = 1;
		constexpr long kQuakeReplayFadeSecondsMax = 60;
        constexpr long kSplinterUndeadTraceBudgetDefault = 32;
        // Redux's FlagDisplay inherits a 0x28-byte GameFeature base. The old
        // BZ1 layout used +0x10/+0x14; writing those offsets in Redux corrupts
        // the base object. Redux's surviving fields are at +0x28/+0x2C.
        constexpr size_t kFlagDisplayFlagIndexOffset = 0x28;
        constexpr size_t kMultiplayerFlagMaxObjects = 512;
        constexpr uintptr_t kLocalPlayerNetIdAddr = 0x009180D4;
        // Returned when the net id cannot be read at all. Every SinglePlayer-tier
        // gate is written as "net id == 0", so a sentinel that is not 0 makes an
        // unreadable net id stand the feature down instead of enabling it. This
        // matches AutoSave, whose gate already treats an unreadable state as "not
        // a live single-player mission" (autosave.cpp IsSinglePlayerMissionActive).
        constexpr uint16_t kLocalPlayerNetIdUnreadable = 0xFFFFu;

        // The convergence tuning constants (minimum target distance, maximum
        // deviation from the stock aim) live alongside the math in
        // include/weapon_convergence.h.




        constexpr ULONGLONG kSteamChunkCreateHookSettleDelayMs = 15000;
        constexpr uintptr_t kGogAIBuildConstructionEndAddr = 0x006905D0;
        constexpr uintptr_t kGogAIBuildReservedAreaRemoveAddr = 0x00690920;
        constexpr uintptr_t kGogAISpentCreditRefundAddr = 0x00690020;
        constexpr uintptr_t kGogUnitsSOrderStopAddr = 0x00416280;
        constexpr uintptr_t kGogAIBuildUnassignedCCAddAddr = 0x00690770;
        constexpr uintptr_t kGogKeyConfigSetKeyAddr = 0x0081C440;
        constexpr uintptr_t kGogWriteInputMapKeyAddr = 0x0061F1C0;
        constexpr uintptr_t kGogMapKeyNameFromCodeAddr = 0x00434F60;
        constexpr uintptr_t kGogReloadGameKeyMapAddr = 0x00620980;
        constexpr uintptr_t kGogUiOverlayCtorAddr = 0x007D1CC0;
        constexpr long kConstructorRemoteBuildTraceBudgetDefault = 32;












        static_assert(sizeof(HudSpriteRectRecord) == kHudSpriteRectEntrySize, "Unexpected HUD sprite rect record size");

        static bool g_JumpSnipeProbeInstallAttempted = false;
        bool g_JumpSnipeProbeInstalled = false;
        JumpSnipeProbeLogState g_JumpSnipeProbeLogState = {};
        HudSpriteRectRecord* g_HudSpriteRectTableBase = nullptr;
        bool g_HudSpriteRectTableDiscoveryAttempted = false;
        ULONGLONG g_HudSpriteRectTableDiscoveryLastTick = 0;
        std::unordered_map<int, HudSpriteRectRecord> g_HudSpriteOriginalEntries;
        std::unordered_map<int, HudSpriteRectRecord> g_HudSpriteHiddenEntries;
        std::unordered_map<uintptr_t, HudSpriteRectRecord> g_HudSpriteOriginalEntriesByAddress;
        std::unordered_set<uintptr_t> g_HudSpriteHiddenAddresses;
        std::vector<uintptr_t> g_HudSpriteCachedPanelAddresses;
        bool g_HudSpriteFallbackDiscoveryAttempted = false;
        ULONGLONG g_HudSpriteFallbackDiscoveryLastTick = 0;
        // Full-memory scans cost seconds on the UI thread, so failed attempts
        // back off exponentially (reset on success or mission-state reset).
        ULONGLONG g_HudSpriteRectTableDiscoveryBackoffMs = 0;
        ULONGLONG g_HudSpriteFallbackDiscoveryBackoffMs = 0;


















        std::vector<BanRecord> g_BanRecords;













        bool g_EnableChunkRenderFallback = false;
        bool g_EnableChunkProxyDebug = false;
        bool g_EnableChunkMeshProxy = false;
        bool g_EnableGenericChunkBatch = false;
        bool g_EnablePartialFragmentBoneCollapse = false;
        bool g_TraceChunkRender = false;
        bool g_TraceChunkRenderVerbose = false;
        bool g_TraceChunkEffectRuntime = false;
        bool g_TraceSatelliteVisibility = false;
        uint32_t g_LastChunkEffectLoggedCount = UINT32_MAX;
        static volatile long g_ChunkRenderLogBudget = 12;
        // 8 was sized for an opt-in probe and burns out after 8 seconds of
        // cumulative satellite viewing -- far too few to walk the validation
        // matrix now that the trace defaults on. Budget is consumed only while
        // the overview is actually open and is rate-limited to one sample per
        // g_SatelliteVisibilityLogIntervalMs.
        volatile long g_SatelliteVisibilityLogBudget = 120;
        uint32_t g_ChunkTraceEntryLimit = 32;
        // 96 slots exhaust in multi-craft battles (each death emits ~10 geo
        // pieces plus impact chunklets); once full, new chunks are silently
        // dropped until a slot expires.
        uint32_t g_ChunkProxyCapacity = 256;
        float g_ChunkProxyDebugSize = 2.5f;
        uint32_t g_SatelliteVisibilityObjectLimit = 96;
        DWORD g_SatelliteVisibilityLastTick = 0;
        DWORD g_SatelliteVisibilityLogIntervalMs = 1000;
        std::unordered_map<uintptr_t, uint32_t> g_ChunkObservedClassIds = {};




        std::unordered_map<uintptr_t, ChunkResolvedBindingEntry> g_ChunkResolvedBindingCache = {};
        std::unordered_map<std::string, bool> g_ChunkPayloadMeshExistsCache = {};
        std::unordered_set<std::string> g_ChunkPayloadResolveFailureLogCache = {};
        DWORD g_ChunkResolvedBindingLastPruneTick = 0;
        bool g_VehicleSkinningTraceEnabled = false;
        DWORD g_VehicleSkinningTraceIntervalMs = 5000;
        DWORD g_VehicleSkinningTraceLastTick = 0;
        volatile long g_VehicleSkinningTraceBudget = 64;
        std::unordered_set<std::string> g_VehicleSkinningTraceFingerprints = {};

        ProducerBuildMenuConfig g_ProducerBuildMenuConfig = {};
        AiTuningCache g_AiTuningCache = {};
        TeamFilterCache g_ShieldTowerTeamFilterCache = {};
        TeamFilterCache g_MagnetMineTeamFilterCache = {};
        TeamFilterCache g_ProximityMineTeamFilterCache = {};
        bool g_HasAppliedProducerBuildMenu = false;
        int64_t g_LastAppliedProducerBuildMenu = 0;
        uint32_t g_LastUnknownProducerVft = 0;
        bool g_LoggedEngineFlameTargetFailure = false;
        bool g_LoggedEngineFlameVtableHook = false;
        bool g_EngineFlameVariantsInitialized = false;
        bool g_EngineFlameVariantsInitAttempted = false;
        bool g_EngineFlameVtableHooksInstalled = false;
        InlineDetour32 g_RecordDeathDetour = {};
        bool g_DistributedRecordDeathIntHookInstalled = false;
        bool g_LobbyNicknameInputHookInstalled = false;
        void* g_ActiveNicknameEntry = nullptr;
        void* g_ActiveNicknameParent = nullptr;
        void* g_NicknameEnterDispatchEntry = nullptr;
        void* g_PendingNicknameConfirmationEntry = nullptr;
        BzrNetNicknameResult g_PendingNicknameConfirmationResult =
            BzrNetNicknameResult::StoredForNextConnection;
        bool g_ReplaceNicknameOnNextInput = false;
        bool g_CareerStatsMpHookInstalled = false;
        bool g_CareerStatsMpHookInstallAttempted = false;
        bool g_CareerStatsMpHookMismatchLogged = false;
        ULONGLONG g_CareerStatsMpHookFirstAttemptTick = 0;
        ULONGLONG g_CareerStatsMpHookLastAttemptTick = 0;
        bool g_CalcRangeCraftHookInstalled = false;
        bool g_ScrapPathScoreHookInstalled = false;
        InlineDetour32 g_RecycleTaskDoGotoScrapDetour = {};
        bool g_ScrapRetargetHookInstalled = false;
        InlineDetour32 g_AttackTaskDoStateDetour = {};
        bool g_AttackTaskDoStateHookInstalled = false;
        static InlineDetour32 g_ArtilleryDoAttackDetour = {};
        static FnArtilleryDoAttack g_BzrFn_ArtilleryDoAttackOriginal = nullptr;
        static bool g_ArtilleryDoAttackHookInstalled = false;
        bool g_RetargetPeriodHooksInstalled = false;
        volatile long g_AttackRevealTraceBudget = 64;
        InlineDetour32 g_ChunkEffectCreateChunkDetour = {};
        InlineDetour32 g_ChunkEffectCreateChunkletDetour = {};
        bool g_ChunkEffectCreateHooksInstalled = false;
        bool g_ChunkEffectCreateHooksLogged = false;
        InlineDetour32 g_ChunkEffectPartialFragmentDetour = {};
        InlineDetour32 g_ChunkEffectFullFragmentDetour = {};
        bool g_ChunkEffectFragmentHooksInstalled = false;
        bool g_AllowUnsafeSteamChunkCreateHooks = false;
        bool g_ChunkEffectCreateHooksWaitLogged = false;
        bool g_ChunkEffectCreateHooksMismatchLogged = false;
        ULONGLONG g_ChunkEffectCreateHooksReadyTick = 0;
        bool g_ShieldTowerSimulateHookInstalled = false;
        bool g_ConstructorRemoteBuildFixInstalled = false;
        bool g_ConstructorRemoteBuildFixMismatchLogged = false;
        bool g_MagnetMineSimulateHookInstalled = false;
        bool g_ProximityMineSimulateHookInstalled = false;
        InlineDetour32 g_ScriptCanBuildDetour = {};
        InlineDetour32 g_ScriptIsBusyDetour = {};
        FnScriptProducerPredicate g_BzrFn_ScriptCanBuildOriginal = nullptr;
        FnScriptProducerPredicate g_BzrFn_ScriptIsBusyOriginal = nullptr;
        bool g_ProducerScriptPredicateHooksInstalled = false;
        // [Fixes] ProducerScriptPredicates. Extends the script-facing CanBuild /
        // IsBusy predicates to base producers. Default on; switchable because it
        // changes what mission Lua observes, in single-player and multiplayer
        // alike, and it had no opt-out at all before.
        bool g_ProducerScriptPredicateHooksEnabled = true;
        bool g_BriefingScrollFixInstalled = false;
        bool g_BriefingScrollFixEnabled = true;
        bool g_MultiRenderCountClampInstalled = false;
        bool g_MultiRenderCountClampEnabled = true;
        volatile long g_MultiRenderCountClampLogBudget = 8;
        bool g_MagnetZeroRangeGuardEnabled = true;
        volatile long g_MagnetZeroRangeLogBudget = 8;
        bool g_ThumbnailBmpGuardEnabled = true;
        bool g_ThumbnailBmpGuardInstalled = false;
        bool g_QuakeReplayFadeInstalled = false;
        bool g_QuakeReplayFadeEnabled = true;
        long g_QuakeReplayFadeSeconds = kQuakeReplayFadeSecondsDefault;
        InlineDetour32 g_EarthQuakeSimulateDetour = {};
        volatile long g_QuakeReplayArmed = 0;
        bool g_TargetCamSatelliteFixInstalled = false;
        bool g_TargetCamSatelliteFixEnabled = true;
        volatile long g_TargetCamSatelliteLogBudget = 8;
        bool g_CinematicSatelliteZoomFixInstalled = false;
        bool g_CinematicSatelliteZoomFixEnabled = true;
        volatile long g_CinematicSatelliteZoomLogBudget = 8;
		bool g_SprayBuildingSimulateHookInstalled = false;
		bool g_TugCargoPostLoadFixInstalled = false;
		bool g_TugCargoPostLoadFixEnabled = true;
		volatile long g_TugCargoPostLoadLogBudget = 16;
		bool g_ApcAlliedTargetDeployFixInstalled = false;
		bool g_ApcAlliedTargetDeployFixEnabled = true;
		bool g_ConstructorRecycleStaleTargetFixInstalled = false;
		bool g_ConstructorRecycleStaleTargetFixEnabled = true;
		bool g_ConstructorRecycleStaleTargetMismatchLogged = false;
		volatile long g_ConstructorRecycleStaleTargetLogBudget = 16;
        bool g_SplinterUndeadFixEnabled = kSplinterUndeadFixEnabledDefault;
        volatile long g_SplinterUndeadTraceBudget = kSplinterUndeadTraceBudgetDefault;
        bool g_ConstructorRemoteBuildFixEnabled = kConstructorRemoteBuildFixEnabledDefault;
        volatile long g_ConstructorRemoteBuildTraceBudget = kConstructorRemoteBuildTraceBudgetDefault;

        // MPAUTH diagnostic traces (Redux receiver replay). Opt-in, cheap, no gameplay change.
        bool g_MpauthEnabled = false;
        bool g_MpauthHooksInstalled = false;
        volatile long g_MpauthInstallRetryBudget = 8;
        thread_local bool g_MpauthInOrdnanceReceive = false;
        std::unordered_map<uint32_t, int> g_MpauthSplHitCounts = {};

        std::unordered_map<uintptr_t, RetargetPeriodState> g_RetargetPeriodStateByProcess = {};
        std::unordered_map<uintptr_t, ScrapPathFailureState> g_ScrapPathFailuresByObject = {};
        std::unordered_map<uintptr_t, ScrapRetargetState> g_ScrapRetargetStateByTask = {};
        std::unordered_map<uintptr_t, AiUnitTuningOverride> g_AiUnitTuningOverridesByObject = {};
        std::unordered_map<uintptr_t, CombatKiteState> g_CombatKiteStateByObject = {};
        volatile long g_AiUnitTuningTraceBudget = 64;
        volatile long g_CombatKiteTraceBudget = 256;
        volatile long g_ScrapPathTraceBudget = 128;

        int g_EngineFlamePrimaryRedTexture = 0;
        int g_EngineFlamePrimaryBlueTexture = 0;
        int g_EngineFlamePrimaryGreenTexture = 0;
        int g_EngineFlamePrimaryOrangeTexture = 0;
        int g_EngineFlamePrimaryBlackDogTexture = 0;
        void* g_EngineFlamePrimaryManager = nullptr;
        void* g_EngineFlameSecondaryManager = nullptr;

        bool g_JetFlamesConfigInitialized = false;
        static constexpr uintptr_t kChunkEffectVtableSimulateSlotAddr = 0x0087708C;
        static constexpr DWORD kVehicleSkinningTraceIntervalMsDefault = 5000;
        static constexpr DWORD kVehicleSkinningTraceIntervalMsMin = 100;
        static constexpr DWORD kVehicleSkinningTraceIntervalMsMax = 60000;
        static constexpr long kVehicleSkinningTraceBudgetDefault = 64;
        static constexpr const char* kChunkProxyBillboardSetName = "OpenShimChunkProxyDebug";
        static constexpr const char* kChunkProxyMaterialName = "BaseWhiteNoLighting";
        static constexpr const char* kChunkProxyMaterialGroup = "General";
        // Resolved by ResolveBzrHooks from scripts/patches.json
        // ("PlayGlobalSound"); null until then, and the caller checks.
        FnPlayGlobalSound g_BzrFn_PlayGlobalSound = nullptr;
        static constexpr bool kHowitzerVolleyEnabledDefault = false;
        // Confirmed Redux defect: damage from a GameObject-owned child reveals
        // only that immediate child, leaving its owning craft disguised.
        // This restores the ownership walk for landed hits. It is gated out of
        // network games because perceivedTeam participates in simulation.
        static constexpr bool kOwnedObjectRevealFixEnabledDefault = true;
        static constexpr long kOwnedObjectRevealTraceBudgetDefault = 96;
        static constexpr bool kWeaponMaskCarrierBiasEnabledDefault = false;
        static constexpr long kAttackRevealTraceBudgetDefault = 64;
        bool g_BomberAiRangeBaselineEnabled = kBomberAiRangeEnabledDefault;
        bool g_BomberAiRangeEnabled = kBomberAiRangeEnabledDefault;
        // Configured value AND'd with the single-player gate, same contract as
        // g_AiOdfGameplayTuningActive below. This feature changes stock content
        // (it raises bomber engagement range from the craft's own weapon ODFs),
        // so it must never reach a network game.
        bool g_BomberAiRangeActive = false;
        bool g_HowitzerVolleyEnabled = kHowitzerVolleyEnabledDefault;
        bool g_HowitzerUndeployedRetaliationFixEnabled =
            kHowitzerUndeployedRetaliationFixEnabledDefault;
        bool g_OwnedObjectRevealFixEnabled =
            kOwnedObjectRevealFixEnabledDefault;
        bool g_OwnedObjectRevealFixActive =
            kOwnedObjectRevealFixEnabledDefault;
        volatile long g_OwnedObjectRevealTraceBudget =
            kOwnedObjectRevealTraceBudgetDefault;
        bool g_WeaponMaskCarrierBiasEnabled = kWeaponMaskCarrierBiasEnabledDefault;
        bool g_AiOdfGameplayTuningEnabled = kAiOdfGameplayTuningEnabledDefault;
        bool g_TurretAimPitchEnabled = kTurretAimPitchEnabledDefault;
        bool g_AttackRevealEnabled = kAttackRevealEnabledDefault;


        // Ties the offsets this file shares with bzr_object_layout.h, whose
        // host test pins them to the disassembly evidence. Editing either side
        // alone is a build break rather than a silent behaviour change.
        static_assert(kGameObjectActualTeamOffset ==
                          ObjectLayout::kGameObjectActualTeam,
                      "actual team offset disagrees with bzr_object_layout.h");
        static_assert(kGameObjectPerceivedTeamOffset ==
                          ObjectLayout::kGameObjectPerceivedTeam,
                      "perceived team offset disagrees with bzr_object_layout.h");
        static_assert(kGameObjectOwnerHandleOffset ==
                          ObjectLayout::kGameObjectOwnerHandle,
                      "owner handle offset disagrees with bzr_object_layout.h");
        static_assert(kGameObjectOwnerHandleOffset !=
                          ObjectLayout::kGameObjectHitch,
                      "owner handle must not alias the hitch field");

        static_assert(kGameObjectTargetHandleOffset ==
                          ObjectLayout::kGameObjectTargetHandle,
                      "target handle offset disagrees with bzr_object_layout.h");
        static_assert(kGameObjectTargetHandleOffset !=
                          ObjectLayout::kGameObjectMaxAmmoObfuscated,
                      "target handle must not alias obfuscated maxAmmo");
        DWORD g_ChunkProxyLastRetryTick = 0;
        bool g_ChunkProxyInitLogged = false;
        bool g_ChunkProxyFailureLogged = false;
        bool g_ChunkProxyWaitLogged = false;
        DWORD g_ChunkMeshProxyLastRetryTick = 0;
        bool g_ChunkMeshProxyInitLogged = false;
        bool g_ChunkMeshProxyFailureLogged = false;
        bool g_ChunkMeshProxyWaitLogged = false;
        bool g_ChunkPayloadResourceLocationsAttempted = false;
        bool g_ChunkPayloadResourceLocationsReady = false;
        bool g_ChunkPayloadResourceLocationsLogged = false;
        bool g_ChunkPayloadResourceLocationsFailureLogged = false;
        std::vector<std::filesystem::path> g_ChunkPayloadResourceDirectories = {};
        void* g_ChunkProxyBillboardSet = nullptr;
        std::vector<ChunkProxySlot> g_ChunkProxySlots = {};
        void* g_GenericChunkBatchManualObject = nullptr;
        void* g_GenericChunkBatchSceneNode = nullptr;
        void* g_GenericChunkBatchSceneManager = nullptr;
        bool g_GenericChunkBatchSectionCreated = false;
        bool g_GenericChunkBatchRuntimeAvailable = true;
        int g_GenericChunkBatchEligibility[2] = { -1, -1 };
        DWORD g_GenericChunkBatchLastLogTick = 0;
        // Bounded diagnostics for the per-frame submission question: the game
        // drives its _updateRenderQueue override more than once per frame (one
        // traversal per active material scheme), and the ManualObject is also
        // attached to the scene graph, so the number of rebuilds and the number
        // of render-queue submissions per frame must be counted, not assumed.
        bool g_GenericChunkBatchRateDiagnostics = false;
        // State-version reuse. The batch is re-submitted to every camera/scheme
        // traversal, but the geometry is only re-emitted when the slot state it
        // is built from actually differs. See include/chunk_batch_invalidation.h
        // for why the version is derived from the source rather than declared by
        // its mutators.
        bool g_GenericChunkBatchReuseEnabled = true;
        // Observer mode: take the decision and count it, then rebuild anyway.
        // This is how the pre-optimization baseline and the dedup opportunity
        // are measured from the same binary, without changing what is drawn.
        bool g_GenericChunkBatchReuseObserveOnly = false;
        uint64_t g_GenericChunkBatchBuiltVersion =
            ChunkBatchInvalidation::kUnbuiltVersion;
        std::string g_GenericChunkBatchBuiltMaterial = {};
        // Last visibility written to the batch object, so setVisible is only
        // called on a transition. Without this the empty path would push
        // setVisible(false) three times per frame for as long as there is no
        // debris, which is most of a normal mission.
        bool g_GenericChunkBatchVisible = false;
        // TEST/DIAGNOSTIC seam only. Set by the environment gate below and
        // never by gameplay: RebuildAndSubmitGenericChunkBatch() reports
        // failure once the slots are already classified batch-ready, which is
        // precisely the window the per-Entity fallback has to cover.
        bool g_ForceGenericChunkBatchFailure = false;
        // TEST/DIAGNOSTIC seam only. ChunkProxyTransform::scale is structurally
        // unit today (the legacy basis vectors are normalised when the
        // quaternion is built), so the unit-scale gate below has no natural
        // trigger. This forces a non-unit scale on tracked generic chunks so
        // the rejection and per-Entity fallback can actually be exercised.
        bool g_ForceGenericChunkNonUnitScale = false;




        FnFlagDisplaySubmit g_BzrFn_FlagDisplaySubmitOriginal = nullptr;
        bool g_MultiplayerFlagRenderHookInstalled = false;
        bool g_MultiplayerFlagRenderHookFailureLogged = false;
        bool g_MultiplayerFlagRendererLoggedReady = false;
        std::unordered_map<uint64_t, MultiplayerFlagRenderSet> g_MultiplayerFlagRenderSets = {};

        // Resolves one decorated export from the shipped OgreMain.dll, caching
        // both outcomes.
        //
        // Caching the *failure* is the point. A caller written as
        // `if (!fn) fn = ResolveOgreProc<T>("...")` retries forever when the
        // name is wrong, because the field it guards on can never be filled.
        // That is not hypothetical: one mis-decorated name in
        // GetHeadlightOgreApi -- `Q` where Ogre::MovableObject::getCastShadows
        // is virtual, so `U` -- turned into a GetProcAddress per emission light
        // per frame and measured 45% of the main thread's CPU in an 80-craft
        // battle. The call sites have been repaired, but the resolver is the
        // place where a *future* typo stops being able to recreate that.
        //
        // A miss is only cached once OgreMain is actually loaded; a lookup made
        // before the module exists is a timing answer, not an answer about the
        // name, and must not be recorded as one.
        void* ResolveOgreProcRaw(const char* name)
        {
            if (!name || !*name)
                return nullptr;

            static std::mutex cacheMutex;
            static std::unordered_map<std::string, void*> cache;

            const HMODULE ogreMain = GetModuleHandleA("OgreMain.dll");
            if (!ogreMain)
                return nullptr;

            std::lock_guard<std::mutex> lock(cacheMutex);
            const auto existing = cache.find(name);
            if (existing != cache.end())
                return existing->second;

            void* const resolved =
                reinterpret_cast<void*>(GetProcAddress(ogreMain, name));
            cache.emplace(name, resolved);
            if (!resolved)
            {
                // One warning per distinct name, for the lifetime of the
                // process. A null Ogre entry point degrades a feature silently,
                // which is exactly how the getCastShadows typo survived.
                Log(L"[OGRE-EXPORTS] WARNING: OgreMain.dll has no export '%hs'. "
                    L"The feature using it will be degraded; the lookup will not "
                    L"be retried.\n",
                    name);
            }
            return resolved;
        }


        // The render-bridge offsets do not hold a bridge on every object that
        // reaches the fragment hooks, and what comes back instead is not even
        // pointer-shaped: observed values include 0x3F3F3F3F ("????") and
        // 0x003D003C (UTF-16 "<="), i.e. the read landed inside a string. Handing
        // those to a __thiscall Ogre method is a virtual dispatch through text --
        // that is the OgreMain write fault at 0x3F3F3F6C in the crash log. Every
        // Ogre object begins with a vtable pointer into OgreMain.dll, so require
        // that before making any call on a candidate.

        bool TryGetOgreModuleRange(uintptr_t& outBase, uintptr_t& outEnd)
        {
            static uintptr_t s_base = 0;
            static uintptr_t s_end = 0;
            static bool s_attempted = false;

            if (!s_attempted)
            {
                // Image size straight off the PE headers, so this needs no psapi.
                // Only a mapped module settles it: asking before OgreMain loads
                // is timing, not an answer, and used to latch "not Ogre" for
                // the life of the process.
                if (const HMODULE ogreMain = GetModuleHandleA("OgreMain.dll"))
                {
                    s_attempted = true;
                    __try
                    {
                        const auto* moduleBytes = reinterpret_cast<const uint8_t*>(ogreMain);
                        const auto* dosHeader = reinterpret_cast<const IMAGE_DOS_HEADER*>(moduleBytes);
                        if (dosHeader->e_magic == IMAGE_DOS_SIGNATURE)
                        {
                            const auto* ntHeaders =
                                reinterpret_cast<const IMAGE_NT_HEADERS*>(moduleBytes + dosHeader->e_lfanew);
                            if (ntHeaders->Signature == IMAGE_NT_SIGNATURE &&
                                ntHeaders->OptionalHeader.SizeOfImage > 0)
                            {
                                s_base = reinterpret_cast<uintptr_t>(moduleBytes);
                                s_end = s_base + ntHeaders->OptionalHeader.SizeOfImage;
                            }
                        }
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        s_base = 0;
                        s_end = 0;
                    }
                }
            }

            outBase = s_base;
            outEnd = s_end;
            return s_base != 0 && s_end > s_base;
        }

        bool LooksLikeOgreObject(const void* candidate)
        {
            const uintptr_t address = reinterpret_cast<uintptr_t>(candidate);
            // Cheap shape rejects first: null, misaligned, or in the bottom 64K.
            if (address < 0x00010000 || (address % sizeof(void*)) != 0)
                return false;

            uintptr_t ogreBase = 0;
            uintptr_t ogreEnd = 0;
            if (!TryGetOgreModuleRange(ogreBase, ogreEnd))
                return false;

            MEMORY_BASIC_INFORMATION mbi = {};
            if (VirtualQuery(candidate, &mbi, sizeof(mbi)) != sizeof(mbi))
                return false;
            if (mbi.State != MEM_COMMIT || !BZROpenShim::MemoryAccess::ProtectionAllows(mbi.Protect, BZROpenShim::MemoryAccess::Access::Read))
                return false;

            uintptr_t vtable = 0;
            __try
            {
                vtable = *reinterpret_cast<const uintptr_t*>(candidate);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }

            return vtable >= ogreBase && vtable < ogreEnd;
        }




        // Master switch for the whole multiplayer vehicle-flag feature: the
        // flag-selection UI, the payload upload and the Ogre renderer hook.
        // [Display] MultiplayerFlags in openshim.ini, defaulting OFF so a
        // missing key does not grow widgets onto BZP/BZP-T's faction-only
        // waiting room. The legacy disable variables remain an override.
        // Latched, because the renderer hook is a vtable write that is only
        // attempted while the feature is on.
        bool ShouldEnableMultiplayerFlagUi()
        {
            static int s_cached = -1;
            if (s_cached < 0)
            {
                bool enabled = false;
                bool iniValue = false;
                if (EnvFlagEnabled("OPENSHIM_DISABLE_MP_FLAG_UI") ||
                    EnvFlagEnabled("OPENSHIM_DISABLE_MULTIPLAYER_FLAG_UI") ||
                    EnvFlagEnabled("OPENSHIM_DISABLE_MP_FLAGS") ||
                    EnvFlagEnabled("BZR_DISABLE_MP_FLAG_UI"))
                {
                    enabled = false;
                }
                else if (TryGetUserConfigBool("Display", "MultiplayerFlags", iniValue))
                {
                    enabled = iniValue;
                }
                s_cached = enabled ? 1 : 0;
                Log(L"[FLAG] multiplayer vehicle flags: %hs\n",
                    enabled ? "enabled" : "disabled");
            }
            return s_cached != 0;
        }

        bool TryGetEnvFloat(const char* name, float& outValue)
        {
            if (!name || !*name)
                return false;

            char value[32] = {};
            const DWORD len = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
            if (len == 0 || len >= sizeof(value))
                return false;

            char* end = nullptr;
            const float parsed = std::strtof(value, &end);
            if (end == value)
                return false;

            while (*end == ' ' || *end == '\t')
                ++end;
            if (*end != '\0')
                return false;

            outValue = parsed;
            return true;
        }

        bool TryGetEnvLong(const char* name, long& outValue)
        {
            if (!name || !*name)
                return false;

            char value[32] = {};
            const DWORD len = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
            if (len == 0 || len >= sizeof(value))
                return false;

            char* end = nullptr;
            const long parsed = std::strtol(value, &end, 10);
            if (end == value)
                return false;

            while (*end == ' ' || *end == '\t')
                ++end;
            if (*end != '\0')
                return false;

            outValue = parsed;
            return true;
        }

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

        void LogChunkDiagnostic(const char* component, const wchar_t* fmt, ...)
        {
            if (!fmt || !*fmt)
                return;

            wchar_t buffer[4096] = {};
            va_list args;
            va_start(args, fmt);
            _vsnwprintf_s(buffer, _countof(buffer), _TRUNCATE, fmt, args);
            va_end(args);

            Log(L"%ls", buffer);
            LogShimW(LogLevel::Info, component, L"%ls", buffer);
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

        uintptr_t GetMainModuleBase()
        {
            static uintptr_t s_moduleBase = 0;
            if (s_moduleBase == 0)
                s_moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
            return s_moduleBase;
        }


        bool AcquireChunkLogSlot()
        {
            if (g_TraceChunkRenderVerbose)
                return true;

            return InterlockedDecrement(&g_ChunkRenderLogBudget) >= 0;
        }

        std::filesystem::path GetConfigModuleDirectory()
        {
            char path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return {};

            return std::filesystem::path(path).parent_path();
        }

        void AppendUniquePath(std::vector<std::filesystem::path>& paths, const std::filesystem::path& candidate)
        {
            if (candidate.empty())
                return;

            if (std::find(paths.begin(), paths.end(), candidate) != paths.end())
                return;

            paths.push_back(candidate);
        }

        static std::filesystem::path TryGetWorkshopContentDirectory(const std::filesystem::path& gameDir)
        {
            if (gameDir.empty())
                return {};

            const auto normalized = gameDir.lexically_normal().string();
            std::string lower = normalized;
            std::transform(lower.begin(), lower.end(), lower.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

            constexpr const char* kSteamCommonMarker = "\\steamapps\\common\\";
            const size_t markerPos = lower.find(kSteamCommonMarker);
            if (markerPos == std::string::npos)
                return {};

            return std::filesystem::path(normalized.substr(0, markerPos)) /
                "steamapps" / "workshop" / "content" / "301650";
        }

        static void AppendImmediateSubdirectories(
            const std::filesystem::path& parent,
            std::vector<std::filesystem::path>& results)
        {
            if (parent.empty())
                return;

            std::error_code ec;
            if (!std::filesystem::exists(parent, ec) || ec)
                return;

            for (std::filesystem::directory_iterator it(parent, ec), end;
                 !ec && it != end;
                 it.increment(ec))
            {
                if (ec)
                    break;

                const auto& entry = *it;
                if (entry.is_directory(ec) && !ec)
                    AppendUniquePath(results, entry.path());
            }
        }

        std::vector<std::filesystem::path> GetCampaignContentRootCandidates(
            const std::filesystem::path& gameDir)
        {
            std::vector<std::filesystem::path> candidates;
            if (gameDir.empty())
                return candidates;

            AppendImmediateSubdirectories(gameDir / "addon", candidates);
            AppendImmediateSubdirectories(gameDir / "mods", candidates);
            AppendImmediateSubdirectories(gameDir / "packaged_mods", candidates);
            AppendImmediateSubdirectories(TryGetWorkshopContentDirectory(gameDir), candidates);
            return candidates;
        }

        char* TrimAsciiInPlace(char* text)
        {
            if (!text)
                return text;

            while (*text && std::isspace(static_cast<unsigned char>(*text)))
                ++text;

            size_t length = std::strlen(text);
            while (length > 0 && std::isspace(static_cast<unsigned char>(text[length - 1])))
                text[--length] = '\0';

            return text;
        }







        // Non-zero in a network game (the host has an id too). Fails CLOSED:
        // see kLocalPlayerNetIdUnreadable. Callers that only want to know
        // "am I in a network session" should read this as `!= 0`, which is
        // correct for the sentinel as well.
        uint16_t ReadLocalPlayerNetIdValue()
        {
            __try
            {
                return *reinterpret_cast<volatile const uint16_t*>(kLocalPlayerNetIdAddr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return kLocalPlayerNetIdUnreadable;
            }
        }

        // The one predicate every SinglePlayer-tier feature gate is written
        // against. Named so a new feature does not have to rediscover that
        // "net id 0" means "safe to touch the simulation".
        bool IsSinglePlayerSession()
        {
            return ReadLocalPlayerNetIdValue() == 0;
        }




        std::string ToLowerAscii(std::string value)
        {
            for (char& ch : value)
            {
                ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            }
            return value;
        }

        bool TryGetGameObjectFieldBase(void* objectPtr, uint8_t*& outBase)
        {
            outBase = nullptr;
            const auto address = reinterpret_cast<uintptr_t>(objectPtr);
            if (address < 0x00010000 || (address % sizeof(void*)) != 0)
                return false;

            MEMORY_BASIC_INFORMATION mbi = {};
            if (VirtualQuery(objectPtr, &mbi, sizeof(mbi)) != sizeof(mbi))
                return false;
            if (mbi.State != MEM_COMMIT || !BZROpenShim::MemoryAccess::ProtectionAllows(mbi.Protect, BZROpenShim::MemoryAccess::Access::Read))
                return false;

            __try
            {
                auto* bytes = reinterpret_cast<uint8_t*>(objectPtr);
                auto** vtable = *reinterpret_cast<void***>(bytes + kGameObjectInterfaceOffset);
                if (!vtable)
                    return false;

                MEMORY_BASIC_INFORMATION vtableInfo = {};
                if (VirtualQuery(vtable, &vtableInfo, sizeof(vtableInfo)) != sizeof(vtableInfo))
                    return false;
                if (vtableInfo.State != MEM_COMMIT || !BZROpenShim::MemoryAccess::ProtectionAllows(vtableInfo.Protect, BZROpenShim::MemoryAccess::Access::Read))
                    return false;

                // Absolute VA, matching kGogGameObjectFriendPAddr and the rest
                // of this file; the shim already assumes the image loads at its
                // preferred base. Rebase defensively anyway so a relocated
                // image degrades to "no entries match" rather than to a
                // mis-identification.
                const uintptr_t base = GetMainModuleBase();
                const uintptr_t expected = base
                    ? base + (kGogGameObjectGetTeamAddr - kGogPreferredImageBase)
                    : kGogGameObjectGetTeamAddr;
                if (reinterpret_cast<uintptr_t>(vtable[kGameObjectGetTeamVtableOffset / sizeof(void*)]) != expected)
                    return false;

                outBase = bytes;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }



        bool IsLikelyGameObjectEntry(void* objectPtr)
        {
            uint8_t* base = nullptr;
            return TryGetGameObjectFieldBase(objectPtr, base);
        }

        int GetGameObjectActualTeam(void* objectPtr)
        {
            uint8_t* base = nullptr;
            if (!TryGetGameObjectFieldBase(objectPtr, base))
                return INT_MIN;

            // Direct field read. GetTeam's whole body is
            // `mov eax,[interface+0x15C]; ret`, and interface is complete+0x18,
            // so this reads exactly what the virtual would have returned.
            __try
            {
                return *reinterpret_cast<const int*>(base + kGameObjectActualTeamOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return INT_MIN;
            }
        }

        bool IsNeutralTeamObject(void* objectPtr)
        {
            return GetGameObjectActualTeam(objectPtr) == 0;
        }


        int GetGameObjectTeamForLog(void* objectPtr)
        {
            return GetGameObjectActualTeam(objectPtr);
        }

        // Defined later (headlight/flag sections); declared here so the
        // earlier diagnostic samplers can share the verified user-object
        // global and arena enumeration instead of the removed stale globals.
        // Defined with the pilot flashlight below. Declared here so the Ogre
        // scene-teardown hooks -- which run earlier in this file -- can drop the
        // shim-owned pilot light before the scene frees it.

        bool g_TraceDamageReveal = false;
        volatile long g_DamageRevealTraceBudget = 0;
        static constexpr long kDamageRevealTraceBudgetDefault = 400;

        // Player-kill research trace (PR 107 phase 2-3). Opt-in only.
        // Default OFF. When enabled, each authoritative multiplayer death
        // emits one compact diagnostic record with candidate controller fields
        // for victim and damager. No career-stats behavior is changed.
        bool g_TracePlayerKills = false;
        volatile long g_PlayerKillTraceBudget = 0;
        static constexpr long kPlayerKillTraceBudgetDefault = 256;
        static constexpr long kPlayerKillTraceBudgetMax = 4096;

        // MSVC RTTI: vtable[-1] -> CompleteObjectLocator, +12 -> TypeDescriptor,
        // +8 -> the decorated name. Every step is bounds-checked and the whole
        // walk sits under SEH, so an object without RTTI yields "?" rather than
        // a fault.
        const char* TryGetRttiClassName(const void* object, char* buffer, size_t bufferSize)
        {
            if (!object || !buffer || bufferSize == 0)
                return "?";
            buffer[0] = '\0';
            __try
            {
                auto* const* vtable = *reinterpret_cast<void* const* const*>(object);
                if (!vtable)
                    return "?";
                const auto* col = reinterpret_cast<const uint8_t*>(vtable[-1]);
                if (!col)
                    return "?";
                const auto* descriptor = *reinterpret_cast<const uint8_t* const*>(col + 12);
                if (!descriptor)
                    return "?";
                const char* name = reinterpret_cast<const char*>(descriptor + 8);
                size_t i = 0;
                for (; i + 1 < bufferSize && name[i] >= 0x20 && name[i] < 0x7F; ++i)
                    buffer[i] = name[i];
                buffer[i] = '\0';
                return (i > 0) ? buffer : "?";
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return "?";
            }
        }

        bool TryGetGameObjectHandleValue(void* objectPtr, int& outHandle)
        {
            outHandle = 0;
            if (!objectPtr || g_GameObjectGetHandleAddr == 0)
                return false;

            using GetHandleThiscallFn = uint32_t(__thiscall*)(void*);
            __try
            {
                outHandle = static_cast<int>(
                    reinterpret_cast<GetHandleThiscallFn>(g_GameObjectGetHandleAddr)(objectPtr));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outHandle = 0;
            }
            return outHandle != 0;
        }


        // The event layer's per-frame driver. Order matters: session
        // transitions and derived kills are published first so they land in the
        // same drain as everything the engine published during this frame.
        static void TickOpenShimEventLayer()
        {
            TickCareerSessionState();
            TickCareerPendingVictims();
            DispatchPendingEvents();
        }


        uint32_t ResolveRel32Target(uint8_t* callInstr)
        {
            if (!callInstr || callInstr[0] != 0xE8)
                return 0;

            const int32_t rel = *reinterpret_cast<int32_t*>(callInstr + 1);
            return static_cast<uint32_t>(
                reinterpret_cast<uintptr_t>(callInstr + 5) + rel);
        }

        bool WritePointerValue(uintptr_t address, void* value)
        {
            if (address == 0)
                return false;

            DWORD oldProtect = 0;
            if (!VirtualProtect(reinterpret_cast<void*>(address), sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;

            *reinterpret_cast<void**>(address) = value;
            FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<void*>(address), sizeof(void*));

            DWORD restoreProtect = 0;
            VirtualProtect(reinterpret_cast<void*>(address), sizeof(void*), oldProtect, &restoreProtect);
            return true;
        }

        bool VtableTypeNameMatches(uintptr_t vtableAddress, const char* expectedName)
        {
            if (!vtableAddress || !expectedName || !*expectedName)
                return false;

            __try
            {
                const uintptr_t completeObjectLocator =
                    *reinterpret_cast<const uint32_t*>(vtableAddress - sizeof(uint32_t));
                if (!completeObjectLocator)
                    return false;

                const uintptr_t typeDescriptor =
                    *reinterpret_cast<const uint32_t*>(completeObjectLocator + 0x0C);
                if (!typeDescriptor)
                    return false;

                const char* typeName = reinterpret_cast<const char*>(typeDescriptor + 0x08);
                return std::strcmp(typeName, expectedName) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }


        bool IsExuModuleLoaded()
        {
            return GetModuleHandleA("exu.dll") != nullptr ||
                   GetModuleHandleA("ExtraUtilities.dll") != nullptr;
        }

        // Generic protected in-place byte write (VirtualProtect + memcpy + flush).
        bool WritePatchBytes(uintptr_t address, const uint8_t* bytes, size_t len)
        {
            auto* target = reinterpret_cast<uint8_t*>(address);
            DWORD oldProtect = 0;
            if (!VirtualProtect(target, len, PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;
            std::memcpy(target, bytes, len);
            FlushInstructionCache(GetCurrentProcess(), target, len);
            DWORD restoreProtect = 0;
            VirtualProtect(target, len, oldProtect, &restoreProtect);
            return true;
        }

        bool HasTerrainLineOfSight(double startX,
                                          double startY,
                                          double startZ,
                                          double endX,
                                          double endY,
                                          double endZ)
        {
            if (!g_BzrFn_TerrainGetIntersection)
                return true;

            const float diffX = static_cast<float>(endX - startX);
            const float diffY = static_cast<float>(endY - startY);
            const float diffZ = static_cast<float>(endZ - startZ);
            float fraction = 1.0f;
            __try
            {
                return g_BzrFn_TerrainGetIntersection(startX,
                                                       startY,
                                                       startZ,
                                                       diffX,
                                                       diffY,
                                                       diffZ,
                                                       &fraction,
                                                       nullptr) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // SEH leaves used by AttackTaskDoStateTuningHook. Keep all checked
        // STL iterators/RAII in the caller so Debug builds do not hit C2712.
        bool RedirectCallTarget(uintptr_t callAddress,
                                       uintptr_t originalTarget,
                                       uintptr_t desiredTarget)
        {
            uint8_t call[5] = {};
            SIZE_T read = 0;
            if (!ReadProcessMemory(GetCurrentProcess(),
                                   reinterpret_cast<const void*>(callAddress),
                                   call,
                                   sizeof(call),
                                   &read) ||
                read != sizeof(call) || call[0] != 0xE8)
            {
                return false;
            }

            int32_t currentRelative = 0;
            std::memcpy(&currentRelative, call + 1, sizeof(currentRelative));
            const uintptr_t currentTarget = callAddress + 5 + currentRelative;
            if (currentTarget == desiredTarget)
                return true;
            if (currentTarget != originalTarget)
                return false;

            const int32_t desiredRelative =
                static_cast<int32_t>(desiredTarget) -
                static_cast<int32_t>(callAddress + 5);
            std::memcpy(call + 1, &desiredRelative, sizeof(desiredRelative));
            return WritePatchBytes(callAddress, call, sizeof(call));
        }

        std::vector<std::filesystem::path> GetProducerOdfDirectoryCandidates()
        {
            std::vector<std::filesystem::path> candidates;

            const auto moduleDir = GetMainModuleDirectory();
            if (moduleDir.empty())
                return candidates;

            for (const auto& root : GetCampaignContentRootCandidates(moduleDir))
            {
                AppendUniquePath(candidates, root / "ODF");
                AppendUniquePath(candidates, root / "_Release" / "ODF");
                AppendUniquePath(candidates, root / "_Source" / "ODF");
            }
            candidates.push_back(moduleDir / "Edit" / "stock");
            return candidates;
        }

        bool TryParseFloatValue(const char* value, float& out)
        {
            if (!value || !*value)
                return false;

            char* end = nullptr;
            const float parsed = std::strtof(value, &end);
            if (end == value)
                return false;

            while (end && *end && std::isspace(static_cast<unsigned char>(*end)))
                ++end;

            if (end && *end == 'f' && end[1] == '\0')
                ++end;

            if (end && *end != '\0')
                return false;

            out = parsed;
            return std::isfinite(out);
        }

        bool TryParseBoolValue(const char* value, bool& out)
        {
            return BZROpenShim::BoolToken::TryParse(value, out);
        }

        bool TryGetObjectOdfToken(void* objectPtr, char (&outToken)[kProducerBuildMenuTokenLen + 1])
        {
            outToken[0] = '\0';
            if (!objectPtr)
                return false;

            // Use the same GameObject -> class virtual lookup as the validated
            // engine-flame ODF path. The tempting raw object+0xF8/class+0x20
            // chain identifies a different class record for Craft instances
            // and produces plausible-looking garbage instead of the ODF name.
            char rawOdf[kGameObjectClassOdfNameMax + 1] = {};
            if (!TryGetCraftOdfName(objectPtr, rawOdf, sizeof(rawOdf)))
                return false;

            const ProducerBuildMenuEntry entry = NormalizeProducerBuildMenuToken(rawOdf);
            if (!entry.hasValue)
                return false;

            strncpy_s(outToken, entry.token, _TRUNCATE);
            return true;
        }

        bool TryNormalizeQuotedStringValue(const char* value,
                                                  char* out,
                                                  size_t outSize)
        {
            if (!value || !out || outSize == 0)
                return false;

            out[0] = '\0';

            const char* start = value;
            while (*start && std::isspace(static_cast<unsigned char>(*start)))
                ++start;

            const char* end = start + std::strlen(start);
            while (end > start && std::isspace(static_cast<unsigned char>(end[-1])))
                --end;

            if (end <= start)
                return false;

            if ((*start == '"' || *start == '\'') && end > start + 1 && end[-1] == *start)
            {
                ++start;
                --end;
            }

            size_t outIndex = 0;
            while (start < end && outIndex + 1 < outSize)
            {
                out[outIndex++] = static_cast<char>(
                    std::tolower(static_cast<unsigned char>(*start++)));
            }
            out[outIndex] = '\0';

            return outIndex > 0;
        }

        ProducerBuildMenuEntry NormalizeQuotedOdfToken(const char* value)
        {
            char normalized[64] = {};
            if (!TryNormalizeQuotedStringValue(value, normalized, sizeof(normalized)))
                return {};

            return NormalizeProducerBuildMenuToken(normalized);
        }

        bool TryResolveOdfFilePath(const char* odfToken, std::filesystem::path& outPath)
        {
            outPath.clear();

            const ProducerBuildMenuEntry odfKey = NormalizeQuotedOdfToken(odfToken);
            if (!odfKey.hasValue)
                return false;

            const auto directories = GetProducerOdfDirectoryCandidates();
            for (const auto& directory : directories)
            {
                std::error_code error;
                const auto mpPath = directory / (std::string(odfKey.token) + "_mp.odf");
                if (std::filesystem::exists(mpPath, error) && !error)
                {
                    outPath = mpPath;
                    return true;
                }

                error.clear();
                const auto normalPath = directory / (std::string(odfKey.token) + ".odf");
                if (std::filesystem::exists(normalPath, error) && !error)
                {
                    outPath = normalPath;
                    return true;
                }
            }

            return false;
        }

        bool TryGetGameObjectObj76(void* gameObject, void*& outObj76)
        {
            outObj76 = nullptr;
            if (!gameObject)
                return false;

            __try
            {
                outObj76 =
                    *reinterpret_cast<void* const*>(reinterpret_cast<const uint8_t*>(gameObject) + kGameObjectObjOffset);
                return outObj76 != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outObj76 = nullptr;
                return false;
            }
        }

        bool TryGetGameObjectFromObj76(void* obj76, void*& outGameObject)
        {
            outGameObject = nullptr;
            if (!obj76)
                return false;

            __try
            {
                outGameObject =
                    *reinterpret_cast<void* const*>(reinterpret_cast<const uint8_t*>(obj76) + kObj76GameObjectOffset);
                return outGameObject != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outGameObject = nullptr;
                return false;
            }
        }

        bool TryGetObjectWorldPositionFromObj76(void* obj76, float (&outPosition)[3])
        {
            outPosition[0] = 0.0f;
            outPosition[1] = 0.0f;
            outPosition[2] = 0.0f;
            if (!obj76)
                return false;

            __try
            {
                const auto* transform = reinterpret_cast<const LegacyMat3*>(
                    reinterpret_cast<const uint8_t*>(obj76) + kObj76TransformOffset);
                outPosition[0] = static_cast<float>(transform->posit_x);
                outPosition[1] = static_cast<float>(transform->posit_y);
                outPosition[2] = static_cast<float>(transform->posit_z);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outPosition[0] = 0.0f;
                outPosition[1] = 0.0f;
                outPosition[2] = 0.0f;
                return false;
            }
        }

        bool TryGetGameObjectWorldPosition(void* gameObject, float (&outPosition)[3])
        {
            void* obj76 = nullptr;
            return TryGetGameObjectObj76(gameObject, obj76) &&
                   TryGetObjectWorldPositionFromObj76(obj76, outPosition);
        }

        // The advisory-PDB "object list" global (removed; it landed in string
        // data on the live exe) never produced objects from pointer-array
        // walks. Enumerate the verified GameObject arena instead:
        // the same 0x400-stride pool the GetObjByHandle slot formula indexes
        // (base 0x0260DB20, 4096 slots), filtered by the live-vtable check
        // the headlight walker uses.
        // Read-only runtime probes (2026-08-18).
        //
        // Static tracing has repeatedly named the wrong function in this
        // codebase, so these two probes answer the remaining questions by
        // observation instead. Both are diagnostic only: they read memory,
        // format a log line, and change nothing.
        // ---------------------------------------------------------------

        // Discovers owner/parent links empirically rather than assuming an
        // offset: reports which dwords inside `object` point at another live
        // slot of the GameObject arena. That is what turns "the damager might
        // be owned by a craft" into a measured field offset.
        void LogArenaPointerFields(const wchar_t* tag, void* object, size_t scanBytes)
        {
            if (!object)
                return;
            auto* arena = reinterpret_cast<uint8_t*>(EngineGlobals::GameObjectArena());
            if (!arena)
                return;
            const uintptr_t arenaLow = reinterpret_cast<uintptr_t>(arena);
            const uintptr_t arenaHigh = arenaLow + kHeadlightObjectSlotCount * kHeadlightObjectSlotSize;

            wchar_t line[512];
            int used = _snwprintf_s(line, _countof(line), _TRUNCATE, L"[DMGREVEAL]     %ls arenaRefs:", tag);
            if (used < 0)
                return;
            int found = 0;
            for (size_t off = 0; off + sizeof(void*) <= scanBytes && found < 8; off += sizeof(void*))
            {
                uintptr_t value = 0;
                __try
                {
                    value = *reinterpret_cast<const uintptr_t*>(reinterpret_cast<uint8_t*>(object) + off);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    break;
                }
                if (value < arenaLow || value >= arenaHigh)
                    continue;
                if (((value - arenaLow) % kHeadlightObjectSlotSize) != 0)
                    continue;
                if (!IsLikelyGameObjectEntry(reinterpret_cast<void*>(value)))
                    continue;
                const int wrote = _snwprintf_s(line + used, _countof(line) - used, _TRUNCATE,
                                               L" +0x%03X=0x%08X", static_cast<unsigned>(off),
                                               static_cast<uint32_t>(value));
                if (wrote < 0)
                    break;
                used += wrote;
                ++found;
            }
            if (found == 0)
                return;
            Log(L"%ls\n", line);
        }

        size_t CollectLiveGameObjectsFromArena(void** outObjects, size_t capacity)
        {
            if (!outObjects || capacity == 0)
                return 0;
            auto* arena = reinterpret_cast<uint8_t*>(EngineGlobals::GameObjectArena());
            if (!arena)
                return 0;
            size_t count = 0;
            for (size_t i = 0; i < kHeadlightObjectSlotCount && count < capacity; ++i)
            {
                void* object = arena + i * kHeadlightObjectSlotSize;
                if (IsLiveHeadlightObjectSlot(object))
                    outObjects[count++] = object;
            }
            return count;
        }

    }
    using namespace Hooks;

    // ---------------------------------------------------------------------
    // Helpers
    // ---------------------------------------------------------------------

    bool EnvFlagEnabled(const char* name)
    {
        if (!name || !*name)
            return false;

        char value[16] = {};
        const DWORD len = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
        if (len == 0 || len >= sizeof(value))
            return false;

        return value[0] != '0' && value[0] != '\0';
    }

    std::filesystem::path GetUserConfigPath()
    {
        const auto dir = GetConfigModuleDirectory();
        if (dir.empty())
            return {};
        return dir / kUserConfigFileName;
    }

    // Tri-state string read: returns false when the key is absent (or the
    // file/section is missing), so callers can distinguish "no opinion"
    // (fall through to the next source) from an explicit value.
    bool TryGetUserConfigString(const char* section, const char* key, std::string& out)
    {
        const auto path = GetUserConfigPath();
        if (path.empty())
            return false;

        // A sentinel default reliably detects a missing key: a present key
        // (even blank) never yields the sentinel byte.
        constexpr char kUnsetSentinel[] = "\x01__openshim_unset__";
        char buf[128] = {};
        GetPrivateProfileStringA(section, key, kUnsetSentinel, buf,
            static_cast<DWORD>(sizeof(buf)), path.string().c_str());
        if (buf[0] == '\0' || std::strcmp(buf, kUnsetSentinel) == 0)
            return false;

        char* trimmed = TrimAsciiInPlace(buf);
        if (*trimmed == '\0')
            return false;
        out.assign(trimmed);
        return true;
    }

    // Tri-state boolean read over TryGetUserConfigString: returns false when
    // the key is absent OR present-but-unparseable (both mean "no opinion").
    // Accepts the words in bool_token.h.
    bool TryGetUserConfigBool(const char* section, const char* key, bool& out)
    {
        std::string value;
        return TryGetUserConfigString(section, key, value) && BZROpenShim::BoolToken::TryParse(value, out);
    }

    // Retry loops call the installer every 100 ms; log each refused site once.
    static void LogDetourStealRefusal(uintptr_t target, size_t patchLen,
                                      const BZROpenShim::X86StealPlan& plan,
                                      const uint8_t* bytes, size_t byteCount)
    {
        static volatile LONG s_loggedTargets[64] = {};
        for (auto& slot : s_loggedTargets)
        {
            const LONG seen = InterlockedCompareExchange(&slot, static_cast<LONG>(target), 0);
            if (seen == 0) break;
            if (seen == static_cast<LONG>(target)) return;
        }
        char hex[3 * kInlineDetourMaxPatchLen + 1] = {};
        size_t n = 0;
        for (size_t i = 0; i < byteCount && i < kInlineDetourMaxPatchLen && n + 3 < sizeof(hex); ++i)
            n += static_cast<size_t>(snprintf(hex + n, sizeof(hex) - n, "%02X ", bytes[i]));
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Warn, "DETOUR",
            "refused %u-byte steal at 0x%08X: %s at +%u (boundary %u, %u instr) bytes=%s",
            static_cast<unsigned>(patchLen), static_cast<unsigned>(target),
            BZROpenShim::X86StealStatusName(plan.status), static_cast<unsigned>(plan.failOffset),
            static_cast<unsigned>(plan.boundary), static_cast<unsigned>(plan.instructionCount), hex);
    }

    bool InstallInlineDetour32(InlineDetour32& detour,
                                      uintptr_t target,
                                      void* hook,
                                      size_t patchLen,
                                      const uint8_t* expectedBytes,
                                      size_t expectedLen)
    {
        if (!target || !hook || patchLen < 5 || patchLen > detour.original.size())
            return false;

        // Held from the "already installed" check through the write: the
        // patch thread's settle loop and a game-thread SDK bridge can both
        // arrive here for one site, and the loser used to see the other's
        // half-written jump as a prologue mismatch, or copy it into its own
        // trampoline.
        HookEngine::CodePatchLock lock;

        if (detour.trampoline)
            return true;

        auto* targetBytes = reinterpret_cast<uint8_t*>(target);
        if (expectedBytes && expectedLen > 0)
        {
            if (expectedLen > patchLen || memcmp(targetBytes, expectedBytes, expectedLen) != 0)
                return false;
        }

        // The stolen range must end on an instruction boundary and contain
        // nothing that changes meaning at the trampoline address. Read past
        // patchLen so an instruction straddling the boundary can be sized;
        // if that read fails (page end) fall back to the exact range.
        uint8_t probe[kInlineDetourMaxPatchLen + 15] = {};
        size_t probeLen = patchLen + 15;
        SIZE_T probeRead = 0;
        if (!ReadProcessMemory(GetCurrentProcess(), targetBytes, probe, probeLen, &probeRead) || probeRead != probeLen)
        {
            probeLen = patchLen;
            probeRead = 0;
            if (!ReadProcessMemory(GetCurrentProcess(), targetBytes, probe, probeLen, &probeRead) || probeRead != probeLen)
                return false;
        }
        const BZROpenShim::X86StealPlan plan = BZROpenShim::PlanDetourSteal32(probe, probeLen, patchLen);
        if (plan.status != BZROpenShim::X86StealStatus::Ok)
        {
            LogDetourStealRefusal(target, patchLen, plan, probe, probeLen);
            return false;
        }

        auto* trampolineBytes = reinterpret_cast<uint8_t*>(
            VirtualAlloc(nullptr, patchLen + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
        if (!trampolineBytes)
            return false;

        memcpy(detour.original.data(), targetBytes, patchLen);
        memcpy(trampolineBytes, targetBytes, patchLen);

        // rel32 call/jmp/jcc inside the stolen range keep their absolute
        // destination once re-based by the copy distance.
        for (size_t r = 0; r < plan.rel32Count; ++r)
        {
            const size_t at = plan.rel32Offsets[r];
            int32_t rel = 0;
            memcpy(&rel, trampolineBytes + at, sizeof(rel));
            rel += static_cast<int32_t>(target - reinterpret_cast<uintptr_t>(trampolineBytes));
            memcpy(trampolineBytes + at, &rel, sizeof(rel));
        }

        const uintptr_t resumeAddr = target + patchLen;
        trampolineBytes[patchLen] = 0xE9;
        const int32_t trampolineRel =
            static_cast<int32_t>(resumeAddr) -
            static_cast<int32_t>(reinterpret_cast<uintptr_t>(trampolineBytes + patchLen) + 5);
        memcpy(trampolineBytes + patchLen + 1, &trampolineRel, sizeof(trampolineRel));

        // The whole jump goes in through one WriteMemory call, which holds
        // every other thread off the site while the bytes land and flushes
        // the instruction cache. It used to be stored a byte at a time,
        // opcode first and rel32 after, on code the game thread may have
        // been executing.
        uint8_t patchImage[kInlineDetourMaxPatchLen] = {};
        patchImage[0] = 0xE9;
        const int32_t hookRel =
            static_cast<int32_t>(reinterpret_cast<uintptr_t>(hook)) -
            static_cast<int32_t>(target + 5);
        memcpy(patchImage + 1, &hookRel, sizeof(hookRel));
        for (size_t i = 5; i < patchLen; ++i)
            patchImage[i] = 0x90;
        if (!HookEngine::WriteMemory(static_cast<uint32_t>(target), patchImage, patchLen))
        {
            VirtualFree(trampolineBytes, 0, MEM_RELEASE);
            return false;
        }

        detour.target = target;
        detour.hook = hook;
        detour.trampoline = trampolineBytes;
        detour.patchLen = patchLen;
        return true;
    }

    bool ExpectedBytesMatchAt(uintptr_t address,
                                     const uint8_t* expectedBytes,
                                     size_t expectedLen)
    {
        if (!address || !expectedBytes || expectedLen == 0 || expectedLen > kInlineDetourMaxPatchLen)
            return false;

        uint8_t current[kInlineDetourMaxPatchLen] = {};
        SIZE_T read = 0;
        if (!ReadProcessMemory(GetCurrentProcess(),
                               reinterpret_cast<const void*>(address),
                               current,
                               expectedLen,
                               &read) ||
            read != expectedLen)
        {
            return false;
        }

        return memcmp(current, expectedBytes, expectedLen) == 0;
    }

    std::filesystem::path GetMainModuleDirectory()
    {
        char path[MAX_PATH] = {};
        const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
        if (length == 0 || length >= MAX_PATH)
            return {};

        return std::filesystem::path(path).parent_path();
    }

    std::string TrimAsciiCopy(const std::string& value)
    {
        size_t start = 0;
        while (start < value.size() &&
               std::isspace(static_cast<unsigned char>(value[start])))
        {
            ++start;
        }

        size_t end = value.size();
        while (end > start &&
               std::isspace(static_cast<unsigned char>(value[end - 1])))
        {
            --end;
        }

        return value.substr(start, end - start);
    }

    // Re-apply the feature behind a settings row from the freshly written
    // ini. Latched initializers get their latch cleared and re-run, which
    // deliberately preserves the documented precedence chain (legacy cfg and
    // env overrides still win over the ini baseline).
    void ApplyShimSettingLive(ShimSettingApplyGroup group)
    {
        switch (group)
        {
        case ShimSettingApplyGroup::GlobalImprovement:
            InitializeGlobalImprovementConfig();
            break;
        case ShimSettingApplyGroup::UnderAttackAlert:
            g_UnderAttackAlertConfigInitialized = false;
            InitializeUnderAttackAlertConfig();
            break;
        case ShimSettingApplyGroup::TargetReticle:
            g_TargetReticlePopupConfigInitialized = false;
            InitializeTargetReticlePopupConfig();
            break;
        case ShimSettingApplyGroup::JetFlames:
            g_JetFlamesConfigInitialized = false;
            InitializeJetFlamesConfig();
            break;
        case ShimSettingApplyGroup::UnitVo:
            g_UnitVoConfigInitialized = false;
            InitializeUnitVoConfig();
            break;
        case ShimSettingApplyGroup::GlobalTurbo:
            g_GlobalTurboConfigInitialized = false;
            InitializeGlobalTurboConfig();
            break;
        case ShimSettingApplyGroup::Headlights:
            ReapplyHeadlightConfigFromUserConfig();
            break;
        case ShimSettingApplyGroup::PilotFlashlight:
            g_PilotFlashlightConfigInitialized = false;
            InitializePilotFlashlightConfig();
            break;
        case ShimSettingApplyGroup::BzrNetRoute:
            // Only the route preference re-applies live; the port is latched on
            // the first pass because the engine overwrites that variable with
            // the port it actually bound.
            InitializeBzrNetConfig();
            break;
        case ShimSettingApplyGroup::RenderProfile:
            RenderProfiles::ReloadRenderProfileConfig();
            break;
        case ShimSettingApplyGroup::LiveEngineToggle:
            InitializeHopOutAttackAlertConfig();
            InitializeSatelliteVisibilityFixConfig(false);
            SunFlash::ReloadConfig();
            break;
        case ShimSettingApplyGroup::ReadOnNextUse:
        case ShimSettingApplyGroup::RestartRequired:
            break;
        }
    }


    // Puts every piece of per-process hook state back to its resting value
    // before ResolveBzrHooks binds addresses and reads configuration.
    // Also re-derives the pointers that come from already-installed detour
    // trampolines. Runs after g_IsSteamExe is set.
    void ResetBzrHookRuntimeState()
    {
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
        g_BzrFn_ProducerModeCallOriginal = nullptr;
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
        g_AiTuningCache = {};
        g_ShieldTowerTeamFilterCache = {};
        g_MagnetMineTeamFilterCache = {};
        g_ProximityMineTeamFilterCache = {};
        g_HasAppliedProducerBuildMenu = false;
        g_LastAppliedProducerBuildMenu = 0;
        g_LastUnknownProducerVft = 0;
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
        g_BzrFn_ArtilleryDoAttackOriginal = g_ArtilleryDoAttackDetour.trampoline
            ? reinterpret_cast<FnArtilleryDoAttack>(g_ArtilleryDoAttackDetour.trampoline)
            : nullptr;
        g_ArtilleryDoAttackHookInstalled =
            (g_BzrFn_ArtilleryDoAttackOriginal != nullptr);
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
        LogChunkDiagnostic("chunk", L"[CHUNK] Trace logging: %hs%s budget=%ld entryLimit=%u\n",
            g_TraceChunkRender ? "enabled" : "disabled",
            g_TraceChunkRenderVerbose ? " verbose" : "",
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
            {"MapFilter6", reinterpret_cast<void**>(&g_BzrFn_MapFilter6)},
            {"ChunkResolve", reinterpret_cast<void**>(&g_BzrFn_ChunkResolve)},
            {"MapFilter8Check", reinterpret_cast<void**>(&g_BzrFn_MapFilter8Check)},
            {"MapFilterCreate", reinterpret_cast<void**>(&g_BzrFn_MapFilterCreate)},
            {"MapFilterScrollUp", reinterpret_cast<void**>(&g_BzrFn_MapFilterScrollUp)},
            {"MapFilterScrollDown", reinterpret_cast<void**>(&g_BzrFn_MapFilterScrollDown)},
            {"Localize", reinterpret_cast<void**>(&g_BzrFn_Localize)},
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
        // The map filter patches share state (5/8 fills the list pointer the
        // scroll callbacks use, 7/8 sets the flag 8/8 reads), so the family
        // stands down as a unit. 5/8 and 8/8 call through the first two
        // pointers from naked asm with no check.
        if (name.rfind("Map Filters ", 0) == 0)
        {
            return firstMissing({{"MapFilterCreate", g_BzrFn_MapFilterCreate},
                                 {"MapFilter8Check", g_BzrFn_MapFilter8Check},
                                 {"MapFilter6", reinterpret_cast<const void*>(g_BzrFn_MapFilter6)}});
        }
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
            {"InstallUiManualObjectDedupeHookIfPossible", &InstallUiManualObjectDedupeHookIfPossible},
            {"InstallSceneTeardownForgetHooksIfPossible", &InstallSceneTeardownForgetHooksIfPossible},
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
        // Gate on both user config AND verified resource availability.
        // This prevents a copied openshim.ini with ChunkMeshes=1 from
        // entering unsafe Ogre Entity creation paths when the asset pack
        // is absent, stale, or partial.
        g_EnableChunkMeshProxy = configWantsChunkMeshProxy && chunkAssetsAvailable;
        if (configWantsChunkMeshProxy && !chunkAssetsAvailable)
        {
            static bool s_logged = false;
            if (!s_logged)
            {
                s_logged = true;
                const auto caps = Assets::GetAssetCapabilities();
                Log(L"[CHUNKMESH] Chunk mesh proxy requested but asset capability unavailable; suppressing feature state=%hs installed=%hs problem=%hs\n",
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
        long chunkLogBudget = 4000;
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
        g_GenericChunkBatchLastLogTick = 0;
        g_ChunkPayloadResourceDirectories.clear();
        g_ChunkPayloadMeshExistsCache.clear();
        g_ChunkPayloadResolveFailureLogCache.clear();
        g_ChunkResolvedBindingCache.clear();
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
            {"InstallEmissionLightFixIfPossible", &InstallEmissionLightFixIfPossible},
            {"VerifyExpectedOgreExportsIfPossible", &VerifyExpectedOgreExportsIfPossible},
            {"InitializeJetFlamesConfig", &InitializeJetFlamesConfig},
            {"InitializeUnitVoConfig", &InitializeUnitVoConfig},
            // Must run before the game reaches BZRNet init: the requested UDP port
            // is only honoured while the P2P socket is still closed.
            {"InitializeBzrNetConfig", &InitializeBzrNetConfig},
            {"InstallBzrNetRouteObserverIfPossible", &InstallBzrNetRouteObserverIfPossible},
            {"EnsureInputBindingPopulateHookScaffold", &EnsureInputBindingPopulateHookScaffold},
            {"EnsureOptionsParentCtorHookScaffold", &EnsureOptionsParentCtorHookScaffold},
            {"EnsureNativeUiMainMenuDiagnosticScaffold", &EnsureNativeUiMainMenuDiagnosticScaffold},
            {"LogShimSettingsUiStatus", &LogShimSettingsUiStatus},
        };
        RunInitSteps(kLateInitSteps);
        Log(L"[MAPTRACE] Map refresh trace: %hs\n",
            (EnvFlagEnabled("OPENSHIM_TRACE_MAP_REFRESH") ||
             EnvFlagEnabled("OPENSHIM_TRACE_STEAM_MAP_REFRESH")) ? "enabled" : "disabled");
        Log(L"[PRODMENU] Builder bridge: %hs\n",
            (g_BzrFn_InitBuildItem && g_BzrFn_CleanupBuildItem && g_BzrBuildMenuRoot)
                ? (g_IsSteamExe ? "Steam ready" : "GOG ready")
                : "disabled");
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
        InstallUiManualObjectDedupeHookIfPossible();
        InstallEmissionLightFixIfPossible();
        VerifyExpectedOgreExportsIfPossible();
        InstallSceneTeardownForgetHooksIfPossible();
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


    bool SetBomberAiRangeEnabledFromBridge(bool enabled)
    {
        RetryDeferredRuntimeHooks();
        g_BomberAiRangeEnabled = enabled;
        RefreshBomberAiRangeState();
        Log(L"[MISSIONHOOK] bomber AI range override %hs (active=%hs)\n",
            enabled ? "enabled" : "disabled",
            BoolText(g_BomberAiRangeActive));
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
        g_BomberAiRangeEnabled = g_BomberAiRangeBaselineEnabled;
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

    namespace Hooks
    {

        constexpr size_t kCraftDeployStateOffset = 0x228;
        constexpr int32_t kCraftDeployedState = 2;

        constexpr uint32_t kHowitzerVftPrimary = 0x0087AD70;
        constexpr uint32_t kHowitzerVftSecondary = 0x0087AE1C;
        constexpr uint32_t kMinelayerVftPrimary = 0x0087D790;
        constexpr uint32_t kMinelayerVftSecondary = 0x0087D83C;

    }

    uint32_t __fastcall MapFilters6Rel32(void* thisPtr, void* /*edx*/)
    {
        if (!thisPtr || !g_BzrFn_MapFilter6)
            return 0;

        auto target = reinterpret_cast<uint8_t*>(thisPtr) + 0x168;
        return g_BzrFn_MapFilter6(target);
    }

    void __fastcall MapFilterOnScrollUp(void* thisPtr)
    {
        void* list = g_MapFilterListPtr ? g_MapFilterListPtr : thisPtr;
        if (EnvFlagEnabled("OPENSHIM_TRACE_MAP_REFRESH") ||
            EnvFlagEnabled("OPENSHIM_TRACE_STEAM_MAP_REFRESH"))
        {
            Log(L"[MAPTRACE] MapFilterOnScrollUp list=0x%08X this=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(list)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)));
        }
        if (list && g_BzrFn_MapFilterScrollUp)
            g_BzrFn_MapFilterScrollUp(list);
    }

    void __fastcall MapFilterOnScrollDown(void* thisPtr)
    {
        void* list = g_MapFilterListPtr ? g_MapFilterListPtr : thisPtr;
        if (EnvFlagEnabled("OPENSHIM_TRACE_MAP_REFRESH") ||
            EnvFlagEnabled("OPENSHIM_TRACE_STEAM_MAP_REFRESH"))
        {
            Log(L"[MAPTRACE] MapFilterOnScrollDown list=0x%08X this=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(list)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)));
        }
        if (list && g_BzrFn_MapFilterScrollDown)
            g_BzrFn_MapFilterScrollDown(list);
    }

    void __fastcall LegacyWorldUpdateRenderQueueHook(void* thisPtr, void* /*edx*/, void* renderQueue)
    {
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

        // Opt-in render queue structure trace. Attaches once, on the first
        // frame a world is rendered, and is inert unless
        // [Diagnostics] TraceRenderQueues is set.
        RenderQueueTraceTick(GetOgreSceneManagerRuntime());

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

        SubmitChunkProxiesToRenderQueue(renderQueue);

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
    }

    BzrNetNicknameResult SetBzrNetNicknameFromBridge(const char* nickname)
    {
        const BzrNetNicknameResult result = ApplyBzrNetNicknameAuthoritative(
            nickname, "external_bridge");
        if (IsAcceptedBzrNetNicknameResult(result))
        {
            const std::string normalized = TrimAsciiCopy(nickname ? nickname : "");
            SyncNicknameEntriesFromAuthoritativeValue(normalized.c_str());
            NetRouteRefreshHost();
            NetRouteRefreshClient();
        }
        return result;
    }

    // Authoritative local-player world position. Consumers that need to know
    // where the player actually is should use this rather than the render
    // camera, which can be a chase or satellite view a long way from them.
    // Reuses the handle -> object -> transform path the chunk proxy path
    // already depends on; no new offsets are introduced here.
    // g_BzrFn_GetPlayerHandle used to be assigned in exactly one place: inside
    // InstallJumpSnipingProbeIfRequested, which early-returns unless
    // OPENSHIM_TRACE_JUMP_SNIPING is set. Every other caller therefore got a
    // null pointer and a silent "no player" forever -- which is how the terrain
    // follow-camera rule reported aimOrigin=camera on every record while
    // claiming to anchor on the player. The address is a GOG-build constant, so
    // callers must have already established they are on that exact build; the
    // terrain proxy gates its whole worker on an exe SHA-256 match before
    // calling this.
    void ResolveLocalPlayerLookupForVerifiedGogBuild()
    {
        if (!g_BzrFn_GetPlayerHandle)
        {
            g_BzrFn_GetPlayerHandle =
                reinterpret_cast<FnGetPlayerHandle>(kGogGetPlayerHandleAddr);
        }
        if (!g_BzrFn_GameObjectGetObjByHandle)
        {
            g_BzrFn_GameObjectGetObjByHandle =
                &GameObjectFromHandleGog; // was 0x0046B160 (wrong fn; crashed)
        }
    }

    bool TryGetLocalPlayerWorldPosition(float& x, float& y, float& z)
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        if (!g_BzrFn_GetPlayerHandle || !g_BzrFn_GameObjectGetObjByHandle)
            return false;

        const int handle = g_BzrFn_GetPlayerHandle();
        if (handle == 0)
            return false;
        void* person = g_BzrFn_GameObjectGetObjByHandle(handle);
        if (!person)
            return false;

        float position[3] = {};
        if (!TryGetGameObjectWorldPosition(person, position))
            return false;
        x = position[0];
        y = position[1];
        z = position[2];
        return true;
    }

}

// Optional high-level bridge used by EXU and other companion DLLs. BZRNet/native
// details remain entirely inside OpenShim; callers receive only a stable status.
extern "C" DWORD WINAPI OpenShimImpl_SetBZRNetNickname(LPCSTR nickname)
{
    return static_cast<DWORD>(BZROpenShim::SetBzrNetNicknameFromBridge(nickname));
}
