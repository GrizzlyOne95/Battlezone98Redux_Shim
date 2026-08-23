#include "ogre_animation_profiler.h"
#include "ogre_profiler_algorithms.h"
#include "ogre_runtime.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <TlHelp32.h>
#include <d3d11.h>
#include <d3d9.h>
#include <dxgi.h>
#include <process.h>

// The retail BZR Ogre is not ABI-identical to pristine upstream 1.10.0.
// We use the pinned headers only for the small POD-facing VertexData surface
// needed by this diagnostic, and sanity-check vertexCount before recording it.
#ifndef register
#define OPENSHIM_OGRE_RESTORE_REGISTER
#define register
#endif
#ifndef _STLP_MSVC
#define _STLP_MSVC 1
#endif
#include <OgreVertexIndexData.h>
#include <OgreHardwareBufferManager.h>
#include <OgreRenderOperation.h>
#ifdef OPENSHIM_OGRE_RESTORE_REGISTER
#undef register
#undef OPENSHIM_OGRE_RESTORE_REGISTER
#endif

#include <array>
#include <atomic>
#include <bit>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <limits>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "ogre-profile";
        constexpr char kEnvironmentSwitch[] = "OPENSHIM_PROFILE_OGRE_ANIMATION";
        // Measurement-only render isolation. Set OPENSHIM_PROFILE_ISOLATE to a
        // '+'-separated list of categories to suppress while capturing, so the
        // frame-time cost of a category can be measured rather than inferred
        // from its submission count. This deliberately changes what is drawn and
        // is never enabled by default; it exists so an A/B has a real arm.
        //   glow    - every technique whose scheme is "glow"
        //   shadow  - every renderable submitted to a shadow-texture camera
        constexpr char kIsolationSwitch[] = "OPENSHIM_PROFILE_ISOLATE";
        constexpr unsigned kIsolateGlow = 1u << 0;
        constexpr unsigned kIsolateShadow = 1u << 1;
        constexpr char kDisableChunkShadowFixSwitch[] =
            "OPENSHIM_DISABLE_NATIVE_CHUNK_SHADOW_FIX";
        constexpr char kLegacyDisableChunkShadowFixSwitch[] =
            "BZR_DISABLE_NATIVE_CHUNK_SHADOW_FIX";
        constexpr char kDisableDx11SkinSourceShadowFixSwitch[] =
            "OPENSHIM_DISABLE_DX11_SKIN_SOURCE_SHADOW_FIX";
        constexpr char kLegacyDisableDx11SkinSourceShadowFixSwitch[] =
            "BZR_DISABLE_DX11_SKIN_SOURCE_SHADOW_FIX";
        constexpr char kIniSection[] = "Diagnostics";
        constexpr char kIniKey[] = "ProfileOgreAnimation";
        constexpr int kDefaultProfilerEnabled = 1;
        constexpr DWORD kPollSleepMs = 25;
        constexpr ULONGLONG kReportIntervalMs = 1000;
        constexpr size_t kBloomWords = 1024; // 65536 bits; low collision rate for BZR-scale scenes.
        constexpr size_t kMaxVtableEntriesToProbe = 128;
        constexpr size_t kMaxSaneVertexCount = 16u * 1024u * 1024u;
        constexpr size_t kLatencyBucketCount = 7;
        constexpr size_t kVertexBucketCount = 8;
        constexpr size_t kMatrixBucketCount = 5;
        constexpr size_t kFrameTimeBucketCount =
            OgreProfilerAlgorithms::kFrameTimeBucketCount;
        constexpr uint64_t kFrameTimeBucketUs =
            OgreProfilerAlgorithms::kFrameTimeBucketUs;
        constexpr size_t kEntityTableSize = 4096;
        constexpr size_t kSourceTableSize = 2048;
        constexpr size_t kProfileProbeCount = 8;
        constexpr size_t kTopContributorCount = 5;
        constexpr size_t kEntityMetadataLength = 96;
        constexpr size_t kDynamicGeometryTableSize = 16;
        constexpr size_t kDynamicMaterialTableSize = 128;
        constexpr size_t kCameraTableSize = 16;
        // Aggregate render work by semantic identity rather than transient
        // Renderable address. Weapon effects churn object instances rapidly;
        // a fixed table keyed by type/pass/camera/mesh stays bounded and keeps
        // long firing captures representative instead of filling with dead IDs.
        constexpr size_t kRenderContributorTableSize = 2048;
        constexpr size_t kRenderContributorProbeCount = 16;
        // A four-team battle produces well over 48 distinct contributor groups
        // (three PSSM cascades x every mesh/material, plus effect materials and
        // post-process quads). Truncating the log at 48 silently drops the tail
        // that attribution has to account for, so the cap covers the observed
        // group count with headroom.
        constexpr size_t kRenderContributorTopCount = 160;
        constexpr unsigned kMaxExportThunkDepth = 2;
        constexpr size_t kMaxSuspendedThreads = 128;
        constexpr size_t kEntryDetourMaxPatchLen = 16;

        static_assert((kEntityTableSize & (kEntityTableSize - 1)) == 0,
                      "entity table must remain power-of-two");
        static_assert((kSourceTableSize & (kSourceTableSize - 1)) == 0,
                      "source table must remain power-of-two");
        static_assert(
            (kRenderContributorTableSize &
             (kRenderContributorTableSize - 1)) == 0,
            "render contributor table must remain power-of-two");

        using FnEntityUpdateAnimation = void(__thiscall*)(void*);
        using FnEntityUpdateRenderQueue = void(__thiscall*)(void*, void*);
        using FnSceneManagerRenderScene =
            void(__thiscall*)(void*, void*, void*, bool);
        using FnSceneManagerRenderSingleObject = void(__thiscall*)(
            void*, void*, const void*, bool, bool, const void*);
        using FnOgreStringQuery = const std::string&(__thiscall*)(const void*);
        using FnEntityGetMesh = const void*(__thiscall*)(const void*);
        using FnSubEntityGetParent = const void*(__thiscall*)(const void*);
        using FnPassGetParent = const void*(__thiscall*)(const void*);
        using FnTechniqueGetParent = const void*(__thiscall*)(const void*);
        using FnPassGetIndex = unsigned short(__thiscall*)(const void*);
        using FnTechniqueGetLodIndex = unsigned short(__thiscall*)(const void*);
        using FnMovableGetCastShadows = bool(__thiscall*)(const void*);
        using FnMovableSetCastShadows = void(__thiscall*)(void*, bool);
        using FnVertexElementGetSource =
            unsigned short(__thiscall*)(const Ogre::VertexElement*);
        using FnVertexElementGetType =
            Ogre::VertexElementType(__thiscall*)(const Ogre::VertexElement*);
        using FnVertexElementGetTypeCount =
            unsigned short(__cdecl*)(Ogre::VertexElementType);
        using FnHardwareVertexBufferGetVertexSize =
            size_t(__thiscall*)(const void*);
        using FnHardwareBufferGetSizeInBytes = size_t(__thiscall*)(const void*);
        using FnHardwareBufferGetUsage =
            Ogre::HardwareBuffer::Usage(__thiscall*)(const void*);
        using FnHardwareBufferBoolQuery = bool(__thiscall*)(const void*);
        using FnHardwareBufferManagerGetSingletonPtr = void*(__cdecl*)();
        using FnHardwareBufferManagerCreateVertexBuffer = void*(__thiscall*)(
            void*, void*, size_t, size_t, Ogre::HardwareBuffer::Usage, bool);
        using FnHardwareBufferLock = void*(__thiscall*)(
            void*, Ogre::HardwareBuffer::LockOptions,
            Ogre::HardwareBuffer::UploadOptions);
        using FnHardwareBufferUnlock = void(__thiscall*)(void*);
        using FnVertexBufferBindingSetBinding =
            void(__thiscall*)(void*, unsigned short, const void*);
        using FnHardwareVertexBufferSharedPtrDestructor =
            void(__thiscall*)(void*);
        using FnD3D11RenderSystemRender = void(__thiscall*)(void*, const void*);
        using FnD3D9RenderSystemRender = void(__thiscall*)(void*, const void*);
        using FnD3D9GetActiveDevice = IDirect3DDevice9*(__cdecl*)();
        using FnD3D11RenderSystemGetDevice = void*(__thiscall*)(void*);
        using FnOgreD3D11DeviceGetImmediateContext =
            ID3D11DeviceContext*(__thiscall*)(void*);
        using FnSoftwareVertexBlend = void(__cdecl*)(
            const Ogre::VertexData*,
            const Ogre::VertexData*,
            const void* const*,
            size_t,
            bool);

        using FnD3D11CreateDevice = HRESULT(WINAPI*)(
            IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
            const D3D_FEATURE_LEVEL*, UINT, UINT,
            ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);
        using FnD3D11CreateDeviceAndSwapChain = HRESULT(WINAPI*)(
            IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
            const D3D_FEATURE_LEVEL*, UINT, UINT,
            const DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**,
            ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);
        using FnFactoryCreateSwapChain = HRESULT(STDMETHODCALLTYPE*)(
            IDXGIFactory*, IUnknown*, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**);
        using FnDeviceCreateDeferredContext = HRESULT(STDMETHODCALLTYPE*)(
            ID3D11Device*, UINT, ID3D11DeviceContext**);
        using FnContextDrawIndexed = void(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, UINT, UINT, INT);
        using FnContextDraw = void(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, UINT, UINT);
        using FnContextMap = HRESULT(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, ID3D11Resource*, UINT, D3D11_MAP, UINT,
            D3D11_MAPPED_SUBRESOURCE*);
        using FnContextUnmap = void(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, ID3D11Resource*, UINT);
        using FnContextUpdateSubresource = void(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, ID3D11Resource*, UINT, const D3D11_BOX*,
            const void*, UINT, UINT);
        using FnContextDrawIndexedInstanced = void(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, UINT, UINT, UINT, INT, UINT);
        using FnContextDrawInstanced = void(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, UINT, UINT, UINT, UINT);
        using FnContextDrawIndexedInstancedIndirect = void(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, ID3D11Buffer*, UINT);
        using FnContextDrawInstancedIndirect = void(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, ID3D11Buffer*, UINT);
        using FnSwapChainPresent = HRESULT(STDMETHODCALLTYPE*)(
            IDXGISwapChain*, UINT, UINT);
        using FnD3D9SwapChainPresent = HRESULT(STDMETHODCALLTYPE*)(
            IDirect3DSwapChain9*, const RECT*, const RECT*, HWND,
            const RGNDATA*, DWORD);
        using FnD3D9DrawPrimitive = HRESULT(STDMETHODCALLTYPE*)(
            IDirect3DDevice9*, D3DPRIMITIVETYPE, UINT, UINT);
        using FnD3D9DrawIndexedPrimitive = HRESULT(STDMETHODCALLTYPE*)(
            IDirect3DDevice9*, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);
        using FnD3D9SetRenderState = HRESULT(STDMETHODCALLTYPE*)(
            IDirect3DDevice9*, D3DRENDERSTATETYPE, DWORD);
        using FnD3D9SetTexture = HRESULT(STDMETHODCALLTYPE*)(
            IDirect3DDevice9*, DWORD, IDirect3DBaseTexture9*);
        using FnD3D9SetTextureStageState = HRESULT(STDMETHODCALLTYPE*)(
            IDirect3DDevice9*, DWORD, D3DTEXTURESTAGESTATETYPE, DWORD);
        using FnD3D9SetSamplerState = HRESULT(STDMETHODCALLTYPE*)(
            IDirect3DDevice9*, DWORD, D3DSAMPLERSTATETYPE, DWORD);
        using FnD3D9SetVertexShader = HRESULT(STDMETHODCALLTYPE*)(
            IDirect3DDevice9*, IDirect3DVertexShader9*);
        using FnD3D9SetPixelShader = HRESULT(STDMETHODCALLTYPE*)(
            IDirect3DDevice9*, IDirect3DPixelShader9*);

        using OgreProfilerAlgorithms::ProfilerState;

        struct EntryDetour32
        {
            uint8_t* target = nullptr;
            void* hook = nullptr;
            void* trampoline = nullptr;
            size_t patchLen = 0;
            std::array<uint8_t, kEntryDetourMaxPatchLen> original{};
        };

        struct PointerPatch
        {
            void** slot = nullptr;
            void* original = nullptr;
        };

        struct ExportMatch
        {
            std::string name;
            void* address = nullptr;
        };

        struct EntityProfileSlot
        {
            std::atomic<uintptr_t> key{ 0 };
            std::atomic<uint32_t> metadataState{ 0 }; // 0=empty, 1=capturing, 2=ready
            std::atomic<uint64_t> lastAnimationFrame{ 0 };
            std::atomic<uint64_t> lastSkinFrame{ 0 };
            std::atomic<uint64_t> lastRenderQueueFrame{ 0 };
            std::atomic<uint64_t> animationCalls{ 0 };
            std::atomic<uint64_t> animationTicks{ 0 };
            std::atomic<uint64_t> skinCalls{ 0 };
            std::atomic<uint64_t> skinVertices{ 0 };
            std::atomic<uint64_t> skinTicks{ 0 };
            std::atomic<uint64_t> renderQueueCalls{ 0 };
            std::array<char, kEntityMetadataLength> entityName{};
            std::array<char, kEntityMetadataLength> meshName{};
            bool castShadows = false;
        };

        struct SourceProfileSlot
        {
            std::atomic<uintptr_t> key{ 0 };
            std::atomic<uint32_t> metadataState{ 0 };
            std::atomic<uint64_t> calls{ 0 };
            std::atomic<uint64_t> vertices{ 0 };
            std::atomic<uint64_t> ticks{ 0 };
            std::atomic<uint64_t> sourceVertices{ 0 };
            uint32_t positionStride = 0;
            uint32_t normalStride = 0;
            uint32_t weightStride = 0;
            uint32_t indexStride = 0;
            uint32_t weightsPerVertex = 0;
            bool positionShadowed = false;
            bool positionSystemMemory = false;
            bool weightShadowed = false;
        };

        struct DynamicGeometryProfileSlot
        {
            std::atomic<uintptr_t> key{ 0 };
            std::atomic<uint64_t> prepareCalls{ 0 };
            std::atomic<uint64_t> rebuilds{ 0 };
            std::atomic<uint64_t> prepareTicks{ 0 };
            std::atomic<uint64_t> queueCalls{ 0 };
            std::atomic<uint64_t> batches{ 0 };
            std::atomic<uint64_t> batchMax{ 0 };
        };

        struct DynamicMaterialProfileSlot
        {
            std::atomic<uintptr_t> key{ 0 };
            std::atomic<uint64_t> batches{ 0 };
            std::atomic<uint64_t> blendedBatches{ 0 };
            std::atomic<uint32_t> metadataState{ 0 };
            std::array<char, kEntityMetadataLength> materialName{};
        };

        struct CameraProfileSlot
        {
            std::atomic<uintptr_t> key{ 0 };
            std::atomic<uint32_t> metadataState{ 0 };
            std::atomic<uint64_t> renderCalls{ 0 };
            std::atomic<uint64_t> nestedRenderCalls{ 0 };
            std::array<char, kEntityMetadataLength> cameraName{};
        };

        struct RenderContributorSlot
        {
            std::atomic<uintptr_t> key{ 0 };
            std::atomic<uint32_t> metadataState{ 0 };
            uintptr_t renderableVtable = 0;
            uintptr_t pass = 0;
            uintptr_t camera = 0;
            uintptr_t mesh = 0;
            std::atomic<uint64_t> calls{ 0 };
            std::atomic<uint64_t> mainCalls{ 0 };
            std::atomic<uint64_t> shadowCalls{ 0 };
            std::atomic<uint64_t> ticks{ 0 };
            std::atomic<uint64_t> ogreSubmissions{ 0 };
            std::atomic<uint64_t> operationVertices{ 0 };
            std::atomic<uint64_t> operationIndices{ 0 };
            std::atomic<uint64_t> draws{ 0 };
            std::atomic<uint64_t> indexedDraws{ 0 };
            std::atomic<uint64_t> drawnVertices{ 0 };
            std::atomic<uint64_t> drawnIndices{ 0 };
            // Submission-to-draw outcome. An Ogre submission is not an API draw:
            // D3D11RenderSystem::_render guards its draw with `if (primCount)`
            // and returns early on an empty vertex buffer, while D3D9 issues the
            // draw unconditionally. These three counters say which submissions
            // produced no API draw and why, so the backend difference can be
            // measured instead of assumed.
            std::atomic<uint64_t> noDrawSubmissions{ 0 };
            std::atomic<uint64_t> emptyVertexSubmissions{ 0 };
            std::atomic<uint64_t> zeroPrimSubmissions{ 0 };
            // Submissions entered while the draw observer was not installed on
            // the device-context vtable. Draws issued during such a submission
            // are invisible to the profiler, so this bounds instrumentation loss.
            std::atomic<uint64_t> unobservedSubmissions{ 0 };
            std::atomic<uint64_t> renderStates{ 0 };
            std::atomic<uint64_t> blendStates{ 0 };
            std::atomic<uint64_t> textureSets{ 0 };
            std::atomic<uint64_t> textureStageSets{ 0 };
            std::atomic<uint64_t> samplerSets{ 0 };
            std::atomic<uint64_t> vertexShaderSets{ 0 };
            std::atomic<uint64_t> pixelShaderSets{ 0 };
            std::array<char, kEntityMetadataLength> typeName{};
            std::array<char, kEntityMetadataLength> ownerName{};
            std::array<char, kEntityMetadataLength> meshName{};
            std::array<char, kEntityMetadataLength> materialName{};
            std::array<char, kEntityMetadataLength> techniqueName{};
            std::array<char, kEntityMetadataLength> schemeName{};
            std::array<char, kEntityMetadataLength> passName{};
            std::array<char, kEntityMetadataLength> cameraName{};
            uint32_t passIndex = 0;
            uint32_t lodIndex = 0;
        };

        struct RenderContributorSample
        {
            uintptr_t key = 0;
            uint64_t calls = 0;
            uint64_t mainCalls = 0;
            uint64_t shadowCalls = 0;
            uint64_t ticks = 0;
            uint64_t ogreSubmissions = 0;
            uint64_t operationVertices = 0;
            uint64_t operationIndices = 0;
            uint64_t draws = 0;
            uint64_t indexedDraws = 0;
            uint64_t drawnVertices = 0;
            uint64_t drawnIndices = 0;
            uint64_t noDrawSubmissions = 0;
            uint64_t emptyVertexSubmissions = 0;
            uint64_t zeroPrimSubmissions = 0;
            uint64_t unobservedSubmissions = 0;
            uint64_t renderStates = 0;
            uint64_t blendStates = 0;
            uint64_t textureSets = 0;
            uint64_t textureStageSets = 0;
            uint64_t samplerSets = 0;
            uint64_t vertexShaderSets = 0;
            uint64_t pixelShaderSets = 0;
            std::array<char, kEntityMetadataLength> typeName{};
            std::array<char, kEntityMetadataLength> ownerName{};
            std::array<char, kEntityMetadataLength> meshName{};
            std::array<char, kEntityMetadataLength> materialName{};
            std::array<char, kEntityMetadataLength> techniqueName{};
            std::array<char, kEntityMetadataLength> schemeName{};
            std::array<char, kEntityMetadataLength> passName{};
            std::array<char, kEntityMetadataLength> cameraName{};
            uint32_t passIndex = 0;
            uint32_t lodIndex = 0;
            bool metadataReady = false;
        };

        struct EntityTopSample
        {
            uintptr_t key = 0;
            uint64_t animationCalls = 0;
            uint64_t animationTicks = 0;
            uint64_t skinCalls = 0;
            uint64_t skinVertices = 0;
            uint64_t skinTicks = 0;
            uint64_t renderQueueCalls = 0;
            std::array<char, kEntityMetadataLength> entityName{};
            std::array<char, kEntityMetadataLength> meshName{};
            bool castShadows = false;
            bool metadataReady = false;
        };

        struct SourceTopSample
        {
            uintptr_t key = 0;
            uint64_t calls = 0;
            uint64_t vertices = 0;
            uint64_t ticks = 0;
            uint64_t sourceVertices = 0;
            uint32_t positionStride = 0;
            uint32_t normalStride = 0;
            uint32_t weightStride = 0;
            uint32_t indexStride = 0;
            uint32_t weightsPerVertex = 0;
            bool positionShadowed = false;
            bool positionSystemMemory = false;
            bool weightShadowed = false;
            bool metadataReady = false;
        };

        struct DynamicGeometryTopSample
        {
            uintptr_t key = 0;
            uint64_t prepareCalls = 0;
            uint64_t rebuilds = 0;
            uint64_t prepareTicks = 0;
            uint64_t queueCalls = 0;
            uint64_t batches = 0;
            uint64_t batchMax = 0;
        };

        struct DynamicMaterialTopSample
        {
            uintptr_t key = 0;
            uint64_t batches = 0;
            uint64_t blendedBatches = 0;
            std::array<char, kEntityMetadataLength> materialName{};
            bool metadataReady = false;
        };

        std::atomic<bool> g_Enabled{ false };
        std::atomic<bool> g_ShutdownRequested{ false };
        std::atomic<bool> g_OgreHooksInstalled{ false };
        std::atomic<bool> g_RenderQueueHookInstalled{ false };
        std::atomic<bool> g_RenderSingleObjectHookInstalled{ false };
        std::atomic<bool> g_ChunkShadowHookInstalled{ false };
        std::atomic<bool> g_ChunkShadowPolicyEnabled{ false };
        std::atomic<bool> g_Dx11SkinSourceShadowPolicyEnabled{ false };
        std::atomic<bool> g_Dx11SkinSourceShadowHookInstalled{ false };
        std::atomic<bool> g_Dx11ImportsPatched{ false };
        std::atomic<bool> g_Dx11ContextObserved{ false };
        std::atomic<bool> g_D3D9DeviceObserved{ false };
        std::atomic<bool> g_D3D11RenderSystemObserverInstalled{ false };
        std::atomic<bool> g_D3D9RenderSystemObserverInstalled{ false };
        std::atomic<bool> g_PresentObserved{ false };
        std::atomic<bool> g_RenderSystemObserverInstalled{ false };
        std::atomic<uintptr_t> g_RenderContextIdentity{ 0 };
        std::atomic<bool> g_OgreInstallAttempted{ false };
        std::atomic<ProfilerState> g_ProfilerState{ ProfilerState::Disabled };
        uintptr_t g_WorkerThread = 0;

        std::mutex g_PatchMutex;
        std::vector<PointerPatch> g_PointerPatches;
        bool g_EntryInstallRetryRequested = false;

        EntryDetour32 g_EntityUpdateAnimationDetour{};
        EntryDetour32 g_EntityUpdateAnimationCoreDetour{};
        EntryDetour32 g_SoftwareVertexBlendDetour{};
        EntryDetour32 g_SceneManagerRenderSceneDetour{};
        EntryDetour32 g_SceneManagerRenderSingleObjectDetour{};
        EntryDetour32 g_D3D11RenderSystemRenderDetour{};
        EntryDetour32 g_D3D9RenderSystemRenderDetour{};

        FnEntityUpdateAnimation g_RealEntityUpdateAnimation = nullptr;
        FnEntityUpdateAnimation g_RealEntityUpdateAnimationCore = nullptr;
        FnEntityUpdateRenderQueue g_RealEntityUpdateRenderQueue = nullptr;
        FnSceneManagerRenderScene g_RealSceneManagerRenderScene = nullptr;
        FnSceneManagerRenderSingleObject g_RealSceneManagerRenderSingleObject = nullptr;
        FnOgreStringQuery g_OgreGetEntityName = nullptr;
        FnEntityGetMesh g_OgreEntityGetMesh = nullptr;
        FnSubEntityGetParent g_OgreSubEntityGetParent = nullptr;
        FnPassGetParent g_OgrePassGetParent = nullptr;
        FnTechniqueGetParent g_OgreTechniqueGetParent = nullptr;
        FnPassGetIndex g_OgrePassGetIndex = nullptr;
        FnOgreStringQuery g_OgreTechniqueGetName = nullptr;
        FnOgreStringQuery g_OgreTechniqueGetSchemeName = nullptr;
        FnTechniqueGetLodIndex g_OgreTechniqueGetLodIndex = nullptr;
        FnOgreStringQuery g_OgrePassGetName = nullptr;
        void* g_OgreSubEntityVtable = nullptr;
        FnOgreStringQuery g_OgreGetResourceName = nullptr;
        FnMovableGetCastShadows g_OgreGetCastShadows = nullptr;
        FnMovableSetCastShadows g_OgreSetCastShadows = nullptr;
        FnVertexElementGetSource g_OgreVertexElementGetSource = nullptr;
        FnVertexElementGetType g_OgreVertexElementGetType = nullptr;
        FnVertexElementGetTypeCount g_OgreVertexElementGetTypeCount = nullptr;
        FnHardwareVertexBufferGetVertexSize g_OgreVertexBufferGetVertexSize = nullptr;
        FnHardwareBufferGetSizeInBytes g_OgreHardwareBufferGetSizeInBytes = nullptr;
        FnHardwareBufferGetUsage g_OgreHardwareBufferGetUsage = nullptr;
        FnHardwareBufferBoolQuery g_OgreHardwareBufferHasShadow = nullptr;
        FnHardwareBufferBoolQuery g_OgreHardwareBufferIsSystemMemory = nullptr;
        FnHardwareBufferManagerGetSingletonPtr
            g_OgreHardwareBufferManagerGetSingletonPtr = nullptr;
        FnHardwareBufferManagerCreateVertexBuffer
            g_OgreHardwareBufferManagerCreateVertexBuffer = nullptr;
        FnHardwareBufferLock g_OgreHardwareBufferLock = nullptr;
        FnHardwareBufferUnlock g_OgreHardwareBufferUnlock = nullptr;
        FnVertexBufferBindingSetBinding g_OgreVertexBufferBindingSetBinding = nullptr;
        FnHardwareVertexBufferSharedPtrDestructor
            g_OgreHardwareVertexBufferSharedPtrDestructor = nullptr;
        FnSoftwareVertexBlend g_RealSoftwareVertexBlend = nullptr;
        FnD3D11RenderSystemRender g_RealD3D11RenderSystemRender = nullptr;
        FnD3D9RenderSystemRender g_RealD3D9RenderSystemRender = nullptr;
        FnD3D9GetActiveDevice g_D3D9GetActiveDevice = nullptr;
        FnD3D11RenderSystemGetDevice g_D3D11RenderSystemGetDevice = nullptr;
        FnOgreD3D11DeviceGetImmediateContext g_OgreD3D11DeviceGetImmediateContext = nullptr;

        FnD3D11CreateDevice g_RealD3D11CreateDevice = nullptr;
        FnD3D11CreateDeviceAndSwapChain g_RealD3D11CreateDeviceAndSwapChain = nullptr;
        FnFactoryCreateSwapChain g_RealFactoryCreateSwapChain = nullptr;
        FnDeviceCreateDeferredContext g_RealCreateDeferredContext = nullptr;
        FnContextDrawIndexed g_RealDrawIndexed = nullptr;
        FnContextDraw g_RealDraw = nullptr;
        FnContextMap g_RealMap = nullptr;
        FnContextUnmap g_RealUnmap = nullptr;
        FnContextUpdateSubresource g_RealUpdateSubresource = nullptr;
        FnContextDrawIndexedInstanced g_RealDrawIndexedInstanced = nullptr;
        FnContextDrawInstanced g_RealDrawInstanced = nullptr;
        FnContextDrawIndexedInstancedIndirect g_RealDrawIndexedInstancedIndirect = nullptr;
        FnContextDrawInstancedIndirect g_RealDrawInstancedIndirect = nullptr;
        FnSwapChainPresent g_RealPresent = nullptr;
        FnD3D9SwapChainPresent g_RealD3D9SwapChainPresent = nullptr;
        FnD3D9DrawPrimitive g_RealD3D9DrawPrimitive = nullptr;
        FnD3D9DrawIndexedPrimitive g_RealD3D9DrawIndexedPrimitive = nullptr;
        FnD3D9SetRenderState g_RealD3D9SetRenderState = nullptr;
        FnD3D9SetTexture g_RealD3D9SetTexture = nullptr;
        FnD3D9SetTextureStageState g_RealD3D9SetTextureStageState = nullptr;
        FnD3D9SetSamplerState g_RealD3D9SetSamplerState = nullptr;
        FnD3D9SetVertexShader g_RealD3D9SetVertexShader = nullptr;
        FnD3D9SetPixelShader g_RealD3D9SetPixelShader = nullptr;

        std::atomic<uint64_t> g_AnimationCalls{ 0 };
        std::atomic<uint64_t> g_AnimationTicks{ 0 };
        std::atomic<uint64_t> g_RenderDrivenAnimationCalls{ 0 };
        std::atomic<uint64_t> g_RenderDrivenAnimationTicks{ 0 };
        std::atomic<uint64_t> g_ExternalAnimationCalls{ 0 };
        std::atomic<uint64_t> g_ExternalAnimationTicks{ 0 };
        std::atomic<uint64_t> g_AnimationWithBlendCalls{ 0 };
        std::atomic<uint64_t> g_AnimationWithoutBlendCalls{ 0 };
        std::atomic<uint64_t> g_BlendCallsInAnimations{ 0 };
        std::atomic<uint64_t> g_BlendVerticesInAnimations{ 0 };
        std::atomic<uint64_t> g_DuplicateAnimationSameFrame{ 0 };
        std::atomic<uint64_t> g_DuplicateSkinSameFrame{ 0 };
        std::atomic<uint64_t> g_SoftwareBlendCalls{ 0 };
        std::atomic<uint64_t> g_SoftwareBlendVertices{ 0 };
        std::atomic<uint64_t> g_SoftwareBlendTicks{ 0 };
        std::atomic<uint64_t> g_SoftwareBlendTicksInAnimation{ 0 };
        std::atomic<uint64_t> g_OrphanBlendCalls{ 0 };
        std::atomic<uint64_t> g_BlendMatrixTotal{ 0 };
        std::atomic<uint64_t> g_BlendMatrixMax{ 0 };
        std::atomic<uint64_t> g_BlendNormalsCalls{ 0 };
        std::atomic<uint64_t> g_AnimationMaxTicks{ 0 };
        std::atomic<uint64_t> g_SoftwareBlendMaxTicks{ 0 };
        std::atomic<uint64_t> g_RenderQueueCalls{ 0 };
        std::atomic<uint64_t> g_DuplicateRenderQueueSameFrame{ 0 };
        std::atomic<uint64_t> g_SceneRenderCalls{ 0 };
        std::atomic<uint64_t> g_ShadowSceneRenderCalls{ 0 };
        std::atomic<uint64_t> g_MainRenderQueueCalls{ 0 };
        std::atomic<uint64_t> g_ShadowRenderQueueCalls{ 0 };
        std::atomic<uint64_t> g_MainAnimationCalls{ 0 };
        std::atomic<uint64_t> g_ShadowAnimationCalls{ 0 };
        std::atomic<uint64_t> g_MainSoftwareBlendCalls{ 0 };
        std::atomic<uint64_t> g_ShadowSoftwareBlendCalls{ 0 };
        std::atomic<uint64_t> g_RenderSystemSubmissions{ 0 };
        std::atomic<uint64_t> g_RenderSystemSubmissionTicks{ 0 };
        std::atomic<uint64_t> g_RenderSystemSubmissionMaxTicks{ 0 };
        std::atomic<uint64_t> g_RenderContributorDrops{ 0 };
        std::atomic<uint64_t> g_ContextVtableRefreshes{ 0 };
        std::atomic<uint64_t> g_NoDrawSubmissions{ 0 };
        std::atomic<uint64_t> g_EmptyVertexSubmissions{ 0 };
        std::atomic<uint64_t> g_ZeroPrimSubmissions{ 0 };
        std::atomic<uint64_t> g_MultiDrawSubmissions{ 0 };
        std::atomic<uint64_t> g_UnobservedSubmissions{ 0 };
        std::atomic<unsigned> g_IsolationMask{ 0 };
        std::atomic<uint64_t> g_IsolatedRenderables{ 0 };
        std::atomic<uint64_t> g_DrawCalls{ 0 };
        std::atomic<uint64_t> g_DrawVertices{ 0 };
        std::atomic<uint64_t> g_DrawIndexedCalls{ 0 };
        std::atomic<uint64_t> g_DrawIndexedIndices{ 0 };
        std::atomic<uint64_t> g_DrawIndexedInstancedCalls{ 0 };
        std::atomic<uint64_t> g_DrawIndexedInstancedIndices{ 0 };
        std::atomic<uint64_t> g_DrawInstancedCalls{ 0 };
        std::atomic<uint64_t> g_DrawInstancedVertices{ 0 };
        std::atomic<uint64_t> g_DrawIndexedInstancedIndirectCalls{ 0 };
        std::atomic<uint64_t> g_DrawInstancedIndirectCalls{ 0 };
        std::atomic<uint64_t> g_MapCalls{ 0 };
        std::atomic<uint64_t> g_MapDuringAnimationCalls{ 0 };
        std::atomic<uint64_t> g_MapDuringBlendCalls{ 0 };
        std::atomic<uint64_t> g_MapTicks{ 0 };
        std::atomic<uint64_t> g_MapMaxTicks{ 0 };
        std::atomic<uint64_t> g_MapWriteCalls{ 0 };
        std::atomic<uint64_t> g_MapWriteDiscardCalls{ 0 };
        std::atomic<uint64_t> g_MapWriteNoOverwriteCalls{ 0 };
        std::atomic<uint64_t> g_MapOtherCalls{ 0 };
        std::atomic<uint64_t> g_UnmapCalls{ 0 };
        std::atomic<uint64_t> g_UnmapDuringAnimationCalls{ 0 };
        std::atomic<uint64_t> g_UpdateSubresourceCalls{ 0 };
        std::atomic<uint64_t> g_UpdateSubresourceDuringAnimationCalls{ 0 };
        std::atomic<uint64_t> g_UpdateSubresourceDuringBlendCalls{ 0 };
        std::atomic<uint64_t> g_UpdateSubresourceTicks{ 0 };
        std::atomic<uint64_t> g_UpdateSubresourceMaxTicks{ 0 };
        std::atomic<uint64_t> g_Presents{ 0 };
        std::atomic<uint64_t> g_D3D9RenderStateCalls{ 0 };
        std::atomic<uint64_t> g_D3D9BlendStateCalls{ 0 };
        std::atomic<uint64_t> g_D3D9TextureCalls{ 0 };
        std::atomic<uint64_t> g_D3D9TextureStageStateCalls{ 0 };
        std::atomic<uint64_t> g_D3D9SamplerStateCalls{ 0 };
        std::atomic<uint64_t> g_D3D9VertexShaderCalls{ 0 };
        std::atomic<uint64_t> g_D3D9PixelShaderCalls{ 0 };
        std::atomic<uint64_t> g_FrameEpoch{ 1 };
        std::atomic<uint64_t> g_LastPresentQpc{ 0 };
        std::atomic<uint64_t> g_FrameTimeSamples{ 0 };
        std::atomic<uint64_t> g_FrameTimeTicks{ 0 };
        std::atomic<uint64_t> g_FrameTimeMaxTicks{ 0 };
        std::atomic<uint64_t> g_FrameOver1667{ 0 };
        std::atomic<uint64_t> g_FrameOver2500{ 0 };
        std::atomic<uint64_t> g_FrameOver3333{ 0 };
        std::atomic<uint64_t> g_NativeChunkSimCalls{ 0 };
        std::atomic<uint64_t> g_NativeChunkSimTicks{ 0 };
        std::atomic<uint64_t> g_NativeChunkActiveTotal{ 0 };
        std::atomic<uint64_t> g_NativeChunkActiveMax{ 0 };
        std::atomic<uint64_t> g_DynamicGeometryPrepareCalls{ 0 };
        std::atomic<uint64_t> g_DynamicGeometryRebuilds{ 0 };
        std::atomic<uint64_t> g_DynamicGeometryPrepareTicks{ 0 };
        std::atomic<uint64_t> g_DynamicGeometryPrepareMaxTicks{ 0 };
        std::atomic<uint64_t> g_DynamicGeometryQueueCalls{ 0 };
        std::atomic<uint64_t> g_DynamicGeometryBatchTotal{ 0 };
        std::atomic<uint64_t> g_DynamicGeometryBatchMax{ 0 };
        std::atomic<uint64_t> g_DynamicGeometryMergeableBatchTotal{ 0 };
        std::atomic<uint64_t> g_DynamicGeometryBlendedBatchTotal{ 0 };
        std::atomic<uint64_t> g_DynamicGeometryDistinctMaterialTotal{ 0 };
        std::atomic<uint64_t> g_DynamicGeometryVertexTotal{ 0 };
        std::atomic<uint64_t> g_DynamicGeometryIndexTotal{ 0 };
        std::atomic<uint64_t> g_ChunkShadowQueries{ 0 };
        std::atomic<uint64_t> g_ChunkShadowSuppressions{ 0 };
        std::atomic<uint64_t> g_Dx11SkinSourceShadowQueries{ 0 };
        std::atomic<uint64_t> g_Dx11SkinSourceShadowRepairs{ 0 };
        std::atomic<uint64_t> g_Dx11SkinSourceShadowRepairBytes{ 0 };
        std::atomic<uint64_t> g_Dx11SkinSourceShadowFailures{ 0 };
        std::atomic<uint32_t> g_Dx11SkinSourceShadowFailureStage{ 0 };

        std::array<std::atomic<uint64_t>, kBloomWords> g_AnimationEntityBloom{};
        std::array<std::atomic<uint64_t>, kBloomWords> g_SkinnedEntityBloom{};
        std::array<std::atomic<uint64_t>, kBloomWords> g_RenderEntityBloom{};
        std::array<std::atomic<uint64_t>, kLatencyBucketCount> g_AnimationLatencyBuckets{};
        std::array<std::atomic<uint64_t>, kLatencyBucketCount> g_SoftwareBlendLatencyBuckets{};
        std::array<std::atomic<uint64_t>, kVertexBucketCount> g_VertexBucketCalls{};
        std::array<std::atomic<uint64_t>, kVertexBucketCount> g_VertexBucketVertices{};
        std::array<std::atomic<uint64_t>, kVertexBucketCount> g_VertexBucketTicks{};
        std::array<std::atomic<uint64_t>, kMatrixBucketCount> g_MatrixBucketCalls{};
        std::array<std::atomic<uint64_t>, kFrameTimeBucketCount> g_FrameTimeBuckets{};
        std::array<EntityProfileSlot, kEntityTableSize> g_EntityProfileSlots{};
        std::array<SourceProfileSlot, kSourceTableSize> g_SourceProfileSlots{};
        std::array<DynamicGeometryProfileSlot, kDynamicGeometryTableSize>
            g_DynamicGeometryProfileSlots{};
        std::array<DynamicMaterialProfileSlot, kDynamicMaterialTableSize>
            g_DynamicMaterialProfileSlots{};
        std::array<CameraProfileSlot, kCameraTableSize> g_CameraProfileSlots{};
        std::array<RenderContributorSlot, kRenderContributorTableSize>
            g_RenderContributorSlots{};

        LARGE_INTEGER g_QpcFrequency{};
        const char* g_ProfilerRequestSource = "build-default";
        thread_local void* t_CurrentAnimationEntity = nullptr;
        thread_local void* t_RenderQueueEntity = nullptr;
        thread_local void* t_CurrentSceneCamera = nullptr;
        thread_local RenderContributorSlot* t_CurrentRenderContributor = nullptr;
        thread_local uint32_t t_CurrentAnimationBlendCalls = 0;
        thread_local uint64_t t_CurrentAnimationBlendVertices = 0;
        thread_local unsigned t_SoftwareBlendDepth = 0;
        thread_local unsigned t_SceneRenderDepth = 0;
        thread_local uint64_t t_LastRenderContextCheckFrame = 0;
        // Monotonic per-thread count of API draw calls seen by the observers.
        // The render-system hooks snapshot it around the real _render call, so
        // the draw count belonging to one submission needs no shared state.
        thread_local uint64_t t_ThreadDrawCalls = 0;
        std::mutex g_Dx11SkinSourceShadowMutex;

        bool StringIsTruthy(const char* value)
        {
            return OgreProfilerAlgorithms::StringIsTruthy(value);
        }

        std::string GetOpenShimIniPath()
        {
            char path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return "openshim.ini";

