// Opt-in DXGI flip-model presentation for Ogre's D3D11 render window.
//
// Why: Redux's RenderSystem_Direct3D11 creates a blt-model swap chain
// (DXGI_SWAP_EFFECT_DISCARD). Under the DWM that costs a composition copy per
// frame and leaves frame queueing to the driver; every hitch captured on
// 2026-10-20 was a Present sleep under D3D11RenderWindowSwap::swapBuffers
// (reverse_engineering/frame_hitch_va_measurement_20261020.md). Flip model
// with a frame-latency waitable object is the documented low-latency,
// even-pacing path, and this switch exists to A/B it against stock.
//
// What: IDXGIFactory::CreateSwapChain (vtable slot 10, shared by every
// factory in dxgi.dll) is wrapped. When the request is eligible the swap chain
// is created with DXGI_SWAP_EFFECT_FLIP_DISCARD, at least two buffers and
// DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT; after each Present the
// render thread waits on the waitable object, so the next frame starts when
// the queue has room instead of blocking inside the following Present.
//
// Flip model forbids a multisampled back buffer, and Redux's Ogre.cfg asks for
// FSAA (8x on the test machine). For an MSAA request the swap chain is created
// single-sampled and Ogre is handed a multisampled proxy texture of the
// requested format and sample count from GetBuffer(0); Present resolves the
// proxy into the real back buffer first. ResizeBuffers rebuilds the proxy.
//
// Fail closed: an ineligible request (sRGB or unusual format, already flip,
// stereo), a proxy that cannot be created, or a flip creation DXGI refuses
// leaves Ogre's own description in force, unchanged. The swap-chain hooks act
// only on the one swap chain this module created.
//
// Config: [Graphics] DxgiFlipModel (default 0); OPENSHIM_DXGI_FLIP_MODEL=1 wins
// over the ini. OPENSHIM_DXGI_FLIP_LATENCY (1-3, default 1) is the maximum
// frame latency; OPENSHIM_DXGI_FLIP_WAITABLE=0 keeps flip model but skips the
// waitable object (for separating the two effects). Logged under [DXGI Flip].
#include "dxgi_flip_model.h"

#include "bool_token.h"
#include "com_vtable_patch.h"
#include "diagnostic_switch.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <d3d11.h>
#include <dxgi1_3.h>

#include <cstdlib>
#include <mutex>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "dxgi-flip";

        // Public COM ABI ordinals (dxgi.h / dxgi1_2.h).
        constexpr size_t kSlotFactoryCreateSwapChain = 10;
        constexpr size_t kSlotPresent = 8;
        constexpr size_t kSlotGetBuffer = 9;
        constexpr size_t kSlotGetDesc = 12;
        constexpr size_t kSlotResizeBuffers = 13;
        constexpr size_t kSlotPresent1 = 22;

        // Bounded so a lost or occluded output can never park the render
        // thread: a timeout costs one frame of pacing, nothing more.
        constexpr DWORD kWaitableTimeoutMs = 250;

        using FnCreateDXGIFactory1 = HRESULT(WINAPI*)(REFIID, void**);
        using FnFactoryCreateSwapChain = HRESULT(STDMETHODCALLTYPE*)(
            IDXGIFactory*, IUnknown*, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**);
        using FnPresent = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT);
        using FnGetBuffer = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, REFIID, void**);
        using FnGetDesc = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, DXGI_SWAP_CHAIN_DESC*);
        using FnResizeBuffers = HRESULT(STDMETHODCALLTYPE*)(
            IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
        using FnPresent1 = HRESULT(STDMETHODCALLTYPE*)(
            IDXGISwapChain1*, UINT, UINT, const DXGI_PRESENT_PARAMETERS*);

        FnFactoryCreateSwapChain g_RealCreateSwapChain = nullptr;
        FnPresent g_RealPresent = nullptr;
        FnGetBuffer g_RealGetBuffer = nullptr;
        FnGetDesc g_RealGetDesc = nullptr;
        FnResizeBuffers g_RealResizeBuffers = nullptr;
        FnPresent1 g_RealPresent1 = nullptr;

        bool g_Armed = false;
        UINT g_MaxLatency = 1;
        bool g_UseWaitable = true;

        // Swap-chain state. Creation, resize and present all run on Ogre's
        // render thread; the mutex only orders them against a device-loss
        // recreation on another thread, which Ogre does not do today.
        std::mutex g_StateMutex;
        IDXGISwapChain* g_Chain = nullptr;   // not owned; Ogre owns it
        ID3D11Texture2D* g_Proxy = nullptr;  // owned; null without MSAA
        ID3D11DeviceContext* g_Context = nullptr;
        DXGI_FORMAT g_ProxyFormat = DXGI_FORMAT_UNKNOWN;
        DXGI_SAMPLE_DESC g_ProxySamples = { 1, 0 };
        UINT g_ProxyBindFlags = 0;
        HANDLE g_Waitable = nullptr;
        bool g_ChainHasWaitableFlag = false;
        unsigned long g_WaitTimeouts = 0;
        unsigned long g_ResolveFailures = 0;
        unsigned long g_Presents = 0;

        UINT ReadLatency()
        {
            char value[16] = {};
            const DWORD n = GetEnvironmentVariableA(
                "OPENSHIM_DXGI_FLIP_LATENCY", value, static_cast<DWORD>(sizeof(value)));
            if (n == 0 || n >= sizeof(value))
                return 1;
            const long parsed = std::strtol(value, nullptr, 10);
            if (parsed < 1)
                return 1;
            return parsed > 3 ? 3u : static_cast<UINT>(parsed);
        }

        bool ReadUseWaitable()
        {
            char value[16] = {};
            const DWORD n = GetEnvironmentVariableA(
                "OPENSHIM_DXGI_FLIP_WAITABLE", value, static_cast<DWORD>(sizeof(value)));
            if (n == 0 || n >= sizeof(value))
                return true;
            return BoolToken::IsTruthy(value, n);
        }

        // Back-buffer formats DXGI accepts for flip model.
        bool IsFlipFormat(DXGI_FORMAT format)
        {
            switch (format)
            {
            case DXGI_FORMAT_R8G8B8A8_UNORM:
            case DXGI_FORMAT_B8G8R8A8_UNORM:
            case DXGI_FORMAT_R10G10B10A2_UNORM:
            case DXGI_FORMAT_R16G16B16A16_FLOAT:
                return true;
            default:
                return false;
            }
        }

        const char* IneligibleReason(const DXGI_SWAP_CHAIN_DESC& desc)
        {
            if (desc.SwapEffect != DXGI_SWAP_EFFECT_DISCARD &&
                desc.SwapEffect != DXGI_SWAP_EFFECT_SEQUENTIAL)
                return "swap effect is not a blt model";
            if (!IsFlipFormat(desc.BufferDesc.Format))
                return "back-buffer format is not a flip-model format (sRGB?)";
            if (!(desc.BufferUsage & DXGI_USAGE_RENDER_TARGET_OUTPUT))
                return "back buffer is not a render target";
            if (desc.SampleDesc.Count == 0)
                return "sample count is zero";
            if (!desc.OutputWindow)
                return "no output window";
            return nullptr;
        }

        void ReleaseProxyLocked()
        {
            if (g_Proxy)
            {
                g_Proxy->Release();
                g_Proxy = nullptr;
            }
        }

        void ResetStateLocked()
        {
            ReleaseProxyLocked();
            if (g_Context)
            {
                g_Context->Release();
                g_Context = nullptr;
            }
            if (g_Waitable)
            {
                CloseHandle(g_Waitable);
                g_Waitable = nullptr;
            }
            g_Chain = nullptr;
            g_ChainHasWaitableFlag = false;
            g_ProxySamples = { 1, 0 };
        }

        ID3D11Texture2D* CreateProxy(ID3D11Device* device, UINT width, UINT height)
        {
            D3D11_TEXTURE2D_DESC td = {};
            td.Width = width;
            td.Height = height;
            td.MipLevels = 1;
            td.ArraySize = 1;
            td.Format = g_ProxyFormat;
            td.SampleDesc = g_ProxySamples;
            td.Usage = D3D11_USAGE_DEFAULT;
            td.BindFlags = g_ProxyBindFlags;
            ID3D11Texture2D* texture = nullptr;
            if (FAILED(device->CreateTexture2D(&td, nullptr, &texture)))
                return nullptr;
            return texture;
        }

        // Rebuilds the proxy at the swap chain's current size. Called with the
        // lock held, after creation and after every successful ResizeBuffers.
        bool RebuildProxyLocked(IDXGISwapChain* chain)
        {
            ReleaseProxyLocked();
            if (!g_Context)
                return false;
            DXGI_SWAP_CHAIN_DESC current = {};
            if (FAILED(g_RealGetDesc(chain, &current)))
                return false;
            ID3D11Device* device = nullptr;
            g_Context->GetDevice(&device);
            if (!device)
                return false;
            if (current.BufferDesc.Format != DXGI_FORMAT_UNKNOWN)
                g_ProxyFormat = current.BufferDesc.Format;
            g_Proxy = CreateProxy(device, current.BufferDesc.Width, current.BufferDesc.Height);
            device->Release();
            return g_Proxy != nullptr;
        }

        void ResolveProxyLocked(IDXGISwapChain* chain)
        {
            if (!g_Proxy || !g_Context)
                return;
            ID3D11Texture2D* backBuffer = nullptr;
            if (FAILED(g_RealGetBuffer(chain, 0, __uuidof(ID3D11Texture2D),
                                       reinterpret_cast<void**>(&backBuffer))) ||
                !backBuffer)
            {
                if (g_ResolveFailures++ == 0)
                    LogShimA(LogLevel::Warn, kComponent,
                             "[DXGI Flip] could not fetch the flip back buffer to resolve into; frame presented unresolved");
                return;
            }
            g_Context->ResolveSubresource(backBuffer, 0, g_Proxy, 0, g_ProxyFormat);
            backBuffer->Release();
        }

        void WaitForQueueRoom()
        {
            if (!g_Waitable)
                return;
            if (WaitForSingleObjectEx(g_Waitable, kWaitableTimeoutMs, TRUE) == WAIT_TIMEOUT)
                ++g_WaitTimeouts;
        }

        void NoteFirstPresent(UINT syncInterval, UINT flags, HRESULT hr)
        {
            // Pacing results are meaningless if VSync never reached the flip
            // chain, so the first present says what it was asked to do.
            if (g_Presents == 1)
                LogShimA(LogLevel::Info, kComponent,
                         "[DXGI Flip] first present: syncInterval=%u flags=0x%X hr=0x%08lX",
                         syncInterval, flags, static_cast<unsigned long>(hr));
        }

        HRESULT STDMETHODCALLTYPE HookPresent(IDXGISwapChain* self, UINT syncInterval, UINT flags)
        {
            if (self != g_Chain)
                return g_RealPresent(self, syncInterval, flags);
            if (!(flags & DXGI_PRESENT_TEST))
            {
                std::lock_guard<std::mutex> lock(g_StateMutex);
                ResolveProxyLocked(self);
            }
            const HRESULT hr = g_RealPresent(self, syncInterval, flags);
            if (!(flags & DXGI_PRESENT_TEST))
            {
                ++g_Presents;
                NoteFirstPresent(syncInterval, flags, hr);
                WaitForQueueRoom();
            }
            return hr;
        }

        HRESULT STDMETHODCALLTYPE HookPresent1(
            IDXGISwapChain1* self, UINT syncInterval, UINT flags, const DXGI_PRESENT_PARAMETERS* params)
        {
            if (static_cast<IDXGISwapChain*>(self) != g_Chain)
                return g_RealPresent1(self, syncInterval, flags, params);
            if (!(flags & DXGI_PRESENT_TEST))
            {
                std::lock_guard<std::mutex> lock(g_StateMutex);
                ResolveProxyLocked(self);
            }
            const HRESULT hr = g_RealPresent1(self, syncInterval, flags, params);
            if (!(flags & DXGI_PRESENT_TEST))
            {
                ++g_Presents;
                NoteFirstPresent(syncInterval, flags, hr);
                WaitForQueueRoom();
            }
            return hr;
        }

        HRESULT STDMETHODCALLTYPE HookGetBuffer(IDXGISwapChain* self, UINT buffer, REFIID riid, void** surface)
        {
            if (self == g_Chain && buffer == 0)
            {
                std::lock_guard<std::mutex> lock(g_StateMutex);
                if (g_Proxy)
                    return g_Proxy->QueryInterface(riid, surface);
            }
            return g_RealGetBuffer(self, buffer, riid, surface);
        }

        HRESULT STDMETHODCALLTYPE HookGetDesc(IDXGISwapChain* self, DXGI_SWAP_CHAIN_DESC* desc)
        {
            const HRESULT hr = g_RealGetDesc(self, desc);
            if (SUCCEEDED(hr) && desc && self == g_Chain)
            {
                // Ogre sized its depth buffer and views from the sample count
                // it asked for; keep reporting that one.
                std::lock_guard<std::mutex> lock(g_StateMutex);
                if (g_Proxy)
                    desc->SampleDesc = g_ProxySamples;
            }
            return hr;
        }

        HRESULT STDMETHODCALLTYPE HookResizeBuffers(
            IDXGISwapChain* self, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT format, UINT flags)
        {
            if (self != g_Chain)
                return g_RealResizeBuffers(self, bufferCount, width, height, format, flags);

            std::lock_guard<std::mutex> lock(g_StateMutex);
            const bool hadProxy = g_Proxy != nullptr;
            ReleaseProxyLocked();
            // Flip model needs two or more buffers (0 keeps the current
            // count), and the waitable flag cannot be added or removed here.
            if (bufferCount == 1)
                bufferCount = 0;
            if (g_ChainHasWaitableFlag)
                flags |= DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
            else
                flags &= ~static_cast<UINT>(DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT);

            const HRESULT hr = g_RealResizeBuffers(self, bufferCount, width, height, format, flags);
            if (hadProxy)
            {
                // On failure the old size still stands; rebuild at whatever
                // the swap chain now reports so Ogre's next GetBuffer works.
                const bool rebuilt = RebuildProxyLocked(self);
                LogShimA(rebuilt && SUCCEEDED(hr) ? LogLevel::Info : LogLevel::Error, kComponent,
                         "[DXGI Flip] ResizeBuffers %ux%u result=0x%08lX msaaProxy=%s waitTimeouts=%lu presents=%lu",
                         width, height, static_cast<unsigned long>(hr), rebuilt ? "rebuilt" : "FAILED",
                         g_WaitTimeouts, g_Presents);
            }
            else
            {
                LogShimA(SUCCEEDED(hr) ? LogLevel::Info : LogLevel::Warn, kComponent,
                         "[DXGI Flip] ResizeBuffers %ux%u result=0x%08lX waitTimeouts=%lu presents=%lu",
                         width, height, static_cast<unsigned long>(hr), g_WaitTimeouts, g_Presents);
            }
            return hr;
        }

        bool PatchSwapChain(IDXGISwapChain* chain)
        {
            using ComVtablePatch::OnForeignWrapper;
            using ComVtablePatch::PatchEntry;
            using ComVtablePatch::Succeeded;
            const bool ok =
                Succeeded(PatchEntry(chain, kSlotPresent, &HookPresent, g_RealPresent, OnForeignWrapper::Refuse)) &&
                Succeeded(PatchEntry(chain, kSlotGetBuffer, &HookGetBuffer, g_RealGetBuffer, OnForeignWrapper::Refuse)) &&
                Succeeded(PatchEntry(chain, kSlotGetDesc, &HookGetDesc, g_RealGetDesc, OnForeignWrapper::Refuse)) &&
                Succeeded(PatchEntry(chain, kSlotResizeBuffers, &HookResizeBuffers, g_RealResizeBuffers,
                                     OnForeignWrapper::Refuse));
            if (!ok)
                return false;

            // Ogre 1.10 presents through IDXGISwapChain::Present; Present1 is
            // covered so a caller using it can never skip the proxy resolve.
            IDXGISwapChain1* chain1 = nullptr;
            if (SUCCEEDED(chain->QueryInterface(__uuidof(IDXGISwapChain1), reinterpret_cast<void**>(&chain1))) &&
                chain1)
            {
                const bool ok1 = Succeeded(PatchEntry(chain1, kSlotPresent1, &HookPresent1, g_RealPresent1,
                                                      OnForeignWrapper::Refuse));
                chain1->Release();
                if (!ok1)
                    return false;
            }
            return true;
        }

        void SetLatency(IDXGISwapChain* chain, IUnknown* device, bool waitable)
        {
            if (waitable)
            {
                IDXGISwapChain2* chain2 = nullptr;
                if (SUCCEEDED(chain->QueryInterface(__uuidof(IDXGISwapChain2), reinterpret_cast<void**>(&chain2))) &&
                    chain2)
                {
                    chain2->SetMaximumFrameLatency(g_MaxLatency);
                    g_Waitable = chain2->GetFrameLatencyWaitableObject();
                    chain2->Release();
                    if (g_Waitable)
                        return;
                }
            }
            IDXGIDevice1* dxgiDevice = nullptr;
            if (SUCCEEDED(device->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&dxgiDevice))) &&
                dxgiDevice)
            {
                dxgiDevice->SetMaximumFrameLatency(g_MaxLatency);
                dxgiDevice->Release();
            }
        }

        HRESULT STDMETHODCALLTYPE HookCreateSwapChain(
            IDXGIFactory* self, IUnknown* device, DXGI_SWAP_CHAIN_DESC* desc, IDXGISwapChain** swapChain)
        {
            if (!desc || !swapChain || !device)
                return g_RealCreateSwapChain(self, device, desc, swapChain);

            const char* reason = IneligibleReason(*desc);
            ID3D11Device* d3dDevice = nullptr;
            if (!reason &&
                (FAILED(device->QueryInterface(__uuidof(ID3D11Device), reinterpret_cast<void**>(&d3dDevice))) ||
                 !d3dDevice))
                reason = "device is not a D3D11 device";
            if (reason)
            {
                LogShimA(LogLevel::Info, kComponent,
                         "[DXGI Flip] kept Ogre's swap chain (swapEffect=%u format=%u samples=%u): %s",
                         static_cast<unsigned>(desc->SwapEffect), static_cast<unsigned>(desc->BufferDesc.Format),
                         desc->SampleDesc.Count, reason);
                return g_RealCreateSwapChain(self, device, desc, swapChain);
            }

            std::lock_guard<std::mutex> lock(g_StateMutex);
            // A second creation is Ogre rebuilding after device loss or a
            // window recreation; the previous chain is gone with its device.
            ResetStateLocked();

            // The proxy is made before the flip swap chain so a refusal here
            // leaves the window never having seen flip model.
            const bool msaa = desc->SampleDesc.Count > 1;
            if (msaa)
            {
                g_ProxyFormat = desc->BufferDesc.Format;
                g_ProxySamples = desc->SampleDesc;
                g_ProxyBindFlags = D3D11_BIND_RENDER_TARGET |
                    ((desc->BufferUsage & DXGI_USAGE_SHADER_INPUT) ? D3D11_BIND_SHADER_RESOURCE : 0u);
                g_Proxy = CreateProxy(d3dDevice, desc->BufferDesc.Width, desc->BufferDesc.Height);
                if (!g_Proxy)
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "[DXGI Flip] could not create the %ux MSAA proxy (%ux%u format=%u); kept Ogre's swap chain",
                             desc->SampleDesc.Count, desc->BufferDesc.Width, desc->BufferDesc.Height,
                             static_cast<unsigned>(desc->BufferDesc.Format));
                    ResetStateLocked();
                    d3dDevice->Release();
                    return g_RealCreateSwapChain(self, device, desc, swapChain);
                }
            }

            DXGI_SWAP_CHAIN_DESC flip = *desc;
            flip.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
            flip.BufferCount = desc->BufferCount < 2 ? 2 : desc->BufferCount;
            flip.SampleDesc = { 1, 0 };
            if (g_UseWaitable)
                flip.Flags |= DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;

            IDXGISwapChain* created = nullptr;
            HRESULT hr = g_RealCreateSwapChain(self, device, &flip, &created);
            if (FAILED(hr) && g_UseWaitable)
            {
                const HRESULT waitableHr = hr;
                flip.Flags &= ~static_cast<UINT>(DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT);
                hr = g_RealCreateSwapChain(self, device, &flip, &created);
                LogShimA(LogLevel::Warn, kComponent,
                         "[DXGI Flip] waitable flip swap chain refused (0x%08lX); without waitable: 0x%08lX",
                         static_cast<unsigned long>(waitableHr), static_cast<unsigned long>(hr));
            }
            if (FAILED(hr) || !created)
            {
                LogShimA(LogLevel::Warn, kComponent,
                         "[DXGI Flip] flip swap chain refused (0x%08lX); kept Ogre's swap chain",
                         static_cast<unsigned long>(hr));
                ResetStateLocked();
                d3dDevice->Release();
                return g_RealCreateSwapChain(self, device, desc, swapChain);
            }

            if (!PatchSwapChain(created))
            {
                LogShimA(LogLevel::Warn, kComponent,
                         "[DXGI Flip] could not hook the swap chain; released the flip chain and kept Ogre's");
                created->Release();
                ResetStateLocked();
                d3dDevice->Release();
                return g_RealCreateSwapChain(self, device, desc, swapChain);
            }

            g_Chain = created;
            g_ChainHasWaitableFlag = (flip.Flags & DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT) != 0;
            d3dDevice->GetImmediateContext(&g_Context);
            SetLatency(created, device, g_ChainHasWaitableFlag);
            d3dDevice->Release();
            *swapChain = created;

            LogShimA(LogLevel::Info, kComponent,
                     "[DXGI Flip] active: FLIP_DISCARD buffers=%u (Ogre asked %u, swapEffect=%u) %ux%u format=%u windowed=%s "
                     "maxLatency=%u waitable=%s msaaProxy=%s",
                     flip.BufferCount, desc->BufferCount, static_cast<unsigned>(desc->SwapEffect),
                     flip.BufferDesc.Width, flip.BufferDesc.Height, static_cast<unsigned>(flip.BufferDesc.Format),
                     flip.Windowed ? "yes" : "no", g_MaxLatency, g_Waitable ? "yes" : "no",
                     msaa ? "yes" : "no");
            if (msaa)
                LogShimA(LogLevel::Info, kComponent,
                         "[DXGI Flip] MSAA %ux (quality %u) renders into a proxy resolved at Present",
                         g_ProxySamples.Count, g_ProxySamples.Quality);
            return hr;
        }
    }

    void InitializeDxgiFlipModel()
    {
        if (g_Armed)
            return;
        if (!DiagnosticSwitch::Requested("OPENSHIM_DXGI_FLIP_MODEL", "Graphics", "DxgiFlipModel"))
            return;

        g_MaxLatency = ReadLatency();
        g_UseWaitable = ReadUseWaitable();

        // Every IDXGIFactory in the process shares dxgi.dll's vtable, so a
        // factory made here arms the hook for the one Ogre makes later. The
        // module reference is kept so the patched vtable is never unloaded.
        HMODULE dxgi = LoadLibraryW(L"dxgi.dll");
        const auto createFactory = dxgi
            ? reinterpret_cast<FnCreateDXGIFactory1>(GetProcAddress(dxgi, "CreateDXGIFactory1"))
            : nullptr;
        IDXGIFactory* factory = nullptr;
        if (!createFactory ||
            FAILED(createFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory))) || !factory)
        {
            LogShimA(LogLevel::Warn, kComponent, "[DXGI Flip] requested but no DXGI factory is available; not armed");
            return;
        }

        const auto result = ComVtablePatch::PatchEntry(
            factory, kSlotFactoryCreateSwapChain, &HookCreateSwapChain, g_RealCreateSwapChain,
            ComVtablePatch::OnForeignWrapper::Refuse);
        factory->Release();
        if (!ComVtablePatch::Succeeded(result))
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[DXGI Flip] requested but IDXGIFactory::CreateSwapChain could not be hooked (result=%d); not armed",
                     static_cast<int>(result));
            return;
        }

        g_Armed = true;
        LogShimA(LogLevel::Info, kComponent,
                 "[DXGI Flip] armed: Ogre's D3D11 swap chain will be created as FLIP_DISCARD (maxLatency=%u waitable=%s)",
                 g_MaxLatency, g_UseWaitable ? "yes" : "no");
    }
}
