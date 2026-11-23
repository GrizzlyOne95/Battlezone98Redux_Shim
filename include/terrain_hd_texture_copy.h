#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

namespace BZROpenShim::TerrainHd
{
inline bool BlockCompressed(DXGI_FORMAT format)
{
    return (format >= DXGI_FORMAT_BC1_TYPELESS && format <= DXGI_FORMAT_BC5_SNORM) ||
        (format >= DXGI_FORMAT_BC6H_TYPELESS && format <= DXGI_FORMAT_BC7_UNORM_SRGB);
}

// Ogre 1.10 D3D11Texture::_create2DTex subtracts two levels from explicit
// BC requests. Match an already-loaded source, then still verify real GPU
// descriptors in CopyTextureSlice. Single-level textures need no adjustment.
inline int OgreArrayMipRequest(UINT additionalMips, DXGI_FORMAT format)
{
    return int(additionalMips + (BlockCompressed(format) && additionalMips ? 2u : 0u));
}

// Paint control (blend weight) arrays: any uncompressed format, or
// BC7_UNORM when nothing rewrites the texels. Live paint uploads raw RGBA
// over the slices, so it keeps them uncompressed. BC1-5 are too coarse for
// weights, and SRGB would curve them.
inline bool ControlFormatAccepted(DXGI_FORMAT format, bool liveRewrite)
{
    if (!BlockCompressed(format)) return true;
    return format == DXGI_FORMAT_BC7_UNORM && !liveRewrite;
}

inline const char* ControlFormatName(DXGI_FORMAT format)
{
    switch (format)
    {
    case DXGI_FORMAT_BC7_UNORM: return "BC7_UNORM";
    case DXGI_FORMAT_R8G8B8A8_UNORM: return "R8G8B8A8_UNORM";
    case DXGI_FORMAT_B8G8R8A8_UNORM: return "B8G8R8A8_UNORM";
    default: return "other";
    }
}

// GPU bytes of a 2D array with every listed mip: 16 bytes per 4x4 block for
// BC formats (8 for BC1/BC4), otherwise 4 bytes per texel. Log-only estimate.
inline unsigned long long ArrayBytes(DXGI_FORMAT format, UINT width, UINT height, UINT mips, UINT slices)
{
    const bool bc = BlockCompressed(format);
    const bool half = (format >= DXGI_FORMAT_BC1_TYPELESS && format <= DXGI_FORMAT_BC1_UNORM_SRGB) ||
        (format >= DXGI_FORMAT_BC4_TYPELESS && format <= DXGI_FORMAT_BC4_SNORM);
    unsigned long long total = 0;
    for (UINT mip = 0; mip < mips; ++mip)
    {
        const UINT w = width >> mip ? width >> mip : 1, h = height >> mip ? height >> mip : 1;
        total += bc ? 1ull * ((w + 3) / 4) * ((h + 3) / 4) * (half ? 8 : 16) : 4ull * w * h;
    }
    return total * slices;
}

// Manifest slices that hold paint control maps: slice 4 of each 9-slice
// bank, and slice 4 of the diffuse-and-control-only 5-slice form.
inline std::vector<UINT> PaintControlSlices(UINT sliceCount)
{
    if (sliceCount == 5 || sliceCount == 9) return {4};
    if (sliceCount == 18) return {4, 13};
    return {};
}

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
