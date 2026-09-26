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

#include "bzr_hooks.h"
#include "bzr_object_layout.h"

namespace BZROpenShim
{
    // Set by ResolveBzrHooks from its isSteam argument.
    extern bool g_IsSteamExe;
    // GameObject::GetHandle, resolved by ResolveBzrHooks from patches.json;
    // 0 until then, and every caller stands down on 0.
    extern uintptr_t g_GameObjectGetHandleAddr;
    using FnPlayGlobalSound = int(__cdecl*)(const char* filename, uint32_t arg1, uint32_t arg2, uint32_t arg3);

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
