#include "give_weapon_selected_guard.h"

#include <cstdint>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::GiveWeaponSelected;

    void TestSelectedBitCleared()
    {
        uint32_t out = 0;
        CHECK(SelectedMaskAfterNilGive(0x05u, 2, out));  // slots 0 and 2 selected
        CHECK(out == 0x01u);
        CHECK(SelectedMaskAfterNilGive(0x1Fu, 4, out));
        CHECK(out == 0x0Fu);
        CHECK(SelectedMaskAfterNilGive(0x01u, 0, out));
        CHECK(out == 0x00u);
    }

    void TestNothingToWrite()
    {
        uint32_t out = 0xDEADu;
        CHECK(!SelectedMaskAfterNilGive(0x05u, 1, out));  // slot 1 not selected
        CHECK(out == 0x05u);
        CHECK(!SelectedMaskAfterNilGive(0u, 3, out));
        CHECK(out == 0u);
    }

    void TestOutOfRangeSlotIgnored()
    {
        uint32_t out = 0;
        CHECK(!SelectedMaskAfterNilGive(0xFFFFFFFFu, 5, out));
        CHECK(out == 0xFFFFFFFFu);
        CHECK(!SelectedMaskAfterNilGive(0xFFFFFFFFu, -1, out));
        CHECK(!SelectedMaskAfterNilGive(0xFFFFFFFFu, 31, out));
        CHECK(!SelectedMaskAfterNilGive(0xFFFFFFFFu, 32, out));
    }

    void TestStockRangeCheckNeverRejects()
    {
        for (int slot = -40; slot <= 40; ++slot)
            CHECK(!RangeCheckRejects(kRangeCheckStockJcc, slot));
    }

    void TestFixedRangeCheckRejectsOutsideZeroToFour()
    {
        for (int slot = -40; slot <= 40; ++slot)
        {
            const bool rejects = RangeCheckRejects(kRangeCheckFixedJcc, slot);
            CHECK(rejects == !SlotInRange(slot));
        }
        CHECK(RangeCheckRejects(kRangeCheckFixedJcc, 0x7FFFFFFF));
        CHECK(RangeCheckRejects(kRangeCheckFixedJcc, -0x7FFFFFFF - 1));
    }
}

int main()
{
    TestSelectedBitCleared();
    TestNothingToWrite();
    TestOutOfRangeSlotIgnored();
    TestStockRangeCheckNeverRejects();
    TestFixedRangeCheckRejectsOutsideZeroToFour();
    return OpenShimTest::ExitCode();
}
