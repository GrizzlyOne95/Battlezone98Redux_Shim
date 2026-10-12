#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <d3d11_4.h>
#include <wrl/client.h>
#include <string>
#include "frame_bridge_protocol.h"
#include "frame_bridge_depth.h"

namespace BZROpenShim::FrameBridge
{
    inline std::wstring MappingName(DWORD pid)
    {
        return L"Local\\OpenShim.FrameBridge." + std::to_wstring(pid);
    }
    inline LONG ReadInterlocked(std::int32_t& value)
    {
        static_assert(sizeof(LONG) == sizeof(value));
        return InterlockedCompareExchange(reinterpret_cast<volatile LONG*>(&value), 0, 0);
    }
    inline LONG Exchange(std::int32_t& value, LONG desired)
    {
        return InterlockedExchange(reinterpret_cast<volatile LONG*>(&value), desired);
    }
    inline bool Claim(std::int32_t& value, LONG expected, LONG desired)
    {
        return InterlockedCompareExchange(reinterpret_cast<volatile LONG*>(&value), desired, expected) == expected;
    }

    // A single bounded mailbox. Capture skips occupied frames instead of ever
    // waiting for the helper. The consumer returns Free only AFTER its GPU has
    // finished reading. A dead consumer freezes capture, not the game's renderer.
    class Producer
    {
    public:
        Producer() = default;
        ~Producer() { Stop(); }
        Producer(const Producer&) = delete;
        Producer& operator=(const Producer&) = delete;
        HRESULT Start(ID3D11Device* device, const D3D11_TEXTURE2D_DESC& source, bool depthEnabled = false);
        HRESULT Publish(ID3D11Texture2D* source, ID3D11Texture2D* depthSource = nullptr,
            DepthReduction reduction = DepthReduction::Minimum);
        // Diagnostic snapshot before the selected matching depth clear. Call
        // before the real clear, serialized with Publish on the render thread.
        void BeforeDepthClear(ID3D11DeviceContext* context, ID3D11DepthStencilView* view, UINT flags);
        void Stop();
        bool Active() const { return frame_ && ReadInterlocked(frame_->active) == 1; }
    private:
        Microsoft::WRL::ComPtr<ID3D11Device> device_;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext4> context_;
        Microsoft::WRL::ComPtr<ID3D11Texture2D> color_;
        Microsoft::WRL::ComPtr<ID3D11Texture2D> depth_;
        DepthExtractor extractor_;
        D3D11_TEXTURE2D_DESC depthDesc_{};
        Microsoft::WRL::ComPtr<ID3D11Texture2D> preclear_;
        D3D11_TEXTURE2D_DESC preclearDesc_{};
        UINT matchingDepthClears_ = 0, capturedDepthOrdinal_ = 0;
        HRESULT preclearResult_ = S_OK;
        Microsoft::WRL::ComPtr<ID3D11Fence> ready_;
        D3D11_TEXTURE2D_DESC sourceDesc_{};
        HANDLE textureHandle_ = nullptr;
        HANDLE depthHandle_ = nullptr;
        HANDLE fenceHandle_ = nullptr;
        HANDLE mapping_ = nullptr;
        SharedFrame* frame_ = nullptr;
        std::uint64_t nextFrame_ = 0;
        void CaptureDepth(ID3D11Texture2D* source, DepthReduction reduction);
    };
}
