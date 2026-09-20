// OpenShim SDK forwarding bridge. See include/openshim_sdk_bridge.h.

#include "openshim_sdk_bridge.h"
#include "shim_log.h"

#include <atomic>

namespace
{
    // Written once during startup, read by every export thunk on arbitrary
    // threads. Release/acquire so a reader that sees the pointer also sees the
    // fully constructed table behind it.
    std::atomic<const OpenShimSdkProviderTable*> g_Provider{nullptr};
    std::atomic<uint64_t> g_UnavailableCalls{0};
}

namespace BZROpenShim::SdkBridge
{
    bool InstallProvider(const OpenShimSdkProviderTable* table)
    {
        if (!table)
        {
            LogShimA(LogLevel::Error, "sdkbridge",
                     "Refusing to install a null OpenShim provider table");
            return false;
        }
        // A table smaller than its own first field cannot be read at all, and
        // one larger than this build knows about came from a newer provider:
        // accept it, because the layout is append-only and every read is
        // bounded by structSize anyway.
        if (table->structSize < sizeof(uint32_t))
        {
            LogShimA(LogLevel::Error, "sdkbridge",
                     "Refusing an OpenShim provider table that reports structSize=%u",
                     table->structSize);
            return false;
        }

        const OpenShimSdkProviderTable* previous = g_Provider.exchange(
            table, std::memory_order_release);
        if (previous && previous != table)
        {
            LogShimA(LogLevel::Warn, "sdkbridge",
                     "Replaced an already-installed OpenShim provider table");
        }
        LogShimA(LogLevel::Info, "sdkbridge",
                 "OpenShim provider installed (structSize=%u, this build knows %u)",
                 table->structSize,
                 static_cast<uint32_t>(sizeof(OpenShimSdkProviderTable)));
        return true;
    }

    bool InstallProviderFromModule(HMODULE pluginModule)
    {
        if (!pluginModule)
        {
            LogShimA(LogLevel::Error, "sdkbridge",
                     "No plugin module handle; OpenShim exports stay unavailable");
            return false;
        }

        // Deliberately GetProcAddress and never LoadLibrary. An export thunk
        // can run on any thread at any time, including while the loader lock
        // is held by someone else, so nothing on this path may load a module.
        // The caller passes a module that is already loaded.
        using GetTableFn = const OpenShimSdkProviderTable*(__cdecl*)();
        const auto getTable = reinterpret_cast<GetTableFn>(
            GetProcAddress(pluginModule, "OpenShimSdkProvider_GetTable"));
        if (!getTable)
        {
            LogShimA(LogLevel::Error, "sdkbridge",
                     "Plugin does not export OpenShimSdkProvider_GetTable (err=%lu)",
                     GetLastError());
            return false;
        }

        // One call fetches all of the entries at once, so no individual export
        // ever has to resolve itself and nothing is looked up per call.
        const OpenShimSdkProviderTable* table = getTable();
        if (!table)
        {
            LogShimA(LogLevel::Error, "sdkbridge",
                     "OpenShimSdkProvider_GetTable returned no table");
            return false;
        }
        return InstallProvider(table);
    }

    const OpenShimSdkProviderTable* Provider()
    {
        return g_Provider.load(std::memory_order_acquire);
    }

    void NoteUnavailableCall()
    {
        g_UnavailableCalls.fetch_add(1, std::memory_order_relaxed);
    }

    uint64_t UnavailableCallCount()
    {
        return g_UnavailableCalls.load(std::memory_order_relaxed);
    }
}
