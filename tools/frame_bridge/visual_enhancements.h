#pragma once
#include "frame_bridge_camera.h"
#include <d3d12.h>
#include <wrl/client.h>
#include <array>

namespace BZROpenShim::FrameBridge
{
    struct VisualSettings
    {
        float exposure = 1.12f, contrast = 1.10f, saturation = 1.08f;
        float bloomThreshold = .55f, bloomStrength = .35f;
        float hazeDensity = .00035f, hazeStart = 120.0f, hazeMaximum = .25f;
        std::array<float, 3> hazeColor{.24f, .30f, .38f}; // sRGB artistic preset.
    };

    // SDR postprocessing over owned, matched helper inputs. Scene bloom is
    // half-resolution/separable. The original scene/final difference mask is
    // conservative and remains unqualified as a general HUD alpha channel.
    class VisualEnhancements
    {
    public:
        void Initialize(ID3D12Device* device, ID3D12Resource* depth, ID3D12Resource* processedScene,
            ID3D12Resource* originalScene, ID3D12Resource* originalFinal);
        void Record(ID3D12GraphicsCommandList* commands, const CameraSnapshot& camera,
            const VisualSettings& settings = {});
        ID3D12Resource* SceneOutput() const { return sceneOutput_.Get(); }
        ID3D12Resource* FinalOutput() const { return finalOutput_.Get(); }
    private:
        std::array<ID3D12Resource*, 4> inputs_{}; // Helper-owned immutable lifetimes.
        Microsoft::WRL::ComPtr<ID3D12Resource> bloomA_, bloomB_, sceneOutput_, finalOutput_;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap_;
        Microsoft::WRL::ComPtr<ID3D12RootSignature> root_;
        std::array<Microsoft::WRL::ComPtr<ID3D12PipelineState>, 4> pipelines_;
        unsigned width_ = 0, height_ = 0, bloomWidth_ = 0, bloomHeight_ = 0;
    };
}
