#include "lcbench_safety_policy.h"

#include <cstdio>
#include "test_check.h"

using OpenShimTest::Check;

using namespace BZROpenShim;


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

    std::printf("lcbench safety policy tests: %d failure(s)\n", OpenShimTest::FailureCount());
    return OpenShimTest::ExitCode();
}
