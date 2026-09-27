#pragma once

// Extra multiplayer map-list filters and the free-text search, as pure rules
// over the fields the stock filter already reads. The engine hooks that feed
// these live in src/patches/mp_map_filter_extras.cpp; this header has no
// Windows or engine dependency so the tests can drive it.
//
// Stock filters (cMapManager::BuildFilteredMapList, 0x00752A50) match on the
// map entry's type character (+0x38), its player range (+0x18 min, +0x1C
// max) and its Workshop id (+0x3C, the literal "0" for a stock map). The
// extras use the same fields and the same player-range rule.

#include <cstddef>
#include <cstring>

namespace BZROpenShim
{
namespace MapFilterExtras
{
    enum class Extra
    {
        None,
        FivePlusPlayers, // the map supports five or more players
        StockOnly,       // shipped with the game, not from the Workshop
    };

    struct ExtraFilterInfo
    {
        Extra extra;
        const char* key;   // internal key, never shown
        const char* label; // what the filter list displays
    };

    // Keys carry a prefix no stock key has, so a stock key can never be taken
    // for an extra one.
    constexpr ExtraFilterInfo kExtraFilters[] = {
        { Extra::FivePlusPlayers, "OpenShim:5PlusPlayers", "5+ Players" },
        { Extra::StockOnly, "OpenShim:Stock", "Stock Maps" },
    };

    inline Extra ExtraFromKey(const char* key)
    {
        if (!key)
            return Extra::None;
        for (const ExtraFilterInfo& info : kExtraFilters)
        {
            if (std::strcmp(key, info.key) == 0)
                return info.extra;
        }
        return Extra::None;
    }

    // `workshopId` is the entry's +0x3C text; stock marks its own maps "0".
    inline bool MatchesExtra(Extra extra, int minPlayers, int maxPlayers, const char* workshopId)
    {
        (void)minPlayers;
        switch (extra)
        {
        case Extra::None:
            return true;
        case Extra::FivePlusPlayers:
            return maxPlayers >= 5;
        case Extra::StockOnly:
            return workshopId && std::strcmp(workshopId, "0") == 0;
        }
        return false;
    }

    namespace Detail
    {
        inline char Lower(char c)
        {
            return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
        }
    }

    // Case-insensitive (ASCII) substring match. An empty or null needle
    // matches everything.
    inline bool ContainsIgnoreCase(const char* haystack, const char* needle)
    {
        if (!needle || !*needle)
            return true;
        if (!haystack)
            return false;
        const size_t needleLength = std::strlen(needle);
        for (const char* start = haystack; *start; ++start)
        {
            size_t i = 0;
            while (i < needleLength && start[i] &&
                   Detail::Lower(start[i]) == Detail::Lower(needle[i]))
            {
                ++i;
            }
            if (i == needleLength)
                return true;
        }
        return false;
    }

    // A search matches the title the list shows (+0x20) or the map's file
    // name (+0x00), so both "Achilles" and "mpach" find the same map.
    inline bool MatchesSearch(const char* title, const char* fileName, const char* search)
    {
        return ContainsIgnoreCase(title, search) || ContainsIgnoreCase(fileName, search);
    }
}
}
