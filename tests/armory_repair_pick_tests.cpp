#include "armory_repair_pick_policy.h"

#include <cmath>
#include <limits>
#include "test_check.h"

namespace
{
    using BZROpenShim::ArmoryRepairPickHealth;

    void TestStaleCurrentUsesRatio()
    {
        CHECK(ArmoryRepairPickHealth(2000.0f, 0.5f, 2000.0f) == 1000.0f);
    }

    void TestFullHealthStaysAtMax()
    {
        CHECK(ArmoryRepairPickHealth(2000.0f, 1.0f, 2000.0f) == 2000.0f);
        CHECK(ArmoryRepairPickHealth(2000.0f, 1.5f, 2000.0f) == 2000.0f);
    }

    void TestLowerStoredCurrentWins()
    {
        CHECK(ArmoryRepairPickHealth(300.0f, 0.5f, 2000.0f) == 300.0f);
    }

    void TestBadInputsFallBackToCurrent()
    {
        const float nan = std::numeric_limits<float>::quiet_NaN();
        CHECK(ArmoryRepairPickHealth(5.0f, 0.5f, 0.0f) == 5.0f);
        CHECK(ArmoryRepairPickHealth(5.0f, 0.5f, -1.0f) == 5.0f);
        CHECK(ArmoryRepairPickHealth(5.0f, 0.5f, nan) == 5.0f);
        CHECK(ArmoryRepairPickHealth(5.0f, nan, 100.0f) == 5.0f);
        CHECK(ArmoryRepairPickHealth(5.0f, std::numeric_limits<float>::infinity(), 100.0f) == 5.0f);
        CHECK(ArmoryRepairPickHealth(100.0f, 0.0f, 100.0f) == 100.0f);
        CHECK(ArmoryRepairPickHealth(100.0f, -0.5f, 100.0f) == 100.0f);
    }
}

int main()
{
    TestStaleCurrentUsesRatio();
    TestFullHealthStaysAtMax();
    TestLowerStoredCurrentWins();
    TestBadInputsFallBackToCurrent();
    return OpenShimTest::ExitCode();
}
