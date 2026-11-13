#pragma once
// quicksave_key_policy.h
// Pure key-message rules for QuickSave and QuickLoad (default Ctrl+Home and
// Ctrl+End, rebindable through [QuickSave] SaveKey / LoadKey).
// No Windows calls, so tests/quicksave_key_policy_tests.cpp can exercise them
// directly; quicksave.cpp feeds in the message and GetKeyState() results.
//
// The game reads its keyboard from WM_KEYDOWN/WM_KEYUP (decompile FUN_00619340
// -> FUN_00619be0 -> FUN_00434bf0(scancode, down)), so a press this policy
// swallows never reaches the stock bindings. Only the exact chord (the
// configured modifiers and no others) is taken; plain and other-modifier
// presses pass. A chord also names whether its key is an extended
// (grey-cluster) key: numpad 7/1 with NumLock off send VK_HOME/VK_END without
// the extended flag, so they never match a grey Home/End chord.

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
        constexpr unsigned kVkF4 = 0x73;

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

        struct Chord
        {
            bool ctrl = false;
            bool shift = false;
            bool alt = false;
            unsigned vk = 0;
            bool extended = false; // the key lives in the grey (extended) cluster

            bool operator==(const Chord& other) const
            {
                return ctrl == other.ctrl && shift == other.shift && alt == other.alt &&
                       vk == other.vk && extended == other.extended;
            }
        };

        struct Chords
        {
            Chord save{true, false, false, kVkHome, true};
            Chord load{true, false, false, kVkEnd, true};
        };

        constexpr const char* kDefaultSaveText = "Ctrl+Home";
        constexpr const char* kDefaultLoadText = "Ctrl+End";

        // Which of the two actions had its press swallowed. Every message for a
        // swallowed key is swallowed until its key-up, whatever the modifiers
        // do meanwhile, so the game never sees half of a press.
        struct SwallowState
        {
            bool save = false;
            bool load = false;
        };

        // ---- Parsing ---------------------------------------------------------

        namespace detail
        {
            inline char Lower(char c)
            {
                return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
            }

            inline bool EqualsNoCase(const char* a, unsigned aLen, const char* b)
            {
                unsigned i = 0;
                for (; i < aLen; ++i)
                {
                    if (b[i] == '\0' || Lower(a[i]) != Lower(b[i]))
                        return false;
                }
                return b[i] == '\0';
            }

            struct NamedKey
            {
                const char* name;
                unsigned vk;
                bool extended;
            };

            constexpr NamedKey kNamedKeys[] = {
                {"home", 0x24, true},     {"end", 0x23, true},      {"insert", 0x2D, true},
                {"ins", 0x2D, true},      {"delete", 0x2E, true},   {"del", 0x2E, true},
                {"pageup", 0x21, true},   {"pgup", 0x21, true},     {"pagedown", 0x22, true},
                {"pgdn", 0x22, true},     {"left", 0x25, true},     {"up", 0x26, true},
                {"right", 0x27, true},    {"down", 0x28, true},     {"leftarrow", 0x25, true},
                {"uparrow", 0x26, true},  {"rightarrow", 0x27, true}, {"downarrow", 0x28, true},
            };

            // Key token -> VK + extended flag. Accepts the editor's gamekey.map
            // spellings too (GreyDelete, GreyUpArrow, ...).
            inline bool ParseKeyToken(const char* t, unsigned len, unsigned& vk, bool& extended)
            {
                if (len > 4 && EqualsNoCase(t, 4, "grey"))
                {
                    t += 4;
                    len -= 4;
                }
                if (len == 1)
                {
                    const char c = Lower(t[0]);
                    if (c >= 'a' && c <= 'z')
                    {
                        vk = static_cast<unsigned>(c - 'a') + 0x41;
                        extended = false;
                        return true;
                    }
                    if (c >= '0' && c <= '9')
                    {
                        vk = static_cast<unsigned>(c - '0') + 0x30;
                        extended = false;
                        return true;
                    }
                    return false;
                }
                if ((t[0] == 'f' || t[0] == 'F') && len >= 2 && len <= 3)
                {
                    unsigned n = 0;
                    for (unsigned i = 1; i < len; ++i)
                    {
                        if (t[i] < '0' || t[i] > '9')
                            return false;
                        n = n * 10 + static_cast<unsigned>(t[i] - '0');
                    }
                    if (n < 1 || n > 24)
                        return false;
                    vk = 0x70 + n - 1;
                    extended = false;
                    return true;
                }
                for (const NamedKey& k : kNamedKeys)
                {
                    if (EqualsNoCase(t, len, k.name))
                    {
                        vk = k.vk;
                        extended = k.extended;
                        return true;
                    }
                }
                return false;
            }
        }

        // "Ctrl+Shift+Home": '+'-separated, case-insensitive, spaces around
        // tokens ignored, modifiers in any order. Exactly one non-modifier key.
        inline bool ParseChord(const char* text, Chord& out)
        {
            if (!text)
                return false;
            Chord chord;
            bool haveKey = false;
            const char* p = text;
            for (;;)
            {
                while (*p == ' ' || *p == '\t')
                    ++p;
                const char* start = p;
                while (*p != '\0' && *p != '+')
                    ++p;
                const char* end = p;
                while (end > start && (end[-1] == ' ' || end[-1] == '\t'))
                    --end;
                const unsigned len = static_cast<unsigned>(end - start);
                if (len == 0)
                    return false;

                if (detail::EqualsNoCase(start, len, "ctrl") || detail::EqualsNoCase(start, len, "control"))
                    chord.ctrl = true;
                else if (detail::EqualsNoCase(start, len, "shift"))
                    chord.shift = true;
                else if (detail::EqualsNoCase(start, len, "alt"))
                    chord.alt = true;
                else
                {
                    if (haveKey || !detail::ParseKeyToken(start, len, chord.vk, chord.extended))
                        return false;
                    haveKey = true;
                }

                if (*p == '\0')
                    break;
                ++p; // the '+'
            }
            if (!haveKey)
                return false;
            out = chord;
            return true;
        }

        // nullptr when the chord is safe to take, else the reason it is not.
        inline const char* UnsafeChordReason(const Chord& chord)
        {
            if (!chord.ctrl && !chord.shift && !chord.alt)
                return "needs a modifier (Ctrl, Shift or Alt); a bare key is used by the game";
            const bool letterOrDigit = (chord.vk >= 0x30 && chord.vk <= 0x39) || (chord.vk >= 0x41 && chord.vk <= 0x5A);
            if (!chord.ctrl && !chord.alt && letterOrDigit)
                return "Shift plus a letter or digit is typing, not a chord";
            if (chord.alt && !chord.ctrl && !chord.shift && chord.vk == kVkF4)
                return "Alt+F4 closes the window";
            return nullptr;
        }

        // Parses and checks one chord against the other action's. nullptr and
        // `out` filled on success, else the reason.
        inline const char* CheckChordText(const char* text, const Chord& other, Chord& out)
        {
            Chord chord;
            if (!ParseChord(text, chord))
                return "not a recognised chord (use e.g. Ctrl+Home, Alt+F5)";
            if (const char* reason = UnsafeChordReason(chord))
                return reason;
            if (chord == other)
                return "same chord as the other QuickSave action";
            out = chord;
            return nullptr;
        }

        struct ResolvedChords
        {
            Chords chords;
            const char* saveProblem = nullptr; // set when the default replaced a bad SaveKey
            const char* loadProblem = nullptr;
        };

        // Turns the two ini strings into chords, replacing an invalid one with
        // its default (and reporting why). If the pair collides, both revert.
        inline ResolvedChords ResolveChords(const char* saveText, const char* loadText)
        {
            ResolvedChords result;
            const Chords defaults;
            Chord save = defaults.save;
            Chord load = defaults.load;

            // The empty Chord{} (vk 0) never collides; the pair test follows.
            Chord parsed;
            if (const char* reason = CheckChordText(saveText, Chord{}, parsed))
                result.saveProblem = reason;
            else
                save = parsed;
            if (const char* reason = CheckChordText(loadText, Chord{}, parsed))
                result.loadProblem = reason;
            else
                load = parsed;

            if (save == load)
            {
                const char* collision = "same chord as the other QuickSave action";
                result.saveProblem = result.saveProblem ? result.saveProblem : collision;
                result.loadProblem = result.loadProblem ? result.loadProblem : collision;
                save = defaults.save;
                load = defaults.load;
            }
            result.chords.save = save;
            result.chords.load = load;
            return result;
        }

        // ---- Message decision --------------------------------------------------

        inline bool KeyMatchesChord(const KeyMessage& key, const Chord& chord)
        {
            return key.vk == chord.vk && key.extended == chord.extended;
        }

        inline bool ModifiersMatch(const KeyMessage& key, const Chord& chord)
        {
            return key.ctrl == chord.ctrl && key.shift == chord.shift && key.alt == chord.alt;
        }

        // Cheap pre-filter so callers only read modifier state for chord keys.
        inline bool IsChordKey(const Chords& chords, unsigned vk)
        {
            return vk == chords.save.vk || vk == chords.load.vk;
        }

        // `enabled` only gates new presses; a press already swallowed is
        // finished (its repeats and key-up swallowed) even if the feature is
        // switched off in between.
        inline Action Decide(const KeyMessage& key, const Chords& chords, bool enabled, SwallowState& state)
        {
            // A key that is not one of the chord keys (including numpad 7/1,
            // which lack the extended flag a grey Home/End chord needs) never
            // touches the swallow state: pass it before reading it.
            const bool matchSave = KeyMatchesChord(key, chords.save);
            const bool matchLoad = KeyMatchesChord(key, chords.load);
            if (!matchSave && !matchLoad)
                return Action::Pass;

            const bool down = key.msg == kWmKeyDown || key.msg == kWmSysKeyDown;
            const bool up = key.msg == kWmKeyUp || key.msg == kWmSysKeyUp;
            if (up)
            {
                if (matchSave && state.save)
                {
                    state.save = false;
                    return Action::Swallow;
                }
                if (matchLoad && state.load)
                {
                    state.load = false;
                    return Action::Swallow;
                }
                return Action::Pass;
            }
            if (!down)
                return Action::Pass;

            // A repeat belongs to whoever got the first press: if the game saw
            // it (Ctrl pressed while Home was already held), the game must also
            // get the repeats and the key-up, or it keeps the key held down.
            if (key.autorepeat)
            {
                const bool swallowed = (matchSave && state.save) || (matchLoad && state.load);
                return swallowed ? Action::Swallow : Action::Pass;
            }

            // A fresh press means any earlier one is over, even if its key-up
            // went to another window (Alt+Tab while held): forget it, or this
            // press's key-up is swallowed and the game keeps the key held.
            if (matchSave)
                state.save = false;
            if (matchLoad)
                state.load = false;

            if (!enabled)
                return Action::Pass;

            if (matchSave && ModifiersMatch(key, chords.save))
            {
                state.save = true;
                return Action::SwallowRequestSave;
            }
            if (matchLoad && ModifiersMatch(key, chords.load))
            {
                state.load = true;
                return Action::SwallowRequestLoad;
            }
            return Action::Pass;
        }
    }
}
