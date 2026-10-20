#pragma once

namespace BZROpenShim
{
    // Opt-in DXGI flip-model presentation for Ogre's D3D11 render window
    // (src/patches/dxgi_flip_model.cpp). Off by default:
    //
    //   [Graphics]
    //   DxgiFlipModel = 0
    //
    // OPENSHIM_DXGI_FLIP_MODEL=1 turns it on for one launch (the environment
    // wins over the ini). OPENSHIM_DXGI_FLIP_LATENCY (1-3, default 1) sets the
    // maximum frame latency. Any swap chain the rewrite cannot build is created
    // exactly as Ogre asked; DX9 is untouched.
    void InitializeDxgiFlipModel();
}
