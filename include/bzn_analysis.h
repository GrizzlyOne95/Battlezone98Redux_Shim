// bzn_analysis.h
// BZR Open Shim - pure structural analysis of an ASCII mission (.bzn)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Header-only and free of Win32 so it can be unit tested off-target. The hook
// and the logging live in src/patches/bzn_load_trace.cpp; everything here is a
// pure function of the file's bytes.
//
// See include/bzn_load_trace.h for why this exists at all. The short version:
// the engine names only an object's CLASS as it loads and says nothing about
// why a load aborted, so a malformed mission costs hours to diagnose by hand.
//
// The ASCII BZN grammar this understands:
//
//   [SectionName]            section header, one per line
//   key [n] =                field whose value is on the FOLLOWING line
//   key = value              field with an inline value
//
// Sections that matter: [GameObject] (one per object, in load order),
// [AiPaths] (carries a `count`), and [AiPath] (one per path).

#pragma once

#include <algorithm>
#include <cerrno>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace BZROpenShim::BznAnalysis
{
    inline constexpr size_t kNone = static_cast<size_t>(-1);

    struct ObjectRecord
    {
        size_t index = 0;        // load order, matching the engine's "obj #N"
        size_t headerLine = 0;   // 1-based line of the [GameObject] header
        std::string prjId;       // ODF name
        std::string label;
        std::string team;
        std::string seqno;
        std::string objAddr;
    };

    struct PathRecord
    {
        size_t index = 0;
        size_t headerLine = 0;
        std::string pointCount;
        long declaredPoints = 0;
        bool pointsCountValid = false;
        size_t xComponents = 0;
        size_t zComponents = 0;
        bool sawPoints = false;
    };

    struct LineEndings
    {
        size_t crlf = 0;
        size_t bareLf = 0;
        size_t bareCr = 0;
        size_t firstUnsafeLine = kNone;  // 1-based

        bool unsafe() const { return bareLf > 0 || bareCr > 0; }

        bool mixed() const
        {
            const int kinds = (crlf > 0 ? 1 : 0) +
                              (bareLf > 0 ? 1 : 0) +
                              (bareCr > 0 ? 1 : 0);
            return kinds > 1;
        }
    };

    struct Result
    {
        bool ascii = false;              // binarySave = false
        bool sawBinarySaveField = false;
        std::string version;
        std::string terrainName;
        std::string seqCount;
        std::string declaredObjectCount;
        std::string declaredAoiCount;
        std::string declaredPathCount;
        size_t aoiBlocks = 0;
        size_t pathBlocks = 0;
        size_t lineCount = 0;
        std::vector<ObjectRecord> objects;
        std::vector<PathRecord> paths;
        LineEndings endings;
        // Index of the GameObject the first non-CRLF terminator falls inside,
        // or kNone. This is the number the engine's own object log is likely
        // to stop on when the malformed run breaks parsing.
        size_t unsafeEnclosingObject = kNone;
        std::vector<std::string> problems;
    };

    namespace detail
    {
        struct Line
        {
            size_t begin = 0;
            size_t length = 0;
            bool crlf = false;
            bool bareCr = false;
            bool terminated = false;
        };

        inline void SplitLines(std::string_view data, std::vector<Line>& lines)
        {
            size_t start = 0;
            for (size_t i = 0; i < data.size(); ++i)
            {
                if (data[i] == '\r')
                {
                    Line line;
                    line.begin = start;
                    line.length = i - start;
                    line.terminated = true;

                    if ((i + 1) < data.size() && data[i + 1] == '\n')
                    {
                        line.crlf = true;
                        ++i;  // consume the LF half of CRLF
                    }
                    else
                    {
                        line.bareCr = true;
                    }

                    lines.push_back(line);
                    start = i + 1;
                    continue;
                }

                if (data[i] == '\n')
                {
                    Line line;
                    line.begin = start;
                    line.length = i - start;
                    line.terminated = true;  // bare LF
                    lines.push_back(line);
                    start = i + 1;
                }
            }

            if (start < data.size())
            {
                Line line;
                line.begin = start;
                line.length = data.size() - start;
                lines.push_back(line);
            }
        }

        inline std::string_view Trim(std::string_view value)
        {
            size_t b = 0;
            size_t e = value.size();
            const auto space = [](char c) { return c == ' ' || c == '\t' || c == '\r'; };
            while (b < e && space(value[b])) ++b;
            while (e > b && space(value[e - 1])) --e;
            return value.substr(b, e - b);
        }

        inline bool IsSection(std::string_view text, std::string_view name)
        {
            const std::string_view t = Trim(text);
            return t.size() >= 2 && t.front() == '[' && t.back() == ']' &&
                   t.substr(1, t.size() - 2) == name;
        }

        inline bool ParseDecimalLong(std::string_view text, long& value)
        {
            const std::string_view trimmed = Trim(text);
            if (trimmed.empty())
                return false;

            std::string copy(trimmed);
            char* end = nullptr;
            errno = 0;
            const long parsed = std::strtol(copy.c_str(), &end, 10);
            if (end == copy.c_str() || !end || *end != '\0' || errno == ERANGE)
                return false;

            value = parsed;
            return true;
        }

        inline bool ParseBracketCount(std::string_view text, std::string_view expectedKey, long& count)
        {
            const size_t eq = text.find('=');
            if (eq == std::string_view::npos)
                return false;

            const std::string_view left = Trim(text.substr(0, eq));
            const size_t open = left.find('[');
            const size_t close = left.find(']', open == std::string_view::npos ? 0 : open + 1);
            if (open == std::string_view::npos || close == std::string_view::npos)
                return false;
            if (Trim(left.substr(0, open)) != expectedKey)
                return false;

            const std::string_view number = Trim(left.substr(open + 1, close - open - 1));
            if (number.empty())
                return false;

            return ParseDecimalLong(number, count);
        }

        // Returns false when the line is not "key = ..." at all.
        inline bool ParseField(std::string_view text, std::string& key, std::string& value,
                               bool& valueOnNextLine)
        {
            const size_t eq = text.find('=');
            if (eq == std::string_view::npos)
                return false;

            std::string_view left = Trim(text.substr(0, eq));
            const size_t bracket = left.find('[');
            if (bracket != std::string_view::npos)
                left = Trim(left.substr(0, bracket));
            if (left.empty())
                return false;

            for (char c : left)
            {
                const bool ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                                (c >= '0' && c <= '9') || c == '_';
                if (!ok)
                    return false;
            }

            key.assign(left);
            const std::string_view rhs = Trim(text.substr(eq + 1));
            value.assign(rhs);
            valueOnNextLine = rhs.empty();
            return true;
        }
    }

    inline Result Analyze(std::string_view data)
    {
        using namespace detail;

        Result result;
        std::vector<Line> lines;
        SplitLines(data, lines);
        result.lineCount = lines.size();

        for (size_t i = 0; i < lines.size(); ++i)
        {
            if (!lines[i].terminated)
                continue;  // a final line without a terminator says nothing

            if (lines[i].crlf)
                result.endings.crlf++;
            else if (lines[i].bareCr)
                result.endings.bareCr++;
            else
                result.endings.bareLf++;

            if (!lines[i].crlf && result.endings.firstUnsafeLine == kNone)
                result.endings.firstUnsafeLine = i + 1;
        }

        std::unordered_set<std::string> ids;
        std::vector<std::string> sObjectRefs;
        std::unordered_map<std::string, int> labelCounts;
        std::unordered_map<std::string, int> seqCounts;

        ObjectRecord* current = nullptr;
        PathRecord* currentPath = nullptr;
        bool seenFirstObject = false;
        bool inAois = false;
        bool expectAoiCount = false;
        bool inPaths = false;
        bool expectPathCount = false;

        std::string key;
        std::string value;

        for (size_t i = 0; i < lines.size(); ++i)
        {
            const std::string_view text(data.data() + lines[i].begin, lines[i].length);

            if (IsSection(text, "GameObject"))
            {
                seenFirstObject = true;
                ObjectRecord rec;
                rec.index = result.objects.size();
                rec.headerLine = i + 1;
                result.objects.push_back(rec);
                current = &result.objects.back();
                currentPath = nullptr;
                inAois = false;
                inPaths = false;
                continue;
            }
            if (IsSection(text, "AOIs"))
            {
                current = nullptr;
                currentPath = nullptr;
                inAois = true;
                expectAoiCount = true;
                inPaths = false;
                continue;
            }
            if (IsSection(text, "AOI"))
            {
                current = nullptr;
                currentPath = nullptr;
                result.aoiBlocks++;
                continue;
            }
            if (IsSection(text, "AiPaths"))
            {
                current = nullptr;
                currentPath = nullptr;
                inAois = false;
                inPaths = true;
                expectPathCount = true;
                continue;
            }
            if (IsSection(text, "AiPath"))
            {
                current = nullptr;
                PathRecord rec;
                rec.index = result.paths.size();
                rec.headerLine = i + 1;
                result.paths.push_back(rec);
                currentPath = &result.paths.back();
                result.pathBlocks++;
                continue;
            }
            if (!Trim(text).empty() && Trim(text).front() == '[')
            {
                current = nullptr;
                currentPath = nullptr;
                continue;
            }

            bool next = false;
            if (!ParseField(text, key, value, next))
                continue;

            long bracketCount = -1;
            const bool hasBracketCount = ParseBracketCount(text, key, bracketCount);
            if (next && (i + 1) < lines.size())
            {
                const std::string_view following(data.data() + lines[i + 1].begin, lines[i + 1].length);
                value.assign(Trim(following));
            }

            if (!seenFirstObject && result.declaredObjectCount.empty() && key == "size")
            {
                // GameObject::SaveAll writes the object count immediately before
                // the first [GameObject]. LoadAll trusts this count to decide
                // exactly how many object records to consume.
                result.declaredObjectCount = value;
            }
            else if (inAois && expectAoiCount && key == "size")
            {
                result.declaredAoiCount = value;
                expectAoiCount = false;
            }
            else if (inPaths && expectPathCount && key == "count")
            {
                result.declaredPathCount = value;
                expectPathCount = false;
            }
            else if (key == "version" && result.version.empty())
                result.version = value;
            else if (key == "binarySave")
            {
                result.sawBinarySaveField = true;
                result.ascii = (value == "false");
            }
            else if (key == "TerrainName" && result.terrainName.empty())
                result.terrainName = value;
            else if (key == "seq_count" && result.seqCount.empty())
                result.seqCount = value;

            if (key == "obj_addr" || key == "old_ptr")
            {
                if (!value.empty() && !ids.insert(value).second)
                    result.problems.push_back("duplicate pointer id " + value);
            }
            else if (key == "sObject" && !value.empty())
                sObjectRefs.push_back(value);

            if (currentPath)
            {
                if (key == "pointCount" && currentPath->pointCount.empty())
                    currentPath->pointCount = value;
                else if (key == "points")
                {
                    currentPath->sawPoints = true;
                    currentPath->pointsCountValid = hasBracketCount;
                    if (hasBracketCount)
                        currentPath->declaredPoints = bracketCount;
                }
                else if (currentPath->sawPoints && key == "x")
                    currentPath->xComponents++;
                else if (currentPath->sawPoints && key == "z")
                    currentPath->zComponents++;
            }

            if (!current)
                continue;

            if (key == "PrjID" && current->prjId.empty())
                current->prjId = value;
            else if (key == "label" && current->label.empty())
            {
                current->label = value;
                if (!value.empty())
                    labelCounts[value]++;
            }
            else if (key == "team" && current->team.empty())
                current->team = value;
            else if (key == "seqno" && current->seqno.empty())
            {
                current->seqno = value;
                if (!value.empty())
                    seqCounts[value]++;
            }
            else if (key == "obj_addr" && current->objAddr.empty())
                current->objAddr = value;
        }

        // Which object does the first non-CRLF terminator fall inside? Naming
        // it makes the diagnostic line up with the engine's own "(Class) is
        // loading (obj #N)" stream when malformed line endings abort loading.
        if (result.endings.unsafe() && result.endings.firstUnsafeLine != kNone)
        {
            for (const ObjectRecord& rec : result.objects)
            {
                if (rec.headerLine <= result.endings.firstUnsafeLine)
                    result.unsafeEnclosingObject = rec.index;
                else
                    break;
            }
        }

        for (const auto& entry : labelCounts)
        {
            if (entry.second > 1)
                result.problems.push_back("duplicate label '" + entry.first + "' on " +
                                          std::to_string(entry.second) + " objects");
        }
        for (const auto& entry : seqCounts)
        {
            if (entry.second > 1)
                result.problems.push_back("duplicate seqno " + entry.first + " on " +
                                          std::to_string(entry.second) + " objects");
        }
        for (const std::string& ref : sObjectRefs)
        {
            if (ref == "00000000")
                continue;
            if (ids.find(ref) == ids.end())
                result.problems.push_back("sObject references undefined id " + ref);
        }

        const auto validateBlockCount =
            [&result](const std::string& raw, const char* label, size_t observed,
                      const char* blockName)
            {
                if (raw.empty())
                    return;

                long declared = 0;
                if (!detail::ParseDecimalLong(raw, declared))
                {
                    result.problems.push_back(std::string(label) +
                                              " is not a valid decimal count: '" + raw + "'");
                    return;
                }
                if (declared < 0)
                {
                    result.problems.push_back(std::string(label) + " is negative: " + raw);
                    return;
                }
                if (static_cast<unsigned long>(declared) >
                    static_cast<unsigned long>(result.lineCount))
                {
                    result.problems.push_back(std::string(label) + " says " + raw +
                                              " but the file has only " +
                                              std::to_string(result.lineCount) +
                                              " lines; that count is impossible");
                    return;
                }
                if (static_cast<size_t>(declared) != observed)
                {
                    result.problems.push_back(std::string(label) + " says " + raw +
                                              " but the file has " +
                                              std::to_string(observed) + " " + blockName);
                }
            };

        validateBlockCount(result.declaredObjectCount, "GameObject size",
                           result.objects.size(), "[GameObject] blocks");
        validateBlockCount(result.declaredAoiCount, "[AOIs] size",
                           result.aoiBlocks, "[AOI] blocks");

        for (const PathRecord& path : result.paths)
        {
            long declaredPointCount = 0;
            bool pointCountValid = true;
            if (!path.pointCount.empty())
            {
                if (!detail::ParseDecimalLong(path.pointCount, declaredPointCount))
                {
                    result.problems.push_back("AiPath #" + std::to_string(path.index) +
                                              " pointCount is not a valid decimal count: '" +
                                              path.pointCount + "'");
                    pointCountValid = false;
                }
                else if (declaredPointCount < 0)
                {
                    result.problems.push_back("AiPath #" + std::to_string(path.index) +
                                              " pointCount is negative: " + path.pointCount);
                    pointCountValid = false;
                }
                else if (static_cast<unsigned long>(declaredPointCount) >
                         static_cast<unsigned long>(result.lineCount))
                {
                    result.problems.push_back("AiPath #" + std::to_string(path.index) +
                                              " pointCount says " + path.pointCount +
                                              " but the file has only " +
                                              std::to_string(result.lineCount) +
                                              " lines; that count is impossible");
                    pointCountValid = false;
                }
            }

            bool pointsArrayValid = path.pointsCountValid;
            if (path.sawPoints && !path.pointsCountValid)
            {
                result.problems.push_back("AiPath #" + std::to_string(path.index) +
                                          " points array has an invalid [N] count");
                pointsArrayValid = false;
            }
            else if (path.sawPoints && path.declaredPoints < 0)
            {
                result.problems.push_back("AiPath #" + std::to_string(path.index) +
                                          " points array count is negative: " +
                                          std::to_string(path.declaredPoints));
                pointsArrayValid = false;
            }
            else if (path.sawPoints &&
                     static_cast<unsigned long>(path.declaredPoints) >
                     static_cast<unsigned long>(result.lineCount))
            {
                result.problems.push_back("AiPath #" + std::to_string(path.index) +
                                          " points array declares " +
                                          std::to_string(path.declaredPoints) +
                                          " entries but the file has only " +
                                          std::to_string(result.lineCount) +
                                          " lines; that count is impossible");
                pointsArrayValid = false;
            }

            if (!path.pointCount.empty() && path.sawPoints &&
                pointCountValid && pointsArrayValid)
            {
                if (declaredPointCount != path.declaredPoints)
                {
                    result.problems.push_back("AiPath #" + std::to_string(path.index) +
                                              " pointCount says " + path.pointCount +
                                              " but points array declares " +
                                              std::to_string(path.declaredPoints));
                }

                const size_t completePairs = (std::min)(path.xComponents, path.zComponents);
                if (static_cast<size_t>(path.declaredPoints) != completePairs ||
                    path.xComponents != path.zComponents)
                {
                    result.problems.push_back("AiPath #" + std::to_string(path.index) +
                                              " points array declares " +
                                              std::to_string(path.declaredPoints) +
                                              " but file contains " +
                                              std::to_string(completePairs) +
                                              " complete x/z point pairs");
                }
            }
        }

        validateBlockCount(result.declaredPathCount, "[AiPaths] count",
                           result.pathBlocks, "[AiPath] blocks");

        return result;
    }
}
