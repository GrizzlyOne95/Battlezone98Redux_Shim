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

#include <algorithm>
#include <cstdio>
#include <iterator>
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

    size_t FindLine(const std::vector<std::string>& lines, const std::string& value)
    {
        const auto it = std::find(lines.begin(), lines.end(), value);
        if (it == lines.end())
            return static_cast<size_t>(-1);
        return static_cast<size_t>(std::distance(lines.begin(), it));
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
            "size [1] =",
            "3",
            "[GameObject]",          // 10 -> object #0
            "PrjID [1] =",
            "player",
            "seqno [1] =",
            "1",
            "pos [1] =",
            "  x [1] =",
            "100",
            "team [1] =",
            "1",
            "label = player-1_hover",
            "isUser [1] =",
            "1",
            "obj_addr = 00000001",
            "transform [1] =",
            "  right_x [1] =",
            "1",
            "[GameObject]",          // 19 -> object #1
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
            "isUser [1] =",
            "0",
            "obj_addr = 00000002",
            "transform [1] =",
            "  right_x [1] =",
            "1",
            "[GameObject]",          // 33 -> object #2
            "PrjID [1] =",
            "avfigh",
            "seqno [1] =",
            "3",
            "pos [1] =",
            "  x [1] =",
            "300",
            "team [1] =",
            "1",
            "label = avfigh0_wingman",
            "isUser [1] =",
            "0",
            "obj_addr = 00000003",
            "transform [1] =",
            "  right_x [1] =",
            "1",
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
            "points [1] =",
            "  x [1] =",
            "10",
            "  z [1] =",
            "20",
            "[AiPath]",
            "old_ptr = 000000B9",
            "size [1] =",
            "8",
            "label = cca_base",
            "pointCount [1] =",
            "1",
            "points [1] =",
            "  x [1] =",
            "30",
            "  z [1] =",
            "40",
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
        Check(r.declaredObjectCount == "3", "clean: declared GameObject count read");
        Check(r.objects.size() == 3, "clean: three GameObject blocks");
        Check(r.pathBlocks == 2, "clean: two AiPath blocks");
        Check(r.declaredPathCount == "2", "clean: declared path count read");
        Check(!r.endings.unsafe(), "clean: CRLF-only endings are safe");
        Check(!r.endings.mixed(), "clean: line endings uniform");
        Check(r.endings.bareLf == 0, "clean: no bare LF");
        Check(r.endings.bareCr == 0, "clean: no bare CR");
        Check(r.problems.empty(), "clean: no structural problems");

        Check(r.objects[1].prjId == "sfield", "clean: object #1 ODF");
        Check(r.objects[1].label == "sfield1_scrapfield", "clean: object #1 label");
        Check(r.objects[1].team == "0", "clean: object #1 team");
        Check(r.objects[1].seqno == "2", "clean: object #1 seqno");
    }

    // --- the misn04 shape: a bare-LF run inside one object ------------------
    {
        // Lines 24..31 sit inside object #1 (header at index 19), which is the
        // same relationship the real file had: the run began in the position
        // block of the object the engine then died on.
        const std::vector<std::string> lines = SampleMission();
        const size_t lfBegin = FindLine(lines, "pos [1] =");
        const std::string data = Build(lines, lfBegin, lfBegin + 8);
        const Result r = Analyze(data);

        Check(r.endings.unsafe(), "mixed: detected as unsafe");
        Check(r.endings.mixed(), "mixed: detected as mixed");
        Check(r.endings.bareLf == 8, "mixed: counted the bare-LF lines");
        Check(r.endings.bareCr == 0, "mixed: no bare CR");
        Check(r.endings.crlf > 0, "mixed: still counted the CRLF lines");
        Check(r.endings.firstUnsafeLine == lfBegin + 1,
              "mixed: located the first unsafe terminator (1-based)");
        Check(r.unsafeEnclosingObject == 1, "mixed: named the enclosing GameObject");
        Check(r.objects[r.unsafeEnclosingObject].prjId == "sfield",
              "mixed: enclosing object carries its ODF for the report");
    }

    // --- a bare LF before any object ----------------------------------------
    {
        const std::string data = Build(SampleMission(), 1, 3);
        const Result r = Analyze(data);
        Check(r.endings.unsafe(), "header-mixed: detected as unsafe");
        Check(r.endings.mixed(), "header-mixed: detected as mixed");
        Check(r.unsafeEnclosingObject == kNone, "header-mixed: no enclosing object");
    }

    // --- uniformly LF is unsafe even though it is not mixed ------------------
    {
        std::string data;
        for (const std::string& line : SampleMission())
            data += line + "\n";
        const Result r = Analyze(data);
        Check(r.endings.unsafe(), "uniform LF: reported as unsafe");
        Check(!r.endings.mixed(), "uniform LF: not falsely reported as mixed");
        Check(r.endings.crlf == 0, "uniform LF: no CRLF counted");
        Check(r.endings.bareLf == SampleMission().size(), "uniform LF: every terminator counted");
        Check(r.endings.firstUnsafeLine == 1, "uniform LF: first unsafe terminator is line 1");
        Check(r.objects.size() == 3, "uniform LF: still parses for diagnostics");
    }

    // --- a bare CR amid CRLF is unsafe and mapped to its object ---------------
    {
        const std::vector<std::string> lines = SampleMission();
        std::string data;
        const size_t crBegin = FindLine(lines, "pos [1] =");
        for (size_t i = 0; i < lines.size(); ++i)
        {
            data += lines[i];
            data += (i >= crBegin && i < crBegin + 2) ? "\r" : "\r\n";
        }

        const Result r = Analyze(data);
        Check(r.endings.unsafe(), "bare CR: detected as unsafe");
        Check(r.endings.mixed(), "bare CR: mixed with CRLF");
        Check(r.endings.bareCr == 2, "bare CR: counted");
        Check(r.endings.bareLf == 0, "bare CR: no bare LF");
        Check(r.endings.firstUnsafeLine == crBegin + 1, "bare CR: first unsafe terminator located");
        Check(r.unsafeEnclosingObject == 1, "bare CR: enclosing GameObject identified");
        Check(r.objects.size() == 3, "bare CR: parser still recovers all objects for diagnostics");
    }

    // --- GameObject count disagreeing with the blocks ----------------------
    {
        std::vector<std::string> lines = SampleMission();
        lines[FindLine(lines, "3")] = "2";  // declared object count; the file still has 3 blocks
        const Result r = Analyze(Build(lines));

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("GameObject size says 2 but the file has 3") != std::string::npos;
        Check(found, "object count: under-count reported");
    }
    {
        std::vector<std::string> lines = SampleMission();
        lines[FindLine(lines, "3")] = "5";  // over-count is equally dangerous: LoadAll will read into the tail
        const Result r = Analyze(Build(lines));

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("GameObject size says 5 but the file has 3") != std::string::npos;
        Check(found, "object count: over-count reported");
    }

    // --- AOI count disagreeing with the blocks ------------------------------
    {
        std::vector<std::string> lines = SampleMission();
        const auto pos = std::find(lines.begin(), lines.end(), "[AiPaths]");
        lines.insert(pos, {
            "[AOIs]",
            "size [1] =",
            "2",
            "[AOI]",
            "undefptr = 0000000B",
            "team [1] =",
            "1",
            "[AOI]",
            "undefptr = 000000B9",
            "team [1] =",
            "2",
        });
        const Result r = Analyze(Build(lines));

        Check(r.declaredAoiCount == "2", "AOI count: declared size read");
        Check(r.aoiBlocks == 2, "AOI count: two blocks counted");
        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("[AOIs] size") != std::string::npos;
        Check(!found, "AOI count: matching count stays clean");
    }
    {
        std::vector<std::string> lines = SampleMission();
        const auto pos = std::find(lines.begin(), lines.end(), "[AiPaths]");
        lines.insert(pos, {
            "[AOIs]",
            "size [1] =",
            "1",
            "[AOI]",
            "undefptr = 0000000B",
            "[AOI]",
            "undefptr = 000000B9",
        });
        const Result r = Analyze(Build(lines));

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("[AOIs] size says 1 but the file has 2") != std::string::npos;
        Check(found, "AOI count: over-block mismatch reported");
    }
    {
        std::vector<std::string> lines = SampleMission();
        const auto pos = std::find(lines.begin(), lines.end(), "[AiPaths]");
        lines.insert(pos, {
            "[AOIs]",
            "size [1] =",
            "3",
            "[AOI]",
            "undefptr = 0000000B",
            "[AOI]",
            "undefptr = 000000B9",
        });
        const Result r = Analyze(Build(lines));

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("[AOIs] size says 3 but the file has 2") != std::string::npos;
        Check(found, "AOI count: under-block mismatch reported");
    }

    // --- required GameObject envelope fields --------------------------------
    {
        const Result r = Analyze(Build(SampleMission()));
        for (const std::string& p : r.problems)
            Check(p.find("missing required envelope field") == std::string::npos,
                  "object envelope: clean fixture has every required field");
    }
    {
        struct MissingCase
        {
            const char* serializedLine;
            const char* fieldName;
        };
        const MissingCase cases[] = {
            {"PrjID [1] =", "PrjID"},
            {"seqno [1] =", "seqno"},
            {"pos [1] =", "pos"},
            {"team [1] =", "team"},
            {"label = player-1_hover", "label"},
            {"isUser [1] =", "isUser"},
            {"obj_addr = 00000001", "obj_addr"},
            {"transform [1] =", "transform"},
        };

        for (const MissingCase& test : cases)
        {
            std::vector<std::string> lines = SampleMission();
            lines[FindLine(lines, test.serializedLine)] = "missing_envelope_field = 0";
            const Result r = Analyze(Build(lines));

            const std::string needle =
                std::string("GameObject #0 is missing required envelope field(s): ") +
                test.fieldName;
            bool found = false;
            for (const std::string& p : r.problems)
                found = found || p.find(needle) != std::string::npos;
            Check(found, test.fieldName);
        }
    }
    {
        std::vector<std::string> lines = SampleMission();
        lines[FindLine(lines, "2016")] = "1001";
        lines[FindLine(lines, "transform [1] =")] = "missingTransform [1] =";
        const Result r = Analyze(Build(lines));

        for (const std::string& p : r.problems)
            Check(!(p.find("GameObject #0 is missing required envelope field(s):") !=
                        std::string::npos &&
                    p.find("transform") != std::string::npos),
                  "object envelope: version 1001 does not require transform");
    }

    // --- structural counts must be valid non-negative decimals --------------
    {
        std::vector<std::string> lines = SampleMission();
        lines[FindLine(lines, "3")] = "not-a-number";
        const Result r = Analyze(Build(lines));

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("GameObject size is not a valid decimal count") !=
                                 std::string::npos;
        Check(found, "count sanity: invalid GameObject size reported");
    }
    {
        std::vector<std::string> lines = SampleMission();
        const auto pos = std::find(lines.begin(), lines.end(), "[AiPaths]");
        lines.insert(pos, {"[AOIs]", "size [1] =", "-1"});
        const Result r = Analyze(Build(lines));

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("[AOIs] size is negative: -1") != std::string::npos;
        Check(found, "count sanity: negative AOI size reported");
    }
    {
        std::vector<std::string> lines = SampleMission();
        const size_t aiPaths = FindLine(lines, "[AiPaths]");
        lines[aiPaths + 2] = "999999";
        const Result r = Analyze(Build(lines));

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || (p.find("[AiPaths] count says 999999") != std::string::npos &&
                              p.find("count is impossible") != std::string::npos);
        Check(found, "count sanity: impossible AiPath block count reported");
    }
    {
        std::vector<std::string> lines = SampleMission();
        const size_t firstPointCount = FindLine(lines, "pointCount [1] =");
        lines[firstPointCount + 1] = "oops";
        const Result r = Analyze(Build(lines));

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("AiPath #0 pointCount is not a valid decimal count") !=
                                 std::string::npos;
        Check(found, "count sanity: invalid pointCount reported");
    }
    {
        std::vector<std::string> lines = SampleMission();
        const size_t firstPoints = FindLine(lines, "points [1] =");
        lines[firstPoints] = "points [-1] =";
        const Result r = Analyze(Build(lines));

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("AiPath #0 points array count is negative: -1") !=
                                 std::string::npos;
        Check(found, "count sanity: negative points array count reported");
    }

    // --- AiPath pointCount and serialized points must agree -----------------
    {
        const Result r = Analyze(Build(SampleMission()));
        Check(r.paths.size() == 2, "path points: two path records captured");
        Check(r.paths[0].pointCount == "1", "path points: pointCount captured");
        Check(r.paths[0].declaredPoints == 1, "path points: points array count captured");
        Check(r.paths[0].xComponents == 1 && r.paths[0].zComponents == 1,
              "path points: complete coordinate pair counted");
    }
    {
        std::vector<std::string> lines = SampleMission();
        const size_t firstPointCount = FindLine(lines, "pointCount [1] =");
        lines[firstPointCount + 1] = "2";
        const Result r = Analyze(Build(lines));

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("AiPath #0 pointCount says 2 but points array declares 1") !=
                                 std::string::npos;
        Check(found, "path points: pointCount mismatch reported");
    }
    {
        std::vector<std::string> lines = SampleMission();
        const size_t firstPoints = FindLine(lines, "points [1] =");
        lines[firstPoints] = "points [2] =";
        const Result r = Analyze(Build(lines));

        bool found = false;
        for (const std::string& p : r.problems)
            found = found || p.find("AiPath #0 points array declares 2 but file contains 1") !=
                                 std::string::npos;
        Check(found, "path points: serialized pair mismatch reported");
    }

    // --- path count disagreeing with the blocks -----------------------------
    {
        std::vector<std::string> lines = SampleMission();
        const size_t aiPaths = FindLine(lines, "[AiPaths]");
        lines[aiPaths + 2] = "5";  // the [AiPaths] count value; the file still has 2 blocks
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
        lines[FindLine(lines, "label = avfigh0_wingman")] =
            "label = sfield1_scrapfield";  // clash with object #1
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
        lines[FindLine(lines, "sObject = 00000002")] =
            "sObject = 0000007A";  // no obj_addr or old_ptr defines 7A
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
        lines[FindLine(lines, "sObject = 00000002")] = "sObject = 00000000";
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
