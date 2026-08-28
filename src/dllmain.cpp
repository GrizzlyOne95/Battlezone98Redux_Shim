// dllmain.cpp
// BZR Open Shim - DLL entry point
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "winmm_proxy.h"
#include "bzr_hooks.h"
#include "render_profile_runtime.h"
#include "crash_logger.h"
#include "net_optimizer.h"
#include "bzrnet_instrumentation.h"
#include "patcher.h"
#include "hook_engine.h"
#include "shim_log.h"
#include "file_io_hooks.h"
#include "editor_view_order.h"
#include "autosave.h"
#include "dx11_colorspace_diagnostic.h"
#include "dx11_enhanced_fxaa.h"
#include "terrain_proxy.h"
#include "ogre_animation_profiler.h"
#include "native_cpu_sampler.h"
#include "pilot_fp_animation_trace.h"
#include "openshim_sdk_v2.h"
#include "openshim_updater.h"
#include "render_profile_runtime.h"
#include "ui_performance.h"
#include "ui_performance_hooks.h"
#include "ui_file_scan_hooks.h"
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
    BZROpenShim::UiPerf::Initialize();
    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Patch thread started");
    BZROpenShim::UiPerfHooks::Install();
    BZROpenShim::UiFileScan::Install();
    // Start renderer diagnostics/features immediately so their workers can
    // observe Ogre/D3D11 module creation before the renderer creates devices,
    // swapchains, entities, or begins normal animation submission.
    BZROpenShim::InitializePilotFpAnimationTrace();
    BZROpenShim::InitializeOgreAnimationProfiler();
    BZROpenShim::InitializeDx11ColorSpaceDiagnostic();
    BZROpenShim::InitializeDx11EnhancedFxaa();
    BZROpenShim::InstallCrashLogger();
    BZROpenShim::InitializeNetworkOptimizer();
    // Install BZRNet observation after the optimizer so it can chain through
    // the optimizer's existing IAT targets without changing network behavior.
    BZROpenShim::InitializeBzrNetInstrumentation();
    BZROpenShim::RunPatcher(SHIM_VERSION);

    // Renderer-profile ownership (backend observation, scheme-policy takeover,
    // capability reporting) initializes after the compatibility gate so the
    // takeover's address-dependent install sees the final gate verdict; its
    // backend-observation thread still watches the render-system modules load
    // well before the first mission.
    BZROpenShim::RenderProfiles::InitializeOgreRenderProfiles();

    // Phase 2 is safe to ask to initialize on every build: it is dormant by
    // default and independently verifies exact executable/Ogre hashes before
    // it resolves addresses or installs either terrain hook, so it does not
    // need the version gate below.
    BZROpenShim::InitializeTerrainProxyPhase2();

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

    // The sampling CPU profiler starts last so its first thread enumeration
    // sees the shim's own workers already running: they are threads of this
    // process and their cost has to be visible in the capture rather than
    // hidden from it. It is dormant unless OPENSHIM_PROFILE_NATIVE_CPU asks
    // for it.
    BZROpenShim::InitializeNativeCpuSampler();

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

    // Pins this module for the life of the process. OpenShim spawns worker
    // threads whose lifetimes are independent of any particular caller's
    // reference count, so an undisciplined FreeLibrary must never be able to
    // unmap code those threads are still executing. With the pin in place,
    // FreeLibrary becomes reference-count noise: the executable pages stay
    // mapped and a worker that outlives its join window keeps running in
    // mapped code instead of unmapped memory. This is the same
    // leak-rather-than-free policy the shutdown paths apply to shared buffers,
    // extended to the module itself.
    static void PinModuleForProcessLifetime(HINSTANCE hModule)
    {
        HMODULE pinned = nullptr;
        if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_PIN |
                                    GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                                reinterpret_cast<LPCWSTR>(hModule), &pinned))
        {
            LogShimA(LogLevel::Warn, "dllmain",
                     "Could not pin module for process lifetime (err=%lu); "
                     "explicit FreeLibrary during worker activity is unsupported",
                     GetLastError());
        }
    }

    static bool g_PatchingComplete = false;
    static uint32_t g_AppliedPatches = 0;
    static bool g_CompatibleVersion = false;

    BZRO_API uint32_t GetShimVersion() { return SHIM_VERSION; }
    BZRO_API bool IsCompatibleGameVersion() { return g_CompatibleVersion; }
    BZRO_API bool IsPatchingComplete() { return g_PatchingComplete; }
    BZRO_API uint32_t GetAppliedPatchCount() { return g_AppliedPatches; }

    void SetPatchingComplete(bool complete)
    {
        const bool changed = g_PatchingComplete != complete;
        g_PatchingComplete = complete;
        if (changed)
        {
            PublishOpenShimEvent(OpenShimEventType::PatchingCompleted,
                                 complete ? 1u : 0u,
                                 g_AppliedPatches,
                                 complete ? "OpenShim patching completed" : "OpenShim patching reset");
        }
    }

    void SetAppliedPatchCount(uint32_t count) { g_AppliedPatches = count; }

    void SetCompatibleVersion(bool compatible)
    {
        const bool changed = g_CompatibleVersion != compatible;
        g_CompatibleVersion = compatible;
        if (changed)
        {
            PublishOpenShimEvent(OpenShimEventType::CompatibilityChanged,
                                 compatible ? 1u : 0u,
                                 SHIM_VERSION,
                                 compatible ? "Compatible game build" : "Unsupported game build");
        }
    }

    BZRO_API void Initialize() {
        static bool s_Initialized = false;
        if (s_Initialized) return;
        BZROpenShim::InitializeShimLogger();
        BZROpenShim::InitializeOpenShimSdkV2();
        HMODULE hMod = GetModuleHandleA("winmm.dll");
        if (hMod) BZROpenShim::SetupLibrarySearchPath(hMod);
        s_Initialized = true;
    }

    // Full joined shutdown. This waits for the patch thread, the native CPU
    // sampler and the network workers (up to 5 s and 1.5 s per worker), so it
    // is only valid from a normal execution context. Never call this from
    // DllMain: the detach path runs under the loader lock, where waiting for a
    // worker that needs loader service can deadlock, and a timed-out worker
    // would keep executing code from a module the caller is unloading.
    //
    // Unload contract: a host that intends to FreeLibrary this module must
    // call Shutdown() first, from one of its own normal threads. If the module
    // is unloaded without that call, DLL_PROCESS_DETACH only signals (never
    // joins) and relies on the process-lifetime pin to keep mapped whatever
    // the workers still touch.
    BZRO_API void Shutdown() {
        if (g_PatchThread)
        {
            BZROpenShim::SignalPatcherShutdown();
            WaitForSingleObject(reinterpret_cast<HANDLE>(g_PatchThread), 2000);
            CloseHandle(reinterpret_cast<HANDLE>(g_PatchThread));
            g_PatchThread = 0;
        }
        BZROpenShim::ShutdownNativeCpuSampler();
        BZROpenShim::ShutdownOpenShimUpdater();
        BZROpenShim::ShutdownOpenShimSdkV2();
        BZROpenShim::ShutdownPilotFpAnimationTrace();
        BZROpenShim::ShutdownOgreAnimationProfiler();
        // Stop the mutating presentation experiment before the read-only DX11
        // observer it can chain with, then release its private D3D resources.
        BZROpenShim::ShutdownDx11EnhancedFxaa();
        BZROpenShim::ShutdownDx11ColorSpaceDiagnostic();
        BZROpenShim::ShutdownTerrainProxyPhase2();
        BZROpenShim::ShutdownAutoSave();
        BZROpenShim::FlushChunkFragmentEventsForShutdown();
        // Stop the upper observation layer before the lower Winsock optimizer
        // it chains through, then let the existing optimizer flush its logs.
        BZROpenShim::ShutdownBzrNetInstrumentation();
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
        // Capture the pristine command line BEFORE anything can run: stock's
        // parser strtok()s the GetCommandLineA() buffer in place once main()
        // starts, and the backend-selection seam must still see /renderer:...
        // tokens no matter which thread wins the startup race. Pure bounded
        // string copy - loader-lock safe.
        BZROpenShim::RenderProfiles::CaptureCommandLineSnapshot();
        BZROpenShim::Initialize();
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "DLL_PROCESS_ATTACH hModule=0x%p reserved=0x%p shimVersion=%u", hModule, reserved, SHIM_VERSION);
        DisableThreadLibraryCalls(hModule);

        if (!LoadRealWinmm())
        {
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "dllmain", "LoadRealWinmm failed; aborting attach");
            return FALSE;
        }

        BZROpenShim::PinModuleForProcessLifetime(hModule);

        // The game creates BZLogger/Ogre logs immediately after process
        // attach, before the normal patch thread can reliably run.
        BZROpenShim::ApplyEarlyGameLogHooks();

        // Seam A: arm ONLY the startup interception here (loader-lock-bounded
        // identity checks + one IAT pointer swap). The backend transport runs
        // later, on the game thread, inside the intercepted startup
        // Ogre::ConfigFile::load — deterministic even when Steam reaches
        // graphics initialization in ~1 s. Heavy work (INI parsing,
        // filesystem, logging) must never run under the loader lock.
        // Do not route the arm result through LogShimA here: its locks/CRT
        // formatting are not safe under the loader lock. The seam records a
        // fixed status enum and the patch thread reports it after attach.
        BZROpenShim::RenderProfiles::InstallStartupBackendSeam();

        // Both patch sites are global constructors that run from the CRT's
        // _initterm before main, so this cannot wait for the patch thread.
        BZROpenShim::ApplyEditorOverheadPlacementOrderFix();

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
        if (reserved != nullptr)
        {
            // Process termination (reserved is the termination flag, not an
            // LPVOID). The OS has already terminated every other thread and
            // the loader will not return here; joins are impossible and
            // cleanup is unnecessary because the whole address space, handle
            // table and kernel state are going away together. Do no work that
            // could touch a lock or a runtime object another dying thread
            // still held.
            OutputDebugStringA("BZR-OpenShim: DLL_PROCESS_DETACH (process termination)\n");
            break;
        }
        // Explicit FreeLibrary without a prior Shutdown() call. The detach
        // thread owns the loader lock, so this path must not wait on workers
        // (deadlock) and must not run logger/heap work that a live worker
        // could be holding or feeding (lock-order cycle through the loader
        // lock). Signal the patch loop to wind down -- a plain atomic store --
        // and rely on the process-lifetime pin: the module's code pages stay
        // mapped for the workers the caller chose not to drain.
        OutputDebugStringA("BZR-OpenShim: DLL_PROCESS_DETACH (explicit unload without Shutdown(); "
                           "workers left running in pinned module)\n");
        BZROpenShim::SignalPatcherShutdown();
        break;
    }
    return TRUE;
}
