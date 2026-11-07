// deferred_modable_policy.h
// BZR Open Shim - when a mount setter may skip the Modable rebuild.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Pure decisions behind src/patches/deferred_modable_rebuild.cpp, kept free of
// the engine so tests can drive them. Mount modes: 0 mission/campaign,
// 1 instant action, 2 multiplayer, 3 campaign list, 4 main menu.

#pragma once

namespace BZROpenShim
{
    namespace DeferredModablePolicy
    {
        constexpr int kModeMission = 0;
        constexpr int kModeIa = 1;
        constexpr int kModeMp = 2;
        constexpr int kModeList = 3;
        constexpr int kModeMain = 4;
        constexpr int kHeldUnknown = -1;

        struct State
        {
            int held = kHeldUnknown;      // mount mode whose content the group holds
            bool pending = false;         // shell mounts moved past held without a rebuild
            bool pendingMission = false;  // campaign enter deferred; the group never saw it
            int storeTarget = -1;         // mode the last hooked store wrote
            int storeBefore = -1;         // mode it replaced (-1 unreadable)
            bool inMissionMount = false;  // inside the mission mount 0x0076E6C0
            bool mountRebuilt = false;    // a real rebuild ran inside the mount
        };

        enum class GateReason
        {
            Kept,              // stock rebuild
            ShellSkipped,      // shell -> main set, nothing to catch up
            ShellDeferred,     // shell -> other shell mode, catch-up pending
            CampaignEnter,     // mode-0 setter outside the mount: deferred
            CampaignBack,      // briefing -> shell, the enter rebuild never happened
        };

        struct GateResult
        {
            bool skip = false;
            GateReason reason = GateReason::Kept;
            int before = -1;  // mode being replaced, -1 unknown
            int held = kHeldUnknown;  // what the group held on entry
        };

        // One of the four shell setters (target 1-4) reached its gate.
        inline GateResult DecideShellGate(State& s, int target)
        {
            GateResult r;
            const bool paired = s.storeTarget == target;
            r.before = paired ? s.storeBefore : -1;
            r.held = s.held;
            s.storeTarget = -1;
            const bool backFromDeferredEnter = r.before == kModeMission && s.pendingMission;
            const bool fromShell = (r.before >= kModeIa && r.before <= kModeMain) || backFromDeferredEnter;
            if (fromShell && s.held == kModeMain)
            {
                s.pendingMission = false;
                s.pending = target != kModeMain;
                r.skip = true;
                r.reason = backFromDeferredEnter ? GateReason::CampaignBack
                                                 : (s.pending ? GateReason::ShellDeferred : GateReason::ShellSkipped);
                return r;
            }
            // Any shell setter that reached its gate replaced mode 0, so a
            // deferred enter is no longer owed (also when store/gate were unpaired).
            s.pendingMission = false;
            s.held = target;
            s.pending = false;
            return r;
        }

        // The mode-0 setter 0x0076AE60 reached its gate. Outside the mission
        // mount (the screen factory entering a campaign) the rebuild is
        // deferred and the group keeps what it held; inside the mount it is
        // stock and leaves the group holding mission content.
        inline GateResult DecideCampaignGate(State& s)
        {
            GateResult r;
            r.before = kModeMission;
            r.held = s.held;
            s.storeTarget = -1;
            if (s.inMissionMount)
            {
                s.mountRebuilt = true;
                s.held = kModeMission;
                return r;
            }
            s.pendingMission = true;
            r.skip = true;
            r.reason = GateReason::CampaignEnter;
            return r;
        }

        // The mission mount is about to run. Returns true when a deferred
        // campaign enter must be rebuilt now: before the mount, which is where
        // stock had already rebuilt it, so everything the mount does after B's
        // guard sees mission content exactly as in stock.
        inline bool BeginMissionMount(State& s)
        {
            s.inMissionMount = true;
            s.mountRebuilt = false;
            if (!s.pendingMission) return false;
            s.pendingMission = false;
            s.pending = false;
            s.held = kModeMission;
            return true;
        }

        // The mission mount returned; the shell catch-up (Flush) runs next.
        inline void FinishMissionMount(State& s)
        {
            s.mountRebuilt = false;
            s.inMissionMount = false;
        }
    }
}
