// pilot_team_restore.cpp
// BZR Open Shim - pilot team restore on boarding (SinglePlayer tier), split
// out of bzr_hooks.cpp. Driven from its dispatchers; shared helpers come
// from bzr_hooks_internal.h.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
    namespace Hooks
    {
        // --- Pilot team restore on boarding (SinglePlayer tier) ---------------
        //
        // Symptom, from a 2026-09-13 play01.bzn capture with no mission script:
        // an Arc Mine on the PLAYER'S OWN TEAM discharges a gmbolt at the
        // player on the exact frame the player boards a craft -- capture frames
        // 689 and 1565, the two frames the weapon panel switches to the craft
        // loadout. Never on a hop-out. The craft takes no damage, because the
        // thing being shot at is the pilot, which is destroyed moments later.
        //
        // Traced mechanism. Boarding runs GameObject::SetAsUser on the craft
        // (Redux 0x004DB930, structurally identical to 1.5 0x00495468). Before
        // it attaches the craft to userTeamNumber it calls SetAsNotUser on the
        // object you were previously controlling -- your pilot -- and
        // GameObject::SetAsNotUser (Redux 0x004DBA60) ends with
        //
        //     SetTeam( get_obj_team(this->obj) )
        //
        // where get_obj_team (Redux 0x0047E9A0) is
        // `(*(uint*)(obj + 0x14) & 0xF0000) >> 16`: a 4-bit team packed into
        // the low-level object's flags, written once by GameObjectClass::Build
        // as `flags = team << 16`.
        //
        // So the pilot's live team comes from userTeamNumber while you are
        // walking around, but boarding restores it from that packed nibble. A
        // pilot whose nibble reads 0 is therefore momentarily on team 0, and
        // Team::FriendP (Redux 0x005E1310) rejects team 0 outright --
        // `n >= 1 && (dwAllies & (1 << n))` -- so team 0 is nobody's friend,
        // including its own side's mines. WeaponMine::Simulate (0x00612950)
        // then has a legitimate target standing exactly where the pilot is.
        //
        // The fix repairs the stale packed field rather than interfering with
        // the restore: while the player is on foot, if the nibble reads 0 but
        // the live team does not, write the live team into the nibble. Boarding
        // then restores the correct team by itself. No hook, no control-flow
        // surgery, and it is idempotent.
        //
        // CONFIRMED LIVE 2026-09-13. The sentinel is -1, not 0.
        //
        // Measured on lcbench, one run, the whole chain:
        //
        //   15:24:39.118  Pilot on foot   packed=1 live=1  (agree)
        //   15:24:58.369  BOARD_RESULT    BOARDED
        //   15:24:58.371  CAUGHT: pilot reads team -1 after boarding
        //                 (packed=1, tick 1 of 90)
        //   15:24:58.371  Restored live team -1 -> 1
        //
        // So the pilot is on team 1 while on foot and reads **-1** on the very
        // first frame after boarding, with its packed team still 1. -1 is what
        // GameObject::GameObject initialises teamNumber to, i.e. "attached to
        // no team", and it is the live field that GetTeam returns -- the one
        // FriendP consumes -- not the packed one.
        //
        // Two earlier readings of this were wrong and are worth recording so
        // nobody re-derives them:
        //
        //  * the sentinel is NOT 0. The first version of this feature repaired
        //    a packed team of 0 and never fired, because the packed team is
        //    always correct. The damage is to the live team.
        //  * the operative guard is NOT Team::FriendP's `n < 1`. It is the
        //    `-1 < param_2` test one level up in GameObject::FriendP(int)
        //    (Redux 0x004DB560), which -1 fails outright:
        //
        //      if (((teamList != 0) && (-1 < param_2)) && Team::FriendP(param_2))
        //          return 1;
        //      return 0;
        //
        // A pilot reading -1 is therefore nobody's friend, and
        // WeaponMine::Simulate accepts it as a legitimate target while it is
        // still reachable -- an Arc Mine on the player's OWN team firing at the
        // spot they just boarded from, doing no damage to the craft because the
        // thing it is shooting is the dying Person.
        //
        // Still ships OFF: this is confirmed on the scripted lcbench route, not
        // yet on a hand-driven boarding, and it writes to engine state.

        // GameObject layout, all confirmed against the shipped GOG image rather
        // than the advisory PDB:
        //   +0x0F4  _OBJ76* obj      (read by SetAsNotUser as this[0x3d])
        //   +0x174  live team        (GameObject::GetTeam 0x00462450 returns
        //                             subobject+0x15C, and the DistributedObject
        //                             subobject sits at +0x18, so +0x174)
        // and on the _OBJ76:
        //   +0x014  flags, team in bits 16..19
        static constexpr size_t kGameObjectLowLevelObjOffset = 0x0F4;
        static constexpr size_t kGameObjectLiveTeamOffset = 0x174;
        static constexpr size_t kLowLevelObjFlagsOffset = 0x014;
        static constexpr uint32_t kLowLevelObjTeamMask = 0x000F0000u;
        static constexpr int kLowLevelObjTeamShift = 16;
        static constexpr int kMaxPackedTeam = 15;

        static bool g_PilotTeamRestoreConfigInitialized = false;
        static bool g_PilotTeamRestoreEnabled = false;
        static bool g_PilotTeamRestoreRuntimeActive = false;
        // The offsets above are only trusted once the running build has agreed
        // with them on a case that MUST agree. While the player is in a craft
        // the packed nibble and the live team are the same number by
        // construction, so seeing them match proves both offsets on this image.
        // Nothing is ever written before that. An offset that is wrong on some
        // future build therefore stands the feature down instead of corrupting
        // an unrelated field.
        static bool g_PilotTeamLayoutVerified = false;
        static uint32_t g_PilotTeamRepairs = 0;
        static void* g_PilotTeamLastReported = nullptr;

        // Watching the pilot ACROSS the boarding call.
        //
        // The on-foot sample below is taken before boarding, so on its own it
        // cannot see what SetAsNotUser does. SetAsNotUser runs inside
        // GameObject::SetAsUser and the Person survives for a short while
        // afterwards, so the way to catch a team being reset to 0 is to keep
        // reading the object after it has stopped being userObject.
        //
        // Reading an object the engine may be tearing down is only safe because
        // IsLiveHeadlightObjectSlot rejects anything whose primary vtable is not
        // inside the exe's code region: a freed-and-reused slot fails that test
        // rather than yielding plausible garbage. The watch is also hard-bounded
        // in ticks so a pointer that gets recycled into another live GameObject
        // cannot be mistaken for the pilot indefinitely.
        static void* g_PilotTeamWatchObject = nullptr;
        static int g_PilotTeamWatchTicks = 0;
        static int g_PilotTeamWatchLogged = 0;
        static constexpr int kPilotTeamWatchTicks = 90;
        static constexpr int kPilotTeamWatchLogLimit = 30;

        struct PilotTeamSample
        {
            void* lowLevelObj = nullptr;
            uint32_t flags = 0;
            int packedTeam = -1;
            int liveTeam = -1;
        };

        static bool TryReadPilotTeamSample(void* gameObject, PilotTeamSample& out)
        {
            out = {};
            if (!gameObject)
                return false;
            __try
            {
                const auto* base = reinterpret_cast<const uint8_t*>(gameObject);
                out.lowLevelObj = *reinterpret_cast<void* const*>(
                    base + kGameObjectLowLevelObjOffset);
                if (!out.lowLevelObj)
                    return false;
                out.liveTeam = *reinterpret_cast<const int32_t*>(
                    base + kGameObjectLiveTeamOffset);
                out.flags = *reinterpret_cast<const uint32_t*>(
                    reinterpret_cast<const uint8_t*>(out.lowLevelObj) +
                    kLowLevelObjFlagsOffset);
                out.packedTeam =
                    static_cast<int>((out.flags & kLowLevelObjTeamMask) >> kLowLevelObjTeamShift);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                out = {};
                return false;
            }
        }

        static bool TryWritePackedTeam(void* lowLevelObj, uint32_t flags, int team)
        {
            if (!lowLevelObj || team < 1 || team > kMaxPackedTeam)
                return false;
            const uint32_t repaired =
                (flags & ~kLowLevelObjTeamMask) |
                (static_cast<uint32_t>(team) << kLowLevelObjTeamShift);
            __try
            {
                *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint8_t*>(lowLevelObj) + kLowLevelObjFlagsOffset) = repaired;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryWriteLiveTeam(void* gameObject, int team)
        {
            if (!gameObject || team < 1 || team > kMaxPackedTeam)
                return false;
            __try
            {
                *reinterpret_cast<int32_t*>(
                    reinterpret_cast<uint8_t*>(gameObject) +
                    kGameObjectLiveTeamOffset) = team;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void InitializePilotTeamRestoreConfig()
        {
            if (g_PilotTeamRestoreConfigInitialized)
                return;
            g_PilotTeamRestoreConfigInitialized = true;

            bool boolValue = false;
            if (TryGetUserConfigBool(
                    kUserConfigSinglePlayerSection, "PilotTeamRestore", boolValue))
            {
                g_PilotTeamRestoreEnabled = boolValue;
            }
            if (EnvFlagEnabled("OPENSHIM_PILOT_TEAM_RESTORE"))
                g_PilotTeamRestoreEnabled = true;

            Log(L"[PILOTTEAM] Baseline enabled=%hs (SP-only)\n",
                g_PilotTeamRestoreEnabled ? "yes" : "no");
        }

        void RefreshPilotTeamRestoreState()
        {
            InitializePilotTeamRestoreConfig();

            const bool wantActive =
                g_PilotTeamRestoreEnabled && ReadLocalPlayerNetIdValue() == 0;
            if (!wantActive)
            {
                if (g_PilotTeamRestoreRuntimeActive)
                {
                    g_PilotTeamRestoreRuntimeActive = false;
                    Log(L"[PILOTTEAM] Stood down (%hs)\n",
                        g_PilotTeamRestoreEnabled ? "multiplayer" : "disabled");
                }
                return;
            }
            if (!g_PilotTeamRestoreRuntimeActive)
            {
                g_PilotTeamRestoreRuntimeActive = true;
                Log(L"[PILOTTEAM] Pilot team restore active (SP-only)\n");
            }

            void* const player = TryGetHeadlightPlayerObject();

            // The boarding window. Runs before anything else can return early,
            // because this is the only moment the defect can actually be seen.
            if (g_PilotTeamWatchObject && g_PilotTeamWatchObject != player &&
                g_PilotTeamWatchTicks > 0)
            {
                --g_PilotTeamWatchTicks;
                PilotTeamSample after = {};
                const bool live = IsLiveHeadlightObjectSlot(g_PilotTeamWatchObject) &&
                                  TryReadPilotTeamSample(g_PilotTeamWatchObject, after);
                if (!live)
                {
                    Log(L"[PILOTTEAM] Boarding watch ended: pilot 0x%08X is gone "
                        L"after %d ticks\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_PilotTeamWatchObject)),
                        kPilotTeamWatchTicks - g_PilotTeamWatchTicks);
                    g_PilotTeamWatchObject = nullptr;
                    g_PilotTeamWatchTicks = 0;
                }
                else
                {
                    // Anything below 1 defeats the friend test, so that is the
                    // predicate. An earlier revision tested `== 0` and printed
                    // "nothing caught" while its own per-tick lines were already
                    // showing live=-1. Too narrow a predicate is how an
                    // instrument lies to you.
                    //
                    // MEASURED 2026-09-13: on foot the pilot reads live=1, and
                    // 2 ms after boarding it reads live=-1 with packed still 1,
                    // and stays there for the whole watch. -1 is what
                    // GameObject::GameObject initialises teamNumber to, i.e.
                    // "attached to no team".
                    if (after.liveTeam < 1)
                    {
                        Log(L"[PILOTTEAM] *** CAUGHT: pilot 0x%08X reads team %d after "
                            L"boarding (packed=%d flags=0x%08X, tick %d of %d). "
                            L"GameObject::FriendP(int) guards on `-1 < team`, so this "
                            L"object is nobody's friend and a weapon mine on the "
                            L"player's own team will accept it as a target. ***\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_PilotTeamWatchObject)),
                            after.liveTeam, after.packedTeam, after.flags,
                            kPilotTeamWatchTicks - g_PilotTeamWatchTicks,
                            kPilotTeamWatchTicks);

                        // Close the window. The packed team is the value the
                        // engine itself would restore, so writing it back puts
                        // the pilot on a real team for the few frames it is
                        // still reachable. One int, on an object whose vtable
                        // was validated on this same tick.
                        if (g_PilotTeamLayoutVerified &&
                            after.packedTeam >= 1 && after.packedTeam <= kMaxPackedTeam &&
                            TryWriteLiveTeam(g_PilotTeamWatchObject, after.packedTeam))
                        {
                            ++g_PilotTeamRepairs;
                            Log(L"[PILOTTEAM] Restored live team %d -> %d on pilot "
                                L"0x%08X (total=%u)\n",
                                after.liveTeam, after.packedTeam,
                                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_PilotTeamWatchObject)),
                                static_cast<unsigned>(g_PilotTeamRepairs));
                        }
                        g_PilotTeamWatchObject = nullptr;
                        g_PilotTeamWatchTicks = 0;
                    }
                    else if (g_PilotTeamWatchLogged < kPilotTeamWatchLogLimit)
                    {
                        ++g_PilotTeamWatchLogged;
                        Log(L"[PILOTTEAM] Boarding watch tick %d of %d: pilot 0x%08X "
                            L"packed=%d live=%d\n",
                            kPilotTeamWatchTicks - g_PilotTeamWatchTicks,
                            kPilotTeamWatchTicks,
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_PilotTeamWatchObject)),
                            after.packedTeam, after.liveTeam);
                    }
                    // Only an expiry with the watch still armed is a real "nothing
                    // caught". The catch branch above clears the counter itself,
                    // so without this guard a successful catch was immediately
                    // followed by a line claiming the opposite.
                    if (g_PilotTeamWatchObject && g_PilotTeamWatchTicks == 0)
                    {
                        Log(L"[PILOTTEAM] Boarding watch expired after %d ticks with "
                            L"the pilot still on a real team -- nothing caught\n",
                            kPilotTeamWatchTicks);
                        g_PilotTeamWatchObject = nullptr;
                    }
                }
            }

            if (!player || !IsLiveHeadlightObjectSlot(player))
                return;  // no world yet; silent by design, this runs per frame

            // Every other bail-out below says so once. A feature that stands
            // down without a word is indistinguishable from one that is broken,
            // and a run spent discovering that is a run wasted.
            PilotTeamSample sample = {};
            if (!TryReadPilotTeamSample(player, sample))
            {
                static bool reported = false;
                if (!reported)
                {
                    reported = true;
                    Log(L"[PILOTTEAM] Stood down: cannot read the team fields on "
                        L"player=0x%08X (obj +0x%X / team +0x%X). Wrong build layout.\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(player)),
                        static_cast<unsigned>(kGameObjectLowLevelObjOffset),
                        static_cast<unsigned>(kGameObjectLiveTeamOffset));
                }
                return;
            }

            const bool onFoot = IsPilotOnFoot(player);

            if (!onFoot)
            {
                // Layout self-check. A craft's packed nibble and live team are
                // the same number by construction, so agreement here proves
                // both offsets on this image. Only then is a write allowed.
                if (!g_PilotTeamLayoutVerified &&
                    sample.liveTeam >= 1 && sample.liveTeam <= kMaxPackedTeam &&
                    sample.packedTeam == sample.liveTeam)
                {
                    g_PilotTeamLayoutVerified = true;
                    Log(L"[PILOTTEAM] Layout verified on a craft: packed=%d live=%d "
                        L"(obj=0x%08X flags=0x%08X)\n",
                        sample.packedTeam, sample.liveTeam,
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sample.lowLevelObj)),
                        sample.flags);
                }
                g_PilotTeamLastReported = nullptr;
                return;
            }

            // One line per distinct pilot object. This is the measurement the
            // decompilation could not supply: whether the packed nibble and the
            // live team actually disagree for a runtime-built pilot.
            // Arm the boarding watch on every frame the player is on foot, so
            // it is live no matter which frame the boarding lands on.
            if (g_PilotTeamWatchObject != player)
            {
                g_PilotTeamWatchLogged = 0;
                g_PilotTeamWatchObject = player;
            }
            g_PilotTeamWatchTicks = kPilotTeamWatchTicks;

            if (g_PilotTeamLastReported != player)
            {
                g_PilotTeamLastReported = player;
                Log(L"[PILOTTEAM] Pilot on foot player=0x%08X packed=%d live=%d "
                    L"verified=%hs%hs\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(player)),
                    sample.packedTeam, sample.liveTeam,
                    g_PilotTeamLayoutVerified ? "yes" : "no",
                    (sample.packedTeam == sample.liveTeam)
                        ? " (agree -- nothing to repair)"
                        : " (DISAGREE)");
            }

            if (!g_PilotTeamLayoutVerified)
            {
                static bool reported = false;
                if (!reported)
                {
                    reported = true;
                    Log(L"[PILOTTEAM] Holding: the layout self-check has not passed "
                        L"yet, so nothing will be written. It passes the first time "
                        L"the player is in a craft whose packed and live team agree.\n");
                }
                return;
            }
            if (sample.packedTeam != 0)
                return;  // nothing to repair; the per-pilot line above says so
            if (sample.liveTeam < 1 || sample.liveTeam > kMaxPackedTeam)
            {
                static bool reported = false;
                if (!reported)
                {
                    reported = true;
                    Log(L"[PILOTTEAM] Not repairing: packed team is 0 but the live "
                        L"team is %d, which is not a team this field can hold "
                        L"(1..%d). Both readings are suspect; standing down.\n",
                        sample.liveTeam, kMaxPackedTeam);
                }
                return;
            }

            if (TryWritePackedTeam(sample.lowLevelObj, sample.flags, sample.liveTeam))
            {
                ++g_PilotTeamRepairs;
                Log(L"[PILOTTEAM] Repaired packed team 0 -> %d on pilot 0x%08X "
                    L"(obj=0x%08X total=%u)\n",
                    sample.liveTeam,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(player)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sample.lowLevelObj)),
                    static_cast<unsigned>(g_PilotTeamRepairs));
            }
        }

        void RevertPilotTeamRestoreToBaseline()
        {
            // Nothing to undo: the only write repairs a field the engine itself
            // owns, and it is already what the engine would have stored. Just
            // re-read the setting and let the next tick decide.
            g_PilotTeamRestoreConfigInitialized = false;
            g_PilotTeamLastReported = nullptr;
            InitializePilotTeamRestoreConfig();
        }
    }
}
