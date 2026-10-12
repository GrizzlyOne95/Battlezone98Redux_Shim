#include "frame_bridge_producer.h"
#include <cstdio>
#include <vector>
#include <cstdlib>

int main(int argc, char** argv)
{
    using namespace BZROpenShim::FrameBridge;
    using Microsoft::WRL::ComPtr;
    const DWORD seconds = argc > 1 ? static_cast<DWORD>(std::strtoul(argv[1], nullptr, 10)) : 20;
    bool msaa = false;
    bool padded = false;
    bool bgra = false;
    bool depthEnabled = false;
    bool motionFixture = false;
    for (int i = 2; i < argc; ++i)
    {
        const std::string arg(argv[i]);
        if (arg == "--msaa") msaa = true;
        else if (arg == "--padded") padded = true;
        else if (arg == "--bgra") bgra = true;
        else if (arg == "--depth") depthEnabled = true;
        else if (arg == "--motion-fixture") { depthEnabled = true; motionFixture = true; }
        else return 2;
    }
    if (seconds == 0 || seconds > 300) return 2;
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    D3D_FEATURE_LEVEL level{};
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        0, nullptr, 0, D3D11_SDK_VERSION, &device, &level, &context);
    D3D11_TEXTURE2D_DESC desc{};
    desc.Width = padded ? 333u : 320u;
    desc.Height = padded ? 181u : 180u;
    desc.MipLevels = desc.ArraySize = 1;
    desc.Format = bgra ? DXGI_FORMAT_B8G8R8A8_UNORM : DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc = {msaa ? 4u : 1u, 0};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_RENDER_TARGET;
    ComPtr<ID3D11Texture2D> source;
    ComPtr<ID3D11RenderTargetView> rtv;
    if (SUCCEEDED(hr)) hr = device->CreateTexture2D(&desc, nullptr, &source);
    if (SUCCEEDED(hr)) hr = device->CreateRenderTargetView(source.Get(), nullptr, &rtv);
    ComPtr<ID3D11Texture2D> depth;
    ComPtr<ID3D11DepthStencilView> dsv;
    if (SUCCEEDED(hr) && depthEnabled)
    {
        auto depthDesc = desc;
        depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        hr = device->CreateTexture2D(&depthDesc, nullptr, &depth);
        if (SUCCEEDED(hr)) hr = device->CreateDepthStencilView(depth.Get(), nullptr, &dsv);
    }
    Producer producer;
    if (SUCCEEDED(hr)) hr = producer.Start(device.Get(), desc, depthEnabled);
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
        if (dsv) context->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
            static_cast<float>(id) / 1024.0f, 0);
        // Synthetic camera is test data only. Its translation encodes the same
        // ID as GPU color/depth so the reader can detect stale camera metadata.
        CameraSnapshot camera{};
        if (depthEnabled)
        {
            camera.status = static_cast<std::uint32_t>(CameraStatus::Observed);
            camera.matrixSource = static_cast<std::uint32_t>(CameraMatrixSource::Synthetic);
            camera.width = desc.Width; camera.height = desc.Height;
            camera.cameraIdentity = 1;
            std::snprintf(camera.name, sizeof(camera.name), "%s", motionFixture ? "SyntheticMotionCamera" : "SyntheticFrameCamera");
            camera.view[0] = camera.view[5] = camera.view[10] = camera.view[15] = 1;
            camera.view[3] = motionFixture ? static_cast<float>(id) / 1000.0f : static_cast<float>(id);
            camera.nearClip = 0.1f; camera.farClip = 1000;
            const float q = camera.farClip / (camera.farClip - camera.nearClip);
            camera.projection[0] = 2.0f * static_cast<float>(desc.Height) / static_cast<float>(desc.Width);
            camera.projection[5] = 2;
            camera.projection[10] = -q;
            camera.projection[11] = -q * camera.nearClip;
            camera.projection[14] = -1;
            LARGE_INTEGER qpc{};
            QueryPerformanceCounter(&qpc);
            camera.observationQpc = qpc.QuadPart;
        }
        hr = producer.Publish(source.Get(), depth.Get(), DepthReduction::Minimum, &camera);
        if (FAILED(hr)) { std::fprintf(stderr, "publish failed: 0x%08lx\n", static_cast<unsigned long>(hr)); return 1; }
        if (hr == S_OK) ++published; else ++skipped;
        Sleep(8);
    }
    std::printf("SOURCE published=%u skipped=%u\n", published, skipped);
    return published > 0 ? 0 : 1;
}
