// hud_visibility.h
// BZR Open Shim - Ctrl+= hides all HUD for screenshots
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// One shared "HUD hidden" flag. Ctrl+= toggles it during live gameplay; it
// also holds the stock show-HUD switch (DAT_008EAAB0) at 0, which removes the
// stock HUD element list, reticle, target camera and sniper scope. OpenShim
// painters and shim-owned HUD meshes check IsHidden(). Resets to visible
// whenever the mission run state changes. See Docs/CONTEXTUAL_HUD.md.

#pragma once

namespace BZROpenShim::HudVisibility
{
    // True while the player has hidden the HUD. Any thread; one atomic load.
    bool IsHidden() noexcept;

    // True while a legacy text editor (in-mission chat, ally prompt) has
    // keyboard focus (LegacyTextEditorFocusLookup). A failed bind or a fault
    // reads as focused, so a key filter leaves the key to the game. Main
    // (window) thread, from key filters.
    bool TextEditorFocused() noexcept;

    // Frame thread (world render-queue tick): installs the key filters once,
    // applies a pending toggle and keeps the stock switch at 0 while hidden.
    void Tick() noexcept;

    // Mission run-state change: shows the HUD again and restores the stock
    // switch. Game thread.
    void ResetMission() noexcept;
}
