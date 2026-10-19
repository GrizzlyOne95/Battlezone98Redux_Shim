#include "hud_color_policy.h"
#include "test_check.h"
using OpenShimTest::Check;
using BZROpenShim::HudColors::Parse;
int main()
{
    Check(!Parse("Default") && !Parse("") && !Parse("unknown"), "default and invalid choices retain the layout palette");
    Check(Parse("bLuE") == 0xFF4080FFu && Parse("Amber") == 0xFFFFC040u,
          "presets preserve native ARGB order and ignore case");
    Check(Parse("#123456") == 0xFF123456u && Parse("0x123456") == 0xFF123456u,
          "RGB hex receives opaque alpha");
    Check(Parse("0x80123456") == 0x80123456u && Parse("#00123456") == 0x00123456u,
          "explicit ARGB retains alpha including zero");
    for (const char* bad : {"123456", "#12345", "#123456789", "0xGG1234", "#12 456", "0x"})
        Check(!Parse(bad), "malformed custom colors retain layout defaults");
    return OpenShimTest::ExitCode();
}
