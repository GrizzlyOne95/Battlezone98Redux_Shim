#include "dns_family_policy.h"
#include "test_check.h"
using namespace BZROpenShim::DnsFamilyPolicy;

static void ForceIPv4Cases()
{
    CHECK(ShouldForceIPv4(true, true, true, false));
    CHECK(!ShouldForceIPv4(false, true, true, false));   // option off
    CHECK(!ShouldForceIPv4(true, false, true, false));   // not a BZRNet name
    CHECK(!ShouldForceIPv4(true, true, false, false));   // caller already picked a family
    CHECK(!ShouldForceIPv4(true, true, true, true));     // IPv6 literal redirect
}

static void IPv6LiteralCases()
{
    CHECK(IsIPv6Literal("::1"));
    CHECK(IsIPv6Literal("fe80::1%3"));
    CHECK(!IsIPv6Literal("68.183.35.188"));
    CHECK(!IsIPv6Literal("battlezone98mp.webdev.rebellion.co.uk"));
    CHECK(!IsIPv6Literal(""));
    CHECK(!IsIPv6Literal(nullptr));
}

static void RetryCases()
{
    CHECK(ShouldRetryWithOriginal(kEaiNoName, 0));
    CHECK(ShouldRetryWithOriginal(kEaiNoData, 0));  // AAAA-only custom host
    CHECK(ShouldRetryWithOriginal(0, 0));
    CHECK(!ShouldRetryWithOriginal(0, 1));
    CHECK(!ShouldRetryWithOriginal(11002, 0));  // WSATRY_AGAIN: no retry
    CHECK(!ShouldRetryWithOriginal(10093, 0));  // WSANOTINITIALISED
}

static void StallCases()
{
    CHECK(TestStallApplies(8000, true, kAfUnspec));
    CHECK(!TestStallApplies(8000, true, kAfInet));   // forced IPv4 skips the stall
    CHECK(!TestStallApplies(8000, false, kAfUnspec));
    CHECK(!TestStallApplies(0, true, kAfUnspec));
    CHECK(ClampTestStallMs(0) == 0);
    CHECK(ClampTestStallMs(8000) == 8000);
    CHECK(ClampTestStallMs(15000) == 15000);
    CHECK(ClampTestStallMs(15001) == kMaxTestStallMs);
    CHECK(ClampTestStallMs(0xFFFFFFFFu) == kMaxTestStallMs);
}

static void LogBudgetCases()
{
    LookupLogBudget budget;
    for (unsigned i = 0; i < LookupLogBudget::kFirst; ++i)
        CHECK(budget.ShouldLog(kEaiNoName, 0, 0));
    CHECK(!budget.ShouldLog(kEaiNoName, 0, 0));      // repeats go quiet
    CHECK(!budget.ShouldLog(kEaiNoName, 0, 0));
    CHECK(budget.ShouldLog(0, 1, 0));                // rc changed
    CHECK(!budget.ShouldLog(0, 1, 0));
    CHECK(budget.ShouldLog(0, 1, 1));                // families changed
    CHECK(!budget.ShouldLog(0, 1, 1));
}

int main()
{
    ForceIPv4Cases();
    IPv6LiteralCases();
    RetryCases();
    StallCases();
    LogBudgetCases();
    return OpenShimTest::ExitCode();
}
