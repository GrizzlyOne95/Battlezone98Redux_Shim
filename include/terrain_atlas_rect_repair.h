#pragma once

// Corrects off-grid tile rectangles in a terrain detail-atlas CSV.
//
// Each `<xx>_detail_atlas.csv` maps a terrain .MAP name to a normalized
// rectangle in that world's atlas texture: `name,u,v,w,h`. Redux ships eleven
// of these and nine lay every tile on an exact grid. Two do not:
//
//     ac row7 : AC05CB0.MAP,0.875,0.000,0.125,0.125    on-grid
//     el row7 : EL01DA0.MAP,0.825,0,0.125,0.125        0.825 is a typo
//     ga row7 : GA04DA0.MAP,0.825,0,0.125,0.125        0.825 is a typo
//
// `0.825` with a width of `0.125` spans 0.825..0.950, straddling the cell
// boundary at 0.875, so the tile renders the right 40% of one atlas cell and
// the left 60% of the next. Four rows are affected: rows 7 and 15 of
// el_detail_atlas.csv and ga_detail_atlas.csv, which are the two atlases whose
// materials ship under materials/TRO/. The same bytes are present in the macOS
// Steam depot, so this is upstream in Redux rather than a local corruption.
//
// The repair is deliberately not a table of known-bad values. It only acts on
// a file that is *demonstrably* a uniform grid everywhere else, so a genuinely
// packed atlas (which the format allows) is left alone. See IsRepairable.

#include <cstddef>
#include <string>
#include <vector>

namespace BZROpenShim::TerrainAtlas
{
    struct RepairedRow
    {
        std::size_t lineNumber = 0;  // 1-based, as a text editor shows it
        std::string name;            // may be empty; row 0 is unnamed in every shipped file
        char axis = 'u';             // which coordinate moved
        double from = 0.0;
        double to = 0.0;
    };

    enum class RepairOutcome
    {
        AlreadyCorrect,     // parsed fine, every rect already on the grid
        Repaired,           // at least one rect was snapped
        NotAUniformGrid,    // rects vary in size or too many are off-grid; left alone
        OffGridButAmbiguous,// off-grid, but no single nearest cell to snap to; left alone
        Unparsable          // not a rect CSV at all; left alone
    };

    struct RepairReport
    {
        RepairOutcome outcome = RepairOutcome::Unparsable;
        std::size_t dataRows = 0;
        std::size_t offGridRows = 0;
        std::vector<RepairedRow> repairs;
    };

    // True when `fileName` (with or without directories) is one of the terrain
    // detail-atlas CSVs. Case-insensitive; accepts '/' and '\\'.
    bool IsDetailAtlasCsvName(const std::string& path);

    // Parses `text` as a detail-atlas CSV and, when every precondition holds,
    // writes a corrected copy to `out`. Returns true only when `out` differs
    // from `text`; on every other outcome `out` is left untouched and the
    // caller should keep using the original bytes.
    //
    // Formatting is preserved: only the offending numeric field is rewritten,
    // with the same number of decimal places the source token used, and the
    // line's own terminator (CRLF or LF) is carried through unchanged.
    bool RepairAtlasCsv(const std::string& text, std::string& out, RepairReport& report);

    const char* RepairOutcomeName(RepairOutcome outcome);
}
