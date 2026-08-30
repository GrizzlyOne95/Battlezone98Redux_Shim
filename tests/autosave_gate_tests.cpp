// Regression tests for the autosave precondition gate.
//
// The case these pin down is the 2026-08-29 Steam repro: an Instant Action map
// that needs an uninstalled EXU leaves the game on the loading screen behind a
// modal error dialog, with the local player object already built. The old gate
// was "not a net game and userObject != nullptr", which is true in exactly that
// state, so autosave called the engine's SaveGame every interval and the engine
// faulted 0xC0000005 every time at battlezone98redux.exe+0x001D7593.
//
// Two of the rules below are the fix, and both are load-bearing:
//   - a classified shell screen blocks the save even with the cursor hidden
//     (the loading screen hides it, which is how the old check was bypassed);
//   - a fault latches the feature off instead of retrying on the next interval.

#include "autosave_gate.h"

#include <cstdio>
#include <cstdlib>

namespace
{
    using namespace BZROpenShim;
    using namespace BZROpenShim::AutoSaveGate;

    int g_failures = 0;

    void Require(bool condition, const char* message)
    {
        if (!condition)
        {
            std::fprintf(stderr, "autosave_gate_tests: %s\n", message);
            ++g_failures;
        }
    }

    void RequireDecision(const ObservedState& state, Decision expected, const char* message)
    {
        const GateResult result = Evaluate(state);
        if (result.decision != expected)
        {
            std::fprintf(
                stderr,
                "autosave_gate_tests: %s (expected %s, got %s: \"%s\")\n",
                message,
                DescribeDecision(expected),
                DescribeDecision(result.decision),
                result.reason);
            ++g_failures;
        }
    }

    // Ordinary gameplay: mission live, no shell screen, cursor hidden.
    ObservedState LiveMission()
    {
        ObservedState state;
        state.stateReadable = true;
        state.netGame = false;
        state.userObjectPresent = true;
        state.userObjectPlausible = true;
        state.pauseMenuOpen = false;
        state.uiWrapperActive = false;
        state.uiScreenPresent = false;
        state.uiScreenType = kScreenTypeNone;
        state.cursorVisible = false;
        return state;
    }

    // The repro: mission load got far enough to build the player object, then
    // aborted on the missing EXU and parked on the loading screen. The cursor is
    // hidden, so only the screen-type rule can catch this.
    ObservedState AbortedLoadScreen()
    {
        ObservedState state = LiveMission();
        state.uiWrapperActive = true;
        state.uiScreenPresent = true;
        state.uiScreenType = kScreenTypeLoading;
        state.cursorVisible = false;
        return state;
    }

    void TestLiveMissionSaves()
    {
        RequireDecision(LiveMission(), Decision::Save, "a live mission must save");
    }

    void TestAbortedLoadIsRefused()
    {
        RequireDecision(
            AbortedLoadScreen(), Decision::UiBusy, "the loading screen must block SaveGame");

        // The specific hole in the old gate: this state satisfied every one of
        // its conditions, so it must not be the screen check alone that is
        // tested - assert the cursor plays no part in the loading-screen rule.
        ObservedState cursorShown = AbortedLoadScreen();
        cursorShown.cursorVisible = true;
        RequireDecision(
            cursorShown, Decision::UiBusy, "the loading screen must block with the cursor up too");
    }

    void TestClassifiedShellScreensAreCursorIndependent()
    {
        const uint32_t screens[] = {
            kScreenTypeOptions,
            kScreenTypePause,
            kScreenTypeSaveGame,
            kScreenTypeLoadGame,
            kScreenTypeLoading,
        };
        for (const uint32_t screenType : screens)
        {
            ObservedState state = LiveMission();
            state.uiWrapperActive = true;
            state.uiScreenPresent = true;
            state.uiScreenType = screenType;
            RequireDecision(state, Decision::UiBusy, "classified shell screen must block");
            Require(
                IsNonGameplayScreenType(screenType), "classified screen must be non-gameplay");
        }
    }

    void TestUnclassifiedScreenTypeStillNeedsTheCursor()
    {
        // A stale non-zero screen type is observed during ordinary gameplay
        // (post-mission dump: wrapperActive=1, screenType=1). Treating it as a
        // shell screen would suppress autosave for the rest of the mission, so
        // the cursor still qualifies the unclassified case.
        ObservedState hidden = LiveMission();
        hidden.uiWrapperActive = true;
        hidden.uiScreenPresent = true;
        hidden.uiScreenType = 0x01;
        hidden.cursorVisible = false;
        RequireDecision(hidden, Decision::Save, "stale screen type alone must not block");

        ObservedState shown = hidden;
        shown.cursorVisible = true;
        RequireDecision(shown, Decision::UiBusy, "unclassified screen with cursor must block");
    }

    void TestScreenTypeOnlyCountsWhenTheWrapperOwnsAScreen()
    {
        ObservedState noWrapper = LiveMission();
        noWrapper.uiWrapperActive = false;
        noWrapper.uiScreenPresent = true;
        noWrapper.uiScreenType = kScreenTypePause;
        RequireDecision(noWrapper, Decision::Save, "screen type without an active wrapper is stale");

        ObservedState noScreen = LiveMission();
        noScreen.uiWrapperActive = true;
        noScreen.uiScreenPresent = false;
        noScreen.uiScreenType = kScreenTypePause;
        RequireDecision(noScreen, Decision::Save, "screen type without a screen pointer is stale");
    }

    void TestMissionPreconditions()
    {
        ObservedState unreadable = LiveMission();
        unreadable.stateReadable = false;
        RequireDecision(unreadable, Decision::StateUnreadable, "unreadable state must not save");

        ObservedState net = LiveMission();
        net.netGame = true;
        RequireDecision(net, Decision::NoLiveMission, "a net game must not autosave");

        ObservedState noPlayer = LiveMission();
        noPlayer.userObjectPresent = false;
        noPlayer.userObjectPlausible = false;
        RequireDecision(noPlayer, Decision::NoLiveMission, "no player object must not save");

        // Present but not a constructed object: the pointer survived a half-built
        // mission but its vtable does not check out.
        ObservedState garbage = LiveMission();
        garbage.userObjectPlausible = false;
        RequireDecision(garbage, Decision::NoLiveMission, "implausible player object must not save");

        ObservedState paused = LiveMission();
        paused.pauseMenuOpen = true;
        RequireDecision(paused, Decision::UiBusy, "the pause menu must block");
    }

    void TestFaultLatches()
    {
        // Once the engine has faulted, no amount of otherwise-clean state may
        // put the call back. This is what bounds the damage when the gate is
        // wrong about a state nobody has seen yet.
        ObservedState missionFault = LiveMission();
        missionFault.missionSaveFaulted = true;
        RequireDecision(missionFault, Decision::FaultLatched, "a mission fault must latch off");

        ObservedState processFault = LiveMission();
        processFault.saveDisabledForProcess = true;
        RequireDecision(processFault, Decision::FaultLatched, "a process fault must latch off");

        // The process latch outranks even an unreadable probe, so a stand-down
        // reports the reason a reader can act on.
        ObservedState both = processFault;
        both.stateReadable = false;
        RequireDecision(both, Decision::FaultLatched, "the process latch must outrank unreadable");
    }

    void TestReasonsAreAlwaysReportable()
    {
        ObservedState state = LiveMission();
        Require(Evaluate(state).reason != nullptr, "a save decision must carry a reason");
        Require(Evaluate(AbortedLoadScreen()).reason != nullptr, "a refusal must carry a reason");
        Require(
            DescribeScreenType(kScreenTypeLoading) == Evaluate(AbortedLoadScreen()).reason,
            "a classified refusal must name the screen");
    }
}

int main()
{
    TestLiveMissionSaves();
    TestAbortedLoadIsRefused();
    TestClassifiedShellScreensAreCursorIndependent();
    TestUnclassifiedScreenTypeStillNeedsTheCursor();
    TestScreenTypeOnlyCountsWhenTheWrapperOwnsAScreen();
    TestMissionPreconditions();
    TestFaultLatches();
    TestReasonsAreAlwaysReportable();

    if (g_failures != 0)
    {
        std::fprintf(stderr, "autosave_gate_tests: %d failure(s)\n", g_failures);
        return 1;
    }
    std::printf("autosave_gate_tests: all checks passed\n");
    return 0;
}
