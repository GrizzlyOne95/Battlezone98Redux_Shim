#include "bzloader_catalog.h"
#include "bzloader_plugin.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <bcrypt.h>

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#pragma comment(lib, "bcrypt.lib")

namespace
{
    struct PluginModule
    {
        HMODULE module = nullptr;
        std::wstring path;
        BZPluginInfo info = {};
        BZPluginLoadFn load = nullptr;
        BZPluginShutdownFn shutdown = nullptr;
        bool loaded = false;
    };

    HMODULE g_Module = nullptr;
    std::wstring g_LoaderDirectory;
    std::wstring g_ExecutablePath;
    std::wstring g_LogPath;
    char g_ExecutableBuildHint[64] = {};
    uint32_t g_ExecutableTimeDateStamp = 0;
    uint32_t g_ExecutableSizeOfImage = 0;
    // bzloader.log is append-only across runs, so every line carries the id of
    // the run that wrote it. Without it a reader -- including the host
    // integration test -- cannot tell this run's lifecycle from a previous
    // run's, and a broken run inherits an old run's success.
    char g_SessionId[24] = {};
    char g_ExecutableSha256[65] = {};
    bool g_ExecutableSha256Attempted = false;
    BZHostApi g_Host = {};
    std::vector<PluginModule> g_Plugins;
    SRWLOCK g_StateLock = SRWLOCK_INIT;
    SRWLOCK g_LogLock = SRWLOCK_INIT;
    SRWLOCK g_ShaLock = SRWLOCK_INIT;
    bool g_Initialized = false;

    const char* LevelName(uint32_t level)
    {
        switch (level)
        {
        case BZ_HOST_LOG_DEBUG: return "DEBUG";
        case BZ_HOST_LOG_WARNING: return "WARN";
        case BZ_HOST_LOG_ERROR: return "ERROR";
        default: return "INFO";
        }
    }

    void BuildSessionId()
    {
        LARGE_INTEGER counter = {};
        QueryPerformanceCounter(&counter);
        FILETIME now = {};
        GetSystemTimeAsFileTime(&now);
        const uint64_t stamp =
            (static_cast<uint64_t>(now.dwHighDateTime) << 32) | now.dwLowDateTime;
        const uint64_t mixed =
            stamp ^ (static_cast<uint64_t>(counter.QuadPart) << 16) ^
            (static_cast<uint64_t>(GetCurrentProcessId()) << 48);
        _snprintf_s(g_SessionId, _TRUNCATE, "%016llX",
                    static_cast<unsigned long long>(mixed));
    }

    void WriteLog(uint32_t level, const char* component, const char* message)
    {
        char line[2048] = {};
        SYSTEMTIME now = {};
        GetLocalTime(&now);
        _snprintf_s(line, _TRUNCATE,
                    "%04u-%02u-%02u %02u:%02u:%02u.%03u [s=%s] [%s] [%s] %s\r\n",
                    now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute,
                    now.wSecond, now.wMilliseconds,
                    g_SessionId[0] ? g_SessionId : "----------------",
                    LevelName(level), component ? component : "host",
                    message ? message : "");
        AcquireSRWLockExclusive(&g_LogLock);
        OutputDebugStringA(line);

        if (g_LogPath.empty())
        {
            ReleaseSRWLockExclusive(&g_LogLock);
            return;
        }
        FILE* file = nullptr;
        if (_wfopen_s(&file, g_LogPath.c_str(), L"ab") == 0 && file)
        {
            fwrite(line, 1, strlen(line), file);
            fclose(file);
        }
        ReleaseSRWLockExclusive(&g_LogLock);
    }

    void Logf(uint32_t level, const char* component, const char* format, ...)
    {
        char message[1536] = {};
        va_list args;
        va_start(args, format);
        _vsnprintf_s(message, _TRUNCATE, format, args);
        va_end(args);
        WriteLog(level, component, message);
    }

    void BZLOADER_CALL HostLog(
        uint32_t level, const char* component, const char* message)
    {
        WriteLog(level, component, message);
    }

    bool ComputeFileSha256(const std::wstring& path, char (&outHex)[65])
    {
        HANDLE file = CreateFileW(path.c_str(), GENERIC_READ,
                                  FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                                  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file == INVALID_HANDLE_VALUE) return false;

        BCRYPT_ALG_HANDLE algorithm = nullptr;
        BCRYPT_HASH_HANDLE hash = nullptr;
        std::vector<UCHAR> hashObject;
        UCHAR digest[32] = {};
        bool ok = false;

        do
        {
            if (!BCRYPT_SUCCESS(BCryptOpenAlgorithmProvider(
                    &algorithm, BCRYPT_SHA256_ALGORITHM, nullptr, 0)))
                break;

            DWORD objectSize = 0;
            DWORD produced = 0;
            if (!BCRYPT_SUCCESS(BCryptGetProperty(
                    algorithm, BCRYPT_OBJECT_LENGTH,
                    reinterpret_cast<PUCHAR>(&objectSize), sizeof(objectSize),
                    &produced, 0)))
                break;

            hashObject.resize(objectSize);
            if (!BCRYPT_SUCCESS(BCryptCreateHash(algorithm, &hash, hashObject.data(),
                                                 objectSize, nullptr, 0, 0)))
                break;

            std::vector<UCHAR> buffer(64 * 1024);
            bool readFailed = false;
            for (;;)
            {
                DWORD read = 0;
                if (!ReadFile(file, buffer.data(),
                              static_cast<DWORD>(buffer.size()), &read, nullptr))
                {
                    readFailed = true;
                    break;
                }
                if (read == 0) break;
                if (!BCRYPT_SUCCESS(BCryptHashData(hash, buffer.data(), read, 0)))
                {
                    readFailed = true;
                    break;
                }
            }
            if (readFailed) break;

            if (!BCRYPT_SUCCESS(BCryptFinishHash(hash, digest, sizeof(digest), 0)))
                break;

            for (size_t i = 0; i < sizeof(digest); ++i)
                _snprintf_s(outHex + i * 2, 3, _TRUNCATE, "%02x", digest[i]);
            ok = true;
        } while (false);

        if (hash) BCryptDestroyHash(hash);
        if (algorithm) BCryptCloseAlgorithmProvider(algorithm, 0);
        CloseHandle(file);
        return ok;
    }

    // Lazy: only a plugin that pins an exact image pays for reading the whole
    // executable, and it is computed at most once per process either way.
    const char* BZLOADER_CALL HostExecutableSha256()
    {
        AcquireSRWLockExclusive(&g_ShaLock);
        if (!g_ExecutableSha256Attempted)
        {
            g_ExecutableSha256Attempted = true;
            if (!ComputeFileSha256(g_ExecutablePath, g_ExecutableSha256))
            {
                g_ExecutableSha256[0] = '\0';
                Logf(BZ_HOST_LOG_WARNING, "host",
                     "Could not compute the executable SHA-256 (err=%lu); any "
                     "plugin that pins an exact image will be refused",
                     GetLastError());
            }
            else
            {
                Logf(BZ_HOST_LOG_INFO, "host", "Executable SHA-256 %s",
                     g_ExecutableSha256);
            }
        }
        const char* result = g_ExecutableSha256[0] ? g_ExecutableSha256 : nullptr;
        ReleaseSRWLockExclusive(&g_ShaLock);
        return result;
    }

    int32_t SafeQuery(BZPluginQueryFn query, BZPluginInfo* info, bool& raised)
    {
        __try
        {
            return query(BZLOADER_ABI_VERSION, info);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            raised = true;
            return 0;
        }
    }

    int32_t SafeLoad(BZPluginLoadFn load, const BZHostApi* host, bool& raised)
    {
        __try
        {
            return load(host);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            raised = true;
            return 0;
        }
    }

    void SafeShutdown(BZPluginShutdownFn shutdown, bool& raised)
    {
        __try
        {
            shutdown();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            raised = true;
        }
    }

    HMODULE SafeLoadLibrary(const wchar_t* path, bool& raised)
    {
        __try
        {
            return LoadLibraryExW(path, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            raised = true;
            return nullptr;
        }
    }

    std::wstring ModulePath(HMODULE module)
    {
        wchar_t path[32768] = {};
        const DWORD length = GetModuleFileNameW(module, path, _countof(path));
        if (length == 0 || length >= _countof(path)) return {};
        return std::wstring(path, length);
    }

    std::wstring ParentDirectory(const std::wstring& path)
    {
        const size_t slash = path.find_last_of(L"\\/");
        return slash == std::wstring::npos ? std::wstring() : path.substr(0, slash);
    }

    uint32_t DetectGame(const std::wstring& executablePath)
    {
        const size_t slash = executablePath.find_last_of(L"\\/");
        const wchar_t* name = executablePath.c_str() +
            (slash == std::wstring::npos ? 0 : slash + 1);
        if (_wcsicmp(name, L"Battlezone98Redux.exe") == 0)
            return BZ_GAME_BATTLEZONE_98_REDUX;
        if (_wcsicmp(name, L"bzone.exe") == 0)
            return BZ_GAME_BATTLEZONE_15;
        return BZ_GAME_UNKNOWN;
    }

    void BuildExecutableHint()
    {
        const auto base = reinterpret_cast<const uint8_t*>(GetModuleHandleW(nullptr));
        if (!base)
        {
            strcpy_s(g_ExecutableBuildHint, "unknown");
            return;
        }

        __try
        {
            const auto dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
            const auto nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE || nt->Signature != IMAGE_NT_SIGNATURE)
            {
                strcpy_s(g_ExecutableBuildHint, "unknown");
                return;
            }
            g_ExecutableTimeDateStamp = nt->FileHeader.TimeDateStamp;
            g_ExecutableSizeOfImage = nt->OptionalHeader.SizeOfImage;
            _snprintf_s(g_ExecutableBuildHint, _TRUNCATE, "pe-%08X-%08X",
                        g_ExecutableTimeDateStamp, g_ExecutableSizeOfImage);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            g_ExecutableTimeDateStamp = 0;
            g_ExecutableSizeOfImage = 0;
            strcpy_s(g_ExecutableBuildHint, "unknown");
        }
    }

    bool EndsWithDll(const wchar_t* name)
    {
        const size_t length = name ? wcslen(name) : 0;
        return length >= 4 && _wcsicmp(name + length - 4, L".dll") == 0;
    }

    std::vector<std::wstring> DiscoverPluginPaths()
    {
        std::vector<std::wstring> paths;
        const std::wstring directory = BZLoader::GetPluginDirectory(ModulePath(g_Module));
        const std::wstring pattern = directory + L"\\*.dll";
        WIN32_FIND_DATAW data = {};
        HANDLE find = FindFirstFileW(pattern.c_str(), &data);
        if (find == INVALID_HANDLE_VALUE)
        {
            const DWORD error = GetLastError();
            if (error == ERROR_FILE_NOT_FOUND || error == ERROR_PATH_NOT_FOUND)
                Logf(BZ_HOST_LOG_INFO, "discovery", "No plugins directory or DLLs found");
            else
                Logf(BZ_HOST_LOG_ERROR, "discovery", "Plugin enumeration failed (err=%lu)", error);
            return paths;
        }

        do
        {
            if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 &&
                EndsWithDll(data.cFileName))
                paths.push_back(directory + L"\\" + data.cFileName);
        } while (FindNextFileW(find, &data));
        FindClose(find);

        std::sort(paths.begin(), paths.end(), [](std::wstring left, std::wstring right) {
            std::transform(left.begin(), left.end(), left.begin(), towlower);
            std::transform(right.begin(), right.end(), right.begin(), towlower);
            return left < right;
        });
        return paths;
    }

    void RejectPlugin(PluginModule& plugin, const char* reason)
    {
        Logf(BZ_HOST_LOG_WARNING, "discovery", "Skipping plugin %ls: %s",
             plugin.path.c_str(), reason);
        if (plugin.module) FreeLibrary(plugin.module);
        plugin.module = nullptr;
    }

    bool QueryPlugin(const std::wstring& path, PluginModule& result)
    {
        result.path = path;
        bool loadLibraryRaised = false;
        result.module = SafeLoadLibrary(path.c_str(), loadLibraryRaised);
        if (!result.module)
        {
            Logf(BZ_HOST_LOG_WARNING, "discovery",
                 "Skipping DLL that could not load: %ls (%s; err=%lu)",
                 path.c_str(), loadLibraryRaised ? "structured exception" : "loader failure",
                 GetLastError());
            return false;
        }

        const auto query = reinterpret_cast<BZPluginQueryFn>(
            GetProcAddress(result.module, "BZPlugin_Query"));
        result.load = reinterpret_cast<BZPluginLoadFn>(
            GetProcAddress(result.module, "BZPlugin_Load"));
        result.shutdown = reinterpret_cast<BZPluginShutdownFn>(
            GetProcAddress(result.module, "BZPlugin_Shutdown"));
        if (!query || !result.load || !result.shutdown)
        {
            RejectPlugin(result, "required plugin exports are missing");
            return false;
        }

        // Zeroed, then handed to the plugin as a capacity. Anything the plugin
        // is too old to fill stays zero rather than reading back as whatever
        // happened to be in the host's own buffer.
        result.info = {};
        result.info.structSize = sizeof(result.info);
        bool queryRaised = false;
        const int32_t queried = SafeQuery(query, &result.info, queryRaised);
        if (queryRaised)
        {
            RejectPlugin(result, "BZPlugin_Query raised a structured exception");
            return false;
        }
        if (!queried)
        {
            RejectPlugin(result, "BZPlugin_Query rejected the host");
            return false;
        }

        std::string reason;
        if (BZLoader::ValidateMetadata(g_Host, result.info, reason) !=
            BZLoader::MetadataStatus::Ok)
        {
            RejectPlugin(result, reason.c_str());
            return false;
        }
        return true;
    }

    void DiscoverAndLoadPlugins()
    {
        std::vector<PluginModule> candidates;
        for (const auto& path : DiscoverPluginPaths())
        {
            PluginModule candidate;
            if (!QueryPlugin(path, candidate)) continue;

            std::vector<BZLoader::CatalogEntry> catalog;
            catalog.reserve(candidates.size());
            for (const auto& existing : candidates)
                catalog.push_back({existing.path, existing.info.pluginId,
                                   BZLoader::PluginLoadPriority(existing.info)});
            if (BZLoader::HasDuplicatePluginId(catalog, candidate.info.pluginId))
            {
                RejectPlugin(candidate, "duplicate plugin ID");
                continue;
            }
            candidates.push_back(std::move(candidate));
        }

        std::sort(candidates.begin(), candidates.end(),
                  [](const PluginModule& left, const PluginModule& right) {
            return BZLoader::CatalogLess(
                {left.path, left.info.pluginId, BZLoader::PluginLoadPriority(left.info)},
                {right.path, right.info.pluginId, BZLoader::PluginLoadPriority(right.info)});
        });

        for (auto& plugin : candidates)
        {
            bool loadRaised = false;
            const int32_t loaded = SafeLoad(plugin.load, &g_Host, loadRaised);
            if (loadRaised)
            {
                Logf(BZ_HOST_LOG_ERROR, plugin.info.pluginId,
                     "BZPlugin_Load raised a structured exception");
            }
            if (!loaded)
            {
                RejectPlugin(plugin, "BZPlugin_Load failed");
                continue;
            }
            plugin.loaded = true;
            Logf(BZ_HOST_LOG_INFO, plugin.info.pluginId,
                 "Loaded %s %s (priority=%d)", plugin.info.pluginName,
                 plugin.info.pluginVersion, BZLoader::PluginLoadPriority(plugin.info));
            const char* dependencies = BZLoader::PluginDependencies(plugin.info);
            if (dependencies && *dependencies)
                Logf(BZ_HOST_LOG_INFO, plugin.info.pluginId,
                     "Declared dependencies (informational in ABI v1): %s", dependencies);
            const char* conflicts = BZLoader::PluginConflicts(plugin.info);
            if (conflicts && *conflicts)
                Logf(BZ_HOST_LOG_INFO, plugin.info.pluginId,
                     "Declared conflicts (informational in ABI v1): %s", conflicts);
            g_Plugins.push_back(std::move(plugin));
        }
    }
}

extern "C" __declspec(dllexport) int32_t __cdecl BZLoader_Initialize()
{
    AcquireSRWLockExclusive(&g_StateLock);
    if (g_Initialized)
    {
        ReleaseSRWLockExclusive(&g_StateLock);
        return 1;
    }

    const std::wstring loaderPath = ModulePath(g_Module);
    g_LoaderDirectory = ParentDirectory(loaderPath);
    g_ExecutablePath = ModulePath(nullptr);
    if (loaderPath.empty() || g_LoaderDirectory.empty() || g_ExecutablePath.empty())
    {
        ReleaseSRWLockExclusive(&g_StateLock);
        return 0;
    }
    g_LogPath = g_LoaderDirectory + L"\\bzloader.log";
    BuildSessionId();
    BuildExecutableHint();
    g_Host = {sizeof(g_Host), BZLOADER_ABI_VERSION, BZLOADER_VERSION,
              DetectGame(g_ExecutablePath), g_LoaderDirectory.c_str(),
              g_ExecutablePath.c_str(), g_ExecutableBuildHint, HostLog,
              g_ExecutableTimeDateStamp, g_ExecutableSizeOfImage,
              HostExecutableSha256};
    g_Initialized = true;
    Logf(BZ_HOST_LOG_INFO, "host",
         "BZLoader %u starting; ABI=%u buildHint=%s game=%u",
         BZLOADER_VERSION, BZLOADER_ABI_VERSION, g_ExecutableBuildHint, g_Host.gameId);
    if (g_Host.gameId == BZ_GAME_UNKNOWN)
        Logf(BZ_HOST_LOG_WARNING, "host",
             "Host executable %ls was not recognised; only plugins declaring "
             "BZ_GAME_MASK_ANY will be loaded",
             g_ExecutablePath.c_str());
    DiscoverAndLoadPlugins();
    ReleaseSRWLockExclusive(&g_StateLock);
    return 1;
}

// The id stamped into every line this run writes to the append-only log.
// Empty until BZLoader_Initialize has run.
extern "C" __declspec(dllexport) const char* __cdecl BZLoader_GetSessionId()
{
    return g_SessionId;
}

extern "C" __declspec(dllexport) void __cdecl BZLoader_Shutdown()
{
    AcquireSRWLockExclusive(&g_StateLock);
    if (!g_Initialized)
    {
        ReleaseSRWLockExclusive(&g_StateLock);
        return;
    }

    for (auto it = g_Plugins.rbegin(); it != g_Plugins.rend(); ++it)
    {
        bool shutdownRaised = false;
        SafeShutdown(it->shutdown, shutdownRaised);
        if (shutdownRaised)
        {
            Logf(BZ_HOST_LOG_ERROR, it->info.pluginId,
                 "BZPlugin_Shutdown raised a structured exception");
        }
        it->loaded = false;
    }
    // Phase 1 deliberately does not FreeLibrary successfully loaded plugins.
    // A plugin may own workers or trampolines, and hot unloading is unsupported.
    g_Plugins.clear();
    Logf(BZ_HOST_LOG_INFO, "host", "BZLoader shutdown complete");
    g_Initialized = false;
    ReleaseSRWLockExclusive(&g_StateLock);
}

BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        g_Module = module;
        DisableThreadLibraryCalls(module);
    }
    return TRUE;
}
