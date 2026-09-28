#include "openshim_env_config.h"
#include "openshim_env_mapping.h"

// This translation unit is itself compiled with openshim_env_config.h forced in.
// Undefine the redirect here so the final fallback reaches the real Win32 API.
#undef GetEnvironmentVariableA

#include <cstring>
#include <filesystem>
#include <string>

// The Win32 half of the redirect: the plugin directory, GetPrivateProfileStringA
// and the real process environment. What a name maps to, and the order the
// sources are consulted in, live in openshim_env_mapping.cpp so the unit tests
// can drive them without a plugin directory.

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
}

DWORD WINAPI OpenShimGetEnvironmentVariableA(LPCSTR name, LPSTR buffer, DWORD size)
{
    using namespace BZROpenShim::EnvConfig;

    const EnvironmentReader processEnvironment = [](const char* envName, char* envBuffer, uint32_t envSize)
    {
        return static_cast<uint32_t>(::GetEnvironmentVariableA(envName, envBuffer, envSize));
    };

    if (!name || !*name)
        return ::GetEnvironmentVariableA(name, buffer, size);

    const auto moduleDir = GetModuleDirectory();
    if (moduleDir.empty())
        return GetEnvironmentValue(name, buffer, size, nullptr, processEnvironment);

    const IniReader ini = [&moduleDir](IniFile file, const char* section, const char* key, std::string& out)
    {
        return TryReadIniValue(moduleDir / IniFileName(file), section, key, out);
    };
    return GetEnvironmentValue(name, buffer, size, &ini, processEnvironment);
}
