// diagnostic_output_cap_tests.cpp
// Host tests for include/diagnostic_output_cap.h: the size caps on the Ogre
// profiler CSV and the native CPU sampler file (audit P2-10). Built as C++14
// because the Ogre profiler translation unit that includes the header is.

#include "diagnostic_output_cap.h"

#include <cstdint>
#include <cstdio>

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

using namespace BZROpenShim::DiagnosticOutputCap;

void TestParse()
{
    uint32_t mib = 12345;
    CHECK(!TryParseCapMiB(nullptr, mib));
    CHECK(!TryParseCapMiB("", mib));
    CHECK(!TryParseCapMiB("   ", mib));
    CHECK(!TryParseCapMiB("-1", mib));
    CHECK(!TryParseCapMiB("+5", mib));
    CHECK(!TryParseCapMiB("1.5", mib));
    CHECK(!TryParseCapMiB("64MB", mib));
    CHECK(!TryParseCapMiB("abc", mib));
    CHECK(!TryParseCapMiB("6 4", mib));
    CHECK(mib == 12345); // untouched on failure

    CHECK(TryParseCapMiB("0", mib) && mib == 0);
    CHECK(TryParseCapMiB("64", mib) && mib == 64);
    CHECK(TryParseCapMiB("  128 \r\n", mib) && mib == 128);
    CHECK(TryParseCapMiB("0064", mib) && mib == 64);
    CHECK(TryParseCapMiB("1048576", mib) && mib == kMaxCapMiB);
    CHECK(TryParseCapMiB("1048577", mib) && mib == kMaxCapMiB);
    CHECK(TryParseCapMiB("99999999999999999999999", mib) && mib == kMaxCapMiB);
}

void TestResolve()
{
    CHECK(CapBytesFromMiB(0) == 0);
    CHECK(CapBytesFromMiB(1) == 1048576ull);
    CHECK(CapBytesFromMiB(kMaxCapMiB) == 1099511627776ull);

    // Defaults.
    CHECK(ResolveCapBytes(nullptr, nullptr, kDefaultOgreCsvCapMiB) == 64ull * kBytesPerMiB);
    CHECK(ResolveCapBytes(nullptr, nullptr, kDefaultCpuSamplerCapMiB) == 256ull * kBytesPerMiB);

    // Priority: first valid wins; invalid falls through.
    CHECK(ResolveCapBytes("8", "16", 64) == 8ull * kBytesPerMiB);
    CHECK(ResolveCapBytes(nullptr, "16", 64) == 16ull * kBytesPerMiB);
    CHECK(ResolveCapBytes("junk", "16", 64) == 16ull * kBytesPerMiB);
    CHECK(ResolveCapBytes("junk", "junk", 64) == 64ull * kBytesPerMiB);

    // 0 is an explicit "no cap", not a fall-through.
    CHECK(ResolveCapBytes("0", "16", 64) == 0);
}

void TestReached()
{
    const uint64_t cap = 64ull * kBytesPerMiB;
    CHECK(!ReachedCap(0, cap));
    CHECK(!ReachedCap(cap - 1, cap));
    CHECK(ReachedCap(cap, cap));
    CHECK(ReachedCap(cap + 1, cap));

    // No cap never triggers.
    CHECK(!ReachedCap(0, 0));
    CHECK(!ReachedCap(UINT64_MAX, 0));
}
} // namespace

int main()
{
    TestParse();
    TestResolve();
    TestReached();

    if (g_failures == 0)
        std::printf("diagnostic_output_cap_tests: all passed\n");
    return g_failures == 0 ? 0 : 1;
}
