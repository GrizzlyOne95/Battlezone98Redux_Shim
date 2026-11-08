#include "resolution_list_policy.h"
#include "test_check.h"

using namespace BZROpenShim::ResolutionList;
using OpenShimTest::Check;
using OpenShimTest::ExitCode;

int main()
{
    int w = 0, h = 0;
    Check(ParseModeSize("1920 x 1080 @ 32-bit colour", w, h) && w == 1920 && h == 1080, "parses a stock mode string");
    Check(ParseModeSize("  800 X 600", w, h) && w == 800 && h == 600, "tolerates spaces and capital X");
    Check(!ParseModeSize("Windowed", w, h) && !ParseModeSize("", w, h) && !ParseModeSize(nullptr, w, h) &&
              !ParseModeSize("1920 x", w, h) && !ParseModeSize("0 x 0", w, h) && !ParseModeSize("123456 x 1", w, h),
          "rejects text that is not WxH");

    // 16:9 desktop at 1920x1080.
    {
        SeenSizes seen;
        Check(ShouldKeep(1920, 1080, 1920, 1080, false, seen), "desktop size is kept");
        Check(!ShouldKeep(1920, 1080, 1920, 1080, false, seen), "a duplicate of it is dropped");
        Check(ShouldKeep(1920, 1080, 1920, 1080, true, seen), "a duplicate that is the current value is kept");
        Check(ShouldKeep(1280, 720, 1920, 1080, false, seen), "common 16:9 size is kept");
        Check(!ShouldKeep(1024, 768, 1920, 1080, false, seen), "common size with the wrong aspect is dropped");
        Check(!ShouldKeep(1280, 1024, 1920, 1080, false, seen), "5:4 is dropped on a 16:9 desktop");
        Check(!ShouldKeep(1234, 694, 1920, 1080, false, seen), "uncommon size with the right aspect is dropped");
        Check(ShouldKeep(1234, 694, 1920, 1080, true, seen), "an uncommon size is kept when current");
        Check(ShouldKeep(1366, 768, 1920, 1080, false, seen), "1366x768 is within 0.02 of 16:9");
        seen.Clear();
        Check(ShouldKeep(1280, 720, 1920, 1080, false, seen), "Clear forgets earlier sizes");
    }
    // Ultrawide desktop: only the desktop size and 21:9 commons survive.
    {
        SeenSizes seen;
        Check(ShouldKeep(3440, 1440, 3440, 1440, false, seen), "ultrawide desktop kept");
        Check(!ShouldKeep(1920, 1080, 3440, 1440, false, seen), "16:9 dropped on a 21:9 desktop");
        Check(ShouldKeep(2560, 1080, 3440, 1440, false, seen), "2560x1080 is within 0.02 of 3440x1440");
    }
    // Unknown desktop: fail open, still deduped.
    {
        SeenSizes seen;
        Check(ShouldKeep(1111, 777, 0, 0, false, seen), "unknown desktop keeps everything");
        Check(!ShouldKeep(1111, 777, 0, 0, false, seen), "unknown desktop still dedupes");
    }
    // A full dedupe table fails open.
    {
        SeenSizes seen;
        for (int i = 0; i < static_cast<int>(SeenSizes::kCapacity); ++i)
            seen.Add(100 + i, 100);
        Check(ShouldKeep(1920, 1080, 1920, 1080, false, seen), "full table still decides");
        Check(ShouldKeep(1920, 1080, 1920, 1080, false, seen), "duplicate past a full table is kept, not dropped wrongly");
    }
    return ExitCode();
}
