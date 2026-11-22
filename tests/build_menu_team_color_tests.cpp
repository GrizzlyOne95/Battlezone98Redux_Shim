#include "build_menu_team_color.h"

#include "test_check.h"

namespace
{
    using namespace BZROpenShim::BuildMenuTeamColor;

    void TestStockClampOverruns()
    {
        // Team 3 indexes past white/green/red: the stack cookie at [ebp-4].
        CHECK(ColorIndex(3, kStockClampMax) == 3);
        CHECK(ColorIndex(3, kStockClampMax) >= kColorCount);
        CHECK(ColorIndex(15, kStockClampMax) == 3);
    }

    void TestFixedClampStaysInArray()
    {
        for (int team = -20; team <= 40; ++team)
        {
            const int index = ColorIndex(team, kFixedClampMax);
            CHECK(index >= 0 && index < kColorCount);
        }
    }

    void TestTeamsZeroToTwoUnchanged()
    {
        for (int team = -5; team <= 2; ++team)
            CHECK(ColorIndex(team, kFixedClampMax) == ColorIndex(team, kStockClampMax));
        CHECK(ColorIndex(0, kFixedClampMax) == 0);  // white
        CHECK(ColorIndex(1, kFixedClampMax) == 1);  // green
        CHECK(ColorIndex(2, kFixedClampMax) == 2);  // red
        CHECK(ColorIndex(3, kFixedClampMax) == 2);  // red, as team 2
    }
}

int main()
{
    TestStockClampOverruns();
    TestFixedClampStaysInArray();
    TestTeamsZeroToTwoUnchanged();
    return OpenShimTest::ExitCode();
}
