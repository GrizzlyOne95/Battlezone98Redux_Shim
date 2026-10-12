#include "frame_bridge_producer.h"
#include "frame_bridge_history.h"
#include "gpu_motion.h"
#include "streamline_fg.h"
#include "visible_rt.h"
#include "gpu_blit.h"
#include "window_recorder.h"
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
#include <iomanip>
#include <filesystem>

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
            try { recorder_.Stop(); } catch (const std::exception& e) { std::fprintf(stderr, "RECORDING ERROR: %s\n", e.what()); }
            frameGeneration_.Shutdown(); // DXGI/device objects still alive.
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
            bool verifyDepth, const std::string& depthPath, UINT depthClearOrdinal, bool requireCamera, const std::string& motionPath,
            const std::string& scenePath, bool verifyScene, UINT sceneStage,
            const std::wstring& streamlineDirectory, const std::string& fgReport, bool visibleAO, const std::string& rtCapture, bool development,
            const std::string& recording, const std::string& rendererRecording)
        {
            verify_ = verify;
            capturePath_ = capturePath;
            verifyDepth_ = verifyDepth;
            depthPath_ = depthPath;
            requireCamera_ = requireCamera;
            motionPath_ = motionPath;
            scenePath_ = scenePath; verifyScene_ = verifyScene;
            sceneStage_ = sceneStage;
            fgMode_ = !streamlineDirectory.empty(); fgReport_ = fgReport;
            rtMode_ = visibleAO; rtPath_ = rtCapture;
            development_ = development;
            if (!rendererRecording.empty())
            {
                rendererRecording_.open(rendererRecording, std::ios::binary | std::ios::trunc);
                if (!rendererRecording_) throw std::runtime_error("open rendered-frame recording");
            }
            if (fgMode_)
                frameGeneration_.Initialize(streamlineDirectory, (std::filesystem::absolute(fgReport).parent_path() / L"streamline").wstring(), development);
            mapping_.value = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, MappingName(pid).c_str());
            if (!mapping_.value) throw std::runtime_error("producer mapping unavailable; start source/capture first");
            frame_ = static_cast<SharedFrame*>(MapViewOfFile(mapping_.value, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedFrame)));
            if (!frame_ || ReadInterlocked(frame_->active) != 1 || !ValidDescriptor(*frame_, pid))
                throw std::runtime_error("inactive or invalid frame bridge descriptor");
            if (rendererRecording_.is_open())
            {
                rendererRecording_.write("BZRINP1\0", 8);
                rendererRecording_.write(reinterpret_cast<const char*>(&frame_->width), 4);
                rendererRecording_.write(reinterpret_cast<const char*>(&frame_->height), 4);
            }
            if (!Claim(frame_->consumerPid, 0, static_cast<LONG>(GetCurrentProcessId())))
            {
                // Do not clear another consumer's claim on destruction.
                UnmapViewOfFile(frame_);
                frame_ = nullptr;
                throw std::runtime_error("mailbox already has a consumer");
            }
            ownsConsumer_ = true;
            Exchange(frame_->requestedDepthClear, static_cast<LONG>(depthClearOrdinal));
            Exchange(frame_->requestedSceneStage, static_cast<LONG>(sceneStage));
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
            if (fgMode_)
            {
                auto* proxy = factory_.Detach(); frameGeneration_.Upgrade(reinterpret_cast<void**>(&proxy)); factory_.Attach(proxy);
            }
            ComPtr<IDXGIAdapter1> adapter;
            const LUID luid{frame_->adapterLuidLow, frame_->adapterLuidHigh};
            Require(factory_->EnumAdapterByLuid(luid, IID_PPV_ARGS(&adapter)), "match producer adapter");
            Require(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device_)), "D3D12CreateDevice");
            if (fgMode_)
            {
                frameGeneration_.SetDevice(device_.Get(), luid, frame_->width, frame_->height, static_cast<DXGI_FORMAT>(frame_->format),
                    rtMode_ ? DXGI_FORMAT_R8G8B8A8_UNORM : static_cast<DXGI_FORMAT>(frame_->format));
                // Only queue creation needs the proxy. Resources and command
                // lists continue using the original native D3D12 device.
                device_.CopyTo(&queueDevice_);
                auto* proxy = queueDevice_.Detach(); frameGeneration_.Upgrade(reinterpret_cast<void**>(&proxy)); queueDevice_.Attach(proxy);
            }
            Require(device_->OpenSharedHandle(texture.value, IID_PPV_ARGS(&color_)), "open shared color");
            Require(device_->OpenSharedHandle(ready.value, IID_PPV_ARGS(&ready_)), "open shared fence");
            if (!scenePath.empty() || verifyScene || fgMode_ || rtMode_)
            {
                if (!frame_->sceneColorHandle) throw std::runtime_error("producer pre-clear scene color is disabled");
                Handle scene;
                duplicate(frame_->sceneColorHandle, scene);
                Require(device_->OpenSharedHandle(scene.value, IID_PPV_ARGS(&sceneColor_)), "open shared scene color");
                const auto desc = sceneColor_->GetDesc();
                if (desc.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE2D || desc.Width != frame_->width || desc.Height != frame_->height ||
                    desc.Format != static_cast<DXGI_FORMAT>(frame_->format) || desc.SampleDesc.Count != 1 || desc.MipLevels != 1 || desc.DepthOrArraySize != 1)
                    throw std::runtime_error("scene color texture does not match descriptor");
                CreateReadback(sceneColor_.Get(), sceneReadback_, sceneFootprint_, sceneReadbackBytes_);
                if (fgMode_ || rtMode_) CreatePrivateTexture(sceneColor_.Get(), fgScene_);
            }
            if (verifyDepth || !depthPath.empty() || fgMode_ || rtMode_)
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
                if (fgMode_ || rtMode_) CreatePrivateTexture(depth_.Get(), fgDepth_);
                if (fgMode_) gpuMotion_.Initialize(device_.Get(), fgDepth_.Get());
            }
            const auto colorDesc = color_->GetDesc();
            if (colorDesc.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE2D ||
                colorDesc.Width != frame_->width || colorDesc.Height != frame_->height ||
                colorDesc.Format != static_cast<DXGI_FORMAT>(frame_->format) ||
                colorDesc.SampleDesc.Count != 1 || colorDesc.MipLevels != 1 || colorDesc.DepthOrArraySize != 1)
                throw std::runtime_error("GPU texture does not match wire descriptor");
            if (rtMode_)
            {
                CreatePrivateTexture(color_.Get(), rtFinal_);
                rayTracing_.Initialize(device_.Get(), fgDepth_.Get(), fgScene_.Get(), rtFinal_.Get());
                blit_.Initialize(device_.Get(), rayTracing_.FinalOutput(), static_cast<DXGI_FORMAT>(frame_->format));
                if (!rtPath_.empty() || rendererRecording_.is_open()) CreateReadback(rayTracing_.FinalOutput(), rtReadback_, rtFootprint_, rtReadbackBytes_);
            }
            D3D12_COMMAND_QUEUE_DESC queueDesc{};
            queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
            Require((fgMode_ ? queueDevice_.Get() : device_.Get())->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&queue_)), "CreateCommandQueue");
            Require(device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator_)), "CreateCommandAllocator");
            Require(device_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator_.Get(), nullptr, IID_PPV_ARGS(&commands_)), "CreateCommandList");
            Require(commands_->Close(), "initial command list close");
            Require(device_->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&done_)), "CreateFence");
            event_.value = CreateEventW(nullptr, FALSE, FALSE, nullptr);
            if (!event_.value) throw std::runtime_error("cannot create fence completion event");

            if (verify || !capturePath.empty() || rendererRecording_.is_open())
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
            if (!recording.empty()) recorder_.Start(window_, recording);
            D3D12_FEATURE_DATA_D3D12_OPTIONS5 options{};
            const HRESULT rayQuery = device_->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &options, sizeof(options));
            std::printf("CONSUMER pointer_bits=%zu size=%ux%u DXR_tier=%u query=0x%08lx DLSS=%s RT=%s\n",
                sizeof(void*) * 8, frame_->width, frame_->height,
                static_cast<unsigned>(options.RaytracingTier), static_cast<unsigned long>(rayQuery), fgMode_ ? "experimental-camera-motion-preview" : "not-integrated",
                rtMode_ ? "experimental-visible-geometry-DXR-AO" : "not-integrated");
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
            while (consumed < limit || (((!depthPath_.empty() && !lastDepthValid) ||
                (!motionPath_.empty() && !lastPair_.comparable) || (!scenePath_.empty() && !lastSceneValid_) ||
                (!rtPath_.empty() && !lastRtValid_)) && consumed < limit + 120))
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
                lastCamera_ = frame_->camera;
                lastCameraValid_ = ValidCameraFrame(*frame_);
                lastSceneValid_ = ValidSceneColorFrame(*frame_) && frame_->sceneColorStage == sceneStage_;
                lastSceneStatus_ = frame_->sceneColorStatus; lastSceneOrdinal_ = frame_->sceneColorCapturedOrdinal;
                lastSceneSource_ = frame_->sceneColorSource;
                lastSceneStage_ = frame_->sceneColorStage;
                lastPair_ = history_.Push(*frame_);
                const bool validDepth = ValidDepthFrame(*frame_);
                lastRtValid_ = rtMode_ && validDepth && lastCameraValid_ && lastSceneValid_ && InspectPerspective(lastCamera_).recognized;
                lastDepthValid = validDepth && (!requireCamera_ || lastCameraValid_);
                if (validDepth) ++depthCandidates_;
                else ++depthUnavailable_;
                if (verifyDepth_ && !validDepth) throw std::runtime_error("synthetic frame lacks valid depth");
                if (verifyScene_ && !lastSceneValid_) throw std::runtime_error("synthetic frame lacks scene color/depth/camera pair");
                if (id == 0 || id <= lastFrame_) throw std::runtime_error("non-monotonic frame ID");
                WaitGpu(ready_.Get(), id);
                if (fgMode_) frameGeneration_.Begin(lastPair_, consumed + 1, validDepth && lastCameraValid_ && lastSceneValid_);
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
                if (verify_ || rendererRecording_.is_open() || (!capturePath_.empty() && consumed + 1 >= limit))
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
                if (sceneColor_ && lastSceneValid_ && (verifyScene_ || consumed + 1 >= limit))
                {
                    Barrier(sceneColor_.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_SOURCE);
                    D3D12_TEXTURE_COPY_LOCATION source{};
                    source.pResource = sceneColor_.Get(); source.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
                    D3D12_TEXTURE_COPY_LOCATION destination{};
                    destination.pResource = sceneReadback_.Get(); destination.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
                    destination.PlacedFootprint = sceneFootprint_;
                    commands_->CopyTextureRegion(&destination, 0, 0, 0, &source, nullptr);
                    Barrier(sceneColor_.Get(), D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_COMMON);
                }
                if (fgMode_ || rtMode_)
                {
                    if (validDepth && lastSceneValid_ && lastCameraValid_)
                    {
                        CopyPrivate(depth_.Get(), fgDepth_.Get()); CopyPrivate(sceneColor_.Get(), fgScene_.Get());
                        if (fgMode_)
                        {
                            Barrier(fgDepth_.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
                            gpuMotion_.Record(commands_.Get(), lastPair_);
                            Barrier(fgDepth_.Get(), D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_COMMON);
                        }
                    }
                    if (lastRtValid_)
                    {
                        CopyPrivate(color_.Get(), rtFinal_.Get()); rayTracing_.Record(commands_.Get(), lastCamera_); ++rtFrames_;
                        if (backbuffer) blit_.Record(commands_.Get(), backbuffer.Get());
                        if (rendererRecording_.is_open() || (!rtPath_.empty() && consumed + 1 >= limit))
                        {
                            auto* output = rayTracing_.FinalOutput();
                            Barrier(output, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_SOURCE);
                            D3D12_TEXTURE_COPY_LOCATION source{}; source.pResource = output; source.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
                            D3D12_TEXTURE_COPY_LOCATION target{}; target.pResource = rtReadback_.Get();
                            target.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT; target.PlacedFootprint = rtFootprint_;
                            commands_->CopyTextureRegion(&target, 0, 0, 0, &source, nullptr);
                            Barrier(output, D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_COMMON);
                        }
                    }
                    // These are private helper copies. Returning the shared
                    // slot cannot allow the game to overwrite SDK inputs.
                    if (fgMode_) frameGeneration_.Tag(commands_.Get(), fgDepth_.Get(), gpuMotion_.Output(),
                        rtMode_ && lastRtValid_ ? rayTracing_.SceneOutput() : fgScene_.Get());
                }
                Require(commands_->Close(), "Close commands");
                ID3D12CommandList* lists[] = {commands_.Get()};
                queue_->ExecuteCommandLists(1, lists);
                if (fgMode_) frameGeneration_.Submitted();
                Require(queue_->Signal(done_.Get(), id * 2), "signal copy completion");
                WaitGpu(done_.Get(), id * 2);
                if (verify_) VerifyPixels(id);
                if (verifyScene_) VerifyPixels(id, true);
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
                const unsigned additionalBeforePresent = frameGeneration_.AdditionalPresents();
                if (swapchain_)
                {
                    if (fgMode_) frameGeneration_.BeforePresent();
                    Require(swapchain_->Present(fgMode_ ? 0 : 1, 0), "Present");
                    if (fgMode_)
                    {
                        frameGeneration_.AfterPresent();
                        if (consumed % 30 == 0)
                        {
                            const auto title = L"Battlezone experimental preview | DLSS FG extra presents: " +
                                std::to_wstring(frameGeneration_.AdditionalPresents()) +
                                (rtMode_ ? L" | hardware DXR AO (visible geometry)" : L" | camera motion only");
                            SetWindowTextW(window_, title.c_str());
                        }
                        // SDK input work is blocked onto this presenting
                        // queue. Drain after Present before reusing copies.
                        Require(queue_->Signal(done_.Get(), id * 2 + 1), "signal SDK input completion"); WaitGpu(done_.Get(), id * 2 + 1);
                    }
                }
                if (rendererRecording_.is_open()) RecordRenderedFrame(additionalBeforePresent);
                deadline = GetTickCount64() + timeoutMs;
            }
            std::printf("CONSUMER frames=%u last_frame=%llu verified=%s max_capture_to_copy_ms=%.3f\n",
                consumed, static_cast<unsigned long long>(lastFrame_), verify_ ? "yes" : "no", maxDelayMs_);
            std::printf("DEPTH candidate_frames=%u unavailable_frames=%u last_status=%u source_format=%u samples=%u hr=0x%08x captured_clear=%u matching_clears=%u\n",
                depthCandidates_, depthUnavailable_, lastDepth_.status, lastDepth_.format, lastDepth_.samples, lastDepth_.result,
                lastDepth_.ordinal, lastDepth_.clears);
            const auto facts = InspectPerspective(lastCamera_);
            std::printf("CAMERA valid_observation=%s status=%u name=%s near=%.9g far=%.9g perspective=%s forward=%d reversed=%u aspect=%.6g fov_y=%.6g (pass identity unqualified)\n",
                lastCameraValid_ ? "yes" : "no", lastCamera_.status, ValidCameraSnapshot(lastCamera_) ? lastCamera_.name : "unavailable",
                lastCamera_.nearClip, lastCamera_.farClip, facts.recognized ? "recognized" : "unqualified", facts.forwardSign,
                facts.reversed ? 1u : 0u, facts.aspect, facts.verticalFovDegrees);
            if (!capturePath_.empty()) SaveCapture();
            if (!depthPath_.empty()) SaveDepth();
            if (!motionPath_.empty()) SaveCameraMotion();
            if (rtMode_)
            {
                std::printf("DXR_AO traced_frames=%u triangle_capacity=%u rays_per_surface_pixel=8 visible_geometry_only=yes\n", rtFrames_, rayTracing_.TriangleCapacity());
                if (!rtPath_.empty())
                {
                    if (!lastRtValid_) throw std::runtime_error("final frame lacks valid DXR inputs");
                    SaveCapture(false, true);
                    std::ofstream out(rtPath_ + ".json");
                    out << "{\n  \"previewOnly\": true,\n  \"hardwareDXR\": true,\n  \"visibleDepthGeometryOnly\": true,\n  \"hudMaskQualified\": false,\n  \"frameId\": " << lastFrame_
                        << ",\n  \"tracedFrames\": " << rtFrames_ << ",\n  \"triangleCapacity\": " << rayTracing_.TriangleCapacity() << ",\n  \"raysPerSurfacePixel\": 8\n}\n";
                    if (!out) throw std::runtime_error("save DXR capture metadata");
                }
            }
            if (!scenePath_.empty())
            {
                if (!lastSceneValid_) throw std::runtime_error("final frame lacks scene color/depth/camera pair");
                SaveCapture(true);
                std::ofstream metadata(scenePath_ + ".json", std::ios::trunc);
                metadata << "{\n  \"candidateOnly\": true,\n  \"hudFreeQualified\": false,\n  \"protocolVersion\": " << kVersion
                    << ",\n  \"frameId\": " << lastFrame_ << ",\n  \"capturedClearOrdinal\": " << lastSceneOrdinal_
                    << ",\n  \"status\": " << lastSceneStatus_ << ",\n  \"source\": " << lastSceneSource_
                    << ",\n  \"stage\": " << lastSceneStage_
                    << ",\n  \"width\": " << frame_->width << ",\n  \"height\": " << frame_->height << ",\n  \"cameraObservation\": ";
                WriteCamera(metadata); metadata << "\n}\n"; metadata.close();
                if (!metadata) throw std::runtime_error("cannot save scene color metadata");
            }
            if (fgMode_) frameGeneration_.SaveReport(fgReport_);
            recorder_.Stop();
            if (rendererRecording_.is_open())
            {
                rendererRecording_.close();
                if (!rendererRecording_) throw std::runtime_error("finish rendered-frame recording");
                std::printf("RECORDING source=renderer-input-frames frames=%u (SDK-generated images are not captured)\n", consumed);
            }
            return consumed;
        }
    private:
        void RecordRenderedFrame(unsigned additionalBeforePresent)
        {
            auto* resource = lastRtValid_ ? rtReadback_.Get() : readback_.Get();
            const auto& footprint = lastRtValid_ ? rtFootprint_ : footprint_;
            const auto bytes = lastRtValid_ ? rtReadbackBytes_ : readbackBytes_;
            const bool rgba = lastRtValid_ || frame_->format == DXGI_FORMAT_R8G8B8A8_UNORM;
            unsigned char* mapped = nullptr; D3D12_RANGE range{0, bytes};
            Require(resource->Map(0, &range, reinterpret_cast<void**>(&mapped)), "map rendered recording");
            std::vector<unsigned char> row(static_cast<SIZE_T>(frame_->width) * 4);
            LARGE_INTEGER now{}, frequency{}; QueryPerformanceCounter(&now); QueryPerformanceFrequency(&frequency);
            const std::int64_t time = static_cast<std::int64_t>(static_cast<double>(now.QuadPart) * 10000000.0 / frequency.QuadPart);
            const std::uint32_t extra = frameGeneration_.AdditionalPresents();
            const std::uint32_t flags = (lastRtValid_ ? 1u : 0u) | (fgMode_ && frameGeneration_.Enabled() ? 2u : 0u) |
                (extra > additionalBeforePresent ? 4u : 0u);
            rendererRecording_.write(reinterpret_cast<const char*>(&time), 8);
            rendererRecording_.write(reinterpret_cast<const char*>(&lastFrame_), 8);
            rendererRecording_.write(reinterpret_cast<const char*>(&extra), 4);
            rendererRecording_.write(reinterpret_cast<const char*>(&flags), 4);
            for (UINT y = 0; y < frame_->height; ++y)
            {
                const auto* source = mapped + footprint.Offset + static_cast<SIZE_T>(y) * footprint.Footprint.RowPitch;
                for (UINT x = 0; x < frame_->width; ++x)
                {
                    row[x * 4] = source[x * 4 + (rgba ? 2 : 0)]; row[x * 4 + 1] = source[x * 4 + 1];
                    row[x * 4 + 2] = source[x * 4 + (rgba ? 0 : 2)]; row[x * 4 + 3] = source[x * 4 + 3];
                }
                rendererRecording_.write(reinterpret_cast<const char*>(row.data()), static_cast<std::streamsize>(row.size()));
            }
            const D3D12_RANGE none{0, 0}; resource->Unmap(0, &none);
            if (!rendererRecording_) throw std::runtime_error("write rendered-frame recording");
        }
        void CreatePrivateTexture(ID3D12Resource* source, ComPtr<ID3D12Resource>& output)
        {
            D3D12_HEAP_PROPERTIES heap{}; heap.Type = D3D12_HEAP_TYPE_DEFAULT;
            auto desc = source->GetDesc(); desc.Flags = D3D12_RESOURCE_FLAG_NONE;
            Require(device_->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_COMMON,
                nullptr, IID_PPV_ARGS(&output)), "create private SDK input");
        }
        void CopyPrivate(ID3D12Resource* source, ID3D12Resource* output)
        {
            Barrier(source, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_SOURCE);
            Barrier(output, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
            commands_->CopyResource(output, source);
            Barrier(output, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_COMMON);
            Barrier(source, D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_COMMON);
        }
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
            if (!lastCameraValid_) throw std::runtime_error("synthetic camera observation invalid");
            const bool motionFixture = std::strcmp(lastCamera_.name, "SyntheticMotionCamera") == 0;
            const bool idFixture = std::strcmp(lastCamera_.name, "SyntheticFrameCamera") == 0;
            const float translation = motionFixture ? static_cast<float>(id) / 1000.0f : static_cast<float>(id);
            if ((!motionFixture && !idFixture) ||
                lastCamera_.matrixSource != static_cast<std::uint32_t>(CameraMatrixSource::Synthetic) ||
                std::fabs(lastCamera_.view[3] - translation) > 0.000001f ||
                !InspectPerspective(lastCamera_).recognized)
                throw std::runtime_error("synthetic camera metadata does not match GPU frame ID/projection");
            const auto pixels = ReadDepthPixels();
            const float expected = static_cast<float>(id) / 1024.0f;
            for (float value : pixels)
                if (!std::isfinite(value) || std::fabs(value - expected) > 0.000001f)
                    throw std::runtime_error("depth verification failed: stale/torn/wrong frame");
        }
        void SaveDepth()
        {
            if (requireCamera_ && !lastCameraValid_)
                throw std::runtime_error("final depth frame has no matching camera observation; camera capture failed closed");
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
            metadata << std::setprecision(9);
            metadata << "{\n  \"candidateOnly\": true,\n  \"protocolVersion\": " << kVersion
                << ",\n  \"frameId\": " << lastDepth_.frameId << ",\n  \"captureQpc\": " << lastDepth_.captureQpc
                << ",\n  \"width\": " << frame_->width << ",\n  \"height\": " << frame_->height << ",\n  \"sourceFormat\": " << lastDepth_.format
                << ",\n  \"sourceSamples\": " << lastDepth_.samples << ",\n  \"reduction\": \"" << (lastDepth_.reduction ? "maximum" : "minimum")
                << "\",\n  \"capturedClearOrdinal\": " << lastDepth_.ordinal << ",\n  \"matchingClears\": " << lastDepth_.clears
                << ",\n  \"depthConvention\": \"unqualified\",\n  \"cameraObservation\": ";
            WriteCamera(metadata);
            metadata << "\n}\n";
            metadata.close();
            if (!metadata) throw std::runtime_error("cannot save depth metadata");
            std::printf("DEPTH_CAPTURE frame=%llu min=%.9g max=%.9g non_clear_pixels=%u path=%s (raw candidate, convention unqualified)\n",
                static_cast<unsigned long long>(lastDepth_.frameId), minimum, maximum, nonClear, depthPath_.c_str());
        }
        void WriteCamera(std::ostream& output)
        {
            const auto& camera = lastCamera_;
            const auto facts = InspectPerspective(camera);
            output << "{\n    \"valid\": " << (lastCameraValid_ ? "true" : "false") << ",\n    \"status\": " << camera.status;
            if (ValidCameraSnapshot(camera))
            {
                output << ",\n    \"candidateOnly\": true,\n    \"cameraIdentity\": " << camera.cameraIdentity
                    << ",\n    \"name\": \"" << camera.name << "\",\n    \"width\": " << camera.width << ",\n    \"height\": " << camera.height
                    << ",\n    \"nearClip\": " << camera.nearClip << ",\n    \"farClip\": " << camera.farClip
                    << ",\n    \"stage\": " << camera.stage << ",\n    \"clearOrdinal\": " << camera.clearOrdinal
                    << ",\n    \"observationQpc\": " << camera.observationQpc
                    << ",\n    \"matrixSource\": \"" << CameraMatrixSourceName(camera.matrixSource)
                    << "\",\n    \"layout\": \"Ogre row-major, column vectors\",\n    \"view\": [";
                for (unsigned i = 0; i < 16; ++i) output << (i ? ", " : "") << camera.view[i];
                output << "],\n    \"projection\": [";
                for (unsigned i = 0; i < 16; ++i) output << (i ? ", " : "") << camera.projection[i];
                output << "],\n    \"recognizedPerspective\": " << (facts.recognized ? "true" : "false");
                if (facts.recognized)
                    output << ",\n    \"forwardSign\": " << facts.forwardSign << ",\n    \"reversed\": " << (facts.reversed ? "true" : "false")
                        << ",\n    \"projectedNearDepth\": " << facts.nearDepth << ",\n    \"projectedFarDepth\": " << facts.farDepth
                        << ",\n    \"projectionAspect\": " << facts.aspect << ",\n    \"verticalFovDegrees\": " << facts.verticalFovDegrees;
            }
            output << "\n  }";
        }
        void SaveCameraMotion()
        {
            CameraReprojection motion;
            if (!lastCameraValid_ || !motion.Prepare(lastPair_))
                throw std::runtime_error("camera motion diagnostic lacks comparable captured history");
            const auto depth = ReadDepthPixels();
            std::ofstream output(motionPath_, std::ios::binary | std::ios::trunc);
            if (!output) throw std::runtime_error("cannot open camera motion PFM");
            // RGB float PFM: previous-minus-current X/Y in pixels, validity in B.
            // Zero vectors with validity=0 are absent data, never DLSS tags.
            output << "PF\n" << frame_->width << " " << frame_->height << "\n-1.0\n";
            std::vector<float> row(static_cast<SIZE_T>(frame_->width) * 3);
            unsigned valid = 0;
            double maximum = 0;
            for (UINT y = frame_->height; y > 0; --y)
            {
                for (UINT x = 0; x < frame_->width; ++x)
                {
                    const auto pixel = motion.Pixel(x, y - 1, depth[static_cast<SIZE_T>(y - 1) * frame_->width + x]);
                    row[x * 3] = pixel.x; row[x * 3 + 1] = pixel.y; row[x * 3 + 2] = pixel.valid;
                    if (pixel.valid) { ++valid; maximum = std::max(maximum, std::hypot(static_cast<double>(pixel.x), pixel.y)); }
                }
                output.write(reinterpret_cast<const char*>(row.data()), static_cast<std::streamsize>(row.size() * sizeof(float)));
            }
            output.close();
            if (!output) throw std::runtime_error("cannot save camera motion PFM");
            std::ofstream metadata(motionPath_ + ".json", std::ios::trunc);
            metadata << std::setprecision(9) << "{\n  \"diagnosticOnly\": true,\n  \"dlssReady\": false,"
                << "\n  \"model\": \"static scene, absolute camera reprojection\","
                << "\n  \"channels\": \"previous-minus-current pixel X, pixel Y, validity\","
                << "\n  \"width\": " << frame_->width << ",\n  \"height\": " << frame_->height
                << ",\n  \"previousFrameId\": " << lastPair_.previousFrame << ",\n  \"currentFrameId\": " << lastPair_.currentFrame
                << ",\n  \"intervalSeconds\": " << lastPair_.intervalSeconds
                << ",\n  \"history\": \"captured frames; original presents and camera cuts unqualified\","
                << "\n  \"missing\": \"object/skinning motion, previous-depth occlusion, HUD and per-draw overrides\","
                << "\n  \"validPixels\": " << valid << ",\n  \"maximumPixels\": " << maximum
                << ",\n  \"previousView\": [";
            for (unsigned i = 0; i < 16; ++i) metadata << (i ? ", " : "") << lastPair_.previous.view[i];
            metadata << "],\n  \"currentCamera\": "; WriteCamera(metadata); metadata << "\n}\n";
            metadata.close();
            if (!metadata) throw std::runtime_error("cannot save camera motion metadata");
            std::printf("CAMERA_MOTION diagnostic_only=yes previous=%llu current=%llu valid_pixels=%u max_pixels=%.9g path=%s\n",
                static_cast<unsigned long long>(lastPair_.previousFrame), static_cast<unsigned long long>(lastPair_.currentFrame),
                valid, maximum, motionPath_.c_str());
        }
        void SaveCapture(bool scene = false, bool rt = false)
        {
            auto* readback = rt ? rtReadback_.Get() : scene ? sceneReadback_.Get() : readback_.Get();
            const auto& footprint = rt ? rtFootprint_ : scene ? sceneFootprint_ : footprint_;
            const auto bytes = rt ? rtReadbackBytes_ : scene ? sceneReadbackBytes_ : readbackBytes_;
            const auto& path = rt ? rtPath_ : scene ? scenePath_ : capturePath_;
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
            const D3D12_RANGE range{0, bytes};
            Require(readback->Map(0, &range, reinterpret_cast<void**>(&data)), "map capture pixels");
            for (UINT y = 0; y < frame_->height; ++y)
                for (UINT x = 0; x < frame_->width; ++x)
                {
                    const auto* source = data + static_cast<SIZE_T>(y) * footprint.Footprint.RowPitch + x * 4;
                    auto* destination = pixels.data() + (static_cast<SIZE_T>(y) * frame_->width + x) * 4;
                    const bool rgba = rt || frame_->format == DXGI_FORMAT_R8G8B8A8_UNORM;
                    destination[0] = source[rgba ? 2 : 0];
                    destination[1] = source[1];
                    destination[2] = source[rgba ? 0 : 2];
                    destination[3] = source[3];
                }
            const D3D12_RANGE written{0, 0};
            readback->Unmap(0, &written);
            std::ofstream output(path, std::ios::binary | std::ios::trunc);
            output.write(reinterpret_cast<const char*>(&file), sizeof(file));
            output.write(reinterpret_cast<const char*>(&info), sizeof(info));
            output.write(reinterpret_cast<const char*>(pixels.data()), pixelBytes);
            output.close();
            if (!output) throw std::runtime_error("cannot save capture BMP");
            std::printf("%s frame=%llu path=%s\n", rt ? "DXR_AO_CAPTURE visible_geometry_only=yes" : scene ? "SCENE_COLOR candidate_only=yes" : "CAPTURE",
                static_cast<unsigned long long>(lastFrame_), path.c_str());
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
        void VerifyPixels(UINT64 id, bool scene = false)
        {
            auto* readback = scene ? sceneReadback_.Get() : readback_.Get();
            const auto& footprint = scene ? sceneFootprint_ : footprint_;
            const auto bytes = scene ? sceneReadbackBytes_ : readbackBytes_;
            const bool rgba = frame_->format == DXGI_FORMAT_R8G8B8A8_UNORM;
            const unsigned char red = static_cast<unsigned char>(id & 255);
            const unsigned char blue = scene ? 128 : 64;
            const unsigned char expected[] = {rgba ? red : blue,
                static_cast<unsigned char>((id >> 8) & 255), rgba ? blue : red, 255};
            unsigned char* data = nullptr;
            D3D12_RANGE range{0, bytes};
            Require(readback->Map(0, &range, reinterpret_cast<void**>(&data)), "map verification pixels");
            bool valid = true;
            for (UINT y = 0; y < frame_->height && valid; ++y)
                for (UINT x = 0; x < frame_->width && valid; ++x)
                    for (UINT c = 0; c < 4; ++c)
                        if (data[static_cast<SIZE_T>(y) * footprint.Footprint.RowPitch + x * 4 + c] != expected[c])
                        {
                            std::fprintf(stderr, "PIXEL_MISMATCH scene=%u frame=%llu x=%u y=%u channel=%u expected=%u actual=%u\n",
                                scene ? 1u : 0u, static_cast<unsigned long long>(id), x, y, c, expected[c],
                                data[static_cast<SIZE_T>(y) * footprint.Footprint.RowPitch + x * 4 + c]);
                            valid = false; break;
                        }
            const D3D12_RANGE written{0, 0};
            readback->Unmap(0, &written);
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
            // DLSS-G deliberately suspends interpolation for an unfocused
            // window. Its explicitly requested demo uses normal window startup.
            const DWORD extendedStyle = fgMode_ && !development_ ? 0 : WS_EX_NOACTIVATE;
            RECT rect{0, 0, static_cast<LONG>(frame_->width), static_cast<LONG>(frame_->height)};
            AdjustWindowRectEx(&rect, style, FALSE, extendedStyle);
            MONITORINFO monitor{sizeof(MONITORINFO)};
            const auto primary = MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
            if (!GetMonitorInfoW(primary, &monitor)) throw std::runtime_error("preview monitor unavailable");
            // Keep this helper on an attached monitor and leave room for the
            // source game. Completely covering its window can suspend Ogre's
            // rendering while simulation continues, starving the transport.
            // The swapchain retains the full source extent; only its preview
            // window is scaled down for this two-window experiment.
            const LONG windowWidth = std::min(rect.right - rect.left, (monitor.rcWork.right - monitor.rcWork.left) / 2);
            const LONG windowHeight = std::min(rect.bottom - rect.top, (monitor.rcWork.bottom - monitor.rcWork.top) / 2);
            window_ = CreateWindowExW(extendedStyle, wc.lpszClassName,
                fgMode_ ? L"Battlezone experimental DLSS Frame Generation preview" : rtMode_ ? L"Battlezone hardware DXR AO preview (visible geometry)" : L"OpenShim DX12 frame transport preview (DLSS/RT pending)", style,
                monitor.rcWork.right - windowWidth - 16, monitor.rcWork.bottom - windowHeight - 16, windowWidth, windowHeight,
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
            ShowWindow(window_, fgMode_ && !development_ ? SW_SHOWNORMAL : SW_SHOWNOACTIVATE);
            // STARTUPINFO can override the first ShowWindow call in a child
            // launched from a harness. An explicit second show keeps only
            // this requested helper window visible without taking focus.
            if (!IsWindowVisible(window_) || IsIconic(window_)) ShowWindow(window_, SW_SHOWNOACTIVATE);
            RECT actual{}; GetWindowRect(window_, &actual);
            std::printf("PREVIEW visible=%u iconic=%u rect=%ld,%ld,%ld,%ld\n", IsWindowVisible(window_) ? 1u : 0u,
                IsIconic(window_) ? 1u : 0u, actual.left, actual.top, actual.right, actual.bottom);
            if (fgMode_ && !development_)
            {
                // One startup request for this explicit interactive demo.
                // Never refocus it while the user works in another window.
                const bool focused = SetForegroundWindow(window_) != FALSE;
                std::printf("DLSSG preview_foreground_request=%s (focus is required by NVIDIA)\n", focused ? "accepted" : "denied");
            }
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
        CameraSnapshot lastCamera_{};
        bool lastCameraValid_ = false;
        bool requireCamera_ = false;
        std::string motionPath_;
        CameraHistory history_;
        CapturedCameraPair lastPair_{};
        std::string scenePath_;
        bool verifyScene_ = false, lastSceneValid_ = false;
        std::uint32_t lastSceneStatus_ = 0, lastSceneOrdinal_ = 0, lastSceneSource_ = 0, lastSceneStage_ = 0, sceneStage_ = 0;
        ComPtr<ID3D12Resource> sceneColor_, sceneReadback_;
        D3D12_PLACED_SUBRESOURCE_FOOTPRINT sceneFootprint_{};
        SIZE_T sceneReadbackBytes_ = 0;
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
        bool fgMode_ = false;
        bool development_ = false;
        std::string fgReport_;
        ComPtr<ID3D12Device> queueDevice_;
        ComPtr<ID3D12Resource> fgScene_, fgDepth_;
        GpuCameraMotion gpuMotion_;
        StreamlineFrameGeneration frameGeneration_;
        bool rtMode_ = false, lastRtValid_ = false;
        unsigned rtFrames_ = 0;
        std::string rtPath_;
        ComPtr<ID3D12Resource> rtFinal_, rtReadback_;
        D3D12_PLACED_SUBRESOURCE_FOOTPRINT rtFootprint_{};
        SIZE_T rtReadbackBytes_ = 0;
        VisibleRayTracing rayTracing_;
        GpuBlit blit_;
        OwnWindowRecorder recorder_;
        std::ofstream rendererRecording_;
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
    bool requireCamera = false;
    std::string motionPath;
    std::string scenePath;
    bool verifyScene = false;
    UINT sceneStage = 0;
    std::wstring streamlineDirectory;
    std::string fgReport;
    bool visibleAO = false;
    std::string rtCapture;
    bool development = false;
    std::string recording;
    std::string rendererRecording;
    for (int i = 1; i < argc; ++i)
    {
        const std::string arg(argv[i]);
        if (arg == "--verify") verify = true;
        else if (arg == "--show") show = true;
        else if (arg == "--verify-depth") verifyDepth = true;
        else if (arg == "--require-camera") requireCamera = true;
        else if (arg == "--verify-scene") verifyScene = true;
        else if (arg == "--rt-visible-ao") visibleAO = true;
        else if (arg == "--streamline-development") development = true;
        else if (arg == "--record-window" && i + 1 < argc) { recording = argv[++i]; show = true; }
        else if (arg == "--record-frames" && i + 1 < argc) rendererRecording = argv[++i];
        else if (arg == "--capture-rt-bmp" && i + 1 < argc) rtCapture = argv[++i];
        else if (arg == "--streamline-dir" && i + 1 < argc)
        {
            const auto length = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, argv[i+1], -1, nullptr, 0);
            if (length <= 1) return 2;
            streamlineDirectory.resize(static_cast<size_t>(length));
            MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, argv[++i], -1, streamlineDirectory.data(), length);
            streamlineDirectory.pop_back(); show = true;
        }
        else if (arg == "--fg-report" && i + 1 < argc) fgReport = argv[++i];
        else if (arg == "--scene-stage" && i + 1 < argc)
        {
            const std::string value(argv[++i]);
            if (value == "before-overlay") sceneStage = 1;
            else if (value != "pre-clear") return 2;
        }
        else if (arg == "--capture-scene-bmp" && i + 1 < argc)
        {
            scenePath = argv[++i];
            if (scenePath.empty()) return 2;
        }
        else if (arg == "--capture-camera-motion-pfm" && i + 1 < argc)
        {
            motionPath = argv[++i];
            if (motionPath.empty()) return 2;
        }
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
            std::fprintf(stderr, "usage: frame_bridge_presenter --pid N [--frames N] [--timeout-ms N] [--show] [--verify] [--capture-bmp PATH] [--verify-depth] [--capture-depth-pfm PATH] [--depth-clear-ordinal 0..8] [--require-camera] [--capture-camera-motion-pfm PATH] [--capture-scene-bmp PATH] [--verify-scene] [--scene-stage pre-clear|before-overlay] [--streamline-dir SDK_BIN_PATH --fg-report PATH] [--streamline-development] [--rt-visible-ao --capture-rt-bmp PATH] [--record-window PATH] [--record-frames PATH]\n");
            return 2;
        }
    }
    if (!pid) return 2;
    if (requireCamera && depthPath.empty()) return 2;
    if (!motionPath.empty() && (depthPath.empty() || frames < 2)) return 2;
    if (!motionPath.empty()) requireCamera = true;
    if ((!scenePath.empty() || verifyScene) && !depthClearOrdinal) return 2;
    if (!scenePath.empty() && depthPath.empty()) return 2;
    if (!scenePath.empty()) requireCamera = true;
    if (!streamlineDirectory.empty() && (!depthClearOrdinal || fgReport.empty())) return 2;
    if (streamlineDirectory.empty() && !fgReport.empty()) return 2;
    if (visibleAO && !depthClearOrdinal) return 2;
    if (!visibleAO && !rtCapture.empty()) return 2;
    if (development && streamlineDirectory.empty()) return 2;
    try
    {
        Consumer consumer;
        consumer.Open(pid, show, verify, capturePath, verifyDepth, depthPath, depthClearOrdinal, requireCamera, motionPath, scenePath, verifyScene, sceneStage,
            streamlineDirectory, fgReport, visibleAO, rtCapture, development, recording, rendererRecording);
        return consumer.Run(frames, timeoutMs) >= frames ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::fprintf(stderr, "CONSUMER ERROR: %s\n", error.what());
        return 1;
    }
}
