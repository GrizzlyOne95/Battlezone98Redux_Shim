// odf_helpers.cpp
// BZR Open Shim - content root and ODF helpers: the addon/mods/
// packaged_mods/Workshop content root candidates, the ODF search path,
// ODF token normalisation and file resolution, and the float/bool ODF
// value parsers, split out of bzr_hooks.cpp.
#include "bzr_hooks.h"
#include "env_switch_table.h"
#include "bool_token.h"
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
#include "memory_access.h"
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
        void AppendUniquePath(std::vector<std::filesystem::path>& paths, const std::filesystem::path& candidate)
        {
            if (candidate.empty())
                return;

            if (std::find(paths.begin(), paths.end(), candidate) != paths.end())
                return;

            paths.push_back(candidate);
        }

        static std::filesystem::path TryGetWorkshopContentDirectory(const std::filesystem::path& gameDir)
        {
            if (gameDir.empty())
                return {};

            const auto normalized = gameDir.lexically_normal().string();
            std::string lower = normalized;
            std::transform(lower.begin(), lower.end(), lower.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

            constexpr const char* kSteamCommonMarker = "\\steamapps\\common\\";
            const size_t markerPos = lower.find(kSteamCommonMarker);
            if (markerPos == std::string::npos)
                return {};

            return std::filesystem::path(normalized.substr(0, markerPos)) /
                "steamapps" / "workshop" / "content" / "301650";
        }

        static void AppendImmediateSubdirectories(
            const std::filesystem::path& parent,
            std::vector<std::filesystem::path>& results)
        {
            if (parent.empty())
                return;

            std::error_code ec;
            if (!std::filesystem::exists(parent, ec) || ec)
                return;

            for (std::filesystem::directory_iterator it(parent, ec), end;
                 !ec && it != end;
                 it.increment(ec))
            {
                if (ec)
                    break;

                const auto& entry = *it;
                if (entry.is_directory(ec) && !ec)
                    AppendUniquePath(results, entry.path());
            }
        }

        std::vector<std::filesystem::path> GetCampaignContentRootCandidates(
            const std::filesystem::path& gameDir)
        {
            std::vector<std::filesystem::path> candidates;
            if (gameDir.empty())
                return candidates;

            AppendImmediateSubdirectories(gameDir / "addon", candidates);
            AppendImmediateSubdirectories(gameDir / "mods", candidates);
            AppendImmediateSubdirectories(gameDir / "packaged_mods", candidates);
            AppendImmediateSubdirectories(TryGetWorkshopContentDirectory(gameDir), candidates);
            return candidates;
        }

        std::vector<std::filesystem::path> GetProducerOdfDirectoryCandidates()
        {
            std::vector<std::filesystem::path> candidates;

            const auto moduleDir = GetMainModuleDirectory();
            if (moduleDir.empty())
                return candidates;

            for (const auto& root : GetCampaignContentRootCandidates(moduleDir))
            {
                AppendUniquePath(candidates, root / "ODF");
                AppendUniquePath(candidates, root / "_Release" / "ODF");
                AppendUniquePath(candidates, root / "_Source" / "ODF");
            }
            candidates.push_back(moduleDir / "Edit" / "stock");
            return candidates;
        }

        bool TryParseFloatValue(const char* value, float& out)
        {
            if (!value || !*value)
                return false;

            char* end = nullptr;
            const float parsed = std::strtof(value, &end);
            if (end == value)
                return false;

            while (end && *end && std::isspace(static_cast<unsigned char>(*end)))
                ++end;

            if (end && *end == 'f' && end[1] == '\0')
                ++end;

            if (end && *end != '\0')
                return false;

            out = parsed;
            return std::isfinite(out);
        }

        bool TryParseBoolValue(const char* value, bool& out)
        {
            return BZROpenShim::BoolToken::TryParse(value, out);
        }

        bool TryGetObjectOdfToken(void* objectPtr, char (&outToken)[kProducerBuildMenuTokenLen + 1])
        {
            outToken[0] = '\0';
            if (!objectPtr)
                return false;

            // Use the same GameObject -> class virtual lookup as the validated
            // engine-flame ODF path. The tempting raw object+0xF8/class+0x20
            // chain identifies a different class record for Craft instances
            // and produces plausible-looking garbage instead of the ODF name.
            char rawOdf[kGameObjectClassOdfNameMax + 1] = {};
            if (!TryGetCraftOdfName(objectPtr, rawOdf, sizeof(rawOdf)))
                return false;

            const ProducerBuildMenuEntry entry = NormalizeProducerBuildMenuToken(rawOdf);
            if (!entry.hasValue)
                return false;

            strncpy_s(outToken, entry.token, _TRUNCATE);
            return true;
        }

        bool TryNormalizeQuotedStringValue(const char* value,
                                                  char* out,
                                                  size_t outSize)
        {
            if (!value || !out || outSize == 0)
                return false;

            out[0] = '\0';

            const char* start = value;
            while (*start && std::isspace(static_cast<unsigned char>(*start)))
                ++start;

            const char* end = start + std::strlen(start);
            while (end > start && std::isspace(static_cast<unsigned char>(end[-1])))
                --end;

            if (end <= start)
                return false;

            if ((*start == '"' || *start == '\'') && end > start + 1 && end[-1] == *start)
            {
                ++start;
                --end;
            }

            size_t outIndex = 0;
            while (start < end && outIndex + 1 < outSize)
            {
                out[outIndex++] = static_cast<char>(
                    std::tolower(static_cast<unsigned char>(*start++)));
            }
            out[outIndex] = '\0';

            return outIndex > 0;
        }

        ProducerBuildMenuEntry NormalizeQuotedOdfToken(const char* value)
        {
            char normalized[64] = {};
            if (!TryNormalizeQuotedStringValue(value, normalized, sizeof(normalized)))
                return {};

            return NormalizeProducerBuildMenuToken(normalized);
        }

        bool TryResolveOdfFilePath(const char* odfToken, std::filesystem::path& outPath)
        {
            outPath.clear();

            const ProducerBuildMenuEntry odfKey = NormalizeQuotedOdfToken(odfToken);
            if (!odfKey.hasValue)
                return false;

            const auto directories = GetProducerOdfDirectoryCandidates();
            for (const auto& directory : directories)
            {
                std::error_code error;
                const auto mpPath = directory / (std::string(odfKey.token) + "_mp.odf");
                if (std::filesystem::exists(mpPath, error) && !error)
                {
                    outPath = mpPath;
                    return true;
                }

                error.clear();
                const auto normalPath = directory / (std::string(odfKey.token) + ".odf");
                if (std::filesystem::exists(normalPath, error) && !error)
                {
                    outPath = normalPath;
                    return true;
                }
            }

            return false;
        }
    }

}
