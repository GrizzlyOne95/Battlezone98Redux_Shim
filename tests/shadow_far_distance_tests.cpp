// Regression tests for the shadow far distance policy.
//
// The behaviour worth pinning is the default. This shipped for weeks as an
// environment-variable experiment that was dormant unless somebody set it,
// and the whole point of the change is that absent now means "apply the fix"
// -- so a test that only exercised explicit values would pass just as loudly
// if the default silently reverted to dormant.
//
// The rest pins the ways to ask for stock back, and the parser's independence
// from the process locale.

#include "shadow_far_distance.h"

#include <cstdio>
#include <initializer_list>
#include <cstdlib>
#include <clocale>

namespace
{
    using namespace openshim::shadow;

    int g_failures = 0;

    void Require(bool condition, const char* message)
    {
        if (!condition)
        {
            std::fprintf(stderr, "shadow_far_distance_tests: %s\n", message);
            ++g_failures;
        }
    }

    void RequireDecision(const char* configured,
                         float expectedDistance,
                         FarDistanceSource expectedSource,
                         const char* message)
    {
        const FarDistanceDecision actual = DecideFarDistance(configured);
        if (actual.distance != expectedDistance || actual.source != expectedSource)
        {
            std::fprintf(stderr,
                "shadow_far_distance_tests: %s (input=%s actual=%.3f/%s "
                "expected=%.3f/%s)\n",
                message,
                configured ? configured : "<null>",
                static_cast<double>(actual.distance), SourceName(actual.source),
                static_cast<double>(expectedDistance), SourceName(expectedSource));
            ++g_failures;
        }
    }

    // The one that matters: nothing configured must apply the fix. If this
    // ever returns 0 again the terminator is back and nothing else here
    // would notice.
    void TestDefaultAppliesTheFix()
    {
        RequireDecision(nullptr, kOuterSplitDistance, FarDistanceSource::Default,
                        "absent configuration must default to the outer split");
        RequireDecision("", kOuterSplitDistance, FarDistanceSource::Default,
                        "empty configuration must default to the outer split");

        const FarDistanceDecision decision = DecideFarDistance(nullptr);
        Require(decision.ShouldOverride(),
                "the default must actually re-issue the setter");
        Require(kOuterSplitDistance > kStockFarDistance,
                "the default must be further than the stock clip, or it fixes nothing");
    }

    void TestOptOutRestoresStock()
    {
        for (const char* text : { "stock", "STOCK", "off", "Off", "0" })
            RequireDecision(text, 0.0f, FarDistanceSource::OptedOut,
                            "explicit opt-out must leave the stock clip alone");

        // Asking for the stock number is a request for stock, not a typo.
        RequireDecision("128", 0.0f, FarDistanceSource::OptedOut,
                        "the stock distance must be treated as an opt-out");
        RequireDecision("128.0", 0.0f, FarDistanceSource::OptedOut,
                        "the stock distance must be treated as an opt-out");

        Require(!DecideFarDistance("stock").ShouldOverride(),
                "an opt-out must not re-issue the setter");
    }

    void TestExplicitDistances()
    {
        RequireDecision("256", 256.0f, FarDistanceSource::Configured,
                        "an explicit outer-split request must be honoured");
        RequireDecision("384.5", 384.5f, FarDistanceSource::Configured,
                        "a fractional distance must be honoured");
        RequireDecision("  512  ", 512.0f, FarDistanceSource::Configured,
                        "surrounding whitespace must be tolerated");
        RequireDecision("16", 16.0f, FarDistanceSource::Configured,
                        "the lower bound must be inclusive");
        RequireDecision("4096", 4096.0f, FarDistanceSource::Configured,
                        "the upper bound must be inclusive");
    }

    void TestRejectsUnusableValues()
    {
        for (const char* text : { "15.9", "4096.1", "-256", "nonsense",
                                  "256abc", "abc256", "." })
            RequireDecision(text, 0.0f, FarDistanceSource::Rejected,
                            "an unusable value must be rejected, not guessed at");

        // A rejected value must fail closed to stock, never to the default:
        // silently applying the fix after refusing what the user asked for
        // would make the refusal invisible.
        Require(!DecideFarDistance("nonsense").ShouldOverride(),
                "a rejected value must not fall through to the default");
    }

    // strtof would read "256,5" as 256 under a comma-decimal locale and as a
    // parse failure under a period-decimal one. The parser here is hand-rolled
    // precisely so the answer does not depend on the user's Windows region.
    void TestLocaleIndependence()
    {
        const char* const locales[] = { "C", "de-DE", "fr-FR", "" };
        for (const char* locale : locales)
        {
            if (std::setlocale(LC_NUMERIC, locale) == nullptr)
                continue;  // not installed on this host; the others still run
            RequireDecision("384.5", 384.5f, FarDistanceSource::Configured,
                            "a period decimal must parse in every locale");
            RequireDecision("384,5", 0.0f, FarDistanceSource::Rejected,
                            "a comma decimal must be rejected in every locale");
        }
        std::setlocale(LC_NUMERIC, "C");
    }
}

int main()
{
    TestDefaultAppliesTheFix();
    std::printf("TestDefaultAppliesTheFix\n");
    TestOptOutRestoresStock();
    std::printf("TestOptOutRestoresStock\n");
    TestExplicitDistances();
    std::printf("TestExplicitDistances\n");
    TestRejectsUnusableValues();
    std::printf("TestRejectsUnusableValues\n");
    TestLocaleIndependence();
    std::printf("TestLocaleIndependence\n");

    if (g_failures != 0)
    {
        std::fprintf(stderr, "shadow_far_distance_tests: %d failure(s)\n", g_failures);
        return 1;
    }
    std::printf("\nshadow_far_distance_tests passed\n");
    return 0;
}
