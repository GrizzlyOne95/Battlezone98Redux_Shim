// moderation.cpp
// BZR Open Shim - multiplayer moderation: the bans.cfg list (and legacy
// banlist), the persistent mutes.cfg list, kicking banned joiners and
// reapplying mutes, and the /help /nickname /ban /mute /unmute command
// handler with the joiner event, split out of bzr_hooks.cpp.
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
        constexpr int kBanScanMaxSessionId = 64;

        constexpr char kBansConfigName[] = "bans.cfg";

        constexpr char kLegacyBanListName[] = "banlist.txt";

        static bool g_BansConfigLoaded = false;

        static std::string BzrStringToStdString(const BzrString* value)
        {
            if (!value || value->size == 0)
                return {};

            return std::string(BzrStringData(value), value->size);
        }

        static std::string NormalizeBanId(const char* value)
        {
            return StableIdList::NormalizeId(value);
        }

        // bans.cfg and mutes.cfg are read and written whole. Text mode, as
        // the fgets/fprintf loops these replace used.
        static bool ReadStableIdListFile(const std::string& path, std::string& out)
        {
            out.clear();
            FILE* file = nullptr;
            if (fopen_s(&file, path.c_str(), "r") != 0 || !file)
                return false;
            char buffer[4096];
            size_t read = 0;
            while ((read = std::fread(buffer, 1, sizeof(buffer), file)) > 0)
                out.append(buffer, read);
            std::fclose(file);
            return true;
        }

        static bool WriteStableIdListFile(const std::string& path, const std::string& text)
        {
            FILE* file = nullptr;
            if (fopen_s(&file, path.c_str(), "w") != 0 || !file)
                return false;
            const bool wrote = std::fwrite(text.data(), 1, text.size(), file) == text.size();
            return std::fclose(file) == 0 && wrote;
        }

        std::filesystem::path GetBansConfigPath()
        {
            return GetConfigModuleDirectory() / kBansConfigName;
        }

        static std::filesystem::path GetLegacyBanListPath()
        {
            return GetConfigModuleDirectory() / kLegacyBanListName;
        }

        static void AppendLegacyBanList(const char* id, const BzrString* name)
        {
            if (!id || !*id)
                return;

            const auto path = GetLegacyBanListPath();
            const std::string pathString = path.string();

            FILE* file = nullptr;
            fopen_s(&file, pathString.c_str(), "a");
            if (!file)
            {
                Log(L"[BAN] Failed to append legacy banlist path=%hs\n", pathString.c_str());
                return;
            }

            if (name && name->size)
                std::fprintf(file, "%s %.*s\n", id, static_cast<int>(name->size), BzrStringData(name));
            else
                std::fprintf(file, "%s\n", id);
            std::fclose(file);
        }

        void EnsureBansConfigLoaded()
        {
            if (g_BansConfigLoaded)
                return;

            g_BansConfigLoaded = true;
            g_BanRecords.clear();

            const auto configPath = GetBansConfigPath();
            const std::string configPathString = configPath.string();
            std::string text;
            if (!ReadStableIdListFile(configPathString, text))
            {
                Log(L"[BAN] No bans config found at path=%hs\n", configPathString.c_str());
                return;
            }

            g_BanRecords = StableIdList::Parse(text);
            Log(L"[BAN] Loaded bans config path=%hs entries=%u\n",
                configPathString.c_str(),
                static_cast<unsigned>(g_BanRecords.size()));
        }

        static bool SaveBansConfig()
        {
            const auto configPath = GetBansConfigPath();
            const std::string configPathString = configPath.string();
            if (!WriteStableIdListFile(configPathString,
                    StableIdList::Format(g_BanRecords, "OpenShim ban list", "<stable_id> [display name]")))
            {
                Log(L"[BAN] Failed to write bans config path=%hs\n", configPathString.c_str());
                return false;
            }

            Log(L"[BAN] Wrote bans config path=%hs entries=%u\n",
                configPathString.c_str(),
                static_cast<unsigned>(g_BanRecords.size()));
            return true;
        }

        static bool IsBanIdConfigured(const char* stableId)
        {
            if (!stableId || !*stableId)
                return false;

            EnsureBansConfigLoaded();
            const std::string normalized = NormalizeBanId(stableId);
            return std::any_of(
                g_BanRecords.begin(),
                g_BanRecords.end(),
                [&normalized](const BanRecord& entry) { return entry.id == normalized; });
        }

        bool AddBanConfigEntry(const char* stableId, const BzrString* name, const char* source)
        {
            const std::string normalized = NormalizeBanId(stableId);
            if (normalized.empty())
            {
                Log(L"[BAN] %hs rejected invalid stable id '%hs'\n",
                    source ? source : "ban",
                    stableId ? stableId : "");
                return false;
            }

            EnsureBansConfigLoaded();

            const std::string displayName = BzrStringToStdString(name);
            auto existing = std::find_if(
                g_BanRecords.begin(),
                g_BanRecords.end(),
                [&normalized](const BanRecord& entry) { return entry.id == normalized; });
            if (existing != g_BanRecords.end())
            {
                if (existing->name.empty() && !displayName.empty())
                {
                    existing->name = displayName;
                    SaveBansConfig();
                    Log(L"[BAN] %hs refreshed existing entry stable=%hs name=%hs\n",
                        source ? source : "ban",
                        normalized.c_str(),
                        displayName.c_str());
                }
                else
                {
                    Log(L"[BAN] %hs entry already present stable=%hs name=%hs\n",
                        source ? source : "ban",
                        normalized.c_str(),
                        existing->name.c_str());
                }

                return true;
            }

            BanRecord entry = {};
            entry.id = normalized;
            entry.name = displayName;
            g_BanRecords.push_back(std::move(entry));
            SaveBansConfig();
            AppendLegacyBanList(normalized.c_str(), name);
            Log(L"[BAN] %hs added entry stable=%hs name=%hs\n",
                source ? source : "ban",
                normalized.c_str(),
                displayName.c_str());
            return true;
        }

        // ------------------------------------------------------------------
        // Persistent per-player mute list (mutes.cfg). Mirrors the bans.cfg
        // format: <stable_id> [display name]. Stable ids use the same
        // G<uid>/S<uid> platform-identity model as bans, so a mute survives
        // restarts, reconnects, lobby changes and nickname changes. Enforced
        // purely by reapplying Redux's own PlayerList mute (via its native
        // /mute command path); OpenShim adds no chat filtering of its own.
        //
        // Persistence is the part that is optional, not the mute itself. With
        // it off, /mute and the lobby button still mute -- Redux's own
        // per-process state does that -- the mute simply stops outliving the
        // process, which is what the stock game does.
        //   openshim.ini  [Network] PersistentPlayerMute = 1
        //   environment   OPENSHIM_DISABLE_PERSISTENT_PLAYER_MUTE=1
        // ------------------------------------------------------------------
        constexpr char kMutesConfigName[] = "mutes.cfg";

        // Deliberately unlatched: every caller is a lobby event or a typed
        // command, never a hot path, and nothing here is a patch site, so a
        // player who flips the setting gets the new answer at the next mute
        // instead of at the next restart.
        static bool IsPersistentPlayerMuteEnabled()
        {
            if (EnvFlagEnabled("OPENSHIM_DISABLE_PERSISTENT_PLAYER_MUTE") ||
                EnvFlagEnabled("BZR_DISABLE_PERSISTENT_PLAYER_MUTE"))
            {
                return false;
            }
            if (EnvFlagEnabled("OPENSHIM_ENABLE_PERSISTENT_PLAYER_MUTE") ||
                EnvFlagEnabled("BZR_ENABLE_PERSISTENT_PLAYER_MUTE"))
            {
                return true;
            }
            bool enabled = true;
            if (TryGetUserConfigBool("Network", "PersistentPlayerMute", enabled))
                return enabled;
            return true;
        }

        using MuteRecord = StableIdList::Record;

        static bool g_MutesConfigLoaded = false;
        static std::vector<MuteRecord> g_MuteRecords;

        static std::filesystem::path GetMutesConfigPath()
        {
            return GetConfigModuleDirectory() / kMutesConfigName;
        }

        static void EnsureMutesConfigLoaded()
        {
            if (g_MutesConfigLoaded)
                return;

            g_MutesConfigLoaded = true;
            g_MuteRecords.clear();

            const auto configPath = GetMutesConfigPath();
            const std::string configPathString = configPath.string();
            std::string text;
            if (!ReadStableIdListFile(configPathString, text))
            {
                Log(L"[MUTE] No mutes config found at path=%hs\n", configPathString.c_str());
                return;
            }

            g_MuteRecords = StableIdList::Parse(text);
            Log(L"[MUTE] Loaded mutes config path=%hs entries=%u\n",
                configPathString.c_str(),
                static_cast<unsigned>(g_MuteRecords.size()));
        }

        static bool SaveMutesConfig()
        {
            const auto configPath = GetMutesConfigPath();
            const std::string configPathString = configPath.string();
            if (!WriteStableIdListFile(configPathString,
                    StableIdList::Format(g_MuteRecords, "OpenShim persistent mute list", "<stable_id> [last display name]")))
            {
                Log(L"[MUTE] Failed to write mutes config path=%hs\n", configPathString.c_str());
                return false;
            }

            Log(L"[MUTE] Wrote mutes config path=%hs entries=%u\n",
                configPathString.c_str(),
                static_cast<unsigned>(g_MuteRecords.size()));
            return true;
        }

        static bool IsMuteIdPersisted(const char* stableId)
        {
            if (!stableId || !*stableId)
                return false;

            EnsureMutesConfigLoaded();
            const std::string normalized = NormalizeBanId(stableId);
            return std::any_of(
                g_MuteRecords.begin(),
                g_MuteRecords.end(),
                [&normalized](const MuteRecord& entry) { return entry.id == normalized; });
        }

        // Adds (or refreshes the display name of) a persistent mute entry.
        // Returns true when the list changed and was saved.
        static bool AddMuteConfigEntry(const char* stableId, const BzrString* name, const char* source)
        {
            // Session-only mode never grows the list. Removals are still let
            // through below, so /unmute always means unmute -- including any
            // entry a previous persistent session left behind.
            if (!IsPersistentPlayerMuteEnabled())
            {
                Log(L"[MUTE] %hs not persisted: PersistentPlayerMute is off (session-only)\n",
                    source ? source : "mute");
                return false;
            }

            const std::string normalized = NormalizeBanId(stableId);
            if (normalized.empty())
            {
                Log(L"[MUTE] %hs rejected invalid stable id '%hs'\n",
                    source ? source : "mute",
                    stableId ? stableId : "");
                return false;
            }

            EnsureMutesConfigLoaded();

            const std::string displayName = BzrStringToStdString(name);
            auto existing = std::find_if(
                g_MuteRecords.begin(),
                g_MuteRecords.end(),
                [&normalized](const MuteRecord& entry) { return entry.id == normalized; });
            if (existing != g_MuteRecords.end())
            {
                if (!displayName.empty() && existing->name != displayName)
                {
                    existing->name = displayName;
                    SaveMutesConfig();
                    Log(L"[MUTE] %hs refreshed entry stable=%hs name=%hs\n",
                        source ? source : "mute",
                        normalized.c_str(),
                        displayName.c_str());
                }
                else
                {
                    Log(L"[MUTE] %hs entry already present stable=%hs name=%hs\n",
                        source ? source : "mute",
                        normalized.c_str(),
                        existing->name.c_str());
                }
                return true;
            }

            MuteRecord entry = {};
            entry.id = normalized;
            entry.name = displayName;
            g_MuteRecords.push_back(std::move(entry));
            SaveMutesConfig();
            Log(L"[MUTE] %hs added entry stable=%hs name=%hs\n",
                source ? source : "mute",
                normalized.c_str(),
                displayName.c_str());
            return true;
        }

        // Removes a persistent mute entry; returns true when an entry was
        // removed and the list was saved.
        static bool RemoveMuteConfigEntry(const char* stableId, const char* source)
        {
            const std::string normalized = NormalizeBanId(stableId);
            if (normalized.empty())
                return false;

            EnsureMutesConfigLoaded();
            auto existing = std::find_if(
                g_MuteRecords.begin(),
                g_MuteRecords.end(),
                [&normalized](const MuteRecord& entry) { return entry.id == normalized; });
            if (existing == g_MuteRecords.end())
                return false;

            g_MuteRecords.erase(existing);
            SaveMutesConfig();
            Log(L"[MUTE] %hs removed entry stable=%hs\n",
                source ? source : "unmute",
                normalized.c_str());
            return true;
        }
    }

    using namespace Hooks;

    namespace Hooks
    {
        struct BanLookupIdentity
        {
            int type = 0;
            uint64_t uid = 0;
            const BzrString* name = nullptr;
            char stableId[32] = {};
        };

        static bool TryBuildBanLookupIdentity(int type, uint64_t uid, const BzrString* name, BanLookupIdentity& out)
        {
            if (type != 1 && type != 2)
                return false;

            const char prefix = (type == 1) ? 'S' : 'G';
            std::snprintf(
                out.stableId,
                sizeof(out.stableId),
                "%c%llu",
                prefix,
                static_cast<unsigned long long>(uid));
            out.type = type;
            out.uid = uid;
            out.name = name;
            return true;
        }

        static bool TryGetBanLookupIdentityForSessionId(uint16_t sessionId, BanLookupIdentity& out)
        {
            if (!g_BzrFn_BanLookup)
                return false;

            uint8_t* entry = reinterpret_cast<uint8_t*>(g_BzrFn_BanLookup(sessionId));
            if (!entry)
                return false;

            const int type = *reinterpret_cast<int*>(entry + 0x30);
            const uint64_t uid = *reinterpret_cast<uint64_t*>(entry + 0x38);
            const auto* name = reinterpret_cast<const BzrString*>(entry + 0x74);
            return TryBuildBanLookupIdentity(type, uid, name, out);
        }

        void KickBannedPlayers(const char* source, uint32_t lobby, uint32_t member, int changes)
        {
            EnsureBansConfigLoaded();

            if (!g_BzrFn_IsHost || g_BzrFn_IsHost() == 0)
            {
                Log(L"[BAN] %hs sweep skipped lobby=0x%08X member=0x%08X changes=0x%08X (not host)\n",
                    source ? source : "ban",
                    lobby,
                    member,
                    static_cast<uint32_t>(changes));
                return;
            }

            if (g_BanRecords.empty())
            {
                Log(L"[BAN] %hs sweep skipped lobby=0x%08X member=0x%08X changes=0x%08X (no bans loaded)\n",
                    source ? source : "ban",
                    lobby,
                    member,
                    static_cast<uint32_t>(changes));
                return;
            }

            if (!g_BzrFn_CommandHandler || !g_BzrFn_BanLookup)
            {
                Log(L"[BAN] %hs sweep skipped lobby=0x%08X member=0x%08X changes=0x%08X (helpers unavailable)\n",
                    source ? source : "ban",
                    lobby,
                    member,
                    static_cast<uint32_t>(changes));
                return;
            }

            int kicks = 0;
            for (uint16_t sessionId = 0; sessionId < kBanScanMaxSessionId; ++sessionId)
            {
                BanLookupIdentity identity = {};
                if (!TryGetBanLookupIdentityForSessionId(sessionId, identity))
                    continue;

                if (!IsBanIdConfigured(identity.stableId))
                    continue;

                const char* nameText =
                    (identity.name && identity.name->size) ? BzrStringData(identity.name) : "";
                Log(L"[BAN] %hs matched session=%u stable=%hs type=%d uid=%llu name=%hs lobby=0x%08X member=0x%08X changes=0x%08X\n",
                    source ? source : "ban",
                    sessionId,
                    identity.stableId,
                    identity.type,
                    static_cast<unsigned long long>(identity.uid),
                    nameText,
                    lobby,
                    member,
                    static_cast<uint32_t>(changes));
                g_BzrFn_CommandHandler(sessionId, "/kick");
                ++kicks;
            }

            Log(L"[BAN] %hs sweep complete lobby=0x%08X member=0x%08X changes=0x%08X kicks=%d entries=%u\n",
                source ? source : "ban",
                lobby,
                member,
                static_cast<uint32_t>(changes),
                kicks,
                static_cast<unsigned>(g_BanRecords.size()));
        }

        // Reapplies persisted mutes to the current session. Redux's mute state
        // is per-process runtime state, so every membership change is a chance
        // a persisted identity is (still) present with a fresh mute flag. The
        // native /mute path does the actual work; the display name passed in
        // the log is refreshed so mutes.cfg tracks the player's current name.
        static void ReapplyPersistentMutes(const char* source, uint32_t lobby, uint32_t member, int changes)
        {
            // This is the half that makes a mute permanent, so it is the half
            // that has to stand down. Checked before the load so session-only
            // mode never even opens mutes.cfg.
            if (!IsPersistentPlayerMuteEnabled())
                return;

            EnsureMutesConfigLoaded();

            if (g_MuteRecords.empty())
                return;

            if (g_BzrFn_CommandHandler && g_BzrFn_BanLookup)
            {
                int reapplied = 0;
                for (uint16_t sessionId = 0; sessionId < kBanScanMaxSessionId; ++sessionId)
                {
                    BanLookupIdentity identity = {};
                    if (!TryGetBanLookupIdentityForSessionId(sessionId, identity))
                        continue;

                    if (!IsMuteIdPersisted(identity.stableId))
                        continue;

                    const char* nameText =
                        (identity.name && identity.name->size) ? BzrStringData(identity.name) : "";
                    Log(L"[MUTE] %hs reapplying session=%u stable=%hs name=%hs lobby=0x%08X member=0x%08X changes=0x%08X\n",
                        source ? source : "mute",
                        sessionId,
                        identity.stableId,
                        nameText,
                        lobby,
                        member,
                        static_cast<uint32_t>(changes));

                    AddMuteConfigEntry(identity.stableId, identity.name, "reapply");
                    g_BzrFn_CommandHandler(sessionId, "/mute");
                    ++reapplied;
                }

                if (reapplied > 0)
                {
                    Log(L"[MUTE] %hs reapplied lobby=0x%08X member=0x%08X changes=0x%08X mutes=%d entries=%u\n",
                        source ? source : "mute",
                        lobby,
                        member,
                        static_cast<uint32_t>(changes),
                        reapplied,
                        static_cast<unsigned>(g_MuteRecords.size()));
                }
            }
        }
    }

    bool __cdecl HandleCommandHelpBan(uint16_t id, const char* cmd)
    {
        if (!cmd || !*cmd)
            return false;

        if (_stricmp(cmd, "/help") == 0)
        {
            static const char* kHelpLines[] =
            {
                "[M] - mute/unmute - select the player in the list and click \"M\"",
                "[L] - kick - select the player in the list and click \"K\"",
                "[B] - ban - select the player in the list and click \"B\"",
                "/lock - prevent new players from joining",
                "/unlock - allow new players to join",
                "/nickname <text> - set your multiplayer name (/name alias)",
            };

            void* helpObj = (g_BzrPtr_920168 && *g_BzrPtr_920168) ? *g_BzrPtr_920168 : nullptr;
            for (const char* line : kHelpLines)
            {
                if (g_BzrFn_HelpLog && helpObj)
                    g_BzrFn_HelpLog(helpObj, line);
                if (g_BzrFn_HelpUi)
                    g_BzrFn_HelpUi(0, line);
            }
            return true;
        }

        // OpenShim already owns the multiplayer chat-command interception used
        // by /help and /ban. Keep nickname handling here instead of adding a
        // second EXU detour over the same Redux text path. /name remains as a
        // compatibility alias; /nickname is the documented command.
        const char* nicknameArgs = nullptr;
        if (_strnicmp(cmd, "/nickname", 9) == 0 && (cmd[9] == '\0' || cmd[9] == ' '))
            nicknameArgs = cmd + 9;
        else if (_strnicmp(cmd, "/name", 5) == 0 && (cmd[5] == '\0' || cmd[5] == ' '))
            nicknameArgs = cmd + 5;

        if (nicknameArgs)
        {
            void* helpObj = (g_BzrPtr_920168 && *g_BzrPtr_920168) ? *g_BzrPtr_920168 : nullptr;
            const auto report = [&](const char* line)
            {
                if (g_BzrFn_HelpLog && helpObj)
                    g_BzrFn_HelpLog(helpObj, line);
                if (g_BzrFn_HelpUi)
                    g_BzrFn_HelpUi(0, line);
            };

            const std::string requested = TrimAsciiCopy(nicknameArgs);
            char message[256] = {};
            if (requested.empty())
            {
                char current[128] = {};
                if (ReadBzrNetNickname(current, sizeof(current)) && current[0] != '\0')
                {
                    std::snprintf(message, sizeof(message),
                                  "Multiplayer name is \"%s\" - /nickname <text> to change it", current);
                }
                else
                {
                    std::snprintf(message, sizeof(message), "Usage: /nickname <text>");
                }
                report(message);
                return true;
            }

            const BzrNetNicknameResult result = ApplyBzrNetNicknameAuthoritative(
                requested.c_str(), "chat_command");
            if (!IsAcceptedBzrNetNicknameResult(result))
            {
                if (result == BzrNetNicknameResult::InvalidNickname)
                    report("Invalid nickname. Use 1-127 printable characters.");
                else
                    report("Could not persist the multiplayer nickname.");
                return true;
            }

            SyncNicknameEntriesFromAuthoritativeValue(requested.c_str());
            const char* outcome = "saved for the next BZRNet connection";
            if (result == BzrNetNicknameResult::NativeSendCompleted)
                outcome = "sent to the server; peers should see the new name shortly";
            else if (result == BzrNetNicknameResult::ReauthQueued)
                outcome = "reconnecting BZRNet; new name applies on the next Authorization";
            else if (result == BzrNetNicknameResult::LiveSendUnavailable)
                outcome = "saved; live update unavailable until reconnect/rejoin";
            else if (result == BzrNetNicknameResult::UnsupportedBuild)
                outcome = "saved; live rename unsupported on this build";
            else if (result == BzrNetNicknameResult::NativeStateInvalid)
                outcome = "saved; live BZRNet state unavailable";

            std::snprintf(message, sizeof(message),
                          "Multiplayer name set to \"%s\" - %s",
                          requested.c_str(), outcome);
            report(message);
            Log(L"[BZRNET] /nickname result=%hs\n",
                BzrNetNicknameResultName(result));
            NetRouteRefreshHost();
            NetRouteRefreshClient();
            return true;
        }

        if (_stricmp(cmd, "/ban") == 0)
        {
            if (g_BzrFn_IsHost && g_BzrFn_IsHost() == 0)
            {
                Log(L"[BAN] /ban blocked (client mode)\n");
                return true;
            }
            if (static_cast<int16_t>(id) < 0)
            {
                Log(L"[BAN] /ban failed: invalid target id (id=%u)\n", id);
                return true;
            }
            else if (!g_BzrFn_BanLookup)
            {
                Log(L"[BAN] /ban failed: ban lookup unavailable (id=%u)\n", id);
                return true;
            }

            BanLookupIdentity identity = {};
            if (!TryGetBanLookupIdentityForSessionId(id, identity))
            {
                Log(L"[BAN] /ban failed: lookup returned no stable identity (id=%u)\n", id);
                return true;
            }

            AddBanConfigEntry(identity.stableId, identity.name, "/ban");
            Log(L"[BAN] /ban queued immediate enforcement session=%u stable=%hs name=%hs\n",
                id,
                identity.stableId,
                (identity.name && identity.name->size) ? BzrStringData(identity.name) : "");
            if (g_BzrFn_CommandHandler)
                g_BzrFn_CommandHandler(id, "/kick");
            return true;
        }

        // Persistent mute support. Redux's own command handler performs the
        // native mute; we only record (or forget) the stable identity so the
        // mute can be reapplied in later sessions. Returning false lets the
        // stock handler run unchanged.
        if (_stricmp(cmd, "/mute") == 0)
        {
            // Session-only mode has nothing to record, and the stock handler
            // still does the muting, so leave before spending a lookup on it.
            if (!IsPersistentPlayerMuteEnabled())
                return false;

            if (static_cast<int16_t>(id) < 0)
            {
                Log(L"[MUTE] /mute failed: invalid target id (id=%u)\n", id);
                return false;
            }
            if (!g_BzrFn_BanLookup)
            {
                Log(L"[MUTE] /mute skipped: lookup unavailable (id=%u)\n", id);
                return false;
            }

            BanLookupIdentity identity = {};
            if (!TryGetBanLookupIdentityForSessionId(id, identity))
            {
                Log(L"[MUTE] /mute skipped: no stable identity for session=%u\n", id);
                return false;
            }

            AddMuteConfigEntry(identity.stableId, identity.name, "/mute");
            Log(L"[MUTE] /mute persisted session=%u stable=%hs name=%hs\n",
                id,
                identity.stableId,
                (identity.name && identity.name->size) ? BzrStringData(identity.name) : "");
            return false;
        }

        if (_stricmp(cmd, "/unmute") == 0)
        {
            if (static_cast<int16_t>(id) < 0)
            {
                Log(L"[MUTE] /unmute failed: invalid target id (id=%u)\n", id);
                return false;
            }
            if (!g_BzrFn_BanLookup)
            {
                Log(L"[MUTE] /unmute skipped: lookup unavailable (id=%u)\n", id);
                return false;
            }

            BanLookupIdentity identity = {};
            if (!TryGetBanLookupIdentityForSessionId(id, identity))
            {
                Log(L"[MUTE] /unmute skipped: no stable identity for session=%u\n", id);
                return false;
            }

            RemoveMuteConfigEntry(identity.stableId, "/unmute");
            Log(L"[MUTE] /unmute cleared session=%u stable=%hs\n", id, identity.stableId);
            return false;
        }

        return false;
    }

    void __cdecl HandleJoinerEvent(uint32_t lobby, uint32_t member, int changes)
    {
        EnsureBansConfigLoaded();
        Log(L"[BAN] Join event observed lobby=0x%08X member=0x%08X changes=0x%08X bans=%u host=%hs\n",
            lobby,
            member,
            static_cast<uint32_t>(changes),
            static_cast<unsigned>(g_BanRecords.size()),
            (g_BzrFn_IsHost && g_BzrFn_IsHost() != 0) ? "yes" : "no");
        KickBannedPlayers("join_event", lobby, member, changes);
        ReapplyPersistentMutes("join_event", lobby, member, changes);
    }
}
