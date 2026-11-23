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
// A few patch files still build as C++14 (no <filesystem>); they get the
// narrow-API path below instead of the layout header.
#if defined(_MSVC_LANG) && _MSVC_LANG >= 201703L
#include "openshim_layout.h"
#define OPENSHIM_DIAGNOSTIC_SWITCH_HAS_LAYOUT 1
#endif

#include <windows.h>

#include <cstring>
#include <string>

namespace BZROpenShim
{
namespace DiagnosticSwitch
{
    // openshim\openshim.ini under the game folder (see openshim_layout.h,
    // which also moves an old root openshim.ini there on first use).
    inline std::string OpenShimIniPath()
    {
#if defined(OPENSHIM_DIAGNOSTIC_SWITCH_HAS_LAYOUT)
        return Layout::OpenShimIniPathA();
#else
        // C++14 readers: the plugin moves the old root ini at startup, so
        // only fall back to it when openshim\openshim.ini is absent.
        char path[MAX_PATH] = {};
        const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
        if (length == 0 || length >= MAX_PATH) return "openshim\\openshim.ini";
        char* slash = std::strrchr(path, '\\');
        if (!slash) return "openshim\\openshim.ini";
        *(slash + 1) = '\0';
        const std::string root(path);
        const std::string moved = root + "openshim\\openshim.ini";
        if (GetFileAttributesA(moved.c_str()) != INVALID_FILE_ATTRIBUTES) return moved;
        const std::string legacy = root + "openshim.ini";
        if (GetFileAttributesA(legacy.c_str()) != INVALID_FILE_ATTRIBUTES) return legacy;
        return moved;
#endif
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
