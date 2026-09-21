// bzn_filename_identity.h
// BZR Open Shim - mission filename identity comparison
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Pure helper for comparing the .bzn file actually opened with the embedded
// msn_filename header. TerrainName is intentionally not part of this rule:
// missions may legitimately reuse terrain authored under a different name.

#pragma once

#include <string_view>

namespace BZROpenShim::BznFilenameIdentity
{
    struct Result
    {
        std::string_view openedBasename;
        bool comparable = false;
        bool matches = false;
    };

    inline std::string_view BaseName(std::string_view path)
    {
        const size_t slash = path.find_last_of("/\\");
        return slash == std::string_view::npos ? path : path.substr(slash + 1);
    }

    inline bool IsAscii(std::string_view value)
    {
        for (const unsigned char c : value)
        {
            if (c >= 0x80)
                return false;
        }
        return true;
    }

    inline char FoldAscii(char c)
    {
        return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
    }

    inline bool EqualAsciiCaseInsensitive(std::string_view left, std::string_view right)
    {
        if (left.size() != right.size())
            return false;

        for (size_t i = 0; i < left.size(); ++i)
        {
            if (FoldAscii(left[i]) != FoldAscii(right[i]))
                return false;
        }
        return true;
    }

    inline std::string_view Stem(std::string_view basename)
    {
        if (basename.size() >= 4 &&
            EqualAsciiCaseInsensitive(basename.substr(basename.size() - 4), ".bzn"))
        {
            return basename.substr(0, basename.size() - 4);
        }
        return basename;
    }

    inline Result Compare(std::string_view openedPath, std::string_view embeddedMsnFilename)
    {
        Result result;
        result.openedBasename = BaseName(openedPath);

        // Avoid inventing Windows case-fold semantics for non-ASCII names in
        // this platform-neutral helper. The diagnostic simply stays silent.
        result.comparable =
            !result.openedBasename.empty() &&
            !embeddedMsnFilename.empty() &&
            IsAscii(result.openedBasename) &&
            IsAscii(embeddedMsnFilename);

        if (result.comparable)
        {
            result.matches =
                EqualAsciiCaseInsensitive(result.openedBasename, embeddedMsnFilename);
        }

        return result;
    }

    inline Result CompareTerrainName(std::string_view openedPath, std::string_view terrainName)
    {
        Result result;
        result.openedBasename = Stem(BaseName(openedPath));

        // This is deliberately a relationship hint, not a validity rule.
        // Battlezone permits a mission BZN to reuse terrain authored under a
        // different name, so callers must not promote a mismatch to a
        // structural error or silently rewrite TerrainName.
        result.comparable =
            !result.openedBasename.empty() &&
            !terrainName.empty() &&
            IsAscii(result.openedBasename) &&
            IsAscii(terrainName);

        if (result.comparable)
        {
            result.matches =
                EqualAsciiCaseInsensitive(result.openedBasename, terrainName);
        }

        return result;
    }
}
