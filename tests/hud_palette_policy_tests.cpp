#include "hud_palette_policy.h"
#include "test_check.h"
#include <limits>
using OpenShimTest::Check;
using namespace BZROpenShim::HudPalette;
int main()
{
    const Settings stock;
    Check(!stock.Active() && !Preset("Stock").Active() && !Preset("unknown").Active(),
          "stock, absent and unknown palettes require no native hooks");
    auto s = Preset("HighContrast");
    Check(s.Active() && s[Role::HullHigh] != s[Role::HullLow] && s.radarBackgroundOpacity == 75,
          "contrast preset distinguishes health states and supplies a backdrop opacity");
    Check(Preset("Classic").radarBackgroundOpacity == -1, "classic leaves the native backdrop alone");
    s[Role::HullHigh] = 0xFF123456u;
    s[Role::HullMedium] = 0xFF654321u;
    s[Role::HullLow] = 0xFFABCDEFu;
    Check(Health(s, .5f, 7) == 0xFF123456u && Health(s, .25f, 7) == 0xFF654321u &&
          Health(s, .249f, 7) == 0xFFABCDEFu, "native 50/25 percent threshold boundaries remain distinct");
    Check(Health(s, -1, 7) == 7 && Health(s, std::numeric_limits<float>::quiet_NaN(), 7) == 7,
          "invalid health keeps the native fallback");
    Check(Health(stock, .1f, 0xFF001122u) == 0xFF001122u,
          "unset health colors preserve the current native palette");
    s[Role::UnitLow] = 0xFF010203u;
    Check(Health(s, .1f, 7, true) == 0xFF010203u && Health(s, .1f, 7) == 0xFFABCDEFu,
          "unit and cockpit health palettes stay independent");
    Check(KeepAlpha(0x3000FF00u, 0xFFFFC040u) == 0x30FFC040u,
          "grid tint preserves its native translucent alpha");
    Check(ContactTint(0x7F009900u, 0xFFFF0000u) == 0x7F990000u,
          "contact recoloring retains dimming and native alpha");
    Check(ContactTint(0x00000000u, 0xFFFFFFFFu) == 0, "invisible contacts remain invisible");
    Check(BZROpenShim::HudColors::Parse("Red") == 0xFFFF4040u &&
          BZROpenShim::HudColors::Parse("Yellow") == 0xFFFFFF40u,
          "warning color choices parse as native ARGB");
    return OpenShimTest::ExitCode();
}
