// bzn_analysis_tests.cpp
// Structural analysis of ASCII mission files.
//
// The case that matters is MixedLineEndingsNameTheStoppingObject: it is the
// 2026-09-07 misn04 failure reduced to its shape. An agent hand-edited the file
// and wrote LF endings for the lines it touched, so the file was CRLF
// everywhere except a run inside one GameObject. The engine's reader is
// line-oriented on CRLF, that run collapsed into one unparseable line, and the
// load aborted on exactly that object -- with nothing in any log naming it.

#include "bzn_analysis.h"

#include <cstdio>
#include <string>
#include <string_view>
#include <vector>

namespace
{
    int g_Failures = 0;

    void Check(bool condition, const char* what)
    {
        if (!condition)
        {
            std::printf("FAIL: %s\n", what);
            g_Failures++;
        }
    }

    // Builds a small but structurally faithful mission. Lines are joined with
    // CRLF except those whose index falls in [lfBegin, lfEnd), which get a bare
    // LF -- the corruption shape this module exists to catch.
    std::string Build(const std::vector<std::string>& lines, size_t lfBegin = 0, size_t lfEnd = 0)
    {
        std::string out;
        for (size_t i = 0; i < lines.size(); ++i)
        {
            out += lines[i];
            const bool bare = (i >= lfBegin && i < lfEnd);
            out += bare ? "\n" : "\r\n";
        }
        return out;
    }

    std::vector<std::string> SampleMission()
    {
        return {
            "version [1] =",
            "2016",
            "binarySave [1] =",
            "false",
            "msn_filename = sample.bzn",
            "seq_count [1] =",
            "8",
            "TerrainName = sample",
            "[GameObject]",          // 8  -> object #0
            "PrjID [1] =",
            "player",
            "seqno [1] =",
            "1",
            "team [1] =",
            "1",
            "label = player-1_hover",
            "obj_addr = 00000001",
            "[GameObject]",          // 17 -> object #1
            "PrjID [1] =",
            "sfield",
            "seqno [1] =",
            "2",
            "pos [1] =",
            "  x [1] =",
            "2449.16",
            "  y [1] =",
            "3.58727",
            "team [1] =",
            "0",
            "label = sfield1_scrapfield",
            "obj_addr = 00000002",
            "[GameObject]",          // 31 -> object #2
            "PrjID [1] =",
            "avfigh",
            "seqno [1] =",
            "3",
            "team [1] =",
            "1",
            "label = avfigh0_wingman",
            "obj_addr = 00000003",
            "sObject = 00000002",
            "[AiPaths]",
            "count [1] =",
            "2",
            "[AiPath]",
            "old_ptr = 0000000B",
            "size [1] =",
            "0",
            "pointCount [1] =",
            "1",
            "[AiPath]",
            "old_ptr = 000000B9",
            "size [1] =",
            "8",
            "label = cca_base",
            "pointCount [1] =",
            "1",
        };
    }
}

int main()
{
    using namespace BZROpenShim::BznAnalysis;

    // --- a clean file reports clean -----------------------------------------
    {
        const std::string data = Build(SampleMission());
        const Result r = Analyze(data);

        Check(r.ascii, "clean: recognised as an ascii save");
        Check(r.version == "2016", "clean: version read");
        Check(r.terrainName == "sample", "clean: terrain name read");
        Check(r.seqCount == "8", "clean: seq_count read");
        Check(r.objects.size() == 3, "clean: three GameObject blocks");
        Check(r.pathBlocks == 2, "clean: two AiPath blocks");
        Check(r.declaredPathCount == "2", "clean: declared path count read");
        Check(!r.endings.mixed(), "clean: line endings uniform");
        Check(r.endings.bareLf == 0, "clean: no bare LF");
        Check(r.problems.empty(), "clean: no structural problems");

        Check(r.objects[1].prjId == "sfield", "clean: object #1 ODF");
        Check(r.objects[1].label == "sfield1_scrapfield", "clean: object #1 label");
        Check(r.objects[1].team == "0", "clean: object #1 team");
        Check(r.objects[1].seqno == "2", "clean: object #1 seqno");
    }

    // --- the misn04 shape: a bare-LF run inside one object ------------------
    {
        // Lines 22..29 sit inside object #1 (header at index 17), which is the
        // same relationship the real file had: the run began in the position
        // block of the object the engine then died on.
        const std::string data = Build(SampleMission(), 22, 30);
        const Result r = Analyze(data);

        Check(r.endings.mixed(), "mixed: detected as mixed");
        Check(r.endings.bareLf == 8, "mixed: counted the bare-LF lines");
        Check(r.endings.crlf > 0, "mixed: still counted the CRLF lines");
        Check(r.endings.firstBareLine == 23, "mixed: located the first bare LF (1-based)");
        Check(r.mixedEnclosingObject == 1, "mixed: named the enclosing GameObject");
        Check(r.objects[r.mixedEnclosingObject].prjId == "sfield",
              "mixed: enclosing object carries its ODF for the report");
    }

    // --- a bare LF before any object ----------------------------------------
    {
        const std::string data = Build(SampleMission(), 1, 3);
        const Result r = Analyze(data);
        Check(r.endings.mixed(), "header-mixed: detected");
        Check(r.mixedEnclosingObject == kNone, "header-mixed: no enclosing object");
    }

    // --- a uniformly LF file is not "mixed" ---------------------------------
    {
        std::string data;
        for (const std::string& line : SampleMission())
            data += line + "\n";
        const Result r = Analyze(data);
        Check(!r.endings.mixed(), "uniform LF: not reported as mixed");
        Check(r.endings.crlf == 0, "uniform LF: no CRLF counted");
        Check(r.objects.size() == 3, "uniform LF: still parses");
    }

    // --- path count disagreeing with the blocks -----------------------------
    {
        std::vector<std::string> lines = SampleMission();
        lines[43] = "5";  // the [AiPaths] count value; the file still has 2 blocks
        const std::string data = Build(lines);
        const Result r = Analyze(data);

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("[AiPaths] count says 5") != std::string::npos;
        Check(found, "path count: mismatch reported");
    }

    // --- duplicate labels ----------------------------------------------------
    {
        std::vector<std::string> lines = SampleMission();
        lines[38] = "label = sfield1_scrapfield";  // clash with object #1
        const std::string data = Build(lines);
        const Result r = Analyze(data);

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("duplicate label 'sfield1_scrapfield'") != std::string::npos;
        Check(found, "duplicate label: reported");
    }

    // --- a pointer reference that resolves to nothing ------------------------
    {
        std::vector<std::string> lines = SampleMission();
        lines[40] = "sObject = 0000007A";  // no obj_addr or old_ptr defines 7A
        const std::string data = Build(lines);
        const Result r = Analyze(data);

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("sObject references undefined id 0000007A") != std::string::npos;
        Check(found, "dangling pointer: reported");
    }

    // --- a null sObject is not a dangling reference --------------------------
    {
        std::vector<std::string> lines = SampleMission();
        lines[40] = "sObject = 00000000";
        const std::string data = Build(lines);
        const Result r = Analyze(data);
        for (const std::string& p : r.problems)
            Check(p.find("sObject") == std::string::npos, "null sObject: not reported");
    }

    // --- a binary save is recognised and skipped -----------------------------
    {
        std::vector<std::string> lines = SampleMission();
        lines[3] = "true";
        const std::string data = Build(lines);
        const Result r = Analyze(data);
        Check(!r.ascii, "binary: not treated as ascii");
        Check(r.sawBinarySaveField, "binary: binarySave field was seen");
    }

    // --- an empty file must not crash or invent findings ---------------------
    {
        const Result r = Analyze(std::string_view());
        Check(r.objects.empty(), "empty: no objects");
        Check(r.problems.empty(), "empty: no problems");
        Check(!r.endings.mixed(), "empty: not mixed");
    }

    if (g_Failures == 0)
    {
        std::printf("bzn_analysis_tests: all checks passed\n");
        return 0;
    }
    std::printf("bzn_analysis_tests: %d failure(s)\n", g_Failures);
    return 1;
}
