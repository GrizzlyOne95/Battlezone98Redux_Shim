#include "offense_overflow_policy.h"

#include <cstdio>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::OffenseOverflowPolicy;

namespace
{
    void TestBuildGate()
    {
        Check(BuildGateOpens(-1, 5, 14, true, true, true), "full offense slots, room in a group: opens");
        Check(!BuildGateOpens(7, 5, 14, true, true, true), "stock found a slot: stock result stands");
        Check(!BuildGateOpens(-1, 15, 24, true, true, true), "defense range never opens");
        Check(!BuildGateOpens(-1, 5, 13, true, true, true), "only the exact offense range");
        Check(!BuildGateOpens(-1, 5, 14, false, true, true), "feature off: stock");
        Check(!BuildGateOpens(-1, 5, 14, true, false, true), "AI team producers: stock");
        Check(!BuildGateOpens(-1, 5, 14, true, true, false), "no group for this ODF: stock");
    }

    void TestTeamHasFreeSlot()
    {
        Check(TeamHasFreeSlotOverride(true, false, false, false, false), "stock true stays true");
        Check(TeamHasFreeSlotOverride(false, true, true, true, true), "grouped user craft: true");
        Check(!TeamHasFreeSlotOverride(false, false, true, true, true), "feature off: stock false");
        Check(!TeamHasFreeSlotOverride(false, true, false, true, true), "other team: stock false");
        Check(!TeamHasFreeSlotOverride(false, true, true, false, true), "not a user craft: stock false");
        Check(!TeamHasFreeSlotOverride(false, true, true, true, false), "ungrouped: stock false");
    }

    void TestSameHandleSet()
    {
        const uint32_t a[] = { 1, 2, 3 };
        const uint32_t b[] = { 3, 1, 2 };
        const uint32_t c[] = { 1, 2 };
        const uint32_t d[] = { 1, 2, 0, 2 };
        Check(SameHandleSet(a, 3, b, 3), "order ignored");
        Check(!SameHandleSet(a, 3, c, 2), "a missing member differs");
        Check(!SameHandleSet(c, 2, a, 3), "an extra member differs");
        Check(SameHandleSet(c, 2, d, 4), "zeros and repeats ignored");
        Check(!SameHandleSet(a, 0, b, 0), "two empty lists never match");
        const uint32_t zeros[] = { 0, 0 };
        Check(!SameHandleSet(zeros, 2, zeros, 2), "all-zero lists never match");
    }

    MemberFrameInput Base()
    {
        MemberFrameInput in;
        in.active = true;
        return in;
    }

    void TestMemberFrame()
    {
        MemberFrameInput in = Base();
        Check(DecideMemberFrame(in).action == MemberAction::None, "idle: stock");

        in.pressedGroup = 2;
        in.selectionIsGroup = true;
        in.selectNum = 4;
        MemberFrame f = DecideMemberFrame(in);
        Check(f.action == MemberAction::Enter && f.group == 2, "second press of a selected group opens its list");

        in.cmdMulti = true;
        Check(DecideMemberFrame(in).action == MemberAction::None, "Ctrl+F binds the group (stock)");
        in.cmdMulti = false;
        in.selectionIsGroup = false;
        Check(DecideMemberFrame(in).action == MemberAction::None, "first press selects the group (stock)");
        in.selectionIsGroup = true;
        in.pressedGroup = 7;
        Check(DecideMemberFrame(in).action == MemberAction::None, "unkeyed groups never open a list");

        in = Base();
        in.memberGroup = 1;
        in.currentItem = 0;
        in.memberLiveCount = 3;
        f = DecideMemberFrame(in);
        Check(f.action == MemberAction::Show && f.group == 1, "open list keeps showing");

        in.selectNum = 2;
        in.cmdMulti = true;
        Check(DecideMemberFrame(in).action == MemberAction::Show, "Ctrl+number adds and the list stays");
        in.cmdMulti = false;
        Check(DecideMemberFrame(in).action == MemberAction::Exit, "a selection without Ctrl shows the command menu");

        in = Base();
        in.memberGroup = 1;
        in.currentItem = -1;
        in.memberLiveCount = 3;
        Check(DecideMemberFrame(in).action == MemberAction::Exit, "SelectOne reset currentItem: closed");
        in.currentItem = 0;
        in.memberLiveCount = 0;
        Check(DecideMemberFrame(in).action == MemberAction::Exit, "every member died: closed");
        in.memberLiveCount = 3;
        in.pressedGroup = 4;
        Check(DecideMemberFrame(in).action == MemberAction::Exit, "another F-key: closed, stock runs it");
        in.pressedGroup = 1;
        in.selectionIsGroup = true;
        f = DecideMemberFrame(in);
        Check(f.action == MemberAction::Enter && f.group == 1, "pressing a matching key while open re-enters");

        in = Base();
        in.active = false;
        in.memberGroup = 3;
        Check(DecideMemberFrame(in).action == MemberAction::Exit, "feature off closes an open list");
        in.memberGroup = -1;
        in.pressedGroup = 0;
        in.selectionIsGroup = true;
        Check(DecideMemberFrame(in).action == MemberAction::None, "feature off never opens");
    }

    void TestSlots()
    {
        int objs[12] = {};
        void* members[12] = {};
        for (int i = 0; i < 12; ++i)
            members[i] = &objs[i];
        members[1] = nullptr;
        void* slots[kOffenseSlotCount] = {};
        Check(FillMemberSlots(members, 12, slots) == 10, "ten slots filled from twelve members");
        Check(slots[0] == &objs[0] && slots[1] == &objs[2] && slots[9] == &objs[10], "nulls skipped, order kept");
        Check(FillMemberSlots(members, 3, slots) == 2 && slots[2] == nullptr && slots[9] == nullptr,
              "short lists pad with null");

        int a = 0, b = 0, c = 0;
        void* saved[kOffenseSlotCount] = { &a, nullptr, &b };
        void* injected[kOffenseSlotCount] = { &c, &c, nullptr };
        void* team[kOffenseSlotCount] = { &c, &a, nullptr };
        const int kept = RestoreSlots(team, saved, injected);
        Check(kept == 1, "one slot changed during the render is kept");
        Check(team[0] == &a && team[1] == &a && team[2] == &b, "injected slots restored, the changed one kept");
    }

    void TestAppendUnique()
    {
        uint32_t list[4] = { 5, 6 };
        int n = 2;
        n = AppendUnique(list, n, 4, 6);
        Check(n == 2, "duplicate skipped");
        n = AppendUnique(list, n, 4, 0);
        Check(n == 2, "zero handle skipped");
        n = AppendUnique(list, n, 4, 7);
        n = AppendUnique(list, n, 4, 8);
        Check(n == 4 && list[3] == 8, "appended up to capacity");
        n = AppendUnique(list, n, 4, 9);
        Check(n == 4, "capacity caps the list");
    }

    void TestRelabel()
    {
        Check(ShouldRelabelCategory(true, true, 0, -1, 0), "Ctrl, nothing selected, category menu: Offense");
        Check(ShouldRelabelCategory(true, true, 0, -1, 2), "Utility too");
        Check(!ShouldRelabelCategory(true, true, 0, -1, 3), "Nav Beacons keeps its label");
        Check(!ShouldRelabelCategory(true, true, 0, -1, 4), "single-slot items keep theirs");
        Check(!ShouldRelabelCategory(true, false, 0, -1, 0), "no Ctrl: stock");
        Check(!ShouldRelabelCategory(true, true, 1, -1, 0), "a selection: stock");
        Check(!ShouldRelabelCategory(true, true, 0, 0, 0), "inside a unit list: stock");
        Check(!ShouldRelabelCategory(false, true, 0, -1, 0), "feature off: stock");
    }
}

int main()
{
    TestBuildGate();
    TestTeamHasFreeSlot();
    TestSameHandleSet();
    TestMemberFrame();
    TestSlots();
    TestAppendUnique();
    TestRelabel();
    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "offense_overflow_policy_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("offense_overflow_policy_tests: all checks passed\n");
    return 0;
}
