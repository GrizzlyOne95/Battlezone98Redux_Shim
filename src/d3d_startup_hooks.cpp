// d3d_startup_hooks.cpp
// BZR Open Shim - early Direct3D startup hooks
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "d3d_startup_hooks.h"
#include "patcher.h"

#include <Windows.h>
#include <d3d9.h>
#include <strsafe.h>
#include <cwchar>

namespace BZROpenShim
{
    using PFN_Direct3DCreate9 = IDirect3D9* (WINAPI*)(UINT);
    using PFN_Direct3DCreate9Ex = HRESULT (WINAPI*)(UINT, IDirect3D9Ex**);

    static PFN_Direct3DCreate9 g_RealDirect3DCreate9 = nullptr;
    static PFN_Direct3DCreate9Ex g_RealDirect3DCreate9Ex = nullptr;
    static volatile LONG g_EarlySubtitlesLoadState = 0;

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
            if (!targetModule)
                return false;

            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(targetModule);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return false;

            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<uint8_t*>(targetModule) + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return false;

            const DWORD importRva = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
            if (!importRva)
                return false;

            auto* importDesc = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(reinterpret_cast<uint8_t*>(targetModule) + importRva);
            while (importDesc->Name)
            {
                const char* importedModule = reinterpret_cast<const char*>(targetModule) + importDesc->Name;
                if (_stricmp(importedModule, moduleName) == 0)
                {
                    auto* origThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(
                        reinterpret_cast<uint8_t*>(targetModule) +
                        (importDesc->OriginalFirstThunk ? importDesc->OriginalFirstThunk : importDesc->FirstThunk));
                    auto* thunk = reinterpret_cast<IMAGE_THUNK_DATA*>(
                        reinterpret_cast<uint8_t*>(targetModule) + importDesc->FirstThunk);

                    while (origThunk->u1.AddressOfData)
                    {
                        if (!IMAGE_SNAP_BY_ORDINAL(origThunk->u1.Ordinal))
                        {
                            auto* importByName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(
                                reinterpret_cast<uint8_t*>(targetModule) + origThunk->u1.AddressOfData);
                            if (strcmp(reinterpret_cast<const char*>(importByName->Name), funcName) == 0)
                            {
                                DWORD oldProtect = 0;
                                auto** iatEntry = reinterpret_cast<void**>(&thunk->u1.Function);
                                if (!VirtualProtect(iatEntry, sizeof(void*), PAGE_READWRITE, &oldProtect))
                                    return false;

                                if (oldFunc)
                                    *oldFunc = *iatEntry;
                                *iatEntry = newFunc;
                                VirtualProtect(iatEntry, sizeof(void*), oldProtect, &oldProtect);
                                return true;
                            }
                        }

                        ++origThunk;
                        ++thunk;
                    }

                    return false;
                }

                ++importDesc;
            }

            return false;
        }

        static bool BuildEarlySubtitlesPath(wchar_t (&path)[MAX_PATH])
        {
            path[0] = L'\0';

            wchar_t exePath[MAX_PATH] = {};
            const DWORD len = GetModuleFileNameW(nullptr, exePath, MAX_PATH);
            if (len == 0 || len >= MAX_PATH)
                return false;

            wchar_t* lastSlash = wcsrchr(exePath, L'\\');
            if (!lastSlash)
                return false;

            *(lastSlash + 1) = L'\0';
            if (FAILED(StringCchPrintfW(path, MAX_PATH, L"%saddon\\campaignReimagined\\subtitles.dll", exePath)))
                return false;

            return true;
        }

        static void EnsureEarlySubtitlesLoaded(const wchar_t* reason)
        {
            const LONG previous = InterlockedCompareExchange(&g_EarlySubtitlesLoadState, 1, 0);
            if (previous != 0)
                return;

            wchar_t subtitlesPath[MAX_PATH] = {};
            if (!BuildEarlySubtitlesPath(subtitlesPath))
            {
                Log(L"[D3D] Failed to build early subtitles.dll path for reason=%ls\n", reason ? reason : L"<unknown>");
                return;
            }

            if (GetFileAttributesW(subtitlesPath) == INVALID_FILE_ATTRIBUTES)
            {
                Log(L"[D3D] Early subtitles.dll path not found: %ls (reason=%ls)\n", subtitlesPath, reason ? reason : L"<unknown>");
                return;
            }

            if (GetModuleHandleW(subtitlesPath))
            {
                Log(L"[D3D] subtitles.dll already loaded before early load attempt: %ls\n", subtitlesPath);
                return;
            }

            Log(L"[D3D] Loading subtitles.dll early from %ls (reason=%ls)\n", subtitlesPath, reason ? reason : L"<unknown>");
            HMODULE subtitlesModule = LoadLibraryW(subtitlesPath);
            if (subtitlesModule)
            {
                Log(L"[D3D] Early subtitles.dll load succeeded: module=0x%p\n", subtitlesModule);
            }
            else
            {
                Log(L"[D3D] Early subtitles.dll load FAILED: err=%lu path=%ls\n", GetLastError(), subtitlesPath);
            }
        }

        static IDirect3D9* WINAPI Hooked_Direct3DCreate9(UINT sdkVersion)
        {
            Log(L"[D3D] Direct3DCreate9 intercepted (sdk=%u)\n", sdkVersion);
            EnsureEarlySubtitlesLoaded(L"Direct3DCreate9");

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
            EnsureEarlySubtitlesLoaded(L"Direct3DCreate9Ex");

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
                    if (_wcsicmp(moduleName, L"RenderSystem_Direct3D9.dll") == 0)
                    {
                        EnsureEarlySubtitlesLoaded(L"RenderSystem_Direct3D9 loaded");
                    }
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
