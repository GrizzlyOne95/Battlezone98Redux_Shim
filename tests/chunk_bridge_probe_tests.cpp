#include "chunk_bridge_probe.h"
#include "test_check.h"
#include <cstdio>
#include <cstring>
#include <initializer_list>

using BZROpenShim::ChunkBridgeProbe::TryReadOgreLinks;

namespace
{
    LONG g_accessViolations = 0;

    LONG WINAPI CountAccessViolations(EXCEPTION_POINTERS* pointers)
    {
        if (pointers->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION ||
            pointers->ExceptionRecord->ExceptionCode == EXCEPTION_GUARD_PAGE)
        {
            ++g_accessViolations;
        }
        return EXCEPTION_CONTINUE_SEARCH;
    }

    void CheckRejected(const void* candidate)
    {
        void* entity = reinterpret_cast<void*>(1);
        void* light = reinterpret_cast<void*>(2);
        CHECK(!TryReadOgreLinks(candidate, entity, light));
        CHECK(entity == nullptr);
        CHECK(light == nullptr);
        CHECK(g_accessViolations == 0);
    }
}

int main()
{
    SYSTEM_INFO info{};
    GetSystemInfo(&info);
    const size_t pageSize = info.dwPageSize;
    auto* pages = static_cast<uint8_t*>(VirtualAlloc(
        nullptr, pageSize * 2, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
    OpenShimTest::Require(pages != nullptr, "allocate bridge fixture");
    PVOID handler = AddVectoredExceptionHandler(1, CountAccessViolations);
    OpenShimTest::Require(handler != nullptr, "install exception observer");

    void* expectedEntity = pages + 0x100;
    void* expectedLight = pages + 0x200;
    std::memcpy(pages + 0x94, &expectedEntity, sizeof(void*));
    std::memcpy(pages + 0xA8, &expectedLight, sizeof(void*));
    void* entity = nullptr;
    void* light = nullptr;
    CHECK(TryReadOgreLinks(pages, entity, light));
    CHECK(entity == expectedEntity);
    CHECK(light == expectedLight);

    CheckRejected(nullptr);
    CheckRejected(reinterpret_cast<void*>(0x18));
    CheckRejected(pages + 1);
    // Recorded values must be declined whenever those low addresses are
    // unmapped; do not assume another process's address-space layout.
    for (uintptr_t candidate : {uintptr_t{0x00080000}, uintptr_t{0x000E0000}})
    {
        if (!BZROpenShim::MemoryAccess::IsReadable(
                reinterpret_cast<void*>(candidate), 0xA8 + sizeof(void*)))
        {
            CheckRejected(reinterpret_cast<void*>(candidate));
        }
    }

    DWORD oldProtect = 0;
    OpenShimTest::Require(VirtualProtect(pages + pageSize, pageSize, PAGE_NOACCESS,
        &oldProtect) != 0, "protect second page");
    // Entity is readable but the light crosses into the inaccessible page.
    // Neither output may escape and no first-chance exception should occur.
    CheckRejected(pages + pageSize - 0xA8);
    CheckRejected(pages + pageSize);

    OpenShimTest::Require(VirtualProtect(pages, pageSize, PAGE_READWRITE | PAGE_GUARD,
        &oldProtect) != 0, "guard first page");
    CheckRejected(pages);
    MEMORY_BASIC_INFORMATION region{};
    CHECK(VirtualQuery(pages, &region, sizeof(region)) == sizeof(region));
    CHECK((region.Protect & PAGE_GUARD) != 0);

    OpenShimTest::Require(VirtualFree(pages, pageSize * 2, MEM_DECOMMIT) != 0,
        "decommit fixture");
    CheckRejected(pages);
    CHECK(RemoveVectoredExceptionHandler(handler) != 0);
    CHECK(VirtualFree(pages, 0, MEM_RELEASE) != 0);
    if (OpenShimTest::FailureCount() == 0)
        std::printf("chunk_bridge_probe_tests: all passed without first-chance exceptions\n");
    return OpenShimTest::ExitCode();
}
