#include "producer_rally_policy.h"

#include <cstdio>
#include <limits>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::ProducerRallyPolicy;

namespace
{
    KeyGate OpenGate()
    {
        KeyGate gate;
        gate.featureActive = true;
        gate.worldInteractive = true;
        gate.editorActive = false;
        gate.eligibleProducerSelected = true;
        return gate;
    }

    KeyEvent Down(bool shift = false, bool ctrl = false, bool alt = false)
    {
        KeyEvent key;
        key.msg = kWmKeyDown;
        key.vk = kVkV;
        key.lParam = 1;
        key.shift = shift;
        key.ctrl = ctrl;
        key.alt = alt;
        return key;
    }

    KeyEvent Repeat()
    {
        KeyEvent key = Down();
        key.lParam |= kLParamPreviousStateBit;
        return key;
    }

    KeyEvent Up()
    {
        KeyEvent key;
        key.msg = kWmKeyUp;
        key.vk = kVkV;
        key.lParam = 0xC0000001ull;
        return key;
    }

    void TestModifiers()
    {
        KeyLatch latch;
        KeyDecision d = ClassifyRallyKey(Down(), OpenGate(), latch);
        Check(d.swallow && d.action == KeyAction::SetRally, "V sets the rally");

        latch = {};
        d = ClassifyRallyKey(Down(true), OpenGate(), latch);
        Check(d.swallow && d.action == KeyAction::ClearRally, "Shift+V clears the rally");

        latch = {};
        d = ClassifyRallyKey(Down(false, true), OpenGate(), latch);
        Check(!d.swallow && d.action == KeyAction::None, "Ctrl+V passes through");

        latch = {};
        d = ClassifyRallyKey(Down(true, true), OpenGate(), latch);
        Check(!d.swallow && d.action == KeyAction::None, "Ctrl+Shift+V passes through");

        latch = {};
        d = ClassifyRallyKey(Down(false, false, true), OpenGate(), latch);
        Check(!d.swallow && d.action == KeyAction::None, "Alt+V passes through");

        latch = {};
        KeyEvent other = Down();
        other.vk = 0x42; // B
        d = ClassifyRallyKey(other, OpenGate(), latch);
        Check(!d.swallow && d.action == KeyAction::None, "other keys pass through");
        Check(!latch.downSwallowed, "other keys leave the latch alone");
    }

    void TestGate()
    {
        KeyLatch latch;
        KeyGate gate = OpenGate();
        gate.eligibleProducerSelected = false;
        KeyDecision d = ClassifyRallyKey(Down(), gate, latch);
        Check(!d.swallow && d.action == KeyAction::None, "no producer selected passes through");

        gate = OpenGate();
        gate.editorActive = true;
        d = ClassifyRallyKey(Down(), gate, latch);
        Check(!d.swallow && d.action == KeyAction::None, "editor on passes V through (edit_vertflip)");
        d = ClassifyRallyKey(Down(true), gate, latch);
        Check(!d.swallow, "editor on passes Shift+V through");

        gate = OpenGate();
        gate.featureActive = false;
        d = ClassifyRallyKey(Down(), gate, latch);
        Check(!d.swallow, "feature off (ini, MP or unhooked) passes through");

        gate = OpenGate();
        gate.worldInteractive = false;
        d = ClassifyRallyKey(Down(), gate, latch);
        Check(!d.swallow, "shell screen or no world passes through");
    }

    void TestAutorepeatAndKeyUp()
    {
        KeyLatch latch;
        KeyDecision d = ClassifyRallyKey(Down(), OpenGate(), latch);
        Check(d.swallow && latch.downSwallowed, "swallowed keydown arms the latch");
        d = ClassifyRallyKey(Repeat(), OpenGate(), latch);
        Check(d.swallow && d.action == KeyAction::None, "autorepeat of a swallowed key is hidden, no action");
        d = ClassifyRallyKey(Up(), OpenGate(), latch);
        Check(d.swallow && !latch.downSwallowed, "matching keyup swallowed and latch cleared");
        d = ClassifyRallyKey(Up(), OpenGate(), latch);
        Check(!d.swallow, "a second keyup passes through");

        latch = {};
        KeyGate closed = OpenGate();
        closed.eligibleProducerSelected = false;
        d = ClassifyRallyKey(Down(), closed, latch);
        Check(!d.swallow && !latch.downSwallowed, "passed keydown leaves the latch clear");
        // The selection changes while V is held: still no action and the
        // keyup goes to the game, which saw the keydown.
        d = ClassifyRallyKey(Repeat(), OpenGate(), latch);
        Check(!d.swallow && d.action == KeyAction::None, "autorepeat never starts an action");
        d = ClassifyRallyKey(Up(), OpenGate(), latch);
        Check(!d.swallow, "keyup of a passed keydown passes through");

        // A fresh keydown after a lost keyup re-decides the latch.
        latch.downSwallowed = true;
        d = ClassifyRallyKey(Down(), closed, latch);
        Check(!d.swallow && !latch.downSwallowed, "fresh keydown resets a stale latch");
    }

    void TestBuiltUnit()
    {
        BuiltUnit unit;
        unit.present = true;
        unit.canCommand = true;
        Check(ClassifyBuiltUnit(true, unit) == BuiltUnitVerdict::Rally, "commandable new unit rallies");
        Check(ClassifyBuiltUnit(false, unit) == BuiltUnitVerdict::NoRally, "no rally, no order");

        BuiltUnit scav = unit;
        scav.isScavenger = true;
        Check(ClassifyBuiltUnit(true, scav) == BuiltUnitVerdict::Scavenger, "scavenger skipped");

        BuiltUnit cons = unit;
        cons.isConstructor = true;
        Check(ClassifyBuiltUnit(true, cons) == BuiltUnitVerdict::Constructor, "constructor skipped");

        BuiltUnit stuck = unit;
        stuck.canCommand = false;
        Check(ClassifyBuiltUnit(true, stuck) == BuiltUnitVerdict::NotCommandable, "uncommandable skipped");

        BuiltUnit ordered = unit;
        ordered.pendingCommand = 3;
        Check(ClassifyBuiltUnit(true, ordered) == BuiltUnitVerdict::AlreadyOrdered,
              "a script's order is not overridden");

        Check(ClassifyBuiltUnit(true, BuiltUnit{}) == BuiltUnitVerdict::NoUnit, "failed build skipped");
    }

    void TestTable()
    {
        RallyTable<2> table;
        const float a[3] = { 1.0f, 2.0f, 3.0f };
        const float b[3] = { 4.0f, 5.0f, 6.0f };

        Check(!table.Set(0, 1, a), "null producer refused");
        Check(table.Set(0x1000, 11, a), "first set");
        Check(table.Set(0x1000, 11, b), "re-set");
        const RallyEntry* entry = table.Find(0x1000);
        Check(entry && entry->pos[0] == 4.0f && entry->producerHandle == 11, "re-set moved the rally");
        Check(table.Size() == 1, "re-set does not add a row");

        Check(table.Set(0x2000, 22, a), "second producer");
        Check(!table.Set(0x3000, 33, a), "full table refuses a new producer");
        Check(table.Set(0x2000, 22, b), "full table still moves an existing rally");

        Check(table.Clear(0x2000), "clear");
        Check(!table.Find(0x2000) && table.Find(0x1000), "clear removes only that producer");
        Check(!table.Clear(0x2000), "clearing twice is a no-op");

        table.ClearAll();
        Check(table.Size() == 0 && !table.Find(0x1000), "clear all empties the table");
    }

    // Identity rotation, camera at the origin looking down +z.
    CameraProjection IdentityCamera()
    {
        CameraProjection cam;
        cam.centerX = 400.0f;
        cam.centerY = 300.0f;
        cam.scaleX = 400.0f;
        cam.scaleY = -400.0f;
        cam.rot[0] = cam.rot[4] = cam.rot[8] = 1.0f;
        return cam;
    }

    void TestProjection()
    {
        CameraProjection cam = IdentityCamera();
        float sx = -1.0f, sy = -1.0f;
        const float ahead[3] = { 0.0f, 0.0f, 10.0f };
        Check(ProjectToScreen(cam, ahead, sx, sy) && sx == 400.0f && sy == 300.0f,
              "a point straight ahead lands on the screen centre");

        const float right[3] = { 5.0f, 5.0f, 10.0f };
        Check(ProjectToScreen(cam, right, sx, sy) && sx == 600.0f && sy == 100.0f,
              "x and y scale by focal/depth from the centre");

        const float behind[3] = { 0.0f, 0.0f, -10.0f };
        Check(!ProjectToScreen(cam, behind, sx, sy), "a point behind the camera is hidden");
        const float onPlane[3] = { 3.0f, 0.0f, 0.0f };
        Check(!ProjectToScreen(cam, onPlane, sx, sy), "a point on the camera plane is hidden");

        // The view translation is applied after the rotation (FUN_0081fe60).
        cam.trans[2] = -5.0;
        const float near[3] = { 0.0f, 0.0f, 5.0f };
        Check(!ProjectToScreen(cam, near, sx, sy), "translation moves the camera plane");
        const float far[3] = { 2.0f, 0.0f, 9.0f };
        Check(ProjectToScreen(cam, far, sx, sy) && sx == 600.0f, "translated depth divides x");

        // A 90-degree yaw: world +x becomes view depth.
        CameraProjection yaw = IdentityCamera();
        yaw.rot[0] = 0.0f; yaw.rot[8] = 0.0f;
        yaw.rot[2] = 1.0f; // world x -> view z
        yaw.rot[6] = -1.0f; // world z -> view -x
        const float side[3] = { 10.0f, 0.0f, 0.0f };
        Check(ProjectToScreen(yaw, side, sx, sy) && sx == 400.0f, "rotation uses the column layout of the stock product");

        CameraProjection broken = IdentityCamera();
        broken.scaleX = std::numeric_limits<float>::quiet_NaN();
        Check(!ProjectToScreen(broken, ahead, sx, sy), "NaN camera data hides the marker");

        Check(OnScreen(0.0f, 0.0f, 800, 600) && !OnScreen(800.0f, 10.0f, 800, 600) &&
              !OnScreen(10.0f, -1.0f, 800, 600), "on-screen bounds");
    }

    void TestLineDots()
    {
        float dots[8][2] = {};
        Check(LineDots(0.0f, 0.0f, 10.0f, 0.0f, 20.0f, 8, dots) == 0, "a line shorter than the spacing has no dots");
        size_t n = LineDots(0.0f, 0.0f, 100.0f, 0.0f, 20.0f, 8, dots);
        Check(n == 4, "100 px at 20 px spacing gives 4 inner dots");
        Check(n == 4 && dots[0][0] == 20.0f && dots[3][0] == 80.0f && dots[1][1] == 0.0f, "dots are evenly spaced");
        n = LineDots(0.0f, 0.0f, 1000.0f, 0.0f, 20.0f, 8, dots);
        Check(n == 8, "long lines are capped");
        Check(LineDots(0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 8, dots) == 0, "zero spacing draws nothing");
    }

    void TestTickPlan()
    {
        TickPlan plan = PlanTick(false, true, true, true, true);
        Check(!plan.applyPending && plan.dropPending && !plan.livenessCheck && !plan.standDownClear,
              "no game-state work outside an interactive world (modal loop, pause menu)");
        plan = PlanTick(false, false, false, true, true);
        Check(!plan.standDownClear, "a stand-down waits for an interactive tick");
        plan = PlanTick(true, false, true, true, true);
        Check(plan.standDownClear && plan.dropPending && !plan.applyPending, "stood down: forget rallies, drop presses");
        plan = PlanTick(true, true, true, true, false);
        Check(plan.applyPending && !plan.livenessCheck, "active: apply the press; liveness only when due");
        plan = PlanTick(true, true, false, true, true);
        Check(plan.livenessCheck && !plan.applyPending, "active with rallies: liveness when due");
        plan = PlanTick(true, true, false, false, true);
        Check(!plan.livenessCheck, "no rallies, nothing to check");
    }

    void TestSetMode()
    {
        // V without the command hooks keeps the immediate set.
        Check(PlanSetKey(false, false, false) == SetKeyPlan::SetImmediately, "no hooks: V sets at once");
        Check(PlanSetKey(false, true, true) == SetKeyPlan::SetImmediately, "no hooks: never a cancel");
        Check(PlanSetKey(true, false, false) == SetKeyPlan::Arm, "hooks: V arms");
        Check(PlanSetKey(true, true, true) == SetKeyPlan::Cancel, "armed, same selection: V cancels");
        Check(PlanSetKey(true, true, false) == SetKeyPlan::Arm, "armed, other selection: V re-arms");

        ArmedSelection<4> armed;
        const uint32_t sel[] = { 0x101, 0x202 };
        const uint32_t reordered[] = { 0x202, 0x101 };
        const uint32_t grown[] = { 0x101, 0x202, 0x303 };
        const uint32_t swapped[] = { 0x101, 0x303 };
        const uint32_t tooMany[] = { 1, 2, 3, 4, 5 };
        Check(!armed.Matches(sel, 2), "nothing armed matches nothing");
        Check(!armed.Capture(sel, 0) && armed.Size() == 0, "an empty selection is not armed");
        Check(!armed.Capture(tooMany, 5) && armed.Size() == 0, "an oversized selection is not armed");
        Check(armed.Capture(sel, 2) && armed.Size() == 2, "a selection is captured");
        Check(armed.Matches(sel, 2), "same selection matches");
        Check(armed.Matches(reordered, 2), "order does not matter");
        Check(!armed.Matches(grown, 3), "an added unit breaks the match");
        Check(!armed.Matches(sel, 1), "a removed unit breaks the match");
        Check(!armed.Matches(swapped, 2), "a different unit breaks the match");
        Check(!armed.Matches(nullptr, 0), "no selection breaks the match");
        armed.Reset();
        Check(!armed.Matches(sel, 2), "reset forgets the selection");

        Check(OverrideAimCommand(true, true), "armed with the same selection: aim is overridden");
        Check(!OverrideAimCommand(true, false), "selection changed: stock aim command");
        Check(!OverrideAimCommand(false, true), "not armed: stock aim command");

        Check(BroadcastIsRallyConfirm(true, true, true, kCmdGoCommand, true), "armed Go to ground confirms");
        Check(!BroadcastIsRallyConfirm(false, true, true, kCmdGoCommand, true), "not armed: stock order");
        Check(!BroadcastIsRallyConfirm(true, false, true, kCmdGoCommand, true), "selection changed: stock order");
        Check(!BroadcastIsRallyConfirm(true, true, false, kCmdGoCommand, true), "another panel: stock order");
        Check(!BroadcastIsRallyConfirm(true, true, true, 4, true), "another command: stock order");
        Check(!BroadcastIsRallyConfirm(true, true, true, kCmdGoCommand, false), "no ground point: stock order");

        Check(!KeepArmed(false, true, true), "stood down: disarm");
        Check(KeepArmed(true, false, false), "modal loop: the mode holds");
        Check(!KeepArmed(true, true, false), "selection changed: disarm");
        Check(KeepArmed(true, true, true), "unchanged: the mode holds");
    }
}

int main()
{
    TestModifiers();
    TestGate();
    TestAutorepeatAndKeyUp();
    TestBuiltUnit();
    TestTable();
    TestProjection();
    TestLineDots();
    TestTickPlan();
    TestSetMode();
    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "producer_rally_policy_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("producer_rally_policy_tests: all checks passed\n");
    return 0;
}
