// diag_vehicle_skinning.cpp
// BZR Open Shim - DIAGNOSTIC ONLY: vehicle skinning probe (captures the
// player vehicle entity/skeleton state for skinning investigations),
// split out of bzr_hooks.cpp.
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
    namespace Hooks
    {
        struct VehicleSkinningProbeResult
        {
            bool initialized = false;
            bool visible = false;
            bool hasSkeleton = false;
            bool hardwareAnimation = false;
            bool animated = false;
            bool skeletonAnimated = false;
            uint16_t boneCount = 0;
            uint16_t boneMatrixCount = 0;
            int softwareRequests = 0;
            int softwareNormalRequests = 0;
            uint32_t subEntityCount = 0;
            char entityName[96] = {};
            char materialNames[512] = {};
        };

        static bool TryCaptureVehicleSkinningProbe(
            void* entity,
            FnOgreEntityBoolQuery isInitialised,
            FnOgreEntityBoolQuery isVisible,
            FnOgreEntityBoolQuery hasSkeleton,
            FnOgreEntityBoolQuery isHardwareAnimationEnabled,
            FnOgreEntityBoolQuery isAnimated,
            FnOgreEntityBoolQuery isSkeletonAnimated,
            FnOgreEntityU16Query getNumBoneMatrices,
            FnOgreEntityGetSkeleton getSkeleton,
            FnOgreEntityU16Query getNumBones,
            FnOgreEntityIntQuery getSoftwareRequests,
            FnOgreEntityIntQuery getSoftwareNormalRequests,
            FnOgreGetNumSubEntities getNumSubEntities,
            FnOgreGetSubEntity getSubEntity,
            FnOgreStringQuery getEntityName,
            FnOgreStringQuery getMaterialName,
            VehicleSkinningProbeResult& outProbe)
        {
            outProbe = {};
            if (!entity || !isInitialised || !hasSkeleton ||
                !isHardwareAnimationEnabled || !getNumBoneMatrices ||
                !getNumSubEntities || !getSubEntity)
            {
                return false;
            }

            __try
            {
                outProbe.initialized = isInitialised(entity);
                if (!outProbe.initialized)
                    return true;

                outProbe.visible = isVisible ? isVisible(entity) : false;
                outProbe.hasSkeleton = hasSkeleton(entity);
                outProbe.hardwareAnimation = isHardwareAnimationEnabled(entity);
                outProbe.animated = isAnimated ? isAnimated(entity) : false;
                outProbe.skeletonAnimated = isSkeletonAnimated ? isSkeletonAnimated(entity) : false;
                outProbe.boneMatrixCount = getNumBoneMatrices(entity);
                outProbe.softwareRequests = getSoftwareRequests ? getSoftwareRequests(entity) : 0;
                outProbe.softwareNormalRequests =
                    getSoftwareNormalRequests ? getSoftwareNormalRequests(entity) : 0;
                outProbe.subEntityCount = getNumSubEntities(entity);

                if (getSkeleton && getNumBones && outProbe.hasSkeleton)
                {
                    void* const skeleton = getSkeleton(entity);
                    if (skeleton)
                    {
                        const uint16_t count = getNumBones(skeleton);
                        if (count <= 1024)
                            outProbe.boneCount = count;
                    }
                }

                if (getEntityName)
                {
                    const std::string& name = getEntityName(entity);
                    strncpy_s(outProbe.entityName, name.c_str(), _TRUNCATE);
                }

                if (getMaterialName)
                {
                    const uint32_t materialLimit =
                        (outProbe.subEntityCount < 16u) ? outProbe.subEntityCount : 16u;
                    for (uint32_t index = 0; index < materialLimit; ++index)
                    {
                        void* const subEntity = getSubEntity(entity, index);
                        if (!subEntity)
                            continue;

                        const std::string& materialName = getMaterialName(subEntity);
                        const size_t used = strlen(outProbe.materialNames);
                        if (used + 2 >= sizeof(outProbe.materialNames))
                            break;
                        _snprintf_s(
                            outProbe.materialNames + used,
                            sizeof(outProbe.materialNames) - used,
                            _TRUNCATE,
                            "%s%s",
                            used ? ";" : "",
                            materialName.c_str());
                    }
                }

                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outProbe = {};
                return false;
            }
        }

        void RefreshVehicleSkinningDiagnosticsIfNeeded()
        {
            if (!g_VehicleSkinningTraceEnabled)
                return;

            const DWORD now = GetTickCount();
            if (g_VehicleSkinningTraceLastTick != 0 &&
                static_cast<DWORD>(now - g_VehicleSkinningTraceLastTick) <
                    g_VehicleSkinningTraceIntervalMs)
            {
                return;
            }
            g_VehicleSkinningTraceLastTick = now;

            static FnOgreEntityBoolQuery isInitialised =
                ResolveOgreProc<FnOgreEntityBoolQuery>("?isInitialised@Entity@Ogre@@QBE_NXZ");
            static FnOgreEntityBoolQuery isVisible =
                ResolveOgreProc<FnOgreEntityBoolQuery>("?isVisible@MovableObject@Ogre@@UBE_NXZ");
            static FnOgreEntityBoolQuery hasSkeleton =
                ResolveOgreProc<FnOgreEntityBoolQuery>("?hasSkeleton@Entity@Ogre@@QBE_NXZ");
            static FnOgreEntityBoolQuery isHardwareAnimationEnabled =
                ResolveOgreProc<FnOgreEntityBoolQuery>("?isHardwareAnimationEnabled@Entity@Ogre@@QAE_NXZ");
            static FnOgreEntityBoolQuery isAnimated =
                ResolveOgreProc<FnOgreEntityBoolQuery>("?_isAnimated@Entity@Ogre@@QBE_NXZ");
            static FnOgreEntityBoolQuery isSkeletonAnimated =
                ResolveOgreProc<FnOgreEntityBoolQuery>("?_isSkeletonAnimated@Entity@Ogre@@QBE_NXZ");
            static FnOgreEntityU16Query getNumBoneMatrices =
                ResolveOgreProc<FnOgreEntityU16Query>("?_getNumBoneMatrices@Entity@Ogre@@QBEGXZ");
            static FnOgreEntityGetSkeleton getSkeleton =
                ResolveOgreProc<FnOgreEntityGetSkeleton>("?getSkeleton@Entity@Ogre@@QBEPAVSkeletonInstance@2@XZ");
            static FnOgreEntityU16Query getNumBones =
                ResolveOgreProc<FnOgreEntityU16Query>("?getNumBones@Skeleton@Ogre@@UBEGXZ");
            static FnOgreEntityIntQuery getSoftwareRequests =
                ResolveOgreProc<FnOgreEntityIntQuery>("?getSoftwareAnimationRequests@Entity@Ogre@@QBEHXZ");
            static FnOgreEntityIntQuery getSoftwareNormalRequests =
                ResolveOgreProc<FnOgreEntityIntQuery>("?getSoftwareAnimationNormalsRequests@Entity@Ogre@@QBEHXZ");
            static FnOgreGetNumSubEntities getNumSubEntities =
                ResolveOgreProc<FnOgreGetNumSubEntities>("?getNumSubEntities@Entity@Ogre@@QBEIXZ");
            static FnOgreGetSubEntity getSubEntity =
                ResolveOgreProc<FnOgreGetSubEntity>("?getSubEntity@Entity@Ogre@@QBEPAVSubEntity@2@I@Z");
            static FnOgreStringQuery getEntityName =
                ResolveOgreProc<FnOgreStringQuery>("?getName@MovableObject@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            static FnOgreStringQuery getMaterialName =
                ResolveOgreProc<FnOgreStringQuery>("?getMaterialName@SubEntity@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

            if (!isInitialised || !hasSkeleton || !isHardwareAnimationEnabled ||
                !getNumBoneMatrices || !getNumSubEntities || !getSubEntity)
            {
                static volatile long s_MissingProcLogBudget = 1;
                if (InterlockedDecrement(&s_MissingProcLogBudget) >= 0)
                {
                    Log(L"[SKINNING] required Ogre exports missing init=%u skeleton=%u hardware=%u bones=%u subentities=%u getsub=%u\n",
                        isInitialised ? 1u : 0u,
                        hasSkeleton ? 1u : 0u,
                        isHardwareAnimationEnabled ? 1u : 0u,
                        getNumBoneMatrices ? 1u : 0u,
                        getNumSubEntities ? 1u : 0u,
                        getSubEntity ? 1u : 0u);
                }
                return;
            }

            static void* s_skinningObjects[kGameObjectArenaSlotCapacity];
            const size_t totalObjects =
                CollectLiveGameObjectsFromArena(s_skinningObjects, kGameObjectArenaSlotCapacity);
            if (totalObjects == 0)
                return;

            const size_t objectLimit =
                (totalObjects < kChunkObjectIdentityMaxObjectsPerRefresh)
                    ? totalObjects
                    : kChunkObjectIdentityMaxObjectsPerRefresh;
            std::unordered_set<uintptr_t> seenEntities;
            seenEntities.reserve(objectLimit);

            uint32_t initializedEntities = 0;
            uint32_t skinnedEntities = 0;
            uint32_t visibleSkinnedEntities = 0;
            uint32_t hardwareEntities = 0;
            uint32_t cpuFallbackEntities = 0;
            uint32_t softwareRequestedEntities = 0;
            uint32_t animatedEntities = 0;
            uint32_t totalBones = 0;
            uint32_t totalBoneMatrices = 0;
            uint32_t totalSubEntities = 0;

            for (size_t index = 0; index < objectLimit; ++index)
            {
                void* obj76 = nullptr;
                if (!TryGetGameObjectObj76(s_skinningObjects[index], obj76) || !obj76)
                    continue;

                const ChunkBridgeSnapshot snapshot =
                    CaptureChunkBridgeSnapshot(reinterpret_cast<const uint8_t*>(obj76));
                void* const candidates[] = {
                    snapshot.directOgreEntity,
                    (snapshot.ownerOgreEntity != snapshot.directOgreEntity)
                        ? snapshot.ownerOgreEntity
                        : nullptr,
                };

                for (void* entity : candidates)
                {
                    if (!entity || !seenEntities.insert(reinterpret_cast<uintptr_t>(entity)).second)
                        continue;

                    VehicleSkinningProbeResult probe = {};
                    if (!TryCaptureVehicleSkinningProbe(
                            entity,
                            isInitialised,
                            isVisible,
                            hasSkeleton,
                            isHardwareAnimationEnabled,
                            isAnimated,
                            isSkeletonAnimated,
                            getNumBoneMatrices,
                            getSkeleton,
                            getNumBones,
                            getSoftwareRequests,
                            getSoftwareNormalRequests,
                            getNumSubEntities,
                            getSubEntity,
                            getEntityName,
                            getMaterialName,
                            probe))
                    {
                        continue;
                    }

                    if (probe.initialized)
                        ++initializedEntities;
                    if (!probe.initialized || !probe.hasSkeleton)
                        continue;

                    ++skinnedEntities;
                    if (probe.visible)
                        ++visibleSkinnedEntities;
                    if (probe.hardwareAnimation)
                        ++hardwareEntities;
                    else
                        ++cpuFallbackEntities;
                    if (probe.softwareRequests > 0 || probe.softwareNormalRequests > 0)
                        ++softwareRequestedEntities;
                    if (probe.animated)
                        ++animatedEntities;
                    totalBones += probe.boneCount;
                    totalBoneMatrices += probe.boneMatrixCount;
                    totalSubEntities += probe.subEntityCount;

                    char meshName[48] = {};
                    if (snapshot.ownerResolvedMeshName[0])
                    {
                        strncpy_s(meshName, snapshot.ownerResolvedMeshName, _TRUNCATE);
                    }
                    else
                    {
                        TryGetGameObjectMeshName(s_skinningObjects[index], meshName, sizeof(meshName));
                    }
                    const char* const identity = meshName[0]
                        ? meshName
                        : (probe.entityName[0] ? probe.entityName : "<unknown>");
                    const char* const mode =
                        (probe.softwareRequests > 0 || probe.softwareNormalRequests > 0)
                            ? (probe.hardwareAnimation ? "gpu+software-request" : "cpu-requested")
                            : (probe.hardwareAnimation ? "gpu" : "cpu-fallback");

                    std::string fingerprint(identity);
                    fingerprint += '|';
                    fingerprint += mode;
                    fingerprint += '|';
                    fingerprint += probe.materialNames;
                    if (g_VehicleSkinningTraceBudget > 0 &&
                        g_VehicleSkinningTraceFingerprints.insert(fingerprint).second &&
                        InterlockedDecrement(&g_VehicleSkinningTraceBudget) >= 0)
                    {
                        Log(L"[SKINNING] mesh=%hs entityName=%hs entity=0x%08X mode=%hs visible=%u animated=%u skeletonAnimated=%u bones=%u boneMatrices=%u softwareRequests=%d softwareNormalRequests=%d subentities=%u materials=%hs\n",
                            identity,
                            probe.entityName[0] ? probe.entityName : "<none>",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entity)),
                            mode,
                            probe.visible ? 1u : 0u,
                            probe.animated ? 1u : 0u,
                            probe.skeletonAnimated ? 1u : 0u,
                            static_cast<unsigned>(probe.boneCount),
                            static_cast<unsigned>(probe.boneMatrixCount),
                            probe.softwareRequests,
                            probe.softwareNormalRequests,
                            probe.subEntityCount,
                            probe.materialNames[0] ? probe.materialNames : "<none>");
                    }
                }
            }

            Log(L"[SKINNING] summary objects=%u scanned=%u uniqueEntities=%u initialized=%u skinned=%u visible=%u animated=%u gpu=%u cpuFallback=%u softwareRequested=%u bones=%u boneMatrices=%u subentities=%u detailBudget=%ld\n",
                static_cast<unsigned>(totalObjects),
                static_cast<unsigned>(objectLimit),
                static_cast<unsigned>(seenEntities.size()),
                initializedEntities,
                skinnedEntities,
                visibleSkinnedEntities,
                animatedEntities,
                hardwareEntities,
                cpuFallbackEntities,
                softwareRequestedEntities,
                totalBones,
                totalBoneMatrices,
                totalSubEntities,
                static_cast<long>(g_VehicleSkinningTraceBudget));
        }
    }

}
