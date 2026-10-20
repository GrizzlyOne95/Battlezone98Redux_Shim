#pragma once
#include <d3d12.h>
#include <wrl/client.h>
namespace BZROpenShim::FrameBridge
{
    class GpuBlit
    {
    public:
        void Initialize(ID3D12Device* device,ID3D12Resource* source,DXGI_FORMAT targetFormat);
        void Record(ID3D12GraphicsCommandList* commands,ID3D12Resource* target);
    private:
        Microsoft::WRL::ComPtr<ID3D12Device> device_;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srv_,rtv_;
        Microsoft::WRL::ComPtr<ID3D12RootSignature> root_;
        Microsoft::WRL::ComPtr<ID3D12PipelineState> pipeline_;
        ID3D12Resource* source_=nullptr;
    };
}
