#pragma once

#include <algorithm>

// Forward declarations keep the public control surface lightweight while also
// letting the implementation declare its factory hook before the concrete DXGI
// headers are included by the translation unit.
struct IDXGIFactory;
struct IUnknown;
struct DXGI_SWAP_CHAIN_DESC;
struct IDXGISwapChain;

namespace BZROpenShim
{
    namespace
    {
        // Implementation-only forward declaration. `long` is HRESULT's Win32
        // underlying type and __stdcall is STDMETHODCALLTYPE on the 32-bit
        // target; the definition in dx11_enhanced_fxaa.cpp uses the canonical
        // SDK spellings after including Windows/DXGI headers.
        long __stdcall HookFactoryCreateSwapChain(
            IDXGIFactory*, IUnknown*, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**);
    }

    // Starts the DX11 Enhanced presentation-stage FXAA path when requested.
    //
    // The reference openshim.ini enables it for Enhanced testing:
    //
    //   [DX11Enhanced]
    //   FXAA = 1
    //
    // or OPENSHIM_DX11_ENHANCED_FXAA=1.
    //
    // A missing key still fails closed, so existing stock/default DX11 installs
    // that have not adopted the Enhanced reference INI remain untouched. The
    // implementation watches only RenderSystem_Direct3D11.dll; DX9 is untouched.
    void InitializeDx11EnhancedFxaa();

    // Stops the short-lived renderer-discovery worker. Installed COM/IAT hooks
    // remain process-lifetime and become pass-through once shutdown is set.
    void ShutdownDx11EnhancedFxaa();
}
