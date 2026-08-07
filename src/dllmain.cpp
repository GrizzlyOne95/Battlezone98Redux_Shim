// dllmain.cpp
// BZR Open Shim - DLL entry point
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "winmm_proxy.h"
#include "bzr_hooks.h"
#include "crash_logger.h"
#include "net_optimizer.h"
#include "patcher.h"
#include "hook_engine.h"
#include "shim_log.h"
#include "file_io_hooks.h"
#include "autosave.h"
#include "BZROpenShim.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <process.h>
#include <cstdio>

static constexpr uint32_t SHIM_VERSION = 5;
static uintptr_t g_PatchThread = 0;

static unsigned __stdcall PatchThreadProc(void*)
{
    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Patch thread started");
    BZROpenShim::InstallCrashLogger();
    BZROpenShim::InitializeNetworkOptimizer();
    BZROpenShim::RunPatcher(SHIM_VERSION);

    // AutoSave stacks its main-thread update hook after the normal patch set so
    // it chains whichever world-update target (stock or OpenShim) is active.
    // Never install version-specific runtime addresses if the core compatibility
    // check failed.
    if (BZROpenShim::IsCompatibleGameVersion())
    {
        if (!BZROpenShim::InitializeAutoSave())
        {
            BZROpenShim::LogShimA(
                BZROpenShim::LogLevel::Warn,
                "dllmain",
                "Engine-level AutoSave initialization failed; normal manual saves remain available");
        }
    }

    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Patch thread exiting");
    return 0;
}

namespace BZROpenShim
{
    static void SetupLibrarySearchPath(HINSTANCE hModule)
    {
        char path[MAX_PATH] = {};
        if (GetModuleFileNameA(hModule, path, MAX_PATH))
        {
            char* lastBackslash = strrchr(path, 0x5C);
            if (lastBackslash)
            {
                *lastBackslash = 0;
                SetDllDirectoryA(path);
                LogShimA(LogLevel::Info, "dllmain", "Added DLL search path: %s", path);
            }
        }
    }

    static bool g_PatchingComplete = false;
    static uint32_t g_AppliedPatches = 0;
    static bool g_CompatibleVersion = false;

    BZRO_API uint32_t GetShimVersion() { return SHIM_VERSION; }
    BZRO_API bool IsCompatibleGameVersion() { return g_CompatibleVersion; }
    BZRO_API bool IsPatchingComplete() { return g_PatchingComplete; }
    BZRO_API uint32_t GetAppliedPatchCount() { return g_AppliedPatches; }

    void SetPatchingComplete(bool complete) { g_PatchingComplete = complete; }
    void SetAppliedPatchCount(uint32_t count) { g_AppliedPatches = count; }
    void SetCompatibleVersion(bool compatible) { g_CompatibleVersion = compatible; }

    BZRO_API void Initialize() {
        static bool s_Initialized = false;
        if (s_Initialized) return;
        BZROpenShim::InitializeShimLogger();
        HMODULE hMod = GetModuleHandleA("winmm.dll");
        if (hMod) BZROpenShim::SetupLibrarySearchPath(hMod);
        s_Initialized = true;
    }

    BZRO_API void Shutdown() {
        if (g_PatchThread)
        {
            BZROpenShim::SignalPatcherShutdown();
            WaitForSingleObject(reinterpret_cast<HANDLE>(g_PatchThread), 2000);
            CloseHandle(reinterpret_cast<HANDLE>(g_PatchThread));
            g_PatchThread = 0;
        }
        BZROpenShim::ShutdownAutoSave();
        BZROpenShim::FlushChunkFragmentEventsForShutdown();
        BZROpenShim::ShutdownNetworkOptimizer();
        FreeRealWinmm();
        BZROpenShim::ShutdownShimLogger();
    }
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        BZROpenShim::Initialize();
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "DLL_PROCESS_ATTACH hModule=0x%p reserved=0x%p shimVersion=%u", hModule, reserved, SHIM_VERSION);
        DisableThreadLibraryCalls(hModule);

        if (!LoadRealWinmm())
        {
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "dllmain", "LoadRealWinmm failed; aborting attach");
            return FALSE;
        }

        // The game creates BZLogger/Ogre logs immediately after process
        // attach, before the normal patch thread can reliably run.
        BZROpenShim::ApplyEarlyGameLogHooks();

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
        BZROpenShim::Shutdown();
        break;
    }
    return TRUE;
}
