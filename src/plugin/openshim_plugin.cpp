// openshim_plugin.cpp
// BZR Open Shim - the runtime, as a BZLoader plugin.
//
// This is what used to be the back half of dllmain.cpp. The patch worker and
// every subsystem it starts now live behind BZPlugin_Load rather than behind
// DLL_PROCESS_ATTACH, which is a strict improvement: none of it was ever
// loader-lock-safe, and it only ever ran on a thread spawned to escape that.
//
// Ownership rule that matters here: the plugin does NOT shut down its host.
// BZLoader owns the plugin lifecycle and calls BZPlugin_Shutdown; the plugin
// cleans itself up and returns. The bootstrap then tears down BZLoader, the
// real WinMM and the logger, in that order, which is why the plugin can still
// log its entire shutdown sequence.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "bzloader_plugin.h"
#include "openshim_bootstrap_api.h"
#include "openshim_plugin_bootstrap.h"
#include "openshim_sdk_provider.h"
#include "shim_log_sink.h"
#include "startup_backend_seam.h"

#include "bzr_hooks.h"
#include "render_profile_runtime.h"
#include "crash_logger.h"
#include "net_optimizer.h"
#include "bzrnet_instrumentation.h"
#include "patcher.h"
#include "hook_engine.h"
#include "shim_log.h"
#include "file_io_hooks.h"
#include "autosave.h"
#include "dx11_colorspace_diagnostic.h"
#include "dx11_enhanced_fxaa.h"
#include "dx11_scene_depth.h"
#include "terrain_proxy.h"
#include "ogre_animation_profiler.h"
#include "native_cpu_sampler.h"
#include "pilot_fp_animation_trace.h"
#include "walker_cockpit_trace.h"
#include "openshim_sdk_v2.h"
#include "openshim_updater.h"
#include "render_profile_runtime.h"
#include "ui_performance.h"
#include "ui_performance_hooks.h"
#include "ui_file_scan_hooks.h"
#include "mp_faction_restrict.h"
#include "mp_ready_diagnostic.h"
#include "BZROpenShim.h"
#include "openshim_sdk_provider.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <process.h>
#include <atomic>
#include <cstdio>
#include <exception>

static constexpr uint32_t SHIM_VERSION = 5;
static uintptr_t g_PatchThread = 0;

// One stage of the patch thread under its own exception barrier. A C++
// exception escaping the thread is std::terminate, which takes the game down
// at launch with nothing in the log to say why. The stages below are
// independent installers that each check their own preconditions, so a stage
// that throws (a library error in an initializer, a malformed config file it
// parses) is logged by name and the later stages still run. SEH faults are
// not C++ exceptions and stay with the crash logger.
template <typename Fn>
static void RunPatchStage(const char* stage, Fn&& fn)
{
    try
    {
        fn();
    }
    catch (const std::exception& e)
    {
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "plugin",
            "Patch stage %s threw %s; later stages continue", stage, e.what());
    }
    catch (...)
    {
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "plugin",
            "Patch stage %s threw a non-standard exception; later stages continue", stage);
    }
}
#define PATCH_STAGE(call) RunPatchStage(#call, [&] { call; })

static unsigned __stdcall PatchThreadProc(void*)
{
    PATCH_STAGE(BZROpenShim::UiPerf::Initialize());
    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "plugin", "Patch thread started");
    // BZLoader is emphatically not started from here any more. The loader owns
    // this module's lifecycle -- it is what called BZPlugin_Load to get us
    // running -- so a call back up into it would invert the dependency graph.
    // The bootstrap starts the loader; the loader starts us.
    // Start renderer diagnostics/features immediately so their workers can
    // observe Ogre/D3D11 module creation before the renderer creates devices,
    // swapchains, entities, or begins normal animation submission.
    PATCH_STAGE(BZROpenShim::InitializePilotFpAnimationTrace());
    PATCH_STAGE(BZROpenShim::InitializeWalkerCockpitTrace());
    PATCH_STAGE(BZROpenShim::InitializeOgreAnimationProfiler());
    PATCH_STAGE(BZROpenShim::InitializeDx11ColorSpaceDiagnostic());
    PATCH_STAGE(BZROpenShim::InitializeDx11EnhancedFxaa());
    // Phase A depth qualification: observation only, and off unless asked
    // for. Starts after the FXAA path so that when both are enabled the
    // creation-hook chain runs FXAA first, mirroring the shutdown order.
    PATCH_STAGE(BZROpenShim::InitializeDx11SceneDepth());
    PATCH_STAGE(BZROpenShim::InstallCrashLogger());
    PATCH_STAGE(BZROpenShim::InitializeNetworkOptimizer());
    // Install BZRNet observation after the optimizer so it can chain through
    // the optimizer's existing IAT targets without changing network behavior.
    PATCH_STAGE(BZROpenShim::InitializeBzrNetInstrumentation());
    PATCH_STAGE(BZROpenShim::RunPatcher(SHIM_VERSION));

    // Multiplayer starting-vehicle list faction policy. Installs after the
    // patcher so scripts/patches.json resolves are loaded; the hook itself is
    // inert until [Network] StockFactionsOnly is turned on, and the loader it
    // intercepts only runs when a multiplayer screen builds its vehicle list.
    PATCH_STAGE(BZROpenShim::MpFactionRestrict::InstallMpFactionRestrictIfPossible());

    // Explains a "Not Ready" multiplayer entry on the main menu. Read-only: it
    // reproduces the shell's own readiness decision from the same globals and
    // logs which term failed, because the stock UI has no way to say. Its own
    // worker waits for platform init, so ordering here is not significant.
    PATCH_STAGE(BZROpenShim::InitializeMpReadyDiagnostic());

    // Shell profiler detours must not touch SteamStub-managed executable pages
    // before platform detection and code settlement. UiPerfHooks installs them
    // immediately on GOG and defers Steam's writes until a live MainScreen is
    // observed on the UI thread. File-scan hooks follow so trigger-file access
    // is suppressed without classifying startup work as a menu transition.
    PATCH_STAGE(BZROpenShim::UiPerfHooks::Install());
    PATCH_STAGE(BZROpenShim::UiFileScan::Install());

    // Renderer-profile ownership (backend observation, scheme-policy takeover,
    // capability reporting) initializes after the compatibility gate so the
    // takeover's address-dependent install sees the final gate verdict; its
    // backend-observation thread still watches the render-system modules load
    // well before the first mission.
    PATCH_STAGE(BZROpenShim::RenderProfiles::InitializeOgreRenderProfiles());

    // Phase 2 is safe to ask to initialize on every build: it is dormant by
    // default and independently verifies exact executable/Ogre hashes before
    // it resolves addresses or installs either terrain hook, so it does not
    // need the version gate below.
    PATCH_STAGE(BZROpenShim::InitializeTerrainProxyPhase2());

    // AutoSave stacks its main-thread update hook after the normal patch set so
    // it chains whichever world-update target (stock or OpenShim) is active.
    // Never install version-specific runtime addresses if the core compatibility
    // check failed.
    RunPatchStage("BZROpenShim::InitializeAutoSave()", [] {
        if (!BZROpenShim::IsCompatibleGameVersion()) return;
        if (!BZROpenShim::InitializeAutoSave())
        {
            BZROpenShim::LogShimA(
                BZROpenShim::LogLevel::Warn,
                "dllmain",
                "Engine-level AutoSave initialization failed; normal manual saves remain available");
        }
    });

    // The sampling CPU profiler starts last so its first thread enumeration
    // sees the shim's own workers already running: they are threads of this
    // process and their cost has to be visible in the capture rather than
    // hidden from it. It is dormant unless OPENSHIM_PROFILE_NATIVE_CPU asks
    // for it.
    PATCH_STAGE(BZROpenShim::InitializeNativeCpuSampler());

    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "dllmain", "Patch thread exiting");
    return 0;
}

namespace BZROpenShim
{
    static bool g_PatchingComplete = false;
    static uint32_t g_AppliedPatches = 0;
    static bool g_CompatibleVersion = false;

    // The runtime's own view of its state. winmm.dll exports the same names
    // and forwards to these through the SDK provider table, so an external
    // caller sees one answer whichever module it asked.
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

    void RuntimeShutdown()
    {
        if (g_PatchThread)
        {
            BZROpenShim::SignalPatcherShutdown();
            WaitForSingleObject(reinterpret_cast<HANDLE>(g_PatchThread), 2000);
            CloseHandle(reinterpret_cast<HANDLE>(g_PatchThread));
            g_PatchThread = 0;
        }
        BZROpenShim::UiPerfHooks::Shutdown();
        BZROpenShim::UiFileScan::Shutdown();
        BZROpenShim::ShutdownNativeCpuSampler();
        BZROpenShim::ShutdownOpenShimUpdater();
        BZROpenShim::ShutdownOpenShimSdkV2();
        BZROpenShim::ShutdownWalkerCockpitTrace();
        BZROpenShim::ShutdownPilotFpAnimationTrace();
        BZROpenShim::ShutdownOgreAnimationProfiler();
        // Stop the mutating presentation experiment before the read-only DX11
        // observer it can chain with, then release its private D3D resources.
        BZROpenShim::ShutdownDx11SceneDepth();
        BZROpenShim::ShutdownDx11EnhancedFxaa();
        BZROpenShim::ShutdownDx11ColorSpaceDiagnostic();
        BZROpenShim::ShutdownTerrainProxyPhase2();
        BZROpenShim::ShutdownAutoSave();
        BZROpenShim::FlushChunkFragmentEventsForShutdown();
        // Stop the upper observation layer before the lower Winsock optimizer
        // it chains through, then let the existing optimizer flush its logs.
        BZROpenShim::ShutdownBzrNetInstrumentation();
        BZROpenShim::ShutdownNetworkOptimizer();
    }
}

namespace BZROpenShim::Plugin
{
    namespace
    {
        std::atomic<const OpenShimBootstrapApiV1*> g_BootstrapApi{nullptr};

        // Routes this module's formatted log lines to the bootstrap's sink,
        // which owns openshim.log. Only a finished UTF-8 string crosses.
        void __cdecl PluginLogSink(uint32_t level, const char* component,
                                   const char* message)
        {
            const OpenShimBootstrapApiV1* api =
                g_BootstrapApi.load(std::memory_order_acquire);
            if (api != nullptr && api->logMessage != nullptr)
                api->logMessage(level, component, message);
        }
    }

    const OpenShimBootstrapApiV1* BootstrapApi()
    {
        return g_BootstrapApi.load(std::memory_order_acquire);
    }

    bool AcquireBootstrapApi()
    {
        // winmm.dll is what loaded us, so it is in the module list already.
        // Never LoadLibrary here.
        const HMODULE proxy = GetModuleHandleW(L"winmm.dll");
        if (proxy == nullptr)
            return false;

        const auto getApi = reinterpret_cast<OpenShimBootstrap_GetApiFn>(
            GetProcAddress(proxy, "OpenShimBootstrap_GetApi"));
        if (getApi == nullptr)
            return false;

        const OpenShimBootstrapApiV1* api = getApi(OPENSHIM_BOOTSTRAP_API_V1);
        if (api == nullptr || api->structSize < sizeof(OpenShimBootstrapApiV1))
            return false;

        g_BootstrapApi.store(api, std::memory_order_release);
        return true;
    }
}

// ---- BZLoader plugin ABI ---------------------------------------------------

extern "C" BZLOADER_API int32_t BZLOADER_CALL BZPlugin_Query(
    uint32_t hostAbiVersion, BZPluginInfo* outInfo)
{
    if (!outInfo || hostAbiVersion != BZLOADER_ABI_VERSION) return 0;

    const uint32_t capacity = outInfo->structSize;
    if (capacity < BZLOADER_PLUGIN_INFO_V1_SIZE) return 0;
    const uint32_t written =
        capacity < sizeof(BZPluginInfo) ? capacity : (uint32_t)sizeof(BZPluginInfo);
    memset(outInfo, 0, written);

    outInfo->requiredLoaderAbi = BZLOADER_ABI_VERSION;
    outInfo->pluginId = "org.openshim.runtime";
    outInfo->pluginName = "OpenShim runtime";
    outInfo->pluginVersion = "5";
    // Redux only. Everything this module does is anchored to Battlezone 98
    // Redux addresses and Ogre build facts; loading it anywhere else would be
    // patching an unknown image.
    outInfo->supportedGameMask = BZ_GAME_MASK_BATTLEZONE_98_REDUX;

    if (written >= BZLOADER_FIELD_END(BZPluginInfo, loadPriority))
        outInfo->loadPriority = 0;

    outInfo->structSize = written;
    return 1;
}

extern "C" BZLOADER_API int32_t BZLOADER_CALL BZPlugin_Load(const BZHostApi* host)
{
    if (!host || host->structSize < BZLOADER_HOST_API_V1_SIZE ||
        host->abiVersion != BZLOADER_ABI_VERSION)
        return 0;

    // The bootstrap table first: without it nothing this module logs would go
    // anywhere, and the renderer runtime could not learn what the startup seam
    // already decided. A failure here is transactional -- nothing has been
    // installed yet, so returning 0 leaves the process exactly as it was.
    if (!BZROpenShim::Plugin::AcquireBootstrapApi())
        return 0;

    BZROpenShim::SetShimLogSink(&BZROpenShim::Plugin::PluginLogSink);
    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "plugin",
                          "OpenShim runtime loaded by BZLoader (game=%u)",
                          host->gameId);

    // Create the worker before anything is installed into winmm.dll, but do
    // not let it run yet. The provider tables below hand winmm.dll function
    // pointers that live inside this module; once they are installed the load
    // can no longer be undone, because a host that unloads us after a failed
    // BZPlugin_Load would leave the executable's CreateFile IAT entries
    // routed through unmapped memory. Making thread creation the last
    // fallible step keeps "return 0" transactional again.
    g_PatchThread = _beginthreadex(nullptr, 0, PatchThreadProc, nullptr, CREATE_SUSPENDED, nullptr);
    if (!g_PatchThread)
    {
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "plugin",
                              "_beginthreadex failed (err=%lu); undoing load",
                              GetLastError());
        BZROpenShim::SetShimLogSink(nullptr);
        return 0;
    }

    // Providers for the two bootstrap seams, then the public SDK surface that
    // winmm.dll's export thunks forward into.
    BZROpenShim::InstallFileIoProvider();
    BZROpenShim::SdkProvider::InstallBuiltIn();

    BZROpenShim::InitializeOpenShimSdkV2();

    ResumeThread(reinterpret_cast<HANDLE>(g_PatchThread));
    return 1;
}

extern "C" BZLOADER_API void BZLOADER_CALL BZPlugin_Shutdown(void)
{
    // Deliberately does not touch BZLoader, the real WinMM, or the logger.
    // The loader owns this module's lifecycle and the bootstrap owns those
    // three; a plugin shutting down its own host would invert the dependency
    // graph. Logging still works throughout, because the bootstrap closes
    // openshim.log only after BZLoader returns from here.
    BZROpenShim::RuntimeShutdown();
    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "plugin",
                          "OpenShim runtime shutdown complete");
}

BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID)
{
    // Minimal by contract: this module initialises only from BZPlugin_Load.
    if (reason == DLL_PROCESS_ATTACH)
        DisableThreadLibraryCalls(module);
    return TRUE;
}
