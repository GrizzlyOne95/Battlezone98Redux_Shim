// game_log_path.h
// BZR Open Shim - where the game's log files go.
//
// The minimal primitive the bootstrap needs from the logging code. It is a
// separate header (and a separate translation unit) so the bootstrap's
// CreateFile wrapper can route the stock game logs into logs\ without
// compiling shim_log.cpp, which owns a file handle, an init-once and a lock
// that must exist exactly once in the process.
//
// Pure and stateless: safe for more than one module to compile.
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <string>

namespace BZROpenShim
{
    // Sanitizes log filenames against relative path traversal, invalid characters,
    // control characters, Windows reserved device names, and trailing dots/spaces.
    std::string SanitizeLogFilename(const char* fileName);

    // Returns <game executable directory>\logs\<fileName>, creating the
    // directory when possible and falling back to the game root on failure.
    std::string GetGameLogPath(const char* fileName);
}
