#pragma once
#include "frame_bridge_history.h"
#include <d3d12.h>
#include <wrl/client.h>

namespace BZROpenShim::FrameBridge
{
    // Experimental camera motion only: objects, animation and particles are
    // absent. Output uses previous-minus-current pixels, including offscreen
    // correspondences. A separate rotation transform handles clear-depth sky.
    class GpuCameraMotion
    {
    public:
        void Initialize(ID3D12Device* device, ID3D12Resource* privateDepth);
        void Record(ID3D12GraphicsCommandList* commands, const CapturedCameraPair& pair);
        ID3D12Resource* Output() const { return output_.Get(); }
    private:
        Microsoft::WRL::ComPtr<ID3D12Resource> output_;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptors_;
        Microsoft::WRL::ComPtr<ID3D12RootSignature> root_;
        Microsoft::WRL::ComPtr<ID3D12PipelineState> pipeline_;
        unsigned width_ = 0, height_ = 0;
    };
}
