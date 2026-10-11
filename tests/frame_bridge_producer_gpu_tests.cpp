#include "frame_bridge_producer.h"
#include "test_check.h"

int main()
{
    using namespace BZROpenShim::FrameBridge;
    using Microsoft::WRL::ComPtr;
    using OpenShimTest::Check;
    using OpenShimTest::Require;
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    D3D_FEATURE_LEVEL level{};
    Require(SUCCEEDED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        0, nullptr, 0, D3D11_SDK_VERSION, &device, &level, &context)), "create hardware D3D11 device");
    D3D11_TEXTURE2D_DESC desc{};
    desc.Width = 64;
    desc.Height = 32;
    desc.MipLevels = desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_RENDER_TARGET;
    ComPtr<ID3D11Texture2D> texture;
    Require(SUCCEEDED(device->CreateTexture2D(&desc, nullptr, &texture)), "create source texture");
    Producer producer;
    Require(SUCCEEDED(producer.Start(device.Get(), desc)), "start producer");
    HANDLE mapping = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, MappingName(GetCurrentProcessId()).c_str());
    Require(mapping != nullptr, "open consumer view");
    auto* frame = static_cast<SharedFrame*>(MapViewOfFile(mapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedFrame)));
    Require(frame != nullptr && ValidDescriptor(*frame, GetCurrentProcessId()), "valid live descriptor");
    Require(producer.Publish(texture.Get()) == S_OK, "publish first frame");
    Check(producer.Publish(texture.Get()) == S_FALSE, "busy mailbox skips capture without waiting");
    Check(ReadInterlocked(frame->slotState) == static_cast<LONG>(SlotState::Ready), "skipped capture preserves published ownership");

    D3D11_TEXTURE2D_DESC resized = desc;
    resized.Width *= 2;
    ComPtr<ID3D11Texture2D> changed;
    Require(SUCCEEDED(device->CreateTexture2D(&resized, nullptr, &changed)), "create resized texture");
    Check(producer.Publish(changed.Get()) == DXGI_ERROR_UNSUPPORTED, "resize ends capture instead of reusing live resources");
    Check(!producer.Active() && ReadInterlocked(frame->active) == 0, "stop is visible through consumer's retained mapping");
    Check(producer.Start(device.Get(), desc) == HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS),
        "refuse a new session while an old reader holds the descriptor name");
    Check(ReadInterlocked(frame->active) == 0, "failed restart does not overwrite retained metadata");
    UnmapViewOfFile(frame);
    CloseHandle(mapping);
    Check(producer.Start(device.Get(), desc) == S_OK, "restart succeeds after old reader closes");
    producer.Stop();
    producer.Stop();
    desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
    Check(producer.Start(device.Get(), desc) == E_INVALIDARG && !producer.Active(), "reject unsupported HDR without leaving an active session");
    return OpenShimTest::ExitCode();
}
