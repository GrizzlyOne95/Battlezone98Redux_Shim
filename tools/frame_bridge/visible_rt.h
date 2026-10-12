#pragma once
#include "frame_bridge_camera.h"
#include <d3d12.h>
#include <wrl/client.h>

namespace BZROpenShim::FrameBridge
{
    // Hardware DXR prototype over a mesh reconstructed from visible depth.
    // No offscreen/hidden geometry, material normals, transparency or complete
    // engine geometry is available. This is not full-scene ray tracing.
    class VisibleRayTracing
    {
    public:
        void Initialize(ID3D12Device* device, ID3D12Resource* depth, ID3D12Resource* scene, ID3D12Resource* finalColor);
        void Record(ID3D12GraphicsCommandList* commands, const CameraSnapshot& camera);
        ID3D12Resource* SceneOutput() const { return sceneOutput_.Get(); }
        ID3D12Resource* FinalOutput() const { return finalOutput_.Get(); }
        unsigned TriangleCapacity() const { return triangles_; }
    private:
        Microsoft::WRL::ComPtr<ID3D12Resource> vertices_, blas_, tlas_, scratch_, instances_, sceneOutput_, finalOutput_;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap_;
        Microsoft::WRL::ComPtr<ID3D12RootSignature> root_;
        Microsoft::WRL::ComPtr<ID3D12PipelineState> meshPipeline_, rayPipeline_;
        D3D12_RAYTRACING_GEOMETRY_DESC geometry_{};
        unsigned width_=0,height_=0,columns_=0,rows_=0,triangles_=0;
        ID3D12Resource *depth_=nullptr,*scene_=nullptr,*final_=nullptr; // Helper-owned immutable lifetime.
    };
}
