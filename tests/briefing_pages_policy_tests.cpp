#include "briefing_pages_policy.h"
#include "test_check.h"
#include <set>
#include <string>

using namespace BZROpenShim::BriefingPagesPolicy;
using OpenShimTest::Check;

namespace
{
    ExistsFn In(const std::set<std::string>& files)
    {
        return [files](const std::string& name) { return files.count(name) != 0; };
    }
}

int main()
{
    Check(MissionBaseFromDesArg("misn04.des") == "misn04", "base cuts at the extension");
    Check(MissionBaseFromDesArg("misn04.bzn") == "misn04", "a .bzn name gives the same base");
    Check(MissionBaseFromDesArg("misn04") == "misn04", "a bare name is the base");
    Check(MissionBaseFromDesArg("a.b.des") == "a", "the loader cuts at the first dot");
    Check(MissionBaseFromDesArg(nullptr).empty(), "null gives no base");

    Check(PageFileName("misn04", 2, ".des") == "misn04_2.des", "page text name");
    Check(PageFileName("misn04", 9, "p.des") == "misn04_9p.des", "sidebar name");
    Check(PageFileName("m", 3, ".ogv") == "m_3.ogv", "media name");

    Check(NamesFit("misn0412"), "8-char base fits: misn0412_9p.des is 15 chars");
    Check(!NamesFit("misn04123"), "9-char base would make a 16-char name");
    Check(!NamesFit(""), "empty base never fits");

    Check(CountPages("misn04", In({})) == 1, "no _2.des: single page, stock behaviour");
    Check(CountPages("misn04", In({ "misn04_2.des", "misn04_3.des" })) == 3, "consecutive pages count");
    Check(CountPages("misn04", In({ "misn04_2.des", "misn04_4.des" })) == 2, "stops at the first gap");
    Check(CountPages("misn04", In({ "misn04_3.des" })) == 1, "page 3 alone is ignored");
    std::set<std::string> many;
    for (int page = 2; page <= 12; ++page)
        many.insert(PageFileName("m", page, ".des"));
    Check(CountPages("m", In(many)) == kMaxPages, "capped at nine pages");
    Check(CountPages("misn04123", In({ "misn04123_2.des" })) == 1, "over-long base stays single page");
    Check(CountPages("misn04", ExistsFn()) == 1, "no lookup: single page");

    const PageFiles bare = ResolvePage("m", 2, In({ "m_2.des" }));
    Check(bare.des == "m_2.des", "page text file");
    Check(bare.sidebar.empty() && bare.media.empty() && bare.wav.empty(), "optional files absent");
    Check(bare.mediaKind == MediaKind::Inherit, "no media keeps page 1's display");

    const PageFiles full = ResolvePage("m", 2, In({ "m_2.des", "m_2p.des", "m_2.png", "m_2.ogv", "m_2.wav" }));
    Check(full.sidebar == "m_2p.des", "sidebar picked up");
    Check(full.media == "m_2.ogv" && full.mediaKind == MediaKind::Video, "ogv preferred over png");
    Check(full.wav == "m_2.wav", "wav picked up");

    const PageFiles image = ResolvePage("m", 3, In({ "m_3.des", "m_3.png" }));
    Check(image.media == "m_3.png" && image.mediaKind == MediaKind::Image, "png used without ogv");

    Check(ClampPage(0, 3) == 1 && ClampPage(4, 3) == 3 && ClampPage(2, 3) == 2, "no wraparound");
    Check(ClampPage(5, 0) == 1, "degenerate count");

    Check(StepForKey(0x25) == -1 && StepForKey(0x21) == -1, "left and page up go back");
    Check(StepForKey(0x27) == 1 && StepForKey(0x22) == 1, "right and page down go forward");
    Check(StepForKey(0x1B) == 0 && StepForKey(0x26) == 0 && StepForKey(0x28) == 0,
          "escape and up/down stay with the game");

    int colour = -1;
    Check(ParseColourPrefix("%2Mission text", colour) && colour == 2, "colour index parsed");
    Check(ParseColourPrefix("%13 tanks", colour) && colour == 1, "one digit only");
    colour = 7;
    Check(!ParseColourPrefix("no prefix", colour) && colour == 7, "absent prefix leaves output");
    Check(!ParseColourPrefix("%x", colour) && !ParseColourPrefix(nullptr, colour), "malformed prefix");

    return OpenShimTest::ExitCode();
}
