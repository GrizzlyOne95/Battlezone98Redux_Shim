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
#include "dynamic_geometry_batching.h"
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

        // --- Piece reuse, material cache and fast sort -------------------
        // See reverse_engineering/dynamic_geometry_begin_sort_20261021.md.
        using FnDgBeginByMaterial =
            void(__thiscall*)(void* dg, const void* material, int32_t op, float dist);
        using FnDgBeginByName =
            void(__thiscall*)(void* dg, const void* name, int32_t op, float dist);
        using FnDgGroup = uint8_t(__thiscall*)(void* dg);
        using FnDgSortLess = bool(__cdecl*)(const void* a, const void* b);

        static InlineDetour32 g_DgBeginByMaterialDetour = {};
        static InlineDetour32 g_DgBeginByNameDetour = {};
        static InlineDetour32 g_DgSortLessDetour = {};
        static InlineDetour32 g_DgOpaqueSortLessDetour = {};

        static FnDgBeginByMaterial g_DgBeginByMaterialOriginal = nullptr;
        static FnDgBeginByName g_DgBeginByNameOriginal = nullptr;
        static FnDgSortLess g_DgSortLessOriginal = nullptr;
        static FnDgSortLess g_DgOpaqueSortLessOriginal = nullptr;
        static FnDynamicGeometrySetSquaredViewDepth g_DgDepthKeyEntry = nullptr;

        static bool g_DgPieceReuseEnabled = false;
        static bool g_DgMaterialCacheEnabled = false;
        static bool g_DgFastSortEnabled = false;
        static bool g_DgBeginStats = false;
        static bool g_DgSortVerify = false;
        static bool g_DgBeginHooksActive = false;

        static DynamicGeometryBatching::RenderableLayout g_DgRenderableLayout = {};
        static DynamicGeometryBatching::NameCache g_DgNameCache = {};

        // Render-thread counters (begin, sort and prepare all run on it).
        struct DgBatchingCounters
        {
            uint64_t beginByMaterial = 0;
            uint64_t beginByName = 0;
            uint64_t newBatches = 0;
            uint64_t reused = 0;
            uint64_t cacheHits = 0;
            uint64_t cacheMisses = 0;
            uint64_t faults = 0;
            uint64_t sortCompares = 0;
            uint64_t sortMismatches = 0;
            uint64_t prepares = 0;
        };
        static DgBatchingCounters g_DgCounters = {};
        static DgBatchingCounters g_DgCountersAtLastLog = {};
        static ULONGLONG g_DgLastLogTick = 0;
    }

    using namespace Hooks;

    namespace
    {
        namespace Dgb = DynamicGeometryBatching;

        // Follows E9 rel32 and FF 25 [abs] thunks, then decodes the
        // "mov al, [ecx+disp8]; ret" body of an exported Renderable getter.
        uint32_t DecodeOgreByteGetter(const char* importName)
        {
            const uintptr_t slot = FindMainImageImportSlot("OgreMain.dll", importName);
            if (!slot)
                return 0;
            __try
            {
                const uint8_t* code = *reinterpret_cast<const uint8_t* const*>(slot);
                for (int hop = 0; code && hop < 4; ++hop)
                {
                    if (code[0] == 0xE9)
                    {
                        int32_t rel = 0;
                        std::memcpy(&rel, code + 1, sizeof(rel));
                        code = code + 5 + rel;
                    }
                    else if (code[0] == 0xFF && code[1] == 0x25)
                    {
                        uint32_t indirect = 0;
                        std::memcpy(&indirect, code + 2, sizeof(indirect));
                        code = *reinterpret_cast<const uint8_t* const*>(
                            static_cast<uintptr_t>(indirect));
                    }
                    else
                    {
                        break;
                    }
                }
                return code ? Dgb::DecodeByteGetterOffset(code) : 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        bool DecodeRenderableLayout()
        {
            g_DgRenderableLayout.identityProjection =
                DecodeOgreByteGetter("?getUseIdentityProjection@Renderable@Ogre@@QBE_NXZ");
            g_DgRenderableLayout.identityView =
                DecodeOgreByteGetter("?getUseIdentityView@Renderable@Ogre@@QBE_NXZ");
            // Both are bools inside Ogre::Renderable, well inside the batch.
            return g_DgRenderableLayout.identityProjection != 0 &&
                   g_DgRenderableLayout.identityView != 0 &&
                   g_DgRenderableLayout.identityProjection < Dgb::kBatchCreationIndex &&
                   g_DgRenderableLayout.identityView < Dgb::kBatchCreationIndex &&
                   g_DgRenderableLayout.identityProjection !=
                       g_DgRenderableLayout.identityView;
        }

        void* ReadCurrentBatch(void* dg)
        {
            __try
            {
                return *reinterpret_cast<void* const*>(
                    static_cast<const uint8_t*>(dg) + Dgb::kDgCurrentBatch);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        uint32_t ReadMaterialRep(const void* materialPtr)
        {
            __try
            {
                return *static_cast<const uint32_t*>(materialPtr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        // True when the begin() can be absorbed by the current batch: stock
        // would open a new piece only because the exact squared depth
        // differs, and the new piece would get the same depth key. Such a
        // piece sorts directly after the current one (creation index is the
        // final tie-break) and the merge concatenates them, so appending to
        // the current batch produces the same merged vertex and index data
        // and keeps the head's squared depth.
        bool TryAbsorbBegin(void* dg, uint32_t materialRep, int32_t op, float dist)
        {
            if (!g_DgDepthKeyEntry || !Dgb::ReusableBeginDistance(dist) || materialRep == 0)
                return false;
            __try
            {
                auto* dgBytes = static_cast<uint8_t*>(dg);
                const uint8_t* batch = *reinterpret_cast<const uint8_t* const*>(
                    dgBytes + Dgb::kDgCurrentBatch);
                if (!batch)
                    return false;
                const float squared = dist * dist;
                // Exact match: stock reuses the batch itself.
                if (Dgb::Read<float>(batch, Dgb::kBatchSquaredDepth) == squared)
                    return false;
                if (batch[Dgb::kBatchMergeable] == 0 ||
                    Dgb::Read<int32_t>(batch, Dgb::kBatchOperation) != op ||
                    Dgb::Read<uint32_t>(batch, Dgb::kBatchMaterialRep) != materialRep)
                    return false;
                const auto groupFn = reinterpret_cast<FnDgGroup>(
                    (*reinterpret_cast<void* const* const*>(dgBytes))
                        [Dgb::kDgGroupVirtualOffset / sizeof(void*)]);
                const uint8_t group = groupFn(dg);
                if (!Dgb::BatchMatchesBegin(
                        batch, dgBytes, materialRep, op, group, g_DgRenderableLayout))
                    return false;

                // The key a new piece would get: run the real depth setter
                // (with OpenShim's alpha coarsening, when installed) on a
                // scratch batch carrying the two fields it reads.
                alignas(16) uint8_t scratch[Dgb::kBatchSize] = {};
                scratch[Dgb::kBatchBlended] = batch[Dgb::kBatchBlended];
                scratch[Dgb::kBatchQueueGroup] = batch[Dgb::kBatchQueueGroup];
                g_DgDepthKeyEntry(scratch, squared);
                return Dgb::Read<float>(scratch, Dgb::kBatchDepthKey) ==
                       Dgb::Read<float>(batch, Dgb::kBatchDepthKey);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ++g_DgCounters.faults;
                return false;
            }
        }

        // Reads the requested name and, when the single cache entry names the
        // current batch's material, returns that batch's MaterialPtr.
        const void* LookupCachedMaterial(
            void* dg, const void* name, uint32_t& rep, bool& nameReadable)
        {
            nameReadable = false;
            __try
            {
                const auto* s = static_cast<const uint8_t*>(name);
                const uint32_t size = Dgb::Read<uint32_t>(s, 0x10);
                const uint32_t capacity = Dgb::Read<uint32_t>(s, 0x14);
                if (capacity < 15 || size > capacity)
                    return nullptr;
                const char* text = capacity >= 16
                    ? *reinterpret_cast<const char* const*>(s)
                    : reinterpret_cast<const char*>(s);
                if (!text)
                    return nullptr;
                nameReadable = size <= Dgb::NameCache::kMaxName;
                const uint8_t* batch = *reinterpret_cast<const uint8_t* const*>(
                    static_cast<const uint8_t*>(dg) + Dgb::kDgCurrentBatch);
                if (!batch)
                {
                    g_DgNameCache.Clear();
                    return nullptr;
                }
                const uint32_t currentRep =
                    Dgb::Read<uint32_t>(batch, Dgb::kBatchMaterialRep);
                if (!g_DgNameCache.Matches(dg, currentRep, text, size))
                    return nullptr;
                rep = currentRep;
                return batch + Dgb::kBatchMaterialRep;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ++g_DgCounters.faults;
                nameReadable = false;
                return nullptr;
            }
        }

        // After a stock by-name begin the current batch holds the material
        // getByName returned, unless the name was missing and the default
        // material was substituted; only the former is cached.
        void StoreCachedMaterial(void* dg, const void* name)
        {
            __try
            {
                const auto* s = static_cast<const uint8_t*>(name);
                const uint32_t size = Dgb::Read<uint32_t>(s, 0x10);
                const uint32_t capacity = Dgb::Read<uint32_t>(s, 0x14);
                const char* text = capacity >= 16
                    ? *reinterpret_cast<const char* const*>(s)
                    : reinterpret_cast<const char*>(s);
                const auto* dgBytes = static_cast<const uint8_t*>(dg);
                const uint8_t* batch = *reinterpret_cast<const uint8_t* const*>(
                    dgBytes + Dgb::kDgCurrentBatch);
                if (!batch || !text || capacity < 15 || size > capacity)
                {
                    g_DgNameCache.Clear();
                    return;
                }
                const uint32_t rep = Dgb::Read<uint32_t>(batch, Dgb::kBatchMaterialRep);
                const uint32_t defaultRep =
                    Dgb::Read<uint32_t>(dgBytes, Dgb::kDgDefaultMaterial);
                if (rep == defaultRep)
                {
                    g_DgNameCache.Clear();
                    return;
                }
                g_DgNameCache.Store(dg, rep, text, size);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ++g_DgCounters.faults;
                g_DgNameCache.Clear();
            }
        }

        void __fastcall DgBeginByMaterialHook(
            void* dg, void* /*edx*/, const void* material, int32_t op, float dist)
        {
            ++g_DgCounters.beginByMaterial;
            if (g_DgPieceReuseEnabled && dg && material &&
                TryAbsorbBegin(dg, ReadMaterialRep(material), op, dist))
            {
                ++g_DgCounters.reused;
                return;
            }
            void* const before = ReadCurrentBatch(dg);
            g_DgBeginByMaterialOriginal(dg, material, op, dist);
            if (ReadCurrentBatch(dg) != before)
                ++g_DgCounters.newBatches;
        }

        void __fastcall DgBeginByNameHook(
            void* dg, void* /*edx*/, const void* name, int32_t op, float dist)
        {
            ++g_DgCounters.beginByName;
            bool nameReadable = false;
            if (g_DgMaterialCacheEnabled && dg && name)
            {
                uint32_t rep = 0;
                const void* cached = LookupCachedMaterial(dg, name, rep, nameReadable);
                if (cached)
                {
                    ++g_DgCounters.cacheHits;
                    if (g_DgPieceReuseEnabled && TryAbsorbBegin(dg, rep, op, dist))
                    {
                        ++g_DgCounters.reused;
                        return;
                    }
                    // Same material getByName would return: the by-material
                    // entry does the same work minus the name lookup. The
                    // MaterialPtr lives in the current batch, which stays in
                    // the batch list when a new one is opened.
                    void* const before = ReadCurrentBatch(dg);
                    g_DgBeginByMaterialOriginal(dg, cached, op, dist);
                    if (ReadCurrentBatch(dg) != before)
                        ++g_DgCounters.newBatches;
                    return;
                }
                ++g_DgCounters.cacheMisses;
            }
            void* const before = ReadCurrentBatch(dg);
            g_DgBeginByNameOriginal(dg, name, op, dist);
            if (ReadCurrentBatch(dg) != before)
                ++g_DgCounters.newBatches;
            if (nameReadable)
                StoreCachedMaterial(dg, name);
        }

        bool GuardedBatchLess(const void* a, const void* b, bool withDepth)
        {
            __try
            {
                return Dgb::BatchLess(
                    static_cast<const uint8_t*>(a),
                    static_cast<const uint8_t*>(b),
                    g_DgRenderableLayout,
                    withDepth);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ++g_DgCounters.faults;
                return false;
            }
        }

        bool __cdecl DgSortLessHook(const void* a, const void* b)
        {
            const bool fast = GuardedBatchLess(a, b, true);
            if (g_DgSortVerify)
            {
                ++g_DgCounters.sortCompares;
                if (g_DgSortLessOriginal(a, b) != fast)
                    ++g_DgCounters.sortMismatches;
            }
            return fast;
        }

        bool __cdecl DgOpaqueSortLessHook(const void* a, const void* b)
        {
            const bool fast = GuardedBatchLess(a, b, false);
            if (g_DgSortVerify)
            {
                ++g_DgCounters.sortCompares;
                if (g_DgOpaqueSortLessOriginal(a, b) != fast)
                    ++g_DgCounters.sortMismatches;
            }
            return fast;
        }

        // Once per prepareForSubmit: drop the name cache (bounds any
        // MaterialManager rename/removal to one frame) and log engagement.
        void DgBatchingFrameTick()
        {
            g_DgNameCache.Clear();
            ++g_DgCounters.prepares;
            const ULONGLONG now = GetTickCount64();
            if (g_DgLastLogTick == 0)
            {
                g_DgLastLogTick = now;
                g_DgCountersAtLastLog = g_DgCounters;
                return;
            }
            const ULONGLONG interval = g_DgBeginStats ? 10000ull : 60000ull;
            if (now - g_DgLastLogTick < interval)
                return;
            const DgBatchingCounters& c = g_DgCounters;
            const DgBatchingCounters& p = g_DgCountersAtLastLog;
            const uint64_t prepares = c.prepares - p.prepares;
            const double perPrepare = prepares ? 1.0 / static_cast<double>(prepares) : 0.0;
            LogShimA(
                LogLevel::Info,
                "render",
                "[DgBatching] window=%llums prepares=%llu per-prepare: beginMat=%.1f beginName=%.1f newBatches=%.1f reused=%.1f cacheHit=%.1f cacheMiss=%.1f | totals reused=%llu new=%llu faults=%llu sortVerify=%llu/%llu reuse=%d cache=%d fastSort=%d",
                static_cast<unsigned long long>(now - g_DgLastLogTick),
                static_cast<unsigned long long>(prepares),
                static_cast<double>(c.beginByMaterial - p.beginByMaterial) * perPrepare,
                static_cast<double>(c.beginByName - p.beginByName) * perPrepare,
                static_cast<double>(c.newBatches - p.newBatches) * perPrepare,
                static_cast<double>(c.reused - p.reused) * perPrepare,
                static_cast<double>(c.cacheHits - p.cacheHits) * perPrepare,
                static_cast<double>(c.cacheMisses - p.cacheMisses) * perPrepare,
                static_cast<unsigned long long>(c.reused),
                static_cast<unsigned long long>(c.newBatches),
                static_cast<unsigned long long>(c.faults),
                static_cast<unsigned long long>(c.sortMismatches),
                static_cast<unsigned long long>(c.sortCompares),
                g_DgPieceReuseEnabled ? 1 : 0,
                g_DgMaterialCacheEnabled ? 1 : 0,
                g_DgFastSortEnabled ? 1 : 0);
            g_DgLastLogTick = now;
            g_DgCountersAtLastLog = c;
        }

        void InstallDynamicGeometryBatchingHooks(bool& wantPrepareHook)
        {
            g_DgPieceReuseEnabled =
                !(EnvFlagEnabled("OPENSHIM_DISABLE_DG_PIECE_REUSE") ||
                  EnvFlagEnabled("BZR_DISABLE_DG_PIECE_REUSE"));
            // Opt-in: measured combat issues ~10 by-name begins per frame and
            // the cache never hit, so it ships off ([Experimental]).
            g_DgMaterialCacheEnabled =
                EnvFlagEnabled("OPENSHIM_DG_MATERIAL_CACHE") ||
                EnvFlagEnabled("BZR_DG_MATERIAL_CACHE");
            g_DgFastSortEnabled =
                !(EnvFlagEnabled("OPENSHIM_DISABLE_DG_FAST_SORT") ||
                  EnvFlagEnabled("BZR_DISABLE_DG_FAST_SORT"));
            g_DgBeginStats = EnvFlagEnabled("OPENSHIM_DG_BEGIN_STATS");
            g_DgSortVerify = EnvFlagEnabled("OPENSHIM_DG_SORT_VERIFY");

            const bool wantBegin =
                g_DgPieceReuseEnabled || g_DgMaterialCacheEnabled || g_DgBeginStats;
            if (g_IsSteamExe || (!wantBegin && !g_DgFastSortEnabled))
            {
                g_DgPieceReuseEnabled = false;
                g_DgMaterialCacheEnabled = false;
                g_DgFastSortEnabled = false;
                return;
            }

            static uintptr_t s_DepthKey = 0;
            static uintptr_t s_BeginByMaterial = 0;
            static uintptr_t s_BeginByName = 0;
            static uintptr_t s_SortLess = 0;
            static uintptr_t s_OpaqueSortLess = 0;
            static const bool bound = [] {
                const HookEngine::EngineRow rows[] = {
                    { "DynamicGeometrySetSquaredViewDepth", &s_DepthKey },
                    { "DynamicGeometryBeginByMaterial", &s_BeginByMaterial },
                    { "DynamicGeometryBeginByName", &s_BeginByName },
                    { "DynamicGeometrySortLess", &s_SortLess },
                    { "DynamicGeometryOpaqueSortLess", &s_OpaqueSortLess },
                };
                return HookEngine::BindEngineRows("DynamicGeometry batching", rows);
            }();
            static const bool layoutOk = DecodeRenderableLayout();
            if (!bound || !layoutOk)
            {
                g_DgPieceReuseEnabled = false;
                g_DgMaterialCacheEnabled = false;
                g_DgFastSortEnabled = false;
                LogShimA(
                    LogLevel::Warn,
                    "render",
                    "[DgBatching] unavailable: rows=%d renderableLayout=%d (proj=0x%X view=0x%X)",
                    bound ? 1 : 0,
                    layoutOk ? 1 : 0,
                    g_DgRenderableLayout.identityProjection,
                    g_DgRenderableLayout.identityView);
                return;
            }
            // Called through the (possibly detoured) entry so a candidate key
            // gets the same alpha coarsening a real new piece would.
            g_DgDepthKeyEntry =
                reinterpret_cast<FnDynamicGeometrySetSquaredViewDepth>(s_DepthKey);

            if (wantBegin)
            {
                static const uint8_t kByMaterialPrologue[] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08 };
                static const uint8_t kByNamePrologue[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
                const bool byMaterial = InstallInlineDetour32(
                    g_DgBeginByMaterialDetour,
                    s_BeginByMaterial,
                    reinterpret_cast<void*>(&DgBeginByMaterialHook),
                    sizeof(kByMaterialPrologue),
                    kByMaterialPrologue,
                    sizeof(kByMaterialPrologue));
                if (byMaterial)
                    g_DgBeginByMaterialOriginal = reinterpret_cast<FnDgBeginByMaterial>(
                        g_DgBeginByMaterialDetour.trampoline);
                // The by-name hook forwards cache hits to the by-material
                // original, so it is installed only after that one.
                const bool byName = byMaterial && InstallInlineDetour32(
                    g_DgBeginByNameDetour,
                    s_BeginByName,
                    reinterpret_cast<void*>(&DgBeginByNameHook),
                    sizeof(kByNamePrologue),
                    kByNamePrologue,
                    sizeof(kByNamePrologue));
                if (byName)
                    g_DgBeginByNameOriginal = reinterpret_cast<FnDgBeginByName>(
                        g_DgBeginByNameDetour.trampoline);
                if (!byName)
                    g_DgMaterialCacheEnabled = false;
                if (!byMaterial)
                    g_DgPieceReuseEnabled = false;
                g_DgBeginHooksActive = byMaterial;
                wantPrepareHook = wantPrepareHook || byMaterial;
            }
            else
            {
                g_DgPieceReuseEnabled = false;
                g_DgMaterialCacheEnabled = false;
            }

            if (g_DgFastSortEnabled)
            {
                static const uint8_t kSortPrologue[] = { 0x55, 0x8B, 0xEC, 0x51, 0x56 };
                const bool mainSort = InstallInlineDetour32(
                    g_DgSortLessDetour,
                    s_SortLess,
                    reinterpret_cast<void*>(&DgSortLessHook),
                    sizeof(kSortPrologue),
                    kSortPrologue,
                    sizeof(kSortPrologue));
                if (mainSort)
                    g_DgSortLessOriginal =
                        reinterpret_cast<FnDgSortLess>(g_DgSortLessDetour.trampoline);
                const bool opaqueSort = InstallInlineDetour32(
                    g_DgOpaqueSortLessDetour,
                    s_OpaqueSortLess,
                    reinterpret_cast<void*>(&DgOpaqueSortLessHook),
                    sizeof(kSortPrologue),
                    kSortPrologue,
                    sizeof(kSortPrologue));
                if (opaqueSort)
                    g_DgOpaqueSortLessOriginal =
                        reinterpret_cast<FnDgSortLess>(g_DgOpaqueSortLessDetour.trampoline);
                g_DgFastSortEnabled = mainSort || opaqueSort;
                wantPrepareHook = wantPrepareHook || (g_DgSortVerify && g_DgFastSortEnabled);
            }

            LogShimA(
                LogLevel::Info,
                "render",
                "[DgBatching] installed pieceReuse=%d materialCache=%d fastSort=%d stats=%d sortVerify=%d renderable proj=+0x%X view=+0x%X optOut=OPENSHIM_DISABLE_DG_PIECE_REUSE/_FAST_SORT optIn=OPENSHIM_DG_MATERIAL_CACHE",
                g_DgPieceReuseEnabled ? 1 : 0,
                g_DgMaterialCacheEnabled ? 1 : 0,
                g_DgFastSortEnabled ? 1 : 0,
                g_DgBeginStats ? 1 : 0,
                g_DgSortVerify ? 1 : 0,
                g_DgRenderableLayout.identityProjection,
                g_DgRenderableLayout.identityView);
        }
    }

    // Dynamic alpha depth batching and the opt-in DynamicGeometry profiler
    // observers. GOG only: both detours check the exact prologue bytes.
    void InstallDynamicGeometryHooks()
    {
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
        static uintptr_t s_SetSquaredViewDepthAddr = 0;
        const bool depthBound = !g_IsSteamExe && g_DynamicAlphaDepthBatchingEnabled && [] {
            static const bool bound = [] {
                const HookEngine::EngineRow rows[] = {
                    { "DynamicGeometrySetSquaredViewDepth", &s_SetSquaredViewDepthAddr },
                };
                return HookEngine::BindEngineRows("Dynamic alpha batching", rows);
            }();
            return bound;
        }();
        if (depthBound)
        {
            static const uint8_t kDynamicGeometryDepthPrologue[] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08
            };
            if (InstallInlineDetour32(
                    g_DynamicGeometrySetSquaredViewDepthDetour,
                    s_SetSquaredViewDepthAddr,
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
                    "Dynamic alpha batching installed target=0x%08X stride=%u optOut=OPENSHIM_DISABLE_DYNAMIC_ALPHA_BATCHING",
                    static_cast<unsigned>(s_SetSquaredViewDepthAddr),
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
        bool wantPrepareHook = false;
        InstallDynamicGeometryBatchingHooks(wantPrepareHook);
        const bool profilerCollecting = IsOgreAnimationProfilerCollecting();
        static uintptr_t s_PrepareAddr = 0;
        if (!g_IsSteamExe && (profilerCollecting || wantPrepareHook))
        {
            static const bool prepareBound = [] {
                const HookEngine::EngineRow rows[] = {
                    { "DynamicGeometryPrepare", &s_PrepareAddr },
                };
                return HookEngine::BindEngineRows("DynamicGeometry profiler observer", rows);
            }();
            static const uint8_t kDynamicGeometryPreparePrologue[] =
            {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF
            };
            if (prepareBound &&
                InstallInlineDetour32(
                    g_DynamicGeometryPrepareDetour,
                    s_PrepareAddr,
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
                    "[OgreProfile] installed GOG DynamicGeometry::prepareForSubmit observer target=0x%08X trampoline=0x%p",
                    static_cast<unsigned>(s_PrepareAddr),
                    g_DynamicGeometryPrepareDetour.trampoline);
            }
            else
            {
                LogShimA(
                    LogLevel::Warn,
                    "ogre-profile",
                    "[OgreProfile] GOG DynamicGeometry::prepareForSubmit prologue mismatch; native rebuild attribution unavailable");
            }
        }
        if (!g_IsSteamExe && profilerCollecting)
        {
            static const uintptr_t kRenderQueueAddRenderableIatSlot = FindMainImageImportSlot(
                "OgreMain.dll", "?addRenderable@RenderQueue@Ogre@@QAEXPAVRenderable@2@E@Z");
            void* const currentAddRenderable = kRenderQueueAddRenderableIatSlot
                ? *reinterpret_cast<void**>(kRenderQueueAddRenderableIatSlot)
                : nullptr;
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
                    "[OgreProfile] installed DynamicGeometry addRenderable batch counter IAT=0x%08X original=0x%p",
                    static_cast<unsigned>(kRenderQueueAddRenderableIatSlot),
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
        if (g_DgBeginHooksActive || g_DgSortVerify)
            DgBatchingFrameTick();
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
