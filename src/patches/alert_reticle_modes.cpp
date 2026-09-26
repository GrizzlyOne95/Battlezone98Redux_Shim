// alert_reticle_modes.cpp
// BZR Open Shim - under-attack alert and target reticle popup modes
// (Display tier), their bridge setters and engine hook entry points, split
// out of bzr_hooks.cpp. Both read the legacy campaignReimagined_settings.cfg
// as well as openshim.ini.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>

namespace BZROpenShim
{
    namespace Hooks
    {
        enum class UnderAttackAlertMode : int
        {
            None = 1,
            Minimal = 2,
            Normal = 3,
        };

        enum class TargetReticlePopupMode : int
        {
            Default = 1,
            NeutralOnly = 2,
            ExplicitOnly = 3,
        };

        bool g_UnderAttackAlertConfigInitialized = false;
        static UnderAttackAlertMode g_UnderAttackAlertMode = UnderAttackAlertMode::Normal;
        static bool g_UnderAttackAlertEnabled = true;
        static float g_UnderAttackAlertCooldownSeconds = 1.0f;
        static float g_UnderAttackAlertNextAllowedTime = 0.0f;
        // User-config baseline: the mode resolved from openshim.ini + legacy cfg
        // + env at init. Scripted (EXU bridge) overrides revert to this, not to
        // the hardcoded Normal default, on a mission reset.
        static bool g_UnderAttackAlertBaselineCaptured = false;
        static UnderAttackAlertMode g_UnderAttackAlertBaselineMode = UnderAttackAlertMode::Normal;
        static bool g_UnderAttackAlertBaselineEnabled = true;
        static float g_UnderAttackAlertBaselineCooldownSeconds = 1.0f;
        static constexpr const char* kUnderAttackAlertConfigName = "campaignReimagined_settings.cfg";
        static constexpr uintptr_t kUnderAttackAlertSoundAddr = 0x00877220;
        bool g_TargetReticlePopupConfigInitialized = false;
        static TargetReticlePopupMode g_TargetReticlePopupMode = TargetReticlePopupMode::Default;
        // User-config baseline (see under-attack alert note above).
        static bool g_TargetReticlePopupBaselineCaptured = false;
        static TargetReticlePopupMode g_TargetReticlePopupBaselineMode = TargetReticlePopupMode::Default;
        static constexpr size_t kGameObjectPlayerShotOffset = 0x1D8;
        static constexpr float kSuppressedRecentHitTime = -1.0e30f;

        static float ClampUnderAttackAlertCooldown(float value)
        {
            if (value < 0.0f)
                return 0.0f;
            if (value > 120.0f)
                return 120.0f;
            return value;
        }

        static const char* UnderAttackAlertModeName(UnderAttackAlertMode mode)
        {
            switch (mode)
            {
            case UnderAttackAlertMode::None:
                return "NONE";
            case UnderAttackAlertMode::Minimal:
                return "MINIMAL";
            default:
                return "NORMAL";
            }
        }

        static UnderAttackAlertMode ClampUnderAttackAlertMode(int value)
        {
            if (value <= static_cast<int>(UnderAttackAlertMode::None))
                return UnderAttackAlertMode::None;
            if (value == static_cast<int>(UnderAttackAlertMode::Minimal))
                return UnderAttackAlertMode::Minimal;
            return UnderAttackAlertMode::Normal;
        }

        static void ApplyUnderAttackAlertMode(UnderAttackAlertMode mode, bool resetTimer)
        {
            g_UnderAttackAlertMode = mode;
            switch (mode)
            {
            case UnderAttackAlertMode::None:
                g_UnderAttackAlertEnabled = false;
                g_UnderAttackAlertCooldownSeconds = 0.0f;
                break;
            case UnderAttackAlertMode::Minimal:
                g_UnderAttackAlertEnabled = true;
                g_UnderAttackAlertCooldownSeconds = 10.0f;
                break;
            case UnderAttackAlertMode::Normal:
            default:
                g_UnderAttackAlertEnabled = true;
                g_UnderAttackAlertCooldownSeconds = 1.0f;
                break;
            }

            if (resetTimer)
                g_UnderAttackAlertNextAllowedTime = 0.0f;
        }

        static bool TryParseUnderAttackAlertModeValue(const char* value, UnderAttackAlertMode& outMode)
        {
            if (!value || !*value)
                return false;

            char normalized[32] = {};
            size_t out = 0;
            for (const char* cursor = value; *cursor && out + 1 < sizeof(normalized); ++cursor)
            {
                if (std::isspace(static_cast<unsigned char>(*cursor)))
                    continue;
                normalized[out++] = static_cast<char>(std::toupper(static_cast<unsigned char>(*cursor)));
            }
            normalized[out] = '\0';
            if (normalized[0] == '\0')
                return false;

            char* end = nullptr;
            const long parsed = std::strtol(normalized, &end, 10);
            if (end != normalized && *end == '\0')
            {
                outMode = parsed <= 0 ? UnderAttackAlertMode::None : ClampUnderAttackAlertMode(static_cast<int>(parsed));
                return true;
            }

            if (std::strcmp(normalized, "NONE") == 0 || std::strcmp(normalized, "OFF") == 0)
            {
                outMode = UnderAttackAlertMode::None;
                return true;
            }
            if (std::strcmp(normalized, "MINIMAL") == 0 || std::strcmp(normalized, "LOW") == 0)
            {
                outMode = UnderAttackAlertMode::Minimal;
                return true;
            }
            if (std::strcmp(normalized, "NORMAL") == 0 || std::strcmp(normalized, "DEFAULT") == 0 ||
                std::strcmp(normalized, "ON") == 0)
            {
                outMode = UnderAttackAlertMode::Normal;
                return true;
            }

            return false;
        }

        static bool TryLoadUnderAttackAlertModeFromConfig(
            const std::filesystem::path& configPath,
            UnderAttackAlertMode& outMode)
        {
            if (configPath.empty())
                return false;

            FILE* file = nullptr;
            if (fopen_s(&file, configPath.string().c_str(), "r") != 0 || !file)
                return false;

            char line[256] = {};
            bool found = false;
            while (std::fgets(line, static_cast<int>(sizeof(line)), file))
            {
                char* trimmed = TrimAsciiInPlace(line);
                if (*trimmed == '\0' || *trimmed == '#' || *trimmed == ';')
                    continue;

                char* equals = std::strchr(trimmed, '=');
                if (!equals)
                    continue;

                *equals = '\0';
                char* key = TrimAsciiInPlace(trimmed);
                char* value = TrimAsciiInPlace(equals + 1);
                if (_stricmp(key, "UnderAttackAlertMode") != 0)
                    continue;

                found = TryParseUnderAttackAlertModeValue(value, outMode);
                break;
            }

            std::fclose(file);
            return found;
        }

        static bool TryGetEnvUnderAttackAlertMode(
            const char* envName,
            UnderAttackAlertMode& outMode)
        {
            if (!envName || !*envName)
                return false;

            char value[32] = {};
            const DWORD len = GetEnvironmentVariableA(envName, value, static_cast<DWORD>(sizeof(value)));
            if (len == 0 || len >= sizeof(value))
                return false;

            return TryParseUnderAttackAlertModeValue(value, outMode);
        }

        void InitializeUnderAttackAlertConfig()
        {
            if (g_UnderAttackAlertConfigInitialized)
                return;

            g_UnderAttackAlertConfigInitialized = true;
            ApplyUnderAttackAlertMode(UnderAttackAlertMode::Normal, true);

            UnderAttackAlertMode mode = UnderAttackAlertMode::Normal;

            // Global user baseline (openshim.ini [Display]) — lowest-priority
            // source above the built-in default. The legacy per-mod cfg and the
            // env overrides below intentionally take precedence over it.
            std::string userConfigValue;
            if (TryGetUserConfigString(kUserConfigDisplaySection, "UnderAttackAlert", userConfigValue) &&
                TryParseUnderAttackAlertModeValue(userConfigValue.c_str(), mode))
                ApplyUnderAttackAlertMode(mode, true);

            const auto configPath = GetConfigModuleDirectory() / kUnderAttackAlertConfigName;
            if (TryLoadUnderAttackAlertModeFromConfig(configPath, mode))
                ApplyUnderAttackAlertMode(mode, true);

            if (TryGetEnvUnderAttackAlertMode("OPENSHIM_UNDER_ATTACK_ALERT_MODE", mode) ||
                TryGetEnvUnderAttackAlertMode("BZR_UNDER_ATTACK_ALERT_MODE", mode))
            {
                ApplyUnderAttackAlertMode(mode, true);
            }
            else if (EnvFlagEnabled("OPENSHIM_DISABLE_UNDER_ATTACK_ALERT") ||
                     EnvFlagEnabled("BZR_DISABLE_UNDER_ATTACK_ALERT"))
            {
                ApplyUnderAttackAlertMode(UnderAttackAlertMode::None, true);
            }
            else
            {
                float envCooldown = g_UnderAttackAlertCooldownSeconds;
                if (TryGetEnvFloat("OPENSHIM_UNDER_ATTACK_ALERT_COOLDOWN", envCooldown) ||
                    TryGetEnvFloat("BZR_UNDER_ATTACK_ALERT_COOLDOWN", envCooldown) ||
                    TryGetEnvFloat("OPENSHIM_UNDER_ATTACK_ALERT_COOLDOWN_SECONDS", envCooldown))
                {
                    g_UnderAttackAlertEnabled = true;
                    g_UnderAttackAlertCooldownSeconds = ClampUnderAttackAlertCooldown(envCooldown);
                }
            }

            // Capture the fully-resolved state as the user baseline so scripted
            // (EXU bridge) overrides revert here on mission end.
            g_UnderAttackAlertBaselineMode = g_UnderAttackAlertMode;
            g_UnderAttackAlertBaselineEnabled = g_UnderAttackAlertEnabled;
            g_UnderAttackAlertBaselineCooldownSeconds = g_UnderAttackAlertCooldownSeconds;
            g_UnderAttackAlertBaselineCaptured = true;

            Log(L"[AUDIO] Under-attack alert mode=%hs enabled=%hs cooldown=%.3fs\n",
                UnderAttackAlertModeName(g_UnderAttackAlertMode),
                g_UnderAttackAlertEnabled ? "yes" : "no",
                static_cast<double>(g_UnderAttackAlertCooldownSeconds));
        }

        void RevertUnderAttackAlertToBaseline()
        {
            InitializeUnderAttackAlertConfig();  // idempotent; ensures baseline captured
            if (!g_UnderAttackAlertBaselineCaptured)
                return;
            g_UnderAttackAlertMode = g_UnderAttackAlertBaselineMode;
            g_UnderAttackAlertEnabled = g_UnderAttackAlertBaselineEnabled;
            g_UnderAttackAlertCooldownSeconds = g_UnderAttackAlertBaselineCooldownSeconds;
            g_UnderAttackAlertNextAllowedTime = 0.0f;
        }

        static bool SetUnderAttackAlertModeInternal(UnderAttackAlertMode mode, bool logChange)
        {
            InitializeUnderAttackAlertConfig();
            const bool changed =
                g_UnderAttackAlertMode != mode ||
                !g_UnderAttackAlertEnabled ||
                std::abs(g_UnderAttackAlertCooldownSeconds -
                    (mode == UnderAttackAlertMode::Minimal ? 10.0f :
                     mode == UnderAttackAlertMode::Normal ? 1.0f : 0.0f)) > 0.0001f;
            ApplyUnderAttackAlertMode(mode, true);
            if (logChange)
            {
                Log(L"[AUDIO] Under-attack alert bridge mode=%hs enabled=%hs cooldown=%.3fs\n",
                    UnderAttackAlertModeName(g_UnderAttackAlertMode),
                    g_UnderAttackAlertEnabled ? "yes" : "no",
                    static_cast<double>(g_UnderAttackAlertCooldownSeconds));
            }
            return changed;
        }

        static const char* TargetReticlePopupModeName(TargetReticlePopupMode mode)
        {
            switch (mode)
            {
            case TargetReticlePopupMode::NeutralOnly:
                return "NEUTRAL_ONLY";
            case TargetReticlePopupMode::ExplicitOnly:
                return "EXPLICIT_ONLY";
            default:
                return "DEFAULT";
            }
        }

        static TargetReticlePopupMode ClampTargetReticlePopupMode(int value)
        {
            if (value <= static_cast<int>(TargetReticlePopupMode::Default))
                return TargetReticlePopupMode::Default;
            if (value == static_cast<int>(TargetReticlePopupMode::NeutralOnly))
                return TargetReticlePopupMode::NeutralOnly;
            return TargetReticlePopupMode::ExplicitOnly;
        }

        static bool TryParseTargetReticlePopupModeValue(const char* value, TargetReticlePopupMode& outMode)
        {
            if (!value || !*value)
                return false;

            char normalized[32] = {};
            size_t out = 0;
            for (const char* cursor = value; *cursor && out + 1 < sizeof(normalized); ++cursor)
            {
                if (std::isspace(static_cast<unsigned char>(*cursor)) || *cursor == '_' || *cursor == '-')
                    continue;
                normalized[out++] = static_cast<char>(std::toupper(static_cast<unsigned char>(*cursor)));
            }
            normalized[out] = '\0';
            if (normalized[0] == '\0')
                return false;

            char* end = nullptr;
            const long parsed = std::strtol(normalized, &end, 10);
            if (end != normalized && *end == '\0')
            {
                outMode = ClampTargetReticlePopupMode(static_cast<int>(parsed));
                return true;
            }

            if (std::strcmp(normalized, "DEFAULT") == 0 || std::strcmp(normalized, "NORMAL") == 0 ||
                std::strcmp(normalized, "ON") == 0)
            {
                outMode = TargetReticlePopupMode::Default;
                return true;
            }
            if (std::strcmp(normalized, "NEUTRALONLY") == 0 || std::strcmp(normalized, "NEUTRAL") == 0)
            {
                outMode = TargetReticlePopupMode::NeutralOnly;
                return true;
            }
            if (std::strcmp(normalized, "EXPLICITONLY") == 0 || std::strcmp(normalized, "EXPLICIT") == 0)
            {
                outMode = TargetReticlePopupMode::ExplicitOnly;
                return true;
            }

            return false;
        }

        static bool TryLoadTargetReticlePopupModeFromConfig(
            const std::filesystem::path& configPath,
            TargetReticlePopupMode& outMode)
        {
            if (configPath.empty())
                return false;

            FILE* file = nullptr;
            if (fopen_s(&file, configPath.string().c_str(), "r") != 0 || !file)
                return false;

            char line[256] = {};
            bool found = false;
            while (std::fgets(line, static_cast<int>(sizeof(line)), file))
            {
                char* trimmed = TrimAsciiInPlace(line);
                if (*trimmed == '\0' || *trimmed == '#' || *trimmed == ';')
                    continue;

                char* equals = std::strchr(trimmed, '=');
                if (!equals)
                    continue;

                *equals = '\0';
                char* key = TrimAsciiInPlace(trimmed);
                char* value = TrimAsciiInPlace(equals + 1);
                if (_stricmp(key, "TargetReticlePopupMode") != 0)
                    continue;

                found = TryParseTargetReticlePopupModeValue(value, outMode);
                break;
            }

            std::fclose(file);
            return found;
        }

        static bool TryGetEnvTargetReticlePopupMode(const char* envName, TargetReticlePopupMode& outMode)
        {
            if (!envName || !*envName)
                return false;

            char value[32] = {};
            const DWORD len = GetEnvironmentVariableA(envName, value, static_cast<DWORD>(sizeof(value)));
            if (len == 0 || len >= sizeof(value))
                return false;

            return TryParseTargetReticlePopupModeValue(value, outMode);
        }

        static void ApplyTargetReticlePopupMode(TargetReticlePopupMode mode)
        {
            g_TargetReticlePopupMode = mode;
        }

        void InitializeTargetReticlePopupConfig()
        {
            if (g_TargetReticlePopupConfigInitialized)
                return;

            g_TargetReticlePopupConfigInitialized = true;
            ApplyTargetReticlePopupMode(TargetReticlePopupMode::Default);

            TargetReticlePopupMode mode = TargetReticlePopupMode::Default;

            // Global user baseline (openshim.ini [Display]) — lowest-priority
            // source above the built-in default; legacy cfg and env override it.
            std::string userConfigValue;
            if ((TryGetUserConfigString(kUserConfigDisplaySection, "TargetPolicy", userConfigValue) ||
                 TryGetUserConfigString(kUserConfigDisplaySection, "TargetReticle", userConfigValue)) &&
                TryParseTargetReticlePopupModeValue(userConfigValue.c_str(), mode))
            {
                ApplyTargetReticlePopupMode(mode);
            }

            const auto configPath = GetConfigModuleDirectory() / kUnderAttackAlertConfigName;
            if (TryLoadTargetReticlePopupModeFromConfig(configPath, mode))
                ApplyTargetReticlePopupMode(mode);

            if (TryGetEnvTargetReticlePopupMode("OPENSHIM_TARGET_RETICLE_POPUP_MODE", mode) ||
                TryGetEnvTargetReticlePopupMode("BZR_TARGET_RETICLE_POPUP_MODE", mode))
            {
                ApplyTargetReticlePopupMode(mode);
            }

            // Capture the resolved mode as the user baseline for mission reset.
            g_TargetReticlePopupBaselineMode = g_TargetReticlePopupMode;
            g_TargetReticlePopupBaselineCaptured = true;

            Log(L"[HUD] Target reticle popup mode=%hs\n",
                TargetReticlePopupModeName(g_TargetReticlePopupMode));
        }

        void RevertTargetReticlePopupToBaseline()
        {
            InitializeTargetReticlePopupConfig();  // idempotent; ensures baseline captured
            if (!g_TargetReticlePopupBaselineCaptured)
                return;
            ApplyTargetReticlePopupMode(g_TargetReticlePopupBaselineMode);
        }

        static bool SetTargetReticlePopupModeInternal(TargetReticlePopupMode mode, bool logChange)
        {
            InitializeTargetReticlePopupConfig();
            const bool changed = g_TargetReticlePopupMode != mode;
            ApplyTargetReticlePopupMode(mode);
            if (logChange)
            {
                Log(L"[HUD] Target reticle popup bridge mode=%hs\n",
                    TargetReticlePopupModeName(g_TargetReticlePopupMode));
            }
            return changed;
        }

        static float GetGameObjectPlayerShotTime(void* objectPtr)
        {
            if (!objectPtr)
                return kSuppressedRecentHitTime;

            __try
            {
                const auto* bytes = reinterpret_cast<const uint8_t*>(objectPtr);
                return *reinterpret_cast<const float*>(bytes + kGameObjectPlayerShotOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return kSuppressedRecentHitTime;
            }
        }
    }

    using namespace Hooks;

    bool SetUnderAttackAlertModeFromBridge(int mode)
    {
        return SetUnderAttackAlertModeInternal(ClampUnderAttackAlertMode(mode), true);
    }

    bool SetTargetReticlePopupModeFromBridge(int mode)
    {
        return SetTargetReticlePopupModeInternal(ClampTargetReticlePopupMode(mode), true);
    }

    float __fastcall TargetReticlePopupRecentHitGetterHook(void* objectPtr, void* /*edx*/)
    {
        InitializeTargetReticlePopupConfig();

        const float playerShotTime = GetGameObjectPlayerShotTime(objectPtr);
        switch (g_TargetReticlePopupMode)
        {
        case TargetReticlePopupMode::ExplicitOnly:
            return kSuppressedRecentHitTime;
        case TargetReticlePopupMode::NeutralOnly:
            return IsNeutralTeamObject(objectPtr) ? kSuppressedRecentHitTime : playerShotTime;
        case TargetReticlePopupMode::Default:
        default:
            return playerShotTime;
        }
    }

    void __cdecl HandleUnderAttackAlert(float currentTime)
    {
        InitializeUnderAttackAlertConfig();
        if (!g_UnderAttackAlertEnabled)
            return;

        if (currentTime <= g_UnderAttackAlertNextAllowedTime)
            return;

        if (g_BzrFn_PlayGlobalSound && kUnderAttackAlertSoundAddr != 0)
        {
            const char* sound = reinterpret_cast<const char*>(kUnderAttackAlertSoundAddr);
            g_BzrFn_PlayGlobalSound(sound, 0, 0, 0);
        }

        const float minSpacing = 1.0f;
        const float nextDelay =
            (std::max)(g_UnderAttackAlertCooldownSeconds, minSpacing);
        g_UnderAttackAlertNextAllowedTime = currentTime + nextDelay;
    }
}
