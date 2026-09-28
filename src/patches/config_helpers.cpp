// config_helpers.cpp
// BZR Open Shim - configuration and string helpers: the environment
// readers (flag, float, long), the openshim.ini string/bool readers, the
// executable directory lookups, and the ASCII trim/lower-case helpers,
// split out of bzr_hooks.cpp.
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
        bool TryGetEnvFloat(const char* name, float& outValue)
        {
            if (!name || !*name)
                return false;

            char value[32] = {};
            const DWORD len = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
            if (len == 0 || len >= sizeof(value))
                return false;

            char* end = nullptr;
            const float parsed = std::strtof(value, &end);
            if (end == value)
                return false;

            while (*end == ' ' || *end == '\t')
                ++end;
            if (*end != '\0')
                return false;

            outValue = parsed;
            return true;
        }

        bool TryGetEnvLong(const char* name, long& outValue)
        {
            if (!name || !*name)
                return false;

            char value[32] = {};
            const DWORD len = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
            if (len == 0 || len >= sizeof(value))
                return false;

            char* end = nullptr;
            const long parsed = std::strtol(value, &end, 10);
            if (end == value)
                return false;

            while (*end == ' ' || *end == '\t')
                ++end;
            if (*end != '\0')
                return false;

            outValue = parsed;
            return true;
        }

        std::filesystem::path GetConfigModuleDirectory()
        {
            char path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return {};

            return std::filesystem::path(path).parent_path();
        }

        char* TrimAsciiInPlace(char* text)
        {
            if (!text)
                return text;

            while (*text && std::isspace(static_cast<unsigned char>(*text)))
                ++text;

            size_t length = std::strlen(text);
            while (length > 0 && std::isspace(static_cast<unsigned char>(text[length - 1])))
                text[--length] = '\0';

            return text;
        }

        std::string ToLowerAscii(std::string value)
        {
            for (char& ch : value)
            {
                ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            }
            return value;
        }
    }

    using namespace Hooks;

    // ---------------------------------------------------------------------
    // Helpers
    // ---------------------------------------------------------------------

    bool EnvFlagEnabled(const char* name)
    {
        if (!name || !*name)
            return false;

        char value[16] = {};
        const DWORD len = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
        if (len == 0 || len >= sizeof(value))
            return false;

        return value[0] != '0' && value[0] != '\0';
    }

    std::filesystem::path GetUserConfigPath()
    {
        const auto dir = GetConfigModuleDirectory();
        if (dir.empty())
            return {};
        return dir / kUserConfigFileName;
    }

    // Tri-state string read: returns false when the key is absent (or the
    // file/section is missing), so callers can distinguish "no opinion"
    // (fall through to the next source) from an explicit value.
    bool TryGetUserConfigString(const char* section, const char* key, std::string& out)
    {
        const auto path = GetUserConfigPath();
        if (path.empty())
            return false;

        // A sentinel default reliably detects a missing key: a present key
        // (even blank) never yields the sentinel byte.
        constexpr char kUnsetSentinel[] = "\x01__openshim_unset__";
        char buf[128] = {};
        GetPrivateProfileStringA(section, key, kUnsetSentinel, buf,
            static_cast<DWORD>(sizeof(buf)), path.string().c_str());
        if (buf[0] == '\0' || std::strcmp(buf, kUnsetSentinel) == 0)
            return false;

        char* trimmed = TrimAsciiInPlace(buf);
        if (*trimmed == '\0')
            return false;
        out.assign(trimmed);
        return true;
    }

    // Tri-state boolean read over TryGetUserConfigString: returns false when
    // the key is absent OR present-but-unparseable (both mean "no opinion").
    // Accepts the words in bool_token.h.
    bool TryGetUserConfigBool(const char* section, const char* key, bool& out)
    {
        std::string value;
        return TryGetUserConfigString(section, key, value) && BZROpenShim::BoolToken::TryParse(value, out);
    }

    std::filesystem::path GetMainModuleDirectory()
    {
        char path[MAX_PATH] = {};
        const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
        if (length == 0 || length >= MAX_PATH)
            return {};

        return std::filesystem::path(path).parent_path();
    }

    std::string TrimAsciiCopy(const std::string& value)
    {
        size_t start = 0;
        while (start < value.size() &&
               std::isspace(static_cast<unsigned char>(value[start])))
        {
            ++start;
        }

        size_t end = value.size();
        while (end > start &&
               std::isspace(static_cast<unsigned char>(value[end - 1])))
        {
            --end;
        }

        return value.substr(start, end - start);
    }
}
