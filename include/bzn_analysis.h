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
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <limits>
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
        std::string isUser;
        std::string objAddr;
        bool hasPrjId = false;
        bool hasSeqno = false;
        bool hasPos = false;
        bool hasTeam = false;
        bool hasLabel = false;
        bool hasIsUser = false;
        bool hasObjAddr = false;
        bool hasTransform = false;
    };

    struct AoiRecord
    {
        size_t index = 0;
        size_t headerLine = 0;
        std::string pathRef;
    };

    struct PathRecord
    {
        size_t index = 0;
        size_t headerLine = 0;
        std::string oldPtr;
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
        bool utf8Bom = false;
        bool utf16LeBom = false;
        bool utf16BeBom = false;
        bool embeddedNul = false;
        size_t firstNulOffset = kNone;     // zero-based byte offset
        std::string version;
        std::string terrainName;
        std::string seqCount;
        long maxObjectSeqno = -1;
        long minimumSafeSeqCount = -1;
        bool seqCountComparable = false;
        std::string declaredObjectCount;
        std::string declaredAoiCount;
        std::string declaredPathCount;
        size_t aoiBlocks = 0;
        size_t pathBlocks = 0;
        size_t lineCount = 0;
        std::vector<ObjectRecord> objects;
        std::vector<AoiRecord> aois;
        std::vector<PathRecord> paths;
        LineEndings endings;
        std::vector<std::string> byteProblems;
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

        inline bool IsNonFiniteNumber(std::string_view text)
        {
            const std::string_view trimmed = Trim(text);
            if (trimmed.empty())
                return false;

            std::string copy(trimmed);
            for (char& c : copy)
            {
                if (c >= 'A' && c <= 'Z')
                    c = static_cast<char>(c - 'A' + 'a');
            }

            // Modern C runtimes commonly spell these as nan/inf. Older MSVC
            // text formatting may emit 1.#INF / 1.#IND / 1.#QNAN instead.
            if (copy == "nan" || copy == "+nan" || copy == "-nan" ||
                copy == "inf" || copy == "+inf" || copy == "-inf" ||
                copy == "infinity" || copy == "+infinity" || copy == "-infinity" ||
                copy == "1.#inf" || copy == "+1.#inf" || copy == "-1.#inf" ||
                copy == "1.#ind" || copy == "+1.#ind" || copy == "-1.#ind" ||
                copy == "1.#qnan" || copy == "+1.#qnan" || copy == "-1.#qnan" ||
                copy == "1.#snan" || copy == "+1.#snan" || copy == "-1.#snan")
            {
                return true;
            }

            char* end = nullptr;
            errno = 0;
            const double parsed = std::strtod(copy.c_str(), &end);
            if (end == copy.c_str() || !end || *end != '\0')
                return false;

            // This also catches syntactically numeric overflow such as 1e9999:
            // if the runtime converts it to infinity, it is unsafe spatial data.
            return !std::isfinite(parsed);
        }

        inline bool IsTransformComponent(std::string_view key)
        {
            return key == "right_x" || key == "right_y" || key == "right_z" ||
                   key == "up_x" || key == "up_y" || key == "up_z" ||
                   key == "front_x" || key == "front_y" || key == "front_z" ||
                   key == "posit_x" || key == "posit_y" || key == "posit_z";
        }

        inline bool ParsePointerId(std::string_view text, uint32_t& value)
        {
            const std::string_view trimmed = Trim(text);
            if (trimmed.empty())
                return false;

            size_t begin = 0;
            if (trimmed.size() > 2 && trimmed[0] == '0' &&
                (trimmed[1] == 'x' || trimmed[1] == 'X'))
            {
                begin = 2;
            }
            if (begin == trimmed.size() || (trimmed.size() - begin) > 8)
                return false;

            uint32_t parsed = 0;
            for (size_t i = begin; i < trimmed.size(); ++i)
            {
                const char c = trimmed[i];
                uint32_t digit = 0;
                if (c >= '0' && c <= '9')
                    digit = static_cast<uint32_t>(c - '0');
                else if (c >= 'a' && c <= 'f')
                    digit = static_cast<uint32_t>(c - 'a' + 10);
                else if (c >= 'A' && c <= 'F')
                    digit = static_cast<uint32_t>(c - 'A' + 10);
                else
                    return false;

                parsed = (parsed << 4) | digit;
            }

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

        const auto byteAt = [&data](size_t offset) -> unsigned char
        {
            return static_cast<unsigned char>(data[offset]);
        };

        if (data.size() >= 3 &&
            byteAt(0) == 0xEF && byteAt(1) == 0xBB && byteAt(2) == 0xBF)
        {
            result.utf8Bom = true;
            result.byteProblems.push_back(
                "UTF-8 BOM present at file start; ASCII BZN must begin directly with the first field");
        }
        if (data.size() >= 2 && byteAt(0) == 0xFF && byteAt(1) == 0xFE)
        {
            result.utf16LeBom = true;
            result.byteProblems.push_back(
                "UTF-16 LE BOM present; Battlezone ASCII BZN is not UTF-16");
        }
        else if (data.size() >= 2 && byteAt(0) == 0xFE && byteAt(1) == 0xFF)
        {
            result.utf16BeBom = true;
            result.byteProblems.push_back(
                "UTF-16 BE BOM present; Battlezone ASCII BZN is not UTF-16");
        }

        for (size_t i = 0; i < data.size(); ++i)
        {
            if (data[i] == '\0')
            {
                result.embeddedNul = true;
                result.firstNulOffset = i;
                break;
            }
        }

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

        std::vector<std::string> sObjectRefs;
        std::unordered_map<std::string, int> labelCounts;
        std::unordered_map<std::string, int> seqCounts;

        ObjectRecord* current = nullptr;
        AoiRecord* currentAoi = nullptr;
        PathRecord* currentPath = nullptr;
        bool seenFirstObject = false;
        bool inAois = false;
        bool expectAoiCount = false;
        bool inPaths = false;
        bool inObjectPosition = false;
        bool inObjectTransform = false;
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
                currentAoi = nullptr;
                currentPath = nullptr;
                inAois = false;
                inPaths = false;
                inObjectPosition = false;
                inObjectTransform = false;
                continue;
            }
            if (IsSection(text, "AOIs"))
            {
                current = nullptr;
                currentAoi = nullptr;
                currentPath = nullptr;
                inAois = true;
                expectAoiCount = true;
                inPaths = false;
                inObjectPosition = false;
                inObjectTransform = false;
                continue;
            }
            if (IsSection(text, "AOI"))
            {
                current = nullptr;
                AoiRecord rec;
                rec.index = result.aois.size();
                rec.headerLine = i + 1;
                result.aois.push_back(rec);
                currentAoi = &result.aois.back();
                currentPath = nullptr;
                inObjectPosition = false;
                inObjectTransform = false;
                result.aoiBlocks++;
                continue;
            }
            if (IsSection(text, "AiPaths"))
            {
                current = nullptr;
                currentAoi = nullptr;
                currentPath = nullptr;
                inAois = false;
                inPaths = true;
                inObjectPosition = false;
                inObjectTransform = false;
                expectPathCount = true;
                continue;
            }
            if (IsSection(text, "AiPath"))
            {
                current = nullptr;
                currentAoi = nullptr;
                PathRecord rec;
                rec.index = result.paths.size();
                rec.headerLine = i + 1;
                result.paths.push_back(rec);
                currentPath = &result.paths.back();
                inObjectPosition = false;
                inObjectTransform = false;
                result.pathBlocks++;
                continue;
            }
            if (!Trim(text).empty() && Trim(text).front() == '[')
            {
                current = nullptr;
                currentAoi = nullptr;
                currentPath = nullptr;
                inObjectPosition = false;
                inObjectTransform = false;
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

            if (key == "sObject" && !value.empty())
                sObjectRefs.push_back(value);

            if (currentAoi && key == "undefptr" && currentAoi->pathRef.empty())
                currentAoi->pathRef = value;

            if (current)
            {
                if (key == "pos")
                {
                    inObjectPosition = true;
                    inObjectTransform = false;
                }
                else if (key == "team" || key == "label" || key == "isUser" ||
                         key == "obj_addr")
                {
                    inObjectPosition = false;
                }
                else if (key == "transform")
                {
                    inObjectPosition = false;
                    inObjectTransform = true;
                }

                if (inObjectPosition && (key == "x" || key == "y" || key == "z") &&
                    detail::IsNonFiniteNumber(value))
                {
                    result.problems.push_back(
                        "GameObject #" + std::to_string(current->index) +
                        " pos." + key + " is non-finite: " + value);
                }

                if (inObjectTransform && detail::IsTransformComponent(key) &&
                    detail::IsNonFiniteNumber(value))
                {
                    result.problems.push_back(
                        "GameObject #" + std::to_string(current->index) +
                        " transform." + key + " is non-finite: " + value);
                }
            }

            if (currentPath)
            {
                if (key == "old_ptr" && currentPath->oldPtr.empty())
                    currentPath->oldPtr = value;
                else if (key == "pointCount" && currentPath->pointCount.empty())
                    currentPath->pointCount = value;
                else if (key == "points")
                {
                    currentPath->sawPoints = true;
                    currentPath->pointsCountValid = hasBracketCount;
                    if (hasBracketCount)
                        currentPath->declaredPoints = bracketCount;
                }
                else if (currentPath->sawPoints && key == "x")
                {
                    currentPath->xComponents++;
                    if (detail::IsNonFiniteNumber(value))
                    {
                        result.problems.push_back(
                            "AiPath #" + std::to_string(currentPath->index) +
                            " points.x is non-finite: " + value);
                    }
                }
                else if (currentPath->sawPoints && key == "z")
                {
                    currentPath->zComponents++;
                    if (detail::IsNonFiniteNumber(value))
                    {
                        result.problems.push_back(
                            "AiPath #" + std::to_string(currentPath->index) +
                            " points.z is non-finite: " + value);
                    }
                }
            }

            if (!current)
                continue;

            if (!current->hasTransform)
            {
                if (key == "PrjID")
                {
                    current->hasPrjId = true;
                    if (current->prjId.empty())
                        current->prjId = value;
                }
                else if (key == "seqno")
                {
                    current->hasSeqno = true;
                    if (current->seqno.empty())
                    {
                        current->seqno = value;
                        if (!value.empty())
                            seqCounts[value]++;
                    }
                }
                else if (key == "pos")
                    current->hasPos = true;
                else if (key == "team")
                {
                    current->hasTeam = true;
                    if (current->team.empty())
                        current->team = value;
                }
                else if (key == "label")
                {
                    current->hasLabel = true;
                    if (current->label.empty())
                    {
                        current->label = value;
                        if (!value.empty())
                            labelCounts[value]++;
                    }
                }
                else if (key == "isUser")
                {
                    current->hasIsUser = true;
                    if (current->isUser.empty())
                        current->isUser = value;
                }
                else if (key == "obj_addr")
                {
                    current->hasObjAddr = true;
                    if (current->objAddr.empty())
                        current->objAddr = value;
                }
                else if (key == "transform")
                    current->hasTransform = true;
            }
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

        if (result.ascii)
        {
            long parsedVersion = 0;
            const bool versionKnown = detail::ParseDecimalLong(result.version, parsedVersion);
            const bool requireTransform = versionKnown && parsedVersion > 1001;

            for (const ObjectRecord& rec : result.objects)
            {
                std::vector<std::string> missing;
                if (!rec.hasPrjId) missing.push_back("PrjID");
                if (!rec.hasSeqno) missing.push_back("seqno");
                if (!rec.hasPos) missing.push_back("pos");
                if (!rec.hasTeam) missing.push_back("team");
                if (!rec.hasLabel) missing.push_back("label");
                if (!rec.hasIsUser) missing.push_back("isUser");
                if (!rec.hasObjAddr) missing.push_back("obj_addr");
                if (requireTransform && !rec.hasTransform) missing.push_back("transform");

                if (!missing.empty())
                {
                    std::string fields;
                    for (size_t i = 0; i < missing.size(); ++i)
                    {
                        if (i != 0)
                            fields += ", ";
                        fields += missing[i];
                    }

                    result.problems.push_back(
                        "GameObject #" + std::to_string(rec.index) +
                        " is missing required envelope field(s): " + fields +
                        " (PrjID=" + (rec.prjId.empty() ? "?" : rec.prjId) +
                        " label=" + (rec.label.empty() ? "?" : rec.label) + ")");
                }
            }
        }

        if (result.ascii)
        {
            std::vector<size_t> effectiveUsers;
            for (const ObjectRecord& rec : result.objects)
            {
                if (!rec.hasIsUser)
                    continue;  // missing field is handled by the envelope check

                long isUser = 0;
                if (!detail::ParseDecimalLong(rec.isUser, isUser))
                {
                    result.problems.push_back(
                        "GameObject #" + std::to_string(rec.index) +
                        " isUser is not a valid decimal integer: '" + rec.isUser + "'");
                    continue;
                }

                if (isUser != 0)
                    effectiveUsers.push_back(rec.index);

                if (isUser != 0 && isUser != 1)
                {
                    result.problems.push_back(
                        "GameObject #" + std::to_string(rec.index) +
                        " has noncanonical isUser=" + rec.isUser +
                        "; engine treats any nonzero value as true, canonical value is 1");
                }
            }

            if (effectiveUsers.size() > 1)
            {
                std::string indices;
                for (size_t i = 0; i < effectiveUsers.size(); ++i)
                {
                    if (i != 0)
                        indices += ", ";
                    indices += "#" + std::to_string(effectiveUsers[i]);
                }

                result.problems.push_back(
                    "multiple GameObjects have nonzero isUser: " + indices +
                    "; loader overwrites userObject for each and leaves the last loaded object active");
            }
        }

        if (result.ascii && !result.objects.empty())
        {
            bool allSeqnosValid = true;
            long maxSeqno = -1;

            for (const ObjectRecord& rec : result.objects)
            {
                long seqno = 0;
                if (!detail::ParseDecimalLong(rec.seqno, seqno))
                {
                    result.problems.push_back(
                        "GameObject #" + std::to_string(rec.index) +
                        " seqno is not a valid decimal integer: '" + rec.seqno + "'");
                    allSeqnosValid = false;
                    continue;
                }
                if (seqno < 0)
                {
                    result.problems.push_back(
                        "GameObject #" + std::to_string(rec.index) +
                        " seqno is negative: " + rec.seqno);
                    allSeqnosValid = false;
                    continue;
                }
                if (seqno > maxSeqno)
                    maxSeqno = seqno;
            }

            if (allSeqnosValid && maxSeqno >= 0)
            {
                result.maxObjectSeqno = maxSeqno;

                if (maxSeqno == (std::numeric_limits<long>::max)())
                {
                    result.problems.push_back(
                        "maximum object seqno cannot be incremented safely; seq_count repair would overflow");
                }
                else
                {
                    result.minimumSafeSeqCount = maxSeqno + 1;

                    long seqCount = 0;
                    if (!detail::ParseDecimalLong(result.seqCount, seqCount))
                    {
                        result.problems.push_back(
                            "seq_count is not a valid decimal integer: '" + result.seqCount + "'");
                    }
                    else if (seqCount < 0)
                    {
                        result.problems.push_back("seq_count is negative: " + result.seqCount);
                    }
                    else
                    {
                        result.seqCountComparable = true;
                        if (seqCount <= maxSeqno)
                        {
                            result.problems.push_back(
                                "seq_count " + result.seqCount +
                                " is stale: maximum object seqno is " +
                                std::to_string(maxSeqno) +
                                "; minimum safe seq_count is " +
                                std::to_string(result.minimumSafeSeqCount));
                        }
                    }
                }
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
        std::unordered_map<uint32_t, size_t> objectIdOwners;
        for (const ObjectRecord& rec : result.objects)
        {
            if (rec.objAddr.empty())
                continue;  // missing obj_addr is handled by the envelope check

            uint32_t id = 0;
            if (!detail::ParsePointerId(rec.objAddr, id))
                continue;  // pointer text-format validation is outside this check

            if (id == 0)
            {
                result.problems.push_back(
                    "GameObject #" + std::to_string(rec.index) +
                    " obj_addr defines null pointer id " + rec.objAddr);
                continue;
            }

            const auto inserted = objectIdOwners.emplace(id, rec.index);
            if (!inserted.second)
            {
                result.problems.push_back(
                    "duplicate GameObject obj_addr " + rec.objAddr +
                    " on objects #" + std::to_string(inserted.first->second) +
                    " and #" + std::to_string(rec.index));
            }
        }

        for (const std::string& ref : sObjectRefs)
        {
            uint32_t id = 0;
            if (!detail::ParsePointerId(ref, id) || id == 0)
                continue;
            if (objectIdOwners.find(id) == objectIdOwners.end())
                result.problems.push_back("sObject references undefined GameObject obj_addr " + ref);
        }

        std::unordered_map<uint32_t, size_t> aiPathIdOwners;
        for (const PathRecord& path : result.paths)
        {
            if (path.oldPtr.empty())
                continue;

            uint32_t id = 0;
            if (!detail::ParsePointerId(path.oldPtr, id))
                continue;

            if (id == 0)
            {
                result.problems.push_back(
                    "AiPath #" + std::to_string(path.index) +
                    " old_ptr defines null pointer id " + path.oldPtr);
                continue;
            }

            const auto inserted = aiPathIdOwners.emplace(id, path.index);
            if (!inserted.second)
            {
                result.problems.push_back(
                    "duplicate AiPath old_ptr " + path.oldPtr +
                    " on paths #" + std::to_string(inserted.first->second) +
                    " and #" + std::to_string(path.index));
            }
        }

        for (const AoiRecord& aoi : result.aois)
        {
            uint32_t id = 0;
            if (!detail::ParsePointerId(aoi.pathRef, id) || id == 0)
                continue;
            if (aiPathIdOwners.find(id) == aiPathIdOwners.end())
            {
                result.problems.push_back(
                    "AOI #" + std::to_string(aoi.index) +
                    " undefptr references missing AiPath old_ptr " + aoi.pathRef);
            }
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

        // Binary BZNs legitimately contain zero bytes in their binary payload,
        // so NUL is only a text-file hazard after binarySave=false is proven.
        if (result.ascii && result.embeddedNul &&
            !result.utf16LeBom && !result.utf16BeBom)
        {
            result.byteProblems.push_back(
                "embedded NUL byte at offset " + std::to_string(result.firstNulOffset) +
                "; ASCII BZN text can be truncated or misparsed at NUL");
        }

        return result;
    }
}
