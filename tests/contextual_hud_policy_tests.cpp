#include "contextual_hud_policy.h"
#include "test_check.h"
#include <limits>
using namespace BZROpenShim::ContextualHud;
using OpenShimTest::Check;
int main()
{
    Settings settings;
    Check(!settings.Active(), "all shipped groups are disabled");
    GroupSettings fade{true,25,2500,500};
    Activity activity;
    Check(activity.Opacity(fade,9000)==1, "missing observation fails fully visible");
    activity.Observe(5,1000);
    Check(activity.Opacity(fade,3500)==1, "new observation holds full opacity through the delay");
    Check(std::abs(activity.Opacity(fade,3750)-0.625f)<0.0001f, "halfway smooth fade respects idle opacity");
    Check(std::abs(activity.Opacity(fade,4000)-0.25f)<0.0001f, "fade reaches the configured floor");
    float previous=1;
    for(uint64_t now=3500;now<5000;now+=5)
    {
        float value=activity.Opacity(fade,now);
        Check(value<=previous && value>=0.25f,"idle fade is monotone and bounded");previous=value;
    }
    activity.Observe(5,6000);
    Check(activity.Opacity(fade,6000)==0.25f,"unchanged readings do not restart the hold");
    activity.Observe(6,6000);
    Check(activity.Opacity(fade,6000)==1,"relevant changes reveal immediately");
    Check(activity.Opacity(fade,5999)==1,"clock reversal fails visible");
    activity.Observe(6,5000);
    Check(activity.changedAt==5000,"observation recovers from a clock reversal");
    fade.fadeMs=0;fade.delayMs=0;
    Check(activity.Opacity(fade,5001)==0.25f,"instant fades use the idle opacity after the hold");
    fade.idlePercent=0;
    Check(activity.Opacity(fade,5001)==0,"explicit hidden choice hides idle geometry");
    fade.enabled=false;
    Check(activity.Opacity(fade,5001)==1,"disabled group retains stock opacity");

    State state;
    std::array<uint64_t,kGroups> values{1,2,3};
    state.Observe(11,values,1000);
    state.Observe(11,values,5000);
    Check(state.groups[0].changedAt==1000,"stable weapon selection/loadout/ammo can fade");
    values[1]=99;state.Observe(11,values,6000);
    Check(state.groups[0].changedAt==1000 && state.groups[1].changedAt==6000 && state.groups[2].changedAt==1000,
        "scrap activity never reveals the other groups");
    values[2]=99;state.Observe(11,values,7000);
    Check(state.groups[1].changedAt==6000 && state.groups[2].changedAt==7000,"pilots have independent activity timing");
    state.Observe(12,values,8000);
    for(const auto& group:state.groups)Check(group.changedAt==8000,"player/team change reveals all groups");
    state.Observe(0,values,9000);
    Check(!state.owner && !state.groups[0].observed,"invalid snapshots discard the preceding player's state");
    state.Observe(12,values,10000);state.Reset();
    Check(!state.groups[0].observed,"mission/config reset removes fade history");

    // Commands are sampled inside their native renderer, after the safe-frame
    // driver samples the other groups. Unchanged active menus must remain visible.
    const size_t commands = static_cast<size_t>(Group::Commands);
    fade = {true,0,1000,500};
    state.Observe(20,values,1000,commands);
    Check(!state.groups[commands].observed,"safe-frame observations leave command history untouched");
    state.groups[commands].Observe(7,1000);
    Check(state.groups[commands].Opacity(fade,3000)==0,"idle command interface can fade completely away");
    state.groups[commands].Observe(7,3000,true);
    Check(state.groups[commands].Opacity(fade,3000)==1,"repeated command input reveals an unchanged menu");
    state.groups[commands].Observe(7,10000,true);
    state.Observe(20,values,10000,commands);
    Check(state.groups[commands].Opacity(fade,11000)==1,"an active menu refreshes the hold independently of other groups");
    state.groups[commands].Observe(7,11000);
    Check(state.groups[commands].Opacity(fade,11500)==0,"idle fade resumes after the final active frame");
    Check(state.groups[0].changedAt==1000,"command activity never reveals the weapon list");
    state.Observe(21,values,12000,commands);
    Check(!state.groups[commands].observed,"a new player invalidates render-sampled command history");

    Check(ScaleAlpha(0x804080FF,0.25f)==0x204080FF,"multiply native alpha while preserving RGB");
    Check(ScaleAlpha(0x004080FF,0.25f)==0x004080FF,"native transparency remains transparent");
    Check(ScaleAlpha(0x804080FF,1)==0x804080FF,"full opacity is byte identical");
    Check(ScaleAlpha(0x804080FF,0)==0x004080FF,"hidden leaves RGB intact");
    Check(ScaleAlpha(0x804080FF,std::numeric_limits<float>::quiet_NaN())==0x804080FF,
        "bad opacity fails visible");
}
