#include "bzloader_bootstrap.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <string>

namespace
{
    using LoaderInitializeFn = int32_t(__cdecl*)();
    using LoaderShutdownFn = void(__cdecl*)();

    HMODULE g_LoaderModule = nullptr;
    LoaderShutdownFn g_LoaderShutdown = nullptr;

    std::wstring GetProxyDirectory()
    {
        HMODULE self = nullptr;
        if (!GetModuleHandleExW(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                    GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                reinterpret_cast<LPCWSTR>(&GetProxyDirectory),
                &self))
            return {};

        wchar_t path[MAX_PATH] = {};
        const DWORD length = GetModuleFileNameW(self, path, MAX_PATH);
        if (length == 0 || length >= MAX_PATH) return {};
        std::wstring directory(path, length);
        const size_t slash = directory.find_last_of(L"\\/");
        if (slash == std::wstring::npos) return {};
        directory.resize(slash + 1);
        return directory;
    }
}

namespace BZROpenShim
{
    bool InitializeBZLoader()
    {
        if (g_LoaderModule) return true;

        const std::wstring directory = GetProxyDirectory();
        if (directory.empty())
        {
            LogShimA(LogLevel::Error, "bzloader", "Could not resolve the proxy installation directory");
            return false;
        }

        const std::wstring loaderPath = directory + L"bzloader.dll";
        g_LoaderModule = LoadLibraryExW(
            loaderPath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
        if (!g_LoaderModule)
        {
            LogShimA(LogLevel::Error, "bzloader",
                     "Could not load bzloader.dll from the proxy directory (err=%lu)",
                     GetLastError());
            return false;
        }

        const auto initialize = reinterpret_cast<LoaderInitializeFn>(
            GetProcAddress(g_LoaderModule, "BZLoader_Initialize"));
        g_LoaderShutdown = reinterpret_cast<LoaderShutdownFn>(
            GetProcAddress(g_LoaderModule, "BZLoader_Shutdown"));
        if (!initialize || !g_LoaderShutdown)
        {
            LogShimA(LogLevel::Error, "bzloader", "bzloader.dll is missing required exports");
            FreeLibrary(g_LoaderModule);
            g_LoaderModule = nullptr;
            g_LoaderShutdown = nullptr;
            return false;
        }

        if (!initialize())
        {
            LogShimA(LogLevel::Error, "bzloader", "BZLoader initialization failed");
            FreeLibrary(g_LoaderModule);
            g_LoaderModule = nullptr;
            g_LoaderShutdown = nullptr;
            return false;
        }

        LogShimA(LogLevel::Info, "bzloader", "BZLoader initialized outside loader lock");
        return true;
    }

    void ShutdownBZLoader()
    {
        if (!g_LoaderModule) return;
        if (g_LoaderShutdown) g_LoaderShutdown();
        FreeLibrary(g_LoaderModule);
        g_LoaderModule = nullptr;
        g_LoaderShutdown = nullptr;
    }
}
