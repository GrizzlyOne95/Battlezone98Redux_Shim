// autosave_notice.h
// BZR Open Shim - "Game autosaved." HUD notice
//
// Copyright (C) 2025-2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim::AutoSaveNotice
{
    // Starts the notice (about three seconds) after a successful autosave.
    // Game thread only. On first use it binds the engine rows and detours the
    // scrap/pilot gauge draw; if any row is missing or mismatched it logs once
    // and every later call does nothing. It never affects the save.
    void Show() noexcept;

    // Ends a notice early (mission change). Safe from any thread.
    void Hide() noexcept;
}
