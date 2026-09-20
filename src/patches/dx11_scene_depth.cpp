// DX11 scene-depth qualification instrument (Phase A).
//
// See include/dx11_scene_depth.h for what this is and why it exists, and
// Docs/DX11_SCENE_DEPTH_AND_SCREENSPACE_EFFECTS.md for the investigation that
// defines its acceptance criteria.
//
// The decision logic - is this address the same depth surface I saw before, or
// a recycled allocation? - lives in include/scene_depth_facts.h and is covered
// by tests/scene_depth_facts_tests.cpp with no D3D11 present. This file is the
// shell: hook, record, report.
//
// Three deliberate limits, stated here so a capture is read correctly:
//
//   * Resource DESTRUCTION is not observed. Hooking Release on every texture to
//     see it would put this instrument in the path of every AddRef/Release in
//     the renderer, which is a large risk for a diagnostic. Instead a
//     destruction is inferred after the fact: when CreateTexture2D returns an
//     address already in the table describing a different surface, that is a
//     recreate, and it is what a mission change or a resize looks like.
//
//   * The device context vtable is known to be reverted mid-frame in this game
//     (a once-per-frame re-check loses draws), so the OMSetRenderTargets hook
//     is re-asserted from the reporting worker and from the device hooks, which
//     sit on the far more stable device vtable. Bind counts are therefore a
//     lower bound, not a census. They are still comparable BETWEEN resources
//     within one run, which is what the main-view question needs.
//
//   * Binding is recorded per OMSetRenderTargets call, not per draw.

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <d3d11.h>

#include <atomic>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <process.h>
#include <string>

#include "dx11_scene_depth.h"
#include "scene_depth_facts.h"
#include "shim_log.h"

namespace BZROpenShim
{
    namespace
    {
        using namespace BZROpenShim::SceneDepth;

        constexpr char kComponent[] = "dx11-scene-depth";
        constexpr char kEnvironmentSwitch[] = "OPENSHIM_DX11_SCENE_DEPTH_DIAG";
        constexpr char kIniSection[] = "DX11Enhanced";
        constexpr char kIniKey[] = "SceneDepthDiagnostic";

        constexpr unsigned kDiscoveryAttempts = 1200; // 30 seconds at 25 ms.
        constexpr DWORD kDiscoverySleepMs = 25;
        constexpr DWORD kReportIntervalMs = 15000;

        // Vtable slots. ID3D11Device and ID3D11DeviceContext both begin with
        // IUnknown; ID3D11DeviceContext additionally carries ID3D11DeviceChild.
        // These are fixed by the D3D11 ABI and have never moved.
        constexpr size_t kDeviceCreateTexture2D = 5;
        constexpr size_t kDeviceCreateRenderTargetView = 9;
        constexpr size_t kDeviceCreateDepthStencilView = 10;
        constexpr size_t kContextOMSetRenderTargets = 33;

        // Bounded for the same reason the registry is: an instrument that grows
        // without limit in response to engine behaviour is a way to turn a
        // diagnostic into an outage.
        constexpr size_t kMaxRenderTargetViews = 128;

        std::atomic<bool> g_ShutdownRequested{ false };
        std::atomic<bool> g_Enabled{ false };
        uintptr_t g_Worker = 0;

        std::mutex g_HookMutex;
        std::mutex g_DataMutex;

        Registry g_Registry;

        struct RenderTargetSize
        {
            void* view = nullptr;
            UINT width = 0;
            UINT height = 0;
        };

        RenderTargetSize g_RenderTargets[kMaxRenderTargetViews] = {};
        size_t g_RenderTargetCount = 0;
        bool g_RenderTargetOverflow = false;

        // DSV -> the resource it was created over. Resolving this at bind time
        // by asking the view would mean a COM call inside OMSetRenderTargets.
        struct DepthViewOwner
        {
            void* view = nullptr;
            uint64_t resource = 0;
        };

        DepthViewOwner g_DepthViews[kMaxRenderTargetViews] = {};
        size_t g_DepthViewCount = 0;
        bool g_DepthViewOverflow = false;

        void* g_CurrentDepthView = nullptr;
        unsigned long long g_BindTransitions = 0;
        bool g_TableDirty = false;

        using FnCreateTexture2D = HRESULT(STDMETHODCALLTYPE*)(
            ID3D11Device*, const D3D11_TEXTURE2D_DESC*, const D3D11_SUBRESOURCE_DATA*,
            ID3D11Texture2D**);
        using FnCreateDepthStencilView = HRESULT(STDMETHODCALLTYPE*)(
            ID3D11Device*, ID3D11Resource*, const D3D11_DEPTH_STENCIL_VIEW_DESC*,
            ID3D11DepthStencilView**);
        using FnCreateRenderTargetView = HRESULT(STDMETHODCALLTYPE*)(
            ID3D11Device*, ID3D11Resource*, const D3D11_RENDER_TARGET_VIEW_DESC*,
            ID3D11RenderTargetView**);
        using FnOMSetRenderTargets = void(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, UINT, ID3D11RenderTargetView* const*, ID3D11DepthStencilView*);

        using FnD3D11CreateDevice = HRESULT(WINAPI*)(
            IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
            const D3D_FEATURE_LEVEL*, UINT, UINT,
            ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);
        using FnD3D11CreateDeviceAndSwapChain = HRESULT(WINAPI*)(
            IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
            const D3D_FEATURE_LEVEL*, UINT, UINT,
            const DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**,
            ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);

        FnCreateTexture2D g_RealCreateTexture2D = nullptr;
        FnCreateDepthStencilView g_RealCreateDepthStencilView = nullptr;
        FnCreateRenderTargetView g_RealCreateRenderTargetView = nullptr;
        FnOMSetRenderTargets g_RealOMSetRenderTargets = nullptr;
        FnD3D11CreateDevice g_RealD3D11CreateDevice = nullptr;
        FnD3D11CreateDeviceAndSwapChain g_RealD3D11CreateDeviceAndSwapChain = nullptr;

        ID3D11DeviceContext* g_ImmediateContext = nullptr;

        // ------------------------------------------------------------------
        // Gating
        // ------------------------------------------------------------------

        bool StringIsTruthy(const char* value)
        {
            if (!value || !*value)
                return false;
            return value[0] == '1' || value[0] == 'y' || value[0] == 'Y'
                || value[0] == 't' || value[0] == 'T'
                || value[0] == 'o' || value[0] == 'O';
        }

        std::string GetOpenShimIniPath()
        {
            char path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return "openshim.ini";

            char* lastSlash = std::strrchr(path, '\\');
            if (!lastSlash)
                return "openshim.ini";

            *(lastSlash + 1) = '\0';
            std::string iniPath(path);
            iniPath += "openshim.ini";
            return iniPath;
        }

        bool DiagnosticRequested()
        {
            char envValue[64] = {};
            const DWORD envLength = GetEnvironmentVariableA(
                kEnvironmentSwitch, envValue, static_cast<DWORD>(sizeof(envValue)));
            if (envLength > 0 && envLength < sizeof(envValue))
                return StringIsTruthy(envValue);

            const std::string iniPath = GetOpenShimIniPath();
            return GetPrivateProfileIntA(kIniSection, kIniKey, 0, iniPath.c_str()) != 0;
        }

        // ------------------------------------------------------------------
        // Hook installation
        // ------------------------------------------------------------------

        template <typename T>
        bool PatchComVtableEntry(void* object, size_t index, T hook, T& original, const char* label)
        {
            if (!object || !hook)
                return false;

            std::lock_guard<std::mutex> lock(g_HookMutex);

            auto*** objectAsVtable = reinterpret_cast<void***>(object);
            if (!objectAsVtable || !*objectAsVtable)
                return false;

            void** vtable = *objectAsVtable;
            void* current = vtable[index];
            if (current == reinterpret_cast<void*>(hook))
                return true;

            DWORD oldProtect = 0;
            if (!VirtualProtect(&vtable[index], sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "[SceneDepth] failed to make %s vtable entry writable (err=%lu)",
                    label, GetLastError());
                return false;
            }

            // Preserve the first predecessor, so this instrument and the
            // Enhanced FXAA / colorspace hooks coexist regardless of which one
            // reached the shared vtable first.
            if (!original)
                original = reinterpret_cast<T>(current);

            vtable[index] = reinterpret_cast<void*>(hook);

            DWORD ignored = 0;
            VirtualProtect(&vtable[index], sizeof(void*), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), &vtable[index], sizeof(void*));
            return true;
        }

        // ------------------------------------------------------------------
        // Bookkeeping
        // ------------------------------------------------------------------

        void RememberRenderTargetSize(void* view, UINT width, UINT height)
        {
            if (!view)
                return;

            for (size_t i = 0; i < g_RenderTargetCount; ++i)
            {
                if (g_RenderTargets[i].view == view)
                {
                    g_RenderTargets[i].width = width;
                    g_RenderTargets[i].height = height;
                    return;
                }
            }

            if (g_RenderTargetCount >= kMaxRenderTargetViews)
            {
                if (!g_RenderTargetOverflow)
                {
                    g_RenderTargetOverflow = true;
                    LogShimA(LogLevel::Warn, kComponent,
                        "[SceneDepth] render-target view table full at %zu entries; "
                        "later targets report size 0 and bind records lose their dimensions",
                        kMaxRenderTargetViews);
                }
                return;
            }

            g_RenderTargets[g_RenderTargetCount].view = view;
            g_RenderTargets[g_RenderTargetCount].width = width;
            g_RenderTargets[g_RenderTargetCount].height = height;
            ++g_RenderTargetCount;
        }

        bool LookupRenderTargetSize(void* view, UINT* width, UINT* height)
        {
            for (size_t i = 0; i < g_RenderTargetCount; ++i)
            {
                if (g_RenderTargets[i].view == view)
                {
                    *width = g_RenderTargets[i].width;
                    *height = g_RenderTargets[i].height;
                    return true;
                }
            }
            return false;
        }

        void RememberDepthView(void* view, uint64_t resource)
        {
            if (!view)
                return;

            for (size_t i = 0; i < g_DepthViewCount; ++i)
            {
                if (g_DepthViews[i].view == view)
                {
                    g_DepthViews[i].resource = resource;
                    return;
                }
            }

            if (g_DepthViewCount >= kMaxRenderTargetViews)
            {
                if (!g_DepthViewOverflow)
                {
                    g_DepthViewOverflow = true;
                    LogShimA(LogLevel::Warn, kComponent,
                        "[SceneDepth] depth-view table full at %zu entries; "
                        "later views cannot be attributed to a resource",
                        kMaxRenderTargetViews);
                }
                return;
            }

            g_DepthViews[g_DepthViewCount].view = view;
            g_DepthViews[g_DepthViewCount].resource = resource;
            ++g_DepthViewCount;
        }

        uint64_t LookupDepthViewOwner(void* view)
        {
            for (size_t i = 0; i < g_DepthViewCount; ++i)
            {
                if (g_DepthViews[i].view == view)
                    return g_DepthViews[i].resource;
            }
            return 0;
        }

        // Reading a COM object's description is the one place this file calls
        // into the renderer's own memory, so it is isolated in a function with
        // no unwinding objects and guarded structurally. A catch(...) would not
        // see an access violation here; only __try/__except does.
        __declspec(noinline) bool TryGetTexture2DSize(ID3D11Resource* resource, UINT* width, UINT* height)
        {
            if (!resource)
                return false;

            bool ok = false;
            __try
            {
                ID3D11Texture2D* texture = nullptr;
                if (SUCCEEDED(resource->QueryInterface(__uuidof(ID3D11Texture2D),
                        reinterpret_cast<void**>(&texture))) && texture)
                {
                    D3D11_TEXTURE2D_DESC desc = {};
                    texture->GetDesc(&desc);
                    *width = desc.Width;
                    *height = desc.Height;
                    texture->Release();
                    ok = true;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ok = false;
            }
            return ok;
        }

        void DescribeCreation(const Observation& entry, Registry::Event event)
        {
            const char* formatName = FormatName(entry.facts.format);
            char formatBuffer[32] = {};
            if (!formatName)
            {
                std::snprintf(formatBuffer, sizeof(formatBuffer), "format(%u)", entry.facts.format);
                formatName = formatBuffer;
            }

            LogShimA(LogLevel::Info, kComponent,
                "[SceneDepth] %s depth resource serial=%u gen=%u addr=0x%llX %ux%u %s "
                "samples=%u/%u bind=0x%X%s misc=0x%X array=%u mips=%u usage=%u",
                event == Registry::Event::Recreated ? "recreated" : "new",
                entry.serial,
                entry.generation,
                static_cast<unsigned long long>(entry.facts.resource),
                entry.facts.width, entry.facts.height,
                formatName,
                entry.facts.sampleCount, entry.facts.sampleQuality,
                entry.facts.bindFlags,
                IsShaderReadable(entry.facts.bindFlags) ? " (SHADER_RESOURCE)" : " (no SRV bind)",
                entry.facts.miscFlags, entry.facts.arraySize, entry.facts.mipLevels,
                entry.facts.usage);
        }

        void ReportTable()
        {
            std::lock_guard<std::mutex> lock(g_DataMutex);
            if (!g_TableDirty)
                return;
            g_TableDirty = false;

            LogShimA(LogLevel::Info, kComponent,
                "[SceneDepth] --- depth surfaces seen: %zu%s, DSV binds observed (transitions=%llu) ---",
                g_Registry.Size(),
                g_Registry.Overflowed() ? " (TABLE OVERFLOWED)" : "",
                g_BindTransitions);

            for (size_t i = 0; i < g_Registry.Size(); ++i)
            {
                const Observation* entry = g_Registry.At(i);
                if (!entry)
                    continue;

                const char* formatName = FormatName(entry->facts.format);
                char formatBuffer[32] = {};
                if (!formatName)
                {
                    std::snprintf(formatBuffer, sizeof(formatBuffer), "format(%u)", entry->facts.format);
                    formatName = formatBuffer;
                }

                const char* dsvName = DsvDimensionName(entry->dsvDimension);
                char dsvBuffer[32] = {};
                if (!dsvName)
                {
                    std::snprintf(dsvBuffer, sizeof(dsvBuffer), "dim(%u)", entry->dsvDimension);
                    dsvName = dsvBuffer;
                }

                LogShimA(LogLevel::Info, kComponent,
                    "[SceneDepth]   serial=%u gen=%u %ux%u %s samples=%u srv=%s "
                    "dsvs=%u dsvDim=%s binds=%llu lastRT=%ux%u rtCount=%u withRT=%s",
                    entry->serial, entry->generation,
                    entry->facts.width, entry->facts.height, formatName,
                    entry->facts.sampleCount,
                    IsShaderReadable(entry->facts.bindFlags) ? "yes" : "no",
                    entry->dsvCount, dsvName,
                    static_cast<unsigned long long>(entry->bindCount),
                    entry->lastRtWidth, entry->lastRtHeight, entry->lastRtCount,
                    entry->everBoundWithRenderTarget ? "yes" : "no");
            }
        }

        // ------------------------------------------------------------------
        // Hooks
        // ------------------------------------------------------------------

        void EnsureContextHook();

        HRESULT STDMETHODCALLTYPE HookCreateTexture2D(
            ID3D11Device* device,
            const D3D11_TEXTURE2D_DESC* desc,
            const D3D11_SUBRESOURCE_DATA* initialData,
            ID3D11Texture2D** texture)
        {
            const HRESULT hr = g_RealCreateTexture2D
                ? g_RealCreateTexture2D(device, desc, initialData, texture)
                : E_FAIL;

            if (FAILED(hr) || !desc || !texture || !*texture
                || g_ShutdownRequested.load(std::memory_order_acquire))
            {
                return hr;
            }

            if (!IsDepthCandidate(desc->BindFlags))
            {
                // The device vtable is stable where the context vtable is not,
                // so this is a cheap, frequent opportunity to re-assert the
                // binding hook without a per-frame timer.
                EnsureContextHook();
                return hr;
            }

            TextureFacts facts;
            facts.resource = reinterpret_cast<uint64_t>(*texture);
            facts.width = desc->Width;
            facts.height = desc->Height;
            facts.format = static_cast<uint32_t>(desc->Format);
            facts.sampleCount = desc->SampleDesc.Count;
            facts.sampleQuality = desc->SampleDesc.Quality;
            facts.bindFlags = desc->BindFlags;
            facts.miscFlags = desc->MiscFlags;
            facts.arraySize = desc->ArraySize;
            facts.mipLevels = desc->MipLevels;
            facts.usage = static_cast<uint32_t>(desc->Usage);

            Observation snapshot;
            Registry::Event event = Registry::Event::Ignored;
            {
                std::lock_guard<std::mutex> lock(g_DataMutex);
                event = g_Registry.Observe(facts);
                if (event == Registry::Event::Added || event == Registry::Event::Recreated)
                {
                    const Observation* entry = g_Registry.Find(facts.resource);
                    if (entry)
                        snapshot = *entry;
                    g_TableDirty = true;
                }
            }

            if (event == Registry::Event::Added || event == Registry::Event::Recreated)
                DescribeCreation(snapshot, event);

            EnsureContextHook();
            return hr;
        }

        HRESULT STDMETHODCALLTYPE HookCreateDepthStencilView(
            ID3D11Device* device,
            ID3D11Resource* resource,
            const D3D11_DEPTH_STENCIL_VIEW_DESC* desc,
            ID3D11DepthStencilView** view)
        {
            const HRESULT hr = g_RealCreateDepthStencilView
                ? g_RealCreateDepthStencilView(device, resource, desc, view)
                : E_FAIL;

            if (FAILED(hr) || !view || !*view
                || g_ShutdownRequested.load(std::memory_order_acquire))
            {
                return hr;
            }

            const uint64_t owner = reinterpret_cast<uint64_t>(resource);
            const uint32_t dsvFormat = desc ? static_cast<uint32_t>(desc->Format) : 0u;
            const uint32_t dsvDimension = desc ? static_cast<uint32_t>(desc->ViewDimension) : 0u;

            bool tracked = false;
            uint32_t serial = 0;
            {
                std::lock_guard<std::mutex> lock(g_DataMutex);
                RememberDepthView(*view, owner);
                tracked = g_Registry.NoteDepthStencilView(owner, dsvFormat, dsvDimension);
                if (tracked)
                {
                    const Observation* entry = g_Registry.Find(owner);
                    if (entry)
                        serial = entry->serial;
                    g_TableDirty = true;
                }
            }

            if (tracked)
            {
                const char* dsvName = DsvDimensionName(dsvDimension);
                char dsvBuffer[32] = {};
                if (!dsvName)
                {
                    std::snprintf(dsvBuffer, sizeof(dsvBuffer), "dim(%u)", dsvDimension);
                    dsvName = dsvBuffer;
                }
                const char* formatName = FormatName(dsvFormat);
                char formatBuffer[32] = {};
                if (!formatName)
                {
                    std::snprintf(formatBuffer, sizeof(formatBuffer), "format(%u)", dsvFormat);
                    formatName = formatBuffer;
                }

                LogShimA(LogLevel::Info, kComponent,
                    "[SceneDepth] DSV 0x%llX over serial=%u format=%s dimension=%s",
                    static_cast<unsigned long long>(reinterpret_cast<uint64_t>(*view)),
                    serial, formatName, dsvName);
            }

            return hr;
        }

        HRESULT STDMETHODCALLTYPE HookCreateRenderTargetView(
            ID3D11Device* device,
            ID3D11Resource* resource,
            const D3D11_RENDER_TARGET_VIEW_DESC* desc,
            ID3D11RenderTargetView** view)
        {
            const HRESULT hr = g_RealCreateRenderTargetView
                ? g_RealCreateRenderTargetView(device, resource, desc, view)
                : E_FAIL;

            if (FAILED(hr) || !view || !*view
                || g_ShutdownRequested.load(std::memory_order_acquire))
            {
                return hr;
            }

            // Resolved once, here, so that OMSetRenderTargets never has to make
            // a COM call to learn how big the target it is binding is.
            UINT width = 0;
            UINT height = 0;
            if (TryGetTexture2DSize(resource, &width, &height))
            {
                std::lock_guard<std::mutex> lock(g_DataMutex);
                RememberRenderTargetSize(*view, width, height);
            }

            return hr;
        }

        void STDMETHODCALLTYPE HookOMSetRenderTargets(
            ID3D11DeviceContext* context,
            UINT numViews,
            ID3D11RenderTargetView* const* renderTargetViews,
            ID3D11DepthStencilView* depthStencilView)
        {
            if (!g_ShutdownRequested.load(std::memory_order_acquire))
            {
                UINT rtWidth = 0;
                UINT rtHeight = 0;
                ID3D11RenderTargetView* firstTarget =
                    (numViews > 0 && renderTargetViews) ? renderTargetViews[0] : nullptr;

                std::lock_guard<std::mutex> lock(g_DataMutex);

                if (firstTarget)
                    LookupRenderTargetSize(firstTarget, &rtWidth, &rtHeight);

                if (depthStencilView != g_CurrentDepthView)
                {
                    g_CurrentDepthView = depthStencilView;
                    ++g_BindTransitions;
                }

                if (depthStencilView)
                {
                    const uint64_t owner = LookupDepthViewOwner(depthStencilView);
                    if (owner != 0 && g_Registry.NoteBind(owner, rtWidth, rtHeight, numViews))
                        g_TableDirty = true;
                }
            }

            if (g_RealOMSetRenderTargets)
                g_RealOMSetRenderTargets(context, numViews, renderTargetViews, depthStencilView);
        }

        void EnsureContextHook()
        {
            ID3D11DeviceContext* context = g_ImmediateContext;
            if (!context || g_ShutdownRequested.load(std::memory_order_acquire))
                return;

            PatchComVtableEntry(
                context,
                kContextOMSetRenderTargets,
                &HookOMSetRenderTargets,
                g_RealOMSetRenderTargets,
                "ID3D11DeviceContext::OMSetRenderTargets");
        }

        void InstallDeviceHooks(ID3D11Device* device, ID3D11DeviceContext* context)
        {
            if (!device)
                return;

            if (!context)
                device->GetImmediateContext(&context);

            g_ImmediateContext = context;

            unsigned installed = 0;
            installed += PatchComVtableEntry(device, kDeviceCreateTexture2D,
                &HookCreateTexture2D, g_RealCreateTexture2D,
                "ID3D11Device::CreateTexture2D") ? 1u : 0u;
            installed += PatchComVtableEntry(device, kDeviceCreateDepthStencilView,
                &HookCreateDepthStencilView, g_RealCreateDepthStencilView,
                "ID3D11Device::CreateDepthStencilView") ? 1u : 0u;
            installed += PatchComVtableEntry(device, kDeviceCreateRenderTargetView,
                &HookCreateRenderTargetView, g_RealCreateRenderTargetView,
                "ID3D11Device::CreateRenderTargetView") ? 1u : 0u;

            EnsureContextHook();

            LogShimA(installed == 3 ? LogLevel::Info : LogLevel::Warn, kComponent,
                "[SceneDepth] device hooks installed=%u/3 context=%s; observation only, "
                "no resource description is modified",
                installed,
                g_RealOMSetRenderTargets ? "hooked" : "NOT hooked");
        }

        HRESULT WINAPI HookD3D11CreateDevice(
            IDXGIAdapter* adapter, D3D_DRIVER_TYPE driverType, HMODULE software, UINT flags,
            const D3D_FEATURE_LEVEL* featureLevels, UINT featureLevelCount, UINT sdkVersion,
            ID3D11Device** device, D3D_FEATURE_LEVEL* featureLevel, ID3D11DeviceContext** context)
        {
            const HRESULT hr = g_RealD3D11CreateDevice
                ? g_RealD3D11CreateDevice(adapter, driverType, software, flags, featureLevels,
                    featureLevelCount, sdkVersion, device, featureLevel, context)
                : E_FAIL;

            if (SUCCEEDED(hr) && device && *device)
                InstallDeviceHooks(*device, context ? *context : nullptr);

            return hr;
        }

        HRESULT WINAPI HookD3D11CreateDeviceAndSwapChain(
            IDXGIAdapter* adapter, D3D_DRIVER_TYPE driverType, HMODULE software, UINT flags,
            const D3D_FEATURE_LEVEL* featureLevels, UINT featureLevelCount, UINT sdkVersion,
            const DXGI_SWAP_CHAIN_DESC* swapChainDesc, IDXGISwapChain** swapChain,
            ID3D11Device** device, D3D_FEATURE_LEVEL* featureLevel, ID3D11DeviceContext** context)
        {
            const HRESULT hr = g_RealD3D11CreateDeviceAndSwapChain
                ? g_RealD3D11CreateDeviceAndSwapChain(adapter, driverType, software, flags,
                    featureLevels, featureLevelCount, sdkVersion, swapChainDesc, swapChain,
                    device, featureLevel, context)
                : E_FAIL;

            if (SUCCEEDED(hr) && device && *device)
                InstallDeviceHooks(*device, context ? *context : nullptr);

            return hr;
        }

        bool PatchIatFunction(
            HMODULE module, const char* importedDll, const char* functionName,
            void* replacement, void** original)
        {
            if (!module || !importedDll || !functionName || !replacement || !original)
                return false;

            auto* base = reinterpret_cast<unsigned char*>(module);
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return false;

            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return false;

            const IMAGE_DATA_DIRECTORY& imports =
                nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
            if (!imports.VirtualAddress || !imports.Size)
                return false;

            FARPROC targetProc = nullptr;
            if (HMODULE importedModule = GetModuleHandleA(importedDll))
                targetProc = GetProcAddress(importedModule, functionName);

            auto* descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + imports.VirtualAddress);
            for (; descriptor->Name; ++descriptor)
            {
                const char* dllName = reinterpret_cast<const char*>(base + descriptor->Name);
                if (_stricmp(dllName, importedDll) != 0)
                    continue;

                auto* firstThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->FirstThunk);
                IMAGE_THUNK_DATA* nameThunk = descriptor->OriginalFirstThunk
                    ? reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->OriginalFirstThunk)
                    : nullptr;

                for (; firstThunk->u1.Function; ++firstThunk)
                {
                    bool matches = false;
                    if (nameThunk && nameThunk->u1.AddressOfData
                        && !IMAGE_SNAP_BY_ORDINAL(nameThunk->u1.Ordinal))
                    {
                        auto* byName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(
                            base + nameThunk->u1.AddressOfData);
                        matches = std::strcmp(reinterpret_cast<const char*>(byName->Name), functionName) == 0;
                    }

                    if (!matches && targetProc)
                    {
                        matches = reinterpret_cast<FARPROC>(firstThunk->u1.Function) == targetProc;
                    }

                    if (matches)
                    {
                        DWORD oldProtect = 0;
                        if (!VirtualProtect(&firstThunk->u1.Function, sizeof(void*),
                                PAGE_READWRITE, &oldProtect))
                        {
                            return false;
                        }

                        if (!*original)
                            *original = reinterpret_cast<void*>(firstThunk->u1.Function);
                        firstThunk->u1.Function = reinterpret_cast<ULONG_PTR>(replacement);

                        DWORD ignored = 0;
                        VirtualProtect(&firstThunk->u1.Function, sizeof(void*), oldProtect, &ignored);
                        return true;
                    }

                    if (nameThunk)
                        ++nameThunk;
                }
            }

            return false;
        }

        void PatchRendererImports(HMODULE renderer)
        {
            unsigned installed = 0;
            installed += PatchIatFunction(renderer, "d3d11.dll", "D3D11CreateDevice",
                reinterpret_cast<void*>(&HookD3D11CreateDevice),
                reinterpret_cast<void**>(&g_RealD3D11CreateDevice)) ? 1u : 0u;
            installed += PatchIatFunction(renderer, "d3d11.dll", "D3D11CreateDeviceAndSwapChain",
                reinterpret_cast<void*>(&HookD3D11CreateDeviceAndSwapChain),
                reinterpret_cast<void**>(&g_RealD3D11CreateDeviceAndSwapChain)) ? 1u : 0u;

            LogShimA(installed ? LogLevel::Info : LogLevel::Warn, kComponent,
                "[SceneDepth] D3D11 creation hooks installed=%u", installed);
        }

        unsigned __stdcall WorkerProc(void*)
        {
            LogShimA(LogLevel::Info, kComponent,
                "[SceneDepth] Phase A depth qualification requested; waiting for "
                "RenderSystem_Direct3D11.dll (DX9 is never hooked)");

            bool found = false;
            for (unsigned attempt = 0;
                 attempt < kDiscoveryAttempts && !g_ShutdownRequested.load(std::memory_order_acquire);
                 ++attempt)
            {
                if (HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll"))
                {
                    LogShimA(LogLevel::Info, kComponent,
                        "[SceneDepth] Direct3D11 renderer found module=0x%p", renderer);
                    PatchRendererImports(renderer);
                    found = true;
                    break;
                }
                Sleep(kDiscoverySleepMs);
            }

            if (!found)
            {
                if (!g_ShutdownRequested.load(std::memory_order_acquire))
                {
                    LogShimA(LogLevel::Info, kComponent,
                        "[SceneDepth] Direct3D11 renderer not observed; no hooks installed");
                }
                return 0;
            }

            // Periodic table dump. Also the backstop that re-asserts the
            // context hook, which this game is known to revert mid-frame.
            while (!g_ShutdownRequested.load(std::memory_order_acquire))
            {
                for (DWORD waited = 0;
                     waited < kReportIntervalMs && !g_ShutdownRequested.load(std::memory_order_acquire);
                     waited += kDiscoverySleepMs)
                {
                    Sleep(kDiscoverySleepMs);
                }

                if (g_ShutdownRequested.load(std::memory_order_acquire))
                    break;

                EnsureContextHook();
                ReportTable();
            }

            return 0;
        }
    }

    void InitializeDx11SceneDepth()
    {
        if (!DiagnosticRequested() || g_Worker)
            return;

        g_Enabled.store(true, std::memory_order_release);
        g_ShutdownRequested.store(false, std::memory_order_release);
        g_Worker = _beginthreadex(nullptr, 0, WorkerProc, nullptr, 0, nullptr);

        if (!g_Worker)
        {
            g_Enabled.store(false, std::memory_order_release);
            LogShimA(LogLevel::Warn, kComponent,
                "[SceneDepth] failed to start discovery thread (err=%lu); diagnostic disabled",
                GetLastError());
        }
    }

    void ShutdownDx11SceneDepth()
    {
        if (!g_Enabled.load(std::memory_order_acquire))
            return;

        // The final table is the one worth having: it covers the whole session
        // rather than whatever the last 15-second tick happened to catch.
        {
            std::lock_guard<std::mutex> lock(g_DataMutex);
            g_TableDirty = true;
        }
        ReportTable();

        g_ShutdownRequested.store(true, std::memory_order_release);

        if (g_Worker)
        {
            WaitForSingleObject(reinterpret_cast<HANDLE>(g_Worker), 2000);
            CloseHandle(reinterpret_cast<HANDLE>(g_Worker));
            g_Worker = 0;
        }

        g_Enabled.store(false, std::memory_order_release);
    }
}
