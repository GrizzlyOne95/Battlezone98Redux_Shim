#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <algorithm>
#include <cstdint>
#include <vector>

namespace BZROpenShim::TerrainHeight
{
    // Domain/hull SRV slots owned by the terrain tessellation shaders.
    constexpr UINT kHeightSlot = 127;
    constexpr UINT kLatticeSlot = 126; // TerrainTessellationSmoothing lattice, domain only

    // Caller serializes access. Only the immediate context and exact owned DS
    // objects can use these views. Never changes PS resources or foreign SRVs.
    // The owned hull reads the height slot (adaptive relief), so it binds and
    // restores in step with the domain. The lattice view (slot 126) is read
    // by the domain alone. Either view may be absent; an absent one's slot is
    // never touched.
    struct DomainBinding
    {
        template<class T> using Ptr = Microsoft::WRL::ComPtr<T>;
        Ptr<ID3D11ShaderResourceView> view, previous, previousHull;
        Ptr<ID3D11ShaderResourceView> lattice, previousLattice;
        Ptr<ID3D11DeviceContext> context;
        std::vector<Ptr<ID3D11DomainShader>> domains;
        uint64_t binds = 0, restores = 0;

        bool Any() const { return view || lattice; }
        bool Owns(ID3D11DomainShader* shader) const
        {
            return Any() && std::any_of(domains.begin(), domains.end(),
                [shader](const auto& candidate) { return candidate.Get() == shader; });
        }
        void RestoreDomainSlot(UINT slot, const Ptr<ID3D11ShaderResourceView>& owned,
            const Ptr<ID3D11ShaderResourceView>& saved)
        {
            if (!owned) return;
            Ptr<ID3D11ShaderResourceView> current;
            context->DSGetShaderResources(slot, 1, &current);
            if (current.Get() == owned.Get())
            {
                auto* raw = saved.Get(); context->DSSetShaderResources(slot, 1, &raw);
            }
        }
        void RestoreSlot()
        {
            if (!context) return;
            RestoreDomainSlot(kHeightSlot, view, previous);
            if (view)
            {
                Ptr<ID3D11ShaderResourceView> current;
                context->HSGetShaderResources(kHeightSlot, 1, &current);
                if (current.Get() == view.Get())
                {
                    auto* saved = previousHull.Get(); context->HSSetShaderResources(kHeightSlot, 1, &saved);
                }
            }
            RestoreDomainSlot(kLatticeSlot, lattice, previousLattice);
            previous.Reset(); previousHull.Reset(); previousLattice.Reset();
            context.Reset(); ++restores;
        }
        static void BindDomainSlot(ID3D11DeviceContext* next, UINT slot,
            const Ptr<ID3D11ShaderResourceView>& owned, Ptr<ID3D11ShaderResourceView>& saved)
        {
            if (!owned) return;
            next->DSGetShaderResources(slot, 1, &saved);
            auto* raw = owned.Get(); next->DSSetShaderResources(slot, 1, &raw);
        }
        void Select(ID3D11DeviceContext* next, ID3D11DomainShader* shader)
        {
            if (!next || next->GetType() != D3D11_DEVICE_CONTEXT_IMMEDIATE) return;
            const bool owned = Owns(shader);
            if (context && (!owned || context.Get() != next)) RestoreSlot();
            if (!owned || context) return;
            context = next;
            if (view)
            {
                BindDomainSlot(next, kHeightSlot, view, previous);
                next->HSGetShaderResources(kHeightSlot, 1, &previousHull);
                auto* height = view.Get(); next->HSSetShaderResources(kHeightSlot, 1, &height);
            }
            BindDomainSlot(next, kLatticeSlot, lattice, previousLattice);
            ++binds;
        }
        // The height view (slot 127) is bound to an owned domain on this
        // context. The lattice view does not count.
        bool Bound(ID3D11DeviceContext* candidate) const
        {
            if (!candidate || !view || context.Get() != candidate) return false;
            Ptr<ID3D11ShaderResourceView> current;
            Ptr<ID3D11DomainShader> shader;
            candidate->DSGetShaderResources(kHeightSlot, 1, &current);
            candidate->DSGetShader(&shader, nullptr, nullptr);
            return current.Get() == view.Get() && Owns(shader.Get());
        }
        void Reset()
        {
            RestoreSlot(); domains.clear(); view.Reset(); lattice.Reset(); binds = restores = 0;
        }
    };
}
