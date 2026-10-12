#include "frame_bridge_producer.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>

namespace
{
    using Microsoft::WRL::ComPtr;
    using namespace BZROpenShim::FrameBridge;

    void Require(HRESULT hr, const char* operation)
    {
        if (FAILED(hr))
        {
            char message[256]{};
            std::snprintf(message, sizeof(message), "%s failed: 0x%08lx", operation, static_cast<unsigned long>(hr));
            throw std::runtime_error(message);
        }
    }
    struct Handle
    {
        HANDLE value = nullptr;
        ~Handle() { if (value) CloseHandle(value); }
        Handle() = default;
        Handle(const Handle&) = delete;
        Handle& operator=(const Handle&) = delete;
    };
    LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
    {
        if (message == WM_CLOSE) { DestroyWindow(window); return 0; }
        if (message == WM_DESTROY) { PostQuitMessage(0); return 0; }
        return DefWindowProcW(window, message, wparam, lparam);
    }

    class Consumer
    {
    public:
        ~Consumer()
        {
            // Never acknowledge a frame with outstanding GPU reads, even on an
            // error. A stalled helper disables capture until the game restarts.
            if (frame_)
            {
                if (ownsConsumer_ && !reading_) Exchange(frame_->consumerPid, 0);
                UnmapViewOfFile(frame_);
            }
            if (window_ && IsWindow(window_)) DestroyWindow(window_);
        }
        void Open(DWORD pid, bool show, bool verify, const std::string& capturePath,
            bool verifyDepth, const std::string& depthPath, UINT depthClearOrdinal)
        {
            verify_ = verify;
            capturePath_ = capturePath;
            verifyDepth_ = verifyDepth;
            depthPath_ = depthPath;
            mapping_.value = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, MappingName(pid).c_str());
            if (!mapping_.value) throw std::runtime_error("producer mapping unavailable; start source/capture first");
            frame_ = static_cast<SharedFrame*>(MapViewOfFile(mapping_.value, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedFrame)));
            if (!frame_ || ReadInterlocked(frame_->active) != 1 || !ValidDescriptor(*frame_, pid))
                throw std::runtime_error("inactive or invalid frame bridge descriptor");
            if (!Claim(frame_->consumerPid, 0, static_cast<LONG>(GetCurrentProcessId())))
            {
                // Do not clear another consumer's claim on destruction.
                UnmapViewOfFile(frame_);
                frame_ = nullptr;
                throw std::runtime_error("mailbox already has a consumer");
            }
            ownsConsumer_ = true;
            Exchange(frame_->requestedDepthClear, static_cast<LONG>(depthClearOrdinal));
            producer_.value = OpenProcess(PROCESS_DUP_HANDLE | SYNCHRONIZE, FALSE, pid);
            if (!producer_.value) throw std::runtime_error("cannot open producer for handle duplication");
            const auto duplicate = [&](std::uint64_t remote, Handle& local)
            {
                if (!DuplicateHandle(producer_.value, reinterpret_cast<HANDLE>(static_cast<std::uintptr_t>(remote)),
                    GetCurrentProcess(), &local.value, 0, FALSE, DUPLICATE_SAME_ACCESS))
                    throw std::runtime_error("cannot duplicate producer GPU handle");
            };
            Handle texture, ready;
            duplicate(frame_->textureHandle, texture);
            duplicate(frame_->readyFenceHandle, ready);
            Require(CreateDXGIFactory2(0, IID_PPV_ARGS(&factory_)), "CreateDXGIFactory2");
            ComPtr<IDXGIAdapter1> adapter;
            const LUID luid{frame_->adapterLuidLow, frame_->adapterLuidHigh};
            Require(factory_->EnumAdapterByLuid(luid, IID_PPV_ARGS(&adapter)), "match producer adapter");
            Require(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device_)), "D3D12CreateDevice");
            Require(device_->OpenSharedHandle(texture.value, IID_PPV_ARGS(&color_)), "open shared color");
            Require(device_->OpenSharedHandle(ready.value, IID_PPV_ARGS(&ready_)), "open shared fence");
            if (verifyDepth || !depthPath.empty())
            {
                if (!frame_->depthTextureHandle) throw std::runtime_error("producer depth capture is disabled");
                Handle depth;
                duplicate(frame_->depthTextureHandle, depth);
                Require(device_->OpenSharedHandle(depth.value, IID_PPV_ARGS(&depth_)), "open shared depth");
                const auto desc = depth_->GetDesc();
                if (desc.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE2D || desc.Width != frame_->width ||
                    desc.Height != frame_->height || desc.Format != DXGI_FORMAT_R32_FLOAT ||
                    desc.SampleDesc.Count != 1 || desc.MipLevels != 1 || desc.DepthOrArraySize != 1)
                    throw std::runtime_error("depth GPU texture does not match descriptor");
                CreateReadback(depth_.Get(), depthReadback_, depthFootprint_, depthReadbackBytes_);
            }
            const auto colorDesc = color_->GetDesc();
            if (colorDesc.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE2D ||
                colorDesc.Width != frame_->width || colorDesc.Height != frame_->height ||
                colorDesc.Format != static_cast<DXGI_FORMAT>(frame_->format) ||
                colorDesc.SampleDesc.Count != 1 || colorDesc.MipLevels != 1 || colorDesc.DepthOrArraySize != 1)
                throw std::runtime_error("GPU texture does not match wire descriptor");
            D3D12_COMMAND_QUEUE_DESC queueDesc{};
            queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
            Require(device_->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&queue_)), "CreateCommandQueue");
            Require(device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator_)), "CreateCommandAllocator");
            Require(device_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator_.Get(), nullptr, IID_PPV_ARGS(&commands_)), "CreateCommandList");
            Require(commands_->Close(), "initial command list close");
            Require(device_->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&done_)), "CreateFence");
            event_.value = CreateEventW(nullptr, FALSE, FALSE, nullptr);
            if (!event_.value) throw std::runtime_error("cannot create fence completion event");

            if (verify || !capturePath.empty())
            {
                UINT rows = 0;
                UINT64 rowBytes = 0;
                UINT64 total = 0;
                device_->GetCopyableFootprints(&colorDesc, 0, 1, 0, &footprint_, &rows, &rowBytes, &total);
                readbackBytes_ = static_cast<SIZE_T>(total);
                D3D12_HEAP_PROPERTIES heap{};
                heap.Type = D3D12_HEAP_TYPE_READBACK;
                D3D12_RESOURCE_DESC buffer{};
                buffer.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
                buffer.Width = total;
                buffer.Height = 1;
                buffer.DepthOrArraySize = buffer.MipLevels = 1;
                buffer.SampleDesc.Count = 1;
                buffer.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
                Require(device_->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &buffer,
                    D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&readback_)), "create verification readback");
            }
            if (show) CreateWindowAndSwapChain();
            D3D12_FEATURE_DATA_D3D12_OPTIONS5 options{};
            const HRESULT rayQuery = device_->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &options, sizeof(options));
            std::printf("CONSUMER pointer_bits=%zu size=%ux%u DXR_tier=%u query=0x%08lx DLSS=not-integrated RT=not-integrated\n",
                sizeof(void*) * 8, frame_->width, frame_->height,
                static_cast<unsigned>(options.RaytracingTier), static_cast<unsigned long>(rayQuery));
            std::fflush(stdout);
        }

        unsigned Run(unsigned limit, DWORD timeoutMs)
        {
            unsigned consumed = 0;
            ULONGLONG deadline = GetTickCount64() + timeoutMs;
            bool lastDepthValid = false;
            // A pre-clear can occur while the prior slot is still Reading. The
            // resulting color frame is valid but depth is Missing. For a paired
            // artifact, wait at most 120 additional frames, never save stale z.
            while (consumed < limit || (!depthPath_.empty() && !lastDepthValid && consumed < limit + 120))
            {
                MSG message{};
                while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
                {
                    if (message.message == WM_QUIT) throw std::runtime_error("preview closed before capture completed");
                    TranslateMessage(&message);
                    DispatchMessageW(&message);
                }
                if (ReadInterlocked(frame_->active) != 1 || WaitForSingleObject(producer_.value, 0) == WAIT_OBJECT_0)
                    throw std::runtime_error("producer stopped before requested frame count");
                if (!Claim(frame_->slotState, static_cast<LONG>(SlotState::Ready), static_cast<LONG>(SlotState::Reading)))
                {
                    if (GetTickCount64() >= deadline) throw std::runtime_error("timed out waiting for producer frame");
                    Sleep(1);
                    continue;
                }
                reading_ = true;
                const auto id = frame_->frameId;
                lastDepth_ = {frame_->depthSourceFormat, frame_->depthSourceSamples, frame_->depthStatus,
                    frame_->depthReduction, frame_->depthResult, frame_->depthCapturedOrdinal, frame_->depthMatchingClears,
                    id, frame_->captureQpc};
                const bool validDepth = ValidDepthFrame(*frame_);
                lastDepthValid = validDepth;
                if (validDepth) ++depthCandidates_;
                else ++depthUnavailable_;
                if (verifyDepth_ && !validDepth) throw std::runtime_error("synthetic frame lacks valid depth");
                if (id == 0 || id <= lastFrame_) throw std::runtime_error("non-monotonic frame ID");
                WaitGpu(ready_.Get(), id);
                Require(allocator_->Reset(), "Reset allocator");
                Require(commands_->Reset(allocator_.Get(), nullptr), "Reset commands");
                Barrier(color_.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_SOURCE);
                ComPtr<ID3D12Resource> backbuffer;
                if (swapchain_)
                {
                    Require(swapchain_->GetBuffer(swapchain_->GetCurrentBackBufferIndex(), IID_PPV_ARGS(&backbuffer)), "GetBuffer");
                    Barrier(backbuffer.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_COPY_DEST);
                    commands_->CopyResource(backbuffer.Get(), color_.Get());
                    Barrier(backbuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PRESENT);
                }
                if (verify_ || (!capturePath_.empty() && consumed + 1 >= limit))
                {
                    D3D12_TEXTURE_COPY_LOCATION source{};
                    source.pResource = color_.Get();
                    source.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
                    D3D12_TEXTURE_COPY_LOCATION destination{};
                    destination.pResource = readback_.Get();
                    destination.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
                    destination.PlacedFootprint = footprint_;
                    commands_->CopyTextureRegion(&destination, 0, 0, 0, &source, nullptr);
                }
                if (depth_ && validDepth && (verifyDepth_ || consumed + 1 >= limit))
                {
                    Barrier(depth_.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_SOURCE);
                    D3D12_TEXTURE_COPY_LOCATION source{};
                    source.pResource = depth_.Get();
                    source.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
                    D3D12_TEXTURE_COPY_LOCATION destination{};
                    destination.pResource = depthReadback_.Get();
                    destination.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
                    destination.PlacedFootprint = depthFootprint_;
                    commands_->CopyTextureRegion(&destination, 0, 0, 0, &source, nullptr);
                    Barrier(depth_.Get(), D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_COMMON);
                }
                Barrier(color_.Get(), D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_COMMON);
                Require(commands_->Close(), "Close commands");
                ID3D12CommandList* lists[] = {commands_.Get()};
                queue_->ExecuteCommandLists(1, lists);
                Require(queue_->Signal(done_.Get(), id), "signal copy completion");
                WaitGpu(done_.Get(), id);
                if (verify_) VerifyPixels(id);
                if (verifyDepth_) VerifyDepth(id);
                LARGE_INTEGER now{};
                QueryPerformanceCounter(&now);
                const double delay = 1000.0 * static_cast<double>(now.QuadPart - frame_->captureQpc) /
                    static_cast<double>(frame_->qpcFrequency);
                if (delay > maxDelayMs_) maxDelayMs_ = delay;
                // GPU completion, not CPU command submission, releases ownership.
                Exchange(frame_->slotState, static_cast<LONG>(SlotState::Free));
                reading_ = false;
                lastFrame_ = id;
                ++consumed;
                if (swapchain_) Require(swapchain_->Present(1, 0), "Present");
                deadline = GetTickCount64() + timeoutMs;
            }
            std::printf("CONSUMER frames=%u last_frame=%llu verified=%s max_capture_to_copy_ms=%.3f\n",
                consumed, static_cast<unsigned long long>(lastFrame_), verify_ ? "yes" : "no", maxDelayMs_);
            std::printf("DEPTH candidate_frames=%u unavailable_frames=%u last_status=%u source_format=%u samples=%u hr=0x%08x captured_clear=%u matching_clears=%u\n",
                depthCandidates_, depthUnavailable_, lastDepth_.status, lastDepth_.format, lastDepth_.samples, lastDepth_.result,
                lastDepth_.ordinal, lastDepth_.clears);
            if (!capturePath_.empty()) SaveCapture();
            if (!depthPath_.empty()) SaveDepth();
            return consumed;
        }
    private:
        void CreateReadback(ID3D12Resource* texture, ComPtr<ID3D12Resource>& buffer,
            D3D12_PLACED_SUBRESOURCE_FOOTPRINT& footprint, SIZE_T& bytes)
        {
            const auto desc = texture->GetDesc();
            UINT rows = 0;
            UINT64 rowBytes = 0, total = 0;
            device_->GetCopyableFootprints(&desc, 0, 1, 0, &footprint, &rows, &rowBytes, &total);
            bytes = static_cast<SIZE_T>(total);
            D3D12_HEAP_PROPERTIES heap{};
            heap.Type = D3D12_HEAP_TYPE_READBACK;
            D3D12_RESOURCE_DESC output{};
            output.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
            output.Width = total;
            output.Height = 1;
            output.DepthOrArraySize = output.MipLevels = 1;
            output.SampleDesc.Count = 1;
            output.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
            Require(device_->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &output,
                D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&buffer)), "create depth readback");
        }
        std::vector<float> ReadDepthPixels()
        {
            std::vector<float> pixels(static_cast<SIZE_T>(frame_->width) * frame_->height);
            unsigned char* data = nullptr;
            const D3D12_RANGE range{0, depthReadbackBytes_};
            Require(depthReadback_->Map(0, &range, reinterpret_cast<void**>(&data)), "map depth pixels");
            for (UINT y = 0; y < frame_->height; ++y)
                std::memcpy(pixels.data() + static_cast<SIZE_T>(y) * frame_->width,
                    data + static_cast<SIZE_T>(y) * depthFootprint_.Footprint.RowPitch, static_cast<SIZE_T>(frame_->width) * sizeof(float));
            const D3D12_RANGE written{0, 0};
            depthReadback_->Unmap(0, &written);
            return pixels;
        }
        void VerifyDepth(UINT64 id)
        {
            const auto pixels = ReadDepthPixels();
            const float expected = static_cast<float>(id) / 1024.0f;
            for (float value : pixels)
                if (!std::isfinite(value) || std::fabs(value - expected) > 0.000001f)
                    throw std::runtime_error("depth verification failed: stale/torn/wrong frame");
        }
        void SaveDepth()
        {
            if (lastDepth_.status != static_cast<std::uint32_t>(DepthStatus::Candidate) || lastDepth_.result != 0)
            {
                std::fprintf(stderr, "DEPTH unavailable frame=%llu status=%u format=%u samples=%u hr=0x%08x\n",
                    static_cast<unsigned long long>(lastDepth_.frameId), lastDepth_.status, lastDepth_.format, lastDepth_.samples, lastDepth_.result);
                throw std::runtime_error("final frame has no valid candidate depth; stale pixels were not saved");
            }
            const auto pixels = ReadDepthPixels();
            float minimum = 1, maximum = 0;
            unsigned nonClear = 0;
            for (float value : pixels)
            {
                if (!std::isfinite(value) || value < 0 || value > 1) throw std::runtime_error("depth outside device-depth range");
                minimum = (std::min)(minimum, value);
                maximum = (std::max)(maximum, value);
                if (value > 0 && value < 1) ++nonClear;
            }
            // PFM uses bottom-to-top rows and negative scale for little endian.
            std::ofstream output(depthPath_, std::ios::binary | std::ios::trunc);
            output << "Pf\n" << frame_->width << ' ' << frame_->height << "\n-1.0\n";
            for (UINT y = frame_->height; y > 0; --y)
                output.write(reinterpret_cast<const char*>(pixels.data() + static_cast<SIZE_T>(y - 1) * frame_->width),
                    static_cast<std::streamsize>(frame_->width) * sizeof(float));
            output.close();
            if (!output) throw std::runtime_error("cannot save depth PFM");
            std::ofstream metadata(depthPath_ + ".json", std::ios::trunc);
            metadata << "{\n  \"candidateOnly\": true,\n  \"frameId\": " << lastDepth_.frameId << ",\n  \"captureQpc\": " << lastDepth_.captureQpc
                << ",\n  \"width\": " << frame_->width << ",\n  \"height\": " << frame_->height << ",\n  \"sourceFormat\": " << lastDepth_.format
                << ",\n  \"sourceSamples\": " << lastDepth_.samples << ",\n  \"reduction\": \"" << (lastDepth_.reduction ? "maximum" : "minimum")
                << "\",\n  \"capturedClearOrdinal\": " << lastDepth_.ordinal << ",\n  \"matchingClears\": " << lastDepth_.clears
                << ",\n  \"depthConvention\": \"unqualified\"\n}\n";
            metadata.close();
            if (!metadata) throw std::runtime_error("cannot save depth metadata");
            std::printf("DEPTH_CAPTURE frame=%llu min=%.9g max=%.9g non_clear_pixels=%u path=%s (raw candidate, convention unqualified)\n",
                static_cast<unsigned long long>(lastDepth_.frameId), minimum, maximum, nonClear, depthPath_.c_str());
        }
        void SaveCapture()
        {
            // BMP stores BGRA pixels. Strip D3D12's padded row pitch and swizzle
            // RGBA input; a negative height keeps the GPU's top-to-bottom order.
            const DWORD pixelBytes = frame_->width * frame_->height * 4;
            BITMAPFILEHEADER file{};
            file.bfType = 0x4d42;
            file.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
            file.bfSize = file.bfOffBits + pixelBytes;
            BITMAPINFOHEADER info{};
            info.biSize = sizeof(info);
            info.biWidth = static_cast<LONG>(frame_->width);
            info.biHeight = -static_cast<LONG>(frame_->height);
            info.biPlanes = 1;
            info.biBitCount = 32;
            info.biCompression = BI_RGB;
            info.biSizeImage = pixelBytes;
            std::vector<unsigned char> pixels(pixelBytes);
            unsigned char* data = nullptr;
            const D3D12_RANGE range{0, readbackBytes_};
            Require(readback_->Map(0, &range, reinterpret_cast<void**>(&data)), "map capture pixels");
            for (UINT y = 0; y < frame_->height; ++y)
                for (UINT x = 0; x < frame_->width; ++x)
                {
                    const auto* source = data + static_cast<SIZE_T>(y) * footprint_.Footprint.RowPitch + x * 4;
                    auto* destination = pixels.data() + (static_cast<SIZE_T>(y) * frame_->width + x) * 4;
                    const bool rgba = frame_->format == DXGI_FORMAT_R8G8B8A8_UNORM;
                    destination[0] = source[rgba ? 2 : 0];
                    destination[1] = source[1];
                    destination[2] = source[rgba ? 0 : 2];
                    destination[3] = source[3];
                }
            const D3D12_RANGE written{0, 0};
            readback_->Unmap(0, &written);
            std::ofstream output(capturePath_, std::ios::binary | std::ios::trunc);
            output.write(reinterpret_cast<const char*>(&file), sizeof(file));
            output.write(reinterpret_cast<const char*>(&info), sizeof(info));
            output.write(reinterpret_cast<const char*>(pixels.data()), pixelBytes);
            output.close();
            if (!output) throw std::runtime_error("cannot save capture BMP");
            std::printf("CAPTURE frame=%llu path=%s\n", static_cast<unsigned long long>(lastFrame_), capturePath_.c_str());
        }
        void WaitGpu(ID3D12Fence* fence, UINT64 value)
        {
            const UINT64 completed = fence->GetCompletedValue();
            if (completed == UINT64_MAX) throw std::runtime_error("GPU device removed");
            if (completed >= value) return;
            Require(fence->SetEventOnCompletion(value, event_.value), "SetEventOnCompletion");
            if (WaitForSingleObject(event_.value, 3000) != WAIT_OBJECT_0)
                throw std::runtime_error("GPU fence timeout; capture slot kept owned");
        }
        void Barrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after)
        {
            D3D12_RESOURCE_BARRIER barrier{};
            barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            barrier.Transition.pResource = resource;
            barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
            barrier.Transition.StateBefore = before;
            barrier.Transition.StateAfter = after;
            commands_->ResourceBarrier(1, &barrier);
        }
        void VerifyPixels(UINT64 id)
        {
            const bool rgba = frame_->format == DXGI_FORMAT_R8G8B8A8_UNORM;
            const unsigned char red = static_cast<unsigned char>(id & 255);
            const unsigned char expected[] = {rgba ? red : static_cast<unsigned char>(64),
                static_cast<unsigned char>((id >> 8) & 255), rgba ? static_cast<unsigned char>(64) : red, 255};
            unsigned char* data = nullptr;
            D3D12_RANGE range{0, readbackBytes_};
            Require(readback_->Map(0, &range, reinterpret_cast<void**>(&data)), "map verification pixels");
            bool valid = true;
            for (UINT y = 0; y < frame_->height && valid; ++y)
                for (UINT x = 0; x < frame_->width && valid; ++x)
                    for (UINT c = 0; c < 4; ++c)
                        if (data[static_cast<SIZE_T>(y) * footprint_.Footprint.RowPitch + x * 4 + c] != expected[c])
                        { valid = false; break; }
            const D3D12_RANGE written{0, 0};
            readback_->Unmap(0, &written);
            if (!valid) throw std::runtime_error("GPU pixel verification failed: stale/torn/wrong frame");
        }
        void CreateWindowAndSwapChain()
        {
            WNDCLASSW wc{};
            wc.lpfnWndProc = WindowProc;
            wc.hInstance = GetModuleHandleW(nullptr);
            wc.lpszClassName = L"OpenShimFrameBridgePresenter";
            if (!RegisterClassW(&wc)) throw std::runtime_error("RegisterClass failed");
            constexpr DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
            RECT rect{0, 0, static_cast<LONG>(frame_->width), static_cast<LONG>(frame_->height)};
            AdjustWindowRectEx(&rect, style, FALSE, WS_EX_NOACTIVATE);
            window_ = CreateWindowExW(WS_EX_NOACTIVATE, wc.lpszClassName,
                L"OpenShim DX12 frame transport preview (DLSS/RT pending)", style,
                CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
                nullptr, nullptr, wc.hInstance, nullptr);
            if (!window_) throw std::runtime_error("CreateWindow failed");
            DXGI_SWAP_CHAIN_DESC1 desc{};
            desc.Width = frame_->width;
            desc.Height = frame_->height;
            desc.Format = static_cast<DXGI_FORMAT>(frame_->format);
            desc.SampleDesc.Count = 1;
            desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            desc.BufferCount = 2;
            desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
            ComPtr<IDXGISwapChain1> swap;
            Require(factory_->CreateSwapChainForHwnd(queue_.Get(), window_, &desc, nullptr, nullptr, &swap), "CreateSwapChainForHwnd");
            Require(swap.As(&swapchain_), "IDXGISwapChain3");
            Require(factory_->MakeWindowAssociation(window_, DXGI_MWA_NO_ALT_ENTER), "disable exclusive fullscreen");
            ShowWindow(window_, SW_SHOWNOACTIVATE);
        }
        Handle mapping_, producer_, event_;
        SharedFrame* frame_ = nullptr;
        HWND window_ = nullptr;
        bool verify_ = false;
        bool verifyDepth_ = false;
        std::string capturePath_;
        std::string depthPath_;
        struct DepthMetadata
        {
            std::uint32_t format, samples, status, reduction, result, ordinal, clears;
            std::uint64_t frameId, captureQpc;
        } lastDepth_{};
        unsigned depthCandidates_ = 0, depthUnavailable_ = 0;
        bool ownsConsumer_ = false;
        bool reading_ = false;
        UINT64 lastFrame_ = 0;
        double maxDelayMs_ = 0;
        ComPtr<IDXGIFactory4> factory_;
        ComPtr<ID3D12Device> device_;
        ComPtr<ID3D12Resource> color_, readback_;
        ComPtr<ID3D12Resource> depth_, depthReadback_;
        ComPtr<ID3D12Fence> ready_, done_;
        ComPtr<ID3D12CommandQueue> queue_;
        ComPtr<ID3D12CommandAllocator> allocator_;
        ComPtr<ID3D12GraphicsCommandList> commands_;
        ComPtr<IDXGISwapChain3> swapchain_;
        D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint_{};
        SIZE_T readbackBytes_ = 0;
        D3D12_PLACED_SUBRESOURCE_FOOTPRINT depthFootprint_{};
        SIZE_T depthReadbackBytes_ = 0;
    };
}

int main(int argc, char** argv)
{
    DWORD pid = 0;
    unsigned frames = 120;
    DWORD timeoutMs = 5000;
    bool verify = false;
    bool show = false;
    std::string capturePath;
    std::string depthPath;
    bool verifyDepth = false;
    UINT depthClearOrdinal = 0;
    for (int i = 1; i < argc; ++i)
    {
        const std::string arg(argv[i]);
        if (arg == "--verify") verify = true;
        else if (arg == "--show") show = true;
        else if (arg == "--verify-depth") verifyDepth = true;
        else if (arg == "--depth-clear-ordinal" && i + 1 < argc)
        {
            char* end = nullptr;
            const auto value = std::strtoul(argv[++i], &end, 10);
            if (!*argv[i] || *end || value > 8) return 2;
            depthClearOrdinal = value;
        }
        else if (arg == "--capture-depth-pfm" && i + 1 < argc)
        {
            depthPath = argv[++i];
            if (depthPath.empty()) return 2;
        }
        else if (arg == "--capture-bmp" && i + 1 < argc)
        {
            capturePath = argv[++i];
            if (capturePath.empty()) return 2;
        }
        else if ((arg == "--pid" || arg == "--frames" || arg == "--timeout-ms") && i + 1 < argc)
        {
            char* end = nullptr;
            const unsigned long value = std::strtoul(argv[++i], &end, 10);
            if (!*argv[i] || *end || value == 0 || value > 1000000) return 2;
            if (arg == "--pid") pid = value;
            else if (arg == "--frames") frames = value;
            else timeoutMs = value;
        }
        else
        {
            std::fprintf(stderr, "usage: frame_bridge_presenter --pid N [--frames N] [--timeout-ms N] [--show] [--verify] [--capture-bmp PATH] [--verify-depth] [--capture-depth-pfm PATH] [--depth-clear-ordinal 0..8]\n");
            return 2;
        }
    }
    if (!pid) return 2;
    try
    {
        Consumer consumer;
        consumer.Open(pid, show, verify, capturePath, verifyDepth, depthPath, depthClearOrdinal);
        return consumer.Run(frames, timeoutMs) >= frames ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::fprintf(stderr, "CONSUMER ERROR: %s\n", error.what());
        return 1;
    }
}
