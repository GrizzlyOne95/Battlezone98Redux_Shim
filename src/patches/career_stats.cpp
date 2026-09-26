// career_stats.cpp
// BZR Open Shim - career statistics: the career_stats.cfg store, the
// multiplayer session worker and RecordDeath hook, the event-layer
// consumers (pending victims, derived kills, session state), reset and
// its bridge accessor, with the opt-in player-kill research trace that
// shares the RecordDeath hooks, split out of bzr_hooks.cpp. The event
// layer itself stays there.
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
        // ====================================================================
        // CAREER STATISTICS ON THE NATIVE EVENT LAYER
        // ====================================================================
        //
        // WHY THIS EXISTS
        //
        // Career statistics used to be two disconnected things. Campaign
        // Reimagined tracked single-player kills in Lua (Scripts/CareerStats.lua)
        // on top of EXU's BulletHit patch, so only content that shipped that
        // script counted anything. OpenShim tracked multiplayer kills natively,
        // but only through NetPlayer::RecordDeath, which reports TEAMS, not
        // objects, and never runs outside a network game.
        //
        // The network-only part is structural, not incidental. RecordDeath
        // (0x00577290) has exactly one caller, the score-notify helper
        // 0x004B9BA0, and every one of that helper's four call sites is guarded
        // by 0x00572A70 -> 0x00571C40, whose entire body is
        // `return DAT_00917F7B` -- the isNetGame global. So no amount of work
        // on that path can ever produce a single-player statistic.
        //
        // WHAT REPLACES IT
        //
        // The four damage handlers ARE shared between single player and network
        // games, and OpenShim already rides all four of them: the "Damage
        // Reveal Probe 1..4/4" call-site patches replace the four rel32 calls to
        // GameObject::SetDamageFlags at 0x0047EFA0, 0x004AA678, 0x005A0CE2 and
        // 0x005AA372. That hook sees (victim, DAMAGE{damager, source}) on every
        // damage application in all content, which is exactly the attribution
        // the Lua version had to reconstruct by polling GetWhoShotMe.
        //
        // SetDamageFlags runs BEFORE the damage is applied, so it cannot report
        // a kill by itself. Each of those four handlers then applies damage and
        // tests, in the decompiled form:
        //
        //     if (healthRatio <= 0.0 && healthRatio != 0.0 &&
        //         (objectState->flags & 0x200) == 0) {
        //         objectState->flags |= 0x200;      // <- unconditional
        //         if (isNetGame() && GetTeam() != 0) {
        //             RecordDeath(...); NotifyScore(...);   // <- net only
        //         }
        //     }
        //
        // The latch write is outside the network gate. So the death signal is
        // available everywhere; only the scoring built on it was gated. This
        // code therefore records the damage association at SetDamageFlags time
        // and resolves the death on the next safe tick, which is the same
        // pending-victim design CareerStats.lua already validated in Lua
        // (PendingVictims / PendingTimeout), lifted into the engine layer so
        // every mission gets it without shipping a script.
        //
        // FIELD EVIDENCE
        //
        //   healthRatio  complete+0x200  float
        //       GameObject::Save (0x004DE110) emits
        //       ::out(file, this + 0x200, 4, "healthRatio"), and the four
        //       damage handlers test that same float. Note the engine's test is
        //       `<= 0.0 && != 0.0`, i.e. strictly less than zero; exactly 0.0 is
        //       NOT death. This mirrors that rather than "fixing" it.
        //   objectState  complete+0xF4   pointer
        //       Already used by GameObjectHandleGetObjHardened above, which
        //       reads the same +0xF4 -> +0x14 flags word.
        //   death latch  objectState+0x14 bit 0x200
        //       Set exactly once per object, by the block quoted above.
        //
        // SCOPE, AND WHY THE TWO SOURCES DO NOT DOUBLE-COUNT
        //
        // Single player uses the damage-derived path: per-object attribution
        // against the local player's own handle. Network games keep using
        // RecordDeath, which is the engine's own authoritative scoring path --
        // a client's local damage simulation is not authority, and counting
        // both would inflate every multiplayer session. The split is enforced
        // in CareerRecordDerivedKill / the TeamDeath sink case below.

        // NetPlayer id, read as uint16. This is the same field the
        // multiplayer flag diagnostic below has always read; do not
        // introduce a second, guessed offset for it.
        constexpr size_t kNetPlayerIdOffset = 0x28;

        // NetPlayer::RecordDeath(int killedTeam, int killerTeam) on the live
        // 2.2.301 exe (advisory-PDB VA 0x004D9210 had drifted; re-derived via
        // the "NetPlayer::SetTeam team=%d" debug-string xref cluster and
        // matched against the 1.5 decompile: netPlayerByTeam[] at 0x9180E8,
        // playerId +0x28, deaths +0x6C, kills +0x70). Same VA on Steam: the
        // Steam exe is the identical build wrapped in SteamStub (.bind), whose
        // .text decrypts in place at runtime.
        constexpr uintptr_t kGogRecordDeathEntryAddr = 0x00577290;

        // DistributedObject::RecordDeath(int) candidate (BSim 0x48a281 -> 0x6796D0).
        // Advisory until qualified via ExpectedBytesMatchAt on GOG and Steam.
        constexpr uintptr_t kGogDistributedRecordDeathIntAddr = 0x006796D0;

        // Same VA on Steam after SteamStub .bind decrypts .text in place (see kGogRecordDeathEntryAddr note).
        // Separate constant kept for distribution-specific override if validation diverges.
        constexpr uintptr_t kSteamDistributedRecordDeathIntAddr = 0x006796D0;

        // SetAsUser / SetAsNotUser had a probe here. Its addresses
        // (0x00495468 / 0x004954D7) are not function entries: both land
        // mid-instruction inside a local-variable store, and there is no
        // 55 8B EC prologue within 0x800 bytes behind either one. They read
        // like the tail of a displacement from a .text reference scan. The
        // prologue guard rejected them every time, so the probe never
        // installed and only cost a re-probe and two log lines per sim
        // tick. Removed rather than left failing; see
        // Docs/MP_EXPLOSIVE_AUTHORITY_QUALIFICATION.md before reviving it.
        constexpr uintptr_t kSteam64GlobalAddr = 0x0260B1D0;

        constexpr uintptr_t kUiWrapperActiveAddr = 0x00918324;

        constexpr size_t kRecordDeathDetourLen = 6;

        constexpr ULONGLONG kCareerStatsMpHookRetryMs = 1000;

        constexpr ULONGLONG kCareerStatsMpHookRetryWindowMs = 15000;

        constexpr DWORD kCareerStatsMpSessionPollIntervalMs = 1000;

        constexpr ULONGLONG kCareerStatsMpSessionResetMs = 15000;

        static InlineDetour32 g_DistributedRecordDeathIntDetour = {};

        static bool g_DistributedRecordDeathIntHookAttempted = false;

        static uint64_t g_DistributedRecordDeathIntFirstTick = 0;

        static uint64_t g_DistributedRecordDeathIntLastTick = 0;

        static bool g_DistributedRecordDeathIntMismatchLogged = false;

        static constexpr size_t kDistributedRecordDeathIntDetourLen = 6;

        static constexpr uint64_t kDistributedHookRetryMs = 500;

        static constexpr uint64_t kDistributedHookRetryWindowMs = 30000;

        static SRWLOCK g_CareerStatsLock = SRWLOCK_INIT;

        static volatile long g_CareerStatsMpSessionWorkerStarted = 0;

        static bool g_CareerStatsMpMatchRecorded = false;

        static std::string g_CareerStatsMpMatchProfileKey;

        static std::string g_CareerStatsMpMatchMissionKey;

        static ULONGLONG g_CareerStatsMpLastActiveTick = 0;

        bool TryReadSteam64Value(uint64_t& outValue)
        {
            outValue = 0;
            __try
            {
                outValue = *reinterpret_cast<volatile const uint64_t*>(kSteam64GlobalAddr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outValue = 0;
                return false;
            }

            return outValue != 0;
        }

        static uint32_t ReadUiWrapperActiveValue()
        {
            __try
            {
                return *reinterpret_cast<volatile const uint32_t*>(kUiWrapperActiveAddr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        // `capacity` is the size of outBuffer, terminator included, so at most
        // capacity - 1 characters are read. It used to read `capacity` and then
        // write the terminator one past the end.
        static size_t ReadInlineAsciiBufferRaw(uintptr_t address, char* outBuffer, size_t capacity)
        {
            if (!outBuffer || capacity == 0)
                return 0;

            size_t length = 0;
            outBuffer[0] = '\0';

            __try
            {
                const char* buffer = reinterpret_cast<const char*>(address);
                for (size_t i = 0; i + 1 < capacity; ++i)
                {
                    const char ch = buffer[i];
                    if (ch == '\0')
                        break;
                    outBuffer[length++] = ch;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                length = 0;
            }

            outBuffer[length] = '\0';
            return length;
        }

        static std::string ReadInlineAsciiBuffer(uintptr_t address, size_t capacity)
        {
            if (capacity == 0)
                return {};

            // One extra byte so an engine buffer filled to `capacity` with no
            // NUL still comes back whole.
            std::string value(capacity + 1, '\0');
            const size_t length = ReadInlineAsciiBufferRaw(address, value.data(), capacity + 1);
            value.resize(length);
            return value;
        }

        // kCareerStatsEnabledDefault / g_CareerStatsEnabled are defined above
        // the multiplayer session worker, which is the earliest reader.
        static bool g_CareerStatsSinkRegistered = false;

        // GameObject::GetHandle comes from g_GameObjectGetHandleAddr, the same
        // resolve GameObjectFromHandleGog above round-trips through.
        static constexpr size_t kGameObjectHealthRatioOffset = 0x200;

        // complete+0xF4 is the object-state pointer; see
        // GameObjectHandleGetObjHardened above, which reads the same field.
        static constexpr size_t kGameObjectStateOffset = 0xF4;

        static constexpr size_t kGameObjectStateFlagsOffset = 0x14;

        static constexpr uint32_t kGameObjectStateDeathRecordedFlag = 0x200u;

        // Bounded on purpose: this is a fixed table walked once per frame, not
        // a map that grows with the battle. Anything that outlives the timeout
        // without dying is not a kill anyone is waiting on.
        static constexpr size_t kCareerPendingVictimCapacity = 64;

        static constexpr uint64_t kCareerPendingVictimTimeoutMs = 2000;

        // Touched only from the event drain, which runs on the game's main
        // thread from LegacyWorldUpdateRenderQueueHook. Producers never reach
        // it; they only publish.
        static CareerPendingVictim g_CareerPendingVictims[kCareerPendingVictimCapacity] = {};

        // Mirrors the engine's own death test. Both signals are read because
        // either one alone has a hole: healthRatio is reset by the load path,
        // and the latch is only set by the four handlers this rides on.
        //
        // No TryGetGameObjectFieldBase here on purpose. This runs once per
        // pending victim per frame, and that helper costs two VirtualQuery
        // calls; the caller has already round-tripped the handle through
        // GameObject::GetHandle, which is what proves the slot is a live
        // GameObject, and the pool arena is always mapped. The __try stays as
        // the backstop.
        static bool TryReadGameObjectDeathState(void* objectPtr, bool& outDead)
        {
            outDead = false;
            if (!objectPtr)
                return false;

            auto* base = reinterpret_cast<const uint8_t*>(objectPtr);
            __try
            {
                const float healthRatio =
                    *reinterpret_cast<const float*>(base + kGameObjectHealthRatioOffset);
                bool dead = (healthRatio < 0.0f);

                void* objectState =
                    *reinterpret_cast<void* const*>(base + kGameObjectStateOffset);
                if (objectState)
                {
                    const uint32_t flags = *reinterpret_cast<const uint32_t*>(
                        reinterpret_cast<const uint8_t*>(objectState) +
                        kGameObjectStateFlagsOffset);
                    if ((flags & kGameObjectStateDeathRecordedFlag) != 0)
                        dead = true;
                }

                outDead = dead;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static std::filesystem::path GetCareerStatsPath()
        {
            return GetConfigModuleDirectory() / "career_stats.cfg";
        }

        static std::string SanitizeCareerStatsKeyToken(const std::string& value, const char* fallback)
        {
            std::string sanitized;
            sanitized.reserve(value.size());

            for (const char ch : value)
            {
                const unsigned char uch = static_cast<unsigned char>(ch);
                if (std::isalnum(uch) || ch == '.' || ch == '_' || ch == '-')
                {
                    sanitized.push_back(static_cast<char>(std::tolower(uch)));
                }
                else if (!sanitized.empty() && sanitized.back() != '_')
                {
                    sanitized.push_back('_');
                }
            }

            while (!sanitized.empty() && sanitized.front() == '_')
                sanitized.erase(sanitized.begin());
            while (!sanitized.empty() && sanitized.back() == '_')
                sanitized.pop_back();

            if (!sanitized.empty())
                return sanitized;

            return fallback ? fallback : "unknown";
        }

        // Last mission name seen in the engine's queued-load name buffer.
        //
        // That buffer is shared state: the shell fills it with the current
        // mission, and QueueAutoSaveLoadPath blanks it so the load screen uses
        // the explicit autosave path instead of re-deriving one from the name.
        // Blanking it destroys the only mission identity the career stats had,
        // so keep a copy of it here before it goes.
        char g_LastKnownQueuedMissionName[kQueuedLoadNameBufferLen + 1] = {};

        void RememberQueuedMissionName(const char* name)
        {
            if (name && name[0])
                strncpy_s(g_LastKnownQueuedMissionName, name, _TRUNCATE);
        }

        static std::string ResolveCareerStatsMissionKey()
        {
            const auto normalizeCandidate = [](const std::string& candidate) -> std::string
            {
                if (candidate.empty())
                    return {};

                std::filesystem::path path(candidate);
                std::string stem = path.stem().string();
                if (stem.empty())
                    stem = path.filename().string();
                if (stem.empty())
                    stem = candidate;

                return SanitizeCareerStatsKeyToken(stem, "");
            };

            const std::string queuedName =
                normalizeCandidate(ReadInlineAsciiBuffer(kQueuedLoadNameBufferAddr, kQueuedLoadNameBufferLen));
            if (!queuedName.empty())
            {
                RememberQueuedMissionName(queuedName.c_str());
                return queuedName;
            }

            if (g_LastKnownQueuedMissionName[0])
                return normalizeCandidate(g_LastKnownQueuedMissionName);

            // Falling back to the queued path only works while it names a
            // mission. After an autosave load it names the save file, whose stem
            // is "auto" -- a single bogus key every autosave-resumed session
            // would file its stats under. It is not a mission, so refuse it
            // rather than inventing one.
            const std::string queuedPath =
                normalizeCandidate(ReadInlineAsciiBuffer(kQueuedLoadPathBufferAddr, MAX_PATH));
            if (_stricmp(queuedPath.c_str(), "auto") == 0)
                return {};

            return queuedPath;
        }

        static std::string ResolveCareerStatsProfileKey()
        {
            uint64_t steam64 = 0;
            if (TryReadSteam64Value(steam64))
                return SanitizeCareerStatsKeyToken(std::to_string(steam64), "offline");

            if (g_BzrFn_GetLocalPlayerNetId)
            {
                const uint16_t netId = g_BzrFn_GetLocalPlayerNetId();
                if (netId != 0)
                    return SanitizeCareerStatsKeyToken("netid_" + std::to_string(netId), "offline");
            }

            return "offline";
        }

        static void LoadCareerStatsFile(std::unordered_map<std::string, std::string>& outData)
        {
            outData.clear();

            const std::filesystem::path path = GetCareerStatsPath();
            std::ifstream input(path);
            if (!input.is_open())
                return;

            std::string line;
            while (std::getline(input, line))
            {
                const size_t split = line.find('=');
                if (split == std::string::npos || split == 0)
                    continue;

                std::string key = line.substr(0, split);
                std::string value = line.substr(split + 1);
                if (key.empty())
                    continue;

                outData[key] = value;
            }
        }

        // Written through a temp file and swapped into place. Truncating the
        // real file first meant a crash mid-write (and this shim ships a crash
        // logger precisely because crashes happen) left career_stats.cfg empty
        // or half-written, losing the player's whole career record. RecordDeath
        // saves often, so that window came around constantly.
        static bool SaveCareerStatsFile(const std::unordered_map<std::string, std::string>& data)
        {
            const std::filesystem::path path = GetCareerStatsPath();
            const std::filesystem::path tempPath =
                std::filesystem::path(path.wstring() + L".openshim.tmp");

            {
                std::ofstream output(tempPath, std::ios::trunc);
                if (!output.is_open())
                    return false;

                std::vector<std::string> keys;
                keys.reserve(data.size());
                for (const auto& entry : data)
                    keys.push_back(entry.first);

                std::sort(keys.begin(), keys.end());
                for (const auto& key : keys)
                {
                    const auto it = data.find(key);
                    if (it == data.end())
                        continue;

                    output << it->first << '=' << it->second << '\n';
                }

                output.flush();
                if (!output.good())
                {
                    output.close();
                    std::error_code ignored;
                    std::filesystem::remove(tempPath, ignored);
                    return false;
                }
            }

            std::error_code existsError;
            if (!std::filesystem::exists(path, existsError))
            {
                if (MoveFileExW(tempPath.c_str(), path.c_str(), MOVEFILE_WRITE_THROUGH))
                    return true;

                std::error_code ignored;
                std::filesystem::remove(tempPath, ignored);
                return false;
            }

            bool replaced = ReplaceFileW(path.c_str(),
                                         tempPath.c_str(),
                                         nullptr,
                                         REPLACEFILE_IGNORE_MERGE_ERRORS,
                                         nullptr,
                                         nullptr) != FALSE;
            if (!replaced)
            {
                replaced = MoveFileExW(tempPath.c_str(),
                                       path.c_str(),
                                       MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != FALSE;
            }
            if (!replaced && CopyFileW(tempPath.c_str(), path.c_str(), FALSE))
            {
                std::error_code ignored;
                std::filesystem::remove(tempPath, ignored);
                replaced = true;
            }
            if (!replaced)
            {
                std::error_code ignored;
                std::filesystem::remove(tempPath, ignored);
                Log(L"[CAREER] Atomic replace failed for %hs\n", path.string().c_str());
                return false;
            }

            return true;
        }

        static int GetCareerStatsInteger(const std::unordered_map<std::string, std::string>& data,
                                         const std::string& key)
        {
            const auto it = data.find(key);
            if (it == data.end())
                return 0;

            return std::atoi(it->second.c_str());
        }

        static void IncrementCareerStatsInteger(std::unordered_map<std::string, std::string>& data,
                                                const std::string& key,
                                                int amount)
        {
            data[key] = std::to_string(GetCareerStatsInteger(data, key) + amount);
        }

        static bool EnsureMultiplayerCareerSessionRecordedLocked(
            std::unordered_map<std::string, std::string>& data,
            const std::string& profileKey,
            const std::string& missionKey,
            const char* sourceTag)
        {
            if (profileKey.empty() || missionKey.empty())
                return false;

            if (g_CareerStatsMpMatchRecorded &&
                g_CareerStatsMpMatchProfileKey == profileKey &&
                g_CareerStatsMpMatchMissionKey == missionKey)
            {
                return false;
            }

            const std::string profilePrefix = "profile." + profileKey;
            IncrementCareerStatsInteger(data, profilePrefix + ".career.mpMatchesPlayed", 1);
            IncrementCareerStatsInteger(data, profilePrefix + ".mission." + missionKey + ".plays", 1);

            g_CareerStatsMpMatchRecorded = true;
            g_CareerStatsMpMatchProfileKey = profileKey;
            g_CareerStatsMpMatchMissionKey = missionKey;

            Log(L"[CAREER] Recorded multiplayer match start source=%hs profile=%hs mission=%hs\n",
                sourceTag ? sourceTag : "unknown",
                profileKey.c_str(),
                missionKey.c_str());
            return true;
        }

        static bool IsMultiplayerCareerSessionActive()
        {
            if (ReadLocalPlayerNetIdValue() == 0)
                return false;

            if (ReadUiWrapperActiveValue() == 0)
                return true;

            return IsMultiplayerPauseMenuOpen();
        }

        // [Career] StatsTracking. Read by InitializeCareerStatsConfig below and
        // honoured by every recording path, including the multiplayer session
        // worker: with tracking off the worker must neither touch
        // career_stats.cfg nor call engine accessors off the game thread.
        static constexpr bool kCareerStatsEnabledDefault = true;
        static bool g_CareerStatsEnabled = kCareerStatsEnabledDefault;

        static void PollMultiplayerCareerSession()
        {
            if (!g_CareerStatsEnabled)
                return;

            const ULONGLONG nowMs = GetTickCount64();
            const bool active = IsMultiplayerCareerSessionActive();

            AcquireSRWLockExclusive(&g_CareerStatsLock);

            if (active)
            {
                g_CareerStatsMpLastActiveTick = nowMs;

                const std::string profileKey = ResolveCareerStatsProfileKey();
                const std::string missionKey = ResolveCareerStatsMissionKey();
                if (!missionKey.empty() &&
                    (!g_CareerStatsMpMatchRecorded ||
                     g_CareerStatsMpMatchProfileKey != profileKey ||
                     g_CareerStatsMpMatchMissionKey != missionKey))
                {
                    const bool previousRecorded = g_CareerStatsMpMatchRecorded;
                    const std::string previousProfileKey = g_CareerStatsMpMatchProfileKey;
                    const std::string previousMissionKey = g_CareerStatsMpMatchMissionKey;
                    std::unordered_map<std::string, std::string> data;
                    LoadCareerStatsFile(data);
                    data["meta.version"] = "1";

                    if (EnsureMultiplayerCareerSessionRecordedLocked(data, profileKey, missionKey, "poll") &&
                        !SaveCareerStatsFile(data))
                    {
                        g_CareerStatsMpMatchRecorded = previousRecorded;
                        g_CareerStatsMpMatchProfileKey = previousProfileKey;
                        g_CareerStatsMpMatchMissionKey = previousMissionKey;
                        const std::string path = GetCareerStatsPath().string();
                        Log(L"[CAREER] Failed writing multiplayer match start file: %hs\n", path.c_str());
                    }
                }
            }
            else if (g_CareerStatsMpMatchRecorded &&
                     g_CareerStatsMpLastActiveTick != 0 &&
                     (nowMs - g_CareerStatsMpLastActiveTick) >= kCareerStatsMpSessionResetMs)
            {
                Log(L"[CAREER] Cleared multiplayer match session profile=%hs mission=%hs\n",
                    g_CareerStatsMpMatchProfileKey.c_str(),
                    g_CareerStatsMpMatchMissionKey.c_str());
                g_CareerStatsMpMatchRecorded = false;
                g_CareerStatsMpMatchProfileKey.clear();
                g_CareerStatsMpMatchMissionKey.clear();
                g_CareerStatsMpLastActiveTick = 0;
            }

            ReleaseSRWLockExclusive(&g_CareerStatsLock);
        }

        static DWORD WINAPI CareerStatsMpSessionThreadProc(LPVOID)
        {
            Log(L"[CAREER] Multiplayer session worker started\n");
            while (true)
            {
                PollMultiplayerCareerSession();
                Sleep(kCareerStatsMpSessionPollIntervalMs);
            }
        }

        void StartCareerStatsMpSessionWorker()
        {
            if (InterlockedCompareExchange(&g_CareerStatsMpSessionWorkerStarted, 1, 0) != 0)
                return;

            HANDLE threadHandle = CreateThread(
                nullptr,
                0,
                CareerStatsMpSessionThreadProc,
                nullptr,
                0,
                nullptr);
            if (!threadHandle)
            {
                InterlockedExchange(&g_CareerStatsMpSessionWorkerStarted, 0);
                Log(L"[CAREER] Failed starting multiplayer session worker (err=%lu)\n", GetLastError());
                return;
            }

            CloseHandle(threadHandle);
        }

        static void RecordMultiplayerCareerStats(int killedTeam, int killerTeam)
        {
            if (!g_CareerStatsEnabled || !g_BzrFn_GetPlayerHandle || !g_BzrFn_GetTeamNum)
                return;

            const int playerHandle = g_BzrFn_GetPlayerHandle();
            if (playerHandle <= 0)
                return;

            const int localTeam = g_BzrFn_GetTeamNum(playerHandle);
            if (localTeam <= 0)
                return;

            const bool localDeath = (killedTeam == localTeam);
            // RecordDeath exposes team ids here; keep the first pass conservative
            // by suppressing same-team kills and counting only cross-team kills.
            const bool localKill = (killerTeam == localTeam && killerTeam > 0 && killerTeam != killedTeam);
            if (!localDeath && !localKill)
                return;

            AcquireSRWLockExclusive(&g_CareerStatsLock);

            std::unordered_map<std::string, std::string> data;
            LoadCareerStatsFile(data);
            data["meta.version"] = "1";

            const std::string profileKey = ResolveCareerStatsProfileKey();
            const std::string missionKey = ResolveCareerStatsMissionKey();
            const std::string profilePrefix = "profile." + profileKey;
            const bool previousRecorded = g_CareerStatsMpMatchRecorded;
            const std::string previousProfileKey = g_CareerStatsMpMatchProfileKey;
            const std::string previousMissionKey = g_CareerStatsMpMatchMissionKey;

            EnsureMultiplayerCareerSessionRecordedLocked(data, profileKey, missionKey, "death");

            if (localKill)
            {
                IncrementCareerStatsInteger(data, profilePrefix + ".career.totalKills", 1);
                IncrementCareerStatsInteger(data, profilePrefix + ".career.mpKills", 1);
                if (!missionKey.empty())
                    IncrementCareerStatsInteger(data, profilePrefix + ".mission." + missionKey + ".kills", 1);
            }
            if (localDeath)
            {
                IncrementCareerStatsInteger(data, profilePrefix + ".career.totalDeaths", 1);
                IncrementCareerStatsInteger(data, profilePrefix + ".career.mpDeaths", 1);
                if (!missionKey.empty())
                    IncrementCareerStatsInteger(data, profilePrefix + ".mission." + missionKey + ".deaths", 1);
            }

            if (!SaveCareerStatsFile(data))
            {
                g_CareerStatsMpMatchRecorded = previousRecorded;
                g_CareerStatsMpMatchProfileKey = previousProfileKey;
                g_CareerStatsMpMatchMissionKey = previousMissionKey;
                const std::string path = GetCareerStatsPath().string();
                Log(L"[CAREER] Failed writing multiplayer career stats file: %hs\n", path.c_str());
            }

            ReleaseSRWLockExclusive(&g_CareerStatsLock);
        }

        void ClearCareerPendingVictims()
        {
            for (auto& entry : g_CareerPendingVictims)
                entry = CareerPendingVictim{};
        }

        // Producer side. Called from DamageRevealProbeHook, so it must stay
        // cheap: read two DAMAGE fields, resolve them with the engine's own
        // accessor, take two guarded GetHandle calls, copy into the queue.
        // No VirtualQuery and no field validation on this path -- everything
        // that can afford to be careful happens on the drain instead.
        //
        // DAMAGE layout: [0] damager obj76, [1] dmg_source obj76. Those are the
        // only two fields SetDamageFlags itself reads, and the obj76 ->
        // GameObject step uses the engine accessor at 0x00479F30 that
        // SetDamageFlags uses, so no offset is assumed here either.
        // Gated on subscribers alone, not on g_CareerStatsEnabled: the career
        // sink unsubscribes when the feature is turned off, so "career stats
        // off and nothing else listening" already collapses to zero cost here,
        // and a future subscriber gets these events without having to be
        // wired into a career-specific predicate.
        void PublishDamageForCareerStatsFromProbe(void* victim, void* damage)
        {
            if (!HasEventSubscribers())
                return;

            int victimHandle = 0;
            if (!TryGetGameObjectHandleValue(victim, victimHandle))
                return;

            void* damagerObj76 = nullptr;
            void* sourceObj76 = nullptr;
            __try
            {
                auto* fields = reinterpret_cast<void* const*>(damage);
                damagerObj76 = fields[0];
                sourceObj76 = fields[1];
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                damagerObj76 = nullptr;
                sourceObj76 = nullptr;
            }

            // Prefer the damager; a collision reports the same obj76 in both
            // fields, and the source is the fallback when the damager is gone.
            void* attackerObj76 = damagerObj76 ? damagerObj76 : sourceObj76;

            void* damagerGameObj = nullptr;
            if (attackerObj76 && g_BzrFn_ResolveObj76GameObject)
            {
                __try
                {
                    damagerGameObj = g_BzrFn_ResolveObj76GameObject(attackerObj76);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    damagerGameObj = nullptr;
                }
            }

            int damagerHandle = 0;
            TryGetGameObjectHandleValue(damagerGameObj, damagerHandle);

            // Resolved here, while the handles still mean what they say.
            int playerHandle = 0;
            if (g_BzrFn_GetPlayerHandle)
                playerHandle = g_BzrFn_GetPlayerHandle();

            PublishSimEvent(OpenShimEventType::SimDamage,
                            victimHandle,
                            damagerHandle,
                            (playerHandle != 0 && victimHandle == playerHandle) ? 1 : 0,
                            (playerHandle != 0 && damagerHandle == playerHandle) ? 1 : 0);
        }

        bool ShouldTracePlayerKills();

        // Drain side: remember who last damaged this victim.
        static void CareerNoteDamageEvent(const OpenShimEvent& event)
        {
            const int victimHandle = SimEventArg(event, 0);
            if (victimHandle == 0)
                return;

            CareerPendingVictim* slot = nullptr;
            CareerPendingVictim* oldest = nullptr;

            for (auto& entry : g_CareerPendingVictims)
            {
                if (entry.inUse && entry.victimHandle == victimHandle)
                {
                    slot = &entry;
                    break;
                }
                if (!entry.inUse && !slot)
                    slot = &entry;
                if (entry.inUse && (!oldest || entry.firstSeenMs < oldest->firstSeenMs))
                    oldest = &entry;
            }

            // Full table: evict the oldest rather than drop the newest. A stale
            // entry is by definition the one least likely to still resolve.
            if (!slot)
                slot = oldest;
            if (!slot)
                return;

            if (!slot->inUse || slot->victimHandle != victimHandle)
            {
                *slot = CareerPendingVictim{};
                slot->inUse = true;
                slot->victimHandle = victimHandle;
                slot->firstSeenMs = event.tickMs;
            }

            slot->lastDamageMs = event.tickMs;
            // Last damager wins, which is what "who got the kill" means.
            const int damagerHandle = SimEventArg(event, 1);
            if (damagerHandle != 0)
            {
                if (slot->damagerHandle != 0 && slot->damagerHandle != damagerHandle)
                {
                    ++slot->distinctDamagers;
                    slot->lastDistinctDamagerMs = event.tickMs;
                }
                else if (slot->distinctDamagers == 0)
                {
                    slot->distinctDamagers = 1;
                }
                slot->damagerHandle = damagerHandle;
            }
            // Resolve teams on the drain (safe, not a probe) so correlation can
            // compare the authoritative killerTeam against the last damager's.
            // The trace is its own consumer here: gating this on event
            // subscribers alone left the trace correlating on teams that were
            // never filled in.
            if (HasEventSubscribers() || ShouldTracePlayerKills())
            {
                void* victimObj = GameObjectFromHandleGog(victimHandle);
                void* damagerObj = GameObjectFromHandleGog(damagerHandle);
                int vTeam = GetGameObjectActualTeam(victimObj);
                int dTeam = GetGameObjectActualTeam(damagerObj);
                if (vTeam != INT_MIN) slot->victimTeam = vTeam;
                if (dTeam != INT_MIN) slot->damagerTeam = dTeam;
                static uint32_t s_damageSeq = 0;
                slot->damageSequence = ++s_damageSeq;
            }
            // Sticky: the player who put the first shot in still counts even if
            // something else lands the last one, and the victim being the
            // player is not something a later hit can undo.
            if (SimEventArg(event, 2) != 0)
                slot->victimWasLocalPlayer = true;
            if (SimEventArg(event, 3) != 0)
                slot->damagerWasLocalPlayer = true;
        }

        // Drain side, once per frame: turn pending damage into Kill events.
        void TickCareerPendingVictims()
        {
            if (!HasEventSubscribers())
                return;

            const uint64_t now = GetTickCount64();

            for (auto& entry : g_CareerPendingVictims)
            {
                if (!entry.inUse)
                    continue;

                // Re-resolve by handle, never by the stored pointer. The object
                // arena is a fixed slot table, so a freed slot is reused at the
                // same address by the next object; the handle's generation bits
                // are the only thing that distinguishes them.
                void* object = GameObjectFromHandleGog(entry.victimHandle);

                bool died = false;
                if (!object)
                {
                    // Handle no longer resolves: the object left the pool. It
                    // was being damaged moments ago, so treat that as a death.
                    died = true;
                }
                else
                {
                    bool dead = false;
                    if (TryReadGameObjectDeathState(object, dead) && dead)
                        died = true;
                }

                if (died)
                {
                    PublishSimEvent(OpenShimEventType::SimKill,
                                    entry.victimHandle,
                                    entry.damagerHandle,
                                    entry.victimWasLocalPlayer ? 1 : 0,
                                    entry.damagerWasLocalPlayer ? 1 : 0);
                    entry = CareerPendingVictim{};
                    continue;
                }

                if (now - entry.lastDamageMs >= kCareerPendingVictimTimeoutMs)
                    entry = CareerPendingVictim{};
            }
        }

        // -----------------------------------------------------------------
        // Player-kill research instrumentation (PR 107 phase 2-3)
        // -----------------------------------------------------------------
        // Opt-in via OPENSHIM_TRACE_PLAYER_KILLS=1. Logs one compact record
        // per authoritative multiplayer death with candidate controller fields.
        // No career-stats or scoring change. Fails closed if validation fails.
        struct DistributedTraceInfo
        {
            int handle = 0;
            int team = INT_MIN;
            uint8_t object_type = 0xFF;
            bool net_user = false;
            uint16_t activnet_id = 0xFFFF;
            uint32_t dwLocalID = 0;
            void* aiProcess = nullptr;
            uint32_t aiVtable = 0;
            bool isLocalHandle = false;
            bool teamHasNetPlayer = false;
            uint16_t netPlayerId = 0xFFFF;
            bool hasInfo = false;
        };

        bool ShouldTracePlayerKills()
        {
            return g_TracePlayerKills && g_PlayerKillTraceBudget > 0;
        }

        // A team having a NetPlayer says a human occupies that team slot. It
        // says nothing about whether any particular object on that team is the
        // one that human is driving -- wingmen share the team.
        static bool IsTeamHumanByNetPlayer(int team)
        {
            if (team <= 0 || team > 15) return false;
            auto** byTeam = reinterpret_cast<void**>(kNetPlayerByTeamAddr);
            __try { return byTeam[team] != nullptr; } __except(EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        static uint16_t GetNetPlayerIdForTeam(int team)
        {
            if (team <= 0 || team > 15) return PlayerKillTrace::kNetPlayerIdUnread;
            auto** byTeam = reinterpret_cast<void**>(kNetPlayerByTeamAddr);
            __try {
                void* np = byTeam[team];
                if (!np) return PlayerKillTrace::kNetPlayerIdUnread;
                return *reinterpret_cast<uint16_t*>(
                    reinterpret_cast<uint8_t*>(np) + kNetPlayerIdOffset);
            } __except(EXCEPTION_EXECUTE_HANDLER) { return PlayerKillTrace::kNetPlayerIdUnread; }
        }

        static bool TryReadDistributedTraceInfoForHandle(int handle, DistributedTraceInfo& out)
        {
            out = DistributedTraceInfo{};
            out.handle = handle;
            if (handle == 0) return false;
            void* obj = GameObjectFromHandleGog(handle);
            if (!obj) return false;
            out.hasInfo = true;
            out.team = GetGameObjectActualTeam(obj);
            out.teamHasNetPlayer = IsTeamHumanByNetPlayer(out.team);
            if (out.teamHasNetPlayer) out.netPlayerId = GetNetPlayerIdForTeam(out.team);
            int playerHandle = 0;
            if (g_BzrFn_GetPlayerHandle) __try { playerHandle = g_BzrFn_GetPlayerHandle(); } __except(EXCEPTION_EXECUTE_HANDLER) { playerHandle = 0; }
            out.isLocalHandle = (handle != 0 && handle == playerHandle);
            // DistributedObject fields: try reading at object base. For Craft/Person this is same as GameObject base.
            // For Building, DistributedObject may be offset; attempt both base and derived handle.
            __try {
                auto* base = reinterpret_cast<uint8_t*>(obj);
                // Offsets from 1.5 DistributedObject: net_user +0x60 bool, activnet_id +0x62 ushort, dwLocalID +0x64, object_type +0x68
                // Try direct read; if garbage, it will be logged as observed value.
                out.net_user = *(reinterpret_cast<bool*>(base + 0x60));
                out.activnet_id = *(reinterpret_cast<uint16_t*>(base + 0x62));
                out.dwLocalID = *(reinterpret_cast<uint32_t*>(base + 0x64));
                out.object_type = *(reinterpret_cast<uint8_t*>(base + 0x68));
                // aiProcess at GameObject +0xF0 per core_object_model.md
                out.aiProcess = *(reinterpret_cast<void**>(base + 0xF0));
                if (out.aiProcess) {
                    __try { out.aiVtable = *reinterpret_cast<uint32_t*>(out.aiProcess); } __except(EXCEPTION_EXECUTE_HANDLER) { out.aiVtable = 0; }
                }
            } __except(EXCEPTION_EXECUTE_HANDLER) {}
            // Also try reading via DistributedObject this delta if available: compute delta from victim hook context is not available here.
            return true;
        }

        static bool TryReadDistributedTraceInfoForObject(void* obj, DistributedTraceInfo& out)
        {
            out = DistributedTraceInfo{};
            if (!obj) return false;
            int handle = 0;
            TryGetGameObjectHandleValue(obj, handle);
            out.handle = handle;
            out.team = GetGameObjectActualTeam(obj);
            out.teamHasNetPlayer = IsTeamHumanByNetPlayer(out.team);
            if (out.teamHasNetPlayer) out.netPlayerId = GetNetPlayerIdForTeam(out.team);
            int playerHandle = 0;
            if (g_BzrFn_GetPlayerHandle) __try { playerHandle = g_BzrFn_GetPlayerHandle(); } __except(EXCEPTION_EXECUTE_HANDLER) { playerHandle = 0; }
            out.isLocalHandle = (handle != 0 && handle == playerHandle);
            __try {
                auto* base = reinterpret_cast<uint8_t*>(obj);
                out.net_user = *(reinterpret_cast<bool*>(base + 0x60));
                out.activnet_id = *(reinterpret_cast<uint16_t*>(base + 0x62));
                out.dwLocalID = *(reinterpret_cast<uint32_t*>(base + 0x64));
                out.object_type = *(reinterpret_cast<uint8_t*>(base + 0x68));
                out.aiProcess = *(reinterpret_cast<void**>(base + 0xF0));
                if (out.aiProcess) {
                    __try { out.aiVtable = *reinterpret_cast<uint32_t*>(out.aiProcess); } __except(EXCEPTION_EXECUTE_HANDLER) { out.aiVtable = 0; }
                }
                out.hasInfo = true;
            } __except(EXCEPTION_EXECUTE_HANDLER) {}
            return out.hasInfo;
        }

        // Not a production predicate: it reports what was observed. The rule
        // itself lives in include/player_kill_trace.h so the tests exercise
        // this code rather than a second copy of it.
        static PlayerKillTrace::ControllerFields ControllerFieldsOf(const DistributedTraceInfo& info)
        {
            PlayerKillTrace::ControllerFields f;
            f.team = (info.team == INT_MIN) ? 0 : info.team;
            f.activnet_id = info.activnet_id;
            f.netPlayerId = info.netPlayerId;
            f.teamHasNetPlayer = info.teamHasNetPlayer;
            f.isLocalHandle = info.isLocalHandle;
            return f;
        }

        static const char* ClassifyObjectController(const DistributedTraceInfo& info)
        {
            return PlayerKillTrace::DescribeController(
                PlayerKillTrace::ClassifyController(ControllerFieldsOf(info)));
        }

        static void LogAuthoritativeDeathResearch(
            uint32_t seq,
            const char* path,
            int victimHandle,
            int killerHandle,
            int victimTeam,
            int killerTeam,
            const DistributedTraceInfo& victimInfo,
            const DistributedTraceInfo& killerInfo,
            const char* correlation,
            uint64_t ageMs,
            uint32_t damageSeq)
        {
            if (!ShouldTracePlayerKills()) return;
            if (InterlockedDecrement(&g_PlayerKillTraceBudget) < 0) return;
            Log(L"[PKTRACE] seq=%u path=%hs victimH=%d(killerH=%d) vTeam=%d kTeam=%d "
                L"victim{type=%u netUser=%u act=0x%04X dwLocal=0x%08X team=%d hasNP=%u npId=0x%04X isLocal=%u aiProc=0x%08X vt=0x%08X => %hs} "
                L"killer{type=%u netUser=%u act=0x%04X dwLocal=0x%08X team=%d hasNP=%u npId=0x%04X isLocal=%u aiProc=0x%08X vt=0x%08X => %hs} "
                L"corr=%hs age=%llu dmgSeq=%u\n",
                seq, path, victimHandle, killerHandle, victimTeam, killerTeam,
                (unsigned)victimInfo.object_type, victimInfo.net_user?1u:0u, (unsigned)victimInfo.activnet_id, (unsigned)victimInfo.dwLocalID, victimInfo.team, victimInfo.teamHasNetPlayer?1u:0u, (unsigned)victimInfo.netPlayerId, victimInfo.isLocalHandle?1u:0u, (uint32_t)(uintptr_t)victimInfo.aiProcess, victimInfo.aiVtable, ClassifyObjectController(victimInfo),
                (unsigned)killerInfo.object_type, killerInfo.net_user?1u:0u, (unsigned)killerInfo.activnet_id, (unsigned)killerInfo.dwLocalID, killerInfo.team, killerInfo.teamHasNetPlayer?1u:0u, (unsigned)killerInfo.netPlayerId, killerInfo.isLocalHandle?1u:0u, (uint32_t)(uintptr_t)killerInfo.aiProcess, killerInfo.aiVtable, ClassifyObjectController(killerInfo),
                correlation, (unsigned long long)ageMs, damageSeq);
        }

        static uint32_t g_PlayerKillSequence = 0;

        using FnDistributedRecordDeathInt = void(__thiscall*)(void* thisPtr, int killerTeam);
        static FnDistributedRecordDeathInt g_BzrFn_DistributedRecordDeathInt = nullptr;

        void __fastcall DistributedRecordDeathIntHook(void* thisPtr, void* /*edx*/, int killerTeam)
        {
            // Preserve victim team before original mutates anything (though it should not).
            int victimTeam = INT_MIN;
            int victimHandle = 0;
            __try { victimHandle = 0; TryGetGameObjectHandleValue(thisPtr, victimHandle); } __except(EXCEPTION_EXECUTE_HANDLER) {}
            __try { victimTeam = GetGameObjectActualTeam(thisPtr); } __except(EXCEPTION_EXECUTE_HANDLER) { victimTeam = INT_MIN; }
            if (g_BzrFn_DistributedRecordDeathInt)
                g_BzrFn_DistributedRecordDeathInt(thisPtr, killerTeam);
            // Research-only logging: only when trace enabled and in net game and victim team valid.
            if (!ShouldTracePlayerKills()) return;
            if (IsSinglePlayerSession()) return;
            if (victimTeam == INT_MIN || victimTeam == 0) return;
            // Find pending damager for correlation
            int killerHandle = 0;
            const char* correlation = "absent";
            uint64_t ageMs = 0;
            int pendingDamagerTeam = INT_MIN;
            uint32_t pendingSeq = 0;
            __try {
                uint64_t now = GetTickCount64();
                CareerPendingVictim* best = nullptr;
                for (auto& e : g_CareerPendingVictims) {
                    if (e.inUse && e.victimHandle == victimHandle) { best = &e; break; }
                }
                // Fallback: if victimHandle not resolved, try by victimTeam most recent
                if (!best) {
                    uint64_t newest = 0;
                    for (auto& e : g_CareerPendingVictims) if (e.inUse && e.victimTeam == victimTeam && e.lastDamageMs > newest) { newest = e.lastDamageMs; best = &e; }
                }
                if (best) {
                    killerHandle = best->damagerHandle;
                    pendingDamagerTeam = best->damagerTeam;
                    pendingSeq = best->damageSequence;
                    ageMs = now > best->lastDamageMs ? (now - best->lastDamageMs) : 0;

                    // Multi-attacker ambiguity is a property of THIS victim's
                    // own damager history. The earlier version counted other
                    // entries sharing the victim's team, i.e. other victims,
                    // which made every busy fight report ambiguous-multi.
                    int otherAttackers = 0;
                    if (best->distinctDamagers > 1 &&
                        now >= best->lastDistinctDamagerMs &&
                        (now - best->lastDistinctDamagerMs) < PlayerKillTrace::kCorrelationLikelyMs)
                    {
                        otherAttackers = best->distinctDamagers - 1;
                    }

                    PlayerKillTrace::CorrelationInput in;
                    in.havePending = true;
                    in.damagerKnown = (killerHandle != 0);
                    in.damagerTeamKnown = (pendingDamagerTeam != INT_MIN);
                    in.damagerTeamMatchesKiller = (pendingDamagerTeam == killerTeam);
                    in.ageMs = ageMs;
                    in.otherAttackersOnVictim = otherAttackers;
                    correlation = PlayerKillTrace::DescribeCorrelation(
                        PlayerKillTrace::ClassifyCorrelation(in));
                }
            } __except(EXCEPTION_EXECUTE_HANDLER) { correlation = "except"; }
            // Gather trace infos
            DistributedTraceInfo victimInfo{}; DistributedTraceInfo killerInfo{};
            TryReadDistributedTraceInfoForObject(thisPtr, victimInfo);
            if (victimHandle != 0) TryReadDistributedTraceInfoForHandle(victimHandle, victimInfo);
            if (killerHandle != 0) TryReadDistributedTraceInfoForHandle(killerHandle, killerInfo); else {
                killerInfo.team = killerTeam;
                killerInfo.teamHasNetPlayer = IsTeamHumanByNetPlayer(killerTeam);
                if (killerInfo.teamHasNetPlayer) killerInfo.netPlayerId = GetNetPlayerIdForTeam(killerTeam);
            }
            uint32_t seq = InterlockedIncrement((LONG*)&g_PlayerKillSequence);
            LogAuthoritativeDeathResearch(seq, "DistributedInt", victimHandle, killerHandle, victimTeam, killerTeam, victimInfo, killerInfo, correlation, ageMs, pendingSeq);
        }

        // Also instrument NetPlayer::RecordDeath to capture sniper/gameObject* path if ever used
        static void TraceNetPlayerRecordDeath(int killedTeam, int killerTeam)
        {
            if (!ShouldTracePlayerKills()) return;
            if (IsSinglePlayerSession()) return;
            // The budget is charged once, by LogAuthoritativeDeathResearch.
            // Charging it here as well drained it at twice the rate on this path.
            // Try to correlate via most recent pending with matching killedTeam
            int victimHandle = 0; int killerHandle = 0; const char* corr = "absent"; uint64_t age=0;
            uint32_t dmgSeq = 0;
            __try {
                uint64_t now = GetTickCount64();
                CareerPendingVictim* best = nullptr; uint64_t newest=0;
                for (auto& e: g_CareerPendingVictims) if (e.inUse && e.victimTeam==killedTeam && e.lastDamageMs>newest) { newest=e.lastDamageMs; best=&e; }
                if (best) {
                    victimHandle = best->victimHandle;
                    killerHandle = best->damagerHandle;
                    age = now > newest ? (now - newest) : 0;
                    dmgSeq = best->damageSequence;
                    PlayerKillTrace::CorrelationInput in;
                    in.havePending = true;
                    in.damagerKnown = (killerHandle != 0);
                    in.damagerTeamKnown = (best->damagerTeam != INT_MIN);
                    in.damagerTeamMatchesKiller = (best->damagerTeam == killerTeam);
                    in.ageMs = age;
                    in.otherAttackersOnVictim =
                        (best->distinctDamagers > 1) ? (best->distinctDamagers - 1) : 0;
                    corr = PlayerKillTrace::DescribeCorrelation(
                        PlayerKillTrace::ClassifyCorrelation(in));
                }
            } __except(EXCEPTION_EXECUTE_HANDLER) {}
            DistributedTraceInfo vInfo{}; DistributedTraceInfo kInfo{};
            if (victimHandle) TryReadDistributedTraceInfoForHandle(victimHandle, vInfo); else { vInfo.team=killedTeam; vInfo.teamHasNetPlayer=IsTeamHumanByNetPlayer(killedTeam); }
            if (killerHandle) TryReadDistributedTraceInfoForHandle(killerHandle, kInfo); else { kInfo.team=killerTeam; kInfo.teamHasNetPlayer=IsTeamHumanByNetPlayer(killerTeam); }
            uint32_t seq = InterlockedIncrement((LONG*)&g_PlayerKillSequence);
            LogAuthoritativeDeathResearch(seq, "NetPlayer", victimHandle, killerHandle, killedTeam, killerTeam, vInfo, kInfo, corr, age, dmgSeq);
        }

        void InstallDistributedRecordDeathIntHookIfPossible()
        {
            if (g_DistributedRecordDeathIntHookInstalled || !ShouldTracePlayerKills()) return;
            if (g_DistributedRecordDeathIntDetour.trampoline && g_BzrFn_DistributedRecordDeathInt) { g_DistributedRecordDeathIntHookInstalled = true; return; }
            const uint64_t now = GetTickCount64();
            if (g_DistributedRecordDeathIntFirstTick==0) g_DistributedRecordDeathIntFirstTick = now;
            if (g_DistributedRecordDeathIntLastTick!=0 && (now - g_DistributedRecordDeathIntLastTick) < kDistributedHookRetryMs) return;
            g_DistributedRecordDeathIntLastTick = now;
            g_DistributedRecordDeathIntHookAttempted = true;
            uintptr_t target = 0;
            if (g_IsSteamExe) target = kSteamDistributedRecordDeathIntAddr; else target = kGogDistributedRecordDeathIntAddr;
            // Re-derive validation: check at least that target is executable and has plausible prolog.
            // From 1.5: RecordDeath(int) is small thiscall: 55 8B EC 83 EC ?? . For Redux candidate 0x6796D0 we expect similar.
            static const uint8_t kExpectedProlog[] = { 0x55, 0x8B, 0xEC };
            if (!ExpectedBytesMatchAt(target, kExpectedProlog, sizeof(kExpectedProlog))) {
                if (!g_DistributedRecordDeathIntMismatchLogged) {
                    Log(L"[PKTRACE] DistributedRecordDeathInt bytes not matched at 0x%08X; will retry %llums\n", (uint32_t)target, (unsigned long long)kDistributedHookRetryWindowMs);
                    g_DistributedRecordDeathIntMismatchLogged = true;
                    // Dump 16 bytes for RE diagnostics (not as identity, just for qualification)
                    __try {
                        uint8_t bytes[16]={}; memcpy(bytes, reinterpret_cast<void*>(target), 16);
                        Log(L"[PKTRACE] bytes at 0x%08X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
                            (uint32_t)target, bytes[0],bytes[1],bytes[2],bytes[3],bytes[4],bytes[5],bytes[6],bytes[7],bytes[8],bytes[9],bytes[10],bytes[11],bytes[12],bytes[13],bytes[14],bytes[15]);
                    } __except(EXCEPTION_EXECUTE_HANDLER) {}
                } else if ((now - g_DistributedRecordDeathIntFirstTick) >= kDistributedHookRetryWindowMs) {
                    Log(L"[PKTRACE] Distributed hook still mismatched after %llums at 0x%08X - failing closed\n", (unsigned long long)(now-g_DistributedRecordDeathIntFirstTick), (uint32_t)target);
                }
                return;
            }
            // Further body check: should contain call to NetPlayer::RecordDeath (indirect). Validate that target calls 0x00577290 region.
            // For now install with trampoline len 6 (push ebp; mov ebp,esp plus one). Detailed delta check omitted; research hook fails closed if install fails.
            if (!InstallInlineDetour32(g_DistributedRecordDeathIntDetour, target, reinterpret_cast<void*>(DistributedRecordDeathIntHook), kDistributedRecordDeathIntDetourLen, kExpectedProlog, sizeof(kExpectedProlog))) {
                Log(L"[PKTRACE] Failed installing DistributedRecordDeathInt hook at 0x%08X\n", (uint32_t)target);
                return;
            }
            g_BzrFn_DistributedRecordDeathInt = reinterpret_cast<FnDistributedRecordDeathInt>(g_DistributedRecordDeathIntDetour.trampoline);
            g_DistributedRecordDeathIntHookInstalled = (g_BzrFn_DistributedRecordDeathInt != nullptr);
            if (g_DistributedRecordDeathIntHookInstalled) {
                g_DistributedRecordDeathIntMismatchLogged = false;
                Log(L"[PKTRACE] Installed DistributedObject::RecordDeath(int) hook at 0x%08X trampoline=0x%08X\n", (uint32_t)target, (uint32_t)(uintptr_t)g_DistributedRecordDeathIntDetour.trampoline);
            }
        }

        // Career persistence for one derived kill. Single player only -- see
        // the double-counting note in this block's header.
        static void CareerRecordDerivedKill(const OpenShimEvent& event)
        {
            if (!g_CareerStatsEnabled || !IsSinglePlayerSession())
                return;

            const bool localDeath = SimEventArg(event, 2) != 0;
            const bool localKill = (SimEventArg(event, 3) != 0) && !localDeath;
            if (!localDeath && !localKill)
                return;

            AcquireSRWLockExclusive(&g_CareerStatsLock);

            std::unordered_map<std::string, std::string> data;
            LoadCareerStatsFile(data);
            data["meta.version"] = "1";

            const std::string profileKey = ResolveCareerStatsProfileKey();
            const std::string missionKey = ResolveCareerStatsMissionKey();
            const std::string profilePrefix = "profile." + profileKey;

            if (localKill)
            {
                IncrementCareerStatsInteger(data, profilePrefix + ".career.totalKills", 1);
                IncrementCareerStatsInteger(data, profilePrefix + ".career.spKills", 1);
                if (!missionKey.empty())
                    IncrementCareerStatsInteger(data, profilePrefix + ".mission." + missionKey + ".kills", 1);
            }
            if (localDeath)
            {
                IncrementCareerStatsInteger(data, profilePrefix + ".career.totalDeaths", 1);
                IncrementCareerStatsInteger(data, profilePrefix + ".career.spDeaths", 1);
                if (!missionKey.empty())
                    IncrementCareerStatsInteger(data, profilePrefix + ".mission." + missionKey + ".deaths", 1);
            }

            if (!SaveCareerStatsFile(data))
            {
                const std::string path = GetCareerStatsPath().string();
                Log(L"[CAREER] Failed writing single-player career stats file: %hs\n", path.c_str());
            }

            ReleaseSRWLockExclusive(&g_CareerStatsLock);
        }

        // One mission play per single-player session. The multiplayer
        // equivalent is already owned by CareerStatsMpSessionThreadProc, which
        // needs its own poll because a network match can start without this
        // driver having seen a world transition.
        static void CareerRecordSinglePlayerSessionStart()
        {
            if (!g_CareerStatsEnabled)
                return;

            AcquireSRWLockExclusive(&g_CareerStatsLock);

            const std::string profileKey = ResolveCareerStatsProfileKey();
            const std::string missionKey = ResolveCareerStatsMissionKey();
            if (!profileKey.empty() && !missionKey.empty())
            {
                std::unordered_map<std::string, std::string> data;
                LoadCareerStatsFile(data);
                data["meta.version"] = "1";

                const std::string profilePrefix = "profile." + profileKey;
                IncrementCareerStatsInteger(data, profilePrefix + ".career.missionsPlayed", 1);
                IncrementCareerStatsInteger(data, profilePrefix + ".career.spMissionsPlayed", 1);
                IncrementCareerStatsInteger(
                    data, profilePrefix + ".mission." + missionKey + ".plays", 1);

                if (SaveCareerStatsFile(data))
                {
                    Log(L"[CAREER] Recorded single-player mission start profile=%hs mission=%hs\n",
                        profileKey.c_str(), missionKey.c_str());
                }
                else
                {
                    const std::string path = GetCareerStatsPath().string();
                    Log(L"[CAREER] Failed writing single-player mission start file: %hs\n", path.c_str());
                }
            }

            ReleaseSRWLockExclusive(&g_CareerStatsLock);
        }

        static void CareerStatsEventSink(const OpenShimEvent& event, void* /*user*/)
        {
            if (!g_CareerStatsEnabled)
                return;

            switch (static_cast<OpenShimEventType>(event.type))
            {
            case OpenShimEventType::SimDamage:
                CareerNoteDamageEvent(event);
                break;
            case OpenShimEventType::SimKill:
                CareerRecordDerivedKill(event);
                break;
            case OpenShimEventType::SimTeamDeath:
                // Network authority path. RecordMultiplayerCareerStats already
                // filters to the local team and does its own file work; it is
                // called here rather than from the detour so no engine hook
                // holds a lock across a disk write.
                RecordMultiplayerCareerStats(SimEventArg(event, 0),
                                             SimEventArg(event, 1));
                break;
            case OpenShimEventType::SimSessionStarted:
                ClearCareerPendingVictims();
                if (SimEventArg(event, 0) == 0)
                    CareerRecordSinglePlayerSessionStart();
                break;
            case OpenShimEventType::SimSessionEnded:
                ClearCareerPendingVictims();
                break;
            default:
                break;
            }
        }

        static void RefreshCareerStatsSubscription()
        {
            if (g_CareerStatsEnabled && !g_CareerStatsSinkRegistered)
            {
                g_CareerStatsSinkRegistered =
                    SubscribeEvents(&CareerStatsEventSink, nullptr);
                if (g_CareerStatsSinkRegistered)
                    Log(L"[CAREER] Statistics tracking enabled (native event layer)\n");
            }
            else if (!g_CareerStatsEnabled && g_CareerStatsSinkRegistered)
            {
                UnsubscribeEvents(&CareerStatsEventSink, nullptr);
                g_CareerStatsSinkRegistered = false;
                ClearCareerPendingVictims();
                Log(L"[CAREER] Statistics tracking disabled\n");
            }
        }

        void InitializeCareerStatsConfig()
        {
            bool configured = false;
            if (TryGetUserConfigBool("Career", "StatsTracking", configured))
                g_CareerStatsEnabled = configured;
            else if (EnvFlagEnabled("OPENSHIM_DISABLE_CAREER_STATS"))
                g_CareerStatsEnabled = false;
            else
                g_CareerStatsEnabled = kCareerStatsEnabledDefault;

            RefreshCareerStatsSubscription();
        }

        // Display-tier baseline is the openshim.ini value, not the compile-time
        // default: reverting a preference means "what the user configured",
        // which for this feature is the same thing as re-reading the key.
        void RevertCareerStatsToBaseline()
        {
            InitializeCareerStatsConfig();
        }

        // Publishes SessionStarted/SessionEnded from the same world-liveness
        // predicate the satellite fix uses, so single player and network games
        // produce one session model. Note the ordering consequence: this driver
        // stops running when the world goes away, so a SessionEnded queued on
        // the last frame is delivered on the FIRST frame of the next world,
        // immediately before that world's SessionStarted. Consumers see the
        // right order, just late; nothing here depends on the dead world.
        void TickCareerSessionState()
        {
            static bool s_WorldWasLive = false;

            // No subscriber check here on purpose. This is a two-state
            // machine, and skipping the update while nothing is listening would
            // leave s_WorldWasLive stale: a subscriber that arrived mid-session
            // would then miss the NEXT world's SessionStarted entirely. The
            // predicate is two guarded pointer reads, and a transition is rare.
            const bool live = SatelliteWorldIsLive();
            if (live == s_WorldWasLive)
                return;

            s_WorldWasLive = live;

            if (live)
            {
                PublishSimEvent(OpenShimEventType::SimSessionStarted,
                                IsSinglePlayerSession() ? 0 : 1);
            }
            else
            {
                // Clear synchronously as well as through the event: the pending
                // table holds handles into a world that no longer exists.
                ClearCareerPendingVictims();
                PublishSimEvent(OpenShimEventType::SimSessionEnded,
                                IsSinglePlayerSession() ? 0 : 1);
            }
        }

        // Wipes the career record. The previous contents are copied to
        // career_stats.cfg.openshim.bak first: this is reachable from a two
        // click confirmation on the settings page, and a player who wipes a
        // long campaign record by accident should have exactly one way back.
        //
        // Only the file and the in-memory session latches are touched. The
        // toggle is deliberately left alone -- "reset my stats" is not "stop
        // recording", and a reset that also disabled tracking would silently
        // stop counting from that point on.
        static CareerStatsResetResult ResetCareerStatsData()
        {
            AcquireSRWLockExclusive(&g_CareerStatsLock);

            const std::filesystem::path path = GetCareerStatsPath();

            std::unordered_map<std::string, std::string> existing;
            LoadCareerStatsFile(existing);

            // "meta.version" alone is not data: a file holding only that is
            // what a previous reset leaves behind.
            size_t recordedKeys = 0;
            for (const auto& entry : existing)
            {
                if (entry.first != "meta.version")
                    ++recordedKeys;
            }

            std::error_code existsError;
            const bool fileExists = std::filesystem::exists(path, existsError);

            if (recordedKeys == 0)
            {
                ReleaseSRWLockExclusive(&g_CareerStatsLock);
                ClearCareerPendingVictims();
                Log(L"[CAREER] Reset requested but nothing was recorded (%hs)\n",
                    path.string().c_str());
                return CareerStatsResetResult::AlreadyEmpty;
            }

            if (fileExists)
            {
                const std::filesystem::path backupPath =
                    std::filesystem::path(path.wstring() + L".openshim.bak");
                std::error_code copyError;
                std::filesystem::copy_file(
                    path, backupPath,
                    std::filesystem::copy_options::overwrite_existing,
                    copyError);
                if (copyError)
                {
                    // Not fatal: the reset is still what was asked for. Say so
                    // rather than pretending a recoverable copy exists.
                    Log(L"[CAREER] Could not back up %hs before reset (%hs)\n",
                        path.string().c_str(), copyError.message().c_str());
                }
            }

            std::unordered_map<std::string, std::string> cleared;
            cleared["meta.version"] = "1";
            const bool saved = SaveCareerStatsFile(cleared);

            if (saved)
            {
                g_CareerStatsMpMatchRecorded = false;
                g_CareerStatsMpMatchProfileKey.clear();
                g_CareerStatsMpMatchMissionKey.clear();
                g_CareerStatsMpLastActiveTick = 0;
            }

            ReleaseSRWLockExclusive(&g_CareerStatsLock);

            // Outside the lock: the pending table belongs to the drain, not to
            // the stats file, and taking both is an ordering nobody else needs.
            ClearCareerPendingVictims();

            if (!saved)
            {
                Log(L"[CAREER] Reset failed writing %hs; existing stats kept\n",
                    path.string().c_str());
                return CareerStatsResetResult::Failed;
            }

            Log(L"[CAREER] Reset career statistics (%zu key(s) cleared) in %hs\n",
                recordedKeys, path.string().c_str());
            return CareerStatsResetResult::Cleared;
        }

        void __cdecl RecordDeathHook(int killedTeam, int killerTeam)
        {
            if (g_BzrFn_RecordDeath)
                g_BzrFn_RecordDeath(killedTeam, killerTeam);
            // Research trace for sniper/GameObject* path coverage (NetPlayer layer)
            TraceNetPlayerRecordDeath(killedTeam, killerTeam);

            // Publish instead of persisting here. This runs inside the engine's
            // score-notify path; the previous version loaded and rewrote
            // career_stats.cfg synchronously on every death, holding an SRW
            // lock across a disk write from inside a detour. The career sink
            // does the same work on the next safe drain instead.
            if (!PublishSimEvent(OpenShimEventType::SimTeamDeath, killedTeam, killerTeam))
            {
                // Dropped (no subscriber, layer off, or queue full). With no
                // subscriber there is nothing to record; otherwise fall back to
                // the direct write so a queue overflow cannot silently lose a
                // multiplayer death.
                if (HasEventSubscribers())
                    RecordMultiplayerCareerStats(killedTeam, killerTeam);
            }
        }

        void InstallCareerStatsMpHookIfPossible()
        {
            if (g_CareerStatsMpHookInstalled)
                return;

            if (g_RecordDeathDetour.trampoline && g_BzrFn_RecordDeath)
            {
                g_CareerStatsMpHookInstalled = true;
                return;
            }

            const ULONGLONG nowMs = GetTickCount64();
            if (g_CareerStatsMpHookFirstAttemptTick == 0)
                g_CareerStatsMpHookFirstAttemptTick = nowMs;

            if (g_CareerStatsMpHookLastAttemptTick != 0 &&
                (nowMs - g_CareerStatsMpHookLastAttemptTick) < kCareerStatsMpHookRetryMs)
            {
                return;
            }

            g_CareerStatsMpHookLastAttemptTick = nowMs;
            g_CareerStatsMpHookInstallAttempted = true;

            static const uint8_t kExpectedRecordDeathBytes[kRecordDeathDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C
            };
            // Body check at +0x0F distinguishes RecordDeath from other small
            // cdecl helpers sharing the generic prologue: cmp [ebp+8],0 / jle /
            // mov eax,[ebp+8] / mov ecx,[eax*4 + netPlayerByTeam(0x9180E8)].
            static const uint8_t kExpectedRecordDeathBodyBytes[] =
            {
                0x83, 0x7D, 0x08, 0x00, 0x7E, 0x3B, 0x8B, 0x45, 0x08,
                0x8B, 0x0C, 0x85, 0xE8, 0x80, 0x91, 0x00
            };
            constexpr uintptr_t kRecordDeathBodyCheckOffset = 0x0F;

            if (!ExpectedBytesMatchAt(kGogRecordDeathEntryAddr,
                                      kExpectedRecordDeathBytes,
                                      sizeof(kExpectedRecordDeathBytes)) ||
                !ExpectedBytesMatchAt(kGogRecordDeathEntryAddr + kRecordDeathBodyCheckOffset,
                                      kExpectedRecordDeathBodyBytes,
                                      sizeof(kExpectedRecordDeathBodyBytes)))
            {
                if (!g_CareerStatsMpHookMismatchLogged)
                {
                    Log(L"[CAREER] RecordDeath entry bytes not settled yet at 0x%08X; retrying for up to %llums\n",
                        static_cast<uint32_t>(kGogRecordDeathEntryAddr),
                        static_cast<unsigned long long>(kCareerStatsMpHookRetryWindowMs));
                    g_CareerStatsMpHookMismatchLogged = true;
                }
                else if ((nowMs - g_CareerStatsMpHookFirstAttemptTick) >= kCareerStatsMpHookRetryWindowMs)
                {
                    Log(L"[CAREER] RecordDeath entry bytes still mismatched at 0x%08X after %llums; continuing guarded retries\n",
                        static_cast<uint32_t>(kGogRecordDeathEntryAddr),
                        static_cast<unsigned long long>(nowMs - g_CareerStatsMpHookFirstAttemptTick));
                    g_CareerStatsMpHookFirstAttemptTick = nowMs;
                }
                return;
            }

            if (!InstallInlineDetour32(g_RecordDeathDetour,
                                       kGogRecordDeathEntryAddr,
                                       reinterpret_cast<void*>(RecordDeathHook),
                                       kRecordDeathDetourLen,
                                       kExpectedRecordDeathBytes,
                                       sizeof(kExpectedRecordDeathBytes)))
            {
                Log(L"[CAREER] Failed installing RecordDeath hook at 0x%08X\n",
                    static_cast<uint32_t>(kGogRecordDeathEntryAddr));
                return;
            }

            g_BzrFn_RecordDeath =
                reinterpret_cast<FnRecordDeath>(g_RecordDeathDetour.trampoline);
            g_CareerStatsMpHookInstalled = (g_BzrFn_RecordDeath != nullptr);
            if (g_CareerStatsMpHookInstalled)
            {
                g_CareerStatsMpHookMismatchLogged = false;
                Log(L"[CAREER] Installed NetPlayer::RecordDeath hook entry=0x%08X trampoline=0x%08X path=%hs\n",
                    static_cast<uint32_t>(kGogRecordDeathEntryAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_RecordDeathDetour.trampoline)),
                    GetCareerStatsPath().string().c_str());
            }
        }
    }

    using namespace Hooks;

    CareerStatsResetResult ResetCareerStatsFromBridge()
    {
        return ResetCareerStatsData();
    }
}
