// Shared failure reporting for the engine-independent unit tests.
//
// Two kinds of check, named by what happens after a failure:
//   Check   -- report, count, and keep going. main() returns ExitCode().
//   Require -- report and exit(1) immediately, for tests whose later steps
//              are meaningless once an earlier one has failed.
// Every failure line starts with "FAIL: " and goes to stderr after stdout is
// flushed, so it lands in order among a test's own progress output.
//
// Never use assert() in a test: the CTest lanes build Release, which defines
// NDEBUG and compiles assert() out, so a failing assert passes.
//
// Portable C++14 on purpose: the Linux CTest lane builds every target with
// -Wall -Wextra -Werror, and at least one target is compiled as C++14. The
// scripts/run_*_tests.ps1 scripts call cl directly on named sources; they
// find this header because a quoted include searches the including file's
// directory first.
#pragma once

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string>

#if defined(__GNUC__) || defined(__clang__)
#define OPENSHIM_TEST_PRINTF(fmt, args) __attribute__((format(printf, fmt, args)))
#else
#define OPENSHIM_TEST_PRINTF(fmt, args)
#endif

namespace OpenShimTest
{
    // Number of failures reported so far. Function-local statics keep the
    // header free of C++17 inline variables.
    inline int& FailureCount()
    {
        static int count = 0;
        return count;
    }

    // Number of Check/CheckAt calls made so far, passed or failed. Only a few
    // suites print it; failures do not depend on it.
    inline int& CheckCount()
    {
        static int count = 0;
        return count;
    }

    inline void VReport(const char* format, va_list args) OPENSHIM_TEST_PRINTF(1, 0);
    inline void VReport(const char* format, va_list args)
    {
        std::fflush(stdout);
        std::fputs("FAIL: ", stderr);
        std::vfprintf(stderr, format, args);
        std::fputc('\n', stderr);
        std::fflush(stderr);
    }

    // Reports one failure and keeps going. printf-style; always pass a
    // literal format ("%s", text), never text as the format.
    inline void Fail(const char* format, ...) OPENSHIM_TEST_PRINTF(1, 2);
    inline void Fail(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        VReport(format, args);
        va_end(args);
        ++FailureCount();
    }

    // Reports one failure and exits the test with status 1.
    [[noreturn]] inline void Abort(const char* format, ...) OPENSHIM_TEST_PRINTF(1, 2);
    [[noreturn]] inline void Abort(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        VReport(format, args);
        va_end(args);
        ++FailureCount();
        std::exit(1);
    }

    // Counts a check; on failure reports `what` and returns false so a
    // caller can print detail lines underneath.
    inline bool Check(bool condition, const char* what)
    {
        ++CheckCount();
        if (!condition)
            Fail("%s", what);
        return condition;
    }

    inline bool Check(bool condition, const std::string& what)
    {
        return Check(condition, what.c_str());
    }

    // The CHECK() form: the expression text and its line.
    inline bool CheckAt(bool condition, const char* expression, int line)
    {
        ++CheckCount();
        if (!condition)
            Fail("line %d: %s", line, expression);
        return condition;
    }

    inline void Require(bool condition, const char* what)
    {
        if (!condition)
            Abort("%s", what);
    }

    // 0 when nothing failed, 1 otherwise: the value main() returns.
    inline int ExitCode()
    {
        return FailureCount() == 0 ? 0 : 1;
    }
}

#define CHECK(c) ::OpenShimTest::CheckAt((c), #c, __LINE__)
