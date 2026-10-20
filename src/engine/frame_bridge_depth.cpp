#include "frame_bridge_depth.h"
#include <d3dcompiler.h>
#include <cstring>

namespace BZROpenShim::FrameBridge
{
    namespace
    {
        constexpr char kShader[] = R"(
#ifdef MULTISAMPLED
Texture2DMS<float> depthInput : register(t0);
#else
Texture2D<float> depthInput : register(t0);
#endif
RWTexture2D<float> depthOutput : register(u0);
cbuffer Parameters : register(b0) { uint width; uint height; uint samples; uint nearestIsMax; };
[numthreads(8,8,1)]
void main(uint3 pixel : SV_DispatchThreadID)
{
    if (pixel.x >= width || pixel.y >= height) return;
#ifdef MULTISAMPLED
    float z = depthInput.Load(pixel.xy, 0);
    [loop] for (uint sample = 1; sample < samples; ++sample)
    {
        float other = depthInput.Load(pixel.xy, sample);
        z = nearestIsMax ? max(z, other) : min(z, other);
    }
#else
    float z = depthInput.Load(int3(pixel.xy, 0));
#endif
    depthOutput[pixel.xy] = z;
})";

        // Only touched compute slots are saved; no raster/OM state changes.
        struct ComputeState
        {
            explicit ComputeState(ID3D11DeviceContext* value) : context(value)
            {
                context->CSGetShader(&shader, instances, &instanceCount);
                context->CSGetShaderResources(0, 1, &view);
                context->CSGetUnorderedAccessViews(0, 1, &target);
                context->CSGetConstantBuffers(0, 1, &constants);
            }
            ~ComputeState()
            {
                ID3D11ShaderResourceView* noView = nullptr;
                ID3D11UnorderedAccessView* noTarget = nullptr;
                context->CSSetShaderResources(0, 1, &noView);
                context->CSSetUnorderedAccessViews(0, 1, &noTarget, nullptr);
                context->CSSetShaderResources(0, 1, &view);
                context->CSSetUnorderedAccessViews(0, 1, &target, nullptr);
                context->CSSetConstantBuffers(0, 1, &constants);
                context->CSSetShader(shader, instances, instanceCount);
                if (shader) shader->Release();
                if (view) view->Release();
                if (target) target->Release();
                if (constants) constants->Release();
                for (UINT i = 0; i < instanceCount; ++i) if (instances[i]) instances[i]->Release();
            }
            ID3D11DeviceContext* context;
            ID3D11ComputeShader* shader = nullptr;
            ID3D11ShaderResourceView* view = nullptr;
            ID3D11UnorderedAccessView* target = nullptr;
            ID3D11Buffer* constants = nullptr;
            ID3D11ClassInstance* instances[D3D11_SHADER_MAX_INTERFACES]{};
            UINT instanceCount = D3D11_SHADER_MAX_INTERFACES;
        };
        struct CompilerModule
        {
            HMODULE value = LoadLibraryExW(L"d3dcompiler_47.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
            ~CompilerModule() { if (value) FreeLibrary(value); }
        };
    }

    void DepthExtractor::Stop()
    {
        constants_.Reset(); shader_.Reset(); target_.Reset(); view_.Reset();
        output_.Reset(); copy_.Reset(); device_.Reset(); sourceDesc_ = {};
    }

    HRESULT DepthExtractor::Start(ID3D11Device* device, const D3D11_TEXTURE2D_DESC& source)
    {
        Stop();
        if (!device || device->GetFeatureLevel() < D3D_FEATURE_LEVEL_11_0 ||
            !source.Width || !source.Height || source.Width > 8192 || source.Height > 8192 ||
            source.MipLevels != 1 || source.ArraySize != 1 ||
            !(source.BindFlags & D3D11_BIND_DEPTH_STENCIL) || source.Usage != D3D11_USAGE_DEFAULT ||
            (source.SampleDesc.Count != 1 && source.SampleDesc.Count != 2 &&
             source.SampleDesc.Count != 4 && source.SampleDesc.Count != 8)) return DXGI_ERROR_UNSUPPORTED;
        DXGI_FORMAT copyFormat, viewFormat;
        if (source.Format == DXGI_FORMAT_D24_UNORM_S8_UINT || source.Format == DXGI_FORMAT_R24G8_TYPELESS)
        {
            copyFormat = DXGI_FORMAT_R24G8_TYPELESS;
            viewFormat = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
        }
        else if (source.Format == DXGI_FORMAT_D32_FLOAT || source.Format == DXGI_FORMAT_R32_TYPELESS)
        {
            copyFormat = DXGI_FORMAT_R32_TYPELESS;
            viewFormat = DXGI_FORMAT_R32_FLOAT;
        }
        else return DXGI_ERROR_UNSUPPORTED;
        device_ = device;
        sourceDesc_ = source;
        auto desc = source;
        desc.Format = copyFormat;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.MiscFlags = desc.CPUAccessFlags = 0;
        HRESULT hr = device->CreateTexture2D(&desc, nullptr, &copy_);
        D3D11_SHADER_RESOURCE_VIEW_DESC srv{};
        srv.Format = viewFormat;
        srv.ViewDimension = source.SampleDesc.Count > 1 ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
        if (source.SampleDesc.Count == 1) srv.Texture2D.MipLevels = 1;
        if (SUCCEEDED(hr)) hr = device->CreateShaderResourceView(copy_.Get(), &srv, &view_);
        desc.Format = DXGI_FORMAT_R32_FLOAT;
        desc.SampleDesc = {1, 0};
        desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
        if (SUCCEEDED(hr)) hr = device->CreateTexture2D(&desc, nullptr, &output_);
        if (SUCCEEDED(hr)) hr = device->CreateUnorderedAccessView(output_.Get(), nullptr, &target_);
        D3D11_BUFFER_DESC cb{};
        cb.ByteWidth = 16;
        cb.Usage = D3D11_USAGE_DEFAULT;
        cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        if (SUCCEEDED(hr)) hr = device->CreateBuffer(&cb, nullptr, &constants_);
        const D3D_SHADER_MACRO defines[] = { {"MULTISAMPLED", "1"}, {nullptr, nullptr} };
        // Keep the compiler optional for stock/DX9 and Wine installs. Blobs
        // must die before the owning module; no new eager DLL import is added.
        CompilerModule compiler;
        const auto compile = compiler.value ? reinterpret_cast<decltype(&D3DCompile)>(GetProcAddress(compiler.value, "D3DCompile")) : nullptr;
        if (SUCCEEDED(hr) && !compile) hr = HRESULT_FROM_WIN32(ERROR_MOD_NOT_FOUND);
        Microsoft::WRL::ComPtr<ID3DBlob> bytecode, errors;
        if (SUCCEEDED(hr)) hr = compile(kShader, std::strlen(kShader), "frame_bridge_depth", source.SampleDesc.Count > 1 ? defines : nullptr,
            nullptr, "main", "cs_5_0", D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &bytecode, &errors);
        if (SUCCEEDED(hr)) hr = device->CreateComputeShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), nullptr, &shader_);
        if (FAILED(hr)) Stop();
        return hr;
    }

    HRESULT DepthExtractor::Extract(ID3D11DeviceContext* context, ID3D11Texture2D* source, DepthReduction reduction)
    {
        if (!device_ || !context || !source || context->GetType() != D3D11_DEVICE_CONTEXT_IMMEDIATE ||
            (reduction != DepthReduction::Minimum && reduction != DepthReduction::Maximum)) return E_INVALIDARG;
        Microsoft::WRL::ComPtr<ID3D11Device> sourceDevice, contextDevice;
        source->GetDevice(&sourceDevice);
        context->GetDevice(&contextDevice);
        D3D11_TEXTURE2D_DESC desc{};
        source->GetDesc(&desc);
        if (sourceDevice.Get() != device_.Get() || contextDevice.Get() != device_.Get() ||
            desc.Width != sourceDesc_.Width || desc.Height != sourceDesc_.Height ||
            desc.Format != sourceDesc_.Format || desc.ArraySize != 1 || desc.MipLevels != 1 ||
            desc.SampleDesc.Count != sourceDesc_.SampleDesc.Count || desc.SampleDesc.Quality != sourceDesc_.SampleDesc.Quality ||
            !(desc.BindFlags & D3D11_BIND_DEPTH_STENCIL) || desc.Usage != D3D11_USAGE_DEFAULT) return DXGI_ERROR_UNSUPPORTED;
        ComputeState saved(context);
        // Copy matching sample layouts and format families, then load individual
        // samples. Color ResolveSubresource cannot resolve this depth surface.
        context->CopyResource(copy_.Get(), source);
        const UINT parameters[] = {desc.Width, desc.Height, desc.SampleDesc.Count, reduction == DepthReduction::Maximum ? 1u : 0u};
        context->UpdateSubresource(constants_.Get(), 0, nullptr, parameters, 0, 0);
        ID3D11ShaderResourceView* view = view_.Get();
        ID3D11UnorderedAccessView* target = target_.Get();
        ID3D11Buffer* constants = constants_.Get();
        context->CSSetShaderResources(0, 1, &view);
        context->CSSetUnorderedAccessViews(0, 1, &target, nullptr);
        context->CSSetConstantBuffers(0, 1, &constants);
        context->CSSetShader(shader_.Get(), nullptr, 0);
        context->Dispatch((desc.Width + 7) / 8, (desc.Height + 7) / 8, 1);
        return device_->GetDeviceRemovedReason();
    }
}
