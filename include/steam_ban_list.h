#pragma once
// Steam bridge ban gate: the bridge refuses a Steam peer whose
// Steam-authenticated SteamID64 is in bans.cfg (S<steamid64>, the id the
// in-game /ban and Ban button write), before the game sees the connection.
// Worker-thread only. Reloads when the file's size or write time changes;
// a missing file means no bans, and an unreadable one keeps the last list.
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include "stable_id_list.h"
#include <cstdint>
#include <fstream>
#include <iterator>
#include <set>
#include <string>

namespace BZROpenShim::SocketTunnel
{
    class SteamBanList
    {
    public:
        // Text form: only "S<decimal SteamID64>" ids count; G ids are ignored.
        void Parse(const std::string& text)
        {
            ids.clear();
            for (const auto& record : StableIdList::Parse(text))
            {
                if (record.id.size() < 2 || record.id.size() > 21 || record.id[0] != 'S') continue;
                uint64_t value = 0; bool digits = true;
                for (size_t i = 1; i < record.id.size() && digits; ++i)
                {
                    const char c = record.id[i];
                    if (c < '0' || c > '9' || value > (UINT64_MAX - uint64_t(c - '0')) / 10) digits = false;
                    else value = value * 10 + uint64_t(c - '0');
                }
                if (digits && value) ids.insert(value);
            }
        }
        // True when the list changed. path is the full bans.cfg path.
        bool Refresh(const std::wstring& path)
        {
            if (path.empty()) return false;
            WIN32_FILE_ATTRIBUTE_DATA data{};
            if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &data))
            {
                const DWORD error = GetLastError();
                if (error != ERROR_FILE_NOT_FOUND && error != ERROR_PATH_NOT_FOUND) return false; // keep last list
                const bool changed = !ids.empty() || stamp != 0;
                ids.clear(); stamp = 0; return changed;
            }
            const uint64_t now = (uint64_t(data.ftLastWriteTime.dwHighDateTime) << 32 | data.ftLastWriteTime.dwLowDateTime) ^
                (uint64_t(data.nFileSizeHigh) << 32 | data.nFileSizeLow) * 0x9E3779B97F4A7C15ull;
            if (now == stamp && loaded) return false;
            // moderation.cpp truncates then writes, and always writes a header:
            // an empty file is mid-write, so keep the last list and retry.
            if (data.nFileSizeHigh == 0 && data.nFileSizeLow == 0) return false;
            std::ifstream file(path, std::ios::binary);
            if (!file) return false; // e.g. mid-write by the game: retry next refresh
            const std::string text{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
            const auto before = ids;
            Parse(text); stamp = now; loaded = true;
            return ids != before;
        }
        bool Banned(uint64_t steamId) const { return ids.count(steamId) != 0; }
        size_t Size() const { return ids.size(); }
    private:
        std::set<uint64_t> ids;
        uint64_t stamp = 0;
        bool loaded = false;
    };
}
