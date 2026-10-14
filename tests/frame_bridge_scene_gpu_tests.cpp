#include "frame_bridge_producer.h"
#include "test_check.h"
#include <cstring>

namespace
{
    using namespace BZROpenShim::FrameBridge;
    bool Camera(CameraSnapshot& c)
    {
        c = {}; c.status = static_cast<std::uint32_t>(CameraStatus::Observed);
        c.matrixSource = static_cast<std::uint32_t>(CameraMatrixSource::Synthetic);
        c.width = 67; c.height = 33; c.cameraIdentity = 1; c.observationQpc = 1;
        c.view[0] = c.view[5] = c.view[10] = c.view[15] = 1;
        c.nearClip = 0.1f; c.farClip = 100;
        c.projection[0] = 1; c.projection[5] = 2; c.projection[10] = -100.0f / 99.9f;
        c.projection[11] = c.projection[10] * c.nearClip; c.projection[14] = -1;
        return true;
    }
}
int main()
{
    using Microsoft::WRL::ComPtr;
    using OpenShimTest::Check;
    using OpenShimTest::Require;
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    Require(SUCCEEDED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
        D3D11_SDK_VERSION, &device, nullptr, &context)), "hardware D3D11");
    for (auto format : {DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_B8G8R8A8_UNORM})
    for (UINT samples : {1u, 4u})
    {
        D3D11_TEXTURE2D_DESC desc{};
        desc.Width = 67; desc.Height = 33; desc.MipLevels = desc.ArraySize = 1;
        desc.Format = format; desc.SampleDesc.Count = samples; desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_RENDER_TARGET;
        ComPtr<ID3D11Texture2D> source, depth, unrelated;
        ComPtr<ID3D11RenderTargetView> target;
        ComPtr<ID3D11DepthStencilView> dsv, otherDsv;
        Require(SUCCEEDED(device->CreateTexture2D(&desc, nullptr, &source)) &&
            SUCCEEDED(device->CreateRenderTargetView(source.Get(), nullptr, &target)), "color source");
        auto depthDesc = desc; depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        Require(SUCCEEDED(device->CreateTexture2D(&depthDesc, nullptr, &depth)) &&
            SUCCEEDED(device->CreateDepthStencilView(depth.Get(), nullptr, &dsv)) &&
            SUCCEEDED(device->CreateTexture2D(&depthDesc, nullptr, &unrelated)) &&
            SUCCEEDED(device->CreateDepthStencilView(unrelated.Get(), nullptr, &otherDsv)), "depth sources");
        Producer producer;
        Check(producer.Start(device.Get(), desc, false, true) == E_INVALIDARG, "scene color requires depth gate");
        Require(SUCCEEDED(producer.Start(device.Get(), desc, true, true)), "scene producer");
        HANDLE mapping = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, MappingName(GetCurrentProcessId()).c_str());
        Require(mapping != nullptr, "metadata mapping");
        auto* frame = static_cast<SharedFrame*>(MapViewOfFile(mapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedFrame)));
        Require(frame && frame->sceneColorHandle, "immutable scene handle");
        Exchange(frame->requestedDepthClear, 1);
        ID3D11RenderTargetView* bound = target.Get(); context->OMSetRenderTargets(1, &bound, dsv.Get());
        const float before[] = {64.0f / 255.0f, 128.0f / 255.0f, 191.0f / 255.0f, 1}, after[] = {0, 0, 0, 1};
        context->ClearRenderTargetView(target.Get(), before);
        context->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH, 0.5f, 0);
        producer.BeforeDepthClear(context.Get(), dsv.Get(), D3D11_CLEAR_DEPTH, &Camera);
        context->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH, 1, 0);
        context->ClearRenderTargetView(target.Get(), after);
        Require(producer.Publish(source.Get()) == S_OK && ValidSceneColorFrame(*frame), "same-boundary scene/depth/camera publication");
        const auto id = frame->frameId;
        producer.BeforeDepthClear(context.Get(), dsv.Get(), D3D11_CLEAR_DEPTH, &Camera);
        Check(producer.Publish(source.Get()) == S_FALSE && frame->frameId == id && ValidSceneColorFrame(*frame),
            "busy observation/publication preserves shared scene metadata");
        ComPtr<ID3D11Device1> device1; ComPtr<ID3D11Texture2D> shared, readback;
        Require(SUCCEEDED(device.As(&device1)) && SUCCEEDED(device1->OpenSharedResource1(
            reinterpret_cast<HANDLE>(static_cast<std::uintptr_t>(frame->sceneColorHandle)), IID_PPV_ARGS(&shared))), "import shared scene");
        D3D11_TEXTURE2D_DESC readDesc{}; shared->GetDesc(&readDesc);
        Check(readDesc.SampleDesc.Count == 1, "color samples resolved independently of depth samples");
        readDesc.Usage = D3D11_USAGE_STAGING; readDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ; readDesc.BindFlags = readDesc.MiscFlags = 0;
        Require(SUCCEEDED(device->CreateTexture2D(&readDesc, nullptr, &readback)), "scene readback");
        context->CopyResource(readback.Get(), shared.Get());
        D3D11_MAPPED_SUBRESOURCE data{}; Require(SUCCEEDED(context->Map(readback.Get(), 0, D3D11_MAP_READ, 0, &data)), "scene GPU completion");
        const unsigned char expected[] = {static_cast<unsigned char>(format == DXGI_FORMAT_R8G8B8A8_UNORM ? 64 : 191), 128,
            static_cast<unsigned char>(format == DXGI_FORMAT_R8G8B8A8_UNORM ? 191 : 64), 255};
        bool match = true;
        for (UINT y = 0; y < desc.Height; ++y)
            for (UINT x = 0; x < desc.Width; ++x)
                match = match && std::memcmp(static_cast<const unsigned char*>(data.pData) + y * data.RowPitch + x * 4, expected, 4) == 0;
        Check(match, "every scene pixel precedes final color mutation, including padded rows and BGRA/MSAA");
        if (!match) {
            const auto* first = static_cast<const unsigned char*>(data.pData);
            std::fprintf(stderr, "SCENE_PIXEL format=%u samples=%u channels=%u,%u,%u,%u\n", static_cast<unsigned>(format), samples, first[0], first[1], first[2], first[3]);
        }
        context->Unmap(readback.Get(), 0);
        const auto acknowledge = [&]() {
            Require(Claim(frame->slotState, static_cast<LONG>(SlotState::Ready), static_cast<LONG>(SlotState::Reading)), "claim");
            Exchange(frame->slotState, static_cast<LONG>(SlotState::Free));
        };
        acknowledge();
        Require(producer.Publish(source.Get()) == S_OK, "color survives absent boundary");
        Check(!ValidSceneColorFrame(*frame) && frame->sceneColorCapturedOrdinal == 0, "missing boundary rejects stale scene pixels");
        acknowledge();
        producer.BeforeDepthClear(context.Get(), otherDsv.Get(), D3D11_CLEAR_DEPTH, &Camera);
        Require(producer.Publish(source.Get()) == S_OK, "unrelated depth clear does not stop color");
        Check(!ValidSceneColorFrame(*frame) && frame->sceneColorStatus == static_cast<std::uint32_t>(SceneColorStatus::Missing),
            "cannot pair bound color with an unrelated cleared DSV");
        acknowledge();
        auto presentDesc = desc; presentDesc.SampleDesc = {1, 0};
        ComPtr<ID3D11Texture2D> present; ComPtr<ID3D11RenderTargetView> presentTarget;
        Require(SUCCEEDED(device->CreateTexture2D(&presentDesc, nullptr, &present)) &&
            SUCCEEDED(device->CreateRenderTargetView(present.Get(), nullptr, &presentTarget)), "separate single-sample present source");
        context->ClearRenderTargetView(presentTarget.Get(), before);
        producer.BeforeDepthClear(context.Get(), dsv.Get(), D3D11_CLEAR_DEPTH, &Camera, present.Get());
        context->ClearRenderTargetView(presentTarget.Get(), after);
        Require(producer.Publish(source.Get()) == S_OK && ValidSceneColorFrame(*frame) &&
            frame->sceneColorSource == static_cast<std::uint32_t>(SceneColorSource::PresentBackbuffer),
            "explicit present source can differ from bound color/depth sample count");
        context->CopyResource(readback.Get(), shared.Get());
        Require(SUCCEEDED(context->Map(readback.Get(), 0, D3D11_MAP_READ, 0, &data)), "present snapshot completion");
        match = true;
        for (UINT y = 0; y < desc.Height; ++y)
            for (UINT x = 0; x < desc.Width; ++x)
                match = match && std::memcmp(static_cast<const unsigned char*>(data.pData) + y * data.RowPitch + x * 4, expected, 4) == 0;
        Check(match, "separate present source captured before mutation instead of bound black target");
        context->Unmap(readback.Get(), 0);
        acknowledge();
        Exchange(frame->requestedSceneStage, 1);
        producer.BeforeDepthClear(context.Get(), dsv.Get(), D3D11_CLEAR_DEPTH, &Camera);
        Check(producer.AwaitingOverlay(), "wait for later scene color with current private depth");
        CameraSnapshot camera{}; Camera(camera);
        context->ClearRenderTargetView(presentTarget.Get(), before);
        camera.view[3] = 1;
        producer.BeforeOverlay(context.Get(), present.Get(), camera);
        Check(producer.AwaitingOverlay(), "changed camera cannot pair earlier depth with later color");
        camera.view[3] = 0;
        producer.BeforeOverlay(context.Get(), present.Get(), camera);
        Check(!producer.AwaitingOverlay(), "first eligible overlay observation latches only once");
        context->ClearRenderTargetView(presentTarget.Get(), after);
        producer.BeforeOverlay(context.Get(), present.Get(), camera);
        Require(producer.Publish(source.Get()) == S_OK && ValidSceneColorFrame(*frame) && frame->sceneColorStage == 1,
            "late color capture publishes explicit overlay stage beside pre-clear depth");
        context->CopyResource(readback.Get(), shared.Get());
        Require(SUCCEEDED(context->Map(readback.Get(), 0, D3D11_MAP_READ, 0, &data)), "overlay snapshot completion");
        match = std::memcmp(data.pData, expected, 4) == 0;
        Check(match, "repeated overlay events cannot replace the pre-UI snapshot");
        context->Unmap(readback.Get(), 0);
        producer.Stop(); UnmapViewOfFile(frame); CloseHandle(mapping);
        context->OMSetRenderTargets(0, nullptr, nullptr);
    }
    return OpenShimTest::ExitCode();
}
