#pragma once
#include "frame_bridge_camera.h"
#include "frame_bridge_native_geometry.h"
#include <d3d12.h>
#include <wrl/client.h>

namespace BZROpenShim::FrameBridge
{
    // Hardware DXR prototype over a mesh reconstructed from visible depth.
    // Optional owned static native triangles are available in diagnostic
    // replay. Material normals, transparency and a complete live scene remain
    // unavailable. This is not full-scene ray tracing.
    class VisibleRayTracing
    {
    public:
        void Initialize(ID3D12Device* device, ID3D12Resource* depth, ID3D12Resource* scene, ID3D12Resource* finalColor);
        // Caller completes the prior submission before reusing upload data.
        void Record(ID3D12GraphicsCommandList* commands, const CameraSnapshot& camera);
        // Set before recording any work. Explicit static world-space snapshot;
        // caller validates that it matches the captured mission/base geometry.
        void SetNativeGeometry(ID3D12Device* device, const NativeGeometry& snapshot);
        unsigned NativeTriangleCount() const { return nativeTriangles_; }
        ID3D12Resource* SceneOutput() const { return sceneOutput_.Get(); }
        ID3D12Resource* FinalOutput() const { return finalOutput_.Get(); }
        unsigned TriangleCapacity() const { return triangles_; }
    private:
        Microsoft::WRL::ComPtr<ID3D12Resource> vertices_, blas_, tlas_, scratch_, instances_, sceneOutput_, finalOutput_;
        Microsoft::WRL::ComPtr<ID3D12Resource> nativeVertices_,nativeBlas_,nativeScratch_;
        D3D12_RAYTRACING_GEOMETRY_DESC nativeGeometry_{};
        unsigned nativeTriangles_=0;
        bool recorded_=false;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap_;
        Microsoft::WRL::ComPtr<ID3D12RootSignature> root_;
        Microsoft::WRL::ComPtr<ID3D12PipelineState> meshPipeline_, rayPipeline_;
        D3D12_RAYTRACING_GEOMETRY_DESC geometry_{};
        unsigned width_=0,height_=0,columns_=0,rows_=0,triangles_=0;
        ID3D12Resource *depth_=nullptr,*scene_=nullptr,*final_=nullptr; // Helper-owned immutable lifetime.
    };
}
