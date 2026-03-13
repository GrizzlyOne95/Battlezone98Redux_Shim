// patcher.h
// BZR Open Shim - runtime patcher
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once
#include <cstdint>

namespace BZROpenShim
{
    // Expected BZR.exe file version (decimal 301)
    static constexpr uint32_t BZR_EXPECTED_VERSION = 301; // 0x12D

    // Maximum attempts waiting for game bytes to settle before aborting
    static constexpr int PATCH_MAX_RETRIES = 1000;

    // Delay between retries in milliseconds
    static constexpr int PATCH_RETRY_DELAY_MS = 10;

    // -----------------------------------------------------------------------
    // Entry point - called on background thread from DllMain.
    // Mirrors the reference patch startup flow:
    //   1. Opens a patch log
    //   2. Checks BZR.exe file version == 301
    //   3. Polls 0x00868300 until signature matches
    //   4. Applies all patches
    // -----------------------------------------------------------------------
    void RunPatcher(uint32_t shimVersion);

    // Logging helpers for use in other modules
    void Log(const wchar_t* fmt, ...);
    extern "C" void LogHit(const char* name);
}
