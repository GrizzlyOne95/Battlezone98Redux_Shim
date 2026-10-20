#include "menu_theme_policy.h"
#include "test_check.h"
#include <cmath>
using namespace BZROpenShim::MenuTheme;
using OpenShimTest::Check;
using OpenShimTest::ExitCode;
int main()
{
    Settings theme;const std::array<float,4> green{0,.5f,0,.25f};
    Check(Colorize(green,theme)==green,"Off retains the original pixel exactly");
    theme.enabled=true;
    Check(Colorize(green,theme)==std::array<float,4>{.5f,0,0,.25f},"green artwork becomes red with alpha preserved");
    for(const auto p: {std::array<float,4>{.8f,.8f,.8f,1},std::array<float,4>{1,0,0,.4f},std::array<float,4>{0,0,1,.8f},std::array<float,4>{0,0,0,0}})
        Check(Colorize(p,theme)==p,"neutral highlights, other hues and black remain unchanged");
    const auto mixed=Colorize({.2f,.7f,.1f,.8f},theme);
    Check(std::abs(mixed[0]-.7f)<.00001f&&mixed[1]==0&&mixed[2]==0&&mixed[3]==.8f,"full saturation removes neutral pink from green highlights while preserving peak detail");
    theme.rgb={0,100,255};const auto blue=Colorize(green,theme);
    Check(blue[0]==0&&std::abs(blue[1]-50/255.0f)<.00001f&&blue[2]==.5f&&blue[3]==.25f,"custom RGB channels affect only green detail");
    theme.rgb={-20,400,0};Check(Colorize(green,theme)==green,"out-of-range channels clamp without changing alpha");
    theme.rgb={255,0,0};theme.saturation=0;
    Check(Colorize(green,theme)==std::array<float,4>{.5f,.5f,.5f,.25f},"zero saturation produces neutral artwork with native alpha");
    theme.saturation=100;theme.whiteLevel=150;
    Check(Colorize(green,theme)==std::array<float,4>{.75f,0,0,.25f},"white level brightens the artwork independently of hue and alpha");
    theme.whiteLevel=0;Check(Colorize(green,theme)==std::array<float,4>{0,0,0,.25f},"minimum white level keeps native transparency");
    Check(IsMenuImage("mainCenterPanel.png")&&IsMenuImage("topcorner.png")&&IsMenuImage("osh_menu_theme_center.png"),"stock and shim menu chrome qualify");
    for(const auto name:{"bzone.ogv","arial.png","radar.png","map_preview.png","aflagon.png","unknown_mod.png","../mainCenterPanel.png","MAINCenterPanel.png"})
        Check(!IsMenuImage(name),"fonts, movies, flags, HUD, unknown and ambiguous paths remain excluded");
    return ExitCode();
}
