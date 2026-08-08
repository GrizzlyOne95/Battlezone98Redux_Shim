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

        // WKPDID_D3DDebugObjectName without a dxguid.lib dependency.
        constexpr GUID kD3DDebugObjectName =
            { 0x429b8c22, 0x9188, 0x4b0c, { 0x87, 0x42, 0xac, 0xb0, 0xbf, 0x85, 0xc2, 0x00 } };

        std::atomic<bool> g_ShutdownRequested{ false };
        std::atomic<uintptr_t> g_BackbufferResource{ 0 };
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

        using FnCreateDXGIFactory = HRESULT(WINAPI*)(REFIID, void**);
        using FnCreateDXGIFactory2 = HRESULT(WINAPI*)(UINT, REFIID, void**);

        using FnFactoryCreateSwapChain = HRESULT(STDMETHODCALLTYPE*)(
            IDXGIFactory*, IUnknown*, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**);

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
        FnCreateDXGIFactory g_RealCreateDXGIFactory = nullptr;
        FnCreateDXGIFactory g_RealCreateDXGIFactory1 = nullptr;
        FnCreateDXGIFactory2 g_RealCreateDXGIFactory2 = nullptr;
        FnFactoryCreateSwapChain g_RealFactoryCreateSwapChain = nullptr;

        FnDeviceCreateTexture2D g_RealCreateTexture2D = nullptr;
        FnDeviceCreateSRV g_RealCreateSRV = nullptr;
        FnDeviceCreateRTV g_RealCreateRTV = nullptr;
        FnDeviceCreateDSV g_RealCreateDSV = nullptr;
        FnContextPSSetShaderResources g_RealPSSetShaderResources = nullptr;
        FnContextOMSetRenderTargets g_RealOMSetRenderTargets = nullptr;

        uint64_t MixKey(uint64_t seed, uint64_t value)
        {
            // 64-bit hash-combine; deterministic and cheap enough for diagnostic-only use.
            seed ^= value + 0x9e3779b97f4a7c15ull + (seed << 6) + (seed >> 2);
            return seed;
        }

        uint64_t PointerKey(const void* p)
        {
            return static_cast<uint64_t>(reinterpret_cast<uintptr_t>(p));
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
                    LogShimA(LogLevel::Warn, kComponent,
                        "[DX11 ColorSpace] %s log limit reached (%u unique records); further records suppressed",
                        label, static_cast<unsigned>(limit));
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
            std::transform(v.begin(), v.end(), v.begin(),
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
                kEnvironmentSwitch, envValue, static_cast<DWORD>(sizeof(envValue)));
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
            case DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020:
                return "DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020";
            case DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020:
                return "DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020";
            case DXGI_COLOR_SPACE_RGB_STUDIO_G2084_NONE_P2020:
                return "DXGI_COLOR_SPACE_RGB_STUDIO_G2084_NONE_P2020";
            case DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020:
                return "DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020";
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
            std::transform(value.begin(), value.end(), value.begin(),
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
            if (FAILED(resource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&texture))) || !texture)
                return false;
            texture->GetDesc(&outDesc);
            texture->Release();
            return true;
        }

        void LogTextureDesc(const char* prefix, ID3D11Texture2D* texture, const D3D11_TEXTURE2D_DESC& desc)
        {
            const std::string debugName = GetDebugName(texture);
            const char* semantic = KnownResourceSemantic(debugName);
            LogShimA(LogLevel::Info, kComponent,
                "[DX11 ColorSpace] %s resource=0x%p name=%s size=%ux%u array=%u mips=%u format=%s(%u) srgb=%s typeless=%s bind=0x%08X misc=0x%08X%s%s",
                prefix,
                texture,
                debugName.empty() ? "<not-set>" : debugName.c_str(),
                desc.Width, desc.Height, desc.ArraySize, desc.MipLevels,
                DxgiFormatName(desc.Format), static_cast<unsigned>(desc.Format),
                IsSrgbFormat(desc.Format) ? "yes" : "no",
                IsTypelessFormat(desc.Format) ? "yes" : "no",
                desc.BindFlags, desc.MiscFlags,
                semantic ? " semantic=\"" : "",
                semantic ? semantic : "");
            if (semantic)
                LogShimA(LogLevel::Info, kComponent, "[DX11 ColorSpace]   semantic-end=\" (name-derived, exact CR bootstrap resource)");
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
                if (!InsertBounded(g_ViewportKeys, key, kMaxViewportLogs,
                    g_ViewportLimitLogged, "viewport"))
                {
                    continue;
                }
                LogShimA(LogLevel::Info, kComponent,
                    "[DX11 ColorSpace] Active D3D11 viewport[%u] trigger=%s x=%.1f y=%.1f width=%.1f height=%.1f minDepth=%.3f maxDepth=%.3f",
                    i, trigger, vp.TopLeftX, vp.TopLeftY, vp.Width, vp.Height,
                    vp.MinDepth, vp.MaxDepth);
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
            const bool cube = srvDesc.ViewDimension == D3D11_SRV_DIMENSION_TEXTURECUBE ||
                srvDesc.ViewDimension == D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;

            uint64_t key = MixKey(PointerKey(srv), PointerKey(resource));
            key = MixKey(key, static_cast<uint64_t>(srvDesc.Format));
            if (binding)
                key = MixKey(key, 0xB1000000ull | slot);

            bool shouldLog = false;
            if (binding)
                shouldLog = InsertBounded(g_SrvBindingKeys, key, kMaxSrvBindingLogs,
                    g_SrvBindingLimitLogged, "SRV binding");
            else
                shouldLog = InsertBounded(g_SrvCreateKeys, key, kMaxSrvCreateLogs,
                    g_SrvCreateLimitLogged, "SRV creation");

            if (!shouldLog)
            {
                resource->Release();
                return;
            }

            std::string srvName = GetDebugName(srv);
            std::string resourceName;
            ID3D11DeviceChild* child = nullptr;
            if (SUCCEEDED(resource->QueryInterface(__uuidof(ID3D11DeviceChild), reinterpret_cast<void**>(&child))) && child)
            {
                resourceName = GetDebugName(child);
                child->Release();
            }
            const char* semantic = KnownResourceSemantic(!resourceName.empty() ? resourceName : srvName);

            if (isTexture2D)
            {
                LogShimA(LogLevel::Info, kComponent,
                    "[DX11 ColorSpace] %s%s%u srv=0x%p srvName=%s resource=0x%p resourceName=%s resourceFormat=%s(%u) srvFormat=%s(%u) resourceSRGB=%s srvSRGB=%s resourceTypeless=%s size=%ux%u array=%u mips=%u cube=%s hint=\"%s\"",
                    binding ? "PS bind t" : "SRV create slot=",
                    binding ? "" : "n/a/",
                    binding ? slot : 0,
                    srv,
                    srvName.empty() ? "<not-set>" : srvName.c_str(),
                    resource,
                    resourceName.empty() ? "<not-set>" : resourceName.c_str(),
                    DxgiFormatName(texDesc.Format), static_cast<unsigned>(texDesc.Format),
                    DxgiFormatName(srvDesc.Format), static_cast<unsigned>(srvDesc.Format),
                    IsSrgbFormat(texDesc.Format) ? "yes" : "no",
                    IsSrgbFormat(srvDesc.Format) ? "yes" : "no",
                    IsTypelessFormat(texDesc.Format) ? "yes" : "no",
                    texDesc.Width, texDesc.Height, texDesc.ArraySize, texDesc.MipLevels,
                    cube ? "yes" : "no",
                    semantic ? semantic : CrPixelSlotHint(slot, cube));
            }
            else
            {
                LogShimA(LogLevel::Info, kComponent,
                    "[DX11 ColorSpace] %s t%u srv=0x%p resource=0x%p non-Texture2D srvFormat=%s(%u)",
                    binding ? "PS bind" : "SRV create", slot, srv, resource,
                    DxgiFormatName(srvDesc.Format), static_cast<unsigned>(srvDesc.Format));
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
            if (!InsertBounded(g_RenderTargetKeys, key, kMaxRenderTargetLogs,
                g_RenderTargetLimitLogged, "render-target"))
            {
                resource->Release();
                return;
            }

            const uintptr_t resourceAddress = reinterpret_cast<uintptr_t>(resource);
            const bool backbuffer = resourceAddress == g_BackbufferResource.load(std::memory_order_acquire);
            const std::string rtvName = GetDebugName(rtv);
            std::string resourceName;
            ID3D11DeviceChild* child = nullptr;
            if (SUCCEEDED(resource->QueryInterface(__uuidof(ID3D11DeviceChild), reinterpret_cast<void**>(&child))) && child)
            {
                resourceName = GetDebugName(child);
                child->Release();
            }

            LogShimA(LogLevel::Info, kComponent,
                "[DX11 ColorSpace] RTV %s slot=%u rtv=0x%p rtvName=%s resource=0x%p resourceName=%s backbuffer=%s resourceFormat=%s(%u) rtvFormat=%s(%u) resourceSRGB=%s rtvSRGB=%s typeless=%s floatTarget=%s size=%ux%u samples=%u",
                trigger, slot, rtv,
                rtvName.empty() ? "<not-set>" : rtvName.c_str(),
                resource,
                resourceName.empty() ? "<not-set>" : resourceName.c_str(),
                backbuffer ? "yes" : "no",
                DxgiFormatName(texDesc.Format), static_cast<unsigned>(texDesc.Format),
                DxgiFormatName(viewDesc.Format), static_cast<unsigned>(viewDesc.Format),
                IsSrgbFormat(texDesc.Format) ? "yes" : "no",
                IsSrgbFormat(viewDesc.Format) ? "yes" : "no",
                IsTypelessFormat(texDesc.Format) ? "yes" : "no",
                (IsFloatFormat(texDesc.Format) || IsFloatFormat(viewDesc.Format)) ? "yes" : "no",
                texDesc.Width, texDesc.Height, texDesc.SampleDesc.Count);

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
                if (InsertBounded(g_RenderTargetKeys, key, kMaxRenderTargetLogs,
                    g_RenderTargetLimitLogged, "render-target"))
                {
                    LogShimA(LogLevel::Info, kComponent,
                        "[DX11 ColorSpace] DSV %s dsv=0x%p resource=0x%p resourceFormat=%s(%u) dsvFormat=%s(%u) typelessResource=%s size=%ux%u samples=%u DATA=yes",
                        trigger, dsv, resource,
                        DxgiFormatName(texDesc.Format), static_cast<unsigned>(texDesc.Format),
                        DxgiFormatName(viewDesc.Format), static_cast<unsigned>(viewDesc.Format),
                        IsTypelessFormat(texDesc.Format) ? "yes" : "no",
                        texDesc.Width, texDesc.Height, texDesc.SampleDesc.Count);
                }
            }
            resource->Release();
        }

        template <typename T>
        bool PatchComVtableEntry(void* object, size_t index, T hook, T& original, const char* label)
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
                // Multiple unrelated D3D11 implementations/devices would require a
                // per-vtable trampoline map. BZR uses one device. Fail closed rather
                // than risk chaining the wrong implementation.
                LogShimA(LogLevel::Warn, kComponent,
                    "[DX11 ColorSpace] %s vtable differs from already-hooked implementation; leaving it untouched",
                    label);
                return false;
            }

            DWORD oldProtect = 0;
            if (!VirtualProtect(&vtable[index], sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;
            if (!original)
                original = reinterpret_cast<T>(current);
            vtable[index] = reinterpret_cast<void*>(hook);
            DWORD ignored = 0;
            VirtualProtect(&vtable[index], sizeof(void*), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), &vtable[index], sizeof(void*));
            LogShimA(LogLevel::Info, kComponent,
                "[DX11 ColorSpace] installed %s observer (vtable[%u])",
                label, static_cast<unsigned>(index));
            return true;
        }

        void InstallContextHooks(ID3D11DeviceContext* context);
        void InstallDeviceHooks(ID3D11Device* device);
        void CaptureSwapChain(IDXGISwapChain* swapChain, const char* source);
        void InstallFactoryHooks(void* factoryObject);

        HRESULT STDMETHODCALLTYPE HookCreateTexture2D(
            ID3D11Device* self,
            const D3D11_TEXTURE2D_DESC* desc,
            const D3D11_SUBRESOURCE_DATA* initialData,
            ID3D11Texture2D** texture)
        {
            const HRESULT hr = g_RealCreateTexture2D(self, desc, initialData, texture);
            if (SUCCEEDED(hr) && texture && *texture && desc)
            {
                uint64_t key = MixKey(PointerKey(*texture), static_cast<uint64_t>(desc->Format));
                if (InsertBounded(g_TextureCreateKeys, key, kMaxTextureCreateLogs,
                    g_TextureCreateLimitLogged, "Texture2D creation"))
                {
                    LogTextureDesc("Texture2D create", *texture, *desc);
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
            if (views)
            {
                for (UINT i = 0; i < numViews; ++i)
                    LogSrvRecord(startSlot + i, views[i], true);
            }
            LogCurrentViewports(self, "PSSetShaderResources");
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

        void InstallContextHooks(ID3D11DeviceContext* context)
        {
            if (!context)
                return;
            // ID3D11DeviceContext inherits ID3D11DeviceChild. These are public
            // COM ABI method ordinals from d3d11.h, not reverse-engineered Ogre
            // object offsets.
            PatchComVtableEntry(context, 8, &HookPSSetShaderResources,
                g_RealPSSetShaderResources, "ID3D11DeviceContext::PSSetShaderResources");
            PatchComVtableEntry(context, 33, &HookOMSetRenderTargets,
                g_RealOMSetRenderTargets, "ID3D11DeviceContext::OMSetRenderTargets");
            LogCurrentViewports(context, "device-capture");
        }

        void InstallDeviceHooks(ID3D11Device* device)
        {
            if (!device)
                return;
            // ID3D11Device public COM ABI ordinals from d3d11.h.
            PatchComVtableEntry(device, 5, &HookCreateTexture2D,
                g_RealCreateTexture2D, "ID3D11Device::CreateTexture2D");
            PatchComVtableEntry(device, 7, &HookCreateSRV,
                g_RealCreateSRV, "ID3D11Device::CreateShaderResourceView");
            PatchComVtableEntry(device, 9, &HookCreateRTV,
                g_RealCreateRTV, "ID3D11Device::CreateRenderTargetView");
            PatchComVtableEntry(device, 10, &HookCreateDSV,
                g_RealCreateDSV, "ID3D11Device::CreateDepthStencilView");

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

            DXGI_SWAP_CHAIN_DESC desc = {};
            if (SUCCEEDED(swapChain->GetDesc(&desc)))
            {
                LogShimA(LogLevel::Info, kComponent,
                    "[DX11 ColorSpace] SwapChain source=%s ptr=0x%p format=%s(%u) size=%ux%u buffers=%u windowed=%s swapEffect=%u flags=0x%08X",
                    source, swapChain,
                    DxgiFormatName(desc.BufferDesc.Format), static_cast<unsigned>(desc.BufferDesc.Format),
                    desc.BufferDesc.Width, desc.BufferDesc.Height, desc.BufferCount,
                    desc.Windowed ? "yes" : "no", static_cast<unsigned>(desc.SwapEffect), desc.Flags);
            }

            IDXGISwapChain3* swapChain3 = nullptr;
            if (SUCCEEDED(swapChain->QueryInterface(__uuidof(IDXGISwapChain3), reinterpret_cast<void**>(&swapChain3))) && swapChain3)
            {
                const DXGI_COLOR_SPACE_TYPE colorSpace = swapChain3->GetColorSpace1();
                LogShimA(LogLevel::Info, kComponent,
                    "[DX11 ColorSpace] SwapChain colorSpace=%s(%u)",
                    ColorSpaceName(colorSpace), static_cast<unsigned>(colorSpace));
                swapChain3->Release();
            }
            else
            {
                LogShimA(LogLevel::Info, kComponent,
                    "[DX11 ColorSpace] SwapChain colorSpace=<IDXGISwapChain3 unavailable>");
            }

            ID3D11Texture2D* backbuffer = nullptr;
            if (SUCCEEDED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backbuffer))) && backbuffer)
            {
                D3D11_TEXTURE2D_DESC backbufferDesc = {};
                backbuffer->GetDesc(&backbufferDesc);
                g_BackbufferResource.store(reinterpret_cast<uintptr_t>(backbuffer), std::memory_order_release);
                LogShimA(LogLevel::Info, kComponent,
                    "[DX11 ColorSpace] Backbuffer resource=0x%p format=%s(%u) srgb=%s typeless=%s float=%s size=%ux%u samples=%u",
                    backbuffer,
                    DxgiFormatName(backbufferDesc.Format), static_cast<unsigned>(backbufferDesc.Format),
                    IsSrgbFormat(backbufferDesc.Format) ? "yes" : "no",
                    IsTypelessFormat(backbufferDesc.Format) ? "yes" : "no",
                    IsFloatFormat(backbufferDesc.Format) ? "yes" : "no",
                    backbufferDesc.Width, backbufferDesc.Height, backbufferDesc.SampleDesc.Count);
                backbuffer->Release();
            }
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
                if (device && SUCCEEDED(device->QueryInterface(__uuidof(ID3D11Device), reinterpret_cast<void**>(&d3dDevice))) && d3dDevice)
                {
                    InstallDeviceHooks(d3dDevice);
                    d3dDevice->Release();
                }
                if (swapChain && *swapChain)
                    CaptureSwapChain(*swapChain, "IDXGIFactory::CreateSwapChain");
            }
            return hr;
        }

        void InstallFactoryHooks(void* factoryObject)
        {
            if (!factoryObject)
                return;
            // IDXGIFactory::CreateSwapChain is vtable slot 10 after IUnknown and
            // IDXGIObject methods. Derived factory interfaces retain the base ABI.
            PatchComVtableEntry(factoryObject, 10, &HookFactoryCreateSwapChain,
                g_RealFactoryCreateSwapChain, "IDXGIFactory::CreateSwapChain");
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
                adapter, driverType, software, flags, featureLevels, featureLevelCount,
                sdkVersion, device, featureLevel, immediateContext);
            if (SUCCEEDED(hr))
            {
                LogShimA(LogLevel::Info, kComponent,
                    "[DX11 ColorSpace] D3D11CreateDevice succeeded device=0x%p featureLevel=0x%X",
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
                adapter, driverType, software, flags, featureLevels, featureLevelCount,
                sdkVersion, swapChainDesc, swapChain, device, featureLevel, immediateContext);
            if (SUCCEEDED(hr))
            {
                LogShimA(LogLevel::Info, kComponent,
                    "[DX11 ColorSpace] D3D11CreateDeviceAndSwapChain succeeded device=0x%p swapChain=0x%p featureLevel=0x%X",
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

        HRESULT WINAPI HookCreateDXGIFactory(REFIID riid, void** factory)
        {
            const HRESULT hr = g_RealCreateDXGIFactory(riid, factory);
            if (SUCCEEDED(hr) && factory && *factory)
                InstallFactoryHooks(*factory);
            return hr;
        }

        HRESULT WINAPI HookCreateDXGIFactory1(REFIID riid, void** factory)
        {
            const HRESULT hr = g_RealCreateDXGIFactory1(riid, factory);
            if (SUCCEEDED(hr) && factory && *factory)
                InstallFactoryHooks(*factory);
            return hr;
        }

        HRESULT WINAPI HookCreateDXGIFactory2(UINT flags, REFIID riid, void** factory)
        {
            const HRESULT hr = g_RealCreateDXGIFactory2(flags, riid, factory);
            if (SUCCEEDED(hr) && factory && *factory)
                InstallFactoryHooks(*factory);
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

            auto* descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + imports.VirtualAddress);
            for (; descriptor->Name; ++descriptor)
            {
                const char* dllName = reinterpret_cast<const char*>(base + descriptor->Name);
                if (_stricmp(dllName, importedDll) != 0)
                    continue;

                auto* firstThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->FirstThunk);
                auto* nameThunk = descriptor->OriginalFirstThunk
                    ? reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->OriginalFirstThunk)
                    : firstThunk;

                for (; firstThunk->u1.Function; ++firstThunk, ++nameThunk)
                {
                    if (IMAGE_SNAP_BY_ORDINAL(nameThunk->u1.Ordinal))
                        continue;
                    auto* byName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(base + nameThunk->u1.AddressOfData);
                    if (std::strcmp(reinterpret_cast<const char*>(byName->Name), functionName) != 0)
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
            installed += PatchIatFunction(renderer, "d3d11.dll", "D3D11CreateDevice",
                reinterpret_cast<void*>(&HookD3D11CreateDevice),
                reinterpret_cast<void**>(&g_RealD3D11CreateDevice)) ? 1u : 0u;
            installed += PatchIatFunction(renderer, "d3d11.dll", "D3D11CreateDeviceAndSwapChain",
                reinterpret_cast<void*>(&HookD3D11CreateDeviceAndSwapChain),
                reinterpret_cast<void**>(&g_RealD3D11CreateDeviceAndSwapChain)) ? 1u : 0u;
            installed += PatchIatFunction(renderer, "dxgi.dll", "CreateDXGIFactory",
                reinterpret_cast<void*>(&HookCreateDXGIFactory),
                reinterpret_cast<void**>(&g_RealCreateDXGIFactory)) ? 1u : 0u;
            installed += PatchIatFunction(renderer, "dxgi.dll", "CreateDXGIFactory1",
                reinterpret_cast<void*>(&HookCreateDXGIFactory1),
                reinterpret_cast<void**>(&g_RealCreateDXGIFactory1)) ? 1u : 0u;
            installed += PatchIatFunction(renderer, "dxgi.dll", "CreateDXGIFactory2",
                reinterpret_cast<void*>(&HookCreateDXGIFactory2),
                reinterpret_cast<void**>(&g_RealCreateDXGIFactory2)) ? 1u : 0u;

            LogShimA(installed ? LogLevel::Info : LogLevel::Warn, kComponent,
                "[DX11 ColorSpace] RenderSystem_Direct3D11.dll import observers installed=%u; no rendering state was changed",
                installed);
        }

        unsigned __stdcall DiscoveryThreadProc(void*)
        {
            LogShimA(LogLevel::Info, kComponent,
                "[DX11 ColorSpace] probe enabled; waiting for RenderSystem_Direct3D11.dll (DX9 remains untouched)");
            LogShimA(LogLevel::Info, kComponent,
                "[DX11 ColorSpace] RenderSystem target = Direct3D11 Rendering Subsystem (validated when the D3D11 plugin creates a device)");
            LogShimA(LogLevel::Info, kComponent,
                "[DX11 ColorSpace] Ogre RenderWindow hwGamma is not read by object-layout offsets; effective swapchain/backbuffer/RTV formats below are authoritative");

            for (unsigned attempt = 0; attempt < kDiscoveryAttempts &&
                !g_ShutdownRequested.load(std::memory_order_acquire); ++attempt)
            {
                HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
                if (renderer)
                {
                    LogShimA(LogLevel::Info, kComponent,
                        "[DX11 ColorSpace] found RenderSystem_Direct3D11.dll module=0x%p",
                        renderer);
                    PatchRendererImports(renderer);
                    return 0;
                }
                Sleep(kDiscoverySleepMs);
            }

            if (!g_ShutdownRequested.load(std::memory_order_acquire))
            {
                LogShimA(LogLevel::Info, kComponent,
                    "[DX11 ColorSpace] Direct3D11 renderer was not observed during discovery window; diagnostic installed no D3D11 hooks (likely DX9 or startup did not reach renderer initialization)");
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
        g_DiscoveryThread = _beginthreadex(nullptr, 0, DiscoveryThreadProc, nullptr, 0, nullptr);
        if (!g_DiscoveryThread)
        {
            LogShimA(LogLevel::Warn, kComponent,
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
