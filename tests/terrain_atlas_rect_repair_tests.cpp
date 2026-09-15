#include "terrain_atlas_rect_repair.h"

#include <cstdio>
#include <string>

using namespace BZROpenShim::TerrainAtlas;

namespace
{
    int g_failures = 0;

    void Check(bool condition, const char* what)
    {
        if (condition)
            return;
        std::fprintf(stderr, "FAIL: %s\n", what);
        ++g_failures;
    }

    // The first 16 rows of the shipped el_detail_atlas.csv, byte for byte,
    // including its CRLF terminators and its bare "0" fields. Rows 7 and 15
    // (0-based) carry the 0.825 typo.
    const std::string kElAtlas =
        ",0,0,0.125,0.125\r\n"
        "EL00SA0.MAP,0.125,0,0.125,0.125\r\n"
        "EL00SB0.MAP,0.25,0,0.125,0.125\r\n"
        "EL00SC0.MAP,0.375,0,0.125,0.125\r\n"
        "EL01CA0.MAP,0.5,0,0.125,0.125\r\n"
        "EL02CA0.MAP,0.625,0,0.125,0.125\r\n"
        "EL04CA0.MAP,0.75,0,0.125,0.125\r\n"
        "EL01DA0.MAP,0.825,0,0.125,0.125\r\n"
        "EL02DA0.MAP,0,0.125,0.125,0.125\r\n"
        "EL04DA0.MAP,0.125,0.125,0.125,0.125\r\n"
        "EL11SA0.MAP,0.25,0.125,0.125,0.125\r\n"
        "EL11SB0.MAP,0.375,0.125,0.125,0.125\r\n"
        "EL11SC0.MAP,0.5,0.125,0.125,0.125\r\n"
        "EL12CA0.MAP,0.625,0.125,0.125,0.125\r\n"
        "EL12DA0.MAP,0.75,0.125,0.125,0.125\r\n"
        "EL22SA0.MAP,0.825,0.125,0.125,0.125\r\n";

    // Mars, which is already correct, in its zero-padded "0.000" style.
    const std::string kMaAtlas =
        ",0.000,0.000,0.125,0.125\r\n"
        "MA00SA0.MAP,0.125,0.000,0.125,0.125\r\n"
        "MA00SB0.MAP,0.250,0.000,0.125,0.125\r\n"
        "MA00SC0.MAP,0.375,0.000,0.125,0.125\r\n"
        "MA01CA0.MAP,0.500,0.000,0.125,0.125\r\n"
        "MA04CA0.MAP,0.625,0.000,0.125,0.125\r\n"
        "MA04CB0.MAP,0.750,0.000,0.125,0.125\r\n"
        "MA01DA0.MAP,0.875,0.000,0.125,0.125\r\n";

    bool Contains(const std::string& haystack, const std::string& needle)
    {
        return haystack.find(needle) != std::string::npos;
    }
}

int main()
{
    // --- name matching -----------------------------------------------------
    Check(IsDetailAtlasCsvName("el_detail_atlas.csv"), "bare leaf name matches");
    Check(IsDetailAtlasCsvName("BZ_ASSETS\\common\\materials\\GA_Detail_Atlas.CSV"),
        "backslash path and mixed case match");
    Check(IsDetailAtlasCsvName("/x/y/ti_2_detail_atlas.csv"), "forward slash path matches");
    Check(!IsDetailAtlasCsvName("_detail_atlas.csv"), "suffix alone is not a world atlas");
    Check(!IsDetailAtlasCsvName("el_detail_atlas.material"), "material file does not match");
    Check(!IsDetailAtlasCsvName("atlas.csv"), "unrelated csv does not match");

    // --- the real defect ---------------------------------------------------
    {
        std::string out;
        RepairReport report;
        const bool changed = RepairAtlasCsv(kElAtlas, out, report);
        Check(changed, "el atlas is repaired");
        Check(report.outcome == RepairOutcome::Repaired, "el outcome is Repaired");
        Check(report.dataRows == 16, "el has 16 data rows");
        Check(report.offGridRows == 2, "el has exactly two off-grid rows");
        Check(report.repairs.size() == 2, "el reports two repairs");
        if (report.repairs.size() == 2)
        {
            Check(report.repairs[0].lineNumber == 8, "first repair is on line 8");
            Check(report.repairs[0].name == "EL01DA0.MAP", "first repair names EL01DA0.MAP");
            Check(report.repairs[0].axis == 'u', "first repair moves u");
            Check(report.repairs[1].lineNumber == 16, "second repair is on line 16");
            Check(report.repairs[1].name == "EL22SA0.MAP", "second repair names EL22SA0.MAP");
        }
        Check(Contains(out, "EL01DA0.MAP,0.875,0,0.125,0.125\r\n"), "row 7 becomes 0.875");
        Check(Contains(out, "EL22SA0.MAP,0.875,0.125,0.125,0.125\r\n"), "row 15 becomes 0.875");
        Check(!Contains(out, "0.825"), "no 0.825 survives");
        Check(out.size() == kElAtlas.size(), "byte length is unchanged");
        // Every untouched row must survive exactly, terminators included.
        Check(Contains(out, ",0,0,0.125,0.125\r\n"), "unnamed row 0 is untouched");
        Check(Contains(out, "EL00SB0.MAP,0.25,0,0.125,0.125\r\n"), "bare 0 fields are preserved");
    }

    // --- a correct file is left strictly alone -----------------------------
    {
        std::string out = "sentinel";
        RepairReport report;
        const bool changed = RepairAtlasCsv(kMaAtlas, out, report);
        Check(!changed, "ma atlas is not changed");
        Check(report.outcome == RepairOutcome::AlreadyCorrect, "ma outcome is AlreadyCorrect");
        Check(report.offGridRows == 0, "ma has no off-grid rows");
        Check(out == "sentinel", "out is untouched when nothing is repaired");
    }

    // --- a genuinely packed atlas is not normalized ------------------------
    {
        // Mixed cell sizes: the format allows this and it is not a typo.
        const std::string packed =
            "A.MAP,0.0,0.0,0.5,0.5\r\n"
            "B.MAP,0.5,0.0,0.25,0.25\r\n"
            "C.MAP,0.31,0.62,0.125,0.125\r\n";
        std::string out = "sentinel";
        RepairReport report;
        Check(!RepairAtlasCsv(packed, out, report), "packed atlas is not repaired");
        Check(report.outcome == RepairOutcome::NotAUniformGrid, "packed outcome is NotAUniformGrid");
        Check(out == "sentinel", "packed atlas bytes are untouched");
    }

    {
        // Uniform cell size, but most rows are off-grid: a deliberate layout.
        const std::string offset =
            "A.MAP,0.03,0.0,0.125,0.125\r\n"
            "B.MAP,0.16,0.0,0.125,0.125\r\n"
            "C.MAP,0.28,0.0,0.125,0.125\r\n"
            "D.MAP,0.5,0.0,0.125,0.125\r\n";
        std::string out = "sentinel";
        RepairReport report;
        Check(!RepairAtlasCsv(offset, out, report), "mostly off-grid file is not repaired");
        Check(report.outcome == RepairOutcome::NotAUniformGrid,
            "mostly off-grid outcome is NotAUniformGrid");
    }

    // --- a rect exactly between two cells is never dragged -----------------
    {
        const std::string halfCell =
            "A.MAP,0.0,0.0,0.125,0.125\r\n"
            "B.MAP,0.125,0.0,0.125,0.125\r\n"
            "C.MAP,0.25,0.0,0.125,0.125\r\n"
            "D.MAP,0.375,0.0,0.125,0.125\r\n"
            "E.MAP,0.5,0.0,0.125,0.125\r\n"
            "F.MAP,0.625,0.0,0.125,0.125\r\n"
            "G.MAP,0.75,0.0,0.125,0.125\r\n"
            "H.MAP,0.8125,0.0,0.125,0.125\r\n";
        std::string out;
        RepairReport report;
        const bool changed = RepairAtlasCsv(halfCell, out, report);
        Check(!changed, "an exact half-cell offset is not snapped");
        Check(report.offGridRows == 1, "the half-cell row is still reported as off-grid");
        Check(report.outcome == RepairOutcome::OffGridButAmbiguous,
            "half-cell outcome names the ambiguity");
    }

    // --- non-atlas text is rejected rather than mangled --------------------
    {
        std::string out = "sentinel";
        RepairReport report;
        Check(!RepairAtlasCsv("material MA_DETAIL_ATLAS\r\n{\r\n}\r\n", out, report),
            "a material script is not treated as an atlas");
        Check(report.outcome == RepairOutcome::Unparsable, "material script outcome is Unparsable");
        Check(out == "sentinel", "material script bytes are untouched");

        RepairReport empty;
        std::string emptyOut = "sentinel";
        Check(!RepairAtlasCsv("", emptyOut, empty), "empty input is not repaired");
        Check(empty.outcome == RepairOutcome::Unparsable, "empty outcome is Unparsable");
    }

    // --- LF-only input keeps LF terminators --------------------------------
    {
        const std::string lf =
            ",0,0,0.125,0.125\n"
            "X00SA0.MAP,0.125,0,0.125,0.125\n"
            "X00SB0.MAP,0.25,0,0.125,0.125\n"
            "X00SC0.MAP,0.375,0,0.125,0.125\n"
            "X01CA0.MAP,0.5,0,0.125,0.125\n"
            "X02CA0.MAP,0.625,0,0.125,0.125\n"
            "X04CA0.MAP,0.75,0,0.125,0.125\n"
            "X01DA0.MAP,0.825,0,0.125,0.125\n";
        std::string out;
        RepairReport report;
        Check(RepairAtlasCsv(lf, out, report), "LF atlas is repaired");
        Check(Contains(out, "X01DA0.MAP,0.875,0,0.125,0.125\n"), "LF row becomes 0.875");
        Check(out.find('\r') == std::string::npos, "no CR is introduced");
    }

    // --- decimal formatting follows the source token -----------------------
    {
        // Same defect written with three decimals must come back with three.
        const std::string padded =
            ",0.000,0.000,0.125,0.125\r\n"
            "P00SA0.MAP,0.125,0.000,0.125,0.125\r\n"
            "P00SB0.MAP,0.250,0.000,0.125,0.125\r\n"
            "P00SC0.MAP,0.375,0.000,0.125,0.125\r\n"
            "P01CA0.MAP,0.500,0.000,0.125,0.125\r\n"
            "P02CA0.MAP,0.625,0.000,0.125,0.125\r\n"
            "P04CA0.MAP,0.750,0.000,0.125,0.125\r\n"
            "P01DA0.MAP,0.825,0.000,0.125,0.125\r\n";
        std::string out;
        RepairReport report;
        Check(RepairAtlasCsv(padded, out, report), "padded atlas is repaired");
        Check(Contains(out, "P01DA0.MAP,0.875,0.000,0.125,0.125\r\n"),
            "three-decimal source keeps three decimals");
    }

    // --- repairing twice is a no-op ----------------------------------------
    {
        std::string once;
        RepairReport first;
        Check(RepairAtlasCsv(kElAtlas, once, first), "first pass repairs");
        std::string twice = "sentinel";
        RepairReport second;
        Check(!RepairAtlasCsv(once, twice, second), "second pass finds nothing to do");
        Check(second.outcome == RepairOutcome::AlreadyCorrect, "repair is idempotent");
    }

    if (g_failures == 0)
        std::puts("terrain atlas rect repair tests passed");
    return g_failures == 0 ? 0 : 1;
}
