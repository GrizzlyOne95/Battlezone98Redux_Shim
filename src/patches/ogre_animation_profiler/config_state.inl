#include "ogre_animation_profiler.h"
#include "ogre_runtime.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <d3d11.h>
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
        constexpr size_t kFrameTimeBucketCount = 401; // 0.25 ms buckets through 100 ms + overflow.
        constexpr uint64_t kFrameTimeBucketUs = 250;
        constexpr size_t kEntityTableSize = 4096;
        constexpr size_t kSourceTableSize = 2048;
        constexpr size_t kProfileProbeCount = 8;
        constexpr size_t kTopContributorCount = 5;

        static_assert((kEntityTableSize & (kEntityTableSize - 1)) == 0,
                      "entity table must remain power-of-two");
        static_assert((kSourceTableSize & (kSourceTableSize - 1)) == 0,
                      "source table must remain power-of-two");

        using FnEntityUpdateAnimation = void(__thiscall*)(void*);
        using FnEntityUpdateRenderQueue = void(__thiscall*)(void*, void*);
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

        struct Rel32Patch
        {
            uint8_t* operand = nullptr;
            int32_t original = 0;
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
            std::atomic<uint64_t> lastAnimationFrame{ 0 };
            std::atomic<uint64_t> lastSkinFrame{ 0 };
            std::atomic<uint64_t> animationCalls{ 0 };
            std::atomic<uint64_t> animationTicks{ 0 };
            std::atomic<uint64_t> skinCalls{ 0 };
            std::atomic<uint64_t> skinVertices{ 0 };
            std::atomic<uint64_t> skinTicks{ 0 };
        };

        struct SourceProfileSlot
        {
            std::atomic<uintptr_t> key{ 0 };
            std::atomic<uint64_t> calls{ 0 };
            std::atomic<uint64_t> vertices{ 0 };
            std::atomic<uint64_t> ticks{ 0 };
            std::atomic<uint64_t> sourceVertices{ 0 };
        };

        struct EntityTopSample
        {
            uintptr_t key = 0;
            uint64_t animationCalls = 0;
            uint64_t animationTicks = 0;
            uint64_t skinCalls = 0;
            uint64_t skinVertices = 0;
            uint64_t skinTicks = 0;
        };

        struct SourceTopSample
        {
            uintptr_t key = 0;
            uint64_t calls = 0;
            uint64_t vertices = 0;
            uint64_t ticks = 0;
            uint64_t sourceVertices = 0;
        };

        std::atomic<bool> g_Enabled{ false };
        std::atomic<bool> g_ShutdownRequested{ false };
        std::atomic<bool> g_OgreHooksInstalled{ false };
        std::atomic<bool> g_RenderQueueHookInstalled{ false };
        std::atomic<bool> g_Dx11ImportsPatched{ false };
        std::atomic<bool> g_Dx11ContextObserved{ false };
        std::atomic<bool> g_PresentObserved{ false };
        uintptr_t g_WorkerThread = 0;

        std::mutex g_PatchMutex;
        std::vector<Rel32Patch> g_Rel32Patches;
        std::vector<PointerPatch> g_PointerPatches;

        FnEntityUpdateAnimation g_RealEntityUpdateAnimation = nullptr;
        FnEntityUpdateRenderQueue g_RealEntityUpdateRenderQueue = nullptr;
        FnSoftwareVertexBlend g_RealSoftwareVertexBlend = nullptr;

        FnD3D11CreateDevice g_RealD3D11CreateDevice = nullptr;
        FnD3D11CreateDeviceAndSwapChain g_RealD3D11CreateDeviceAndSwapChain = nullptr;
        FnFactoryCreateSwapChain g_RealFactoryCreateSwapChain = nullptr;
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
        std::atomic<uint64_t> g_FrameEpoch{ 1 };
        std::atomic<uint64_t> g_LastPresentQpc{ 0 };
        std::atomic<uint64_t> g_FrameTimeSamples{ 0 };
        std::atomic<uint64_t> g_FrameTimeTicks{ 0 };
        std::atomic<uint64_t> g_FrameTimeMaxTicks{ 0 };
        std::atomic<uint64_t> g_FrameOver1667{ 0 };
        std::atomic<uint64_t> g_FrameOver2500{ 0 };
        std::atomic<uint64_t> g_FrameOver3333{ 0 };

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

        LARGE_INTEGER g_QpcFrequency{};
        const char* g_ProfilerRequestSource = "build-default";
        thread_local void* t_CurrentAnimationEntity = nullptr;
        thread_local void* t_RenderQueueEntity = nullptr;
        thread_local uint32_t t_CurrentAnimationBlendCalls = 0;
        thread_local uint64_t t_CurrentAnimationBlendVertices = 0;
        thread_local unsigned t_SoftwareBlendDepth = 0;

        bool StringIsTruthy(const char* value)
        {
            if (!value || !*value)
                return false;

            std::string v(value);
            for (char& ch : v)
                ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            return v != "0" && v != "false" && v != "no" && v != "off";
        }

        std::string GetOpenShimIniPath()
        {
            char path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return "openshim.ini";

