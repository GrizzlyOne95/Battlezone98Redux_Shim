#pragma once

// Pure decisions for the Steam launcher proxy (Launcher\d3d9.dll). Header-only
// and free of Windows calls so tests/launcher_proxy_logic_tests.cpp can cover
// them; the proxy and the plugin's deploy code both include it.

#include "bool_token.h"

#include <cstddef>
#include <cwchar>

namespace BZROpenShim
{
namespace LauncherProxy
{
    // The launcher goes straight to the game only when every gate passes.
    // Shift held, the toggle off, no Ogre.cfg yet (first run: the launcher
    // writes it) or Wine/Proton each show the stock launcher.
    inline bool ShouldSkipLauncher(bool shiftHeld, bool toggleOn, bool ogreCfgExists, bool underWine)
    {
        return !shiftHeld && toggleOn && ogreCfgExists && !underWine;
    }

    // Reads an openshim.ini value with the same words as the plugin
    // (bool_token.h). Anything unrecognized, including blank, is off.
    inline bool ParseToggle(const wchar_t* text)
    {
        if (!text)
            return false;
        char narrow[16] = {};
        size_t length = 0;
        for (; text[length] != L'\0'; ++length)
        {
            if (length >= sizeof(narrow) || text[length] > 0x7F)
                return false;
            narrow[length] = static_cast<char>(text[length]);
        }
        bool value = false;
        return BoolToken::TryParse(narrow, length, value) && value;
    }

    // The launcher's own arguments: the command line with argv[0] (quoted or
    // not) and the blanks after it removed. Never null.
    inline const wchar_t* CommandLineTail(const wchar_t* commandLine)
    {
        if (!commandLine)
            return L"";
        const wchar_t* p = commandLine;
        if (*p == L'"')
        {
            ++p;
            while (*p != L'\0' && *p != L'"')
                ++p;
            if (*p == L'"')
                ++p;
        }
        else
        {
            while (*p != L'\0' && *p != L' ' && *p != L'\t')
                ++p;
        }
        while (*p == L' ' || *p == L'\t')
            ++p;
        return p;
    }
}
}
