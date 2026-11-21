#pragma once
// Single-player player paint ([SinglePlayer] PlayerPaint, Docs/SP_PLAYER_PAINT.md).
// Render-only: the local player's own ship gets a per-variant clone of its
// materials whose en-high passes bind a team mask and set teamPaint. Other
// units keep stock paint. Off in network games and outside DX11 Enhanced.

namespace BZROpenShim::SpPlayerPaint
{
    // Options-menu change (any thread): the frame tick re-reads the ini.
    void RequestReload();
}

namespace BZROpenShim
{
    // World render-queue hook (bzr_hooks.cpp): evaluates the mission at its
    // first world render and installs the frame listener once.
    void SpPlayerPaintRenderFrameTick();
    void SpPlayerPaintNotifyMissionRunStateChanged(bool running);
    void SpPlayerPaintNotifySceneEntitiesDestroyed();
    void SpPlayerPaintSetSceneTeardownSeam(bool installed);
}
