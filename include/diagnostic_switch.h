#pragma once

// The opt-in gate shared by OpenShim's diagnostic instruments (FXAA, scene
// depth, colorspace and terrain probes, the walker and pilot traces).
//
// An environment variable wins when it is set: its value is read with
// BoolToken::IsTruthy, so any non-blank value other than a false word turns
// the instrument on. Otherwise `[section] key` in openshim.ini is read as an
// integer, and 0 or absent leaves it off.
//
// Each instrument used to carry its own copy of this gate and of the ini path
// (audit P2-3). Their truthy readers disagreed: the scene-depth copy looked
// only at the first letter, so OPENSHIM_..=off switched it on.
//
// Windows-only. GetEnvironmentVariableA here is the forced-include redirect
// from openshim_env_config.h, so [Environment] entries in openshim.ini count
// as set variables, the same as in each copy it replaces.

#include "bool_token.h"

#include <windows.h>

#include <cstring>
#include <string>

namespace BZROpenShim
{
namespace DiagnosticSwitch
{
    // openshim.ini beside the game executable, or a bare "openshim.ini"
    // (relative to the working directory) when the executable path is not
    // available.
    inline std::string OpenShimIniPath()
    {
        char path[MAX_PATH] = {};
        const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
        if (length == 0 || length >= MAX_PATH)
            return "openshim.ini";

        char* slash = std::strrchr(path, '\\');
        if (!slash)
            return "openshim.ini";
        *(slash + 1) = '\0';
        return std::string(path) + "openshim.ini";
    }

    inline bool Requested(const char* environmentName, const char* iniSection, const char* iniKey)
    {
        char value[64] = {};
        const DWORD length = GetEnvironmentVariableA(
            environmentName, value, static_cast<DWORD>(sizeof(value)));
        if (length > 0 && length < sizeof(value))
            return BoolToken::IsTruthy(value, length);

        const std::string iniPath = OpenShimIniPath();
        return GetPrivateProfileIntA(iniSection, iniKey, 0, iniPath.c_str()) != 0;
    }
}
}
