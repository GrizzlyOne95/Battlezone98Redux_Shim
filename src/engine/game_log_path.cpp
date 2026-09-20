// game_log_path.cpp
// BZR Open Shim - where the game's log files go.
//
// Split out of shim_log.cpp deliberately. The bootstrap has to route the
// stock game logs into the logs directory from its CreateFile wrapper before
// OpenShim exists, and that is the only thing it needs from the logging code.
// Pulling shim_log.cpp across the boundary for it would drag the whole
// logging subsystem -- file handle, init-once, lock -- back into the proxy
// and give the process two of them. These two functions are pure and
// stateless, so more than one module can compile them safely.
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "game_log_path.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifdef _WIN32
#include <Windows.h>
#endif

#include <cstring>
#include <string>

namespace BZROpenShim
{
    std::string SanitizeLogFilename(const char* fileName)
    {
        const char* safeName = (fileName && fileName[0]) ? fileName : "openshim.log";
        if (const char* slash = std::strrchr(safeName, '\\'))
            safeName = slash + 1;
        if (const char* slash = std::strrchr(safeName, '/'))
            safeName = slash + 1;

        if (!safeName[0] ||
            std::strcmp(safeName, ".") == 0 ||
            std::strcmp(safeName, "..") == 0 ||
            std::strpbrk(safeName, "\\/:*?\"<>|") != nullptr)
        {
            return "openshim.log";
        }

        const size_t len = std::strlen(safeName);
        for (size_t i = 0; i < len; ++i)
        {
            if (static_cast<unsigned char>(safeName[i]) < 32)
                return "openshim.log";
        }

        if (safeName[len - 1] == '.' || safeName[len - 1] == ' ')
            return "openshim.log";

        // Check for Windows reserved device names in the filename stem.
        size_t stemLen = 0;
        while (safeName[stemLen] && safeName[stemLen] != '.')
            ++stemLen;

        if (stemLen == 3 || stemLen == 4)
        {
            char stemUpper[5] = {};
            for (size_t i = 0; i < stemLen; ++i)
                stemUpper[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(safeName[i])));

            if (stemLen == 3)
            {
                if (std::strcmp(stemUpper, "CON") == 0 ||
                    std::strcmp(stemUpper, "PRN") == 0 ||
                    std::strcmp(stemUpper, "AUX") == 0 ||
                    std::strcmp(stemUpper, "NUL") == 0)
                {
                    return "openshim.log";
                }
            }
            else if (stemLen == 4)
            {
                if ((std::strncmp(stemUpper, "COM", 3) == 0 || std::strncmp(stemUpper, "LPT", 3) == 0) &&
                    stemUpper[3] >= '1' && stemUpper[3] <= '9')
                {
                    return "openshim.log";
                }
            }
        }

        return safeName;
    }

    std::string GetGameLogPath(const char* fileName)
    {
        const std::string safeName = SanitizeLogFilename(fileName);

#ifdef _WIN32
        char modulePath[MAX_PATH] = {};
        if (GetModuleFileNameA(nullptr, modulePath, MAX_PATH) == 0)
            return safeName;

        char* lastSlash = std::strrchr(modulePath, '\\');
        if (!lastSlash)
            return safeName;

        *(lastSlash + 1) = '\0';
        const std::string gameRoot(modulePath);
        const std::string logDirectory = gameRoot + "logs";
        if (CreateDirectoryA(logDirectory.c_str(), nullptr) != FALSE ||
            GetLastError() == ERROR_ALREADY_EXISTS)
        {
            return logDirectory + "\\" + safeName;
        }

        return gameRoot + safeName;
#else
        return safeName;
#endif
    }
}
