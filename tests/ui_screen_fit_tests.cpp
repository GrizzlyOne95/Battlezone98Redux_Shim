#include "ui_screen_fit.h"
#include "test_check.h"
#include <array>
#include <limits>
using OpenShimTest::Check;
using namespace BZROpenShim::UiScreenFit;
int main()
{
    for (const auto size : {std::array<float, 2>{640, 360}, {584, 900}, {1600, 900}, {3840, 2160}, {3440, 1440}})
    {
        const auto fit = Calculate(size[0], size[1]);
        Check(fit.x >= -.001f && fit.y >= -.001f && fit.x + 1440 * fit.scale <= size[0] + .001f &&
              fit.y + 1080 * fit.scale <= size[1] + .001f, "whole options canvas stays inside the client area");
        const float x = fit.x + 970 * fit.scale, y = fit.y + 550 * fit.scale;
        Check(std::abs((x - fit.x) / fit.scale - 970) < .001f &&
              std::abs((y - fit.y) / fit.scale - 550) < .001f, "hover/input coordinates invert the same letterbox transform");
        Check(fit.RelativeToHeight(size[1]) <= 1, "fit never enlarges native height-scaled content");
    }
    Check(Calculate(1600, 900).RelativeToHeight(900) == 1, "normal widescreen keeps the original layout scale");
    Check(Calculate(584, 900).RelativeToHeight(900) < .5f, "narrow windows scale the entire content rather than cropping columns");
    Check(TextWidthInDesignSpace(100, 360) == 300 && TextWidthInDesignSpace(100, 2160) == 50,
          "text measures normalize by client height for both small windows and large displays");
    const auto narrow = Calculate(584, 900);
    Check(std::abs(TextWidthInDesignSpace(100, 900, narrow.RelativeToHeight(900)) - 100 / narrow.scale) < .001f,
          "native width-fitted fonts normalize by the same scale as narrow-window geometry");
    Check(Calculate(0, 0).scale == 1 && Calculate(std::numeric_limits<float>::quiet_NaN(), 900).scale == 1,
          "invalid metrics retain a safe default");
    return OpenShimTest::ExitCode();
}
