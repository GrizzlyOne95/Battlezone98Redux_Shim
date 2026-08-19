#pragma once

#include <cstdarg>
#include <cstdint>
#include <string>

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

    // Sanitizes log filenames against relative path traversal, invalid characters,
    // control characters, Windows reserved device names, and trailing dots/spaces.
    std::string SanitizeLogFilename(const char* fileName);

    // Returns <game executable directory>\logs\<fileName>, creating the
    // directory when possible and falling back to the game root on failure.
    std::string GetGameLogPath(const char* fileName);

    void LogShimA(LogLevel level, const char* component, const char* fmt, ...);
    void LogShimW(LogLevel level, const char* component, const wchar_t* fmt, ...);
    void LogShimVA(LogLevel level, const char* component, const char* fmt, va_list args);
    void LogShimVW(LogLevel level, const char* component, const wchar_t* fmt, va_list args);
}
