#pragma once
#include <d3d11.h>
#include <wrl/client.h>

namespace BZROpenShim::TerrainHd
{
// Copy explicit 2D mip subresources to one array slice. Ogre's pixel-buffer
// blit may invoke mip generation and is not a safe array upload primitive in
// the released DX11 backend. This path never rescales or generates mipmaps.
inline bool CopyTextureSlice(ID3D11Texture2D* destination, ID3D11Texture2D* source,
    UINT slice, UINT width, UINT height, UINT mipmaps)
{
    if (!destination || !source || !width || !height || mipmaps >= 15) return false;
    D3D11_TEXTURE2D_DESC src = {}, dst = {};
    source->GetDesc(&src); destination->GetDesc(&dst);
    if (src.Width != width || dst.Width != width || src.Height != height || dst.Height != height ||
        src.MipLevels != mipmaps + 1 || dst.MipLevels != src.MipLevels ||
        src.ArraySize != 1 || slice >= dst.ArraySize || src.Format != dst.Format ||
        src.SampleDesc.Count != 1 || dst.SampleDesc.Count != 1 ||
        src.SampleDesc.Quality != 0 || dst.SampleDesc.Quality != 0 ||
        dst.Usage != D3D11_USAGE_DEFAULT) return false;
    Microsoft::WRL::ComPtr<ID3D11Device> srcDevice, dstDevice;
    source->GetDevice(&srcDevice); destination->GetDevice(&dstDevice);
    if (!srcDevice || srcDevice.Get() != dstDevice.Get()) return false;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    srcDevice->GetImmediateContext(&context);
    if (!context) return false;
    for (UINT mip = 0; mip < src.MipLevels; ++mip)
        context->CopySubresourceRegion(destination, D3D11CalcSubresource(mip, slice, dst.MipLevels),
            0, 0, 0, source, D3D11CalcSubresource(mip, 0, src.MipLevels), nullptr);
    return SUCCEEDED(srcDevice->GetDeviceRemovedReason());
}
}
