// Unit tests for BZROpenShim::GetGameLogPath sanitization logic
// (src/engine/shim_log.cpp).

#include "shim_log.h"

#include <cstdio>
#include <string>

using BZROpenShim::GetGameLogPath;

namespace
{
    int g_Failures = 0;
    int g_Checks = 0;

    void CheckEq(const std::string& actual, const std::string& expected, const char* name)
    {
        ++g_Checks;
        if (actual == expected)
            return;
        ++g_Failures;
        std::printf("FAIL %s\n  expected: %s\n  actual:   %s\n", name, expected.c_str(), actual.c_str());
    }
}

int main()
{
    // Normal filenames remain intact.
    CheckEq(GetGameLogPath("openshim.log"), "openshim.log", "normal log name");
    CheckEq(GetGameLogPath("custom_test.log"), "custom_test.log", "custom log name");

    // Subdirectory paths strip directory component to leaf name.
    CheckEq(GetGameLogPath("logs/custom.log"), "custom.log", "forward slash strip");
    CheckEq(GetGameLogPath("logs\\custom.log"), "custom.log", "backward slash strip");

    // Path traversal inputs fall back to openshim.log.
    CheckEq(GetGameLogPath(".."), "openshim.log", "dot dot traversal");
    CheckEq(GetGameLogPath("../.."), "openshim.log", "double dot dot traversal");
    CheckEq(GetGameLogPath("dir/.."), "openshim.log", "dir dot dot traversal");
    CheckEq(GetGameLogPath("."), "openshim.log", "single dot traversal");

    // Null and empty strings fall back to openshim.log.
    CheckEq(GetGameLogPath(nullptr), "openshim.log", "null pointer fallback");
    CheckEq(GetGameLogPath(""), "openshim.log", "empty string fallback");
    CheckEq(GetGameLogPath("folder/"), "openshim.log", "trailing slash fallback");

    // Invalid path characters fall back to openshim.log.
    CheckEq(GetGameLogPath("test:stream.log"), "openshim.log", "colon in filename");
    CheckEq(GetGameLogPath("test*file.log"), "openshim.log", "wildcard in filename");
    CheckEq(GetGameLogPath("test?file.log"), "openshim.log", "question mark in filename");
    CheckEq(GetGameLogPath("test<file.log"), "openshim.log", "less than in filename");
    CheckEq(GetGameLogPath("test>file.log"), "openshim.log", "greater than in filename");
    CheckEq(GetGameLogPath("test|file.log"), "openshim.log", "pipe in filename");

    std::printf("%d checks, %d failures\n", g_Checks, g_Failures);
    return g_Failures == 0 ? 0 : 1;
}
