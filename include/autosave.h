// autosave.h
// BZR Open Shim - engine-level single-player autosave support
//
// Copyright (C) 2025-2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // Installs the main-thread autosave service after the normal OpenShim
    // patch set has finished installing. Returns false when the native save
    // routine or the update hook cannot be resolved safely.
    bool InitializeAutoSave();

    // Restores the update hook when possible. Safe to call when autosave was
    // never initialized or was disabled in openshim.ini.
    void ShutdownAutoSave();

    // Services the autosave timer. Normally called by the installed main-thread
    // world-update hook rather than directly by consumers.
    void AutoSaveTick();

    // Re-reads [AutoSave] from openshim.ini and applies Enabled/Interval
    // changes immediately. Returns false if enabling cannot initialize safely.
    bool ReloadAutoSaveConfig();

    enum class MissionSaveResult
    {
        Saved,
        Refused, // gate closed (no mission, pause/shell UI, no AiMission yet)
        Failed,  // SaveGame returned false or faulted, or a fault latch holds
    };

    // One immediate save of the live single-player mission to Save\<stem>.sav
    // plus Save\<stem>.label.txt ("<mission> - <labelSuffix>"), then the HUD
    // notice with noticeText (a string literal). Same gate, AiMission check,
    // fault latch and missionSave-flag handling as the timed autosave; works
    // with AutoSave disabled as long as the service initialized for QuickSave.
    // Main thread only. `reason` is a static string describing the outcome.
    MissionSaveResult SaveMissionNow(
        const char* stem, const char* labelSuffix, const char* noticeText, const char*& reason);

    // True when a single-player mission is live and no pause/shell UI owns
    // the screen: the save gate without its fault latch. Main thread only.
    bool IsMissionLiveForLoad(const char*& reason);
}
