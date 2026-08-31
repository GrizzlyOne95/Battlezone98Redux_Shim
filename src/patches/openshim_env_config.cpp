#include "openshim_env_config.h"

// This translation unit is itself compiled with openshim_env_config.h forced in.
// Undefine the redirect here so the final fallback reaches the real Win32 API.
#undef GetEnvironmentVariableA

#include <algorithm>
#include <cctype>
#include <cstring>
#include <filesystem>
#include <string>

namespace
{
    constexpr char kUnsetValue[] = "\x01__openshim_unset__";

    std::filesystem::path GetModuleDirectory()
    {
        char path[MAX_PATH] = {};
        const DWORD length = GetModuleFileNameA(nullptr, path, static_cast<DWORD>(sizeof(path)));
        if (length == 0 || length >= sizeof(path))
            return {};
        return std::filesystem::path(path).parent_path();
    }

    bool TryReadIniValue(const std::filesystem::path& path,
                         const char* section,
                         const char* key,
                         std::string& out)
    {
        if (path.empty() || !section || !key)
            return false;

        char value[1024] = {};
        const DWORD length = GetPrivateProfileStringA(
            section,
            key,
            kUnsetValue,
            value,
            static_cast<DWORD>(sizeof(value)),
            path.string().c_str());
        if (length == 0 || std::strcmp(value, kUnsetValue) == 0)
            return false;

        out.assign(value, length);
        return true;
    }

    bool ParseBool(const std::string& raw, bool& out)
    {
        std::string value = raw;
        value.erase(value.begin(), std::find_if(value.begin(), value.end(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }));
        value.erase(std::find_if(value.rbegin(), value.rend(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }).base(), value.end());
        std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch)
        {
            return static_cast<char>(std::tolower(ch));
        });

        if (value == "1" || value == "true" || value == "on" ||
            value == "yes" || value == "enabled")
        {
            out = true;
            return true;
        }
        if (value == "0" || value == "false" || value == "off" ||
            value == "no" || value == "disabled")
        {
            out = false;
            return true;
        }
        return false;
    }

    bool TryReadMappedBool(const std::filesystem::path& configPath,
                           const char* section,
                           const char* key,
                           bool invert,
                           std::string& out)
    {
        std::string value;
        if (!TryReadIniValue(configPath, section, key, value))
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
    bool TryReadMappedGovernorTuning(const std::filesystem::path& configPath,
                                     const char* section,
                                     const char* key,
                                     std::string& out)
    {
        std::string value;
        if (!TryReadIniValue(configPath, section, key, value))
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

    bool Equals(const char* left, const char* right)
    {
        return left && right && _stricmp(left, right) == 0;
    }

    bool TryReadFriendlyMapping(const char* name,
                                const std::filesystem::path& moduleDir,
                                std::string& out)
    {
        const auto mainIni = moduleDir / "openshim.ini";

        // Startup / patcher diagnostics.
        if (Equals(name, "OPENSHIM_TRACE_HITS"))
            return TryReadMappedBool(mainIni, "Diagnostics", "TraceHookHits", false, out);
        if (Equals(name, "OPENSHIM_ENABLE_D3D_STARTUP_HOOKS"))
            return TryReadMappedBool(mainIni, "Startup", "D3DStartupHooks", false, out);
        if (Equals(name, "OPENSHIM_ALLOW_STARTUP_AUTOLOAD"))
            return TryReadMappedBool(mainIni, "Startup", "AllowStartupAutoLoad", false, out);
        if (Equals(name, "OPENSHIM_TRACE_MAP_REFRESH") ||
            Equals(name, "OPENSHIM_TRACE_STEAM_MAP_REFRESH"))
        {
            return TryReadMappedBool(mainIni, "Diagnostics", "TraceMapRefresh", false, out);
        }
        if (Equals(name, "OPENSHIM_TRACE_JUMP_SNIPING") ||
            Equals(name, "OPENSHIM_TRACE_JUMPSNIPE"))
        {
            return TryReadMappedBool(mainIni, "Diagnostics", "TraceJumpSniping", false, out);
        }
        if (Equals(name, "OPENSHIM_TRACE_ARTILLERY_MASK") ||
            Equals(name, "OPENSHIM_TRACE_WEAPON_MASK"))
        {
            return TryReadMappedBool(mainIni, "Diagnostics", "TraceArtilleryMask", false, out);
        }
        if (Equals(name, "OPENSHIM_TRACE_SUN_FLASH"))
            return TryReadMappedBool(mainIni, "Diagnostics", "TraceSunFlash", false, out);

        // Working runtime features use positive INI keys; legacy DISABLE_*
        // environment names are inverted here so old call-site semantics remain
        // unchanged.
        if (Equals(name, "OPENSHIM_DISABLE_CHUNK_EXPERIMENTS") ||
            Equals(name, "BZR_DISABLE_CHUNK_EXPERIMENTS"))
        {
            return TryReadMappedBool(mainIni, "General", "ChunkMeshes", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_MAP_REFRESH_FIXES") ||
            Equals(name, "BZR_DISABLE_MAP_REFRESH_FIXES"))
        {
            return TryReadMappedBool(mainIni, "General", "MapRefreshFixes", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_MUSIC_GLOBAL_FOCUS"))
            return TryReadMappedBool(mainIni, "General", "MusicGlobalFocus", true, out);

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
            return TryReadMappedBool(mainIni, "Fixes", "ApcAlliedTargetDeploy", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_SPLINTER_UNDEAD_FIX") ||
            Equals(name, "BZR_DISABLE_SPLINTER_UNDEAD_FIX"))
        {
            return TryReadMappedBool(mainIni, "Fixes", "SplinterUndead", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_HOWITZER_DEPLOY_FIX") ||
            Equals(name, "BZR_DISABLE_HOWITZER_DEPLOY_FIX"))
        {
            return TryReadMappedBool(mainIni, "Fixes", "HowitzerUndeployedRetaliation", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_TUG_CARGO_FIX") ||
            Equals(name, "BZR_DISABLE_TUG_CARGO_FIX"))
        {
            return TryReadMappedBool(mainIni, "Fixes", "TugCargoPostLoad", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_CONSTRUCTOR_REMOTE_BUILD_FIX") ||
            Equals(name, "BZR_DISABLE_CONSTRUCTOR_REMOTE_BUILD_FIX"))
        {
            return TryReadMappedBool(mainIni, "Fixes", "ConstructorRemoteBuild", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_MAGNET_ZERO_RANGE_FIX") ||
            Equals(name, "BZR_DISABLE_MAGNET_ZERO_RANGE_FIX"))
        {
            return TryReadMappedBool(mainIni, "Fixes", "MagnetZeroRangeGuard", true, out);
        }
        // New switches: these two had no opt-out of any kind before.
        if (Equals(name, "OPENSHIM_DISABLE_PRODUCER_SCRIPT_PREDICATES") ||
            Equals(name, "BZR_DISABLE_PRODUCER_SCRIPT_PREDICATES"))
        {
            return TryReadMappedBool(mainIni, "Fixes", "ProducerScriptPredicates", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_VEHICLE_LIST_MOD_SCOPING") ||
            Equals(name, "BZR_DISABLE_VEHICLE_LIST_MOD_SCOPING"))
        {
            return TryReadMappedBool(mainIni, "Fixes", "VehicleListModScoping", true, out);
        }
        if (Equals(name, "OPENSHIM_ENABLE_OGRE_MATERIAL_COLLISION_GUARD") ||
            Equals(name, "BZR_ENABLE_OGRE_MATERIAL_COLLISION_GUARD"))
        {
            return TryReadMappedBool(mainIni, "General", "OgreMaterialCollisionGuard", false, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_OGRE_MATERIAL_COLLISION_GUARD") ||
            Equals(name, "BZR_DISABLE_OGRE_MATERIAL_COLLISION_GUARD"))
        {
            return TryReadMappedBool(mainIni, "General", "OgreMaterialCollisionGuard", true, out);
        }

        // Producer submenus are deliberately default-on for the current test
        // cycle. The dedicated producer INI is the authoritative opt-out.
        if (Equals(name, "OPENSHIM_ENABLE_PRODUCER_BUILD_MENU") ||
            Equals(name, "OPENSHIM_ENABLE_PRODUCER_BUILD_MENU_EXPERIMENT") ||
            Equals(name, "BZR_ENABLE_PRODUCER_BUILD_MENU"))
        {
            const auto producerIni = moduleDir / "openshim_producer_build_menus.ini";
            std::string value;
            if (!TryReadIniValue(producerIni, "ProducerBuildMenus", "Enabled", value))
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
            return TryReadMappedBool(mainIni, "Network", "LobbyBzrnetIntegration", false, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_LOBBY_BZRNET_INTEGRATION") ||
            Equals(name, "BZR_DISABLE_LOBBY_BZRNET_INTEGRATION"))
        {
            return TryReadMappedBool(mainIni, "Network", "LobbyBzrnetIntegration", true, out);
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
            return TryReadMappedBool(mainIni, "Network", "NetImprovements", false, out);
        }

        // Selects which tuning the bandwidth governor and auto-kick run. This is
        // the only openshim.ini key the network layer reads: net_optimizer takes
        // it as the DEFAULT for net.ini's NetTune and AutoKickRelax, so an
        // explicit key in net.ini still wins and the granular per-value keys are
        // unaffected either way.
        if (Equals(name, "OPENSHIM_GOVERNOR_TUNING") ||
            Equals(name, "BZ_GOVERNOR_TUNING"))
        {
            return TryReadMappedGovernorTuning(mainIni, "Network", "GovernorTuning", out);
        }

        // Existing user-facing INI settings. These mappings make the old env
        // names aliases of the documented INI keys rather than prerequisites.
        if (Equals(name, "OPENSHIM_MAX_SOUND_CHANNELS") || Equals(name, "BZR_MAX_SOUND_CHANNELS"))
        {
            return TryReadIniValue(mainIni, "General", "SoundChannels", out);
        }
        if (Equals(name, "OPENSHIM_ENABLE_INPUT_BINDING_UI") ||
            Equals(name, "OPENSHIM_ENABLE_INPUT_BINDING_UI_REPLACEMENT") ||
            Equals(name, "BZR_ENABLE_INPUT_BINDING_UI"))
        {
            return TryReadMappedBool(mainIni, "General", "CustomBindsUi", false, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_INPUT_BINDING_UI") ||
            Equals(name, "OPENSHIM_DISABLE_INPUT_BINDING_UI_REPLACEMENT") ||
            Equals(name, "BZR_DISABLE_INPUT_BINDING_UI"))
        {
            return TryReadMappedBool(mainIni, "General", "CustomBindsUi", true, out);
        }
        if (Equals(name, "OPENSHIM_DISABLE_SETTINGS_UI") || Equals(name, "BZR_DISABLE_SETTINGS_UI"))
            return TryReadMappedBool(mainIni, "General", "SettingsUi", true, out);

        if (Equals(name, "OPENSHIM_TERRAIN_SEMANTIC_LIFECYCLE_LOG"))
            return TryReadIniValue(mainIni, "Terrain", "TerrainSemanticLifecycleLog", out);
        if (Equals(name, "OPENSHIM_TERRAIN_SEMANTIC_DEBUG"))
            return TryReadIniValue(mainIni, "Terrain", "TerrainSemanticDebug", out);
        if (Equals(name, "OPENSHIM_TERRAIN_SEMANTIC_FRAME_CAPTURE"))
            return TryReadIniValue(mainIni, "Terrain", "TerrainSemanticFrameCapture", out);
        if (Equals(name, "OPENSHIM_TERRAIN_SEMANTIC_FRAME_CAPTURE_STRIDE"))
            return TryReadIniValue(mainIni, "Terrain", "TerrainSemanticFrameCaptureStride", out);
        if (Equals(name, "OPENSHIM_TERRAIN_HD"))
            return TryReadIniValue(mainIni, "Terrain", "TerrainHdEnabled", out);
        if (Equals(name, "OPENSHIM_TERRAIN_HD_MANIFEST"))
            return TryReadIniValue(mainIni, "Terrain", "TerrainHdManifest", out);

        if (Equals(name, "OPENSHIM_MP_FLAG_SHOW_OWN") || Equals(name, "BZR_MP_FLAG_SHOW_OWN"))
            return TryReadIniValue(mainIni, "Display", "MultiplayerFlagShowOwnCraft", out);
        if (Equals(name, "OPENSHIM_FACTION_JET_FLAMES") || Equals(name, "BZR_FACTION_JET_FLAMES"))
            return TryReadMappedBool(mainIni, "Display", "JetFlames", false, out);
        if (Equals(name, "OPENSHIM_DISABLE_FACTION_JET_FLAMES") ||
            Equals(name, "BZR_DISABLE_FACTION_JET_FLAMES"))
        {
            return TryReadMappedBool(mainIni, "Display", "JetFlames", true, out);
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
            return TryReadMappedBool(mainIni, "Diagnostics", "RelayLogging", false, out);
        }
        if (Equals(name, "OPENSHIM_RELAY_LOG_ALL_CONTROL"))
            return TryReadMappedBool(mainIni, "Diagnostics", "RelayLogAllControl", false, out);
        if (Equals(name, "OPENSHIM_RELAY_LOG_DATAGRAMS"))
            return TryReadMappedBool(mainIni, "Diagnostics", "RelayLogDatagrams", false, out);
        if (Equals(name, "OPENSHIM_BZRNET_TRACE_PRIVATE") ||
            Equals(name, "BZ_BZRNET_TRACE_PRIVATE"))
        {
            return TryReadMappedBool(mainIni, "Diagnostics", "RelayLoggingPrivateForensic", false, out);
        }
        if (Equals(name, "OPENSHIM_BZRNET_TRACE_ALL_UDP") ||
            Equals(name, "BZ_BZRNET_TRACE_ALL_UDP"))
        {
            return TryReadMappedBool(mainIni, "Diagnostics", "RelayLoggingAllUdp", false, out);
        }
        if (Equals(name, "OPENSHIM_BZRNET_TRACE_QUEUE") ||
            Equals(name, "BZ_BZRNET_TRACE_QUEUE"))
        {
            return TryReadIniValue(mainIni, "Diagnostics", "RelayLoggingQueueRecords", out);
        }

        if (Equals(name, "OPENSHIM_PROFILE_OGRE_ANIMATION"))
            return TryReadIniValue(mainIni, "Diagnostics", "ProfileOgreAnimation", out);
        if (Equals(name, "OPENSHIM_TERRAIN_RENDER_PROBE"))
            return TryReadIniValue(mainIni, "Diagnostics", "TerrainRenderProbe", out);
        if (Equals(name, "OPENSHIM_UI_PERFORMANCE_LOGGING"))
            return TryReadIniValue(mainIni, "Diagnostics", "UiPerformanceLogging", out);
        if (Equals(name, "OPENSHIM_UI_PERFORMANCE_VERBOSE"))
            return TryReadIniValue(mainIni, "Diagnostics", "UiPerformanceVerbose", out);

        if (Equals(name, "OPENSHIM_DISABLE_LIVE_NICKNAME"))
            return TryReadMappedBool(mainIni, "Network", "LiveNicknameKeys", true, out);
        if (Equals(name, "OPENSHIM_DISABLE_BZRNET_REAUTH"))
            return TryReadMappedBool(mainIni, "Network", "ReauthOnNicknameChange", true, out);
        if (Equals(name, "OPENSHIM_DISABLE_LOBBY_READOUTS"))
            return TryReadMappedBool(mainIni, "Network", "LobbyReadouts", true, out);

        if (Equals(name, "OPENSHIM_TURRET_AIM_PITCH_MULTIPLIER") ||
            Equals(name, "OPENSHIM_TURRET_PITCH_MULTIPLIER"))
        {
            return TryReadIniValue(mainIni, "SinglePlayer", "TurretAimPitchMultiplier", out);
        }
        if (Equals(name, "OPENSHIM_GLOBAL_TURBO_TOLERANCE"))
            return TryReadIniValue(mainIni, "SinglePlayer", "TurboTolerance", out);

        return false;
    }

    DWORD CopyEnvironmentValue(const std::string& value, LPSTR buffer, DWORD size)
    {
        const DWORD required = static_cast<DWORD>(value.size() + 1);
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
        return static_cast<DWORD>(value.size());
    }
}

DWORD WINAPI OpenShimGetEnvironmentVariableA(LPCSTR name, LPSTR buffer, DWORD size)
{
    if (!name || !*name)
        return ::GetEnvironmentVariableA(name, buffer, size);

    const auto moduleDir = GetModuleDirectory();
    if (!moduleDir.empty())
    {
        std::string value;
        if (TryReadFriendlyMapping(name, moduleDir, value))
            return CopyEnvironmentValue(value, buffer, size);

        // Universal compatibility escape hatch: any old or newly-added
        // OPENSHIM_*/BZR_* environment key can be placed verbatim under
        // [Environment] in openshim.ini. This means new diagnostics do not need
        // another round of process-level launch configuration just to be tested.
        const auto mainIni = moduleDir / "openshim.ini";
        if (TryReadIniValue(mainIni, "Environment", name, value))
            return CopyEnvironmentValue(value, buffer, size);
    }

    // Backward compatibility for existing launch scripts and developer setups.
    return ::GetEnvironmentVariableA(name, buffer, size);
}
