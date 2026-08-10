#pragma once

namespace BZROpenShim
{
    // Starts the shared, opt-in, read-only Direct3D 11 diagnostics bootstrap.
    // The color-space observer is enabled by
    // OPENSHIM_TRACE_DX11_COLORSPACE=1 or:
    //
    //   [Diagnostics]
    //   TraceDX11ColorSpace = 1
    //
    // The terrain construction observer independently uses:
    //
    //   [Diagnostics]
    //   TerrainRenderProbe = 1
    //
    // or OPENSHIM_TERRAIN_RENDER_PROBE=1. Both observers leave Ogre and D3D11
    // render state unchanged. If DX11 is not active, discovery times out
    // without installing hooks.
    void InitializeDx11ColorSpaceDiagnostic();

    // Stops only the short-lived module-discovery worker if it is still
    // running. Runtime observation hooks intentionally remain process-lifetime
    // because they wrap D3D11 objects owned by Ogre.
    void ShutdownDx11ColorSpaceDiagnostic();
}
