// Pins the autosave HUD notice's placement arithmetic.

#include "autosave_notice_layout.h"

#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::AutoSaveNotice;

int main()
{
    Layout l;
    // 1920x1080, a 200x20 text: panel is 16% wide, sits 3% above the bottom.
    Check(ComputeLayout(1920, 1080, 200.0f, 20.0f, l), "layout 1080p");
    Check((l.x2 - l.x1 + 1) >= 306 && (l.x2 - l.x1 + 1) <= 308, "panel is ~16% wide");
    Check(((l.x1 + l.x2 + 1) / 2 - 960) >= -1 && ((l.x1 + l.x2 + 1) / 2 - 960) <= 1, "panel is centred");
    Check(l.y2 == static_cast<int>(1080 * 0.97f) - 1, "bottom margin is 3%");
    Check((l.y2 - l.y1 + 1) >= 41 && (l.y2 - l.y1 + 1) <= 43, "height is ~2.1 lines");
    Check(l.textCentreX == 960, "text centred on x");
    Check(l.textTop > l.y1 && l.textTop + 20 < l.y2, "text sits inside the panel");

    // Wide text widens the panel past 16% so it never overflows.
    Check(ComputeLayout(800, 600, 300.0f, 20.0f, l), "wide text");
    Check((l.x2 - l.x1 + 1) >= 320, "panel grows to fit text");

    // Unusable inputs are refused.
    Check(!ComputeLayout(0, 1080, 200.0f, 20.0f, l), "zero width refused");
    Check(!ComputeLayout(1920, 1080, 0.0f, 20.0f, l), "zero text width refused");
    Check(!ComputeLayout(1920, 1080, 200.0f, -1.0f, l), "negative height refused");
    Check(!ComputeLayout(1920, 20, 200.0f, 20.0f, l), "viewport too short refused");

    return OpenShimTest::ExitCode();
}
