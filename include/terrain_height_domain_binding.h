#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <vector>

namespace BZROpenShim::TerrainHeight
{
    // Caller serializes access. Only the immediate context and exact owned DS
    // objects can use this view. Never changes PS resources or foreign SRVs.
    // The owned hull reads the same slot (adaptive relief), so it binds and
    // restores in step with the domain. controlView, when set, rides slot 126
    // (a split paint control array) under the same rules, and bakedView slot
    // 125 (the relief bake).
    struct DomainBinding
    {
        template<class T> using Ptr = Microsoft::WRL::ComPtr<T>;
        static constexpr UINT kSlot = 127, kControlSlot = 126, kBakedSlot = 125;
        Ptr<ID3D11ShaderResourceView> view, previous, previousHull;
        Ptr<ID3D11ShaderResourceView> controlView, previousControl, previousControlHull;
        Ptr<ID3D11ShaderResourceView> bakedView, previousBaked, previousBakedHull;
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
            if (bakedView) RestoreOne(context.Get(), kBakedSlot, bakedView.Get(), previousBaked, previousBakedHull);
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
            if (bakedView)
            {
                next->DSGetShaderResources(kBakedSlot, 1, &previousBaked);
                next->HSGetShaderResources(kBakedSlot, 1, &previousBakedHull);
                auto* baked = bakedView.Get(); next->DSSetShaderResources(kBakedSlot, 1, &baked);
                next->HSSetShaderResources(kBakedSlot, 1, &baked);
            }
            ++binds;
        }
        bool Bound(ID3D11DeviceContext* candidate) const
        {
            if (!candidate || !view || context.Get() != candidate) return false;
            Ptr<ID3D11ShaderResourceView> current, control, baked;
            Ptr<ID3D11DomainShader> shader;
            candidate->DSGetShaderResources(kSlot, 1, &current);
            if (controlView) candidate->DSGetShaderResources(kControlSlot, 1, &control);
            if (bakedView) candidate->DSGetShaderResources(kBakedSlot, 1, &baked);
            candidate->DSGetShader(&shader, nullptr, nullptr);
            return current.Get() == view.Get() && control.Get() == controlView.Get() &&
                baked.Get() == bakedView.Get() && Owns(shader.Get());
        }
        void Reset()
        {
            RestoreSlot(); domains.clear(); view.Reset(); controlView.Reset(); bakedView.Reset(); binds = restores = 0;
        }
    };

    // The relief bake's compute state. Under the caller's height mutex.
    struct ReliefBake
    {
        Microsoft::WRL::ComPtr<ID3D11ComputeShader> shader;
        Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> target;
        UINT width = 0, height = 0;
        uint64_t dispatches = 0;
    };

    // Texel i sits at bounds.xy + i * step; the last reaches the far edge (the
    // epsilon keeps an exact multiple from adding a texel). Past 4096 texels a
    // side the step coarsens to cover the span in 4096 (capped = true).
    struct ReliefBakeSize { UINT width, height; double step; bool capped; };
    inline ReliefBakeSize SizeReliefBake(float spanX, float spanZ, float spacing)
    {
        const auto texels = [](float span, double step) {
            return (std::max)(2.0, std::ceil(double(span) / step - 1e-3) + 1.0); };
        double step = spacing;
        if ((std::max)(texels(spanX, step), texels(spanZ, step)) > 4096.0)
            step = double((std::max)(spanX, spanZ)) / 4095.0;
        return {UINT(texels(spanX, step)), UINT(texels(spanZ, step)), step, step != double(spacing)};
    }

    // Caller holds the height mutex. Runs before Select binds t125 and drops
    // our binding first, so the bake's UAV is never bound beside its SRV. Saves
    // and restores only the compute slots it touches. Returns whether it ran;
    // a non-immediate context leaves the dirty flag set.
    inline bool DispatchReliefBake(ReliefBake& bake, DomainBinding& binding, std::atomic<bool>& dirty,
        ID3D11DeviceContext* context, ID3D11DomainShader* shader)
    {
        if (!bake.shader || !context || context->GetType() != D3D11_DEVICE_CONTEXT_IMMEDIATE ||
            !binding.Owns(shader) || !dirty.exchange(false)) return false;
        binding.RestoreSlot();
        constexpr UINT kControl = DomainBinding::kControlSlot; // t126, then t127 paint
        Microsoft::WRL::ComPtr<ID3D11ComputeShader> savedShader;
        ID3D11ClassInstance* instances[D3D11_SHADER_MAX_INTERFACES]{};
        UINT instanceCount = D3D11_SHADER_MAX_INTERFACES;
        ID3D11ShaderResourceView* savedViews[2]{};
        ID3D11UnorderedAccessView* savedTarget = nullptr;
        context->CSGetShader(&savedShader, instances, &instanceCount);
        context->CSGetShaderResources(kControl, 2, savedViews);
        context->CSGetUnorderedAccessViews(0, 1, &savedTarget);
        ID3D11ShaderResourceView* views[2] = {binding.controlView.Get(), binding.view.Get()};
        ID3D11UnorderedAccessView* target = bake.target.Get();
        context->CSSetShader(bake.shader.Get(), nullptr, 0);
        context->CSSetShaderResources(kControl, 2, views);
        context->CSSetUnorderedAccessViews(0, 1, &target, nullptr);
        context->Dispatch((bake.width + 7) / 8, (bake.height + 7) / 8, 1);
        target = nullptr;
        context->CSSetUnorderedAccessViews(0, 1, &target, nullptr);
        context->CSSetShaderResources(kControl, 2, savedViews);
        const UINT keepCounts = static_cast<UINT>(-1); // restore without resetting a counter
        context->CSSetUnorderedAccessViews(0, 1, &savedTarget, &keepCounts);
        context->CSSetShader(savedShader.Get(), instances, instanceCount);
        for (auto* saved : savedViews) if (saved) saved->Release();
        if (savedTarget) savedTarget->Release();
        for (UINT i = 0; i < instanceCount; ++i) if (instances[i]) instances[i]->Release();
        ++bake.dispatches;
        return true;
    }
}
