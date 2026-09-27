#include "light_colour_presets.h"
#include "stable_id_list.h"

#include <cstdio>
#include <string>
#include <vector>

namespace
{
    int g_failures = 0;

    void Check(bool cond, const char* what, int line)
    {
        if (!cond)
        {
            ++g_failures;
            std::printf("FAIL %d: %s\n", line, what);
        }
    }

#define CHECK(c) Check((c), #c, __LINE__)

    using BZROpenShim::StableIdList::Format;
    using BZROpenShim::StableIdList::NormalizeId;
    using BZROpenShim::StableIdList::Parse;
    using BZROpenShim::StableIdList::Record;

    void TestNormalizeId()
    {
        CHECK(NormalizeId("g123abc") == "G123ABC");
        CHECK(NormalizeId("S42 trailing") == "S42");
        CHECK(NormalizeId("G9#comment") == "G9");
        CHECK(NormalizeId("G9;comment") == "G9");
        CHECK(NormalizeId("") == "");
        CHECK(NormalizeId(nullptr) == "");
    }

    void TestParseSkipsCommentsAndBlankLines()
    {
        const std::vector<Record> records = Parse(
            "; OpenShim ban list\n"
            "# another comment\n"
            "\n"
            "   \t\n"
            "g1 Alice\n"
            "  s2   Bob Smith  \n"
            "G3\n");
        CHECK(records.size() == 3);
        CHECK(records.size() == 3 && records[0].id == "G1" && records[0].name == "Alice");
        CHECK(records.size() == 3 && records[1].id == "S2" && records[1].name == "Bob Smith");
        CHECK(records.size() == 3 && records[2].id == "G3" && records[2].name.empty());
    }

    void TestParseCrLfAndMissingFinalNewline()
    {
        const std::vector<Record> records = Parse("G1 Alice\r\nG2 Bob");
        CHECK(records.size() == 2);
        CHECK(records.size() == 2 && records[0].name == "Alice" && records[1].name == "Bob");
    }

    void TestParseFirstEntryWinsAndFillsName()
    {
        const std::vector<Record> records = Parse(
            "G1\n"
            "g1 Alice\n"
            "G1 Mallory\n"
            "G2 Bob\n"
            "g2 Eve\n");
        CHECK(records.size() == 2);
        CHECK(records.size() == 2 && records[0].id == "G1" && records[0].name == "Alice");
        CHECK(records.size() == 2 && records[1].id == "G2" && records[1].name == "Bob");
    }

    void TestParseSkipsLinesWithoutAnId()
    {
        CHECK(Parse("").empty());
        CHECK(Parse("\n\n").empty());
        const std::vector<Record> records = Parse("G1;inline\n#G2\n");
        CHECK(records.size() == 1 && records[0].id == "G1" && records[0].name.empty());
    }

    void TestFormatRoundTrips()
    {
        const std::vector<Record> records = { { "G1", "Alice" }, { "S2", "" }, { "G3", "Bob Smith" } };
        const std::string text = Format(records, "OpenShim ban list", "<stable_id> [display name]");
        CHECK(text ==
              "; OpenShim ban list\n"
              "; Format: <stable_id> [display name]\n"
              "G1 Alice\n"
              "S2\n"
              "G3 Bob Smith\n");
        const std::vector<Record> reparsed = Parse(text);
        CHECK(reparsed.size() == 3);
        CHECK(reparsed.size() == 3 && reparsed[2].name == "Bob Smith" && reparsed[1].name.empty());
    }

    void TestLightColourPresets()
    {
        using BZROpenShim::LightColourPresets::TryFind;
        float r = -1.0f;
        float g = -1.0f;
        float b = -1.0f;
        CHECK(TryFind("orange", r, g, b) && r == 5.0f && g == 2.5f && b == 1.0f);
        CHECK(TryFind("white", r, g, b) && r == 5.0f && g == 5.0f && b == 5.0f);
        r = -1.0f;
        CHECK(!TryFind("Orange", r, g, b) && r == -1.0f);
        CHECK(!TryFind("rainbow", r, g, b));
        CHECK(!TryFind(nullptr, r, g, b));
        CHECK(sizeof(BZROpenShim::LightColourPresets::kPresets) /
                  sizeof(BZROpenShim::LightColourPresets::kPresets[0]) == 10);
    }
}

int main()
{
    TestNormalizeId();
    TestParseSkipsCommentsAndBlankLines();
    TestParseCrLfAndMissingFinalNewline();
    TestParseFirstEntryWinsAndFillsName();
    TestParseSkipsLinesWithoutAnId();
    TestFormatRoundTrips();
    TestLightColourPresets();
    if (g_failures == 0)
        std::printf("stable_id_list_tests: all passed\n");
    return g_failures == 0 ? 0 : 1;
}
