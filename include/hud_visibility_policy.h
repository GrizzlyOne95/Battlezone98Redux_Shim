#pragma once
// hud_visibility_policy.h
// Pure rules for the Ctrl+= "hide all HUD" screenshot toggle
// (hud_visibility.cpp). No Windows calls, so
// tests/hud_visibility_policy_tests.cpp can exercise them directly.
//
// The key is matched by scan code 0x0D, the key input.map calls "Equal"
// (stock zoom_factor_plus). The game reads its keyboard from WM_KEYDOWN/
// WM_KEYUP scan codes (FUN_00619be0 -> FUN_00434bf0(scancode, down), whose
// key-state bits are only set from those messages), so a swallowed press
// never reaches the zoom binding. Matching the scan code rather than
// VK_OEM_PLUS keeps the chord on the same physical key as stock zoom on any
// keyboard layout. Only the exact chord Ctrl+= (no Shift, no Alt) is taken;
// plain "=" and every other combination pass to the game.

namespace BZROpenShim
{
    namespace HudVisibilityPolicy
    {
        constexpr unsigned kWmKeyDown = 0x0100;
        constexpr unsigned kWmKeyUp = 0x0101;
        constexpr unsigned kWmSysKeyDown = 0x0104;
        constexpr unsigned kWmSysKeyUp = 0x0105;
        constexpr unsigned kScanEqual = 0x0D;

        constexpr const char* kChordText = "Ctrl+=";

        struct KeyMessage
        {
            unsigned msg = 0;
            unsigned scanCode = 0;   // lParam bits 16-23
            bool extended = false;   // lParam bit 24
            bool autorepeat = false; // lParam bit 30: the key was already down
            bool ctrl = false;
            bool shift = false;
            bool alt = false;
        };

        enum class KeyAction
        {
            Pass,
            Swallow,
            SwallowToggle,
        };

        // Whether the press now being handled was swallowed. Every message for
        // a swallowed press is swallowed until its key-up, so the game never
        // sees half of it (and so never zooms or keeps "=" held).
        struct KeyLatch
        {
            bool swallowed = false;
        };

        // When a press may toggle. Anything that is not live gameplay leaves
        // Ctrl+= to the game: the shell and pause/options screens, a focused
        // in-mission text editor (chat, ally prompt), and a world that has not
        // ticked recently (loading, main menu).
        struct Gate
        {
            bool worldTicking = false;
            bool shellReadable = false;
            bool shellScreenUp = false;  // UI wrapper active or a screen present
            bool textEditorFocused = true;
        };

        inline bool GateOpen(const Gate& gate)
        {
            return gate.worldTicking && gate.shellReadable && !gate.shellScreenUp && !gate.textEditorFocused;
        }

        inline bool IsChordKey(const KeyMessage& key)
        {
            return key.scanCode == kScanEqual && !key.extended;
        }

        // Same latch rules as QuickSaveKeyPolicy::Decide. `gateOpen` only
        // gates new presses; a press already swallowed is finished.
        inline KeyAction Decide(const KeyMessage& key, bool gateOpen, KeyLatch& latch)
        {
            if (!IsChordKey(key))
                return KeyAction::Pass;

            const bool down = key.msg == kWmKeyDown || key.msg == kWmSysKeyDown;
            const bool up = key.msg == kWmKeyUp || key.msg == kWmSysKeyUp;
            if (up)
            {
                if (latch.swallowed)
                {
                    latch.swallowed = false;
                    return KeyAction::Swallow;
                }
                return KeyAction::Pass;
            }
            if (!down)
                return KeyAction::Pass;

            // A repeat belongs to whoever got the first press.
            if (key.autorepeat)
                return latch.swallowed ? KeyAction::Swallow : KeyAction::Pass;

            // A fresh press: any earlier one is over, even if its key-up went
            // to another window.
            latch.swallowed = false;
            if (!gateOpen)
                return KeyAction::Pass;
            if (key.ctrl && !key.shift && !key.alt)
            {
                latch.swallowed = true;
                return KeyAction::SwallowToggle;
            }
            return KeyAction::Pass;
        }

        // ---- The stock HUD switch ---------------------------------------------
        // DAT_008EAAB0 ("useDisplayInterface", the Options HUD on/off box) is
        // the stock show-HUD switch. While hidden it is held at 0; showing
        // puts back whatever it held when the HUD was hidden, so a player who
        // had the stock HUD off keeps it off.

        struct StockSwitch
        {
            bool hidden = false;
            bool saved = false;
            int savedValue = 1;
        };

        // `currentReadable` false: the switch could not be read; the OpenShim
        // overlays still hide, the stock switch is left alone.
        inline void Hide(StockSwitch& s, bool currentReadable, int current)
        {
            if (s.hidden)
                return;
            s.hidden = true;
            s.saved = currentReadable;
            s.savedValue = currentReadable ? current : 1;
        }

        // Per frame while hidden: true (and `write`) when the switch must be
        // forced back to 0, e.g. after a stock view key (Shift+F1/F2) set it.
        // Only a switch whose value was captured is forced.
        inline bool Enforce(const StockSwitch& s, int current, int& write)
        {
            if (!s.hidden || !s.saved || current == 0)
                return false;
            write = 0;
            return true;
        }

        // Shows again. True (and `write`) when the switch must be restored.
        inline bool Show(StockSwitch& s, int current, int& write)
        {
            if (!s.hidden)
                return false;
            const bool restore = s.saved && current != s.savedValue;
            if (restore)
                write = s.savedValue;
            s = StockSwitch{};
            return restore;
        }
    }
}
