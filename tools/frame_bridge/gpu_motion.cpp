#include "gpu_motion.h"
#include <d3dcompiler.h>
#include <stdexcept>
#include <cstring>

namespace BZROpenShim::FrameBridge
{
    namespace
    {
        void Check(HRESULT hr, const char* where) { if (FAILED(hr)) throw std::runtime_error(where); }
        constexpr char shader[] = R"(
Texture2D<float> Depth : register(t0);
RWTexture2D<float2> Motion : register(u0);
cbuffer Params : register(b0) {
    row_major float4x4 ToPrevious;
    row_major float4x4 SkyToPrevious;
    uint Width; uint Height; uint Reset; float ClearDepth;
};
[numthreads(8,8,1)]
void main(uint3 id : SV_DispatchThreadID) {
    if (id.x >= Width || id.y >= Height) return;
    float z = Depth.Load(int3(id.xy,0));
    float2 current = float2(id.xy) + 0.5;
    float4 clip = float4(2*current.x/Width-1, 1-2*current.y/Height, z, 1);
    float4 old = z == ClearDepth ? mul(SkyToPrevious,clip) : mul(ToPrevious,clip);
    float2 mv = 0;
    if (!Reset && isfinite(z) && z >= 0 && z <= 1 && all(isfinite(old)) && old.w > 1e-8) {
        float2 previous = float2((old.x/old.w+1)*0.5*Width, (1-old.y/old.w)*0.5*Height);
        mv = previous - current;
    }
    Motion[id.xy] = mv;
})";
        MatrixD RotationViewProjection(const CameraSnapshot& camera)
        {
            CameraSnapshot rotation = camera;
            rotation.view[3]=rotation.view[7]=rotation.view[11]=0;
            return ViewProjection(rotation);
        }
    }
    void GpuCameraMotion::Initialize(ID3D12Device* device, ID3D12Resource* depth)
    {
        const auto desc = depth->GetDesc(); width_=static_cast<unsigned>(desc.Width); height_=desc.Height;
        D3D12_HEAP_PROPERTIES heap{}; heap.Type=D3D12_HEAP_TYPE_DEFAULT;
        auto outputDesc=desc; outputDesc.Format=DXGI_FORMAT_R32G32_FLOAT;
        outputDesc.Flags=D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
        Check(device->CreateCommittedResource(&heap,D3D12_HEAP_FLAG_NONE,&outputDesc,D3D12_RESOURCE_STATE_COMMON,
            nullptr,IID_PPV_ARGS(&output_)),"create camera motion output");
        D3D12_DESCRIPTOR_HEAP_DESC dh{}; dh.Type=D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        dh.NumDescriptors=2; dh.Flags=D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        Check(device->CreateDescriptorHeap(&dh,IID_PPV_ARGS(&descriptors_)),"create motion descriptors");
        auto handle=descriptors_->GetCPUDescriptorHandleForHeapStart();
        D3D12_SHADER_RESOURCE_VIEW_DESC srv{}; srv.Format=DXGI_FORMAT_R32_FLOAT;
        srv.ViewDimension=D3D12_SRV_DIMENSION_TEXTURE2D; srv.Shader4ComponentMapping=D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srv.Texture2D.MipLevels=1; device->CreateShaderResourceView(depth,&srv,handle);
        handle.ptr += device->GetDescriptorHandleIncrementSize(dh.Type);
        D3D12_UNORDERED_ACCESS_VIEW_DESC uav{}; uav.Format=outputDesc.Format; uav.ViewDimension=D3D12_UAV_DIMENSION_TEXTURE2D;
        device->CreateUnorderedAccessView(output_.Get(),nullptr,&uav,handle);
        D3D12_DESCRIPTOR_RANGE ranges[2]{};
        ranges[0]={D3D12_DESCRIPTOR_RANGE_TYPE_SRV,1,0,0,0};
        ranges[1]={D3D12_DESCRIPTOR_RANGE_TYPE_UAV,1,0,0,1};
        D3D12_ROOT_PARAMETER parameters[2]{};
        parameters[0].ParameterType=D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        parameters[0].DescriptorTable={2,ranges};
        parameters[1].ParameterType=D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
        parameters[1].Constants={0,0,36};
        D3D12_ROOT_SIGNATURE_DESC rootDesc{}; rootDesc.NumParameters=2; rootDesc.pParameters=parameters;
        Microsoft::WRL::ComPtr<ID3DBlob> blob, errors;
        Check(D3D12SerializeRootSignature(&rootDesc,D3D_ROOT_SIGNATURE_VERSION_1,&blob,&errors),"serialize motion root");
        Check(device->CreateRootSignature(0,blob->GetBufferPointer(),blob->GetBufferSize(),IID_PPV_ARGS(&root_)),"create motion root");
        blob.Reset(); errors.Reset();
        const auto hr=D3DCompile(shader,sizeof(shader)-1,"OpenShim camera motion",nullptr,nullptr,"main","cs_5_1",
            D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_OPTIMIZATION_LEVEL3,0,&blob,&errors);
        if (FAILED(hr)) throw std::runtime_error(errors ? static_cast<const char*>(errors->GetBufferPointer()) : "compile motion shader");
        D3D12_COMPUTE_PIPELINE_STATE_DESC ps{}; ps.pRootSignature=root_.Get(); ps.CS={blob->GetBufferPointer(),blob->GetBufferSize()};
        Check(device->CreateComputePipelineState(&ps,IID_PPV_ARGS(&pipeline_)),"create motion pipeline");
    }
    void GpuCameraMotion::Record(ID3D12GraphicsCommandList* commands, const CapturedCameraPair& pair)
    {
        struct Constants { float previous[16], sky[16]; unsigned width,height,reset; float clear; } c{};
        c.width=width_; c.height=height_; c.reset=1;
        const auto facts=InspectPerspective(pair.current); c.clear=facts.reversed ? 0.0f : 1.0f;
        MatrixD inverse{}, inverseSky{};
        if (pair.comparable && facts.recognized && Inverse(ViewProjection(pair.current),inverse) &&
            Inverse(RotationViewProjection(pair.current),inverseSky))
        {
            const auto transform=Multiply(ViewProjection(pair.previous),inverse);
            const auto sky=Multiply(RotationViewProjection(pair.previous),inverseSky);
            for(unsigned i=0;i<16;++i) { c.previous[i]=static_cast<float>(transform[i]); c.sky[i]=static_cast<float>(sky[i]); }
            c.reset=0;
        }
        D3D12_RESOURCE_BARRIER barrier{}; barrier.Type=D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        barrier.Transition={output_.Get(),D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_UNORDERED_ACCESS};
        commands->ResourceBarrier(1,&barrier);
        ID3D12DescriptorHeap* heaps[]={descriptors_.Get()}; commands->SetDescriptorHeaps(1,heaps);
        commands->SetComputeRootSignature(root_.Get()); commands->SetPipelineState(pipeline_.Get());
        commands->SetComputeRootDescriptorTable(0,descriptors_->GetGPUDescriptorHandleForHeapStart());
        commands->SetComputeRoot32BitConstants(1,36,&c,0);
        commands->Dispatch((width_+7)/8,(height_+7)/8,1);
        std::swap(barrier.Transition.StateBefore,barrier.Transition.StateAfter); commands->ResourceBarrier(1,&barrier);
    }
}
