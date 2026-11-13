#include "quicksave_key_policy.h"

#include <cstdio>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::QuickSaveKeyPolicy;

namespace
{
    const Chords kDefaults;

    KeyMessage Key(unsigned msg, unsigned vk, bool ctrl, bool shift = false, bool alt = false,
                   bool autorepeat = false)
    {
        KeyMessage key;
        key.msg = msg;
        key.vk = vk;
        key.ctrl = ctrl;
        key.shift = shift;
        key.alt = alt;
        key.autorepeat = autorepeat;
        key.extended = true;
        return key;
    }

    void TestStockChordsPass()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkHome, false), kDefaults, true, state) == Action::Pass, "plain Home passes");
        Check(Decide(Key(kWmKeyUp, kVkHome, false), kDefaults, true, state) == Action::Pass, "plain Home key-up passes");
        Check(Decide(Key(kWmKeyDown, kVkEnd, false), kDefaults, true, state) == Action::Pass, "plain End passes");
        Check(Decide(Key(kWmKeyDown, kVkHome, false, true), kDefaults, true, state) == Action::Pass, "Shift+Home passes");
        Check(Decide(Key(kWmKeyDown, kVkEnd, false, true), kDefaults, true, state) == Action::Pass, "Shift+End passes");
        Check(Decide(Key(kWmKeyDown, kVkHome, true, true), kDefaults, true, state) == Action::Pass, "Ctrl+Shift+Home passes");
        Check(Decide(Key(kWmKeyDown, kVkHome, true, false, true), kDefaults, true, state) == Action::Pass, "Ctrl+Alt+Home passes");
        Check(Decide(Key(kWmSysKeyDown, kVkHome, true, false, true), kDefaults, true, state) == Action::Pass,
              "Ctrl+Alt+Home as WM_SYSKEYDOWN passes");
        Check(Decide(Key(kWmKeyDown, 0x75 /* F6 */, true), kDefaults, true, state) == Action::Pass, "Ctrl+F6 passes");
        Check(!state.save && !state.load, "nothing was marked swallowed");
    }

    void TestNumpadKeysPass()
    {
        SwallowState state;
        KeyMessage key = Key(kWmKeyDown, kVkHome, true);
        key.extended = false; // numpad 7 with NumLock off
        Check(Decide(key, kDefaults, true, state) == Action::Pass, "Ctrl+numpad7 (non-extended Home) passes");
        key.vk = kVkEnd;
        Check(Decide(key, kDefaults, true, state) == Action::Pass, "Ctrl+numpad1 (non-extended End) passes");
        Check(!state.save && !state.load, "numpad keys are not marked swallowed");

        // Grey Home held (swallowed) while numpad 7 is pressed and released:
        // the numpad key must neither clear nor consume the grey key's mark.
        Check(Decide(Key(kWmKeyDown, kVkHome, true), kDefaults, true, state) == Action::SwallowRequestSave, "grey Ctrl+Home saves");
        KeyMessage pad = Key(kWmKeyDown, kVkHome, true);
        pad.extended = false;
        Check(Decide(pad, kDefaults, true, state) == Action::Pass, "numpad7 down passes while grey Home is held");
        pad.autorepeat = true;
        Check(Decide(pad, kDefaults, true, state) == Action::Pass, "numpad7 repeat passes while grey Home is held");
        pad.autorepeat = false;
        pad.msg = kWmKeyUp;
        Check(Decide(pad, kDefaults, true, state) == Action::Pass, "numpad7 key-up passes while grey Home is held");
        Check(state.save, "grey Home mark survives the numpad key");
        Check(Decide(Key(kWmKeyUp, kVkHome, true), kDefaults, true, state) == Action::Swallow, "grey Home key-up still swallowed");
    }

    void TestSaveAndLoadChords()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkHome, true), kDefaults, true, state) == Action::SwallowRequestSave, "Ctrl+Home saves");
        Check(state.save, "Ctrl+Home press is remembered");
        Check(Decide(Key(kWmKeyUp, kVkHome, true), kDefaults, true, state) == Action::Swallow, "Ctrl+Home key-up swallowed");
        Check(!state.save, "key-up clears the Home mark");

        Check(Decide(Key(kWmKeyDown, kVkEnd, true), kDefaults, true, state) == Action::SwallowRequestLoad, "Ctrl+End loads");
        Check(Decide(Key(kWmKeyUp, kVkEnd, true), kDefaults, true, state) == Action::Swallow, "Ctrl+End key-up swallowed");
        Check(!state.load, "key-up clears the End mark");
    }

    void TestAutorepeat()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkHome, true), kDefaults, true, state) == Action::SwallowRequestSave, "first press saves");
        Check(Decide(Key(kWmKeyDown, kVkHome, true, false, false, true), kDefaults, true, state) == Action::Swallow,
              "autorepeat swallowed without a new request");
        Check(Decide(Key(kWmKeyDown, kVkHome, false, false, false, true), kDefaults, true, state) == Action::Swallow,
              "autorepeat after Ctrl release still swallowed");
        Check(Decide(Key(kWmKeyUp, kVkHome, false), kDefaults, true, state) == Action::Swallow, "key-up still swallowed");

        // Ctrl pressed while Home was already held by the game: the game owns
        // the whole press, repeats and key-up included.
        SwallowState held;
        Check(Decide(Key(kWmKeyDown, kVkHome, false), kDefaults, true, held) == Action::Pass, "plain Home press reaches the game");
        Check(Decide(Key(kWmKeyDown, kVkHome, true, false, false, true), kDefaults, true, held) == Action::Pass,
              "repeat of a game-owned press passes even with Ctrl down");
        Check(Decide(Key(kWmKeyUp, kVkHome, true), kDefaults, true, held) == Action::Pass, "its key-up passes too");
    }

    void TestKeyUpAfterCtrlReleased()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkEnd, true), kDefaults, true, state) == Action::SwallowRequestLoad, "Ctrl+End loads");
        Check(Decide(Key(kWmKeyUp, kVkEnd, false), kDefaults, true, state) == Action::Swallow,
              "key-up swallowed after Ctrl was released first");
        Check(Decide(Key(kWmSysKeyDown, kVkEnd, true), kDefaults, true, state) == Action::SwallowRequestLoad,
              "Alt-free WM_SYSKEYDOWN is treated like WM_KEYDOWN");
        Check(Decide(Key(kWmSysKeyUp, kVkEnd, false, false, true), kDefaults, true, state) == Action::Swallow,
              "key-up arriving as WM_SYSKEYUP (Alt pressed mid-hold) swallowed");
    }

    void TestDisabled()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkHome, true), kDefaults, false, state) == Action::Pass, "disabled: Ctrl+Home passes");
        Check(!state.save, "disabled press is not marked");

        Check(Decide(Key(kWmKeyDown, kVkHome, true), kDefaults, true, state) == Action::SwallowRequestSave, "enabled press");
        Check(Decide(Key(kWmKeyUp, kVkHome, true), kDefaults, false, state) == Action::Swallow,
              "key-up of a swallowed press is swallowed even after disabling");
    }

    // Ctrl+Home held, then Alt+Tab: the key-up goes to another window. The next
    // plain Home press must own its own key-up, not inherit the stale flag.
    void TestLostKeyUpDoesNotStickNextPress()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkHome, true), kDefaults, true, state) == Action::SwallowRequestSave, "chord taken");
        Check(Decide(Key(kWmKeyDown, kVkHome, false), kDefaults, true, state) == Action::Pass, "later plain Home passes");
        Check(Decide(Key(kWmKeyUp, kVkHome, false), kDefaults, true, state) == Action::Pass,
              "its key-up passes too, so the game does not keep Home held");
    }

    void TestParseChord()
    {
        Chord c;
        Check(ParseChord("Ctrl+Home", c) && c == kDefaults.save, "Ctrl+Home parses to the default save chord");
        Check(ParseChord("  ctrl + END ", c) && c == kDefaults.load, "case and spaces are ignored");
        Check(ParseChord("Home+Control", c) && c.ctrl && c.vk == kVkHome && c.extended, "modifier order is free");
        Check(ParseChord("Alt+F5", c) && c.alt && !c.ctrl && c.vk == 0x74 && !c.extended, "F-keys are not extended");
        Check(ParseChord("Ctrl+Shift+q", c) && c.ctrl && c.shift && c.vk == 'Q' && !c.extended, "letters are not extended");
        Check(ParseChord("Ctrl+7", c) && c.vk == '7' && !c.extended, "digits are not extended");
        Check(ParseChord("Ctrl+Delete", c) && c.vk == 0x2E && c.extended, "Delete is extended");
        Check(ParseChord("CTRL+GreyDelete", c) && c.vk == 0x2E && c.extended, "editor spelling GreyDelete parses");
        Check(ParseChord("Ctrl+GreyUpArrow", c) && c.vk == 0x26 && c.extended, "editor spelling GreyUpArrow parses");
        Check(ParseChord("Ctrl+PageDown", c) && c.vk == 0x22 && c.extended, "PageDown is extended");
        Check(ParseChord("Ctrl+F24", c) && c.vk == 0x87, "F24 parses");

        Check(!ParseChord("", c), "empty is rejected");
        Check(!ParseChord(nullptr, c), "null is rejected");
        Check(!ParseChord("Ctrl", c), "modifier only is rejected");
        Check(!ParseChord("Ctrl+", c), "trailing plus is rejected");
        Check(!ParseChord("Ctrl+Home+End", c), "two keys are rejected");
        Check(!ParseChord("Ctrl+F25", c), "F25 is rejected");
        Check(!ParseChord("Ctrl+Banana", c), "unknown key is rejected");
    }

    void TestUnsafeChords()
    {
        Chord c;
        const Chord other{};
        Check(CheckChordText("Home", other, c) != nullptr, "bare Home is unsafe");
        Check(CheckChordText("F5", other, c) != nullptr, "bare F5 is unsafe");
        Check(CheckChordText("Alt+F4", other, c) != nullptr, "Alt+F4 is unsafe");
        Check(CheckChordText("Shift+Q", other, c) != nullptr, "Shift+letter is unsafe");
        Check(CheckChordText("Ctrl+Alt+F4", other, c) == nullptr, "Ctrl+Alt+F4 is allowed");
        Check(CheckChordText("Ctrl+F5", other, c) == nullptr && c.vk == 0x74, "Ctrl+F5 is allowed");
        Check(CheckChordText("Ctrl+Home", kDefaults.save, c) != nullptr, "a chord equal to the other action is rejected");
    }

    void TestResolveChords()
    {
        ResolvedChords r = ResolveChords("Ctrl+F5", "Ctrl+F9");
        Check(!r.saveProblem && !r.loadProblem, "valid pair has no problem");
        Check(r.chords.save.vk == 0x74 && r.chords.load.vk == 0x78, "valid pair is taken");

        r = ResolveChords("Banana", "Ctrl+F9");
        Check(r.saveProblem && !r.loadProblem, "bad SaveKey is reported only for save");
        Check(r.chords.save == kDefaults.save && r.chords.load.vk == 0x78, "bad SaveKey falls back to the default");

        r = ResolveChords("Alt+F4", "F9");
        Check(r.saveProblem && r.loadProblem, "unsafe chords are reported");
        Check(r.chords.save == kDefaults.save && r.chords.load == kDefaults.load, "unsafe chords fall back");

        r = ResolveChords("Ctrl+F5", "ctrl+f5");
        Check(r.saveProblem && r.loadProblem, "identical chords are reported");
        Check(r.chords.save == kDefaults.save && r.chords.load == kDefaults.load, "identical chords revert both");

        r = ResolveChords(kDefaultSaveText, kDefaultLoadText);
        Check(!r.saveProblem && !r.loadProblem, "the default texts resolve cleanly");
        r = ResolveChords(nullptr, nullptr);
        Check(r.saveProblem && r.loadProblem, "null texts are reported");
    }

    void TestReboundChords()
    {
        Chords chords;
        Check(ParseChord("Ctrl+F5", chords.save) && ParseChord("Alt+F9", chords.load), "rebind parses");
        SwallowState state;
        const auto fkey = [](unsigned msg, unsigned vk, bool ctrl, bool alt, bool repeat = false)
        {
            KeyMessage k;
            k.msg = msg;
            k.vk = vk;
            k.ctrl = ctrl;
            k.alt = alt;
            k.autorepeat = repeat;
            k.extended = false;
            return k;
        };
        Check(Decide(fkey(kWmKeyDown, 0x74, true, false), chords, true, state) == Action::SwallowRequestSave, "Ctrl+F5 saves");
        Check(Decide(fkey(kWmKeyDown, 0x74, true, false, true), chords, true, state) == Action::Swallow, "its repeat is swallowed");
        Check(Decide(fkey(kWmKeyUp, 0x74, false, false), chords, true, state) == Action::Swallow, "its key-up is swallowed");
        Check(Decide(fkey(kWmSysKeyDown, 0x78, false, true), chords, true, state) == Action::SwallowRequestLoad, "Alt+F9 (WM_SYSKEYDOWN) loads");
        Check(Decide(fkey(kWmSysKeyUp, 0x78, false, true), chords, true, state) == Action::Swallow, "Alt+F9 key-up swallowed");
        Check(!state.save && !state.load, "no mark left behind");

        Check(Decide(fkey(kWmKeyDown, 0x74, false, false), chords, true, state) == Action::Pass, "plain F5 passes");
        Check(Decide(fkey(kWmKeyUp, 0x74, false, false), chords, true, state) == Action::Pass, "plain F5 key-up passes");
        Check(Decide(fkey(kWmKeyDown, 0x74, true, false), chords, false, state) == Action::Pass, "disabled: Ctrl+F5 passes");

        // The old defaults no longer belong to the plugin once rebound.
        Check(Decide(Key(kWmKeyDown, kVkHome, true), chords, true, state) == Action::Pass, "Ctrl+Home passes when rebound");
        Check(Decide(Key(kWmKeyDown, kVkEnd, true), chords, true, state) == Action::Pass, "Ctrl+End passes when rebound");
        Check(IsChordKey(chords, 0x74) && !IsChordKey(chords, kVkHome), "IsChordKey follows the rebound keys");

        // An extended chord does not take the matching non-extended key.
        Chords ins;
        Check(ParseChord("Ctrl+Insert", ins.save), "Ctrl+Insert parses");
        KeyMessage pad = Key(kWmKeyDown, 0x2D, true);
        pad.extended = false; // numpad 0 with NumLock off
        Check(Decide(pad, ins, true, state) == Action::Pass, "non-extended Insert passes");
        Check(Decide(Key(kWmKeyDown, 0x2D, true), ins, true, state) == Action::SwallowRequestSave, "extended Insert saves");
    }
}

int main()
{
    TestStockChordsPass();
    TestNumpadKeysPass();
    TestSaveAndLoadChords();
    TestAutorepeat();
    TestKeyUpAfterCtrlReleased();
    TestDisabled();
    TestLostKeyUpDoesNotStickNextPress();
    TestParseChord();
    TestUnsafeChords();
    TestResolveChords();
    TestReboundChords();
    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "quicksave_key_policy_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("quicksave_key_policy_tests: all checks passed\n");
    return 0;
}
