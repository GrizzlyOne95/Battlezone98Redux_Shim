#include "camera_fov_policy.h"
#include "test_check.h"
#include <cmath>
#include <cstdio>
#include <initializer_list>

using namespace BZROpenShim::CameraFovPolicy;
using OpenShimTest::Check;

int main()
{
    for (const char* invalid : { "", "0", "Stock", "nan", "inf", "-90", "59", "121",
                                "90junk", "90.5", "999999999999999999999999999" })
        Check(ParseDegrees(invalid) == 0, "invalid/stock input must disable the override");
    Check(ParseDegrees(nullptr) == 0, "missing preference keeps stock");
    Check(ParseDegrees(" 90 \t") == 90, "whitespace is accepted");
    Check(ParseDegrees("60") == 60 && ParseDegrees("120") == 120, "inclusive safe bounds");
    const uint32_t satellite = 0x3FC90FDB; // pi/2
    for (int degrees : { 0, 60, 80, 90, 120, 999 })
    {
        Check(SelectFovBits(kStockFovBits, degrees, false) == kStockFovBits,
              "non-player cameras pass through even with an 80-degree input");
        Check(SelectFovBits(satellite, degrees, true) == satellite,
              "nonstandard engine angles pass through");
    }
    Check(SelectFovBits(kStockFovBits, 0, true) == kStockFovBits, "stock preserves exact bits");
    for (int degrees : { 60, 80, 90, 120 })
    {
        const uint32_t bits = SelectFovBits(kStockFovBits, degrees, true);
        float radians = 0;
        std::memcpy(&radians, &bits, sizeof(radians));
        Check(std::abs(radians - degrees * 3.14159265358979323846 / 180.0) < 0.000001,
              "player override converts degrees to radians");
    }
    std::puts("camera FOV policy tests passed");
    return OpenShimTest::ExitCode();
}
