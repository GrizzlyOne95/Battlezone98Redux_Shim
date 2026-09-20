// Native BZLoader lifecycle test:
//   host -> bzloader.dll -> plugins/bzloader_test_plugin.dll -> Load -> Shutdown
//
// bzloader.log is append-only across runs, so searching the whole file lets a
// previous successful run satisfy a later broken one. This validates only the
// lines stamped with the session id of the run it just started, and deletes
// any existing log first so a locked or undeletable log is itself reported.

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

    std::vector<std::string> ReadSessionLines(
        const std::wstring& logPath, const std::string& sessionId)
    {
        std::vector<std::string> lines;
        std::ifstream log(logPath, std::ios::binary);
        const std::string marker = "[s=" + sessionId + "]";
        std::string line;
        while (std::getline(log, line))
        {
            if (line.find(marker) != std::string::npos) lines.push_back(line);
        }
        return lines;
    }

    bool Contains(const std::vector<std::string>& lines, const char* needle)
    {
        for (const auto& line : lines)
        {
            if (line.find(needle) != std::string::npos) return true;
        }
        return false;
    }
}

int wmain()
{
    const std::wstring directory = ExecutableDirectory();
    const std::wstring loaderPath = directory + L"\\bzloader.dll";
    const std::wstring logPath = directory + L"\\bzloader.log";

    // Start from no log at all, so a stale file cannot contribute anything and
    // an undeletable one fails loudly instead of silently passing the run.
    if (!DeleteFileW(logPath.c_str()) && GetLastError() != ERROR_FILE_NOT_FOUND)
    {
        std::wcerr << L"could not clear " << logPath << L" error=" << GetLastError() << L'\n';
        return 1;
    }

    HMODULE loader = LoadLibraryExW(
        loaderPath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (!loader)
    {
        std::wcerr << L"could not load " << loaderPath << L" error=" << GetLastError() << L'\n';
        return 1;
    }

    using InitializeFn = int32_t(__cdecl*)();
    using ShutdownFn = void(__cdecl*)();
    using SessionIdFn = const char*(__cdecl*)();
    const auto initialize = reinterpret_cast<InitializeFn>(
        GetProcAddress(loader, "BZLoader_Initialize"));
    const auto shutdown = reinterpret_cast<ShutdownFn>(
        GetProcAddress(loader, "BZLoader_Shutdown"));
    const auto getSessionId = reinterpret_cast<SessionIdFn>(
        GetProcAddress(loader, "BZLoader_GetSessionId"));
    if (!initialize || !shutdown || !getSessionId || !initialize())
    {
        std::cerr << "loader lifecycle exports failed\n";
        return 2;
    }

    const char* rawSessionId = getSessionId();
    const std::string sessionId = rawSessionId ? rawSessionId : "";
    if (sessionId.empty())
    {
        std::cerr << "loader did not report a session id\n";
        return 2;
    }

    shutdown();

    const std::vector<std::string> lines = ReadSessionLines(logPath, sessionId);
    if (lines.empty())
    {
        std::cerr << "no log lines carried this run's session id " << sessionId << '\n';
        return 3;
    }
    if (!Contains(lines, "Lifecycle test plugin loaded") ||
        !Contains(lines, "Lifecycle test plugin shut down") ||
        !Contains(lines, "BZLoader shutdown complete"))
    {
        std::cerr << "plugin lifecycle messages were not observed in session "
                  << sessionId << '\n';
        for (const auto& line : lines) std::cerr << "  " << line << '\n';
        return 3;
    }

    std::cout << "bzloader host integration test passed (session " << sessionId << ")\n";
    return 0;
}
