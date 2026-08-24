#include "terrain_proxy.h"

#include "terrain_semantic.h"

#include "bzr_hooks.h"
#include "bzr_options_ui.h"
#include "shim_log.h"
#include <nlohmann/json.hpp>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <bcrypt.h>
#include <d3d11.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <map>
#include <mutex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kExpectedExeSha256[] =
            "8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413";
        constexpr char kExpectedOgreSha256[] =
            "E5E693960B95AD0D60733A3B688464A6C6CBA234E86950698F9C2BEA4ACFEB45";
        constexpr uintptr_t kPreferredImageBase = 0x00400000;
        constexpr uintptr_t kZoneConstructVa = 0x007778B0;
        constexpr uintptr_t kZoneProcessVa = 0x00778450;
        constexpr uintptr_t kTerrainWordAtVa = 0x004C0FE0;
        constexpr uintptr_t kHeightAtVa = 0x0077D640;
        constexpr uintptr_t kAtlasRectAtVa = 0x0050CE10;
        constexpr uintptr_t kTerrainManagerVa = 0x0077C670;
        constexpr uintptr_t kTileIndexAtVa = 0x00780DC0;
        constexpr uintptr_t kMixAtVa = 0x00780E40;
        constexpr uintptr_t kTerrainOriginXVa = 0x02CE99C0;
        constexpr uintptr_t kTerrainOriginZVa = 0x02CD9984;
        // Redux's mission-run state machine. FUN_00434170 is
        // `void __cdecl SetRunning(int)`: it stores the new state in
        // kRunStateVa (unless the state is already RUN_WAS_EXITED, which is
        // sticky) and logs "SetRunning: was %s, now %s" using a table of
        // eleven name pointers at kRunStateNameTableVa. This is the only
        // mission-lifetime boundary Redux crosses in-process: it never calls
        // SceneManager::clearScene or destroyAllMovableObjects.
        constexpr uintptr_t kSetRunningVa = 0x00434170;
        constexpr uintptr_t kRunStateVa = 0x008E706C;
        constexpr uintptr_t kRunStateNameTableVa = 0x00871690;
        constexpr int kRunStateNameCount = 11;
        constexpr int kRunStateStarted = 5;
        constexpr int kRunStateUnknown = -1;
        constexpr char kRunStateStartedName[] = "RUN_STARTED";

        constexpr size_t kZoneMeshPtrBase = 0x000;
        constexpr size_t kZoneNodeBase = 0x080;
        constexpr size_t kZoneEntityBase = 0x0C0;
        constexpr size_t kZoneXOffset = 0x240;
        constexpr size_t kZoneZOffset = 0x244;
        constexpr size_t kHeightDirtyOffset = 0x250;
        constexpr size_t kHeightDirtyNextOffset = 0x260;
        constexpr size_t kFullDirtyOffset = 0x270;
        constexpr size_t kClusterXStride = 0x20;
        constexpr size_t kClusterZStride = 0x08;
        constexpr uint32_t kExpectedVertices = 9409;
        constexpr uint32_t kExpectedIndices = 38400;
        constexpr int kClusterAxisCount = 4;
        // TerrainSemanticDebug selectors. 0 keeps stock shading.
        constexpr int kSemanticDebugTileIndex = 1;
        constexpr int kSemanticDebugOrientation = 2;
        constexpr int kSemanticDebugTypeA = 3;
        constexpr int kSemanticDebugTypeB = 4;
        constexpr int kSemanticDebugLocalUv = 5;
        constexpr int kSemanticDebugAtlasRect = 6;
        constexpr int kSemanticDebugUvDelta = 7;
        constexpr int kSemanticDebugModeMaximum = kSemanticDebugUvDelta;
        constexpr int kOgreTextureType2D = 2;
        constexpr int kOgreTextureType2DArray = 5;
        constexpr int kOgreTextureUsageStaticWriteOnly = 5;
        constexpr int kOgreMipDefault = -1;
        constexpr int kOgrePixelFormatUnknown = 0;

        const char* SemanticDebugModeName(int mode)
        {
            switch (mode)
            {
            case kSemanticDebugTileIndex: return "tileIndex";
            case kSemanticDebugOrientation: return "orientation";
            case kSemanticDebugTypeA: return "typeA";
            case kSemanticDebugTypeB: return "typeB";
            case kSemanticDebugLocalUv: return "localUV";
            case kSemanticDebugAtlasRect: return "atlasRect";
            case kSemanticDebugUvDelta: return "uvDelta";
            default: return "off";
            }
        }

        struct Vector3
        {
            float x;
            float y;
            float z;
        };

        struct Quaternion
        {
            float w;
            float x;
            float y;
            float z;
        };

        struct AxisAlignedBox
        {
            Vector3 minimum;
            Vector3 maximum;
            int extent;
        };

        // Ogre::Matrix4 is row-major float[4][4]; m[row][column]. Only used to
        // project the proxy's world bounds into viewport pixels for the
        // capture-framing diagnostic, never to drive rendering.
        struct Matrix4
        {
            float m[4][4];
        };

        // Screen-space answer for one proxy/camera pair. `visible` is Ogre's
        // own frustum test; the rect is the screen bounding box of the eight
        // projected world-AABB corners, clamped to the viewport.
        struct ProxyScreenRect
        {
            bool valid = false;
            bool visible = false;
            int viewportWidth = 0;
            int viewportHeight = 0;
            int left = 0;
            int top = 0;
            int right = 0;
            int bottom = 0;
            int cornersInFront = 0;
            float coverage = 0.0f;
        };

        struct OgreBox
        {
            uint32_t left;
            uint32_t top;
            uint32_t right;
            uint32_t bottom;
            uint32_t front;
            uint32_t back;
        };

        struct OgreSharedPtr
        {
            void* rep = nullptr;
            void* info = nullptr;
        };

        struct VertexDataPrefix
        {
            void* manager;
            void* declaration;
            void* binding;
            uint8_t deleteDeclarationAndBinding;
            uint8_t padding0D[3];
            uint32_t vertexStart;
            uint32_t vertexCount;
        };

        struct IndexDataPrefix
        {
            OgreSharedPtr indexBuffer;
            uint32_t indexStart;
            uint32_t indexCount;
        };

        struct RenderOperation
        {
            VertexDataPrefix* vertexData;
            int operationType;
            uint8_t useIndexes;
            uint8_t padding09[3];
            IndexDataPrefix* indexData;
            const void* sourceRenderable;
            uint32_t numberOfInstances;
            uint8_t renderToVertexBuffer;
            uint8_t globalInstancingAvailable;
            uint8_t padding1A[2];
        };

        struct AtlasRect
        {
            float u;
            float v;
            float w;
            float h;
        };

        static_assert(sizeof(OgreSharedPtr) == 8, "Redux Ogre SharedPtr ABI changed");
        static_assert(sizeof(VertexDataPrefix) == 24, "Redux Ogre VertexData ABI changed");
        static_assert(sizeof(IndexDataPrefix) == 16, "Redux Ogre IndexData ABI changed");
        static_assert(sizeof(RenderOperation) == 28, "Redux Ogre RenderOperation ABI changed");
        static_assert(sizeof(AxisAlignedBox) == 28, "Redux Ogre AxisAlignedBox ABI changed");
        static_assert(sizeof(Matrix4) == 64, "Redux Ogre Matrix4 ABI changed");

        struct TerrainConfig
        {
            bool proxyEnabled = false;
            bool proxyVisible = true;
            bool semanticCapture = false;
            bool semanticDumpJson = true;
            bool semanticRenderer = false;
            bool semanticValidateUv = false;
            bool semanticLegacyUvQuantization = true;
            bool semanticDumpMismatches = false;
            bool semanticLifecycleLog = false;
            int semanticDebugMode = 0;
            int semanticFrameCaptures = 0;
            int semanticFrameCaptureStride = 300;
            // A capture that does not contain the cluster answers nothing, so
            // the default is to wait for a framed one rather than spend the
            // capture slot. Set to 0 for the old fixed-frame-index behaviour.
            bool semanticFrameCaptureRequireOnScreen = true;
            // 0.02 was guessed and proved too strict: on the live build no
            // cluster exceeded 0.0164 of a 3840x2160 viewport, because terrain
            // is seen at a grazing angle and projects to a thin band. A band of
            // ~500x250 px is entirely measurable.
            float semanticFrameCaptureMinCoverage = 0.005f;
            bool followCamera = false;
            // How far ahead of the eye the aim point is pushed, in world units.
            float followCameraAimDistance = 35.0f;
            // Re-choose the cluster when the proxy has gone this many rendered
            // frames without being framed. 0 disables re-selection.
            int followCameraReselectFrames = 300;
            bool hdEnabled = false;
            std::string hdManifest = "terrain_hd_tiles.json";
            int zoneOrdinal = -1;
            int clusterOrdinal = -1;
            int zoneX = INT_MIN;
            int zoneZ = INT_MIN;
            int clusterX = INT_MIN;
            int clusterZ = INT_MIN;
            Vector3 offset = {};
        };

        struct ProxyState
        {
            bool selected = false;
            bool proxyCreated = false;
            bool tearingDown = false;
            void* zone = nullptr;
            void* sceneManager = nullptr;
            void* sourceMesh = nullptr;
            void* sourceEntity = nullptr;
            void* sourceNode = nullptr;
            void* proxyMesh = nullptr;
            void* proxyEntity = nullptr;
            void* proxyNode = nullptr;
            int zoneOrdinal = -1;
            int zoneX = 0;
            int zoneZ = 0;
            int clusterOrdinal = -1;
            int clusterX = 0;
            int clusterZ = 0;
            uint32_t semanticHash = 0;
            uint32_t heightHash = 0;
            uint16_t heightMinimum = 0;
            uint16_t heightMaximum = 0;
            uint32_t generation = 0;
            uint32_t rebuildCount = 0;
            uint32_t heightRefreshCount = 0;
            uint32_t fullRefreshCount = 0;
            std::string sourceMeshName;
            std::string proxyMeshName;
            std::string proxyEntityName;
            std::string proxyNodeName;
            std::string materialName;
            std::string semanticMaterialName;
            std::vector<std::string> semanticProgramNames;
            bool semanticStreamInstalled = false;
            bool semanticMaterialInstalled = false;
            bool semanticMaterialUnsupported = false;
            // Stable identities so lifecycle records never depend on an
            // allocator address that can be recycled by a later mission.
            uint32_t semanticVbGeneration = 0;
            uint32_t semanticMaterialGeneration = 0;
            void* semanticBuffer = nullptr;
            uint32_t semanticDataHash = 0;
            uint32_t semanticBuildCount = 0;
            uint32_t semanticUploadCount = 0;
            uint32_t semanticUnchangedCount = 0;
            uint32_t semanticBindingSignature = 0;
            uint32_t heightUpdateLogCount = 0;
            size_t semanticProgramsCreated = 0;
            size_t semanticProgramsReused = 0;
            size_t semanticPassesSpecialized = 0;
            size_t semanticPassesSeen = 0;
            size_t semanticFragmentProgramsCreated = 0;
            std::vector<TerrainSemantic::Vertex> semanticVertices;
            std::string hdTextureName;
            std::string hdDiffuseFallback;
            uint32_t hdSliceCount = 0;
            uint32_t hdWidth = 0;
            uint32_t hdHeight = 0;
            uint32_t hdMipmaps = 0;
        };

        struct TerrainHdMaterialBinding
        {
            uint32_t sliceCount = 0;
            std::string fallback;
            std::unordered_map<uint32_t, std::string> tiles;
        };

        struct TerrainHdManifest
        {
            std::filesystem::path path;
            std::unordered_map<std::string, TerrainHdMaterialBinding> materials;
            bool loaded = false;
        };

        // Although the decompiler labels this as void, the placement-new
        // caller consumes EAX and stores it in the manager's zone table.
        // Preserve the native constructor's machine-level `this` return.
        using FnZoneConstruct = void* (__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t);
        using FnZoneProcess = void(__thiscall*)(void*);
        using FnMeshClone = OgreSharedPtr* (__thiscall*)(
            void*, OgreSharedPtr*, const std::string&, const std::string&);
        using FnCreateEntityFromMesh = void* (__thiscall*)(
            void*, const std::string&, const OgreSharedPtr&);
        using FnGetResourceName = const std::string* (__thiscall*)(void*);
        using FnGetNumSubMeshes = uint16_t(__thiscall*)(void*);
        using FnGetSubEntity = void* (__thiscall*)(void*, uint32_t);
        using FnGetRenderOperation = void(__thiscall*)(void*, RenderOperation&);
        using FnGetMaterialName = const std::string* (__thiscall*)(void*);
        using FnSetMaterialName = void(__thiscall*)(void*, const std::string&, const std::string&);
        using FnGetBuffer = const OgreSharedPtr* (__thiscall*)(void*, uint16_t);
        using FnGetVertexSize = uint32_t(__thiscall*)(void*);
        using FnGetNumVertices = uint32_t(__thiscall*)(void*);
        using FnGetIndexSize = uint32_t(__thiscall*)(void*);
        using FnGetNumIndexes = uint32_t(__thiscall*)(void*);
        using FnGetBufferSize = uint32_t(__thiscall*)(void*);
        using FnCopyBufferData = void(__thiscall*)(void*, void*);
        using FnLockBuffer = void* (__thiscall*)(void*, uint32_t, uint32_t, int, int);
        using FnUnlockBuffer = void(__thiscall*)(void*);
        using FnGetD3D11VertexBuffer = ID3D11Buffer* (__thiscall*)(void*);
        using FnGetParentSceneNode = void* (__thiscall*)(void*);
        using FnGetVector3 = const Vector3* (__thiscall*)(void*);
        using FnGetQuaternion = const Quaternion* (__thiscall*)(void*);
        using FnCreateChildSceneNode = void* (__thiscall*)(
            void*, const std::string&, const Vector3&, const Quaternion&);
        using FnSetNodeScale = void(__thiscall*)(void*, const Vector3&);
        using FnAttachObject = void(__thiscall*)(void*, void*);
        using FnSetVisible = void(__thiscall*)(void*, bool);
        using FnSetCastShadows = void(__thiscall*)(void*, bool);
        using FnSetRenderQueueGroup = void(__thiscall*)(void*, uint8_t);
        using FnDestroySceneNode = void(__thiscall*)(void*, void*);
        using FnDestroyByName = void(__thiscall*)(void*, const std::string&);
        using FnHasByName = bool(__thiscall*)(void*, const std::string&);
        using FnGetBounds = const AxisAlignedBox* (__thiscall*)(void*);
        using FnSetBounds = void(__thiscall*)(void*, const AxisAlignedBox&, bool);
        using FnGetRadius = float(__thiscall*)(void*);
        using FnSetRadius = void(__thiscall*)(void*, float);
        using FnGetSingleton = void* (__cdecl*)();
        using FnCreateVertexBuffer = OgreSharedPtr* (__thiscall*)(
            void*, OgreSharedPtr*, uint32_t, uint32_t, int, bool);
        using FnAddVertexElement = const void* (__thiscall*)(
            void*, uint16_t, uint32_t, int, int, uint16_t);
        using FnSetVertexBinding = void(__thiscall*)(
            void*, uint16_t, const OgreSharedPtr&);
        using FnGetMaterialByName = OgreSharedPtr* (__thiscall*)(
            void*, OgreSharedPtr*, const std::string&, const std::string&);
        using FnCloneMaterial = OgreSharedPtr* (__thiscall*)(
            void*, OgreSharedPtr*, const std::string&, bool, const std::string&);
        using FnGetNumTechniques = uint16_t(__thiscall*)(void*);
        using FnGetTechnique = void* (__thiscall*)(void*, uint16_t);
        using FnGetNumPasses = uint16_t(__thiscall*)(void*);
        using FnGetPass = void* (__thiscall*)(void*, uint16_t);
        using FnGetGpuProgram = const OgreSharedPtr* (__thiscall*)(void*);
        using FnGetUnifiedDelegate = const OgreSharedPtr* (__thiscall*)(void*);
        using FnGetGpuProgramParameters = OgreSharedPtr* (__thiscall*)(
            void*, OgreSharedPtr*);
        using FnSetVertexProgram = void(__thiscall*)(
            void*, const std::string&, bool);
        using FnSetVertexProgramParameters = void(__thiscall*)(
            void*, OgreSharedPtr);
        using FnGetStringReference = const std::string* (__thiscall*)(void*);
        using FnGetStringParameter = std::string* (__thiscall*)(
            void*, std::string*, const std::string&);
        using FnCreateHighLevelProgram = OgreSharedPtr* (__thiscall*)(
            void*, OgreSharedPtr*, const std::string&, const std::string&,
            const std::string&, int);
        using FnSetProgramSource = void(__thiscall*)(void*, const std::string&);
        using FnSetStringParameter = bool(__thiscall*)(
            void*, const std::string&, const std::string&);
        using FnLoadResource = void(__thiscall*)(void*, bool);
        using FnGetMeshManager = void* (__cdecl*)();
        using FnRemoveResource = void(__thiscall*)(void*, const std::string&);
        using FnTerrainWordAt = uint16_t* (__cdecl*)(int, int);
        using FnHeightAt = uint16_t(__cdecl*)(int, int);
        using FnTerrainManager = void* (__cdecl*)();
        using FnAtlasRectAt = const AtlasRect* (__thiscall*)(void*, uint32_t);
        using FnTileIndexAt = uint8_t(__cdecl*)(int, int);
        using FnMixAt = int(__cdecl*)(int, int);
        using FnGetAutoCreatedWindow = void* (__thiscall*)(void*);
        using FnWriteContentsToFile = void(__thiscall*)(void*, const std::string&);
        using FnFindElementBySemantic = const void* (__thiscall*)(
            void*, int, uint16_t);
        using FnGetElementUShort = uint16_t(__thiscall*)(const void*);
        using FnGetElementInt = int(__thiscall*)(const void*);
        using FnGetElementUInt = uint32_t(__thiscall*)(const void*);
        using FnGetNumTextureUnitStates = uint16_t(__thiscall*)(void*);
        using FnGetTextureUnitState = void* (__thiscall*)(void*, uint16_t);
        using FnSetTexture = void(__thiscall*)(void*, const OgreSharedPtr&);
        using FnGetTextureManager = void* (__cdecl*)();
        using FnLoadTexture = OgreSharedPtr* (__thiscall*)(
            void*, OgreSharedPtr*, const std::string&, const std::string&,
            int, int, float, bool, int, bool);
        using FnCreateManualTexture = OgreSharedPtr* (__thiscall*)(
            void*, OgreSharedPtr*, const std::string&, const std::string&,
            int, uint32_t, uint32_t, uint32_t, int, int, int, void*, bool,
            uint32_t, const std::string&);
        using FnGetTextureUInt = uint32_t(__thiscall*)(void*);
        using FnGetTextureByte = uint8_t(__thiscall*)(void*);
        using FnGetTextureInt = int(__thiscall*)(void*);
        using FnGetTextureBuffer = OgreSharedPtr* (__thiscall*)(
            void*, OgreSharedPtr*, uint32_t, uint32_t);
        using FnBlitPixelBuffer = void(__thiscall*)(
            void*, const OgreSharedPtr&, const OgreBox&, const OgreBox&);
        using FnGetViewport = void* (__thiscall*)(void*, uint16_t);
        using FnGetViewportCamera = void* (__thiscall*)(void*);
        using FnGetViewportInt = int(__thiscall*)(void*);
        using FnGetMatrix4 = const Matrix4* (__thiscall*)(void*);
        // Ogre::Camera::isVisible(const AxisAlignedBox&, FrustumPlane*). The
        // culling-plane out-parameter is always passed null here.
        using FnCameraBoxVisible = bool(__thiscall*)(void*, const AxisAlignedBox&, int*);
        using FnGetWorldBoundingBox = const AxisAlignedBox* (__thiscall*)(void*, bool);
        using FnGetDerivedPosition = const Vector3* (__thiscall*)(void*);

        struct OgreApi
        {
            FnMeshClone cloneMesh = nullptr;
            FnCreateEntityFromMesh createEntity = nullptr;
            FnGetResourceName getResourceName = nullptr;
            FnGetNumSubMeshes getNumSubMeshes = nullptr;
            FnGetSubEntity getSubEntity = nullptr;
            FnGetRenderOperation getRenderOperation = nullptr;
            FnGetMaterialName getMaterialName = nullptr;
            FnSetMaterialName setMaterialName = nullptr;
            FnGetBuffer getBuffer = nullptr;
            FnGetVertexSize getVertexSize = nullptr;
            FnGetNumVertices getNumVertices = nullptr;
            FnGetIndexSize getIndexSize = nullptr;
            FnGetNumIndexes getNumIndexes = nullptr;
            FnGetBufferSize getBufferSize = nullptr;
            FnCopyBufferData copyBufferData = nullptr;
            FnLockBuffer lockBuffer = nullptr;
            FnUnlockBuffer unlockBuffer = nullptr;
            FnGetD3D11VertexBuffer getD3D11VertexBuffer = nullptr;
            FnGetParentSceneNode getParentSceneNode = nullptr;
            FnGetVector3 getNodePosition = nullptr;
            FnGetQuaternion getNodeOrientation = nullptr;
            FnGetVector3 getNodeScale = nullptr;
            FnCreateChildSceneNode createChildSceneNode = nullptr;
            FnSetNodeScale setNodeScale = nullptr;
            FnAttachObject attachObject = nullptr;
            FnSetVisible setVisible = nullptr;
            FnSetCastShadows setCastShadows = nullptr;
            FnSetRenderQueueGroup setRenderQueueGroup = nullptr;
            FnDestroySceneNode destroySceneNode = nullptr;
            // Name-based scene teardown/probe. Pointer-based destruction is
            // deliberately unused: the engine can destroy the proxy Entity
            // between missions, and a stored pointer cannot be tested for that.
            FnDestroyByName destroyEntityByName = nullptr;
            FnDestroyByName destroySceneNodeByName = nullptr;
            FnHasByName hasEntityByName = nullptr;
            FnHasByName hasSceneNodeByName = nullptr;
            FnGetBounds getBounds = nullptr;
            FnSetBounds setBounds = nullptr;
            FnGetRadius getRadius = nullptr;
            FnSetRadius setRadius = nullptr;
            FnGetSingleton getHardwareBufferManager = nullptr;
            FnCreateVertexBuffer createVertexBuffer = nullptr;
            FnAddVertexElement addVertexElement = nullptr;
            FnSetVertexBinding setVertexBinding = nullptr;
            FnGetSingleton getMaterialManager = nullptr;
            FnGetMaterialByName getMaterialByName = nullptr;
            FnCloneMaterial cloneMaterial = nullptr;
            FnGetNumTechniques getNumTechniques = nullptr;
            FnGetTechnique getTechnique = nullptr;
            FnGetNumPasses getNumPasses = nullptr;
            FnGetPass getPass = nullptr;
            FnGetGpuProgram getVertexProgram = nullptr;
            FnGetUnifiedDelegate getUnifiedDelegate = nullptr;
            FnGetGpuProgramParameters getVertexProgramParameters = nullptr;
            FnSetVertexProgram setVertexProgram = nullptr;
            FnSetVertexProgramParameters setVertexProgramParameters = nullptr;
            FnGetStringReference getProgramSource = nullptr;
            FnGetStringParameter getStringParameter = nullptr;
            FnGetSingleton getHighLevelProgramManager = nullptr;
            FnCreateHighLevelProgram createHighLevelProgram = nullptr;
            FnSetProgramSource setProgramSource = nullptr;
            FnSetStringParameter setStringParameter = nullptr;
            FnLoadResource loadResource = nullptr;
            FnGetMeshManager getMeshManager = nullptr;
            FnRemoveResource removeResource = nullptr;
            // Optional: only the semantic debug visualization and the
            // slot-3 declaration audit use these. An unresolved entry
            // degrades that diagnostic; it never disables Phase 2/3A.
            FnGetGpuProgram getFragmentProgram = nullptr;
            FnGetGpuProgramParameters getFragmentProgramParameters = nullptr;
            FnSetVertexProgram setFragmentProgram = nullptr;
            FnSetVertexProgramParameters setFragmentProgramParameters = nullptr;
            FnGetSingleton getRoot = nullptr;
            FnGetAutoCreatedWindow getAutoCreatedWindow = nullptr;
            FnWriteContentsToFile writeContentsToFile = nullptr;
            FnFindElementBySemantic findElementBySemantic = nullptr;
            FnGetElementUShort getElementSource = nullptr;
            FnGetElementInt getElementType = nullptr;
            FnGetElementUInt getElementOffset = nullptr;
            // Optional Phase 3B smoke-path APIs. Their absence disables only
            // TerrainHdEnabled and leaves the Phase 3A stock-atlas path intact.
            FnGetNumTextureUnitStates getNumTextureUnitStates = nullptr;
            FnGetTextureUnitState getTextureUnitState = nullptr;
            FnSetTexture setTexture = nullptr;
            FnGetTextureManager getTextureManager = nullptr;
            FnLoadTexture loadTexture = nullptr;
            FnCreateManualTexture createManualTexture = nullptr;
            FnGetTextureUInt getTextureWidth = nullptr;
            FnGetTextureUInt getTextureHeight = nullptr;
            FnGetTextureUInt getTextureDepth = nullptr;
            FnGetTextureByte getTextureMipmaps = nullptr;
            FnGetTextureInt getTextureType = nullptr;
            FnGetTextureInt getTextureFormat = nullptr;
            FnGetTextureBuffer getTextureBuffer = nullptr;
            FnBlitPixelBuffer blitPixelBuffer = nullptr;
            // Optional capture-framing APIs. Their absence disables only the
            // screen-rect diagnostic and the camera-aware selection mode; the
            // Phase 2/3A/3B render paths never depend on them.
            FnGetViewport getViewport = nullptr;
            FnGetViewportCamera getViewportCamera = nullptr;
            FnGetViewportInt getViewportWidth = nullptr;
            FnGetViewportInt getViewportHeight = nullptr;
            FnGetMatrix4 getViewMatrix = nullptr;
            FnGetMatrix4 getProjectionMatrix = nullptr;
            FnCameraBoxVisible cameraBoxVisible = nullptr;
            FnGetWorldBoundingBox getWorldBoundingBox = nullptr;
            FnGetDerivedPosition getCameraDerivedPosition = nullptr;
            FnGetQuaternion getCameraDerivedOrientation = nullptr;
        };

        TerrainConfig g_config;
        ProxyState g_proxy;
        OgreApi g_ogre;
        TerrainHdManifest g_hdManifest;
        InlineDetour32 g_zoneConstructDetour;
        InlineDetour32 g_zoneProcessDetour;
        FnZoneConstruct g_originalZoneConstruct = nullptr;
        FnZoneProcess g_originalZoneProcess = nullptr;
        FnTerrainWordAt g_terrainWordAt = nullptr;
        FnHeightAt g_heightAt = nullptr;
        FnTerrainManager g_terrainManager = nullptr;
        FnAtlasRectAt g_atlasRectAt = nullptr;
        FnTileIndexAt g_tileIndexAt = nullptr;
        FnMixAt g_mixAt = nullptr;
        uintptr_t g_mainBase = 0;
        std::atomic<bool> g_active{ false };
        std::atomic<bool> g_shutdown{ false };
        HANDLE g_worker = nullptr;
        std::mutex g_mutex;
        std::unordered_map<void*, int> g_zoneOrdinals;
        int g_nextZoneOrdinal = 0;
        uint32_t g_resourceSerial = 0;
        // Process-lifetime semantic identity/accounting. These deliberately
        // survive ResetSelectedState so an A -> B -> A mission sequence can be
        // shown to create and release matching numbers of resources instead of
        // accumulating them.
        uint32_t g_semanticVbSerial = 0;
        uint32_t g_semanticMaterialSerial = 0;
        uint32_t g_semanticVbCreated = 0;
        uint32_t g_semanticVbReleased = 0;
        uint32_t g_semanticVbHandoffRetained = 0;
        uint32_t g_semanticMaterialCreated = 0;
        uint32_t g_semanticMaterialRemoved = 0;
        uint32_t g_semanticProgramsCreatedTotal = 0;
        uint32_t g_semanticProgramsRemovedTotal = 0;
        uint32_t g_zoneDispatchCount = 0;
        std::atomic<uint32_t> g_nullZoneDispatchCount{ 0 };
        int g_teardownDepth = 0;
        bool g_teardownIncludesClear = false;
        // Mission lifecycle. Process-lifetime by design: missionGeneration and
        // the forget accounting have to keep increasing across A -> B -> A so
        // stale-generation activity is detectable in the log.
        uint32_t g_missionGeneration = 0;
        uint32_t g_missionForgetCount = 0;
        uint32_t g_missionForgetNoopCount = 0;
        uint32_t g_sceneTeardownObservations = 0;
        int g_lastRunState = kRunStateUnknown;
        bool g_runStateHookInstalled = false;

        uint32_t g_proxyLostCount = 0;
        // Render-tick probe: how many frames observed the proxy entity
        // unregistered (see QueryProxyScreenRect).
        uint32_t g_proxyTickProbeLostCount = 0;
        // Retry-path source verification: how many selections were forgotten
        // because the live zone table no longer advertised the stored source
        // objects.
        uint32_t g_sourceMismatchForgetCount = 0;
        // Discovery gate. Without it the zone dispatcher immediately re-selects
        // the outgoing mission's still-live zone after a transition forget and
        // builds a complete proxy -- entity, mesh, slot-3 buffer, material and
        // 13 programs -- that the engine then destroys when the map actually
        // changes. The first full A -> B -> A trace showed exactly that: six
        // proxy generations for three missions, every even one pure churn.
        bool g_discoveryArmed = false;

        enum class TerrainForgetReason
        {
            MissionTransition,
            SceneTeardown,
            ProcessShutdown,
            ProxyLost,
            FramingStale,
            SourceMismatch,
        };

        const char* ForgetReasonName(TerrainForgetReason reason)
        {
            switch (reason)
            {
            case TerrainForgetReason::MissionTransition: return "mission_transition";
            case TerrainForgetReason::SceneTeardown: return "scene_teardown";
            case TerrainForgetReason::ProcessShutdown: return "process_shutdown";
            case TerrainForgetReason::ProxyLost: return "proxy_lost";
            case TerrainForgetReason::FramingStale: return "framing_stale";
            case TerrainForgetReason::SourceMismatch: return "source_mismatch";
            default: return "unknown";
            }
        }

        uintptr_t Rebase(uintptr_t preferredVa)
        {
            return g_mainBase + (preferredVa - kPreferredImageBase);
        }

        bool IsEnvEnabled(const char* name)
        {
            char value[16] = {};
            const DWORD length = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
            return length > 0 && length < sizeof(value) && value[0] != '0';
        }

        bool ReadEnvInt(const char* name, int& value)
        {
            char text[16] = {};
            const DWORD length = GetEnvironmentVariableA(
                name, text, static_cast<DWORD>(sizeof(text)));
            if (length == 0 || length >= sizeof(text))
                return false;
            char* end = nullptr;
            const long parsed = std::strtol(text, &end, 10);
            if (end == text || *end != '\0')
                return false;
            value = static_cast<int>(parsed);
            return true;
        }

        bool ReadEnvFloat(const char* name, float& value)
        {
            char text[64] = {};
            const DWORD length = GetEnvironmentVariableA(
                name, text, static_cast<DWORD>(sizeof(text)));
            if (length == 0 || length >= sizeof(text))
                return false;
            char* end = nullptr;
            const float parsed = std::strtof(text, &end);
            if (end == text || *end != '\0')
                return false;
            value = parsed;
            return true;
        }

        std::filesystem::path GetIniPath()
        {
            wchar_t path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameW(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return {};
            return std::filesystem::path(path).parent_path() / L"openshim.ini";
        }

        float ReadIniFloat(const wchar_t* path, const char* key, float fallback)
        {
            char value[64] = {};
            char fallbackText[64] = {};
            sprintf_s(fallbackText, "%.9g", static_cast<double>(fallback));
            GetPrivateProfileStringA(
                "Terrain", key, fallbackText, value, static_cast<DWORD>(sizeof(value)),
                std::filesystem::path(path).string().c_str());
            char* end = nullptr;
            const float parsed = std::strtof(value, &end);
            return end != value && *end == '\0' ? parsed : fallback;
        }

        std::string ReadIniString(const std::string& iniPath,
                                  const char* key,
                                  const char* fallback)
        {
            std::array<char, 1024> value = {};
            GetPrivateProfileStringA("Terrain", key, fallback, value.data(),
                static_cast<DWORD>(value.size()), iniPath.c_str());
            return value.data();
        }

        bool ReadEnvString(const char* name, std::string& value)
        {
            std::array<char, 4096> text = {};
            const DWORD length = GetEnvironmentVariableA(
                name, text.data(), static_cast<DWORD>(text.size()));
            if (length == 0 || length >= text.size())
                return false;
            value.assign(text.data(), length);
            return true;
        }

        TerrainConfig ReadConfig()
        {
            TerrainConfig config;
            const std::filesystem::path ini = GetIniPath();
            const std::string iniText = ini.string();
            config.proxyEnabled = GetPrivateProfileIntA("Terrain", "TerrainProxyEnabled", 0, iniText.c_str()) != 0;
            config.proxyVisible = GetPrivateProfileIntA("Terrain", "TerrainProxyVisible", 1, iniText.c_str()) != 0;
            config.semanticCapture = GetPrivateProfileIntA("Terrain", "TerrainSemanticCapture", 0, iniText.c_str()) != 0;
            config.semanticDumpJson = GetPrivateProfileIntA("Terrain", "TerrainSemanticDumpJson", 1, iniText.c_str()) != 0;
            config.semanticRenderer = GetPrivateProfileIntA("Terrain", "TerrainSemanticRenderer", 0, iniText.c_str()) != 0;
            config.semanticValidateUv = GetPrivateProfileIntA("Terrain", "TerrainSemanticValidateUV", 0, iniText.c_str()) != 0;
            config.semanticLegacyUvQuantization = GetPrivateProfileIntA("Terrain", "TerrainSemanticLegacyUVQuantization", 1, iniText.c_str()) != 0;
            config.semanticDumpMismatches = GetPrivateProfileIntA("Terrain", "TerrainSemanticDumpMismatches", 0, iniText.c_str()) != 0;
            config.semanticLifecycleLog = GetPrivateProfileIntA("Terrain", "TerrainSemanticLifecycleLog", 0, iniText.c_str()) != 0;
            config.semanticDebugMode = GetPrivateProfileIntA("Terrain", "TerrainSemanticDebug", 0, iniText.c_str());
            config.semanticFrameCaptures = GetPrivateProfileIntA("Terrain", "TerrainSemanticFrameCapture", 0, iniText.c_str());
            config.semanticFrameCaptureStride = GetPrivateProfileIntA("Terrain", "TerrainSemanticFrameCaptureStride", 300, iniText.c_str());
            config.semanticFrameCaptureRequireOnScreen = GetPrivateProfileIntA(
                "Terrain", "TerrainSemanticFrameCaptureRequireOnScreen", 1, iniText.c_str()) != 0;
            config.semanticFrameCaptureMinCoverage = ReadIniFloat(
                ini.c_str(), "TerrainSemanticFrameCaptureMinCoverage", 0.005f);
            config.followCamera = GetPrivateProfileIntA(
                "Terrain", "TerrainProxyFollowCamera", 0, iniText.c_str()) != 0;
            config.followCameraAimDistance = ReadIniFloat(
                ini.c_str(), "TerrainProxyFollowCameraAimDistance", 35.0f);
            config.followCameraReselectFrames = GetPrivateProfileIntA(
                "Terrain", "TerrainProxyFollowCameraReselectFrames", 300, iniText.c_str());
            config.hdEnabled = GetPrivateProfileIntA(
                "Terrain", "TerrainHdEnabled", 0, iniText.c_str()) != 0;
            config.hdManifest = ReadIniString(
                iniText, "TerrainHdManifest", "terrain_hd_tiles.json");
            config.zoneOrdinal = GetPrivateProfileIntA("Terrain", "TerrainProxyZone", -1, iniText.c_str());
            config.clusterOrdinal = GetPrivateProfileIntA("Terrain", "TerrainProxyCluster", -1, iniText.c_str());
            config.zoneX = GetPrivateProfileIntA("Terrain", "TerrainProxyZoneX", INT_MIN, iniText.c_str());
            config.zoneZ = GetPrivateProfileIntA("Terrain", "TerrainProxyZoneZ", INT_MIN, iniText.c_str());
            config.clusterX = GetPrivateProfileIntA("Terrain", "TerrainProxyClusterX", INT_MIN, iniText.c_str());
            config.clusterZ = GetPrivateProfileIntA("Terrain", "TerrainProxyClusterZ", INT_MIN, iniText.c_str());
            config.offset.x = ReadIniFloat(ini.c_str(), "TerrainProxyOffsetX", 0.0f);
            config.offset.y = ReadIniFloat(ini.c_str(), "TerrainProxyOffsetY", 0.0f);
            config.offset.z = ReadIniFloat(ini.c_str(), "TerrainProxyOffsetZ", 0.0f);
            if (IsEnvEnabled("OPENSHIM_TERRAIN_PROXY"))
                config.proxyEnabled = true;
            if (IsEnvEnabled("OPENSHIM_TERRAIN_SEMANTIC_CAPTURE"))
                config.semanticCapture = true;
            if (IsEnvEnabled("OPENSHIM_TERRAIN_SEMANTIC_VALIDATE_UV"))
                config.semanticValidateUv = true;
            if (IsEnvEnabled("OPENSHIM_TERRAIN_SEMANTIC_RENDERER"))
                config.semanticRenderer = true;
            if (IsEnvEnabled("OPENSHIM_TERRAIN_SEMANTIC_LIFECYCLE_LOG"))
                config.semanticLifecycleLog = true;
            if (IsEnvEnabled("OPENSHIM_TERRAIN_HD"))
                config.hdEnabled = true;
            ReadEnvString("OPENSHIM_TERRAIN_HD_MANIFEST", config.hdManifest);
            int debugOverride = 0;
            if (ReadEnvInt("OPENSHIM_TERRAIN_SEMANTIC_DEBUG", debugOverride))
                config.semanticDebugMode = debugOverride;
            if (config.semanticDebugMode < 0 ||
                config.semanticDebugMode > kSemanticDebugModeMaximum)
                config.semanticDebugMode = 0;
            int captureOverride = 0;
            if (ReadEnvInt("OPENSHIM_TERRAIN_SEMANTIC_FRAME_CAPTURE", captureOverride))
                config.semanticFrameCaptures = captureOverride;
            int strideOverride = 0;
            if (ReadEnvInt("OPENSHIM_TERRAIN_SEMANTIC_FRAME_CAPTURE_STRIDE", strideOverride))
                config.semanticFrameCaptureStride = strideOverride;
            int quantizationOverride = 0;
            if (ReadEnvInt("OPENSHIM_TERRAIN_SEMANTIC_LEGACY_UV_QUANTIZATION",
                    quantizationOverride))
                config.semanticLegacyUvQuantization = quantizationOverride != 0;
            if (IsEnvEnabled("OPENSHIM_TERRAIN_PROXY_FOLLOW_CAMERA"))
                config.followCamera = true;
            int onScreenOverride = 0;
            if (ReadEnvInt("OPENSHIM_TERRAIN_SEMANTIC_FRAME_CAPTURE_REQUIRE_ON_SCREEN",
                    onScreenOverride))
                config.semanticFrameCaptureRequireOnScreen = onScreenOverride != 0;
            ReadEnvFloat("OPENSHIM_TERRAIN_SEMANTIC_FRAME_CAPTURE_MIN_COVERAGE",
                config.semanticFrameCaptureMinCoverage);
            ReadEnvFloat("OPENSHIM_TERRAIN_PROXY_FOLLOW_CAMERA_AIM_DISTANCE",
                config.followCameraAimDistance);
            if (!(config.followCameraAimDistance >= 0.0f))
                config.followCameraAimDistance = 35.0f;
            int reselectOverride = 0;
            if (ReadEnvInt("OPENSHIM_TERRAIN_PROXY_FOLLOW_CAMERA_RESELECT_FRAMES",
                    reselectOverride))
                config.followCameraReselectFrames = reselectOverride;
            if (config.followCameraReselectFrames < 0)
                config.followCameraReselectFrames = 0;
            if (config.semanticFrameCaptures < 0)
                config.semanticFrameCaptures = 0;
            if (config.semanticFrameCaptures > 64)
                config.semanticFrameCaptures = 64;
            if (config.semanticFrameCaptureStride < 1)
                config.semanticFrameCaptureStride = 1;
            if (!(config.semanticFrameCaptureMinCoverage >= 0.0f) ||
                config.semanticFrameCaptureMinCoverage > 1.0f)
                config.semanticFrameCaptureMinCoverage = 0.005f;
            return config;
        }

        std::filesystem::path ResolveHdManifestPath(const std::string& configured)
        {
            if (configured.empty())
                return {};
            std::filesystem::path path(configured);
            if (path.is_absolute())
                return path.lexically_normal();
            wchar_t executable[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameW(nullptr, executable, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return {};
            return (std::filesystem::path(executable).parent_path() / path)
                .lexically_normal();
        }

        bool LoadTerrainHdManifest()
        {
            g_hdManifest = {};
            if (!g_config.hdEnabled)
                return false;

            const std::filesystem::path path =
                ResolveHdManifestPath(g_config.hdManifest);
            if (path.empty())
            {
                LogShimA(LogLevel::Warn, "terrain-hd",
                    "[TERRAIN-HD] manifest path is empty; stock atlas retained");
                return false;
            }

            try
            {
                std::ifstream stream(path);
                if (!stream)
                {
                    LogShimA(LogLevel::Warn, "terrain-hd",
                        "[TERRAIN-HD] manifest unavailable path=\"%s\"; stock atlas retained",
                        path.string().c_str());
                    return false;
                }
                nlohmann::json root;
                stream >> root;
                if (root.value("schema", std::string()) !=
                        "bzr-openshim-terrain-hd-v1" ||
                    !root.contains("materials") ||
                    !root["materials"].is_object())
                {
                    LogShimA(LogLevel::Warn, "terrain-hd",
                        "[TERRAIN-HD] manifest schema/materials invalid path=\"%s\"; stock atlas retained",
                        path.string().c_str());
                    return false;
                }

                TerrainHdManifest parsed;
                parsed.path = path;
                for (auto materialIt = root["materials"].begin();
                     materialIt != root["materials"].end(); ++materialIt)
                {
                    if (!materialIt.value().is_object())
                        throw std::runtime_error("material binding is not an object");
                    TerrainHdMaterialBinding binding;
                    binding.sliceCount = materialIt.value().value(
                        "sliceCount", 0u);
                    binding.fallback = materialIt.value().value(
                        "fallback", std::string());
                    if (binding.sliceCount == 0 || binding.sliceCount > 256 ||
                        binding.fallback.empty())
                        throw std::runtime_error(
                            "sliceCount must be 1..256 and fallback must be non-empty");
                    if (materialIt.value().contains("tiles"))
                    {
                        const auto& tiles = materialIt.value()["tiles"];
                        if (!tiles.is_object())
                            throw std::runtime_error("tiles must be an object");
                        for (auto tileIt = tiles.begin(); tileIt != tiles.end(); ++tileIt)
                        {
                            char* end = nullptr;
                            const unsigned long index = std::strtoul(
                                tileIt.key().c_str(), &end, 10);
                            if (end == tileIt.key().c_str() || *end != '\0' ||
                                index >= binding.sliceCount ||
                                !tileIt.value().is_string() ||
                                tileIt.value().get<std::string>().empty())
                                throw std::runtime_error("invalid tile override");
                            binding.tiles.emplace(static_cast<uint32_t>(index),
                                tileIt.value().get<std::string>());
                        }
                    }
                    parsed.materials.emplace(materialIt.key(), std::move(binding));
                }
                if (parsed.materials.empty())
                    throw std::runtime_error("materials is empty");
                parsed.loaded = true;
                g_hdManifest = std::move(parsed);
                LogShimA(LogLevel::Info, "terrain-hd",
                    "[TERRAIN-HD] manifest loaded path=\"%s\" materials=%zu",
                    g_hdManifest.path.string().c_str(),
                    g_hdManifest.materials.size());
                return true;
            }
            catch (const std::exception& error)
            {
                LogShimA(LogLevel::Warn, "terrain-hd",
                    "[TERRAIN-HD] manifest parse failed path=\"%s\" error=\"%s\"; stock atlas retained",
                    path.string().c_str(), error.what());
            }
            return false;
        }

        const TerrainHdMaterialBinding* FindTerrainHdBinding(
            const std::string& material)
        {
            if (!g_hdManifest.loaded)
                return nullptr;
            const auto exact = g_hdManifest.materials.find(material);
            if (exact != g_hdManifest.materials.end())
                return &exact->second;
            const auto fallback = g_hdManifest.materials.find("*");
            return fallback != g_hdManifest.materials.end()
                ? &fallback->second : nullptr;
        }

        bool ComputeSha256(const wchar_t* path, std::string& outHash)
        {
            outHash.clear();
            HMODULE bcrypt = LoadLibraryW(L"bcrypt.dll");
            if (!bcrypt)
                return false;

            const auto openProvider = reinterpret_cast<decltype(&BCryptOpenAlgorithmProvider)>(
                GetProcAddress(bcrypt, "BCryptOpenAlgorithmProvider"));
            const auto getProperty = reinterpret_cast<decltype(&BCryptGetProperty)>(
                GetProcAddress(bcrypt, "BCryptGetProperty"));
            const auto createHash = reinterpret_cast<decltype(&BCryptCreateHash)>(
                GetProcAddress(bcrypt, "BCryptCreateHash"));
            const auto hashData = reinterpret_cast<decltype(&BCryptHashData)>(
                GetProcAddress(bcrypt, "BCryptHashData"));
            const auto finishHash = reinterpret_cast<decltype(&BCryptFinishHash)>(
                GetProcAddress(bcrypt, "BCryptFinishHash"));
            const auto destroyHash = reinterpret_cast<decltype(&BCryptDestroyHash)>(
                GetProcAddress(bcrypt, "BCryptDestroyHash"));
            const auto closeProvider = reinterpret_cast<decltype(&BCryptCloseAlgorithmProvider)>(
                GetProcAddress(bcrypt, "BCryptCloseAlgorithmProvider"));
            if (!openProvider || !getProperty || !createHash || !hashData || !finishHash ||
                !destroyHash || !closeProvider)
            {
                FreeLibrary(bcrypt);
                return false;
            }

            BCRYPT_ALG_HANDLE algorithm = nullptr;
            BCRYPT_HASH_HANDLE hash = nullptr;
            HANDLE file = INVALID_HANDLE_VALUE;
            bool ok = false;
            do
            {
                if (openProvider(&algorithm, BCRYPT_SHA256_ALGORITHM, nullptr, 0) < 0)
                    break;
                DWORD objectBytes = 0;
                DWORD hashBytes = 0;
                DWORD resultBytes = 0;
                if (getProperty(algorithm, BCRYPT_OBJECT_LENGTH,
                        reinterpret_cast<PUCHAR>(&objectBytes), sizeof(objectBytes), &resultBytes, 0) < 0 ||
                    getProperty(algorithm, BCRYPT_HASH_LENGTH,
                        reinterpret_cast<PUCHAR>(&hashBytes), sizeof(hashBytes), &resultBytes, 0) < 0 ||
                    hashBytes != 32)
                {
                    break;
                }
                std::vector<uint8_t> object(objectBytes);
                std::array<uint8_t, 32> digest = {};
                if (createHash(algorithm, &hash, object.data(), objectBytes, nullptr, 0, 0) < 0)
                    break;
                file = CreateFileW(path, GENERIC_READ,
                    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                    nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
                if (file == INVALID_HANDLE_VALUE)
                    break;
                std::array<uint8_t, 64 * 1024> buffer = {};
                for (;;)
                {
                    DWORD read = 0;
                    if (!ReadFile(file, buffer.data(), static_cast<DWORD>(buffer.size()), &read, nullptr))
                        break;
                    if (read == 0)
                    {
                        if (finishHash(hash, digest.data(), hashBytes, 0) < 0)
                            break;
                        std::ostringstream text;
                        text << std::uppercase << std::hex << std::setfill('0');
                        for (uint8_t byte : digest)
                            text << std::setw(2) << static_cast<unsigned>(byte);
                        outHash = text.str();
                        ok = true;
                        break;
                    }
                    if (hashData(hash, buffer.data(), read, 0) < 0)
                        break;
                }
            } while (false);

            if (file != INVALID_HANDLE_VALUE)
                CloseHandle(file);
            if (hash)
                destroyHash(hash);
            if (algorithm)
                closeProvider(algorithm, 0);
            FreeLibrary(bcrypt);
            return ok;
        }

        bool VerifyModuleHash(HMODULE module, const char* expected, std::string& actual)
        {
            wchar_t path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameW(module, path, MAX_PATH);
            return length > 0 && length < MAX_PATH && ComputeSha256(path, actual) && actual == expected;
        }

        template <typename T>
        T Resolve(HMODULE module, const char* name)
        {
            return reinterpret_cast<T>(GetProcAddress(module, name));
        }

        bool ResolveOgreApi(HMODULE module)
        {
            g_ogre.cloneMesh = Resolve<FnMeshClone>(module,
                "?clone@Mesh@Ogre@@QAE?AV?$SharedPtr@VMesh@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
            g_ogre.createEntity = Resolve<FnCreateEntityFromMesh>(module,
                "?createEntity@SceneManager@Ogre@@UAEPAVEntity@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV?$SharedPtr@VMesh@Ogre@@@2@@Z");
            g_ogre.getResourceName = Resolve<FnGetResourceName>(module,
                "?getName@Resource@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            g_ogre.getNumSubMeshes = Resolve<FnGetNumSubMeshes>(module, "?getNumSubMeshes@Mesh@Ogre@@QBEGXZ");
            g_ogre.getSubEntity = Resolve<FnGetSubEntity>(module, "?getSubEntity@Entity@Ogre@@QBEPAVSubEntity@2@I@Z");
            g_ogre.getRenderOperation = Resolve<FnGetRenderOperation>(module,
                "?getRenderOperation@SubEntity@Ogre@@UAEXAAVRenderOperation@2@@Z");
            g_ogre.getMaterialName = Resolve<FnGetMaterialName>(module,
                "?getMaterialName@SubEntity@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            g_ogre.setMaterialName = Resolve<FnSetMaterialName>(module,
                "?setMaterialName@Entity@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
            g_ogre.getBuffer = Resolve<FnGetBuffer>(module,
                "?getBuffer@VertexBufferBinding@Ogre@@UBEABVHardwareVertexBufferSharedPtr@2@G@Z");
            g_ogre.getVertexSize = Resolve<FnGetVertexSize>(module, "?getVertexSize@HardwareVertexBuffer@Ogre@@QBEIXZ");
            g_ogre.getNumVertices = Resolve<FnGetNumVertices>(module, "?getNumVertices@HardwareVertexBuffer@Ogre@@QBEIXZ");
            g_ogre.getIndexSize = Resolve<FnGetIndexSize>(module, "?getIndexSize@HardwareIndexBuffer@Ogre@@QBEIXZ");
            g_ogre.getNumIndexes = Resolve<FnGetNumIndexes>(module, "?getNumIndexes@HardwareIndexBuffer@Ogre@@QBEIXZ");
            g_ogre.getBufferSize = Resolve<FnGetBufferSize>(module, "?getSizeInBytes@HardwareBuffer@Ogre@@QBEIXZ");
            g_ogre.copyBufferData = Resolve<FnCopyBufferData>(module, "?copyData@HardwareBuffer@Ogre@@UAEXAAV12@@Z");
            g_ogre.lockBuffer = Resolve<FnLockBuffer>(module,
                "?lock@HardwareBuffer@Ogre@@UAEPAXIIW4LockOptions@12@W4UploadOptions@12@@Z");
            g_ogre.unlockBuffer = Resolve<FnUnlockBuffer>(module, "?unlock@HardwareBuffer@Ogre@@UAEXXZ");
            g_ogre.getParentSceneNode = Resolve<FnGetParentSceneNode>(module,
                "?getParentSceneNode@SceneNode@Ogre@@QBEPAV12@XZ");
            g_ogre.getNodePosition = Resolve<FnGetVector3>(module, "?getPosition@Node@Ogre@@UBEABVVector3@2@XZ");
            g_ogre.getNodeOrientation = Resolve<FnGetQuaternion>(module, "?getOrientation@Node@Ogre@@UBEABVQuaternion@2@XZ");
            g_ogre.getNodeScale = Resolve<FnGetVector3>(module, "?getScale@Node@Ogre@@UBEABVVector3@2@XZ");
            g_ogre.createChildSceneNode = Resolve<FnCreateChildSceneNode>(module,
                "?createChildSceneNode@SceneNode@Ogre@@UAEPAV12@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABVVector3@2@ABVQuaternion@2@@Z");
            g_ogre.setNodeScale = Resolve<FnSetNodeScale>(module, "?setScale@Node@Ogre@@UAEXABVVector3@2@@Z");
            g_ogre.attachObject = Resolve<FnAttachObject>(module, "?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
            g_ogre.setVisible = Resolve<FnSetVisible>(module, "?setVisible@MovableObject@Ogre@@UAEX_N@Z");
            g_ogre.setCastShadows = Resolve<FnSetCastShadows>(module, "?setCastShadows@MovableObject@Ogre@@QAEX_N@Z");
            g_ogre.setRenderQueueGroup = Resolve<FnSetRenderQueueGroup>(module, "?setRenderQueueGroup@Entity@Ogre@@UAEXE@Z");
            g_ogre.destroySceneNode = Resolve<FnDestroySceneNode>(module, "?destroySceneNode@SceneManager@Ogre@@UAEXPAVSceneNode@2@@Z");
            g_ogre.destroyEntityByName = Resolve<FnDestroyByName>(module,
                "?destroyEntity@SceneManager@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            g_ogre.destroySceneNodeByName = Resolve<FnDestroyByName>(module,
                "?destroySceneNode@SceneManager@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            g_ogre.hasEntityByName = Resolve<FnHasByName>(module,
                "?hasEntity@SceneManager@Ogre@@UBE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            g_ogre.hasSceneNodeByName = Resolve<FnHasByName>(module,
                "?hasSceneNode@SceneManager@Ogre@@UBE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            g_ogre.getBounds = Resolve<FnGetBounds>(module, "?getBounds@Mesh@Ogre@@QBEABVAxisAlignedBox@2@XZ");
            g_ogre.setBounds = Resolve<FnSetBounds>(module, "?_setBounds@Mesh@Ogre@@QAEXABVAxisAlignedBox@2@_N@Z");
            g_ogre.getRadius = Resolve<FnGetRadius>(module, "?getBoundingSphereRadius@Mesh@Ogre@@QBEMXZ");
            g_ogre.setRadius = Resolve<FnSetRadius>(module, "?_setBoundingSphereRadius@Mesh@Ogre@@QAEXM@Z");
            g_ogre.getHardwareBufferManager = Resolve<FnGetSingleton>(module,
                "?getSingletonPtr@HardwareBufferManager@Ogre@@SAPAV12@XZ");
            g_ogre.createVertexBuffer = Resolve<FnCreateVertexBuffer>(module,
                "?createVertexBuffer@HardwareBufferManager@Ogre@@UAE?AVHardwareVertexBufferSharedPtr@2@IIW4Usage@HardwareBuffer@2@_N@Z");
            g_ogre.addVertexElement = Resolve<FnAddVertexElement>(module,
                "?addElement@VertexDeclaration@Ogre@@UAEABVVertexElement@2@GIW4VertexElementType@2@W4VertexElementSemantic@2@G@Z");
            g_ogre.setVertexBinding = Resolve<FnSetVertexBinding>(module,
                "?setBinding@VertexBufferBinding@Ogre@@UAEXGABVHardwareVertexBufferSharedPtr@2@@Z");
            g_ogre.getMaterialManager = Resolve<FnGetSingleton>(module,
                "?getSingletonPtr@MaterialManager@Ogre@@SAPAV12@XZ");
            g_ogre.getMaterialByName = Resolve<FnGetMaterialByName>(module,
                "?getByName@MaterialManager@Ogre@@QAE?AV?$SharedPtr@VMaterial@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
            g_ogre.cloneMaterial = Resolve<FnCloneMaterial>(module,
                "?clone@Material@Ogre@@QBE?AV?$SharedPtr@VMaterial@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N0@Z");
            g_ogre.getNumTechniques = Resolve<FnGetNumTechniques>(module,
                "?getNumTechniques@Material@Ogre@@QBEGXZ");
            g_ogre.getTechnique = Resolve<FnGetTechnique>(module,
                "?getTechnique@Material@Ogre@@QAEPAVTechnique@2@G@Z");
            g_ogre.getNumPasses = Resolve<FnGetNumPasses>(module,
                "?getNumPasses@Technique@Ogre@@QBEGXZ");
            g_ogre.getPass = Resolve<FnGetPass>(module,
                "?getPass@Technique@Ogre@@QAEPAVPass@2@G@Z");
            g_ogre.getVertexProgram = Resolve<FnGetGpuProgram>(module,
                "?getVertexProgram@Pass@Ogre@@QBEABV?$SharedPtr@VGpuProgram@Ogre@@@2@XZ");
            g_ogre.getUnifiedDelegate = Resolve<FnGetUnifiedDelegate>(module,
                "?_getDelegate@UnifiedHighLevelGpuProgram@Ogre@@QBEABV?$SharedPtr@VHighLevelGpuProgram@Ogre@@@2@XZ");
            g_ogre.getVertexProgramParameters = Resolve<FnGetGpuProgramParameters>(module,
                "?getVertexProgramParameters@Pass@Ogre@@QBE?AV?$SharedPtr@VGpuProgramParameters@Ogre@@@2@XZ");
            g_ogre.setVertexProgram = Resolve<FnSetVertexProgram>(module,
                "?setVertexProgram@Pass@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
            g_ogre.setVertexProgramParameters = Resolve<FnSetVertexProgramParameters>(module,
                "?setVertexProgramParameters@Pass@Ogre@@QAEXV?$SharedPtr@VGpuProgramParameters@Ogre@@@2@@Z");
            g_ogre.getProgramSource = Resolve<FnGetStringReference>(module,
                "?getSource@GpuProgram@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            g_ogre.getStringParameter = Resolve<FnGetStringParameter>(module,
                "?getParameter@StringInterface@Ogre@@UBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z");
            g_ogre.getHighLevelProgramManager = Resolve<FnGetSingleton>(module,
                "?getSingletonPtr@HighLevelGpuProgramManager@Ogre@@SAPAV12@XZ");
            g_ogre.createHighLevelProgram = Resolve<FnCreateHighLevelProgram>(module,
                "?createProgram@HighLevelGpuProgramManager@Ogre@@QAE?AV?$SharedPtr@VHighLevelGpuProgram@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4GpuProgramType@2@@Z");
            g_ogre.setProgramSource = Resolve<FnSetProgramSource>(module,
                "?setSource@GpuProgram@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            g_ogre.setStringParameter = Resolve<FnSetStringParameter>(module,
                "?setParameter@StringInterface@Ogre@@UAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
            g_ogre.loadResource = Resolve<FnLoadResource>(module,
                "?load@Resource@Ogre@@UAEX_N@Z");
            g_ogre.getMeshManager = Resolve<FnGetMeshManager>(module, "?getSingletonPtr@MeshManager@Ogre@@SAPAV12@XZ");
            g_ogre.removeResource = Resolve<FnRemoveResource>(module,
                "?remove@ResourceManager@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            g_ogre.getFragmentProgram = Resolve<FnGetGpuProgram>(module,
                "?getFragmentProgram@Pass@Ogre@@QBEABV?$SharedPtr@VGpuProgram@Ogre@@@2@XZ");
            g_ogre.getFragmentProgramParameters = Resolve<FnGetGpuProgramParameters>(module,
                "?getFragmentProgramParameters@Pass@Ogre@@QBE?AV?$SharedPtr@VGpuProgramParameters@Ogre@@@2@XZ");
            g_ogre.setFragmentProgram = Resolve<FnSetVertexProgram>(module,
                "?setFragmentProgram@Pass@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
            g_ogre.setFragmentProgramParameters = Resolve<FnSetVertexProgramParameters>(module,
                "?setFragmentProgramParameters@Pass@Ogre@@QAEXV?$SharedPtr@VGpuProgramParameters@Ogre@@@2@@Z");
            g_ogre.getRoot = Resolve<FnGetSingleton>(module,
                "?getSingletonPtr@Root@Ogre@@SAPAV12@XZ");
            g_ogre.getAutoCreatedWindow = Resolve<FnGetAutoCreatedWindow>(module,
                "?getAutoCreatedWindow@Root@Ogre@@QAEPAVRenderWindow@2@XZ");
            g_ogre.writeContentsToFile = Resolve<FnWriteContentsToFile>(module,
                "?writeContentsToFile@RenderTarget@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            g_ogre.findElementBySemantic = Resolve<FnFindElementBySemantic>(module,
                "?findElementBySemantic@VertexDeclaration@Ogre@@UBEPBVVertexElement@2@W4VertexElementSemantic@2@G@Z");
            g_ogre.getElementSource = Resolve<FnGetElementUShort>(module,
                "?getSource@VertexElement@Ogre@@QBEGXZ");
            g_ogre.getElementType = Resolve<FnGetElementInt>(module,
                "?getType@VertexElement@Ogre@@QBE?AW4VertexElementType@2@XZ");
            g_ogre.getElementOffset = Resolve<FnGetElementUInt>(module,
                "?getOffset@VertexElement@Ogre@@QBEIXZ");
            g_ogre.getNumTextureUnitStates = Resolve<FnGetNumTextureUnitStates>(module,
                "?getNumTextureUnitStates@Pass@Ogre@@QBEGXZ");
            g_ogre.getTextureUnitState = Resolve<FnGetTextureUnitState>(module,
                "?getTextureUnitState@Pass@Ogre@@QAEPAVTextureUnitState@2@G@Z");
            g_ogre.setTexture = Resolve<FnSetTexture>(module,
                "?setTexture@TextureUnitState@Ogre@@QAEXABV?$SharedPtr@VTexture@Ogre@@@2@@Z");
            g_ogre.getTextureManager = Resolve<FnGetTextureManager>(module,
                "?getSingletonPtr@TextureManager@Ogre@@SAPAV12@XZ");
            g_ogre.loadTexture = Resolve<FnLoadTexture>(module,
                "?load@TextureManager@Ogre@@UAE?AV?$SharedPtr@VTexture@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0W4TextureType@2@HM_NW4PixelFormat@2@2@Z");
            g_ogre.createManualTexture = Resolve<FnCreateManualTexture>(module,
                "?createManual@TextureManager@Ogre@@UAE?AV?$SharedPtr@VTexture@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0W4TextureType@2@IIIHW4PixelFormat@2@HPAVManualResourceLoader@2@_NI0@Z");
            g_ogre.getTextureWidth = Resolve<FnGetTextureUInt>(module,
                "?getWidth@Texture@Ogre@@UBEIXZ");
            g_ogre.getTextureHeight = Resolve<FnGetTextureUInt>(module,
                "?getHeight@Texture@Ogre@@UBEIXZ");
            g_ogre.getTextureDepth = Resolve<FnGetTextureUInt>(module,
                "?getDepth@Texture@Ogre@@UBEIXZ");
            g_ogre.getTextureMipmaps = Resolve<FnGetTextureByte>(module,
                "?getNumMipmaps@Texture@Ogre@@UBEEXZ");
            g_ogre.getTextureType = Resolve<FnGetTextureInt>(module,
                "?getTextureType@Texture@Ogre@@UBE?AW4TextureType@2@XZ");
            g_ogre.getTextureFormat = Resolve<FnGetTextureInt>(module,
                "?getFormat@Texture@Ogre@@UBE?AW4PixelFormat@2@XZ");
            g_ogre.blitPixelBuffer = Resolve<FnBlitPixelBuffer>(module,
                "?blit@HardwarePixelBuffer@Ogre@@UAEXABVHardwarePixelBufferSharedPtr@2@ABUBox@2@1@Z");
            g_ogre.getViewport = Resolve<FnGetViewport>(module,
                "?getViewport@RenderTarget@Ogre@@UAEPAVViewport@2@G@Z");
            g_ogre.getViewportCamera = Resolve<FnGetViewportCamera>(module,
                "?getCamera@Viewport@Ogre@@QBEPAVCamera@2@XZ");
            g_ogre.getViewportWidth = Resolve<FnGetViewportInt>(module,
                "?getActualWidth@Viewport@Ogre@@QBEHXZ");
            g_ogre.getViewportHeight = Resolve<FnGetViewportInt>(module,
                "?getActualHeight@Viewport@Ogre@@QBEHXZ");
            // Camera overrides getViewMatrix, so the Camera export is the
            // correct implementation to call on a Camera*. getProjectionMatrix
            // is only implemented by Frustum and is not overridden by Camera.
            g_ogre.getViewMatrix = Resolve<FnGetMatrix4>(module,
                "?getViewMatrix@Camera@Ogre@@UBEABVMatrix4@2@XZ");
            g_ogre.getProjectionMatrix = Resolve<FnGetMatrix4>(module,
                "?getProjectionMatrix@Frustum@Ogre@@UBEABVMatrix4@2@XZ");
            g_ogre.cameraBoxVisible = Resolve<FnCameraBoxVisible>(module,
                "?isVisible@Camera@Ogre@@UBE_NABVAxisAlignedBox@2@PAW4FrustumPlane@2@@Z");
            g_ogre.getWorldBoundingBox = Resolve<FnGetWorldBoundingBox>(module,
                "?getWorldBoundingBox@Entity@Ogre@@UBEABVAxisAlignedBox@2@_N@Z");
            g_ogre.getCameraDerivedPosition = Resolve<FnGetDerivedPosition>(module,
                "?getDerivedPosition@Camera@Ogre@@QBEABVVector3@2@XZ");
            // Orientation rather than getDirection: the direction getters
            // return Vector3 by value, which on x86 __thiscall needs a hidden
            // return pointer. This one returns a const reference.
            g_ogre.getCameraDerivedOrientation = Resolve<FnGetQuaternion>(module,
                "?getDerivedOrientation@Camera@Ogre@@QBEABVQuaternion@2@XZ");

            const void* const required[] = {
                reinterpret_cast<void*>(g_ogre.cloneMesh), reinterpret_cast<void*>(g_ogre.createEntity),
                reinterpret_cast<void*>(g_ogre.getResourceName), reinterpret_cast<void*>(g_ogre.getNumSubMeshes),
                reinterpret_cast<void*>(g_ogre.getSubEntity), reinterpret_cast<void*>(g_ogre.getRenderOperation),
                reinterpret_cast<void*>(g_ogre.getMaterialName), reinterpret_cast<void*>(g_ogre.setMaterialName),
                reinterpret_cast<void*>(g_ogre.getBuffer), reinterpret_cast<void*>(g_ogre.getVertexSize),
                reinterpret_cast<void*>(g_ogre.getNumVertices), reinterpret_cast<void*>(g_ogre.getIndexSize),
                reinterpret_cast<void*>(g_ogre.getNumIndexes), reinterpret_cast<void*>(g_ogre.getBufferSize),
                reinterpret_cast<void*>(g_ogre.copyBufferData), reinterpret_cast<void*>(g_ogre.lockBuffer),
                reinterpret_cast<void*>(g_ogre.unlockBuffer), reinterpret_cast<void*>(g_ogre.getParentSceneNode),
                reinterpret_cast<void*>(g_ogre.getNodePosition), reinterpret_cast<void*>(g_ogre.getNodeOrientation),
                reinterpret_cast<void*>(g_ogre.getNodeScale), reinterpret_cast<void*>(g_ogre.createChildSceneNode),
                reinterpret_cast<void*>(g_ogre.setNodeScale), reinterpret_cast<void*>(g_ogre.attachObject),
                reinterpret_cast<void*>(g_ogre.setVisible), reinterpret_cast<void*>(g_ogre.setCastShadows),
                reinterpret_cast<void*>(g_ogre.setRenderQueueGroup), reinterpret_cast<void*>(g_ogre.getBounds),
                reinterpret_cast<void*>(g_ogre.setBounds), reinterpret_cast<void*>(g_ogre.getRadius),
                reinterpret_cast<void*>(g_ogre.setRadius), reinterpret_cast<void*>(g_ogre.getHardwareBufferManager),
                reinterpret_cast<void*>(g_ogre.createVertexBuffer), reinterpret_cast<void*>(g_ogre.addVertexElement),
                reinterpret_cast<void*>(g_ogre.setVertexBinding), reinterpret_cast<void*>(g_ogre.getMaterialManager),
                reinterpret_cast<void*>(g_ogre.getMaterialByName), reinterpret_cast<void*>(g_ogre.cloneMaterial),
                reinterpret_cast<void*>(g_ogre.getNumTechniques), reinterpret_cast<void*>(g_ogre.getTechnique),
                reinterpret_cast<void*>(g_ogre.getNumPasses), reinterpret_cast<void*>(g_ogre.getPass),
                reinterpret_cast<void*>(g_ogre.getVertexProgram), reinterpret_cast<void*>(g_ogre.getUnifiedDelegate),
                reinterpret_cast<void*>(g_ogre.getVertexProgramParameters),
                reinterpret_cast<void*>(g_ogre.setVertexProgram), reinterpret_cast<void*>(g_ogre.setVertexProgramParameters),
                reinterpret_cast<void*>(g_ogre.getProgramSource), reinterpret_cast<void*>(g_ogre.getStringParameter),
                reinterpret_cast<void*>(g_ogre.getHighLevelProgramManager), reinterpret_cast<void*>(g_ogre.createHighLevelProgram),
                reinterpret_cast<void*>(g_ogre.setProgramSource), reinterpret_cast<void*>(g_ogre.setStringParameter),
                reinterpret_cast<void*>(g_ogre.loadResource), reinterpret_cast<void*>(g_ogre.getMeshManager),
                reinterpret_cast<void*>(g_ogre.removeResource)
            };
            for (const void* function : required)
                if (!function)
                    return false;
            return true;
        }

        bool ResolveD3D11TextureApi()
        {
            if (g_ogre.getTextureBuffer)
                return true;
            HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
            if (!renderer)
                return false;
            g_ogre.getTextureBuffer = Resolve<FnGetTextureBuffer>(renderer,
                "?getBuffer@D3D11Texture@Ogre@@UAE?AVHardwarePixelBufferSharedPtr@2@II@Z");
            return g_ogre.getTextureBuffer != nullptr;
        }

        bool SafeReadZoneInt(void* zone, size_t offset, int& value)
        {
            __try
            {
                value = *reinterpret_cast<const int*>(reinterpret_cast<const uint8_t*>(zone) + offset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeReadZoneByte(void* zone, size_t offset, uint8_t& value)
        {
            __try
            {
                value = *reinterpret_cast<const uint8_t*>(reinterpret_cast<const uint8_t*>(zone) + offset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeReadZonePointer(void* zone, size_t offset, void*& value)
        {
            __try
            {
                value = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(zone) + offset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeReadIntAddress(uintptr_t address, int& value)
        {
            __try
            {
                value = *reinterpret_cast<const int*>(address);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeReadRunState(int& value)
        {
            return SafeReadIntAddress(Rebase(kRunStateVa), value);
        }

        // Names come from Redux's own SetRunning table rather than from a
        // guessed enum, so a table layout change shows up as a mismatch at
        // install time instead of as a silently wrong lifecycle decision.
        const char* RunStateName(int state)
        {
            if (state < 0 || state >= kRunStateNameCount)
                return "<out-of-range>";
            __try
            {
                const char* const* const table =
                    reinterpret_cast<const char* const*>(Rebase(kRunStateNameTableVa));
                const char* const name = table[state];
                return name ? name : "<null>";
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return "<unreadable>";
            }
        }

        bool RunStateNameMatches(int state, const char* expected)
        {
            __try
            {
                const char* const* const table =
                    reinterpret_cast<const char* const*>(Rebase(kRunStateNameTableVa));
                const char* const name = table[state];
                if (!name)
                    return false;
                for (size_t index = 0;; ++index)
                {
                    if (name[index] != expected[index])
                        return false;
                    if (expected[index] == '\0')
                        return true;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void* SafeGetSceneManager()
        {
            __try
            {
                void* structure = *reinterpret_cast<void**>(Rebase(0x00920EA0));
                return structure
                    ? *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(structure) + 8)
                    : nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        bool CaptureClusterHeightSignature(uint32_t& hash, uint16_t& minimum, uint16_t& maximum)
        {
            if (!g_heightAt || !g_proxy.selected)
                return false;
            int originX = 0;
            int originZ = 0;
            if (!SafeReadIntAddress(Rebase(kTerrainOriginXVa), originX) ||
                !SafeReadIntAddress(Rebase(kTerrainOriginZVa), originZ))
                return false;
            const int baseX = g_proxy.zoneX * 256 + originX - 128 + g_proxy.clusterX * 64;
            const int baseZ = g_proxy.zoneZ * 256 + originZ - 128 + g_proxy.clusterZ * 64;
            uint32_t nextHash = 2166136261u;
            uint16_t nextMinimum = 0xFFFF;
            uint16_t nextMaximum = 0;
            __try
            {
                // A stock cluster spans 16 cells at four height samples per
                // cell. Hash its complete 65x65 integer height lattice only
                // when Redux marks the cluster dirty (never per frame).
                for (int z = 0; z <= 64; ++z)
                {
                    for (int x = 0; x <= 64; ++x)
                    {
                        const uint16_t height = g_heightAt(baseX + x, baseZ + z);
                        nextMinimum = height < nextMinimum ? height : nextMinimum;
                        nextMaximum = height > nextMaximum ? height : nextMaximum;
                        nextHash ^= static_cast<uint8_t>(height & 0xFF);
                        nextHash *= 16777619u;
                        nextHash ^= static_cast<uint8_t>(height >> 8);
                        nextHash *= 16777619u;
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            hash = nextHash;
            minimum = nextMinimum;
            maximum = nextMaximum;
            return true;
        }

        bool ReleaseCloneHandoff(OgreSharedPtr& pointer)
        {
            if (!pointer.rep || !pointer.info)
                return true;
            __try
            {
                auto* count = reinterpret_cast<volatile LONG*>(
                    reinterpret_cast<uint8_t*>(pointer.info) + sizeof(void*));
                const LONG current = InterlockedCompareExchange(count, 0, 0);
                if (current <= 1)
                    return false;
                InterlockedDecrement(count);
                pointer.rep = nullptr;
                pointer.info = nullptr;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ParseTerrainMeshName(const std::string& name, int& zoneX, int& zoneZ, int& clusterX, int& clusterZ)
        {
            int consumed = 0;
            return sscanf_s(name.c_str(), "RenderableTileCluster_%dx%d_%dx%d%n",
                &zoneX, &zoneZ, &clusterX, &clusterZ, &consumed) == 4 &&
                consumed == static_cast<int>(name.size());
        }

        bool GetEntityOperation(void* entity, RenderOperation& operation, void*& subEntity)
        {
            operation = {};
            subEntity = nullptr;
            if (!entity)
                return false;
            subEntity = g_ogre.getSubEntity(entity, 0);
            if (!subEntity)
                return false;
            g_ogre.getRenderOperation(subEntity, operation);
            return operation.vertexData && operation.indexData;
        }

        bool GetVertexBuffer(const RenderOperation& operation, uint16_t slot, void*& buffer)
        {
            buffer = nullptr;
            if (!operation.vertexData || !operation.vertexData->binding)
                return false;
            const OgreSharedPtr* pointer = g_ogre.getBuffer(operation.vertexData->binding, slot);
            if (!pointer || !pointer->rep)
                return false;
            buffer = pointer->rep;
            return true;
        }

        bool ReadD3D11VertexBuffer(
            void* ogreBuffer,
            uint32_t byteCount,
            std::vector<uint8_t>& bytes)
        {
            bytes.clear();
            if (!ogreBuffer || byteCount == 0)
                return false;

            if (!g_ogre.getD3D11VertexBuffer)
            {
                HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
                if (!renderer)
                    return false;
                g_ogre.getD3D11VertexBuffer = Resolve<FnGetD3D11VertexBuffer>(
                    renderer,
                    "?getD3DVertexBuffer@D3D11HardwareVertexBuffer@Ogre@@QBEPAUID3D11Buffer@@XZ");
                if (!g_ogre.getD3D11VertexBuffer)
                    return false;
            }

            ID3D11Buffer* source = nullptr;
            ID3D11Device* device = nullptr;
            ID3D11DeviceContext* context = nullptr;
            ID3D11Buffer* staging = nullptr;
            bool mapped = false;
            bool ok = false;
            D3D11_MAPPED_SUBRESOURCE mapping = {};
            try
            {
                do
                {
                    source = g_ogre.getD3D11VertexBuffer(ogreBuffer);
                    if (!source)
                        break;

                    D3D11_BUFFER_DESC sourceDesc = {};
                    source->GetDesc(&sourceDesc);
                    if (sourceDesc.ByteWidth < byteCount)
                        break;

                    source->GetDevice(&device);
                    if (!device)
                        break;
                    device->GetImmediateContext(&context);
                    if (!context)
                        break;

                    D3D11_BUFFER_DESC stagingDesc = sourceDesc;
                    stagingDesc.Usage = D3D11_USAGE_STAGING;
                    stagingDesc.BindFlags = 0;
                    stagingDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
                    stagingDesc.MiscFlags = 0;
                    stagingDesc.StructureByteStride = 0;
                    if (FAILED(device->CreateBuffer(&stagingDesc, nullptr, &staging)) || !staging)
                        break;

                    context->CopyResource(staging, source);
                    if (FAILED(context->Map(staging, 0, D3D11_MAP_READ, 0, &mapping)) ||
                        !mapping.pData)
                        break;
                    mapped = true;
                    bytes.resize(byteCount);
                    memcpy(bytes.data(), mapping.pData, byteCount);
                    ok = true;
                } while (false);
            }
            catch (...)
            {
                ok = false;
            }

            if (mapped && context && staging)
                context->Unmap(staging, 0);
            if (staging)
                staging->Release();
            if (context)
                context->Release();
            if (device)
                device->Release();
            if (!ok)
                bytes.clear();
            return ok;
        }

        bool WriteD3D11VertexBuffer(
            void* ogreBuffer,
            const void* bytes,
            uint32_t byteCount)
        {
            if (!ogreBuffer || !bytes || byteCount == 0)
                return false;
            if (!g_ogre.getD3D11VertexBuffer)
            {
                HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
                if (!renderer)
                    return false;
                g_ogre.getD3D11VertexBuffer = Resolve<FnGetD3D11VertexBuffer>(
                    renderer,
                    "?getD3DVertexBuffer@D3D11HardwareVertexBuffer@Ogre@@QBEPAUID3D11Buffer@@XZ");
                if (!g_ogre.getD3D11VertexBuffer)
                    return false;
            }
            ID3D11Buffer* buffer = nullptr;
            ID3D11Device* device = nullptr;
            ID3D11DeviceContext* context = nullptr;
            bool mapped = false;
            bool ok = false;
            D3D11_MAPPED_SUBRESOURCE mapping = {};
            try
            {
                do
                {
                    buffer = g_ogre.getD3D11VertexBuffer(ogreBuffer);
                    if (!buffer)
                        break;
                    D3D11_BUFFER_DESC description = {};
                    buffer->GetDesc(&description);
                    if (description.ByteWidth < byteCount ||
                        description.Usage != D3D11_USAGE_DYNAMIC ||
                        !(description.CPUAccessFlags & D3D11_CPU_ACCESS_WRITE))
                        break;
                    buffer->GetDevice(&device);
                    if (!device)
                        break;
                    device->GetImmediateContext(&context);
                    if (!context)
                        break;
                    if (FAILED(context->Map(buffer, 0,
                            D3D11_MAP_WRITE_DISCARD, 0, &mapping)) ||
                        !mapping.pData)
                        break;
                    mapped = true;
                    memcpy(mapping.pData, bytes, byteCount);
                    ok = true;
                } while (false);
            }
            catch (...)
            {
                ok = false;
            }
            if (mapped && context && buffer)
                context->Unmap(buffer, 0);
            if (context)
                context->Release();
            if (device)
                device->Release();
            return ok;
        }

        bool ValidateTerrainOperation(void* mesh, void* entity, const char* role)
        {
            if (!mesh || !entity || g_ogre.getNumSubMeshes(mesh) != 1)
                return false;
            RenderOperation operation = {};
            void* subEntity = nullptr;
            if (!GetEntityOperation(entity, operation, subEntity) ||
                operation.operationType != 4 || !operation.useIndexes ||
                operation.vertexData->vertexCount != kExpectedVertices ||
                operation.indexData->indexCount != kExpectedIndices)
            {
                return false;
            }

            static constexpr uint32_t expectedStrides[] = { 16, 4, 4 };
            for (uint16_t slot = 0; slot < 3; ++slot)
            {
                void* buffer = nullptr;
                if (!GetVertexBuffer(operation, slot, buffer) ||
                    g_ogre.getVertexSize(buffer) != expectedStrides[slot] ||
                    g_ogre.getNumVertices(buffer) < kExpectedVertices ||
                    g_ogre.getBufferSize(buffer) < expectedStrides[slot] * kExpectedVertices)
                {
                    return false;
                }
            }
            void* indexBuffer = operation.indexData->indexBuffer.rep;
            if (!indexBuffer || g_ogre.getIndexSize(indexBuffer) != 2 ||
                g_ogre.getNumIndexes(indexBuffer) < kExpectedIndices ||
                g_ogre.getBufferSize(indexBuffer) < kExpectedIndices * 2)
            {
                return false;
            }
            LogShimA(LogLevel::Info, "terrain-proxy",
                "[TERRAIN-PROXY] %s validated vertices=%u indices=%u topology=triangle-list strides=16/4/4",
                role, kExpectedVertices, kExpectedIndices);
            return true;
        }

        // Configured selectors only. The implicit "first cluster" default is
        // deliberately left to the caller so camera-aware selection can weigh
        // all sixteen clusters instead of stopping at ordinal 0.
        bool MatchExplicitSelection(int zoneOrdinal, int zoneX, int zoneZ, int clusterX, int clusterZ)
        {
            const int clusterOrdinal = clusterX * kClusterAxisCount + clusterZ;
            if (g_config.zoneOrdinal >= 0 && zoneOrdinal != g_config.zoneOrdinal)
                return false;
            if (g_config.clusterOrdinal >= 0 && clusterOrdinal != g_config.clusterOrdinal)
                return false;
            if (g_config.zoneX != INT_MIN && zoneX != g_config.zoneX)
                return false;
            if (g_config.zoneZ != INT_MIN && zoneZ != g_config.zoneZ)
                return false;
            if (g_config.clusterX != INT_MIN && clusterX != g_config.clusterX)
                return false;
            if (g_config.clusterZ != INT_MIN && clusterZ != g_config.clusterZ)
                return false;
            return true;
        }

        bool HasExplicitClusterSelector()
        {
            return g_config.clusterOrdinal >= 0 ||
                g_config.clusterX != INT_MIN || g_config.clusterZ != INT_MIN;
        }

        bool MatchSelection(int zoneOrdinal, int zoneX, int zoneZ, int clusterX, int clusterZ)
        {
            if (!MatchExplicitSelection(zoneOrdinal, zoneX, zoneZ, clusterX, clusterZ))
                return false;
            if (!HasExplicitClusterSelector())
                return clusterX * kClusterAxisCount + clusterZ == 0;
            return true;
        }

        void RemoveProxyMeshResource()
        {
            if (g_proxy.proxyMeshName.empty() || !g_ogre.getMeshManager || !g_ogre.removeResource)
                return;
            try
            {
                void* manager = g_ogre.getMeshManager();
                if (manager)
                    g_ogre.removeResource(manager, g_proxy.proxyMeshName);
            }
            catch (...)
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] failed removing mesh resource name=\"%s\"",
                    g_proxy.proxyMeshName.c_str());
            }
        }

        bool AddSharedReference(const OgreSharedPtr& pointer)
        {
            if (!pointer.rep || !pointer.info)
                return false;
            __try
            {
                auto* count = reinterpret_cast<volatile LONG*>(
                    reinterpret_cast<uint8_t*>(pointer.info) + sizeof(void*));
                InterlockedIncrement(count);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Eight hex digits of the generated source, for use inside a generated
        // program name. Ogre's microcode cache is name-keyed, so the name has
        // to change whenever the source does or the cache serves stale
        // microcode compiled from an earlier run's source.
        std::string SourceHashSuffix(const std::string& source);

        uint32_t HashBytes(const void* data, size_t byteCount, uint32_t seed = 2166136261u)
        {
            const auto* bytes = static_cast<const uint8_t*>(data);
            uint32_t hash = seed;
            for (size_t i = 0; i < byteCount; ++i)
            {
                hash ^= bytes[i];
                hash *= 16777619u;
            }
            return hash;
        }

        std::string SourceHashSuffix(const std::string& source)
        {
            char text[16] = {};
            sprintf_s(text, "%08x",
                HashBytes(source.data(), source.size()));
            return std::string(text);
        }

        // Snapshot of everything the semantic path depends on at draw time.
        // Every field is read back from OGRE rather than from shim state so a
        // silent fallback to the packed-UV path cannot go unnoticed.
        struct SemanticBinding
        {
            bool operationValid = false;
            bool slotPresent = false;
            void* buffer = nullptr;
            uint32_t stride = 0;
            uint32_t vertices = 0;
            bool declarationLocalUv = false;
            bool declarationSemantic = false;
            bool declarationAtlasRect = false;
            bool declarationAudited = false;
            bool materialIsSemantic = false;
            std::string materialName;

            uint32_t Signature() const
            {
                const uint32_t flags =
                    (slotPresent ? 1u : 0u) |
                    (declarationLocalUv ? 2u : 0u) |
                    (declarationSemantic ? 4u : 0u) |
                    (declarationAtlasRect ? 8u : 0u) |
                    (materialIsSemantic ? 16u : 0u) |
                    (declarationAudited ? 32u : 0u);
                const uint32_t fields[] = {
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(buffer)),
                    stride, vertices, flags
                };
                return HashBytes(fields, sizeof(fields));
            }
        };

        // VES_TEXTURE_COORDINATES in OGRE 1.10.
        constexpr int kVesTextureCoordinates = 7;

        void AuditSemanticDeclaration(void* declaration, SemanticBinding& binding)
        {
            if (!declaration || !g_ogre.findElementBySemantic ||
                !g_ogre.getElementSource)
                return;
            const auto sourceIsSlotThree = [&](uint16_t index) -> bool
            {
                const void* element = g_ogre.findElementBySemantic(
                    declaration, kVesTextureCoordinates, index);
                return element && g_ogre.getElementSource(element) == 3;
            };
            try
            {
                binding.declarationLocalUv = sourceIsSlotThree(2);
                binding.declarationSemantic = sourceIsSlotThree(3);
                binding.declarationAtlasRect = sourceIsSlotThree(4);
                binding.declarationAudited = true;
            }
            catch (...)
            {
                binding.declarationAudited = false;
            }
        }

        bool QuerySemanticBinding(SemanticBinding& binding)
        {
            binding = {};
            if (!g_proxy.proxyCreated || !g_proxy.proxyEntity)
                return false;
            try
            {
                RenderOperation operation = {};
                void* subEntity = nullptr;
                if (!GetEntityOperation(g_proxy.proxyEntity, operation, subEntity))
                    return false;
                binding.operationValid = true;

                void* buffer = nullptr;
                if (GetVertexBuffer(operation, 3, buffer) && buffer)
                {
                    binding.slotPresent = true;
                    binding.buffer = buffer;
                    binding.stride = g_ogre.getVertexSize(buffer);
                    binding.vertices = g_ogre.getNumVertices(buffer);
                }
                AuditSemanticDeclaration(
                    operation.vertexData ? operation.vertexData->declaration : nullptr,
                    binding);

                if (const std::string* material = g_ogre.getMaterialName(subEntity))
                {
                    binding.materialName = *material;
                    binding.materialIsSemantic =
                        !g_proxy.semanticMaterialName.empty() &&
                        *material == g_proxy.semanticMaterialName;
                }
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        // Guarded invariants. Nothing here aborts the process: a violated
        // invariant is a diagnostic, and the stock terrain stays authoritative
        // in every case.
        bool ValidateSemanticBinding(const char* phase, const SemanticBinding& binding)
        {
            if (!g_proxy.semanticStreamInstalled)
                return true;
            bool ok = true;
            const auto fail = [&](const char* detail)
            {
                ok = false;
                LogShimA(LogLevel::Warn, "terrain-p3",
                    "[TERRAIN-P3] semantic invariant violated phase=%s detail=%s vbGeneration=%u proxyGeneration=%u",
                    phase, detail, g_proxy.semanticVbGeneration, g_proxy.generation);
            };
            if (!binding.operationValid)
                fail("render-operation-unavailable");
            if (!binding.slotPresent)
                fail("slot3-missing");
            else
            {
                if (binding.stride != sizeof(TerrainSemantic::GpuVertex))
                    fail("slot3-stride");
                if (binding.vertices < TerrainSemantic::kVertexCount)
                    fail("slot3-vertex-count");
                if (g_proxy.semanticBuffer && binding.buffer != g_proxy.semanticBuffer)
                    fail("slot3-buffer-identity");
            }
            if (binding.declarationAudited &&
                (!binding.declarationLocalUv || !binding.declarationSemantic ||
                 !binding.declarationAtlasRect))
                fail("declaration-slot3-elements");
            if (g_proxy.semanticMaterialInstalled && !binding.materialIsSemantic)
                fail("material-reverted-to-packed-uv");
            if (g_proxy.semanticVertices.size() != TerrainSemantic::kVertexCount)
                fail("cpu-vertex-count");
            return ok;
        }

        // Per-vertex range checks over the freshly generated semantic set.
        bool ValidateSemanticVertexRanges(const std::vector<TerrainSemantic::Vertex>& vertices)
        {
            size_t reported = 0;
            bool ok = true;
            for (size_t i = 0; i < vertices.size(); ++i)
            {
                const TerrainSemantic::GpuVertex& gpu = vertices[i].gpu;
                const bool orientationOk = gpu.orientation <= 15;
                const bool rectOk = std::isfinite(gpu.atlasU) &&
                    std::isfinite(gpu.atlasV) && std::isfinite(gpu.atlasW) &&
                    std::isfinite(gpu.atlasH) && gpu.atlasW > 0.0f &&
                    gpu.atlasH > 0.0f && gpu.atlasU >= 0.0f && gpu.atlasV >= 0.0f &&
                    gpu.atlasU + gpu.atlasW <= 1.0f + 1e-4f &&
                    gpu.atlasV + gpu.atlasH <= 1.0f + 1e-4f;
                const bool localOk = gpu.localU >= 0.0f && gpu.localU <= 1.0f &&
                    gpu.localV >= 0.0f && gpu.localV <= 1.0f;
                if (orientationOk && rectOk && localOk)
                    continue;
                ok = false;
                if (reported++ < 4)
                {
                    LogShimA(LogLevel::Warn, "terrain-p3",
                        "[TERRAIN-P3] semantic range check failed vertex=%zu tileIndex=%u orientation=%u localUV=(%.6f,%.6f) rect=(%.6f,%.6f,%.6f,%.6f)",
                        i, static_cast<unsigned>(gpu.tileIndex),
                        static_cast<unsigned>(gpu.orientation),
                        static_cast<double>(gpu.localU), static_cast<double>(gpu.localV),
                        static_cast<double>(gpu.atlasU), static_cast<double>(gpu.atlasV),
                        static_cast<double>(gpu.atlasW), static_cast<double>(gpu.atlasH));
                }
            }
            return ok;
        }

        void LogSemanticBinding(const char* event, const SemanticBinding& binding)
        {
            LogShimA(LogLevel::Info, "terrain-p3",
                "[TERRAIN-P3] terrain_semantic: %s proxyGeneration=%u vbGeneration=%u materialGeneration=%u vb=%p slot3=%d stride=%u vertices=%u declSlot3={localUV:%d,semantic:%d,atlasRect:%d,audited:%d} material=\"%s\" semanticMaterial=%d",
                event, g_proxy.generation, g_proxy.semanticVbGeneration,
                g_proxy.semanticMaterialGeneration, binding.buffer,
                binding.slotPresent ? 1 : 0, binding.stride, binding.vertices,
                binding.declarationLocalUv ? 1 : 0, binding.declarationSemantic ? 1 : 0,
                binding.declarationAtlasRect ? 1 : 0, binding.declarationAudited ? 1 : 0,
                binding.materialName.c_str(), binding.materialIsSemantic ? 1 : 0);
        }

        // One-shot / state-change reporting for the frequent update paths.
        void ReportSemanticBinding(const char* event, bool alwaysLog)
        {
            if (!g_config.semanticRenderer || !g_proxy.semanticStreamInstalled)
                return;
            SemanticBinding binding;
            if (!QuerySemanticBinding(binding))
            {
                LogShimA(LogLevel::Warn, "terrain-p3",
                    "[TERRAIN-P3] terrain_semantic: %s binding query failed proxyGeneration=%u",
                    event, g_proxy.generation);
                g_proxy.semanticBindingSignature = 0;
                return;
            }
            const uint32_t signature = binding.Signature();
            const bool changed = signature != g_proxy.semanticBindingSignature;
            const bool valid = ValidateSemanticBinding(event, binding);
            if (alwaysLog || changed || !valid)
                LogSemanticBinding(event, binding);
            g_proxy.semanticBindingSignature = signature;
        }

        // ---------------------------------------------------- capture framing --
        // Everything below answers one question: is the proxy cluster actually
        // on screen, and where? Sixteen captures across cluster ordinals 0-7
        // once returned an identical ~6,000 pixels of static UI because nothing
        // checked. It is diagnostic only and never influences rendering.

        constexpr int kAabbExtentFinite = 1;

        bool CaptureFramingApiAvailable()
        {
            return g_ogre.getRoot && g_ogre.getAutoCreatedWindow &&
                g_ogre.getViewport && g_ogre.getViewportCamera &&
                g_ogre.getViewportWidth && g_ogre.getViewportHeight &&
                g_ogre.getViewMatrix && g_ogre.getProjectionMatrix &&
                g_ogre.cameraBoxVisible && g_ogre.getWorldBoundingBox &&
                g_ogre.getCameraDerivedPosition;
        }

        // Ogre::Matrix4 is row-major, so a point transform is
        // result_i = sum_j m[i][j] * v_j with v_3 = 1.
        Matrix4 MultiplyMatrix(const Matrix4& left, const Matrix4& right)
        {
            Matrix4 product = {};
            for (int row = 0; row < 4; ++row)
                for (int column = 0; column < 4; ++column)
                    product.m[row][column] =
                        left.m[row][0] * right.m[0][column] +
                        left.m[row][1] * right.m[1][column] +
                        left.m[row][2] * right.m[2][column] +
                        left.m[row][3] * right.m[3][column];
            return product;
        }

        // Resolves the camera the auto-created window is actually rendering
        // through, which is the only one whose framing matches a capture.
        bool GetActiveCamera(void*& camera, int& width, int& height)
        {
            camera = nullptr;
            width = 0;
            height = 0;
            if (!CaptureFramingApiAvailable())
                return false;
            try
            {
                void* root = g_ogre.getRoot();
                void* window = root ? g_ogre.getAutoCreatedWindow(root) : nullptr;
                void* viewport = window ? g_ogre.getViewport(window, 0) : nullptr;
                if (!viewport)
                    return false;
                camera = g_ogre.getViewportCamera(viewport);
                if (!camera)
                    return false;
                width = g_ogre.getViewportWidth(viewport);
                height = g_ogre.getViewportHeight(viewport);
                return width > 0 && height > 0;
            }
            catch (...)
            {
                camera = nullptr;
                return false;
            }
        }

        // Screen bounding box of a world AABB's eight projected corners.
        // Corners behind the eye plane are excluded and counted rather than
        // wrapped around, so a partially clipped cluster reports a real rect
        // plus an honest cornersInFront value instead of a plausible lie.
        bool ProjectBoundsToScreen(void* camera,
                                   const AxisAlignedBox& bounds,
                                   int width,
                                   int height,
                                   ProxyScreenRect& out)
        {
            const Matrix4* view = g_ogre.getViewMatrix(camera);
            const Matrix4* projection = g_ogre.getProjectionMatrix(camera);
            if (!view || !projection)
                return false;
            const Matrix4 viewProjection = MultiplyMatrix(*projection, *view);

            float minimumX = 0.0f;
            float minimumY = 0.0f;
            float maximumX = 0.0f;
            float maximumY = 0.0f;
            int inFront = 0;
            for (int corner = 0; corner < 8; ++corner)
            {
                const Vector3 point = {
                    (corner & 1) ? bounds.maximum.x : bounds.minimum.x,
                    (corner & 2) ? bounds.maximum.y : bounds.minimum.y,
                    (corner & 4) ? bounds.maximum.z : bounds.minimum.z
                };
                const float clipW =
                    viewProjection.m[3][0] * point.x + viewProjection.m[3][1] * point.y +
                    viewProjection.m[3][2] * point.z + viewProjection.m[3][3];
                if (clipW <= 1e-4f)
                    continue;
                const float clipX =
                    viewProjection.m[0][0] * point.x + viewProjection.m[0][1] * point.y +
                    viewProjection.m[0][2] * point.z + viewProjection.m[0][3];
                const float clipY =
                    viewProjection.m[1][0] * point.x + viewProjection.m[1][1] * point.y +
                    viewProjection.m[1][2] * point.z + viewProjection.m[1][3];
                // Ogre normalized device coordinates put +1 at the top; the
                // captured image is top-down, hence the Y inversion.
                const float screenX = (clipX / clipW * 0.5f + 0.5f) * static_cast<float>(width);
                const float screenY = (0.5f - clipY / clipW * 0.5f) * static_cast<float>(height);
                if (inFront == 0)
                {
                    minimumX = maximumX = screenX;
                    minimumY = maximumY = screenY;
                }
                else
                {
                    minimumX = (std::min)(minimumX, screenX);
                    maximumX = (std::max)(maximumX, screenX);
                    minimumY = (std::min)(minimumY, screenY);
                    maximumY = (std::max)(maximumY, screenY);
                }
                ++inFront;
            }

            out.cornersInFront = inFront;
            if (inFront == 0)
            {
                out.left = out.top = out.right = out.bottom = 0;
                out.coverage = 0.0f;
                return true;
            }

            const int left = static_cast<int>((std::max)(0.0f,
                (std::min)(static_cast<float>(width), std::floor(minimumX))));
            const int top = static_cast<int>((std::max)(0.0f,
                (std::min)(static_cast<float>(height), std::floor(minimumY))));
            const int right = static_cast<int>((std::max)(0.0f,
                (std::min)(static_cast<float>(width), std::ceil(maximumX))));
            const int bottom = static_cast<int>((std::max)(0.0f,
                (std::min)(static_cast<float>(height), std::ceil(maximumY))));
            out.left = left;
            out.top = top;
            out.right = right;
            out.bottom = bottom;
            const double area = static_cast<double>((std::max)(0, right - left)) *
                static_cast<double>((std::max)(0, bottom - top));
            out.coverage = static_cast<float>(
                area / (static_cast<double>(width) * static_cast<double>(height)));
            return true;
        }

        // Defined near the lifecycle block; name-based liveness probe for the
        // stored proxy entity.
        bool ProxyEntityStillRegistered();

        bool QueryProxyScreenRect(ProxyScreenRect& out)
        {
            out = {};
            if (!g_proxy.proxyCreated || !g_proxy.proxyEntity)
                return false;
            // The render tick has no zone dispatch around it, so the
            // ProxyLost probe that guards the sim path never runs here. The
            // engine can destroy the proxy entity at an unpredictable point
            // (documented asymmetric teardown; the loading screen keeps
            // rendering frames through the window), and this call is the one
            // place a stored proxyEntity pointer would be dereferenced without
            // any registration evidence. Re-probe by name before use.
            if (!ProxyEntityStillRegistered())
            {
                ++g_proxyTickProbeLostCount;
                if (g_proxyTickProbeLostCount <= 4 ||
                    g_proxyTickProbeLostCount % 512 == 0)
                {
                    LogShimA(LogLevel::Warn, "terrain-proxy",
                        "[TERRAIN-PROXY] render-tick probe found proxy entity unregistered losses=%u proxyGeneration=%u missionGeneration=%u",
                        g_proxyTickProbeLostCount, g_proxy.generation,
                        g_missionGeneration);
                }
                return false;
            }
            void* camera = nullptr;
            int width = 0;
            int height = 0;
            if (!GetActiveCamera(camera, width, height))
                return false;
            try
            {
                const AxisAlignedBox* bounds =
                    g_ogre.getWorldBoundingBox(g_proxy.proxyEntity, true);
                if (!bounds || bounds->extent != kAabbExtentFinite)
                    return false;
                out.viewportWidth = width;
                out.viewportHeight = height;
                // Ogre's own frustum test is authoritative for "visible";
                // the projected rect only says where.
                out.visible = g_ogre.cameraBoxVisible(camera, *bounds, nullptr);
                if (!ProjectBoundsToScreen(camera, *bounds, width, height, out))
                    return false;
                out.valid = true;
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        // A capture is only worth writing when the cluster covers enough of the
        // frame to measure. Both conditions are reported so a run that never
        // frames the cluster says so instead of producing static-UI pixels.
        bool ProxyIsFramed(const ProxyScreenRect& rect)
        {
            return rect.valid && rect.visible && rect.cornersInFront > 0 &&
                rect.coverage >= g_config.semanticFrameCaptureMinCoverage;
        }

        // Deterministic in-process frame capture. The stock desktop-screenshot
        // route cannot correlate two runs to the same logical frame; counting
        // terrain dispatches since semantic installation can. Opt-in only.
        // Counts rendered world frames while a proxy exists, so a capture index
        // means the same thing in two runs of the same mission.
        uint32_t g_semanticRenderFrames = 0;
        uint32_t g_semanticFramesWritten = 0;
        uint32_t g_semanticNextCaptureFrame = 0;
        uint32_t g_semanticFramingWaits = 0;
        uint32_t g_semanticFramedStreak = 0;
        bool g_semanticCaptureUnavailable = false;
        bool g_semanticFramingWaitLogged = false;

        // The tick runs during the world render-queue update, so the buffer
        // written by writeContentsToFile is the previously presented frame
        // while the camera matrices describe the frame about to be drawn.
        // Requiring the cluster to be framed for two consecutive frames keeps
        // a capture off that one-frame boundary.
        constexpr uint32_t kFramedStreakRequired = 2;

        // Re-selection state. Selection runs once against whatever camera
        // exists at the time; a live misn04 run showed the chosen cluster
        // sitting entirely behind the gameplay camera (cornersInFront=0) for
        // 12,600 consecutive frames, so an unframed proxy has to be re-chosen
        // or the capture simply never happens. Bounded: each re-selection
        // rebuilds a material and thirteen programs.
        uint32_t g_unframedStreak = 0;
        uint32_t g_reselectCount = 0;
        bool g_reselectRequested = false;
        constexpr uint32_t kMaxReselects = 16;

        void MaybeCaptureSemanticFrame()
        {
            // Gated on the proxy rather than on the semantic material so the
            // packed-UV proxy run produces captures at the same dispatch
            // indices. That is what makes the legacy-vs-semantic comparison
            // correlated instead of two unrelated frames.
            if (g_config.semanticFrameCaptures <= 0 ||
                g_semanticCaptureUnavailable ||
                !g_proxy.proxyCreated ||
                g_semanticFramesWritten >=
                    static_cast<uint32_t>(g_config.semanticFrameCaptures))
                return;
            if (g_semanticRenderFrames < g_semanticNextCaptureFrame)
                return;

            // Framing gate. A capture that does not contain the cluster cannot
            // answer a parity question, so by default the capture slot waits
            // for a framed frame instead of being spent on one.
            ProxyScreenRect rect;
            const bool framingKnown = QueryProxyScreenRect(rect);
            g_semanticFramedStreak = (framingKnown && ProxyIsFramed(rect))
                ? g_semanticFramedStreak + 1 : 0;

            // Ask the rebuild dispatcher to re-choose a cluster when this one
            // has stopped being visible. The request is only raised here; the
            // teardown itself happens at the dispatcher, which is the seam
            // already proven safe for destroying proxy scene objects.
            g_unframedStreak = g_semanticFramedStreak == 0 ? g_unframedStreak + 1 : 0;
            if (g_config.followCamera && g_config.followCameraReselectFrames > 0 &&
                !g_reselectRequested && g_reselectCount < kMaxReselects &&
                g_unframedStreak >=
                    static_cast<uint32_t>(g_config.followCameraReselectFrames))
            {
                g_reselectRequested = true;
                LogShimA(LogLevel::Info, "terrain-proxy",
                    "[TERRAIN-PROXY] follow-camera reselect requested unframedFrames=%u proxyGeneration=%u cluster=(%d,%d) reselects=%u/%u",
                    g_unframedStreak, g_proxy.generation, g_proxy.clusterX,
                    g_proxy.clusterZ, g_reselectCount, kMaxReselects);
            }
            if (g_config.semanticFrameCaptureRequireOnScreen)
            {
                if (!framingKnown)
                {
                    // Never let a diagnostic block the thing it measures: if
                    // framing cannot be evaluated at all, say so once and fall
                    // back to the old fixed-frame behaviour.
                    if (!g_semanticFramingWaitLogged)
                    {
                        g_semanticFramingWaitLogged = true;
                        LogShimA(LogLevel::Warn, "terrain-p3",
                            "[TERRAIN-P3] frame capture framing unavailable; capturing without an on-screen check apiResolved=%d",
                            CaptureFramingApiAvailable() ? 1 : 0);
                    }
                }
                else if (g_semanticFramedStreak < kFramedStreakRequired)
                {
                    // Log the first wait and then periodically: a single record
                    // cannot show whether coverage is trending toward the
                    // threshold or the cluster is simply never framed.
                    const uint32_t waits = ++g_semanticFramingWaits;
                    if (!g_semanticFramingWaitLogged || waits % 600 == 0)
                    {
                        g_semanticFramingWaitLogged = true;
                        LogShimA(LogLevel::Info, "terrain-p3",
                            "[TERRAIN-P3] terrain_semantic: frame_capture waiting for framing renderFrame=%u visible=%d cornersInFront=%d coverage=%.5f minCoverage=%.5f streak=%u waits=%u",
                            g_semanticRenderFrames, rect.visible ? 1 : 0,
                            rect.cornersInFront, static_cast<double>(rect.coverage),
                            static_cast<double>(g_config.semanticFrameCaptureMinCoverage),
                            g_semanticFramedStreak, waits);
                    }
                    return;
                }
            }

            if (!g_ogre.getRoot || !g_ogre.getAutoCreatedWindow ||
                !g_ogre.writeContentsToFile)
            {
                g_semanticCaptureUnavailable = true;
                LogShimA(LogLevel::Warn, "terrain-p3",
                    "[TERRAIN-P3] frame capture unavailable: OGRE render-target exports unresolved");
                return;
            }

            char exePath[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(
                nullptr, exePath, static_cast<DWORD>(sizeof(exePath)));
            if (length == 0 || length >= sizeof(exePath))
                return;
            std::string directory(exePath, length);
            const size_t separator = directory.find_last_of("\\/");
            directory = separator == std::string::npos
                ? std::string() : directory.substr(0, separator + 1);

            char name[128] = {};
            sprintf_s(name, "terrain_semantic_frame_s%dq%dd%d_%02u.png",
                g_config.semanticRenderer ? 1 : 0,
                g_config.semanticLegacyUvQuantization ? 1 : 0,
                g_config.semanticDebugMode, g_semanticFramesWritten);
            const std::string path = directory + name;

            try
            {
                void* root = g_ogre.getRoot();
                void* window = root ? g_ogre.getAutoCreatedWindow(root) : nullptr;
                if (!window)
                {
                    g_semanticCaptureUnavailable = true;
                    LogShimA(LogLevel::Warn, "terrain-p3",
                        "[TERRAIN-P3] frame capture unavailable: no auto-created render window");
                    return;
                }
                g_ogre.writeContentsToFile(window, path);
                ++g_semanticFramesWritten;
                g_semanticNextCaptureFrame = g_semanticRenderFrames +
                    static_cast<uint32_t>(g_config.semanticFrameCaptureStride);
                // The rect is emitted in the exact form the parity harness
                // feeds back as -Region, so metrics can be restricted to the
                // cluster instead of scoring HUD and sky as mismatches.
                LogShimA(LogLevel::Info, "terrain-p3",
                    "[TERRAIN-P3] terrain_semantic: frame_capture index=%u renderFrame=%u debug=%s legacyUVQuantization=%d framed=%d visible=%d cornersInFront=%d coverage=%.5f viewport=%dx%d region=%d,%d,%d,%d waits=%u path=\"%s\"",
                    g_semanticFramesWritten, g_semanticRenderFrames,
                    SemanticDebugModeName(g_config.semanticDebugMode),
                    g_config.semanticLegacyUvQuantization ? 1 : 0,
                    framingKnown ? (ProxyIsFramed(rect) ? 1 : 0) : -1,
                    framingKnown ? (rect.visible ? 1 : 0) : -1,
                    framingKnown ? rect.cornersInFront : -1,
                    static_cast<double>(framingKnown ? rect.coverage : 0.0f),
                    rect.viewportWidth, rect.viewportHeight,
                    rect.left, rect.top,
                    (std::max)(0, rect.right - rect.left),
                    (std::max)(0, rect.bottom - rect.top),
                    g_semanticFramingWaits, path.c_str());
            }
            catch (...)
            {
                g_semanticCaptureUnavailable = true;
                LogShimA(LogLevel::Warn, "terrain-p3",
                    "[TERRAIN-P3] frame capture raised an OGRE exception; capture disabled path=\"%s\"",
                    path.c_str());
            }
        }

        bool TerrainHdApiAvailable()
        {
            return g_ogre.getNumTextureUnitStates &&
                g_ogre.getTextureUnitState && g_ogre.setTexture &&
                g_ogre.getTextureManager && g_ogre.loadTexture &&
                g_ogre.createManualTexture && g_ogre.getTextureWidth &&
                g_ogre.getTextureHeight && g_ogre.getTextureDepth &&
                g_ogre.getTextureMipmaps && g_ogre.getTextureType &&
                g_ogre.getTextureFormat && g_ogre.blitPixelBuffer &&
                ResolveD3D11TextureApi();
        }

        void RemoveTerrainHdTextureResource(const char* reason)
        {
            if (g_proxy.hdTextureName.empty())
                return;
            try
            {
                if (g_ogre.getTextureManager && g_ogre.removeResource)
                {
                    if (void* manager = g_ogre.getTextureManager())
                        g_ogre.removeResource(manager, g_proxy.hdTextureName);
                }
            }
            catch (...)
            {
                LogShimA(LogLevel::Warn, "terrain-hd",
                    "[TERRAIN-HD] texture removal raised an OGRE exception name=\"%s\"",
                    g_proxy.hdTextureName.c_str());
            }
            LogShimA(LogLevel::Info, "terrain-hd",
                "[TERRAIN-HD] texture released reason=%s name=\"%s\" slices=%u size=%ux%u mips=%u",
                reason, g_proxy.hdTextureName.c_str(), g_proxy.hdSliceCount,
                g_proxy.hdWidth, g_proxy.hdHeight, g_proxy.hdMipmaps + 1);
            g_proxy.hdTextureName.clear();
            g_proxy.hdDiffuseFallback.clear();
            g_proxy.hdSliceCount = 0;
            g_proxy.hdWidth = 0;
            g_proxy.hdHeight = 0;
            g_proxy.hdMipmaps = 0;
        }

        bool LoadTerrainHdSourceTexture(void* textureManager,
                                        const std::string& resource,
                                        OgreSharedPtr& texture)
        {
            const std::string autodetect = "Autodetect";
            g_ogre.loadTexture(textureManager, &texture, resource, autodetect,
                kOgreTextureType2D, kOgreMipDefault, 1.0f, false,
                kOgrePixelFormatUnknown, false);
            return texture.rep && texture.info &&
                g_ogre.getTextureType(texture.rep) == kOgreTextureType2D;
        }

        bool CopyTerrainHdSlice(void* arrayTexture,
                                void* sourceTexture,
                                uint32_t slice,
                                uint32_t width,
                                uint32_t height,
                                uint32_t mipmaps)
        {
            for (uint32_t mip = 0; mip <= mipmaps; ++mip)
            {
                OgreSharedPtr sourceBuffer;
                OgreSharedPtr destinationBuffer;
                g_ogre.getTextureBuffer(sourceTexture, &sourceBuffer, 0, mip);
                g_ogre.getTextureBuffer(arrayTexture, &destinationBuffer, 0, mip);
                if (!sourceBuffer.rep || !sourceBuffer.info ||
                    !destinationBuffer.rep || !destinationBuffer.info)
                {
                    ReleaseCloneHandoff(sourceBuffer);
                    ReleaseCloneHandoff(destinationBuffer);
                    return false;
                }
                const uint32_t mipWidth = (std::max)(1u, width >> mip);
                const uint32_t mipHeight = (std::max)(1u, height >> mip);
                const OgreBox sourceBox = {
                    0, 0, mipWidth, mipHeight, 0, 1
                };
                const OgreBox destinationBox = {
                    0, 0, mipWidth, mipHeight, slice, slice + 1
                };
                g_ogre.blitPixelBuffer(destinationBuffer.rep, sourceBuffer,
                    sourceBox, destinationBox);
                ReleaseCloneHandoff(sourceBuffer);
                ReleaseCloneHandoff(destinationBuffer);
            }
            return true;
        }

        // Reports which array slices the selected cluster actually samples, and
        // whether those slices carry distinct manifest images. This decides
        // whether the run can demonstrate anything: if every tile index the
        // cluster uses resolves to the same fallback image, the terrain will
        // render plausibly no matter how wrong the slice mapping is, and a
        // visual "looks right" would be worth nothing.
        void LogTerrainHdTileCoverage(const TerrainHdMaterialBinding& binding)
        {
            std::map<uint32_t, uint32_t> usage;
            for (const TerrainSemantic::Vertex& vertex : g_proxy.semanticVertices)
                ++usage[static_cast<uint32_t>(vertex.gpu.tileIndex)];
            if (usage.empty())
            {
                LogShimA(LogLevel::Warn, "terrain-hd",
                    "[TERRAIN-HD] tile coverage unavailable: no semantic vertices for the selected cluster");
                return;
            }

            size_t overridden = 0;
            std::string detail;
            for (const auto& entry : usage)
            {
                const bool hasOverride =
                    binding.tiles.find(entry.first) != binding.tiles.end();
                if (hasOverride)
                    ++overridden;
                if (!detail.empty())
                    detail += ",";
                char item[64] = {};
                sprintf_s(item, "%u:%s:%u", entry.first,
                    hasOverride ? "override" : "fallback", entry.second);
                detail += item;
            }

            LogShimA(LogLevel::Info, "terrain-hd",
                "[TERRAIN-HD] tile coverage material=\"%s\" distinctTiles=%zu overridden=%zu fallbackOnly=%zu tiles=[%s]",
                g_proxy.materialName.c_str(), usage.size(), overridden,
                usage.size() - overridden, detail.c_str());

            if (overridden == 0)
            {
                LogShimA(LogLevel::Warn, "terrain-hd",
                    "[TERRAIN-HD] every slice this cluster samples holds the fallback image; a correct-looking frame would not prove slice selection. Add manifest overrides for the tile indices above.");
            }
            else if (usage.size() < 2)
            {
                LogShimA(LogLevel::Warn, "terrain-hd",
                    "[TERRAIN-HD] the cluster samples a single tile index, so this frame cannot distinguish correct slice ordering from a constant slice. Select a cluster spanning a transition.");
            }
        }

        bool BuildTerrainHdTextureArray(
            const TerrainHdMaterialBinding& binding,
            OgreSharedPtr& arrayTexture)
        {
            if (!TerrainHdApiAvailable())
            {
                LogShimA(LogLevel::Warn, "terrain-hd",
                    "[TERRAIN-HD] required Ogre/D3D11 texture APIs unresolved; stock atlas retained");
                return false;
            }
            uint32_t maximumTileIndex = 0;
            for (const TerrainSemantic::Vertex& vertex : g_proxy.semanticVertices)
                maximumTileIndex = (std::max)(maximumTileIndex,
                    static_cast<uint32_t>(vertex.gpu.tileIndex));
            if (maximumTileIndex >= binding.sliceCount)
            {
                LogShimA(LogLevel::Warn, "terrain-hd",
                    "[TERRAIN-HD] manifest has too few slices material=\"%s\" slices=%u selectedMaxTileIndex=%u; stock atlas retained",
                    g_proxy.materialName.c_str(), binding.sliceCount,
                    maximumTileIndex);
                return false;
            }

            void* textureManager = g_ogre.getTextureManager();
            if (!textureManager)
                return false;
            OgreSharedPtr fallbackTexture;
            try
            {
                if (!LoadTerrainHdSourceTexture(textureManager,
                        binding.fallback, fallbackTexture))
                {
                    LogShimA(LogLevel::Warn, "terrain-hd",
                        "[TERRAIN-HD] fallback texture failed resource=\"%s\"; stock atlas retained",
                        binding.fallback.c_str());
                    ReleaseCloneHandoff(fallbackTexture);
                    return false;
                }
                const uint32_t width = g_ogre.getTextureWidth(fallbackTexture.rep);
                const uint32_t height = g_ogre.getTextureHeight(fallbackTexture.rep);
                const uint32_t mipmaps = g_ogre.getTextureMipmaps(fallbackTexture.rep);
                const int format = g_ogre.getTextureFormat(fallbackTexture.rep);
                if (width == 0 || height == 0 || format == kOgrePixelFormatUnknown)
                {
                    ReleaseCloneHandoff(fallbackTexture);
                    return false;
                }

                g_proxy.hdTextureName = "OpenShim/TerrainHD/Diffuse/" +
                    std::to_string(g_proxy.generation) + "/" +
                    std::to_string(g_proxy.semanticMaterialGeneration);
                const std::string group = "General";
                const std::string empty;
                g_ogre.createManualTexture(textureManager, &arrayTexture,
                    g_proxy.hdTextureName, group, kOgreTextureType2DArray,
                    width, height, binding.sliceCount,
                    static_cast<int>(mipmaps), format,
                    kOgreTextureUsageStaticWriteOnly, nullptr, false, 0, empty);
                if (!arrayTexture.rep || !arrayTexture.info ||
                    g_ogre.getTextureType(arrayTexture.rep) !=
                        kOgreTextureType2DArray ||
                    g_ogre.getTextureDepth(arrayTexture.rep) < binding.sliceCount)
                {
                    LogShimA(LogLevel::Warn, "terrain-hd",
                        "[TERRAIN-HD] Ogre failed to create array name=\"%s\" slices=%u; stock atlas retained",
                        g_proxy.hdTextureName.c_str(), binding.sliceCount);
                    ReleaseCloneHandoff(fallbackTexture);
                    ReleaseCloneHandoff(arrayTexture);
                    RemoveTerrainHdTextureResource("create-failed");
                    return false;
                }

                size_t overrideCopies = 0;
                for (uint32_t slice = 0; slice < binding.sliceCount; ++slice)
                {
                    const auto overrideIt = binding.tiles.find(slice);
                    const std::string& resource = overrideIt != binding.tiles.end()
                        ? overrideIt->second : binding.fallback;
                    OgreSharedPtr sourceTexture;
                    void* source = fallbackTexture.rep;
                    if (resource != binding.fallback)
                    {
                        if (!LoadTerrainHdSourceTexture(textureManager,
                                resource, sourceTexture))
                        {
                            LogShimA(LogLevel::Warn, "terrain-hd",
                                "[TERRAIN-HD] tile load failed slice=%u resource=\"%s\"; stock atlas retained",
                                slice, resource.c_str());
                            ReleaseCloneHandoff(sourceTexture);
                            throw std::runtime_error("tile load failed");
                        }
                        source = sourceTexture.rep;
                        ++overrideCopies;
                    }
                    if (g_ogre.getTextureWidth(source) != width ||
                        g_ogre.getTextureHeight(source) != height ||
                        g_ogre.getTextureMipmaps(source) != mipmaps ||
                        g_ogre.getTextureFormat(source) != format ||
                        !CopyTerrainHdSlice(arrayTexture.rep, source, slice,
                            width, height, mipmaps))
                    {
                        LogShimA(LogLevel::Warn, "terrain-hd",
                            "[TERRAIN-HD] tile contract/copy failed slice=%u resource=\"%s\" expected=%ux%u mips=%u format=%d; stock atlas retained",
                            slice, resource.c_str(), width, height, mipmaps + 1,
                            format);
                        ReleaseCloneHandoff(sourceTexture);
                        throw std::runtime_error("tile contract/copy failed");
                    }
                    ReleaseCloneHandoff(sourceTexture);
                }

                ReleaseCloneHandoff(fallbackTexture);
                g_proxy.hdDiffuseFallback = binding.fallback;
                g_proxy.hdSliceCount = binding.sliceCount;
                g_proxy.hdWidth = width;
                g_proxy.hdHeight = height;
                g_proxy.hdMipmaps = mipmaps;
                LogShimA(LogLevel::Info, "terrain-hd",
                    "[TERRAIN-HD] array ready material=\"%s\" name=\"%s\" slices=%u overrides=%zu selectedMaxTileIndex=%u size=%ux%u mips=%u format=%d fallback=\"%s\"",
                    g_proxy.materialName.c_str(), g_proxy.hdTextureName.c_str(),
                    binding.sliceCount, overrideCopies, maximumTileIndex,
                    width, height, mipmaps + 1, format,
                    binding.fallback.c_str());
                LogTerrainHdTileCoverage(binding);
                return true;
            }
            catch (...)
            {
                ReleaseCloneHandoff(fallbackTexture);
                ReleaseCloneHandoff(arrayTexture);
                RemoveTerrainHdTextureResource("build-failed");
                return false;
            }
        }

        void RemoveSemanticResources(const char* reason)
        {
            const bool hadMaterial = !g_proxy.semanticMaterialName.empty();
            const size_t programCount = g_proxy.semanticProgramNames.size();
            if (!hadMaterial && programCount == 0 &&
                g_proxy.hdTextureName.empty())
            {
                g_proxy.semanticMaterialInstalled = false;
                return;
            }
            try
            {
                if (hadMaterial && g_ogre.getMaterialManager && g_ogre.removeResource)
                {
                    if (void* manager = g_ogre.getMaterialManager())
                    {
                        g_ogre.removeResource(manager, g_proxy.semanticMaterialName);
                        ++g_semanticMaterialRemoved;
                    }
                }
                if (programCount != 0 &&
                    g_ogre.getHighLevelProgramManager && g_ogre.removeResource)
                {
                    if (void* manager = g_ogre.getHighLevelProgramManager())
                    {
                        for (const std::string& name : g_proxy.semanticProgramNames)
                        {
                            g_ogre.removeResource(manager, name);
                            ++g_semanticProgramsRemovedTotal;
                        }
                    }
                }
            }
            catch (...)
            {
                LogShimA(LogLevel::Warn, "terrain-p3",
                    "[TERRAIN-P3] semantic material/program resource removal raised an OGRE exception");
            }
            LogShimA(LogLevel::Info, "terrain-p3",
                "[TERRAIN-P3] terrain_semantic_shader: destroy reason=%s materialGeneration=%u material=\"%s\" programs=%zu totals={materialCreated:%u,materialRemoved:%u,programsCreated:%u,programsRemoved:%u}",
                reason, g_proxy.semanticMaterialGeneration,
                g_proxy.semanticMaterialName.c_str(), programCount,
                g_semanticMaterialCreated, g_semanticMaterialRemoved,
                g_semanticProgramsCreatedTotal, g_semanticProgramsRemovedTotal);
            g_proxy.semanticMaterialName.clear();
            g_proxy.semanticProgramNames.clear();
            g_proxy.semanticMaterialInstalled = false;
            g_proxy.semanticProgramsCreated = 0;
            g_proxy.semanticProgramsReused = 0;
            g_proxy.semanticPassesSpecialized = 0;
            g_proxy.semanticPassesSeen = 0;
            g_proxy.semanticFragmentProgramsCreated = 0;
            RemoveTerrainHdTextureResource(reason);
        }

        // The slot-3 buffer lives inside the proxy mesh's VertexBufferBinding,
        // so the SceneManager/Mesh owner destroys it. This only forgets the
        // shim-side identity and records that the generation went away.
        void ReleaseSemanticStreamOwnership(const char* reason)
        {
            if (!g_proxy.semanticStreamInstalled && !g_proxy.semanticBuffer)
                return;
            ++g_semanticVbReleased;
            LogShimA(LogLevel::Info, "terrain-p3",
                "[TERRAIN-P3] terrain_semantic: destroy reason=%s vbGeneration=%u vb=%p proxyGeneration=%u uploads=%u builds=%u unchangedBuilds=%u totals={created:%u,released:%u,handoffRetained:%u}",
                reason, g_proxy.semanticVbGeneration, g_proxy.semanticBuffer,
                g_proxy.generation, g_proxy.semanticUploadCount,
                g_proxy.semanticBuildCount, g_proxy.semanticUnchangedCount,
                g_semanticVbCreated, g_semanticVbReleased,
                g_semanticVbHandoffRetained);
            g_proxy.semanticStreamInstalled = false;
            g_proxy.semanticBuffer = nullptr;
            g_proxy.semanticVbGeneration = 0;
            g_proxy.semanticDataHash = 0;
            g_proxy.semanticBindingSignature = 0;
        }

        // Phase 3B changes only the diffuse sample. Detail, normal, specular,
        // emissive, shadow and IBL inputs retain the stock atlas UV. The debug
        // visualization can additionally replace final shading as in Phase 3A.
        bool BuildSemanticFragmentSource(
            const std::string& source,
            bool debugColor,
            bool hdDiffuse,
            std::string& output)
        {
            output = source;
            if (hdDiffuse)
            {
                static const char kDiffuseDeclaration[] =
                    "uniform Texture2D diffuseMap : register(t0),";
                static const char kFragmentUv[] =
                    "in float2 vTexCoord : TEXCOORD0,";
                static const char kDiffuseSample[] =
                    "diffuseMap.Sample(diffuseSam, vTexCoord)";
                const size_t declaration = output.find(kDiffuseDeclaration);
                const size_t fragmentUv = output.find(kFragmentUv);
                const size_t sample = output.find(kDiffuseSample);
                if (declaration == std::string::npos ||
                    fragmentUv == std::string::npos ||
                    sample == std::string::npos)
                {
                    output.clear();
                    return false;
                }
                output.replace(declaration, sizeof(kDiffuseDeclaration) - 1,
                    "uniform Texture2DArray diffuseMap : register(t0),");
                const size_t shiftedFragmentUv = output.find(kFragmentUv);
                output.insert(shiftedFragmentUv + sizeof(kFragmentUv) - 1,
                    "\n    in float2 openShimHdUV : TEXCOORD9,"
                    "\n    in float openShimTileSlice : TEXCOORD10,");
                const size_t shiftedSample = output.find(kDiffuseSample);
                output.replace(shiftedSample, sizeof(kDiffuseSample) - 1,
                    "diffuseMap.Sample(diffuseSam, float3(openShimHdUV, openShimTileSlice))");
            }

            if (debugColor)
            {
                static const char kAlphaToken[] = "oColor.a = vColor.a;";
                const size_t alpha = output.find(kAlphaToken);
                if (alpha == std::string::npos)
                {
                    output.clear();
                    return false;
                }
                output.replace(alpha, sizeof(kAlphaToken) - 1,
                    "oColor = float4(saturate(vColor.xyz), 1.0);");
            }
            return true;
        }

        std::string BuildSemanticDebugExpression(int debugMode)
        {
            switch (debugMode)
            {
            case kSemanticDebugTileIndex:
                return "OpenShimSemanticTileColor(openShimSemantic.x)";
            case kSemanticDebugOrientation:
                return "OpenShimSemanticPalette(openShimSemantic.y)";
            case kSemanticDebugTypeA:
                return "OpenShimSemanticPalette(openShimSemantic.z)";
            case kSemanticDebugTypeB:
                return "OpenShimSemanticPalette(openShimSemantic.w)";
            case kSemanticDebugLocalUv:
                return "float3(openShimOrientedUV, 0.0)";
            case kSemanticDebugAtlasRect:
                return "float3(openShimAtlasRect.xy, openShimAtlasRect.z * 8.0)";
            case kSemanticDebugUvDelta:
                return "float3(saturate(abs(vTexCoord - openShimStockUV) * 640.0), 0.0)";
            default:
                return std::string();
            }
        }

        // debugColorInstalled reports whether the false-colour assignment was
        // actually written into this permutation. The fragment specialization
        // is only valid for a pass whose vertex program carries that colour;
        // see the call site.
        bool BuildSemanticProgramSource(
            const std::string& source,
            bool legacyQuantization,
            bool hdDiffuse,
            int debugMode,
            const std::string& programName,
            std::string& output,
            bool& debugColorInstalled)
        {
            debugColorInstalled = false;
            output = source;
            const std::string heightToken = "heightOffset : TEXCOORD1,";
            const size_t signature = output.find(heightToken);
            const size_t stockUvToken = output.find("vTexCoord =");
            const size_t function = output.find("void terrain_vertex(");
            if (signature == std::string::npos ||
                stockUvToken == std::string::npos ||
                function == std::string::npos)
            {
                output.clear();
                return false;
            }
            size_t stockUvLineEnd = output.find('\n', stockUvToken);
            if (stockUvLineEnd == std::string::npos)
                stockUvLineEnd = output.size();
            size_t stockUvLineStart = output.rfind('\n', stockUvToken);
            stockUvLineStart = stockUvLineStart == std::string::npos
                ? 0 : stockUvLineStart + 1;
            const std::string stockUvLine = output.substr(
                stockUvLineStart, stockUvLineEnd - stockUvLineStart);
            if (stockUvLine.find("iBlendIndices") == std::string::npos ||
                stockUvLine.find("160.0") == std::string::npos)
            {
                output.clear();
                return false;
            }
            const bool stockUsesHalfTexel =
                stockUvLine.find("0.5") != std::string::npos;

            static const char kOrientationHelper[] = R"HLSL(
float2 OpenShimApplyTerrainOrientation(float2 uv, uint orientation)
{
    switch (orientation & 15u)
    {
        case 0u: case 8u:  return float2(uv.x, 1.0 - uv.y);
        case 1u: case 9u:  return float2(uv.y, uv.x);
        case 2u: case 10u: return float2(1.0 - uv.x, uv.y);
        case 3u: case 11u: return float2(1.0 - uv.y, 1.0 - uv.x);
        case 4u: case 15u: return float2(1.0 - uv.x, 1.0 - uv.y);
        case 5u: case 12u: return float2(1.0 - uv.y, uv.x);
        case 6u: case 13u: return uv;
        default:            return float2(uv.y, 1.0 - uv.x);
    }
}

// Sixteen deliberately separated colors. Values 8..15 must stay visually
// distinct from 0..7 so an accidental `mix & 7` collapse is obvious on screen.
float3 OpenShimSemanticPalette(uint index)
{
    switch (index & 15u)
    {
        case  0u: return float3(0.10, 0.10, 0.10);
        case  1u: return float3(0.85, 0.10, 0.10);
        case  2u: return float3(0.10, 0.85, 0.10);
        case  3u: return float3(0.10, 0.10, 0.95);
        case  4u: return float3(0.90, 0.90, 0.10);
        case  5u: return float3(0.90, 0.10, 0.90);
        case  6u: return float3(0.10, 0.90, 0.90);
        case  7u: return float3(0.98, 0.98, 0.98);
        case  8u: return float3(0.45, 0.22, 0.05);
        case  9u: return float3(0.95, 0.50, 0.10);
        case 10u: return float3(0.55, 0.90, 0.20);
        case 11u: return float3(0.05, 0.45, 0.30);
        case 12u: return float3(0.35, 0.35, 0.95);
        case 13u: return float3(0.65, 0.20, 0.75);
        case 14u: return float3(0.20, 0.55, 0.85);
        default:  return float3(0.55, 0.55, 0.55);
    }
}

float3 OpenShimSemanticTileColor(uint tileIndex)
{
    uint mixed = tileIndex * 2654435761u;
    float3 rgb = float3(
        float((mixed >>  0u) & 255u),
        float((mixed >> 11u) & 255u),
        float((mixed >> 21u) & 255u)) / 255.0;
    return saturate(rgb * 0.8 + 0.15);
}

)HLSL";
            output.insert(function, kOrientationHelper);

            const size_t shiftedSignature = output.find(heightToken);
            const size_t signatureLineEnd = output.find('\n', shiftedSignature);
            if (signatureLineEnd == std::string::npos)
            {
                output.clear();
                return false;
            }
            static const char kSemanticInputs[] = R"HLSL(
	in float2 openShimLocalUV : TEXCOORD2,
	in uint4 openShimSemantic : TEXCOORD3,
	in float4 openShimAtlasRect : TEXCOORD4,
)HLSL";
            output.insert(signatureLineEnd + 1, kSemanticInputs);

            if (hdDiffuse)
            {
                static const char kVertexUvOutput[] =
                    "out float2 vTexCoord : TEXCOORD0,";
                const size_t vertexUv = output.find(kVertexUvOutput);
                if (vertexUv == std::string::npos)
                {
                    output.clear();
                    return false;
                }
                output.insert(vertexUv + sizeof(kVertexUvOutput) - 1,
                    "\n    out float2 openShimHdUV : TEXCOORD9,"
                    "\n    out float openShimTileSlice : TEXCOORD10,");
            }

            const size_t shiftedStockUvToken = output.find("vTexCoord =");
            size_t shiftedStockUvLineStart = output.rfind(
                '\n', shiftedStockUvToken);
            shiftedStockUvLineStart = shiftedStockUvLineStart ==
                std::string::npos ? 0 : shiftedStockUvLineStart + 1;
            size_t shiftedStockUvLineEnd = output.find(
                '\n', shiftedStockUvToken);
            if (shiftedStockUvLineEnd == std::string::npos)
                shiftedStockUvLineEnd = output.size();

            // Keep the stock packed-UV expression verbatim, renamed to a local.
            // The HD diffuse sample bypasses it while the other stock maps keep
            // using atlas UV; retaining it also lets the parity debug mode
            // difference both paths inside a single frame.
            std::string stockUvStatement = output.substr(
                shiftedStockUvLineStart,
                shiftedStockUvLineEnd - shiftedStockUvLineStart);
            const size_t stockAssignment = stockUvStatement.find("vTexCoord");
            if (stockAssignment == std::string::npos)
            {
                output.clear();
                return false;
            }
            stockUvStatement.replace(stockAssignment,
                sizeof("vTexCoord") - 1, "float2 openShimStockUV");

            std::string semanticUv = stockUvStatement;
            semanticUv += R"HLSL(
    float2 openShimOrientedUV = OpenShimApplyTerrainOrientation(
        openShimLocalUV, openShimSemantic.y);
    float2 openShimAtlasUV = openShimAtlasRect.xy +
        openShimOrientedUV * openShimAtlasRect.zw;
)HLSL";
            if (hdDiffuse)
            {
                semanticUv += R"HLSL(    openShimHdUV = openShimOrientedUV;
    openShimTileSlice = float(openShimSemantic.x);
)HLSL";
            }
            if (legacyQuantization)
            {
                semanticUv += R"HLSL(    float2 openShimPackedUV = clamp(
        floor(openShimAtlasUV * 160.0), 0.0, 255.0);
    vTexCoord = (openShimPackedUV + )HLSL";
                semanticUv += stockUsesHalfTexel ? "0.5" : "0.0";
                semanticUv += ") / 160.0;";
            }
            else
            {
                semanticUv += "    vTexCoord = openShimAtlasUV;";
            }
            output.replace(shiftedStockUvLineStart,
                shiftedStockUvLineEnd - shiftedStockUvLineStart,
                semanticUv);

            const std::string debugExpression =
                BuildSemanticDebugExpression(debugMode);
            if (debugExpression.empty())
                return true;

            static const char kVertexColorToken[] = "vColor = iColor.bgra;";
            const size_t vertexColor = output.find(kVertexColorToken);
            if (vertexColor == std::string::npos)
            {
                // Fail soft: normal semantic rendering still works, only the
                // debug overlay is unavailable for this program permutation.
                LogShimA(LogLevel::Warn, "terrain-p3",
                    "[TERRAIN-P3] semantic debug skipped: COLOR0 assignment not found in vertex program \"%s\"",
                    programName.c_str());
                return true;
            }
            std::string debugAssignment = "\n    vColor = float4(";
            debugAssignment += debugExpression;
            debugAssignment += ", 1.0);";
            output.insert(vertexColor + sizeof(kVertexColorToken) - 1,
                debugAssignment);
            debugColorInstalled = true;
            return true;
        }

        bool InstallOrRefreshSemanticStream()
        {
            if (!g_config.semanticRenderer || !g_proxy.proxyCreated ||
                g_proxy.semanticVertices.size() != TerrainSemantic::kVertexCount)
                return false;
            try
            {
                RenderOperation operation = {};
                void* subEntity = nullptr;
                if (!GetEntityOperation(g_proxy.proxyEntity, operation, subEntity))
                {
                    LogShimA(LogLevel::Warn, "terrain-p3",
                        "[TERRAIN-P3] semantic stream failed: proxy render operation unavailable");
                    return false;
                }

                std::vector<TerrainSemantic::GpuVertex> upload;
                upload.reserve(g_proxy.semanticVertices.size());
                for (const TerrainSemantic::Vertex& vertex : g_proxy.semanticVertices)
                    upload.push_back(vertex.gpu);
                const uint32_t byteCount = static_cast<uint32_t>(
                    upload.size() * sizeof(TerrainSemantic::GpuVertex));
                const uint32_t dataHash = HashBytes(upload.data(), byteCount);

                if (g_proxy.semanticStreamInstalled)
                {
                    void* buffer = nullptr;
                    if (!GetVertexBuffer(operation, 3, buffer) ||
                        g_ogre.getBufferSize(buffer) != byteCount)
                    {
                        LogShimA(LogLevel::Warn, "terrain-p3",
                            "[TERRAIN-P3] semantic stream refresh failed: slot 3 unavailable or size changed");
                        return false;
                    }
                    if (buffer != g_proxy.semanticBuffer)
                    {
                        // The owner replaced the bound resource underneath us.
                        // Adopt it under a new generation rather than keeping a
                        // stale identity that would defeat the audit.
                        LogShimA(LogLevel::Warn, "terrain-p3",
                            "[TERRAIN-P3] terrain_semantic: slot 3 resource replaced by owner previous=%p current=%p vbGeneration=%u",
                            g_proxy.semanticBuffer, buffer,
                            g_proxy.semanticVbGeneration);
                        g_proxy.semanticBuffer = buffer;
                        g_proxy.semanticVbGeneration = ++g_semanticVbSerial;
                        g_proxy.semanticDataHash = 0;
                    }
                    if (dataHash == g_proxy.semanticDataHash)
                    {
                        // Tile semantics did not change; the existing GPU copy
                        // is still authoritative and is intentionally retained.
                        ++g_proxy.semanticUnchangedCount;
                        return true;
                    }
                    if (!WriteD3D11VertexBuffer(
                            buffer, upload.data(), byteCount))
                    {
                        LogShimA(LogLevel::Warn, "terrain-p3",
                            "[TERRAIN-P3] semantic stream refresh failed: D3D11 upload failed");
                        return false;
                    }
                    g_proxy.semanticDataHash = dataHash;
                    ++g_proxy.semanticUploadCount;
                    LogShimA(LogLevel::Info, "terrain-p3",
                        "[TERRAIN-P3] terrain_semantic: refresh vbGeneration=%u vb=%p bytes=%u dataHash=%08X uploads=%u",
                        g_proxy.semanticVbGeneration, buffer, byteCount,
                        dataHash, g_proxy.semanticUploadCount);
                    return true;
                }

                void* manager = g_ogre.getHardwareBufferManager();
                if (!manager || !operation.vertexData->declaration ||
                    !operation.vertexData->binding)
                {
                    LogShimA(LogLevel::Warn, "terrain-p3",
                        "[TERRAIN-P3] semantic stream failed: manager=%p declaration=%p binding=%p",
                        manager, operation.vertexData->declaration,
                        operation.vertexData->binding);
                    return false;
                }
                OgreSharedPtr buffer;
                g_ogre.createVertexBuffer(manager, &buffer,
                    static_cast<uint32_t>(sizeof(TerrainSemantic::GpuVertex)),
                    static_cast<uint32_t>(upload.size()), 14, false);
                if (!buffer.rep || !buffer.info)
                {
                    LogShimA(LogLevel::Warn, "terrain-p3",
                        "[TERRAIN-P3] semantic stream failed: createVertexBuffer returned rep=%p info=%p",
                        buffer.rep, buffer.info);
                    return false;
                }
                if (!WriteD3D11VertexBuffer(
                        buffer.rep, upload.data(), byteCount))
                {
                    LogShimA(LogLevel::Warn, "terrain-p3",
                        "[TERRAIN-P3] semantic stream failed: initial D3D11 upload failed bytes=%u",
                        byteCount);
                    ReleaseCloneHandoff(buffer);
                    return false;
                }

                // OGRE 1.10: VET_FLOAT2=1, VET_UBYTE4=9,
                // VET_FLOAT4=3, VES_TEXTURE_COORDINATES=7.
                g_ogre.addVertexElement(operation.vertexData->declaration,
                    3, 0, 1, 7, 2);
                g_ogre.addVertexElement(operation.vertexData->declaration,
                    3, 8, 9, 7, 3);
                g_ogre.addVertexElement(operation.vertexData->declaration,
                    3, 12, 3, 7, 4);
                g_ogre.setVertexBinding(operation.vertexData->binding, 3, buffer);
                void* const installedBuffer = buffer.rep;
                if (!ReleaseCloneHandoff(buffer))
                {
                    ++g_semanticVbHandoffRetained;
                    LogShimA(LogLevel::Warn, "terrain-p3",
                        "[TERRAIN-P3] retained semantic buffer handoff reference for safety retained=%u",
                        g_semanticVbHandoffRetained);
                }
                g_proxy.semanticStreamInstalled = true;
                g_proxy.semanticBuffer = installedBuffer;
                g_proxy.semanticVbGeneration = ++g_semanticVbSerial;
                g_proxy.semanticDataHash = dataHash;
                ++g_proxy.semanticUploadCount;
                ++g_semanticVbCreated;
                LogShimA(LogLevel::Info, "terrain-p3",
                    "[TERRAIN-P3] terrain_semantic: create generation=%u vertices=%zu stride=%zu bytes=%u vb=%p dataHash=%08X layout=TEXCOORD2(float2)+TEXCOORD3(ubyte4)+TEXCOORD4(float4) totals={created:%u,released:%u}",
                    g_proxy.semanticVbGeneration, upload.size(),
                    sizeof(TerrainSemantic::GpuVertex), byteCount,
                    installedBuffer, dataHash, g_semanticVbCreated,
                    g_semanticVbReleased);
                ReportSemanticBinding("bind", true);
                return true;
            }
            catch (...)
            {
                LogShimA(LogLevel::Warn, "terrain-p3",
                    "[TERRAIN-P3] semantic stream installation failed; stock material retained");
                return false;
            }
        }

        bool InstallSemanticMaterial()
        {
            if (!g_config.semanticRenderer || !g_proxy.proxyCreated ||
                !g_proxy.semanticStreamInstalled || g_proxy.materialName.empty())
                return false;
            if (g_proxy.semanticMaterialInstalled)
                return true;
            if (g_proxy.semanticMaterialUnsupported)
            {
                // A material that produced no compatible DX11 terrain vertex
                // program will not become compatible on a later dirty event.
                // Retrying would clone a fresh material per rebuild.
                return false;
            }

            try
            {
                void* materialManager = g_ogre.getMaterialManager();
                void* programManager = g_ogre.getHighLevelProgramManager();
                if (!materialManager || !programManager)
                    return false;

                const std::string autodetect = "Autodetect";
                OgreSharedPtr sourceMaterial;
                g_ogre.getMaterialByName(materialManager, &sourceMaterial,
                    g_proxy.materialName, autodetect);
                if (!sourceMaterial.rep || !sourceMaterial.info)
                    return false;

                // The material generation is a process-lifetime serial, so a
                // recreated cluster (new mission, material change, A->B->A)
                // can never collide with a name the resource manager may still
                // be holding.
                g_proxy.semanticMaterialGeneration = ++g_semanticMaterialSerial;
                const std::string generationSuffix =
                    std::to_string(g_proxy.generation) + "/" +
                    std::to_string(g_proxy.semanticMaterialGeneration);
                g_proxy.semanticMaterialName =
                    "OpenShim/TerrainSemantic/Material/" + generationSuffix;
                OgreSharedPtr semanticMaterial;
                const std::string empty;
                g_ogre.cloneMaterial(sourceMaterial.rep, &semanticMaterial,
                    g_proxy.semanticMaterialName, false, empty);
                ReleaseCloneHandoff(sourceMaterial);
                if (!semanticMaterial.rep || !semanticMaterial.info)
                    return false;

                OgreSharedPtr hdDiffuseArray;
                bool hdDiffuseReady = false;
                if (g_config.hdEnabled)
                {
                    const TerrainHdMaterialBinding* binding =
                        FindTerrainHdBinding(g_proxy.materialName);
                    if (!binding)
                    {
                        LogShimA(LogLevel::Warn, "terrain-hd",
                            "[TERRAIN-HD] no manifest binding for material=\"%s\"; stock atlas retained",
                            g_proxy.materialName.c_str());
                    }
                    else
                    {
                        hdDiffuseReady = BuildTerrainHdTextureArray(
                            *binding, hdDiffuseArray);
                    }
                }

                size_t replacedPasses = 0;
                size_t createdPrograms = 0;
                size_t reusedPrograms = 0;
                size_t seenPasses = 0;
                size_t createdFragmentPrograms = 0;
                size_t reusedFragmentPrograms = 0;
                const int debugMode = g_config.semanticDebugMode;
                const bool fragmentApiAvailable =
                    g_ogre.getFragmentProgram && g_ogre.setFragmentProgram &&
                    g_ogre.getFragmentProgramParameters &&
                    g_ogre.setFragmentProgramParameters;
                std::unordered_map<std::string, std::string> semanticPrograms;
                std::unordered_map<std::string, std::string> semanticFragmentPrograms;
                // Source vertex-program names whose semantic permutation
                // actually received the debug false colour.
                std::set<std::string> semanticProgramsWithDebugColor;
                size_t debugColorSkippedPasses = 0;
                size_t hdDiffusePasses = 0;
                // A bind is only credited when the Pass reports our program
                // back. Asserting the swap from the call succeeding is what
                // let a silently ineffective bind look like a working one.
                size_t vertexBindVerified = 0;
                size_t vertexBindMismatched = 0;
                size_t fragmentBindVerified = 0;
                size_t fragmentBindMismatched = 0;
                std::string firstVertexBindActual;
                const auto bindProgram = [&](void* pass,
                                             const std::string& programName)
                {
                    OgreSharedPtr oldParameters;
                    g_ogre.getVertexProgramParameters(pass, &oldParameters);
                    g_ogre.setVertexProgram(pass, programName, false);
                    if (oldParameters.rep && oldParameters.info &&
                        AddSharedReference(oldParameters))
                    {
                        // The raw ABI call does not run Ogre's C++ caller-side
                        // SharedPtr copy constructor. Supply that reference
                        // explicitly for the by-value parameter.
                        g_ogre.setVertexProgramParameters(pass, oldParameters);
                        ReleaseCloneHandoff(oldParameters);
                    }
                    const OgreSharedPtr* bound = g_ogre.getVertexProgram(pass);
                    const std::string* boundName =
                        bound && bound->rep
                            ? g_ogre.getResourceName(bound->rep) : nullptr;
                    if (boundName && *boundName == programName)
                    {
                        ++vertexBindVerified;
                    }
                    else
                    {
                        ++vertexBindMismatched;
                        if (firstVertexBindActual.empty())
                            firstVertexBindActual = boundName
                                ? *boundName : std::string("<none>");
                    }
                };
                const auto bindFragmentProgram = [&](void* pass,
                                                     const std::string& programName)
                    -> bool
                {
                    OgreSharedPtr oldParameters;
                    g_ogre.getFragmentProgramParameters(pass, &oldParameters);
                    g_ogre.setFragmentProgram(pass, programName, false);
                    if (oldParameters.rep && oldParameters.info &&
                        AddSharedReference(oldParameters))
                    {
                        g_ogre.setFragmentProgramParameters(pass, oldParameters);
                        ReleaseCloneHandoff(oldParameters);
                    }
                    const OgreSharedPtr* bound = g_ogre.getFragmentProgram(pass);
                    const std::string* boundName =
                        bound && bound->rep
                            ? g_ogre.getResourceName(bound->rep) : nullptr;
                    if (boundName && *boundName == programName)
                    {
                        ++fragmentBindVerified;
                        return true;
                    }
                    ++fragmentBindMismatched;
                    return false;
                };
                // Resolve a Pass program to the HLSL delegate that actually
                // carries source; unified programs hold none themselves.
                const auto resolveProgram = [&](const OgreSharedPtr* program)
                    -> const OgreSharedPtr*
                {
                    if (!program || !program->rep)
                        return nullptr;
                    const std::string* source =
                        g_ogre.getProgramSource(program->rep);
                    if (source && !source->empty())
                        return program;
                    const OgreSharedPtr* delegated =
                        g_ogre.getUnifiedDelegate(program->rep);
                    if (!delegated || !delegated->rep)
                        return nullptr;
                    source = g_ogre.getProgramSource(delegated->rep);
                    return source && !source->empty() ? delegated : nullptr;
                };
                const uint16_t techniqueCount =
                    g_ogre.getNumTechniques(semanticMaterial.rep);
                for (uint16_t techniqueIndex = 0;
                     techniqueIndex < techniqueCount; ++techniqueIndex)
                {
                    void* technique = g_ogre.getTechnique(
                        semanticMaterial.rep, techniqueIndex);
                    if (!technique)
                        continue;
                    const uint16_t passCount = g_ogre.getNumPasses(technique);
                    for (uint16_t passIndex = 0; passIndex < passCount; ++passIndex)
                    {
                        void* pass = g_ogre.getPass(technique, passIndex);
                        if (!pass)
                            continue;
                        ++seenPasses;
                        const OgreSharedPtr* sourceProgram =
                            resolveProgram(g_ogre.getVertexProgram(pass));
                        const std::string* source = sourceProgram
                            ? g_ogre.getProgramSource(sourceProgram->rep)
                            : nullptr;
                        const std::string* sourceProgramName = sourceProgram
                            ? g_ogre.getResourceName(sourceProgram->rep)
                            : nullptr;
                        if (!source || source->empty() || !sourceProgramName)
                            continue;

                        // Debug visualization needs one matching fragment
                        // specialization per pass so the false color survives
                        // lighting and the atlas sample.
                        // Only meaningful when this pass's vertex program
                        // carries the debug colour. Rewriting the fragment
                        // program of a pass that does not carry it replaces
                        // the whole oColor with stock COLOR0 - opaque white,
                        // with the atlas sample, the fog blend and the COLOR0
                        // alpha mask all discarded - which paints over every
                        // other pass and hides the debug output entirely.
                        const auto specializeFragment = [&](bool hasDebugColor)
                        {
                            const bool addDebugColor = debugMode != 0 && hasDebugColor;
                            if (debugMode != 0 && !hasDebugColor)
                            {
                                ++debugColorSkippedPasses;
                            }
                            if (!addDebugColor && !hdDiffuseReady)
                                return;
                            if (!fragmentApiAvailable)
                                return;
                            void* hdTextureUnit = nullptr;
                            if (hdDiffuseReady)
                            {
                                if (g_ogre.getNumTextureUnitStates(pass) == 0)
                                    return;
                                hdTextureUnit = g_ogre.getTextureUnitState(pass, 0);
                                if (!hdTextureUnit)
                                    return;
                            }
                            const OgreSharedPtr* fragmentProgram =
                                resolveProgram(g_ogre.getFragmentProgram(pass));
                            const std::string* fragmentSource = fragmentProgram
                                ? g_ogre.getProgramSource(fragmentProgram->rep)
                                : nullptr;
                            const std::string* fragmentName = fragmentProgram
                                ? g_ogre.getResourceName(fragmentProgram->rep)
                                : nullptr;
                            if (!fragmentSource || fragmentSource->empty() ||
                                !fragmentName)
                                return;
                            const std::string fragmentCacheKey = *fragmentName +
                                (addDebugColor ? "|debug" : "|normal");
                            const auto known =
                                semanticFragmentPrograms.find(fragmentCacheKey);
                            if (known != semanticFragmentPrograms.end())
                            {
                                if (!bindFragmentProgram(pass, known->second))
                                    return;
                                if (hdTextureUnit)
                                {
                                    g_ogre.setTexture(hdTextureUnit, hdDiffuseArray);
                                    ++hdDiffusePasses;
                                }
                                ++reusedFragmentPrograms;
                                return;
                            }
                            std::string fragmentTarget;
                            std::string fragmentEntry;
                            std::string fragmentDefines;
                            g_ogre.getStringParameter(fragmentProgram->rep,
                                &fragmentTarget, std::string("target"));
                            g_ogre.getStringParameter(fragmentProgram->rep,
                                &fragmentEntry, std::string("entry_point"));
                            g_ogre.getStringParameter(fragmentProgram->rep,
                                &fragmentDefines,
                                std::string("preprocessor_defines"));
                            if (fragmentTarget.rfind("ps_4", 0) != 0 ||
                                fragmentEntry != "terrain_fragment")
                                return;
                            std::string semanticFragmentSource;
                            if (!BuildSemanticFragmentSource(
                                    *fragmentSource, addDebugColor,
                                    hdDiffuseReady, semanticFragmentSource))
                                return;
                            // The name carries a hash of the generated source.
                            // Ogre's microcode cache is keyed by program name
                            // and this shim's cache fingerprint covers only the
                            // mod's shader files, so a stable name would hand
                            // back microcode compiled from different generated
                            // source - silently ignoring the mode being tested.
                            const std::string fragmentProgramName =
                                "OpenShim/TerrainSemantic/Fragment/" +
                                generationSuffix + "/" +
                                std::to_string(createdFragmentPrograms) + "/" +
                                SourceHashSuffix(semanticFragmentSource);
                            OgreSharedPtr generatedFragmentProgram;
                            const std::string group = "General";
                            const std::string language = "hlsl";
                            g_ogre.createHighLevelProgram(programManager,
                                &generatedFragmentProgram, fragmentProgramName, group,
                                language, 1);
                            if (!generatedFragmentProgram.rep ||
                                !generatedFragmentProgram.info)
                                return;
                            g_ogre.setProgramSource(generatedFragmentProgram.rep,
                                semanticFragmentSource);
                            if (!g_ogre.setStringParameter(generatedFragmentProgram.rep,
                                    std::string("target"), fragmentTarget) ||
                                !g_ogre.setStringParameter(generatedFragmentProgram.rep,
                                    std::string("entry_point"), fragmentEntry))
                            {
                                ReleaseCloneHandoff(generatedFragmentProgram);
                                return;
                            }
                            g_ogre.setStringParameter(generatedFragmentProgram.rep,
                                std::string("preprocessor_defines"),
                                fragmentDefines);
                            g_ogre.loadResource(generatedFragmentProgram.rep, true);
                            if (!bindFragmentProgram(pass, fragmentProgramName))
                            {
                                ReleaseCloneHandoff(generatedFragmentProgram);
                                return;
                            }
                            if (hdTextureUnit)
                            {
                                g_ogre.setTexture(hdTextureUnit, hdDiffuseArray);
                                ++hdDiffusePasses;
                            }
                            semanticFragmentPrograms.emplace(fragmentCacheKey,
                                fragmentProgramName);
                            g_proxy.semanticProgramNames.push_back(
                                fragmentProgramName);
                            ReleaseCloneHandoff(generatedFragmentProgram);
                            ++createdFragmentPrograms;
                            ++g_semanticProgramsCreatedTotal;
                        };

                        const auto reused = semanticPrograms.find(
                            *sourceProgramName);
                        if (reused != semanticPrograms.end())
                        {
                            bindProgram(pass, reused->second);
                            specializeFragment(
                                semanticProgramsWithDebugColor.count(
                                    *sourceProgramName) != 0);
                            ++reusedPrograms;
                            ++replacedPasses;
                            continue;
                        }

                        std::string target;
                        std::string entryPoint;
                        std::string defines;
                        g_ogre.getStringParameter(sourceProgram->rep,
                            &target, std::string("target"));
                        g_ogre.getStringParameter(sourceProgram->rep,
                            &entryPoint, std::string("entry_point"));
                        g_ogre.getStringParameter(sourceProgram->rep,
                            &defines, std::string("preprocessor_defines"));

                        std::string semanticSource;
                        bool debugColorInstalled = false;
                        const bool compatibleSource =
                            BuildSemanticProgramSource(*source,
                                g_config.semanticLegacyUvQuantization,
                                hdDiffuseReady,
                                debugMode, *sourceProgramName, semanticSource,
                                debugColorInstalled);
                        LogShimA(LogLevel::Info, "terrain-p3",
                            "[TERRAIN-P3] vertex delegate inspect name=\"%s\" sourceBytes=%zu target=\"%s\" entry=\"%s\" semanticSource=%d",
                            sourceProgramName->c_str(),
                            source->size(), target.c_str(), entryPoint.c_str(),
                            compatibleSource ? 1 : 0);
                        if (!compatibleSource)
                            continue;
                        if (target.rfind("vs_4", 0) != 0 ||
                            entryPoint != "terrain_vertex")
                            continue;

                        // See the fragment name above: the source hash is what
                        // keeps Ogre's name-keyed microcode cache from serving
                        // a different mode's compiled program.
                        const std::string programName =
                            "OpenShim/TerrainSemantic/Vertex/" +
                            generationSuffix + "/" +
                            std::to_string(createdPrograms) + "/" +
                            SourceHashSuffix(semanticSource);
                        OgreSharedPtr semanticProgram;
                        const std::string group = "General";
                        const std::string language = "hlsl";
                        g_ogre.createHighLevelProgram(programManager,
                            &semanticProgram, programName, group, language, 0);
                        if (!semanticProgram.rep || !semanticProgram.info)
                            continue;
                        g_ogre.setProgramSource(semanticProgram.rep,
                            semanticSource);
                        if (!g_ogre.setStringParameter(semanticProgram.rep,
                                std::string("target"), target) ||
                            !g_ogre.setStringParameter(semanticProgram.rep,
                                std::string("entry_point"), entryPoint))
                        {
                            ReleaseCloneHandoff(semanticProgram);
                            continue;
                        }
                        g_ogre.setStringParameter(semanticProgram.rep,
                            std::string("preprocessor_defines"), defines);
                        g_ogre.loadResource(semanticProgram.rep, true);

                        bindProgram(pass, programName);
                        specializeFragment(debugColorInstalled);
                        if (debugColorInstalled)
                            semanticProgramsWithDebugColor.insert(
                                *sourceProgramName);
                        semanticPrograms.emplace(*sourceProgramName,
                            programName);
                        g_proxy.semanticProgramNames.push_back(programName);
                        ReleaseCloneHandoff(semanticProgram);
                        ++createdPrograms;
                        ++g_semanticProgramsCreatedTotal;
                        ++replacedPasses;
                    }
                }

                if (replacedPasses == 0)
                {
                    ReleaseCloneHandoff(hdDiffuseArray);
                    RemoveTerrainHdTextureResource("no-compatible-vertex-program");
                    ReleaseCloneHandoff(semanticMaterial);
                    RemoveSemanticResources("no-compatible-vertex-program");
                    g_proxy.semanticMaterialName.clear();
                    g_proxy.semanticMaterialUnsupported = true;
                    LogShimA(LogLevel::Warn, "terrain-p3",
                        "[TERRAIN-P3] active material had no compatible DX11 terrain vertex program; stock material retained material=\"%s\"",
                        g_proxy.materialName.c_str());
                    return false;
                }

                if (hdDiffuseReady && hdDiffusePasses == 0)
                {
                    LogShimA(LogLevel::Warn, "terrain-hd",
                        "[TERRAIN-HD] no compatible terrain fragment pass accepted the array; stock atlas retained material=\"%s\"",
                        g_proxy.materialName.c_str());
                    RemoveTerrainHdTextureResource("no-compatible-fragment-program");
                    hdDiffuseReady = false;
                }

                g_ogre.setMaterialName(g_proxy.proxyEntity,
                    g_proxy.semanticMaterialName, autodetect);
                ReleaseCloneHandoff(hdDiffuseArray);
                ReleaseCloneHandoff(semanticMaterial);
                g_proxy.semanticMaterialInstalled = true;
                ++g_semanticMaterialCreated;
                g_proxy.semanticProgramsCreated = createdPrograms;
                g_proxy.semanticProgramsReused = reusedPrograms;
                g_proxy.semanticPassesSpecialized = replacedPasses;
                g_proxy.semanticPassesSeen = seenPasses;
                g_proxy.semanticFragmentProgramsCreated = createdFragmentPrograms;
                LogShimA(LogLevel::Info, "terrain-p3",
                    "[TERRAIN-P3] terrain_semantic_shader: material=\"%s\" clone=\"%s\" materialGeneration=%u passes=%zu specialized_passes=%zu semantic_programs=%zu created=%zu reused=%zu debug=%s fragment_programs={created:%zu,reused:%zu,api:%d,skipped_no_vertex_color:%zu} legacyUVQuantization=%d atlasRects=per-vertex hdDiffuse={requested:%d,active:%d,passes:%zu,array:\"%s\"}",
                    g_proxy.materialName.c_str(),
                    g_proxy.semanticMaterialName.c_str(),
                    g_proxy.semanticMaterialGeneration, seenPasses,
                    replacedPasses, semanticPrograms.size(), createdPrograms,
                    reusedPrograms, SemanticDebugModeName(debugMode),
                    createdFragmentPrograms, reusedFragmentPrograms,
                    fragmentApiAvailable ? 1 : 0, debugColorSkippedPasses,
                    g_config.semanticLegacyUvQuantization ? 1 : 0,
                    g_config.hdEnabled ? 1 : 0, hdDiffuseReady ? 1 : 0,
                    hdDiffusePasses, g_proxy.hdTextureName.c_str());
                // Generated program identity, once per material install. The
                // microcode cache is keyed by program name, so proving that a
                // changed generated source produces a changed name is the only
                // way to show the cache cannot serve a stale compile. Without
                // this the property can only be inferred from cache growth.
                for (const std::string& name : g_proxy.semanticProgramNames)
                {
                    LogShimA(LogLevel::Info, "terrain-p3",
                        "[TERRAIN-P3] terrain_semantic_shader program materialGeneration=%u name=\"%s\"",
                        g_proxy.semanticMaterialGeneration, name.c_str());
                }
                LogShimA(
                    (vertexBindMismatched || fragmentBindMismatched)
                        ? LogLevel::Warn : LogLevel::Info,
                    "terrain-p3",
                    "[TERRAIN-P3] terrain_semantic_shader bind audit: vertex={verified:%zu,mismatched:%zu} fragment={verified:%zu,mismatched:%zu} firstVertexActual=\"%s\"",
                    vertexBindVerified, vertexBindMismatched,
                    fragmentBindVerified, fragmentBindMismatched,
                    firstVertexBindActual.empty()
                        ? "-" : firstVertexBindActual.c_str());
                if (debugMode != 0 && createdFragmentPrograms == 0)
                {
                    LogShimA(LogLevel::Warn, "terrain-p3",
                        "[TERRAIN-P3] semantic debug=%s specialized no fragment program; false color remains modulated by lighting and the atlas sample",
                        SemanticDebugModeName(debugMode));
                }
                LogShimA(LogLevel::Info, "terrain-p3",
                    "[TERRAIN-P3] terrain_semantic_shader totals: materialCreated=%u materialRemoved=%u programsCreated=%u programsRemoved=%u",
                    g_semanticMaterialCreated, g_semanticMaterialRemoved,
                    g_semanticProgramsCreatedTotal, g_semanticProgramsRemovedTotal);
                ReportSemanticBinding("material-installed", true);
                return true;
            }
            catch (...)
            {
                RemoveSemanticResources("material-install-exception");
                LogShimA(LogLevel::Warn, "terrain-p3",
                    "[TERRAIN-P3] semantic material creation failed; stock material retained");
                return false;
            }
        }

        // Single entry point for "make the semantic path current", so every
        // caller produces the same lifecycle record.
        bool InstallSemanticRenderPath(const char* phase)
        {
            const uint32_t previousUnchanged = g_proxy.semanticUnchangedCount;
            if (!InstallOrRefreshSemanticStream())
                return false;
            const bool dataUnchanged =
                g_proxy.semanticUnchangedCount != previousUnchanged;
            if (!InstallSemanticMaterial())
                return false;
            if (dataUnchanged && g_config.semanticLifecycleLog)
            {
                LogShimA(LogLevel::Info, "terrain-p3",
                    "[TERRAIN-P3] terrain_semantic: semantic_unchanged phase=%s vbGeneration=%u dataHash=%08X retained=1 uploads=%u skipped=%u",
                    phase, g_proxy.semanticVbGeneration,
                    g_proxy.semanticDataHash, g_proxy.semanticUploadCount,
                    g_proxy.semanticUnchangedCount);
            }
            ReportSemanticBinding(phase, false);
            return true;
        }

        void ResetSelectedState()
        {
            g_proxy = {};
            g_zoneOrdinals.clear();
            g_nextZoneOrdinal = 0;
            g_teardownDepth = 0;
            g_teardownIncludesClear = false;
        }

        // Is the proxy Entity still registered with the SceneManager?
        //
        // The engine destroys the proxy Entity underneath OpenShim at an
        // unpredictable point during a mission change. Crash dump
        // battlezone98redux.exe.1916.dmp caught it: at the second mission seam
        // the generation-2 Entity allocation had already been recycled (its
        // vtable slot read 0x00000008) while the proxy SceneNode, the proxy
        // Mesh and every stock cluster object were still valid. A stored
        // Entity pointer therefore cannot be trusted across a mission
        // boundary, and cannot be tested for validity either. Every lifecycle
        // decision about the scene objects goes through the name instead.
        //
        // Resource names carry a process-lifetime serial, so a stale name can
        // only ever resolve to OpenShim's own object, never to a later one.
        bool ProxyEntityStillRegistered()
        {
            if (!g_proxy.sceneManager || !g_ogre.hasEntityByName ||
                g_proxy.proxyEntityName.empty())
                return true;
            try
            {
                return g_ogre.hasEntityByName(
                    g_proxy.sceneManager, g_proxy.proxyEntityName);
            }
            catch (...)
            {
                return true;
            }
        }

        void DestroyProxySceneObjectsByName(const char* reason, bool destroyEntity, bool destroyNode)
        {
            if (!g_proxy.sceneManager)
                return;
            int entityPresent = -1;
            int nodePresent = -1;
            bool entityDestroyed = false;
            bool nodeDestroyed = false;
            try
            {
                // Entity first: Ogre's MovableObject destructor detaches it, so
                // the node is left clean for its own destruction.
                if (destroyEntity && !g_proxy.proxyEntityName.empty() &&
                    g_ogre.hasEntityByName && g_ogre.destroyEntityByName)
                {
                    entityPresent = g_ogre.hasEntityByName(
                        g_proxy.sceneManager, g_proxy.proxyEntityName) ? 1 : 0;
                    if (entityPresent == 1)
                    {
                        g_ogre.destroyEntityByName(
                            g_proxy.sceneManager, g_proxy.proxyEntityName);
                        entityDestroyed = true;
                    }
                }
                if (destroyNode && !g_proxy.proxyNodeName.empty() &&
                    g_ogre.hasSceneNodeByName && g_ogre.destroySceneNodeByName)
                {
                    nodePresent = g_ogre.hasSceneNodeByName(
                        g_proxy.sceneManager, g_proxy.proxyNodeName) ? 1 : 0;
                    if (nodePresent == 1)
                    {
                        g_ogre.destroySceneNodeByName(
                            g_proxy.sceneManager, g_proxy.proxyNodeName);
                        nodeDestroyed = true;
                    }
                }
            }
            catch (...)
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] OGRE exception destroying proxy scene objects by name reason=%s entity=\"%s\" node=\"%s\"",
                    reason, g_proxy.proxyEntityName.c_str(),
                    g_proxy.proxyNodeName.c_str());
            }
            // entityPresent/nodePresent = 0 means the engine had already
            // destroyed it, which is ownership evidence, not an error.
            LogShimA(LogLevel::Info, "terrain-proxy",
                "[TERRAIN-PROXY] lifecycle scene-objects reason=%s proxyGeneration=%u entityPresent=%d destroyedByOpenShim=%d nodePresent=%d nodeDestroyedByOpenShim=%d entity=\"%s\" node=\"%s\"",
                reason, g_proxy.generation, entityPresent,
                entityDestroyed ? 1 : 0, nodePresent, nodeDestroyed ? 1 : 0,
                g_proxy.proxyEntityName.c_str(), g_proxy.proxyNodeName.c_str());
        }

        bool TerrainProxyStateIsForgotten()
        {
            return !g_proxy.selected && !g_proxy.proxyCreated &&
                !g_proxy.semanticStreamInstalled && !g_proxy.semanticBuffer &&
                g_proxy.semanticMaterialName.empty() &&
                g_proxy.semanticProgramNames.empty() &&
                g_proxy.proxyMeshName.empty() && !g_proxy.zone;
        }

        // The single idempotent "stop owning this mission's terrain proxy"
        // operation. Reachable from the mission-transition seam, from the two
        // Phase 2 SceneManager teardown seams, and from process shutdown.
        // Resource removal is by resource-manager name only; the stored mesh,
        // entity and node pointers are dereferenced solely when the caller can
        // prove the scene is still alive (destroySceneObjects).
        void ForgetTerrainProxy(TerrainForgetReason reason, bool destroyEntity, bool destroyNode)
        {
            const char* const reasonName = ForgetReasonName(reason);
            if (TerrainProxyStateIsForgotten())
            {
                ++g_missionForgetNoopCount;
                if (g_config.semanticLifecycleLog)
                {
                    LogShimA(LogLevel::Info, "terrain-proxy",
                        "[TERRAIN-PROXY] lifecycle already-forgotten reason=%s missionGeneration=%u noops=%u",
                        reasonName, g_missionGeneration, g_missionForgetNoopCount);
                }
                ResetSelectedState();
                return;
            }

            g_proxy.tearingDown = true;
            LogShimA(LogLevel::Info, "terrain-proxy",
                "[TERRAIN-PROXY] lifecycle teardown-begin reason=%s missionGeneration=%u proxyGeneration=%u materialGeneration=%u vbGeneration=%u zonePtr=%p sourceMesh=%p proxyMesh=%p proxyEntity=%p proxyNode=%p destroyEntityHere=%d destroyNodeHere=%d",
                reasonName, g_missionGeneration, g_proxy.generation,
                g_proxy.semanticMaterialGeneration, g_proxy.semanticVbGeneration,
                g_proxy.zone, g_proxy.sourceMesh, g_proxy.proxyMesh,
                g_proxy.proxyEntity, g_proxy.proxyNode,
                destroyEntity ? 1 : 0, destroyNode ? 1 : 0);

            if (destroyEntity || destroyNode)
                DestroyProxySceneObjectsByName(reasonName, destroyEntity, destroyNode);

            RemoveSemanticResources(reasonName);
            ReleaseSemanticStreamOwnership(reasonName);
            RemoveProxyMeshResource();

            ++g_missionForgetCount;
            LogShimA(LogLevel::Info, "terrain-proxy",
                "[TERRAIN-PROXY] lifecycle-forgotten reason=%s missionGeneration=%u proxyGeneration=%u selected=0 proxyCreated=0 forgets=%u refreshes={height:%u,full:%u,total:%u} semantic={builds:%u,uploads:%u,unchanged:%u} totals={vbCreated:%u,vbReleased:%u,materialCreated:%u,materialRemoved:%u,programsCreated:%u,programsRemoved:%u}",
                reasonName, g_missionGeneration, g_proxy.generation,
                g_missionForgetCount, g_proxy.heightRefreshCount,
                g_proxy.fullRefreshCount, g_proxy.rebuildCount,
                g_proxy.semanticBuildCount, g_proxy.semanticUploadCount,
                g_proxy.semanticUnchangedCount, g_semanticVbCreated,
                g_semanticVbReleased, g_semanticMaterialCreated,
                g_semanticMaterialRemoved, g_semanticProgramsCreatedTotal,
                g_semanticProgramsRemovedTotal);
            // Let the next mission report its own framing state. The capture
            // budget itself stays process-wide, as it always has.
            g_semanticFramingWaitLogged = false;
            g_semanticFramingWaits = 0;
            g_semanticFramedStreak = 0;
            g_unframedStreak = 0;
            g_reselectRequested = false;
            // The re-selection budget is per mission, not per process.
            if (reason == TerrainForgetReason::MissionTransition ||
                reason == TerrainForgetReason::SceneTeardown)
                g_reselectCount = 0;
            ResetSelectedState();
        }

        bool CreateProxy()
        {
            if (!g_config.proxyEnabled || g_proxy.tearingDown || g_proxy.proxyCreated)
                return g_proxy.proxyCreated;
            if (!g_proxy.sourceMesh || !g_proxy.sourceEntity || !g_proxy.sourceNode || !g_proxy.sceneManager)
                return false;
            try
            {
                if (!ValidateTerrainOperation(g_proxy.sourceMesh, g_proxy.sourceEntity, "stock cluster"))
                {
                    LogShimA(LogLevel::Warn, "terrain-proxy",
                        "[TERRAIN-PROXY] stock geometry contract mismatch; feature disabled for selected cluster");
                    return false;
                }

                const uint32_t serial = ++g_resourceSerial;
                g_proxy.generation = serial;
                char identity[128] = {};
                sprintf_s(identity, "z%d_%d/c%d_%d/%u", g_proxy.zoneX, g_proxy.zoneZ,
                    g_proxy.clusterX, g_proxy.clusterZ, serial);
                g_proxy.proxyMeshName = std::string("OpenShim/TerrainProxy/Mesh/") + identity;
                g_proxy.proxyEntityName = std::string("OpenShim/TerrainProxy/Entity/") + identity;
                g_proxy.proxyNodeName = std::string("OpenShim/TerrainProxy/Node/") + identity;

                OgreSharedPtr clone;
                const std::string group = "General";
                g_ogre.cloneMesh(g_proxy.sourceMesh, &clone, g_proxy.proxyMeshName, group);
                if (!clone.rep || !clone.info)
                    return false;
                g_proxy.proxyMesh = clone.rep;
                g_proxy.proxyEntity = g_ogre.createEntity(g_proxy.sceneManager, g_proxy.proxyEntityName, clone);
                if (!g_proxy.proxyEntity)
                {
                    ReleaseCloneHandoff(clone);
                    RemoveProxyMeshResource();
                    return false;
                }
                if (!ReleaseCloneHandoff(clone))
                    LogShimA(LogLevel::Warn, "terrain-proxy", "[TERRAIN-PROXY] retained clone handoff reference for safety");

                void* stockSubEntity = g_ogre.getSubEntity(g_proxy.sourceEntity, 0);
                const std::string* material = stockSubEntity ? g_ogre.getMaterialName(stockSubEntity) : nullptr;
                if (!material || material->empty())
                    return false;
                g_proxy.materialName = *material;
                const std::string autodetect = "Autodetect";
                g_ogre.setMaterialName(g_proxy.proxyEntity, g_proxy.materialName, autodetect);
                g_ogre.setCastShadows(g_proxy.proxyEntity, false);
                g_ogre.setRenderQueueGroup(g_proxy.proxyEntity, 0x28);
                g_ogre.setVisible(g_proxy.proxyEntity, g_config.proxyVisible);

                void* parent = g_ogre.getParentSceneNode(g_proxy.sourceNode);
                const Vector3* stockPosition = g_ogre.getNodePosition(g_proxy.sourceNode);
                const Quaternion* stockOrientation = g_ogre.getNodeOrientation(g_proxy.sourceNode);
                const Vector3* stockScale = g_ogre.getNodeScale(g_proxy.sourceNode);
                if (!parent || !stockPosition || !stockOrientation || !stockScale)
                    return false;
                Vector3 proxyPosition = *stockPosition;
                proxyPosition.x += g_config.offset.x;
                proxyPosition.y += g_config.offset.y;
                proxyPosition.z += g_config.offset.z;
                g_proxy.proxyNode = g_ogre.createChildSceneNode(
                    parent, g_proxy.proxyNodeName, proxyPosition, *stockOrientation);
                if (!g_proxy.proxyNode)
                    return false;
                g_ogre.setNodeScale(g_proxy.proxyNode, *stockScale);
                g_ogre.attachObject(g_proxy.proxyNode, g_proxy.proxyEntity);
                if (!ValidateTerrainOperation(g_proxy.proxyMesh, g_proxy.proxyEntity, "proxy cluster"))
                    return false;

                g_proxy.proxyCreated = true;
                LogShimA(LogLevel::Info, "terrain-proxy",
                    "[TERRAIN-PROXY] lifecycle created generation=%u zonePtr=%p sourceMesh=%p sourceEntity=%p sourceNode=%p proxyMesh=%p proxyEntity=%p proxyNode=%p mesh=\"%s\" entity=\"%s\" material=\"%s\" worldPosition=(%.3f,%.3f,%.3f) visible=%d",
                    g_proxy.generation, g_proxy.zone, g_proxy.sourceMesh,
                    g_proxy.sourceEntity, g_proxy.sourceNode, g_proxy.proxyMesh,
                    g_proxy.proxyEntity, g_proxy.proxyNode,
                    g_proxy.proxyMeshName.c_str(), g_proxy.proxyEntityName.c_str(),
                    g_proxy.materialName.c_str(), static_cast<double>(proxyPosition.x),
                    static_cast<double>(proxyPosition.y), static_cast<double>(proxyPosition.z),
                    g_config.proxyVisible ? 1 : 0);
                return true;
            }
            catch (...)
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] OGRE exception while creating proxy; stock terrain remains active");
                return false;
            }
        }

        bool RefreshProxyBuffers(bool fullDirty, bool heightDirty)
        {
            if ((!fullDirty && !heightDirty) || !g_proxy.proxyCreated ||
                !g_proxy.sourceEntity || !g_proxy.proxyEntity)
                return false;
            try
            {
                RenderOperation source = {};
                RenderOperation destination = {};
                void* sourceSubEntity = nullptr;
                void* destinationSubEntity = nullptr;
                if (!GetEntityOperation(g_proxy.sourceEntity, source, sourceSubEntity) ||
                    !GetEntityOperation(g_proxy.proxyEntity, destination, destinationSubEntity) ||
                    source.vertexData->vertexCount != destination.vertexData->vertexCount ||
                    source.indexData->indexCount != destination.indexData->indexCount)
                {
                    return false;
                }

                // Redux's full path (FUN_007794F0) locks and repopulates slots
                // 1 and 2, then updates bounds. Its height-only path in
                // FUN_00778450 locks slot 2 only and leaves normals/UVs and
                // bounds untouched. Mirror that granularity exactly; slot 0
                // and the index buffer remain immutable in both paths.
                const uint16_t firstSlot = fullDirty ? 1 : 2;
                for (uint16_t slot = firstSlot; slot <= 2; ++slot)
                {
                    void* sourceBuffer = nullptr;
                    void* destinationBuffer = nullptr;
                    if (!GetVertexBuffer(source, slot, sourceBuffer) ||
                        !GetVertexBuffer(destination, slot, destinationBuffer) ||
                        g_ogre.getBufferSize(sourceBuffer) != g_ogre.getBufferSize(destinationBuffer))
                    {
                        return false;
                    }
                    g_ogre.copyBufferData(destinationBuffer, sourceBuffer);
                }

                if (fullDirty)
                {
                    const AxisAlignedBox* bounds = g_ogre.getBounds(g_proxy.sourceMesh);
                    if (bounds)
                        g_ogre.setBounds(g_proxy.proxyMesh, *bounds, false);
                    g_ogre.setRadius(g_proxy.proxyMesh, g_ogre.getRadius(g_proxy.sourceMesh));
                    const std::string* material = g_ogre.getMaterialName(sourceSubEntity);
                    if (material && *material != g_proxy.materialName)
                    {
                        if (g_proxy.semanticMaterialInstalled)
                        {
                            const std::string autodetect = "Autodetect";
                            g_ogre.setMaterialName(g_proxy.proxyEntity,
                                *material, autodetect);
                            RemoveSemanticResources("stock-material-changed");
                            // A different stock material may well be a
                            // compatible terrain material, so allow one fresh
                            // specialization attempt against it.
                            g_proxy.semanticMaterialUnsupported = false;
                        }
                        g_proxy.materialName = *material;
                        const std::string autodetect = "Autodetect";
                        g_ogre.setMaterialName(g_proxy.proxyEntity, g_proxy.materialName, autodetect);
                    }
                }
                const uint32_t previousHeightHash = g_proxy.heightHash;
                uint32_t nextHeightHash = previousHeightHash;
                uint16_t nextHeightMinimum = g_proxy.heightMinimum;
                uint16_t nextHeightMaximum = g_proxy.heightMaximum;
                const bool capturedHeight = CaptureClusterHeightSignature(
                    nextHeightHash, nextHeightMinimum, nextHeightMaximum);
                if (capturedHeight)
                {
                    g_proxy.heightHash = nextHeightHash;
                    g_proxy.heightMinimum = nextHeightMinimum;
                    g_proxy.heightMaximum = nextHeightMaximum;
                }
                ++g_proxy.rebuildCount;
                uint32_t& typeCount = fullDirty
                    ? g_proxy.fullRefreshCount
                    : g_proxy.heightRefreshCount;
                ++typeCount;
                if (typeCount <= 8)
                {
                    LogShimA(LogLevel::Info, "terrain-proxy",
                        "[TERRAIN-PROXY] refresh mirrored generation=%u type=%s typeCount=%u totalCount=%u streams=%s bounds=%s heightHash=%08X->%08X heightChanged=%d heightRange=[%u,%u] zone=(%d,%d) cluster=(%d,%d)",
                        g_proxy.generation,
                        fullDirty ? "full" : "height-only", typeCount,
                        g_proxy.rebuildCount, fullDirty ? "1,2" : "2",
                        fullDirty ? "mirrored" : "unchanged",
                        previousHeightHash, nextHeightHash,
                        capturedHeight && previousHeightHash != nextHeightHash ? 1 : 0,
                        static_cast<unsigned>(nextHeightMinimum),
                        static_cast<unsigned>(nextHeightMaximum),
                        g_proxy.zoneX, g_proxy.zoneZ, g_proxy.clusterX,
                        g_proxy.clusterZ);
                }

                // Height-only events must never touch the semantic stream.
                // Prove that here rather than inferring it: re-read slot 3 and
                // the active material straight from OGRE and compare the
                // resource identity against the one recorded at creation.
                if (!fullDirty && g_config.semanticRenderer &&
                    g_proxy.semanticStreamInstalled)
                {
                    SemanticBinding binding;
                    const bool queried = QuerySemanticBinding(binding);
                    const bool retained = queried && binding.slotPresent &&
                        binding.buffer == g_proxy.semanticBuffer &&
                        binding.stride == sizeof(TerrainSemantic::GpuVertex);
                    const uint32_t signature = queried ? binding.Signature() : 0;
                    const bool changed =
                        signature != g_proxy.semanticBindingSignature;
                    if (queried)
                        ValidateSemanticBinding("height_update", binding);
                    if (changed || !retained ||
                        (g_config.semanticLifecycleLog &&
                         g_proxy.heightUpdateLogCount < 8))
                    {
                        ++g_proxy.heightUpdateLogCount;
                        LogShimA(retained ? LogLevel::Info : LogLevel::Warn,
                            "terrain-p3",
                            "[TERRAIN-P3] terrain_semantic: height_update owner=%p proxyGeneration=%u vbGeneration=%u vb=%p retained=%d rebuilt=0 stride=%u material=\"%s\" semanticMaterial=%d heightUpdates=%u",
                            g_proxy.zone, g_proxy.generation,
                            g_proxy.semanticVbGeneration, binding.buffer,
                            retained ? 1 : 0, binding.stride,
                            binding.materialName.c_str(),
                            binding.materialIsSemantic ? 1 : 0,
                            g_proxy.heightRefreshCount);
                    }
                    g_proxy.semanticBindingSignature = signature;
                }
                return true;
            }
            catch (...)
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] rebuild copy failed; disabling proxy visibility");
                try
                {
                    g_ogre.setVisible(g_proxy.proxyEntity, false);
                }
                catch (...)
                {
                }
                return false;
            }
        }

        bool ReadTerrainSemantic(int terrainX, int terrainZ, uint16_t& word,
            uint8_t& tileIndex, AtlasRect& rect)
        {
            __try
            {
                uint16_t* wordPointer = g_terrainWordAt(terrainX, terrainZ);
                void* manager = g_terrainManager();
                if (!wordPointer || !manager)
                    return false;
                word = *wordPointer;
                tileIndex = g_tileIndexAt(terrainX, terrainZ);
                const int accessorMix = g_mixAt(terrainX, terrainZ);
                if (accessorMix != static_cast<int>((word >> 4) & 0xF))
                    return false;
                const AtlasRect* activeRect = g_atlasRectAt(manager, tileIndex);
                if (!activeRect)
                    return false;
                rect = *activeRect;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        struct SemanticBuildContext
        {
            int originX;
            int originZ;
        };

        bool ProvideSemanticCell(void* opaque, int cellX, int cellZ,
            TerrainSemantic::Cell& cell)
        {
            const auto* context = static_cast<const SemanticBuildContext*>(opaque);
            if (!context || !g_proxy.selected)
                return false;

            cell.cellX = cellX;
            cell.cellZ = cellZ;
            cell.terrainX = g_proxy.zoneX * 256 + context->originX - 128 +
                (g_proxy.clusterX * 16 + cellX) * 4;
            cell.terrainZ = g_proxy.zoneZ * 256 + context->originZ - 128 +
                (g_proxy.clusterZ * 16 + cellZ) * 4;

            AtlasRect rect = {};
            if (!ReadTerrainSemantic(cell.terrainX, cell.terrainZ,
                    cell.word, cell.tileIndex, rect))
                return false;

            cell.typeA = static_cast<uint8_t>((cell.word >> 12) & 0xF);
            cell.typeB = static_cast<uint8_t>((cell.word >> 8) & 0xF);
            cell.mix = static_cast<uint8_t>((cell.word >> 4) & 0xF);
            // FUN_00779C20 indexes MIX2UV with the complete mix nibble. The
            // final four records differ from the low-three-bit aliases.
            cell.orientation = cell.mix;
            cell.variant = static_cast<uint8_t>(cell.word & 0x3);
            cell.rect = {rect.u, rect.v, rect.w, rect.h};
            return true;
        }

        bool BuildAndValidateSemanticVertices(bool forceLog)
        {
            if ((!g_config.semanticValidateUv && !g_config.semanticRenderer) ||
                !g_proxy.selected || g_proxy.tearingDown)
                return false;

            int originX = 0;
            int originZ = 0;
            if (!SafeReadIntAddress(Rebase(kTerrainOriginXVa), originX) ||
                !SafeReadIntAddress(Rebase(kTerrainOriginZVa), originZ))
                return false;

            SemanticBuildContext context{originX, originZ};
            std::vector<TerrainSemantic::Vertex> vertices;
            if (!TerrainSemantic::BuildVertices(
                    ProvideSemanticCell, &context, vertices))
            {
                LogShimA(LogLevel::Warn, "terrain-p3",
                    "[TERRAIN-P3] semantic vertex generation failed zone=(%d,%d) cluster=(%d,%d)",
                    g_proxy.zoneX, g_proxy.zoneZ,
                    g_proxy.clusterX, g_proxy.clusterZ);
                return false;
            }

            g_proxy.semanticVertices = std::move(vertices);
            ++g_proxy.semanticBuildCount;
            if (!ValidateSemanticVertexRanges(g_proxy.semanticVertices))
            {
                LogShimA(LogLevel::Warn, "terrain-p3",
                    "[TERRAIN-P3] semantic range validation failed build=%u; semantic upload skipped and stock material retained",
                    g_proxy.semanticBuildCount);
                return false;
            }
            if (forceLog || g_config.semanticLifecycleLog)
            {
                LogShimA(LogLevel::Info, "terrain-p3",
                    "[TERRAIN-P3] terrain_semantic: semantic_rebuild proxyGeneration=%u build=%u zone=(%d,%d) cluster=(%d,%d) vertices=%zu generation-order=released-clipped-17x17",
                    g_proxy.generation, g_proxy.semanticBuildCount,
                    g_proxy.zoneX, g_proxy.zoneZ,
                    g_proxy.clusterX, g_proxy.clusterZ,
                    g_proxy.semanticVertices.size());
            }

            if (!g_config.semanticValidateUv)
            {
                if (!g_config.semanticRenderer)
                    return true;
                return InstallSemanticRenderPath(
                    forceLog ? "install" : "semantic_rebuild");
            }

            RenderOperation operation = {};
            void* subEntity = nullptr;
            void* stockBuffer = nullptr;
            if (!GetEntityOperation(g_proxy.sourceEntity, operation, subEntity) ||
                !GetVertexBuffer(operation, 1, stockBuffer))
            {
                LogShimA(LogLevel::Warn, "terrain-p3",
                    "[TERRAIN-P3-UV] stock stream 1 unavailable; validation skipped");
                return false;
            }

            constexpr uint32_t kBytes =
                static_cast<uint32_t>(TerrainSemantic::kVertexCount * 4);
            std::vector<uint8_t> stockBytes;
            if (!ReadD3D11VertexBuffer(stockBuffer, kBytes, stockBytes))
            {
                LogShimA(LogLevel::Warn, "terrain-p3",
                    "[TERRAIN-P3-UV] D3D11 staging readback failed; validation skipped");
                return false;
            }
            const TerrainSemantic::ValidationResult result =
                TerrainSemantic::ValidatePackedUv(
                    g_proxy.semanticVertices, stockBytes.data(), 4,
                    g_config.semanticDumpMismatches ? 8 : 0);

            LogShimA(LogLevel::Info, "terrain-p3",
                "[TERRAIN-P3-UV] checked=%zu matched=%zu mismatched=%zu maxUvErrorBeforeQuantization=%.9f",
                result.checked, result.exactMatches, result.mismatches,
                static_cast<double>(result.maximumUvErrorBeforeQuantization));
            for (const TerrainSemantic::Mismatch& mismatch : result.examples)
            {
                const auto& vertex = mismatch.semantic;
                LogShimA(LogLevel::Warn, "terrain-p3",
                    "[TERRAIN-P3-UV] mismatch vertex=%zu cell=(%d,%d) q=(%u,%u) localUV=(%.6f,%.6f) tileIndex=%u orientation=%u rect=(%.9f,%.9f,%.9f,%.9f) atlasUV=(%.9f,%.9f) semanticPacked=(%u,%u) stockPacked=(%u,%u)",
                    mismatch.vertex,
                    static_cast<int>(vertex.cellX), static_cast<int>(vertex.cellZ),
                    static_cast<unsigned>(vertex.qx), static_cast<unsigned>(vertex.qz),
                    static_cast<double>(vertex.gpu.localU),
                    static_cast<double>(vertex.gpu.localV),
                    static_cast<unsigned>(vertex.gpu.tileIndex),
                    static_cast<unsigned>(vertex.gpu.orientation),
                    static_cast<double>(vertex.rect.u), static_cast<double>(vertex.rect.v),
                    static_cast<double>(vertex.rect.w), static_cast<double>(vertex.rect.h),
                    static_cast<double>(vertex.atlasUv.x),
                    static_cast<double>(vertex.atlasUv.y),
                    static_cast<unsigned>(vertex.packedU),
                    static_cast<unsigned>(vertex.packedV),
                    static_cast<unsigned>(mismatch.stockU),
                    static_cast<unsigned>(mismatch.stockV));
            }
            const bool exact = result.checked == TerrainSemantic::kVertexCount &&
                result.mismatches == 0;
            if (!exact || !g_config.semanticRenderer)
                return exact;
            return InstallSemanticRenderPath(
                forceLog ? "install" : "semantic_rebuild");
        }

        std::filesystem::path SemanticOutputPath()
        {
            wchar_t path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameW(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return L"terrain_semantic.json";
            return std::filesystem::path(path).parent_path() / L"terrain_semantic.json";
        }

        void CaptureSemantics(bool forceLog)
        {
            if (!g_config.semanticCapture || !g_proxy.selected)
                return;
            int originX = 0;
            int originZ = 0;
            if (!SafeReadIntAddress(Rebase(kTerrainOriginXVa), originX) ||
                !SafeReadIntAddress(Rebase(kTerrainOriginZVa), originZ))
                return;

            struct Cell
            {
                int x;
                int z;
                int terrainX;
                int terrainZ;
                uint16_t word;
                uint8_t tileIndex;
                AtlasRect rect;
            };
            std::array<Cell, 256> cells = {};
            uint32_t hash = 2166136261u;
            size_t count = 0;
            for (int z = 0; z < 16; ++z)
            {
                for (int x = 0; x < 16; ++x)
                {
                    Cell& cell = cells[count];
                    cell.x = x;
                    cell.z = z;
                    cell.terrainX = g_proxy.zoneX * 256 + originX - 128 +
                        (g_proxy.clusterX * 16 + x) * 4;
                    cell.terrainZ = g_proxy.zoneZ * 256 + originZ - 128 +
                        (g_proxy.clusterZ * 16 + z) * 4;
                    if (!ReadTerrainSemantic(cell.terrainX, cell.terrainZ, cell.word,
                            cell.tileIndex, cell.rect))
                    {
                        LogShimA(LogLevel::Warn, "terrain-semantic",
                            "[TERRAIN-SEMANTIC] capture failed cell=(%d,%d); stock rendering continues", x, z);
                        return;
                    }
                    const uint8_t bytes[] = {
                        static_cast<uint8_t>(cell.word & 0xFF), static_cast<uint8_t>(cell.word >> 8),
                        cell.tileIndex
                    };
                    for (uint8_t byte : bytes)
                    {
                        hash ^= byte;
                        hash *= 16777619u;
                    }
                    ++count;
                }
            }
            if (!forceLog && hash == g_proxy.semanticHash)
                return;
            g_proxy.semanticHash = hash;

            if (g_config.semanticDumpJson)
            {
                const std::filesystem::path outputPath = SemanticOutputPath();
                std::ofstream output(outputPath, std::ios::trunc);
                if (output)
                {
                    output << std::setprecision(9);
                    output << "{\n"
                        << "  \"schema\": \"bzr-openshim-terrain-semantic-v1\",\n"
                        << "  \"zone\": " << g_proxy.zoneOrdinal << ",\n"
                        << "  \"zoneX\": " << g_proxy.zoneX << ",\n"
                        << "  \"zoneZ\": " << g_proxy.zoneZ << ",\n"
                        << "  \"cluster\": " << g_proxy.clusterOrdinal << ",\n"
                        << "  \"clusterX\": " << g_proxy.clusterX << ",\n"
                        << "  \"clusterZ\": " << g_proxy.clusterZ << ",\n"
                        << "  \"sampleConvention\": {\"localU\": \"qx / 5.0\", \"localV\": \"qz / 5.0\", \"qxRange\": [0, 5], \"qzRange\": [0, 5]},\n"
                        << "  \"cells\": [\n";
                    for (size_t i = 0; i < count; ++i)
                    {
                        const Cell& cell = cells[i];
                        const unsigned typeA = (cell.word >> 12) & 0xF;
                        const unsigned typeB = (cell.word >> 8) & 0xF;
                        const unsigned mix = (cell.word >> 4) & 0xF;
                        const unsigned variant = cell.word & 0x3;
                        const unsigned lookupIndex = typeA * 64 + typeB * 8 + variant * 2 + ((mix >> 3) & 1);
                        output << "    {\"cellX\": " << cell.x
                            << ", \"cellZ\": " << cell.z
                            << ", \"terrainX\": " << cell.terrainX
                            << ", \"terrainZ\": " << cell.terrainZ
                            << ", \"terrainWord\": " << cell.word
                            << ", \"typeA\": " << typeA
                            << ", \"typeB\": " << typeB
                            << ", \"mix\": " << mix
                            << ", \"orientation\": " << mix
                            << ", \"variant\": " << variant
                            << ", \"lookupIndex\": " << lookupIndex
                            << ", \"tileIndex\": " << static_cast<unsigned>(cell.tileIndex)
                            << ", \"atlasRect\": {\"u\": " << cell.rect.u
                            << ", \"v\": " << cell.rect.v
                            << ", \"w\": " << cell.rect.w
                            << ", \"h\": " << cell.rect.h << "}}";
                        output << (i + 1 == count ? "\n" : ",\n");
                    }
                    output << "  ]\n}\n";
                    output.close();
                    LogShimA(LogLevel::Info, "terrain-semantic",
                        "[TERRAIN-SEMANTIC] captured cells=%zu json=written path=\"%s\"",
                        count, outputPath.string().c_str());
                }
                else
                {
                    LogShimA(LogLevel::Warn, "terrain-semantic",
                        "[TERRAIN-SEMANTIC] json write failed path=\"%s\"",
                        outputPath.string().c_str());
                }
            }
            else
            {
                LogShimA(LogLevel::Info, "terrain-semantic",
                    "[TERRAIN-SEMANTIC] captured cells=%zu json=disabled", count);
            }
        }

        struct ClusterCandidate
        {
            void* mesh = nullptr;
            void* entity = nullptr;
            void* node = nullptr;
            int clusterX = 0;
            int clusterZ = 0;
            std::string meshName;
            float cameraDistance = 0.0f;
            float coverage = 0.0f;
        };

        // Resolves and identity-checks one cluster of a zone. `abort` means the
        // layout assumption itself is wrong, so nothing in this zone can be
        // trusted and the whole scan stops. A merely absent cluster is not an
        // abort: camera-aware selection walks all sixteen, and one unpopulated
        // entry must not veto the other fifteen. For the single-candidate case
        // this is equivalent to the original behaviour, since the scan then
        // ends with nothing selected either way.
        bool ResolveClusterCandidate(void* zone, int zoneX, int zoneZ,
                                     int clusterX, int clusterZ,
                                     ClusterCandidate& candidate, bool& abort)
        {
            abort = false;
            const size_t meshOffset = kZoneMeshPtrBase +
                clusterX * kClusterXStride + clusterZ * kClusterZStride;
            const size_t pointerOffset = clusterX * 0x10 + clusterZ * 4;
            void* mesh = nullptr;
            void* entity = nullptr;
            void* node = nullptr;
            if (!SafeReadZonePointer(zone, meshOffset, mesh) ||
                !SafeReadZonePointer(zone, kZoneEntityBase + pointerOffset, entity) ||
                !SafeReadZonePointer(zone, kZoneNodeBase + pointerOffset, node) ||
                !mesh || !entity || !node)
            {
                return false;
            }
            const std::string* meshName = nullptr;
            try
            {
                meshName = g_ogre.getResourceName(mesh);
            }
            catch (...)
            {
                abort = true;
                return false;
            }
            int nameZoneX = 0;
            int nameZoneZ = 0;
            int nameClusterX = 0;
            int nameClusterZ = 0;
            if (!meshName ||
                !ParseTerrainMeshName(*meshName, nameZoneX, nameZoneZ, nameClusterX, nameClusterZ) ||
                nameZoneX != zoneX || nameZoneZ != zoneZ ||
                nameClusterX != clusterX || nameClusterZ != clusterZ)
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] native identity validation failed; selected cluster skipped");
                abort = true;
                return false;
            }
            candidate.mesh = mesh;
            candidate.entity = entity;
            candidate.node = node;
            candidate.clusterX = clusterX;
            candidate.clusterZ = clusterZ;
            candidate.meshName = *meshName;
            return true;
        }

        bool GetActiveCameraPosition(void*& camera, Vector3& position)
        {
            camera = nullptr;
            position = {};
            int width = 0;
            int height = 0;
            if (!GetActiveCamera(camera, width, height))
                return false;
            try
            {
                const Vector3* derived = g_ogre.getCameraDerivedPosition(camera);
                if (!derived)
                    return false;
                position = *derived;
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        // Rotates a vector by a quaternion: v' = v + 2w(q x v) + 2(q x (q x v)).
        Vector3 RotateByQuaternion(const Quaternion& q, const Vector3& v)
        {
            const Vector3 qv = { q.x, q.y, q.z };
            const Vector3 t = {
                2.0f * (qv.y * v.z - qv.z * v.y),
                2.0f * (qv.z * v.x - qv.x * v.z),
                2.0f * (qv.x * v.y - qv.y * v.x)
            };
            return {
                v.x + q.w * t.x + (qv.y * t.z - qv.z * t.y),
                v.y + q.w * t.y + (qv.z * t.x - qv.x * t.z),
                v.z + q.w * t.z + (qv.x * t.y - qv.y * t.x)
            };
        }

        // The ground the player is looking at: the player's own simulation
        // position pushed forward along the view direction. An Ogre camera
        // looks down local -Z.
        //
        // The origin is the player rather than the eye because the render
        // camera can be a chase or satellite view far from them, and because
        // the player is by definition standing on terrain, which makes the
        // containment test below resolve instead of falling between clusters.
        // The eye is used only as a fallback before the player object exists.
        // A whole BZ98R map is 4x4 zones of 1,280 units. Anything further than
        // this between the player and the render camera is a bad read.
        constexpr float kMaxPlayerEyeSeparation = 5120.0f;
        bool g_playerPositionRejectedLogged = false;

        bool GetCameraAimPoint(void* camera, float aimDistance, Vector3& aim,
                               bool& usedPlayer)
        {
            aim = {};
            usedPlayer = false;
            if (!g_ogre.getCameraDerivedPosition || !g_ogre.getCameraDerivedOrientation)
                return false;
            try
            {
                const Vector3* eye = g_ogre.getCameraDerivedPosition(camera);
                const Quaternion* orientation = g_ogre.getCameraDerivedOrientation(camera);
                if (!eye || !orientation)
                    return false;

                Vector3 origin = *eye;
                float playerX = 0.0f;
                float playerY = 0.0f;
                float playerZ = 0.0f;
                if (TryGetLocalPlayerWorldPosition(playerX, playerY, playerZ))
                {
                    // Sanity-gate the simulation read against the render camera.
                    // Even a chase or satellite view stays within a few hundred
                    // units of the player, so a position further away than a
                    // whole map is a bad read, not a distant player. Observed:
                    // z reads ~100797 on a 5120-unit map while x and y look
                    // sane, which then makes every zone fail containment and
                    // the mode defer forever. Falling back to the eye keeps
                    // selection working while that offset is chased down.
                    const float dx = playerX - eye->x;
                    const float dy = playerY - eye->y;
                    const float dz = playerZ - eye->z;
                    const bool finite = std::isfinite(playerX) &&
                                        std::isfinite(playerY) &&
                                        std::isfinite(playerZ);
                    const float distanceSquared = dx * dx + dy * dy + dz * dz;
                    if (finite && distanceSquared <=
                            kMaxPlayerEyeSeparation * kMaxPlayerEyeSeparation)
                    {
                        origin = { playerX, playerY, playerZ };
                        usedPlayer = true;
                    }
                    else if (!g_playerPositionRejectedLogged)
                    {
                        g_playerPositionRejectedLogged = true;
                        LogShimA(LogLevel::Warn, "terrain-proxy",
                            "[TERRAIN-PROXY] follow-camera rejecting implausible player position player=(%.1f,%.1f,%.1f) eye=(%.1f,%.1f,%.1f) separation=%.1f limit=%.1f; anchoring on the camera instead",
                            static_cast<double>(playerX), static_cast<double>(playerY),
                            static_cast<double>(playerZ), static_cast<double>(eye->x),
                            static_cast<double>(eye->y), static_cast<double>(eye->z),
                            static_cast<double>(std::sqrt(distanceSquared)),
                            static_cast<double>(kMaxPlayerEyeSeparation));
                    }
                }

                const Vector3 forward =
                    RotateByQuaternion(*orientation, Vector3{ 0.0f, 0.0f, -1.0f });
                aim.x = origin.x + forward.x * aimDistance;
                aim.y = origin.y + forward.y * aimDistance;
                aim.z = origin.z + forward.z * aimDistance;
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        // Ground-plane distance from the aim point to a cluster's world bounds,
        // zero when the aim point lands inside it. This is the whole selection
        // rule: take the ground the player is looking at.
        //
        // It deliberately replaces an earlier screen-coverage ranking, which
        // systematically preferred distant clusters: a cluster you are standing
        // on has most of its corners behind the eye plane, so a rect built only
        // from in-front corners underestimates exactly the cluster that fills
        // the view. Y is ignored because terrain clusters tile the XZ plane.
        bool ScoreClusterAgainstAim(void* entity, const Vector3& aim,
                                    float& groundDistance, bool& contains)
        {
            groundDistance = 0.0f;
            contains = false;
            try
            {
                const AxisAlignedBox* bounds = g_ogre.getWorldBoundingBox(entity, true);
                if (!bounds || bounds->extent != kAabbExtentFinite)
                    return false;
                const float dx = (std::max)(
                    (std::max)(bounds->minimum.x - aim.x, aim.x - bounds->maximum.x), 0.0f);
                const float dz = (std::max)(
                    (std::max)(bounds->minimum.z - aim.z, aim.z - bounds->maximum.z), 0.0f);
                contains = dx <= 0.0f && dz <= 0.0f;
                groundDistance = std::sqrt(dx * dx + dz * dz);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        uint32_t g_followCameraDeferrals = 0;
        bool g_followCameraUnavailableLogged = false;

        // Camera-aware selection needs the projection API. If it is missing the
        // mode stands down to ordinal selection rather than never selecting.
        bool FollowCameraUsable()
        {
            if (!g_config.followCamera)
                return false;
            if (CaptureFramingApiAvailable())
                return true;
            if (!g_followCameraUnavailableLogged)
            {
                g_followCameraUnavailableLogged = true;
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] TerrainProxyFollowCamera requested but the OGRE camera exports are unresolved; falling back to ordinal selection");
            }
            g_config.followCamera = false;
            return false;
        }

        bool ObserveZone(void* zone)
        {
            if (!zone || g_proxy.tearingDown || g_proxy.selected || !g_discoveryArmed)
                return g_proxy.selected;
            int zoneX = 0;
            int zoneZ = 0;
            if (!SafeReadZoneInt(zone, kZoneXOffset, zoneX) ||
                !SafeReadZoneInt(zone, kZoneZOffset, zoneZ))
                return false;
            int zoneOrdinal = 0;
            const auto existing = g_zoneOrdinals.find(zone);
            if (existing != g_zoneOrdinals.end())
                zoneOrdinal = existing->second;
            else
            {
                zoneOrdinal = g_nextZoneOrdinal++;
                g_zoneOrdinals.emplace(zone, zoneOrdinal);
            }

            const bool followCamera = FollowCameraUsable();
            void* camera = nullptr;
            Vector3 cameraPosition = {};
            Vector3 aim = {};
            bool aimUsedPlayer = false;
            int viewportWidth = 0;
            int viewportHeight = 0;
            if (followCamera &&
                (!GetActiveCameraPosition(camera, cameraPosition) ||
                 !GetActiveCamera(camera, viewportWidth, viewportHeight) ||
                 !GetCameraAimPoint(camera, g_config.followCameraAimDistance, aim,
                     aimUsedPlayer)))
            {
                // Zone construction can precede the gameplay camera. The
                // rebuild dispatcher calls back on later dispatches, so defer
                // rather than settle for a cluster nobody will ever see.
                return false;
            }

            ClusterCandidate best;
            bool haveBest = false;
            int evaluated = 0;
            int visible = 0;
            for (int ordinal = 0; ordinal < kClusterAxisCount * kClusterAxisCount; ++ordinal)
            {
                const int clusterX = ordinal / kClusterAxisCount;
                const int clusterZ = ordinal % kClusterAxisCount;
                if (!MatchExplicitSelection(zoneOrdinal, zoneX, zoneZ, clusterX, clusterZ))
                    continue;
                if (!followCamera &&
                    !MatchSelection(zoneOrdinal, zoneX, zoneZ, clusterX, clusterZ))
                    continue;

                ClusterCandidate candidate;
                bool abort = false;
                if (!ResolveClusterCandidate(zone, zoneX, zoneZ, clusterX, clusterZ,
                        candidate, abort))
                {
                    if (abort)
                        return false;
                    continue;
                }
                ++evaluated;

                if (!followCamera)
                {
                    best = candidate;
                    haveBest = true;
                    break;
                }

                float groundDistance = 0.0f;
                bool contains = false;
                if (!ScoreClusterAgainstAim(candidate.entity, aim,
                        groundDistance, contains))
                    continue;
                // Containment, not proximity. ObserveZone only ever sees the
                // clusters of the zone currently being dispatched, so a
                // "nearest within N units" rule happily settles for a cluster
                // 2,000 units from where the player is looking simply because
                // the right zone had not been dispatched yet. Requiring the
                // aim point to land inside the cluster makes the wrong zone
                // defer, and zones are re-dispatched constantly.
                if (!contains)
                    continue;
                ++visible;
                candidate.cameraDistance = groundDistance;
                best = candidate;
                haveBest = true;
                break;
            }

            if (!haveBest)
            {
                if (followCamera)
                {
                    // Runs per zone per dispatch, so report the first deferral
                    // and then only occasionally.
                    const uint32_t deferrals = ++g_followCameraDeferrals;
                    if (deferrals == 1 || deferrals % 600 == 0)
                    {
                        LogShimA(LogLevel::Info, "terrain-proxy",
                            "[TERRAIN-PROXY] follow-camera deferring selection zone=%d nativeZone=(%d,%d) evaluated=%d containing=%d aim=(%.1f,%.1f,%.1f) aimOrigin=%s deferrals=%u",
                            zoneOrdinal, zoneX, zoneZ, evaluated, visible,
                            static_cast<double>(aim.x), static_cast<double>(aim.y),
                            static_cast<double>(aim.z),
                            aimUsedPlayer ? "player" : "camera", deferrals);
                    }
                }
                return false;
            }

            {
                const int clusterX = best.clusterX;
                const int clusterZ = best.clusterZ;
                void* const mesh = best.mesh;
                void* const entity = best.entity;
                void* const node = best.node;
                const std::string* const meshName = &best.meshName;
                    void* sceneManager = SafeGetSceneManager();
                    if (!sceneManager)
                        return false;

                    g_proxy.selected = true;
                    g_proxy.zone = zone;
                    g_proxy.sceneManager = sceneManager;
                    g_proxy.sourceMesh = mesh;
                    g_proxy.sourceEntity = entity;
                    g_proxy.sourceNode = node;
                    g_proxy.zoneOrdinal = zoneOrdinal;
                    g_proxy.zoneX = zoneX;
                    g_proxy.zoneZ = zoneZ;
                    g_proxy.clusterOrdinal = clusterX * kClusterAxisCount + clusterZ;
                    g_proxy.clusterX = clusterX;
                    g_proxy.clusterZ = clusterZ;
                    g_proxy.sourceMeshName = *meshName;
                    CaptureClusterHeightSignature(
                        g_proxy.heightHash, g_proxy.heightMinimum, g_proxy.heightMaximum);
                    LogShimA(LogLevel::Info, "terrain-proxy",
                        "[TERRAIN-PROXY] selected zone=%d nativeZone=(%d,%d) cluster=%d nativeCluster=(%d,%d) zonePtr=%p sourceMesh=%p sourceEntity=%p sourceNode=%p heightHash=%08X heightRange=[%u,%u] followCamera=%d evaluated=%d containing=%d aim=(%.1f,%.1f,%.1f) aimOrigin=%s aimAhead=%.1f aimGap=%.1f mesh=\"%s\"",
                        zoneOrdinal, zoneX, zoneZ, g_proxy.clusterOrdinal, clusterX, clusterZ,
                        g_proxy.zone, g_proxy.sourceMesh, g_proxy.sourceEntity,
                        g_proxy.sourceNode, g_proxy.heightHash,
                        static_cast<unsigned>(g_proxy.heightMinimum),
                        static_cast<unsigned>(g_proxy.heightMaximum),
                        followCamera ? 1 : 0, evaluated, visible,
                        static_cast<double>(aim.x), static_cast<double>(aim.y),
                        static_cast<double>(aim.z),
                        aimUsedPlayer ? "player" : "camera",
                        static_cast<double>(g_config.followCameraAimDistance),
                        static_cast<double>(best.cameraDistance),
                        g_proxy.sourceMeshName.c_str());
                    CreateProxy();
                    CaptureSemantics(true);
                    BuildAndValidateSemanticVertices(true);
                    // With the proxy live, report where it actually lands on
                    // screen. This is the value the harness needs and the one
                    // that was missing when sixteen captures returned static UI.
                    ProxyScreenRect rect;
                    if (QueryProxyScreenRect(rect))
                    {
                        LogShimA(LogLevel::Info, "terrain-proxy",
                            "[TERRAIN-PROXY] proxy framing visible=%d cornersInFront=%d coverage=%.5f viewport=%dx%d region=%d,%d,%d,%d",
                            rect.visible ? 1 : 0, rect.cornersInFront,
                            static_cast<double>(rect.coverage),
                            rect.viewportWidth, rect.viewportHeight,
                            rect.left, rect.top,
                            (std::max)(0, rect.right - rect.left),
                            (std::max)(0, rect.bottom - rect.top));
                    }
                    return true;
            }
        }

        void* __fastcall ZoneConstructHook(
            void* zone, void*, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
        {
            void* constructedZone = zone;
            if (g_originalZoneConstruct)
                constructedZone = g_originalZoneConstruct(zone, a, b, c, d);
            if (!g_active.load(std::memory_order_acquire) || g_shutdown.load())
                return constructedZone;
            std::lock_guard<std::mutex> lock(g_mutex);
            ObserveZone(zone);
            return constructedZone;
        }

        void __fastcall ZoneProcessHook(void* zone, void*)
        {
            // FUN_00778450 immediately reads zone+0x270. A null entry means
            // the manager's zone table has already been corrupted or is not
            // ready, so forwarding it can only AV. This is a bounded fail-soft
            // backstop; healthy runs must leave the counter at zero.
            if (!zone)
            {
                const uint32_t count = g_nullZoneDispatchCount.fetch_add(
                    1, std::memory_order_relaxed) + 1;
                if (count <= 4)
                {
                    LogShimA(LogLevel::Warn, "terrain-proxy",
                        "[TERRAIN-PROXY] skipped invalid null zone rebuild dispatch count=%u",
                        count);
                }
                return;
            }

            bool selectedZone = false;
            bool fullDirty = false;
            bool heightDirty = false;
            int clusterX = 0;
            int clusterZ = 0;
            if (g_active.load(std::memory_order_acquire) && !g_shutdown.load())
            {
                std::lock_guard<std::mutex> lock(g_mutex);
                selectedZone = g_proxy.selected && !g_proxy.tearingDown && g_proxy.zone == zone;
                if (selectedZone)
                {
                    clusterX = g_proxy.clusterX;
                    clusterZ = g_proxy.clusterZ;
                    const size_t index = static_cast<size_t>(clusterX * 4 + clusterZ);
                    uint8_t full = 0;
                    uint8_t height = 0;
                    uint8_t nextHeight = 0;
                    SafeReadZoneByte(zone, kFullDirtyOffset + index, full);
                    SafeReadZoneByte(zone, kHeightDirtyOffset + index, height);
                    SafeReadZoneByte(zone, kHeightDirtyNextOffset + index, nextHeight);
                    fullDirty = full != 0;
                    heightDirty = height != 0 || nextHeight != 0;
                }
            }

            if (g_originalZoneProcess)
                g_originalZoneProcess(zone);
            if (!g_active.load(std::memory_order_acquire) || g_shutdown.load())
                return;
            std::lock_guard<std::mutex> lock(g_mutex);
            // The engine can destroy the proxy Entity at any point during a
            // mission change. Detect that by name before anything dereferences
            // the stored pointer, and forget so the next qualifying zone in
            // this same dispatch rebuilds the proxy instead of leaving the
            // mission silently without a semantic terrain.
            if (g_proxy.proxyCreated && !g_proxy.tearingDown &&
                !ProxyEntityStillRegistered())
            {
                ++g_proxyLostCount;
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] proxy entity destroyed by the engine proxyGeneration=%u missionGeneration=%u entity=\"%s\" losses=%u; rebuilding",
                    g_proxy.generation, g_missionGeneration,
                    g_proxy.proxyEntityName.c_str(), g_proxyLostCount);
                selectedZone = false;
                ForgetTerrainProxy(TerrainForgetReason::ProxyLost, true, true);
            }
            // Honour a re-selection raised by the render tick. Doing it here
            // rather than in the tick keeps proxy destruction on the seam that
            // already handles it, instead of inside render-queue traversal.
            // ObserveZone scores against the current camera, so a cluster that
            // is behind the player cannot simply be re-chosen.
            if (g_reselectRequested && !g_proxy.tearingDown)
            {
                g_reselectRequested = false;
                g_unframedStreak = 0;
                if (g_proxy.proxyCreated)
                {
                    ++g_reselectCount;
                    LogShimA(LogLevel::Info, "terrain-proxy",
                        "[TERRAIN-PROXY] follow-camera reselecting proxyGeneration=%u cluster=(%d,%d) reselects=%u/%u",
                        g_proxy.generation, g_proxy.clusterX, g_proxy.clusterZ,
                        g_reselectCount, kMaxReselects);
                    selectedZone = false;
                    ForgetTerrainProxy(TerrainForgetReason::FramingStale, true, true);
                }
            }
            // Retry-path source verification. A stored sourceMesh/Entity/Node
            // triple can predate an engine-side rebuild of this cluster; every
            // dereference below CreateProxy is a virtual call on that stored
            // state, and catch(...) cannot intercept the resulting fault under
            // /EHsc. Require the live zone table to still advertise exactly the
            // stored objects (SEH reads plus mesh-name identity) before they
            // are used again. An unreadable table without a layout abort is
            // not proof of staleness: fail open and keep waiting.
            if (!g_proxy.proxyCreated && !g_proxy.tearingDown &&
                g_proxy.selected && g_proxy.zone == zone)
            {
                ClusterCandidate fresh;
                bool layoutAbort = false;
                const bool resolved = ResolveClusterCandidate(
                    zone, g_proxy.zoneX, g_proxy.zoneZ,
                    g_proxy.clusterX, g_proxy.clusterZ, fresh, layoutAbort);
                const bool sourcesVerified = layoutAbort ? false :
                    (!resolved || (fresh.mesh == g_proxy.sourceMesh &&
                                   fresh.entity == g_proxy.sourceEntity &&
                                   fresh.node == g_proxy.sourceNode));
                if (!sourcesVerified)
                {
                    ++g_sourceMismatchForgetCount;
                    LogShimA(LogLevel::Warn, "terrain-proxy",
                        "[TERRAIN-PROXY] stored source objects no longer match the live zone table proxyGeneration=%u missionGeneration=%u losses=%u; reselecting",
                        g_proxy.generation, g_missionGeneration,
                        g_sourceMismatchForgetCount);
                    selectedZone = false;
                    ForgetTerrainProxy(TerrainForgetReason::SourceMismatch, true, true);
                }
            }
            if (!g_proxy.selected && !g_proxy.tearingDown)
                ObserveZone(zone);
            if (selectedZone && !g_proxy.tearingDown && g_proxy.zone == zone &&
                (fullDirty || heightDirty))
            {
                if (g_config.proxyEnabled)
                {
                    if (!g_proxy.proxyCreated)
                        CreateProxy();
                    if (g_proxy.proxyCreated)
                        RefreshProxyBuffers(fullDirty, heightDirty);
                }
                if (fullDirty)
                {
                    // Record the owner/resource identity across a real stock
                    // full rebuild. Redux's full path (FUN_007794F0) repopulates
                    // slots 1 and 2 in place, so the expected outcome is a
                    // retained slot-3 owner with a regenerated payload; an owner
                    // replacement is detected and re-generationed inside
                    // InstallOrRefreshSemanticStream.
                    const uint32_t beforeVbGeneration = g_proxy.semanticVbGeneration;
                    void* const beforeBuffer = g_proxy.semanticBuffer;
                    const uint32_t beforePayloadHash = g_proxy.semanticDataHash;
                    const uint32_t beforeUploads = g_proxy.semanticUploadCount;
                    const size_t beforeVertexCount = g_proxy.semanticVertices.size();
                    const std::string beforeMaterial = g_proxy.semanticMaterialName;
                    CaptureSemantics(false);
                    BuildAndValidateSemanticVertices(false);
                    if (g_config.semanticRenderer)
                    {
                        SemanticBinding binding;
                        const bool queried = QuerySemanticBinding(binding);
                        const bool retainedOwner = queried && binding.slotPresent &&
                            binding.buffer == g_proxy.semanticBuffer &&
                            binding.stride == sizeof(TerrainSemantic::GpuVertex);
                        if (queried)
                            ValidateSemanticBinding("full_rebuild", binding);
                        LogShimA(retainedOwner ? LogLevel::Info : LogLevel::Warn,
                            "terrain-p3",
                            "[TERRAIN-P3] terrain_semantic: full_rebuild owner=%p proxyGeneration=%u fullRefreshes=%u vbGeneration=%u->%u vb=%p->%p ownerReplaced=%d payloadHash=%08X->%08X payloadChanged=%d vertices=%zu->%zu uploads=%u->%u slot3Present=%d stride=%u declaration={localUv:%d,semantic:%d,atlasRect:%d,audited:%d} material=\"%s\"->\"%s\" activeMaterial=\"%s\" semanticMaterial=%d",
                            g_proxy.zone, g_proxy.generation,
                            g_proxy.fullRefreshCount, beforeVbGeneration,
                            g_proxy.semanticVbGeneration, beforeBuffer,
                            g_proxy.semanticBuffer,
                            beforeBuffer && beforeBuffer != g_proxy.semanticBuffer ? 1 : 0,
                            beforePayloadHash, g_proxy.semanticDataHash,
                            beforePayloadHash != g_proxy.semanticDataHash ? 1 : 0,
                            beforeVertexCount, g_proxy.semanticVertices.size(),
                            beforeUploads, g_proxy.semanticUploadCount,
                            binding.slotPresent ? 1 : 0, binding.stride,
                            binding.declarationLocalUv ? 1 : 0,
                            binding.declarationSemantic ? 1 : 0,
                            binding.declarationAtlasRect ? 1 : 0,
                            binding.declarationAudited ? 1 : 0,
                            beforeMaterial.c_str(),
                            g_proxy.semanticMaterialName.c_str(),
                            binding.materialName.c_str(),
                            binding.materialIsSemantic ? 1 : 0);
                        g_proxy.semanticBindingSignature =
                            queried ? binding.Signature() : 0;
                    }
                }
            }
            ++g_zoneDispatchCount;
            if (g_config.semanticLifecycleLog &&
                (g_zoneDispatchCount == 1 || g_zoneDispatchCount == 25 ||
                 g_zoneDispatchCount == 100 || g_zoneDispatchCount == 1000))
            {
                LogShimA(LogLevel::Info, "terrain-p3",
                    "[TERRAIN-P3] terrain_semantic: zone_dispatch count=%u (rebuild-dispatcher cadence probe)",
                    g_zoneDispatchCount);
            }
        }

        // Mission lifetime boundary. Leaving RUN_STARTED is the point at which
        // the current mission stops being simulated; Redux then reloads a map
        // and re-enters RUN_STARTED. The scene is still fully alive here --
        // the zone destructor (FUN_00777EF0) has not run yet -- so this is the
        // seam at which OpenShim can both destroy what it owns and forget the
        // rest without ever touching a destroyed object.
        void OnRunStateChanged(int previous, int current)
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            const bool wasRunning = previous == kRunStateStarted;
            const bool isRunning = current == kRunStateStarted;
            if (g_config.semanticLifecycleLog || wasRunning || isRunning)
            {
                LogShimA(LogLevel::Info, "terrain-proxy",
                    "[TERRAIN-PROXY] run-state was=%s(%d) now=%s(%d) missionGeneration=%u selected=%d proxyGeneration=%u",
                    RunStateName(previous), previous, RunStateName(current),
                    current, g_missionGeneration, g_proxy.selected ? 1 : 0,
                    g_proxy.generation);
            }
            if (wasRunning && !isRunning)
            {
                // Disarm before forgetting: the outgoing mission's zone stays
                // alive and keeps dispatching for the rest of the teardown, and
                // re-selecting it would only build a proxy for a scene that is
                // about to go away.
                g_discoveryArmed = false;
                ForgetTerrainProxy(TerrainForgetReason::MissionTransition, true, true);
            }
            if (isRunning && !wasRunning)
            {
                ++g_missionGeneration;
                g_discoveryArmed = true;
                LogShimA(LogLevel::Info, "terrain-proxy",
                    "[TERRAIN-PROXY] lifecycle mission-arm missionGeneration=%u armed=1 forgets=%u forgetNoops=%u proxyLosses=%u sceneTeardownSeamsObserved=%u",
                    g_missionGeneration, g_missionForgetCount,
                    g_missionForgetNoopCount, g_proxyLostCount,
                    g_sceneTeardownObservations);
            }
        }

        bool InstallHooks()
        {
            g_mainBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
            if (!g_mainBase)
                return false;
            static const uint8_t expectedEntry[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
            const uintptr_t constructor = Rebase(kZoneConstructVa);
            const uintptr_t process = Rebase(kZoneProcessVa);
            if (!ExpectedBytesMatchAt(constructor, expectedEntry, sizeof(expectedEntry)) ||
                !ExpectedBytesMatchAt(process, expectedEntry, sizeof(expectedEntry)))
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] released function entry bytes mismatched; Phase 2 unavailable");
                return false;
            }
            if (!InstallInlineDetour32(g_zoneConstructDetour, constructor,
                    reinterpret_cast<void*>(ZoneConstructHook), sizeof(expectedEntry),
                    expectedEntry, sizeof(expectedEntry)))
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] hook install failed; Phase 2 remains inert");
                return false;
            }
            g_originalZoneConstruct = reinterpret_cast<FnZoneConstruct>(g_zoneConstructDetour.trampoline);

            // Assign the first trampoline before attempting the second detour.
            // If the second install fails, the process-lifetime constructor
            // detour remains a transparent call-through while g_active is false.
            if (!InstallInlineDetour32(g_zoneProcessDetour, process,
                    reinterpret_cast<void*>(ZoneProcessHook), sizeof(expectedEntry),
                    expectedEntry, sizeof(expectedEntry)))
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] rebuild hook install failed; constructor observation remains inert");
                return false;
            }
            g_originalZoneProcess = reinterpret_cast<FnZoneProcess>(g_zoneProcessDetour.trampoline);
            // The mission lifetime seam itself lives in bzr_hooks: chunk
            // proxies and the multiplayer flag need it whether or not the
            // opt-in terrain proxy is configured. This module only subscribes,
            // through TerrainProxyMissionRunStateChanged.
            SafeReadRunState(g_lastRunState);
            g_runStateHookInstalled =
                RunStateNameMatches(kRunStateStarted, kRunStateStartedName);
            // If a mission is already running when Phase 2 comes up, no arming
            // transition will be observed for it, so adopt the current state.
            g_discoveryArmed = g_lastRunState == kRunStateStarted;
            g_terrainWordAt = reinterpret_cast<FnTerrainWordAt>(Rebase(kTerrainWordAtVa));
            g_heightAt = reinterpret_cast<FnHeightAt>(Rebase(kHeightAtVa));
            g_terrainManager = reinterpret_cast<FnTerrainManager>(Rebase(kTerrainManagerVa));
            g_atlasRectAt = reinterpret_cast<FnAtlasRectAt>(Rebase(kAtlasRectAtVa));
            g_tileIndexAt = reinterpret_cast<FnTileIndexAt>(Rebase(kTileIndexAtVa));
            g_mixAt = reinterpret_cast<FnMixAt>(Rebase(kMixAtVa));
            g_active.store(true, std::memory_order_release);
            return true;
        }

        DWORD WINAPI WorkerProc(void*)
        {
            HMODULE executable = GetModuleHandleW(nullptr);
            std::string exeHash;
            if (!VerifyModuleHash(executable, kExpectedExeSha256, exeHash))
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] exact executable build not validated sha256=%s; Phase 2 unavailable",
                    exeHash.empty() ? "<unavailable>" : exeHash.c_str());
                return 0;
            }
            LogShimA(LogLevel::Info, "terrain-proxy", "[TERRAIN-PROXY] exact executable build validated");

            // The follow-camera aim point anchors on the player, which needs the
            // GOG-build player-handle lookup wired up. The hash check above is
            // what makes that address safe to take.
            ResolveLocalPlayerLookupForVerifiedGogBuild();

            HMODULE ogre = nullptr;
            for (int attempt = 0; attempt < 600 && !g_shutdown.load(); ++attempt)
            {
                ogre = GetModuleHandleW(L"OgreMain.dll");
                if (ogre)
                    break;
                Sleep(100);
            }
            if (!ogre || g_shutdown.load())
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] OgreMain.dll unavailable; Phase 2 not installed");
                return 0;
            }
            std::string ogreHash;
            if (!VerifyModuleHash(ogre, kExpectedOgreSha256, ogreHash))
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] exact Ogre build not validated sha256=%s; Phase 2 unavailable",
                    ogreHash.empty() ? "<unavailable>" : ogreHash.c_str());
                return 0;
            }
            if (!ResolveOgreApi(ogre))
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] required Ogre exports unresolved; Phase 2 unavailable");
                return 0;
            }
            if (InstallHooks())
            {
                LogShimA(LogLevel::Info, "terrain-proxy",
                    "[TERRAIN-PROXY] hooks installed constructor=0x%08X rebuild=0x%08X missionSeam=0x%08X runStateTable=%s initialRunState=%s(%d)",
                    static_cast<unsigned>(Rebase(kZoneConstructVa)),
                    static_cast<unsigned>(Rebase(kZoneProcessVa)),
                    static_cast<unsigned>(Rebase(kSetRunningVa)),
                    g_runStateHookInstalled ? "verified" : "mismatched",
                    RunStateName(g_lastRunState), g_lastRunState);
            }
            return 0;
        }
    }

    void InitializeTerrainProxyPhase2()
    {
        if (g_worker || g_active.load())
            return;
        g_config = ReadConfig();
        if (g_config.hdEnabled)
        {
            // The HD smoke path is a Phase 3B specialization of the semantic
            // proxy. One opt-in switch activates its two prerequisites so a
            // missing secondary setting cannot silently turn the test into a
            // stock-atlas run.
            if (LoadTerrainHdManifest())
            {
                g_config.proxyEnabled = true;
                g_config.semanticRenderer = true;
            }
            else
                g_config.hdEnabled = false;
        }
        if (g_config.semanticRenderer && !g_config.proxyEnabled)
        {
            LogShimA(LogLevel::Warn, "terrain-p3",
                "[TERRAIN-P3] TerrainSemanticRenderer requires TerrainProxyEnabled=1; renderer disabled");
            g_config.semanticRenderer = false;
        }
        if (!g_config.proxyEnabled && !g_config.semanticCapture &&
            !g_config.semanticValidateUv && !g_config.semanticRenderer)
            return;
        g_shutdown.store(false);
        LogShimA(LogLevel::Info, "terrain-proxy",
            "[TERRAIN-PROXY] phase2 initialized proxy=%d semantic=%d (features default off)",
            g_config.proxyEnabled ? 1 : 0, g_config.semanticCapture ? 1 : 0);
        if (g_config.semanticValidateUv || g_config.semanticRenderer)
        {
            LogShimA(LogLevel::Info, "terrain-p3",
                "[TERRAIN-P3] initialized renderer=%d validateUV=%d legacyUVQuantization=%d debug=%s(%d) lifecycleLog=%d (features default off)",
                g_config.semanticRenderer ? 1 : 0,
                g_config.semanticValidateUv ? 1 : 0,
                g_config.semanticLegacyUvQuantization ? 1 : 0,
                SemanticDebugModeName(g_config.semanticDebugMode),
                g_config.semanticDebugMode,
                g_config.semanticLifecycleLog ? 1 : 0);
        }
        if (g_config.hdEnabled)
        {
            LogShimA(LogLevel::Info, "terrain-hd",
                "[TERRAIN-HD] initialized manifest=\"%s\" proxy=1 semanticRenderer=1 stockFallback=enabled",
                g_hdManifest.path.string().c_str());
        }
        g_worker = CreateThread(nullptr, 0, WorkerProc, nullptr, 0, nullptr);
        if (!g_worker)
            LogShimA(LogLevel::Warn, "terrain-proxy", "[TERRAIN-PROXY] discovery worker creation failed");
    }

    void ShutdownTerrainProxyPhase2()
    {
        g_shutdown.store(true);
        g_active.store(false);
        if (g_worker)
        {
            WaitForSingleObject(g_worker, 2000);
            CloseHandle(g_worker);
            g_worker = nullptr;
        }
        std::lock_guard<std::mutex> lock(g_mutex);
        // Process shutdown can run after OGRE has already gone away, so this
        // path forgets by name only and never touches a scene object.
        ForgetTerrainProxy(TerrainForgetReason::ProcessShutdown, false, false);
    }

    void TerrainProxyRenderFrameTick()
    {
        // Cheap early-out: this runs on every rendered world frame and must
        // cost nothing when the opt-in capture is off.
        if (g_config.semanticFrameCaptures <= 0 || !g_active.load() ||
            g_shutdown.load())
            return;
        std::lock_guard<std::mutex> lock(g_mutex);
        if (!g_proxy.proxyCreated || g_proxy.tearingDown)
            return;
        ++g_semanticRenderFrames;
        MaybeCaptureSemanticFrame();
    }

    void TerrainProxyMissionRunStateChanged(int previousState, int currentState)
    {
        if (!g_active.load(std::memory_order_acquire) || g_shutdown.load())
            return;
        OnRunStateChanged(previousState, currentState);
        g_lastRunState = currentState;
    }

    void TerrainProxySceneTeardownBegin(void* sceneManager, bool clearScene)
    {
        if (!g_active.load() || g_shutdown.load())
            return;
        std::lock_guard<std::mutex> lock(g_mutex);
        // Record that the seam fired at all. Redux never calls clearScene or
        // destroyAllMovableObjects, so a nonzero count here is evidence that
        // some other component (or a future build) does.
        if (g_sceneTeardownObservations < 8)
        {
            ++g_sceneTeardownObservations;
            LogShimA(LogLevel::Info, "terrain-proxy",
                "[TERRAIN-PROXY] scene-teardown seam observed reason=%s sceneManager=%p selected=%d missionGeneration=%u count=%u",
                clearScene ? "clearScene" : "destroyAllMovableObjects",
                sceneManager, g_proxy.selected ? 1 : 0, g_missionGeneration,
                g_sceneTeardownObservations);
        }
        if (!g_proxy.selected || (g_proxy.sceneManager && g_proxy.sceneManager != sceneManager))
            return;
        if (g_teardownDepth == 0)
        {
            g_proxy.tearingDown = true;
            LogShimA(LogLevel::Info, "terrain-proxy",
                "[TERRAIN-PROXY] lifecycle teardown-begin generation=%u reason=%s sceneManager=%p zonePtr=%p sourceMesh=%p proxyMesh=%p proxyEntity=%p proxyNode=%p",
                g_proxy.generation, clearScene ? "clearScene" : "destroyAllMovableObjects",
                sceneManager, g_proxy.zone, g_proxy.sourceMesh, g_proxy.proxyMesh,
                g_proxy.proxyEntity, g_proxy.proxyNode);
        }
        ++g_teardownDepth;
        g_teardownIncludesClear = g_teardownIncludesClear || clearScene;
    }

    void TerrainProxySceneTeardownComplete(void* sceneManager, bool clearScene)
    {
        if (!g_active.load() || g_shutdown.load())
            return;
        std::lock_guard<std::mutex> lock(g_mutex);
        if (!g_proxy.selected || (g_proxy.sceneManager && g_proxy.sceneManager != sceneManager) || g_teardownDepth <= 0)
            return;
        g_teardownIncludesClear = g_teardownIncludesClear || clearScene;
        --g_teardownDepth;
        if (g_teardownDepth != 0)
            return;
        // Both seams run after the stock call, so whatever the stock teardown
        // already destroyed simply reports absent by name.
        LogShimA(LogLevel::Info, "terrain-proxy",
            "[TERRAIN-PROXY] lifecycle released generation=%u reason=%s sceneManager=%p zonePtr=%p sourceMesh=%p proxyMesh=%p proxyEntity=%p proxyNode=%p refreshes={height:%u,full:%u,total:%u} semantic={builds:%u,uploads:%u,unchanged:%u}",
            g_proxy.generation,
            g_teardownIncludesClear ? "clearScene" : "destroyAllMovableObjects",
            sceneManager, g_proxy.zone, g_proxy.sourceMesh, g_proxy.proxyMesh,
            g_proxy.proxyEntity, g_proxy.proxyNode, g_proxy.heightRefreshCount,
            g_proxy.fullRefreshCount, g_proxy.rebuildCount,
            g_proxy.semanticBuildCount, g_proxy.semanticUploadCount,
            g_proxy.semanticUnchangedCount);
        ForgetTerrainProxy(TerrainForgetReason::SceneTeardown, true, true);
    }
}
