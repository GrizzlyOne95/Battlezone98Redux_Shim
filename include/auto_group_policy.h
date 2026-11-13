#pragma once
// auto_group_policy.h
// Pure decision rules for [Gameplay] AutoGroupNewUnits. No Windows or engine
// calls, so tests/auto_group_policy_tests.cpp can exercise them directly. The
// engine side is src/patches/auto_group_new_units.cpp; the behaviour is
// documented in Docs/PRODUCER_RALLY_POINTS.md ("Auto-group new units").
//
// Ported from BZCC: SetBestGroup (004da8b0 lines 19-26) takes
// GroupPanel::FirstMatchGroup (005a4e03 lines 14-18), else
// GroupPanel::FirstEmptyGroup (005a4dd6 lines 14-16), else nothing. Stricter
// than BZCC, which compares only the first member: a group matches only when
// every live member has the new unit's ODF, so a mixed group the player
// built by hand is never touched.

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace AutoGroupPolicy
    {
        // ControlPanel groups (GOG 2.2.301): 10 groups of 0x16C bytes, so 91
        // handles each (FUN_004a6f00, ControlPanel save FUN_004a7440 writes
        // groupNum 0x28 bytes and groupList 0xE38 = 10 * 0x16C bytes).
        constexpr int kGroupCount = 10;
        constexpr int kGroupCapacity = 0x16C / 4;
        // Only groups 0-6 have a key: the stock input.map (GOG 2.2.301, lines
        // 159-194) binds group_select_0..group_select_6 to F1-F7, each with a
        // "- keyboard LeftShift" line, and nothing selects groups 7-9, so
        // auto-group never uses them.
        constexpr int kKeyedGroupCount = 7;
        static_assert(kKeyedGroupCount <= kGroupCount, "keyed groups are a prefix of the stored groups");
        // BZCC's member cap (FirstMatchGroup: count < 10).
        constexpr int kMaxLiveMembers = 10;
        // ODF names are at most 8 characters (GameObjectClass +0x30, char[8]).
        constexpr size_t kOdfBufferSize = 16;

        // What the engine side read from one group.
        struct GroupSummary
        {
            int storedCount = 0;         // groupNum[n], clamped to 0..kGroupCapacity
            int liveCount = 0;           // entries whose handle still resolves
            bool allLiveSameOdf = false; // liveCount > 0 and every live member has the unit's ODF
            bool containsUnit = false;   // the new unit's handle is already stored
        };

        // Walks one stored group. memberOdf(handle, out, outSize) returns
        // false when the handle no longer resolves (dead) and otherwise fills
        // `out` with the member's ODF name (empty when unreadable, which never
        // matches). Dead entries are not counted and not touched: stock
        // SelectGroup (FUN_004a6dd0 lines 14-24) skips them the same way, and
        // stock already removes a deleted object from every group
        // (FUN_004a0710 lines 27-37).
        template <typename MemberOdf>
        GroupSummary SummarizeGroup(const uint32_t* handles, int storedCount, uint32_t unitHandle,
                                    const char* unitOdf, MemberOdf&& memberOdf)
        {
            GroupSummary summary;
            if (storedCount < 0)
                storedCount = 0;
            if (storedCount > kGroupCapacity)
                storedCount = kGroupCapacity;
            summary.storedCount = storedCount;
            const bool unitOdfKnown = unitOdf && unitOdf[0] != '\0';
            bool allSame = true;
            for (int i = 0; i < storedCount; ++i)
            {
                const uint32_t handle = handles[i];
                if (handle == 0)
                    continue;
                if (unitHandle != 0 && handle == unitHandle)
                    summary.containsUnit = true;
                char odf[kOdfBufferSize] = {};
                if (!memberOdf(handle, odf, sizeof(odf)))
                    continue;
                odf[sizeof(odf) - 1] = '\0';
                ++summary.liveCount;
                if (!unitOdfKnown || odf[0] == '\0' || std::strcmp(odf, unitOdf) != 0)
                    allSame = false;
            }
            summary.allLiveSameOdf = summary.liveCount > 0 && allSame;
            return summary;
        }

        enum class ChoiceKind
        {
            Match,          // joins a group of its own ODF
            Empty,          // starts the first empty keyed group
            None,           // every keyed group is full, mixed or another ODF
            AlreadyGrouped, // the unit is in a group already: leave it
        };

        struct GroupChoice
        {
            ChoiceKind kind = ChoiceKind::None;
            int group = -1; // 0..kKeyedGroupCount-1 for Match and Empty
        };

        // A group is empty when nothing in it is alive. Either kind of target
        // needs a free stored slot, since entries are appended, never reused.
        // Membership is checked in all ten groups; only keyed ones are chosen.
        inline GroupChoice ChooseGroup(const GroupSummary (&groups)[kGroupCount])
        {
            GroupChoice choice;
            for (const GroupSummary& g : groups)
            {
                if (g.containsUnit)
                {
                    choice.kind = ChoiceKind::AlreadyGrouped;
                    return choice;
                }
            }
            for (int i = 0; i < kKeyedGroupCount; ++i)
            {
                const GroupSummary& g = groups[i];
                if (g.allLiveSameOdf && g.liveCount < kMaxLiveMembers && g.storedCount < kGroupCapacity)
                {
                    choice.kind = ChoiceKind::Match;
                    choice.group = i;
                    return choice;
                }
            }
            for (int i = 0; i < kKeyedGroupCount; ++i)
            {
                const GroupSummary& g = groups[i];
                if (g.liveCount == 0 && g.storedCount < kGroupCapacity)
                {
                    choice.kind = ChoiceKind::Empty;
                    choice.group = i;
                    return choice;
                }
            }
            return choice;
        }

        // The unit a Recycler or Factory has just finished.
        struct BuiltUnit
        {
            bool present = false;
            bool playerTeam = false;
            bool isScavenger = false;
            bool isConstructor = false;
            bool isPerson = false;
            bool isBuilding = false;
            bool canCommand = false;
            bool handleValid = false; // GetObj(GetHandle(unit)) == unit
            bool odfKnown = false;    // its ODF name could be read
        };

        enum class BuiltUnitVerdict
        {
            Group,
            NoUnit,
            OtherTeam,
            Scavenger,
            Constructor,
            Pilot,
            Building,
            NotCommandable,
            NoHandle,
            NoOdf,
        };

        inline BuiltUnitVerdict ClassifyBuiltUnit(const BuiltUnit& unit)
        {
            if (!unit.present)
                return BuiltUnitVerdict::NoUnit;
            if (!unit.playerTeam)
                return BuiltUnitVerdict::OtherTeam;
            if (unit.isScavenger)
                return BuiltUnitVerdict::Scavenger;
            if (unit.isConstructor)
                return BuiltUnitVerdict::Constructor;
            if (unit.isPerson)
                return BuiltUnitVerdict::Pilot;
            if (unit.isBuilding)
                return BuiltUnitVerdict::Building;
            if (!unit.canCommand)
                return BuiltUnitVerdict::NotCommandable;
            if (!unit.handleValid)
                return BuiltUnitVerdict::NoHandle;
            if (!unit.odfKnown)
                return BuiltUnitVerdict::NoOdf;
            return BuiltUnitVerdict::Group;
        }

        inline const char* DescribeVerdict(BuiltUnitVerdict verdict)
        {
            switch (verdict)
            {
            case BuiltUnitVerdict::Group: return "group";
            case BuiltUnitVerdict::NoUnit: return "no unit";
            case BuiltUnitVerdict::OtherTeam: return "not the player's team";
            case BuiltUnitVerdict::Scavenger: return "scavenger";
            case BuiltUnitVerdict::Constructor: return "constructor";
            case BuiltUnitVerdict::Pilot: return "pilot";
            case BuiltUnitVerdict::Building: return "building";
            case BuiltUnitVerdict::NotCommandable: return "not commandable";
            case BuiltUnitVerdict::NoHandle: return "no handle";
            case BuiltUnitVerdict::NoOdf: return "ODF name unreadable";
            }
            return "?";
        }
    }
}
