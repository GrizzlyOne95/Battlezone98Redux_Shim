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

        // --- Engine state (bzr_hooks.cpp) ------------------------------------
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
        // GameObject::GetTeam (0x00462450), which makes an exact pointer
        // compare a positive identification rather than a heuristic, and
        // rejects abstract/_purecall tables and foreign objects alike.
        inline constexpr uintptr_t kGogGameObjectGetTeamAddr = 0x00462450;
        inline constexpr uintptr_t kGogPreferredImageBase = 0x00400000;
        bool IsLikelyGameObjectEntry(void* objectPtr);
        bool IsReadableDataProtect(DWORD protect);
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
        inline constexpr uintptr_t kQueuedLoadPathBufferAddr = 0x00945708;
        inline constexpr uintptr_t kQueuedLoadNameBufferAddr = 0x00915540;
        inline constexpr uintptr_t kNetPlayerByTeamAddr = 0x009180E8;
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
