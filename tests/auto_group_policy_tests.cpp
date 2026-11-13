#include "auto_group_policy.h"

#include <cstdio>
#include <cstring>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::AutoGroupPolicy;

namespace
{
    // A fake world. Handles >= 0x900 are dead; below 0x100 is an "avtank",
    // 0x100-0x1FF an "avfigh", 0x200-0x2FF a live object whose ODF cannot be
    // read, anything else live "avscav".
    bool FakeOdf(uint32_t handle, char* out, size_t outSize)
    {
        if (handle == 0 || handle >= 0x900)
            return false;
        const char* name = handle < 0x100 ? "avtank" : handle < 0x200 ? "avfigh" : handle < 0x300 ? "" : "avscav";
        size_t i = 0;
        for (; name[i] != '\0' && i + 1 < outSize; ++i)
            out[i] = name[i];
        out[i] = '\0';
        return true;
    }

    GroupSummary Summ(const uint32_t* handles, int count, const char* unitOdf = "avtank", uint32_t unit = 0x7F)
    {
        return SummarizeGroup(handles, count, unit, unitOdf, FakeOdf);
    }

    GroupSummary Same(int live)
    {
        GroupSummary g;
        g.storedCount = live;
        g.liveCount = live;
        g.allLiveSameOdf = live > 0;
        return g;
    }

    GroupSummary Other(int live)
    {
        GroupSummary g = Same(live);
        g.allLiveSameOdf = false;
        return g;
    }

    void TestSummarize()
    {
        const uint32_t same[] = { 0x10, 0x11, 0x12 };
        GroupSummary s = Summ(same, 3);
        Check(s.liveCount == 3 && s.allLiveSameOdf && !s.containsUnit, "an all-same group matches");

        const uint32_t mixed[] = { 0x10, 0x110, 0x11 };
        s = Summ(mixed, 3);
        Check(s.liveCount == 3 && !s.allLiveSameOdf, "a mixed group never matches, even with the same first member");

        const uint32_t deadFirst[] = { 0x901, 0x10, 0x902, 0x11, 0 };
        s = Summ(deadFirst, 5);
        Check(s.storedCount == 5 && s.liveCount == 2, "dead and zero handles are not counted");
        Check(s.allLiveSameOdf, "dead members do not break the ODF match");

        const uint32_t deadOtherOdf[] = { 0x10, 0x9FF };
        s = Summ(deadOtherOdf, 2);
        Check(s.allLiveSameOdf, "a dead handle is ignored whatever it used to be");

        const uint32_t unreadable[] = { 0x10, 0x210 };
        s = Summ(unreadable, 2);
        Check(s.liveCount == 2 && !s.allLiveSameOdf, "a live member with an unreadable ODF is a mismatch");

        s = Summ(same, 3, "");
        Check(!s.allLiveSameOdf, "an unknown unit ODF matches nothing");

        const uint32_t dead[] = { 0x901, 0x902 };
        s = Summ(dead, 2);
        Check(s.liveCount == 0 && !s.allLiveSameOdf && s.storedCount == 2, "an all-dead group has no live members");

        const uint32_t withUnit[] = { 0x10, 0x7F };
        s = Summ(withUnit, 2);
        Check(s.containsUnit, "the unit's handle is found");

        s = Summ(same, -3);
        Check(s.storedCount == 0 && s.liveCount == 0, "a negative count reads as empty");

        uint32_t many[kGroupCapacity + 5] = {};
        for (uint32_t& h : many)
            h = 0x10;
        s = Summ(many, kGroupCapacity + 5);
        Check(s.storedCount == kGroupCapacity && s.liveCount == kGroupCapacity, "count clamped to the 91-entry capacity");
        Check(kGroupCapacity == 91, "0x16C bytes per group is 91 handles");
        Check(kKeyedGroupCount == 7, "input.map keys groups 0-6 only");
    }

    void TestChoose()
    {
        GroupSummary groups[kGroupCount] = {};
        GroupChoice c = ChooseGroup(groups);
        Check(c.kind == ChoiceKind::Empty && c.group == 0, "no groups: first empty group");

        groups[0] = Other(3);
        groups[1] = Same(2);
        groups[2] = Same(1);
        c = ChooseGroup(groups);
        Check(c.kind == ChoiceKind::Match && c.group == 1, "an all-same group under 10 is chosen, the first one");

        groups[1] = Other(2);
        c = ChooseGroup(groups);
        Check(c.kind == ChoiceKind::Match && c.group == 2, "a mixed group is skipped");

        groups[1] = Same(kMaxLiveMembers);
        groups[2] = Same(kMaxLiveMembers - 1);
        c = ChooseGroup(groups);
        Check(c.kind == ChoiceKind::Match && c.group == 2, "an all-same group at 10 is skipped; 9 still has room");

        groups[2] = Same(kMaxLiveMembers);
        c = ChooseGroup(groups);
        Check(c.kind == ChoiceKind::Empty && c.group == 3, "all matches full: first empty group");

        // Dead entries do not count against the cap...
        groups[1].storedCount = 14;
        groups[1].liveCount = 4;
        c = ChooseGroup(groups);
        Check(c.kind == ChoiceKind::Match && c.group == 1, "dead entries are not members");

        // ...but the stored list must have a free slot to append to.
        groups[1].storedCount = kGroupCapacity;
        c = ChooseGroup(groups);
        Check(c.kind == ChoiceKind::Empty && c.group == 3, "a group with no stored slot left is skipped");

        // A group whose members all died counts as empty.
        GroupSummary dead[kGroupCount] = {};
        for (GroupSummary& g : dead)
            g = Other(kMaxLiveMembers);
        dead[5].liveCount = 0;
        dead[5].allLiveSameOdf = false;
        dead[5].storedCount = 3;
        c = ChooseGroup(dead);
        Check(c.kind == ChoiceKind::Empty && c.group == 5, "a group of only dead handles counts as empty");
        dead[5].storedCount = kGroupCapacity;
        c = ChooseGroup(dead);
        Check(c.kind == ChoiceKind::None && c.group == -1, "an all-dead group with no free slot is not usable");

        // Groups 7-9 have no key: never chosen, even when empty or matching.
        GroupSummary keyed[kGroupCount] = {};
        for (int i = 0; i < kKeyedGroupCount; ++i)
            keyed[i] = Other(3);
        keyed[7] = Same(1);
        c = ChooseGroup(keyed);
        Check(c.kind == ChoiceKind::None && c.group == -1, "groups 7-9 are never chosen, empty or matching");
        keyed[6] = GroupSummary{};
        c = ChooseGroup(keyed);
        Check(c.kind == ChoiceKind::Empty && c.group == 6, "group 6 is the last keyed group");

        // Membership counts in every group, keyed or not.
        keyed[8].containsUnit = true;
        c = ChooseGroup(keyed);
        Check(c.kind == ChoiceKind::AlreadyGrouped, "a unit in an unkeyed group is left alone");

        GroupSummary one[kGroupCount] = {};
        one[0] = Same(1);
        one[0].containsUnit = true;
        c = ChooseGroup(one);
        Check(c.kind == ChoiceKind::AlreadyGrouped, "already grouped beats a match");

        // End to end through SummarizeGroup.
        GroupSummary real[kGroupCount] = {};
        const uint32_t mixed[] = { 0x10, 0x110 };
        const uint32_t tanks[] = { 0x11, 0x12, 0x903 };
        real[0] = Summ(mixed, 2);
        real[1] = Summ(tanks, 3);
        c = ChooseGroup(real);
        Check(c.kind == ChoiceKind::Match && c.group == 1, "summaries: mixed group 0 skipped, tank group 1 joined");
    }

    BuiltUnit Eligible()
    {
        BuiltUnit u;
        u.present = true;
        u.playerTeam = true;
        u.canCommand = true;
        u.handleValid = true;
        u.odfKnown = true;
        return u;
    }

    void TestBuiltUnit()
    {
        Check(ClassifyBuiltUnit(Eligible()) == BuiltUnitVerdict::Group, "a commandable player tank is grouped");
        Check(ClassifyBuiltUnit(BuiltUnit{}) == BuiltUnitVerdict::NoUnit, "no unit");
        BuiltUnit u = Eligible();
        u.playerTeam = false;
        Check(ClassifyBuiltUnit(u) == BuiltUnitVerdict::OtherTeam, "other team skipped");
        u = Eligible();
        u.isScavenger = true;
        Check(ClassifyBuiltUnit(u) == BuiltUnitVerdict::Scavenger, "scavenger skipped");
        u = Eligible();
        u.isConstructor = true;
        Check(ClassifyBuiltUnit(u) == BuiltUnitVerdict::Constructor, "constructor skipped");
        u = Eligible();
        u.isPerson = true;
        Check(ClassifyBuiltUnit(u) == BuiltUnitVerdict::Pilot, "pilot skipped");
        u = Eligible();
        u.isBuilding = true;
        Check(ClassifyBuiltUnit(u) == BuiltUnitVerdict::Building, "building skipped");
        u = Eligible();
        u.canCommand = false;
        Check(ClassifyBuiltUnit(u) == BuiltUnitVerdict::NotCommandable, "not commandable skipped");
        u = Eligible();
        u.handleValid = false;
        Check(ClassifyBuiltUnit(u) == BuiltUnitVerdict::NoHandle, "no handle skipped");
        u = Eligible();
        u.odfKnown = false;
        Check(ClassifyBuiltUnit(u) == BuiltUnitVerdict::NoOdf, "unreadable ODF skipped");
        for (int v = 0; v <= static_cast<int>(BuiltUnitVerdict::NoOdf); ++v)
            Check(DescribeVerdict(static_cast<BuiltUnitVerdict>(v))[0] != '?', "every verdict has a description");
    }
}

int main()
{
    TestSummarize();
    TestChoose();
    TestBuiltUnit();
    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "auto_group_policy_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("auto_group_policy_tests: all checks passed\n");
    return 0;
}
