#include "openshim_env_config.h"
#include "openshim_env_mapping.h"

// This translation unit is itself compiled with openshim_env_config.h forced in.
// Undefine the redirect here so the final fallback reaches the real Win32 API.
#undef GetEnvironmentVariableA

#include <cstring>
#include <filesystem>
#include <string>
#include <unordered_map>

// The Win32 half of the redirect: the plugin directory, GetPrivateProfileStringA
// and the real process environment. What a name maps to, and the order the
// sources are consulted in, live in openshim_env_mapping.cpp so the unit tests
// can drive them without a plugin directory.

namespace
{
    constexpr char kUnsetValue[] = "\x01__openshim_unset__";

    std::filesystem::path ComputeModuleDirectory()
    {
        char path[MAX_PATH] = {};
        const DWORD length = GetModuleFileNameA(nullptr, path, static_cast<DWORD>(sizeof(path)));
        if (length == 0 || length >= sizeof(path))
            return {};
        return std::filesystem::path(path).parent_path();
    }

    const std::filesystem::path& GetModuleDirectory()
    {
        static const std::filesystem::path s_directory = ComputeModuleDirectory();
        return s_directory;
    }

    bool ReadIniValueFromDisk(const std::filesystem::path& path,
                              const char* section,
                              const char* key,
                              std::string& out)
    {
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

    // Every redirected GetEnvironmentVariableA used to reach
    // GetPrivateProfileStringA, which opens and parses the file. Uncached
    // flag checks on damage and kill paths made that ~4.5 ms of an 80-craft
    // volley frame. Answers are kept per (file, section, key); a file's cache
    // is dropped when its write time or size changes (re-checked at most
    // every 250 ms) or when OpenShim itself rewrites it.
    struct IniFileStamp
    {
        ULONGLONG lastWrite = 0;
        ULONGLONG size = 0;
        bool exists = false;

        bool operator==(const IniFileStamp& other) const
        {
            return lastWrite == other.lastWrite && size == other.size && exists == other.exists;
        }
    };

    struct IniFileCache
    {
        IniFileStamp stamp;
        ULONGLONG checkedTick = 0;
        bool valid = false;
        std::unordered_map<std::string, std::pair<bool, std::string>> values;
    };

    constexpr ULONGLONG kIniStampRecheckMs = 250;

    SRWLOCK g_IniCacheLock = SRWLOCK_INIT;
    std::unordered_map<std::string, IniFileCache> g_IniCache;

    IniFileStamp ReadIniFileStamp(const std::filesystem::path& path)
    {
        IniFileStamp stamp;
        WIN32_FILE_ATTRIBUTE_DATA data = {};
        if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &data))
            return stamp;
        stamp.exists = true;
        stamp.lastWrite = (static_cast<ULONGLONG>(data.ftLastWriteTime.dwHighDateTime) << 32) |
                          data.ftLastWriteTime.dwLowDateTime;
        stamp.size = (static_cast<ULONGLONG>(data.nFileSizeHigh) << 32) | data.nFileSizeLow;
        return stamp;
    }

    bool TryReadIniValue(const std::filesystem::path& path,
                         const char* section,
                         const char* key,
                         std::string& out)
    {
        if (path.empty() || !section || !key)
            return false;

        std::string valueKey(section);
        valueKey.push_back('|');
        valueKey.append(key);

        AcquireSRWLockExclusive(&g_IniCacheLock);
        IniFileCache& file = g_IniCache[path.string()];
        const ULONGLONG now = GetTickCount64();
        if (!file.valid || now - file.checkedTick >= kIniStampRecheckMs)
        {
            const IniFileStamp stamp = ReadIniFileStamp(path);
            if (!file.valid || !(stamp == file.stamp))
                file.values.clear();
            file.stamp = stamp;
            file.checkedTick = now;
            file.valid = true;
        }

        const auto cached = file.values.find(valueKey);
        if (cached != file.values.end())
        {
            const bool present = cached->second.first;
            if (present)
                out = cached->second.second;
            ReleaseSRWLockExclusive(&g_IniCacheLock);
            return present;
        }
        ReleaseSRWLockExclusive(&g_IniCacheLock);

        std::string value;
        const bool present = ReadIniValueFromDisk(path, section, key, value);

        AcquireSRWLockExclusive(&g_IniCacheLock);
        g_IniCache[path.string()].values.insert_or_assign(std::move(valueKey), std::make_pair(present, value));
        ReleaseSRWLockExclusive(&g_IniCacheLock);

        if (present)
            out = std::move(value);
        return present;
    }
}

void OpenShimInvalidateEnvIniCache()
{
    AcquireSRWLockExclusive(&g_IniCacheLock);
    g_IniCache.clear();
    ReleaseSRWLockExclusive(&g_IniCacheLock);
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

    const std::filesystem::path& moduleDir = GetModuleDirectory();
    if (moduleDir.empty())
        return GetEnvironmentValue(name, buffer, size, nullptr, processEnvironment);

    const IniReader ini = [&moduleDir](IniFile file, const char* section, const char* key, std::string& out)
    {
        return TryReadIniValue(moduleDir / IniFileName(file), section, key, out);
    };
    return GetEnvironmentValue(name, buffer, size, &ini, processEnvironment);
}
