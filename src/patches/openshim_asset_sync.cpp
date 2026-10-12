#include "openshim_asset_sync.h"

#include "openshim_asset_sets.h"
#include "openshim_update_internal.h"
#include "openshim_update_manifest.h"
#include "render_profile_resources.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <process.h>

#include <atomic>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "assetsync";
        constexpr DWORD kShutdownWaitMs = 10000;

        uintptr_t g_Thread = 0;
        std::atomic<bool> g_ShutdownRequested{ false };

        bool ReadRunningVersion(std::string& version)
        {
            HMODULE module = nullptr;
            if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                    GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                    reinterpret_cast<LPCWSTR>(&StartOpenShimAssetSync), &module))
                return false;
            std::wstring path(MAX_PATH, L'\0');
            for (;;)
            {
                const DWORD length = GetModuleFileNameW(module, path.data(), static_cast<DWORD>(path.size()));
                if (length == 0)
                    return false;
                if (length < path.size())
                {
                    path.resize(length);
                    break;
                }
                path.resize(path.size() * 2);
            }
            return UpdaterDetail::ReadFileVersion(path, version);
        }

        void RunSync()
        {
            std::filesystem::path itemDir;
            std::string error;
            if (!UpdaterDetail::FindWorkshopItemDirectory(itemDir, error))
            {
                LogShimA(LogLevel::Info, kComponent, "No Workshop item to sync assets from: %s", error.c_str());
                return;
            }

            std::ifstream input(itemDir / L"OpenShimManifest.lua", std::ios::binary);
            const std::string text((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
            OpenShimUpdateManifest manifest;
            if (text.empty() || text.size() > 256 * 1024 ||
                !ParseOpenShimUpdateManifest(text, manifest, error))
            {
                LogShimA(LogLevel::Info, kComponent, "Workshop manifest not usable for asset sync: %s",
                         error.empty() ? "unreadable" : error.c_str());
                return;
            }

            OpenShimAssetSets sets;
            if (!ParseOpenShimAssetSets(text, sets, error))
            {
                LogShimA(LogLevel::Warn, kComponent, "Workshop asset sets refused: %s", error.c_str());
                return;
            }
            for (const std::string& name : sets.ignored)
                LogShimA(LogLevel::Info, kComponent, "Ignoring unknown asset set '%s'", name.c_str());
            if (sets.sets.empty())
            {
                LogShimA(LogLevel::Info, kComponent, "Workshop manifest declares no asset sets");
                return;
            }

            std::string running;
            int order = 0;
            if (!ReadRunningVersion(running) ||
                !CompareOpenShimVersions(manifest.version, running, order) || order != 0)
            {
                LogShimA(LogLevel::Info, kComponent,
                         "Skipping asset sync: Workshop manifest is %s, running build is %s",
                         manifest.version.c_str(), running.empty() ? "unknown" : running.c_str());
                return;
            }

            const std::filesystem::path gameDir = UpdaterDetail::GetGameRoot();
            if (gameDir.empty())
                return;
            const OpenShimAssetSetValidator rendererValidator =
                [](const std::filesystem::path& dir, std::string& problem)
                {
                    return RenderProfiles::ValidateDeployedResourceSetAt(dir, problem);
                };

            for (const OpenShimAssetSet& set : sets.sets)
            {
                if (g_ShutdownRequested.load(std::memory_order_acquire))
                    return;
                const OpenShimAssetSyncOutcome outcome = SyncOpenShimAssetSet(
                    itemDir, gameDir, set, set.name == "renderer" ? rendererValidator : nullptr);
                switch (outcome.result)
                {
                case OpenShimAssetSyncResult::Current:
                    LogShimA(LogLevel::Info, kComponent, "%s: already current", set.name.c_str());
                    break;
                case OpenShimAssetSyncResult::Installed:
                    LogShimA(LogLevel::Info, kComponent, "%s: installed %u files",
                             set.name.c_str(), outcome.filesInstalled);
                    break;
                case OpenShimAssetSyncResult::Refused:
                    LogShimA(LogLevel::Warn, kComponent, "%s: refused (%s)",
                             set.name.c_str(), outcome.detail.c_str());
                    break;
                case OpenShimAssetSyncResult::Deferred:
                    LogShimA(LogLevel::Warn, kComponent, "%s: deferred, will retry next start (%s)",
                             set.name.c_str(), outcome.detail.c_str());
                    break;
                }
            }
        }

        unsigned __stdcall SyncThreadProc(void*)
        {
            try
            {
                RunSync();
            }
            catch (...)
            {
                LogShimA(LogLevel::Warn, kComponent, "Asset sync stopped on an unexpected error");
            }
            return 0;
        }
    }

    void StartOpenShimAssetSync()
    {
        if (g_Thread)
            return;
        g_ShutdownRequested.store(false, std::memory_order_release);
        g_Thread = _beginthreadex(nullptr, 0, SyncThreadProc, nullptr, 0, nullptr);
        if (!g_Thread)
            LogShimA(LogLevel::Warn, kComponent, "Could not start the asset sync worker");
    }

    void ShutdownOpenShimAssetSync()
    {
        g_ShutdownRequested.store(true, std::memory_order_release);
        if (!g_Thread)
            return;
        HANDLE thread = reinterpret_cast<HANDLE>(g_Thread);
        // Joined means joined: the worker runs code from this module, so
        // returning while it still copies would let the unload pull it out
        // from under it. The bounded wait only decides when to say so.
        if (WaitForSingleObject(thread, kShutdownWaitMs) == WAIT_TIMEOUT)
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "Asset sync worker still running after %lu ms; waiting for it", kShutdownWaitMs);
            WaitForSingleObject(thread, INFINITE);
        }
        CloseHandle(thread);
        g_Thread = 0;
    }
}
