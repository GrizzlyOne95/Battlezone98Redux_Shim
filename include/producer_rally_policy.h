#pragma once
// producer_rally_policy.h
// Pure decision rules for [Gameplay] ProducerRallyPoints. No Windows or
// engine calls, so tests/producer_rally_policy_tests.cpp can exercise them
// directly. The engine side is src/patches/producer_rally_points.cpp; the
// behaviour is documented in Docs/PRODUCER_RALLY_POINTS.md.

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

        struct KeyEvent
        {
            unsigned msg = 0;
            unsigned vk = 0;
            unsigned long long lParam = 0;
            bool shift = false;
            bool ctrl = false;
            bool alt = false;
        };

        // Everything outside the key itself that decides whether V is ours.
        struct KeyGate
        {
            // [Gameplay] ProducerRallyPoints on, hooks installed, single player.
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

        // V sets the rally, Shift+V clears it. Ctrl+V and Alt+V are never ours
        // (Alt+V arrives as WM_SYSKEYDOWN and never reaches this either).
        // Autorepeat never triggers an action. Everything else passes through.
        inline KeyDecision ClassifyRallyKey(const KeyEvent& key, const KeyGate& gate, KeyLatch& latch)
        {
            KeyDecision decision;
            if (key.vk != kVkV)
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
        };

        enum class BuiltUnitVerdict
        {
            Rally,
            NoRally,
            NoUnit,
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

        // Evenly spaced dots strictly between two screen points (the line
        // from producer to rally): gaps of at most `spacing` pixels, at most
        // `maxDots` dots. Writes x/y pairs into `out`; returns how many.
        inline size_t LineDots(float x0, float y0, float x1, float y1, float spacing, size_t maxDots, float (*out)[2])
        {
            const float dx = x1 - x0;
            const float dy = y1 - y0;
            const float lengthSq = dx * dx + dy * dy;
            const float spacingSq = spacing * spacing;
            if (!(spacing > 0.0f) || !(lengthSq > spacingSq) || maxDots == 0)
                return 0;
            // Fewest segments whose length is within `spacing` (no sqrt).
            size_t segments = 2;
            while (segments <= maxDots &&
                   lengthSq > spacingSq * static_cast<float>(segments) * static_cast<float>(segments))
                ++segments;
            const size_t dots = segments - 1;
            for (size_t i = 1; i <= dots; ++i)
            {
                const float t = static_cast<float>(i) / static_cast<float>(segments);
                out[i - 1][0] = x0 + dx * t;
                out[i - 1][1] = y0 + dy * t;
            }
            return dots;
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
    }
}
