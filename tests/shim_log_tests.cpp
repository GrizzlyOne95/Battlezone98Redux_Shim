// Unit tests for BZROpenShim::SanitizeLogFilename sanitization logic
// (src/engine/shim_log.cpp).

#include "shim_log.h"

#include <cstdio>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#include <share.h>
#endif

using BZROpenShim::SanitizeLogFilename;

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

    void Check(bool condition, const char* name)
    {
        ++g_Checks;
        if (condition)
            return;
        ++g_Failures;
        std::printf("FAIL %s\n", name);
    }
}

int main()
{
    // Normal filenames remain intact.
    CheckEq(SanitizeLogFilename("openshim.log"), "openshim.log", "normal log name");
    CheckEq(SanitizeLogFilename("custom_test.log"), "custom_test.log", "custom log name");

    // Subdirectory paths strip directory component to leaf name.
    CheckEq(SanitizeLogFilename("logs/custom.log"), "custom.log", "forward slash strip");
    CheckEq(SanitizeLogFilename("logs\\custom.log"), "custom.log", "backward slash strip");

    // Relative path navigation tokens fall back to openshim.log.
    CheckEq(SanitizeLogFilename(".."), "openshim.log", "dot dot traversal");
    CheckEq(SanitizeLogFilename("../.."), "openshim.log", "double dot dot traversal");
    CheckEq(SanitizeLogFilename("dir/.."), "openshim.log", "dir dot dot traversal");
    CheckEq(SanitizeLogFilename("."), "openshim.log", "single dot traversal");

    // Null and empty strings fall back to openshim.log.
    CheckEq(SanitizeLogFilename(nullptr), "openshim.log", "null pointer fallback");
    CheckEq(SanitizeLogFilename(""), "openshim.log", "empty string fallback");
    CheckEq(SanitizeLogFilename("folder/"), "openshim.log", "trailing slash fallback");

    // Invalid path and NTFS ADS characters fall back to openshim.log.
    CheckEq(SanitizeLogFilename("test:stream.log"), "openshim.log", "colon in filename");
    CheckEq(SanitizeLogFilename("test*file.log"), "openshim.log", "wildcard in filename");
    CheckEq(SanitizeLogFilename("test?file.log"), "openshim.log", "question mark in filename");
    CheckEq(SanitizeLogFilename("test<file.log"), "openshim.log", "less than in filename");
    CheckEq(SanitizeLogFilename("test>file.log"), "openshim.log", "greater than in filename");
    CheckEq(SanitizeLogFilename("test|file.log"), "openshim.log", "pipe in filename");

    // Control characters fall back to openshim.log.
    CheckEq(SanitizeLogFilename("test\nfile.log"), "openshim.log", "newline in filename");
    CheckEq(SanitizeLogFilename("test\tfile.log"), "openshim.log", "tab in filename");

    // Trailing dots and spaces fall back to openshim.log.
    CheckEq(SanitizeLogFilename("test.log."), "openshim.log", "trailing dot");
    CheckEq(SanitizeLogFilename("test.log "), "openshim.log", "trailing space");

    // Windows reserved device names fall back to openshim.log.
    CheckEq(SanitizeLogFilename("CON"), "openshim.log", "CON device name");
    CheckEq(SanitizeLogFilename("con.log"), "openshim.log", "con.log device name");
    CheckEq(SanitizeLogFilename("PRN.txt"), "openshim.log", "PRN device name");
    CheckEq(SanitizeLogFilename("AUX"), "openshim.log", "AUX device name");
    CheckEq(SanitizeLogFilename("NUL.log"), "openshim.log", "NUL device name");
    CheckEq(SanitizeLogFilename("COM1.log"), "openshim.log", "COM1 device name");
    CheckEq(SanitizeLogFilename("LPT9.txt"), "openshim.log", "LPT9 device name");

    // COM10/LPT0 are NOT reserved device names (only COM1-COM9 / LPT1-LPT9).
    CheckEq(SanitizeLogFilename("COM10.log"), "COM10.log", "COM10 is not reserved");
    CheckEq(SanitizeLogFilename("LPT0.log"), "LPT0.log", "LPT0 is not reserved");

    // Upper bound of the reserved COM/LPT ranges (COM9, LPT9) still sanitize.
    CheckEq(SanitizeLogFilename("COM9.txt"), "openshim.log", "COM9 device name");
    CheckEq(SanitizeLogFilename("LPT9.log"), "openshim.log", "LPT9 device name");

    // Reserved device names are matched case-insensitively.
    CheckEq(SanitizeLogFilename("nul"), "openshim.log", "lowercase nul device name");
    CheckEq(SanitizeLogFilename("CoM1.log"), "openshim.log", "mixed case COM1 device name");

    // GetGameLogPath on non-Windows builds returns the sanitized leaf directly.
#ifndef _WIN32
    CheckEq(BZROpenShim::GetGameLogPath("logs/custom.log"), "custom.log", "linux game log path strips to leaf");
    CheckEq(BZROpenShim::GetGameLogPath(".."), "openshim.log", "linux game log path rejects traversal");
#endif

#ifdef _WIN32
    // Reproduce a second game process starting while the first still owns the
    // shared log. Its BZN diagnostics must go to a process-specific file.
    const std::string primaryPath = BZROpenShim::GetGameLogPath("openshim.log");
    FILE* owner = _fsopen(primaryPath.c_str(), "w", _SH_DENYWR);
    Check(owner != nullptr, "open primary log as first process");
    if (owner)
    {
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "test", "fallback marker");
        BZROpenShim::ShutdownShimLogger();
        std::fclose(owner);

        char fallbackName[64] = {};
        _snprintf_s(fallbackName, _TRUNCATE, "openshim-%lu.log",
                    static_cast<unsigned long>(GetCurrentProcessId()));
        const std::string fallbackPath = BZROpenShim::GetGameLogPath(fallbackName);
        FILE* fallback = nullptr;
        fopen_s(&fallback, fallbackPath.c_str(), "rb");
        Check(fallback != nullptr, "process log created while primary is locked");
        if (fallback)
        {
            std::string contents;
            char buffer[512] = {};
            while (const size_t count = std::fread(buffer, 1, sizeof(buffer), fallback))
                contents.append(buffer, count);
            std::fclose(fallback);
            Check(contents.find("fallback marker") != std::string::npos,
                  "diagnostic preserved in process log");
            Check(contents.find("Primary openshim.log unavailable") != std::string::npos,
                  "fallback reason recorded");
        }
        std::remove(fallbackPath.c_str());
        std::remove(primaryPath.c_str());
    }
#endif

    std::printf("%d checks, %d failures\n", g_Checks, g_Failures);
    return g_Failures == 0 ? 0 : 1;
}
