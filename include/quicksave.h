// quicksave.h
// BZR Open Shim - QuickSave / QuickLoad (default Ctrl+Home / Ctrl+End, single player)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim::QuickSave
{
    // Save\<kSlotStem>.sav and Save\<kSlotStem>.label.txt.
    inline constexpr char kSlotStem[] = "quick";

    // Reads [QuickSave] QuickSaveEnabled (default 1) and SaveKey / LoadKey
    // (default Ctrl+Home / Ctrl+End; an invalid or unsafe value falls back to
    // the default with a log line) from the given ini.
    // Called from the AutoSave config load, which owns the shared hook.
    void LoadConfig(const char* iniPath);

    bool IsEnabled();

    // The chord text in force for QuickSave (true) or QuickLoad (false).
    const char* ChordText(bool save);

    // Rebinds one action live (main thread). Returns nullptr on success, else
    // the reason the chord was refused (unparseable, unsafe, or equal to the
    // other action's). Does not touch the ini; the caller persists it.
    const char* SetChordText(bool save, const char* text);

    // Runs on the main thread from the AutoSave world-update hook: installs
    // the key filters on first use and executes a pending save/load request.
    void Tick();
}
