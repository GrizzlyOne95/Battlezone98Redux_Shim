// resolve_table_tests.cpp
// Host-side checks for the "resolves" array in scripts/patches.json.
//
// The point of the first test is the migration itself: the five signatures
// that used to live in bzr_hooks.cpp as uint8_t pattern/mask array pairs are
// reproduced here byte for byte, exactly as they were written in the two
// different mask conventions that file used (0xFF/0x00 for the engine flame
// group, 1/0 for the unit VO group). If the JSON text and these arrays ever
// disagree, the move dropped or mistyped a byte.
#include "resolve_table.h"

#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

using namespace BZROpenShim;

namespace
{
    int g_Failures = 0;

    void Check(bool condition, const char* what)
    {
        if (condition) return;
        std::fprintf(stderr, "FAIL: %s\n", what);
        ++g_Failures;
    }

    // Renders a pattern/mask array pair the way the old FindPatternInMainText
    // read it: any non-zero mask byte means "this byte is concrete".
    std::string ToIdaText(const uint8_t* pattern, const uint8_t* mask, size_t size)
    {
        std::string text;
        char buf[4] = {};
        for (size_t i = 0; i < size; ++i)
        {
            if (i) text.push_back(' ');
            if (mask[i] == 0)
            {
                text += "??";
                continue;
            }
            std::snprintf(buf, sizeof(buf), "%02X", pattern[i]);
            text += buf;
        }
        return text;
    }

    // --- verbatim copies of the pre-migration arrays -----------------------

    const uint8_t kEmit1Pattern[] = {
        0x0F, 0x11, 0x04, 0x24, 0x8D, 0x85, 0x00, 0x00, 0x00, 0x00,
        0x50, 0xB9, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00,
        0x00, 0x83, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x84,
    };
    const uint8_t kEmit1Mask[] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
        0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
        0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
    };

    const uint8_t kGetTeamNumPattern[] = {
        0x8B, 0x45, 0x08, 0x50, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x83,
        0xC4, 0x04, 0x89, 0x45, 0xFC, 0x83, 0x7D, 0xFC, 0x00, 0x75,
        0x04, 0x33, 0xC0, 0xEB, 0x11, 0x8B, 0x4D, 0xFC, 0x83, 0xC1,
        0x18, 0x8B, 0x55, 0xFC, 0x8B, 0x42, 0x18, 0x8B, 0x50, 0x04,
        0xFF, 0xD2,
    };
    const uint8_t kGetTeamNumMask[] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF,
    };

    const uint8_t kResolveTexturePattern[] = {
        0x55, 0x8B, 0xEC, 0x51, 0x83, 0x7D, 0x08, 0x00, 0x75, 0x04,
        0x33, 0xC0, 0xEB, 0x44, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x83,
        0xE8, 0x01, 0x89, 0x45, 0xFC, 0xEB, 0x09, 0x8B, 0x4D, 0xFC,
        0x83, 0xE9, 0x01, 0x89, 0x4D, 0xFC, 0x83, 0x7D, 0xFC, 0x00,
        0x7E, 0x26, 0x6A, 0x20, 0x8B, 0x55, 0x08, 0x52, 0x8B, 0x45,
        0xFC, 0xC1, 0xE0, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x50,
        0xFF, 0x15, 0x00, 0x00, 0x00, 0x00, 0x83, 0xC4, 0x0C, 0x85,
        0xC0, 0x75, 0x05,
    };
    const uint8_t kResolveTextureMask[] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
        0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF,
    };

    const uint8_t kUnitVoSayQueuePattern[] = {
        0x6A, 0x00, 0x8B, 0x4D, 0xFC, 0x83, 0xC1, 0x18, 0x8B, 0x55,
        0xFC, 0x8B, 0x42, 0x18, 0x8B, 0x50, 0x30, 0xFF, 0xD2, 0x50,
        0x8B, 0x45, 0xF8, 0x50, 0xE8, 0, 0, 0, 0, 0x83, 0xC4, 0x0C,
        0x8B, 0x4D, 0x0C, 0x89, 0x0D, 0, 0, 0, 0, 0xE8, 0, 0, 0, 0,
        0xD9, 0x1D, 0, 0, 0, 0
    };
    const uint8_t kUnitVoSayQueueMask[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
        1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0
    };

    const uint8_t kUnitVoRecycleQueuePattern[] = {
        0x6A, 0x03, 0x8B, 0x4D, 0xFC, 0x83, 0xC1, 0x18, 0x8B, 0x45,
        0xFC, 0x8B, 0x50, 0x18, 0x8B, 0x42, 0x30, 0xFF, 0xD0, 0x50,
        0x8B, 0x4D, 0x08, 0x51, 0xE8, 0, 0, 0, 0, 0x83, 0xC4, 0x0C,
        0x5E, 0x8B, 0xE5
    };
    const uint8_t kUnitVoRecycleQueueMask[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
        1, 1, 1
    };

    // The five entries as they now appear in scripts/patches.json, held here
    // so the parsing tests are self-contained. The shipped file itself is
    // checked separately by TestShippedTableMatchesTheOriginalArrays.
    const char* const kJson = R"JSON({
      "resolves": [
        {
          "name": "EngineFlame::AddFlame",
          "pattern": "0F 11 04 24 8D 85 ?? ?? ?? ?? 50 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 3D ?? ?? ?? ?? 00 0F 84",
          "offset": 16,
          "mode": "rel32_target",
          "prefer": "fallback",
          "fallback": "0x004C8800",
          "identity": "callsite 0x004EAD77 in HoverCraft::Simulate"
        },
        {
          "name": "GetTeamNum",
          "pattern": "8B 45 08 50 E8 ?? ?? ?? ?? 83 C4 04 89 45 FC 83 7D FC 00 75 04 33 C0 EB 11 8B 4D FC 83 C1 18 8B 55 FC 8B 42 18 8B 50 04 FF D2",
          "offset": -4,
          "mode": "address",
          "prefer": "fallback",
          "fallback": "0x005C8800",
          "identity": "live GetTeamNum helper 0x005C8800"
        },
        {
          "name": "EngineFlame::ResolveTexture",
          "pattern": "55 8B EC 51 83 7D 08 00 75 04 33 C0 EB 44 A1 ?? ?? ?? ?? 83 E8 01 89 45 FC EB 09 8B 4D FC 83 E9 01 89 4D FC 83 7D FC 00 7E 26 6A 20 8B 55 08 52 8B 45 FC C1 E0 05 05 ?? ?? ?? ?? 50 FF 15 ?? ?? ?? ?? 83 C4 0C 85 C0 75 05",
          "offset": 0,
          "mode": "address",
          "prefer": "fallback",
          "fallback": "0x0068BED0",
          "identity": "shared sprite/texture lookup 0x0068BED0"
        },
        {
          "name": "UnitVo::SayQueueCallSite",
          "pattern": "6A 00 8B 4D FC 83 C1 18 8B 55 FC 8B 42 18 8B 50 30 FF D2 50 8B 45 F8 50 E8 ?? ?? ?? ?? 83 C4 0C 8B 4D 0C 89 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? D9 1D ?? ?? ?? ??",
          "offset": 24,
          "mode": "address",
          "identity": "Say -> QueueCB call site, priority 6A 00"
        },
        {
          "name": "UnitVo::RecycleQueueCallSite",
          "pattern": "6A 03 8B 4D FC 83 C1 18 8B 45 FC 8B 50 18 8B 42 30 FF D0 50 8B 4D 08 51 E8 ?? ?? ?? ?? 83 C4 0C 5E 8B E5",
          "offset": 24,
          "mode": "address",
          "identity": "Recycle -> QueueCB call site, priority 6A 03"
        }
      ]
    })JSON";

    const ResolveTarget* Find(const std::vector<ResolveTarget>& targets, const char* name)
    {
        for (const auto& target : targets)
            if (target.name == name) return &target;
        return nullptr;
    }

    void TestMigratedPatternsAreByteIdentical()
    {
        std::string error;
        const auto targets = ParseResolveTable(kJson, &error);
        Check(error.empty(), "the resolve table must parse without rejected entries");
        Check(targets.size() == 5, "all five migrated entries must survive parsing");

        struct Case
        {
            const char* name;
            const uint8_t* pattern;
            const uint8_t* mask;
            size_t size;
        };
        const Case cases[] = {
            { "EngineFlame::AddFlame", kEmit1Pattern, kEmit1Mask, sizeof(kEmit1Pattern) },
            { "GetTeamNum", kGetTeamNumPattern, kGetTeamNumMask, sizeof(kGetTeamNumPattern) },
            { "EngineFlame::ResolveTexture", kResolveTexturePattern, kResolveTextureMask, sizeof(kResolveTexturePattern) },
            { "UnitVo::SayQueueCallSite", kUnitVoSayQueuePattern, kUnitVoSayQueueMask, sizeof(kUnitVoSayQueuePattern) },
            { "UnitVo::RecycleQueueCallSite", kUnitVoRecycleQueuePattern, kUnitVoRecycleQueueMask, sizeof(kUnitVoRecycleQueuePattern) },
        };

        for (const auto& c : cases)
        {
            const ResolveTarget* target = Find(targets, c.name);
            Check(target != nullptr, c.name);
            if (!target) continue;

            Check(target->ida_pattern == ToIdaText(c.pattern, c.mask, c.size),
                  "migrated pattern text must equal the original array pair");

            // Same again through the matcher's own parser, so a formatting
            // difference cannot hide a byte difference.
            const auto parsed = ParseIdaPatternText(target->ida_pattern);
            Check(parsed.size() == c.size, "migrated pattern must keep its length");
            if (parsed.size() != c.size) continue;
            for (size_t i = 0; i < c.size; ++i)
            {
                const bool wildcard = c.mask[i] == 0;
                const bool ok = wildcard ? (parsed[i] == 0x100)
                                         : (parsed[i] == c.pattern[i]);
                Check(ok, "each byte must keep its concrete/wildcard status");
                if (!ok) break;
            }
        }
    }

    void TestAnchorsAndSourcesSurvive()
    {
        const auto targets = ParseResolveTable(kJson, nullptr);

        const ResolveTarget* addFlame = Find(targets, "EngineFlame::AddFlame");
        Check(addFlame && addFlame->offset == 16, "AddFlame anchors on the E8 at +16");
        Check(addFlame && addFlame->mode == ResolveMode::Rel32Target,
              "AddFlame is reached through the call, not at the call");
        Check(addFlame && addFlame->fallback_addr == 0x004C8800u,
              "AddFlame keeps the constant the shim used before the migration");

        // The negative offset is the whole reason the resolver takes a signed
        // one: this function's prologue is too generic to sit in the pattern.
        const ResolveTarget* teamNum = Find(targets, "GetTeamNum");
        Check(teamNum && teamNum->offset == -4, "GetTeamNum anchors 4 bytes before the match");
        Check(teamNum && teamNum->mode == ResolveMode::Address, "GetTeamNum is the match itself");

        const ResolveTarget* say = Find(targets, "UnitVo::SayQueueCallSite");
        Check(say && say->offset == 24, "the Say call site is at +24");
        Check(say && say->fallback_addr == 0, "the unit VO sites have no constant to fall back to");
        Check(say && say->preference == ResolvePreference::Scan,
              "the unit VO sites were already scan-driven and must stay that way");

        // The three flame entries were dead code before the migration: the
        // shim seeded the constants and the scan then early-returned. They
        // stay fallback-preferred until a live log line shows agree=yes.
        for (const char* name : { "EngineFlame::AddFlame", "GetTeamNum", "EngineFlame::ResolveTexture" })
        {
            const ResolveTarget* target = Find(targets, name);
            Check(target && target->preference == ResolvePreference::Fallback, name);
        }
    }

    void TestBadEntriesAreRejectedIndividually()
    {
        // A malformed entry must not disarm the entries around it.
        const char* json = R"JSON({
          "resolves": [
            { "name": "good", "pattern": "8B 45 08", "identity": "a call site" },
            { "name": "no-identity", "pattern": "8B 45 08" },
            { "name": "bad-pattern", "pattern": "8B ZZ 08", "identity": "x" },
            { "name": "bad-mode", "pattern": "8B 45 08", "mode": "sideways", "identity": "x" },
            { "name": "prefers-missing-fallback", "pattern": "8B 45 08", "prefer": "fallback", "identity": "x" },
            { "name": "also-good", "pattern": "90 90", "identity": "a padding run" }
          ]
        })JSON";

        std::string error;
        const auto targets = ParseResolveTable(json, &error);
        Check(targets.size() == 2, "only the two well-formed entries survive");
        Check(Find(targets, "good") != nullptr, "a good entry before the bad ones survives");
        Check(Find(targets, "also-good") != nullptr, "a good entry after the bad ones survives");
        Check(!error.empty(), "rejections must be reported, not swallowed");

        // An entry with no identity note is refused on purpose: a signature
        // nobody can trace to independent evidence is the failure this table
        // exists to surface.
        Check(Find(targets, "no-identity") == nullptr, "an entry without an identity note is refused");
    }

    // Closes the loop on the artifact that actually ships: the entries the
    // game will read must carry the same bytes as the arrays they replaced.
    void TestShippedTableMatchesTheOriginalArrays()
    {
#ifndef BZR_PATCHES_JSON
        std::printf("resolve_table_tests: shipped patches.json path not configured; skipped\n");
#else
        std::ifstream file(BZR_PATCHES_JSON, std::ios::binary);
        Check(file.is_open(), "scripts/patches.json must be readable at " BZR_PATCHES_JSON);
        if (!file.is_open()) return;
        const std::string text((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());

        std::string error;
        const auto shipped = ParseResolveTable(text, &error);
        Check(error.empty(), "the shipped resolve table must have no rejected entries");
        Check(shipped.size() >= 5, "the shipped table must still carry the migrated entries");

        const auto reference = ParseResolveTable(kJson, nullptr);
        for (const auto& expected : reference)
        {
            const ResolveTarget* actual = Find(shipped, expected.name.c_str());
            Check(actual != nullptr, expected.name.c_str());
            if (!actual) continue;
            Check(actual->ida_pattern == expected.ida_pattern,
                  "shipped pattern must match the migrated one");
            Check(actual->offset == expected.offset, "shipped offset must match");
            Check(actual->mode == expected.mode, "shipped mode must match");
            Check(actual->preference == expected.preference, "shipped preference must match");
            Check(actual->fallback_addr == expected.fallback_addr, "shipped fallback must match");
            Check(!actual->identity.empty(), "every shipped entry must carry an identity note");
        }
#endif
    }

    void TestUnparseablePatternFailsWhole()
    {
        // Fail closed: a typo must not leave a shorter pattern that still
        // matches somewhere.
        Check(ParseIdaPatternText("8B 45 ZZ 08").empty(), "a bad token voids the pattern");
        Check(ParseIdaPatternText("").empty(), "an empty pattern stays empty");

        const auto parsed = ParseIdaPatternText("8B ?? 08 ?");
        Check(parsed.size() == 4, "both wildcard spellings are accepted");
        Check(parsed.size() == 4 && parsed[1] == 0x100 && parsed[3] == 0x100,
              "?? and ? both mark a wildcard");
    }
}

int main()
{
    TestMigratedPatternsAreByteIdentical();
    TestAnchorsAndSourcesSurvive();
    TestBadEntriesAreRejectedIndividually();
    TestUnparseablePatternFailsWhole();
    TestShippedTableMatchesTheOriginalArrays();

    if (g_Failures != 0)
    {
        std::fprintf(stderr, "resolve_table_tests: %d check(s) failed\n", g_Failures);
        return 1;
    }
    std::printf("resolve_table_tests: all checks passed\n");
    return 0;
}
