#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
    std::wstring ExecutableDirectory()
    {
        wchar_t path[MAX_PATH] = {};
        const DWORD length = GetModuleFileNameW(nullptr, path, MAX_PATH);
        if (length == 0 || length >= MAX_PATH) return {};
        std::wstring result(path, length);
        const size_t slash = result.find_last_of(L"\\/");
        if (slash == std::wstring::npos) return {};
        result.resize(slash);
        return result;
    }
}

int wmain()
{
    const std::wstring directory = ExecutableDirectory();
    const std::wstring loaderPath = directory + L"\\bzloader.dll";
    HMODULE loader = LoadLibraryExW(
        loaderPath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (!loader)
    {
        std::wcerr << L"could not load " << loaderPath << L" error=" << GetLastError() << L'\n';
        return 1;
    }

    using InitializeFn = int32_t(__cdecl*)();
    using ShutdownFn = void(__cdecl*)();
    const auto initialize = reinterpret_cast<InitializeFn>(
        GetProcAddress(loader, "BZLoader_Initialize"));
    const auto shutdown = reinterpret_cast<ShutdownFn>(
        GetProcAddress(loader, "BZLoader_Shutdown"));
    if (!initialize || !shutdown || !initialize())
    {
        std::cerr << "loader lifecycle exports failed\n";
        return 2;
    }
    shutdown();

    std::ifstream log(directory + L"\\bzloader.log", std::ios::binary);
    std::ostringstream contents;
    contents << log.rdbuf();
    const std::string text = contents.str();
    if (text.find("Lifecycle test plugin loaded") == std::string::npos ||
        text.find("Lifecycle test plugin shut down") == std::string::npos)
    {
        std::cerr << "plugin lifecycle messages were not observed\n";
        return 3;
    }

    std::cout << "bzloader host integration test passed\n";
    return 0;
}
