// dllmain.cpp
// BZR Open Shim - the bootstrap entry point.
//
// winmm.dll is boring infrastructure now. It forwards the real WinMM API,
// arms the seams that genuinely have to exist before the CRT runs, owns
// openshim.log, and starts BZLoader. Everything that used to happen on the
// patch thread lives in plugins/openshim.dll behind BZPlugin_Load.
//
// What stays here does so for one reason only: it cannot wait for a plugin.
//
//   * the command-line snapshot, because stock's parser strtok()s the
//     GetCommandLineA() buffer in place once main() starts;
//   * the startup renderer seam, because the intercepted ConfigFile::load is
//     the game's own read of Ogre.cfg and the decision point is gone once it
//     returns (see startup_backend_seam.h);
//   * the early file-I/O seam, because the game creates BZLogger.txt and its
//     Ogre log almost immediately (see bootstrap_file_io.h);
//   * the editor constructor fix and the CLI delimiter fix, because both
//     patch sites run from the CRT's _initterm before main.
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "winmm_proxy.h"
#include "shim_log.h"
#include "bootstrap_file_io.h"
#include "bzloader_bootstrap.h"
#include "cli_multiparam_parser.h"
#include "editor_view_order.h"
#include "render_profile_runtime.h"
#include "BZROpenShim.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <process.h>

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

    // Pins this module for the life of the process. The loader, the plugin and
    // their workers all execute code that lives here, and their lifetimes are
    // independent of any particular caller's reference count, so an
    // undisciplined FreeLibrary must never be able to unmap it. With the pin
    // in place FreeLibrary becomes reference-count noise.
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

    // Loads BZLoader, which in turn loads plugins/openshim.dll. Deliberately a
    // worker: DllMain must never LoadLibrary, and the loader's own discovery,
    // logging and filesystem work has no business running under the loader
    // lock. The seams above are already armed by the time this runs, so a slow
    // or missing plugin costs compatibility features, not correctness.
    static unsigned __stdcall LoaderThreadProc(void*)
    {
        LogShimA(LogLevel::Info, "dllmain", "Loader thread started");
        if (!InitializeBZLoader())
        {
            LogShimA(LogLevel::Warn, "dllmain",
                     "BZLoader unavailable; the bootstrap seams remain active but "
                     "the OpenShim runtime did not load");
        }
        return 0;
    }

    static uintptr_t g_LoaderThread = 0;

    BZRO_API void Initialize()
    {
        static bool s_Initialized = false;
        if (s_Initialized) return;
        InitializeShimLogger();
        HMODULE hMod = GetModuleHandleA("winmm.dll");
        if (hMod) SetupLibrarySearchPath(hMod);
        s_Initialized = true;
    }

    // Full joined shutdown, and the only ordering that is correct:
    // BZLoader calls BZPlugin_Shutdown so the runtime can drain its workers
    // and still log while doing it, then the real WinMM is released, then the
    // log file is closed. A host that intends to FreeLibrary this module calls
    // this first, from one of its own normal threads. Never from DllMain: the
    // detach path holds the loader lock, where waiting on a worker that needs
    // loader service can deadlock.
    BZRO_API void Shutdown()
    {
        if (g_LoaderThread)
        {
            WaitForSingleObject(reinterpret_cast<HANDLE>(g_LoaderThread), 5000);
            CloseHandle(reinterpret_cast<HANDLE>(g_LoaderThread));
            g_LoaderThread = 0;
        }
        ShutdownBZLoader();
        FreeRealWinmm();
        ShutdownShimLogger();
    }
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        // Capture the pristine command line BEFORE anything can run: stock's
        // parser strtok()s the GetCommandLineA() buffer in place once main()
        // starts, and the startup renderer seam must still see /renderer:...
        // tokens no matter which thread wins the startup race. Pure bounded
        // string copy - loader-lock safe.
        BZROpenShim::RenderProfiles::CaptureCommandLineSnapshot();
        BZROpenShim::Initialize();
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain",
                              "DLL_PROCESS_ATTACH hModule=0x%p reserved=0x%p",
                              hModule, reserved);
        DisableThreadLibraryCalls(hModule);

        if (!LoadRealWinmm())
        {
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "dllmain",
                                  "LoadRealWinmm failed; aborting attach");
            return FALSE;
        }

        BZROpenShim::PinModuleForProcessLifetime(hModule);

        // The game creates BZLogger/Ogre logs immediately after process
        // attach, long before any plugin could be hosted.
        BZROpenShim::BootstrapFileIo::ApplyEarlyGameLogHooks();

        // Arm ONLY the startup interception here (loader-lock-bounded identity
        // checks plus one IAT pointer swap). The transport itself runs later,
        // on the game thread, inside the intercepted startup
        // Ogre::ConfigFile::load - deterministic even when Steam reaches
        // graphics initialization in ~1 s. Heavy work must never run under the
        // loader lock, and the arm result is a fixed status enum rather than a
        // log call for the same reason.
        BZROpenShim::RenderProfiles::InstallStartupBackendSeam();

        // Both patch sites are global constructors that run from the CRT's
        // _initterm before main, so neither can wait for a worker.
        BZROpenShim::ApplyEditorOverheadPlacementOrderFix();

        // Stock's command-line parser runs from WinMain immediately after CRT
        // startup, so the delimiter it tokenises with has to be corrected here.
        // Writes 4 bytes in .data only.
        BZROpenShim::ApplyCliMultiParameterOptionFix();

        OutputDebugStringA("BZR-OpenShim: DLL_PROCESS_ATTACH\n");

        BZROpenShim::g_LoaderThread =
            _beginthreadex(nullptr, 0, BZROpenShim::LoaderThreadProc, nullptr, 0, nullptr);
        if (!BZROpenShim::g_LoaderThread)
        {
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "dllmain",
                                  "_beginthreadex failed (err=%lu)", GetLastError());
            return FALSE;
        }
        break;

    case DLL_PROCESS_DETACH:
        if (reserved != nullptr)
        {
            // Process termination. The OS has already terminated every other
            // thread and the loader will not return here; joins are impossible
            // and cleanup is unnecessary because the whole address space is
            // going away together. Do no work that could touch a lock another
            // dying thread still held.
            OutputDebugStringA("BZR-OpenShim: DLL_PROCESS_DETACH (process termination)\n");
            break;
        }
        // Explicit FreeLibrary without a prior Shutdown(). The detach thread
        // owns the loader lock, so this path must not wait on workers and must
        // not run logger/heap work a live worker could be holding. Rely on the
        // process-lifetime pin instead.
        OutputDebugStringA("BZR-OpenShim: DLL_PROCESS_DETACH (explicit unload without "
                           "Shutdown(); workers left running in pinned module)\n");
        break;
    }
    return TRUE;
}
