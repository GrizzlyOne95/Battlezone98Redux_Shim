#include "bzr_hooks.h"
#include "patcher.h"

#include <Windows.h>
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <filesystem>
#include <new>

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
    void* g_AutoSaveLoadParent = nullptr;
    void* g_AutoSaveLoadScreen = nullptr;
    void* g_AutoSaveLoadButton = nullptr;

    uint32_t g_BanFlag = 0;
    float g_BanX = 0.0f;
    float g_BanY = 0.0f;
    float g_TurretAimPitchMultiplier = 0.95f;

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

    using FnUiCtor = void* (__thiscall*)(void* self,
                                         const char* label,
                                         float x, float y, float w, float h,
                                         uint32_t flags, void* parent, int a, int b);
    using FnUiSetStr = void(__thiscall*)(void* self, const char* str);
    using FnUiSetInt = void(__thiscall*)(void* self, void* param);
    using FnUiSetCb  = void(__thiscall*)(void* self, void* cb);
    using FnUiAddChild = void(__thiscall*)(void* parent, void* child, int flags);
    using FnUiDialogAction = void(__thiscall*)(void* thisPtr, int value);

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
    struct BuildItem;
    using FnBuildItemInit = void(__cdecl*)(BuildItem& item, int64_t token);
    using FnBuildItemCleanup = void(__cdecl*)(BuildItem& item);
    using FnProducerModeCall = void* (__cdecl*)(void* producerPtr, int slot, int flags);
    using FnEngineFlameAddFlame = void(__thiscall*)(void* self, const void* transform, float scale);
    using FnEngineFlameControl = void(__thiscall*)(void* self);
    using FnEngineFlameSubmit = void(__thiscall*)(void* self, void* camera);
    using FnEngineFlameResolveTexture = int(__cdecl*)(BzrString* textureName);
    using FnGetHandle = uint32_t(__thiscall*)(void* self);
    using FnGetTeamNum = int(__cdecl*)(int handle);
    using FnExuGetTeamEngineFlameColor = int(__cdecl*)(int team);

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

    static FnUiCtor g_BzrFn_ButtonCtor = nullptr; // 0x007C2480
    static FnUiCtor g_BzrFn_LabelCtor  = nullptr; // 0x007CC390
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
    static FnBuildItemInit g_BzrFn_InitBuildItem = nullptr; // 0x0049F5C0
    static FnBuildItemCleanup g_BzrFn_CleanupBuildItem = nullptr; // 0x0049F880
    static FnProducerModeCall g_BzrFn_ProducerModeCallOriginal = nullptr;
    static FnEngineFlameAddFlame g_BzrFn_EngineFlameAddFlame = reinterpret_cast<FnEngineFlameAddFlame>(0x004C8800);
    static FnEngineFlameControl g_BzrFn_EngineFlameControl = reinterpret_cast<FnEngineFlameControl>(0x004C88A0);
    static FnEngineFlameSubmit g_BzrFn_EngineFlameSubmit = reinterpret_cast<FnEngineFlameSubmit>(0x004C88C0);
    static FnEngineFlameResolveTexture g_BzrFn_EngineFlameResolveTexture = reinterpret_cast<FnEngineFlameResolveTexture>(0x0068BED0);
    static FnGetHandle g_BzrFn_GetHandle = reinterpret_cast<FnGetHandle>(0x00462380);
    static FnGetTeamNum g_BzrFn_GetTeamNum = reinterpret_cast<FnGetTeamNum>(0x005C8800);
    static FnExuGetTeamEngineFlameColor g_ExuFn_GetTeamEngineFlameColor = nullptr;
    static BuildItem* g_BzrBuildMenuRoot = nullptr;
    static bool g_IsSteamExe = false;

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
        constexpr int kLoadQueuedState = 5;
        constexpr int kQueuedLoadNameBufferLen = 16;
        constexpr uintptr_t kLoadScreenSelectionFlagAddr = 0x00918133;
        constexpr uintptr_t kQueuedLoadPathBufferAddr = 0x00945708;
        constexpr uintptr_t kQueuedLoadNameBufferAddr = 0x00915540;
        constexpr uintptr_t kBuildMenuRootAddr = 0x009174C4;
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
        constexpr uintptr_t kEngineFlamePrimaryAddr = 0x009B2C88;
        constexpr uintptr_t kEngineFlameSecondaryAddr = 0x009B3ED8;
        constexpr size_t kEngineFlameObjectSize = 0x1250;
        constexpr size_t kEngineFlameFlamePtrOffset = 0x1228;
        constexpr size_t kEngineFlameFlameTextureOffset = 0x123C;
        constexpr int kEngineFlameColorDefault = 0;
        constexpr int kEngineFlameColorBlue = 1;
        constexpr int kEngineFlameColorRed = 2;
        constexpr int kEngineFlameColorGreen = 3;

        enum class ProducerBuildMenuKind
        {
            Unknown,
            Recycler,
            Factory,
            Armory,
            ConstructionRig,
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
        };

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

        static bool g_EnableChunkRenderFallback = false;
        static volatile long g_ChunkRenderLogBudget = 12;
        static volatile long g_ArtilleryMaskTraceBudget = 400;
        static VehicleAssetExceptionCacheEntry g_VehicleAssetExceptionCache[kVehicleAssetExceptionCacheSize] = {};
        static ProducerBuildMenuConfig g_ProducerBuildMenuConfig = {};
        static bool g_HasAppliedProducerBuildMenu = false;
        static int64_t g_LastAppliedProducerBuildMenu = 0;
        static uint32_t g_LastUnknownProducerVft = 0;
        static bool g_LoggedExuEngineFlameBridge = false;
        static bool g_LoggedExuEngineFlameBridgeMissing = false;
        static bool g_EngineFlameVariantsInitialized = false;
        static bool g_EngineFlameVariantsInitAttempted = false;
        static int g_EngineFlamePrimaryRedTexture = 0;
        static int g_EngineFlamePrimaryGreenTexture = 0;
        alignas(16) static unsigned char g_EngineFlamePrimaryRed[kEngineFlameObjectSize] = {};
        alignas(16) static unsigned char g_EngineFlamePrimaryGreen[kEngineFlameObjectSize] = {};
        alignas(16) static unsigned char g_EngineFlameSecondaryRed[kEngineFlameObjectSize] = {};
        alignas(16) static unsigned char g_EngineFlameSecondaryGreen[kEngineFlameObjectSize] = {};

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

        static float ClampTurretAimPitchMultiplier(float value)
        {
            if (value < 0.0f)
                return 0.0f;
            if (value > 1.25f)
                return 1.25f;
            return value;
        }

        static void* GetEngineFlamePrimary()
        {
            return reinterpret_cast<void*>(kEngineFlamePrimaryAddr);
        }

        static void* GetEngineFlameSecondary()
        {
            return reinterpret_cast<void*>(kEngineFlameSecondaryAddr);
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
            if (g_ExuFn_GetTeamEngineFlameColor)
                return g_ExuFn_GetTeamEngineFlameColor;

            HMODULE exuModule = GetModuleHandleA("exu.dll");
            if (!exuModule)
                exuModule = GetModuleHandleA("ExtraUtilities.dll");

            if (!exuModule)
            {
                if (!g_LoggedExuEngineFlameBridgeMissing)
                {
                    Log(L"[FLAME] EXU module not loaded; team engine flame colors default to stock blue\n");
                    g_LoggedExuEngineFlameBridgeMissing = true;
                }
                return nullptr;
            }

            auto* proc = reinterpret_cast<FnExuGetTeamEngineFlameColor>(
                GetProcAddress(exuModule, "EXU_GetTeamEngineFlameColor"));
            if (!proc)
            {
                if (!g_LoggedExuEngineFlameBridgeMissing)
                {
                    Log(L"[FLAME] EXU_GetTeamEngineFlameColor export missing; team engine flame colors disabled\n");
                    g_LoggedExuEngineFlameBridgeMissing = true;
                }
                return nullptr;
            }

            g_ExuFn_GetTeamEngineFlameColor = proc;
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

            const int color = exuGetColor(team);
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
            if (g_EngineFlameVariantsInitialized || g_EngineFlameVariantsInitAttempted)
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

            if (g_EngineFlamePrimaryRedTexture != 0)
            {
                CloneEngineFlameManager(g_EngineFlamePrimaryRed, GetEngineFlamePrimary(), g_EngineFlamePrimaryRedTexture);
                CloneEngineFlameManager(g_EngineFlameSecondaryRed, GetEngineFlameSecondary(), g_EngineFlamePrimaryRedTexture);
            }

            if (g_EngineFlamePrimaryGreenTexture != 0)
            {
                CloneEngineFlameManager(g_EngineFlamePrimaryGreen, GetEngineFlamePrimary(), g_EngineFlamePrimaryGreenTexture);
                CloneEngineFlameManager(g_EngineFlameSecondaryGreen, GetEngineFlameSecondary(), g_EngineFlamePrimaryGreenTexture);
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

            if (!g_BzrFn_GetHandle || !g_BzrFn_GetTeamNum)
                return originalManager;

            const uint32_t handle = g_BzrFn_GetHandle(craftPtr);
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
            if (!g_ProducerBuildMenuConfig.constructionRig.hasValue)
            {
                g_ProducerBuildMenuConfig.constructionRig = ReadProducerBuildMenuEntry("Constructor");
            }

            const bool hasAnyEntry =
                g_ProducerBuildMenuConfig.recycler.hasValue ||
                g_ProducerBuildMenuConfig.factory.hasValue ||
                g_ProducerBuildMenuConfig.armory.hasValue ||
                g_ProducerBuildMenuConfig.constructionRig.hasValue;
            g_ProducerBuildMenuConfig.enabled = IsIniBoolTrue(enabledBuffer, true) && hasAnyEntry;

            Log(L"[PRODMENU] Config %hs loaded enabled=%hs recycler=%hs factory=%hs armory=%hs constrig=%hs\n",
                configPathString.c_str(),
                g_ProducerBuildMenuConfig.enabled ? "true" : "false",
                g_ProducerBuildMenuConfig.recycler.hasValue ? g_ProducerBuildMenuConfig.recycler.token : "-",
                g_ProducerBuildMenuConfig.factory.hasValue ? g_ProducerBuildMenuConfig.factory.token : "-",
                g_ProducerBuildMenuConfig.armory.hasValue ? g_ProducerBuildMenuConfig.armory.token : "-",
                g_ProducerBuildMenuConfig.constructionRig.hasValue ? g_ProducerBuildMenuConfig.constructionRig.token : "-");
        }

        static const ProducerBuildMenuEntry& SelectProducerBuildMenuEntry(ProducerBuildMenuKind kind)
        {
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
            if (g_IsSteamExe || !g_BzrFn_InitBuildItem || !g_BzrFn_CleanupBuildItem || !g_BzrBuildMenuRoot)
                return;

            LoadProducerBuildMenuConfig();
            if (!g_ProducerBuildMenuConfig.enabled)
                return;

            const ProducerBuildMenuKind kind = ClassifyProducerBuildMenuKind(producerPtr);
            const auto& entry = SelectProducerBuildMenuEntry(kind);
            if (!entry.hasValue)
                return;

            if (g_HasAppliedProducerBuildMenu && g_LastAppliedProducerBuildMenu == entry.packedToken)
                return;

            __try
            {
                g_BzrFn_CleanupBuildItem(*g_BzrBuildMenuRoot);
                g_BzrFn_InitBuildItem(*g_BzrBuildMenuRoot, entry.packedToken);
                g_HasAppliedProducerBuildMenu = true;
                g_LastAppliedProducerBuildMenu = entry.packedToken;
                Log(L"[PRODMENU] Applied %hs root=%hs producer=0x%08X\n",
                    ProducerBuildMenuKindName(kind),
                    entry.token,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(producerPtr)));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
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
    void ResolveBzrHooks(bool isSteam)
    {
        g_IsSteamExe = isSteam;
        g_BzrFn_ProducerModeCallOriginal = nullptr;
        g_BzrFn_InitBuildItem = nullptr;
        g_BzrFn_CleanupBuildItem = nullptr;
        g_BzrBuildMenuRoot = nullptr;
        g_ProducerBuildMenuConfig = {};
        g_HasAppliedProducerBuildMenu = false;
        g_LastAppliedProducerBuildMenu = 0;
        g_LastUnknownProducerVft = 0;

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

        g_BzrFn_ButtonCtor = reinterpret_cast<FnUiCtor>(0x007C2480);
        g_BzrFn_LabelCtor  = reinterpret_cast<FnUiCtor>(0x007CC390);
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
        if (!g_IsSteamExe)
        {
            g_BzrFn_InitBuildItem = reinterpret_cast<FnBuildItemInit>(0x0049F5C0);
            g_BzrFn_CleanupBuildItem = reinterpret_cast<FnBuildItemCleanup>(0x0049F880);
            g_BzrBuildMenuRoot = reinterpret_cast<BuildItem*>(kBuildMenuRootAddr);
        }

        g_EnableChunkRenderFallback =
            EnvFlagEnabled("BZR_CHUNK_FORCE_FIRST_GEO") ||
            EnvFlagEnabled("OPENSHIM_CHUNK_FORCE_FIRST_GEO");
        float turretAimPitchMultiplier = g_TurretAimPitchMultiplier;
        if (TryGetEnvFloat("OPENSHIM_TURRET_AIM_PITCH_MULTIPLIER", turretAimPitchMultiplier) ||
            TryGetEnvFloat("OPENSHIM_TURRET_PITCH_MULTIPLIER", turretAimPitchMultiplier))
        {
            g_TurretAimPitchMultiplier = ClampTurretAimPitchMultiplier(turretAimPitchMultiplier);
        }
        else
        {
            g_TurretAimPitchMultiplier = 0.95f;
        }
        Log(L"[CHUNK] Force-first-geo fallback: %hs\n",
            g_EnableChunkRenderFallback ? "enabled" : "disabled");
        Log(L"[TURRET] Aim pitch multiplier: %.3f%s\n",
            static_cast<double>(g_TurretAimPitchMultiplier),
            g_TurretAimPitchMultiplier >= 0.999f ? " (full range)" : "");
        Log(L"[PRODMENU] Builder bridge: %hs\n",
            (!g_IsSteamExe && g_BzrFn_InitBuildItem && g_BzrFn_CleanupBuildItem && g_BzrBuildMenuRoot)
                ? "GOG ready"
                : "disabled");
    }

    void InitBzrHookStrings()
    {
        BzrStringInitEmpty(&g_BzrnetLabel1);
        BzrStringInitEmpty(&g_BzrnetLabel2);
        BzrStringInitEmpty(&g_BzrnetLabel3);
        BzrStringInitEmpty(&g_BzrnetLabel4);
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
        constexpr size_t kWeaponIndexOffset = 0xAC;

        constexpr uint32_t kHowitzerVftPrimary = 0x0087AD70;
        constexpr uint32_t kHowitzerVftSecondary = 0x0087AE1C;
        constexpr uint32_t kMinelayerVftPrimary = 0x0087D790;
        constexpr uint32_t kMinelayerVftSecondary = 0x0087D83C;

        bool IsWeaponMaskCarrierBiasCraft(const void* craft)
        {
            if (!craft)
                return false;

            const uint32_t vft = *reinterpret_cast<const uint32_t*>(craft);
            return vft == kHowitzerVftPrimary ||
                vft == kHowitzerVftSecondary ||
                vft == kMinelayerVftPrimary ||
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
    }

    void __cdecl ApplyWeaponMaskCarrierBiasForCraft(void* craft)
    {
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

    static void AppendBanList(const char* id, const BzrString* name)
    {
        if (!id || !*id)
            return;
        FILE* f = nullptr;
        fopen_s(&f, "banlist.txt", "a");
        if (!f)
            return;

        if (name && name->size)
        {
            std::fprintf(f, "%s %.*s\n", id, static_cast<int>(name->size), BzrStringData(name));
        }
        else
        {
            std::fprintf(f, "%s\n", id);
        }
        std::fclose(f);
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
        auto* objectBytes = reinterpret_cast<uint8_t*>(objectPtr);
        auto* activeHandle = reinterpret_cast<void**>(objectBytes + 0x64);

        if (resolved != 0 && *activeHandle != nullptr)
            return resolved;

        if (!g_EnableChunkRenderFallback)
            return resolved;

        auto* lookup = reinterpret_cast<BzrGeoLookup*>(objectBytes + 0x68);
        if (!lookup || lookup->count == 0 || !lookup->entries)
            return resolved;

        for (uint32_t index = 0; index < lookup->count; ++index)
        {
            BzrGeoEntry& entry = lookup->entries[index];
            if (!entry.handle)
                continue;

            *activeHandle = entry.handle;
            lookup->cachedKey = entry.packedKey;

            if (InterlockedDecrement(&g_ChunkRenderLogBudget) >= 0)
            {
                const uint32_t renderClass =
                    *reinterpret_cast<uint32_t*>(objectBytes + 0x14) & 0xF000;
                const uint32_t objectType = *reinterpret_cast<uint32_t*>(objectBytes + 0x84);
                Log(L"[CHUNK] Forced geometry entry idx=%u key=0x%08X class=0x%04X type=0x%X count=%u obj=0x%08X\n",
                    index,
                    entry.packedKey,
                    renderClass,
                    objectType,
                    lookup->count,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectPtr)));
            }

            return 1;
        }

        return resolved;
    }

    void __cdecl MapFilterOnScrollUp()
    {
        if (g_MapFilterListPtr && g_BzrFn_MapFilterScrollUp)
            g_BzrFn_MapFilterScrollUp();
    }

    void __cdecl MapFilterOnScrollDown()
    {
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
        if (!g_BzrFn_EngineFlameAddFlame || !managerPtr || !transform)
            return;

        ApplyWeaponMaskCarrierBiasForCraft(craftPtr);

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

            uint8_t* entry = reinterpret_cast<uint8_t*>(g_BzrFn_BanLookup(id));
            if (!entry)
            {
                Log(L"[BAN] /ban failed: ban lookup returned null (id=%u)\n", id);
                return true;
            }

            int type = *reinterpret_cast<int*>(entry + 0x30);
            if (type != 1 && type != 2)
            {
                Log(L"[BAN] /ban failed: ban entry type invalid (id=%u)\n", id);
                return true;
            }

            const char prefix = (type == 1) ? 'S' : 'G';
            uint64_t uid = *reinterpret_cast<uint64_t*>(entry + 0x38);
            char idbuf[32] = {};
            std::snprintf(idbuf, sizeof(idbuf), "%c%llu", prefix, static_cast<unsigned long long>(uid));

            const auto* name = reinterpret_cast<const BzrString*>(entry + 0x74);
            AppendBanList(idbuf, name);
            Log(L"[BAN] /ban added %c%llu (%hs)\n", prefix, static_cast<unsigned long long>(uid),
                (name && name->size) ? BzrStringData(name) : "");
            return true;
        }

        return false;
    }

    void __cdecl BanButtonOnClickHost()
    {
        if (!g_BzrPtr_9456D0 || !g_BzrFn_GetSelected)
            return;

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
        AppendBanList(idbuf, &name);
        BzrStringFree(&name);
    }

    void __cdecl BanButtonOnClickClient()
    {
        if (!g_BzrPtr_94557C || !g_BzrFn_GetSelected || !g_BzrFn_CommandHandler)
            return;

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
        g_BzrFn_CommandHandler(id, "/ban");
        g_BzrFn_CommandHandler(id, "/kick");
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

    void __cdecl AutoSaveButtonOnClickLoad()
    {
        if (!g_BzrFn_LoadGameByPath || !g_BzrFn_FinalizeQueuedLoad || !g_BzrFn_SetShellState)
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
            auto* queuedName = reinterpret_cast<char*>(kQueuedLoadNameBufferAddr);
            const int result = g_BzrFn_LoadGameByPath(
                queuedPath,
                queuedName,
                kQueuedLoadNameBufferLen);
            Log(L"[AUTOSAVE] Queued auto-save load path=%hs result=%d name=%hs\n",
                queuedPath,
                result,
                queuedName);

            if (result)
            {
                g_BzrFn_FinalizeQueuedLoad();
                g_BzrFn_SetShellState(kLoadQueuedState);
            }
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

        if (g_AutoSaveLoadButton && g_AutoSaveLoadParent == parent && g_AutoSaveLoadScreen == screen)
            return;

        g_AutoSaveLoadParent = parent;
        g_AutoSaveLoadScreen = screen;
        g_AutoSaveLoadButton = nullptr;

        void* buttonMem = ::operator new(0x1EC, std::nothrow);
        if (!buttonMem)
            return;

        std::memset(buttonMem, 0, 0x1EC);
        g_AutoSaveLoadButton = g_BzrFn_ButtonCtor(
            buttonMem,
            "AutoSave",
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
        if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(g_AutoSaveLoadButton, "AutoSave");
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

    void BanButtonCreateHost()
    {
        if (!g_BzrFn_ButtonCtor || !g_BzrFn_LabelCtor || !g_BzrFn_AddChild || !g_BanParentHost)
            return;

        void* parent = g_BanParentHost;

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
            0,
            0);

        if (g_BanLabelHost)
        {
            if (g_BzrFn_SetTooltip) g_BzrFn_SetTooltip(g_BanLabelHost, "Ban highlighted player");
            if (g_BzrFn_LabelState) g_BzrFn_LabelState(g_BanLabelHost, nullptr);
            g_BzrFn_AddChild(parent, g_BanLabelHost, 0);
        }
    }

    void BanButtonCreateClient()
    {
        if (!g_BzrFn_ButtonCtor || !g_BzrFn_LabelCtor || !g_BzrFn_AddChild || !g_BanParentClient)
            return;

        void* parent = g_BanParentClient;

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
            0,
            0);

        if (g_BanLabelClient)
        {
            if (g_BzrFn_SetTooltip) g_BzrFn_SetTooltip(g_BanLabelClient, "Ban highlighted player");
            if (g_BzrFn_LabelState) g_BzrFn_LabelState(g_BanLabelClient, nullptr);
            g_BzrFn_AddChild(parent, g_BanLabelClient, 0);
        }
    }
}
