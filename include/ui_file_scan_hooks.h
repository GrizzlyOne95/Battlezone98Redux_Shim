#pragma once
// ui_file_scan_hooks.h
// Lightweight Win32 file-enumeration counters for UiPerf [SCAN] attribution.
// Intercepts the file-enumeration path Redux uses when building mod / mission
// lists (FindFirstFileW / FindNextFileW / FindClose plus GetFileAttributes).
// When UiPerformanceLogging is OFF the hooks are not installed and there is no
// overhead.  When ON they aggregate per-root counters and emit a single
// [UIPERF][SCAN] summary at the end of each ModDiscovery scope.
//
// SPDX-License-Identifier: MIT

#include <Windows.h>

namespace BZROpenShim::UiFileScan
{
    void Install() noexcept;
    void Shutdown() noexcept;
} // namespace BZROpenShim::UiFileScan
