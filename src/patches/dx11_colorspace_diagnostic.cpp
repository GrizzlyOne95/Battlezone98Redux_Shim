#include "dx11_colorspace_diagnostic.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <d3d11.h>
#include <dxgi1_4.h>
#include <process.h>

#include <algorithm>
#include <atomic>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_set>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "dx11-colorspace";
        constexpr char kEnvironmentSwitch[] = "OPENSHIM_TRACE_DX11_COLORSPACE";
        constexpr char kIniSection[] = "Diagnostics";
        constexpr char kIniKey[] = "TraceDX11ColorSpace";
        constexpr unsigned kDiscoveryAttempts = 1200; // 30 seconds at 25 ms.
        constexpr DWORD kDiscoverySleepMs = 25;

        constexpr size_t kMaxTextureCreateLogs = 384;
        constexpr size_t kMaxSrvCreateLogs = 512;
        constexpr size_t kMaxSrvBindingLogs = 768;
        constexpr size_t kMaxRenderTargetLogs = 256;
        constexpr size_t kMaxViewportLogs = 32;

        // WKPDID_D3DDebugObjectName, kept local to avoid a dxguid.lib dependency.
        constexpr GUID kD3DDebugObjectName =
            { 0x429b8c22, 0x9188, 0x4b0c, { 0x87, 0x42, 0xac, 0xb0, 0xbf, 0x85, 0xc2, 0x00 } };

        std::atomic<bool> g_ShutdownRequested{ false };
        std::atomic<uintptr_t> g_BackbufferIdentity{ 0 };
        uintptr_t g_DiscoveryThread = 0;

        std::mutex g_HookMutex;
        std::mutex g_LogSetMutex;

        std::unordered_set<uint64_t> g_TextureCreateKeys;
        std::unordered_set<uint64_t> g_SrvCreateKeys;
        std::unordered_set<uint64_t> g_SrvBindingKeys;
        std::unordered_set<uint64_t> g_RenderTargetKeys;
        std::unordered_set<uint64_t> g_ViewportKeys;

        bool g_TextureCreateLimitLogged = false;
        bool g_SrvCreateLimitLogged = false;
        bool g_SrvBindingLimitLogged = false;
        bool g_RenderTargetLimitLogged = false;
        bool g_ViewportLimitLogged = false;

        using FnD3D11CreateDevice = HRESULT(WINAPI*)(
            IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
            const D3D_FEATURE_LEVEL*, UINT, UINT,
            ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);

        using FnD3D11CreateDeviceAndSwapChain = HRESULT(WINAPI*)(
            IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
            const D3D_FEATURE_LEVEL*, UINT, UINT,
            const DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**,
            ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);

        using FnFactoryCreateSwapChain = HRESULT(STDMETHODCALLTYPE*)(
            IDXGIFactory*, IUnknown*, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**);

        using FnSwapChainResizeBuffers = HRESULT(STDMETHODCALLTYPE*)(
            IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

        using FnSwapChainSetColorSpace1 = HRESULT(STDMETHODCALLTYPE*)(
            IDXGISwapChain3*, DXGI_COLOR_SPACE_TYPE);

        using FnDeviceCreateTexture2D = HRESULT(STDMETHODCALLTYPE*)(
            ID3D11Device*, const D3D11_TEXTURE2D_DESC*,
            const D3D11_SUBRESOURCE_DATA*, ID3D11Texture2D**);

        using FnDeviceCreateSRV = HRESULT(STDMETHODCALLTYPE*)(
            ID3D11Device*, ID3D11Resource*, const D3D11_SHADER_RESOURCE_VIEW_DESC*,
            ID3D11ShaderResourceView**);

        using FnDeviceCreateRTV = HRESULT(STDMETHODCALLTYPE*)(
            ID3D11Device*, ID3D11Resource*, const D3D11_RENDER_TARGET_VIEW_DESC*,
            ID3D11RenderTargetView**);

        using FnDeviceCreateDSV = HRESULT(STDMETHODCALLTYPE*)(
            ID3D11Device*, ID3D11Resource*, const D3D11_DEPTH_STENCIL_VIEW_DESC*,
            ID3D11DepthStencilView**);

        using FnContextPSSetShaderResources = void(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, UINT, UINT, ID3D11ShaderResourceView* const*);

        using FnContextOMSetRenderTargets = void(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, UINT, ID3D11RenderTargetView* const*, ID3D11DepthStencilView*);

        FnD3D11CreateDevice g_RealD3D11CreateDevice = nullptr;
        FnD3D11CreateDeviceAndSwapChain g_RealD3D11CreateDeviceAndSwapChain = nullptr;
        FnFactoryCreateSwapChain g_RealFactoryCreateSwapChain = nullptr;
        FnSwapChainResizeBuffers g_RealResizeBuffers = nullptr;
        FnSwapChainSetColorSpace1 g_RealSetColorSpace1 = nullptr;
        FnDeviceCreateTexture2D g_RealCreateTexture2D = nullptr;
        FnDeviceCreateSRV g_RealCreateSRV = nullptr;
        FnDeviceCreateRTV g_RealCreateRTV = nullptr;
        FnDeviceCreateDSV g_RealCreateDSV = nullptr;
        FnContextPSSetShaderResources g_RealPSSetShaderResources = nullptr;
        FnContextOMSetRenderTargets g_RealOMSetRenderTargets = nullptr;

        uint64_t MixKey(uint64_t seed, uint64_t value)
        {
            seed ^= value + 0x9e3779b97f4a7c15ull + (seed << 6) + (seed >> 2);
            return seed;
        }

        uint64_t PointerKey(const void* p)
        {
            return static_cast<uint64_t>(reinterpret_cast<uintptr_t>(p));
        }

        uintptr_t ComIdentity(IUnknown* object)
        {
            if (!object)
                return 0;

            IUnknown* identity = nullptr;
            if (FAILED(object->QueryInterface(__uuidof(IUnknown), reinterpret_cast<void**>(&identity))) || !identity)
                return 0;

            const uintptr_t value = reinterpret_cast<uintptr_t>(identity);
            identity->Release();
            return value;
        }

        bool InsertBounded(
            std::unordered_set<uint64_t>& set,
            uint64_t key,
            size_t limit,
            bool& limitLogged,
            const char* label)
        {
            std::lock_guard<std::mutex> lock(g_LogSetMutex);
            if (set.find(key) != set.end())
                return false;

            if (set.size() >= limit)
            {
                if (!limitLogged)
                {
                    limitLogged = true;
                    LogShimA(
                        LogLevel::Warn,
                        kComponent,
                        "[DX11 ColorSpace] %s log limit reached (%u unique records); further records suppressed",
                        label,
                        static_cast<unsigned>(limit));
                }
                return false;
            }

            set.insert(key);
            return true;
        }

        bool StringIsTruthy(const char* value)
        {
            if (!value || !*value)
                return false;

            std::string v(value);
            std::transform(
                v.begin(), v.end(), v.begin(),
                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

            return v != "0" && v != "false" && v != "no" && v != "off";
        }

        std::string GetOpenShimIniPath()
        {
            char path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return "openshim.ini";

            char* slash = std::strrchr(path, '\\');
            if (slash)
                *(slash + 1) = '\0';
            else
                path[0] = '\0';

            return std::string(path) + "openshim.ini";
        }

        bool DiagnosticRequested()
        {
            char envValue[64] = {};
            const DWORD envLength = GetEnvironmentVariableA(
                kEnvironmentSwitch,
                envValue,
                static_cast<DWORD>(sizeof(envValue)));

            if (envLength > 0 && envLength < sizeof(envValue))
                return StringIsTruthy(envValue);

            const std::string iniPath = GetOpenShimIniPath();
            return GetPrivateProfileIntA(kIniSection, kIniKey, 0, iniPath.c_str()) != 0;
        }

        const char* DxgiFormatName(DXGI_FORMAT format)
        {
            switch (format)
            {
            case DXGI_FORMAT_UNKNOWN: return "DXGI_FORMAT_UNKNOWN";
            case DXGI_FORMAT_R32G32B32A32_TYPELESS: return "DXGI_FORMAT_R32G32B32A32_TYPELESS";
            case DXGI_FORMAT_R32G32B32A32_FLOAT: return "DXGI_FORMAT_R32G32B32A32_FLOAT";
            case DXGI_FORMAT_R16G16B16A16_TYPELESS: return "DXGI_FORMAT_R16G16B16A16_TYPELESS";
            case DXGI_FORMAT_R16G16B16A16_FLOAT: return "DXGI_FORMAT_R16G16B16A16_FLOAT";
            case DXGI_FORMAT_R16G16B16A16_UNORM: return "DXGI_FORMAT_R16G16B16A16_UNORM";
            case DXGI_FORMAT_R32G32_TYPELESS: return "DXGI_FORMAT_R32G32_TYPELESS";
            case DXGI_FORMAT_R32G32_FLOAT: return "DXGI_FORMAT_R32G32_FLOAT";
            case DXGI_FORMAT_R10G10B10A2_TYPELESS: return "DXGI_FORMAT_R10G10B10A2_TYPELESS";
            case DXGI_FORMAT_R10G10B10A2_UNORM: return "DXGI_FORMAT_R10G10B10A2_UNORM";
            case DXGI_FORMAT_R11G11B10_FLOAT: return "DXGI_FORMAT_R11G11B10_FLOAT";
            case DXGI_FORMAT_R8G8B8A8_TYPELESS: return "DXGI_FORMAT_R8G8B8A8_TYPELESS";
            case DXGI_FORMAT_R8G8B8A8_UNORM: return "DXGI_FORMAT_R8G8B8A8_UNORM";
            case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB: return "DXGI_FORMAT_R8G8B8A8_UNORM_SRGB";
            case DXGI_FORMAT_R16G16_TYPELESS: return "DXGI_FORMAT_R16G16_TYPELESS";
            case DXGI_FORMAT_R16G16_FLOAT: return "DXGI_FORMAT_R16G16_FLOAT";
            case DXGI_FORMAT_R16G16_UNORM: return "DXGI_FORMAT_R16G16_UNORM";
            case DXGI_FORMAT_R32_TYPELESS: return "DXGI_FORMAT_R32_TYPELESS";
            case DXGI_FORMAT_D32_FLOAT: return "DXGI_FORMAT_D32_FLOAT";
            case DXGI_FORMAT_R32_FLOAT: return "DXGI_FORMAT_R32_FLOAT";
            case DXGI_FORMAT_R24G8_TYPELESS: return "DXGI_FORMAT_R24G8_TYPELESS";
            case DXGI_FORMAT_D24_UNORM_S8_UINT: return "DXGI_FORMAT_D24_UNORM_S8_UINT";
            case DXGI_FORMAT_R24_UNORM_X8_TYPELESS: return "DXGI_FORMAT_R24_UNORM_X8_TYPELESS";
            case DXGI_FORMAT_R8G8_TYPELESS: return "DXGI_FORMAT_R8G8_TYPELESS";
            case DXGI_FORMAT_R8G8_UNORM: return "DXGI_FORMAT_R8G8_UNORM";
            case DXGI_FORMAT_R16_TYPELESS: return "DXGI_FORMAT_R16_TYPELESS";
            case DXGI_FORMAT_R16_FLOAT: return "DXGI_FORMAT_R16_FLOAT";
            case DXGI_FORMAT_D16_UNORM: return "DXGI_FORMAT_D16_UNORM";
            case DXGI_FORMAT_R16_UNORM: return "DXGI_FORMAT_R16_UNORM";
            case DXGI_FORMAT_R8_TYPELESS: return "DXGI_FORMAT_R8_TYPELESS";
            case DXGI_FORMAT_R8_UNORM: return "DXGI_FORMAT_R8_UNORM";
            case DXGI_FORMAT_BC1_TYPELESS: return "DXGI_FORMAT_BC1_TYPELESS";
            case DXGI_FORMAT_BC1_UNORM: return "DXGI_FORMAT_BC1_UNORM";
            case DXGI_FORMAT_BC1_UNORM_SRGB: return "DXGI_FORMAT_BC1_UNORM_SRGB";
            case DXGI_FORMAT_BC2_TYPELESS: return "DXGI_FORMAT_BC2_TYPELESS";
            case DXGI_FORMAT_BC2_UNORM: return "DXGI_FORMAT_BC2_UNORM";
            case DXGI_FORMAT_BC2_UNORM_SRGB: return "DXGI_FORMAT_BC2_UNORM_SRGB";
            case DXGI_FORMAT_BC3_TYPELESS: return "DXGI_FORMAT_BC3_TYPELESS";
            case DXGI_FORMAT_BC3_UNORM: return "DXGI_FORMAT_BC3_UNORM";
            case DXGI_FORMAT_BC3_UNORM_SRGB: return "DXGI_FORMAT_BC3_UNORM_SRGB";
            case DXGI_FORMAT_BC4_TYPELESS: return "DXGI_FORMAT_BC4_TYPELESS";
            case DXGI_FORMAT_BC4_UNORM: return "DXGI_FORMAT_BC4_UNORM";
            case DXGI_FORMAT_BC5_TYPELESS: return "DXGI_FORMAT_BC5_TYPELESS";
            case DXGI_FORMAT_BC5_UNORM: return "DXGI_FORMAT_BC5_UNORM";
            case DXGI_FORMAT_B8G8R8A8_UNORM: return "DXGI_FORMAT_B8G8R8A8_UNORM";
            case DXGI_FORMAT_B8G8R8X8_UNORM: return "DXGI_FORMAT_B8G8R8X8_UNORM";
            case DXGI_FORMAT_B8G8R8A8_TYPELESS: return "DXGI_FORMAT_B8G8R8A8_TYPELESS";
            case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB: return "DXGI_FORMAT_B8G8R8A8_UNORM_SRGB";
            case DXGI_FORMAT_B8G8R8X8_TYPELESS: return "DXGI_FORMAT_B8G8R8X8_TYPELESS";
            case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB: return "DXGI_FORMAT_B8G8R8X8_UNORM_SRGB";
            case DXGI_FORMAT_BC6H_TYPELESS: return "DXGI_FORMAT_BC6H_TYPELESS";
            case DXGI_FORMAT_BC6H_UF16: return "DXGI_FORMAT_BC6H_UF16";
            case DXGI_FORMAT_BC7_TYPELESS: return "DXGI_FORMAT_BC7_TYPELESS";
            case DXGI_FORMAT_BC7_UNORM: return "DXGI_FORMAT_BC7_UNORM";
            case DXGI_FORMAT_BC7_UNORM_SRGB: return "DXGI_FORMAT_BC7_UNORM_SRGB";
            default: return "DXGI_FORMAT_(other)";
            }
        }

        bool IsSrgbFormat(DXGI_FORMAT format)
        {
            switch (format)
            {
            case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
            case DXGI_FORMAT_BC1_UNORM_SRGB:
            case DXGI_FORMAT_BC2_UNORM_SRGB:
            case DXGI_FORMAT_BC3_UNORM_SRGB:
            case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
            case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
            case DXGI_FORMAT_BC7_UNORM_SRGB:
                return true;
            default:
                return false;
            }
        }

        bool IsTypelessFormat(DXGI_FORMAT format)
        {
            switch (format)
            {
            case DXGI_FORMAT_R32G32B32A32_TYPELESS:
            case DXGI_FORMAT_R16G16B16A16_TYPELESS:
            case DXGI_FORMAT_R32G32_TYPELESS:
            case DXGI_FORMAT_R10G10B10A2_TYPELESS:
            case DXGI_FORMAT_R8G8B8A8_TYPELESS:
            case DXGI_FORMAT_R16G16_TYPELESS:
            case DXGI_FORMAT_R32_TYPELESS:
            case DXGI_FORMAT_R24G8_TYPELESS:
            case DXGI_FORMAT_R8G8_TYPELESS:
            case DXGI_FORMAT_R16_TYPELESS:
            case DXGI_FORMAT_R8_TYPELESS:
            case DXGI_FORMAT_BC1_TYPELESS:
            case DXGI_FORMAT_BC2_TYPELESS:
            case DXGI_FORMAT_BC3_TYPELESS:
            case DXGI_FORMAT_BC4_TYPELESS:
            case DXGI_FORMAT_BC5_TYPELESS:
            case DXGI_FORMAT_B8G8R8A8_TYPELESS:
            case DXGI_FORMAT_B8G8R8X8_TYPELESS:
            case DXGI_FORMAT_BC6H_TYPELESS:
            case DXGI_FORMAT_BC7_TYPELESS:
                return true;
            default:
                return false;
            }
        }

        bool IsFloatFormat(DXGI_FORMAT format)
        {
            switch (format)
            {
            case DXGI_FORMAT_R32G32B32A32_FLOAT:
            case DXGI_FORMAT_R16G16B16A16_FLOAT:
            case DXGI_FORMAT_R32G32_FLOAT:
            case DXGI_FORMAT_R11G11B10_FLOAT:
            case DXGI_FORMAT_R16G16_FLOAT:
            case DXGI_FORMAT_R32_FLOAT:
            case DXGI_FORMAT_R16_FLOAT:
            case DXGI_FORMAT_BC6H_UF16:
                return true;
            default:
                return false;
            }
        }

        const char* ColorSpaceName(DXGI_COLOR_SPACE_TYPE colorSpace)
        {
            switch (colorSpace)
            {
            case DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709:
                return "DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709";
            case DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709:
                return "DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709";
            case DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709:
                return "DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709";
            case DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020:
                return "DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020";
            default:
                return "DXGI_COLOR_SPACE_(other)";
            }
        }

        std::string GetDebugName(ID3D11DeviceChild* child)
        {
            if (!child)
                return {};

            UINT length = 0;
            if (FAILED(child->GetPrivateData(kD3DDebugObjectName, &length, nullptr)) ||
                length == 0 || length > 1024)
            {
                return {};
            }

            std::vector<char> buffer(length + 1, '\0');
            if (FAILED(child->GetPrivateData(kD3DDebugObjectName, &length, buffer.data())))
                return {};

            buffer.back() = '\0';
            return std::string(buffer.data());
        }

        std::string LowerCopy(std::string value)
        {
            std::transform(
                value.begin(), value.end(), value.begin(),
                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            return value;
        }

        const char* KnownResourceSemantic(const std::string& debugName)
        {
            const std::string lower = LowerCopy(debugName);

            if (lower.find("cr_ibl_neutral_irradiance") != std::string::npos)
                return "CR static irradiance cubemap (generated linear numeric data)";
            if (lower.find("cr_ibl_neutral_prefilter") != std::string::npos)
                return "CR static prefiltered environment cubemap (generated linear numeric data)";
            if (lower.find("cr_ibl_brdf_lut") != std::string::npos)
                return "CR BRDF LUT (linear data)";
            if (lower.find("flat_n") != std::string::npos)
                return "normal-map fallback (linear data)";

            return nullptr;
        }

        const char* CrPixelSlotHint(UINT slot, bool cube)
        {
            if (cube)
                return "CR Enhanced IBL cube candidate; exact irradiance/prefilter role is variant-dependent";

            switch (slot)
            {
            case 0: return "CR base + terrain diffuse/albedo slot (COLOR candidate)";
            case 1: return "CR base normal OR terrain detail slot (variant-dependent)";
            case 2: return "CR base specular OR terrain normal slot (variant-dependent)";
            case 3: return "CR base emissive OR terrain specular slot (variant-dependent)";
            case 4: return "CR terrain emissive OR base shadow/IBL slot (variant-dependent)";
            case 5: return "CR shadow/IBL slot (variant-dependent)";
            case 6: return "CR shadow/IBL slot (variant-dependent)";
            case 7: return "CR shadow/IBL slot (variant-dependent)";
            case 8: return "CR IBL slot in PSSM/terrain variants";
            case 9: return "CR IBL slot in PSSM variants";
            case 10: return "CR terrain PSSM BRDF-LUT slot";
            default: return "non-CR-core or auxiliary pixel-shader slot";
            }
        }

        bool GetTexture2DDesc(ID3D11Resource* resource, D3D11_TEXTURE2D_DESC& outDesc)
        {
            if (!resource)
                return false;

            ID3D11Texture2D* texture = nullptr;
            if (FAILED(resource->QueryInterface(
                    __uuidof(ID3D11Texture2D),
                    reinterpret_cast<void**>(&texture))) ||
                !texture)
            {
                return false;
            }

            texture->GetDesc(&outDesc);
            texture->Release();
            return true;
        }

        void LogTextureCreated(ID3D11Texture2D* texture, const D3D11_TEXTURE2D_DESC& desc)
        {
            const std::string debugName = GetDebugName(texture);
            const char* semantic = KnownResourceSemantic(debugName);
            const std::string semanticSuffix = semantic
                ? std::string(" semantic=\"") + semantic + "\""
                : std::string();

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[DX11 ColorSpace] Texture2D create resource=0x%p name=%s size=%ux%u array=%u mips=%u format=%s(%u) srgb=%s typeless=%s bind=0x%08X misc=0x%08X%s",
                texture,
                debugName.empty() ? "<not-set>" : debugName.c_str(),
                desc.Width,
                desc.Height,
                desc.ArraySize,
                desc.MipLevels,
                DxgiFormatName(desc.Format),
                static_cast<unsigned>(desc.Format),
                IsSrgbFormat(desc.Format) ? "yes" : "no",
                IsTypelessFormat(desc.Format) ? "yes" : "no",
                desc.BindFlags,
                desc.MiscFlags,
                semanticSuffix.c_str());
        }

        void LogCurrentViewports(ID3D11DeviceContext* context, const char* trigger)
        {
            if (!context)
                return;

            UINT count = 0;
            context->RSGetViewports(&count, nullptr);
            if (count == 0 || count > D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)
                return;

            std::vector<D3D11_VIEWPORT> viewports(count);
            UINT requested = count;
            context->RSGetViewports(&requested, viewports.data());

            for (UINT i = 0; i < requested; ++i)
            {
                const D3D11_VIEWPORT& vp = viewports[i];
                uint64_t key = 0x565057ull;
                const uint32_t* words = reinterpret_cast<const uint32_t*>(&vp);
                for (size_t word = 0; word < sizeof(D3D11_VIEWPORT) / sizeof(uint32_t); ++word)
                    key = MixKey(key, words[word]);

                if (!InsertBounded(
                        g_ViewportKeys,
                        key,
                        kMaxViewportLogs,
                        g_ViewportLimitLogged,
                        "viewport"))
                {
                    continue;
                }

                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[DX11 ColorSpace] Active D3D11 viewport[%u] trigger=%s x=%.1f y=%.1f width=%.1f height=%.1f minDepth=%.3f maxDepth=%.3f",
                    i,
                    trigger,
                    vp.TopLeftX,
                    vp.TopLeftY,
                    vp.Width,
                    vp.Height,
                    vp.MinDepth,
                    vp.MaxDepth);
            }
        }

        void LogSrvRecord(UINT slot, ID3D11ShaderResourceView* srv, bool binding)
        {
            if (!srv)
                return;

            D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
            srv->GetDesc(&srvDesc);

            ID3D11Resource* resource = nullptr;
            srv->GetResource(&resource);
            if (!resource)
                return;

            D3D11_TEXTURE2D_DESC texDesc = {};
            const bool isTexture2D = GetTexture2DDesc(resource, texDesc);
            const bool cube =
                srvDesc.ViewDimension == D3D11_SRV_DIMENSION_TEXTURECUBE ||
                srvDesc.ViewDimension == D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;

            uint64_t key = MixKey(PointerKey(srv), PointerKey(resource));
            key = MixKey(key, static_cast<uint64_t>(srvDesc.Format));
            if (binding)
                key = MixKey(key, 0xB1000000ull | slot);

            const bool shouldLog = binding
                ? InsertBounded(
                    g_SrvBindingKeys,
                    key,
                    kMaxSrvBindingLogs,
                    g_SrvBindingLimitLogged,
                    "SRV binding")
                : InsertBounded(
                    g_SrvCreateKeys,
                    key,
                    kMaxSrvCreateLogs,
                    g_SrvCreateLimitLogged,
                    "SRV creation");

            if (!shouldLog)
            {
                resource->Release();
                return;
            }

            const std::string srvName = GetDebugName(srv);
            const std::string resourceName = GetDebugName(resource);
            const char* knownSemantic = KnownResourceSemantic(
                !resourceName.empty() ? resourceName : srvName);

            const char* hint = knownSemantic
                ? knownSemantic
                : (binding
                    ? CrPixelSlotHint(slot, cube)
                    : "role unresolved until SRV is bound to a shader slot");

            if (isTexture2D)
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[DX11 ColorSpace] %s%s srv=0x%p srvName=%s resource=0x%p resourceName=%s resourceFormat=%s(%u) srvFormat=%s(%u) resourceSRGB=%s srvSRGB=%s resourceTypeless=%s size=%ux%u array=%u mips=%u cube=%s hint=\"%s\"",
                    binding ? "PS bind " : "SRV create ",
                    binding ? (std::string("t") + std::to_string(slot)).c_str() : "",
                    srv,
                    srvName.empty() ? "<not-set>" : srvName.c_str(),
                    resource,
                    resourceName.empty() ? "<not-set>" : resourceName.c_str(),
                    DxgiFormatName(texDesc.Format),
                    static_cast<unsigned>(texDesc.Format),
                    DxgiFormatName(srvDesc.Format),
                    static_cast<unsigned>(srvDesc.Format),
                    IsSrgbFormat(texDesc.Format) ? "yes" : "no",
                    IsSrgbFormat(srvDesc.Format) ? "yes" : "no",
                    IsTypelessFormat(texDesc.Format) ? "yes" : "no",
                    texDesc.Width,
                    texDesc.Height,
                    texDesc.ArraySize,
                    texDesc.MipLevels,
                    cube ? "yes" : "no",
                    hint);
            }
            else
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[DX11 ColorSpace] %s srv=0x%p resource=0x%p non-Texture2D srvFormat=%s(%u)",
                    binding ? "PS bind" : "SRV create",
                    srv,
                    resource,
                    DxgiFormatName(srvDesc.Format),
                    static_cast<unsigned>(srvDesc.Format));
            }

            resource->Release();
        }

        void LogRenderTargetView(ID3D11RenderTargetView* rtv, UINT slot, const char* trigger)
        {
            if (!rtv)
                return;

            D3D11_RENDER_TARGET_VIEW_DESC viewDesc = {};
            rtv->GetDesc(&viewDesc);

            ID3D11Resource* resource = nullptr;
            rtv->GetResource(&resource);
            if (!resource)
                return;

            D3D11_TEXTURE2D_DESC texDesc = {};
            if (!GetTexture2DDesc(resource, texDesc))
            {
                resource->Release();
                return;
            }

            uint64_t key = MixKey(PointerKey(resource), PointerKey(rtv));
            key = MixKey(key, static_cast<uint64_t>(viewDesc.Format));
            key = MixKey(key, slot);

            if (!InsertBounded(
                    g_RenderTargetKeys,
                    key,
                    kMaxRenderTargetLogs,
                    g_RenderTargetLimitLogged,
                    "render-target"))
            {
                resource->Release();
                return;
            }

            const bool backbuffer =
                ComIdentity(resource) == g_BackbufferIdentity.load(std::memory_order_acquire);

            const std::string rtvName = GetDebugName(rtv);
            const std::string resourceName = GetDebugName(resource);

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[DX11 ColorSpace] RTV %s slot=%u rtv=0x%p rtvName=%s resource=0x%p resourceName=%s backbuffer=%s resourceFormat=%s(%u) rtvFormat=%s(%u) resourceSRGB=%s rtvSRGB=%s typeless=%s floatTarget=%s size=%ux%u samples=%u",
                trigger,
                slot,
                rtv,
                rtvName.empty() ? "<not-set>" : rtvName.c_str(),
                resource,
                resourceName.empty() ? "<not-set>" : resourceName.c_str(),
                backbuffer ? "yes" : "no",
                DxgiFormatName(texDesc.Format),
                static_cast<unsigned>(texDesc.Format),
                DxgiFormatName(viewDesc.Format),
                static_cast<unsigned>(viewDesc.Format),
                IsSrgbFormat(texDesc.Format) ? "yes" : "no",
                IsSrgbFormat(viewDesc.Format) ? "yes" : "no",
                IsTypelessFormat(texDesc.Format) ? "yes" : "no",
                (IsFloatFormat(texDesc.Format) || IsFloatFormat(viewDesc.Format)) ? "yes" : "no",
                texDesc.Width,
                texDesc.Height,
                texDesc.SampleDesc.Count);

            if (backbuffer)
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[DX11 ColorSpace] Effective backbuffer write conversion: rtvSRGB=%s (Ogre RenderWindow mHwGamma is not read through guessed object offsets)",
                    IsSrgbFormat(viewDesc.Format) ? "yes" : "no");
            }

            resource->Release();
        }

        void LogDepthStencilView(ID3D11DepthStencilView* dsv, const char* trigger)
        {
            if (!dsv)
                return;

            D3D11_DEPTH_STENCIL_VIEW_DESC viewDesc = {};
            dsv->GetDesc(&viewDesc);

            ID3D11Resource* resource = nullptr;
            dsv->GetResource(&resource);
            if (!resource)
                return;

            D3D11_TEXTURE2D_DESC texDesc = {};
            if (GetTexture2DDesc(resource, texDesc))
            {
                uint64_t key = MixKey(PointerKey(resource), PointerKey(dsv));
                key = MixKey(key, 0xD5000000ull | static_cast<uint64_t>(viewDesc.Format));

                if (InsertBounded(
                        g_RenderTargetKeys,
                        key,
                        kMaxRenderTargetLogs,
                        g_RenderTargetLimitLogged,
                        "render-target"))
                {
                    LogShimA(
                        LogLevel::Info,
                        kComponent,
                        "[DX11 ColorSpace] DSV %s dsv=0x%p resource=0x%p resourceFormat=%s(%u) dsvFormat=%s(%u) typelessResource=%s size=%ux%u samples=%u DATA=yes",
                        trigger,
                        dsv,
                        resource,
                        DxgiFormatName(texDesc.Format),
                        static_cast<unsigned>(texDesc.Format),
                        DxgiFormatName(viewDesc.Format),
                        static_cast<unsigned>(viewDesc.Format),
                        IsTypelessFormat(texDesc.Format) ? "yes" : "no",
                        texDesc.Width,
                        texDesc.Height,
                        texDesc.SampleDesc.Count);
                }
            }

            resource->Release();
        }

        template <typename T>
        bool PatchComVtableEntry(
            void* object,
            size_t index,
            T hook,
            T& original,
            const char* label)
        {
            if (!object)
                return false;

            std::lock_guard<std::mutex> lock(g_HookMutex);

            void*** objectVtable = reinterpret_cast<void***>(object);
            if (!objectVtable || !*objectVtable)
                return false;

            void** vtable = *objectVtable;
            void* current = vtable[index];

            if (current == reinterpret_cast<void*>(hook))
                return true;

            if (original && current != reinterpret_cast<void*>(original))
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[DX11 ColorSpace] %s vtable differs from already-hooked implementation; leaving it untouched",
                    label);
                return false;
            }

            DWORD oldProtect = 0;
            if (!VirtualProtect(
                    &vtable[index],
                    sizeof(void*),
                    PAGE_EXECUTE_READWRITE,
                    &oldProtect))
            {
                return false;
            }

            if (!original)
                original = reinterpret_cast<T>(current);

            vtable[index] = reinterpret_cast<void*>(hook);

            DWORD ignored = 0;
            VirtualProtect(&vtable[index], sizeof(void*), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), &vtable[index], sizeof(void*));

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[DX11 ColorSpace] installed %s observer (vtable[%u])",
                label,
                static_cast<unsigned>(index));
            return true;
        }

        void InstallContextHooks(ID3D11DeviceContext* context);
        void InstallDeviceHooks(ID3D11Device* device);
        void InstallFactoryHooks(IDXGIFactory* factory);
        void CaptureSwapChain(IDXGISwapChain* swapChain, const char* source);

        HRESULT STDMETHODCALLTYPE HookCreateTexture2D(
            ID3D11Device* self,
            const D3D11_TEXTURE2D_DESC* desc,
            const D3D11_SUBRESOURCE_DATA* initialData,
            ID3D11Texture2D** texture)
        {
            const HRESULT hr = g_RealCreateTexture2D(self, desc, initialData, texture);

            if (SUCCEEDED(hr) && texture && *texture && desc)
            {
                uint64_t key = MixKey(
                    PointerKey(*texture),
                    static_cast<uint64_t>(desc->Format));

                if (InsertBounded(
                        g_TextureCreateKeys,
                        key,
                        kMaxTextureCreateLogs,
                        g_TextureCreateLimitLogged,
                        "Texture2D creation"))
                {
                    LogTextureCreated(*texture, *desc);
                }
            }

            return hr;
        }

        HRESULT STDMETHODCALLTYPE HookCreateSRV(
            ID3D11Device* self,
            ID3D11Resource* resource,
            const D3D11_SHADER_RESOURCE_VIEW_DESC* desc,
            ID3D11ShaderResourceView** srv)
        {
            const HRESULT hr = g_RealCreateSRV(self, resource, desc, srv);
            if (SUCCEEDED(hr) && srv && *srv)
                LogSrvRecord(0, *srv, false);
            return hr;
        }

        HRESULT STDMETHODCALLTYPE HookCreateRTV(
            ID3D11Device* self,
            ID3D11Resource* resource,
            const D3D11_RENDER_TARGET_VIEW_DESC* desc,
            ID3D11RenderTargetView** rtv)
        {
            const HRESULT hr = g_RealCreateRTV(self, resource, desc, rtv);
            if (SUCCEEDED(hr) && rtv && *rtv)
                LogRenderTargetView(*rtv, 0, "create");
            return hr;
        }

        HRESULT STDMETHODCALLTYPE HookCreateDSV(
            ID3D11Device* self,
            ID3D11Resource* resource,
            const D3D11_DEPTH_STENCIL_VIEW_DESC* desc,
            ID3D11DepthStencilView** dsv)
        {
            const HRESULT hr = g_RealCreateDSV(self, resource, desc, dsv);
            if (SUCCEEDED(hr) && dsv && *dsv)
                LogDepthStencilView(*dsv, "create");
            return hr;
        }

        void STDMETHODCALLTYPE HookPSSetShaderResources(
            ID3D11DeviceContext* self,
            UINT startSlot,
            UINT numViews,
            ID3D11ShaderResourceView* const* views)
        {
            g_RealPSSetShaderResources(self, startSlot, numViews, views);

            if (!views)
                return;

            for (UINT i = 0; i < numViews; ++i)
                LogSrvRecord(startSlot + i, views[i], true);
        }

        void STDMETHODCALLTYPE HookOMSetRenderTargets(
            ID3D11DeviceContext* self,
            UINT numViews,
            ID3D11RenderTargetView* const* views,
            ID3D11DepthStencilView* dsv)
        {
            g_RealOMSetRenderTargets(self, numViews, views, dsv);

            if (views)
            {
                for (UINT i = 0; i < numViews; ++i)
                    LogRenderTargetView(views[i], i, "bind");
            }

            LogDepthStencilView(dsv, "bind");
            LogCurrentViewports(self, "OMSetRenderTargets");
        }

        HRESULT STDMETHODCALLTYPE HookFactoryCreateSwapChain(
            IDXGIFactory* self,
            IUnknown* device,
            DXGI_SWAP_CHAIN_DESC* desc,
            IDXGISwapChain** swapChain)
        {
            const HRESULT hr = g_RealFactoryCreateSwapChain(self, device, desc, swapChain);

            if (SUCCEEDED(hr))
            {
                ID3D11Device* d3dDevice = nullptr;
                if (device &&
                    SUCCEEDED(device->QueryInterface(
                        __uuidof(ID3D11Device),
                        reinterpret_cast<void**>(&d3dDevice))) &&
                    d3dDevice)
                {
                    InstallDeviceHooks(d3dDevice);
                    d3dDevice->Release();
                }

                if (swapChain && *swapChain)
                    CaptureSwapChain(*swapChain, "IDXGIFactory::CreateSwapChain");
            }

            return hr;
        }

        HRESULT STDMETHODCALLTYPE HookResizeBuffers(
            IDXGISwapChain* self,
            UINT bufferCount,
            UINT width,
            UINT height,
            DXGI_FORMAT newFormat,
            UINT swapChainFlags)
        {
            const HRESULT hr = g_RealResizeBuffers(
                self,
                bufferCount,
                width,
                height,
                newFormat,
                swapChainFlags);

            LogShimA(
                SUCCEEDED(hr) ? LogLevel::Info : LogLevel::Warn,
                kComponent,
                "[DX11 ColorSpace] ResizeBuffers result=0x%08X requestedFormat=%s(%u) size=%ux%u buffers=%u",
                static_cast<unsigned>(hr),
                DxgiFormatName(newFormat),
                static_cast<unsigned>(newFormat),
                width,
                height,
                bufferCount);

            if (SUCCEEDED(hr))
                CaptureSwapChain(self, "ResizeBuffers");

            return hr;
        }

        HRESULT STDMETHODCALLTYPE HookSetColorSpace1(
            IDXGISwapChain3* self,
            DXGI_COLOR_SPACE_TYPE colorSpace)
        {
            const HRESULT hr = g_RealSetColorSpace1(self, colorSpace);

            LogShimA(
                SUCCEEDED(hr) ? LogLevel::Info : LogLevel::Warn,
                kComponent,
                "[DX11 ColorSpace] SwapChain SetColorSpace1 requested=%s(%u) result=0x%08X%s",
                ColorSpaceName(colorSpace),
                static_cast<unsigned>(colorSpace),
                static_cast<unsigned>(hr),
                SUCCEEDED(hr) ? " state-now-requested-value" : " state-unchanged-or-unknown");

            return hr;
        }

        void InstallContextHooks(ID3D11DeviceContext* context)
        {
            if (!context)
                return;

            // Public ID3D11DeviceContext COM ABI ordinals from d3d11.h.
            PatchComVtableEntry(
                context,
                8,
                &HookPSSetShaderResources,
                g_RealPSSetShaderResources,
                "ID3D11DeviceContext::PSSetShaderResources");

            PatchComVtableEntry(
                context,
                33,
                &HookOMSetRenderTargets,
                g_RealOMSetRenderTargets,
                "ID3D11DeviceContext::OMSetRenderTargets");

            LogCurrentViewports(context, "device-capture");
        }

        void InstallFactoryHooks(IDXGIFactory* factory)
        {
            if (!factory)
                return;

            // Public IDXGIFactory COM ABI ordinal.
            PatchComVtableEntry(
                factory,
                10,
                &HookFactoryCreateSwapChain,
                g_RealFactoryCreateSwapChain,
                "IDXGIFactory::CreateSwapChain");
        }

        void InstallFactoryFromDevice(ID3D11Device* device)
        {
            if (!device)
                return;

            IDXGIDevice* dxgiDevice = nullptr;
            if (FAILED(device->QueryInterface(
                    __uuidof(IDXGIDevice),
                    reinterpret_cast<void**>(&dxgiDevice))) ||
                !dxgiDevice)
            {
                return;
            }

            IDXGIAdapter* adapter = nullptr;
            if (SUCCEEDED(dxgiDevice->GetAdapter(&adapter)) && adapter)
            {
                IDXGIFactory* factory = nullptr;
                if (SUCCEEDED(adapter->GetParent(
                        __uuidof(IDXGIFactory),
                        reinterpret_cast<void**>(&factory))) &&
                    factory)
                {
                    InstallFactoryHooks(factory);
                    factory->Release();
                }
                adapter->Release();
            }

            dxgiDevice->Release();
        }

        void InstallDeviceHooks(ID3D11Device* device)
        {
            if (!device)
                return;

            // Public ID3D11Device COM ABI ordinals from d3d11.h.
            PatchComVtableEntry(
                device,
                5,
                &HookCreateTexture2D,
                g_RealCreateTexture2D,
                "ID3D11Device::CreateTexture2D");

            PatchComVtableEntry(
                device,
                7,
                &HookCreateSRV,
                g_RealCreateSRV,
                "ID3D11Device::CreateShaderResourceView");

            PatchComVtableEntry(
                device,
                9,
                &HookCreateRTV,
                g_RealCreateRTV,
                "ID3D11Device::CreateRenderTargetView");

            PatchComVtableEntry(
                device,
                10,
                &HookCreateDSV,
                g_RealCreateDSV,
                "ID3D11Device::CreateDepthStencilView");

            InstallFactoryFromDevice(device);

            ID3D11DeviceContext* context = nullptr;
            device->GetImmediateContext(&context);
            if (context)
            {
                InstallContextHooks(context);
                context->Release();
            }
        }

        void CaptureSwapChain(IDXGISwapChain* swapChain, const char* source)
        {
            if (!swapChain)
                return;

            PatchComVtableEntry(
                swapChain,
                13,
                &HookResizeBuffers,
                g_RealResizeBuffers,
                "IDXGISwapChain::ResizeBuffers");

            DXGI_SWAP_CHAIN_DESC desc = {};
            if (SUCCEEDED(swapChain->GetDesc(&desc)))
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[DX11 ColorSpace] SwapChain source=%s ptr=0x%p format=%s(%u) size=%ux%u buffers=%u windowed=%s swapEffect=%u flags=0x%08X",
                    source,
                    swapChain,
                    DxgiFormatName(desc.BufferDesc.Format),
                    static_cast<unsigned>(desc.BufferDesc.Format),
                    desc.BufferDesc.Width,
                    desc.BufferDesc.Height,
                    desc.BufferCount,
                    desc.Windowed ? "yes" : "no",
                    static_cast<unsigned>(desc.SwapEffect),
                    desc.Flags);
            }

            IDXGISwapChain3* swapChain3 = nullptr;
            if (SUCCEEDED(swapChain->QueryInterface(
                    __uuidof(IDXGISwapChain3),
                    reinterpret_cast<void**>(&swapChain3))) &&
                swapChain3)
            {
                // DXGI exposes CheckColorSpaceSupport and SetColorSpace1 here,
                // but no GetColorSpace1 accessor. Observe every SetColorSpace1
                // call rather than inventing current state from supported modes.
                PatchComVtableEntry(
                    swapChain3,
                    38,
                    &HookSetColorSpace1,
                    g_RealSetColorSpace1,
                    "IDXGISwapChain3::SetColorSpace1");

                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[DX11 ColorSpace] SwapChain colorSpaceState=<no public getter>; SetColorSpace1 requests will be logged if BZR/Ogre makes one");

                swapChain3->Release();
            }
            else
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[DX11 ColorSpace] SwapChain colorSpaceState=<IDXGISwapChain3 unavailable>");
            }

            ID3D11Texture2D* backbuffer = nullptr;
            if (SUCCEEDED(swapChain->GetBuffer(
                    0,
                    __uuidof(ID3D11Texture2D),
                    reinterpret_cast<void**>(&backbuffer))) &&
                backbuffer)
            {
                D3D11_TEXTURE2D_DESC backbufferDesc = {};
                backbuffer->GetDesc(&backbufferDesc);

                g_BackbufferIdentity.store(
                    ComIdentity(backbuffer),
                    std::memory_order_release);

                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[DX11 ColorSpace] Backbuffer resource=0x%p format=%s(%u) srgb=%s typeless=%s float=%s size=%ux%u samples=%u",
                    backbuffer,
                    DxgiFormatName(backbufferDesc.Format),
                    static_cast<unsigned>(backbufferDesc.Format),
                    IsSrgbFormat(backbufferDesc.Format) ? "yes" : "no",
                    IsTypelessFormat(backbufferDesc.Format) ? "yes" : "no",
                    IsFloatFormat(backbufferDesc.Format) ? "yes" : "no",
                    backbufferDesc.Width,
                    backbufferDesc.Height,
                    backbufferDesc.SampleDesc.Count);

                backbuffer->Release();
            }
        }

        HRESULT WINAPI HookD3D11CreateDevice(
            IDXGIAdapter* adapter,
            D3D_DRIVER_TYPE driverType,
            HMODULE software,
            UINT flags,
            const D3D_FEATURE_LEVEL* featureLevels,
            UINT featureLevelCount,
            UINT sdkVersion,
            ID3D11Device** device,
            D3D_FEATURE_LEVEL* featureLevel,
            ID3D11DeviceContext** immediateContext)
        {
            const HRESULT hr = g_RealD3D11CreateDevice(
                adapter,
                driverType,
                software,
                flags,
                featureLevels,
                featureLevelCount,
                sdkVersion,
                device,
                featureLevel,
                immediateContext);

            if (SUCCEEDED(hr))
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[DX11 ColorSpace] RenderSystem = Direct3D11 Rendering Subsystem (RenderSystem_Direct3D11.dll created device); device=0x%p featureLevel=0x%X",
                    device ? *device : nullptr,
                    featureLevel ? static_cast<unsigned>(*featureLevel) : 0u);

                if (device && *device)
                    InstallDeviceHooks(*device);
                if (immediateContext && *immediateContext)
                    InstallContextHooks(*immediateContext);
            }

            return hr;
        }

        HRESULT WINAPI HookD3D11CreateDeviceAndSwapChain(
            IDXGIAdapter* adapter,
            D3D_DRIVER_TYPE driverType,
            HMODULE software,
            UINT flags,
            const D3D_FEATURE_LEVEL* featureLevels,
            UINT featureLevelCount,
            UINT sdkVersion,
            const DXGI_SWAP_CHAIN_DESC* swapChainDesc,
            IDXGISwapChain** swapChain,
            ID3D11Device** device,
            D3D_FEATURE_LEVEL* featureLevel,
            ID3D11DeviceContext** immediateContext)
        {
            const HRESULT hr = g_RealD3D11CreateDeviceAndSwapChain(
                adapter,
                driverType,
                software,
                flags,
                featureLevels,
                featureLevelCount,
                sdkVersion,
                swapChainDesc,
                swapChain,
                device,
                featureLevel,
                immediateContext);

            if (SUCCEEDED(hr))
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[DX11 ColorSpace] RenderSystem = Direct3D11 Rendering Subsystem (RenderSystem_Direct3D11.dll created device+swapchain); device=0x%p swapChain=0x%p featureLevel=0x%X",
                    device ? *device : nullptr,
                    swapChain ? *swapChain : nullptr,
                    featureLevel ? static_cast<unsigned>(*featureLevel) : 0u);

                if (device && *device)
                    InstallDeviceHooks(*device);
                if (immediateContext && *immediateContext)
                    InstallContextHooks(*immediateContext);
                if (swapChain && *swapChain)
                    CaptureSwapChain(*swapChain, "D3D11CreateDeviceAndSwapChain");
            }

            return hr;
        }

        bool PatchIatFunction(
            HMODULE module,
            const char* importedDll,
            const char* functionName,
            void* replacement,
            void** original)
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
            HMODULE importedModule = GetModuleHandleA(importedDll);
            if (importedModule)
                targetProc = GetProcAddress(importedModule, functionName);

            auto* descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(
                base + imports.VirtualAddress);

            for (; descriptor->Name; ++descriptor)
            {
                const char* dllName = reinterpret_cast<const char*>(base + descriptor->Name);
                if (_stricmp(dllName, importedDll) != 0)
                    continue;

                auto* firstThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(
                    base + descriptor->FirstThunk);

                IMAGE_THUNK_DATA* nameThunk = descriptor->OriginalFirstThunk
                    ? reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->OriginalFirstThunk)
                    : nullptr;

                for (; firstThunk->u1.Function; ++firstThunk)
                {
                    bool matches = false;

                    if (nameThunk)
                    {
                        if (!IMAGE_SNAP_BY_ORDINAL(nameThunk->u1.Ordinal))
                        {
                            auto* byName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(
                                base + nameThunk->u1.AddressOfData);
                            matches = std::strcmp(
                                reinterpret_cast<const char*>(byName->Name),
                                functionName) == 0;
                        }
                        ++nameThunk;
                    }
                    else if (targetProc)
                    {
                        matches = reinterpret_cast<void*>(firstThunk->u1.Function) ==
                            reinterpret_cast<void*>(targetProc);
                    }

                    if (!matches)
                        continue;

                    auto** entry = reinterpret_cast<void**>(&firstThunk->u1.Function);
                    if (*entry == replacement)
                        return true;

                    DWORD oldProtect = 0;
                    if (!VirtualProtect(entry, sizeof(void*), PAGE_READWRITE, &oldProtect))
                        return false;

                    if (!*original)
                        *original = *entry;

                    *entry = replacement;

                    DWORD ignored = 0;
                    VirtualProtect(entry, sizeof(void*), oldProtect, &ignored);
                    FlushInstructionCache(GetCurrentProcess(), entry, sizeof(void*));
                    return true;
                }
            }

            return false;
        }

        void PatchRendererImports(HMODULE renderer)
        {
            unsigned installed = 0;

            installed += PatchIatFunction(
                renderer,
                "d3d11.dll",
                "D3D11CreateDevice",
                reinterpret_cast<void*>(&HookD3D11CreateDevice),
                reinterpret_cast<void**>(&g_RealD3D11CreateDevice)) ? 1u : 0u;

            installed += PatchIatFunction(
                renderer,
                "d3d11.dll",
                "D3D11CreateDeviceAndSwapChain",
                reinterpret_cast<void*>(&HookD3D11CreateDeviceAndSwapChain),
                reinterpret_cast<void**>(&g_RealD3D11CreateDeviceAndSwapChain)) ? 1u : 0u;

            LogShimA(
                installed ? LogLevel::Info : LogLevel::Warn,
                kComponent,
                "[DX11 ColorSpace] RenderSystem_Direct3D11.dll D3D11 creation observers installed=%u; no rendering state was changed",
                installed);
        }

        unsigned __stdcall DiscoveryThreadProc(void*)
        {
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[DX11 ColorSpace] probe enabled; waiting for RenderSystem_Direct3D11.dll (DX9 remains untouched)");

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[DX11 ColorSpace] Ogre RenderWindow mHwGamma is not read through hardcoded object layout; effective backbuffer/RTV state and matching BZOgreLogfile gamma lines are the proof inputs");

            for (unsigned attempt = 0;
                 attempt < kDiscoveryAttempts &&
                 !g_ShutdownRequested.load(std::memory_order_acquire);
                 ++attempt)
            {
                HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
                if (renderer)
                {
                    LogShimA(
                        LogLevel::Info,
                        kComponent,
                        "[DX11 ColorSpace] found RenderSystem_Direct3D11.dll module=0x%p",
                        renderer);

                    PatchRendererImports(renderer);
                    return 0;
                }

                Sleep(kDiscoverySleepMs);
            }

            if (!g_ShutdownRequested.load(std::memory_order_acquire))
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[DX11 ColorSpace] Direct3D11 renderer was not observed during discovery window; installed no D3D11 hooks (likely DX9 or renderer initialization was not reached)");
            }

            return 0;
        }
    }

    void InitializeDx11ColorSpaceDiagnostic()
    {
        if (!DiagnosticRequested())
            return;
        if (g_DiscoveryThread)
            return;

        g_ShutdownRequested.store(false, std::memory_order_release);
        g_DiscoveryThread = _beginthreadex(
            nullptr,
            0,
            DiscoveryThreadProc,
            nullptr,
            0,
            nullptr);

        if (!g_DiscoveryThread)
        {
            LogShimA(
                LogLevel::Warn,
                kComponent,
                "[DX11 ColorSpace] failed to start discovery thread (err=%lu); diagnostic disabled",
                GetLastError());
        }
    }

    void ShutdownDx11ColorSpaceDiagnostic()
    {
        g_ShutdownRequested.store(true, std::memory_order_release);

        if (g_DiscoveryThread)
        {
            WaitForSingleObject(reinterpret_cast<HANDLE>(g_DiscoveryThread), 1000);
            CloseHandle(reinterpret_cast<HANDLE>(g_DiscoveryThread));
            g_DiscoveryThread = 0;
        }
    }
}
