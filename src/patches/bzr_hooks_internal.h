#pragma once
// bzr_hooks_internal.h
// BZR Open Shim - what the translation units split out of bzr_hooks.cpp
// share with it: Ogre ABI types and the helpers each one calls. Everything
// here lives in BZROpenShim::Hooks (formerly bzr_hooks.cpp's anonymous
// namespace). Not a public interface; keep it to what a split-out file needs.
#include <Windows.h>

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "bzr_hooks.h"
#include "stable_id_list.h"
#include "bzr_object_layout.h"
#include "bzr_options_ui.h"

namespace BZROpenShim
{
    // Set by ResolveBzrHooks from its isSteam argument.
    extern bool g_IsSteamExe;
    // GameObject::GetHandle, resolved by ResolveBzrHooks from patches.json;
    // 0 until then, and every caller stands down on 0.
    extern uintptr_t g_GameObjectGetHandleAddr;
    using FnPlayGlobalSound = int(__cdecl*)(const char* filename, uint32_t arg1, uint32_t arg2, uint32_t arg3);

    using FnCarrierGetWeapon = void* (__thiscall*)(void* carrier, int slot);

    using FnHudSpriteLookup = int(__cdecl*)(const char* spriteName);
    extern FnHudSpriteLookup g_BzrFn_HudSpriteLookup;
    bool SetStockScrapPilotPanelsVisible(bool visible);

    using FnGetLocalPlayerNetId = uint16_t(__cdecl*)();
    using FnGetTeamNum = int(__cdecl*)(int handle);
    using FnGetPlayerHandle = int(__cdecl*)();
    using FnRecordDeath = void(__cdecl*)(int killedTeam, int killerTeam);
    using FnResolveObj76GameObject = void*(__cdecl*)(void*);
    void* __cdecl GameObjectFromHandleGog(int handle);
    extern FnGetLocalPlayerNetId g_BzrFn_GetLocalPlayerNetId;
    extern FnGetPlayerHandle g_BzrFn_GetPlayerHandle;
    extern FnGetTeamNum g_BzrFn_GetTeamNum;
    extern FnRecordDeath g_BzrFn_RecordDeath;
    extern FnResolveObj76GameObject g_BzrFn_ResolveObj76GameObject;

    void InstallShadowFarOverrideIfPossible();

    using FnEngineFlameAddFlame = void(__thiscall*)(void* self, const void* transform, float scale);
    using FnEngineFlameControl = void(__thiscall*)(void* self);
    using FnEngineFlameSubmit = void(__thiscall*)(void* self, void* camera);
    using FnEngineFlameResolveTexture = int(__cdecl*)(BzrString* textureName);
    using FnExuGetTeamEngineFlameColor = int(__cdecl*)(int team);
    extern FnEngineFlameAddFlame g_BzrFn_EngineFlameAddFlame;
    extern FnEngineFlameControl g_BzrFn_EngineFlameControl;
    extern FnEngineFlameResolveTexture g_BzrFn_EngineFlameResolveTexture;
    extern FnEngineFlameSubmit g_BzrFn_EngineFlameSubmit;

    using FnCarrierGetSelectedMask = uint32_t(__thiscall*)(void* carrier);
    using FnTeamEnemyPInt = bool(__thiscall*)(void* team, int targetTeam);
    // PREREQ_WhatIs(itemName) -> prereq id, 0 when the name is not in the
    // strategic AI's enumerated unit/building universe.
    using FnPrereqWhatIs = uint16_t(__cdecl*)(const char*);
    // Multi-producer maker registration. InitObjectClasses walks the build
    // trees of every load-time root; FindObjectClass keys the resulting list on
    // the built class alone, so a class reachable from two producers keeps only
    // the first producer it was seen under, and SetMaker writes that one into
    // makers[0]. Collect the pairs FindObjectClass rejects, and append them
    // after Units_Init has filled makers[0] for every accepted pair.
    using FnAiFindObjectClass = uint32_t(__cdecl*)(void* objClass, void* buildClass);
    using FnAiUnitsInit = void(__cdecl*)();
    using FnAiIsBuilding = uint8_t(__cdecl*)(void* objClass);
    using FnAiClass2UnitType = void*(__cdecl*)(void* objClass);
    using FnAiClass2BuildingType = void*(__cdecl*)(void* objClass, int zero);
    using FnAiGetPrereq = uint16_t(__cdecl*)(void* objClass);
    struct AiExtraMakerPair { void* objClass; void* buildClass; };
    extern std::vector<AiExtraMakerPair> g_AiExtraMakerPairs;
    extern volatile long g_AiMultiProducerMakerLogBudget;
    extern volatile long g_AipPrereqCensusEmitted;
    extern volatile long g_AipResolveTraceBudget;
    extern volatile long g_NeutralAttackOrderLogBudget;
    extern std::unordered_set<uintptr_t> g_PilotCarrierNullLoggedObjects;

    using FnCommandHandler = void(__cdecl*)(uint16_t id, const char* cmd);
    using FnHelpLog = void(__cdecl*)(void* obj, const char* text);
    using FnHelpUi = void(__cdecl*)(int channel, const char* text);
    using FnBanLookup = void* (__cdecl*)(uint16_t id);
    using FnIsHost = int(__cdecl*)();
    extern FnBanLookup g_BzrFn_BanLookup;
    extern FnCommandHandler g_BzrFn_CommandHandler;
    extern FnHelpLog g_BzrFn_HelpLog;
    extern FnHelpUi g_BzrFn_HelpUi;
    extern FnIsHost g_BzrFn_IsHost;
    extern void** g_BzrPtr_920168;

    using FnGetSelected = void* (__thiscall*)(void* list);
    using FnNetPlayerSetData = void(__thiscall*)(void* thisPtr, uint32_t slot, uint8_t* data, uint32_t len);
    using FnNetPlayerSetFlagBuffer = void(__thiscall*)(void* thisPtr, const uint8_t* data, uint32_t len);
    using FnSetMyFlag = void(__cdecl*)();
    using FnUiTextEntryClear = void (__thiscall*)(void*);
    extern FnGetSelected g_BzrFn_GetSelected;
    extern FnNetPlayerSetData g_BzrFn_NetPlayerSetData;
    extern FnNetPlayerSetFlagBuffer g_BzrFn_NetPlayerSetFlagBuffer;
    extern FnSetMyFlag g_BzrFn_SetMyFlag;
    extern FnUiSetStr g_BzrFn_TextEntryAppendText;
    extern FnUiTextEntryClear g_BzrFn_TextEntryClear;
    extern void** g_BzrPtr_94557C;
    extern void** g_BzrPtr_9456D0;
    extern uint8_t* g_BzrPtr_CurrentUser;

    extern void (__thiscall* g_BzrFn_TextEntrySetInputLimit)(void*, int);

    // ---------------------------------------------------------------------
    // BZR function pointers (GOG v2.2.301 addresses)
    // ---------------------------------------------------------------------
    using FnVehicleListSet = void(__thiscall*)(void* thisPtr, BzrString a, BzrString b);
    using FnVehicleListLoad = void(__thiscall*)(void* thisPtr, BzrString* name);
    using FnVehicleListStep = void(__thiscall*)(void* thisPtr);
    using FnVehicleListFinalize = void(__thiscall*)(void* thisPtr);
    extern FnVehicleListFinalize g_BzrFn_VehicleListFinalize;
    extern FnVehicleListLoad g_BzrFn_VehicleListLoad;
    extern FnVehicleListStep g_BzrFn_VehicleListRefresh1;
    extern FnVehicleListStep g_BzrFn_VehicleListRefresh2;
    extern FnVehicleListSet g_BzrFn_VehicleListSet;
    extern void** g_BzrPtr_945478;
    extern void** g_BzrPtr_94548C;
    extern void** g_BzrPtr_94555C;

    struct BuildItem;
    using FnBuildItemInit = void(__cdecl*)(BuildItem& item, int64_t token);
    using FnBuildItemCleanup = void(__cdecl*)(BuildItem& item);
    extern BuildItem* g_BzrBuildMenuRoot;
    extern FnBuildItemCleanup g_BzrFn_CleanupBuildItem;
    extern FnBuildItemInit g_BzrFn_InitBuildItem;

    // Producer nested build menus (producer_build_menu.cpp). The functions are
    // the stock targets of the vtable slots the menu patches replace, and the
    // vtables identify which producer type an object is.
    using FnModeListUpdate = void(__thiscall*)(void* self);
    using FnSetActiveMode = bool(__thiscall*)(void* self, int mode);
    using FnObjectDeselect = void(__thiscall*)(void* self);
    using FnControlPanelLifecycle = void(__thiscall*)(void* self);
    using FnModeListSetMode = void(__thiscall*)(void* modeList, int slot, int mode, int enabled);
    extern FnModeListUpdate g_BzrFn_ProducerUpdateModeList;
    extern FnSetActiveMode g_BzrFn_ProducerSetActiveMode;
    extern FnObjectDeselect g_BzrFn_GameObjectDeselect;
    extern FnModeListUpdate g_BzrFn_ConstructionRigUpdateModeList;
    extern FnSetActiveMode g_BzrFn_ConstructionRigSetActiveMode;
    extern FnObjectDeselect g_BzrFn_ConstructionRigDeselect;
    extern FnControlPanelLifecycle g_BzrFn_ControlPanelPostLoad;
    extern FnControlPanelLifecycle g_BzrFn_ControlPanelCleanup;
    extern FnModeListSetMode g_BzrFn_ModeListSetMode;
    extern void* g_BzrVtbl_Producer;
    extern void* g_BzrVtbl_Recycler;
    extern void* g_BzrVtbl_Factory;
    extern void* g_BzrVtbl_ConstructionRig;
    extern uint8_t* g_BzrPtr_ClassLoadAssetsFlag;

    using FnLoadScreenPrep = void(__cdecl*)();
    using FnSetShellState = void(__cdecl*)(int state);
    using FnBzrStringCtorFromCStr = void(__thiscall*)(BzrString* self, const char* text);
    using FnBzrStringDtor = void(__thiscall*)(BzrString* self);
    using FnLoadScreenClearSelection = void(__cdecl*)(BzrString* text);
    extern FnBzrStringCtorFromCStr g_BzrFn_BzrStringCtorFromCStr;
    extern FnBzrStringDtor g_BzrFn_BzrStringDtor;
    extern FnLoadScreenClearSelection g_BzrFn_LoadScreenClearSelection;
    extern FnLoadScreenPrep g_BzrFn_LoadScreenPrep;
    extern FnSetShellState g_BzrFn_SetShellState;
    extern FnUiDialogAction g_BzrFn_UiDialogAdvance;
    extern FnUiDialogAction g_BzrFn_UiDialogSetEnabled;

    using FnGameObjectClassBuild = void*(__thiscall*)(void* objectClass,
                                                      void* transform,
                                                      int team,
                                                      int independent,
                                                      int seqNo,
                                                      void* existingObject);
    extern FnGameObjectClassBuild g_BzrFn_SprayEmitterBuildOriginal;

    using FnGameObjectRelation = bool(__thiscall*)(void* thisPtr, void* other);
    using FnGameObjectGetObjByHandle = void* (__cdecl*)(int handle);
    using FnShieldTowerSimulate = void(__thiscall*)(void* thisPtr, float dt);
    using FnMagnetMineSimulate = void(__thiscall*)(void* thisPtr, float dt);
    using FnProximityMineSimulate = void(__thiscall*)(void* thisPtr, float dt);
    using FnShieldTowerPowerUpdate = void(__fastcall*)(void* thisPtr);
    using FnMatrixInverse = void(__cdecl*)(void* outMatrix, const void* inMatrix);
    using FnVectorTransform = void(__cdecl*)(float* dst, const float* src, int count, const void* matrix);
    using FnRangeSearch = void(__thiscall*)(void* rangeSearch,
                                            double minX,
                                            double minZ,
                                            double maxX,
                                            double maxZ,
                                            void* outResults);
    using FnRangeResultsGetNext = uint32_t(__thiscall*)(void* results, uint32_t** outHandlePtr);
    extern FnShieldTowerSimulate g_BzrFn_BuildingSimulate;
    extern FnRangeSearch g_BzrFn_CollisionRangeSearch;
    extern FnGameObjectRelation g_BzrFn_GameObjectEnemyP;
    extern FnGameObjectRelation g_BzrFn_GameObjectFriendP;
    extern FnGameObjectGetObjByHandle g_BzrFn_GameObjectGetObjByHandle;
    extern FnMagnetMineSimulate g_BzrFn_MagnetMineSimulateOriginal;
    extern FnMatrixInverse g_BzrFn_MatrixInverse;
    extern FnProximityMineSimulate g_BzrFn_MineSimulate;
    extern FnProximityMineSimulate g_BzrFn_ProximityMineSimulateOriginal;
    extern FnRangeResultsGetNext g_BzrFn_RangeResultsGetNext;
    extern FnShieldTowerPowerUpdate g_BzrFn_ShieldTowerPowerUpdate;
    extern FnShieldTowerSimulate g_BzrFn_ShieldTowerSimulateOriginal;
    extern FnVectorTransform g_BzrFn_VectorTransform;

    using FnCalcRangeCraft = void(__cdecl*)(void* craft,
                                            float* closeRange,
                                            float* range,
                                            float* time,
                                            void** weapon);
    using FnAttackTaskDoState = void(__thiscall*)(void* thisPtr);
    using FnTerrainGetIntersection = int(__cdecl*)(double startX,
                                                   double startY,
                                                   double startZ,
                                                   float diffX,
                                                   float diffY,
                                                   float diffZ,
                                                   float* fraction,
                                                   void* outNormal);
    using FnProcessDoSubTask = bool(__thiscall*)(void* thisPtr);
    using FnGetGameTime = float(__cdecl*)();
    using FnFindPlanForObject = void* (__cdecl*)(void* objectPtr, float x, float z);
    using FnAiPathGetLength = float(__thiscall*)(void* pathPtr);
    using FnAiPathDelete = void* (__thiscall*)(void* pathPtr, uint32_t flags);
    using FnRecycleTaskDoGotoScrap = void(__thiscall*)(void* recycleTask);
    extern FnAiPathDelete g_BzrFn_AiPathDelete;
    extern FnAiPathGetLength g_BzrFn_AiPathGetLength;
    extern FnAttackTaskDoState g_BzrFn_AttackTaskDoState;
    extern FnCalcRangeCraft g_BzrFn_CalcRangeCraft;
    extern FnFindPlanForObject g_BzrFn_FindPlanForObject;
    extern FnGetGameTime g_BzrFn_GetGameTime;
    extern FnProcessDoSubTask g_BzrFn_GunTowerProcessDoSubTask;
    extern FnProcessDoSubTask g_BzrFn_OffensiveProcessDoSubTask;
    extern FnRecycleTaskDoGotoScrap g_BzrFn_RecycleTaskDoGotoScrap;
    extern FnTerrainGetIntersection g_BzrFn_TerrainGetIntersection;
    extern FnProcessDoSubTask g_BzrFn_TurretTankProcessDoSubTask;

    using FnSprayBuildingSimulate = void(__thiscall*)(void* thisPtr, float dt);
    using FnTugPostLoad = bool(__thiscall*)(void* thisPtr);
    using FnRigProcessCleanUState2 = void(__thiscall*)(void* process);
    using FnGameObjectHandleGetObj = void*(__cdecl*)(uint32_t handle);
    using FnScriptProducerPredicate = bool(__cdecl*)(int handle);
    using FnAIUnitRemove = void(__cdecl*)(void* unitPtr);
    using FnAIBuildConstructionEnd = void(__cdecl*)(int teamId, int constructType);
    using FnAIBuildReservedAreaRemove = void(__cdecl*)(int teamId, int reservedArea);
    using FnAISpentCreditRefund = void(__cdecl*)(int teamId, void* buildingPtr, void* unitPtr);
    using FnUnitsSOrderStop = void(__cdecl*)(void* unitPtr);
    using FnAIBuildUnassignedCCAdd = void(__cdecl*)(void* teamPtr, void* unitPtr);
    extern FnAIBuildConstructionEnd g_BzrFn_AIBuildConstructionEnd;
    extern FnAIBuildReservedAreaRemove g_BzrFn_AIBuildReservedAreaRemove;
    extern FnAIBuildUnassignedCCAdd g_BzrFn_AIBuildUnassignedCCAdd;
    extern FnAISpentCreditRefund g_BzrFn_AISpentCreditRefund;
    extern FnAIUnitRemove g_BzrFn_AIUnitRemove;
    extern FnSprayBuildingSimulate g_BzrFn_SprayBuildingSimulateOriginal;
    extern FnUnitsSOrderStop g_BzrFn_UnitsSOrderStop;

    using FnUiTextEntryAppendChar = uint8_t (__thiscall*)(void*, uint8_t);
    extern FnUiTextEntryAppendChar g_BzrFn_TextEntryAppendChar;

    using FnPersonSimulate = void(__thiscall*)(void* thisPtr, float dt);
    extern FnPersonSimulate g_BzrFn_PersonSimulate;
    extern float g_TurretAimPitchMultiplierEnhanced;
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
    extern FnChunkEffectCreateChunk g_BzrFn_ChunkEffectCreateChunk;
    extern FnChunkEffectCreateChunklet g_BzrFn_ChunkEffectCreateChunklet;
    extern FnChunkEffectFragmentObject g_BzrFn_ChunkEffectFullFragment;
    extern FnChunkEffectFragmentObject g_BzrFn_ChunkEffectPartialFragment;

    using FnChunkResolve = uint32_t(__cdecl*)(void* objectPtr, uint32_t variant);
    extern FnChunkResolve g_BzrFn_ChunkResolve;

    using FnDynamicGeometryPrepare = void(__thiscall*)(void* self);
    using FnLegacyWorldUpdateRenderQueue = void(__thiscall*)(void* self, void* renderQueue);
    extern FnDynamicGeometryPrepare g_BzrFn_DynamicGeometryPrepare;
    extern FnLegacyWorldUpdateRenderQueue g_BzrFn_LegacyWorldUpdateRenderQueue;
    void InstallDynamicGeometryHooks();
    bool RunLegacyWorldQueueWithDynamicGeometryCounters(void* thisPtr, void* renderQueue);

    namespace Hooks
    {
        // --- Ogre ABI value types -----------------------------------------
        struct OgreColourValue
        {
            float r;
            float g;
            float b;
            float a;
        };

        struct OgreVector3
        {
            float x;
            float y;
            float z;
        };

        struct OgreQuaternion
        {
            float w;
            float x;
            float y;
            float z;
        };

        // --- Ogre entry points, resolved by mangled name ------------------
        using FnOgreGetRootSceneNode = void*(__thiscall*)(void*);
        using FnOgreCreateBillboardSet = void*(__thiscall*)(void*, uint32_t);
        using FnOgreCreateChildSceneNode = void*(__thiscall*)(void*, const OgreVector3&, const OgreQuaternion&);
        using FnOgreCreateEntity = void*(__thiscall*)(void*, const std::string&);
        using FnOgreCreateManualObject = void*(__thiscall*)(void*);
        using FnOgreGetResourceGroupManager = void*(__cdecl*)();
        using FnOgreResourceGroupExists = bool(__thiscall*)(void*, const std::string&);
        using FnOgreCreateResourceGroup = void(__thiscall*)(void*, const std::string&, bool);
        using FnOgreAddResourceLocation = void(__thiscall*)(void*, const std::string&, const std::string&, const std::string&, bool, bool);
        using FnOgreInitialiseResourceGroup = void(__thiscall*)(void*, const std::string&);
        using FnOgreAttachObject = void(__thiscall*)(void*, void*);
        using FnOgreSetBillboardsInWorldSpace = void(__thiscall*)(void*, bool);
        using FnOgreSetDefaultDimensions = void(__thiscall*)(void*, float, float);
        using FnOgreSetBillboardMaterialName = void(__thiscall*)(void*, const std::string&, const std::string&);
        using FnOgreCreateBillboard = void*(__thiscall*)(void*, float, float, float, const OgreColourValue&);
        using FnOgreSetBillboardPosition = void(__thiscall*)(void*, float, float, float);
        using FnOgreSetBillboardColour = void(__thiscall*)(void*, const OgreColourValue&);
        using FnOgreDestroyBillboardSet = void(__thiscall*)(void*, void*);
        using FnOgreSetNodePosition = void(__thiscall*)(void*, float, float, float);
        using FnOgreSetNodeOrientation = void(__thiscall*)(void*, float, float, float, float);
        using FnOgreSetVisible = void(__thiscall*)(void*, bool);
        using FnOgreGetLightColour = const OgreColourValue*(__thiscall*)(void*);
        using FnOgreSetLightColour = void(__thiscall*)(void*, float, float, float);
        using FnOgreGetLightRadian = const float*(__thiscall*)(void*);
        using FnOgreGetLightFloat = float(__thiscall*)(void*);
        using FnOgreGetLightVisible = bool(__thiscall*)(void*);
        using FnOgreSetSpotlightRange = void(__thiscall*)(void*, const float*, const float*, float);
        using FnOgreSetAttenuation = void(__thiscall*)(void*, float, float, float, float);
        using FnOgreGetLightType = int(__thiscall*)(void*);
        using FnOgreGetLightVector3 = const OgreVector3*(__thiscall*)(void*);
        using FnOgreGetLightDerivedPosition = const OgreVector3*(__thiscall*)(void*, bool);
        using FnOgreGetCastShadows = bool(__thiscall*)(void*);
        using FnOgreGetRenderQueue = void*(__thiscall*)(void*);
        using FnOgreGetCurrentViewport = void*(__thiscall*)(void*);
        using FnOgreViewportGetCamera = void*(__thiscall*)(void*);
        using FnOgreMovableObjectNotifyCurrentCamera = void(__thiscall*)(void*, void*);
        using FnOgreEntityUpdateRenderQueue = void(__thiscall*)(void*, void*);
        using FnOgreRenderQueueAddRenderablePriority = void(__thiscall*)(void*, void*, uint8_t, uint16_t);
        using FnOgreIsVisible = bool(__thiscall*)(void*);
        using FnOgreGetRenderQueueGroup = uint8_t(__thiscall*)(void*);
        using FnOgreGetNumSubEntities = uint32_t(__thiscall*)(void*);
        using FnOgreGetSubEntity = void*(__thiscall*)(void*, uint32_t);
        using FnOgreEntityBoolQuery = bool(__thiscall*)(void*);
        using FnOgreEntityU16Query = uint16_t(__thiscall*)(void*);
        using FnOgreEntityIntQuery = int(__thiscall*)(void*);
        using FnOgreEntityGetSkeleton = void*(__thiscall*)(void*);
        using FnOgreSkeletonGetBoneByIndex = void*(__thiscall*)(void*, uint16_t);
        using FnOgreBoneSetManuallyControlled = void(__thiscall*)(void*, bool);
        using FnOgreNodeSetScale = void(__thiscall*)(void*, float, float, float);
        using FnOgreStringQuery = const std::string&(__thiscall*)(void*);
        using FnOgreProcessQueuedUpdates = void(__cdecl*)();
        using FnOgreNumAttachedObjects = uint16_t(__thiscall*)(void*);
        using FnOgreGetAttachedObjectByIndex = void*(__thiscall*)(void*, uint16_t);
        using FnOgreManualObjectSetDynamic = void(__thiscall*)(void*, bool);
        using FnOgreManualObjectEstimateCount = void(__thiscall*)(void*, uint32_t);
        using FnOgreManualObjectBegin = void(__thiscall*)(
            void*, const std::string&, int, const std::string&);
        using FnOgreManualObjectBeginUpdate = void(__thiscall*)(void*, uint32_t);
        using FnOgreManualObjectVertex3 = void(__thiscall*)(void*, float, float, float);
        using FnOgreManualObjectTexture2 = void(__thiscall*)(void*, float, float);
        using FnOgreManualObjectIndex = void(__thiscall*)(void*, uint32_t);
        using FnOgreManualObjectEnd = void*(__thiscall*)(void*);
        using FnOgreManualObjectUpdateRenderQueue = void(__thiscall*)(void*, void*);
        using FnOgreMovableSetCastShadows = void(__thiscall*)(void*, bool);
        // Diagnostic-only. Ogre grows ManualObject::mAABB monotonically across
        // beginUpdate() cycles (it is reset only by clear()), so the batch's
        // aggregate bounds are read back rather than assumed.
        using FnOgreManualObjectGetBoundingBox = const void*(__thiscall*)(void*);
        using FnOgreManualObjectGetBoundingRadius = float(__thiscall*)(void*);

        // Cached GetProcAddress on OgreMain.dll; one warning per missing name.
        void* ResolveOgreProcRaw(const char* name);
        template<typename T>
        T ResolveOgreProc(const char* name)
        {
            return reinterpret_cast<T>(ResolveOgreProcRaw(name));
        }
        bool TryGetOgreModuleRange(uintptr_t& outBase, uintptr_t& outEnd);
        void* GetOgreSceneManagerRuntime();
        const char* TryGetRttiClassName(const void* object, char* buffer, size_t bufferSize);

        // --- Settings --------------------------------------------------------
        inline constexpr char kUserConfigSinglePlayerSection[] = "SinglePlayer";
        inline constexpr char kUserConfigDisplaySection[] = "Display";
        inline constexpr char kUserConfigNetworkSection[] = "Network";
        uint16_t ReadLocalPlayerNetIdValue();
        bool TryGetEnvFloat(const char* name, float& outValue);
        std::string ToLowerAscii(std::string value);
        bool TryReadSteam64Value(uint64_t& outValue);

        // --- Shared helpers and engine state (the *_helpers.cpp files, bzr_hooks.cpp) --
        uintptr_t GetMainModuleBase();
        bool IsExuModuleLoaded();
        // VirtualProtect + memcpy + flush; false if the page cannot be made writable.
        bool WritePatchBytes(uintptr_t address, const uint8_t* bytes, size_t len);
        // Target of the E8 call at callInstr; 0 when it is not an E8.
        uint32_t ResolveRel32Target(uint8_t* callInstr);
        // True once the SetRunning mission seam is hooked; its enter/exit
        // callbacks then drive the per-world baseline resets.
        extern bool g_MissionSeamInstalled;
        inline constexpr size_t kGameObjectArenaSlotCapacity = 4096;
        inline constexpr size_t kGameObjectVelocityOffset = 0x12C; // world velocity vec3
        // Confirmed on the shipped image: Ordnance::Init stores its owner obj76
        // argument ([ebp+0xC]) here at 0x00585292, and zeroes the paired handle
        // at +0xDC (0x005852A4) when that argument is null.
        inline constexpr size_t kOrdnanceOwnerObjOffset = 0xD8;
        static_assert(kOrdnanceOwnerObjOffset == ObjectLayout::kOrdnanceOwnerObj,
                      "ordnance owner obj76 disagrees with bzr_object_layout.h");
        bool IsSinglePlayerSession();
        bool TryGetGameObjectFieldBase(void* objectPtr, uint8_t*& outBase);
        bool TryGetGameObjectFromObj76(void* obj76, void*& outGameObject);
        bool IsNeutralTeamObject(void* objectPtr);
        // Directory of the game executable; legacy per-mod cfg files live there.
        std::filesystem::path GetConfigModuleDirectory();
        char* TrimAsciiInPlace(char* text);
        // Resolved by ResolveBzrHooks from patches.json ("PlayGlobalSound").
        extern FnPlayGlobalSound g_BzrFn_PlayGlobalSound;
        // Engine viewport height global (the scrap/pilot HUD and radar layout read it).
        inline constexpr uintptr_t kScrapPilotHudViewportHeightAddr = 0x02CECEE4;

        // --- Headlights (headlights.cpp) -------------------------------------
        inline constexpr size_t kHeadlightObjectSlotCount = 4096;
        static_assert(kGameObjectArenaSlotCapacity == kHeadlightObjectSlotCount,
                      "arena capacity forward constant out of sync");
        inline constexpr size_t kHeadlightObjectSlotSize = 0x400;
        // Redux's verified handle mapping (mirrors EXU GameObject::GetObj):
        // object = arena + (handle >> 20) * 0x400, the arena being
        // EngineGlobals::GameObjectArena (0x0260DB20 on GOG).
        struct HeadlightOgreApi
        {
            FnOgreGetLightColour getDiffuse = nullptr;
            FnOgreSetLightColour setDiffuse = nullptr;
            FnOgreGetLightColour getSpecular = nullptr;
            FnOgreSetLightColour setSpecular = nullptr;
            FnOgreGetLightRadian getInnerAngle = nullptr;
            FnOgreGetLightRadian getOuterAngle = nullptr;
            FnOgreGetLightFloat getFalloff = nullptr;
            FnOgreSetSpotlightRange setRange = nullptr;
            FnOgreGetLightVisible getVisible = nullptr;
            FnOgreSetVisible setVisible = nullptr;
            // Attenuation half of the light. Stock BZR sets this once at
            // headlight creation (0x0067F599: setAttenuation(600, 1, 0.007,
            // 0.0002)) and never revisits it, so the shim owns any change.
            FnOgreSetAttenuation setAttenuation = nullptr;
            FnOgreGetLightFloat getAttenuationRange = nullptr;
            FnOgreGetLightFloat getAttenuationConstant = nullptr;
            FnOgreGetLightFloat getAttenuationLinear = nullptr;
            FnOgreGetLightFloat getAttenuationQuadratic = nullptr;
            FnOgreGetLightFloat getPowerScale = nullptr;
            FnOgreGetLightType getType = nullptr;
            FnOgreGetLightDerivedPosition getDerivedPosition = nullptr;
            FnOgreGetLightVector3 getDerivedDirection = nullptr;
            FnOgreGetCastShadows getCastShadows = nullptr;
        };
        HeadlightOgreApi& GetHeadlightOgreApi();
        void HueToHeadlightRgb(float hue, float& r, float& g, float& b);
        bool IsLiveHeadlightObjectSlot(void* gameObject);
        void* TryGetHeadlightPlayerObject();
        void InitializeHeadlightConfig();
        void RefreshHeadlightState();
        void RevertHeadlightsToBaseline();
        void ReapplyHeadlightConfigFromUserConfig();
        // The headlight baselines are stamped with a world generation that the
        // SetRunning mission seam advances, so baseline invalidation never has
        // to infer a world change from allocator behavior.
        void HeadlightNotifyMissionRunStateChanged(bool enteringSimulation);
        void InstallEmissionLightFixIfPossible();
        void VerifyExpectedOgreExportsIfPossible();

        // --- Weapon convergence and smart reticle (weapon_convergence_hooks.cpp) ---
        inline constexpr size_t kGameObjectDistributedObjectOffset = 0x18;
        inline constexpr size_t kGameObjectObjOffset = 0xF4;
        inline constexpr size_t kObj76TransformOffset = 0x20;
        struct SmartReticleRangeSite
        {
            uintptr_t instructionAddr;
            uint8_t opcode[4];
            uint8_t opcodeLen;
        };
        inline constexpr float kSmartReticleRangeStock = 200.0f;
        inline constexpr size_t kGameObjectGetTeamVtableOffset = 0x4;
        // Identifies a raw arena entry as a live GameObject WITHOUT calling
        // anything through its vtable.
        //
        // The arena hands back entries that are not GameObjects at all --
        // including objects whose vtable is an abstract base table. One such
        // table is 0x00878E94, whose slots 0, 1 and 3 all point at 0x0083E98E,
        // the import thunk for msvcr120!_purecall. Calling slot 1 there reaches
        // _purecall -> abort -> __fastfail(7), which raises 0xC0000409 with
        // subcode 7. __fastfail bypasses SEH entirely, so the __try below (and
        // any other handler) cannot contain it: the process dies immediately.
        // That is the crash captured in battlezone98redux.exe.23280.dmp.
        //
        // So the vtable is used only as a type tag -- compared, never invoked.
        // Slot 1 of every GameObject-family vtable in .rdata is the same
        // GameObject::GetTeam (the GameObjectGetTeam row), which makes an
        // exact pointer compare a positive identification rather than a
        // heuristic, and rejects abstract/_purecall tables and foreign objects
        // alike. Rebased to the live image; 0 when the row is not bound, which
        // no vtable slot equals, so every check fails closed.
        uintptr_t ExpectedGameObjectGetTeamAddr();
        // The main image's import address table slot for dllName!importName,
        // found through the import name table so it follows the build. 0 when
        // the image does not import it by name.
        uintptr_t FindMainImageImportSlot(const char* dllName, const char* importName);
        inline constexpr uintptr_t kGogPreferredImageBase = 0x00400000;
        bool IsLikelyGameObjectEntry(void* objectPtr);
        bool WritePointerValue(uintptr_t address, void* value);
        extern bool g_PlayerReticleShotConvergenceBaselineEnabled;
        extern bool g_PlayerReticleShotConvergenceEnabled;
        extern bool g_ShotConvergenceBaselineEnabled;
        extern bool g_ShotConvergenceEnabled;
        extern float g_SmartReticleRange;
        extern float g_SmartReticleRangeBaseline;
        extern bool g_SmartReticleRangeOwnedByBridge;
        void RefreshShotConvergencePatchState();
        float ClampSmartReticleRange(float range);
        void RefreshSmartReticleRangeState();
        void RevertShotConvergenceToBaseline();
        void RevertSmartReticleRangeToBaseline();

        // --- HUD sprite rect table (hud_sprite_rects.cpp) ----------------------
        struct HudSpriteRectRecord
        {
            int16_t x = 0;
            int16_t y = 0;
            int16_t w = 0;
            int16_t h = 0;
            float u0 = 0.0f;
            float v0 = 0.0f;
            float u1 = 0.0f;
            float v1 = 0.0f;
            uint32_t flags18 = 0;
            uint32_t textureRef1C = 0;
            uint32_t textureRef20 = 0;
        };
        extern std::vector<uintptr_t> g_HudSpriteCachedPanelAddresses;
        extern bool g_HudSpriteFallbackDiscoveryAttempted;
        extern ULONGLONG g_HudSpriteFallbackDiscoveryBackoffMs;
        extern ULONGLONG g_HudSpriteFallbackDiscoveryLastTick;
        extern std::unordered_set<uintptr_t> g_HudSpriteHiddenAddresses;
        extern std::unordered_map<int, HudSpriteRectRecord> g_HudSpriteHiddenEntries;
        extern std::unordered_map<int, HudSpriteRectRecord> g_HudSpriteOriginalEntries;
        extern std::unordered_map<uintptr_t, HudSpriteRectRecord> g_HudSpriteOriginalEntriesByAddress;
        extern HudSpriteRectRecord* g_HudSpriteRectTableBase;
        extern bool g_HudSpriteRectTableDiscoveryAttempted;
        extern ULONGLONG g_HudSpriteRectTableDiscoveryBackoffMs;
        extern ULONGLONG g_HudSpriteRectTableDiscoveryLastTick;
        extern bool g_ScrapPilotHudPanelOverrideActive;
        extern bool g_ScrapPilotHudPanelOverrideVisible;
        bool TryGetHudSpriteCurrentRecord(int spriteId, HudSpriteRectRecord& outRecord);

        // --- Scrap/pilot HUD legacy layout (scrap_pilot_hud.cpp) ---------------
        inline constexpr size_t kScrapPilotHudPointCount = 6;
        inline constexpr size_t kScrapPilotHudValueCount = kScrapPilotHudPointCount * 2;
        // BZ 1.5's plates, taken from the shipped 1.5 asset: spritea.stb in
        // bzone152.zfs places scrap_panel at (0,94) 58x34 and pilot_panel at
        // (70,102) 58x26 inside scrncut.map. Every pixel in both regions is one
        // of exactly two ARGB4444 values -- 0xF000 opaque black or 0x0000
        // transparent -- so the art carries no texture detail at all and these
        // run tables reproduce the silhouettes pixel for pixel (1534 and 1299
        // solid pixels respectively).
        struct ScrapPilotHudPlateRun
        {
            uint8_t y0;
            uint8_t y1;
            uint8_t x0;
            uint8_t x1;
        };
        struct ScrapPilotHudPlate
        {
            const ScrapPilotHudPlateRun* runs;
            size_t runCount;
        };
        extern ULONGLONG g_ScrapPilotHudLastRefreshTick;
        extern bool g_ScrapPilotHudLegacyLayoutEnabled;
        void RefreshScrapPilotHudLayout();
        void RevertScrapPilotHudToBaseline();

        // --- Career statistics and PKTRACE (career_stats.cpp) ------------------
        inline constexpr int kQueuedLoadNameBufferLen = 16;
        // The QueuedLoadPathBuffer / QueuedLoadNameBuffer rows; 0 when not
        // bound. Career stats and the multiplayer flags bind these and
        // NetPlayerByTeam into their own row sets instead.
        uintptr_t QueuedLoadPathBufferAddr();
        uintptr_t QueuedLoadNameBufferAddr();
        struct CareerPendingVictim
        {
            bool inUse = false;
            int victimHandle = 0;
            int damagerHandle = 0;
            // Sampled at damage time and sticky thereafter. See the note on
            // SimKill in BZROpenShim.h: GetPlayerHandle moves the instant the
            // player's craft dies, so this cannot be re-derived at kill time.
            bool victimWasLocalPlayer = false;
            bool damagerWasLocalPlayer = false;
            uint64_t firstSeenMs = 0;
            uint64_t lastDamageMs = 0;
            // Research extension for player-kill correlation: retain teams,
            // and enough attacker history to tell a clean last-hit from a
            // genuine multi-attacker window.
            int victimTeam = 0;
            int damagerTeam = 0;
            uint32_t damageSequence = 0;
            // There is one slot per victim, so a second attacker overwrites
            // the first. Count the changeovers instead of trying to recover
            // them from the table afterwards, which cannot work.
            int distinctDamagers = 0;
            uint64_t lastDistinctDamagerMs = 0;
        };
        int GetGameObjectActualTeam(void* objectPtr);
        bool SatelliteWorldIsLive();
        bool TryGetGameObjectHandleValue(void* objectPtr, int& outHandle);
        extern ULONGLONG g_CareerStatsMpHookFirstAttemptTick;
        extern bool g_CareerStatsMpHookInstallAttempted;
        extern bool g_CareerStatsMpHookInstalled;
        extern ULONGLONG g_CareerStatsMpHookLastAttemptTick;
        extern bool g_CareerStatsMpHookMismatchLogged;
        extern bool g_DistributedRecordDeathIntHookInstalled;
        extern volatile long g_PlayerKillTraceBudget;
        extern InlineDetour32 g_RecordDeathDetour;
        extern bool g_TracePlayerKills;
        extern char g_LastKnownQueuedMissionName[kQueuedLoadNameBufferLen + 1];
        void RememberQueuedMissionName(const char* name);
        void StartCareerStatsMpSessionWorker();
        void ClearCareerPendingVictims();
        void PublishDamageForCareerStatsFromProbe(void* victim, void* damage);
        bool ShouldTracePlayerKills();
        void TickCareerPendingVictims();
        void InstallDistributedRecordDeathIntHookIfPossible();
        void InitializeCareerStatsConfig();
        void RevertCareerStatsToBaseline();
        void TickCareerSessionState();
        void InstallCareerStatsMpHookIfPossible();

        // --- Satellite visibility fix (satellite_visibility.cpp) ---------------
        inline constexpr size_t kGameObjectClassOffset = 0xF8;
        inline constexpr size_t kObjectClassTypeOffset = 0x1C;
        // Live GOG 2.2.301 View_Record. The previous value 0x004FD770 (VA
        // 0x008FD770) has *zero* cross-references anywhere in .text -- the
        // satellite gate below was reading unreferenced memory, so every
        // [SATVIS] sample taken before 2026-08-17 is void. The real record is
        // written by the satellite view setter (0x0061BD20) at 0x0061BE27:
        //   mov [0x008EAAD4], 0            ; previous view
        //   mov [0x008EAAD8], 3            ; Current_View = OVER_VIEW
        //   mov [0x008EACB8], ecx          ; overview object
        //   mov [0x008EAAD0], 0x0061BC90   ; Update_Camera = Set_Satellite_View
        // Base 0x008EAAD0 + kPresetViewCurrentViewOffset (0x8) lands on
        // 0x008EAAD8, which matches the independently derived
        // kGogViewModeAddr used by the target-camera fix.
        // The ViewRecord row; 0 when it is not bound.
        uintptr_t ViewRecordAddr();
        inline constexpr bool kHopOutAttackAlertFixEnabledDefault = false;
        // SelectionDisplay::Render carries the complete Redux GameObject pointer,
        // while the inherited GameObject interface (whose slot +4 is GetTeam)
        // begins at +0x18. Calling slot +4 from the complete-object vtable was
        // the crash-prone behavior in the original NEUTRAL_ONLY experiment.
        inline constexpr size_t kGameObjectInterfaceOffset = 0x18;
        // CORRECTED 2026-08-17. 0x00462450 is NOT GetPerceivedTeam -- it is
        // GameObject::GetTeam, and it returns the *actual* team. It occupies
        // slot 1 of the interface vtable in all twelve GameObject-family
        // vtables in .rdata, beside GetClass/SetTeam/GetPosition. The
        // non-virtual GetPerceivedTeam is 0x004625B0, it reads
        // [complete+0x180], and it appears in no vtable at all.
        //
        // Because 0x00462450 runs on the interface subobject (complete+0x18),
        // its [this+0x15C] resolves to complete+0x174 -- the actual team, a
        // different field 0xC below perceivedTeam. Reading that operand as if
        // it were perceivedTeam is what produced the bogus "save base is
        // complete-0xC" rule that shifted every visibility offset below.
        //
        // The save walker's base register IS the complete object. Two
        // independent confirmations:
        //   * SetPerceivedTeam (0x004DB4F0) writes [this+0x180] and is called
        //     with the complete pointer from Craft::AbandonPilot (0x004ADF20)
        //     and SetDamageFlags (0x004DC29C).
        //   * WeaponMine::Simulate reads the mine position at complete+0x108 /
        //     +0x10C / +0x110, and the walker records "pos" size=12 at +0x108.
        inline constexpr size_t kGameObjectActualTeamOffset = 0x174;
        inline constexpr size_t kGameObjectPerceivedTeamOffset = 0x180;
        inline constexpr int kGameTeamMin = 0;
        inline constexpr int kGameTeamMax = 15;
        inline constexpr size_t kGameObjectIlluminationOffset = 0xE8;
        inline constexpr size_t kGameObjectIsObjectiveOffset = 0x189;
        inline constexpr size_t kGameObjectIsVisibleOffset = 0x18C;
        inline constexpr size_t kGameObjectSeenOffset = 0x190;
        // CORRECTED 2026-09-19, and no longer advisory. This was 0x214, which
        // is where BZ 1.5 keeps targetHandle -- the Redux shift was never
        // applied. In Redux 0x214 is maxAmmo, stored XOR-obfuscated with
        // 0x33333333 (GameObject::GetMaxAmmo 0x0046D060 reads [this+0x214] and
        // unscrambles it), so the [SATVIS] `target` column has been printing a
        // scrambled ammo count for its whole life. Every value it recorded
        // before this commit should be discarded rather than reinterpreted.
        //
        // The real field comes from the engine's own accessor pair, the same
        // way the owner handle below it does:
        //   GameObject::SetTarget 0x0049F450 -- 0x0049F479 `mov [eax+0x21C],ecx`
        //   GameObject::GetTarget 0x00462610 -- 0x0046261A `mov ecx,[eax+0x21C]`
        //                                       then GetObj 0x004DA060
        // reached from the Lua bindings at .rdata 0x0087C4CC "SetTarget" /
        // 0x0087C4D8 "GetTarget" (table slots 0x00871D18 / 0x00871D20, the two
        // immediately above SetOwner).
        //
        // Complete-object relative and non-virtual, so it shares a base with
        // the fields above: the call site at 0x005AA94E does `sub ecx,0x18`
        // before calling GetTarget and re-adds 0x18 to the result, and neither
        // accessor appears anywhere in .rdata.
        //
        // BZ 1.5's PDB struct corroborates the ordering: targetHandle 0x214,
        // hitch 0x218, ownerHandle 0x21C -- the same three fields adjacent in
        // the same order, uniformly +0x8 here.
        inline constexpr size_t kGameObjectTargetHandleOffset = 0x21C;
        inline constexpr long kCameraTypeOverView = 3;
        // Some render-queue helpers are inlined or unexported from the shipped
        // OgreMain.dll; resolve those by raw image offset from the module base.
        // The offsets are only meaningful in the OgreMain both storefronts
        // ship, so anything else (a patch that updates OgreMain) gets nullptr.
        bool IsKnownOgreMainBuild(HMODULE ogreMain);
        template<typename T>
        T ResolveOgreProcByOffset(uintptr_t offset)
        {
            if (!offset)
                return nullptr;

            static HMODULE ogreMain = nullptr;
            if (!ogreMain)
                ogreMain = GetModuleHandleA("OgreMain.dll");
            if (!ogreMain || !IsKnownOgreMainBuild(ogreMain))
                return nullptr;

            return reinterpret_cast<T>(reinterpret_cast<uint8_t*>(ogreMain) + offset);
        }
        inline constexpr long kSatVisValidateBudgetDefault = 240;
        inline constexpr DWORD kSatVisValidateIntervalMs = 1000;
        size_t CollectLiveGameObjectsFromArena(void** outObjects, size_t capacity);
        bool LooksLikeOgreObject(const void* candidate);
        extern DWORD g_SatelliteVisibilityLastTick;
        extern volatile long g_SatelliteVisibilityLogBudget;
        extern DWORD g_SatelliteVisibilityLogIntervalMs;
        extern uint32_t g_SatelliteVisibilityObjectLimit;
        extern bool g_TraceSatelliteVisibility;
        bool IsSatelliteOverviewActive();
        void InitializeHopOutAttackAlertConfig();
        void RefreshSatelliteVisibilityFixState();
        void InitializeSatelliteVisibilityFixConfig(bool resetTracking);
        extern bool g_SatVisTestPreHideEnabled;
        extern int g_SatVisTestPreHideTeam;
        extern std::unordered_set<void*> g_SatVisTestPreHidden;
        extern bool g_SatVisValidateEnabled;
        extern volatile long g_SatVisValidateBudget;
        extern DWORD g_SatVisValidateLastTick;
        void MaybeSuppressStaleHopOutAttackAlert();
        void MaybeLogSatelliteVisibilitySample();
        void SyncSatelliteVisibility();
        void LogSatelliteVisibilityValidationSample();

        // --- Ogre dedupe crash fixes (ogre_dedupe_crash_fixes.cpp) -------------
        void InstallParticleTemplateDedupeHookIfPossible();
        void InstallUiManualObjectDedupeHookIfPossible();

        // --- Raw mouse input (raw_mouse_input.cpp) -----------------------------
        // Bound by RawMouseInputSignaturesMatch(); 0 until then.
        extern uintptr_t g_RawMouseInputEnabledAddr;
        extern uintptr_t g_RawMouseInputProcessAddr;
        extern bool g_RawMouseInputSignaturesMatch;
        extern bool g_RawMouseInputProcessHookInstalled;
        extern long g_RawMouseInputTraceBudget;
        bool ShouldTraceRawMouseInput();
        bool RawMouseInputSignaturesMatch();
        void InstallRawMouseInputProcessHookIfPossible();
        bool ResolveRawMouseInputPreference(const char*& outSource);

        // --- Shadow far distance correction (shadow_far_distance_hook.cpp) -----

        // --- Engine flames (engine_flames.cpp) ---------------------------------
        inline constexpr size_t kEngineFlameObjectSize = 0x1250;
        // GameObject -> ODF name chain, verified on the live GOG exe from GetOdf
        // (0x004FFFD0): the class accessor is a virtual on the sub-object at
        // GameObject+0x18 (vtable[0] returns GameObjectClass*), and the ODF name
        // is an INLINE char[8] buffer at GameObjectClass+0x30 (read by address,
        // not a pointer). The unit's faction is the first character of that name
        // (a=NSDF, s=CCA, c=CRA, b=Black Dog). Note: the char* at class+0x18 that
        // GetClassLabel returns is the gameplay category ("wingman", "tank"...),
        // which has no faction prefix -- do not use it here.
        inline constexpr size_t kGameObjectClassSubObjOffset = 0x18;
        inline constexpr size_t kGameObjectClassOdfNameMax = 8;
        // Faction jet flames (openshim.ini [Display] JetFlames). A global cosmetic
        // preference: when on, a unit's engine flame is tinted by its faction
        // (first char of the ODF label) for any team an EXU script has NOT already
        // colored. Purely visual/local, so it applies everywhere including MP.
        inline constexpr bool kJetFlamesEnabledDefault = false;
        void TickChunkProxyDebug(
            void* currentCamera = nullptr,
            bool allowManualSubmit = true);
        bool TryGetGameObjectWorldPosition(void* gameObject, float (&outPosition)[3]);
        extern int g_EngineFlamePrimaryBlackDogTexture;
        extern int g_EngineFlamePrimaryBlueTexture;
        extern int g_EngineFlamePrimaryGreenTexture;
        extern void* g_EngineFlamePrimaryManager;
        extern int g_EngineFlamePrimaryOrangeTexture;
        extern int g_EngineFlamePrimaryRedTexture;
        extern void* g_EngineFlameSecondaryManager;
        extern bool g_EngineFlameVariantsInitAttempted;
        extern bool g_EngineFlameVariantsInitialized;
        extern bool g_EngineFlameVtableHooksInstalled;
        extern bool g_JetFlamesConfigInitialized;
        extern bool g_LoggedEngineFlameTargetFailure;
        extern bool g_LoggedEngineFlameVtableHook;
        void ResolveEngineFlameRuntimeTargets();
        bool TryGetCraftOdfName(void* craftPtr, char* out, size_t outSize);
        void InitializeJetFlamesConfig();

        // --- AI and unit fixes (ai_unit_fixes.cpp) -----------------------------
        inline constexpr size_t kPersonCarrierOffset = 0x1A0;      // PDB 0x198
        extern bool g_AiMultiProducerMakersEnabled;
        extern bool g_AipResolveTraceEnabled;
        extern bool g_AllowNeutralAttackOrders;

        // --- AI weapon-mask selection (ai_weapon_mask.cpp) ---------------------
        // Makes artillery / lay-mines AI honour weaponMask, firing every
        // fitted hardpoint the mask names as one synchronized volley.
        //
        // These are enhancements, not restorations -- BZ 1.5 ignores the mask
        // on both paths exactly as stock Redux does -- and under the volley
        // policy they are not no-ops even for content that authors no mask:
        // the stock default 11111 means "every fitted hardpoint", so a stock
        // howitzer with four mortar hardpoints fires four rounds instead of
        // one. Both therefore default OFF, and both are gated to single
        // player because they change simulation outcomes.
        //
        // Split per craft type so the artillery volley can be enabled without
        // the lay-mines one and vice versa.
        inline constexpr bool kAiWeaponMaskArtilleryEnabledDefault = false;
        inline constexpr bool kAiWeaponMaskMinelayerEnabledDefault = false;
        extern bool g_AiWeaponMaskArtilleryEnabled;
        extern bool g_AiWeaponMaskMinelayerEnabled;
        extern bool g_HowitzerVolleyEnabled;
        extern bool g_WeaponMaskCarrierBiasEnabled;
        void RefreshAiWeaponMaskArtilleryState();
        void RevertAiWeaponMaskArtilleryToBaseline();
        void RefreshAiWeaponMaskMinelayerState();
        void RevertAiWeaponMaskMinelayerToBaseline();

        inline constexpr bool kHowitzerVolleyEnabledDefault = false;
        inline constexpr bool kWeaponMaskCarrierBiasEnabledDefault = false;

        // --- Multiplayer moderation (moderation.cpp) ---------------------------
        using BanRecord = StableIdList::Record;
        void SyncNicknameEntriesFromAuthoritativeValue(const char* value);
        extern std::vector<BanRecord> g_BanRecords;
        std::filesystem::path GetBansConfigPath();
        void EnsureBansConfigLoaded();
        bool AddBanConfigEntry(const char* stableId, const BzrString* name, const char* source);
        void KickBannedPlayers(const char* source, uint32_t lobby, uint32_t member, int changes);

        // --- Multiplayer lobby UI (lobby_ui.cpp) -------------------------------
        inline constexpr int kFlagPreviewWidth = 64;
        inline constexpr int kFlagPreviewHeight = 32;
        // 1.5 put the flag in a titled panel. Redux has no resizable frame
        // widget to borrow: its lobby panels ("Rooms", "Games", "Chat") are
        // whole pre-rendered panels packed into ui/Multiplayer/multipe_center.png
        // and multipc_center.png, sized for the slots they occupy. So the panel
        // is drawn into the generated PNG instead, matching that art's own edge
        // profile -- sampled off multipe_center.png at 1440x1080, which is the
        // canvas the widget is placed on, so these are 1:1 screen pixels:
        //   border   3px (0,42,0) | 2px (0,127,0) | 2px (0,84,0) | 2px (0,42,0)
        //   header   fill (0,42,0), then 4px (0,127,0) | 3px (0,84,0) | 2px dark
        //   field    1.5-style red with the one-bit emblem rendered black
        inline constexpr int kFlagPanelBorder = 9;
        inline constexpr int kFlagPanelHeaderHeight = 49;
        // Leave a real gutter before the stock W/M buttons. The old 240px plate
        // ended only a few pixels before their hit rectangles and its bright
        // border visibly covered their left edge.
        inline constexpr int kFlagPanelWidth = 224;
        inline constexpr int kFlagPreviewFieldScale = 3;
        inline constexpr uint32_t kLegacyFlagDataSlot = 0x0Du;
        inline constexpr int kLegacyFlagWidth = 64;
        inline constexpr int kLegacyFlagHeight = 32;
        inline constexpr size_t kLegacyFlagPayloadBytes = 0x100;
        inline constexpr size_t kLegacyFlagRowBytes = 8;
        struct FlagCatalogEntry
        {
            std::string fileName;
            std::string displayName;
            std::filesystem::path sourcePath;
        };
        void AppendUniquePath(std::vector<std::filesystem::path>& paths, const std::filesystem::path& candidate);
        std::vector<std::filesystem::path> GetCampaignContentRootCandidates(
            const std::filesystem::path& gameDir);
        bool RedirectCallTarget(uintptr_t callAddress,
                                       uintptr_t originalTarget,
                                       uintptr_t desiredTarget);
        bool ShouldEnableMultiplayerFlagUi();
        extern void* g_ActiveNicknameEntry;
        extern void* g_ActiveNicknameParent;
        extern bool g_FlagApplyPending;
        extern bool g_FlagPayloadReady;
        extern bool g_LobbyNicknameInputHookInstalled;
        extern void* g_NicknameEnterDispatchEntry;
        extern void* g_PendingNicknameConfirmationEntry;
        extern BzrNetNicknameResult g_PendingNicknameConfirmationResult;
        extern bool g_ReplaceNicknameOnNextInput;
        std::filesystem::path GetGeneratedFlagsDirectoryPath();
        bool TryGetLocalPlayerForFlags(void*& outPlayer);
        bool TryApplySelectedFlagThroughEngine(const char* source);
        bool TryApplyCachedFlagPayload(const char* source);
        void InstallBzrNetRouteObserverIfPossible();
        void InstallMapFilterExtrasIfEnabled();
        // Hands a character to the Create Game map search box while it is
        // being edited; false leaves it to the caller. mp_map_filter_extras.cpp.
        bool TryRouteMapSearchChar(uint8_t character, FnUiTextEntryAppendChar original, uint8_t& result);
        bool IsWidgetLiveChildOfParent(void* parent, void* widget);
        const char* EnsureInvalidThumbnailTextureName();
        void ShowNicknameApplyConfirmation(void* entry, BzrNetNicknameResult result);

        // --- Vehicle list mod fix (vehicle_list_mod_fix.cpp) -------------------
        struct VehicleAssetExceptionCacheEntry
        {
            char assetName[64];
            DWORD suppressUntil;
            DWORD lastSkipLogTick;
        };

        // --- Producer build menu (producer_build_menu.cpp) ---------------------
        inline constexpr size_t kProducerBuildMenuTokenLen = 8;
        struct ProducerBuildMenuEntry
        {
            bool hasValue = false;
            char token[kProducerBuildMenuTokenLen + 1] = {};
            int64_t packedToken = 0;
        };
        struct ProducerBuildMenuConfig
        {
            bool initialized = false;
            bool enabled = false;
            ProducerBuildMenuEntry recycler = {};
            ProducerBuildMenuEntry factory = {};
            ProducerBuildMenuEntry constructionRig = {};
            std::unordered_map<std::string, ProducerBuildMenuEntry> odfOverrides = {};
            std::unordered_map<std::string, ProducerBuildMenuEntry> odfFileEntries = {};
        };
        std::vector<std::filesystem::path> GetProducerOdfDirectoryCandidates();
        bool TryGetObjectOdfToken(void* objectPtr, char (&outToken)[kProducerBuildMenuTokenLen + 1]);
        extern ProducerBuildMenuConfig g_ProducerBuildMenuConfig;
        ProducerBuildMenuEntry NormalizeProducerBuildMenuToken(const char* value);
        // Drops every menu tree, cursor and stub mapping; the stub blocks
        // themselves are kept, since a stale mode value may still name one.
        void ResetProducerBuildMenuRuntime();

        // --- AutoSave load button and restart mission (autosave_restart.cpp) ---
        void ForgetAllChunkProxySceneResources(const wchar_t* reason);

        // --- MPAUTH diagnostic (diag_mpauth_trace.cpp) -------------------------
        inline constexpr size_t kOrdnanceObjOffset = 0x14;
        // Budgets for MPAUTH traces (opt-in).
        inline constexpr long kMpauthDwTraceBudgetDefault = 256;
        inline constexpr long kMpauthSplTraceBudgetDefault = 256;
        inline constexpr size_t kObjStateFlagsOffset = 0x14;
        const char* BoolText(bool value);
        bool TryGetEnvLong(const char* name, long& outValue);
        extern bool g_MpauthEnabled;
        extern bool g_MpauthHooksInstalled;
        extern thread_local bool g_MpauthInOrdnanceReceive;
        extern volatile long g_MpauthInstallRetryBudget;
        extern std::unordered_map<uint32_t, int> g_MpauthSplHitCounts;
        extern std::unordered_set<uint32_t> g_MpauthRecentDwRemovedIds;
        extern std::unordered_map<uint32_t, uint64_t> g_MpauthDwRemoveTick;
        extern std::unordered_map<uint32_t, int> g_MpauthDwDeletedRecord;
        void InitializeMpauthConfig();
        void InstallMpauthHooksIfPossible();

        // --- Vehicle skinning diagnostic (diag_vehicle_skinning.cpp) -----------
        struct ChunkBridgeSnapshot
        {
            void* directBridgeRoot = nullptr;
            void* directOgreEntity = nullptr;
            void* directOgreLight = nullptr;
            bool directProbeOk = false;
            void* legacyOwner = nullptr;
            void* ownerBridgeRoot = nullptr;
            void* ownerOgreEntity = nullptr;
            void* ownerOgreLight = nullptr;
            void* ownerObj = nullptr;
            void* ownerEntity = nullptr;
            void* gameObject = nullptr;
            bool ownerProbeOk = false;
            char ownerEntityBaseName[32] = {};
            char ownerOgreFilename[32] = {};
            char ownerResolvedMeshName[48] = {};
            bool ownerNameProbeOk = false;
        };
        inline constexpr size_t kChunkObjectIdentityMaxObjectsPerRefresh = 1024;
        ChunkBridgeSnapshot CaptureChunkBridgeSnapshot(const uint8_t* objectBytes);
        bool TryGetGameObjectMeshName(void* gameObject, char* outMeshName, size_t outMeshNameCapacity);
        bool TryGetGameObjectObj76(void* gameObject, void*& outObj76);
        extern volatile long g_VehicleSkinningTraceBudget;
        extern bool g_VehicleSkinningTraceEnabled;
        extern std::unordered_set<std::string> g_VehicleSkinningTraceFingerprints;
        extern DWORD g_VehicleSkinningTraceIntervalMs;
        extern DWORD g_VehicleSkinningTraceLastTick;
        void RefreshVehicleSkinningDiagnosticsIfNeeded();

        // --- Multiplayer vehicle flags (multiplayer_vehicle_flags.cpp) ---------
        // Ogre::Vector3 global holding the per-map render origin (terrain
        // center); every engine sim->render conversion subtracts it and
        // mirrors Z (render = simX-o.x, simY-o.y, -simZ-o.z). The
        // WorldRenderOrigin row; 0 when it is not bound.
        uintptr_t WorldRenderOriginAddr();
        using FnFlagDisplaySubmit = void(__thiscall*)(void*, void*);
        struct MultiplayerFlagRenderSet
        {
            uint64_t payloadHash = 0;
            std::string materialName;
            std::string resourceGroup;
            std::filesystem::path resourceDirectory;
            bool resourcesReady = false;
            void* sceneManager = nullptr;
            void* billboardSet = nullptr;
            std::vector<void*> billboards;
            size_t usedBillboards = 0;
        };
        int GetGameObjectTeamForLog(void* objectPtr);
        bool HasTerrainLineOfSight(double startX,
                                          double startY,
                                          double startZ,
                                          double endX,
                                          double endY,
                                          double endZ);
        extern FnFlagDisplaySubmit g_BzrFn_FlagDisplaySubmitOriginal;
        extern bool g_MultiplayerFlagRenderHookFailureLogged;
        extern bool g_MultiplayerFlagRenderHookInstalled;
        extern std::unordered_map<uint64_t, MultiplayerFlagRenderSet> g_MultiplayerFlagRenderSets;
        extern bool g_MultiplayerFlagRendererLoggedReady;
        void ForgetMultiplayerFlagSceneResources(const wchar_t* reason);
        void RenderMultiplayerFlags(void* /*camera*/);
        void MaybeDriveMultiplayerFlagRenderFallback();
        void InstallMultiplayerFlagRenderHookIfPossible();

        // --- Perceived-team reveal (perceived_team_reveal.cpp) -----------------
        // Fail-closed safe default: the perceived-team reveal tail is an
        // enhancement, not proven legacy parity, and its hook sites are
        // quarantined from normal registration on main. Shipping a default
        // of false ensures a failed or missing migration cannot leave the
        // experimental behavior enabled for this boot; a user who explicitly
        // wants it can still set AttackRevealPerceivedTeam=1.
        inline constexpr bool kAttackRevealEnabledDefault = false;
        // CORRECTED 2026-09-19. This was 0x220, which is a different field in
        // the tug/cargo path, so the owner walk below never once resolved an
        // owner and PreserveSprayEmitterOwner wrote a craft handle into live
        // engine state. The owner field is +0x224, taken from the engine's own
        // accessor pair rather than from inline stores that merely look like
        // one:
        //
        //   GameObject::SetOwner 0x0046FC40
        //     0x0046FC50 call 0x00462380 (GetHandle) on the argument
        //     0x0046FC58 mov [ecx+0x224], eax
        //     0x0046FC63 mov [edx+0x224], 0        (null owner branch)
        //   GameObject::GetOwner 0x004B0400
        //     0x004B040A mov ecx, [eax+0x224]
        //     0x004B0411 call 0x004DA060 (GetObj)
        //
        // Reached from the Lua bindings: the "SetOwner"/"GetOwner" name
        // literals at .rdata 0x0087C4E4/0x0087C4F0 are entries 0 and 1 of the
        // table at 0x00871D28, whose function pointers are 0x00500820 and
        // 0x00500860; those tail into the handle-level pair 0x005C89D0 /
        // 0x005C8A10, which call the two addresses above.
        //
        // Complete-object relative, unlike the GetTeam family: the call site at
        // 0x005AA91C does `mov ecx, this` / `sub ecx, 0x18` before calling
        // GetOwner, and re-adds 0x18 to the returned pointer before using it as
        // an interface. So this offset shares the base of
        // kGameObjectPerceivedTeamOffset and needs no rebasing.
        //
        // What +0x220 actually is: a tug/cargo claim handle. At 0x004A8229 the
        // engine tests it for zero, lazily fills it with the object's *own*
        // GetHandle when the carrier slot +0xFC is empty (0x004A8255), and
        // clears it again at 0x004A828A when the carrier at +0xF8 is not class
        // 'TUG ' (0x54554700). Writing a foreign handle there both fails to
        // record an owner and suppresses that initialization.
        inline constexpr size_t kGameObjectOwnerHandleOffset = 0x224;
        inline constexpr size_t kProcessOwnerObjectOffset = 0x34;
        void LogArenaPointerFields(const wchar_t* tag, void* object, size_t scanBytes);
        extern bool g_AttackRevealEnabled;
        extern volatile long g_AttackRevealTraceBudget;
        extern volatile long g_DamageRevealTraceBudget;
        extern bool g_OwnedObjectRevealFixActive;
        extern bool g_OwnedObjectRevealFixEnabled;
        extern volatile long g_OwnedObjectRevealTraceBudget;
        extern bool g_TraceDamageReveal;
        void RefreshAttackRevealState();
        void RevertAttackRevealToBaseline();
        void RefreshOwnedObjectRevealFixState();
        bool ShouldTraceOwnedObjectReveal();
        bool ShouldTraceAttackReveal();
        void RevealProcessOwnerPerceivedTeam(void* processPtr, const char* sourceTag);

        inline constexpr long kAttackRevealTraceBudgetDefault = 64;

        // Confirmed Redux defect: damage from a GameObject-owned child reveals
        // only that immediate child, leaving its owning craft disguised.
        // This restores the ownership walk for landed hits. It is gated out of
        // network games because perceivedTeam participates in simulation.
        inline constexpr bool kOwnedObjectRevealFixEnabledDefault = true;
        inline constexpr long kOwnedObjectRevealTraceBudgetDefault = 96;

        // --- Lifecycle seams (lifecycle_seams.cpp) -----------------------------
        inline constexpr int kBzrRunStateStarted = 5;
        inline constexpr int kBzrRunStateUnknown = -1;
        void DeactivateAllChunkProxySceneResources(const wchar_t* reason);
        void InstallSceneTeardownForgetHooksIfPossible();
        bool TryReadBzrRunState(int& value);
        void InstallMissionTransitionSeamIfPossible();
        void PinDirect3DModulesForShutdown();

        // --- Shield tower and mine team filters (team_filter_mines.cpp) --------
        inline constexpr uintptr_t kGogBuildingSimulateAddr = 0x0047FCB0;
        struct TeamFilterConfig;
        struct TeamFilterCache;
        struct TeamFilterConfig
        {
            bool parsed = false;
            bool affectAllies = true;
            bool affectEnemies = true;
        };
        struct TeamFilterCache
        {
            bool initialized = false;
            std::unordered_map<std::string, TeamFilterConfig> odfEntries = {};
        };
        struct ListNodePtrValue
        {
            ListNodePtrValue* next = nullptr;
            ListNodePtrValue* prev = nullptr;
            void* value = nullptr;
        };
        struct LegacyMat3
        {
            float right_x;
            float right_y;
            float right_z;
            float up_x;
            float up_y;
            float up_z;
            float front_x;
            float front_y;
            float front_z;
            uint32_t padding;
            double posit_x;
            double posit_y;
            double posit_z;
        };
        ProducerBuildMenuEntry NormalizeQuotedOdfToken(const char* value);
        const float* TryCallEntityGetPosition(void* gameObject);
        bool TryGetObjectWorldPositionFromObj76(void* obj76, float (&outPosition)[3]);
        bool TryNormalizeQuotedStringValue(const char* value,
                                                  char* out,
                                                  size_t outSize);
        bool TryParseBoolValue(const char* value, bool& out);
        bool TryResolveOdfFilePath(const char* odfToken, std::filesystem::path& outPath);
        extern bool g_MagnetMineSimulateHookInstalled;
        extern TeamFilterCache g_MagnetMineTeamFilterCache;
        extern bool g_MagnetZeroRangeGuardEnabled;
        extern volatile long g_MagnetZeroRangeLogBudget;
        extern bool g_ProximityMineSimulateHookInstalled;
        extern TeamFilterCache g_ProximityMineTeamFilterCache;
        extern bool g_ShieldTowerSimulateHookInstalled;
        extern TeamFilterCache g_ShieldTowerTeamFilterCache;
        void InstallShieldTowerTeamFilterHookIfPossible();
        void InstallMineTeamFilterHooksIfPossible();
        bool TryGetTeamFilterForObject(void* objectPtr, TeamFilterConfig& outConfig, TeamFilterCache& cache, const char* logTag);
        void RunShieldTowerFilteredSimulate(void* shieldTowerPtr, float dt);
        void RunMagnetMineFilteredSimulate(void* magnetMinePtr, float dt);
        void RunProximityMineFilteredSimulate(void* proximityMinePtr, float dt);

        // --- AI ODF tuning (ai_odf_tuning.cpp) ---------------------------------
        inline constexpr float kScrapRetargetPeriodDefault = 2.0f;
        inline constexpr float kScrapRetargetMinImprovementDefault = 25.0f;
        inline constexpr uintptr_t kGogTerrainGetIntersectionAddr = 0x00784620;
        struct RetargetPeriodState
        {
            float appliedDeadline = 0.0f;
            float period = 0.0f;
        };
        struct ScrapPathFailureState
        {
            float retryAfter = 0.0f;
            float x = 0.0f;
            float z = 0.0f;
        };
        struct ScrapRetargetState
        {
            uintptr_t owner = 0;
            float nextCheck = 0.0f;
            float pendingUntil = 0.0f;
            int incumbentHandle = 0;
            bool rescorePending = false;
        };
        struct AiTuningConfig;
        struct AiTuningConfig
        {
            bool parsed = false;
            bool bomberAiRole = false;
            bool legacyAiRole = false;
            bool hasEngageRangeAI = false;
            float engageRangeAI = 0.0f;
            bool hasWeaponRangeMinAI = false;
            float weaponRangeMinAI = 0.0f;
            bool derivedBomberWeaponRangeAI = false;
            bool hasRetargetPeriodAI = false;
            float retargetPeriodAI = 0.0f;
            bool hasStuckCheckPeriodAI = false;
            float stuckCheckPeriodAI = 0.0f;
            bool hasStuckReverseTimeAI = false;
            float stuckReverseTimeAI = 0.0f;
            bool hasStuckStrafeTimeAI = false;
            float stuckStrafeTimeAI = 0.0f;
            bool scrapPathingAI = false;
            bool hasScrapPathingAI = false;
            bool hasScrapPathLengthWeightAI = false;
            float scrapPathLengthWeightAI = 1.0f;
            bool hasScrapStraightDistanceWeightAI = false;
            float scrapStraightDistanceWeightAI = 0.05f;
            bool hasScrapPathFailPenaltyAI = false;
            float scrapPathFailPenaltyAI = 250.0f;
            bool hasScrapHardToGetCooldownAI = false;
            float scrapHardToGetCooldownAI = 10.0f;
            bool hasScrapSearchRadiusAI = false;
            float scrapSearchRadiusAI = 0.0f;
            bool hasScrapRetargetPeriodAI = false;
            float scrapRetargetPeriodAI = kScrapRetargetPeriodDefault;
            bool hasScrapRetargetMinImprovementAI = false;
            float scrapRetargetMinImprovementAI = kScrapRetargetMinImprovementDefault;
        };
        struct AiTuningCache
        {
            bool initialized = false;
            std::unordered_map<std::string, AiTuningConfig> odfEntries = {};
        };
        // Per-unit AI tuning override set at runtime through the EXU bridge.
        // Keyed by GameObject pointer; wins over ODF-level AiTuningConfig and
        // applies regardless of the g_AiOdfGameplayTuningEnabled master toggle
        // because each entry is an explicit script request for that unit.
        struct AiUnitTuningOverride
        {
            bool hasLegacyAi = false;
            bool legacyAi = false;
            bool hasEngageRange = false;
            float engageRange = 0.0f;
            bool hasWeaponRangeMin = false;
            float weaponRangeMin = 0.0f;
            bool hasRetargetPeriod = false;
            float retargetPeriod = 0.0f;
            bool hasKiteRanges = false;
            float kiteDesiredRange = 0.0f;
            float kiteEnterRange = 0.0f;
            float kiteExitRange = 0.0f;
            bool kitePreserveLos = false;
            float kiteStrafe = 0.0f;
            float kiteSwitchPeriod = 0.0f;
        };
        struct CombatKiteState
        {
            bool retreating = false;
            uintptr_t target = 0;
            int strafeDirection = 1;
            ULONGLONG nextStrafeSwitchMs = 0;
        };
        bool TryParseFloatValue(const char* value, float& out);
        bool VtableTypeNameMatches(uintptr_t vtableAddress, const char* expectedName);
        extern bool g_AiOdfGameplayTuningActive;
        extern AiTuningCache g_AiTuningCache;
        extern std::unordered_map<uintptr_t, AiUnitTuningOverride> g_AiUnitTuningOverridesByObject;
        extern volatile long g_AiUnitTuningTraceBudget;
        extern InlineDetour32 g_AttackTaskDoStateDetour;
        extern bool g_AttackTaskDoStateHookInstalled;
        extern bool g_BomberAiRangeActive;
        extern bool g_CalcRangeCraftHookInstalled;
        extern std::unordered_map<uintptr_t, CombatKiteState> g_CombatKiteStateByObject;
        extern volatile long g_CombatKiteTraceBudget;
        extern bool g_HowitzerUndeployedRetaliationFixActive;
        extern InlineDetour32 g_RecycleTaskDoGotoScrapDetour;
        extern bool g_RetargetPeriodHooksInstalled;
        extern std::unordered_map<uintptr_t, RetargetPeriodState> g_RetargetPeriodStateByProcess;
        extern std::unordered_map<uintptr_t, ScrapPathFailureState> g_ScrapPathFailuresByObject;
        extern bool g_ScrapPathScoreHookInstalled;
        extern volatile long g_ScrapPathTraceBudget;
        extern bool g_ScrapRetargetHookInstalled;
        extern std::unordered_map<uintptr_t, ScrapRetargetState> g_ScrapRetargetStateByTask;
        extern bool g_SmartScavengerPathingEnabled;
        bool TryGetAiTuningForObject(void* objectPtr, AiTuningConfig& outConfig);
        void InstallAiTuningHooksIfPossible();

        // --- Unit behaviour fixes (unit_behavior_fixes.cpp) --------------------
        extern bool g_ApcAlliedTargetDeployFixEnabled;
        extern bool g_ApcAlliedTargetDeployFixInstalled;
        extern FnScriptProducerPredicate g_BzrFn_ScriptCanBuildOriginal;
        extern FnScriptProducerPredicate g_BzrFn_ScriptIsBusyOriginal;
        extern bool g_ConstructorRecycleStaleTargetFixActive;
        extern bool g_ConstructorRecycleStaleTargetFixEnabled;
        extern bool g_ConstructorRecycleStaleTargetFixInstalled;
        extern volatile long g_ConstructorRecycleStaleTargetLogBudget;
        extern bool g_ConstructorRecycleStaleTargetMismatchLogged;
        extern bool g_ConstructorRemoteBuildFixActive;
        extern bool g_ConstructorRemoteBuildFixEnabled;
        extern bool g_ConstructorRemoteBuildFixInstalled;
        extern bool g_ConstructorRemoteBuildFixMismatchLogged;
        extern volatile long g_ConstructorRemoteBuildTraceBudget;
        extern bool g_ProducerScriptPredicateHooksEnabled;
        extern bool g_ProducerScriptPredicateHooksInstalled;
        extern InlineDetour32 g_ScriptCanBuildDetour;
        extern InlineDetour32 g_ScriptIsBusyDetour;
        extern bool g_SplinterUndeadFixActive;
        extern bool g_SplinterUndeadFixEnabled;
        extern volatile long g_SplinterUndeadTraceBudget;
        extern bool g_SprayBuildingSimulateHookInstalled;
        extern bool g_TugCargoPostLoadFixActive;
        extern bool g_TugCargoPostLoadFixEnabled;
        extern bool g_TugCargoPostLoadFixInstalled;
        extern volatile long g_TugCargoPostLoadLogBudget;
        void InstallProducerScriptPredicateHooksIfPossible();
        void InstallSplinterUndeadFixIfPossible();
        void InstallConstructorRecycleStaleTargetFixIfPossible();
        void InstallTugCargoPostLoadFixIfPossible();
        void RefreshApcAlliedTargetDeployFixState();
        void InstallApcAlliedTargetDeployFixIfPossible();
        bool ShouldTraceConstructorRemoteBuildFix();
        void InstallConstructorRemoteBuildFixIfPossible();

        inline constexpr long kSplinterUndeadTraceBudgetDefault = 32;
        inline constexpr long kConstructorRemoteBuildTraceBudgetDefault = 32;

        // --- UI and camera fixes (ui_camera_fixes.cpp) -------------------------
        inline constexpr int32_t kMultiRenderCountMax = 256;
        // Post-load quake replay fade (#57) helpers. All calls run on the game
        // thread: the arm hook replaces PostLoadScriptUtils' StartQuake call
        // and the fade tick runs from the EarthQuake::Simulate entry detour.
        using FnEarthQuakeSimulate = void(__fastcall*)(void* thisPtr, void* edx, float dt);
        extern bool g_BriefingScrollFixEnabled;
        extern bool g_BriefingScrollFixInstalled;
        extern bool g_CinematicSatelliteZoomFixEnabled;
        extern bool g_CinematicSatelliteZoomFixInstalled;
        extern volatile long g_CinematicSatelliteZoomLogBudget;
        extern InlineDetour32 g_EarthQuakeSimulateDetour;
        extern bool g_MultiRenderCountClampEnabled;
        extern bool g_MultiRenderCountClampInstalled;
        extern volatile long g_MultiRenderCountClampLogBudget;
        extern volatile long g_QuakeReplayArmed;
        extern bool g_QuakeReplayFadeEnabled;
        extern bool g_QuakeReplayFadeInstalled;
        extern long g_QuakeReplayFadeSeconds;
        extern bool g_TargetCamSatelliteFixEnabled;
        extern bool g_TargetCamSatelliteFixInstalled;
        extern volatile long g_TargetCamSatelliteLogBudget;
        extern bool g_ThumbnailBmpGuardEnabled;
        extern bool g_ThumbnailBmpGuardInstalled;
        void InstallBriefingScrollFixIfPossible();
        void InstallMultiRenderCountClampIfPossible();
        void InstallThumbnailBmpGuardIfPossible();
        extern FnEarthQuakeSimulate g_BzrFn_EarthQuakeSimulateOriginal;
        void InstallQuakeReplayFadeIfPossible();
        void InstallTargetCamSatelliteFixIfPossible();
        void InstallCinematicSatelliteZoomFixIfPossible();

        inline constexpr long kQuakeReplayFadeSecondsDefault = 5;

        // --- Lobby screen hooks (lobby_screen_hooks.cpp) -----------------------
        void InstallNicknameTextEntryInputHookIfPossible();
        void InstallMultiCreatePreviewFixIfPossible();

        // --- Craft bounds and frustum cull (ogre_entity_frustum_cull.cpp) ------
        extern bool g_EntityFrustumCullEnabled;
        extern bool g_FrustumCullCensusEnabled;
        extern bool g_RestoreCraftBoundsEnabled;
        extern bool g_BoundsTraceEnabled;
        void InstallEntityFrustumCullingIfEnabled();

        // --- Jump-sniping probe (diag_jump_snipe_probe.cpp) --------------------
        // GetPlayerHandle() — int __cdecl(). Verified on live GOG exe: reads
        // GameObject::userObject (via 0x417C70) + playerHandle global (0x02CC2BDC),
        // round-trips through GameObjectHandle::GetObj (0x462630) / GameObject::GetHandle
        // (0x477590). This is the inner void-overload the Lua wrapper (0x4FFCD0) calls on
        // its non-numeric branch, matching the 1.5 decomp. Previous 0x00514610 was WRONG
        // (mid-instruction, same failure class as the fixed GetObjByHandle).
        // Now the GetPlayerHandle engine_addresses row.
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
        extern bool g_JumpSnipeProbeInstalled;
        extern JumpSnipeProbeLogState g_JumpSnipeProbeLogState;
        void InstallJumpSnipingProbeIfRequested();

        // --- Global feature configuration (global_feature_config.cpp) ----------
        inline constexpr bool kSplinterUndeadFixEnabledDefault = true;
        inline constexpr float kSmartReticleRangeDefault = 500.0f;
        inline constexpr bool kConstructorRemoteBuildFixEnabledDefault = true;
        inline constexpr bool kBomberAiRangeEnabledDefault = false;
        inline constexpr bool kHowitzerUndeployedRetaliationFixEnabledDefault = true;
        // Master switch for the ODF-authored AI tuning keys (engageRangeAI,
        // weaponRangeMinAI, retargetPeriodAI, scrapPathingAI and friends).
        // Defaults ON: every path it gates additionally requires the ODF to
        // declare one of those keys, so content that does not author them --
        // the stock campaign included -- is completely unaffected.
        inline constexpr bool kAiOdfGameplayTuningEnabledDefault = true;
        inline constexpr bool kTurretAimPitchEnabledDefault = true;
        inline constexpr bool kAllowNeutralAttackOrdersDefault = false;
        // Pure instrumentation for the AIP construction program. Off by default
        // because it prints one line per AIP item name plus a one-shot dump of
        // the whole prereq universe; nothing about the game changes either way.
        inline constexpr bool kAipResolveTraceDefault = false;
        // Always-on fix: give a built class every producer that can make it,
        // instead of only the first one InitObjectClasses happened to reach.
        inline constexpr bool kAiMultiProducerMakersDefault = true;
        inline constexpr char kUserConfigFixesSection[] = "Fixes";
        extern bool g_AiOdfGameplayTuningEnabled;
        extern bool g_BomberAiRangeBaselineEnabled;
        extern bool g_BomberAiRangeEnabled;
        extern bool g_HowitzerUndeployedRetaliationFixEnabled;
        extern bool g_TurretAimPitchEnabled;
        void RefreshTurretAimPitchState();
        void RefreshAiOdfGameplayTuningState();
        void RefreshBomberAiRangeState();
        void RefreshSplinterUndeadFixState();
        void RefreshTugCargoPostLoadFixState();
        void RefreshConstructorRecycleStaleTargetFixState();
        void RefreshHowitzerUndeployedRetaliationFixState();
        void RefreshConstructorRemoteBuildFixState();
        void InitializeGlobalImprovementConfig();
        void RevertRegisteredFeaturesToBaseline();
        void TickMpGateReconcile();

        // --- Chunk payload resolution (chunk_payload_resolve.cpp) --------------
        struct ChunkObjectLinkProbe;
        struct ChunkCreateSourceTreeProbe;
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
        struct ChunkVdfMeshRef
        {
            char meshBase[48] = {};
            uint32_t type = 0;
        };
        inline constexpr const char* kChunkPayloadResourceRootName = "OpenShimChunkPayloads";
        inline constexpr const char* kChunkPayloadModRelativeDirName = "chunkMeshes";
        inline constexpr const char* kChunkPayloadModRelativeDirNameAlt = "Chunks";
        bool AcquireChunkLogSlot();
        void LogChunkDiagnostic(const char* component, const wchar_t* fmt, ...);
        extern char g_ActiveFragmentSourceOdfName[16];
        extern std::unordered_map<std::string, bool> g_ChunkPayloadMeshExistsCache;
        extern std::unordered_set<std::string> g_ChunkPayloadResolveFailureLogCache;
        extern std::vector<std::filesystem::path> g_ChunkPayloadResourceDirectories;
        extern bool g_EnableChunkMeshProxy;
        extern bool g_TraceChunkEffectRuntime;
        extern bool g_TraceChunkRender;
        std::filesystem::path GetChunkPayloadStockResourceDirectory();
        void RefreshChunkPayloadResourceDirectories();
        std::filesystem::path GetNativeChunkCacheDirectory();
        bool PrepareNativeChunkPayloads(void* entity, char* sourceName = nullptr, size_t capacity = 0);
        void ResetNativeChunkPayloads();

        // --- SkinnedGibs (skinned_gibs.cpp) --------------------------------
        // Person deaths become rigid per-limb gibs split at runtime from the
        // skinned mesh (or an authored gibs.txt payload), posed at the death
        // frame and simulated by the shim. [General] SkinnedGibs = 0 leaves
        // every path below inert.
        bool IsSkinnedGibsEnabled();
        // Inside ChunkEffect::FullFragmentObject (outermost call only).
        // Begin captures pose and returns true when this is a person it will
        // gib; End then spawns, hides the body and marks that call's legacy
        // chunks so the proxy renderer skips them.
        bool SkinnedGibsBeginFullFragment(void* chunkEffect, void* obj76, const float* velocity);
        void SkinnedGibsEndFullFragment(void* chunkEffect);
        void TickSkinnedGibs(void* chunkEffect, float dt);
        void SubmitSkinnedGibsToRenderQueue(void* renderQueue);
        void ForgetSkinnedGibSceneResources(const wchar_t* reason);
        void DeactivateSkinnedGibs(const wchar_t* reason);
        // PathBlockFaces (path_block.cpp): forget the per-mission blocker
        // registry and ODF cache. No-op when the hook is not installed.
        void ResetPathBlockState(const wchar_t* reason);
        bool IsSkinnedGibSuppressedChunk(const uint8_t* objectBytes, const void* geomRef);
        // Writes the default openshim_gib_flesh.material into the chunk cache
        // root unless a payload directory overrides it. Must run before the
        // payload resource group is initialised.
        void EnsureSkinnedGibFleshMaterial(
            const std::filesystem::path& cacheRoot,
            const std::vector<std::filesystem::path>& payloadDirectories);

        // ShellCasings (shell_casings.cpp): cosmetic casings ejected by
        // cannon-like weapons, simulated and drawn by the shim. [General]
        // ShellCasings = 0 leaves every path below inert.
        bool IsShellCasingsEnabled();
        void TickShellCasings(float dt);
        void SubmitShellCasingsToRenderQueue(void* renderQueue);
        void ForgetShellCasingSceneResources(const wchar_t* reason);
        void DeactivateShellCasings(const wchar_t* reason);
        // Writes the generated casing mesh and its default materials into
        // the chunk cache root (materials yield to a payload pack's own).
        // Must run before the payload resource group is initialised.
        void EnsureShellCasingAssets(
            const std::filesystem::path& cacheRoot,
            const std::vector<std::filesystem::path>& payloadDirectories);

        // Shim-owned mesh objects on the chunk payload group
        // (chunk_proxy_render.cpp), independent of ChunkMeshes.
        bool EnsureSkinnedGibResourceLocations();
        bool CreateShimOwnedMeshObject(const char* meshName, void*& outSceneManager, void*& outNode, void*& outEntity);
        bool ReplaceShimOwnedMeshEntity(void* sceneManager, void* node, void*& entity, const char* meshName);
        bool SetShimOwnedObjectTransform(
            void* node,
            void* entity,
            const float position[3],
            const float orientationWxyz[4],
            const float scale[3]);
        void HideShimOwnedObject(void* node, void* entity);
        bool SubmitShimOwnedEntityToRenderQueue(void* sceneManager, void* entity, void* renderQueue);

        // Gib payloads (native_chunk_runtime.cpp). Runtime pieces sit in their
        // bone's bind frame (offset = centre in that frame); authored pieces
        // sit in model space (offset = pivot), and are placed through the
        // bone's skinning transform instead.
        struct SkinnedGibPieceInfo
        {
            std::string resource;
            std::string boneName;
            uint16_t bone = 0;
            float offset[3] = {};
            float radius = 0.0f;
            bool weapon = false;
        };
        struct SkinnedGibModelInfo
        {
            bool authored = false;
            std::string source;
            std::vector<SkinnedGibPieceInfo> pieces;
        };
        bool TryCaptureEntityMeshIdentity(
            void* entity,
            char* outName,
            size_t nameCapacity,
            char* outGroup,
            size_t groupCapacity);
        bool PrepareSkinnedGibPayloads(const std::string& meshName, const std::string& group, SkinnedGibModelInfo& out);
        void ResetSkinnedGibPayloads();
        bool TryResolveGeneratedStockChunkFallback(const char* seed, char* out, size_t capacity);
        bool TryResolveNativeChunkPayload(const char* mesh, const char* geom,
            char* out, size_t capacity, bool& handled);
        // Once per new chunk: move its physical origin onto a generated
        // piece's centre. No-op for stock, external or uncentred payloads.
        // geomRef (optional) is the fragment's legacy geometry, whose
        // node-local bounds cross-check the piece frame in the log.
        bool RecenterNativeChunkObject(uint8_t* objectBytes, const char* payloadMeshName,
            const void* geomRef = nullptr);
        bool TryComputeChunkGeomLocalBounds(const void* geomRef, uint32_t& outCount,
            float outMin[3], float outMax[3]);
        std::string NormalizeChunkPayloadComponentName(const char* value);
        bool TryResolveChunkPayloadMeshResource(
            const ChunkObjectLinkProbe& probe,
            const char* preferredMeshName,
            const char* explicitGeomName,
            char* outMeshName,
            size_t outMeshNameCapacity);
        ChunkVdfAssetInfo& GetChunkVdfAssetInfoForMesh(const char* meshName);
        bool BuildChunkVdfSourceCandidateList(
            const char* meshName,
            const ChunkObjectLinkProbe& source,
            const ChunkObjectLinkProbe& parent,
            const ChunkObjectLinkProbe& sibling,
            const ChunkObjectLinkProbe& child,
            char* outText,
            size_t outTextCapacity);
        void PopulateChunkVdfCandidates(const char* meshName, ChunkObjectLinkProbe& probe);
        bool TryInferChunkMeshNameFromGeom(
            const char* geomName,
            uint32_t classId,
            char* outMeshName,
            size_t outMeshNameCapacity);
        void AppendAllChunkMeshBasesForGeom(
            const char* geomName,
            uint32_t classId,
            std::vector<std::string>& outMeshCandidates);
        bool ResolveChunkCreateMeshContext(
            const ChunkCreateSourceTreeProbe& probe,
            char* outMeshName,
            size_t outMeshNameCapacity);
        bool TryInferChunkMeshNameFromTree(
            const ChunkObjectLinkProbe& source,
            const ChunkObjectLinkProbe& parent,
            const ChunkObjectLinkProbe& sibling,
            const ChunkObjectLinkProbe& child,
            char* outMeshName,
            size_t outMeshNameCapacity);

        // --- Chunk identity (chunk_identity.cpp) -------------------------------
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
        inline constexpr uintptr_t kChunkEffectActiveCountOffset = 0x8028;
        bool TryGetChunkProxyPosition(const uint8_t* objectBytes, float& outX, float& outY, float& outZ);
        extern char g_ActiveFragmentSourceMeshName[48];
        extern std::unordered_map<uintptr_t, ChunkResolvedBindingEntry> g_ChunkResolvedBindingCache;
        extern DWORD g_ChunkResolvedBindingLastPruneTick;
        extern bool g_EnableChunkProxyDebug;
        bool TryReadInlineAsciiBuffer(
            const void* address,
            size_t maxInlineBytes,
            char* outText,
            size_t outTextCapacity);
        bool TryReadOwnerEntityNames(
            const void* ownerEntity,
            char* outEntityBaseName,
            size_t outEntityBaseNameCapacity,
            char* outOgreFilename,
            size_t outOgreFilenameCapacity,
            char* outResolvedMeshName,
            size_t outResolvedMeshNameCapacity);
        bool TryReadChunkGeomIdentity(
            const uint8_t* objectBytes,
            const void*& outGeomRef,
            char* outGeomName,
            size_t outGeomNameCapacity);
        bool TryReadChunkObjectSummary(
            const uint8_t* objectBytes,
            uint32_t& outClassId,
            uint32_t& outFlags,
            void*& outGeomRef,
            char* outGeomName,
            size_t outGeomNameCapacity,
            void*& outOwner);
        bool CaptureChunkObjectLinkProbe(const uint8_t* objectBytes, ChunkObjectLinkProbe& outProbe);
        void EraseChunkResolvedBinding(const uint8_t* objectBytes);
        const ChunkResolvedBindingEntry* FindChunkResolvedBindingEntryForGeom(
            const uint8_t* objectBytes,
            const char* liveGeomName);
        void StoreChunkResolvedBinding(
            const uint8_t* objectBytes,
            const ChunkCreateSourceTreeProbe& sourceTreeProbe);
        void TouchChunkResolvedBinding(const uint8_t* objectBytes);
        void PruneChunkResolvedBindingsIfNeeded();
        void PopulateChunkObjectLinkProbeFromIdentityCache(ChunkObjectLinkProbe& probe);
        bool CaptureChunkCreateSourceTreeProbe(
            const uint8_t* sourceBytes,
            ChunkCreateSourceTreeProbe& outProbe);
        bool TryReadChunkEffectCount(const uint8_t* thisBytes, uint32_t& outCount);
        void LogChunkCreateLifecycle(
            const wchar_t* tag,
            void* thisPtr,
            const uint8_t* sourceBytes,
            const float* positionVec,
            const float* velocityVec,
            uint8_t preserveFlag,
            uint32_t countBefore,
            uint32_t countAfter,
            const ChunkEffectActiveEntry* createdEntry,
            const ChunkCreateSourceTreeProbe* sourceTreeProbe);
        bool TryReadChunkObjectLinks(
            const uint8_t* objectBytes,
            const uint8_t*& outParent,
            const uint8_t*& outSibling,
            const uint8_t*& outChild);
        void RefreshChunkObjectIdentityCacheIfNeeded();

        // --- Chunk proxy rendering (chunk_proxy_render.cpp) --------------------
        inline constexpr uintptr_t kGogChunkEffectCreateChunkAddr = 0x00492AA0;
        inline constexpr uintptr_t kGogChunkEffectCreateChunkletAddr = 0x004927D0;
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
        inline constexpr uint32_t kClassIdChunk = 53;
        extern bool g_AllowUnsafeSteamChunkCreateHooks;
        extern InlineDetour32 g_ChunkEffectCreateChunkDetour;
        extern InlineDetour32 g_ChunkEffectCreateChunkletDetour;
        extern bool g_ChunkEffectCreateHooksInstalled;
        extern bool g_ChunkEffectCreateHooksLogged;
        extern bool g_ChunkEffectCreateHooksMismatchLogged;
        extern ULONGLONG g_ChunkEffectCreateHooksReadyTick;
        extern bool g_ChunkEffectCreateHooksWaitLogged;
        extern bool g_ChunkEffectFragmentHooksInstalled;
        extern InlineDetour32 g_ChunkEffectFullFragmentDetour;
        extern InlineDetour32 g_ChunkEffectPartialFragmentDetour;
        extern bool g_ChunkMeshProxyFailureLogged;
        extern bool g_ChunkMeshProxyInitLogged;
        extern DWORD g_ChunkMeshProxyLastRetryTick;
        extern bool g_ChunkMeshProxyWaitLogged;
        extern std::unordered_map<uintptr_t, uint32_t> g_ChunkObservedClassIds;
        extern bool g_ChunkPayloadResourceLocationsAttempted;
        extern bool g_ChunkPayloadResourceLocationsFailureLogged;
        extern bool g_ChunkPayloadResourceLocationsLogged;
        extern bool g_ChunkPayloadResourceLocationsReady;
        extern void* g_ChunkProxyBillboardSet;
        extern uint32_t g_ChunkProxyCapacity;
        extern float g_ChunkProxyDebugSize;
        extern bool g_ChunkProxyFailureLogged;
        extern bool g_ChunkProxyInitLogged;
        extern DWORD g_ChunkProxyLastRetryTick;
        extern std::vector<ChunkProxySlot> g_ChunkProxySlots;
        extern bool g_ChunkProxyWaitLogged;
        extern uint32_t g_ChunkTraceEntryLimit;
        extern bool g_EnableGenericChunkBatch;
        extern bool g_ForceGenericChunkBatchFailure;
        extern bool g_ForceGenericChunkNonUnitScale;
        extern std::string g_GenericChunkBatchBuiltMaterial;
        extern uint64_t g_GenericChunkBatchBuiltVersion;
        extern int g_GenericChunkBatchEligibility[2];
        extern int g_StockFallbackBatchEligibility[2];
        void ObserveChunkWorldQueueDriver();
        bool ChunkWorldQueueDriverIsActive();
        void WarmNativeChunkCaches();
        extern DWORD g_GenericChunkBatchLastLogTick;
        extern void* g_GenericChunkBatchManualObject;
        extern bool g_GenericChunkBatchRateDiagnostics;
        extern bool g_GenericChunkBatchReuseEnabled;
        extern bool g_GenericChunkBatchReuseObserveOnly;
        extern bool g_GenericChunkBatchRuntimeAvailable;
        extern void* g_GenericChunkBatchSceneManager;
        extern void* g_GenericChunkBatchSceneNode;
        extern bool g_GenericChunkBatchSectionCreated;
        extern bool g_GenericChunkBatchVisible;
        extern uint32_t g_LastChunkEffectLoggedCount;
        extern bool g_TraceChunkRenderVerbose;
        extern bool g_ChunkEventLogging;
        int FindChunkGeoEntryByKey(const BzrGeoLookup* lookup, uint32_t key);
        int FindFirstChunkGeoEntryWithHandle(const BzrGeoLookup* lookup);
        void MaybeLogDx11EnhancedLightingState();
        void SubmitChunkProxiesToRenderQueue(void* renderQueue);
        void TrackChunkProxyDebugObject(
            const uint8_t* objectBytes,
            uint32_t objectType,
            const void* activeHandle,
            const BzrGeoLookup* lookup);
        bool TryReadChunkEffectEntry(
            const uint8_t* thisBytes,
            uint32_t index,
            ChunkEffectActiveEntry& outEntry);
        void LogChunkEffectRuntimeSample(void* thisPtr, float dt);
        void TrackChunkEffectActiveEntries(void* thisPtr);
        void ReleaseChunkProxiesMissingFromActiveList(void* thisPtr);
        void NoteChunkClassTransition(const uint8_t* objectBytes, uint32_t classId);
        void LogChunkResolveSnapshot(
            const char* stage,
            const char* reason,
            const uint8_t* objectBytes,
            uint32_t variant,
            uint32_t stockResolved,
            const void* activeBefore,
            const void* activeAfter,
            const BzrGeoLookup* lookup,
            int selectedIndex,
            uint32_t selectedKey);
        void InstallChunkEffectCreateHooksIfRequested();
        void InstallChunkFragmentWalkHooksIfRequested();

        extern volatile long g_ChunkRenderLogBudget;

        // --- Chunk engine hooks (chunk_engine_hooks.cpp) -----------------------
        extern bool g_EnableChunkRenderFallback;
        extern bool g_EnablePartialFragmentBoneCollapse;

        // --- DynamicGeometry hooks (dynamic_geometry_hooks.cpp) ----------------
        extern InlineDetour32 g_DynamicGeometryPrepareDetour;

        // --- Satellite view limits (satellite_view_limits.cpp) ---------------
        extern float g_SatelliteZoomOutMultiplier;
        extern float g_SatelliteZoomOutMultiplierBaseline;
        extern float g_SatellitePanSpeedMultiplier;
        extern float g_SatellitePanSpeedMultiplierBaseline;
        float ClampSatelliteMultiplier(float value);
        void RefreshSatelliteViewState();
        void RevertSatelliteViewToBaseline();

        // --- Jump-snipe crouch fix (jump_snipe_crouch.cpp) -------------------
        extern bool g_JumpSnipeCrouchEnabled;
        extern bool g_JumpSnipeCrouchBaselineEnabled;
        void RefreshJumpSnipeCrouchPatchState();
        void RevertJumpSnipeCrouchToBaseline();

        // --- Under-attack alert and reticle popup (alert_reticle_modes.cpp) --
        extern bool g_UnderAttackAlertConfigInitialized;
        extern bool g_TargetReticlePopupConfigInitialized;
        void InitializeUnderAttackAlertConfig();
        void RevertUnderAttackAlertToBaseline();
        void InitializeTargetReticlePopupConfig();
        void RevertTargetReticlePopupToBaseline();

        // --- Ordnance velocity inheritance (ordnance_velocity.cpp) -----------
        extern bool g_OrdnanceVelocityInheritanceEnabled;
        extern bool g_OrdnanceVelocityInheritanceBaselineEnabled;
        void RefreshOrdnanceVelocityInheritanceState();
        void RevertOrdnanceVelocityInheritanceToBaseline();

        // --- Radar layout and size scale (radar_layout.cpp) ------------------
        extern bool g_RadarLayoutHookInstalled;
        extern float g_RadarSizeScale;
        extern float g_RadarSizeScaleBaseline;
        void InstallRadarLayoutHookIfPossible();
        float ClampRadarSizeScaleSetting(float scale);
        void RefreshRadarSizeScaleState();
        void RevertRadarSizeScaleToBaseline();

        // --- BZRNet route, UDP port and nickname (bzrnet_settings.cpp) -------
        inline constexpr size_t kBzrNetNicknameCapacity = 0x80; // last byte kept NUL
        void InitializeBzrNetConfig();
        int GetBzrNetUdpPort();
        bool IsBzrNetForceRelayActive();
        bool ReadBzrNetNickname(char* out, size_t outSize);
        BzrNetNicknameResult ApplyBzrNetNicknameAuthoritative(
            const char* requestedValue, const char* source);
        const char* BzrNetNicknameResultName(BzrNetNicknameResult result);
        bool IsAcceptedBzrNetNicknameResult(BzrNetNicknameResult result);

        // --- Global and unit turbo (global_turbo.cpp) ------------------------
        extern bool g_GlobalTurboConfigInitialized;
        void InitializeGlobalTurboConfig();
        void InstallUnitTurboHooksIfPossible();
        void RefreshGlobalTurboPatchState();
        void RevertGlobalTurboToBaseline();

        // --- Unit VO queue policy (unit_vo.cpp) ------------------------------
        extern bool g_UnitVoConfigInitialized;
        void InitializeUnitVoConfig();
        void InstallUnitVoQueueHooksIfPossible();
        void RevertUnitVoToBaseline();

        // --- Pilot team restore on boarding (pilot_team_restore.cpp) ----------
        void RefreshPilotTeamRestoreState();
        void RevertPilotTeamRestoreToBaseline();

        // --- Player pilot flashlight (pilot_flashlight.cpp) ------------------
        extern bool g_PilotFlashlightConfigInitialized;
        void InitializePilotFlashlightConfig();
        void RefreshPilotFlashlightState();
        void RevertPilotFlashlightToBaseline();
        void ForgetPilotFlashlight(const wchar_t* reason);
        void PilotFlashlightNotifyMissionRunStateChanged(bool enteringSimulation);
        bool IsPilotOnFoot(void* player);
    }
}
