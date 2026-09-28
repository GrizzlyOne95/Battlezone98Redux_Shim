#include "memory_access.h"

#include <cstdio>
#include <vector>
#include "test_check.h"

namespace
{
    using BZROpenShim::MemoryAccess::Access;
    using BZROpenShim::MemoryAccess::kMemCommit;
    using BZROpenShim::MemoryAccess::ProtectionAllows;
    using BZROpenShim::MemoryAccess::RangeAllows;
    using BZROpenShim::MemoryAccess::Region;
    namespace Protect = BZROpenShim::MemoryAccess::Protect;

    constexpr uint32_t kMemReserve = 0x2000;

    // A fake address space: a sorted list of regions with no gaps.
    struct FakeSpace
    {
        std::vector<Region> regions;
        int queries = 0;

        bool operator()(uintptr_t address, Region& out)
        {
            ++queries;
            for (const Region& r : regions)
            {
                if (address >= r.base && address < r.base + r.size)
                {
                    out = r;
                    return true;
                }
            }
            return false;
        }
    };

    void TestProtectionTable()
    {
        struct Row
        {
            uint32_t protect;
            bool read;
            bool write;
            bool execute;
        };
        const Row rows[] = {
            {Protect::NoAccess, false, false, false},
            {Protect::ReadOnly, true, false, false},
            {Protect::ReadWrite, true, true, false},
            {Protect::WriteCopy, true, true, false},
            {Protect::Execute, false, false, true},
            {Protect::ExecuteRead, true, false, true},
            {Protect::ExecuteReadWrite, true, true, true},
            {Protect::ExecuteWriteCopy, true, true, true},
        };
        for (const Row& row : rows)
        {
            CHECK(ProtectionAllows(row.protect, Access::Read) == row.read);
            CHECK(ProtectionAllows(row.protect, Access::Write) == row.write);
            CHECK(ProtectionAllows(row.protect, Access::Execute) == row.execute);
        }
    }

    void TestGuardPagesAllowNothing()
    {
        const uint32_t guarded = Protect::ExecuteReadWrite | Protect::Guard;
        CHECK(!ProtectionAllows(guarded, Access::Read));
        CHECK(!ProtectionAllows(guarded, Access::Write));
        CHECK(!ProtectionAllows(guarded, Access::Execute));
    }

    void TestOtherModifiersAreIgnored()
    {
        const uint32_t noCache = 0x200;
        const uint32_t writeCombine = 0x400;
        CHECK(ProtectionAllows(Protect::ReadWrite | noCache, Access::Write));
        CHECK(ProtectionAllows(Protect::ExecuteRead | writeCombine, Access::Execute));
    }

    void TestRejectsNullEmptyAndWrappingRanges()
    {
        FakeSpace space;
        space.regions = {{0x1000, 0x1000, kMemCommit, Protect::ReadWrite}};
        CHECK(!RangeAllows(0, 4, Access::Read, space));
        CHECK(!RangeAllows(0x1000, 0, Access::Read, space));
        CHECK(!RangeAllows(UINTPTR_MAX - 1, 4, Access::Read, space));
        CHECK(space.queries == 0);
    }

    void TestRangeInsideOneRegion()
    {
        FakeSpace space;
        space.regions = {{0x1000, 0x1000, kMemCommit, Protect::ReadOnly}};
        CHECK(RangeAllows(0x1010, 0x20, Access::Read, space));
        CHECK(!RangeAllows(0x1010, 0x20, Access::Write, space));
        CHECK(!RangeAllows(0x1010, 0x20, Access::Execute, space));
    }

    void TestRangeRunningPastTheLastRegion()
    {
        FakeSpace space;
        space.regions = {{0x1000, 0x1000, kMemCommit, Protect::ReadWrite}};
        CHECK(RangeAllows(0x1FF0, 0x10, Access::Read, space));
        CHECK(!RangeAllows(0x1FF0, 0x11, Access::Read, space));
    }

    void TestRangeAcrossRegionsChecksEach()
    {
        FakeSpace space;
        space.regions = {
            {0x1000, 0x1000, kMemCommit, Protect::ReadWrite},
            {0x2000, 0x1000, kMemCommit, Protect::ReadOnly},
            {0x3000, 0x1000, kMemReserve, Protect::ReadWrite},
        };
        CHECK(RangeAllows(0x1FF0, 0x20, Access::Read, space));
        CHECK(!RangeAllows(0x1FF0, 0x20, Access::Write, space));
        CHECK(!RangeAllows(0x2FF0, 0x20, Access::Read, space));
    }

    void TestUncommittedAndGuardedRegionsAreRefused()
    {
        FakeSpace space;
        space.regions = {
            {0x1000, 0x1000, kMemReserve, Protect::ReadWrite},
            {0x2000, 0x1000, kMemCommit, Protect::ReadWrite | Protect::Guard},
        };
        CHECK(!RangeAllows(0x1000, 4, Access::Read, space));
        CHECK(!RangeAllows(0x2000, 4, Access::Read, space));
    }

    void TestZeroSizedRegionDoesNotLoop()
    {
        struct Stuck
        {
            bool operator()(uintptr_t address, Region& out) const
            {
                out = {address, 0, kMemCommit, Protect::ReadWrite};
                return true;
            }
        };
        CHECK(!RangeAllows(0x1000, 4, Access::Read, Stuck{}));
    }
}

int main()
{
    TestProtectionTable();
    TestGuardPagesAllowNothing();
    TestOtherModifiersAreIgnored();
    TestRejectsNullEmptyAndWrappingRanges();
    TestRangeInsideOneRegion();
    TestRangeRunningPastTheLastRegion();
    TestRangeAcrossRegionsChecksEach();
    TestUncommittedAndGuardedRegionsAreRefused();
    TestZeroSizedRegionDoesNotLoop();
    if (OpenShimTest::FailureCount() == 0)
        std::printf("memory_access_tests: all passed\n");
    return OpenShimTest::ExitCode();
}
