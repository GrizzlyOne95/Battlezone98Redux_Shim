#pragma once
// rts_commands_policy.h
// Pure rules for the RTS command extras ([Gameplay] RtsRemoteTarget,
// RtsSmartCommandMenu, RtsSmartRepairReload, RtsAreaSelect, RtsHold): the
// mixed-selection command-menu merge, which selected units an order is sent
// to, unit families, target cycles, the area-select radius filter and the
// rebindable keys. No Windows or engine calls, so
// tests/rts_commands_policy_tests.cpp runs them directly. The engine side is
// src/patches/rts_commands.cpp; behaviour and evidence: Docs/RTS_COMMANDS.md.

#include "quicksave_key_policy.h"

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace RtsCommandsPolicy
    {
        // ---- the ModeList (GameObject +0x1A4, FUN_0049f430) ------------------

        // 11 mode ids, then the enabled mask (bit = slot, FUN_0049f230) and
        // the active slot (FUN_0049f270 lines 9-20; ControlPanel::Render
        // copies 0xD dwords, FUN_004a08e0 lines 796-801).
        constexpr int kModeSlots = 11;
        struct ModeList
        {
            int32_t modes[kModeSlots] = {};
            uint32_t enabled = 0;
            int32_t active = -1;
        };
        static_assert(sizeof(ModeList) == 0x34, "ModeList is 0xD dwords");

        // Mode ids (the names table at 0x008E7B00, stride 8).
        constexpr int kModeNone = 0;
        constexpr int kModeGoTo = 1;
        constexpr int kModeFollowMe = 2;
        constexpr int kModeGetRepair = 5;
        constexpr int kModeGetReload = 6;
        constexpr int kModeHunt = 13;
        constexpr int kModeAttack = 14;
        constexpr int kModeFollowClose = 16;
        constexpr int kModeDefend = 17;
        // Command ids (the names table at 0x008E7A18): CMD_DEFEND.
        constexpr int kCmdDefend = 0xF;

        // ControlPanel selectList: 91 handles (+0x1C up to selectNum at +0x188).
        constexpr int kSelectCapacity = 0x16C / 4;

        inline bool SlotEnabled(const ModeList& list, int slot)
        {
            return slot >= 0 && slot < kModeSlots && ((list.enabled >> slot) & 1u) != 0;
        }

        // ModeList::GetMode (FUN_0046faf0): the mode in `slot`, 0 off the end.
        inline int ModeAt(const ModeList& list, int slot)
        {
            return slot >= 0 && slot < kModeSlots ? list.modes[slot] : kModeNone;
        }

        // The menu entries the merge keeps for a mixed selection, each sent
        // only to the units that hold it (Follow Close is the Formation
        // order). Mode ids, not slots: the walker/APC/howitzer lists hold 0 or
        // another mode where a wingman holds Hunt, Follow Close and Defend.
        enum SmartSet : unsigned
        {
            kSmartCommandMenu = 1u << 0, // Hunt, Follow Close, Defend
            kSmartRepairReload = 1u << 1, // Get Repair, Get Reload
        };

        inline bool IsSmartMode(int mode, unsigned smart)
        {
            switch (mode)
            {
            case kModeHunt:
            case kModeFollowClose:
            case kModeDefend:
                return (smart & kSmartCommandMenu) != 0;
            case kModeGetRepair:
            case kModeGetReload:
                return (smart & kSmartRepairReload) != 0;
            default:
                return false;
            }
        }

        // The stock rule, ModeList::Intersect (FUN_0049f270): a slot keeps its
        // mode only when both lists hold the same id, the enabled masks are
        // ANDed, and the active slot survives only when both agree and it
        // still names a mode.
        inline void StockIntersect(ModeList& merged, const ModeList& other)
        {
            for (int i = 0; i < kModeSlots; ++i)
            {
                if (merged.modes[i] != other.modes[i])
                    merged.modes[i] = kModeNone;
            }
            merged.enabled &= other.enabled;
            if (!(merged.active == other.active && ModeAt(merged, merged.active) != kModeNone))
                merged.active = -1;
        }

        // The smart rule. For a smart mode (see IsSmartMode):
        //   * both lists hold it in the slot: it stays, enabled when either
        //     unit has it enabled (Get Repair shows when any unit needs it);
        //   * only one list holds it there and the other holds a non-smart
        //     mode or nothing: the smart mode wins, with its own enabled bit.
        // Every other slot follows the stock rule, as does the active slot.
        // With `smart` 0 this is StockIntersect.
        inline void SmartIntersect(ModeList& merged, const ModeList& other, unsigned smart)
        {
            const ModeList before = merged;
            StockIntersect(merged, other);
            if (smart == 0)
                return;
            for (int i = 0; i < kModeSlots; ++i)
            {
                const int a = before.modes[i];
                const int b = other.modes[i];
                const bool sa = IsSmartMode(a, smart);
                const bool sb = IsSmartMode(b, smart);
                const uint32_t bit = 1u << i;
                const bool ea = (before.enabled & bit) != 0;
                const bool eb = (other.enabled & bit) != 0;
                bool keep = false;
                int mode = kModeNone;
                bool on = false;
                if (a == b && sa)
                {
                    keep = true;
                    mode = a;
                    on = ea || eb;
                }
                else if (sa && !sb)
                {
                    keep = true;
                    mode = a;
                    on = ea;
                }
                else if (sb && !sa)
                {
                    keep = true;
                    mode = b;
                    on = eb;
                }
                if (!keep)
                    continue;
                merged.modes[i] = mode;
                merged.enabled = on ? (merged.enabled | bit) : (merged.enabled & ~bit);
            }
            merged.active = (before.active == other.active && ModeAt(merged, before.active) != kModeNone)
                                ? before.active
                                : -1;
        }

        // Folds every selected unit's list the way ControlPanel::Render does
        // (copy the first, intersect the rest; FUN_004a08e0 lines 796-809).
        inline ModeList MergeSelection(const ModeList* lists, int count, unsigned smart)
        {
            ModeList merged;
            if (!lists || count <= 0)
                return merged;
            merged = lists[0];
            for (int i = 1; i < count; ++i)
                SmartIntersect(merged, lists[i], smart);
            return merged;
        }

        // True when the unit's own menu holds `mode` in an enabled slot.
        inline bool UnitTakesMode(const ModeList& unit, int mode)
        {
            if (mode == kModeNone)
                return false;
            for (int i = 0; i < kModeSlots; ++i)
            {
                if (unit.modes[i] == mode && SlotEnabled(unit, i))
                    return true;
            }
            return false;
        }

        // The menu sends `mode` to this unit. Stock sends every mode to every
        // commandable selected unit (FUN_004a7140); a smart mode goes only to
        // units whose own menu offers it, so the others keep their orders.
        inline bool SendModeToUnit(int mode, const ModeList& unit, unsigned smart)
        {
            return !IsSmartMode(mode, smart) || UnitTakesMode(unit, mode);
        }

        // ---- unit families (area select) -------------------------------------

        enum class Family
        {
            None,
            Combat, // Wingman, APC, Walker
            TurretTank,
            Howitzer,
            Minelayer,
            Scavenger,
            Tug,
        };

        // From the object's most-derived MSVC RTTI type name (".?AVWingman@@").
        // Howitzer derives from TurretTank and every other class here from
        // HoverCraft (Walker from Craft), so only the exact name is used.
        inline Family ClassifyFamily(const char* rttiName)
        {
            if (!rttiName)
                return Family::None;
            struct Entry
            {
                const char* name;
                Family family;
            };
            static const Entry kEntries[] = {
                { ".?AVWingman@@", Family::Combat },     { ".?AVAPC@@", Family::Combat },
                { ".?AVWalker@@", Family::Combat },      { ".?AVTurretTank@@", Family::TurretTank },
                { ".?AVHowitzer@@", Family::Howitzer },  { ".?AVMinelayer@@", Family::Minelayer },
                { ".?AVScavenger@@", Family::Scavenger }, { ".?AVTug@@", Family::Tug },
            };
            for (const Entry& entry : kEntries)
            {
                if (std::strcmp(rttiName, entry.name) == 0)
                    return entry.family;
            }
            return Family::None;
        }

        // Combat units take Hold (they have a Defend entry; Wingman
        // UpdateModeList 0x00613630 slot 9). Turret tanks and howitzers hold
        // too when their menu offers Defend; the engine side checks the menu.
        inline const char* FamilyName(Family family)
        {
            switch (family)
            {
            case Family::Combat: return "combat";
            case Family::TurretTank: return "turret tank";
            case Family::Howitzer: return "howitzer";
            case Family::Minelayer: return "minelayer";
            case Family::Scavenger: return "scavenger";
            case Family::Tug: return "tug";
            default: return "none";
            }
        }

        // A base structure for the building cycle: anything that derives from
        // Building, plus the deployed producers (Recycler, Factory, Armory
        // derive from Producer/HoverCraft, not Building). The Construction
        // Rig is a vehicle and is left out.
        inline bool IsBaseStructure(bool derivesFromBuilding, const char* rttiName)
        {
            if (derivesFromBuilding)
                return true;
            if (!rttiName)
                return false;
            return std::strcmp(rttiName, ".?AVRecycler@@") == 0 || std::strcmp(rttiName, ".?AVFactory@@") == 0 ||
                   std::strcmp(rttiName, ".?AVArmory@@") == 0;
        }

        // ---- target cycles ----------------------------------------------------

        // The handle's sequence number (GameObject::GetHandle 0x00462380:
        // ([+0x160] << 20) | ([+0x15C] & 0xFFFFF)). Larger is newer
        // (UNVERIFIED that the counter only grows; see the doc).
        inline uint32_t HandleSequence(uint32_t handle)
        {
            return handle & 0xFFFFFu;
        }

        // Sorts handles newest first (insertion sort; n is small).
        inline void SortNewestFirst(uint32_t* handles, int count)
        {
            for (int i = 1; i < count; ++i)
            {
                const uint32_t h = handles[i];
                int j = i - 1;
                while (j >= 0 && HandleSequence(handles[j]) < HandleSequence(h))
                {
                    handles[j + 1] = handles[j];
                    --j;
                }
                handles[j + 1] = h;
            }
        }

        // The next entry after `current` in `list` (wrapping), or the first
        // when `current` is not in it. 0 for an empty list.
        inline uint32_t NextInCycle(const uint32_t* list, int count, uint32_t current)
        {
            if (!list || count <= 0)
                return 0;
            for (int i = 0; i < count; ++i)
            {
                if (list[i] == current && current != 0)
                    return list[(i + 1) % count];
            }
            return list[0];
        }

        // ---- area select ------------------------------------------------------

        constexpr float kAreaRadius = 100.0f;
        constexpr float kAreaRadiusWide = 200.0f;

        // Horizontal distance (x, z; y is up), squared.
        inline float HorizontalDistanceSq(const float a[3], const float b[3])
        {
            const float dx = a[0] - b[0];
            const float dz = a[2] - b[2];
            return dx * dx + dz * dz;
        }

        inline bool WithinRadius(const float centre[3], const float pos[3], float radius)
        {
            return radius > 0.0f && HorizontalDistanceSq(centre, pos) <= radius * radius;
        }

        struct AreaCandidate
        {
            uint32_t handle = 0;
            Family family = Family::None;
            float pos[3] = {};
            bool ownCommandable = false; // the player's team and CanCommand
        };

        // Handles to add to the selection: own commandable units of `family`
        // within `radius` of `centre`, not already selected, nearest first,
        // never past kSelectCapacity (SelectAdd 0x004A6C70 checks neither
        // duplicates nor room). Returns how many were written to `out`.
        inline int PlanAreaAdd(const uint32_t* selected, int selectedCount, const AreaCandidate* candidates,
                               int candidateCount, Family family, const float centre[3], float radius,
                               uint32_t* out, int outCapacity)
        {
            if (family == Family::None || !candidates || !out || outCapacity <= 0 || selectedCount < 0)
                return 0;
            int room = kSelectCapacity - selectedCount;
            if (room > outCapacity)
                room = outCapacity;
            if (room <= 0)
                return 0;
            int n = 0;
            float dist[kSelectCapacity] = {};
            for (int c = 0; c < candidateCount; ++c)
            {
                const AreaCandidate& cand = candidates[c];
                if (!cand.ownCommandable || cand.family != family || cand.handle == 0 ||
                    !WithinRadius(centre, cand.pos, radius))
                    continue;
                bool already = false;
                for (int s = 0; s < selectedCount && !already; ++s)
                    already = selected && selected[s] == cand.handle;
                for (int s = 0; s < n && !already; ++s)
                    already = out[s] == cand.handle;
                if (already)
                    continue;
                const float d = HorizontalDistanceSq(centre, cand.pos);
                // Keep the `room` nearest: insert sorted, drop the farthest.
                int at = n;
                while (at > 0 && dist[at - 1] > d)
                    --at;
                if (at >= room)
                    continue;
                const int last = n < room ? n : room - 1;
                for (int k = last; k > at; --k)
                {
                    out[k] = out[k - 1];
                    dist[k] = dist[k - 1];
                }
                out[at] = cand.handle;
                dist[at] = d;
                if (n < room)
                    ++n;
            }
            return n;
        }

        // ---- the Shift alternate on the Defend entry --------------------------

        // While Shift is held the Defend entry reads "Hold" and choosing it
        // issues Hold. Only the Defend mode, only when the alternate is on.
        inline bool ShowHoldLabel(bool alternateActive, bool shiftHeld, int mode)
        {
            return alternateActive && shiftHeld && mode == kModeDefend;
        }

        // ---- keys -------------------------------------------------------------

        enum class KeyId
        {
            RemoteTarget = 0, // Shift+key: cycle the target through the selection
            BuildingCycle,    // key: cycle the target through own buildings
            AreaSelect,       // key: 100 m, Shift+key: 200 m
            Hold,             // key: Hold the selection
            Count,
        };
        constexpr int kKeyCount = static_cast<int>(KeyId::Count);

        struct KeyDef
        {
            const char* iniKey;      // [Gameplay]
            const char* rowCommand;  // Options > Input > RTS Actions row id
            const char* displayText; // row label
            const char* defaultText;
            bool needsShift;         // only Shift+key is ours (plain key stays stock)
            bool shiftVariant;       // Shift+key is ours too (a variant of the action)
        };

        // Stock input.map/gamekey.map: T is frontal_target (no Shift
        // exclusion), Ctrl+B eject, X, Z and plain B unbound; F is pitch_down.
        inline const KeyDef& GetKeyDef(KeyId id)
        {
            static const KeyDef kDefs[kKeyCount] = {
                { "RtsRemoteTargetKey", "OpenShim:RtsRemoteTargetKey", "Target Selected Unit", "T", true, false },
                { "RtsBuildingCycleKey", "OpenShim:RtsBuildingCycleKey", "Target Next Building", "B", false, false },
                { "RtsAreaSelectKey", "OpenShim:RtsAreaSelectKey", "Select Same Type Nearby", "X", false, true },
                { "RtsHoldKey", "OpenShim:RtsHoldKey", "Hold Position", "Z", false, false },
            };
            const int index = static_cast<int>(id);
            return kDefs[index >= 0 && index < kKeyCount ? index : 0];
        }

        struct Key
        {
            unsigned vk = 0;
            bool extended = false;
            bool operator==(const Key& other) const { return vk == other.vk && extended == other.extended; }
        };

        // nullptr when `vk` may be an RTS key, else why not (the rally key's
        // reserved list: digits, F1-F10, Space, Tab, Alt, Enter, Esc).
        inline const char* ReservedKeyReason(unsigned vk)
        {
            if (vk >= 0x30 && vk <= 0x39)
                return "digits are the game's command-menu keys";
            if (vk >= 0x70 && vk <= 0x79)
                return "F1-F10 are the game's group keys";
            switch (vk)
            {
            case 0x20: return "Space is a game key";
            case 0x09: return "Tab is a game key";
            case 0x10: return "Shift is a modifier";
            case 0x11: return "Ctrl is a modifier";
            case 0x12: return "Alt is a modifier";
            case 0x0D: return "Enter is a game key";
            case 0x1B: return "Esc is a game key";
            default: return nullptr;
            }
        }

        // Parses and checks one RTS key against the keys already taken: the
        // other RTS keys (`others`, kKeyCount entries, the slot for `id` and
        // vk 0 ignored), the rally key and the two QuickSave chords. nullptr
        // and `out` filled on success, else the reason.
        inline const char* CheckKeyText(KeyId id, const char* text, const Key* others, const Key& rally,
                                        const QuickSaveKeyPolicy::Chord& quickSave,
                                        const QuickSaveKeyPolicy::Chord& quickLoad, Key& out)
        {
            QuickSaveKeyPolicy::Chord chord;
            if (!QuickSaveKeyPolicy::ParseChord(text, chord))
                return "not a recognised key (use e.g. X, Insert, PageUp)";
            if (chord.ctrl || chord.shift || chord.alt)
                return "must be a single key without Ctrl, Shift or Alt";
            if (const char* reason = ReservedKeyReason(chord.vk))
                return reason;
            const Key key{ chord.vk, chord.extended };
            if (key == rally)
                return "it is the Rally Point key";
            for (int i = 0; others && i < kKeyCount; ++i)
            {
                if (i != static_cast<int>(id) && others[i].vk != 0 && others[i] == key)
                    return "another RTS action uses it";
            }
            // The filter ignores Ctrl/Alt chords; a Shift-only QuickSave
            // chord on this key would be eaten when Shift+key is ours.
            const KeyDef& def = GetKeyDef(id);
            if (def.needsShift || def.shiftVariant)
            {
                const QuickSaveKeyPolicy::Chord* const quick[2] = { &quickSave, &quickLoad };
                for (const QuickSaveKeyPolicy::Chord* q : quick)
                {
                    if (q->vk == key.vk && q->extended == key.extended && q->shift && !q->ctrl && !q->alt)
                        return "Shift plus this key is a QuickSave chord";
                }
            }
            out = key;
            return nullptr;
        }

        // The RTS action whose key filter takes this chord in a mission, or
        // KeyId::Count. Mirrors ClassifyKey: Ctrl and Alt chords are never
        // ours; a needsShift action takes only Shift+key, a shiftVariant
        // action both, the others only the plain key. Used by the rally,
        // QuickSave and gamekey rebinding paths to refuse or warn.
        inline KeyId ActionTakingChord(const Key* keys, unsigned vk, bool extended, bool shift, bool ctrl, bool alt)
        {
            if (!keys || vk == 0 || ctrl || alt)
                return KeyId::Count;
            for (int i = 0; i < kKeyCount; ++i)
            {
                if (keys[i].vk != vk || keys[i].extended != extended)
                    continue;
                const KeyDef& def = GetKeyDef(static_cast<KeyId>(i));
                const bool taken = def.needsShift ? shift : (def.shiftVariant || !shift);
                if (taken)
                    return static_cast<KeyId>(i);
            }
            return KeyId::Count;
        }

        // The RTS action using this key at all (any Shift state), or
        // KeyId::Count: the rally key is one plain key whose Shift variant
        // clears, so it may share no RTS key.
        inline KeyId ActionUsingKey(const Key* keys, unsigned vk, bool extended)
        {
            for (int i = 0; keys && vk != 0 && i < kKeyCount; ++i)
            {
                if (keys[i].vk == vk && keys[i].extended == extended)
                    return static_cast<KeyId>(i);
            }
            return KeyId::Count;
        }

        // ---- key messages -----------------------------------------------------

        constexpr unsigned kWmKeyDown = 0x0100;
        constexpr unsigned kWmKeyUp = 0x0101;
        constexpr unsigned long long kLParamPreviousStateBit = 1ull << 30;

        struct KeyEvent
        {
            unsigned msg = 0;
            unsigned vk = 0;
            unsigned long long lParam = 0;
            bool extended = false;
            bool shift = false;
            bool ctrl = false;
            bool alt = false;
        };

        struct KeyDecision
        {
            bool swallow = false;
            bool act = false;
            bool shift = false; // the action's Shift variant
        };

        // Per key: was the last fresh keydown swallowed? Only then are its
        // autorepeats and keyup swallowed too.
        struct KeyLatch
        {
            bool downSwallowed = false;
        };

        // `gateOpen`: the action is on, the world is interactive, the editor
        // is off (and, for the remote target, an own unit is selected).
        // Ctrl+key and Alt+key are never ours.
        inline KeyDecision ClassifyKey(const KeyEvent& key, KeyId id, const Key& bound, bool gateOpen, KeyLatch& latch)
        {
            KeyDecision decision;
            if (bound.vk == 0 || key.vk != bound.vk || key.extended != bound.extended)
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
                decision.swallow = latch.downSwallowed;
                return decision;
            }
            const KeyDef& def = GetKeyDef(id);
            bool ours = gateOpen && !key.ctrl && !key.alt;
            if (def.needsShift)
                ours = ours && key.shift;
            else if (!def.shiftVariant)
                ours = ours && !key.shift;
            latch.downSwallowed = ours;
            if (!ours)
                return decision;
            decision.swallow = true;
            decision.act = true;
            decision.shift = key.shift;
            return decision;
        }

        // ---- Hold -------------------------------------------------------------

        // The rebindable Hold key and the Shift alternate apply the native
        // hold (SetAiHold), which is single player only: its table is not
        // saved and peers never learn of it (Docs/NATIVE_HOLD_DEFEND_FOLLOW.md).
        inline bool HoldAvailable(bool enabled, bool hooksInstalled, bool singlePlayer)
        {
            return enabled && hooksInstalled && singlePlayer;
        }

        // [Gameplay] RtsHold: 0 off, 1 the Hold key only, 2 the key and the
        // Shift alternate on the Defend entry (default).
        constexpr int kHoldOff = 0;
        constexpr int kHoldKeyOnly = 1;
        constexpr int kHoldKeyAndShiftMenu = 2;
        inline int ClampHoldMode(int value)
        {
            return value < kHoldOff ? kHoldOff : (value > kHoldKeyAndShiftMenu ? kHoldKeyAndShiftMenu : value);
        }

        // ---- Build at Nav ------------------------------------------------------

        // Mode 10 is Go To Nav (names table 0x008E7B00). Its submenu's nav
        // pick sends CMD_GO (3) to the selection (0x004A4A6D `push 3`).
        constexpr int kModeGoToNav = 10;
        constexpr int kCmdGo = 3;
        // ConstructionRig::GetCommand(VECTOR) 0x0049D230 returns CMD_DROPOFF
        // (8) for a spot it accepts and CMD_NO_DROPOFF (9) otherwise
        // (0x0049D4E2 / 0x0049D50B / 0x0049D533).
        constexpr int kCmdDropoff = 8;
        // CMD_BUILD: ConstructionRig::SetActiveMode FUN_0049d0e0 line 12.
        constexpr int kCmdBuild = 0x15;
        // Mode ids up to 0x1A are fixed entries; a larger one is the
        // GameObjectClass* of a building (FUN_0049d0e0 lines 12-13).
        constexpr uint32_t kLastFixedMode = 0x1A;
        // DistributedObject +0x68 == 2: a remote replica (FUN_004b9830).
        constexpr uint8_t kReplicaOwnership = 2;

        // What the engine side reads from one selected object.
        struct RigPick
        {
            bool isRig = false;   // vtable is ConstructionRig's
            bool ownTeam = false; // the player's team
            bool replica = true;  // +0x68 == kReplicaOwnership
            int32_t busy = 1;     // +0x228; GetCommand refuses unless 0
            ModeList modes;       // +0x1A4
            uint32_t dropClass = 0; // +0x370, written with the active mode
        };

        // The building class a rig has picked and not yet placed, or 0. The
        // stock hover test (FUN_0049d230 line 36): active mode above
        // 0x1A and +0x228 == 0. The drop class must equal that mode too, so
        // a stale +0x370 (never cleared on cancel) or a PRODMENU submenu
        // stub (SetActiveMode never sees one) does not count.
        inline uint32_t PickedBuildClass(const RigPick& rig)
        {
            if (!rig.isRig || !rig.ownTeam || rig.replica || rig.busy != 0)
                return 0;
            const uint32_t mode = static_cast<uint32_t>(ModeAt(rig.modes, rig.modes.active));
            if (mode <= kLastFixedMode || mode != rig.dropClass)
                return 0;
            return mode;
        }

        // The rig's picked entry is still enabled (the build menu greys out
        // what the team cannot afford).
        inline bool PickedSlotEnabled(const RigPick& rig)
        {
            return SlotEnabled(rig.modes, rig.modes.active);
        }

        // The Go To Nav entry reads "Build at Nav" while a selected rig has a
        // building picked.
        inline bool ShowBuildAtNavLabel(bool active, int mode, bool selectionHasPickedRig)
        {
            return active && mode == kModeGoToNav && selectionHasPickedRig;
        }

        enum class BuildAtNavVerdict
        {
            Build,
            NotAffordable, // the picked entry is disabled
            NoPosition,    // the nav's position could not be read
            BadSpot,       // GetCommand did not return CMD_DROPOFF
        };

        // `queried`: GetCommand ran without a fault and gave `result`.
        inline BuildAtNavVerdict DecideBuildAtNav(bool slotEnabled, bool havePosition, bool queried, int result)
        {
            if (!slotEnabled)
                return BuildAtNavVerdict::NotAffordable;
            if (!havePosition)
                return BuildAtNavVerdict::NoPosition;
            if (!queried || result != kCmdDropoff)
                return BuildAtNavVerdict::BadSpot;
            return BuildAtNavVerdict::Build;
        }

        inline const char* BuildAtNavVerdictName(BuildAtNavVerdict verdict)
        {
            switch (verdict)
            {
            case BuildAtNavVerdict::Build: return "build";
            case BuildAtNavVerdict::NotAffordable: return "entry disabled (cannot afford)";
            case BuildAtNavVerdict::NoPosition: return "nav position unreadable";
            case BuildAtNavVerdict::BadSpot: return "cannot build there";
            default: return "?";
            }
        }

        // The stock pick deselects after the order (SelectNone 0x004A6D50 at
        // 0x004A4A80). When every unit that would have been ordered was a
        // refused rig, nothing happened, so the selection stays and the
        // player can pick another nav.
        inline bool KeepSelectionAfterNavPick(int built, int stockOrdered, int refused)
        {
            return refused > 0 && built == 0 && stockOrdered == 0;
        }
    }
}
