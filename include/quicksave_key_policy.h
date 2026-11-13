#pragma once
// quicksave_key_policy.h
// Pure key-message rules for QuickSave (Ctrl+Home) and QuickLoad (Ctrl+End).
// No Windows calls, so tests/quicksave_key_policy_tests.cpp can exercise them
// directly; quicksave.cpp feeds in the message and GetKeyState() results.
//
// The game reads its keyboard from WM_KEYDOWN/WM_KEYUP (decompile FUN_00619340
// -> FUN_00619be0 -> FUN_00434bf0(scancode, down)), so a press this policy
// swallows never reaches the stock bindings. Only the exact chord Ctrl
// (no Shift, no Alt) + Home/End is taken; plain and Shift chords pass. Only the
// extended (grey-cluster) keys count: numpad 7/1 with NumLock off also send
// VK_HOME/VK_END but without the extended flag, so they pass.

namespace BZROpenShim
{
    namespace QuickSaveKeyPolicy
    {
        constexpr unsigned kWmKeyDown = 0x0100;
        constexpr unsigned kWmKeyUp = 0x0101;
        constexpr unsigned kWmSysKeyDown = 0x0104;
        constexpr unsigned kWmSysKeyUp = 0x0105;
        constexpr unsigned kVkHome = 0x24;
        constexpr unsigned kVkEnd = 0x23;

        enum class Action
        {
            Pass,
            Swallow,
            SwallowRequestSave,
            SwallowRequestLoad,
        };

        struct KeyMessage
        {
            unsigned msg = 0;
            unsigned vk = 0;
            bool autorepeat = false; // lParam bit 30: the key was already down
            bool extended = false;   // lParam bit 24: grey-cluster key, not the numpad
            bool ctrl = false;
            bool shift = false;
            bool alt = false;
        };

        // Which of the two keys had its press swallowed. Every message for a
        // swallowed key is swallowed until its key-up, whatever the modifiers
        // do meanwhile, so the game never sees half of a press.
        struct SwallowState
        {
            bool home = false;
            bool end = false;
        };

        inline bool* SwallowFlagFor(SwallowState& state, unsigned vk)
        {
            if (vk == kVkHome)
                return &state.home;
            if (vk == kVkEnd)
                return &state.end;
            return nullptr;
        }

        // `enabled` only gates new presses; a press already swallowed is
        // finished (its repeats and key-up swallowed) even if the feature is
        // switched off in between.
        inline Action Decide(const KeyMessage& key, bool enabled, SwallowState& state)
        {
            // Numpad 7/1 with NumLock off also send VK_HOME/VK_END, without the
            // extended flag. They are separate physical keys, so they never touch
            // the grey keys' swallow state: pass them before reading it.
            if (!key.extended)
                return Action::Pass;

            bool* const swallowed = SwallowFlagFor(state, key.vk);
            if (!swallowed)
                return Action::Pass;

            const bool down = key.msg == kWmKeyDown || key.msg == kWmSysKeyDown;
            const bool up = key.msg == kWmKeyUp || key.msg == kWmSysKeyUp;
            if (up)
            {
                if (!*swallowed)
                    return Action::Pass;
                *swallowed = false;
                return Action::Swallow;
            }
            if (!down)
                return Action::Pass;

            // A repeat belongs to whoever got the first press: if the game saw
            // it (Ctrl pressed while Home was already held), the game must also
            // get the repeats and the key-up, or it keeps the key held down.
            if (key.autorepeat)
                return *swallowed ? Action::Swallow : Action::Pass;

            // A fresh press means any earlier one is over, even if its key-up
            // went to another window (Alt+Tab while held): forget it, or this
            // press's key-up is swallowed and the game keeps the key held.
            *swallowed = false;

            if (!enabled || !key.ctrl || key.shift || key.alt)
                return Action::Pass;

            *swallowed = true;
            return key.vk == kVkHome ? Action::SwallowRequestSave : Action::SwallowRequestLoad;
        }
    }
}
