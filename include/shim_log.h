#pragma once

#include <cstdarg>
#include <cstdint>
#include <string>

#include "game_log_path.h"

namespace BZROpenShim
{
    enum class LogLevel : uint8_t
    {
        Debug,
        Info,
        Warn,
        Error,
    };

    void InitializeShimLogger();
    void ShutdownShimLogger();

    // SanitizeLogFilename and GetGameLogPath now live in game_log_path.h, so
    // the bootstrap can route the stock game logs without compiling the
    // logging subsystem. Included here so existing users keep working.

    void LogShimA(LogLevel level, const char* component, const char* fmt, ...);
    void LogShimW(LogLevel level, const char* component, const wchar_t* fmt, ...);
    void LogShimVA(LogLevel level, const char* component, const char* fmt, va_list args);
    void LogShimVW(LogLevel level, const char* component, const wchar_t* fmt, va_list args);
}
