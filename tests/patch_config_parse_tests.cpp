// patch_config_parse_tests.cpp
// Pins the non-throwing readers the patcher uses for scripts/patches.json.
//
// WHY THIS EXISTS
// ===============
//
// patches.json is deployed by hand next to winmm.dll and is edited by hand
// during patch work. The patcher reads it on the patch thread, where a C++
// exception is std::terminate: the game used to die at launch, with no log
// line naming the entry, for a non-string address, a bad hex digit, an
// offset written as a string, or a key left out of one element. Some of
// those were not even exceptions -- nlohmann's const operator[] on a missing
// key dereferences end() in a release build.
//
// Two things are pinned here. First, that each malformed shape is reported
// (Malformed / false, with a message) instead of thrown, and that a valid
// shape still yields the value the old throwing code produced. Second, that
// the shipped scripts/patches.json passes every reader without a single
// complaint: the readers are stricter than std::stoul was (no trailing
// text, no negative offsets), and this is where a stricter rule would be
// caught before it silently dropped a real entry at runtime.

#include "patch_config_parse.h"
#include "resolve_table.h"

#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

using namespace BZROpenShim::PatchConfig;
using BZROpenShim::ParseIdaPatternText;
using nlohmann::json;

namespace
{
    int g_Failures = 0;

    void Check(bool condition, const char* what)
    {
        if (!condition)
        {
            std::fprintf(stderr, "FAIL: %s\n", what);
            ++g_Failures;
        }
    }

    void ExpectHex(const char* text, uint32_t expected)
    {
        uint32_t value = 0;
        const bool ok = ParseHexAddress32(text, value);
        if (!ok || value != expected)
        {
            std::fprintf(stderr, "FAIL: ParseHexAddress32(\"%s\") -> ok=%d value=0x%08X, expected 0x%08X\n",
                         text, ok ? 1 : 0, value, expected);
            ++g_Failures;
        }
    }

    void RejectHex(const char* text)
    {
        uint32_t value = 0;
        if (ParseHexAddress32(text, value))
        {
            std::fprintf(stderr, "FAIL: ParseHexAddress32(\"%s\") accepted as 0x%08X\n", text, value);
            ++g_Failures;
        }
    }

    void TestHexParser()
    {
        ExpectHex("0x00494D35", 0x00494D35);
        ExpectHex("494d35", 0x00494D35);
        ExpectHex("0X8EAAA8", 0x008EAAA8);
        ExpectHex("  0x10  ", 0x10);
        ExpectHex("0", 0);
        ExpectHex("0x0000000000000001", 1);   // leading zeros are not significant digits
        ExpectHex("0xFFFFFFFF", 0xFFFFFFFFu);
        RejectHex("");
        RejectHex("0x");
        RejectHex("   ");
        RejectHex("xyz");
        RejectHex("0x1G");
        RejectHex("0x100000000");             // 33 bits
        RejectHex("0x10 junk");               // std::stoul would have returned 0x10
        RejectHex("-1");
        RejectHex("12.5");
    }

    void TestStaticPointer()
    {
        const json root = json::parse(R"({
            "static_pointers": [
                { "name": "Good", "address": "0x008EAAA8" },
                { "name": "NotString", "address": 12 },
                { "name": "BadHex", "address": "0xZZ" },
                { "name": "NoAddress" },
                { "address": "0x1" },
                { "name": 7, "address": "0x2" },
                { "name": "Dup", "address": "0x10" },
                { "name": "Dup", "address": "0x20" }
            ]
        })");
        uint32_t value = 0;
        std::string error;

        Check(ReadStaticPointer(root, "Good", value, error) == LookupStatus::Found && value == 0x008EAAA8,
              "static_pointers: a valid entry is Found with its address");
        Check(ReadStaticPointer(root, "Missing", value, error) == LookupStatus::Absent,
              "static_pointers: an unknown name is Absent");
        Check(ReadStaticPointer(root, "NotString", value, error) == LookupStatus::Malformed && !error.empty(),
              "static_pointers: a numeric address is Malformed, not thrown");
        error.clear();
        Check(ReadStaticPointer(root, "BadHex", value, error) == LookupStatus::Malformed && error.find("0xZZ") != std::string::npos,
              "static_pointers: a bad hex string is Malformed and the message quotes it");
        Check(ReadStaticPointer(root, "NoAddress", value, error) == LookupStatus::Malformed,
              "static_pointers: an entry without an address is Malformed, not an out-of-bounds read");
        Check(ReadStaticPointer(root, "Dup", value, error) == LookupStatus::Found && value == 0x10,
              "static_pointers: the first entry of a duplicated name wins, as before");

        Check(ReadStaticPointer(json::parse("{}"), "Good", value, error) == LookupStatus::Absent,
              "static_pointers: no table at all is Absent");
        Check(ReadStaticPointer(json::parse("[1,2]"), "Good", value, error) == LookupStatus::Absent,
              "static_pointers: a non-object document is Absent");
        Check(ReadStaticPointer(json::parse(R"({"static_pointers":"x"})"), "Good", value, error) == LookupStatus::Malformed,
              "static_pointers: a non-array table is Malformed");
        Check(ReadStaticPointer(json::parse(R"({"static_pointers":[5, "s", null]})"), "Good", value, error) == LookupStatus::Absent,
              "static_pointers: non-object elements are skipped");
    }

    void TestFeatureBool()
    {
        const json root = json::parse(R"({
            "features": { "on": true, "off": false, "bad": "yes" },
            "top": true,
            "topbad": 1
        })");
        bool value = false;
        std::string error;
        Check(ReadFeatureBool(root, "on", value, error) == LookupStatus::Found && value,
              "features: a true flag is Found");
        Check(ReadFeatureBool(root, "off", value, error) == LookupStatus::Found && !value,
              "features: a false flag is Found");
        Check(ReadFeatureBool(root, "bad", value, error) == LookupStatus::Malformed,
              "features: a non-boolean flag is Malformed");
        Check(ReadFeatureBool(root, "top", value, error) == LookupStatus::Found && value,
              "features: a top-level boolean is the fallback lookup");
        Check(ReadFeatureBool(root, "topbad", value, error) == LookupStatus::Malformed,
              "features: a top-level non-boolean is Malformed");
        Check(ReadFeatureBool(root, "none", value, error) == LookupStatus::Absent,
              "features: an unknown flag is Absent");
        Check(ReadFeatureBool(json::parse(R"({"features": []})"), "on", value, error) == LookupStatus::Malformed,
              "features: a non-object features section is Malformed");
    }

    void TestSectionPattern()
    {
        std::string pattern;
        std::string error;
        Check(ReadSectionPattern(json::parse(R"({"audio_gas_pattern":{"pattern":"55 8B ?? EC"}})"),
                                 "audio_gas_pattern", pattern, error) == LookupStatus::Found && pattern == "55 8B ?? EC",
              "section pattern: a valid section is Found");
        Check(ReadSectionPattern(json::parse("{}"), "audio_gas_pattern", pattern, error) == LookupStatus::Absent,
              "section pattern: a missing section is Absent");
        Check(ReadSectionPattern(json::parse(R"({"audio_gas_pattern":"55 8B"})"), "audio_gas_pattern", pattern, error) == LookupStatus::Malformed,
              "section pattern: a non-object section is Malformed");
        Check(ReadSectionPattern(json::parse(R"({"audio_gas_pattern":{"pattern":5}})"), "audio_gas_pattern", pattern, error) == LookupStatus::Malformed,
              "section pattern: a numeric pattern is Malformed");
        Check(ReadSectionPattern(json::parse(R"({"audio_gas_pattern":{}})"), "audio_gas_pattern", pattern, error) == LookupStatus::Malformed,
              "section pattern: a section without a pattern is Malformed");
    }

    void TestScanEntry()
    {
        ScanEntry entry;
        std::string error;

        Check(ParseScanEntry(json::parse(R"({
                  "name": "Map Sorting", "pattern": "55 8B EC ?? ??", "offset": 3,
                  "expected_size": 5, "fallback": "0x007A3130", "require_unique": true })"), entry, error)
                  && entry.name == "Map Sorting" && entry.pattern == "55 8B EC ?? ??" && entry.offset == 3
                  && entry.expectedSize == 5 && entry.fallback == 0x007A3130 && entry.requireUnique,
              "patches entry: a full entry parses to the same fields the patcher used");

        Check(ParseScanEntry(json::parse(R"({ "name": "N", "pattern": "55", "offset": 0, "expected_size": 0, "fallback": "0x1" })"), entry, error)
                  && !entry.requireUnique,
              "patches entry: require_unique defaults to false when absent");

        const char* malformed[] = {
            R"({ "pattern": "55", "offset": 0, "expected_size": 0, "fallback": "0x1" })",                    // no name
            R"({ "name": "N", "offset": 0, "expected_size": 0, "fallback": "0x1" })",                        // no pattern
            R"({ "name": "N", "pattern": "55", "expected_size": 0, "fallback": "0x1" })",                    // no offset
            R"({ "name": "N", "pattern": "55", "offset": 0, "fallback": "0x1" })",                           // no expected_size
            R"({ "name": "N", "pattern": "55", "offset": 0, "expected_size": 0 })",                          // no fallback
            R"({ "name": "N", "pattern": "55", "offset": "3", "expected_size": 0, "fallback": "0x1" })",     // offset as string
            R"({ "name": "N", "pattern": "55", "offset": -1, "expected_size": 0, "fallback": "0x1" })",      // negative offset
            R"({ "name": "N", "pattern": "55", "offset": 2.5, "expected_size": 0, "fallback": "0x1" })",     // float offset
            R"({ "name": "N", "pattern": "55", "offset": 0, "expected_size": 4294967296, "fallback": "0x1" })", // 33-bit size
            R"({ "name": "N", "pattern": "55", "offset": 0, "expected_size": 0, "fallback": 4096 })",        // numeric fallback
            R"({ "name": "N", "pattern": "55", "offset": 0, "expected_size": 0, "fallback": "0xQ" })",       // bad hex
            R"({ "name": "N", "pattern": "55", "offset": 0, "expected_size": 0, "fallback": "0x1", "require_unique": "yes" })",
            R"({ "name": 5, "pattern": "55", "offset": 0, "expected_size": 0, "fallback": "0x1" })",         // numeric name
            R"("just a string")",
            R"(null)",
        };
        for (const char* text : malformed)
        {
            error.clear();
            if (ParseScanEntry(json::parse(text), entry, error) || error.empty())
            {
                std::fprintf(stderr, "FAIL: patches entry accepted or unexplained: %s\n", text);
                ++g_Failures;
            }
        }
    }

    void TestGlobalEntry()
    {
        GlobalEntry entry;
        std::string error;

        const json shared = json::parse(R"({ "name": "G", "expected_original": "55 8B", "fallback": "0x10" })");
        Check(ParseGlobalEntry(shared, false, entry, error) && entry.name == "G" && entry.fallback == 0x10 && entry.expectedOriginal == "55 8B",
              "globals entry: fallback alone serves GOG");
        Check(ParseGlobalEntry(shared, true, entry, error) && entry.fallback == 0x10,
              "globals entry: fallback alone serves Steam");

        const json split = json::parse(R"({ "name": "G", "expected_original": "55", "fallback_gog": "0x20", "fallback_steam": "0x30" })");
        Check(ParseGlobalEntry(split, false, entry, error) && entry.fallback == 0x20,
              "globals entry: GOG picks fallback_gog");
        Check(ParseGlobalEntry(split, true, entry, error) && entry.fallback == 0x30,
              "globals entry: Steam picks fallback_steam");

        const json steamOnly = json::parse(R"({ "name": "G", "expected_original": "55", "fallback_steam": "0x30", "fallback": "0x40" })");
        Check(ParseGlobalEntry(steamOnly, false, entry, error) && entry.fallback == 0x40,
              "globals entry: GOG with no fallback_gog takes the shared fallback");
        Check(ParseGlobalEntry(steamOnly, true, entry, error) && entry.fallback == 0x30,
              "globals entry: Steam prefers fallback_steam over the shared fallback");

        const json zeroSpecific = json::parse(R"({ "name": "G", "expected_original": "55", "fallback_gog": "0x0", "fallback": "0x40" })");
        Check(ParseGlobalEntry(zeroSpecific, false, entry, error) && entry.fallback == 0x40,
              "globals entry: a zero distribution address still falls through to the shared one, as before");

        const json noAddress = json::parse(R"({ "name": "G", "expected_original": "55" })");
        Check(ParseGlobalEntry(noAddress, false, entry, error) && entry.fallback == 0,
              "globals entry: no address at all is a valid entry at 0 (unverified), as before");

        const char* malformed[] = {
            R"({ "expected_original": "55", "fallback": "0x10" })",                       // no name
            R"({ "name": "G", "fallback": "0x10" })",                                     // no expected_original
            R"({ "name": "G", "expected_original": 55, "fallback": "0x10" })",            // numeric guard
            R"({ "name": "G", "expected_original": "55", "fallback": "0xZZ" })",          // bad shared hex
            R"({ "name": "G", "expected_original": "55", "fallback_gog": "nope", "fallback": "0x10" })", // bad specific hex
            R"({ "name": "G", "expected_original": "55", "fallback": 16 })",              // numeric fallback
            R"([])",
        };
        for (const char* text : malformed)
        {
            error.clear();
            if (ParseGlobalEntry(json::parse(text), false, entry, error) || error.empty())
            {
                std::fprintf(stderr, "FAIL: globals entry accepted or unexplained: %s\n", text);
                ++g_Failures;
            }
        }
    }

    void TestHelpers()
    {
        const json root = json::parse(R"({ "patches": [ { "name": "A" }, { "x": 1 }, 3 ], "globals": {}, "n": 1 })");
        Check(ArraySection(root, "patches") != nullptr && ArraySection(root, "patches")->size() == 3,
              "ArraySection: returns the array");
        Check(ArraySection(root, "globals") == nullptr, "ArraySection: a non-array value is nullptr");
        Check(ArraySection(root, "missing") == nullptr, "ArraySection: a missing key is nullptr");
        Check(ArraySection(json::parse("[]"), "patches") == nullptr, "ArraySection: a non-object root is nullptr");
        Check(EntryName((*ArraySection(root, "patches"))[0]) == "A", "EntryName: reads the name");
        Check(EntryName((*ArraySection(root, "patches"))[1]).empty(), "EntryName: no name is empty");
        Check(EntryName((*ArraySection(root, "patches"))[2]).empty(), "EntryName: a non-object is empty");
    }

    // ---- VerifyFallbackSite ---------------------------------------------

    // A fake 32-bit image: `bytes` live at `base`, anything outside is
    // unreadable, the way ReadProcessMemory fails on an unmapped page. The
    // last request is recorded so a test can pin where the reader looked.
    struct FakeImage
    {
        uint32_t base = 0;
        std::vector<uint8_t> bytes;
        mutable uint32_t lastAddress = 0;
        mutable size_t lastLength = 0;

        MemoryReader Reader() const
        {
            return [this](uint32_t address, size_t length, std::vector<uint8_t>& out) {
                lastAddress = address;
                lastLength = length;
                if (address < base) return false;
                const size_t start = static_cast<size_t>(address - base);
                if (start > bytes.size() || length > bytes.size() - start) return false;
                out.assign(bytes.begin() + static_cast<std::ptrdiff_t>(start),
                           bytes.begin() + static_cast<std::ptrdiff_t>(start + length));
                return true;
            };
        }
    };

    // Concrete bytes that satisfy `pattern`: literals as written, each
    // wildcard a distinctive non-zero byte (0xA0 + index), so a guard that
    // demanded 0x00 for a wildcard would be caught.
    std::vector<uint8_t> Instantiate(const std::vector<uint16_t>& pattern)
    {
        std::vector<uint8_t> out;
        for (size_t j = 0; j < pattern.size(); ++j)
            out.push_back(pattern[j] < 0x100 ? static_cast<uint8_t>(pattern[j]) : static_cast<uint8_t>(0xA0 + j));
        return out;
    }

    void TestFallbackSite()
    {
        // The shipped "HoverCraft Engine Flame Emit Hook 1/2" entry: offset 17
        // lands on the rel32 operand of the E8, four wildcards. The old code
        // guarded the fallback with pattern bytes 0..3 (0F 11 04 24), which
        // the operand can never equal.
        const auto hover1 = ParseIdaPatternText(
            "0F 11 04 24 8D 85 ?? ?? ?? ?? 50 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 3D ?? ?? ?? ?? 00 0F 84");
        Check(hover1.size() == 30, "fallback: hover1 pattern parses to 30 bytes");
        FakeImage image;
        image.base = 0x004EAD67;
        image.bytes = Instantiate(hover1);
        const uint32_t fallback = image.base + 17;   // 0x004EAD78, as shipped

        std::vector<uint8_t> guard;
        std::string error;
        Check(VerifyFallbackSite(hover1, fallback, 17, 4, image.Reader(), guard, error),
              "fallback: hover1 is accepted when its pattern is present at fallback - offset");
        Check(image.lastAddress == image.base && image.lastLength == 30,
              "fallback: hover1 reads the whole pattern starting at fallback - offset");
        Check(guard == std::vector<uint8_t>{ 0xB1, 0xB2, 0xB3, 0xB4 },
              "fallback: hover1 guard is the observed operand, not 0F 11 04 24 and not 00 00 00 00");

        // "2/2": offset 13, wildcards at pattern index 2-3, so the old guard
        // was 8D 95 00 00. The guard must be the four bytes at offset 13.
        const auto hover2 = ParseIdaPatternText(
            "8D 95 ?? ?? ?? ?? 52 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? E9 ?? ?? ?? ?? 83 BD ?? ?? ?? ?? 00 0F 8E");
        FakeImage image2;
        image2.base = 0x004EAFD2;
        image2.bytes = Instantiate(hover2);
        guard.clear();
        Check(VerifyFallbackSite(hover2, image2.base + 13, 13, 4, image2.Reader(), guard, error),
              "fallback: hover2 is accepted");
        Check(guard == std::vector<uint8_t>{ 0xAD, 0xAE, 0xAF, 0xB0 },
              "fallback: hover2 guard is the observed operand, not 8D 95 00 00");

        // A wildcard position may hold anything, including zero; a zero that
        // was observed is guarded as zero.
        FakeImage wild = image;
        wild.bytes[6] = 0x00;
        wild.bytes[17] = 0x00;
        guard.clear();
        Check(VerifyFallbackSite(hover1, fallback, 17, 4, wild.Reader(), guard, error),
              "fallback: wildcard bytes are not compared");
        Check(guard.size() == 4 && guard[0] == 0x00 && guard[1] == 0xB2,
              "fallback: an observed zero operand byte is guarded as observed");

        // One literal byte off: the site is not the one the entry describes.
        FakeImage wrong = image;
        wrong.bytes[0] = 0x0E;
        guard.clear();
        error.clear();
        Check(!VerifyFallbackSite(hover1, fallback, 17, 4, wrong.Reader(), guard, error),
              "fallback: a literal mismatch is refused");
        Check(error.find("pattern byte 0 is 0F but 0x004EAD67 holds 0E") != std::string::npos,
              "fallback: the refusal names the byte, its address and what was found");
        Check(guard.empty(), "fallback: a refused site leaves no guard");
        FakeImage wrongTail = image;
        wrongTail.bytes[29] = 0x85;
        Check(!VerifyFallbackSite(hover1, fallback, 17, 4, wrongTail.Reader(), guard, error) &&
                  error.find("pattern byte 29") != std::string::npos,
              "fallback: a literal past the guard window is still compared");

        // Unreadable memory, and a pattern that runs into unmapped memory.
        FakeImage unmapped;
        unmapped.base = 0x00400000;
        error.clear();
        Check(!VerifyFallbackSite(hover1, fallback, 17, 4, unmapped.Reader(), guard, error) &&
                  error.find("30 byte(s) at 0x004EAD67 could not be read") != std::string::npos,
              "fallback: an unreadable site is refused");
        FakeImage truncated = image;
        truncated.bytes.resize(20);
        Check(!VerifyFallbackSite(hover1, fallback, 17, 4, truncated.Reader(), guard, error) &&
                  error.find("could not be read") != std::string::npos,
              "fallback: a pattern that runs into unmapped memory is refused");

        // The bookkeeping refusals.
        Check(!VerifyFallbackSite(hover1, 0, 17, 4, image.Reader(), guard, error) &&
                  error.find("no fallback") != std::string::npos,
              "fallback: address 0 is refused");
        Check(!VerifyFallbackSite({}, fallback, 17, 4, image.Reader(), guard, error) &&
                  error.find("pattern is empty") != std::string::npos,
              "fallback: an empty pattern is refused");
        Check(!VerifyFallbackSite(hover1, fallback, 17, 0, image.Reader(), guard, error) &&
                  error.find("expected_size is 0") != std::string::npos,
              "fallback: expected_size 0 is refused rather than written unguarded");
        Check(!VerifyFallbackSite(hover1, 0x00000010, 17, 4, image.Reader(), guard, error) &&
                  error.find("below address 0") != std::string::npos,
              "fallback: an offset larger than the fallback is refused");
        Check(!VerifyFallbackSite(hover1, 0xFFFFFFF0, 0, 4, image.Reader(), guard, error) &&
                  error.find("address space") != std::string::npos,
              "fallback: a window past the end of the address space is refused");

        // A guard window that reaches past the pattern is read from memory
        // too, as the scan path reads it from its region buffer.
        const auto prologue = ParseIdaPatternText("55 8B EC");
        FakeImage tail;
        tail.base = 0x00500000;
        tail.bytes = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x10, 0x53, 0x56 };
        guard.clear();
        Check(VerifyFallbackSite(prologue, tail.base + 2, 2, 5, tail.Reader(), guard, error),
              "fallback: a window past the pattern is accepted when readable");
        Check(tail.lastLength == 7 && guard == std::vector<uint8_t>{ 0xEC, 0x83, 0xEC, 0x10, 0x53 },
              "fallback: a window past the pattern is read from the site");
        tail.bytes.resize(6);
        Check(!VerifyFallbackSite(prologue, tail.base + 2, 2, 5, tail.Reader(), guard, error),
              "fallback: a window past the pattern that is unreadable is refused");
    }

    // The shipped file must pass every reader without a complaint; a stricter
    // reader than the old std::stoul path would otherwise drop a real entry.
    void TestShippedPatchesJson()
    {
#ifdef BZR_PATCHES_JSON
        std::ifstream f(BZR_PATCHES_JSON, std::ios::binary);
        if (!f.is_open())
        {
            std::fprintf(stderr, "FAIL: cannot open %s\n", BZR_PATCHES_JSON);
            ++g_Failures;
            return;
        }
        json root;
        try { root = json::parse(f); }
        catch (const std::exception& e)
        {
            std::fprintf(stderr, "FAIL: %s does not parse: %s\n", BZR_PATCHES_JSON, e.what());
            ++g_Failures;
            return;
        }

        std::string error;
        const json* patches = ArraySection(root, "patches");
        Check(patches != nullptr, "shipped: patches is an array");
        if (patches)
        {
            for (const auto& node : *patches)
            {
                ScanEntry entry;
                error.clear();
                if (!ParseScanEntry(node, entry, error))
                {
                    std::fprintf(stderr, "FAIL: shipped patches entry '%s': %s\n", EntryName(node).c_str(), error.c_str());
                    ++g_Failures;
                    continue;
                }
                if (entry.requireUnique) continue;
                // Every entry that can take the fallback must be able to:
                // with its pattern present at fallback - offset, the site
                // verifies and the guard covers expected_size bytes. The two
                // HoverCraft entries, whose window is a rel32 operand, are why
                // the guard comes from the observed bytes and not the pattern.
                const auto pattern = ParseIdaPatternText(entry.pattern);
                FakeImage image;
                image.base = entry.fallback - entry.offset;
                image.bytes = Instantiate(pattern);
                while (image.bytes.size() < static_cast<size_t>(entry.offset) + entry.expectedSize)
                    image.bytes.push_back(0xCC);
                std::vector<uint8_t> guard;
                error.clear();
                if (!VerifyFallbackSite(pattern, entry.fallback, entry.offset, entry.expectedSize, image.Reader(), guard, error) ||
                    guard.size() != entry.expectedSize)
                {
                    std::fprintf(stderr, "FAIL: shipped patches entry '%s' cannot take its fallback: %s\n",
                                 entry.name.c_str(), error.c_str());
                    ++g_Failures;
                }
            }
        }
        const json* globals = ArraySection(root, "globals");
        Check(globals != nullptr, "shipped: globals is an array");
        if (globals)
        {
            for (const auto& node : *globals)
            {
                for (bool steam : { false, true })
                {
                    GlobalEntry entry;
                    error.clear();
                    if (!ParseGlobalEntry(node, steam, entry, error))
                    {
                        std::fprintf(stderr, "FAIL: shipped globals entry '%s' (%s): %s\n",
                                     EntryName(node).c_str(), steam ? "steam" : "gog", error.c_str());
                        ++g_Failures;
                    }
                }
            }
        }
        const json* pointers = ArraySection(root, "static_pointers");
        Check(pointers != nullptr, "shipped: static_pointers is an array");
        if (pointers)
        {
            for (const auto& node : *pointers)
            {
                uint32_t value = 0;
                error.clear();
                if (ReadStaticPointer(root, EntryName(node), value, error) != LookupStatus::Found)
                {
                    std::fprintf(stderr, "FAIL: shipped static pointer '%s': %s\n", EntryName(node).c_str(), error.c_str());
                    ++g_Failures;
                }
            }
        }
        std::string pattern;
        Check(ReadSectionPattern(root, "audio_gas_pattern", pattern, error) == LookupStatus::Found && !pattern.empty(),
              "shipped: audio_gas_pattern.pattern reads");
        bool guard = false;
        Check(ReadFeatureBool(root, "ogre_material_collision_guard", guard, error) == LookupStatus::Found,
              "shipped: features.ogre_material_collision_guard reads");
#endif
    }
}

int main()
{
    TestHexParser();
    TestStaticPointer();
    TestFeatureBool();
    TestSectionPattern();
    TestScanEntry();
    TestGlobalEntry();
    TestHelpers();
    TestFallbackSite();
    TestShippedPatchesJson();

    if (g_Failures != 0)
    {
        std::fprintf(stderr, "%d failure(s)\n", g_Failures);
        return 1;
    }
    std::printf("patch_config_parse_tests: all checks passed\n");
    return 0;
}
