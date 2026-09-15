// terrain_atlas_rect_repair.cpp
// BZR Open Shim - off-grid terrain atlas rectangle correction
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "terrain_atlas_rect_repair.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>

namespace BZROpenShim::TerrainAtlas
{
    namespace
    {
        // A file is only repaired when at most this share of its rows are off
        // the grid. Above it, "off-grid" is the file's design rather than a
        // typo. The two real cases are 2 rows in 21 and 2 in 23.
        constexpr double kMaxOffGridFraction = 0.25;

        // A coordinate is snapped only if it is already within this fraction of
        // a cell of the grid position, so a rect deliberately placed at a half
        // cell is never dragged to a neighbour.
        constexpr double kMaxSnapFractionOfCell = 0.5;

        constexpr double kEpsilon = 1e-9;

        struct Token
        {
            std::size_t offset = 0;  // into the whole text
            std::size_t length = 0;
            double value = 0.0;
            int decimals = 0;
            bool valid = false;
        };

        // Deliberately not strtod/from_chars: the CSV is always dot-decimal,
        // but this runs inside a process whose locale Redux owns, and a comma
        // locale would make strtod stop at the decimal point and silently read
        // 0.825 as 0. Hand-parsing also yields the decimal-place count, which
        // the rewrite needs to preserve the source formatting.
        bool ParseDotDecimal(const std::string& text,
                             std::size_t begin,
                             std::size_t end,
                             double& value,
                             int& decimals)
        {
            std::size_t i = begin;
            while (i < end && std::isspace(static_cast<unsigned char>(text[i])))
                ++i;
            std::size_t stop = end;
            while (stop > i && std::isspace(static_cast<unsigned char>(text[stop - 1])))
                --stop;
            if (i >= stop)
                return false;

            bool negative = false;
            if (text[i] == '+' || text[i] == '-')
            {
                negative = (text[i] == '-');
                ++i;
            }

            bool sawDigit = false;
            double whole = 0.0;
            while (i < stop && std::isdigit(static_cast<unsigned char>(text[i])))
            {
                whole = whole * 10.0 + static_cast<double>(text[i] - '0');
                sawDigit = true;
                ++i;
            }

            int places = 0;
            double fraction = 0.0;
            double scale = 1.0;
            if (i < stop && text[i] == '.')
            {
                ++i;
                while (i < stop && std::isdigit(static_cast<unsigned char>(text[i])))
                {
                    fraction = fraction * 10.0 + static_cast<double>(text[i] - '0');
                    scale *= 10.0;
                    sawDigit = true;
                    ++places;
                    ++i;
                }
            }

            if (!sawDigit || i != stop)
                return false;  // trailing junk, exponent, or an empty field

            value = whole + (scale > 1.0 ? fraction / scale : 0.0);
            if (negative)
                value = -value;
            decimals = places;
            return true;
        }

        std::string FormatWithDecimals(double value, int decimals)
        {
            // %.*f is locale-sensitive for the decimal point, so format the
            // integer and fractional halves separately and join with a literal
            // '.'. Values here are in 0..1 with at most a handful of places.
            const bool negative = value < 0.0;
            const double magnitude = negative ? -value : value;
            double scale = 1.0;
            for (int i = 0; i < decimals; ++i)
                scale *= 10.0;

            const double scaled = magnitude * scale;
            const long long rounded = static_cast<long long>(scaled + 0.5);
            const long long whole = decimals > 0 ? rounded / static_cast<long long>(scale) : rounded;
            const long long frac = decimals > 0 ? rounded % static_cast<long long>(scale) : 0;

            std::string result;
            if (negative)
                result.push_back('-');
            result += std::to_string(whole);

            if (decimals > 0)
            {
                result.push_back('.');
                const std::string fraction = std::to_string(frac);
                const std::size_t width = static_cast<std::size_t>(decimals);
                if (fraction.size() < width)
                    result.append(width - fraction.size(), '0');
                result += fraction;
            }
            return result;
        }

        bool IsOnGrid(double coordinate, double cell)
        {
            if (cell <= kEpsilon)
                return true;  // nothing to be on or off
            const double steps = coordinate / cell;
            return std::fabs(steps - std::floor(steps + 0.5)) < 1e-6;
        }

        // Snapped position, or the original when snapping would move it too far.
        bool TrySnap(double coordinate, double cell, double& snapped)
        {
            if (cell <= kEpsilon)
                return false;
            const double target = std::floor(coordinate / cell + 0.5) * cell;
            // Strictly nearer, not merely no further: a rect sitting exactly
            // half a cell out is equidistant from both neighbours, so there is
            // no nearest cell to snap it to and picking one would be a guess.
            // That is also the shape a deliberate straddle would take.
            if (std::fabs(target - coordinate) >= cell * kMaxSnapFractionOfCell)
                return false;
            if (target < -kEpsilon || target + cell > 1.0 + 1e-6)
                return false;  // snapping off the atlas is never a repair
            snapped = target;
            return true;
        }

        std::string ToLowerAscii(std::string value)
        {
            std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
                return static_cast<char>(std::tolower(ch));
            });
            return value;
        }

        struct ParsedRow
        {
            std::size_t lineNumber = 0;
            std::string name;
            Token u;
            Token v;
            double w = 0.0;
            double h = 0.0;
            bool valid = false;
        };
    }

    const char* RepairOutcomeName(RepairOutcome outcome)
    {
        switch (outcome)
        {
        case RepairOutcome::AlreadyCorrect: return "already-correct";
        case RepairOutcome::Repaired:       return "repaired";
        case RepairOutcome::NotAUniformGrid:return "not-a-uniform-grid";
        case RepairOutcome::OffGridButAmbiguous: return "off-grid-but-ambiguous";
        default:                            return "unparsable";
        }
    }

    bool IsDetailAtlasCsvName(const std::string& path)
    {
        const std::string lower = ToLowerAscii(path);
        const std::size_t slash = lower.find_last_of("/\\");
        const std::string leaf = (slash == std::string::npos) ? lower : lower.substr(slash + 1);
        // "_detail_atlas.csv" is 17 characters; the shipped names prefix it
        // with a two-letter world code, so require at least one prefix char.
        constexpr std::size_t kSuffixLength = 17;
        if (leaf.size() <= kSuffixLength)
            return false;
        return leaf.compare(leaf.size() - kSuffixLength, kSuffixLength, "_detail_atlas.csv") == 0;
    }

    bool RepairAtlasCsv(const std::string& text, std::string& out, RepairReport& report)
    {
        report = RepairReport{};

        std::vector<ParsedRow> rows;
        std::size_t lineStart = 0;
        std::size_t lineNumber = 0;

        while (lineStart <= text.size())
        {
            std::size_t lineEnd = text.find('\n', lineStart);
            const bool last = (lineEnd == std::string::npos);
            if (last)
                lineEnd = text.size();
            ++lineNumber;

            // Content span excludes the terminator; a trailing CR belongs to it.
            std::size_t contentEnd = lineEnd;
            if (contentEnd > lineStart && text[contentEnd - 1] == '\r')
                --contentEnd;

            if (contentEnd > lineStart)
            {
                // Split into at most five fields.
                std::size_t fieldStart[5] = {};
                std::size_t fieldEnd[5] = {};
                int fields = 0;
                std::size_t cursor = lineStart;
                while (fields < 5 && cursor <= contentEnd)
                {
                    std::size_t comma = text.find(',', cursor);
                    if (comma == std::string::npos || comma > contentEnd)
                        comma = contentEnd;
                    fieldStart[fields] = cursor;
                    fieldEnd[fields] = comma;
                    ++fields;
                    if (comma >= contentEnd)
                        break;
                    cursor = comma + 1;
                }

                if (fields == 5)
                {
                    ParsedRow row;
                    row.lineNumber = lineNumber;
                    row.name = text.substr(fieldStart[0], fieldEnd[0] - fieldStart[0]);

                    double w = 0.0;
                    double h = 0.0;
                    int wDecimals = 0;
                    int hDecimals = 0;
                    row.u.valid = ParseDotDecimal(text, fieldStart[1], fieldEnd[1], row.u.value, row.u.decimals);
                    row.u.offset = fieldStart[1];
                    row.u.length = fieldEnd[1] - fieldStart[1];
                    row.v.valid = ParseDotDecimal(text, fieldStart[2], fieldEnd[2], row.v.value, row.v.decimals);
                    row.v.offset = fieldStart[2];
                    row.v.length = fieldEnd[2] - fieldStart[2];
                    const bool haveW = ParseDotDecimal(text, fieldStart[3], fieldEnd[3], w, wDecimals);
                    const bool haveH = ParseDotDecimal(text, fieldStart[4], fieldEnd[4], h, hDecimals);
                    row.w = w;
                    row.h = h;
                    row.valid = row.u.valid && row.v.valid && haveW && haveH && w > kEpsilon && h > kEpsilon;
                    rows.push_back(std::move(row));
                }
            }

            if (last)
                break;
            lineStart = lineEnd + 1;
        }

        const std::size_t validRows = static_cast<std::size_t>(
            std::count_if(rows.begin(), rows.end(), [](const ParsedRow& r) { return r.valid; }));
        report.dataRows = validRows;
        if (validRows == 0 || validRows != rows.size())
        {
            // Every non-empty line of a real atlas CSV is a rect row. A file
            // with headers, comments or ragged rows is not this format.
            report.outcome = RepairOutcome::Unparsable;
            return false;
        }

        // Precondition: one cell size for the whole file. The shipped files use
        // 0.125 (eight columns) or 0.25 (four); a file that mixes sizes is a
        // packed atlas and is not ours to normalize.
        const double cellW = rows.front().w;
        const double cellH = rows.front().h;
        for (const ParsedRow& row : rows)
        {
            if (std::fabs(row.w - cellW) > 1e-6 || std::fabs(row.h - cellH) > 1e-6)
            {
                report.outcome = RepairOutcome::NotAUniformGrid;
                return false;
            }
        }

        std::vector<const ParsedRow*> offGrid;
        for (const ParsedRow& row : rows)
        {
            if (!IsOnGrid(row.u.value, cellW) || !IsOnGrid(row.v.value, cellH))
                offGrid.push_back(&row);
        }
        report.offGridRows = offGrid.size();

        if (offGrid.empty())
        {
            report.outcome = RepairOutcome::AlreadyCorrect;
            return false;
        }

        if (static_cast<double>(offGrid.size()) >
            static_cast<double>(rows.size()) * kMaxOffGridFraction)
        {
            report.outcome = RepairOutcome::NotAUniformGrid;
            return false;
        }

        // Collect the edits first so a row that cannot be snapped safely aborts
        // nothing but itself, then apply them back-to-front so earlier offsets
        // stay valid.
        struct Edit
        {
            std::size_t offset;
            std::size_t length;
            std::string replacement;
        };
        std::vector<Edit> edits;

        for (const ParsedRow* row : offGrid)
        {
            double snapped = 0.0;
            if (!IsOnGrid(row->u.value, cellW) && TrySnap(row->u.value, cellW, snapped))
            {
                edits.push_back({ row->u.offset, row->u.length,
                                  FormatWithDecimals(snapped, row->u.decimals) });
                report.repairs.push_back({ row->lineNumber, row->name, 'u', row->u.value, snapped });
            }
            if (!IsOnGrid(row->v.value, cellH) && TrySnap(row->v.value, cellH, snapped))
            {
                edits.push_back({ row->v.offset, row->v.length,
                                  FormatWithDecimals(snapped, row->v.decimals) });
                report.repairs.push_back({ row->lineNumber, row->name, 'v', row->v.value, snapped });
            }
        }

        if (edits.empty())
        {
            // Off-grid but not safely snappable: report it and change nothing.
            report.outcome = RepairOutcome::OffGridButAmbiguous;
            return false;
        }

        std::sort(edits.begin(), edits.end(),
                  [](const Edit& a, const Edit& b) { return a.offset > b.offset; });

        out = text;
        for (const Edit& edit : edits)
            out.replace(edit.offset, edit.length, edit.replacement);

        report.outcome = RepairOutcome::Repaired;
        return out != text;
    }
}
