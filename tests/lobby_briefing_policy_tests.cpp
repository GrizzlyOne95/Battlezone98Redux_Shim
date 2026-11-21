#include "lobby_briefing_policy.h"
#include "test_check.h"
#include <set>
#include <string>

using namespace BZROpenShim::LobbyBriefingPolicy;
using OpenShimTest::Check;

namespace
{
    Pages::ExistsFn In(const std::set<std::string>& files)
    {
        return [files](const std::string& name) { return files.count(name) != 0; };
    }
}

int main()
{
    Check(MissionStemFromMapFile("misn04.bzn") == "misn04", "extension removed");
    Check(MissionStemFromMapFile("maps\\mpdm01.bzn") == "mpdm01", "folder removed");
    Check(MissionStemFromMapFile("a/b.c.bzn") == "b", "cut at the first '.', as the .des loader");
    Check(MissionStemFromMapFile("bare") == "bare", "a bare name is the stem");
    Check(MissionStemFromMapFile("").empty(), "empty name");

    Check(!HasBriefing("mpdm01", In({})), "no .des: no briefing");
    Check(HasBriefing("mpdm01", In({ "mpdm01.des" })), "page 1 present");
    Check(!HasBriefing("", In({ ".des" })), "empty stem never has a briefing");
    Check(!HasBriefing("abcdefghijkl", In({ "abcdefghijkl.des" })), "16-char name is past the lookup limit");
    Check(HasBriefing("abcdefghijk", In({ "abcdefghijk.des" })), "15-char name fits");
    Check(!HasBriefing("m", nullptr), "no lookup: no briefing");

    Check(CountPages("m", In({})) == 0, "no page 1: zero pages");
    Check(CountPages("m", In({ "m.des" })) == 1, "page 1 only");
    Check(CountPages("m", In({ "m.des", "m_2.des", "m_3.des" })) == 3, "consecutive pages");
    Check(CountPages("m", In({ "m.des", "m_3.des" })) == 1, "a gap stops the count");
    Check(CountPages("m", In({ "m_2.des" })) == 0, "page 2 without page 1 is ignored");
    Check(CountPages("abcdefghi", In({ "abcdefghi.des", "abcdefghi_2.des" })) == 1,
          "a base too long for page files stays single page");

    Check(PageTextFileName("m", 1) == "m.des" && PageTextFileName("m", 4) == "m_4.des", "page text names");
    Check(PageImageFileName("m", 1) == "m_1.png" && PageImageFileName("m", 9) == "m_9.png", "page image names");

    Check(ClipPageText("short") == "short", "short text untouched");
    Check(ClipPageText(std::string(kMaxPageTextChars + 10, 'x')).size() == kMaxPageTextChars, "long text clipped");

    Check(ActionForKey(0x1B) == KeyAction::Close, "escape closes");
    Check(ActionForKey(0x25) == KeyAction::Prev && ActionForKey(0x21) == KeyAction::Prev, "left and page up go back");
    Check(ActionForKey(0x27) == KeyAction::Next && ActionForKey(0x22) == KeyAction::Next, "right and page down go on");
    Check(ActionForKey(0x26) == KeyAction::ScrollUp && ActionForKey(0x28) == KeyAction::ScrollDown, "up/down scroll");
    Check(ActionForKey(0x0D) == KeyAction::None && ActionForKey(0x41) == KeyAction::None, "other keys are not ours");

    return OpenShimTest::ExitCode();
}
