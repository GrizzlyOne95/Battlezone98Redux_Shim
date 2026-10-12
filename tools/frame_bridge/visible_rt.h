#pragma once
#include "frame_bridge_camera.h"
#include "frame_bridge_native_geometry.h"
#include <d3d12.h>
#include <wrl/client.h>

namespace BZROpenShim::FrameBridge
{
    // Hardware DXR prototype over a mesh reconstructed from visible depth.
    // Optional leased native terrain supports AO and directional shadow previews.
    // Material normals, transparency and a complete live scene remain
    // unavailable. This is not full-scene ray tracing.
    class VisibleRayTracing
    {
    public:
        void Initialize(ID3D12Device* device, ID3D12Resource* depth, ID3D12Resource* scene, ID3D12Resource* finalColor);
        // Caller completes the prior submission before reusing upload data.
        void Record(ID3D12GraphicsCommandList* commands, const CameraSnapshot& camera);
        // Set/replace only after prior GPU work completes. Explicit world-space
        // snapshot; caller validates the captured mission/generation lease.
        void SetNativeGeometry(ID3D12Device* device, const NativeGeometry& snapshot);
        void ClearNativeGeometry(); // Prior submission must be complete.
        // 0: AO, 1: artistic shadow composite, 2: green lit / magenta blocked diagnostic.
        // Direction must be the current game's unit world-space vector toward sun.
        void SetTerrainSun(const float* direction, unsigned mode);
        unsigned TerrainShadowMode() const { return shadowMode_; }
        unsigned NativeTriangleCount() const { return nativeTriangles_; }
        ID3D12Resource* SceneOutput() const { return sceneOutput_.Get(); }
        ID3D12Resource* FinalOutput() const { return finalOutput_.Get(); }
        unsigned TriangleCapacity() const { return triangles_; }
    private:
        Microsoft::WRL::ComPtr<ID3D12Resource> vertices_, blas_, tlas_, scratch_, instances_, sceneOutput_, finalOutput_;
        Microsoft::WRL::ComPtr<ID3D12Resource> nativeVertices_,nativeBlas_,nativeScratch_;
        D3D12_RAYTRACING_GEOMETRY_DESC nativeGeometry_{};
        unsigned nativeTriangles_=0;
        bool nativeBuilt_=false;
        float towardSun_[3]{};
        unsigned shadowMode_=0;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap_;
        Microsoft::WRL::ComPtr<ID3D12RootSignature> root_;
        Microsoft::WRL::ComPtr<ID3D12PipelineState> meshPipeline_, rayPipeline_;
        D3D12_RAYTRACING_GEOMETRY_DESC geometry_{};
        unsigned width_=0,height_=0,columns_=0,rows_=0,triangles_=0;
        ID3D12Resource *depth_=nullptr,*scene_=nullptr,*final_=nullptr; // Helper-owned immutable lifetime.
    };
}
