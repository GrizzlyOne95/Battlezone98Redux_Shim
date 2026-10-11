#include "frame_bridge_producer.h"
#include <dxgi1_2.h>
#include <cstring>

namespace BZROpenShim::FrameBridge
{
    using Microsoft::WRL::ComPtr;
    HRESULT Producer::Start(ID3D11Device* device, const D3D11_TEXTURE2D_DESC& source)
    {
        Stop();
        if (!device || source.Width == 0 || source.Height == 0 ||
            source.Width > kMaxDimension || source.Height > kMaxDimension ||
            source.MipLevels != 1 || source.ArraySize != 1 ||
            (source.Format != DXGI_FORMAT_R8G8B8A8_UNORM &&
             source.Format != DXGI_FORMAT_B8G8R8A8_UNORM))
            return E_INVALIDARG;
        device_ = device;
        sourceDesc_ = source;
        ComPtr<ID3D11Device5> device5;
        ComPtr<ID3D11DeviceContext> context;
        device->GetImmediateContext(&context);
        HRESULT hr = device->QueryInterface(IID_PPV_ARGS(&device5));
        if (SUCCEEDED(hr)) hr = context.As(&context_);
        if (FAILED(hr)) { Stop(); return hr; }
        if (source.SampleDesc.Count > 1)
        {
            UINT support = 0;
            hr = device->CheckFormatSupport(source.Format, &support);
            if (FAILED(hr) || !(support & D3D11_FORMAT_SUPPORT_MULTISAMPLE_RESOLVE))
            { Stop(); return DXGI_ERROR_UNSUPPORTED; }
        }

        D3D11_TEXTURE2D_DESC desc = source;
        desc.SampleDesc = {1, 0};
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = D3D11_RESOURCE_MISC_SHARED | D3D11_RESOURCE_MISC_SHARED_NTHANDLE;
        hr = device->CreateTexture2D(&desc, nullptr, &color_);
        ComPtr<IDXGIResource1> resource;
        if (SUCCEEDED(hr)) hr = color_.As(&resource);
        if (SUCCEEDED(hr)) hr = resource->CreateSharedHandle(nullptr,
            DXGI_SHARED_RESOURCE_READ | DXGI_SHARED_RESOURCE_WRITE, nullptr, &textureHandle_);
        if (SUCCEEDED(hr)) hr = device5->CreateFence(0, D3D11_FENCE_FLAG_SHARED, IID_PPV_ARGS(&ready_));
        if (SUCCEEDED(hr)) hr = ready_->CreateSharedHandle(nullptr, GENERIC_ALL, nullptr, &fenceHandle_);
        ComPtr<IDXGIDevice> dxgiDevice;
        ComPtr<IDXGIAdapter> adapter;
        DXGI_ADAPTER_DESC adapterDesc{};
        if (SUCCEEDED(hr)) hr = device->QueryInterface(IID_PPV_ARGS(&dxgiDevice));
        if (SUCCEEDED(hr)) hr = dxgiDevice->GetAdapter(&adapter);
        if (SUCCEEDED(hr)) hr = adapter->GetDesc(&adapterDesc);
        if (FAILED(hr)) { Stop(); return hr; }

        const auto name = MappingName(GetCurrentProcessId());
        mapping_ = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE,
            0, sizeof(SharedFrame), name.c_str());
        const DWORD error = GetLastError();
        if (!mapping_ || error == ERROR_ALREADY_EXISTS)
        {
            const DWORD failure = mapping_ ? ERROR_ALREADY_EXISTS : (error ? error : ERROR_GEN_FAILURE);
            Stop();
            return HRESULT_FROM_WIN32(failure);
        }
        frame_ = static_cast<SharedFrame*>(MapViewOfFile(mapping_, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedFrame)));
        if (!frame_) { hr = HRESULT_FROM_WIN32(GetLastError()); Stop(); return hr; }
        std::memset(frame_, 0, sizeof(*frame_));
        frame_->magic = kMagic;
        frame_->version = kVersion;
        frame_->byteSize = sizeof(*frame_);
        frame_->producerPid = GetCurrentProcessId();
        frame_->width = desc.Width;
        frame_->height = desc.Height;
        frame_->format = desc.Format;
        frame_->adapterLuidLow = adapterDesc.AdapterLuid.LowPart;
        frame_->adapterLuidHigh = adapterDesc.AdapterLuid.HighPart;
        frame_->textureHandle = reinterpret_cast<std::uintptr_t>(textureHandle_);
        frame_->readyFenceHandle = reinterpret_cast<std::uintptr_t>(fenceHandle_);
        LARGE_INTEGER frequency{};
        QueryPerformanceFrequency(&frequency);
        frame_->qpcFrequency = frequency.QuadPart;
        Exchange(frame_->active, 1);
        return S_OK;
    }

    HRESULT Producer::Publish(ID3D11Texture2D* source)
    {
        if (!source || !Active()) return E_UNEXPECTED;
        D3D11_TEXTURE2D_DESC desc{};
        source->GetDesc(&desc);
        ComPtr<ID3D11Device> sourceDevice;
        source->GetDevice(&sourceDevice);
        if (sourceDevice.Get() != device_.Get() || desc.Width != sourceDesc_.Width ||
            desc.Height != sourceDesc_.Height || desc.Format != sourceDesc_.Format ||
            desc.ArraySize != 1 || desc.MipLevels != 1 ||
            desc.SampleDesc.Count != sourceDesc_.SampleDesc.Count ||
            desc.SampleDesc.Quality != sourceDesc_.SampleDesc.Quality)
        {
            // V1 deliberately ends a session on resize/device replacement.
            // Old readers keep their imported resource alive; no slot is reused.
            Stop();
            return DXGI_ERROR_UNSUPPORTED;
        }
        if (!Claim(frame_->slotState, static_cast<LONG>(SlotState::Free), static_cast<LONG>(SlotState::Writing)))
            return S_FALSE;
        if (desc.SampleDesc.Count > 1)
            context_->ResolveSubresource(color_.Get(), 0, source, 0, desc.Format);
        else
            context_->CopyResource(color_.Get(), source);
        const std::uint64_t id = ++nextFrame_;
        HRESULT hr = context_->Signal(ready_.Get(), id);
        context_->Flush();
        if (FAILED(hr)) { Stop(); return hr; }
        LARGE_INTEGER qpc{};
        QueryPerformanceCounter(&qpc);
        frame_->frameId = id;
        frame_->captureQpc = qpc.QuadPart;
        Exchange(frame_->slotState, static_cast<LONG>(SlotState::Ready));
        return S_OK;
    }

    void Producer::Stop()
    {
        if (frame_) { Exchange(frame_->active, 0); UnmapViewOfFile(frame_); frame_ = nullptr; }
        if (mapping_) { CloseHandle(mapping_); mapping_ = nullptr; }
        if (textureHandle_) { CloseHandle(textureHandle_); textureHandle_ = nullptr; }
        if (fenceHandle_) { CloseHandle(fenceHandle_); fenceHandle_ = nullptr; }
        ready_.Reset();
        color_.Reset();
        context_.Reset();
        device_.Reset();
        nextFrame_ = 0;
    }
}
