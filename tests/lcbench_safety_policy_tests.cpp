#include "lcbench_safety_policy.h"

#include <cstdio>

using namespace BZROpenShim;

namespace
{
    int g_Failures = 0;

    void Check(bool condition, const char* message)
    {
        if (condition)
            return;
        std::fprintf(stderr, "FAIL: %s\n", message);
        ++g_Failures;
    }
}

int main()
{
    using namespace LcbenchSafetyPolicy;

    Check(SelectedMaskForMissingCarrier() == 0u,
          "a missing pilot carrier must behave as no selected weapon");

    Check(AllowExplicitAttackTarget(true, 2, false),
          "stock enemy targets must remain eligible while the option is off");
    Check(!AllowExplicitAttackTarget(false, 0, false),
          "team 0 must retain stock exclusion while the option is off");
    Check(AllowExplicitAttackTarget(false, 0, true),
          "team 0 must become eligible when the option is on");
    Check(!AllowExplicitAttackTarget(false, 1, true),
          "the option must not make friendly non-neutral teams attackable");
    Check(AllowExplicitAttackTarget(true, 0, true),
          "an existing stock-eligible result must never be suppressed");

    std::printf("lcbench safety policy tests: %d failure(s)\n", g_Failures);
    return g_Failures == 0 ? 0 : 1;
}
