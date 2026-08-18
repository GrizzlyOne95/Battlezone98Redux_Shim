#include "dx11_enhanced_fxaa.h"
#include "dx11_enhanced_fxaa_resources.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <process.h>

#include <array>
#include <atomic>
#include <cctype>
#include <cfloat>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <string>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "dx11-enhanced-fxaa";
        constexpr char kEnvironmentSwitch[] = "OPENSHIM_DX11_ENHANCED_FXAA";
        constexpr char kIniSection[] = "DX11Enhanced";
        constexpr char kIniKey[] = "FXAA";
        constexpr unsigned kDiscoveryAttempts = 1200; // 30 seconds at 25 ms.
        constexpr DWORD kDiscoverySleepMs = 25;
        constexpr UINT kMaxShaderClassInstances = 256;

        std::atomic<bool> g_ShutdownRequested{ false };
        std::atomic<bool> g_FxaaEnabled{ false };
        std::atomic<bool> g_PermanentFault{ false };
        std::atomic<bool> g_UnsupportedFormatLogged{ false };
        uintptr_t g_DiscoveryThread = 0;
        int g_ModuleAnchor = 0;

        std::mutex g_HookMutex;
        std::mutex g_RuntimeMutex;

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

        using FnSwapChainPresent = HRESULT(STDMETHODCALLTYPE*)(
            IDXGISwapChain*, UINT, UINT);

        using FnD3DCompile = HRESULT(WINAPI*)(
            LPCVOID, SIZE_T, LPCSTR, const D3D_SHADER_MACRO*, ID3DInclude*,
            LPCSTR, LPCSTR, UINT, UINT, ID3DBlob**, ID3DBlob**);

        FnD3D11CreateDevice g_RealD3D11CreateDevice = nullptr;
        FnD3D11CreateDeviceAndSwapChain g_RealD3D11CreateDeviceAndSwapChain = nullptr;
        FnFactoryCreateSwapChain g_RealFactoryCreateSwapChain = nullptr;
        FnSwapChainPresent g_RealPresent = nullptr;

        HMODULE g_D3DCompilerModule = nullptr;
        FnD3DCompile g_D3DCompile = nullptr;

        template <typename T>
        void SafeRelease(T*& object)
        {
            if (object)
            {
                object->Release();
                object = nullptr;
            }
        }

        bool StringIsTruthy(const char* value)
        {
            if (!value || !*value)
                return false;

            std::string v(value);
            for (char& c : v)
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

            return v != "0" && v != "false" && v != "no" && v != "off" && v != "disabled";
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

        bool FxaaRequested()
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

        HMODULE GetThisModule()
        {
            HMODULE module = nullptr;
            if (!GetModuleHandleExA(
                    GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                        GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                    reinterpret_cast<LPCSTR>(&g_ModuleAnchor),
                    &module))
            {
                return nullptr;
            }
            return module;
        }

        bool LoadEmbeddedResource(int resourceId, const void*& data, UINT& size)
        {
            data = nullptr;
            size = 0;

            HMODULE module = GetThisModule();
            if (!module)
                return false;

            HRSRC resource = FindResourceA(
                module,
                MAKEINTRESOURCEA(resourceId),
                RT_RCDATA);
            if (!resource)
                return false;

            HGLOBAL loaded = LoadResource(module, resource);
            if (!loaded)
                return false;

            const DWORD resourceSize = SizeofResource(module, resource);
            const void* resourceData = LockResource(loaded);
            if (!resourceData || resourceSize == 0)
                return false;

            data = resourceData;
            size = resourceSize;
            return true;
        }

        const char* DxgiFormatName(DXGI_FORMAT format)
        {
            switch (format)
            {
            case DXGI_FORMAT_R8G8B8A8_UNORM: return "DXGI_FORMAT_R8G8B8A8_UNORM";
            case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB: return "DXGI_FORMAT_R8G8B8A8_UNORM_SRGB";
            case DXGI_FORMAT_B8G8R8A8_UNORM: return "DXGI_FORMAT_B8G8R8A8_UNORM";
            case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB: return "DXGI_FORMAT_B8G8R8A8_UNORM_SRGB";
            case DXGI_FORMAT_B8G8R8X8_UNORM: return "DXGI_FORMAT_B8G8R8X8_UNORM";
            case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB: return "DXGI_FORMAT_B8G8R8X8_UNORM_SRGB";
            case DXGI_FORMAT_R10G10B10A2_UNORM: return "DXGI_FORMAT_R10G10B10A2_UNORM";
            case DXGI_FORMAT_R16G16B16A16_FLOAT: return "DXGI_FORMAT_R16G16B16A16_FLOAT";
            default: return "DXGI_FORMAT_OTHER";
            }
        }

        bool IsSupportedEncodedLdrFormat(DXGI_FORMAT format)
        {
            // FXAA_GREEN_AS_LUMA requires encoded/non-linear RGB. Sampling an
            // _SRGB SRV would decode into linear light, which NVIDIA explicitly
            // warns against for this algorithm. Keep this first experiment to
            // the ordinary 8-bit UNORM presentation formats used by the beta's
            // PF_A8R8G8B8 compositor target. HDR/float/10-bit/typeless paths
            // fail closed rather than guessing their transfer function.
            return format == DXGI_FORMAT_R8G8B8A8_UNORM ||
                   format == DXGI_FORMAT_B8G8R8A8_UNORM ||
                   format == DXGI_FORMAT_B8G8R8X8_UNORM;
        }

        template <typename T>
        bool PatchComVtableEntry(
            void* object,
            size_t index,
            T hook,
            T& original,
            const char* label)
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
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[DX11 Enhanced FXAA] failed to make %s vtable entry writable (err=%lu)",
                    label,
                    GetLastError());
                return false;
            }

            // Preserve the first predecessor in the hook chain. This lets the
            // color-space observer and FXAA coexist regardless of which one
            // reached the shared D3D/DXGI vtable first.
            if (!original)
                original = reinterpret_cast<T>(current);

            vtable[index] = reinterpret_cast<void*>(hook);

            DWORD ignored = 0;
            VirtualProtect(&vtable[index], sizeof(void*), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), &vtable[index], sizeof(void*));
            return true;
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

        class EmbeddedFxaaInclude final : public ID3DInclude
        {
        public:
            EmbeddedFxaaInclude()
            {
                LoadEmbeddedResource(
                    IDR_NVIDIA_FXAA3_11_HEADER,
                    m_HeaderData,
                    m_HeaderSize);
            }

            HRESULT STDMETHODCALLTYPE Open(
                D3D_INCLUDE_TYPE,
                LPCSTR fileName,
                LPCVOID,
                LPCVOID* data,
                UINT* bytes) override
            {
                if (!fileName || !data || !bytes || !m_HeaderData || m_HeaderSize == 0)
                    return E_FAIL;

                const char* baseName = std::strrchr(fileName, '\\');
                baseName = baseName ? baseName + 1 : fileName;
                const char* slash = std::strrchr(baseName, '/');
                baseName = slash ? slash + 1 : baseName;

                if (_stricmp(baseName, "Fxaa3_11.h") != 0)
                    return E_FAIL;

                *data = m_HeaderData;
                *bytes = m_HeaderSize;
                return S_OK;
            }

            HRESULT STDMETHODCALLTYPE Close(LPCVOID) override
            {
                // RCDATA remains valid for the lifetime of the loaded module.
                return S_OK;
            }

        private:
            const void* m_HeaderData = nullptr;
            UINT m_HeaderSize = 0;
        };

        bool LoadD3DCompiler()
        {
            if (g_D3DCompile)
                return true;

            constexpr const wchar_t* kCompilerCandidates[] = {
                L"d3dcompiler_47.dll",
                L"d3dcompiler_46.dll",
                L"d3dcompiler_43.dll",
            };

            for (const wchar_t* candidate : kCompilerCandidates)
            {
                HMODULE module = LoadLibraryW(candidate);
                if (!module)
                    continue;

                auto compile = reinterpret_cast<FnD3DCompile>(
                    GetProcAddress(module, "D3DCompile"));
                if (compile)
                {
                    g_D3DCompilerModule = module;
                    g_D3DCompile = compile;
                    LogShimA(
                        LogLevel::Info,
                        kComponent,
                        "[DX11 Enhanced FXAA] runtime shader compiler loaded");
                    return true;
                }

                FreeLibrary(module);
            }

            LogShimA(
                LogLevel::Error,
                kComponent,
                "[DX11 Enhanced FXAA] no compatible d3dcompiler DLL was available; FXAA disabled for this process");
            return false;
        }

        HRESULT CompileEmbeddedShader(
            const char* entryPoint,
            const char* target,
            ID3DBlob** bytecode)
        {
            if (!entryPoint || !target || !bytecode)
                return E_INVALIDARG;
            *bytecode = nullptr;

            if (!LoadD3DCompiler())
                return E_NOINTERFACE;

            const void* source = nullptr;
            UINT sourceSize = 0;
            if (!LoadEmbeddedResource(IDR_DX11_ENHANCED_FXAA_HLSL, source, sourceSize))
                return HRESULT_FROM_WIN32(ERROR_RESOURCE_DATA_NOT_FOUND);

            EmbeddedFxaaInclude include;
            ID3DBlob* errors = nullptr;
            const UINT flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_OPTIMIZATION_LEVEL3;
            const HRESULT hr = g_D3DCompile(
                source,
                sourceSize,
                "dx11_enhanced_fxaa.hlsl",
                nullptr,
                &include,
                entryPoint,
                target,
                flags,
                0,
                bytecode,
                &errors);

            if (FAILED(hr))
            {
                if (errors && errors->GetBufferPointer() && errors->GetBufferSize())
                {
                    const int logLength = static_cast<int>((std::min)(
                        static_cast<SIZE_T>(4096),
                        errors->GetBufferSize()));
                    LogShimA(
                        LogLevel::Error,
                        kComponent,
                        "[DX11 Enhanced FXAA] %s/%s compile failed hr=0x%08X: %.*s",
                        entryPoint,
                        target,
                        static_cast<unsigned>(hr),
                        logLength,
                        static_cast<const char*>(errors->GetBufferPointer()));
                }
                else
                {
                    LogShimA(
                        LogLevel::Error,
                        kComponent,
                        "[DX11 Enhanced FXAA] %s/%s compile failed hr=0x%08X",
                        entryPoint,
                        target,
                        static_cast<unsigned>(hr));
                }
            }

            SafeRelease(errors);
            return hr;
        }

        struct FxaaFrameConstants
        {
            float rcpFrame[2] = {};
            float padding[2] = {};
        };

        struct FxaaRuntime
        {
            ID3D11Device* device = nullptr;
            ID3D11DeviceContext* context = nullptr;
            ID3D11VertexShader* vertexShader = nullptr;
            ID3D11PixelShader* pixelShader = nullptr;
            ID3D11SamplerState* sampler = nullptr;
            ID3D11Buffer* frameConstants = nullptr;
            ID3D11RasterizerState* rasterizerState = nullptr;
            ID3D11DepthStencilState* depthStencilState = nullptr;
            ID3D11Texture2D* inputTexture = nullptr;
            ID3D11ShaderResourceView* inputSrv = nullptr;
            UINT sourceWidth = 0;
            UINT sourceHeight = 0;
            DXGI_FORMAT sourceFormat = DXGI_FORMAT_UNKNOWN;
            bool readyLogged = false;

            void ReleaseSizeResources()
            {
                SafeRelease(inputSrv);
                SafeRelease(inputTexture);
                sourceWidth = 0;
                sourceHeight = 0;
                sourceFormat = DXGI_FORMAT_UNKNOWN;
            }

            void Reset()
            {
                ReleaseSizeResources();
                SafeRelease(depthStencilState);
                SafeRelease(rasterizerState);
                SafeRelease(frameConstants);
                SafeRelease(sampler);
                SafeRelease(pixelShader);
                SafeRelease(vertexShader);
                SafeRelease(context);
                SafeRelease(device);
                readyLogged = false;
            }
        };

        FxaaRuntime g_Runtime;

        struct SavedContextState
        {
            explicit SavedContextState(ID3D11DeviceContext* ctx)
                : context(ctx)
            {
                context->OMGetRenderTargets(
                    static_cast<UINT>(renderTargets.size()),
                    renderTargets.data(),
                    &depthStencilView);
                context->OMGetBlendState(&blendState, blendFactor, &sampleMask);
                context->OMGetDepthStencilState(&depthStencilState, &stencilRef);
                context->RSGetState(&rasterizerState);

                viewportCount = static_cast<UINT>(viewports.size());
                context->RSGetViewports(&viewportCount, viewports.data());

                context->IAGetInputLayout(&inputLayout);
                context->IAGetPrimitiveTopology(&topology);

                vsClassCount = static_cast<UINT>(vsClasses.size());
                context->VSGetShader(&vertexShader, vsClasses.data(), &vsClassCount);
                psClassCount = static_cast<UINT>(psClasses.size());
                context->PSGetShader(&pixelShader, psClasses.data(), &psClassCount);
                gsClassCount = static_cast<UINT>(gsClasses.size());
                context->GSGetShader(&geometryShader, gsClasses.data(), &gsClassCount);
                hsClassCount = static_cast<UINT>(hsClasses.size());
                context->HSGetShader(&hullShader, hsClasses.data(), &hsClassCount);
                dsClassCount = static_cast<UINT>(dsClasses.size());
                context->DSGetShader(&domainShader, dsClasses.data(), &dsClassCount);

                context->PSGetShaderResources(0, 1, &psSrv0);
                context->PSGetSamplers(0, 1, &psSampler0);
                context->PSGetConstantBuffers(0, 1, &psConstantBuffer0);
                context->GetPredication(&predicate, &predicateValue);
            }

            ~SavedContextState()
            {
                Restore();
            }

            void Restore()
            {
                if (!context || restored)
                    return;
                restored = true;

                context->SetPredication(predicate, predicateValue);
                context->IASetInputLayout(inputLayout);
                context->IASetPrimitiveTopology(topology);
                context->VSSetShader(vertexShader, vsClasses.data(), vsClassCount);
                context->PSSetShader(pixelShader, psClasses.data(), psClassCount);
                context->GSSetShader(geometryShader, gsClasses.data(), gsClassCount);
                context->HSSetShader(hullShader, hsClasses.data(), hsClassCount);
                context->DSSetShader(domainShader, dsClasses.data(), dsClassCount);
                context->PSSetShaderResources(0, 1, &psSrv0);
                context->PSSetSamplers(0, 1, &psSampler0);
                context->PSSetConstantBuffers(0, 1, &psConstantBuffer0);
                context->RSSetState(rasterizerState);
                if (viewportCount > 0)
                    context->RSSetViewports(viewportCount, viewports.data());
                context->OMSetBlendState(blendState, blendFactor, sampleMask);
                context->OMSetDepthStencilState(depthStencilState, stencilRef);
                context->OMSetRenderTargets(
                    static_cast<UINT>(renderTargets.size()),
                    renderTargets.data(),
                    depthStencilView);

                ReleaseCapturedRefs();
            }

            void ReleaseCapturedRefs()
            {
                for (auto*& view : renderTargets)
                    SafeRelease(view);
                SafeRelease(depthStencilView);
                SafeRelease(blendState);
                SafeRelease(depthStencilState);
                SafeRelease(rasterizerState);
                SafeRelease(inputLayout);
                SafeRelease(vertexShader);
                SafeRelease(pixelShader);
                SafeRelease(geometryShader);
                SafeRelease(hullShader);
                SafeRelease(domainShader);
                for (UINT i = 0; i < vsClassCount; ++i) SafeRelease(vsClasses[i]);
                for (UINT i = 0; i < psClassCount; ++i) SafeRelease(psClasses[i]);
                for (UINT i = 0; i < gsClassCount; ++i) SafeRelease(gsClasses[i]);
                for (UINT i = 0; i < hsClassCount; ++i) SafeRelease(hsClasses[i]);
                for (UINT i = 0; i < dsClassCount; ++i) SafeRelease(dsClasses[i]);
                SafeRelease(psSrv0);
                SafeRelease(psSampler0);
                SafeRelease(psConstantBuffer0);
                SafeRelease(predicate);
            }

            ID3D11DeviceContext* context = nullptr;
            std::array<ID3D11RenderTargetView*, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> renderTargets = {};
            ID3D11DepthStencilView* depthStencilView = nullptr;
            ID3D11BlendState* blendState = nullptr;
            FLOAT blendFactor[4] = {};
            UINT sampleMask = 0xFFFFFFFFu;
            ID3D11DepthStencilState* depthStencilState = nullptr;
            UINT stencilRef = 0;
            ID3D11RasterizerState* rasterizerState = nullptr;
            std::array<D3D11_VIEWPORT, D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE> viewports = {};
            UINT viewportCount = 0;
            ID3D11InputLayout* inputLayout = nullptr;
            D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;

            ID3D11VertexShader* vertexShader = nullptr;
            ID3D11PixelShader* pixelShader = nullptr;
            ID3D11GeometryShader* geometryShader = nullptr;
            ID3D11HullShader* hullShader = nullptr;
            ID3D11DomainShader* domainShader = nullptr;
            std::array<ID3D11ClassInstance*, kMaxShaderClassInstances> vsClasses = {};
            std::array<ID3D11ClassInstance*, kMaxShaderClassInstances> psClasses = {};
            std::array<ID3D11ClassInstance*, kMaxShaderClassInstances> gsClasses = {};
            std::array<ID3D11ClassInstance*, kMaxShaderClassInstances> hsClasses = {};
            std::array<ID3D11ClassInstance*, kMaxShaderClassInstances> dsClasses = {};
            UINT vsClassCount = 0;
            UINT psClassCount = 0;
            UINT gsClassCount = 0;
            UINT hsClassCount = 0;
            UINT dsClassCount = 0;

            ID3D11ShaderResourceView* psSrv0 = nullptr;
            ID3D11SamplerState* psSampler0 = nullptr;
            ID3D11Buffer* psConstantBuffer0 = nullptr;
            ID3D11Predicate* predicate = nullptr;
            BOOL predicateValue = FALSE;
            bool restored = false;
        };

        bool CreateDeviceResources(ID3D11Device* device)
        {
            if (!device)
                return false;

            if (device->GetFeatureLevel() < D3D_FEATURE_LEVEL_11_0)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[DX11 Enhanced FXAA] D3D feature level 11_0 is required for the HLSL5/Gather path; featureLevel=0x%X",
                    static_cast<unsigned>(device->GetFeatureLevel()));
                return false;
            }

            ID3DBlob* vsBlob = nullptr;
            ID3DBlob* psBlob = nullptr;
            HRESULT hr = CompileEmbeddedShader("VSMain", "vs_5_0", &vsBlob);
            if (FAILED(hr))
            {
                g_PermanentFault.store(true, std::memory_order_release);
                return false;
            }

            hr = CompileEmbeddedShader("PSMain", "ps_5_0", &psBlob);
            if (FAILED(hr))
            {
                SafeRelease(vsBlob);
                g_PermanentFault.store(true, std::memory_order_release);
                return false;
            }

            hr = device->CreateVertexShader(
                vsBlob->GetBufferPointer(),
                vsBlob->GetBufferSize(),
                nullptr,
                &g_Runtime.vertexShader);
            if (SUCCEEDED(hr))
            {
                hr = device->CreatePixelShader(
                    psBlob->GetBufferPointer(),
                    psBlob->GetBufferSize(),
                    nullptr,
                    &g_Runtime.pixelShader);
            }
            SafeRelease(vsBlob);
            SafeRelease(psBlob);

            if (FAILED(hr))
            {
                LogShimA(
                    LogLevel::Error,
                    kComponent,
                    "[DX11 Enhanced FXAA] failed to create SM5 shaders hr=0x%08X",
                    static_cast<unsigned>(hr));
                return false;
            }

            D3D11_SAMPLER_DESC samplerDesc = {};
            samplerDesc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
            samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
            samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
            samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
            samplerDesc.MaxAnisotropy = 1;
            samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
            samplerDesc.MinLOD = 0.0f;
            samplerDesc.MaxLOD = FLT_MAX;
            hr = device->CreateSamplerState(&samplerDesc, &g_Runtime.sampler);

            if (SUCCEEDED(hr))
            {
                D3D11_BUFFER_DESC cbDesc = {};
                cbDesc.ByteWidth = sizeof(FxaaFrameConstants);
                cbDesc.Usage = D3D11_USAGE_DEFAULT;
                cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
                hr = device->CreateBuffer(&cbDesc, nullptr, &g_Runtime.frameConstants);
            }

            if (SUCCEEDED(hr))
            {
                D3D11_RASTERIZER_DESC rasterDesc = {};
                rasterDesc.FillMode = D3D11_FILL_SOLID;
                rasterDesc.CullMode = D3D11_CULL_NONE;
                rasterDesc.DepthClipEnable = TRUE;
                hr = device->CreateRasterizerState(&rasterDesc, &g_Runtime.rasterizerState);
            }

            if (SUCCEEDED(hr))
            {
                D3D11_DEPTH_STENCIL_DESC depthDesc = {};
                depthDesc.DepthEnable = FALSE;
                depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
                depthDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
                depthDesc.StencilEnable = FALSE;
                hr = device->CreateDepthStencilState(&depthDesc, &g_Runtime.depthStencilState);
            }

            if (FAILED(hr))
            {
                LogShimA(
                    LogLevel::Error,
                    kComponent,
                    "[DX11 Enhanced FXAA] failed to create fixed presentation state hr=0x%08X",
                    static_cast<unsigned>(hr));
                return false;
            }

            return true;
        }

        bool EnsureDeviceResources(ID3D11Device* device)
        {
            if (!device)
                return false;

            if (g_Runtime.device == device &&
                g_Runtime.context &&
                g_Runtime.vertexShader &&
                g_Runtime.pixelShader)
            {
                return true;
            }

            g_Runtime.Reset();
            device->AddRef();
            g_Runtime.device = device;
            device->GetImmediateContext(&g_Runtime.context);
            if (!g_Runtime.context || !CreateDeviceResources(device))
            {
                g_Runtime.Reset();
                return false;
            }

            return true;
        }

        bool EnsureSourceResources(const D3D11_TEXTURE2D_DESC& backbufferDesc)
        {
            if (g_Runtime.inputTexture &&
                g_Runtime.inputSrv &&
                g_Runtime.sourceWidth == backbufferDesc.Width &&
                g_Runtime.sourceHeight == backbufferDesc.Height &&
                g_Runtime.sourceFormat == backbufferDesc.Format)
            {
                return true;
            }

            g_Runtime.ReleaseSizeResources();

            D3D11_TEXTURE2D_DESC inputDesc = {};
            inputDesc.Width = backbufferDesc.Width;
            inputDesc.Height = backbufferDesc.Height;
            inputDesc.MipLevels = 1;
            inputDesc.ArraySize = 1;
            inputDesc.Format = backbufferDesc.Format;
            inputDesc.SampleDesc.Count = 1;
            inputDesc.SampleDesc.Quality = 0;
            inputDesc.Usage = D3D11_USAGE_DEFAULT;
            inputDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

            HRESULT hr = g_Runtime.device->CreateTexture2D(
                &inputDesc,
                nullptr,
                &g_Runtime.inputTexture);
            if (SUCCEEDED(hr))
            {
                D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
                srvDesc.Format = backbufferDesc.Format;
                srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                srvDesc.Texture2D.MostDetailedMip = 0;
                srvDesc.Texture2D.MipLevels = 1;
                hr = g_Runtime.device->CreateShaderResourceView(
                    g_Runtime.inputTexture,
                    &srvDesc,
                    &g_Runtime.inputSrv);
            }

            if (FAILED(hr))
            {
                LogShimA(
                    LogLevel::Error,
                    kComponent,
                    "[DX11 Enhanced FXAA] failed to create %ux%u %s input copy/SRV hr=0x%08X",
                    backbufferDesc.Width,
                    backbufferDesc.Height,
                    DxgiFormatName(backbufferDesc.Format),
                    static_cast<unsigned>(hr));
                g_Runtime.ReleaseSizeResources();
                return false;
            }

            g_Runtime.sourceWidth = backbufferDesc.Width;
            g_Runtime.sourceHeight = backbufferDesc.Height;
            g_Runtime.sourceFormat = backbufferDesc.Format;

            FxaaFrameConstants constants = {};
            constants.rcpFrame[0] = 1.0f / static_cast<float>(backbufferDesc.Width);
            constants.rcpFrame[1] = 1.0f / static_cast<float>(backbufferDesc.Height);
            g_Runtime.context->UpdateSubresource(
                g_Runtime.frameConstants,
                0,
                nullptr,
                &constants,
                0,
                0);

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[DX11 Enhanced FXAA] presentation resources ready size=%ux%u format=%s preset=39 GREEN_AS_LUMA=1",
                backbufferDesc.Width,
                backbufferDesc.Height,
                DxgiFormatName(backbufferDesc.Format));
            return true;
        }

        bool ApplyFxaa(IDXGISwapChain* swapChain)
        {
            if (!swapChain ||
                !g_FxaaEnabled.load(std::memory_order_acquire) ||
                g_ShutdownRequested.load(std::memory_order_acquire) ||
                g_PermanentFault.load(std::memory_order_acquire))
            {
                return false;
            }

            std::lock_guard<std::mutex> lock(g_RuntimeMutex);

            ID3D11Device* device = nullptr;
            HRESULT hr = swapChain->GetDevice(
                __uuidof(ID3D11Device),
                reinterpret_cast<void**>(&device));
            if (FAILED(hr) || !device)
                return false;

            if (!EnsureDeviceResources(device))
            {
                SafeRelease(device);
                return false;
            }
            SafeRelease(device);

            ID3D11Texture2D* backbuffer = nullptr;
            hr = swapChain->GetBuffer(
                0,
                __uuidof(ID3D11Texture2D),
                reinterpret_cast<void**>(&backbuffer));
            if (FAILED(hr) || !backbuffer)
                return false;

            D3D11_TEXTURE2D_DESC backbufferDesc = {};
            backbuffer->GetDesc(&backbufferDesc);

            if (backbufferDesc.Width == 0 || backbufferDesc.Height == 0 ||
                !IsSupportedEncodedLdrFormat(backbufferDesc.Format))
            {
                if (!g_UnsupportedFormatLogged.exchange(true, std::memory_order_acq_rel))
                {
                    LogShimA(
                        LogLevel::Warn,
                        kComponent,
                        "[DX11 Enhanced FXAA] skipped unsupported presentation format=%s(%u) size=%ux%u; only ordinary 8-bit UNORM LDR targets are accepted because FXAA runs on encoded/non-linear RGB",
                        DxgiFormatName(backbufferDesc.Format),
                        static_cast<unsigned>(backbufferDesc.Format),
                        backbufferDesc.Width,
                        backbufferDesc.Height);
                }
                SafeRelease(backbuffer);
                return false;
            }

            g_UnsupportedFormatLogged.store(false, std::memory_order_release);
            if (!EnsureSourceResources(backbufferDesc))
            {
                SafeRelease(backbuffer);
                return false;
            }

            D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
            rtvDesc.Format = backbufferDesc.Format;
            if (backbufferDesc.SampleDesc.Count > 1)
            {
                rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
            }
            else
            {
                rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
                rtvDesc.Texture2D.MipSlice = 0;
            }

            ID3D11RenderTargetView* backbufferRtv = nullptr;
            hr = g_Runtime.device->CreateRenderTargetView(
                backbuffer,
                &rtvDesc,
                &backbufferRtv);
            if (FAILED(hr) || !backbufferRtv)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[DX11 Enhanced FXAA] backbuffer RTV creation failed hr=0x%08X",
                    static_cast<unsigned>(hr));
                SafeRelease(backbuffer);
                return false;
            }

            {
                // Capture before unbinding the game's targets. The RAII object
                // restores every state we mutate, including shader class
                // instances and predication, before Present reaches Ogre/DXGI.
                SavedContextState saved(g_Runtime.context);

                g_Runtime.context->SetPredication(nullptr, FALSE);
                g_Runtime.context->OMSetRenderTargets(0, nullptr, nullptr);

                if (backbufferDesc.SampleDesc.Count > 1)
                {
                    g_Runtime.context->ResolveSubresource(
                        g_Runtime.inputTexture,
                        0,
                        backbuffer,
                        0,
                        backbufferDesc.Format);
                }
                else
                {
                    g_Runtime.context->CopyResource(g_Runtime.inputTexture, backbuffer);
                }

                g_Runtime.context->OMSetRenderTargets(1, &backbufferRtv, nullptr);

                const FLOAT blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
                g_Runtime.context->OMSetBlendState(nullptr, blendFactor, 0xFFFFFFFFu);
                g_Runtime.context->OMSetDepthStencilState(g_Runtime.depthStencilState, 0);
                g_Runtime.context->RSSetState(g_Runtime.rasterizerState);

                D3D11_VIEWPORT viewport = {};
                viewport.TopLeftX = 0.0f;
                viewport.TopLeftY = 0.0f;
                viewport.Width = static_cast<float>(backbufferDesc.Width);
                viewport.Height = static_cast<float>(backbufferDesc.Height);
                viewport.MinDepth = 0.0f;
                viewport.MaxDepth = 1.0f;
                g_Runtime.context->RSSetViewports(1, &viewport);

                g_Runtime.context->IASetInputLayout(nullptr);
                g_Runtime.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                g_Runtime.context->VSSetShader(g_Runtime.vertexShader, nullptr, 0);
                g_Runtime.context->GSSetShader(nullptr, nullptr, 0);
                g_Runtime.context->HSSetShader(nullptr, nullptr, 0);
                g_Runtime.context->DSSetShader(nullptr, nullptr, 0);
                g_Runtime.context->PSSetShader(g_Runtime.pixelShader, nullptr, 0);
                g_Runtime.context->PSSetShaderResources(0, 1, &g_Runtime.inputSrv);
                g_Runtime.context->PSSetSamplers(0, 1, &g_Runtime.sampler);
                g_Runtime.context->PSSetConstantBuffers(0, 1, &g_Runtime.frameConstants);

                g_Runtime.context->Draw(3, 0);

                // Explicitly unbind our SRV before the saved game state is put
                // back. This also guarantees the input texture is no longer a
                // read dependency when the next frame copies into it.
                ID3D11ShaderResourceView* nullSrv = nullptr;
                g_Runtime.context->PSSetShaderResources(0, 1, &nullSrv);
            }

            // Never hold a swapchain-backbuffer reference across Present. DXGI
            // requires all such references to be released before ResizeBuffers;
            // retaining an RTV here would break fullscreen/resize transitions.
            SafeRelease(backbufferRtv);
            SafeRelease(backbuffer);
            return true;
        }

        HRESULT STDMETHODCALLTYPE HookPresent(
            IDXGISwapChain* self,
            UINT syncInterval,
            UINT flags)
        {
            if (!g_RealPresent)
                return E_FAIL;

            if ((flags & DXGI_PRESENT_TEST) != 0 ||
                !g_FxaaEnabled.load(std::memory_order_acquire) ||
                g_ShutdownRequested.load(std::memory_order_acquire))
            {
                return g_RealPresent(self, syncInterval, flags);
            }

            static thread_local bool s_InPresent = false;
            if (!s_InPresent)
            {
                s_InPresent = true;
                ApplyFxaa(self);
                s_InPresent = false;
            }

            return g_RealPresent(self, syncInterval, flags);
        }

        void AttachSwapChain(IDXGISwapChain* swapChain)
        {
            if (!swapChain)
                return;

            if (PatchComVtableEntry(
                    swapChain,
                    8,
                    &HookPresent,
                    g_RealPresent,
                    "IDXGISwapChain::Present"))
            {
                DXGI_SWAP_CHAIN_DESC desc = {};
                if (SUCCEEDED(swapChain->GetDesc(&desc)))
                {
                    LogShimA(
                        LogLevel::Info,
                        kComponent,
                        "[DX11 Enhanced FXAA] attached to swapchain=0x%p format=%s(%u) size=%ux%u buffers=%u; pass executes immediately before Present",
                        swapChain,
                        DxgiFormatName(desc.BufferDesc.Format),
                        static_cast<unsigned>(desc.BufferDesc.Format),
                        desc.BufferDesc.Width,
                        desc.BufferDesc.Height,
                        desc.BufferCount);
                }
            }
        }

        void InstallFactoryHooks(IDXGIFactory* factory)
        {
            if (!factory)
                return;

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
            InstallFactoryFromDevice(device);
        }

        HRESULT STDMETHODCALLTYPE HookFactoryCreateSwapChain(
            IDXGIFactory* self,
            IUnknown* device,
            DXGI_SWAP_CHAIN_DESC* desc,
            IDXGISwapChain** swapChain)
        {
            if (!g_RealFactoryCreateSwapChain)
                return E_FAIL;

            const HRESULT hr = g_RealFactoryCreateSwapChain(self, device, desc, swapChain);
            if (SUCCEEDED(hr) && swapChain && *swapChain)
                AttachSwapChain(*swapChain);

            // Another OpenShim DXGI observer can legitimately re-write this
            // shared factory vtable while it is inside our predecessor chain.
            // Reassert our top-level wrapper before returning so later
            // swapchains remain covered; the saved predecessor is unchanged.
            InstallFactoryHooks(self);
            return hr;
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
            if (!g_RealD3D11CreateDevice)
                return E_FAIL;

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

            if (SUCCEEDED(hr) && device && *device)
                InstallDeviceHooks(*device);
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
            if (!g_RealD3D11CreateDeviceAndSwapChain)
                return E_FAIL;

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
                if (device && *device)
                    InstallDeviceHooks(*device);
                if (swapChain && *swapChain)
                    AttachSwapChain(*swapChain);
            }
            return hr;
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
                "[DX11 Enhanced FXAA] D3D11 creation hooks installed=%u; DX9 and default-off stock paths remain untouched",
                installed);
        }

        unsigned __stdcall DiscoveryThreadProc(void*)
        {
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[DX11 Enhanced FXAA] experimental FXAA 3.11 requested; waiting for RenderSystem_Direct3D11.dll (DX9 is never hooked)");

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
                        "[DX11 Enhanced FXAA] Direct3D11 renderer found module=0x%p; enabling Enhanced-only presentation experiment",
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
                    "[DX11 Enhanced FXAA] Direct3D11 renderer not observed; no hooks installed (DX9 or renderer initialization not reached)");
            }
            return 0;
        }
    }

    void InitializeDx11EnhancedFxaa()
    {
        if (!FxaaRequested() || g_DiscoveryThread)
            return;

        g_FxaaEnabled.store(true, std::memory_order_release);
        g_PermanentFault.store(false, std::memory_order_release);
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
            g_FxaaEnabled.store(false, std::memory_order_release);
            LogShimA(
                LogLevel::Warn,
                kComponent,
                "[DX11 Enhanced FXAA] failed to start renderer discovery thread (err=%lu); feature disabled",
                GetLastError());
        }
    }

    void ShutdownDx11EnhancedFxaa()
    {
        g_FxaaEnabled.store(false, std::memory_order_release);
        g_ShutdownRequested.store(true, std::memory_order_release);

        if (g_DiscoveryThread)
        {
            WaitForSingleObject(reinterpret_cast<HANDLE>(g_DiscoveryThread), 1000);
            CloseHandle(reinterpret_cast<HANDLE>(g_DiscoveryThread));
            g_DiscoveryThread = 0;
        }

        std::lock_guard<std::mutex> lock(g_RuntimeMutex);
        g_Runtime.Reset();

        if (g_D3DCompilerModule)
        {
            FreeLibrary(g_D3DCompilerModule);
            g_D3DCompilerModule = nullptr;
            g_D3DCompile = nullptr;
        }
    }
}
