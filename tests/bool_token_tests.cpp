#include "bool_token.h"

#include <cstdio>
#include <string>
#include "test_check.h"

namespace
{
    using BZROpenShim::BoolToken::TryParse;

    // 1 = parses true, 0 = parses false, -1 = unrecognized.
    int Parse(const char* text)
    {
        bool value = false;
        if (!TryParse(text, value))
            return -1;
        return value ? 1 : 0;
    }

    void TestEveryWord()
    {
        for (const char* word : {"1", "true", "on", "yes", "enabled"})
            CHECK(Parse(word) == 1);
        for (const char* word : {"0", "false", "off", "no", "disabled"})
            CHECK(Parse(word) == 0);
    }

    void TestCaseAndSurroundingWhitespaceAreIgnored()
    {
        CHECK(Parse("TRUE") == 1);
        CHECK(Parse("Enabled") == 1);
        CHECK(Parse("  off\t") == 0);
        CHECK(Parse("\r\nDisabled \n") == 0);
    }

    void TestOtherTextIsUnrecognized()
    {
        CHECK(Parse(nullptr) == -1);
        CHECK(Parse("") == -1);
        CHECK(Parse("   ") == -1);
        CHECK(Parse("2") == -1);
        CHECK(Parse("-1") == -1);
        CHECK(Parse("y") == -1);
        CHECK(Parse("t rue") == -1);
        CHECK(Parse("truee") == -1);
        CHECK(Parse("enabledx") == -1);
        CHECK(Parse("reduced") == -1);
    }

    void TestUnrecognizedLeavesOutputAlone()
    {
        bool value = true;
        CHECK(!TryParse("maybe", value));
        CHECK(value);
        value = false;
        CHECK(!TryParse("maybe", value));
        CHECK(!value);
    }

    void TestLengthIsHonored()
    {
        bool value = false;
        const char text[] = "offset";
        CHECK(TryParse(text, 3, value));
        CHECK(!value);
        CHECK(!TryParse(text, sizeof(text) - 1, value));
    }

    void TestStringOverload()
    {
        bool value = false;
        CHECK(TryParse(std::string(" yes "), value));
        CHECK(value);
        const std::string embedded("on\0x", 4);
        CHECK(!TryParse(embedded, value));
    }
}

namespace
{
    using BZROpenShim::BoolToken::IsTruthy;

    void TestTruthyFollowsTheWords()
    {
        for (const char* word : {"1", "true", "ON", "yes", "Enabled"})
            CHECK(IsTruthy(word));
        for (const char* word : {"0", "false", "OFF", "No", "disabled", " off "})
            CHECK(!IsTruthy(word));
    }

    void TestTruthyTreatsOtherTextAsOn()
    {
        CHECK(IsTruthy("2"));
        CHECK(IsTruthy("verbose"));
        CHECK(IsTruthy("offf"));
    }

    void TestTruthyTreatsBlankAsOff()
    {
        CHECK(!IsTruthy(static_cast<const char*>(nullptr)));
        CHECK(!IsTruthy(""));
        CHECK(!IsTruthy(" \t"));
        CHECK(!IsTruthy(std::string()));
    }
}

int main()
{
    TestTruthyFollowsTheWords();
    TestTruthyTreatsOtherTextAsOn();
    TestTruthyTreatsBlankAsOff();
    TestEveryWord();
    TestCaseAndSurroundingWhitespaceAreIgnored();
    TestOtherTextIsUnrecognized();
    TestUnrecognizedLeavesOutputAlone();
    TestLengthIsHonored();
    TestStringOverload();
    if (OpenShimTest::FailureCount() == 0)
        std::printf("bool_token_tests: all passed\n");
    return OpenShimTest::ExitCode();
}
