#include "hud_ownership_policy.h"
#include "test_check.h"
#include <initializer_list>
using namespace BZROpenShim::HudOwnership;
using OpenShimTest::Check;
int main()
{
    // Wire ABI: independently releasable presentation; native input stays owned.
    static_assert(Hull==1 && Ammo==2 && Weapons==4 && Scrap==8 && Radar==16 && Commands==32);
    for (uint32_t mask=0;mask<=All;++mask)
    {
        Check(Valid(mask),"all defined ownership combinations are valid");
        for (auto area:{Hull,Ammo,Weapons,Scrap,Radar,Commands})
        {
            const auto acquired=mask|area;
            Check(Claimed(acquired,area),"claim selects the requested area");
            const auto released=acquired&~area;
            Check(!Claimed(released,area),"release restores the requested area");
            Check((released&~area)==(mask&~area),"release preserves other owners");
        }
    }
    Check(!Valid(64) && !Valid(~0u),"unknown ownership bits are rejected");
    Check(!Claimed(All,0),"zero is not a presentation area");
    return OpenShimTest::ExitCode();
}
