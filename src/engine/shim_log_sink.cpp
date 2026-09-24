// shim_log_sink.cpp
// BZR Open Shim - the openshim.log sink. See shim_log_sink.h for why the
// logger is split: this file is the single owner of the log file, its lock,
// and the session header and footer.
//
// winmm.dll compiles this. plugins/openshim.dll does not; it formats its own
// lines and hands the finished text over through the bootstrap API.
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "shim_log.h"
#include "shim_log_sink.h"
#include "game_log_path.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifdef _WIN32
#include <Windows.h>
#include <share.h>
#endif

#include <cstdio>
#include <cstring>
#include <string>

namespace BZROpenShim
{
#ifdef _WIN32
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
        return GetGameLogPath("openshim.log");
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
        const std::string primaryPath = BuildLogPath();
        std::string logPath = primaryPath;

        // _SH_DENYWR instead of fopen_s's deny-all sharing so the log can be
        // tailed by external tools while the game is running.
        g_LogFile = _fsopen(logPath.c_str(), "w", _SH_DENYWR);
        const bool usingFallback = g_LogFile == nullptr;
        if (usingFallback)
        {
            // An earlier game process may still own openshim.log. Keep this
            // process's diagnostics instead of silently dropping every line.
            char fallbackName[64] = {};
            _snprintf_s(fallbackName, _TRUNCATE, "openshim-%lu.log",
                        static_cast<unsigned long>(GetCurrentProcessId()));
            logPath = GetGameLogPath(fallbackName);
            g_LogFile = _fsopen(logPath.c_str(), "w", _SH_DENYWR);
        }
        if (!g_LogFile)
        {
            WriteDebugMirror(LogLevel::Error, "logger", "Could not open primary or process log file");
            return TRUE;
        }
        strncpy_s(g_LogPath, logPath.c_str(), _TRUNCATE);

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
        if (usingFallback)
            WriteLineUnlocked(LogLevel::Warn, "logger",
                              "Primary openshim.log unavailable; writing to process log instead");
        return TRUE;
    }

    bool EnsureLoggerReady()
    {
        InitOnceExecuteOnce(&g_LogInitOnce, InitLoggerOnce, nullptr, nullptr);
        return g_LogFile != nullptr;
    }

}

    void ShimLogSinkWrite(uint32_t level, const char* component, const char* message)
    {
        const LogLevel typed = static_cast<LogLevel>(level);
        if (EnsureLoggerReady())
        {
            AcquireSRWLockExclusive(&g_LogLock);
            WriteLineUnlocked(typed, component, message ? message : "");
            ReleaseSRWLockExclusive(&g_LogLock);
        }
        WriteDebugMirror(typed, component, message ? message : "");
    }

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

namespace
{
    // Registers the sink during static initialisation, which for a DLL runs
    // before our own DllMain body. The bootstrap is therefore already wired
    // by the time anything in DLL_PROCESS_ATTACH logs.
    struct SinkRegistration
    {
        SinkRegistration() { SetShimLogSink(&ShimLogSinkWrite); }
    };
    const SinkRegistration g_SinkRegistration;
}
#else
    void ShimLogSinkWrite(uint32_t, const char*, const char*) {}
    void InitializeShimLogger() {}
    void ShutdownShimLogger() {}
#endif
}
