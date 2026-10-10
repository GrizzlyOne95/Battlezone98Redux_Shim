#include "unit_damage_policy.h"
#include <cstdlib>
#include <limits>

int main()
{
    BZROpenShim::UnitDamage::Policy policy;
    auto check = [](bool value) { if (!value) std::abort(); };
    check(policy.Apply(0x1000, 123, 120) == 120);
    check(policy.Set(0x1000, 123, .75f));
    check(policy.Apply(0x1000, 123, 120) == 90); // 100 HP survives at 10
    check(policy.Apply(0x2000, 456, 120) == 120); // shared blast unchanged
    check(policy.Apply(0x1000, 124, 120) == 120); // recycled pool address
    check(policy.Apply(0x1000, 123, -20) == -20); // healing unchanged
    check(policy.Apply(0x1000, 123, 0) == 0);
    check(!policy.Set(0x1000, 123, -1));
    check(!policy.Set(0x1000, 123, 2));
    check(!policy.Set(0x1000, 123, std::numeric_limits<float>::quiet_NaN()));
    check(!policy.Set(0, 123, .5f));
    check(!policy.Set(0x1000, 0, .5f));
    check(policy.Get(0x1000, 123) == .75f); // rejected updates leave it intact
    check(policy.Set(0x1000, 124, 0));
    check(policy.Apply(0x1000, 124, 120) == 0);
    policy.Clear(123);
    check(policy.Get(0x1000, 124) == 0); // stale handle cannot clear new unit
    policy.Clear(124);
    check(policy.Empty());
    check(policy.Set(0x1000, 123, .75f));
    check(policy.Set(0x1000, 123, 1));
    check(policy.Empty());
    check(policy.Set(0x1000, 123, .5f));
    policy.Reset();
    check(policy.Apply(0x1000, 123, 120) == 120);
}
