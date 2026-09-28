// chunk_proxy_render.cpp
// BZR Open Shim - chunk proxy rendering: proxy slots and transforms,
// the Ogre billboard/entity proxies under the Ogre call guards, render
// queue submission, the generic chunk batch, the per-frame debug and
// chunk-effect tracking, and the create/fragment hook installers, split
// out of bzr_hooks.cpp.
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
    FnChunkEffectCreateChunk g_BzrFn_ChunkEffectCreateChunk = nullptr;
    FnChunkEffectCreateChunklet g_BzrFn_ChunkEffectCreateChunklet = nullptr;
    FnChunkEffectFragmentObject g_BzrFn_ChunkEffectPartialFragment = nullptr;
    FnChunkEffectFragmentObject g_BzrFn_ChunkEffectFullFragment = nullptr;

    namespace Hooks
    {
        bool g_EnableChunkProxyDebug = false;
        bool g_EnableChunkMeshProxy = false;
        bool g_EnableGenericChunkBatch = false;
        bool g_TraceChunkRender = false;
        bool g_TraceChunkRenderVerbose = false;
        bool g_TraceChunkEffectRuntime = false;
        uint32_t g_LastChunkEffectLoggedCount = UINT32_MAX;
        volatile long g_ChunkRenderLogBudget = 12;
        uint32_t g_ChunkTraceEntryLimit = 32;
        // 96 slots exhaust in multi-craft battles (each death emits ~10 geo
        // pieces plus impact chunklets); once full, new chunks are silently
        // dropped until a slot expires.
        uint32_t g_ChunkProxyCapacity = 256;
        float g_ChunkProxyDebugSize = 2.5f;
        std::unordered_map<uintptr_t, uint32_t> g_ChunkObservedClassIds = {};
        InlineDetour32 g_ChunkEffectCreateChunkDetour = {};
        InlineDetour32 g_ChunkEffectCreateChunkletDetour = {};
        bool g_ChunkEffectCreateHooksInstalled = false;
        bool g_ChunkEffectCreateHooksLogged = false;
        InlineDetour32 g_ChunkEffectPartialFragmentDetour = {};
        InlineDetour32 g_ChunkEffectFullFragmentDetour = {};
        bool g_ChunkEffectFragmentHooksInstalled = false;
        bool g_AllowUnsafeSteamChunkCreateHooks = false;
        bool g_ChunkEffectCreateHooksWaitLogged = false;
        bool g_ChunkEffectCreateHooksMismatchLogged = false;
        ULONGLONG g_ChunkEffectCreateHooksReadyTick = 0;
        DWORD g_ChunkProxyLastRetryTick = 0;
        bool g_ChunkProxyInitLogged = false;
        bool g_ChunkProxyFailureLogged = false;
        bool g_ChunkProxyWaitLogged = false;
        DWORD g_ChunkMeshProxyLastRetryTick = 0;
        bool g_ChunkMeshProxyInitLogged = false;
        bool g_ChunkMeshProxyFailureLogged = false;
        bool g_ChunkMeshProxyWaitLogged = false;
        bool g_ChunkPayloadResourceLocationsAttempted = false;
        bool g_ChunkPayloadResourceLocationsReady = false;
        bool g_ChunkPayloadResourceLocationsLogged = false;
        bool g_ChunkPayloadResourceLocationsFailureLogged = false;
        std::vector<std::filesystem::path> g_ChunkPayloadResourceDirectories = {};
        void* g_ChunkProxyBillboardSet = nullptr;
        std::vector<ChunkProxySlot> g_ChunkProxySlots = {};
        void* g_GenericChunkBatchManualObject = nullptr;
        void* g_GenericChunkBatchSceneNode = nullptr;
        void* g_GenericChunkBatchSceneManager = nullptr;
        bool g_GenericChunkBatchSectionCreated = false;
        bool g_GenericChunkBatchRuntimeAvailable = true;
        int g_GenericChunkBatchEligibility[2] = { -1, -1 };
        DWORD g_GenericChunkBatchLastLogTick = 0;
        // Bounded diagnostics for the per-frame submission question: the game
        // drives its _updateRenderQueue override more than once per frame (one
        // traversal per active material scheme), and the ManualObject is also
        // attached to the scene graph, so the number of rebuilds and the number
        // of render-queue submissions per frame must be counted, not assumed.
        bool g_GenericChunkBatchRateDiagnostics = false;
        // State-version reuse. The batch is re-submitted to every camera/scheme
        // traversal, but the geometry is only re-emitted when the slot state it
        // is built from actually differs. See include/chunk_batch_invalidation.h
        // for why the version is derived from the source rather than declared by
        // its mutators.
        bool g_GenericChunkBatchReuseEnabled = true;
        // Observer mode: take the decision and count it, then rebuild anyway.
        // This is how the pre-optimization baseline and the dedup opportunity
        // are measured from the same binary, without changing what is drawn.
        bool g_GenericChunkBatchReuseObserveOnly = false;
        uint64_t g_GenericChunkBatchBuiltVersion =
            ChunkBatchInvalidation::kUnbuiltVersion;
        std::string g_GenericChunkBatchBuiltMaterial = {};
        // Last visibility written to the batch object, so setVisible is only
        // called on a transition. Without this the empty path would push
        // setVisible(false) three times per frame for as long as there is no
        // debris, which is most of a normal mission.
        bool g_GenericChunkBatchVisible = false;
        // TEST/DIAGNOSTIC seam only. Set by the environment gate below and
        // never by gameplay: RebuildAndSubmitGenericChunkBatch() reports
        // failure once the slots are already classified batch-ready, which is
        // precisely the window the per-Entity fallback has to cover.
        bool g_ForceGenericChunkBatchFailure = false;
        // TEST/DIAGNOSTIC seam only. ChunkProxyTransform::scale is structurally
        // unit today (the legacy basis vectors are normalised when the
        // quaternion is built), so the unit-scale gate below has no natural
        // trigger. This forces a non-unit scale on tracked generic chunks so
        // the rejection and per-Entity fallback can actually be exercised.
        bool g_ForceGenericChunkNonUnitScale = false;

        void LogChunkDiagnostic(const char* component, const wchar_t* fmt, ...)
        {
            if (!fmt || !*fmt)
                return;

            wchar_t buffer[4096] = {};
            va_list args;
            va_start(args, fmt);
            _vsnwprintf_s(buffer, _countof(buffer), _TRUNCATE, fmt, args);
            va_end(args);

            Log(L"%ls", buffer);
            LogShimW(LogLevel::Info, component, L"%ls", buffer);
        }

        bool AcquireChunkLogSlot()
        {
            if (g_TraceChunkRenderVerbose)
                return true;

            return InterlockedDecrement(&g_ChunkRenderLogBudget) >= 0;
        }

#include "chunk_proxy_generic_meshes.inl"

        constexpr size_t kChunkEffectCreateChunkDetourLen = 9;

        constexpr size_t kChunkEffectCreateChunkletDetourLen = 9;

        constexpr size_t kChunkEffectCreateExpectedLen = 16;

        constexpr uintptr_t kGogChunkEffectPartialFragmentAddr = 0x00492460;

        constexpr uintptr_t kGogChunkEffectFullFragmentAddr = 0x00492640;

        constexpr size_t kChunkEffectFragmentDetourLen = 6;

        static bool g_ChunkEffectFragmentHooksLogged = false;

        static constexpr uintptr_t kOgreSceneManagerOffset = 0x08;

        static constexpr uintptr_t kChunkEffectGateOffset = 0x802C;

        static constexpr uintptr_t kChunkEffectTuningBaseOffset = 0x8038;

        static constexpr uintptr_t kChunkEffectTemplateListOffset = 0x8050;

        static constexpr uintptr_t kChunkEffectEntryBaseOffset = 0x28;

        // The advisory-PDB object-list/userObject/userTeam globals that used
        // to live here (0x50D2F0/F8/E4) landed in string data on the live exe
        // and were removed 2026-07-18. Verified replacements: userObject
        // global 0x00917AFC (EngineGlobals::UserObjectSlot, accessor 0x417C70),
        // object enumeration via the 0x0260DB20 arena
        // (CollectLiveGameObjectsFromArena), team via
        // GetGameObjectActualTeam(userObject).
        static constexpr size_t kChunkEffectEntrySize = 0x20;

        static constexpr DWORD kChunkProxyExpireMs = 400;

        static constexpr DWORD kChunkProxyRetryDelayMs = 1000;

        static constexpr float kChunkProxyEntryPositionTolerance = 256.0f;

        static constexpr float kChunkProxyLocalTransformTolerance = 0.001f;

        static constexpr float kChunkProxyAnchoredTransformAdoptDistance = 1.0f;

        static constexpr float kChunkProxyHiddenY = -100000.0f;

        static constexpr const char* kChunkPayloadResourceLocationType = "FileSystem";

        static uint64_t g_GenericChunkBatchSubmitCalls = 0;

        // Counts successful *submissions*, not geometry rebuilds. Since
        // state-version reuse landed those are different numbers: the rebuild
        // count lives in g_GenericChunkBatchTelemetry.
        static uint64_t g_GenericChunkBatchRebuilds = 0;

        static DWORD g_GenericChunkBatchRateLogTick = 0;

        static uint64_t g_GenericChunkBatchSubmitCallsAtLastLog = 0;

        static uint64_t g_GenericChunkBatchRebuildsAtLastLog = 0;

        static ChunkBatchInvalidation::Telemetry g_GenericChunkBatchTelemetry = {};

        static ChunkBatchInvalidation::Telemetry g_GenericChunkBatchTelemetryAtLastLog = {};

        static int64_t g_GenericChunkBatchQpcFrequency = 0;

        static const std::string g_GenericChunkBatchMaterialName = "scarpmat2";

        static const std::string g_GenericChunkBatchMaterialGroup = "General";

        // Bounded diagnostics. A mod or future runtime that gives a stock
        // chunk1/chunk2 a non-unit transform scale would otherwise be batched
        // with the scale silently dropped, so count the rejections instead of
        // logging one line per chunk per frame.
        static uint64_t g_GenericChunkBatchNonUnitScaleRejections = 0;

        static DWORD g_GenericChunkBatchScaleLogTick = 0;

        static uint64_t g_GenericChunkBatchRehydrations = 0;

        static DWORD g_GenericChunkBatchRehydrateLogTick = 0;

        // Render-pass procs captured at hook time when available; the mangled
        // export fallback in TrySubmitChunkMeshProxyToCurrentRenderQueue covers
        // the case where these were never observed.
        static FnOgreMovableObjectNotifyCurrentCamera g_OgreFn_MovableObjectNotifyCurrentCamera = nullptr;

        static FnOgreEntityUpdateRenderQueue g_OgreFn_EntityUpdateRenderQueue = nullptr;

        static const char* ClassifyChunkGeomName(const char* geomName)
        {
            if (!geomName || !*geomName)
                return "unknown";

            if (_stricmp(geomName, "chunk1") == 0 || _stricmp(geomName, "chunk2") == 0)
                return "stock-chunklet";

            return "named-nonchunklet";
        }

        static const char* GetChunkGeomNameForLog(const char* geomName)
        {
            return (geomName && *geomName) ? geomName : "<none>";
        }

        static bool ShouldUseChunkPayloadMesh(const ChunkProxySlot& slot)
        {
            return g_EnableChunkMeshProxy && slot.proofMeshName[0];
        }

        static const char* GetChunkPayloadMeshName(const ChunkProxySlot& slot)
        {
            return slot.proofMeshName;
        }

        static void HideChunkProxyMesh(ChunkProxySlot& slot);

        static void InvalidateChunkMeshProxySlot(ChunkProxySlot& slot)
        {
            if (slot.meshAssigned)
                HideChunkProxyMesh(slot);

            slot.sceneNode = nullptr;
            slot.entity = nullptr;
            slot.meshAssigned = false;
        }

        int FindChunkGeoEntryByKey(const BzrGeoLookup* lookup, uint32_t key)
        {
            if (!lookup || !lookup->entries || lookup->count == 0 || key == 0)
                return -1;

            for (uint32_t index = 0; index < lookup->count; ++index)
            {
                const BzrGeoEntry& entry = lookup->entries[index];
                if (entry.handle && entry.packedKey == key)
                    return static_cast<int>(index);
            }

            return -1;
        }

        int FindFirstChunkGeoEntryWithHandle(const BzrGeoLookup* lookup)
        {
            if (!lookup || !lookup->entries || lookup->count == 0)
                return -1;

            for (uint32_t index = 0; index < lookup->count; ++index)
            {
                if (lookup->entries[index].handle)
                    return static_cast<int>(index);
            }

            return -1;
        }

        static bool TryBuildOgreQuaternionFromLegacyTransform(
            const LegacyMat3& transform,
            OgreQuaternion& outOrientation)
        {
            outOrientation = { 1.0f, 0.0f, 0.0f, 0.0f };

            double rightX = transform.right_x;
            double rightY = transform.right_y;
            double rightZ = transform.right_z;
            double upX = transform.up_x;
            double upY = transform.up_y;
            double upZ = transform.up_z;
            double frontX = transform.front_x;
            double frontY = transform.front_y;
            double frontZ = transform.front_z;

            const double rightLen = std::sqrt(rightX * rightX + rightY * rightY + rightZ * rightZ);
            const double upLen = std::sqrt(upX * upX + upY * upY + upZ * upZ);
            const double frontLen = std::sqrt(frontX * frontX + frontY * frontY + frontZ * frontZ);
            if (!(std::isfinite(rightLen) && std::isfinite(upLen) && std::isfinite(frontLen)) ||
                rightLen <= 1.0e-8 || upLen <= 1.0e-8 || frontLen <= 1.0e-8)
            {
                return false;
            }

            rightX /= rightLen;
            rightY /= rightLen;
            rightZ /= rightLen;
            upX /= upLen;
            upY /= upLen;
            upZ /= upLen;
            frontX /= frontLen;
            frontY /= frontLen;
            frontZ /= frontLen;

            // LegacyMat3 stores basis vectors directly. Build a rotation matrix
            // with those basis vectors as columns to match Ogre's node orientation.
            const double m00 = rightX;
            const double m10 = rightY;
            const double m20 = rightZ;
            const double m01 = upX;
            const double m11 = upY;
            const double m21 = upZ;
            const double m02 = frontX;
            const double m12 = frontY;
            const double m22 = frontZ;

            double w = 1.0;
            double x = 0.0;
            double y = 0.0;
            double z = 0.0;

            const double trace = m00 + m11 + m22;
            if (trace > 0.0)
            {
                const double s = std::sqrt(trace + 1.0) * 2.0;
                if (!std::isfinite(s) || s <= 1.0e-8)
                    return false;
                w = 0.25 * s;
                x = (m21 - m12) / s;
                y = (m02 - m20) / s;
                z = (m10 - m01) / s;
            }
            else if (m00 > m11 && m00 > m22)
            {
                const double s = std::sqrt(1.0 + m00 - m11 - m22) * 2.0;
                if (!std::isfinite(s) || s <= 1.0e-8)
                    return false;
                w = (m21 - m12) / s;
                x = 0.25 * s;
                y = (m01 + m10) / s;
                z = (m02 + m20) / s;
            }
            else if (m11 > m22)
            {
                const double s = std::sqrt(1.0 + m11 - m00 - m22) * 2.0;
                if (!std::isfinite(s) || s <= 1.0e-8)
                    return false;
                w = (m02 - m20) / s;
                x = (m01 + m10) / s;
                y = 0.25 * s;
                z = (m12 + m21) / s;
            }
            else
            {
                const double s = std::sqrt(1.0 + m22 - m00 - m11) * 2.0;
                if (!std::isfinite(s) || s <= 1.0e-8)
                    return false;
                w = (m10 - m01) / s;
                x = (m02 + m20) / s;
                y = (m12 + m21) / s;
                z = 0.25 * s;
            }

            const double quatLen = std::sqrt(w * w + x * x + y * y + z * z);
            if (!std::isfinite(quatLen) || quatLen <= 1.0e-8)
                return false;

            outOrientation.w = static_cast<float>(w / quatLen);
            outOrientation.x = static_cast<float>(x / quatLen);
            outOrientation.y = static_cast<float>(y / quatLen);
            outOrientation.z = static_cast<float>(z / quatLen);
            return std::isfinite(outOrientation.w) &&
                   std::isfinite(outOrientation.x) &&
                   std::isfinite(outOrientation.y) &&
                   std::isfinite(outOrientation.z);
        }

        bool TryGetChunkProxyPosition(const uint8_t* objectBytes, float& outX, float& outY, float& outZ)
        {
            if (!objectBytes)
                return false;

            __try
            {
                const auto* transform = reinterpret_cast<const LegacyMat3*>(objectBytes + 0x20);
                const double x = transform->posit_x;
                const double y = transform->posit_y;
                const double z = transform->posit_z;
                if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
                    return false;

                outX = static_cast<float>(x);
                outY = static_cast<float>(y);
                outZ = static_cast<float>(z);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryGetChunkProxyTransform(const uint8_t* objectBytes, ChunkProxyTransform& outTransform)
        {
            outTransform = {};
            if (!objectBytes)
                return false;

            __try
            {
                const auto* transform = reinterpret_cast<const LegacyMat3*>(objectBytes + 0x20);
                const double x = transform->posit_x;
                const double y = transform->posit_y;
                const double z = transform->posit_z;
                if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
                    return false;

                outTransform.x = static_cast<float>(x);
                outTransform.y = static_cast<float>(y);
                outTransform.z = static_cast<float>(z);
                if (!TryBuildOgreQuaternionFromLegacyTransform(*transform, outTransform.orientation))
                    outTransform.orientation = { 1.0f, 0.0f, 0.0f, 0.0f };
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outTransform = {};
                return false;
            }
        }

        static bool TryResolveChunkProxyPositionFromCandidates(
            const uint8_t* primaryObjectBytes,
            const ChunkResolvedBindingEntry* binding,
            const ChunkBridgeSnapshot* bridgeSnapshot,
            float& outX,
            float& outY,
            float& outZ,
            const void** outResolvedObject = nullptr)
        {
            if (outResolvedObject)
                *outResolvedObject = nullptr;

            const void* candidates[] =
            {
                primaryObjectBytes,
                reinterpret_cast<const void*>(static_cast<uintptr_t>(binding ? binding->sourceRootObjectPtr : 0)),
                reinterpret_cast<const void*>(static_cast<uintptr_t>(binding ? binding->sourceOwnerEntityPtr : 0)),
                reinterpret_cast<const void*>(static_cast<uintptr_t>(binding ? binding->sourceOwnerObjPtr : 0)),
                reinterpret_cast<const void*>(static_cast<uintptr_t>(binding ? binding->sourceGameObjectPtr : 0)),
                reinterpret_cast<const void*>(static_cast<uintptr_t>(binding ? binding->sourceRootGameObjectPtr : 0)),
                bridgeSnapshot ? bridgeSnapshot->ownerEntity : nullptr,
                bridgeSnapshot ? bridgeSnapshot->ownerObj : nullptr,
                bridgeSnapshot ? bridgeSnapshot->gameObject : nullptr,
            };

            std::unordered_set<uintptr_t> seen;
            seen.reserve(std::size(candidates));
            for (const void* candidate : candidates)
            {
                const uintptr_t key = reinterpret_cast<uintptr_t>(candidate);
                if (!candidate || !seen.insert(key).second)
                    continue;

                if (TryGetChunkProxyPosition(
                        reinterpret_cast<const uint8_t*>(candidate),
                        outX,
                        outY,
                        outZ))
                {
                    if (outResolvedObject)
                        *outResolvedObject = candidate;
                    return true;
                }
            }

            return false;
        }

        static bool TryResolveChunkProxyTransformForSlot(
            const ChunkProxySlot& slot,
            ChunkProxyTransform& outTransform,
            const void** outResolvedObject = nullptr)
        {
            if (outResolvedObject)
                *outResolvedObject = nullptr;

            const void* candidates[] =
            {
                slot.objectBytes,
                slot.sourceRootObject,
                slot.ownerEntity,
                slot.ownerObj,
                slot.sourceGameObject,
                slot.sourceRootGameObject,
            };

            std::unordered_set<uintptr_t> seen;
            seen.reserve(std::size(candidates));
            for (const void* candidate : candidates)
            {
                const uintptr_t key = reinterpret_cast<uintptr_t>(candidate);
                if (!candidate || !seen.insert(key).second)
                    continue;

                if (TryGetChunkProxyTransform(
                        reinterpret_cast<const uint8_t*>(candidate),
                        outTransform))
                {
                    if (outResolvedObject)
                        *outResolvedObject = candidate;
                    return true;
                }
            }

            outTransform = {};
            return false;
        }

        static bool TryBuildChunkProxyAnchoredEntryTransform(
            const ChunkProxySlot& slot,
            const ChunkProxyTransform* baseTransform,
            ChunkProxyTransform& outTransform,
            const void** outAnchorObject = nullptr)
        {
            const void* candidates[] =
            {
                slot.sourceRootGameObject,
                slot.sourceGameObject,
                slot.ownerObj,
                slot.ownerEntity,
                slot.sourceRootObject,
            };

            std::unordered_set<uintptr_t> seen;
            seen.reserve(std::size(candidates));

            bool found = false;
            double bestScore = 0.0;
            ChunkProxyTransform bestTransform = {};
            const void* bestAnchorObject = nullptr;
            for (const void* candidate : candidates)
            {
                const uintptr_t key = reinterpret_cast<uintptr_t>(candidate);
                if (!candidate || !seen.insert(key).second)
                    continue;

                ChunkProxyTransform anchorTransform = {};
                if (!TryGetChunkProxyTransform(
                        reinterpret_cast<const uint8_t*>(candidate),
                        anchorTransform))
                {
                    continue;
                }

                ChunkProxyTransform candidateTransform = baseTransform ? *baseTransform : anchorTransform;
                candidateTransform.x = anchorTransform.x + slot.positionX;
                candidateTransform.y = anchorTransform.y + slot.positionY;
                candidateTransform.z = anchorTransform.z + slot.positionZ;

                if (!baseTransform)
                {
                    candidateTransform.orientation = anchorTransform.orientation;
                    candidateTransform.scale = anchorTransform.scale;
                }

                double candidateScore = 0.0;
                if (baseTransform)
                {
                    const double dx = static_cast<double>(candidateTransform.x) - static_cast<double>(baseTransform->x);
                    const double dy = static_cast<double>(candidateTransform.y) - static_cast<double>(baseTransform->y);
                    const double dz = static_cast<double>(candidateTransform.z) - static_cast<double>(baseTransform->z);
                    candidateScore = std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                }

                if (!found || candidateScore < bestScore)
                {
                    bestScore = candidateScore;
                    bestTransform = candidateTransform;
                    bestAnchorObject = candidate;
                    found = true;
                    if (!baseTransform)
                        break;
                }
            }

            if (!found)
            {
                seen.clear();
                for (const void* candidate : candidates)
                {
                    const uintptr_t key = reinterpret_cast<uintptr_t>(candidate);
                    if (!candidate || !seen.insert(key).second)
                        continue;

                    float anchorX = 0.0f;
                    float anchorY = 0.0f;
                    float anchorZ = 0.0f;
                    if (!TryGetChunkProxyPosition(
                            reinterpret_cast<const uint8_t*>(candidate),
                            anchorX,
                            anchorY,
                            anchorZ))
                    {
                        continue;
                    }

                    ChunkProxyTransform candidateTransform = {};
                    if (baseTransform)
                    {
                        candidateTransform = *baseTransform;
                    }
                    else
                    {
                        candidateTransform.orientation = { 1.0f, 0.0f, 0.0f, 0.0f };
                        candidateTransform.scale = { 1.0f, 1.0f, 1.0f };
                    }

                    candidateTransform.x = anchorX + slot.positionX;
                    candidateTransform.y = anchorY + slot.positionY;
                    candidateTransform.z = anchorZ + slot.positionZ;

                    double candidateScore = 0.0;
                    if (baseTransform)
                    {
                        const double dx = static_cast<double>(candidateTransform.x) - static_cast<double>(baseTransform->x);
                        const double dy = static_cast<double>(candidateTransform.y) - static_cast<double>(baseTransform->y);
                        const double dz = static_cast<double>(candidateTransform.z) - static_cast<double>(baseTransform->z);
                        candidateScore = std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                    }

                    if (!found || candidateScore < bestScore)
                    {
                        bestScore = candidateScore;
                        bestTransform = candidateTransform;
                        bestAnchorObject = candidate;
                        found = true;
                        if (!baseTransform)
                            break;
                    }
                }
            }

            if (!found)
                return false;

            outTransform = bestTransform;
            if (outAnchorObject)
                *outAnchorObject = bestAnchorObject;
            return true;
        }

        static bool ShouldPreferChunkEntryPosition(
            const ChunkProxySlot& slot,
            const ChunkProxyTransform& transform)
        {
            if (!slot.useEntryPosition)
                return false;

            const double dx = static_cast<double>(transform.x) - static_cast<double>(slot.positionX);
            const double dy = static_cast<double>(transform.y) - static_cast<double>(slot.positionY);
            const double dz = static_cast<double>(transform.z) - static_cast<double>(slot.positionZ);
            const double distance = std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
            return std::isfinite(distance) &&
                   distance > static_cast<double>(kChunkProxyEntryPositionTolerance);
        }

        static double ComputeChunkProxyPositionDistance(
            float ax,
            float ay,
            float az,
            float bx,
            float by,
            float bz)
        {
            const double dx = static_cast<double>(ax) - static_cast<double>(bx);
            const double dy = static_cast<double>(ay) - static_cast<double>(by);
            const double dz = static_cast<double>(az) - static_cast<double>(bz);
            return std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
        }

        static bool TryPromoteChunkProxyLocalTransformToAnchoredWorld(
            const ChunkProxySlot& slot,
            const ChunkProxyTransform& resolvedTransform,
            const void* resolvedTransformObject,
            ChunkProxyTransform& outTransform,
            const void** outAnchorObject = nullptr)
        {
            if (outAnchorObject)
                *outAnchorObject = nullptr;

            if (!slot.useEntryPosition ||
                resolvedTransformObject == nullptr ||
                resolvedTransformObject != slot.objectBytes)
            {
                return false;
            }

            const double rawEntryDistance = ComputeChunkProxyPositionDistance(
                resolvedTransform.x,
                resolvedTransform.y,
                resolvedTransform.z,
                slot.positionX,
                slot.positionY,
                slot.positionZ);
            const double rawMagnitude = ComputeChunkProxyPositionDistance(
                resolvedTransform.x,
                resolvedTransform.y,
                resolvedTransform.z,
                0.0f,
                0.0f,
                0.0f);
            const bool localLike =
                (std::isfinite(rawEntryDistance) &&
                 rawEntryDistance <= static_cast<double>(kChunkProxyLocalTransformTolerance)) ||
                (std::isfinite(rawMagnitude) &&
                 rawMagnitude <= static_cast<double>(kChunkProxyLocalTransformTolerance));
            if (!localLike)
                return false;

            ChunkProxyTransform anchoredTransform = {};
            const void* anchoredObject = nullptr;
            if (!TryBuildChunkProxyAnchoredEntryTransform(
                    slot,
                    &resolvedTransform,
                    anchoredTransform,
                    &anchoredObject))
            {
                return false;
            }

            const double anchorDelta = ComputeChunkProxyPositionDistance(
                anchoredTransform.x,
                anchoredTransform.y,
                anchoredTransform.z,
                resolvedTransform.x,
                resolvedTransform.y,
                resolvedTransform.z);
            if (!std::isfinite(anchorDelta) ||
                anchorDelta < static_cast<double>(kChunkProxyAnchoredTransformAdoptDistance))
            {
                return false;
            }

            outTransform = anchoredTransform;
            if (outAnchorObject)
                *outAnchorObject = anchoredObject;
            return true;
        }

        void* GetOgreSceneManagerRuntime()
        {
            __try
            {
                auto* const renderGlobalsSlot =
                    reinterpret_cast<uint8_t**>(EngineGlobals::RenderGlobals());
                if (!renderGlobalsSlot)
                    return nullptr;
                auto* sceneManagerStructure = *renderGlobalsSlot;
                if (!sceneManagerStructure)
                    return nullptr;

                return *reinterpret_cast<void**>(sceneManagerStructure + kOgreSceneManagerOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        static bool TrySetChunkProxyBillboardPosition(
            void* billboard,
            FnOgreSetBillboardPosition setPosition,
            float x,
            float y,
            float z);

        static void HideChunkProxyBillboard(void* billboard)
        {
            static FnOgreSetBillboardPosition setPosition =
                ResolveOgreProc<FnOgreSetBillboardPosition>("?setPosition@Billboard@Ogre@@QAEXMMM@Z");
            if (!billboard || !setPosition)
                return;

            TrySetChunkProxyBillboardPosition(billboard, setPosition, 0.0f, kChunkProxyHiddenY, 0.0f);
        }

        // --- Ogre call guards ------------------------------------------------
        //
        // Every Ogre call in the chunk proxy runs under __try, because the
        // object it is handed may have been destroyed by a scene teardown the
        // shim did not observe, and only SEH stops the access violation that
        // follows. But Ogre also throws C++ exceptions as a matter of course:
        // a missing mesh or material, a name collision in createEntity, an
        // out-of-range getSubEntity, a codec error. An
        // __except(EXCEPTION_EXECUTE_HANDLER) caught those too, as the MSVC
        // C++ exception code, and executing an SEH handler for a C++ throw
        // skips every destructor between the throw and that frame: OgreMain's
        // mutex guards stayed held, a half-registered object stayed in the
        // movable-object map, the exception object leaked. So each guard now
        // has two halves. The C++ half (CatchOgreThrow) runs the call inside
        // try/catch, which lets the throw unwind OgreMain's frames before it
        // is caught. The SEH half keeps only the hardware faults and hands a
        // C++ exception back to the unwinder (OgreCallSehFilter), so it can
        // never again be swallowed on this path.
        constexpr unsigned long kMsvcCppExceptionCode = 0xE06D7363UL;

        static int OgreCallSehFilter(unsigned long code)
        {
            return code == kMsvcCppExceptionCode ? EXCEPTION_CONTINUE_SEARCH : EXCEPTION_EXECUTE_HANDLER;
        }

        // Runs `call` and reports a C++ throw as false. The lambda is its own
        // function, so the caller's __try frame stays free of objects that
        // need unwinding (C2712). The log budget is per site and small: these
        // guards sit on the per-slot render tick.
        template <typename Call>
        static bool CatchOgreThrow(const char* site, Call&& call)
        {
            try
            {
                call();
                return true;
            }
            catch (...)
            {
                static volatile LONG s_budget = 8;
                if (InterlockedDecrement(&s_budget) >= 0)
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Ogre threw in %hs; call abandoned\n", site);
                return false;
            }
        }

        static bool TryCreateChunkProxyBillboardSet(
            void* sceneManager,
            FnOgreGetRootSceneNode getRootSceneNode,
            FnOgreCreateBillboardSet createBillboardSet,
            void*& outRootNode,
            void*& outBillboardSet)
        {
            outRootNode = nullptr;
            outBillboardSet = nullptr;
            if (!sceneManager || !getRootSceneNode || !createBillboardSet)
                return false;

            __try
            {
                if (!CatchOgreThrow("createBillboardSet", [&] {
                        outRootNode = getRootSceneNode(sceneManager);
                        if (outRootNode)
                            outBillboardSet = createBillboardSet(sceneManager, g_ChunkProxyCapacity);
                    }))
                {
                    outRootNode = nullptr;
                    outBillboardSet = nullptr;
                }
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                outRootNode = nullptr;
                outBillboardSet = nullptr;
            }

            return outRootNode != nullptr && outBillboardSet != nullptr;
        }

        static bool TrySetupChunkProxyBillboardSet(
            void* rootNode,
            void* billboardSet,
            FnOgreAttachObject attachObject,
            FnOgreSetBillboardsInWorldSpace setBillboardsInWorldSpace,
            FnOgreSetDefaultDimensions setDefaultDimensions)
        {
            if (!rootNode || !billboardSet || !attachObject || !setBillboardsInWorldSpace || !setDefaultDimensions)
                return false;

            __try
            {
                return CatchOgreThrow("setupBillboardSet", [&] {
                    setBillboardsInWorldSpace(billboardSet, true);
                    setDefaultDimensions(billboardSet, g_ChunkProxyDebugSize, g_ChunkProxyDebugSize);
                    attachObject(rootNode, billboardSet);
                });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        static void* TryCreateChunkProxyBillboard(void* billboardSet, FnOgreCreateBillboard createBillboard, const OgreColourValue& color)
        {
            if (!billboardSet || !createBillboard)
                return nullptr;

            void* billboard = nullptr;
            __try
            {
                if (!CatchOgreThrow("createBillboard", [&] {
                        billboard = createBillboard(billboardSet, 0.0f, kChunkProxyHiddenY, 0.0f, color);
                    }))
                {
                    billboard = nullptr;
                }
                return billboard;
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return nullptr;
            }
        }

        static bool TrySetChunkProxyBillboardPosition(
            void* billboard,
            FnOgreSetBillboardPosition setPosition,
            float x,
            float y,
            float z)
        {
            if (!billboard || !setPosition)
                return false;

            __try
            {
                return CatchOgreThrow("setBillboardPosition", [&] { setPosition(billboard, x, y, z); });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        static void TryHideChunkProxyEntity(void* entity, FnOgreSetVisible setVisible)
        {
            if (!entity || !setVisible)
                return;

            __try
            {
                CatchOgreThrow("hideEntity", [&] { setVisible(entity, false); });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
            }
        }

        static void TryResetChunkProxyNode(
            void* sceneNode,
            FnOgreSetNodePosition setPosition,
            FnOgreSetNodeOrientation setOrientation)
        {
            if (!sceneNode || !setPosition)
                return;

            __try
            {
                CatchOgreThrow("resetNode", [&] {
                    setPosition(sceneNode, 0.0f, kChunkProxyHiddenY, 0.0f);
                    if (setOrientation)
                        setOrientation(sceneNode, 1.0f, 0.0f, 0.0f, 0.0f);
                });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
            }
        }

        static void* CreateChunkMeshProxyEntity(
            void* sceneManager,
            FnOgreCreateEntity createEntity,
            const char* meshName)
        {
            if (!sceneManager || !createEntity || !meshName || !*meshName)
                return nullptr;

            return createEntity(sceneManager, std::string(meshName));
        }

        static bool TryCreateChunkMeshProxyObjects(
            void* rootNode,
            void* sceneManager,
            FnOgreCreateChildSceneNode createChildSceneNode,
            FnOgreCreateEntity createEntity,
            FnOgreAttachObject attachObject,
            FnOgreSetVisible setVisible,
            const char* meshName,
            void*& outSceneNode,
            void*& outEntity)
        {
            outSceneNode = nullptr;
            outEntity = nullptr;
            if (!rootNode || !sceneManager || !createChildSceneNode || !createEntity || !attachObject || !setVisible)
                return false;

            const OgreVector3 zeroPos = { 0.0f, kChunkProxyHiddenY, 0.0f };
            const OgreQuaternion identity = { 1.0f, 0.0f, 0.0f, 0.0f };
            __try
            {
                if (!CatchOgreThrow("createMeshProxy", [&] {
                        outSceneNode = createChildSceneNode(rootNode, zeroPos, identity);
                        if (outSceneNode)
                        {
                            outEntity = CreateChunkMeshProxyEntity(sceneManager, createEntity, meshName);
                            if (outEntity)
                            {
                                attachObject(outSceneNode, outEntity);
                                setVisible(outEntity, false);
                            }
                        }
                    }))
                {
                    outSceneNode = nullptr;
                    outEntity = nullptr;
                }
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                outSceneNode = nullptr;
                outEntity = nullptr;
            }

            return outSceneNode != nullptr && outEntity != nullptr;
        }

        static void* TryGetChunkMeshProxyRootNode(
            void* sceneManager,
            FnOgreGetRootSceneNode getRootSceneNode)
        {
            if (!sceneManager || !getRootSceneNode)
                return nullptr;

            void* rootNode = nullptr;
            __try
            {
                if (!CatchOgreThrow("rootSceneNode", [&] { rootNode = getRootSceneNode(sceneManager); }))
                    rootNode = nullptr;
                return rootNode;
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return nullptr;
            }
        }

        static bool EnsureChunkPayloadResourceLocations()
        {
            if (!g_EnableChunkMeshProxy)
                return false;

            if (g_ChunkPayloadResourceLocationsReady)
                return true;

            if (!g_ChunkPayloadResourceLocationsAttempted)
            {
                RefreshChunkPayloadResourceDirectories();
                g_ChunkPayloadResourceLocationsAttempted = true;
            }

            if (g_ChunkPayloadResourceDirectories.empty())
            {
                if (!g_ChunkPayloadResourceLocationsFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh",
                        L"[CHUNKMESH] No chunk payload resource directories found; stockRoot=%hs modRelative=%hs\n",
                        GetChunkPayloadStockResourceDirectory().string().c_str(),
                        kChunkPayloadModRelativeDirName);
                    g_ChunkPayloadResourceLocationsFailureLogged = true;
                }
                return false;
            }

            static FnOgreGetResourceGroupManager getResourceGroupManager =
                ResolveOgreProc<FnOgreGetResourceGroupManager>("?getSingletonPtr@ResourceGroupManager@Ogre@@SAPAV12@XZ");
            static FnOgreResourceGroupExists resourceGroupExists =
                ResolveOgreProc<FnOgreResourceGroupExists>("?resourceGroupExists@ResourceGroupManager@Ogre@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            static FnOgreCreateResourceGroup createResourceGroup =
                ResolveOgreProc<FnOgreCreateResourceGroup>("?createResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
            static FnOgreAddResourceLocation addResourceLocation =
                ResolveOgreProc<FnOgreAddResourceLocation>("?addResourceLocation@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00_N1@Z");
            static FnOgreInitialiseResourceGroup initialiseResourceGroup =
                ResolveOgreProc<FnOgreInitialiseResourceGroup>("?initialiseResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

            if (!getResourceGroupManager || !resourceGroupExists || !createResourceGroup ||
                !addResourceLocation || !initialiseResourceGroup)
            {
                if (!g_ChunkPayloadResourceLocationsFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Missing Ogre resource manager symbols; cannot register chunk payload roots\n");
                    g_ChunkPayloadResourceLocationsFailureLogged = true;
                }
                return false;
            }

            void* resourceManager = getResourceGroupManager();
            if (!resourceManager)
            {
                if (!g_ChunkPayloadResourceLocationsFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Ogre resource manager unavailable; cannot register chunk payload roots yet\n");
                    g_ChunkPayloadResourceLocationsFailureLogged = true;
                }
                return false;
            }

            const std::string groupName = kChunkPayloadResourceRootName;
            const std::string locationType = kChunkPayloadResourceLocationType;
            try
            {
                if (!resourceGroupExists(resourceManager, groupName))
                    createResourceGroup(resourceManager, groupName, false);

                for (const std::filesystem::path& resourceRoot : g_ChunkPayloadResourceDirectories)
                {
                    addResourceLocation(resourceManager, resourceRoot.string(), locationType, groupName, true, true);
                    if (!g_ChunkPayloadResourceLocationsLogged)
                    {
                        LogChunkDiagnostic("chunkmesh",
                            L"[CHUNKMESH] Registered chunk payload resource root group=%hs path=%hs\n",
                            groupName.c_str(),
                            resourceRoot.string().c_str());
                    }
                }

                initialiseResourceGroup(resourceManager, groupName);
            }
            catch (...)
            {
                if (!g_ChunkPayloadResourceLocationsFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Exception while registering chunk payload resource roots\n");
                    g_ChunkPayloadResourceLocationsFailureLogged = true;
                }
                return false;
            }

            g_ChunkPayloadResourceLocationsReady = true;
            g_ChunkPayloadResourceLocationsLogged = true;
            g_ChunkPayloadResourceLocationsFailureLogged = false;
            return true;
        }

        static bool TryUpdateChunkMeshProxyTransform(
            void* sceneNode,
            void* entity,
            FnOgreSetNodePosition setNodePosition,
            FnOgreSetNodeOrientation setNodeOrientation,
            FnOgreSetVisible setVisible,
            const ChunkProxyTransform& transform)
        {
            if (!sceneNode || !entity || !setNodePosition || !setVisible)
                return false;

            __try
            {
                return CatchOgreThrow("updateMeshProxyTransform", [&] {
                    setNodePosition(sceneNode, transform.x, transform.y, transform.z);
                    if (setNodeOrientation)
                    {
                        setNodeOrientation(
                            sceneNode,
                            transform.orientation.w,
                            transform.orientation.x,
                            transform.orientation.y,
                            transform.orientation.z);
                    }
                    setVisible(entity, true);
                });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        static void HideChunkProxyMesh(ChunkProxySlot& slot)
        {
            static FnOgreSetVisible setVisible =
                ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");
            static FnOgreSetNodePosition setPosition =
                ResolveOgreProc<FnOgreSetNodePosition>("?setPosition@Node@Ogre@@UAEXMMM@Z");
            static FnOgreSetNodeOrientation setOrientation =
                ResolveOgreProc<FnOgreSetNodeOrientation>("?setOrientation@Node@Ogre@@UAEXMMMM@Z");

            TryHideChunkProxyEntity(slot.entity, setVisible);
            TryResetChunkProxyNode(slot.sceneNode, setPosition, setOrientation);
        }

        static bool EnsureChunkMeshProxySlot(ChunkProxySlot& slot)
        {
            if (!g_EnableChunkMeshProxy)
                return false;
            // Second gate: even if config said enabled at boot, re-check
            // centralized asset capability on every creation attempt. This
            // covers partial packages where the sentinel says "detected" but
            // the specific mesh file for this slot is absent, and ensures we
            // never create an Ogre Entity with a missing mesh name.
            if (!Assets::IsAssetFeatureAvailable(Assets::AssetFeature::DestructionChunks))
                return false;
            // Per-mesh verification: even when the global capability is true
            // (some payloads exist), the particular requested mesh may be absent
            // in a partial pack. The resolver (TryResolveChunkPayloadMeshResource)
            // already verified before filling proofMeshName, so an empty
            // proofMeshName means "no file for this mesh" and must not allocate.
            // Trace for partial-pack proof (see tests/openshim_assets_tests):
            //   partial pack → capability true → requested mesh absent → resolver false →
            //   proofMeshName empty → NO SceneNode → NO Entity → NO createEntity("") → no retry storm
            {
                const char* meshName = GetChunkPayloadMeshName(slot);
                if (!meshName || !*meshName)
                    return false;
            }

            if (slot.sceneNode && slot.entity)
                return true;

            // Back off only after a failed attempt (Ogre not ready yet). Arming
            // the throttle on success too would let just one fragment per second
            // acquire an entity, while chunk entries expire within 400ms.
            const DWORD now = GetTickCount();
            if (g_ChunkMeshProxyLastRetryTick != 0 &&
                static_cast<DWORD>(now - g_ChunkMeshProxyLastRetryTick) < kChunkProxyRetryDelayMs)
            {
                return false;
            }

            static FnOgreGetRootSceneNode getRootSceneNode =
                ResolveOgreProc<FnOgreGetRootSceneNode>("?getRootSceneNode@SceneManager@Ogre@@UAEPAVSceneNode@2@XZ");
            static FnOgreCreateChildSceneNode createChildSceneNode =
                ResolveOgreProc<FnOgreCreateChildSceneNode>("?createChildSceneNode@SceneNode@Ogre@@UAEPAV12@ABVVector3@2@ABVQuaternion@2@@Z");
            static FnOgreCreateEntity createEntity =
                ResolveOgreProc<FnOgreCreateEntity>("?createEntity@SceneManager@Ogre@@UAEPAVEntity@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            static FnOgreAttachObject attachObject =
                ResolveOgreProc<FnOgreAttachObject>("?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
            static FnOgreSetVisible setVisible =
                ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");

            if (!getRootSceneNode || !createChildSceneNode || !createEntity || !attachObject || !setVisible)
            {
                if (!g_ChunkMeshProxyFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Missing Ogre entity symbols; mesh proxy disabled for now\n");
                    g_ChunkMeshProxyFailureLogged = true;
                }
                g_ChunkMeshProxyLastRetryTick = now;
                return false;
            }

            void* sceneManager = GetOgreSceneManagerRuntime();
            if (!sceneManager)
            {
                if (!g_ChunkMeshProxyWaitLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Scene manager unavailable; waiting to initialize chunk mesh proxy\n");
                    g_ChunkMeshProxyWaitLogged = true;
                }
                g_ChunkMeshProxyLastRetryTick = now;
                return false;
            }

            if (!EnsureChunkPayloadResourceLocations())
            {
                g_ChunkMeshProxyLastRetryTick = now;
                return false;
            }

            void* rootNode = TryGetChunkMeshProxyRootNode(sceneManager, getRootSceneNode);
            if (!rootNode)
            {
                if (!g_ChunkMeshProxyFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Root scene node unavailable sceneManager=0x%08X\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sceneManager)));
                    g_ChunkMeshProxyFailureLogged = true;
                }
                g_ChunkMeshProxyLastRetryTick = now;
                return false;
            }

            void* sceneNode = nullptr;
            void* entity = nullptr;
            const char* const meshName = GetChunkPayloadMeshName(slot);
            if (!TryCreateChunkMeshProxyObjects(
                    rootNode,
                    sceneManager,
                    createChildSceneNode,
                    createEntity,
                    attachObject,
                    setVisible,
                    meshName,
                    sceneNode,
                    entity))
            {
                if (!g_ChunkMeshProxyFailureLogged)
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Entity creation failed mesh=%hs node=0x%08X entity=0x%08X\n",
                        meshName,
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sceneNode)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entity)));
                    g_ChunkMeshProxyFailureLogged = true;
                }
                g_ChunkMeshProxyLastRetryTick = now;
                return false;
            }

            slot.sceneNode = sceneNode;
            slot.entity = entity;
            slot.sceneManager = sceneManager;
            g_ChunkMeshProxyLastRetryTick = 0;
            g_ChunkMeshProxyFailureLogged = false;
            g_ChunkMeshProxyWaitLogged = false;
            if (!g_ChunkMeshProxyInitLogged)
            {
                LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Initialized chunk mesh proxy mesh=%hs\n", meshName);
                g_ChunkMeshProxyInitLogged = true;
            }
            return true;
        }

        static bool EnsureChunkProxyResources()
        {
            if (!g_EnableChunkProxyDebug)
                return false;

            if (g_ChunkProxyBillboardSet)
                return true;

            const DWORD now = GetTickCount();
            if (g_ChunkProxyLastRetryTick != 0 &&
                static_cast<DWORD>(now - g_ChunkProxyLastRetryTick) < kChunkProxyRetryDelayMs)
            {
                return false;
            }
            g_ChunkProxyLastRetryTick = now;

            static FnOgreGetRootSceneNode getRootSceneNode =
                ResolveOgreProc<FnOgreGetRootSceneNode>("?getRootSceneNode@SceneManager@Ogre@@UAEPAVSceneNode@2@XZ");
            static FnOgreCreateBillboardSet createBillboardSet =
                ResolveOgreProc<FnOgreCreateBillboardSet>("?createBillboardSet@SceneManager@Ogre@@UAEPAVBillboardSet@2@I@Z");
            static FnOgreAttachObject attachObject =
                ResolveOgreProc<FnOgreAttachObject>("?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
            static FnOgreSetBillboardsInWorldSpace setBillboardsInWorldSpace =
                ResolveOgreProc<FnOgreSetBillboardsInWorldSpace>("?setBillboardsInWorldSpace@BillboardSet@Ogre@@UAEX_N@Z");
            static FnOgreSetDefaultDimensions setDefaultDimensions =
                ResolveOgreProc<FnOgreSetDefaultDimensions>("?setDefaultDimensions@BillboardSet@Ogre@@UAEXMM@Z");
            static FnOgreCreateBillboard createBillboard =
                ResolveOgreProc<FnOgreCreateBillboard>("?createBillboard@BillboardSet@Ogre@@QAEPAVBillboard@2@MMMABVColourValue@2@@Z");

            if (!getRootSceneNode || !attachObject || !setBillboardsInWorldSpace ||
                !setDefaultDimensions || !createBillboard)
            {
                if (!g_ChunkProxyFailureLogged)
                {
                    LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] Missing Ogre billboard symbols; proxy debug disabled for now\n");
                    g_ChunkProxyFailureLogged = true;
                }
                return false;
            }

            void* sceneManager = GetOgreSceneManagerRuntime();
            if (!sceneManager)
            {
                if (!g_ChunkProxyWaitLogged)
                {
                    LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] Scene manager unavailable; waiting to initialize chunk proxy debug\n");
                    g_ChunkProxyWaitLogged = true;
                }
                return false;
            }

            void* rootNode = nullptr;
            void* billboardSet = nullptr;
            if (!TryCreateChunkProxyBillboardSet(
                    sceneManager,
                    getRootSceneNode,
                    createBillboardSet,
                    rootNode,
                    billboardSet))
            {
                if (!g_ChunkProxyFailureLogged)
                {
                    LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] BillboardSet creation failed sceneManager=0x%08X root=0x%08X set=0x%08X\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sceneManager)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(rootNode)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(billboardSet)));
                    g_ChunkProxyFailureLogged = true;
                }
                return false;
            }

            if (!TrySetupChunkProxyBillboardSet(
                    rootNode,
                    billboardSet,
                    attachObject,
                    setBillboardsInWorldSpace,
                    setDefaultDimensions))
            {
                if (!g_ChunkProxyFailureLogged)
                {
                    LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] BillboardSet setup fault set=0x%08X code=0x%08X\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(billboardSet)),
                        0u);
                    g_ChunkProxyFailureLogged = true;
                }
                return false;
            }

            if (g_ChunkProxySlots.size() != g_ChunkProxyCapacity)
                g_ChunkProxySlots.resize(g_ChunkProxyCapacity);
            const OgreColourValue color = { 1.0f, 0.35f, 0.05f, 0.9f };
            for (uint32_t index = 0; index < g_ChunkProxyCapacity; ++index)
            {
                void* billboard = TryCreateChunkProxyBillboard(billboardSet, createBillboard, color);
                g_ChunkProxySlots[index].billboard = billboard;
                g_ChunkProxySlots[index].billboardAssigned = false;
                HideChunkProxyBillboard(billboard);
            }

            g_ChunkProxyBillboardSet = billboardSet;
            g_ChunkProxyFailureLogged = false;
            g_ChunkProxyWaitLogged = false;
            if (!g_ChunkProxyInitLogged)
            {
                LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] Initialized billboard debug set=0x%08X cap=%u size=%.2f\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(billboardSet)),
                    g_ChunkProxyCapacity,
                    g_ChunkProxyDebugSize);
                g_ChunkProxyInitLogged = true;
            }

            return true;
        }

        static void ReleaseChunkProxySlot(ChunkProxySlot& slot, const wchar_t* reason = nullptr)
        {
            if (slot.active && reason && AcquireChunkLogSlot())
            {
                LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] release obj=0x%08X billboard=0x%08X entity=0x%08X geom=0x%08X geomName=%hs geomKind=%hs reason=%ls\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.billboard)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.geomRef)),
                    GetChunkGeomNameForLog(slot.geomName),
                    ClassifyChunkGeomName(slot.geomName),
                    reason);
            }

            if (slot.billboardAssigned)
                HideChunkProxyBillboard(slot.billboard);
            if (slot.sceneNode || slot.entity || slot.meshAssigned)
                InvalidateChunkMeshProxySlot(slot);
            slot.objectBytes = nullptr;
            slot.geomRef = nullptr;
            slot.geomName[0] = '\0';
            slot.ownerEntity = nullptr;
            slot.ownerEntityBaseName[0] = '\0';
            slot.ownerOgreFilename[0] = '\0';
            slot.proofMeshName[0] = '\0';
            slot.positionX = 0.0f;
            slot.positionY = 0.0f;
            slot.positionZ = 0.0f;
            slot.useEntryPosition = false;
            slot.lastSeenTick = 0;
            slot.active = false;
            slot.billboardAssigned = false;
            slot.meshAssigned = false;
            slot.genericBatchKind = 0;
            slot.genericBatchTransformReady = false;
        }

        // Drops every Ogre reference a slot holds WITHOUT calling into Ogre.
        // Used when the referenced objects are already destroyed (or about to
        // be): scene teardown, or an access fault while touching the entity.
        static void ForgetChunkProxySlotOgreRefs(ChunkProxySlot& slot)
        {
            slot.billboard = nullptr;
            slot.billboardAssigned = false;
            slot.sceneNode = nullptr;
            slot.entity = nullptr;
            slot.meshAssigned = false;
            slot.sceneManager = nullptr;
            slot.objectBytes = nullptr;
            slot.geomRef = nullptr;
            slot.geomName[0] = '\0';
            slot.ownerEntity = nullptr;
            slot.ownerEntityBaseName[0] = '\0';
            slot.ownerOgreFilename[0] = '\0';
            slot.proofMeshName[0] = '\0';
            slot.sourceRootObject = nullptr;
            slot.ownerObj = nullptr;
            slot.sourceGameObject = nullptr;
            slot.sourceRootGameObject = nullptr;
            slot.useEntryPosition = false;
            slot.lastSeenTick = 0;
            slot.active = false;
            slot.genericBatchKind = 0;
            slot.genericBatchTransformReady = false;
        }

        // Save-load and mission teardown destroy the whole Ogre scene
        // (SceneManager::clearScene / destroyAllMovableObjects), taking our
        // proxy billboard set, scene nodes, and entities with it. Any later
        // touch of those pointers is a use-after-free: crash dump 35064 was
        // Entity::isVisible on a destroyed chunk entity while the loading
        // screen still rendered frames. Forget everything without calling
        // into Ogre; resources are lazily recreated on the next tick.
        void ForgetAllChunkProxySceneResources(const wchar_t* reason)
        {
            size_t forgotten = 0;
            for (ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (slot.active || slot.entity || slot.sceneNode || slot.billboard)
                    ++forgotten;
                ForgetChunkProxySlotOgreRefs(slot);
            }
            g_ChunkProxyBillboardSet = nullptr;
            g_GenericChunkBatchManualObject = nullptr;
            // The recorded visibility described the object just dropped.
            g_GenericChunkBatchVisible = false;
            g_GenericChunkBatchSceneNode = nullptr;
            // A destroyed scene invalidates the cached geometry too.
            g_GenericChunkBatchBuiltVersion =
                ChunkBatchInvalidation::kUnbuiltVersion;
            g_GenericChunkBatchBuiltMaterial.clear();
            g_GenericChunkBatchSceneManager = nullptr;
            g_GenericChunkBatchSectionCreated = false;

            if (forgotten > 0)
            {
                LogChunkDiagnostic(
                    "chunkproxy",
                    L"[CHUNKPROXY] scene teardown (%ls): forgot %zu slot(s) and the billboard set\n",
                    reason ? reason : L"<none>",
                    forgotten);
            }
        }

        static void LogChunkManualSubmitSkip(
            const ChunkProxySlot& slot,
            const wchar_t* reason,
            void* sceneManager,
            void* viewport,
            void* hintedCamera,
            void* resolvedCamera)
        {
            static volatile long s_ManualSubmitSkipBudget = 24;
            const long remaining = InterlockedDecrement(&s_ManualSubmitSkipBudget);
            if (remaining < 0)
                return;

            LogChunkDiagnostic(
                "chunkmesh",
                L"[CHUNKMESH] manual-submit-skip obj=0x%08X entity=0x%08X mesh=%hs reason=%ls sceneMgr=0x%08X viewport=0x%08X hintedCamera=0x%08X camera=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                GetChunkPayloadMeshName(slot),
                reason ? reason : L"<none>",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sceneManager)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(viewport)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(hintedCamera)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(resolvedCamera)));
        }

        static void* TryGetChunkProxyViewportCameraSafe(
            void* sceneManager,
            FnOgreGetCurrentViewport getCurrentViewport,
            FnOgreViewportGetCamera getViewportCamera,
            void** outViewport,
            void* fallbackCamera)
        {
            if (outViewport)
                *outViewport = nullptr;
            if (!sceneManager || !getCurrentViewport)
                return fallbackCamera;

            void* viewportCamera = nullptr;
            __try
            {
                if (!CatchOgreThrow("viewportCamera", [&] {
                        void* viewport = getCurrentViewport(sceneManager);
                        if (outViewport)
                            *outViewport = viewport;
                        if (viewport && getViewportCamera)
                            viewportCamera = getViewportCamera(viewport);
                    }))
                {
                    viewportCamera = nullptr;
                }
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                viewportCamera = nullptr;
            }

            return viewportCamera ? viewportCamera : fallbackCamera;
        }

        // A chunk mesh has a handful of sub-entities. A destroyed Entity whose
        // allocation has been recycled usually does not fault on this read --
        // it just returns whatever the reused memory holds. Freeze
        // C:\BZDumps\hang2_34268.dmp came back with 0x0086C62F (8,832,559)
        // here, and the caller then took one swallowed access violation per
        // iteration; SEH dispatch is a kernel transition, so a single stale
        // slot cost minutes of CPU per frame and read as a hang rather than a
        // crash. Treat an implausible count as proof the entity is stale.
        static constexpr uint32_t kChunkProxyMaxSubEntities = 32;

        static uint32_t TryGetChunkProxySubEntityCountSafe(
            void* entity,
            FnOgreGetNumSubEntities getNumSubEntities,
            bool* faulted = nullptr)
        {
            if (faulted)
                *faulted = false;
            if (!entity || !getNumSubEntities)
                return 0;

            uint32_t count = 0;
            __try
            {
                if (!CatchOgreThrow("numSubEntities", [&] { count = getNumSubEntities(entity); }))
                {
                    if (faulted)
                        *faulted = true;
                    return 0;
                }
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                if (faulted)
                    *faulted = true;
                return 0;
            }
            if (count > kChunkProxyMaxSubEntities)
            {
                if (faulted)
                    *faulted = true;
                return 0;
            }
            return count;
        }

        static void* TryGetChunkProxySubEntitySafe(
            void* entity,
            uint32_t index,
            FnOgreGetSubEntity getSubEntity)
        {
            if (!entity || !getSubEntity)
                return nullptr;

            void* subEntity = nullptr;
            __try
            {
                if (!CatchOgreThrow("subEntity", [&] { subEntity = getSubEntity(entity, index); }))
                    subEntity = nullptr;
                return subEntity;
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return nullptr;
            }
        }

        // The entity a slot references can be destroyed behind our back by a
        // scene teardown we did not observe (the teardown hooks cover the
        // known paths, these guards cover the unknown ones). On a fault the
        // caller must forget the slot's Ogre refs instead of releasing them
        // through Ogre calls.
        static bool TryNotifyChunkProxyCameraSafe(
            void* entity,
            void* camera,
            FnOgreMovableObjectNotifyCurrentCamera notifyCurrentCamera)
        {
            if (!entity || !camera || !notifyCurrentCamera)
                return false;

            __try
            {
                return CatchOgreThrow("notifyCurrentCamera", [&] { notifyCurrentCamera(entity, camera); });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        // Returns 1/0 for the entity's visibility, or -1 if reading it faulted.
        static int TryGetChunkProxyVisibleSafe(void* entity, FnOgreIsVisible isVisible)
        {
            if (!entity || !isVisible)
                return 1;

            int visible = -1;
            __try
            {
                if (!CatchOgreThrow("isVisible", [&] { visible = isVisible(entity) ? 1 : 0; }))
                    visible = -1;
                return visible;
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return -1;
            }
        }

        static bool TryUpdateChunkProxyRenderQueueSafe(
            void* entity,
            void* renderQueue,
            FnOgreEntityUpdateRenderQueue updateRenderQueue)
        {
            if (!entity || !renderQueue || !updateRenderQueue)
                return false;

            __try
            {
                return CatchOgreThrow("updateRenderQueue", [&] { updateRenderQueue(entity, renderQueue); });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        static bool IsLikelyLiveOgreObject(const void* object)
        {
            if (!object)
                return false;

            void* vtable = nullptr;
            __try
            {
                vtable = *reinterpret_cast<void* const*>(object);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }

            HMODULE ogreMain = GetModuleHandleA("OgreMain.dll");
            if (!vtable || !ogreMain)
                return false;

            MEMORY_BASIC_INFORMATION mbi = {};
            return VirtualQuery(vtable, &mbi, sizeof(mbi)) == sizeof(mbi) &&
                mbi.State == MEM_COMMIT &&
                mbi.Type == MEM_IMAGE &&
                mbi.AllocationBase == ogreMain;
        }

        static bool TryAddChunkProxyRenderableSafe(
            void* renderQueue,
            void* renderable,
            uint8_t groupId,
            uint16_t priority,
            FnOgreRenderQueueAddRenderablePriority addRenderablePriority)
        {
            // A freed SubEntity can remain in committed heap memory long enough
            // for Entity::getSubEntity to return it successfully. Validate its
            // vtable before Ogre dereferences it, then contain any access fault
            // from a teardown race we could not observe in advance.
            if (!renderQueue || !addRenderablePriority ||
                !IsLikelyLiveOgreObject(renderable))
            {
                return false;
            }

            __try
            {
                return CatchOgreThrow("addRenderable", [&] { addRenderablePriority(renderQueue, renderable, groupId, priority); });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        static uint8_t TryGetChunkProxyRenderQueueGroupSafe(
            void* entity,
            FnOgreGetRenderQueueGroup getRenderQueueGroup,
            bool* outFaulted = nullptr)
        {
            if (outFaulted)
                *outFaulted = false;
            if (!entity || !getRenderQueueGroup)
                return 50u;

            uint8_t group = 50u;
            __try
            {
                if (!CatchOgreThrow("renderQueueGroup", [&] { group = getRenderQueueGroup(entity); }))
                {
                    if (outFaulted)
                        *outFaulted = true;
                    return 50u;
                }
                return group;
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                if (outFaulted)
                    *outFaulted = true;
                return 50u;
            }
        }

        using FnOgreCameraGetDerivedPosition = const OgreVector3&(__thiscall*)(void*);

        static bool TryGetChunkProxyCameraPositionSafe(
            void* camera,
            FnOgreCameraGetDerivedPosition getCameraDerivedPosition,
            OgreVector3& outPos)
        {
            if (!camera || !getCameraDerivedPosition)
                return false;

            __try
            {
                return CatchOgreThrow("cameraPosition", [&] { outPos = getCameraDerivedPosition(camera); });
            }
            __except (OgreCallSehFilter(GetExceptionCode()))
            {
                return false;
            }
        }

        static bool TrySubmitChunkMeshProxyToCurrentRenderQueue(
            ChunkProxySlot& slot,
            void* currentCamera)
        {
            if (!slot.active || !slot.entity)
                return false;

            static FnOgreGetRenderQueue getRenderQueue =
                ResolveOgreProc<FnOgreGetRenderQueue>("?getRenderQueue@SceneManager@Ogre@@UAEPAVRenderQueue@2@XZ");
            static FnOgreMovableObjectNotifyCurrentCamera notifyCurrentCamera =
                nullptr;
            static FnOgreEntityUpdateRenderQueue updateRenderQueue =
                nullptr;
            static FnOgreRenderQueueAddRenderablePriority addRenderablePriority =
                ResolveOgreProcByOffset<FnOgreRenderQueueAddRenderablePriority>(0x00026850);
            static FnOgreGetCurrentViewport getCurrentViewport =
                ResolveOgreProc<FnOgreGetCurrentViewport>("?getCurrentViewport@SceneManager@Ogre@@QBEPAVViewport@2@XZ");
            static FnOgreViewportGetCamera getViewportCamera =
                ResolveOgreProc<FnOgreViewportGetCamera>("?getCamera@Viewport@Ogre@@QBEPAVCamera@2@XZ");
            static FnOgreIsVisible isVisible =
                ResolveOgreProcByOffset<FnOgreIsVisible>(0x0002CCCD);
            static FnOgreGetRenderQueueGroup getRenderQueueGroup =
                ResolveOgreProcByOffset<FnOgreGetRenderQueueGroup>(0x0001584D);
            static FnOgreGetNumSubEntities getNumSubEntities =
                ResolveOgreProc<FnOgreGetNumSubEntities>("?getNumSubEntities@Entity@Ogre@@QBEIXZ");
            static FnOgreGetSubEntity getSubEntity =
                ResolveOgreProc<FnOgreGetSubEntity>("?getSubEntity@Entity@Ogre@@QBEPAVSubEntity@2@I@Z");

            if (!notifyCurrentCamera)
            {
                notifyCurrentCamera = g_OgreFn_MovableObjectNotifyCurrentCamera
                    ? g_OgreFn_MovableObjectNotifyCurrentCamera
                    : ResolveOgreProc<FnOgreMovableObjectNotifyCurrentCamera>(
                        "?_notifyCurrentCamera@Entity@Ogre@@UAEXPAVCamera@2@@Z");
            }
            if (!updateRenderQueue)
            {
                updateRenderQueue = g_OgreFn_EntityUpdateRenderQueue
                    ? g_OgreFn_EntityUpdateRenderQueue
                    : ResolveOgreProc<FnOgreEntityUpdateRenderQueue>(
                        "?_updateRenderQueue@Entity@Ogre@@UAEXPAVRenderQueue@2@@Z");
            }

            void* sceneManager = slot.sceneManager ? slot.sceneManager : GetOgreSceneManagerRuntime();
            void* viewport = nullptr;
            void* resolvedCamera = TryGetChunkProxyViewportCameraSafe(
                sceneManager,
                getCurrentViewport,
                getViewportCamera,
                &viewport,
                currentCamera);

            if (!sceneManager)
            {
                LogChunkManualSubmitSkip(slot, L"scene-manager-null", sceneManager, viewport, currentCamera, resolvedCamera);
                return false;
            }
            if (!resolvedCamera)
            {
                LogChunkManualSubmitSkip(slot, L"camera-null", sceneManager, viewport, currentCamera, resolvedCamera);
                return false;
            }
            if (!getRenderQueue)
            {
                LogChunkManualSubmitSkip(slot, L"get-render-queue-missing", sceneManager, viewport, currentCamera, resolvedCamera);
                return false;
            }
            if (!notifyCurrentCamera || (!updateRenderQueue && !addRenderablePriority))
            {
                LogChunkManualSubmitSkip(slot, L"submit-procs-missing", sceneManager, viewport, currentCamera, resolvedCamera);
                return false;
            }

            void* renderQueue = getRenderQueue(sceneManager);
            if (!renderQueue)
            {
                LogChunkManualSubmitSkip(slot, L"render-queue-null", sceneManager, viewport, currentCamera, resolvedCamera);
                return false;
            }

            bool visibleNow = true;
            if (!TryNotifyChunkProxyCameraSafe(slot.entity, resolvedCamera, notifyCurrentCamera))
            {
                LogChunkManualSubmitSkip(slot, L"entity-fault-notify", sceneManager, viewport, currentCamera, resolvedCamera);
                ForgetChunkProxySlotOgreRefs(slot);
                return false;
            }
            if (slot.cameraNotifyCount < USHRT_MAX)
                ++slot.cameraNotifyCount;

            if (isVisible)
            {
                const int visibleProbe = TryGetChunkProxyVisibleSafe(slot.entity, isVisible);
                if (visibleProbe < 0)
                {
                    LogChunkManualSubmitSkip(slot, L"entity-fault-visible", sceneManager, viewport, currentCamera, resolvedCamera);
                    ForgetChunkProxySlotOgreRefs(slot);
                    return false;
                }
                visibleNow = visibleProbe != 0;
            }

            uint32_t directAddCount = 0;
            if (visibleNow && updateRenderQueue)
            {
                if (!TryUpdateChunkProxyRenderQueueSafe(slot.entity, renderQueue, updateRenderQueue))
                {
                    LogChunkManualSubmitSkip(slot, L"entity-fault-update-queue", sceneManager, viewport, currentCamera, resolvedCamera);
                    ForgetChunkProxySlotOgreRefs(slot);
                    return false;
                }
                if (slot.entityUpdateQueueCount < USHRT_MAX)
                    ++slot.entityUpdateQueueCount;
            }
            else if (visibleNow && addRenderablePriority && getNumSubEntities && getSubEntity)
            {
                bool groupFaulted = false;
                const uint8_t groupId =
                    TryGetChunkProxyRenderQueueGroupSafe(slot.entity, getRenderQueueGroup, &groupFaulted);
                if (groupFaulted)
                {
                    LogChunkManualSubmitSkip(slot, L"entity-fault-queue-group", sceneManager, viewport, currentCamera, resolvedCamera);
                    ForgetChunkProxySlotOgreRefs(slot);
                    return false;
                }
                bool countFaulted = false;
                const uint32_t subEntityCount = TryGetChunkProxySubEntityCountSafe(
                    slot.entity, getNumSubEntities, &countFaulted);
                if (countFaulted)
                {
                    LogChunkManualSubmitSkip(slot, L"entity-fault-sub-entity-count", sceneManager, viewport, currentCamera, resolvedCamera);
                    ForgetChunkProxySlotOgreRefs(slot);
                    return false;
                }

                for (uint32_t index = 0; index < subEntityCount; ++index)
                {
                    void* const subEntity =
                        TryGetChunkProxySubEntitySafe(slot.entity, index, getSubEntity);

                    // A live Entity never returns null below its own count, so
                    // this is a stale entity. Stop touching it immediately
                    // rather than faulting once per remaining index.
                    if (!subEntity)
                    {
                        LogChunkManualSubmitSkip(slot, L"entity-fault-sub-entity", sceneManager, viewport, currentCamera, resolvedCamera);
                        ForgetChunkProxySlotOgreRefs(slot);
                        return false;
                    }

                    if (!TryAddChunkProxyRenderableSafe(
                            renderQueue,
                            subEntity,
                            groupId,
                            100u,
                            addRenderablePriority))
                    {
                        LogChunkManualSubmitSkip(
                            slot,
                            L"sub-entity-stale",
                            sceneManager,
                            viewport,
                            currentCamera,
                            resolvedCamera);
                        ForgetChunkProxySlotOgreRefs(slot);
                        return false;
                    }
                    ++directAddCount;
                    if (slot.renderQueueAddCount < USHRT_MAX)
                        ++slot.renderQueueAddCount;
                }
            }

            if (isVisible)
            {
                const int visibleProbe = TryGetChunkProxyVisibleSafe(slot.entity, isVisible);
                if (visibleProbe >= 0)
                    visibleNow = visibleProbe != 0;
            }

            // Camera world position tells us whether the render camera lives in
            // the same coordinate space as the sim positions we mirror onto the
            // proxy nodes; a camera near the origin while chunks sit at ~1e5
            // would mean a render-space offset we are not applying.
            static FnOgreCameraGetDerivedPosition getCameraDerivedPosition =
                ResolveOgreProc<FnOgreCameraGetDerivedPosition>("?getDerivedPosition@Camera@Ogre@@QBEABVVector3@2@XZ");
            OgreVector3 cameraPos = { 0.0f, 0.0f, 0.0f };
            const bool haveCameraPos = TryGetChunkProxyCameraPositionSafe(
                resolvedCamera, getCameraDerivedPosition, cameraPos);

            static volatile long s_FirstManualSubmitLogBudget = 12;
            if ((slot.cameraNotifyCount <= 4 || slot.entityUpdateQueueCount <= 4 || slot.renderQueueAddCount <= 4) &&
                InterlockedDecrement(&s_FirstManualSubmitLogBudget) >= 0)
            {
                LogChunkDiagnostic(
                    "chunkmesh",
                    L"[CHUNKMESH] manual-submit-campos have=%u pos=(%.2f, %.2f, %.2f)\n",
                    haveCameraPos ? 1u : 0u,
                    static_cast<double>(cameraPos.x),
                    static_cast<double>(cameraPos.y),
                    static_cast<double>(cameraPos.z));
                LogChunkDiagnostic(
                    "chunkmesh",
                    L"[CHUNKMESH] manual-submit obj=0x%08X entity=0x%08X mesh=%hs sceneMgr=0x%08X viewport=0x%08X queue=0x%08X camera=0x%08X source=%hs visibleNow=%u notifyCount=%u updateCount=%u addCount=%u\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                    GetChunkPayloadMeshName(slot),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sceneManager)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(viewport)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(renderQueue)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(resolvedCamera)),
                    (viewport && resolvedCamera && resolvedCamera != currentCamera) ? "viewport" :
                    (currentCamera ? "hint" : "none"),
                    visibleNow ? 1u : 0u,
                    static_cast<unsigned>(slot.cameraNotifyCount),
                    static_cast<unsigned>(slot.entityUpdateQueueCount),
                    static_cast<unsigned>(slot.renderQueueAddCount));
            }

            return visibleNow;
        }

        static bool IsChunkManualSubmitEnabled()
        {
            static const bool disabled =
                EnvFlagEnabled("OPENSHIM_DISABLE_CHUNK_MANUAL_SUBMIT") ||
                EnvFlagEnabled("BZR_DISABLE_CHUNK_MANUAL_SUBMIT");
            return !disabled;
        }

        // Reads the geo-local vertex bounds straight out of the Redux geom
        // struct (vertex count at +0x04, position array at +0x0C, 3 floats
        // per vertex) so payload mesh pivots can be compared against the
        // original geo pivots the chunk sim rotates around.
        static bool TryComputeChunkGeomLocalBounds(
            const void* geomRef,
            uint32_t& outCount,
            float outMin[3],
            float outMax[3])
        {
            outCount = 0;
            if (!geomRef)
                return false;

            __try
            {
                const auto* geomBytes = reinterpret_cast<const uint8_t*>(geomRef);
                const uint32_t count = *reinterpret_cast<const uint32_t*>(geomBytes + 0x04);
                const float* verts = *reinterpret_cast<const float* const*>(geomBytes + 0x0C);
                if (!verts || count == 0 || count > 65536)
                    return false;

                for (uint32_t i = 0; i < count; ++i)
                {
                    const float* v = verts + (static_cast<size_t>(i) * 3);
                    for (int axis = 0; axis < 3; ++axis)
                    {
                        if (i == 0 || v[axis] < outMin[axis])
                            outMin[axis] = v[axis];
                        if (i == 0 || v[axis] > outMax[axis])
                            outMax[axis] = v[axis];
                    }
                }

                outCount = count;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outCount = 0;
                return false;
            }
        }

        // Redux renders around a per-map origin (terrain center, the
        // Ogre::Vector3 global at kGogWorldRenderOriginAddr) with the Z axis
        // mirrored versus sim space. The camera, lights, and every world
        // renderable go through this conversion inside the exe, so proxy
        // nodes fed raw sim coordinates land ~1e5 units outside the render
        // world and never appear on screen.
        static bool TryConvertChunkSimTransformToRenderSpace(ChunkProxyTransform& transform)
        {
            float origin[3] = {};

            __try
            {
                const float* originPtr = reinterpret_cast<const float*>(kGogWorldRenderOriginAddr);
                origin[0] = originPtr[0];
                origin[1] = originPtr[1];
                origin[2] = originPtr[2];
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }

            static volatile long s_OriginLogBudget = 1;
            if (InterlockedDecrement(&s_OriginLogBudget) >= 0)
            {
                LogChunkDiagnostic(
                    "chunkmesh",
                    L"[CHUNKMESH] render-origin=(%.2f, %.2f, %.2f)\n",
                    static_cast<double>(origin[0]),
                    static_cast<double>(origin[1]),
                    static_cast<double>(origin[2]));
            }

            transform.x = transform.x - origin[0];
            transform.y = transform.y - origin[1];
            transform.z = -transform.z - origin[2];
            // Conjugating a rotation by the Z mirror negates the quaternion
            // X/Y components (X/Y rotations flip direction, Z rotations do
            // not).
            transform.orientation.x = -transform.orientation.x;
            transform.orientation.y = -transform.orientation.y;
            return true;
        }

        static bool TryHashGenericChunkPayload(
            const std::filesystem::path& path,
            uintmax_t expectedBytes,
            uint64_t& outHash)
        {
            outHash = 0;
            std::error_code error;
            if (!std::filesystem::is_regular_file(path, error) || error ||
                std::filesystem::file_size(path, error) != expectedBytes || error)
            {
                return false;
            }

            std::ifstream input(path, std::ios::binary);
            if (!input)
                return false;

            uint64_t hash = 14695981039346656037ull;
            std::array<char, 4096> buffer = {};
            while (input)
            {
                input.read(buffer.data(), buffer.size());
                const std::streamsize count = input.gcount();
                for (std::streamsize index = 0; index < count; ++index)
                {
                    hash ^= static_cast<uint8_t>(buffer[static_cast<size_t>(index)]);
                    hash *= 1099511628211ull;
                }
            }
            if (!input.eof())
                return false;

            outHash = hash;
            return true;
        }

        static bool IsCanonicalGenericChunkPayload(uint8_t kind)
        {
            if (kind < 1 || kind > 2)
                return false;

            int& cached = g_GenericChunkBatchEligibility[kind - 1];
            if (cached >= 0)
                return cached != 0;

            if (g_ChunkPayloadResourceDirectories.empty())
                RefreshChunkPayloadResourceDirectories();

            const std::filesystem::path relativePath = kind == 1
                ? std::filesystem::path("chunk1") / "chunk1.mesh"
                : std::filesystem::path("chunk2") / "chunk2.mesh";
            const uintmax_t expectedBytes = kind == 1
                ? kChunk1MeshBytes : kChunk2MeshBytes;
            const uint64_t expectedHash = kind == 1
                ? kChunk1MeshFnv1a : kChunk2MeshFnv1a;

            bool found = false;
            bool canonical = true;
            for (const std::filesystem::path& root : g_ChunkPayloadResourceDirectories)
            {
                const std::filesystem::path candidate = root / relativePath;
                std::error_code existsError;
                if (!std::filesystem::exists(candidate, existsError) || existsError)
                    continue;

                found = true;
                uint64_t actualHash = 0;
                if (!TryHashGenericChunkPayload(
                        candidate, expectedBytes, actualHash) ||
                    actualHash != expectedHash)
                {
                    canonical = false;
                    break;
                }
            }

            cached = found && canonical ? 1 : 0;
            LogChunkDiagnostic(
                "chunkbatch",
                L"[CHUNKBATCH] canonical chunk%u batching=%hs roots=%zu expectedBytes=%zu hash=0x%016llX\n",
                static_cast<unsigned>(kind),
                cached ? "enabled" : "fallback-entity",
                g_ChunkPayloadResourceDirectories.size(),
                static_cast<size_t>(expectedBytes),
                static_cast<unsigned long long>(expectedHash));
            return cached != 0;
        }

        // The batch bakes every chunklet into one shared ManualObject section,
        // and AppendGenericChunkBatchGeometry() applies orientation and
        // translation only -- there is no per-chunk node left to carry a
        // scale. Batching a scaled chunk would therefore render it at the
        // wrong size with no way to notice.
        //
        // Today ChunkProxyTransform::scale is structurally unit: the legacy
        // basis vectors are normalised when the quaternion is built, so no
        // code path ever populates a non-unit value. This gate exists so that
        // stays an enforced invariant rather than an assumption -- if a future
        // change or runtime does populate scale, the chunk falls back to the
        // per-Entity path instead of being silently mis-sized.
        //
        // Correct arbitrary scale in the batch would additionally require
        // inverse-transpose handling for normals and tangents. That is not
        // implemented deliberately: no evidence shows stock or modded generic
        // chunklets need it, and the fallback path already renders them.
        static bool IsUnitScaleForGenericChunkBatch(const OgreVector3& scale)
        {
            // Loose enough to absorb float round-trips through a matrix
            // decomposition, tight enough that a real authored scale (the
            // smallest plausible being a few percent) is always rejected.
            constexpr float kEpsilon = 1.0e-3f;
            const float components[3] = { scale.x, scale.y, scale.z };
            for (const float component : components)
            {
                if (!std::isfinite(component) ||
                    std::fabs(component - 1.0f) > kEpsilon)
                {
                    return false;
                }
            }
            return true;
        }

        static void NoteGenericChunkBatchScaleRejection(const OgreVector3& scale)
        {
            ++g_GenericChunkBatchNonUnitScaleRejections;
            const DWORD now = GetTickCount();
            if (g_GenericChunkBatchScaleLogTick != 0 &&
                static_cast<DWORD>(now - g_GenericChunkBatchScaleLogTick) < 5000)
            {
                return;
            }
            g_GenericChunkBatchScaleLogTick = now;
            LogChunkDiagnostic(
                "chunkbatch",
                L"[CHUNKBATCH] non-unit scale (%.4f, %.4f, %.4f); per-entity fallback, total=%llu\n",
                static_cast<double>(scale.x),
                static_cast<double>(scale.y),
                static_cast<double>(scale.z),
                static_cast<unsigned long long>(
                    g_GenericChunkBatchNonUnitScaleRejections));
        }

        static uint8_t GetGenericChunkBatchKind(const char* meshName)
        {
            if (!g_EnableGenericChunkBatch ||
                !g_GenericChunkBatchRuntimeAvailable || !meshName)
            {
                return 0;
            }
            if (_stricmp(meshName, "chunk1/chunk1.mesh") == 0)
                return IsCanonicalGenericChunkPayload(1) ? 1 : 0;
            if (_stricmp(meshName, "chunk2/chunk2.mesh") == 0)
                return IsCanonicalGenericChunkPayload(2) ? 2 : 0;
            return 0;
        }

        static void UpdateChunkProxySlotPosition(
            ChunkProxySlot& slot,
            void* currentCamera = nullptr,
            bool allowManualSubmit = true)
        {
            static FnOgreSetBillboardPosition setPosition =
                ResolveOgreProc<FnOgreSetBillboardPosition>("?setPosition@Billboard@Ogre@@QAEXMMM@Z");
            static FnOgreSetNodePosition setNodePosition =
                ResolveOgreProc<FnOgreSetNodePosition>("?setPosition@Node@Ogre@@UAEXMMM@Z");
            static FnOgreSetNodeOrientation setNodeOrientation =
                ResolveOgreProc<FnOgreSetNodeOrientation>("?setOrientation@Node@Ogre@@UAEXMMMM@Z");
            static FnOgreSetVisible setVisible =
                ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");
            if (!slot.active)
                return;

            slot.genericBatchKind = 0;
            slot.genericBatchTransformReady = false;

            if (slot.objectBytes)
            {
                const ChunkResolvedBindingEntry* binding =
                    FindChunkResolvedBindingEntryForGeom(slot.objectBytes, slot.geomName);
                if (binding && binding->payloadMeshName[0] &&
                    _stricmp(slot.proofMeshName, binding->payloadMeshName) != 0)
                {
                    if (AcquireChunkLogSlot())
                    {
                        LogChunkDiagnostic(
                            "chunkmesh",
                            L"[CHUNKMESH] rebinding obj=0x%08X oldMesh=%hs newMesh=%hs root=0x%08X rootGameObj=0x%08X ownerObj=0x%08X\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                            slot.proofMeshName[0] ? slot.proofMeshName : "<none>",
                            binding->payloadMeshName,
                            binding->sourceRootObjectPtr,
                            binding->sourceRootGameObjectPtr,
                            binding->sourceOwnerObjPtr);
                    }

                    InvalidateChunkMeshProxySlot(slot);
                    strncpy_s(slot.proofMeshName, sizeof(slot.proofMeshName), binding->payloadMeshName, _TRUNCATE);
                }
            }

            ChunkProxyTransform transform = {};
            const void* resolvedTransformObject = nullptr;
            bool haveTransform = TryResolveChunkProxyTransformForSlot(
                slot,
                transform,
                &resolvedTransformObject);

            if (haveTransform)
            {
                ChunkProxyTransform anchoredTransform = {};
                const void* anchorObject = nullptr;
                if (TryPromoteChunkProxyLocalTransformToAnchoredWorld(
                        slot,
                        transform,
                        resolvedTransformObject,
                        anchoredTransform,
                        &anchorObject))
                {
                    transform = anchoredTransform;
                    if (anchorObject)
                        resolvedTransformObject = anchorObject;
                }
                else if (slot.useEntryPosition && ShouldPreferChunkEntryPosition(slot, transform))
                {
                    transform.x = slot.positionX;
                    transform.y = slot.positionY;
                    transform.z = slot.positionZ;
                }
            }
            else if (slot.useEntryPosition)
            {
                const void* anchorObject = nullptr;
                if (TryBuildChunkProxyAnchoredEntryTransform(
                        slot,
                        nullptr,
                        transform,
                        &anchorObject))
                {
                    resolvedTransformObject = anchorObject;
                    haveTransform = true;
                }
                else
                {
                    transform.x = slot.positionX;
                    transform.y = slot.positionY;
                    transform.z = slot.positionZ;
                    transform.orientation = { 1.0f, 0.0f, 0.0f, 0.0f };
                    transform.scale = { 1.0f, 1.0f, 1.0f };
                    resolvedTransformObject = slot.objectBytes;
                    haveTransform = true;
                }
            }

            if (haveTransform && !TryConvertChunkSimTransformToRenderSpace(transform))
                haveTransform = false;

            const bool useMeshProxy = ShouldUseChunkPayloadMesh(slot);

            if (!useMeshProxy)
            {
                if (slot.billboard && haveTransform && setPosition)
                {
                    if (TrySetChunkProxyBillboardPosition(
                            slot.billboard,
                            setPosition,
                            transform.x,
                            transform.y,
                            transform.z))
                    {
                        slot.billboardAssigned = true;
                    }
                    else
                    {
                        LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] Billboard setPosition failed for obj=0x%08X geom=0x%08X\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.geomRef)),
                            GetChunkGeomNameForLog(slot.geomName));
                    }
                }

                if (slot.meshAssigned)
                {
                    HideChunkProxyMesh(slot);
                    slot.meshAssigned = false;
                }
                return;
            }

            if (haveTransform)
            {
                uint8_t genericBatchKind =
                    GetGenericChunkBatchKind(slot.proofMeshName);
                if (genericBatchKind != 0 && g_ForceGenericChunkNonUnitScale)
                    transform.scale = { 1.25f, 0.75f, 1.0f };
                if (genericBatchKind != 0 &&
                    !IsUnitScaleForGenericChunkBatch(transform.scale))
                {
                    // Not batchable: fall through to the per-Entity fidelity
                    // path below, which keeps its own scene node.
                    NoteGenericChunkBatchScaleRejection(transform.scale);
                    genericBatchKind = 0;
                }
                if (genericBatchKind != 0)
                {
                    if (slot.meshAssigned)
                    {
                        HideChunkProxyMesh(slot);
                        slot.meshAssigned = false;
                    }
                    slot.genericBatchTransform = transform;
                    slot.genericBatchKind = genericBatchKind;
                    slot.genericBatchTransformReady = true;
                    return;
                }

                if (!EnsureChunkMeshProxySlot(slot))
                    return;

                const bool transformOk = TryUpdateChunkMeshProxyTransform(
                    slot.sceneNode,
                    slot.entity,
                    setNodePosition,
                    setNodeOrientation,
                    setVisible,
                    transform);

                static volatile long s_FirstMeshTransformLogBudget = 8;
                if (InterlockedDecrement(&s_FirstMeshTransformLogBudget) >= 0)
                {
                    LogChunkDiagnostic("chunkmesh",
                        L"[CHUNKMESH] first-transform obj=0x%08X node=0x%08X entity=0x%08X mesh=%hs ok=%u procs=%u/%u pos=(%.2f, %.2f, %.2f)\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.sceneNode)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                        GetChunkPayloadMeshName(slot),
                        transformOk ? 1u : 0u,
                        setNodePosition ? 1u : 0u,
                        setVisible ? 1u : 0u,
                        static_cast<double>(transform.x),
                        static_cast<double>(transform.y),
                        static_cast<double>(transform.z));
                }

                if (!transformOk)
                {
                    ReleaseChunkProxySlot(slot, L"mesh-set-failed");
                    return;
                }

                if (!slot.meshAssigned && AcquireChunkLogSlot())
                {
                    LogChunkDiagnostic("chunkmesh", L"[CHUNKMESH] assigned obj=0x%08X entity=0x%08X geom=0x%08X geomName=%hs mesh=%hs pos=(%.4f, %.4f, %.4f)\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.objectBytes)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.geomRef)),
                        GetChunkGeomNameForLog(slot.geomName),
                        GetChunkPayloadMeshName(slot),
                        static_cast<double>(transform.x),
                        static_cast<double>(transform.y),
                        static_cast<double>(transform.z));

                    uint32_t geoVertCount = 0;
                    float geoMin[3] = {};
                    float geoMax[3] = {};
                    if (TryComputeChunkGeomLocalBounds(slot.geomRef, geoVertCount, geoMin, geoMax))
                    {
                        LogChunkDiagnostic("chunkmesh",
                            L"[CHUNKMESH] geo-bounds geom=0x%08X name=%hs verts=%u center=(%.2f, %.2f, %.2f) size=(%.2f, %.2f, %.2f)\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.geomRef)),
                            GetChunkGeomNameForLog(slot.geomName),
                            geoVertCount,
                            static_cast<double>((geoMin[0] + geoMax[0]) * 0.5f),
                            static_cast<double>((geoMin[1] + geoMax[1]) * 0.5f),
                            static_cast<double>((geoMin[2] + geoMax[2]) * 0.5f),
                            static_cast<double>(geoMax[0] - geoMin[0]),
                            static_cast<double>(geoMax[1] - geoMin[1]),
                            static_cast<double>(geoMax[2] - geoMin[2]));
                    }
                }
                slot.meshAssigned = true;

                // Redux drives the Ogre render queue itself rather than letting
                // the scene manager traverse root-node children, so a positioned
                // visible entity still never draws. Inject it into the current
                // render queue while the game is submitting its own legacy
                // effects (EngineFlameSubmitHook passes the active camera).
                if (allowManualSubmit && IsChunkManualSubmitEnabled())
                    TrySubmitChunkMeshProxyToCurrentRenderQueue(slot, currentCamera);
            }
            else if (slot.meshAssigned)
            {
                HideChunkProxyMesh(slot);
                slot.meshAssigned = false;
            }
        }

        void TickChunkProxyDebug(
            void* currentCamera,
            bool allowManualSubmit)
        {
            if (!g_EnableChunkProxyDebug && !g_EnableChunkMeshProxy)
                return;

            if (g_EnableChunkProxyDebug)
                EnsureChunkProxyResources();
            if (g_ChunkProxySlots.empty())
                return;

            const DWORD now = GetTickCount();
            for (ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (!slot.active)
                    continue;

                if (slot.lastSeenTick == 0 ||
                    static_cast<DWORD>(now - slot.lastSeenTick) >= kChunkProxyExpireMs)
                {
                    ReleaseChunkProxySlot(slot, L"expired");
                    continue;
                }

                UpdateChunkProxySlotPosition(slot, currentCamera, allowManualSubmit);
            }
        }

        static OgreVector3 RotateGenericChunkVector(
            const OgreQuaternion& q,
            const OgreVector3& value)
        {
            const OgreVector3 qv = { q.x, q.y, q.z };
            const float dotQvValue =
                qv.x * value.x + qv.y * value.y + qv.z * value.z;
            const float dotQvQv = qv.x * qv.x + qv.y * qv.y + qv.z * qv.z;
            const OgreVector3 cross = {
                qv.y * value.z - qv.z * value.y,
                qv.z * value.x - qv.x * value.z,
                qv.x * value.y - qv.y * value.x
            };
            return {
                2.0f * dotQvValue * qv.x +
                    (q.w * q.w - dotQvQv) * value.x + 2.0f * q.w * cross.x,
                2.0f * dotQvValue * qv.y +
                    (q.w * q.w - dotQvQv) * value.y + 2.0f * q.w * cross.y,
                2.0f * dotQvValue * qv.z +
                    (q.w * q.w - dotQvQv) * value.z + 2.0f * q.w * cross.z
            };
        }

        static void AppendGenericChunkBatchGeometry(
            void* manualObject,
            const GenericChunkVertex* vertices,
            size_t vertexCount,
            const ChunkProxyTransform& transform,
            uint32_t& nextIndex,
            FnOgreManualObjectVertex3 position,
            FnOgreManualObjectVertex3 normal,
            FnOgreManualObjectVertex3 tangent,
            FnOgreManualObjectTexture2 textureCoord,
            FnOgreManualObjectIndex addIndex)
        {
            const uint32_t firstIndex = nextIndex;
            for (size_t index = 0; index < vertexCount; ++index)
            {
                const GenericChunkVertex& source = vertices[index];
                OgreVector3 transformedPosition = RotateGenericChunkVector(
                    transform.orientation, source.position);
                transformedPosition.x += transform.x;
                transformedPosition.y += transform.y;
                transformedPosition.z += transform.z;
                const OgreVector3 transformedNormal = RotateGenericChunkVector(
                    transform.orientation, source.normal);
                const OgreVector3 transformedTangent = RotateGenericChunkVector(
                    transform.orientation, source.tangent);

                position(
                    manualObject,
                    transformedPosition.x,
                    transformedPosition.y,
                    transformedPosition.z);
                normal(
                    manualObject,
                    transformedNormal.x,
                    transformedNormal.y,
                    transformedNormal.z);
                tangent(
                    manualObject,
                    transformedTangent.x,
                    transformedTangent.y,
                    transformedTangent.z);
                textureCoord(manualObject, source.u, source.v);
                ++nextIndex;
            }
            for (uint32_t index = firstIndex; index < nextIndex; ++index)
                addIndex(manualObject, index);
        }

        // Failure invariant for the generic chunk batch.
        //
        // UpdateChunkProxySlotPosition() hides (and for a slot born eligible,
        // never creates) the per-Entity mesh proxy the moment a slot is
        // classified batch-ready. From that point until the ManualObject is
        // successfully submitted, the *only* thing that will draw those
        // chunklets is the batch. So if RebuildAndSubmitGenericChunkBatch()
        // returns false, the per-Entity loop below cannot simply be allowed to
        // run: it skips any slot with a null `entity`, which is exactly the
        // slots that were classified batch-ready, and the debris disappears.
        //
        // Two different strengths of assurance apply here, and they should
        // not be conflated.
        //
        // Guaranteed by construction: batch ownership is always released.
        // genericBatchTransformReady/genericBatchKind are cleared before any
        // Ogre call and on every path, including both `continue`s below, so a
        // slot can never stay stranded claiming the batch owns it. That is
        // what makes the pre-fix pathological state unreachable.
        //
        // Attempted but not guaranteed: same-frame Entity restoration.
        // EnsureChunkMeshProxySlot() and TryUpdateChunkMeshProxyTransform()
        // can both fail (SceneManager unavailable, entity creation failure,
        // unresolved Ogre export). Such a slot is counted in `demoted` but
        // not in `restored`, is invisible for that one frame, and is retried
        // by the ordinary per-Entity path on later frames because its flags
        // are already clear. The forced-failure test observed
        // demoted == restored across 39,688 rehydrations, so restoration was
        // complete on the tested workload -- but this code does not prove it
        // must be.
        //
        // Recovering a partially constructed ManualObject is deliberately not
        // attempted -- the Entity path is the known-good fidelity path and is
        // cheap to rehydrate.
        static void RehydrateGenericChunkBatchSlotsToEntities(const wchar_t* reason)
        {
            static FnOgreSetNodePosition setNodePosition =
                ResolveOgreProc<FnOgreSetNodePosition>("?setPosition@Node@Ogre@@UAEXMMM@Z");
            static FnOgreSetNodeOrientation setNodeOrientation =
                ResolveOgreProc<FnOgreSetNodeOrientation>("?setOrientation@Node@Ogre@@UAEXMMMM@Z");
            static FnOgreSetVisible setVisible =
                ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");

            size_t demoted = 0;
            size_t restored = 0;
            for (ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (!slot.active || !slot.genericBatchTransformReady)
                    continue;

                const ChunkProxyTransform transform = slot.genericBatchTransform;
                // Clear first and unconditionally. Even if the Entity cannot
                // be built this frame (Ogre not ready), the slot must stop
                // claiming the batch owns it, or the per-Entity loop will keep
                // skipping it forever.
                slot.genericBatchTransformReady = false;
                slot.genericBatchKind = 0;
                ++demoted;

                if (!EnsureChunkMeshProxySlot(slot))
                    continue;
                if (!TryUpdateChunkMeshProxyTransform(
                        slot.sceneNode,
                        slot.entity,
                        setNodePosition,
                        setNodeOrientation,
                        setVisible,
                        transform))
                {
                    continue;
                }
                slot.meshAssigned = true;
                ++restored;
            }

            if (demoted == 0)
                return;

            g_GenericChunkBatchRehydrations += demoted;
            const DWORD now = GetTickCount();
            if (g_GenericChunkBatchRehydrateLogTick != 0 &&
                static_cast<DWORD>(now - g_GenericChunkBatchRehydrateLogTick) < 1000)
            {
                return;
            }
            g_GenericChunkBatchRehydrateLogTick = now;
            LogChunkDiagnostic(
                "chunkbatch",
                L"[CHUNKBATCH] rehydrate (%ls): demoted=%zu restored=%zu total=%llu runtimeAvailable=%u\n",
                reason ? reason : L"<none>",
                demoted,
                restored,
                static_cast<unsigned long long>(g_GenericChunkBatchRehydrations),
                g_GenericChunkBatchRuntimeAvailable ? 1u : 0u);
        }

        // High-resolution rebuild cost. Sampled unconditionally because the
        // rebuild path is already thousands of virtual Ogre calls, so two QPC
        // reads are noise -- and a cost figure that only exists when
        // diagnostics are on cannot be used to justify the optimization.
        static int64_t ReadChunkBatchQpc()
        {
            LARGE_INTEGER counter = {};
            QueryPerformanceCounter(&counter);
            return counter.QuadPart;
        }

        static void NoteChunkBatchRebuildCost(int64_t startTicks)
        {
            if (g_GenericChunkBatchQpcFrequency == 0)
            {
                LARGE_INTEGER frequency = {};
                QueryPerformanceFrequency(&frequency);
                g_GenericChunkBatchQpcFrequency = frequency.QuadPart;
            }
            if (g_GenericChunkBatchQpcFrequency <= 0)
                return;
            const int64_t elapsed = ReadChunkBatchQpc() - startTicks;
            if (elapsed <= 0)
                return;
            const uint64_t nanoseconds = static_cast<uint64_t>(
                (elapsed * 1000000000ll) / g_GenericChunkBatchQpcFrequency);
            g_GenericChunkBatchTelemetry.rebuildNanoseconds += nanoseconds;
            if (nanoseconds > g_GenericChunkBatchTelemetry.maxRebuildNanoseconds)
                g_GenericChunkBatchTelemetry.maxRebuildNanoseconds = nanoseconds;
        }

        // Which pass is asking. Ogre drives the world _updateRenderQueue
        // override once per camera traversal per active material scheme, so the
        // viewport's scheme is what distinguishes the repeats from each other.
        // Measured on lcbench: exactly three per rendered frame, named
        // "high-pssm", "glow" and "ShaderGeneratorDefaultScheme". They are one
        // world camera path visited once per scheme -- not three PSSM shadow
        // cameras, which was the standing assumption before this instrument.
        //
        // Declared as a pointer return rather than a reference: a reference
        // binding makes MSVC treat the frame as requiring object unwinding,
        // which __try forbids. The ABI is identical.
        using FnOgreGetCurrentViewport = void*(__thiscall*)(void*);
        using FnOgreGetViewportMaterialScheme = const std::string*(__thiscall*)(void*);

        // SEH-only leaf: no statics, no objects, so the frame needs no
        // unwinding. The returned pointer is into Ogre's own string and is only
        // ever read by the immediate caller.
        static const char* TryReadViewportSchemeName(
            void* sceneManager,
            FnOgreGetCurrentViewport getCurrentViewport,
            FnOgreGetViewportMaterialScheme getMaterialScheme)
        {
            __try
            {
                void* const viewport = getCurrentViewport(sceneManager);
                if (!viewport)
                    return "<no-viewport>";
                const std::string* const scheme = getMaterialScheme(viewport);
                if (!scheme || scheme->empty())
                    return "<empty>";
                return scheme->c_str();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return "<faulted>";
            }
        }

        static const char* GetCurrentOgreMaterialSchemeName(void* sceneManager)
        {
            static FnOgreGetCurrentViewport getCurrentViewport =
                ResolveOgreProc<FnOgreGetCurrentViewport>(
                    "?getCurrentViewport@SceneManager@Ogre@@QBEPAVViewport@2@XZ");
            static FnOgreGetViewportMaterialScheme getMaterialScheme =
                ResolveOgreProc<FnOgreGetViewportMaterialScheme>(
                    "?getMaterialScheme@Viewport@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            if (!sceneManager || !getCurrentViewport || !getMaterialScheme)
                return "<unavailable>";
            return TryReadViewportSchemeName(
                sceneManager, getCurrentViewport, getMaterialScheme);
        }

        struct OgreColourValueSnapshot
        {
            float r;
            float g;
            float b;
            float a;
        };

        struct Dx11EnhancedLightingSnapshot
        {
            OgreColourValueSnapshot fog;
            OgreColourValueSnapshot ambient;
            float fogDensity;
            float fogStart;
            float fogEnd;
        };

        using FnOgreGetSceneColour = const OgreColourValueSnapshot*(__thiscall*)(void*);
        using FnOgreGetSceneFloat = float(__thiscall*)(void*);

        // SEH-only leaf. Ogre's colour getters return const ColourValue&, which
        // is an EAX pointer in this 32-bit ABI; copy it while the call is live.
        static bool TryReadDx11EnhancedLightingSnapshot(
            void* sceneManager,
            FnOgreGetSceneColour getFogColour,
            FnOgreGetSceneColour getAmbientLight,
            FnOgreGetSceneFloat getFogDensity,
            FnOgreGetSceneFloat getFogStart,
            FnOgreGetSceneFloat getFogEnd,
            Dx11EnhancedLightingSnapshot* outSnapshot)
        {
            __try
            {
                const OgreColourValueSnapshot* const fog = getFogColour(sceneManager);
                const OgreColourValueSnapshot* const ambient = getAmbientLight(sceneManager);
                if (!fog || !ambient || !outSnapshot)
                    return false;
                outSnapshot->fog = *fog;
                outSnapshot->ambient = *ambient;
                outSnapshot->fogDensity = getFogDensity(sceneManager);
                outSnapshot->fogStart = getFogStart(sceneManager);
                outSnapshot->fogEnd = getFogEnd(sceneManager);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static float SrgbToLinearDiagnostic(float value)
        {
            value = std::clamp(value, 0.0f, 1.0f);
            return value <= 0.04045f
                ? value / 12.92f
                : std::pow((value + 0.055f) / 1.055f, 2.4f);
        }

        static float LinearToSrgbDiagnostic(float value)
        {
            value = std::clamp(value, 0.0f, 1.0f);
            return value <= 0.0031308f
                ? value * 12.92f
                : 1.055f * std::pow(value, 1.0f / 2.4f) - 0.055f;
        }

        static bool Dx11EnhancedLightingSnapshotChanged(
            const Dx11EnhancedLightingSnapshot& lhs,
            const Dx11EnhancedLightingSnapshot& rhs)
        {
            constexpr float epsilon = 0.0001f;
            const auto changed = [epsilon](float a, float b)
            {
                return !std::isfinite(a) || !std::isfinite(b) || std::fabs(a - b) > epsilon;
            };
            return changed(lhs.fog.r, rhs.fog.r) ||
                   changed(lhs.fog.g, rhs.fog.g) ||
                   changed(lhs.fog.b, rhs.fog.b) ||
                   changed(lhs.ambient.r, rhs.ambient.r) ||
                   changed(lhs.ambient.g, rhs.ambient.g) ||
                   changed(lhs.ambient.b, rhs.ambient.b) ||
                   changed(lhs.fogDensity, rhs.fogDensity) ||
                   changed(lhs.fogStart, rhs.fogStart) ||
                   changed(lhs.fogEnd, rhs.fogEnd);
        }

        void MaybeLogDx11EnhancedLightingState()
        {
            static int enabled = -1;
            static DWORD lastPollTick = 0;
            static bool haveLast = false;
            static Dx11EnhancedLightingSnapshot lastSnapshot = {};
            static std::string lastScheme;

            if (enabled < 0)
            {
                bool iniEnabled = false;
                const bool haveIniValue = TryGetUserConfigBool(
                    "Diagnostics", "TraceDX11EnhancedLighting", iniEnabled);
                enabled = (EnvFlagEnabled("OPENSHIM_TRACE_DX11_ENHANCED_LIGHTING") ||
                           (haveIniValue && iniEnabled)) ? 1 : 0;
                if (enabled != 0)
                    LogShimA(LogLevel::Info, "dx11fog", "[DX11FOG] diagnostic enabled\n");
            }
            if (enabled == 0)
                return;

            const DWORD now = GetTickCount();
            if (lastPollTick != 0 && (now - lastPollTick) < 250)
                return;
            lastPollTick = now;

            static FnOgreGetSceneColour getFogColour =
                ResolveOgreProc<FnOgreGetSceneColour>(
                    "?getFogColour@SceneManager@Ogre@@UBEABVColourValue@2@XZ");
            static FnOgreGetSceneColour getAmbientLight =
                ResolveOgreProc<FnOgreGetSceneColour>(
                    "?getAmbientLight@SceneManager@Ogre@@QBEABVColourValue@2@XZ");
            static FnOgreGetSceneFloat getFogDensity =
                ResolveOgreProc<FnOgreGetSceneFloat>(
                    "?getFogDensity@SceneManager@Ogre@@UBEMXZ");
            static FnOgreGetSceneFloat getFogStart =
                ResolveOgreProc<FnOgreGetSceneFloat>(
                    "?getFogStart@SceneManager@Ogre@@UBEMXZ");
            static FnOgreGetSceneFloat getFogEnd =
                ResolveOgreProc<FnOgreGetSceneFloat>(
                    "?getFogEnd@SceneManager@Ogre@@UBEMXZ");
            if (!getFogColour || !getAmbientLight || !getFogDensity ||
                !getFogStart || !getFogEnd)
                return;

            void* const sceneManager = GetOgreSceneManagerRuntime();
            if (!sceneManager)
                return;

            const char* const schemeName = GetCurrentOgreMaterialSchemeName(sceneManager);
            const std::string scheme = schemeName ? schemeName : "<null>";
            const bool enhancedScheme = scheme.size() >= 3 &&
                _strnicmp(scheme.c_str(), "en-", 3) == 0;

            Dx11EnhancedLightingSnapshot snapshot = {};
            if (!TryReadDx11EnhancedLightingSnapshot(
                    sceneManager, getFogColour, getAmbientLight, getFogDensity,
                    getFogStart, getFogEnd, &snapshot))
                return;

            const bool schemeChanged = scheme != lastScheme;
            if (haveLast && !schemeChanged &&
                !Dx11EnhancedLightingSnapshotChanged(snapshot, lastSnapshot))
                return;

            lastScheme = scheme;
            lastSnapshot = snapshot;
            haveLast = true;

            if (!enhancedScheme)
            {
                LogShimA(LogLevel::Info, "dx11fog",
                    "[DX11FOG] state scheme=%s enhanced=0\n", scheme.c_str());
                return;
            }

            const float fogLinearR = SrgbToLinearDiagnostic(snapshot.fog.r);
            const float fogLinearG = SrgbToLinearDiagnostic(snapshot.fog.g);
            const float fogLinearB = SrgbToLinearDiagnostic(snapshot.fog.b);
            constexpr float ambientTintStrength = 0.16f;
            constexpr float ambientInputStrength = 0.35f;
            const float ambientTargetR = std::clamp(
                fogLinearR + snapshot.ambient.r * ambientInputStrength, 0.0f, 1.0f);
            const float ambientTargetG = std::clamp(
                fogLinearG + snapshot.ambient.g * ambientInputStrength, 0.0f, 1.0f);
            const float ambientTargetB = std::clamp(
                fogLinearB + snapshot.ambient.b * ambientInputStrength, 0.0f, 1.0f);
            const float ambientAddR = (ambientTargetR - fogLinearR) * ambientTintStrength;
            const float ambientAddG = (ambientTargetG - fogLinearG) * ambientTintStrength;
            const float ambientAddB = (ambientTargetB - fogLinearB) * ambientTintStrength;
            const float baseLinearR = fogLinearR + ambientAddR;
            const float baseLinearG = fogLinearG + ambientAddG;
            const float baseLinearB = fogLinearB + ambientAddB;
            const float fogRange = snapshot.fogEnd - snapshot.fogStart;
            const float inverseFogRange = fogRange > 0.001f ? 1.0f / fogRange : 0.0f;
            const float atmosphereSupport = std::clamp(inverseFogRange * 160.0f, 0.0f, 1.0f);
            const float terrainIblScale = 0.15f + 0.85f * atmosphereSupport;

            LogShimA(LogLevel::Info, "dx11fog",
                "[DX11FOG] state scheme=%s enhanced=1 authored_srgb=(%.6f,%.6f,%.6f) "
                "shader_linear=(%.6f,%.6f,%.6f) ambient=(%.6f,%.6f,%.6f) "
                "ambient_add=(%.6f,%.6f,%.6f) base_final_srgb=(%.6f,%.6f,%.6f) "
                "untreated_final_srgb=(%.6f,%.6f,%.6f) fogDensity=%.6f fogStart=%.3f "
                "fogEnd=%.3f invRange=%.8f terrainDiffuseIblScale=%.6f\n",
                scheme.c_str(),
                snapshot.fog.r, snapshot.fog.g, snapshot.fog.b,
                fogLinearR, fogLinearG, fogLinearB,
                snapshot.ambient.r, snapshot.ambient.g, snapshot.ambient.b,
                ambientAddR, ambientAddG, ambientAddB,
                LinearToSrgbDiagnostic(baseLinearR),
                LinearToSrgbDiagnostic(baseLinearG),
                LinearToSrgbDiagnostic(baseLinearB),
                LinearToSrgbDiagnostic(snapshot.fog.r),
                LinearToSrgbDiagnostic(snapshot.fog.g),
                LinearToSrgbDiagnostic(snapshot.fog.b),
                snapshot.fogDensity, snapshot.fogStart, snapshot.fogEnd,
                inverseFogRange, terrainIblScale);
        }

        // Interval telemetry for the state-version reuse. Everything here is
        // a delta over the reporting window, so the numbers can be divided by
        // the frame count of the same window to get per-frame rates without
        // needing a frame hook of our own.
        static void LogGenericChunkBatchTelemetry(DWORD windowMs)
        {
            using namespace ChunkBatchInvalidation;
            const Telemetry& now = g_GenericChunkBatchTelemetry;
            const Telemetry& then = g_GenericChunkBatchTelemetryAtLastLog;
            const unsigned long long requests = now.requests - then.requests;
            const unsigned long long rebuilds = now.rebuilds - then.rebuilds;
            const unsigned long long reused = now.reused - then.reused;
            const unsigned long long emptySkips = now.emptySkips - then.emptySkips;
            const unsigned long long vertices = now.verticesRebuilt - then.verticesRebuilt;
            const unsigned long long indices = now.indicesRebuilt - then.indicesRebuilt;
            const unsigned long long nanos =
                now.rebuildNanoseconds - then.rebuildNanoseconds;

            LogChunkDiagnostic(
                "chunkbatch",
                L"[CHUNKBATCH] reuse windowMs=%lu requests=%llu rebuilds=%llu reused=%llu "
                L"emptySkips=%llu dedupPct=%.1f verts=%llu indices=%llu rebuildMs=%.3f maxRebuildMs=%.3f"
                L" mode=%hs\n",
                static_cast<unsigned long>(windowMs),
                requests, rebuilds, reused, emptySkips,
                requests ? (100.0 * static_cast<double>(reused) /
                            static_cast<double>(requests)) : 0.0,
                vertices, indices,
                static_cast<double>(nanos) / 1000000.0,
                static_cast<double>(now.maxRebuildNanoseconds) / 1000000.0,
                g_GenericChunkBatchReuseObserveOnly
                    ? "observe"
                    : (g_GenericChunkBatchReuseEnabled ? "reuse" : "always-rebuild"));

            for (int index = 0; index < 8; ++index)
            {
                const unsigned long long count =
                    now.reasonCounts[index] - then.reasonCounts[index];
                if (count == 0)
                    continue;
                LogChunkDiagnostic(
                    "chunkbatch",
                    L"[CHUNKBATCH] reuse   reason=%hs count=%llu\n",
                    ReasonName(static_cast<Reason>(index)),
                    count);
            }
            for (size_t index = 0; index < now.schemeCount; ++index)
            {
                const SchemeCounters& scheme = now.schemes[index];
                const SchemeCounters& previous =
                    index < then.schemeCount ? then.schemes[index] : SchemeCounters{};
                const unsigned long long schemeRequests =
                    scheme.requests - previous.requests;
                if (schemeRequests == 0)
                    continue;
                LogChunkDiagnostic(
                    "chunkbatch",
                    L"[CHUNKBATCH] reuse   scheme=%hs requests=%llu rebuilds=%llu\n",
                    scheme.name,
                    schemeRequests,
                    static_cast<unsigned long long>(scheme.rebuilds - previous.rebuilds));
            }
            g_GenericChunkBatchTelemetryAtLastLog = now;
        }

        // Takes the batch out of the scene without destroying it, so the next
        // explosion reuses the same ManualObject and section rather than
        // paying for a fresh one. The built version is deliberately left
        // alone: the geometry in the object is still valid, it is simply not
        // wanted right now, and clearing it would force a needless rebuild
        // the moment the same debris set comes back.
        static void HideGenericChunkBatchIfBuilt()
        {
            static FnOgreSetVisible setVisible =
                ResolveOgreProc<FnOgreSetVisible>(
                    "?setVisible@MovableObject@Ogre@@UAEX_N@Z");
            if (!g_GenericChunkBatchManualObject || !setVisible)
                return;
            if (!g_GenericChunkBatchVisible)
                return;
            try
            {
                setVisible(g_GenericChunkBatchManualObject, false);
                g_GenericChunkBatchVisible = false;
            }
            catch (...)
            {
                // Deliberately does NOT clear g_GenericChunkBatchRuntimeAvailable,
                // unlike the emit and submit failures below. Those happen while
                // slots are classified batch-ready and their per-Entity proxies
                // are already hidden, so the batch has promised to draw geometry
                // it can no longer produce and standing down permanently is the
                // safe answer. This path only runs when there is nothing to draw
                // at all, so dropping the object and letting the next explosion
                // recreate it is a recovery, not a risk.
                LogChunkDiagnostic(
                    "chunkbatch",
                    L"[CHUNKBATCH] hide threw; dropping cached batch\n");
                g_GenericChunkBatchManualObject = nullptr;
                // The recorded visibility described the object just dropped.
                g_GenericChunkBatchVisible = false;
                g_GenericChunkBatchSceneNode = nullptr;
                g_GenericChunkBatchSectionCreated = false;
                g_GenericChunkBatchBuiltVersion =
                    ChunkBatchInvalidation::kUnbuiltVersion;
            }
        }

        // The mission run-state seam fires while the outgoing Ogre objects are
        // still valid, before Redux unloads the Modable resource group. Hide
        // every shim-owned renderable in that window, then retire its slot.
        // Merely forgetting the pointers is unsafe: the Entity remains attached
        // to the scene graph and Ogre can traverse it after its Mesh/SubMesh has
        // been unloaded. Dump battlezone98redux.exe.16476.dmp captured exactly
        // that path for Ogre/MO656 (avfigh/ara11nrr.mesh): SubMesh::indexData
        // was null when the loading-screen frame called _getRenderOperation.
        void DeactivateAllChunkProxySceneResources(const wchar_t* reason)
        {
            // Dump battlezone98redux.exe.38660.dmp ended in OgreMain!operator delete
            // with a corrupted stack after mission quit (write to 001b835c, esp in
            // free memory). The seam runs on the main thread with Ogre still valid
            // but about to unload Modable. An Ogre call that faults must not unwind
            // through every slot and leave attached entities. Faults are caught
            // per-slot and demoted to a pointer forget, which is the same recovery
            // the periodic "expired" tick uses when touching the entity faults.
            size_t deactivated = 0;
            size_t faulted = 0;
            for (ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (slot.active || slot.billboardAssigned || slot.meshAssigned)
                    ++deactivated;
                __try
                {
                    ReleaseChunkProxySlot(slot);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    ForgetChunkProxySlotOgreRefs(slot);
                    ++faulted;
                }
            }
            __try
            {
                HideGenericChunkBatchIfBuilt();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_GenericChunkBatchManualObject = nullptr;
                g_GenericChunkBatchSceneNode = nullptr;
                g_GenericChunkBatchVisible = false;
                g_GenericChunkBatchSectionCreated = false;
                ++faulted;
            }

            if (deactivated > 0 || faulted > 0)
            {
                LogChunkDiagnostic(
                    "chunkproxy",
                    L"[CHUNKPROXY] mission transition (%ls): deactivated %zu slot(s) faulted=%zu before resource unload\n",
                    reason ? reason : L"<none>",
                    deactivated,
                    faulted);
            }
        }

        static bool RebuildAndSubmitGenericChunkBatch(void* renderQueue)
        {
            size_t chunkCount = 0;
            size_t vertexCount = 0;
            // Tight bounds of the live chunk set, for the diagnostic comparison
            // against Ogre's own accumulated ManualObject AABB below. Chunk
            // half-extent is under a metre, so slot origins are a fair proxy.
            float tightMin[3] = { FLT_MAX, FLT_MAX, FLT_MAX };
            float tightMax[3] = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
            // The state version is accumulated inside this existing scan, so
            // the reuse check costs no extra pass over the slots -- only a few
            // integer mixes per eligible chunk.
            ChunkBatchInvalidation::SourceVersion sourceVersion;
            uint32_t ordinal = 0;
            for (const ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (!slot.active || !slot.genericBatchTransformReady)
                    continue;
                ++chunkCount;
                vertexCount += slot.genericBatchKind == 1
                    ? std::size(kChunk1Vertices) : std::size(kChunk2Vertices);
                const ChunkProxyTransform& batchTransform = slot.genericBatchTransform;
                ChunkBatchInvalidation::SlotState slotState = {};
                slotState.kind = slot.genericBatchKind;
                slotState.x = batchTransform.x;
                slotState.y = batchTransform.y;
                slotState.z = batchTransform.z;
                slotState.qw = batchTransform.orientation.w;
                slotState.qx = batchTransform.orientation.x;
                slotState.qy = batchTransform.orientation.y;
                slotState.qz = batchTransform.orientation.z;
                slotState.sx = batchTransform.scale.x;
                slotState.sy = batchTransform.scale.y;
                slotState.sz = batchTransform.scale.z;
                ChunkBatchInvalidation::MixSlot(sourceVersion, ordinal++, slotState);
                const float slotOrigin[3] = {
                    batchTransform.x,
                    batchTransform.y,
                    batchTransform.z };
                for (int axis = 0; axis < 3; ++axis)
                {
                    if (slotOrigin[axis] < tightMin[axis])
                        tightMin[axis] = slotOrigin[axis];
                    if (slotOrigin[axis] > tightMax[axis])
                        tightMax[axis] = slotOrigin[axis];
                }
            }
            if (chunkCount == 0)
            {
                // Nothing eligible. Not submitting is necessary but not
                // sufficient: the ManualObject still holds the last geometry
                // and is attached to a node under the root, so it would remain
                // eligible for Ogre's own traversal. Hide it as well, so the
                // frame the last chunk expires is the frame it stops drawing --
                // with or without reuse, and whether or not Ogre traverses it
                // independently of this hook.
                HideGenericChunkBatchIfBuilt();
                ++g_GenericChunkBatchTelemetry.emptySkips;
                return false;
            }
            ChunkBatchInvalidation::MixCount(
                sourceVersion, static_cast<uint32_t>(chunkCount));

            // TEST/DIAGNOSTIC ONLY. Placed deliberately *after* the eligible
            // slots have been counted, so the injected failure lands in the
            // same window a real Ogre construction failure would: the mesh
            // proxies are already hidden or unbuilt and the batch has promised
            // to draw them. Production never sets this flag.
            if (g_ForceGenericChunkBatchFailure)
            {
                static volatile long s_ForcedFailureLogBudget = 4;
                if (InterlockedDecrement(&s_ForcedFailureLogBudget) >= 0)
                {
                    LogChunkDiagnostic(
                        "chunkbatch",
                        L"[CHUNKBATCH] forced failure injected (diagnostic): eligible=%zu\n",
                        chunkCount);
                }
                return false;
            }

            static FnOgreCreateManualObject createManualObject =
                ResolveOgreProc<FnOgreCreateManualObject>(
                    "?createManualObject@SceneManager@Ogre@@UAEPAVManualObject@2@XZ");
            static FnOgreGetRootSceneNode getRootSceneNode =
                ResolveOgreProc<FnOgreGetRootSceneNode>(
                    "?getRootSceneNode@SceneManager@Ogre@@UAEPAVSceneNode@2@XZ");
            static FnOgreCreateChildSceneNode createChildSceneNode =
                ResolveOgreProc<FnOgreCreateChildSceneNode>(
                    "?createChildSceneNode@SceneNode@Ogre@@UAEPAV12@ABVVector3@2@ABVQuaternion@2@@Z");
            static FnOgreAttachObject attachObject =
                ResolveOgreProc<FnOgreAttachObject>(
                    "?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
            static FnOgreManualObjectSetDynamic setDynamic =
                ResolveOgreProc<FnOgreManualObjectSetDynamic>(
                    "?setDynamic@ManualObject@Ogre@@UAEX_N@Z");
            static FnOgreManualObjectEstimateCount estimateVertices =
                ResolveOgreProc<FnOgreManualObjectEstimateCount>(
                    "?estimateVertexCount@ManualObject@Ogre@@UAEXI@Z");
            static FnOgreManualObjectEstimateCount estimateIndices =
                ResolveOgreProc<FnOgreManualObjectEstimateCount>(
                    "?estimateIndexCount@ManualObject@Ogre@@UAEXI@Z");
            static FnOgreManualObjectBegin begin =
                ResolveOgreProc<FnOgreManualObjectBegin>(
                    "?begin@ManualObject@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4OperationType@RenderOperation@2@0@Z");
            static FnOgreManualObjectBeginUpdate beginUpdate =
                ResolveOgreProc<FnOgreManualObjectBeginUpdate>(
                    "?beginUpdate@ManualObject@Ogre@@UAEXI@Z");
            static FnOgreManualObjectVertex3 position =
                ResolveOgreProc<FnOgreManualObjectVertex3>(
                    "?position@ManualObject@Ogre@@UAEXMMM@Z");
            static FnOgreManualObjectVertex3 normal =
                ResolveOgreProc<FnOgreManualObjectVertex3>(
                    "?normal@ManualObject@Ogre@@UAEXMMM@Z");
            static FnOgreManualObjectVertex3 tangent =
                ResolveOgreProc<FnOgreManualObjectVertex3>(
                    "?tangent@ManualObject@Ogre@@UAEXMMM@Z");
            static FnOgreManualObjectTexture2 textureCoord =
                ResolveOgreProc<FnOgreManualObjectTexture2>(
                    "?textureCoord@ManualObject@Ogre@@UAEXMM@Z");
            static FnOgreManualObjectIndex addIndex =
                ResolveOgreProc<FnOgreManualObjectIndex>(
                    "?index@ManualObject@Ogre@@UAEXI@Z");
            static FnOgreManualObjectEnd end =
                ResolveOgreProc<FnOgreManualObjectEnd>(
                    "?end@ManualObject@Ogre@@UAEPAVManualObjectSection@12@XZ");
            static FnOgreManualObjectUpdateRenderQueue updateRenderQueue =
                ResolveOgreProc<FnOgreManualObjectUpdateRenderQueue>(
                    "?_updateRenderQueue@ManualObject@Ogre@@UAEXPAVRenderQueue@2@@Z");
            static FnOgreMovableSetCastShadows setCastShadows =
                ResolveOgreProc<FnOgreMovableSetCastShadows>(
                    "?setCastShadows@MovableObject@Ogre@@QAEX_N@Z");
            static FnOgreSetVisible setVisible =
                ResolveOgreProc<FnOgreSetVisible>(
                    "?setVisible@MovableObject@Ogre@@UAEX_N@Z");

            if (!createManualObject || !getRootSceneNode ||
                !createChildSceneNode || !attachObject || !setDynamic ||
                !estimateVertices || !estimateIndices || !begin ||
                !beginUpdate || !position || !normal || !tangent ||
                !textureCoord || !addIndex || !end || !updateRenderQueue ||
                !setCastShadows || !setVisible)
            {
                LogChunkDiagnostic(
                    "chunkbatch",
                    L"[CHUNKBATCH] required Ogre exports unavailable; falling back to per-entity chunks\n");
                g_GenericChunkBatchRuntimeAvailable = false;
                return false;
            }

            void* const sceneManager = GetOgreSceneManagerRuntime();
            if (!sceneManager)
                return false;
            const bool sceneManagerChanged =
                g_GenericChunkBatchSceneManager != sceneManager;
            if (sceneManagerChanged)
            {
                // A new SceneManager means the previous ManualObject belongs to
                // a destroyed scene. Drop the cached version with it, or reuse
                // would submit a dangling object across a mission boundary.
                g_GenericChunkBatchManualObject = nullptr;
                // The recorded visibility described the object just dropped.
                g_GenericChunkBatchVisible = false;
                g_GenericChunkBatchSceneNode = nullptr;
                g_GenericChunkBatchSceneManager = sceneManager;
                g_GenericChunkBatchSectionCreated = false;
                g_GenericChunkBatchBuiltVersion =
                    ChunkBatchInvalidation::kUnbuiltVersion;
            }

            // ---- reuse decision -------------------------------------------
            // Everything below this point that can invalidate the built
            // geometry has already been resolved: the ManualObject exists or
            // does not, the SceneManager has been compared, and the source
            // version is computed. Anything uncertain resolves toward
            // rebuilding inside DecideRebuild().
            ChunkBatchInvalidation::BuiltState builtState = {};
            builtState.version = g_GenericChunkBatchBuiltVersion;
            builtState.objectAlive = g_GenericChunkBatchManualObject != nullptr;
            builtState.sectionCreated = g_GenericChunkBatchSectionCreated;
            // Redundant with objectAlive today, because the SceneManager check
            // above already nulls the object. Fed anyway so the policy states
            // the requirement itself rather than relying on a side effect
            // several lines up.
            builtState.objectIdentityStable = !sceneManagerChanged;
            builtState.materialStable =
                g_GenericChunkBatchBuiltMaterial == g_GenericChunkBatchMaterialName;

            const ChunkBatchInvalidation::Reason reason =
                ChunkBatchInvalidation::DecideRebuild(
                    builtState,
                    sourceVersion.Value(),
                    !g_GenericChunkBatchReuseEnabled);
            const bool wantRebuild = ChunkBatchInvalidation::ShouldRebuild(reason);

            ++g_GenericChunkBatchTelemetry.requests;
            g_GenericChunkBatchTelemetry.NoteReason(reason);
            // Pass attribution costs two virtual Ogre calls plus a short string
            // walk on every traversal, which is real work on a path that runs
            // three times a frame. The counters above are a handful of
            // increments and stay unconditional; this part is opt-in.
            if (g_GenericChunkBatchRateDiagnostics)
            {
                g_GenericChunkBatchTelemetry.NoteScheme(
                    GetCurrentOgreMaterialSchemeName(sceneManager), wantRebuild);
            }

            if (!wantRebuild && !g_GenericChunkBatchReuseObserveOnly)
            {
                // The geometry already in the ManualObject is byte-identical to
                // what a rebuild would produce, so this traversal only needs the
                // submission. This is the whole optimization: one emit per
                // source-state change instead of one per camera/scheme pass.
                ++g_GenericChunkBatchTelemetry.reused;
                try
                {
                    if (!g_GenericChunkBatchVisible)
                    {
                        setVisible(g_GenericChunkBatchManualObject, true);
                        g_GenericChunkBatchVisible = true;
                    }
                    updateRenderQueue(g_GenericChunkBatchManualObject, renderQueue);
                }
                catch (...)
                {
                    LogChunkDiagnostic(
                        "chunkbatch",
                        L"[CHUNKBATCH] reuse submit threw; dropping cached batch\n");
                    g_GenericChunkBatchRuntimeAvailable = false;
                    g_GenericChunkBatchManualObject = nullptr;
                    // The recorded visibility described the object just dropped.
                    g_GenericChunkBatchVisible = false;
                    g_GenericChunkBatchSceneNode = nullptr;
                    g_GenericChunkBatchSectionCreated = false;
                    g_GenericChunkBatchBuiltVersion =
                        ChunkBatchInvalidation::kUnbuiltVersion;
                    return false;
                }
                return true;
            }

            // Observer mode still rebuilds, but the counters above already
            // recorded what reuse would have skipped.
            if (!wantRebuild)
                ++g_GenericChunkBatchTelemetry.reused;
            ++g_GenericChunkBatchTelemetry.rebuilds;
            g_GenericChunkBatchTelemetry.verticesRebuilt += vertexCount;
            g_GenericChunkBatchTelemetry.indicesRebuilt += vertexCount;
            const int64_t rebuildStartTicks = ReadChunkBatchQpc();

            bool updateStarted = false;
            try
            {
                if (!g_GenericChunkBatchManualObject)
                {
                    void* const rootNode = getRootSceneNode(sceneManager);
                    const OgreVector3 origin = { 0.0f, 0.0f, 0.0f };
                    const OgreQuaternion identity = { 1.0f, 0.0f, 0.0f, 0.0f };
                    g_GenericChunkBatchSceneNode = rootNode
                        ? createChildSceneNode(rootNode, origin, identity)
                        : nullptr;
                    g_GenericChunkBatchManualObject = createManualObject(sceneManager);
                    if (!g_GenericChunkBatchSceneNode ||
                        !g_GenericChunkBatchManualObject)
                    {
                        g_GenericChunkBatchRuntimeAvailable = false;
                        return false;
                    }
                    attachObject(
                        g_GenericChunkBatchSceneNode,
                        g_GenericChunkBatchManualObject);
                    setDynamic(g_GenericChunkBatchManualObject, true);
                    estimateVertices(
                        g_GenericChunkBatchManualObject,
                        static_cast<uint32_t>(
                            g_ChunkProxyCapacity * std::size(kChunk2Vertices)));
                    estimateIndices(
                        g_GenericChunkBatchManualObject,
                        static_cast<uint32_t>(
                            g_ChunkProxyCapacity * std::size(kChunk2Vertices)));
                    setCastShadows(g_GenericChunkBatchManualObject, false);
                    LogChunkDiagnostic(
                        "chunkbatch",
                        L"[CHUNKBATCH] initialized dynamic generic chunk batch capacity=%u material=scarpmat2\n",
                        g_ChunkProxyCapacity);
                }

                if (g_GenericChunkBatchSectionCreated)
                    beginUpdate(g_GenericChunkBatchManualObject, 0);
                else
                    begin(
                        g_GenericChunkBatchManualObject,
                        g_GenericChunkBatchMaterialName,
                        4,
                        g_GenericChunkBatchMaterialGroup);
                updateStarted = true;

                uint32_t nextIndex = 0;
                for (const ChunkProxySlot& slot : g_ChunkProxySlots)
                {
                    if (!slot.active || !slot.genericBatchTransformReady)
                        continue;
                    if (slot.genericBatchKind == 1)
                    {
                        AppendGenericChunkBatchGeometry(
                            g_GenericChunkBatchManualObject,
                            kChunk1Vertices,
                            std::size(kChunk1Vertices),
                            slot.genericBatchTransform,
                            nextIndex,
                            position,
                            normal,
                            tangent,
                            textureCoord,
                            addIndex);
                    }
                    else
                    {
                        AppendGenericChunkBatchGeometry(
                            g_GenericChunkBatchManualObject,
                            kChunk2Vertices,
                            std::size(kChunk2Vertices),
                            slot.genericBatchTransform,
                            nextIndex,
                            position,
                            normal,
                            tangent,
                            textureCoord,
                            addIndex);
                    }
                }
                end(g_GenericChunkBatchManualObject);
                updateStarted = false;
                g_GenericChunkBatchSectionCreated = true;
                // Only stamp the version once the emit has actually completed.
                // A throw between begin and end leaves the object half-built,
                // and the catch below clears the stamp so the next call cannot
                // mistake that wreckage for valid cached geometry.
                g_GenericChunkBatchBuiltVersion = sourceVersion.Value();
                g_GenericChunkBatchBuiltMaterial = g_GenericChunkBatchMaterialName;
                NoteChunkBatchRebuildCost(rebuildStartTicks);
                if (!g_GenericChunkBatchVisible)
                {
                    setVisible(g_GenericChunkBatchManualObject, true);
                    g_GenericChunkBatchVisible = true;
                }
                updateRenderQueue(g_GenericChunkBatchManualObject, renderQueue);
            }
            catch (...)
            {
                LogChunkDiagnostic(
                    "chunkbatch",
                    L"[CHUNKBATCH] Ogre batch update threw started=%u; falling back to per-entity chunks\n",
                    updateStarted ? 1u : 0u);
                g_GenericChunkBatchRuntimeAvailable = false;
                g_GenericChunkBatchManualObject = nullptr;
                // The recorded visibility described the object just dropped.
                g_GenericChunkBatchVisible = false;
                g_GenericChunkBatchSceneNode = nullptr;
                g_GenericChunkBatchSectionCreated = false;
                g_GenericChunkBatchBuiltVersion =
                    ChunkBatchInvalidation::kUnbuiltVersion;
                return false;
            }

            const DWORD now = GetTickCount();
            if (g_GenericChunkBatchLastLogTick == 0 ||
                static_cast<DWORD>(now - g_GenericChunkBatchLastLogTick) >= 1000)
            {
                g_GenericChunkBatchLastLogTick = now;
                LogChunkDiagnostic(
                    "chunkbatch",
                    L"[CHUNKBATCH] active=%zu vertices=%zu sections=1\n",
                    chunkCount,
                    vertexCount);

                // Diagnostic-only, once per second, never on the hot path.
                // Ogre resets ManualObject::mAABB only in clear(); beginUpdate()
                // leaves it alone, so the aggregate bounds are expected to grow
                // monotonically over a mission. Read Ogre's own box back and log
                // it beside the tight box, so the claim is measured not argued.
                static FnOgreManualObjectGetBoundingBox getBoundingBox =
                    ResolveOgreProc<FnOgreManualObjectGetBoundingBox>(
                        "?getBoundingBox@ManualObject@Ogre@@UBEABVAxisAlignedBox@2@XZ");
                static FnOgreManualObjectGetBoundingRadius getBoundingRadius =
                    ResolveOgreProc<FnOgreManualObjectGetBoundingRadius>(
                        "?getBoundingRadius@ManualObject@Ogre@@UBEMXZ");
                if (getBoundingBox && getBoundingRadius &&
                    g_GenericChunkBatchManualObject && chunkCount > 0)
                {
                    try
                    {
                        const float* const box = static_cast<const float*>(
                            getBoundingBox(g_GenericChunkBatchManualObject));
                        if (box)
                        {
                            const uint32_t extentEnum =
                                *reinterpret_cast<const uint32_t*>(box + 6);
                            const float radius = getBoundingRadius(
                                g_GenericChunkBatchManualObject);
                            LogChunkDiagnostic(
                                "chunkbatch",
                                L"[CHUNKBATCH] bounds ogre=(%.1f,%.1f,%.1f)-(%.1f,%.1f,%.1f)"
                                L" ogreSpan=(%.1f,%.1f,%.1f) extentEnum=%u radius=%.1f"
                                L" tight=(%.1f,%.1f,%.1f)-(%.1f,%.1f,%.1f)"
                                L" tightSpan=(%.1f,%.1f,%.1f)\n",
                                box[0], box[1], box[2],
                                box[3], box[4], box[5],
                                box[3] - box[0], box[4] - box[1], box[5] - box[2],
                                extentEnum, radius,
                                tightMin[0], tightMin[1], tightMin[2],
                                tightMax[0], tightMax[1], tightMax[2],
                                tightMax[0] - tightMin[0],
                                tightMax[1] - tightMin[1],
                                tightMax[2] - tightMin[2]);
                        }
                    }
                    catch (...)
                    {
                    }
                }
            }
            return true;
        }

        // Render-time injection: called from the game's own _updateRenderQueue
        // override (0x00679570), the only exe-side path that feeds Ogre's
        // RenderQueue. Adding our sub-entities to the queue passed here puts
        // chunk proxies in exactly the same queue, frame, and coordinate space
        // as the game's world geometry — no camera/viewport guesswork.
        void SubmitChunkProxiesToRenderQueue(void* renderQueue)
        {
            if (!renderQueue || !g_EnableChunkMeshProxy)
                return;
            if (!IsChunkManualSubmitEnabled())
                return;
            if (g_ChunkProxySlots.empty())
                return;

            const bool genericBatchSubmitted =
                RebuildAndSubmitGenericChunkBatch(renderQueue);
            if (g_GenericChunkBatchRateDiagnostics)
            {
                ++g_GenericChunkBatchSubmitCalls;
                if (genericBatchSubmitted)
                    ++g_GenericChunkBatchRebuilds;
                const DWORD rateNow = GetTickCount();
                if (g_GenericChunkBatchRateLogTick == 0)
                {
                    g_GenericChunkBatchRateLogTick = rateNow;
                }
                else if (static_cast<DWORD>(
                             rateNow - g_GenericChunkBatchRateLogTick) >= 1000)
                {
                    const DWORD windowMs = static_cast<DWORD>(
                        rateNow - g_GenericChunkBatchRateLogTick);
                    LogChunkDiagnostic(
                        "chunkbatch",
                        L"[CHUNKBATCH] rate windowMs=%lu submitCalls=%llu submissions=%llu\n",
                        static_cast<unsigned long>(windowMs),
                        static_cast<unsigned long long>(
                            g_GenericChunkBatchSubmitCalls -
                            g_GenericChunkBatchSubmitCallsAtLastLog),
                        static_cast<unsigned long long>(
                            g_GenericChunkBatchRebuilds -
                            g_GenericChunkBatchRebuildsAtLastLog));
                    LogGenericChunkBatchTelemetry(windowMs);
                    g_GenericChunkBatchRateLogTick = rateNow;
                    g_GenericChunkBatchSubmitCallsAtLastLog =
                        g_GenericChunkBatchSubmitCalls;
                    g_GenericChunkBatchRebuildsAtLastLog =
                        g_GenericChunkBatchRebuilds;
                }
            }
            if (!genericBatchSubmitted)
            {
                // Same frame, before the per-Entity loop below reads the slots.
                RehydrateGenericChunkBatchSlotsToEntities(
                    g_ForceGenericChunkBatchFailure ? L"forced" : L"batch-unavailable");
            }

            static FnOgreRenderQueueAddRenderablePriority addRenderablePriority =
                ResolveOgreProcByOffset<FnOgreRenderQueueAddRenderablePriority>(0x00026850);
            static FnOgreGetRenderQueueGroup getRenderQueueGroup =
                ResolveOgreProcByOffset<FnOgreGetRenderQueueGroup>(0x0001584D);
            static FnOgreGetNumSubEntities getNumSubEntities =
                ResolveOgreProc<FnOgreGetNumSubEntities>("?getNumSubEntities@Entity@Ogre@@QBEIXZ");
            static FnOgreGetSubEntity getSubEntity =
                ResolveOgreProc<FnOgreGetSubEntity>("?getSubEntity@Entity@Ogre@@QBEPAVSubEntity@2@I@Z");

            if (!addRenderablePriority || !getNumSubEntities || !getSubEntity)
            {
                static volatile long s_MissingProcLogBudget = 2;
                if (InterlockedDecrement(&s_MissingProcLogBudget) >= 0)
                {
                    LogChunkDiagnostic(
                        "chunkmesh",
                        L"[CHUNKMESH] world-rq-submit procs-missing add=%u numSub=%u getSub=%u\n",
                        addRenderablePriority ? 1u : 0u,
                        getNumSubEntities ? 1u : 0u,
                        getSubEntity ? 1u : 0u);
                }
                return;
            }

            for (ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (genericBatchSubmitted &&
                    slot.genericBatchTransformReady)
                {
                    continue;
                }
                if (!slot.active || !slot.entity)
                    continue;

                bool groupFaulted = false;
                const uint8_t groupId =
                    TryGetChunkProxyRenderQueueGroupSafe(slot.entity, getRenderQueueGroup, &groupFaulted);
                if (groupFaulted)
                {
                    ForgetChunkProxySlotOgreRefs(slot);
                    continue;
                }
                bool countFaulted = false;
                const uint32_t subEntityCount = TryGetChunkProxySubEntityCountSafe(
                    slot.entity, getNumSubEntities, &countFaulted);
                if (countFaulted)
                {
                    ForgetChunkProxySlotOgreRefs(slot);
                    continue;
                }
                uint32_t added = 0;

                bool slotWentStale = false;
                for (uint32_t index = 0; index < subEntityCount; ++index)
                {
                    void* const subEntity =
                        TryGetChunkProxySubEntitySafe(slot.entity, index, getSubEntity);
                    // A live Entity never returns null below its own count.
                    // Bail out instead of faulting once per remaining index.
                    if (!subEntity)
                    {
                        slotWentStale = true;
                        break;
                    }

                    if (!TryAddChunkProxyRenderableSafe(
                            renderQueue,
                            subEntity,
                            groupId,
                            100u,
                            addRenderablePriority))
                    {
                        static volatile long s_StaleSubEntityLogBudget = 8;
                        if (InterlockedDecrement(&s_StaleSubEntityLogBudget) >= 0)
                        {
                            LogChunkDiagnostic(
                                "chunkmesh",
                                L"[CHUNKMESH] world-rq-submit rejected stale sub-entity entity=0x%08X subEntity=0x%08X\n",
                                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(subEntity)));
                        }
                        ForgetChunkProxySlotOgreRefs(slot);
                        break;
                    }
                    ++added;
                    if (slot.renderQueueAddCount < USHRT_MAX)
                        ++slot.renderQueueAddCount;
                }
                if (slotWentStale)
                {
                    static volatile long s_StaleEntityLogBudget = 8;
                    if (InterlockedDecrement(&s_StaleEntityLogBudget) >= 0)
                    {
                        LogChunkDiagnostic(
                            "chunkmesh",
                            L"[CHUNKMESH] world-rq-submit stale entity=0x%08X dropped after %u/%u sub-entities\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                            added,
                            subEntityCount);
                    }
                    ForgetChunkProxySlotOgreRefs(slot);
                    continue;
                }

                static volatile long s_FirstWorldRqSubmitLogBudget = 12;
                if (added != 0 && slot.renderQueueAddCount <= 8 &&
                    InterlockedDecrement(&s_FirstWorldRqSubmitLogBudget) >= 0)
                {
                    LogChunkDiagnostic(
                        "chunkmesh",
                        L"[CHUNKMESH] world-rq-submit entity=0x%08X mesh=%hs queue=0x%08X group=%u added=%u totalAdds=%u\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                        GetChunkPayloadMeshName(slot),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(renderQueue)),
                        static_cast<unsigned>(groupId),
                        added,
                        static_cast<unsigned>(slot.renderQueueAddCount));
                }
            }
        }

        // Pieces the simulation still fragments but the Redux model no longer
        // renders separately. Each was verified against the shipped .mesh in
        // Blender, and there is no geometry to draw for any of them -- a proxy
        // here can only ever be a generic rock or a billboard standing in for
        // something that is already gone. Suppressing is closer to the legacy
        // look than inventing debris.
        //
        // Keyed on the ODF name, which is the craft identity the engine states
        // outright, so a faction twin sharing a piece name is unaffected.
        struct SuppressedChunkPiece
        {
            const char* odfName;
            const char* geomName;
            const char* reason;
        };

        static constexpr SuppressedChunkPiece kSuppressedChunkPieces[] = {
            // abhang models two door panels of 88 verts where bbhang models four
            // of 44 -- same 176 total, so doors C and D are already inside the
            // geometry that flies off as abh11dra/abh11drb.
            { "abhang", "abh11drc", "merged into abh11dra/abh11drb" },
            { "abhang", "abh11drd", "merged into abh11dra/abh11drb" },
            // Bone exists but carries 4 verts and zero complete faces.
            { "abhang", "abh11bli", "degenerate: 4 verts, 0 faces" },
            // No such bone in abspow.mesh at all (21 geometry bones, none is bul).
            { "abspow", "asp11bul", "absent from abspow.mesh" },
            { "bbspow", "asp11bul", "absent from abspow.mesh" },
        };

        static const SuppressedChunkPiece* FindSuppressedChunkPiece(const char* geomName)
        {
            if (!geomName || !*geomName || !g_ActiveFragmentSourceOdfName[0])
                return nullptr;

            for (const SuppressedChunkPiece& entry : kSuppressedChunkPieces)
            {
                if (_stricmp(entry.odfName, g_ActiveFragmentSourceOdfName) == 0 &&
                    _stricmp(entry.geomName, geomName) == 0)
                {
                    return &entry;
                }
            }

            return nullptr;
        }

        static void TrackChunkProxyDebugEntry(
            const uint8_t* objectBytes,
            const void* geomRef,
            const char* geomName,
            float positionX,
            float positionY,
            float positionZ)
        {
            if ((!g_EnableChunkProxyDebug && !g_EnableChunkMeshProxy) || !objectBytes)
                return;

            // Before a slot is taken: no slot means no mesh and no billboard,
            // which is the whole point -- an empty payload name still draws a
            // billboard sprite.
            if (const SuppressedChunkPiece* suppressed = FindSuppressedChunkPiece(geomName))
            {
                static volatile long s_SuppressedPieceLogBudget = 32;
                if (InterlockedDecrement(&s_SuppressedPieceLogBudget) >= 0)
                {
                    LogChunkDiagnostic(
                        "chunkmesh",
                        L"[CHUNKMESH] suppressed geom=%hs odf=%hs reason=%hs\n",
                        geomName,
                        g_ActiveFragmentSourceOdfName,
                        suppressed->reason);
                }
                return;
            }

            if (g_ChunkProxySlots.size() != g_ChunkProxyCapacity)
                g_ChunkProxySlots.resize(g_ChunkProxyCapacity);

            ChunkProxySlot* freeSlot = nullptr;
            const DWORD now = GetTickCount();
            for (ChunkProxySlot& slot : g_ChunkProxySlots)
            {
                if (slot.active && slot.objectBytes == objectBytes)
                {
                    char resolvedMeshName[sizeof(slot.proofMeshName)] = {};
                    ChunkObjectLinkProbe probe = {};
                    CaptureChunkObjectLinkProbe(objectBytes, probe);
                    const ChunkBridgeSnapshot bridgeSnapshot = CaptureChunkBridgeSnapshot(objectBytes);
                    const char* preferredMeshName =
                        probe.cachedMeshName[0] ? probe.cachedMeshName : bridgeSnapshot.ownerResolvedMeshName;
                    slot.geomRef = geomRef;
                    if (geomName && *geomName)
                    {
                        strncpy_s(slot.geomName, geomName, _TRUNCATE);
                    }
                    else
                    {
                        slot.geomName[0] = '\0';
                    }
                    slot.positionX = positionX;
                    slot.positionY = positionY;
                    slot.positionZ = positionZ;
                    slot.useEntryPosition = true;
                    slot.ownerEntity = bridgeSnapshot.ownerEntity;
                    if (bridgeSnapshot.ownerEntityBaseName[0])
                        strncpy_s(slot.ownerEntityBaseName, bridgeSnapshot.ownerEntityBaseName, _TRUNCATE);
                    else
                        slot.ownerEntityBaseName[0] = '\0';
                    if (bridgeSnapshot.ownerOgreFilename[0])
                        strncpy_s(slot.ownerOgreFilename, bridgeSnapshot.ownerOgreFilename, _TRUNCATE);
                    else
                        slot.ownerOgreFilename[0] = '\0';
                    TryResolveChunkPayloadMeshResource(
                        probe,
                        preferredMeshName,
                        slot.geomName,
                        resolvedMeshName,
                        sizeof(resolvedMeshName));

                    if (_stricmp(slot.proofMeshName, resolvedMeshName) != 0)
                    {
                        InvalidateChunkMeshProxySlot(slot);
                        strncpy_s(slot.proofMeshName, sizeof(slot.proofMeshName), resolvedMeshName, _TRUNCATE);
                    }
                    slot.lastSeenTick = now;
                    return;
                }

                if (!slot.active && !freeSlot)
                    freeSlot = &slot;
            }

            if (!freeSlot)
                return;

            freeSlot->objectBytes = objectBytes;
            freeSlot->geomRef = geomRef;
            ChunkObjectLinkProbe probe = {};
            CaptureChunkObjectLinkProbe(objectBytes, probe);
            const ChunkBridgeSnapshot bridgeSnapshot = CaptureChunkBridgeSnapshot(objectBytes);
            const char* preferredMeshName =
                probe.cachedMeshName[0] ? probe.cachedMeshName : bridgeSnapshot.ownerResolvedMeshName;
            if (geomName && *geomName)
            {
                strncpy_s(freeSlot->geomName, geomName, _TRUNCATE);
            }
            else
            {
                freeSlot->geomName[0] = '\0';
            }
            freeSlot->positionX = positionX;
            freeSlot->positionY = positionY;
            freeSlot->positionZ = positionZ;
            freeSlot->useEntryPosition = true;
            freeSlot->ownerEntity = bridgeSnapshot.ownerEntity;
            if (bridgeSnapshot.ownerEntityBaseName[0])
                strncpy_s(freeSlot->ownerEntityBaseName, bridgeSnapshot.ownerEntityBaseName, _TRUNCATE);
            else
                freeSlot->ownerEntityBaseName[0] = '\0';
            if (bridgeSnapshot.ownerOgreFilename[0])
                strncpy_s(freeSlot->ownerOgreFilename, bridgeSnapshot.ownerOgreFilename, _TRUNCATE);
            else
                freeSlot->ownerOgreFilename[0] = '\0';
            if (!TryResolveChunkPayloadMeshResource(
                    probe,
                    preferredMeshName,
                    freeSlot->geomName,
                    freeSlot->proofMeshName,
                    sizeof(freeSlot->proofMeshName)))
            {
                freeSlot->proofMeshName[0] = '\0';
            }
            freeSlot->lastSeenTick = now;
            freeSlot->active = true;
            freeSlot->billboardAssigned = false;
            freeSlot->meshAssigned = false;
            if (AcquireChunkLogSlot())
            {
                LogChunkDiagnostic("chunkproxy", L"[CHUNKPROXY] tracking obj=0x%08X geom=0x%08X geomName=%hs geomKind=%hs ownerEntity=0x%08X ownerBase=%hs ownerFile=%hs mesh=%hs pos=(%.4f, %.4f, %.4f)\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectBytes)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(geomRef)),
                    GetChunkGeomNameForLog(geomName),
                    ClassifyChunkGeomName(geomName),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(freeSlot->ownerEntity)),
                    freeSlot->ownerEntityBaseName[0] ? freeSlot->ownerEntityBaseName : "<none>",
                    freeSlot->ownerOgreFilename[0] ? freeSlot->ownerOgreFilename : "<none>",
                    freeSlot->proofMeshName[0] ? freeSlot->proofMeshName : "<none>",
                    static_cast<double>(positionX),
                    static_cast<double>(positionY),
                    static_cast<double>(positionZ));
            }
            if (freeSlot->proofMeshName[0])
                UpdateChunkProxySlotPosition(*freeSlot);
        }

        void TrackChunkProxyDebugObject(
            const uint8_t* objectBytes,
            uint32_t objectType,
            const void* activeHandle,
            const BzrGeoLookup* lookup)
        {
            (void)objectBytes;
            (void)objectType;
            (void)activeHandle;
            (void)lookup;
        }

        bool TryReadChunkEffectEntry(
            const uint8_t* thisBytes,
            uint32_t index,
            ChunkEffectActiveEntry& outEntry)
        {
            if (!thisBytes)
                return false;

            const uintptr_t entryOffset = kChunkEffectEntryBaseOffset +
                (static_cast<uintptr_t>(index) * kChunkEffectEntrySize);
            __try
            {
                const auto* entryBytes = thisBytes + entryOffset;
                outEntry.objectBytes = *reinterpret_cast<const uint8_t* const*>(entryBytes + 0x00);
                outEntry.reserved = *reinterpret_cast<const uint32_t*>(entryBytes + 0x04);
                outEntry.timer = *reinterpret_cast<const float*>(entryBytes + 0x08);
                outEntry.velocityX = *reinterpret_cast<const float*>(entryBytes + 0x0C);
                outEntry.velocityY = *reinterpret_cast<const float*>(entryBytes + 0x10);
                outEntry.velocityZ = *reinterpret_cast<const float*>(entryBytes + 0x14);
                outEntry.omegaX = *reinterpret_cast<const float*>(entryBytes + 0x18);
                outEntry.omegaY = *reinterpret_cast<const float*>(entryBytes + 0x1C);
                outEntry.omegaZ = 0.0f;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void LogChunkEffectRuntimeSample(void* thisPtr, float dt)
        {
            if (!g_TraceChunkEffectRuntime || !thisPtr)
                return;

            const auto* thisBytes = reinterpret_cast<const uint8_t*>(thisPtr);
            __try
            {
                const uint32_t count = *reinterpret_cast<const uint32_t*>(thisBytes + kChunkEffectActiveCountOffset);
                const bool shouldLog =
                    g_TraceChunkRenderVerbose ||
                    count > 0 ||
                    count != g_LastChunkEffectLoggedCount;
                g_LastChunkEffectLoggedCount = count;
                if (!shouldLog || !AcquireChunkLogSlot())
                    return;

                const uint32_t gate = *reinterpret_cast<const uint32_t*>(thisBytes + kChunkEffectGateOffset);
                const uint32_t templateList = *reinterpret_cast<const uint32_t*>(thisBytes + kChunkEffectTemplateListOffset);
                const uint32_t templateCount = *reinterpret_cast<const uint32_t*>(thisBytes + kChunkEffectTemplateListOffset + 4);
                const float tuning8038 = *reinterpret_cast<const float*>(thisBytes + kChunkEffectTuningBaseOffset + 0x0);
                const float tuning8044 = *reinterpret_cast<const float*>(thisBytes + kChunkEffectTuningBaseOffset + 0xC);
                const float tuning8048 = *reinterpret_cast<const float*>(thisBytes + kChunkEffectTuningBaseOffset + 0x10);

                LogChunkDiagnostic("chunkeffect", L"[CHUNKEFFECT] this=0x%08X dt=%.4f count=%u gate=0x%08X templateList=0x%08X templateCount=%u tune8038=%.4f tune8044=%.4f tune8048=%.4f\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)),
                    static_cast<double>(dt),
                    count,
                    gate,
                    templateList,
                    templateCount,
                    static_cast<double>(tuning8038),
                    static_cast<double>(tuning8044),
                    static_cast<double>(tuning8048));

                const uint32_t entryLimit = (std::min)(count, g_ChunkTraceEntryLimit);
                for (uint32_t index = 0; index < entryLimit; ++index)
                {
                    ChunkEffectActiveEntry entry = {};
                    if (!TryReadChunkEffectEntry(thisBytes, index, entry))
                    {
                        LogChunkDiagnostic("chunkeffect", L"[CHUNKEFFECT]   entry[%u] fault\n", index);
                        continue;
                    }

                    uint32_t classId = 0;
                    uint32_t flags = 0;
                    uint32_t owner = 0;
                    float timer = 0.0f;
                    const void* geomRef = nullptr;
                    char geomName[64] = {};
                    __try
                    {
                        if (entry.objectBytes)
                        {
                            classId = *reinterpret_cast<const uint32_t*>(entry.objectBytes + 0x84);
                            flags = *reinterpret_cast<const uint32_t*>(entry.objectBytes + 0x14);
                            owner = *reinterpret_cast<const uint32_t*>(entry.objectBytes + 0x8C);
                            timer = *reinterpret_cast<const float*>(entry.objectBytes + 0xAC);
                        }
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                    }
                    TryReadChunkGeomIdentity(entry.objectBytes, geomRef, geomName, sizeof(geomName));

                    LogChunkDiagnostic("chunkeffect", L"[CHUNKEFFECT]   entry[%u] obj=0x%08X reserved=0x%08X classId=%u flags=0x%08X owner=0x%08X timer=%.6f geom=0x%08X geomName=%hs geomKind=%hs vel=(%.4f, %.4f, %.4f) omega=(%.4f, %.4f, %.4f)\n",
                        index,
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entry.objectBytes)),
                        entry.reserved,
                        classId,
                        flags,
                        owner,
                        static_cast<double>(timer),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(geomRef)),
                        GetChunkGeomNameForLog(geomName),
                        ClassifyChunkGeomName(geomName),
                        static_cast<double>(entry.velocityX),
                        static_cast<double>(entry.velocityY),
                        static_cast<double>(entry.velocityZ),
                        static_cast<double>(entry.omegaX),
                        static_cast<double>(entry.omegaY),
                        static_cast<double>(entry.omegaZ));
                }

                if (count > entryLimit)
                {
                    LogChunkDiagnostic("chunkeffect", L"[CHUNKEFFECT]   ... truncated %u additional entries\n",
                        count - entryLimit);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                LogChunkDiagnostic("chunkeffect", L"[CHUNKEFFECT] sample fault this=0x%08X code=0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)),
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        void TrackChunkEffectActiveEntries(void* thisPtr)
        {
            if ((!g_EnableChunkProxyDebug && !g_EnableChunkMeshProxy && !g_TraceChunkEffectRuntime) || !thisPtr)
                return;

            PruneChunkResolvedBindingsIfNeeded();

            const auto* thisBytes = reinterpret_cast<const uint8_t*>(thisPtr);
            __try
            {
                const uint32_t count = *reinterpret_cast<const uint32_t*>(thisBytes + kChunkEffectActiveCountOffset);
                for (uint32_t index = 0; index < count; ++index)
                {
                    ChunkEffectActiveEntry entry = {};
                    if (!TryReadChunkEffectEntry(thisBytes, index, entry))
                        continue;
                    if (!entry.objectBytes)
                        continue;

                    uint32_t classId = 0;
                    __try
                    {
                        classId = *reinterpret_cast<const uint32_t*>(entry.objectBytes + 0x84);
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        classId = 0;
                    }

                    if (classId != kClassIdChunk)
                        continue;

                    const void* geomRef = nullptr;
                    char geomName[64] = {};
                    TryReadChunkGeomIdentity(entry.objectBytes, geomRef, geomName, sizeof(geomName));

                    const ChunkResolvedBindingEntry* binding =
                        FindChunkResolvedBindingEntryForGeom(entry.objectBytes, geomName);
                    if (binding)
                        TouchChunkResolvedBinding(entry.objectBytes);
                    const ChunkBridgeSnapshot bridgeSnapshot = CaptureChunkBridgeSnapshot(entry.objectBytes);
                    float positionX = 0.0f;
                    float positionY = 0.0f;
                    float positionZ = 0.0f;
                    const void* resolvedPositionObject = nullptr;
                    if (!TryResolveChunkProxyPositionFromCandidates(
                            entry.objectBytes,
                            binding,
                            &bridgeSnapshot,
                            positionX,
                            positionY,
                            positionZ,
                            &resolvedPositionObject))
                    {
                        continue;
                    }

                    TrackChunkProxyDebugEntry(
                        entry.objectBytes,
                        geomRef,
                        geomName,
                        positionX,
                        positionY,
                        positionZ);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        ChunkBridgeSnapshot CaptureChunkBridgeSnapshot(const uint8_t* objectBytes)
        {
            ChunkBridgeSnapshot snapshot = {};
            if (!objectBytes)
                return snapshot;

            __try
            {
                snapshot.directBridgeRoot = *reinterpret_cast<void* const*>(objectBytes + 0xF0);
                if (snapshot.directBridgeRoot)
                {
                    const auto* bridgeBytes = reinterpret_cast<const uint8_t*>(snapshot.directBridgeRoot);
                    snapshot.directOgreEntity = *reinterpret_cast<void* const*>(bridgeBytes + 0x94);
                    snapshot.directOgreLight = *reinterpret_cast<void* const*>(bridgeBytes + 0xA8);
                }
                snapshot.directProbeOk = true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                snapshot.directProbeOk = false;
            }

            __try
            {
                // Legacy OBJ76 layouts observed in Redux helpers place the owning GameObject*
                // at +0x8C, which is the bridge we want to validate for native death chunks.
                snapshot.legacyOwner = *reinterpret_cast<void* const*>(objectBytes + 0x8C);
                if (snapshot.legacyOwner)
                {
                    const auto* ownerBytes = reinterpret_cast<const uint8_t*>(snapshot.legacyOwner);
                    snapshot.ownerBridgeRoot = *reinterpret_cast<void* const*>(ownerBytes + 0xF0);
                    snapshot.ownerEntity = *reinterpret_cast<void* const*>(ownerBytes + 0xF4);
                    snapshot.ownerObj = *reinterpret_cast<void* const*>(ownerBytes + 0xF8);

                    if (snapshot.ownerBridgeRoot)
                    {
                        const auto* bridgeBytes = reinterpret_cast<const uint8_t*>(snapshot.ownerBridgeRoot);
                        snapshot.ownerOgreEntity = *reinterpret_cast<void* const*>(bridgeBytes + 0x94);
                        snapshot.ownerOgreLight = *reinterpret_cast<void* const*>(bridgeBytes + 0xA8);
                    }
                }
                snapshot.ownerProbeOk = true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                snapshot.ownerProbeOk = false;
            }

            __try
            {
                snapshot.ownerNameProbeOk = TryReadOwnerEntityNames(
                    snapshot.ownerEntity,
                    snapshot.ownerEntityBaseName,
                    sizeof(snapshot.ownerEntityBaseName),
                    snapshot.ownerOgreFilename,
                    sizeof(snapshot.ownerOgreFilename),
                    snapshot.ownerResolvedMeshName,
                    sizeof(snapshot.ownerResolvedMeshName));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                snapshot.ownerEntityBaseName[0] = '\0';
                snapshot.ownerOgreFilename[0] = '\0';
                snapshot.ownerResolvedMeshName[0] = '\0';
                snapshot.ownerNameProbeOk = false;
            }

            return snapshot;
        }

        static void LogChunkClassProbe(const uint8_t* objectBytes)
        {
            if (!objectBytes)
                return;

            __try
            {
                // Redux's live OBJ76-like layout appears to preserve the legacy
                // parent/child/class/gameObj neighborhood, shifted down by 0x28:
                // legacy A0/A4/A8/AC/B0/B4 -> live 78/7C/80/84/88/8C.
                const void* parent = *reinterpret_cast<void* const*>(objectBytes + 0x78);
                const void* sibling = *reinterpret_cast<void* const*>(objectBytes + 0x7C);
                const void* child = *reinterpret_cast<void* const*>(objectBytes + 0x80);
                const uint32_t classId = *reinterpret_cast<const uint32_t*>(objectBytes + 0x84);
                const void* classPtr = *reinterpret_cast<void* const*>(objectBytes + 0x88);
                const void* gameObj = *reinterpret_cast<void* const*>(objectBytes + 0x8C);

                LogChunkDiagnostic("chunk", L"[CHUNK]   obj76Probe parent=0x%08X sibling=0x%08X child=0x%08X classId=0x%X classPtr=0x%08X gameObj=0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parent)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sibling)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(child)),
                    classId,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(classPtr)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(gameObj)));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                LogChunkDiagnostic("chunk", L"[CHUNK]   obj76Probe fault code=0x%08X\n",
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        static void LogChunkClassTransitionProbe(const uint8_t* objectBytes,
                                                uintptr_t objectKey,
                                                uint32_t previousClassId,
                                                uint32_t classId);

        void NoteChunkClassTransition(const uint8_t* objectBytes, uint32_t classId)
        {
            if (!g_TraceChunkRender || !objectBytes)
                return;

            constexpr size_t kMaxTrackedChunkClasses = 8192;

            const uintptr_t objectKey = reinterpret_cast<uintptr_t>(objectBytes);
            if (g_ChunkObservedClassIds.size() >= kMaxTrackedChunkClasses &&
                g_ChunkObservedClassIds.find(objectKey) == g_ChunkObservedClassIds.end())
            {
                g_ChunkObservedClassIds.clear();
            }

            auto [it, inserted] = g_ChunkObservedClassIds.emplace(objectKey, classId);
            if (inserted)
                return;

            const uint32_t previousClassId = it->second;
            if (previousClassId == classId)
                return;

            it->second = classId;

            LogChunkClassTransitionProbe(objectBytes, objectKey, previousClassId, classId);
        }

        static void LogChunkClassTransitionProbe(const uint8_t* objectBytes,
                                                uintptr_t objectKey,
                                                uint32_t previousClassId,
                                                uint32_t classId)
        {
            if (!AcquireChunkLogSlot())
                return;

            __try
            {
                const void* parent = *reinterpret_cast<void* const*>(objectBytes + 0x78);
                const void* sibling = *reinterpret_cast<void* const*>(objectBytes + 0x7C);
                const void* child = *reinterpret_cast<void* const*>(objectBytes + 0x80);
                const void* classPtr = *reinterpret_cast<void* const*>(objectBytes + 0x88);
                const void* gameObj = *reinterpret_cast<void* const*>(objectBytes + 0x8C);

                LogChunkDiagnostic("chunk", L"[CHUNK] classChange obj=0x%08X old=0x%X new=0x%X parent=0x%08X sibling=0x%08X child=0x%08X classPtr=0x%08X gameObj=0x%08X\n",
                    static_cast<uint32_t>(objectKey),
                    previousClassId,
                    classId,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parent)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sibling)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(child)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(classPtr)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(gameObj)));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                LogChunkDiagnostic("chunk", L"[CHUNK] classChange obj=0x%08X old=0x%X new=0x%X probe=fault code=0x%08X\n",
                    static_cast<uint32_t>(objectKey),
                    previousClassId,
                    classId,
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        void LogChunkResolveSnapshot(
            const char* stage,
            const char* reason,
            const uint8_t* objectBytes,
            uint32_t variant,
            uint32_t stockResolved,
            const void* activeBefore,
            const void* activeAfter,
            const BzrGeoLookup* lookup,
            int selectedIndex,
            uint32_t selectedKey)
        {
            if (!stage || !objectBytes)
                return;

            const uint32_t renderFlags = *reinterpret_cast<const uint32_t*>(objectBytes + 0x14);
            const uint32_t renderClass = renderFlags & 0xF000;
            const uint32_t objectType = *reinterpret_cast<const uint32_t*>(objectBytes + 0x84);
            const uint32_t lookupCount = lookup ? lookup->count : 0;
            const uint32_t cachedKey = lookup ? lookup->cachedKey : 0;
            const uintptr_t entriesPtr = lookup ? reinterpret_cast<uintptr_t>(lookup->entries) : 0;
            const ChunkBridgeSnapshot bridgeSnapshot = CaptureChunkBridgeSnapshot(objectBytes);

            LogChunkDiagnostic("chunk", L"[CHUNK] %hs obj=0x%08X variant=0x%08X resolved=0x%08X before=0x%08X after=0x%08X class=0x%04X classId=0x%X count=%u cached=0x%08X entries=0x%08X reason=%hs idx=%d key=0x%08X\n",
                stage,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectBytes)),
                variant,
                stockResolved,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(activeBefore)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(activeAfter)),
                renderClass,
                objectType,
                lookupCount,
                cachedKey,
                static_cast<uint32_t>(entriesPtr),
                reason ? reason : "-",
                selectedIndex,
                selectedKey);

            LogChunkDiagnostic("chunk", L"[CHUNK]   direct root=0x%08X entity=0x%08X light=0x%08X probe=%hs | owner=0x%08X ownerBridge=0x%08X ownerEntity=0x%08X ownerObj=0x%08X ownerOgre=0x%08X ownerLight=0x%08X ownerProbe=%hs ownerNameProbe=%hs ownerBase=%hs ownerFile=%hs ownerMesh=%hs\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.directBridgeRoot)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.directOgreEntity)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.directOgreLight)),
                bridgeSnapshot.directProbeOk ? "ok" : "fault",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.legacyOwner)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.ownerBridgeRoot)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.ownerEntity)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.ownerObj)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.ownerOgreEntity)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bridgeSnapshot.ownerOgreLight)),
                bridgeSnapshot.ownerProbeOk ? "ok" : "fault",
                bridgeSnapshot.ownerNameProbeOk ? "ok" : "fault",
                bridgeSnapshot.ownerEntityBaseName[0] ? bridgeSnapshot.ownerEntityBaseName : "<none>",
                bridgeSnapshot.ownerOgreFilename[0] ? bridgeSnapshot.ownerOgreFilename : "<none>",
                bridgeSnapshot.ownerResolvedMeshName[0] ? bridgeSnapshot.ownerResolvedMeshName : "<none>");

            LogChunkClassProbe(objectBytes);

            if (!lookup || !lookup->entries || lookup->count == 0)
                return;

            const uint32_t entryLimit = (std::min)(lookup->count, g_ChunkTraceEntryLimit);
            for (uint32_t index = 0; index < entryLimit; ++index)
            {
                const BzrGeoEntry& entry = lookup->entries[index];
                LogChunkDiagnostic("chunk", L"[CHUNK]   entry[%u] key=0x%08X handle=0x%08X unk8=0x%08X unkC=0x%08X%s\n",
                    index,
                    entry.packedKey,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entry.handle)),
                    entry.unk8,
                    entry.unkC,
                    (selectedIndex == static_cast<int>(index)) ? " <selected>" : "");
            }

            if (lookup->count > entryLimit)
            {
                LogChunkDiagnostic("chunk", L"[CHUNK]   ... truncated %u additional entries\n",
                    lookup->count - entryLimit);
            }
        }


        void InstallChunkEffectCreateHooksIfRequested()
        {
            if ((!g_TraceChunkRender && !g_TraceChunkEffectRuntime) || g_ChunkEffectCreateHooksInstalled)
                return;

            static const uint8_t kExpectedCreateChunkletBytes[kChunkEffectCreateExpectedLen] =
            {
                0x55, 0x8B, 0xEC, 0x81, 0xEC, 0xB8, 0x00, 0x00,
                0x00, 0xA1, 0x00, 0x70, 0x8E, 0x00, 0x33, 0xC5
            };
            static const uint8_t kExpectedCreateChunkBytes[kChunkEffectCreateExpectedLen] =
            {
                0x55, 0x8B, 0xEC, 0x81, 0xEC, 0xA8, 0x00, 0x00,
                0x00, 0xA1, 0x00, 0x70, 0x8E, 0x00, 0x33, 0xC5
            };

            if (g_IsSteamExe && !g_AllowUnsafeSteamChunkCreateHooks)
            {
                const ULONGLONG nowMs = GetTickCount64();
                if (g_ChunkEffectCreateHooksReadyTick != 0 && nowMs < g_ChunkEffectCreateHooksReadyTick)
                {
                    if (!g_ChunkEffectCreateHooksWaitLogged)
                    {
                        LogChunkDiagnostic(
                            "chunkspawn",
                            L"[CHUNKSPAWN] Steam creator hooks waiting %llums for settled-byte verification\n",
                            static_cast<unsigned long long>(g_ChunkEffectCreateHooksReadyTick - nowMs));
                        g_ChunkEffectCreateHooksWaitLogged = true;
                    }
                    return;
                }

                const bool createChunkBytesMatch =
                    ExpectedBytesMatchAt(
                        kGogChunkEffectCreateChunkAddr,
                        kExpectedCreateChunkBytes,
                        sizeof(kExpectedCreateChunkBytes));
                const bool createChunkletBytesMatch =
                    ExpectedBytesMatchAt(
                        kGogChunkEffectCreateChunkletAddr,
                        kExpectedCreateChunkletBytes,
                        sizeof(kExpectedCreateChunkletBytes));
                if (!createChunkBytesMatch || !createChunkletBytesMatch)
                {
                    if (!g_ChunkEffectCreateHooksMismatchLogged)
                    {
                        LogChunkDiagnostic(
                            "chunkspawn",
                            L"[CHUNKSPAWN] Steam creator hooks still waiting for settled bytes create=%hs chunklet=%hs\n",
                            createChunkBytesMatch ? "ok" : "mismatch",
                            createChunkletBytesMatch ? "ok" : "mismatch");
                        g_ChunkEffectCreateHooksMismatchLogged = true;
                    }
                    return;
                }
            }

            if (g_ChunkEffectCreateChunkDetour.trampoline && g_BzrFn_ChunkEffectCreateChunk &&
                g_ChunkEffectCreateChunkletDetour.trampoline && g_BzrFn_ChunkEffectCreateChunklet)
            {
                g_ChunkEffectCreateHooksInstalled = true;
            }
            else
            {
                if (!g_ChunkEffectCreateChunkDetour.trampoline)
                {
                    InstallInlineDetour32(
                        g_ChunkEffectCreateChunkDetour,
                        kGogChunkEffectCreateChunkAddr,
                        reinterpret_cast<void*>(ChunkEffectCreateChunkHook),
                        kChunkEffectCreateChunkDetourLen,
                        nullptr,
                        0);
                }
                if (g_ChunkEffectCreateChunkDetour.trampoline)
                {
                    g_BzrFn_ChunkEffectCreateChunk = reinterpret_cast<FnChunkEffectCreateChunk>(
                        g_ChunkEffectCreateChunkDetour.trampoline);
                }

                if (!g_ChunkEffectCreateChunkletDetour.trampoline)
                {
                    InstallInlineDetour32(
                        g_ChunkEffectCreateChunkletDetour,
                        kGogChunkEffectCreateChunkletAddr,
                        reinterpret_cast<void*>(ChunkEffectCreateChunkletHook),
                        kChunkEffectCreateChunkletDetourLen,
                        nullptr,
                        0);
                }
                if (g_ChunkEffectCreateChunkletDetour.trampoline)
                {
                    g_BzrFn_ChunkEffectCreateChunklet = reinterpret_cast<FnChunkEffectCreateChunklet>(
                        g_ChunkEffectCreateChunkletDetour.trampoline);
                }

                g_ChunkEffectCreateHooksInstalled =
                    g_ChunkEffectCreateChunkDetour.trampoline &&
                    g_BzrFn_ChunkEffectCreateChunk &&
                    g_ChunkEffectCreateChunkletDetour.trampoline &&
                    g_BzrFn_ChunkEffectCreateChunklet;
            }

            if (g_ChunkEffectCreateHooksInstalled && !g_ChunkEffectCreateHooksLogged)
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN] Installed create hooks create=0x%08X chunklet=0x%08X\n",
                    static_cast<uint32_t>(kGogChunkEffectCreateChunkAddr),
                    static_cast<uint32_t>(kGogChunkEffectCreateChunkletAddr));
                g_ChunkEffectCreateHooksLogged = true;
            }
        }

        // Diagnostic detours on ChunkEffect::PartialFragmentObject/FullFragmentObject
        // (the walkers Craft/Building explode paths hand the dying OBJ76 tree to).
        // Logs the tree each walk receives so "death produced no CreateChunk" can be
        // told apart from "walker never ran". GOG only; addresses are GOG layout.
        void InstallChunkFragmentWalkHooksIfRequested()
        {
            if ((!g_TraceChunkRender && !g_TraceChunkEffectRuntime) ||
                g_ChunkEffectFragmentHooksInstalled || g_IsSteamExe)
                return;

            static const uint8_t kExpectedPartialFragmentBytes[kChunkEffectFragmentDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x30
            };
            static const uint8_t kExpectedFullFragmentBytes[kChunkEffectFragmentDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x28
            };

            if (!g_ChunkEffectPartialFragmentDetour.trampoline)
            {
                InstallInlineDetour32(
                    g_ChunkEffectPartialFragmentDetour,
                    kGogChunkEffectPartialFragmentAddr,
                    reinterpret_cast<void*>(ChunkEffectPartialFragmentHook),
                    kChunkEffectFragmentDetourLen,
                    kExpectedPartialFragmentBytes,
                    sizeof(kExpectedPartialFragmentBytes));
            }
            if (g_ChunkEffectPartialFragmentDetour.trampoline)
            {
                g_BzrFn_ChunkEffectPartialFragment = reinterpret_cast<FnChunkEffectFragmentObject>(
                    g_ChunkEffectPartialFragmentDetour.trampoline);
            }

            if (!g_ChunkEffectFullFragmentDetour.trampoline)
            {
                InstallInlineDetour32(
                    g_ChunkEffectFullFragmentDetour,
                    kGogChunkEffectFullFragmentAddr,
                    reinterpret_cast<void*>(ChunkEffectFullFragmentHook),
                    kChunkEffectFragmentDetourLen,
                    kExpectedFullFragmentBytes,
                    sizeof(kExpectedFullFragmentBytes));
            }
            if (g_ChunkEffectFullFragmentDetour.trampoline)
            {
                g_BzrFn_ChunkEffectFullFragment = reinterpret_cast<FnChunkEffectFragmentObject>(
                    g_ChunkEffectFullFragmentDetour.trampoline);
            }

            g_ChunkEffectFragmentHooksInstalled =
                g_ChunkEffectPartialFragmentDetour.trampoline &&
                g_BzrFn_ChunkEffectPartialFragment &&
                g_ChunkEffectFullFragmentDetour.trampoline &&
                g_BzrFn_ChunkEffectFullFragment;

            if (g_ChunkEffectFragmentHooksInstalled && !g_ChunkEffectFragmentHooksLogged)
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN] Installed fragment walk hooks partial=0x%08X full=0x%08X\n",
                    static_cast<uint32_t>(kGogChunkEffectPartialFragmentAddr),
                    static_cast<uint32_t>(kGogChunkEffectFullFragmentAddr));
                g_ChunkEffectFragmentHooksLogged = true;
            }
        }
    }

}
