#pragma once

// Page-protection checks made before OpenShim reads, writes or calls through
// a pointer it got from the engine.
//
// Seven files used to carry their own copy (audit P2-3), and the copies had
// drifted: one accepted guard pages as executable, one treated an execute-only
// page as readable, one refused a range that crossed two readable regions.
// The rules below are the strictest of those copies, and the one exception
// (ranges may span regions, as long as every region passes) is documented at
// RangeAllows.
//
// The predicates and the region walk are free of Windows calls: the region
// query is a parameter, so the tests can drive it with a fake address space.
// The VirtualQuery wrappers at the bottom are Windows-only.

#include <cstddef>
#include <cstdint>

#ifdef _WIN32
#include <windows.h>
#endif

namespace BZROpenShim
{
namespace MemoryAccess
{
    // The winnt.h values, spelled out so the pure part builds without
    // windows.h. The static_asserts below pin them to the SDK on Windows.
    namespace Protect
    {
        constexpr uint32_t NoAccess = 0x01;
        constexpr uint32_t ReadOnly = 0x02;
        constexpr uint32_t ReadWrite = 0x04;
        constexpr uint32_t WriteCopy = 0x08;
        constexpr uint32_t Execute = 0x10;
        constexpr uint32_t ExecuteRead = 0x20;
        constexpr uint32_t ExecuteReadWrite = 0x40;
        constexpr uint32_t ExecuteWriteCopy = 0x80;
        constexpr uint32_t Guard = 0x100;
    }

    constexpr uint32_t kMemCommit = 0x1000;

    enum class Access
    {
        Read,
        Write,   // implies Read: every writable protection is also readable
        Execute,
    };

    // Whether a page with this protection allows the access. A guard page or a
    // no-access page allows nothing; the other modifier bits (no-cache,
    // write-combine) are ignored.
    constexpr bool ProtectionAllows(uint32_t protect, Access access)
    {
        if ((protect & (Protect::Guard | Protect::NoAccess)) != 0)
            return false;

        const uint32_t base = protect & 0xFFu;
        switch (access)
        {
        case Access::Read:
            return base == Protect::ReadOnly || base == Protect::ReadWrite ||
                base == Protect::WriteCopy || base == Protect::ExecuteRead ||
                base == Protect::ExecuteReadWrite || base == Protect::ExecuteWriteCopy;
        case Access::Write:
            return base == Protect::ReadWrite || base == Protect::WriteCopy ||
                base == Protect::ExecuteReadWrite || base == Protect::ExecuteWriteCopy;
        case Access::Execute:
            return base == Protect::Execute || base == Protect::ExecuteRead ||
                base == Protect::ExecuteReadWrite || base == Protect::ExecuteWriteCopy;
        }
        return false;
    }

    // One VirtualQuery answer, reduced to the fields the checks use.
    struct Region
    {
        uintptr_t base = 0;
        size_t size = 0;
        uint32_t state = 0;
        uint32_t protect = 0;
    };

    // True when every byte of [start, start + length) sits in committed memory
    // that allows the access. The range may cross region boundaries; each
    // region it touches is checked. A null start, an empty range, a range that
    // wraps the address space, or a failed query is refused.
    //
    // `query(address, region)` fills the region containing `address` and
    // returns false when there is none.
    template <typename Query>
    bool RangeAllows(uintptr_t start, size_t length, Access access, Query&& query)
    {
        if (start == 0 || length == 0)
            return false;

        const uintptr_t end = start + length;
        if (end < start)
            return false;

        uintptr_t cursor = start;
        while (cursor < end)
        {
            Region region{};
            if (!query(cursor, region))
                return false;
            if (region.state != kMemCommit || !ProtectionAllows(region.protect, access))
                return false;

            const uintptr_t regionEnd = region.base + region.size;
            if (regionEnd <= cursor)
                return false;
            cursor = regionEnd;
        }
        return true;
    }

#ifdef _WIN32
    static_assert(Protect::NoAccess == PAGE_NOACCESS, "winnt.h value");
    static_assert(Protect::ReadOnly == PAGE_READONLY, "winnt.h value");
    static_assert(Protect::ReadWrite == PAGE_READWRITE, "winnt.h value");
    static_assert(Protect::WriteCopy == PAGE_WRITECOPY, "winnt.h value");
    static_assert(Protect::Execute == PAGE_EXECUTE, "winnt.h value");
    static_assert(Protect::ExecuteRead == PAGE_EXECUTE_READ, "winnt.h value");
    static_assert(Protect::ExecuteReadWrite == PAGE_EXECUTE_READWRITE, "winnt.h value");
    static_assert(Protect::ExecuteWriteCopy == PAGE_EXECUTE_WRITECOPY, "winnt.h value");
    static_assert(Protect::Guard == PAGE_GUARD, "winnt.h value");
    static_assert(kMemCommit == MEM_COMMIT, "winnt.h value");

    // These hold no objects with destructors, so they may be called from a
    // function that uses __try.
    inline bool QueryRegion(uintptr_t address, Region& out) noexcept
    {
        MEMORY_BASIC_INFORMATION mbi{};
        if (VirtualQuery(reinterpret_cast<const void*>(address), &mbi, sizeof(mbi)) != sizeof(mbi))
            return false;
        out.base = reinterpret_cast<uintptr_t>(mbi.BaseAddress);
        out.size = mbi.RegionSize;
        out.state = mbi.State;
        out.protect = mbi.Protect;
        return true;
    }

    inline bool RangeAllows(const void* address, size_t length, Access access) noexcept
    {
        return RangeAllows(reinterpret_cast<uintptr_t>(address), length, access,
                           [](uintptr_t a, Region& r) { return QueryRegion(a, r); });
    }

    inline bool IsReadable(const void* address, size_t length) noexcept
    {
        return RangeAllows(address, length, Access::Read);
    }

    inline bool IsWritable(const void* address, size_t length) noexcept
    {
        return RangeAllows(address, length, Access::Write);
    }

    // Whether a call to `address` would land in executable, committed memory.
    inline bool IsExecutable(const void* address) noexcept
    {
        return RangeAllows(address, 1, Access::Execute);
    }
#endif
}
}
