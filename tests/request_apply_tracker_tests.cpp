// Contract tests for the request/apply epoch tracker behind
// OpenShimRequestRenderProfile's truthful status reporting. Pure logic: no
// engine, no game. Build+run via scripts/run_render_profile_tests.ps1.

#include "render_profile_request_tracker.h"

#include <cstdio>

using BZROpenShim::RenderProfiles::RequestApplyTracker;

namespace
{
    int g_failures = 0;

    void ExpectTrue(bool condition, const char* what)
    {
        if (!condition)
        {
            std::printf("  FAIL: %s\n", what);
            ++g_failures;
        }
    }
}

void TestPublishWithoutDrainIsDeferred()
{
    std::printf("TestPublishWithoutDrainIsDeferred\n");
    RequestApplyTracker tracker;
    const uint64_t epoch = tracker.Publish();
    ExpectTrue(!tracker.AppliedSince(epoch), "unpublished drain reports deferred");
    ExpectTrue(tracker.AppliedThrough() == 0u, "watermark untouched");
}

void TestDrainCoveringPublishReportsApplied()
{
    std::printf("TestDrainCoveringPublishReportsApplied\n");
    RequestApplyTracker tracker;
    const uint64_t epoch = tracker.Publish();

    // Drain order mirrors the runtime hook: snapshot BEFORE consuming.
    const uint64_t covered = tracker.SnapshotPublished();
    ExpectTrue(covered >= epoch, "snapshot covers the publish");
    tracker.MarkApplied(covered);

    ExpectTrue(tracker.AppliedSince(epoch), "drained publish reports applied-live");
}

void TestStaleAppliedCannotSatisfyNewerEpoch()
{
    std::printf("TestStaleAppliedCannotSatisfyNewerEpoch\n");
    RequestApplyTracker tracker;
    const uint64_t first = tracker.Publish();
    const uint64_t firstCovered = tracker.SnapshotPublished();
    tracker.MarkApplied(firstCovered);
    ExpectTrue(tracker.AppliedSince(first), "first applied");

    const uint64_t second = tracker.Publish();
    ExpectTrue(!tracker.AppliedSince(second), "second still deferred until its own drain");

    // The next drain covers the second publish and advances the watermark;
    // both epochs now read applied (monotonic watermark).
    const uint64_t secondCovered = tracker.SnapshotPublished();
    tracker.MarkApplied(secondCovered);
    ExpectTrue(tracker.AppliedSince(second), "second applied after its drain");
    ExpectTrue(tracker.AppliedSince(first), "monotonic watermark keeps first applied");
}

void TestMarkAppliedIsMonotonicAgainstStaleDrains()
{
    std::printf("TestMarkAppliedIsMonotonicAgainstStaleDrains\n");
    RequestApplyTracker tracker;
    const uint64_t first = tracker.Publish();
    tracker.MarkApplied(tracker.SnapshotPublished());

    const uint64_t second = tracker.Publish();
    tracker.MarkApplied(tracker.SnapshotPublished());
    ExpectTrue(tracker.AppliedThrough() >= second, "second advanced watermark");

    // A stale/late drain carrying an older epoch must never lower it.
    tracker.MarkApplied(first);
    ExpectTrue(tracker.AppliedThrough() >= second, "stale MarkApplied ignored");

    // A drain that found NO viewports must not mark anything applied; the
    // runtime simply never calls MarkApplied in that case - modelled here by
    // asserting a fresh tracker stays at zero.
    RequestApplyTracker empty;
    empty.Publish();
    ExpectTrue(empty.AppliedThrough() == 0u, "viewport-less drain leaves watermark");
}

int main()
{
    TestPublishWithoutDrainIsDeferred();
    TestDrainCoveringPublishReportsApplied();
    TestStaleAppliedCannotSatisfyNewerEpoch();
    TestMarkAppliedIsMonotonicAgainstStaleDrains();

    if (g_failures != 0)
    {
        std::printf("\nrequest_apply_tracker_tests FAILED (%d)\n", g_failures);
        return 1;
    }
    std::printf("\nrequest_apply_tracker_tests passed\n");
    return 0;
}
