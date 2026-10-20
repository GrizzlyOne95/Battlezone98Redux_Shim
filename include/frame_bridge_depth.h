#pragma once

#include <d3d11.h>
#include <wrl/client.h>

namespace BZROpenShim::FrameBridge
{
    // Raw device depth, not linearized depth. The caller must qualify source
    // identity and the projection convention before choosing a reduction.
    enum class DepthReduction { Minimum, Maximum };

    class DepthExtractor
    {
    public:
        // Single-threaded immediate-context caller; Output must be unbound from
        // the pipeline during Extract. Only CS t0/u0/b0 and its shader are touched.
        HRESULT Start(ID3D11Device* device, const D3D11_TEXTURE2D_DESC& source);
        HRESULT Extract(ID3D11DeviceContext* context, ID3D11Texture2D* source, DepthReduction reduction);
        ID3D11Texture2D* Output() const { return output_.Get(); }
        void Stop();
    private:
        D3D11_TEXTURE2D_DESC sourceDesc_{};
        Microsoft::WRL::ComPtr<ID3D11Device> device_;
        Microsoft::WRL::ComPtr<ID3D11Texture2D> copy_, output_;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> view_;
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> target_;
        Microsoft::WRL::ComPtr<ID3D11ComputeShader> shader_;
        Microsoft::WRL::ComPtr<ID3D11Buffer> constants_;
    };
}
