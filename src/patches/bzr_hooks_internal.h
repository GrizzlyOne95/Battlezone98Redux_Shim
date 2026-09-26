#pragma once
// bzr_hooks_internal.h
// BZR Open Shim - what the translation units split out of bzr_hooks.cpp
// share with it: Ogre ABI types and the helpers each one calls. Everything
// here lives in BZROpenShim::Hooks (formerly bzr_hooks.cpp's anonymous
// namespace). Not a public interface; keep it to what a split-out file needs.
#include <Windows.h>

#include <cstddef>
#include <cstdint>
#include <string>

namespace BZROpenShim
{
    // Set by ResolveBzrHooks from its isSteam argument.
    extern bool g_IsSteamExe;

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
        uint16_t ReadLocalPlayerNetIdValue();

        // --- Engine state (bzr_hooks.cpp) ------------------------------------
        uintptr_t GetMainModuleBase();
        bool IsExuModuleLoaded();
        // True once the SetRunning mission seam is hooked; its enter/exit
        // callbacks then drive the per-world baseline resets.
        extern bool g_MissionSeamInstalled;
        inline constexpr size_t kGameObjectArenaSlotCapacity = 4096;

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
