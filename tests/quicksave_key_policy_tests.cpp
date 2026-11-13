#include "quicksave_key_policy.h"

#include <cstdio>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::QuickSaveKeyPolicy;

namespace
{
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
        Check(Decide(Key(kWmKeyDown, kVkHome, false), true, state) == Action::Pass, "plain Home passes");
        Check(Decide(Key(kWmKeyUp, kVkHome, false), true, state) == Action::Pass, "plain Home key-up passes");
        Check(Decide(Key(kWmKeyDown, kVkEnd, false), true, state) == Action::Pass, "plain End passes");
        Check(Decide(Key(kWmKeyDown, kVkHome, false, true), true, state) == Action::Pass, "Shift+Home passes");
        Check(Decide(Key(kWmKeyDown, kVkEnd, false, true), true, state) == Action::Pass, "Shift+End passes");
        Check(Decide(Key(kWmKeyDown, kVkHome, true, true), true, state) == Action::Pass, "Ctrl+Shift+Home passes");
        Check(Decide(Key(kWmKeyDown, kVkHome, true, false, true), true, state) == Action::Pass, "Ctrl+Alt+Home passes");
        Check(Decide(Key(kWmSysKeyDown, kVkHome, true, false, true), true, state) == Action::Pass,
              "Ctrl+Alt+Home as WM_SYSKEYDOWN passes");
        Check(Decide(Key(kWmKeyDown, 0x75 /* F6 */, true), true, state) == Action::Pass, "Ctrl+F6 passes");
        Check(!state.home && !state.end, "nothing was marked swallowed");
    }

    void TestNumpadKeysPass()
    {
        SwallowState state;
        KeyMessage key = Key(kWmKeyDown, kVkHome, true);
        key.extended = false; // numpad 7 with NumLock off
        Check(Decide(key, true, state) == Action::Pass, "Ctrl+numpad7 (non-extended Home) passes");
        key.vk = kVkEnd;
        Check(Decide(key, true, state) == Action::Pass, "Ctrl+numpad1 (non-extended End) passes");
        Check(!state.home && !state.end, "numpad keys are not marked swallowed");

        // Grey Home held (swallowed) while numpad 7 is pressed and released:
        // the numpad key must neither clear nor consume the grey key's mark.
        Check(Decide(Key(kWmKeyDown, kVkHome, true), true, state) == Action::SwallowRequestSave, "grey Ctrl+Home saves");
        KeyMessage pad = Key(kWmKeyDown, kVkHome, true);
        pad.extended = false;
        Check(Decide(pad, true, state) == Action::Pass, "numpad7 down passes while grey Home is held");
        pad.autorepeat = true;
        Check(Decide(pad, true, state) == Action::Pass, "numpad7 repeat passes while grey Home is held");
        pad.autorepeat = false;
        pad.msg = kWmKeyUp;
        Check(Decide(pad, true, state) == Action::Pass, "numpad7 key-up passes while grey Home is held");
        Check(state.home, "grey Home mark survives the numpad key");
        Check(Decide(Key(kWmKeyUp, kVkHome, true), true, state) == Action::Swallow, "grey Home key-up still swallowed");
    }

    void TestSaveAndLoadChords()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkHome, true), true, state) == Action::SwallowRequestSave, "Ctrl+Home saves");
        Check(state.home, "Ctrl+Home press is remembered");
        Check(Decide(Key(kWmKeyUp, kVkHome, true), true, state) == Action::Swallow, "Ctrl+Home key-up swallowed");
        Check(!state.home, "key-up clears the Home mark");

        Check(Decide(Key(kWmKeyDown, kVkEnd, true), true, state) == Action::SwallowRequestLoad, "Ctrl+End loads");
        Check(Decide(Key(kWmKeyUp, kVkEnd, true), true, state) == Action::Swallow, "Ctrl+End key-up swallowed");
        Check(!state.end, "key-up clears the End mark");
    }

    void TestAutorepeat()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkHome, true), true, state) == Action::SwallowRequestSave, "first press saves");
        Check(Decide(Key(kWmKeyDown, kVkHome, true, false, false, true), true, state) == Action::Swallow,
              "autorepeat swallowed without a new request");
        Check(Decide(Key(kWmKeyDown, kVkHome, false, false, false, true), true, state) == Action::Swallow,
              "autorepeat after Ctrl release still swallowed");
        Check(Decide(Key(kWmKeyUp, kVkHome, false), true, state) == Action::Swallow, "key-up still swallowed");

        // Ctrl pressed while Home was already held by the game: the game owns
        // the whole press, repeats and key-up included.
        SwallowState held;
        Check(Decide(Key(kWmKeyDown, kVkHome, false), true, held) == Action::Pass, "plain Home press reaches the game");
        Check(Decide(Key(kWmKeyDown, kVkHome, true, false, false, true), true, held) == Action::Pass,
              "repeat of a game-owned press passes even with Ctrl down");
        Check(Decide(Key(kWmKeyUp, kVkHome, true), true, held) == Action::Pass, "its key-up passes too");
    }

    void TestKeyUpAfterCtrlReleased()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkEnd, true), true, state) == Action::SwallowRequestLoad, "Ctrl+End loads");
        Check(Decide(Key(kWmKeyUp, kVkEnd, false), true, state) == Action::Swallow,
              "key-up swallowed after Ctrl was released first");
        Check(Decide(Key(kWmSysKeyDown, kVkEnd, true), true, state) == Action::SwallowRequestLoad,
              "Alt-free WM_SYSKEYDOWN is treated like WM_KEYDOWN");
        Check(Decide(Key(kWmSysKeyUp, kVkEnd, false, false, true), true, state) == Action::Swallow,
              "key-up arriving as WM_SYSKEYUP (Alt pressed mid-hold) swallowed");
    }

    void TestDisabled()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkHome, true), false, state) == Action::Pass, "disabled: Ctrl+Home passes");
        Check(!state.home, "disabled press is not marked");

        Check(Decide(Key(kWmKeyDown, kVkHome, true), true, state) == Action::SwallowRequestSave, "enabled press");
        Check(Decide(Key(kWmKeyUp, kVkHome, true), false, state) == Action::Swallow,
              "key-up of a swallowed press is swallowed even after disabling");
    }

    // Ctrl+Home held, then Alt+Tab: the key-up goes to another window. The next
    // plain Home press must own its own key-up, not inherit the stale flag.
    void TestLostKeyUpDoesNotStickNextPress()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkHome, true), true, state) == Action::SwallowRequestSave, "chord taken");
        Check(Decide(Key(kWmKeyDown, kVkHome, false), true, state) == Action::Pass, "later plain Home passes");
        Check(Decide(Key(kWmKeyUp, kVkHome, false), true, state) == Action::Pass,
              "its key-up passes too, so the game does not keep Home held");
    }
}

int main()
{
    TestStockChordsPass();
    TestSaveAndLoadChords();
    TestAutorepeat();
    TestKeyUpAfterCtrlReleased();
    TestDisabled();
    TestLostKeyUpDoesNotStickNextPress();
    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "quicksave_key_policy_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("quicksave_key_policy_tests: all checks passed\n");
    return 0;
}
