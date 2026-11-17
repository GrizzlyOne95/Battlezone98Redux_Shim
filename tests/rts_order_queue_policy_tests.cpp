// RtsOrderQueue's engine-independent logic: which commands queue, the queue
// table and its caps, the pop gate, clearing, the per-unit press plan and the
// label text.
#include "rts_order_queue_policy.h"
#include "test_check.h"

#include <cstring>

using namespace BZROpenShim::RtsOrderQueuePolicy;
using OpenShimTest::Check;

namespace
{
    Entry Go(float x, float z)
    {
        Entry e;
        e.cmd = kCmdGo;
        e.kind = Kind::Ground;
        e.where[0] = x;
        e.where[2] = z;
        e.param = 3;
        return e;
    }

    Entry Defend(uint32_t target)
    {
        Entry e;
        e.cmd = kCmdDefend;
        e.kind = Kind::Object;
        e.target = target;
        return e;
    }

    void AllowlistTests()
    {
        const int yes[] = {kCmdGo, kCmdAttack, kCmdFollow, kCmdPickup, kCmdDropoff, kCmdGetRepair, kCmdGetReload,
                           kCmdDefend};
        for (int cmd : yes)
            Check(IsQueueable(cmd), "an order command queues");
        const int no[] = {0, kCmdSelect, kCmdStop, kCmdNoDropoff, kCmdBuild, 6, 12, 13, 14, 16, 17, 18, 19, 20, 22, 26, -1, 99};
        for (int cmd : no)
            Check(!IsQueueable(cmd), "select, no-dropoff, stop, build and the rest stay stock");
    }

    void ArmedTests()
    {
        Check(QueueArmed(true, true, 1, kCmdDefend), "armed: active, modifier, selection, queueable");
        Check(!QueueArmed(false, true, 1, kCmdDefend), "option off");
        Check(!QueueArmed(true, false, 1, kCmdDefend), "modifier not held");
        Check(!QueueArmed(true, true, 0, kCmdDefend), "nothing selected");
        Check(!QueueArmed(true, true, 1, kCmdSelect), "Shift+Space on a select button stays stock");
        Check(!QueueArmed(true, true, 1, kCmdNoDropoff), "no-dropoff stays stock");
        Check(ShouldQueuePress(true, true, 2, kCmdGo, false, true), "a queueable press queues");
        Check(!ShouldQueuePress(true, true, 2, kCmdGo, true, true), "a pending rally confirm keeps priority");
        Check(!ShouldQueuePress(true, true, 2, kCmdGo, false, false), "a null target is never queued");
    }

    void PlanTests()
    {
        Check(PlanUnit(false, 0, true) == UnitAction::Skip, "an ineligible unit is skipped");
        Check(PlanUnit(true, 0, true) == UnitAction::IssueNow, "idle with no queue: order now");
        Check(PlanUnit(true, 0, false) == UnitAction::Append, "busy: append");
        Check(PlanUnit(true, 2, true) == UnitAction::Append, "idle but already queued: append, the drain pops");
        Check(PlanUnit(true, 2, false) == UnitAction::Append, "busy and queued: append");
    }

    void TableTests()
    {
        Table t;
        Check(t.UnitCount() == 0 && t.Depth(5) == 0, "starts empty");
        Check(!t.CanPush(0), "handle 0 is no unit");
        Check(t.Push(5, Go(1, 2)) == 1 && t.Push(5, Defend(9)) == 2, "pushes grow the depth");
        Check(t.Depth(5) == 2 && t.UnitCount() == 1, "one unit, two entries");

        Entry snap[kMaxEntries];
        Check(t.Snapshot(5, snap, kMaxEntries) == 2 && snap[0].cmd == kCmdGo && snap[1].cmd == kCmdDefend &&
                  snap[1].target == 9,
              "snapshot keeps order");
        Check(t.Snapshot(5, snap, 1) == 1, "snapshot honours its capacity");
        Check(t.Snapshot(6, snap, kMaxEntries) == 0, "unknown unit has none");

        for (int i = 2; i < kMaxEntries; ++i)
            Check(t.Push(5, Go(static_cast<float>(i), 0)) == i + 1, "fills to the cap");
        Check(!t.CanPush(5) && t.Push(5, Go(0, 0)) == 0, "the ninth entry is refused");
        Check(t.Depth(5) == kMaxEntries, "a refusal changes nothing");

        // The unit cap.
        Table many;
        for (uint32_t h = 1; h <= static_cast<uint32_t>(kMaxUnits); ++h)
            Check(many.Push(h, Go(0, 0)) == 1, "32 units take a queue");
        Check(many.UnitCount() == kMaxUnits, "table full");
        Check(!many.CanPush(100) && many.Push(100, Go(0, 0)) == 0, "a 33rd unit is refused");
        Check(many.CanPush(7) && many.Push(7, Go(1, 1)) == 2, "a queued unit still appends when the table is full");
        Check(many.Clear(7) == 2 && many.UnitCount() == kMaxUnits - 1, "clearing frees the slot");
        Check(many.CanPush(100) && many.Push(100, Go(0, 0)) == 1, "which a new unit then takes");
        Check(many.HandleAt(0) != 0 && many.HandleAt(kMaxUnits) == 0, "HandleAt walks the units");
        Check(many.ClearAll() == kMaxUnits && many.UnitCount() == 0, "ClearAll drops every queue");
    }

    void PopTests()
    {
        Table t;
        t.Push(5, Go(1, 2));
        t.Push(5, Defend(9));
        Check(!t.PopDue(5, false, 10000), "never while busy");
        Check(!t.PopDue(6, true, 10000), "never without a queue");
        Check(t.PopDue(5, true, 0), "an idle unit with an entry and no pop yet is due");
        Entry e;
        Check(t.PopFront(5, e) && e.cmd == kCmdGo && e.where[0] == 1.0f && e.param == 3, "pops the front first");
        t.NoteIssued(5, 1000);
        Check(!t.PopDue(5, true, 1000) && !t.PopDue(5, true, 1499), "less than 500 ms after a pop: wait");
        Check(t.PopDue(5, true, 1500), "500 ms after a pop: due");
        Check(t.PopFront(5, e) && e.cmd == kCmdDefend && e.target == 9, "then the next");
        Check(t.Depth(5) == 0 && t.UnitCount() == 0, "an emptied queue frees its slot");
        Check(!t.PopFront(5, e), "nothing left");
        t.NoteIssued(5, 2000); // no queue: harmless
        Check(!t.PopDue(5, true, 5000), "an emptied queue is never due");

        // A dropped (dead-target) entry does not consume the gap: popping
        // without NoteIssued leaves the unit due.
        Table d;
        d.Push(8, Defend(1));
        d.Push(8, Go(4, 4));
        Check(d.PopFront(8, e), "drop the dead one");
        Check(d.PopDue(8, true, 0), "still due for the next entry");
    }

    void ClearTests()
    {
        Table t;
        t.Push(1, Go(0, 0));
        t.Push(2, Go(0, 0));
        Check(t.Clear(3) == 0, "clearing an unqueued unit does nothing");
        Check(t.Clear(1) == 1 && t.Depth(1) == 0 && t.Depth(2) == 1, "clear one unit only");
        Check(t.Push(1, Defend(4)) == 1, "a cleared unit starts a fresh queue");
        t.NoteIssued(1, 100);
        t.Clear(1);
        t.Push(1, Go(0, 0));
        Check(t.PopDue(1, true, 101), "a cleared queue's pop stamp does not leak into the next");
        Check(std::strcmp(ReasonName(ClearReason::Dead), "unit gone") == 0 &&
                  std::strcmp(ReasonName(ClearReason::PlainOrder), "plain order") == 0 &&
                  std::strcmp(ReasonName(ClearReason::Reset), "mission reset") == 0 &&
                  std::strcmp(ReasonName(ClearReason::OptionOff), "option off") == 0 &&
                  std::strcmp(ReasonName(ClearReason::Multiplayer), "multiplayer") == 0,
              "every clear reason has a log name");
    }

    void LabelTests()
    {
        char out[kLabelCapacity];
        Check(FormatQueueLabel("Queue", "Defend", out, sizeof(out)) && std::strcmp(out, "Queue Defend") == 0,
              "Queue Defend");
        Check(FormatQueueLabel("Queue", "Go To", out, sizeof(out)) && std::strcmp(out, "Queue Go To") == 0,
              "Queue Go To");
        char tiny[12];
        Check(!FormatQueueLabel("Queue", "Defend", tiny, sizeof(tiny)), "12 characters need 13 bytes");
        char exact[13];
        Check(FormatQueueLabel("Queue", "Defend", exact, sizeof(exact)), "13 bytes just fit");
        Check(!FormatQueueLabel("", "Defend", out, sizeof(out)), "an empty prefix is refused");
        Check(!FormatQueueLabel("Queue", "", out, sizeof(out)), "an empty stock label is refused");
        Check(!FormatQueueLabel(nullptr, "Defend", out, sizeof(out)) &&
                  !FormatQueueLabel("Queue", nullptr, out, sizeof(out)),
              "null text is refused");
        Check(!FormatQueueLabel("Queue", "Defend", nullptr, 0), "no buffer is refused");
    }

    void ColourTests()
    {
        Check(kQueueColour.a > 0.0f && kQueueColour.r > kQueueColour.g && kQueueColour.g > kQueueColour.b,
              "amber: red over green over blue");
    }
}

int main()
{
    AllowlistTests();
    ArmedTests();
    PlanTests();
    TableTests();
    PopTests();
    ClearTests();
    LabelTests();
    ColourTests();
    return OpenShimTest::ExitCode();
}
