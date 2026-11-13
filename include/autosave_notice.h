// autosave_notice.h
// BZR Open Shim - "Game autosaved." / "Game quicksaved." HUD notice
//
// Copyright (C) 2025-2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim::AutoSaveNotice
{
    // Starts the notice (about three seconds) after a successful autosave.
    // Game thread only. On first use it installs the shared gauge-draw overlay
    // (hud_gauge_overlay.h); if any row is missing or mismatched it logs once
    // and every later call does nothing. It never affects the save.
    void Show() noexcept;

    // Same notice with other text ("Game quicksaved."). `text` must outlive
    // the notice: pass a string literal.
    void Show(const char* text) noexcept;

    // Ends a notice early (mission change). Safe from any thread.
    void Hide() noexcept;
}
