// openshim_events.h — in-process dispatch for the OpenShim event queue.
//
// ============================================================================
// WHAT THIS ADDS, AND WHAT IT DELIBERATELY DOES NOT DUPLICATE
// ============================================================================
//
// OpenShim already had half of a native event layer: SDK v2 (BZROpenShim.h,
// openshim_sdk_v2.cpp) publishes ABI-stable OpenShimEvent records into a
// bounded ring that companion DLLs POLL through the v2 function table
// (OPENSHIM_CAP_EVENT_QUEUE). That is the right shape for EXU, but it gave
// OpenShim's own subsystems nothing: there was no way for shim-internal code to
// be told about an event, and there were no simulation events to be told about.
//
// This header supplies the missing halves without starting a second event
// system:
//
//   1. An in-process fan-out. PublishOpenShimEvent now also copies each record
//      into a dispatch ring here; DispatchPendingEvents drains that ring on a
//      known-safe per-frame point and hands each record to registered sinks.
//      The SDK's polling queue is untouched by this, so a companion polling it
//      and a shim subsystem subscribing here both see the same events.
//
//   2. Simulation events. SimSessionStarted / SimSessionEnded / SimDamage /
//      SimKill / SimTeamDeath, published by PublishSimEvent below and defined
//      in BZROpenShim.h so the numbering stays wire-stable for companions.
//
// The constraint the native-event-layer work is built around — never run
// arbitrary consumer code (least of all Lua) from inside an engine detour;
// queue from the hook and deliver on a known-safe tick — is what the split
// between PublishSimEvent and DispatchPendingEvents enforces.
//
// ============================================================================
// RULES
// ============================================================================
//
// Producers run in arbitrary engine hook contexts. PublishSimEvent is
// noexcept, never allocates, and never touches the file system; it takes one
// SRW lock for the length of a struct copy, and drops rather than stalls when
// the ring is full.
//
// Sinks run on the drain, on the game's main thread, with no lock held. They
// may allocate and do file I/O. A sink that publishes queues for the NEXT
// drain: the drain copies its batch out before invoking anything, so
// re-entrancy can neither deadlock nor livelock inside one frame.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include "BZROpenShim.h"

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
    // Sinks are plain function pointers plus an opaque cookie, so a consumer
    // needs neither a vtable nor an allocation to register.
    using OpenShimEventSink = void (*)(const OpenShimEvent& event, void* user);

    // Publishes a simulation event. The four int32 slots are packed into the
    // ABI-stable record's arg0/arg1 exactly as documented on OpenShimEventType.
    //
    // Every simulation event reaches in-process sinks. All of them except
    // SimDamage are ALSO forwarded to the SDK polling queue for companion DLLs;
    // SimDamage fires per damage application and would evict the lifecycle
    // events companions actually poll for.
    bool PublishSimEvent(OpenShimEventType type,
                         int32_t slot0 = 0,
                         int32_t slot1 = 0,
                         int32_t slot2 = 0,
                         int32_t slot3 = 0) noexcept;

    // Unpacks slot `index` (0..3) from a record published by PublishSimEvent.
    int32_t SimEventArg(const OpenShimEvent& event, size_t index) noexcept;

    // Called by PublishOpenShimEvent so lifecycle events reach sinks too.
    // Not for direct use by feature code — publish, do not enqueue. Returns
    // true when the record was stored, false when it was dropped (no
    // subscribers, or the ring is full).
    bool EnqueueEventForInProcessDispatch(const OpenShimEvent& event) noexcept;

    // Registration is idempotent per (sink, user) pair.
    bool SubscribeEvents(OpenShimEventSink sink, void* user) noexcept;
    void UnsubscribeEvents(OpenShimEventSink sink, void* user) noexcept;

    // Drain. Call ONLY from the known-safe per-frame point (see
    // TickOpenShimEventLayer in bzr_hooks.cpp). Returns the number of events
    // handed to sinks.
    size_t DispatchPendingEvents() noexcept;

    // True when at least one sink is registered. Producers that would have to
    // do real work to build an event should check this first; with no sinks,
    // enqueueing short-circuits before taking the lock.
    bool HasEventSubscribers() noexcept;

    struct OpenShimEventStats
    {
        uint64_t enqueued = 0;
        uint64_t dispatched = 0;
        uint64_t dropped = 0;
        uint32_t queueDepth = 0;
        uint32_t highWaterMark = 0;
        uint32_t subscribers = 0;
    };

    OpenShimEventStats GetInProcessEventStats() noexcept;

    // Drops everything queued. Called on mission teardown and on the patch
    // baseline reset so a record from a dead world cannot be delivered against
    // the next one.
    void ResetInProcessEventQueue() noexcept;

    const char* DescribeEventType(OpenShimEventType type) noexcept;

    // Capacity is fixed at compile time so the dispatch ring never allocates.
    inline constexpr size_t kInProcessEventQueueCapacity = 256;
}
