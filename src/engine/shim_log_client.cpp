// shim_log_client.cpp
// BZR Open Shim - log message formatting, on whichever side called.
//
// This is the half every LogShimA/W/VA/VW call site in the codebase reaches.
// It formats locally and hands one finished UTF-8 string to the installed
// sink, so no va_list, variadic call, std::string or FILE* ever crosses a
// module boundary. See shim_log_sink.h.
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "shim_log.h"
#include "shim_log_sink.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifdef _WIN32
#include <Windows.h>
#endif

#include <atomic>
#include <cstdio>
#include <cstring>
#include <string>

namespace BZROpenShim
{
namespace
{
    std::atomic<ShimLogSinkFn> g_Sink{nullptr};

    void TrimTrailingNewlines(std::string& text)
    {
        while (!text.empty() && (text.back() == '\r' || text.back() == '\n'))
            text.pop_back();
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

    void WriteFormattedMessage(LogLevel level, const char* component,
                               const std::string& formatted)
    {
        std::string line = formatted;
        TrimTrailingNewlines(line);
        if (line.empty())
            line = "<empty>";

        const ShimLogSinkFn sink = g_Sink.load(std::memory_order_acquire);
        if (sink != nullptr)
        {
            sink(static_cast<uint32_t>(level), component, line.c_str());
            return;
        }

        // No sink yet: the line still reaches a debugger, but no file. This
        // is the window before BZPlugin_Load installs the bridge, and it is
        // deliberately not an error -- dropping a diagnostic is better than
        // a second module opening openshim.log behind the owner's back.
#ifdef _WIN32
        char buffer[4608] = {};
        _snprintf_s(buffer, _TRUNCATE, "BZR-OpenShim [no-sink] [%s] %s\n",
                    component ? component : "shim", line.c_str());
        OutputDebugStringA(buffer);
#endif
    }
}

    void SetShimLogSink(ShimLogSinkFn sink)
    {
        g_Sink.store(sink, std::memory_order_release);
    }

    ShimLogSinkFn GetShimLogSink()
    {
        return g_Sink.load(std::memory_order_acquire);
    }

    void LogShimVA(LogLevel level, const char* component, const char* fmt, va_list args)
    {
        WriteFormattedMessage(level, component, FormatAnsi(fmt, args));
    }

    void LogShimVW(LogLevel level, const char* component, const wchar_t* fmt, va_list args)
    {
        WriteFormattedMessage(level, component, FormatWideToUtf8(fmt, args));
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
