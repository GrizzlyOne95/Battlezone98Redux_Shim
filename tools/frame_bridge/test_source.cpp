#include "frame_bridge_producer.h"
#include <cstdio>
#include <vector>
#include <cstdlib>

int main(int argc, char** argv)
{
    using namespace BZROpenShim::FrameBridge;
    using Microsoft::WRL::ComPtr;
    const DWORD seconds = argc > 1 ? static_cast<DWORD>(std::strtoul(argv[1], nullptr, 10)) : 20;
    const bool msaa = argc > 2 && std::string(argv[2]) == "--msaa";
    if (seconds == 0 || seconds > 300) return 2;
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    D3D_FEATURE_LEVEL level{};
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        0, nullptr, 0, D3D11_SDK_VERSION, &device, &level, &context);
    D3D11_TEXTURE2D_DESC desc{};
    desc.Width = 320;
    desc.Height = 180;
    desc.MipLevels = desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc = {msaa ? 4u : 1u, 0};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_RENDER_TARGET;
    ComPtr<ID3D11Texture2D> source;
    ComPtr<ID3D11RenderTargetView> rtv;
    if (SUCCEEDED(hr)) hr = device->CreateTexture2D(&desc, nullptr, &source);
    if (SUCCEEDED(hr)) hr = device->CreateRenderTargetView(source.Get(), nullptr, &rtv);
    Producer producer;
    if (SUCCEEDED(hr)) hr = producer.Start(device.Get(), desc);
    if (FAILED(hr)) { std::fprintf(stderr, "source initialization failed: 0x%08lx\n", static_cast<unsigned long>(hr)); return 1; }
    std::printf("SOURCE pid=%lu pointer_bits=%zu sample_count=%u\n", GetCurrentProcessId(), sizeof(void*) * 8, desc.SampleDesc.Count);
    std::fflush(stdout);
    const ULONGLONG end = GetTickCount64() + seconds * 1000ull;
    unsigned published = 0;
    unsigned skipped = 0;
    while (GetTickCount64() < end)
    {
        // Each successful mailbox publication has a unique byte-exact color.
        // Skipped frames retain the same ID, so the helper can check GPU data
        // against metadata and detect stale frames or missing synchronization.
        const unsigned id = published + 1;
        const float color[4] = {static_cast<float>(id & 255) / 255.0f,
            static_cast<float>((id >> 8) & 255) / 255.0f, 0.25f, 1.0f};
        context->ClearRenderTargetView(rtv.Get(), color);
        hr = producer.Publish(source.Get());
        if (FAILED(hr)) { std::fprintf(stderr, "publish failed: 0x%08lx\n", static_cast<unsigned long>(hr)); return 1; }
        if (hr == S_OK) ++published; else ++skipped;
        Sleep(8);
    }
    std::printf("SOURCE published=%u skipped=%u\n", published, skipped);
    return published > 0 ? 0 : 1;
}
