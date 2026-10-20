#pragma once
#include "frame_bridge_history.h"
#include <d3d12.h>
#include <memory>
#include <string>

namespace BZROpenShim::FrameBridge
{
    // A development preview in a separate process. Reflex markers describe
    // this helper's work; they do not measure or pace the game simulation.
    class StreamlineFrameGeneration
    {
    public:
        StreamlineFrameGeneration();
        ~StreamlineFrameGeneration();
        void Initialize(const std::wstring& sdkDirectory, const std::wstring& logDirectory, bool development);
        void Upgrade(void** object);
        void SetDevice(ID3D12Device* device, LUID adapter, unsigned width, unsigned height, DXGI_FORMAT colorFormat, DXGI_FORMAT hudlessFormat);
        void Begin(const CapturedCameraPair& pair, unsigned frameIndex, bool inputsValid);
        void Tag(ID3D12GraphicsCommandList* commands, ID3D12Resource* depth, ID3D12Resource* motion, ID3D12Resource* scene);
        void Submitted();
        void BeforePresent();
        void AfterPresent();
        void SaveReport(const std::string& path) const;
        void Shutdown();
        bool Enabled() const;
        unsigned AdditionalPresents() const;
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
