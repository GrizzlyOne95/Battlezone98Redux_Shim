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
    // The owned hull reads the same slot (adaptive relief), so it binds and
    // restores in step with the domain. controlView, when set, rides slot 126
    // (a split paint control array) under the same rules.
    struct DomainBinding
    {
        template<class T> using Ptr = Microsoft::WRL::ComPtr<T>;
        static constexpr UINT kSlot = 127, kControlSlot = 126;
        Ptr<ID3D11ShaderResourceView> view, previous, previousHull;
        Ptr<ID3D11ShaderResourceView> controlView, previousControl, previousControlHull;
        Ptr<ID3D11DeviceContext> context;
        std::vector<Ptr<ID3D11DomainShader>> domains;
        uint64_t binds = 0, restores = 0;

        bool Owns(ID3D11DomainShader* shader) const
        {
            return view && std::any_of(domains.begin(), domains.end(),
                [shader](const auto& candidate) { return candidate.Get() == shader; });
        }
        // Puts back what was there only if the slot still holds ours.
        static void RestoreOne(ID3D11DeviceContext* context, UINT slot, ID3D11ShaderResourceView* ours,
            Ptr<ID3D11ShaderResourceView>& savedDomain, Ptr<ID3D11ShaderResourceView>& savedHull)
        {
            Ptr<ID3D11ShaderResourceView> current;
            context->DSGetShaderResources(slot, 1, &current);
            if (current.Get() == ours)
            {
                auto* saved = savedDomain.Get(); context->DSSetShaderResources(slot, 1, &saved);
            }
            current.Reset();
            context->HSGetShaderResources(slot, 1, &current);
            if (current.Get() == ours)
            {
                auto* saved = savedHull.Get(); context->HSSetShaderResources(slot, 1, &saved);
            }
            savedDomain.Reset(); savedHull.Reset();
        }
        void RestoreSlot()
        {
            if (!context) return;
            RestoreOne(context.Get(), kSlot, view.Get(), previous, previousHull);
            if (controlView) RestoreOne(context.Get(), kControlSlot, controlView.Get(), previousControl, previousControlHull);
            context.Reset(); ++restores;
        }
        void Select(ID3D11DeviceContext* next, ID3D11DomainShader* shader)
        {
            if (!next || next->GetType() != D3D11_DEVICE_CONTEXT_IMMEDIATE) return;
            const bool owned = Owns(shader);
            if (context && (!owned || context.Get() != next)) RestoreSlot();
            if (!owned || context) return;
            next->DSGetShaderResources(kSlot, 1, &previous);
            next->HSGetShaderResources(kSlot, 1, &previousHull);
            context = next;
            auto* height = view.Get(); next->DSSetShaderResources(kSlot, 1, &height);
            next->HSSetShaderResources(kSlot, 1, &height);
            if (controlView)
            {
                next->DSGetShaderResources(kControlSlot, 1, &previousControl);
                next->HSGetShaderResources(kControlSlot, 1, &previousControlHull);
                auto* control = controlView.Get(); next->DSSetShaderResources(kControlSlot, 1, &control);
                next->HSSetShaderResources(kControlSlot, 1, &control);
            }
            ++binds;
        }
        bool Bound(ID3D11DeviceContext* candidate) const
        {
            if (!candidate || !view || context.Get() != candidate) return false;
            Ptr<ID3D11ShaderResourceView> current, control;
            Ptr<ID3D11DomainShader> shader;
            candidate->DSGetShaderResources(kSlot, 1, &current);
            if (controlView) candidate->DSGetShaderResources(kControlSlot, 1, &control);
            candidate->DSGetShader(&shader, nullptr, nullptr);
            return current.Get() == view.Get() && control.Get() == controlView.Get() && Owns(shader.Get());
        }
        void Reset()
        {
            RestoreSlot(); domains.clear(); view.Reset(); controlView.Reset(); binds = restores = 0;
        }
    };
}
