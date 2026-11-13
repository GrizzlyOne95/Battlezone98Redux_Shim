// quicksave.h
// BZR Open Shim - Ctrl+F5 QuickSave / Ctrl+F9 QuickLoad (single player)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim::QuickSave
{
    // Save\<kSlotStem>.sav and Save\<kSlotStem>.label.txt.
    inline constexpr char kSlotStem[] = "quick";

    // Reads [QuickSave] QuickSaveEnabled (default 1) from the given ini.
    // Called from the AutoSave config load, which owns the shared hook.
    void LoadConfig(const char* iniPath);

    bool IsEnabled();

    // Runs on the main thread from the AutoSave world-update hook: installs
    // the key filters on first use and executes a pending save/load request.
    void Tick();
}
