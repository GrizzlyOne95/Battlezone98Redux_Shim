#include "text_entry_input_filter.h"

#include <cstdio>
#include <string>
#include "test_check.h"

namespace
{
    namespace TI = BZROpenShim::TextEntryInput;

    void TestClassify()
    {
        CHECK(TI::Classify(0x16) == TI::CharAction::Paste);
        CHECK(TI::Classify(0x08) == TI::CharAction::Pass);
        CHECK(TI::Classify('\r') == TI::CharAction::Pass);
        CHECK(TI::Classify('\n') == TI::CharAction::Pass);
        CHECK(TI::Classify(0x00) == TI::CharAction::Drop);
        CHECK(TI::Classify(0x03) == TI::CharAction::Drop);  // Ctrl+C
        CHECK(TI::Classify('\t') == TI::CharAction::Drop);
        CHECK(TI::Classify(0x1B) == TI::CharAction::Drop);  // Escape
        CHECK(TI::Classify(0x1F) == TI::CharAction::Drop);
        CHECK(TI::Classify(0x7F) == TI::CharAction::Drop);  // Ctrl+Backspace
        CHECK(TI::Classify(' ') == TI::CharAction::Pass);
        CHECK(TI::Classify('b') == TI::CharAction::Pass);
        CHECK(TI::Classify('~') == TI::CharAction::Pass);
        CHECK(TI::Classify(0xE9) == TI::CharAction::Pass);  // stock keeps Latin-1 typing
    }

    void TestPastableText()
    {
        CHECK(TI::PastableText("ws://bzr.battlezonecommunity.com:1337/") ==
              "ws://bzr.battlezonecommunity.com:1337/");
        CHECK(TI::PastableText(L"bzr.battlezonecommunity.com") == "bzr.battlezonecommunity.com");
        CHECK(TI::PastableText("host.example\r\nsecond line") == "host.example");
        CHECK(TI::PastableText(L"a\nb") == "a");
        CHECK(TI::PastableText("\x16h\to\x7Fst") == "host");
        CHECK(TI::PastableText(L"caf\u00E9 \u4E2D!") == "caf !");
        CHECK(TI::PastableText("\xE9x") == "x");
        CHECK(TI::PastableText("") == "");
        CHECK(TI::PastableText(static_cast<const char*>(nullptr)) == "");
        CHECK(TI::PastableText("\nx") == "");
        CHECK(TI::PastableText("abcdef", 3) == "abc");
        const std::string longText(1000, 'x');
        CHECK(TI::PastableText(longText.c_str()).size() == TI::kMaxPasteChars);
    }
}

int main()
{
    TestClassify();
    TestPastableText();
    if (OpenShimTest::FailureCount() == 0)
        std::printf("text_entry_input_filter_tests: all passed\n");
    return OpenShimTest::ExitCode();
}
