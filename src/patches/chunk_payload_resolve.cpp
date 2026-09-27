// chunk_payload_resolve.cpp
// BZR Open Shim - chunk proxy payload resolution: mapping a legacy chunk
// geom to an Ogre payload mesh through the payload directories, the geo
// manifest and the VDF/SDF asset index, split out of bzr_hooks.cpp.
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
        static std::unordered_map<std::string, ChunkVdfAssetInfo> g_ChunkVdfAssetCache = {};

        // Distributable replacement for shipping the stock VDF/SDF files:
        // a text manifest holding just the geo-piece names/hierarchy, seeded
        // into g_ChunkVdfAssetCache before any Edit\stock fallback runs.
        static bool g_ChunkGeoManifestAttempted = false;

        static constexpr const char* kChunkGeoManifestFileName = "chunk_geo_manifest.txt";

        static bool g_ChunkVdfReverseIndexAttempted = false;
        static std::unordered_map<std::string, std::vector<ChunkVdfMeshRef>> g_ChunkVdfGeomReverseIndex = {};

        static constexpr size_t kChunkPayloadResolveFailureLogCacheLimit = 512;

        static std::string ReadFixedAsciiField(const uint8_t* bytes, size_t length)
        {
            if (!bytes || length == 0)
                return {};

            size_t end = 0;
            while (end < length && bytes[end] != 0)
                ++end;

            std::string text(reinterpret_cast<const char*>(bytes), end);
            return TrimAsciiCopy(text);
        }

        static uint32_t ReadLeU32(const uint8_t* bytes)
        {
            if (!bytes)
                return 0;

            uint32_t value = 0;
            std::memcpy(&value, bytes, sizeof(value));
            return value;
        }

        static std::string NormalizeChunkMeshBaseName(const char* meshName)
        {
            if (!meshName || !*meshName)
                return {};

            std::string baseName(meshName);
            const size_t slash = baseName.find_last_of("/\\");
            if (slash != std::string::npos)
                baseName.erase(0, slash + 1);

            const size_t dot = baseName.find_last_of('.');
            if (dot != std::string::npos)
                baseName.erase(dot);

            std::transform(
                baseName.begin(),
                baseName.end(),
                baseName.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
            return baseName;
        }

        std::filesystem::path GetChunkPayloadStockResourceDirectory()
        {
            return GetMainModuleDirectory() / "BZ_ASSETS" / "common" / "models" / kChunkPayloadResourceRootName;
        }

        void RefreshChunkPayloadResourceDirectories()
        {
            g_ChunkPayloadResourceDirectories.clear();

            const std::filesystem::path gameDir = GetMainModuleDirectory();
            static constexpr const char* kPayloadDirNames[] =
            {
                kChunkPayloadModRelativeDirName,
                kChunkPayloadModRelativeDirNameAlt,
            };
            for (const std::filesystem::path& modRoot : GetCampaignContentRootCandidates(gameDir))
            {
                for (const char* dirName : kPayloadDirNames)
                {
                    const std::filesystem::path candidate = modRoot / dirName;
                    std::error_code ec;
                    if (std::filesystem::exists(candidate, ec) && !ec &&
                        std::filesystem::is_directory(candidate, ec) && !ec)
                    {
                        AppendUniquePath(g_ChunkPayloadResourceDirectories, candidate);
                    }
                }
            }

            const std::filesystem::path stockDir = GetChunkPayloadStockResourceDirectory();
            std::error_code stockError;
            if (std::filesystem::exists(stockDir, stockError) && !stockError &&
                std::filesystem::is_directory(stockDir, stockError) && !stockError)
            {
                AppendUniquePath(g_ChunkPayloadResourceDirectories, stockDir);
            }
        }

        static const std::vector<std::filesystem::path>& GetChunkPayloadResourceDirectories()
        {
            if (g_ChunkPayloadResourceDirectories.empty())
                RefreshChunkPayloadResourceDirectories();

            return g_ChunkPayloadResourceDirectories;
        }

        std::string NormalizeChunkPayloadComponentName(const char* value)
        {
            return NormalizeChunkMeshBaseName(value);
        }

        static void AppendUniqueChunkPayloadCandidate(
            std::vector<std::string>& candidates,
            const std::string& candidate)
        {
            if (candidate.empty())
                return;

            // Candidate strings are pre-normalized to lowercase by callers via
            // NormalizeChunkMeshBaseName / NormalizeChunkPayloadComponentName.
            // Using operator== provides O(1) string length short-circuiting
            // and fast byte comparison without CRT locale overhead (_stricmp).
            for (const std::string& existing : candidates)
            {
                if (existing == candidate)
                    return;
            }

            candidates.push_back(candidate);
        }

        static void AppendChunkPayloadCandidatesFromPipeList(
            const char* listText,
            std::vector<std::string>& outCandidates)
        {
            if (!listText || !*listText)
                return;

            const char* cursor = listText;
            while (*cursor)
            {
                const char* separator = std::strchr(cursor, '|');
                const size_t tokenLength = separator
                    ? static_cast<size_t>(separator - cursor)
                    : std::strlen(cursor);
                if (tokenLength > 0)
                {
                    std::string token(cursor, tokenLength);
                    AppendUniqueChunkPayloadCandidate(
                        outCandidates,
                        NormalizeChunkPayloadComponentName(token.c_str()));
                }

                if (!separator)
                    break;
                cursor = separator + 1;
            }
        }

        static std::string JoinChunkPayloadCandidates(const std::vector<std::string>& candidates)
        {
            std::string result;
            for (size_t index = 0; index < candidates.size(); ++index)
            {
                if (index != 0)
                    result += "|";
                result += candidates[index];
            }

            return result;
        }

        static void LogChunkPayloadResolveFailureOnce(
            const ChunkObjectLinkProbe& probe,
            const char* preferredMeshName,
            const char* explicitGeomName,
            const std::vector<std::string>& meshCandidates,
            const std::vector<std::string>& geomCandidates)
        {
            if (!g_EnableChunkMeshProxy && !g_TraceChunkRender && !g_TraceChunkEffectRuntime)
                return;

            const std::string meshCandidateText = JoinChunkPayloadCandidates(meshCandidates);
            const std::string geomCandidateText = JoinChunkPayloadCandidates(geomCandidates);

            std::string fingerprint;
            fingerprint.reserve(
                meshCandidateText.size() + geomCandidateText.size() +
                std::strlen(probe.cachedMeshName) + std::strlen(probe.geomName) +
                std::strlen(probe.vdfCandidates) + 48);
            fingerprint += meshCandidateText;
            fingerprint += "||";
            fingerprint += geomCandidateText;
            fingerprint += "||";
            fingerprint += probe.cachedMeshName;
            fingerprint += "||";
            fingerprint += probe.geomName;
            fingerprint += "||";
            fingerprint += probe.vdfCandidates;

            if (g_ChunkPayloadResolveFailureLogCache.size() >= kChunkPayloadResolveFailureLogCacheLimit &&
                g_ChunkPayloadResolveFailureLogCache.find(fingerprint) == g_ChunkPayloadResolveFailureLogCache.end())
            {
                g_ChunkPayloadResolveFailureLogCache.clear();
            }

            if (!g_ChunkPayloadResolveFailureLogCache.insert(fingerprint).second)
                return;

            // Acquire the shared slot only once the dedup cache says this line
            // will actually be written; otherwise repeated resolve failures
            // drain the budget silently and blind all lifecycle logging.
            if (!AcquireChunkLogSlot())
                return;

            LogChunkDiagnostic(
                "chunkmesh",
                L"[CHUNKMESH] payload resolve miss obj=0x%08X class=%u preferredMesh=%hs cachedMesh=%hs explicitGeom=%hs probeGeom=%hs vdf=%hs meshCandidates=%hs geomCandidates=%hs\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(probe.objectBytes)),
                probe.classId,
                preferredMeshName ? preferredMeshName : "",
                probe.cachedMeshName[0] ? probe.cachedMeshName : "<none>",
                explicitGeomName ? explicitGeomName : "",
                probe.geomName[0] ? probe.geomName : "<none>",
                probe.vdfCandidates[0] ? probe.vdfCandidates : "<none>",
                meshCandidateText.empty() ? "<none>" : meshCandidateText.c_str(),
                geomCandidateText.empty() ? "<none>" : geomCandidateText.c_str());
        }

        static bool ChunkPayloadFlatMeshExists(const std::string& fileName)
        {
            if (fileName.empty())
                return false;

            auto cacheIt = g_ChunkPayloadMeshExistsCache.find(fileName);
            if (cacheIt != g_ChunkPayloadMeshExistsCache.end())
                return cacheIt->second;

            bool exists = false;
            for (const std::filesystem::path& resourceRoot : GetChunkPayloadResourceDirectories())
            {
                std::error_code error;
                if (std::filesystem::exists(resourceRoot / fileName, error) && !error)
                {
                    exists = true;
                    break;
                }
            }
            g_ChunkPayloadMeshExistsCache.emplace(fileName, exists);
            return exists;
        }

        // Lowercased payload stems per craft directory, built once on demand.
        static std::unordered_map<std::string, std::vector<std::string>> g_ChunkPayloadDirListingCache;

        static const std::vector<std::string>& GetChunkPayloadDirListing(const std::string& meshBase)
        {
            const auto cached = g_ChunkPayloadDirListingCache.find(meshBase);
            if (cached != g_ChunkPayloadDirListingCache.end())
                return cached->second;

            std::vector<std::string> stems;
            for (const std::filesystem::path& resourceRoot : GetChunkPayloadResourceDirectories())
            {
                std::error_code error;
                for (std::filesystem::directory_iterator it(resourceRoot / meshBase, error);
                     !error && it != std::filesystem::directory_iterator();
                     it.increment(error))
                {
                    const auto& entry = *it;
                    if (!entry.is_regular_file(error) || error)
                        continue;

                    std::string extension = entry.path().extension().string();
                    std::transform(
                        extension.begin(),
                        extension.end(),
                        extension.begin(),
                        [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
                    if (extension != ".mesh")
                        continue;

                    stems.emplace_back(NormalizeChunkPayloadComponentName(
                        entry.path().stem().string().c_str()));
                }
            }

            return g_ChunkPayloadDirListingCache.emplace(meshBase, std::move(stems)).first->second;
        }

        // A payload whose name matches this geo once punctuation is ignored.
        //
        // ablpad's Redux model names its first piece bone "alp11_bda" where the
        // simulation fragments "alp11bda" -- a stray underscore, and the only
        // instance of its kind across every stock model (ablpad and bblpad share
        // the bone). Scoped to the craft's own directory and requiring a unique
        // hit, exactly like the prefix translation below, so it cannot reach
        // across to another building or pick between ambiguous candidates.
        static const std::string* FindChunkPayloadByRelaxedGeomName(
            const std::string& meshBase,
            const std::string& geomBase)
        {
            const auto strip = [](const std::string& value) {
                std::string out;
                out.reserve(value.size());
                for (const char ch : value)
                {
                    if (std::isalnum(static_cast<unsigned char>(ch)))
                        out.push_back(ch);
                }
                return out;
            };

            // The punctuation is on the payload side, not in the name the
            // simulation asks for, so do not gate on geomBase being dirty.
            const std::string wanted = strip(geomBase);
            if (wanted.empty())
                return nullptr;

            const std::string* match = nullptr;
            for (const std::string& stem : GetChunkPayloadDirListing(meshBase))
            {
                if (stem == geomBase || strip(stem) != wanted)
                    continue;

                if (match)
                    return nullptr;
                match = &stem;
            }

            return match;
        }

        // A payload whose name is this geo's with a different three-character
        // prefix -- same length, same tail -- and only when exactly one file in
        // the craft's own directory qualifies.
        static const std::string* FindChunkPayloadByGeomSuffix(
            const std::string& meshBase,
            const std::string& geomBase)
        {
            const std::vector<std::string>& stems = GetChunkPayloadDirListing(meshBase);

            const std::string* match = nullptr;
            for (const std::string& stem : stems)
            {
                if (stem.size() != geomBase.size())
                    continue;
                if (stem.compare(3, std::string::npos, geomBase, 3, std::string::npos) != 0)
                    continue;
                if (stem.compare(0, 3, geomBase, 0, 3) == 0)
                    continue;

                if (match)
                    return nullptr;
                match = &stem;
            }

            return match;
        }

        static bool TryResolveChunkPayloadMeshResourceForMeshAndGeom(
            const char* meshName,
            const char* geomName,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';
            const std::string meshBase = NormalizeChunkMeshBaseName(meshName);
            const std::string geomBase = NormalizeChunkPayloadComponentName(geomName);
            if (meshBase.empty() || geomBase.empty())
                return false;

            const std::string payloadFileName = geomBase + ".mesh";

            std::string nestedResourceName = meshBase;
            nestedResourceName += "/";
            nestedResourceName += payloadFileName;

            auto nestedCacheIt = g_ChunkPayloadMeshExistsCache.find(nestedResourceName);
            bool nestedExists = false;
            if (nestedCacheIt != g_ChunkPayloadMeshExistsCache.end())
            {
                nestedExists = nestedCacheIt->second;
            }
            else
            {
                for (const std::filesystem::path& resourceRoot : GetChunkPayloadResourceDirectories())
                {
                    const std::filesystem::path payloadPath = resourceRoot / meshBase / payloadFileName;
                    std::error_code error;
                    if (std::filesystem::exists(payloadPath, error) && !error)
                    {
                        nestedExists = true;
                        break;
                    }
                }
                g_ChunkPayloadMeshExistsCache.emplace(nestedResourceName, nestedExists);
            }

            if (nestedExists)
            {
                strncpy_s(outMeshName, outMeshNameCapacity, nestedResourceName.c_str(), _TRUNCATE);
                return outMeshName[0] != '\0';
            }

            // Some models name their bones "<craft>_<geo>" (sbsilo ships
            // sbsilo_sss11bda.mesh and friends), so the export carried the prefix
            // through. Cheap exact probe before the directory scan below.
            const std::string prefixedFileName = meshBase + "_" + payloadFileName;
            std::string prefixedResourceName = meshBase;
            prefixedResourceName += "/";
            prefixedResourceName += prefixedFileName;

            auto prefixedCacheIt = g_ChunkPayloadMeshExistsCache.find(prefixedResourceName);
            bool prefixedExists = false;
            if (prefixedCacheIt != g_ChunkPayloadMeshExistsCache.end())
            {
                prefixedExists = prefixedCacheIt->second;
            }
            else
            {
                for (const std::filesystem::path& resourceRoot : GetChunkPayloadResourceDirectories())
                {
                    const std::filesystem::path payloadPath = resourceRoot / meshBase / prefixedFileName;
                    std::error_code error;
                    if (std::filesystem::exists(payloadPath, error) && !error)
                    {
                        prefixedExists = true;
                        break;
                    }
                }
                g_ChunkPayloadMeshExistsCache.emplace(prefixedResourceName, prefixedExists);
            }

            if (prefixedExists)
            {
                strncpy_s(outMeshName, outMeshNameCapacity, prefixedResourceName.c_str(), _TRUNCATE);
                return outMeshName[0] != '\0';
            }

            // Punctuation-insensitive match inside the craft's own directory,
            // for models whose bone names carry a stray separator (ablpad's
            // alp11_bda against the simulation's alp11bda).
            if (const std::string* relaxed =
                    FindChunkPayloadByRelaxedGeomName(meshBase, geomBase))
            {
                std::string relaxedResourceName = meshBase;
                relaxedResourceName += "/";
                relaxedResourceName += *relaxed;
                relaxedResourceName += ".mesh";
                strncpy_s(
                    outMeshName, outMeshNameCapacity, relaxedResourceName.c_str(), _TRUNCATE);
                return outMeshName[0] != '\0';
            }

            // Two Black Dog buildings carry piece names in their Redux models
            // that differ from the names the simulation uses, in the first three
            // characters only: bbhang's sim geos are abh11* while its payloads
            // are bbh11*, and bbsilo runs the other way (bss11* -> ass11*). Every
            // other twin matches outright. Without this they resolve nothing and
            // every Black Dog hangar/silo chunk becomes a placeholder.
            //
            // Scoped to the already-resolved craft directory, so it can only ever
            // pick a piece of the right building with the right material -- it
            // cannot reach across to the NSDF twin. Requires a unique hit.
            if (geomBase.size() > 4)
            {
                if (const std::string* translated =
                        FindChunkPayloadByGeomSuffix(meshBase, geomBase))
                {
                    std::string translatedResourceName = meshBase;
                    translatedResourceName += "/";
                    translatedResourceName += *translated;
                    translatedResourceName += ".mesh";
                    strncpy_s(
                        outMeshName, outMeshNameCapacity, translatedResourceName.c_str(), _TRUNCATE);
                    return outMeshName[0] != '\0';
                }
            }

            auto flatCacheIt = g_ChunkPayloadMeshExistsCache.find(payloadFileName);
            bool flatExists = false;
            if (flatCacheIt != g_ChunkPayloadMeshExistsCache.end())
            {
                flatExists = flatCacheIt->second;
            }
            else
            {
                for (const std::filesystem::path& resourceRoot : GetChunkPayloadResourceDirectories())
                {
                    const std::filesystem::path payloadPath = resourceRoot / payloadFileName;
                    std::error_code error;
                    if (std::filesystem::exists(payloadPath, error) && !error)
                    {
                        flatExists = true;
                        break;
                    }
                }
                g_ChunkPayloadMeshExistsCache.emplace(payloadFileName, flatExists);
            }

            if (!flatExists)
                return false;

            strncpy_s(outMeshName, outMeshNameCapacity, payloadFileName.c_str(), _TRUNCATE);
            return outMeshName[0] != '\0';
        }

        static bool TryResolveGenericChunkPayloadFallback(
            const char* seedName,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';

            std::vector<std::string> available;
            for (uint32_t index = 1; index <= 8; ++index)
            {
                char geomBuffer[16] = {};
                _snprintf_s(geomBuffer, _TRUNCATE, "iechunk%u", index);
                char resourceName[128] = {};
                if (TryResolveChunkPayloadMeshResourceForMeshAndGeom(
                        "generic",
                        geomBuffer,
                        resourceName,
                        sizeof(resourceName)))
                {
                    available.emplace_back(resourceName);
                }
            }
            if (available.empty())
                return false;

            uint32_t hash = 2166136261u;
            for (const char* ch = seedName ? seedName : ""; *ch; ++ch)
            {
                hash ^= static_cast<uint8_t>(std::tolower(static_cast<unsigned char>(*ch)));
                hash *= 16777619u;
            }

            const std::string& pick = available[hash % available.size()];
            strncpy_s(outMeshName, outMeshNameCapacity, pick.c_str(), _TRUNCATE);
            return outMeshName[0] != '\0';
        }

        bool TryResolveChunkPayloadMeshResource(
            const ChunkObjectLinkProbe& probe,
            const char* preferredMeshName,
            const char* explicitGeomName,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';

            std::vector<std::string> meshCandidates;
            meshCandidates.reserve(2);
            AppendUniqueChunkPayloadCandidate(meshCandidates, NormalizeChunkMeshBaseName(preferredMeshName));
            AppendUniqueChunkPayloadCandidate(meshCandidates, NormalizeChunkMeshBaseName(probe.cachedMeshName));

            // Identity caches only cover objects seen live before death; a
            // chunk that missed them (buildings especially) can still be
            // identified purely from its own geo name when the VDF/SDF
            // reverse index maps it to exactly one craft.
            if (meshCandidates.empty())
            {
                char inferredMeshName[48] = {};
                const char* inferGeomName =
                    (explicitGeomName && explicitGeomName[0]) ? explicitGeomName : probe.geomName;
                if (TryInferChunkMeshNameFromGeom(
                        inferGeomName,
                        probe.classId,
                        inferredMeshName,
                        sizeof(inferredMeshName)))
                {
                    AppendUniqueChunkPayloadCandidate(
                        meshCandidates, NormalizeChunkMeshBaseName(inferredMeshName));
                }
            }

            // The ODF name off the owning GameObject's class is the one piece of
            // craft identity the engine states outright rather than us inferring
            // it, so it settles faction twins the geo name cannot: an abhang and
            // a bbhang share every geo name but never share an ODF. It goes in
            // ahead of the try-every-twin sweep below and behind the identity
            // caches above, and like every candidate here it only wins if its
            // payload file actually exists -- an ODF whose model differs from its
            // own name (variant ODFs) simply misses and costs nothing.
            AppendUniqueChunkPayloadCandidate(
                meshCandidates, NormalizeChunkMeshBaseName(g_ActiveFragmentSourceOdfName));

            // Faction twins (abspow/bbspow, abtowe/bbtowe, ...) share their
            // entire piece list, so the single-craft inference above refuses
            // them. The lookup below is gated on the payload file actually
            // existing per candidate, and twin payload dirs ship the same
            // per-piece mesh files, so trying every craft the reverse index
            // maps this geo to still yields the correct piece.
            if (meshCandidates.empty())
            {
                const char* inferGeomName =
                    (explicitGeomName && explicitGeomName[0]) ? explicitGeomName : probe.geomName;
                AppendAllChunkMeshBasesForGeom(inferGeomName, probe.classId, meshCandidates);
            }

            // Last resort: some pieces were exported into a folder named after
            // the geo itself rather than the craft (apc11bda/apc11bda.mesh,
            // apm11bda/apm11bda.mesh) while the craft folder holds unrelated
            // exporter node names. Tried after every craft-scoped candidate so a
            // correct craft folder always wins.
            AppendUniqueChunkPayloadCandidate(
                meshCandidates, NormalizeChunkPayloadComponentName(explicitGeomName));
            AppendUniqueChunkPayloadCandidate(
                meshCandidates, NormalizeChunkPayloadComponentName(probe.geomName));

            std::vector<std::string> geomCandidates;
            geomCandidates.reserve(4);
            AppendUniqueChunkPayloadCandidate(geomCandidates, NormalizeChunkPayloadComponentName(explicitGeomName));
            AppendUniqueChunkPayloadCandidate(geomCandidates, NormalizeChunkPayloadComponentName(probe.geomName));
            // The VDF candidate list names OTHER pieces of the source craft.
            // Substituting one of those is only acceptable when the chunk's
            // own geo name could not be read at all — otherwise a resolve
            // miss (or a stale craft binding) turns into a visibly wrong
            // piece instead of an invisible chunk.
            if (geomCandidates.empty())
                AppendChunkPayloadCandidatesFromPipeList(probe.vdfCandidates, geomCandidates);

            for (const std::string& meshCandidate : meshCandidates)
            {
                for (const std::string& geomCandidate : geomCandidates)
                {
                    if (TryResolveChunkPayloadMeshResourceForMeshAndGeom(
                            meshCandidate.c_str(),
                            geomCandidate.c_str(),
                            outMeshName,
                            outMeshNameCapacity))
                    {
                        return true;
                    }
                }
            }

            // Generic chunklet templates ("chunk1", "chunk2", ...) have no craft
            // owner; map them onto the legacy iechunkN payload meshes when a
            // payload root ships them flat.
            for (const std::string& geomCandidate : geomCandidates)
            {
                if (geomCandidate.size() <= 5 ||
                    _strnicmp(geomCandidate.c_str(), "chunk", 5) != 0)
                {
                    continue;
                }

                bool digitsOnly = true;
                for (size_t index = 5; index < geomCandidate.size(); ++index)
                {
                    if (!std::isdigit(static_cast<unsigned char>(geomCandidate[index])))
                    {
                        digitsOnly = false;
                        break;
                    }
                }
                if (!digitsOnly)
                    continue;

                const std::string chunkletFileName = "ie" + geomCandidate + ".mesh";
                if (ChunkPayloadFlatMeshExists(chunkletFileName))
                {
                    strncpy_s(outMeshName, outMeshNameCapacity, chunkletFileName.c_str(), _TRUNCATE);
                    return true;
                }

                // Nested layouts for the same templates: chunkN/chunkN.mesh
                // and generic/iechunkN.mesh.
                if (TryResolveChunkPayloadMeshResourceForMeshAndGeom(
                        geomCandidate.c_str(),
                        geomCandidate.c_str(),
                        outMeshName,
                        outMeshNameCapacity))
                {
                    return true;
                }
                const std::string chunkletGeneric = "ie" + geomCandidate;
                if (TryResolveChunkPayloadMeshResourceForMeshAndGeom(
                        "generic",
                        chunkletGeneric.c_str(),
                        outMeshName,
                        outMeshNameCapacity))
                {
                    return true;
                }
            }

            // Last resort: a payload root can ship generic debris meshes in a
            // "generic" dir (generic/iechunkN.mesh). Seed the pick with the
            // geo name so a given piece always shatters into the same shape.
            if (TryResolveGenericChunkPayloadFallback(
                    geomCandidates.empty() ? nullptr : geomCandidates.front().c_str(),
                    outMeshName,
                    outMeshNameCapacity))
            {
                static volatile long s_GenericFallbackLogBudget = 64;
                if (InterlockedDecrement(&s_GenericFallbackLogBudget) >= 0)
                {
                    LogChunkDiagnostic(
                        "chunkmesh",
                        L"[CHUNKMESH] generic-fallback geom=%hs mesh=%hs\n",
                        geomCandidates.empty() ? "<none>" : geomCandidates.front().c_str(),
                        outMeshName);
                }
                return true;
            }

            LogChunkPayloadResolveFailureOnce(
                probe,
                preferredMeshName,
                explicitGeomName,
                meshCandidates,
                geomCandidates);
            return false;
        }

        // Manifest line format: craft|geoName|parentName|type|flags
        // ('#' comments and blank lines ignored; parent/type/flags optional).
        static void LoadChunkGeoManifestFile(
            const std::filesystem::path& manifestPath,
            uint32_t& craftCount,
            uint32_t& recordCount)
        {
            std::ifstream file(manifestPath);
            if (!file)
                return;

            std::string line;
            while (std::getline(file, line))
            {
                const std::string trimmed = TrimAsciiCopy(line);
                if (trimmed.empty() || trimmed[0] == '#')
                    continue;

                std::array<std::string, 5> fields = {};
                size_t fieldIndex = 0;
                size_t start = 0;
                while (fieldIndex < fields.size())
                {
                    const size_t separator = trimmed.find('|', start);
                    fields[fieldIndex++] =
                        TrimAsciiCopy(trimmed.substr(start, separator - start));
                    if (separator == std::string::npos)
                        break;
                    start = separator + 1;
                }

                const std::string craftBase = NormalizeChunkMeshBaseName(fields[0].c_str());
                const std::string& geoName = fields[1];
                if (craftBase.empty() || geoName.empty() ||
                    geoName.size() >= sizeof(ChunkVdfRecord{}.name) ||
                    _stricmp(geoName.c_str(), "NULL") == 0)
                {
                    continue;
                }

                ChunkVdfAssetInfo& info = g_ChunkVdfAssetCache[craftBase];
                if (!info.attempted)
                    ++craftCount;
                info.attempted = true;

                bool duplicate = false;
                for (const ChunkVdfRecord& existing : info.records)
                {
                    if (_stricmp(existing.name, geoName.c_str()) == 0 &&
                        _stricmp(existing.parent, fields[2].c_str()) == 0)
                    {
                        duplicate = true;
                        break;
                    }
                }
                if (duplicate)
                    continue;

                ChunkVdfRecord record = {};
                strncpy_s(record.name, sizeof(record.name), geoName.c_str(), _TRUNCATE);
                strncpy_s(record.parent, sizeof(record.parent), fields[2].c_str(), _TRUNCATE);
                record.type = static_cast<uint32_t>(std::strtoul(fields[3].c_str(), nullptr, 10));
                record.flags = static_cast<uint32_t>(std::strtoul(fields[4].c_str(), nullptr, 10));
                info.records.push_back(record);
                info.loaded = true;
                ++recordCount;
            }
        }

        static void EnsureChunkGeoManifestLoaded()
        {
            if (g_ChunkGeoManifestAttempted)
                return;

            g_ChunkGeoManifestAttempted = true;

            std::vector<std::filesystem::path> manifestCandidates;
            AppendUniquePath(
                manifestCandidates,
                GetMainModuleDirectory() / "scripts" / kChunkGeoManifestFileName);
            for (const std::filesystem::path& payloadDir : GetChunkPayloadResourceDirectories())
                AppendUniquePath(manifestCandidates, payloadDir / kChunkGeoManifestFileName);

            uint32_t fileCount = 0;
            uint32_t craftCount = 0;
            uint32_t recordCount = 0;
            for (const std::filesystem::path& candidate : manifestCandidates)
            {
                std::error_code error;
                if (!std::filesystem::exists(candidate, error) || error)
                    continue;

                ++fileCount;
                LoadChunkGeoManifestFile(candidate, craftCount, recordCount);
            }

            if (fileCount)
            {
                LogChunkDiagnostic(
                    "chunkmesh",
                    L"[CHUNKMESH] geo-manifest loaded files=%u crafts=%u records=%u\n",
                    fileCount,
                    craftCount,
                    recordCount);
            }
        }

        // Buildings ship as .sdf instead of .vdf: same BWD2 container, but the
        // geo table is an SGEO block (120-byte records vs VGEO's 100) whose
        // count field is authoritative — the block is padded with "NULL"
        // records to a fixed capacity.
        static bool TryLoadChunkSdfAssetInfo(
            const std::filesystem::path& sdfPath,
            ChunkVdfAssetInfo& info)
        {
            std::ifstream file(sdfPath, std::ios::binary);
            if (!file)
                return false;

            const std::vector<uint8_t> bytes(
                (std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
            constexpr size_t kSdfPreambleBytes = 20;
            constexpr size_t kSgeoHeaderBytes = 12;
            constexpr size_t kSgeoRecordBytes = 120;
            constexpr size_t kSgeoNameOffset = 0;
            constexpr size_t kSgeoParentOffset = 56;
            constexpr size_t kSgeoTypeOffset = 92;

            // Block sizes include the 8-byte tag+size header; walk until SGEO.
            size_t cursor = kSdfPreambleBytes;
            size_t sgeoOffset = 0;
            size_t sgeoSize = 0;
            while (cursor + 8 <= bytes.size())
            {
                const uint32_t blockSize = ReadLeU32(bytes.data() + cursor + 4);
                if (blockSize < 8 || cursor + blockSize > bytes.size())
                    break;

                if (std::memcmp(bytes.data() + cursor, "SGEO", 4) == 0)
                {
                    sgeoOffset = cursor;
                    sgeoSize = blockSize;
                    break;
                }
                cursor += blockSize;
            }

            if (!sgeoOffset || sgeoSize < kSgeoHeaderBytes + kSgeoRecordBytes)
                return false;

            const size_t recordCapacity = (sgeoSize - kSgeoHeaderBytes) / kSgeoRecordBytes;
            const uint32_t declaredCount = ReadLeU32(bytes.data() + sgeoOffset + 8);
            const size_t geoCount =
                (declaredCount < recordCapacity) ? declaredCount : recordCapacity;
            if (geoCount == 0)
                return false;

            const size_t recordsStart = sgeoOffset + kSgeoHeaderBytes;
            std::unordered_set<std::string> seenKeys;
            info.records.clear();
            info.records.reserve(geoCount);
            for (size_t index = 0; index < geoCount; ++index)
            {
                const size_t recordOffset = recordsStart + (index * kSgeoRecordBytes);
                const std::string name = ReadFixedAsciiField(bytes.data() + recordOffset + kSgeoNameOffset, 8);
                if (name.empty() || _stricmp(name.c_str(), "NULL") == 0)
                    continue;

                const std::string parent = ReadFixedAsciiField(bytes.data() + recordOffset + kSgeoParentOffset, 8);
                const std::string seenKey = name + "|" + parent;
                if (!seenKeys.insert(seenKey).second)
                    continue;

                ChunkVdfRecord record = {};
                strncpy_s(record.name, sizeof(record.name), name.c_str(), _TRUNCATE);
                strncpy_s(record.parent, sizeof(record.parent), parent.c_str(), _TRUNCATE);
                record.type = ReadLeU32(bytes.data() + recordOffset + kSgeoTypeOffset);
                info.records.push_back(record);
            }

            info.loaded = !info.records.empty();
            return info.loaded;
        }

        ChunkVdfAssetInfo& GetChunkVdfAssetInfoForMesh(const char* meshName)
        {
            static ChunkVdfAssetInfo kEmptyInfo = {};

            const std::string baseName = NormalizeChunkMeshBaseName(meshName);
            if (baseName.empty())
                return kEmptyInfo;

            EnsureChunkGeoManifestLoaded();

            ChunkVdfAssetInfo& info = g_ChunkVdfAssetCache[baseName];
            if (info.attempted)
                return info;

            info.attempted = true;

            const std::filesystem::path stockDir = GetMainModuleDirectory() / "Edit" / "stock";
            const std::filesystem::path vdfPath = stockDir / (baseName + ".vdf");
            std::error_code error;
            if (!std::filesystem::exists(vdfPath, error) || error)
            {
                const std::filesystem::path sdfPath = stockDir / (baseName + ".sdf");
                std::error_code sdfError;
                if (std::filesystem::exists(sdfPath, sdfError) && !sdfError)
                    TryLoadChunkSdfAssetInfo(sdfPath, info);
                return info;
            }

            std::ifstream file(vdfPath, std::ios::binary);
            if (!file)
                return info;

            const std::vector<uint8_t> bytes(
                (std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
            constexpr size_t kVdfHeaderBytes = 20;
            constexpr size_t kVdfcHeaderBytes = 68;
            constexpr size_t kExitBytes = 8;
            constexpr size_t kVgeoHeaderBytes = 12;
            constexpr size_t kVgeoRecordBytes = 100;
            constexpr size_t kVgeoNameOffset = 0;
            constexpr size_t kVgeoParentOffset = 56;
            constexpr size_t kVgeoTypeOffset = 92;
            constexpr size_t kVgeoFlagsOffset = 96;

            if (bytes.size() < (kVdfHeaderBytes + kVdfcHeaderBytes + kExitBytes + kVgeoHeaderBytes))
                return info;

            size_t cursor = kVdfHeaderBytes + kVdfcHeaderBytes + kExitBytes;
            const int32_t geoCount = static_cast<int32_t>(ReadLeU32(bytes.data() + cursor + 8));
            cursor += kVgeoHeaderBytes;
            if (geoCount <= 0)
                return info;

            if (bytes.size() < cursor + (static_cast<size_t>(geoCount) * kVgeoRecordBytes))
                return info;

            std::unordered_set<std::string> seenKeys;
            info.records.clear();
            info.records.reserve(static_cast<size_t>(geoCount));
            for (int32_t index = 0; index < geoCount; ++index)
            {
                const size_t recordOffset = cursor + (static_cast<size_t>(index) * kVgeoRecordBytes);
                const std::string name = ReadFixedAsciiField(bytes.data() + recordOffset + kVgeoNameOffset, 8);
                if (name.empty() || _stricmp(name.c_str(), "NULL") == 0)
                    continue;

                const std::string parent = ReadFixedAsciiField(bytes.data() + recordOffset + kVgeoParentOffset, 8);
                const std::string seenKey = name + "|" + parent;
                if (!seenKeys.insert(seenKey).second)
                    continue;

                ChunkVdfRecord record = {};
                strncpy_s(record.name, sizeof(record.name), name.c_str(), _TRUNCATE);
                strncpy_s(record.parent, sizeof(record.parent), parent.c_str(), _TRUNCATE);
                record.type = ReadLeU32(bytes.data() + recordOffset + kVgeoTypeOffset);
                record.flags = ReadLeU32(bytes.data() + recordOffset + kVgeoFlagsOffset);
                info.records.push_back(record);
            }

            info.loaded = !info.records.empty();
            return info;
        }

        static void AddChunkVdfReverseIndexRecord(
            const std::string& geomName,
            const std::string& meshBase,
            uint32_t type)
        {
            if (geomName.empty() || meshBase.empty())
                return;

            std::string key = geomName;
            std::transform(
                key.begin(),
                key.end(),
                key.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

            auto& refs = g_ChunkVdfGeomReverseIndex[key];
            for (const ChunkVdfMeshRef& existing : refs)
            {
                if (_stricmp(existing.meshBase, meshBase.c_str()) == 0 && existing.type == type)
                    return;
            }

            ChunkVdfMeshRef ref = {};
            strncpy_s(ref.meshBase, sizeof(ref.meshBase), meshBase.c_str(), _TRUNCATE);
            ref.type = type;
            refs.push_back(ref);
        }

        static void EnsureChunkVdfReverseIndex()
        {
            if (g_ChunkVdfReverseIndexAttempted)
                return;

            g_ChunkVdfReverseIndexAttempted = true;

            EnsureChunkGeoManifestLoaded();
            for (const auto& [meshBase, info] : g_ChunkVdfAssetCache)
            {
                if (!info.loaded)
                    continue;
                for (const ChunkVdfRecord& record : info.records)
                {
                    if (record.name[0])
                        AddChunkVdfReverseIndexRecord(record.name, meshBase, record.type);
                }
            }

            const std::filesystem::path stockDir = GetMainModuleDirectory() / "Edit" / "stock";
            std::error_code error;
            if (!std::filesystem::exists(stockDir, error) || error)
                return;

            for (std::filesystem::directory_iterator it(stockDir, error);
                 !error && it != std::filesystem::directory_iterator();
                 it.increment(error))
            {
                const auto& entry = *it;
                if (!entry.is_regular_file(error) || error)
                    continue;

                std::string extension = entry.path().extension().string();
                std::transform(
                    extension.begin(),
                    extension.end(),
                    extension.begin(),
                    [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
                if (extension != ".vdf" && extension != ".sdf")
                    continue;

                const std::string meshBase = entry.path().stem().string();
                ChunkVdfAssetInfo& info = GetChunkVdfAssetInfoForMesh(meshBase.c_str());
                if (!info.loaded)
                    continue;

                for (const ChunkVdfRecord& record : info.records)
                {
                    if (!record.name[0])
                        continue;
                    AddChunkVdfReverseIndexRecord(record.name, meshBase, record.type);
                }
            }
        }

        static bool TryCopyChunkVdfExactName(
            const char* meshName,
            const char* geomName,
            uint32_t classId,
            char* outText,
            size_t outTextCapacity)
        {
            if (!outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';
            if (!meshName || !*meshName || !geomName || !*geomName)
                return false;

            ChunkVdfAssetInfo& info = GetChunkVdfAssetInfoForMesh(meshName);
            if (!info.loaded)
                return false;

            for (const ChunkVdfRecord& record : info.records)
            {
                if (!record.name[0] || _stricmp(record.name, geomName) != 0)
                    continue;
                if (classId != 0 && record.type != classId)
                    continue;

                strncpy_s(outText, outTextCapacity, record.name, _TRUNCATE);
                return outText[0] != '\0';
            }

            return false;
        }

        static bool BuildChunkVdfCandidateList(
            const char* meshName,
            uint32_t classId,
            char* outText,
            size_t outTextCapacity)
        {
            if (!outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';
            if (!meshName || !*meshName || classId == 0)
                return false;

            ChunkVdfAssetInfo& info = GetChunkVdfAssetInfoForMesh(meshName);
            if (!info.loaded)
                return false;

            bool wroteAny = false;
            for (const ChunkVdfRecord& record : info.records)
            {
                if (record.type != classId || !record.name[0])
                    continue;

                const size_t currentLength = std::strlen(outText);
                if (currentLength + (wroteAny ? 1 : 0) + std::strlen(record.name) + 1 >= outTextCapacity)
                    break;

                if (wroteAny)
                    strcat_s(outText, outTextCapacity, "|");
                strcat_s(outText, outTextCapacity, record.name);
                wroteAny = true;
            }

            return wroteAny;
        }

        static uint32_t FindChunkVdfRecordTypeByName(
            const ChunkVdfAssetInfo& info,
            const char* name)
        {
            if (!name || !*name)
                return 0;

            for (const ChunkVdfRecord& record : info.records)
            {
                if (record.name[0] && _stricmp(record.name, name) == 0)
                    return record.type;
            }

            return 0;
        }

        static bool ChunkVdfRecordHasSiblingType(
            const ChunkVdfAssetInfo& info,
            const ChunkVdfRecord& record,
            uint32_t siblingClassId)
        {
            if (siblingClassId == 0)
                return true;

            for (const ChunkVdfRecord& other : info.records)
            {
                if (&other == &record)
                    continue;
                if (other.type != siblingClassId)
                    continue;
                if (_stricmp(other.parent, record.parent) == 0)
                    return true;
            }

            return false;
        }

        static bool ChunkVdfRecordHasChildType(
            const ChunkVdfAssetInfo& info,
            const ChunkVdfRecord& record,
            uint32_t childClassId)
        {
            if (childClassId == 0)
                return true;

            for (const ChunkVdfRecord& other : info.records)
            {
                if (other.type != childClassId)
                    continue;
                if (_stricmp(other.parent, record.name) == 0)
                    return true;
            }

            return false;
        }

        static bool ChunkVdfRecordMatchesTree(
            const ChunkVdfAssetInfo& info,
            const ChunkVdfRecord& record,
            const ChunkObjectLinkProbe& source,
            const ChunkObjectLinkProbe& parent,
            const ChunkObjectLinkProbe& sibling,
            const ChunkObjectLinkProbe& child)
        {
            if (!record.name[0] || record.type != source.classId)
                return false;

            if (source.geomName[0] && _stricmp(source.geomName, record.name) != 0)
                return false;

            if (parent.objectBytes && parent.classId != 0)
            {
                if (parent.classId == 1)
                {
                    if (_stricmp(record.parent, "WORLD") != 0)
                        return false;
                }
                else
                {
                    if (!record.parent[0])
                        return false;

                    const uint32_t parentType = FindChunkVdfRecordTypeByName(info, record.parent);
                    if (parentType != parent.classId)
                        return false;

                    if (parent.geomName[0] && _stricmp(parent.geomName, record.parent) != 0)
                        return false;
                }
            }

            if (sibling.objectBytes && sibling.classId != 0)
            {
                if (!ChunkVdfRecordHasSiblingType(info, record, sibling.classId))
                    return false;
            }

            if (child.objectBytes && child.classId != 0)
            {
                if (!ChunkVdfRecordHasChildType(info, record, child.classId))
                    return false;
            }

            return true;
        }

        bool BuildChunkVdfSourceCandidateList(
            const char* meshName,
            const ChunkObjectLinkProbe& source,
            const ChunkObjectLinkProbe& parent,
            const ChunkObjectLinkProbe& sibling,
            const ChunkObjectLinkProbe& child,
            char* outText,
            size_t outTextCapacity)
        {
            if (!outText || outTextCapacity == 0)
                return false;

            outText[0] = '\0';
            if (!meshName || !*meshName || !source.objectBytes || source.classId == 0)
                return false;

            ChunkVdfAssetInfo& info = GetChunkVdfAssetInfoForMesh(meshName);
            if (!info.loaded)
                return false;

            bool wroteAny = false;
            for (const ChunkVdfRecord& record : info.records)
            {
                if (!ChunkVdfRecordMatchesTree(info, record, source, parent, sibling, child))
                    continue;

                const size_t currentLength = std::strlen(outText);
                if (currentLength + (wroteAny ? 1 : 0) + std::strlen(record.name) + 1 >= outTextCapacity)
                    break;

                if (wroteAny)
                    strcat_s(outText, outTextCapacity, "|");
                strcat_s(outText, outTextCapacity, record.name);
                wroteAny = true;
            }

            return wroteAny;
        }

        void PopulateChunkVdfCandidates(const char* meshName, ChunkObjectLinkProbe& probe)
        {
            probe.vdfCandidates[0] = '\0';
            if (!probe.objectBytes || !meshName || !*meshName)
                return;

            if (probe.geomName[0] &&
                TryCopyChunkVdfExactName(
                    meshName,
                    probe.geomName,
                    probe.classId,
                    probe.vdfCandidates,
                    sizeof(probe.vdfCandidates)))
            {
                return;
            }

            BuildChunkVdfCandidateList(meshName, probe.classId, probe.vdfCandidates, sizeof(probe.vdfCandidates));
        }

        bool TryInferChunkMeshNameFromGeom(
            const char* geomName,
            uint32_t classId,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';
            if (!geomName || !*geomName)
                return false;
            if (_stricmp(geomName, "chunk1") == 0 || _stricmp(geomName, "chunk2") == 0)
                return false;

            EnsureChunkVdfReverseIndex();

            std::string key(geomName);
            std::transform(
                key.begin(),
                key.end(),
                key.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

            const auto it = g_ChunkVdfGeomReverseIndex.find(key);
            if (it == g_ChunkVdfGeomReverseIndex.end() || it->second.empty())
                return false;

            const ChunkVdfMeshRef* selected = nullptr;
            for (const ChunkVdfMeshRef& ref : it->second)
            {
                if (classId != 0 && ref.type != classId)
                    continue;

                if (!selected)
                {
                    selected = &ref;
                    continue;
                }

                if (_stricmp(selected->meshBase, ref.meshBase) != 0)
                    return false;
            }

            if (!selected)
            {
                for (const ChunkVdfMeshRef& ref : it->second)
                {
                    if (!selected)
                    {
                        selected = &ref;
                        continue;
                    }

                    if (_stricmp(selected->meshBase, ref.meshBase) != 0)
                        return false;
                }
            }

            if (!selected || !selected->meshBase[0])
                return false;

            _snprintf_s(outMeshName, outMeshNameCapacity, _TRUNCATE, "%s.mesh", selected->meshBase);
            return outMeshName[0] != '\0';
        }

        // Unlike TryInferChunkMeshNameFromGeom this does not refuse ambiguous
        // geo names; it hands back every craft the reverse index knows, in
        // stable alphabetical order, for callers that can verify candidates
        // against actual payload files.
        void AppendAllChunkMeshBasesForGeom(
            const char* geomName,
            uint32_t classId,
            std::vector<std::string>& outMeshCandidates)
        {
            if (!geomName || !*geomName)
                return;
            if (_stricmp(geomName, "chunk1") == 0 || _stricmp(geomName, "chunk2") == 0)
                return;

            EnsureChunkVdfReverseIndex();

            std::string key(geomName);
            std::transform(
                key.begin(),
                key.end(),
                key.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

            const auto it = g_ChunkVdfGeomReverseIndex.find(key);
            if (it == g_ChunkVdfGeomReverseIndex.end() || it->second.empty())
                return;

            std::vector<std::string> bases;
            for (const ChunkVdfMeshRef& ref : it->second)
            {
                if (classId != 0 && ref.type != classId)
                    continue;
                if (ref.meshBase[0])
                    bases.emplace_back(ref.meshBase);
            }
            if (bases.empty())
            {
                for (const ChunkVdfMeshRef& ref : it->second)
                {
                    if (ref.meshBase[0])
                        bases.emplace_back(ref.meshBase);
                }
            }

            std::sort(
                bases.begin(),
                bases.end(),
                [](const std::string& left, const std::string& right)
                {
                    return _stricmp(left.c_str(), right.c_str()) < 0;
                });
            for (const std::string& base : bases)
                AppendUniqueChunkPayloadCandidate(outMeshCandidates, NormalizeChunkMeshBaseName(base.c_str()));
        }

        bool ResolveChunkCreateMeshContext(
            const ChunkCreateSourceTreeProbe& probe,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';

            if (probe.ownerResolvedMeshName[0])
            {
                strncpy_s(outMeshName, outMeshNameCapacity, probe.ownerResolvedMeshName, _TRUNCATE);
                return true;
            }

            const ChunkObjectLinkProbe* links[] = {
                &probe.source,
                &probe.parent,
                &probe.sibling,
                &probe.child,
            };
            for (const ChunkObjectLinkProbe* link : links)
            {
                if (!link || !link->cachedMeshName[0])
                    continue;

                if (!outMeshName[0])
                {
                    strncpy_s(outMeshName, outMeshNameCapacity, link->cachedMeshName, _TRUNCATE);
                    continue;
                }

                if (_stricmp(outMeshName, link->cachedMeshName) != 0)
                {
                    outMeshName[0] = '\0';
                    break;
                }
            }
            if (outMeshName[0])
                return true;

            for (const ChunkObjectLinkProbe* link : links)
            {
                if (!link || !link->geomName[0])
                    continue;

                if (TryInferChunkMeshNameFromGeom(
                        link->geomName,
                        link->classId,
                        outMeshName,
                        outMeshNameCapacity))
                {
                    return true;
                }
            }

            if (TryInferChunkMeshNameFromTree(
                    probe.source,
                    probe.parent,
                    probe.sibling,
                    probe.child,
                    outMeshName,
                    outMeshNameCapacity))
            {
                return true;
            }

            return false;
        }

        bool TryInferChunkMeshNameFromTree(
            const ChunkObjectLinkProbe& source,
            const ChunkObjectLinkProbe& parent,
            const ChunkObjectLinkProbe& sibling,
            const ChunkObjectLinkProbe& child,
            char* outMeshName,
            size_t outMeshNameCapacity)
        {
            if (!outMeshName || outMeshNameCapacity == 0)
                return false;

            outMeshName[0] = '\0';
            if (!source.objectBytes || source.classId == 0)
                return false;

            EnsureChunkVdfReverseIndex();

            std::string selectedMeshBase;
            for (const auto& pair : g_ChunkVdfAssetCache)
            {
                const std::string& meshBase = pair.first;
                const ChunkVdfAssetInfo& info = pair.second;
                if (!info.loaded)
                    continue;

                bool matchedMesh = false;
                for (const ChunkVdfRecord& record : info.records)
                {
                    if (ChunkVdfRecordMatchesTree(info, record, source, parent, sibling, child))
                    {
                        matchedMesh = true;
                        break;
                    }
                }

                if (!matchedMesh)
                    continue;

                if (selectedMeshBase.empty())
                {
                    selectedMeshBase = meshBase;
                    continue;
                }

                if (_stricmp(selectedMeshBase.c_str(), meshBase.c_str()) != 0)
                    return false;
            }

            if (selectedMeshBase.empty())
                return false;

            _snprintf_s(outMeshName, outMeshNameCapacity, _TRUNCATE, "%s.mesh", selectedMeshBase.c_str());
            return outMeshName[0] != '\0';
        }
    }

}
