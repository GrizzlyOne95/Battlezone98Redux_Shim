#pragma once

namespace BZROpenShim
{
    // DX11 window on the primary monitor (src/patches/d3d11_primary_monitor.cpp).
    // Ogre's D3D11 window picks the monitor nearest (INT_MAX, INT_MAX) when no
    // position is given, which is the bottom-right-most monitor, not the
    // primary one. On by default:
    //
    //   [Graphics]
    //   D3D11PrimaryMonitor = 1
    //
    // OPENSHIM_DISABLE_D3D11_PRIMARY_MONITOR=1 turns it off. DX9 is untouched.
    void InitializeD3D11PrimaryMonitor();
}
