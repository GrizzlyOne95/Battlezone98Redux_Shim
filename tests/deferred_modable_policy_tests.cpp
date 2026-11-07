#include "deferred_modable_policy.h"

#include <cstdio>

#include "test_check.h"

namespace
{
    using namespace BZROpenShim::DeferredModablePolicy;

    // Mirrors the store hook: record the mode being replaced, then the gate.
    GateResult Shell(State& s, int before, int target)
    {
        s.storeTarget = target;
        s.storeBefore = before;
        return DecideShellGate(s, target);
    }

    void TestShellRules()
    {
        State s;
        s.held = kModeMain;
        GateResult r = Shell(s, kModeMain, kModeIa);
        CHECK(r.skip && r.reason == GateReason::ShellDeferred && s.pending);
        r = Shell(s, kModeIa, kModeMain);
        CHECK(r.skip && r.reason == GateReason::ShellSkipped && !s.pending);

        // Unpaired store/gate: unknown before, stock rebuild.
        State u;
        u.held = kModeMain;
        r = DecideShellGate(u, kModeIa);
        CHECK(!r.skip && u.held == kModeIa);

        // Coming back from mission content without a deferred enter rebuilds.
        State m;
        m.held = kModeMain;
        r = Shell(m, kModeMission, kModeList);
        CHECK(!r.skip && m.held == kModeList && !m.pending);
    }

    void TestCampaignEnterDefersOutsideTheMount()
    {
        State s;
        s.held = kModeMain;
        GateResult r = DecideCampaignGate(s);
        CHECK(r.skip && r.reason == GateReason::CampaignEnter);
        CHECK(s.pendingMission && s.held == kModeMain);
    }

    void TestCampaignBackSkipsWhenEnterWasDeferred()
    {
        State s;
        s.held = kModeMain;
        s.pending = true;  // main -> list had deferred
        DecideCampaignGate(s);
        GateResult r = Shell(s, kModeMission, kModeList);
        CHECK(r.skip && r.reason == GateReason::CampaignBack);
        CHECK(!s.pendingMission && s.held == kModeMain && s.pending);
        r = Shell(s, kModeList, kModeMain);
        CHECK(r.skip && !s.pending);
    }

    void TestCampaignBackRebuildsWhenGroupIsNotMain()
    {
        State s;
        s.held = kModeIa;
        DecideCampaignGate(s);
        GateResult r = Shell(s, kModeMission, kModeList);
        CHECK(!r.skip && !s.pendingMission && s.held == kModeList);
    }

    void TestMountForcesTheDeferredRebuildBeforeRunning()
    {
        State s;
        s.held = kModeMain;
        s.pending = true;
        DecideCampaignGate(s);
        CHECK(BeginMissionMount(s));  // rebuild now, before the mount runs
        CHECK(!s.pendingMission && s.inMissionMount && s.held == kModeMission && !s.pending);
        FinishMissionMount(s);
        CHECK(!s.inMissionMount && !s.pending);  // Flush is then a no-op
    }

    void TestMountPathChangeRebuildsAgainAsStock()
    {
        State s;
        s.held = kModeMain;
        DecideCampaignGate(s);
        CHECK(BeginMissionMount(s));
        GateResult r = DecideCampaignGate(s);  // different path inside the mount
        CHECK(!r.skip && s.held == kModeMission && !s.pendingMission);
        FinishMissionMount(s);
    }

    void TestMountWithoutDeferredEnterIsUnchanged()
    {
        State s;
        s.held = kModeMain;
        s.pending = true;
        CHECK(!BeginMissionMount(s));
        FinishMissionMount(s);
        CHECK(s.pending && s.held == kModeMain);  // Flush decides, as before
    }

    void TestMissionRestartDoesNotRebuildTwice()
    {
        State s;
        s.held = kModeMission;
        CHECK(!BeginMissionMount(s));
        FinishMissionMount(s);
        CHECK(s.held == kModeMission && !s.pending);
    }

    void TestBackThenEnterAnotherCampaign()
    {
        State s;
        s.held = kModeMain;
        DecideCampaignGate(s);
        Shell(s, kModeMission, kModeList);
        DecideCampaignGate(s);
        CHECK(s.pendingMission && s.held == kModeMain);
        CHECK(BeginMissionMount(s));
    }

    void TestUnpairedShellGateClearsDeferredEnter()
    {
        State s;
        s.held = kModeMain;
        DecideCampaignGate(s);
        GateResult r = DecideShellGate(s, kModeList);  // no store seen
        CHECK(!r.skip && !s.pendingMission && s.held == kModeList);
        CHECK(!BeginMissionMount(s));
    }

    void TestBackWithGroupNotMainClearsDeferredEnter()
    {
        State s;
        s.held = kModeIa;
        DecideCampaignGate(s);
        Shell(s, kModeMission, kModeList);
        CHECK(!s.pendingMission);
        CHECK(!BeginMissionMount(s));
    }
}

int main()
{
    TestShellRules();
    TestCampaignEnterDefersOutsideTheMount();
    TestCampaignBackSkipsWhenEnterWasDeferred();
    TestCampaignBackRebuildsWhenGroupIsNotMain();
    TestMountForcesTheDeferredRebuildBeforeRunning();
    TestMountPathChangeRebuildsAgainAsStock();
    TestMountWithoutDeferredEnterIsUnchanged();
    TestMissionRestartDoesNotRebuildTwice();
    TestBackThenEnterAnotherCampaign();
    TestUnpairedShellGateClearsDeferredEnter();
    TestBackWithGroupNotMainClearsDeferredEnter();
    if (OpenShimTest::FailureCount() == 0)
        std::printf("deferred_modable_policy_tests: all passed\n");
    return OpenShimTest::ExitCode();
}
