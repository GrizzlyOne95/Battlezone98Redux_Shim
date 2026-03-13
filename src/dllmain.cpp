// dllmain.cpp
// BZR Open Shim - DLL entry point
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// This is the winmm.dll replacement entry point.
// On DLL_PROCESS_ATTACH:
//   1. Load the real System32/winmm.dll (so proxy exports work)
//   2. Spawn the background patch thread

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
// Shim version number for the standalone OpenShim patch thread.
// Version 5: native three-stage hop-fix pipeline (save, reselect, replay rows)
// ---------------------------------------------------------------------------
static constexpr uint32_t SHIM_VERSION = 5;

static uintptr_t g_PatchThread  = 0;

// Patch thread - wraps BZROpenShim::RunPatcher
static unsigned __stdcall PatchThreadProc(void*)
{
    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Patch thread started");
    BZROpenShim::InitializeNetworkOptimizer();
    BZROpenShim::RunPatcher(SHIM_VERSION);
    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Patch thread exiting");
    return 0;
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

        g_PatchThread = _beginthreadex(nullptr, 0, PatchThreadProc, nullptr, 0, nullptr);
        if (!g_PatchThread)
        {
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "dllmain", "_beginthreadex failed (err=%lu)", GetLastError());
            return FALSE;
        }
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Patch thread handle created: 0x%p", reinterpret_cast<void*>(g_PatchThread));
        break;

    case DLL_PROCESS_DETACH:
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "DLL_PROCESS_DETACH reserved=0x%p", reserved);
        FreeRealWinmm();
        BZROpenShim::ShutdownShimLogger();
        break;
    }
    return TRUE;
}
