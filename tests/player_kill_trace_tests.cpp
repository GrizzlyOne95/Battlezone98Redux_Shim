// Tests for the player-kill research instrumentation's two pure decisions.
//
// These exercise include/player_kill_trace.h directly -- the same code the
// trace in bzr_hooks.cpp calls -- rather than a copy of the rules, so a change
// to the classifier cannot pass here and drift in the shim.
//
// What is NOT being asserted: that activnet_id == the team's NetPlayer id
// really identifies a human-driven object. That is the hypothesis the trace
// exists to test against live two-peer captures. What IS asserted is the
// property that must hold whatever the answer turns out to be: an AI wingman
// sharing a human's team must never be reported as that human.
//
// Engine-independent: links no engine patch code.

#include "player_kill_trace.h"

#include <cstdio>
#include <cstring>

namespace
{
    using namespace BZROpenShim::PlayerKillTrace;

    int g_failures = 0;

    void Require(bool condition, const char* message)
    {
        if (!condition)
        {
            std::fprintf(stderr, "player_kill_trace_tests: %s\n", message);
            ++g_failures;
        }
    }

    void RequireController(const ControllerFields& fields,
                           Controller expected,
                           const char* message)
    {
        const Controller actual = ClassifyController(fields);
        if (actual != expected)
        {
            std::fprintf(stderr,
                         "player_kill_trace_tests: %s (expected %s, got %s)\n",
                         message,
                         DescribeController(expected),
                         DescribeController(actual));
            ++g_failures;
        }
    }

    void RequireCorrelation(const CorrelationInput& in,
                            Correlation expected,
                            const char* message)
    {
        const Correlation actual = ClassifyCorrelation(in);
        if (actual != expected)
        {
            std::fprintf(stderr,
                         "player_kill_trace_tests: %s (expected %s, got %s)\n",
                         message,
                         DescribeCorrelation(expected),
                         DescribeCorrelation(actual));
            ++g_failures;
        }
    }

    // The case the whole instrument turns on. An AI wingman on a human's team
    // has teamHasNetPlayer == true, exactly like the human's own craft. If the
    // classifier leaned on that flag alone, every wingman kill would be
    // counted as a player kill, which is the miscount being investigated.
    void TestTeamNetPlayerIsNotProofOfHuman()
    {
        ControllerFields wingman;
        wingman.team = 2;
        wingman.teamHasNetPlayer = true;
        wingman.netPlayerId = 0x1234;
        wingman.activnet_id = kActivNetUnowned;
        RequireController(wingman, Controller::AiUnowned,
                          "unowned wingman on a human team must not read as human");

        ControllerFields human;
        human.team = 2;
        human.teamHasNetPlayer = true;
        human.netPlayerId = 0x1234;
        human.activnet_id = 0x1234;
        RequireController(human, Controller::HumanByActivNet,
                          "owned craft matching its team's NetPlayer id");

        Require(ClassifyController(wingman) != ClassifyController(human),
                "wingman and human on one team must not classify alike");
    }

    // The unowned sentinel has to be checked before the team fallback.
    // Ordered the other way, a zero activnet_id on a human team reports
    // human-team-ai? instead of ai-unowned and the log loses the distinction.
    void TestUnownedSentinelBeatsTeamFallback()
    {
        ControllerFields zeroId;
        zeroId.team = 3;
        zeroId.teamHasNetPlayer = true;
        zeroId.netPlayerId = 0x0007;
        zeroId.activnet_id = 0;
        RequireController(zeroId, Controller::AiUnowned,
                          "activnet_id 0 is unowned, not a team-AI guess");
    }

    // A failed read must not be able to match a failed NetPlayer lookup and
    // manufacture a human. Both fields default to 0xFFFF.
    void TestUnreadFieldsNeverMatch()
    {
        ControllerFields unread;
        unread.team = 4;
        unread.teamHasNetPlayer = true;
        RequireController(unread, Controller::HumanTeamAi,
                          "0xFFFF == 0xFFFF must not be read as an id match");

        ControllerFields noNetPlayer;
        noNetPlayer.team = 4;
        noNetPlayer.activnet_id = 0x0042;
        RequireController(noNetPlayer, Controller::Other,
                          "an owned object on a team with no NetPlayer");
    }

    void TestLocalHandleWins()
    {
        ControllerFields local;
        local.team = 1;
        local.isLocalHandle = true;
        local.activnet_id = kActivNetUnowned;
        RequireController(local, Controller::LocalHuman,
                          "the local player's own handle outranks every field read");
    }

    void TestCorrelationWindows()
    {
        CorrelationInput in;
        in.havePending = true;
        in.damagerKnown = true;
        in.damagerTeamKnown = true;
        in.damagerTeamMatchesKiller = true;

        in.ageMs = 0;
        RequireCorrelation(in, Correlation::Exact, "same-tick death is exact");

        in.ageMs = kCorrelationExactMs - 1;
        RequireCorrelation(in, Correlation::Exact, "just inside the exact window");

        in.ageMs = kCorrelationExactMs;
        RequireCorrelation(in, Correlation::Likely, "the exact window is half-open");

        in.ageMs = kCorrelationLikelyMs - 1;
        RequireCorrelation(in, Correlation::Likely, "just inside the likely window");

        in.ageMs = kCorrelationLikelyMs;
        RequireCorrelation(in, Correlation::Ambiguous, "the likely window is half-open");
    }

    // Multi-attacker ambiguity is a property of one victim's own damager
    // history. The first version of this counted other entries that merely
    // shared the victim's team -- i.e. other victims -- so any teammate taking
    // fire downgraded an otherwise clean attribution.
    void TestMultiAttackerOnlyDowngradesExact()
    {
        CorrelationInput in;
        in.havePending = true;
        in.damagerKnown = true;
        in.damagerTeamKnown = true;
        in.damagerTeamMatchesKiller = true;
        in.ageMs = 10;

        in.otherAttackersOnVictim = 0;
        RequireCorrelation(in, Correlation::Exact, "a single attacker stays exact");

        in.otherAttackersOnVictim = 1;
        RequireCorrelation(in, Correlation::AmbiguousMulti,
                           "a second attacker on this victim is ambiguous");

        // Outside the exact window the age already tells the story; a second
        // attacker must not promote a stale record to a more specific verdict.
        in.ageMs = kCorrelationLikelyMs + 1;
        in.otherAttackersOnVictim = 3;
        RequireCorrelation(in, Correlation::Ambiguous,
                           "a stale record stays ambiguous, not ambiguous-multi");
    }

    void TestMissingAndMismatchedPending()
    {
        CorrelationInput none;
        RequireCorrelation(none, Correlation::Absent, "no pending record");

        CorrelationInput noDamager;
        noDamager.havePending = true;
        RequireCorrelation(noDamager, Correlation::Absent,
                           "a pending record naming no damager is absent");

        CorrelationInput noTeam;
        noTeam.havePending = true;
        noTeam.damagerKnown = true;
        RequireCorrelation(noTeam, Correlation::Likely,
                           "damager known but team unresolved");

        CorrelationInput mismatch;
        mismatch.havePending = true;
        mismatch.damagerKnown = true;
        mismatch.damagerTeamKnown = true;
        mismatch.damagerTeamMatchesKiller = false;
        mismatch.ageMs = 1;
        RequireCorrelation(mismatch, Correlation::TeamMismatch,
                           "the recorded killer team disagrees with the damager");
    }

    // The strings end up in operator-supplied logs and in the analysis
    // scripts that read them back, so they are part of the contract.
    void TestDescriptionsAreStable()
    {
        Require(std::strcmp(DescribeController(Controller::LocalHuman), "local-human") == 0,
                "local-human label");
        Require(std::strcmp(DescribeController(Controller::HumanByActivNet), "human-by-activnet") == 0,
                "human-by-activnet label");
        Require(std::strcmp(DescribeController(Controller::AiUnowned), "ai-unowned") == 0,
                "ai-unowned label");
        Require(std::strcmp(DescribeCorrelation(Correlation::AmbiguousMulti), "ambiguous-multi") == 0,
                "ambiguous-multi label");
        Require(std::strcmp(DescribeCorrelation(Correlation::TeamMismatch), "mismatch-team-ambiguous") == 0,
                "mismatch-team-ambiguous label");
    }
}

int main()
{
    TestTeamNetPlayerIsNotProofOfHuman();
    TestUnownedSentinelBeatsTeamFallback();
    TestUnreadFieldsNeverMatch();
    TestLocalHandleWins();
    TestCorrelationWindows();
    TestMultiAttackerOnlyDowngradesExact();
    TestMissingAndMismatchedPending();
    TestDescriptionsAreStable();

    if (g_failures != 0)
    {
        std::fprintf(stderr, "player_kill_trace_tests: %d failure(s)\n", g_failures);
        return 1;
    }

    std::printf("player_kill_trace_tests passed\n");
    return 0;
}
