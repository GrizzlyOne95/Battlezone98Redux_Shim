#pragma once

// The text format of OpenShim's per-player lists, bans.cfg and mutes.cfg:
//
//   ; comment lines start with ';' or '#'
//   <stable_id> [display name]
//
// A stable id is the G<uid>/S<uid> platform identity, upper-cased, and ends at
// the first space, '#' or ';'. The first line for an id wins; a later line for
// the same id only fills in a name the first one lacked.
//
// The ban and mute lists each carried a copy of this loader and writer (audit
// P2-3). What each list does when an entry is added stays with the list:
// bans keep the first name seen, mutes keep the latest.
//
// Pure and free of Windows calls; moderation.cpp does the file I/O.

#include <cctype>
#include <string>
#include <vector>

namespace BZROpenShim
{
namespace StableIdList
{
    struct Record
    {
        std::string id;
        std::string name;
    };

    inline std::string NormalizeId(const char* value)
    {
        std::string normalized;
        if (!value)
            return normalized;

        normalized.reserve(32);
        for (const char* cursor = value; *cursor; ++cursor)
        {
            if (*cursor == '#' || *cursor == ';' ||
                std::isspace(static_cast<unsigned char>(*cursor)))
            {
                break;
            }
            normalized.push_back(
                static_cast<char>(std::toupper(static_cast<unsigned char>(*cursor))));
        }
        return normalized;
    }

    namespace Detail
    {
        inline bool IsSpace(char c)
        {
            return std::isspace(static_cast<unsigned char>(c)) != 0;
        }

        inline std::string Trim(const std::string& text)
        {
            size_t begin = 0;
            size_t end = text.size();
            while (begin < end && IsSpace(text[begin]))
                ++begin;
            while (end > begin && IsSpace(text[end - 1]))
                --end;
            return text.substr(begin, end - begin);
        }
    }

    inline std::vector<Record> Parse(const std::string& text)
    {
        std::vector<Record> records;
        size_t lineStart = 0;
        while (lineStart <= text.size())
        {
            size_t lineEnd = text.find('\n', lineStart);
            if (lineEnd == std::string::npos)
                lineEnd = text.size();
            const std::string line = Detail::Trim(text.substr(lineStart, lineEnd - lineStart));
            lineStart = lineEnd + 1;

            if (line.empty() || line[0] == '#' || line[0] == ';')
                continue;

            size_t split = 0;
            while (split < line.size() && !Detail::IsSpace(line[split]))
                ++split;

            const std::string id = NormalizeId(line.substr(0, split).c_str());
            if (id.empty())
                continue;
            const std::string name = split < line.size() ? Detail::Trim(line.substr(split + 1)) : std::string();

            bool merged = false;
            for (Record& existing : records)
            {
                if (existing.id != id)
                    continue;
                if (existing.name.empty() && !name.empty())
                    existing.name = name;
                merged = true;
                break;
            }
            if (!merged)
                records.push_back({ id, name });
        }
        return records;
    }

    // Two comment lines, then one line per record.
    inline std::string Format(const std::vector<Record>& records, const char* title, const char* formatHint)
    {
        std::string text;
        text += "; ";
        text += title;
        text += "\n; Format: ";
        text += formatHint;
        text += "\n";
        for (const Record& record : records)
        {
            text += record.id;
            if (!record.name.empty())
            {
                text += ' ';
                text += record.name;
            }
            text += '\n';
        }
        return text;
    }
}
}
