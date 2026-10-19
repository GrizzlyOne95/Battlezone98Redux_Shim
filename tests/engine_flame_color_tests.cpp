#include "engine_flame_color.h"
#include "test_check.h"

using namespace BZROpenShim::EngineFlameColor;
using OpenShimTest::Check;

int main()
{
    Check(ReadOdf("[HoverCraftClass]\nflameColor = \"red\"\n") == 2,
          "canonical stock HoverCraftClass section is supported");
    Check(ReadOdf("[HoverCraft]\r\nflameColor = \"GrEeN\" // custom\r\n") == 3,
          "section, key and value ignore case and accept quotes/comments");
    Check(ReadOdf("[hovercraft]\nFLAMECOLOR='blackdog' ; blood red") == 5,
          "blackdog is available through the ODF");
    Check(ReadOdf("[HoverCraft]\nflameColor=orange\n[Other]\nflameColor=red") == 4,
          "other sections cannot override HoverCraft");
    Check(ReadOdf("flameColor=blue\n[GameObjectClass]\nflameColor=red") == Unspecified,
          "only HoverCraft keys apply");
    for (const char* value : {"purple", "#ff0000", "blue extra", "\"blue", "6", ""})
        Check(Parse(value) == Unspecified, "unsupported colors retain faction fallback");
    Check(ReadOdf("[HoverCraft]\nflameColor=default") == 0,
          "explicit stock is distinct from missing or invalid");
    constexpr char terminated[] = "[HoverCraftClass]\nflameColor=blue\0ignored";
    Check(ReadOdf(std::string_view(terminated, sizeof(terminated) - 1)) == 1,
          "engine item terminator is not part of the value");
    Check(Parse("blue") == 1 && Parse("red") == 2 && Parse("green") == 3 &&
          Parse("orange") == 4 && Parse("blackdog") == 5, "all texture choices");
    const int pink = RgbTag | 0xFF3399;
    Check(Parse("\"1.0 0.2 0.6\"") == pink &&
          ReadOdf("[HoverCraftClass]\nflameColor=\"1.0 0.2 0.6\" ; pink") == pink,
          "normalized RGB produces the requested pink");
    Check(Parse("0 0 0") == RgbTag && Parse("1 1 1") == (RgbTag | 0xFFFFFF),
          "black and white are explicit RGB choices");
    for (const char* bad : {"1 0", "1 0 0 0", "1.1 0 0", "-0.1 0 0", "nan 0 1",
                            "1 inf 0", "1.0.2.6", "1,0,1", "1 0 1 extra"})
        Check(Parse(bad) == Unspecified, "malformed or out-of-range RGB falls back");
    Check(Select(0, pink, false, 'a') == pink && Select(2, pink, true, 'a') == 2,
          "RGB works independently of faction coloring and retains EXU priority");
    Check(TintVertex(0xA0ABCDEF, 0xFF3399) == 0xA0FF3399,
          "RGB tint retains native sprite alpha");
    Check(TintVertex(0x60000000, 0xFF0000) == 0x60FF0000 &&
          TintVertex(0xFF000000, 0x003300) == 0xFF003300 &&
          TintVertex(0xFF000000, 0x000099) == 0xFF000099,
          "additive channel passes isolate red green and blue");
    Check(Select(2, 3, true, 'a') == 2, "EXU beats ODF and faction");
    Check(Select(0, 3, false, 's') == 3, "ODF applies with faction coloring disabled");
    Check(Select(0, 0, true, 'a') == 0, "explicit default suppresses faction tint");
    Check(Select(0, Unspecified, true, 'a') == 1 &&
          Select(0, Unspecified, true, 's') == 4 &&
          Select(0, Unspecified, true, 'c') == 3 &&
          Select(0, Unspecified, true, 'b') == 5, "faction mapping is preserved");
    Check(Select(0, Unspecified, false, 'a') == 0 &&
          Select(0, Unspecified, true, 'x') == 0, "stock fallbacks");
    return OpenShimTest::ExitCode();
}
