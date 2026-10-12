#include "frame_bridge_producer.h"
#include "test_check.h"

namespace
{
    bool FixtureCamera(BZROpenShim::FrameBridge::CameraSnapshot& camera)
    {
        using namespace BZROpenShim::FrameBridge;
        camera = {};
        camera.status = static_cast<std::uint32_t>(CameraStatus::Observed);
        camera.width = 64; camera.height = 32;
        camera.cameraIdentity = 7; camera.observationQpc = 10;
        camera.view[0] = camera.view[5] = camera.view[10] = camera.view[15] = 1;
        camera.nearClip = 0.1f; camera.farClip = 100;
        camera.projection[0] = 1; camera.projection[5] = 2;
        camera.projection[10] = -100.0f / 99.9f;
        camera.projection[11] = camera.projection[10] * camera.nearClip;
        camera.projection[14] = -1;
        return true;
    }
}

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
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    Require(producer.Start(device.Get(), desc, true) == S_OK, "start color/depth producer");
    mapping = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, MappingName(GetCurrentProcessId()).c_str());
    Require(mapping != nullptr, "open depth consumer metadata");
    frame = static_cast<SharedFrame*>(MapViewOfFile(mapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedFrame)));
    Require(frame != nullptr && frame->depthTextureHandle != 0, "shared depth handle published before active descriptor");
    auto depthDesc = desc;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthDesc.SampleDesc.Count = 4;
    ComPtr<ID3D11Texture2D> depth;
    ComPtr<ID3D11DepthStencilView> depthView;
    Require(SUCCEEDED(device->CreateTexture2D(&depthDesc, nullptr, &depth)), "create MSAA depth without SRV flag");
    Require(SUCCEEDED(device->CreateDepthStencilView(depth.Get(), nullptr, &depthView)), "create source depth view");
    context->ClearDepthStencilView(depthView.Get(), D3D11_CLEAR_DEPTH, 0.25f, 0);
    CameraSnapshot camera{};
    FixtureCamera(camera);
    Require(producer.Publish(texture.Get(), depth.Get(), DepthReduction::Minimum, &camera) == S_OK &&
        ValidDepthFrame(*frame) && ValidCameraFrame(*frame), "publish valid matching color/depth/camera");
    Check(producer.Publish(texture.Get()) == S_FALSE && ValidDepthFrame(*frame) && ValidCameraFrame(*frame) &&
        frame->camera.cameraIdentity == 7, "busy publication preserves depth and camera metadata");
    // This metadata-only reader submits no GPU work and therefore has no GPU
    // reads to wait for before returning the slot.
    const auto acknowledge = [&]() {
        Require(Claim(frame->slotState, static_cast<LONG>(SlotState::Ready), static_cast<LONG>(SlotState::Reading)), "claim metadata slot");
        Exchange(frame->slotState, static_cast<LONG>(SlotState::Free));
    };
    acknowledge();
    Require(producer.Publish(texture.Get()) == S_OK, "publish color with missing depth");
    Check(!ValidDepthFrame(*frame) && !ValidCameraFrame(*frame) && frame->camera.cameraIdentity == 0 &&
        frame->depthStatus == static_cast<std::uint32_t>(DepthStatus::Missing) &&
        frame->depthSourceFormat == 0, "missing frame invalidates previous depth and source metadata");
    acknowledge();
    depthDesc.Format = DXGI_FORMAT_D16_UNORM;
    depthDesc.SampleDesc.Count = 1;
    ComPtr<ID3D11Texture2D> unsupportedDepth;
    Require(SUCCEEDED(device->CreateTexture2D(&depthDesc, nullptr, &unsupportedDepth)), "create unsupported depth format");
    Require(producer.Publish(texture.Get(), unsupportedDepth.Get()) == S_OK, "unsupported depth keeps color capture alive");
    Check(!ValidDepthFrame(*frame) && frame->depthStatus == static_cast<std::uint32_t>(DepthStatus::Unsupported), "unsupported frame rejects stale depth pixels");
    acknowledge();
    Require(producer.Publish(texture.Get(), depth.Get(), DepthReduction::Maximum) == S_OK && ValidDepthFrame(*frame) &&
        frame->depthReduction == 1 && frame->depthSourceSamples == 4, "depth extraction recovers after rejected source");
    acknowledge();
    Exchange(frame->requestedDepthClear, 1);
    producer.BeforeDepthClear(context.Get(), depthView.Get(), D3D11_CLEAR_DEPTH, &FixtureCamera);
    context->ClearDepthStencilView(depthView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
    Require(producer.Publish(texture.Get()) == S_OK && ValidDepthFrame(*frame) &&
        frame->depthCapturedOrdinal == 1 && frame->depthMatchingClears == 1 && ValidCameraFrame(*frame) &&
        frame->camera.clearOrdinal == 1 && frame->camera.stage == 1, "pre-clear snapshot publishes matching camera boundary");
    ComPtr<ID3D11Device1> device1;
    ComPtr<ID3D11Texture2D> sharedDepth;
    Require(SUCCEEDED(device.As(&device1)) && SUCCEEDED(device1->OpenSharedResource1(
        reinterpret_cast<HANDLE>(static_cast<std::uintptr_t>(frame->depthTextureHandle)), IID_PPV_ARGS(&sharedDepth))), "open exported depth for pre-clear pixel check");
    D3D11_TEXTURE2D_DESC readDesc{};
    sharedDepth->GetDesc(&readDesc);
    readDesc.BindFlags = readDesc.MiscFlags = 0;
    readDesc.Usage = D3D11_USAGE_STAGING;
    readDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    ComPtr<ID3D11Texture2D> readback;
    Require(SUCCEEDED(device->CreateTexture2D(&readDesc, nullptr, &readback)), "create snapshot readback");
    context->CopyResource(readback.Get(), sharedDepth.Get());
    D3D11_MAPPED_SUBRESOURCE pixels{};
    Require(SUCCEEDED(context->Map(readback.Get(), 0, D3D11_MAP_READ, 0, &pixels)), "wait for snapshot GPU copy and map");
    Check(*static_cast<const float*>(pixels.pData) > 0.24999f && *static_cast<const float*>(pixels.pData) < 0.25001f,
        "pre-clear captured old depth before source was cleared to one");
    context->Unmap(readback.Get(), 0);
    producer.BeforeDepthClear(context.Get(), depthView.Get(), D3D11_CLEAR_DEPTH);
    Check(ValidDepthFrame(*frame) && frame->depthCapturedOrdinal == 1, "pre-clear observer cannot mutate occupied metadata");
    acknowledge();
    // A publication without a new matching clear must not reuse the snapshot.
    // Clear counting itself is reset by every Publish, including busy skips.
    Check(producer.Publish(texture.Get()) == S_OK && !ValidDepthFrame(*frame) && !ValidCameraFrame(*frame) &&
        frame->camera.cameraIdentity == 0, "pre-clear missing in next frame rejects retained depth and camera");
    producer.Stop();
    Check(ReadInterlocked(frame->active) == 0, "color/depth shutdown is visible to retained consumer");
    UnmapViewOfFile(frame);
    CloseHandle(mapping);
    return OpenShimTest::ExitCode();
}
