#include "hud_feedback_policy.h"
#include "test_check.h"
#include <limits>

using namespace BZROpenShim::HudFeedback;
using OpenShimTest::Check;

int main()
{
    Check(ParseStyle("cRoSsDoT") == Style::CrossDot && ParseStyle("invalid") == Style::Stock,
          "style tokens are case-insensitive and unknown values preserve stock");
    Check(ParseColor("Amber") == 0xFFFFC040u && ParseColor("invalid") == 0xFFFFFFFFu,
          "color presets keep ARGB order and unknown values use white");
    Settings settings;
    Check(!settings.NeedsDraw(), "shipped defaults install no draw adapter");
    const Rect pane{100, 50, 900, 650, 0};
    auto plan = MakeDrawPlan(settings, 500, 350, 1, 1, pane, true, 0);
    Check(plan.count == 0 && !plan.replacesStock, "default keeps stock artwork even over a target");

    settings.style = Style::CrossDot;
    settings.outline = true;
    settings.color = ParseColor("Cyan");
    settings.opacity = 75;
    for (float scale : {0.5f, 1.0f, 2.0f, 4.0f})
    {
        plan = MakeDrawPlan(settings, 500, 350, scale, scale, pane, false, 0);
        Check(plan.count == 10 && plan.replacesStock, "cross/dot and outlines produce fixed bounded geometry");
        Check((plan.rects[1].color & 0xFFFFFFu) == 0x40FFFFu, "tint is not red/blue swapped");
        Check((plan.rects[1].color >> 24) == 191, "opacity applies to reticle vertices");
    }
    settings.reactive = true;
    const auto idle = MakeDrawPlan(settings, 500, 350, 1, 1, pane, false, 0);
    const auto contact = MakeDrawPlan(settings, 500, 350, 1, 1, pane, true, 0);
    Check(contact.count == idle.count + 4, "contact adds only the optional bracket pair");
    Check(contact.rects[1].right > idle.rects[1].right, "contact contracts the cross's center gap");
    settings.style = Style::Stock;
    plan = MakeDrawPlan(settings, 500, 350, 1, 1, pane, true, 1);
    Check(plan.count > 0 && !plan.replacesStock, "contact/hit feedback can overlay stock art");

    settings.style = Style::CrossDot;
    for (const auto& point : {std::array<int, 2>{100, 50}, {899, 649}, {500, 350}})
    {
        plan = MakeDrawPlan(settings, point[0], point[1], 8, 8, pane, true, 1);
        Check(plan.count <= plan.rects.size(), "combined reticle/feedback fits bounded storage");
        for (size_t i = 0; i < plan.count; ++i)
        {
            const auto& r = plan.rects[i];
            Check(r.left >= pane.left && r.top >= pane.top && r.right < pane.right && r.bottom < pane.bottom,
                  "all geometry including outlines stays in the current pane");
            Check(r.left <= r.right && r.top <= r.bottom, "clipped rectangles remain nonempty");
        }
    }
    for (float bad : {0.0f, -1.0f, 9.0f, std::numeric_limits<float>::quiet_NaN(),
                      std::numeric_limits<float>::infinity()})
        Check(MakeDrawPlan(settings, 500, 350, bad, 1, pane, true, 1).count == 0,
              "invalid scales stand down");
    Check(!MakeDrawPlan(settings, 99, 350, 1, 1, pane, true, 1).replacesStock,
          "off-pane aim points preserve the stock draw");
    Check(MakeDrawPlan(settings, 500, 350, 1, 1, {0, 0, 0, 0, 0}, true, 1).count == 0,
          "stale/empty pane stands down");

    DamageSample hit{1, 2, 1.0f, 0.8f, true, true, true, true};
    Check(ConfirmsHit(hit), "positive weapon damage by the local player confirms");
    auto sample = hit; sample.after = -0.1f;
    Check(ConfirmsHit(sample), "lethal health loss confirms without guessing a kill event");
    sample = hit; sample.after = sample.before;
    Check(!ConfirmsHit(sample), "immune/zero-damage contact does not confirm");
    sample.after = 1.1f;
    Check(!ConfirmsHit(sample), "healing does not confirm");
    sample = hit; sample.before = 0;
    Check(!ConfirmsHit(sample), "damage to an already depleted object does not confirm");
    sample = hit; sample.sameLifetime = false;
    Check(!ConfirmsHit(sample), "despawn/reused object identity is not proof of a hit");
    sample = hit; sample.localAttacker = false;
    Check(!ConfirmsHit(sample), "AI/other player damage does not confirm");
    sample = hit; sample.weaponSource = false;
    Check(!ConfirmsHit(sample), "collision/environmental damage does not confirm");
    sample = hit; sample.singlePlayer = false;
    Check(!ConfirmsHit(sample), "unqualified multiplayer authority is excluded");
    sample = hit; sample.victim = sample.attacker;
    Check(!ConfirmsHit(sample), "self damage does not confirm");
    sample = hit; sample.after = std::numeric_limits<float>::quiet_NaN();
    Check(!ConfirmsHit(sample), "invalid health data does not confirm");

    Pulse pulse;
    settings = {};
    settings.hitColor = ParseColor("Amber");
    settings.hitOpacity = 75;
    settings.hitSizePercent = 150;
    const auto hitOnly = MakeDrawPlan(settings, 500, 350, 2, 2, pane, false, 1);
    settings.opacity = 25;
    settings.sizePercent = 75;
    const auto resizedReticle = MakeDrawPlan(settings, 500, 350, 2, 2, pane, false, 1);
    Check(hitOnly.count == 16 && resizedReticle.count == hitOnly.count, "hit-only preview uses bounded geometry");
    for (size_t i = 0; i < hitOnly.count; ++i)
    {
        const auto& a = hitOnly.rects[i]; const auto& b = resizedReticle.rects[i];
        Check(a.left == b.left && a.top == b.top && a.right == b.right && a.bottom == b.bottom && a.color == b.color,
              "hit size/opacity stay independent of reticle size/opacity");
        Check(a.color == 0xBFFFC040u, "hit tint and opacity use their independent native ARGB values");
    }
    settings.style = Style::CrossDot; settings.reactive = true; settings.outline = true;
    size_t previewCount = 0;
    for (int i = 0; i < 3; ++i)
        previewCount += MakeDrawPlan(settings, 820 + i * 150, 550, 2, 2,
                                    {750, 490, 1200, 620, 0}, i != 0, i == 2 ? 1.0f : 0.0f).count;
    Check(previewCount <= 96, "all three UI samples fit their owned quad pool");
    Check(pulse.Strength(100, 120) == 0, "no initial hit pulse");
    pulse.Start(100);
    Check(pulse.Strength(100, 120) == 1 && pulse.Strength(160, 120) == 1, "hold first half of duration");
    Check(pulse.Strength(190, 120) == 0.5f && pulse.Strength(220, 120) == 0, "fade to zero on deadline");
    pulse.Start(210);
    Check(pulse.Strength(220, 120) == 1, "rapid successive hits refresh one pulse");
    Check(pulse.Strength(209, 120) == 0, "backward clock does not revive stale feedback");
    pulse.Reset();
    Check(pulse.Strength(220, 120) == 0, "mission reset removes feedback");
    return OpenShimTest::ExitCode();
}
