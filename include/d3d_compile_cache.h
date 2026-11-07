#pragma once

namespace BZROpenShim
{
    // Redirects D3DCompile (imported by RenderSystem_Direct3D11.dll) through a
    // content-addressed DXBC disk cache and keeps the window pumped during
    // slow compiles. Safe to call repeatedly; does nothing until the renderer
    // is loaded.
    void InstallD3DCompileCacheIfPossible();
}
