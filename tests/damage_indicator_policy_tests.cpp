#include "damage_indicator_policy.h"
#include "test_check.h"
#include <limits>
using namespace BZROpenShim::HudFeedback;
using OpenShimTest::Check;

int main()
{
    DamageSample sample{1,2,1.0f,0.9f,true,false,true,true};
    Check(ConfirmsIncoming(sample, true), "other weapon damages local victim");
    Check(!ConfirmsHit(sample), "incoming AI damage never confirms an outgoing hit");
    Check(!ConfirmsIncoming(sample, false), "another victim does not qualify");
    auto bad = sample; bad.after = bad.before;
    Check(!ConfirmsIncoming(bad, true), "immunity does not pulse");
    bad.after = 1.1f; Check(!ConfirmsIncoming(bad, true), "healing does not pulse");
    bad = sample; bad.attacker = bad.victim; Check(!ConfirmsIncoming(bad, true), "self damage excluded");
    bad = sample; bad.weaponSource = false; Check(!ConfirmsIncoming(bad, true), "environment excluded");
    bad = sample; bad.sameLifetime = false; Check(!ConfirmsIncoming(bad, true), "stale victim excluded");
    bad = sample; bad.singlePlayer = false; Check(!ConfirmsIncoming(bad, true), "multiplayer excluded");
    bad = sample; bad.before = 0; Check(!ConfirmsIncoming(bad, true), "dead victim excluded");
    bad = sample; bad.after = -1; Check(ConfirmsIncoming(bad, true), "lethal damage accepted until identity changes");
    bad.after = std::numeric_limits<float>::quiet_NaN();
    Check(!ConfirmsIncoming(bad, true), "nonfinite health excluded");

    const std::array<float, 9> identity{1,0,0,0,1,0,0,0,1};
    float angle = 0;
    Check(ViewBearing({0,0,100}, identity, angle) && std::abs(angle) < 0.001f, "front points up");
    Check(ViewBearing({100,0,0}, identity, angle) && std::abs(angle - 1.5707963f) < 0.001f, "right points right");
    Check(ViewBearing({0,0,-100}, identity, angle) && std::abs(std::abs(angle) - 3.1415926f) < 0.001f, "rear points down");
    Check(ViewBearing({-100,0,0}, identity, angle) && angle < -1.57f, "left points left");
    const std::array<float, 9> facingRight{0,0,1,0,1,0,-1,0,0};
    Check(ViewBearing({100,0,0}, facingRight, angle) && std::abs(angle) < 0.001f, "turning right rotates the world source to front");
    Check(!ViewBearing({0,100,0}, identity, angle), "vertical-only source has no invented horizontal bearing");
    Check(!ViewBearing({}, identity, angle), "coincident source excluded");
    auto corrupt = identity; corrupt[0] = 0;
    Check(!ViewBearing({1,0,0}, corrupt, angle), "uninitialized camera excluded");
    corrupt = identity; corrupt[3] = 1;
    Check(!ViewBearing({1,0,0}, corrupt, angle), "nonorthogonal camera excluded");

    IncomingPulses pulses;
    pulses.Add(1000, 600, 1, 2, {0,0,10}, 0.1f);
    Check(pulses.entries[0].victim == 1 && pulses.entries[0].severity == 0.5f, "captured loss scales severity");
    pulses.Add(1100, 600, 1, 2, {0,0,20}, 0.2f);
    Check(pulses.entries[0].pulse.started == 1100 && pulses.entries[1].victim == 0, "same bearing refreshes one arc");
    pulses.Add(1100, 600, 1, 3, {10,0,0}, 0.01f);
    Check(pulses.entries[1].victim == 1, "different direction remains independently visible");
    Check(pulses.entries[0].pulse.Strength(1700,600) == 0, "expiry removes the arc");
    pulses.Reset(); Check(pulses.entries[0].victim == 0, "mission/config reset clears captured sources");
    for (int i = 0; i < 20; ++i)
        pulses.Add(1000 + i, 600, 1, 100 + i, {std::sin(i * 0.5f), 0, std::cos(i * 0.5f)}, 0.1f);
    for (const auto& entry : pulses.entries)
        Check(entry.victim == 1 && std::isfinite(entry.direction.x), "source burst stays bounded");

    pulses.Reset();
    const auto groupsAt = [&](uint64_t now) { return GroupIncomingArcs(pulses, now, 600, 1, identity); };
    pulses.Add(1000,600,1,2,{0,0,10},0.1f);
    pulses.Add(1100,600,1,3,{1,0,10},0.05f);
    auto groups = groupsAt(1100);
    Check(groups.count == 1 && groups.entries[0].owners.count == 2, "two distinct attackers sharing a bearing get two ticks");
    pulses.Add(1200,600,1,2,{0,0,10},0.1f);
    groups = groupsAt(1200);
    Check(groups.count == 1 && groups.entries[0].owners.count == 2, "repeated damage and pellets never double count an attacker");
    groups = groupsAt(1750);
    Check(groups.count == 1 && groups.entries[0].owners.count == 1, "refreshing one attacker does not extend another owner's tick");
    Check(groupsAt(1800).count == 0, "last owner expiry removes the arc");
    pulses.Add(1800,600,1,3,{1,0,10},0.05f);
    pulses.Add(1900,600,1,3,{10,0,0},0.05f);
    groups = groupsAt(1900);
    Check(groups.count == 1 && groups.entries[0].owners.count == 1 && groups.entries[0].angle > 1.5f,
        "an attacker moves its record to the new bearing instead of being counted twice");
    pulses.Add(1900,600,1,4,{0,0,10},0.05f);
    groups = groupsAt(1900);
    Check(groups.count == 2 && groups.entries[0].owners.count == 1 && groups.entries[1].owners.count == 1,
        "different directions display simultaneous independent counts");
    Check(GroupIncomingArcs(pulses,1900,600,9,identity).count == 0, "counts cannot cross player identities");
    pulses.Reset();
    pulses.Add(1000,600,1,2,{0.1f,0,-10},0.1f);
    pulses.Add(1000,600,1,3,{-0.1f,0,-10},0.1f);
    groups = groupsAt(1000);
    Check(groups.count == 1 && groups.entries[0].owners.count == 2, "nearby rear directions merge across angle wraparound");
    pulses.Reset();
    pulses.Add(1000,600,1,0x10002,{0,0,10},0.1f);
    pulses.Add(1000,600,1,0x20002,{0,0,10},0.1f);
    Check(groupsAt(1000).entries[0].owners.count == 2, "reused arena slot with a different generation is a distinct owner");
    pulses.Reset();
    for(int i=0;i<9;++i) pulses.Add(1000+i,600,1,100+i,{0,0,10},0.1f);
    groups = groupsAt(1010);
    Check(groups.count == 1 && groups.entries[0].owners.count == 8 && pulses.entries[0].attacker == 108,
        "overflow retains eight recent owners and replaces the oldest");
    const auto fullGroups = groups;
    pulses.Add(1100,600,1,0,{0,0,10},0.1f);
    pulses.Add(1100,600,1,1,{0,0,10},0.1f);
    Check(groupsAt(1100).entries[0].owners.count == 8, "invalid or self owners never enter the count");

    DamageIndicatorSettings settings;
    Check(!settings.enabled, "default is disabled");
    const Rect clip{100,50,900,650,0};
    auto plan = MakeDamageIndicatorPlan(settings,500,350,1,1,clip,0,1,1);
    Check(plan.count == 32 && !plan.replacesStock, "arc preserves native reticle");
    for (size_t i = 0; i < plan.count; ++i)
        Check(plan.rects[i].bottom < 350, "front arc stays above aim point");
    const auto light = MakeDamageIndicatorPlan(settings,500,350,1,1,clip,0,1,0);
    Check((light.rects[light.count-1].color >> 24) < (plan.rects[plan.count-1].color >> 24), "severity affects alpha");
    auto counted = MakeDamageIndicatorPlan(settings,500,350,1,1,clip,0,1,1,fullGroups.entries[0].owners);
    Check(counted.count == 96 && !counted.replacesStock, "eight owner ticks and the arc fit bounded drawing storage");
    OwnerTicks fading; fading.count=2; fading.strengths[0]=1; fading.strengths[1]=0.25f;
    counted = MakeDamageIndicatorPlan(settings,500,350,1,1,clip,0,1,1,fading);
    Check(counted.count == 48 && (counted.rects[40].color >> 24) > (counted.rects[44].color >> 24),
        "each owner's stroke fades independently");
    for (float scale : {0.1f,0.5f,1.0f,2.0f,8.0f})
        for (float a : {0.0f,1.57f,3.14f,-1.57f})
            for (const auto point : {std::array<int,2>{100,50},{899,649},{500,350}})
            {
                plan = MakeDamageIndicatorPlan(settings,point[0],point[1],scale,scale,clip,a,1,0.5f,fullGroups.entries[0].owners);
                Check(plan.count <= 96, "geometry and eight ticks remain bounded even when clipped");
                for (size_t i = 0; i < plan.count; ++i)
                {
                    const auto& r = plan.rects[i];
                    Check(r.left >= clip.left && r.top >= clip.top && r.right < clip.right && r.bottom < clip.bottom &&
                        r.left <= r.right && r.top <= r.bottom, "edge arcs stay inside current pane");
                }
            }
    {
        // A fresh hit kicks the arc outward and thicker; more attackers press harder.
        DamageIndicatorSettings dim = settings; dim.opacity = 50;
        const auto calm = MakeDamageIndicatorPlan(dim,500,350,1,1,clip,0,1,0.5f,{},0,1);
        const auto kicked = MakeDamageIndicatorPlan(dim,500,350,1,1,clip,0,1,0.5f,{},1,1);
        const auto pressed = MakeDamageIndicatorPlan(dim,500,350,1,1,clip,0,1,0.5f,{},0,4);
        const auto mobbed = MakeDamageIndicatorPlan(dim,500,350,1,1,clip,0,1,0.5f,{},0,99);
        const auto height = [](const DrawPlan& p) { return p.rects[16].bottom - p.rects[16].top; };
        Check(calm.count == 32 && kicked.count == 32 && pressed.count == 32, "kick and pressure add no geometry");
        Check(kicked.rects[16].top < calm.rects[16].top, "kick pushes the arc outward");
        Check(height(kicked) > height(calm) && height(pressed) > height(calm), "kick and pressure thicken the arc");
        Check((pressed.rects[16].color >> 24) > (calm.rects[16].color >> 24), "pressure brightens the arc");
        Check(height(mobbed) == height(pressed), "pressure caps at four attackers");
        Check(MakeDamageIndicatorPlan(dim,500,350,1,1,clip,0,1,0.5f,{},
              std::numeric_limits<float>::quiet_NaN(),1).rects[16].top == calm.rects[16].top, "bad kick is ignored");
        IncomingPulses two;
        two.Add(5000,600,1,2,{0,0,1},0.1f);
        two.Add(5300,600,1,3,{1,0,0},0.1f);
        const auto g = GroupIncomingArcs(two,5300,600,1,identity);
        Check(g.attackers == 2 && g.count == 2, "attackers are counted across directions");
        Check(g.entries[0].kick == 0 && g.entries[1].kick == 1, "only the fresh hit's arc kicks");
    }
    Check(MakeDamageIndicatorPlan(settings,500,350,1,1,clip,0,0,1).count == 0, "expired arc draws nothing");
    Check(MakeDamageIndicatorPlan(settings,500,350,9,1,clip,0,1,1).count == 0, "bad scale fails closed");
    Check(MakeDamageIndicatorPlan(settings,99,350,1,1,clip,0,1,1).count == 0, "off-pane aim fails closed");
    Check(MakeDamageIndicatorPlan(settings,500,350,1,1,clip,std::numeric_limits<float>::infinity(),1,1).count == 0,
        "bad bearing fails closed");
}
