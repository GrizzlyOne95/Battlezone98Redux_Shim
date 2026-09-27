// producer_build_menu.cpp
// BZR Open Shim - producer build menu (PRODMENU): per-producer build menu
// overrides from producer_build_menu.ini and ODF tokens, applied through
// the producer mode call hook, split out of bzr_hooks.cpp.
#include "bzr_hooks.h"
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
#include "render_queue_trace.h"
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
        constexpr char kProducerBuildMenuIniName[] = "openshim_producer_build_menus.ini";

        constexpr char kProducerBuildMenuSection[] = "ProducerBuildMenus";

        constexpr char kProducerBuildMenuDefaultRoot[] = "build";

        constexpr uint32_t kRecyclerDistributedVft = 0x00417D74;

        constexpr uint32_t kRecyclerAttachableVft = 0x00417DCC;

        constexpr uint32_t kRecyclerFriendVft = 0x00417F68;

        constexpr uint32_t kRecyclerEnemyVft = 0x00417F9C;

        constexpr uint32_t kFactoryDistributedVft = 0x0040B71C;

        constexpr uint32_t kFactoryAttachableVft = 0x0040B774;

        constexpr uint32_t kArmoryDistributedVft = 0x004089C0;

        constexpr uint32_t kArmoryAttachableVft = 0x00408A18;

        constexpr uint32_t kConstructionRigDistributedVft = 0x0040A158;

        constexpr uint32_t kConstructionRigAttachableVft = 0x0040A1B0;

        enum class ProducerBuildMenuKind
        {
            Unknown,
            Recycler,
            Factory,
            Armory,
            ConstructionRig,
        };

        static bool IsIniBoolTrue(const char* value, bool fallback)
        {
            bool parsed = fallback;
            return BZROpenShim::BoolToken::TryParse(value, parsed) ? parsed : fallback;
        }

        static int64_t PackProducerBuildMenuToken(const char* token)
        {
            if (!token)
                return 0;

            uint8_t bytes[kProducerBuildMenuTokenLen] = {};
            for (size_t i = 0; i < kProducerBuildMenuTokenLen && token[i]; ++i)
                bytes[i] = static_cast<uint8_t>(token[i]);

            int64_t packed = 0;
            memcpy(&packed, bytes, sizeof(bytes));
            return packed;
        }

        ProducerBuildMenuEntry NormalizeProducerBuildMenuToken(const char* value)
        {
            ProducerBuildMenuEntry entry = {};
            if (!value)
                return entry;

            const char* start = value;
            while (*start && std::isspace(static_cast<unsigned char>(*start)))
                ++start;

            const char* end = start + strlen(start);
            while (end > start && std::isspace(static_cast<unsigned char>(end[-1])))
                --end;

            size_t length = static_cast<size_t>(end - start);
            if (length == 0)
                return entry;

            char normalized[64] = {};
            size_t out = 0;
            for (size_t i = 0; i < length && out + 1 < sizeof(normalized); ++i)
            {
                normalized[out++] = static_cast<char>(
                    std::tolower(static_cast<unsigned char>(start[i])));
            }
            normalized[out] = '\0';

            if (out > 7 && strcmp(normalized + out - 7, "_mp.odf") == 0)
            {
                out -= 7;
                normalized[out] = '\0';
            }
            else if (out > 4 && strcmp(normalized + out - 4, ".odf") == 0)
            {
                out -= 4;
                normalized[out] = '\0';
            }

            if (out == 0)
                return entry;

            if (out > kProducerBuildMenuTokenLen)
                out = kProducerBuildMenuTokenLen;

            memcpy(entry.token, normalized, out);
            entry.token[out] = '\0';
            entry.hasValue = entry.token[0] != '\0';
            entry.packedToken = entry.hasValue ? PackProducerBuildMenuToken(entry.token) : 0;
            return entry;
        }

        static ProducerBuildMenuKind ClassifyProducerBuildMenuKind(void* producerPtr)
        {
            if (!producerPtr)
                return ProducerBuildMenuKind::Unknown;

            const uint32_t vft = *reinterpret_cast<const uint32_t*>(producerPtr);
            switch (vft)
            {
            case kRecyclerDistributedVft:
            case kRecyclerAttachableVft:
            case kRecyclerFriendVft:
            case kRecyclerEnemyVft:
                return ProducerBuildMenuKind::Recycler;
            case kFactoryDistributedVft:
            case kFactoryAttachableVft:
                return ProducerBuildMenuKind::Factory;
            case kArmoryDistributedVft:
            case kArmoryAttachableVft:
                return ProducerBuildMenuKind::Armory;
            case kConstructionRigDistributedVft:
            case kConstructionRigAttachableVft:
                return ProducerBuildMenuKind::ConstructionRig;
            default:
                if (vft != g_LastUnknownProducerVft)
                {
                    g_LastUnknownProducerVft = vft;
                    Log(L"[PRODMENU] Unknown producer vft=0x%08X\n", vft);
                }
                return ProducerBuildMenuKind::Unknown;
            }
        }

        static const char* ProducerBuildMenuKindName(ProducerBuildMenuKind kind)
        {
            switch (kind)
            {
            case ProducerBuildMenuKind::Recycler: return "Recycler";
            case ProducerBuildMenuKind::Factory: return "Factory";
            case ProducerBuildMenuKind::Armory: return "Armory";
            case ProducerBuildMenuKind::ConstructionRig: return "ConstructionRig";
            default: return "Producer";
            }
        }

        static ProducerBuildMenuEntry ReadProducerBuildMenuEntry(const char* key)
        {
            ProducerBuildMenuEntry entry = {};
            const auto moduleDir = GetMainModuleDirectory();
            if (moduleDir.empty())
                return entry;

            const auto configPath = moduleDir / kProducerBuildMenuIniName;
            char buffer[64] = {};
            GetPrivateProfileStringA(
                kProducerBuildMenuSection,
                key,
                "",
                buffer,
                static_cast<DWORD>(sizeof(buffer)),
                configPath.string().c_str());
            return NormalizeProducerBuildMenuToken(buffer);
        }

        static bool IsProducerBuildMenuReservedKey(const char* key)
        {
            if (!key || !*key)
                return true;

            return _stricmp(key, "Enabled") == 0 ||
                _stricmp(key, "Recycler") == 0 ||
                _stricmp(key, "Factory") == 0 ||
                _stricmp(key, "Armory") == 0 ||
                _stricmp(key, "ConstructionRig") == 0 ||
                _stricmp(key, "Constructor") == 0 ||
                _stricmp(key, "Default") == 0 ||
                _stricmp(key, "Fallback") == 0;
        }

        static void LoadProducerBuildMenuOdfOverrides(const std::filesystem::path& configPath)
        {
            g_ProducerBuildMenuConfig.odfOverrides.clear();

            FILE* file = nullptr;
            if (fopen_s(&file, configPath.string().c_str(), "r") != 0 || !file)
                return;

            char line[256] = {};
            bool inTargetSection = false;
            while (std::fgets(line, static_cast<int>(sizeof(line)), file))
            {
                char* trimmed = TrimAsciiInPlace(line);
                if (*trimmed == '\0' || *trimmed == ';' || *trimmed == '#')
                    continue;

                if (*trimmed == '[')
                {
                    char* closing = std::strchr(trimmed, ']');
                    if (!closing)
                        continue;

                    *closing = '\0';
                    inTargetSection = (_stricmp(trimmed + 1, kProducerBuildMenuSection) == 0);
                    continue;
                }

                if (!inTargetSection)
                    continue;

                char* equals = std::strchr(trimmed, '=');
                if (!equals)
                    continue;

                *equals = '\0';
                char* key = TrimAsciiInPlace(trimmed);
                char* value = TrimAsciiInPlace(equals + 1);
                if (!key || !*key || !value || !*value)
                    continue;
                if (IsProducerBuildMenuReservedKey(key))
                    continue;

                const ProducerBuildMenuEntry keyEntry = NormalizeProducerBuildMenuToken(key);
                const ProducerBuildMenuEntry valueEntry = NormalizeProducerBuildMenuToken(value);
                if (!keyEntry.hasValue || !valueEntry.hasValue)
                    continue;

                g_ProducerBuildMenuConfig.odfOverrides[keyEntry.token] = valueEntry;
            }

            std::fclose(file);
        }

        static ProducerBuildMenuEntry TryGetProducerBuildMenuEntryForOdf(const char* producerOdf)
        {
            ProducerBuildMenuEntry entry = {};
            const ProducerBuildMenuEntry key = NormalizeProducerBuildMenuToken(producerOdf);
            if (!key.hasValue)
                return entry;

            const auto it = g_ProducerBuildMenuConfig.odfOverrides.find(key.token);
            if (it != g_ProducerBuildMenuConfig.odfOverrides.end())
                return it->second;

            return entry;
        }

        static ProducerBuildMenuEntry TryReadProducerBuildMenuEntryFromOdfFile(const char* producerOdf)
        {
            ProducerBuildMenuEntry result = {};
            const ProducerBuildMenuEntry producerKey = NormalizeProducerBuildMenuToken(producerOdf);
            if (!producerKey.hasValue)
                return result;

            const auto cached = g_ProducerBuildMenuConfig.odfFileEntries.find(producerKey.token);
            if (cached != g_ProducerBuildMenuConfig.odfFileEntries.end())
                return cached->second;

            const auto directories = GetProducerOdfDirectoryCandidates();
            std::filesystem::path resolvedPath;
            for (const auto& directory : directories)
            {
                std::error_code error;
                const auto mpPath = directory / (std::string(producerKey.token) + "_mp.odf");
                if (std::filesystem::exists(mpPath, error) && !error)
                {
                    resolvedPath = mpPath;
                    break;
                }

                error.clear();
                const auto normalPath = directory / (std::string(producerKey.token) + ".odf");
                if (std::filesystem::exists(normalPath, error) && !error)
                {
                    resolvedPath = normalPath;
                    break;
                }
            }

            if (!resolvedPath.empty())
            {
                FILE* file = nullptr;
                if (fopen_s(&file, resolvedPath.string().c_str(), "r") == 0 && file)
                {
                    char line[256] = {};
                    bool inProducerSection = false;
                    while (std::fgets(line, static_cast<int>(sizeof(line)), file))
                    {
                        char* trimmed = TrimAsciiInPlace(line);
                        if (*trimmed == '\0' || *trimmed == ';' || *trimmed == '#')
                            continue;

                        if (*trimmed == '[')
                        {
                            char* closing = std::strchr(trimmed, ']');
                            if (!closing)
                                continue;

                            *closing = '\0';
                            inProducerSection = (_stricmp(trimmed + 1, "ProducerClass") == 0);
                            continue;
                        }

                        if (!inProducerSection)
                            continue;

                        char* equals = std::strchr(trimmed, '=');
                        if (!equals)
                            continue;

                        *equals = '\0';
                        char* key = TrimAsciiInPlace(trimmed);
                        char* value = TrimAsciiInPlace(equals + 1);
                        if (!key || !*key || !value || !*value)
                            continue;

                        if (_stricmp(key, "buildMenuRoot") == 0 ||
                            _stricmp(key, "buildMenu") == 0)
                        {
                            result = NormalizeProducerBuildMenuToken(value);
                            break;
                        }
                    }

                    std::fclose(file);

                    if (result.hasValue)
                    {
                        Log(L"[PRODMENU] ODF root producer=%hs root=%hs path=%hs\n",
                            producerKey.token,
                            result.token,
                            resolvedPath.string().c_str());
                    }
                }
            }

            g_ProducerBuildMenuConfig.odfFileEntries[producerKey.token] = result;
            return result;
        }

        static bool TryGetProducerOdfToken(void* producerPtr, char (&outToken)[kProducerBuildMenuTokenLen + 1])
        {
            return TryGetObjectOdfToken(producerPtr, outToken);
        }

        static void LoadProducerBuildMenuConfig()
        {
            if (g_ProducerBuildMenuConfig.initialized)
                return;

            g_ProducerBuildMenuConfig.initialized = true;
            g_ProducerBuildMenuConfig.fallbackRoot =
                NormalizeProducerBuildMenuToken(kProducerBuildMenuDefaultRoot);

            if (g_IsSteamExe)
            {
                Log(L"[PRODMENU] Disabled on Steam until the producer hook site is revalidated there\n");
                return;
            }

            const auto moduleDir = GetMainModuleDirectory();
            if (moduleDir.empty())
            {
                Log(L"[PRODMENU] Game directory unavailable; feature disabled\n");
                return;
            }

            const auto configPath = moduleDir / kProducerBuildMenuIniName;
            const auto configPathString = configPath.string();
            DWORD attrs = GetFileAttributesA(configPathString.c_str());
            if (attrs == INVALID_FILE_ATTRIBUTES || (attrs & FILE_ATTRIBUTE_DIRECTORY) != 0)
            {
                Log(L"[PRODMENU] Config not found at %hs; feature disabled\n", configPathString.c_str());
                return;
            }

            char enabledBuffer[32] = {};
            GetPrivateProfileStringA(
                kProducerBuildMenuSection,
                "Enabled",
                "1",
                enabledBuffer,
                static_cast<DWORD>(sizeof(enabledBuffer)),
                configPathString.c_str());

            g_ProducerBuildMenuConfig.recycler = ReadProducerBuildMenuEntry("Recycler");
            g_ProducerBuildMenuConfig.factory = ReadProducerBuildMenuEntry("Factory");
            g_ProducerBuildMenuConfig.armory = ReadProducerBuildMenuEntry("Armory");
            g_ProducerBuildMenuConfig.constructionRig = ReadProducerBuildMenuEntry("ConstructionRig");
            ProducerBuildMenuEntry fallbackEntry = ReadProducerBuildMenuEntry("Fallback");
            if (!fallbackEntry.hasValue)
                fallbackEntry = ReadProducerBuildMenuEntry("Default");
            if (fallbackEntry.hasValue)
                g_ProducerBuildMenuConfig.fallbackRoot = fallbackEntry;
            if (!g_ProducerBuildMenuConfig.constructionRig.hasValue)
            {
                g_ProducerBuildMenuConfig.constructionRig = ReadProducerBuildMenuEntry("Constructor");
            }
            LoadProducerBuildMenuOdfOverrides(configPath);

            const bool hasAnyEntry =
                !g_ProducerBuildMenuConfig.odfOverrides.empty() ||
                g_ProducerBuildMenuConfig.recycler.hasValue ||
                g_ProducerBuildMenuConfig.factory.hasValue ||
                g_ProducerBuildMenuConfig.armory.hasValue ||
                g_ProducerBuildMenuConfig.constructionRig.hasValue;
            g_ProducerBuildMenuConfig.enabled = IsIniBoolTrue(enabledBuffer, true) && hasAnyEntry;

            Log(L"[PRODMENU] Config %hs loaded enabled=%hs fallback=%hs recycler=%hs factory=%hs armory=%hs constrig=%hs odfOverrides=%u\n",
                configPathString.c_str(),
                g_ProducerBuildMenuConfig.enabled ? "true" : "false",
                g_ProducerBuildMenuConfig.fallbackRoot.hasValue ? g_ProducerBuildMenuConfig.fallbackRoot.token : "-",
                g_ProducerBuildMenuConfig.recycler.hasValue ? g_ProducerBuildMenuConfig.recycler.token : "-",
                g_ProducerBuildMenuConfig.factory.hasValue ? g_ProducerBuildMenuConfig.factory.token : "-",
                g_ProducerBuildMenuConfig.armory.hasValue ? g_ProducerBuildMenuConfig.armory.token : "-",
                g_ProducerBuildMenuConfig.constructionRig.hasValue ? g_ProducerBuildMenuConfig.constructionRig.token : "-",
                static_cast<unsigned>(g_ProducerBuildMenuConfig.odfOverrides.size()));
        }

        static ProducerBuildMenuEntry SelectProducerBuildMenuEntry(void* producerPtr, ProducerBuildMenuKind kind)
        {
            char producerOdf[kProducerBuildMenuTokenLen + 1] = {};
            if (TryGetProducerOdfToken(producerPtr, producerOdf))
            {
                ProducerBuildMenuEntry odfFileEntry = TryReadProducerBuildMenuEntryFromOdfFile(producerOdf);
                if (odfFileEntry.hasValue)
                    return odfFileEntry;

                ProducerBuildMenuEntry odfEntry = TryGetProducerBuildMenuEntryForOdf(producerOdf);
                if (odfEntry.hasValue)
                    return odfEntry;
            }

            switch (kind)
            {
            case ProducerBuildMenuKind::Recycler:
                if (g_ProducerBuildMenuConfig.recycler.hasValue)
                    return g_ProducerBuildMenuConfig.recycler;
                break;
            case ProducerBuildMenuKind::Factory:
                if (g_ProducerBuildMenuConfig.factory.hasValue)
                    return g_ProducerBuildMenuConfig.factory;
                break;
            case ProducerBuildMenuKind::Armory:
                if (g_ProducerBuildMenuConfig.armory.hasValue)
                    return g_ProducerBuildMenuConfig.armory;
                break;
            case ProducerBuildMenuKind::ConstructionRig:
                if (g_ProducerBuildMenuConfig.constructionRig.hasValue)
                    return g_ProducerBuildMenuConfig.constructionRig;
                break;
            default:
                break;
            }

            return g_ProducerBuildMenuConfig.fallbackRoot;
        }

        static void MaybeApplyProducerBuildMenu(void* producerPtr)
        {
            if (!g_BzrFn_InitBuildItem || !g_BzrFn_CleanupBuildItem || !g_BzrBuildMenuRoot)
                return;

            LoadProducerBuildMenuConfig();
            if (!g_ProducerBuildMenuConfig.enabled)
                return;

            const ProducerBuildMenuKind kind = ClassifyProducerBuildMenuKind(producerPtr);
            const ProducerBuildMenuEntry entry = SelectProducerBuildMenuEntry(producerPtr, kind);
            if (!entry.hasValue)
                return;

            if (g_HasAppliedProducerBuildMenu && g_LastAppliedProducerBuildMenu == entry.packedToken)
                return;

            __try
            {
                char producerOdf[kProducerBuildMenuTokenLen + 1] = {};
                TryGetProducerOdfToken(producerPtr, producerOdf);
                g_BzrFn_CleanupBuildItem(*g_BzrBuildMenuRoot);
                g_BzrFn_InitBuildItem(*g_BzrBuildMenuRoot, entry.packedToken);
                g_HasAppliedProducerBuildMenu = true;
                g_LastAppliedProducerBuildMenu = entry.packedToken;
                Log(L"[PRODMENU] Applied %hs root=%hs producer=0x%08X odf=%hs\n",
                    ProducerBuildMenuKindName(kind),
                    entry.token,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(producerPtr)),
                    producerOdf[0] ? producerOdf : "-");
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                char producerOdf[kProducerBuildMenuTokenLen + 1] = {};
                TryGetProducerOdfToken(producerPtr, producerOdf);
                Log(L"[PRODMENU] Failed applying root=%hs producer=0x%08X\n",
                    entry.token,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(producerPtr)));
            }
        }
    }

    using namespace Hooks;

    void SetProducerBuildMenuOriginal(void* target)
    {
        g_BzrFn_ProducerModeCallOriginal = reinterpret_cast<FnProducerModeCall>(target);
        Log(L"[PRODMENU] Original producer helper target=0x%08X\n",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(target)));
    }

    void* __cdecl ProducerBuildMenuCallHook(void* producerPtr, int slot, int flags)
    {
        MaybeApplyProducerBuildMenu(producerPtr);

        if (!g_BzrFn_ProducerModeCallOriginal)
            return nullptr;

        return g_BzrFn_ProducerModeCallOriginal(producerPtr, slot, flags);
    }
}
