#pragma once

namespace BZROpenShim
{
    // Starts the opt-in, read-only Direct3D 11 color-space diagnostic.
    // Enabled by OPENSHIM_TRACE_DX11_COLORSPACE=1 or:
    //
    //   [Diagnostics]
    //   TraceDX11ColorSpace = 1
    //
    // in openshim.ini. The probe never changes Ogre gamma state, texture
    // formats, shader constants, or render-target formats. If DX11 is not the
    // active renderer, it times out without installing any D3D11 hooks.
    void InitializeDx11ColorSpaceDiagnostic();

    // Stops only the short-lived module-discovery worker if it is still
    // running. Runtime observation hooks intentionally remain process-lifetime
    // because they wrap D3D11 objects owned by Ogre.
    void ShutdownDx11ColorSpaceDiagnostic();
}
