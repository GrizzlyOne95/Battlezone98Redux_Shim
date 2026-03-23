#include "bzr_hooks.h"
#include "game_state.h"
#include "patches.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <array>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <filesystem>
#include <fstream>
#include <new>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    // ---------------------------------------------------------------------
    // Global state used by hooks/trampolines
    // ---------------------------------------------------------------------
    void* g_VehicleListContext = nullptr;
    void* g_VehicleListParam   = nullptr;

    void* g_BzrnetHostObj   = nullptr;
    void* g_BzrnetClientObj = nullptr;

    void* g_BanParentHost  = nullptr;
    void* g_BanParentClient = nullptr;
    void* g_BanButtonHost  = nullptr;
    void* g_BanButtonClient = nullptr;
    void* g_BanLabelHost   = nullptr;
    void* g_BanLabelClient = nullptr;
    void* g_FlagButtonHost = nullptr;
    void* g_FlagButtonClient = nullptr;
    void* g_FlagLabelHost = nullptr;
    void* g_FlagLabelClient = nullptr;
    void* g_HostUiParent = nullptr;
    void* g_ClientUiParent = nullptr;
    void* g_AutoSaveLoadParent = nullptr;
    void* g_AutoSaveLoadScreen = nullptr;
    void* g_AutoSaveLoadButton = nullptr;

    uint32_t g_BanFlag = 0;
    float g_BanX = 0.0f;
    float g_BanY = 0.0f;
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

    // ---------------------------------------------------------------------
    // BZR function pointers (GOG v2.2.301 addresses)
    // ---------------------------------------------------------------------
    using FnVehicleListSet = void(__thiscall*)(void* thisPtr, BzrString a, BzrString b);
    using FnVehicleListLoad = void(__thiscall*)(void* thisPtr, BzrString* name);
    using FnVehicleListStep = void(__thiscall*)(void* thisPtr);
    using FnVehicleListFinalize = void(__thiscall*)(void* thisPtr);

    using FnUiButtonCtor = void* (__thiscall*)(void* self,
                                               const char* label,
                                               float x, float y, float w, float h,
                                               uint32_t flags, void* parent, int a, int b);
    // The label ctor only cleans 8 stack arguments in v2.2.301.
    using FnUiLabelCtor = void* (__thiscall*)(void* self,
                                              const char* label,
                                              float x, float y, float w, float h,
                                              uint32_t flags, void* parent, int a);
    using FnUiSetStr = void(__thiscall*)(void* self, const char* str);
    using FnUiSetInt = void(__thiscall*)(void* self, void* param);
    using FnUiSetCb  = void(__thiscall*)(void* self, void* cb);
    using FnUiAddChild = void(__thiscall*)(void* parent, void* child, int flags);
    using FnUiDialogAction = void(__thiscall*)(void* thisPtr, int value);
    using FnPlayGlobalSound = int(__cdecl*)(const char* filename, uint32_t arg1, uint32_t arg2, uint32_t arg3);

    using FnGetSelected = void* (__thiscall*)(void* list);
    using FnCommandHandler = void(__cdecl*)(uint16_t id, const char* cmd);
    using FnHelpLog = void(__cdecl*)(void* obj, const char* text);
    using FnHelpUi = void(__cdecl*)(int channel, const char* text);
    using FnBanLookup = void* (__cdecl*)(uint16_t id);
    using FnIsHost = int(__cdecl*)();
    using FnAutoLoadShellGame = int(__cdecl*)();
    using FnLoadGameByPath = int(__cdecl*)(const char* path, char* outName, int outNameLen);
    using FnLoadScreenPrep = void(__cdecl*)();
    using FnFinalizeQueuedLoad = void(__cdecl*)();
    using FnSetShellState = void(__cdecl*)(int state);
    using FnBzrStringCtorFromCStr = void(__thiscall*)(BzrString* self, const char* text);
    using FnBzrStringDtor = void(__thiscall*)(BzrString* self);
    using FnLoadScreenClearSelection = void(__cdecl*)(BzrString* text);
    using FnMapFilter6 = uint32_t(__thiscall*)(void* thisPtr);
    using FnChunkResolve = uint32_t(__cdecl*)(void* objectPtr, uint32_t variant);
    using FnMapFilterScroll = void(__cdecl*)();
    using FnGetLocalPlayerNetId = uint16_t(__cdecl*)();
    using FnNetPlayerSetData = void(__thiscall*)(void* thisPtr, uint32_t slot, uint8_t* data, uint32_t len);
    using FnNetPlayerSetFlagBuffer = void(__thiscall*)(void* thisPtr, const uint8_t* data, uint32_t len);
    using FnSetMyFlag = void(__cdecl*)();
    struct BuildItem;
    using FnBuildItemInit = void(__cdecl*)(BuildItem& item, int64_t token);
    using FnBuildItemCleanup = void(__cdecl*)(BuildItem& item);
    using FnProducerModeCall = void* (__cdecl*)(void* producerPtr, int slot, int flags);
    using FnEngineFlameAddFlame = void(__thiscall*)(void* self, const void* transform, float scale);
    using FnEngineFlameControl = void(__thiscall*)(void* self);
    using FnEngineFlameSubmit = void(__thiscall*)(void* self, void* camera);
    using FnEngineFlameResolveTexture = int(__cdecl*)(BzrString* textureName);
    using FnHudSpriteLookup = int(__cdecl*)(const char* spriteName);
    using FnGetTeamNum = int(__cdecl*)(int handle);
    using FnExuGetTeamEngineFlameColor = int(__cdecl*)(int team);
    using FnGameObjectGetTeam = int(__thiscall*)(void* thisPtr);
    using FnGameObjectRelation = bool(__thiscall*)(void* thisPtr, void* other);
    using FnChunkEffectSimulate = void(__thiscall*)(void* self, float dt);
    using FnGetPlayerHandle = int(__cdecl*)();
    using FnGameObjectGetObjByHandle = void* (__cdecl*)(int handle);
    using FnPersonSimulate = void(__thiscall*)(void* thisPtr, float dt);
    using FnShieldTowerSimulate = void(__thiscall*)(void* thisPtr, float dt);
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
    using FnOptionsInputCtor = void* (__thiscall*)(void* thisPtr);
    using FnRecordDeath = void(__cdecl*)(int killedTeam, int killerTeam);
    using FnCalcRangeCraft = void(__cdecl*)(void* craft,
                                            float* closeRange,
                                            float* range,
                                            float* time,
                                            void** weapon);
    using FnProcessDoSubTask = bool(__thiscall*)(void* thisPtr);
    using FnAIUnitRemove = void(__cdecl*)(void* unitPtr);
    using FnAIBuildConstructionEnd = void(__cdecl*)(int teamId, int constructType);
    using FnAIBuildReservedAreaRemove = void(__cdecl*)(int teamId, int reservedArea);
    using FnAISpentCreditRefund = void(__cdecl*)(int teamId, void* buildingPtr, void* unitPtr);
    using FnUnitsSOrderStop = void(__cdecl*)(void* unitPtr);
    using FnAIBuildUnassignedCCAdd = void(__cdecl*)(void* teamPtr, void* unitPtr);

    static void** g_BzrPtr_945478 = nullptr;
    static void** g_BzrPtr_94548C = nullptr;
    static void** g_BzrPtr_94555C = nullptr;
    static void** g_BzrPtr_9456D0 = nullptr;
    static void** g_BzrPtr_94557C = nullptr;
    static void** g_BzrPtr_920168 = nullptr;
    static uint8_t* g_BzrPtr_CurrentUser = nullptr;

    static FnVehicleListSet g_BzrFn_VehicleListSet = nullptr;      // 0x0076B7A0
    static FnVehicleListFinalize g_BzrFn_VehicleListFinalize = nullptr; // 0x0076BA00
    static FnVehicleListLoad g_BzrFn_VehicleListLoad = nullptr;    // 0x00766900
    static FnVehicleListStep g_BzrFn_VehicleListRefresh1 = nullptr; // 0x007A3F80
    static FnVehicleListStep g_BzrFn_VehicleListRefresh2 = nullptr; // 0x007A4070

    static FnUiButtonCtor g_BzrFn_ButtonCtor = nullptr; // 0x007C2480
    static FnUiLabelCtor g_BzrFn_LabelCtor  = nullptr; // 0x007CC390
    static FnUiSetStr g_BzrFn_SetTextureOff = nullptr; // 0x007D2870
    static FnUiSetStr g_BzrFn_SetTextureOver = nullptr; // 0x007C2F10
    static FnUiSetStr g_BzrFn_SetTextureOn = nullptr; // 0x007C2E80
    static FnUiSetStr g_BzrFn_SetButtonLabel = nullptr; // 0x007C2950
    static FnUiSetStr g_BzrFn_SetTooltip = nullptr; // 0x007CC660
    static FnUiSetInt g_BzrFn_LabelState = nullptr; // 0x007CC5C0
    static FnUiSetCb g_BzrFn_SetOnClick = nullptr; // 0x007C23E0
    static FnUiSetCb g_BzrFn_SetOnHover = nullptr; // 0x007C23C0
    static FnUiAddChild g_BzrFn_AddChild = nullptr; // 0x007D2110
    static FnUiDialogAction g_BzrFn_UiDialogSetEnabled = nullptr; // 0x007C9170
    static FnUiDialogAction g_BzrFn_UiDialogAdvance = nullptr; // 0x007C7930

    static FnGetSelected g_BzrFn_GetSelected = nullptr; // 0x007CB1A0
    static FnCommandHandler g_BzrFn_CommandHandler = nullptr; // 0x006247A0
    static FnHelpLog g_BzrFn_HelpLog = nullptr; // 0x00821390
    static FnHelpUi g_BzrFn_HelpUi = nullptr;   // 0x007A47B0
    static FnBanLookup g_BzrFn_BanLookup = nullptr; // 0x005771B0
    static FnIsHost g_BzrFn_IsHost = nullptr; // 0x00572A60
    static FnAutoLoadShellGame g_BzrFn_AutoLoadShellGame = nullptr; // 0x004FDAB0
    static FnLoadGameByPath g_BzrFn_LoadGameByPath = nullptr; // 0x004FDFE0 (_load_bzone_game)
    static FnLoadScreenPrep g_BzrFn_LoadScreenPrep = nullptr; // 0x0078BB00
    static FnFinalizeQueuedLoad g_BzrFn_FinalizeQueuedLoad = nullptr; // 0x005D4980
    static FnSetShellState g_BzrFn_SetShellState = nullptr; // 0x00434170
    static FnBzrStringCtorFromCStr g_BzrFn_BzrStringCtorFromCStr = nullptr; // 0x00416EF0
    static FnBzrStringDtor g_BzrFn_BzrStringDtor = nullptr; // 0x00416F30
    static FnLoadScreenClearSelection g_BzrFn_LoadScreenClearSelection = nullptr; // 0x00482860
    static FnMapFilter6 g_BzrFn_MapFilter6 = nullptr; // 0x004200B0
    static FnChunkResolve g_BzrFn_ChunkResolve = nullptr; // 0x004E3620
    static FnMapFilterScroll g_BzrFn_MapFilterScrollUp = nullptr; // 0x007CB500
    static FnMapFilterScroll g_BzrFn_MapFilterScrollDown = nullptr; // 0x007CB540
    static FnGetLocalPlayerNetId g_BzrFn_GetLocalPlayerNetId = nullptr;
    static FnNetPlayerSetData g_BzrFn_NetPlayerSetData = nullptr;
    static FnNetPlayerSetFlagBuffer g_BzrFn_NetPlayerSetFlagBuffer = nullptr;
    static FnSetMyFlag g_BzrFn_SetMyFlag = nullptr;
    static FnBuildItemInit g_BzrFn_InitBuildItem = nullptr; // 0x0049F5C0
    static FnBuildItemCleanup g_BzrFn_CleanupBuildItem = nullptr; // 0x0049F880
    static FnProducerModeCall g_BzrFn_ProducerModeCallOriginal = nullptr;
    static FnEngineFlameAddFlame g_BzrFn_EngineFlameAddFlame = nullptr;
    static FnEngineFlameControl g_BzrFn_EngineFlameControl = nullptr;
    static FnEngineFlameSubmit g_BzrFn_EngineFlameSubmit = nullptr;
    static FnEngineFlameResolveTexture g_BzrFn_EngineFlameResolveTexture = nullptr;
    static FnHudSpriteLookup g_BzrFn_HudSpriteLookup = nullptr;
    static FnGetTeamNum g_BzrFn_GetTeamNum = nullptr;
    static FnExuGetTeamEngineFlameColor g_ExuFn_GetTeamEngineFlameColor = nullptr;
    static HMODULE g_ExuTeamEngineFlameColorModule = nullptr;
    static FnChunkEffectSimulate g_BzrFn_ChunkEffectSimulate = nullptr;
    static FnGetPlayerHandle g_BzrFn_GetPlayerHandle = nullptr;
    static FnGameObjectGetObjByHandle g_BzrFn_GameObjectGetObjByHandle = nullptr;
    static FnPersonSimulate g_BzrFn_PersonSimulate = nullptr;
    static FnShieldTowerSimulate g_BzrFn_ShieldTowerSimulateOriginal = nullptr;
    static FnShieldTowerSimulate g_BzrFn_BuildingSimulate = nullptr;
    static FnShieldTowerPowerUpdate g_BzrFn_ShieldTowerPowerUpdate = nullptr;
    static FnGameObjectRelation g_BzrFn_GameObjectFriendP = nullptr;
    static FnGameObjectRelation g_BzrFn_GameObjectEnemyP = nullptr;
    static FnMatrixInverse g_BzrFn_MatrixInverse = nullptr;
    static FnVectorTransform g_BzrFn_VectorTransform = nullptr;
    static FnRangeSearch g_BzrFn_CollisionRangeSearch = nullptr;
    static FnRangeResultsGetNext g_BzrFn_RangeResultsGetNext = nullptr;
    static FnOptionsInputCtor g_BzrFn_OptionsInputCtor = nullptr;
    static FnRecordDeath g_BzrFn_RecordDeath = nullptr;
    static FnCalcRangeCraft g_BzrFn_CalcRangeCraft = nullptr;
    static FnProcessDoSubTask g_BzrFn_OffensiveProcessDoSubTask = nullptr;
    static FnProcessDoSubTask g_BzrFn_GunTowerProcessDoSubTask = nullptr;
    static FnAIUnitRemove g_BzrFn_AIUnitRemove = nullptr;
    static FnAIBuildConstructionEnd g_BzrFn_AIBuildConstructionEnd = nullptr;
    static FnAIBuildReservedAreaRemove g_BzrFn_AIBuildReservedAreaRemove = nullptr;
    static FnAISpentCreditRefund g_BzrFn_AISpentCreditRefund = nullptr;
    static FnUnitsSOrderStop g_BzrFn_UnitsSOrderStop = nullptr;
    static FnAIBuildUnassignedCCAdd g_BzrFn_AIBuildUnassignedCCAdd = nullptr;
    static BuildItem* g_BzrBuildMenuRoot = nullptr;
    static bool g_IsSteamExe = false;

    void* __fastcall OptionsInputPopulateUiHook(void* thisPtr, void* /*edx*/);

    namespace
    {
        constexpr DWORD kDbgPrintExceptionAnsi = 0x40010006u;
        constexpr DWORD kDbgPrintExceptionWide = 0x4001000Au;
        constexpr DWORD kVehicleAssetRetryDelayMs = 1500u;
        constexpr size_t kVehicleAssetExceptionCacheSize = 8;
        constexpr float kAutoSaveLoadButtonX = 135.0f;
        constexpr float kAutoSaveLoadButtonY = 180.0f + (10.0f * 68.0f);
        constexpr float kAutoSaveLoadButtonW = 1100.0f;
        constexpr float kAutoSaveLoadButtonH = 58.0f;
        constexpr uint32_t kAutoSaveLoadButtonFlags = 0x22;
        constexpr int kBanScanMaxSessionId = 64;
        constexpr int kLoadQueuedState = 5;
        constexpr int kRestartMissionState = 6;
        constexpr int kLoadSaveState = 8;
        constexpr int kQueuedLoadNameBufferLen = 16;
        constexpr uintptr_t kLoadScreenSelectionFlagAddr = 0x00918133;
        constexpr uintptr_t kMissionSaveFlagAddr = 0x009173B7;
        constexpr uintptr_t kOldMissionModeAddr = 0x00918314;
        constexpr uintptr_t kUiScreenTypeAddr = 0x00918328;
        constexpr uintptr_t kQueuedLoadPathBufferAddr = 0x00945708;
        constexpr uintptr_t kQueuedLoadNameBufferAddr = 0x00915540;
        constexpr uintptr_t kBuildMenuRootAddr = 0x009174C4;
        constexpr char kBansConfigName[] = "bans.cfg";
        constexpr char kLegacyBanListName[] = "banlist.txt";
        constexpr char kFlagsConfigName[] = "flags.cfg";
        constexpr char kFlagsDirectoryName[] = "flags";
        constexpr char kFlagsGeneratedDirectoryName[] = "_generated";
        constexpr char kGeneratedFlagBmpName[] = "openshim_selected_flag.bmp";
        constexpr char kGeneratedFlagPayloadName[] = "openshim_selected_flag.bin";
        constexpr char kEngineFlagResourceRootName[] = "BZ_ASSETS";
        constexpr char kEngineFlagResourceDirectoryName[] = "OpenShimFlags";
        constexpr char kEngineFlagResourcePath[] = "OpenShimFlags/openshim_selected_flag.bmp";
        constexpr char kProducerBuildMenuIniName[] = "openshim_producer_build_menus.ini";
        constexpr char kProducerBuildMenuSection[] = "ProducerBuildMenus";
        constexpr char kProducerBuildMenuDefaultRoot[] = "build";
        constexpr size_t kProducerBuildMenuTokenLen = 8;
        constexpr uint32_t kRecyclerDistributedVft = 0x00417D74;
        constexpr uint32_t kRecyclerAttachableVft = 0x00417DCC;
        constexpr uint32_t kRecyclerFriendVft = 0x00417F68;
        constexpr uint32_t kRecyclerEnemyVft = 0x00417F9C;
        constexpr uint32_t kFactoryDistributedVft = 0x0040B71C;
        constexpr uint32_t kFactoryAttachableVft = 0x0040B774;
        constexpr uint32_t kArmoryDistributedVft = 0x004089C0;
        constexpr uint32_t kArmoryAttachableVft = 0x00408A18;
        constexpr uint32_t kConstructionRigDistributedVft = 0x0040A158;
        constexpr uint32_t kConstructionRigAttachableVft = 0x0040A1B0;
        constexpr size_t kEngineFlameObjectSize = 0x1250;
        constexpr size_t kEngineFlameFlamePtrOffset = 0x1228;
        constexpr size_t kEngineFlameFlameTextureOffset = 0x123C;
        constexpr size_t kEngineFlameControlVtableOffset = 0x18;
        constexpr size_t kEngineFlameSubmitVtableOffset = 0x20;
        constexpr size_t kCraftHandleLoOffset = 0x15C;
        constexpr size_t kCraftHandleHiOffset = 0x160;
        constexpr int kEngineFlameColorDefault = 0;
        constexpr int kEngineFlameColorBlue = 1;
        constexpr int kEngineFlameColorRed = 2;
        constexpr int kEngineFlameColorGreen = 3;
        constexpr uintptr_t kHudSpriteNameCountAddr = 0x00920F00;
        constexpr uintptr_t kHudSpriteNameTableAddr = 0x00920F08;
        constexpr size_t kHudSpriteNameEntrySize = 0x20;
        constexpr size_t kHudSpriteRectEntrySize = 0x30;
        constexpr size_t kHudSpriteRectXYWHOffset = 0x08;
        constexpr size_t kHudSpriteRectScanAlignment = 0x08;
        constexpr uint32_t kHudSpriteMaxReasonableCount = 4096;
        constexpr ULONGLONG kHudSpriteRectDiscoveryRetryMs = 10000;
        constexpr ULONGLONG kHudSpriteFallbackDiscoveryRetryMs = 15000;
        constexpr size_t kGameObjectClassOffset = 0xF8;
        constexpr size_t kGameObjectObjOffset = 0xF4;
        constexpr size_t kObjectClassOdfOffset = 0x20;
        constexpr size_t kObjectClassOdfLen = 16;
        constexpr size_t kObj76TransformOffset = 0x20;
        constexpr size_t kObj76GameObjectOffset = 0x8C;
        constexpr size_t kOrdnanceObjOffset = 0x14;
        constexpr size_t kOrdnanceSpeedOffset = 0x20;
        constexpr size_t kOrdnanceInvSpeedOffset = 0x24;
        constexpr size_t kOrdnanceVelocityOffset = 0x30;
        constexpr size_t kOrdnanceOwnerObjOffset = 0xCC;
        constexpr uintptr_t kOrdnanceListAddr = 0x0072665C;
        constexpr size_t kShieldTowerClassShieldMinXOffset = 0x160;
        constexpr size_t kShieldTowerClassShieldMaxXOffset = 0x16C;
        constexpr size_t kShieldTowerClassObjPushOffset = 0x178;
        constexpr size_t kShieldTowerClassObjDragOffset = 0x17C;
        constexpr size_t kShieldTowerClassOrdPushOffset = 0x180;
        constexpr size_t kShieldTowerClassOrdDragOffset = 0x184;
        constexpr size_t kShieldTowerPowerSourceOffset = 0x238;
        constexpr uintptr_t kCollisionRangeSearchAddr = 0x006A3E10;
        constexpr uintptr_t kGogShieldTowerSimulateAddr = 0x005D0D80;
        constexpr uintptr_t kGogBuildingSimulateAddr = 0x0047FCB0;
        constexpr uintptr_t kGogShieldTowerPowerUpdateAddr = 0x005D0CC0;
        constexpr uintptr_t kGogGameObjectFriendPAddr = 0x0046BF40;
        constexpr uintptr_t kGogGameObjectEnemyPAddr = 0x0046BFD0;
        constexpr uintptr_t kGogGameObjectAddVelocityAddr = 0x004A75B0;
        constexpr uintptr_t kGogMatrixInverseAddr = 0x008203F0;
        constexpr uintptr_t kGogVectorTransformAddr = 0x00820180;
        constexpr uintptr_t kGogRangeSearchAddr = 0x005B2950;
        constexpr uintptr_t kGogRangeResultsGetNextAddr = 0x00462710;
        constexpr uintptr_t kShieldTowerSimulateVtableSlotAddr = 0x00887728;
        constexpr float kFlagButtonSize = 48.0f;
        constexpr uint32_t kLegacyFlagDataSlot = 0x0Du;
        constexpr int kLegacyFlagWidth = 64;
        constexpr int kLegacyFlagHeight = 32;
        constexpr size_t kLegacyFlagPayloadBytes = 0x100;
        constexpr size_t kLegacyFlagRowBytes = 8;
        constexpr uintptr_t kFlagDisplayAddr = 0x006DDD34;
        constexpr uintptr_t kFlagFilePathBufferAddr = 0x00917FAC;
        constexpr size_t kFlagFilePathBufferCapacity = MAX_PATH;
        constexpr size_t kFlagDisplayFlagIndexOffset = 0x10;
        constexpr size_t kFlagDisplayMakeTextureOffset = 0x14;
        constexpr uintptr_t kGogPersonSimulateEntryAddr = 0x004F4370;
        constexpr uintptr_t kGogGetPlayerHandleAddr = 0x00514610;
        constexpr uintptr_t kGogGameObjectGetObjByHandleAddr = 0x0046B160;
        constexpr uintptr_t kGogRecordDeathEntryAddr = 0x004D9210;
        constexpr uintptr_t kSteam64GlobalAddr = 0x0260B1D0;
        // The shipped GOG PDB public-symbol addresses for cUI_OptionsInput methods
        // are not reliable function-entry hooks against the current Redux binary.
        // The stock input screen constructor was recovered from string xrefs instead.
        constexpr uintptr_t kOptionsInputCtorAddr = 0x007B25B0;
        constexpr uintptr_t kOptionsInputScreenFactoryCallerAddr = 0x007C8600;
        constexpr size_t kInlineDetourMaxPatchLen = 16;
        constexpr size_t kOptionsInputCtorDetourLen = 10;
        constexpr size_t kPersonSimulateDetourLen = 8;
        constexpr size_t kRecordDeathDetourLen = 6;
        constexpr ULONGLONG kCareerStatsMpHookRetryMs = 1000;
        constexpr ULONGLONG kCareerStatsMpHookRetryWindowMs = 15000;
        constexpr uint32_t kWeaponSigSnip = 0x534E4950u;
        constexpr size_t kPersonObjOffset = 0x0E8;
        constexpr size_t kPersonCarrierOffset = 0x198;
        constexpr size_t kGameObjectVelocityYOffset = 0x124;
        constexpr size_t kCraftStateOffset = 0x220;
        constexpr size_t kPersonCurAnimOffset = 0x288;
        constexpr size_t kPersonAnimHandleOffset = 0x28C;
        constexpr size_t kCarrierWeaponsOffset = 0x18;
        constexpr size_t kCarrierSelectedOffset = 0x30;
        constexpr size_t kWeaponClassOffset = 0x08;
        constexpr size_t kWeaponClassSigOffset = 0x0C;
        constexpr size_t kWeaponClassOdfOffset = 0x20;
        constexpr float kJumpSnipeVelocityBandThreshold = 0.15f;
        constexpr uintptr_t kGogCalcRangeCraftEntryAddr = 0x0041F240;
        constexpr size_t kCalcRangeCraftDetourLen = 8;
        constexpr uintptr_t kGogOffensiveProcessDoSubTaskEntryAddr = 0x004DFE70;
        constexpr size_t kOffensiveProcessDoSubTaskDetourLen = 8;
        constexpr uintptr_t kGogGunTowerProcessDoSubTaskEntryAddr = 0x004741A0;
        constexpr size_t kGunTowerProcessDoSubTaskDetourLen = 6;
        constexpr uintptr_t kGogAIUnitRemoveEntryAddr = 0x0068FC60;
        constexpr size_t kAIUnitRemoveDetourLen = 11;
        constexpr uintptr_t kGogAIBuildConstructionEndAddr = 0x006905D0;
        constexpr uintptr_t kGogAIBuildReservedAreaRemoveAddr = 0x00690920;
        constexpr uintptr_t kGogAISpentCreditRefundAddr = 0x00690020;
        constexpr uintptr_t kGogUnitsSOrderStopAddr = 0x00416280;
        constexpr uintptr_t kGogAIBuildUnassignedCCAddAddr = 0x00690770;
        constexpr uintptr_t kAiGameInitialisedAddr = 0x00930F08;
        constexpr uintptr_t kAiTeamTableAddr = 0x00920F04;
        constexpr uintptr_t kAiTeamDataBaseAddr = 0x02CE9B18;
        constexpr size_t kAiTeamDataStride = 0x1E0;
        constexpr size_t kUnitTypeOffset = 0x08;
        constexpr size_t kUnitTeamOffset = 0x10;
        constexpr size_t kUnitTypeAbilitiesOffset = 0x70;
        constexpr size_t kUnitAiConstructTypeOffset = 0x30;
        constexpr size_t kUnitAiConstructCostOffset = 0x34;
        constexpr size_t kUnitAiConstructingOffset = 0x38;
        constexpr size_t kUnitAiReservedAreaOffset = 0x3C;
        constexpr size_t kUnitAiAccountOffset = 0x40;
        constexpr uint32_t kConstructorAbilityMask = 0x2;
        constexpr bool kConstructorRemoteBuildFixEnabledDefault = true;
        constexpr long kConstructorRemoteBuildTraceBudgetDefault = 32;
        constexpr size_t kUnitProcessNextEnemyCheckOffset = 0x28;
        constexpr size_t kUnitProcessObjectOffset = 0x2C;

        struct InlineDetour32
        {
            uintptr_t target = 0;
            void* hook = nullptr;
            void* trampoline = nullptr;
            size_t patchLen = 0;
            std::array<uint8_t, kInlineDetourMaxPatchLen> original = {};
        };

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
            uint32_t craftState = 0;
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

        struct ConstructorCleanupSnapshot
        {
            int teamId = 0;
            void* teamPtr = nullptr;
            uint32_t constructType = 0;
            uint32_t constructCost = 0;
            uint32_t constructing = 0;
            uint32_t reservedArea = 0;
            uint32_t account = 0;
        };

        struct AiTuningConfig;
        static bool TryGetAiTuningForObject(void* objectPtr, AiTuningConfig& outConfig);
        static bool TryGetObjectOdfToken(void* objectPtr, char (&outToken)[kProducerBuildMenuTokenLen + 1]);
        struct ShieldTowerTeamFilterConfig;
        static bool TryGetShieldTowerTeamFilterForObject(void* objectPtr, ShieldTowerTeamFilterConfig& outConfig);
        static void RunShieldTowerFilteredSimulate(void* shieldTowerPtr, float dt);
        static void RevealProcessOwnerPerceivedTeam(void* processPtr, const char* sourceTag);

        struct HudSpriteRectRecord
        {
            uint32_t ref0 = 0;
            uint32_t ref4 = 0;
            int16_t x = 0;
            int16_t y = 0;
            int16_t w = 0;
            int16_t h = 0;
            float u0 = 0.0f;
            float v0 = 0.0f;
            float u1 = 0.0f;
            float v1 = 0.0f;
            uint8_t extra[0x10] = {};
        };

        struct HudSpriteKnownSample
        {
            const char* name = nullptr;
            float u0 = 0.0f;
            float v0 = 0.0f;
            float u1 = 0.0f;
            float v1 = 0.0f;
            int id = 0;
        };

        static_assert(sizeof(HudSpriteRectRecord) == 0x30, "Unexpected HUD sprite rect record size");

        static InlineDetour32 g_PersonSimulateDetour = {};
        static bool g_JumpSnipeProbeInstallAttempted = false;
        static bool g_JumpSnipeProbeInstalled = false;
        static JumpSnipeProbeLogState g_JumpSnipeProbeLogState = {};
        static HudSpriteRectRecord* g_HudSpriteRectTableBase = nullptr;
        static bool g_HudSpriteRectTableDiscoveryAttempted = false;
        static ULONGLONG g_HudSpriteRectTableDiscoveryLastTick = 0;
        static std::unordered_map<int, HudSpriteRectRecord> g_HudSpriteOriginalEntries;
        static std::unordered_map<int, HudSpriteRectRecord> g_HudSpriteHiddenEntries;
        static std::unordered_map<uintptr_t, HudSpriteRectRecord> g_HudSpriteOriginalEntriesByAddress;
        static std::unordered_set<uintptr_t> g_HudSpriteHiddenAddresses;
        static std::vector<uintptr_t> g_HudSpriteCachedPanelAddresses;
        static bool g_HudSpriteFallbackDiscoveryAttempted = false;
        static ULONGLONG g_HudSpriteFallbackDiscoveryLastTick = 0;

        enum class ProducerBuildMenuKind
        {
            Unknown,
            Recycler,
            Factory,
            Armory,
            ConstructionRig,
        };

        struct BanRecord
        {
            std::string id;
            std::string name;
        };

        struct FlagCatalogEntry
        {
            std::string fileName;
            std::string displayName;
            std::filesystem::path sourcePath;
        };

        struct LegacyFlagArtifactPaths
        {
            std::filesystem::path generatedDir;
            std::filesystem::path bmpPath;
            std::filesystem::path payloadPath;
        };

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
            ProducerBuildMenuEntry fallbackRoot = {};
            ProducerBuildMenuEntry recycler = {};
            ProducerBuildMenuEntry factory = {};
            ProducerBuildMenuEntry armory = {};
            ProducerBuildMenuEntry constructionRig = {};
            std::unordered_map<std::string, ProducerBuildMenuEntry> odfOverrides = {};
            std::unordered_map<std::string, ProducerBuildMenuEntry> odfFileEntries = {};
        };

        struct AiTuningConfig
        {
            bool parsed = false;
            bool bomberAiRole = false;
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
        };

        struct AiTuningCache
        {
            bool initialized = false;
            std::unordered_map<std::string, AiTuningConfig> odfEntries = {};
        };

        struct ShieldTowerTeamFilterConfig
        {
            bool parsed = false;
            bool affectAllies = true;
            bool affectEnemies = true;
        };

        struct ShieldTowerTeamFilterCache
        {
            bool initialized = false;
            std::unordered_map<std::string, ShieldTowerTeamFilterConfig> odfEntries = {};
        };

        struct ShieldTowerRangeSearchResults
        {
            uint8_t storage[48] = {};
        };

        struct ListNodePtrValue
        {
            ListNodePtrValue* next = nullptr;
            ListNodePtrValue* prev = nullptr;
            void* value = nullptr;
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

        enum class InputBindingMapFamily
        {
            Input,
            GameKey,
        };

        struct InputBindingCommandBlock
        {
            std::string command;
            std::string comment;
            std::vector<std::string> positiveKeyboardTokens;
            bool hasPositiveNonKeyboard = false;
        };

        struct InputBindingInventoryStats
        {
            size_t uniqueCommandBlocks = 0;
            size_t simpleKeyboardBlocks = 0;
            size_t keyboardChordBlocks = 0;
            size_t mixedBlocks = 0;
            size_t uniqueGameKeyActions = 0;
            size_t gameKeyChords = 0;
            size_t firstPassInputRows = 0;
            size_t firstPassGameKeyRows = 0;
        };

        struct GameKeyBindingAction
        {
            std::string action;
            std::vector<std::string> chords;
        };

        struct InputBindingRowSeed
        {
            const char* command = nullptr;
            const char* labelKey = nullptr;
            const char* displayText = nullptr;
        };

        struct InputBindingUiRow
        {
            InputBindingMapFamily family = InputBindingMapFamily::Input;
            std::string command;
            std::string displayLabelKey;
            std::string displayText;
            std::string currentBindingText;
            bool reserved = false;
            bool foundInMap = false;
            size_t matchingBlockCount = 0;
        };

        static bool g_BansConfigLoaded = false;
        static std::vector<BanRecord> g_BanRecords;
        static bool g_FlagCatalogLoaded = false;
        static std::vector<FlagCatalogEntry> g_FlagCatalog;
        static std::filesystem::path g_ActiveFlagsDirectory;
        static std::filesystem::path g_ConfigRequestedFlagsDirectory;
        static std::string g_SelectedFlagFileName;
        static int g_SelectedFlagIndex = -1;
        static std::string g_SelectedFlagStatus = "Legacy test path idle.";
        static std::string g_GeneratedFlagFileName;
        static std::string g_EngineStagedFlagFileName;
        static bool g_FlagPayloadReady = false;
        static bool g_FlagApplyPending = false;
        static std::array<uint8_t, kLegacyFlagPayloadBytes> g_SelectedFlagPayload = {};
        static ULONG_PTR g_GdiplusToken = 0;
        static bool g_GdiplusInitialized = false;

        struct VehicleAssetExceptionCacheEntry
        {
            char assetName[64];
            DWORD suppressUntil;
            DWORD lastSkipLogTick;
        };

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
            bool ownerProbeOk = false;
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

        struct OgreColourValue
        {
            float r;
            float g;
            float b;
            float a;
        };

        struct ChunkProxySlot
        {
            const uint8_t* objectBytes = nullptr;
            const void* geomRef = nullptr;
            char geomName[64] = {};
            float positionX = 0.0f;
            float positionY = 0.0f;
            float positionZ = 0.0f;
            bool useEntryPosition = false;
            void* billboard = nullptr;
            DWORD lastSeenTick = 0;
            bool active = false;
            bool billboardAssigned = false;
        };

        struct ChunkEffectActiveEntry
        {
            const uint8_t* objectBytes = nullptr;
            uint32_t reserved = 0;
            float positionX = 0.0f;
            float positionY = 0.0f;
            float positionZ = 0.0f;
            float velocityX = 0.0f;
            float velocityY = 0.0f;
            float velocityZ = 0.0f;
        };

        static bool g_EnableChunkRenderFallback = false;
        static bool g_EnableChunkProxyDebug = false;
        static bool g_TraceChunkRender = false;
        static bool g_TraceChunkRenderVerbose = false;
        static bool g_TraceChunkEffectRuntime = false;
        static bool g_TraceSatelliteVisibility = false;
        static uint32_t g_LastChunkEffectLoggedCount = UINT32_MAX;
        static volatile long g_ChunkRenderLogBudget = 12;
        static volatile long g_SatelliteVisibilityLogBudget = 8;
        static uint32_t g_ChunkTraceEntryLimit = 32;
        static uint32_t g_ChunkProxyCapacity = 96;
        static float g_ChunkProxyDebugSize = 2.5f;
        static uint32_t g_SatelliteVisibilityObjectLimit = 96;
        static DWORD g_SatelliteVisibilityLastTick = 0;
        static DWORD g_SatelliteVisibilityLogIntervalMs = 1000;
        static std::unordered_map<uintptr_t, uint32_t> g_ChunkObservedClassIds = {};
        static volatile long g_ArtilleryMaskTraceBudget = 400;
        static volatile long g_BomberRangeTraceBudget = 200;
        static VehicleAssetExceptionCacheEntry g_VehicleAssetExceptionCache[kVehicleAssetExceptionCacheSize] = {};
        static ProducerBuildMenuConfig g_ProducerBuildMenuConfig = {};
        static AiTuningCache g_AiTuningCache = {};
        static ShieldTowerTeamFilterCache g_ShieldTowerTeamFilterCache = {};
        static bool g_HasAppliedProducerBuildMenu = false;
        static int64_t g_LastAppliedProducerBuildMenu = 0;
        static uint32_t g_LastUnknownProducerVft = 0;
        static bool g_LoggedExuEngineFlameBridge = false;
        static bool g_LoggedExuEngineFlameBridgeMissing = false;
        static bool g_LoggedEngineFlameTargetFailure = false;
        static bool g_LoggedEngineFlameVtableHook = false;
        static bool g_EngineFlameVariantsInitialized = false;
        static bool g_EngineFlameVariantsInitAttempted = false;
        static bool g_EngineFlameVtableHooksInstalled = false;
        static InlineDetour32 g_OptionsInputPopulateUiDetour = {};
        static InlineDetour32 g_RecordDeathDetour = {};
        static bool g_CareerStatsMpHookInstalled = false;
        static bool g_CareerStatsMpHookInstallAttempted = false;
        static bool g_CareerStatsMpHookMismatchLogged = false;
        static ULONGLONG g_CareerStatsMpHookFirstAttemptTick = 0;
        static ULONGLONG g_CareerStatsMpHookLastAttemptTick = 0;
        static InlineDetour32 g_CalcRangeCraftDetour = {};
        static bool g_CalcRangeCraftHookInstalled = false;
        static InlineDetour32 g_OffensiveProcessDoSubTaskDetour = {};
        static InlineDetour32 g_GunTowerProcessDoSubTaskDetour = {};
        static bool g_RetargetPeriodHooksInstalled = false;
        static volatile long g_AttackRevealTraceBudget = 64;
        static InlineDetour32 g_AIUnitRemoveDetour = {};
        static bool g_ConstructorRemoteBuildFixInstalled = false;
        static bool g_ShieldTowerSimulateHookInstalled = false;
        static bool g_ConstructorRemoteBuildFixEnabled = kConstructorRemoteBuildFixEnabledDefault;
        static volatile long g_ConstructorRemoteBuildTraceBudget = kConstructorRemoteBuildTraceBudgetDefault;
        static std::unordered_map<uintptr_t, ULONGLONG> g_RetargetPeriodNextForceMsByProcess = {};
        static bool g_InputBindingUiScaffoldInitialized = false;
        static bool g_InputBindingUiScaffoldLogged = false;
        static bool g_InputBindingUiPopulateHookInstallAttempted = false;
        static bool g_InputBindingUiPopulateHookInstalled = false;
        static bool g_InputBindingUiPopulateHookMismatchLogged = false;
        static std::filesystem::path g_InputBindingInstallDirectory = {};
        static InputBindingInventoryStats g_InputBindingInventory = {};
        static std::vector<InputBindingCommandBlock> g_InputBindingCommandBlocks = {};
        static std::vector<GameKeyBindingAction> g_GameKeyBindingActions = {};
        static std::vector<InputBindingUiRow> g_InputBindingUiRows = {};
        static void* g_LastOptionsInputScreen = nullptr;
        static void InitializeInputBindingUiScaffold();
        static int g_EngineFlamePrimaryRedTexture = 0;
        static int g_EngineFlamePrimaryGreenTexture = 0;
        static void* g_EngineFlamePrimaryManager = nullptr;
        static void* g_EngineFlameSecondaryManager = nullptr;
        alignas(16) static unsigned char g_EngineFlamePrimaryRed[kEngineFlameObjectSize] = {};
        alignas(16) static unsigned char g_EngineFlamePrimaryGreen[kEngineFlameObjectSize] = {};
        alignas(16) static unsigned char g_EngineFlameSecondaryRed[kEngineFlameObjectSize] = {};
        alignas(16) static unsigned char g_EngineFlameSecondaryGreen[kEngineFlameObjectSize] = {};
        enum class UnderAttackAlertMode : int
        {
            None = 1,
            Minimal = 2,
            Normal = 3,
        };

        enum class TargetReticlePopupMode : int
        {
            Default = 1,
            NeutralOnly = 2,
            ExplicitOnly = 3,
        };

        static bool g_UnderAttackAlertConfigInitialized = false;
        static UnderAttackAlertMode g_UnderAttackAlertMode = UnderAttackAlertMode::Normal;
        static bool g_UnderAttackAlertEnabled = true;
        static float g_UnderAttackAlertCooldownSeconds = 1.0f;
        static float g_UnderAttackAlertNextAllowedTime = 0.0f;
        static constexpr const char* kUnderAttackAlertConfigName = "campaignReimagined_settings.cfg";
        static constexpr uintptr_t kUnderAttackAlertSoundAddr = 0x00877220;
        static constexpr uintptr_t kOgreSceneManagerStructureAddr = 0x00920EA0;
        static constexpr uintptr_t kOgreSceneManagerOffset = 0x08;
        static constexpr uintptr_t kChunkEffectActiveCountOffset = 0x8028;
        static constexpr uintptr_t kChunkEffectGateOffset = 0x802C;
        static constexpr uintptr_t kChunkEffectTuningBaseOffset = 0x8038;
        static constexpr uintptr_t kChunkEffectTemplateListOffset = 0x8050;
        static constexpr uintptr_t kChunkEffectEntryBaseOffset = 0x28;
        static constexpr uintptr_t kChunkEffectVtableSimulateSlotAddr = 0x0087708C;
        static constexpr uintptr_t kChunkObjGeomRefOffset = 0x64;
        static constexpr uintptr_t kViewRecordRva = 0x004FD770;
        static constexpr uintptr_t kGameObjectObjectListRva = 0x0050D2F0;
        static constexpr uintptr_t kGameObjectUserObjectRva = 0x0050D2F8;
        static constexpr uintptr_t kGameObjectUserTeamNumberRva = 0x0050D2E4;
        static constexpr size_t kChunkEffectEntrySize = 0x20;
        static constexpr uint32_t kClassIdChunk = 53;
        static constexpr DWORD kChunkProxyExpireMs = 400;
        static constexpr DWORD kChunkProxyRetryDelayMs = 1000;
        static constexpr float kChunkProxyHiddenY = -100000.0f;
        static constexpr const char* kChunkProxyBillboardSetName = "OpenShimChunkProxyDebug";
        static constexpr const char* kChunkProxyMaterialName = "BaseWhiteNoLighting";
        static constexpr const char* kChunkProxyMaterialGroup = "General";
        static FnPlayGlobalSound g_BzrFn_PlayGlobalSound =
            reinterpret_cast<FnPlayGlobalSound>(0x0043AA30);
        static bool g_TargetReticlePopupConfigInitialized = false;
        static TargetReticlePopupMode g_TargetReticlePopupMode = TargetReticlePopupMode::Default;
        static bool g_TargetReticlePopupSteamNeutralAllowed = false;
        static bool g_TargetReticlePopupSteamNeutralWarned = false;
        static constexpr bool kBomberAiRangeEnabledDefault = false;
        static constexpr bool kHowitzerVolleyEnabledDefault = false;
        static constexpr bool kWeaponMaskCarrierBiasEnabledDefault = false;
        static constexpr bool kAiOdfGameplayTuningEnabledDefault = false;
        static constexpr bool kTurretAimPitchEnabledDefault = false;
        static constexpr bool kAttackRevealEnabledDefault = true;
        static constexpr long kAttackRevealTraceBudgetDefault = 64;
        static bool g_BomberAiRangeEnabled = kBomberAiRangeEnabledDefault;
        static bool g_HowitzerVolleyEnabled = kHowitzerVolleyEnabledDefault;
        static bool g_WeaponMaskCarrierBiasEnabled = kWeaponMaskCarrierBiasEnabledDefault;
        static bool g_AiOdfGameplayTuningEnabled = kAiOdfGameplayTuningEnabledDefault;
        static bool g_TurretAimPitchEnabled = kTurretAimPitchEnabledDefault;
        static bool g_AttackRevealEnabled = kAttackRevealEnabledDefault;
        static constexpr InputBindingRowSeed kInputBindingFirstPassSeeds[] = {
            { "center_player", nullptr, "Center On Player" },
            { "center_recycler", nullptr, "Center On Recycler" },
            { "menu_up", nullptr, "Menu Up" },
            { "menu_down", nullptr, "Menu Down" },
            { "menu_back", nullptr, "Menu Back" },
            { "menu_press", nullptr, "Reticle Command" },
            { "group_select_0", nullptr, "Select Group 1" },
            { "group_select_1", nullptr, "Select Group 2" },
            { "group_select_2", nullptr, "Select Group 3" },
            { "group_select_3", nullptr, "Select Group 4" },
            { "group_select_4", nullptr, "Select Group 5" },
            { "group_select_5", nullptr, "Select Group 6" },
            { "group_select_6", nullptr, "Select Group 7" },
            { "turbo", nullptr, "Turbo" },
            { "throttle_up", nullptr, "Throttle Forward" },
            { "throttle_down", nullptr, "Throttle Back" },
            { "steer_left", nullptr, "Steer Left" },
            { "steer_right", nullptr, "Steer Right" },
            { "strafe_left", nullptr, "Strafe Left" },
            { "strafe_right", nullptr, "Strafe Right" },
            { "jump", nullptr, "Jump" },
            { "weapon_link", nullptr, "Link Weapons" },
            { "weapon_select_0", nullptr, "Weapon Slot 1" },
            { "weapon_select_1", nullptr, "Weapon Slot 2" },
            { "weapon_select_2", nullptr, "Weapon Slot 3" },
            { "weapon_select_3", nullptr, "Weapon Slot 4" },
            { "weapon_select_4", nullptr, "Weapon Slot 5" },
            { "eject", nullptr, "Eject" },
            { "abandon", nullptr, "Abandon Vehicle" },
            { "cloak", nullptr, "Cloak" },
            { "deploy", nullptr, "Deploy" },
            { "drop_beacon", nullptr, "Drop Beacon" },
            { "cycle_beacon", nullptr, "Cycle Beacon" },
            { "zoom_factor_plus", nullptr, "Zoom In" },
            { "zoom_factor_minus", nullptr, "Zoom Out" },
        };
        static constexpr size_t kGameObjectPlayerShotOffset = 0x1D8;
        static constexpr size_t kGameObjectGetTeamVtableOffset = 0x4;
        static constexpr size_t kGameObjectPerceivedTeamOffset = 0x180;
        static constexpr size_t kProcessOwnerObjectOffset = 0x34;
        static constexpr size_t kPresetViewCurrentViewOffset = 0x8;
        static constexpr size_t kGameObjectIlluminationOffset = 0xDC;
        static constexpr size_t kGameObjectIsVisibleOffset = 0x184;
        static constexpr size_t kGameObjectSeenOffset = 0x188;
        static constexpr size_t kGameObjectTargetHandleOffset = 0x214;
        static constexpr long kCameraTypeOverView = 3;
        static constexpr float kSuppressedRecentHitTime = -1.0e30f;
        static DWORD g_ChunkProxyLastRetryTick = 0;
        static bool g_ChunkProxyInitLogged = false;
        static bool g_ChunkProxyFailureLogged = false;
        static bool g_ChunkProxyWaitLogged = false;
        static void* g_ChunkProxyBillboardSet = nullptr;
        static std::vector<ChunkProxySlot> g_ChunkProxySlots = {};
        using FnOgreGetRootSceneNode = void*(__thiscall*)(void*);
        using FnOgreCreateBillboardSet = void*(__thiscall*)(void*, uint32_t);
        using FnOgreAttachObject = void(__thiscall*)(void*, void*);
        using FnOgreSetBillboardsInWorldSpace = void(__thiscall*)(void*, bool);
        using FnOgreSetDefaultDimensions = void(__thiscall*)(void*, float, float);
        using FnOgreCreateBillboard = void*(__thiscall*)(void*, float, float, float, const OgreColourValue&);
        using FnOgreSetBillboardPosition = void(__thiscall*)(void*, float, float, float);

        template<typename T>
        static T ResolveOgreProc(const char* name)
        {
            if (!name || !*name)
                return nullptr;

            static HMODULE ogreMain = nullptr;
            if (!ogreMain)
                ogreMain = GetModuleHandleA("OgreMain.dll");
            if (!ogreMain)
                return nullptr;

            return reinterpret_cast<T>(GetProcAddress(ogreMain, name));
        }

        static bool EnvFlagEnabled(const char* name)
        {
            if (!name || !*name)
                return false;

            char value[16] = {};
            const DWORD len = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
            if (len == 0 || len >= sizeof(value))
                return false;

            return value[0] != '0' && value[0] != '\0';
        }

        static bool ShouldEnableMultiplayerFlagUi()
        {
            static int s_cached = -1;
            if (s_cached < 0)
            {
                s_cached =
                    EnvFlagEnabled("OPENSHIM_ENABLE_MP_FLAG_UI") ||
                    EnvFlagEnabled("OPENSHIM_ENABLE_MULTIPLAYER_FLAG_UI") ||
                    EnvFlagEnabled("OPENSHIM_ENABLE_MP_FLAGS") ||
                    EnvFlagEnabled("BZR_ENABLE_MP_FLAG_UI") ? 1 : 0;
            }
            return s_cached != 0;
        }

        static bool TryGetEnvFloat(const char* name, float& outValue)
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

        static bool TryGetEnvLong(const char* name, long& outValue)
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

        static uintptr_t GetMainModuleBase()
        {
            static uintptr_t s_moduleBase = 0;
            if (s_moduleBase == 0)
                s_moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
            return s_moduleBase;
        }

        template<typename T>
        static T* ResolveMainModulePtr(uintptr_t rva)
        {
            const uintptr_t base = GetMainModuleBase();
            if (base == 0)
                return nullptr;
            return reinterpret_cast<T*>(base + rva);
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

        static int16_t ClampHudSpriteCoord(int value)
        {
            if (value < static_cast<int>(SHRT_MIN))
                return SHRT_MIN;
            if (value > static_cast<int>(SHRT_MAX))
                return SHRT_MAX;
            return static_cast<int16_t>(value);
        }

        static bool IsReadableDataProtect(DWORD protect)
        {
            if ((protect & PAGE_GUARD) != 0 || (protect & PAGE_NOACCESS) != 0)
                return false;

            switch (protect & 0xFFu)
            {
            case PAGE_READONLY:
            case PAGE_READWRITE:
            case PAGE_WRITECOPY:
            case PAGE_EXECUTE_READ:
            case PAGE_EXECUTE_READWRITE:
            case PAGE_EXECUTE_WRITECOPY:
                return true;
            default:
                return false;
            }
        }

        static bool TryReadHudSpriteNameCount(uint32_t& outCount)
        {
            __try
            {
                const uint32_t count = *reinterpret_cast<const uint32_t*>(kHudSpriteNameCountAddr);
                if (count == 0 || count > kHudSpriteMaxReasonableCount)
                    return false;

                outCount = count;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            return false;
        }

        static int LookupHudSpriteId(const char* name)
        {
            if (!name || !name[0])
                return 0;

            if (g_BzrFn_HudSpriteLookup)
            {
                __try
                {
                    const int id = g_BzrFn_HudSpriteLookup(name);
                    LogShimA(
                        LogLevel::Info,
                        "hudlookup",
                        "lookupFn=0x%p sprite=%s => id=%d",
                        reinterpret_cast<void*>(g_BzrFn_HudSpriteLookup),
                        name,
                        id);
                    if (id > 0)
                        return id;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    LogShimA(
                        LogLevel::Warn,
                        "hudlookup",
                        "lookupFn=0x%p sprite=%s raised exception",
                        reinterpret_cast<void*>(g_BzrFn_HudSpriteLookup),
                        name);
                }
            }

            uint32_t count = 0;
            if (!TryReadHudSpriteNameCount(count))
            {
                LogShimA(
                    LogLevel::Warn,
                    "hudlookup",
                    "fallback table unavailable for sprite=%s countAddr=0x%08X tableAddr=0x%08X",
                    name,
                    static_cast<unsigned>(kHudSpriteNameCountAddr),
                    static_cast<unsigned>(kHudSpriteNameTableAddr));
                return 0;
            }

            LogShimA(
                LogLevel::Info,
                "hudlookup",
                "fallback table search sprite=%s count=%u tableAddr=0x%08X",
                name,
                static_cast<unsigned>(count),
                static_cast<unsigned>(kHudSpriteNameTableAddr));

            __try
            {
                auto* table = reinterpret_cast<const char*>(kHudSpriteNameTableAddr);
                char entryName[kHudSpriteNameEntrySize + 1] = {};
                for (int index = static_cast<int>(count) - 1; index > 0; --index)
                {
                    const char* entry = table + (static_cast<size_t>(index) * kHudSpriteNameEntrySize);
                    std::memcpy(entryName, entry, kHudSpriteNameEntrySize);
                    entryName[kHudSpriteNameEntrySize] = '\0';
                    if (_stricmp(entryName, name) == 0)
                    {
                        LogShimA(
                            LogLevel::Info,
                            "hudlookup",
                            "fallback table sprite=%s => id=%d",
                            name,
                            index);
                        return index;
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                LogShimA(
                    LogLevel::Warn,
                    "hudlookup",
                    "fallback table search sprite=%s raised exception",
                    name);
            }

            LogShimA(
                LogLevel::Warn,
                "hudlookup",
                "sprite=%s not found by any lookup path",
                name);
            return 0;
        }

        static bool HudSpriteUvNearlyEqual(float a, float b)
        {
            return std::fabs(a - b) <= 0.0005f;
        }

        static bool ResolveHudSpriteKnownSamples(std::array<HudSpriteKnownSample, 6>& outSamples)
        {
            outSamples = {{
                {"scrap_panel", 660.0f / 1024.0f, 960.0f / 1024.0f, 840.0f / 1024.0f, 1024.0f / 1024.0f, 0},
                {"pilot_panel", 844.0f / 1024.0f, 960.0f / 1024.0f, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 0},
                {"sscrap_panel", 660.0f / 1024.0f, 960.0f / 1024.0f, 840.0f / 1024.0f, 1024.0f / 1024.0f, 0},
                {"spilot_panel", 844.0f / 1024.0f, 960.0f / 1024.0f, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 0},
                {"fscrap_panel", 660.0f / 1024.0f, 960.0f / 1024.0f, 840.0f / 1024.0f, 1024.0f / 1024.0f, 0},
                {"fpilot_panel", 844.0f / 1024.0f, 960.0f / 1024.0f, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 0},
            }};

            for (auto& sample : outSamples)
            {
                sample.id = LookupHudSpriteId(sample.name);
                if (sample.id <= 0)
                    return false;
            }

            return true;
        }

        static bool HudSpriteRecordMatches(const HudSpriteRectRecord& record, const HudSpriteKnownSample& sample)
        {
            return HudSpriteUvNearlyEqual(record.u0, sample.u0) &&
                   HudSpriteUvNearlyEqual(record.v0, sample.v0) &&
                   HudSpriteUvNearlyEqual(record.u1, sample.u1) &&
                   HudSpriteUvNearlyEqual(record.v1, sample.v1);
        }

        static bool ValidateHudSpriteRectTableBase(
            HudSpriteRectRecord* base,
            const std::array<HudSpriteKnownSample, 6>& samples)
        {
            if (!base)
                return false;

            __try
            {
                for (const auto& sample : samples)
                {
                    const HudSpriteRectRecord& record = base[sample.id];
                    if (!HudSpriteRecordMatches(record, sample))
                        return false;
                }

                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            return false;
        }

        static bool HudSpriteUvBlockMatches(const uint8_t* address, const HudSpriteKnownSample& sample)
        {
            if (!address)
                return false;

            __try
            {
                const float* uv = reinterpret_cast<const float*>(address);
                return HudSpriteUvNearlyEqual(uv[0], sample.u0) &&
                       HudSpriteUvNearlyEqual(uv[1], sample.v0) &&
                       HudSpriteUvNearlyEqual(uv[2], sample.u1) &&
                       HudSpriteUvNearlyEqual(uv[3], sample.v1);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            return false;
        }

        static bool IsLikelyHudSpriteRectRegion(const MEMORY_BASIC_INFORMATION& mbi);

        static bool IsStockScrapPilotPanelName(const char* name)
        {
            if (!name || !name[0])
                return false;

            return _stricmp(name, "scrap_panel") == 0 ||
                   _stricmp(name, "pilot_panel") == 0 ||
                   _stricmp(name, "sscrap_panel") == 0 ||
                   _stricmp(name, "spilot_panel") == 0 ||
                   _stricmp(name, "fscrap_panel") == 0 ||
                   _stricmp(name, "fpilot_panel") == 0;
        }

        static bool HudSpriteRecordMatchesStockScrapOrPilotUv(const HudSpriteRectRecord& record)
        {
            const HudSpriteKnownSample scrapSample = {
                "scrap_panel",
                660.0f / 1024.0f,
                960.0f / 1024.0f,
                840.0f / 1024.0f,
                1024.0f / 1024.0f,
                0
            };
            const HudSpriteKnownSample pilotSample = {
                "pilot_panel",
                844.0f / 1024.0f,
                960.0f / 1024.0f,
                1024.0f / 1024.0f,
                1024.0f / 1024.0f,
                0
            };

            return HudSpriteRecordMatches(record, scrapSample) ||
                   HudSpriteRecordMatches(record, pilotSample);
        }

        static bool HudSpriteRecordLooksLikeLivePanelRecord(const HudSpriteRectRecord& record)
        {
            return record.w > 0 &&
                   record.h > 0 &&
                   record.w <= 4096 &&
                   record.h <= 4096 &&
                   record.x >= -64 &&
                   record.y >= -64 &&
                   record.x <= 8192 &&
                   record.y <= 8192;
        }

        static bool DiscoverStockScrapPilotPanelRecordAddresses(std::vector<uintptr_t>& outAddresses)
        {
            outAddresses.clear();
            if (!g_HudSpriteCachedPanelAddresses.empty())
            {
                outAddresses = g_HudSpriteCachedPanelAddresses;
                return true;
            }

            const ULONGLONG now = GetTickCount64();
            if (g_HudSpriteFallbackDiscoveryAttempted &&
                now - g_HudSpriteFallbackDiscoveryLastTick < kHudSpriteFallbackDiscoveryRetryMs)
            {
                return false;
            }

            g_HudSpriteFallbackDiscoveryAttempted = true;
            g_HudSpriteFallbackDiscoveryLastTick = now;

            SYSTEM_INFO systemInfo = {};
            GetSystemInfo(&systemInfo);

            auto* cursor = static_cast<uint8_t*>(systemInfo.lpMinimumApplicationAddress);
            auto* maxAddress = static_cast<uint8_t*>(systemInfo.lpMaximumApplicationAddress);
            MEMORY_BASIC_INFORMATION mbi = {};
            while (cursor < maxAddress &&
                   VirtualQuery(cursor, &mbi, sizeof(mbi)) == sizeof(mbi))
            {
                auto* regionBase = static_cast<uint8_t*>(mbi.BaseAddress);
                auto* regionEnd = regionBase + mbi.RegionSize;
                cursor = regionEnd;

                if (!IsLikelyHudSpriteRectRegion(mbi))
                    continue;

                if (mbi.RegionSize < sizeof(HudSpriteRectRecord))
                    continue;

                for (size_t offset = 0; offset + sizeof(HudSpriteRectRecord) <= mbi.RegionSize; offset += sizeof(float))
                {
                    const auto* candidate = reinterpret_cast<const HudSpriteRectRecord*>(regionBase + offset);
                    HudSpriteRectRecord record = {};
                    __try
                    {
                        record = *candidate;
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        continue;
                    }

                    if (!HudSpriteRecordLooksLikeLivePanelRecord(record))
                        continue;

                    if (!HudSpriteRecordMatchesStockScrapOrPilotUv(record))
                        continue;

                    const uintptr_t address = reinterpret_cast<uintptr_t>(candidate);
                    if (g_HudSpriteOriginalEntriesByAddress.find(address) == g_HudSpriteOriginalEntriesByAddress.end())
                        g_HudSpriteOriginalEntriesByAddress.emplace(address, record);
                    outAddresses.push_back(address);
                }
            }

            std::sort(outAddresses.begin(), outAddresses.end());
            outAddresses.erase(std::unique(outAddresses.begin(), outAddresses.end()), outAddresses.end());
            if (!outAddresses.empty())
                g_HudSpriteCachedPanelAddresses = outAddresses;
            return !outAddresses.empty();
        }

        static bool WriteHudSpriteRectRecordAtAddress(uintptr_t address, const HudSpriteRectRecord& record)
        {
            if (address == 0)
                return false;

            auto* entry = reinterpret_cast<void*>(address);
            DWORD oldProtect = 0;
            if (!VirtualProtect(entry, sizeof(record), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;

            *reinterpret_cast<HudSpriteRectRecord*>(entry) = record;
            FlushInstructionCache(GetCurrentProcess(), entry, sizeof(record));

            DWORD restoreProtect = 0;
            VirtualProtect(entry, sizeof(record), oldProtect, &restoreProtect);
            return true;
        }

        static bool SetStockScrapPilotPanelsVisibleByUv(bool visible)
        {
            if (!visible)
            {
                if (!g_HudSpriteHiddenAddresses.empty())
                    return true;

                std::vector<uintptr_t> addresses;
                if (!DiscoverStockScrapPilotPanelRecordAddresses(addresses))
                {
                    LogShimA(LogLevel::Warn, "hudfallback", "no stock scrap/pilot panel records found");
                    return false;
                }

                bool anySucceeded = false;
                for (uintptr_t address : addresses)
                {
                    auto originalIt = g_HudSpriteOriginalEntriesByAddress.find(address);
                    if (originalIt == g_HudSpriteOriginalEntriesByAddress.end())
                        continue;

                    HudSpriteRectRecord hidden = originalIt->second;
                    hidden.w = 0;
                    hidden.h = 0;
                    if (WriteHudSpriteRectRecordAtAddress(address, hidden))
                    {
                        g_HudSpriteHiddenAddresses.insert(address);
                        anySucceeded = true;
                    }
                }

                LogShimA(
                    anySucceeded ? LogLevel::Info : LogLevel::Warn,
                    "hudfallback",
                    "hide stock scrap/pilot panels matches=%zu hidden=%zu",
                    addresses.size(),
                    g_HudSpriteHiddenAddresses.size());
                return anySucceeded;
            }

            if (g_HudSpriteHiddenAddresses.empty())
                return true;

            bool anySucceeded = false;
            for (const auto& entry : g_HudSpriteOriginalEntriesByAddress)
            {
                if (g_HudSpriteHiddenAddresses.find(entry.first) == g_HudSpriteHiddenAddresses.end())
                    continue;

                if (WriteHudSpriteRectRecordAtAddress(entry.first, entry.second))
                    anySucceeded = true;
            }

            if (anySucceeded)
                g_HudSpriteHiddenAddresses.clear();
            LogShimA(
                anySucceeded ? LogLevel::Info : LogLevel::Warn,
                "hudfallback",
                "restore stock scrap/pilot panels restored=%zu",
                anySucceeded ? g_HudSpriteOriginalEntriesByAddress.size() : 0u);
            return anySucceeded;
        }

        static void LogHudSpriteValidationSnapshot(
            const char* source,
            uintptr_t candidateBaseAddr,
            const std::array<HudSpriteKnownSample, 6>& samples)
        {
            static long s_budget = 6;
            if (InterlockedDecrement(&s_budget) < 0)
                return;

            char line[1024] = {};
            int written = _snprintf_s(
                line,
                _countof(line),
                _TRUNCATE,
                "%s base=0x%08X",
                source ? source : "candidate",
                static_cast<unsigned>(candidateBaseAddr));

            auto* base = reinterpret_cast<const HudSpriteRectRecord*>(candidateBaseAddr);
            for (const auto& sample : samples)
            {
                HudSpriteRectRecord record = {};
                bool readOk = false;
                __try
                {
                    record = base[sample.id];
                    readOk = true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }

                if (!readOk)
                {
                    written += _snprintf_s(
                        line + written,
                        _countof(line) - written,
                        _TRUNCATE,
                        " | %s#%d=<fault>",
                        sample.name ? sample.name : "?",
                        sample.id);
                    continue;
                }

                written += _snprintf_s(
                    line + written,
                    _countof(line) - written,
                    _TRUNCATE,
                    " | %s#%d=(%.3f,%.3f,%.3f,%.3f)",
                    sample.name ? sample.name : "?",
                    sample.id,
                    static_cast<double>(record.u0),
                    static_cast<double>(record.v0),
                    static_cast<double>(record.u1),
                    static_cast<double>(record.v1));
            }

            LogShimA(LogLevel::Info, "huddiscover", "%s", line);
        }

        static bool IsLikelyHudSpriteRectRegion(const MEMORY_BASIC_INFORMATION& mbi)
        {
            if (mbi.State != MEM_COMMIT || !IsReadableDataProtect(mbi.Protect))
                return false;

            // The rect table is runtime-owned data; avoid crawling image/code
            // mappings when a hide/show request arrives on the UI thread.
            switch (mbi.Type)
            {
            case MEM_PRIVATE:
            case MEM_MAPPED:
            case MEM_IMAGE:
                return true;
            default:
                return false;
            }
        }

        static bool DiscoverHudSpriteRectTableBase()
        {
            if (g_HudSpriteRectTableBase)
                return true;
            const ULONGLONG now = GetTickCount64();
            if (g_HudSpriteRectTableDiscoveryAttempted &&
                now - g_HudSpriteRectTableDiscoveryLastTick < kHudSpriteRectDiscoveryRetryMs)
                return false;

            g_HudSpriteRectTableDiscoveryAttempted = true;
            g_HudSpriteRectTableDiscoveryLastTick = now;

            std::array<HudSpriteKnownSample, 6> samples = {};
            if (!ResolveHudSpriteKnownSamples(samples))
            {
                Log(L"[HUD] Failed resolving stock HUD sprite ids needed for rect-table discovery\n");
                return false;
            }

            int maxSpriteId = 0;
            for (const auto& sample : samples)
            {
                if (sample.id > maxSpriteId)
                    maxSpriteId = sample.id;
            }

            const size_t requiredSpan =
                (static_cast<size_t>(maxSpriteId) * kHudSpriteRectEntrySize) + sizeof(HudSpriteRectRecord);
            const auto& first = samples.front();
            size_t regionsScanned = 0;
            size_t directRecordHits = 0;
            size_t uvBlockHits = 0;
            size_t validationFailures = 0;

            SYSTEM_INFO systemInfo = {};
            GetSystemInfo(&systemInfo);

            auto* cursor = static_cast<uint8_t*>(systemInfo.lpMinimumApplicationAddress);
            auto* maxAddress = static_cast<uint8_t*>(systemInfo.lpMaximumApplicationAddress);
            MEMORY_BASIC_INFORMATION mbi = {};
            while (cursor < maxAddress &&
                   VirtualQuery(cursor, &mbi, sizeof(mbi)) == sizeof(mbi))
            {
                auto* regionBase = static_cast<uint8_t*>(mbi.BaseAddress);
                auto* regionEnd = regionBase + mbi.RegionSize;
                cursor = regionEnd;

                if (!IsLikelyHudSpriteRectRegion(mbi))
                    continue;

                if (mbi.RegionSize < requiredSpan)
                    continue;

                ++regionsScanned;

                const uintptr_t regionAddress = reinterpret_cast<uintptr_t>(regionBase);
                size_t candidateOffset = 0;
                const size_t misalignment = regionAddress % kHudSpriteRectScanAlignment;
                if (misalignment != 0)
                    candidateOffset = kHudSpriteRectScanAlignment - misalignment;

                for (; candidateOffset + requiredSpan <= mbi.RegionSize;
                     candidateOffset += kHudSpriteRectScanAlignment)
                {
                    auto* candidateBase = reinterpret_cast<HudSpriteRectRecord*>(regionBase + candidateOffset);

                    __try
                    {
                        const HudSpriteRectRecord& record = candidateBase[first.id];
                        if (!HudSpriteRecordMatches(record, first))
                            continue;
                        ++directRecordHits;
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        continue;
                    }

                    if (!ValidateHudSpriteRectTableBase(candidateBase, samples))
                    {
                        ++validationFailures;
                        LogHudSpriteValidationSnapshot(
                            "direct-fail",
                            reinterpret_cast<uintptr_t>(candidateBase),
                            samples);
                        continue;
                    }

                    g_HudSpriteRectTableBase = candidateBase;
                    g_HudSpriteOriginalEntries.clear();
                    g_HudSpriteHiddenEntries.clear();
                    Log(L"[HUD] Sprite rect table discovered base=0x%08X scrap=%d pilot=%d sscrap=%d spilot=%d fscrap=%d fpilot=%d\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(candidateBase)),
                        samples[0].id,
                        samples[1].id,
                        samples[2].id,
                        samples[3].id,
                        samples[4].id,
                        samples[5].id);
                    return true;
                }

                const size_t uvScanSpan = sizeof(float) * 4;
                for (size_t uvOffset = 0; uvOffset + uvScanSpan <= mbi.RegionSize; uvOffset += sizeof(float))
                {
                    const uint8_t* candidateUv = regionBase + uvOffset;
                    if (!HudSpriteUvBlockMatches(candidateUv, first))
                        continue;
                    ++uvBlockHits;

                    const uintptr_t candidateBaseAddr =
                        reinterpret_cast<uintptr_t>(candidateUv) -
                        (static_cast<uintptr_t>(first.id) * kHudSpriteRectEntrySize) -
                        offsetof(HudSpriteRectRecord, u0);
                    auto* candidateBase = reinterpret_cast<HudSpriteRectRecord*>(candidateBaseAddr);
                    if (!ValidateHudSpriteRectTableBase(candidateBase, samples))
                    {
                        ++validationFailures;
                        LogHudSpriteValidationSnapshot(
                            "uv-fail",
                            candidateBaseAddr,
                            samples);
                        continue;
                    }

                    g_HudSpriteRectTableBase = candidateBase;
                    g_HudSpriteOriginalEntries.clear();
                    g_HudSpriteHiddenEntries.clear();
                    Log(L"[HUD] Sprite rect table discovered via UV scan base=0x%08X scrap=%d pilot=%d sscrap=%d spilot=%d fscrap=%d fpilot=%d\n",
                        static_cast<uint32_t>(candidateBaseAddr),
                        samples[0].id,
                        samples[1].id,
                        samples[2].id,
                        samples[3].id,
                        samples[4].id,
                        samples[5].id);
                    return true;
                }
            }

            LogShimA(
                LogLevel::Warn,
                "huddiscover",
                "failed regions=%zu directHits=%zu uvHits=%zu validationFailures=%zu firstId=%d requiredSpan=0x%zX",
                regionsScanned,
                directRecordHits,
                uvBlockHits,
                validationFailures,
                first.id,
                requiredSpan);
            Log(L"[HUD] Failed discovering sprite rect table in live process memory\n");
            return false;
        }

        static HudSpriteRectRecord* GetHudSpriteRectEntry(int spriteId)
        {
            if (spriteId <= 0)
                return nullptr;

            for (int attempt = 0; attempt < 2; ++attempt)
            {
                if (!g_HudSpriteRectTableBase && !DiscoverHudSpriteRectTableBase())
                    return nullptr;

                __try
                {
                    auto* entry = g_HudSpriteRectTableBase + spriteId;
                    volatile int16_t probe = entry->w;
                    (void)probe;
                    return entry;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    g_HudSpriteRectTableBase = nullptr;
                    g_HudSpriteRectTableDiscoveryAttempted = false;
                }
            }

            return nullptr;
        }

        static bool WriteHudSpriteRectEntry(int spriteId, const HudSpriteRectRecord& record)
        {
            auto* entry = GetHudSpriteRectEntry(spriteId);
            if (!entry)
                return false;

            DWORD oldProtect = 0;
            if (!VirtualProtect(entry, sizeof(record), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;

            *entry = record;
            FlushInstructionCache(GetCurrentProcess(), entry, sizeof(record));

            DWORD restoreProtect = 0;
            VirtualProtect(entry, sizeof(record), oldProtect, &restoreProtect);
            return true;
        }

        static bool TryGetHudSpriteCurrentRecord(int spriteId, HudSpriteRectRecord& outRecord)
        {
            auto* entry = GetHudSpriteRectEntry(spriteId);
            if (!entry)
                return false;

            __try
            {
                outRecord = *entry;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            return false;
        }

        static bool ResolveHudSpriteForMutation(const char* name, int& outId, HudSpriteRectRecord& outCurrent)
        {
            outId = LookupHudSpriteId(name);
            if (outId <= 0)
            {
                Log(L"[HUD] Unknown sprite '%hs'\n", name ? name : "<null>");
                return false;
            }

            if (!TryGetHudSpriteCurrentRecord(outId, outCurrent))
            {
                Log(L"[HUD] Failed reading live rect entry for sprite '%hs' (id=%d)\n",
                    name ? name : "<null>",
                    outId);
                return false;
            }

            if (g_HudSpriteOriginalEntries.find(outId) == g_HudSpriteOriginalEntries.end())
                g_HudSpriteOriginalEntries.emplace(outId, outCurrent);
            return true;
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
                TryReadAsciiString(geomNamePtr, outGeomName, outGeomNameCapacity);
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

        static void* GetOgreSceneManagerRuntime()
        {
            __try
            {
                auto* sceneManagerStructure =
                    *reinterpret_cast<uint8_t**>(kOgreSceneManagerStructureAddr);
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
                outRootNode = getRootSceneNode(sceneManager);
                if (outRootNode)
                    outBillboardSet = createBillboardSet(sceneManager, g_ChunkProxyCapacity);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
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
                setBillboardsInWorldSpace(billboardSet, true);
                setDefaultDimensions(billboardSet, g_ChunkProxyDebugSize, g_ChunkProxyDebugSize);
                attachObject(rootNode, billboardSet);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void* TryCreateChunkProxyBillboard(void* billboardSet, FnOgreCreateBillboard createBillboard, const OgreColourValue& color)
        {
            if (!billboardSet || !createBillboard)
                return nullptr;

            __try
            {
                return createBillboard(billboardSet, 0.0f, kChunkProxyHiddenY, 0.0f, color);
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
            float z)
        {
            if (!billboard || !setPosition)
                return false;

            __try
            {
                setPosition(billboard, x, y, z);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
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
                    Log(L"[CHUNKPROXY] Missing Ogre billboard symbols; proxy debug disabled for now\n");
                    g_ChunkProxyFailureLogged = true;
                }
                return false;
            }

            void* sceneManager = GetOgreSceneManagerRuntime();
            if (!sceneManager)
            {
                if (!g_ChunkProxyWaitLogged)
                {
                    Log(L"[CHUNKPROXY] Scene manager unavailable; waiting to initialize chunk proxy debug\n");
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
                    Log(L"[CHUNKPROXY] BillboardSet creation failed sceneManager=0x%08X root=0x%08X set=0x%08X\n",
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
                    Log(L"[CHUNKPROXY] BillboardSet setup fault set=0x%08X code=0x%08X\n",
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
                Log(L"[CHUNKPROXY] Initialized billboard debug set=0x%08X cap=%u size=%.2f\n",
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
                Log(L"[CHUNKPROXY] release obj=0x%08X billboard=0x%08X geom=0x%08X geomName=%hs geomKind=%hs reason=%ls\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.billboard)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.geomRef)),
                    GetChunkGeomNameForLog(slot.geomName),
                    ClassifyChunkGeomName(slot.geomName),
                    reason);
            }

            if (slot.billboardAssigned)
                HideChunkProxyBillboard(slot.billboard);
            slot.objectBytes = nullptr;
            slot.geomRef = nullptr;
            slot.geomName[0] = '\0';
            slot.positionX = 0.0f;
            slot.positionY = 0.0f;
            slot.positionZ = 0.0f;
            slot.useEntryPosition = false;
            slot.lastSeenTick = 0;
            slot.active = false;
            slot.billboardAssigned = false;
        }

        static void UpdateChunkProxySlotPosition(ChunkProxySlot& slot)
        {
            static FnOgreSetBillboardPosition setPosition =
                ResolveOgreProc<FnOgreSetBillboardPosition>("?setPosition@Billboard@Ogre@@QAEXMMM@Z");
            if (!slot.active || !slot.billboard || !setPosition)
                return;

            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
            if (slot.useEntryPosition)
            {
                x = slot.positionX;
                y = slot.positionY;
                z = slot.positionZ;
            }
            else if (!TryGetChunkProxyPosition(slot.objectBytes, x, y, z))
            {
                ReleaseChunkProxySlot(slot, L"transform-read-failed");
                return;
            }

            if (!TrySetChunkProxyBillboardPosition(slot.billboard, setPosition, x, y, z))
            {
                ReleaseChunkProxySlot(slot, L"billboard-set-failed");
                return;
            }

            if (!slot.billboardAssigned && AcquireChunkLogSlot())
            {
                Log(L"[CHUNKPROXY] assigned obj=0x%08X billboard=0x%08X geom=0x%08X geomName=%hs geomKind=%hs pos=(%.4f, %.4f, %.4f)\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.billboard)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.geomRef)),
                    GetChunkGeomNameForLog(slot.geomName),
                    ClassifyChunkGeomName(slot.geomName),
                    static_cast<double>(x),
                    static_cast<double>(y),
                    static_cast<double>(z));
            }
            slot.billboardAssigned = true;
        }

        static void TickChunkProxyDebug()
        {
            if (!g_EnableChunkProxyDebug)
                return;

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

                UpdateChunkProxySlotPosition(slot);
            }
        }

        static void TrackChunkProxyDebugEntry(
            const uint8_t* objectBytes,
            const void* geomRef,
            const char* geomName,
            float positionX,
            float positionY,
            float positionZ)
        {
            if (!g_EnableChunkProxyDebug || !objectBytes)
                return;

            if (g_ChunkProxySlots.size() != g_ChunkProxyCapacity)
                g_ChunkProxySlots.resize(g_ChunkProxyCapacity);

            ChunkProxySlot* freeSlot = nullptr;
            const DWORD now = GetTickCount();
            for (ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (slot.active && slot.objectBytes == objectBytes)
                {
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
            freeSlot->lastSeenTick = now;
            freeSlot->active = true;
            freeSlot->billboardAssigned = false;
            if (AcquireChunkLogSlot())
            {
                Log(L"[CHUNKPROXY] tracking obj=0x%08X geom=0x%08X geomName=%hs geomKind=%hs pos=(%.4f, %.4f, %.4f)\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectBytes)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(geomRef)),
                    GetChunkGeomNameForLog(geomName),
                    ClassifyChunkGeomName(geomName),
                    static_cast<double>(positionX),
                    static_cast<double>(positionY),
                    static_cast<double>(positionZ));
            }
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
                outEntry.positionX = *reinterpret_cast<const float*>(entryBytes + 0x08);
                outEntry.positionY = *reinterpret_cast<const float*>(entryBytes + 0x0C);
                outEntry.positionZ = *reinterpret_cast<const float*>(entryBytes + 0x10);
                outEntry.velocityX = *reinterpret_cast<const float*>(entryBytes + 0x14);
                outEntry.velocityY = *reinterpret_cast<const float*>(entryBytes + 0x18);
                outEntry.velocityZ = *reinterpret_cast<const float*>(entryBytes + 0x1C);
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

                Log(L"[CHUNKEFFECT] this=0x%08X dt=%.4f count=%u gate=0x%08X templateList=0x%08X templateCount=%u tune8038=%.4f tune8044=%.4f tune8048=%.4f\n",
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
                        Log(L"[CHUNKEFFECT]   entry[%u] fault\n", index);
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

                    Log(L"[CHUNKEFFECT]   entry[%u] obj=0x%08X reserved=0x%08X classId=%u flags=0x%08X owner=0x%08X timer=%.6f geom=0x%08X geomName=%hs geomKind=%hs pos=(%.4f, %.4f, %.4f) vel=(%.4f, %.4f, %.4f)\n",
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
                        static_cast<double>(entry.positionX),
                        static_cast<double>(entry.positionY),
                        static_cast<double>(entry.positionZ),
                        static_cast<double>(entry.velocityX),
                        static_cast<double>(entry.velocityY),
                        static_cast<double>(entry.velocityZ));
                }

                if (count > entryLimit)
                {
                    Log(L"[CHUNKEFFECT]   ... truncated %u additional entries\n",
                        count - entryLimit);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[CHUNKEFFECT] sample fault this=0x%08X code=0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)),
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        static void TrackChunkEffectActiveEntries(void* thisPtr)
        {
            if ((!g_EnableChunkProxyDebug && !g_TraceChunkEffectRuntime) || !thisPtr)
                return;

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

                    TrackChunkProxyDebugEntry(
                        entry.objectBytes,
                        geomRef,
                        geomName,
                        entry.positionX,
                        entry.positionY,
                        entry.positionZ);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        static ChunkBridgeSnapshot CaptureChunkBridgeSnapshot(const uint8_t* objectBytes)
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

                Log(L"[CHUNK]   obj76Probe parent=0x%08X sibling=0x%08X child=0x%08X classId=0x%X classPtr=0x%08X gameObj=0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parent)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sibling)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(child)),
                    classId,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(classPtr)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(gameObj)));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[CHUNK]   obj76Probe fault code=0x%08X\n",
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

                Log(L"[CHUNK] classChange obj=0x%08X old=0x%X new=0x%X parent=0x%08X sibling=0x%08X child=0x%08X classPtr=0x%08X gameObj=0x%08X\n",
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
                Log(L"[CHUNK] classChange obj=0x%08X old=0x%X new=0x%X probe=fault code=0x%08X\n",
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

            Log(L"[CHUNK] %hs obj=0x%08X variant=0x%08X resolved=0x%08X before=0x%08X after=0x%08X class=0x%04X classId=0x%X count=%u cached=0x%08X entries=0x%08X reason=%hs idx=%d key=0x%08X\n",
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

            Log(L"[CHUNK]   direct root=0x%08X entity=0x%08X light=0x%08X probe=%hs | owner=0x%08X ownerBridge=0x%08X ownerEntity=0x%08X ownerObj=0x%08X ownerOgre=0x%08X ownerLight=0x%08X ownerProbe=%hs\n",
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
                bridgeSnapshot.ownerProbeOk ? "ok" : "fault");

            LogChunkClassProbe(objectBytes);

            if (!lookup || !lookup->entries || lookup->count == 0)
                return;

            const uint32_t entryLimit = (std::min)(lookup->count, g_ChunkTraceEntryLimit);
            for (uint32_t index = 0; index < entryLimit; ++index)
            {
                const BzrGeoEntry& entry = lookup->entries[index];
                Log(L"[CHUNK]   entry[%u] key=0x%08X handle=0x%08X unk8=0x%08X unkC=0x%08X%s\n",
                    index,
                    entry.packedKey,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entry.handle)),
                    entry.unk8,
                    entry.unkC,
                    (selectedIndex == static_cast<int>(index)) ? " <selected>" : "");
            }

            if (lookup->count > entryLimit)
            {
                Log(L"[CHUNK]   ... truncated %u additional entries\n",
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

        static float ClampUnderAttackAlertCooldown(float value)
        {
            if (value < 0.0f)
                return 0.0f;
            if (value > 120.0f)
                return 120.0f;
            return value;
        }

        static std::filesystem::path GetConfigModuleDirectory()
        {
            char path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return {};

            return std::filesystem::path(path).parent_path();
        }

        static void AppendUniquePath(std::vector<std::filesystem::path>& paths, const std::filesystem::path& candidate)
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

        static std::vector<std::filesystem::path> GetCampaignContentRootCandidates(
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

        static char* TrimAsciiInPlace(char* text)
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

        static std::string NormalizeBanId(const char* value)
        {
            std::string normalized;
            if (!value)
                return normalized;

            normalized.reserve(32);
            for (const char* cursor = value; *cursor; ++cursor)
            {
                if (*cursor == '#' || *cursor == ';' ||
                    std::isspace(static_cast<unsigned char>(*cursor)))
                {
                    break;
                }

                normalized.push_back(
                    static_cast<char>(std::toupper(static_cast<unsigned char>(*cursor))));
            }

            return normalized;
        }

        static std::string BzrStringToStdString(const BzrString* value)
        {
            if (!value || value->size == 0)
                return {};

            return std::string(BzrStringData(value), value->size);
        }

        static bool TryReadSteam64Value(uint64_t& outValue)
        {
            outValue = 0;
            __try
            {
                outValue = *reinterpret_cast<volatile const uint64_t*>(kSteam64GlobalAddr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outValue = 0;
                return false;
            }

            return outValue != 0;
        }

        static std::filesystem::path GetCareerStatsPath()
        {
            return GetConfigModuleDirectory() / "career_stats.cfg";
        }

        static std::string SanitizeCareerStatsKeyToken(const std::string& value, const char* fallback)
        {
            std::string sanitized;
            sanitized.reserve(value.size());

            for (const char ch : value)
            {
                const unsigned char uch = static_cast<unsigned char>(ch);
                if (std::isalnum(uch) || ch == '.' || ch == '_' || ch == '-')
                {
                    sanitized.push_back(static_cast<char>(std::tolower(uch)));
                }
                else if (!sanitized.empty() && sanitized.back() != '_')
                {
                    sanitized.push_back('_');
                }
            }

            while (!sanitized.empty() && sanitized.front() == '_')
                sanitized.erase(sanitized.begin());
            while (!sanitized.empty() && sanitized.back() == '_')
                sanitized.pop_back();

            if (!sanitized.empty())
                return sanitized;

            return fallback ? fallback : "unknown";
        }

        static std::string ResolveCareerStatsProfileKey()
        {
            uint64_t steam64 = 0;
            if (TryReadSteam64Value(steam64))
                return SanitizeCareerStatsKeyToken(std::to_string(steam64), "offline");

            if (g_BzrFn_GetLocalPlayerNetId)
            {
                const uint16_t netId = g_BzrFn_GetLocalPlayerNetId();
                if (netId != 0)
                    return SanitizeCareerStatsKeyToken("netid_" + std::to_string(netId), "offline");
            }

            return "offline";
        }

        static void LoadCareerStatsFile(std::unordered_map<std::string, std::string>& outData)
        {
            outData.clear();

            const std::filesystem::path path = GetCareerStatsPath();
            std::ifstream input(path);
            if (!input.is_open())
                return;

            std::string line;
            while (std::getline(input, line))
            {
                const size_t split = line.find('=');
                if (split == std::string::npos || split == 0)
                    continue;

                std::string key = line.substr(0, split);
                std::string value = line.substr(split + 1);
                if (key.empty())
                    continue;

                outData[key] = value;
            }
        }

        static bool SaveCareerStatsFile(const std::unordered_map<std::string, std::string>& data)
        {
            const std::filesystem::path path = GetCareerStatsPath();
            std::ofstream output(path, std::ios::trunc);
            if (!output.is_open())
                return false;

            std::vector<std::string> keys;
            keys.reserve(data.size());
            for (const auto& entry : data)
                keys.push_back(entry.first);

            std::sort(keys.begin(), keys.end());
            for (const auto& key : keys)
            {
                const auto it = data.find(key);
                if (it == data.end())
                    continue;

                output << it->first << '=' << it->second << '\n';
            }

            return output.good();
        }

        static int GetCareerStatsInteger(const std::unordered_map<std::string, std::string>& data,
                                         const std::string& key)
        {
            const auto it = data.find(key);
            if (it == data.end())
                return 0;

            return std::atoi(it->second.c_str());
        }

        static void IncrementCareerStatsInteger(std::unordered_map<std::string, std::string>& data,
                                                const std::string& key,
                                                int amount)
        {
            data[key] = std::to_string(GetCareerStatsInteger(data, key) + amount);
        }

        static void RecordMultiplayerCareerStats(int killedTeam, int killerTeam)
        {
            if (!g_BzrFn_GetPlayerHandle || !g_BzrFn_GetTeamNum)
                return;

            const int playerHandle = g_BzrFn_GetPlayerHandle();
            if (playerHandle <= 0)
                return;

            const int localTeam = g_BzrFn_GetTeamNum(playerHandle);
            if (localTeam <= 0)
                return;

            const bool localDeath = (killedTeam == localTeam);
            // RecordDeath exposes team ids here; keep the first pass conservative
            // by suppressing same-team kills and counting only cross-team kills.
            const bool localKill = (killerTeam == localTeam && killerTeam > 0 && killerTeam != killedTeam);
            if (!localDeath && !localKill)
                return;

            std::unordered_map<std::string, std::string> data;
            LoadCareerStatsFile(data);
            data["meta.version"] = "1";

            const std::string profilePrefix = "profile." + ResolveCareerStatsProfileKey();
            if (localKill)
            {
                IncrementCareerStatsInteger(data, profilePrefix + ".career.totalKills", 1);
                IncrementCareerStatsInteger(data, profilePrefix + ".career.mpKills", 1);
            }
            if (localDeath)
            {
                IncrementCareerStatsInteger(data, profilePrefix + ".career.totalDeaths", 1);
                IncrementCareerStatsInteger(data, profilePrefix + ".career.mpDeaths", 1);
            }

            if (!SaveCareerStatsFile(data))
            {
                const std::string path = GetCareerStatsPath().string();
                Log(L"[CAREER] Failed writing multiplayer career stats file: %hs\n", path.c_str());
            }
        }

        static std::filesystem::path GetBansConfigPath()
        {
            return GetConfigModuleDirectory() / kBansConfigName;
        }

        static std::filesystem::path GetLegacyBanListPath()
        {
            return GetConfigModuleDirectory() / kLegacyBanListName;
        }

        static std::filesystem::path GetFlagsConfigPath()
        {
            return GetConfigModuleDirectory() / kFlagsConfigName;
        }

        static std::filesystem::path GetFlagsDirectoryPath()
        {
            return GetConfigModuleDirectory() / kFlagsDirectoryName;
        }

        static std::filesystem::path GetGeneratedFlagsDirectoryPath()
        {
            return GetFlagsDirectoryPath() / kFlagsGeneratedDirectoryName;
        }

        static std::filesystem::path GetEngineFlagResourceDirectoryPath()
        {
            return GetConfigModuleDirectory() /
                   kEngineFlagResourceRootName /
                   kEngineFlagResourceDirectoryName;
        }

        static std::filesystem::path GetEngineFlagResourceFilePath()
        {
            return GetEngineFlagResourceDirectoryPath() / kGeneratedFlagBmpName;
        }

        static LegacyFlagArtifactPaths GetLegacyFlagArtifactPaths()
        {
            LegacyFlagArtifactPaths paths = {};
            paths.generatedDir = GetGeneratedFlagsDirectoryPath();
            paths.bmpPath = paths.generatedDir / kGeneratedFlagBmpName;
            paths.payloadPath = paths.generatedDir / kGeneratedFlagPayloadName;
            return paths;
        }

        static std::string ToLowerAscii(std::string value)
        {
            for (char& ch : value)
            {
                ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            }
            return value;
        }

        static bool IsSupportedFlagSourcePath(const std::filesystem::path& path)
        {
            const std::string ext = ToLowerAscii(path.extension().string());
            return ext == ".bmp" || ext == ".png" || ext == ".tga" ||
                   ext == ".jpg" || ext == ".jpeg";
        }

        static std::vector<std::filesystem::path> GetFlagDirectoryCandidates()
        {
            std::vector<std::filesystem::path> candidates;

            const auto configDir = GetConfigModuleDirectory();
            if (configDir.empty())
                return candidates;

            candidates.push_back(configDir / kFlagsDirectoryName);

            for (const auto& root : GetCampaignContentRootCandidates(configDir))
            {
                AppendUniquePath(candidates, root / kFlagsDirectoryName);
                AppendUniquePath(candidates, root / "_Release" / kFlagsDirectoryName);
                AppendUniquePath(candidates, root / "_Source" / kFlagsDirectoryName);
            }
            return candidates;
        }

        static bool DirectoryContainsSupportedFlagSources(const std::filesystem::path& directory)
        {
            if (directory.empty())
                return false;

            std::error_code ec;
            if (!std::filesystem::exists(directory, ec) || ec)
                return false;

            for (std::filesystem::directory_iterator it(directory, ec), end;
                 !ec && it != end;
                 it.increment(ec))
            {
                if (ec)
                    break;

                const auto& entry = *it;
                if (!entry.is_regular_file(ec) || ec)
                    continue;
                if (IsSupportedFlagSourcePath(entry.path()))
                    return true;
            }

            return false;
        }

        static std::filesystem::path ResolveFlagSourceDirectoryPath()
        {
            if (!g_ConfigRequestedFlagsDirectory.empty())
            {
                std::error_code ec;
                if (std::filesystem::exists(g_ConfigRequestedFlagsDirectory, ec) && !ec)
                {
                    if (DirectoryContainsSupportedFlagSources(g_ConfigRequestedFlagsDirectory))
                        return g_ConfigRequestedFlagsDirectory;

                    return g_ConfigRequestedFlagsDirectory;
                }
            }

            const auto candidates = GetFlagDirectoryCandidates();
            for (const auto& candidate : candidates)
            {
                if (DirectoryContainsSupportedFlagSources(candidate))
                    return candidate;
            }

            for (const auto& candidate : candidates)
            {
                std::error_code ec;
                if (std::filesystem::exists(candidate, ec) && !ec)
                    return candidate;
            }

            return GetFlagsDirectoryPath();
        }

        static void InvalidateFlagPayloadCache()
        {
            g_FlagPayloadReady = false;
            g_FlagApplyPending = false;
            g_GeneratedFlagFileName.clear();
            g_EngineStagedFlagFileName.clear();
            g_SelectedFlagPayload.fill(0);
        }

        static bool EnsureEngineFlagResourceStaged(const char* source, std::string& outResourcePath)
        {
            if (g_SelectedFlagIndex < 0 ||
                static_cast<size_t>(g_SelectedFlagIndex) >= g_FlagCatalog.size())
            {
                return false;
            }

            const FlagCatalogEntry& entry = g_FlagCatalog[static_cast<size_t>(g_SelectedFlagIndex)];

            outResourcePath = kEngineFlagResourcePath;
            if (g_EngineStagedFlagFileName == entry.fileName)
                return true;

            const auto generatedBmpPath = GetLegacyFlagArtifactPaths().bmpPath;
            std::error_code ec;
            std::filesystem::create_directories(GetEngineFlagResourceDirectoryPath(), ec);
            if (ec)
            {
                Log(L"[FLAG] %hs failed ensuring staged engine flag directory path=%hs ec=%d\n",
                    source ? source : "flag",
                    GetEngineFlagResourceDirectoryPath().string().c_str(),
                    static_cast<int>(ec.value()));
                return false;
            }

            ec.clear();
            std::filesystem::copy_file(
                generatedBmpPath,
                GetEngineFlagResourceFilePath(),
                std::filesystem::copy_options::overwrite_existing,
                ec);
            if (ec)
            {
                Log(L"[FLAG] %hs failed staging engine flag resource src=%hs dst=%hs ec=%d\n",
                    source ? source : "flag",
                    generatedBmpPath.string().c_str(),
                    GetEngineFlagResourceFilePath().string().c_str(),
                    static_cast<int>(ec.value()));
                return false;
            }

            g_EngineStagedFlagFileName = entry.fileName;
            Log(L"[FLAG] %hs staged engine flag resource src=%hs dst=%hs resource=%hs\n",
                source ? source : "flag",
                generatedBmpPath.string().c_str(),
                GetEngineFlagResourceFilePath().string().c_str(),
                outResourcePath.c_str());
            return true;
        }

        static bool EnsureGdiplusInitialized(std::string& error)
        {
            if (g_GdiplusInitialized)
                return true;

            Gdiplus::GdiplusStartupInput startupInput;
            const Gdiplus::Status status =
                Gdiplus::GdiplusStartup(&g_GdiplusToken, &startupInput, nullptr);
            if (status != Gdiplus::Ok)
            {
                char buffer[128] = {};
                std::snprintf(buffer, sizeof(buffer), "GDI+ startup failed (status=%d)", static_cast<int>(status));
                error = buffer;
                return false;
            }

            g_GdiplusInitialized = true;
            return true;
        }

        static bool TryBuildLegacyFlagPayloadFromSource(
            const std::filesystem::path& sourcePath,
            std::array<uint8_t, kLegacyFlagPayloadBytes>& outPayload,
            std::string& error)
        {
            error.clear();
            outPayload.fill(0);

            std::string gdiplusError;
            if (!EnsureGdiplusInitialized(gdiplusError))
            {
                error = gdiplusError;
                return false;
            }

            const std::wstring widePath = sourcePath.wstring();
            Gdiplus::Bitmap original(widePath.c_str(), FALSE);
            if (original.GetLastStatus() != Gdiplus::Ok)
            {
                char buffer[512] = {};
                std::snprintf(
                    buffer,
                    sizeof(buffer),
                    "failed to load source image '%hs' (status=%d)",
                    sourcePath.string().c_str(),
                    static_cast<int>(original.GetLastStatus()));
                error = buffer;
                return false;
            }

            Gdiplus::Bitmap scaled(kLegacyFlagWidth, kLegacyFlagHeight, PixelFormat32bppARGB);
            if (scaled.GetLastStatus() != Gdiplus::Ok)
            {
                error = "failed to allocate scaled flag surface";
                return false;
            }

            {
                Gdiplus::Graphics graphics(&scaled);
                if (graphics.GetLastStatus() != Gdiplus::Ok)
                {
                    error = "failed to create GDI+ graphics context";
                    return false;
                }

                graphics.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
                graphics.SetCompositingQuality(Gdiplus::CompositingQualityHighQuality);
                graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
                graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
                graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
                graphics.Clear(Gdiplus::Color(0, 0, 0, 0));
                graphics.DrawImage(
                    &original,
                    Gdiplus::Rect(0, 0, kLegacyFlagWidth, kLegacyFlagHeight),
                    0,
                    0,
                    static_cast<INT>(original.GetWidth()),
                    static_cast<INT>(original.GetHeight()),
                    Gdiplus::UnitPixel);
            }

            struct PixelSample
            {
                uint8_t alpha;
                uint8_t luminance;
            };

            PixelSample samples[kLegacyFlagHeight][kLegacyFlagWidth] = {};
            int opaqueCount = 0;
            int darkCount = 0;
            for (int y = 0; y < kLegacyFlagHeight; ++y)
            {
                for (int x = 0; x < kLegacyFlagWidth; ++x)
                {
                    Gdiplus::Color color;
                    if (scaled.GetPixel(x, y, &color) != Gdiplus::Ok)
                    {
                        error = "failed reading scaled flag pixels";
                        return false;
                    }

                    const uint8_t alpha = color.GetA();
                    const uint8_t luminance = static_cast<uint8_t>(
                        ((299u * color.GetR()) + (587u * color.GetG()) + (114u * color.GetB())) / 1000u);
                    samples[y][x] = { alpha, luminance };
                    if (alpha >= 64)
                    {
                        ++opaqueCount;
                        if (luminance < 200)
                            ++darkCount;
                    }
                }
            }

            const bool useAlphaOnly = (opaqueCount > 0) && (darkCount == 0);
            int enabledPixels = 0;
            for (int bmpRow = 0; bmpRow < kLegacyFlagHeight; ++bmpRow)
            {
                const int sourceY = (kLegacyFlagHeight - 1) - bmpRow;
                for (int x = 0; x < kLegacyFlagWidth; ++x)
                {
                    const PixelSample sample = samples[sourceY][x];
                    bool enabled = false;
                    if (useAlphaOnly)
                        enabled = sample.alpha >= 64;
                    else
                        enabled = sample.alpha >= 64 && sample.luminance < 200;

                    if (!enabled)
                        continue;

                    ++enabledPixels;
                    outPayload[static_cast<size_t>(bmpRow) * kLegacyFlagRowBytes + static_cast<size_t>(x / 8)] |=
                        static_cast<uint8_t>(0x80u >> (x & 7));
                }
            }

            if (enabledPixels == 0)
            {
                error = "source image converted to an empty mask";
                return false;
            }

            return true;
        }

        static bool WriteLegacyFlagBitmap(
            const std::filesystem::path& outputPath,
            const std::array<uint8_t, kLegacyFlagPayloadBytes>& payload,
            std::string& error)
        {
            error.clear();

            std::error_code ec;
            std::filesystem::create_directories(outputPath.parent_path(), ec);
            if (ec)
            {
                char buffer[256] = {};
                std::snprintf(buffer, sizeof(buffer), "failed to create output directory (%d)", static_cast<int>(ec.value()));
                error = buffer;
                return false;
            }

            FILE* file = nullptr;
            if (fopen_s(&file, outputPath.string().c_str(), "wb") != 0 || !file)
            {
                error = "failed to create generated BMP";
                return false;
            }

            unsigned char header[62] = {};
            auto write16 = [&header](size_t offset, uint16_t value)
            {
                header[offset + 0] = static_cast<unsigned char>(value & 0xFFu);
                header[offset + 1] = static_cast<unsigned char>((value >> 8) & 0xFFu);
            };
            auto write32 = [&header](size_t offset, uint32_t value)
            {
                header[offset + 0] = static_cast<unsigned char>(value & 0xFFu);
                header[offset + 1] = static_cast<unsigned char>((value >> 8) & 0xFFu);
                header[offset + 2] = static_cast<unsigned char>((value >> 16) & 0xFFu);
                header[offset + 3] = static_cast<unsigned char>((value >> 24) & 0xFFu);
            };

            header[0] = 'B';
            header[1] = 'M';
            write32(2, 62u + static_cast<uint32_t>(payload.size()));
            write32(10, 62u);
            write32(14, 40u);
            write32(18, kLegacyFlagWidth);
            write32(22, kLegacyFlagHeight);
            write16(26, 1u);
            write16(28, 1u);
            write32(34, static_cast<uint32_t>(payload.size()));
            write32(38, 2835u);
            write32(42, 2835u);
            write32(46, 2u);
            write32(50, 2u);

            // Palette: 0 = white, 1 = black. The engine only copies the bits.
            header[54] = 0xFF; header[55] = 0xFF; header[56] = 0xFF; header[57] = 0x00;
            header[58] = 0x00; header[59] = 0x00; header[60] = 0x00; header[61] = 0x00;

            const bool headerWritten = std::fwrite(header, 1, sizeof(header), file) == sizeof(header);
            const bool payloadWritten = std::fwrite(payload.data(), 1, payload.size(), file) == payload.size();
            std::fclose(file);

            if (!headerWritten || !payloadWritten)
            {
                error = "failed while writing generated BMP";
                return false;
            }

            return true;
        }

        static bool WriteLegacyFlagPayloadBin(
            const std::filesystem::path& outputPath,
            const std::array<uint8_t, kLegacyFlagPayloadBytes>& payload,
            std::string& error)
        {
            error.clear();

            FILE* file = nullptr;
            if (fopen_s(&file, outputPath.string().c_str(), "wb") != 0 || !file)
            {
                error = "failed to create generated payload";
                return false;
            }

            const bool written = std::fwrite(payload.data(), 1, payload.size(), file) == payload.size();
            std::fclose(file);
            if (!written)
            {
                error = "failed while writing generated payload";
                return false;
            }

            return true;
        }

        static void MarkFlagDisplayDirty()
        {
            auto* flagDisplay = reinterpret_cast<uint8_t*>(kFlagDisplayAddr);
            if (!flagDisplay)
                return;

            __try
            {
                const int flagIndex = *reinterpret_cast<int*>(flagDisplay + kFlagDisplayFlagIndexOffset);
                if (flagIndex != 0)
                    *(flagDisplay + kFlagDisplayMakeTextureOffset) = 1;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[FLAG] Failed to mark flag display dirty at 0x%08X\n", static_cast<uint32_t>(kFlagDisplayAddr));
            }
        }

        static bool TryGetLocalPlayerForFlags(void*& outPlayer)
        {
            outPlayer = nullptr;
            if (!g_BzrFn_GetLocalPlayerNetId || !g_BzrFn_BanLookup)
                return false;

            __try
            {
                const uint16_t localPlayerId = g_BzrFn_GetLocalPlayerNetId();
                outPlayer = g_BzrFn_BanLookup(localPlayerId);
                return outPlayer != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            outPlayer = nullptr;
            return false;
        }

        static void SortFlagCatalog()
        {
            std::sort(
                g_FlagCatalog.begin(),
                g_FlagCatalog.end(),
                [](const FlagCatalogEntry& a, const FlagCatalogEntry& b)
                {
                    return _stricmp(a.displayName.c_str(), b.displayName.c_str()) < 0;
                });
        }

        static bool SaveSelectedFlagConfig()
        {
            const auto configPath = GetFlagsConfigPath();
            const std::string configPathString = configPath.string();
            FILE* file = nullptr;
            if (fopen_s(&file, configPathString.c_str(), "w") != 0 || !file)
            {
                Log(L"[FLAG] Failed to write flag config path=%hs\n", configPathString.c_str());
                return false;
            }

            std::fprintf(file, "; OpenShim multiplayer vehicle flag selection\n");
            std::fprintf(file, "; Place source images in .\\flags\\ and click the lobby F button to cycle.\n");
            std::fprintf(file, "; Supported source formats: .bmp .png .tga .jpg .jpeg\n");
            std::fprintf(file, "selected=%s\n", g_SelectedFlagFileName.c_str());
            if (!g_ConfigRequestedFlagsDirectory.empty())
                std::fprintf(file, "sourceDir=%s\n", g_ConfigRequestedFlagsDirectory.string().c_str());
            if (!g_ActiveFlagsDirectory.empty())
                std::fprintf(file, "; activeSourceDir=%s\n", g_ActiveFlagsDirectory.string().c_str());
            if (!g_GeneratedFlagFileName.empty())
                std::fprintf(file, "; generatedFor=%s\n", g_GeneratedFlagFileName.c_str());
            std::fclose(file);
            Log(L"[FLAG] Wrote flag config path=%hs selected=%hs sourceDir=%hs activeDir=%hs\n",
                configPathString.c_str(),
                g_SelectedFlagFileName.c_str(),
                g_ConfigRequestedFlagsDirectory.empty() ? "" : g_ConfigRequestedFlagsDirectory.string().c_str(),
                g_ActiveFlagsDirectory.empty() ? "" : g_ActiveFlagsDirectory.string().c_str());
            return true;
        }

        static void SyncSelectedFlagIndex()
        {
            g_SelectedFlagIndex = -1;
            if (g_FlagCatalog.empty())
            {
                g_SelectedFlagFileName.clear();
                return;
            }

            if (!g_SelectedFlagFileName.empty())
            {
                for (size_t i = 0; i < g_FlagCatalog.size(); ++i)
                {
                    if (_stricmp(g_FlagCatalog[i].fileName.c_str(), g_SelectedFlagFileName.c_str()) == 0)
                    {
                        g_SelectedFlagIndex = static_cast<int>(i);
                        return;
                    }
                }
            }

            g_SelectedFlagIndex = 0;
            g_SelectedFlagFileName = g_FlagCatalog.front().fileName;
        }

        static void EnsureFlagCatalogLoaded()
        {
            if (g_FlagCatalogLoaded)
                return;

            g_FlagCatalogLoaded = true;
            g_FlagCatalog.clear();
            g_ActiveFlagsDirectory.clear();
            g_ConfigRequestedFlagsDirectory.clear();
            g_SelectedFlagFileName.clear();
            g_SelectedFlagIndex = -1;
            g_SelectedFlagStatus = "Legacy test path idle.";
            InvalidateFlagPayloadCache();

            const auto primaryFlagsDir = GetFlagsDirectoryPath();
            std::error_code ec;
            std::filesystem::create_directories(primaryFlagsDir, ec);
            if (ec)
            {
                Log(L"[FLAG] Failed to ensure flags directory path=%hs ec=%d\n",
                    primaryFlagsDir.string().c_str(),
                    static_cast<int>(ec.value()));
            }

            const auto configPath = GetFlagsConfigPath();
            FILE* file = nullptr;
            if (fopen_s(&file, configPath.string().c_str(), "r") == 0 && file)
            {
                char line[512] = {};
                while (std::fgets(line, static_cast<int>(sizeof(line)), file))
                {
                    char* trimmed = TrimAsciiInPlace(line);
                    if (*trimmed == '\0' || *trimmed == '#' || *trimmed == ';')
                        continue;

                    char* equals = std::strchr(trimmed, '=');
                    if (!equals)
                        continue;

                    *equals = '\0';
                    char* key = TrimAsciiInPlace(trimmed);
                    char* value = TrimAsciiInPlace(equals + 1);
                    if (_stricmp(key, "selected") == 0 && value && *value)
                    {
                        g_SelectedFlagFileName = value;
                    }
                    else if ((_stricmp(key, "sourceDir") == 0 ||
                              _stricmp(key, "sourcePath") == 0) &&
                             value && *value)
                    {
                        g_ConfigRequestedFlagsDirectory = value;
                    }
                }

                std::fclose(file);
            }

            if (!g_ConfigRequestedFlagsDirectory.empty())
            {
                std::error_code overrideError;
                if (!std::filesystem::exists(g_ConfigRequestedFlagsDirectory, overrideError) || overrideError)
                {
                    Log(L"[FLAG] Config sourceDir does not exist path=%hs\n",
                        g_ConfigRequestedFlagsDirectory.string().c_str());
                    g_SelectedFlagStatus = "Configured flag source directory was not found; using fallback search.";
                    g_ConfigRequestedFlagsDirectory.clear();
                }
                else
                {
                    Log(L"[FLAG] Config requested source directory path=%hs\n",
                        g_ConfigRequestedFlagsDirectory.string().c_str());
                }
            }

            const auto flagsDir = ResolveFlagSourceDirectoryPath();
            g_ActiveFlagsDirectory = flagsDir;
            if (!flagsDir.empty() && flagsDir != primaryFlagsDir)
            {
                Log(L"[FLAG] Using fallback flag source directory path=%hs primary=%hs\n",
                    flagsDir.string().c_str(),
                    primaryFlagsDir.string().c_str());
            }
            for (std::filesystem::directory_iterator it(flagsDir, ec), end;
                 !ec && it != end;
                 it.increment(ec))
            {
                if (ec)
                    break;

                const auto& entry = *it;
                if (!entry.is_regular_file(ec) || ec)
                    continue;
                if (!IsSupportedFlagSourcePath(entry.path()))
                    continue;

                FlagCatalogEntry catalogEntry = {};
                catalogEntry.fileName = entry.path().filename().string();
                catalogEntry.displayName = entry.path().stem().string();
                catalogEntry.sourcePath = entry.path();
                g_FlagCatalog.push_back(std::move(catalogEntry));
            }

            SortFlagCatalog();
            SyncSelectedFlagIndex();

            if (g_FlagCatalog.empty())
            {
                if (!g_ConfigRequestedFlagsDirectory.empty())
                    g_SelectedFlagStatus = "No source images found in the configured flag source directory.";
                else
                    g_SelectedFlagStatus = "No source images found under the configured flag folders.";
                SaveSelectedFlagConfig();
                Log(L"[FLAG] No flag source files found. Checked primary=%hs active=%hs requested=%hs\n",
                    primaryFlagsDir.string().c_str(),
                    flagsDir.string().c_str(),
                    g_ConfigRequestedFlagsDirectory.empty() ? "" : g_ConfigRequestedFlagsDirectory.string().c_str());
                return;
            }

            SaveSelectedFlagConfig();
            Log(L"[FLAG] Loaded flag catalog path=%hs entries=%u selected=%hs requested=%hs\n",
                flagsDir.string().c_str(),
                static_cast<unsigned>(g_FlagCatalog.size()),
                g_SelectedFlagFileName.c_str(),
                g_ConfigRequestedFlagsDirectory.empty() ? "" : g_ConfigRequestedFlagsDirectory.string().c_str());
        }

        static const FlagCatalogEntry* GetSelectedFlagEntry()
        {
            EnsureFlagCatalogLoaded();
            if (g_SelectedFlagIndex < 0 ||
                static_cast<size_t>(g_SelectedFlagIndex) >= g_FlagCatalog.size())
            {
                return nullptr;
            }
            return &g_FlagCatalog[static_cast<size_t>(g_SelectedFlagIndex)];
        }

        static std::string GetSelectedFlagSummary()
        {
            const FlagCatalogEntry* entry = GetSelectedFlagEntry();
            if (!entry)
                return "No flag files found in the configured flag folders. Add PNG/BMP/TGA/JPG images.";

            const std::string sourceDirName =
                g_ActiveFlagsDirectory.empty()
                ? std::string("<none>")
                : g_ActiveFlagsDirectory.filename().string();
            char buffer[512] = {};
            std::snprintf(
                buffer,
                sizeof(buffer),
                "Selected multiplayer vehicle flag: %s (%d/%u, dir=%s). %s",
                entry->displayName.c_str(),
                g_SelectedFlagIndex + 1,
                static_cast<unsigned>(g_FlagCatalog.size()),
                sourceDirName.c_str(),
                g_SelectedFlagStatus.c_str());
            return buffer;
        }

        static bool TryGenerateSelectedFlagArtifacts(const char* source)
        {
            const FlagCatalogEntry* entry = GetSelectedFlagEntry();
            if (!entry)
            {
                g_SelectedFlagStatus = "No source images found under the configured flag folders.";
                return false;
            }

            if (g_FlagPayloadReady &&
                _stricmp(g_GeneratedFlagFileName.c_str(), entry->fileName.c_str()) == 0)
            {
                Log(L"[FLAG] %hs reused cached generated artifacts source=%hs\n",
                    source ? source : "flag",
                    entry->sourcePath.string().c_str());
                return true;
            }

            std::array<uint8_t, kLegacyFlagPayloadBytes> payload = {};
            std::string error;
            if (!TryBuildLegacyFlagPayloadFromSource(entry->sourcePath, payload, error))
            {
                g_SelectedFlagStatus = "Legacy conversion failed; see log for source-path detail.";
                Log(L"[FLAG] %hs failed converting source path=%hs error=%hs\n",
                    source ? source : "flag",
                    entry->sourcePath.string().c_str(),
                    error.c_str());
                return false;
            }

            const LegacyFlagArtifactPaths paths = GetLegacyFlagArtifactPaths();
            if (!WriteLegacyFlagBitmap(paths.bmpPath, payload, error))
            {
                g_SelectedFlagStatus = "Generated payload but writing the debug BMP failed.";
                Log(L"[FLAG] %hs failed writing BMP path=%hs error=%hs\n",
                    source ? source : "flag",
                    paths.bmpPath.string().c_str(),
                    error.c_str());
                return false;
            }

            if (!WriteLegacyFlagPayloadBin(paths.payloadPath, payload, error))
            {
                g_SelectedFlagStatus = "Generated BMP but writing the legacy payload failed.";
                Log(L"[FLAG] %hs failed writing payload path=%hs error=%hs\n",
                    source ? source : "flag",
                    paths.payloadPath.string().c_str(),
                    error.c_str());
                return false;
            }

            g_SelectedFlagPayload = payload;
            g_GeneratedFlagFileName = entry->fileName;
            g_FlagPayloadReady = true;
            g_FlagApplyPending = true;
            g_SelectedFlagStatus = "Generated legacy 64x32/1-bpp BMP and 256-byte payload; upload pending.";
            Log(L"[FLAG] %hs generated legacy artifacts source=%hs bmp=%hs payload=%hs\n",
                source ? source : "flag",
                entry->sourcePath.string().c_str(),
                paths.bmpPath.string().c_str(),
                paths.payloadPath.string().c_str());
            return true;
        }

        static bool TryApplySelectedFlagThroughEnginePath(const char* source, const char* path)
        {
            __try
            {
                auto* pathBuffer = reinterpret_cast<char*>(kFlagFilePathBufferAddr);
                std::memset(pathBuffer, 0, kFlagFilePathBufferCapacity);
                std::memcpy(pathBuffer, path, std::strlen(path));
                g_BzrFn_SetMyFlag();
                MarkFlagDisplayDirty();

                void* localPlayer = nullptr;
                const bool haveLocalPlayer = TryGetLocalPlayerForFlags(localPlayer);
                const void* flagBuffer =
                    haveLocalPlayer && localPlayer
                    ? *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(localPlayer) + 0x1C)
                    : nullptr;
                const int flagIndex =
                    haveLocalPlayer && localPlayer
                    ? *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(localPlayer) + 0x50)
                    : -1;

                if (flagBuffer)
                {
                    g_SelectedFlagStatus = "Uploaded selected flag through the engine SetMyFlag path.";
                    g_FlagApplyPending = false;
                }
                else
                {
                    g_SelectedFlagStatus = "Engine SetMyFlag ran, but the local player flag buffer stayed empty; fallback remains pending.";
                    g_FlagApplyPending = true;
                }

                Log(L"[FLAG] %hs engine apply path=%hs player=0x%p flagBuf=0x%p flagIndex=%d\n",
                    source ? source : "flag",
                    path,
                    localPlayer,
                    flagBuffer,
                    flagIndex);
                return flagBuffer != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_SelectedFlagStatus = "Engine SetMyFlag apply raised an exception.";
                g_FlagApplyPending = true;
                Log(L"[FLAG] %hs engine apply raised an exception path=%hs\n",
                    source ? source : "flag",
                    path ? path : "");
                return false;
            }
        }

        static bool TryApplySelectedFlagThroughEngine(const char* source)
        {
            const FlagCatalogEntry* entry = GetSelectedFlagEntry();
            if (!entry)
            {
                g_SelectedFlagStatus = "No source images found under the configured flag folders.";
                return false;
            }

            if (!g_BzrFn_SetMyFlag)
            {
                g_SelectedFlagStatus = "Engine flag upload helper was not resolved; using legacy fallback if available.";
                g_FlagApplyPending = true;
                return false;
            }

            if (!TryGenerateSelectedFlagArtifacts(source))
                return false;

            std::string path;
            if (!EnsureEngineFlagResourceStaged(source, path))
                path = entry->sourcePath.string();

            if (path.empty() || path.size() >= kFlagFilePathBufferCapacity)
            {
                g_SelectedFlagStatus = "Selected flag path is empty or too long for engine upload; using legacy fallback if available.";
                g_FlagApplyPending = true;
                return false;
            }

            return TryApplySelectedFlagThroughEnginePath(source, path.c_str());
        }

        static bool TryApplyCachedFlagPayload(const char* source)
        {
            if (!g_FlagPayloadReady)
                return false;

            if (!g_BzrFn_GetLocalPlayerNetId ||
                !g_BzrFn_BanLookup ||
                !g_BzrFn_NetPlayerSetData ||
                !g_BzrFn_NetPlayerSetFlagBuffer)
            {
                g_SelectedFlagStatus = "Generated legacy files, but fallback apply helpers were not resolved.";
                g_FlagApplyPending = true;
                return false;
            }

            __try
            {
                void* localPlayer = nullptr;
                if (!TryGetLocalPlayerForFlags(localPlayer))
                {
                    g_SelectedFlagStatus = "Generated legacy files; waiting for a local multiplayer player object.";
                    g_FlagApplyPending = true;
                    return false;
                }

                g_BzrFn_NetPlayerSetFlagBuffer(
                    localPlayer,
                    g_SelectedFlagPayload.data(),
                    static_cast<uint32_t>(g_SelectedFlagPayload.size()));
                g_BzrFn_NetPlayerSetData(
                    localPlayer,
                    kLegacyFlagDataSlot,
                    g_SelectedFlagPayload.data(),
                    static_cast<uint32_t>(g_SelectedFlagPayload.size()));
                MarkFlagDisplayDirty();
                g_SelectedFlagStatus = "Uploaded 256-byte legacy fallback flag payload.";
                g_FlagApplyPending = false;
                Log(L"[FLAG] %hs applied legacy fallback payload bytes=%u slot=0x%02X player=0x%p\n",
                    source ? source : "flag",
                    static_cast<unsigned>(g_SelectedFlagPayload.size()),
                    static_cast<unsigned>(kLegacyFlagDataSlot),
                    localPlayer);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_SelectedFlagStatus = "Generated legacy files, but fallback apply raised an exception.";
                g_FlagApplyPending = true;
                Log(L"[FLAG] %hs apply raised an exception\n", source ? source : "flag");
                return false;
            }
        }

        static void PrimeSelectedFlagForTesting(const char* source)
        {
            if (TryApplySelectedFlagThroughEngine(source))
                return;

            if (!TryGenerateSelectedFlagArtifacts(source))
                return;

            TryApplyCachedFlagPayload(source);
        }

        static void SelectFlagEntryByIndex(int index, const char* source)
        {
            EnsureFlagCatalogLoaded();
            if (g_FlagCatalog.empty())
            {
                Log(L"[FLAG] %hs ignored because no flag files are available\n",
                    source ? source : "flag");
                return;
            }

            const int count = static_cast<int>(g_FlagCatalog.size());
            if (index < 0)
                index = (count - 1);
            else if (index >= count)
                index = 0;

            const std::string previousSelection = g_SelectedFlagFileName;
            g_SelectedFlagIndex = index;
            g_SelectedFlagFileName = g_FlagCatalog[static_cast<size_t>(index)].fileName;
            if (_stricmp(previousSelection.c_str(), g_SelectedFlagFileName.c_str()) != 0)
            {
                InvalidateFlagPayloadCache();
                g_SelectedFlagStatus = "Selected new source image; upload pending.";
            }
            SaveSelectedFlagConfig();
            Log(L"[FLAG] %hs selected index=%d file=%hs path=%hs\n",
                source ? source : "flag",
                index,
                g_SelectedFlagFileName.c_str(),
                g_FlagCatalog[static_cast<size_t>(index)].sourcePath.string().c_str());
        }

        static void AppendLegacyBanList(const char* id, const BzrString* name)
        {
            if (!id || !*id)
                return;

            const auto path = GetLegacyBanListPath();
            const std::string pathString = path.string();

            FILE* file = nullptr;
            fopen_s(&file, pathString.c_str(), "a");
            if (!file)
            {
                Log(L"[BAN] Failed to append legacy banlist path=%hs\n", pathString.c_str());
                return;
            }

            if (name && name->size)
                std::fprintf(file, "%s %.*s\n", id, static_cast<int>(name->size), BzrStringData(name));
            else
                std::fprintf(file, "%s\n", id);
            std::fclose(file);
        }

        static void EnsureBansConfigLoaded()
        {
            if (g_BansConfigLoaded)
                return;

            g_BansConfigLoaded = true;
            g_BanRecords.clear();

            const auto configPath = GetBansConfigPath();
            const std::string configPathString = configPath.string();
            FILE* file = nullptr;
            if (fopen_s(&file, configPathString.c_str(), "r") != 0 || !file)
            {
                Log(L"[BAN] No bans config found at path=%hs\n", configPathString.c_str());
                return;
            }

            char line[512] = {};
            while (std::fgets(line, static_cast<int>(sizeof(line)), file))
            {
                char* trimmed = TrimAsciiInPlace(line);
                if (*trimmed == '\0' || *trimmed == '#' || *trimmed == ';')
                    continue;

                char* split = trimmed;
                while (*split && !std::isspace(static_cast<unsigned char>(*split)))
                    ++split;

                char saved = *split;
                *split = '\0';
                std::string id = NormalizeBanId(trimmed);
                *split = saved;
                if (id.empty())
                    continue;

                char* name = (*split != '\0') ? TrimAsciiInPlace(split + 1) : split;
                auto existing = std::find_if(
                    g_BanRecords.begin(),
                    g_BanRecords.end(),
                    [&id](const BanRecord& entry) { return entry.id == id; });
                if (existing != g_BanRecords.end())
                {
                    if (existing->name.empty() && name && *name)
                        existing->name = name;
                    continue;
                }

                BanRecord entry = {};
                entry.id = std::move(id);
                if (name && *name)
                    entry.name = name;
                g_BanRecords.push_back(std::move(entry));
            }

            std::fclose(file);
            Log(L"[BAN] Loaded bans config path=%hs entries=%u\n",
                configPathString.c_str(),
                static_cast<unsigned>(g_BanRecords.size()));
        }

        static bool SaveBansConfig()
        {
            const auto configPath = GetBansConfigPath();
            const std::string configPathString = configPath.string();
            FILE* file = nullptr;
            if (fopen_s(&file, configPathString.c_str(), "w") != 0 || !file)
            {
                Log(L"[BAN] Failed to write bans config path=%hs\n", configPathString.c_str());
                return false;
            }

            std::fprintf(file, "; OpenShim experimental ban list\n");
            std::fprintf(file, "; Format: <stable_id> [display name]\n");
            for (const BanRecord& entry : g_BanRecords)
            {
                if (entry.name.empty())
                    std::fprintf(file, "%s\n", entry.id.c_str());
                else
                    std::fprintf(file, "%s %s\n", entry.id.c_str(), entry.name.c_str());
            }

            std::fclose(file);
            Log(L"[BAN] Wrote bans config path=%hs entries=%u\n",
                configPathString.c_str(),
                static_cast<unsigned>(g_BanRecords.size()));
            return true;
        }

        static bool IsBanIdConfigured(const char* stableId)
        {
            if (!stableId || !*stableId)
                return false;

            EnsureBansConfigLoaded();
            const std::string normalized = NormalizeBanId(stableId);
            return std::any_of(
                g_BanRecords.begin(),
                g_BanRecords.end(),
                [&normalized](const BanRecord& entry) { return entry.id == normalized; });
        }

        static bool AddBanConfigEntry(const char* stableId, const BzrString* name, const char* source)
        {
            const std::string normalized = NormalizeBanId(stableId);
            if (normalized.empty())
            {
                Log(L"[BAN] %hs rejected invalid stable id '%hs'\n",
                    source ? source : "ban",
                    stableId ? stableId : "");
                return false;
            }

            EnsureBansConfigLoaded();

            const std::string displayName = BzrStringToStdString(name);
            auto existing = std::find_if(
                g_BanRecords.begin(),
                g_BanRecords.end(),
                [&normalized](const BanRecord& entry) { return entry.id == normalized; });
            if (existing != g_BanRecords.end())
            {
                if (existing->name.empty() && !displayName.empty())
                {
                    existing->name = displayName;
                    SaveBansConfig();
                    Log(L"[BAN] %hs refreshed existing entry stable=%hs name=%hs\n",
                        source ? source : "ban",
                        normalized.c_str(),
                        displayName.c_str());
                }
                else
                {
                    Log(L"[BAN] %hs entry already present stable=%hs name=%hs\n",
                        source ? source : "ban",
                        normalized.c_str(),
                        existing->name.c_str());
                }

                return true;
            }

            BanRecord entry = {};
            entry.id = normalized;
            entry.name = displayName;
            g_BanRecords.push_back(std::move(entry));
            SaveBansConfig();
            AppendLegacyBanList(normalized.c_str(), name);
            Log(L"[BAN] %hs added entry stable=%hs name=%hs\n",
                source ? source : "ban",
                normalized.c_str(),
                displayName.c_str());
            return true;
        }

        static const char* UnderAttackAlertModeName(UnderAttackAlertMode mode)
        {
            switch (mode)
            {
            case UnderAttackAlertMode::None:
                return "NONE";
            case UnderAttackAlertMode::Minimal:
                return "MINIMAL";
            default:
                return "NORMAL";
            }
        }

        static UnderAttackAlertMode ClampUnderAttackAlertMode(int value)
        {
            if (value <= static_cast<int>(UnderAttackAlertMode::None))
                return UnderAttackAlertMode::None;
            if (value == static_cast<int>(UnderAttackAlertMode::Minimal))
                return UnderAttackAlertMode::Minimal;
            return UnderAttackAlertMode::Normal;
        }

        static void ApplyUnderAttackAlertMode(UnderAttackAlertMode mode, bool resetTimer)
        {
            g_UnderAttackAlertMode = mode;
            switch (mode)
            {
            case UnderAttackAlertMode::None:
                g_UnderAttackAlertEnabled = false;
                g_UnderAttackAlertCooldownSeconds = 0.0f;
                break;
            case UnderAttackAlertMode::Minimal:
                g_UnderAttackAlertEnabled = true;
                g_UnderAttackAlertCooldownSeconds = 10.0f;
                break;
            case UnderAttackAlertMode::Normal:
            default:
                g_UnderAttackAlertEnabled = true;
                g_UnderAttackAlertCooldownSeconds = 1.0f;
                break;
            }

            if (resetTimer)
                g_UnderAttackAlertNextAllowedTime = 0.0f;
        }

        static bool TryParseUnderAttackAlertModeValue(const char* value, UnderAttackAlertMode& outMode)
        {
            if (!value || !*value)
                return false;

            char normalized[32] = {};
            size_t out = 0;
            for (const char* cursor = value; *cursor && out + 1 < sizeof(normalized); ++cursor)
            {
                if (std::isspace(static_cast<unsigned char>(*cursor)))
                    continue;
                normalized[out++] = static_cast<char>(std::toupper(static_cast<unsigned char>(*cursor)));
            }
            normalized[out] = '\0';
            if (normalized[0] == '\0')
                return false;

            char* end = nullptr;
            const long parsed = std::strtol(normalized, &end, 10);
            if (end != normalized && *end == '\0')
            {
                outMode = parsed <= 0 ? UnderAttackAlertMode::None : ClampUnderAttackAlertMode(static_cast<int>(parsed));
                return true;
            }

            if (std::strcmp(normalized, "NONE") == 0 || std::strcmp(normalized, "OFF") == 0)
            {
                outMode = UnderAttackAlertMode::None;
                return true;
            }
            if (std::strcmp(normalized, "MINIMAL") == 0 || std::strcmp(normalized, "LOW") == 0)
            {
                outMode = UnderAttackAlertMode::Minimal;
                return true;
            }
            if (std::strcmp(normalized, "NORMAL") == 0 || std::strcmp(normalized, "DEFAULT") == 0 ||
                std::strcmp(normalized, "ON") == 0)
            {
                outMode = UnderAttackAlertMode::Normal;
                return true;
            }

            return false;
        }

        static bool TryLoadUnderAttackAlertModeFromConfig(
            const std::filesystem::path& configPath,
            UnderAttackAlertMode& outMode)
        {
            if (configPath.empty())
                return false;

            FILE* file = nullptr;
            if (fopen_s(&file, configPath.string().c_str(), "r") != 0 || !file)
                return false;

            char line[256] = {};
            bool found = false;
            while (std::fgets(line, static_cast<int>(sizeof(line)), file))
            {
                char* trimmed = TrimAsciiInPlace(line);
                if (*trimmed == '\0' || *trimmed == '#' || *trimmed == ';')
                    continue;

                char* equals = std::strchr(trimmed, '=');
                if (!equals)
                    continue;

                *equals = '\0';
                char* key = TrimAsciiInPlace(trimmed);
                char* value = TrimAsciiInPlace(equals + 1);
                if (_stricmp(key, "UnderAttackAlertMode") != 0)
                    continue;

                found = TryParseUnderAttackAlertModeValue(value, outMode);
                break;
            }

            std::fclose(file);
            return found;
        }

        static bool TryGetEnvUnderAttackAlertMode(
            const char* envName,
            UnderAttackAlertMode& outMode)
        {
            if (!envName || !*envName)
                return false;

            char value[32] = {};
            const DWORD len = GetEnvironmentVariableA(envName, value, static_cast<DWORD>(sizeof(value)));
            if (len == 0 || len >= sizeof(value))
                return false;

            return TryParseUnderAttackAlertModeValue(value, outMode);
        }

        static void InitializeUnderAttackAlertConfig()
        {
            if (g_UnderAttackAlertConfigInitialized)
                return;

            g_UnderAttackAlertConfigInitialized = true;
            ApplyUnderAttackAlertMode(UnderAttackAlertMode::Normal, true);

            UnderAttackAlertMode mode = UnderAttackAlertMode::Normal;
            const auto configPath = GetConfigModuleDirectory() / kUnderAttackAlertConfigName;
            if (TryLoadUnderAttackAlertModeFromConfig(configPath, mode))
                ApplyUnderAttackAlertMode(mode, true);

            if (TryGetEnvUnderAttackAlertMode("OPENSHIM_UNDER_ATTACK_ALERT_MODE", mode) ||
                TryGetEnvUnderAttackAlertMode("BZR_UNDER_ATTACK_ALERT_MODE", mode))
            {
                ApplyUnderAttackAlertMode(mode, true);
            }
            else if (EnvFlagEnabled("OPENSHIM_DISABLE_UNDER_ATTACK_ALERT") ||
                     EnvFlagEnabled("BZR_DISABLE_UNDER_ATTACK_ALERT"))
            {
                ApplyUnderAttackAlertMode(UnderAttackAlertMode::None, true);
            }
            else
            {
                float envCooldown = g_UnderAttackAlertCooldownSeconds;
                if (TryGetEnvFloat("OPENSHIM_UNDER_ATTACK_ALERT_COOLDOWN", envCooldown) ||
                    TryGetEnvFloat("BZR_UNDER_ATTACK_ALERT_COOLDOWN", envCooldown) ||
                    TryGetEnvFloat("OPENSHIM_UNDER_ATTACK_ALERT_COOLDOWN_SECONDS", envCooldown))
                {
                    g_UnderAttackAlertEnabled = true;
                    g_UnderAttackAlertCooldownSeconds = ClampUnderAttackAlertCooldown(envCooldown);
                }
            }

            Log(L"[AUDIO] Under-attack alert mode=%hs enabled=%hs cooldown=%.3fs\n",
                UnderAttackAlertModeName(g_UnderAttackAlertMode),
                g_UnderAttackAlertEnabled ? "yes" : "no",
                static_cast<double>(g_UnderAttackAlertCooldownSeconds));
        }

        static bool SetUnderAttackAlertModeInternal(UnderAttackAlertMode mode, bool logChange)
        {
            InitializeUnderAttackAlertConfig();
            const bool changed =
                g_UnderAttackAlertMode != mode ||
                !g_UnderAttackAlertEnabled ||
                std::abs(g_UnderAttackAlertCooldownSeconds -
                    (mode == UnderAttackAlertMode::Minimal ? 10.0f :
                     mode == UnderAttackAlertMode::Normal ? 1.0f : 0.0f)) > 0.0001f;
            ApplyUnderAttackAlertMode(mode, true);
            if (logChange)
            {
                Log(L"[AUDIO] Under-attack alert bridge mode=%hs enabled=%hs cooldown=%.3fs\n",
                    UnderAttackAlertModeName(g_UnderAttackAlertMode),
                    g_UnderAttackAlertEnabled ? "yes" : "no",
                    static_cast<double>(g_UnderAttackAlertCooldownSeconds));
            }
            return changed;
        }

        static const char* TargetReticlePopupModeName(TargetReticlePopupMode mode)
        {
            switch (mode)
            {
            case TargetReticlePopupMode::NeutralOnly:
                return "NEUTRAL_ONLY";
            case TargetReticlePopupMode::ExplicitOnly:
                return "EXPLICIT_ONLY";
            default:
                return "DEFAULT";
            }
        }

        static TargetReticlePopupMode ClampTargetReticlePopupMode(int value)
        {
            if (value <= static_cast<int>(TargetReticlePopupMode::Default))
                return TargetReticlePopupMode::Default;
            if (value == static_cast<int>(TargetReticlePopupMode::NeutralOnly))
                return TargetReticlePopupMode::NeutralOnly;
            return TargetReticlePopupMode::ExplicitOnly;
        }

        static bool TryParseTargetReticlePopupModeValue(const char* value, TargetReticlePopupMode& outMode)
        {
            if (!value || !*value)
                return false;

            char normalized[32] = {};
            size_t out = 0;
            for (const char* cursor = value; *cursor && out + 1 < sizeof(normalized); ++cursor)
            {
                if (std::isspace(static_cast<unsigned char>(*cursor)) || *cursor == '_' || *cursor == '-')
                    continue;
                normalized[out++] = static_cast<char>(std::toupper(static_cast<unsigned char>(*cursor)));
            }
            normalized[out] = '\0';
            if (normalized[0] == '\0')
                return false;

            char* end = nullptr;
            const long parsed = std::strtol(normalized, &end, 10);
            if (end != normalized && *end == '\0')
            {
                outMode = ClampTargetReticlePopupMode(static_cast<int>(parsed));
                return true;
            }

            if (std::strcmp(normalized, "DEFAULT") == 0 || std::strcmp(normalized, "NORMAL") == 0 ||
                std::strcmp(normalized, "ON") == 0)
            {
                outMode = TargetReticlePopupMode::Default;
                return true;
            }
            if (std::strcmp(normalized, "NEUTRALONLY") == 0 || std::strcmp(normalized, "NEUTRAL") == 0)
            {
                outMode = TargetReticlePopupMode::NeutralOnly;
                return true;
            }
            if (std::strcmp(normalized, "EXPLICITONLY") == 0 || std::strcmp(normalized, "EXPLICIT") == 0)
            {
                outMode = TargetReticlePopupMode::ExplicitOnly;
                return true;
            }

            return false;
        }

        static bool TryLoadTargetReticlePopupModeFromConfig(
            const std::filesystem::path& configPath,
            TargetReticlePopupMode& outMode)
        {
            if (configPath.empty())
                return false;

            FILE* file = nullptr;
            if (fopen_s(&file, configPath.string().c_str(), "r") != 0 || !file)
                return false;

            char line[256] = {};
            bool found = false;
            while (std::fgets(line, static_cast<int>(sizeof(line)), file))
            {
                char* trimmed = TrimAsciiInPlace(line);
                if (*trimmed == '\0' || *trimmed == '#' || *trimmed == ';')
                    continue;

                char* equals = std::strchr(trimmed, '=');
                if (!equals)
                    continue;

                *equals = '\0';
                char* key = TrimAsciiInPlace(trimmed);
                char* value = TrimAsciiInPlace(equals + 1);
                if (_stricmp(key, "TargetReticlePopupMode") != 0)
                    continue;

                found = TryParseTargetReticlePopupModeValue(value, outMode);
                break;
            }

            std::fclose(file);
            return found;
        }

        static bool TryGetEnvTargetReticlePopupMode(const char* envName, TargetReticlePopupMode& outMode)
        {
            if (!envName || !*envName)
                return false;

            char value[32] = {};
            const DWORD len = GetEnvironmentVariableA(envName, value, static_cast<DWORD>(sizeof(value)));
            if (len == 0 || len >= sizeof(value))
                return false;

            return TryParseTargetReticlePopupModeValue(value, outMode);
        }

        static TargetReticlePopupMode SanitizeTargetReticlePopupMode(TargetReticlePopupMode mode, bool logDowngrade)
        {
            if (mode == TargetReticlePopupMode::NeutralOnly &&
                !g_TargetReticlePopupSteamNeutralAllowed)
            {
                if (logDowngrade && !g_TargetReticlePopupSteamNeutralWarned)
                {
                    g_TargetReticlePopupSteamNeutralWarned = true;
                    Log(L"[HUD] Reticle popup NEUTRAL_ONLY is experimental and downgraded to DEFAULT; set OPENSHIM_ALLOW_NEUTRAL_RETICLE_POPUP=1 to force it\n");
                }
                return TargetReticlePopupMode::Default;
            }

            return mode;
        }

        static void ApplyTargetReticlePopupMode(TargetReticlePopupMode mode)
        {
            g_TargetReticlePopupMode = mode;
        }

        static void InitializeTargetReticlePopupConfig()
        {
            if (g_TargetReticlePopupConfigInitialized)
                return;

            g_TargetReticlePopupConfigInitialized = true;
            g_TargetReticlePopupSteamNeutralAllowed =
                EnvFlagEnabled("OPENSHIM_ALLOW_NEUTRAL_RETICLE_POPUP") ||
                EnvFlagEnabled("BZR_ALLOW_NEUTRAL_RETICLE_POPUP") ||
                EnvFlagEnabled("OPENSHIM_ALLOW_STEAM_NEUTRAL_RETICLE_POPUP") ||
                EnvFlagEnabled("BZR_ALLOW_STEAM_NEUTRAL_RETICLE_POPUP");
            ApplyTargetReticlePopupMode(TargetReticlePopupMode::Default);

            TargetReticlePopupMode mode = TargetReticlePopupMode::Default;
            const auto configPath = GetConfigModuleDirectory() / kUnderAttackAlertConfigName;
            if (TryLoadTargetReticlePopupModeFromConfig(configPath, mode))
                ApplyTargetReticlePopupMode(SanitizeTargetReticlePopupMode(mode, true));

            if (TryGetEnvTargetReticlePopupMode("OPENSHIM_TARGET_RETICLE_POPUP_MODE", mode) ||
                TryGetEnvTargetReticlePopupMode("BZR_TARGET_RETICLE_POPUP_MODE", mode))
            {
                ApplyTargetReticlePopupMode(SanitizeTargetReticlePopupMode(mode, true));
            }

            Log(L"[HUD] Target reticle popup mode=%hs\n",
                TargetReticlePopupModeName(g_TargetReticlePopupMode));
        }

        static bool SetTargetReticlePopupModeInternal(TargetReticlePopupMode mode, bool logChange)
        {
            InitializeTargetReticlePopupConfig();
            mode = SanitizeTargetReticlePopupMode(mode, logChange);
            const bool changed = g_TargetReticlePopupMode != mode;
            ApplyTargetReticlePopupMode(mode);
            if (logChange)
            {
                Log(L"[HUD] Target reticle popup bridge mode=%hs\n",
                    TargetReticlePopupModeName(g_TargetReticlePopupMode));
            }
            return changed;
        }

        static float GetGameObjectPlayerShotTime(void* objectPtr)
        {
            if (!objectPtr)
                return kSuppressedRecentHitTime;

            __try
            {
                const auto* bytes = reinterpret_cast<const uint8_t*>(objectPtr);
                return *reinterpret_cast<const float*>(bytes + kGameObjectPlayerShotOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return kSuppressedRecentHitTime;
            }
        }

        static bool IsNeutralTeamObject(void* objectPtr)
        {
            if (!objectPtr)
                return false;

            __try
            {
                auto** vtable = *reinterpret_cast<void***>(objectPtr);
                if (!vtable)
                    return false;

                auto getTeam = reinterpret_cast<FnGameObjectGetTeam>(vtable[kGameObjectGetTeamVtableOffset / sizeof(void*)]);
                if (!getTeam)
                    return false;

                return getTeam(objectPtr) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        struct SatelliteVisibilityLogEntry
        {
            void* objectPtr = nullptr;
            int team = INT_MIN;
            float illumination = 0.0f;
            uint32_t isVisible = 0;
            uint32_t seen = 0;
            int targetHandle = 0;
        };

        static int GetGameObjectTeamForLog(void* objectPtr)
        {
            if (!objectPtr)
                return INT_MIN;

            __try
            {
                auto** vtable = *reinterpret_cast<void***>(objectPtr);
                if (!vtable)
                    return INT_MIN;

                auto getTeam = reinterpret_cast<FnGameObjectGetTeam>(vtable[kGameObjectGetTeamVtableOffset / sizeof(void*)]);
                if (!getTeam)
                    return INT_MIN;

                return getTeam(objectPtr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return INT_MIN;
            }
        }

        static bool IsSatelliteOverviewActive()
        {
            auto* viewRecord = ResolveMainModulePtr<uint8_t>(kViewRecordRva);
            if (!viewRecord)
                return false;

            __try
            {
                const long currentView =
                    *reinterpret_cast<const long*>(viewRecord + kPresetViewCurrentViewOffset);
                return currentView == kCameraTypeOverView;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool CaptureSatelliteVisibilityEntry(void* objectPtr, SatelliteVisibilityLogEntry& outEntry)
        {
            if (!objectPtr)
                return false;

            __try
            {
                auto* bytes = reinterpret_cast<uint8_t*>(objectPtr);
                outEntry.objectPtr = objectPtr;
                outEntry.team = GetGameObjectTeamForLog(objectPtr);
                outEntry.illumination =
                    *reinterpret_cast<const float*>(bytes + kGameObjectIlluminationOffset);
                outEntry.isVisible =
                    *reinterpret_cast<const uint32_t*>(bytes + kGameObjectIsVisibleOffset);
                outEntry.seen =
                    *reinterpret_cast<const uint32_t*>(bytes + kGameObjectSeenOffset);
                outEntry.targetHandle =
                    *reinterpret_cast<const int*>(bytes + kGameObjectTargetHandleOffset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void LogSatelliteVisibilityEntry(const wchar_t* tag, const SatelliteVisibilityLogEntry& entry)
        {
            if (!tag)
                return;

            Log(L"[SATVIS]   %ls obj=0x%08X team=%d illum=%.3f isVisible=0x%08X seen=0x%08X target=0x%08X\n",
                tag,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entry.objectPtr)),
                entry.team,
                static_cast<double>(entry.illumination),
                entry.isVisible,
                entry.seen,
                static_cast<uint32_t>(entry.targetHandle));
        }

        static void MaybeLogSatelliteVisibilitySample()
        {
            if (!g_TraceSatelliteVisibility)
                return;
            if (!IsSatelliteOverviewActive())
                return;

            const DWORD now = GetTickCount();
            if (g_SatelliteVisibilityLastTick != 0 &&
                (now - g_SatelliteVisibilityLastTick) < g_SatelliteVisibilityLogIntervalMs)
            {
                return;
            }

            if (InterlockedDecrement(&g_SatelliteVisibilityLogBudget) < 0)
                return;

            g_SatelliteVisibilityLastTick = now;

            auto* viewRecord = ResolveMainModulePtr<uint8_t>(kViewRecordRva);
            auto* userTeamNumberPtr = ResolveMainModulePtr<long>(kGameObjectUserTeamNumberRva);
            auto* userObjectPtr = ResolveMainModulePtr<void*>(kGameObjectUserObjectRva);
            auto* objectListBytes = ResolveMainModulePtr<uint8_t>(kGameObjectObjectListRva);
            if (!viewRecord || !userTeamNumberPtr || !userObjectPtr || !objectListBytes)
            {
                Log(L"[SATVIS] missing runtime pointers viewRecord=0x%08X userTeam=0x%08X userObject=0x%08X objectList=0x%08X\n",
                    static_cast<uint32_t>(GetMainModuleBase() + kViewRecordRva),
                    static_cast<uint32_t>(GetMainModuleBase() + kGameObjectUserTeamNumberRva),
                    static_cast<uint32_t>(GetMainModuleBase() + kGameObjectUserObjectRva),
                    static_cast<uint32_t>(GetMainModuleBase() + kGameObjectObjectListRva));
                return;
            }

            __try
            {
                const long currentView =
                    *reinterpret_cast<const long*>(viewRecord + kPresetViewCurrentViewOffset);
                const long userTeam = *userTeamNumberPtr;
                void* const userObject = *userObjectPtr;

                auto** begin = *reinterpret_cast<void***>(objectListBytes + 0x0);
                auto** end = *reinterpret_cast<void***>(objectListBytes + 0x4);
                auto** capacity = *reinterpret_cast<void***>(objectListBytes + 0x8);
                if (!begin || !end || !capacity || end < begin || capacity < end)
                {
                    Log(L"[SATVIS] invalid objectList begin=0x%08X end=0x%08X cap=0x%08X\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(begin)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(end)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(capacity)));
                    return;
                }

                const size_t totalObjects = static_cast<size_t>(end - begin);
                const size_t maxSampleObjects = static_cast<size_t>(g_SatelliteVisibilityObjectLimit);
                const size_t sampleObjects =
                    (totalObjects < maxSampleObjects) ? totalObjects : maxSampleObjects;

                SatelliteVisibilityLogEntry userEntry = {};
                const bool haveUserEntry = CaptureSatelliteVisibilityEntry(userObject, userEntry);

                uint32_t illuminatedCount = 0;
                uint32_t visibleCount = 0;
                uint32_t seenCount = 0;
                std::array<SatelliteVisibilityLogEntry, 3> hiddenEntries = {};
                std::array<SatelliteVisibilityLogEntry, 3> visibleEntries = {};
                size_t hiddenLogged = 0;
                size_t visibleLogged = 0;

                for (size_t index = 0; index < sampleObjects; ++index)
                {
                    SatelliteVisibilityLogEntry entry = {};
                    if (!CaptureSatelliteVisibilityEntry(begin[index], entry))
                        continue;

                    if (entry.illumination > 0.0f)
                        ++illuminatedCount;
                    if (entry.isVisible != 0)
                        ++visibleCount;
                    if (entry.seen != 0)
                        ++seenCount;

                    if (entry.illumination <= 0.0f && entry.isVisible == 0)
                    {
                        if (hiddenLogged < hiddenEntries.size())
                            hiddenEntries[hiddenLogged++] = entry;
                    }
                    else if (visibleLogged < visibleEntries.size())
                    {
                        visibleEntries[visibleLogged++] = entry;
                    }
                }

                Log(L"[SATVIS] view=%ld userTeam=%ld userObj=0x%08X total=%u sampled=%u illum=%u visible=%u seen=%u interval=%lums remaining=%ld\n",
                    currentView,
                    userTeam,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(userObject)),
                    static_cast<unsigned>(totalObjects),
                    static_cast<unsigned>(sampleObjects),
                    illuminatedCount,
                    visibleCount,
                    seenCount,
                    static_cast<unsigned long>(g_SatelliteVisibilityLogIntervalMs),
                    g_SatelliteVisibilityLogBudget);

                if (haveUserEntry)
                    LogSatelliteVisibilityEntry(L"user", userEntry);

                for (size_t index = 0; index < hiddenLogged; ++index)
                    LogSatelliteVisibilityEntry(L"hidden", hiddenEntries[index]);
                for (size_t index = 0; index < visibleLogged; ++index)
                    LogSatelliteVisibilityEntry(L"visible", visibleEntries[index]);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[SATVIS] sample fault code=0x%08X\n", static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        static void* GetEngineFlamePrimary()
        {
            return g_EngineFlamePrimaryManager;
        }

        static void* GetEngineFlameSecondary()
        {
            return g_EngineFlameSecondaryManager;
        }

        static bool FindPatternInMainText(
            const uint8_t* pattern,
            const uint8_t* mask,
            size_t size,
            uint8_t*& outMatch)
        {
            outMatch = nullptr;
            if (!pattern || !mask || size == 0)
                return false;

            HMODULE module = GetModuleHandleA(nullptr);
            if (!module)
                return false;

            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(module);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return false;

            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(
                reinterpret_cast<uint8_t*>(module) + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return false;

            auto* section = IMAGE_FIRST_SECTION(nt);
            for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
            {
                if ((section->Characteristics & IMAGE_SCN_MEM_EXECUTE) == 0)
                    continue;

                auto* start = reinterpret_cast<uint8_t*>(module) + section->VirtualAddress;
                const size_t sectionSize =
                    (section->Misc.VirtualSize != 0) ? section->Misc.VirtualSize : section->SizeOfRawData;
                if (sectionSize < size)
                    continue;

                for (size_t offset = 0; offset <= sectionSize - size; ++offset)
                {
                    bool match = true;
                    for (size_t j = 0; j < size; ++j)
                    {
                        if (mask[j] != 0 && start[offset + j] != pattern[j])
                        {
                            match = false;
                            break;
                        }
                    }

                    if (match)
                    {
                        outMatch = start + offset;
                        return true;
                    }
                }
            }

            return false;
        }

        static uint32_t ResolveRel32Target(uint8_t* callInstr)
        {
            if (!callInstr || callInstr[0] != 0xE8)
                return 0;

            const int32_t rel = *reinterpret_cast<int32_t*>(callInstr + 1);
            return static_cast<uint32_t>(
                reinterpret_cast<uintptr_t>(callInstr + 5) + rel);
        }

        static void LogEngineFlameTargetFailure(const wchar_t* name)
        {
            if (!name || !name[0])
                return;

            if (!g_LoggedEngineFlameTargetFailure)
            {
                Log(L"[FLAME] Failed to resolve Steam runtime target: %ls\n", name);
                g_LoggedEngineFlameTargetFailure = true;
            }
        }

        static void ResolveEngineFlameRuntimeTargets()
        {
            if (g_BzrFn_EngineFlameAddFlame &&
                g_BzrFn_EngineFlameResolveTexture &&
                g_BzrFn_GetTeamNum)
            {
                return;
            }

            static const uint8_t kEmit1Pattern[] =
            {
                0x0F, 0x11, 0x04, 0x24, 0x8D, 0x85, 0x00, 0x00, 0x00, 0x00,
                0x50, 0xB9, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00,
                0x00, 0x83, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x84,
            };
            static const uint8_t kEmit1Mask[] =
            {
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
                0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
                0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
            };
            static const uint8_t kGetTeamNumPattern[] =
            {
                0x8B, 0x45, 0x08, 0x50, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x83,
                0xC4, 0x04, 0x89, 0x45, 0xFC, 0x83, 0x7D, 0xFC, 0x00, 0x75,
                0x04, 0x33, 0xC0, 0xEB, 0x11, 0x8B, 0x4D, 0xFC, 0x83, 0xC1,
                0x18, 0x8B, 0x55, 0xFC, 0x8B, 0x42, 0x18, 0x8B, 0x50, 0x04,
                0xFF, 0xD2,
            };
            static const uint8_t kGetTeamNumMask[] =
            {
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF,
            };
            static const uint8_t kResolveTexturePattern[] =
            {
                0x55, 0x8B, 0xEC, 0x51, 0x83, 0x7D, 0x08, 0x00, 0x75, 0x04,
                0x33, 0xC0, 0xEB, 0x44, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x83,
                0xE8, 0x01, 0x89, 0x45, 0xFC, 0xEB, 0x09, 0x8B, 0x4D, 0xFC,
                0x83, 0xE9, 0x01, 0x89, 0x4D, 0xFC, 0x83, 0x7D, 0xFC, 0x00,
                0x7E, 0x26, 0x6A, 0x20, 0x8B, 0x55, 0x08, 0x52, 0x8B, 0x45,
                0xFC, 0xC1, 0xE0, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x50,
                0xFF, 0x15, 0x00, 0x00, 0x00, 0x00, 0x83, 0xC4, 0x0C, 0x85,
                0xC0, 0x75, 0x05,
            };
            static const uint8_t kResolveTextureMask[] =
            {
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
                0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF,
            };

            uint8_t* match = nullptr;
            if (!g_BzrFn_EngineFlameAddFlame)
            {
                if (FindPatternInMainText(kEmit1Pattern, kEmit1Mask, sizeof(kEmit1Pattern), match))
                {
                    const uint32_t target = ResolveRel32Target(match + 16);
                    if (target != 0)
                    {
                        g_BzrFn_EngineFlameAddFlame =
                            reinterpret_cast<FnEngineFlameAddFlame>(target);
                    }
                }

                if (!g_BzrFn_EngineFlameAddFlame)
                    LogEngineFlameTargetFailure(L"EngineFlame::AddFlame");
            }

            if (!g_BzrFn_GetTeamNum)
            {
                if (FindPatternInMainText(kGetTeamNumPattern, kGetTeamNumMask, sizeof(kGetTeamNumPattern), match))
                {
                    g_BzrFn_GetTeamNum =
                        reinterpret_cast<FnGetTeamNum>(
                            reinterpret_cast<uintptr_t>(match) - 4);
                }

                if (!g_BzrFn_GetTeamNum)
                    LogEngineFlameTargetFailure(L"GetTeamNum");
            }

            if (!g_BzrFn_EngineFlameResolveTexture)
            {
                if (FindPatternInMainText(
                        kResolveTexturePattern,
                        kResolveTextureMask,
                        sizeof(kResolveTexturePattern),
                        match))
                {
                    g_BzrFn_EngineFlameResolveTexture =
                        reinterpret_cast<FnEngineFlameResolveTexture>(match);
                    g_BzrFn_HudSpriteLookup =
                        reinterpret_cast<FnHudSpriteLookup>(match);
                }

                if (!g_BzrFn_EngineFlameResolveTexture)
                    LogEngineFlameTargetFailure(L"ResolveTexture");
            }
        }

        static void ObserveEngineFlameManager(void* manager)
        {
            if (!manager)
                return;

            if (!g_EngineFlamePrimaryManager)
            {
                g_EngineFlamePrimaryManager = manager;
                Log(L"[FLAME] Observed primary engine flame manager=0x%p\n", manager);
                return;
            }

            if (manager != g_EngineFlamePrimaryManager && !g_EngineFlameSecondaryManager)
            {
                g_EngineFlameSecondaryManager = manager;
                Log(L"[FLAME] Observed secondary engine flame manager=0x%p\n", manager);
            }
        }

        static bool WritePointerValue(uintptr_t address, void* value)
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

        static const char* BoolText(bool value)
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

        static bool InstallInlineDetour32(InlineDetour32& detour,
                                          uintptr_t target,
                                          void* hook,
                                          size_t patchLen,
                                          const uint8_t* expectedBytes,
                                          size_t expectedLen)
        {
            if (!target || !hook || patchLen < 5 || patchLen > detour.original.size())
                return false;

            if (detour.trampoline)
                return true;

            auto* targetBytes = reinterpret_cast<uint8_t*>(target);
            if (expectedBytes && expectedLen > 0)
            {
                if (expectedLen > patchLen || memcmp(targetBytes, expectedBytes, expectedLen) != 0)
                    return false;
            }

            auto* trampolineBytes = reinterpret_cast<uint8_t*>(
                VirtualAlloc(nullptr, patchLen + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
            if (!trampolineBytes)
                return false;

            memcpy(detour.original.data(), targetBytes, patchLen);
            memcpy(trampolineBytes, targetBytes, patchLen);

            const uintptr_t resumeAddr = target + patchLen;
            trampolineBytes[patchLen] = 0xE9;
            const int32_t trampolineRel =
                static_cast<int32_t>(resumeAddr) -
                static_cast<int32_t>(reinterpret_cast<uintptr_t>(trampolineBytes + patchLen) + 5);
            memcpy(trampolineBytes + patchLen + 1, &trampolineRel, sizeof(trampolineRel));

            DWORD oldProtect = 0;
            if (!VirtualProtect(targetBytes, patchLen, PAGE_EXECUTE_READWRITE, &oldProtect))
            {
                VirtualFree(trampolineBytes, 0, MEM_RELEASE);
                return false;
            }

            targetBytes[0] = 0xE9;
            const int32_t hookRel =
                static_cast<int32_t>(reinterpret_cast<uintptr_t>(hook)) -
                static_cast<int32_t>(target + 5);
            memcpy(targetBytes + 1, &hookRel, sizeof(hookRel));
            for (size_t i = 5; i < patchLen; ++i)
                targetBytes[i] = 0x90;

            FlushInstructionCache(GetCurrentProcess(), targetBytes, patchLen);

            DWORD restoreProtect = 0;
            VirtualProtect(targetBytes, patchLen, oldProtect, &restoreProtect);

            detour.target = target;
            detour.hook = hook;
            detour.trampoline = trampolineBytes;
            detour.patchLen = patchLen;
            return true;
        }

        static bool ExpectedBytesMatchAt(uintptr_t address,
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
                out.craftState = ReadValueAtOffset<uint32_t>(person, kCraftStateOffset);
                out.curAnim = ReadValueAtOffset<long>(person, kPersonCurAnimOffset);
                out.animHandle = ReadValueAtOffset<int>(person, kPersonAnimHandleOffset);

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
                   lhs.craftState != rhs.craftState ||
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

            Log(L"[JUMPSNIPE] dt=%.3f handle=%d person=0x%08X obj=0x%08X state=%u->%u anim=%ld->%ld animH=%d->%d velY=%.3f->%.3f band=%hs->%hs sel=0x%08X->0x%08X slot=%d->%d sig=%hs->%hs odf=%hs->%hs sniper=%hs->%hs\n",
                dt,
                after.playerHandle,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(after.person)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(after.obj)),
                before.craftState,
                after.craftState,
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

        void __cdecl RecordDeathHook(int killedTeam, int killerTeam)
        {
            if (g_BzrFn_RecordDeath)
                g_BzrFn_RecordDeath(killedTeam, killerTeam);

            RecordMultiplayerCareerStats(killedTeam, killerTeam);
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

        static void InstallCareerStatsMpHookIfPossible()
        {
            if (g_CareerStatsMpHookInstalled)
                return;

            if (g_RecordDeathDetour.trampoline && g_BzrFn_RecordDeath)
            {
                g_CareerStatsMpHookInstalled = true;
                return;
            }

            const ULONGLONG nowMs = GetTickCount64();
            if (g_CareerStatsMpHookFirstAttemptTick == 0)
                g_CareerStatsMpHookFirstAttemptTick = nowMs;

            if (g_CareerStatsMpHookLastAttemptTick != 0 &&
                (nowMs - g_CareerStatsMpHookLastAttemptTick) < kCareerStatsMpHookRetryMs)
            {
                return;
            }

            g_CareerStatsMpHookLastAttemptTick = nowMs;
            g_CareerStatsMpHookInstallAttempted = true;

            static const uint8_t kExpectedRecordDeathBytes[kRecordDeathDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x10
            };

            if (!ExpectedBytesMatchAt(kGogRecordDeathEntryAddr,
                                      kExpectedRecordDeathBytes,
                                      sizeof(kExpectedRecordDeathBytes)))
            {
                if (!g_CareerStatsMpHookMismatchLogged)
                {
                    Log(L"[CAREER] RecordDeath entry bytes not settled yet at 0x%08X; retrying for up to %llums\n",
                        static_cast<uint32_t>(kGogRecordDeathEntryAddr),
                        static_cast<unsigned long long>(kCareerStatsMpHookRetryWindowMs));
                    g_CareerStatsMpHookMismatchLogged = true;
                }
                else if ((nowMs - g_CareerStatsMpHookFirstAttemptTick) >= kCareerStatsMpHookRetryWindowMs)
                {
                    Log(L"[CAREER] RecordDeath entry bytes still mismatched at 0x%08X after %llums; continuing guarded retries\n",
                        static_cast<uint32_t>(kGogRecordDeathEntryAddr),
                        static_cast<unsigned long long>(nowMs - g_CareerStatsMpHookFirstAttemptTick));
                    g_CareerStatsMpHookFirstAttemptTick = nowMs;
                }
                return;
            }

            if (!InstallInlineDetour32(g_RecordDeathDetour,
                                       kGogRecordDeathEntryAddr,
                                       reinterpret_cast<void*>(RecordDeathHook),
                                       kRecordDeathDetourLen,
                                       kExpectedRecordDeathBytes,
                                       sizeof(kExpectedRecordDeathBytes)))
            {
                Log(L"[CAREER] Failed installing RecordDeath hook at 0x%08X\n",
                    static_cast<uint32_t>(kGogRecordDeathEntryAddr));
                return;
            }

            g_BzrFn_RecordDeath =
                reinterpret_cast<FnRecordDeath>(g_RecordDeathDetour.trampoline);
            g_CareerStatsMpHookInstalled = (g_BzrFn_RecordDeath != nullptr);
            if (g_CareerStatsMpHookInstalled)
            {
                g_CareerStatsMpHookMismatchLogged = false;
                Log(L"[CAREER] Installed NetPlayer::RecordDeath hook entry=0x%08X trampoline=0x%08X path=%hs\n",
                    static_cast<uint32_t>(kGogRecordDeathEntryAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_RecordDeathDetour.trampoline)),
                    GetCareerStatsPath().string().c_str());
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

            g_BzrFn_GetPlayerHandle = reinterpret_cast<FnGetPlayerHandle>(kGogGetPlayerHandleAddr);
            g_BzrFn_GameObjectGetObjByHandle =
                reinterpret_cast<FnGameObjectGetObjByHandle>(kGogGameObjectGetObjByHandleAddr);

            static const uint8_t kExpectedPersonSimulateBytes[kPersonSimulateDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0xB8, 0x44, 0x10, 0x00, 0x00
            };

            if (!ExpectedBytesMatchAt(kGogPersonSimulateEntryAddr,
                                      kExpectedPersonSimulateBytes,
                                      sizeof(kExpectedPersonSimulateBytes)))
            {
                return;
            }

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
            AiTuningConfig tuning = {};
            if (!TryGetAiTuningForObject(craft, tuning))
                return;

            const bool applyRangeOverride =
                g_AiOdfGameplayTuningEnabled ||
                (tuning.bomberAiRole && g_BomberAiRangeEnabled);
            float minRange = 0.0f;
            bool hasMinRange = false;
            if (applyRangeOverride && tuning.hasEngageRangeAI)
            {
                minRange = (std::max)(minRange, tuning.engageRangeAI);
                hasMinRange = true;
            }
            if (applyRangeOverride && tuning.hasWeaponRangeMinAI)
            {
                minRange = (std::max)(minRange, tuning.weaponRangeMinAI);
                hasMinRange = true;
            }

            if (hasMinRange && std::isfinite(*range) && *range < minRange)
                *range = minRange;

            if (applyRangeOverride &&
                time &&
                (!std::isfinite(*time) || *time <= 0.0f))
            {
                *time = 1.0f;
            }

            if (tuning.bomberAiRole &&
                (EnvFlagEnabled("OPENSHIM_TRACE_BOMBER_RANGE") ||
                 EnvFlagEnabled("OPENSHIM_TRACE_AI_RANGE")))
            {
                const long remaining = InterlockedDecrement(&g_BomberRangeTraceBudget);
                if (remaining >= 0)
                {
                    char odfToken[kProducerBuildMenuTokenLen + 1] = {};
                    TryGetObjectOdfToken(craft, odfToken);
                    Log(L"[BOMBERRANGE] craft=0x%08X odf=%hs original=%.2f final=%.2f min=%.2f engage=%hs%.2f weaponMin=%hs%.2f derived=%hs close=%.2f time=%.2f weapon=0x%08X remaining=%ld\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                        odfToken[0] ? odfToken : "-",
                        originalRange,
                        *range,
                        minRange,
                        tuning.hasEngageRangeAI ? "" : "-",
                        tuning.engageRangeAI,
                        tuning.hasWeaponRangeMinAI ? "" : "-",
                        tuning.weaponRangeMinAI,
                        tuning.derivedBomberWeaponRangeAI ? "true" : "false",
                        closeRange ? *closeRange : -1.0f,
                        time ? *time : -1.0f,
                        weapon && *weapon ? static_cast<uint32_t>(reinterpret_cast<uintptr_t>(*weapon)) : 0u,
                        remaining);
                }
            }
        }

        static void ApplyRetargetPeriodAfterDoSubTask(void* processPtr)
        {
            if (!g_AiOdfGameplayTuningEnabled)
                return;

            if (!processPtr)
                return;

            auto* processBytes = reinterpret_cast<uint8_t*>(processPtr);
            void* objectPtr = *reinterpret_cast<void**>(processBytes + kUnitProcessObjectOffset);
            if (!objectPtr)
                return;

            AiTuningConfig tuning = {};
            if (!TryGetAiTuningForObject(objectPtr, tuning) ||
                !tuning.hasRetargetPeriodAI ||
                !std::isfinite(tuning.retargetPeriodAI) ||
                tuning.retargetPeriodAI <= 0.0f)
            {
                g_RetargetPeriodNextForceMsByProcess.erase(reinterpret_cast<uintptr_t>(processPtr));
                return;
            }

            float& nextEnemyCheck =
                *reinterpret_cast<float*>(processBytes + kUnitProcessNextEnemyCheckOffset);
            if (!std::isfinite(nextEnemyCheck) || nextEnemyCheck <= 0.0f)
                return;

            const ULONGLONG nowMs = GetTickCount64();
            const ULONGLONG periodMs = static_cast<ULONGLONG>(
                (std::max)(tuning.retargetPeriodAI, 0.01f) * 1000.0f);
            ULONGLONG& nextForceMs =
                g_RetargetPeriodNextForceMsByProcess[reinterpret_cast<uintptr_t>(processPtr)];
            if (nextForceMs == 0)
            {
                nextForceMs = nowMs + periodMs;
                return;
            }

            if (nowMs < nextForceMs)
                return;

            // These processes only look for a fresh enemy when this timer expires.
            nextEnemyCheck = 0.0f;
            nextForceMs = nowMs + periodMs;
        }

        static bool ShouldTraceAttackReveal()
        {
            return EnvFlagEnabled("OPENSHIM_TRACE_ATTACK_REVEAL") ||
                   EnvFlagEnabled("BZR_TRACE_ATTACK_REVEAL");
        }

        static void TraceAttackRevealEvent(const char* action,
                                           const char* reason,
                                           const char* sourceTag,
                                           void* processPtr,
                                           void* objectPtr,
                                           int perceivedTeam,
                                           int actualTeam)
        {
            if (!ShouldTraceAttackReveal())
                return;

            const long remaining = InterlockedDecrement(&g_AttackRevealTraceBudget);
            if (remaining < 0)
                return;

            Log(L"[AGGRO] trace remaining=%ld action=%hs reason=%hs source=%hs process=0x%08X object=0x%08X perceived=%d actual=%d enabled=%hs\n",
                remaining,
                action ? action : "unknown",
                reason ? reason : "unspecified",
                sourceTag ? sourceTag : "unknown",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(processPtr)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectPtr)),
                perceivedTeam,
                actualTeam,
                BoolText(g_AttackRevealEnabled));
        }

        static void RevealProcessOwnerPerceivedTeam(void* processPtr, const char* sourceTag)
        {
            if (!g_AttackRevealEnabled || !processPtr)
                return;

            __try
            {
                auto* processBytes = reinterpret_cast<uint8_t*>(processPtr);
                void* const objectPtr =
                    *reinterpret_cast<void**>(processBytes + kProcessOwnerObjectOffset);
                if (!objectPtr)
                {
                    TraceAttackRevealEvent("skip", "missing_owner", sourceTag, processPtr, nullptr, INT_MIN, INT_MIN);
                    return;
                }

                const int actualTeam = GetGameObjectTeamForLog(objectPtr);
                if (actualTeam == INT_MIN)
                {
                    TraceAttackRevealEvent("skip", "team_read_failed", sourceTag, processPtr, objectPtr, INT_MIN, INT_MIN);
                    return;
                }

                auto* objectBytes = reinterpret_cast<uint8_t*>(objectPtr);
                int& perceivedTeam =
                    *reinterpret_cast<int*>(objectBytes + kGameObjectPerceivedTeamOffset);
                const int previousPerceivedTeam = perceivedTeam;
                if (previousPerceivedTeam == actualTeam)
                {
                    TraceAttackRevealEvent("noop", "already_revealed", sourceTag, processPtr, objectPtr, previousPerceivedTeam, actualTeam);
                    return;
                }

                perceivedTeam = actualTeam;
                TraceAttackRevealEvent("write", "revealed", sourceTag, processPtr, objectPtr, previousPerceivedTeam, actualTeam);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                TraceAttackRevealEvent("fault", "access_fault", sourceTag, processPtr, nullptr, INT_MIN, INT_MIN);
            }
        }

        bool __fastcall OffensiveProcessDoSubTaskHook(void* thisPtr, void* /*edx*/)
        {
            const bool result =
                g_BzrFn_OffensiveProcessDoSubTask
                    ? g_BzrFn_OffensiveProcessDoSubTask(thisPtr)
                    : false;
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

        void __fastcall ShieldTowerSimulateTeamFilterHook(void* thisPtr, void* /*edx*/, float dt)
        {
            RunShieldTowerFilteredSimulate(thisPtr, dt);
        }

        static void InstallShieldTowerTeamFilterHookIfPossible()
        {
            if (g_ShieldTowerSimulateHookInstalled)
                return;

            if (!g_BzrFn_ShieldTowerSimulateOriginal)
                g_BzrFn_ShieldTowerSimulateOriginal =
                    reinterpret_cast<FnShieldTowerSimulate>(kGogShieldTowerSimulateAddr);
            if (!g_BzrFn_BuildingSimulate)
                g_BzrFn_BuildingSimulate =
                    reinterpret_cast<FnShieldTowerSimulate>(kGogBuildingSimulateAddr);
            if (!g_BzrFn_ShieldTowerPowerUpdate)
                g_BzrFn_ShieldTowerPowerUpdate =
                    reinterpret_cast<FnShieldTowerPowerUpdate>(kGogShieldTowerPowerUpdateAddr);
            if (!g_BzrFn_GameObjectFriendP)
                g_BzrFn_GameObjectFriendP =
                    reinterpret_cast<FnGameObjectRelation>(kGogGameObjectFriendPAddr);
            if (!g_BzrFn_GameObjectEnemyP)
                g_BzrFn_GameObjectEnemyP =
                    reinterpret_cast<FnGameObjectRelation>(kGogGameObjectEnemyPAddr);
            if (!g_BzrFn_GameObjectGetObjByHandle)
                g_BzrFn_GameObjectGetObjByHandle =
                    reinterpret_cast<FnGameObjectGetObjByHandle>(kGogGameObjectGetObjByHandleAddr);
            if (!g_BzrFn_MatrixInverse)
                g_BzrFn_MatrixInverse =
                    reinterpret_cast<FnMatrixInverse>(kGogMatrixInverseAddr);
            if (!g_BzrFn_VectorTransform)
                g_BzrFn_VectorTransform =
                    reinterpret_cast<FnVectorTransform>(kGogVectorTransformAddr);
            if (!g_BzrFn_CollisionRangeSearch)
                g_BzrFn_CollisionRangeSearch =
                    reinterpret_cast<FnRangeSearch>(kGogRangeSearchAddr);
            if (!g_BzrFn_RangeResultsGetNext)
                g_BzrFn_RangeResultsGetNext =
                    reinterpret_cast<FnRangeResultsGetNext>(kGogRangeResultsGetNextAddr);

            void* current = nullptr;
            __try
            {
                current = *reinterpret_cast<void**>(kShieldTowerSimulateVtableSlotAddr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                current = nullptr;
            }

            if (current != reinterpret_cast<void*>(ShieldTowerSimulateTeamFilterHook) &&
                current != reinterpret_cast<void*>(kGogShieldTowerSimulateAddr))
            {
                Log(L"[SHIELDODF] ShieldTower::Simulate vtable mismatch slot=0x%08X current=0x%08X expected=0x%08X\n",
                    static_cast<uint32_t>(kShieldTowerSimulateVtableSlotAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                    static_cast<uint32_t>(kGogShieldTowerSimulateAddr));
                return;
            }

            const bool patched =
                (current == reinterpret_cast<void*>(ShieldTowerSimulateTeamFilterHook)) ||
                WritePointerValue(kShieldTowerSimulateVtableSlotAddr,
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
                    static_cast<uint32_t>(kShieldTowerSimulateVtableSlotAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_ShieldTowerSimulateOriginal)));
            }
        }

        static void InstallAiTuningHooksIfPossible()
        {
            if (g_CalcRangeCraftHookInstalled && g_RetargetPeriodHooksInstalled)
                return;

            if (g_CalcRangeCraftDetour.trampoline && g_BzrFn_CalcRangeCraft)
            {
                g_CalcRangeCraftHookInstalled = true;
            }

            if (!g_CalcRangeCraftHookInstalled)
            {
                static const uint8_t kExpectedCalcRangeCraftBytes[kCalcRangeCraftDetourLen] =
                {
                    0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C, 0x89, 0x4D
                };

                if (!ExpectedBytesMatchAt(kGogCalcRangeCraftEntryAddr,
                                          kExpectedCalcRangeCraftBytes,
                                          sizeof(kExpectedCalcRangeCraftBytes)))
                {
                    Log(L"[AIODF] CalcRange(Craft) entry bytes mismatch at 0x%08X; AI ODF range tuning disabled\n",
                        static_cast<uint32_t>(kGogCalcRangeCraftEntryAddr));
                }
                else if (!InstallInlineDetour32(g_CalcRangeCraftDetour,
                                                kGogCalcRangeCraftEntryAddr,
                                                reinterpret_cast<void*>(CalcRangeCraftHook),
                                                kCalcRangeCraftDetourLen,
                                                kExpectedCalcRangeCraftBytes,
                                                sizeof(kExpectedCalcRangeCraftBytes)))
                {
                    Log(L"[AIODF] Failed installing CalcRange(Craft) hook at 0x%08X\n",
                        static_cast<uint32_t>(kGogCalcRangeCraftEntryAddr));
                }
                else
                {
                    g_BzrFn_CalcRangeCraft =
                        reinterpret_cast<FnCalcRangeCraft>(g_CalcRangeCraftDetour.trampoline);
                    g_CalcRangeCraftHookInstalled = (g_BzrFn_CalcRangeCraft != nullptr);
                    if (g_CalcRangeCraftHookInstalled)
                    {
                        Log(L"[AIODF] Installed CalcRange(Craft) hook entry=0x%08X trampoline=0x%08X\n",
                            static_cast<uint32_t>(kGogCalcRangeCraftEntryAddr),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_CalcRangeCraftDetour.trampoline)));
                    }
                }
            }

            if (g_RetargetPeriodHooksInstalled)
                return;

            if (g_OffensiveProcessDoSubTaskDetour.trampoline && g_BzrFn_OffensiveProcessDoSubTask &&
                g_GunTowerProcessDoSubTaskDetour.trampoline && g_BzrFn_GunTowerProcessDoSubTask)
            {
                g_RetargetPeriodHooksInstalled = true;
                return;
            }

            static const uint8_t kExpectedOffensiveProcessDoSubTaskBytes[kOffensiveProcessDoSubTaskDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0xE8, 0xB8, 0x15, 0xF8, 0xFF
            };
            static const uint8_t kExpectedGunTowerProcessDoSubTaskBytes[kGunTowerProcessDoSubTaskDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x5C
            };

            bool offensiveInstalled = false;
            if (ExpectedBytesMatchAt(kGogOffensiveProcessDoSubTaskEntryAddr,
                                     kExpectedOffensiveProcessDoSubTaskBytes,
                                     sizeof(kExpectedOffensiveProcessDoSubTaskBytes)) &&
                InstallInlineDetour32(g_OffensiveProcessDoSubTaskDetour,
                                      kGogOffensiveProcessDoSubTaskEntryAddr,
                                      reinterpret_cast<void*>(OffensiveProcessDoSubTaskHook),
                                      kOffensiveProcessDoSubTaskDetourLen,
                                      kExpectedOffensiveProcessDoSubTaskBytes,
                                      sizeof(kExpectedOffensiveProcessDoSubTaskBytes)))
            {
                g_BzrFn_OffensiveProcessDoSubTask =
                    reinterpret_cast<FnProcessDoSubTask>(g_OffensiveProcessDoSubTaskDetour.trampoline);
                offensiveInstalled = (g_BzrFn_OffensiveProcessDoSubTask != nullptr);
                if (offensiveInstalled)
                {
                    Log(L"[AIODF] Installed OffensiveProcess::DoSubTask hook entry=0x%08X trampoline=0x%08X\n",
                        static_cast<uint32_t>(kGogOffensiveProcessDoSubTaskEntryAddr),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_OffensiveProcessDoSubTaskDetour.trampoline)));
                }
            }
            else
            {
                Log(L"[AIODF] OffensiveProcess::DoSubTask entry bytes mismatch at 0x%08X; shared retarget tuning disabled there\n",
                    static_cast<uint32_t>(kGogOffensiveProcessDoSubTaskEntryAddr));
            }

            bool gunTowerInstalled = false;
            if (ExpectedBytesMatchAt(kGogGunTowerProcessDoSubTaskEntryAddr,
                                     kExpectedGunTowerProcessDoSubTaskBytes,
                                     sizeof(kExpectedGunTowerProcessDoSubTaskBytes)) &&
                InstallInlineDetour32(g_GunTowerProcessDoSubTaskDetour,
                                      kGogGunTowerProcessDoSubTaskEntryAddr,
                                      reinterpret_cast<void*>(GunTowerProcessDoSubTaskHook),
                                      kGunTowerProcessDoSubTaskDetourLen,
                                      kExpectedGunTowerProcessDoSubTaskBytes,
                                      sizeof(kExpectedGunTowerProcessDoSubTaskBytes)))
            {
                g_BzrFn_GunTowerProcessDoSubTask =
                    reinterpret_cast<FnProcessDoSubTask>(g_GunTowerProcessDoSubTaskDetour.trampoline);
                gunTowerInstalled = (g_BzrFn_GunTowerProcessDoSubTask != nullptr);
                if (gunTowerInstalled)
                {
                    Log(L"[AIODF] Installed GunTowerProcess::DoSubTask hook entry=0x%08X trampoline=0x%08X\n",
                        static_cast<uint32_t>(kGogGunTowerProcessDoSubTaskEntryAddr),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_GunTowerProcessDoSubTaskDetour.trampoline)));
                }
            }
            else
            {
                Log(L"[AIODF] GunTowerProcess::DoSubTask entry bytes mismatch at 0x%08X; tower retarget tuning disabled there\n",
                    static_cast<uint32_t>(kGogGunTowerProcessDoSubTaskEntryAddr));
            }

            g_RetargetPeriodHooksInstalled = offensiveInstalled && gunTowerInstalled;
        }

        static bool ShouldTraceConstructorRemoteBuildFix()
        {
            return EnvFlagEnabled("OPENSHIM_TRACE_CONSTRUCTOR_REMOTE_BUILD") ||
                   EnvFlagEnabled("OPENSHIM_TRACE_CONSTRUCTOR_BUILD_CLEANUP") ||
                   EnvFlagEnabled("BZR_TRACE_CONSTRUCTOR_REMOTE_BUILD");
        }

        static void TraceConstructorRemoteBuildEvent(const char* action,
                                                     const char* reason,
                                                     void* unitPtr,
                                                     const ConstructorCleanupSnapshot* snapshot)
        {
            if (!ShouldTraceConstructorRemoteBuildFix())
                return;

            const long remaining = InterlockedDecrement(&g_ConstructorRemoteBuildTraceBudget);
            if (remaining < 0)
                return;

            const ConstructorCleanupSnapshot empty = {};
            const ConstructorCleanupSnapshot& current = snapshot ? *snapshot : empty;
            Log(L"[AICONSTRUCT] trace remaining=%ld action=%hs reason=%hs team=%d teamPtr=0x%08X unit=0x%08X constructType=%u cost=%u constructing=%u account=%u reservedArea=%u helpers=end:%hs reserved:%hs refund:%hs add:%hs stop:%hs\n",
                remaining,
                action ? action : "unknown",
                reason ? reason : "unspecified",
                current.teamId,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current.teamPtr)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(unitPtr)),
                current.constructType,
                current.constructCost,
                current.constructing,
                current.account,
                current.reservedArea,
                BoolText(g_BzrFn_AIBuildConstructionEnd != nullptr),
                BoolText(g_BzrFn_AIBuildReservedAreaRemove != nullptr),
                BoolText(g_BzrFn_AISpentCreditRefund != nullptr),
                BoolText(g_BzrFn_AIBuildUnassignedCCAdd != nullptr),
                BoolText(g_BzrFn_UnitsSOrderStop != nullptr));
        }

        static bool TryCaptureConstructorCleanupSnapshot(void* unitPtr,
                                                        ConstructorCleanupSnapshot& outSnapshot,
                                                        const char** outReason)
        {
            outSnapshot = {};
            if (outReason)
                *outReason = "unknown";
            if (!unitPtr)
            {
                if (outReason)
                    *outReason = "null_unit";
                return false;
            }

            __try
            {
                if (*reinterpret_cast<const uint32_t*>(kAiGameInitialisedAddr) == 0)
                {
                    if (outReason)
                        *outReason = "ai_not_ready";
                    return false;
                }

                auto* unitBytes = reinterpret_cast<const uint8_t*>(unitPtr);
                const int teamId =
                    static_cast<int>(*reinterpret_cast<const int8_t*>(unitBytes + kUnitTeamOffset));
                if (teamId < 0)
                {
                    if (outReason)
                        *outReason = "team_invalid";
                    return false;
                }

                auto* teamAicontrol =
                    reinterpret_cast<const uint8_t*>(kAiTeamDataBaseAddr + (teamId * kAiTeamDataStride));
                if (*teamAicontrol == 0)
                {
                    if (outReason)
                        *outReason = "team_not_ai";
                    return false;
                }

                auto* teamTable = reinterpret_cast<void* const*>(kAiTeamTableAddr);
                outSnapshot.teamPtr = teamTable[teamId];
                if (!outSnapshot.teamPtr)
                {
                    if (outReason)
                        *outReason = "team_ptr_missing";
                    return false;
                }

                void* typePtr = *reinterpret_cast<void* const*>(unitBytes + kUnitTypeOffset);
                if (!typePtr)
                {
                    if (outReason)
                        *outReason = "missing_type";
                    return false;
                }

                const uint32_t abilities =
                    *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(typePtr) +
                                                       kUnitTypeAbilitiesOffset);
                if ((abilities & kConstructorAbilityMask) == 0)
                {
                    if (outReason)
                        *outReason = "not_constructor";
                    return false;
                }

                outSnapshot.teamId = teamId;
                outSnapshot.constructType =
                    *reinterpret_cast<const uint32_t*>(unitBytes + kUnitAiConstructTypeOffset);
                outSnapshot.constructCost =
                    *reinterpret_cast<const uint32_t*>(unitBytes + kUnitAiConstructCostOffset);
                outSnapshot.constructing =
                    *reinterpret_cast<const uint32_t*>(unitBytes + kUnitAiConstructingOffset);
                outSnapshot.reservedArea =
                    *reinterpret_cast<const uint32_t*>(unitBytes + kUnitAiReservedAreaOffset);
                outSnapshot.account =
                    *reinterpret_cast<const uint32_t*>(unitBytes + kUnitAiAccountOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outSnapshot = {};
                if (outReason)
                    *outReason = "access_fault";
                return false;
            }

            if (outReason)
                *outReason = "eligible";
            return true;
        }

        static bool TryApplyConstructorRemoteBuildDeathCleanup(void* unitPtr,
                                                               ConstructorCleanupSnapshot& outSnapshot,
                                                               const char** outReason)
        {
            outSnapshot = {};
            if (outReason)
                *outReason = "unknown";

            if (!g_ConstructorRemoteBuildFixEnabled ||
                !g_BzrFn_AIBuildConstructionEnd ||
                !g_BzrFn_AIBuildReservedAreaRemove ||
                !g_BzrFn_AISpentCreditRefund ||
                !g_BzrFn_AIBuildUnassignedCCAdd ||
                !unitPtr)
            {
                if (outReason)
                    *outReason = !g_ConstructorRemoteBuildFixEnabled
                        ? "fix_disabled"
                        : (!unitPtr ? "null_unit" : "helpers_missing");
                return false;
            }

            if (!TryCaptureConstructorCleanupSnapshot(unitPtr, outSnapshot, outReason))
                return false;

            if (outSnapshot.constructType == 0)
            {
                if (outReason)
                    *outReason = "construct_type_zero";
                return false;
            }

            if (outSnapshot.constructing == 0)
            {
                if (outReason)
                    *outReason = "constructing_zero";
                return false;
            }

            g_BzrFn_AIBuildConstructionEnd(outSnapshot.teamId, static_cast<int>(outSnapshot.constructType));
            g_BzrFn_AIBuildReservedAreaRemove(outSnapshot.teamId, static_cast<int>(outSnapshot.reservedArea));
            g_BzrFn_AISpentCreditRefund(outSnapshot.teamId, nullptr, unitPtr);
            if (outSnapshot.teamPtr)
                g_BzrFn_AIBuildUnassignedCCAdd(outSnapshot.teamPtr, unitPtr);
            if (g_BzrFn_UnitsSOrderStop)
                g_BzrFn_UnitsSOrderStop(unitPtr);

            auto* unitBytes = reinterpret_cast<uint8_t*>(unitPtr);
            *reinterpret_cast<uint32_t*>(unitBytes + kUnitAiConstructTypeOffset) = 0;
            *reinterpret_cast<uint32_t*>(unitBytes + kUnitAiConstructCostOffset) = 0;
            *reinterpret_cast<uint32_t*>(unitBytes + kUnitAiConstructingOffset) = 0;
            *reinterpret_cast<uint32_t*>(unitBytes + kUnitAiAccountOffset) = 0;
            *reinterpret_cast<uint32_t*>(unitBytes + kUnitAiReservedAreaOffset) = 0;

            Log(L"[AICONSTRUCT] Applied constructor death cleanup action=death_cleanup team=%d teamPtr=0x%08X unit=0x%08X constructType=%u cost=%u constructing=%u account=%u reservedArea=%u end=0x%08X reserved=0x%08X refund=0x%08X add=0x%08X stop=0x%08X\n",
                outSnapshot.teamId,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(outSnapshot.teamPtr)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(unitPtr)),
                outSnapshot.constructType,
                outSnapshot.constructCost,
                outSnapshot.constructing,
                outSnapshot.account,
                outSnapshot.reservedArea,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_AIBuildConstructionEnd)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_AIBuildReservedAreaRemove)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_AISpentCreditRefund)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_AIBuildUnassignedCCAdd)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_UnitsSOrderStop)));

            if (outReason)
                *outReason = "applied";
            TraceConstructorRemoteBuildEvent("death_cleanup", "applied", unitPtr, &outSnapshot);

            return true;
        }

        void __cdecl AIUnitRemoveConstructorCleanupHook(void* unitPtr)
        {
            ConstructorCleanupSnapshot snapshot = {};
            const char* reason = nullptr;
            const bool applied = TryApplyConstructorRemoteBuildDeathCleanup(unitPtr, snapshot, &reason);

            TraceConstructorRemoteBuildEvent(applied ? "forward_after_cleanup" : "fallback", reason, unitPtr, &snapshot);
            if (g_BzrFn_AIUnitRemove)
                g_BzrFn_AIUnitRemove(unitPtr);
        }

        static void InstallConstructorRemoteBuildFixIfPossible()
        {
            if (!g_ConstructorRemoteBuildFixEnabled)
                return;

            if (g_ConstructorRemoteBuildFixInstalled)
                return;

            if (g_AIUnitRemoveDetour.trampoline && g_BzrFn_AIUnitRemove)
            {
                g_ConstructorRemoteBuildFixInstalled = true;
                return;
            }

            static const uint8_t kExpectedAIUnitRemoveBytes[kAIUnitRemoveDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x51, 0x83, 0x3D, 0x08, 0x0F, 0x93, 0x00, 0x00
            };

            if (!ExpectedBytesMatchAt(kGogAIUnitRemoveEntryAddr,
                                      kExpectedAIUnitRemoveBytes,
                                      sizeof(kExpectedAIUnitRemoveBytes)))
            {
                Log(L"[AICONSTRUCT] AI_UnitRemove entry bytes mismatch at 0x%08X; constructor death cleanup fix disabled\n",
                    static_cast<uint32_t>(kGogAIUnitRemoveEntryAddr));
                return;
            }

            if (!InstallInlineDetour32(g_AIUnitRemoveDetour,
                                       kGogAIUnitRemoveEntryAddr,
                                       reinterpret_cast<void*>(AIUnitRemoveConstructorCleanupHook),
                                       kAIUnitRemoveDetourLen,
                                       kExpectedAIUnitRemoveBytes,
                                       sizeof(kExpectedAIUnitRemoveBytes)))
            {
                Log(L"[AICONSTRUCT] Failed installing AI_UnitRemove cleanup hook at 0x%08X\n",
                    static_cast<uint32_t>(kGogAIUnitRemoveEntryAddr));
                return;
            }

            g_BzrFn_AIUnitRemove =
                reinterpret_cast<FnAIUnitRemove>(g_AIUnitRemoveDetour.trampoline);
            g_ConstructorRemoteBuildFixInstalled = (g_BzrFn_AIUnitRemove != nullptr);
            if (g_ConstructorRemoteBuildFixInstalled)
            {
                Log(L"[AICONSTRUCT] Installed AI_UnitRemove cleanup hook entry=0x%08X trampoline=0x%08X trace=%hs\n",
                    static_cast<uint32_t>(kGogAIUnitRemoveEntryAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_AIUnitRemoveDetour.trampoline)),
                    BoolText(ShouldTraceConstructorRemoteBuildFix()));
            }
        }

        static void EnsureEngineFlameVtableHooksInstalled(void* manager)
        {
            if (!g_IsSteamExe || g_EngineFlameVtableHooksInstalled || !manager)
                return;

            auto** vtable = *reinterpret_cast<void***>(manager);
            if (!vtable)
                return;

            const uintptr_t controlSlot =
                reinterpret_cast<uintptr_t>(vtable) + kEngineFlameControlVtableOffset;
            const uintptr_t submitSlot =
                reinterpret_cast<uintptr_t>(vtable) + kEngineFlameSubmitVtableOffset;
            const size_t controlIndex = kEngineFlameControlVtableOffset / sizeof(void*);
            const size_t submitIndex = kEngineFlameSubmitVtableOffset / sizeof(void*);

            if (!g_BzrFn_EngineFlameControl)
            {
                g_BzrFn_EngineFlameControl =
                    reinterpret_cast<FnEngineFlameControl>(vtable[controlIndex]);
            }
            if (!g_BzrFn_EngineFlameSubmit)
            {
                g_BzrFn_EngineFlameSubmit =
                    reinterpret_cast<FnEngineFlameSubmit>(vtable[submitIndex]);
            }

            const bool controlPatched =
                (vtable[controlIndex] == reinterpret_cast<void*>(EngineFlameControlHook)) ||
                WritePointerValue(controlSlot, reinterpret_cast<void*>(EngineFlameControlHook));
            const bool submitPatched =
                (vtable[submitIndex] == reinterpret_cast<void*>(EngineFlameSubmitHook)) ||
                WritePointerValue(submitSlot, reinterpret_cast<void*>(EngineFlameSubmitHook));

            g_EngineFlameVtableHooksInstalled = controlPatched && submitPatched;
            if (g_EngineFlameVtableHooksInstalled && !g_LoggedEngineFlameVtableHook)
            {
                Log(L"[FLAME] Patched Steam engine flame vtable control=0x%08X submit=0x%08X\n",
                    static_cast<uint32_t>(controlSlot),
                    static_cast<uint32_t>(submitSlot));
                g_LoggedEngineFlameVtableHook = true;
            }
        }

        static uint32_t ResolveCraftHandle(void* craftPtr)
        {
            if (!craftPtr)
                return 0;

            auto* bytes = reinterpret_cast<uint8_t*>(craftPtr);
            const uint32_t low = *reinterpret_cast<uint32_t*>(bytes + kCraftHandleLoOffset);
            if (low == 0)
                return 0;

            const uint32_t high = *reinterpret_cast<uint32_t*>(bytes + kCraftHandleHiOffset);
            return ((high & 0x0FFFu) << 20) | (low & 0x000FFFFFu);
        }

        static void ResetEngineFlameQueue(void* manager)
        {
            if (!manager)
                return;

            auto* bytes = reinterpret_cast<uint8_t*>(manager);
            *reinterpret_cast<uintptr_t*>(bytes + kEngineFlameFlamePtrOffset) =
                reinterpret_cast<uintptr_t>(bytes + 0x28);
        }

        static void SetEngineFlameTexture(void* manager, int textureHandle)
        {
            if (!manager)
                return;

            auto* bytes = reinterpret_cast<uint8_t*>(manager);
            *reinterpret_cast<int*>(bytes + kEngineFlameFlameTextureOffset) = textureHandle;
        }

        static FnExuGetTeamEngineFlameColor ResolveExuTeamEngineFlameColor()
        {
            HMODULE exuModule = GetModuleHandleA("exu.dll");
            if (!exuModule)
                exuModule = GetModuleHandleA("ExtraUtilities.dll");

            if (!exuModule)
            {
                g_ExuFn_GetTeamEngineFlameColor = nullptr;
                g_ExuTeamEngineFlameColorModule = nullptr;
                if (!g_LoggedExuEngineFlameBridgeMissing)
                {
                    Log(L"[FLAME] EXU module not loaded; team engine flame colors default to stock blue\n");
                    g_LoggedExuEngineFlameBridgeMissing = true;
                }
                return nullptr;
            }

            if (g_ExuFn_GetTeamEngineFlameColor && g_ExuTeamEngineFlameColorModule == exuModule)
                return g_ExuFn_GetTeamEngineFlameColor;

            auto* proc = reinterpret_cast<FnExuGetTeamEngineFlameColor>(
                GetProcAddress(exuModule, "EXU_GetTeamEngineFlameColor"));
            if (!proc)
            {
                g_ExuFn_GetTeamEngineFlameColor = nullptr;
                g_ExuTeamEngineFlameColorModule = nullptr;
                if (!g_LoggedExuEngineFlameBridgeMissing)
                {
                    Log(L"[FLAME] EXU_GetTeamEngineFlameColor export missing; team engine flame colors disabled\n");
                    g_LoggedExuEngineFlameBridgeMissing = true;
                }
                return nullptr;
            }

            g_ExuFn_GetTeamEngineFlameColor = proc;
            g_ExuTeamEngineFlameColorModule = exuModule;
            g_LoggedExuEngineFlameBridgeMissing = false;
            if (!g_LoggedExuEngineFlameBridge)
            {
                Log(L"[FLAME] Connected EXU engine flame color bridge from module=0x%p\n", exuModule);
                g_LoggedExuEngineFlameBridge = true;
            }
            return g_ExuFn_GetTeamEngineFlameColor;
        }

        static int ResolveTeamEngineFlameColor(int team)
        {
            if (team <= 0)
                return kEngineFlameColorDefault;

            auto* exuGetColor = ResolveExuTeamEngineFlameColor();
            if (!exuGetColor)
                return kEngineFlameColorDefault;

            int color = kEngineFlameColorDefault;
            __try
            {
                color = exuGetColor(team);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_ExuFn_GetTeamEngineFlameColor = nullptr;
                g_ExuTeamEngineFlameColorModule = nullptr;
                if (!g_LoggedExuEngineFlameBridgeMissing)
                {
                    Log(L"[FLAME] EXU engine flame color bridge call faulted; disabling cached bridge and falling back to stock blue\n");
                    g_LoggedExuEngineFlameBridgeMissing = true;
                }
                return kEngineFlameColorDefault;
            }
            if (color < kEngineFlameColorDefault || color > kEngineFlameColorGreen)
                return kEngineFlameColorDefault;
            return color;
        }

        static int ResolveEngineFlameTextureHandle(const char* const* candidates, size_t count, const wchar_t* colorName)
        {
            if (!g_BzrFn_EngineFlameResolveTexture || !candidates || count == 0)
                return 0;

            for (size_t i = 0; i < count; ++i)
            {
                const char* candidate = candidates[i];
                if (!candidate || !candidate[0])
                    continue;

                BzrString textureName = {};
                BzrStringInitEmpty(&textureName);
                BzrStringAssign(&textureName, candidate, std::strlen(candidate));
                const int textureHandle = g_BzrFn_EngineFlameResolveTexture(&textureName);
                BzrStringFree(&textureName);

                if (textureHandle != 0)
                {
                    Log(L"[FLAME] Resolved %ls engine flame texture '%hs' => 0x%08X\n",
                        colorName ? colorName : L"unknown",
                        candidate,
                        textureHandle);
                    return textureHandle;
                }
            }

            Log(L"[FLAME] Failed to resolve any %ls engine flame texture candidate\n",
                colorName ? colorName : L"unknown");
            return 0;
        }

        static void CloneEngineFlameManager(void* destination, const void* source, int textureHandle)
        {
            if (!destination || !source || textureHandle == 0)
                return;

            std::memcpy(destination, source, kEngineFlameObjectSize);
            ResetEngineFlameQueue(destination);
            SetEngineFlameTexture(destination, textureHandle);
        }

        static void EnsureEngineFlameVariantsInitialized()
        {
            if (g_EngineFlameVariantsInitialized)
                return;

            if (g_IsSteamExe)
                ResolveEngineFlameRuntimeTargets();

            if (!GetEngineFlamePrimary() || !GetEngineFlameSecondary() || !g_BzrFn_EngineFlameResolveTexture)
                return;

            if (g_EngineFlameVariantsInitAttempted)
                return;

            g_EngineFlameVariantsInitAttempted = true;

            static const char* const kRedTextureCandidates[] =
            {
                "exhaust_r.0",
                "rflame.0",
                "rflame",
            };
            static const char* const kGreenTextureCandidates[] =
            {
                "exhaust_g.0",
                "gflame.0",
                "gflame",
            };

            g_EngineFlamePrimaryRedTexture =
                ResolveEngineFlameTextureHandle(kRedTextureCandidates, _countof(kRedTextureCandidates), L"red");
            g_EngineFlamePrimaryGreenTexture =
                ResolveEngineFlameTextureHandle(kGreenTextureCandidates, _countof(kGreenTextureCandidates), L"green");

            void* primary = GetEngineFlamePrimary();
            void* secondary = GetEngineFlameSecondary();
            if (g_EngineFlamePrimaryRedTexture != 0)
            {
                CloneEngineFlameManager(g_EngineFlamePrimaryRed, primary, g_EngineFlamePrimaryRedTexture);
                CloneEngineFlameManager(g_EngineFlameSecondaryRed, secondary, g_EngineFlamePrimaryRedTexture);
            }

            if (g_EngineFlamePrimaryGreenTexture != 0)
            {
                CloneEngineFlameManager(g_EngineFlamePrimaryGreen, primary, g_EngineFlamePrimaryGreenTexture);
                CloneEngineFlameManager(g_EngineFlameSecondaryGreen, secondary, g_EngineFlamePrimaryGreenTexture);
            }

            g_EngineFlameVariantsInitialized = true;
            Log(L"[FLAME] Engine flame variants initialized red=%hs green=%hs\n",
                g_EngineFlamePrimaryRedTexture != 0 ? "yes" : "no",
                g_EngineFlamePrimaryGreenTexture != 0 ? "yes" : "no");
        }

        static void* SelectEngineFlameManager(void* originalManager, void* craftPtr)
        {
            if (!originalManager || !craftPtr)
                return originalManager;

            if (originalManager != GetEngineFlamePrimary() && originalManager != GetEngineFlameSecondary())
                return originalManager;

            if (g_IsSteamExe)
                ResolveEngineFlameRuntimeTargets();

            if (!g_BzrFn_GetTeamNum)
                return originalManager;

            const uint32_t handle = ResolveCraftHandle(craftPtr);
            if (handle == 0)
                return originalManager;

            const int team = g_BzrFn_GetTeamNum(static_cast<int>(handle));
            const int color = ResolveTeamEngineFlameColor(team);
            if (color == kEngineFlameColorDefault || color == kEngineFlameColorBlue)
                return originalManager;

            EnsureEngineFlameVariantsInitialized();

            if (color == kEngineFlameColorRed && g_EngineFlamePrimaryRedTexture != 0)
            {
                return (originalManager == GetEngineFlamePrimary())
                    ? static_cast<void*>(g_EngineFlamePrimaryRed)
                    : static_cast<void*>(g_EngineFlameSecondaryRed);
            }

            if (color == kEngineFlameColorGreen && g_EngineFlamePrimaryGreenTexture != 0)
            {
                return (originalManager == GetEngineFlamePrimary())
                    ? static_cast<void*>(g_EngineFlamePrimaryGreen)
                    : static_cast<void*>(g_EngineFlameSecondaryGreen);
            }

            return originalManager;
        }

        static bool ShouldTraceArtilleryMask()
        {
            static int s_cached = -1;
            if (s_cached < 0)
            {
                s_cached =
                    (EnvFlagEnabled("OPENSHIM_TRACE_ARTILLERY_MASK") ||
                     EnvFlagEnabled("OPENSHIM_TRACE_WEAPON_MASK")) ? 1 : 0;
            }
            return s_cached != 0;
        }

        static int FilterVehicleAssetDebugException(
            unsigned int code,
            const char* stage,
            const BzrString* assetName)
        {
            if (code == kDbgPrintExceptionAnsi || code == kDbgPrintExceptionWide)
            {
                Log(L"[VEHICLE] Swallowed debug-print exception during %hs for asset '%hs' (code=0x%08X)\n",
                    stage ? stage : "unknown",
                    assetName ? BzrStringData(assetName) : "",
                    code);
                return EXCEPTION_EXECUTE_HANDLER;
            }

            return EXCEPTION_CONTINUE_SEARCH;
        }

        static bool CopyVehicleAssetName(
            const BzrString* assetName,
            char (&buffer)[64])
        {
            buffer[0] = '\0';
            if (!assetName)
                return false;

            const char* name = BzrStringData(assetName);
            if (!name || !name[0])
                return false;

            strncpy_s(buffer, name, _TRUNCATE);
            return buffer[0] != '\0';
        }

        static bool TickIsBefore(DWORD lhs, DWORD rhs)
        {
            return static_cast<long>(lhs - rhs) < 0;
        }

        static VehicleAssetExceptionCacheEntry* FindVehicleAssetExceptionEntry(const char* assetName)
        {
            if (!assetName || !assetName[0])
                return nullptr;

            for (auto& entry : g_VehicleAssetExceptionCache)
            {
                if (entry.assetName[0] && _stricmp(entry.assetName, assetName) == 0)
                    return &entry;
            }

            return nullptr;
        }

        static VehicleAssetExceptionCacheEntry* GetVehicleAssetExceptionSlot()
        {
            VehicleAssetExceptionCacheEntry* oldest = &g_VehicleAssetExceptionCache[0];
            for (auto& entry : g_VehicleAssetExceptionCache)
            {
                if (!entry.assetName[0])
                    return &entry;
                if (TickIsBefore(entry.suppressUntil, oldest->suppressUntil))
                    oldest = &entry;
            }
            return oldest;
        }

        static std::filesystem::path GetMainModuleDirectory()
        {
            char path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return {};

            return std::filesystem::path(path).parent_path();
        }

        static std::string TrimAsciiCopy(const std::string& value)
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

        static std::string HumanizeInputBindingCommand(const std::string& command)
        {
            if (command.empty())
                return {};

            std::string text = command;
            for (char& ch : text)
            {
                if (ch == '_')
                    ch = ' ';
                else
                    ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            }

            bool capitalizeNext = true;
            for (char& ch : text)
            {
                if (std::isspace(static_cast<unsigned char>(ch)))
                {
                    capitalizeNext = true;
                    continue;
                }

                if (capitalizeNext)
                {
                    ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
                    capitalizeNext = false;
                }
            }

            return text;
        }

        static GameKeyBindingAction* FindGameKeyBindingAction(
            std::vector<GameKeyBindingAction>& actions,
            const std::string& action)
        {
            for (GameKeyBindingAction& entry : actions)
            {
                if (entry.action == action)
                    return &entry;
            }

            return nullptr;
        }

        static std::string JoinStrings(const std::vector<std::string>& parts, const char* separator)
        {
            if (parts.empty())
                return {};

            std::string combined;
            for (size_t index = 0; index < parts.size(); ++index)
            {
                if (index != 0 && separator)
                    combined += separator;
                combined += parts[index];
            }
            return combined;
        }

        static bool AppendUniqueString(std::vector<std::string>& values, const std::string& value)
        {
            if (value.empty())
                return false;

            if (std::find(values.begin(), values.end(), value) != values.end())
                return false;

            values.push_back(value);
            return true;
        }

        static std::filesystem::path ResolveInputBindingInstallDirectory()
        {
            const auto moduleDir = GetMainModuleDirectory();
            const auto hasInputMap = [](const std::filesystem::path& dir) -> bool
            {
                if (dir.empty())
                    return false;

                std::error_code error;
                return std::filesystem::exists(dir / "input.map", error);
            };

            if (hasInputMap(moduleDir))
                return moduleDir;

            char userProfile[MAX_PATH] = {};
            const DWORD userProfileLen =
                GetEnvironmentVariableA("USERPROFILE", userProfile, MAX_PATH);
            if (userProfileLen > 0 && userProfileLen < MAX_PATH)
            {
                const std::filesystem::path documentsInstall =
                    std::filesystem::path(userProfile) / "Documents" / "Battlezone 98 Redux";
                if (hasInputMap(documentsInstall))
                    return documentsInstall;
            }

            const std::filesystem::path gogInstall("C:\\GOG Games\\Battlezone 98 Redux");
            if (hasInputMap(gogInstall))
                return gogInstall;

            return moduleDir;
        }

        static bool ParseInputBindingMapFile(
            const std::filesystem::path& inputMapPath,
            std::vector<InputBindingCommandBlock>& outBlocks,
            InputBindingInventoryStats& outInventory)
        {
            outBlocks.clear();
            outInventory = {};

            std::ifstream file(inputMapPath);
            if (!file)
                return false;

            std::string line;
            std::string pendingComment;
            bool inBlock = false;
            InputBindingCommandBlock currentBlock = {};

            auto finalizeBlock = [&]()
            {
                if (currentBlock.command.empty())
                    return;

                ++outInventory.uniqueCommandBlocks;
                if (currentBlock.hasPositiveNonKeyboard)
                    ++outInventory.mixedBlocks;
                else if (currentBlock.positiveKeyboardTokens.size() > 1)
                    ++outInventory.keyboardChordBlocks;
                else if (!currentBlock.positiveKeyboardTokens.empty())
                    ++outInventory.simpleKeyboardBlocks;

                outBlocks.push_back(currentBlock);
                currentBlock = {};
            };

            while (std::getline(file, line))
            {
                const std::string trimmed = TrimAsciiCopy(line);
                if (!inBlock)
                {
                    if (trimmed.empty())
                        continue;

                    if (trimmed[0] == '#')
                    {
                        const std::string comment = TrimAsciiCopy(trimmed.substr(1));
                        if (!comment.empty())
                            pendingComment = comment;
                        continue;
                    }

                    const size_t bracePos = trimmed.find('{');
                    if (bracePos == std::string::npos)
                    {
                        pendingComment.clear();
                        continue;
                    }

                    const std::string command = TrimAsciiCopy(trimmed.substr(0, bracePos));
                    if (command.empty())
                    {
                        pendingComment.clear();
                        continue;
                    }

                    currentBlock = {};
                    currentBlock.command = command;
                    currentBlock.comment = pendingComment;
                    pendingComment.clear();
                    inBlock = true;
                    continue;
                }

                if (trimmed.empty() || trimmed[0] == '#')
                    continue;

                if (trimmed[0] == '}')
                {
                    finalizeBlock();
                    inBlock = false;
                    continue;
                }

                if (trimmed[0] != '+' && trimmed[0] != '-')
                    continue;

                size_t cursor = 1;
                while (cursor < trimmed.size() &&
                       std::isspace(static_cast<unsigned char>(trimmed[cursor])))
                {
                    ++cursor;
                }

                const size_t sourceStart = cursor;
                while (cursor < trimmed.size() &&
                       !std::isspace(static_cast<unsigned char>(trimmed[cursor])))
                {
                    ++cursor;
                }

                const std::string source = trimmed.substr(sourceStart, cursor - sourceStart);
                const std::string token = TrimAsciiCopy(trimmed.substr(cursor));
                if (source.empty() || token.empty())
                    continue;

                if (trimmed[0] == '+')
                {
                    if (_stricmp(source.c_str(), "keyboard") == 0)
                        currentBlock.positiveKeyboardTokens.push_back(token);
                    else
                        currentBlock.hasPositiveNonKeyboard = true;
                }
            }

            if (inBlock)
                finalizeBlock();

            return true;
        }

        static bool ParseGameKeyBindingMapFile(
            const std::filesystem::path& gameKeyMapPath,
            std::vector<GameKeyBindingAction>& outActions,
            InputBindingInventoryStats& outInventory)
        {
            outActions.clear();
            outInventory.uniqueGameKeyActions = 0;
            outInventory.gameKeyChords = 0;

            std::ifstream file(gameKeyMapPath);
            if (!file)
                return false;

            std::string line;
            while (std::getline(file, line))
            {
                const std::string trimmed = TrimAsciiCopy(line);
                if (trimmed.empty() || trimmed[0] == '#')
                    continue;

                size_t cursor = 0;
                while (cursor < trimmed.size() &&
                       !std::isspace(static_cast<unsigned char>(trimmed[cursor])))
                {
                    ++cursor;
                }

                const std::string action = trimmed.substr(0, cursor);
                const std::string chord = TrimAsciiCopy(trimmed.substr(cursor));
                if (action.empty() || chord.empty())
                    continue;

                GameKeyBindingAction* existing = FindGameKeyBindingAction(outActions, action);
                if (!existing)
                {
                    GameKeyBindingAction created = {};
                    created.action = action;
                    outActions.push_back(std::move(created));
                    existing = &outActions.back();
                }

                if (AppendUniqueString(existing->chords, chord))
                    ++outInventory.gameKeyChords;
            }

            outInventory.uniqueGameKeyActions = outActions.size();
            return true;
        }

        static std::string FormatInputBindingBlockValue(const InputBindingCommandBlock& block)
        {
            if (block.positiveKeyboardTokens.empty() || block.hasPositiveNonKeyboard)
                return {};

            return JoinStrings(block.positiveKeyboardTokens, " + ");
        }

        static std::vector<InputBindingUiRow> BuildFirstPassInputBindingRows(
            const std::vector<InputBindingCommandBlock>& blocks)
        {
            std::vector<InputBindingUiRow> rows;
            rows.reserve(std::size(kInputBindingFirstPassSeeds));

            for (const InputBindingRowSeed& seed : kInputBindingFirstPassSeeds)
            {
                InputBindingUiRow row = {};
                row.family = InputBindingMapFamily::Input;
                row.command = seed.command ? seed.command : "";
                row.displayLabelKey = seed.labelKey ? seed.labelKey : "";
                row.displayText = seed.displayText ? seed.displayText : "";

                std::vector<std::string> bindingValues;
                std::string firstComment;

                for (const InputBindingCommandBlock& block : blocks)
                {
                    if (block.command != row.command)
                        continue;

                    row.foundInMap = true;
                    ++row.matchingBlockCount;

                    if (firstComment.empty() && !block.comment.empty())
                        firstComment = block.comment;

                    AppendUniqueString(bindingValues, FormatInputBindingBlockValue(block));
                }

                if (row.displayText.empty())
                {
                    if (!firstComment.empty())
                        row.displayText = firstComment;
                    else
                        row.displayText = HumanizeInputBindingCommand(row.command);
                }

                row.currentBindingText = JoinStrings(bindingValues, ", ");
                row.reserved = !row.foundInMap || row.currentBindingText.empty();
                rows.push_back(row);
            }

            return rows;
        }

        static std::vector<InputBindingUiRow> BuildFirstPassGameKeyBindingRows(
            const std::vector<GameKeyBindingAction>& actions)
        {
            std::vector<InputBindingUiRow> rows;
            rows.reserve(actions.size());

            for (const GameKeyBindingAction& action : actions)
            {
                InputBindingUiRow row = {};
                row.family = InputBindingMapFamily::GameKey;
                row.command = action.action;
                row.displayText = HumanizeInputBindingCommand(action.action);
                row.currentBindingText = JoinStrings(action.chords, ", ");
                row.foundInMap = true;
                row.reserved = row.currentBindingText.empty();
                row.matchingBlockCount = action.chords.size();
                rows.push_back(std::move(row));
            }

            return rows;
        }

        static void LogInputBindingUiScaffoldSummary()
        {
            if (g_InputBindingUiScaffoldLogged)
                return;
            g_InputBindingUiScaffoldLogged = true;

            const std::string installPath = g_InputBindingInstallDirectory.string();
            const std::string inputMapPath =
                (g_InputBindingInstallDirectory / "input.map").string();
            const std::string gameKeyMapPath =
                (g_InputBindingInstallDirectory / "gamekey.map").string();

            Log(L"[INPUTUI] Scaffold install=%hs input.map=%hs gamekey.map=%hs inputBlocks=%u simple=%u chord=%u mixed=%u gameActions=%u gameChords=%u firstPassInputRows=%u firstPassGameKeyRows=%u totalRows=%u\n",
                installPath.c_str(),
                inputMapPath.c_str(),
                gameKeyMapPath.c_str(),
                static_cast<unsigned>(g_InputBindingInventory.uniqueCommandBlocks),
                static_cast<unsigned>(g_InputBindingInventory.simpleKeyboardBlocks),
                static_cast<unsigned>(g_InputBindingInventory.keyboardChordBlocks),
                static_cast<unsigned>(g_InputBindingInventory.mixedBlocks),
                static_cast<unsigned>(g_InputBindingInventory.uniqueGameKeyActions),
                static_cast<unsigned>(g_InputBindingInventory.gameKeyChords),
                static_cast<unsigned>(g_InputBindingInventory.firstPassInputRows),
                static_cast<unsigned>(g_InputBindingInventory.firstPassGameKeyRows),
                static_cast<unsigned>(g_InputBindingUiRows.size()));

            const size_t previewCount = std::min<size_t>(g_InputBindingUiRows.size(), 10);
            for (size_t index = 0; index < previewCount; ++index)
            {
                const InputBindingUiRow& row = g_InputBindingUiRows[index];
                const char* familyText =
                    row.family == InputBindingMapFamily::GameKey ? "gamekey" : "input";
                Log(L"[INPUTUI]   row[%u] family=%hs cmd=%hs title=%hs value=%hs reserved=%hs blocks=%u\n",
                    static_cast<unsigned>(index),
                    familyText,
                    row.command.c_str(),
                    row.displayText.c_str(),
                    row.currentBindingText.empty() ? "<none>" : row.currentBindingText.c_str(),
                    row.reserved ? "yes" : "no",
                    static_cast<unsigned>(row.matchingBlockCount));
            }

            Log(L"[INPUTUI] Recovered stock constructor entry=0x%08X screenFactoryCall=0x%08X\n",
                static_cast<uint32_t>(kOptionsInputCtorAddr),
                static_cast<uint32_t>(kOptionsInputScreenFactoryCallerAddr));
        }

        static bool ShouldEnableInputBindingUiReplacement()
        {
            return EnvFlagEnabled("OPENSHIM_ENABLE_INPUT_BINDING_UI_CONSTRUCTOR_HOOK") ||
                   EnvFlagEnabled("OPENSHIM_ENABLE_INPUT_BINDING_UI_POPULATE_HOOK") ||
                   EnvFlagEnabled("OPENSHIM_ENABLE_INPUT_BINDING_UI_SCAFFOLD");
        }

        static bool CreateInputBindingPreviewLabel(void* parent,
                                                   const char* text,
                                                   float x,
                                                   float y,
                                                   float w,
                                                   float h)
        {
            if (!parent || !text || !*text || !g_BzrFn_LabelCtor || !g_BzrFn_AddChild)
                return false;

            void* labelMem = ::operator new(0x930, std::nothrow);
            if (!labelMem)
                return false;

            std::memset(labelMem, 0, 0x930);
            void* label = g_BzrFn_LabelCtor(labelMem, text, x, y, w, h, 0x20, parent, 0);
            if (!label)
                return false;

            if (g_BzrFn_LabelState)
                g_BzrFn_LabelState(label, nullptr);
            g_BzrFn_AddChild(parent, label, 0);
            return true;
        }

        static std::string FormatInputBindingPreviewLine(const InputBindingUiRow& row)
        {
            std::string line = row.displayText.empty() ? HumanizeInputBindingCommand(row.command) : row.displayText;
            line += ": ";
            line += row.currentBindingText.empty() ? "<none>" : row.currentBindingText;
            if (row.reserved)
                line += " [reserved]";
            return line;
        }

        static void RenderInputBindingUiPreview(void* screen)
        {
            InitializeInputBindingUiScaffold();

            if (!screen)
                return;

            static constexpr float kHeaderX = 170.0f;
            static constexpr float kHeaderY = 185.0f;
            static constexpr float kHeaderW = 980.0f;
            static constexpr float kHeaderH = 30.0f;
            static constexpr float kRowX = 170.0f;
            static constexpr float kRowY = 222.0f;
            static constexpr float kRowW = 980.0f;
            static constexpr float kRowH = 24.0f;
            static constexpr float kRowStep = 25.0f;
            static constexpr size_t kMaxPreviewRows = 12;

            CreateInputBindingPreviewLabel(
                screen,
                "OpenShim Input UI Preview",
                kHeaderX,
                kHeaderY,
                kHeaderW,
                kHeaderH);

            size_t rendered = 0;
            for (const InputBindingUiRow& row : g_InputBindingUiRows)
            {
                if (row.family != InputBindingMapFamily::Input)
                    continue;
                if (rendered >= kMaxPreviewRows)
                    break;

                const std::string line = FormatInputBindingPreviewLine(row);
                if (CreateInputBindingPreviewLabel(
                        screen,
                        line.c_str(),
                        kRowX,
                        kRowY + (static_cast<float>(rendered) * kRowStep),
                        kRowW,
                        kRowH))
                {
                    ++rendered;
                }
            }

            const std::string footer =
                "OpenShim preview overlays the stock screen; capture/edit flow not wired yet.";
            CreateInputBindingPreviewLabel(
                screen,
                footer.c_str(),
                kRowX,
                kRowY + (static_cast<float>(kMaxPreviewRows) * kRowStep) + 8.0f,
                kRowW,
                kRowH);
        }

        static void InitializeInputBindingUiScaffold()
        {
            if (g_InputBindingUiScaffoldInitialized)
                return;
            g_InputBindingUiScaffoldInitialized = true;

            g_InputBindingInstallDirectory = ResolveInputBindingInstallDirectory();
            g_InputBindingInventory = {};
            g_InputBindingCommandBlocks.clear();
            g_GameKeyBindingActions.clear();
            g_InputBindingUiRows.clear();
            g_LastOptionsInputScreen = nullptr;

            const std::filesystem::path inputMapPath = g_InputBindingInstallDirectory / "input.map";
            if (!ParseInputBindingMapFile(inputMapPath, g_InputBindingCommandBlocks, g_InputBindingInventory))
            {
                const std::string inputMapPathText = inputMapPath.string();
                Log(L"[INPUTUI] Failed to parse input binding map at %hs\n",
                    inputMapPathText.c_str());
                return;
            }

            const std::filesystem::path gameKeyMapPath = g_InputBindingInstallDirectory / "gamekey.map";
            if (!ParseGameKeyBindingMapFile(gameKeyMapPath, g_GameKeyBindingActions, g_InputBindingInventory))
            {
                const std::string gameKeyMapPathText = gameKeyMapPath.string();
                Log(L"[INPUTUI] Failed to parse gamekey binding map at %hs\n",
                    gameKeyMapPathText.c_str());
            }

            std::vector<InputBindingUiRow> inputRows =
                BuildFirstPassInputBindingRows(g_InputBindingCommandBlocks);
            std::vector<InputBindingUiRow> gameKeyRows =
                BuildFirstPassGameKeyBindingRows(g_GameKeyBindingActions);
            g_InputBindingInventory.firstPassInputRows = inputRows.size();
            g_InputBindingInventory.firstPassGameKeyRows = gameKeyRows.size();

            g_InputBindingUiRows = inputRows;
            g_InputBindingUiRows.insert(
                g_InputBindingUiRows.end(),
                gameKeyRows.begin(),
                gameKeyRows.end());
            LogInputBindingUiScaffoldSummary();
        }

        static void EnsureInputBindingPopulateHookScaffold()
        {
            InitializeInputBindingUiScaffold();

            if (g_InputBindingUiPopulateHookInstallAttempted)
                return;
            g_InputBindingUiPopulateHookInstallAttempted = true;

            if (!ShouldEnableInputBindingUiReplacement())
                return;

            static const uint8_t kExpectedOptionsInputCtorBytes[kOptionsInputCtorDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0x73, 0x12, 0x86, 0x00
            };

            if (!ExpectedBytesMatchAt(kOptionsInputCtorAddr,
                                      kExpectedOptionsInputCtorBytes,
                                      sizeof(kExpectedOptionsInputCtorBytes)))
            {
                if (!g_InputBindingUiPopulateHookMismatchLogged)
                {
                    Log(L"[INPUTUI] Constructor entry bytes mismatch at 0x%08X; input UI replacement remains disabled\n",
                        static_cast<uint32_t>(kOptionsInputCtorAddr));
                    g_InputBindingUiPopulateHookMismatchLogged = true;
                }
                return;
            }

            if (!InstallInlineDetour32(g_OptionsInputPopulateUiDetour,
                                       kOptionsInputCtorAddr,
                                       reinterpret_cast<void*>(OptionsInputPopulateUiHook),
                                       kOptionsInputCtorDetourLen,
                                       kExpectedOptionsInputCtorBytes,
                                       sizeof(kExpectedOptionsInputCtorBytes)))
            {
                Log(L"[INPUTUI] Failed installing constructor hook at 0x%08X\n",
                    static_cast<uint32_t>(kOptionsInputCtorAddr));
                return;
            }

            g_BzrFn_OptionsInputCtor =
                reinterpret_cast<FnOptionsInputCtor>(g_OptionsInputPopulateUiDetour.trampoline);
            g_InputBindingUiPopulateHookInstalled = (g_BzrFn_OptionsInputCtor != nullptr);
            g_InputBindingUiPopulateHookMismatchLogged = false;
            Log(L"[INPUTUI] Installed constructor hook entry=0x%08X trampoline=0x%08X preview=%hs\n",
                static_cast<uint32_t>(kOptionsInputCtorAddr),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_OptionsInputPopulateUiDetour.trampoline)),
                "enabled");
        }

        static void OnOptionsInputPopulateUiScaffold(void* screen)
        {
            InitializeInputBindingUiScaffold();

            if (!screen || g_LastOptionsInputScreen == screen)
                return;

            g_LastOptionsInputScreen = screen;
            Log(L"[INPUTUI] Constructor hook screen=0x%08X rows=%u stockFallback=%hs preview=%hs\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(screen)),
                static_cast<unsigned>(g_InputBindingUiRows.size()),
                "yes",
                "yes");

            RenderInputBindingUiPreview(screen);
        }

        static bool IsIniBoolTrue(const char* value, bool fallback)
        {
            if (!value || !*value)
                return fallback;

            char normalized[16] = {};
            size_t out = 0;
            for (const char* cursor = value; *cursor && out + 1 < sizeof(normalized); ++cursor)
            {
                if (std::isspace(static_cast<unsigned char>(*cursor)))
                    continue;
                normalized[out++] = static_cast<char>(std::tolower(static_cast<unsigned char>(*cursor)));
            }
            normalized[out] = '\0';

            if (normalized[0] == '\0')
                return fallback;

            if (strcmp(normalized, "1") == 0 ||
                strcmp(normalized, "true") == 0 ||
                strcmp(normalized, "yes") == 0 ||
                strcmp(normalized, "on") == 0)
            {
                return true;
            }

            if (strcmp(normalized, "0") == 0 ||
                strcmp(normalized, "false") == 0 ||
                strcmp(normalized, "no") == 0 ||
                strcmp(normalized, "off") == 0)
            {
                return false;
            }

            return fallback;
        }

        static int64_t PackProducerBuildMenuToken(const char* token)
        {
            if (!token)
                return 0;

            uint8_t bytes[kProducerBuildMenuTokenLen] = {};
            for (size_t i = 0; i < kProducerBuildMenuTokenLen && token[i]; ++i)
                bytes[i] = static_cast<uint8_t>(token[i]);

            int64_t packed = 0;
            memcpy(&packed, bytes, sizeof(bytes));
            return packed;
        }

        static ProducerBuildMenuEntry NormalizeProducerBuildMenuToken(const char* value)
        {
            ProducerBuildMenuEntry entry = {};
            if (!value)
                return entry;

            const char* start = value;
            while (*start && std::isspace(static_cast<unsigned char>(*start)))
                ++start;

            const char* end = start + strlen(start);
            while (end > start && std::isspace(static_cast<unsigned char>(end[-1])))
                --end;

            size_t length = static_cast<size_t>(end - start);
            if (length == 0)
                return entry;

            char normalized[64] = {};
            size_t out = 0;
            for (size_t i = 0; i < length && out + 1 < sizeof(normalized); ++i)
            {
                normalized[out++] = static_cast<char>(
                    std::tolower(static_cast<unsigned char>(start[i])));
            }
            normalized[out] = '\0';

            if (out > 7 && strcmp(normalized + out - 7, "_mp.odf") == 0)
            {
                out -= 7;
                normalized[out] = '\0';
            }
            else if (out > 4 && strcmp(normalized + out - 4, ".odf") == 0)
            {
                out -= 4;
                normalized[out] = '\0';
            }

            if (out == 0)
                return entry;

            if (out > kProducerBuildMenuTokenLen)
                out = kProducerBuildMenuTokenLen;

            memcpy(entry.token, normalized, out);
            entry.token[out] = '\0';
            entry.hasValue = entry.token[0] != '\0';
            entry.packedToken = entry.hasValue ? PackProducerBuildMenuToken(entry.token) : 0;
            return entry;
        }

        static ProducerBuildMenuKind ClassifyProducerBuildMenuKind(void* producerPtr)
        {
            if (!producerPtr)
                return ProducerBuildMenuKind::Unknown;

            const uint32_t vft = *reinterpret_cast<const uint32_t*>(producerPtr);
            switch (vft)
            {
            case kRecyclerDistributedVft:
            case kRecyclerAttachableVft:
            case kRecyclerFriendVft:
            case kRecyclerEnemyVft:
                return ProducerBuildMenuKind::Recycler;
            case kFactoryDistributedVft:
            case kFactoryAttachableVft:
                return ProducerBuildMenuKind::Factory;
            case kArmoryDistributedVft:
            case kArmoryAttachableVft:
                return ProducerBuildMenuKind::Armory;
            case kConstructionRigDistributedVft:
            case kConstructionRigAttachableVft:
                return ProducerBuildMenuKind::ConstructionRig;
            default:
                if (vft != g_LastUnknownProducerVft)
                {
                    g_LastUnknownProducerVft = vft;
                    Log(L"[PRODMENU] Unknown producer vft=0x%08X\n", vft);
                }
                return ProducerBuildMenuKind::Unknown;
            }
        }

        static const char* ProducerBuildMenuKindName(ProducerBuildMenuKind kind)
        {
            switch (kind)
            {
            case ProducerBuildMenuKind::Recycler: return "Recycler";
            case ProducerBuildMenuKind::Factory: return "Factory";
            case ProducerBuildMenuKind::Armory: return "Armory";
            case ProducerBuildMenuKind::ConstructionRig: return "ConstructionRig";
            default: return "Producer";
            }
        }

        static ProducerBuildMenuEntry ReadProducerBuildMenuEntry(const char* key)
        {
            ProducerBuildMenuEntry entry = {};
            const auto moduleDir = GetMainModuleDirectory();
            if (moduleDir.empty())
                return entry;

            const auto configPath = moduleDir / kProducerBuildMenuIniName;
            char buffer[64] = {};
            GetPrivateProfileStringA(
                kProducerBuildMenuSection,
                key,
                "",
                buffer,
                static_cast<DWORD>(sizeof(buffer)),
                configPath.string().c_str());
            return NormalizeProducerBuildMenuToken(buffer);
        }

        static bool IsProducerBuildMenuReservedKey(const char* key)
        {
            if (!key || !*key)
                return true;

            return _stricmp(key, "Enabled") == 0 ||
                _stricmp(key, "Recycler") == 0 ||
                _stricmp(key, "Factory") == 0 ||
                _stricmp(key, "Armory") == 0 ||
                _stricmp(key, "ConstructionRig") == 0 ||
                _stricmp(key, "Constructor") == 0 ||
                _stricmp(key, "Default") == 0 ||
                _stricmp(key, "Fallback") == 0;
        }

        static void LoadProducerBuildMenuOdfOverrides(const std::filesystem::path& configPath)
        {
            g_ProducerBuildMenuConfig.odfOverrides.clear();

            FILE* file = nullptr;
            if (fopen_s(&file, configPath.string().c_str(), "r") != 0 || !file)
                return;

            char line[256] = {};
            bool inTargetSection = false;
            while (std::fgets(line, static_cast<int>(sizeof(line)), file))
            {
                char* trimmed = TrimAsciiInPlace(line);
                if (*trimmed == '\0' || *trimmed == ';' || *trimmed == '#')
                    continue;

                if (*trimmed == '[')
                {
                    char* closing = std::strchr(trimmed, ']');
                    if (!closing)
                        continue;

                    *closing = '\0';
                    inTargetSection = (_stricmp(trimmed + 1, kProducerBuildMenuSection) == 0);
                    continue;
                }

                if (!inTargetSection)
                    continue;

                char* equals = std::strchr(trimmed, '=');
                if (!equals)
                    continue;

                *equals = '\0';
                char* key = TrimAsciiInPlace(trimmed);
                char* value = TrimAsciiInPlace(equals + 1);
                if (!key || !*key || !value || !*value)
                    continue;
                if (IsProducerBuildMenuReservedKey(key))
                    continue;

                const ProducerBuildMenuEntry keyEntry = NormalizeProducerBuildMenuToken(key);
                const ProducerBuildMenuEntry valueEntry = NormalizeProducerBuildMenuToken(value);
                if (!keyEntry.hasValue || !valueEntry.hasValue)
                    continue;

                g_ProducerBuildMenuConfig.odfOverrides[keyEntry.token] = valueEntry;
            }

            std::fclose(file);
        }

        static ProducerBuildMenuEntry TryGetProducerBuildMenuEntryForOdf(const char* producerOdf)
        {
            ProducerBuildMenuEntry entry = {};
            const ProducerBuildMenuEntry key = NormalizeProducerBuildMenuToken(producerOdf);
            if (!key.hasValue)
                return entry;

            const auto it = g_ProducerBuildMenuConfig.odfOverrides.find(key.token);
            if (it != g_ProducerBuildMenuConfig.odfOverrides.end())
                return it->second;

            return entry;
        }

        static std::vector<std::filesystem::path> GetProducerOdfDirectoryCandidates()
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

        static bool TryParseFloatValue(const char* value, float& out)
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

        static bool TryParseBoolValue(const char* value, bool& out)
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

        static bool TryGetObjectOdfToken(void* objectPtr, char (&outToken)[kProducerBuildMenuTokenLen + 1])
        {
            outToken[0] = '\0';
            if (!objectPtr)
                return false;

            __try
            {
                void* objectClass = ReadValueAtOffset<void*>(objectPtr, kGameObjectClassOffset);
                if (!objectClass)
                    return false;

                char rawOdf[kObjectClassOdfLen + 1] = {};
                std::memcpy(rawOdf,
                            reinterpret_cast<const uint8_t*>(objectClass) + kObjectClassOdfOffset,
                            kObjectClassOdfLen);
                rawOdf[kObjectClassOdfLen] = '\0';

                const ProducerBuildMenuEntry entry = NormalizeProducerBuildMenuToken(rawOdf);
                if (!entry.hasValue)
                    return false;

                strncpy_s(outToken, entry.token, _TRUNCATE);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outToken[0] = '\0';
                return false;
            }
        }

        static bool TryNormalizeQuotedStringValue(const char* value,
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

        static ProducerBuildMenuEntry NormalizeQuotedOdfToken(const char* value)
        {
            char normalized[64] = {};
            if (!TryNormalizeQuotedStringValue(value, normalized, sizeof(normalized)))
                return {};

            return NormalizeProducerBuildMenuToken(normalized);
        }

        static bool TryResolveOdfFilePath(const char* odfToken, std::filesystem::path& outPath)
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
                Log(L"[AIODF] Loaded tuning odf=%hs engage=%hs%.2f weaponMin=%hs%.2f bomberDerived=%hs scrapPathing=%hs pathWeight=%hs%.3f straightWeight=%hs%.3f file=%hs\n",
                    odfKey.token,
                    outConfig.hasEngageRangeAI ? "" : "-",
                    outConfig.engageRangeAI,
                    outConfig.hasWeaponRangeMinAI ? "" : "-",
                    outConfig.weaponRangeMinAI,
                    outConfig.derivedBomberWeaponRangeAI ? "true" : "false",
                    outConfig.scrapPathingAI ? "true" : "false",
                    outConfig.hasScrapPathLengthWeightAI ? "" : "-",
                    outConfig.scrapPathLengthWeightAI,
                    outConfig.hasScrapStraightDistanceWeightAI ? "" : "-",
                    outConfig.scrapStraightDistanceWeightAI,
                    resolvedPath.string().c_str());
            }

            return foundAny;
        }

        static bool TryGetAiTuningForObject(void* objectPtr, AiTuningConfig& outConfig)
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

        static bool TryParseShieldTowerTeamFilterValue(const char* value,
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

        static bool TryReadShieldTowerTeamFilterFromOdfFile(const char* odfToken,
                                                            ShieldTowerTeamFilterConfig& outConfig)
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
                    TryParseShieldTowerTeamFilterValue(value, parsedAllies, parsedEnemies))
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
            Log(L"[SHIELDODF] Loaded team filter odf=%hs allies=%hs enemies=%hs file=%hs\n",
                odfKey.token,
                affectAllies ? "true" : "false",
                affectEnemies ? "true" : "false",
                resolvedPath.string().c_str());
            return true;
        }

        static bool TryGetShieldTowerTeamFilterForObject(void* objectPtr, ShieldTowerTeamFilterConfig& outConfig)
        {
            outConfig = {};

            char odfToken[kProducerBuildMenuTokenLen + 1] = {};
            if (!TryGetObjectOdfToken(objectPtr, odfToken))
                return false;

            const auto cached = g_ShieldTowerTeamFilterCache.odfEntries.find(odfToken);
            if (cached != g_ShieldTowerTeamFilterCache.odfEntries.end())
            {
                outConfig = cached->second;
                return outConfig.parsed;
            }

            ShieldTowerTeamFilterConfig loaded = {};
            TryReadShieldTowerTeamFilterFromOdfFile(odfToken, loaded);
            g_ShieldTowerTeamFilterCache.odfEntries[odfToken] = loaded;
            outConfig = loaded;
            return outConfig.parsed;
        }

        static bool ShieldTowerNeedsCustomFilterPath(const ShieldTowerTeamFilterConfig& config)
        {
            return config.parsed && !(config.affectAllies && config.affectEnemies);
        }

        static bool TryGetGameObjectObj76(void* gameObject, void*& outObj76)
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

        static bool TryGetGameObjectFromObj76(void* obj76, void*& outGameObject)
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

        static bool TryGetObjectWorldPositionFromObj76(void* obj76, float (&outPosition)[3])
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

        static bool TryGetGameObjectWorldPosition(void* gameObject, float (&outPosition)[3])
        {
            void* obj76 = nullptr;
            return TryGetGameObjectObj76(gameObject, obj76) &&
                   TryGetObjectWorldPositionFromObj76(obj76, outPosition);
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

        static bool ShieldTowerShouldAffectObject(void* shieldTowerPtr,
                                                  void* targetObject,
                                                  const ShieldTowerTeamFilterConfig& config)
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

        static bool ShieldTowerShouldAffectOrdnance(void* shieldTowerPtr,
                                                    void* ordnance,
                                                    const ShieldTowerTeamFilterConfig& config)
        {
            if (config.affectAllies && config.affectEnemies)
                return true;

            void* ownerObject = nullptr;
            if (!TryGetOrdnanceOwnerGameObject(ordnance, ownerObject))
                return false;

            return ShieldTowerShouldAffectObject(shieldTowerPtr, ownerObject, config);
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
                reinterpret_cast<void(__thiscall*)(void*, const float*)>(kGogGameObjectAddVelocityAddr)(targetObject, delta);
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

        static void RunShieldTowerFilteredSimulate(void* shieldTowerPtr, float dt)
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

            ShieldTowerTeamFilterConfig filter = {};
            const bool hasFilter = TryGetShieldTowerTeamFilterForObject(shieldTowerPtr, filter);
            if (!hasFilter || !ShieldTowerNeedsCustomFilterPath(filter))
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

                void* collisionRangeSearch = nullptr;
                __try
                {
                    collisionRangeSearch = *reinterpret_cast<void**>(kCollisionRangeSearchAddr);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    collisionRangeSearch = nullptr;
                }

                if (collisionRangeSearch)
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
                        if (!targetObject || !ShieldTowerShouldAffectObject(shieldTowerPtr, targetObject, filter))
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

                const auto* list = reinterpret_cast<const ListPtrValue*>(kOrdnanceListAddr);
                __try
                {
                    if (list && list->head)
                    {
                        for (ListNodePtrValue* node = list->head->next;
                             node && node != list->head;
                             node = node->next)
                        {
                            void* ordnance = node->value;
                            if (!ordnance || !ShieldTowerShouldAffectOrdnance(shieldTowerPtr, ordnance, filter))
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

        static ProducerBuildMenuEntry TryReadProducerBuildMenuEntryFromOdfFile(const char* producerOdf)
        {
            ProducerBuildMenuEntry result = {};
            const ProducerBuildMenuEntry producerKey = NormalizeProducerBuildMenuToken(producerOdf);
            if (!producerKey.hasValue)
                return result;

            const auto cached = g_ProducerBuildMenuConfig.odfFileEntries.find(producerKey.token);
            if (cached != g_ProducerBuildMenuConfig.odfFileEntries.end())
                return cached->second;

            const auto directories = GetProducerOdfDirectoryCandidates();
            std::filesystem::path resolvedPath;
            for (const auto& directory : directories)
            {
                std::error_code error;
                const auto mpPath = directory / (std::string(producerKey.token) + "_mp.odf");
                if (std::filesystem::exists(mpPath, error) && !error)
                {
                    resolvedPath = mpPath;
                    break;
                }

                error.clear();
                const auto normalPath = directory / (std::string(producerKey.token) + ".odf");
                if (std::filesystem::exists(normalPath, error) && !error)
                {
                    resolvedPath = normalPath;
                    break;
                }
            }

            if (!resolvedPath.empty())
            {
                FILE* file = nullptr;
                if (fopen_s(&file, resolvedPath.string().c_str(), "r") == 0 && file)
                {
                    char line[256] = {};
                    bool inProducerSection = false;
                    while (std::fgets(line, static_cast<int>(sizeof(line)), file))
                    {
                        char* trimmed = TrimAsciiInPlace(line);
                        if (*trimmed == '\0' || *trimmed == ';' || *trimmed == '#')
                            continue;

                        if (*trimmed == '[')
                        {
                            char* closing = std::strchr(trimmed, ']');
                            if (!closing)
                                continue;

                            *closing = '\0';
                            inProducerSection = (_stricmp(trimmed + 1, "ProducerClass") == 0);
                            continue;
                        }

                        if (!inProducerSection)
                            continue;

                        char* equals = std::strchr(trimmed, '=');
                        if (!equals)
                            continue;

                        *equals = '\0';
                        char* key = TrimAsciiInPlace(trimmed);
                        char* value = TrimAsciiInPlace(equals + 1);
                        if (!key || !*key || !value || !*value)
                            continue;

                        if (_stricmp(key, "buildMenuRoot") == 0 ||
                            _stricmp(key, "buildMenu") == 0)
                        {
                            result = NormalizeProducerBuildMenuToken(value);
                            break;
                        }
                    }

                    std::fclose(file);

                    if (result.hasValue)
                    {
                        Log(L"[PRODMENU] ODF root producer=%hs root=%hs path=%hs\n",
                            producerKey.token,
                            result.token,
                            resolvedPath.string().c_str());
                    }
                }
            }

            g_ProducerBuildMenuConfig.odfFileEntries[producerKey.token] = result;
            return result;
        }

        static bool TryGetProducerOdfToken(void* producerPtr, char (&outToken)[kProducerBuildMenuTokenLen + 1])
        {
            return TryGetObjectOdfToken(producerPtr, outToken);
        }

        static void LoadProducerBuildMenuConfig()
        {
            if (g_ProducerBuildMenuConfig.initialized)
                return;

            g_ProducerBuildMenuConfig.initialized = true;
            g_ProducerBuildMenuConfig.fallbackRoot =
                NormalizeProducerBuildMenuToken(kProducerBuildMenuDefaultRoot);

            if (g_IsSteamExe)
            {
                Log(L"[PRODMENU] Disabled on Steam until the producer hook site is revalidated there\n");
                return;
            }

            const auto moduleDir = GetMainModuleDirectory();
            if (moduleDir.empty())
            {
                Log(L"[PRODMENU] Game directory unavailable; feature disabled\n");
                return;
            }

            const auto configPath = moduleDir / kProducerBuildMenuIniName;
            const auto configPathString = configPath.string();
            DWORD attrs = GetFileAttributesA(configPathString.c_str());
            if (attrs == INVALID_FILE_ATTRIBUTES || (attrs & FILE_ATTRIBUTE_DIRECTORY) != 0)
            {
                Log(L"[PRODMENU] Config not found at %hs; feature disabled\n", configPathString.c_str());
                return;
            }

            char enabledBuffer[32] = {};
            GetPrivateProfileStringA(
                kProducerBuildMenuSection,
                "Enabled",
                "1",
                enabledBuffer,
                static_cast<DWORD>(sizeof(enabledBuffer)),
                configPathString.c_str());

            g_ProducerBuildMenuConfig.recycler = ReadProducerBuildMenuEntry("Recycler");
            g_ProducerBuildMenuConfig.factory = ReadProducerBuildMenuEntry("Factory");
            g_ProducerBuildMenuConfig.armory = ReadProducerBuildMenuEntry("Armory");
            g_ProducerBuildMenuConfig.constructionRig = ReadProducerBuildMenuEntry("ConstructionRig");
            ProducerBuildMenuEntry fallbackEntry = ReadProducerBuildMenuEntry("Fallback");
            if (!fallbackEntry.hasValue)
                fallbackEntry = ReadProducerBuildMenuEntry("Default");
            if (fallbackEntry.hasValue)
                g_ProducerBuildMenuConfig.fallbackRoot = fallbackEntry;
            if (!g_ProducerBuildMenuConfig.constructionRig.hasValue)
            {
                g_ProducerBuildMenuConfig.constructionRig = ReadProducerBuildMenuEntry("Constructor");
            }
            LoadProducerBuildMenuOdfOverrides(configPath);

            const bool hasAnyEntry =
                !g_ProducerBuildMenuConfig.odfOverrides.empty() ||
                g_ProducerBuildMenuConfig.recycler.hasValue ||
                g_ProducerBuildMenuConfig.factory.hasValue ||
                g_ProducerBuildMenuConfig.armory.hasValue ||
                g_ProducerBuildMenuConfig.constructionRig.hasValue;
            g_ProducerBuildMenuConfig.enabled = IsIniBoolTrue(enabledBuffer, true) && hasAnyEntry;

            Log(L"[PRODMENU] Config %hs loaded enabled=%hs fallback=%hs recycler=%hs factory=%hs armory=%hs constrig=%hs odfOverrides=%u\n",
                configPathString.c_str(),
                g_ProducerBuildMenuConfig.enabled ? "true" : "false",
                g_ProducerBuildMenuConfig.fallbackRoot.hasValue ? g_ProducerBuildMenuConfig.fallbackRoot.token : "-",
                g_ProducerBuildMenuConfig.recycler.hasValue ? g_ProducerBuildMenuConfig.recycler.token : "-",
                g_ProducerBuildMenuConfig.factory.hasValue ? g_ProducerBuildMenuConfig.factory.token : "-",
                g_ProducerBuildMenuConfig.armory.hasValue ? g_ProducerBuildMenuConfig.armory.token : "-",
                g_ProducerBuildMenuConfig.constructionRig.hasValue ? g_ProducerBuildMenuConfig.constructionRig.token : "-",
                static_cast<unsigned>(g_ProducerBuildMenuConfig.odfOverrides.size()));
        }

        static ProducerBuildMenuEntry SelectProducerBuildMenuEntry(void* producerPtr, ProducerBuildMenuKind kind)
        {
            char producerOdf[kProducerBuildMenuTokenLen + 1] = {};
            if (TryGetProducerOdfToken(producerPtr, producerOdf))
            {
                ProducerBuildMenuEntry odfFileEntry = TryReadProducerBuildMenuEntryFromOdfFile(producerOdf);
                if (odfFileEntry.hasValue)
                    return odfFileEntry;

                ProducerBuildMenuEntry odfEntry = TryGetProducerBuildMenuEntryForOdf(producerOdf);
                if (odfEntry.hasValue)
                    return odfEntry;
            }

            switch (kind)
            {
            case ProducerBuildMenuKind::Recycler:
                if (g_ProducerBuildMenuConfig.recycler.hasValue)
                    return g_ProducerBuildMenuConfig.recycler;
                break;
            case ProducerBuildMenuKind::Factory:
                if (g_ProducerBuildMenuConfig.factory.hasValue)
                    return g_ProducerBuildMenuConfig.factory;
                break;
            case ProducerBuildMenuKind::Armory:
                if (g_ProducerBuildMenuConfig.armory.hasValue)
                    return g_ProducerBuildMenuConfig.armory;
                break;
            case ProducerBuildMenuKind::ConstructionRig:
                if (g_ProducerBuildMenuConfig.constructionRig.hasValue)
                    return g_ProducerBuildMenuConfig.constructionRig;
                break;
            default:
                break;
            }

            return g_ProducerBuildMenuConfig.fallbackRoot;
        }

        static void MaybeApplyProducerBuildMenu(void* producerPtr)
        {
            if (!g_BzrFn_InitBuildItem || !g_BzrFn_CleanupBuildItem || !g_BzrBuildMenuRoot)
                return;

            LoadProducerBuildMenuConfig();
            if (!g_ProducerBuildMenuConfig.enabled)
                return;

            const ProducerBuildMenuKind kind = ClassifyProducerBuildMenuKind(producerPtr);
            const ProducerBuildMenuEntry entry = SelectProducerBuildMenuEntry(producerPtr, kind);
            if (!entry.hasValue)
                return;

            if (g_HasAppliedProducerBuildMenu && g_LastAppliedProducerBuildMenu == entry.packedToken)
                return;

            __try
            {
                char producerOdf[kProducerBuildMenuTokenLen + 1] = {};
                TryGetProducerOdfToken(producerPtr, producerOdf);
                g_BzrFn_CleanupBuildItem(*g_BzrBuildMenuRoot);
                g_BzrFn_InitBuildItem(*g_BzrBuildMenuRoot, entry.packedToken);
                g_HasAppliedProducerBuildMenu = true;
                g_LastAppliedProducerBuildMenu = entry.packedToken;
                Log(L"[PRODMENU] Applied %hs root=%hs producer=0x%08X odf=%hs\n",
                    ProducerBuildMenuKindName(kind),
                    entry.token,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(producerPtr)),
                    producerOdf[0] ? producerOdf : "-");
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                char producerOdf[kProducerBuildMenuTokenLen + 1] = {};
                TryGetProducerOdfToken(producerPtr, producerOdf);
                Log(L"[PRODMENU] Failed applying root=%hs producer=0x%08X\n",
                    entry.token,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(producerPtr)));
            }
        }

        static bool AutoSaveFileExists()
        {
            const auto moduleDir = GetMainModuleDirectory();
            if (moduleDir.empty())
                return false;

            std::error_code error;
            return std::filesystem::exists(moduleDir / "Save" / "auto.sav", error) ||
                std::filesystem::exists(moduleDir / "Save" / "auto2.sav", error);
        }

        static bool TryGetAutoSaveFilePathUtf8(char (&outPath)[MAX_PATH])
        {
            outPath[0] = '\0';

            const auto moduleDir = GetMainModuleDirectory();
            if (moduleDir.empty())
                return false;

            std::error_code error;
            const auto primaryPath = moduleDir / "Save" / "auto.sav";
            if (std::filesystem::exists(primaryPath, error))
            {
                const auto primaryString = primaryPath.string();
                return strncpy_s(outPath, primaryString.c_str(), _TRUNCATE) == 0;
            }

            error.clear();
            const auto secondaryPath = moduleDir / "Save" / "auto2.sav";
            if (std::filesystem::exists(secondaryPath, error))
            {
                const auto secondaryString = secondaryPath.string();
                return strncpy_s(outPath, secondaryString.c_str(), _TRUNCATE) == 0;
            }

            return false;
        }

        static std::string GetAutoSaveButtonLabel()
        {
            char autoSavePath[MAX_PATH] = {};
            if (!TryGetAutoSaveFilePathUtf8(autoSavePath))
                return "AutoSave";

            std::filesystem::path labelPath(autoSavePath);
            labelPath.replace_extension(".label.txt");

            std::ifstream input(labelPath, std::ios::binary);
            if (!input.is_open())
                return "AutoSave";

            std::string data((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
            if (!input.good() && !input.eof())
                return "AutoSave";

            data.erase(std::remove(data.begin(), data.end(), '\0'), data.end());
            data.erase(std::remove(data.begin(), data.end(), '\r'), data.end());
            data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());

            const auto trimPred = [](unsigned char ch)
            {
                return std::isspace(ch) != 0;
            };
            data.erase(data.begin(), std::find_if(data.begin(), data.end(), [&](char ch)
            {
                return !trimPred(static_cast<unsigned char>(ch));
            }));
            data.erase(std::find_if(data.rbegin(), data.rend(), [&](char ch)
            {
                return !trimPred(static_cast<unsigned char>(ch));
            }).base(), data.end());

            if (data.empty())
                return "AutoSave";

            constexpr size_t kMaxButtonLabelChars = 96;
            if (data.size() > kMaxButtonLabelChars)
                data.resize(kMaxButtonLabelChars);

            return data;
        }

        static void PrepareLoadScreenForSelection(void* screen)
        {
            if (!screen)
                return;

            auto* screenBytes = reinterpret_cast<uint8_t*>(screen);
            void* dialog = *reinterpret_cast<void**>(screenBytes + 0x138);
            if (!dialog || !g_BzrFn_UiDialogSetEnabled || !g_BzrFn_UiDialogAdvance ||
                !g_BzrFn_LoadScreenPrep || !g_BzrFn_BzrStringCtorFromCStr ||
                !g_BzrFn_BzrStringDtor || !g_BzrFn_LoadScreenClearSelection)
            {
                return;
            }

            *reinterpret_cast<uint8_t*>(kLoadScreenSelectionFlagAddr) = 1;
            g_BzrFn_UiDialogSetEnabled(dialog, 0);
            g_BzrFn_LoadScreenPrep();
            g_BzrFn_UiDialogAdvance(dialog, 0x17);

            BzrString emptyText = {};
            g_BzrFn_BzrStringCtorFromCStr(&emptyText, "");
            g_BzrFn_LoadScreenClearSelection(&emptyText);
            g_BzrFn_BzrStringDtor(&emptyText);
        }

        static bool QueueAutoSaveLoadPath(const char* autoSavePath)
        {
            if (!autoSavePath || !autoSavePath[0])
                return false;

            auto* queuedPath = reinterpret_cast<char*>(kQueuedLoadPathBufferAddr);
            auto* queuedName = reinterpret_cast<char*>(kQueuedLoadNameBufferAddr);
            if (!queuedPath || !queuedName)
                return false;

            queuedName[0] = '\0';
            return strncpy_s(queuedPath, MAX_PATH, autoSavePath, _TRUNCATE) == 0;
        }

        static bool RefreshQueuedPathFromMissionName()
        {
            auto* queuedPath = reinterpret_cast<char*>(kQueuedLoadPathBufferAddr);
            auto* queuedName = reinterpret_cast<const char*>(kQueuedLoadNameBufferAddr);
            if (!queuedPath || !queuedName || !queuedName[0])
                return false;

            return strncpy_s(queuedPath, MAX_PATH, queuedName, _TRUNCATE) == 0;
        }

        static void ForceFreshRestartMissionState(void* screenThis, const char* sourceTag)
        {
            if (!screenThis)
            {
                Log(L"[RESTART] %hs missing screen context\n", sourceTag ? sourceTag : "unknown");
                return;
            }

            auto* screenBytes = reinterpret_cast<uint8_t*>(screenThis);
            void* dialog = *reinterpret_cast<void**>(screenBytes + 0x138);
            if (!dialog || !g_BzrFn_UiDialogSetEnabled || !g_BzrFn_UiDialogAdvance ||
                !g_BzrFn_LoadScreenPrep || !g_BzrFn_BzrStringCtorFromCStr ||
                !g_BzrFn_BzrStringDtor || !g_BzrFn_LoadScreenClearSelection ||
                !g_BzrFn_SetShellState)
            {
                Log(L"[RESTART] %hs missing restart helpers dialog=0x%p setEnabled=0x%p advance=0x%p prep=0x%p strCtor=0x%p strDtor=0x%p clearSelection=0x%p setState=0x%p\n",
                    sourceTag ? sourceTag : "unknown",
                    dialog,
                    g_BzrFn_UiDialogSetEnabled,
                    g_BzrFn_UiDialogAdvance,
                    g_BzrFn_LoadScreenPrep,
                    g_BzrFn_BzrStringCtorFromCStr,
                    g_BzrFn_BzrStringDtor,
                    g_BzrFn_LoadScreenClearSelection,
                    g_BzrFn_SetShellState);
                return;
            }

            auto* missionSaveFlag = reinterpret_cast<uint8_t*>(kMissionSaveFlagAddr);
            auto* oldMissionMode = reinterpret_cast<uint32_t*>(kOldMissionModeAddr);
            auto* screenType = reinterpret_cast<uint32_t*>(kUiScreenTypeAddr);
            auto* queuedPath = reinterpret_cast<const char*>(kQueuedLoadPathBufferAddr);
            auto* queuedName = reinterpret_cast<const char*>(kQueuedLoadNameBufferAddr);

            const uint8_t previousMissionSave = *missionSaveFlag;
            const uint32_t previousMissionMode = *oldMissionMode;
            char previousQueuedPath[MAX_PATH] = {};
            strncpy_s(previousQueuedPath, queuedPath ? queuedPath : "", _TRUNCATE);

            *missionSaveFlag = 0;
            *oldMissionMode = 0;
            const bool refreshedQueuedPath = RefreshQueuedPathFromMissionName();
            PrepareLoadScreenForSelection(screenThis);
            g_BzrFn_SetShellState(kRestartMissionState);
            *screenType = 0;

            Log(L"[RESTART] %hs forcing restart mission reload state=%d missionSave=%u->%u oldMissionMode=%u->%u queuedName=%hs queuedPath=%hs refreshedQueuedPath=%hs previousQueuedPath=%hs\n",
                sourceTag ? sourceTag : "unknown",
                kRestartMissionState,
                previousMissionSave,
                *missionSaveFlag,
                previousMissionMode,
                *oldMissionMode,
                queuedName,
                queuedPath,
                refreshedQueuedPath ? "true" : "false",
                previousQueuedPath);
        }

        static void RememberVehicleAssetDebugException(const BzrString* assetName)
        {
            char assetNameBuffer[64] = {};
            if (!CopyVehicleAssetName(assetName, assetNameBuffer))
                return;

            VehicleAssetExceptionCacheEntry* entry = FindVehicleAssetExceptionEntry(assetNameBuffer);
            if (!entry)
                entry = GetVehicleAssetExceptionSlot();
            if (!entry)
                return;

            strncpy_s(entry->assetName, assetNameBuffer, _TRUNCATE);
            entry->suppressUntil = GetTickCount() + kVehicleAssetRetryDelayMs;
            entry->lastSkipLogTick = 0;
        }

        static bool ShouldSuppressVehicleAssetLoad(const BzrString* assetName, const char* stage)
        {
            char assetNameBuffer[64] = {};
            if (!CopyVehicleAssetName(assetName, assetNameBuffer))
                return false;

            VehicleAssetExceptionCacheEntry* entry = FindVehicleAssetExceptionEntry(assetNameBuffer);
            if (!entry)
                return false;

            const DWORD now = GetTickCount();
            if (!TickIsBefore(now, entry->suppressUntil))
                return false;

            if (entry->lastSkipLogTick == 0 || !TickIsBefore(now, entry->lastSkipLogTick + 500u))
            {
                Log(L"[VEHICLE] Suppressed retry during %hs for recent-miss asset '%hs'\n",
                    stage ? stage : "unknown",
                    assetNameBuffer);
                entry->lastSkipLogTick = now;
            }

            return true;
        }

        static void CallVehicleListLoadSafely(void* mgrThis, BzrString* assetName, const char* stage)
        {
            if (!g_BzrFn_VehicleListLoad || !mgrThis || !assetName)
                return;

            if (ShouldSuppressVehicleAssetLoad(assetName, stage))
                return;

            __try
            {
                g_BzrFn_VehicleListLoad(mgrThis, assetName);
            }
            __except (FilterVehicleAssetDebugException(GetExceptionCode(), stage, assetName))
            {
                RememberVehicleAssetDebugException(assetName);
            }
        }
    }

    // ---------------------------------------------------------------------
    // Helpers
    // ---------------------------------------------------------------------
    void* __fastcall OptionsInputPopulateUiHook(void* thisPtr, void* /*edx*/)
    {
        void* screen = thisPtr;

        if (g_BzrFn_OptionsInputCtor)
            screen = g_BzrFn_OptionsInputCtor(thisPtr);

        OnOptionsInputPopulateUiScaffold(screen);
        return screen;
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
        g_BzrFn_GetPlayerHandle = nullptr;
        g_BzrFn_GameObjectGetObjByHandle = nullptr;
        g_BzrFn_PersonSimulate = nullptr;
        g_BzrFn_ShieldTowerSimulateOriginal = nullptr;
        g_BzrFn_BuildingSimulate = nullptr;
        g_BzrFn_ShieldTowerPowerUpdate = nullptr;
        g_BzrFn_GameObjectFriendP = nullptr;
        g_BzrFn_GameObjectEnemyP = nullptr;
        g_BzrFn_MatrixInverse = nullptr;
        g_BzrFn_VectorTransform = nullptr;
        g_BzrFn_CollisionRangeSearch = nullptr;
        g_BzrFn_RangeResultsGetNext = nullptr;
        g_BzrFn_OptionsInputCtor = nullptr;
        g_BzrFn_RecordDeath = g_RecordDeathDetour.trampoline
            ? reinterpret_cast<FnRecordDeath>(g_RecordDeathDetour.trampoline)
            : nullptr;
        g_JumpSnipeProbeInstalled = false;
        g_EngineFlamePrimaryManager = nullptr;
        g_EngineFlameSecondaryManager = nullptr;
        g_EngineFlameVtableHooksInstalled = false;
        g_EngineFlameVariantsInitialized = false;
        g_EngineFlameVariantsInitAttempted = false;
        g_EngineFlamePrimaryRedTexture = 0;
        g_EngineFlamePrimaryGreenTexture = 0;
        g_LoggedEngineFlameTargetFailure = false;
        g_LoggedEngineFlameVtableHook = false;
        g_BzrFn_ProducerModeCallOriginal = nullptr;
        g_BzrFn_InitBuildItem = nullptr;
        g_BzrFn_CleanupBuildItem = nullptr;
        g_BzrBuildMenuRoot = nullptr;
        g_BzrFn_GetLocalPlayerNetId = nullptr;
        g_BzrFn_NetPlayerSetData = nullptr;
        g_InputBindingUiScaffoldInitialized = false;
        g_InputBindingUiScaffoldLogged = false;
        g_InputBindingUiPopulateHookInstallAttempted = false;
        g_InputBindingUiPopulateHookInstalled = false;
        g_InputBindingUiPopulateHookMismatchLogged = false;
        g_CareerStatsMpHookInstalled = (g_RecordDeathDetour.trampoline != nullptr);
        g_CareerStatsMpHookInstallAttempted = g_CareerStatsMpHookInstalled;
        g_CareerStatsMpHookMismatchLogged = false;
        g_CareerStatsMpHookFirstAttemptTick = 0;
        g_CareerStatsMpHookLastAttemptTick = 0;
        g_InputBindingInstallDirectory.clear();
        g_InputBindingInventory = {};
        g_InputBindingCommandBlocks.clear();
        g_GameKeyBindingActions.clear();
        g_InputBindingUiRows.clear();
        g_LastOptionsInputScreen = nullptr;
        g_JumpSnipeProbeLogState = {};
        g_ProducerBuildMenuConfig = {};
        g_AiTuningCache = {};
        g_ShieldTowerTeamFilterCache = {};
        g_HasAppliedProducerBuildMenu = false;
        g_LastAppliedProducerBuildMenu = 0;
        g_LastUnknownProducerVft = 0;
        g_CalcRangeCraftHookInstalled = false;
        g_BzrFn_CalcRangeCraft = nullptr;
        g_RetargetPeriodHooksInstalled = false;
        g_BzrFn_OffensiveProcessDoSubTask = nullptr;
        g_BzrFn_GunTowerProcessDoSubTask = nullptr;
        g_BzrFn_AIUnitRemove = nullptr;
        g_BzrFn_AIBuildConstructionEnd = nullptr;
        g_BzrFn_AIBuildReservedAreaRemove = nullptr;
        g_BzrFn_AISpentCreditRefund = nullptr;
        g_BzrFn_UnitsSOrderStop = nullptr;
        g_BzrFn_AIBuildUnassignedCCAdd = nullptr;
        g_ConstructorRemoteBuildFixInstalled = false;
        g_ShieldTowerSimulateHookInstalled = false;
        g_AttackRevealTraceBudget = kAttackRevealTraceBudgetDefault;
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
        g_BomberAiRangeEnabled = kBomberAiRangeEnabledDefault;
        g_HowitzerVolleyEnabled = kHowitzerVolleyEnabledDefault;
        g_WeaponMaskCarrierBiasEnabled = kWeaponMaskCarrierBiasEnabledDefault;
        g_AiOdfGameplayTuningEnabled = kAiOdfGameplayTuningEnabledDefault;
        g_TurretAimPitchEnabled = kTurretAimPitchEnabledDefault;
        g_AttackRevealEnabled = kAttackRevealEnabledDefault;
        g_ConstructorRemoteBuildFixEnabled = kConstructorRemoteBuildFixEnabledDefault;
        g_TurretAimPitchMultiplier = 0.5f;
        g_TurretAimPitchMultiplierEnhanced = 0.95f;
        g_RetargetPeriodNextForceMsByProcess.clear();

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
        g_BzrFn_SetTextureOff = reinterpret_cast<FnUiSetStr>(0x007D2870);
        g_BzrFn_SetTextureOver = reinterpret_cast<FnUiSetStr>(0x007C2F10);
        g_BzrFn_SetTextureOn = reinterpret_cast<FnUiSetStr>(0x007C2E80);
        g_BzrFn_SetButtonLabel = reinterpret_cast<FnUiSetStr>(0x007C2950);
        g_BzrFn_SetTooltip = reinterpret_cast<FnUiSetStr>(0x007CC660);
        g_BzrFn_LabelState = reinterpret_cast<FnUiSetInt>(0x007CC5C0);
        g_BzrFn_SetOnClick = reinterpret_cast<FnUiSetCb>(0x007C23E0);
        g_BzrFn_SetOnHover = reinterpret_cast<FnUiSetCb>(0x007C23C0);
        g_BzrFn_AddChild = reinterpret_cast<FnUiAddChild>(0x007D2110);
        g_BzrFn_UiDialogSetEnabled = reinterpret_cast<FnUiDialogAction>(0x007C9170);
        g_BzrFn_UiDialogAdvance = reinterpret_cast<FnUiDialogAction>(0x007C7930);

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
        g_BzrFn_GetLocalPlayerNetId = reinterpret_cast<FnGetLocalPlayerNetId>(0x00572D90);
        g_BzrFn_NetPlayerSetData = reinterpret_cast<FnNetPlayerSetData>(0x00575570);
        g_BzrFn_NetPlayerSetFlagBuffer = reinterpret_cast<FnNetPlayerSetFlagBuffer>(0x00575810);
        g_BzrFn_SetMyFlag = reinterpret_cast<FnSetMyFlag>(0x0056FA50);

        // Steam's wrapped executable still maps these helpers at the same live
        // runtime addresses as GOG on the current 2.2.301 build.
        g_BzrFn_EngineFlameAddFlame = reinterpret_cast<FnEngineFlameAddFlame>(0x004C8800);
        g_BzrFn_EngineFlameControl = reinterpret_cast<FnEngineFlameControl>(0x004C88A0);
        g_BzrFn_EngineFlameSubmit = reinterpret_cast<FnEngineFlameSubmit>(0x004C88C0);
        g_BzrFn_EngineFlameResolveTexture = reinterpret_cast<FnEngineFlameResolveTexture>(0x0068BED0);
        g_BzrFn_HudSpriteLookup = reinterpret_cast<FnHudSpriteLookup>(0x0068BED0);
        g_BzrFn_GetTeamNum = reinterpret_cast<FnGetTeamNum>(0x005C8800);
        g_BzrFn_ChunkEffectSimulate = reinterpret_cast<FnChunkEffectSimulate>(0x004917F0);
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
        InstallShieldTowerTeamFilterHookIfPossible();

        if (g_IsSteamExe)
        {
            ResolveEngineFlameRuntimeTargets();
        }

        g_EnableChunkRenderFallback =
            EnvFlagEnabled("BZR_CHUNK_FORCE_FIRST_GEO") ||
            EnvFlagEnabled("OPENSHIM_CHUNK_FORCE_FIRST_GEO");
        g_EnableChunkProxyDebug =
            EnvFlagEnabled("OPENSHIM_CHUNK_PROXY_DEBUG") ||
            EnvFlagEnabled("OPENSHIM_CHUNK_PLACEHOLDER_PROXY");
        long chunkLogBudget = 200;
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
        g_TraceChunkRender =
            g_EnableChunkRenderFallback ||
            g_EnableChunkProxyDebug ||
            EnvFlagEnabled("BZR_CHUNK_TRACE") ||
            EnvFlagEnabled("OPENSHIM_CHUNK_TRACE") ||
            chunkLogBudgetSpecified ||
            chunkTraceEntryLimitSpecified;
        g_TraceChunkRenderVerbose =
            EnvFlagEnabled("BZR_CHUNK_TRACE_VERBOSE") ||
            EnvFlagEnabled("OPENSHIM_CHUNK_TRACE_VERBOSE");
        g_TraceChunkEffectRuntime =
            EnvFlagEnabled("BZR_TRACE_CHUNK_EFFECT") ||
            EnvFlagEnabled("OPENSHIM_TRACE_CHUNK_EFFECT") ||
            EnvFlagEnabled("OPENSHIM_CHUNK_EFFECT_TRACE");
        g_TraceSatelliteVisibility =
            EnvFlagEnabled("BZR_TRACE_SAT_VIS") ||
            EnvFlagEnabled("OPENSHIM_TRACE_SAT_VIS") ||
            EnvFlagEnabled("OPENSHIM_TRACE_SATELLITE_VISIBILITY");
        g_ConstructorRemoteBuildFixEnabled =
            !(EnvFlagEnabled("OPENSHIM_DISABLE_CONSTRUCTOR_REMOTE_BUILD_FIX") ||
              EnvFlagEnabled("BZR_DISABLE_CONSTRUCTOR_REMOTE_BUILD_FIX"));
        long constructorCleanupTraceBudget = kConstructorRemoteBuildTraceBudgetDefault;
        if (TryGetEnvLong("OPENSHIM_TRACE_CONSTRUCTOR_REMOTE_BUILD_BUDGET", constructorCleanupTraceBudget) ||
            TryGetEnvLong("BZR_TRACE_CONSTRUCTOR_REMOTE_BUILD_BUDGET", constructorCleanupTraceBudget))
        {
            if (constructorCleanupTraceBudget < 0)
                constructorCleanupTraceBudget = 0;
        }
        g_ConstructorRemoteBuildTraceBudget = constructorCleanupTraceBudget;
        long chunkProxyCapacity = static_cast<long>(g_ChunkProxyCapacity);
        if (TryGetEnvLong("OPENSHIM_CHUNK_PROXY_CAP", chunkProxyCapacity) ||
            TryGetEnvLong("OPENSHIM_CHUNK_PROXY_CAPACITY", chunkProxyCapacity))
        {
            g_ChunkProxyCapacity = ClampChunkProxyCapacity(chunkProxyCapacity);
        }
        else
        {
            g_ChunkProxyCapacity = 96;
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
        long satelliteVisibilityBudget = 8;
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
        g_ChunkProxyBillboardSet = nullptr;
        g_ChunkProxySlots.clear();
        float turretAimPitchMultiplier = g_TurretAimPitchMultiplierEnhanced;
        if (TryGetEnvFloat("OPENSHIM_TURRET_AIM_PITCH_MULTIPLIER", turretAimPitchMultiplier) ||
            TryGetEnvFloat("OPENSHIM_TURRET_PITCH_MULTIPLIER", turretAimPitchMultiplier))
        {
            g_TurretAimPitchMultiplierEnhanced = ClampTurretAimPitchMultiplier(turretAimPitchMultiplier);
        }
        else
        {
            g_TurretAimPitchMultiplierEnhanced = 0.95f;
        }
        g_TurretAimPitchMultiplier = g_TurretAimPitchEnabled ? g_TurretAimPitchMultiplierEnhanced : 0.5f;
        Log(L"[CHUNK] Force-first-geo fallback: %hs\n",
            g_EnableChunkRenderFallback ? "enabled" : "disabled");
        Log(L"[CHUNK] Trace logging: %hs%s budget=%ld entryLimit=%u\n",
            g_TraceChunkRender ? "enabled" : "disabled",
            g_TraceChunkRenderVerbose ? " verbose" : "",
            static_cast<long>(g_ChunkRenderLogBudget),
            g_ChunkTraceEntryLimit);
        Log(L"[CHUNKPROXY] Placeholder proxy debug: %hs cap=%u size=%.2f\n",
            g_EnableChunkProxyDebug ? "enabled" : "disabled",
            g_ChunkProxyCapacity,
            g_ChunkProxyDebugSize);
        Log(L"[CHUNKEFFECT] Runtime manager trace: %hs vtableSlot=0x%08X orig=0x%08X\n",
            g_TraceChunkEffectRuntime ? "enabled" : "disabled",
            static_cast<uint32_t>(kChunkEffectVtableSimulateSlotAddr),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_ChunkEffectSimulate)));
        Log(L"[SATVIS] Satellite visibility trace: %hs budget=%ld interval=%lums objectLimit=%u viewRecord=0x%08X objectList=0x%08X userObject=0x%08X\n",
            g_TraceSatelliteVisibility ? "enabled" : "disabled",
            g_SatelliteVisibilityLogBudget,
            static_cast<unsigned long>(g_SatelliteVisibilityLogIntervalMs),
            g_SatelliteVisibilityObjectLimit,
            static_cast<uint32_t>(GetMainModuleBase() + kViewRecordRva),
            static_cast<uint32_t>(GetMainModuleBase() + kGameObjectObjectListRva),
            static_cast<uint32_t>(GetMainModuleBase() + kGameObjectUserObjectRva));
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
        InitializeUnderAttackAlertConfig();
        InitializeTargetReticlePopupConfig();
        EnsureInputBindingPopulateHookScaffold();
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
            Log(L"[BAN] Experimental bans path=%hs entries=%u\n",
                bansConfigPath.c_str(),
                static_cast<unsigned>(g_BanRecords.size()));
        }
    }

    void RetryDeferredRuntimeHooks()
    {
        InstallJumpSnipingProbeIfRequested();
        InstallCareerStatsMpHookIfPossible();
        InstallShieldTowerTeamFilterHookIfPossible();
        InstallAiTuningHooksIfPossible();
        InstallConstructorRemoteBuildFixIfPossible();
        EnsureInputBindingPopulateHookScaffold();
    }

    void InitBzrHookStrings()
    {
        BzrStringInitEmpty(&g_BzrnetLabel1);
        BzrStringInitEmpty(&g_BzrnetLabel2);
        BzrStringInitEmpty(&g_BzrnetLabel3);
        BzrStringInitEmpty(&g_BzrnetLabel4);
    }

    void PrimeUnderAttackAlertConfig()
    {
        InitializeUnderAttackAlertConfig();
    }

    bool SetUnderAttackAlertModeFromBridge(int mode)
    {
        return SetUnderAttackAlertModeInternal(ClampUnderAttackAlertMode(mode), true);
    }

    void PrimeTargetReticlePopupConfig()
    {
        InitializeTargetReticlePopupConfig();
    }

    bool SetTargetReticlePopupModeFromBridge(int mode)
    {
        return SetTargetReticlePopupModeInternal(ClampTargetReticlePopupMode(mode), true);
    }

    bool SetBomberAiRangeEnabledFromBridge(bool enabled)
    {
        RetryDeferredRuntimeHooks();
        g_BomberAiRangeEnabled = enabled;
        Log(L"[MISSIONHOOK] bomber AI range override %hs\n", enabled ? "enabled" : "disabled");
        return true;
    }

    bool SetHowitzerVolleyEnabledFromBridge(bool enabled)
    {
        g_HowitzerVolleyEnabled = enabled;
        Log(L"[MISSIONHOOK] howitzer volley override %hs\n", enabled ? "enabled" : "disabled");
        return true;
    }

    bool SetWeaponMaskCarrierBiasEnabledFromBridge(bool enabled)
    {
        g_WeaponMaskCarrierBiasEnabled = enabled;
        Log(L"[MISSIONHOOK] weapon-mask carrier bias %hs\n", enabled ? "enabled" : "disabled");
        return true;
    }

    bool SetAiOdfGameplayTuningEnabledFromBridge(bool enabled)
    {
        RetryDeferredRuntimeHooks();
        g_AiOdfGameplayTuningEnabled = enabled;
        Log(L"[MISSIONHOOK] AI ODF gameplay tuning %hs\n", enabled ? "enabled" : "disabled");
        return true;
    }

    bool SetTurretAimPitchEnabledFromBridge(bool enabled)
    {
        g_TurretAimPitchEnabled = enabled;
        g_TurretAimPitchMultiplier = enabled ? g_TurretAimPitchMultiplierEnhanced : 0.5f;
        Log(L"[MISSIONHOOK] turret aim pitch override %hs active=%.3f\n",
            enabled ? "enabled" : "disabled",
            static_cast<double>(g_TurretAimPitchMultiplier));
        return true;
    }

    bool SetAttackRevealEnabledFromBridge(bool enabled)
    {
        RetryDeferredRuntimeHooks();
        g_AttackRevealEnabled = enabled;
        Log(L"[MISSIONHOOK] attack reveal %hs\n", enabled ? "enabled" : "disabled");
        return true;
    }

    bool ResetMissionHookOverridesFromBridge()
    {
        RetryDeferredRuntimeHooks();
        g_BomberAiRangeEnabled = kBomberAiRangeEnabledDefault;
        g_HowitzerVolleyEnabled = kHowitzerVolleyEnabledDefault;
        g_WeaponMaskCarrierBiasEnabled = kWeaponMaskCarrierBiasEnabledDefault;
        g_AiOdfGameplayTuningEnabled = kAiOdfGameplayTuningEnabledDefault;
        g_TurretAimPitchEnabled = kTurretAimPitchEnabledDefault;
        g_AttackRevealEnabled = kAttackRevealEnabledDefault;
        g_AttackRevealTraceBudget = kAttackRevealTraceBudgetDefault;
        g_TurretAimPitchMultiplier = 0.5f;
        Log(L"[MISSIONHOOK] restored mission hook overrides to defaults\n");
        return true;
    }

    bool GetHudSpriteRectFromBridge(const char* name, int* outX, int* outY, int* outW, int* outH)
    {
        if (!outX || !outY || !outW || !outH)
        {
            Log(L"[HUD] Invalid rect output pointers for sprite '%hs'\n", name ? name : "<null>");
            return false;
        }

        const int spriteId = LookupHudSpriteId(name);
        if (spriteId <= 0)
        {
            Log(L"[HUD] Unknown sprite '%hs'\n", name ? name : "<null>");
            return false;
        }

        HudSpriteRectRecord current = {};
        if (!TryGetHudSpriteCurrentRecord(spriteId, current))
        {
            Log(L"[HUD] Failed reading live rect entry for sprite '%hs' (id=%d)\n",
                name ? name : "<null>",
                spriteId);
            return false;
        }

        *outX = static_cast<int>(current.x);
        *outY = static_cast<int>(current.y);
        *outW = static_cast<int>(current.w);
        *outH = static_cast<int>(current.h);
        return true;
    }

    bool SetHudSpriteRectFromBridge(const char* name, int x, int y, int w, int h)
    {
        if (IsStockScrapPilotPanelName(name) && w == 0 && h == 0)
            return SetStockScrapPilotPanelsVisibleByUv(false);

        int spriteId = 0;
        HudSpriteRectRecord current = {};
        if (!ResolveHudSpriteForMutation(name, spriteId, current))
        {
            return false;
        }

        HudSpriteRectRecord updated = current;
        const auto hiddenIt = g_HudSpriteHiddenEntries.find(spriteId);
        if (hiddenIt != g_HudSpriteHiddenEntries.end())
            updated = hiddenIt->second;

        updated.x = ClampHudSpriteCoord(x);
        updated.y = ClampHudSpriteCoord(y);
        updated.w = ClampHudSpriteCoord(w);
        updated.h = ClampHudSpriteCoord(h);

        if (hiddenIt != g_HudSpriteHiddenEntries.end())
        {
            hiddenIt->second = updated;

            HudSpriteRectRecord hiddenRecord = updated;
            hiddenRecord.w = 0;
            hiddenRecord.h = 0;
            if (!WriteHudSpriteRectEntry(spriteId, hiddenRecord))
            {
                Log(L"[HUD] Failed updating hidden sprite '%hs' (id=%d)\n",
                    name ? name : "<null>",
                    spriteId);
                return false;
            }
        }
        else if (!WriteHudSpriteRectEntry(spriteId, updated))
        {
            Log(L"[HUD] Failed writing rect for sprite '%hs' (id=%d)\n",
                name ? name : "<null>",
                spriteId);
            return false;
        }

        Log(L"[HUD] Sprite rect %hs id=%d => (%d,%d,%d,%d)%s\n",
            name ? name : "<null>",
            spriteId,
            static_cast<int>(updated.x),
            static_cast<int>(updated.y),
            static_cast<int>(updated.w),
            static_cast<int>(updated.h),
            hiddenIt != g_HudSpriteHiddenEntries.end() ? " [hidden snapshot]" : "");
        return true;
    }

    bool SetHudSpriteVisibleFromBridge(const char* name, bool visible)
    {
        if (IsStockScrapPilotPanelName(name))
            return SetStockScrapPilotPanelsVisibleByUv(visible);

        const int spriteId = LookupHudSpriteId(name);
        if (spriteId <= 0)
        {
            Log(L"[HUD] Unknown sprite '%hs'\n", name ? name : "<null>");
            return false;
        }

        const auto hiddenIt = g_HudSpriteHiddenEntries.find(spriteId);
        if (!visible)
        {
            if (hiddenIt != g_HudSpriteHiddenEntries.end())
            {
                Log(L"[HUD] Sprite already hidden %hs id=%d\n", name ? name : "<null>", spriteId);
                return true;
            }

            HudSpriteRectRecord current = {};
            if (!TryGetHudSpriteCurrentRecord(spriteId, current))
            {
                Log(L"[HUD] Failed reading live rect entry for sprite '%hs' (id=%d)\n",
                    name ? name : "<null>",
                    spriteId);
                return false;
            }

            g_HudSpriteOriginalEntries.emplace(spriteId, current);
            g_HudSpriteHiddenEntries[spriteId] = current;

            HudSpriteRectRecord hiddenRecord = current;
            hiddenRecord.w = 0;
            hiddenRecord.h = 0;
            if (!WriteHudSpriteRectEntry(spriteId, hiddenRecord))
            {
                Log(L"[HUD] Failed hiding sprite '%hs' (id=%d)\n",
                    name ? name : "<null>",
                    spriteId);
                return false;
            }

            Log(L"[HUD] Sprite hidden %hs id=%d\n", name ? name : "<null>", spriteId);
            return true;
        }

        if (hiddenIt == g_HudSpriteHiddenEntries.end())
        {
            Log(L"[HUD] Sprite already visible %hs id=%d\n", name ? name : "<null>", spriteId);
            return true;
        }

        if (!WriteHudSpriteRectEntry(spriteId, hiddenIt->second))
        {
            Log(L"[HUD] Failed restoring visible state for sprite '%hs' (id=%d)\n",
                name ? name : "<null>",
                spriteId);
            return false;
        }

        g_HudSpriteHiddenEntries.erase(spriteId);
        Log(L"[HUD] Sprite shown %hs id=%d\n", name ? name : "<null>", spriteId);
        return true;
    }

    bool RestoreHudSpriteFromBridge(const char* name)
    {
        if (IsStockScrapPilotPanelName(name))
            return SetStockScrapPilotPanelsVisibleByUv(true);

        const int spriteId = LookupHudSpriteId(name);
        if (spriteId <= 0)
        {
            Log(L"[HUD] Unknown sprite '%hs'\n", name ? name : "<null>");
            return false;
        }

        const auto originalIt = g_HudSpriteOriginalEntries.find(spriteId);
        if (originalIt == g_HudSpriteOriginalEntries.end())
        {
            Log(L"[HUD] No cached original rect for sprite '%hs' (id=%d)\n",
                name ? name : "<null>",
                spriteId);
            return false;
        }

        if (!WriteHudSpriteRectEntry(spriteId, originalIt->second))
        {
            Log(L"[HUD] Failed restoring original rect for sprite '%hs' (id=%d)\n",
                name ? name : "<null>",
                spriteId);
            return false;
        }

        g_HudSpriteHiddenEntries.erase(spriteId);
        Log(L"[HUD] Sprite restored %hs id=%d\n", name ? name : "<null>", spriteId);
        return true;
    }

    bool RestoreAllHudSpritesFromBridge()
    {
        bool anyFailed = false;
        for (const auto& entry : g_HudSpriteOriginalEntries)
        {
            if (!WriteHudSpriteRectEntry(entry.first, entry.second))
            {
                anyFailed = true;
                Log(L"[HUD] Failed restoring cached sprite id=%d during restore-all\n", entry.first);
            }
        }

        if (!anyFailed)
        {
            g_HudSpriteHiddenEntries.clear();
            Log(L"[HUD] Restored %u cached HUD sprite rect(s)\n",
                static_cast<unsigned>(g_HudSpriteOriginalEntries.size()));
        }

        return !anyFailed;
    }

    float __fastcall TargetReticlePopupRecentHitGetterHook(void* objectPtr, void* /*edx*/)
    {
        InitializeTargetReticlePopupConfig();

        const float playerShotTime = GetGameObjectPlayerShotTime(objectPtr);
        switch (g_TargetReticlePopupMode)
        {
        case TargetReticlePopupMode::ExplicitOnly:
            return kSuppressedRecentHitTime;
        case TargetReticlePopupMode::NeutralOnly:
            return IsNeutralTeamObject(objectPtr) ? kSuppressedRecentHitTime : playerShotTime;
        case TargetReticlePopupMode::Default:
        default:
            return playerShotTime;
        }
    }

    void __cdecl RevealProcessOwnerPerceivedTeamOnAttackStateEntry(void* processPtr)
    {
        RevealProcessOwnerPerceivedTeam(processPtr, "attack_state_entry");
    }

    void __cdecl HandleUnderAttackAlert(float currentTime)
    {
        InitializeUnderAttackAlertConfig();
        if (!g_UnderAttackAlertEnabled)
            return;

        if (currentTime <= g_UnderAttackAlertNextAllowedTime)
            return;

        if (g_BzrFn_PlayGlobalSound && kUnderAttackAlertSoundAddr != 0)
        {
            const char* sound = reinterpret_cast<const char*>(kUnderAttackAlertSoundAddr);
            g_BzrFn_PlayGlobalSound(sound, 0, 0, 0);
        }

        const float minSpacing = 1.0f;
        const float nextDelay =
            (std::max)(g_UnderAttackAlertCooldownSeconds, minSpacing);
        g_UnderAttackAlertNextAllowedTime = currentTime + nextDelay;
    }

    namespace
    {
        struct CarrierView
        {
            void* owner;
            void* hardpoint[5];
            void* weapon[5];
            uint32_t existant;
            uint32_t selected;
            uint32_t enabled;
            int32_t special;
            float weaponTriggerTillTime;
        };

        constexpr size_t kGameObjectCarrierOffset = 0x198;
        constexpr size_t kGameObjectWeaponMaskOffset = 0x210;
        constexpr size_t kUnitProcessMeOffset = 44;
        constexpr size_t kWeaponIndexOffset = 0xAC;

        constexpr uint32_t kHowitzerVftPrimary = 0x0087AD70;
        constexpr uint32_t kHowitzerVftSecondary = 0x0087AE1C;
        constexpr uint32_t kMinelayerVftPrimary = 0x0087D790;
        constexpr uint32_t kMinelayerVftSecondary = 0x0087D83C;

        bool IsHowitzerCraft(const void* craft)
        {
            if (!craft)
                return false;

            const uint32_t vft = *reinterpret_cast<const uint32_t*>(craft);
            return vft == kHowitzerVftPrimary ||
                vft == kHowitzerVftSecondary;
        }

        bool IsWeaponMaskCarrierBiasCraft(const void* craft)
        {
            if (!craft)
                return false;

            const uint32_t vft = *reinterpret_cast<const uint32_t*>(craft);
            return vft == kMinelayerVftPrimary ||
                vft == kMinelayerVftSecondary;
        }

        int FindPreferredWeaponSlot(const void* craft)
        {
            const auto* craftBytes = reinterpret_cast<const uint8_t*>(craft);
            const uint32_t rawMask = *reinterpret_cast<const uint32_t*>(craftBytes + kGameObjectWeaponMaskOffset);
            const uint32_t decodedMask = rawMask ^ 0x33333333u;

            if (decodedMask != 0 && (decodedMask & (decodedMask - 1u)) == 0)
            {
                for (int slot = 0; slot < 5; ++slot)
                {
                    if (decodedMask == (1u << slot))
                        return slot;
                }
            }

            const uint32_t activeSlot = *reinterpret_cast<const uint32_t*>(craftBytes + 0x1CC);
            return activeSlot < 5 ? static_cast<int>(activeSlot) : -1;
        }

        int FindWeaponArrayIndexForSlot(const CarrierView* carrier, int desiredSlot)
        {
            if (!carrier)
                return -1;

            for (int index = 0; index < 5; ++index)
            {
                const auto* weapon = reinterpret_cast<const uint8_t*>(carrier->weapon[index]);
                if (!weapon)
                    continue;

                if (*reinterpret_cast<const int32_t*>(weapon + kWeaponIndexOffset) == desiredSlot)
                    return index;
            }

            if (desiredSlot >= 0 && desiredSlot < 5 && carrier->weapon[desiredSlot] != nullptr)
                return desiredSlot;

            return -1;
        }

        void SwapCarrierBits(uint32_t& bits, int a, int b)
        {
            const uint32_t bitA = (bits >> a) & 1u;
            const uint32_t bitB = (bits >> b) & 1u;
            if (bitA == bitB)
                return;

            bits ^= (1u << a);
            bits ^= (1u << b);
        }

        struct CarrierSnapshot
        {
            void* hardpoint[5];
            void* weapon[5];
            uint32_t existant;
            uint32_t selected;
            uint32_t enabled;
        };

        void SnapshotCarrierState(const CarrierView* carrier, CarrierSnapshot* snapshot)
        {
            if (!carrier || !snapshot)
                return;

            memcpy(snapshot->hardpoint, carrier->hardpoint, sizeof(snapshot->hardpoint));
            memcpy(snapshot->weapon, carrier->weapon, sizeof(snapshot->weapon));
            snapshot->existant = carrier->existant;
            snapshot->selected = carrier->selected;
            snapshot->enabled = carrier->enabled;
        }

        void RestoreCarrierState(CarrierView* carrier, const CarrierSnapshot& snapshot)
        {
            if (!carrier)
                return;

            memcpy(carrier->hardpoint, snapshot.hardpoint, sizeof(snapshot.hardpoint));
            memcpy(carrier->weapon, snapshot.weapon, sizeof(snapshot.weapon));
            carrier->existant = snapshot.existant;
            carrier->selected = snapshot.selected;
            carrier->enabled = snapshot.enabled;
        }

        void MoveCarrierWeaponIndexToFront(CarrierView* carrier, int desiredIndex)
        {
            if (!carrier || desiredIndex <= 0 || desiredIndex >= 5)
                return;

            std::swap(carrier->hardpoint[0], carrier->hardpoint[desiredIndex]);
            std::swap(carrier->weapon[0], carrier->weapon[desiredIndex]);
            SwapCarrierBits(carrier->existant, 0, desiredIndex);
            SwapCarrierBits(carrier->selected, 0, desiredIndex);
            SwapCarrierBits(carrier->enabled, 0, desiredIndex);
        }

        int CollectCarrierVolleyIndices(const CarrierView* carrier, int* outIndices, int maxCount)
        {
            if (!carrier || !outIndices || maxCount <= 0)
                return 0;

            int count = 0;
            for (int index = 0; index < 5 && count < maxCount; ++index)
            {
                if (!carrier->weapon[index])
                    continue;

                outIndices[count++] = index;
            }

            return count;
        }

        using FnArtilleryHowitzerVolleyOriginal =
            uint32_t(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

        uint32_t CallOriginalArtilleryHowitzerVolley(
            void* process,
            uint32_t arg1,
            uint32_t arg2,
            uint32_t arg3,
            uint32_t arg4,
            uint32_t arg5)
        {
            auto fn = reinterpret_cast<FnArtilleryHowitzerVolleyOriginal>(
                Trampoline_ArtilleryHowitzerVolleyOriginal);
            return fn(process, arg1, arg2, arg3, arg4, arg5);
        }
    }

    void __cdecl ApplyWeaponMaskCarrierBiasForCraft(void* craft)
    {
        if (!g_WeaponMaskCarrierBiasEnabled)
            return;

        if (!craft)
            return;

        __try
        {
            if (!IsWeaponMaskCarrierBiasCraft(craft))
                return;

            const int desiredSlot = FindPreferredWeaponSlot(craft);
            if (desiredSlot < 0 || desiredSlot >= 5)
                return;

            auto* craftBytes = reinterpret_cast<uint8_t*>(craft);
            auto* carrier = *reinterpret_cast<CarrierView**>(craftBytes + kGameObjectCarrierOffset);
            if (!carrier)
                return;

            const int currentIndex = FindWeaponArrayIndexForSlot(carrier, desiredSlot);
            if (currentIndex <= 0)
                return;

            std::swap(carrier->hardpoint[0], carrier->hardpoint[currentIndex]);
            std::swap(carrier->weapon[0], carrier->weapon[currentIndex]);
            SwapCarrierBits(carrier->existant, 0, currentIndex);
            SwapCarrierBits(carrier->selected, 0, currentIndex);
            SwapCarrierBits(carrier->enabled, 0, currentIndex);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }

    void __cdecl TraceArtilleryMaskFromProcess(void* process)
    {
        if (!process)
            return;

        __try
        {
            auto* processBytes = reinterpret_cast<uint8_t*>(process);
            void* craft = *reinterpret_cast<void**>(processBytes + 44);
            ApplyWeaponMaskCarrierBiasForCraft(craft);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }

        if (!ShouldTraceArtilleryMask())
            return;

        const long remaining = InterlockedDecrement(&g_ArtilleryMaskTraceBudget);
        if (remaining < 0)
            return;

        const uint32_t processAddr = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(process));

        __try
        {
            auto* processBytes = reinterpret_cast<uint8_t*>(process);
            void* craft = *reinterpret_cast<void**>(processBytes + 44);
            const uint32_t craftAddr = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft));
            const uint32_t processVft = *reinterpret_cast<const uint32_t*>(process);
            const uint32_t craftVft = craft ? *reinterpret_cast<const uint32_t*>(craft) : 0;

            uint32_t rawMask = 0;
            uint32_t decodedMask = 0;
            uint32_t enabledMask = 0;
            uint32_t activeSlot = 0xFFFFFFFFu;

            if (craft)
            {
                auto* craftBytes = reinterpret_cast<uint8_t*>(craft);
                rawMask = *reinterpret_cast<const uint32_t*>(craftBytes + 0x210);
                decodedMask = rawMask ^ 0x33333333u;
                enabledMask = *reinterpret_cast<const uint32_t*>(craftBytes + 0x1C8);
                activeSlot = *reinterpret_cast<const uint32_t*>(craftBytes + 0x1CC);
            }

            Log(L"[ARTYMASK] process=0x%08X procVft=0x%08X craft=0x%08X craftVft=0x%08X raw=0x%08X decoded=0x%08X enabled=0x%08X active=%u remaining=%ld\n",
                processAddr,
                processVft,
                craftAddr,
                craftVft,
                rawMask,
                decodedMask,
                enabledMask,
                activeSlot,
                remaining);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Log(L"[ARTYMASK] exception while inspecting process=0x%08X remaining=%ld\n",
                processAddr,
                remaining);
        }
    }

    uint32_t __cdecl ArtilleryHowitzerVolleyHook(
        void* process,
        uint32_t arg1,
        uint32_t arg2,
        uint32_t arg3,
        uint32_t arg4,
        uint32_t arg5)
    {
        if (!g_BZRFnPtr_ArtilleryHowitzerVolleyContinue)
            return 0;
        if (!g_HowitzerVolleyEnabled)
            return CallOriginalArtilleryHowitzerVolley(process, arg1, arg2, arg3, arg4, arg5);

        uint32_t lastResult = 0;
        bool startedVolley = false;
        CarrierView* carrier = nullptr;
        CarrierSnapshot snapshot = {};
        bool hasSnapshot = false;

        __try
        {
            if (!process)
            {
                return CallOriginalArtilleryHowitzerVolley(process, arg1, arg2, arg3, arg4, arg5);
            }

            auto* processBytes = reinterpret_cast<uint8_t*>(process);
            void* craft = *reinterpret_cast<void**>(processBytes + kUnitProcessMeOffset);
            if (!IsHowitzerCraft(craft))
            {
                return CallOriginalArtilleryHowitzerVolley(process, arg1, arg2, arg3, arg4, arg5);
            }

            auto* craftBytes = reinterpret_cast<uint8_t*>(craft);
            carrier = *reinterpret_cast<CarrierView**>(craftBytes + kGameObjectCarrierOffset);
            if (!carrier)
            {
                return CallOriginalArtilleryHowitzerVolley(process, arg1, arg2, arg3, arg4, arg5);
            }

            int volleyIndices[5] = {};
            const int volleyCount = CollectCarrierVolleyIndices(carrier, volleyIndices, 5);
            if (volleyCount <= 1)
            {
                return CallOriginalArtilleryHowitzerVolley(process, arg1, arg2, arg3, arg4, arg5);
            }

            SnapshotCarrierState(carrier, &snapshot);
            hasSnapshot = true;

            if (ShouldTraceArtilleryMask())
            {
                const long remaining = InterlockedDecrement(&g_ArtilleryMaskTraceBudget);
                if (remaining >= 0)
                {
                    Log(L"[ARTYVOLLEY] process=0x%08X craft=0x%08X weapons=%d raw=0x%08X decoded=0x%08X\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(process)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                        volleyCount,
                        *reinterpret_cast<const uint32_t*>(craftBytes + kGameObjectWeaponMaskOffset),
                        *reinterpret_cast<const uint32_t*>(craftBytes + kGameObjectWeaponMaskOffset) ^ 0x33333333u);
                }
            }

            for (int i = 0; i < volleyCount; ++i)
            {
                RestoreCarrierState(carrier, snapshot);
                MoveCarrierWeaponIndexToFront(carrier, volleyIndices[i]);
                lastResult = CallOriginalArtilleryHowitzerVolley(process, arg1, arg2, arg3, arg4, arg5);
                startedVolley = true;
            }

            RestoreCarrierState(carrier, snapshot);
            return startedVolley ?
                lastResult :
                CallOriginalArtilleryHowitzerVolley(process, arg1, arg2, arg3, arg4, arg5);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            if (hasSnapshot && carrier)
            {
                __try
                {
                    RestoreCarrierState(carrier, snapshot);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            return startedVolley ?
                lastResult :
                CallOriginalArtilleryHowitzerVolley(process, arg1, arg2, arg3, arg4, arg5);
        }
    }

    void SetProducerBuildMenuOriginal(void* target)
    {
        g_BzrFn_ProducerModeCallOriginal = reinterpret_cast<FnProducerModeCall>(target);
        Log(L"[PRODMENU] Original producer helper target=0x%08X\n",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(target)));
    }

    static uint8_t* VehicleEntryAt(void* context, uint32_t index)
    {
        if (!context) return nullptr;
        auto table = *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(context) + 0x18);
        if (!table) return nullptr;
        uint32_t bucket = *reinterpret_cast<uint32_t*>(table + 0x0C);
        uint32_t mask = *reinterpret_cast<uint32_t*>(table + 0x08);
        if (mask == 0) return nullptr;
        mask -= 1;
        uint32_t base = *reinterpret_cast<uint32_t*>(table + 0x04);
        return *reinterpret_cast<uint8_t**>(base + ((bucket + index) & mask) * 4);
    }

    static void VehicleListModFix_Select(const BzrString* name)
    {
        if (!g_VehicleListContext || !name)
            return;

        auto ctx = reinterpret_cast<uint8_t*>(g_VehicleListContext);
        *reinterpret_cast<int*>(ctx + 0x38) = -1;

        uint8_t* match = nullptr;
        auto table = *reinterpret_cast<uint8_t**>(ctx + 0x18);
        if (table)
        {
            uint32_t count = *reinterpret_cast<uint32_t*>(table + 0x10);
            if (count)
            {
                uint32_t bucket = *reinterpret_cast<uint32_t*>(table + 0x0C);
                uint32_t mask = *reinterpret_cast<uint32_t*>(table + 0x08);
                uint32_t base = *reinterpret_cast<uint32_t*>(table + 0x04);
                if (mask)
                {
                    mask -= 1;
                    for (uint32_t i = 0; i < count; ++i)
                    {
                        auto entry = *reinterpret_cast<uint8_t**>(base + ((bucket + i) & mask) * 4);
                        if (!entry)
                            continue;
                        auto entryStr = reinterpret_cast<const BzrString*>(entry);
                        if (BzrStringEquals(entryStr, name))
                        {
                            match = entry;
                            *reinterpret_cast<uint32_t*>(ctx + 0x38) = i;
                            break;
                        }
                    }
                }
            }
        }

        BzrString title;
        BzrString subtitle;
        BzrStringInitEmpty(&title);
        BzrStringInitEmpty(&subtitle);
        if (match)
        {
            BzrStringCopy(&title, reinterpret_cast<const BzrString*>(match));
            BzrStringCopy(&subtitle, reinterpret_cast<const BzrString*>(match + 0x3C));
        }

        void* listThis = (g_BzrPtr_945478 && *g_BzrPtr_945478) ? *g_BzrPtr_945478 : nullptr;
        if (g_BzrFn_VehicleListSet && listThis)
            g_BzrFn_VehicleListSet(listThis, title, subtitle);

        BzrString file;
        BzrStringInitEmpty(&file);
        BzrStringCopy(&file, name);
        BzrStringAppend(&file, ".vxt", 4);

        void* mgrThis = (g_BzrPtr_94548C && *g_BzrPtr_94548C) ? *g_BzrPtr_94548C : nullptr;
        if (mgrThis)
            CallVehicleListLoadSafely(mgrThis, &file, "VehicleListModFix_Select");

        if (g_BzrFn_VehicleListRefresh1 && g_VehicleListContext)
            g_BzrFn_VehicleListRefresh1(g_VehicleListContext);
        if (g_BzrFn_VehicleListRefresh2 && g_VehicleListContext)
            g_BzrFn_VehicleListRefresh2(g_VehicleListContext);
        if (g_BzrFn_VehicleListFinalize && listThis)
            g_BzrFn_VehicleListFinalize(listThis);

        BzrStringFree(&title);
        BzrStringFree(&subtitle);
        BzrStringFree(&file);
    }

    void __fastcall VehicleListModFix2(void* thisPtr, void* /*edx*/, BzrString* name)
    {
        g_VehicleListContext = thisPtr;
        VehicleListModFix_Select(name);
    }

    void VehicleListModFix4Helper()
    {
        if (!g_BzrPtr_94555C || !*g_BzrPtr_94555C)
            return;

        auto root = reinterpret_cast<uint8_t*>(*g_BzrPtr_94555C);
        g_VehicleListContext = *reinterpret_cast<void**>(root + 0x1C8);
        if (!g_VehicleListContext)
            return;

        auto ctx = reinterpret_cast<uint8_t*>(g_VehicleListContext);
        int index = *reinterpret_cast<int*>(ctx + 0x38);
        BzrString title;
        BzrString subtitle;
        BzrStringInitEmpty(&title);
        BzrStringInitEmpty(&subtitle);

        if (index >= 0)
        {
            auto entry = VehicleEntryAt(g_VehicleListContext, static_cast<uint32_t>(index));
            if (entry)
            {
                BzrStringCopy(&title, reinterpret_cast<const BzrString*>(entry));
                BzrStringCopy(&subtitle, reinterpret_cast<const BzrString*>(entry + 0x3C));
            }
        }

        void* listThis = (g_BzrPtr_945478 && *g_BzrPtr_945478) ? *g_BzrPtr_945478 : nullptr;
        if (g_BzrFn_VehicleListSet && listThis)
            g_BzrFn_VehicleListSet(listThis, title, subtitle);

        void* mgrThis = (g_BzrPtr_94548C && *g_BzrPtr_94548C) ? *g_BzrPtr_94548C : nullptr;
        if (mgrThis && g_VehicleListParam)
        {
            CallVehicleListLoadSafely(
                mgrThis,
                reinterpret_cast<BzrString*>(g_VehicleListParam),
                "VehicleListModFix4Helper");
        }

        if (g_BzrFn_VehicleListFinalize && listThis)
            g_BzrFn_VehicleListFinalize(listThis);

        BzrStringFree(&title);
        BzrStringFree(&subtitle);
    }

    namespace
    {
        struct BanLookupIdentity
        {
            int type = 0;
            uint64_t uid = 0;
            const BzrString* name = nullptr;
            char stableId[32] = {};
        };

        static bool TryBuildBanLookupIdentity(int type, uint64_t uid, const BzrString* name, BanLookupIdentity& out)
        {
            if (type != 1 && type != 2)
                return false;

            const char prefix = (type == 1) ? 'S' : 'G';
            std::snprintf(
                out.stableId,
                sizeof(out.stableId),
                "%c%llu",
                prefix,
                static_cast<unsigned long long>(uid));
            out.type = type;
            out.uid = uid;
            out.name = name;
            return true;
        }

        static bool TryGetBanLookupIdentityForSessionId(uint16_t sessionId, BanLookupIdentity& out)
        {
            if (!g_BzrFn_BanLookup)
                return false;

            uint8_t* entry = reinterpret_cast<uint8_t*>(g_BzrFn_BanLookup(sessionId));
            if (!entry)
                return false;

            const int type = *reinterpret_cast<int*>(entry + 0x30);
            const uint64_t uid = *reinterpret_cast<uint64_t*>(entry + 0x38);
            const auto* name = reinterpret_cast<const BzrString*>(entry + 0x74);
            return TryBuildBanLookupIdentity(type, uid, name, out);
        }

        static void KickBannedPlayers(const char* source, uint32_t lobby, uint32_t member, int changes)
        {
            EnsureBansConfigLoaded();

            if (!g_BzrFn_IsHost || g_BzrFn_IsHost() == 0)
            {
                Log(L"[BAN] %hs sweep skipped lobby=0x%08X member=0x%08X changes=0x%08X (not host)\n",
                    source ? source : "ban",
                    lobby,
                    member,
                    static_cast<uint32_t>(changes));
                return;
            }

            if (g_BanRecords.empty())
            {
                Log(L"[BAN] %hs sweep skipped lobby=0x%08X member=0x%08X changes=0x%08X (no bans loaded)\n",
                    source ? source : "ban",
                    lobby,
                    member,
                    static_cast<uint32_t>(changes));
                return;
            }

            if (!g_BzrFn_CommandHandler || !g_BzrFn_BanLookup)
            {
                Log(L"[BAN] %hs sweep skipped lobby=0x%08X member=0x%08X changes=0x%08X (helpers unavailable)\n",
                    source ? source : "ban",
                    lobby,
                    member,
                    static_cast<uint32_t>(changes));
                return;
            }

            int kicks = 0;
            for (uint16_t sessionId = 0; sessionId < kBanScanMaxSessionId; ++sessionId)
            {
                BanLookupIdentity identity = {};
                if (!TryGetBanLookupIdentityForSessionId(sessionId, identity))
                    continue;

                if (!IsBanIdConfigured(identity.stableId))
                    continue;

                const char* nameText =
                    (identity.name && identity.name->size) ? BzrStringData(identity.name) : "";
                Log(L"[BAN] %hs matched session=%u stable=%hs type=%d uid=%llu name=%hs lobby=0x%08X member=0x%08X changes=0x%08X\n",
                    source ? source : "ban",
                    sessionId,
                    identity.stableId,
                    identity.type,
                    static_cast<unsigned long long>(identity.uid),
                    nameText,
                    lobby,
                    member,
                    static_cast<uint32_t>(changes));
                g_BzrFn_CommandHandler(sessionId, "/kick");
                ++kicks;
            }

            Log(L"[BAN] %hs sweep complete lobby=0x%08X member=0x%08X changes=0x%08X kicks=%d entries=%u\n",
                source ? source : "ban",
                lobby,
                member,
                static_cast<uint32_t>(changes),
                kicks,
                static_cast<unsigned>(g_BanRecords.size()));
        }
    }

    void* __cdecl ProducerBuildMenuCallHook(void* producerPtr, int slot, int flags)
    {
        MaybeApplyProducerBuildMenu(producerPtr);

        if (!g_BzrFn_ProducerModeCallOriginal)
            return nullptr;

        return g_BzrFn_ProducerModeCallOriginal(producerPtr, slot, flags);
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
        if (!g_EnableChunkRenderFallback && !g_TraceChunkRender && !g_TraceChunkRenderVerbose && !g_EnableChunkProxyDebug)
            return resolved;

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
                Log(L"[CHUNK] Resolve hook exception obj=0x%08X variant=0x%08X resolved=0x%08X code=0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectPtr)),
                    variant,
                    resolved,
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        return resolved;
    }

    void __cdecl MapFilterOnScrollUp()
    {
        if (EnvFlagEnabled("OPENSHIM_TRACE_MAP_REFRESH") ||
            EnvFlagEnabled("OPENSHIM_TRACE_STEAM_MAP_REFRESH"))
        {
            Log(L"[MAPTRACE] MapFilterOnScrollUp list=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_MapFilterListPtr)));
        }
        if (g_MapFilterListPtr && g_BzrFn_MapFilterScrollUp)
            g_BzrFn_MapFilterScrollUp();
    }

    void __cdecl MapFilterOnScrollDown()
    {
        if (EnvFlagEnabled("OPENSHIM_TRACE_MAP_REFRESH") ||
            EnvFlagEnabled("OPENSHIM_TRACE_STEAM_MAP_REFRESH"))
        {
            Log(L"[MAPTRACE] MapFilterOnScrollDown list=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_MapFilterListPtr)));
        }
        if (g_MapFilterListPtr && g_BzrFn_MapFilterScrollDown)
            g_BzrFn_MapFilterScrollDown();
    }

    namespace
    {
        struct BzrVector
        {
            BzrString* begin;
            BzrString* end;
            BzrString* cap;
        };

        struct MapFilterList
        {
            BzrVector keys;
            BzrVector labels;
        };

        struct MapEntry
        {
            BzrString name;
            int32_t field18;
            int32_t field1C;
            BzrString str20;
            char type;
            uint8_t pad39[3];
            BzrString str3C;
            BzrString str54;
            BzrString str6C;
            BzrString str84;
            BzrString str9C;
        };

        struct MapRing
        {
            void* pad0;
            void** entries;
            uint32_t capacity;
            uint32_t head;
            uint32_t count;
        };

        struct MapManager
        {
            uint8_t pad[0x1C];
            MapEntry** entries;
            uint32_t capacity;
            uint32_t head;
            uint32_t count;
        };

        static_assert(offsetof(MapEntry, field18) == 0x18, "MapEntry field18 offset mismatch");
        static_assert(offsetof(MapEntry, str20) == 0x20, "MapEntry str20 offset mismatch");
        static_assert(offsetof(MapEntry, type) == 0x38, "MapEntry type offset mismatch");
        static_assert(offsetof(MapEntry, str3C) == 0x3C, "MapEntry str3C offset mismatch");
        static_assert(offsetof(MapEntry, str54) == 0x54, "MapEntry str54 offset mismatch");
        static_assert(offsetof(MapEntry, str6C) == 0x6C, "MapEntry str6C offset mismatch");
        static_assert(offsetof(MapEntry, str84) == 0x84, "MapEntry str84 offset mismatch");
        static_assert(offsetof(MapEntry, str9C) == 0x9C, "MapEntry str9C offset mismatch");
        static_assert(sizeof(MapEntry) == 0xB4, "MapEntry size mismatch");

        static MapManager* GetMapManager()
        {
            __try
            {
                return *reinterpret_cast<MapManager**>(0x00945478);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        static bool BzrStringIsBlank(const BzrString* s)
        {
            if (!s || s->size == 0)
                return true;
            const char* data = BzrStringData(s);
            for (uint32_t i = 0; i < s->size; ++i)
            {
                if (data[i] != ' ' && data[i] != '\t' && data[i] != '\r' && data[i] != '\n')
                    return false;
            }
            return true;
        }

        static bool BzrStringEqualsCStr(const BzrString* s, const char* text)
        {
            if (!s || !text)
                return false;
            const size_t len = std::strlen(text);
            if (s->size != len)
                return false;
            const char* data = BzrStringData(s);
            return std::memcmp(data, text, len) == 0;
        }

        static bool BzrStringStartsWithI(const BzrString* s, const char* prefix)
        {
            if (!s || !prefix)
                return false;
            const size_t plen = std::strlen(prefix);
            if (s->size < plen)
                return false;
            const char* data = BzrStringData(s);
            for (size_t i = 0; i < plen; ++i)
            {
                if (std::tolower(static_cast<unsigned char>(data[i])) !=
                    std::tolower(static_cast<unsigned char>(prefix[i])))
                    return false;
            }
            return true;
        }

        static bool BzrStringContainsI(const BzrString* s, const char* needle)
        {
            if (!s || !needle || !*needle)
                return false;
            const size_t nlen = std::strlen(needle);
            if (nlen == 0 || s->size < nlen)
                return false;
            const char* data = BzrStringData(s);
            for (uint32_t i = 0; i + nlen <= s->size; ++i)
            {
                bool match = true;
                for (size_t j = 0; j < nlen; ++j)
                {
                    if (std::tolower(static_cast<unsigned char>(data[i + j])) !=
                        std::tolower(static_cast<unsigned char>(needle[j])))
                    {
                        match = false;
                        break;
                    }
                }
                if (match)
                    return true;
            }
            return false;
        }

        static void BzrVectorClear(BzrVector* v)
        {
            if (!v)
                return;
            if (v->begin && v->end)
            {
                for (BzrString* cur = v->begin; cur < v->end; ++cur)
                    BzrStringFree(cur);
            }
            if (v->begin)
                std::free(v->begin);
            v->begin = nullptr;
            v->end = nullptr;
            v->cap = nullptr;
        }

        static void BzrVectorEnsure(BzrVector* v, size_t extra)
        {
            if (!v)
                return;
            const size_t size = v->begin ? static_cast<size_t>(v->end - v->begin) : 0;
            const size_t cap = v->begin ? static_cast<size_t>(v->cap - v->begin) : 0;
            if (size + extra <= cap)
                return;

            size_t new_cap = cap ? cap * 2 : 8;
            if (new_cap < size + extra)
                new_cap = size + extra;

            BzrString* mem = static_cast<BzrString*>(std::malloc(new_cap * sizeof(BzrString)));
            if (!mem)
                return;

            if (v->begin && size)
            {
                std::memcpy(mem, v->begin, size * sizeof(BzrString));
                std::free(v->begin);
            }
            v->begin = mem;
            v->end = mem + size;
            v->cap = mem + new_cap;
        }

        static void BzrVectorPushCStr(BzrVector* v, const char* str)
        {
            if (!v)
                return;
            if (!str)
                str = "";
            BzrVectorEnsure(v, 1);
            if (!v->begin || v->end >= v->cap)
                return;
            BzrStringInitEmpty(v->end);
            BzrStringAssign(v->end, str, std::strlen(str));
            v->end += 1;
        }

        static void MapFilterListClear(MapFilterList* list)
        {
            if (!list)
                return;
            BzrVectorClear(&list->keys);
            BzrVectorClear(&list->labels);
        }

        static void MapFilterListPush(MapFilterList* list, const char* key, const char* label)
        {
            if (!list)
                return;
            BzrVectorPushCStr(&list->keys, key ? key : "");
            BzrVectorPushCStr(&list->labels, label ? label : "");
        }

        static bool MapEntryHasTag(const MapEntry* entry, const char* tag)
        {
            if (!entry || !tag || !*tag)
                return false;
            return BzrStringContainsI(&entry->str3C, tag) ||
                   BzrStringContainsI(&entry->str54, tag) ||
                   BzrStringContainsI(&entry->str6C, tag) ||
                   BzrStringContainsI(&entry->str84, tag) ||
                   BzrStringContainsI(&entry->str9C, tag) ||
                   BzrStringContainsI(&entry->name, tag)  ||
                   BzrStringContainsI(&entry->str20, tag);
        }

        static bool MapEntryIsStock(const MapEntry* entry)
        {
            if (!entry)
                return false;
            return BzrStringIsBlank(&entry->str3C);
        }

        static bool MapEntryIsTRO(const MapEntry* entry)
        {
            if (!entry)
                return false;
            return BzrStringStartsWithI(&entry->name, "evolve_");
        }

        static bool MapEntryMatchesPlayers(const MapEntry* entry, int count)
        {
            if (!entry || count <= 0)
                return false;
            int minP = entry->field1C;
            int maxP = entry->field18;
            if (minP > maxP)
                std::swap(minP, maxP);
            if (minP <= 0 || maxP <= 0)
                return false;
            return minP <= count && maxP >= count;
        }

        static void MapEntryInit(MapEntry* entry)
        {
            if (!entry)
                return;
            std::memset(entry, 0, sizeof(*entry));
            BzrStringInitEmpty(&entry->name);
            BzrStringInitEmpty(&entry->str20);
            BzrStringInitEmpty(&entry->str3C);
            BzrStringInitEmpty(&entry->str54);
            BzrStringInitEmpty(&entry->str6C);
            BzrStringInitEmpty(&entry->str84);
            BzrStringInitEmpty(&entry->str9C);
        }

        static void MapEntryCopy(MapEntry* dst, const MapEntry* src)
        {
            if (!dst || !src)
                return;
            MapEntryInit(dst);
            BzrStringCopy(&dst->name, &src->name);
            dst->field18 = src->field18;
            dst->field1C = src->field1C;
            BzrStringCopy(&dst->str20, &src->str20);
            dst->type = src->type;
            BzrStringCopy(&dst->str3C, &src->str3C);
            BzrStringCopy(&dst->str54, &src->str54);
            BzrStringCopy(&dst->str6C, &src->str6C);
            BzrStringCopy(&dst->str84, &src->str84);
            BzrStringCopy(&dst->str9C, &src->str9C);
        }

        static void MapEntryDestroy(MapEntry* entry)
        {
            if (!entry)
                return;
            BzrStringFree(&entry->name);
            BzrStringFree(&entry->str20);
            BzrStringFree(&entry->str3C);
            BzrStringFree(&entry->str54);
            BzrStringFree(&entry->str6C);
            BzrStringFree(&entry->str84);
            BzrStringFree(&entry->str9C);
            operator delete(entry);
        }

        static void MapRingClear(MapRing* ring)
        {
            if (!ring)
                return;
            if (ring->entries)
            {
                for (uint32_t i = 0; i < ring->capacity; ++i)
                {
                    if (ring->entries[i])
                    {
                        MapEntryDestroy(reinterpret_cast<MapEntry*>(ring->entries[i]));
                        ring->entries[i] = nullptr;
                    }
                }
                std::free(ring->entries);
            }
            ring->entries = nullptr;
            ring->capacity = 0;
            ring->head = 0;
            ring->count = 0;
        }

        static void MapRingEnsure(MapRing* ring, uint32_t needed)
        {
            if (!ring)
                return;
            if (ring->capacity > ring->count + needed + 1)
                return;

            uint32_t new_cap = ring->capacity ? ring->capacity : 1;
            while (new_cap == ring->capacity || new_cap < 8)
                new_cap <<= 1;
            while (new_cap <= ring->count + needed + 1)
                new_cap <<= 1;

            void** mem = static_cast<void**>(std::calloc(new_cap, sizeof(void*)));
            if (!mem)
                return;

            for (uint32_t i = 0; i < ring->count; ++i)
            {
                uint32_t idx = ring->capacity ? ((ring->head + i) & (ring->capacity - 1)) : 0;
                mem[i] = ring->entries ? ring->entries[idx] : nullptr;
            }

            if (ring->entries)
                std::free(ring->entries);

            ring->entries = mem;
            ring->capacity = new_cap;
            ring->head = 0;
        }

        static void MapRingPush(MapRing* ring, const MapEntry* entry)
        {
            if (!ring || !entry)
                return;
            MapRingEnsure(ring, 1);
            if (!ring->entries || ring->capacity == 0)
                return;
            ring->head &= (ring->capacity - 1);
            const uint32_t idx = (ring->head + ring->count) & (ring->capacity - 1);
            if (!ring->entries[idx])
            {
                ring->entries[idx] = operator new(sizeof(MapEntry));
            }
            MapEntryCopy(reinterpret_cast<MapEntry*>(ring->entries[idx]), entry);
            ring->count += 1;
        }

        static uint32_t ComputeMapFilterFlags()
        {
            MapManager* mgr = GetMapManager();
            if (!mgr || !mgr->entries || mgr->capacity == 0)
                return 0;

            uint32_t flags = 0;
            for (uint32_t i = 0; i < mgr->count; ++i)
            {
                uint32_t idx = (mgr->head + i) & (mgr->capacity - 1);
                MapEntry* entry = mgr->entries[idx];
                if (!entry)
                    continue;

                if (MapEntryHasTag(entry, "Favorites"))
                    flags |= 0x4;
                if (MapEntryHasTag(entry, "Special"))
                    flags |= 0x2;
                if (MapEntryIsStock(entry) || !MapEntryIsStock(entry))
                    flags |= 0x1;

                switch (entry->type)
                {
                    case 'M': flags |= 0x20; break;
                    case 'A': flags |= 0x40; break;
                    case 'X': flags |= 0x80; break;
                    default: break;
                }

                for (int players = 5; players <= 15; ++players)
                {
                    if (MapEntryMatchesPlayers(entry, players))
                    {
                        flags |= (0x100u << (players - 5));
                    }
                }
            }
            return flags;
        }

        static const char* LocalizeMaybe(const char* section, const char* key, const char* fallback)
        {
            if (g_BzrFn_Localize)
            {
                const char* txt = g_BzrFn_Localize(section, key);
                if (txt && *txt)
                    return txt;
            }
            return fallback;
        }
    }

    void __cdecl MapFilters1Rebuild(void* listPtr)
    {
        if (!listPtr)
            return;

        auto* list = reinterpret_cast<MapFilterList*>(listPtr);
        MapFilterListClear(list);

        const uint32_t flags = ComputeMapFilterFlags();
        if (EnvFlagEnabled("OPENSHIM_TRACE_MAP_REFRESH") ||
            EnvFlagEnabled("OPENSHIM_TRACE_STEAM_MAP_REFRESH"))
        {
            Log(L"[MAPTRACE] MapFilters1Rebuild list=0x%08X flags=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(listPtr)),
                flags);
        }

        if (flags & 0x4)
        {
            MapFilterListPush(list, "Favorites", "Favorites");
            MapFilterListPush(list, "", "");
        }

        MapFilterListPush(list, "All Maps",
            LocalizeMaybe("filters", "all_maps", "All Maps"));

        if (flags & 0x1)
        {
            MapFilterListPush(list, "Stock",
                LocalizeMaybe("filters", "stock", "Stock"));
        }

        MapFilterListPush(list, "Stock_BZ98", "Stock (BZ98)");
        MapFilterListPush(list, "Stock_TRO", "Stock (TRO)");

        if (flags & 0x1)
        {
            MapFilterListPush(list, "Workshop",
                LocalizeMaybe("filters", "workshop", "Workshop"));
        }

        MapFilterListPush(list, "", "");

        MapFilterListPush(list, "Strategy",
            LocalizeMaybe("filters", "strategy", "Strategy"));

        if (flags & 0x20)
            MapFilterListPush(list, "Mission MPI", "Mission MPI");

        MapFilterListPush(list, "Death Match",
            LocalizeMaybe("filters", "death_match", "Death Match"));

        if (flags & 0x40)
            MapFilterListPush(list, "Action MPI", "Action MPI");

        MapFilterListPush(list, "KOTH",
            LocalizeMaybe("filters", "koth", "KOTH"));

        if (flags & 0x2)
            MapFilterListPush(list, "Special", "Special");

        MapFilterListPush(list, "", "");
        MapFilterListPush(list, "", "");

        MapFilterListPush(list, "2 Players",
            LocalizeMaybe("filters", "2_players", "2 Players"));
        MapFilterListPush(list, "3 Players",
            LocalizeMaybe("filters", "3_players", "3 Players"));
        MapFilterListPush(list, "4 Players",
            LocalizeMaybe("filters", "4_players", "4 Players"));

        const struct { int players; uint32_t bit; } kPlayerFlags[] =
        {
            { 5, 0x100 }, { 6, 0x200 }, { 7, 0x400 }, { 8, 0x800 },
            { 9, 0x1000 }, { 10, 0x2000 }, { 11, 0x4000 }, { 12, 0x8000 },
            { 13, 0x10000 }, { 14, 0x20000 }, { 15, 0x40000 },
        };

        for (const auto& entry : kPlayerFlags)
        {
            if (flags & entry.bit)
            {
                char label[16] = {};
                std::snprintf(label, sizeof(label), "%d Players", entry.players);
                MapFilterListPush(list, label, label);
            }
        }

        if (static_cast<int32_t>(flags) < 0)
        {
            MapFilterListPush(list, "", "");
            MapFilterListPush(list, "Other", "Other");
        }
    }

    void __cdecl MapFilters2Filter(void* listPtr, BzrString* filter)
    {
        if (!listPtr || !filter)
            return;

        auto* ring = reinterpret_cast<MapRing*>(listPtr);
        MapRingClear(ring);

        const char* filterStr = BzrStringData(filter);
        const uint32_t filterLen = filter->size;
        if (!filterStr || filterLen == 0)
            return;
        if (EnvFlagEnabled("OPENSHIM_TRACE_MAP_REFRESH") ||
            EnvFlagEnabled("OPENSHIM_TRACE_STEAM_MAP_REFRESH"))
        {
            Log(L"[MAPTRACE] MapFilters2Filter list=0x%08X filter=%hs len=%u\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(listPtr)),
                filterStr,
                filterLen);
        }

        MapManager* mgr = GetMapManager();
        if (!mgr || !mgr->entries || mgr->capacity == 0)
            return;

        for (uint32_t i = 0; i < mgr->count; ++i)
        {
            uint32_t idx = (mgr->head + i) & (mgr->capacity - 1);
            const MapEntry* entry = mgr->entries[idx];
            if (!entry)
                continue;

            bool include = false;
            if (BzrStringEqualsCStr(filter, "All Maps"))
                include = true;
            else if (BzrStringEqualsCStr(filter, "Stock"))
                include = MapEntryIsStock(entry);
            else if (BzrStringEqualsCStr(filter, "Stock_BZ98"))
                include = MapEntryIsStock(entry) && !MapEntryIsTRO(entry);
            else if (BzrStringEqualsCStr(filter, "Stock_TRO"))
                include = MapEntryIsStock(entry) && MapEntryIsTRO(entry);
            else if (BzrStringEqualsCStr(filter, "Workshop"))
                include = !MapEntryIsStock(entry);
            else if (BzrStringEqualsCStr(filter, "Strategy"))
                include = entry->type == 'S';
            else if (BzrStringEqualsCStr(filter, "Mission MPI"))
                include = entry->type == 'M';
            else if (BzrStringEqualsCStr(filter, "Death Match"))
                include = entry->type == 'D';
            else if (BzrStringEqualsCStr(filter, "Action MPI"))
                include = entry->type == 'A';
            else if (BzrStringEqualsCStr(filter, "KOTH"))
                include = entry->type == 'K';
            else if (BzrStringEqualsCStr(filter, "Special"))
                include = MapEntryHasTag(entry, "Special");
            else if (BzrStringEqualsCStr(filter, "Favorites"))
                include = MapEntryHasTag(entry, "Favorites");
            else if (BzrStringEqualsCStr(filter, "Other"))
                include = entry->type == 'X';
            else if (filterLen >= 8 && std::strstr(filterStr, "Players"))
            {
                const int count = std::atoi(filterStr);
                include = MapEntryMatchesPlayers(entry, count);
            }
            else
            {
                include = MapEntryHasTag(entry, filterStr);
            }

            if (include)
                MapRingPush(ring, entry);
        }
    }

    void __cdecl EngineFlameHoverCraftEmitHook(
        void* managerPtr,
        const void* transform,
        uint32_t scaleBits,
        void* craftPtr)
    {
        if (g_IsSteamExe)
            ResolveEngineFlameRuntimeTargets();

        if (!g_BzrFn_EngineFlameAddFlame || !managerPtr || !transform)
            return;

        ApplyWeaponMaskCarrierBiasForCraft(craftPtr);
        ObserveEngineFlameManager(managerPtr);
        EnsureEngineFlameVtableHooksInstalled(managerPtr);

        const float scale = *reinterpret_cast<const float*>(&scaleBits);
        void* selectedManager = SelectEngineFlameManager(managerPtr, craftPtr);
        g_BzrFn_EngineFlameAddFlame(selectedManager, transform, scale);
    }

    void __fastcall EngineFlameControlHook(void* thisPtr, void* /*edx*/)
    {
        if (!g_BzrFn_EngineFlameControl || !thisPtr)
            return;

        EnsureEngineFlameVariantsInitialized();
        g_BzrFn_EngineFlameControl(thisPtr);

        if (thisPtr == GetEngineFlamePrimary())
        {
            if (g_EngineFlamePrimaryRedTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlamePrimaryRed);
            if (g_EngineFlamePrimaryGreenTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlamePrimaryGreen);
            return;
        }

        if (thisPtr == GetEngineFlameSecondary())
        {
            if (g_EngineFlamePrimaryRedTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlameSecondaryRed);
            if (g_EngineFlamePrimaryGreenTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlameSecondaryGreen);
        }
    }

    void __fastcall EngineFlameSubmitHook(void* thisPtr, void* /*edx*/, void* camera)
    {
        if (!g_BzrFn_EngineFlameSubmit || !thisPtr)
            return;

        EnsureEngineFlameVariantsInitialized();
        g_BzrFn_EngineFlameSubmit(thisPtr, camera);
        TickChunkProxyDebug();

        if (thisPtr == GetEngineFlamePrimary())
        {
            if (g_EngineFlamePrimaryRedTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlamePrimaryRed, camera);
            if (g_EngineFlamePrimaryGreenTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlamePrimaryGreen, camera);
            return;
        }

        if (thisPtr == GetEngineFlameSecondary())
        {
            if (g_EngineFlamePrimaryRedTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlameSecondaryRed, camera);
            if (g_EngineFlamePrimaryGreenTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlameSecondaryGreen, camera);
        }
    }

    void __fastcall ChunkEffectSimulateHook(void* thisPtr, void* /*edx*/, float dt)
    {
        if (!g_BzrFn_ChunkEffectSimulate || !thisPtr)
            return;

        if (!g_JumpSnipeProbeInstalled)
            InstallJumpSnipingProbeIfRequested();
        if (!g_CareerStatsMpHookInstalled)
            InstallCareerStatsMpHookIfPossible();

        MaybeLogSatelliteVisibilitySample();
        TrackChunkEffectActiveEntries(thisPtr);
        LogChunkEffectRuntimeSample(thisPtr, dt);
        g_BzrFn_ChunkEffectSimulate(thisPtr, dt);
    }

    bool __cdecl HandleCommandHelpBan(uint16_t id, const char* cmd)
    {
        if (!cmd || !*cmd)
            return false;

        if (_stricmp(cmd, "/help") == 0)
        {
            static const char* kHelpLines[] =
            {
                "[M] - mute/unmute - select the player in the list and click \"M\"",
                "[L] - kick - select the player in the list and click \"K\"",
                "[B] - ban - select the player in the list and click \"B\"",
                "/lock - prevent new players from joining",
                "/unlock - allow new players to join",
            };

            void* helpObj = (g_BzrPtr_920168 && *g_BzrPtr_920168) ? *g_BzrPtr_920168 : nullptr;
            for (const char* line : kHelpLines)
            {
                if (g_BzrFn_HelpLog && helpObj)
                    g_BzrFn_HelpLog(helpObj, line);
                if (g_BzrFn_HelpUi)
                    g_BzrFn_HelpUi(0, line);
            }
            return true;
        }

        if (_stricmp(cmd, "/ban") == 0)
        {
            if (g_BzrFn_IsHost && g_BzrFn_IsHost() == 0)
            {
                Log(L"[BAN] /ban blocked (client mode)\n");
                return true;
            }
            if (static_cast<int16_t>(id) < 0)
            {
                Log(L"[BAN] /ban failed: invalid target id (id=%u)\n", id);
                return true;
            }
            else if (!g_BzrFn_BanLookup)
            {
                Log(L"[BAN] /ban failed: ban lookup unavailable (id=%u)\n", id);
                return true;
            }

            BanLookupIdentity identity = {};
            if (!TryGetBanLookupIdentityForSessionId(id, identity))
            {
                Log(L"[BAN] /ban failed: lookup returned no stable identity (id=%u)\n", id);
                return true;
            }

            AddBanConfigEntry(identity.stableId, identity.name, "/ban");
            Log(L"[BAN] /ban queued immediate enforcement session=%u stable=%hs name=%hs\n",
                id,
                identity.stableId,
                (identity.name && identity.name->size) ? BzrStringData(identity.name) : "");
            if (g_BzrFn_CommandHandler)
                g_BzrFn_CommandHandler(id, "/kick");
            KickBannedPlayers("/ban", 0, id, 0);
            return true;
        }

        return false;
    }

    void __cdecl HandleJoinerEvent(uint32_t lobby, uint32_t member, int changes)
    {
        EnsureBansConfigLoaded();
        Log(L"[BAN] Join event observed lobby=0x%08X member=0x%08X changes=0x%08X bans=%u host=%hs\n",
            lobby,
            member,
            static_cast<uint32_t>(changes),
            static_cast<unsigned>(g_BanRecords.size()),
            (g_BzrFn_IsHost && g_BzrFn_IsHost() != 0) ? "yes" : "no");
        KickBannedPlayers("join_event", lobby, member, changes);
    }

    namespace
    {
        static void ResetHostUiCache()
        {
            g_BanButtonHost = nullptr;
            g_BanLabelHost = nullptr;
            g_FlagButtonHost = nullptr;
            g_FlagLabelHost = nullptr;
        }

        static void ResetClientUiCache()
        {
            g_BanButtonClient = nullptr;
            g_BanLabelClient = nullptr;
            g_FlagButtonClient = nullptr;
            g_FlagLabelClient = nullptr;
        }

        static void EnsureUiCacheMatchesParent(void* parent, bool host)
        {
            if (!parent)
                return;

            void*& cachedParent = host ? g_HostUiParent : g_ClientUiParent;
            if (cachedParent == parent)
                return;

            cachedParent = parent;
            if (host)
                ResetHostUiCache();
            else
                ResetClientUiCache();
        }

        static void UpdateFlagSelectionUiLabel(void* label)
        {
            if (g_FlagApplyPending)
            {
                if (!TryApplySelectedFlagThroughEngine("ui_update"))
                    TryApplyCachedFlagPayload("ui_update");
            }

            if (!label || !g_BzrFn_SetTooltip)
                return;

            const std::string summary = GetSelectedFlagSummary();
            g_BzrFn_SetTooltip(label, summary.c_str());
        }

        static void CreateFlagButtonCommon(
            void* parent,
            float x,
            float y,
            void** outButton,
            void** outLabel,
            void* onClick,
            void* onHover)
        {
            if (!parent || !outButton || !outLabel || !g_BzrFn_ButtonCtor || !g_BzrFn_LabelCtor || !g_BzrFn_AddChild)
                return;

            EnsureFlagCatalogLoaded();
            PrimeSelectedFlagForTesting("ui_create");

            void* buttonMem = ::operator new(0x1EC, std::nothrow);
            if (!buttonMem)
                return;
            std::memset(buttonMem, 0, 0x1EC);

            *outButton = g_BzrFn_ButtonCtor(
                buttonMem,
                "Flag Select",
                x,
                y,
                kFlagButtonSize,
                kFlagButtonSize,
                0x20,
                parent,
                0,
                0);
            if (*outButton)
            {
                if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(*outButton, "MultiplayerModeButton_off.png");
                if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(*outButton, "MultiplayerModeButton_over.png");
                if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(*outButton, "MultiplayerModeButton_on.png");
                if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(*outButton, "F");
                if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(*outButton, onClick);
                if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(*outButton, onHover);
                g_BzrFn_AddChild(parent, *outButton, 0);
            }

            void* labelMem = ::operator new(0x930, std::nothrow);
            if (!labelMem)
                return;
            std::memset(labelMem, 0, 0x930);

            *outLabel = g_BzrFn_LabelCtor(
                labelMem,
                "Lobby",
                270.0f,
                960.0f,
                338.0f,
                43.0f,
                0x20,
                parent,
                0);
            if (*outLabel)
            {
                if (g_BzrFn_LabelState)
                    g_BzrFn_LabelState(*outLabel, nullptr);
                g_BzrFn_AddChild(parent, *outLabel, 0);
            }

            UpdateFlagSelectionUiLabel(*outLabel);
        }

        static void CycleSelectedFlag(int delta, const char* source)
        {
            EnsureFlagCatalogLoaded();
            if (g_FlagCatalog.empty())
                return;

            int nextIndex = g_SelectedFlagIndex;
            if (nextIndex < 0)
                nextIndex = 0;
            else
                nextIndex += delta;

            SelectFlagEntryByIndex(nextIndex, source);
            PrimeSelectedFlagForTesting(source);
        }
    }

    void __cdecl BanButtonOnClickHost()
    {
        if (!g_BzrPtr_9456D0 || !g_BzrFn_GetSelected)
            return;
        if (g_BzrFn_IsHost && g_BzrFn_IsHost() == 0)
        {
            Log(L"[BAN] Host ban button ignored while not hosting\n");
            return;
        }

        void* root = *g_BzrPtr_9456D0;
        if (!root)
            return;

        auto listObj = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(root) + 0x0C);
        auto selected = g_BzrFn_GetSelected(listObj);
        if (!selected)
            return;

        int type = *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(selected) + 0x08);
        if (type != 1 && type != 2)
            return;

        const char prefix = (type == 1) ? 'S' : 'G';
        uint64_t id = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(selected) + 0x10);
        char idbuf[32] = {};
        std::snprintf(idbuf, sizeof(idbuf), "%c%llu", prefix, static_cast<unsigned long long>(id));

        BzrString name;
        BzrStringInitEmpty(&name);
        BzrStringCopy(&name, reinterpret_cast<BzrString*>(reinterpret_cast<uint8_t*>(selected) + 0x2C));
        Log(L"[BAN] Host button selected stable=%hs name=%hs\n",
            idbuf,
            name.size ? BzrStringData(&name) : "");
        AddBanConfigEntry(idbuf, &name, "host_button");
        KickBannedPlayers("host_button", 0, 0, 0);
        BzrStringFree(&name);
    }

    void __cdecl BanButtonOnClickClient()
    {
        if (!g_BzrPtr_94557C || !g_BzrFn_GetSelected || !g_BzrFn_CommandHandler)
            return;
        if (g_BzrFn_IsHost && g_BzrFn_IsHost() == 0)
        {
            Log(L"[BAN] Client-side ban button blocked because local user is not host\n");
            return;
        }

        void* root = *g_BzrPtr_94557C;
        if (!root)
            return;

        void* listObj = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(root) + 0x194);
        void* selected = g_BzrFn_GetSelected(listObj);
        if (!selected)
            return;

        if (g_BzrPtr_CurrentUser)
        {
            auto cur = g_BzrPtr_CurrentUser;
            if (*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(selected) + 0x38) ==
                    *reinterpret_cast<uint32_t*>(cur + 8) &&
                *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(selected) + 0x3C) ==
                    *reinterpret_cast<uint32_t*>(cur + 0x0C))
                return;

            if (*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(selected) + 0x30) ==
                *reinterpret_cast<uint32_t*>(cur))
                return;
        }

        uint16_t id = *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(selected) + 0x28);
        Log(L"[BAN] Client-style lobby button issuing /ban for session=%u\n", id);
        g_BzrFn_CommandHandler(id, "/ban");
    }

    void __cdecl BanButtonOnHoverHost(void* param)
    {
        if (g_BzrFn_LabelState && g_BanLabelHost)
            g_BzrFn_LabelState(g_BanLabelHost, param);
    }

    void __cdecl BanButtonOnHoverClient(void* param)
    {
        if (g_BzrFn_LabelState && g_BanLabelClient)
            g_BzrFn_LabelState(g_BanLabelClient, param);
    }

    void __cdecl FlagButtonOnClickHost()
    {
        CycleSelectedFlag(1, "host_button");
        UpdateFlagSelectionUiLabel(g_FlagLabelHost);
    }

    void __cdecl FlagButtonOnClickClient()
    {
        CycleSelectedFlag(1, "client_button");
        UpdateFlagSelectionUiLabel(g_FlagLabelClient);
    }

    void __cdecl FlagButtonOnHoverHost(void* param)
    {
        if (g_BzrFn_LabelState && g_FlagLabelHost)
            g_BzrFn_LabelState(g_FlagLabelHost, param);
        UpdateFlagSelectionUiLabel(g_FlagLabelHost);
    }

    void __cdecl FlagButtonOnHoverClient(void* param)
    {
        if (g_BzrFn_LabelState && g_FlagLabelClient)
            g_BzrFn_LabelState(g_FlagLabelClient, param);
        UpdateFlagSelectionUiLabel(g_FlagLabelClient);
    }

    void __cdecl AutoSaveButtonOnClickLoad()
    {
        if (!g_BzrFn_SetShellState)
            return;

        char autoSavePath[MAX_PATH] = {};
        if (!TryGetAutoSaveFilePathUtf8(autoSavePath))
        {
            Log(L"[AUTOSAVE] AutoSave button clicked but no auto-save file exists\n");
            return;
        }

        __try
        {
            PrepareLoadScreenForSelection(g_AutoSaveLoadScreen);
            if (!QueueAutoSaveLoadPath(autoSavePath))
            {
                Log(L"[AUTOSAVE] Failed to queue auto-save load path=%hs\n", autoSavePath);
                return;
            }

            auto* queuedPath = reinterpret_cast<char*>(kQueuedLoadPathBufferAddr);
            Log(L"[AUTOSAVE] Auto-save queued for stock save-load state path=%hs\n",
                queuedPath);
            g_BzrFn_SetShellState(kLoadSaveState);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Log(L"[AUTOSAVE] Direct auto-save load raised an exception\n");
        }
    }

    static void AutoSaveLoadButtonCreate(void* parent, void* screen)
    {
        if (!parent || !screen || !g_BzrFn_ButtonCtor || !g_BzrFn_AddChild)
            return;

        if (!AutoSaveFileExists())
            return;

        const std::string autoSaveLabel = GetAutoSaveButtonLabel();
        if (g_AutoSaveLoadButton && g_AutoSaveLoadParent == parent && g_AutoSaveLoadScreen == screen)
        {
            if (g_BzrFn_SetButtonLabel)
                g_BzrFn_SetButtonLabel(g_AutoSaveLoadButton, autoSaveLabel.c_str());
            return;
        }

        g_AutoSaveLoadParent = parent;
        g_AutoSaveLoadScreen = screen;
        g_AutoSaveLoadButton = nullptr;

        void* buttonMem = ::operator new(0x1EC, std::nothrow);
        if (!buttonMem)
            return;

        std::memset(buttonMem, 0, 0x1EC);
        g_AutoSaveLoadButton = g_BzrFn_ButtonCtor(
            buttonMem,
            autoSaveLabel.c_str(),
            kAutoSaveLoadButtonX,
            kAutoSaveLoadButtonY,
            kAutoSaveLoadButtonW,
            kAutoSaveLoadButtonH,
            kAutoSaveLoadButtonFlags,
            parent,
            0,
            0);

        if (!g_AutoSaveLoadButton)
            return;

        if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(g_AutoSaveLoadButton, "mpcron.png");
        if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(g_AutoSaveLoadButton, "mpcrclk.png");
        if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(g_AutoSaveLoadButton, "mpcrclk.png");
        if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(g_AutoSaveLoadButton, autoSaveLabel.c_str());
        // 0x007CC660 is a label-style tooltip writer that stores text inline at
        // +0x144. Button objects use +0x150/+0x154 for hover/click callbacks,
        // so using it here corrupts the callback slot and crashes the load menu.
        if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(g_AutoSaveLoadButton, reinterpret_cast<void*>(AutoSaveButtonOnClickLoad));
        g_BzrFn_AddChild(parent, g_AutoSaveLoadButton, 0);
    }

    void AutoSaveLoadButtonCreateFromFrame(void* frameBase)
    {
        if (!frameBase)
            return;

        __try
        {
            auto* frame = reinterpret_cast<uint8_t*>(frameBase);
            void* parent = *reinterpret_cast<void**>(frame - 0x184);
            void* screen = *reinterpret_cast<void**>(frame - 0x178);
            AutoSaveLoadButtonCreate(parent, screen);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Log(L"[AUTOSAVE] Failed to inspect load screen frame for AutoSave button injection\n");
        }
    }

    void __fastcall RestartMissionPauseHook(void* thisPtr)
    {
        ForceFreshRestartMissionState(thisPtr, "pause");
    }

    void __fastcall RestartMissionFailureHook(void* thisPtr)
    {
        ForceFreshRestartMissionState(thisPtr, "failure");
    }

    void BanButtonCreateHost()
    {
        if (!g_BzrFn_ButtonCtor || !g_BzrFn_LabelCtor || !g_BzrFn_AddChild || !g_BanParentHost)
            return;

        void* parent = g_BanParentHost;
        EnsureUiCacheMatchesParent(parent, true);

        void* buttonMem = ::operator new(0x1EC, std::nothrow);
        if (!buttonMem)
            return;
        std::memset(buttonMem, 0, 0x1EC);
        g_BanButtonHost = g_BzrFn_ButtonCtor(
            buttonMem,
            "Ban User",
            g_BanX - 48.0f,
            g_BanY + 96.0f,
            48.0f,
            48.0f,
            0x20,
            parent,
            0,
            0);

        if (g_BanButtonHost)
        {
            if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(g_BanButtonHost, "MultiplayerModeButton_off.png");
            if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(g_BanButtonHost, "MultiplayerModeButton_over.png");
            if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(g_BanButtonHost, "MultiplayerModeButton_on.png");
            if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(g_BanButtonHost, "B");
            if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(g_BanButtonHost, reinterpret_cast<void*>(BanButtonOnClickHost));
            if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(g_BanButtonHost, reinterpret_cast<void*>(BanButtonOnHoverHost));
            g_BzrFn_AddChild(parent, g_BanButtonHost, 0);
        }

        void* labelMem = ::operator new(0x930, std::nothrow);
        if (!labelMem)
            return;
        std::memset(labelMem, 0, 0x930);
        g_BanLabelHost = g_BzrFn_LabelCtor(
            labelMem,
            "Lobby",
            270.0f,
            980.0f,
            338.0f,
            43.0f,
            0x8020,
            parent,
            0);

        if (g_BanLabelHost)
        {
            if (g_BzrFn_SetTooltip) g_BzrFn_SetTooltip(g_BanLabelHost, "Ban highlighted player");
            if (g_BzrFn_LabelState) g_BzrFn_LabelState(g_BanLabelHost, nullptr);
            g_BzrFn_AddChild(parent, g_BanLabelHost, 0);
        }

        if (ShouldEnableMultiplayerFlagUi() && (!g_FlagButtonHost || !g_FlagLabelHost))
        {
            CreateFlagButtonCommon(
                parent,
                g_BanX - 104.0f,
                g_BanY + 96.0f,
                &g_FlagButtonHost,
                &g_FlagLabelHost,
                reinterpret_cast<void*>(FlagButtonOnClickHost),
                reinterpret_cast<void*>(FlagButtonOnHoverHost));
        }
    }

    void BanButtonCreateClient()
    {
        if (!g_BzrFn_ButtonCtor || !g_BzrFn_LabelCtor || !g_BzrFn_AddChild || !g_BanParentClient)
            return;

        void* parent = g_BanParentClient;
        EnsureUiCacheMatchesParent(parent, false);

        void* buttonMem = ::operator new(0x1EC, std::nothrow);
        if (!buttonMem)
            return;
        std::memset(buttonMem, 0, 0x1EC);
        g_BanButtonClient = g_BzrFn_ButtonCtor(
            buttonMem,
            "Ban User",
            -33.0f,
            942.0f,
            48.0f,
            48.0f,
            0,
            parent,
            0,
            0);

        if (g_BanButtonClient)
        {
            if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(g_BanButtonClient, "MultiplayerModeButton_off.png");
            if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(g_BanButtonClient, "MultiplayerModeButton_over.png");
            if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(g_BanButtonClient, "MultiplayerModeButton_on.png");
            if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(g_BanButtonClient, "B");
            if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(g_BanButtonClient, reinterpret_cast<void*>(BanButtonOnClickClient));
            if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(g_BanButtonClient, reinterpret_cast<void*>(BanButtonOnHoverClient));
            g_BzrFn_AddChild(parent, g_BanButtonClient, 0);
        }

        void* labelMem = ::operator new(0x930, std::nothrow);
        if (!labelMem)
            return;
        std::memset(labelMem, 0, 0x930);
        g_BanLabelClient = g_BzrFn_LabelCtor(
            labelMem,
            "Lobby",
            270.0f,
            1000.0f,
            338.0f,
            43.0f,
            0x20,
            parent,
            0);

        if (g_BanLabelClient)
        {
            if (g_BzrFn_SetTooltip) g_BzrFn_SetTooltip(g_BanLabelClient, "Ban highlighted player");
            if (g_BzrFn_LabelState) g_BzrFn_LabelState(g_BanLabelClient, nullptr);
            g_BzrFn_AddChild(parent, g_BanLabelClient, 0);
        }

        if (ShouldEnableMultiplayerFlagUi() && (!g_FlagButtonClient || !g_FlagLabelClient))
        {
            CreateFlagButtonCommon(
                parent,
                -85.0f,
                942.0f,
                &g_FlagButtonClient,
                &g_FlagLabelClient,
                reinterpret_cast<void*>(FlagButtonOnClickClient),
                reinterpret_cast<void*>(FlagButtonOnHoverClient));
        }
    }
}
