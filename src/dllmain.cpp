// dllmain.cpp
// BZR Open Shim - DLL entry point
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// This is the winmm.dll replacement entry point.
// On DLL_PROCESS_ATTACH:
//   1. Load the real System32/winmm.dll (so proxy exports work)
//   2. Load _bzcp.dll from the workshop/content path (same as winmm.bin did)
//   3. Spawn background patch thread

#include "winmm_proxy.h"
#include "patcher.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <process.h>
#include <cstdio>

// ---------------------------------------------------------------------------
// Shim version number.
// _bzcp.dll checks "Expected Shim Version" against this value.
// From bzcp_hopfix_decompiled.txt: the shim version is passed as param_1
// to FUN_1000eb30 and compared to a minimum expected value.
// Version 4: Extended frame candidate search for manual refresh
// ---------------------------------------------------------------------------
static constexpr uint32_t SHIM_VERSION = 4;
static constexpr const char* SHIM_VERSION_STRING = "2";

// ---------------------------------------------------------------------------
// _bzcp.dll load path logic (reconstructed from winmm.bin analysis and
// FUN_10001f40 in _bzcp.dll which calls FUN_10019300(param_1,"winmm.bin")):
//
// winmm.bin loads _bzcp.dll from:
//   ..\workshop\content\301650\<workshopid>\_bzcp.dll
// OR from the local addon path.
//
// For our replacement we load it from the same location that _requirefix.lua
// uses: the game's own folder, and if not there, from workshop paths.
// ---------------------------------------------------------------------------

static HMODULE   g_hBZCP       = nullptr;
static uintptr_t g_PatchThread  = 0;

// Patch thread - wraps BZROpenShim::RunPatcher
static unsigned __stdcall PatchThreadProc(void*)
{
    BZROpenShim::RunPatcher(SHIM_VERSION);
    return 0;
}

// ---------------------------------------------------------------------------
// Try to find and load _bzcp.dll.  We replicate the search order from
// winmm.bin (rdata section decode + FUN_10001f40 analysis):
//   1. <game_dir>\_bzcp.dll
//   2. <game_dir>\..\workshop\content\301650\*\_bzcp.dll  (first found)
// ---------------------------------------------------------------------------
static HMODULE TryLoadBZCP()
{
    // 1. Adjacent to BZR.exe
    HMODULE h = LoadLibraryA("_bzcp.dll");
    if (h) return h;

    // 2. Workshop paths
    char exePath[MAX_PATH] = {};
    GetModuleFileNameA(nullptr, exePath, MAX_PATH);

    // Strip filename from path
    char* lastSlash = strrchr(exePath, '\\');
    if (!lastSlash) return nullptr;
    *(lastSlash + 1) = '\0';

    // Build workshop base: <exedir>\..\workshop\content\301650
    char workshopBase[MAX_PATH] = {};
    _snprintf_s(workshopBase, MAX_PATH, "%s..\\workshop\\content\\301650\\", exePath);

    // Glob subdirectories
    char searchPath[MAX_PATH] = {};
    _snprintf_s(searchPath, MAX_PATH, "%s*", workshopBase);

    WIN32_FIND_DATAA fd = {};
    HANDLE hFind = FindFirstFileA(searchPath, &fd);
    if (hFind == INVALID_HANDLE_VALUE) return nullptr;

    do
    {
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) continue;
        if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0) continue;

        char candidate[MAX_PATH] = {};
        _snprintf_s(candidate, MAX_PATH, "%s%s\\_bzcp.dll", workshopBase, fd.cFileName);
        h = LoadLibraryA(candidate);
        if (h) break;

    } while (FindNextFileA(hFind, &fd));

    FindClose(hFind);
    return h;
}

// ---------------------------------------------------------------------------
// DLL entry point
// ---------------------------------------------------------------------------
BOOL WINAPI DllMain(HINSTANCE /*hModule*/, DWORD reason, LPVOID)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        // Load real winmm.dll so our proxy exports actually work
        if (!LoadRealWinmm())
            return FALSE;

        // Verify we are loading
        OutputDebugStringA("BZR-OpenShim: DLL_PROCESS_ATTACH\n");

        // Try to load _bzcp.dll (original closed-source) for compatibility.
        // If found, it will apply all patches itself - do NOT also run our
        // open-source patch thread, as both would race to patch the same
        // addresses and our expected_original checks would fail against
        // already-patched bytes.
        // When _bzcp.dll is absent, fall through to our open-source patcher.
        g_hBZCP = TryLoadBZCP();

        // Only spawn our patch thread if _bzcp.dll was NOT loaded.
        // Once all patches are implemented and verified, remove TryLoadBZCP()
        // entirely and always run our thread.
        if (!g_hBZCP)
        {
            g_PatchThread = _beginthreadex(nullptr, 0, PatchThreadProc, nullptr, 0, nullptr);
        }
        else
        {
            OutputDebugStringA("BZR-OpenShim: _bzcp.dll loaded, deferring patching to it.\n");
        }
        break;

    case DLL_PROCESS_DETACH:
        if (g_hBZCP)
        {
            FreeLibrary(g_hBZCP);
            g_hBZCP = nullptr;
        }
        FreeRealWinmm();
        break;
    }
    return TRUE;
}
