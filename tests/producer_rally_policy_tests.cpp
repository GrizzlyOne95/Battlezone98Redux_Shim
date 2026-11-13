#include "producer_rally_policy.h"

#include <cstdio>
#include <limits>
#include <string>
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

    void TestPanelRow()
    {
        PanelRowGate gate;
        gate.active = true;
        gate.userObject = true;
        gate.branchInputHeld = false;
        gate.panelState = kPanelUnitCommandState;
        gate.selectionCount = 1;
        gate.altLayout = false;
        gate.eligibleProducer = true;
        Check(PanelRowVisible(gate), "unit-command panel with a producer: row shown");
        PanelRowGate g = gate;
        g.active = false;
        Check(!PanelRowVisible(g), "feature off: no row");
        g = gate;
        g.userObject = false;
        Check(!PanelRowVisible(g), "no user object (dead, respawning): stale state, no row");
        g = gate;
        g.branchInputHeld = true;
        Check(!PanelRowVisible(g), "DAT_00919875 set: not the unit-command branch, no row");
        g = gate;
        g.panelState = 2;
        Check(!PanelRowVisible(g), "unit-type menu: no row");
        g = gate;
        g.selectionCount = 0;
        Check(!PanelRowVisible(g), "stale state with no selection: no row");
        g = gate;
        g.altLayout = true;
        Check(!PanelRowVisible(g), "alternate layout: no row");
        g = gate;
        g.eligibleProducer = false;
        Check(!PanelRowVisible(g), "no Recycler/Factory selected: no row");

        Check(std::string(kPanelRowLabel) == "Rally", "the row reads Rally");
        Check(std::string(PanelRowLabel(false)) == "Rally", "not armed: the row reads Rally");
        Check(std::string(PanelRowLabel(true)) == "Cancel", "armed: the row reads Cancel (V cancels)");

        int x = 0, y = 0;
        Check(PanelRowAnchor(31, 300, 278, x, y) && x == 31 && y == 322, "row 13 is one pitch below TAB");
        Check(!PanelRowAnchor(31, 300, 300, x, y), "zero pitch is refused");
        Check(!PanelRowAnchor(31, 278, 300, x, y), "an upward layout is refused");
        Check(!PanelRowAnchor(31, 1000, 100, x, y), "an absurd pitch is refused");

        PixelRect box;
        // A 32x16 atlas sprite at UI scale 2, inset 8.
        Check(KeyBoxRect(100, 322, 8, 32, 16, 2.0f, 2.0f, box), "box from a sprite");
        Check(box.right == 92 && box.left == 28 && box.top == 306 && box.bottom == 338,
              "right-aligned on anchor - inset, centred on the row");
        Check(KeyBoxRect(100, 322, 8, 33, 17, 1.5f, 1.5f, box) && box.right - box.left == 49 &&
                  box.bottom - box.top == 25 && box.top == 322 - 12,
              "sizes truncate and odd heights centre like h >> 1");
        Check(!KeyBoxRect(100, 322, 8, 0, 16, 2.0f, 2.0f, box), "empty sprite: no box");

        Check(CenteredTextY(322, 18.0f) == 313, "text top is row centre minus half the height");
        Check(CenteredTextY(322, 13.5f) == 315, "fractional heights truncate like the stock call");
    }

    void TestKeyCapFill()
    {
        FillRect r[2];
        // key_0's 9x9 at UI scale 2: 18x18, notched by 2 px.
        PixelRect box;
        box.left = 10;
        box.top = 20;
        box.right = 28;
        box.bottom = 38;
        Check(KeyCapFillRects(box, 2.0f, r) == 2, "a scaled cap is two bands");
        Check(r[0].x1 == 10 && r[0].x2 == 27 && r[0].y1 == 22 && r[0].y2 == 35,
              "full-width band, inclusive corners, notched top and bottom");
        Check(r[1].x1 == 12 && r[1].x2 == 25 && r[1].y1 == 20 && r[1].y2 == 37,
              "full-height band, inclusive corners, notched left and right");
        // Scale below 1 still notches by one pixel.
        box.right = 19;
        box.bottom = 29;
        Check(KeyCapFillRects(box, 0.75f, r) == 2 && r[0].y1 == 21 && r[1].x1 == 11, "minimum notch is 1 px");
        // Too small to notch: one plain rect.
        box.right = 12;
        box.bottom = 22;
        Check(KeyCapFillRects(box, 1.0f, r) == 1 && r[0].x1 == 10 && r[0].x2 == 11 && r[0].y2 == 21,
              "a 2x2 cap is one rect");
        box.right = box.left;
        Check(KeyCapFillRects(box, 1.0f, r) == 0, "empty box: nothing to fill");
    }

    void TestSpaceRowLabel()
    {
        Check(SpaceRowLabelOverride(true, "Go To"), "armed Go To reads Rally");
        Check(std::string(kSpaceRowArmedLabel) == "Rally", "the armed SPACE label");
        Check(!SpaceRowLabelOverride(false, "Go To"), "not armed: stock Go To");
        Check(!SpaceRowLabelOverride(true, "Attack"), "another command: stock label");
        Check(!SpaceRowLabelOverride(true, "Go"), "a prefix is not the key");
        Check(!SpaceRowLabelOverride(true, "Go To "), "a longer key is not the key");
        Check(!SpaceRowLabelOverride(true, "go to"), "the key compare is exact");
        Check(!SpaceRowLabelOverride(true, nullptr), "no key: stock label");
    }

    PanelRowLayoutInput LayoutAt2x()
    {
        // UI scale 2: TAB anchor (31, 300), ALT y 278, row right 320.
        PanelRowLayoutInput in;
        in.tabX = 31;
        in.tabY = 300;
        in.altY = 278;
        in.rowRight = 320;
        in.scaleX = 2.0f;
        in.scaleY = 2.0f;
        in.inset = 8;
        in.keyW = 9;
        in.keyH = 9;
        in.labelW = 40.0f;
        in.labelH = 18.0f;
        in.costW = 16.0f;
        in.cancelKnown = true;
        in.cancelW = 60.0f;
        in.viewportW = 1920;
        in.viewportH = 1080;
        in.underlayKnown = true;
        in.underlayTop = 100;
        in.underlaySpriteH = 256;
        return in;
    }

    void TestPanelRowLayout()
    {
        Check(UnderlayBottom(100, 256, 2.0f) == 356, "underlay bottom: top + h * scale / 2");
        Check(UnderlayBottom(100, 255, 1.5f) == 291, "underlay bottom truncates like the stock call");

        // Column right = 320 - 40 + 16 = 296; label at 256; key 18 px wide
        // right-aligned at 256 - 8, so the group starts at 230.
        PanelRowLayoutInput in = LayoutAt2x();
        PanelRowLayout out = ChoosePanelRowLayout(in);
        Check(out.placement == PanelRowPlacement::TabLine && out.rowY == 300 && out.labelX == 256,
              "short TAB label: on the TAB line, right-aligned to the cost column");

        in = LayoutAt2x();
        in.cancelW = 191.0f; // 31 + 191 + 16 = 238 > 230
        out = ChoosePanelRowLayout(in);
        Check(out.placement == PanelRowPlacement::BelowUnderlay && out.rowY == 356 + 8 + 9 && out.labelX == 256,
              "long TAB label: under the underlay, clear by one inset plus half the row");
        in.cancelW = 183.0f; // 31 + 183 + 16 = 230: just fits
        Check(ChoosePanelRowLayout(in).placement == PanelRowPlacement::TabLine, "a label that just fits stays");

        in = LayoutAt2x();
        in.cancelKnown = false;
        Check(ChoosePanelRowLayout(in).placement == PanelRowPlacement::BelowUnderlay,
              "TAB label not measurable: the safe place under the underlay");

        in = LayoutAt2x();
        in.cancelW = 500.0f;
        in.underlayTop = 0;
        in.underlaySpriteH = 100; // bottom 100, above the TAB row
        out = ChoosePanelRowLayout(in);
        Check(out.placement == PanelRowPlacement::BelowUnderlay && out.rowY == 322,
              "a short underlay never lifts the row onto TAB");

        in = LayoutAt2x();
        in.cancelW = 500.0f;
        in.viewportW = 400;
        out = ChoosePanelRowLayout(in);
        Check(out.placement == PanelRowPlacement::BelowTab && out.rowY == 322,
              "no underlay at 400 px: one pitch under TAB");

        in = LayoutAt2x();
        in.cancelW = 500.0f;
        in.underlayKnown = false;
        Check(ChoosePanelRowLayout(in).placement == PanelRowPlacement::Hidden,
              "underlay drawn but unreadable: hidden, never over it");
        in.underlayKnown = true;
        in.underlaySpriteH = 0;
        Check(ChoosePanelRowLayout(in).placement == PanelRowPlacement::Hidden, "empty underlay sprite: hidden");

        in = LayoutAt2x();
        in.cancelW = 500.0f;
        in.viewportH = 380; // 373 + 9 > 380
        Check(ChoosePanelRowLayout(in).placement == PanelRowPlacement::Hidden, "off the bottom of the screen: hidden");

        in = LayoutAt2x();
        in.labelW = 300.0f;
        Check(ChoosePanelRowLayout(in).placement == PanelRowPlacement::Hidden,
              "a label wider than the row: hidden");
        in = LayoutAt2x();
        in.rowRight = 1900;
        in.viewportW = 1600;
        Check(ChoosePanelRowLayout(in).placement == PanelRowPlacement::Hidden, "column off the right edge: hidden");

        in = LayoutAt2x();
        in.scaleX = 0.0f;
        Check(ChoosePanelRowLayout(in).placement == PanelRowPlacement::Hidden, "no UI scale: hidden");
        in = LayoutAt2x();
        in.scaleY = std::numeric_limits<float>::quiet_NaN();
        Check(ChoosePanelRowLayout(in).placement == PanelRowPlacement::Hidden, "NaN UI scale: hidden");
        in = LayoutAt2x();
        in.altY = 300;
        Check(ChoosePanelRowLayout(in).placement == PanelRowPlacement::Hidden, "no row pitch: hidden");
        in = LayoutAt2x();
        in.keyW = 0;
        Check(ChoosePanelRowLayout(in).placement == PanelRowPlacement::Hidden, "no key size: hidden");

        // 640x480 at UI scale 1: column right 160 - 20 + 8 = 148, label at
        // 128, key 9 px at 124, group from 115; "Cancel" ends at 16 + 30 + 8.
        PanelRowLayoutInput small;
        small.tabX = 16;
        small.tabY = 150;
        small.altY = 139;
        small.rowRight = 160;
        small.scaleX = 1.0f;
        small.scaleY = 1.0f;
        small.inset = 4;
        small.keyW = 9;
        small.keyH = 9;
        small.labelW = 20.0f;
        small.labelH = 9.0f;
        small.costW = 8.0f;
        small.cancelKnown = true;
        small.cancelW = 30.0f;
        small.viewportW = 640;
        small.viewportH = 480;
        small.underlayKnown = true;
        small.underlayTop = 50;
        small.underlaySpriteH = 256;
        out = ChoosePanelRowLayout(small);
        Check(out.placement == PanelRowPlacement::TabLine && out.labelX == 128 && out.rowY == 150,
              "640x480: on the TAB line");
    }
}

void TestProducerLabelAndLamp()
{
    Check(UseAmberLamp(ProducerKind::Factory), "Factory lamp is amber");
    Check(!UseAmberLamp(ProducerKind::Recycler), "Recycler lamp stays green");
    Check(!UseAmberLamp(ProducerKind::Unknown), "unclassified producer keeps the current green lamp");

    char out[kLabelMax];
    size_t n = FormatRallyLabel("Recycler", out, sizeof(out));
    Check(std::string(out) == "Recycler rally" && n == 14, "unitName plus ' rally'");
    n = FormatRallyLabel("Factory", out, sizeof(out));
    Check(std::string(out) == "Factory rally" && n == 13, "Factory label");
    n = FormatRallyLabel("", out, sizeof(out));
    Check(std::string(out) == "Rally" && n == 5, "empty unitName falls back to the generic label");
    n = FormatRallyLabel(nullptr, out, sizeof(out));
    Check(std::string(out) == "Rally" && n == 5, "null unitName falls back to the generic label");
    n = FormatRallyLabel("   ", out, sizeof(out));
    Check(std::string(out) == "Rally", "blank unitName falls back to the generic label");
    n = FormatRallyLabel("  Heavy\tRecycler \x01 ", out, sizeof(out));
    Check(std::string(out) == "HeavyRecycler rally", "control characters dropped, spaces trimmed");
    n = FormatRallyLabel("\xC3\xA9\xC3\xA9", out, sizeof(out));
    Check(std::string(out) == "Rally", "non-ASCII only falls back to the generic label");
    n = FormatRallyLabel("ABCDEFGHIJKLMNOPQRSTUVWXYZ", out, sizeof(out));
    Check(std::string(out) == "ABCDEFGHIJKLMNOPQRST rally" && n == 26 && n < kLabelMax, "long unitName is capped");
    char tiny[8];
    n = FormatRallyLabel("Recycler", tiny, sizeof(tiny));
    Check(n == 7 && tiny[7] == '\0' && std::string(tiny) == "Recycle", "a small buffer truncates and terminates");
    Check(FormatRallyLabel("x", nullptr, 8) == 0 && FormatRallyLabel("x", out, 0) == 0, "no buffer: nothing written");
    Check(LabelHalfWidth(5) == 22, "generic label keeps the original 22 px half width");
    Check(LabelHalfWidth(14) > LabelHalfWidth(5), "longer labels get a wider panel");
}

int main()
{
    TestModifiers();
    TestGate();
    TestAutorepeatAndKeyUp();
    TestBuiltUnit();
    TestTable();
    TestProjection();
    TestTickPlan();
    TestSetMode();
    TestPanelRow();
    TestKeyCapFill();
    TestSpaceRowLabel();
    TestPanelRowLayout();
    TestProducerLabelAndLamp();
    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "producer_rally_policy_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("producer_rally_policy_tests: all checks passed\n");
    return 0;
}
