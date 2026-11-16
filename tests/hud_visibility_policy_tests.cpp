#include "hud_visibility_policy.h"

#include <cstdio>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::HudVisibilityPolicy;

namespace
{
    KeyMessage Key(unsigned msg, bool ctrl, bool shift = false, bool alt = false, bool autorepeat = false)
    {
        KeyMessage key;
        key.msg = msg;
        key.scanCode = kScanEqual;
        key.ctrl = ctrl;
        key.shift = shift;
        key.alt = alt;
        key.autorepeat = autorepeat;
        return key;
    }

    Gate LiveGate()
    {
        Gate gate;
        gate.worldTicking = true;
        gate.shellReadable = true;
        gate.shellScreenUp = false;
        gate.textEditorFocused = false;
        return gate;
    }

    void TestGate()
    {
        Check(GateOpen(LiveGate()), "live gameplay opens the gate");
        Check(!GateOpen(Gate{}), "default gate is closed (editor focus assumed)");
        Gate g = LiveGate();
        g.worldTicking = false;
        Check(!GateOpen(g), "no recent world tick closes the gate");
        g = LiveGate();
        g.shellReadable = false;
        Check(!GateOpen(g), "unreadable shell state closes the gate");
        g = LiveGate();
        g.shellScreenUp = true;
        Check(!GateOpen(g), "pause/options screen closes the gate");
        g = LiveGate();
        g.textEditorFocused = true;
        Check(!GateOpen(g), "focused chat editor closes the gate");
    }

    void TestPlainEqualPasses()
    {
        KeyLatch latch;
        Check(Decide(Key(kWmKeyDown, false), true, latch) == KeyAction::Pass, "plain = passes (stock zoom)");
        Check(Decide(Key(kWmKeyDown, false, false, false, true), true, latch) == KeyAction::Pass,
              "plain = autorepeat passes");
        Check(Decide(Key(kWmKeyUp, false), true, latch) == KeyAction::Pass, "plain = key-up passes");
        Check(Decide(Key(kWmKeyDown, true, true), true, latch) == KeyAction::Pass, "Ctrl+Shift+= passes");
        Check(Decide(Key(kWmSysKeyDown, true, false, true), true, latch) == KeyAction::Pass, "Ctrl+Alt+= passes");
        Check(Decide(Key(kWmKeyDown, false, true), true, latch) == KeyAction::Pass, "Shift+= passes");
        Check(!latch.swallowed, "nothing swallowed");
    }

    void TestOtherKeysPass()
    {
        KeyLatch latch;
        KeyMessage other = Key(kWmKeyDown, true);
        other.scanCode = 0x0C; // Minus
        Check(!IsChordKey(other), "minus is not the chord key");
        Check(Decide(other, true, latch) == KeyAction::Pass, "Ctrl+- passes");
        KeyMessage pad = Key(kWmKeyDown, true);
        pad.scanCode = 0x4E; // numpad plus (GreyPlus)
        Check(Decide(pad, true, latch) == KeyAction::Pass, "Ctrl+numpad plus passes");
        KeyMessage ext = Key(kWmKeyDown, true);
        ext.extended = true;
        Check(Decide(ext, true, latch) == KeyAction::Pass, "an extended 0x0D scan code passes");
        Check(!latch.swallowed, "nothing swallowed");
    }

    void TestChordTogglesAndSwallowsWholePress()
    {
        KeyLatch latch;
        Check(Decide(Key(kWmKeyDown, true), true, latch) == KeyAction::SwallowToggle, "Ctrl+= toggles");
        Check(latch.swallowed, "press marked swallowed");
        Check(Decide(Key(kWmKeyDown, true, false, false, true), true, latch) == KeyAction::Swallow,
              "its autorepeat is swallowed, not a second toggle");
        Check(Decide(Key(kWmKeyUp, false), true, latch) == KeyAction::Swallow,
              "its key-up is swallowed even after Ctrl was released");
        Check(!latch.swallowed, "latch cleared by key-up");
        Check(Decide(Key(kWmKeyUp, true), true, latch) == KeyAction::Pass, "a stray key-up passes");
        Check(Decide(Key(kWmKeyDown, true), true, latch) == KeyAction::SwallowToggle, "a second press toggles again");
    }

    void TestClosedGatePasses()
    {
        KeyLatch latch;
        Check(Decide(Key(kWmKeyDown, true), false, latch) == KeyAction::Pass, "closed gate: Ctrl+= passes");
        Check(!latch.swallowed, "closed gate: not swallowed");
        Check(Decide(Key(kWmKeyUp, true), false, latch) == KeyAction::Pass, "closed gate: key-up passes");
    }

    void TestRepeatOfUnswallowedPressPasses()
    {
        KeyLatch latch;
        // "=" held first (zooming), then Ctrl pressed: the repeats belong to
        // the game, which must also get the key-up.
        Check(Decide(Key(kWmKeyDown, false), true, latch) == KeyAction::Pass, "= press passes");
        Check(Decide(Key(kWmKeyDown, true, false, false, true), true, latch) == KeyAction::Pass,
              "repeat with Ctrl now held passes");
        Check(Decide(Key(kWmKeyUp, true), true, latch) == KeyAction::Pass, "its key-up passes");
    }

    void TestLostKeyUpDoesNotStick()
    {
        KeyLatch latch;
        Check(Decide(Key(kWmKeyDown, true), true, latch) == KeyAction::SwallowToggle, "toggle press");
        // Key-up went to another window (Alt+Tab). A fresh plain press must
        // reach the game, and so must its key-up.
        Check(Decide(Key(kWmKeyDown, false), true, latch) == KeyAction::Pass, "fresh plain press passes");
        Check(Decide(Key(kWmKeyUp, false), true, latch) == KeyAction::Pass, "and its key-up passes");
    }

    void TestStockSwitchHideShow()
    {
        StockSwitch s;
        int write = -7;
        Check(!Enforce(s, 1, write), "visible: nothing enforced");
        Check(!Show(s, 1, write), "show while visible: no write");

        Hide(s, true, 1);
        Check(s.hidden && s.saved && s.savedValue == 1, "hide captures the stock value");
        Check(Enforce(s, 1, write) && write == 0, "hidden: stock 1 is forced to 0");
        Check(!Enforce(s, 0, write), "hidden: stock 0 is left alone");
        Hide(s, true, 0);
        Check(s.savedValue == 1, "a second hide does not overwrite the saved value");

        write = -7;
        Check(Show(s, 0, write) && write == 1, "show restores 1");
        Check(!s.hidden && !s.saved, "show clears the state");
        Check(!Enforce(s, 1, write), "visible again: nothing enforced");
    }

    void TestStockSwitchAlreadyOff()
    {
        StockSwitch s;
        int write = -7;
        Hide(s, true, 0);
        Check(!Enforce(s, 0, write), "player had stock HUD off: nothing to force");
        Check(!Show(s, 0, write), "player had stock HUD off: show writes nothing, stays off");
    }

    void TestStockSwitchViewKeyWhileHidden()
    {
        StockSwitch s;
        int write = -7;
        Hide(s, true, 1);
        // Shift+F1 cockpit view sets the switch back to 1.
        Check(Enforce(s, 1, write) && write == 0, "view key while hidden is undone");
        write = -7;
        Check(!Show(s, 1, write), "show when the switch already holds the saved value writes nothing");
    }

    void TestStockSwitchUnreadable()
    {
        StockSwitch s;
        int write = -7;
        Hide(s, false, 0);
        Check(s.hidden && !s.saved, "unreadable: hidden but nothing captured");
        Check(!Enforce(s, 1, write), "unreadable: the stock switch is never forced");
        Check(!Show(s, 1, write), "unreadable: show writes nothing");
        Check(!s.hidden, "unreadable: show clears hidden");
    }
}

int main()
{
    TestGate();
    TestPlainEqualPasses();
    TestOtherKeysPass();
    TestChordTogglesAndSwallowsWholePress();
    TestClosedGatePasses();
    TestRepeatOfUnswallowedPressPasses();
    TestLostKeyUpDoesNotStick();
    TestStockSwitchHideShow();
    TestStockSwitchAlreadyOff();
    TestStockSwitchViewKeyWhileHidden();
    TestStockSwitchUnreadable();
    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "hud_visibility_policy_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("hud_visibility_policy_tests: all checks passed\n");
    return 0;
}
