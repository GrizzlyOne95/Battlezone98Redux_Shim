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

int main()
{
    try
    {
        ComPtr<ID3D11Device> device; ComPtr<ID3D11DeviceContext> context;
        ok(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 0,
            D3D11_SDK_VERSION, &device, nullptr, &context));
        qualify(device.Get(), context.Get(), 512, 10, 3);
        qualify(device.Get(), context.Get(), 16, 5, 256);
        ComPtr<ID3D11Device> other; ComPtr<ID3D11DeviceContext> otherContext;
        ok(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 0,
            D3D11_SDK_VERSION, &other, nullptr, &otherContext));
        auto source = makeTexture(other.Get(), 16, 5, 1, 10);
        auto destination = makeTexture(device.Get(), 16, 5, 3, 0);
        check(!BZROpenShim::TerrainHd::CopyTextureSlice(destination.Get(), source.Get(), 0, 16, 16, 4), "cross-device copy accepted");
        std::cout << "PASS: explicit 512px mips, 256 slices, preserved neighbours and invalid contracts\n";
        return 0;
    }
    catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
