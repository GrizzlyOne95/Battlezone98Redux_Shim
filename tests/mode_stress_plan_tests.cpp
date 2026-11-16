// mode_stress_plan_tests.cpp
// The mode-transition stress driver's plan-file parser (include/mode_stress_plan.h).
#include "mode_stress_plan.h"

#include <cstdio>
#include <string>

namespace
{
    using namespace BZROpenShim::ModeStress;

    int g_failures = 0;
    void check(bool ok, const char* text)
    {
        if (!ok)
        {
            std::fprintf(stderr, "FAIL: %s\n", text);
            ++g_failures;
        }
    }

    void TestFullPlan()
    {
        const ParseResult r = ParsePlan(
            "# default plan\r\n"
            "shell 5\r\n"
            "mission misn03cr.bzn 90 cr_campaign   # trailing comment\r\n"
            "\r\n"
            "  ia crsetup.bzn 60\r\n"
            "mp_host dm01.bzn 30\r\n"
            "mission bd01cr.bzn 45\r\n"
            "loop 2\r\n");
        check(r.ok, "the full plan parses");
        check(r.plan.loops == 2, "loop count is read");
        check(r.plan.steps.size() == 5, "five steps, comments and blanks skipped");
        if (r.plan.steps.size() != 5)
            return;
        check(r.plan.steps[0].kind == StepKind::Shell && r.plan.steps[0].seconds == 5, "shell step");
        check(r.plan.steps[1].kind == StepKind::Mission && r.plan.steps[1].arg == "misn03cr.bzn" &&
                  r.plan.steps[1].seconds == 90 && r.plan.steps[1].campaign == "cr_campaign" &&
                  r.plan.steps[1].line == 3,
              "mission step keeps bzn, seconds, campaign and line");
        check(r.plan.steps[2].kind == StepKind::InstantAction && r.plan.steps[2].arg == "crsetup.bzn",
              "ia step with leading spaces");
        check(r.plan.steps[3].kind == StepKind::MpHost && r.plan.steps[3].arg == "dm01.bzn" &&
                  r.plan.steps[3].seconds == 30,
              "mp_host step keeps the map and seconds");
        check(r.plan.steps[4].campaign.empty(), "campaign is optional");
        check(std::string(KindName(StepKind::InstantAction)) == "ia", "kind names match the plan words");
    }

    void TestDefaults()
    {
        const ParseResult r = ParsePlan("ia a.bzn 1");
        check(r.ok && r.plan.loops == 1, "no loop line means one pass");
        check(ParsePlan("shell 0").ok, "a zero-second shell gap is allowed");
        check(ParsePlan("mission ABC.BZN 3600").ok, "upper-case extension and max seconds accepted");
        check(ParsePlan("mission a23456789ab.bzn 5").ok, "a 15-char name fits the engine buffer");
    }

    void ExpectError(const char* text, int line, const char* what)
    {
        const ParseResult r = ParsePlan(text);
        check(!r.ok, what);
        check(r.errorLine == line, what);
        check(!r.error.empty(), what);
        check(r.plan.steps.empty(), what);
    }

    void TestErrors()
    {
        ExpectError("", 0, "an empty plan is refused");
        ExpectError("# only comments\n\n", 0, "a comment-only plan is refused");
        ExpectError("shell 5\nfly away 3\n", 2, "an unknown kind is refused with its line");
        ExpectError("mission misn03cr 90\n", 1, "a bzn without .bzn is refused");
        ExpectError("mission a234567890ab.bzn 5\n", 1, "a 16-char name overflows the engine buffer");
        ExpectError("mission ../x.bzn 5\n", 1, "path characters are refused");
        ExpectError("ia a.bzn 0\n", 1, "zero seconds is refused for a load");
        ExpectError("ia a.bzn 3601\n", 1, "over an hour is refused");
        ExpectError("ia a.bzn 5 extra\n", 1, "ia takes no campaign");
        ExpectError("ia a.bzn -5\n", 1, "negative seconds are refused");
        ExpectError("ia a.bzn 5x\n", 1, "trailing junk in seconds is refused");
        ExpectError("mission a.bzn 5 bad/id\n", 1, "a campaign id with a slash is refused");
        ExpectError("mp_host dm01 5\n", 1, "mp_host needs a .bzn map");
        ExpectError("mp_host dm01.bzn 0\n", 1, "mp_host refuses zero seconds");
        ExpectError("mp_host dm01.bzn\n", 1, "mp_host needs seconds");
        ExpectError("mp_host dm01.bzn 5 cr_campaign\n", 1, "mp_host takes no campaign");
        ExpectError("mp_join 127.0.0.1:17770 5\n", 1, "the old mp_join kind is gone");
        ExpectError("shell\n", 1, "shell needs seconds");
        ExpectError("shell 1\nloop 2\nloop 3\n", 3, "loop twice is refused");
        ExpectError("shell 1\nloop 0\n", 2, "loop 0 is refused");
        ExpectError("shell 1\nloop 101\n", 2, "loop over 100 is refused");

        std::string many;
        for (int i = 0; i < 65; ++i)
            many += "shell 1\n";
        ExpectError(many.c_str(), 65, "more than 64 steps is refused");
    }
}

int main()
{
    TestFullPlan();
    TestDefaults();
    TestErrors();
    if (g_failures == 0)
    {
        std::printf("mode_stress_plan_tests: all checks passed\n");
        return 0;
    }
    std::printf("mode_stress_plan_tests: %d failure(s)\n", g_failures);
    return 1;
}
