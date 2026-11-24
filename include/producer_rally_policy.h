#pragma once
// producer_rally_policy.h
// Pure decision rules for [Gameplay] ProducerRallyPoints. No Windows or
// engine calls, so tests/producer_rally_policy_tests.cpp can exercise them
// directly. The engine side is src/patches/producer_rally_points.cpp; the
// behaviour is documented in Docs/PRODUCER_RALLY_POINTS.md.

#include "quicksave_key_policy.h"

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
    namespace ProducerRallyPolicy
    {
        constexpr unsigned kWmKeyDown = 0x0100;
        constexpr unsigned kWmKeyUp = 0x0101;
        constexpr unsigned kVkV = 0x56;
        // WM_KEYDOWN lParam bit 30: the key was already down (autorepeat).
        constexpr unsigned long long kLParamPreviousStateBit = 1ull << 30;

        enum class KeyAction
        {
            None,
            SetRally,
            ClearRally,
        };

        // The configured rally key ([Gameplay] RallyKey, default V): one key,
        // no modifier. A plain press arms/cancels, Shift+key clears.
        struct RallyKey
        {
            unsigned vk = kVkV;
            bool extended = false; // grey-cluster key (Ins, Home, arrows, ...)

            bool operator==(const RallyKey& other) const
            {
                return vk == other.vk && extended == other.extended;
            }
        };

        constexpr const char* kDefaultRallyKeyText = "V";

        // nullptr when `vk` may be the rally key, else why not. The game
        // hard-wires digits (command menus), Space, Tab, Alt, Enter and Esc,
        // and F1-F10 are the group keys.
        inline const char* ReservedRallyKeyReason(unsigned vk)
        {
            if (vk >= 0x30 && vk <= 0x39)
                return "digits are the game's command-menu keys";
            if (vk >= 0x70 && vk <= 0x79)
                return "F1-F10 are the game's group keys";
            switch (vk)
            {
            case 0x20: return "Space is a game key";
            case 0x09: return "Tab is a game key";
            case 0x12: return "Alt is a modifier";
            case 0x0D: return "Enter is a game key";
            case 0x1B: return "Esc is a game key";
            default: return nullptr;
            }
        }

        // Parses and checks the [Gameplay] RallyKey text against the two
        // QuickSave chords. nullptr and `out` filled on success, else the
        // reason. A Ctrl or Alt chord on the same key never reaches the rally
        // filter (it ignores Ctrl and Alt), so only a Shift-only chord clashes.
        inline const char* CheckRallyKeyText(const char* text, const QuickSaveKeyPolicy::Chord& quickSave,
                                             const QuickSaveKeyPolicy::Chord& quickLoad, RallyKey& out)
        {
            QuickSaveKeyPolicy::Chord chord;
            if (!QuickSaveKeyPolicy::ParseChord(text, chord))
                return "not a recognised key (use e.g. V, Insert, PageUp)";
            if (chord.ctrl || chord.shift || chord.alt)
                return "must be a single key without Ctrl, Shift or Alt";
            if (const char* reason = ReservedRallyKeyReason(chord.vk))
                return reason;
            const QuickSaveKeyPolicy::Chord* const quickChords[2] = { &quickSave, &quickLoad };
            for (const QuickSaveKeyPolicy::Chord* quick : quickChords)
            {
                if (quick->vk == chord.vk && quick->extended == chord.extended && !quick->ctrl && !quick->alt)
                    return "Shift plus this key is a QuickSave chord";
            }
            out.vk = chord.vk;
            out.extended = chord.extended;
            return nullptr;
        }

        // The key's name as printed on the panel key cap: the letter itself,
        // "F11", or a short name ("Ins", "PgUp"). Returns the length written
        // (0 for a key with no name; the buffer then holds "").
        inline size_t RallyKeyCapName(const RallyKey& key, char* out, size_t cap)
        {
            if (!out || cap == 0)
                return 0;
            out[0] = '\0';
            char text[8] = {};
            if ((key.vk >= 0x41 && key.vk <= 0x5A) || (key.vk >= 0x30 && key.vk <= 0x39))
            {
                text[0] = static_cast<char>(key.vk);
            }
            else if (key.vk >= 0x70 && key.vk <= 0x87)
            {
                const unsigned n = key.vk - 0x70 + 1;
                size_t len = 0;
                text[len++] = 'F';
                if (n >= 10)
                    text[len++] = static_cast<char>('0' + n / 10);
                text[len++] = static_cast<char>('0' + n % 10);
            }
            else
            {
                const char* name = nullptr;
                switch (key.vk)
                {
                case 0x2D: name = "Ins"; break;
                case 0x2E: name = "Del"; break;
                case 0x24: name = "Home"; break;
                case 0x23: name = "End"; break;
                case 0x21: name = "PgUp"; break;
                case 0x22: name = "PgDn"; break;
                case 0x25: name = "Left"; break;
                case 0x26: name = "Up"; break;
                case 0x27: name = "Right"; break;
                case 0x28: name = "Down"; break;
                default: break;
                }
                if (!name)
                    return 0;
                for (size_t i = 0; name[i] && i + 1 < sizeof(text); ++i)
                    text[i] = name[i];
            }
            size_t len = 0;
            for (; text[len] && len + 1 < cap; ++len)
                out[len] = text[len];
            out[len] = '\0';
            return len;
        }

        struct KeyEvent
        {
            unsigned msg = 0;
            unsigned vk = 0;
            unsigned long long lParam = 0;
            bool extended = false; // lParam bit 24: grey-cluster key, not the numpad
            bool shift = false;
            bool ctrl = false;
            bool alt = false;
        };

        // Everything outside the key itself that decides whether V is ours.
        struct KeyGate
        {
            // [Gameplay] ProducerRallyPoints on, hooks installed, and single
            // player or a network game whose mission opted in.
            bool featureActive = false;
            // A mission world exists and no shell screen (pause, options,
            // save/load) is up.
            bool worldInteractive = false;
            // The stock EditMode input program is on (map editor): V is
            // edit_vertflip and Ctrl+V edit_paste there.
            bool editorActive = false;
            // The current selection holds at least one Recycler or Factory of
            // the player's team.
            bool eligibleProducerSelected = false;
        };

        struct KeyDecision
        {
            bool swallow = false;
            KeyAction action = KeyAction::None;
        };

        // Per-window latch: was the last fresh V keydown swallowed? Only then is
        // the matching WM_KEYUP (and any autorepeat in between) swallowed too,
        // so the game never sees half of a keypress.
        struct KeyLatch
        {
            bool downSwallowed = false;
        };

        inline bool GateOpen(const KeyGate& gate)
        {
            return gate.featureActive && gate.worldInteractive && !gate.editorActive &&
                   gate.eligibleProducerSelected;
        }

        // The rally key sets the rally, Shift+key clears it. Ctrl+key and
        // Alt+key are never ours (Alt+key arrives as WM_SYSKEYDOWN and never
        // reaches this either). Autorepeat never triggers an action.
        // Everything else passes through. `bound` defaults to V; an extended
        // key (Ins, Home, ...) does not match its numpad twin.
        inline KeyDecision ClassifyRallyKey(const KeyEvent& key, const KeyGate& gate, KeyLatch& latch,
                                            const RallyKey& bound = RallyKey{})
        {
            KeyDecision decision;
            if (key.vk != bound.vk || key.extended != bound.extended)
                return decision;

            if (key.msg == kWmKeyUp)
            {
                decision.swallow = latch.downSwallowed;
                latch.downSwallowed = false;
                return decision;
            }
            if (key.msg != kWmKeyDown)
                return decision;

            if ((key.lParam & kLParamPreviousStateBit) != 0)
            {
                // Autorepeat: no action; keep hiding the held key only when its
                // first keydown was hidden.
                decision.swallow = latch.downSwallowed;
                return decision;
            }

            const bool ours = !key.ctrl && !key.alt && GateOpen(gate);
            latch.downSwallowed = ours;
            if (!ours)
                return decision;
            decision.swallow = true;
            decision.action = key.shift ? KeyAction::ClearRally : KeyAction::SetRally;
            return decision;
        }

        // A unit a rallied producer has just finished. Scavengers and
        // constructors keep their stock behaviour; a unit that already has an
        // order (a mission script gave it one while it was being added) or that
        // the player cannot command is left alone.
        struct BuiltUnit
        {
            bool present = false;
            bool isScavenger = false;
            bool isConstructor = false;
            bool canCommand = false;
            int pendingCommand = 0; // nextCmd.what; 0 = CMD_NONE
            // In a network game: the producer or the unit is simulated by
            // another machine (or its ownership could not be read). Only the
            // owner's machine may order it.
            bool remote = false;
        };

        // Single-player always; a network game only while the running mission
        // has opted in (EXU, mission-scoped).
        inline bool ShouldBeActive(bool enabled, bool hooksInstalled, bool singlePlayer, bool missionAllowsNetwork)
        {
            return enabled && hooksInstalled && (singlePlayer || missionAllowsNetwork);
        }

        // DistributedObject object_type: 0 = unowned (built but never
        // published), 1 = local, 2 = remote (Docs/MPAUTH_SPLINTER_STATIC_ANALYSIS.md).
        constexpr uint8_t kObjectTypeLocal = 1;
        constexpr uint8_t kObjectTypeRemote = 2;

        // Network games only. An unreadable object is foreign. A remote one is
        // foreign. With mustBeLocal (a producer, which is always published), an
        // unowned one is foreign too; a unit fresh out of FinishBuild may still
        // be unowned on the machine that built it, so it only has to be not
        // remote.
        inline bool IsForeignObject(bool readable, uint8_t objectType, bool mustBeLocal)
        {
            if (!readable || objectType == kObjectTypeRemote)
                return true;
            return mustBeLocal && objectType != kObjectTypeLocal;
        }

        enum class BuiltUnitVerdict
        {
            Rally,
            NoRally,
            NoUnit,
            Remote,
            Scavenger,
            Constructor,
            NotCommandable,
            AlreadyOrdered,
        };

        inline BuiltUnitVerdict ClassifyBuiltUnit(bool producerHasRally, const BuiltUnit& unit)
        {
            if (!producerHasRally)
                return BuiltUnitVerdict::NoRally;
            if (!unit.present)
                return BuiltUnitVerdict::NoUnit;
            if (unit.remote)
                return BuiltUnitVerdict::Remote;
            if (unit.isScavenger)
                return BuiltUnitVerdict::Scavenger;
            if (unit.isConstructor)
                return BuiltUnitVerdict::Constructor;
            if (!unit.canCommand)
                return BuiltUnitVerdict::NotCommandable;
            if (unit.pendingCommand != 0)
                return BuiltUnitVerdict::AlreadyOrdered;
            return BuiltUnitVerdict::Rally;
        }

        inline const char* DescribeVerdict(BuiltUnitVerdict verdict)
        {
            switch (verdict)
            {
            case BuiltUnitVerdict::Rally: return "rally";
            case BuiltUnitVerdict::NoRally: return "no rally set";
            case BuiltUnitVerdict::NoUnit: return "no unit";
            case BuiltUnitVerdict::Remote: return "owned by another machine";
            case BuiltUnitVerdict::Scavenger: return "scavenger";
            case BuiltUnitVerdict::Constructor: return "constructor";
            case BuiltUnitVerdict::NotCommandable: return "not commandable";
            case BuiltUnitVerdict::AlreadyOrdered: return "already ordered";
            }
            return "?";
        }

        // One rally per producer. Keyed by the producer's object pointer; the
        // handle is kept so a dead producer whose memory was reused is not
        // mistaken for the original (the caller checks GetObj(handle) == key).
        struct RallyEntry
        {
            uintptr_t producer = 0;
            uint32_t producerHandle = 0;
            float pos[3] = {};
        };

        template <size_t Capacity>
        class RallyTable
        {
        public:
            size_t Size() const { return m_count; }
            const RallyEntry& At(size_t index) const { return m_entries[index]; }

            const RallyEntry* Find(uintptr_t producer) const
            {
                for (size_t i = 0; i < m_count; ++i)
                {
                    if (m_entries[i].producer == producer)
                        return &m_entries[i];
                }
                return nullptr;
            }

            // Sets or moves a rally. Returns false only when the table is full
            // and the producer is new.
            bool Set(uintptr_t producer, uint32_t handle, const float pos[3])
            {
                if (producer == 0)
                    return false;
                RallyEntry* entry = nullptr;
                for (size_t i = 0; i < m_count && !entry; ++i)
                {
                    if (m_entries[i].producer == producer)
                        entry = &m_entries[i];
                }
                if (!entry)
                {
                    if (m_count == Capacity)
                        return false;
                    entry = &m_entries[m_count++];
                    entry->producer = producer;
                }
                entry->producerHandle = handle;
                entry->pos[0] = pos[0];
                entry->pos[1] = pos[1];
                entry->pos[2] = pos[2];
                return true;
            }

            bool Clear(uintptr_t producer)
            {
                for (size_t i = 0; i < m_count; ++i)
                {
                    if (m_entries[i].producer != producer)
                        continue;
                    m_entries[i] = m_entries[m_count - 1];
                    m_entries[m_count - 1] = {};
                    --m_count;
                    return true;
                }
                return false;
            }

            void ClearAll()
            {
                for (size_t i = 0; i < m_count; ++i)
                    m_entries[i] = {};
                m_count = 0;
            }

        private:
            RallyEntry m_entries[Capacity] = {};
            size_t m_count = 0;
        };

        // The stock main-camera record (FUN_00439e60 returns &DAT_008eaae0):
        // screen centre x/y at +0x00/+0x04, focal scale x/y at +0x08/+0x0C,
        // and the world-to-view matrix at +0x40 (MAT_3D: 3x3 float rotation,
        // then the translation as three doubles at matrix +0x28). The stock
        // reticle projects its aim point with exactly this arithmetic
        // (FUN_005bc170 lines 61-81, matrix product FUN_0081fe60 lines 28-36).
        struct CameraProjection
        {
            float centerX = 0.0f;
            float centerY = 0.0f;
            float scaleX = 0.0f;
            float scaleY = 0.0f;
            float rot[9] = {};
            double trans[3] = {};
        };

        // The stock reticle's near limit (FUN_005bc170 line 78).
        constexpr double kMinViewDepth = 0.0001;

        // World point to screen pixels. False when the point is behind (or
        // on) the camera plane or the result is not finite.
        inline bool ProjectToScreen(const CameraProjection& cam, const float world[3], float& sx, float& sy)
        {
            const double x = world[0], y = world[1], z = world[2];
            const double vx = cam.rot[0] * x + cam.rot[3] * y + cam.rot[6] * z + cam.trans[0];
            const double vy = cam.rot[1] * x + cam.rot[4] * y + cam.rot[7] * z + cam.trans[1];
            const double vz = cam.rot[2] * x + cam.rot[5] * y + cam.rot[8] * z + cam.trans[2];
            if (!(vz > kMinViewDepth))
                return false;
            const double px = cam.scaleX * vx / vz + cam.centerX;
            const double py = cam.scaleY * vy / vz + cam.centerY;
            // NaN fails both comparisons; anything this far out is off screen.
            if (!(px > -1.0e6 && px < 1.0e6 && py > -1.0e6 && py < 1.0e6))
                return false;
            sx = static_cast<float>(px);
            sy = static_cast<float>(py);
            return true;
        }

        inline bool OnScreen(float sx, float sy, int viewW, int viewH)
        {
            return sx >= 0.0f && sy >= 0.0f && sx < static_cast<float>(viewW) && sy < static_cast<float>(viewH);
        }

        // ---- rally set mode ------------------------------------------------
        // With the three command hooks installed, V arms "set mode" instead
        // of setting the rally at once: the stock ground reticle and order
        // line then preview the point, and the stock confirm key (menu_press)
        // sets it. Without them V keeps the immediate custom-ray set.

        enum class SetKeyPlan
        {
            SetImmediately, // fallback: a hook is missing
            Arm,
            Cancel,
        };

        // A V press (not Shift+V) that passed the key gate.
        inline SetKeyPlan PlanSetKey(bool setModeAvailable, bool armed, bool selectionMatchesArmed)
        {
            if (!setModeAvailable)
                return SetKeyPlan::SetImmediately;
            if (armed && selectionMatchesArmed)
                return SetKeyPlan::Cancel;
            return SetKeyPlan::Arm;
        }

        // The selection (ControlPanel handle list) captured when set mode was
        // armed. The mode holds only while the live selection is exactly this
        // set of handles, so any selection change cancels it.
        template <size_t Capacity>
        class ArmedSelection
        {
        public:
            size_t Size() const { return m_count; }

            // False (and empty) for an empty or oversized selection.
            bool Capture(const uint32_t* handles, size_t count)
            {
                m_count = 0;
                if (!handles || count == 0 || count > Capacity)
                    return false;
                for (size_t i = 0; i < count; ++i)
                    m_handles[i] = handles[i];
                m_count = count;
                return true;
            }

            void Reset() { m_count = 0; }

            // Same handles, in any order.
            bool Matches(const uint32_t* handles, size_t count) const
            {
                if (m_count == 0 || !handles || count != m_count)
                    return false;
                for (size_t i = 0; i < count; ++i)
                {
                    bool found = false;
                    for (size_t j = 0; j < m_count && !found; ++j)
                        found = m_handles[j] == handles[i];
                    if (!found)
                        return false;
                }
                return true;
            }

        private:
            uint32_t m_handles[Capacity] = {};
            size_t m_count = 0;
        };

        // While armed and the selection is unchanged, a ground aim yields a
        // Go (so the stock reticle and order line draw) and an object aim
        // yields no command (no object orders while placing a rally).
        constexpr int kCmdNone = 0;
        constexpr int kCmdGoCommand = 3;

        inline bool OverrideAimCommand(bool armed, bool selectionMatches)
        {
            return armed && selectionMatches;
        }

        // ControlPanel::BroadcastCommand: a Go to a ground point from the
        // global ControlPanel, while armed with the selection unchanged, is
        // the rally confirm; it is consumed (no order is issued).
        inline bool BroadcastIsRallyConfirm(bool armed, bool selectionMatches, bool isGlobalControlPanel, int cmd,
                                            bool hasWhere)
        {
            return armed && selectionMatches && isGlobalControlPanel && cmd == kCmdGoCommand && hasWhere;
        }

        // Per-tick check of an armed set mode. Outside an interactive world
        // (pause menu, dialogs) the selection is not read and the mode holds.
        inline bool KeepArmed(bool active, bool worldInteractive, bool selectionMatches)
        {
            if (!active)
                return false;
            if (!worldInteractive)
                return true;
            return selectionMatches;
        }

        // What the per-frame main-loop tick may do. Everything that reads or
        // writes game objects waits for an interactive world: the tick also
        // runs inside nested modal loops (pause menu, dialogs).
        struct TickPlan
        {
            bool applyPending = false;   // run the queued V / Shift+V
            bool dropPending = false;    // discard it unrun
            bool standDownClear = false; // feature off: forget every rally
            bool livenessCheck = false;  // look for dead producers
        };

        inline TickPlan PlanTick(bool worldInteractive, bool active, bool hasPending, bool tableNonEmpty,
                                 bool livenessDue)
        {
            TickPlan plan;
            if (!worldInteractive)
            {
                // A press queued just before a menu opened is not replayed later.
                plan.dropPending = hasPending;
                return plan;
            }
            if (!active)
            {
                plan.dropPending = hasPending;
                plan.standDownClear = tableNonEmpty;
                return plan;
            }
            plan.applyPending = hasPending;
            plan.livenessCheck = tableNonEmpty && livenessDue;
            return plan;
        }

        // ---- the command-panel row ("V Rally Point") --------------------------
        // ControlPanel::Render (FUN_004a08e0) sets this+0x11A0 to 4 in its
        // unit-command branch (lines 1313-1314: DAT_00919875 == 0 and a
        // selection), and draws key glyphs only in the classic layout
        // (DAT_00915567 == 0, lines 402 and 1383). It writes +0x11A0 only
        // while there is a user object (lines 367-368), so without one the
        // field is stale and the panel is not drawn.
        constexpr int kPanelUnitCommandState = 4;

        struct PanelRowGate
        {
            bool active = false;           // feature on (SP, ini)
            bool userObject = false;       // GameObject::userObject non-null
            bool branchInputHeld = true;   // DAT_00919875 != 0
            int panelState = 0;            // ControlPanel +0x11A0
            int selectionCount = 0;        // ControlPanel +0x188
            bool altLayout = true;         // DAT_00915567 != 0
            bool eligibleProducer = false; // the V key gate's producer test
        };

        inline bool PanelRowVisible(const PanelRowGate& gate)
        {
            return gate.active && gate.userObject && !gate.branchInputHeld &&
                   gate.panelState == kPanelUnitCommandState && gate.selectionCount > 0 && !gate.altLayout &&
                   gate.eligibleProducer;
        }

        // The row reads "Rally" beside its V key, and "Cancel" while set mode
        // is armed for the current selection (V then cancels it,
        // PlanSetKey). The placement uses the wider of the two, and both
        // start at the same x, so neither the key nor the line moves when
        // the label changes.
        constexpr char kPanelRowLabel[] = "Rally";
        constexpr char kPanelRowArmedLabel[] = "Cancel";

        inline const char* PanelRowLabel(bool armedAndMatching)
        {
            return armedAndMatching ? kPanelRowArmedLabel : kPanelRowLabel;
        }

        // ---- the SPACE row label in set mode -------------------------------
        // ControlPanel::Render draws the SPACE label as
        // Localize("names", table[cmd * 2]) (FUN_004a08e0.c line 604); the
        // table entry for the Go To command is "Go To" (0x00877EAC). While set
        // mode is armed the next ground click places the rally instead of
        // giving that order, so the row reads "Rally". Any other key, or set
        // mode off, keeps the stock lookup.
        constexpr char kSpaceRowStockKey[] = "Go To";
        constexpr char kSpaceRowArmedLabel[] = "Rally";

        inline bool SpaceRowLabelOverride(bool armed, const char* key)
        {
            if (!armed || !key)
                return false;
            for (size_t i = 0;; ++i)
            {
                if (key[i] != kSpaceRowStockKey[i])
                    return false;
                if (key[i] == '\0')
                    return true;
            }
        }

        // Row anchors (x, y) from FUN_0049f9e0 lines 57-69: x is the same for
        // every row, y is the row centre with a constant pitch. The new row is
        // one pitch below TAB (row 12), measured from ALT (row 11). False for a
        // layout that is not a downward run of rows.
        constexpr int kMaxPanelRowPitch = 256;

        inline bool PanelRowAnchor(int tabX, int tabY, int altY, int& x, int& y)
        {
            const int pitch = tabY - altY;
            if (pitch <= 0 || pitch > kMaxPanelRowPitch)
                return false;
            x = tabX;
            y = tabY + pitch;
            return true;
        }

        // Where FUN_0068c560 puts a key sprite for the stock call
        // (anchorX - inset, anchorY, flags 0x60001): 0x20000 right-aligns the
        // sprite on x, 0x40000 centres it on y (h >> 1), and the size is the
        // atlas size times the UI scale, truncated.
        struct PixelRect
        {
            int left = 0;
            int top = 0;
            int right = 0;
            int bottom = 0;
        };

        // widthPx > 0 replaces the atlas-width term (a widened drawn cap).
        inline bool KeyBoxRect(int anchorX, int anchorY, int inset, int spriteW, int spriteH, float scaleX,
                               float scaleY, PixelRect& out, int widthPx = 0)
        {
            const int w = widthPx > 0 ? widthPx : static_cast<int>(static_cast<float>(spriteW) * scaleX);
            const int h = static_cast<int>(static_cast<float>(spriteH) * scaleY);
            if (w <= 0 || h <= 0)
                return false;
            out.right = anchorX - inset;
            out.left = out.right - w;
            out.top = anchorY - (h >> 1);
            out.bottom = out.top + h;
            return true;
        }

        // Width in pixels of the drawn cap for a key name of `nameLen`
        // characters whose measured text is `textW` wide. One character keeps
        // the key_0-sized cap (atlas width times the UI scale); a longer name
        // widens it to the text plus a padding of two reference units
        // (scaled, at least 1 px) each side, never narrower than that cap.
        // The padding is a choice, not read from key_TAB/key_SPACE (UNVERIFIED).
        inline int KeyCapWidthPx(int atlasW, float scaleX, size_t nameLen, float textW)
        {
            const int base = static_cast<int>(static_cast<float>(atlasW) * scaleX);
            if (nameLen <= 1 || !(textW == textW) || textW <= 0.0f || textW > 1.0e6f || !(scaleX > 0.0f))
                return base;
            const int scaled = static_cast<int>(2.0f * scaleX);
            const int pad = scaled >= 1 ? scaled : 1;
            const int wide = static_cast<int>(textW) + 2 * pad;
            return wide > base ? wide : base;
        }

        // The drawn key cap: a filled rect with its four corners notched by
        // one reference unit (scaled, at least 1 px), the shape of the stock
        // white caps. HudFillRect (FUN_0068afb0) takes inclusive corners:
        // FUN_0068af70 passes x2 + 1 and y2 + 1 to the quad. Returns how many
        // rects to fill (1 when the cap is too small to notch, else 2: a
        // full-width band and a full-height band), 0 for an empty box.
        struct FillRect
        {
            int x1 = 0;
            int y1 = 0;
            int x2 = 0;
            int y2 = 0;
        };

        inline int KeyCapFillRects(const PixelRect& box, float scaleX, FillRect out[2])
        {
            const int w = box.right - box.left;
            const int h = box.bottom - box.top;
            if (w <= 0 || h <= 0)
                return 0;
            const int scaled = static_cast<int>(scaleX);
            const int notch = scaled >= 1 ? scaled : 1;
            if (2 * notch >= w || 2 * notch >= h)
            {
                out[0] = FillRect{ box.left, box.top, box.right - 1, box.bottom - 1 };
                return 1;
            }
            out[0] = FillRect{ box.left, box.top + notch, box.right - 1, box.bottom - 1 - notch };
            out[1] = FillRect{ box.left + notch, box.top, box.right - 1 - notch, box.bottom - 1 };
            return 2;
        }

        // The stock row text call: y = (int)(rowY - textHeight / 2.0).
        inline int CenteredTextY(int rowY, float textHeight)
        {
            return static_cast<int>(static_cast<double>(rowY) - static_cast<double>(textHeight) / 2.0);
        }

        // ---- where the row goes ---------------------------------------------
        // Preferred: on the TAB row's line (row 12), right-aligned to the
        // scrap-cost column. The classic layout draws the cost text
        // left-aligned at rowRect.right - (int)(scaleX * 20) (FUN_004a08e0.c
        // lines 1436-1440; the trailing DAT_009173e0 term is 0 in the classic
        // layout, FUN_0049f9e0.c line 43), so the column's right edge is that
        // x plus the width of a two-digit cost ("%02ld", line 1430). The TAB
        // label is drawn left-aligned at the TAB anchor x (lines 707-712).
        // When that label would reach the V key, the row drops to just under
        // the menu underlay instead: the underlay is drawn top-left anchored
        // at CommandUI bounds.top with height (int)(spriteH * scaleY / 2.0)
        // (lines 402-410; FUN_0068ca30.c lines 49-64), and only while the
        // viewport is wider than 400 px (line 402). Without the underlay the
        // row takes its old place, one row pitch under TAB.
        enum class PanelRowPlacement
        {
            Hidden,
            TabLine,       // on the TAB row's line
            BelowUnderlay, // under the underlay's bottom edge
            BelowTab,      // one pitch under TAB (no underlay at this width)
        };

        struct PanelRowLayoutInput
        {
            int tabX = 0; // CommandMenuRowAnchors row 12
            int tabY = 0;
            int altY = 0;       // row 11, for the pitch
            int rowRight = 0;   // CommandMenuRowRects row 12 .right
            float scaleX = 0.0f; // HudFeedbackScale
            float scaleY = 0.0f;
            int inset = 0; // CommandMenuKeyInset
            int keyW = 0;  // key sprite size, atlas units
            int keyH = 0;
            int keyWidthPx = 0;  // > 0: the key's pixel width (a wide drawn cap), else keyW * scaleX
            float labelW = 0.0f; // the wider measured row label
            float labelH = 0.0f; // the font's line height
            float costW = 0.0f;  // measured "00"
            bool cancelKnown = false;
            float cancelW = 0.0f; // measured localized TAB label
            int viewportW = 0;    // HudViewportWidth
            int viewportH = 0;    // HudViewportHeight (0: unknown)
            bool underlayKnown = false;
            int underlayTop = 0;     // CommandUI bounds.top
            int underlaySpriteH = 0; // atlas height of the underlay sprite
        };

        struct PanelRowLayout
        {
            PanelRowPlacement placement = PanelRowPlacement::Hidden;
            int labelX = 0; // left of the label text; the key sits left of it
            int rowY = 0;   // the row centre, as the stock rows use it
        };

        // The stock underlay draw needs a viewport wider than this (line 402).
        constexpr int kUnderlayMinViewportWidth = 400;

        // Bottom edge of the underlay as FUN_004a08e0.c lines 406-410 size it.
        inline int UnderlayBottom(int underlayTop, int spriteH, float scaleY)
        {
            return underlayTop +
                   static_cast<int>(static_cast<double>(static_cast<float>(spriteH) * scaleY) / 2.0);
        }

        inline bool PanelRowFinite(float v)
        {
            return v == v && v < 1.0e9f && v > -1.0e9f;
        }

        inline PanelRowLayout ChoosePanelRowLayout(const PanelRowLayoutInput& in)
        {
            PanelRowLayout out;
            if (!PanelRowFinite(in.scaleX) || !PanelRowFinite(in.scaleY) || in.scaleX <= 0.0f || in.scaleY <= 0.0f)
                return out;
            if (!PanelRowFinite(in.labelW) || !PanelRowFinite(in.labelH) || !PanelRowFinite(in.costW) ||
                in.labelW <= 0.0f || in.costW < 0.0f || in.labelH < 0.0f)
                return out;
            const int pitch = in.tabY - in.altY;
            if (pitch <= 0 || pitch > kMaxPanelRowPitch || in.inset < 0)
                return out;
            const int keyWpx = in.keyWidthPx > 0 ? in.keyWidthPx
                                                 : static_cast<int>(static_cast<float>(in.keyW) * in.scaleX);
            const int keyHpx = static_cast<int>(static_cast<float>(in.keyH) * in.scaleY);
            if (keyWpx <= 0 || keyHpx <= 0)
                return out;

            const int columnRight =
                in.rowRight - static_cast<int>(in.scaleX * 20.0f) + static_cast<int>(in.costW);
            const int labelX = columnRight - static_cast<int>(in.labelW);
            const int groupLeft = labelX - in.inset - keyWpx;
            // The key must stay right of the row's own key slot and on screen.
            if (groupLeft <= in.tabX - in.inset || (in.viewportW > 0 && columnRight > in.viewportW))
                return out;

            // Key or text, whichever is taller, sets the row's half height.
            const int textH = static_cast<int>(in.labelH);
            const int half = ((keyHpx > textH ? keyHpx : textH) + 1) / 2;

            int rowY = 0;
            PanelRowPlacement placement = PanelRowPlacement::Hidden;
            const bool cancelFits = in.cancelKnown && PanelRowFinite(in.cancelW) && in.cancelW >= 0.0f &&
                                    in.tabX + static_cast<int>(in.cancelW) + 2 * in.inset <= groupLeft;
            if (cancelFits)
            {
                placement = PanelRowPlacement::TabLine;
                rowY = in.tabY;
            }
            else if (in.viewportW > 0 && in.viewportW <= kUnderlayMinViewportWidth)
            {
                placement = PanelRowPlacement::BelowTab;
                rowY = in.tabY + pitch;
            }
            else if (in.viewportW > kUnderlayMinViewportWidth && in.underlayKnown && in.underlaySpriteH > 0)
            {
                // Clear of the underlay's bottom edge by one key inset, and
                // never above the old one-pitch-down place.
                placement = PanelRowPlacement::BelowUnderlay;
                rowY = UnderlayBottom(in.underlayTop, in.underlaySpriteH, in.scaleY) + in.inset + half;
                if (rowY < in.tabY + pitch)
                    rowY = in.tabY + pitch;
            }
            else
            {
                return out;
            }
            if (in.viewportH > 0 && rowY + half > in.viewportH)
                return out;
            out.placement = placement;
            out.labelX = labelX;
            out.rowY = rowY;
            return out;
        }

        // ---- the "[Shift] [key] Clear" row ----------------------------------
        // A second row that teaches Shift+<rally key>. Same right edge as the
        // Rally row. Preferred on the ALT line (one pitch above TAB) when the
        // Rally row is on the TAB line and the group clears the ALT label by
        // two insets (the TAB-line test, against the ALT label); otherwise one
        // pitch below the Rally row.
        constexpr char kClearRowLabel[] = "Clear";
        constexpr char kClearRowShiftCap[] = "Shift";

        enum class ClearRowPlacement
        {
            Hidden,
            AltLine,
            BelowRally,
        };

        struct ClearRowLayoutInput
        {
            PanelRowLayout rally; // the placed Rally row
            float rallyLabelW = 0.0f; // the width ChoosePanelRowLayout used for the Rally label
            int tabX = 0;
            int tabY = 0;
            int altY = 0;
            int inset = 0;
            int shiftWidthPx = 0; // the Shift cap
            int keyWidthPx = 0;   // the bound key's cap
            int keyHeightPx = 0;
            float clearW = 0.0f;  // measured "Clear"
            float labelH = 0.0f;
            bool altKnown = false;
            float altW = 0.0f; // measured ALT label
            // Measured "00": on the ALT line the group may slide right past the
            // Rally column by up to two of these to clear the ALT label.
            float costW = 0.0f;
            int viewportW = 0;
            int viewportH = 0; // 0: unknown
            // The panel underlay, as ChoosePanelRowLayout saw it: a Clear row
            // below a TAB-line Rally row must clear its bottom edge.
            bool underlayKnown = false;
            int underlayTop = 0;
            int underlaySpriteH = 0;
            float scaleY = 0.0f;
        };

        struct ClearRowLayout
        {
            ClearRowPlacement placement = ClearRowPlacement::Hidden;
            int labelX = 0; // left of the "Clear" text; the caps sit left of it
            int rowY = 0;
        };

        inline ClearRowLayout ChooseClearRowLayout(const ClearRowLayoutInput& in)
        {
            ClearRowLayout out;
            if (in.rally.placement == PanelRowPlacement::Hidden)
                return out;
            if (!PanelRowFinite(in.rallyLabelW) || !PanelRowFinite(in.clearW) || !PanelRowFinite(in.labelH) ||
                in.rallyLabelW <= 0.0f || in.clearW <= 0.0f || in.labelH < 0.0f)
                return out;
            const int pitch = in.tabY - in.altY;
            if (pitch <= 0 || pitch > kMaxPanelRowPitch || in.inset < 0 || in.shiftWidthPx <= 0 ||
                in.keyWidthPx <= 0 || in.keyHeightPx <= 0)
                return out;
            const int columnRight = in.rally.labelX + static_cast<int>(in.rallyLabelW);
            int labelX = columnRight - static_cast<int>(in.clearW);
            const int groupLeft = labelX - in.inset - in.keyWidthPx - in.inset - in.shiftWidthPx;
            if (groupLeft <= in.tabX - in.inset || (in.viewportW > 0 && columnRight > in.viewportW))
                return out;
            // On the ALT line the group starts at the Rally column's left, or
            // just past the ALT label when that reaches further, as long as it
            // then ends within two cost widths right of the Rally column.
            int altShift = -1;
            if (in.rally.placement == PanelRowPlacement::TabLine && in.altKnown && PanelRowFinite(in.altW) &&
                in.altW >= 0.0f)
            {
                const int altEnd = in.tabX + static_cast<int>(in.altW) + 2 * in.inset;
                const int shift = altEnd > groupLeft ? altEnd - groupLeft : 0;
                const int slack = PanelRowFinite(in.costW) && in.costW > 0.0f ? static_cast<int>(2.0f * in.costW) : 0;
                if (shift <= slack && (in.viewportW <= 0 || columnRight + shift <= in.viewportW))
                    altShift = shift;
            }
            const bool altFits = altShift >= 0;
            const int textH = static_cast<int>(in.labelH);
            const int half = ((in.keyHeightPx > textH ? in.keyHeightPx : textH) + 1) / 2;
            ClearRowPlacement placement;
            int rowY;
            if (altFits)
            {
                placement = ClearRowPlacement::AltLine;
                rowY = in.altY;
                labelX += altShift;
            }
            else
            {
                placement = ClearRowPlacement::BelowRally;
                rowY = in.rally.rowY + pitch;
                // Under a TAB-line Rally row, one pitch down lands on the
                // underlay's bottom border: clear it like the Rally fallback.
                if (in.rally.placement == PanelRowPlacement::TabLine && in.underlayKnown &&
                    in.underlaySpriteH > 0 && PanelRowFinite(in.scaleY) && in.scaleY > 0.0f)
                {
                    const int below = UnderlayBottom(in.underlayTop, in.underlaySpriteH, in.scaleY) + in.inset + half;
                    if (below > rowY)
                        rowY = below;
                }
            }
            if (in.viewportH > 0 && rowY + half > in.viewportH)
                return out;
            out.placement = placement;
            out.labelX = labelX;
            out.rowY = rowY;
            return out;
        }

        // ---- producer type: beacon lamp colour and HUD label ---------------

        enum class ProducerKind
        {
            Unknown,
            Recycler,
            Factory,
        };

        // Recycler keeps the original green lamp; only a Factory is amber.
        // Unknown (anything unclassified) stays green.
        inline bool UseAmberLamp(ProducerKind kind)
        {
            return kind == ProducerKind::Factory;
        }

        constexpr size_t kLabelMax = 32;         // buffer size, NUL included
        constexpr size_t kUnitNameLabelMax = 20; // unitName characters kept
        constexpr char kGenericLabel[] = "Rally";
        constexpr char kLabelSuffix[] = " rally";

        // "<unitName> rally" into out (cap bytes, NUL-terminated); the generic
        // "Rally" when unitName is null, empty or has no printable text.
        // Only printable ASCII is kept (spaces trimmed at both ends), at most
        // kUnitNameLabelMax characters. Returns the length written.
        inline size_t FormatRallyLabel(const char* unitName, char* out, size_t cap)
        {
            if (!out || cap == 0)
                return 0;
            out[0] = '\0';
            char name[kUnitNameLabelMax + 1] = {};
            size_t n = 0;
            for (size_t i = 0; unitName && unitName[i] && n < kUnitNameLabelMax; ++i)
            {
                const unsigned char c = static_cast<unsigned char>(unitName[i]);
                if (c < 0x20 || c > 0x7E)
                    continue;
                if (c == ' ' && n == 0)
                    continue;
                name[n++] = static_cast<char>(c);
            }
            while (n > 0 && name[n - 1] == ' ')
                --n;
            name[n] = '\0';
            const char* const parts[2] = { n ? name : kGenericLabel, n ? kLabelSuffix : "" };
            size_t len = 0;
            for (const char* part : parts)
                for (size_t i = 0; part[i] && len + 1 < cap; ++i)
                    out[len++] = part[i];
            out[len] = '\0';
            return len;
        }

        // Half the backing panel's width for a label of `length` characters;
        // 22 for the generic "Rally", which is the original fixed panel.
        inline int LabelHalfWidth(size_t length)
        {
            return static_cast<int>(length) * 4 + 2;
        }
    }
}
