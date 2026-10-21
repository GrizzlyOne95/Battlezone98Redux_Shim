// The options-UI localization table: the shipped CSV parses, every registry
// row, value label, category and pseudo row has its key, the English column
// matches the compiled text, and lookups fall back to English instead of
// blank. Docs/OPTIONS_UI_LOCALIZATION.md.
#include "options_ui_l10n.h"
#include "test_check.h"

#include <cstddef>
#include <cstring>
#include <fstream>
#include <iterator>
#include <set>
#include <string>

#ifndef OPENSHIM_L10N_TABLE
#error OPENSHIM_L10N_TABLE must name resources/localization/openshim_localization.csv
#endif

using OpenShimTest::Check;
namespace L10n = BZROpenShim::OptionsL10n;

namespace Registry
{
    // bzr_options_ui.h carries the real enum but also __thiscall engine
    // types the Linux lane cannot compile; the .inc only names enumerators,
    // so a new apply group must be added here as well.
    enum class ShimSettingApplyGroup
    {
        GlobalImprovement, UnderAttackAlert, TargetReticle, JetFlames, UnitVo, GlobalTurbo,
        Headlights, PilotFlashlight, AutoSave, HudFeedback, HudPalette, ContextualHud,
        BzrNetRoute, RenderProfile, LiveEngineToggle, ReadOnNextUse, RestartRequired,
        CareerStatsReset,
    };

#include "../src/patches/bzr_options_registry.inc"
#include "../src/patches/bzr_options_categories.inc"
}

static std::string ReadFile(const char* path)
{
    std::ifstream file(path, std::ios::binary);
    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

static bool EnglishIs(const L10n::Table& table, const std::string& key, const char* english)
{
    const char* cell = table.Find(key, L10n::English);
    const bool ok = cell && english && std::strcmp(cell, english) == 0;
    if (!ok)
        OpenShimTest::Fail("%s: English cell is \"%s\", code has \"%s\"", key.c_str(), cell ? cell : "(missing)",
                           english ? english : "(null)");
    return ok;
}

static void CheckShippedTable()
{
    const std::string text = ReadFile(OPENSHIM_L10N_TABLE);
    OpenShimTest::Require(!text.empty(), "shipped localization table is readable");
    const std::string header = "Key~English~French~German~Spanish~Italian~Russian~Portuguese\r\n";
    Check(text.compare(0, header.size(), header) == 0,
          "table starts with the stock header and CRLF");
    Check(text.find('\t') == std::string::npos, "table has no tabs");
    Check(!(text.size() >= 3 && static_cast<unsigned char>(text[0]) == 0xEF), "table is ANSI, not UTF-8 with BOM");

    L10n::Table table;
    std::string error;
    OpenShimTest::Require(table.Parse(text, &error), "shipped localization table parses");

    std::set<std::string> seen;
    for (const auto& key : table.KeysInOrder())
    {
        if (!seen.insert(key).second)
            OpenShimTest::Fail("duplicate key %s", key.c_str());
        if (key.compare(0, 9, "openshim_") != 0)
            OpenShimTest::Fail("key %s is outside the openshim_ namespaces", key.c_str());
    }

    std::set<std::string> iniKeys;
    for (const auto& setting : Registry::g_ShimSettingsRegistry)
    {
        Check(setting.label && *setting.label, "every row has an English label");
        Check(setting.description && *setting.description, std::string(setting.label) + " has a description");
        if (setting.key && *setting.key)
            Check(iniKeys.insert(setting.key).second, std::string("ini key is unique: ") + setting.key);
        EnglishIs(table, L10n::RowKey(setting.key, setting.label, "label"), setting.label);
        EnglishIs(table, L10n::RowKey(setting.key, setting.label, "desc"), setting.description);
        for (size_t i = 0; i < setting.valueCount; ++i)
        {
            const std::string own = L10n::RowValueKey(setting.key, setting.label, setting.values[i]);
            if (table.Has(own))
                EnglishIs(table, own, setting.valueLabels[i]);
            else
                EnglishIs(table, L10n::CommonValueKey(setting.valueLabels[i]), setting.valueLabels[i]);
        }
    }

    for (const auto& category : Registry::kShimSettingsCategories)
    {
        EnglishIs(table, L10n::CategoryKey(category.name, "name"), category.name);
        EnglishIs(table, L10n::CategoryKey(category.name, "title"), category.title);
        EnglishIs(table, L10n::CategoryKey(category.name, "blurb"), category.blurb);
    }

    const char* const pseudoRows[] = {
        Registry::kShimRowUpdateCheck, Registry::kShimRowKeyBindings, Registry::kShimRowReticle,
        Registry::kShimRowPalette, Registry::kShimRowDamage, Registry::kShimRowFading,
        Registry::kShimRowMeters, Registry::kShimRowRadar, Registry::kShimRowMenuTheme,
    };
    for (const char* row : pseudoRows)
    {
        EnglishIs(table, "openshim_ui:row:" + L10n::Slug(row) + ":label", row);
        Check(table.Has("openshim_ui:row:" + L10n::Slug(row) + ":desc"), std::string(row) + " has a description key");
    }

    std::printf("shipped table: %zu keys, %zu registry rows, %zu categories\n", table.Size(),
                sizeof(Registry::g_ShimSettingsRegistry) / sizeof(Registry::g_ShimSettingsRegistry[0]),
                sizeof(Registry::kShimSettingsCategories) / sizeof(Registry::kShimSettingsCategories[0]));
}

static void CheckFallback()
{
    // File order is the stock one: Russian before Portuguese.
    const char* text =
        "\xEF\xBB\xBF"
        "Key~English~French~German~Spanish~Italian~Russian~Portuguese\r\n"
        "~~~~~~~\r\n"
        "\r\n"
        "a:full~On~Oui~An~Si~Si~\xC2\xEA\xEB~Ligado\r\n"
        "a:sparse~Off~Non~~~~~\r\n"
        "a:short~Back~Retour\n"
        "a:dup~First~Premier~~~~~\r\n"
        "a:dup~Second~Deuxieme~~~~~\r\n";
    L10n::Table table;
    std::string error;
    Check(table.Parse(text, &error), "BOM, spacers, blank lines and LF-only lines parse");
    Check(table.Size() == 4, "four distinct keys");

    Check(std::strcmp(table.Find("a:full", L10n::Russian), "\xC2\xEA\xEB") == 0,
          "language 7 reads the Russian column byte for byte (cp1251)");
    Check(std::strcmp(table.Find("a:full", L10n::Portuguese), "Ligado") == 0,
          "language 6 reads the Portuguese column although it is last in the file");
    Check(std::strcmp(table.Find("a:dup", L10n::French), "Deuxieme") == 0, "a later duplicate wins");
    Check(table.Find("a:sparse", L10n::German) == nullptr, "an empty cell is missing, never \"\"");
    Check(table.Find("a:short", L10n::Spanish) == nullptr, "a short row is missing its trailing cells");
    Check(table.Find("a:full", 0) == nullptr && table.Find("a:full", 8) == nullptr, "out-of-range languages miss");

    const std::string sparse[] = { "a:sparse" };
    Check(std::strcmp(L10n::Pick(table, L10n::German, sparse, 1, "Off"), "Off") == 0, "empty cell falls back to English");
    Check(std::strcmp(L10n::Pick(table, L10n::French, sparse, 1, "Off"), "Non") == 0, "present cell is used");
    const std::string unknown[] = { "a:nope" };
    Check(std::strcmp(L10n::Pick(table, L10n::French, unknown, 1, "Code"), "Code") == 0, "unknown key falls back to English");
    const std::string full[] = { "a:full" };
    Check(std::strcmp(L10n::Pick(table, L10n::English, full, 1, "Compiled"), "Compiled") == 0,
          "English always returns the compiled string, not the table's");
    Check(std::strcmp(L10n::Pick(table, 9, full, 1, "Compiled"), "Compiled") == 0, "unknown language is English");
    const std::string chain[] = { "a:sparse", "a:full" };
    Check(std::strcmp(L10n::Pick(table, L10n::German, chain, 2, "x"), "An") == 0, "the first non-empty key in a chain wins");

    L10n::Table bad;
    Check(!bad.Parse("Name~English\r\nx~y\r\n", &error), "a header without Key is rejected");
    Check(!bad.Parse("Key~French\r\n", &error), "a header without English is rejected");
    Check(!bad.Parse("", &error), "an empty table is rejected");

    Check(L10n::Slug("Reticle & Hits") == "ReticleHits", "slug keeps ASCII letters and digits");
    Check(L10n::RowKey("RenderProfile", "Render Profile", "label") == "openshim_opt:RenderProfile:label",
          "a row is named by its ini key");
    Check(L10n::RowKey("", "Reset Career Stats", "desc") == "openshim_opt:ResetCareerStats:desc",
          "a keyless row is named by its label");
    Check(L10n::RowValueKey("RenderProfile", "x", "Enhanced") == "openshim_opt:RenderProfile:value:Enhanced",
          "a value is named by the ini value it writes");
}

int main()
{
    CheckFallback();
    CheckShippedTable();
    return OpenShimTest::ExitCode();
}
