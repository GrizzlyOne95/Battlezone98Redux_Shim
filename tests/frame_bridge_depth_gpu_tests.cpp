#include "frame_bridge_depth.h"
#include <d3dcompiler.h>
#include <d3d11sdklayers.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <vector>

namespace
{
    using Microsoft::WRL::ComPtr;
    using namespace BZROpenShim::FrameBridge;
    void Check(bool valid, const char* message) { if (!valid) throw std::runtime_error(message); }
    void Require(HRESULT hr, const char* message) { Check(SUCCEEDED(hr), message); }
    ComPtr<ID3DBlob> Compile(const char* source, const char* profile)
    {
        ComPtr<ID3DBlob> result, errors;
        const HRESULT hr = D3DCompile(source, std::strlen(source), "depth_test", nullptr, nullptr, "main", profile,
            D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &result, &errors);
        if (FAILED(hr) && errors) std::fprintf(stderr, "%s", static_cast<const char*>(errors->GetBufferPointer()));
        Require(hr, "compile depth fixture");
        return result;
    }
    void Verify(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11Texture2D* texture, UINT samples, bool maximum)
    {
        D3D11_TEXTURE2D_DESC desc{};
        texture->GetDesc(&desc);
        desc.Usage = D3D11_USAGE_STAGING;
        desc.BindFlags = desc.MiscFlags = 0;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        ComPtr<ID3D11Texture2D> staging;
        Require(device->CreateTexture2D(&desc, nullptr, &staging), "create depth readback");
        context->CopyResource(staging.Get(), texture);
        D3D11_MAPPED_SUBRESOURCE mapped{};
        Require(context->Map(staging.Get(), 0, D3D11_MAP_READ, 0, &mapped), "read extracted depth");
        bool valid = true;
        for (UINT y = 0; y < desc.Height; ++y)
        {
            const auto* row = reinterpret_cast<const float*>(static_cast<const unsigned char*>(mapped.pData) + y * mapped.RowPitch);
            for (UINT x = 0; x < desc.Width; ++x)
            {
                const float expected = 0.1f + (maximum ? static_cast<float>(samples - 1) * 0.07f : 0.0f) +
                    (static_cast<float>(x) + 0.5f) * 0.003f;
                valid = valid && std::isfinite(row[x]) && std::fabs(row[x] - expected) < 0.00001f;
            }
        }
        context->Unmap(staging.Get(), 0);
        Check(valid, "depth pixels wrong (format conversion, MSAA reduction or edge dispatch)");
    }
    void Test(ID3D11Device* device, ID3D11DeviceContext* context, DXGI_FORMAT format, UINT samples)
    {
        // Non-multiple-of-eight dimensions test the shader's dispatch bounds.
        D3D11_TEXTURE2D_DESC desc{};
        desc.Width = 37; desc.Height = 19; desc.MipLevels = desc.ArraySize = 1;
        desc.Format = format; desc.SampleDesc = {samples, 0};
        desc.Usage = D3D11_USAGE_DEFAULT; desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        ComPtr<ID3D11Texture2D> depth;
        ComPtr<ID3D11DepthStencilView> dsv;
        Require(device->CreateTexture2D(&desc, nullptr, &depth), "create typed depth without SRV bind");
        Require(device->CreateDepthStencilView(depth.Get(), nullptr, &dsv), "create depth fixture DSV");
        D3D11_DEPTH_STENCIL_DESC depthState{};
        depthState.DepthEnable = TRUE;
        depthState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        depthState.DepthFunc = D3D11_COMPARISON_ALWAYS;
        ComPtr<ID3D11DepthStencilState> depthMode;
        Require(device->CreateDepthStencilState(&depthState, &depthMode), "create depth fixture state");
        D3D11_RASTERIZER_DESC raster{};
        raster.FillMode = D3D11_FILL_SOLID; raster.CullMode = D3D11_CULL_NONE;
        raster.DepthClipEnable = TRUE; raster.MultisampleEnable = TRUE;
        ComPtr<ID3D11RasterizerState> rasterMode;
        Require(device->CreateRasterizerState(&raster, &rasterMode), "create raster fixture state");
        const auto vsBytes = Compile(R"(
float4 main(uint vertex : SV_VertexID) : SV_Position {
    float2 p[3] = {float2(-1,-1), float2(-1,3), float2(3,-1)};
    return float4(p[vertex], 0, 1);
})", "vs_5_0");
        const auto psBytes = Compile(R"(
float main(float4 pixel : SV_Position, uint sample : SV_SampleIndex) : SV_Depth {
    // floor removes per-sample position offsets so samples differ only in z.
    return 0.1 + sample * 0.07 + (floor(pixel.x) + 0.5) * 0.003;
})", "ps_5_0");
        ComPtr<ID3D11VertexShader> vs;
        ComPtr<ID3D11PixelShader> ps;
        Require(device->CreateVertexShader(vsBytes->GetBufferPointer(), vsBytes->GetBufferSize(), nullptr, &vs), "create VS");
        Require(device->CreatePixelShader(psBytes->GetBufferPointer(), psBytes->GetBufferSize(), nullptr, &ps), "create PS");
        context->ClearState();
        context->OMSetRenderTargets(0, nullptr, dsv.Get());
        context->OMSetDepthStencilState(depthMode.Get(), 0);
        context->RSSetState(rasterMode.Get());
        const D3D11_VIEWPORT viewport{0, 0, 37, 19, 0, 1};
        context->RSSetViewports(1, &viewport);
        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        context->VSSetShader(vs.Get(), nullptr, 0);
        context->PSSetShader(ps.Get(), nullptr, 0);
        context->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
        context->Draw(3, 0);

        // Install unrelated compute state to detect damage to the caller.
        const auto csBytes = Compile("[numthreads(1,1,1)] void main() {}", "cs_5_0");
        ComPtr<ID3D11ComputeShader> oldShader;
        Require(device->CreateComputeShader(csBytes->GetBufferPointer(), csBytes->GetBufferSize(), nullptr, &oldShader), "create saved CS");
        auto spareDesc = desc;
        spareDesc.Format = DXGI_FORMAT_R32_FLOAT; spareDesc.SampleDesc = {1, 0};
        spareDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
        ComPtr<ID3D11Texture2D> spareInput, spareOutput;
        ComPtr<ID3D11ShaderResourceView> oldView;
        ComPtr<ID3D11UnorderedAccessView> oldTarget;
        Require(device->CreateTexture2D(&spareDesc, nullptr, &spareInput), "create saved input");
        Require(device->CreateTexture2D(&spareDesc, nullptr, &spareOutput), "create saved output");
        Require(device->CreateShaderResourceView(spareInput.Get(), nullptr, &oldView), "create saved SRV");
        Require(device->CreateUnorderedAccessView(spareOutput.Get(), nullptr, &oldTarget), "create saved UAV");
        D3D11_BUFFER_DESC buffer{};
        buffer.ByteWidth = 16; buffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        ComPtr<ID3D11Buffer> oldBuffer;
        Require(device->CreateBuffer(&buffer, nullptr, &oldBuffer), "create saved CB");
        auto* savedView = oldView.Get(); auto* savedTarget = oldTarget.Get(); auto* savedBuffer = oldBuffer.Get();
        context->CSSetShader(oldShader.Get(), nullptr, 0);
        context->CSSetShaderResources(0, 1, &savedView);
        context->CSSetUnorderedAccessViews(0, 1, &savedTarget, nullptr);
        context->CSSetConstantBuffers(0, 1, &savedBuffer);
        DepthExtractor extractor;
        Require(extractor.Start(device, desc), "initialize extraction");
        for (const bool maximum : {false, true})
        {
            Require(extractor.Extract(context, depth.Get(), maximum ? DepthReduction::Maximum : DepthReduction::Minimum), "extract depth");
            Verify(device, context, extractor.Output(), samples, maximum);
            ComPtr<ID3D11ComputeShader> shader;
            ComPtr<ID3D11ShaderResourceView> view;
            ComPtr<ID3D11UnorderedAccessView> target;
            ComPtr<ID3D11Buffer> constants;
            ComPtr<ID3D11DepthStencilView> boundDepth;
            context->CSGetShader(&shader, nullptr, nullptr);
            context->CSGetShaderResources(0, 1, &view);
            context->CSGetUnorderedAccessViews(0, 1, &target);
            context->CSGetConstantBuffers(0, 1, &constants);
            context->OMGetRenderTargets(0, nullptr, &boundDepth);
            Check(shader.Get() == oldShader.Get() && view.Get() == savedView && target.Get() == savedTarget &&
                constants.Get() == savedBuffer && boundDepth.Get() == dsv.Get(), "caller pipeline state changed");
        }
        auto changed = desc; changed.Width += 1;
        ComPtr<ID3D11Texture2D> wrongSize;
        Require(device->CreateTexture2D(&changed, nullptr, &wrongSize), "create resized depth");
        Check(extractor.Extract(context, wrongSize.Get(), DepthReduction::Minimum) == DXGI_ERROR_UNSUPPORTED, "resize must fail closed");
        extractor.Stop(); extractor.Stop();
        Check(extractor.Extract(context, depth.Get(), DepthReduction::Minimum) == E_INVALIDARG, "stopped extractor accepted input");
        changed.Format = DXGI_FORMAT_D16_UNORM;
        Check(extractor.Start(device, changed) == DXGI_ERROR_UNSUPPORTED && !extractor.Output(), "unsupported depth accepted");
        context->ClearState();
        std::printf("PASS depth format=%u samples=%u min/max pixels, state restoration, invalidation\n", static_cast<unsigned>(format), samples);
    }
}
int main()
{
    try
    {
        ComPtr<ID3D11Device> device;
        ComPtr<ID3D11DeviceContext> context;
        D3D_FEATURE_LEVEL level{};
        HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
            nullptr, 0, D3D11_SDK_VERSION, &device, &level, &context);
        if (hr == DXGI_ERROR_SDK_COMPONENT_MISSING)
            hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &device, &level, &context);
        Require(hr, "create depth test device");
        ComPtr<ID3D11InfoQueue> diagnostics;
        device.As(&diagnostics);
        std::printf("DEPTH pointer_bits=%zu debug_layer=%s\n", sizeof(void*) * 8, diagnostics ? "yes" : "unavailable");
        for (const auto format : {DXGI_FORMAT_D24_UNORM_S8_UINT, DXGI_FORMAT_D32_FLOAT})
            for (const UINT samples : {1u, 2u, 4u, 8u}) Test(device.Get(), context.Get(), format, samples);
        if (diagnostics)
        {
            for (UINT64 i = 0; i < diagnostics->GetNumStoredMessages(); ++i)
            {
                SIZE_T size = 0;
                Require(diagnostics->GetMessage(i, nullptr, &size), "query debug message");
                std::vector<unsigned char> data(size);
                auto* message = reinterpret_cast<D3D11_MESSAGE*>(data.data());
                Require(diagnostics->GetMessage(i, message, &size), "read debug message");
                if (message->Severity <= D3D11_MESSAGE_SEVERITY_WARNING)
                {
                    std::fprintf(stderr, "%s\n", message->pDescription);
                    throw std::runtime_error("D3D11 debug layer reported warning/error");
                }
            }
        }
        return 0;
    }
    catch (const std::exception& error) { std::fprintf(stderr, "DEPTH ERROR: %s\n", error.what()); return 1; }
}
