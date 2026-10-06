// dynamic_geometry_hooks.cpp
// BZR Open Shim - DynamicGeometry hooks: dynamic alpha depth batching
// and the opt-in Ogre profiler observers (prepareForSubmit detour and
// the RenderQueue::addRenderable IAT counter), split out of bzr_hooks.cpp.
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
    using FnDynamicGeometrySetSquaredViewDepth =
        void(__thiscall*)(void* self, float squaredViewDepth);
    using FnRenderQueueAddRenderable =
        void(__thiscall*)(void* renderQueue, void* renderable, uint8_t queueGroup);

    FnDynamicGeometryPrepare g_BzrFn_DynamicGeometryPrepare = nullptr;

    static FnDynamicGeometrySetSquaredViewDepth g_BzrFn_DynamicGeometrySetSquaredViewDepth = nullptr;

    static FnRenderQueueAddRenderable g_BzrFn_RenderQueueAddRenderable = nullptr;

    namespace Hooks
    {
        InlineDetour32 g_DynamicGeometryPrepareDetour = {};

        static InlineDetour32 g_DynamicGeometrySetSquaredViewDepthDetour = {};

        static constexpr size_t kDynamicGeometryMaterialSampleCapacity = 64;

        static bool g_DynamicAlphaDepthBatchingEnabled = true;

        static uint32_t g_DynamicAlphaDepthBucketStride = 8;

        thread_local bool g_InDynamicGeometryQueueUpdate = false;

        thread_local uint32_t g_DynamicGeometryQueuedBatches = 0;

        thread_local uint32_t g_DynamicGeometryMergeableBatches = 0;

        thread_local uint32_t g_DynamicGeometryBlendedBatches = 0;

        thread_local uint64_t g_DynamicGeometryQueuedVertices = 0;

        thread_local uint64_t g_DynamicGeometryQueuedIndices = 0;

        thread_local uint32_t g_DynamicGeometryDistinctMaterials = 0;

        thread_local uintptr_t
            g_DynamicGeometryMaterialSamples[kDynamicGeometryMaterialSampleCapacity] = {};
        thread_local uint32_t
            g_DynamicGeometryMaterialBatchCounts[kDynamicGeometryMaterialSampleCapacity] = {};
        thread_local uint32_t
            g_DynamicGeometryMaterialBlendedCounts[kDynamicGeometryMaterialSampleCapacity] = {};


    }

    using namespace Hooks;

    // Dynamic alpha depth batching and the opt-in DynamicGeometry profiler
    // observers. GOG only: both detours check the exact prologue bytes.
    void InstallDynamicGeometryHooks()
    {
        if (!HookEngine::LiteralAddressesApply("Dynamic geometry hooks")) return;
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
    }

    // Runs the world queue update with the addRenderable batch counters armed
    // when the Ogre profiler is collecting; returns false (and runs nothing)
    // otherwise, so the caller makes the plain call.
    bool RunLegacyWorldQueueWithDynamicGeometryCounters(void* thisPtr, void* renderQueue)
    {
        if (!IsOgreAnimationProfilerCollecting() ||
            !g_BzrFn_RenderQueueAddRenderable)
            return false;
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
        return true;
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
}
