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
        return key;
    }

    void TestStockChordsPass()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkF5, false), true, state) == Action::Pass, "plain F5 passes");
        Check(Decide(Key(kWmKeyUp, kVkF5, false), true, state) == Action::Pass, "plain F5 key-up passes");
        Check(Decide(Key(kWmKeyDown, kVkF9, false), true, state) == Action::Pass, "plain F9 passes");
        Check(Decide(Key(kWmKeyDown, kVkF5, false, true), true, state) == Action::Pass, "Shift+F5 passes");
        Check(Decide(Key(kWmKeyDown, kVkF9, false, true), true, state) == Action::Pass, "Shift+F9 passes");
        Check(Decide(Key(kWmKeyDown, kVkF5, true, true), true, state) == Action::Pass, "Ctrl+Shift+F5 passes");
        Check(Decide(Key(kWmKeyDown, kVkF5, true, false, true), true, state) == Action::Pass, "Ctrl+Alt+F5 passes");
        Check(Decide(Key(kWmSysKeyDown, kVkF5, true, false, true), true, state) == Action::Pass,
              "Ctrl+Alt+F5 as WM_SYSKEYDOWN passes");
        Check(Decide(Key(kWmKeyDown, 0x75 /* F6 */, true), true, state) == Action::Pass, "Ctrl+F6 passes");
        Check(!state.f5 && !state.f9, "nothing was marked swallowed");
    }

    void TestSaveAndLoadChords()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkF5, true), true, state) == Action::SwallowRequestSave, "Ctrl+F5 saves");
        Check(state.f5, "Ctrl+F5 press is remembered");
        Check(Decide(Key(kWmKeyUp, kVkF5, true), true, state) == Action::Swallow, "Ctrl+F5 key-up swallowed");
        Check(!state.f5, "key-up clears the F5 mark");

        Check(Decide(Key(kWmKeyDown, kVkF9, true), true, state) == Action::SwallowRequestLoad, "Ctrl+F9 loads");
        Check(Decide(Key(kWmKeyUp, kVkF9, true), true, state) == Action::Swallow, "Ctrl+F9 key-up swallowed");
        Check(!state.f9, "key-up clears the F9 mark");
    }

    void TestAutorepeat()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkF5, true), true, state) == Action::SwallowRequestSave, "first press saves");
        Check(Decide(Key(kWmKeyDown, kVkF5, true, false, false, true), true, state) == Action::Swallow,
              "autorepeat swallowed without a new request");
        Check(Decide(Key(kWmKeyDown, kVkF5, false, false, false, true), true, state) == Action::Swallow,
              "autorepeat after Ctrl release still swallowed");
        Check(Decide(Key(kWmKeyUp, kVkF5, false), true, state) == Action::Swallow, "key-up still swallowed");

        // Ctrl pressed while F5 was already held by the game: the game owns
        // the whole press, repeats and key-up included.
        SwallowState held;
        Check(Decide(Key(kWmKeyDown, kVkF5, false), true, held) == Action::Pass, "plain F5 press reaches the game");
        Check(Decide(Key(kWmKeyDown, kVkF5, true, false, false, true), true, held) == Action::Pass,
              "repeat of a game-owned press passes even with Ctrl down");
        Check(Decide(Key(kWmKeyUp, kVkF5, true), true, held) == Action::Pass, "its key-up passes too");
    }

    void TestKeyUpAfterCtrlReleased()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkF9, true), true, state) == Action::SwallowRequestLoad, "Ctrl+F9 loads");
        Check(Decide(Key(kWmKeyUp, kVkF9, false), true, state) == Action::Swallow,
              "key-up swallowed after Ctrl was released first");
        Check(Decide(Key(kWmSysKeyDown, kVkF9, true), true, state) == Action::SwallowRequestLoad,
              "Alt-free WM_SYSKEYDOWN is treated like WM_KEYDOWN");
        Check(Decide(Key(kWmSysKeyUp, kVkF9, false, false, true), true, state) == Action::Swallow,
              "key-up arriving as WM_SYSKEYUP (Alt pressed mid-hold) swallowed");
    }

    void TestDisabled()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkF5, true), false, state) == Action::Pass, "disabled: Ctrl+F5 passes");
        Check(!state.f5, "disabled press is not marked");

        Check(Decide(Key(kWmKeyDown, kVkF5, true), true, state) == Action::SwallowRequestSave, "enabled press");
        Check(Decide(Key(kWmKeyUp, kVkF5, true), false, state) == Action::Swallow,
              "key-up of a swallowed press is swallowed even after disabling");
    }

    // Ctrl+F5 held, then Alt+Tab: the key-up goes to another window. The next
    // plain F5 press must own its own key-up, not inherit the stale flag.
    void TestLostKeyUpDoesNotStickNextPress()
    {
        SwallowState state;
        Check(Decide(Key(kWmKeyDown, kVkF5, true), true, state) == Action::SwallowRequestSave, "chord taken");
        Check(Decide(Key(kWmKeyDown, kVkF5, false), true, state) == Action::Pass, "later plain F5 passes");
        Check(Decide(Key(kWmKeyUp, kVkF5, false), true, state) == Action::Pass,
              "its key-up passes too, so the game does not keep F5 held");
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
