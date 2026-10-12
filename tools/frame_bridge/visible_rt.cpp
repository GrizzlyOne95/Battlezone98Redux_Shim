#include "visible_rt.h"
#include "frame_bridge_history.h"
#include <stdexcept>
#include <algorithm>
#ifdef FRAME_BRIDGE_DXR
#include "visible_rt_mesh.h"
#include "visible_rt_rays.h"
#include <d3dcompiler.h>
#endif
namespace BZROpenShim::FrameBridge
{
#ifdef FRAME_BRIDGE_DXR
    namespace
    {
        using Microsoft::WRL::ComPtr;
        void Check(HRESULT hr,const char* where) { if(FAILED(hr)) throw std::runtime_error(where); }
        ComPtr<ID3D12Resource> Buffer(ID3D12Device* device,UINT64 bytes,D3D12_RESOURCE_STATES state,D3D12_HEAP_TYPE type=D3D12_HEAP_TYPE_DEFAULT)
        {
            D3D12_RESOURCE_DESC desc{}; desc.Dimension=D3D12_RESOURCE_DIMENSION_BUFFER; desc.Width=bytes; desc.Height=1;
            desc.DepthOrArraySize=desc.MipLevels=1; desc.SampleDesc.Count=1; desc.Layout=D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
            if(type==D3D12_HEAP_TYPE_DEFAULT) desc.Flags=D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
            D3D12_HEAP_PROPERTIES heap{}; heap.Type=type; ComPtr<ID3D12Resource> output;
            Check(device->CreateCommittedResource(&heap,D3D12_HEAP_FLAG_NONE,&desc,state,nullptr,IID_PPV_ARGS(&output)),"create DXR buffer"); return output;
        }
        void Transition(ID3D12GraphicsCommandList* list,ID3D12Resource* resource,D3D12_RESOURCE_STATES before,D3D12_RESOURCE_STATES after)
        {
            D3D12_RESOURCE_BARRIER b{}; b.Type=D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            b.Transition={resource,D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,before,after}; list->ResourceBarrier(1,&b);
        }
        void UAV(ID3D12GraphicsCommandList* list,ID3D12Resource* resource)
        { D3D12_RESOURCE_BARRIER b{}; b.Type=D3D12_RESOURCE_BARRIER_TYPE_UAV; b.UAV.pResource=resource; list->ResourceBarrier(1,&b); }
    }
    void VisibleRayTracing::Initialize(ID3D12Device* device,ID3D12Resource* depth,ID3D12Resource* scene,ID3D12Resource* final)
    {
        D3D12_FEATURE_DATA_D3D12_OPTIONS5 options{};
        Check(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5,&options,sizeof(options)),"query DXR tier");
        if(options.RaytracingTier<D3D12_RAYTRACING_TIER_1_1) throw std::runtime_error("visible AO requires hardware DXR 1.1");
        ComPtr<ID3D12Device5> dxr; Check(device->QueryInterface(IID_PPV_ARGS(&dxr)),"DXR device interface");
        depth_=depth; scene_=scene; final_=final; const auto desc=depth->GetDesc();
        width_=static_cast<unsigned>(desc.Width); height_=desc.Height; columns_=(width_-1)/2; rows_=(height_-1)/2; triangles_=columns_*rows_*2;
        if(width_<3||height_<3||width_>4096||height_>4096) throw std::runtime_error("visible DXR preview extent outside bounded range");
        vertices_=Buffer(device,static_cast<UINT64>(triangles_)*3*12,D3D12_RESOURCE_STATE_COMMON);
        geometry_.Type=D3D12_RAYTRACING_GEOMETRY_TYPE_TRIANGLES; geometry_.Flags=D3D12_RAYTRACING_GEOMETRY_FLAG_OPAQUE;
        geometry_.Triangles.VertexBuffer={vertices_->GetGPUVirtualAddress(),12}; geometry_.Triangles.VertexCount=triangles_*3;
        geometry_.Triangles.VertexFormat=DXGI_FORMAT_R32G32B32_FLOAT;
        D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS input{}; input.Type=D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL;
        input.Flags=D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_BUILD; input.NumDescs=1;
        input.DescsLayout=D3D12_ELEMENTS_LAYOUT_ARRAY; input.pGeometryDescs=&geometry_;
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO bottom{},top{}; dxr->GetRaytracingAccelerationStructurePrebuildInfo(&input,&bottom);
        input.Type=D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL; input.pGeometryDescs=nullptr;
        dxr->GetRaytracingAccelerationStructurePrebuildInfo(&input,&top);
        if(!bottom.ResultDataMaxSizeInBytes||!top.ResultDataMaxSizeInBytes) throw std::runtime_error("DXR acceleration structure requirements unavailable");
        blas_=Buffer(device,bottom.ResultDataMaxSizeInBytes,D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE);
        tlas_=Buffer(device,top.ResultDataMaxSizeInBytes,D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE);
        scratch_=Buffer(device,std::max(bottom.ScratchDataSizeInBytes,top.ScratchDataSizeInBytes),D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
        instances_=Buffer(device,sizeof(D3D12_RAYTRACING_INSTANCE_DESC),D3D12_RESOURCE_STATE_GENERIC_READ,D3D12_HEAP_TYPE_UPLOAD);
        D3D12_RAYTRACING_INSTANCE_DESC instance{}; instance.Transform[0][0]=instance.Transform[1][1]=instance.Transform[2][2]=1;
        instance.InstanceMask=255; instance.AccelerationStructure=blas_->GetGPUVirtualAddress();
        void* mapped=nullptr; D3D12_RANGE none{0,0}; Check(instances_->Map(0,&none,&mapped),"map DXR instance");
        std::memcpy(mapped,&instance,sizeof(instance)); instances_->Unmap(0,nullptr);
        D3D12_HEAP_PROPERTIES properties{}; properties.Type=D3D12_HEAP_TYPE_DEFAULT;
        auto outDesc=scene->GetDesc(); outDesc.Format=DXGI_FORMAT_R8G8B8A8_UNORM; outDesc.Flags=D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
        Check(device->CreateCommittedResource(&properties,D3D12_HEAP_FLAG_NONE,&outDesc,D3D12_RESOURCE_STATE_COMMON,nullptr,IID_PPV_ARGS(&sceneOutput_)),"create DXR scene output");
        Check(device->CreateCommittedResource(&properties,D3D12_HEAP_FLAG_NONE,&outDesc,D3D12_RESOURCE_STATE_COMMON,nullptr,IID_PPV_ARGS(&finalOutput_)),"create DXR final output");
        D3D12_DESCRIPTOR_HEAP_DESC hd{}; hd.Type=D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; hd.NumDescriptors=6; hd.Flags=D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        Check(device->CreateDescriptorHeap(&hd,IID_PPV_ARGS(&heap_)),"create DXR descriptors");
        auto cpu=heap_->GetCPUDescriptorHandleForHeapStart(); const auto step=device->GetDescriptorHandleIncrementSize(hd.Type);
        for(auto* resource : {depth,scene,final})
        {
            D3D12_SHADER_RESOURCE_VIEW_DESC srv{}; srv.Format=resource->GetDesc().Format; srv.ViewDimension=D3D12_SRV_DIMENSION_TEXTURE2D;
            srv.Shader4ComponentMapping=D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING; srv.Texture2D.MipLevels=1;
            device->CreateShaderResourceView(resource,&srv,cpu); cpu.ptr+=step;
        }
        D3D12_UNORDERED_ACCESS_VIEW_DESC uav{}; uav.ViewDimension=D3D12_UAV_DIMENSION_BUFFER;
        uav.Buffer.NumElements=triangles_*3; uav.Buffer.StructureByteStride=12; device->CreateUnorderedAccessView(vertices_.Get(),nullptr,&uav,cpu); cpu.ptr+=step;
        uav={}; uav.ViewDimension=D3D12_UAV_DIMENSION_TEXTURE2D; uav.Format=outDesc.Format;
        device->CreateUnorderedAccessView(sceneOutput_.Get(),nullptr,&uav,cpu); cpu.ptr+=step;
        device->CreateUnorderedAccessView(finalOutput_.Get(),nullptr,&uav,cpu);
        D3D12_DESCRIPTOR_RANGE ranges[2]={{D3D12_DESCRIPTOR_RANGE_TYPE_SRV,3,0,0,0},{D3D12_DESCRIPTOR_RANGE_TYPE_UAV,3,0,0,3}};
        D3D12_ROOT_PARAMETER parameters[3]{}; parameters[0].ParameterType=D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; parameters[0].DescriptorTable={2,ranges};
        parameters[1].ParameterType=D3D12_ROOT_PARAMETER_TYPE_SRV; parameters[1].Descriptor={3,0};
        parameters[2].ParameterType=D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS; parameters[2].Constants={0,0,24};
        D3D12_ROOT_SIGNATURE_DESC rd{}; rd.NumParameters=3; rd.pParameters=parameters;
        ComPtr<ID3DBlob> blob,errors; Check(D3D12SerializeRootSignature(&rd,D3D_ROOT_SIGNATURE_VERSION_1,&blob,&errors),"serialize DXR compute root");
        Check(device->CreateRootSignature(0,blob->GetBufferPointer(),blob->GetBufferSize(),IID_PPV_ARGS(&root_)),"create DXR compute root");
        D3D12_COMPUTE_PIPELINE_STATE_DESC ps{}; ps.pRootSignature=root_.Get(); ps.CS={visibleRtMesh,sizeof(visibleRtMesh)};
        Check(device->CreateComputePipelineState(&ps,IID_PPV_ARGS(&meshPipeline_)),"create DXR mesh pipeline"); ps.CS={visibleRtRays,sizeof(visibleRtRays)};
        Check(device->CreateComputePipelineState(&ps,IID_PPV_ARGS(&rayPipeline_)),"create inline DXR ray pipeline");
    }
    void VisibleRayTracing::Record(ID3D12GraphicsCommandList* list,const CameraSnapshot& camera)
    {
        MatrixD projection{},inverse{}; for(unsigned i=0;i<16;++i) projection[i]=camera.projection[i];
        const auto facts=InspectPerspective(camera);
        if(!facts.recognized||!Inverse(projection,inverse)) throw std::runtime_error("visible DXR camera convention unavailable");
        struct Constants { float inverse[16]; unsigned width,height,columns,rows; float clear,radius,bias,strength; } c{};
        for(unsigned i=0;i<16;++i) c.inverse[i]=static_cast<float>(inverse[i]);
        c.width=width_; c.height=height_; c.columns=columns_; c.rows=rows_;
        c.clear=facts.reversed?0.0f:1.0f; c.radius=4.0f; c.bias=.015f; c.strength=.8f;
        ComPtr<ID3D12GraphicsCommandList4> dxr; Check(list->QueryInterface(IID_PPV_ARGS(&dxr)),"DXR command interface");
        for(auto* resource : {depth_,scene_,final_}) Transition(list,resource,D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
        Transition(list,vertices_.Get(),D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
        ID3D12DescriptorHeap* heaps[]={heap_.Get()}; list->SetDescriptorHeaps(1,heaps); list->SetComputeRootSignature(root_.Get());
        list->SetComputeRootDescriptorTable(0,heap_->GetGPUDescriptorHandleForHeapStart()); list->SetComputeRootShaderResourceView(1,tlas_->GetGPUVirtualAddress());
        list->SetComputeRoot32BitConstants(2,24,&c,0); list->SetPipelineState(meshPipeline_.Get()); list->Dispatch((columns_+7)/8,(rows_+7)/8,1);
        Transition(list,vertices_.Get(),D3D12_RESOURCE_STATE_UNORDERED_ACCESS,D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
        D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC build{}; build.Inputs.Type=D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL;
        build.Inputs.Flags=D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_BUILD; build.Inputs.NumDescs=1;
        build.Inputs.DescsLayout=D3D12_ELEMENTS_LAYOUT_ARRAY; build.Inputs.pGeometryDescs=&geometry_;
        build.DestAccelerationStructureData=blas_->GetGPUVirtualAddress(); build.ScratchAccelerationStructureData=scratch_->GetGPUVirtualAddress();
        dxr->BuildRaytracingAccelerationStructure(&build,0,nullptr); UAV(list,blas_.Get()); UAV(list,scratch_.Get());
        build.Inputs.Type=D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL; build.Inputs.InstanceDescs=instances_->GetGPUVirtualAddress();
        build.DestAccelerationStructureData=tlas_->GetGPUVirtualAddress(); dxr->BuildRaytracingAccelerationStructure(&build,0,nullptr); UAV(list,tlas_.Get());
        for(auto* resource : {sceneOutput_.Get(),finalOutput_.Get()}) Transition(list,resource,D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
        list->SetPipelineState(rayPipeline_.Get()); list->Dispatch((width_+7)/8,(height_+7)/8,1);
        for(auto* resource : {sceneOutput_.Get(),finalOutput_.Get()}) Transition(list,resource,D3D12_RESOURCE_STATE_UNORDERED_ACCESS,D3D12_RESOURCE_STATE_COMMON);
        Transition(list,vertices_.Get(),D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,D3D12_RESOURCE_STATE_COMMON);
        for(auto* resource : {depth_,scene_,final_}) Transition(list,resource,D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,D3D12_RESOURCE_STATE_COMMON);
    }
#else
    void VisibleRayTracing::Initialize(ID3D12Device*,ID3D12Resource*,ID3D12Resource*,ID3D12Resource*)
    { throw std::runtime_error("configure FRAME_BRIDGE_DXR=ON with dxc to build the visible DXR AO preview"); }
    void VisibleRayTracing::Record(ID3D12GraphicsCommandList*,const CameraSnapshot&) {}
#endif
}
