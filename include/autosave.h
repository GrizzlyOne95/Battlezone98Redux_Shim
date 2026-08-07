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

    // Requests an immediate save using the same safety gates as scheduled
    // autosaves. Primarily useful for diagnostics and future UI/bridge work.
    bool TriggerAutoSaveNow();
}
