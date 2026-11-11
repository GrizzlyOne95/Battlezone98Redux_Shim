#pragma once

namespace BZROpenShim
{
    // Graphics options "Full Screen" row with a third value, Borderless
    // (src/patches/fullscreen_mode_choice.cpp). DX11 only; DX9 keeps the
    // stock two values. Borderless = stock fullscreen on plus
    // [Graphics] BorderlessFullscreen = 1 (read by dxgi_flip_model.cpp at
    // startup, so switching into or out of it asks for a restart).
    //
    // OPENSHIM_DISABLE_FULLSCREEN_MODE_CHOICE=1 turns it off.
    void InitializeFullscreenModeChoice();
}
