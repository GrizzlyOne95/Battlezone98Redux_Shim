// RtsBuildQueue's engine-independent logic: busy and pick decisions, the
// queue table and its caps, Shift-remove-last, the drain gate, the afford
// test and the badge texts.
#include "rts_build_queue_policy.h"
#include "test_check.h"

#include <cstdio>
#include <cstring>

using namespace BZROpenShim::RtsBuildQueuePolicy;
using OpenShimTest::Check;

namespace
{
    void BusyTests()
    {
        Check(!IsBusy(0, 0), "idle and empty queue is not busy");
        Check(IsBusy(0x1000, 0), "a build class set is busy");
        Check(IsBusy(0, 1), "a non-empty queue is busy, so the order of picks is kept");
        Check(IsBusy(0x1000, 3), "building with a queue is busy");
        Check(IsBusy(0, 0, true), "a just-issued last entry is busy until +0x300 is set");
        Check(!IsBusy(0, 0, false), "no recent issue, idle, empty: not busy");
    }

    void PickTests()
    {
        Check(PlanPick(false, false, true, 0, false) == PickAction::Stock, "option inactive: stock");
        Check(PlanPick(false, true, true, 2, true) == PickAction::Stock, "option inactive with Shift: stock");
        Check(PlanPick(true, false, false, 0, false) == PickAction::Stock, "idle, empty queue: stock builds at once");
        Check(PlanPick(true, false, true, 0, false) == PickAction::Enqueue, "busy: enqueue");
        Check(PlanPick(true, false, true, kMaxEntries - 1, false) == PickAction::Enqueue, "one slot left: enqueue");
        Check(PlanPick(true, false, true, kMaxEntries, false) == PickAction::Refuse, "full: refuse");
        Check(PlanPick(true, false, IsBusy(0, 2), 2, false) == PickAction::Enqueue, "idle but queued (waiting): enqueue");
        Check(PlanPick(true, true, true, 2, true) == PickAction::RemoveLast, "Shift and queued: remove last");
        Check(PlanPick(true, true, true, 2, false) == PickAction::Stock, "Shift, item not queued: stock");
        Check(PlanPick(true, true, false, 0, false) == PickAction::Stock, "Shift on an idle producer: stock");
        Check(PlanPick(true, true, true, kMaxEntries, true) == PickAction::RemoveLast, "Shift removes even when full");
    }

    void TableTests()
    {
        Table t;
        Check(t.ProducerCount() == 0 && t.Depth(5) == 0 && t.Front(5) == 0, "starts empty");
        Check(t.Push(0, 0x1000) == 0 && t.Push(5, 0) == 0, "handle 0 and class 0 are refused");
        Check(t.Push(5, 0x1000) == 1 && t.Push(5, 0x2000) == 2 && t.Push(5, 0x1000) == 3, "pushes grow the depth");
        Check(t.Depth(5) == 3 && t.ProducerCount() == 1 && t.Front(5) == 0x1000, "order kept, front first");
        Check(t.Contains(5, 0x2000) && !t.Contains(5, 0x3000) && !t.Contains(6, 0x1000), "contains");

        // Shift removes the LAST entry of that item.
        Check(t.RemoveLast(5, 0x1000) == 2, "removed one, two left");
        Check(t.Front(5) == 0x1000 && t.Depth(5) == 2, "the first copy stays, the last went");
        Check(t.RemoveLast(5, 0x3000) == -1 && t.RemoveLast(6, 0x1000) == -1, "not queued: -1");
        Check(t.RemoveLast(5, 0x2000) == 1 && t.Front(5) == 0x1000, "removes from the middle of the order");
        Check(t.RemoveLast(5, 0x1000) == 0 && t.ProducerCount() == 0, "an emptied queue frees its slot");

        Table cap;
        for (int i = 0; i < kMaxEntries; ++i)
            Check(cap.Push(7, 0x1000 + i) == i + 1, "fills to the cap");
        Check(cap.Push(7, 0x9000) == 0 && cap.Depth(7) == kMaxEntries, "the cap refuses the 11th");

        Table many;
        for (int h = 1; h <= kMaxProducers; ++h)
            Check(many.Push(h, 0x1000) == 1, "16 producers fit");
        Check(many.Push(99, 0x1000) == 0 && many.ProducerCount() == kMaxProducers, "a 17th producer is refused");
        Check(many.Push(3, 0x2000) == 2, "a producer that already has a queue still appends");
        Check(many.HandleAt(0) == 1 && many.HandleAt(kMaxProducers - 1) == kMaxProducers && many.HandleAt(kMaxProducers) == 0,
              "HandleAt walks the producers");
    }

    void PopAndClearTests()
    {
        Table t;
        t.Push(5, 0x1000);
        t.Push(5, 0x2000);
        t.Push(6, 0x3000);
        uint64_t last = 0;
        Check(!t.Issued(5, last), "nothing issued yet");
        Check(t.PopFront(5, 1000) && t.Front(5) == 0x2000 && t.Depth(5) == 1, "pop drops the front");
        Check(t.Issued(5, last) && last == 1000, "issue time kept while entries remain");
        Check(t.PopFront(5, 1500) && t.Depth(5) == 0 && t.ProducerCount() == 1, "last pop frees the slot");
        Check(!t.PopFront(5, 1600), "popping an empty queue fails");
        Check(t.RecentlyIssued(5, 1500) && t.RecentlyIssued(5, 1500 + kRecentIssueMs - 1),
              "the emptied queue's last issue stays recent");
        Check(!t.RecentlyIssued(5, 1500 + kRecentIssueMs) && !t.RecentlyIssued(6, 1500), "recent window ends; other handle no");
        Check(t.Clear(6) == 1 && t.Clear(6) == 0 && t.ProducerCount() == 0, "clear returns the dropped count");
        t.Push(1, 0x1000);
        t.Push(1, 0x1000);
        t.Push(2, 0x1000);
        Check(t.ClearAll() == 3 && t.ProducerCount() == 0, "clear all");
    }

    void RecentIssueTests()
    {
        Table t;
        t.Push(5, 0x1000);
        t.PopFront(5, 2000);
        Check(t.ProducerCount() == 0 && t.RecentlyIssued(5, 2100), "slot freed but the issue is remembered");
        // A pick in the window enqueues (busy) and inherits the gap.
        Check(PlanPick(true, false, IsBusy(0, 0, t.RecentlyIssued(5, 2100)), 0, false) == PickAction::Enqueue,
              "pick right after the last pop is queued, not stock");
        Check(t.Push(5, 0x2000) == 1, "the pick is queued");
        uint64_t last = 0;
        Check(t.Issued(5, last) && last == 2000, "new queue inherits the issue time");
        Check(!DrainDue(1, 0, true, true, last, 2100), "drain waits out the gap");
        Check(DrainDue(1, 0, true, true, last, 2000 + kIssueGapMs), "then issues");
        Table fresh;
        fresh.Push(5, 0x1000);
        Check(!fresh.RecentlyIssued(5, 0), "no pop, no recent issue");
        t.ClearAll();
        Check(!t.RecentlyIssued(5, 2100), "clear all forgets recent issues");
        Check(std::strcmp(ReasonName(ClearReason::PlainOrder), "plain order") == 0, "plain order reason name");
    }

    void DrainTests()
    {
        Check(CanAfford(100, 100, 1, 1), "exact scrap and pilots affords");
        Check(!CanAfford(101, 100, 0, 5), "short of scrap");
        Check(!CanAfford(50, 100, 2, 1), "short of pilots");
        Check(CanAfford(0, 0, 0, 0), "free affords");
        Check(DrainDue(2, 0, true, false, 0, 100), "idle, entries, affordable: due");
        Check(!DrainDue(0, 0, true, false, 0, 100), "nothing queued");
        Check(!DrainDue(2, 0x1000, true, false, 0, 100), "still building: wait");
        Check(!DrainDue(2, 0, false, false, 0, 100), "cannot pay: wait");
        Check(!DrainDue(2, 0, true, true, 100, 400), "inside the issue gap");
        Check(DrainDue(2, 0, true, true, 100, 100 + kIssueGapMs), "gap elapsed");
    }

    void TextTests()
    {
        char buf[48];
        std::snprintf(buf, sizeof(buf), "%s", "Tank 45%");
        AppendQueuedSuffix(buf, sizeof(buf), 2);
        Check(std::strcmp(buf, "Tank 45% +2") == 0, "suffix for two queued");
        std::snprintf(buf, sizeof(buf), "%s", "Tank 45%");
        AppendQueuedSuffix(buf, sizeof(buf), 10);
        Check(std::strcmp(buf, "Tank 45% +10") == 0, "two-digit suffix");
        std::snprintf(buf, sizeof(buf), "%s", "Tank 45%");
        AppendQueuedSuffix(buf, sizeof(buf), 0);
        Check(std::strcmp(buf, "Tank 45%") == 0, "no suffix when nothing is queued");
        char small[8];
        std::snprintf(small, sizeof(small), "%s", "Tank 45");
        AppendQueuedSuffix(small, sizeof(small), 3);
        Check(std::strcmp(small, "Tank +3") == 0, "a small buffer cuts the base and stays terminated");

        char out[64];
        Check(FormatWaitingText("Tank", "waiting for scrap", out, sizeof(out)) &&
                  std::strcmp(out, "Tank waiting for scrap") == 0,
              "waiting text");
        Check(!FormatWaitingText("", "waiting for scrap", out, sizeof(out)), "empty label refused");
        Check(!FormatWaitingText("Tank", "", out, sizeof(out)), "empty phrase refused");
        Check(!FormatWaitingText("Tank", "waiting for scrap", out, 10), "too small refused");
    }
}

int main()
{
    BusyTests();
    PickTests();
    TableTests();
    PopAndClearTests();
    RecentIssueTests();
    DrainTests();
    TextTests();
    return OpenShimTest::ExitCode();
}
