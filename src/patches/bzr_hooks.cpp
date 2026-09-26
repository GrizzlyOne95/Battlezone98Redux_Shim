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
    using FnChunkResolve = uint32_t(__cdecl*)(void* objectPtr, uint32_t variant);
    using FnMapFilterScroll = void(__thiscall*)(void* self);
    using FnGameObjectGetTeam = int(__thiscall*)(void* thisPtr);
    using FnChunkEffectSimulate = void(__thiscall*)(void* self, float dt);
    using FnDynamicGeometryPrepare = void(__thiscall*)(void* self);
    using FnDynamicGeometrySetSquaredViewDepth =
        void(__thiscall*)(void* self, float squaredViewDepth);
    using FnRenderQueueAddRenderable =
        void(__thiscall*)(void* renderQueue, void* renderable, uint8_t queueGroup);
    using FnLegacyWorldUpdateRenderQueue = void(__thiscall*)(void* self, void* renderQueue);
    using FnPersonSimulate = void(__thiscall*)(void* thisPtr, float dt);
    // Redux's ArtilleryProcess::DoAttack is not the zero-stack-argument method
    // described by the legacy 1.5 PDB. At the machine ABI it consumes four
    // stack words (the first is the hidden/result destination) and returns with
    // `ret 0x10`. Preserve all four words when replaying the stock routine.
    using FnArtilleryDoAttack = uint32_t(__thiscall*)(void* thisPtr,
                                                      uint32_t arg0,
                                                      uint32_t arg1,
                                                      uint32_t arg2,
                                                      uint32_t arg3);
    using FnChunkEffectCreateChunk = void* (__thiscall*)(void* thisPtr,
                                                         void* objectPtr,
                                                         const float* velocity,
                                                         uint8_t preserveFlag);
    using FnChunkEffectCreateChunklet = void(__thiscall*)(void* thisPtr,
                                                          const void* positionVec,
                                                          const float* velocity,
                                                          uint8_t preserveFlag);
    using FnChunkEffectFragmentObject = void(__thiscall*)(void* thisPtr,
                                                          void* objectPtr,
                                                          const float* velocity,
                                                          uint8_t preserveFlag);

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
    using FnUiTextEntryAppendChar = uint8_t (__thiscall*)(void*, uint8_t);
    static FnUiTextEntryAppendChar g_BzrFn_TextEntryAppendChar = nullptr; // 0x007CFA70
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
    static FnChunkResolve g_BzrFn_ChunkResolve = nullptr; // 0x004E3620
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
    static FnDynamicGeometryPrepare g_BzrFn_DynamicGeometryPrepare = nullptr;
    static FnDynamicGeometrySetSquaredViewDepth
        g_BzrFn_DynamicGeometrySetSquaredViewDepth = nullptr;
    static FnRenderQueueAddRenderable g_BzrFn_RenderQueueAddRenderable = nullptr;
    static FnLegacyWorldUpdateRenderQueue g_BzrFn_LegacyWorldUpdateRenderQueue = nullptr;
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

    static FnPersonSimulate g_BzrFn_PersonSimulate = nullptr;

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
    static FnChunkEffectCreateChunk g_BzrFn_ChunkEffectCreateChunk = nullptr;
    static FnChunkEffectCreateChunklet g_BzrFn_ChunkEffectCreateChunklet = nullptr;
    static FnChunkEffectFragmentObject g_BzrFn_ChunkEffectPartialFragment = nullptr;
    static FnChunkEffectFragmentObject g_BzrFn_ChunkEffectFullFragment = nullptr;
    BuildItem* g_BzrBuildMenuRoot = nullptr;
    bool g_IsSteamExe = false;

    void* __fastcall ChunkEffectCreateChunkHook(void* thisPtr,
                                                void* /*edx*/,
                                                void* objectPtr,
                                                const float* velocity,
                                                uint8_t preserveFlag);
    void __fastcall ChunkEffectCreateChunkletHook(void* thisPtr,
                                                  void* /*edx*/,
                                                  const void* positionVec,
                                                  const float* velocity,
                                                  uint8_t preserveFlag);
    void __fastcall ChunkEffectPartialFragmentHook(void* thisPtr,
                                                   void* /*edx*/,
                                                   void* objectPtr,
                                                   const float* velocity,
                                                   uint8_t preserveFlag);
    void __fastcall ChunkEffectFullFragmentHook(void* thisPtr,
                                                void* /*edx*/,
                                                void* objectPtr,
                                                const float* velocity,
                                                uint8_t preserveFlag);


    // Formerly an anonymous namespace. A named one plus the using-directive
    // after its closing brace keeps every lookup identical, and lets the
    // translation units split out of this file (declared in
    // bzr_hooks_internal.h) share what they need. Anything meant to stay
    // file-local is `static`.
    namespace Hooks
    {
        static void InstallNicknameTextEntryInputHookIfPossible();

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
        constexpr bool kSplinterUndeadFixEnabledDefault = true;
        constexpr long kSplinterUndeadTraceBudgetDefault = 32;
        // Redux's FlagDisplay inherits a 0x28-byte GameFeature base. The old
        // BZ1 layout used +0x10/+0x14; writing those offsets in Redux corrupts
        // the base object. Redux's surviving fields are at +0x28/+0x2C.
        constexpr size_t kFlagDisplayFlagIndexOffset = 0x28;
        constexpr size_t kMultiplayerFlagMaxObjects = 512;
        // Real GOG Person::Simulate. The old 0x004F4370 was a version/string
        // builder (advisory-PDB drift); relocated by content (SNIP sig compare
        // + anim FSM). Prologue: 55 8B EC 6A FF 68 D6 C1 84 00.
        constexpr uintptr_t kGogPersonSimulateEntryAddr = 0x0059D340;
        // GetPlayerHandle() — int __cdecl(). Verified on live GOG exe: reads
        // GameObject::userObject (via 0x417C70) + playerHandle global (0x02CC2BDC),
        // round-trips through GameObjectHandle::GetObj (0x462630) / GameObject::GetHandle
        // (0x477590). This is the inner void-overload the Lua wrapper (0x4FFCD0) calls on
        // its non-numeric branch, matching the 1.5 decomp. Previous 0x00514610 was WRONG
        // (mid-instruction, same failure class as the fixed GetObjByHandle).
        constexpr uintptr_t kGogGetPlayerHandleAddr = 0x005C7FB0;
        constexpr uintptr_t kLocalPlayerNetIdAddr = 0x009180D4;
        // Returned when the net id cannot be read at all. Every SinglePlayer-tier
        // gate is written as "net id == 0", so a sentinel that is not 0 makes an
        // unreadable net id stand the feature down instead of enabling it. This
        // matches AutoSave, whose gate already treats an unreadable state as "not
        // a live single-player mission" (autosave.cpp IsSinglePlayerMissionActive).
        constexpr uint16_t kLocalPlayerNetIdUnreadable = 0xFFFFu;
        constexpr size_t kPersonSimulateDetourLen = 10;
        constexpr uint32_t kWeaponSigSnip = 0x534E4950u;
        // Live GOG Person offsets, re-derived from disassembly of the shipped
        // exe (the advisory beta PDB is drifted). Uniform +8 vs the PDB through
        // the vehicle fields, then +0x20 for the animation tail. See
        // reverse_engineering/jump_sniping_crouch_fix_20260713.md.
        constexpr size_t kPersonObjOffset = 0x0F0;          // PDB 0xE8 render obj
        constexpr size_t kGameObjectVelocityYOffset = 0x12C; // PDB 0x124 euler.v.y
        constexpr size_t kPersonVehiclePtrOffset = 0x230;   // PDB 0x228 vhcl (VEHICLE*)
        constexpr size_t kVehicleGroundFlagsOffset = 0x114; // VEHICLE flags word
        constexpr uint32_t kVehicleGroundedFlagBit = 0x80;  // set = grounded
        // Person on-foot animation state machine index (0..3), also the field
        // the crouch FSM switches on.
        constexpr size_t kPersonAnimStateOffset = 0x228;    // PDB 0x220 craft state
        constexpr size_t kPersonCurAnimOffset = 0x2A8;      // PDB 0x288
        constexpr size_t kPersonAnimHandleOffset = 0x2AC;   // PDB 0x28C
        constexpr size_t kCarrierWeaponsOffset = 0x18;
        constexpr size_t kCarrierSelectedOffset = 0x30;
        constexpr size_t kWeaponClassOffset = 0x08;
        constexpr size_t kWeaponClassSigOffset = 0x0C;
        constexpr size_t kWeaponClassOdfOffset = 0x20;
        constexpr float kJumpSnipeVelocityBandThreshold = 0.15f;

        constexpr float kSmartReticleRangeDefault = 500.0f;
        // The convergence tuning constants (minimum target distance, maximum
        // deviation from the stock aim) live alongside the math in
        // include/weapon_convergence.h.




        constexpr uintptr_t kGogChunkEffectCreateChunkAddr = 0x00492AA0;
        constexpr uintptr_t kGogChunkEffectCreateChunkletAddr = 0x004927D0;
        constexpr size_t kChunkEffectCreateChunkDetourLen = 9;
        constexpr size_t kChunkEffectCreateChunkletDetourLen = 9;
        constexpr size_t kChunkEffectCreateExpectedLen = 16;
        constexpr uintptr_t kGogChunkEffectPartialFragmentAddr = 0x00492460;
        constexpr uintptr_t kGogChunkEffectFullFragmentAddr = 0x00492640;
        constexpr size_t kChunkEffectFragmentDetourLen = 6;
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
        constexpr bool kConstructorRemoteBuildFixEnabledDefault = true;
        constexpr long kConstructorRemoteBuildTraceBudgetDefault = 32;





        enum class VerticalBand
        {
            Down,
            Flat,
            Up,
        };

        struct JumpSnipeProbeSnapshot
        {
            bool valid = false;
            int playerHandle = 0;
            void* person = nullptr;
            void* obj = nullptr;
            float velY = 0.0f;
            uint32_t animState = 0;   // on-foot anim FSM state (0..3)
            bool grounded = false;    // vhcl ground-contact flag bit
            long curAnim = 0;
            int animHandle = 0;
            uint32_t selectedMask = 0;
            int selectedSlot = -1;
            uint32_t selectedSig = 0;
            char selectedOdf[17] = {};
            bool sniperSelected = false;
        };

        struct JumpSnipeProbeLogState
        {
            bool initialized = false;
            JumpSnipeProbeSnapshot last = {};
        };


        struct ChunkObjectLinkProbe;
        struct ChunkCreateSourceTreeProbe;
        static std::filesystem::path GetChunkPayloadStockResourceDirectory();
        static void RefreshChunkPayloadResourceDirectories();
        static void PopulateChunkVdfCandidates(const char* meshName, ChunkObjectLinkProbe& probe);
        static void PopulateChunkObjectLinkProbeFromIdentityCache(ChunkObjectLinkProbe& probe);
        static bool TryInferChunkMeshNameFromGeom(
            const char* geomName,
            uint32_t classId,
            char* outMeshName,
            size_t outMeshNameCapacity);
        static void AppendAllChunkMeshBasesForGeom(
            const char* geomName,
            uint32_t classId,
            std::vector<std::string>& outMeshCandidates);
        static std::string NormalizeChunkPayloadComponentName(const char* value);
        static bool TryGetChunkProxyPosition(const uint8_t* objectBytes, float& outX, float& outY, float& outZ);
        static bool TryResolveChunkPayloadMeshResource(
            const ChunkObjectLinkProbe& probe,
            const char* preferredMeshName,
            const char* explicitGeomName,
            char* outMeshName,
            size_t outMeshNameCapacity);
        static bool ResolveChunkCreateMeshContext(
            const ChunkCreateSourceTreeProbe& probe,
            char* outMeshName,
            size_t outMeshNameCapacity);
        static bool BuildChunkVdfSourceCandidateList(
            const char* meshName,
            const ChunkObjectLinkProbe& source,
            const ChunkObjectLinkProbe& parent,
            const ChunkObjectLinkProbe& sibling,
            const ChunkObjectLinkProbe& child,
            char* outText,
            size_t outTextCapacity);
        static bool TryInferChunkMeshNameFromTree(
            const ChunkObjectLinkProbe& source,
            const ChunkObjectLinkProbe& parent,
            const ChunkObjectLinkProbe& sibling,
            const ChunkObjectLinkProbe& child,
            char* outMeshName,
            size_t outMeshNameCapacity);
        static void RefreshChunkObjectIdentityCacheIfNeeded();



        static_assert(sizeof(HudSpriteRectRecord) == kHudSpriteRectEntrySize, "Unexpected HUD sprite rect record size");

        static InlineDetour32 g_PersonSimulateDetour = {};
        static bool g_JumpSnipeProbeInstallAttempted = false;
        static bool g_JumpSnipeProbeInstalled = false;
        static bool g_JumpSnipeProbeMismatchLogged = false;
        static JumpSnipeProbeLogState g_JumpSnipeProbeLogState = {};
        bool g_ShotConvergenceEnabled = true;
        bool g_ShotConvergenceBaselineEnabled = true;
        bool g_PlayerReticleShotConvergenceEnabled = true;
        bool g_PlayerReticleShotConvergenceBaselineEnabled = true;
        float g_SmartReticleRange = kSmartReticleRangeDefault;
        float g_SmartReticleRangeBaseline = kSmartReticleRangeDefault;
        // EXU/Lua (BZP, Reloaded, etc.) own the range when they call the
        // exported setter. The MP gate must not then force stock 200 over that
        // value -- those mods apply the longer reticle in network games on
        // purpose, and every peer in a matched lobby is doing the same.
        bool g_SmartReticleRangeOwnedByBridge = false;
        bool g_SmartScavengerPathingEnabled = true;
        static bool g_TurretAimPitchBaselineEnabled = true;
        bool g_ScrapPilotHudLegacyLayoutEnabled = true;
        ULONGLONG g_ScrapPilotHudLastRefreshTick = 0;
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


        struct BzrGeoEntry
        {
            uint32_t packedKey;
            void* handle;
            uint32_t unk8;
            uint32_t unkC;
        };

        struct BzrGeoLookup
        {
            uint32_t count;
            uint32_t unk4;
            uint32_t cachedKey;
            BzrGeoEntry* entries;
        };




        struct ChunkProxyTransform
        {
            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
            OgreQuaternion orientation = { 1.0f, 0.0f, 0.0f, 0.0f };
            OgreVector3 scale = { 1.0f, 1.0f, 1.0f };
        };

#include "chunk_proxy_generic_meshes.inl"
#include "ogre_entity_frustum_cull.inl"

        struct ChunkProxySlot
        {
            const uint8_t* objectBytes = nullptr;
            const void* geomRef = nullptr;
            char geomName[64] = {};
            void* ownerEntity = nullptr;
            char ownerEntityBaseName[32] = {};
            char ownerOgreFilename[32] = {};
            char proofMeshName[128] = {};
            float positionX = 0.0f;
            float positionY = 0.0f;
            float positionZ = 0.0f;
            bool useEntryPosition = false;
            void* billboard = nullptr;
            void* sceneNode = nullptr;
            void* entity = nullptr;
            void* sceneManager = nullptr;
            void* sourceRootObject = nullptr;
            void* ownerObj = nullptr;
            void* sourceGameObject = nullptr;
            void* sourceRootGameObject = nullptr;
            DWORD lastSeenTick = 0;
            uint16_t cameraNotifyCount = 0;
            uint16_t entityUpdateQueueCount = 0;
            uint16_t renderQueueAddCount = 0;
            ChunkProxyTransform genericBatchTransform = {};
            uint8_t genericBatchKind = 0;
            bool active = false;
            bool billboardAssigned = false;
            bool meshAssigned = false;
            bool genericBatchTransformReady = false;
        };

        struct ChunkEffectActiveEntry
        {
            const uint8_t* objectBytes = nullptr;
            uint32_t reserved = 0;
            float timer = 0.0f;
            float velocityX = 0.0f;
            float velocityY = 0.0f;
            float velocityZ = 0.0f;
            float omegaX = 0.0f;
            float omegaY = 0.0f;
            float omegaZ = 0.0f;
        };

        struct ChunkObjectLinkProbe
        {
            const uint8_t* objectBytes = nullptr;
            char objectId[16] = {};
            uint32_t classId = 0;
            uint32_t flags = 0;
            void* geomRef = nullptr;
            char geomName[64] = {};
            char cachedMeshName[48] = {};
            char vdfCandidates[128] = {};
        };

        struct ChunkCreateSourceTreeProbe
        {
            bool valid = false;
            ChunkObjectLinkProbe source = {};
            ChunkObjectLinkProbe parent = {};
            ChunkObjectLinkProbe sibling = {};
            ChunkObjectLinkProbe child = {};
            // The game-side tagENTITY for the owning craft. NOT an Ogre object:
            // it is only good for reading names off fixed offsets.
            void* ownerEntity = nullptr;
            // The craft's Ogre::Entity, reached through the render bridge. This
            // is the one that accepts Ogre calls (getSkeleton, setVisible, ...).
            void* ownerOgreEntity = nullptr;
            char ownerEntityBaseName[32] = {};
            char ownerOgreFilename[32] = {};
            char ownerResolvedMeshName[48] = {};
        };

        static bool g_EnableChunkRenderFallback = false;
        static bool g_EnableChunkProxyDebug = false;
        static bool g_EnableChunkMeshProxy = false;
        static bool g_EnableGenericChunkBatch = false;
        static bool g_EnablePartialFragmentBoneCollapse = false;
        // Guards against a craft mesh with an implausible bone count being walked.
        static constexpr uint16_t kMaxOwnerSkeletonBones = 1024;
        // Building geo nodes carry no owner GameObject link (+0x8C is null),
        // so chunks born from a building can't identify their craft through
        // the bridge. The fragment ROOT still can. FragmentObject calls
        // CreateChunk synchronously on the same thread, so the root's
        // resolved mesh name is handed down through this scoped global while
        // the walk is on the stack.
        static char g_ActiveFragmentSourceMeshName[48] = {};
        // The craft's Ogre::Entity for the fragment walk currently on the stack.
        // Geo nodes below the root do not carry a bridge link of their own, so
        // the entity is resolved once at the root and handed down the same way
        // the mesh name is.
        static void* g_ActiveFragmentSourceOgreEntity = nullptr;
        static const char* g_ActiveFragmentSourceOgreEntityVia = "none";
        // ODF name of the craft being fragmented, read off its GameObject class.
        // The tagENTITY name probe never resolved a real name, so this is the
        // only stated (rather than inferred) identity the payload lookup gets.
        static char g_ActiveFragmentSourceOdfName[16] = {};
        // Set only while PartialFragmentObject is on the stack. Full fragmentation
        // hides the whole source mesh instead, so per-piece bone collapse there
        // would be wasted work on an already-invisible entity.
        static bool g_ActivePartialFragment = false;
        static bool g_TraceChunkRender = false;
        static bool g_TraceChunkRenderVerbose = false;
        static bool g_TraceChunkEffectRuntime = false;
        bool g_TraceSatelliteVisibility = false;
        static uint32_t g_LastChunkEffectLoggedCount = UINT32_MAX;
        static volatile long g_ChunkRenderLogBudget = 12;
        // 8 was sized for an opt-in probe and burns out after 8 seconds of
        // cumulative satellite viewing -- far too few to walk the validation
        // matrix now that the trace defaults on. Budget is consumed only while
        // the overview is actually open and is rate-limited to one sample per
        // g_SatelliteVisibilityLogIntervalMs.
        volatile long g_SatelliteVisibilityLogBudget = 120;
        static uint32_t g_ChunkTraceEntryLimit = 32;
        // 96 slots exhaust in multi-craft battles (each death emits ~10 geo
        // pieces plus impact chunklets); once full, new chunks are silently
        // dropped until a slot expires.
        static uint32_t g_ChunkProxyCapacity = 256;
        static float g_ChunkProxyDebugSize = 2.5f;
        uint32_t g_SatelliteVisibilityObjectLimit = 96;
        DWORD g_SatelliteVisibilityLastTick = 0;
        DWORD g_SatelliteVisibilityLogIntervalMs = 1000;
        static std::unordered_map<uintptr_t, uint32_t> g_ChunkObservedClassIds = {};
        struct ChunkVdfRecord
        {
            char name[16] = {};
            char parent[16] = {};
            uint32_t type = 0;
            uint32_t flags = 0;
        };

        struct ChunkVdfAssetInfo
        {
            bool attempted = false;
            bool loaded = false;
            std::vector<ChunkVdfRecord> records = {};
        };

        struct ChunkObjectIdentityCacheEntry
        {
            char meshName[48] = {};
            char vdfCandidates[128] = {};
            char geomName[64] = {};
            uint32_t classId = 0;
        };

        struct ChunkResolvedBindingEntry
        {
            char meshName[48] = {};
            char payloadMeshName[128] = {};
            char vdfCandidates[128] = {};
            uint32_t sourceClassId = 0;
            uint32_t sourceRootObjectPtr = 0;
            uint32_t sourceOwnerEntityPtr = 0;
            uint32_t sourceOwnerObjPtr = 0;
            uint32_t sourceGameObjectPtr = 0;
            uint32_t sourceRootGameObjectPtr = 0;
            char sourceGeomName[64] = {};
            DWORD bindTick = 0;
            DWORD lastSeenTick = 0;
        };

        static std::unordered_map<std::string, ChunkVdfAssetInfo> g_ChunkVdfAssetCache = {};
        // Distributable replacement for shipping the stock VDF/SDF files:
        // a text manifest holding just the geo-piece names/hierarchy, seeded
        // into g_ChunkVdfAssetCache before any Edit\stock fallback runs.
        static bool g_ChunkGeoManifestAttempted = false;
        static constexpr const char* kChunkGeoManifestFileName = "chunk_geo_manifest.txt";
        static std::unordered_map<uintptr_t, ChunkObjectIdentityCacheEntry> g_ChunkObjectIdentityCache = {};
        static std::unordered_map<uintptr_t, ChunkResolvedBindingEntry> g_ChunkResolvedBindingCache = {};
        static std::unordered_map<std::string, bool> g_ChunkPayloadMeshExistsCache = {};
        static std::unordered_set<std::string> g_ChunkPayloadResolveFailureLogCache = {};
        static DWORD g_ChunkObjectIdentityLastRefreshTick = 0;
        static DWORD g_ChunkResolvedBindingLastPruneTick = 0;
        bool g_VehicleSkinningTraceEnabled = false;
        DWORD g_VehicleSkinningTraceIntervalMs = 5000;
        DWORD g_VehicleSkinningTraceLastTick = 0;
        volatile long g_VehicleSkinningTraceBudget = 64;
        std::unordered_set<std::string> g_VehicleSkinningTraceFingerprints = {};
        struct ChunkVdfMeshRef
        {
            char meshBase[48] = {};
            uint32_t type = 0;
        };

        static bool g_ChunkVdfReverseIndexAttempted = false;
        static std::unordered_map<std::string, std::vector<ChunkVdfMeshRef>> g_ChunkVdfGeomReverseIndex = {};
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
        static InlineDetour32 g_TextEntryAppendCharDetour = {};
        static FnUiTextEntryAppendChar g_BzrFn_TextEntryAppendCharOriginal = nullptr;
        bool g_LobbyNicknameInputHookInstalled = false;
        static bool g_LobbyNicknameInputHookFailureLogged = false;
        void* g_ActiveNicknameEntry = nullptr;
        void* g_ActiveNicknameParent = nullptr;
        void* g_NicknameEnterDispatchEntry = nullptr;
        void* g_PendingNicknameConfirmationEntry = nullptr;
        BzrNetNicknameResult g_PendingNicknameConfirmationResult =
            BzrNetNicknameResult::StoredForNextConnection;
        bool g_ReplaceNicknameOnNextInput = false;
        static volatile long g_NicknameInputTraceBudget = 16;
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
        static InlineDetour32 g_DynamicGeometryPrepareDetour = {};
        static InlineDetour32 g_DynamicGeometrySetSquaredViewDepthDetour = {};
        static bool g_DynamicAlphaDepthBatchingEnabled = true;
        static uint32_t g_DynamicAlphaDepthBucketStride = 8;
        thread_local bool g_InDynamicGeometryQueueUpdate = false;
        thread_local uint32_t g_DynamicGeometryQueuedBatches = 0;
        thread_local uint32_t g_DynamicGeometryMergeableBatches = 0;
        thread_local uint32_t g_DynamicGeometryBlendedBatches = 0;
        thread_local uint64_t g_DynamicGeometryQueuedVertices = 0;
        thread_local uint64_t g_DynamicGeometryQueuedIndices = 0;
        static constexpr size_t kDynamicGeometryMaterialSampleCapacity = 64;
        thread_local uintptr_t
            g_DynamicGeometryMaterialSamples[kDynamicGeometryMaterialSampleCapacity] = {};
        thread_local uint32_t
            g_DynamicGeometryMaterialBatchCounts[kDynamicGeometryMaterialSampleCapacity] = {};
        thread_local uint32_t
            g_DynamicGeometryMaterialBlendedCounts[kDynamicGeometryMaterialSampleCapacity] = {};
        thread_local uint32_t g_DynamicGeometryDistinctMaterials = 0;

        static InlineDetour32 g_ChunkEffectCreateChunkDetour = {};
        static InlineDetour32 g_ChunkEffectCreateChunkletDetour = {};
        static bool g_ChunkEffectCreateHooksInstalled = false;
        static bool g_ChunkEffectCreateHooksLogged = false;
        static InlineDetour32 g_ChunkEffectPartialFragmentDetour = {};
        static InlineDetour32 g_ChunkEffectFullFragmentDetour = {};
        static bool g_ChunkEffectFragmentHooksInstalled = false;
        static bool g_ChunkEffectFragmentHooksLogged = false;
        static int g_ChunkFragmentHookDepth = 0;
        static bool g_AllowUnsafeSteamChunkCreateHooks = false;
        static bool g_ChunkEffectCreateHooksWaitLogged = false;
        static bool g_ChunkEffectCreateHooksMismatchLogged = false;
        static ULONGLONG g_ChunkEffectCreateHooksReadyTick = 0;
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

        // [Fixes] multiplayer gate. Each of these seven corrects a confirmed
        // Redux defect, but all seven change simulation behaviour, and none of
        // them is negotiated with peers -- so in a lobby that mixes OpenShim and
        // stock clients the two machines would run different code for the same
        // object. The `Enabled` flag above stays the user's openshim.ini answer
        // and still decides whether the hook/patch is installed at all; the
        // `Active` flag below is that answer reconciled against the live net id
        // by the feature registry, and it is what each hook body tests. Install
        // is deliberately NOT gated on Active: the hook has to already be in
        // place when a mission goes from single-player to a network game.
        bool g_TugCargoPostLoadFixActive = true;
        bool g_ConstructorRecycleStaleTargetFixActive = true;
        bool g_SplinterUndeadFixActive = kSplinterUndeadFixEnabledDefault;
        bool g_ConstructorRemoteBuildFixActive = kConstructorRemoteBuildFixEnabledDefault;
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
        static constexpr uintptr_t kOgreSceneManagerOffset = 0x08;
        static constexpr uintptr_t kChunkEffectActiveCountOffset = 0x8028;
        static constexpr uintptr_t kChunkEffectGateOffset = 0x802C;
        static constexpr uintptr_t kChunkEffectTuningBaseOffset = 0x8038;
        static constexpr uintptr_t kChunkEffectTemplateListOffset = 0x8050;
        static constexpr uintptr_t kChunkEffectEntryBaseOffset = 0x28;
        static constexpr uintptr_t kChunkEffectVtableSimulateSlotAddr = 0x0087708C;
        static constexpr uintptr_t kChunkObjGeomRefOffset = 0x64;
        // The advisory-PDB object-list/userObject/userTeam globals that used
        // to live here (0x50D2F0/F8/E4) landed in string data on the live exe
        // and were removed 2026-07-18. Verified replacements: userObject
        // global 0x00917AFC (EngineGlobals::UserObjectSlot, accessor 0x417C70),
        // object enumeration via the 0x0260DB20 arena
        // (CollectLiveGameObjectsFromArena), team via
        // GetGameObjectActualTeam(userObject).
        static constexpr size_t kChunkEffectEntrySize = 0x20;
        static constexpr uint32_t kClassIdChunk = 53;
        static constexpr DWORD kChunkProxyExpireMs = 400;
        static constexpr DWORD kChunkProxyRetryDelayMs = 1000;
        static constexpr DWORD kChunkObjectIdentityRefreshMs = 1000;
        static constexpr DWORD kVehicleSkinningTraceIntervalMsDefault = 5000;
        static constexpr DWORD kVehicleSkinningTraceIntervalMsMin = 100;
        static constexpr DWORD kVehicleSkinningTraceIntervalMsMax = 60000;
        static constexpr long kVehicleSkinningTraceBudgetDefault = 64;
        static constexpr DWORD kChunkResolvedBindingExpireMs = 10000;
        static constexpr DWORD kChunkResolvedBindingPruneMs = 1000;
        static constexpr size_t kChunkPayloadResolveFailureLogCacheLimit = 512;
        static constexpr size_t kChunkObjectIdentityMaxNodesPerObject = 256;
        static constexpr float kChunkProxyEntryPositionTolerance = 256.0f;
        static constexpr float kChunkProxyLocalTransformTolerance = 0.001f;
        static constexpr float kChunkProxyAnchoredTransformAdoptDistance = 1.0f;
        static constexpr float kChunkProxyHiddenY = -100000.0f;
        static constexpr const char* kChunkProxyBillboardSetName = "OpenShimChunkProxyDebug";
        static constexpr const char* kChunkProxyMaterialName = "BaseWhiteNoLighting";
        static constexpr const char* kChunkProxyMaterialGroup = "General";
        static constexpr const char* kChunkPayloadResourceRootName = "OpenShimChunkPayloads";
        static constexpr const char* kChunkPayloadModRelativeDirName = "chunkMeshes";
        static constexpr const char* kChunkPayloadModRelativeDirNameAlt = "Chunks";
        static constexpr const char* kChunkPayloadResourceLocationType = "FileSystem";
        // Resolved by ResolveBzrHooks from scripts/patches.json
        // ("PlayGlobalSound"); null until then, and the caller checks.
        FnPlayGlobalSound g_BzrFn_PlayGlobalSound = nullptr;
        static constexpr bool kBomberAiRangeEnabledDefault = false;
        static constexpr bool kHowitzerVolleyEnabledDefault = false;
        static constexpr bool kHowitzerUndeployedRetaliationFixEnabledDefault = true;
        // Confirmed Redux defect: damage from a GameObject-owned child reveals
        // only that immediate child, leaving its owning craft disguised.
        // This restores the ownership walk for landed hits. It is gated out of
        // network games because perceivedTeam participates in simulation.
        static constexpr bool kOwnedObjectRevealFixEnabledDefault = true;
        static constexpr long kOwnedObjectRevealTraceBudgetDefault = 96;
        static constexpr bool kWeaponMaskCarrierBiasEnabledDefault = false;
        // Master switch for the ODF-authored AI tuning keys (engageRangeAI,
        // weaponRangeMinAI, retargetPeriodAI, scrapPathingAI and friends).
        // Defaults ON: every path it gates additionally requires the ODF to
        // declare one of those keys, so content that does not author them --
        // the stock campaign included -- is completely unaffected.
        static constexpr bool kAiOdfGameplayTuningEnabledDefault = true;
        static constexpr bool kTurretAimPitchEnabledDefault = true;
        static constexpr long kAttackRevealTraceBudgetDefault = 64;
        // Global single-player improvement. The exact-byte and live-net-id
        // guards still keep it off unsupported builds and multiplayer.
        static constexpr bool kJumpSnipeCrouchEnabledDefault = true;
        // Enhancement rather than a defect fix, and it changes projectile
        // physics for every shot in the world, so it ships OFF under the
        // [SinglePlayer] policy and is hard-disabled in network games.
        static constexpr bool kOrdnanceVelocityInheritanceDefault = false;
        static constexpr bool kAllowNeutralAttackOrdersDefault = false;
        bool g_AllowNeutralAttackOrders = kAllowNeutralAttackOrdersDefault;
        // Pure instrumentation for the AIP construction program. Off by default
        // because it prints one line per AIP item name plus a one-shot dump of
        // the whole prereq universe; nothing about the game changes either way.
        static constexpr bool kAipResolveTraceDefault = false;
        bool g_AipResolveTraceEnabled = kAipResolveTraceDefault;
        // Always-on fix: give a built class every producer that can make it,
        // instead of only the first one InitObjectClasses happened to reach.
        static constexpr bool kAiMultiProducerMakersDefault = true;
        bool g_AiMultiProducerMakersEnabled = kAiMultiProducerMakersDefault;
        static bool g_BomberAiRangeBaselineEnabled = kBomberAiRangeEnabledDefault;
        static bool g_BomberAiRangeEnabled = kBomberAiRangeEnabledDefault;
        // Configured value AND'd with the single-player gate, same contract as
        // g_AiOdfGameplayTuningActive below. This feature changes stock content
        // (it raises bomber engagement range from the craft's own weapon ODFs),
        // so it must never reach a network game.
        bool g_BomberAiRangeActive = false;
        bool g_HowitzerVolleyEnabled = kHowitzerVolleyEnabledDefault;
        static bool g_HowitzerUndeployedRetaliationFixEnabled =
            kHowitzerUndeployedRetaliationFixEnabledDefault;
        // See the [Fixes] multiplayer gate note above.
        bool g_HowitzerUndeployedRetaliationFixActive =
            kHowitzerUndeployedRetaliationFixEnabledDefault;
        bool g_OwnedObjectRevealFixEnabled =
            kOwnedObjectRevealFixEnabledDefault;
        bool g_OwnedObjectRevealFixActive =
            kOwnedObjectRevealFixEnabledDefault;
        volatile long g_OwnedObjectRevealTraceBudget =
            kOwnedObjectRevealTraceBudgetDefault;
        bool g_WeaponMaskCarrierBiasEnabled = kWeaponMaskCarrierBiasEnabledDefault;
        bool g_AiWeaponMaskArtilleryEnabled = kAiWeaponMaskArtilleryEnabledDefault;
        bool g_AiWeaponMaskMinelayerEnabled = kAiWeaponMaskMinelayerEnabledDefault;
        static bool g_AiOdfGameplayTuningBaselineEnabled = kAiOdfGameplayTuningEnabledDefault;
        static bool g_AiOdfGameplayTuningEnabled = kAiOdfGameplayTuningEnabledDefault;
        bool g_AiOdfGameplayTuningActive = false;
        static bool g_TurretAimPitchEnabled = kTurretAimPitchEnabledDefault;
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
        static DWORD g_ChunkProxyLastRetryTick = 0;
        static bool g_ChunkProxyInitLogged = false;
        static bool g_ChunkProxyFailureLogged = false;
        static bool g_ChunkProxyWaitLogged = false;
        static DWORD g_ChunkMeshProxyLastRetryTick = 0;
        static bool g_ChunkMeshProxyInitLogged = false;
        static bool g_ChunkMeshProxyFailureLogged = false;
        static bool g_ChunkMeshProxyWaitLogged = false;
        static bool g_ChunkPayloadResourceLocationsAttempted = false;
        static bool g_ChunkPayloadResourceLocationsReady = false;
        static bool g_ChunkPayloadResourceLocationsLogged = false;
        static bool g_ChunkPayloadResourceLocationsFailureLogged = false;
        static std::vector<std::filesystem::path> g_ChunkPayloadResourceDirectories = {};
        static void* g_ChunkProxyBillboardSet = nullptr;
        static std::vector<ChunkProxySlot> g_ChunkProxySlots = {};
        static void* g_GenericChunkBatchManualObject = nullptr;
        static void* g_GenericChunkBatchSceneNode = nullptr;
        static void* g_GenericChunkBatchSceneManager = nullptr;
        static bool g_GenericChunkBatchSectionCreated = false;
        static bool g_GenericChunkBatchRuntimeAvailable = true;
        static int g_GenericChunkBatchEligibility[2] = { -1, -1 };
        static DWORD g_GenericChunkBatchLastLogTick = 0;
        // Bounded diagnostics for the per-frame submission question: the game
        // drives its _updateRenderQueue override more than once per frame (one
        // traversal per active material scheme), and the ManualObject is also
        // attached to the scene graph, so the number of rebuilds and the number
        // of render-queue submissions per frame must be counted, not assumed.
        static bool g_GenericChunkBatchRateDiagnostics = false;
        static uint64_t g_GenericChunkBatchSubmitCalls = 0;
        // Counts successful *submissions*, not geometry rebuilds. Since
        // state-version reuse landed those are different numbers: the rebuild
        // count lives in g_GenericChunkBatchTelemetry.
        static uint64_t g_GenericChunkBatchRebuilds = 0;
        static DWORD g_GenericChunkBatchRateLogTick = 0;
        static uint64_t g_GenericChunkBatchSubmitCallsAtLastLog = 0;
        static uint64_t g_GenericChunkBatchRebuildsAtLastLog = 0;
        // State-version reuse. The batch is re-submitted to every camera/scheme
        // traversal, but the geometry is only re-emitted when the slot state it
        // is built from actually differs. See include/chunk_batch_invalidation.h
        // for why the version is derived from the source rather than declared by
        // its mutators.
        static bool g_GenericChunkBatchReuseEnabled = true;
        // Observer mode: take the decision and count it, then rebuild anyway.
        // This is how the pre-optimization baseline and the dedup opportunity
        // are measured from the same binary, without changing what is drawn.
        static bool g_GenericChunkBatchReuseObserveOnly = false;
        static uint64_t g_GenericChunkBatchBuiltVersion =
            ChunkBatchInvalidation::kUnbuiltVersion;
        static std::string g_GenericChunkBatchBuiltMaterial = {};
        static ChunkBatchInvalidation::Telemetry g_GenericChunkBatchTelemetry = {};
        static ChunkBatchInvalidation::Telemetry g_GenericChunkBatchTelemetryAtLastLog = {};
        static int64_t g_GenericChunkBatchQpcFrequency = 0;
        // Last visibility written to the batch object, so setVisible is only
        // called on a transition. Without this the empty path would push
        // setVisible(false) three times per frame for as long as there is no
        // debris, which is most of a normal mission.
        static bool g_GenericChunkBatchVisible = false;
        static const std::string g_GenericChunkBatchMaterialName = "scarpmat2";
        static const std::string g_GenericChunkBatchMaterialGroup = "General";
        // TEST/DIAGNOSTIC seam only. Set by the environment gate below and
        // never by gameplay: RebuildAndSubmitGenericChunkBatch() reports
        // failure once the slots are already classified batch-ready, which is
        // precisely the window the per-Entity fallback has to cover.
        static bool g_ForceGenericChunkBatchFailure = false;
        // TEST/DIAGNOSTIC seam only. ChunkProxyTransform::scale is structurally
        // unit today (the legacy basis vectors are normalised when the
        // quaternion is built), so the unit-scale gate below has no natural
        // trigger. This forces a non-unit scale on tracked generic chunks so
        // the rejection and per-Entity fallback can actually be exercised.
        static bool g_ForceGenericChunkNonUnitScale = false;
        // Bounded diagnostics. A mod or future runtime that gives a stock
        // chunk1/chunk2 a non-unit transform scale would otherwise be batched
        // with the scale silently dropped, so count the rejections instead of
        // logging one line per chunk per frame.
        static uint64_t g_GenericChunkBatchNonUnitScaleRejections = 0;
        static DWORD g_GenericChunkBatchScaleLogTick = 0;
        static uint64_t g_GenericChunkBatchRehydrations = 0;
        static DWORD g_GenericChunkBatchRehydrateLogTick = 0;

        // Render-pass procs captured at hook time when available; the mangled
        // export fallback in TrySubmitChunkMeshProxyToCurrentRenderQueue covers
        // the case where these were never observed.
        static FnOgreMovableObjectNotifyCurrentCamera g_OgreFn_MovableObjectNotifyCurrentCamera = nullptr;
        static FnOgreEntityUpdateRenderQueue g_OgreFn_EntityUpdateRenderQueue = nullptr;



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
            if (mbi.State != MEM_COMMIT || !IsReadableDataProtect(mbi.Protect))
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

        static void LogChunkDiagnostic(const char* component, const wchar_t* fmt, ...)
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


        static bool AcquireChunkLogSlot()
        {
            if (g_TraceChunkRenderVerbose)
                return true;

            return InterlockedDecrement(&g_ChunkRenderLogBudget) >= 0;
        }

        static bool TryReadAsciiString(const char* address, char* outText, size_t outTextCapacity)
        {
            if (!address || !outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';

            __try
            {
                size_t index = 0;
                for (; index + 1 < outTextCapacity; ++index)
                {
                    const unsigned char ch = static_cast<unsigned char>(address[index]);
                    if (ch == 0)
                    {
                        outText[index] = '\0';
                        return index > 0;
                    }

                    if (ch < 0x20 || ch > 0x7E)
                    {
                        outText[0] = '\0';
                        return false;
                    }

                    outText[index] = static_cast<char>(ch);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outText[0] = '\0';
                return false;
            }

            outText[outTextCapacity - 1] = '\0';
            return false;
        }

        // Legacy geo names live in a fixed 8-byte field that is NOT
        // NUL-terminated when the name is exactly 8 chars (e.g. "scz11bda"
        // is immediately followed by the geom back-pointer); shorter names
        // are NUL-padded ("chunk2\0\0"). Read at most 8 chars and accept
        // hitting the field boundary without a terminator.
        static bool TryReadLegacyGeoNameField(const char* address, char* outText, size_t outTextCapacity)
        {
            if (!address || !outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';

            __try
            {
                const size_t kFieldLen = 8;
                size_t index = 0;
                for (; index < kFieldLen && index + 1 < outTextCapacity; ++index)
                {
                    const unsigned char ch = static_cast<unsigned char>(address[index]);
                    if (ch == 0)
                        break;

                    if (ch < 0x20 || ch > 0x7E)
                    {
                        outText[0] = '\0';
                        return false;
                    }

                    outText[index] = static_cast<char>(ch);
                }

                outText[index] = '\0';
                return index > 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outText[0] = '\0';
                return false;
            }
        }

        static bool TryReadInlineAsciiBuffer(
            const void* address,
            size_t maxInlineBytes,
            char* outText,
            size_t outTextCapacity)
        {
            if (!address || !outText || outTextCapacity == 0 || maxInlineBytes == 0)
                return false;

            outText[0] = '\0';

            __try
            {
                const auto* textBytes = reinterpret_cast<const unsigned char*>(address);
                size_t index = 0;
                for (; index < maxInlineBytes && index + 1 < outTextCapacity; ++index)
                {
                    const unsigned char ch = textBytes[index];
                    if (ch == 0)
                    {
                        outText[index] = '\0';
                        return index > 0;
                    }

                    if (ch < 0x20 || ch > 0x7E)
                    {
                        outText[0] = '\0';
                        return false;
                    }

                    outText[index] = static_cast<char>(ch);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outText[0] = '\0';
                return false;
            }

            outText[outTextCapacity - 1] = '\0';
            return outText[0] != '\0';
        }

        static bool IsLikelyChunkGeomName(const char* text)
        {
            if (!text || !*text)
                return false;

            size_t length = 0;
            bool hasAlpha = false;
            for (const unsigned char* cursor = reinterpret_cast<const unsigned char*>(text); *cursor; ++cursor)
            {
                const unsigned char ch = *cursor;
                if (!(std::isalnum(ch) || ch == '_' || ch == '-'))
                    return false;

                if (std::isalpha(ch))
                    hasAlpha = true;

                ++length;
                if (length > 15)
                    return false;
            }

            if (!hasAlpha || length < 4)
                return false;

            return _strnicmp(text, "chunk", 5) == 0 ||
                   _strnicmp(text, "agr", 3) == 0;
        }

        static bool TryProbeChunkGeomName(
            const uint8_t* geomBytes,
            char* outGeomName,
            size_t outGeomNameCapacity)
        {
            if (!geomBytes || !outGeomName || outGeomNameCapacity == 0)
                return false;

            outGeomName[0] = '\0';

            constexpr uintptr_t kGeomPointerProbeOffsets[] = {
                0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C, 0x20,
                0x24, 0x28, 0x2C, 0x30, 0x34, 0x38, 0x3C, 0x40
            };
            constexpr uintptr_t kGeomInlineProbeOffsets[] = {
                0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C,
                0x20, 0x24, 0x28, 0x2C, 0x30, 0x34, 0x38, 0x3C
            };

            char candidate[64] = {};

            for (uintptr_t offset : kGeomPointerProbeOffsets)
            {
                const char* candidatePtr = nullptr;
                __try
                {
                    candidatePtr = *reinterpret_cast<const char* const*>(geomBytes + offset);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    candidatePtr = nullptr;
                }

                if (!candidatePtr)
                    continue;

                if (TryReadAsciiString(candidatePtr, candidate, sizeof(candidate)) &&
                    IsLikelyChunkGeomName(candidate))
                {
                    strncpy_s(outGeomName, outGeomNameCapacity, candidate, _TRUNCATE);
                    return true;
                }
            }

            for (uintptr_t offset : kGeomInlineProbeOffsets)
            {
                if (TryReadInlineAsciiBuffer(geomBytes + offset, 16, candidate, sizeof(candidate)) &&
                    IsLikelyChunkGeomName(candidate))
                {
                    strncpy_s(outGeomName, outGeomNameCapacity, candidate, _TRUNCATE);
                    return true;
                }
            }

            return false;
        }

        static bool TryReadObjProjectId(
            const uint8_t* objectBytes,
            char* outText,
            size_t outTextCapacity)
        {
            if (!objectBytes || !outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';

            __try
            {
                size_t index = 0;
                for (; index < 8 && index + 1 < outTextCapacity; ++index)
                {
                    const unsigned char rawCh = objectBytes[index];
                    const unsigned char ch = rawCh & 0x7F;
                    if (ch == 0)
                        break;

                    if (!(std::isalnum(ch) || ch == '_' || ch == '-'))
                    {
                        outText[0] = '\0';
                        return false;
                    }

                    outText[index] = static_cast<char>(ch);
                }

                outText[index] = '\0';
                return index > 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outText[0] = '\0';
                return false;
            }
        }

        static bool BuildChunkOwnerMeshName(
            const char* ownerEntityBaseName,
            const char* ownerOgreFilename,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';

            const char* preferredName =
                (ownerOgreFilename && *ownerOgreFilename) ? ownerOgreFilename :
                ((ownerEntityBaseName && *ownerEntityBaseName) ? ownerEntityBaseName : nullptr);
            if (!preferredName || !*preferredName)
                return false;

            if (strchr(preferredName, '.') != nullptr)
            {
                strncpy_s(outMeshName, outMeshNameCapacity, preferredName, _TRUNCATE);
                return true;
            }

            _snprintf_s(outMeshName, outMeshNameCapacity, _TRUNCATE, "%s.mesh", preferredName);
            return outMeshName[0] != '\0';
        }

        // The owner-name offsets below are guesses across two candidate tagENTITY
        // layouts, and TryReadInlineAsciiBuffer accepts any printable ASCII. That
        // is too weak: an avtank's entity holds the bytes "cd=@" at the first
        // probed offset, which sailed through as a name and became "cd=@.mesh".
        // A bogus name is worse than no name, because a resolved owner mesh wins
        // over every downstream fallback -- it suppressed the VDF candidate list
        // and dropped every avtank chunk onto the generic placeholder payloads.
        // Model names are identifiers, so hold candidates to that shape.
        static bool IsPlausibleOwnerEntityName(const char* text)
        {
            if (!text || !*text)
                return false;

            size_t length = 0;
            size_t alphaNumeric = 0;
            size_t dots = 0;
            for (const unsigned char* cursor = reinterpret_cast<const unsigned char*>(text); *cursor; ++cursor)
            {
                const unsigned char ch = *cursor;
                if (std::isalnum(ch))
                {
                    ++alphaNumeric;
                }
                else if (ch == '.')
                {
                    // One extension separator at most, and never leading.
                    if (++dots > 1 || length == 0)
                        return false;
                }
                else if (ch != '_' && ch != '-')
                {
                    return false;
                }

                ++length;
                if (length > 24)
                    return false;
            }

            // "avtank", "avfigh.mesh" pass; "cd=@", "a", "12" do not.
            return length >= 3 && alphaNumeric >= 3 && std::isalpha(static_cast<unsigned char>(text[0]));
        }

        // Takes the first offset whose contents actually look like a name instead
        // of short-circuiting on the first offset that holds any readable ASCII.
        static bool TryReadOwnerEntityNameField(
            const uint8_t* entityBytes,
            const uintptr_t* probeOffsets,
            size_t probeOffsetCount,
            char* outText,
            size_t outTextCapacity)
        {
            if (!entityBytes || !probeOffsets || !outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';

            char candidate[32] = {};
            for (size_t index = 0; index < probeOffsetCount; ++index)
            {
                if (!TryReadInlineAsciiBuffer(
                        entityBytes + probeOffsets[index],
                        16,
                        candidate,
                        sizeof(candidate)))
                {
                    continue;
                }

                if (!IsPlausibleOwnerEntityName(candidate))
                    continue;

                strncpy_s(outText, outTextCapacity, candidate, _TRUNCATE);
                return true;
            }

            return false;
        }

        static bool TryReadOwnerEntityNames(
            const void* ownerEntity,
            char* outEntityBaseName,
            size_t outEntityBaseNameCapacity,
            char* outOgreFilename,
            size_t outOgreFilenameCapacity,
            char* outResolvedMeshName,
            size_t outResolvedMeshNameCapacity)
        {
            if (outEntityBaseName && outEntityBaseNameCapacity > 0)
                outEntityBaseName[0] = '\0';
            if (outOgreFilename && outOgreFilenameCapacity > 0)
                outOgreFilename[0] = '\0';
            if (outResolvedMeshName && outResolvedMeshNameCapacity > 0)
                outResolvedMeshName[0] = '\0';

            if (!ownerEntity)
                return false;

            char entityBaseName[32] = {};
            char ogreFilename[32] = {};

            // The current best-effort corpora disagree on the inline string offsets for
            // tagENTITY. Probe both candidate layouts and keep whichever yields a name.
            static constexpr uintptr_t kBaseNameProbeOffsets[] = { 0xC4, 0x84 };
            static constexpr uintptr_t kFilenameProbeOffsets[] = { 0xD4, 0x94 };

            const auto* entityBytes = reinterpret_cast<const uint8_t*>(ownerEntity);
            const bool baseRead = TryReadOwnerEntityNameField(
                entityBytes,
                kBaseNameProbeOffsets,
                _countof(kBaseNameProbeOffsets),
                entityBaseName,
                sizeof(entityBaseName));
            const bool fileRead = TryReadOwnerEntityNameField(
                entityBytes,
                kFilenameProbeOffsets,
                _countof(kFilenameProbeOffsets),
                ogreFilename,
                sizeof(ogreFilename));

            if (outEntityBaseName && outEntityBaseNameCapacity > 0 && baseRead)
                strncpy_s(outEntityBaseName, outEntityBaseNameCapacity, entityBaseName, _TRUNCATE);
            if (outOgreFilename && outOgreFilenameCapacity > 0 && fileRead)
                strncpy_s(outOgreFilename, outOgreFilenameCapacity, ogreFilename, _TRUNCATE);

            if (outResolvedMeshName && outResolvedMeshNameCapacity > 0)
                BuildChunkOwnerMeshName(entityBaseName, ogreFilename, outResolvedMeshName, outResolvedMeshNameCapacity);

            return baseRead || fileRead;
        }

        static bool TryReadChunkGeomIdentity(
            const uint8_t* objectBytes,
            const void*& outGeomRef,
            char* outGeomName,
            size_t outGeomNameCapacity)
        {
            outGeomRef = nullptr;
            if (outGeomName && outGeomNameCapacity > 0)
                outGeomName[0] = '\0';

            if (!objectBytes)
                return false;

            __try
            {
                outGeomRef = *reinterpret_cast<void* const*>(objectBytes + kChunkObjGeomRefOffset);
                if (!outGeomRef || !outGeomName || outGeomNameCapacity == 0)
                    return true;

                const auto* geomBytes = reinterpret_cast<const uint8_t*>(outGeomRef);
                const char* const geomNamePtr = *reinterpret_cast<const char* const*>(geomBytes + 0x0);
                if (!TryReadLegacyGeoNameField(geomNamePtr, outGeomName, outGeomNameCapacity) ||
                    !outGeomName[0])
                {
                    TryProbeChunkGeomName(geomBytes, outGeomName, outGeomNameCapacity);
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outGeomRef = nullptr;
                if (outGeomName && outGeomNameCapacity > 0)
                    outGeomName[0] = '\0';
                return false;
            }
        }

        static bool TryReadFloat3(const float* values, float& outX, float& outY, float& outZ)
        {
            outX = 0.0f;
            outY = 0.0f;
            outZ = 0.0f;
            if (!values)
                return false;

            __try
            {
                outX = values[0];
                outY = values[1];
                outZ = values[2];
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outX = 0.0f;
                outY = 0.0f;
                outZ = 0.0f;
                return false;
            }
        }

        static bool TryReadChunkObjectSummary(
            const uint8_t* objectBytes,
            uint32_t& outClassId,
            uint32_t& outFlags,
            void*& outGeomRef,
            char* outGeomName,
            size_t outGeomNameCapacity,
            void*& outOwner)
        {
            outClassId = 0;
            outFlags = 0;
            outGeomRef = nullptr;
            outOwner = nullptr;
            if (outGeomName && outGeomNameCapacity > 0)
                outGeomName[0] = '\0';
            if (!objectBytes)
                return false;

            __try
            {
                outFlags = *reinterpret_cast<const uint32_t*>(objectBytes + 0x14);
                outClassId = *reinterpret_cast<const uint32_t*>(objectBytes + 0x84);
                outOwner = *reinterpret_cast<void* const*>(objectBytes + 0x8C);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outClassId = 0;
                outFlags = 0;
                outOwner = nullptr;
                if (outGeomName && outGeomNameCapacity > 0)
                    outGeomName[0] = '\0';
                return false;
            }

            const void* geomRefConst = nullptr;
            TryReadChunkGeomIdentity(objectBytes, geomRefConst, outGeomName, outGeomNameCapacity);
            outGeomRef = const_cast<void*>(geomRefConst);
            return true;
        }

        static bool CaptureChunkObjectLinkProbe(const uint8_t* objectBytes, ChunkObjectLinkProbe& outProbe)
        {
            outProbe = {};
            outProbe.objectBytes = objectBytes;
            if (!objectBytes)
                return false;

            TryReadObjProjectId(objectBytes, outProbe.objectId, sizeof(outProbe.objectId));

            void* ownerUnused = nullptr;
            const bool ok = TryReadChunkObjectSummary(
                objectBytes,
                outProbe.classId,
                outProbe.flags,
                outProbe.geomRef,
                outProbe.geomName,
                sizeof(outProbe.geomName),
                ownerUnused);
            if (ok)
                PopulateChunkObjectLinkProbeFromIdentityCache(outProbe);
            return ok;
        }

        static const ChunkObjectIdentityCacheEntry* FindChunkObjectIdentityCacheEntry(const uint8_t* objectBytes)
        {
            if (!objectBytes)
                return nullptr;

            const auto it = g_ChunkObjectIdentityCache.find(reinterpret_cast<uintptr_t>(objectBytes));
            return (it != g_ChunkObjectIdentityCache.end()) ? &it->second : nullptr;
        }

        // Caches keyed on raw OBJ76 pointers go stale when the engine's object
        // pool recycles an address for a new chunk: without validation a fresh
        // chunklet (or another craft's chunk) inherits the previous owner's
        // craft identity. A geo-name mismatch is the recycle signal.
        static bool ChunkCachedGeomNameMatchesLive(const char* cachedGeomName, const char* liveGeomName)
        {
            if (!cachedGeomName || !cachedGeomName[0] || !liveGeomName || !liveGeomName[0])
                return true;

            return _stricmp(cachedGeomName, liveGeomName) == 0;
        }

        static void EraseChunkResolvedBinding(const uint8_t* objectBytes)
        {
            if (!objectBytes)
                return;

            g_ChunkResolvedBindingCache.erase(reinterpret_cast<uintptr_t>(objectBytes));
        }

        static const ChunkResolvedBindingEntry* FindChunkResolvedBindingEntryForGeom(
            const uint8_t* objectBytes,
            const char* liveGeomName)
        {
            if (!objectBytes)
                return nullptr;

            const auto it = g_ChunkResolvedBindingCache.find(reinterpret_cast<uintptr_t>(objectBytes));
            if (it == g_ChunkResolvedBindingCache.end())
                return nullptr;

            if (!ChunkCachedGeomNameMatchesLive(it->second.sourceGeomName, liveGeomName))
            {
                g_ChunkResolvedBindingCache.erase(it);
                return nullptr;
            }

            return &it->second;
        }

        static void StoreChunkResolvedBinding(
            const uint8_t* objectBytes,
            const ChunkCreateSourceTreeProbe& sourceTreeProbe)
        {
            if (!objectBytes || !sourceTreeProbe.valid)
                return;

            ChunkResolvedBindingEntry entry = {};
            if (sourceTreeProbe.source.cachedMeshName[0])
            {
                strncpy_s(entry.meshName, sizeof(entry.meshName), sourceTreeProbe.source.cachedMeshName, _TRUNCATE);
            }
            else if (sourceTreeProbe.ownerResolvedMeshName[0])
            {
                strncpy_s(entry.meshName, sizeof(entry.meshName), sourceTreeProbe.ownerResolvedMeshName, _TRUNCATE);
            }
            else
            {
                ResolveChunkCreateMeshContext(
                    sourceTreeProbe,
                    entry.meshName,
                    sizeof(entry.meshName));
            }

            if (sourceTreeProbe.source.vdfCandidates[0])
            {
                strncpy_s(
                    entry.vdfCandidates,
                    sizeof(entry.vdfCandidates),
                    sourceTreeProbe.source.vdfCandidates,
                    _TRUNCATE);
            }
            else if (entry.meshName[0])
            {
                BuildChunkVdfSourceCandidateList(
                    entry.meshName,
                    sourceTreeProbe.source,
                    sourceTreeProbe.parent,
                    sourceTreeProbe.sibling,
                    sourceTreeProbe.child,
                    entry.vdfCandidates,
                    sizeof(entry.vdfCandidates));
            }

            entry.sourceClassId = sourceTreeProbe.source.classId;
            if (sourceTreeProbe.source.geomName[0])
                strncpy_s(entry.sourceGeomName, sizeof(entry.sourceGeomName), sourceTreeProbe.source.geomName, _TRUNCATE);

            if (!entry.meshName[0] &&
                !entry.vdfCandidates[0] &&
                entry.sourceClassId == 0 &&
                !entry.sourceGeomName[0])
            {
                return;
            }

            entry.bindTick = GetTickCount();
            entry.lastSeenTick = entry.bindTick;
            g_ChunkResolvedBindingCache[reinterpret_cast<uintptr_t>(objectBytes)] = entry;
        }

        static void TouchChunkResolvedBinding(const uint8_t* objectBytes)
        {
            if (!objectBytes)
                return;

            const auto it = g_ChunkResolvedBindingCache.find(reinterpret_cast<uintptr_t>(objectBytes));
            if (it == g_ChunkResolvedBindingCache.end())
                return;

            it->second.lastSeenTick = GetTickCount();
        }

        static void PruneChunkResolvedBindingsIfNeeded()
        {
            if (g_ChunkResolvedBindingCache.empty())
                return;

            const DWORD now = GetTickCount();
            if (g_ChunkResolvedBindingLastPruneTick != 0 &&
                static_cast<DWORD>(now - g_ChunkResolvedBindingLastPruneTick) < kChunkResolvedBindingPruneMs)
            {
                return;
            }
            g_ChunkResolvedBindingLastPruneTick = now;

            for (auto it = g_ChunkResolvedBindingCache.begin(); it != g_ChunkResolvedBindingCache.end();)
            {
                const DWORD referenceTick =
                    (it->second.lastSeenTick != 0) ? it->second.lastSeenTick : it->second.bindTick;
                if (referenceTick != 0 &&
                    static_cast<DWORD>(now - referenceTick) >= kChunkResolvedBindingExpireMs)
                {
                    it = g_ChunkResolvedBindingCache.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        static void PopulateChunkObjectLinkProbeFromIdentityCache(ChunkObjectLinkProbe& probe)
        {
            const ChunkResolvedBindingEntry* binding =
                FindChunkResolvedBindingEntryForGeom(probe.objectBytes, probe.geomName);
            if (binding)
            {
                if (binding->meshName[0])
                    strncpy_s(probe.cachedMeshName, binding->meshName, _TRUNCATE);
                if (binding->vdfCandidates[0])
                    strncpy_s(probe.vdfCandidates, binding->vdfCandidates, _TRUNCATE);
            }

            const ChunkObjectIdentityCacheEntry* cached = FindChunkObjectIdentityCacheEntry(probe.objectBytes);
            if (!cached)
                return;
            if (!ChunkCachedGeomNameMatchesLive(cached->geomName, probe.geomName))
                return;

            if (!probe.cachedMeshName[0] && cached->meshName[0])
                strncpy_s(probe.cachedMeshName, cached->meshName, _TRUNCATE);
            if (!probe.vdfCandidates[0] && cached->vdfCandidates[0])
                strncpy_s(probe.vdfCandidates, cached->vdfCandidates, _TRUNCATE);
        }

        static bool CaptureChunkCreateSourceTreeProbe(
            const uint8_t* sourceBytes,
            ChunkCreateSourceTreeProbe& outProbe)
        {
            outProbe = {};
            if (!sourceBytes)
                return false;

            outProbe.valid = CaptureChunkObjectLinkProbe(sourceBytes, outProbe.source);

            const uint8_t* parentBytes = nullptr;
            const uint8_t* siblingBytes = nullptr;
            const uint8_t* childBytes = nullptr;
            __try
            {
                parentBytes = *reinterpret_cast<const uint8_t* const*>(sourceBytes + 0x78);
                siblingBytes = *reinterpret_cast<const uint8_t* const*>(sourceBytes + 0x7C);
                childBytes = *reinterpret_cast<const uint8_t* const*>(sourceBytes + 0x80);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                parentBytes = nullptr;
                siblingBytes = nullptr;
                childBytes = nullptr;
            }

            CaptureChunkObjectLinkProbe(parentBytes, outProbe.parent);
            CaptureChunkObjectLinkProbe(siblingBytes, outProbe.sibling);
            CaptureChunkObjectLinkProbe(childBytes, outProbe.child);

            const ChunkBridgeSnapshot bridgeSnapshot = CaptureChunkBridgeSnapshot(sourceBytes);
            outProbe.ownerEntity = bridgeSnapshot.ownerEntity;
            outProbe.ownerOgreEntity =
                LooksLikeOgreObject(bridgeSnapshot.directOgreEntity) ? bridgeSnapshot.directOgreEntity
                : LooksLikeOgreObject(bridgeSnapshot.ownerOgreEntity) ? bridgeSnapshot.ownerOgreEntity
                                                                      : nullptr;
            if (bridgeSnapshot.ownerEntityBaseName[0])
                strncpy_s(outProbe.ownerEntityBaseName, bridgeSnapshot.ownerEntityBaseName, _TRUNCATE);
            if (bridgeSnapshot.ownerOgreFilename[0])
                strncpy_s(outProbe.ownerOgreFilename, bridgeSnapshot.ownerOgreFilename, _TRUNCATE);
            if (bridgeSnapshot.ownerResolvedMeshName[0])
                strncpy_s(outProbe.ownerResolvedMeshName, bridgeSnapshot.ownerResolvedMeshName, _TRUNCATE);
            if (!outProbe.ownerResolvedMeshName[0] && g_ActiveFragmentSourceMeshName[0])
                strncpy_s(outProbe.ownerResolvedMeshName, g_ActiveFragmentSourceMeshName, _TRUNCATE);
            if (!outProbe.ownerResolvedMeshName[0])
            {
                ResolveChunkCreateMeshContext(
                    outProbe,
                    outProbe.ownerResolvedMeshName,
                    sizeof(outProbe.ownerResolvedMeshName));
            }
            if (!outProbe.source.vdfCandidates[0] && outProbe.ownerResolvedMeshName[0])
            {
                BuildChunkVdfSourceCandidateList(
                    outProbe.ownerResolvedMeshName,
                    outProbe.source,
                    outProbe.parent,
                    outProbe.sibling,
                    outProbe.child,
                    outProbe.source.vdfCandidates,
                    sizeof(outProbe.source.vdfCandidates));
            }

            if (outProbe.ownerResolvedMeshName[0])
            {
                if (!outProbe.source.vdfCandidates[0])
                    PopulateChunkVdfCandidates(outProbe.ownerResolvedMeshName, outProbe.source);
                PopulateChunkVdfCandidates(outProbe.ownerResolvedMeshName, outProbe.parent);
                PopulateChunkVdfCandidates(outProbe.ownerResolvedMeshName, outProbe.sibling);
                PopulateChunkVdfCandidates(outProbe.ownerResolvedMeshName, outProbe.child);
            }

            return outProbe.valid;
        }

        static bool TryReadChunkEffectCount(const uint8_t* thisBytes, uint32_t& outCount)
        {
            outCount = 0;
            if (!thisBytes)
                return false;

            __try
            {
                outCount = *reinterpret_cast<const uint32_t*>(thisBytes + kChunkEffectActiveCountOffset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outCount = 0;
                return false;
            }
        }

        static void LogChunkCreateLifecycle(
            const wchar_t* tag,
            void* thisPtr,
            const uint8_t* sourceBytes,
            const float* positionVec,
            const float* velocityVec,
            uint8_t preserveFlag,
            uint32_t countBefore,
            uint32_t countAfter,
            const ChunkEffectActiveEntry* createdEntry,
            const ChunkCreateSourceTreeProbe* sourceTreeProbe)
        {
            if ((!g_TraceChunkRender && !g_TraceChunkEffectRuntime) || !AcquireChunkLogSlot())
                return;

            uint32_t sourceClassId = 0;
            uint32_t sourceFlags = 0;
            void* sourceGeomRef = nullptr;
            void* sourceOwner = nullptr;
            char sourceGeomName[64] = {};
            TryReadChunkObjectSummary(
                sourceBytes,
                sourceClassId,
                sourceFlags,
                sourceGeomRef,
                sourceGeomName,
                sizeof(sourceGeomName),
                sourceOwner);

            uint32_t createdClassId = 0;
            uint32_t createdFlags = 0;
            void* createdGeomRef = nullptr;
            void* createdOwner = nullptr;
            char createdGeomName[64] = {};
            TryReadChunkObjectSummary(
                createdEntry ? createdEntry->objectBytes : nullptr,
                createdClassId,
                createdFlags,
                createdGeomRef,
                createdGeomName,
                sizeof(createdGeomName),
                createdOwner);

            const char* const sourceGeomDisplay = sourceGeomName[0] ? sourceGeomName : "<none>";
            const char* const sourceGeomKind =
                !sourceGeomName[0]
                    ? "unknown"
                    : ((_stricmp(sourceGeomName, "chunk1") == 0 || _stricmp(sourceGeomName, "chunk2") == 0)
                           ? "stock-chunklet"
                           : "named-nonchunklet");
            const char* const sourceVdfDisplay =
                (sourceTreeProbe && sourceTreeProbe->source.vdfCandidates[0])
                    ? sourceTreeProbe->source.vdfCandidates
                    : "<none>";
            const char* const createdGeomDisplay = createdGeomName[0] ? createdGeomName : "<none>";
            const char* const createdGeomKind =
                !createdGeomName[0]
                    ? "unknown"
                    : ((_stricmp(createdGeomName, "chunk1") == 0 || _stricmp(createdGeomName, "chunk2") == 0)
                           ? "stock-chunklet"
                           : "named-nonchunklet");

            float posX = 0.0f;
            float posY = 0.0f;
            float posZ = 0.0f;
            bool havePos = TryReadFloat3(positionVec, posX, posY, posZ);
            if (!havePos && createdEntry && createdEntry->objectBytes)
                havePos = TryGetChunkProxyPosition(createdEntry->objectBytes, posX, posY, posZ);

            float velX = 0.0f;
            float velY = 0.0f;
            float velZ = 0.0f;
            bool haveVel = false;
            if (createdEntry)
            {
                velX = createdEntry->velocityX;
                velY = createdEntry->velocityY;
                velZ = createdEntry->velocityZ;
                haveVel = true;
            }
            else
            {
                haveVel = TryReadFloat3(velocityVec, velX, velY, velZ);
            }

            LogChunkDiagnostic(
                "chunkspawn",
                L"[CHUNKSPAWN] %ls this=0x%08X before=%u after=%u preserve=%u src=0x%08X srcClass=%u srcFlags=0x%08X srcOwner=0x%08X srcGeom=0x%08X srcGeomName=%hs srcGeomKind=%hs srcVdf=%hs created=0x%08X createdClass=%u createdFlags=0x%08X createdOwner=0x%08X createdGeom=0x%08X createdGeomName=%hs createdGeomKind=%hs pos=%hs(%.4f, %.4f, %.4f) vel=%hs(%.4f, %.4f, %.4f)\n",
                tag ? tag : L"unknown",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)),
                countBefore,
                countAfter,
                static_cast<uint32_t>(preserveFlag),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceBytes)),
                sourceClassId,
                sourceFlags,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceOwner)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceGeomRef)),
                sourceGeomDisplay,
                sourceGeomKind,
                sourceVdfDisplay,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(createdEntry ? createdEntry->objectBytes : nullptr)),
                createdClassId,
                createdFlags,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(createdOwner)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(createdGeomRef)),
                createdGeomDisplay,
                createdGeomKind,
                havePos ? "" : "missing-",
                static_cast<double>(posX),
                static_cast<double>(posY),
                static_cast<double>(posZ),
                haveVel ? "" : "missing-",
                static_cast<double>(velX),
                static_cast<double>(velY),
                static_cast<double>(velZ));

            if (sourceTreeProbe && sourceTreeProbe->valid)
            {
                const ChunkObjectLinkProbe& sourceProbe = sourceTreeProbe->source;
                const ChunkObjectLinkProbe& parentProbe = sourceTreeProbe->parent;
                const ChunkObjectLinkProbe& siblingProbe = sourceTreeProbe->sibling;
                const ChunkObjectLinkProbe& childProbe = sourceTreeProbe->child;

                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN]   srcTree src=0x%08X objId=%hs class=%u flags=0x%08X geom=0x%08X geomName=%hs ownerEntity=0x%08X ownerBase=%hs ownerFile=%hs ownerMesh=%hs | parent=0x%08X objId=%hs class=%u geom=0x%08X geomName=%hs | sibling=0x%08X objId=%hs class=%u geom=0x%08X geomName=%hs | child=0x%08X objId=%hs class=%u geom=0x%08X geomName=%hs\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceProbe.objectBytes)),
                    sourceProbe.objectId[0] ? sourceProbe.objectId : "<none>",
                    sourceProbe.classId,
                    sourceProbe.flags,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceProbe.geomRef)),
                    sourceProbe.geomName[0] ? sourceProbe.geomName : "<none>",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceTreeProbe->ownerEntity)),
                    sourceTreeProbe->ownerEntityBaseName[0] ? sourceTreeProbe->ownerEntityBaseName : "<none>",
                    sourceTreeProbe->ownerOgreFilename[0] ? sourceTreeProbe->ownerOgreFilename : "<none>",
                    sourceTreeProbe->ownerResolvedMeshName[0] ? sourceTreeProbe->ownerResolvedMeshName : "<none>",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parentProbe.objectBytes)),
                    parentProbe.objectId[0] ? parentProbe.objectId : "<none>",
                    parentProbe.classId,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parentProbe.geomRef)),
                    parentProbe.geomName[0] ? parentProbe.geomName : "<none>",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(siblingProbe.objectBytes)),
                    siblingProbe.objectId[0] ? siblingProbe.objectId : "<none>",
                    siblingProbe.classId,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(siblingProbe.geomRef)),
                    siblingProbe.geomName[0] ? siblingProbe.geomName : "<none>",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(childProbe.objectBytes)),
                    childProbe.objectId[0] ? childProbe.objectId : "<none>",
                    childProbe.classId,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(childProbe.geomRef)),
                    childProbe.geomName[0] ? childProbe.geomName : "<none>");

                if (sourceProbe.vdfCandidates[0] || parentProbe.vdfCandidates[0] ||
                    siblingProbe.vdfCandidates[0] || childProbe.vdfCandidates[0])
                {
                    LogChunkDiagnostic(
                        "chunkspawn",
                        L"[CHUNKSPAWN]   vdf src=%hs | parent=%hs | sibling=%hs | child=%hs\n",
                        sourceProbe.vdfCandidates[0] ? sourceProbe.vdfCandidates : "<none>",
                        parentProbe.vdfCandidates[0] ? parentProbe.vdfCandidates : "<none>",
                        siblingProbe.vdfCandidates[0] ? siblingProbe.vdfCandidates : "<none>",
                        childProbe.vdfCandidates[0] ? childProbe.vdfCandidates : "<none>");
                }
            }
        }

        static const char* ClassifyChunkGeomName(const char* geomName)
        {
            if (!geomName || !*geomName)
                return "unknown";

            if (_stricmp(geomName, "chunk1") == 0 || _stricmp(geomName, "chunk2") == 0)
                return "stock-chunklet";

            return "named-nonchunklet";
        }

        static const char* GetChunkGeomNameForLog(const char* geomName)
        {
            return (geomName && *geomName) ? geomName : "<none>";
        }

        static bool ShouldUseChunkPayloadMesh(const ChunkProxySlot& slot)
        {
            return g_EnableChunkMeshProxy && slot.proofMeshName[0];
        }

        static const char* GetChunkPayloadMeshName(const ChunkProxySlot& slot)
        {
            return slot.proofMeshName;
        }

        static void HideChunkProxyMesh(ChunkProxySlot& slot);

        static void InvalidateChunkMeshProxySlot(ChunkProxySlot& slot)
        {
            if (slot.meshAssigned)
                HideChunkProxyMesh(slot);

            slot.sceneNode = nullptr;
            slot.entity = nullptr;
            slot.meshAssigned = false;
        }

        static int FindChunkGeoEntryByKey(const BzrGeoLookup* lookup, uint32_t key)
        {
            if (!lookup || !lookup->entries || lookup->count == 0 || key == 0)
                return -1;

            for (uint32_t index = 0; index < lookup->count; ++index)
            {
                const BzrGeoEntry& entry = lookup->entries[index];
                if (entry.handle && entry.packedKey == key)
                    return static_cast<int>(index);
            }

            return -1;
        }

        static int FindFirstChunkGeoEntryWithHandle(const BzrGeoLookup* lookup)
        {
            if (!lookup || !lookup->entries || lookup->count == 0)
                return -1;

            for (uint32_t index = 0; index < lookup->count; ++index)
            {
                if (lookup->entries[index].handle)
                    return static_cast<int>(index);
            }

            return -1;
        }

        static bool TryBuildOgreQuaternionFromLegacyTransform(
            const LegacyMat3& transform,
            OgreQuaternion& outOrientation)
        {
            outOrientation = { 1.0f, 0.0f, 0.0f, 0.0f };

            double rightX = transform.right_x;
            double rightY = transform.right_y;
            double rightZ = transform.right_z;
            double upX = transform.up_x;
            double upY = transform.up_y;
            double upZ = transform.up_z;
            double frontX = transform.front_x;
            double frontY = transform.front_y;
            double frontZ = transform.front_z;

            const double rightLen = std::sqrt(rightX * rightX + rightY * rightY + rightZ * rightZ);
            const double upLen = std::sqrt(upX * upX + upY * upY + upZ * upZ);
            const double frontLen = std::sqrt(frontX * frontX + frontY * frontY + frontZ * frontZ);
            if (!(std::isfinite(rightLen) && std::isfinite(upLen) && std::isfinite(frontLen)) ||
                rightLen <= 1.0e-8 || upLen <= 1.0e-8 || frontLen <= 1.0e-8)
            {
                return false;
            }

            rightX /= rightLen;
            rightY /= rightLen;
            rightZ /= rightLen;
            upX /= upLen;
            upY /= upLen;
            upZ /= upLen;
            frontX /= frontLen;
            frontY /= frontLen;
            frontZ /= frontLen;

            // LegacyMat3 stores basis vectors directly. Build a rotation matrix
            // with those basis vectors as columns to match Ogre's node orientation.
            const double m00 = rightX;
            const double m10 = rightY;
            const double m20 = rightZ;
            const double m01 = upX;
            const double m11 = upY;
            const double m21 = upZ;
            const double m02 = frontX;
            const double m12 = frontY;
            const double m22 = frontZ;

            double w = 1.0;
            double x = 0.0;
            double y = 0.0;
            double z = 0.0;

            const double trace = m00 + m11 + m22;
            if (trace > 0.0)
            {
                const double s = std::sqrt(trace + 1.0) * 2.0;
                if (!std::isfinite(s) || s <= 1.0e-8)
                    return false;
                w = 0.25 * s;
                x = (m21 - m12) / s;
                y = (m02 - m20) / s;
                z = (m10 - m01) / s;
            }
            else if (m00 > m11 && m00 > m22)
            {
                const double s = std::sqrt(1.0 + m00 - m11 - m22) * 2.0;
                if (!std::isfinite(s) || s <= 1.0e-8)
                    return false;
                w = (m21 - m12) / s;
                x = 0.25 * s;
                y = (m01 + m10) / s;
                z = (m02 + m20) / s;
            }
            else if (m11 > m22)
            {
                const double s = std::sqrt(1.0 + m11 - m00 - m22) * 2.0;
                if (!std::isfinite(s) || s <= 1.0e-8)
                    return false;
                w = (m02 - m20) / s;
                x = (m01 + m10) / s;
                y = 0.25 * s;
                z = (m12 + m21) / s;
            }
            else
            {
                const double s = std::sqrt(1.0 + m22 - m00 - m11) * 2.0;
                if (!std::isfinite(s) || s <= 1.0e-8)
                    return false;
                w = (m10 - m01) / s;
                x = (m02 + m20) / s;
                y = (m12 + m21) / s;
                z = 0.25 * s;
            }

            const double quatLen = std::sqrt(w * w + x * x + y * y + z * z);
            if (!std::isfinite(quatLen) || quatLen <= 1.0e-8)
                return false;

            outOrientation.w = static_cast<float>(w / quatLen);
            outOrientation.x = static_cast<float>(x / quatLen);
            outOrientation.y = static_cast<float>(y / quatLen);
            outOrientation.z = static_cast<float>(z / quatLen);
            return std::isfinite(outOrientation.w) &&
                   std::isfinite(outOrientation.x) &&
                   std::isfinite(outOrientation.y) &&
                   std::isfinite(outOrientation.z);
        }

        static bool TryGetChunkProxyPosition(const uint8_t* objectBytes, float& outX, float& outY, float& outZ)
        {
            if (!objectBytes)
                return false;

            __try
            {
                const auto* transform = reinterpret_cast<const LegacyMat3*>(objectBytes + 0x20);
                const double x = transform->posit_x;
                const double y = transform->posit_y;
                const double z = transform->posit_z;
                if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
                    return false;

                outX = static_cast<float>(x);
                outY = static_cast<float>(y);
                outZ = static_cast<float>(z);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryGetChunkProxyTransform(const uint8_t* objectBytes, ChunkProxyTransform& outTransform)
        {
            outTransform = {};
            if (!objectBytes)
                return false;

            __try
            {
                const auto* transform = reinterpret_cast<const LegacyMat3*>(objectBytes + 0x20);
                const double x = transform->posit_x;
                const double y = transform->posit_y;
                const double z = transform->posit_z;
                if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
                    return false;

                outTransform.x = static_cast<float>(x);
                outTransform.y = static_cast<float>(y);
                outTransform.z = static_cast<float>(z);
                if (!TryBuildOgreQuaternionFromLegacyTransform(*transform, outTransform.orientation))
                    outTransform.orientation = { 1.0f, 0.0f, 0.0f, 0.0f };
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outTransform = {};
                return false;
            }
        }

        static bool TryResolveChunkProxyPositionFromCandidates(
            const uint8_t* primaryObjectBytes,
            const ChunkResolvedBindingEntry* binding,
            const ChunkBridgeSnapshot* bridgeSnapshot,
            float& outX,
            float& outY,
            float& outZ,
            const void** outResolvedObject = nullptr)
        {
            if (outResolvedObject)
                *outResolvedObject = nullptr;

            const void* candidates[] =
            {
                primaryObjectBytes,
                reinterpret_cast<const void*>(static_cast<uintptr_t>(binding ? binding->sourceRootObjectPtr : 0)),
                reinterpret_cast<const void*>(static_cast<uintptr_t>(binding ? binding->sourceOwnerEntityPtr : 0)),
                reinterpret_cast<const void*>(static_cast<uintptr_t>(binding ? binding->sourceOwnerObjPtr : 0)),
                reinterpret_cast<const void*>(static_cast<uintptr_t>(binding ? binding->sourceGameObjectPtr : 0)),
                reinterpret_cast<const void*>(static_cast<uintptr_t>(binding ? binding->sourceRootGameObjectPtr : 0)),
                bridgeSnapshot ? bridgeSnapshot->ownerEntity : nullptr,
                bridgeSnapshot ? bridgeSnapshot->ownerObj : nullptr,
                bridgeSnapshot ? bridgeSnapshot->gameObject : nullptr,
            };

            std::unordered_set<uintptr_t> seen;
            seen.reserve(std::size(candidates));
            for (const void* candidate : candidates)
            {
                const uintptr_t key = reinterpret_cast<uintptr_t>(candidate);
                if (!candidate || !seen.insert(key).second)
                    continue;

                if (TryGetChunkProxyPosition(
                        reinterpret_cast<const uint8_t*>(candidate),
                        outX,
                        outY,
                        outZ))
                {
                    if (outResolvedObject)
                        *outResolvedObject = candidate;
                    return true;
                }
            }

            return false;
        }

        static bool TryResolveChunkProxyTransformForSlot(
            const ChunkProxySlot& slot,
            ChunkProxyTransform& outTransform,
            const void** outResolvedObject = nullptr)
        {
            if (outResolvedObject)
                *outResolvedObject = nullptr;

            const void* candidates[] =
            {
                slot.objectBytes,
                slot.sourceRootObject,
                slot.ownerEntity,
                slot.ownerObj,
                slot.sourceGameObject,
                slot.sourceRootGameObject,
            };

            std::unordered_set<uintptr_t> seen;
            seen.reserve(std::size(candidates));
            for (const void* candidate : candidates)
            {
                const uintptr_t key = reinterpret_cast<uintptr_t>(candidate);
                if (!candidate || !seen.insert(key).second)
                    continue;

                if (TryGetChunkProxyTransform(
                        reinterpret_cast<const uint8_t*>(candidate),
                        outTransform))
                {
                    if (outResolvedObject)
                        *outResolvedObject = candidate;
                    return true;
                }
            }

            outTransform = {};
            return false;
        }

        static bool TryBuildChunkProxyAnchoredEntryTransform(
            const ChunkProxySlot& slot,
            const ChunkProxyTransform* baseTransform,
            ChunkProxyTransform& outTransform,
            const void** outAnchorObject = nullptr)
        {
            const void* candidates[] =
            {
                slot.sourceRootGameObject,
                slot.sourceGameObject,
                slot.ownerObj,
                slot.ownerEntity,
                slot.sourceRootObject,
            };

            std::unordered_set<uintptr_t> seen;
            seen.reserve(std::size(candidates));

            bool found = false;
            double bestScore = 0.0;
            ChunkProxyTransform bestTransform = {};
            const void* bestAnchorObject = nullptr;
            for (const void* candidate : candidates)
            {
                const uintptr_t key = reinterpret_cast<uintptr_t>(candidate);
                if (!candidate || !seen.insert(key).second)
                    continue;

                ChunkProxyTransform anchorTransform = {};
                if (!TryGetChunkProxyTransform(
                        reinterpret_cast<const uint8_t*>(candidate),
                        anchorTransform))
                {
                    continue;
                }

                ChunkProxyTransform candidateTransform = baseTransform ? *baseTransform : anchorTransform;
                candidateTransform.x = anchorTransform.x + slot.positionX;
                candidateTransform.y = anchorTransform.y + slot.positionY;
                candidateTransform.z = anchorTransform.z + slot.positionZ;

                if (!baseTransform)
                {
                    candidateTransform.orientation = anchorTransform.orientation;
                    candidateTransform.scale = anchorTransform.scale;
                }

                double candidateScore = 0.0;
                if (baseTransform)
                {
                    const double dx = static_cast<double>(candidateTransform.x) - static_cast<double>(baseTransform->x);
                    const double dy = static_cast<double>(candidateTransform.y) - static_cast<double>(baseTransform->y);
                    const double dz = static_cast<double>(candidateTransform.z) - static_cast<double>(baseTransform->z);
                    candidateScore = std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                }

                if (!found || candidateScore < bestScore)
                {
                    bestScore = candidateScore;
                    bestTransform = candidateTransform;
                    bestAnchorObject = candidate;
                    found = true;
                    if (!baseTransform)
                        break;
                }
            }

            if (!found)
            {
                seen.clear();
                for (const void* candidate : candidates)
                {
                    const uintptr_t key = reinterpret_cast<uintptr_t>(candidate);
                    if (!candidate || !seen.insert(key).second)
                        continue;

                    float anchorX = 0.0f;
                    float anchorY = 0.0f;
                    float anchorZ = 0.0f;
                    if (!TryGetChunkProxyPosition(
                            reinterpret_cast<const uint8_t*>(candidate),
                            anchorX,
                            anchorY,
                            anchorZ))
                    {
                        continue;
                    }

                    ChunkProxyTransform candidateTransform = {};
                    if (baseTransform)
                    {
                        candidateTransform = *baseTransform;
                    }
                    else
                    {
                        candidateTransform.orientation = { 1.0f, 0.0f, 0.0f, 0.0f };
                        candidateTransform.scale = { 1.0f, 1.0f, 1.0f };
                    }

                    candidateTransform.x = anchorX + slot.positionX;
                    candidateTransform.y = anchorY + slot.positionY;
                    candidateTransform.z = anchorZ + slot.positionZ;

                    double candidateScore = 0.0;
                    if (baseTransform)
                    {
                        const double dx = static_cast<double>(candidateTransform.x) - static_cast<double>(baseTransform->x);
                        const double dy = static_cast<double>(candidateTransform.y) - static_cast<double>(baseTransform->y);
                        const double dz = static_cast<double>(candidateTransform.z) - static_cast<double>(baseTransform->z);
                        candidateScore = std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                    }

                    if (!found || candidateScore < bestScore)
                    {
                        bestScore = candidateScore;
                        bestTransform = candidateTransform;
                        bestAnchorObject = candidate;
                        found = true;
                        if (!baseTransform)
                            break;
                    }
                }
            }

            if (!found)
                return false;

            outTransform = bestTransform;
            if (outAnchorObject)
                *outAnchorObject = bestAnchorObject;
            return true;
        }

        static bool ShouldPreferChunkEntryPosition(
            const ChunkProxySlot& slot,
            const ChunkProxyTransform& transform)
        {
            if (!slot.useEntryPosition)
                return false;

            const double dx = static_cast<double>(transform.x) - static_cast<double>(slot.positionX);
            const double dy = static_cast<double>(transform.y) - static_cast<double>(slot.positionY);
            const double dz = static_cast<double>(transform.z) - static_cast<double>(slot.positionZ);
            const double distance = std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
            return std::isfinite(distance) &&
                   distance > static_cast<double>(kChunkProxyEntryPositionTolerance);
        }

        static double ComputeChunkProxyPositionDistance(
            float ax,
            float ay,
            float az,
            float bx,
            float by,
            float bz)
        {
            const double dx = static_cast<double>(ax) - static_cast<double>(bx);
            const double dy = static_cast<double>(ay) - static_cast<double>(by);
            const double dz = static_cast<double>(az) - static_cast<double>(bz);
            return std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
        }

        static bool TryPromoteChunkProxyLocalTransformToAnchoredWorld(
            const ChunkProxySlot& slot,
            const ChunkProxyTransform& resolvedTransform,
            const void* resolvedTransformObject,
            ChunkProxyTransform& outTransform,
            const void** outAnchorObject = nullptr)
        {
            if (outAnchorObject)
                *outAnchorObject = nullptr;

            if (!slot.useEntryPosition ||
                resolvedTransformObject == nullptr ||
                resolvedTransformObject != slot.objectBytes)
            {
                return false;
            }

            const double rawEntryDistance = ComputeChunkProxyPositionDistance(
                resolvedTransform.x,
                resolvedTransform.y,
                resolvedTransform.z,
                slot.positionX,
                slot.positionY,
                slot.positionZ);
            const double rawMagnitude = ComputeChunkProxyPositionDistance(
                resolvedTransform.x,
                resolvedTransform.y,
                resolvedTransform.z,
                0.0f,
                0.0f,
                0.0f);
            const bool localLike =
                (std::isfinite(rawEntryDistance) &&
                 rawEntryDistance <= static_cast<double>(kChunkProxyLocalTransformTolerance)) ||
                (std::isfinite(rawMagnitude) &&
                 rawMagnitude <= static_cast<double>(kChunkProxyLocalTransformTolerance));
            if (!localLike)
                return false;

            ChunkProxyTransform anchoredTransform = {};
            const void* anchoredObject = nullptr;
            if (!TryBuildChunkProxyAnchoredEntryTransform(
                    slot,
                    &resolvedTransform,
                    anchoredTransform,
                    &anchoredObject))
            {
                return false;
            }

            const double anchorDelta = ComputeChunkProxyPositionDistance(
                anchoredTransform.x,
                anchoredTransform.y,
                anchoredTransform.z,
                resolvedTransform.x,
                resolvedTransform.y,
                resolvedTransform.z);
            if (!std::isfinite(anchorDelta) ||
                anchorDelta < static_cast<double>(kChunkProxyAnchoredTransformAdoptDistance))
            {
                return false;
            }

            outTransform = anchoredTransform;
            if (outAnchorObject)
                *outAnchorObject = anchoredObject;
            return true;
        }

        void* GetOgreSceneManagerRuntime()
        {
            __try
            {
                auto* const renderGlobalsSlot =
                    reinterpret_cast<uint8_t**>(EngineGlobals::RenderGlobals());
                if (!renderGlobalsSlot)
                    return nullptr;
                auto* sceneManagerStructure = *renderGlobalsSlot;
                if (!sceneManagerStructure)
                    return nullptr;

                return *reinterpret_cast<void**>(sceneManagerStructure + kOgreSceneManagerOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        static bool TrySetChunkProxyBillboardPosition(
            void* billboard,
            FnOgreSetBillboardPosition setPosition,
            float x,
            float y,
            float z);

        static void HideChunkProxyBillboard(void* billboard)
        {
            static FnOgreSetBillboardPosition setPosition =
                ResolveOgreProc<FnOgreSetBillboardPosition>("?setPosition@Billboard@Ogre@@QAEXMMM@Z");
            if (!billboard || !setPosition)
                return;

            TrySetChunkProxyBillboardPosition(billboard, setPosition, 0.0f, kChunkProxyHiddenY, 0.0f);
        }

        // --- Ogre call guards ------------------------------------------------
        //
        // Every Ogre call in the chunk proxy runs under __try, because the
        // object it is handed may have been destroyed by a scene teardown the
        // shim did not observe, and only SEH stops the access violation that
        // follows. But Ogre also throws C++ exceptions as a matter of course:
        // a missing mesh or material, a name collision in createEntity, an
        // out-of-range getSubEntity, a codec error. An
        // __except(EXCEPTION_EXECUTE_HANDLER) caught those too, as the MSVC
        // C++ exception code, and executing an SEH handler for a C++ throw
        // skips every destructor between the throw and that frame: OgreMain's
        // mutex guards stayed held, a half-registered object stayed in the
        // movable-object map, the exception object leaked. So each guard now
        // has two halves. The C++ half (CatchOgreThrow) runs the call inside
        // try/catch, which lets the throw unwind OgreMain's frames before it
        // is caught. The SEH half keeps only the hardware faults and hands a
        // C++ exception back to the unwinder (OgreCallSehFilter), so it can
        // never again be swallowed on this path.
        constexpr unsigned long kMsvcCppExceptionCode = 0xE06D7363UL;

        static int OgreCallSehFilter(unsigned long code)
        {
            return code == kMsvcCppExceptionCode ? EXCEPTION_CONTINUE_SEARCH : EXCEPTION_EXECUTE_HANDLER;
        }

        // Runs `call` and reports a C++ throw as false. The lambda is its own
        // function, so the caller's __try frame stays free of objects that
        // need unwinding (C2712). The log budget is per site and small: these
        // guards sit on the per-slot render tick.
        template <typename Call>
        static bool CatchOgreThrow(const char* site, Call&& call)
        {
            try
            {
                call();
                return true;
            }
            catch (...)
            {
                static volatile LONG s_budget = 8;
                if (InterlockedDecrement(&s_budget) >= 0)
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Ogre threw in %hs; call abandoned\n", site);
                return false;
            }
        }

        static bool TryCreateChunkProxyBillboardSet(
            void* sceneManager,
            FnOgreGetRootSceneNode getRootSceneNode,
            FnOgreCreateBillboardSet createBillboardSet,
            void*& outRootNode,
            void*& outBillboardSet)
        {
            outRootNode = nullptr;
            outBillboardSet = nullptr;
            if (!sceneManager || !getRootSceneNode || !createBillboardSet)
                return false;

            __try
            {
                if (!CatchOgreThrow("createBillboardSet", [&] {
                        outRootNode = getRootSceneNode(sceneManager);
                        if (outRootNode)
                            outBillboardSet = createBillboardSet(sceneManager, g_ChunkProxyCapacity);
                    }))
                {
                    outRootNode = nullptr;
                    outBillboardSet = nullptr;
                }
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                outRootNode = nullptr;
                outBillboardSet = nullptr;
            }

            return outRootNode != nullptr && outBillboardSet != nullptr;
        }

        static bool TrySetupChunkProxyBillboardSet(
            void* rootNode,
            void* billboardSet,
            FnOgreAttachObject attachObject,
            FnOgreSetBillboardsInWorldSpace setBillboardsInWorldSpace,
            FnOgreSetDefaultDimensions setDefaultDimensions)
        {
            if (!rootNode || !billboardSet || !attachObject || !setBillboardsInWorldSpace || !setDefaultDimensions)
                return false;

            __try
            {
                return CatchOgreThrow("setupBillboardSet", [&] {
                    setBillboardsInWorldSpace(billboardSet, true);
                    setDefaultDimensions(billboardSet, g_ChunkProxyDebugSize, g_ChunkProxyDebugSize);
                    attachObject(rootNode, billboardSet);
                });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        static void* TryCreateChunkProxyBillboard(void* billboardSet, FnOgreCreateBillboard createBillboard, const OgreColourValue& color)
        {
            if (!billboardSet || !createBillboard)
                return nullptr;

            void* billboard = nullptr;
            __try
            {
                if (!CatchOgreThrow("createBillboard", [&] {
                        billboard = createBillboard(billboardSet, 0.0f, kChunkProxyHiddenY, 0.0f, color);
                    }))
                {
                    billboard = nullptr;
                }
                return billboard;
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return nullptr;
            }
        }

        static bool TrySetChunkProxyBillboardPosition(
            void* billboard,
            FnOgreSetBillboardPosition setPosition,
            float x,
            float y,
            float z)
        {
            if (!billboard || !setPosition)
                return false;

            __try
            {
                return CatchOgreThrow("setBillboardPosition", [&] { setPosition(billboard, x, y, z); });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        static void TryHideChunkProxyEntity(void* entity, FnOgreSetVisible setVisible)
        {
            if (!entity || !setVisible)
                return;

            __try
            {
                CatchOgreThrow("hideEntity", [&] { setVisible(entity, false); });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
            }
        }

        static void TryResetChunkProxyNode(
            void* sceneNode,
            FnOgreSetNodePosition setPosition,
            FnOgreSetNodeOrientation setOrientation)
        {
            if (!sceneNode || !setPosition)
                return;

            __try
            {
                CatchOgreThrow("resetNode", [&] {
                    setPosition(sceneNode, 0.0f, kChunkProxyHiddenY, 0.0f);
                    if (setOrientation)
                        setOrientation(sceneNode, 1.0f, 0.0f, 0.0f, 0.0f);
                });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
            }
        }

        static void* CreateChunkMeshProxyEntity(
            void* sceneManager,
            FnOgreCreateEntity createEntity,
            const char* meshName)
        {
            if (!sceneManager || !createEntity || !meshName || !*meshName)
                return nullptr;

            return createEntity(sceneManager, std::string(meshName));
        }

        static bool TryCreateChunkMeshProxyObjects(
            void* rootNode,
            void* sceneManager,
            FnOgreCreateChildSceneNode createChildSceneNode,
            FnOgreCreateEntity createEntity,
            FnOgreAttachObject attachObject,
            FnOgreSetVisible setVisible,
            const char* meshName,
            void*& outSceneNode,
            void*& outEntity)
        {
            outSceneNode = nullptr;
            outEntity = nullptr;
            if (!rootNode || !sceneManager || !createChildSceneNode || !createEntity || !attachObject || !setVisible)
                return false;

            const OgreVector3 zeroPos = { 0.0f, kChunkProxyHiddenY, 0.0f };
            const OgreQuaternion identity = { 1.0f, 0.0f, 0.0f, 0.0f };
            __try
            {
                if (!CatchOgreThrow("createMeshProxy", [&] {
                        outSceneNode = createChildSceneNode(rootNode, zeroPos, identity);
                        if (outSceneNode)
                        {
                            outEntity = CreateChunkMeshProxyEntity(sceneManager, createEntity, meshName);
                            if (outEntity)
                            {
                                attachObject(outSceneNode, outEntity);
                                setVisible(outEntity, false);
                            }
                        }
                    }))
                {
                    outSceneNode = nullptr;
                    outEntity = nullptr;
                }
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                outSceneNode = nullptr;
                outEntity = nullptr;
            }

            return outSceneNode != nullptr && outEntity != nullptr;
        }

        static void* TryGetChunkMeshProxyRootNode(
            void* sceneManager,
            FnOgreGetRootSceneNode getRootSceneNode)
        {
            if (!sceneManager || !getRootSceneNode)
                return nullptr;

            void* rootNode = nullptr;
            __try
            {
                if (!CatchOgreThrow("rootSceneNode", [&] { rootNode = getRootSceneNode(sceneManager); }))
                    rootNode = nullptr;
                return rootNode;
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return nullptr;
            }
        }

        static bool EnsureChunkPayloadResourceLocations()
        {
            if (!g_EnableChunkMeshProxy)
                return false;

            if (g_ChunkPayloadResourceLocationsReady)
                return true;

            if (!g_ChunkPayloadResourceLocationsAttempted)
            {
                RefreshChunkPayloadResourceDirectories();
                g_ChunkPayloadResourceLocationsAttempted = true;
            }

            if (g_ChunkPayloadResourceDirectories.empty())
            {
                if (!g_ChunkPayloadResourceLocationsFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh",
                        L"[CHUNKMESH] No chunk payload resource directories found; stockRoot=%hs modRelative=%hs\n",
                        GetChunkPayloadStockResourceDirectory().string().c_str(),
                        kChunkPayloadModRelativeDirName);
                    g_ChunkPayloadResourceLocationsFailureLogged = true;
                }
                return false;
            }

            static FnOgreGetResourceGroupManager getResourceGroupManager =
                ResolveOgreProc<FnOgreGetResourceGroupManager>("?getSingletonPtr@ResourceGroupManager@Ogre@@SAPAV12@XZ");
            static FnOgreResourceGroupExists resourceGroupExists =
                ResolveOgreProc<FnOgreResourceGroupExists>("?resourceGroupExists@ResourceGroupManager@Ogre@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            static FnOgreCreateResourceGroup createResourceGroup =
                ResolveOgreProc<FnOgreCreateResourceGroup>("?createResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
            static FnOgreAddResourceLocation addResourceLocation =
                ResolveOgreProc<FnOgreAddResourceLocation>("?addResourceLocation@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00_N1@Z");
            static FnOgreInitialiseResourceGroup initialiseResourceGroup =
                ResolveOgreProc<FnOgreInitialiseResourceGroup>("?initialiseResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

            if (!getResourceGroupManager || !resourceGroupExists || !createResourceGroup ||
                !addResourceLocation || !initialiseResourceGroup)
            {
                if (!g_ChunkPayloadResourceLocationsFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Missing Ogre resource manager symbols; cannot register chunk payload roots\n");
                    g_ChunkPayloadResourceLocationsFailureLogged = true;
                }
                return false;
            }

            void* resourceManager = getResourceGroupManager();
            if (!resourceManager)
            {
                if (!g_ChunkPayloadResourceLocationsFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Ogre resource manager unavailable; cannot register chunk payload roots yet\n");
                    g_ChunkPayloadResourceLocationsFailureLogged = true;
                }
                return false;
            }

            const std::string groupName = kChunkPayloadResourceRootName;
            const std::string locationType = kChunkPayloadResourceLocationType;
            try
            {
                if (!resourceGroupExists(resourceManager, groupName))
                    createResourceGroup(resourceManager, groupName, false);

                for (const std::filesystem::path& resourceRoot : g_ChunkPayloadResourceDirectories)
                {
                    addResourceLocation(resourceManager, resourceRoot.string(), locationType, groupName, true, true);
                    if (!g_ChunkPayloadResourceLocationsLogged)
                    {
                        LogChunkDiagnostic("chunkmesh",
                            L"[CHUNKMESH] Registered chunk payload resource root group=%hs path=%hs\n",
                            groupName.c_str(),
                            resourceRoot.string().c_str());
                    }
                }

                initialiseResourceGroup(resourceManager, groupName);
            }
            catch (...)
            {
                if (!g_ChunkPayloadResourceLocationsFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Exception while registering chunk payload resource roots\n");
                    g_ChunkPayloadResourceLocationsFailureLogged = true;
                }
                return false;
            }

            g_ChunkPayloadResourceLocationsReady = true;
            g_ChunkPayloadResourceLocationsLogged = true;
            g_ChunkPayloadResourceLocationsFailureLogged = false;
            return true;
        }

        static bool TryUpdateChunkMeshProxyTransform(
            void* sceneNode,
            void* entity,
            FnOgreSetNodePosition setNodePosition,
            FnOgreSetNodeOrientation setNodeOrientation,
            FnOgreSetVisible setVisible,
            const ChunkProxyTransform& transform)
        {
            if (!sceneNode || !entity || !setNodePosition || !setVisible)
                return false;

            __try
            {
                return CatchOgreThrow("updateMeshProxyTransform", [&] {
                    setNodePosition(sceneNode, transform.x, transform.y, transform.z);
                    if (setNodeOrientation)
                    {
                        setNodeOrientation(
                            sceneNode,
                            transform.orientation.w,
                            transform.orientation.x,
                            transform.orientation.y,
                            transform.orientation.z);
                    }
                    setVisible(entity, true);
                });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        static void HideChunkProxyMesh(ChunkProxySlot& slot)
        {
            static FnOgreSetVisible setVisible =
                ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");
            static FnOgreSetNodePosition setPosition =
                ResolveOgreProc<FnOgreSetNodePosition>("?setPosition@Node@Ogre@@UAEXMMM@Z");
            static FnOgreSetNodeOrientation setOrientation =
                ResolveOgreProc<FnOgreSetNodeOrientation>("?setOrientation@Node@Ogre@@UAEXMMMM@Z");

            TryHideChunkProxyEntity(slot.entity, setVisible);
            TryResetChunkProxyNode(slot.sceneNode, setPosition, setOrientation);
        }

        static bool EnsureChunkMeshProxySlot(ChunkProxySlot& slot)
        {
            if (!g_EnableChunkMeshProxy)
                return false;
            // Second gate: even if config said enabled at boot, re-check
            // centralized asset capability on every creation attempt. This
            // covers partial packages where the sentinel says "detected" but
            // the specific mesh file for this slot is absent, and ensures we
            // never create an Ogre Entity with a missing mesh name.
            if (!Assets::IsAssetFeatureAvailable(Assets::AssetFeature::DestructionChunks))
                return false;
            // Per-mesh verification: even when the global capability is true
            // (some payloads exist), the particular requested mesh may be absent
            // in a partial pack. The resolver (TryResolveChunkPayloadMeshResource)
            // already verified before filling proofMeshName, so an empty
            // proofMeshName means "no file for this mesh" and must not allocate.
            // Trace for partial-pack proof (see tests/openshim_assets_tests):
            //   partial pack → capability true → requested mesh absent → resolver false →
            //   proofMeshName empty → NO SceneNode → NO Entity → NO createEntity("") → no retry storm
            {
                const char* meshName = GetChunkPayloadMeshName(slot);
                if (!meshName || !*meshName)
                    return false;
            }

            if (slot.sceneNode && slot.entity)
                return true;

            // Back off only after a failed attempt (Ogre not ready yet). Arming
            // the throttle on success too would let just one fragment per second
            // acquire an entity, while chunk entries expire within 400ms.
            const DWORD now = GetTickCount();
            if (g_ChunkMeshProxyLastRetryTick != 0 &&
                static_cast<DWORD>(now - g_ChunkMeshProxyLastRetryTick) < kChunkProxyRetryDelayMs)
            {
                return false;
            }

            static FnOgreGetRootSceneNode getRootSceneNode =
                ResolveOgreProc<FnOgreGetRootSceneNode>("?getRootSceneNode@SceneManager@Ogre@@UAEPAVSceneNode@2@XZ");
            static FnOgreCreateChildSceneNode createChildSceneNode =
                ResolveOgreProc<FnOgreCreateChildSceneNode>("?createChildSceneNode@SceneNode@Ogre@@UAEPAV12@ABVVector3@2@ABVQuaternion@2@@Z");
            static FnOgreCreateEntity createEntity =
                ResolveOgreProc<FnOgreCreateEntity>("?createEntity@SceneManager@Ogre@@UAEPAVEntity@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            static FnOgreAttachObject attachObject =
                ResolveOgreProc<FnOgreAttachObject>("?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
            static FnOgreSetVisible setVisible =
                ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");

            if (!getRootSceneNode || !createChildSceneNode || !createEntity || !attachObject || !setVisible)
            {
                if (!g_ChunkMeshProxyFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Missing Ogre entity symbols; mesh proxy disabled for now\n");
                    g_ChunkMeshProxyFailureLogged = true;
                }
                g_ChunkMeshProxyLastRetryTick = now;
                return false;
            }

            void* sceneManager = GetOgreSceneManagerRuntime();
            if (!sceneManager)
            {
                if (!g_ChunkMeshProxyWaitLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Scene manager unavailable; waiting to initialize chunk mesh proxy\n");
                    g_ChunkMeshProxyWaitLogged = true;
                }
                g_ChunkMeshProxyLastRetryTick = now;
                return false;
            }

            if (!EnsureChunkPayloadResourceLocations())
            {
                g_ChunkMeshProxyLastRetryTick = now;
                return false;
            }

            void* rootNode = TryGetChunkMeshProxyRootNode(sceneManager, getRootSceneNode);
            if (!rootNode)
            {
                if (!g_ChunkMeshProxyFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Root scene node unavailable sceneManager=0x%08X\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sceneManager)));
                    g_ChunkMeshProxyFailureLogged = true;
                }
                g_ChunkMeshProxyLastRetryTick = now;
                return false;
            }

            void* sceneNode = nullptr;
            void* entity = nullptr;
            const char* const meshName = GetChunkPayloadMeshName(slot);
            if (!TryCreateChunkMeshProxyObjects(
                    rootNode,
                    sceneManager,
                    createChildSceneNode,
                    createEntity,
                    attachObject,
                    setVisible,
                    meshName,
                    sceneNode,
                    entity))
            {
                if (!g_ChunkMeshProxyFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Entity creation failed mesh=%hs node=0x%08X entity=0x%08X\n",
                        meshName,
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sceneNode)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entity)));
                    g_ChunkMeshProxyFailureLogged = true;
                }
                g_ChunkMeshProxyLastRetryTick = now;
                return false;
            }

            slot.sceneNode = sceneNode;
            slot.entity = entity;
            slot.sceneManager = sceneManager;
            g_ChunkMeshProxyLastRetryTick = 0;
            g_ChunkMeshProxyFailureLogged = false;
            g_ChunkMeshProxyWaitLogged = false;
            if (!g_ChunkMeshProxyInitLogged)
            {
                LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Initialized chunk mesh proxy mesh=%hs\n", meshName);
                g_ChunkMeshProxyInitLogged = true;
            }
            return true;
        }

        static bool EnsureChunkProxyResources()
        {
            if (!g_EnableChunkProxyDebug)
                return false;

            if (g_ChunkProxyBillboardSet)
                return true;

            const DWORD now = GetTickCount();
            if (g_ChunkProxyLastRetryTick != 0 &&
                static_cast<DWORD>(now - g_ChunkProxyLastRetryTick) < kChunkProxyRetryDelayMs)
            {
                return false;
            }
            g_ChunkProxyLastRetryTick = now;

            static FnOgreGetRootSceneNode getRootSceneNode =
                ResolveOgreProc<FnOgreGetRootSceneNode>("?getRootSceneNode@SceneManager@Ogre@@UAEPAVSceneNode@2@XZ");
            static FnOgreCreateBillboardSet createBillboardSet =
                ResolveOgreProc<FnOgreCreateBillboardSet>("?createBillboardSet@SceneManager@Ogre@@UAEPAVBillboardSet@2@I@Z");
            static FnOgreAttachObject attachObject =
                ResolveOgreProc<FnOgreAttachObject>("?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
            static FnOgreSetBillboardsInWorldSpace setBillboardsInWorldSpace =
                ResolveOgreProc<FnOgreSetBillboardsInWorldSpace>("?setBillboardsInWorldSpace@BillboardSet@Ogre@@UAEX_N@Z");
            static FnOgreSetDefaultDimensions setDefaultDimensions =
                ResolveOgreProc<FnOgreSetDefaultDimensions>("?setDefaultDimensions@BillboardSet@Ogre@@UAEXMM@Z");
            static FnOgreCreateBillboard createBillboard =
                ResolveOgreProc<FnOgreCreateBillboard>("?createBillboard@BillboardSet@Ogre@@QAEPAVBillboard@2@MMMABVColourValue@2@@Z");

            if (!getRootSceneNode || !attachObject || !setBillboardsInWorldSpace ||
                !setDefaultDimensions || !createBillboard)
            {
                if (!g_ChunkProxyFailureLogged)
                {
                    LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] Missing Ogre billboard symbols; proxy debug disabled for now\n");
                    g_ChunkProxyFailureLogged = true;
                }
                return false;
            }

            void* sceneManager = GetOgreSceneManagerRuntime();
            if (!sceneManager)
            {
                if (!g_ChunkProxyWaitLogged)
                {
                    LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] Scene manager unavailable; waiting to initialize chunk proxy debug\n");
                    g_ChunkProxyWaitLogged = true;
                }
                return false;
            }

            void* rootNode = nullptr;
            void* billboardSet = nullptr;
            if (!TryCreateChunkProxyBillboardSet(
                    sceneManager,
                    getRootSceneNode,
                    createBillboardSet,
                    rootNode,
                    billboardSet))
            {
                if (!g_ChunkProxyFailureLogged)
                {
                    LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] BillboardSet creation failed sceneManager=0x%08X root=0x%08X set=0x%08X\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sceneManager)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(rootNode)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(billboardSet)));
                    g_ChunkProxyFailureLogged = true;
                }
                return false;
            }

            if (!TrySetupChunkProxyBillboardSet(
                    rootNode,
                    billboardSet,
                    attachObject,
                    setBillboardsInWorldSpace,
                    setDefaultDimensions))
            {
                if (!g_ChunkProxyFailureLogged)
                {
                    LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] BillboardSet setup fault set=0x%08X code=0x%08X\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(billboardSet)),
                        0u);
                    g_ChunkProxyFailureLogged = true;
                }
                return false;
            }

            if (g_ChunkProxySlots.size() != g_ChunkProxyCapacity)
                g_ChunkProxySlots.resize(g_ChunkProxyCapacity);
            const OgreColourValue color = { 1.0f, 0.35f, 0.05f, 0.9f };
            for (uint32_t index = 0; index < g_ChunkProxyCapacity; ++index)
            {
                void* billboard = TryCreateChunkProxyBillboard(billboardSet, createBillboard, color);
                g_ChunkProxySlots[index].billboard = billboard;
                g_ChunkProxySlots[index].billboardAssigned = false;
                HideChunkProxyBillboard(billboard);
            }

            g_ChunkProxyBillboardSet = billboardSet;
            g_ChunkProxyFailureLogged = false;
            g_ChunkProxyWaitLogged = false;
            if (!g_ChunkProxyInitLogged)
            {
                LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] Initialized billboard debug set=0x%08X cap=%u size=%.2f\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(billboardSet)),
                    g_ChunkProxyCapacity,
                    g_ChunkProxyDebugSize);
                g_ChunkProxyInitLogged = true;
            }

            return true;
        }

        static void ReleaseChunkProxySlot(ChunkProxySlot& slot, const wchar_t* reason = nullptr)
        {
            if (slot.active && reason && AcquireChunkLogSlot())
            {
                LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] release obj=0x%08X billboard=0x%08X entity=0x%08X geom=0x%08X geomName=%hs geomKind=%hs reason=%ls\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.billboard)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.geomRef)),
                    GetChunkGeomNameForLog(slot.geomName),
                    ClassifyChunkGeomName(slot.geomName),
                    reason);
            }

            if (slot.billboardAssigned)
                HideChunkProxyBillboard(slot.billboard);
            if (slot.sceneNode || slot.entity || slot.meshAssigned)
                InvalidateChunkMeshProxySlot(slot);
            slot.objectBytes = nullptr;
            slot.geomRef = nullptr;
            slot.geomName[0] = '\0';
            slot.ownerEntity = nullptr;
            slot.ownerEntityBaseName[0] = '\0';
            slot.ownerOgreFilename[0] = '\0';
            slot.proofMeshName[0] = '\0';
            slot.positionX = 0.0f;
            slot.positionY = 0.0f;
            slot.positionZ = 0.0f;
            slot.useEntryPosition = false;
            slot.lastSeenTick = 0;
            slot.active = false;
            slot.billboardAssigned = false;
            slot.meshAssigned = false;
            slot.genericBatchKind = 0;
            slot.genericBatchTransformReady = false;
        }

        // Drops every Ogre reference a slot holds WITHOUT calling into Ogre.
        // Used when the referenced objects are already destroyed (or about to
        // be): scene teardown, or an access fault while touching the entity.
        static void ForgetChunkProxySlotOgreRefs(ChunkProxySlot& slot)
        {
            slot.billboard = nullptr;
            slot.billboardAssigned = false;
            slot.sceneNode = nullptr;
            slot.entity = nullptr;
            slot.meshAssigned = false;
            slot.sceneManager = nullptr;
            slot.objectBytes = nullptr;
            slot.geomRef = nullptr;
            slot.geomName[0] = '\0';
            slot.ownerEntity = nullptr;
            slot.ownerEntityBaseName[0] = '\0';
            slot.ownerOgreFilename[0] = '\0';
            slot.proofMeshName[0] = '\0';
            slot.sourceRootObject = nullptr;
            slot.ownerObj = nullptr;
            slot.sourceGameObject = nullptr;
            slot.sourceRootGameObject = nullptr;
            slot.useEntryPosition = false;
            slot.lastSeenTick = 0;
            slot.active = false;
            slot.genericBatchKind = 0;
            slot.genericBatchTransformReady = false;
        }

        // Save-load and mission teardown destroy the whole Ogre scene
        // (SceneManager::clearScene / destroyAllMovableObjects), taking our
        // proxy billboard set, scene nodes, and entities with it. Any later
        // touch of those pointers is a use-after-free: crash dump 35064 was
        // Entity::isVisible on a destroyed chunk entity while the loading
        // screen still rendered frames. Forget everything without calling
        // into Ogre; resources are lazily recreated on the next tick.
        void ForgetAllChunkProxySceneResources(const wchar_t* reason)
        {
            size_t forgotten = 0;
            for (ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (slot.active || slot.entity || slot.sceneNode || slot.billboard)
                    ++forgotten;
                ForgetChunkProxySlotOgreRefs(slot);
            }
            g_ChunkProxyBillboardSet = nullptr;
            g_GenericChunkBatchManualObject = nullptr;
            // The recorded visibility described the object just dropped.
            g_GenericChunkBatchVisible = false;
            g_GenericChunkBatchSceneNode = nullptr;
            // A destroyed scene invalidates the cached geometry too.
            g_GenericChunkBatchBuiltVersion =
                ChunkBatchInvalidation::kUnbuiltVersion;
            g_GenericChunkBatchBuiltMaterial.clear();
            g_GenericChunkBatchSceneManager = nullptr;
            g_GenericChunkBatchSectionCreated = false;

            if (forgotten > 0)
            {
                LogChunkDiagnostic(
                    "chunkproxy",
                    L"[CHUNKPROXY] scene teardown (%ls): forgot %zu slot(s) and the billboard set\n",
                    reason ? reason : L"<none>",
                    forgotten);
            }
        }

        static void LogChunkManualSubmitSkip(
            const ChunkProxySlot& slot,
            const wchar_t* reason,
            void* sceneManager,
            void* viewport,
            void* hintedCamera,
            void* resolvedCamera)
        {
            static volatile long s_ManualSubmitSkipBudget = 24;
            const long remaining = InterlockedDecrement(&s_ManualSubmitSkipBudget);
            if (remaining < 0)
                return;

            LogChunkDiagnostic(
                "chunkmesh",
                L"[CHUNKMESH] manual-submit-skip obj=0x%08X entity=0x%08X mesh=%hs reason=%ls sceneMgr=0x%08X viewport=0x%08X hintedCamera=0x%08X camera=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                GetChunkPayloadMeshName(slot),
                reason ? reason : L"<none>",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sceneManager)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(viewport)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(hintedCamera)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(resolvedCamera)));
        }

        static void* TryGetChunkProxyViewportCameraSafe(
            void* sceneManager,
            FnOgreGetCurrentViewport getCurrentViewport,
            FnOgreViewportGetCamera getViewportCamera,
            void** outViewport,
            void* fallbackCamera)
        {
            if (outViewport)
                *outViewport = nullptr;
            if (!sceneManager || !getCurrentViewport)
                return fallbackCamera;

            void* viewportCamera = nullptr;
            __try
            {
                if (!CatchOgreThrow("viewportCamera", [&] {
                        void* viewport = getCurrentViewport(sceneManager);
                        if (outViewport)
                            *outViewport = viewport;
                        if (viewport && getViewportCamera)
                            viewportCamera = getViewportCamera(viewport);
                    }))
                {
                    viewportCamera = nullptr;
                }
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                viewportCamera = nullptr;
            }

            return viewportCamera ? viewportCamera : fallbackCamera;
        }

        // A chunk mesh has a handful of sub-entities. A destroyed Entity whose
        // allocation has been recycled usually does not fault on this read --
        // it just returns whatever the reused memory holds. Freeze
        // C:\BZDumps\hang2_34268.dmp came back with 0x0086C62F (8,832,559)
        // here, and the caller then took one swallowed access violation per
        // iteration; SEH dispatch is a kernel transition, so a single stale
        // slot cost minutes of CPU per frame and read as a hang rather than a
        // crash. Treat an implausible count as proof the entity is stale.
        static constexpr uint32_t kChunkProxyMaxSubEntities = 32;

        static uint32_t TryGetChunkProxySubEntityCountSafe(
            void* entity,
            FnOgreGetNumSubEntities getNumSubEntities,
            bool* faulted = nullptr)
        {
            if (faulted)
                *faulted = false;
            if (!entity || !getNumSubEntities)
                return 0;

            uint32_t count = 0;
            __try
            {
                if (!CatchOgreThrow("numSubEntities", [&] { count = getNumSubEntities(entity); }))
                {
                    if (faulted)
                        *faulted = true;
                    return 0;
                }
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                if (faulted)
                    *faulted = true;
                return 0;
            }
            if (count > kChunkProxyMaxSubEntities)
            {
                if (faulted)
                    *faulted = true;
                return 0;
            }
            return count;
        }

        static void* TryGetChunkProxySubEntitySafe(
            void* entity,
            uint32_t index,
            FnOgreGetSubEntity getSubEntity)
        {
            if (!entity || !getSubEntity)
                return nullptr;

            void* subEntity = nullptr;
            __try
            {
                if (!CatchOgreThrow("subEntity", [&] { subEntity = getSubEntity(entity, index); }))
                    subEntity = nullptr;
                return subEntity;
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return nullptr;
            }
        }

        // The entity a slot references can be destroyed behind our back by a
        // scene teardown we did not observe (the teardown hooks cover the
        // known paths, these guards cover the unknown ones). On a fault the
        // caller must forget the slot's Ogre refs instead of releasing them
        // through Ogre calls.
        static bool TryNotifyChunkProxyCameraSafe(
            void* entity,
            void* camera,
            FnOgreMovableObjectNotifyCurrentCamera notifyCurrentCamera)
        {
            if (!entity || !camera || !notifyCurrentCamera)
                return false;

            __try
            {
                return CatchOgreThrow("notifyCurrentCamera", [&] { notifyCurrentCamera(entity, camera); });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        // Returns 1/0 for the entity's visibility, or -1 if reading it faulted.
        static int TryGetChunkProxyVisibleSafe(void* entity, FnOgreIsVisible isVisible)
        {
            if (!entity || !isVisible)
                return 1;

            int visible = -1;
            __try
            {
                if (!CatchOgreThrow("isVisible", [&] { visible = isVisible(entity) ? 1 : 0; }))
                    visible = -1;
                return visible;
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return -1;
            }
        }

        static bool TryUpdateChunkProxyRenderQueueSafe(
            void* entity,
            void* renderQueue,
            FnOgreEntityUpdateRenderQueue updateRenderQueue)
        {
            if (!entity || !renderQueue || !updateRenderQueue)
                return false;

            __try
            {
                return CatchOgreThrow("updateRenderQueue", [&] { updateRenderQueue(entity, renderQueue); });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        static bool IsLikelyLiveOgreObject(const void* object)
        {
            if (!object)
                return false;

            void* vtable = nullptr;
            __try
            {
                vtable = *reinterpret_cast<void* const*>(object);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }

            HMODULE ogreMain = GetModuleHandleA("OgreMain.dll");
            if (!vtable || !ogreMain)
                return false;

            MEMORY_BASIC_INFORMATION mbi = {};
            return VirtualQuery(vtable, &mbi, sizeof(mbi)) == sizeof(mbi) &&
                mbi.State == MEM_COMMIT &&
                mbi.Type == MEM_IMAGE &&
                mbi.AllocationBase == ogreMain;
        }

        static bool TryAddChunkProxyRenderableSafe(
            void* renderQueue,
            void* renderable,
            uint8_t groupId,
            uint16_t priority,
            FnOgreRenderQueueAddRenderablePriority addRenderablePriority)
        {
            // A freed SubEntity can remain in committed heap memory long enough
            // for Entity::getSubEntity to return it successfully. Validate its
            // vtable before Ogre dereferences it, then contain any access fault
            // from a teardown race we could not observe in advance.
            if (!renderQueue || !addRenderablePriority ||
                !IsLikelyLiveOgreObject(renderable))
            {
                return false;
            }

            __try
            {
                return CatchOgreThrow("addRenderable", [&] { addRenderablePriority(renderQueue, renderable, groupId, priority); });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        static uint8_t TryGetChunkProxyRenderQueueGroupSafe(
            void* entity,
            FnOgreGetRenderQueueGroup getRenderQueueGroup,
            bool* outFaulted = nullptr)
        {
            if (outFaulted)
                *outFaulted = false;
            if (!entity || !getRenderQueueGroup)
                return 50u;

            uint8_t group = 50u;
            __try
            {
                if (!CatchOgreThrow("renderQueueGroup", [&] { group = getRenderQueueGroup(entity); }))
                {
                    if (outFaulted)
                        *outFaulted = true;
                    return 50u;
                }
                return group;
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                if (outFaulted)
                    *outFaulted = true;
                return 50u;
            }
        }

        using FnOgreCameraGetDerivedPosition = const OgreVector3&(__thiscall*)(void*);

        static bool TryGetChunkProxyCameraPositionSafe(
            void* camera,
            FnOgreCameraGetDerivedPosition getCameraDerivedPosition,
            OgreVector3& outPos)
        {
            if (!camera || !getCameraDerivedPosition)
                return false;

            __try
            {
                return CatchOgreThrow("cameraPosition", [&] { outPos = getCameraDerivedPosition(camera); });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        static bool TrySubmitChunkMeshProxyToCurrentRenderQueue(
            ChunkProxySlot& slot,
            void* currentCamera)
        {
            if (!slot.active || !slot.entity)
                return false;

            static FnOgreGetRenderQueue getRenderQueue =
                ResolveOgreProc<FnOgreGetRenderQueue>("?getRenderQueue@SceneManager@Ogre@@UAEPAVRenderQueue@2@XZ");
            static FnOgreMovableObjectNotifyCurrentCamera notifyCurrentCamera =
                nullptr;
            static FnOgreEntityUpdateRenderQueue updateRenderQueue =
                nullptr;
            static FnOgreRenderQueueAddRenderablePriority addRenderablePriority =
                ResolveOgreProcByOffset<FnOgreRenderQueueAddRenderablePriority>(0x00026850);
            static FnOgreGetCurrentViewport getCurrentViewport =
                ResolveOgreProc<FnOgreGetCurrentViewport>("?getCurrentViewport@SceneManager@Ogre@@QBEPAVViewport@2@XZ");
            static FnOgreViewportGetCamera getViewportCamera =
                ResolveOgreProc<FnOgreViewportGetCamera>("?getCamera@Viewport@Ogre@@QBEPAVCamera@2@XZ");
            static FnOgreIsVisible isVisible =
                ResolveOgreProcByOffset<FnOgreIsVisible>(0x0002CCCD);
            static FnOgreGetRenderQueueGroup getRenderQueueGroup =
                ResolveOgreProcByOffset<FnOgreGetRenderQueueGroup>(0x0001584D);
            static FnOgreGetNumSubEntities getNumSubEntities =
                ResolveOgreProc<FnOgreGetNumSubEntities>("?getNumSubEntities@Entity@Ogre@@QBEIXZ");
            static FnOgreGetSubEntity getSubEntity =
                ResolveOgreProc<FnOgreGetSubEntity>("?getSubEntity@Entity@Ogre@@QBEPAVSubEntity@2@I@Z");

            if (!notifyCurrentCamera)
            {
                notifyCurrentCamera = g_OgreFn_MovableObjectNotifyCurrentCamera
                    ? g_OgreFn_MovableObjectNotifyCurrentCamera
                    : ResolveOgreProc<FnOgreMovableObjectNotifyCurrentCamera>(
                        "?_notifyCurrentCamera@Entity@Ogre@@UAEXPAVCamera@2@@Z");
            }
            if (!updateRenderQueue)
            {
                updateRenderQueue = g_OgreFn_EntityUpdateRenderQueue
                    ? g_OgreFn_EntityUpdateRenderQueue
                    : ResolveOgreProc<FnOgreEntityUpdateRenderQueue>(
                        "?_updateRenderQueue@Entity@Ogre@@UAEXPAVRenderQueue@2@@Z");
            }

            void* sceneManager = slot.sceneManager ? slot.sceneManager : GetOgreSceneManagerRuntime();
            void* viewport = nullptr;
            void* resolvedCamera = TryGetChunkProxyViewportCameraSafe(
                sceneManager,
                getCurrentViewport,
                getViewportCamera,
                &viewport,
                currentCamera);

            if (!sceneManager)
            {
                LogChunkManualSubmitSkip(slot, L"scene-manager-null", sceneManager, viewport, currentCamera, resolvedCamera);
                return false;
            }
            if (!resolvedCamera)
            {
                LogChunkManualSubmitSkip(slot, L"camera-null", sceneManager, viewport, currentCamera, resolvedCamera);
                return false;
            }
            if (!getRenderQueue)
            {
                LogChunkManualSubmitSkip(slot, L"get-render-queue-missing", sceneManager, viewport, currentCamera, resolvedCamera);
                return false;
            }
            if (!notifyCurrentCamera || (!updateRenderQueue && !addRenderablePriority))
            {
                LogChunkManualSubmitSkip(slot, L"submit-procs-missing", sceneManager, viewport, currentCamera, resolvedCamera);
                return false;
            }

            void* renderQueue = getRenderQueue(sceneManager);
            if (!renderQueue)
            {
                LogChunkManualSubmitSkip(slot, L"render-queue-null", sceneManager, viewport, currentCamera, resolvedCamera);
                return false;
            }

            bool visibleNow = true;
            if (!TryNotifyChunkProxyCameraSafe(slot.entity, resolvedCamera, notifyCurrentCamera))
            {
                LogChunkManualSubmitSkip(slot, L"entity-fault-notify", sceneManager, viewport, currentCamera, resolvedCamera);
                ForgetChunkProxySlotOgreRefs(slot);
                return false;
            }
            if (slot.cameraNotifyCount < USHRT_MAX)
                ++slot.cameraNotifyCount;

            if (isVisible)
            {
                const int visibleProbe = TryGetChunkProxyVisibleSafe(slot.entity, isVisible);
                if (visibleProbe < 0)
                {
                    LogChunkManualSubmitSkip(slot, L"entity-fault-visible", sceneManager, viewport, currentCamera, resolvedCamera);
                    ForgetChunkProxySlotOgreRefs(slot);
                    return false;
                }
                visibleNow = visibleProbe != 0;
            }

            uint32_t directAddCount = 0;
            if (visibleNow && updateRenderQueue)
            {
                if (!TryUpdateChunkProxyRenderQueueSafe(slot.entity, renderQueue, updateRenderQueue))
                {
                    LogChunkManualSubmitSkip(slot, L"entity-fault-update-queue", sceneManager, viewport, currentCamera, resolvedCamera);
                    ForgetChunkProxySlotOgreRefs(slot);
                    return false;
                }
                if (slot.entityUpdateQueueCount < USHRT_MAX)
                    ++slot.entityUpdateQueueCount;
            }
            else if (visibleNow && addRenderablePriority && getNumSubEntities && getSubEntity)
            {
                bool groupFaulted = false;
                const uint8_t groupId =
                    TryGetChunkProxyRenderQueueGroupSafe(slot.entity, getRenderQueueGroup, &groupFaulted);
                if (groupFaulted)
                {
                    LogChunkManualSubmitSkip(slot, L"entity-fault-queue-group", sceneManager, viewport, currentCamera, resolvedCamera);
                    ForgetChunkProxySlotOgreRefs(slot);
                    return false;
                }
                bool countFaulted = false;
                const uint32_t subEntityCount = TryGetChunkProxySubEntityCountSafe(
                    slot.entity, getNumSubEntities, &countFaulted);
                if (countFaulted)
                {
                    LogChunkManualSubmitSkip(slot, L"entity-fault-sub-entity-count", sceneManager, viewport, currentCamera, resolvedCamera);
                    ForgetChunkProxySlotOgreRefs(slot);
                    return false;
                }

                for (uint32_t index = 0; index < subEntityCount; ++index)
                {
                    void* const subEntity =
                        TryGetChunkProxySubEntitySafe(slot.entity, index, getSubEntity);

                    // A live Entity never returns null below its own count, so
                    // this is a stale entity. Stop touching it immediately
                    // rather than faulting once per remaining index.
                    if (!subEntity)
                    {
                        LogChunkManualSubmitSkip(slot, L"entity-fault-sub-entity", sceneManager, viewport, currentCamera, resolvedCamera);
                        ForgetChunkProxySlotOgreRefs(slot);
                        return false;
                    }

                    if (!TryAddChunkProxyRenderableSafe(
                            renderQueue,
                            subEntity,
                            groupId,
                            100u,
                            addRenderablePriority))
                    {
                        LogChunkManualSubmitSkip(
                            slot,
                            L"sub-entity-stale",
                            sceneManager,
                            viewport,
                            currentCamera,
                            resolvedCamera);
                        ForgetChunkProxySlotOgreRefs(slot);
                        return false;
                    }
                    ++directAddCount;
                    if (slot.renderQueueAddCount < USHRT_MAX)
                        ++slot.renderQueueAddCount;
                }
            }

            if (isVisible)
            {
                const int visibleProbe = TryGetChunkProxyVisibleSafe(slot.entity, isVisible);
                if (visibleProbe >= 0)
                    visibleNow = visibleProbe != 0;
            }

            // Camera world position tells us whether the render camera lives in
            // the same coordinate space as the sim positions we mirror onto the
            // proxy nodes; a camera near the origin while chunks sit at ~1e5
            // would mean a render-space offset we are not applying.
            static FnOgreCameraGetDerivedPosition getCameraDerivedPosition =
                ResolveOgreProc<FnOgreCameraGetDerivedPosition>("?getDerivedPosition@Camera@Ogre@@QBEABVVector3@2@XZ");
            OgreVector3 cameraPos = { 0.0f, 0.0f, 0.0f };
            const bool haveCameraPos = TryGetChunkProxyCameraPositionSafe(
                resolvedCamera, getCameraDerivedPosition, cameraPos);

            static volatile long s_FirstManualSubmitLogBudget = 12;
            if ((slot.cameraNotifyCount <= 4 || slot.entityUpdateQueueCount <= 4 || slot.renderQueueAddCount <= 4) &&
                InterlockedDecrement(&s_FirstManualSubmitLogBudget) >= 0)
            {
                LogChunkDiagnostic(
                    "chunkmesh",
                    L"[CHUNKMESH] manual-submit-campos have=%u pos=(%.2f, %.2f, %.2f)\n",
                    haveCameraPos ? 1u : 0u,
                    static_cast<double>(cameraPos.x),
                    static_cast<double>(cameraPos.y),
                    static_cast<double>(cameraPos.z));
                LogChunkDiagnostic(
                    "chunkmesh",
                    L"[CHUNKMESH] manual-submit obj=0x%08X entity=0x%08X mesh=%hs sceneMgr=0x%08X viewport=0x%08X queue=0x%08X camera=0x%08X source=%hs visibleNow=%u notifyCount=%u updateCount=%u addCount=%u\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                    GetChunkPayloadMeshName(slot),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sceneManager)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(viewport)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(renderQueue)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(resolvedCamera)),
                    (viewport && resolvedCamera && resolvedCamera != currentCamera) ? "viewport" :
                    (currentCamera ? "hint" : "none"),
                    visibleNow ? 1u : 0u,
                    static_cast<unsigned>(slot.cameraNotifyCount),
                    static_cast<unsigned>(slot.entityUpdateQueueCount),
                    static_cast<unsigned>(slot.renderQueueAddCount));
            }

            return visibleNow;
        }

        static bool IsChunkManualSubmitEnabled()
        {
            static const bool disabled =
                EnvFlagEnabled("OPENSHIM_DISABLE_CHUNK_MANUAL_SUBMIT") ||
                EnvFlagEnabled("BZR_DISABLE_CHUNK_MANUAL_SUBMIT");
            return !disabled;
        }

        // Reads the geo-local vertex bounds straight out of the Redux geom
        // struct (vertex count at +0x04, position array at +0x0C, 3 floats
        // per vertex) so payload mesh pivots can be compared against the
        // original geo pivots the chunk sim rotates around.
        static bool TryComputeChunkGeomLocalBounds(
            const void* geomRef,
            uint32_t& outCount,
            float outMin[3],
            float outMax[3])
        {
            outCount = 0;
            if (!geomRef)
                return false;

            __try
            {
                const auto* geomBytes = reinterpret_cast<const uint8_t*>(geomRef);
                const uint32_t count = *reinterpret_cast<const uint32_t*>(geomBytes + 0x04);
                const float* verts = *reinterpret_cast<const float* const*>(geomBytes + 0x0C);
                if (!verts || count == 0 || count > 65536)
                    return false;

                for (uint32_t i = 0; i < count; ++i)
                {
                    const float* v = verts + (static_cast<size_t>(i) * 3);
                    for (int axis = 0; axis < 3; ++axis)
                    {
                        if (i == 0 || v[axis] < outMin[axis])
                            outMin[axis] = v[axis];
                        if (i == 0 || v[axis] > outMax[axis])
                            outMax[axis] = v[axis];
                    }
                }

                outCount = count;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outCount = 0;
                return false;
            }
        }

        // Redux renders around a per-map origin (terrain center, the
        // Ogre::Vector3 global at kGogWorldRenderOriginAddr) with the Z axis
        // mirrored versus sim space. The camera, lights, and every world
        // renderable go through this conversion inside the exe, so proxy
        // nodes fed raw sim coordinates land ~1e5 units outside the render
        // world and never appear on screen.
        static bool TryConvertChunkSimTransformToRenderSpace(ChunkProxyTransform& transform)
        {
            float origin[3] = {};

            __try
            {
                const float* originPtr = reinterpret_cast<const float*>(kGogWorldRenderOriginAddr);
                origin[0] = originPtr[0];
                origin[1] = originPtr[1];
                origin[2] = originPtr[2];
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }

            static volatile long s_OriginLogBudget = 1;
            if (InterlockedDecrement(&s_OriginLogBudget) >= 0)
            {
                LogChunkDiagnostic(
                    "chunkmesh",
                    L"[CHUNKMESH] render-origin=(%.2f, %.2f, %.2f)\n",
                    static_cast<double>(origin[0]),
                    static_cast<double>(origin[1]),
                    static_cast<double>(origin[2]));
            }

            transform.x = transform.x - origin[0];
            transform.y = transform.y - origin[1];
            transform.z = -transform.z - origin[2];
            // Conjugating a rotation by the Z mirror negates the quaternion
            // X/Y components (X/Y rotations flip direction, Z rotations do
            // not).
            transform.orientation.x = -transform.orientation.x;
            transform.orientation.y = -transform.orientation.y;
            return true;
        }

        static bool TryHashGenericChunkPayload(
            const std::filesystem::path& path,
            uintmax_t expectedBytes,
            uint64_t& outHash)
        {
            outHash = 0;
            std::error_code error;
            if (!std::filesystem::is_regular_file(path, error) || error ||
                std::filesystem::file_size(path, error) != expectedBytes || error)
            {
                return false;
            }

            std::ifstream input(path, std::ios::binary);
            if (!input)
                return false;

            uint64_t hash = 14695981039346656037ull;
            std::array<char, 4096> buffer = {};
            while (input)
            {
                input.read(buffer.data(), buffer.size());
                const std::streamsize count = input.gcount();
                for (std::streamsize index = 0; index < count; ++index)
                {
                    hash ^= static_cast<uint8_t>(buffer[static_cast<size_t>(index)]);
                    hash *= 1099511628211ull;
                }
            }
            if (!input.eof())
                return false;

            outHash = hash;
            return true;
        }

        static bool IsCanonicalGenericChunkPayload(uint8_t kind)
        {
            if (kind < 1 || kind > 2)
                return false;

            int& cached = g_GenericChunkBatchEligibility[kind - 1];
            if (cached >= 0)
                return cached != 0;

            if (g_ChunkPayloadResourceDirectories.empty())
                RefreshChunkPayloadResourceDirectories();

            const std::filesystem::path relativePath = kind == 1
                ? std::filesystem::path("chunk1") / "chunk1.mesh"
                : std::filesystem::path("chunk2") / "chunk2.mesh";
            const uintmax_t expectedBytes = kind == 1
                ? kChunk1MeshBytes : kChunk2MeshBytes;
            const uint64_t expectedHash = kind == 1
                ? kChunk1MeshFnv1a : kChunk2MeshFnv1a;

            bool found = false;
            bool canonical = true;
            for (const std::filesystem::path& root : g_ChunkPayloadResourceDirectories)
            {
                const std::filesystem::path candidate = root / relativePath;
                std::error_code existsError;
                if (!std::filesystem::exists(candidate, existsError) || existsError)
                    continue;

                found = true;
                uint64_t actualHash = 0;
                if (!TryHashGenericChunkPayload(
                        candidate, expectedBytes, actualHash) ||
                    actualHash != expectedHash)
                {
                    canonical = false;
                    break;
                }
            }

            cached = found && canonical ? 1 : 0;
            LogChunkDiagnostic(
                "chunkbatch",
                L"[CHUNKBATCH] canonical chunk%u batching=%hs roots=%zu expectedBytes=%zu hash=0x%016llX\n",
                static_cast<unsigned>(kind),
                cached ? "enabled" : "fallback-entity",
                g_ChunkPayloadResourceDirectories.size(),
                static_cast<size_t>(expectedBytes),
                static_cast<unsigned long long>(expectedHash));
            return cached != 0;
        }

        // The batch bakes every chunklet into one shared ManualObject section,
        // and AppendGenericChunkBatchGeometry() applies orientation and
        // translation only -- there is no per-chunk node left to carry a
        // scale. Batching a scaled chunk would therefore render it at the
        // wrong size with no way to notice.
        //
        // Today ChunkProxyTransform::scale is structurally unit: the legacy
        // basis vectors are normalised when the quaternion is built, so no
        // code path ever populates a non-unit value. This gate exists so that
        // stays an enforced invariant rather than an assumption -- if a future
        // change or runtime does populate scale, the chunk falls back to the
        // per-Entity path instead of being silently mis-sized.
        //
        // Correct arbitrary scale in the batch would additionally require
        // inverse-transpose handling for normals and tangents. That is not
        // implemented deliberately: no evidence shows stock or modded generic
        // chunklets need it, and the fallback path already renders them.
        static bool IsUnitScaleForGenericChunkBatch(const OgreVector3& scale)
        {
            // Loose enough to absorb float round-trips through a matrix
            // decomposition, tight enough that a real authored scale (the
            // smallest plausible being a few percent) is always rejected.
            constexpr float kEpsilon = 1.0e-3f;
            const float components[3] = { scale.x, scale.y, scale.z };
            for (const float component : components)
            {
                if (!std::isfinite(component) ||
                    std::fabs(component - 1.0f) > kEpsilon)
                {
                    return false;
                }
            }
            return true;
        }

        static void NoteGenericChunkBatchScaleRejection(const OgreVector3& scale)
        {
            ++g_GenericChunkBatchNonUnitScaleRejections;
            const DWORD now = GetTickCount();
            if (g_GenericChunkBatchScaleLogTick != 0 &&
                static_cast<DWORD>(now - g_GenericChunkBatchScaleLogTick) < 5000)
            {
                return;
            }
            g_GenericChunkBatchScaleLogTick = now;
            LogChunkDiagnostic(
                "chunkbatch",
                L"[CHUNKBATCH] non-unit scale (%.4f, %.4f, %.4f); per-entity fallback, total=%llu\n",
                static_cast<double>(scale.x),
                static_cast<double>(scale.y),
                static_cast<double>(scale.z),
                static_cast<unsigned long long>(
                    g_GenericChunkBatchNonUnitScaleRejections));
        }

        static uint8_t GetGenericChunkBatchKind(const char* meshName)
        {
            if (!g_EnableGenericChunkBatch ||
                !g_GenericChunkBatchRuntimeAvailable || !meshName)
            {
                return 0;
            }
            if (_stricmp(meshName, "chunk1/chunk1.mesh") == 0)
                return IsCanonicalGenericChunkPayload(1) ? 1 : 0;
            if (_stricmp(meshName, "chunk2/chunk2.mesh") == 0)
                return IsCanonicalGenericChunkPayload(2) ? 2 : 0;
            return 0;
        }

        static void UpdateChunkProxySlotPosition(
            ChunkProxySlot& slot,
            void* currentCamera = nullptr,
            bool allowManualSubmit = true)
        {
            static FnOgreSetBillboardPosition setPosition =
                ResolveOgreProc<FnOgreSetBillboardPosition>("?setPosition@Billboard@Ogre@@QAEXMMM@Z");
            static FnOgreSetNodePosition setNodePosition =
                ResolveOgreProc<FnOgreSetNodePosition>("?setPosition@Node@Ogre@@UAEXMMM@Z");
            static FnOgreSetNodeOrientation setNodeOrientation =
                ResolveOgreProc<FnOgreSetNodeOrientation>("?setOrientation@Node@Ogre@@UAEXMMMM@Z");
            static FnOgreSetVisible setVisible =
                ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");
            if (!slot.active)
                return;

            slot.genericBatchKind = 0;
            slot.genericBatchTransformReady = false;

            if (slot.objectBytes)
            {
                const ChunkResolvedBindingEntry* binding =
                    FindChunkResolvedBindingEntryForGeom(slot.objectBytes, slot.geomName);
                if (binding && binding->payloadMeshName[0] &&
                    _stricmp(slot.proofMeshName, binding->payloadMeshName) != 0)
                {
                    if (AcquireChunkLogSlot())
                    {
                        LogChunkDiagnostic(
                            "chunkmesh",
                            L"[CHUNKMESH] rebinding obj=0x%08X oldMesh=%hs newMesh=%hs root=0x%08X rootGameObj=0x%08X ownerObj=0x%08X\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                            slot.proofMeshName[0] ? slot.proofMeshName : "<none>",
                            binding->payloadMeshName,
                            binding->sourceRootObjectPtr,
                            binding->sourceRootGameObjectPtr,
                            binding->sourceOwnerObjPtr);
                    }

                    InvalidateChunkMeshProxySlot(slot);
                    strncpy_s(slot.proofMeshName, sizeof(slot.proofMeshName), binding->payloadMeshName, _TRUNCATE);
                }
            }

            ChunkProxyTransform transform = {};
            const void* resolvedTransformObject = nullptr;
            bool haveTransform = TryResolveChunkProxyTransformForSlot(
                slot,
                transform,
                &resolvedTransformObject);

            if (haveTransform)
            {
                ChunkProxyTransform anchoredTransform = {};
                const void* anchorObject = nullptr;
                if (TryPromoteChunkProxyLocalTransformToAnchoredWorld(
                        slot,
                        transform,
                        resolvedTransformObject,
                        anchoredTransform,
                        &anchorObject))
                {
                    transform = anchoredTransform;
                    if (anchorObject)
                        resolvedTransformObject = anchorObject;
                }
                else if (slot.useEntryPosition && ShouldPreferChunkEntryPosition(slot, transform))
                {
                    transform.x = slot.positionX;
                    transform.y = slot.positionY;
                    transform.z = slot.positionZ;
                }
            }
            else if (slot.useEntryPosition)
            {
                const void* anchorObject = nullptr;
                if (TryBuildChunkProxyAnchoredEntryTransform(
                        slot,
                        nullptr,
                        transform,
                        &anchorObject))
                {
                    resolvedTransformObject = anchorObject;
                    haveTransform = true;
                }
                else
                {
                    transform.x = slot.positionX;
                    transform.y = slot.positionY;
                    transform.z = slot.positionZ;
                    transform.orientation = { 1.0f, 0.0f, 0.0f, 0.0f };
                    transform.scale = { 1.0f, 1.0f, 1.0f };
                    resolvedTransformObject = slot.objectBytes;
                    haveTransform = true;
                }
            }

            if (haveTransform && !TryConvertChunkSimTransformToRenderSpace(transform))
                haveTransform = false;

            const bool useMeshProxy = ShouldUseChunkPayloadMesh(slot);

            if (!useMeshProxy)
            {
                if (slot.billboard && haveTransform && setPosition)
                {
                    if (TrySetChunkProxyBillboardPosition(
                            slot.billboard,
                            setPosition,
                            transform.x,
                            transform.y,
                            transform.z))
                    {
                        slot.billboardAssigned = true;
                    }
                    else
                    {
                        LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Billboard setPosition failed for obj=0x%08X geom=0x%08X\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.geomRef)),
                            GetChunkGeomNameForLog(slot.geomName));
                    }
                }

                if (slot.meshAssigned)
                {
                    HideChunkProxyMesh(slot);
                    slot.meshAssigned = false;
                }
                return;
            }

            if (haveTransform)
            {
                uint8_t genericBatchKind =
                    GetGenericChunkBatchKind(slot.proofMeshName);
                if (genericBatchKind != 0 && g_ForceGenericChunkNonUnitScale)
                    transform.scale = { 1.25f, 0.75f, 1.0f };
                if (genericBatchKind != 0 &&
                    !IsUnitScaleForGenericChunkBatch(transform.scale))
                {
                    // Not batchable: fall through to the per-Entity fidelity
                    // path below, which keeps its own scene node.
                    NoteGenericChunkBatchScaleRejection(transform.scale);
                    genericBatchKind = 0;
                }
                if (genericBatchKind != 0)
                {
                    if (slot.meshAssigned)
                    {
                        HideChunkProxyMesh(slot);
                        slot.meshAssigned = false;
                    }
                    slot.genericBatchTransform = transform;
                    slot.genericBatchKind = genericBatchKind;
                    slot.genericBatchTransformReady = true;
                    return;
                }

                if (!EnsureChunkMeshProxySlot(slot))
                    return;

                const bool transformOk = TryUpdateChunkMeshProxyTransform(
                    slot.sceneNode,
                    slot.entity,
                    setNodePosition,
                    setNodeOrientation,
                    setVisible,
                    transform);

                static volatile long s_FirstMeshTransformLogBudget = 8;
                if (InterlockedDecrement(&s_FirstMeshTransformLogBudget) >= 0)
                {
                    LogChunkDiagnostic("chunkmesh",
                        L"[CHUNKMESH] first-transform obj=0x%08X node=0x%08X entity=0x%08X mesh=%hs ok=%u procs=%u/%u pos=(%.2f, %.2f, %.2f)\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.sceneNode)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                        GetChunkPayloadMeshName(slot),
                        transformOk ? 1u : 0u,
                        setNodePosition ? 1u : 0u,
                        setVisible ? 1u : 0u,
                        static_cast<double>(transform.x),
                        static_cast<double>(transform.y),
                        static_cast<double>(transform.z));
                }

                if (!transformOk)
                {
                    ReleaseChunkProxySlot(slot, L"mesh-set-failed");
                    return;
                }

                if (!slot.meshAssigned && AcquireChunkLogSlot())
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] assigned obj=0x%08X entity=0x%08X geom=0x%08X geomName=%hs mesh=%hs pos=(%.4f, %.4f, %.4f)\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.geomRef)),
                        GetChunkGeomNameForLog(slot.geomName),
                        GetChunkPayloadMeshName(slot),
                        static_cast<double>(transform.x),
                        static_cast<double>(transform.y),
                        static_cast<double>(transform.z));

                    uint32_t geoVertCount = 0;
                    float geoMin[3] = {};
                    float geoMax[3] = {};
                    if (TryComputeChunkGeomLocalBounds(slot.geomRef, geoVertCount, geoMin, geoMax))
                    {
                        LogChunkDiagnostic("chunkmesh",
                            L"[CHUNKMESH] geo-bounds geom=0x%08X name=%hs verts=%u center=(%.2f, %.2f, %.2f) size=(%.2f, %.2f, %.2f)\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.geomRef)),
                            GetChunkGeomNameForLog(slot.geomName),
                            geoVertCount,
                            static_cast<double>((geoMin[0] + geoMax[0]) * 0.5f),
                            static_cast<double>((geoMin[1] + geoMax[1]) * 0.5f),
                            static_cast<double>((geoMin[2] + geoMax[2]) * 0.5f),
                            static_cast<double>(geoMax[0] - geoMin[0]),
                            static_cast<double>(geoMax[1] - geoMin[1]),
                            static_cast<double>(geoMax[2] - geoMin[2]));
                    }
                }
                slot.meshAssigned = true;

                // Redux drives the Ogre render queue itself rather than letting
                // the scene manager traverse root-node children, so a positioned
                // visible entity still never draws. Inject it into the current
                // render queue while the game is submitting its own legacy
                // effects (EngineFlameSubmitHook passes the active camera).
                if (allowManualSubmit && IsChunkManualSubmitEnabled())
                    TrySubmitChunkMeshProxyToCurrentRenderQueue(slot, currentCamera);
            }
            else if (slot.meshAssigned)
            {
                HideChunkProxyMesh(slot);
                slot.meshAssigned = false;
            }
        }

        void TickChunkProxyDebug(
            void* currentCamera,
            bool allowManualSubmit)
        {
            if (!g_EnableChunkProxyDebug && !g_EnableChunkMeshProxy)
                return;

            if (g_EnableChunkProxyDebug)
                EnsureChunkProxyResources();
            if (g_ChunkProxySlots.empty())
                return;

            const DWORD now = GetTickCount();
            for (ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (!slot.active)
                    continue;

                if (slot.lastSeenTick == 0 ||
                    static_cast<DWORD>(now - slot.lastSeenTick) >= kChunkProxyExpireMs)
                {
                    ReleaseChunkProxySlot(slot, L"expired");
                    continue;
                }

                UpdateChunkProxySlotPosition(slot, currentCamera, allowManualSubmit);
            }
        }

        static OgreVector3 RotateGenericChunkVector(
            const OgreQuaternion& q,
            const OgreVector3& value)
        {
            const OgreVector3 qv = { q.x, q.y, q.z };
            const float dotQvValue =
                qv.x * value.x + qv.y * value.y + qv.z * value.z;
            const float dotQvQv = qv.x * qv.x + qv.y * qv.y + qv.z * qv.z;
            const OgreVector3 cross = {
                qv.y * value.z - qv.z * value.y,
                qv.z * value.x - qv.x * value.z,
                qv.x * value.y - qv.y * value.x
            };
            return {
                2.0f * dotQvValue * qv.x +
                    (q.w * q.w - dotQvQv) * value.x + 2.0f * q.w * cross.x,
                2.0f * dotQvValue * qv.y +
                    (q.w * q.w - dotQvQv) * value.y + 2.0f * q.w * cross.y,
                2.0f * dotQvValue * qv.z +
                    (q.w * q.w - dotQvQv) * value.z + 2.0f * q.w * cross.z
            };
        }

        static void AppendGenericChunkBatchGeometry(
            void* manualObject,
            const GenericChunkVertex* vertices,
            size_t vertexCount,
            const ChunkProxyTransform& transform,
            uint32_t& nextIndex,
            FnOgreManualObjectVertex3 position,
            FnOgreManualObjectVertex3 normal,
            FnOgreManualObjectVertex3 tangent,
            FnOgreManualObjectTexture2 textureCoord,
            FnOgreManualObjectIndex addIndex)
        {
            const uint32_t firstIndex = nextIndex;
            for (size_t index = 0; index < vertexCount; ++index)
            {
                const GenericChunkVertex& source = vertices[index];
                OgreVector3 transformedPosition = RotateGenericChunkVector(
                    transform.orientation, source.position);
                transformedPosition.x += transform.x;
                transformedPosition.y += transform.y;
                transformedPosition.z += transform.z;
                const OgreVector3 transformedNormal = RotateGenericChunkVector(
                    transform.orientation, source.normal);
                const OgreVector3 transformedTangent = RotateGenericChunkVector(
                    transform.orientation, source.tangent);

                position(
                    manualObject,
                    transformedPosition.x,
                    transformedPosition.y,
                    transformedPosition.z);
                normal(
                    manualObject,
                    transformedNormal.x,
                    transformedNormal.y,
                    transformedNormal.z);
                tangent(
                    manualObject,
                    transformedTangent.x,
                    transformedTangent.y,
                    transformedTangent.z);
                textureCoord(manualObject, source.u, source.v);
                ++nextIndex;
            }
            for (uint32_t index = firstIndex; index < nextIndex; ++index)
                addIndex(manualObject, index);
        }

        // Failure invariant for the generic chunk batch.
        //
        // UpdateChunkProxySlotPosition() hides (and for a slot born eligible,
        // never creates) the per-Entity mesh proxy the moment a slot is
        // classified batch-ready. From that point until the ManualObject is
        // successfully submitted, the *only* thing that will draw those
        // chunklets is the batch. So if RebuildAndSubmitGenericChunkBatch()
        // returns false, the per-Entity loop below cannot simply be allowed to
        // run: it skips any slot with a null `entity`, which is exactly the
        // slots that were classified batch-ready, and the debris disappears.
        //
        // Two different strengths of assurance apply here, and they should
        // not be conflated.
        //
        // Guaranteed by construction: batch ownership is always released.
        // genericBatchTransformReady/genericBatchKind are cleared before any
        // Ogre call and on every path, including both `continue`s below, so a
        // slot can never stay stranded claiming the batch owns it. That is
        // what makes the pre-fix pathological state unreachable.
        //
        // Attempted but not guaranteed: same-frame Entity restoration.
        // EnsureChunkMeshProxySlot() and TryUpdateChunkMeshProxyTransform()
        // can both fail (SceneManager unavailable, entity creation failure,
        // unresolved Ogre export). Such a slot is counted in `demoted` but
        // not in `restored`, is invisible for that one frame, and is retried
        // by the ordinary per-Entity path on later frames because its flags
        // are already clear. The forced-failure test observed
        // demoted == restored across 39,688 rehydrations, so restoration was
        // complete on the tested workload -- but this code does not prove it
        // must be.
        //
        // Recovering a partially constructed ManualObject is deliberately not
        // attempted -- the Entity path is the known-good fidelity path and is
        // cheap to rehydrate.
        static void RehydrateGenericChunkBatchSlotsToEntities(const wchar_t* reason)
        {
            static FnOgreSetNodePosition setNodePosition =
                ResolveOgreProc<FnOgreSetNodePosition>("?setPosition@Node@Ogre@@UAEXMMM@Z");
            static FnOgreSetNodeOrientation setNodeOrientation =
                ResolveOgreProc<FnOgreSetNodeOrientation>("?setOrientation@Node@Ogre@@UAEXMMMM@Z");
            static FnOgreSetVisible setVisible =
                ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");

            size_t demoted = 0;
            size_t restored = 0;
            for (ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (!slot.active || !slot.genericBatchTransformReady)
                    continue;

                const ChunkProxyTransform transform = slot.genericBatchTransform;
                // Clear first and unconditionally. Even if the Entity cannot
                // be built this frame (Ogre not ready), the slot must stop
                // claiming the batch owns it, or the per-Entity loop will keep
                // skipping it forever.
                slot.genericBatchTransformReady = false;
                slot.genericBatchKind = 0;
                ++demoted;

                if (!EnsureChunkMeshProxySlot(slot))
                    continue;
                if (!TryUpdateChunkMeshProxyTransform(
                        slot.sceneNode,
                        slot.entity,
                        setNodePosition,
                        setNodeOrientation,
                        setVisible,
                        transform))
                {
                    continue;
                }
                slot.meshAssigned = true;
                ++restored;
            }

            if (demoted == 0)
                return;

            g_GenericChunkBatchRehydrations += demoted;
            const DWORD now = GetTickCount();
            if (g_GenericChunkBatchRehydrateLogTick != 0 &&
                static_cast<DWORD>(now - g_GenericChunkBatchRehydrateLogTick) < 1000)
            {
                return;
            }
            g_GenericChunkBatchRehydrateLogTick = now;
            LogChunkDiagnostic(
                "chunkbatch",
                L"[CHUNKBATCH] rehydrate (%ls): demoted=%zu restored=%zu total=%llu runtimeAvailable=%u\n",
                reason ? reason : L"<none>",
                demoted,
                restored,
                static_cast<unsigned long long>(g_GenericChunkBatchRehydrations),
                g_GenericChunkBatchRuntimeAvailable ? 1u : 0u);
        }

        // High-resolution rebuild cost. Sampled unconditionally because the
        // rebuild path is already thousands of virtual Ogre calls, so two QPC
        // reads are noise -- and a cost figure that only exists when
        // diagnostics are on cannot be used to justify the optimization.
        static int64_t ReadChunkBatchQpc()
        {
            LARGE_INTEGER counter = {};
            QueryPerformanceCounter(&counter);
            return counter.QuadPart;
        }

        static void NoteChunkBatchRebuildCost(int64_t startTicks)
        {
            if (g_GenericChunkBatchQpcFrequency == 0)
            {
                LARGE_INTEGER frequency = {};
                QueryPerformanceFrequency(&frequency);
                g_GenericChunkBatchQpcFrequency = frequency.QuadPart;
            }
            if (g_GenericChunkBatchQpcFrequency <= 0)
                return;
            const int64_t elapsed = ReadChunkBatchQpc() - startTicks;
            if (elapsed <= 0)
                return;
            const uint64_t nanoseconds = static_cast<uint64_t>(
                (elapsed * 1000000000ll) / g_GenericChunkBatchQpcFrequency);
            g_GenericChunkBatchTelemetry.rebuildNanoseconds += nanoseconds;
            if (nanoseconds > g_GenericChunkBatchTelemetry.maxRebuildNanoseconds)
                g_GenericChunkBatchTelemetry.maxRebuildNanoseconds = nanoseconds;
        }

        // Which pass is asking. Ogre drives the world _updateRenderQueue
        // override once per camera traversal per active material scheme, so the
        // viewport's scheme is what distinguishes the repeats from each other.
        // Measured on lcbench: exactly three per rendered frame, named
        // "high-pssm", "glow" and "ShaderGeneratorDefaultScheme". They are one
        // world camera path visited once per scheme -- not three PSSM shadow
        // cameras, which was the standing assumption before this instrument.
        //
        // Declared as a pointer return rather than a reference: a reference
        // binding makes MSVC treat the frame as requiring object unwinding,
        // which __try forbids. The ABI is identical.
        using FnOgreGetCurrentViewport = void*(__thiscall*)(void*);
        using FnOgreGetViewportMaterialScheme = const std::string*(__thiscall*)(void*);

        // SEH-only leaf: no statics, no objects, so the frame needs no
        // unwinding. The returned pointer is into Ogre's own string and is only
        // ever read by the immediate caller.
        static const char* TryReadViewportSchemeName(
            void* sceneManager,
            FnOgreGetCurrentViewport getCurrentViewport,
            FnOgreGetViewportMaterialScheme getMaterialScheme)
        {
            __try
            {
                void* const viewport = getCurrentViewport(sceneManager);
                if (!viewport)
                    return "<no-viewport>";
                const std::string* const scheme = getMaterialScheme(viewport);
                if (!scheme || scheme->empty())
                    return "<empty>";
                return scheme->c_str();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return "<faulted>";
            }
        }

        static const char* GetCurrentOgreMaterialSchemeName(void* sceneManager)
        {
            static FnOgreGetCurrentViewport getCurrentViewport =
                ResolveOgreProc<FnOgreGetCurrentViewport>(
                    "?getCurrentViewport@SceneManager@Ogre@@QBEPAVViewport@2@XZ");
            static FnOgreGetViewportMaterialScheme getMaterialScheme =
                ResolveOgreProc<FnOgreGetViewportMaterialScheme>(
                    "?getMaterialScheme@Viewport@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            if (!sceneManager || !getCurrentViewport || !getMaterialScheme)
                return "<unavailable>";
            return TryReadViewportSchemeName(
                sceneManager, getCurrentViewport, getMaterialScheme);
        }

        struct OgreColourValueSnapshot
        {
            float r;
            float g;
            float b;
            float a;
        };

        struct Dx11EnhancedLightingSnapshot
        {
            OgreColourValueSnapshot fog;
            OgreColourValueSnapshot ambient;
            float fogDensity;
            float fogStart;
            float fogEnd;
        };

        using FnOgreGetSceneColour = const OgreColourValueSnapshot*(__thiscall*)(void*);
        using FnOgreGetSceneFloat = float(__thiscall*)(void*);

        // SEH-only leaf. Ogre's colour getters return const ColourValue&, which
        // is an EAX pointer in this 32-bit ABI; copy it while the call is live.
        static bool TryReadDx11EnhancedLightingSnapshot(
            void* sceneManager,
            FnOgreGetSceneColour getFogColour,
            FnOgreGetSceneColour getAmbientLight,
            FnOgreGetSceneFloat getFogDensity,
            FnOgreGetSceneFloat getFogStart,
            FnOgreGetSceneFloat getFogEnd,
            Dx11EnhancedLightingSnapshot* outSnapshot)
        {
            __try
            {
                const OgreColourValueSnapshot* const fog = getFogColour(sceneManager);
                const OgreColourValueSnapshot* const ambient = getAmbientLight(sceneManager);
                if (!fog || !ambient || !outSnapshot)
                    return false;
                outSnapshot->fog = *fog;
                outSnapshot->ambient = *ambient;
                outSnapshot->fogDensity = getFogDensity(sceneManager);
                outSnapshot->fogStart = getFogStart(sceneManager);
                outSnapshot->fogEnd = getFogEnd(sceneManager);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static float SrgbToLinearDiagnostic(float value)
        {
            value = std::clamp(value, 0.0f, 1.0f);
            return value <= 0.04045f
                ? value / 12.92f
                : std::pow((value + 0.055f) / 1.055f, 2.4f);
        }

        static float LinearToSrgbDiagnostic(float value)
        {
            value = std::clamp(value, 0.0f, 1.0f);
            return value <= 0.0031308f
                ? value * 12.92f
                : 1.055f * std::pow(value, 1.0f / 2.4f) - 0.055f;
        }

        static bool Dx11EnhancedLightingSnapshotChanged(
            const Dx11EnhancedLightingSnapshot& lhs,
            const Dx11EnhancedLightingSnapshot& rhs)
        {
            constexpr float epsilon = 0.0001f;
            const auto changed = [epsilon](float a, float b)
            {
                return !std::isfinite(a) || !std::isfinite(b) || std::fabs(a - b) > epsilon;
            };
            return changed(lhs.fog.r, rhs.fog.r) ||
                   changed(lhs.fog.g, rhs.fog.g) ||
                   changed(lhs.fog.b, rhs.fog.b) ||
                   changed(lhs.ambient.r, rhs.ambient.r) ||
                   changed(lhs.ambient.g, rhs.ambient.g) ||
                   changed(lhs.ambient.b, rhs.ambient.b) ||
                   changed(lhs.fogDensity, rhs.fogDensity) ||
                   changed(lhs.fogStart, rhs.fogStart) ||
                   changed(lhs.fogEnd, rhs.fogEnd);
        }

        static void MaybeLogDx11EnhancedLightingState()
        {
            static int enabled = -1;
            static DWORD lastPollTick = 0;
            static bool haveLast = false;
            static Dx11EnhancedLightingSnapshot lastSnapshot = {};
            static std::string lastScheme;

            if (enabled < 0)
            {
                bool iniEnabled = false;
                const bool haveIniValue = TryGetUserConfigBool(
                    "Diagnostics", "TraceDX11EnhancedLighting", iniEnabled);
                enabled = (EnvFlagEnabled("OPENSHIM_TRACE_DX11_ENHANCED_LIGHTING") ||
                           (haveIniValue && iniEnabled)) ? 1 : 0;
                if (enabled != 0)
                    LogShimA(LogLevel::Info, "dx11fog", "[DX11FOG] diagnostic enabled\n");
            }
            if (enabled == 0)
                return;

            const DWORD now = GetTickCount();
            if (lastPollTick != 0 && (now - lastPollTick) < 250)
                return;
            lastPollTick = now;

            static FnOgreGetSceneColour getFogColour =
                ResolveOgreProc<FnOgreGetSceneColour>(
                    "?getFogColour@SceneManager@Ogre@@UBEABVColourValue@2@XZ");
            static FnOgreGetSceneColour getAmbientLight =
                ResolveOgreProc<FnOgreGetSceneColour>(
                    "?getAmbientLight@SceneManager@Ogre@@QBEABVColourValue@2@XZ");
            static FnOgreGetSceneFloat getFogDensity =
                ResolveOgreProc<FnOgreGetSceneFloat>(
                    "?getFogDensity@SceneManager@Ogre@@UBEMXZ");
            static FnOgreGetSceneFloat getFogStart =
                ResolveOgreProc<FnOgreGetSceneFloat>(
                    "?getFogStart@SceneManager@Ogre@@UBEMXZ");
            static FnOgreGetSceneFloat getFogEnd =
                ResolveOgreProc<FnOgreGetSceneFloat>(
                    "?getFogEnd@SceneManager@Ogre@@UBEMXZ");
            if (!getFogColour || !getAmbientLight || !getFogDensity ||
                !getFogStart || !getFogEnd)
                return;

            void* const sceneManager = GetOgreSceneManagerRuntime();
            if (!sceneManager)
                return;

            const char* const schemeName = GetCurrentOgreMaterialSchemeName(sceneManager);
            const std::string scheme = schemeName ? schemeName : "<null>";
            const bool enhancedScheme = scheme.size() >= 3 &&
                _strnicmp(scheme.c_str(), "en-", 3) == 0;

            Dx11EnhancedLightingSnapshot snapshot = {};
            if (!TryReadDx11EnhancedLightingSnapshot(
                    sceneManager, getFogColour, getAmbientLight, getFogDensity,
                    getFogStart, getFogEnd, &snapshot))
                return;

            const bool schemeChanged = scheme != lastScheme;
            if (haveLast && !schemeChanged &&
                !Dx11EnhancedLightingSnapshotChanged(snapshot, lastSnapshot))
                return;

            lastScheme = scheme;
            lastSnapshot = snapshot;
            haveLast = true;

            if (!enhancedScheme)
            {
                LogShimA(LogLevel::Info, "dx11fog",
                    "[DX11FOG] state scheme=%s enhanced=0\n", scheme.c_str());
                return;
            }

            const float fogLinearR = SrgbToLinearDiagnostic(snapshot.fog.r);
            const float fogLinearG = SrgbToLinearDiagnostic(snapshot.fog.g);
            const float fogLinearB = SrgbToLinearDiagnostic(snapshot.fog.b);
            constexpr float ambientTintStrength = 0.16f;
            constexpr float ambientInputStrength = 0.35f;
            const float ambientTargetR = std::clamp(
                fogLinearR + snapshot.ambient.r * ambientInputStrength, 0.0f, 1.0f);
            const float ambientTargetG = std::clamp(
                fogLinearG + snapshot.ambient.g * ambientInputStrength, 0.0f, 1.0f);
            const float ambientTargetB = std::clamp(
                fogLinearB + snapshot.ambient.b * ambientInputStrength, 0.0f, 1.0f);
            const float ambientAddR = (ambientTargetR - fogLinearR) * ambientTintStrength;
            const float ambientAddG = (ambientTargetG - fogLinearG) * ambientTintStrength;
            const float ambientAddB = (ambientTargetB - fogLinearB) * ambientTintStrength;
            const float baseLinearR = fogLinearR + ambientAddR;
            const float baseLinearG = fogLinearG + ambientAddG;
            const float baseLinearB = fogLinearB + ambientAddB;
            const float fogRange = snapshot.fogEnd - snapshot.fogStart;
            const float inverseFogRange = fogRange > 0.001f ? 1.0f / fogRange : 0.0f;
            const float atmosphereSupport = std::clamp(inverseFogRange * 160.0f, 0.0f, 1.0f);
            const float terrainIblScale = 0.15f + 0.85f * atmosphereSupport;

            LogShimA(LogLevel::Info, "dx11fog",
                "[DX11FOG] state scheme=%s enhanced=1 authored_srgb=(%.6f,%.6f,%.6f) "
                "shader_linear=(%.6f,%.6f,%.6f) ambient=(%.6f,%.6f,%.6f) "
                "ambient_add=(%.6f,%.6f,%.6f) base_final_srgb=(%.6f,%.6f,%.6f) "
                "untreated_final_srgb=(%.6f,%.6f,%.6f) fogDensity=%.6f fogStart=%.3f "
                "fogEnd=%.3f invRange=%.8f terrainDiffuseIblScale=%.6f\n",
                scheme.c_str(),
                snapshot.fog.r, snapshot.fog.g, snapshot.fog.b,
                fogLinearR, fogLinearG, fogLinearB,
                snapshot.ambient.r, snapshot.ambient.g, snapshot.ambient.b,
                ambientAddR, ambientAddG, ambientAddB,
                LinearToSrgbDiagnostic(baseLinearR),
                LinearToSrgbDiagnostic(baseLinearG),
                LinearToSrgbDiagnostic(baseLinearB),
                LinearToSrgbDiagnostic(snapshot.fog.r),
                LinearToSrgbDiagnostic(snapshot.fog.g),
                LinearToSrgbDiagnostic(snapshot.fog.b),
                snapshot.fogDensity, snapshot.fogStart, snapshot.fogEnd,
                inverseFogRange, terrainIblScale);
        }

        // Interval telemetry for the state-version reuse. Everything here is
        // a delta over the reporting window, so the numbers can be divided by
        // the frame count of the same window to get per-frame rates without
        // needing a frame hook of our own.
        static void LogGenericChunkBatchTelemetry(DWORD windowMs)
        {
            using namespace ChunkBatchInvalidation;
            const Telemetry& now = g_GenericChunkBatchTelemetry;
            const Telemetry& then = g_GenericChunkBatchTelemetryAtLastLog;
            const unsigned long long requests = now.requests - then.requests;
            const unsigned long long rebuilds = now.rebuilds - then.rebuilds;
            const unsigned long long reused = now.reused - then.reused;
            const unsigned long long emptySkips = now.emptySkips - then.emptySkips;
            const unsigned long long vertices = now.verticesRebuilt - then.verticesRebuilt;
            const unsigned long long indices = now.indicesRebuilt - then.indicesRebuilt;
            const unsigned long long nanos =
                now.rebuildNanoseconds - then.rebuildNanoseconds;

            LogChunkDiagnostic(
                "chunkbatch",
                L"[CHUNKBATCH] reuse windowMs=%lu requests=%llu rebuilds=%llu reused=%llu "
                L"emptySkips=%llu dedupPct=%.1f verts=%llu indices=%llu rebuildMs=%.3f maxRebuildMs=%.3f"
                L" mode=%hs\n",
                static_cast<unsigned long>(windowMs),
                requests, rebuilds, reused, emptySkips,
                requests ? (100.0 * static_cast<double>(reused) /
                            static_cast<double>(requests)) : 0.0,
                vertices, indices,
                static_cast<double>(nanos) / 1000000.0,
                static_cast<double>(now.maxRebuildNanoseconds) / 1000000.0,
                g_GenericChunkBatchReuseObserveOnly
                    ? "observe"
                    : (g_GenericChunkBatchReuseEnabled ? "reuse" : "always-rebuild"));

            for (int index = 0; index < 8; ++index)
            {
                const unsigned long long count =
                    now.reasonCounts[index] - then.reasonCounts[index];
                if (count == 0)
                    continue;
                LogChunkDiagnostic(
                    "chunkbatch",
                    L"[CHUNKBATCH] reuse   reason=%hs count=%llu\n",
                    ReasonName(static_cast<Reason>(index)),
                    count);
            }
            for (size_t index = 0; index < now.schemeCount; ++index)
            {
                const SchemeCounters& scheme = now.schemes[index];
                const SchemeCounters& previous =
                    index < then.schemeCount ? then.schemes[index] : SchemeCounters{};
                const unsigned long long schemeRequests =
                    scheme.requests - previous.requests;
                if (schemeRequests == 0)
                    continue;
                LogChunkDiagnostic(
                    "chunkbatch",
                    L"[CHUNKBATCH] reuse   scheme=%hs requests=%llu rebuilds=%llu\n",
                    scheme.name,
                    schemeRequests,
                    static_cast<unsigned long long>(scheme.rebuilds - previous.rebuilds));
            }
            g_GenericChunkBatchTelemetryAtLastLog = now;
        }

        // Takes the batch out of the scene without destroying it, so the next
        // explosion reuses the same ManualObject and section rather than
        // paying for a fresh one. The built version is deliberately left
        // alone: the geometry in the object is still valid, it is simply not
        // wanted right now, and clearing it would force a needless rebuild
        // the moment the same debris set comes back.
        static void HideGenericChunkBatchIfBuilt()
        {
            static FnOgreSetVisible setVisible =
                ResolveOgreProc<FnOgreSetVisible>(
                    "?setVisible@MovableObject@Ogre@@UAEX_N@Z");
            if (!g_GenericChunkBatchManualObject || !setVisible)
                return;
            if (!g_GenericChunkBatchVisible)
                return;
            try
            {
                setVisible(g_GenericChunkBatchManualObject, false);
                g_GenericChunkBatchVisible = false;
            }
            catch (...)
            {
                // Deliberately does NOT clear g_GenericChunkBatchRuntimeAvailable,
                // unlike the emit and submit failures below. Those happen while
                // slots are classified batch-ready and their per-Entity proxies
                // are already hidden, so the batch has promised to draw geometry
                // it can no longer produce and standing down permanently is the
                // safe answer. This path only runs when there is nothing to draw
                // at all, so dropping the object and letting the next explosion
                // recreate it is a recovery, not a risk.
                LogChunkDiagnostic(
                    "chunkbatch",
                    L"[CHUNKBATCH] hide threw; dropping cached batch\n");
                g_GenericChunkBatchManualObject = nullptr;
                // The recorded visibility described the object just dropped.
                g_GenericChunkBatchVisible = false;
                g_GenericChunkBatchSceneNode = nullptr;
                g_GenericChunkBatchSectionCreated = false;
                g_GenericChunkBatchBuiltVersion =
                    ChunkBatchInvalidation::kUnbuiltVersion;
            }
        }

        // The mission run-state seam fires while the outgoing Ogre objects are
        // still valid, before Redux unloads the Modable resource group. Hide
        // every shim-owned renderable in that window, then retire its slot.
        // Merely forgetting the pointers is unsafe: the Entity remains attached
        // to the scene graph and Ogre can traverse it after its Mesh/SubMesh has
        // been unloaded. Dump battlezone98redux.exe.16476.dmp captured exactly
        // that path for Ogre/MO656 (avfigh/ara11nrr.mesh): SubMesh::indexData
        // was null when the loading-screen frame called _getRenderOperation.
        void DeactivateAllChunkProxySceneResources(const wchar_t* reason)
        {
            // Dump battlezone98redux.exe.38660.dmp ended in OgreMain!operator delete
            // with a corrupted stack after mission quit (write to 001b835c, esp in
            // free memory). The seam runs on the main thread with Ogre still valid
            // but about to unload Modable. An Ogre call that faults must not unwind
            // through every slot and leave attached entities. Faults are caught
            // per-slot and demoted to a pointer forget, which is the same recovery
            // the periodic "expired" tick uses when touching the entity faults.
            size_t deactivated = 0;
            size_t faulted = 0;
            for (ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (slot.active || slot.billboardAssigned || slot.meshAssigned)
                    ++deactivated;
                __try
                {
                    ReleaseChunkProxySlot(slot);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    ForgetChunkProxySlotOgreRefs(slot);
                    ++faulted;
                }
            }
            __try
            {
                HideGenericChunkBatchIfBuilt();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_GenericChunkBatchManualObject = nullptr;
                g_GenericChunkBatchSceneNode = nullptr;
                g_GenericChunkBatchVisible = false;
                g_GenericChunkBatchSectionCreated = false;
                ++faulted;
            }

            if (deactivated > 0 || faulted > 0)
            {
                LogChunkDiagnostic(
                    "chunkproxy",
                    L"[CHUNKPROXY] mission transition (%ls): deactivated %zu slot(s) faulted=%zu before resource unload\n",
                    reason ? reason : L"<none>",
                    deactivated,
                    faulted);
            }
        }

        static bool RebuildAndSubmitGenericChunkBatch(void* renderQueue)
        {
            size_t chunkCount = 0;
            size_t vertexCount = 0;
            // Tight bounds of the live chunk set, for the diagnostic comparison
            // against Ogre's own accumulated ManualObject AABB below. Chunk
            // half-extent is under a metre, so slot origins are a fair proxy.
            float tightMin[3] = { FLT_MAX, FLT_MAX, FLT_MAX };
            float tightMax[3] = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
            // The state version is accumulated inside this existing scan, so
            // the reuse check costs no extra pass over the slots -- only a few
            // integer mixes per eligible chunk.
            ChunkBatchInvalidation::SourceVersion sourceVersion;
            uint32_t ordinal = 0;
            for (const ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (!slot.active || !slot.genericBatchTransformReady)
                    continue;
                ++chunkCount;
                vertexCount += slot.genericBatchKind == 1
                    ? std::size(kChunk1Vertices) : std::size(kChunk2Vertices);
                const ChunkProxyTransform& batchTransform = slot.genericBatchTransform;
                ChunkBatchInvalidation::SlotState slotState = {};
                slotState.kind = slot.genericBatchKind;
                slotState.x = batchTransform.x;
                slotState.y = batchTransform.y;
                slotState.z = batchTransform.z;
                slotState.qw = batchTransform.orientation.w;
                slotState.qx = batchTransform.orientation.x;
                slotState.qy = batchTransform.orientation.y;
                slotState.qz = batchTransform.orientation.z;
                slotState.sx = batchTransform.scale.x;
                slotState.sy = batchTransform.scale.y;
                slotState.sz = batchTransform.scale.z;
                ChunkBatchInvalidation::MixSlot(sourceVersion, ordinal++, slotState);
                const float slotOrigin[3] = {
                    batchTransform.x,
                    batchTransform.y,
                    batchTransform.z };
                for (int axis = 0; axis < 3; ++axis)
                {
                    if (slotOrigin[axis] < tightMin[axis])
                        tightMin[axis] = slotOrigin[axis];
                    if (slotOrigin[axis] > tightMax[axis])
                        tightMax[axis] = slotOrigin[axis];
                }
            }
            if (chunkCount == 0)
            {
                // Nothing eligible. Not submitting is necessary but not
                // sufficient: the ManualObject still holds the last geometry
                // and is attached to a node under the root, so it would remain
                // eligible for Ogre's own traversal. Hide it as well, so the
                // frame the last chunk expires is the frame it stops drawing --
                // with or without reuse, and whether or not Ogre traverses it
                // independently of this hook.
                HideGenericChunkBatchIfBuilt();
                ++g_GenericChunkBatchTelemetry.emptySkips;
                return false;
            }
            ChunkBatchInvalidation::MixCount(
                sourceVersion, static_cast<uint32_t>(chunkCount));

            // TEST/DIAGNOSTIC ONLY. Placed deliberately *after* the eligible
            // slots have been counted, so the injected failure lands in the
            // same window a real Ogre construction failure would: the mesh
            // proxies are already hidden or unbuilt and the batch has promised
            // to draw them. Production never sets this flag.
            if (g_ForceGenericChunkBatchFailure)
            {
                static volatile long s_ForcedFailureLogBudget = 4;
                if (InterlockedDecrement(&s_ForcedFailureLogBudget) >= 0)
                {
                    LogChunkDiagnostic(
                        "chunkbatch",
                        L"[CHUNKBATCH] forced failure injected (diagnostic): eligible=%zu\n",
                        chunkCount);
                }
                return false;
            }

            static FnOgreCreateManualObject createManualObject =
                ResolveOgreProc<FnOgreCreateManualObject>(
                    "?createManualObject@SceneManager@Ogre@@UAEPAVManualObject@2@XZ");
            static FnOgreGetRootSceneNode getRootSceneNode =
                ResolveOgreProc<FnOgreGetRootSceneNode>(
                    "?getRootSceneNode@SceneManager@Ogre@@UAEPAVSceneNode@2@XZ");
            static FnOgreCreateChildSceneNode createChildSceneNode =
                ResolveOgreProc<FnOgreCreateChildSceneNode>(
                    "?createChildSceneNode@SceneNode@Ogre@@UAEPAV12@ABVVector3@2@ABVQuaternion@2@@Z");
            static FnOgreAttachObject attachObject =
                ResolveOgreProc<FnOgreAttachObject>(
                    "?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
            static FnOgreManualObjectSetDynamic setDynamic =
                ResolveOgreProc<FnOgreManualObjectSetDynamic>(
                    "?setDynamic@ManualObject@Ogre@@UAEX_N@Z");
            static FnOgreManualObjectEstimateCount estimateVertices =
                ResolveOgreProc<FnOgreManualObjectEstimateCount>(
                    "?estimateVertexCount@ManualObject@Ogre@@UAEXI@Z");
            static FnOgreManualObjectEstimateCount estimateIndices =
                ResolveOgreProc<FnOgreManualObjectEstimateCount>(
                    "?estimateIndexCount@ManualObject@Ogre@@UAEXI@Z");
            static FnOgreManualObjectBegin begin =
                ResolveOgreProc<FnOgreManualObjectBegin>(
                    "?begin@ManualObject@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4OperationType@RenderOperation@2@0@Z");
            static FnOgreManualObjectBeginUpdate beginUpdate =
                ResolveOgreProc<FnOgreManualObjectBeginUpdate>(
                    "?beginUpdate@ManualObject@Ogre@@UAEXI@Z");
            static FnOgreManualObjectVertex3 position =
                ResolveOgreProc<FnOgreManualObjectVertex3>(
                    "?position@ManualObject@Ogre@@UAEXMMM@Z");
            static FnOgreManualObjectVertex3 normal =
                ResolveOgreProc<FnOgreManualObjectVertex3>(
                    "?normal@ManualObject@Ogre@@UAEXMMM@Z");
            static FnOgreManualObjectVertex3 tangent =
                ResolveOgreProc<FnOgreManualObjectVertex3>(
                    "?tangent@ManualObject@Ogre@@UAEXMMM@Z");
            static FnOgreManualObjectTexture2 textureCoord =
                ResolveOgreProc<FnOgreManualObjectTexture2>(
                    "?textureCoord@ManualObject@Ogre@@UAEXMM@Z");
            static FnOgreManualObjectIndex addIndex =
                ResolveOgreProc<FnOgreManualObjectIndex>(
                    "?index@ManualObject@Ogre@@UAEXI@Z");
            static FnOgreManualObjectEnd end =
                ResolveOgreProc<FnOgreManualObjectEnd>(
                    "?end@ManualObject@Ogre@@UAEPAVManualObjectSection@12@XZ");
            static FnOgreManualObjectUpdateRenderQueue updateRenderQueue =
                ResolveOgreProc<FnOgreManualObjectUpdateRenderQueue>(
                    "?_updateRenderQueue@ManualObject@Ogre@@UAEXPAVRenderQueue@2@@Z");
            static FnOgreMovableSetCastShadows setCastShadows =
                ResolveOgreProc<FnOgreMovableSetCastShadows>(
                    "?setCastShadows@MovableObject@Ogre@@QAEX_N@Z");
            static FnOgreSetVisible setVisible =
                ResolveOgreProc<FnOgreSetVisible>(
                    "?setVisible@MovableObject@Ogre@@UAEX_N@Z");

            if (!createManualObject || !getRootSceneNode ||
                !createChildSceneNode || !attachObject || !setDynamic ||
                !estimateVertices || !estimateIndices || !begin ||
                !beginUpdate || !position || !normal || !tangent ||
                !textureCoord || !addIndex || !end || !updateRenderQueue ||
                !setCastShadows || !setVisible)
            {
                LogChunkDiagnostic(
                    "chunkbatch",
                    L"[CHUNKBATCH] required Ogre exports unavailable; falling back to per-entity chunks\n");
                g_GenericChunkBatchRuntimeAvailable = false;
                return false;
            }

            void* const sceneManager = GetOgreSceneManagerRuntime();
            if (!sceneManager)
                return false;
            const bool sceneManagerChanged =
                g_GenericChunkBatchSceneManager != sceneManager;
            if (sceneManagerChanged)
            {
                // A new SceneManager means the previous ManualObject belongs to
                // a destroyed scene. Drop the cached version with it, or reuse
                // would submit a dangling object across a mission boundary.
                g_GenericChunkBatchManualObject = nullptr;
                // The recorded visibility described the object just dropped.
                g_GenericChunkBatchVisible = false;
                g_GenericChunkBatchSceneNode = nullptr;
                g_GenericChunkBatchSceneManager = sceneManager;
                g_GenericChunkBatchSectionCreated = false;
                g_GenericChunkBatchBuiltVersion =
                    ChunkBatchInvalidation::kUnbuiltVersion;
            }

            // ---- reuse decision -------------------------------------------
            // Everything below this point that can invalidate the built
            // geometry has already been resolved: the ManualObject exists or
            // does not, the SceneManager has been compared, and the source
            // version is computed. Anything uncertain resolves toward
            // rebuilding inside DecideRebuild().
            ChunkBatchInvalidation::BuiltState builtState = {};
            builtState.version = g_GenericChunkBatchBuiltVersion;
            builtState.objectAlive = g_GenericChunkBatchManualObject != nullptr;
            builtState.sectionCreated = g_GenericChunkBatchSectionCreated;
            // Redundant with objectAlive today, because the SceneManager check
            // above already nulls the object. Fed anyway so the policy states
            // the requirement itself rather than relying on a side effect
            // several lines up.
            builtState.objectIdentityStable = !sceneManagerChanged;
            builtState.materialStable =
                g_GenericChunkBatchBuiltMaterial == g_GenericChunkBatchMaterialName;

            const ChunkBatchInvalidation::Reason reason =
                ChunkBatchInvalidation::DecideRebuild(
                    builtState,
                    sourceVersion.Value(),
                    !g_GenericChunkBatchReuseEnabled);
            const bool wantRebuild = ChunkBatchInvalidation::ShouldRebuild(reason);

            ++g_GenericChunkBatchTelemetry.requests;
            g_GenericChunkBatchTelemetry.NoteReason(reason);
            // Pass attribution costs two virtual Ogre calls plus a short string
            // walk on every traversal, which is real work on a path that runs
            // three times a frame. The counters above are a handful of
            // increments and stay unconditional; this part is opt-in.
            if (g_GenericChunkBatchRateDiagnostics)
            {
                g_GenericChunkBatchTelemetry.NoteScheme(
                    GetCurrentOgreMaterialSchemeName(sceneManager), wantRebuild);
            }

            if (!wantRebuild && !g_GenericChunkBatchReuseObserveOnly)
            {
                // The geometry already in the ManualObject is byte-identical to
                // what a rebuild would produce, so this traversal only needs the
                // submission. This is the whole optimization: one emit per
                // source-state change instead of one per camera/scheme pass.
                ++g_GenericChunkBatchTelemetry.reused;
                try
                {
                    if (!g_GenericChunkBatchVisible)
                    {
                        setVisible(g_GenericChunkBatchManualObject, true);
                        g_GenericChunkBatchVisible = true;
                    }
                    updateRenderQueue(g_GenericChunkBatchManualObject, renderQueue);
                }
                catch (...)
                {
                    LogChunkDiagnostic(
                        "chunkbatch",
                        L"[CHUNKBATCH] reuse submit threw; dropping cached batch\n");
                    g_GenericChunkBatchRuntimeAvailable = false;
                    g_GenericChunkBatchManualObject = nullptr;
                    // The recorded visibility described the object just dropped.
                    g_GenericChunkBatchVisible = false;
                    g_GenericChunkBatchSceneNode = nullptr;
                    g_GenericChunkBatchSectionCreated = false;
                    g_GenericChunkBatchBuiltVersion =
                        ChunkBatchInvalidation::kUnbuiltVersion;
                    return false;
                }
                return true;
            }

            // Observer mode still rebuilds, but the counters above already
            // recorded what reuse would have skipped.
            if (!wantRebuild)
                ++g_GenericChunkBatchTelemetry.reused;
            ++g_GenericChunkBatchTelemetry.rebuilds;
            g_GenericChunkBatchTelemetry.verticesRebuilt += vertexCount;
            g_GenericChunkBatchTelemetry.indicesRebuilt += vertexCount;
            const int64_t rebuildStartTicks = ReadChunkBatchQpc();

            bool updateStarted = false;
            try
            {
                if (!g_GenericChunkBatchManualObject)
                {
                    void* const rootNode = getRootSceneNode(sceneManager);
                    const OgreVector3 origin = { 0.0f, 0.0f, 0.0f };
                    const OgreQuaternion identity = { 1.0f, 0.0f, 0.0f, 0.0f };
                    g_GenericChunkBatchSceneNode = rootNode
                        ? createChildSceneNode(rootNode, origin, identity)
                        : nullptr;
                    g_GenericChunkBatchManualObject = createManualObject(sceneManager);
                    if (!g_GenericChunkBatchSceneNode ||
                        !g_GenericChunkBatchManualObject)
                    {
                        g_GenericChunkBatchRuntimeAvailable = false;
                        return false;
                    }
                    attachObject(
                        g_GenericChunkBatchSceneNode,
                        g_GenericChunkBatchManualObject);
                    setDynamic(g_GenericChunkBatchManualObject, true);
                    estimateVertices(
                        g_GenericChunkBatchManualObject,
                        static_cast<uint32_t>(
                            g_ChunkProxyCapacity * std::size(kChunk2Vertices)));
                    estimateIndices(
                        g_GenericChunkBatchManualObject,
                        static_cast<uint32_t>(
                            g_ChunkProxyCapacity * std::size(kChunk2Vertices)));
                    setCastShadows(g_GenericChunkBatchManualObject, false);
                    LogChunkDiagnostic(
                        "chunkbatch",
                        L"[CHUNKBATCH] initialized dynamic generic chunk batch capacity=%u material=scarpmat2\n",
                        g_ChunkProxyCapacity);
                }

                if (g_GenericChunkBatchSectionCreated)
                    beginUpdate(g_GenericChunkBatchManualObject, 0);
                else
                    begin(
                        g_GenericChunkBatchManualObject,
                        g_GenericChunkBatchMaterialName,
                        4,
                        g_GenericChunkBatchMaterialGroup);
                updateStarted = true;

                uint32_t nextIndex = 0;
                for (const ChunkProxySlot& slot : g_ChunkProxySlots)
                {
                    if (!slot.active || !slot.genericBatchTransformReady)
                        continue;
                    if (slot.genericBatchKind == 1)
                    {
                        AppendGenericChunkBatchGeometry(
                            g_GenericChunkBatchManualObject,
                            kChunk1Vertices,
                            std::size(kChunk1Vertices),
                            slot.genericBatchTransform,
                            nextIndex,
                            position,
                            normal,
                            tangent,
                            textureCoord,
                            addIndex);
                    }
                    else
                    {
                        AppendGenericChunkBatchGeometry(
                            g_GenericChunkBatchManualObject,
                            kChunk2Vertices,
                            std::size(kChunk2Vertices),
                            slot.genericBatchTransform,
                            nextIndex,
                            position,
                            normal,
                            tangent,
                            textureCoord,
                            addIndex);
                    }
                }
                end(g_GenericChunkBatchManualObject);
                updateStarted = false;
                g_GenericChunkBatchSectionCreated = true;
                // Only stamp the version once the emit has actually completed.
                // A throw between begin and end leaves the object half-built,
                // and the catch below clears the stamp so the next call cannot
                // mistake that wreckage for valid cached geometry.
                g_GenericChunkBatchBuiltVersion = sourceVersion.Value();
                g_GenericChunkBatchBuiltMaterial = g_GenericChunkBatchMaterialName;
                NoteChunkBatchRebuildCost(rebuildStartTicks);
                if (!g_GenericChunkBatchVisible)
                {
                    setVisible(g_GenericChunkBatchManualObject, true);
                    g_GenericChunkBatchVisible = true;
                }
                updateRenderQueue(g_GenericChunkBatchManualObject, renderQueue);
            }
            catch (...)
            {
                LogChunkDiagnostic(
                    "chunkbatch",
                    L"[CHUNKBATCH] Ogre batch update threw started=%u; falling back to per-entity chunks\n",
                    updateStarted ? 1u : 0u);
                g_GenericChunkBatchRuntimeAvailable = false;
                g_GenericChunkBatchManualObject = nullptr;
                // The recorded visibility described the object just dropped.
                g_GenericChunkBatchVisible = false;
                g_GenericChunkBatchSceneNode = nullptr;
                g_GenericChunkBatchSectionCreated = false;
                g_GenericChunkBatchBuiltVersion =
                    ChunkBatchInvalidation::kUnbuiltVersion;
                return false;
            }

            const DWORD now = GetTickCount();
            if (g_GenericChunkBatchLastLogTick == 0 ||
                static_cast<DWORD>(now - g_GenericChunkBatchLastLogTick) >= 1000)
            {
                g_GenericChunkBatchLastLogTick = now;
                LogChunkDiagnostic(
                    "chunkbatch",
                    L"[CHUNKBATCH] active=%zu vertices=%zu sections=1\n",
                    chunkCount,
                    vertexCount);

                // Diagnostic-only, once per second, never on the hot path.
                // Ogre resets ManualObject::mAABB only in clear(); beginUpdate()
                // leaves it alone, so the aggregate bounds are expected to grow
                // monotonically over a mission. Read Ogre's own box back and log
                // it beside the tight box, so the claim is measured not argued.
                static FnOgreManualObjectGetBoundingBox getBoundingBox =
                    ResolveOgreProc<FnOgreManualObjectGetBoundingBox>(
                        "?getBoundingBox@ManualObject@Ogre@@UBEABVAxisAlignedBox@2@XZ");
                static FnOgreManualObjectGetBoundingRadius getBoundingRadius =
                    ResolveOgreProc<FnOgreManualObjectGetBoundingRadius>(
                        "?getBoundingRadius@ManualObject@Ogre@@UBEMXZ");
                if (getBoundingBox && getBoundingRadius &&
                    g_GenericChunkBatchManualObject && chunkCount > 0)
                {
                    try
                    {
                        const float* const box = static_cast<const float*>(
                            getBoundingBox(g_GenericChunkBatchManualObject));
                        if (box)
                        {
                            const uint32_t extentEnum =
                                *reinterpret_cast<const uint32_t*>(box + 6);
                            const float radius = getBoundingRadius(
                                g_GenericChunkBatchManualObject);
                            LogChunkDiagnostic(
                                "chunkbatch",
                                L"[CHUNKBATCH] bounds ogre=(%.1f,%.1f,%.1f)-(%.1f,%.1f,%.1f)"
                                L" ogreSpan=(%.1f,%.1f,%.1f) extentEnum=%u radius=%.1f"
                                L" tight=(%.1f,%.1f,%.1f)-(%.1f,%.1f,%.1f)"
                                L" tightSpan=(%.1f,%.1f,%.1f)\n",
                                box[0], box[1], box[2],
                                box[3], box[4], box[5],
                                box[3] - box[0], box[4] - box[1], box[5] - box[2],
                                extentEnum, radius,
                                tightMin[0], tightMin[1], tightMin[2],
                                tightMax[0], tightMax[1], tightMax[2],
                                tightMax[0] - tightMin[0],
                                tightMax[1] - tightMin[1],
                                tightMax[2] - tightMin[2]);
                        }
                    }
                    catch (...)
                    {
                    }
                }
            }
            return true;
        }

        // Render-time injection: called from the game's own _updateRenderQueue
        // override (0x00679570), the only exe-side path that feeds Ogre's
        // RenderQueue. Adding our sub-entities to the queue passed here puts
        // chunk proxies in exactly the same queue, frame, and coordinate space
        // as the game's world geometry — no camera/viewport guesswork.
        static void SubmitChunkProxiesToRenderQueue(void* renderQueue)
        {
            if (!renderQueue || !g_EnableChunkMeshProxy)
                return;
            if (!IsChunkManualSubmitEnabled())
                return;
            if (g_ChunkProxySlots.empty())
                return;

            const bool genericBatchSubmitted =
                RebuildAndSubmitGenericChunkBatch(renderQueue);
            if (g_GenericChunkBatchRateDiagnostics)
            {
                ++g_GenericChunkBatchSubmitCalls;
                if (genericBatchSubmitted)
                    ++g_GenericChunkBatchRebuilds;
                const DWORD rateNow = GetTickCount();
                if (g_GenericChunkBatchRateLogTick == 0)
                {
                    g_GenericChunkBatchRateLogTick = rateNow;
                }
                else if (static_cast<DWORD>(
                             rateNow - g_GenericChunkBatchRateLogTick) >= 1000)
                {
                    const DWORD windowMs = static_cast<DWORD>(
                        rateNow - g_GenericChunkBatchRateLogTick);
                    LogChunkDiagnostic(
                        "chunkbatch",
                        L"[CHUNKBATCH] rate windowMs=%lu submitCalls=%llu submissions=%llu\n",
                        static_cast<unsigned long>(windowMs),
                        static_cast<unsigned long long>(
                            g_GenericChunkBatchSubmitCalls -
                            g_GenericChunkBatchSubmitCallsAtLastLog),
                        static_cast<unsigned long long>(
                            g_GenericChunkBatchRebuilds -
                            g_GenericChunkBatchRebuildsAtLastLog));
                    LogGenericChunkBatchTelemetry(windowMs);
                    g_GenericChunkBatchRateLogTick = rateNow;
                    g_GenericChunkBatchSubmitCallsAtLastLog =
                        g_GenericChunkBatchSubmitCalls;
                    g_GenericChunkBatchRebuildsAtLastLog =
                        g_GenericChunkBatchRebuilds;
                }
            }
            if (!genericBatchSubmitted)
            {
                // Same frame, before the per-Entity loop below reads the slots.
                RehydrateGenericChunkBatchSlotsToEntities(
                    g_ForceGenericChunkBatchFailure ? L"forced" : L"batch-unavailable");
            }

            static FnOgreRenderQueueAddRenderablePriority addRenderablePriority =
                ResolveOgreProcByOffset<FnOgreRenderQueueAddRenderablePriority>(0x00026850);
            static FnOgreGetRenderQueueGroup getRenderQueueGroup =
                ResolveOgreProcByOffset<FnOgreGetRenderQueueGroup>(0x0001584D);
            static FnOgreGetNumSubEntities getNumSubEntities =
                ResolveOgreProc<FnOgreGetNumSubEntities>("?getNumSubEntities@Entity@Ogre@@QBEIXZ");
            static FnOgreGetSubEntity getSubEntity =
                ResolveOgreProc<FnOgreGetSubEntity>("?getSubEntity@Entity@Ogre@@QBEPAVSubEntity@2@I@Z");

            if (!addRenderablePriority || !getNumSubEntities || !getSubEntity)
            {
                static volatile long s_MissingProcLogBudget = 2;
                if (InterlockedDecrement(&s_MissingProcLogBudget) >= 0)
                {
                    LogChunkDiagnostic(
                        "chunkmesh",
                        L"[CHUNKMESH] world-rq-submit procs-missing add=%u numSub=%u getSub=%u\n",
                        addRenderablePriority ? 1u : 0u,
                        getNumSubEntities ? 1u : 0u,
                        getSubEntity ? 1u : 0u);
                }
                return;
            }

            for (ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (genericBatchSubmitted &&
                    slot.genericBatchTransformReady)
                {
                    continue;
                }
                if (!slot.active || !slot.entity)
                    continue;

                bool groupFaulted = false;
                const uint8_t groupId =
                    TryGetChunkProxyRenderQueueGroupSafe(slot.entity, getRenderQueueGroup, &groupFaulted);
                if (groupFaulted)
                {
                    ForgetChunkProxySlotOgreRefs(slot);
                    continue;
                }
                bool countFaulted = false;
                const uint32_t subEntityCount = TryGetChunkProxySubEntityCountSafe(
                    slot.entity, getNumSubEntities, &countFaulted);
                if (countFaulted)
                {
                    ForgetChunkProxySlotOgreRefs(slot);
                    continue;
                }
                uint32_t added = 0;

                bool slotWentStale = false;
                for (uint32_t index = 0; index < subEntityCount; ++index)
                {
                    void* const subEntity =
                        TryGetChunkProxySubEntitySafe(slot.entity, index, getSubEntity);
                    // A live Entity never returns null below its own count.
                    // Bail out instead of faulting once per remaining index.
                    if (!subEntity)
                    {
                        slotWentStale = true;
                        break;
                    }

                    if (!TryAddChunkProxyRenderableSafe(
                            renderQueue,
                            subEntity,
                            groupId,
                            100u,
                            addRenderablePriority))
                    {
                        static volatile long s_StaleSubEntityLogBudget = 8;
                        if (InterlockedDecrement(&s_StaleSubEntityLogBudget) >= 0)
                        {
                            LogChunkDiagnostic(
                                "chunkmesh",
                                L"[CHUNKMESH] world-rq-submit rejected stale sub-entity entity=0x%08X subEntity=0x%08X\n",
                                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(subEntity)));
                        }
                        ForgetChunkProxySlotOgreRefs(slot);
                        break;
                    }
                    ++added;
                    if (slot.renderQueueAddCount < USHRT_MAX)
                        ++slot.renderQueueAddCount;
                }
                if (slotWentStale)
                {
                    static volatile long s_StaleEntityLogBudget = 8;
                    if (InterlockedDecrement(&s_StaleEntityLogBudget) >= 0)
                    {
                        LogChunkDiagnostic(
                            "chunkmesh",
                            L"[CHUNKMESH] world-rq-submit stale entity=0x%08X dropped after %u/%u sub-entities\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                            added,
                            subEntityCount);
                    }
                    ForgetChunkProxySlotOgreRefs(slot);
                    continue;
                }

                static volatile long s_FirstWorldRqSubmitLogBudget = 12;
                if (added != 0 && slot.renderQueueAddCount <= 8 &&
                    InterlockedDecrement(&s_FirstWorldRqSubmitLogBudget) >= 0)
                {
                    LogChunkDiagnostic(
                        "chunkmesh",
                        L"[CHUNKMESH] world-rq-submit entity=0x%08X mesh=%hs queue=0x%08X group=%u added=%u totalAdds=%u\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                        GetChunkPayloadMeshName(slot),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(renderQueue)),
                        static_cast<unsigned>(groupId),
                        added,
                        static_cast<unsigned>(slot.renderQueueAddCount));
                }
            }
        }

        // Pieces the simulation still fragments but the Redux model no longer
        // renders separately. Each was verified against the shipped .mesh in
        // Blender, and there is no geometry to draw for any of them -- a proxy
        // here can only ever be a generic rock or a billboard standing in for
        // something that is already gone. Suppressing is closer to the legacy
        // look than inventing debris.
        //
        // Keyed on the ODF name, which is the craft identity the engine states
        // outright, so a faction twin sharing a piece name is unaffected.
        struct SuppressedChunkPiece
        {
            const char* odfName;
            const char* geomName;
            const char* reason;
        };

        static constexpr SuppressedChunkPiece kSuppressedChunkPieces[] = {
            // abhang models two door panels of 88 verts where bbhang models four
            // of 44 -- same 176 total, so doors C and D are already inside the
            // geometry that flies off as abh11dra/abh11drb.
            { "abhang", "abh11drc", "merged into abh11dra/abh11drb" },
            { "abhang", "abh11drd", "merged into abh11dra/abh11drb" },
            // Bone exists but carries 4 verts and zero complete faces.
            { "abhang", "abh11bli", "degenerate: 4 verts, 0 faces" },
            // No such bone in abspow.mesh at all (21 geometry bones, none is bul).
            { "abspow", "asp11bul", "absent from abspow.mesh" },
            { "bbspow", "asp11bul", "absent from abspow.mesh" },
        };

        static const SuppressedChunkPiece* FindSuppressedChunkPiece(const char* geomName)
        {
            if (!geomName || !*geomName || !g_ActiveFragmentSourceOdfName[0])
                return nullptr;

            for (const SuppressedChunkPiece& entry : kSuppressedChunkPieces)
            {
                if (_stricmp(entry.odfName, g_ActiveFragmentSourceOdfName) == 0 &&
                    _stricmp(entry.geomName, geomName) == 0)
                {
                    return &entry;
                }
            }

            return nullptr;
        }

        static void TrackChunkProxyDebugEntry(
            const uint8_t* objectBytes,
            const void* geomRef,
            const char* geomName,
            float positionX,
            float positionY,
            float positionZ)
        {
            if ((!g_EnableChunkProxyDebug && !g_EnableChunkMeshProxy) || !objectBytes)
                return;

            // Before a slot is taken: no slot means no mesh and no billboard,
            // which is the whole point -- an empty payload name still draws a
            // billboard sprite.
            if (const SuppressedChunkPiece* suppressed = FindSuppressedChunkPiece(geomName))
            {
                static volatile long s_SuppressedPieceLogBudget = 32;
                if (InterlockedDecrement(&s_SuppressedPieceLogBudget) >= 0)
                {
                    LogChunkDiagnostic(
                        "chunkmesh",
                        L"[CHUNKMESH] suppressed geom=%hs odf=%hs reason=%hs\n",
                        geomName,
                        g_ActiveFragmentSourceOdfName,
                        suppressed->reason);
                }
                return;
            }

            if (g_ChunkProxySlots.size() != g_ChunkProxyCapacity)
                g_ChunkProxySlots.resize(g_ChunkProxyCapacity);

            ChunkProxySlot* freeSlot = nullptr;
            const DWORD now = GetTickCount();
            for (ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (slot.active && slot.objectBytes == objectBytes)
                {
                    char resolvedMeshName[sizeof(slot.proofMeshName)] = {};
                    ChunkObjectLinkProbe probe = {};
                    CaptureChunkObjectLinkProbe(objectBytes, probe);
                    const ChunkBridgeSnapshot bridgeSnapshot = CaptureChunkBridgeSnapshot(objectBytes);
                    const char* preferredMeshName =
                        probe.cachedMeshName[0] ? probe.cachedMeshName : bridgeSnapshot.ownerResolvedMeshName;
                    slot.geomRef = geomRef;
                    if (geomName && *geomName)
                    {
                        strncpy_s(slot.geomName, geomName, _TRUNCATE);
                    }
                    else
                    {
                        slot.geomName[0] = '\0';
                    }
                    slot.positionX = positionX;
                    slot.positionY = positionY;
                    slot.positionZ = positionZ;
                    slot.useEntryPosition = true;
                    slot.ownerEntity = bridgeSnapshot.ownerEntity;
                    if (bridgeSnapshot.ownerEntityBaseName[0])
                        strncpy_s(slot.ownerEntityBaseName, bridgeSnapshot.ownerEntityBaseName, _TRUNCATE);
                    else
                        slot.ownerEntityBaseName[0] = '\0';
                    if (bridgeSnapshot.ownerOgreFilename[0])
                        strncpy_s(slot.ownerOgreFilename, bridgeSnapshot.ownerOgreFilename, _TRUNCATE);
                    else
                        slot.ownerOgreFilename[0] = '\0';
                    TryResolveChunkPayloadMeshResource(
                        probe,
                        preferredMeshName,
                        slot.geomName,
                        resolvedMeshName,
                        sizeof(resolvedMeshName));

                    if (_stricmp(slot.proofMeshName, resolvedMeshName) != 0)
                    {
                        InvalidateChunkMeshProxySlot(slot);
                        strncpy_s(slot.proofMeshName, sizeof(slot.proofMeshName), resolvedMeshName, _TRUNCATE);
                    }
                    slot.lastSeenTick = now;
                    return;
                }

                if (!slot.active && !freeSlot)
                    freeSlot = &slot;
            }

            if (!freeSlot)
                return;

            freeSlot->objectBytes = objectBytes;
            freeSlot->geomRef = geomRef;
            ChunkObjectLinkProbe probe = {};
            CaptureChunkObjectLinkProbe(objectBytes, probe);
            const ChunkBridgeSnapshot bridgeSnapshot = CaptureChunkBridgeSnapshot(objectBytes);
            const char* preferredMeshName =
                probe.cachedMeshName[0] ? probe.cachedMeshName : bridgeSnapshot.ownerResolvedMeshName;
            if (geomName && *geomName)
            {
                strncpy_s(freeSlot->geomName, geomName, _TRUNCATE);
            }
            else
            {
                freeSlot->geomName[0] = '\0';
            }
            freeSlot->positionX = positionX;
            freeSlot->positionY = positionY;
            freeSlot->positionZ = positionZ;
            freeSlot->useEntryPosition = true;
            freeSlot->ownerEntity = bridgeSnapshot.ownerEntity;
            if (bridgeSnapshot.ownerEntityBaseName[0])
                strncpy_s(freeSlot->ownerEntityBaseName, bridgeSnapshot.ownerEntityBaseName, _TRUNCATE);
            else
                freeSlot->ownerEntityBaseName[0] = '\0';
            if (bridgeSnapshot.ownerOgreFilename[0])
                strncpy_s(freeSlot->ownerOgreFilename, bridgeSnapshot.ownerOgreFilename, _TRUNCATE);
            else
                freeSlot->ownerOgreFilename[0] = '\0';
            if (!TryResolveChunkPayloadMeshResource(
                    probe,
                    preferredMeshName,
                    freeSlot->geomName,
                    freeSlot->proofMeshName,
                    sizeof(freeSlot->proofMeshName)))
            {
                freeSlot->proofMeshName[0] = '\0';
            }
            freeSlot->lastSeenTick = now;
            freeSlot->active = true;
            freeSlot->billboardAssigned = false;
            freeSlot->meshAssigned = false;
            if (AcquireChunkLogSlot())
            {
                LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] tracking obj=0x%08X geom=0x%08X geomName=%hs geomKind=%hs ownerEntity=0x%08X ownerBase=%hs ownerFile=%hs mesh=%hs pos=(%.4f, %.4f, %.4f)\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectBytes)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(geomRef)),
                    GetChunkGeomNameForLog(geomName),
                    ClassifyChunkGeomName(geomName),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(freeSlot->ownerEntity)),
                    freeSlot->ownerEntityBaseName[0] ? freeSlot->ownerEntityBaseName : "<none>",
                    freeSlot->ownerOgreFilename[0] ? freeSlot->ownerOgreFilename : "<none>",
                    freeSlot->proofMeshName[0] ? freeSlot->proofMeshName : "<none>",
                    static_cast<double>(positionX),
                    static_cast<double>(positionY),
                    static_cast<double>(positionZ));
            }
            if (freeSlot->proofMeshName[0])
                UpdateChunkProxySlotPosition(*freeSlot);
        }

        static void TrackChunkProxyDebugObject(
            const uint8_t* objectBytes,
            uint32_t objectType,
            const void* activeHandle,
            const BzrGeoLookup* lookup)
        {
            (void)objectBytes;
            (void)objectType;
            (void)activeHandle;
            (void)lookup;
        }

        static bool TryReadChunkEffectEntry(
            const uint8_t* thisBytes,
            uint32_t index,
            ChunkEffectActiveEntry& outEntry)
        {
            if (!thisBytes)
                return false;

            const uintptr_t entryOffset = kChunkEffectEntryBaseOffset +
                (static_cast<uintptr_t>(index) * kChunkEffectEntrySize);
            __try
            {
                const auto* entryBytes = thisBytes + entryOffset;
                outEntry.objectBytes = *reinterpret_cast<const uint8_t* const*>(entryBytes + 0x00);
                outEntry.reserved = *reinterpret_cast<const uint32_t*>(entryBytes + 0x04);
                outEntry.timer = *reinterpret_cast<const float*>(entryBytes + 0x08);
                outEntry.velocityX = *reinterpret_cast<const float*>(entryBytes + 0x0C);
                outEntry.velocityY = *reinterpret_cast<const float*>(entryBytes + 0x10);
                outEntry.velocityZ = *reinterpret_cast<const float*>(entryBytes + 0x14);
                outEntry.omegaX = *reinterpret_cast<const float*>(entryBytes + 0x18);
                outEntry.omegaY = *reinterpret_cast<const float*>(entryBytes + 0x1C);
                outEntry.omegaZ = 0.0f;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void LogChunkEffectRuntimeSample(void* thisPtr, float dt)
        {
            if (!g_TraceChunkEffectRuntime || !thisPtr)
                return;

            const auto* thisBytes = reinterpret_cast<const uint8_t*>(thisPtr);
            __try
            {
                const uint32_t count = *reinterpret_cast<const uint32_t*>(thisBytes + kChunkEffectActiveCountOffset);
                const bool shouldLog =
                    g_TraceChunkRenderVerbose ||
                    count > 0 ||
                    count != g_LastChunkEffectLoggedCount;
                g_LastChunkEffectLoggedCount = count;
                if (!shouldLog || !AcquireChunkLogSlot())
                    return;

                const uint32_t gate = *reinterpret_cast<const uint32_t*>(thisBytes + kChunkEffectGateOffset);
                const uint32_t templateList = *reinterpret_cast<const uint32_t*>(thisBytes + kChunkEffectTemplateListOffset);
                const uint32_t templateCount = *reinterpret_cast<const uint32_t*>(thisBytes + kChunkEffectTemplateListOffset + 4);
                const float tuning8038 = *reinterpret_cast<const float*>(thisBytes + kChunkEffectTuningBaseOffset + 0x0);
                const float tuning8044 = *reinterpret_cast<const float*>(thisBytes + kChunkEffectTuningBaseOffset + 0xC);
                const float tuning8048 = *reinterpret_cast<const float*>(thisBytes + kChunkEffectTuningBaseOffset + 0x10);

                LogChunkDiagnostic("chunkeffect", L"[CHUNKEFFECT] this=0x%08X dt=%.4f count=%u gate=0x%08X templateList=0x%08X templateCount=%u tune8038=%.4f tune8044=%.4f tune8048=%.4f\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)),
                    static_cast<double>(dt),
                    count,
                    gate,
                    templateList,
                    templateCount,
                    static_cast<double>(tuning8038),
                    static_cast<double>(tuning8044),
                    static_cast<double>(tuning8048));

                const uint32_t entryLimit = (std::min)(count, g_ChunkTraceEntryLimit);
                for (uint32_t index = 0; index < entryLimit; ++index)
                {
                    ChunkEffectActiveEntry entry = {};
                    if (!TryReadChunkEffectEntry(thisBytes, index, entry))
                    {
                        LogChunkDiagnostic("chunkeffect", L"[CHUNKEFFECT]   entry[%u] fault\n", index);
                        continue;
                    }

                    uint32_t classId = 0;
                    uint32_t flags = 0;
                    uint32_t owner = 0;
                    float timer = 0.0f;
                    const void* geomRef = nullptr;
                    char geomName[64] = {};
                    __try
                    {
                        if (entry.objectBytes)
                        {
                            classId = *reinterpret_cast<const uint32_t*>(entry.objectBytes + 0x84);
                            flags = *reinterpret_cast<const uint32_t*>(entry.objectBytes + 0x14);
                            owner = *reinterpret_cast<const uint32_t*>(entry.objectBytes + 0x8C);
                            timer = *reinterpret_cast<const float*>(entry.objectBytes + 0xAC);
                        }
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                    }
                    TryReadChunkGeomIdentity(entry.objectBytes, geomRef, geomName, sizeof(geomName));

                    LogChunkDiagnostic("chunkeffect", L"[CHUNKEFFECT]   entry[%u] obj=0x%08X reserved=0x%08X classId=%u flags=0x%08X owner=0x%08X timer=%.6f geom=0x%08X geomName=%hs geomKind=%hs vel=(%.4f, %.4f, %.4f) omega=(%.4f, %.4f, %.4f)\n",
                        index,
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entry.objectBytes)),
                        entry.reserved,
                        classId,
                        flags,
                        owner,
                        static_cast<double>(timer),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(geomRef)),
                        GetChunkGeomNameForLog(geomName),
                        ClassifyChunkGeomName(geomName),
                        static_cast<double>(entry.velocityX),
                        static_cast<double>(entry.velocityY),
                        static_cast<double>(entry.velocityZ),
                        static_cast<double>(entry.omegaX),
                        static_cast<double>(entry.omegaY),
                        static_cast<double>(entry.omegaZ));
                }

                if (count > entryLimit)
                {
                    LogChunkDiagnostic("chunkeffect", L"[CHUNKEFFECT]   ... truncated %u additional entries\n",
                        count - entryLimit);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                LogChunkDiagnostic("chunkeffect", L"[CHUNKEFFECT] sample fault this=0x%08X code=0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)),
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        static void TrackChunkEffectActiveEntries(void* thisPtr)
        {
            if ((!g_EnableChunkProxyDebug && !g_EnableChunkMeshProxy && !g_TraceChunkEffectRuntime) || !thisPtr)
                return;

            PruneChunkResolvedBindingsIfNeeded();

            const auto* thisBytes = reinterpret_cast<const uint8_t*>(thisPtr);
            __try
            {
                const uint32_t count = *reinterpret_cast<const uint32_t*>(thisBytes + kChunkEffectActiveCountOffset);
                for (uint32_t index = 0; index < count; ++index)
                {
                    ChunkEffectActiveEntry entry = {};
                    if (!TryReadChunkEffectEntry(thisBytes, index, entry))
                        continue;
                    if (!entry.objectBytes)
                        continue;

                    uint32_t classId = 0;
                    __try
                    {
                        classId = *reinterpret_cast<const uint32_t*>(entry.objectBytes + 0x84);
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        classId = 0;
                    }

                    if (classId != kClassIdChunk)
                        continue;

                    const void* geomRef = nullptr;
                    char geomName[64] = {};
                    TryReadChunkGeomIdentity(entry.objectBytes, geomRef, geomName, sizeof(geomName));

                    const ChunkResolvedBindingEntry* binding =
                        FindChunkResolvedBindingEntryForGeom(entry.objectBytes, geomName);
                    if (binding)
                        TouchChunkResolvedBinding(entry.objectBytes);
                    const ChunkBridgeSnapshot bridgeSnapshot = CaptureChunkBridgeSnapshot(entry.objectBytes);
                    float positionX = 0.0f;
                    float positionY = 0.0f;
                    float positionZ = 0.0f;
                    const void* resolvedPositionObject = nullptr;
                    if (!TryResolveChunkProxyPositionFromCandidates(
                            entry.objectBytes,
                            binding,
                            &bridgeSnapshot,
                            positionX,
                            positionY,
                            positionZ,
                            &resolvedPositionObject))
                    {
                        continue;
                    }

                    TrackChunkProxyDebugEntry(
                        entry.objectBytes,
                        geomRef,
                        geomName,
                        positionX,
                        positionY,
                        positionZ);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        ChunkBridgeSnapshot CaptureChunkBridgeSnapshot(const uint8_t* objectBytes)
        {
            ChunkBridgeSnapshot snapshot = {};
            if (!objectBytes)
                return snapshot;

            __try
            {
                snapshot.directBridgeRoot = *reinterpret_cast<void* const*>(objectBytes + 0xF0);
                if (snapshot.directBridgeRoot)
                {
                    const auto* bridgeBytes = reinterpret_cast<const uint8_t*>(snapshot.directBridgeRoot);
                    snapshot.directOgreEntity = *reinterpret_cast<void* const*>(bridgeBytes + 0x94);
                    snapshot.directOgreLight = *reinterpret_cast<void* const*>(bridgeBytes + 0xA8);
                }
                snapshot.directProbeOk = true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                snapshot.directProbeOk = false;
            }

            __try
            {
                // Legacy OBJ76 layouts observed in Redux helpers place the owning GameObject*
                // at +0x8C, which is the bridge we want to validate for native death chunks.
                snapshot.legacyOwner = *reinterpret_cast<void* const*>(objectBytes + 0x8C);
                if (snapshot.legacyOwner)
                {
                    const auto* ownerBytes = reinterpret_cast<const uint8_t*>(snapshot.legacyOwner);
                    snapshot.ownerBridgeRoot = *reinterpret_cast<void* const*>(ownerBytes + 0xF0);
                    snapshot.ownerEntity = *reinterpret_cast<void* const*>(ownerBytes + 0xF4);
                    snapshot.ownerObj = *reinterpret_cast<void* const*>(ownerBytes + 0xF8);

                    if (snapshot.ownerBridgeRoot)
                    {
                        const auto* bridgeBytes = reinterpret_cast<const uint8_t*>(snapshot.ownerBridgeRoot);
                        snapshot.ownerOgreEntity = *reinterpret_cast<void* const*>(bridgeBytes + 0x94);
                        snapshot.ownerOgreLight = *reinterpret_cast<void* const*>(bridgeBytes + 0xA8);
                    }
                }
                snapshot.ownerProbeOk = true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                snapshot.ownerProbeOk = false;
            }

            __try
            {
                snapshot.ownerNameProbeOk = TryReadOwnerEntityNames(
                    snapshot.ownerEntity,
                    snapshot.ownerEntityBaseName,
                    sizeof(snapshot.ownerEntityBaseName),
                    snapshot.ownerOgreFilename,
                    sizeof(snapshot.ownerOgreFilename),
                    snapshot.ownerResolvedMeshName,
                    sizeof(snapshot.ownerResolvedMeshName));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                snapshot.ownerEntityBaseName[0] = '\0';
                snapshot.ownerOgreFilename[0] = '\0';
                snapshot.ownerResolvedMeshName[0] = '\0';
                snapshot.ownerNameProbeOk = false;
            }

            return snapshot;
        }

        static void LogChunkClassProbe(const uint8_t* objectBytes)
        {
            if (!objectBytes)
                return;

            __try
            {
                // Redux's live OBJ76-like layout appears to preserve the legacy
                // parent/child/class/gameObj neighborhood, shifted down by 0x28:
                // legacy A0/A4/A8/AC/B0/B4 -> live 78/7C/80/84/88/8C.
                const void* parent = *reinterpret_cast<void* const*>(objectBytes + 0x78);
                const void* sibling = *reinterpret_cast<void* const*>(objectBytes + 0x7C);
                const void* child = *reinterpret_cast<void* const*>(objectBytes + 0x80);
                const uint32_t classId = *reinterpret_cast<const uint32_t*>(objectBytes + 0x84);
                const void* classPtr = *reinterpret_cast<void* const*>(objectBytes + 0x88);
                const void* gameObj = *reinterpret_cast<void* const*>(objectBytes + 0x8C);

                LogChunkDiagnostic("chunk", L"[CHUNK]   obj76Probe parent=0x%08X sibling=0x%08X child=0x%08X classId=0x%X classPtr=0x%08X gameObj=0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parent)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sibling)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(child)),
                    classId,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(classPtr)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(gameObj)));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                LogChunkDiagnostic("chunk", L"[CHUNK]   obj76Probe fault code=0x%08X\n",
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        static void LogChunkClassTransitionProbe(const uint8_t* objectBytes,
                                                uintptr_t objectKey,
                                                uint32_t previousClassId,
                                                uint32_t classId);

        static void NoteChunkClassTransition(const uint8_t* objectBytes, uint32_t classId)
        {
            if (!g_TraceChunkRender || !objectBytes)
                return;

            constexpr size_t kMaxTrackedChunkClasses = 8192;

            const uintptr_t objectKey = reinterpret_cast<uintptr_t>(objectBytes);
            if (g_ChunkObservedClassIds.size() >= kMaxTrackedChunkClasses &&
                g_ChunkObservedClassIds.find(objectKey) == g_ChunkObservedClassIds.end())
            {
                g_ChunkObservedClassIds.clear();
            }

            auto [it, inserted] = g_ChunkObservedClassIds.emplace(objectKey, classId);
            if (inserted)
                return;

            const uint32_t previousClassId = it->second;
            if (previousClassId == classId)
                return;

            it->second = classId;

            LogChunkClassTransitionProbe(objectBytes, objectKey, previousClassId, classId);
        }

        static void LogChunkClassTransitionProbe(const uint8_t* objectBytes,
                                                uintptr_t objectKey,
                                                uint32_t previousClassId,
                                                uint32_t classId)
        {
            if (!AcquireChunkLogSlot())
                return;

            __try
            {
                const void* parent = *reinterpret_cast<void* const*>(objectBytes + 0x78);
                const void* sibling = *reinterpret_cast<void* const*>(objectBytes + 0x7C);
                const void* child = *reinterpret_cast<void* const*>(objectBytes + 0x80);
                const void* classPtr = *reinterpret_cast<void* const*>(objectBytes + 0x88);
                const void* gameObj = *reinterpret_cast<void* const*>(objectBytes + 0x8C);

                LogChunkDiagnostic("chunk", L"[CHUNK] classChange obj=0x%08X old=0x%X new=0x%X parent=0x%08X sibling=0x%08X child=0x%08X classPtr=0x%08X gameObj=0x%08X\n",
                    static_cast<uint32_t>(objectKey),
                    previousClassId,
                    classId,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parent)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sibling)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(child)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(classPtr)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(gameObj)));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                LogChunkDiagnostic("chunk", L"[CHUNK] classChange obj=0x%08X old=0x%X new=0x%X probe=fault code=0x%08X\n",
                    static_cast<uint32_t>(objectKey),
                    previousClassId,
                    classId,
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        static void LogChunkResolveSnapshot(
            const char* stage,
            const char* reason,
            const uint8_t* objectBytes,
            uint32_t variant,
            uint32_t stockResolved,
            const void* activeBefore,
            const void* activeAfter,
            const BzrGeoLookup* lookup,
            int selectedIndex,
            uint32_t selectedKey)
        {
            if (!stage || !objectBytes)
                return;

            const uint32_t renderFlags = *reinterpret_cast<const uint32_t*>(objectBytes + 0x14);
            const uint32_t renderClass = renderFlags & 0xF000;
            const uint32_t objectType = *reinterpret_cast<const uint32_t*>(objectBytes + 0x84);
            const uint32_t lookupCount = lookup ? lookup->count : 0;
            const uint32_t cachedKey = lookup ? lookup->cachedKey : 0;
            const uintptr_t entriesPtr = lookup ? reinterpret_cast<uintptr_t>(lookup->entries) : 0;
            const ChunkBridgeSnapshot bridgeSnapshot = CaptureChunkBridgeSnapshot(objectBytes);

            LogChunkDiagnostic("chunk", L"[CHUNK] %hs obj=0x%08X variant=0x%08X resolved=0x%08X before=0x%08X after=0x%08X class=0x%04X classId=0x%X count=%u cached=0x%08X entries=0x%08X reason=%hs idx=%d key=0x%08X\n",
                stage,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectBytes)),
                variant,
                stockResolved,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(activeBefore)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(activeAfter)),
                renderClass,
                objectType,
                lookupCount,
                cachedKey,
                static_cast<uint32_t>(entriesPtr),
                reason ? reason : "-",
                selectedIndex,
                selectedKey);

            LogChunkDiagnostic("chunk", L"[CHUNK]   direct root=0x%08X entity=0x%08X light=0x%08X probe=%hs | owner=0x%08X ownerBridge=0x%08X ownerEntity=0x%08X ownerObj=0x%08X ownerOgre=0x%08X ownerLight=0x%08X ownerProbe=%hs ownerNameProbe=%hs ownerBase=%hs ownerFile=%hs ownerMesh=%hs\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.directBridgeRoot)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.directOgreEntity)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.directOgreLight)),
                bridgeSnapshot.directProbeOk ? "ok" : "fault",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.legacyOwner)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.ownerBridgeRoot)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.ownerEntity)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.ownerObj)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.ownerOgreEntity)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.ownerOgreLight)),
                bridgeSnapshot.ownerProbeOk ? "ok" : "fault",
                bridgeSnapshot.ownerNameProbeOk ? "ok" : "fault",
                bridgeSnapshot.ownerEntityBaseName[0] ? bridgeSnapshot.ownerEntityBaseName : "<none>",
                bridgeSnapshot.ownerOgreFilename[0] ? bridgeSnapshot.ownerOgreFilename : "<none>",
                bridgeSnapshot.ownerResolvedMeshName[0] ? bridgeSnapshot.ownerResolvedMeshName : "<none>");

            LogChunkClassProbe(objectBytes);

            if (!lookup || !lookup->entries || lookup->count == 0)
                return;

            const uint32_t entryLimit = (std::min)(lookup->count, g_ChunkTraceEntryLimit);
            for (uint32_t index = 0; index < entryLimit; ++index)
            {
                const BzrGeoEntry& entry = lookup->entries[index];
                LogChunkDiagnostic("chunk", L"[CHUNK]   entry[%u] key=0x%08X handle=0x%08X unk8=0x%08X unkC=0x%08X%s\n",
                    index,
                    entry.packedKey,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entry.handle)),
                    entry.unk8,
                    entry.unkC,
                    (selectedIndex == static_cast<int>(index)) ? " <selected>" : "");
            }

            if (lookup->count > entryLimit)
            {
                LogChunkDiagnostic("chunk", L"[CHUNK]   ... truncated %u additional entries\n",
                    lookup->count - entryLimit);
            }
        }

        static float ClampTurretAimPitchMultiplier(float value)
        {
            if (value < 0.0f)
                return 0.0f;
            if (value > 1.25f)
                return 1.25f;
            return value;
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

        // --- Global user preferences (openshim.ini) ----------------------------
        // A single user-editable INI carrying global preferences applied to ALL
        // single-player content (the stock campaign, Instant Action, and any
        // mission that does not script the setting itself). Two sections encode
        // the multiplayer-safety rule directly in the file layout:
        //   [Display]      cosmetic/local settings; applied everywhere, incl. MP.
        //   [SinglePlayer] sim/gameplay settings; applied in SP only, never MP.
        // Precedence per feature: engine default -> this file (user baseline) ->
        // mission script (EXU bridge) wins. A scripted override reverts to the
        // baseline captured from this file, not the hardcoded default, when the
        // mission ends (ResetMissionHookOverrides).
        static constexpr char kUserConfigGameplaySection[] = "Gameplay";
        static constexpr char kUserConfigDiagnosticsSection[] = "Diagnostics";
        static constexpr char kUserConfigFixesSection[] = "Fixes";






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
            if (mbi.State != MEM_COMMIT || !IsReadableDataProtect(mbi.Protect))
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
                if (vtableInfo.State != MEM_COMMIT || !IsReadableDataProtect(vtableInfo.Protect))
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

        static void RefreshTurretAimPitchState()
        {
            const bool active = g_TurretAimPitchEnabled && ReadLocalPlayerNetIdValue() == 0;
            g_TurretAimPitchMultiplier = active ? g_TurretAimPitchMultiplierEnhanced : 0.5f;
        }

        static void RefreshAiOdfGameplayTuningState()
        {
            g_AiOdfGameplayTuningActive =
                g_AiOdfGameplayTuningEnabled && ReadLocalPlayerNetIdValue() == 0;
        }

        static void RevertAiOdfGameplayTuningToBaseline()
        {
            g_AiOdfGameplayTuningEnabled = g_AiOdfGameplayTuningBaselineEnabled;
            RefreshAiOdfGameplayTuningState();
        }

        static void RefreshBomberAiRangeState()
        {
            g_BomberAiRangeActive =
                g_BomberAiRangeEnabled && IsSinglePlayerSession();
        }

        static void RevertBomberAiRangeToBaseline()
        {
            g_BomberAiRangeEnabled = g_BomberAiRangeBaselineEnabled;
            RefreshBomberAiRangeState();
        }

        // --- [Fixes] multiplayer gate reconcilers ------------------------------
        // Six of the seven are plain flag tests inside an already-installed
        // hook, so reconciling them is just the net-id AND. The APC fix rewrites
        // two branch displacements and needs its bytes put back, so it gets its
        // own reconciler next to the writer (declared below, defined with the
        // installer).
        static void RefreshSplinterUndeadFixState()
        {
            g_SplinterUndeadFixActive =
                g_SplinterUndeadFixEnabled && IsSinglePlayerSession();
        }

        static void RefreshTugCargoPostLoadFixState()
        {
            g_TugCargoPostLoadFixActive =
                g_TugCargoPostLoadFixEnabled && IsSinglePlayerSession();
        }

        static void RefreshConstructorRecycleStaleTargetFixState()
        {
            g_ConstructorRecycleStaleTargetFixActive =
                g_ConstructorRecycleStaleTargetFixEnabled && IsSinglePlayerSession();
        }

        static void RefreshHowitzerUndeployedRetaliationFixState()
        {
            g_HowitzerUndeployedRetaliationFixActive =
                g_HowitzerUndeployedRetaliationFixEnabled && IsSinglePlayerSession();
        }

        static void RefreshConstructorRemoteBuildFixState()
        {
            g_ConstructorRemoteBuildFixActive =
                g_ConstructorRemoteBuildFixEnabled && IsSinglePlayerSession();
        }


        static void InitializeGlobalImprovementConfig()
        {
            bool value = true;

            g_ScrapPilotHudLegacyLayoutEnabled = true;
            std::string layout;
            if (TryGetUserConfigString(kUserConfigDisplaySection, "ScrapPilotHud", layout))
            {
                std::transform(layout.begin(), layout.end(), layout.begin(),
                    [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
                if (layout == "stock" || layout == "default" || layout == "0" ||
                    layout == "off" || layout == "false")
                {
                    g_ScrapPilotHudLegacyLayoutEnabled = false;
                }
                else if (layout == "legacy" || layout == "compact" || layout == "1" ||
                         layout == "on" || layout == "true")
                {
                    g_ScrapPilotHudLegacyLayoutEnabled = true;
                }
                else
                {
                    Log(L"[HUD] Ignoring invalid ScrapPilotHud=%hs\n", layout.c_str());
                }
            }

            g_ShotConvergenceBaselineEnabled = true;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "WeaponConvergence", value))
                g_ShotConvergenceBaselineEnabled = value;
            g_ShotConvergenceEnabled = g_ShotConvergenceBaselineEnabled;

            g_PlayerReticleShotConvergenceBaselineEnabled = true;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "PlayerReticleConvergence", value) ||
                TryGetUserConfigBool(kUserConfigSinglePlayerSection, "SmartReticleConvergence", value))
            {
                g_PlayerReticleShotConvergenceBaselineEnabled = value;
            }
            g_PlayerReticleShotConvergenceEnabled =
                g_PlayerReticleShotConvergenceBaselineEnabled;

            g_SmartReticleRangeBaseline = kSmartReticleRangeDefault;
            std::string reticleRangeText;
            if (TryGetUserConfigString(
                    kUserConfigSinglePlayerSection,
                    "SmartReticleRange",
                    reticleRangeText) ||
                TryGetUserConfigString(
                    kUserConfigSinglePlayerSection,
                    "ReticleRange",
                    reticleRangeText))
            {
                char* end = nullptr;
                const float parsed = std::strtof(reticleRangeText.c_str(), &end);
                if (end != reticleRangeText.c_str() && *end == '\0' && std::isfinite(parsed))
                {
                    g_SmartReticleRangeBaseline = ClampSmartReticleRange(parsed);
                }
                else
                {
                    Log(L"[RETICLE] Ignoring invalid SmartReticleRange=%hs\n",
                        reticleRangeText.c_str());
                }
            }
            g_SmartReticleRangeOwnedByBridge = false;
            g_SmartReticleRange = g_SmartReticleRangeBaseline;

            g_SmartScavengerPathingEnabled = true;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "SmartScavengerPathing", value) ||
                TryGetUserConfigBool(kUserConfigSinglePlayerSection, "ScavengerPathing", value))
            {
                g_SmartScavengerPathingEnabled = value;
            }

            g_JumpSnipeCrouchBaselineEnabled = kJumpSnipeCrouchEnabledDefault;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "JumpSnipeCrouch", value))
                g_JumpSnipeCrouchBaselineEnabled = value;
            g_JumpSnipeCrouchEnabled = g_JumpSnipeCrouchBaselineEnabled;

            g_OrdnanceVelocityInheritanceBaselineEnabled =
                kOrdnanceVelocityInheritanceDefault;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection,
                                     "OrdnanceVelocityInheritance",
                                     value) ||
                TryGetUserConfigBool(kUserConfigSinglePlayerSection,
                                     "OrdnanceVelocInheritance",
                                     value))
            {
                g_OrdnanceVelocityInheritanceBaselineEnabled = value;
            }
            if (EnvFlagEnabled("OPENSHIM_DISABLE_ORDNANCE_VELOCITY_INHERITANCE"))
                g_OrdnanceVelocityInheritanceBaselineEnabled = false;
            g_OrdnanceVelocityInheritanceEnabled =
                g_OrdnanceVelocityInheritanceBaselineEnabled;

            g_RadarSizeScaleBaseline = 1.0f;
            std::string radarScaleText;
            if (TryGetUserConfigString(kUserConfigDisplaySection,
                                       "RadarSizeScale",
                                       radarScaleText))
            {
                char* end = nullptr;
                const float parsed = std::strtof(radarScaleText.c_str(), &end);
                if (end != radarScaleText.c_str() && *end == '\0' && std::isfinite(parsed))
                    g_RadarSizeScaleBaseline = ClampRadarSizeScaleSetting(parsed);
                else
                    Log(L"[RADAR] Ignoring invalid RadarSizeScale=%hs\n",
                        radarScaleText.c_str());
            }
            g_RadarSizeScale = g_RadarSizeScaleBaseline;

            g_SatelliteZoomOutMultiplierBaseline = 1.0f;
            std::string satelliteText;
            if (TryGetUserConfigString(kUserConfigSinglePlayerSection,
                                       "SatelliteZoomOut",
                                       satelliteText))
            {
                char* end = nullptr;
                const float parsed = std::strtof(satelliteText.c_str(), &end);
                if (end != satelliteText.c_str() && *end == '\0' && std::isfinite(parsed))
                    g_SatelliteZoomOutMultiplierBaseline = ClampSatelliteMultiplier(parsed);
                else
                    Log(L"[SATELLITE] Ignoring invalid SatelliteZoomOut=%hs\n",
                        satelliteText.c_str());
            }
            g_SatelliteZoomOutMultiplier = g_SatelliteZoomOutMultiplierBaseline;

            g_SatellitePanSpeedMultiplierBaseline = 1.0f;
            if (TryGetUserConfigString(kUserConfigSinglePlayerSection,
                                       "SatellitePanSpeed",
                                       satelliteText))
            {
                char* end = nullptr;
                const float parsed = std::strtof(satelliteText.c_str(), &end);
                if (end != satelliteText.c_str() && *end == '\0' && std::isfinite(parsed))
                    g_SatellitePanSpeedMultiplierBaseline = ClampSatelliteMultiplier(parsed);
                else
                    Log(L"[SATELLITE] Ignoring invalid SatellitePanSpeed=%hs\n",
                        satelliteText.c_str());
            }
            g_SatellitePanSpeedMultiplier = g_SatellitePanSpeedMultiplierBaseline;

            g_AllowNeutralAttackOrders = kAllowNeutralAttackOrdersDefault;
            if (TryGetUserConfigBool(
                    kUserConfigGameplaySection,
                    "AllowNeutralAttackOrders",
                    value))
            {
                g_AllowNeutralAttackOrders = value;
            }

            g_AipResolveTraceEnabled = kAipResolveTraceDefault;
            if (TryGetUserConfigBool(
                    kUserConfigDiagnosticsSection,
                    "AipResolveTrace",
                    value))
            {
                g_AipResolveTraceEnabled = value;
            }

            g_AiMultiProducerMakersEnabled = kAiMultiProducerMakersDefault;
            if (TryGetUserConfigBool(
                    kUserConfigFixesSection,
                    "AiMultiProducerMakers",
                    value))
            {
                g_AiMultiProducerMakersEnabled = value;
            }
            if (EnvFlagEnabled("OPENSHIM_DISABLE_AI_MULTI_PRODUCER_MAKERS"))
                g_AiMultiProducerMakersEnabled = false;

            g_TurretAimPitchBaselineEnabled = kTurretAimPitchEnabledDefault;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "TurretAimPitch", value))
                g_TurretAimPitchBaselineEnabled = value;
            g_TurretAimPitchEnabled = g_TurretAimPitchBaselineEnabled;

            // AiWeaponMaskSelection is the retired single key. It is still
            // honoured as the starting value for both halves so an existing
            // config keeps working, and either specific key then overrides it.
            g_AiWeaponMaskArtilleryEnabled = kAiWeaponMaskArtilleryEnabledDefault;
            g_AiWeaponMaskMinelayerEnabled = kAiWeaponMaskMinelayerEnabledDefault;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "AiWeaponMaskSelection", value))
            {
                g_AiWeaponMaskArtilleryEnabled = value;
                g_AiWeaponMaskMinelayerEnabled = value;
            }
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "AiWeaponMaskArtillery", value))
                g_AiWeaponMaskArtilleryEnabled = value;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "AiWeaponMaskMinelayer", value))
                g_AiWeaponMaskMinelayerEnabled = value;

            g_BomberAiRangeBaselineEnabled = kBomberAiRangeEnabledDefault;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "BomberAiRange", value))
                g_BomberAiRangeBaselineEnabled = value;
            g_BomberAiRangeEnabled = g_BomberAiRangeBaselineEnabled;
            RefreshBomberAiRangeState();

            g_AiOdfGameplayTuningBaselineEnabled = kAiOdfGameplayTuningEnabledDefault;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "AiOdfGameplayTuning", value))
                g_AiOdfGameplayTuningBaselineEnabled = value;
            g_AiOdfGameplayTuningEnabled = g_AiOdfGameplayTuningBaselineEnabled;

            float configuredMultiplier = 0.95f;
            std::string multiplierText;
            if (TryGetUserConfigString(
                    kUserConfigSinglePlayerSection,
                    "TurretAimPitchMultiplier",
                    multiplierText))
            {
                char* end = nullptr;
                const float parsed = std::strtof(multiplierText.c_str(), &end);
                if (end != multiplierText.c_str() && *end == '\0' && std::isfinite(parsed))
                    configuredMultiplier = parsed;
                else
                    Log(L"[TURRET] Ignoring invalid TurretAimPitchMultiplier=%hs\n",
                        multiplierText.c_str());
            }

            // Environment variables remain the highest-priority compatibility
            // override for existing installs and automation.
            if (TryGetEnvFloat("OPENSHIM_TURRET_AIM_PITCH_MULTIPLIER", configuredMultiplier) ||
                TryGetEnvFloat("OPENSHIM_TURRET_PITCH_MULTIPLIER", configuredMultiplier))
            {
            }
            g_TurretAimPitchMultiplierEnhanced =
                ClampTurretAimPitchMultiplier(configuredMultiplier);

            g_ScrapPilotHudLastRefreshTick = 0;
            RefreshTurretAimPitchState();
            RefreshAiWeaponMaskArtilleryState();
            RefreshAiWeaponMaskMinelayerState();
            RefreshAiOdfGameplayTuningState();
            RefreshJumpSnipeCrouchPatchState();
            RefreshOrdnanceVelocityInheritanceState();
            RefreshRadarSizeScaleState();
            RefreshSatelliteViewState();
            RefreshShotConvergencePatchState();
            RefreshSmartReticleRangeState();
            RefreshScrapPilotHudLayout();

            Log(L"[GLOBAL] scrapPilotHud=%hs weaponConvergence=%hs playerReticleConvergence=%hs smartReticleRange=%.3f smartScavengerPathing=%hs jumpSnipeCrouch=%hs neutralAttackOrders=%hs turretAim=%hs multiplier=%.3f aiOdfTuning=%hs (SinglePlayer features remain SP-only)\n",
                g_ScrapPilotHudLegacyLayoutEnabled ? "legacy" : "stock",
                BoolText(g_ShotConvergenceBaselineEnabled),
                BoolText(g_PlayerReticleShotConvergenceBaselineEnabled),
                static_cast<double>(g_SmartReticleRangeBaseline),
                BoolText(g_SmartScavengerPathingEnabled),
                BoolText(g_JumpSnipeCrouchBaselineEnabled),
                BoolText(g_AllowNeutralAttackOrders),
                BoolText(g_TurretAimPitchBaselineEnabled),
                static_cast<double>(g_TurretAimPitchMultiplierEnhanced),
                BoolText(g_AiOdfGameplayTuningBaselineEnabled));
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

        template <typename T>
        static T ReadValueAtOffset(const void* base, size_t offset)
        {
            return *reinterpret_cast<const T*>(reinterpret_cast<const uint8_t*>(base) + offset);
        }

        static bool ShouldEnableJumpSnipingProbe()
        {
            static int s_cached = -1;
            if (s_cached < 0)
            {
                char value[8] = {};
                DWORD len = GetEnvironmentVariableA("OPENSHIM_TRACE_JUMP_SNIPING",
                                                    value,
                                                    static_cast<DWORD>(sizeof(value)));
                if (!(len > 0 && len < sizeof(value) && value[0] != '0'))
                {
                    ZeroMemory(value, sizeof(value));
                    len = GetEnvironmentVariableA("OPENSHIM_TRACE_JUMPSNIPE",
                                                  value,
                                                  static_cast<DWORD>(sizeof(value)));
                }
                s_cached = (len > 0 && len < sizeof(value) && value[0] != '0') ? 1 : 0;
            }
            return s_cached != 0;
        }


        const char* BoolText(bool value)
        {
            return value ? "true" : "false";
        }

        static VerticalBand ClassifyVerticalBand(float velY)
        {
            if (velY > kJumpSnipeVelocityBandThreshold)
                return VerticalBand::Up;
            if (velY < -kJumpSnipeVelocityBandThreshold)
                return VerticalBand::Down;
            return VerticalBand::Flat;
        }

        static const char* VerticalBandText(VerticalBand band)
        {
            switch (band)
            {
            case VerticalBand::Down:
                return "down";
            case VerticalBand::Up:
                return "up";
            default:
                return "flat";
            }
        }

        static void FormatSigString(uint32_t sig, char (&out)[5])
        {
            out[0] = static_cast<char>((sig >> 24) & 0xFFu);
            out[1] = static_cast<char>((sig >> 16) & 0xFFu);
            out[2] = static_cast<char>((sig >> 8) & 0xFFu);
            out[3] = static_cast<char>(sig & 0xFFu);
            out[4] = '\0';

            for (size_t i = 0; i < 4; ++i)
            {
                const unsigned char ch = static_cast<unsigned char>(out[i]);
                if (ch < 32 || ch > 126)
                    out[i] = '.';
            }
        }



        static bool TryCaptureLocalPlayerSnapshot(JumpSnipeProbeSnapshot& out)
        {
            out = {};

            if (!g_BzrFn_GetPlayerHandle || !g_BzrFn_GameObjectGetObjByHandle)
                return false;

            __try
            {
                const int playerHandle = g_BzrFn_GetPlayerHandle();
                if (playerHandle == 0)
                    return false;

                void* person = g_BzrFn_GameObjectGetObjByHandle(playerHandle);
                if (!person)
                    return false;

                out.valid = true;
                out.playerHandle = playerHandle;
                out.person = person;
                out.obj = ReadValueAtOffset<void*>(person, kPersonObjOffset);
                out.velY = ReadValueAtOffset<float>(person, kGameObjectVelocityYOffset);
                out.animState = ReadValueAtOffset<uint32_t>(person, kPersonAnimStateOffset);
                out.curAnim = ReadValueAtOffset<long>(person, kPersonCurAnimOffset);
                out.animHandle = ReadValueAtOffset<int>(person, kPersonAnimHandleOffset);

                void* vhcl = ReadValueAtOffset<void*>(person, kPersonVehiclePtrOffset);
                if (vhcl)
                {
                    const uint32_t flags =
                        ReadValueAtOffset<uint32_t>(vhcl, kVehicleGroundFlagsOffset);
                    out.grounded = (flags & kVehicleGroundedFlagBit) != 0;
                }

                void* carrier = ReadValueAtOffset<void*>(person, kPersonCarrierOffset);
                if (!carrier)
                    return true;

                out.selectedMask = ReadValueAtOffset<uint32_t>(carrier, kCarrierSelectedOffset);
                auto** weapons =
                    reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(carrier) + kCarrierWeaponsOffset);

                for (int slot = 0; slot < 5; ++slot)
                {
                    if ((out.selectedMask & (1u << slot)) == 0)
                        continue;

                    out.selectedSlot = slot;
                    void* weapon = weapons[slot];
                    if (!weapon)
                        break;

                    void* weaponClass = ReadValueAtOffset<void*>(weapon, kWeaponClassOffset);
                    if (!weaponClass)
                        break;

                    out.selectedSig = ReadValueAtOffset<uint32_t>(weaponClass, kWeaponClassSigOffset);
                    const char* odf = reinterpret_cast<const char*>(
                        reinterpret_cast<const uint8_t*>(weaponClass) + kWeaponClassOdfOffset);
                    strncpy_s(out.selectedOdf, odf ? odf : "", _TRUNCATE);
                    out.sniperSelected = (out.selectedSig == kWeaponSigSnip);
                    break;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                out = {};
                return false;
            }

            return out.valid;
        }

        static bool HasMeaningfulJumpSnipeChange(const JumpSnipeProbeSnapshot& lhs,
                                                 const JumpSnipeProbeSnapshot& rhs)
        {
            return lhs.person != rhs.person ||
                   lhs.obj != rhs.obj ||
                   lhs.animState != rhs.animState ||
                   lhs.grounded != rhs.grounded ||
                   lhs.curAnim != rhs.curAnim ||
                   lhs.animHandle != rhs.animHandle ||
                   lhs.selectedMask != rhs.selectedMask ||
                   lhs.selectedSlot != rhs.selectedSlot ||
                   lhs.selectedSig != rhs.selectedSig ||
                   lhs.sniperSelected != rhs.sniperSelected ||
                   strcmp(lhs.selectedOdf, rhs.selectedOdf) != 0 ||
                   ClassifyVerticalBand(lhs.velY) != ClassifyVerticalBand(rhs.velY);
        }

        static void LogJumpSnipeProbeState(const JumpSnipeProbeSnapshot& before,
                                           const JumpSnipeProbeSnapshot& after,
                                           float dt)
        {
            if (!after.valid)
                return;

            char beforeSig[5] = {};
            char afterSig[5] = {};
            FormatSigString(before.selectedSig, beforeSig);
            FormatSigString(after.selectedSig, afterSig);

            Log(L"[JUMPSNIPE] dt=%.3f handle=%d person=0x%08X obj=0x%08X fsm=%u->%u grounded=%hs->%hs anim=%ld->%ld animH=%d->%d velY=%.3f->%.3f band=%hs->%hs sel=0x%08X->0x%08X slot=%d->%d sig=%hs->%hs odf=%hs->%hs sniper=%hs->%hs\n",
                dt,
                after.playerHandle,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(after.person)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(after.obj)),
                before.animState,
                after.animState,
                BoolText(before.grounded),
                BoolText(after.grounded),
                before.curAnim,
                after.curAnim,
                before.animHandle,
                after.animHandle,
                before.velY,
                after.velY,
                VerticalBandText(ClassifyVerticalBand(before.velY)),
                VerticalBandText(ClassifyVerticalBand(after.velY)),
                before.selectedMask,
                after.selectedMask,
                before.selectedSlot,
                after.selectedSlot,
                beforeSig,
                afterSig,
                before.selectedOdf,
                after.selectedOdf,
                BoolText(before.sniperSelected),
                BoolText(after.sniperSelected));
        }

        void __fastcall PersonSimulateJumpSnipeProbeHook(void* thisPtr, void* /*edx*/, float dt)
        {
            JumpSnipeProbeSnapshot before = {};
            TryCaptureLocalPlayerSnapshot(before);

            g_BzrFn_PersonSimulate(thisPtr, dt);

            JumpSnipeProbeSnapshot after = {};
            TryCaptureLocalPlayerSnapshot(after);

            if ((!before.valid || before.person != thisPtr) &&
                (!after.valid || after.person != thisPtr))
            {
                return;
            }

            const JumpSnipeProbeSnapshot& current = after.valid ? after : before;
            if (!g_JumpSnipeProbeLogState.initialized ||
                HasMeaningfulJumpSnipeChange(g_JumpSnipeProbeLogState.last, current))
            {
                LogJumpSnipeProbeState(before, after.valid ? after : before, dt);
                g_JumpSnipeProbeLogState.initialized = true;
                g_JumpSnipeProbeLogState.last = current;
            }
        }

        static void InstallJumpSnipingProbeIfRequested()
        {
            if (!ShouldEnableJumpSnipingProbe() || g_JumpSnipeProbeInstalled)
                return;

            if (g_PersonSimulateDetour.trampoline && g_BzrFn_PersonSimulate)
            {
                g_JumpSnipeProbeInstalled = true;
                return;
            }

            // push ebp; mov ebp,esp; push -1; push 0x84C1D6; (SEH frame setup).
            // 10 bytes lands on the instruction boundary after the push imm32.
            static const uint8_t kExpectedPersonSimulateBytes[kPersonSimulateDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0xD6, 0xC1, 0x84, 0x00
            };

            if (!ExpectedBytesMatchAt(kGogPersonSimulateEntryAddr,
                                      kExpectedPersonSimulateBytes,
                                      sizeof(kExpectedPersonSimulateBytes)))
            {
                // Called every sim tick until the probe installs, so say it once.
                if (!g_JumpSnipeProbeMismatchLogged)
                {
                    g_JumpSnipeProbeMismatchLogged = true;
                    Log(L"[JUMPSNIPE] Person::Simulate entry at 0x%08X does not match; probe and player-handle lookup stand down\n",
                        static_cast<uint32_t>(kGogPersonSimulateEntryAddr));
                }
                return;
            }

            // The entry bytes just checked (an SEH frame naming this build's
            // handler) are the identity proof for the GOG constants, so they
            // are published only now. They used to be written before the
            // check, so a build that then failed it still handed every later
            // consumer -- career stats, the kill trace,
            // TryGetLocalPlayerWorldPosition -- an unverified address.
            g_BzrFn_GetPlayerHandle = reinterpret_cast<FnGetPlayerHandle>(kGogGetPlayerHandleAddr);
            g_BzrFn_GameObjectGetObjByHandle =
                &GameObjectFromHandleGog; // was 0x0046B160 (wrong fn; crashed)

            if (!InstallInlineDetour32(g_PersonSimulateDetour,
                                       kGogPersonSimulateEntryAddr,
                                       reinterpret_cast<void*>(PersonSimulateJumpSnipeProbeHook),
                                       kPersonSimulateDetourLen,
                                       kExpectedPersonSimulateBytes,
                                       sizeof(kExpectedPersonSimulateBytes)))
            {
                Log(L"[JUMPSNIPE] Failed to install Person::Simulate probe at 0x%08X\n",
                    static_cast<uint32_t>(kGogPersonSimulateEntryAddr));
                return;
            }

            g_BzrFn_PersonSimulate =
                reinterpret_cast<FnPersonSimulate>(g_PersonSimulateDetour.trampoline);
            g_JumpSnipeProbeInstalled = (g_BzrFn_PersonSimulate != nullptr);
            if (g_JumpSnipeProbeInstalled)
            {
                Log(L"[JUMPSNIPE] Installed %hs player Person::Simulate probe entry=0x%08X trampoline=0x%08X env=OPENSHIM_TRACE_JUMP_SNIPING\n",
                    g_IsSteamExe ? "Steam" : "GOG",
                    static_cast<uint32_t>(kGogPersonSimulateEntryAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_PersonSimulateDetour.trampoline)));
            }
        }

        static void RevertTurretAimPitchToBaseline()
        {
            g_TurretAimPitchEnabled = g_TurretAimPitchBaselineEnabled;
            RefreshTurretAimPitchState();
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

        // --- Global feature registry -------------------------------------------
        // One coordination point for the user-config / EXU-bridge driven features.
        // Each feature keeps its own apply/parse/baseline internals; the registry
        // only centralizes the two cross-cutting lifecycle actions so new features
        // are a single appended row instead of another open-coded call at every
        // reset/tick site:
        //   revertToBaseline  restore the post-mission resting state — the user's
        //                     openshim.ini baseline for Display features, the build
        //                     default for gameplay features. Called on mission end.
        //   refreshMpGate     reconcile a SinglePlayer-tier feature against the
        //                     live net id so it can never touch a network game.
        //                     Called on mission end and from the periodic sim tick.
        // Tier is advisory metadata today (it documents the [Display] vs
        // [SinglePlayer] openshim.ini section and whether refreshMpGate is required)
        // and is the hook future native features will read to auto-gate themselves.
        enum class FeatureTier
        {
            Display,       // cosmetic/local; applied everywhere, including MP.
            SinglePlayer,  // sim/gameplay; applied in SP only, hard-off in MP.
        };

        struct FeatureDescriptor
        {
            const char* name;
            FeatureTier tier;
            void (*revertToBaseline)();  // nullptr = nothing to revert
            void (*refreshMpGate)();     // nullptr = not multiplayer-gated
        };

        static const FeatureDescriptor g_FeatureRegistry[] = {
            { "UnderAttackAlert", FeatureTier::Display,
              &RevertUnderAttackAlertToBaseline, nullptr },
            { "TargetReticle", FeatureTier::Display,
              &RevertTargetReticlePopupToBaseline, nullptr },
            { "UnitVoFeedback", FeatureTier::Display,
              &RevertUnitVoToBaseline, nullptr },
            { "ScrapPilotHud", FeatureTier::Display,
              &RevertScrapPilotHudToBaseline, &RefreshScrapPilotHudLayout },
            { "WeaponConvergence", FeatureTier::SinglePlayer,
              &RevertShotConvergenceToBaseline, &RefreshShotConvergencePatchState },
            { "SmartReticleRange", FeatureTier::SinglePlayer,
              &RevertSmartReticleRangeToBaseline, &RefreshSmartReticleRangeState },
            { "TurretAimPitch", FeatureTier::SinglePlayer,
              &RevertTurretAimPitchToBaseline, &RefreshTurretAimPitchState },
            { "JumpSnipeCrouch", FeatureTier::SinglePlayer,
              &RevertJumpSnipeCrouchToBaseline, &RefreshJumpSnipeCrouchPatchState },
            { "OrdnanceVelocityInheritance", FeatureTier::SinglePlayer,
              &RevertOrdnanceVelocityInheritanceToBaseline,
              &RefreshOrdnanceVelocityInheritanceState },
            // Local HUD geometry; applied everywhere, including MP.
            { "RadarSizeScale", FeatureTier::Display,
              &RevertRadarSizeScaleToBaseline, nullptr },
            { "SatelliteView", FeatureTier::SinglePlayer,
              &RevertSatelliteViewToBaseline, &RefreshSatelliteViewState },
            { "GlobalTurbo", FeatureTier::SinglePlayer,
              &RevertGlobalTurboToBaseline, &RefreshGlobalTurboPatchState },
            { "Headlights", FeatureTier::SinglePlayer,
              &RevertHeadlightsToBaseline, &RefreshHeadlightState },
            { "PilotFlashlight", FeatureTier::SinglePlayer,
              &RevertPilotFlashlightToBaseline, &RefreshPilotFlashlightState },
            { "PilotTeamRestore", FeatureTier::SinglePlayer,
              &RevertPilotTeamRestoreToBaseline, &RefreshPilotTeamRestoreState },
            { "AiWeaponMaskArtillery", FeatureTier::SinglePlayer,
              &RevertAiWeaponMaskArtilleryToBaseline, &RefreshAiWeaponMaskArtilleryState },
            { "AiWeaponMaskMinelayer", FeatureTier::SinglePlayer,
              &RevertAiWeaponMaskMinelayerToBaseline, &RefreshAiWeaponMaskMinelayerState },
            { "AiOdfGameplayTuning", FeatureTier::SinglePlayer,
              &RevertAiOdfGameplayTuningToBaseline, &RefreshAiOdfGameplayTuningState },
            { "BomberAiRange", FeatureTier::SinglePlayer,
              &RevertBomberAiRangeToBaseline, &RefreshBomberAiRangeState },
            { "AttackRevealPerceivedTeam", FeatureTier::SinglePlayer,
              &RevertAttackRevealToBaseline, &RefreshAttackRevealState },
            // Display tier: purely observational, writes only its own config
            // file, and must keep running in network games.
            { "CareerStats", FeatureTier::Display,
              &RevertCareerStatsToBaseline, nullptr },
            // Client-side only, so it cannot desync -- but it is documented
            // under [SinglePlayer], and standing it down online is what keeps
            // a shim player's satellite view equivalent to a stock peer's.
            { "SatelliteVisibilityFix", FeatureTier::SinglePlayer,
              nullptr, &RefreshSatelliteVisibilityFixState },
            // [Fixes] engine-defect corrections. They are bug fixes rather than
            // enhancements and stay on for normal single-player play, but every
            // one of them changes simulation behaviour and none is negotiated
            // with peers, so they stand down for the duration of a network game
            // and a mixed OpenShim/stock lobby stays behaviourally identical.
            // There is no baseline to revert: the openshim.ini answer is read
            // once at startup and never scripted, so the gate is all they need.
            { "ApcAlliedTargetDeploy", FeatureTier::SinglePlayer,
              nullptr, &RefreshApcAlliedTargetDeployFixState },
            { "SplinterUndead", FeatureTier::SinglePlayer,
              nullptr, &RefreshSplinterUndeadFixState },
            { "HowitzerUndeployedRetaliation", FeatureTier::SinglePlayer,
              nullptr, &RefreshHowitzerUndeployedRetaliationFixState },
            { "OwnedObjectReveal", FeatureTier::SinglePlayer,
              nullptr, &RefreshOwnedObjectRevealFixState },
            { "TugCargoPostLoad", FeatureTier::SinglePlayer,
              nullptr, &RefreshTugCargoPostLoadFixState },
            { "ConstructorRecycleStaleTarget", FeatureTier::SinglePlayer,
              nullptr, &RefreshConstructorRecycleStaleTargetFixState },
            { "ConstructorRemoteBuild", FeatureTier::SinglePlayer,
              nullptr, &RefreshConstructorRemoteBuildFixState },
        };

        // Restore every registered feature to its resting state (mission end).
        static void RevertRegisteredFeaturesToBaseline()
        {
            for (const auto& feature : g_FeatureRegistry)
            {
                if (feature.revertToBaseline)
                    feature.revertToBaseline();
            }
        }

        // Reconcile every multiplayer-gated feature against the current net id.
        static void RefreshRegisteredMpGatedFeatures()
        {
            for (const auto& feature : g_FeatureRegistry)
            {
                if (feature.refreshMpGate)
                    feature.refreshMpGate();
            }
        }

        // Slow re-assert cadence for the gate. A net id change reconciles
        // immediately regardless; this only bounds how long a patch site the
        // engine rewrote underneath us can stay out of sync.
        constexpr ULONGLONG kMpGateReassertMs = 250;

        // The gate's driver. Until now the only caller of
        // RefreshRegisteredMpGatedFeatures was ChunkEffectSimulateHook, which
        // runs only while debris is simulating -- so a byte-patched
        // SinglePlayer feature armed before a network game started stayed armed
        // until that match's first explosion. This is called from the Ogre
        // world-queue update as well, which runs every rendered frame whether or
        // not anything has blown up, and reconciles the instant the net id moves.
        static void TickMpGateReconcile()
        {
            static uint16_t s_LastNetId = 0;
            static ULONGLONG s_LastReconcileTick = 0;

            // Only reconcile while a mission world exists. Some registry
            // entries write executable bytes (the crouch branch, the turbo
            // hooks), and this must not pull those writes earlier than the
            // chunk-effect driver already did: on Steam a .text write before
            // the runtime has settled trips SteamStub's integrity check. The
            // net id is deliberately NOT sampled into s_LastNetId here, so a
            // change that happened in the shell still reconciles on the first
            // frame of the mission that follows.
            if (!SatelliteWorldIsLive())
                return;

            const uint16_t netId = ReadLocalPlayerNetIdValue();
            const ULONGLONG now = GetTickCount64();
            const bool netIdChanged = netId != s_LastNetId;

            if (!netIdChanged &&
                s_LastReconcileTick != 0 &&
                now - s_LastReconcileTick < kMpGateReassertMs)
            {
                return;
            }

            if (netIdChanged)
            {
                Log(L"[MPGATE] net id %u -> %u; reconciling SinglePlayer-tier features (%hs)\n",
                    static_cast<unsigned>(s_LastNetId),
                    static_cast<unsigned>(netId),
                    netId == 0 ? "single-player" : "network game");
            }

            s_LastNetId = netId;
            s_LastReconcileTick = now;
            RefreshRegisteredMpGatedFeatures();
        }

        static void InstallChunkEffectCreateHooksIfRequested()
        {
            if ((!g_TraceChunkRender && !g_TraceChunkEffectRuntime) || g_ChunkEffectCreateHooksInstalled)
                return;

            static const uint8_t kExpectedCreateChunkletBytes[kChunkEffectCreateExpectedLen] =
            {
                0x55, 0x8B, 0xEC, 0x81, 0xEC, 0xB8, 0x00, 0x00,
                0x00, 0xA1, 0x00, 0x70, 0x8E, 0x00, 0x33, 0xC5
            };
            static const uint8_t kExpectedCreateChunkBytes[kChunkEffectCreateExpectedLen] =
            {
                0x55, 0x8B, 0xEC, 0x81, 0xEC, 0xA8, 0x00, 0x00,
                0x00, 0xA1, 0x00, 0x70, 0x8E, 0x00, 0x33, 0xC5
            };

            if (g_IsSteamExe && !g_AllowUnsafeSteamChunkCreateHooks)
            {
                const ULONGLONG nowMs = GetTickCount64();
                if (g_ChunkEffectCreateHooksReadyTick != 0 && nowMs < g_ChunkEffectCreateHooksReadyTick)
                {
                    if (!g_ChunkEffectCreateHooksWaitLogged)
                    {
                        LogChunkDiagnostic(
                            "chunkspawn",
                            L"[CHUNKSPAWN] Steam creator hooks waiting %llums for settled-byte verification\n",
                            static_cast<unsigned long long>(g_ChunkEffectCreateHooksReadyTick - nowMs));
                        g_ChunkEffectCreateHooksWaitLogged = true;
                    }
                    return;
                }

                const bool createChunkBytesMatch =
                    ExpectedBytesMatchAt(
                        kGogChunkEffectCreateChunkAddr,
                        kExpectedCreateChunkBytes,
                        sizeof(kExpectedCreateChunkBytes));
                const bool createChunkletBytesMatch =
                    ExpectedBytesMatchAt(
                        kGogChunkEffectCreateChunkletAddr,
                        kExpectedCreateChunkletBytes,
                        sizeof(kExpectedCreateChunkletBytes));
                if (!createChunkBytesMatch || !createChunkletBytesMatch)
                {
                    if (!g_ChunkEffectCreateHooksMismatchLogged)
                    {
                        LogChunkDiagnostic(
                            "chunkspawn",
                            L"[CHUNKSPAWN] Steam creator hooks still waiting for settled bytes create=%hs chunklet=%hs\n",
                            createChunkBytesMatch ? "ok" : "mismatch",
                            createChunkletBytesMatch ? "ok" : "mismatch");
                        g_ChunkEffectCreateHooksMismatchLogged = true;
                    }
                    return;
                }
            }

            if (g_ChunkEffectCreateChunkDetour.trampoline && g_BzrFn_ChunkEffectCreateChunk &&
                g_ChunkEffectCreateChunkletDetour.trampoline && g_BzrFn_ChunkEffectCreateChunklet)
            {
                g_ChunkEffectCreateHooksInstalled = true;
            }
            else
            {
                if (!g_ChunkEffectCreateChunkDetour.trampoline)
                {
                    InstallInlineDetour32(
                        g_ChunkEffectCreateChunkDetour,
                        kGogChunkEffectCreateChunkAddr,
                        reinterpret_cast<void*>(ChunkEffectCreateChunkHook),
                        kChunkEffectCreateChunkDetourLen,
                        nullptr,
                        0);
                }
                if (g_ChunkEffectCreateChunkDetour.trampoline)
                {
                    g_BzrFn_ChunkEffectCreateChunk = reinterpret_cast<FnChunkEffectCreateChunk>(
                        g_ChunkEffectCreateChunkDetour.trampoline);
                }

                if (!g_ChunkEffectCreateChunkletDetour.trampoline)
                {
                    InstallInlineDetour32(
                        g_ChunkEffectCreateChunkletDetour,
                        kGogChunkEffectCreateChunkletAddr,
                        reinterpret_cast<void*>(ChunkEffectCreateChunkletHook),
                        kChunkEffectCreateChunkletDetourLen,
                        nullptr,
                        0);
                }
                if (g_ChunkEffectCreateChunkletDetour.trampoline)
                {
                    g_BzrFn_ChunkEffectCreateChunklet = reinterpret_cast<FnChunkEffectCreateChunklet>(
                        g_ChunkEffectCreateChunkletDetour.trampoline);
                }

                g_ChunkEffectCreateHooksInstalled =
                    g_ChunkEffectCreateChunkDetour.trampoline &&
                    g_BzrFn_ChunkEffectCreateChunk &&
                    g_ChunkEffectCreateChunkletDetour.trampoline &&
                    g_BzrFn_ChunkEffectCreateChunklet;
            }

            if (g_ChunkEffectCreateHooksInstalled && !g_ChunkEffectCreateHooksLogged)
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN] Installed create hooks create=0x%08X chunklet=0x%08X\n",
                    static_cast<uint32_t>(kGogChunkEffectCreateChunkAddr),
                    static_cast<uint32_t>(kGogChunkEffectCreateChunkletAddr));
                g_ChunkEffectCreateHooksLogged = true;
            }
        }

        // Diagnostic detours on ChunkEffect::PartialFragmentObject/FullFragmentObject
        // (the walkers Craft/Building explode paths hand the dying OBJ76 tree to).
        // Logs the tree each walk receives so "death produced no CreateChunk" can be
        // told apart from "walker never ran". GOG only; addresses are GOG layout.
        static void InstallChunkFragmentWalkHooksIfRequested()
        {
            if ((!g_TraceChunkRender && !g_TraceChunkEffectRuntime) ||
                g_ChunkEffectFragmentHooksInstalled || g_IsSteamExe)
                return;

            static const uint8_t kExpectedPartialFragmentBytes[kChunkEffectFragmentDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x30
            };
            static const uint8_t kExpectedFullFragmentBytes[kChunkEffectFragmentDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x28
            };

            if (!g_ChunkEffectPartialFragmentDetour.trampoline)
            {
                InstallInlineDetour32(
                    g_ChunkEffectPartialFragmentDetour,
                    kGogChunkEffectPartialFragmentAddr,
                    reinterpret_cast<void*>(ChunkEffectPartialFragmentHook),
                    kChunkEffectFragmentDetourLen,
                    kExpectedPartialFragmentBytes,
                    sizeof(kExpectedPartialFragmentBytes));
            }
            if (g_ChunkEffectPartialFragmentDetour.trampoline)
            {
                g_BzrFn_ChunkEffectPartialFragment = reinterpret_cast<FnChunkEffectFragmentObject>(
                    g_ChunkEffectPartialFragmentDetour.trampoline);
            }

            if (!g_ChunkEffectFullFragmentDetour.trampoline)
            {
                InstallInlineDetour32(
                    g_ChunkEffectFullFragmentDetour,
                    kGogChunkEffectFullFragmentAddr,
                    reinterpret_cast<void*>(ChunkEffectFullFragmentHook),
                    kChunkEffectFragmentDetourLen,
                    kExpectedFullFragmentBytes,
                    sizeof(kExpectedFullFragmentBytes));
            }
            if (g_ChunkEffectFullFragmentDetour.trampoline)
            {
                g_BzrFn_ChunkEffectFullFragment = reinterpret_cast<FnChunkEffectFragmentObject>(
                    g_ChunkEffectFullFragmentDetour.trampoline);
            }

            g_ChunkEffectFragmentHooksInstalled =
                g_ChunkEffectPartialFragmentDetour.trampoline &&
                g_BzrFn_ChunkEffectPartialFragment &&
                g_ChunkEffectFullFragmentDetour.trampoline &&
                g_BzrFn_ChunkEffectFullFragment;

            if (g_ChunkEffectFragmentHooksInstalled && !g_ChunkEffectFragmentHooksLogged)
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN] Installed fragment walk hooks partial=0x%08X full=0x%08X\n",
                    static_cast<uint32_t>(kGogChunkEffectPartialFragmentAddr),
                    static_cast<uint32_t>(kGogChunkEffectFullFragmentAddr));
                g_ChunkEffectFragmentHooksLogged = true;
            }
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

        static std::string ReadFixedAsciiField(const uint8_t* bytes, size_t length)
        {
            if (!bytes || length == 0)
                return {};

            size_t end = 0;
            while (end < length && bytes[end] != 0)
                ++end;

            std::string text(reinterpret_cast<const char*>(bytes), end);
            return TrimAsciiCopy(text);
        }

        static uint32_t ReadLeU32(const uint8_t* bytes)
        {
            if (!bytes)
                return 0;

            uint32_t value = 0;
            std::memcpy(&value, bytes, sizeof(value));
            return value;
        }

        static std::string NormalizeChunkMeshBaseName(const char* meshName)
        {
            if (!meshName || !*meshName)
                return {};

            std::string baseName(meshName);
            const size_t slash = baseName.find_last_of("/\\");
            if (slash != std::string::npos)
                baseName.erase(0, slash + 1);

            const size_t dot = baseName.find_last_of('.');
            if (dot != std::string::npos)
                baseName.erase(dot);

            std::transform(
                baseName.begin(),
                baseName.end(),
                baseName.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
            return baseName;
        }

        static std::filesystem::path GetChunkPayloadStockResourceDirectory()
        {
            return GetMainModuleDirectory() / "BZ_ASSETS" / "common" / "models" / kChunkPayloadResourceRootName;
        }

        static void RefreshChunkPayloadResourceDirectories()
        {
            g_ChunkPayloadResourceDirectories.clear();

            const std::filesystem::path gameDir = GetMainModuleDirectory();
            static constexpr const char* kPayloadDirNames[] =
            {
                kChunkPayloadModRelativeDirName,
                kChunkPayloadModRelativeDirNameAlt,
            };
            for (const std::filesystem::path& modRoot : GetCampaignContentRootCandidates(gameDir))
            {
                for (const char* dirName : kPayloadDirNames)
                {
                    const std::filesystem::path candidate = modRoot / dirName;
                    std::error_code ec;
                    if (std::filesystem::exists(candidate, ec) && !ec &&
                        std::filesystem::is_directory(candidate, ec) && !ec)
                    {
                        AppendUniquePath(g_ChunkPayloadResourceDirectories, candidate);
                    }
                }
            }

            const std::filesystem::path stockDir = GetChunkPayloadStockResourceDirectory();
            std::error_code stockError;
            if (std::filesystem::exists(stockDir, stockError) && !stockError &&
                std::filesystem::is_directory(stockDir, stockError) && !stockError)
            {
                AppendUniquePath(g_ChunkPayloadResourceDirectories, stockDir);
            }
        }

        static const std::vector<std::filesystem::path>& GetChunkPayloadResourceDirectories()
        {
            if (g_ChunkPayloadResourceDirectories.empty())
                RefreshChunkPayloadResourceDirectories();

            return g_ChunkPayloadResourceDirectories;
        }

        static std::string NormalizeChunkPayloadComponentName(const char* value)
        {
            return NormalizeChunkMeshBaseName(value);
        }

        static void AppendUniqueChunkPayloadCandidate(
            std::vector<std::string>& candidates,
            const std::string& candidate)
        {
            if (candidate.empty())
                return;

            // Candidate strings are pre-normalized to lowercase by callers via
            // NormalizeChunkMeshBaseName / NormalizeChunkPayloadComponentName.
            // Using operator== provides O(1) string length short-circuiting
            // and fast byte comparison without CRT locale overhead (_stricmp).
            for (const std::string& existing : candidates)
            {
                if (existing == candidate)
                    return;
            }

            candidates.push_back(candidate);
        }

        static void AppendChunkPayloadCandidatesFromPipeList(
            const char* listText,
            std::vector<std::string>& outCandidates)
        {
            if (!listText || !*listText)
                return;

            const char* cursor = listText;
            while (*cursor)
            {
                const char* separator = std::strchr(cursor, '|');
                const size_t tokenLength = separator
                    ? static_cast<size_t>(separator - cursor)
                    : std::strlen(cursor);
                if (tokenLength > 0)
                {
                    std::string token(cursor, tokenLength);
                    AppendUniqueChunkPayloadCandidate(
                        outCandidates,
                        NormalizeChunkPayloadComponentName(token.c_str()));
                }

                if (!separator)
                    break;
                cursor = separator + 1;
            }
        }

        static std::string JoinChunkPayloadCandidates(const std::vector<std::string>& candidates)
        {
            std::string result;
            for (size_t index = 0; index < candidates.size(); ++index)
            {
                if (index != 0)
                    result += "|";
                result += candidates[index];
            }

            return result;
        }

        static void LogChunkPayloadResolveFailureOnce(
            const ChunkObjectLinkProbe& probe,
            const char* preferredMeshName,
            const char* explicitGeomName,
            const std::vector<std::string>& meshCandidates,
            const std::vector<std::string>& geomCandidates)
        {
            if (!g_EnableChunkMeshProxy && !g_TraceChunkRender && !g_TraceChunkEffectRuntime)
                return;

            const std::string meshCandidateText = JoinChunkPayloadCandidates(meshCandidates);
            const std::string geomCandidateText = JoinChunkPayloadCandidates(geomCandidates);

            std::string fingerprint;
            fingerprint.reserve(
                meshCandidateText.size() + geomCandidateText.size() +
                std::strlen(probe.cachedMeshName) + std::strlen(probe.geomName) +
                std::strlen(probe.vdfCandidates) + 48);
            fingerprint += meshCandidateText;
            fingerprint += "||";
            fingerprint += geomCandidateText;
            fingerprint += "||";
            fingerprint += probe.cachedMeshName;
            fingerprint += "||";
            fingerprint += probe.geomName;
            fingerprint += "||";
            fingerprint += probe.vdfCandidates;

            if (g_ChunkPayloadResolveFailureLogCache.size() >= kChunkPayloadResolveFailureLogCacheLimit &&
                g_ChunkPayloadResolveFailureLogCache.find(fingerprint) == g_ChunkPayloadResolveFailureLogCache.end())
            {
                g_ChunkPayloadResolveFailureLogCache.clear();
            }

            if (!g_ChunkPayloadResolveFailureLogCache.insert(fingerprint).second)
                return;

            // Acquire the shared slot only once the dedup cache says this line
            // will actually be written; otherwise repeated resolve failures
            // drain the budget silently and blind all lifecycle logging.
            if (!AcquireChunkLogSlot())
                return;

            LogChunkDiagnostic(
                "chunkmesh",
                L"[CHUNKMESH] payload resolve miss obj=0x%08X class=%u preferredMesh=%hs cachedMesh=%hs explicitGeom=%hs probeGeom=%hs vdf=%hs meshCandidates=%hs geomCandidates=%hs\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(probe.objectBytes)),
                probe.classId,
                preferredMeshName ? preferredMeshName : "",
                probe.cachedMeshName[0] ? probe.cachedMeshName : "<none>",
                explicitGeomName ? explicitGeomName : "",
                probe.geomName[0] ? probe.geomName : "<none>",
                probe.vdfCandidates[0] ? probe.vdfCandidates : "<none>",
                meshCandidateText.empty() ? "<none>" : meshCandidateText.c_str(),
                geomCandidateText.empty() ? "<none>" : geomCandidateText.c_str());
        }

        static bool ChunkPayloadFlatMeshExists(const std::string& fileName)
        {
            if (fileName.empty())
                return false;

            auto cacheIt = g_ChunkPayloadMeshExistsCache.find(fileName);
            if (cacheIt != g_ChunkPayloadMeshExistsCache.end())
                return cacheIt->second;

            bool exists = false;
            for (const std::filesystem::path& resourceRoot : GetChunkPayloadResourceDirectories())
            {
                std::error_code error;
                if (std::filesystem::exists(resourceRoot / fileName, error) && !error)
                {
                    exists = true;
                    break;
                }
            }
            g_ChunkPayloadMeshExistsCache.emplace(fileName, exists);
            return exists;
        }

        // Lowercased payload stems per craft directory, built once on demand.
        static std::unordered_map<std::string, std::vector<std::string>> g_ChunkPayloadDirListingCache;

        static const std::vector<std::string>& GetChunkPayloadDirListing(const std::string& meshBase)
        {
            const auto cached = g_ChunkPayloadDirListingCache.find(meshBase);
            if (cached != g_ChunkPayloadDirListingCache.end())
                return cached->second;

            std::vector<std::string> stems;
            for (const std::filesystem::path& resourceRoot : GetChunkPayloadResourceDirectories())
            {
                std::error_code error;
                for (std::filesystem::directory_iterator it(resourceRoot / meshBase, error);
                     !error && it != std::filesystem::directory_iterator();
                     it.increment(error))
                {
                    const auto& entry = *it;
                    if (!entry.is_regular_file(error) || error)
                        continue;

                    std::string extension = entry.path().extension().string();
                    std::transform(
                        extension.begin(),
                        extension.end(),
                        extension.begin(),
                        [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
                    if (extension != ".mesh")
                        continue;

                    stems.emplace_back(NormalizeChunkPayloadComponentName(
                        entry.path().stem().string().c_str()));
                }
            }

            return g_ChunkPayloadDirListingCache.emplace(meshBase, std::move(stems)).first->second;
        }

        // A payload whose name matches this geo once punctuation is ignored.
        //
        // ablpad's Redux model names its first piece bone "alp11_bda" where the
        // simulation fragments "alp11bda" -- a stray underscore, and the only
        // instance of its kind across every stock model (ablpad and bblpad share
        // the bone). Scoped to the craft's own directory and requiring a unique
        // hit, exactly like the prefix translation below, so it cannot reach
        // across to another building or pick between ambiguous candidates.
        static const std::string* FindChunkPayloadByRelaxedGeomName(
            const std::string& meshBase,
            const std::string& geomBase)
        {
            const auto strip = [](const std::string& value) {
                std::string out;
                out.reserve(value.size());
                for (const char ch : value)
                {
                    if (std::isalnum(static_cast<unsigned char>(ch)))
                        out.push_back(ch);
                }
                return out;
            };

            // The punctuation is on the payload side, not in the name the
            // simulation asks for, so do not gate on geomBase being dirty.
            const std::string wanted = strip(geomBase);
            if (wanted.empty())
                return nullptr;

            const std::string* match = nullptr;
            for (const std::string& stem : GetChunkPayloadDirListing(meshBase))
            {
                if (stem == geomBase || strip(stem) != wanted)
                    continue;

                if (match)
                    return nullptr;
                match = &stem;
            }

            return match;
        }

        // A payload whose name is this geo's with a different three-character
        // prefix -- same length, same tail -- and only when exactly one file in
        // the craft's own directory qualifies.
        static const std::string* FindChunkPayloadByGeomSuffix(
            const std::string& meshBase,
            const std::string& geomBase)
        {
            const std::vector<std::string>& stems = GetChunkPayloadDirListing(meshBase);

            const std::string* match = nullptr;
            for (const std::string& stem : stems)
            {
                if (stem.size() != geomBase.size())
                    continue;
                if (stem.compare(3, std::string::npos, geomBase, 3, std::string::npos) != 0)
                    continue;
                if (stem.compare(0, 3, geomBase, 0, 3) == 0)
                    continue;

                if (match)
                    return nullptr;
                match = &stem;
            }

            return match;
        }

        static bool TryResolveChunkPayloadMeshResourceForMeshAndGeom(
            const char* meshName,
            const char* geomName,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';
            const std::string meshBase = NormalizeChunkMeshBaseName(meshName);
            const std::string geomBase = NormalizeChunkPayloadComponentName(geomName);
            if (meshBase.empty() || geomBase.empty())
                return false;

            const std::string payloadFileName = geomBase + ".mesh";

            std::string nestedResourceName = meshBase;
            nestedResourceName += "/";
            nestedResourceName += payloadFileName;

            auto nestedCacheIt = g_ChunkPayloadMeshExistsCache.find(nestedResourceName);
            bool nestedExists = false;
            if (nestedCacheIt != g_ChunkPayloadMeshExistsCache.end())
            {
                nestedExists = nestedCacheIt->second;
            }
            else
            {
                for (const std::filesystem::path& resourceRoot : GetChunkPayloadResourceDirectories())
                {
                    const std::filesystem::path payloadPath = resourceRoot / meshBase / payloadFileName;
                    std::error_code error;
                    if (std::filesystem::exists(payloadPath, error) && !error)
                    {
                        nestedExists = true;
                        break;
                    }
                }
                g_ChunkPayloadMeshExistsCache.emplace(nestedResourceName, nestedExists);
            }

            if (nestedExists)
            {
                strncpy_s(outMeshName, outMeshNameCapacity, nestedResourceName.c_str(), _TRUNCATE);
                return outMeshName[0] != '\0';
            }

            // Some models name their bones "<craft>_<geo>" (sbsilo ships
            // sbsilo_sss11bda.mesh and friends), so the export carried the prefix
            // through. Cheap exact probe before the directory scan below.
            const std::string prefixedFileName = meshBase + "_" + payloadFileName;
            std::string prefixedResourceName = meshBase;
            prefixedResourceName += "/";
            prefixedResourceName += prefixedFileName;

            auto prefixedCacheIt = g_ChunkPayloadMeshExistsCache.find(prefixedResourceName);
            bool prefixedExists = false;
            if (prefixedCacheIt != g_ChunkPayloadMeshExistsCache.end())
            {
                prefixedExists = prefixedCacheIt->second;
            }
            else
            {
                for (const std::filesystem::path& resourceRoot : GetChunkPayloadResourceDirectories())
                {
                    const std::filesystem::path payloadPath = resourceRoot / meshBase / prefixedFileName;
                    std::error_code error;
                    if (std::filesystem::exists(payloadPath, error) && !error)
                    {
                        prefixedExists = true;
                        break;
                    }
                }
                g_ChunkPayloadMeshExistsCache.emplace(prefixedResourceName, prefixedExists);
            }

            if (prefixedExists)
            {
                strncpy_s(outMeshName, outMeshNameCapacity, prefixedResourceName.c_str(), _TRUNCATE);
                return outMeshName[0] != '\0';
            }

            // Punctuation-insensitive match inside the craft's own directory,
            // for models whose bone names carry a stray separator (ablpad's
            // alp11_bda against the simulation's alp11bda).
            if (const std::string* relaxed =
                    FindChunkPayloadByRelaxedGeomName(meshBase, geomBase))
            {
                std::string relaxedResourceName = meshBase;
                relaxedResourceName += "/";
                relaxedResourceName += *relaxed;
                relaxedResourceName += ".mesh";
                strncpy_s(
                    outMeshName, outMeshNameCapacity, relaxedResourceName.c_str(), _TRUNCATE);
                return outMeshName[0] != '\0';
            }

            // Two Black Dog buildings carry piece names in their Redux models
            // that differ from the names the simulation uses, in the first three
            // characters only: bbhang's sim geos are abh11* while its payloads
            // are bbh11*, and bbsilo runs the other way (bss11* -> ass11*). Every
            // other twin matches outright. Without this they resolve nothing and
            // every Black Dog hangar/silo chunk becomes a placeholder.
            //
            // Scoped to the already-resolved craft directory, so it can only ever
            // pick a piece of the right building with the right material -- it
            // cannot reach across to the NSDF twin. Requires a unique hit.
            if (geomBase.size() > 4)
            {
                if (const std::string* translated =
                        FindChunkPayloadByGeomSuffix(meshBase, geomBase))
                {
                    std::string translatedResourceName = meshBase;
                    translatedResourceName += "/";
                    translatedResourceName += *translated;
                    translatedResourceName += ".mesh";
                    strncpy_s(
                        outMeshName, outMeshNameCapacity, translatedResourceName.c_str(), _TRUNCATE);
                    return outMeshName[0] != '\0';
                }
            }

            auto flatCacheIt = g_ChunkPayloadMeshExistsCache.find(payloadFileName);
            bool flatExists = false;
            if (flatCacheIt != g_ChunkPayloadMeshExistsCache.end())
            {
                flatExists = flatCacheIt->second;
            }
            else
            {
                for (const std::filesystem::path& resourceRoot : GetChunkPayloadResourceDirectories())
                {
                    const std::filesystem::path payloadPath = resourceRoot / payloadFileName;
                    std::error_code error;
                    if (std::filesystem::exists(payloadPath, error) && !error)
                    {
                        flatExists = true;
                        break;
                    }
                }
                g_ChunkPayloadMeshExistsCache.emplace(payloadFileName, flatExists);
            }

            if (!flatExists)
                return false;

            strncpy_s(outMeshName, outMeshNameCapacity, payloadFileName.c_str(), _TRUNCATE);
            return outMeshName[0] != '\0';
        }

        static bool TryResolveGenericChunkPayloadFallback(
            const char* seedName,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';

            std::vector<std::string> available;
            for (uint32_t index = 1; index <= 8; ++index)
            {
                char geomBuffer[16] = {};
                _snprintf_s(geomBuffer, _TRUNCATE, "iechunk%u", index);
                char resourceName[128] = {};
                if (TryResolveChunkPayloadMeshResourceForMeshAndGeom(
                        "generic",
                        geomBuffer,
                        resourceName,
                        sizeof(resourceName)))
                {
                    available.emplace_back(resourceName);
                }
            }
            if (available.empty())
                return false;

            uint32_t hash = 2166136261u;
            for (const char* ch = seedName ? seedName : ""; *ch; ++ch)
            {
                hash ^= static_cast<uint8_t>(std::tolower(static_cast<unsigned char>(*ch)));
                hash *= 16777619u;
            }

            const std::string& pick = available[hash % available.size()];
            strncpy_s(outMeshName, outMeshNameCapacity, pick.c_str(), _TRUNCATE);
            return outMeshName[0] != '\0';
        }

        static bool TryResolveChunkPayloadMeshResource(
            const ChunkObjectLinkProbe& probe,
            const char* preferredMeshName,
            const char* explicitGeomName,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';

            std::vector<std::string> meshCandidates;
            meshCandidates.reserve(2);
            AppendUniqueChunkPayloadCandidate(meshCandidates, NormalizeChunkMeshBaseName(preferredMeshName));
            AppendUniqueChunkPayloadCandidate(meshCandidates, NormalizeChunkMeshBaseName(probe.cachedMeshName));

            // Identity caches only cover objects seen live before death; a
            // chunk that missed them (buildings especially) can still be
            // identified purely from its own geo name when the VDF/SDF
            // reverse index maps it to exactly one craft.
            if (meshCandidates.empty())
            {
                char inferredMeshName[48] = {};
                const char* inferGeomName =
                    (explicitGeomName && explicitGeomName[0]) ? explicitGeomName : probe.geomName;
                if (TryInferChunkMeshNameFromGeom(
                        inferGeomName,
                        probe.classId,
                        inferredMeshName,
                        sizeof(inferredMeshName)))
                {
                    AppendUniqueChunkPayloadCandidate(
                        meshCandidates, NormalizeChunkMeshBaseName(inferredMeshName));
                }
            }

            // The ODF name off the owning GameObject's class is the one piece of
            // craft identity the engine states outright rather than us inferring
            // it, so it settles faction twins the geo name cannot: an abhang and
            // a bbhang share every geo name but never share an ODF. It goes in
            // ahead of the try-every-twin sweep below and behind the identity
            // caches above, and like every candidate here it only wins if its
            // payload file actually exists -- an ODF whose model differs from its
            // own name (variant ODFs) simply misses and costs nothing.
            AppendUniqueChunkPayloadCandidate(
                meshCandidates, NormalizeChunkMeshBaseName(g_ActiveFragmentSourceOdfName));

            // Faction twins (abspow/bbspow, abtowe/bbtowe, ...) share their
            // entire piece list, so the single-craft inference above refuses
            // them. The lookup below is gated on the payload file actually
            // existing per candidate, and twin payload dirs ship the same
            // per-piece mesh files, so trying every craft the reverse index
            // maps this geo to still yields the correct piece.
            if (meshCandidates.empty())
            {
                const char* inferGeomName =
                    (explicitGeomName && explicitGeomName[0]) ? explicitGeomName : probe.geomName;
                AppendAllChunkMeshBasesForGeom(inferGeomName, probe.classId, meshCandidates);
            }

            // Last resort: some pieces were exported into a folder named after
            // the geo itself rather than the craft (apc11bda/apc11bda.mesh,
            // apm11bda/apm11bda.mesh) while the craft folder holds unrelated
            // exporter node names. Tried after every craft-scoped candidate so a
            // correct craft folder always wins.
            AppendUniqueChunkPayloadCandidate(
                meshCandidates, NormalizeChunkPayloadComponentName(explicitGeomName));
            AppendUniqueChunkPayloadCandidate(
                meshCandidates, NormalizeChunkPayloadComponentName(probe.geomName));

            std::vector<std::string> geomCandidates;
            geomCandidates.reserve(4);
            AppendUniqueChunkPayloadCandidate(geomCandidates, NormalizeChunkPayloadComponentName(explicitGeomName));
            AppendUniqueChunkPayloadCandidate(geomCandidates, NormalizeChunkPayloadComponentName(probe.geomName));
            // The VDF candidate list names OTHER pieces of the source craft.
            // Substituting one of those is only acceptable when the chunk's
            // own geo name could not be read at all — otherwise a resolve
            // miss (or a stale craft binding) turns into a visibly wrong
            // piece instead of an invisible chunk.
            if (geomCandidates.empty())
                AppendChunkPayloadCandidatesFromPipeList(probe.vdfCandidates, geomCandidates);

            for (const std::string& meshCandidate : meshCandidates)
            {
                for (const std::string& geomCandidate : geomCandidates)
                {
                    if (TryResolveChunkPayloadMeshResourceForMeshAndGeom(
                            meshCandidate.c_str(),
                            geomCandidate.c_str(),
                            outMeshName,
                            outMeshNameCapacity))
                    {
                        return true;
                    }
                }
            }

            // Generic chunklet templates ("chunk1", "chunk2", ...) have no craft
            // owner; map them onto the legacy iechunkN payload meshes when a
            // payload root ships them flat.
            for (const std::string& geomCandidate : geomCandidates)
            {
                if (geomCandidate.size() <= 5 ||
                    _strnicmp(geomCandidate.c_str(), "chunk", 5) != 0)
                {
                    continue;
                }

                bool digitsOnly = true;
                for (size_t index = 5; index < geomCandidate.size(); ++index)
                {
                    if (!std::isdigit(static_cast<unsigned char>(geomCandidate[index])))
                    {
                        digitsOnly = false;
                        break;
                    }
                }
                if (!digitsOnly)
                    continue;

                const std::string chunkletFileName = "ie" + geomCandidate + ".mesh";
                if (ChunkPayloadFlatMeshExists(chunkletFileName))
                {
                    strncpy_s(outMeshName, outMeshNameCapacity, chunkletFileName.c_str(), _TRUNCATE);
                    return true;
                }

                // Nested layouts for the same templates: chunkN/chunkN.mesh
                // and generic/iechunkN.mesh.
                if (TryResolveChunkPayloadMeshResourceForMeshAndGeom(
                        geomCandidate.c_str(),
                        geomCandidate.c_str(),
                        outMeshName,
                        outMeshNameCapacity))
                {
                    return true;
                }
                const std::string chunkletGeneric = "ie" + geomCandidate;
                if (TryResolveChunkPayloadMeshResourceForMeshAndGeom(
                        "generic",
                        chunkletGeneric.c_str(),
                        outMeshName,
                        outMeshNameCapacity))
                {
                    return true;
                }
            }

            // Last resort: a payload root can ship generic debris meshes in a
            // "generic" dir (generic/iechunkN.mesh). Seed the pick with the
            // geo name so a given piece always shatters into the same shape.
            if (TryResolveGenericChunkPayloadFallback(
                    geomCandidates.empty() ? nullptr : geomCandidates.front().c_str(),
                    outMeshName,
                    outMeshNameCapacity))
            {
                static volatile long s_GenericFallbackLogBudget = 64;
                if (InterlockedDecrement(&s_GenericFallbackLogBudget) >= 0)
                {
                    LogChunkDiagnostic(
                        "chunkmesh",
                        L"[CHUNKMESH] generic-fallback geom=%hs mesh=%hs\n",
                        geomCandidates.empty() ? "<none>" : geomCandidates.front().c_str(),
                        outMeshName);
                }
                return true;
            }

            LogChunkPayloadResolveFailureOnce(
                probe,
                preferredMeshName,
                explicitGeomName,
                meshCandidates,
                geomCandidates);
            return false;
        }

        // Manifest line format: craft|geoName|parentName|type|flags
        // ('#' comments and blank lines ignored; parent/type/flags optional).
        static void LoadChunkGeoManifestFile(
            const std::filesystem::path& manifestPath,
            uint32_t& craftCount,
            uint32_t& recordCount)
        {
            std::ifstream file(manifestPath);
            if (!file)
                return;

            std::string line;
            while (std::getline(file, line))
            {
                const std::string trimmed = TrimAsciiCopy(line);
                if (trimmed.empty() || trimmed[0] == '#')
                    continue;

                std::array<std::string, 5> fields = {};
                size_t fieldIndex = 0;
                size_t start = 0;
                while (fieldIndex < fields.size())
                {
                    const size_t separator = trimmed.find('|', start);
                    fields[fieldIndex++] =
                        TrimAsciiCopy(trimmed.substr(start, separator - start));
                    if (separator == std::string::npos)
                        break;
                    start = separator + 1;
                }

                const std::string craftBase = NormalizeChunkMeshBaseName(fields[0].c_str());
                const std::string& geoName = fields[1];
                if (craftBase.empty() || geoName.empty() ||
                    geoName.size() >= sizeof(ChunkVdfRecord{}.name) ||
                    _stricmp(geoName.c_str(), "NULL") == 0)
                {
                    continue;
                }

                ChunkVdfAssetInfo& info = g_ChunkVdfAssetCache[craftBase];
                if (!info.attempted)
                    ++craftCount;
                info.attempted = true;

                bool duplicate = false;
                for (const ChunkVdfRecord& existing : info.records)
                {
                    if (_stricmp(existing.name, geoName.c_str()) == 0 &&
                        _stricmp(existing.parent, fields[2].c_str()) == 0)
                    {
                        duplicate = true;
                        break;
                    }
                }
                if (duplicate)
                    continue;

                ChunkVdfRecord record = {};
                strncpy_s(record.name, sizeof(record.name), geoName.c_str(), _TRUNCATE);
                strncpy_s(record.parent, sizeof(record.parent), fields[2].c_str(), _TRUNCATE);
                record.type = static_cast<uint32_t>(std::strtoul(fields[3].c_str(), nullptr, 10));
                record.flags = static_cast<uint32_t>(std::strtoul(fields[4].c_str(), nullptr, 10));
                info.records.push_back(record);
                info.loaded = true;
                ++recordCount;
            }
        }

        static void EnsureChunkGeoManifestLoaded()
        {
            if (g_ChunkGeoManifestAttempted)
                return;

            g_ChunkGeoManifestAttempted = true;

            std::vector<std::filesystem::path> manifestCandidates;
            AppendUniquePath(
                manifestCandidates,
                GetMainModuleDirectory() / "scripts" / kChunkGeoManifestFileName);
            for (const std::filesystem::path& payloadDir : GetChunkPayloadResourceDirectories())
                AppendUniquePath(manifestCandidates, payloadDir / kChunkGeoManifestFileName);

            uint32_t fileCount = 0;
            uint32_t craftCount = 0;
            uint32_t recordCount = 0;
            for (const std::filesystem::path& candidate : manifestCandidates)
            {
                std::error_code error;
                if (!std::filesystem::exists(candidate, error) || error)
                    continue;

                ++fileCount;
                LoadChunkGeoManifestFile(candidate, craftCount, recordCount);
            }

            if (fileCount)
            {
                LogChunkDiagnostic(
                    "chunkmesh",
                    L"[CHUNKMESH] geo-manifest loaded files=%u crafts=%u records=%u\n",
                    fileCount,
                    craftCount,
                    recordCount);
            }
        }

        // Buildings ship as .sdf instead of .vdf: same BWD2 container, but the
        // geo table is an SGEO block (120-byte records vs VGEO's 100) whose
        // count field is authoritative — the block is padded with "NULL"
        // records to a fixed capacity.
        static bool TryLoadChunkSdfAssetInfo(
            const std::filesystem::path& sdfPath,
            ChunkVdfAssetInfo& info)
        {
            std::ifstream file(sdfPath, std::ios::binary);
            if (!file)
                return false;

            const std::vector<uint8_t> bytes(
                (std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
            constexpr size_t kSdfPreambleBytes = 20;
            constexpr size_t kSgeoHeaderBytes = 12;
            constexpr size_t kSgeoRecordBytes = 120;
            constexpr size_t kSgeoNameOffset = 0;
            constexpr size_t kSgeoParentOffset = 56;
            constexpr size_t kSgeoTypeOffset = 92;

            // Block sizes include the 8-byte tag+size header; walk until SGEO.
            size_t cursor = kSdfPreambleBytes;
            size_t sgeoOffset = 0;
            size_t sgeoSize = 0;
            while (cursor + 8 <= bytes.size())
            {
                const uint32_t blockSize = ReadLeU32(bytes.data() + cursor + 4);
                if (blockSize < 8 || cursor + blockSize > bytes.size())
                    break;

                if (std::memcmp(bytes.data() + cursor, "SGEO", 4) == 0)
                {
                    sgeoOffset = cursor;
                    sgeoSize = blockSize;
                    break;
                }
                cursor += blockSize;
            }

            if (!sgeoOffset || sgeoSize < kSgeoHeaderBytes + kSgeoRecordBytes)
                return false;

            const size_t recordCapacity = (sgeoSize - kSgeoHeaderBytes) / kSgeoRecordBytes;
            const uint32_t declaredCount = ReadLeU32(bytes.data() + sgeoOffset + 8);
            const size_t geoCount =
                (declaredCount < recordCapacity) ? declaredCount : recordCapacity;
            if (geoCount == 0)
                return false;

            const size_t recordsStart = sgeoOffset + kSgeoHeaderBytes;
            std::unordered_set<std::string> seenKeys;
            info.records.clear();
            info.records.reserve(geoCount);
            for (size_t index = 0; index < geoCount; ++index)
            {
                const size_t recordOffset = recordsStart + (index * kSgeoRecordBytes);
                const std::string name = ReadFixedAsciiField(bytes.data() + recordOffset + kSgeoNameOffset, 8);
                if (name.empty() || _stricmp(name.c_str(), "NULL") == 0)
                    continue;

                const std::string parent = ReadFixedAsciiField(bytes.data() + recordOffset + kSgeoParentOffset, 8);
                const std::string seenKey = name + "|" + parent;
                if (!seenKeys.insert(seenKey).second)
                    continue;

                ChunkVdfRecord record = {};
                strncpy_s(record.name, sizeof(record.name), name.c_str(), _TRUNCATE);
                strncpy_s(record.parent, sizeof(record.parent), parent.c_str(), _TRUNCATE);
                record.type = ReadLeU32(bytes.data() + recordOffset + kSgeoTypeOffset);
                info.records.push_back(record);
            }

            info.loaded = !info.records.empty();
            return info.loaded;
        }

        static ChunkVdfAssetInfo& GetChunkVdfAssetInfoForMesh(const char* meshName)
        {
            static ChunkVdfAssetInfo kEmptyInfo = {};

            const std::string baseName = NormalizeChunkMeshBaseName(meshName);
            if (baseName.empty())
                return kEmptyInfo;

            EnsureChunkGeoManifestLoaded();

            ChunkVdfAssetInfo& info = g_ChunkVdfAssetCache[baseName];
            if (info.attempted)
                return info;

            info.attempted = true;

            const std::filesystem::path stockDir = GetMainModuleDirectory() / "Edit" / "stock";
            const std::filesystem::path vdfPath = stockDir / (baseName + ".vdf");
            std::error_code error;
            if (!std::filesystem::exists(vdfPath, error) || error)
            {
                const std::filesystem::path sdfPath = stockDir / (baseName + ".sdf");
                std::error_code sdfError;
                if (std::filesystem::exists(sdfPath, sdfError) && !sdfError)
                    TryLoadChunkSdfAssetInfo(sdfPath, info);
                return info;
            }

            std::ifstream file(vdfPath, std::ios::binary);
            if (!file)
                return info;

            const std::vector<uint8_t> bytes(
                (std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
            constexpr size_t kVdfHeaderBytes = 20;
            constexpr size_t kVdfcHeaderBytes = 68;
            constexpr size_t kExitBytes = 8;
            constexpr size_t kVgeoHeaderBytes = 12;
            constexpr size_t kVgeoRecordBytes = 100;
            constexpr size_t kVgeoNameOffset = 0;
            constexpr size_t kVgeoParentOffset = 56;
            constexpr size_t kVgeoTypeOffset = 92;
            constexpr size_t kVgeoFlagsOffset = 96;

            if (bytes.size() < (kVdfHeaderBytes + kVdfcHeaderBytes + kExitBytes + kVgeoHeaderBytes))
                return info;

            size_t cursor = kVdfHeaderBytes + kVdfcHeaderBytes + kExitBytes;
            const int32_t geoCount = static_cast<int32_t>(ReadLeU32(bytes.data() + cursor + 8));
            cursor += kVgeoHeaderBytes;
            if (geoCount <= 0)
                return info;

            if (bytes.size() < cursor + (static_cast<size_t>(geoCount) * kVgeoRecordBytes))
                return info;

            std::unordered_set<std::string> seenKeys;
            info.records.clear();
            info.records.reserve(static_cast<size_t>(geoCount));
            for (int32_t index = 0; index < geoCount; ++index)
            {
                const size_t recordOffset = cursor + (static_cast<size_t>(index) * kVgeoRecordBytes);
                const std::string name = ReadFixedAsciiField(bytes.data() + recordOffset + kVgeoNameOffset, 8);
                if (name.empty() || _stricmp(name.c_str(), "NULL") == 0)
                    continue;

                const std::string parent = ReadFixedAsciiField(bytes.data() + recordOffset + kVgeoParentOffset, 8);
                const std::string seenKey = name + "|" + parent;
                if (!seenKeys.insert(seenKey).second)
                    continue;

                ChunkVdfRecord record = {};
                strncpy_s(record.name, sizeof(record.name), name.c_str(), _TRUNCATE);
                strncpy_s(record.parent, sizeof(record.parent), parent.c_str(), _TRUNCATE);
                record.type = ReadLeU32(bytes.data() + recordOffset + kVgeoTypeOffset);
                record.flags = ReadLeU32(bytes.data() + recordOffset + kVgeoFlagsOffset);
                info.records.push_back(record);
            }

            info.loaded = !info.records.empty();
            return info;
        }

        static void AddChunkVdfReverseIndexRecord(
            const std::string& geomName,
            const std::string& meshBase,
            uint32_t type)
        {
            if (geomName.empty() || meshBase.empty())
                return;

            std::string key = geomName;
            std::transform(
                key.begin(),
                key.end(),
                key.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

            auto& refs = g_ChunkVdfGeomReverseIndex[key];
            for (const ChunkVdfMeshRef& existing : refs)
            {
                if (_stricmp(existing.meshBase, meshBase.c_str()) == 0 && existing.type == type)
                    return;
            }

            ChunkVdfMeshRef ref = {};
            strncpy_s(ref.meshBase, sizeof(ref.meshBase), meshBase.c_str(), _TRUNCATE);
            ref.type = type;
            refs.push_back(ref);
        }

        static void EnsureChunkVdfReverseIndex()
        {
            if (g_ChunkVdfReverseIndexAttempted)
                return;

            g_ChunkVdfReverseIndexAttempted = true;

            EnsureChunkGeoManifestLoaded();
            for (const auto& [meshBase, info] : g_ChunkVdfAssetCache)
            {
                if (!info.loaded)
                    continue;
                for (const ChunkVdfRecord& record : info.records)
                {
                    if (record.name[0])
                        AddChunkVdfReverseIndexRecord(record.name, meshBase, record.type);
                }
            }

            const std::filesystem::path stockDir = GetMainModuleDirectory() / "Edit" / "stock";
            std::error_code error;
            if (!std::filesystem::exists(stockDir, error) || error)
                return;

            for (std::filesystem::directory_iterator it(stockDir, error);
                 !error && it != std::filesystem::directory_iterator();
                 it.increment(error))
            {
                const auto& entry = *it;
                if (!entry.is_regular_file(error) || error)
                    continue;

                std::string extension = entry.path().extension().string();
                std::transform(
                    extension.begin(),
                    extension.end(),
                    extension.begin(),
                    [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
                if (extension != ".vdf" && extension != ".sdf")
                    continue;

                const std::string meshBase = entry.path().stem().string();
                ChunkVdfAssetInfo& info = GetChunkVdfAssetInfoForMesh(meshBase.c_str());
                if (!info.loaded)
                    continue;

                for (const ChunkVdfRecord& record : info.records)
                {
                    if (!record.name[0])
                        continue;
                    AddChunkVdfReverseIndexRecord(record.name, meshBase, record.type);
                }
            }
        }

        static bool TryCopyChunkVdfExactName(
            const char* meshName,
            const char* geomName,
            uint32_t classId,
            char* outText,
            size_t outTextCapacity)
        {
            if (!outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';
            if (!meshName || !*meshName || !geomName || !*geomName)
                return false;

            ChunkVdfAssetInfo& info = GetChunkVdfAssetInfoForMesh(meshName);
            if (!info.loaded)
                return false;

            for (const ChunkVdfRecord& record : info.records)
            {
                if (!record.name[0] || _stricmp(record.name, geomName) != 0)
                    continue;
                if (classId != 0 && record.type != classId)
                    continue;

                strncpy_s(outText, outTextCapacity, record.name, _TRUNCATE);
                return outText[0] != '\0';
            }

            return false;
        }

        static bool BuildChunkVdfCandidateList(
            const char* meshName,
            uint32_t classId,
            char* outText,
            size_t outTextCapacity)
        {
            if (!outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';
            if (!meshName || !*meshName || classId == 0)
                return false;

            ChunkVdfAssetInfo& info = GetChunkVdfAssetInfoForMesh(meshName);
            if (!info.loaded)
                return false;

            bool wroteAny = false;
            for (const ChunkVdfRecord& record : info.records)
            {
                if (record.type != classId || !record.name[0])
                    continue;

                const size_t currentLength = std::strlen(outText);
                if (currentLength + (wroteAny ? 1 : 0) + std::strlen(record.name) + 1 >= outTextCapacity)
                    break;

                if (wroteAny)
                    strcat_s(outText, outTextCapacity, "|");
                strcat_s(outText, outTextCapacity, record.name);
                wroteAny = true;
            }

            return wroteAny;
        }

        static uint32_t FindChunkVdfRecordTypeByName(
            const ChunkVdfAssetInfo& info,
            const char* name)
        {
            if (!name || !*name)
                return 0;

            for (const ChunkVdfRecord& record : info.records)
            {
                if (record.name[0] && _stricmp(record.name, name) == 0)
                    return record.type;
            }

            return 0;
        }

        static bool ChunkVdfRecordHasSiblingType(
            const ChunkVdfAssetInfo& info,
            const ChunkVdfRecord& record,
            uint32_t siblingClassId)
        {
            if (siblingClassId == 0)
                return true;

            for (const ChunkVdfRecord& other : info.records)
            {
                if (&other == &record)
                    continue;
                if (other.type != siblingClassId)
                    continue;
                if (_stricmp(other.parent, record.parent) == 0)
                    return true;
            }

            return false;
        }

        static bool ChunkVdfRecordHasChildType(
            const ChunkVdfAssetInfo& info,
            const ChunkVdfRecord& record,
            uint32_t childClassId)
        {
            if (childClassId == 0)
                return true;

            for (const ChunkVdfRecord& other : info.records)
            {
                if (other.type != childClassId)
                    continue;
                if (_stricmp(other.parent, record.name) == 0)
                    return true;
            }

            return false;
        }

        static bool ChunkVdfRecordMatchesTree(
            const ChunkVdfAssetInfo& info,
            const ChunkVdfRecord& record,
            const ChunkObjectLinkProbe& source,
            const ChunkObjectLinkProbe& parent,
            const ChunkObjectLinkProbe& sibling,
            const ChunkObjectLinkProbe& child)
        {
            if (!record.name[0] || record.type != source.classId)
                return false;

            if (source.geomName[0] && _stricmp(source.geomName, record.name) != 0)
                return false;

            if (parent.objectBytes && parent.classId != 0)
            {
                if (parent.classId == 1)
                {
                    if (_stricmp(record.parent, "WORLD") != 0)
                        return false;
                }
                else
                {
                    if (!record.parent[0])
                        return false;

                    const uint32_t parentType = FindChunkVdfRecordTypeByName(info, record.parent);
                    if (parentType != parent.classId)
                        return false;

                    if (parent.geomName[0] && _stricmp(parent.geomName, record.parent) != 0)
                        return false;
                }
            }

            if (sibling.objectBytes && sibling.classId != 0)
            {
                if (!ChunkVdfRecordHasSiblingType(info, record, sibling.classId))
                    return false;
            }

            if (child.objectBytes && child.classId != 0)
            {
                if (!ChunkVdfRecordHasChildType(info, record, child.classId))
                    return false;
            }

            return true;
        }

        static bool BuildChunkVdfSourceCandidateList(
            const char* meshName,
            const ChunkObjectLinkProbe& source,
            const ChunkObjectLinkProbe& parent,
            const ChunkObjectLinkProbe& sibling,
            const ChunkObjectLinkProbe& child,
            char* outText,
            size_t outTextCapacity)
        {
            if (!outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';
            if (!meshName || !*meshName || !source.objectBytes || source.classId == 0)
                return false;

            ChunkVdfAssetInfo& info = GetChunkVdfAssetInfoForMesh(meshName);
            if (!info.loaded)
                return false;

            bool wroteAny = false;
            for (const ChunkVdfRecord& record : info.records)
            {
                if (!ChunkVdfRecordMatchesTree(info, record, source, parent, sibling, child))
                    continue;

                const size_t currentLength = std::strlen(outText);
                if (currentLength + (wroteAny ? 1 : 0) + std::strlen(record.name) + 1 >= outTextCapacity)
                    break;

                if (wroteAny)
                    strcat_s(outText, outTextCapacity, "|");
                strcat_s(outText, outTextCapacity, record.name);
                wroteAny = true;
            }

            return wroteAny;
        }

        static void PopulateChunkVdfCandidates(const char* meshName, ChunkObjectLinkProbe& probe)
        {
            probe.vdfCandidates[0] = '\0';
            if (!probe.objectBytes || !meshName || !*meshName)
                return;

            if (probe.geomName[0] &&
                TryCopyChunkVdfExactName(
                    meshName,
                    probe.geomName,
                    probe.classId,
                    probe.vdfCandidates,
                    sizeof(probe.vdfCandidates)))
            {
                return;
            }

            BuildChunkVdfCandidateList(meshName, probe.classId, probe.vdfCandidates, sizeof(probe.vdfCandidates));
        }

        static bool TryInferChunkMeshNameFromGeom(
            const char* geomName,
            uint32_t classId,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';
            if (!geomName || !*geomName)
                return false;
            if (_stricmp(geomName, "chunk1") == 0 || _stricmp(geomName, "chunk2") == 0)
                return false;

            EnsureChunkVdfReverseIndex();

            std::string key(geomName);
            std::transform(
                key.begin(),
                key.end(),
                key.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

            const auto it = g_ChunkVdfGeomReverseIndex.find(key);
            if (it == g_ChunkVdfGeomReverseIndex.end() || it->second.empty())
                return false;

            const ChunkVdfMeshRef* selected = nullptr;
            for (const ChunkVdfMeshRef& ref : it->second)
            {
                if (classId != 0 && ref.type != classId)
                    continue;

                if (!selected)
                {
                    selected = &ref;
                    continue;
                }

                if (_stricmp(selected->meshBase, ref.meshBase) != 0)
                    return false;
            }

            if (!selected)
            {
                for (const ChunkVdfMeshRef& ref : it->second)
                {
                    if (!selected)
                    {
                        selected = &ref;
                        continue;
                    }

                    if (_stricmp(selected->meshBase, ref.meshBase) != 0)
                        return false;
                }
            }

            if (!selected || !selected->meshBase[0])
                return false;

            _snprintf_s(outMeshName, outMeshNameCapacity, _TRUNCATE, "%s.mesh", selected->meshBase);
            return outMeshName[0] != '\0';
        }

        // Unlike TryInferChunkMeshNameFromGeom this does not refuse ambiguous
        // geo names; it hands back every craft the reverse index knows, in
        // stable alphabetical order, for callers that can verify candidates
        // against actual payload files.
        static void AppendAllChunkMeshBasesForGeom(
            const char* geomName,
            uint32_t classId,
            std::vector<std::string>& outMeshCandidates)
        {
            if (!geomName || !*geomName)
                return;
            if (_stricmp(geomName, "chunk1") == 0 || _stricmp(geomName, "chunk2") == 0)
                return;

            EnsureChunkVdfReverseIndex();

            std::string key(geomName);
            std::transform(
                key.begin(),
                key.end(),
                key.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

            const auto it = g_ChunkVdfGeomReverseIndex.find(key);
            if (it == g_ChunkVdfGeomReverseIndex.end() || it->second.empty())
                return;

            std::vector<std::string> bases;
            for (const ChunkVdfMeshRef& ref : it->second)
            {
                if (classId != 0 && ref.type != classId)
                    continue;
                if (ref.meshBase[0])
                    bases.emplace_back(ref.meshBase);
            }
            if (bases.empty())
            {
                for (const ChunkVdfMeshRef& ref : it->second)
                {
                    if (ref.meshBase[0])
                        bases.emplace_back(ref.meshBase);
                }
            }

            std::sort(
                bases.begin(),
                bases.end(),
                [](const std::string& left, const std::string& right)
                {
                    return _stricmp(left.c_str(), right.c_str()) < 0;
                });
            for (const std::string& base : bases)
                AppendUniqueChunkPayloadCandidate(outMeshCandidates, NormalizeChunkMeshBaseName(base.c_str()));
        }

        static bool ResolveChunkCreateMeshContext(
            const ChunkCreateSourceTreeProbe& probe,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';

            if (probe.ownerResolvedMeshName[0])
            {
                strncpy_s(outMeshName, outMeshNameCapacity, probe.ownerResolvedMeshName, _TRUNCATE);
                return true;
            }

            const ChunkObjectLinkProbe* links[] = {
                &probe.source,
                &probe.parent,
                &probe.sibling,
                &probe.child,
            };
            for (const ChunkObjectLinkProbe* link : links)
            {
                if (!link || !link->cachedMeshName[0])
                    continue;

                if (!outMeshName[0])
                {
                    strncpy_s(outMeshName, outMeshNameCapacity, link->cachedMeshName, _TRUNCATE);
                    continue;
                }

                if (_stricmp(outMeshName, link->cachedMeshName) != 0)
                {
                    outMeshName[0] = '\0';
                    break;
                }
            }
            if (outMeshName[0])
                return true;

            for (const ChunkObjectLinkProbe* link : links)
            {
                if (!link || !link->geomName[0])
                    continue;

                if (TryInferChunkMeshNameFromGeom(
                        link->geomName,
                        link->classId,
                        outMeshName,
                        outMeshNameCapacity))
                {
                    return true;
                }
            }

            if (TryInferChunkMeshNameFromTree(
                    probe.source,
                    probe.parent,
                    probe.sibling,
                    probe.child,
                    outMeshName,
                    outMeshNameCapacity))
            {
                return true;
            }

            return false;
        }

        static bool TryInferChunkMeshNameFromTree(
            const ChunkObjectLinkProbe& source,
            const ChunkObjectLinkProbe& parent,
            const ChunkObjectLinkProbe& sibling,
            const ChunkObjectLinkProbe& child,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';
            if (!source.objectBytes || source.classId == 0)
                return false;

            EnsureChunkVdfReverseIndex();

            std::string selectedMeshBase;
            for (const auto& pair : g_ChunkVdfAssetCache)
            {
                const std::string& meshBase = pair.first;
                const ChunkVdfAssetInfo& info = pair.second;
                if (!info.loaded)
                    continue;

                bool matchedMesh = false;
                for (const ChunkVdfRecord& record : info.records)
                {
                    if (ChunkVdfRecordMatchesTree(info, record, source, parent, sibling, child))
                    {
                        matchedMesh = true;
                        break;
                    }
                }

                if (!matchedMesh)
                    continue;

                if (selectedMeshBase.empty())
                {
                    selectedMeshBase = meshBase;
                    continue;
                }

                if (_stricmp(selectedMeshBase.c_str(), meshBase.c_str()) != 0)
                    return false;
            }

            if (selectedMeshBase.empty())
                return false;

            _snprintf_s(outMeshName, outMeshNameCapacity, _TRUNCATE, "%s.mesh", selectedMeshBase.c_str());
            return outMeshName[0] != '\0';
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
            if (!value)
                return false;

            char normalized[16] = {};
            size_t i = 0;
            for (const char* p = value; *p && i + 1 < sizeof(normalized); ++p)
            {
                if (std::isspace(static_cast<unsigned char>(*p)))
                    continue;

                normalized[i++] = static_cast<char>(
                    std::tolower(static_cast<unsigned char>(*p)));
            }
            normalized[i] = '\0';

            if (strcmp(normalized, "1") == 0 ||
                strcmp(normalized, "true") == 0 ||
                strcmp(normalized, "yes") == 0 ||
                strcmp(normalized, "on") == 0)
            {
                out = true;
                return true;
            }

            if (strcmp(normalized, "0") == 0 ||
                strcmp(normalized, "false") == 0 ||
                strcmp(normalized, "no") == 0 ||
                strcmp(normalized, "off") == 0)
            {
                out = false;
                return true;
            }

            return false;
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

        static bool TryReadChunkObjectLinks(
            const uint8_t* objectBytes,
            const uint8_t*& outParent,
            const uint8_t*& outSibling,
            const uint8_t*& outChild)
        {
            outParent = nullptr;
            outSibling = nullptr;
            outChild = nullptr;
            if (!objectBytes)
                return false;

            __try
            {
                outParent = *reinterpret_cast<const uint8_t* const*>(objectBytes + 0x78);
                outSibling = *reinterpret_cast<const uint8_t* const*>(objectBytes + 0x7C);
                outChild = *reinterpret_cast<const uint8_t* const*>(objectBytes + 0x80);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outParent = nullptr;
                outSibling = nullptr;
                outChild = nullptr;
                return false;
            }
        }

        bool TryGetGameObjectMeshName(void* gameObject, char* outMeshName, size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';
            if (!gameObject)
                return false;

            void* obj76 = nullptr;
            if (!TryGetGameObjectObj76(gameObject, obj76))
                return false;

            const ChunkBridgeSnapshot snapshot = CaptureChunkBridgeSnapshot(reinterpret_cast<const uint8_t*>(obj76));
            if (snapshot.ownerResolvedMeshName[0])
            {
                strncpy_s(outMeshName, outMeshNameCapacity, snapshot.ownerResolvedMeshName, _TRUNCATE);
                return true;
            }

            char entityBaseName[32] = {};
            char ogreFilename[32] = {};
            if (TryReadOwnerEntityNames(
                    gameObject,
                    entityBaseName,
                    sizeof(entityBaseName),
                    ogreFilename,
                    sizeof(ogreFilename),
                    outMeshName,
                    outMeshNameCapacity))
            {
                return outMeshName[0] != '\0';
            }

            return false;
        }

        static void CacheChunkObjectIdentityForNode(const uint8_t* objectBytes, const char* meshName)
        {
            if (!objectBytes || !meshName || !*meshName)
                return;

            ChunkObjectLinkProbe source = {};
            if (!CaptureChunkObjectLinkProbe(objectBytes, source))
                return;

            const uint8_t* parentBytes = nullptr;
            const uint8_t* siblingBytes = nullptr;
            const uint8_t* childBytes = nullptr;
            TryReadChunkObjectLinks(objectBytes, parentBytes, siblingBytes, childBytes);

            ChunkObjectLinkProbe parent = {};
            ChunkObjectLinkProbe sibling = {};
            ChunkObjectLinkProbe child = {};
            CaptureChunkObjectLinkProbe(parentBytes, parent);
            CaptureChunkObjectLinkProbe(siblingBytes, sibling);
            CaptureChunkObjectLinkProbe(childBytes, child);

            ChunkObjectIdentityCacheEntry entry = {};
            strncpy_s(entry.meshName, sizeof(entry.meshName), meshName, _TRUNCATE);
            if (source.geomName[0])
                strncpy_s(entry.geomName, sizeof(entry.geomName), source.geomName, _TRUNCATE);
            entry.classId = source.classId;
            if (!BuildChunkVdfSourceCandidateList(
                    meshName,
                    source,
                    parent,
                    sibling,
                    child,
                    entry.vdfCandidates,
                    sizeof(entry.vdfCandidates)))
            {
                PopulateChunkVdfCandidates(meshName, source);
                if (source.vdfCandidates[0])
                    strncpy_s(entry.vdfCandidates, sizeof(entry.vdfCandidates), source.vdfCandidates, _TRUNCATE);
            }

            g_ChunkObjectIdentityCache[reinterpret_cast<uintptr_t>(objectBytes)] = entry;
        }

        static void CacheChunkObjectIdentityTreeForGameObject(void* gameObject)
        {
            char meshName[48] = {};
            if (!TryGetGameObjectMeshName(gameObject, meshName, sizeof(meshName)))
                return;

            ChunkVdfAssetInfo& info = GetChunkVdfAssetInfoForMesh(meshName);
            if (!info.loaded)
                return;

            void* rootObj76 = nullptr;
            if (!TryGetGameObjectObj76(gameObject, rootObj76) || !rootObj76)
                return;

            std::vector<const uint8_t*> stack;
            stack.reserve(32);
            stack.push_back(reinterpret_cast<const uint8_t*>(rootObj76));
            std::unordered_set<uintptr_t> visited;
            visited.reserve(64);

            while (!stack.empty() && visited.size() < kChunkObjectIdentityMaxNodesPerObject)
            {
                const uint8_t* nodeBytes = stack.back();
                stack.pop_back();
                if (!nodeBytes)
                    continue;

                const uintptr_t nodeKey = reinterpret_cast<uintptr_t>(nodeBytes);
                if (!visited.insert(nodeKey).second)
                    continue;

                CacheChunkObjectIdentityForNode(nodeBytes, meshName);

                const uint8_t* parentBytes = nullptr;
                const uint8_t* siblingBytes = nullptr;
                const uint8_t* childBytes = nullptr;
                if (!TryReadChunkObjectLinks(nodeBytes, parentBytes, siblingBytes, childBytes))
                    continue;

                if (siblingBytes)
                    stack.push_back(siblingBytes);
                if (childBytes)
                    stack.push_back(childBytes);
            }
        }

        static void RefreshChunkObjectIdentityCacheIfNeeded()
        {
            if (!g_TraceChunkRender &&
                !g_TraceChunkEffectRuntime &&
                !g_EnableChunkProxyDebug &&
                !g_EnableChunkMeshProxy)
            {
                return;
            }

            const DWORD now = GetTickCount();
            if (g_ChunkObjectIdentityLastRefreshTick != 0 &&
                static_cast<DWORD>(now - g_ChunkObjectIdentityLastRefreshTick) < kChunkObjectIdentityRefreshMs)
            {
                return;
            }
            g_ChunkObjectIdentityLastRefreshTick = now;

            // NOTE: until 2026-07-18 this walked the stale advisory-PDB
            // object-list global, whose sanity checks always failed — so the
            // identity cache had silently stayed empty since it was written.
            // The arena walk makes it populate for the first time.
            static void* s_identityObjects[kGameObjectArenaSlotCapacity];
            const size_t totalObjects =
                CollectLiveGameObjectsFromArena(s_identityObjects, kGameObjectArenaSlotCapacity);
            if (totalObjects == 0)
                return;

            const size_t objectLimit =
                (totalObjects < kChunkObjectIdentityMaxObjectsPerRefresh)
                    ? totalObjects
                    : kChunkObjectIdentityMaxObjectsPerRefresh;

            g_ChunkObjectIdentityCache.clear();
            g_ChunkObjectIdentityCache.reserve(objectLimit * 8);
            for (size_t index = 0; index < objectLimit; ++index)
                CacheChunkObjectIdentityTreeForGameObject(s_identityObjects[index]);
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

        // Lobby screens route keyboard characters to their own stock chat
        // entries through cUI_TextEntry::AppendChar (0x007CFA70), but they do
        // not share one reliable screen-level OnChar target. Intercept the
        // common append operation instead. The detour is inert unless the
        // player explicitly activated our live nickname entry.
        static uint8_t __fastcall TextEntryAppendCharNicknameHook(
            void* thisPtr,
            void* /*unusedEdx*/,
            uint8_t character)
        {
            void* const entry = g_ActiveNicknameEntry;
            void* const parent = g_ActiveNicknameParent;
            if (entry && parent && g_BzrFn_TextEntryAppendChar &&
                IsWidgetLiveChildOfParent(parent, entry))
            {
                // A click means "replace" when a configured nickname is
                // already displayed. Keep it visible until the first actual
                // edit so clicking and pressing Enter remains a no-op update.
                if (g_ReplaceNicknameOnNextInput && character != '\r' && character != '\n')
                {
                    if (g_BzrFn_TextEntryClear)
                        g_BzrFn_TextEntryClear(entry);
                    g_ReplaceNicknameOnNextInput = false;
                }
                if (InterlockedDecrement(&g_NicknameInputTraceBudget) >= 0)
                    Log(L"[BZRNET] Nickname input routed (enter=%hs)\n",
                        (character == '\r' || character == '\n') ? "yes" : "no");
                const bool isEnter = (character == '\r' || character == '\n');
                if (isEnter)
                    g_NicknameEnterDispatchEntry = entry;
                const uint8_t result = g_BzrFn_TextEntryAppendCharOriginal
                    ? g_BzrFn_TextEntryAppendCharOriginal(entry, character)
                    : 0;
                if (isEnter)
                {
                    g_NicknameEnterDispatchEntry = nullptr;
                    // AppendChar rebuilds the rendered text after invoking its
                    // Enter callback. Paint confirmation only after it returns
                    // so the rebuild cannot immediately erase the message.
                    if (g_PendingNicknameConfirmationEntry == entry)
                    {
                        g_PendingNicknameConfirmationEntry = nullptr;
                        ShowNicknameApplyConfirmation(
                            entry, g_PendingNicknameConfirmationResult);
                    }
                }
                return result;
            }

            if (entry || parent)
            {
                // A rebuilt lobby invalidates injected children. Drop edit
                // mode before falling back so stale pointers receive no input.
                g_ActiveNicknameEntry = nullptr;
                g_ActiveNicknameParent = nullptr;
                g_NicknameEnterDispatchEntry = nullptr;
                g_ReplaceNicknameOnNextInput = false;
            }
            return g_BzrFn_TextEntryAppendCharOriginal
                ? g_BzrFn_TextEntryAppendCharOriginal(thisPtr, character)
                : 0;
        }

        static void InstallNicknameTextEntryInputHookIfPossible()
        {
            if (g_LobbyNicknameInputHookInstalled)
                return;

            constexpr uintptr_t kTextEntryAppendCharAddr = 0x007CFA70;
            // push ebp; mov ebp,esp; push -1 -- complete instructions only.
            static constexpr uint8_t kExpectedBytes[] =
            {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF
            };

            if (!InstallInlineDetour32(
                    g_TextEntryAppendCharDetour,
                    kTextEntryAppendCharAddr,
                    reinterpret_cast<void*>(TextEntryAppendCharNicknameHook),
                    sizeof(kExpectedBytes),
                    kExpectedBytes,
                    sizeof(kExpectedBytes)))
            {
                if (!g_LobbyNicknameInputHookFailureLogged)
                {
                    Log(L"[BZRNET] TextEntry AppendChar bytes mismatch at 0x%08X; nickname editing disabled\n",
                        static_cast<uint32_t>(kTextEntryAppendCharAddr));
                    g_LobbyNicknameInputHookFailureLogged = true;
                }
                return;
            }

            g_BzrFn_TextEntryAppendCharOriginal =
                reinterpret_cast<FnUiTextEntryAppendChar>(g_TextEntryAppendCharDetour.trampoline);
            g_LobbyNicknameInputHookInstalled =
                (g_BzrFn_TextEntryAppendCharOriginal != nullptr);
            if (g_LobbyNicknameInputHookInstalled)
                Log(L"[BZRNET] Installed TextEntry nickname input routing hook at 0x%08X\n",
                    static_cast<uint32_t>(kTextEntryAppendCharAddr));
        }

        // ---- Multiplayer create-screen "Map Layout" preview overflow fix ----
        //
        // cUI_Multiplayer_Create (ctor 0x00796880) builds the preview as a
        // 200x200 UI-unit image widget ("MapPreview", image ctor 0x007D1CC0),
        // but the first selection update rewrites the widget's design size to
        // the wire texture's pixel size (500x500), so the quad overflows the
        // "Map Layout" frame at every resolution. The quad geometry is built
        // only once (later texture changes just swap the Ogre material), so
        // the fix clamps the design size back to 200x200, re-runs the
        // engine's own layout pass, and rebuilds the quad using the same
        // beginUpdate/rebuild/end sequence the video-texture path uses
        // (0x7D3C92..0x7D3CEA). Driven from the screen's per-frame update
        // virtual (vftable 0x0089EBE0 slot 13, live-verified as the only
        // per-frame slot), so only this screen ever dispatches the hook.
        constexpr uintptr_t kMultiCreateUpdateVtblSlotAddr = 0x0089EC14;
        constexpr uintptr_t kMultiCreateUpdateFnAddr = 0x0079CDA0;
        constexpr uintptr_t kMultiMapComponentPtrAddr = 0x00945574;
        constexpr uintptr_t kUiImageWidgetVftableAddr = 0x008A0B94;
        constexpr uintptr_t kUiWidgetLayoutFnAddr = 0x007D14B0;
        constexpr uintptr_t kUiImageRebuildGeometryFnAddr = 0x007D2E20;
        constexpr float kMultiMapPreviewDesignSize = 200.0f;

        using FnScreenUpdate = void(__thiscall*)(void*);
        using FnWidgetLayout = void(__thiscall*)(void*, float, float, float, float);
        using FnImageRebuildGeometry = void(__thiscall*)(void*);
        using FnManualObjectBeginUpdate = void(__thiscall*)(void*, uint32_t);
        using FnManualObjectEnd = void(__thiscall*)(void*);

        static FnScreenUpdate g_BzrFn_MultiCreateUpdateOriginal = nullptr;
        static bool g_MultiCreatePreviewHookInstalled = false;
        static bool g_MultiCreatePreviewHookFailureLogged = false;
        static bool g_MultiCreatePreviewClampLogged = false;

        static bool ShouldEnableMapPreviewFix()
        {
            static int s_cached = -1;
            if (s_cached < 0)
            {
                s_cached =
                    (EnvFlagEnabled("OPENSHIM_DISABLE_MAP_PREVIEW_FIX") ||
                     EnvFlagEnabled("BZR_DISABLE_MAP_PREVIEW_FIX")) ? 0 : 1;
            }
            return s_cached != 0;
        }

        static void ClampMultiCreateMapPreviewIfNeeded()
        {
            __try
            {
                uint8_t* component = *reinterpret_cast<uint8_t**>(kMultiMapComponentPtrAddr);
                if (!component)
                    return;
                uint8_t* widget = *reinterpret_cast<uint8_t**>(component + 0x1C);
                if (!widget ||
                    *reinterpret_cast<uintptr_t*>(widget) != kUiImageWidgetVftableAddr)
                    return;

                float* designW = reinterpret_cast<float*>(widget + 0xF4);
                float* designH = reinterpret_cast<float*>(widget + 0xF8);
                if (*designW == kMultiMapPreviewDesignSize &&
                    *designH == kMultiMapPreviewDesignSize)
                    return;

                if (!g_MultiCreatePreviewClampLogged)
                {
                    g_MultiCreatePreviewClampLogged = true;
                    Log(L"[MAPPREVIEW] clamping oversized map preview design %.0fx%.0f -> %.0fx%.0f\n",
                        static_cast<double>(*designW),
                        static_cast<double>(*designH),
                        static_cast<double>(kMultiMapPreviewDesignSize),
                        static_cast<double>(kMultiMapPreviewDesignSize));
                }

                *designW = kMultiMapPreviewDesignSize;
                *designH = kMultiMapPreviewDesignSize;
                const float designX = *reinterpret_cast<float*>(widget + 0xEC);
                const float designY = *reinterpret_cast<float*>(widget + 0xF0);
                reinterpret_cast<FnWidgetLayout>(kUiWidgetLayoutFnAddr)(
                    widget,
                    designX,
                    designY,
                    kMultiMapPreviewDesignSize,
                    kMultiMapPreviewDesignSize);

                void* manualObject = *reinterpret_cast<void**>(widget + 0x120);
                if (manualObject)
                {
                    uintptr_t* vtbl = *reinterpret_cast<uintptr_t**>(manualObject);
                    reinterpret_cast<FnManualObjectBeginUpdate>(vtbl[0x118 / 4])(manualObject, 0);
                    reinterpret_cast<FnImageRebuildGeometry>(kUiImageRebuildGeometryFnAddr)(widget);
                    reinterpret_cast<FnManualObjectEnd>(vtbl[0x16C / 4])(manualObject);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                if (!g_MultiCreatePreviewHookFailureLogged)
                {
                    g_MultiCreatePreviewHookFailureLogged = true;
                    Log(L"[MAPPREVIEW] clamp faulted code=0x%08X; leaving preview untouched\n",
                        static_cast<uint32_t>(GetExceptionCode()));
                }
            }
        }

        static void __fastcall MultiCreateUpdateHook(void* screen, void* /*unusedEdx*/)
        {
            if (g_BzrFn_MultiCreateUpdateOriginal)
                g_BzrFn_MultiCreateUpdateOriginal(screen);
            if (ShouldEnableMapPreviewFix())
                ClampMultiCreateMapPreviewIfNeeded();
        }

        static void InstallMultiCreatePreviewFixIfPossible()
        {
            if (!ShouldEnableMapPreviewFix() || g_MultiCreatePreviewHookInstalled)
                return;

            __try
            {
                void* current = *reinterpret_cast<void**>(kMultiCreateUpdateVtblSlotAddr);
                if (current == reinterpret_cast<void*>(MultiCreateUpdateHook))
                {
                    g_MultiCreatePreviewHookInstalled = true;
                    return;
                }
                if (current != reinterpret_cast<void*>(kMultiCreateUpdateFnAddr))
                {
                    if (!g_MultiCreatePreviewHookFailureLogged)
                    {
                        Log(L"[MAPPREVIEW] update hook skipped: slot=0x%08X current=0x%08X expected=0x%08X\n",
                            static_cast<uint32_t>(kMultiCreateUpdateVtblSlotAddr),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                            static_cast<uint32_t>(kMultiCreateUpdateFnAddr));
                        g_MultiCreatePreviewHookFailureLogged = true;
                    }
                    return;
                }

                g_BzrFn_MultiCreateUpdateOriginal =
                    reinterpret_cast<FnScreenUpdate>(current);
                if (!WritePointerValue(
                        kMultiCreateUpdateVtblSlotAddr,
                        reinterpret_cast<void*>(MultiCreateUpdateHook)))
                {
                    return;
                }
                g_MultiCreatePreviewHookInstalled = true;
                Log(L"[MAPPREVIEW] Installed multi-create map preview fix slot=0x%08X original=0x%08X\n",
                    static_cast<uint32_t>(kMultiCreateUpdateVtblSlotAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                if (!g_MultiCreatePreviewHookFailureLogged)
                {
                    Log(L"[MAPPREVIEW] update hook install fault code=0x%08X\n",
                        static_cast<uint32_t>(GetExceptionCode()));
                    g_MultiCreatePreviewHookFailureLogged = true;
                }
            }
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
    // Accepts 1/0, true/false, on/off, yes/no, enabled/disabled (any case).
    bool TryGetUserConfigBool(const char* section, const char* key, bool& out)
    {
        std::string value;
        if (!TryGetUserConfigString(section, key, value))
            return false;
        for (char& c : value)
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        if (value == "1" || value == "true" || value == "on" ||
            value == "yes" || value == "enabled")
        {
            out = true;
            return true;
        }
        if (value == "0" || value == "false" || value == "off" ||
            value == "no" || value == "disabled")
        {
            out = false;
            return true;
        }
        return false;
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


    void ResolveBzrHooks(bool isSteam)
    {
        g_IsSteamExe = isSteam;
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

        g_BzrPtr_945478 = reinterpret_cast<void**>(0x00945478);
        g_BzrPtr_94548C = reinterpret_cast<void**>(0x0094548C);
        g_BzrPtr_94555C = reinterpret_cast<void**>(0x0094555C);
        g_BzrPtr_9456D0 = reinterpret_cast<void**>(0x009456D0);
        g_BzrPtr_94557C = reinterpret_cast<void**>(0x0094557C);
        g_BzrPtr_920168 = reinterpret_cast<void**>(0x00920168);
        g_BzrPtr_CurrentUser = reinterpret_cast<uint8_t*>(0x009C8F60);

        g_BzrFn_VehicleListSet = reinterpret_cast<FnVehicleListSet>(0x0076B7A0);
        g_BzrFn_VehicleListFinalize = reinterpret_cast<FnVehicleListFinalize>(0x0076BA00);
        g_BzrFn_VehicleListLoad = reinterpret_cast<FnVehicleListLoad>(0x00766900);
        g_BzrFn_VehicleListRefresh1 = reinterpret_cast<FnVehicleListStep>(0x007A3F80);
        g_BzrFn_VehicleListRefresh2 = reinterpret_cast<FnVehicleListStep>(0x007A4070);

        g_BzrFn_ButtonCtor = reinterpret_cast<FnUiButtonCtor>(0x007C2480);
        g_BzrFn_LabelCtor  = reinterpret_cast<FnUiLabelCtor>(0x007CC390);
        g_BzrFn_OverlayCtor = reinterpret_cast<FnUiOverlayCtor>(kGogUiOverlayCtorAddr);
        g_BzrFn_TextEntryCtor = reinterpret_cast<FnUiTextEntryCtor>(0x007CF410);
        g_BzrFn_SelectlistCtor = reinterpret_cast<FnUiSelectlistCtor>(0x007C9DE0);
        g_BzrFn_SelectlistSetItem = reinterpret_cast<FnUiSelectlistSetItem>(0x007CABF0);
        g_BzrFn_TextEntrySetEnterCb = reinterpret_cast<FnUiSetCb>(0x007CF940);
        g_BzrFn_TextEntryAppendText = reinterpret_cast<FnUiSetStr>(0x007CF980);
        g_BzrFn_TextEntryAppendChar = reinterpret_cast<FnUiTextEntryAppendChar>(0x007CFA70);
        g_BzrFn_TextEntryClear = reinterpret_cast<FnUiTextEntryClear>(0x007CF9F0);
        g_BzrFn_TextEntrySetInputLimit =
            reinterpret_cast<void (__thiscall*)(void*, int)>(0x00795BD0);
        g_BzrFn_SelectlistSetOnSelect = reinterpret_cast<FnUiSetCb>(0x007CB3E0);
        g_BzrFn_SetTextureOff = reinterpret_cast<FnUiSetStr>(0x007D2870);
        g_BzrFn_SetTextureOver = reinterpret_cast<FnUiSetStr>(0x007C2F10);
        g_BzrFn_SetTextureOn = reinterpret_cast<FnUiSetStr>(0x007C2E80);
        g_BzrFn_SetButtonLabel = reinterpret_cast<FnUiSetStr>(0x007C2950);
        g_BzrFn_SetButtonTextScale = reinterpret_cast<FnUiSetFloat>(0x007C30E0);
        g_BzrFn_SetTooltip = reinterpret_cast<FnUiSetStr>(0x007CC660);
        g_BzrFn_LabelState = reinterpret_cast<FnUiSetInt>(0x007CC5C0);
        g_BzrFn_SetOnClick = reinterpret_cast<FnUiSetCb>(0x007C23E0);
        g_BzrFn_SetOnHover = reinterpret_cast<FnUiSetCb>(0x007C23C0);
        g_BzrFn_UiSetActive = reinterpret_cast<FnUiSetActive>(0x007D3310);
        g_BzrFn_AddChild = reinterpret_cast<FnUiAddChild>(0x007D2110);
        g_BzrFn_UiDialogSetEnabled = reinterpret_cast<FnUiDialogAction>(0x007C9170);
        g_BzrFn_UiDialogAdvance = reinterpret_cast<FnUiDialogAction>(
            HookEngine::ResolveNamedAddress("ShellRequest")); // the same site ui_performance_hooks resolves
        g_BzrFn_KeyConfigSetKey = reinterpret_cast<FnKeyConfigSetKey>(kGogKeyConfigSetKeyAddr);
        g_BzrFn_WriteInputMapKey = reinterpret_cast<FnWriteInputMapKey>(kGogWriteInputMapKeyAddr);
        g_BzrFn_MapKeyNameFromCode = reinterpret_cast<FnMapKeyNameFromCode>(kGogMapKeyNameFromCodeAddr);
        g_BzrFn_ReloadGameKeyMap = reinterpret_cast<FnReloadGameKeyMap>(kGogReloadGameKeyMapAddr);

        g_BzrFn_GetSelected = reinterpret_cast<FnGetSelected>(0x007CB1A0);
        g_BzrFn_CommandHandler = reinterpret_cast<FnCommandHandler>(0x006247A0);
        g_BzrFn_HelpLog = reinterpret_cast<FnHelpLog>(0x00821390);
        g_BzrFn_HelpUi = reinterpret_cast<FnHelpUi>(0x007A47B0);
        g_BzrFn_BanLookup = reinterpret_cast<FnBanLookup>(0x005771B0);
        g_BzrFn_IsHost = reinterpret_cast<FnIsHost>(0x00572A60);
        g_BzrFn_AutoLoadShellGame = reinterpret_cast<FnAutoLoadShellGame>(0x004FDAB0);
        g_BzrFn_LoadGameByPath = reinterpret_cast<FnLoadGameByPath>(0x004FDFE0);
        g_BzrFn_LoadScreenPrep = reinterpret_cast<FnLoadScreenPrep>(0x0078BB00);
        g_BzrFn_FinalizeQueuedLoad = reinterpret_cast<FnFinalizeQueuedLoad>(0x005D4980);
        g_BzrFn_SetShellState = reinterpret_cast<FnSetShellState>(0x00434170);
        g_BzrFn_BzrStringCtorFromCStr = reinterpret_cast<FnBzrStringCtorFromCStr>(0x00416EF0);
        g_BzrFn_BzrStringDtor = reinterpret_cast<FnBzrStringDtor>(0x00416F30);
        g_BzrFn_LoadScreenClearSelection = reinterpret_cast<FnLoadScreenClearSelection>(0x00482860);
        g_BzrFn_MapFilter6 = reinterpret_cast<FnMapFilter6>(0x004200B0);
        g_BzrFn_ChunkResolve = reinterpret_cast<FnChunkResolve>(0x004E3620);

        g_BzrFn_MapFilter8Check = reinterpret_cast<void*>(0x007D3360);
        g_BzrFn_MapFilterCreate = reinterpret_cast<void*>(0x007C9DE0);
        g_BzrFn_MapFilterScrollUp = reinterpret_cast<FnMapFilterScroll>(0x007CB500);
        g_BzrFn_MapFilterScrollDown = reinterpret_cast<FnMapFilterScroll>(0x007CB540);
        g_BzrFn_Localize = reinterpret_cast<const char* (__cdecl*)(const char*, const char*)>(0x0081CB40);

        g_BzrFn_VehicleFixPre = reinterpret_cast<void*>(0x00481EA0);
        g_BzrFn_VehicleFixOrig = reinterpret_cast<void*>(0x00481AF0);
        // The live Redux runtime maps these multiplayer flag helpers at the
        // same settled addresses on current GOG and Steam builds.
        g_BzrFn_GetLocalPlayerNetId = reinterpret_cast<FnGetLocalPlayerNetId>(
            HookEngine::ResolveNamedAddress("GetLocalPlayerNetId"));
        g_BzrFn_NetPlayerSetData = reinterpret_cast<FnNetPlayerSetData>(0x00575570);
        g_BzrFn_NetPlayerSetFlagBuffer = reinterpret_cast<FnNetPlayerSetFlagBuffer>(0x00575810);
        g_BzrFn_SetMyFlag = reinterpret_cast<FnSetMyFlag>(0x0056FA50);
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
        g_BzrFn_EngineFlameControl = reinterpret_cast<FnEngineFlameControl>(0x004C88A0);
        g_BzrFn_EngineFlameSubmit = reinterpret_cast<FnEngineFlameSubmit>(0x004C88C0);
        // One function in two roles; resolve once and share it.
        const uint32_t resolveTexture =
            HookEngine::ResolveNamedAddress("EngineFlame::ResolveTexture");
        g_BzrFn_EngineFlameResolveTexture =
            reinterpret_cast<FnEngineFlameResolveTexture>(resolveTexture);
        g_BzrFn_HudSpriteLookup = reinterpret_cast<FnHudSpriteLookup>(resolveTexture);
        g_BzrFn_GetTeamNum = reinterpret_cast<FnGetTeamNum>(
            HookEngine::ResolveNamedAddress("GetTeamNum"));
        g_BzrFn_ChunkEffectSimulate = reinterpret_cast<FnChunkEffectSimulate>(0x004917F0);
        g_DynamicAlphaDepthBatchingEnabled =
            !(EnvFlagEnabled("OPENSHIM_DISABLE_DYNAMIC_ALPHA_BATCHING") ||
              EnvFlagEnabled("BZR_DISABLE_DYNAMIC_ALPHA_BATCHING"));
        long dynamicAlphaDepthStride =
            static_cast<long>(g_DynamicAlphaDepthBucketStride);
        if (TryGetEnvLong(
                "OPENSHIM_DYNAMIC_ALPHA_DEPTH_BUCKET_STRIDE",
                dynamicAlphaDepthStride))
        {
            if (dynamicAlphaDepthStride < 1)
                dynamicAlphaDepthStride = 1;
            if (dynamicAlphaDepthStride > 32)
                dynamicAlphaDepthStride = 32;
            g_DynamicAlphaDepthBucketStride =
                static_cast<uint32_t>(dynamicAlphaDepthStride);
            if (g_DynamicAlphaDepthBucketStride <= 1)
                g_DynamicAlphaDepthBatchingEnabled = false;
        }
        if (!g_IsSteamExe && g_DynamicAlphaDepthBatchingEnabled)
        {
            static const uint8_t kDynamicGeometryDepthPrologue[] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08
            };
            if (InstallInlineDetour32(
                    g_DynamicGeometrySetSquaredViewDepthDetour,
                    0x0067A780,
                    reinterpret_cast<void*>(
                        &DynamicGeometrySetSquaredViewDepthHook),
                    sizeof(kDynamicGeometryDepthPrologue),
                    kDynamicGeometryDepthPrologue,
                    sizeof(kDynamicGeometryDepthPrologue)))
            {
                g_BzrFn_DynamicGeometrySetSquaredViewDepth =
                    reinterpret_cast<FnDynamicGeometrySetSquaredViewDepth>(
                        g_DynamicGeometrySetSquaredViewDepthDetour.trampoline);
                LogShimA(
                    LogLevel::Info,
                    "render",
                    "Dynamic alpha batching installed target=0x0067A780 stride=%u optOut=OPENSHIM_DISABLE_DYNAMIC_ALPHA_BATCHING",
                    g_DynamicAlphaDepthBucketStride);
            }
            else
            {
                g_DynamicAlphaDepthBatchingEnabled = false;
                LogShimA(
                    LogLevel::Warn,
                    "render",
                    "Dynamic alpha batching unavailable: GOG depth-key prologue mismatch");
            }
        }
        if (!g_IsSteamExe && IsOgreAnimationProfilerCollecting())
        {
            static const uint8_t kDynamicGeometryPreparePrologue[] =
            {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF
            };
            if (InstallInlineDetour32(
                    g_DynamicGeometryPrepareDetour,
                    0x00678CD0,
                    reinterpret_cast<void*>(&DynamicGeometryPrepareHook),
                    sizeof(kDynamicGeometryPreparePrologue),
                    kDynamicGeometryPreparePrologue,
                    sizeof(kDynamicGeometryPreparePrologue)))
            {
                g_BzrFn_DynamicGeometryPrepare =
                    reinterpret_cast<FnDynamicGeometryPrepare>(
                        g_DynamicGeometryPrepareDetour.trampoline);
                LogShimA(
                    LogLevel::Info,
                    "ogre-profile",
                    "[OgreProfile] installed GOG DynamicGeometry::prepareForSubmit observer target=0x00678CD0 trampoline=0x%p",
                    g_DynamicGeometryPrepareDetour.trampoline);
            }
            else
            {
                LogShimA(
                    LogLevel::Warn,
                    "ogre-profile",
                    "[OgreProfile] GOG DynamicGeometry::prepareForSubmit prologue mismatch; native rebuild attribution unavailable");
            }

            constexpr uintptr_t kRenderQueueAddRenderableIatSlot = 0x00869B64;
            void* const currentAddRenderable =
                *reinterpret_cast<void**>(kRenderQueueAddRenderableIatSlot);
            if (currentAddRenderable ==
                reinterpret_cast<void*>(&DynamicGeometryAddRenderableHook))
            {
                // A repeated resolver pass keeps the original captured below.
            }
            else if (currentAddRenderable)
            {
                MEMORY_BASIC_INFORMATION targetInfo{};
                const bool executableTarget =
                    VirtualQuery(
                        currentAddRenderable, &targetInfo, sizeof(targetInfo)) ==
                        sizeof(targetInfo) &&
                    targetInfo.State == MEM_COMMIT &&
                    targetInfo.Type == MEM_IMAGE &&
                    (targetInfo.Protect & (PAGE_GUARD | PAGE_NOACCESS)) == 0 &&
                    ((targetInfo.Protect & 0xFFu) == PAGE_EXECUTE ||
                     (targetInfo.Protect & 0xFFu) == PAGE_EXECUTE_READ ||
                     (targetInfo.Protect & 0xFFu) == PAGE_EXECUTE_READWRITE ||
                     (targetInfo.Protect & 0xFFu) == PAGE_EXECUTE_WRITECOPY);
                if (executableTarget)
                {
                    g_BzrFn_RenderQueueAddRenderable =
                        reinterpret_cast<FnRenderQueueAddRenderable>(currentAddRenderable);
                    if (!WritePointerValue(
                            kRenderQueueAddRenderableIatSlot,
                            reinterpret_cast<void*>(&DynamicGeometryAddRenderableHook)))
                    {
                        g_BzrFn_RenderQueueAddRenderable = nullptr;
                    }
                }
            }
            if (g_BzrFn_RenderQueueAddRenderable)
            {
                LogShimA(
                    LogLevel::Info,
                    "ogre-profile",
                    "[OgreProfile] installed DynamicGeometry addRenderable batch counter IAT=0x00869B64 original=0x%p",
                    reinterpret_cast<void*>(g_BzrFn_RenderQueueAddRenderable));
            }
            else
            {
                LogShimA(
                    LogLevel::Warn,
                    "ogre-profile",
                    "[OgreProfile] DynamicGeometry addRenderable batch counter unavailable");
            }
        }
        // FUN_00679570: _updateRenderQueue override of the game's world
        // renderable container — the only exe-side caller of
        // Ogre::RenderQueue::addRenderable. Vtable slot 0x00892728.
        g_BzrFn_LegacyWorldUpdateRenderQueue = reinterpret_cast<FnLegacyWorldUpdateRenderQueue>(0x00679570);
        g_BzrFn_AIBuildConstructionEnd =
            reinterpret_cast<FnAIBuildConstructionEnd>(kGogAIBuildConstructionEndAddr);
        g_BzrFn_AIBuildReservedAreaRemove =
            reinterpret_cast<FnAIBuildReservedAreaRemove>(kGogAIBuildReservedAreaRemoveAddr);
        g_BzrFn_AISpentCreditRefund =
            reinterpret_cast<FnAISpentCreditRefund>(kGogAISpentCreditRefundAddr);
        g_BzrFn_UnitsSOrderStop =
            reinterpret_cast<FnUnitsSOrderStop>(kGogUnitsSOrderStopAddr);
        g_BzrFn_AIBuildUnassignedCCAdd =
            reinterpret_cast<FnAIBuildUnassignedCCAdd>(kGogAIBuildUnassignedCCAddAddr);

        g_BzrFn_InitBuildItem = reinterpret_cast<FnBuildItemInit>(0x0049F5C0);
        g_BzrFn_CleanupBuildItem = reinterpret_cast<FnBuildItemCleanup>(0x0049F880);
        g_BzrBuildMenuRoot = reinterpret_cast<BuildItem*>(kBuildMenuRootAddr);

        InstallJumpSnipingProbeIfRequested();
        InstallCareerStatsMpHookIfPossible();
        InstallUnitVoQueueHooksIfPossible();
        InstallParticleTemplateDedupeHookIfPossible();
        InstallUiManualObjectDedupeHookIfPossible();
        InstallSceneTeardownForgetHooksIfPossible();
        // InstallEntityFrustumCullingIfEnabled runs further down, once its
        // two switches have been read; here it saw both false and did nothing.
        InstallMissionTransitionSeamIfPossible();
        PinDirect3DModulesForShutdown();
        InstallMultiplayerFlagRenderHookIfPossible();
        InstallNicknameTextEntryInputHookIfPossible();
        StartCareerStatsMpSessionWorker();
        InstallShieldTowerTeamFilterHookIfPossible();
        InstallMineTeamFilterHooksIfPossible();
        g_MagnetZeroRangeGuardEnabled =
            !(EnvFlagEnabled("OPENSHIM_DISABLE_MAGNET_ZERO_RANGE_FIX") ||
              EnvFlagEnabled("BZR_DISABLE_MAGNET_ZERO_RANGE_FIX"));
		g_BriefingScrollFixEnabled =
			!(EnvFlagEnabled("OPENSHIM_DISABLE_BRIEFING_SCROLL_FIX") ||
			  EnvFlagEnabled("BZR_DISABLE_BRIEFING_SCROLL_FIX"));
		g_MultiRenderCountClampEnabled =
			!(EnvFlagEnabled("OPENSHIM_DISABLE_RENDERCOUNT_CLAMP") ||
			  EnvFlagEnabled("BZR_DISABLE_RENDERCOUNT_CLAMP"));
		g_ThumbnailBmpGuardEnabled =
			!(EnvFlagEnabled("OPENSHIM_DISABLE_BMP_GUARD") ||
			  EnvFlagEnabled("BZR_DISABLE_BMP_GUARD"));
		g_ProducerScriptPredicateHooksEnabled =
			!(EnvFlagEnabled("OPENSHIM_DISABLE_PRODUCER_SCRIPT_PREDICATES") ||
			  EnvFlagEnabled("BZR_DISABLE_PRODUCER_SCRIPT_PREDICATES"));
		g_TugCargoPostLoadFixEnabled =
			!(EnvFlagEnabled("OPENSHIM_DISABLE_TUG_CARGO_FIX") ||
			  EnvFlagEnabled("BZR_DISABLE_TUG_CARGO_FIX"));
		RefreshTugCargoPostLoadFixState();
		g_ConstructorRecycleStaleTargetFixEnabled =
			!(EnvFlagEnabled("OPENSHIM_DISABLE_CONSTRUCTOR_RECYCLE_FIX") ||
			  EnvFlagEnabled("BZR_DISABLE_CONSTRUCTOR_RECYCLE_FIX"));
		RefreshConstructorRecycleStaleTargetFixState();
		g_ApcAlliedTargetDeployFixEnabled =
			!(EnvFlagEnabled("OPENSHIM_DISABLE_APC_DEPLOY_FIX") ||
			  EnvFlagEnabled("BZR_DISABLE_APC_DEPLOY_FIX"));
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
		g_QuakeReplayFadeEnabled =
			!(EnvFlagEnabled("OPENSHIM_DISABLE_QUAKE_FADE") ||
			  EnvFlagEnabled("BZR_DISABLE_QUAKE_FADE"));
		g_TargetCamSatelliteFixEnabled =
			!(EnvFlagEnabled("OPENSHIM_DISABLE_TARGETCAM_FIX") ||
			  EnvFlagEnabled("BZR_DISABLE_TARGETCAM_FIX"));
		g_CinematicSatelliteZoomFixEnabled =
			!(EnvFlagEnabled("OPENSHIM_DISABLE_CINECAM_FIX") ||
			  EnvFlagEnabled("BZR_DISABLE_CINECAM_FIX"));
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
		InstallProducerScriptPredicateHooksIfPossible();
		InstallBriefingScrollFixIfPossible();
		InstallMultiRenderCountClampIfPossible();
		InstallThumbnailBmpGuardIfPossible();
		InstallSplinterUndeadFixIfPossible();
		InstallMpauthHooksIfPossible();
		InstallTugCargoPostLoadFixIfPossible();
		InstallConstructorRecycleStaleTargetFixIfPossible();
		InstallApcAlliedTargetDeployFixIfPossible();
		InstallQuakeReplayFadeIfPossible();
		InstallTargetCamSatelliteFixIfPossible();
		InstallCinematicSatelliteZoomFixIfPossible();

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
        // Restores the per-object frustum test that Redux's DefaultSceneManager
        // never performs. Measured: 20 tanks 50 m behind the camera cost exactly
        // as many main-view submissions as 20 tanks in front of it.
        g_EntityFrustumCullEnabled =
            !(EnvFlagEnabled("OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING") ||
              EnvFlagEnabled("BZR_DISABLE_ENTITY_FRUSTUM_CULLING"));
        g_FrustumCullCensusEnabled =
            EnvFlagEnabled("OPENSHIM_FRUSTUM_CULL_CENSUS") ||
            EnvFlagEnabled("BZR_FRUSTUM_CULL_CENSUS");

        // Second, independent repair experiment: restore finite Ogre bounds on
        // the shared craft meshes instead of emulating the frustum test
        // privately. Opt-in, and it stands the private cull down by default so
        // the two mechanisms are never measured on top of each other. Set
        // OPENSHIM_FRUSTUM_CULL_WITH_RESTORE=1 to run both deliberately.
        g_RestoreCraftBoundsEnabled =
            EnvFlagEnabled("OPENSHIM_RESTORE_CRAFT_BOUNDS") ||
            EnvFlagEnabled("BZR_RESTORE_CRAFT_BOUNDS");
        g_BoundsTraceEnabled =
            EnvFlagEnabled("OPENSHIM_BOUNDS_TRACE") ||
            EnvFlagEnabled("BZR_BOUNDS_TRACE");
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
        InitializeUnderAttackAlertConfig();
        InitializeTargetReticlePopupConfig();
        InitializeGlobalTurboConfig();
        InitializeHeadlightConfig();
        InitializePilotFlashlightConfig();
        InstallEmissionLightFixIfPossible();
        VerifyExpectedOgreExportsIfPossible();
        InitializeJetFlamesConfig();
        InitializeUnitVoConfig();
        // Must run before the game reaches BZRNet init: the requested UDP port
        // is only honoured while the P2P socket is still closed.
        InitializeBzrNetConfig();
        InstallBzrNetRouteObserverIfPossible();
        EnsureInputBindingPopulateHookScaffold();
        EnsureOptionsParentCtorHookScaffold();
        EnsureNativeUiMainMenuDiagnosticScaffold();
        LogShimSettingsUiStatus();
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

    uint32_t __cdecl ChunkRenderResolveHook(void* objectPtr, uint32_t variant)
    {
        if (!objectPtr || !g_BzrFn_ChunkResolve)
            return 0;

        uint32_t resolved = g_BzrFn_ChunkResolve(objectPtr, variant);
        if (!g_EnableChunkRenderFallback &&
            !g_TraceChunkRender &&
            !g_TraceChunkRenderVerbose &&
            !g_EnableChunkProxyDebug &&
            !g_EnableChunkMeshProxy)
        {
            return resolved;
        }

        __try
        {
            constexpr uint32_t kMaxReasonableGeoEntries = 256;

            auto* objectBytes = reinterpret_cast<uint8_t*>(objectPtr);
            auto* activeHandle = reinterpret_cast<void**>(objectBytes + 0x64);
            auto* lookup = reinterpret_cast<BzrGeoLookup*>(objectBytes + 0x68);
            void* activeBefore = *activeHandle;
            const uint32_t objectType = *reinterpret_cast<const uint32_t*>(objectBytes + 0x84);
            NoteChunkClassTransition(objectBytes, objectType);

            const bool hasLookup =
                lookup && lookup->entries && lookup->count > 0 && lookup->count <= kMaxReasonableGeoEntries;
            const bool shouldTraceStock =
                g_TraceChunkRenderVerbose ||
                (g_TraceChunkRender &&
                    ((hasLookup && (resolved == 0 || activeBefore == nullptr)) ||
                     objectType == kClassIdChunk));

            if (shouldTraceStock && AcquireChunkLogSlot())
            {
                LogChunkResolveSnapshot(
                    "stock",
                    hasLookup ? "post-stock" :
                        (objectType == kClassIdChunk ? "class-id-chunk-no-lookup" : "lookup-missing-or-invalid"),
                    objectBytes,
                    variant,
                    resolved,
                    activeBefore,
                    *activeHandle,
                    lookup,
                    -1,
                    0);
            }

            if (*activeHandle != nullptr && hasLookup)
                TrackChunkProxyDebugObject(objectBytes, objectType, *activeHandle, lookup);

            if (resolved != 0 && *activeHandle != nullptr)
                return resolved;

            if (!g_EnableChunkRenderFallback)
                return resolved;

            if (!hasLookup)
                return resolved;

            int selectedIndex = -1;
            const char* selectionReason = "no-handle-entry";

            if (resolved != 0)
            {
                selectedIndex = FindChunkGeoEntryByKey(lookup, resolved);
                if (selectedIndex >= 0)
                    selectionReason = "matched-stock-key";
            }

            if (selectedIndex < 0 && lookup->cachedKey != 0)
            {
                selectedIndex = FindChunkGeoEntryByKey(lookup, lookup->cachedKey);
                if (selectedIndex >= 0)
                    selectionReason = "matched-cached-key";
            }

            if (selectedIndex < 0 && variant != 0)
            {
                selectedIndex = FindChunkGeoEntryByKey(lookup, variant);
                if (selectedIndex >= 0)
                    selectionReason = "matched-variant";
            }

            if (selectedIndex < 0)
            {
                selectedIndex = FindFirstChunkGeoEntryWithHandle(lookup);
                if (selectedIndex >= 0)
                    selectionReason = "first-handle";
            }

            if (selectedIndex < 0)
            {
                if (g_TraceChunkRender && AcquireChunkLogSlot())
                {
                    LogChunkResolveSnapshot(
                        "forced",
                        selectionReason,
                        objectBytes,
                        variant,
                        resolved,
                        activeBefore,
                        *activeHandle,
                        lookup,
                        -1,
                        0);
                }
                return resolved;
            }

            BzrGeoEntry& entry = lookup->entries[selectedIndex];
            *activeHandle = entry.handle;
            lookup->cachedKey = entry.packedKey;

            if (AcquireChunkLogSlot())
            {
                LogChunkResolveSnapshot(
                    "forced",
                    selectionReason,
                    objectBytes,
                    variant,
                    resolved,
                    activeBefore,
                    *activeHandle,
                    lookup,
                    selectedIndex,
                    entry.packedKey);
            }

            if (*activeHandle != nullptr)
                TrackChunkProxyDebugObject(objectBytes, objectType, *activeHandle, lookup);

            return entry.packedKey != 0 ? entry.packedKey : (resolved != 0 ? resolved : 1u);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            if (AcquireChunkLogSlot())
            {
                LogChunkDiagnostic("chunk", L"[CHUNK] Resolve hook exception obj=0x%08X variant=0x%08X resolved=0x%08X code=0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectPtr)),
                    variant,
                    resolved,
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        return resolved;
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
            if (IsOgreAnimationProfilerCollecting() &&
                g_BzrFn_RenderQueueAddRenderable)
            {
                g_DynamicGeometryQueuedBatches = 0;
                g_DynamicGeometryMergeableBatches = 0;
                g_DynamicGeometryBlendedBatches = 0;
                g_DynamicGeometryQueuedVertices = 0;
                g_DynamicGeometryQueuedIndices = 0;
                g_DynamicGeometryDistinctMaterials = 0;
                g_InDynamicGeometryQueueUpdate = true;
                g_BzrFn_LegacyWorldUpdateRenderQueue(thisPtr, renderQueue);
                g_InDynamicGeometryQueueUpdate = false;
                RecordNativeDynamicGeometryQueueSample(
                    thisPtr,
                    g_DynamicGeometryQueuedBatches,
                    g_DynamicGeometryMergeableBatches,
                    g_DynamicGeometryBlendedBatches,
                    g_DynamicGeometryDistinctMaterials,
                    g_DynamicGeometryQueuedVertices,
                    g_DynamicGeometryQueuedIndices);
                for (uint32_t i = 0;
                     i < g_DynamicGeometryDistinctMaterials;
                     ++i)
                {
                    RecordNativeDynamicGeometryMaterialSample(
                        reinterpret_cast<const void*>(
                            g_DynamicGeometryMaterialSamples[i]),
                        g_DynamicGeometryMaterialBatchCounts[i],
                        g_DynamicGeometryMaterialBlendedCounts[i]);
                }
            }
            else
            {
                g_BzrFn_LegacyWorldUpdateRenderQueue(thisPtr, renderQueue);
            }
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

    static volatile long g_ChunkGeomDumpFragmentBudget = 8;
    static volatile long g_ChunkGeomDumpChunkletBudget = 2;

    static bool TryCopyBytesSeh(const void* src, void* dst, size_t len)
    {
        __try
        {
            memcpy(dst, src, len);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    // One-shot layout probe for the structure at obj+0x64: hex-dumps the first
    // 0x60 bytes and ASCII-probes every dword that looks like a heap/module
    // pointer, so the real geo-name field can be located from a live session.
    static void DumpChunkGeomBytes(const char* tag, const void* geomPtr, volatile long* budget)
    {
        if (!geomPtr || !budget || InterlockedDecrement(budget) < 0)
            return;

        uint8_t raw[0x60] = {};
        if (!TryCopyBytesSeh(geomPtr, raw, sizeof(raw)))
        {
            LogChunkDiagnostic(
                "chunkspawn",
                L"[CHUNKSPAWN] geom-dump tag=%hs geom=0x%08X unreadable\n",
                tag ? tag : "?",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(geomPtr)));
            return;
        }

        wchar_t hex[sizeof(raw) * 3 + 1] = {};
        for (size_t i = 0; i < sizeof(raw); ++i)
        {
            static const wchar_t kDigits[] = L"0123456789ABCDEF";
            hex[i * 3 + 0] = kDigits[raw[i] >> 4];
            hex[i * 3 + 1] = kDigits[raw[i] & 0xF];
            hex[i * 3 + 2] = L' ';
        }
        hex[sizeof(raw) * 3] = L'\0';

        LogChunkDiagnostic(
            "chunkspawn",
            L"[CHUNKSPAWN] geom-dump tag=%hs geom=0x%08X bytes=%ls\n",
            tag ? tag : "?",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(geomPtr)),
            hex);

        for (size_t off = 0; off + 4 <= sizeof(raw); off += 4)
        {
            const uint32_t value = *reinterpret_cast<const uint32_t*>(raw + off);
            if (value < 0x10000 || value >= 0x7FFF0000)
                continue;

            char text[40] = {};
            if (TryReadInlineAsciiBuffer(reinterpret_cast<const void*>(static_cast<uintptr_t>(value)),
                                         sizeof(text) - 1,
                                         text,
                                         sizeof(text)) &&
                std::strlen(text) >= 3)
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN]   geom-deref tag=%hs off=0x%02X ptr=0x%08X text=%hs\n",
                    tag ? tag : "?",
                    static_cast<uint32_t>(off),
                    value,
                    text);
            }
        }

        // The dword at geom+0x00 points into a 0x18-byte-stride name table
        // (chunk2's slot holds inline ASCII, craft-piece slots don't).
        // Hex-dump the raw slot bytes so the actual encoding is visible.
        const uint32_t nameRef = *reinterpret_cast<const uint32_t*>(raw);
        if (nameRef >= 0x10000 && nameRef < 0x7FFF0000)
        {
            uint8_t slot[0x30] = {};
            if (TryCopyBytesSeh(reinterpret_cast<const void*>(static_cast<uintptr_t>(nameRef)),
                                slot,
                                sizeof(slot)))
            {
                wchar_t slotHex[sizeof(slot) * 3 + 1] = {};
                for (size_t i = 0; i < sizeof(slot); ++i)
                {
                    static const wchar_t kDigits[] = L"0123456789ABCDEF";
                    slotHex[i * 3 + 0] = kDigits[slot[i] >> 4];
                    slotHex[i * 3 + 1] = kDigits[slot[i] & 0xF];
                    slotHex[i * 3 + 2] = L' ';
                }
                slotHex[sizeof(slot) * 3] = L'\0';
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN]   geom-name-slot tag=%hs target=0x%08X bytes=%ls\n",
                    tag ? tag : "?",
                    nameRef,
                    slotHex);
            }
            else
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN]   geom-name-slot tag=%hs target=0x%08X unreadable\n",
                    tag ? tag : "?",
                    nameRef);
            }
        }
    }

    static volatile long g_PartialFragmentBoneCollapseLogBudget = 24;

    // The bridge offsets are only sometimes populated on the objects the fragment
    // hooks see -- a fragment root is not always the same node the renderer keeps
    // the craft's entity on. Try every route to the entity and take the first that
    // is actually an Ogre object, rather than trusting a single offset:
    //   direct/owner  - the bridge hanging off this node, when it has one
    //   gameobj       - round-trip out to the owning GameObject and back to the
    //                   node the renderer uses, which is the path the skinning
    //                   sweep walks and the only one proven to work for every craft
    static void* ResolveCraftOgreEntity(void* objectPtr, const char*& outVia)
    {
        outVia = "none";
        if (!objectPtr)
            return nullptr;

        const ChunkBridgeSnapshot snapshot =
            CaptureChunkBridgeSnapshot(reinterpret_cast<const uint8_t*>(objectPtr));
        if (LooksLikeOgreObject(snapshot.directOgreEntity))
        {
            outVia = "direct";
            return snapshot.directOgreEntity;
        }
        if (LooksLikeOgreObject(snapshot.ownerOgreEntity))
        {
            outVia = "owner";
            return snapshot.ownerOgreEntity;
        }

        void* gameObject = nullptr;
        if (!TryGetGameObjectFromObj76(objectPtr, gameObject) || !gameObject)
            return nullptr;

        void* liveObj76 = nullptr;
        if (!TryGetGameObjectObj76(gameObject, liveObj76) || !liveObj76 || liveObj76 == objectPtr)
            return nullptr;

        const ChunkBridgeSnapshot liveSnapshot =
            CaptureChunkBridgeSnapshot(reinterpret_cast<const uint8_t*>(liveObj76));
        if (LooksLikeOgreObject(liveSnapshot.directOgreEntity))
        {
            outVia = "gameobj";
            return liveSnapshot.directOgreEntity;
        }
        if (LooksLikeOgreObject(liveSnapshot.ownerOgreEntity))
        {
            outVia = "gameobj-owner";
            return liveSnapshot.ownerOgreEntity;
        }

        return nullptr;
    }

    // Raw Ogre calls kept in their own frame so a bad entity/skeleton pointer
    // cannot take the fragment walk down with it. No named C++ objects here:
    // __try cannot coexist with object unwinding.
    static bool TryCollapseOwnerBoneSeh(
        FnOgreEntityGetSkeleton getSkeleton,
        FnOgreEntityU16Query getNumBones,
        FnOgreSkeletonGetBoneByIndex getBoneByIndex,
        FnOgreStringQuery getBoneName,
        FnOgreBoneSetManuallyControlled setManuallyControlled,
        FnOgreNodeSetScale setScale,
        void* ownerEntity,
        const char* geomName,
        uint16_t& outBoneIndex,
        uint16_t& outBoneCount)
    {
        __try
        {
            void* const skeleton = getSkeleton(ownerEntity);
            if (!skeleton)
                return false;

            const uint16_t boneCount = getNumBones(skeleton);
            outBoneCount = boneCount;
            if (boneCount == 0 || boneCount > kMaxOwnerSkeletonBones)
                return false;

            for (uint16_t index = 0; index < boneCount; ++index)
            {
                void* const bone = getBoneByIndex(skeleton, index);
                if (!bone)
                    continue;

                if (_stricmp(getBoneName(bone).c_str(), geomName) != 0)
                    continue;

                // Manual control stops the skeleton's animation pass restoring
                // the bone next frame; the zero scale is what actually removes
                // the piece's vertices.
                setManuallyControlled(bone, true);
                setScale(bone, 0.0f, 0.0f, 0.0f);
                outBoneIndex = index;
                return true;
            }

            return false;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    // Partial fragmentation detaches individual geos while the hull keeps
    // rendering. The legacy engine unparented each detached geo from the craft's
    // object tree, so it stopped drawing on the model the same frame its debris
    // appeared. Redux bakes the whole craft into a single skinned Ogre mesh that
    // cannot unparent anything, so the piece stays welded to the body until
    // FullFragmentObject hides the entire mesh — a tank flies its blown-off wing
    // away while a second copy rides along on the hull.
    //
    // Every stock craft mesh skins each geo rigidly to one identically-named bone
    // (all vertex weights are exactly 1.0), so zeroing that bone removes exactly
    // the piece that just detached. Ogre propagates scale down the bone tree,
    // which matches the legacy semantics: unparenting a geo took its children
    // with it, and those children spawn as their own chunks anyway.
    static void CollapseOwnerBoneForDetachedPiece(const ChunkCreateSourceTreeProbe& probe)
    {
        if (!g_EnablePartialFragmentBoneCollapse || !g_ActivePartialFragment)
            return;
        if (!probe.valid || !probe.source.geomName[0])
            return;

        // probe.ownerEntity is the game-side tagENTITY, not an Ogre object, so it
        // can never answer getSkeleton. The bridge on the geo node itself is the
        // next best thing, and the root-scoped entity is the backstop; every
        // candidate is vetted before any Ogre call is made on it.
        const char* entityVia = "none";
        const char* entitySource = "node";
        void* ownerOgreEntity =
            ResolveCraftOgreEntity(const_cast<void*>(static_cast<const void*>(probe.source.objectBytes)), entityVia);
        if (!ownerOgreEntity)
        {
            entitySource = "root";
            ownerOgreEntity = g_ActiveFragmentSourceOgreEntity;
            entityVia = g_ActiveFragmentSourceOgreEntityVia;
        }
        if (!ownerOgreEntity)
        {
            if (InterlockedDecrement(&g_PartialFragmentBoneCollapseLogBudget) >= 0)
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN] bone-collapse geo=%hs skipped=no-owner-entity\n",
                    probe.source.geomName);
            }
            return;
        }

        static FnOgreEntityGetSkeleton getSkeleton =
            ResolveOgreProc<FnOgreEntityGetSkeleton>("?getSkeleton@Entity@Ogre@@QBEPAVSkeletonInstance@2@XZ");
        static FnOgreEntityU16Query getNumBones =
            ResolveOgreProc<FnOgreEntityU16Query>("?getNumBones@Skeleton@Ogre@@UBEGXZ");
        static FnOgreSkeletonGetBoneByIndex getBoneByIndex =
            ResolveOgreProc<FnOgreSkeletonGetBoneByIndex>("?getBone@Skeleton@Ogre@@UBEPAVBone@2@G@Z");
        static FnOgreStringQuery getBoneName =
            ResolveOgreProc<FnOgreStringQuery>("?getName@Node@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
        static FnOgreBoneSetManuallyControlled setManuallyControlled =
            ResolveOgreProc<FnOgreBoneSetManuallyControlled>("?setManuallyControlled@Bone@Ogre@@QAEX_N@Z");
        static FnOgreNodeSetScale setScale =
            ResolveOgreProc<FnOgreNodeSetScale>("?setScale@Node@Ogre@@UAEXMMM@Z");

        if (!getSkeleton || !getNumBones || !getBoneByIndex || !getBoneName ||
            !setManuallyControlled || !setScale)
        {
            static bool s_ProcFailureLogged = false;
            if (!s_ProcFailureLogged)
            {
                s_ProcFailureLogged = true;
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN] bone-collapse unavailable; skeleton procs unresolved\n");
            }
            return;
        }

        uint16_t boneIndex = 0;
        uint16_t boneCount = 0;
        const bool collapsed = TryCollapseOwnerBoneSeh(
            getSkeleton,
            getNumBones,
            getBoneByIndex,
            getBoneName,
            setManuallyControlled,
            setScale,
            ownerOgreEntity,
            probe.source.geomName,
            boneIndex,
            boneCount);

        if (InterlockedDecrement(&g_PartialFragmentBoneCollapseLogBudget) >= 0)
        {
            LogChunkDiagnostic(
                "chunkspawn",
                L"[CHUNKSPAWN] bone-collapse geo=%hs entity=0x%08X from=%hs via=%hs bones=%u %hs=%u\n",
                probe.source.geomName,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ownerOgreEntity)),
                entitySource,
                entityVia,
                static_cast<uint32_t>(boneCount),
                collapsed ? "boneIndex" : "unmatched",
                static_cast<uint32_t>(boneIndex));
        }
    }

    void* __fastcall ChunkEffectCreateChunkHook(void* thisPtr,
                                                void* /*edx*/,
                                                void* objectPtr,
                                                const float* velocity,
                                                uint8_t preserveFlag)
    {
        if (!g_BzrFn_ChunkEffectCreateChunk)
            return nullptr;

        const auto* thisBytes = reinterpret_cast<const uint8_t*>(thisPtr);
        uint32_t countBefore = 0;
        TryReadChunkEffectCount(thisBytes, countBefore);

        ChunkCreateSourceTreeProbe sourceTreeProbe = {};
        CaptureChunkCreateSourceTreeProbe(reinterpret_cast<const uint8_t*>(objectPtr), sourceTreeProbe);

        void* result = g_BzrFn_ChunkEffectCreateChunk(thisPtr, objectPtr, velocity, preserveFlag);

        uint32_t countAfter = countBefore;
        TryReadChunkEffectCount(thisBytes, countAfter);

        ChunkEffectActiveEntry createdEntry = {};
        const ChunkEffectActiveEntry* createdEntryPtr = nullptr;
        if (countAfter > countBefore)
        {
            if (TryReadChunkEffectEntry(thisBytes, countBefore, createdEntry))
                createdEntryPtr = &createdEntry;
        }

        const uint8_t* boundObjectBytes = nullptr;
        if (createdEntryPtr && createdEntryPtr->objectBytes)
            boundObjectBytes = createdEntryPtr->objectBytes;
        else
            boundObjectBytes = reinterpret_cast<const uint8_t*>(objectPtr);

        // The object pool recycles pointers, so any binding left at either
        // address belongs to a previous chunk. Evict before storing — a
        // failed source capture must not leave the old craft's identity
        // behind for this chunk to inherit.
        EraseChunkResolvedBinding(reinterpret_cast<const uint8_t*>(objectPtr));
        EraseChunkResolvedBinding(boundObjectBytes);

        if (boundObjectBytes)
            StoreChunkResolvedBinding(boundObjectBytes, sourceTreeProbe);

        // Now that the debris exists, stop the intact hull from drawing the piece
        // that just left it. No-op unless PartialFragmentObject is on the stack.
        CollapseOwnerBoneForDetachedPiece(sourceTreeProbe);

        LogChunkCreateLifecycle(
            L"CreateChunk",
            thisPtr,
            reinterpret_cast<const uint8_t*>(objectPtr),
            nullptr,
            velocity,
            preserveFlag,
            countBefore,
            countAfter,
            createdEntryPtr,
            sourceTreeProbe.valid ? &sourceTreeProbe : nullptr);

        return result;
    }

    void __fastcall ChunkEffectCreateChunkletHook(void* thisPtr,
                                                  void* /*edx*/,
                                                  const void* positionVec,
                                                  const float* velocity,
                                                  uint8_t preserveFlag)
    {
        if (!g_BzrFn_ChunkEffectCreateChunklet)
            return;

        const auto* thisBytes = reinterpret_cast<const uint8_t*>(thisPtr);
        uint32_t countBefore = 0;
        TryReadChunkEffectCount(thisBytes, countBefore);

        g_BzrFn_ChunkEffectCreateChunklet(thisPtr, positionVec, velocity, preserveFlag);

        uint32_t countAfter = countBefore;
        TryReadChunkEffectCount(thisBytes, countAfter);

        ChunkEffectActiveEntry createdEntry = {};
        const ChunkEffectActiveEntry* createdEntryPtr = nullptr;
        if (countAfter > countBefore)
        {
            if (TryReadChunkEffectEntry(thisBytes, countBefore, createdEntry))
                createdEntryPtr = &createdEntry;
        }

        // Generic chunklets have no craft owner; if the pool recycled this
        // pointer from a craft chunk, the leftover binding would dress the
        // chunklet in that craft's debris meshes.
        if (createdEntryPtr && createdEntryPtr->objectBytes)
            EraseChunkResolvedBinding(createdEntryPtr->objectBytes);

        LogChunkCreateLifecycle(
            L"CreateChunklet",
            thisPtr,
            nullptr,
            reinterpret_cast<const float*>(positionVec),
            velocity,
            preserveFlag,
            countBefore,
            countAfter,
            createdEntryPtr,
            nullptr);

        // Baseline layout dump of a known-good chunklet geo (its name reads
        // fine) to compare against the craft-piece geoms whose names don't.
        if (createdEntryPtr && createdEntryPtr->objectBytes)
        {
            const void* geomRef = nullptr;
            char geomName[64] = {};
            if (TryReadChunkGeomIdentity(createdEntryPtr->objectBytes, geomRef, geomName, sizeof(geomName)) &&
                geomRef && geomName[0])
            {
                DumpChunkGeomBytes("chunklet-baseline", geomRef, &g_ChunkGeomDumpChunkletBudget);
            }
        }
    }

    static volatile long g_ChunkFragmentWalkLogBudget = 160;

    static bool AcquireChunkFragmentWalkLogSlot()
    {
        return InterlockedDecrement(&g_ChunkFragmentWalkLogBudget) >= 0;
    }


    static void LogChunkFragmentWalkTree(const wchar_t* tag,
                                         void* thisPtr,
                                         void* objectPtr,
                                         uint8_t preserveFlag)
    {
        if (!g_TraceChunkRender && !g_TraceChunkEffectRuntime)
            return;
        if (!AcquireChunkFragmentWalkLogSlot())
            return;

        LogChunkDiagnostic(
            "chunkspawn",
            L"[CHUNKSPAWN] %ls-walk this=0x%08X root=0x%08X preserve=%u\n",
            tag ? tag : L"fragment",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectPtr)),
            static_cast<uint32_t>(preserveFlag));

        // Depth-first dump of the OBJ76 tree handed to the fragment walker.
        constexpr uint32_t kMaxWalkNodes = 24;
        constexpr uint32_t kMaxWalkStack = 24;
        const uint8_t* pending[kMaxWalkStack] = {};
        uint32_t pendingDepth[kMaxWalkStack] = {};
        uint32_t pendingCount = 0;
        if (objectPtr)
        {
            pending[pendingCount] = reinterpret_cast<const uint8_t*>(objectPtr);
            pendingDepth[pendingCount] = 0;
            ++pendingCount;
        }

        uint32_t visited = 0;
        while (pendingCount != 0 && visited < kMaxWalkNodes)
        {
            --pendingCount;
            const uint8_t* node = pending[pendingCount];
            const uint32_t depth = pendingDepth[pendingCount];
            if (!node)
                continue;
            ++visited;

            uint32_t classId = 0;
            uint32_t flags = 0;
            void* geomRef = nullptr;
            void* owner = nullptr;
            char geomName[64] = {};
            TryReadChunkObjectSummary(node, classId, flags, geomRef, geomName, sizeof(geomName), owner);

            const uint8_t* parent = nullptr;
            const uint8_t* sibling = nullptr;
            const uint8_t* child = nullptr;
            const bool linksOk = TryReadChunkObjectLinks(node, parent, sibling, child);

            if (AcquireChunkFragmentWalkLogSlot())
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN]   frag-node depth=%u obj=0x%08X class=%u flags=0x%08X geom=0x%08X geomName=%hs parent=0x%08X sibling=0x%08X child=0x%08X%hs\n",
                    depth,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(node)),
                    classId,
                    flags,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(geomRef)),
                    geomName[0] ? geomName : "<none>",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parent)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sibling)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(child)),
                    linksOk ? "" : " links=unreadable");
            }

            if (geomRef && !geomName[0])
                DumpChunkGeomBytes("fragnode", geomRef, &g_ChunkGeomDumpFragmentBudget);

            if (!linksOk)
                continue;
            // Push sibling first so children print directly under their parent.
            if (sibling && pendingCount < kMaxWalkStack)
            {
                pending[pendingCount] = sibling;
                pendingDepth[pendingCount] = depth;
                ++pendingCount;
            }
            if (child && pendingCount < kMaxWalkStack)
            {
                pending[pendingCount] = child;
                pendingDepth[pendingCount] = depth + 1;
                ++pendingCount;
            }
        }

        if (visited >= kMaxWalkNodes && AcquireChunkFragmentWalkLogSlot())
        {
            LogChunkDiagnostic(
                "chunkspawn",
                L"[CHUNKSPAWN]   frag-walk truncated at %u nodes\n",
                visited);
        }
    }

    static void BeginActiveFragmentSourceContext(void* rootObjectPtr)
    {
        g_ActiveFragmentSourceMeshName[0] = '\0';
        g_ActiveFragmentSourceOgreEntity = nullptr;
        g_ActiveFragmentSourceOgreEntityVia = "none";
        g_ActiveFragmentSourceOdfName[0] = '\0';
        if (!rootObjectPtr)
            return;

        const ChunkBridgeSnapshot rootSnapshot =
            CaptureChunkBridgeSnapshot(reinterpret_cast<const uint8_t*>(rootObjectPtr));
        if (rootSnapshot.ownerResolvedMeshName[0])
        {
            strncpy_s(
                g_ActiveFragmentSourceMeshName,
                rootSnapshot.ownerResolvedMeshName,
                _TRUNCATE);
        }

        g_ActiveFragmentSourceOgreEntity =
            ResolveCraftOgreEntity(rootObjectPtr, g_ActiveFragmentSourceOgreEntityVia);

        // Fragment nodes are render-tree nodes; the ODF lives on the GameObject
        // that owns them, one hop out through the obj76 back-link.
        void* rootGameObject = nullptr;
        if (TryGetGameObjectFromObj76(rootObjectPtr, rootGameObject) && rootGameObject)
        {
            TryGetCraftOdfName(
                rootGameObject,
                g_ActiveFragmentSourceOdfName,
                sizeof(g_ActiveFragmentSourceOdfName));
        }

        if (AcquireChunkFragmentWalkLogSlot())
        {
            LogChunkDiagnostic(
                "chunkspawn",
                L"[CHUNKSPAWN] frag-source obj=0x%08X mesh=%hs odf=%hs base=%hs file=%hs ogreEntity=0x%08X via=%hs\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(rootObjectPtr)),
                g_ActiveFragmentSourceMeshName[0] ? g_ActiveFragmentSourceMeshName : "<none>",
                g_ActiveFragmentSourceOdfName[0] ? g_ActiveFragmentSourceOdfName : "<none>",
                rootSnapshot.ownerEntityBaseName[0] ? rootSnapshot.ownerEntityBaseName : "<none>",
                rootSnapshot.ownerOgreFilename[0] ? rootSnapshot.ownerOgreFilename : "<none>",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_ActiveFragmentSourceOgreEntity)),
                g_ActiveFragmentSourceOgreEntityVia);
        }
    }

    void __fastcall ChunkEffectPartialFragmentHook(void* thisPtr,
                                                   void* /*edx*/,
                                                   void* objectPtr,
                                                   const float* velocity,
                                                   uint8_t preserveFlag)
    {
        if (!g_BzrFn_ChunkEffectPartialFragment)
            return;

        // The original recurses into its own patched entry for child levels;
        // only dump the tree for the outermost call.
        const bool outermost = (g_ChunkFragmentHookDepth == 0);
        uint32_t countBefore = 0;
        if (outermost)
        {
            LogChunkFragmentWalkTree(L"PartialFragmentObject", thisPtr, objectPtr, preserveFlag);
            TryReadChunkEffectCount(reinterpret_cast<const uint8_t*>(thisPtr), countBefore);
            BeginActiveFragmentSourceContext(objectPtr);
            g_ActivePartialFragment = true;
        }
        ++g_ChunkFragmentHookDepth;
        g_BzrFn_ChunkEffectPartialFragment(thisPtr, objectPtr, velocity, preserveFlag);
        --g_ChunkFragmentHookDepth;
        if (outermost)
        {
            g_ActivePartialFragment = false;
            g_ActiveFragmentSourceMeshName[0] = '\0';
            g_ActiveFragmentSourceOgreEntity = nullptr;
            g_ActiveFragmentSourceOgreEntityVia = "none";
            g_ActiveFragmentSourceOdfName[0] = '\0';
            uint32_t countAfter = countBefore;
            TryReadChunkEffectCount(reinterpret_cast<const uint8_t*>(thisPtr), countAfter);
            if (AcquireChunkFragmentWalkLogSlot())
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN] PartialFragmentObject-result created=%d countBefore=%u countAfter=%u\n",
                    static_cast<int>(countAfter) - static_cast<int>(countBefore),
                    countBefore,
                    countAfter);
            }
        }
    }

    // In the legacy engine full fragmentation unparented every geo from the
    // craft's object tree, so the intact model stopped rendering on the same
    // frame the debris appeared. Redux instead renders a baked Ogre mesh that
    // lingers until entity teardown; hide that mesh (and its light) here so
    // the chunk proxies visually take over immediately.
    static bool TrySetChunkOwnerMovableVisibleSeh(
        FnOgreSetVisible setVisible,
        void* movable,
        bool visible)
    {
        // Same trap as the bone collapse: these bridge slots sometimes hold text
        // rather than a movable, and setVisible on text is a virtual call into
        // string bytes. Vet before dispatching -- SEH turns that into a caught
        // fault, not a safe no-op.
        if (!setVisible || !LooksLikeOgreObject(movable))
            return false;

        __try
        {
            setVisible(movable, visible);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    static void HideChunkFragmentSourceMesh(void* objectPtr)
    {
        if (!objectPtr)
            return;

        static FnOgreSetVisible setVisible =
            ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");
        if (!setVisible)
            return;

        const ChunkBridgeSnapshot snapshot =
            CaptureChunkBridgeSnapshot(reinterpret_cast<const uint8_t*>(objectPtr));

        // When this node's own bridge slots are bogus the resolver still reaches
        // the craft's entity through the owning GameObject, so full fragmentation
        // stops depending on the same offset the collapse could not trust either.
        const char* resolvedVia = "none";
        void* const resolvedEntity = ResolveCraftOgreEntity(objectPtr, resolvedVia);

        uint32_t hiddenCount = 0;
        void* const candidates[] = {
            resolvedEntity,
            snapshot.directOgreLight,
            (snapshot.ownerOgreLight != snapshot.directOgreLight) ? snapshot.ownerOgreLight : nullptr,
        };
        for (void* candidate : candidates)
        {
            if (TrySetChunkOwnerMovableVisibleSeh(setVisible, candidate, false))
                ++hiddenCount;
        }

        if (AcquireChunkFragmentWalkLogSlot())
        {
            LogChunkDiagnostic(
                "chunkspawn",
                L"[CHUNKSPAWN] hide-source obj=0x%08X entity=0x%08X via=%hs directEntity=0x%08X ownerEntity=0x%08X hidden=%u\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectPtr)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(resolvedEntity)),
                resolvedVia,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(snapshot.directOgreEntity)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(snapshot.ownerOgreEntity)),
                hiddenCount);
        }
    }

    void __fastcall ChunkEffectFullFragmentHook(void* thisPtr,
                                                void* /*edx*/,
                                                void* objectPtr,
                                                const float* velocity,
                                                uint8_t preserveFlag)
    {
        if (!g_BzrFn_ChunkEffectFullFragment)
            return;

        const bool outermost = (g_ChunkFragmentHookDepth == 0);
        uint32_t countBefore = 0;
        if (outermost)
        {
            LogChunkFragmentWalkTree(L"FullFragmentObject", thisPtr, objectPtr, preserveFlag);
            TryReadChunkEffectCount(reinterpret_cast<const uint8_t*>(thisPtr), countBefore);
            HideChunkFragmentSourceMesh(objectPtr);
            BeginActiveFragmentSourceContext(objectPtr);
        }
        ++g_ChunkFragmentHookDepth;
        g_BzrFn_ChunkEffectFullFragment(thisPtr, objectPtr, velocity, preserveFlag);
        --g_ChunkFragmentHookDepth;
        if (outermost)
        {
            g_ActiveFragmentSourceMeshName[0] = '\0';
            g_ActiveFragmentSourceOgreEntity = nullptr;
            g_ActiveFragmentSourceOgreEntityVia = "none";
            g_ActiveFragmentSourceOdfName[0] = '\0';
            uint32_t countAfter = countBefore;
            TryReadChunkEffectCount(reinterpret_cast<const uint8_t*>(thisPtr), countAfter);
            if (AcquireChunkFragmentWalkLogSlot())
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN] FullFragmentObject-result created=%d countBefore=%u countAfter=%u\n",
                    static_cast<int>(countAfter) - static_cast<int>(countBefore),
                    countBefore,
                    countAfter);
            }
        }
    }

    void __fastcall DynamicGeometryPrepareHook(void* thisPtr, void* /*edx*/)
    {
        if (!g_BzrFn_DynamicGeometryPrepare || !thisPtr)
            return;
        if (!IsOgreAnimationProfilerCollecting())
        {
            g_BzrFn_DynamicGeometryPrepare(thisPtr);
            return;
        }

        bool preparedBefore = false;
        __try
        {
            const auto* bytes = static_cast<const uint8_t*>(thisPtr);
            preparedBefore = bytes[0x1DC] != 0;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            preparedBefore = false;
        }

        LARGE_INTEGER start{};
        LARGE_INTEGER end{};
        QueryPerformanceCounter(&start);
        g_BzrFn_DynamicGeometryPrepare(thisPtr);
        QueryPerformanceCounter(&end);

        bool preparedAfter = false;
        __try
        {
            preparedAfter = static_cast<const uint8_t*>(thisPtr)[0x1DC] != 0;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            preparedAfter = false;
        }
        RecordNativeDynamicGeometryPrepareSample(
            thisPtr,
            !preparedBefore && preparedAfter,
            static_cast<uint64_t>(end.QuadPart - start.QuadPart));
    }

    void __fastcall DynamicGeometrySetSquaredViewDepthHook(
        void* thisPtr,
        void* /*edx*/,
        float squaredViewDepth)
    {
        if (!g_BzrFn_DynamicGeometrySetSquaredViewDepth || !thisPtr)
            return;

        g_BzrFn_DynamicGeometrySetSquaredViewDepth(thisPtr, squaredViewDepth);
        if (!g_DynamicAlphaDepthBatchingEnabled)
            return;

        __try
        {
            auto* bytes = static_cast<uint8_t*>(thisPtr);
            // +0x31 is the stock material-derived blending classification and
            // +0xAC is the render-queue group. Stock already quantizes groups
            // below 100 to 32 logarithmic depth slices per distance doubling.
            // Coarsen only blended world effects; opaque geometry, overlays,
            // the true squared view depth at +0xB0, and material state remain
            // untouched.
            if (bytes[0x31] != 0 && bytes[0xAC] < 100)
            {
                auto* depthKey = reinterpret_cast<float*>(bytes + 0x34);
                *depthKey = OgreProfilerAlgorithms::QuantizeDynamicAlphaDepthKey(
                    *depthKey,
                    g_DynamicAlphaDepthBucketStride);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            // Preserve stock behavior if an unexpected batch layout appears.
        }
    }

    void __fastcall DynamicGeometryAddRenderableHook(
        void* renderQueue,
        void* /*edx*/,
        void* renderable,
        uint8_t queueGroup)
    {
        if (!g_BzrFn_RenderQueueAddRenderable)
            return;
        if (g_InDynamicGeometryQueueUpdate)
        {
            ++g_DynamicGeometryQueuedBatches;
            __try
            {
                const auto* bytes = static_cast<const uint8_t*>(renderable);
                if (bytes[0x30] != 0)
                    ++g_DynamicGeometryMergeableBatches;
                if (bytes[0x31] != 0)
                    ++g_DynamicGeometryBlendedBatches;
                g_DynamicGeometryQueuedVertices +=
                    *reinterpret_cast<const uint32_t*>(bytes + 0x58);
                g_DynamicGeometryQueuedIndices +=
                    *reinterpret_cast<const uint32_t*>(bytes + 0x88);

                const uintptr_t materialIdentity =
                    *reinterpret_cast<const uintptr_t*>(bytes + 0x3C);
                if (materialIdentity != 0)
                {
                    uint32_t materialIndex = g_DynamicGeometryDistinctMaterials;
                    for (uint32_t i = 0;
                         i < g_DynamicGeometryDistinctMaterials;
                         ++i)
                    {
                        if (g_DynamicGeometryMaterialSamples[i] == materialIdentity)
                        {
                            materialIndex = i;
                            break;
                        }
                    }
                    if (materialIndex == g_DynamicGeometryDistinctMaterials &&
                        g_DynamicGeometryDistinctMaterials <
                            kDynamicGeometryMaterialSampleCapacity)
                    {
                        g_DynamicGeometryMaterialSamples[materialIndex] = materialIdentity;
                        g_DynamicGeometryMaterialBatchCounts[materialIndex] = 0;
                        g_DynamicGeometryMaterialBlendedCounts[materialIndex] = 0;
                        ++g_DynamicGeometryDistinctMaterials;
                    }
                    if (materialIndex < g_DynamicGeometryDistinctMaterials)
                    {
                        ++g_DynamicGeometryMaterialBatchCounts[materialIndex];
                        if (bytes[0x31] != 0)
                            ++g_DynamicGeometryMaterialBlendedCounts[materialIndex];
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                // Keep the aggregate batch count even when an unsupported
                // DynamicGeometryBatch layout is encountered.
            }
        }
        g_BzrFn_RenderQueueAddRenderable(renderQueue, renderable, queueGroup);
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

    // Stub: chunk fragment event flush not present in this revision.
    void FlushChunkFragmentEventsForShutdown()
    {
    }
}

// Optional high-level bridge used by EXU and other companion DLLs. BZRNet/native
// details remain entirely inside OpenShim; callers receive only a stable status.
extern "C" DWORD WINAPI OpenShimImpl_SetBZRNetNickname(LPCSTR nickname)
{
    return static_cast<DWORD>(BZROpenShim::SetBzrNetNicknameFromBridge(nickname));
}
