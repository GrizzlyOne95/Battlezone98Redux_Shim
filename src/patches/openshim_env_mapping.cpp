// The decision half of the OPENSHIM_* / BZR_* environment redirect; see
// openshim_env_mapping.h for the lookup order. No Windows calls: the Win32
// readers live in openshim_env_config.cpp, and the unit tests supply fakes.

#include "openshim_env_mapping.h"
#include "bool_token.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <string>

namespace
{
    using BZROpenShim::EnvConfig::IniFile;
    using BZROpenShim::EnvConfig::IniReader;

    bool ParseBool(const std::string& raw, bool& out)
    {
        return BZROpenShim::BoolToken::TryParse(raw, out);
    }

    bool TryReadMappedBool(const IniReader& ini,
                           const char* section,
                           const char* key,
                           bool invert,
                           std::string& out)
    {
        std::string value;
        if (!ini(IniFile::Main, section, key, value))
            return false;

        bool enabled = false;
        if (!ParseBool(value, enabled))
            return false;
        if (invert)
            enabled = !enabled;
        out = enabled ? "1" : "0";
        return true;
    }

    // [Network] GovernorTuning is a named choice rather than a boolean, because
    // "1" would read as "turn something on" when what it actually selects is
    // which of two measured tuning sets the bandwidth governor runs. The plain
    // booleans stay accepted so an existing script setting 0/1 keeps working.
    bool TryReadMappedGovernorTuning(const IniReader& ini,
                                     const char* section,
                                     const char* key,
                                     std::string& out)
    {
        std::string value;
        if (!ini(IniFile::Main, section, key, value))
            return false;

        std::string token = value;
        token.erase(token.begin(), std::find_if(token.begin(), token.end(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }));
        token.erase(std::find_if(token.rbegin(), token.rend(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }).base(), token.end());
        std::transform(token.begin(), token.end(), token.begin(), [](unsigned char ch)
        {
            return static_cast<char>(std::tolower(ch));
        });

        if (token == "openshim" || token == "tuned")
        {
            out = "1";
            return true;
        }
        if (token == "stock" || token == "default")
        {
            out = "0";
            return true;
        }

        bool enabled = false;
        if (!ParseBool(value, enabled))
            return false;
        out = enabled ? "1" : "0";
        return true;
    }

    // ASCII case-insensitive, as _stricmp is in the C locale. Environment
    // names are ASCII.
    bool Equals(const char* left, const char* right)
    {
        if (!left || !right)
            return false;
        for (;; ++left, ++right)
        {
            const char a = BZROpenShim::BoolToken::Detail::ToLowerAscii(*left);
            const char b = BZROpenShim::BoolToken::Detail::ToLowerAscii(*right);
            if (a != b)
                return false;
            if (a == '\0')
                return true;
        }
    }

    bool TryReadFriendlyMapping(const char* name,
                                const IniReader& ini,
                                std::string& out)
    {
        // Startup / patcher diagnostics.
        if (Equals(name, "OPENSHIM_TRACE_HITS"))
            return TryReadMappedBool(ini, "Diagnostics", "TraceHookHits", false, out);
        if (Equals(name, "OPENSHIM_ENABLE_D3D_STARTUP_HOOKS"))
            return TryReadMappedBool(ini, "Startup", "D3DStartupHooks", false, out);
        if (Equals(name, "OPENSHIM_ALLOW_STARTUP_AUTOLOAD"))
            return TryReadMappedBool(ini, "Startup", "AllowStartupAutoLoad", false, out);
        if (Equals(name, "OPENSHIM_TRACE_MAP_REFRESH") ||
            Equals(name, "OPENSHIM_TRACE_STEAM_MAP_REFRESH"))
        {
            return TryReadMappedBool(ini, "Diagnostics", "TraceMapRefresh", false, out);
        }
        if (Equals(name, "OPENSHIM_TRACE_JUMP_SNIPING") ||
            Equals(name, "OPENSHIM_TRACE_JUMPSNIPE"))
        {
            return TryReadMappedBool(ini, "Diagnostics", "TraceJumpSniping", false, out);
        }
        if (Equals(name, "OPENSHIM_TRACE_ARTILLERY_MASK") ||
            Equals(name, "OPENSHIM_TRACE_WEAPON_MASK"))
        {
            return TryReadMappedBool(ini, "Diagnostics", "TraceArtilleryMask", false, out);
        }
        if (Equals(name, "OPENSHIM_RUN_IN_BACKGROUND"))
            return TryReadMappedBool(ini, "Testing", "RunInBackground", false, out);
        if (Equals(name, "OPENSHIM_TRACE_SUN_FLASH"))
            return TryReadMappedBool(ini, "Diagnostics", "TraceSunFlash", false, out);
        if (Equals(name, "OPENSHIM_TRACE_BZN_LOAD"))
            return TryReadMappedBool(ini, "Diagnostics", "TraceBznLoad", false, out);
        if (Equals(name, "OPENSHIM_INTERACTIVE_FOG_WAKES"))
            return TryReadMappedBool(ini, "Experimental", "InteractiveFogWakes", false, out);

        // Working runtime features use positive INI keys; legacy DISABLE_*
        // environment names are inverted here so old call-site semantics remain
        // unchanged.
        if (Equals(name, "OPENSHIM_DISABLE_CHUNK_EXPERIMENTS") ||
            Equals(name, "BZR_DISABLE_CHUNK_EXPERIMENTS"))
        {
            return TryReadMappedBool(ini, "General", "ChunkMeshes", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_CHUNK_MESH_PROXY") ||
            Equals(name, "BZR_DISABLE_CHUNK_MESH_PROXY"))
        {
            return TryReadMappedBool(ini, "General", "ChunkMeshes", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_GENERIC_CHUNK_BATCH") ||
            Equals(name, "BZR_DISABLE_GENERIC_CHUNK_BATCH"))
        {
            return TryReadMappedBool(ini, "General", "ChunkMeshes", true, out);
        }
        // SkinnedGibs: person deaths as rigid limb gibs. Independent of
        // ChunkMeshes; the numeric keys are read raw and clamped by the
        // feature.
        if (Equals(name, "OPENSHIM_DISABLE_SKINNED_GIBS") || Equals(name, "BZR_DISABLE_SKINNED_GIBS"))
            return TryReadMappedBool(ini, "General", "SkinnedGibs", true, out);
        if (Equals(name, "OPENSHIM_SKINNED_GIBS_MAX"))
            return ini(IniFile::Main, "General", "SkinnedGibsMax", out);
        if (Equals(name, "OPENSHIM_SKINNED_GIBS_LINGER"))
            return ini(IniFile::Main, "General", "SkinnedGibsLinger", out);
        if (Equals(name, "OPENSHIM_SKINNED_GIBS_FORCE"))
            return ini(IniFile::Main, "General", "SkinnedGibsForce", out);
        if (Equals(name, "OPENSHIM_TRACE_SKINNED_GIBS"))
            return TryReadMappedBool(ini, "Diagnostics", "TraceSkinnedGibs", false, out);
        // ShellCasings: cosmetic casings from cannon-like weapons. The class
        // list and numeric keys are read raw and parsed by the feature.
        if (Equals(name, "OPENSHIM_DISABLE_SHELL_CASINGS") || Equals(name, "BZR_DISABLE_SHELL_CASINGS"))
            return TryReadMappedBool(ini, "General", "ShellCasings", true, out);
        if (Equals(name, "OPENSHIM_SHELL_CASINGS_MAX"))
            return ini(IniFile::Main, "General", "ShellCasingsMax", out);
        if (Equals(name, "OPENSHIM_SHELL_CASINGS_LINGER"))
            return ini(IniFile::Main, "General", "ShellCasingsLinger", out);
        if (Equals(name, "OPENSHIM_SHELL_CASINGS_CLASSES"))
            return ini(IniFile::Main, "General", "ShellCasingsClasses", out);
        if (Equals(name, "OPENSHIM_TRACE_SHELL_CASINGS"))
            return TryReadMappedBool(ini, "Diagnostics", "TraceShellCasings", false, out);

        // PathBlockFaces: building path-grid footprints from collision faces
        // for ODFs that opt in. Its own inverted switch, default ON.
        if (Equals(name, "OPENSHIM_DISABLE_PATH_BLOCK_FACES"))
            return TryReadMappedBool(ini, "General", "PathBlockFaces", true, out);
        if (Equals(name, "OPENSHIM_TRACE_PATH_BLOCK"))
            return TryReadMappedBool(ini, "Diagnostics", "TracePathBlock", false, out);
        if (Equals(name, "OPENSHIM_DISABLE_MAP_REFRESH_FIXES") ||
            Equals(name, "BZR_DISABLE_MAP_REFRESH_FIXES"))
        {
            return TryReadMappedBool(ini, "General", "MapRefreshFixes", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_MUSIC_GLOBAL_FOCUS"))
            return TryReadMappedBool(ini, "General", "MusicGlobalFocus", true, out);
        if (Equals(name, "OPENSHIM_DISABLE_CONTROL_SMOOTHING") ||
            Equals(name, "BZR_DISABLE_CONTROL_SMOOTHING"))
        {
            return TryReadMappedBool(ini, "General", "DisableControlSmoothing", false, out);
        }

        // [Fixes]: confirmed Redux engine defects OpenShim corrects. These are
        // ON by default and stay on for normal play -- they are bug fixes, not
        // enhancements -- but each one is now individually switchable, because
        // they apply in single-player and multiplayer alike and several of them
        // touch the simulation. A player in a lobby with stock clients, or
        // anyone bisecting a suspected regression, needs to be able to turn an
        // individual fix off without editing the process environment.
        if (Equals(name, "OPENSHIM_DISABLE_APC_DEPLOY_FIX") ||
            Equals(name, "BZR_DISABLE_APC_DEPLOY_FIX"))
        {
            return TryReadMappedBool(ini, "Fixes", "ApcAlliedTargetDeploy", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_SPLINTER_UNDEAD_FIX") ||
            Equals(name, "BZR_DISABLE_SPLINTER_UNDEAD_FIX"))
        {
            return TryReadMappedBool(ini, "Fixes", "SplinterUndead", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_HOWITZER_DEPLOY_FIX") ||
            Equals(name, "BZR_DISABLE_HOWITZER_DEPLOY_FIX"))
        {
            return TryReadMappedBool(ini, "Fixes", "HowitzerUndeployedRetaliation", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_TUG_CARGO_FIX") ||
            Equals(name, "BZR_DISABLE_TUG_CARGO_FIX"))
        {
            return TryReadMappedBool(ini, "Fixes", "TugCargoPostLoad", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_CONSTRUCTOR_RECYCLE_FIX") ||
            Equals(name, "BZR_DISABLE_CONSTRUCTOR_RECYCLE_FIX"))
        {
            return TryReadMappedBool(ini, "Fixes", "ConstructorRecycleStaleTarget", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_CONSTRUCTOR_REMOTE_BUILD_FIX") ||
            Equals(name, "BZR_DISABLE_CONSTRUCTOR_REMOTE_BUILD_FIX"))
        {
            return TryReadMappedBool(ini, "Fixes", "ConstructorRemoteBuild", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_MAGNET_ZERO_RANGE_FIX") ||
            Equals(name, "BZR_DISABLE_MAGNET_ZERO_RANGE_FIX"))
        {
            return TryReadMappedBool(ini, "Fixes", "MagnetZeroRangeGuard", true, out);
        }
        // New switches: these two had no opt-out of any kind before.
        if (Equals(name, "OPENSHIM_DISABLE_PRODUCER_SCRIPT_PREDICATES") ||
            Equals(name, "BZR_DISABLE_PRODUCER_SCRIPT_PREDICATES"))
        {
            return TryReadMappedBool(ini, "Fixes", "ProducerScriptPredicates", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_VEHICLE_LIST_MOD_SCOPING") ||
            Equals(name, "BZR_DISABLE_VEHICLE_LIST_MOD_SCOPING"))
        {
            return TryReadMappedBool(ini, "Fixes", "VehicleListModScoping", true, out);
        }
        if (Equals(name, "OPENSHIM_ENABLE_VEHICLE_LIST_MOD_SCOPING") ||
            Equals(name, "BZR_ENABLE_VEHICLE_LIST_MOD_SCOPING"))
        {
            return TryReadMappedBool(ini, "Fixes", "VehicleListModScoping", false, out);
        }
        if (Equals(name, "OPENSHIM_ENABLE_OGRE_MATERIAL_COLLISION_GUARD") ||
            Equals(name, "BZR_ENABLE_OGRE_MATERIAL_COLLISION_GUARD"))
        {
            return TryReadMappedBool(ini, "General", "OgreMaterialCollisionGuard", false, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_OGRE_MATERIAL_COLLISION_GUARD") ||
            Equals(name, "BZR_DISABLE_OGRE_MATERIAL_COLLISION_GUARD"))
        {
            return TryReadMappedBool(ini, "General", "OgreMaterialCollisionGuard", true, out);
        }

        // Producer submenus are deliberately default-on for the current test
        // cycle. The dedicated producer INI is the authoritative opt-out.
        if (Equals(name, "OPENSHIM_ENABLE_PRODUCER_BUILD_MENU") ||
            Equals(name, "OPENSHIM_ENABLE_PRODUCER_BUILD_MENU_EXPERIMENT") ||
            Equals(name, "BZR_ENABLE_PRODUCER_BUILD_MENU"))
        {
            std::string value;
            if (!ini(IniFile::ProducerBuildMenus, "ProducerBuildMenus", "Enabled", value))
            {
                out = "1";
                return true;
            }
            bool enabled = true;
            if (!ParseBool(value, enabled))
                enabled = true;
            out = enabled ? "1" : "0";
            return true;
        }

        // Multiplayer lobby integration preserves the existing code's platform
        // default when the INI key is omitted. Setting the key makes testing
        // explicit without needing a process environment variable.
        if (Equals(name, "OPENSHIM_ENABLE_LOBBY_BZRNET_INTEGRATION") ||
            Equals(name, "OPENSHIM_ENABLE_LOBBY_UI_BZRNET") ||
            Equals(name, "BZR_ENABLE_LOBBY_BZRNET_INTEGRATION"))
        {
            return TryReadMappedBool(ini, "Network", "LobbyBzrnetIntegration", false, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_LOBBY_BZRNET_INTEGRATION") ||
            Equals(name, "BZR_DISABLE_LOBBY_BZRNET_INTEGRATION"))
        {
            return TryReadMappedBool(ini, "Network", "LobbyBzrnetIntegration", true, out);
        }

        // Wholesale opt-out for OpenShim's socket layer. net_optimizer takes this
        // as the DEFAULT for net.ini's EnableSocketOptimizer, so an explicit key
        // in net.ini still wins. Off means the socket optimizer installs nothing
        // at all -- no winsock hooks, no governor, no auto-kick relax, no
        // reorder/dup mitigation, no DSCP -- which is the "give me stock
        // networking" answer when a player is diagnosing a connection problem.
        if (Equals(name, "OPENSHIM_NET_IMPROVEMENTS") ||
            Equals(name, "BZ_NET_IMPROVEMENTS"))
        {
            return TryReadMappedBool(ini, "Network", "NetImprovements", false, out);
        }

        // Selects which tuning the bandwidth governor and auto-kick run. This is
        // the only openshim.ini key the network layer reads: net_optimizer takes
        // it as the DEFAULT for net.ini's NetTune and AutoKickRelax, so an
        // explicit key in net.ini still wins and the granular per-value keys are
        // unaffected either way.
        if (Equals(name, "OPENSHIM_GOVERNOR_TUNING") ||
            Equals(name, "BZ_GOVERNOR_TUNING"))
        {
            return TryReadMappedGovernorTuning(ini, "Network", "GovernorTuning", out);
        }

        // Existing user-facing INI settings. These mappings make the old env
        // names aliases of the documented INI keys rather than prerequisites.
        if (Equals(name, "OPENSHIM_MAX_SOUND_CHANNELS") || Equals(name, "BZR_MAX_SOUND_CHANNELS"))
        {
            return ini(IniFile::Main, "General", "SoundChannels", out);
        }
        if (Equals(name, "OPENSHIM_ENABLE_INPUT_BINDING_UI") ||
            Equals(name, "OPENSHIM_ENABLE_INPUT_BINDING_UI_REPLACEMENT") ||
            Equals(name, "BZR_ENABLE_INPUT_BINDING_UI"))
        {
            return TryReadMappedBool(ini, "General", "CustomBindsUi", false, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_INPUT_BINDING_UI") ||
            Equals(name, "OPENSHIM_DISABLE_INPUT_BINDING_UI_REPLACEMENT") ||
            Equals(name, "BZR_DISABLE_INPUT_BINDING_UI"))
        {
            return TryReadMappedBool(ini, "General", "CustomBindsUi", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_SETTINGS_UI") || Equals(name, "BZR_DISABLE_SETTINGS_UI"))
            return TryReadMappedBool(ini, "General", "SettingsUi", true, out);

        if (Equals(name, "OPENSHIM_TERRAIN_SEMANTIC_LIFECYCLE_LOG"))
            return ini(IniFile::Main, "Terrain", "TerrainSemanticLifecycleLog", out);
        if (Equals(name, "OPENSHIM_TERRAIN_SEMANTIC_DEBUG"))
            return ini(IniFile::Main, "Terrain", "TerrainSemanticDebug", out);
        if (Equals(name, "OPENSHIM_TERRAIN_SEMANTIC_FRAME_CAPTURE"))
            return ini(IniFile::Main, "Terrain", "TerrainSemanticFrameCapture", out);
        if (Equals(name, "OPENSHIM_TERRAIN_SEMANTIC_FRAME_CAPTURE_STRIDE"))
            return ini(IniFile::Main, "Terrain", "TerrainSemanticFrameCaptureStride", out);
        if (Equals(name, "OPENSHIM_TERRAIN_HD"))
            return ini(IniFile::Main, "Terrain", "TerrainHdEnabled", out);
        if (Equals(name, "OPENSHIM_TERRAIN_HD_MANIFEST"))
            return ini(IniFile::Main, "Terrain", "TerrainHdManifest", out);

        if (Equals(name, "OPENSHIM_MP_FLAG_SHOW_OWN") || Equals(name, "BZR_MP_FLAG_SHOW_OWN"))
            return ini(IniFile::Main, "Display", "MultiplayerFlagShowOwnCraft", out);
        if (Equals(name, "OPENSHIM_FACTION_JET_FLAMES") || Equals(name, "BZR_FACTION_JET_FLAMES"))
            return TryReadMappedBool(ini, "Display", "JetFlames", false, out);
        if (Equals(name, "OPENSHIM_DISABLE_FACTION_JET_FLAMES") ||
            Equals(name, "BZR_DISABLE_FACTION_JET_FLAMES"))
        {
            return TryReadMappedBool(ini, "Display", "JetFlames", true, out);
        }
        // Route tracing for the flames above. Env-only diagnostics are a trap
        // here: the game is launched by a storefront that inherited its
        // environment long before anyone typed setx, so the flag silently never
        // arrives. Reading it from the INI is the only lever a tester has.
        if (Equals(name, "OPENSHIM_TRACE_JET_FLAMES") ||
            Equals(name, "BZR_TRACE_JET_FLAMES"))
        {
            return TryReadMappedBool(ini, "Diagnostics", "TraceJetFlames", false, out);
        }

        // One master switch for the whole BZRNet/relay control-plane capture, so
        // a tester is told one key rather than four. It reaches the relay-control
        // JSONL and raw buffer ring in net_optimizer.cpp and the structured
        // BZRNet trace in bzrnet_instrumentation.cpp, both of which already read
        // these legacy names through this redirect.
        if (Equals(name, "OPENSHIM_RELAY_CAPTURE") ||
            Equals(name, "BZ_RELAY_CAPTURE") ||
            Equals(name, "OPENSHIM_BZRNET_TRACE") ||
            Equals(name, "BZ_BZRNET_TRACE"))
        {
            return TryReadMappedBool(ini, "Diagnostics", "RelayLogging", false, out);
        }
        if (Equals(name, "OPENSHIM_RELAY_LOG_ALL_CONTROL"))
            return TryReadMappedBool(ini, "Diagnostics", "RelayLogAllControl", false, out);
        if (Equals(name, "OPENSHIM_RELAY_LOG_DATAGRAMS"))
            return TryReadMappedBool(ini, "Diagnostics", "RelayLogDatagrams", false, out);
        if (Equals(name, "OPENSHIM_BZRNET_TRACE_PRIVATE") ||
            Equals(name, "BZ_BZRNET_TRACE_PRIVATE"))
        {
            return TryReadMappedBool(ini, "Diagnostics", "RelayLoggingPrivateForensic", false, out);
        }
        if (Equals(name, "OPENSHIM_BZRNET_TRACE_ALL_UDP") ||
            Equals(name, "BZ_BZRNET_TRACE_ALL_UDP"))
        {
            return TryReadMappedBool(ini, "Diagnostics", "RelayLoggingAllUdp", false, out);
        }
        if (Equals(name, "OPENSHIM_BZRNET_TRACE_QUEUE") ||
            Equals(name, "BZ_BZRNET_TRACE_QUEUE"))
        {
            return ini(IniFile::Main, "Diagnostics", "RelayLoggingQueueRecords", out);
        }

        if (Equals(name, "OPENSHIM_PROFILE_OGRE_ANIMATION"))
            return ini(IniFile::Main, "Diagnostics", "ProfileOgreAnimation", out);
        if (Equals(name, "OPENSHIM_TERRAIN_RENDER_PROBE"))
            return ini(IniFile::Main, "Diagnostics", "TerrainRenderProbe", out);
        if (Equals(name, "OPENSHIM_UI_PERFORMANCE_LOGGING"))
            return ini(IniFile::Main, "Diagnostics", "UiPerformanceLogging", out);
        if (Equals(name, "OPENSHIM_UI_PERFORMANCE_VERBOSE"))
            return ini(IniFile::Main, "Diagnostics", "UiPerformanceVerbose", out);

        if (Equals(name, "OPENSHIM_DISABLE_LOBBY_READOUTS"))
            return TryReadMappedBool(ini, "Network", "LobbyReadouts", true, out);
        if (Equals(name, "OPENSHIM_DISABLE_LOBBY_BAN_BUTTON") ||
            Equals(name, "BZR_DISABLE_LOBBY_BAN_BUTTON"))
        {
            return TryReadMappedBool(ini, "Network", "LobbyBanButton", true, out);
        }
        if (Equals(name, "OPENSHIM_ENABLE_LOBBY_BAN_BUTTON") ||
            Equals(name, "BZR_ENABLE_LOBBY_BAN_BUTTON"))
        {
            return TryReadMappedBool(ini, "Network", "LobbyBanButton", false, out);
        }
        // Persistent per-player mute. Positive key, default ON, so absence keeps
        // the shipped behaviour: a mute is written to mutes.cfg and reapplied on
        // later sessions. Off leaves Redux's own per-process mute alone, which is
        // session-only -- it does not delete an existing mutes.cfg.
        if (Equals(name, "OPENSHIM_DISABLE_PERSISTENT_PLAYER_MUTE") ||
            Equals(name, "BZR_DISABLE_PERSISTENT_PLAYER_MUTE"))
        {
            return TryReadMappedBool(ini, "Network", "PersistentPlayerMute", true, out);
        }
        if (Equals(name, "OPENSHIM_ENABLE_PERSISTENT_PLAYER_MUTE") ||
            Equals(name, "BZR_ENABLE_PERSISTENT_PLAYER_MUTE"))
        {
            return TryReadMappedBool(ini, "Network", "PersistentPlayerMute", false, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_BZRNET_REAUTH") || Equals(name, "BZR_DISABLE_BZRNET_REAUTH"))
            return TryReadMappedBool(ini, "Network", "ReauthOnNicknameChange", true, out);
        if (Equals(name, "OPENSHIM_ENABLE_BZRNET_REAUTH") || Equals(name, "BZR_ENABLE_BZRNET_REAUTH") ||
            Equals(name, "OPENSHIM_BZRNET_REAUTH") || Equals(name, "BZR_BZRNET_REAUTH"))
            return TryReadMappedBool(ini, "Network", "ReauthOnNicknameChange", false, out);
        // Multiplayer starting-vehicle list: restore the 1.5 "Any Nation = OFF"
        // restricted pool. Positive key, default OFF, so absence is stock.
        // Terrain detail-atlas rect repair. Positive key, default OFF: the
        // correction itself is proven against all eleven shipped atlases, but
        // the open-redirect that delivers it to Redux has not been confirmed
        // on a live run yet.
        if (Equals(name, "OPENSHIM_TERRAIN_ATLAS_RECT_REPAIR") ||
            Equals(name, "BZR_TERRAIN_ATLAS_RECT_REPAIR"))
        {
            return TryReadMappedBool(ini, "Fixes", "TerrainAtlasRectRepair", false, out);
        }
        if (Equals(name, "OPENSHIM_STOCK_FACTIONS_ONLY"))
            return TryReadMappedBool(ini, "Network", "StockFactionsOnly", false, out);
        if (Equals(name, "OPENSHIM_STOCK_FACTION_SET"))
            return ini(IniFile::Main, "Network", "StockFactionSet", out);

        if (Equals(name, "OPENSHIM_TURRET_AIM_PITCH_MULTIPLIER") ||
            Equals(name, "OPENSHIM_TURRET_PITCH_MULTIPLIER"))
        {
            return ini(IniFile::Main, "SinglePlayer", "TurretAimPitchMultiplier", out);
        }
        if (Equals(name, "OPENSHIM_GLOBAL_TURBO_TOLERANCE"))
            return ini(IniFile::Main, "SinglePlayer", "TurboTolerance", out);

        return false;
    }
}

namespace BZROpenShim
{
namespace EnvConfig
{
    const char* IniFileName(IniFile file)
    {
        switch (file)
        {
        case IniFile::Main:
            return "openshim.ini";
        case IniFile::ProducerBuildMenus:
            return "openshim_producer_build_menus.ini";
        }
        return "openshim.ini";
    }

    bool IsCaptureOverrideName(const char* name)
    {
        // Capture wrappers need to override the shipped OFF defaults without
        // rewriting a player's persistent INI. Honor these short-lived
        // diagnostic variables first; the INI remains authoritative when no
        // override exists.
        return Equals(name, "BZ_RELAY_CAPTURE") ||
               Equals(name, "OPENSHIM_RELAY_CAPTURE") ||
               Equals(name, "BZ_BZRNET_TRACE") ||
               Equals(name, "OPENSHIM_BZRNET_TRACE") ||
               Equals(name, "BZ_BZRNET_TRACE_PRIVATE") ||
               Equals(name, "OPENSHIM_BZRNET_TRACE_PRIVATE") ||
               Equals(name, "BZ_BZRNET_TRACE_ALL_UDP") ||
               Equals(name, "OPENSHIM_BZRNET_TRACE_ALL_UDP") ||
               Equals(name, "BZ_BZRNET_TRACE_QUEUE") ||
               Equals(name, "OPENSHIM_BZRNET_TRACE_QUEUE") ||
               Equals(name, "OPENSHIM_RELAY_LOG_ALL_CONTROL") ||
               Equals(name, "OPENSHIM_RELAY_LOG_DATAGRAMS");
    }

    bool TryReadFromIni(const char* name, const IniReader& ini, std::string& out)
    {
        if (!name || !*name)
            return false;
        if (TryReadFriendlyMapping(name, ini, out))
            return true;

        // Universal compatibility escape hatch: any old or newly-added
        // OPENSHIM_*/BZR_* environment key can be placed verbatim under
        // [Environment] in openshim.ini. This means new diagnostics do not
        // need another round of process-level launch configuration just to be
        // tested.
        return ini(IniFile::Main, "Environment", name, out);
    }

    uint32_t CopyEnvironmentValue(const std::string& value, char* buffer, uint32_t size)
    {
        const uint32_t required = static_cast<uint32_t>(value.size() + 1);
        if (size == 0)
            return required;
        if (!buffer)
            return 0;
        if (required > size)
        {
            buffer[0] = '\0';
            return required;
        }
        std::memcpy(buffer, value.c_str(), required);
        return static_cast<uint32_t>(value.size());
    }

    uint32_t GetEnvironmentValue(const char* name,
                                 char* buffer,
                                 uint32_t size,
                                 const IniReader* ini,
                                 const EnvironmentReader& env)
    {
        if (!name || !*name)
            return env(name, buffer, size);

        if (IsCaptureOverrideName(name))
        {
            const uint32_t overrideLength = env(name, buffer, size);
            if (overrideLength != 0)
                return overrideLength;
        }

        if (ini)
        {
            std::string value;
            if (TryReadFromIni(name, *ini, value))
                return CopyEnvironmentValue(value, buffer, size);
        }

        // Backward compatibility for existing launch scripts and developer
        // setups.
        return env(name, buffer, size);
    }
}
}
