#pragma once
// quicksave_key_policy.h
// Pure key-message rules for QuickSave (Ctrl+F5) and QuickLoad (Ctrl+F9).
// No Windows calls, so tests/quicksave_key_policy_tests.cpp can exercise them
// directly; quicksave.cpp feeds in the message and GetKeyState() results.
//
// The game reads its keyboard from WM_KEYDOWN/WM_KEYUP (decompile FUN_00619340
// -> FUN_00619be0 -> FUN_00434bf0(scancode, down)), so a press this policy
// swallows never reaches the stock F5/F9 bindings. Only the exact chord Ctrl
// (no Shift, no Alt) + F5/F9 is taken; plain F5/F9 and Shift+F5/F9 pass.

namespace BZROpenShim
{
    namespace QuickSaveKeyPolicy
    {
        constexpr unsigned kWmKeyDown = 0x0100;
        constexpr unsigned kWmKeyUp = 0x0101;
        constexpr unsigned kWmSysKeyDown = 0x0104;
        constexpr unsigned kWmSysKeyUp = 0x0105;
        constexpr unsigned kVkF5 = 0x74;
        constexpr unsigned kVkF9 = 0x78;

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
            bool ctrl = false;
            bool shift = false;
            bool alt = false;
        };

        // Which of the two keys had its press swallowed. Every message for a
        // swallowed key is swallowed until its key-up, whatever the modifiers
        // do meanwhile, so the game never sees half of a press.
        struct SwallowState
        {
            bool f5 = false;
            bool f9 = false;
        };

        inline bool* SwallowFlagFor(SwallowState& state, unsigned vk)
        {
            if (vk == kVkF5)
                return &state.f5;
            if (vk == kVkF9)
                return &state.f9;
            return nullptr;
        }

        // `enabled` only gates new presses; a press already swallowed is
        // finished (its repeats and key-up swallowed) even if the feature is
        // switched off in between.
        inline Action Decide(const KeyMessage& key, bool enabled, SwallowState& state)
        {
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
            // it (Ctrl pressed while F5 was already held), the game must also
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
            return key.vk == kVkF5 ? Action::SwallowRequestSave : Action::SwallowRequestLoad;
        }
    }
}
