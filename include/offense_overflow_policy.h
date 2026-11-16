#pragma once
// offense_overflow_policy.h
// Pure rules for [Gameplay] ExtendedUnitCap (more than 10 offensive units,
// the extras kept in F1-F7 groups) and [Gameplay] GroupMemberMenu (a second
// F-key press lists that group's members in the stock unit list). No Windows
// or engine calls, so tests/offense_overflow_policy_tests.cpp runs them
// directly. The engine side is src/patches/offense_overflow.cpp; behaviour and
// evidence are in Docs/PRODUCER_RALLY_POINTS.md ("Extended unit cap" and
// "Group member list").

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
    namespace OffenseOverflowPolicy
    {
        // MENU_ITEM[0] "Offense" covers team slots 5-14 (table 0x008E7990,
        // ControlPanelMenuItems row); a class's slot range is
        // GameObjectClass +0x13C/+0x140 (FUN_005ae660 line 69,
        // FUN_00464140 lines 15-18).
        constexpr int kOffenseMinSlot = 5;
        constexpr int kOffenseMaxSlot = 14;
        constexpr int kOffenseSlotCount = kOffenseMaxSlot - kOffenseMinSlot + 1;
        constexpr int kOffenseItem = 0;
        // ControlPanel selectList holds 91 handles (+0x1C up to selectNum at
        // +0x188, 0x16C bytes).
        constexpr int kSelectCapacity = 0x16C / 4;
        constexpr int kKeyedGroupCount = 7;

        // ---- part 1: the build gate (Producer::UpdateModeList) -------------

        // Stock enables a build entry only when FirstEmptySlot(team, min, max)
        // finds a slot (FUN_005ae660 line 74). Opened only for the user's
        // offense classes, and only when auto-group has a keyed group for it.
        inline bool BuildGateOpens(int stockResult, int minSlot, int maxSlot, bool active, bool userTeam,
                                   bool canPlace)
        {
            return stockResult == -1 && minSlot == kOffenseMinSlot && maxSlot == kOffenseMaxSlot && active &&
                   userTeam && canPlace;
        }

        // ---- part 3: TeamHasFreeSlot -----------------------------------------

        // A grouped overflow craft of the user's team counts as having a slot.
        inline bool TeamHasFreeSlotOverride(bool stockResult, bool active, bool userTeam, bool craftOnUserTeam,
                                            bool inAnyGroup)
        {
            return stockResult || (active && userTeam && craftOnUserTeam && inAnyGroup);
        }

        // ---- part 4: the member list -----------------------------------------

        // True when both lists name the same handles (order and repeats
        // ignored). Zero handles are skipped; two empty lists are not equal
        // (an empty selection never "matches" a group).
        inline bool SameHandleSet(const uint32_t* a, int na, const uint32_t* b, int nb)
        {
            auto contains = [](const uint32_t* list, int n, uint32_t h) {
                for (int i = 0; i < n; ++i)
                    if (list[i] == h)
                        return true;
                return false;
            };
            bool any = false;
            for (int i = 0; i < na; ++i)
            {
                if (a[i] == 0)
                    continue;
                any = true;
                if (!contains(b, nb, a[i]))
                    return false;
            }
            for (int i = 0; i < nb; ++i)
                if (b[i] != 0 && !contains(a, na, b[i]))
                    return false;
            return any;
        }

        // What the engine read at the start of one ControlPanel render.
        struct MemberFrameInput
        {
            bool active = false;           // GroupMemberMenu on, bound, single player
            int memberGroup = -1;          // the open member list, -1 none
            int currentItem = -1;          // ControlPanel +0x117C
            int selectNum = 0;             // ControlPanel +0x188
            bool cmdMulti = false;         // cmd_multi (0x00919875)
            int pressedGroup = -1;         // first group_select byte set (0..9), -1 none
            bool selectionIsGroup = false; // selection == pressedGroup's live members, non-empty
            int memberLiveCount = 0;       // live, commandable members of memberGroup
        };

        enum class MemberAction
        {
            None,  // stock frame
            Enter, // consume the press, SelectNone, currentItem = 0, then Show
            Show,  // the open list: swap the members into team slots 5-14
            Exit,  // close the list, stock frame
        };

        struct MemberFrame
        {
            MemberAction action = MemberAction::None;
            int group = -1;
        };

        // The F-key loop (FUN_004a08e0 lines 528-540) runs the first set
        // group_select byte: SelectGroup without cmd_multi, BindGroup with it.
        // A second press of a keyed group whose members are exactly the
        // selection opens the list instead. The list stays open while the
        // unit list would draw item 0: currentItem 0 and either nothing
        // selected or cmd_multi held (else the command menu draws, line 1313).
        inline MemberFrame DecideMemberFrame(const MemberFrameInput& in)
        {
            MemberFrame out;
            if (!in.active)
            {
                if (in.memberGroup >= 0)
                    out.action = MemberAction::Exit;
                return out;
            }
            if (in.pressedGroup >= 0 && in.pressedGroup < kKeyedGroupCount && !in.cmdMulti && in.selectionIsGroup)
            {
                out.action = MemberAction::Enter;
                out.group = in.pressedGroup;
                return out;
            }
            if (in.memberGroup < 0)
                return out;
            const bool commandMenu = in.selectNum > 0 && !in.cmdMulti;
            if (in.memberGroup >= kKeyedGroupCount || in.currentItem != kOffenseItem || in.pressedGroup >= 0 ||
                commandMenu || in.memberLiveCount <= 0)
            {
                out.action = MemberAction::Exit;
                return out;
            }
            out.action = MemberAction::Show;
            out.group = in.memberGroup;
            return out;
        }

        // Writes the first kOffenseSlotCount members into `slots` and pads
        // with null. Returns how many were written.
        inline int FillMemberSlots(void* const* members, int count, void* (&slots)[kOffenseSlotCount])
        {
            int n = 0;
            for (int i = 0; i < count && n < kOffenseSlotCount; ++i)
                if (members[i])
                    slots[n++] = members[i];
            for (int i = n; i < kOffenseSlotCount; ++i)
                slots[i] = nullptr;
            return n;
        }

        // Puts the saved team slots back. A slot is restored only while it
        // still holds what was injected; anything else was written by the
        // engine during the render and is kept. Returns the number of slots
        // left alone that way.
        inline int RestoreSlots(void** team, void* const (&saved)[kOffenseSlotCount],
                                void* const (&injected)[kOffenseSlotCount])
        {
            int kept = 0;
            for (int i = 0; i < kOffenseSlotCount; ++i)
            {
                if (team[i] == injected[i])
                    team[i] = saved[i];
                else
                    ++kept;
            }
            return kept;
        }

        // ---- part 5: Ctrl+offense selects grouped overflow units too ---------

        // Appends `handle` to list[0..count) unless it is zero, already there
        // or the list is at `capacity`. Returns the new count.
        inline int AppendUnique(uint32_t* list, int count, int capacity, uint32_t handle)
        {
            if (handle == 0 || count < 0 || count >= capacity)
                return count;
            for (int i = 0; i < count; ++i)
                if (list[i] == handle)
                    return count;
            list[count] = handle;
            return count + 1;
        }

        // ---- part 6: the Ctrl category labels --------------------------------

        // With cmd_multi held, nothing selected and the category menu up
        // (currentItem -1), a category key runs SelectType (FUN_004a08e0
        // line 1551), so Offense, Defense and Utility read "All ...". Nav
        // Beacons (item 3) has its own menu and keeps its label.
        inline bool ShouldRelabelCategory(bool active, bool cmdMulti, int selectNum, int currentItem, int item)
        {
            return active && cmdMulti && selectNum == 0 && currentItem == -1 && item >= 0 && item <= 2;
        }
    }
}
