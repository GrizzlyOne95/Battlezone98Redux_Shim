#include "faction_vfx_setting.h"
#include "test_check.h"

using BZROpenShim::FactionVfx::Resolve;
using BZROpenShim::FactionVfx::Tri;
using OpenShimTest::Check;

int main()
{
    const Tri absent{};
    const Tri on{ true, true };
    const Tri off{ true, false };

    Check(!Resolve(absent, absent, absent), "nothing set is off");
    Check(Resolve(on, absent, absent), "new key on");
    Check(!Resolve(off, absent, absent), "new key off");
    Check(Resolve(absent, on, absent), "absent new key: JetFlames on enables both features");
    Check(Resolve(absent, absent, on), "absent new key: FactionConstructionBlobs on enables both features");
    Check(Resolve(absent, off, on) && Resolve(absent, on, off), "either legacy key on wins");
    Check(!Resolve(absent, off, off), "both legacy keys off");
    Check(!Resolve(off, on, on), "present new key off beats legacy keys on");
    Check(Resolve(on, off, off), "present new key on beats legacy keys off");
    return OpenShimTest::ExitCode();
}
