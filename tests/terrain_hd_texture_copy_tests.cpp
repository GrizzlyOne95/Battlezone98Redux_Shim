#include "terrain_hd_texture_copy.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>
using Microsoft::WRL::ComPtr;
static void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
static void ok(HRESULT result) { check(SUCCEEDED(result), "D3D11 operation failed"); }

static ComPtr<ID3D11Texture2D> makeTexture(ID3D11Device* device, UINT size, UINT mips, UINT slices, uint8_t base)
{
    std::vector<std::vector<uint8_t>> pixels(mips * slices);
    std::vector<D3D11_SUBRESOURCE_DATA> data(mips * slices);
    for (UINT slice = 0; slice < slices; ++slice)
    for (UINT mip = 0; mip < mips; ++mip)
    {
        const UINT side = (std::max)(1u, size >> mip);
        auto& bytes = pixels[D3D11CalcSubresource(mip, slice, mips)];
        bytes.resize(side * side * 4);
        for (UINT y = 0; y < side; ++y)
        for (UINT x = 0; x < side; ++x)
        {
            const size_t offset = (y * side + x) * 4;
            bytes[offset] = base ? uint8_t(base + x % 17) : 0;
            bytes[offset + 1] = base ? uint8_t(mip * 7) : 0;
            bytes[offset + 2] = base ? uint8_t(y % 19) : 0;
            bytes[offset + 3] = base ? 255 : 0;
        }
        data[D3D11CalcSubresource(mip, slice, mips)] = {bytes.data(), side * 4, side * side * 4};
    }
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = desc.Height = size; desc.MipLevels = mips; desc.ArraySize = slices;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT; desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    ComPtr<ID3D11Texture2D> texture;
    ok(device->CreateTexture2D(&desc, data.data(), &texture));
    return texture;
}

static void qualify(ID3D11Device* device, ID3D11DeviceContext* context, UINT size, UINT mips, UINT slices)
{
    auto a = makeTexture(device, size, mips, 1, 10);
    auto b = makeTexture(device, size, mips, 1, 90);
    auto array = makeTexture(device, size, mips, slices, 0);
    check(BZROpenShim::TerrainHd::CopyTextureSlice(array.Get(), a.Get(), slices - 1, size, size, mips - 1), "last slice copy declined");
    check(BZROpenShim::TerrainHd::CopyTextureSlice(array.Get(), b.Get(), 0, size, size, mips - 1), "first slice copy declined");
    check(!BZROpenShim::TerrainHd::CopyTextureSlice(array.Get(), a.Get(), slices, size, size, mips - 1), "out of bounds slice accepted");
    check(!BZROpenShim::TerrainHd::CopyTextureSlice(array.Get(), a.Get(), 0, size + 1, size, mips - 1), "wrong dimensions accepted");
    check(!BZROpenShim::TerrainHd::CopyTextureSlice(array.Get(), a.Get(), 0, size, size, mips), "wrong mip count accepted");
    check(!BZROpenShim::TerrainHd::CopyTextureSlice(array.Get(), nullptr, 0, size, size, mips - 1), "null source accepted");
    D3D11_TEXTURE2D_DESC desc; array->GetDesc(&desc);
    desc.Usage = D3D11_USAGE_STAGING; desc.BindFlags = 0; desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    ComPtr<ID3D11Texture2D> staging;
    ok(device->CreateTexture2D(&desc, nullptr, &staging));
    context->CopyResource(staging.Get(), array.Get());
    for (UINT slice : {0u, 1u, slices - 1})
    for (UINT mip = 0; mip < mips; ++mip)
    {
        D3D11_MAPPED_SUBRESOURCE mapped;
        const UINT sub = D3D11CalcSubresource(mip, slice, mips);
        ok(context->Map(staging.Get(), sub, D3D11_MAP_READ, 0, &mapped));
        const UINT side = (std::max)(1u, size >> mip);
        bool matched = true;
        for (UINT y : {0u, side - 1})
        for (UINT x : {0u, side - 1})
        {
            const auto* pixel = static_cast<const uint8_t*>(mapped.pData) + y * mapped.RowPitch + x * 4;
            const uint8_t base = slice == 0 ? 90 : slice == slices - 1 ? 10 : 0;
            matched &= pixel[0] == (base ? uint8_t(base + x % 17) : 0) &&
                pixel[1] == (base ? uint8_t(mip * 7) : 0) &&
                pixel[2] == (base ? uint8_t(y % 19) : 0) && pixel[3] == (base ? 255 : 0);
        }
        context->Unmap(staging.Get(), sub);
        check(matched, "array slice/mip content or untouched neighbour changed");
    }
}

// DXT5 (BC3) block data: 16 bytes per 4x4 block, blocks seeded per slice
// and mip so a copy to the wrong subresource shows.
static ComPtr<ID3D11Texture2D> makeBc3(ID3D11Device* device, UINT size, UINT mips, UINT slices, uint8_t base)
{
    std::vector<std::vector<uint8_t>> blocks(mips * slices);
    std::vector<D3D11_SUBRESOURCE_DATA> data(mips * slices);
    for (UINT slice = 0; slice < slices; ++slice)
    for (UINT mip = 0; mip < mips; ++mip)
    {
        const UINT across = (std::max)(1u, ((std::max)(1u, size >> mip) + 3) / 4);
        auto& bytes = blocks[D3D11CalcSubresource(mip, slice, mips)];
        bytes.resize(across * across * 16);
        for (size_t i = 0; i < bytes.size(); ++i) bytes[i] = base ? uint8_t(base + mip * 3 + i % 13) : 0;
        data[D3D11CalcSubresource(mip, slice, mips)] = {bytes.data(), across * 16, across * across * 16};
    }
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = desc.Height = size; desc.MipLevels = mips; desc.ArraySize = slices;
    desc.Format = DXGI_FORMAT_BC3_UNORM; desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT; desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    ComPtr<ID3D11Texture2D> texture;
    ok(device->CreateTexture2D(&desc, data.data(), &texture));
    return texture;
}

// Paint colour/normal arrays may be DXT5 with full mips; control arrays stay
// uncompressed. Each array copies only slices of its own format.
static void qualifyCompressed(ID3D11Device* device, ID3D11DeviceContext* context)
{
    using namespace BZROpenShim::TerrainHd;
    const UINT size = 16, mips = 5, slices = 9;
    auto colour = makeBc3(device, size, mips, 1, 40);
    auto array = makeBc3(device, size, mips, slices, 0);
    check(CopyTextureSlice(array.Get(), colour.Get(), 8, size, size, mips - 1), "BC3 slice copy declined");
    auto png = makeTexture(device, size, mips, 1, 10);
    check(!CopyTextureSlice(array.Get(), png.Get(), 5, size, size, mips - 1), "uncompressed slice accepted into a BC3 array");
    auto control = makeTexture(device, size, mips, 2, 0);
    check(!CopyTextureSlice(control.Get(), colour.Get(), 0, size, size, mips - 1), "BC3 slice accepted into an uncompressed control array");
    check(CopyTextureSlice(control.Get(), png.Get(), 1, size, size, mips - 1), "control slice copy declined");
    // A level-0-only control array takes just the top level of a mipped source.
    auto topOnly = makeTexture(device, size, 1, 2, 0);
    check(CopyTextureSlice(topOnly.Get(), png.Get(), 1, size, size, mips - 1, 0), "level-0 control copy declined");
    check(!CopyTextureSlice(topOnly.Get(), png.Get(), 1, size, size, mips - 1), "full chain accepted into a level-0 array");
    check(!CopyTextureSlice(topOnly.Get(), png.Get(), 1, size, size, mips - 1, 1), "wrong array mip count accepted");
    check(!CopyTextureSlice(control.Get(), png.Get(), 1, size, size, mips - 1, mips), "more array levels than source accepted");
    {
        D3D11_TEXTURE2D_DESC topDesc; topOnly->GetDesc(&topDesc);
        topDesc.Usage = D3D11_USAGE_STAGING; topDesc.BindFlags = 0; topDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        ComPtr<ID3D11Texture2D> topStaging;
        ok(device->CreateTexture2D(&topDesc, nullptr, &topStaging));
        context->CopyResource(topStaging.Get(), topOnly.Get());
        D3D11_MAPPED_SUBRESOURCE mapped;
        ok(context->Map(topStaging.Get(), D3D11CalcSubresource(0, 1, 1), D3D11_MAP_READ, 0, &mapped));
        const auto* last = static_cast<const uint8_t*>(mapped.pData) + (size - 1) * mapped.RowPitch + (size - 1) * 4;
        const bool matched = last[0] == uint8_t(10 + (size - 1) % 17) && last[1] == 0 &&
            last[2] == uint8_t((size - 1) % 19) && last[3] == 255;
        context->Unmap(topStaging.Get(), D3D11CalcSubresource(0, 1, 1));
        check(matched, "level-0 control copy content wrong");
    }
    D3D11_TEXTURE2D_DESC desc; array->GetDesc(&desc);
    desc.Usage = D3D11_USAGE_STAGING; desc.BindFlags = 0; desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    ComPtr<ID3D11Texture2D> staging;
    ok(device->CreateTexture2D(&desc, nullptr, &staging));
    context->CopyResource(staging.Get(), array.Get());
    for (UINT slice : {5u, 8u})
    for (UINT mip = 0; mip < mips; ++mip)
    {
        D3D11_MAPPED_SUBRESOURCE mapped;
        const UINT sub = D3D11CalcSubresource(mip, slice, mips);
        ok(context->Map(staging.Get(), sub, D3D11_MAP_READ, 0, &mapped));
        const UINT across = (std::max)(1u, ((std::max)(1u, size >> mip) + 3) / 4);
        bool matched = true;
        for (UINT row = 0; row < across; ++row)
        for (UINT i = 0; i < across * 16; ++i)
        {
            const uint8_t expected = slice == 8 ? uint8_t(40 + mip * 3 + (row * across * 16 + i) % 13) : 0;
            matched &= static_cast<const uint8_t*>(mapped.pData)[row * mapped.RowPitch + i] == expected;
        }
        context->Unmap(staging.Get(), sub);
        check(matched, "BC3 slice/mip blocks or untouched neighbour changed");
    }
}

int main()
{
    try
    {
        check(BZROpenShim::TerrainHd::OgreArrayMipRequest(8, DXGI_FORMAT_BC1_UNORM) == 10,
            "released Ogre BC mip subtraction not compensated");
        check(BZROpenShim::TerrainHd::OgreArrayMipRequest(0, DXGI_FORMAT_BC1_UNORM) == 0 &&
            BZROpenShim::TerrainHd::OgreArrayMipRequest(10, DXGI_FORMAT_R8G8B8A8_UNORM) == 10,
            "single-level or uncompressed mip request changed");
        check(BZROpenShim::TerrainHd::OgreArrayMipRequest(11, DXGI_FORMAT_BC3_UNORM) == 13 &&
            BZROpenShim::TerrainHd::BlockCompressed(DXGI_FORMAT_BC3_UNORM) &&
            !BZROpenShim::TerrainHd::BlockCompressed(DXGI_FORMAT_B8G8R8A8_UNORM), "DXT5 paint array mip request wrong");
        using Slices = std::vector<UINT>;
        check(BZROpenShim::TerrainHd::PaintControlSlices(5) == Slices{4} &&
            BZROpenShim::TerrainHd::PaintControlSlices(9) == Slices{4} &&
            BZROpenShim::TerrainHd::PaintControlSlices(18) == Slices{4, 13} &&
            BZROpenShim::TerrainHd::PaintControlSlices(7).empty(), "paint control slices wrong");
        check(BZROpenShim::TerrainHd::ArrayBytes(DXGI_FORMAT_B8G8R8A8_UNORM, 2048, 2048, 1, 2) == 32ull << 20 &&
            BZROpenShim::TerrainHd::ArrayBytes(DXGI_FORMAT_B8G8R8A8_UNORM, 2048, 2048, 12, 2) == 44739240ull &&
            BZROpenShim::TerrainHd::ArrayBytes(DXGI_FORMAT_BC3_UNORM, 4, 4, 3, 1) == 48 &&
            BZROpenShim::TerrainHd::ArrayBytes(DXGI_FORMAT_BC1_UNORM, 8, 8, 1, 1) == 32, "array byte estimate wrong");
        ComPtr<ID3D11Device> device; ComPtr<ID3D11DeviceContext> context;
        ok(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 0,
            D3D11_SDK_VERSION, &device, nullptr, &context));
        qualify(device.Get(), context.Get(), 512, 10, 3);
        qualify(device.Get(), context.Get(), 16, 5, 256);
        qualifyCompressed(device.Get(), context.Get());
        ComPtr<ID3D11Device> other; ComPtr<ID3D11DeviceContext> otherContext;
        ok(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 0,
            D3D11_SDK_VERSION, &other, nullptr, &otherContext));
        auto source = makeTexture(other.Get(), 16, 5, 1, 10);
        auto destination = makeTexture(device.Get(), 16, 5, 3, 0);
        check(!BZROpenShim::TerrainHd::CopyTextureSlice(destination.Get(), source.Get(), 0, 16, 16, 4), "cross-device copy accepted");
        std::cout << "PASS: explicit 512px mips, 256 slices, DXT5 slices, per-array formats, control slices, level-0 control arrays, byte estimates, preserved neighbours and invalid contracts\n";
        return 0;
    }
    catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
