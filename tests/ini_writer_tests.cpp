// Unit tests for the lossless openshim.ini document-update logic
// (src/patches/openshim_ini.cpp). Build and run with scripts/run_ini_tests.ps1
// — no engine, no game install, no winmm.dll required.

#include "openshim_ini.h"

#include <cstdio>
#include <string>
#include <vector>

using BZROpenShim::IniLineIsSectionHeader;
using BZROpenShim::IniLineMatchesKey;
using BZROpenShim::UpdateIniDocumentValueLossless;

namespace
{
    int g_Failures = 0;
    int g_Checks = 0;

    void CheckEq(const std::vector<std::string>& actual,
                 const std::vector<std::string>& expected,
                 const char* name)
    {
        ++g_Checks;
        if (actual == expected)
            return;
        ++g_Failures;
        std::printf("FAIL %s\n  expected (%zu lines):\n", name, expected.size());
        for (const auto& l : expected) std::printf("    |%s|\n", l.c_str());
        std::printf("  actual (%zu lines):\n", actual.size());
        for (const auto& l : actual) std::printf("    |%s|\n", l.c_str());
    }

    void CheckTrue(bool condition, const char* name)
    {
        ++g_Checks;
        if (condition)
            return;
        ++g_Failures;
        std::printf("FAIL %s\n", name);
    }

    void Update(std::vector<std::string>& lines,
                const char* section, const char* key, const char* value,
                const char* const* altKeys = nullptr, size_t altKeyCount = 0)
    {
        UpdateIniDocumentValueLossless(lines, section, key, altKeys, altKeyCount, value);
    }
}

int main()
{
    // --- line parsers ----------------------------------------------------
    {
        std::string name;
        CheckTrue(IniLineIsSectionHeader("[Display]", name) && name == "Display",
                  "section header parses");
        CheckTrue(IniLineIsSectionHeader("   [ Spaced ]  ; trailing", name) && name == " Spaced ",
                  "indented header parses verbatim inside brackets");
        CheckTrue(!IniLineIsSectionHeader("Display]", name), "missing open bracket rejected");
        CheckTrue(!IniLineIsSectionHeader("; [Display]", name), "commented header rejected");
        CheckTrue(!IniLineIsSectionHeader("[Display", name), "unterminated header rejected");

        CheckTrue(IniLineMatchesKey("JetFlames = 1", "JetFlames"), "simple key matches");
        CheckTrue(IniLineMatchesKey("  jetflames=0", "JetFlames"), "case-insensitive + indent matches");
        CheckTrue(IniLineMatchesKey("JetFlames\t = 1", "JetFlames"), "whitespace before = matches");
        CheckTrue(!IniLineMatchesKey("; JetFlames = 1", "JetFlames"), "comment ; not matched");
        CheckTrue(!IniLineMatchesKey("# JetFlames = 1", "JetFlames"), "comment # not matched");
        CheckTrue(!IniLineMatchesKey("JetFlamesX = 1", "JetFlames"), "prefix key not matched");
        CheckTrue(!IniLineMatchesKey("JetFlames", "JetFlames"), "no '=' not matched");
    }

    // --- update existing key preserves everything else --------------------
    {
        std::vector<std::string> doc = {
            "; OpenShim user preferences",
            "",
            "[Display]",
            "JetFlames = 0   ",
            "UnderAttackAlert = Normal",
            "",
            "[SinglePlayer]",
            "GlobalTurbo = 1",
        };
        Update(doc, "Display", "JetFlames", "1");
        CheckEq(doc, {
            "; OpenShim user preferences",
            "",
            "[Display]",
            "JetFlames = 1",
            "UnderAttackAlert = Normal",
            "",
            "[SinglePlayer]",
            "GlobalTurbo = 1",
        }, "existing key rewritten in place; comments/blank/other keys survive");
    }

    // --- same key name in another section must not be touched -------------
    {
        std::vector<std::string> doc = {
            "[Display]",
            "Enabled = 1",
            "[SinglePlayer]",
            "Enabled = 0",
        };
        Update(doc, "SinglePlayer", "Enabled", "1");
        CheckEq(doc, {
            "[Display]",
            "Enabled = 1",
            "[SinglePlayer]",
            "Enabled = 1",
        }, "key scoped to its section");
    }

    // --- missing key appends inside the section, before trailing blanks ---
    {
        std::vector<std::string> doc = {
            "[Display]",
            "JetFlames = 1",
            "",
            "",
            "[SinglePlayer]",
            "GlobalTurbo = 1",
        };
        Update(doc, "Display", "UnitVoFeedback", "Reduced");
        CheckEq(doc, {
            "[Display]",
            "JetFlames = 1",
            "UnitVoFeedback = Reduced",
            "",
            "",
            "[SinglePlayer]",
            "GlobalTurbo = 1",
        }, "missing key appended before trailing blank lines");
    }

    // --- missing key appends at EOF when section is last -------------------
    {
        std::vector<std::string> doc = {
            "[Display]",
            "JetFlames = 1",
        };
        Update(doc, "Display", "TargetPolicy", "Default");
        CheckEq(doc, {
            "[Display]",
            "JetFlames = 1",
            "TargetPolicy = Default",
        }, "missing key appended at end of last section");
    }

    // --- missing section created at end, blank separator added -------------
    {
        std::vector<std::string> doc = {
            "[Display]",
            "JetFlames = 1",
        };
        Update(doc, "General", "SettingsUi", "1");
        CheckEq(doc, {
            "[Display]",
            "JetFlames = 1",
            "",
            "[General]",
            "SettingsUi = 1",
        }, "missing section created with separator");
    }

    // --- empty document gets section without leading blank ------------------
    {
        std::vector<std::string> doc;
        Update(doc, "Display", "JetFlames", "0");
        CheckEq(doc, {
            "[Display]",
            "JetFlames = 0",
        }, "empty document initialized");
    }

    // --- legacy alias replaced in place under canonical name ----------------
    {
        static const char* const kAlt[] = { "SmartReticleConvergence" };
        std::vector<std::string> doc = {
            "[SinglePlayer]",
            "; convergence tuning",
            "SmartReticleConvergence = 0",
        };
        Update(doc, "SinglePlayer", "PlayerReticleConvergence", "1", kAlt, 1);
        CheckEq(doc, {
            "[SinglePlayer]",
            "; convergence tuning",
            "PlayerReticleConvergence = 1",
        }, "legacy alias line replaced by canonical key");
    }

    // --- canonical key wins over alias when both present --------------------
    {
        static const char* const kAlt[] = { "TargetReticle" };
        std::vector<std::string> doc = {
            "[Display]",
            "TargetReticle = ExplicitOnly",
            "TargetPolicy = Default",
        };
        Update(doc, "Display", "TargetPolicy", "NeutralOnly", kAlt, 1);
        CheckEq(doc, {
            "[Display]",
            "TargetReticle = ExplicitOnly",
            "TargetPolicy = NeutralOnly",
        }, "canonical key preferred over alias");
    }

    // --- section header matching is case-insensitive ------------------------
    {
        std::vector<std::string> doc = {
            "[display]",
            "JetFlames = 0",
        };
        Update(doc, "Display", "JetFlames", "1");
        CheckEq(doc, {
            "[display]",
            "JetFlames = 1",
        }, "section matched case-insensitively, header casing preserved");
    }

    // --- commented-out key line must not be edited ---------------------------
    {
        std::vector<std::string> doc = {
            "[Display]",
            "; JetFlames = 0",
        };
        Update(doc, "Display", "JetFlames", "1");
        CheckEq(doc, {
            "[Display]",
            "; JetFlames = 0",
            "JetFlames = 1",
        }, "commented key kept, live key appended");
    }

    // --- repeated updates are idempotent in shape -----------------------------
    {
        std::vector<std::string> doc = {
            "[Display]",
            "JetFlames = 0",
        };
        Update(doc, "Display", "JetFlames", "1");
        Update(doc, "Display", "JetFlames", "0");
        Update(doc, "Display", "JetFlames", "1");
        CheckEq(doc, {
            "[Display]",
            "JetFlames = 1",
        }, "repeated cycling never duplicates lines");
    }

    std::printf("%d checks, %d failures\n", g_Checks, g_Failures);
    return g_Failures == 0 ? 0 : 1;
}
