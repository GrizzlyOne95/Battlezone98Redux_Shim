#include "gpu_blit.h"
#include <d3dcompiler.h>
#include <stdexcept>
namespace BZROpenShim::FrameBridge
{
    namespace
    {
        void Check(HRESULT hr,const char* message) { if(FAILED(hr)) throw std::runtime_error(message); }
        void Transition(ID3D12GraphicsCommandList* commands,ID3D12Resource* resource,D3D12_RESOURCE_STATES before,D3D12_RESOURCE_STATES after)
        {
            D3D12_RESOURCE_BARRIER b{}; b.Type=D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            b.Transition={resource,D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,before,after}; commands->ResourceBarrier(1,&b);
        }
        constexpr char shader[]=R"(
Texture2D<float4> Image:register(t0);
struct Vertex { float4 pos:SV_Position; float2 uv:TEXCOORD0; };
Vertex VS(uint id:SV_VertexID) { Vertex v; v.uv=float2((id<<1)&2,id&2); v.pos=float4(v.uv*float2(2,-2)+float2(-1,1),0,1); return v; }
float4 PS(Vertex v):SV_Target { uint w,h; Image.GetDimensions(w,h); return Image.Load(int3(min(uint2(v.uv*float2(w,h)),uint2(w-1,h-1)),0)); }
)";
    }
    void GpuBlit::Initialize(ID3D12Device* device,ID3D12Resource* source,DXGI_FORMAT format)
    {
        device_=device; source_=source;
        D3D12_DESCRIPTOR_HEAP_DESC h{}; h.Type=D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; h.NumDescriptors=1; h.Flags=D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        Check(device->CreateDescriptorHeap(&h,IID_PPV_ARGS(&srv_)),"create blit SRV heap");
        D3D12_SHADER_RESOURCE_VIEW_DESC view{}; view.Format=source->GetDesc().Format; view.ViewDimension=D3D12_SRV_DIMENSION_TEXTURE2D;
        view.Shader4ComponentMapping=D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING; view.Texture2D.MipLevels=1;
        device->CreateShaderResourceView(source,&view,srv_->GetCPUDescriptorHandleForHeapStart());
        h.Type=D3D12_DESCRIPTOR_HEAP_TYPE_RTV; h.Flags=D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        Check(device->CreateDescriptorHeap(&h,IID_PPV_ARGS(&rtv_)),"create blit RTV heap");
        D3D12_DESCRIPTOR_RANGE range{D3D12_DESCRIPTOR_RANGE_TYPE_SRV,1,0,0,0};
        D3D12_ROOT_PARAMETER param{}; param.ParameterType=D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        param.DescriptorTable={1,&range}; param.ShaderVisibility=D3D12_SHADER_VISIBILITY_PIXEL;
        D3D12_ROOT_SIGNATURE_DESC desc{}; desc.NumParameters=1; desc.pParameters=&param;
        Microsoft::WRL::ComPtr<ID3DBlob> root,errors,vs,ps;
        Check(D3D12SerializeRootSignature(&desc,D3D_ROOT_SIGNATURE_VERSION_1,&root,&errors),"serialize blit root");
        Check(device->CreateRootSignature(0,root->GetBufferPointer(),root->GetBufferSize(),IID_PPV_ARGS(&root_)),"create blit root");
        Check(D3DCompile(shader,sizeof(shader)-1,"OpenShim blit",nullptr,nullptr,"VS","vs_5_1",D3DCOMPILE_OPTIMIZATION_LEVEL3,0,&vs,&errors),"compile blit VS");
        Check(D3DCompile(shader,sizeof(shader)-1,"OpenShim blit",nullptr,nullptr,"PS","ps_5_1",D3DCOMPILE_OPTIMIZATION_LEVEL3,0,&ps,&errors),"compile blit PS");
        D3D12_GRAPHICS_PIPELINE_STATE_DESC p{}; p.pRootSignature=root_.Get(); p.VS={vs->GetBufferPointer(),vs->GetBufferSize()}; p.PS={ps->GetBufferPointer(),ps->GetBufferSize()};
        p.BlendState.RenderTarget[0].RenderTargetWriteMask=D3D12_COLOR_WRITE_ENABLE_ALL;
        p.RasterizerState.FillMode=D3D12_FILL_MODE_SOLID; p.RasterizerState.CullMode=D3D12_CULL_MODE_NONE;
        p.RasterizerState.DepthClipEnable=TRUE; p.SampleMask=UINT_MAX; p.PrimitiveTopologyType=D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        p.NumRenderTargets=1; p.RTVFormats[0]=format; p.SampleDesc.Count=1;
        p.DepthStencilState.DepthFunc=D3D12_COMPARISON_FUNC_ALWAYS;
        p.DepthStencilState.FrontFace={D3D12_STENCIL_OP_KEEP,D3D12_STENCIL_OP_KEEP,D3D12_STENCIL_OP_KEEP,D3D12_COMPARISON_FUNC_ALWAYS};
        p.DepthStencilState.BackFace=p.DepthStencilState.FrontFace;
        Check(device->CreateGraphicsPipelineState(&p,IID_PPV_ARGS(&pipeline_)),"create blit pipeline");
    }
    void GpuBlit::Record(ID3D12GraphicsCommandList* commands,ID3D12Resource* target)
    {
        device_->CreateRenderTargetView(target,nullptr,rtv_->GetCPUDescriptorHandleForHeapStart());
        Transition(commands,source_,D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
        Transition(commands,target,D3D12_RESOURCE_STATE_PRESENT,D3D12_RESOURCE_STATE_RENDER_TARGET);
        ID3D12DescriptorHeap* heaps[]={srv_.Get()}; commands->SetDescriptorHeaps(1,heaps); commands->SetGraphicsRootSignature(root_.Get());
        commands->SetGraphicsRootDescriptorTable(0,srv_->GetGPUDescriptorHandleForHeapStart()); commands->SetPipelineState(pipeline_.Get());
        const auto desc=target->GetDesc(); const D3D12_VIEWPORT viewport{0,0,static_cast<float>(desc.Width),static_cast<float>(desc.Height),0,1};
        const D3D12_RECT scissor{0,0,static_cast<LONG>(desc.Width),static_cast<LONG>(desc.Height)};
        commands->RSSetViewports(1,&viewport); commands->RSSetScissorRects(1,&scissor);
        const auto handle=rtv_->GetCPUDescriptorHandleForHeapStart(); commands->OMSetRenderTargets(1,&handle,FALSE,nullptr);
        commands->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); commands->DrawInstanced(3,1,0,0);
        Transition(commands,target,D3D12_RESOURCE_STATE_RENDER_TARGET,D3D12_RESOURCE_STATE_PRESENT);
        Transition(commands,source_,D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,D3D12_RESOURCE_STATE_COMMON);
    }
}
