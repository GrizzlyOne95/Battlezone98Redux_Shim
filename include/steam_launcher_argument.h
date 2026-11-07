// steam_launcher_argument.h
// Lets Steam players skip Rebellion's launcher with the launch option
//
//     "<game folder>\battlezone98redux.exe" %command%
//
// Steam expands %command% to the launcher's own path, so the game receives
// "...\Launcher\BZLauncher.exe" as an extra argument. Stock's parser treats a
// bare argument as a mission file to load (BZR_LUA_AGENT_REFERENCE.md,
// "Launching a mission from the command line"), so that token must go before
// the parser strtok()s the GetCommandLineA() buffer in WinMain.
//
// BlankSteamLauncherArgument overwrites every such token (and its quotes)
// with spaces in place. The buffer keeps its length, argv[0] is never
// touched, and a command line without the token is left byte-identical.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef>

namespace BZROpenShim
{
    namespace SteamLauncherArgument
    {
        inline char LowerAscii(char c)
        {
            return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
        }

        // True when [begin, end) names BZLauncher.exe: either the whole token
        // or its last path component.
        inline bool IsLauncherPath(const char* begin, const char* end)
        {
            static const char kName[] = "bzlauncher.exe";
            const std::size_t nameLength = sizeof(kName) - 1;
            const std::size_t length = static_cast<std::size_t>(end - begin);
            if (length < nameLength)
                return false;
            const char* name = end - nameLength;
            if (name != begin && name[-1] != '\\' && name[-1] != '/')
                return false;
            for (std::size_t i = 0; i < nameLength; ++i)
            {
                if (LowerAscii(name[i]) != kName[i])
                    return false;
            }
            return true;
        }

        // Returns the number of tokens blanked.
        inline int BlankSteamLauncherArgument(char* commandLine)
        {
            if (!commandLine)
                return 0;

            int blanked = 0;
            bool first = true;
            char* p = commandLine;
            while (*p)
            {
                while (*p == ' ' || *p == '\t')
                    ++p;
                if (!*p)
                    break;

                char* tokenStart = p;
                const bool quoted = (*p == '"');
                const char* textBegin = quoted ? p + 1 : p;
                const char* textEnd = nullptr;
                if (quoted)
                {
                    ++p;
                    while (*p && *p != '"')
                        ++p;
                    textEnd = p;
                    if (*p == '"')
                        ++p;
                }
                else
                {
                    while (*p && *p != ' ' && *p != '\t')
                        ++p;
                    textEnd = p;
                }

                if (!first && IsLauncherPath(textBegin, textEnd))
                {
                    for (char* q = tokenStart; q < p; ++q)
                        *q = ' ';
                    ++blanked;
                }
                first = false;
            }
            return blanked;
        }
    }
}
