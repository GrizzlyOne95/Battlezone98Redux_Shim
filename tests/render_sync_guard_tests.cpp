#include "render_sync_guard_policy.h"

#include "test_check.h"

namespace
{
    using namespace BZROpenShim::RenderSyncGuard;

    Observed Live()
    {
        Observed o;
        o.readOk = true;
        o.node = 0x1000;
        o.entity = 0x2000;
        o.nodeLive = true;
        o.entityLive = true;
        return o;
    }

    void TestLiveObjectsCallStock()
    {
        CHECK(Decide(Live()) == Verdict::CallStock);
    }

    void TestNullNodeCallsStock()
    {
        // Stock does nothing, or lazily builds a fresh entity and node.
        Observed o = Live();
        o.node = 0;
        o.nodeLive = false;
        o.entity = 0;
        o.entityLive = false;
        CHECK(Decide(o) == Verdict::CallStock);
        o.entity = 0xDEAD; // stale entity with no node is never called by stock
        CHECK(Decide(o) == Verdict::CallStock);
    }

    void TestDeadEntitySkips()
    {
        Observed o = Live();
        o.entityLive = false;
        CHECK(Decide(o) == Verdict::SkipDeadEntity);
    }

    void TestNullEntitySkips()
    {
        Observed o = Live();
        o.entity = 0;
        o.entityLive = false;
        CHECK(Decide(o) == Verdict::SkipNullEntity);
    }

    void TestDeadNodeSkipsBeforeEntity()
    {
        Observed o = Live();
        o.nodeLive = false;
        o.entityLive = false;
        CHECK(Decide(o) == Verdict::SkipDeadNode);
    }

    void TestUnreadableSkips()
    {
        Observed o = Live();
        o.readOk = false;
        CHECK(Decide(o) == Verdict::SkipUnreadable);
    }

    void TestSeenSetLogsOncePerPointer()
    {
        SeenSet<2> seen;
        CHECK(seen.FirstTime(0x10));
        CHECK(!seen.FirstTime(0x10));
        CHECK(seen.FirstTime(0x20));
        CHECK(!seen.FirstTime(0x30)); // full: stops logging
        CHECK(!seen.FirstTime(0x20));
    }

    void TestVerdictNames()
    {
        CHECK(VerdictName(Verdict::SkipDeadEntity)[0] == 'd');
        CHECK(VerdictName(Verdict::CallStock)[0] == 'c');
    }
}

int main()
{
    TestLiveObjectsCallStock();
    TestNullNodeCallsStock();
    TestDeadEntitySkips();
    TestNullEntitySkips();
    TestDeadNodeSkipsBeforeEntity();
    TestUnreadableSkips();
    TestSeenSetLogsOncePerPointer();
    TestVerdictNames();
    return OpenShimTest::ExitCode();
}
