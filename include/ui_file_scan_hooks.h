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
    // Suppress counting while the shader fingerprint scans mod sources; that
    // scan is not part of menu Workshop/addon enumeration and must not be
    // misclassified as generic scanning.
    void SetSuppress(bool suppress) noexcept;
} // namespace BZROpenShim::UiFileScan
