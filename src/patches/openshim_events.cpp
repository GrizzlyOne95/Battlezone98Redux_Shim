// openshim_events.cpp — in-process dispatch for the OpenShim event queue.
//
// See include/openshim_events.h for the contract and for why this rides on the
// existing SDK v2 event record rather than defining a second one.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "openshim_events.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include "openshim_sdk_v2.h"
#include "patcher.h"

namespace BZROpenShim
{
    namespace
    {
        // Fixed for the same reason the ring is: a bounded consumer count is
        // not a real limit, and registration must not depend on the heap.
        constexpr size_t kMaxSinks = 8;

        struct SinkEntry
        {
            OpenShimEventSink sink = nullptr;
            void* user = nullptr;
        };

        SRWLOCK g_DispatchLock = SRWLOCK_INIT;
        OpenShimEvent g_Ring[kInProcessEventQueueCapacity] = {};
        uint32_t g_Head = 0;   // next slot to read
        uint32_t g_Count = 0;  // live entries

        SinkEntry g_Sinks[kMaxSinks] = {};
        // Read without the lock by the enqueue fast path, so it is interlocked
        // rather than a plain size_t: "nobody is listening" must not cost a
        // lock acquisition on a per-damage-application code path.
        volatile LONG g_SinkCount = 0;

        uint64_t g_Enqueued = 0;
        uint64_t g_Dispatched = 0;
        uint64_t g_Dropped = 0;
        uint32_t g_HighWaterMark = 0;

        // Drop reporting is throttled so a pathological frame cannot turn the
        // log into the bottleneck it is warning about.
        uint64_t g_LastDropLogTick = 0;
        uint64_t g_DropsAtLastLog = 0;
        constexpr uint64_t kDropLogIntervalMs = 5000;

        LONG LiveSinkCountLocked()
        {
            LONG live = 0;
            for (size_t i = 0; i < kMaxSinks; ++i)
                if (g_Sinks[i].sink)
                    ++live;
            return live;
        }
    }

    bool EnqueueEventForInProcessDispatch(const OpenShimEvent& event) noexcept
    {
        if (InterlockedCompareExchange(&g_SinkCount, 0, 0) == 0)
            return false;

        bool stored = false;
        bool shouldLogDrops = false;
        uint64_t dropsSinceLastLog = 0;

        AcquireSRWLockExclusive(&g_DispatchLock);
        if (g_Count < kInProcessEventQueueCapacity)
        {
            const uint32_t tail =
                (g_Head + g_Count) % static_cast<uint32_t>(kInProcessEventQueueCapacity);
            g_Ring[tail] = event;
            ++g_Count;
            ++g_Enqueued;
            if (g_Count > g_HighWaterMark)
                g_HighWaterMark = g_Count;
            stored = true;
        }
        else
        {
            // Drop the newest. Dropping the oldest, as the SDK polling queue
            // does, would let a burst of damage erase the session transition a
            // sink needs to stay consistent.
            ++g_Dropped;
            const uint64_t now = event.tickMs ? event.tickMs : GetTickCount64();
            if (now - g_LastDropLogTick >= kDropLogIntervalMs)
            {
                dropsSinceLastLog = g_Dropped - g_DropsAtLastLog;
                g_DropsAtLastLog = g_Dropped;
                g_LastDropLogTick = now;
                shouldLogDrops = true;
            }
        }
        ReleaseSRWLockExclusive(&g_DispatchLock);

        if (shouldLogDrops)
        {
            Log(L"[EVENTS] Dispatch ring full; dropped %llu event(s) in the last "
                L"%llums (%llu total, capacity %zu)\n",
                static_cast<unsigned long long>(dropsSinceLastLog),
                static_cast<unsigned long long>(kDropLogIntervalMs),
                static_cast<unsigned long long>(g_Dropped),
                kInProcessEventQueueCapacity);
        }

        return stored;
    }

    bool PublishSimEvent(OpenShimEventType type,
                         int32_t slot0,
                         int32_t slot1,
                         int32_t slot2,
                         int32_t slot3) noexcept
    {
        const uint64_t arg0 =
            static_cast<uint64_t>(static_cast<uint32_t>(slot0)) |
            (static_cast<uint64_t>(static_cast<uint32_t>(slot1)) << 32);
        const uint64_t arg1 =
            static_cast<uint64_t>(static_cast<uint32_t>(slot2)) |
            (static_cast<uint64_t>(static_cast<uint32_t>(slot3)) << 32);

        if (type == OpenShimEventType::SimDamage)
        {
            // In-process only; see the note on OpenShimEventType. Built by hand
            // rather than routed through PublishOpenShimEvent so it never
            // reaches the companion polling queue.
            if (InterlockedCompareExchange(&g_SinkCount, 0, 0) == 0)
                return false;

            OpenShimEvent event = {};
            event.structSize = sizeof(OpenShimEvent);
            event.apiVersion = SDK_API_V2;
            event.type = static_cast<uint32_t>(type);
            event.threadId = GetCurrentThreadId();
            event.tickMs = GetTickCount64();
            event.arg0 = arg0;
            event.arg1 = arg1;
            return EnqueueEventForInProcessDispatch(event);
        }

        // Everything else goes through the SDK producer, which stamps the
        // process-wide sequence and QPC and fans out to both queues.
        return PublishOpenShimEvent(type, arg0, arg1, nullptr);
    }

    int32_t SimEventArg(const OpenShimEvent& event, size_t index) noexcept
    {
        switch (index)
        {
        case 0: return static_cast<int32_t>(static_cast<uint32_t>(event.arg0 & 0xFFFFFFFFull));
        case 1: return static_cast<int32_t>(static_cast<uint32_t>(event.arg0 >> 32));
        case 2: return static_cast<int32_t>(static_cast<uint32_t>(event.arg1 & 0xFFFFFFFFull));
        case 3: return static_cast<int32_t>(static_cast<uint32_t>(event.arg1 >> 32));
        default: return 0;
        }
    }

    bool SubscribeEvents(OpenShimEventSink sink, void* user) noexcept
    {
        if (!sink)
            return false;

        bool added = false;
        bool alreadyPresent = false;
        LONG newCount = 0;

        AcquireSRWLockExclusive(&g_DispatchLock);
        for (size_t i = 0; i < kMaxSinks; ++i)
        {
            if (g_Sinks[i].sink == sink && g_Sinks[i].user == user)
            {
                alreadyPresent = true;
                break;
            }
        }
        if (!alreadyPresent)
        {
            for (size_t i = 0; i < kMaxSinks; ++i)
            {
                if (g_Sinks[i].sink == nullptr)
                {
                    g_Sinks[i].sink = sink;
                    g_Sinks[i].user = user;
                    added = true;
                    break;
                }
            }
        }
        if (added)
        {
            newCount = LiveSinkCountLocked();
            InterlockedExchange(&g_SinkCount, newCount);
        }
        ReleaseSRWLockExclusive(&g_DispatchLock);

        if (added)
        {
            Log(L"[EVENTS] Subscribed sink 0x%08X user=0x%08X (%ld total)\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sink)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(user)),
                newCount);
        }
        else if (!alreadyPresent)
        {
            Log(L"[EVENTS] Sink table full (%zu); refused sink 0x%08X\n",
                kMaxSinks,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sink)));
        }

        return added || alreadyPresent;
    }

    void UnsubscribeEvents(OpenShimEventSink sink, void* user) noexcept
    {
        if (!sink)
            return;

        bool removed = false;
        AcquireSRWLockExclusive(&g_DispatchLock);
        for (size_t i = 0; i < kMaxSinks; ++i)
        {
            if (g_Sinks[i].sink == sink && g_Sinks[i].user == user)
            {
                g_Sinks[i].sink = nullptr;
                g_Sinks[i].user = nullptr;
                removed = true;
            }
        }
        if (removed)
            InterlockedExchange(&g_SinkCount, LiveSinkCountLocked());
        ReleaseSRWLockExclusive(&g_DispatchLock);

        if (removed)
        {
            Log(L"[EVENTS] Unsubscribed sink 0x%08X user=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sink)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(user)));
        }
    }

    size_t DispatchPendingEvents() noexcept
    {
        // Re-entrancy guard: a sink that reaches the drain again, directly or
        // through the engine, must not consume the batch out from under us.
        static volatile LONG s_InDispatch = 0;
        if (InterlockedCompareExchange(&s_InDispatch, 1, 0) != 0)
            return 0;

        static OpenShimEvent s_Batch[kInProcessEventQueueCapacity];
        SinkEntry sinks[kMaxSinks];
        size_t batchCount = 0;
        size_t sinkCount = 0;

        AcquireSRWLockExclusive(&g_DispatchLock);
        while (g_Count > 0 && batchCount < kInProcessEventQueueCapacity)
        {
            s_Batch[batchCount++] = g_Ring[g_Head];
            g_Head = (g_Head + 1) % static_cast<uint32_t>(kInProcessEventQueueCapacity);
            --g_Count;
        }
        for (size_t i = 0; i < kMaxSinks; ++i)
        {
            if (g_Sinks[i].sink)
                sinks[sinkCount++] = g_Sinks[i];
        }
        g_Dispatched += batchCount;
        ReleaseSRWLockExclusive(&g_DispatchLock);

        // Sinks run with no lock held, so one of them publishing (which the
        // career sink does when it derives a kill from damage) simply queues
        // for the next drain.
        for (size_t e = 0; e < batchCount; ++e)
        {
            for (size_t s = 0; s < sinkCount; ++s)
                sinks[s].sink(s_Batch[e], sinks[s].user);
        }

        InterlockedExchange(&s_InDispatch, 0);
        return batchCount;
    }

    bool HasEventSubscribers() noexcept
    {
        return InterlockedCompareExchange(&g_SinkCount, 0, 0) != 0;
    }

    OpenShimEventStats GetInProcessEventStats() noexcept
    {
        OpenShimEventStats stats = {};
        AcquireSRWLockShared(&g_DispatchLock);
        stats.enqueued = g_Enqueued;
        stats.dispatched = g_Dispatched;
        stats.dropped = g_Dropped;
        stats.queueDepth = g_Count;
        stats.highWaterMark = g_HighWaterMark;
        for (size_t i = 0; i < kMaxSinks; ++i)
            if (g_Sinks[i].sink)
                ++stats.subscribers;
        ReleaseSRWLockShared(&g_DispatchLock);
        return stats;
    }

    void ResetInProcessEventQueue() noexcept
    {
        uint32_t discarded = 0;
        AcquireSRWLockExclusive(&g_DispatchLock);
        discarded = g_Count;
        g_Head = 0;
        g_Count = 0;
        ReleaseSRWLockExclusive(&g_DispatchLock);

        if (discarded != 0)
            Log(L"[EVENTS] Reset dispatch ring, discarded %u pending event(s)\n", discarded);
    }

    const char* DescribeEventType(OpenShimEventType type) noexcept
    {
        switch (type)
        {
        case OpenShimEventType::None:                      return "None";
        case OpenShimEventType::ShimInitialized:           return "ShimInitialized";
        case OpenShimEventType::CompatibilityChanged:      return "CompatibilityChanged";
        case OpenShimEventType::PatchingCompleted:         return "PatchingCompleted";
        case OpenShimEventType::ShutdownStarted:           return "ShutdownStarted";
        case OpenShimEventType::DeveloperSnapshotCaptured: return "DeveloperSnapshotCaptured";
        case OpenShimEventType::NativeUiAction:            return "NativeUiAction";
        case OpenShimEventType::SimSessionStarted:         return "SimSessionStarted";
        case OpenShimEventType::SimSessionEnded:           return "SimSessionEnded";
        case OpenShimEventType::SimDamage:                 return "SimDamage";
        case OpenShimEventType::SimKill:                   return "SimKill";
        case OpenShimEventType::SimTeamDeath:              return "SimTeamDeath";
        default:                                           return "Unknown";
        }
    }
}
