#pragma once

// Lock-free publish/apply epoch tracking for the content render-profile
// request ABI.
//
// Problem being solved: OpenShimRequestRenderProfile must report whether a
// request was APPLIED to live viewports, but the Ogre mutation happens later
// on the engine thread (the viewport scheme hook drains the pending flag).
// Inferring "applied" from viewport existence is a lie: viewports can exist
// while the drain has not run yet. The truthful signal is an epoch pair:
//
//   - Publish() hands each deferred apply a monotonically increasing epoch.
//   - The engine-thread drain snapshots the highest published epoch BEFORE
//     consuming the pending flag, performs the apply pass, and - only if the
//     pass actually found viewports - advances the applied watermark to that
//     snapshot.
//   - AppliedSince(epoch) then answers exactly "did a drain that covered my
//     publish complete with viewports".
//
// Race contract: the drain snapshots before consuming so it can only ever
// UNDER-report during a concurrent publish (transient StoredDeferred that the
// next drain corrects). It can never over-report an epoch whose publish was
// not drained. MarkApplied is monotonic: stale drains cannot lower the
// watermark.

#include <atomic>
#include <cstdint>

namespace BZROpenShim::RenderProfiles
{
    class RequestApplyTracker
    {
    public:
        // Publishers call this immediately before setting the pending flag;
        // the returned value identifies their request for AppliedSince().
        uint64_t Publish() noexcept
        {
            return s_published.fetch_add(1, std::memory_order_acq_rel) + 1;
        }

        // Highest epoch visible at drain time. Call BEFORE consuming the
        // pending flag (see race contract above).
        uint64_t SnapshotPublished() const noexcept
        {
            return s_published.load(std::memory_order_acquire);
        }

        // Advance the watermark to `covered`; ignored when stale. Only call
        // after an apply pass that actually reached at least one viewport.
        void MarkApplied(const uint64_t covered) noexcept
        {
            uint64_t current = s_appliedThrough.load(std::memory_order_acquire);
            while (covered > current &&
                   !s_appliedThrough.compare_exchange_weak(
                       current, covered, std::memory_order_release,
                       std::memory_order_acquire))
            {
            }
        }

        uint64_t AppliedThrough() const noexcept
        {
            return s_appliedThrough.load(std::memory_order_acquire);
        }

        // True when some drained apply pass covering `epoch` completed.
        bool AppliedSince(const uint64_t epoch) const noexcept
        {
            return AppliedThrough() >= epoch;
        }

    private:
        std::atomic<uint64_t> s_published { 0 };
        std::atomic<uint64_t> s_appliedThrough { 0 };
    };
}
