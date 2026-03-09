#pragma once

#include <cstdarg>
#include <cstdint>

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

    void LogShimA(LogLevel level, const char* component, const char* fmt, ...);
    void LogShimW(LogLevel level, const char* component, const wchar_t* fmt, ...);
    void LogShimVA(LogLevel level, const char* component, const char* fmt, va_list args);
    void LogShimVW(LogLevel level, const char* component, const wchar_t* fmt, va_list args);
}
