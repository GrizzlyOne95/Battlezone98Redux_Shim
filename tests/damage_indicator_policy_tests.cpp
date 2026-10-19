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
    pulses.Add(1000, 600, 1, {0,0,10}, 0.1f);
    Check(pulses.entries[0].victim == 1 && pulses.entries[0].severity == 0.5f, "captured loss scales severity");
    pulses.Add(1100, 600, 1, {0,0,20}, 0.2f);
    Check(pulses.entries[0].pulse.started == 1100 && pulses.entries[1].victim == 0, "same bearing refreshes one arc");
    pulses.Add(1100, 600, 1, {10,0,0}, 0.01f);
    Check(pulses.entries[1].victim == 1, "different direction remains independently visible");
    Check(pulses.entries[0].pulse.Strength(1700,600) == 0, "expiry removes the arc");
    pulses.Reset(); Check(pulses.entries[0].victim == 0, "mission/config reset clears captured sources");
    for (int i = 0; i < 20; ++i)
        pulses.Add(1000 + i, 600, 1, {std::sin(i * 0.5f), 0, std::cos(i * 0.5f)}, 0.1f);
    for (const auto& entry : pulses.entries)
        Check(entry.victim == 1 && std::isfinite(entry.direction.x), "source burst stays bounded");

    DamageIndicatorSettings settings;
    Check(!settings.enabled, "default is disabled");
    const Rect clip{100,50,900,650,0};
    auto plan = MakeDamageIndicatorPlan(settings,500,350,1,1,clip,0,1,1);
    Check(plan.count == 32 && !plan.replacesStock, "arc preserves native reticle");
    for (size_t i = 0; i < plan.count; ++i)
        Check(plan.rects[i].bottom < 350, "front arc stays above aim point");
    const auto light = MakeDamageIndicatorPlan(settings,500,350,1,1,clip,0,1,0);
    Check((light.rects[light.count-1].color >> 24) < (plan.rects[plan.count-1].color >> 24), "severity affects alpha");
    for (float scale : {0.1f,0.5f,1.0f,2.0f,8.0f})
        for (float a : {0.0f,1.57f,3.14f,-1.57f})
            for (const auto point : {std::array<int,2>{100,50},{899,649},{500,350}})
            {
                plan = MakeDamageIndicatorPlan(settings,point[0],point[1],scale,scale,clip,a,1,0.5f);
                Check(plan.count <= 32, "geometry remains bounded even when clipped");
                for (size_t i = 0; i < plan.count; ++i)
                {
                    const auto& r = plan.rects[i];
                    Check(r.left >= clip.left && r.top >= clip.top && r.right < clip.right && r.bottom < clip.bottom &&
                        r.left <= r.right && r.top <= r.bottom, "edge arcs stay inside current pane");
                }
            }
    Check(MakeDamageIndicatorPlan(settings,500,350,1,1,clip,0,0,1).count == 0, "expired arc draws nothing");
    Check(MakeDamageIndicatorPlan(settings,500,350,9,1,clip,0,1,1).count == 0, "bad scale fails closed");
    Check(MakeDamageIndicatorPlan(settings,99,350,1,1,clip,0,1,1).count == 0, "off-pane aim fails closed");
    Check(MakeDamageIndicatorPlan(settings,500,350,1,1,clip,std::numeric_limits<float>::infinity(),1,1).count == 0,
        "bad bearing fails closed");
}
