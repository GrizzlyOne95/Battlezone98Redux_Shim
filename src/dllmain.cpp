// dllmain.cpp
// BZR Open Shim - DLL entry point
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// This is the winmm.dll replacement entry point.
// On DLL_PROCESS_ATTACH:
//   1. Load the real System32/winmm.dll (so proxy exports work)
//   2. Load [third-party patch DLL] from the workshop/content path (same as [third-party proxy DLL] did)
//   3. Spawn background patch thread

#include "winmm_proxy.h"
#include "patcher.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <process.h>
#include <cstdio>

// ---------------------------------------------------------------------------
// Shim version number.
// [third-party patch DLL] checks "Expected Shim Version" against this value.
// From [third-party patch]_hopfix_decompiled.txt: the shim version is passed as param_1
// to FUN_1000eb30 and compared to a minimum expected value.
// Version 5: Added MapListFix1/2 probes for manual refresh path
// ---------------------------------------------------------------------------
static constexpr uint32_t SHIM_VERSION = 5;
static constexpr const char* SHIM_VERSION_STRING = "5";

// ---------------------------------------------------------------------------
// [third-party patch DLL] load path logic (reconstructed from [third-party proxy DLL] analysis and
// FUN_10001f40 in [third-party patch DLL] which calls FUN_10019300(param_1,"[third-party proxy DLL]")):
//
// [third-party proxy DLL] loads [third-party patch DLL] from:
//   ..\workshop\content\301650\<workshopid>\[third-party patch DLL]
// OR from the local addon path.
//
// For our replacement we load it from the same location that _requirefix.lua
// uses: the game's own folder, and if not there, from workshop paths.
// ---------------------------------------------------------------------------

static HMODULE   g_h[third-party patch]       = nullptr;
static uintptr_t g_PatchThread  = 0;

// Patch thread - wraps BZROpenShim::RunPatcher
static unsigned __stdcall PatchThreadProc(void*)
{
    BZROpenShim::RunPatcher(SHIM_VERSION);
    return 0;
}

// ---------------------------------------------------------------------------
// Try to find and load [third-party patch DLL].  We replicate the search order from
// [third-party proxy DLL] (rdata section decode + FUN_10001f40 analysis):
//   1. <game_dir>\[third-party patch DLL]
//   2. <game_dir>\..\workshop\content\301650\*\[third-party patch DLL]  (first found)
// ---------------------------------------------------------------------------
static HMODULE TryLoad[third-party patch]()
{
    // 1. Adjacent to BZR.exe
    HMODULE h = LoadLibraryA("[third-party patch DLL]");
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
        _snprintf_s(candidate, MAX_PATH, "%s%s\\[third-party patch DLL]", workshopBase, fd.cFileName);
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

        // Try to load [third-party patch DLL] (original closed-source) for compatibility.
        // If found, it will apply all patches itself - do NOT also run our
        // open-source patch thread, as both would race to patch the same
        // addresses and our expected_original checks would fail against
        // already-patched bytes.
        // When [third-party patch DLL] is absent, fall through to our open-source patcher.
        g_h[third-party patch] = TryLoad[third-party patch]();

        // Only spawn our patch thread if [third-party patch DLL] was NOT loaded.
        // Once all patches are implemented and verified, remove TryLoad[third-party patch]()
        // entirely and always run our thread.
        if (!g_h[third-party patch])
        {
            g_PatchThread = _beginthreadex(nullptr, 0, PatchThreadProc, nullptr, 0, nullptr);
        }
        else
        {
            OutputDebugStringA("BZR-OpenShim: [third-party patch DLL] loaded, deferring patching to it.\n");
        }
        break;

    case DLL_PROCESS_DETACH:
        if (g_h[third-party patch])
        {
            FreeLibrary(g_h[third-party patch]);
            g_h[third-party patch] = nullptr;
        }
        FreeRealWinmm();
        break;
    }
    return TRUE;
}
