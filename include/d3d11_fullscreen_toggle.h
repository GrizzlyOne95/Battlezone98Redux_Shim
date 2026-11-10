#pragma once

namespace BZROpenShim
{
    // DX11 Alt-Enter from a window (src/patches/d3d11_fullscreen_toggle.cpp).
    // Stock Ogre loses its fullscreen flag to the resize it triggers itself
    // and leaves a small borderless window. On by default;
    // OPENSHIM_DISABLE_D3D11_FULLSCREEN_FIX=1 turns it off. DX9 is untouched.
    void InitializeD3D11FullscreenToggle();
}
