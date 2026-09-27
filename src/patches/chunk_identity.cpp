// chunk_identity.cpp
// BZR Open Shim - chunk proxy identity: reading a legacy chunk's geom
// name, owner entity and object links, the resolved-binding and object
// identity caches, and the create-lifecycle diagnostics, split out of
// bzr_hooks.cpp.
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
        static std::unordered_map<uintptr_t, ChunkObjectIdentityCacheEntry> g_ChunkObjectIdentityCache = {};

        static DWORD g_ChunkObjectIdentityLastRefreshTick = 0;

        static constexpr uintptr_t kChunkObjGeomRefOffset = 0x64;

        static constexpr DWORD kChunkObjectIdentityRefreshMs = 1000;

        static constexpr DWORD kChunkResolvedBindingExpireMs = 10000;

        static constexpr DWORD kChunkResolvedBindingPruneMs = 1000;

        static constexpr size_t kChunkObjectIdentityMaxNodesPerObject = 256;

        static bool TryReadAsciiString(const char* address, char* outText, size_t outTextCapacity)
        {
            if (!address || !outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';

            __try
            {
                size_t index = 0;
                for (; index + 1 < outTextCapacity; ++index)
                {
                    const unsigned char ch = static_cast<unsigned char>(address[index]);
                    if (ch == 0)
                    {
                        outText[index] = '\0';
                        return index > 0;
                    }

                    if (ch < 0x20 || ch > 0x7E)
                    {
                        outText[0] = '\0';
                        return false;
                    }

                    outText[index] = static_cast<char>(ch);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outText[0] = '\0';
                return false;
            }

            outText[outTextCapacity - 1] = '\0';
            return false;
        }

        // Legacy geo names live in a fixed 8-byte field that is NOT
        // NUL-terminated when the name is exactly 8 chars (e.g. "scz11bda"
        // is immediately followed by the geom back-pointer); shorter names
        // are NUL-padded ("chunk2\0\0"). Read at most 8 chars and accept
        // hitting the field boundary without a terminator.
        static bool TryReadLegacyGeoNameField(const char* address, char* outText, size_t outTextCapacity)
        {
            if (!address || !outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';

            __try
            {
                const size_t kFieldLen = 8;
                size_t index = 0;
                for (; index < kFieldLen && index + 1 < outTextCapacity; ++index)
                {
                    const unsigned char ch = static_cast<unsigned char>(address[index]);
                    if (ch == 0)
                        break;

                    if (ch < 0x20 || ch > 0x7E)
                    {
                        outText[0] = '\0';
                        return false;
                    }

                    outText[index] = static_cast<char>(ch);
                }

                outText[index] = '\0';
                return index > 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outText[0] = '\0';
                return false;
            }
        }

        bool TryReadInlineAsciiBuffer(
            const void* address,
            size_t maxInlineBytes,
            char* outText,
            size_t outTextCapacity)
        {
            if (!address || !outText || outTextCapacity == 0 || maxInlineBytes == 0)
                return false;

            outText[0] = '\0';

            __try
            {
                const auto* textBytes = reinterpret_cast<const unsigned char*>(address);
                size_t index = 0;
                for (; index < maxInlineBytes && index + 1 < outTextCapacity; ++index)
                {
                    const unsigned char ch = textBytes[index];
                    if (ch == 0)
                    {
                        outText[index] = '\0';
                        return index > 0;
                    }

                    if (ch < 0x20 || ch > 0x7E)
                    {
                        outText[0] = '\0';
                        return false;
                    }

                    outText[index] = static_cast<char>(ch);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outText[0] = '\0';
                return false;
            }

            outText[outTextCapacity - 1] = '\0';
            return outText[0] != '\0';
        }

        static bool IsLikelyChunkGeomName(const char* text)
        {
            if (!text || !*text)
                return false;

            size_t length = 0;
            bool hasAlpha = false;
            for (const unsigned char* cursor = reinterpret_cast<const unsigned char*>(text); *cursor; ++cursor)
            {
                const unsigned char ch = *cursor;
                if (!(std::isalnum(ch) || ch == '_' || ch == '-'))
                    return false;

                if (std::isalpha(ch))
                    hasAlpha = true;

                ++length;
                if (length > 15)
                    return false;
            }

            if (!hasAlpha || length < 4)
                return false;

            return _strnicmp(text, "chunk", 5) == 0 ||
                   _strnicmp(text, "agr", 3) == 0;
        }

        static bool TryProbeChunkGeomName(
            const uint8_t* geomBytes,
            char* outGeomName,
            size_t outGeomNameCapacity)
        {
            if (!geomBytes || !outGeomName || outGeomNameCapacity == 0)
                return false;

            outGeomName[0] = '\0';

            constexpr uintptr_t kGeomPointerProbeOffsets[] = {
                0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C, 0x20,
                0x24, 0x28, 0x2C, 0x30, 0x34, 0x38, 0x3C, 0x40
            };
            constexpr uintptr_t kGeomInlineProbeOffsets[] = {
                0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C,
                0x20, 0x24, 0x28, 0x2C, 0x30, 0x34, 0x38, 0x3C
            };

            char candidate[64] = {};

            for (uintptr_t offset : kGeomPointerProbeOffsets)
            {
                const char* candidatePtr = nullptr;
                __try
                {
                    candidatePtr = *reinterpret_cast<const char* const*>(geomBytes + offset);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    candidatePtr = nullptr;
                }

                if (!candidatePtr)
                    continue;

                if (TryReadAsciiString(candidatePtr, candidate, sizeof(candidate)) &&
                    IsLikelyChunkGeomName(candidate))
                {
                    strncpy_s(outGeomName, outGeomNameCapacity, candidate, _TRUNCATE);
                    return true;
                }
            }

            for (uintptr_t offset : kGeomInlineProbeOffsets)
            {
                if (TryReadInlineAsciiBuffer(geomBytes + offset, 16, candidate, sizeof(candidate)) &&
                    IsLikelyChunkGeomName(candidate))
                {
                    strncpy_s(outGeomName, outGeomNameCapacity, candidate, _TRUNCATE);
                    return true;
                }
            }

            return false;
        }

        static bool TryReadObjProjectId(
            const uint8_t* objectBytes,
            char* outText,
            size_t outTextCapacity)
        {
            if (!objectBytes || !outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';

            __try
            {
                size_t index = 0;
                for (; index < 8 && index + 1 < outTextCapacity; ++index)
                {
                    const unsigned char rawCh = objectBytes[index];
                    const unsigned char ch = rawCh & 0x7F;
                    if (ch == 0)
                        break;

                    if (!(std::isalnum(ch) || ch == '_' || ch == '-'))
                    {
                        outText[0] = '\0';
                        return false;
                    }

                    outText[index] = static_cast<char>(ch);
                }

                outText[index] = '\0';
                return index > 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outText[0] = '\0';
                return false;
            }
        }

        static bool BuildChunkOwnerMeshName(
            const char* ownerEntityBaseName,
            const char* ownerOgreFilename,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';

            const char* preferredName =
                (ownerOgreFilename && *ownerOgreFilename) ? ownerOgreFilename :
                ((ownerEntityBaseName && *ownerEntityBaseName) ? ownerEntityBaseName : nullptr);
            if (!preferredName || !*preferredName)
                return false;

            if (strchr(preferredName, '.') != nullptr)
            {
                strncpy_s(outMeshName, outMeshNameCapacity, preferredName, _TRUNCATE);
                return true;
            }

            _snprintf_s(outMeshName, outMeshNameCapacity, _TRUNCATE, "%s.mesh", preferredName);
            return outMeshName[0] != '\0';
        }

        // The owner-name offsets below are guesses across two candidate tagENTITY
        // layouts, and TryReadInlineAsciiBuffer accepts any printable ASCII. That
        // is too weak: an avtank's entity holds the bytes "cd=@" at the first
        // probed offset, which sailed through as a name and became "cd=@.mesh".
        // A bogus name is worse than no name, because a resolved owner mesh wins
        // over every downstream fallback -- it suppressed the VDF candidate list
        // and dropped every avtank chunk onto the generic placeholder payloads.
        // Model names are identifiers, so hold candidates to that shape.
        static bool IsPlausibleOwnerEntityName(const char* text)
        {
            if (!text || !*text)
                return false;

            size_t length = 0;
            size_t alphaNumeric = 0;
            size_t dots = 0;
            for (const unsigned char* cursor = reinterpret_cast<const unsigned char*>(text); *cursor; ++cursor)
            {
                const unsigned char ch = *cursor;
                if (std::isalnum(ch))
                {
                    ++alphaNumeric;
                }
                else if (ch == '.')
                {
                    // One extension separator at most, and never leading.
                    if (++dots > 1 || length == 0)
                        return false;
                }
                else if (ch != '_' && ch != '-')
                {
                    return false;
                }

                ++length;
                if (length > 24)
                    return false;
            }

            // "avtank", "avfigh.mesh" pass; "cd=@", "a", "12" do not.
            return length >= 3 && alphaNumeric >= 3 && std::isalpha(static_cast<unsigned char>(text[0]));
        }

        // Takes the first offset whose contents actually look like a name instead
        // of short-circuiting on the first offset that holds any readable ASCII.
        static bool TryReadOwnerEntityNameField(
            const uint8_t* entityBytes,
            const uintptr_t* probeOffsets,
            size_t probeOffsetCount,
            char* outText,
            size_t outTextCapacity)
        {
            if (!entityBytes || !probeOffsets || !outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';

            char candidate[32] = {};
            for (size_t index = 0; index < probeOffsetCount; ++index)
            {
                if (!TryReadInlineAsciiBuffer(
                        entityBytes + probeOffsets[index],
                        16,
                        candidate,
                        sizeof(candidate)))
                {
                    continue;
                }

                if (!IsPlausibleOwnerEntityName(candidate))
                    continue;

                strncpy_s(outText, outTextCapacity, candidate, _TRUNCATE);
                return true;
            }

            return false;
        }

        bool TryReadOwnerEntityNames(
            const void* ownerEntity,
            char* outEntityBaseName,
            size_t outEntityBaseNameCapacity,
            char* outOgreFilename,
            size_t outOgreFilenameCapacity,
            char* outResolvedMeshName,
            size_t outResolvedMeshNameCapacity)
        {
            if (outEntityBaseName && outEntityBaseNameCapacity > 0)
                outEntityBaseName[0] = '\0';
            if (outOgreFilename && outOgreFilenameCapacity > 0)
                outOgreFilename[0] = '\0';
            if (outResolvedMeshName && outResolvedMeshNameCapacity > 0)
                outResolvedMeshName[0] = '\0';

            if (!ownerEntity)
                return false;

            char entityBaseName[32] = {};
            char ogreFilename[32] = {};

            // The current best-effort corpora disagree on the inline string offsets for
            // tagENTITY. Probe both candidate layouts and keep whichever yields a name.
            static constexpr uintptr_t kBaseNameProbeOffsets[] = { 0xC4, 0x84 };
            static constexpr uintptr_t kFilenameProbeOffsets[] = { 0xD4, 0x94 };

            const auto* entityBytes = reinterpret_cast<const uint8_t*>(ownerEntity);
            const bool baseRead = TryReadOwnerEntityNameField(
                entityBytes,
                kBaseNameProbeOffsets,
                _countof(kBaseNameProbeOffsets),
                entityBaseName,
                sizeof(entityBaseName));
            const bool fileRead = TryReadOwnerEntityNameField(
                entityBytes,
                kFilenameProbeOffsets,
                _countof(kFilenameProbeOffsets),
                ogreFilename,
                sizeof(ogreFilename));

            if (outEntityBaseName && outEntityBaseNameCapacity > 0 && baseRead)
                strncpy_s(outEntityBaseName, outEntityBaseNameCapacity, entityBaseName, _TRUNCATE);
            if (outOgreFilename && outOgreFilenameCapacity > 0 && fileRead)
                strncpy_s(outOgreFilename, outOgreFilenameCapacity, ogreFilename, _TRUNCATE);

            if (outResolvedMeshName && outResolvedMeshNameCapacity > 0)
                BuildChunkOwnerMeshName(entityBaseName, ogreFilename, outResolvedMeshName, outResolvedMeshNameCapacity);

            return baseRead || fileRead;
        }

        bool TryReadChunkGeomIdentity(
            const uint8_t* objectBytes,
            const void*& outGeomRef,
            char* outGeomName,
            size_t outGeomNameCapacity)
        {
            outGeomRef = nullptr;
            if (outGeomName && outGeomNameCapacity > 0)
                outGeomName[0] = '\0';

            if (!objectBytes)
                return false;

            __try
            {
                outGeomRef = *reinterpret_cast<void* const*>(objectBytes + kChunkObjGeomRefOffset);
                if (!outGeomRef || !outGeomName || outGeomNameCapacity == 0)
                    return true;

                const auto* geomBytes = reinterpret_cast<const uint8_t*>(outGeomRef);
                const char* const geomNamePtr = *reinterpret_cast<const char* const*>(geomBytes + 0x0);
                if (!TryReadLegacyGeoNameField(geomNamePtr, outGeomName, outGeomNameCapacity) ||
                    !outGeomName[0])
                {
                    TryProbeChunkGeomName(geomBytes, outGeomName, outGeomNameCapacity);
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outGeomRef = nullptr;
                if (outGeomName && outGeomNameCapacity > 0)
                    outGeomName[0] = '\0';
                return false;
            }
        }

        static bool TryReadFloat3(const float* values, float& outX, float& outY, float& outZ)
        {
            outX = 0.0f;
            outY = 0.0f;
            outZ = 0.0f;
            if (!values)
                return false;

            __try
            {
                outX = values[0];
                outY = values[1];
                outZ = values[2];
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outX = 0.0f;
                outY = 0.0f;
                outZ = 0.0f;
                return false;
            }
        }

        bool TryReadChunkObjectSummary(
            const uint8_t* objectBytes,
            uint32_t& outClassId,
            uint32_t& outFlags,
            void*& outGeomRef,
            char* outGeomName,
            size_t outGeomNameCapacity,
            void*& outOwner)
        {
            outClassId = 0;
            outFlags = 0;
            outGeomRef = nullptr;
            outOwner = nullptr;
            if (outGeomName && outGeomNameCapacity > 0)
                outGeomName[0] = '\0';
            if (!objectBytes)
                return false;

            __try
            {
                outFlags = *reinterpret_cast<const uint32_t*>(objectBytes + 0x14);
                outClassId = *reinterpret_cast<const uint32_t*>(objectBytes + 0x84);
                outOwner = *reinterpret_cast<void* const*>(objectBytes + 0x8C);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outClassId = 0;
                outFlags = 0;
                outOwner = nullptr;
                if (outGeomName && outGeomNameCapacity > 0)
                    outGeomName[0] = '\0';
                return false;
            }

            const void* geomRefConst = nullptr;
            TryReadChunkGeomIdentity(objectBytes, geomRefConst, outGeomName, outGeomNameCapacity);
            outGeomRef = const_cast<void*>(geomRefConst);
            return true;
        }

        bool CaptureChunkObjectLinkProbe(const uint8_t* objectBytes, ChunkObjectLinkProbe& outProbe)
        {
            outProbe = {};
            outProbe.objectBytes = objectBytes;
            if (!objectBytes)
                return false;

            TryReadObjProjectId(objectBytes, outProbe.objectId, sizeof(outProbe.objectId));

            void* ownerUnused = nullptr;
            const bool ok = TryReadChunkObjectSummary(
                objectBytes,
                outProbe.classId,
                outProbe.flags,
                outProbe.geomRef,
                outProbe.geomName,
                sizeof(outProbe.geomName),
                ownerUnused);
            if (ok)
                PopulateChunkObjectLinkProbeFromIdentityCache(outProbe);
            return ok;
        }

        static const ChunkObjectIdentityCacheEntry* FindChunkObjectIdentityCacheEntry(const uint8_t* objectBytes)
        {
            if (!objectBytes)
                return nullptr;

            const auto it = g_ChunkObjectIdentityCache.find(reinterpret_cast<uintptr_t>(objectBytes));
            return (it != g_ChunkObjectIdentityCache.end()) ? &it->second : nullptr;
        }

        // Caches keyed on raw OBJ76 pointers go stale when the engine's object
        // pool recycles an address for a new chunk: without validation a fresh
        // chunklet (or another craft's chunk) inherits the previous owner's
        // craft identity. A geo-name mismatch is the recycle signal.
        static bool ChunkCachedGeomNameMatchesLive(const char* cachedGeomName, const char* liveGeomName)
        {
            if (!cachedGeomName || !cachedGeomName[0] || !liveGeomName || !liveGeomName[0])
                return true;

            return _stricmp(cachedGeomName, liveGeomName) == 0;
        }

        void EraseChunkResolvedBinding(const uint8_t* objectBytes)
        {
            if (!objectBytes)
                return;

            g_ChunkResolvedBindingCache.erase(reinterpret_cast<uintptr_t>(objectBytes));
        }

        const ChunkResolvedBindingEntry* FindChunkResolvedBindingEntryForGeom(
            const uint8_t* objectBytes,
            const char* liveGeomName)
        {
            if (!objectBytes)
                return nullptr;

            const auto it = g_ChunkResolvedBindingCache.find(reinterpret_cast<uintptr_t>(objectBytes));
            if (it == g_ChunkResolvedBindingCache.end())
                return nullptr;

            if (!ChunkCachedGeomNameMatchesLive(it->second.sourceGeomName, liveGeomName))
            {
                g_ChunkResolvedBindingCache.erase(it);
                return nullptr;
            }

            return &it->second;
        }

        void StoreChunkResolvedBinding(
            const uint8_t* objectBytes,
            const ChunkCreateSourceTreeProbe& sourceTreeProbe)
        {
            if (!objectBytes || !sourceTreeProbe.valid)
                return;

            ChunkResolvedBindingEntry entry = {};
            if (sourceTreeProbe.source.cachedMeshName[0])
            {
                strncpy_s(entry.meshName, sizeof(entry.meshName), sourceTreeProbe.source.cachedMeshName, _TRUNCATE);
            }
            else if (sourceTreeProbe.ownerResolvedMeshName[0])
            {
                strncpy_s(entry.meshName, sizeof(entry.meshName), sourceTreeProbe.ownerResolvedMeshName, _TRUNCATE);
            }
            else
            {
                ResolveChunkCreateMeshContext(
                    sourceTreeProbe,
                    entry.meshName,
                    sizeof(entry.meshName));
            }

            if (sourceTreeProbe.source.vdfCandidates[0])
            {
                strncpy_s(
                    entry.vdfCandidates,
                    sizeof(entry.vdfCandidates),
                    sourceTreeProbe.source.vdfCandidates,
                    _TRUNCATE);
            }
            else if (entry.meshName[0])
            {
                BuildChunkVdfSourceCandidateList(
                    entry.meshName,
                    sourceTreeProbe.source,
                    sourceTreeProbe.parent,
                    sourceTreeProbe.sibling,
                    sourceTreeProbe.child,
                    entry.vdfCandidates,
                    sizeof(entry.vdfCandidates));
            }

            entry.sourceClassId = sourceTreeProbe.source.classId;
            if (sourceTreeProbe.source.geomName[0])
                strncpy_s(entry.sourceGeomName, sizeof(entry.sourceGeomName), sourceTreeProbe.source.geomName, _TRUNCATE);

            if (!entry.meshName[0] &&
                !entry.vdfCandidates[0] &&
                entry.sourceClassId == 0 &&
                !entry.sourceGeomName[0])
            {
                return;
            }

            entry.bindTick = GetTickCount();
            entry.lastSeenTick = entry.bindTick;
            g_ChunkResolvedBindingCache[reinterpret_cast<uintptr_t>(objectBytes)] = entry;
        }

        void TouchChunkResolvedBinding(const uint8_t* objectBytes)
        {
            if (!objectBytes)
                return;

            const auto it = g_ChunkResolvedBindingCache.find(reinterpret_cast<uintptr_t>(objectBytes));
            if (it == g_ChunkResolvedBindingCache.end())
                return;

            it->second.lastSeenTick = GetTickCount();
        }

        void PruneChunkResolvedBindingsIfNeeded()
        {
            if (g_ChunkResolvedBindingCache.empty())
                return;

            const DWORD now = GetTickCount();
            if (g_ChunkResolvedBindingLastPruneTick != 0 &&
                static_cast<DWORD>(now - g_ChunkResolvedBindingLastPruneTick) < kChunkResolvedBindingPruneMs)
            {
                return;
            }
            g_ChunkResolvedBindingLastPruneTick = now;

            for (auto it = g_ChunkResolvedBindingCache.begin(); it != g_ChunkResolvedBindingCache.end();)
            {
                const DWORD referenceTick =
                    (it->second.lastSeenTick != 0) ? it->second.lastSeenTick : it->second.bindTick;
                if (referenceTick != 0 &&
                    static_cast<DWORD>(now - referenceTick) >= kChunkResolvedBindingExpireMs)
                {
                    it = g_ChunkResolvedBindingCache.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        void PopulateChunkObjectLinkProbeFromIdentityCache(ChunkObjectLinkProbe& probe)
        {
            const ChunkResolvedBindingEntry* binding =
                FindChunkResolvedBindingEntryForGeom(probe.objectBytes, probe.geomName);
            if (binding)
            {
                if (binding->meshName[0])
                    strncpy_s(probe.cachedMeshName, binding->meshName, _TRUNCATE);
                if (binding->vdfCandidates[0])
                    strncpy_s(probe.vdfCandidates, binding->vdfCandidates, _TRUNCATE);
            }

            const ChunkObjectIdentityCacheEntry* cached = FindChunkObjectIdentityCacheEntry(probe.objectBytes);
            if (!cached)
                return;
            if (!ChunkCachedGeomNameMatchesLive(cached->geomName, probe.geomName))
                return;

            if (!probe.cachedMeshName[0] && cached->meshName[0])
                strncpy_s(probe.cachedMeshName, cached->meshName, _TRUNCATE);
            if (!probe.vdfCandidates[0] && cached->vdfCandidates[0])
                strncpy_s(probe.vdfCandidates, cached->vdfCandidates, _TRUNCATE);
        }

        bool CaptureChunkCreateSourceTreeProbe(
            const uint8_t* sourceBytes,
            ChunkCreateSourceTreeProbe& outProbe)
        {
            outProbe = {};
            if (!sourceBytes)
                return false;

            outProbe.valid = CaptureChunkObjectLinkProbe(sourceBytes, outProbe.source);

            const uint8_t* parentBytes = nullptr;
            const uint8_t* siblingBytes = nullptr;
            const uint8_t* childBytes = nullptr;
            __try
            {
                parentBytes = *reinterpret_cast<const uint8_t* const*>(sourceBytes + 0x78);
                siblingBytes = *reinterpret_cast<const uint8_t* const*>(sourceBytes + 0x7C);
                childBytes = *reinterpret_cast<const uint8_t* const*>(sourceBytes + 0x80);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                parentBytes = nullptr;
                siblingBytes = nullptr;
                childBytes = nullptr;
            }

            CaptureChunkObjectLinkProbe(parentBytes, outProbe.parent);
            CaptureChunkObjectLinkProbe(siblingBytes, outProbe.sibling);
            CaptureChunkObjectLinkProbe(childBytes, outProbe.child);

            const ChunkBridgeSnapshot bridgeSnapshot = CaptureChunkBridgeSnapshot(sourceBytes);
            outProbe.ownerEntity = bridgeSnapshot.ownerEntity;
            outProbe.ownerOgreEntity =
                LooksLikeOgreObject(bridgeSnapshot.directOgreEntity) ? bridgeSnapshot.directOgreEntity
                : LooksLikeOgreObject(bridgeSnapshot.ownerOgreEntity) ? bridgeSnapshot.ownerOgreEntity
                                                                      : nullptr;
            if (bridgeSnapshot.ownerEntityBaseName[0])
                strncpy_s(outProbe.ownerEntityBaseName, bridgeSnapshot.ownerEntityBaseName, _TRUNCATE);
            if (bridgeSnapshot.ownerOgreFilename[0])
                strncpy_s(outProbe.ownerOgreFilename, bridgeSnapshot.ownerOgreFilename, _TRUNCATE);
            if (bridgeSnapshot.ownerResolvedMeshName[0])
                strncpy_s(outProbe.ownerResolvedMeshName, bridgeSnapshot.ownerResolvedMeshName, _TRUNCATE);
            if (!outProbe.ownerResolvedMeshName[0] && g_ActiveFragmentSourceMeshName[0])
                strncpy_s(outProbe.ownerResolvedMeshName, g_ActiveFragmentSourceMeshName, _TRUNCATE);
            if (!outProbe.ownerResolvedMeshName[0])
            {
                ResolveChunkCreateMeshContext(
                    outProbe,
                    outProbe.ownerResolvedMeshName,
                    sizeof(outProbe.ownerResolvedMeshName));
            }
            if (!outProbe.source.vdfCandidates[0] && outProbe.ownerResolvedMeshName[0])
            {
                BuildChunkVdfSourceCandidateList(
                    outProbe.ownerResolvedMeshName,
                    outProbe.source,
                    outProbe.parent,
                    outProbe.sibling,
                    outProbe.child,
                    outProbe.source.vdfCandidates,
                    sizeof(outProbe.source.vdfCandidates));
            }

            if (outProbe.ownerResolvedMeshName[0])
            {
                if (!outProbe.source.vdfCandidates[0])
                    PopulateChunkVdfCandidates(outProbe.ownerResolvedMeshName, outProbe.source);
                PopulateChunkVdfCandidates(outProbe.ownerResolvedMeshName, outProbe.parent);
                PopulateChunkVdfCandidates(outProbe.ownerResolvedMeshName, outProbe.sibling);
                PopulateChunkVdfCandidates(outProbe.ownerResolvedMeshName, outProbe.child);
            }

            return outProbe.valid;
        }

        bool TryReadChunkEffectCount(const uint8_t* thisBytes, uint32_t& outCount)
        {
            outCount = 0;
            if (!thisBytes)
                return false;

            __try
            {
                outCount = *reinterpret_cast<const uint32_t*>(thisBytes + kChunkEffectActiveCountOffset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outCount = 0;
                return false;
            }
        }

        void LogChunkCreateLifecycle(
            const wchar_t* tag,
            void* thisPtr,
            const uint8_t* sourceBytes,
            const float* positionVec,
            const float* velocityVec,
            uint8_t preserveFlag,
            uint32_t countBefore,
            uint32_t countAfter,
            const ChunkEffectActiveEntry* createdEntry,
            const ChunkCreateSourceTreeProbe* sourceTreeProbe)
        {
            if ((!g_TraceChunkRender && !g_TraceChunkEffectRuntime) || !AcquireChunkLogSlot())
                return;

            uint32_t sourceClassId = 0;
            uint32_t sourceFlags = 0;
            void* sourceGeomRef = nullptr;
            void* sourceOwner = nullptr;
            char sourceGeomName[64] = {};
            TryReadChunkObjectSummary(
                sourceBytes,
                sourceClassId,
                sourceFlags,
                sourceGeomRef,
                sourceGeomName,
                sizeof(sourceGeomName),
                sourceOwner);

            uint32_t createdClassId = 0;
            uint32_t createdFlags = 0;
            void* createdGeomRef = nullptr;
            void* createdOwner = nullptr;
            char createdGeomName[64] = {};
            TryReadChunkObjectSummary(
                createdEntry ? createdEntry->objectBytes : nullptr,
                createdClassId,
                createdFlags,
                createdGeomRef,
                createdGeomName,
                sizeof(createdGeomName),
                createdOwner);

            const char* const sourceGeomDisplay = sourceGeomName[0] ? sourceGeomName : "<none>";
            const char* const sourceGeomKind =
                !sourceGeomName[0]
                    ? "unknown"
                    : ((_stricmp(sourceGeomName, "chunk1") == 0 || _stricmp(sourceGeomName, "chunk2") == 0)
                           ? "stock-chunklet"
                           : "named-nonchunklet");
            const char* const sourceVdfDisplay =
                (sourceTreeProbe && sourceTreeProbe->source.vdfCandidates[0])
                    ? sourceTreeProbe->source.vdfCandidates
                    : "<none>";
            const char* const createdGeomDisplay = createdGeomName[0] ? createdGeomName : "<none>";
            const char* const createdGeomKind =
                !createdGeomName[0]
                    ? "unknown"
                    : ((_stricmp(createdGeomName, "chunk1") == 0 || _stricmp(createdGeomName, "chunk2") == 0)
                           ? "stock-chunklet"
                           : "named-nonchunklet");

            float posX = 0.0f;
            float posY = 0.0f;
            float posZ = 0.0f;
            bool havePos = TryReadFloat3(positionVec, posX, posY, posZ);
            if (!havePos && createdEntry && createdEntry->objectBytes)
                havePos = TryGetChunkProxyPosition(createdEntry->objectBytes, posX, posY, posZ);

            float velX = 0.0f;
            float velY = 0.0f;
            float velZ = 0.0f;
            bool haveVel = false;
            if (createdEntry)
            {
                velX = createdEntry->velocityX;
                velY = createdEntry->velocityY;
                velZ = createdEntry->velocityZ;
                haveVel = true;
            }
            else
            {
                haveVel = TryReadFloat3(velocityVec, velX, velY, velZ);
            }

            LogChunkDiagnostic(
                "chunkspawn",
                L"[CHUNKSPAWN] %ls this=0x%08X before=%u after=%u preserve=%u src=0x%08X srcClass=%u srcFlags=0x%08X srcOwner=0x%08X srcGeom=0x%08X srcGeomName=%hs srcGeomKind=%hs srcVdf=%hs created=0x%08X createdClass=%u createdFlags=0x%08X createdOwner=0x%08X createdGeom=0x%08X createdGeomName=%hs createdGeomKind=%hs pos=%hs(%.4f, %.4f, %.4f) vel=%hs(%.4f, %.4f, %.4f)\n",
                tag ? tag : L"unknown",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)),
                countBefore,
                countAfter,
                static_cast<uint32_t>(preserveFlag),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceBytes)),
                sourceClassId,
                sourceFlags,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceOwner)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceGeomRef)),
                sourceGeomDisplay,
                sourceGeomKind,
                sourceVdfDisplay,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(createdEntry ? createdEntry->objectBytes : nullptr)),
                createdClassId,
                createdFlags,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(createdOwner)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(createdGeomRef)),
                createdGeomDisplay,
                createdGeomKind,
                havePos ? "" : "missing-",
                static_cast<double>(posX),
                static_cast<double>(posY),
                static_cast<double>(posZ),
                haveVel ? "" : "missing-",
                static_cast<double>(velX),
                static_cast<double>(velY),
                static_cast<double>(velZ));

            if (sourceTreeProbe && sourceTreeProbe->valid)
            {
                const ChunkObjectLinkProbe& sourceProbe = sourceTreeProbe->source;
                const ChunkObjectLinkProbe& parentProbe = sourceTreeProbe->parent;
                const ChunkObjectLinkProbe& siblingProbe = sourceTreeProbe->sibling;
                const ChunkObjectLinkProbe& childProbe = sourceTreeProbe->child;

                LogChunkDiagnostic(
                    "chunkspawn",
                    L"[CHUNKSPAWN]   srcTree src=0x%08X objId=%hs class=%u flags=0x%08X geom=0x%08X geomName=%hs ownerEntity=0x%08X ownerBase=%hs ownerFile=%hs ownerMesh=%hs | parent=0x%08X objId=%hs class=%u geom=0x%08X geomName=%hs | sibling=0x%08X objId=%hs class=%u geom=0x%08X geomName=%hs | child=0x%08X objId=%hs class=%u geom=0x%08X geomName=%hs\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceProbe.objectBytes)),
                    sourceProbe.objectId[0] ? sourceProbe.objectId : "<none>",
                    sourceProbe.classId,
                    sourceProbe.flags,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceProbe.geomRef)),
                    sourceProbe.geomName[0] ? sourceProbe.geomName : "<none>",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sourceTreeProbe->ownerEntity)),
                    sourceTreeProbe->ownerEntityBaseName[0] ? sourceTreeProbe->ownerEntityBaseName : "<none>",
                    sourceTreeProbe->ownerOgreFilename[0] ? sourceTreeProbe->ownerOgreFilename : "<none>",
                    sourceTreeProbe->ownerResolvedMeshName[0] ? sourceTreeProbe->ownerResolvedMeshName : "<none>",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parentProbe.objectBytes)),
                    parentProbe.objectId[0] ? parentProbe.objectId : "<none>",
                    parentProbe.classId,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parentProbe.geomRef)),
                    parentProbe.geomName[0] ? parentProbe.geomName : "<none>",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(siblingProbe.objectBytes)),
                    siblingProbe.objectId[0] ? siblingProbe.objectId : "<none>",
                    siblingProbe.classId,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(siblingProbe.geomRef)),
                    siblingProbe.geomName[0] ? siblingProbe.geomName : "<none>",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(childProbe.objectBytes)),
                    childProbe.objectId[0] ? childProbe.objectId : "<none>",
                    childProbe.classId,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(childProbe.geomRef)),
                    childProbe.geomName[0] ? childProbe.geomName : "<none>");

                if (sourceProbe.vdfCandidates[0] || parentProbe.vdfCandidates[0] ||
                    siblingProbe.vdfCandidates[0] || childProbe.vdfCandidates[0])
                {
                    LogChunkDiagnostic(
                        "chunkspawn",
                        L"[CHUNKSPAWN]   vdf src=%hs | parent=%hs | sibling=%hs | child=%hs\n",
                        sourceProbe.vdfCandidates[0] ? sourceProbe.vdfCandidates : "<none>",
                        parentProbe.vdfCandidates[0] ? parentProbe.vdfCandidates : "<none>",
                        siblingProbe.vdfCandidates[0] ? siblingProbe.vdfCandidates : "<none>",
                        childProbe.vdfCandidates[0] ? childProbe.vdfCandidates : "<none>");
                }
            }
        }

        bool TryReadChunkObjectLinks(
            const uint8_t* objectBytes,
            const uint8_t*& outParent,
            const uint8_t*& outSibling,
            const uint8_t*& outChild)
        {
            outParent = nullptr;
            outSibling = nullptr;
            outChild = nullptr;
            if (!objectBytes)
                return false;

            __try
            {
                outParent = *reinterpret_cast<const uint8_t* const*>(objectBytes + 0x78);
                outSibling = *reinterpret_cast<const uint8_t* const*>(objectBytes + 0x7C);
                outChild = *reinterpret_cast<const uint8_t* const*>(objectBytes + 0x80);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outParent = nullptr;
                outSibling = nullptr;
                outChild = nullptr;
                return false;
            }
        }

        bool TryGetGameObjectMeshName(void* gameObject, char* outMeshName, size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';
            if (!gameObject)
                return false;

            void* obj76 = nullptr;
            if (!TryGetGameObjectObj76(gameObject, obj76))
                return false;

            const ChunkBridgeSnapshot snapshot = CaptureChunkBridgeSnapshot(reinterpret_cast<const uint8_t*>(obj76));
            if (snapshot.ownerResolvedMeshName[0])
            {
                strncpy_s(outMeshName, outMeshNameCapacity, snapshot.ownerResolvedMeshName, _TRUNCATE);
                return true;
            }

            char entityBaseName[32] = {};
            char ogreFilename[32] = {};
            if (TryReadOwnerEntityNames(
                    gameObject,
                    entityBaseName,
                    sizeof(entityBaseName),
                    ogreFilename,
                    sizeof(ogreFilename),
                    outMeshName,
                    outMeshNameCapacity))
            {
                return outMeshName[0] != '\0';
            }

            return false;
        }

        static void CacheChunkObjectIdentityForNode(const uint8_t* objectBytes, const char* meshName)
        {
            if (!objectBytes || !meshName || !*meshName)
                return;

            ChunkObjectLinkProbe source = {};
            if (!CaptureChunkObjectLinkProbe(objectBytes, source))
                return;

            const uint8_t* parentBytes = nullptr;
            const uint8_t* siblingBytes = nullptr;
            const uint8_t* childBytes = nullptr;
            TryReadChunkObjectLinks(objectBytes, parentBytes, siblingBytes, childBytes);

            ChunkObjectLinkProbe parent = {};
            ChunkObjectLinkProbe sibling = {};
            ChunkObjectLinkProbe child = {};
            CaptureChunkObjectLinkProbe(parentBytes, parent);
            CaptureChunkObjectLinkProbe(siblingBytes, sibling);
            CaptureChunkObjectLinkProbe(childBytes, child);

            ChunkObjectIdentityCacheEntry entry = {};
            strncpy_s(entry.meshName, sizeof(entry.meshName), meshName, _TRUNCATE);
            if (source.geomName[0])
                strncpy_s(entry.geomName, sizeof(entry.geomName), source.geomName, _TRUNCATE);
            entry.classId = source.classId;
            if (!BuildChunkVdfSourceCandidateList(
                    meshName,
                    source,
                    parent,
                    sibling,
                    child,
                    entry.vdfCandidates,
                    sizeof(entry.vdfCandidates)))
            {
                PopulateChunkVdfCandidates(meshName, source);
                if (source.vdfCandidates[0])
                    strncpy_s(entry.vdfCandidates, sizeof(entry.vdfCandidates), source.vdfCandidates, _TRUNCATE);
            }

            g_ChunkObjectIdentityCache[reinterpret_cast<uintptr_t>(objectBytes)] = entry;
        }

        static void CacheChunkObjectIdentityTreeForGameObject(void* gameObject)
        {
            char meshName[48] = {};
            if (!TryGetGameObjectMeshName(gameObject, meshName, sizeof(meshName)))
                return;

            ChunkVdfAssetInfo& info = GetChunkVdfAssetInfoForMesh(meshName);
            if (!info.loaded)
                return;

            void* rootObj76 = nullptr;
            if (!TryGetGameObjectObj76(gameObject, rootObj76) || !rootObj76)
                return;

            std::vector<const uint8_t*> stack;
            stack.reserve(32);
            stack.push_back(reinterpret_cast<const uint8_t*>(rootObj76));
            std::unordered_set<uintptr_t> visited;
            visited.reserve(64);

            while (!stack.empty() && visited.size() < kChunkObjectIdentityMaxNodesPerObject)
            {
                const uint8_t* nodeBytes = stack.back();
                stack.pop_back();
                if (!nodeBytes)
                    continue;

                const uintptr_t nodeKey = reinterpret_cast<uintptr_t>(nodeBytes);
                if (!visited.insert(nodeKey).second)
                    continue;

                CacheChunkObjectIdentityForNode(nodeBytes, meshName);

                const uint8_t* parentBytes = nullptr;
                const uint8_t* siblingBytes = nullptr;
                const uint8_t* childBytes = nullptr;
                if (!TryReadChunkObjectLinks(nodeBytes, parentBytes, siblingBytes, childBytes))
                    continue;

                if (siblingBytes)
                    stack.push_back(siblingBytes);
                if (childBytes)
                    stack.push_back(childBytes);
            }
        }

        void RefreshChunkObjectIdentityCacheIfNeeded()
        {
            if (!g_TraceChunkRender &&
                !g_TraceChunkEffectRuntime &&
                !g_EnableChunkProxyDebug &&
                !g_EnableChunkMeshProxy)
            {
                return;
            }

            const DWORD now = GetTickCount();
            if (g_ChunkObjectIdentityLastRefreshTick != 0 &&
                static_cast<DWORD>(now - g_ChunkObjectIdentityLastRefreshTick) < kChunkObjectIdentityRefreshMs)
            {
                return;
            }
            g_ChunkObjectIdentityLastRefreshTick = now;

            // NOTE: until 2026-07-18 this walked the stale advisory-PDB
            // object-list global, whose sanity checks always failed — so the
            // identity cache had silently stayed empty since it was written.
            // The arena walk makes it populate for the first time.
            static void* s_identityObjects[kGameObjectArenaSlotCapacity];
            const size_t totalObjects =
                CollectLiveGameObjectsFromArena(s_identityObjects, kGameObjectArenaSlotCapacity);
            if (totalObjects == 0)
                return;

            const size_t objectLimit =
                (totalObjects < kChunkObjectIdentityMaxObjectsPerRefresh)
                    ? totalObjects
                    : kChunkObjectIdentityMaxObjectsPerRefresh;

            g_ChunkObjectIdentityCache.clear();
            g_ChunkObjectIdentityCache.reserve(objectLimit * 8);
            for (size_t index = 0; index < objectLimit; ++index)
                CacheChunkObjectIdentityTreeForGameObject(s_identityObjects[index]);
        }
    }

}
