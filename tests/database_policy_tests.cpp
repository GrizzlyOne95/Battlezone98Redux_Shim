#include "database_policy.h"
#include "test_check.h"
#include <string>
#include <vector>

using namespace BZROpenShim::DatabasePolicy;
using OpenShimTest::Check;

namespace
{
    void TestParse()
    {
        std::vector<std::string> errors;
        const Content c = ParseContent(
            "\xEF\xBB\xBF; header comment\r\n"
            "[tab nsdf]\r\n"
            "label = NSDF\r\n"
            "\n"
            "# another comment\n"
            "[unit AVTANK]\n"
            "Tab = nsdf\n"
            "designation = M60A7 Grizzly | BZ98 Redux manual p10\n"
            "designation = T7 Grizzly\n"
            "lore =\n"
            "stray line\n"
            "[broken\n"
            "[unit]\n"
            "[unit two words]\n"
            "orphan = 1\n"
            "[campaign nsdf]\n"
            "tab = briefings\n"
            "missions = misn01 misn02,misn03\n"
            "missions = MISN04\n"
            "[unit avtank]\n"
            "icon = a.png\n",
            &errors);
        Check(c.sections.size() == 3, "three sections (repeated header continues the first)");
        const Section* tab = c.Find("tab", "nsdf");
        Check(tab && tab->Get("label") == "NSDF", "tab label");
        const Section* unit = c.Find("unit", "avtank");
        Check(unit != nullptr, "kind and id are lower-cased");
        Check(unit && unit->Get("tab") == "nsdf", "keys are lower-cased");
        Check(unit && unit->GetAll("designation").size() == 2, "repeated key keeps every value");
        Check(unit && unit->Has("lore") && unit->Get("lore").empty(), "empty lore is kept as a present, empty key");
        Check(unit && unit->Get("icon") == "a.png", "continued section gets later values");
        Check(errors.size() == 5, "five bad lines reported, got " + std::to_string(errors.size()));
        Check(!errors.empty() && errors[0].rfind("line 11:", 0) == 0, "error names its line");

        const Section* campaign = c.Find("campaign", "nsdf");
        std::vector<std::string> missions;
        for (const std::string& v : campaign ? campaign->GetAll("missions") : std::vector<std::string>())
            for (const std::string& m : SplitList(v))
                missions.push_back(m);
        Check(missions.size() == 4 && missions[2] == "misn03" && missions[3] == "misn04",
              "mission lists split on space and comma and are lower-cased");

        Check(c.InTab("nsdf").size() == 1 && c.InTab("briefings").size() == 1, "entries by tab");
        Check(c.OfKind("tab").size() == 1, "tabs by kind");
    }

    void TestDesignation()
    {
        const Designation a = ParseDesignation(" M173 Badger | tran02.des:1 ");
        Check(a.text == "M173 Badger" && a.citation == "tran02.des:1", "text and citation");
        const Designation b = ParseDesignation("T7 Badger");
        Check(b.text == "T7 Badger" && b.citation.empty(), "no citation");
    }

    void TestMerge()
    {
        const Content stock = ParseContent(
            "[tab nsdf]\nlabel = NSDF\n"
            "[unit avtank]\ntab = nsdf\ndesignation = A | a\ndesignation = B | b\nicon = x.png\n"
            "[unit avfigh]\ntab = nsdf\n"
            "[campaign nsdf]\ntab = briefings\nmissions = misn01 misn02\n");
        const Content over = ParseContent(
            "[unit avtank]\ndesignation = C | c\nlore = Cited text\n"
            "[unit avfigh]\nremove = 1\n"
            "[unit crtank]\ntab = nsdf\n"
            "[relic r1]\ntab = relics\n"
            "[unit nothere]\nremove = yes\n");
        const Content m = MergeContent(stock, over);
        const Section* tank = m.Find("unit", "avtank");
        Check(tank && tank->GetAll("designation").size() == 1 && tank->Get("designation") == "C | c",
              "a repeated key in the override replaces the whole list");
        Check(tank && tank->Get("icon") == "x.png" && tank->Get("tab") == "nsdf", "keys the override omits stay");
        Check(tank && tank->Get("lore") == "Cited text", "new key added");
        Check(!m.Find("unit", "avfigh"), "remove drops the stock section");
        Check(m.Find("unit", "crtank") && m.Find("relic", "r1"), "new sections, any kind, are appended");
        Check(!m.Find("unit", "nothere"), "removing a missing section adds nothing");
        Check(m.InTab("nsdf").size() == 2, "tab order: stock first, appended after");
        Check(m.InTab("nsdf")[1]->id == "crtank", "appended entry comes last");

        const Content twice = MergeContent(stock, ParseContent("[unit avtank]\ndesignation = D\ndesignation = E\n"));
        Check(twice.Find("unit", "avtank")->GetAll("designation").size() == 2,
              "an override list with two values keeps both");
        const Content same = MergeContent(stock, Content());
        Check(same.sections.size() == stock.sections.size(), "an empty override changes nothing");
    }

    void TestInfHeader()
    {
        InfHeader h = ParseInfHeader("GRIZZLY - MEDIUM TANK:\r\nA well rounded battle tank\r\n");
        Check(h.model == "GRIZZLY" && h.role == "MEDIUM TANK", "model - role");
        h = ParseInfHeader("RECYCLER:\nText");
        Check(h.model.empty() && h.role == "RECYCLER", "role alone");
        h = ParseInfHeader("BLACK DOG RED DEVIL:\n");
        Check(h.model.empty() && h.role == "BLACK DOG RED DEVIL", "no dash is a role");
        h = ParseInfHeader("\r\nName: Fury\r\nFunction: Sentient Fighter\r\n\r\nAdditional");
        Check(h.model == "Fury" && h.role == "Sentient Fighter", "Name:/Function: form, leading blank skipped");
        h = ParseInfHeader("Name: Fury Tank\n");
        Check(h.model == "Fury Tank" && h.role.empty(), "Name: without Function:");
        h = ParseInfHeader("");
        Check(h.model.empty() && h.role.empty(), "empty file");
    }

    void TestOdfAndStats()
    {
        const Odf odf = ParseOdf(
            "[GameObjectClass]\r\n"
            "scrapCost = 8 // comment\r\n"
            "maxHealth = 3000\r\n"
            "maxAmmo=1200\r\n"
            "unitName = \"Tank\"\r\n"
            "weaponName1 = \"gatstab\"\r\n"
            "weaponName2 = \"gminigun\"\r\n"
            "weaponName4 = \"gmdmgun\" ; trailing\r\n"
            "[HoverCraftClass]\r\n"
            "velocForward = 20.0\r\n");
        Check(odf.Get("gameobjectclass", "UNITNAME") == "Tank", "case-insensitive lookup, quotes stripped");
        Check(odf.Get("", "velocForward") == "20.0", "any-section lookup");
        Check(odf.Get("GameObjectClass", "velocForward").empty(), "section-bound lookup misses other sections");

        const UnitStats stats = ReadStats(odf, [](const std::string& w) {
            return w == "gatstab" ? std::string("AT-Stabber") : std::string();
        });
        Check(stats.scrapCost == "8" && stats.health == "3000" && stats.ammo == "1200", "core stats");
        Check(stats.speed == "20.0", "speed raw");
        Check(stats.weapons.size() == 3, "three weapon slots");
        Check(stats.weapons.size() == 3 && stats.weapons[2].slot == 4 && stats.weapons[2].odf == "gmdmgun",
              "slot numbers keep gaps");
        Check(!stats.weapons.empty() && stats.weapons[0].name == "AT-Stabber", "weapon display name");

        UnitDetail unit;
        unit.odf = "avtank";
        unit.role = "MEDIUM TANK";
        unit.model = "GRIZZLY";
        unit.designations = { { "M60A7 Grizzly", "BZ98 Redux manual p10" }, { "", "skipped" } };
        unit.odfFound = true;
        unit.stats = stats;
        const std::string text = FormatUnitDetail(unit, Labels());
        Check(text.find("Role: MEDIUM TANK\n") != std::string::npos, "role line");
        Check(text.find("Model: GRIZZLY\n") != std::string::npos, "model line");
        Check(text.find("  M60A7 Grizzly  (BZ98 Redux manual p10)\n") != std::string::npos, "designation with citation");
        Check(text.find("skipped") == std::string::npos, "empty designation not shown");
        Check(text.find("Scrap cost: 8\n") != std::string::npos, "scrap");
        Check(text.find("Armor: 3000\n") != std::string::npos, "armor");
        Check(text.find("Speed: 20 m/s\n") != std::string::npos, "speed formatted");
        Check(text.find("  Slot 1: AT-Stabber (gatstab)\n") != std::string::npos, "named weapon");
        Check(text.find("  Slot 2: gminigun\n") != std::string::npos, "unnamed weapon shows its ODF");
        Check(text.find("Notes") == std::string::npos, "empty lore shows nothing");

        unit.lore = "  Cited lore.  ";
        unit.odfFound = false;
        const std::string missing = FormatUnitDetail(unit, Labels());
        Check(missing.find("ODF not found (avtank.odf)") != std::string::npos, "missing ODF");
        Check(missing.find("Scrap cost") == std::string::npos, "no stats without the ODF");
        Check(missing.find("Notes:\nCited lore.\n") != std::string::npos, "lore shown when present");

        UnitDetail bare;
        bare.odf = "x";
        bare.odfFound = true;
        const std::string none = FormatUnitDetail(bare, Labels());
        Check(none.find("Speed: -\n") != std::string::npos, "missing speed is a dash without a unit");
        Check(none.find("Weapons: none\n") != std::string::npos, "no weapons");
    }

    void TestFormatNumber()
    {
        Check(FormatNumber("20.0") == "20", "trailing zeros");
        Check(FormatNumber("400.0f") == "400", "float suffix");
        Check(FormatNumber("1.25") == "1.25", "decimals kept");
        Check(FormatNumber("0.126") == "0.13", "two decimals at most");
        Check(FormatNumber(" 8 ") == "8", "trimmed");
        Check(FormatNumber("").compare("-") == 0, "empty is a dash");
        Check(FormatNumber("fast") == "fast", "text kept");
        Check(FormatNumber("-0.0") == "0", "negative zero");
    }

    void TestCaptionAndPaging()
    {
        Check(UnitCaption("GRIZZLY", "MEDIUM TANK", "Tank", "avtank") == "GRIZZLY", "model first");
        Check(UnitCaption("", "RECYCLER", "Recycler", "avrecy") == "RECYCLER", "role next");
        Check(UnitCaption("", "", "Tank", "avtank") == "Tank", "unitName next");
        Check(UnitCaption("", "", "", "avtank") == "avtank", "ODF last");
        Check(PageCount(0, 16) == 1 && PageCount(16, 16) == 1 && PageCount(17, 16) == 2, "page count");
        Check(PageCount(5, 0) == 1, "zero rows per page is one page");
    }

    void TestComments()
    {
        std::vector<std::string> errors;
        const Content c = ParseContent(
            "[tab nsdf] ; the NSDF tab\n"
            "label = NSDF ; trailing\n"
            "[tab cca] # hash\n"
            "label = CCA # trailing\n"
            "[unit avtank]  \n"
            "designation = M60A7 Grizzly | BZ98 Redux manual p10\n"
            "designation = A | campaigns.csv:57; misn03.des:7\n"
            "designation = B | c#1\n"
            "name = \"Odd ; name # x\" ; real comment\n"
            "[bad] junk\n",
            &errors);
        Check(c.Find("tab", "nsdf") != nullptr && c.Find("tab", "cca") != nullptr, "header with a trailing comment");
        Check(c.Find("tab", "nsdf")->Get("label") == "NSDF", "value comment after ;");
        Check(c.Find("tab", "cca")->Get("label") == "CCA", "value comment after #");
        const Section* unit = c.Find("unit", "avtank");
        Check(unit && unit->GetAll("designation").size() == 3, "unit parsed");
        Check(unit && unit->GetAll("designation")[0] == "M60A7 Grizzly | BZ98 Redux manual p10",
              "designation with a citation stays intact");
        Check(unit && unit->GetAll("designation")[1] == "A | campaigns.csv:57; misn03.des:7",
              "; not preceded by whitespace stays");
        Check(unit && unit->GetAll("designation")[2] == "B | c#1", "# not preceded by whitespace stays");
        Check(unit && unit->Get("name") == "\"Odd ; name # x\"", "comment marker inside quotes stays");
        Check(errors.size() == 1, "a header followed by junk is still an error");
    }

    void TestParserEdges()
    {
        const Odf odf = ParseOdf("[GameObjectClass]\n"
                                 "unitName = \"Tank; Mk // 2\" ; note\n"
                                 "scrapCost = 40 // plain\n"
                                 "label = \"open\n");
        Check(odf.Get("GameObjectClass", "unitName") == "Tank; Mk // 2", "quoted ; and // survive");
        Check(odf.Get("GameObjectClass", "scrapCost") == "40", "unquoted // still a comment");
        const InfHeader bom = ParseInfHeader("\xEF\xBB\xBFGRIZZLY - MEDIUM TANK:\nmore\n");
        Check(bom.model == "GRIZZLY" && bom.role == "MEDIUM TANK", "inf header BOM stripped");
    }

    void TestMergeWarnings()
    {
        const Content stock = ParseContent("[tab a]\nlabel = A\n[tab b]\nlabel = B\n"
                                           "[unit u1]\ntab = a\n[unit u2]\ntab = a\n[unit u3]\ntab = b\n");
        std::vector<std::string> warnings;
        MergeContent(stock, ParseContent("[tab a]\nremove = 1\n"), &warnings);
        Check(warnings.size() == 1 && warnings[0].find("'a'") != std::string::npos &&
                  warnings[0].find("2 entries") != std::string::npos,
              "removed tab with entries warns with the count");
        warnings.clear();
        MergeContent(stock, ParseContent("[tab a]\nremove = 1\n[unit u1]\nremove = 1\n[unit u2]\nremove = 1\n"),
                     &warnings);
        Check(warnings.empty(), "no warning when the entries went too");
        warnings.clear();
        MergeContent(stock, ParseContent("[tab a]\nlabel = X\n"), &warnings);
        Check(warnings.empty(), "no warning when no tab is removed");
    }
}

int main()
{
    TestParse();
    TestDesignation();
    TestMerge();
    TestInfHeader();
    TestOdfAndStats();
    TestFormatNumber();
    TestCaptionAndPaging();
    TestComments();
    TestParserEdges();
    TestMergeWarnings();
    return OpenShimTest::ExitCode();
}
