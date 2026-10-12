#include "visual_enhancements.h"
#include "frame_bridge_history.h"
#include "visual_enhancements_shader.h"
#include <d3dcompiler.h>
#include <stdexcept>
#include <algorithm>
#include <cmath>

namespace BZROpenShim::FrameBridge
{
    namespace
    {
        using Microsoft::WRL::ComPtr;
        void Check(HRESULT hr, const char* message) { if (FAILED(hr)) throw std::runtime_error(message); }
        void Transition(ID3D12GraphicsCommandList* list, ID3D12Resource* resource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after)
        {
            D3D12_RESOURCE_BARRIER b{}; b.Type=D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            b.Transition={resource,D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,before,after}; list->ResourceBarrier(1,&b);
        }
        void Validate(const VisualSettings& s)
        {
            const auto bounded=[](float v,float low,float high) { return std::isfinite(v)&&v>=low&&v<=high; };
            if (!bounded(s.exposure,.1f,4)||!bounded(s.contrast,0,2)||!bounded(s.saturation,0,2)||
                !bounded(s.bloomThreshold,0,1)||!bounded(s.bloomStrength,0,2)||!bounded(s.hazeDensity,0,.1f)||
                !bounded(s.hazeStart,0,10000)||std::any_of(s.hazeColor.begin(),s.hazeColor.end(),[&](float v){return !bounded(v,0,1);}))
                throw std::runtime_error("visual preset parameters outside finite bounds");
        }
    }
    void VisualEnhancements::Initialize(ID3D12Device* device, ID3D12Resource* depth, ID3D12Resource* processedScene,
        ID3D12Resource* originalScene, ID3D12Resource* originalFinal)
    {
        inputs_={depth,processedScene,originalScene,originalFinal};
        if(!device||!depth||!processedScene||!originalScene||!originalFinal) throw std::runtime_error("visual preset inputs unavailable");
        auto desc=depth->GetDesc(); width_=static_cast<unsigned>(desc.Width); height_=desc.Height;
        if(desc.Format!=DXGI_FORMAT_R32_FLOAT||width_<1||height_<1||width_>4096||height_>4096)
            throw std::runtime_error("visual preset depth extent/format unavailable");
        for(auto* resource:inputs_)
        {
            const auto d=resource->GetDesc();
            if(d.Dimension!=D3D12_RESOURCE_DIMENSION_TEXTURE2D||d.Width!=width_||d.Height!=height_||
                d.SampleDesc.Count!=1||d.MipLevels!=1||d.DepthOrArraySize!=1)
                throw std::runtime_error("visual preset inputs must have matching single-sample extents");
            if(resource!=depth&&d.Format!=DXGI_FORMAT_R8G8B8A8_UNORM&&d.Format!=DXGI_FORMAT_B8G8R8A8_UNORM)
                throw std::runtime_error("visual preset requires SDR scene inputs");
        }
        bloomWidth_=(width_+1)/2; bloomHeight_=(height_+1)/2;
        D3D12_HEAP_PROPERTIES properties{}; properties.Type=D3D12_HEAP_TYPE_DEFAULT;
        desc.Flags=D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS; desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
        Check(device->CreateCommittedResource(&properties,D3D12_HEAP_FLAG_NONE,&desc,D3D12_RESOURCE_STATE_COMMON,nullptr,IID_PPV_ARGS(&sceneOutput_)),"create enhanced scene");
        Check(device->CreateCommittedResource(&properties,D3D12_HEAP_FLAG_NONE,&desc,D3D12_RESOURCE_STATE_COMMON,nullptr,IID_PPV_ARGS(&finalOutput_)),"create enhanced final");
        desc.Width=bloomWidth_; desc.Height=bloomHeight_; desc.Format=DXGI_FORMAT_R16G16B16A16_FLOAT;
        Check(device->CreateCommittedResource(&properties,D3D12_HEAP_FLAG_NONE,&desc,D3D12_RESOURCE_STATE_COMMON,nullptr,IID_PPV_ARGS(&bloomA_)),"create bloom A");
        Check(device->CreateCommittedResource(&properties,D3D12_HEAP_FLAG_NONE,&desc,D3D12_RESOURCE_STATE_COMMON,nullptr,IID_PPV_ARGS(&bloomB_)),"create bloom B");
        D3D12_DESCRIPTOR_HEAP_DESC hd{}; hd.Type=D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; hd.NumDescriptors=10; hd.Flags=D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        Check(device->CreateDescriptorHeap(&hd,IID_PPV_ARGS(&heap_)),"create visual descriptors");
        auto cpu=heap_->GetCPUDescriptorHandleForHeapStart(); const auto step=device->GetDescriptorHandleIncrementSize(hd.Type);
        for(auto* resource:{depth,processedScene,originalScene,originalFinal,bloomA_.Get(),bloomB_.Get()})
        {
            D3D12_SHADER_RESOURCE_VIEW_DESC srv{}; srv.Format=resource->GetDesc().Format; srv.ViewDimension=D3D12_SRV_DIMENSION_TEXTURE2D;
            srv.Shader4ComponentMapping=D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING; srv.Texture2D.MipLevels=1;
            device->CreateShaderResourceView(resource,&srv,cpu); cpu.ptr+=step;
        }
        for(auto* resource:{bloomA_.Get(),bloomB_.Get(),sceneOutput_.Get(),finalOutput_.Get()})
        {
            D3D12_UNORDERED_ACCESS_VIEW_DESC uav{}; uav.Format=resource->GetDesc().Format; uav.ViewDimension=D3D12_UAV_DIMENSION_TEXTURE2D;
            device->CreateUnorderedAccessView(resource,nullptr,&uav,cpu); cpu.ptr+=step;
        }
        D3D12_DESCRIPTOR_RANGE ranges[2]={{D3D12_DESCRIPTOR_RANGE_TYPE_SRV,6,0,0,0},{D3D12_DESCRIPTOR_RANGE_TYPE_UAV,4,0,0,6}};
        D3D12_ROOT_PARAMETER parameters[2]{}; parameters[0].ParameterType=D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; parameters[0].DescriptorTable={2,ranges};
        parameters[1].ParameterType=D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS; parameters[1].Constants={0,0,32};
        D3D12_ROOT_SIGNATURE_DESC rd{}; rd.NumParameters=2; rd.pParameters=parameters;
        ComPtr<ID3DBlob> blob,errors; Check(D3D12SerializeRootSignature(&rd,D3D_ROOT_SIGNATURE_VERSION_1,&blob,&errors),"serialize visual root");
        Check(device->CreateRootSignature(0,blob->GetBufferPointer(),blob->GetBufferSize(),IID_PPV_ARGS(&root_)),"create visual root");
        const char* entries[]={"Extract","BlurHorizontal","BlurVertical","Composite"};
        for(unsigned i=0;i<4;++i)
        {
            blob.Reset(); errors.Reset();
            const auto hr=D3DCompile(visualEnhancementsShader,sizeof(visualEnhancementsShader),"OpenShim visual enhancements",nullptr,nullptr,entries[i],"cs_5_1",
                D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_WARNINGS_ARE_ERRORS|D3DCOMPILE_OPTIMIZATION_LEVEL3,0,&blob,&errors);
            if(FAILED(hr)) throw std::runtime_error(errors?static_cast<const char*>(errors->GetBufferPointer()):"compile visual shader");
            D3D12_COMPUTE_PIPELINE_STATE_DESC ps{}; ps.pRootSignature=root_.Get(); ps.CS={blob->GetBufferPointer(),blob->GetBufferSize()};
            Check(device->CreateComputePipelineState(&ps,IID_PPV_ARGS(&pipelines_[i])),"create visual pipeline");
        }
    }
    void VisualEnhancements::Record(ID3D12GraphicsCommandList* list, const CameraSnapshot& camera, const VisualSettings& settings)
    {
        Validate(settings);
        MatrixD projection{},inverse{}; for(unsigned i=0;i<16;++i) projection[i]=camera.projection[i];
        const auto facts=InspectPerspective(camera);
        if(!facts.recognized||!Inverse(projection,inverse)||camera.width!=width_||camera.height!=height_)
            throw std::runtime_error("visual preset requires a matched perspective camera");
        struct Constants { float inverse[16]; unsigned width,height,bloomWidth,bloomHeight; float clear,exposure,contrast,saturation;
            float threshold,bloom,density,start; float color[3],padding; } c{};
        static_assert(sizeof(c)==32*4,"visual shader constants layout");
        for(unsigned i=0;i<16;++i) c.inverse[i]=static_cast<float>(inverse[i]);
        c.width=width_; c.height=height_; c.bloomWidth=bloomWidth_; c.bloomHeight=bloomHeight_; c.clear=facts.reversed?0.0f:1.0f;
        c.exposure=settings.exposure; c.contrast=settings.contrast; c.saturation=settings.saturation;
        c.threshold=settings.bloomThreshold; c.bloom=settings.bloomStrength; c.density=settings.hazeDensity; c.start=settings.hazeStart;
        std::copy(settings.hazeColor.begin(),settings.hazeColor.end(),c.color);
        const auto transitionInputs=[&](D3D12_RESOURCE_STATES before,D3D12_RESOURCE_STATES after) {
            for(unsigned i=0;i<inputs_.size();++i)
                if(std::find(inputs_.begin(),inputs_.begin()+i,inputs_[i])==inputs_.begin()+i) Transition(list,inputs_[i],before,after);
        };
        transitionInputs(D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
        ID3D12DescriptorHeap* heaps[]={heap_.Get()}; list->SetDescriptorHeaps(1,heaps); list->SetComputeRootSignature(root_.Get());
        list->SetComputeRootDescriptorTable(0,heap_->GetGPUDescriptorHandleForHeapStart()); list->SetComputeRoot32BitConstants(1,32,&c,0);
        const auto dispatch=[&](unsigned pass,unsigned width,unsigned height) { list->SetPipelineState(pipelines_[pass].Get()); list->Dispatch((width+7)/8,(height+7)/8,1); };
        Transition(list,bloomA_.Get(),D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_UNORDERED_ACCESS); dispatch(0,bloomWidth_,bloomHeight_);
        Transition(list,bloomA_.Get(),D3D12_RESOURCE_STATE_UNORDERED_ACCESS,D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
        Transition(list,bloomB_.Get(),D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_UNORDERED_ACCESS); dispatch(1,bloomWidth_,bloomHeight_);
        Transition(list,bloomB_.Get(),D3D12_RESOURCE_STATE_UNORDERED_ACCESS,D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
        Transition(list,bloomA_.Get(),D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,D3D12_RESOURCE_STATE_UNORDERED_ACCESS); dispatch(2,bloomWidth_,bloomHeight_);
        Transition(list,bloomA_.Get(),D3D12_RESOURCE_STATE_UNORDERED_ACCESS,D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
        for(auto* resource:{sceneOutput_.Get(),finalOutput_.Get()}) Transition(list,resource,D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
        dispatch(3,width_,height_);
        for(auto* resource:{sceneOutput_.Get(),finalOutput_.Get()}) Transition(list,resource,D3D12_RESOURCE_STATE_UNORDERED_ACCESS,D3D12_RESOURCE_STATE_COMMON);
        for(auto* resource:{bloomA_.Get(),bloomB_.Get()}) Transition(list,resource,D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,D3D12_RESOURCE_STATE_COMMON);
        transitionInputs(D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,D3D12_RESOURCE_STATE_COMMON);
    }
}
