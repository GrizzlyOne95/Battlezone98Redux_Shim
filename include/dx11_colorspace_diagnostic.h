#pragma once

struct ID3D11Device;

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
    // or OPENSHIM_TERRAIN_RENDER_PROBE=1. Observers leave render state unchanged;
    // the separate opt-in height path binds/restores DS t127 only for its exact
    // owned domain shaders. If DX11 is not active, discovery times out
    // without installing hooks.
    void InitializeDx11ColorSpaceDiagnostic();

    // Stops only the short-lived module-discovery worker if it is still
    // running. Runtime observation hooks intentionally remain process-lifetime
    // because they wrap D3D11 objects owned by Ogre.
    void ShutdownDx11ColorSpaceDiagnostic();

    // The import observers miss a device that Ogre creates between the D3D11
    // renderer's load and the discovery poll. The height path calls this with
    // its live device so the owned DSSetShader seam is installed late instead
    // of the binding declining. No-op unless the height binding was requested.
    void EnsureTerrainHeightDomainHook(ID3D11Device* device);
}
