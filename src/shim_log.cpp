#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <cstdio>
#include <cstring>
#include <string>

namespace BZROpenShim
{
namespace
{
    INIT_ONCE g_LogInitOnce = INIT_ONCE_STATIC_INIT;
    SRWLOCK g_LogLock = SRWLOCK_INIT;
    FILE* g_LogFile = nullptr;
    char g_LogPath[MAX_PATH] = {};

    const char* LevelToString(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Info:  return "INFO";
        case LogLevel::Warn:  return "WARN";
        case LogLevel::Error: return "ERROR";
        default:              return "INFO";
        }
    }

    const char* SafeComponent(const char* component)
    {
        return (component && component[0]) ? component : "shim";
    }

    void TrimTrailingNewlines(std::string& text)
    {
        while (!text.empty() && (text.back() == '\r' || text.back() == '\n'))
            text.pop_back();
    }

    int GetCurrentUtcOffsetMinutes()
    {
        DYNAMIC_TIME_ZONE_INFORMATION tz = {};
        const DWORD tzId = GetDynamicTimeZoneInformation(&tz);

        LONG bias = tz.Bias;
        if (tzId == TIME_ZONE_ID_DAYLIGHT)
            bias += tz.DaylightBias;
        else if (tzId == TIME_ZONE_ID_STANDARD)
            bias += tz.StandardBias;

        return -static_cast<int>(bias);
    }

    void FormatIso8601Utc(char* buffer, size_t bufferCount, const SYSTEMTIME& st)
    {
        if (!buffer || bufferCount == 0)
            return;

        _snprintf_s(
            buffer,
            bufferCount,
            _TRUNCATE,
            "%04u-%02u-%02uT%02u:%02u:%02u.%03uZ",
            st.wYear,
            st.wMonth,
            st.wDay,
            st.wHour,
            st.wMinute,
            st.wSecond,
            st.wMilliseconds);
    }

    void FormatIso8601Local(char* buffer, size_t bufferCount, const SYSTEMTIME& st, int utcOffsetMinutes)
    {
        if (!buffer || bufferCount == 0)
            return;

        const char sign = utcOffsetMinutes >= 0 ? '+' : '-';
        const int absOffsetMinutes = utcOffsetMinutes >= 0 ? utcOffsetMinutes : -utcOffsetMinutes;
        const int offsetHours = absOffsetMinutes / 60;
        const int offsetMinutes = absOffsetMinutes % 60;

        _snprintf_s(
            buffer,
            bufferCount,
            _TRUNCATE,
            "%04u-%02u-%02uT%02u:%02u:%02u.%03u%c%02d:%02d",
            st.wYear,
            st.wMonth,
            st.wDay,
            st.wHour,
            st.wMinute,
            st.wSecond,
            st.wMilliseconds,
            sign,
            offsetHours,
            offsetMinutes);
    }

    std::string BuildLogPath()
    {
        char modulePath[MAX_PATH] = {};
        if (GetModuleFileNameA(nullptr, modulePath, MAX_PATH) == 0)
            return "openshim.log";

        char* lastSlash = std::strrchr(modulePath, '\\');
        if (!lastSlash)
            return "openshim.log";

        *(lastSlash + 1) = '\0';
        return std::string(modulePath) + "openshim.log";
    }

    void WriteLineUnlocked(LogLevel level, const char* component, const char* message)
    {
        if (!g_LogFile)
            return;

        SYSTEMTIME st = {};
        GetSystemTime(&st);
        char utcBuffer[40] = {};
        FormatIso8601Utc(utcBuffer, sizeof(utcBuffer), st);
        std::fprintf(
            g_LogFile,
            "[%s] [pid:%lu tid:%lu] [%s] [%s] %s\n",
            utcBuffer,
            static_cast<unsigned long>(GetCurrentProcessId()),
            static_cast<unsigned long>(GetCurrentThreadId()),
            LevelToString(level),
            SafeComponent(component),
            message ? message : "");
        std::fflush(g_LogFile);
    }

    void WriteDebugMirror(LogLevel level, const char* component, const char* message)
    {
        char buffer[4608] = {};
        _snprintf_s(
            buffer,
            _TRUNCATE,
            "BZR-OpenShim [%s] [%s] %s\n",
            LevelToString(level),
            SafeComponent(component),
            message ? message : "");
        OutputDebugStringA(buffer);
    }

    BOOL CALLBACK InitLoggerOnce(PINIT_ONCE, PVOID, PVOID*)
    {
        const std::string logPath = BuildLogPath();
        std::strncpy(g_LogPath, logPath.c_str(), MAX_PATH - 1);

        fopen_s(&g_LogFile, logPath.c_str(), "a");
        if (!g_LogFile)
            return TRUE;

        // UCRT rejects line-buffered mode with a zero-sized buffer here and
        // fail-fast triggers during DllMain. Leave the default buffering in
        // place and flush explicitly after each write instead.
        SYSTEMTIME utcNow = {};
        SYSTEMTIME localNow = {};
        GetSystemTime(&utcNow);
        GetLocalTime(&localNow);

        char utcBuffer[40] = {};
        char localBuffer[48] = {};
        const int utcOffsetMinutes = GetCurrentUtcOffsetMinutes();
        FormatIso8601Utc(utcBuffer, sizeof(utcBuffer), utcNow);
        FormatIso8601Local(localBuffer, sizeof(localBuffer), localNow, utcOffsetMinutes);

        WriteLineUnlocked(LogLevel::Info, "logger", "================ session start ================");
        WriteLineUnlocked(LogLevel::Info, "logger", g_LogPath);
        char clockLine[160] = {};
        _snprintf_s(
            clockLine,
            _TRUNCATE,
            "Clock baseline utc=%s local=%s utcOffsetMinutes=%d",
            utcBuffer,
            localBuffer,
            utcOffsetMinutes);
        WriteLineUnlocked(LogLevel::Info, "logger", clockLine);
        return TRUE;
    }

    bool EnsureLoggerReady()
    {
        InitOnceExecuteOnce(&g_LogInitOnce, InitLoggerOnce, nullptr, nullptr);
        return g_LogFile != nullptr;
    }

    std::string FormatWideToUtf8(const wchar_t* fmt, va_list args)
    {
        if (!fmt)
            return {};

        wchar_t wideBuffer[4096] = {};
        _vsnwprintf_s(wideBuffer, _countof(wideBuffer), _TRUNCATE, fmt, args);

        const int bytesNeeded = WideCharToMultiByte(CP_UTF8, 0, wideBuffer, -1, nullptr, 0, nullptr, nullptr);
        if (bytesNeeded <= 1)
            return {};

        std::string utf8(static_cast<size_t>(bytesNeeded), '\0');
        WideCharToMultiByte(CP_UTF8, 0, wideBuffer, -1, utf8.data(), bytesNeeded, nullptr, nullptr);
        utf8.pop_back();
        return utf8;
    }

    std::string FormatAnsi(const char* fmt, va_list args)
    {
        if (!fmt)
            return {};

        char buffer[4096] = {};
        _vsnprintf_s(buffer, _countof(buffer), _TRUNCATE, fmt, args);
        return buffer;
    }

    void WriteFormattedMessage(LogLevel level, const char* component, const std::string& formatted)
    {
        std::string line = formatted;
        TrimTrailingNewlines(line);
        if (line.empty())
            line = "<empty>";

        if (EnsureLoggerReady())
        {
            AcquireSRWLockExclusive(&g_LogLock);
            WriteLineUnlocked(level, component, line.c_str());
            ReleaseSRWLockExclusive(&g_LogLock);
        }

        WriteDebugMirror(level, component, line.c_str());
    }
} // namespace

    void InitializeShimLogger()
    {
        EnsureLoggerReady();
    }

    void ShutdownShimLogger()
    {
        AcquireSRWLockExclusive(&g_LogLock);
        if (g_LogFile)
        {
            WriteLineUnlocked(LogLevel::Info, "logger", "================ session end ==================");
            std::fclose(g_LogFile);
            g_LogFile = nullptr;
        }
        ReleaseSRWLockExclusive(&g_LogLock);
    }

    void LogShimVA(LogLevel level, const char* component, const char* fmt, va_list args)
    {
        const std::string formatted = FormatAnsi(fmt, args);
        WriteFormattedMessage(level, component, formatted);
    }

    void LogShimVW(LogLevel level, const char* component, const wchar_t* fmt, va_list args)
    {
        const std::string formatted = FormatWideToUtf8(fmt, args);
        WriteFormattedMessage(level, component, formatted);
    }

    void LogShimA(LogLevel level, const char* component, const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        LogShimVA(level, component, fmt, args);
        va_end(args);
    }

    void LogShimW(LogLevel level, const char* component, const wchar_t* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        LogShimVW(level, component, fmt, args);
        va_end(args);
    }
}
