// Offline CLI Parser Test Suite
//
// Models Redux's ProcessCommandLine (FUN_007D5120) closely enough to prove
// both the stock multi-parameter defect and the production fix in
// src/patches/cli_multiparam_parser.cpp.
//
// The production fix changes exactly one thing about the stock parser: the
// strtok delimiter set at 0x008F068C, from " ,\t" to " \t". So the model here
// is written once and run twice, with each delimiter set, rather than as two
// separate parsers. Anything these tests prove about the "repaired" run is a
// property of the stock parser fed the repaired delimiters, which is precisely
// what ships.
//
// Input convention: the parser receives WinMain's lpCmdLine, i.e. the
// arguments WITHOUT the program name. FUN_00618C10 passes its third parameter
// straight to FUN_007D5120 and uses the same value for the window/title setup
// path, and a stock launch does not corrupt the map-name buffer, which it
// would if argv[0] reached the positional branch.
//
// Engine-independent: links no engine patch code.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <algorithm>

// Portable case-insensitive compare helpers: MSVC uses _strnicmp/_stricmp
// while POSIX (g++ test harness) provides strncasecmp/strcasecmp.
#if defined(_MSC_VER)
#include <string.h>
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

namespace
{
    int g_failures = 0;

    void ExpectTrue(bool condition, const char* message)
    {
        if (!condition)
        {
            std::cerr << "FAIL: " << message << std::endl;
            ++g_failures;
        }
    }

    // The stock delimiter set at 0x008F068C (" ,\t") and the repaired one the
    // production patch writes there (" \t"). \r and \n are not stock
    // delimiters; a Windows command line never contains them.
    const char* const kStockDelims = " ,\t";
    const char* const kRepairedDelims = " \t";

    // Native state ProcessCommandLine writes. Field names carry the addresses
    // so the model can be checked against the decompile.
    struct ParseState
    {
        // Set by the shellmap/largemap handlers.
        int shellmapMode = 0;        // DAT_009183D4: 1 = shellmap, 2 = largemap.
                                     // NOTE: a mode selector, never a dimension.
        uint32_t shellmapPacked = 0; // _DAT_009183C4: (height << 16) | width

        bool disableMods = false;    // DAT_00915568

        // Written by the positional (non-switch) branch. FUN_00617110 passes
        // mapName to FUN_0050F920 as the shellmap name, so an unintended
        // positional token corrupts the shellmap call itself, not just some
        // unrelated global.
        std::string mapName;         // DAT_00915540, 16 bytes
        std::string missionPath;     // DAT_00945708
        int runState = 0;            // DAT_008E706C via FUN_00434170 (SetRunning)
        bool missionRequested = false; // DAT_0091556C

        std::vector<std::string> positionalTokens;
    };

    int Width(const ParseState& s) { return static_cast<int>(s.shellmapPacked & 0xFFFFu); }
    int Height(const ParseState& s) { return static_cast<int>((s.shellmapPacked >> 16) & 0xFFFFu); }

    // FUN_007D5120 with a caller-supplied delimiter set.
    ParseState SimulateParse(const std::string& lpCmdLine, const char* delims)
    {
        ParseState state;
        if (lpCmdLine.empty()) return state;

        std::vector<char> buf(lpCmdLine.begin(), lpCmdLine.end());
        buf.push_back('\0');

        char* token = strtok(buf.data(), delims);
        while (token != nullptr)
        {
            if (token[0] == '/' || token[0] == '-' || token[0] == '+')
            {
                const char* opt = token + 1;
                if (strncasecmp(opt, "shellmap", 8) == 0)
                {
                    // 0x007D55EA: width and height are seeded with 108 and 89
                    // before the sscanf, so a failed conversion leaves those.
                    int w = 108;
                    int h = 89;
                    const int res = sscanf(opt + 8, ":%d,%d", &w, &h);
                    if (res == 1)
                    {
                        h = w; // 0x007D5620-ish: the square fallback
                    }
                    state.shellmapMode = 1;
                    state.shellmapPacked = (static_cast<uint32_t>(h) << 16) | static_cast<uint32_t>(w);
                }
                else if (strncasecmp(opt, "largemap", 8) == 0)
                {
                    int val = 8;
                    sscanf(opt + 8, ":%d", &val);
                    state.shellmapMode = 2;
                    state.shellmapPacked = static_cast<uint32_t>(val);
                }
                else if (strcasecmp(opt, "disablemods") == 0)
                {
                    state.disableMods = true;
                }
                // Unrecognised switches fall through silently, as in stock.
            }
            else
            {
                // The positional branch at FUN_007D5120 line 468.
                state.missionPath = token;
                state.mapName = std::string(token).substr(0, 15);
                state.runState = 5;
                state.missionRequested = true;
                state.positionalTokens.push_back(token);
            }
            token = strtok(nullptr, delims);
        }
        return state;
    }

    bool HasPositional(const ParseState& s, const char* value)
    {
        return std::find(s.positionalTokens.begin(), s.positionalTokens.end(), value) !=
               s.positionalTokens.end();
    }
}

// ---------------------------------------------------------------------------
// The defect

void TestStockParserDefect()
{
    const ParseState stock = SimulateParse("-shellmap:216,178 -disablemods", kStockDelims);

    ExpectTrue(stock.shellmapMode == 1, "stock: shellmap recognised (mode 1)");
    ExpectTrue(Width(stock) == 216, "stock: width parses as 216");
    ExpectTrue(Height(stock) == 216, "stock DEFECT: height truncated to 216, not 178");
    ExpectTrue(stock.disableMods, "stock: later switches still parse");

    std::cout << "[PASS] TestStockParserDefect (-shellmap:216,178 -> W=" << Width(stock)
              << " H=" << Height(stock) << ")" << std::endl;
}

// The finding that rules out a post-parser repair of the dimension globals
// alone: the orphaned "178" is not merely stranded, it is consumed by the
// positional branch and overwrites the buffer the shellmap consumer reads as
// the map name.
void TestStockOrphanTokenCollateral()
{
    const ParseState stock = SimulateParse("-shellmap:216,178", kStockDelims);

    ExpectTrue(HasPositional(stock, "178"), "stock DEFECT: '178' orphaned into the positional branch");
    ExpectTrue(stock.mapName == "178", "stock DEFECT: orphan overwrites DAT_00915540 (shellmap map name)");
    ExpectTrue(stock.missionPath == "178", "stock DEFECT: orphan overwrites DAT_00945708 (mission path)");
    ExpectTrue(stock.runState == 5, "stock DEFECT: orphan calls SetRunning(5)");
    ExpectTrue(stock.missionRequested, "stock DEFECT: orphan sets DAT_0091556C");

    std::cout << "[PASS] TestStockOrphanTokenCollateral (orphan corrupts map name, mission path, run state)"
              << std::endl;
}

// ---------------------------------------------------------------------------
// The fix

void TestRepairedDelimitersFixShellmap()
{
    const ParseState fixed = SimulateParse("-shellmap:216,178 -disablemods", kRepairedDelims);

    ExpectTrue(fixed.shellmapMode == 1, "repaired: mode stays 1 (mode is not a dimension)");
    ExpectTrue(Width(fixed) == 216, "repaired: width 216");
    ExpectTrue(Height(fixed) == 178, "repaired: height 178");
    ExpectTrue(fixed.shellmapPacked == 0x00B200D8u, "repaired: packed value 0x00B200D8");
    ExpectTrue(fixed.disableMods, "repaired: later switches unaffected");

    // No split means no orphan means no collateral.
    ExpectTrue(fixed.positionalTokens.empty(), "repaired: no orphan token produced");
    ExpectTrue(fixed.mapName.empty(), "repaired: map name left as the caller initialised it");
    ExpectTrue(fixed.missionPath.empty(), "repaired: mission path untouched");
    ExpectTrue(fixed.runState == 0, "repaired: run state untouched");
    ExpectTrue(!fixed.missionRequested, "repaired: DAT_0091556C untouched");

    std::cout << "[PASS] TestRepairedDelimitersFixShellmap (216x178, packed 0x"
              << std::hex << fixed.shellmapPacked << std::dec << ", no collateral)" << std::endl;
}

// The stock square-fallback and largemap paths must keep behaving identically
// once the delimiter changes, because neither of them involves a comma.
void TestRepairedPreservesSingleValueOptions()
{
    {
        const ParseState s = SimulateParse("-shellmap:216", kRepairedDelims);
        ExpectTrue(Width(s) == 216 && Height(s) == 216, "repaired: -shellmap:216 keeps the square fallback");
    }
    {
        const ParseState stock = SimulateParse("-largemap:16 -disablemods", kStockDelims);
        const ParseState fixed = SimulateParse("-largemap:16 -disablemods", kRepairedDelims);
        ExpectTrue(fixed.shellmapMode == 2 && fixed.shellmapPacked == 16u, "repaired: -largemap:16 parses");
        ExpectTrue(stock.shellmapMode == fixed.shellmapMode &&
                   stock.shellmapPacked == fixed.shellmapPacked &&
                   stock.disableMods == fixed.disableMods,
                   "repaired: single-value options byte-for-byte identical to stock");
    }
    {
        const ParseState stock = SimulateParse("-disablemods -nointro /win +multi", kStockDelims);
        const ParseState fixed = SimulateParse("-disablemods -nointro /win +multi", kRepairedDelims);
        ExpectTrue(stock.disableMods && fixed.disableMods, "repaired: -disablemods still parses");
        ExpectTrue(stock.positionalTokens == fixed.positionalTokens,
                   "repaired: space-separated switch lists tokenise identically");
    }

    std::cout << "[PASS] TestRepairedPreservesSingleValueOptions" << std::endl;
}

// A genuine mission argument must still reach the positional branch, and must
// not be displaced by the shellmap value now that the value stays attached.
void TestRepairedPreservesPositionalArgument()
{
    const ParseState fixed = SimulateParse("-shellmap:216,178 fun.bzn", kRepairedDelims);

    ExpectTrue(Width(fixed) == 216 && Height(fixed) == 178, "repaired: dimensions still correct");
    ExpectTrue(fixed.positionalTokens.size() == 1, "repaired: exactly one positional token");
    ExpectTrue(fixed.mapName == "fun.bzn", "repaired: the real positional token wins");
    ExpectTrue(fixed.missionRequested, "repaired: mission request still raised");

    // Ordering must not matter.
    const ParseState reordered = SimulateParse("fun.bzn -shellmap:216,178", kRepairedDelims);
    ExpectTrue(Width(reordered) == 216 && Height(reordered) == 178 && reordered.mapName == "fun.bzn",
               "repaired: option order does not change the result");

    std::cout << "[PASS] TestRepairedPreservesPositionalArgument" << std::endl;
}

// ---------------------------------------------------------------------------
// Malformed input
//
// Every case here is stock sscanf semantics reached through the repaired
// delimiters. The fix adds no value-level tolerance of its own: nothing is
// "helpfully" rewritten, and a conversion that fails leaves the handler's own
// seeded defaults (108 x 89) exactly as stock would.

void TestMalformedShellmapValues()
{
    struct Case
    {
        const char* cmdline;
        int width;
        int height;
        const char* why;
    };

    const Case cases[] = {
        { "-shellmap:216,178",     216, 178, "both values convert" },
        { "-shellmap:1920,1080",  1920,1080, "large pair converts" },
        { "-shellmap:216,216",     216, 216, "explicit square pair" },
        { "-shellmap:216",         216, 216, "one value -> square fallback" },
        { "-shellmap:216,",        216, 216, "trailing comma -> square fallback" },
        { "-shellmap:216,abc",     216, 216, "bad height -> square fallback" },
        { "-shellmap:abc,178",     108,  89, "bad width -> handler defaults" },
        { "-shellmap:,178",        108,  89, "missing width -> handler defaults" },
        { "-shellmap",             108,  89, "no value at all -> handler defaults" },
        { "-shellmap:216,178,999", 216, 178, "extra component ignored by :%d,%d" },
    };

    for (const Case& c : cases)
    {
        const ParseState s = SimulateParse(c.cmdline, kRepairedDelims);
        ExpectTrue(s.shellmapMode == 1, c.why);
        if (Width(s) != c.width || Height(s) != c.height)
        {
            std::cerr << "FAIL: " << c.cmdline << " -> " << Width(s) << "x" << Height(s)
                      << ", expected " << c.width << "x" << c.height << " (" << c.why << ")" << std::endl;
            ++g_failures;
        }
        // No malformed value may leak into the positional branch.
        ExpectTrue(s.positionalTokens.empty(), "malformed shellmap value produces no positional token");
    }

    std::cout << "[PASS] TestMalformedShellmapValues (" << (sizeof(cases) / sizeof(cases[0]))
              << " cases)" << std::endl;
}

// ---------------------------------------------------------------------------
// Non-regression for surrounding arguments

void TestSurroundingArgumentsUnaffected()
{
    {
        const ParseState s = SimulateParse("-disablemods -shellmap:216,178 -nointro", kRepairedDelims);
        ExpectTrue(Width(s) == 216 && Height(s) == 178, "repaired: value survives between switches");
        ExpectTrue(s.disableMods, "repaired: preceding switch parses");
        ExpectTrue(s.positionalTokens.empty(), "repaired: no positional fallout between switches");
    }
    {
        // Tab is a stock delimiter and stays one.
        const ParseState s = SimulateParse("-disablemods\t-shellmap:216,178\t-nointro", kRepairedDelims);
        ExpectTrue(Width(s) == 216 && Height(s) == 178, "repaired: tab still separates arguments");
        ExpectTrue(s.disableMods, "repaired: tab-separated switch parses");
    }
    {
        // An unrelated comma-bearing argument is not rewritten; it simply stops
        // being split, which is the whole point.
        const ParseState s = SimulateParse("-someunknownopt:a,b -disablemods", kRepairedDelims);
        ExpectTrue(s.disableMods, "repaired: unknown comma-bearing option does not break the rest");
        ExpectTrue(s.positionalTokens.empty(), "repaired: unknown option's tail is not orphaned");
    }
    {
        // A path containing spaces is quoted by the shell but strtok has no
        // quote awareness, in stock or repaired. Documented, not claimed fixed.
        const ParseState stock = SimulateParse("\"my map.bzn\"", kStockDelims);
        const ParseState fixed = SimulateParse("\"my map.bzn\"", kRepairedDelims);
        ExpectTrue(stock.positionalTokens == fixed.positionalTokens,
                   "repaired: quoted-path handling is unchanged from stock (still split on space)");
    }

    std::cout << "[PASS] TestSurroundingArgumentsUnaffected" << std::endl;
}

// The one accepted behaviour change, asserted so it can never regress
// silently: a comma used where a space belongs no longer separates arguments.
// [Fixes] CliMultiParameterOptions = 0 restores the stock tokenising.
void TestAcceptedTradeOffCommaAsSeparator()
{
    const ParseState stock = SimulateParse("-disablemods,-shellmap:216", kStockDelims);
    const ParseState fixed = SimulateParse("-disablemods,-shellmap:216", kRepairedDelims);

    ExpectTrue(stock.disableMods && stock.shellmapMode == 1,
               "stock: comma separated two options");
    ExpectTrue(!fixed.disableMods && fixed.shellmapMode == 0,
               "repaired: comma no longer separates options (accepted trade-off)");
    ExpectTrue(fixed.positionalTokens.empty(),
               "repaired: the unmatched token is a switch, so it is not taken as a mission");

    std::cout << "[PASS] TestAcceptedTradeOffCommaAsSeparator (documented behaviour change)" << std::endl;
}

int main()
{
    std::cout << "Running CLI multi-parameter parser tests..." << std::endl;

    TestStockParserDefect();
    TestStockOrphanTokenCollateral();
    TestRepairedDelimitersFixShellmap();
    TestRepairedPreservesSingleValueOptions();
    TestRepairedPreservesPositionalArgument();
    TestMalformedShellmapValues();
    TestSurroundingArgumentsUnaffected();
    TestAcceptedTradeOffCommaAsSeparator();

    if (g_failures != 0)
    {
        std::cerr << g_failures << " check(s) failed." << std::endl;
        return 1;
    }

    std::cout << "All CLI multi-parameter parser tests passed." << std::endl;
    return 0;
}
