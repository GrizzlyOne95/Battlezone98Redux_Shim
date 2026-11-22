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

    void TestControlPanelStockIsUnclamped()
    {
        // The control panel indexes itemColor[3] with the raw team.
        CHECK(StockControlPanelIndex(3) >= kColorCount);
        CHECK(StockControlPanelIndex(-1) < 0);
        CHECK(StockControlPanelIndex(1) == 1);
    }

    void TestControlPanelFixedStaysInTable()
    {
        for (int team = -40; team <= 40; ++team)
        {
            const int index = FixedControlPanelIndex(team);
            CHECK(index >= 0 && index < kColorCount);
            CHECK(index == ColorIndex(team, kFixedClampMax));  // same mapping as the build menu
        }
        for (int team = 0; team < kColorCount; ++team)
            CHECK(FixedControlPanelIndex(team) == StockControlPanelIndex(team));
        CHECK(FixedControlPanelIndex(-1) == 0);  // white
        CHECK(FixedControlPanelIndex(7) == 2);   // red
    }

    void TestControlPanelPatchLayout()
    {
        // The 7-byte load (8B ModRM SIB disp32) sits at +3 / +0x10 in its row,
        // and each row's disp32 is 3 bytes into the load.
        CHECK(kColorLoadLength == 7);
        CHECK(kColorLoadLength >= 5);  // room for jmp rel32
        CHECK(kTitleLoadOffset + kColorLoadLength <= 11);   // ControlPanelTitleColorRead is 11 bytes
        CHECK(kChildLoadOffset + kColorLoadLength <= 30);   // ControlPanelChildColorRead is 30 bytes
        CHECK(kInitTableStoreOffset + 4 <= 34);             // ControlPanelItemColorInit is 34 bytes
    }
}

int main()
{
    TestStockClampOverruns();
    TestFixedClampStaysInArray();
    TestTeamsZeroToTwoUnchanged();
    TestControlPanelStockIsUnclamped();
    TestControlPanelFixedStaysInTable();
    TestControlPanelPatchLayout();
    return OpenShimTest::ExitCode();
}
