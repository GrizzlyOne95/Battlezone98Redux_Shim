#include "frame_bridge_producer.h"
#include <dxgi1_2.h>
#include <cstring>

namespace BZROpenShim::FrameBridge
{
    using Microsoft::WRL::ComPtr;
    HRESULT Producer::Start(ID3D11Device* device, const D3D11_TEXTURE2D_DESC& source, bool depthEnabled)
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
        if (SUCCEEDED(hr) && depthEnabled)
        {
            auto depthDesc = desc;
            depthDesc.Format = DXGI_FORMAT_R32_FLOAT;
            hr = device->CreateTexture2D(&depthDesc, nullptr, &depth_);
            resource.Reset();
            if (SUCCEEDED(hr)) hr = depth_.As(&resource);
            if (SUCCEEDED(hr)) hr = resource->CreateSharedHandle(nullptr,
                DXGI_SHARED_RESOURCE_READ | DXGI_SHARED_RESOURCE_WRITE, nullptr, &depthHandle_);
        }
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
        frame_->depthTextureHandle = reinterpret_cast<std::uintptr_t>(depthHandle_);
        frame_->readyFenceHandle = reinterpret_cast<std::uintptr_t>(fenceHandle_);
        LARGE_INTEGER frequency{};
        QueryPerformanceFrequency(&frequency);
        frame_->qpcFrequency = frequency.QuadPart;
        Exchange(frame_->active, 1);
        return S_OK;
    }

    void Producer::BeforeDepthClear(ID3D11DeviceContext* context, ID3D11DepthStencilView* view, UINT flags)
    {
        if (!Active() || !depth_ || !context || !view || !(flags & D3D11_CLEAR_DEPTH) ||
            context->GetType() != D3D11_DEVICE_CONTEXT_IMMEDIATE) return;
        ComPtr<ID3D11Device> contextDevice;
        context->GetDevice(&contextDevice);
        if (contextDevice.Get() != device_.Get()) return;
        ComPtr<ID3D11Resource> resource;
        ComPtr<ID3D11Texture2D> source;
        view->GetResource(&resource);
        if (FAILED(resource.As(&source))) return;
        D3D11_TEXTURE2D_DESC desc{};
        source->GetDesc(&desc);
        if (desc.Width != sourceDesc_.Width || desc.Height != sourceDesc_.Height ||
            desc.ArraySize != 1 || desc.MipLevels != 1) return;
        ++matchingDepthClears_;
        const LONG ordinal = ReadInterlocked(frame_->requestedDepthClear);
        if (ordinal < 1 || ordinal > 8 || matchingDepthClears_ != static_cast<UINT>(ordinal) ||
            ReadInterlocked(frame_->slotState) != static_cast<LONG>(SlotState::Free)) return;
        capturedDepthOrdinal_ = matchingDepthClears_;
        if (!preclear_ || desc.Format != preclearDesc_.Format || desc.Width != preclearDesc_.Width ||
            desc.Height != preclearDesc_.Height || desc.SampleDesc.Count != preclearDesc_.SampleDesc.Count ||
            desc.SampleDesc.Quality != preclearDesc_.SampleDesc.Quality)
        {
            preclear_.Reset();
            preclearDesc_ = desc;
            preclearDesc_.Usage = D3D11_USAGE_DEFAULT;
            preclearDesc_.BindFlags = D3D11_BIND_DEPTH_STENCIL;
            preclearDesc_.MiscFlags = preclearDesc_.CPUAccessFlags = 0;
            preclearResult_ = device_->CreateTexture2D(&preclearDesc_, nullptr, &preclear_);
        }
        else preclearResult_ = S_OK;
        if (SUCCEEDED(preclearResult_))
        {
            // Private snapshot only. Never modify shared metadata or a shared
            // image while the consumer can own a previous frame.
            context->CopyResource(preclear_.Get(), source.Get());
            preclearResult_ = device_->GetDeviceRemovedReason();
        }
    }

    void Producer::CaptureDepth(ID3D11Texture2D* source, DepthReduction reduction)
    {
        // Reset validity on EVERY publication. The GPU image may retain old
        // pixels, but it is never valid when a current source is unavailable.
        frame_->depthStatus = static_cast<std::uint32_t>(depth_ ? DepthStatus::Missing : DepthStatus::Disabled);
        frame_->depthSourceFormat = frame_->depthSourceSamples = frame_->depthResult = 0;
        frame_->depthReduction = reduction == DepthReduction::Maximum ? 1u : 0u;
        if (!depth_ || !source) return;
        D3D11_TEXTURE2D_DESC desc{};
        source->GetDesc(&desc);
        frame_->depthSourceFormat = desc.Format;
        frame_->depthSourceSamples = desc.SampleDesc.Count;
        ComPtr<ID3D11Device> sourceDevice;
        source->GetDevice(&sourceDevice);
        HRESULT hr = DXGI_ERROR_UNSUPPORTED;
        if (sourceDevice.Get() == device_.Get() && desc.Width == sourceDesc_.Width && desc.Height == sourceDesc_.Height)
        {
            if (!extractor_.Output() || desc.Format != depthDesc_.Format ||
                desc.SampleDesc.Count != depthDesc_.SampleDesc.Count || desc.SampleDesc.Quality != depthDesc_.SampleDesc.Quality)
            {
                hr = extractor_.Start(device_.Get(), desc);
                if (SUCCEEDED(hr)) depthDesc_ = desc;
            }
            else hr = S_OK;
            if (SUCCEEDED(hr)) hr = extractor_.Extract(context_.Get(), source, reduction);
            if (SUCCEEDED(hr)) context_->CopyResource(depth_.Get(), extractor_.Output());
        }
        frame_->depthResult = static_cast<std::uint32_t>(hr);
        frame_->depthStatus = static_cast<std::uint32_t>(SUCCEEDED(hr) ? DepthStatus::Candidate :
            (hr == DXGI_ERROR_UNSUPPORTED ? DepthStatus::Unsupported : DepthStatus::Failed));
    }

    HRESULT Producer::Publish(ID3D11Texture2D* source, ID3D11Texture2D* depthSource, DepthReduction reduction)
    {
        if (!source || !Active()) return E_UNEXPECTED;
        const UINT matchingClears = matchingDepthClears_;
        const UINT capturedOrdinal = capturedDepthOrdinal_;
        matchingDepthClears_ = capturedDepthOrdinal_ = 0; // reset even when this Present is skipped
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
            // End a session on resize/device replacement.
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
        const LONG requestedOrdinal = ReadInterlocked(frame_->requestedDepthClear);
        frame_->depthCapturedOrdinal = 0;
        frame_->depthMatchingClears = matchingClears;
        if (requestedOrdinal == 0) CaptureDepth(depthSource, reduction);
        else
        {
            const bool captured = requestedOrdinal > 0 && requestedOrdinal <= 8 && capturedOrdinal == static_cast<UINT>(requestedOrdinal);
            CaptureDepth(captured && SUCCEEDED(preclearResult_) ? preclear_.Get() : nullptr, reduction);
            if (captured)
            {
                frame_->depthCapturedOrdinal = capturedOrdinal;
                if (FAILED(preclearResult_))
                {
                    frame_->depthStatus = static_cast<std::uint32_t>(DepthStatus::Failed);
                    frame_->depthResult = static_cast<std::uint32_t>(preclearResult_);
                }
            }
        }
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
        if (depthHandle_) { CloseHandle(depthHandle_); depthHandle_ = nullptr; }
        if (fenceHandle_) { CloseHandle(fenceHandle_); fenceHandle_ = nullptr; }
        ready_.Reset();
        color_.Reset();
        depth_.Reset();
        extractor_.Stop();
        depthDesc_ = {};
        preclear_.Reset(); preclearDesc_ = {};
        matchingDepthClears_ = capturedDepthOrdinal_ = 0;
        preclearResult_ = S_OK;
        context_.Reset();
        device_.Reset();
        nextFrame_ = 0;
    }
}
