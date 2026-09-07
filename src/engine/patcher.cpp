// patcher.cpp
// BZR Open Shim - runtime patcher implementation
#include "patcher.h"
#include "hook_engine.h"
#include "patches.h"
#include "scroll_helper.h"
#include "trampolines.h"
#include "d3d_startup_hooks.h"
#include "file_io_hooks.h"
#include "bzr_hooks.h"
#include "openshim_preset_migration.h"
#include "shim_log.h"
#include "sun_flash.h"
#include "openshim_sdk_v2.h"
#include "cli_multiparam_parser.h"
#include "redux_compatibility.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <new>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <atomic>
#include <nlohmann/json.hpp>

namespace BZROpenShim
{
    static std::atomic<bool> g_ShutdownRequested{ false };
    void SignalPatcherShutdown() { g_ShutdownRequested = true; }

    struct PatcherConfig {
        nlohmann::json data;
        bool Load() {
            // One search order for the whole shim: HookEngine::ResolveNamedAddress
            // has to find the same file this does, or a "resolves" entry and the
            // patch that depends on it could come from different installs.
            try {
                const std::string path = HookEngine::FindPatchesJsonPath();
                if (path.empty()) return false;
                std::ifstream f(path);
                if (f.is_open()) { data = nlohmann::json::parse(f); return true; }
            } catch (...) {}
            return false;
        }
        uint32_t GetStaticPointer(const std::string& name, uint32_t defaultVal = 0) {
            if (data.contains("static_pointers")) {
                for (const auto& p : data["static_pointers"]) {
                    if (p["name"] == name) return std::stoul(p["address"].get<std::string>(), nullptr, 16);
                }
            }
            return defaultVal;
        }
        bool GetBool(const std::string& name, bool defaultVal = false) {
            try {
                if (data.contains("features")) {
                    const auto& features = data["features"];
                    if (features.contains(name) && features[name].is_boolean()) {
                        return features[name].get<bool>();
                    }
                }
                if (data.contains(name) && data[name].is_boolean()) {
                    return data[name].get<bool>();
                }
            } catch (...) {}
            return defaultVal;
        }
    };
    static PatcherConfig g_Config;

    // Main-menu version notice. The three "Version Notice"/"Main Menu"
    // globals in patches.json point the game's version string pointer at
    // this buffer, so whatever it holds is what the shell prints.
    //
    // It carries the shim's own build version so a player can read back
    // which DLL is actually loaded. That matters because winmm.dll and
    // scripts/patches.json are deployed by hand and can drift apart, and
    // because a stale DLL left in the game directory is otherwise
    // indistinguishable from a current one at runtime.
    //
    // The version is read from this module's own VERSIONINFO resource
    // rather than a second hard-coded constant, so it cannot disagree with
    // src/engine/version.rc -- which is the value the updater compares
    // against the manifest (see ReadFileVersion in openshim_updater.cpp).
    static const char kOpenShimVersionTagFallback[] = "2.2.301 + BZR Open Shim";
    static char g_OpenShimVersionTag[96] = {};

    // Returns "2.2.301 + BZR Open Shim <a.b.c.d>", or the plain fallback
    // when the resource cannot be read. Never fails, never allocates after
    // the first call; the buffer has process lifetime because the patched
    // pointer outlives this function.
    static const char* GetOpenShimVersionTag()
    {
        if (g_OpenShimVersionTag[0])
            return g_OpenShimVersionTag;

        // Default to the historical text so a failure here is invisible
        // rather than blank.
        strcpy_s(g_OpenShimVersionTag, kOpenShimVersionTagFallback);

        HMODULE self = nullptr;
        if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                    GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                reinterpret_cast<LPCSTR>(&g_OpenShimVersionTag),
                                &self) ||
            !self)
        {
            return g_OpenShimVersionTag;
        }

        char modulePath[MAX_PATH] = {};
        if (GetModuleFileNameA(self, modulePath, MAX_PATH) == 0)
            return g_OpenShimVersionTag;

        DWORD ignored = 0;
        const DWORD infoSize = GetFileVersionInfoSizeA(modulePath, &ignored);
        if (infoSize == 0)
            return g_OpenShimVersionTag;

        std::vector<uint8_t> info(infoSize);
        if (!GetFileVersionInfoA(modulePath, 0, infoSize, info.data()))
            return g_OpenShimVersionTag;

        VS_FIXEDFILEINFO* fixed = nullptr;
        UINT fixedLen = 0;
        if (!VerQueryValueA(info.data(), "\\",
                            reinterpret_cast<LPVOID*>(&fixed), &fixedLen) ||
            !fixed || fixedLen < sizeof(VS_FIXEDFILEINFO))
        {
            return g_OpenShimVersionTag;
        }

        char composed[sizeof(g_OpenShimVersionTag)] = {};
        const int written = _snprintf_s(
            composed, _TRUNCATE, "%s %u.%u.%u.%u",
            kOpenShimVersionTagFallback,
            HIWORD(fixed->dwFileVersionMS), LOWORD(fixed->dwFileVersionMS),
            HIWORD(fixed->dwFileVersionLS), LOWORD(fixed->dwFileVersionLS));
        if (written > 0)
            strcpy_s(g_OpenShimVersionTag, composed);

        return g_OpenShimVersionTag;
    }
    static constexpr uint32_t kDefaultMaxSoundChannels = 256;
    static constexpr uint32_t kMaxSupportedSoundChannels = 256;
    static constexpr uint32_t kGASMasterMaxObjectsOffset = 0x10;
    static constexpr DWORD kSoundChannelRefreshDelayMs = 1000;

    struct SoundChannelOverrideConfig {
        bool enabled = true;
        bool iniOverride = false;
        bool iniInvalid = false;
        bool envOverride = false;
        bool envInvalid = false;
        bool envClamped = false;
        const char* sourceEnv = nullptr;
        uint32_t requestedChannels = kDefaultMaxSoundChannels;
        uint32_t maxChannels = kDefaultMaxSoundChannels;
    };
    struct SoundChannelOverrideTargets {
        uint32_t gmStorageAddress = 0;
        uint32_t gasMasterAddress = 0;
        uint32_t initSiteAddress = 0;
    };
    struct SoundChannelOverrideThreadContext {
        uint32_t gmStorageAddress = 0;
        uint32_t gasMasterAddress = 0;
        uint32_t maxChannels = 0;
    };

    static bool ShouldLogHookHits() {
        static int s_cached = -1;
        if (s_cached < 0) {
            char value[8] = {};
            const DWORD len = GetEnvironmentVariableA("OPENSHIM_TRACE_HITS", value, static_cast<DWORD>(sizeof(value)));
            s_cached = (len > 0 && len < sizeof(value) && value[0] != '0') ? 1 : 0;
        }
        return s_cached != 0;
    }

    static bool ShouldEnableD3DStartupHooks() {
        static int s_cached = -1;
        if (s_cached < 0) {
            char value[8] = {};
            const DWORD len = GetEnvironmentVariableA("OPENSHIM_ENABLE_D3D_STARTUP_HOOKS", value, static_cast<DWORD>(sizeof(value)));
            s_cached = (len > 0 && len < sizeof(value) && value[0] != '0') ? 1 : 0;
        }
        return s_cached != 0;
    }

    // Reads [AutoSave] Enabled out of the openshim.ini next to the exe.
    // Deliberately defaults to "off" rather than mirroring autosave.cpp's own
    // default of 1: this is only used to make the autoload MORE conservative,
    // and an unreadable ini must not silently change the stock startup path.
    static bool AutoSaveEnabledForStartup() {
        char exePath[MAX_PATH] = {};
        const DWORD len = GetModuleFileNameA(nullptr, exePath, static_cast<DWORD>(sizeof(exePath)));
        if (len == 0 || len >= sizeof(exePath)) return false;
        char* const slash = strrchr(exePath, '\\');
        if (!slash) return false;
        slash[1] = '\0';
        std::string ini(exePath);
        ini += "openshim.ini";
        return GetPrivateProfileIntA("AutoSave", "Enabled", 0, ini.c_str()) != 0;
    }

    // The stock startup shell will happily resume the most recent save, and
    // OpenShim's AutoSave writes a rolling recovery slot that qualifies. The
    // two together mean launching the bare exe drops the player straight back
    // into the last autosaved mission instead of the main menu -- which is not
    // what a recovery slot is for. Manual saves are the checkpoints.
    //
    // So AllowStartupAutoLoad=1 asks for the stock path, but AutoSave being on
    // overrides it and keeps the autoload suppressed. A user who genuinely
    // wants the bare exe to resume an autosave can still say so explicitly with
    // OPENSHIM_FORCE_STARTUP_AUTOLOAD=1, which beats both.
    static bool ShouldSuppressStartupAutoLoad() {
        static int s_cached = -1;
        if (s_cached >= 0) return s_cached != 0;

        char value[8] = {};
        const DWORD forceLen = GetEnvironmentVariableA("OPENSHIM_FORCE_STARTUP_AUTOLOAD", value, static_cast<DWORD>(sizeof(value)));
        if (forceLen > 0 && forceLen < sizeof(value) && value[0] != '0') {
            s_cached = 0;
            return false;
        }

        ZeroMemory(value, sizeof(value));
        const DWORD allowLen = GetEnvironmentVariableA("OPENSHIM_ALLOW_STARTUP_AUTOLOAD", value, static_cast<DWORD>(sizeof(value)));
        const bool allow = (allowLen > 0 && allowLen < sizeof(value) && value[0] != '0');
        if (allow && AutoSaveEnabledForStartup()) {
            Log(L"[STARTUP] AllowStartupAutoLoad is on but AutoSave is enabled; "
                L"suppressing the shell autoload so the bare exe does not resume "
                L"the rolling recovery save. Set OPENSHIM_FORCE_STARTUP_AUTOLOAD=1 to override.\n");
            s_cached = 1;
            return true;
        }

        s_cached = allow ? 0 : 1;
        return s_cached != 0;
    }

    static bool ShouldEnableArtilleryMaskTracePatch() {
        static int s_cached = -1;
        if (s_cached < 0) {
            char value[8] = {};
            DWORD len = GetEnvironmentVariableA("OPENSHIM_TRACE_ARTILLERY_MASK", value, static_cast<DWORD>(sizeof(value)));
            if (!(len > 0 && len < sizeof(value) && value[0] != '0')) {
                ZeroMemory(value, sizeof(value));
                len = GetEnvironmentVariableA("OPENSHIM_TRACE_WEAPON_MASK", value, static_cast<DWORD>(sizeof(value)));
            }
            s_cached = (len > 0 && len < sizeof(value) && value[0] != '0') ? 1 : 0;
        }
        return s_cached != 0;
    }

    static bool EnvFlagEnabledByName(const char* name);
    static bool ShouldEnableChunkExperiments() {
        static int s_cached = -1;
        if (s_cached < 0) {
            if (EnvFlagEnabledByName("OPENSHIM_DISABLE_CHUNK_EXPERIMENTS") || EnvFlagEnabledByName("BZR_DISABLE_CHUNK_EXPERIMENTS")) s_cached = 0;
            else s_cached = 1;
        }
        return s_cached != 0;
    }

    // Redux creates the streaming music buffer with dwFlags 0x10188 --
    // LOCSOFTWARE | CTRLVOLUME | CTRLPOSITIONNOTIFY | GETCURRENTPOSITION2 --
    // and neither DSBCAPS_GLOBALFOCUS nor DSBCAPS_STICKYFOCUS. DirectSound
    // therefore stops the buffer whenever the game is not the foreground
    // window. That alone would only mute it, but the refill runs off play
    // position notifications: a stopped buffer's play cursor does not advance,
    // no notification fires, and the streaming thread blocks in
    // MsgWaitForMultipleObjects(INFINITE) without decoding. When focus returns
    // the ring is replayed while the thread catches up, so the music keeps
    // sounding but skips -- and anything that takes focus briefly (an overlay,
    // a notification toast) does the same thing for a shorter moment.
    //
    // Adding GLOBALFOCUS keeps the buffer playing across focus changes, which
    // keeps the notifications coming and the decoder fed.
    static bool ShouldEnableMusicBufferGlobalFocus() {
        static int s_cached = -1;
        if (s_cached < 0) {
            if (EnvFlagEnabledByName("OPENSHIM_DISABLE_MUSIC_GLOBAL_FOCUS")) s_cached = 0;
            else s_cached = 1;
        }
        return s_cached != 0;
    }

    static bool ShouldEnableProducerBuildMenuExperiment() {
        static int s_cached = -1;
        if (s_cached < 0) {
            s_cached = EnvFlagEnabledByName("OPENSHIM_ENABLE_PRODUCER_BUILD_MENU") || EnvFlagEnabledByName("OPENSHIM_ENABLE_PRODUCER_BUILD_MENU_EXPERIMENT") || EnvFlagEnabledByName("BZR_ENABLE_PRODUCER_BUILD_MENU") ? 1 : 0;
        }
        return s_cached != 0;
    }

    static bool ShouldEnableLobbyBzrnetIntegration(bool isSteam) {
        static int s_cachedSteam = -1; static int s_cachedGog = -1;
        int& cache = isSteam ? s_cachedSteam : s_cachedGog;
        if (cache >= 0) return cache != 0;
        if (EnvFlagEnabledByName("OPENSHIM_DISABLE_LOBBY_BZRNET_INTEGRATION") || EnvFlagEnabledByName("BZR_DISABLE_LOBBY_BZRNET_INTEGRATION")) { cache = 0; return false; }
        if (EnvFlagEnabledByName("OPENSHIM_ENABLE_LOBBY_BZRNET_INTEGRATION") || EnvFlagEnabledByName("OPENSHIM_ENABLE_LOBBY_UI_BZRNET") || EnvFlagEnabledByName("BZR_ENABLE_LOBBY_BZRNET_INTEGRATION")) { cache = 1; return true; }
        cache = isSteam ? 0 : 1;
        return cache != 0;
    }

    static bool EnvFlagEnabledByName(const char* name) {
        if (!name || !*name) return false;
        char value[8] = {};
        const DWORD len = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
        return (len > 0 && len < sizeof(value) && value[0] != '0');
    }

    static bool ShouldEnableMapRefreshFixes(bool isSteam) {
        static int s_cachedSteam = -1; static int s_cachedGog = -1;
        int& cache = isSteam ? s_cachedSteam : s_cachedGog;
        if (cache >= 0) return cache != 0;
        if (EnvFlagEnabledByName("OPENSHIM_DISABLE_MAP_REFRESH_FIXES") || EnvFlagEnabledByName("BZR_DISABLE_MAP_REFRESH_FIXES")) { cache = 0; return false; }
        cache = 1; return true;
    }

    // [Fixes] VehicleListModScoping. Forces mod-scoped asset resolution for the
    // multiplayer vehicle list. Default on, but it is the one always-on fix that
    // changes which assets a client resolves, so a modded lobby mixing shim and
    // stock clients needs to be able to turn it off and compare.
    static bool ShouldEnableVehicleListModScoping() {
        static int s_cached = -1;
        if (s_cached >= 0) return s_cached != 0;
        if (EnvFlagEnabledByName("OPENSHIM_DISABLE_VEHICLE_LIST_MOD_SCOPING") || EnvFlagEnabledByName("BZR_DISABLE_VEHICLE_LIST_MOD_SCOPING")) { s_cached = 0; return false; }
        s_cached = 1; return true;
    }

    static bool IsMapRefreshPatchName(const char* name) {
        if (!name) return false;
        return strcmp(name, "Map Sorting") == 0 || strcmp(name, "Map List Rewrite for Hop-Fix 1/3") == 0 || strcmp(name, "Map List Rewrite for Hop-Fix 2/3") == 0 || strcmp(name, "Map List Rewrite for Hop-Fix 3/3") == 0 || strcmp(name, "Map List Fix Support 1/3") == 0;
    }

    // Declarative gating lives in scripts/patches.json ("platforms": ["steam"]),
    // applied by FilterPatchesForDistribution. This name list is kept as a
    // fail-safe for a deployed patches.json that predates that metadata: a
    // Steam-only rewrite applied to a GOG executable would patch the wrong
    // bytes, so both gates must agree before these survive on GOG.
    static bool IsSteamOnlyPatchName(const char* name) {
        if (!name) return false;
        return strcmp(name, "Map List Rewrite for Hop-Fix 1/3") == 0 ||
               strcmp(name, "Map List Rewrite for Hop-Fix 2/3") == 0 ||
               strcmp(name, "Map List Rewrite for Hop-Fix 3/3") == 0;
    }

    // Only "Chunk Render Resolve Hook" is a chunk experiment. Its hook body
    // early-returns unless a chunk flag is set, and it drives nothing else.
    //
    // The other two vtable hooks used to be listed here, and that was wrong.
    // Both grew into general per-tick drivers for work that has nothing to do
    // with chunks:
    //
    //   LegacyWorldUpdateRenderQueueHook (per rendered frame)
    //     RefreshHeadlightState, RefreshPilotFlashlightState,
    //     TickMpGateReconcile, TickOpenShimEventLayer,
    //     RefreshVehicleSkinningDiagnosticsIfNeeded
    //
    //   ChunkEffectSimulateHook (per sim tick)
    //     TickMpGateReconcile (secondary), MaybeDriveMultiplayerFlagRenderFallback,
    //     OgreShaderCacheTick, SyncSatelliteVisibility,
    //     MaybeSuppressStaleHopOutAttackAlert, the UiPerf heartbeat, and the
    //     deferred installs for mpauth, radar layout, career-stats MP and the
    //     jump-snipe probe
    //
    // The shipped default is [General] ChunkMeshes = 0, which this gate maps to
    // OPENSHIM_DISABLE_CHUNK_EXPERIMENTS, so on a default install every one of
    // those was dead -- silently, because a filtered patch produces no [SKIP]
    // line. Neither hook needs the chunk features: their chunk-side calls
    // (TickChunkProxyDebug, TrackChunkEffectActiveEntries,
    // LogChunkEffectRuntimeSample, the batching branch) all early-return on the
    // same flags, so with chunks off each hook costs one call-through plus a few
    // boolean tests.
    static bool IsChunkExperimentPatchName(const char* name) {
        if (!name) return false;
        return strcmp(name, "Chunk Render Resolve Hook") == 0;
    }

    static bool IsProducerBuildMenuExperimentPatchName(const char* name) { return name && strcmp(name, "Producer Build Menu Root Hook") == 0; }

    static bool IsMusicBufferGlobalFocusPatchName(const char* name) { return name && strcmp(name, "Music Buffer Global Focus") == 0; }

    static bool IsLobbyBzrnetIntegrationPatchName(const char* name) {
        if (!name) return false;
        return strcmp(name, "Lobby BZRNET Integration HOST") == 0 || strcmp(name, "Lobby BZRNET Integration CLIENT") == 0;
    }

    static bool IsBanFeaturePatchName(const char* name) {
        if (!name) return false;
        return strcmp(name, "Custom Command /help Handler") == 0 ||
               strcmp(name, "Joiner Event Hook") == 0 ||
               strcmp(name, "Ban Button Hook 1/2") == 0 ||
               strcmp(name, "Ban Button Hook 2/2") == 0;
    }

    static bool IsVehicleListModFixPatchName(const char* name) {
        return name && strncmp(name, "Vehicle List Mod Fix ", 21) == 0;
    }

    static const char* DistributionConfigKey(BzrDistribution distribution) {
        switch (distribution) {
        case BzrDistribution::GOG: return "gog";
        case BzrDistribution::Steam: return "steam";
        default: return nullptr;
        }
    }

    static bool ConfigNodeAllowsDistribution(const nlohmann::json& node, BzrDistribution distribution) {
        if (!node.contains("platforms")) return true;
        if (!node["platforms"].is_array()) return false;
        const char* key = DistributionConfigKey(distribution);
        if (!key) return false;
        for (const auto& platform : node["platforms"]) {
            if (platform.is_string() && platform.get<std::string>() == key) return true;
        }
        return false;
    }

    static bool PatchAllowsDistribution(const HookEngine::PatchDef& patch, BzrDistribution distribution) {
        static const char* groups[] = { "patches", "globals" };
        for (const char* group : groups) {
            if (!g_Config.data.contains(group) || !g_Config.data[group].is_array()) continue;
            for (const auto& node : g_Config.data[group]) {
                if (!node.contains("name") || !node["name"].is_string()) continue;
                if (node["name"].get<std::string>() == patch.name)
                    return ConfigNodeAllowsDistribution(node, distribution);
            }
        }
        return true;
    }

    static void FilterPatchesForDistribution(std::vector<HookEngine::PatchDef>& patches, BzrDistribution distribution) {
        patches.erase(std::remove_if(patches.begin(), patches.end(), [distribution](const HookEngine::PatchDef& patch) {
            return !PatchAllowsDistribution(patch, distribution);
        }), patches.end());
    }

    static bool ShouldEnableOgreMaterialCollisionGuard() {
        static int s_cached = -1;
        if (s_cached < 0) {
            if (EnvFlagEnabledByName("OPENSHIM_DISABLE_OGRE_MATERIAL_COLLISION_GUARD") ||
                EnvFlagEnabledByName("BZR_DISABLE_OGRE_MATERIAL_COLLISION_GUARD")) {
                s_cached = 0;
            } else if (EnvFlagEnabledByName("OPENSHIM_ENABLE_OGRE_MATERIAL_COLLISION_GUARD") ||
                       EnvFlagEnabledByName("BZR_ENABLE_OGRE_MATERIAL_COLLISION_GUARD")) {
                s_cached = 1;
            } else {
                // Duplicate material declarations otherwise escape Ogre's script
                // loader as ERR_DUPLICATE_ITEM and terminate the game. Keep the
                // guard on even if patches.json is missing; the disable variables
                // above remain an emergency compatibility escape hatch.
                s_cached = g_Config.GetBool("ogre_material_collision_guard", true) ? 1 : 0;
            }
        }
        return s_cached != 0;
    }

    static void FilterPatchesForRuntime(std::vector<HookEngine::PatchDef>& patches, BzrDistribution distribution) {
        const bool isSteam = distribution == BzrDistribution::Steam;
        if (!isSteam) {
            patches.erase(std::remove_if(patches.begin(), patches.end(), [](const HookEngine::PatchDef& p) { return IsSteamOnlyPatchName(p.name.c_str()); }), patches.end());
        }
        if (!ShouldEnableMapRefreshFixes(isSteam)) {
            patches.erase(std::remove_if(patches.begin(), patches.end(), [](const HookEngine::PatchDef& p) { return IsMapRefreshPatchName(p.name.c_str()); }), patches.end());
        }
        if (!ShouldEnableVehicleListModScoping()) {
            patches.erase(std::remove_if(patches.begin(), patches.end(), [](const HookEngine::PatchDef& p) { return IsVehicleListModFixPatchName(p.name.c_str()); }), patches.end());
        }
        if (!ShouldEnableChunkExperiments()) {
            patches.erase(std::remove_if(patches.begin(), patches.end(), [](const HookEngine::PatchDef& p) { return IsChunkExperimentPatchName(p.name.c_str()); }), patches.end());
        }
        if (!ShouldEnableProducerBuildMenuExperiment()) {
            patches.erase(std::remove_if(patches.begin(), patches.end(), [](const HookEngine::PatchDef& p) { return IsProducerBuildMenuExperimentPatchName(p.name.c_str()); }), patches.end());
        }
        if (!ShouldEnableLobbyBzrnetIntegration(isSteam)) {
            patches.erase(std::remove_if(patches.begin(), patches.end(), [](const HookEngine::PatchDef& p) { return IsLobbyBzrnetIntegrationPatchName(p.name.c_str()); }), patches.end());
        }
        if (!ShouldEnableMusicBufferGlobalFocus()) {
            patches.erase(std::remove_if(patches.begin(), patches.end(), [](const HookEngine::PatchDef& p) { return IsMusicBufferGlobalFocusPatchName(p.name.c_str()); }), patches.end());
        }
    }

    static SoundChannelOverrideConfig GetSoundChannelOverrideConfig() {
        static bool s_init = false; static SoundChannelOverrideConfig s_config = {};
        if (s_init) return s_config;
        s_init = true; s_config.enabled = true; s_config.requestedChannels = kDefaultMaxSoundChannels; s_config.maxChannels = kDefaultMaxSoundChannels;

        char exePath[MAX_PATH] = {};
        const DWORD exePathLen = GetModuleFileNameA(nullptr, exePath, MAX_PATH);
        if (exePathLen > 0 && exePathLen < MAX_PATH) {
            char* slash = strrchr(exePath, '\\');
            if (slash) {
                *(slash + 1) = '\0';
                strcat_s(exePath, "openshim.ini");
                static constexpr char kUnset[] = "\x01__openshim_unset__";
                char iniValue[32] = {};
                GetPrivateProfileStringA("General", "SoundChannels", kUnset, iniValue,
                    static_cast<DWORD>(sizeof(iniValue)), exePath);
                if (strcmp(iniValue, kUnset) != 0 && iniValue[0] != '\0') {
                    s_config.iniOverride = true;
                    char* end = nullptr;
                    const unsigned long parsed = strtoul(iniValue, &end, 10);
                    if (end == iniValue || *end != '\0') {
                        s_config.iniInvalid = true;
                    } else {
                        s_config.requestedChannels = static_cast<uint32_t>(parsed);
                        if (s_config.requestedChannels == 0) {
                            s_config.enabled = false;
                            s_config.maxChannels = 0;
                        } else {
                            s_config.enabled = true;
                            s_config.maxChannels = (std::min)(s_config.requestedChannels, kMaxSupportedSoundChannels);
                        }
                    }
                }
            }
        }

        const char* envNames[] = { "OPENSHIM_MAX_SOUND_CHANNELS", "BZR_MAX_SOUND_CHANNELS" };
        for (const char* envName : envNames) {
            char value[32] = {};
            const DWORD len = GetEnvironmentVariableA(envName, value, static_cast<DWORD>(sizeof(value)));
            if (!(len > 0 && len < sizeof(value))) continue;
            s_config.envOverride = true; s_config.sourceEnv = envName;
            char* end = nullptr; const unsigned long parsed = strtoul(value, &end, 10);
            if (end == value || *end != '\0') { s_config.envInvalid = true; return s_config; }
            s_config.requestedChannels = static_cast<uint32_t>(parsed);
            if (s_config.requestedChannels == 0) { s_config.enabled = false; s_config.maxChannels = 0; return s_config; }
            s_config.enabled = true;
            s_config.maxChannels = s_config.requestedChannels;
            if (s_config.maxChannels > kMaxSupportedSoundChannels) { s_config.maxChannels = kMaxSupportedSoundChannels; s_config.envClamped = true; }
            return s_config;
        }
        return s_config;
    }

    static void WriteZeroGuarded(uintptr_t addr) {
        __try { auto* flag = reinterpret_cast<volatile uint32_t*>(addr); *flag = 0; }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }

    static void SuppressStartupShellAutoLoad() {
        const uintptr_t kAddr = g_Config.GetStaticPointer("StartupShellAutoLoadFlag", 0x008EAAA8);
        if (!ShouldSuppressStartupAutoLoad()) return;
        WriteZeroGuarded(kAddr);
    }

    static bool ScanForSoundChannelOverrideTargets(SoundChannelOverrideTargets& outTargets) {
        outTargets = {}; if (!g_Config.data.contains("audio_gas_pattern")) return false;
        auto pVec = HookEngine::ParseIdaPattern(g_Config.data["audio_gas_pattern"]["pattern"]);
        // An unparseable pattern yields an empty vector, which would otherwise
        // "match" at the first byte of the first region.
        if (pVec.empty()) return false;
        HMODULE hMain = GetModuleHandleA(nullptr); uint8_t* mainBase = reinterpret_cast<uint8_t*>(hMain);
        size_t mainSize = 0; if (hMain) {
            auto dos = reinterpret_cast<IMAGE_DOS_HEADER*>(hMain);
            if (dos->e_magic == IMAGE_DOS_SIGNATURE) {
                auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<uint8_t*>(hMain) + dos->e_lfanew);
                if (nt->Signature == IMAGE_NT_SIGNATURE) mainSize = nt->OptionalHeader.SizeOfImage;
            }
        }
        if (!mainBase || !mainSize) return false;
        HANDLE hProc = GetCurrentProcess(); MEMORY_BASIC_INFORMATION mbi = {}; uint8_t* addr = mainBase;
        while (addr < (mainBase + mainSize) && VirtualQuery(addr, &mbi, sizeof(mbi)) == sizeof(mbi)) {
            uint8_t* rBase = reinterpret_cast<uint8_t*>(mbi.BaseAddress); uint8_t* rEnd = rBase + mbi.RegionSize;
            if (rEnd <= mainBase || rBase >= (mainBase + mainSize)) { addr = rEnd; continue; }
            if (mbi.State != MEM_COMMIT || !(mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY))) { addr = rEnd; continue; }
            uint8_t* clipStart = (rBase < mainBase) ? mainBase : rBase; uint8_t* clipEnd = (rEnd > (mainBase + mainSize)) ? (mainBase + mainSize) : rEnd;
            const size_t clipSize = static_cast<size_t>(clipEnd - clipStart); if (clipSize < pVec.size()) { addr = rEnd; continue; }
            std::vector<uint8_t> buffer(clipSize); SIZE_T read = 0;
            if (!ReadProcessMemory(hProc, clipStart, buffer.data(), clipSize, &read) || read < pVec.size()) { addr = rEnd; continue; }
            for (size_t i = 0; i <= read - pVec.size(); ++i) {
                bool match = true; for (size_t j = 0; j < pVec.size(); ++j) { if (pVec[j] < 0x100 && buffer[i + j] != static_cast<uint8_t>(pVec[j])) { match = false; break; } }
                if (!match) continue;
                uint32_t gasA = 0; uint32_t gasB = 0; uint32_t gasC = 0; uint32_t gmS = 0;
                memcpy(&gasA, &buffer[i + 26], 4); memcpy(&gmS, &buffer[i + 48], 4); memcpy(&gasB, &buffer[i + 52], 4); memcpy(&gasC, &buffer[i + 57], 4);
                if (gasA == 0 || gmS == 0 || gasA != gasB || gasA != gasC) continue;
                outTargets.gmStorageAddress = gmS; outTargets.gasMasterAddress = gasA; outTargets.initSiteAddress = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(clipStart + i));
                return true;
            }
            addr = rEnd;
        }
        return false;
    }

    static bool ResolveSoundChannelOverrideTargets(bool isSteam, SoundChannelOverrideTargets& outTargets) {
        if (ScanForSoundChannelOverrideTargets(outTargets)) return true;
        outTargets.gmStorageAddress = g_Config.GetStaticPointer("GAS_GMStorage", 0x00915594);
        outTargets.gasMasterAddress = g_Config.GetStaticPointer("GAS_Master", 0x0091559C);
        return true;
    }

    static DWORD WINAPI SoundChannelOverrideThreadProc(LPVOID param) {
        SoundChannelOverrideThreadContext context = {};
        SoundChannelOverrideThreadContext* heapContext = reinterpret_cast<SoundChannelOverrideThreadContext*>(param);
        if (heapContext) { context = *heapContext; delete heapContext; }
        HANDLE hProc = GetCurrentProcess();
        while (!g_ShutdownRequested) {
            uint32_t gmPtr = 0; SIZE_T r = 0;
            if (ReadProcessMemory(hProc, reinterpret_cast<LPCVOID>(context.gmStorageAddress), &gmPtr, 4, &r) && r == 4) {
                const uint32_t base = (gmPtr != 0) ? gmPtr : context.gasMasterAddress;
                if (base != 0) {
                    uint32_t cur = 0; if (ReadProcessMemory(hProc, reinterpret_cast<LPCVOID>(base + kGASMasterMaxObjectsOffset), &cur, 4, &r) && cur != context.maxChannels) {
                        WriteProcessMemory(hProc, reinterpret_cast<LPVOID>(base + kGASMasterMaxObjectsOffset), &context.maxChannels, 4, &r);
                    }
                }
            }
            Sleep(kSoundChannelRefreshDelayMs);
        }
        return 0;
    }

    static void StartSoundChannelOverride(bool isSteam) {
        const auto config = GetSoundChannelOverrideConfig();
        Log(L"[SOUND] channels requested=%u applied=%u source=%hs enabled=%hs%s%s\n",
            config.requestedChannels,
            config.maxChannels,
            config.envOverride ? (config.sourceEnv ? config.sourceEnv : "environment") :
                (config.iniOverride ? "openshim.ini" : "default"),
            config.enabled ? "yes" : "no",
            config.envInvalid || config.iniInvalid ? " invalid-value" : "",
            config.envClamped || config.requestedChannels > kMaxSupportedSoundChannels ? " clamped" : "");
        if (!config.enabled) return;
        SoundChannelOverrideTargets targets = {}; if (!ResolveSoundChannelOverrideTargets(isSteam, targets)) return;
        auto* ctx = new (std::nothrow) SoundChannelOverrideThreadContext(); if (!ctx) return;
        ctx->gmStorageAddress = targets.gmStorageAddress; ctx->gasMasterAddress = targets.gasMasterAddress; ctx->maxChannels = config.maxChannels;
        HANDLE h = CreateThread(nullptr, 0, SoundChannelOverrideThreadProc, ctx, 0, nullptr);
        if (h) CloseHandle(h); else delete ctx;
    }

    // Routed through the structured shim logger (openshim.log). The old
    // private winmm_shim.log wide stream silently dropped every line once a
    // conversion failure latched the stream error flag, which hid all patch
    // and hook diagnostics.
    void Log(const wchar_t* fmt, ...) {
        va_list args; va_start(args, fmt);
        LogShimVW(LogLevel::Info, "patcher", fmt, args);
        va_end(args);
    }

    extern "C" void LogHit(const char* name) {
        static volatile long s_budget = 100;
        if (ShouldLogHookHits() && InterlockedDecrement(&s_budget) >= 0) Log(L"[HIT]  %hs\n", name);
    }

    static bool IsSteamExe() {
        // GOG and Steam both ship battlezone98redux.exe, so the name cannot
        // distinguish them. The Steam build is SteamStub-packed and carries a
        // ".bind" PE section - the exact property the Steam settled-byte
        // waits exist for - while the GOG build has none.
        const uint8_t* base = reinterpret_cast<const uint8_t*>(GetModuleHandleA(nullptr));
        if (!base) return false;
        const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE) return false;
        const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(base + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE) return false;
        const IMAGE_SECTION_HEADER* sect = IMAGE_FIRST_SECTION(nt);
        static const uint8_t kBindName[IMAGE_SIZEOF_SHORT_NAME] = { '.', 'b', 'i', 'n', 'd', 0, 0, 0 };
        for (WORD i = 0; i < nt->FileHeader.NumberOfSections; ++i) {
            if (memcmp(sect[i].Name, kBindName, IMAGE_SIZEOF_SHORT_NAME) == 0) return true;
        }
        return false;
    }

    static uint32_t GetBZRVersion() {
        char path[MAX_PATH] = {}; GetModuleFileNameA(nullptr, path, MAX_PATH);
        DWORD d = 0; DWORD sz = GetFileVersionInfoSizeA(path, &d); if (sz == 0) return 0xFFFFFFFF;
        std::vector<uint8_t> buf(sz); if (!GetFileVersionInfoA(path, 0, sz, buf.data())) return 0xFFFFFFFF;
        VS_FIXEDFILEINFO* ffi = nullptr; UINT fl = 0;
        if (!VerQueryValueA(buf.data(), "\\", reinterpret_cast<LPVOID*>(&ffi), &fl) || !ffi) return 0xFFFFFFFF;
        uint32_t ver = static_cast<uint32_t>(LOWORD(ffi->dwFileVersionLS));
        if (ver == 0) ver = static_cast<uint32_t>(HIWORD(ffi->dwFileVersionLS));
        return ver;
    }

    static bool BytesMatchAt(uint32_t address, const uint8_t* expected, size_t len) {
        std::vector<uint8_t> buf(len); SIZE_T r = 0;
        return ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(address), buf.data(), len, &r) && memcmp(buf.data(), expected, len) == 0;
    }

    static bool ReadExeSignature(std::vector<uint8_t>& outSig) {
        char path[MAX_PATH] = {}; GetModuleFileNameA(nullptr, path, MAX_PATH);
        HANDLE h = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, 0, nullptr);
        if (h == INVALID_HANDLE_VALUE) return false;
        IMAGE_DOS_HEADER dos; DWORD r; ReadFile(h, &dos, sizeof(dos), &r, nullptr);
        IMAGE_NT_HEADERS32 nt; SetFilePointer(h, dos.e_lfanew, nullptr, FILE_BEGIN); ReadFile(h, &nt, sizeof(nt), &r, nullptr);
        uint32_t sigVA = g_Config.GetStaticPointer("BZR_SIGNATURE_ADDR", DEFAULT_BZR_SIGNATURE_ADDR);
        uint32_t sigRVA = sigVA - nt.OptionalHeader.ImageBase;
        std::vector<IMAGE_SECTION_HEADER> sects(nt.FileHeader.NumberOfSections);
        ReadFile(h, sects.data(), sects.size()*sizeof(IMAGE_SECTION_HEADER), &r, nullptr);
        for (const auto& s : sects) {
            if (sigRVA >= s.VirtualAddress && sigRVA < s.VirtualAddress + s.Misc.VirtualSize) {
                SetFilePointer(h, s.PointerToRawData + (sigRVA - s.VirtualAddress), nullptr, FILE_BEGIN);
                outSig.resize(256); ReadFile(h, outSig.data(), 256, &r, nullptr); CloseHandle(h); return true;
            }
        }
        CloseHandle(h); return false;
    }

    static bool WaitForSignature(const std::vector<uint8_t>& sig) {
        if (sig.empty()) return true;
        uint32_t addr = g_Config.GetStaticPointer("BZR_SIGNATURE_ADDR", DEFAULT_BZR_SIGNATURE_ADDR);
        for (int i = 0; i < PATCH_MAX_RETRIES; ++i) {
            if (g_ShutdownRequested) return false;
            if (BytesMatchAt(addr, sig.data(), sig.size())) return true;
            Sleep(PATCH_RETRY_DELAY_MS);
        }
        return false;
    }

    // Steam decrypts .text lazily, so a single read of a call opcode can come
    // back as ciphertext and resolve to null - permanently, because nothing
    // retried. Retry briefly, then fall back to the address for the build we
    // already version-gated on in RunPatcher.
    static void* ResolveCallTargetWithFallback(uint32_t instrAddr, bool isSteam, const char* cfgName, uint32_t fallback, const char* label) {
        void* target = isSteam ? HookEngine::ResolveRelCallTargetWithRetry(instrAddr, 100, 5) : HookEngine::ResolveRelCallTarget(instrAddr);
        if (target) return target;
        const uint32_t fb = g_Config.GetStaticPointer(cfgName, fallback);
        Log(L"[WARN] %hs call target unresolved at 0x%08X; using fallback 0x%08X\n", label, instrAddr, fb);
        return reinterpret_cast<void*>(fb);
    }

    static void ResolvePointers(uint32_t mapS, uint32_t h1, uint32_t h2, uint32_t h3, uint32_t pF1, uint32_t pL1, uint32_t pL2, uint32_t tc, uint32_t tt, uint32_t ua1, uint32_t ua2, uint32_t oa, uint32_t tta, bool isSteam) {
        if (h1) { g_RetAddr_HopFix1 = reinterpret_cast<void*>(h1 + g_Config.GetStaticPointer("RetAddr_HopFix1_Offset", 0x0E)); g_BZRFnPtr_HopFix1 = reinterpret_cast<void(*)()>(ResolveCallTargetWithFallback(h1 + 9, isSteam, "HopFix1Call_Fallback", 0x005D4260, "Hop-Fix 1")); }
        if (h2) {
            g_RetAddr_HopFix2 = reinterpret_cast<void*>(h2 + g_Config.GetStaticPointer("RetAddr_HopFix2_Offset", 0x13));
            // Record the site and fallback so RestoreMapListSelection can
            // re-derive the select target later if this resolve still fails;
            // a null there means the replaced select(0) never runs and the
            // engine faults on the unselected list.
            g_HopFix2SelectCallSite = h2 + 0x0E;
            g_HopFix2SelectFallback = g_Config.GetStaticPointer("HopFix2Select_Fallback", 0x007CAFA0);
            g_BZRFnPtr_HopFix2 = reinterpret_cast<void(*)()>(ResolveCallTargetWithFallback(h2 + 0x0E, isSteam, "HopFix2Select_Fallback", 0x007CAFA0, "Hop-Fix 2 select"));
            g_MapListObject = reinterpret_cast<void**>(g_Config.GetStaticPointer("MapListObject", 0x0094555C));
        }
        if (h3) g_RetAddr_HopFix3 = reinterpret_cast<void*>(h3 + g_Config.GetStaticPointer("RetAddr_HopFix3_Offset", 0x07));
        g_BZRFnPtr_HopFix3Step = reinterpret_cast<void(*)()>(g_Config.GetStaticPointer("HopFix3Step_Fallback", 0x007A3130));
        if (mapS) g_RetAddr_Probe_MapSorting = reinterpret_cast<void*>(mapS + g_Config.GetStaticPointer("RetAddr_HopFix3_Offset", 0x07));
        if (pF1) g_RetAddr_Probe_MapFilter1 = reinterpret_cast<void*>(pF1 + g_Config.GetStaticPointer("RetAddr_Probe_MapFilter1_Offset", 0x05));
        if (pL1) { g_RetAddr_MapListFixSupport1 = reinterpret_cast<void*>(pL1 + g_Config.GetStaticPointer("RetAddr_MapListFixSupport1_Offset", 0x15)); g_BZRFn_MapListFixSupport1 = reinterpret_cast<void(*)()>(g_Config.GetStaticPointer("MapListFixSupport1_Fallback", 0x007A3BD0)); }
        if (pL2) g_RetAddr_Probe_MapListFix2 = reinterpret_cast<void*>(pL2 + g_Config.GetStaticPointer("RetAddr_Probe_MapFilter1_Offset", 0x05));
        if (tc) g_RetAddr_TurretCraftAimPitchMultiplier = reinterpret_cast<void*>(tc + g_Config.GetStaticPointer("RetAddr_TurretCraft_Offset", 0x08));
        if (tt) g_RetAddr_TurretTankAimPitchMultiplier = reinterpret_cast<void*>(tt + g_Config.GetStaticPointer("RetAddr_TurretCraft_Offset", 0x08));
        if (ua1) g_RetAddr_UnderAttackAlertHook1 = reinterpret_cast<void*>(ua1 + g_Config.GetStaticPointer("RetAddr_UnderAttack1_Offset", 0x34));
        if (ua2) g_RetAddr_UnderAttackAlertHook2 = reinterpret_cast<void*>(ua2 + g_Config.GetStaticPointer("RetAddr_UnderAttack1_Offset", 0x34));
        if (oa) g_RetAddr_OffensiveAttackRevealHook = reinterpret_cast<void*>(oa + g_Config.GetStaticPointer("RetAddr_OffensiveAttack_Offset", 0x0C));
        if (tta) g_RetAddr_TurretTankAttackRevealHook = reinterpret_cast<void*>(tta + g_Config.GetStaticPointer("RetAddr_OffensiveAttack_Offset", 0x0C));
        // 0x007D3360 is a validated GOG cUI helper, but the same address in the
        // settled Steam image has different context requirements.  Publishing
        // it on Steam lets the GOG-specific Map Sorting frame probe reach the
        // function with a plausible-but-invalid UI object and raise an access
        // violation during frontend startup.  All consumers already treat a
        // null getter as "scroll state unavailable" and retain the validated
        // HopFix3 frame delta, so fail closed until a Steam identity and ABI are
        // recovered independently.
        g_EnableScrollRestore = !isSteam;
        g_BZRFn_GetScrollState = isSteam
            ? nullptr
            : reinterpret_cast<uint32_t(*)()>(g_Config.GetStaticPointer("GetScrollState", 0x007D3360));
        if (isSteam)
            Log(L"[REFRESH] Steam scroll-state capture disabled; using HopFix3 frame delta\n");
        g_BZRFn_ScrollUp = reinterpret_cast<void(*)()>(g_Config.GetStaticPointer("ScrollUp", 0x007CB500));
        g_BZRFn_ScrollDown = reinterpret_cast<void(*)()>(g_Config.GetStaticPointer("ScrollDown", 0x007CB540));
    }

    static void ResolveStaticReturnPointers() {
        auto ptr = [](const char* name, uint32_t fallback) -> void* {
            return reinterpret_cast<void*>(g_Config.GetStaticPointer(name, fallback));
        };

        g_RetAddr_MapFilters1 = ptr("RetAddr_MapFilters1", 0x007A35C0);
        g_RetAddr_MapFilters2 = ptr("RetAddr_MapFilters2", 0x00752D00);
        g_RetAddr_MapFilters3 = ptr("RetAddr_MapFilters3", 0x0079D6B9);
        g_RetAddr_MapFilters4 = ptr("RetAddr_MapFilters4", 0x0079D699);
        g_RetAddr_MapFilters5 = ptr("RetAddr_MapFilters5", 0x0079916B);
        g_RetAddr_MapFilters7 = ptr("RetAddr_MapFilters7", 0x007998B4);
        g_RetAddr_MapFilters8_A = ptr("RetAddr_MapFilters8_A", 0x007997B2);
        g_RetAddr_MapFilters8_B = ptr("RetAddr_MapFilters8_B", 0x007997B7);
        g_RetAddr_MapFilters8_C = ptr("RetAddr_MapFilters8_C", 0x0079987C);
        g_RetAddr_VehicleListModFix1 = ptr("RetAddr_VehicleListModFix1", 0x00766C52);
        g_RetAddr_VehicleListModFix4 = ptr("RetAddr_VehicleListModFix4", 0x00798BE6);
        g_RetAddr_BzrnetHost = ptr("RetAddr_BzrnetHost", 0x00743C30);
        g_RetAddr_BzrnetClient = ptr("RetAddr_BzrnetClient", 0x0073E748);
        g_RetAddr_CommandHelpHandled = ptr("RetAddr_CommandHelpHandled", 0x00625052);
        g_RetAddr_CommandHelpFallback = ptr("RetAddr_CommandHelpFallback", 0x0062491F);
        g_RetAddr_JoinerEventHook = ptr("RetAddr_JoinerEventHook", 0x0073F435);
        g_RetAddr_BanHook1 = ptr("RetAddr_BanHook1", 0x007D0A35);
        g_RetAddr_BanHook2 = ptr("RetAddr_BanHook2", 0x007A691A);
        g_RetAddr_AutoSaveLoadHook = ptr("RetAddr_AutoSaveLoadHook", 0x0078B45F);
        g_BZRFnPtr_JoinerEventOriginal = reinterpret_cast<void(*)()>(
            g_Config.GetStaticPointer("JoinerEventOriginal", 0x00742560));
    }

    static void ScanForPatchAddresses(
        std::vector<HookEngine::PatchDef>& patches,
        bool isSteam,
        bool compatibilityOnly = false) {
        std::vector<HookEngine::ScanTarget> targets;
        try {
            if (g_Config.data.contains("patches")) {
                for (const auto& p : g_Config.data["patches"]) {
                    const std::string name = p["name"].get<std::string>();
                    // Two independent skips: the compatibility-only pass scans
                    // just the Redux compatibility group, and no pass ever
                    // scans a pattern whose patch the distribution/runtime
                    // filters already dropped from the list.
                    if (compatibilityOnly && !IsReduxCompatibilityPatchName(name.c_str())) continue;
                    const bool active = std::any_of(patches.begin(), patches.end(), [&name](const HookEngine::PatchDef& patch) {
                        return patch.name == name;
                    });
                    if (!active) continue;
                    HookEngine::ScanTarget t; t.name = name; t.ida_pattern = p["pattern"]; t.offset = p["offset"]; t.expected_size = p["expected_size"]; t.fallback_addr = std::stoul(p["fallback"].get<std::string>(), nullptr, 16); t.require_unique = p.value("require_unique", false); targets.push_back(t);
                }
            }
            if (!compatibilityOnly && g_Config.data.contains("globals")) {
                for (const auto& g : g_Config.data["globals"]) {
                    uint32_t fb = 0; if (isSteam && g.contains("fallback_steam")) fb = std::stoul(g["fallback_steam"].get<std::string>(), nullptr, 16);
                    else if (!isSteam && g.contains("fallback_gog")) fb = std::stoul(g["fallback_gog"].get<std::string>(), nullptr, 16);
                    if (fb == 0 && g.contains("fallback")) fb = std::stoul(g["fallback"].get<std::string>(), nullptr, 16);
                    auto expVec = HookEngine::ParseIdaPattern(g["expected_original"]);
                    std::vector<uint8_t> exp; for (auto v : expVec) exp.push_back(static_cast<uint8_t>(v));
                    for (auto& p : patches) { if (p.name == g["name"].get<std::string>()) { p.address = fb; p.verified = (fb != 0); p.expected_original = exp; } }
                }
            }
        } catch (...) {}
        HookEngine::ScanForPatterns("", patches, targets);
        for (const auto& t : targets) {
            for (auto& p : patches) {
                if (!p.verified && p.name == t.name && !t.require_unique) {
                    p.address = t.fallback_addr; p.verified = true;
                    auto ida = HookEngine::ParseIdaPattern(t.ida_pattern);
                    if (t.expected_size > 0) { p.expected_original.clear(); for (size_t j = 0; j < t.expected_size && j < ida.size(); ++j) p.expected_original.push_back(static_cast<uint8_t>(ida[j])); }
                }
            }
        }
    }

    static void FillJmp5Payloads(std::vector<HookEngine::PatchDef>& patches) {
        struct M { const char* n; void* f; } m[] = {
            {"Map Sorting", (void*)Trampoline_Probe_MapSorting}, {"GameObject Handle Stale Slot Guard", (void*)GameObjectHandleGetObjHardened}, {"Map List Rewrite for Hop-Fix 1/3", (void*)Trampoline_HopFix1}, {"Map List Rewrite for Hop-Fix 2/3", (void*)Trampoline_HopFix2}, {"Map List Rewrite for Hop-Fix 3/3", (void*)Trampoline_HopFix3}, {"Map List Fix Support 1/3", (void*)Trampoline_MapListFixSupport1}, {"Probe Refresh Path MapFilter1", (void*)Trampoline_Probe_MapFilter1}, {"Probe MapListFix1", (void*)Trampoline_Probe_MapListFix1}, {"Probe MapListFix2", (void*)Trampoline_Probe_MapListFix2}, {"Map Filters 1/8", (void*)Trampoline_MapFilters1}, {"Map Filters 2/8", (void*)Trampoline_MapFilters2}, {"Map Filters 3/8", (void*)Trampoline_MapFilters3}, {"Map Filters 4/8", (void*)Trampoline_MapFilters4}, {"Map Filters 5/8", (void*)Trampoline_MapFilters5}, {"Map Filters 7/8", (void*)Trampoline_MapFilters7}, {"Map Filters 8/8", (void*)Trampoline_MapFilters8}, {"Vehicle List Mod Fix 1/4 (Force Mod-Scoped Assets 1/3)", (void*)Trampoline_VehicleListModFix1}, {"Vehicle List Mod Fix 4/4 (Force Mod-Scoped Assets 3/3)", (void*)Trampoline_VehicleListModFix4}, {"Lobby BZRNET Integration HOST", (void*)Trampoline_BzrnetHost}, {"Lobby BZRNET Integration CLIENT", (void*)Trampoline_BzrnetClient}, {"Custom Command /help Handler", (void*)Trampoline_CommandHelp}, {"Joiner Event Hook", (void*)Trampoline_JoinerEventHook}, {"Ban Button Hook 1/2", (void*)Trampoline_BanButtonHook1}, {"Ban Button Hook 2/2", (void*)Trampoline_BanButtonHook2}, {"AutoSave Load Button Hook", (void*)Trampoline_AutoSaveLoadButtonHook}, {"Restart Mission Hook Pause", (void*)Trampoline_RestartMissionPauseHook}, {"Restart Mission Hook Failure", (void*)Trampoline_RestartMissionFailureHook}, {"TurretCraft Aim Pitch Multiplier", (void*)Trampoline_TurretCraftAimPitchMultiplier}, {"TurretTank Aim Pitch Multiplier", (void*)Trampoline_TurretTankAimPitchMultiplier}, {"Under Attack Alert Hook 1/2", (void*)Trampoline_UnderAttackAlertHook1}, {"Under Attack Alert Hook 2/2", (void*)Trampoline_UnderAttackAlertHook2}, {"Offensive Attack Reveal Hook", (void*)Trampoline_OffensiveAttackRevealHook}, {"TurretTank Attack Reveal Hook", (void*)Trampoline_TurretTankAttackRevealHook}, {"Decoded Weapon Mask Carrier Bias Hook", (void*)Trampoline_DecodedWeaponMaskBias}, {"Raw Weapon Mask Carrier Bias Hook", (void*)Trampoline_RawWeaponMaskBias}
        };
        for (auto& p : patches) {
            if (p.type != HookEngine::PatchType::JMP5 || !p.verified) continue;
            for (auto& x : m) {
                if (p.name == x.n) {
                    size_t l = (p.name.find("Turret") != std::string::npos && p.name.find("Pitch") != std::string::npos) ? 8 : (p.name.find("Reveal") != std::string::npos ? 12 : (p.name.find("Volley") != std::string::npos ? 6 : (p.name.find("Attack Alert") != std::string::npos ? 52 : 5)));
                    p.payload = HookEngine::MakeJmp5Payload(p.address, static_cast<uint32_t>(reinterpret_cast<uintptr_t>(x.f)), l); break;
                }
            }
        }
    }

    static void FillRel32Payloads(std::vector<HookEngine::PatchDef>& patches, bool isSteam) {
        for (auto& p : patches) {
            if (p.type != HookEngine::PatchType::REL32 || !p.verified) continue;
            uint32_t target = 0;
            if (p.name.find("Vehicle List Mod Fix 2/4") != std::string::npos) target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(VehicleListModFix2));
            else if (p.name == "Map Filters 6/8") target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(MapFilters6Rel32));
            else if (p.name == "Chunk Render Resolve Hook") target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ChunkRenderResolveHook));
            else if (p.name == "Producer Build Menu Root Hook") {
                void* orig = isSteam ? HookEngine::ResolveRelCallTargetWithRetry(p.address - 1, 300, 10) : HookEngine::ResolveRelCallTarget(p.address - 1);
                if (!orig) continue; SetProducerBuildMenuOriginal(orig); target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ProducerBuildMenuCallHook));
            } else if (p.name == "Target Reticle Popup Recent-Hit Getter Hook") target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(TargetReticlePopupRecentHitGetterHook));
            else if (p.name == "Pilot Carrier Null Guard") {
                void* original = isSteam
                    ? HookEngine::ResolveRelCallTargetWithRetry(p.address - 1, 300, 10)
                    : HookEngine::ResolveRelCallTarget(p.address - 1);
                const uint32_t expected =
                    HookEngine::ResolveNamedAddress("Carrier::GetSelected");
                if (!original || expected == 0 ||
                    reinterpret_cast<uintptr_t>(original) != expected) {
                    Log(L"[PILOTSAFE] call identity failed site=0x%08X original=%p expected=0x%08X; leaving stock call\n",
                        p.address - 1, original, expected);
                    continue;
                }
                SetPersonCarrierGetSelectedOriginal(original);
                target = static_cast<uint32_t>(
                    reinterpret_cast<uintptr_t>(PersonCarrierGetSelectedGuard));
            }
            else if (p.name == "Neutral Attack Order Target Hook") {
                void* original = isSteam
                    ? HookEngine::ResolveRelCallTargetWithRetry(p.address - 1, 300, 10)
                    : HookEngine::ResolveRelCallTarget(p.address - 1);
                const uint32_t expected =
                    HookEngine::ResolveNamedAddress("Team::EnemyP(int)");
                if (!original || expected == 0 ||
                    reinterpret_cast<uintptr_t>(original) != expected) {
                    Log(L"[NEUTORDER] call identity failed site=0x%08X original=%p expected=0x%08X; leaving stock call\n",
                        p.address - 1, original, expected);
                    continue;
                }
                SetControlPanelEnemyPOriginal(original);
                target = static_cast<uint32_t>(
                    reinterpret_cast<uintptr_t>(ControlPanelEnemyPAttackOrderHook));
            }
            else if (p.name.rfind("AIP Prereq Name Resolve Probe", 0) == 0) {
                void* original = isSteam
                    ? HookEngine::ResolveRelCallTargetWithRetry(p.address - 1, 300, 10)
                    : HookEngine::ResolveRelCallTarget(p.address - 1);
                const uint32_t expected =
                    HookEngine::ResolveNamedAddress("PREREQ_WhatIs");
                if (!original || expected == 0 ||
                    reinterpret_cast<uintptr_t>(original) != expected) {
                    Log(L"[AIPRES] call identity failed site=0x%08X original=%p expected=0x%08X; leaving stock call\n",
                        p.address - 1, original, expected);
                    continue;
                }
                SetAipPrereqWhatIsOriginal(original);
                // Three call sites, one shared original: the account loader
                // (construction program items) and the two matching tables.
                if (p.name.find("Force Matching") != std::string::npos)
                    target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(AipPrereqWhatIsProbeForceMatching));
                else if (p.name.find("Building Matching") != std::string::npos)
                    target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(AipPrereqWhatIsProbeBuildingMatching));
                else
                    target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(AipPrereqWhatIsProbe));
            }
            else if (p.name.rfind("AI Multi Producer Maker", 0) == 0) {
                // Both sites need the same four helpers, so resolve them once
                // and stand the whole feature down unless every one of them,
                // plus this site's own callee, verifies.
                const bool collect = p.name.find("Collect") != std::string::npos;
                void* original = isSteam
                    ? HookEngine::ResolveRelCallTargetWithRetry(p.address - 1, 300, 10)
                    : HookEngine::ResolveRelCallTarget(p.address - 1);
                const uint32_t expected = HookEngine::ResolveNamedAddress(
                    collect ? "AI FindObjectClass" : "AI Units_Init");
                const uint32_t isBuilding = HookEngine::ResolveNamedAddress("AI IsBuilding");
                const uint32_t class2Unit = HookEngine::ResolveNamedAddress("AI Class2UnitType");
                const uint32_t class2Building = HookEngine::ResolveNamedAddress("AI Class2BuildingType");
                const uint32_t getPrereq = HookEngine::ResolveNamedAddress("AI GetPrereq");
                if (!original || expected == 0 ||
                    reinterpret_cast<uintptr_t>(original) != expected ||
                    isBuilding == 0 || class2Unit == 0 || class2Building == 0 || getPrereq == 0) {
                    Log(L"[AIMAKER] identity failed site=0x%08X original=%p expected=0x%08X helpers=%08X/%08X/%08X/%08X; leaving stock registration\n",
                        p.address - 1, original, expected,
                        isBuilding, class2Unit, class2Building, getPrereq);
                    continue;
                }
                SetAiMakerHelperOriginals(reinterpret_cast<void*>(isBuilding),
                                          reinterpret_cast<void*>(class2Unit),
                                          reinterpret_cast<void*>(class2Building),
                                          reinterpret_cast<void*>(getPrereq));
                if (collect) {
                    SetAiFindObjectClassOriginal(original);
                    target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(AiFindObjectClassCollectHook));
                } else {
                    SetAiUnitsInitOriginal(original);
                    target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(AiUnitsInitMultiMakerHook));
                }
            }
            else if (p.name == "Sun Screen Flash Contribution Hook") {
                // Verify the instruction, not just the operand: the byte in
                // front has to be a CALL rel32 and it has to resolve to
                // ScreenFlash::AddFlash. A build whose layout moved leaves the
                // payload empty, so ApplyPatch skips it and stock stands.
                if (!SunFlash::VerifyCallSite(isSteam ? 300 : 1, 10)) { Log(L"[SUNFLASH] call site verify failed at 0x%08X; leaving stock flash in place\n", p.address); continue; }
                SunFlash::LoadConfig();
                target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(SunFlash::ThunkAddress()));
            }
            else if (p.name.find("Damage Reveal Probe") != std::string::npos) target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(DamageRevealProbeHook));
            else if (p.name.find("HoverCraft Engine Flame Emit Hook") != std::string::npos) target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(Trampoline_EngineFlameHoverCraftEmit));
            else if (p.name == "Artillery Weapon Mask Select Hook") target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(Trampoline_ArtilleryWeaponSelect));
            else if (p.name == "LayMines Weapon Mask Select Hook") target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(Trampoline_LayMinesWeaponSelect));
            else if (p.name == "LayMines Weapon Mask Trigger Hook") target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(Trampoline_LayMinesSetSelected));
            if (target) { int32_t rel = static_cast<int32_t>(target) - static_cast<int32_t>(p.address + 4); p.payload.resize(4); memcpy(p.payload.data(), &rel, 4); }
        }
    }

    // The four artillery volley sites replace a whole 5-byte instruction pair
    // (`mov r32,[vtbl+8]` + `call r32`) rather than a rel32 operand, so the
    // payload is built here as an explicit CALL rel32 instead of going through
    // the REL32 or JMP5 fillers. A site whose address never resolved keeps an
    // empty payload and ApplyPatch leaves the stock indirect call alone.
    static void FillArtilleryVolleyPayloads(std::vector<HookEngine::PatchDef>& patches) {
        const uint32_t target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(Trampoline_ArtilleryTriggerVolley));
        for (auto& p : patches) {
            if (p.type != HookEngine::PatchType::BYTES || !p.verified) continue;
            if (p.name.find("Artillery Volley Trigger Hook") == std::string::npos) continue;
            if (p.address == 0) continue;
            const int32_t rel = static_cast<int32_t>(target) - static_cast<int32_t>(p.address + 5);
            p.payload.resize(5);
            p.payload[0] = 0xE8;
            memcpy(p.payload.data() + 1, &rel, 4);
        }
    }

    static void FillVersionNoticePayloads(std::vector<HookEngine::PatchDef>& patches) {
        const uint32_t tag = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(GetOpenShimVersionTag()));
        const uint32_t flameC = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(EngineFlameControlHook));
        const uint32_t flameS = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(EngineFlameSubmitHook));
        const uint32_t chunkE = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ChunkEffectSimulateHook));
        const uint32_t legacyRQ = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(LegacyWorldUpdateRenderQueueHook));
        for (auto& p : patches) {
            if (p.type != HookEngine::PatchType::DWORD) continue;
            uint32_t val = 0;
            if (p.name.find("Version Notice") != std::string::npos || p.name.find("Main Menu") != std::string::npos) val = tag;
            else if (p.name == "Engine Flame Control VTable Hook") val = flameC;
            else if (p.name == "Engine Flame Submit VTable Hook") val = flameS;
            else if (p.name == "Chunk Effect Simulate VTable Hook") val = chunkE;
            else if (p.name == "Legacy World Update RenderQueue VTable Hook") val = legacyRQ;
            if (val) { p.payload.resize(4); memcpy(p.payload.data(), &val, 4); }
        }
    }

    static void WaitForExpectedBytes(std::vector<HookEngine::PatchDef>& patches, bool isSteam) {
        if (!isSteam) return;
        for (int i = 0; i < 2500; ++i) {
            if (g_ShutdownRequested) return;
            bool all = true;
            for (const auto& p : patches) {
                if (p.address == 0 || p.expected_original.empty()) continue;
                if (p.name.find("Version Notice") == std::string::npos &&
                    p.name.find("Offensive Attack") == std::string::npos &&
                    !IsBanFeaturePatchName(p.name.c_str()) &&
                    !IsVehicleListModFixPatchName(p.name.c_str())) continue;
                std::vector<uint8_t> cur(p.expected_original.size()); SIZE_T r;
                if (!ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(p.address), cur.data(), cur.size(), &r) || cur != p.expected_original) { all = false; break; }
            }
            if (all) return; Sleep(10);
        }
    }

    void RunPatcher(uint32_t shimVersion) {
        g_Config.Load();
        // Preset migration must happen before normal player configuration is
        // fully applied, or the loader must explicitly reload the migrated
        // file before using its values. Run it here – early enough that the
        // corrected file is used for this boot where practical – and before
        // any TryGetUserConfigBool / GetSoundChannelOverrideConfig reads.
        // Documented in openshim_preset_migration.h.
        {
            auto mr = TryMigratePlayerPresetOnStartup();
            (void)mr;
            // If migration migrated or failed, subsequent config reads will
            // either see the new file or (for quarantined settings) the
            // fail-closed in-memory fallback. No further reload is needed
            // because all config readers are lazy GetPrivateProfileStringA
            // consumers that re-read the file on the next query if this
            // completed before their first Initialize*.
        }
        SetBzrDistribution(BzrDistribution::Unknown);
        const bool isSteam = IsSteamExe(); g_EnableScrollRestore = true;
        if (ShouldEnableD3DStartupHooks()) ApplyD3DStartupHooks();
        ApplyTrnSaveNormalizeHooks();
        uint32_t gameVer = GetBZRVersion();
        if (gameVer != static_cast<uint32_t>(g_Config.GetStaticPointer("BZR_EXPECTED_VERSION", BZR_EXPECTED_VERSION))) return;
        const BzrDistribution distribution = isSteam ? BzrDistribution::Steam : BzrDistribution::GOG;
        SetBzrDistribution(distribution);
        Log(L"[PLATFORM] distribution=%hs steamStub=%hs\n",
            distribution == BzrDistribution::Steam ? "Steam" : "GOG",
            isSteam ? "yes" : "no");
        // Publish the result of the check above. Everything past this point
        // writes version-specific addresses, so reaching here IS the definition
        // of a compatible build -- and callers outside the patcher have no other
        // way to ask. This was never being set: the check early-returns on a
        // mismatch and simply fell through on success, leaving the flag false
        // forever. dllmain gates engine-level AutoSave on it, so AutoSave never
        // initialized on any build.
        SetCompatibleVersion(true);
        std::vector<uint8_t> sig; if (ReadExeSignature(sig)) WaitForSignature(sig);
        // .text is decrypted by now, so the CLI delimiter repair applied at
        // attach can finally have its .text corroboration settled, and a
        // SteamStub restore over the .data write would be reported rather than
        // failing silently.
        BZROpenShim::VerifyCliMultiParameterOptionFix();
        const ReduxCompatibilityGate compatibilityGate = PrepareReduxCompatibilityGate(isSteam);
        StartSoundChannelOverride(isSteam);
        g_Config.Load(); auto patches = BuildPatchList(); FilterPatchesForDistribution(patches, distribution); FilterPatchesForRuntime(patches, distribution); ScanForPatchAddresses(patches, isSteam);
        if (isSteam && compatibilityGate.supportedHash && compatibilityGate.settledBytes) {
            const auto compatibilitySignaturesReady = [&patches]() {
                for (const auto& patch : patches) {
                    if (IsReduxCompatibilityPatchName(patch.name.c_str()) && !patch.verified)
                        return false;
                }
                return true;
            };
            // SteamStub can rewrite one of these pages in the few milliseconds
            // between the settlement sample and the unique scan. Retry only
            // this three-signature group; no fallback address is ever enabled.
            for (int attempt = 0; !compatibilitySignaturesReady() && attempt < 10; ++attempt) {
                Sleep(100);
                ScanForPatchAddresses(patches, isSteam, true);
            }
        }
        auto findAddr = [&patches](const char* n) -> uint32_t { for (const auto& p : patches) { if (p.name == n) return p.address; } return 0; };
        ResolvePointers(findAddr("Map Sorting"), findAddr("Map List Rewrite for Hop-Fix 1/3"), findAddr("Map List Rewrite for Hop-Fix 2/3"), findAddr("Map List Rewrite for Hop-Fix 3/3"), findAddr("Probe Refresh Path MapFilter1"), findAddr("Map List Fix Support 1/3"), findAddr("Probe MapListFix2"), findAddr("TurretCraft Aim Pitch Multiplier"), findAddr("TurretTank Aim Pitch Multiplier"), findAddr("Under Attack Alert Hook 1/2"), findAddr("Under Attack Alert Hook 2/2"), findAddr("Offensive Attack Reveal Hook"), findAddr("TurretTank Attack Reveal Hook"), isSteam);
        ResolveStaticReturnPointers();
        ResolveBzrHooks(isSteam); InitBzrHookStrings(); SuppressStartupShellAutoLoad();
        FillJmp5Payloads(patches); FillVersionNoticePayloads(patches); FillRel32Payloads(patches, isSteam); FillArtilleryVolleyPayloads(patches); WaitForExpectedBytes(patches, isSteam);
        // Apply critical patches (JMP5 hooks, version notice, etc.) BEFORE the
        // deferred-hook retry loop. The retry loop can take ~25 seconds for
        // Steam input binding UI hooks, and the game may crash during that
        // window if critical fixes (e.g. AutoSave +0x150 null callback) are
        // not yet installed.
        int app = ApplyReduxCompatibilityPatches(patches, compatibilityGate);
        patches.erase(std::remove_if(patches.begin(), patches.end(), [](const HookEngine::PatchDef& patch) {
            return IsReduxCompatibilityPatchName(patch.name.c_str());
        }), patches.end());
        for (const auto& p : patches) {
            if (HookEngine::ApplyPatch(p)) {
                app++;
                if (p.name == "Sun Screen Flash Contribution Hook") SunFlash::SetPatchInstalled(true);
                Log(L"[OK]   %hs wrote %u bytes to 0x%08X\n", p.name.c_str(), static_cast<unsigned>(p.payload.size()), p.address);
            } else {
                Log(L"[SKIP] %hs address=0x%08X verified=%hs payload=%u\n", p.name.c_str(), p.address, p.verified ? "yes" : "no", static_cast<unsigned>(p.payload.size()));
            }
        }
        Log(L"[DONE] Applied=%d of %u\n", app, static_cast<unsigned>(patches.size()));
        // A patch this build knows about but that resolved to address 0 was
        // never looked up at all: its scripts/patches.json entry is missing.
        // That is almost always a deploy where winmm.dll moved and patches.json
        // did not, and the only prior symptom was one [SKIP] line among forty.
        // Name them together so a stale json is obvious in the log.
        {
            std::string unresolved;
            int unresolvedCount = 0;
            for (const auto& p : patches) {
                if (p.address != 0) continue;
                if (!unresolved.empty()) unresolved += ", ";
                unresolved += p.name;
                ++unresolvedCount;
            }
            if (unresolvedCount > 0) {
                Log(L"[STALE-CONFIG] %d patch(es) had no scripts/patches.json entry and were never "
                    L"attempted: %hs -- check that patches.json was deployed alongside winmm.dll\n",
                    unresolvedCount, unresolved.c_str());
            }
        }
        SetPatchingComplete(true); SetAppliedPatchCount(app);
        InstallBriefingAssetOverrides();
        if (ShouldEnableOgreMaterialCollisionGuard()) {
            InstallOgreMaterialCollisionGuard();
        }
        RetryDeferredRuntimeHooks();
        if (isSteam && (!AreInputBindingUiHooksInstalled() || !AreRequiredDeferredRuntimeHooksInstalled())) {
            // Steam's executable code pages do not all settle at once. Keep
            // retrying the required deferred hooks even if the input UI hooks
            // became ready first; GOG reaches the same plaintext bytes without
            // this settlement window.
            for (int i = 0; i < 250; ++i) {
                if (g_ShutdownRequested) return;
                if (AreInputBindingUiHooksInstalled() && AreRequiredDeferredRuntimeHooksInstalled()) break;
                Sleep(100);
                RetryDeferredRuntimeHooks();
            }
        }
    }
}
