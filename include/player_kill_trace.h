// Player-kill research instrumentation: engine-independent classification.
//
// Background (PR 107 phase 2-3): Redux records a multiplayer death against a
// *team*, not against the object that fired.  To tell "a player killed a
// player" from "a player killed somebody's AI wingman" we need a per-object
// controller signal, and no such field has been qualified yet.  This header
// holds the two pure decisions the instrument makes -- how an object's
// observed distributed fields are classified, and how confident the
// damage->death correlation is -- so the trace log and its tests read the same
// code rather than two copies that can drift.
//
// Nothing here is a production predicate.  ClassifyController reports what was
// observed; it deliberately refuses to call an object human-controlled just
// because its team has a NetPlayer, because an AI wingman on a human team has
// exactly that shape.  The activnet_id rule is a hypothesis under test.

#pragma once

#include <cstdint>

namespace BZROpenShim
{
    namespace PlayerKillTrace
    {
        // Sentinel activnet_id values seen on objects with no network owner.
        constexpr uint16_t kActivNetUnowned = 0xFA01;
        constexpr uint16_t kActivNetUnread = 0xFFFF;
        constexpr uint16_t kNetPlayerIdUnread = 0xFFFF;

        // Correlation windows, in milliseconds, between the last recorded
        // damage event and the authoritative death callback.
        constexpr uint64_t kCorrelationExactMs = 500;
        constexpr uint64_t kCorrelationLikelyMs = 2000;

        // The subset of an object's observed distributed state that the
        // classification actually depends on.  The full trace record carries
        // more (dwLocalID, aiProcess, vtable); those are logged, not decided on.
        struct ControllerFields
        {
            int team = 0;
            uint16_t activnet_id = kActivNetUnread;
            uint16_t netPlayerId = kNetPlayerIdUnread;
            bool teamHasNetPlayer = false;
            bool isLocalHandle = false;
        };

        enum class Controller
        {
            LocalHuman,      // the handle is this process's own player object
            HumanByActivNet, // hypothesis: activnet_id matches the team's NetPlayer id
            AiUnowned,       // activnet_id carries an unowned sentinel
            HumanTeamAi,     // on a team that has a NetPlayer, but not identified as that player
            Other,
        };

        constexpr const char* DescribeController(Controller c)
        {
            switch (c)
            {
            case Controller::LocalHuman:      return "local-human";
            case Controller::HumanByActivNet: return "human-by-activnet";
            case Controller::AiUnowned:       return "ai-unowned";
            case Controller::HumanTeamAi:     return "human-team-ai?";
            case Controller::Other:           break;
            }
            return "ai/other";
        }

        // Order matters.  The unowned sentinel is checked before the
        // team-has-a-NetPlayer fallback so that an AI wingman sitting on a
        // human team can never be reported as human.
        constexpr Controller ClassifyController(const ControllerFields& f)
        {
            if (f.isLocalHandle)
                return Controller::LocalHuman;

            if (f.activnet_id == kActivNetUnowned || f.activnet_id == 0)
                return Controller::AiUnowned;

            if (f.activnet_id != kActivNetUnread &&
                f.teamHasNetPlayer &&
                f.netPlayerId != kNetPlayerIdUnread &&
                f.activnet_id == f.netPlayerId)
            {
                return Controller::HumanByActivNet;
            }

            if (f.teamHasNetPlayer)
                return Controller::HumanTeamAi;

            return Controller::Other;
        }

        enum class Correlation
        {
            Absent,        // no pending damage record for this victim
            Exact,         // single attacker, death within the exact window
            Likely,        // attacker known, but older or team not confirmed
            Ambiguous,     // attacker known, death too far from the last hit
            AmbiguousMulti,// more than one attacker damaged this victim in-window
            TeamMismatch,  // the pending damager's team is not the recorded killer team
            Exception,     // reading the pending table faulted
        };

        constexpr const char* DescribeCorrelation(Correlation c)
        {
            switch (c)
            {
            case Correlation::Absent:         return "absent";
            case Correlation::Exact:          return "exact";
            case Correlation::Likely:         return "likely";
            case Correlation::Ambiguous:      return "ambiguous";
            case Correlation::AmbiguousMulti: return "ambiguous-multi";
            case Correlation::TeamMismatch:   return "mismatch-team-ambiguous";
            case Correlation::Exception:      break;
            }
            return "except";
        }

        // What the pending-damage table yielded for one victim.
        struct CorrelationInput
        {
            bool havePending = false;   // a pending record was found at all
            bool damagerKnown = false;  // that record names a damager handle
            bool damagerTeamKnown = false;
            bool damagerTeamMatchesKiller = false;
            uint64_t ageMs = 0;         // now - lastDamageMs
            // Distinct damagers, other than the one selected, that hit THIS
            // victim inside kCorrelationLikelyMs.  Counting other victims here
            // instead is the easy mistake: it makes every busy fight ambiguous.
            int otherAttackersOnVictim = 0;
        };

        constexpr Correlation ClassifyCorrelation(const CorrelationInput& in)
        {
            if (!in.havePending || !in.damagerKnown)
                return Correlation::Absent;

            if (!in.damagerTeamKnown)
                return Correlation::Likely;

            if (!in.damagerTeamMatchesKiller)
                return Correlation::TeamMismatch;

            if (in.ageMs >= kCorrelationLikelyMs)
                return Correlation::Ambiguous;

            if (in.ageMs >= kCorrelationExactMs)
                return Correlation::Likely;

            return in.otherAttackersOnVictim > 0 ? Correlation::AmbiguousMulti
                                                 : Correlation::Exact;
        }
    }
}
