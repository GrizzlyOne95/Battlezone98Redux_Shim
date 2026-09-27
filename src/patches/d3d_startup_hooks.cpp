// d3d_startup_hooks.cpp
// BZR Open Shim - early Direct3D startup hooks
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "d3d_startup_hooks.h"
#include "iat_patch.h"
#include "patcher.h"

#include <Windows.h>
#include <d3d9.h>

namespace BZROpenShim
{
    using PFN_Direct3DCreate9 = IDirect3D9* (WINAPI*)(UINT);
    using PFN_Direct3DCreate9Ex = HRESULT (WINAPI*)(UINT, IDirect3D9Ex**);

    static PFN_Direct3DCreate9 g_RealDirect3DCreate9 = nullptr;
    static PFN_Direct3DCreate9Ex g_RealDirect3DCreate9Ex = nullptr;

    namespace
    {
        static bool PatchIAT(HMODULE targetModule, const char* moduleName, const char* funcName, void* newFunc, void** oldFunc);
        static IDirect3D9* WINAPI Hooked_Direct3DCreate9(UINT sdkVersion);
        static HRESULT WINAPI Hooked_Direct3DCreate9Ex(UINT sdkVersion, IDirect3D9Ex** outD3D9Ex);

        static bool PatchD3DImportsForModule(HMODULE module, const wchar_t* moduleLabel)
        {
            if (!module)
                return false;

            bool anyHooked = false;

            const bool hooked9 = PatchIAT(
                module,
                "d3d9.dll",
                "Direct3DCreate9",
                reinterpret_cast<void*>(Hooked_Direct3DCreate9),
                reinterpret_cast<void**>(&g_RealDirect3DCreate9));
            const bool hooked9Ex = PatchIAT(
                module,
                "d3d9.dll",
                "Direct3DCreate9Ex",
                reinterpret_cast<void*>(Hooked_Direct3DCreate9Ex),
                reinterpret_cast<void**>(&g_RealDirect3DCreate9Ex));

            Log(
                L"[D3D] Module %ls hook results: Direct3DCreate9=%ls Direct3DCreate9Ex=%ls base=0x%p\n",
                moduleLabel ? moduleLabel : L"<unknown>",
                hooked9 ? L"installed" : L"not installed",
                hooked9Ex ? L"installed" : L"not installed",
                module);

            anyHooked = hooked9 || hooked9Ex;
            return anyHooked;
        }

        static bool PatchIAT(HMODULE targetModule, const char* moduleName, const char* funcName, void* newFunc, void** oldFunc)
        {
            // The previous entry is kept only the first time. A second pass over the
            // same module would otherwise record our own hook as the "real" function.
            return IatPatch::PatchImport(targetModule, moduleName, funcName, newFunc, oldFunc) ==
                IatPatch::Result::Patched;
        }

        static IDirect3D9* WINAPI Hooked_Direct3DCreate9(UINT sdkVersion)
        {
            Log(L"[D3D] Direct3DCreate9 intercepted (sdk=%u)\n", sdkVersion);

            if (!g_RealDirect3DCreate9)
            {
                Log(L"[D3D] Direct3DCreate9 original pointer missing\n");
                return nullptr;
            }

            IDirect3D9* result = g_RealDirect3DCreate9(sdkVersion);
            Log(L"[D3D] Direct3DCreate9 returned d3d=0x%p\n", result);
            return result;
        }

        static HRESULT WINAPI Hooked_Direct3DCreate9Ex(UINT sdkVersion, IDirect3D9Ex** outD3D9Ex)
        {
            Log(L"[D3D] Direct3DCreate9Ex intercepted (sdk=%u)\n", sdkVersion);

            if (!g_RealDirect3DCreate9Ex)
            {
                Log(L"[D3D] Direct3DCreate9Ex original pointer missing\n");
                return E_POINTER;
            }

            const HRESULT hr = g_RealDirect3DCreate9Ex(sdkVersion, outD3D9Ex);
            Log(L"[D3D] Direct3DCreate9Ex returned hr=0x%08X d3dEx=0x%p\n", hr, outD3D9Ex ? *outD3D9Ex : nullptr);
            return hr;
        }
    }

    void ApplyD3DStartupHooks()
    {
        Log(L"=========== D3D STARTUP HOOKS ===========\n");

        HMODULE hMain = GetModuleHandleW(nullptr);
        if (!hMain)
        {
            Log(L"[D3D] GetModuleHandleW(nullptr) failed; cannot install startup hooks\n");
            return;
        }

        PatchD3DImportsForModule(hMain, L"battlezone98redux.exe");

        const wchar_t* d3dModulesToWatch[] = {
            L"RenderSystem_Direct3D9.dll",
            L"d3d9.dll"
        };

        for (const wchar_t* moduleName : d3dModulesToWatch)
        {
            bool hooked = false;
            for (int attempt = 0; attempt < 200; ++attempt)
            {
                HMODULE module = GetModuleHandleW(moduleName);
                if (module != nullptr)
                {
                    hooked = PatchD3DImportsForModule(module, moduleName);
                    break;
                }

                Sleep(25);
            }

            if (!hooked)
            {
                Log(L"[D3D] Module %ls was not hooked during startup watch window\n", moduleName);
            }
        }
    }
}
