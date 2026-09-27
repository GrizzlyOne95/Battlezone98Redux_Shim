#include "map_filter_extras.h"

#include <cstdio>
#include <initializer_list>

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

    using namespace BZROpenShim::MapFilterExtras;

    void TestKeysRoundTripAndStockKeysAreNotExtras()
    {
        for (const ExtraFilterInfo& info : kExtraFilters)
            CHECK(ExtraFromKey(info.key) == info.extra);
        // Stock keys, and anything else, stay with the stock predicate.
        for (const char* key : {"All Maps", "2", "8", "D", "S", "", "OpenShim:"})
            CHECK(ExtraFromKey(key) == Extra::None);
        CHECK(ExtraFromKey(nullptr) == Extra::None);
    }

    void TestFivePlusUsesTheMaximum()
    {
        CHECK(MatchesExtra(Extra::FivePlusPlayers, 2, 8, "0"));
        CHECK(MatchesExtra(Extra::FivePlusPlayers, 5, 5, "0"));
        CHECK(!MatchesExtra(Extra::FivePlusPlayers, 2, 4, "0"));
        CHECK(!MatchesExtra(Extra::FivePlusPlayers, 1, 1, "0"));
    }

    void TestStockMeansWorkshopIdZero()
    {
        CHECK(MatchesExtra(Extra::StockOnly, 2, 8, "0"));
        CHECK(!MatchesExtra(Extra::StockOnly, 2, 8, "1234567890"));
        CHECK(!MatchesExtra(Extra::StockOnly, 2, 8, ""));
        CHECK(!MatchesExtra(Extra::StockOnly, 2, 8, "00"));
        CHECK(!MatchesExtra(Extra::StockOnly, 2, 8, nullptr));
    }

    void TestNoneKeepsEverything()
    {
        CHECK(MatchesExtra(Extra::None, 0, 0, nullptr));
    }

    void TestSearch()
    {
        CHECK(ContainsIgnoreCase("Achilles Heel", "achilles"));
        CHECK(ContainsIgnoreCase("Achilles Heel", "HEEL"));
        CHECK(ContainsIgnoreCase("Achilles Heel", "s h"));
        CHECK(!ContainsIgnoreCase("Achilles Heel", "Heels"));
        CHECK(ContainsIgnoreCase("abc", ""));
        CHECK(ContainsIgnoreCase("abc", nullptr));
        CHECK(ContainsIgnoreCase(nullptr, ""));
        CHECK(!ContainsIgnoreCase(nullptr, "a"));
        CHECK(ContainsIgnoreCase("aab", "ab")); // restarts after a partial match

        CHECK(MatchesSearch("Achilles Heel", "mpach01.bzn", "mpach"));
        CHECK(MatchesSearch("Achilles Heel", "mpach01.bzn", "heel"));
        CHECK(!MatchesSearch("Achilles Heel", "mpach01.bzn", "titan"));
    }
}

int main()
{
    TestKeysRoundTripAndStockKeysAreNotExtras();
    TestFivePlusUsesTheMaximum();
    TestStockMeansWorkshopIdZero();
    TestNoneKeepsEverything();
    TestSearch();
    if (g_failures)
    {
        std::printf("%d failure(s)\n", g_failures);
        return 1;
    }
    std::printf("map_filter_extras_tests: ok\n");
    return 0;
}
