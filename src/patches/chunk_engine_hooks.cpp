// chunk_engine_hooks.cpp
// BZR Open Shim - chunk proxy engine hooks: the chunk render resolve
// hook, ChunkEffect create/chunklet and partial/full fragment hooks,
// owner-bone collapse and source-mesh hiding for detached pieces, and
// the geom byte dumps, split out of bzr_hooks.cpp.
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
        bool g_EnableChunkRenderFallback = false;
        bool g_EnablePartialFragmentBoneCollapse = false;

        // Guards against a craft mesh with an implausible bone count being walked.
        static constexpr uint16_t kMaxOwnerSkeletonBones = 1024;

        // Building geo nodes carry no owner GameObject link (+0x8C is null),
        // so chunks born from a building can't identify their craft through
        // the bridge. The fragment ROOT still can. FragmentObject calls
        // CreateChunk synchronously on the same thread, so the root's
        // resolved mesh name is handed down through this scoped global while
        // the walk is on the stack.
        char g_ActiveFragmentSourceMeshName[48] = {};

        // The craft's Ogre::Entity for the fragment walk currently on the stack.
        // Geo nodes below the root do not carry a bridge link of their own, so
        // the entity is resolved once at the root and handed down the same way
        // the mesh name is.
        static void* g_ActiveFragmentSourceOgreEntity = nullptr;

        static const char* g_ActiveFragmentSourceOgreEntityVia = "none";

        // ODF name of the craft being fragmented, read off its GameObject class.
        // The tagENTITY name probe never resolved a real name, so this is the
        // only stated (rather than inferred) identity the payload lookup gets.
        char g_ActiveFragmentSourceOdfName[16] = {};

        // Set only while PartialFragmentObject is on the stack. Full fragmentation
        // hides the whole source mesh instead, so per-piece bone collapse there
        // would be wasted work on an already-invisible entity.
        static bool g_ActivePartialFragment = false;

        static int g_ChunkFragmentHookDepth = 0;


    }

    using namespace Hooks;

    uint32_t __cdecl ChunkRenderResolveHook(void* objectPtr, uint32_t variant)
    {
        if (!objectPtr || !g_BzrFn_ChunkResolve)
            return 0;

        uint32_t resolved = g_BzrFn_ChunkResolve(objectPtr, variant);
        if (!g_EnableChunkRenderFallback &&
            !g_TraceChunkRender &&
            !g_TraceChunkRenderVerbose &&
            !g_EnableChunkProxyDebug &&
            !g_EnableChunkMeshProxy)
        {
            return resolved;
        }

        __try
        {
            constexpr uint32_t kMaxReasonableGeoEntries = 256;

            auto* objectBytes = reinterpret_cast<uint8_t*>(objectPtr);
            auto* activeHandle = reinterpret_cast<void**>(objectBytes + 0x64);
            auto* lookup = reinterpret_cast<BzrGeoLookup*>(objectBytes + 0x68);
            void* activeBefore = *activeHandle;
            const uint32_t objectType = *reinterpret_cast<const uint32_t*>(objectBytes + 0x84);
            NoteChunkClassTransition(objectBytes, objectType);

            const bool hasLookup =
                lookup && lookup->entries && lookup->count > 0 && lookup->count <= kMaxReasonableGeoEntries;
            const bool shouldTraceStock =
                g_TraceChunkRenderVerbose ||
                (g_TraceChunkRender &&
                    ((hasLookup && (resolved == 0 || activeBefore == nullptr)) ||
                     objectType == kClassIdChunk));

            if (shouldTraceStock && AcquireChunkLogSlot())
            {
                LogChunkResolveSnapshot(
                    "stock",
                    hasLookup ? "post-stock" :
                        (objectType == kClassIdChunk ? "class-id-chunk-no-lookup" : "lookup-missing-or-invalid"),
                    objectBytes,
                    variant,
                    resolved,
                    activeBefore,
                    *activeHandle,
                    lookup,
                    -1,
                    0);
            }

            if (*activeHandle != nullptr && hasLookup)
                TrackChunkProxyDebugObject(objectBytes, objectType, *activeHandle, lookup);

            if (resolved != 0 && *activeHandle != nullptr)
                return resolved;

            if (!g_EnableChunkRenderFallback)
                return resolved;

            if (!hasLookup)
                return resolved;

            int selectedIndex = -1;
            const char* selectionReason = "no-handle-entry";

            if (resolved != 0)
            {
                selectedIndex = FindChunkGeoEntryByKey(lookup, resolved);
                if (selectedIndex >= 0)
                    selectionReason = "matched-stock-key";
            }

            if (selectedIndex < 0 && lookup->cachedKey != 0)
            {
                selectedIndex = FindChunkGeoEntryByKey(lookup, lookup->cachedKey);
                if (selectedIndex >= 0)
                    selectionReason = "matched-cached-key";
            }

            if (selectedIndex < 0 && variant != 0)
            {
                selectedIndex = FindChunkGeoEntryByKey(lookup, variant);
                if (selectedIndex >= 0)
                    selectionReason = "matched-variant";
            }

            if (selectedIndex < 0)
            {
                selectedIndex = FindFirstChunkGeoEntryWithHandle(lookup);
                if (selectedIndex >= 0)
                    selectionReason = "first-handle";
            }

            if (selectedIndex < 0)
            {
                if (g_TraceChunkRender && AcquireChunkLogSlot())
                {
                    LogChunkResolveSnapshot(
                        "forced",
                        selectionReason,
                        objectBytes,
                        variant,
                        resolved,
                        activeBefore,
                        *activeHandle,
                        lookup,
                        -1,
                        0);
                }
                return resolved;
            }

            BzrGeoEntry& entry = lookup->entries[selectedIndex];
            *activeHandle = entry.handle;
            lookup->cachedKey = entry.packedKey;

            if (AcquireChunkLogSlot())
            {
                LogChunkResolveSnapshot(
                    "forced",
                    selectionReason,
                    objectBytes,
                    variant,
                    resolved,
                    activeBefore,
                    *activeHandle,
                    lookup,
                    selectedIndex,
                    entry.packedKey);
            }

            if (*activeHandle != nullptr)
                TrackChunkProxyDebugObject(objectBytes, objectType, *activeHandle, lookup);

            return entry.packedKey != 0 ? entry.packedKey : (resolved != 0 ? resolved : 1u);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            if (AcquireChunkLogSlot())
            {
                LogChunkDiagnostic("chunk", L"[CHUNK] Resolve hook exception obj=0x%08X variant=0x%08X resolved=0x%08X code=0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectPtr)),
                    variant,
                    resolved,
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        return resolved;
    }

    static volatile long g_ChunkGeomDumpFragmentBudget = 8;
    static volatile long g_ChunkGeomDumpChunkletBudget = 2;

    static bool TryCopyBytesSeh(const void* src, void* dst, size_t len)
    {
        __try
        {
            memcpy(dst, src, len);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    // One-shot layout probe for the structure at obj+0x64: hex-dumps the first
    // 0x60 bytes and ASCII-probes every dword that looks like a heap/module
    // pointer, so the real geo-name field can be located from a live session.
    static void DumpChunkGeomBytes(const char* tag, const void* geomPtr, volatile long* budget)
    {
        // Diagnostic only: the dword probe below deliberately dereferences
        // floats and indices as pointers, so every call takes first-chance
        // faults. Never run it without an explicit chunk trace request.
        if (!g_ChunkEventLogging || !geomPtr || !budget || InterlockedDecrement(budget) < 0)
            return;

        uint8_t raw[0x60] = {};
        if (!TryCopyBytesSeh(geomPtr, raw, sizeof(raw)))
        {
            LogChunkDiagnostic(
                "chunkspawn",
                L"[CHUNKSPAWN] geom-dump tag=%hs geom=0x%08X unreadable\n",
                tag ? tag : "?",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(geomPtr)));
            return;
        }

        wchar_t hex[sizeof(raw) * 3 + 1] = {};
        for (size_t i = 0; i < sizeof(raw); ++i)
        {
            static const wchar_t kDigits[] = L"0123456789ABCDEF";
            hex[i * 3 + 0] = kDigits[raw[i] >> 4];
            hex[i * 3 + 1] = kDigits[raw[i] & 0xF];
            hex[i * 3 + 2] = L' ';
        }
        hex[sizeof(raw) * 3] = L'\0';

        LogChunkDiagnostic(
            "chunkspawn",
            L"[CHUNKSPAWN] geom-dump tag=%hs geom=0x%08X bytes=%ls\n",
            tag ? tag : "?",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(geomPtr)),
            hex);

        for (size_t off = 0; off + 4 <= sizeof(raw); off += 4)
        {
            const uint32_t value = *reinterpret_cast<const uint32_t*>(raw + off);
            if (value < 0x10000 || value >= 0x7FFF0000)
                continue;

            char text[40] = {};
            if (TryReadInlineAsciiBuffer(reinterpret_cast<const void*>(static_cast<uintptr_t>(value)),
                                         sizeof(text) - 1,
                                         text,
                                         sizeof(text)) &&
                std::strlen(text) >= 3)
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN]   geom-deref tag=%hs off=0x%02X ptr=0x%08X text=%hs\n",
                    tag ? tag : "?",
                    static_cast<uint32_t>(off),
                    value,
                    text);
            }
        }

        // The dword at geom+0x00 points into a 0x18-byte-stride name table
        // (chunk2's slot holds inline ASCII, craft-piece slots don't).
        // Hex-dump the raw slot bytes so the actual encoding is visible.
        const uint32_t nameRef = *reinterpret_cast<const uint32_t*>(raw);
        if (nameRef >= 0x10000 && nameRef < 0x7FFF0000)
        {
            uint8_t slot[0x30] = {};
            if (TryCopyBytesSeh(reinterpret_cast<const void*>(static_cast<uintptr_t>(nameRef)),
                                slot,
                                sizeof(slot)))
            {
                wchar_t slotHex[sizeof(slot) * 3 + 1] = {};
                for (size_t i = 0; i < sizeof(slot); ++i)
                {
                    static const wchar_t kDigits[] = L"0123456789ABCDEF";
                    slotHex[i * 3 + 0] = kDigits[slot[i] >> 4];
                    slotHex[i * 3 + 1] = kDigits[slot[i] & 0xF];
                    slotHex[i * 3 + 2] = L' ';
                }
                slotHex[sizeof(slot) * 3] = L'\0';
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN]   geom-name-slot tag=%hs target=0x%08X bytes=%ls\n",
                    tag ? tag : "?",
                    nameRef,
                    slotHex);
            }
            else
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN]   geom-name-slot tag=%hs target=0x%08X unreadable\n",
                    tag ? tag : "?",
                    nameRef);
            }
        }
    }

    static volatile long g_PartialFragmentBoneCollapseLogBudget = 24;

    // The bridge offsets are only sometimes populated on the objects the fragment
    // hooks see -- a fragment root is not always the same node the renderer keeps
    // the craft's entity on. Try every route to the entity and take the first that
    // is actually an Ogre object, rather than trusting a single offset:
    //   direct/owner  - the bridge hanging off this node, when it has one
    //   gameobj       - round-trip out to the owning GameObject and back to the
    //                   node the renderer uses, which is the path the skinning
    //                   sweep walks and the only one proven to work for every craft
    static void* ResolveCraftOgreEntity(void* objectPtr, const char*& outVia)
    {
        outVia = "none";
        if (!objectPtr)
            return nullptr;

        const ChunkBridgeSnapshot snapshot =
            CaptureChunkBridgeSnapshot(reinterpret_cast<const uint8_t*>(objectPtr));
        if (LooksLikeOgreObject(snapshot.directOgreEntity))
        {
            outVia = "direct";
            return snapshot.directOgreEntity;
        }
        if (LooksLikeOgreObject(snapshot.ownerOgreEntity))
        {
            outVia = "owner";
            return snapshot.ownerOgreEntity;
        }

        void* gameObject = nullptr;
        if (!TryGetGameObjectFromObj76(objectPtr, gameObject) || !gameObject)
            return nullptr;

        void* liveObj76 = nullptr;
        if (!TryGetGameObjectObj76(gameObject, liveObj76) || !liveObj76 || liveObj76 == objectPtr)
            return nullptr;

        const ChunkBridgeSnapshot liveSnapshot =
            CaptureChunkBridgeSnapshot(reinterpret_cast<const uint8_t*>(liveObj76));
        if (LooksLikeOgreObject(liveSnapshot.directOgreEntity))
        {
            outVia = "gameobj";
            return liveSnapshot.directOgreEntity;
        }
        if (LooksLikeOgreObject(liveSnapshot.ownerOgreEntity))
        {
            outVia = "gameobj-owner";
            return liveSnapshot.ownerOgreEntity;
        }

        return nullptr;
    }

    // Raw Ogre calls kept in their own frame so a bad entity/skeleton pointer
    // cannot take the fragment walk down with it. No named C++ objects here:
    // __try cannot coexist with object unwinding.
    static bool TryCollapseOwnerBoneSeh(
        FnOgreEntityGetSkeleton getSkeleton,
        FnOgreEntityU16Query getNumBones,
        FnOgreSkeletonGetBoneByIndex getBoneByIndex,
        FnOgreStringQuery getBoneName,
        FnOgreBoneSetManuallyControlled setManuallyControlled,
        FnOgreNodeSetScale setScale,
        void* ownerEntity,
        const char* geomName,
        uint16_t& outBoneIndex,
        uint16_t& outBoneCount)
    {
        __try
        {
            void* const skeleton = getSkeleton(ownerEntity);
            if (!skeleton)
                return false;

            const uint16_t boneCount = getNumBones(skeleton);
            outBoneCount = boneCount;
            if (boneCount == 0 || boneCount > kMaxOwnerSkeletonBones)
                return false;

            for (uint16_t index = 0; index < boneCount; ++index)
            {
                void* const bone = getBoneByIndex(skeleton, index);
                if (!bone)
                    continue;

                if (_stricmp(getBoneName(bone).c_str(), geomName) != 0)
                    continue;

                // Manual control stops the skeleton's animation pass restoring
                // the bone next frame; the zero scale is what actually removes
                // the piece's vertices.
                setManuallyControlled(bone, true);
                setScale(bone, 0.0f, 0.0f, 0.0f);
                outBoneIndex = index;
                return true;
            }

            return false;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    // Partial fragmentation detaches individual geos while the hull keeps
    // rendering. The legacy engine unparented each detached geo from the craft's
    // object tree, so it stopped drawing on the model the same frame its debris
    // appeared. Redux bakes the whole craft into a single skinned Ogre mesh that
    // cannot unparent anything, so the piece stays welded to the body until
    // FullFragmentObject hides the entire mesh — a tank flies its blown-off wing
    // away while a second copy rides along on the hull.
    //
    // Every stock craft mesh skins each geo rigidly to one identically-named bone
    // (all vertex weights are exactly 1.0), so zeroing that bone removes exactly
    // the piece that just detached. Ogre propagates scale down the bone tree,
    // which matches the legacy semantics: unparenting a geo took its children
    // with it, and those children spawn as their own chunks anyway.
    static void CollapseOwnerBoneForDetachedPiece(const ChunkCreateSourceTreeProbe& probe)
    {
        if (!g_EnablePartialFragmentBoneCollapse || !g_ActivePartialFragment)
            return;
        if (!probe.valid || !probe.source.geomName[0])
            return;

        // probe.ownerEntity is the game-side tagENTITY, not an Ogre object, so it
        // can never answer getSkeleton. The bridge on the geo node itself is the
        // next best thing, and the root-scoped entity is the backstop; every
        // candidate is vetted before any Ogre call is made on it.
        const char* entityVia = "none";
        const char* entitySource = "node";
        void* ownerOgreEntity =
            ResolveCraftOgreEntity(const_cast<void*>(static_cast<const void*>(probe.source.objectBytes)), entityVia);
        if (!ownerOgreEntity)
        {
            entitySource = "root";
            ownerOgreEntity = g_ActiveFragmentSourceOgreEntity;
            entityVia = g_ActiveFragmentSourceOgreEntityVia;
        }
        if (!ownerOgreEntity)
        {
            if (InterlockedDecrement(&g_PartialFragmentBoneCollapseLogBudget) >= 0)
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN] bone-collapse geo=%hs skipped=no-owner-entity\n",
                    probe.source.geomName);
            }
            return;
        }

        static FnOgreEntityGetSkeleton getSkeleton =
            ResolveOgreProc<FnOgreEntityGetSkeleton>("?getSkeleton@Entity@Ogre@@QBEPAVSkeletonInstance@2@XZ");
        static FnOgreEntityU16Query getNumBones =
            ResolveOgreProc<FnOgreEntityU16Query>("?getNumBones@Skeleton@Ogre@@UBEGXZ");
        static FnOgreSkeletonGetBoneByIndex getBoneByIndex =
            ResolveOgreProc<FnOgreSkeletonGetBoneByIndex>("?getBone@Skeleton@Ogre@@UBEPAVBone@2@G@Z");
        static FnOgreStringQuery getBoneName =
            ResolveOgreProc<FnOgreStringQuery>("?getName@Node@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
        static FnOgreBoneSetManuallyControlled setManuallyControlled =
            ResolveOgreProc<FnOgreBoneSetManuallyControlled>("?setManuallyControlled@Bone@Ogre@@QAEX_N@Z");
        static FnOgreNodeSetScale setScale =
            ResolveOgreProc<FnOgreNodeSetScale>("?setScale@Node@Ogre@@UAEXMMM@Z");

        if (!getSkeleton || !getNumBones || !getBoneByIndex || !getBoneName ||
            !setManuallyControlled || !setScale)
        {
            static bool s_ProcFailureLogged = false;
            if (!s_ProcFailureLogged)
            {
                s_ProcFailureLogged = true;
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN] bone-collapse unavailable; skeleton procs unresolved\n");
            }
            return;
        }

        uint16_t boneIndex = 0;
        uint16_t boneCount = 0;
        const bool collapsed = TryCollapseOwnerBoneSeh(
            getSkeleton,
            getNumBones,
            getBoneByIndex,
            getBoneName,
            setManuallyControlled,
            setScale,
            ownerOgreEntity,
            probe.source.geomName,
            boneIndex,
            boneCount);

        if (InterlockedDecrement(&g_PartialFragmentBoneCollapseLogBudget) >= 0)
        {
            LogChunkDiagnostic(
                "chunkspawn",
                L"[CHUNKSPAWN] bone-collapse geo=%hs entity=0x%08X from=%hs via=%hs bones=%u %hs=%u\n",
                probe.source.geomName,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ownerOgreEntity)),
                entitySource,
                entityVia,
                static_cast<uint32_t>(boneCount),
                collapsed ? "boneIndex" : "unmatched",
                static_cast<uint32_t>(boneIndex));
        }
    }

    void* __fastcall ChunkEffectCreateChunkHook(void* thisPtr,
                                                void* /*edx*/,
                                                void* objectPtr,
                                                const float* velocity,
                                                uint8_t preserveFlag)
    {
        if (!g_BzrFn_ChunkEffectCreateChunk)
            return nullptr;

        const auto* thisBytes = reinterpret_cast<const uint8_t*>(thisPtr);
        uint32_t countBefore = 0;
        TryReadChunkEffectCount(thisBytes, countBefore);

        ChunkCreateSourceTreeProbe sourceTreeProbe = {};
        CaptureChunkCreateSourceTreeProbe(reinterpret_cast<const uint8_t*>(objectPtr), sourceTreeProbe);

        void* result = g_BzrFn_ChunkEffectCreateChunk(thisPtr, objectPtr, velocity, preserveFlag);

        uint32_t countAfter = countBefore;
        TryReadChunkEffectCount(thisBytes, countAfter);

        ChunkEffectActiveEntry createdEntry = {};
        const ChunkEffectActiveEntry* createdEntryPtr = nullptr;
        if (countAfter > countBefore)
        {
            if (TryReadChunkEffectEntry(thisBytes, countBefore, createdEntry))
                createdEntryPtr = &createdEntry;
        }

        const uint8_t* boundObjectBytes = nullptr;
        if (createdEntryPtr && createdEntryPtr->objectBytes)
            boundObjectBytes = createdEntryPtr->objectBytes;
        else
            boundObjectBytes = reinterpret_cast<const uint8_t*>(objectPtr);

        // The object pool recycles pointers, so any binding left at either
        // address belongs to a previous chunk. Evict before storing — a
        // failed source capture must not leave the old craft's identity
        // behind for this chunk to inherit.
        EraseChunkResolvedBinding(reinterpret_cast<const uint8_t*>(objectPtr));
        EraseChunkResolvedBinding(boundObjectBytes);

        if (boundObjectBytes)
            StoreChunkResolvedBinding(boundObjectBytes, sourceTreeProbe);

        // Now that the debris exists, stop the intact hull from drawing the piece
        // that just left it. No-op unless PartialFragmentObject is on the stack.
        CollapseOwnerBoneForDetachedPiece(sourceTreeProbe);

        LogChunkCreateLifecycle(
            L"CreateChunk",
            thisPtr,
            reinterpret_cast<const uint8_t*>(objectPtr),
            nullptr,
            velocity,
            preserveFlag,
            countBefore,
            countAfter,
            createdEntryPtr,
            sourceTreeProbe.valid ? &sourceTreeProbe : nullptr);

        return result;
    }

    void __fastcall ChunkEffectCreateChunkletHook(void* thisPtr,
                                                  void* /*edx*/,
                                                  const void* positionVec,
                                                  const float* velocity,
                                                  uint8_t preserveFlag)
    {
        if (!g_BzrFn_ChunkEffectCreateChunklet)
            return;

        const auto* thisBytes = reinterpret_cast<const uint8_t*>(thisPtr);
        uint32_t countBefore = 0;
        TryReadChunkEffectCount(thisBytes, countBefore);

        g_BzrFn_ChunkEffectCreateChunklet(thisPtr, positionVec, velocity, preserveFlag);

        uint32_t countAfter = countBefore;
        TryReadChunkEffectCount(thisBytes, countAfter);

        ChunkEffectActiveEntry createdEntry = {};
        const ChunkEffectActiveEntry* createdEntryPtr = nullptr;
        if (countAfter > countBefore)
        {
            if (TryReadChunkEffectEntry(thisBytes, countBefore, createdEntry))
                createdEntryPtr = &createdEntry;
        }

        // Generic chunklets have no craft owner; if the pool recycled this
        // pointer from a craft chunk, the leftover binding would dress the
        // chunklet in that craft's debris meshes.
        if (createdEntryPtr && createdEntryPtr->objectBytes)
            EraseChunkResolvedBinding(createdEntryPtr->objectBytes);

        LogChunkCreateLifecycle(
            L"CreateChunklet",
            thisPtr,
            nullptr,
            reinterpret_cast<const float*>(positionVec),
            velocity,
            preserveFlag,
            countBefore,
            countAfter,
            createdEntryPtr,
            nullptr);

        // Baseline layout dump of a known-good chunklet geo (its name reads
        // fine) to compare against the craft-piece geoms whose names don't.
        if (g_ChunkEventLogging && createdEntryPtr && createdEntryPtr->objectBytes)
        {
            const void* geomRef = nullptr;
            char geomName[64] = {};
            if (TryReadChunkGeomIdentity(createdEntryPtr->objectBytes, geomRef, geomName, sizeof(geomName)) &&
                geomRef && geomName[0])
            {
                DumpChunkGeomBytes("chunklet-baseline", geomRef, &g_ChunkGeomDumpChunkletBudget);
            }
        }
    }

    static volatile long g_ChunkFragmentWalkLogBudget = 160;

    static bool AcquireChunkFragmentWalkLogSlot()
    {
        return g_ChunkEventLogging &&
            InterlockedDecrement(&g_ChunkFragmentWalkLogBudget) >= 0;
    }


    static void LogChunkFragmentWalkTree(const wchar_t* tag,
                                         void* thisPtr,
                                         void* objectPtr,
                                         uint8_t preserveFlag)
    {
        if (!g_TraceChunkRender && !g_TraceChunkEffectRuntime)
            return;
        if (!AcquireChunkFragmentWalkLogSlot())
            return;

        LogChunkDiagnostic(
            "chunkspawn",
            L"[CHUNKSPAWN] %ls-walk this=0x%08X root=0x%08X preserve=%u\n",
            tag ? tag : L"fragment",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectPtr)),
            static_cast<uint32_t>(preserveFlag));

        // Depth-first dump of the OBJ76 tree handed to the fragment walker.
        constexpr uint32_t kMaxWalkNodes = 24;
        constexpr uint32_t kMaxWalkStack = 24;
        const uint8_t* pending[kMaxWalkStack] = {};
        uint32_t pendingDepth[kMaxWalkStack] = {};
        uint32_t pendingCount = 0;
        if (objectPtr)
        {
            pending[pendingCount] = reinterpret_cast<const uint8_t*>(objectPtr);
            pendingDepth[pendingCount] = 0;
            ++pendingCount;
        }

        uint32_t visited = 0;
        while (pendingCount != 0 && visited < kMaxWalkNodes)
        {
            --pendingCount;
            const uint8_t* node = pending[pendingCount];
            const uint32_t depth = pendingDepth[pendingCount];
            if (!node)
                continue;
            ++visited;

            uint32_t classId = 0;
            uint32_t flags = 0;
            void* geomRef = nullptr;
            void* owner = nullptr;
            char geomName[64] = {};
            TryReadChunkObjectSummary(node, classId, flags, geomRef, geomName, sizeof(geomName), owner);

            const uint8_t* parent = nullptr;
            const uint8_t* sibling = nullptr;
            const uint8_t* child = nullptr;
            const bool linksOk = TryReadChunkObjectLinks(node, parent, sibling, child);

            if (AcquireChunkFragmentWalkLogSlot())
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN]   frag-node depth=%u obj=0x%08X class=%u flags=0x%08X geom=0x%08X geomName=%hs parent=0x%08X sibling=0x%08X child=0x%08X%hs\n",
                    depth,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(node)),
                    classId,
                    flags,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(geomRef)),
                    geomName[0] ? geomName : "<none>",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parent)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sibling)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(child)),
                    linksOk ? "" : " links=unreadable");
            }

            if (geomRef && !geomName[0])
                DumpChunkGeomBytes("fragnode", geomRef, &g_ChunkGeomDumpFragmentBudget);

            if (!linksOk)
                continue;
            // Push sibling first so children print directly under their parent.
            if (sibling && pendingCount < kMaxWalkStack)
            {
                pending[pendingCount] = sibling;
                pendingDepth[pendingCount] = depth;
                ++pendingCount;
            }
            if (child && pendingCount < kMaxWalkStack)
            {
                pending[pendingCount] = child;
                pendingDepth[pendingCount] = depth + 1;
                ++pendingCount;
            }
        }

        if (visited >= kMaxWalkNodes && AcquireChunkFragmentWalkLogSlot())
        {
            LogChunkDiagnostic(
                "chunkspawn",
                L"[CHUNKSPAWN]   frag-walk truncated at %u nodes\n",
                visited);
        }
    }

    static void BeginActiveFragmentSourceContext(void* rootObjectPtr)
    {
        g_ActiveFragmentSourceMeshName[0] = '\0';
        g_ActiveFragmentSourceOgreEntity = nullptr;
        g_ActiveFragmentSourceOgreEntityVia = "none";
        g_ActiveFragmentSourceOdfName[0] = '\0';
        if (!rootObjectPtr)
            return;

        const ChunkBridgeSnapshot rootSnapshot =
            CaptureChunkBridgeSnapshot(reinterpret_cast<const uint8_t*>(rootObjectPtr));
        if (rootSnapshot.ownerResolvedMeshName[0])
        {
            strncpy_s(
                g_ActiveFragmentSourceMeshName,
                rootSnapshot.ownerResolvedMeshName,
                _TRUNCATE);
        }

        g_ActiveFragmentSourceOgreEntity =
            ResolveCraftOgreEntity(rootObjectPtr, g_ActiveFragmentSourceOgreEntityVia);

        // Fragment nodes are render-tree nodes; the ODF lives on the GameObject
        // that owns them, one hop out through the obj76 back-link.
        void* rootGameObject = nullptr;
        if (TryGetGameObjectFromObj76(rootObjectPtr, rootGameObject) && rootGameObject)
        {
            TryGetCraftOdfName(
                rootGameObject,
                g_ActiveFragmentSourceOdfName,
                sizeof(g_ActiveFragmentSourceOdfName));
        }

        if (AcquireChunkFragmentWalkLogSlot())
        {
            LogChunkDiagnostic(
                "chunkspawn",
                L"[CHUNKSPAWN] frag-source obj=0x%08X mesh=%hs odf=%hs base=%hs file=%hs ogreEntity=0x%08X via=%hs\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(rootObjectPtr)),
                g_ActiveFragmentSourceMeshName[0] ? g_ActiveFragmentSourceMeshName : "<none>",
                g_ActiveFragmentSourceOdfName[0] ? g_ActiveFragmentSourceOdfName : "<none>",
                rootSnapshot.ownerEntityBaseName[0] ? rootSnapshot.ownerEntityBaseName : "<none>",
                rootSnapshot.ownerOgreFilename[0] ? rootSnapshot.ownerOgreFilename : "<none>",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_ActiveFragmentSourceOgreEntity)),
                g_ActiveFragmentSourceOgreEntityVia);
        }
    }

    void __fastcall ChunkEffectPartialFragmentHook(void* thisPtr,
                                                   void* /*edx*/,
                                                   void* objectPtr,
                                                   const float* velocity,
                                                   uint8_t preserveFlag)
    {
        if (!g_BzrFn_ChunkEffectPartialFragment)
            return;

        // The original recurses into its own patched entry for child levels;
        // only dump the tree for the outermost call.
        const bool outermost = (g_ChunkFragmentHookDepth == 0);
        uint32_t countBefore = 0;
        if (outermost)
        {
            LogChunkFragmentWalkTree(L"PartialFragmentObject", thisPtr, objectPtr, preserveFlag);
            TryReadChunkEffectCount(reinterpret_cast<const uint8_t*>(thisPtr), countBefore);
            BeginActiveFragmentSourceContext(objectPtr);
            g_ActivePartialFragment = true;
        }
        ++g_ChunkFragmentHookDepth;
        g_BzrFn_ChunkEffectPartialFragment(thisPtr, objectPtr, velocity, preserveFlag);
        --g_ChunkFragmentHookDepth;
        if (outermost)
        {
            g_ActivePartialFragment = false;
            g_ActiveFragmentSourceMeshName[0] = '\0';
            g_ActiveFragmentSourceOgreEntity = nullptr;
            g_ActiveFragmentSourceOgreEntityVia = "none";
            g_ActiveFragmentSourceOdfName[0] = '\0';
            uint32_t countAfter = countBefore;
            TryReadChunkEffectCount(reinterpret_cast<const uint8_t*>(thisPtr), countAfter);
            if (AcquireChunkFragmentWalkLogSlot())
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN] PartialFragmentObject-result created=%d countBefore=%u countAfter=%u\n",
                    static_cast<int>(countAfter) - static_cast<int>(countBefore),
                    countBefore,
                    countAfter);
            }
        }
    }

    // In the legacy engine full fragmentation unparented every geo from the
    // craft's object tree, so the intact model stopped rendering on the same
    // frame the debris appeared. Redux instead renders a baked Ogre mesh that
    // lingers until entity teardown; hide that mesh (and its light) here so
    // the chunk proxies visually take over immediately.
    static bool TrySetChunkOwnerMovableVisibleSeh(
        FnOgreSetVisible setVisible,
        void* movable,
        bool visible)
    {
        // Same trap as the bone collapse: these bridge slots sometimes hold text
        // rather than a movable, and setVisible on text is a virtual call into
        // string bytes. Vet before dispatching -- SEH turns that into a caught
        // fault, not a safe no-op.
        if (!setVisible || !LooksLikeOgreObject(movable))
            return false;

        __try
        {
            setVisible(movable, visible);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    static void HideChunkFragmentSourceMesh(void* objectPtr)
    {
        if (!objectPtr)
            return;

        static FnOgreSetVisible setVisible =
            ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");
        if (!setVisible)
            return;

        const ChunkBridgeSnapshot snapshot =
            CaptureChunkBridgeSnapshot(reinterpret_cast<const uint8_t*>(objectPtr));

        // When this node's own bridge slots are bogus the resolver still reaches
        // the craft's entity through the owning GameObject, so full fragmentation
        // stops depending on the same offset the collapse could not trust either.
        const char* resolvedVia = "none";
        void* const resolvedEntity = ResolveCraftOgreEntity(objectPtr, resolvedVia);

        uint32_t hiddenCount = 0;
        void* const candidates[] = {
            resolvedEntity,
            snapshot.directOgreLight,
            (snapshot.ownerOgreLight != snapshot.directOgreLight) ? snapshot.ownerOgreLight : nullptr,
        };
        for (void* candidate : candidates)
        {
            if (TrySetChunkOwnerMovableVisibleSeh(setVisible, candidate, false))
                ++hiddenCount;
        }

        if (AcquireChunkFragmentWalkLogSlot())
        {
            LogChunkDiagnostic(
                "chunkspawn",
                L"[CHUNKSPAWN] hide-source obj=0x%08X entity=0x%08X via=%hs directEntity=0x%08X ownerEntity=0x%08X hidden=%u\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectPtr)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(resolvedEntity)),
                resolvedVia,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(snapshot.directOgreEntity)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(snapshot.ownerOgreEntity)),
                hiddenCount);
        }
    }

    void __fastcall ChunkEffectFullFragmentHook(void* thisPtr,
                                                void* /*edx*/,
                                                void* objectPtr,
                                                const float* velocity,
                                                uint8_t preserveFlag)
    {
        if (!g_BzrFn_ChunkEffectFullFragment)
            return;

        const bool outermost = (g_ChunkFragmentHookDepth == 0);
        uint32_t countBefore = 0;
        if (outermost)
        {
            LogChunkFragmentWalkTree(L"FullFragmentObject", thisPtr, objectPtr, preserveFlag);
            TryReadChunkEffectCount(reinterpret_cast<const uint8_t*>(thisPtr), countBefore);
            HideChunkFragmentSourceMesh(objectPtr);
            BeginActiveFragmentSourceContext(objectPtr);
        }
        ++g_ChunkFragmentHookDepth;
        g_BzrFn_ChunkEffectFullFragment(thisPtr, objectPtr, velocity, preserveFlag);
        --g_ChunkFragmentHookDepth;
        if (outermost)
        {
            g_ActiveFragmentSourceMeshName[0] = '\0';
            g_ActiveFragmentSourceOgreEntity = nullptr;
            g_ActiveFragmentSourceOgreEntityVia = "none";
            g_ActiveFragmentSourceOdfName[0] = '\0';
            uint32_t countAfter = countBefore;
            TryReadChunkEffectCount(reinterpret_cast<const uint8_t*>(thisPtr), countAfter);
            if (AcquireChunkFragmentWalkLogSlot())
            {
                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN] FullFragmentObject-result created=%d countBefore=%u countAfter=%u\n",
                    static_cast<int>(countAfter) - static_cast<int>(countBefore),
                    countBefore,
                    countAfter);
            }
        }
    }

    // Stub: chunk fragment event flush not present in this revision.
    void FlushChunkFragmentEventsForShutdown()
    {
    }
}
