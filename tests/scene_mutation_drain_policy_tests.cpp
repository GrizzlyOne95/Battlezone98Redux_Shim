// Scene-mutation drain gate tests. Pure logic: no engine, no game. Covers
// include/scene_mutation_drain_policy.h.

#include "scene_mutation_drain_policy.h"

#include <cstdint>
#include <cstdio>
#include <vector>
#include "test_check.h"

using OpenShimTest::Check;

namespace SMD = BZROpenShim::SceneMutationDrain;

void TestInlineOnlyUntilInstalled()
{
    std::printf("TestInlineOnlyUntilInstalled\n");
    SMD::Gate gate;
    Check(gate.InstallState() == SMD::Gate::Install::Pending, "starts pending");
    Check(!gate.Deferring(), "pending gate does not defer");
    Check(!gate.OnRenderQueue().defer, "pending gate mutates inline");
    gate.OnRequest();
    Check(!gate.OnFrameStarted(), "pending gate counts no deferred work");
    Check(!gate.OnSimTick(), "pending gate has no fallback drain");

    SMD::Gate unavailable;
    unavailable.NoteUnavailable();
    for (int i = 0; i < 1000; ++i)
        Check(!unavailable.OnRenderQueue().defer, "unavailable drain mutates inline");
    Check(!unavailable.StallReported() && !unavailable.OnSimTick(), "unavailable is not a stall");
}

void TestDefersAndDrainsOncePerWorldFrame()
{
    std::printf("TestDefersAndDrainsOncePerWorldFrame\n");
    SMD::Gate gate;
    gate.NoteInstalled();
    Check(!gate.OnFrameStarted(), "shell frame with no world queue runs nothing");
    for (int camera = 0; camera < 4; ++camera)
        Check(gate.OnRenderQueue().defer, "installed drain defers every camera's call");
    Check(!gate.OnSimTick(), "no fallback drain while frameStarted is healthy");
    Check(gate.OnFrameStarted(), "world frame leaves work due");
    Check(!gate.OnFrameStarted(), "work runs once, not again on the next empty frame");
    gate.OnRequest();
    Check(gate.OnFrameStarted(), "a flame-path request alone makes the drain run");
}

void TestStallKeepsDeferringAndFallsBackToSimTick()
{
    std::printf("TestStallKeepsDeferringAndFallsBackToSimTick\n");
    SMD::Gate gate;
    gate.NoteInstalled();
    for (uint32_t i = 0; i < SMD::kStallRenderQueueCalls; ++i)
        Check(gate.OnRenderQueue().defer && !gate.Stalled(), "within the stall budget");
    Check(!gate.OnSimTick(), "no fallback before the stall");
    const SMD::RenderQueueDecision first = gate.OnRenderQueue();
    Check(first.defer, "a stall never resumes inline mutation");
    Check(first.reportStall && gate.Stalled(), "first stalled call reports");
    const SMD::RenderQueueDecision second = gate.OnRenderQueue();
    Check(second.defer && !second.reportStall, "stall reported once per episode");
    for (int i = 0; i < 100000; ++i)
        Check(gate.OnRenderQueue().defer, "long stall keeps deferring");

    Check(gate.OnSimTick(), "sim tick drains while stalled");
    Check(!gate.OnSimTick(), "sim tick drains only work that is due");
    gate.OnRenderQueue();
    Check(gate.OnSimTick(), "next stalled world frame drains from the sim tick again");

    gate.OnRenderQueue();
    Check(gate.OnFrameStarted(), "frameStarted resumes and takes the due work");
    Check(!gate.Stalled() && !gate.OnSimTick(), "recovery ends the fallback");

    for (uint32_t i = 0; i < SMD::kStallRenderQueueCalls; ++i)
        gate.OnRenderQueue();
    const SMD::RenderQueueDecision again = gate.OnRenderQueue();
    Check(again.defer && again.reportStall, "a new stall episode is reported again");
}

void TestSceneTeardownDropsDueWork()
{
    std::printf("TestSceneTeardownDropsDueWork\n");
    SMD::Gate gate;
    gate.NoteInstalled();
    gate.OnRenderQueue();
    gate.OnSceneTeardown();
    Check(!gate.OnFrameStarted(), "work due for a torn-down scene is dropped");
    Check(gate.OnRenderQueue().defer, "the next world defers normally");
}

// The laser beam path: the render-queue tick asks, the drain builds.
void TestDeferredCreateRequestThenDrain()
{
    std::printf("TestDeferredCreateRequestThenDrain\n");
    SMD::DeferredCreate beam;
    Check(beam.Allow(false), "outside a render callback the object is created now");
    Check(!beam.Take(), "an immediate create leaves no request");
    Check(!beam.Allow(true), "inside a deferring render callback nothing is created");
    Check(!beam.Allow(true), "a second camera only repeats the request");
    Check(beam.Take(), "the drain sees the request");
    Check(!beam.Take(), "the request is taken once");
    Check(!beam.Allow(true), "asked again");
    beam = SMD::DeferredCreate{}; // ForgetBeam on scene teardown
    Check(!beam.Take(), "teardown drops the request");
}

// The chunk mesh proxy path: per-slot requests keyed by the slot occupant.
void TestSlotRequests()
{
    std::printf("TestSlotRequests\n");
    int a = 0, b = 0, c = 0;
    std::vector<const int*> occupants = { &a, &b, nullptr };
    SMD::SlotRequests<const int*> requests;
    Check(requests.Request(0, &a, occupants.size()), "slot 0 requested");
    Check(requests.Request(0, &a, occupants.size()) && requests.Size() == 1, "repeat request deduplicated");
    Check(requests.Request(1, &b, occupants.size()), "slot 1 requested");
    Check(!requests.Request(3, &c, occupants.size()), "out-of-pool index refused");
    occupants[1] = &c; // slot 1 released and reused before the drain
    std::vector<size_t> built;
    requests.Drain(occupants.size(), [&](size_t i) { return occupants[i]; },
                   [&](size_t i) { built.push_back(i); });
    Check(built.size() == 1 && built[0] == 0, "only the unchanged occupant is built");
    Check(requests.Empty(), "drain empties the list");

    requests.Request(0, &a, occupants.size());
    requests.Drain(0, [&](size_t i) { return occupants[i]; }, [&](size_t) { built.push_back(99); });
    Check(built.size() == 1, "a shrunk pool builds nothing");

    requests.Request(0, &a, occupants.size());
    requests.Clear(); // scene teardown
    Check(requests.Empty(), "teardown clears the requests");

    SMD::SlotRequests<const int*> bounded;
    for (size_t i = 0; i < 2; ++i)
        bounded.Request(i, &a, 2);
    Check(bounded.Size() == 2, "bounded by the pool size");
}

int main()
{
    TestInlineOnlyUntilInstalled();
    TestDefersAndDrainsOncePerWorldFrame();
    TestStallKeepsDeferringAndFallsBackToSimTick();
    TestSceneTeardownDropsDueWork();
    TestDeferredCreateRequestThenDrain();
    TestSlotRequests();
    return OpenShimTest::ExitCode();
}
