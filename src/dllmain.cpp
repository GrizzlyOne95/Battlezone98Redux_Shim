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
#include "net_optimizer.h"
#include "patcher.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <process.h>
#include <cstdio>

// ---------------------------------------------------------------------------
// Shim version number.
// [third-party patch DLL] checks "Expected Shim Version" against this value.
// From [third-party patch]_hopfix_decompiled.txt: the shim version is passed as param_1
// to FUN_1000eb30 and compared to a minimum expected value.
// Version 5: native three-stage hop-fix pipeline (save, reselect, replay rows)
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
    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Patch thread started ([third-party patch]Loaded=%d)", g_h[third-party patch] ? 1 : 0);
    BZROpenShim::InitializeNetworkOptimizer();
    if (!g_h[third-party patch])
        BZROpenShim::RunPatcher(SHIM_VERSION);
    else
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "[third-party patch DLL] already loaded; skipping open-source patcher thread work");
    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Patch thread exiting");
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
    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Trying to load adjacent [third-party patch DLL]");
    HMODULE h = LoadLibraryA("[third-party patch DLL]");
    if (h)
    {
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Loaded adjacent [third-party patch DLL] at 0x%p", h);
        return h;
    }

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
    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Searching workshop path for [third-party patch DLL] under %s", workshopBase);

    // Glob subdirectories
    char searchPath[MAX_PATH] = {};
    _snprintf_s(searchPath, MAX_PATH, "%s*", workshopBase);

    WIN32_FIND_DATAA fd = {};
    HANDLE hFind = FindFirstFileA(searchPath, &fd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Warn, "dllmain", "Workshop search path unavailable: %s (err=%lu)", searchPath, GetLastError());
        return nullptr;
    }

    do
    {
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) continue;
        if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0) continue;

        char candidate[MAX_PATH] = {};
        _snprintf_s(candidate, MAX_PATH, "%s%s\\[third-party patch DLL]", workshopBase, fd.cFileName);
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Debug, "dllmain", "Trying workshop candidate %s", candidate);
        h = LoadLibraryA(candidate);
        if (h)
        {
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Loaded workshop [third-party patch DLL] from %s at 0x%p", candidate, h);
            break;
        }

    } while (FindNextFileA(hFind, &fd));

    FindClose(hFind);
    if (!h)
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "No [third-party patch DLL] found; OpenShim patcher will handle patching");
    return h;
}

// ---------------------------------------------------------------------------
// DLL entry point
// ---------------------------------------------------------------------------
BOOL WINAPI DllMain(HINSTANCE hModule, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        BZROpenShim::InitializeShimLogger();
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "DLL_PROCESS_ATTACH hModule=0x%p reserved=0x%p shimVersion=%u", hModule, reserved, SHIM_VERSION);
        DisableThreadLibraryCalls(hModule);

        // Load real winmm.dll so our proxy exports actually work
        if (!LoadRealWinmm())
        {
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "dllmain", "LoadRealWinmm failed; aborting attach");
            return FALSE;
        }

        // Verify we are loading
        OutputDebugStringA("BZR-OpenShim: DLL_PROCESS_ATTACH\n");

        // Try to load [third-party patch DLL] (original closed-source) for compatibility.
        // If found, it will apply all patches itself - do NOT also run our
        // open-source patch thread, as both would race to patch the same
        // addresses and our expected_original checks would fail against
        // already-patched bytes.
        // When [third-party patch DLL] is absent, fall through to our open-source patcher.
        g_h[third-party patch] = TryLoad[third-party patch]();

        g_PatchThread = _beginthreadex(nullptr, 0, PatchThreadProc, nullptr, 0, nullptr);
        if (!g_PatchThread)
        {
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "dllmain", "_beginthreadex failed (err=%lu)", GetLastError());
            return FALSE;
        }
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Patch thread handle created: 0x%p", reinterpret_cast<void*>(g_PatchThread));
        if (g_h[third-party patch])
        {
            OutputDebugStringA("BZR-OpenShim: [third-party patch DLL] loaded, deferring patching to it.\n");
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "[third-party patch DLL] loaded; compatibility mode active");
        }
        break;

    case DLL_PROCESS_DETACH:
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "DLL_PROCESS_DETACH reserved=0x%p", reserved);
        if (g_h[third-party patch])
        {
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Freeing loaded [third-party patch DLL] handle 0x%p", g_h[third-party patch]);
            FreeLibrary(g_h[third-party patch]);
            g_h[third-party patch] = nullptr;
        }
        FreeRealWinmm();
        BZROpenShim::ShutdownShimLogger();
        break;
    }
    return TRUE;
}
