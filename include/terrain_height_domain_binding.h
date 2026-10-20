#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <algorithm>
#include <cstdint>
#include <vector>

namespace BZROpenShim::TerrainHeight
{
    // Caller serializes access. Only the immediate context and exact owned DS
    // objects can use this view. Never changes PS resources or foreign SRVs.
    struct DomainBinding
    {
        template<class T> using Ptr = Microsoft::WRL::ComPtr<T>;
        Ptr<ID3D11ShaderResourceView> view, previous;
        Ptr<ID3D11DeviceContext> context;
        std::vector<Ptr<ID3D11DomainShader>> domains;
        uint64_t binds = 0, restores = 0;

        bool Owns(ID3D11DomainShader* shader) const
        {
            return view && std::any_of(domains.begin(), domains.end(),
                [shader](const auto& candidate) { return candidate.Get() == shader; });
        }
        void RestoreSlot()
        {
            if (!context) return;
            Ptr<ID3D11ShaderResourceView> current;
            context->DSGetShaderResources(127, 1, &current);
            if (current.Get() == view.Get())
            {
                auto* saved = previous.Get(); context->DSSetShaderResources(127, 1, &saved);
            }
            previous.Reset(); context.Reset(); ++restores;
        }
        void Select(ID3D11DeviceContext* next, ID3D11DomainShader* shader)
        {
            if (!next || next->GetType() != D3D11_DEVICE_CONTEXT_IMMEDIATE) return;
            const bool owned = Owns(shader);
            if (context && (!owned || context.Get() != next)) RestoreSlot();
            if (!owned || context) return;
            next->DSGetShaderResources(127, 1, &previous);
            context = next;
            auto* height = view.Get(); next->DSSetShaderResources(127, 1, &height);
            ++binds;
        }
        bool Bound(ID3D11DeviceContext* candidate) const
        {
            if (!candidate || !view || context.Get() != candidate) return false;
            Ptr<ID3D11ShaderResourceView> current;
            Ptr<ID3D11DomainShader> shader;
            candidate->DSGetShaderResources(127, 1, &current);
            candidate->DSGetShader(&shader, nullptr, nullptr);
            return current.Get() == view.Get() && Owns(shader.Get());
        }
        void Reset()
        {
            RestoreSlot(); domains.clear(); view.Reset(); binds = restores = 0;
        }
    };
}
