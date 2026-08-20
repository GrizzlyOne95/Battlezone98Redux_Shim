// OpenShim SDK v2: stable function-table ABI, queued native events, and a
// read-only developer snapshot surface.

#include "openshim_sdk_v2.h"

#include "bzr_hooks.h"
#include "native_ui.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <array>
#include <atomic>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace
    {
        constexpr size_t kEventQueueCapacity = 256;

        SRWLOCK g_EventQueueLock = SRWLOCK_INIT;
        std::array<OpenShimEvent, kEventQueueCapacity> g_EventQueue = {};
        size_t g_EventQueueHead = 0;
        size_t g_EventQueueCount = 0;
        uint64_t g_NextEventSequence = 1;
        uint64_t g_DroppedEventCount = 0;
        std::atomic<bool> g_SdkInitialized{ false };
        std::atomic<uint32_t> g_BzrDistribution{
            static_cast<uint32_t>(BzrDistribution::Unknown) };

        struct EventQueueStats
        {
            uint32_t pending = 0;
            uint64_t dropped = 0;
        };

        static EventQueueStats ReadEventQueueStats()
        {
            EventQueueStats stats = {};
            AcquireSRWLockShared(&g_EventQueueLock);
            stats.pending = static_cast<uint32_t>(g_EventQueueCount);
            stats.dropped = g_DroppedEventCount;
            ReleaseSRWLockShared(&g_EventQueueLock);
            return stats;
        }

        static int32_t __cdecl ApiPollEvent(OpenShimEvent* outEvent)
        {
            if (!outEvent)
                return 0;

            AcquireSRWLockExclusive(&g_EventQueueLock);
            if (g_EventQueueCount == 0)
            {
                ReleaseSRWLockExclusive(&g_EventQueueLock);
                return 0;
            }

            *outEvent = g_EventQueue[g_EventQueueHead];
            g_EventQueueHead = (g_EventQueueHead + 1) % kEventQueueCapacity;
            --g_EventQueueCount;
            ReleaseSRWLockExclusive(&g_EventQueueLock);
            return 1;
        }

        static uint32_t __cdecl ApiGetPendingEventCount()
        {
            return ReadEventQueueStats().pending;
        }

        static uint64_t __cdecl ApiGetDroppedEventCount()
        {
            return ReadEventQueueStats().dropped;
        }

        static void __cdecl ApiClearEventQueue()
        {
            AcquireSRWLockExclusive(&g_EventQueueLock);
            g_EventQueueHead = 0;
            g_EventQueueCount = 0;
            ReleaseSRWLockExclusive(&g_EventQueueLock);
        }

        static uint32_t __cdecl ApiGetShimVersion()
        {
            return GetShimVersion();
        }

        static uint32_t __cdecl ApiGetSdkVersion()
        {
            return SDK_VERSION;
        }

        static uint64_t __cdecl ApiGetCapabilities()
        {
            return GetOpenShimCapabilityMask();
        }

        static uint8_t __cdecl ApiIsCompatibleGameVersion()
        {
            return IsCompatibleGameVersion() ? 1u : 0u;
        }

        static uint8_t __cdecl ApiIsPatchingComplete()
        {
            return IsPatchingComplete() ? 1u : 0u;
        }

        static uint32_t __cdecl ApiGetAppliedPatchCount()
        {
            return GetAppliedPatchCount();
        }

        static int32_t __cdecl ApiCaptureDeveloperSnapshot(OpenShimDeveloperSnapshot* outSnapshot)
        {
            return OpenShimCaptureDeveloperSnapshot(outSnapshot);
        }

        static int32_t __cdecl ApiLogDeveloperSnapshot()
        {
            return OpenShimLogDeveloperSnapshot();
        }

        static const OpenShimNativeUiApiV1* __cdecl ApiGetNativeUiApi(uint32_t requestedVersion)
        {
            return GetOpenShimNativeUiApi(requestedVersion);
        }

        static const OpenShimApiV2& GetApiV2Table()
        {
            static const OpenShimApiV2 api = []
            {
                OpenShimApiV2 value = {};
                value.structSize = sizeof(OpenShimApiV2);
                value.apiVersion = SDK_API_V2;
                value.capabilities = GetOpenShimCapabilityMask();
                value.getShimVersion = ApiGetShimVersion;
                value.getSdkVersion = ApiGetSdkVersion;
                value.getCapabilities = ApiGetCapabilities;
                value.isCompatibleGameVersion = ApiIsCompatibleGameVersion;
                value.isPatchingComplete = ApiIsPatchingComplete;
                value.getAppliedPatchCount = ApiGetAppliedPatchCount;
                value.pollEvent = ApiPollEvent;
                value.getPendingEventCount = ApiGetPendingEventCount;
                value.getDroppedEventCount = ApiGetDroppedEventCount;
                value.clearEventQueue = ApiClearEventQueue;
                value.captureDeveloperSnapshot = ApiCaptureDeveloperSnapshot;
                value.logDeveloperSnapshot = ApiLogDeveloperSnapshot;
                value.getNativeUiApi = ApiGetNativeUiApi;
                return value;
            }();
            return api;
        }
    }

    BzrDistribution GetBzrDistribution()
    {
        const uint32_t raw = g_BzrDistribution.load(std::memory_order_acquire);
        switch (raw)
        {
        case static_cast<uint32_t>(BzrDistribution::GOG):
            return BzrDistribution::GOG;
        case static_cast<uint32_t>(BzrDistribution::Steam):
            return BzrDistribution::Steam;
        default:
            return BzrDistribution::Unknown;
        }
    }

    void SetBzrDistribution(BzrDistribution distribution)
    {
        g_BzrDistribution.store(static_cast<uint32_t>(distribution),
                                std::memory_order_release);
    }

    uint64_t GetOpenShimCapabilityMask()
    {
        return OPENSHIM_CAP_STATUS |
               OPENSHIM_CAP_EVENT_QUEUE |
               OPENSHIM_CAP_DEVELOPER_INSPECTOR |
               OPENSHIM_CAP_NATIVE_UI;
    }

    void InitializeOpenShimSdkV2()
    {
        bool expected = false;
        if (!g_SdkInitialized.compare_exchange_strong(expected, true))
            return;

        SetBzrDistribution(BzrDistribution::Unknown);
        PublishOpenShimEvent(OpenShimEventType::ShimInitialized,
                             GetShimVersion(),
                             SDK_VERSION,
                             "OpenShim SDK v2 initialized");
        LogShimA(LogLevel::Info,
                 "sdk_v2",
                 "SDK v2 initialized capabilities=0x%llX queueCapacity=%u",
                 static_cast<unsigned long long>(GetOpenShimCapabilityMask()),
                 static_cast<unsigned>(kEventQueueCapacity));
    }

    void ShutdownOpenShimSdkV2()
    {
        if (!g_SdkInitialized.load())
            return;

        PublishOpenShimEvent(OpenShimEventType::ShutdownStarted,
                             0,
                             0,
                             "OpenShim shutdown started");
        ShutdownNativeUi();
        SetBzrDistribution(BzrDistribution::Unknown);
        g_SdkInitialized.store(false);
    }

    void PublishOpenShimEvent(OpenShimEventType type,
                              uint64_t arg0,
                              uint64_t arg1,
                              const char* text)
    {
        if (!g_SdkInitialized.load())
            return;

        OpenShimEvent event = {};
        event.structSize = sizeof(OpenShimEvent);
        event.apiVersion = SDK_API_V2;
        event.type = static_cast<uint32_t>(type);
        event.threadId = GetCurrentThreadId();
        event.tickMs = GetTickCount64();
        event.arg0 = arg0;
        event.arg1 = arg1;

        LARGE_INTEGER qpc = {};
        if (QueryPerformanceCounter(&qpc))
            event.qpc = static_cast<uint64_t>(qpc.QuadPart);

        if (text && *text)
        {
            strncpy_s(event.text, sizeof(event.text), text, _TRUNCATE);
        }

        AcquireSRWLockExclusive(&g_EventQueueLock);
        event.sequence = g_NextEventSequence++;

        if (g_EventQueueCount == kEventQueueCapacity)
        {
            g_EventQueueHead = (g_EventQueueHead + 1) % kEventQueueCapacity;
            --g_EventQueueCount;
            ++g_DroppedEventCount;
        }

        const size_t tail = (g_EventQueueHead + g_EventQueueCount) % kEventQueueCapacity;
        g_EventQueue[tail] = event;
        ++g_EventQueueCount;
        ReleaseSRWLockExclusive(&g_EventQueueLock);
    }

    bool CaptureDeveloperSnapshot(OpenShimDeveloperSnapshot& outSnapshot)
    {
        outSnapshot = {};
        outSnapshot.structSize = sizeof(OpenShimDeveloperSnapshot);
        outSnapshot.apiVersion = SDK_API_V2;
        outSnapshot.capabilities = GetOpenShimCapabilityMask();
        outSnapshot.shimVersion = GetShimVersion();
        outSnapshot.sdkVersion = SDK_VERSION;
        outSnapshot.processId = GetCurrentProcessId();
        outSnapshot.captureThreadId = GetCurrentThreadId();
        outSnapshot.appliedPatchCount = GetAppliedPatchCount();
        outSnapshot.compatibleGameVersion = IsCompatibleGameVersion() ? 1u : 0u;
        outSnapshot.patchingComplete = IsPatchingComplete() ? 1u : 0u;

        const EventQueueStats stats = ReadEventQueueStats();
        outSnapshot.pendingEventCount = stats.pending;
        outSnapshot.droppedEventCount = stats.dropped;

        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        if (IsCompatibleGameVersion() && TryGetLocalPlayerWorldPosition(x, y, z))
        {
            outSnapshot.localPlayerResolved = 1u;
            outSnapshot.localPlayerX = x;
            outSnapshot.localPlayerY = y;
            outSnapshot.localPlayerZ = z;
        }

        return true;
    }

    bool LogDeveloperSnapshot()
    {
        OpenShimDeveloperSnapshot snapshot = {};
        if (!CaptureDeveloperSnapshot(snapshot))
            return false;

        if (snapshot.localPlayerResolved)
        {
            LogShimA(LogLevel::Info,
                     "dev_inspector",
                     "snapshot shim=%u sdk=%u compatible=%u patchingComplete=%u patches=%u events=%u dropped=%llu player={resolved:1,x:%.3f,y:%.3f,z:%.3f}",
                     snapshot.shimVersion,
                     snapshot.sdkVersion,
                     static_cast<unsigned>(snapshot.compatibleGameVersion),
                     static_cast<unsigned>(snapshot.patchingComplete),
                     snapshot.appliedPatchCount,
                     snapshot.pendingEventCount,
                     static_cast<unsigned long long>(snapshot.droppedEventCount),
                     snapshot.localPlayerX,
                     snapshot.localPlayerY,
                     snapshot.localPlayerZ);
        }
        else
        {
            LogShimA(LogLevel::Info,
                     "dev_inspector",
                     "snapshot shim=%u sdk=%u compatible=%u patchingComplete=%u patches=%u events=%u dropped=%llu player={resolved:0}",
                     snapshot.shimVersion,
                     snapshot.sdkVersion,
                     static_cast<unsigned>(snapshot.compatibleGameVersion),
                     static_cast<unsigned>(snapshot.patchingComplete),
                     snapshot.appliedPatchCount,
                     snapshot.pendingEventCount,
                     static_cast<unsigned long long>(snapshot.droppedEventCount));
        }

        PublishOpenShimEvent(OpenShimEventType::DeveloperSnapshotCaptured,
                             snapshot.localPlayerResolved,
                             snapshot.appliedPatchCount,
                             "Developer snapshot captured");
        return true;
    }

    extern "C" BZRO_API const OpenShimApiV2* __cdecl OpenShimGetApi(uint32_t requestedVersion)
    {
        if (requestedVersion != 0 && requestedVersion != SDK_API_V2)
            return nullptr;
        return &GetApiV2Table();
    }

    extern "C" BZRO_API uint32_t __cdecl OpenShimGetBzrDistribution()
    {
        return static_cast<uint32_t>(GetBzrDistribution());
    }

    extern "C" BZRO_API int32_t __cdecl OpenShimCaptureDeveloperSnapshot(
        OpenShimDeveloperSnapshot* outSnapshot)
    {
        if (!outSnapshot)
            return 0;

        OpenShimDeveloperSnapshot snapshot = {};
        if (!CaptureDeveloperSnapshot(snapshot))
            return 0;

        *outSnapshot = snapshot;
        return 1;
    }

    extern "C" BZRO_API int32_t __cdecl OpenShimLogDeveloperSnapshot()
    {
        return LogDeveloperSnapshot() ? 1 : 0;
    }
}
