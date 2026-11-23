// howitzer_attack_approach.cpp
// BZR Open Shim - when the player orders a howitzer (class Howitzer, e.g.
// avartl/svartl) to attack a target its shells cannot reach, pack up, drive
// toward the target, and deploy and fire once it is in reach, instead of the
// stock "out of range" reply. Single player only; [SinglePlayer]
// HowitzerAttackApproach, default OFF. Addresses and behaviour:
// Docs/HOWITZER_ATTACK_APPROACH.md.
//
// Stock ArtilleryProcess::DoAttack (0x00475B30) runs the ballistic reach test
// on the first weapon and, on a miss, says "out of range" and drops to idle.
// It never moves the craft. This wraps that slot on the ArtilleryFriend vtable
// only: while the target is out of reach it skips the stock body and drives
// the craft with the stock UnitProcess GotoTask (the same task the goto state
// uses), and once in reach it deploys and hands the tick back to stock.
#include "bzr_hooks_internal.h"
#include "hook_engine.h"
#include "patcher.h"
#include "shim_log.h"
#include <Windows.h>
#include <cmath>
#include <cstdint>
#include <unordered_map>

namespace BZROpenShim::Hooks
{
    namespace
    {
        using FnCraftVoid = void(__thiscall*)(void* craft);
        using FnProcessVoid = void(__thiscall*)(void* process);
        using FnGetObj = void*(__cdecl*)(uint32_t handle);
        using FnGetTime = float(__cdecl*)();
        // 0x0056AF20, thiscall(ECX = weapon): AL = discriminant >= 0.
        using FnBallisticReach = bool(__thiscall*)(void* weapon, float* outTime,
                                                   const float* targetPos, char highArc);
        using FnTaskDelete = void*(__thiscall*)(void* task, unsigned flags);
        using FnTaskBool = bool(__thiscall*)(void* task);
        using FnTaskVoid = void(__thiscall*)(void* task);

        // Craft vtable slots (HowitzerVtable).
        constexpr size_t kCraftDeploySlot = 24;
        constexpr size_t kCraftPackupSlot = 25;
        // ArtilleryFriend vtable slots: state 7 (attack) End / Do.
        constexpr size_t kProcessEndAttackSlot = 25;
        constexpr size_t kProcessDoAttackSlot = 26;
        // Task vtable slots, as UnitProcess::DoGoto 0x005FB770 calls them.
        constexpr size_t kTaskDeleteSlot = 0;
        constexpr size_t kTaskDoneSlot = 6;
        constexpr size_t kTaskExecuteSlot = 7;

        constexpr int kCmdAttack = 4;

        // Craft fields.
        constexpr size_t kCraftCurrentCommandOffset = 0xAC;
        constexpr size_t kCraftCarrierOffset = 0x1A0;
        constexpr size_t kCraftDeployStateOffset = 0x228;
        constexpr size_t kCraftControlsOffset = 0x230;
        constexpr int kDeployStateUndeployed = 0;
        constexpr int kDeployStateDeploying = 1;
        constexpr int kDeployStateDeployed = 2;
        // Controls the stock artillery idle zeroes (0x00475970 lines 37-45).
        constexpr size_t kControlsFirst = 0xC4;
        constexpr size_t kControlsLast = 0xD8;

        // Carrier fields (Carrier::GetWeapon 0x00417F60).
        constexpr size_t kCarrierWeaponsOffset = 0x18;
        constexpr size_t kCarrierMaskOffset = 0x2C;
        constexpr int kCarrierWeaponCount = 5;
        // Weapon fields: +0x08 class (+0x0C signature), +0x0C ordnance class
        // (+0x54 shot speed).
        constexpr size_t kWeaponClassOffset = 0x08;
        constexpr size_t kWeaponOrdnanceOffset = 0x0C;
        constexpr size_t kClassSignatureOffset = 0x0C;
        constexpr size_t kOrdnanceSpeedOffset = 0x54;
        constexpr int kMortarSignature = 0x4D4F5254; // 'MORT'

        // AiProcess fields.
        constexpr size_t kProcessCraftOffset = 0x34;
        constexpr size_t kProcessTaskOffset = 0x38;
        constexpr size_t kProcessTargetHandleOffset = 0x3C;
        constexpr size_t kProcessAttackTimeoutOffset = 0x7C;
        constexpr float kAttackTimeoutSeconds = 30.0f;

        // Reach margins: the target is pushed out horizontally from the craft
        // by this factor before the stock reach test. Stock aims at a led
        // position, so deploy only with room to spare, and keep firing while
        // the smaller margin still passes (hysteresis).
        constexpr float kDeployReachFactor = 1.05f;
        constexpr float kHoldReachFactor = 1.02f;
        // Pack up once a deployed howitzer has been out of reach this long.
        constexpr float kPackupDelaySeconds = 1.0f;
        // Re-path when the target has moved this far from the goto snapshot,
        // at most once per kRepathMinSeconds.
        constexpr float kRepathDistanceSq = 25.0f * 25.0f;
        constexpr float kRepathMinSeconds = 2.0f;
        // An entry not ticked for this long belongs to an earlier attack.
        constexpr float kTrackMaxAgeSeconds = 2.0f;
        constexpr size_t kTrackLimit = 256;

        uint32_t g_FriendVtableAddr = 0;
        uint32_t g_HowitzerVtableAddr = 0;
        uint32_t g_DoAttackAddr = 0;
        uint32_t g_EndAttackAddr = 0;
        uint32_t g_InitGotoAddr = 0;
        uint32_t g_ReachAddr = 0;
        uint32_t g_CraftDeployAddr = 0;
        uint32_t g_CraftPackupAddr = 0;
        uint32_t g_GetObjAddr = 0;
        uint32_t g_GetTimeAddr = 0;

        FnProcessVoid g_StockDoAttack = nullptr;
        FnProcessVoid g_StockEndAttack = nullptr;
        FnProcessVoid g_FnInitGoto = nullptr;
        FnBallisticReach g_FnReach = nullptr;
        FnCraftVoid g_FnCraftDeploy = nullptr;
        FnCraftVoid g_FnCraftPackup = nullptr;
        FnGetObj g_FnGetObj = nullptr;
        FnGetTime g_FnGetTime = nullptr;

        bool g_ConfigInitialized = false;
        bool g_Enabled = false;
        bool g_HooksInstalled = false;
        bool g_Active = false;
        volatile long g_LogBudget = 96;

        enum class Phase : int
        {
            None,
            Fire,       // deployed in reach: stock DoAttack runs
            Hold,       // deployed, target just left reach: waiting to pack up
            Packup,     // pack-up requested
            Drive,      // driving with our GotoTask
            Deploy,     // in reach, deploy requested
            Arrived,    // goto finished out of reach: stock gives its verdict
        };

        const wchar_t* PhaseName(Phase p)
        {
            switch (p)
            {
            case Phase::Fire: return L"fire";
            case Phase::Hold: return L"hold";
            case Phase::Packup: return L"packup";
            case Phase::Drive: return L"drive";
            case Phase::Deploy: return L"deploy";
            case Phase::Arrived: return L"arrived";
            default: return L"none";
            }
        }

        struct ApproachTrack
        {
            uint32_t target = 0;
            void* task = nullptr;          // our GotoTask at process+0x38
            float taskTargetPos[3] = {};
            float taskCreatedAt = 0.0f;
            bool everInReach = false;
            bool beyondReach = false;
            float beyondReachSince = 0.0f;
            Phase phase = Phase::None;
            float lastTime = -1.0e9f;
            bool suppressLogged = false;
        };
        std::unordered_map<uintptr_t, ApproachTrack> g_Tracks;

        // ---- small fault-safe helpers (no C++ objects, so __try is legal) ----

        float NowSeconds()
        {
            if (!g_FnGetTime)
                return 0.0f;
            __try
            {
                return g_FnGetTime();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0.0f;
            }
        }

        void* SafeGetObj(uint32_t handle)
        {
            if (!g_FnGetObj || handle == 0)
                return nullptr;
            __try
            {
                return g_FnGetObj(handle);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        bool ReadInt(const void* base, size_t offset, int& out)
        {
            if (reinterpret_cast<uintptr_t>(base) < 0x10000)
                return false;
            __try
            {
                out = *reinterpret_cast<const int*>(
                    static_cast<const uint8_t*>(base) + offset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void* ReadPtr(const void* base, size_t offset)
        {
            if (reinterpret_cast<uintptr_t>(base) < 0x10000)
                return nullptr;
            __try
            {
                return *reinterpret_cast<void* const*>(
                    static_cast<const uint8_t*>(base) + offset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        bool ReadFloat(const void* base, size_t offset, float& out)
        {
            if (reinterpret_cast<uintptr_t>(base) < 0x10000)
                return false;
            __try
            {
                out = *reinterpret_cast<const float*>(
                    static_cast<const uint8_t*>(base) + offset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void WriteField(void* base, size_t offset, uint32_t value)
        {
            if (reinterpret_cast<uintptr_t>(base) < 0x10000)
                return;
            __try
            {
                *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(base) + offset) = value;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        void WriteFloatField(void* base, size_t offset, float value)
        {
            if (reinterpret_cast<uintptr_t>(base) < 0x10000)
                return;
            __try
            {
                *reinterpret_cast<float*>(static_cast<uint8_t*>(base) + offset) = value;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        bool CraftSlotIs(void* craft, size_t slot, uint32_t expected)
        {
            void* vtable = ReadPtr(craft, 0);
            if (!vtable || expected == 0)
                return false;
            void* fn = ReadPtr(vtable, slot * sizeof(void*));
            return reinterpret_cast<uintptr_t>(fn) == expected;
        }

        bool CallCraftVoid(FnCraftVoid fn, void* craft)
        {
            if (!fn || !craft)
                return false;
            __try
            {
                fn(craft);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool RequestDeploy(void* craft)
        {
            return CraftSlotIs(craft, kCraftDeploySlot, g_CraftDeployAddr) &&
                   CallCraftVoid(g_FnCraftDeploy, craft);
        }

        // Craft::Packup on an undeployed craft cancels a pending Deploy
        // (patches.json CraftPackup), so it is safe in every deploy state.
        bool RequestPackup(void* craft)
        {
            return CraftSlotIs(craft, kCraftPackupSlot, g_CraftPackupAddr) &&
                   CallCraftVoid(g_FnCraftPackup, craft);
        }

        void ZeroDriveControls(void* craft)
        {
            void* controls = ReadPtr(craft, kCraftControlsOffset);
            for (size_t off = kControlsFirst; off <= kControlsLast; off += 4)
                WriteField(controls, off, 0);
        }

        void RefreshAttackTimeout(void* process, float now)
        {
            WriteFloatField(process, kProcessAttackTimeoutOffset, now + kAttackTimeoutSeconds);
        }

        bool CallReach(void* weapon, const float* pos, bool& reachable)
        {
            if (!g_FnReach || !weapon)
                return false;
            __try
            {
                float time = 0.0f;
                reachable = g_FnReach(weapon, &time, pos, 1);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool CallInitGoto(void* process)
        {
            if (!g_FnInitGoto)
                return false;
            __try
            {
                g_FnInitGoto(process);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // -1 = fault, 0 = still going, 1 = done.
        int CallTaskDoneThenExecute(void* task)
        {
            void* vtable = ReadPtr(task, 0);
            auto done = reinterpret_cast<FnTaskBool>(ReadPtr(vtable, kTaskDoneSlot * sizeof(void*)));
            auto execute = reinterpret_cast<FnTaskVoid>(ReadPtr(vtable, kTaskExecuteSlot * sizeof(void*)));
            if (!done || !execute)
                return -1;
            __try
            {
                if (done(task))
                    return 1;
                execute(task);
                return 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1;
            }
        }

        // Deletes the task only while process+0x38 still holds it, the way
        // UnitProcess::EndGoto 0x005FB720 does (vt[0](1), then +0x38 = 0).
        void DeleteOwnedTask(void* process, void* task)
        {
            if (!task || ReadPtr(process, kProcessTaskOffset) != task)
                return;
            void* vtable = ReadPtr(task, 0);
            auto del = reinterpret_cast<FnTaskDelete>(ReadPtr(vtable, kTaskDeleteSlot * sizeof(void*)));
            WriteField(process, kProcessTaskOffset, 0);
            if (!del)
                return;
            __try
            {
                del(task, 1);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        bool IsLocalPlayerTeamCraft(void* craft)
        {
            int craftTeam = -1;
            int playerTeam = -1;
            void* player = TryGetHeadlightPlayerObject();
            return player &&
                   ReadInt(craft, kGameObjectActualTeamOffset, craftTeam) &&
                   ReadInt(player, kGameObjectActualTeamOffset, playerTeam) &&
                   playerTeam > 0 && craftTeam == playerTeam;
        }

        // First mounted weapon whose class signature is 'MORT' and whose
        // ordnance has a shot speed (what 0x0056AF20 reads).
        void* FindMortarWeapon(void* craft)
        {
            void* carrier = ReadPtr(craft, kCraftCarrierOffset);
            int mask = 0;
            if (!carrier || !ReadInt(carrier, kCarrierMaskOffset, mask))
                return nullptr;
            for (int i = 0; i < kCarrierWeaponCount; ++i)
            {
                if ((mask & (1 << i)) == 0)
                    continue;
                void* weapon = ReadPtr(carrier, kCarrierWeaponsOffset + i * sizeof(void*));
                if (!weapon)
                    continue;
                int sig = 0;
                float speed = 0.0f;
                void* cls = ReadPtr(weapon, kWeaponClassOffset);
                void* ord = ReadPtr(weapon, kWeaponOrdnanceOffset);
                if (cls && ReadInt(cls, kClassSignatureOffset, sig) && sig == kMortarSignature &&
                    ord && ReadFloat(ord, kOrdnanceSpeedOffset, speed) && speed > 0.0f)
                    return weapon;
            }
            return nullptr;
        }

        enum class Gate : int
        {
            Pass,
            NotHowitzer,
            NotPlayerTeam,
            NotAttackOrder,
            NoTarget,
            TargetGone,
            NoMortar,
            NoPosition,
            ReachFault,
        };

        const wchar_t* GateName(Gate g)
        {
            switch (g)
            {
            case Gate::Pass: return L"pass";
            case Gate::NotHowitzer: return L"not a Howitzer craft";
            case Gate::NotPlayerTeam: return L"not the player's team";
            case Gate::NotAttackOrder: return L"current command is not ATTACK";
            case Gate::NoTarget: return L"no target handle";
            case Gate::TargetGone: return L"target gone";
            case Gate::NoMortar: return L"no MORT weapon";
            case Gate::NoPosition: return L"no position";
            default: return L"reach test faulted";
            }
        }

        struct ApproachContext
        {
            void* craft = nullptr;
            uint32_t target = 0;
            int deployState = -1;
            float craftPos[3] = {};
            float targetPos[3] = {};
            bool reachDeploy = false;
            bool reachHold = false;
        };

        bool ReachWithMargin(void* weapon, const ApproachContext& ctx, float factor, bool& reachable)
        {
            float pos[3] = {
                ctx.craftPos[0] + (ctx.targetPos[0] - ctx.craftPos[0]) * factor,
                ctx.targetPos[1],
                ctx.craftPos[2] + (ctx.targetPos[2] - ctx.craftPos[2]) * factor,
            };
            return CallReach(weapon, pos, reachable);
        }

        Gate ReadApproachContext(void* process, ApproachContext& ctx)
        {
            ctx.craft = ReadPtr(process, kProcessCraftOffset);
            if (!ctx.craft || reinterpret_cast<uintptr_t>(ReadPtr(ctx.craft, 0)) != g_HowitzerVtableAddr)
                return Gate::NotHowitzer;
            if (!IsLocalPlayerTeamCraft(ctx.craft))
                return Gate::NotPlayerTeam;
            int command = 0;
            if (!ReadInt(ctx.craft, kCraftCurrentCommandOffset, command) || command != kCmdAttack)
                return Gate::NotAttackOrder;
            int handle = 0;
            if (!ReadInt(process, kProcessTargetHandleOffset, handle) || handle == 0)
                return Gate::NoTarget;
            ctx.target = static_cast<uint32_t>(handle);
            void* target = SafeGetObj(ctx.target);
            if (!target)
                return Gate::TargetGone;
            void* weapon = FindMortarWeapon(ctx.craft);
            if (!weapon)
                return Gate::NoMortar;
            if (!ReadInt(ctx.craft, kCraftDeployStateOffset, ctx.deployState) ||
                !TryGetGameObjectWorldPosition(ctx.craft, ctx.craftPos) ||
                !TryGetGameObjectWorldPosition(target, ctx.targetPos))
                return Gate::NoPosition;
            if (!ReachWithMargin(weapon, ctx, kDeployReachFactor, ctx.reachDeploy) ||
                !ReachWithMargin(weapon, ctx, kHoldReachFactor, ctx.reachHold))
                return Gate::ReachFault;
            return Gate::Pass;
        }

        float HorizontalDistance(const float* a, const float* b)
        {
            const float dx = a[0] - b[0];
            const float dz = a[2] - b[2];
            return std::sqrt(dx * dx + dz * dz);
        }

        bool TakeLogBudget()
        {
            return InterlockedDecrement(&g_LogBudget) >= 0;
        }

        // Change-only decision log.
        void SetPhase(ApproachTrack& track, Phase phase, void* process, const ApproachContext& ctx)
        {
            if (track.phase == phase)
                return;
            if (TakeLogBudget())
                Log(L"[HOWAPPR] %ls -> %ls process=0x%08X craft=0x%08X target=0x%08X dist=%.1f reach=%d/%d deploy=%d\n",
                    PhaseName(track.phase), PhaseName(phase),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(process)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ctx.craft)),
                    ctx.target, HorizontalDistance(ctx.craftPos, ctx.targetPos),
                    ctx.reachDeploy ? 1 : 0, ctx.reachHold ? 1 : 0, ctx.deployState);
            track.phase = phase;
        }

        // Last gate result per process, so two howitzers in different gates
        // do not log alternately every tick.
        std::unordered_map<uintptr_t, Gate> g_LastGates;

        void LogGateChange(void* process, Gate gate)
        {
            const uintptr_t key = reinterpret_cast<uintptr_t>(process);
            auto it = g_LastGates.find(key);
            if (it != g_LastGates.end() && it->second == gate)
                return;
            if (it == g_LastGates.end() && gate == Gate::Pass)
                return;
            if (g_LastGates.size() > kTrackLimit)
                g_LastGates.clear();
            g_LastGates[key] = gate;
            // Enemy and non-howitzer processes are the common case; stay quiet.
            if (gate == Gate::Pass || gate == Gate::NotHowitzer || gate == Gate::NotPlayerTeam)
                return;
            if (TakeLogBudget())
                Log(L"[HOWAPPR] process=0x%08X gate=%ls\n",
                    static_cast<uint32_t>(key), GateName(gate));
        }

        // Ends our part of the approach: our task goes, the drive controls
        // go back to zero.
        void StopDriving(void* process, void* craft, ApproachTrack& track)
        {
            if (!track.task)
                return;
            DeleteOwnedTask(process, track.task);
            track.task = nullptr;
            ZeroDriveControls(craft);
        }

        void DropTrack(void* process)
        {
            auto it = g_Tracks.find(reinterpret_cast<uintptr_t>(process));
            if (it == g_Tracks.end())
                return;
            if (it->second.task)
            {
                DeleteOwnedTask(process, it->second.task);
                ZeroDriveControls(ReadPtr(process, kProcessCraftOffset));
            }
            g_Tracks.erase(it);
        }

        // Returns true when it handled this tick (the stock body is skipped).
        bool ManageApproach(void* process)
        {
            ApproachContext ctx;
            const Gate gate = ReadApproachContext(process, ctx);
            LogGateChange(process, gate);
            if (gate != Gate::Pass)
            {
                // Target dead or order changed: stock DoAttack clears the
                // command and drops to idle (0x00475B30 lines 385-401).
                DropTrack(process);
                return false;
            }

            const uintptr_t key = reinterpret_cast<uintptr_t>(process);
            const float now = NowSeconds();
            if (g_Tracks.size() > kTrackLimit && g_Tracks.find(key) == g_Tracks.end())
            {
                // Only stale tracks go: a live attacking process refreshes its
                // track every tick, so a stale one left attack or died, and
                // its process is not touched.
                for (auto it = g_Tracks.begin(); it != g_Tracks.end();)
                {
                    if (now < it->second.lastTime || now - it->second.lastTime > kTrackMaxAgeSeconds)
                        it = g_Tracks.erase(it);
                    else
                        ++it;
                }
            }
            ApproachTrack& track = g_Tracks[key];
            if (track.target != ctx.target || now < track.lastTime ||
                now - track.lastTime > kTrackMaxAgeSeconds)
            {
                if (track.task)
                    DeleteOwnedTask(process, track.task);
                track = ApproachTrack();
                track.target = ctx.target;
            }
            track.lastTime = now;

            void* const liveTask = ReadPtr(process, kProcessTaskOffset);
            if (track.task && liveTask != track.task)
                track.task = nullptr; // replaced by someone else; not ours to delete

            if (ctx.deployState == kDeployStateDeploying || ctx.deployState == kDeployStateDeployed)
            {
                StopDriving(process, ctx.craft, track);
                if (ctx.reachHold)
                {
                    track.everInReach = true;
                    track.beyondReach = false;
                    SetPhase(track, Phase::Fire, process, ctx);
                    return false;
                }
                RefreshAttackTimeout(process, now);
                // Stock InitAttack deploys at once (0x00475AF0 line 13): a
                // target out of reach from the start packs up straight away.
                if (track.everInReach)
                {
                    if (!track.beyondReach)
                    {
                        track.beyondReach = true;
                        track.beyondReachSince = now;
                    }
                    if (now - track.beyondReachSince < kPackupDelaySeconds)
                    {
                        SetPhase(track, Phase::Hold, process, ctx);
                        return true;
                    }
                }
                // A refused packup hands the tick to stock (out of range),
                // so the howitzer never sits in attack doing nothing.
                if (!RequestPackup(ctx.craft))
                    return false;
                SetPhase(track, Phase::Packup, process, ctx);
                return true;
            }

            if (ctx.reachDeploy)
            {
                StopDriving(process, ctx.craft, track);
                RefreshAttackTimeout(process, now);
                if (ctx.deployState == kDeployStateUndeployed)
                {
                    ZeroDriveControls(ctx.craft);
                    if (!RequestDeploy(ctx.craft))
                        return false;
                    SetPhase(track, Phase::Deploy, process, ctx);
                }
                // Undeploying (3): wait for it to finish, then deploy.
                return true;
            }

            // Out of reach and packed (or packing): drive.
            bool repath = !track.task;
            if (track.task)
            {
                const float dx = ctx.targetPos[0] - track.taskTargetPos[0];
                const float dz = ctx.targetPos[2] - track.taskTargetPos[2];
                repath = dx * dx + dz * dz > kRepathDistanceSq &&
                         now - track.taskCreatedAt >= kRepathMinSeconds;
            }
            if (repath)
            {
                if (!track.task && liveTask)
                {
                    // A task we did not make (e.g. restored by a save load):
                    // leave the attack to stock.
                    if (TakeLogBudget())
                        Log(L"[HOWAPPR] process=0x%08X foreign task 0x%08X at +0x38; stock attack\n",
                            static_cast<uint32_t>(key),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(liveTask)));
                    return false;
                }
                StopDriving(process, ctx.craft, track);
                RequestPackup(ctx.craft);
                // UnitProcess::InitGoto 0x005FB500 builds a GotoTask to the
                // live target at +0x3C (lines 101-143) and stores it at +0x38.
                if (!CallInitGoto(process))
                    return false;
                track.task = ReadPtr(process, kProcessTaskOffset);
                if (!track.task)
                    return false;
                track.taskTargetPos[0] = ctx.targetPos[0];
                track.taskTargetPos[1] = ctx.targetPos[1];
                track.taskTargetPos[2] = ctx.targetPos[2];
                track.taskCreatedAt = now;
            }

            const int step = CallTaskDoneThenExecute(track.task);
            if (step != 0)
            {
                // Arrived (or faulted) and still out of reach: stock decides.
                StopDriving(process, ctx.craft, track);
                SetPhase(track, Phase::Arrived, process, ctx);
                return false;
            }
            RefreshAttackTimeout(process, now);
            SetPhase(track, Phase::Drive, process, ctx);
            return true;
        }

        void __fastcall ArtilleryFriendDoAttackHook(void* process, void* /*edx*/)
        {
            if (g_Active && ManageApproach(process))
                return;
            g_StockDoAttack(process);
        }

        void __fastcall ArtilleryFriendEndAttackHook(void* process, void* /*edx*/)
        {
            // Leaving the attack state: our GotoTask must not outlive it
            // (the next InitGoto would overwrite +0x38 without deleting).
            if (!g_Tracks.empty())
                DropTrack(process);
            g_StockEndAttack(process);
        }

        // ---- vtable install -----------------------------------------------

        struct SlotPlan
        {
            const wchar_t* label;
            uint32_t vtable;
            const char* rttiName;
            size_t slot;
            uint32_t original;
            void* hook;
        };

        bool SlotReady(const SlotPlan& p)
        {
            const uintptr_t slotAddress = p.vtable + p.slot * sizeof(void*);
            if (!VtableTypeNameMatches(p.vtable, p.rttiName))
            {
                Log(L"[HOWAPPR] %ls RTTI mismatch vtable=0x%08X; not installed\n",
                    p.label, p.vtable);
                return false;
            }
            void* current = nullptr;
            __try
            {
                current = *reinterpret_cast<void**>(slotAddress);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                current = nullptr;
            }
            if (current != p.hook && current != reinterpret_cast<void*>(p.original))
            {
                Log(L"[HOWAPPR] %ls slot mismatch slot=0x%08X current=0x%08X expected=0x%08X; not installed\n",
                    p.label, static_cast<uint32_t>(slotAddress),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)), p.original);
                return false;
            }
            return true;
        }

        bool InstallSlot(const SlotPlan& p)
        {
            const uintptr_t slotAddress = p.vtable + p.slot * sizeof(void*);
            void* current = nullptr;
            __try
            {
                current = *reinterpret_cast<void**>(slotAddress);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                current = nullptr;
            }
            if (current != p.hook && !WritePointerValue(slotAddress, p.hook))
            {
                Log(L"[HOWAPPR] Failed installing %ls hook slot=0x%08X\n",
                    p.label, static_cast<uint32_t>(slotAddress));
                return false;
            }
            Log(L"[HOWAPPR] %ls hook installed slot=0x%08X\n",
                p.label, static_cast<uint32_t>(slotAddress));
            return true;
        }

        void InitializeHowitzerAttackApproachConfig()
        {
            if (g_ConfigInitialized)
                return;
            g_ConfigInitialized = true;
            bool value = false;
            g_Enabled = TryGetUserConfigBool(kUserConfigSinglePlayerSection,
                                             "HowitzerAttackApproach", value) && value;
            Log(L"[HOWAPPR] Baseline enabled=%hs (SP-only)\n", g_Enabled ? "yes" : "no");
        }
    }

    void InstallHowitzerAttackApproachHooksIfPossible()
    {
        static bool s_tried = false;
        if (s_tried)
            return;
        s_tried = true;

        InitializeHowitzerAttackApproachConfig();
        if (!g_Enabled)
        {
            Log(L"[HOWAPPR] Disabled in openshim.ini; hooks not installed\n");
            return;
        }

        const HookEngine::EngineRow rows[] = {
            { "ArtilleryFriendVtable", &g_FriendVtableAddr },
            { "HowitzerVtable", &g_HowitzerVtableAddr },
            { "ArtilleryProcessDoAttack", &g_DoAttackAddr },
            { "GameObjectDeselect", &g_EndAttackAddr },
            { "UnitProcessInitGoto", &g_InitGotoAddr },
            { "WeaponBallisticReach", &g_ReachAddr },
            { "CraftDeploy", &g_CraftDeployAddr },
            { "CraftPackup", &g_CraftPackupAddr },
            { "GameObjectHandleGetObj", &g_GetObjAddr },
            { "GetGameTime", &g_GetTimeAddr },
        };
        if (!HookEngine::BindEngineRows("Howitzer attack approach", rows))
        {
            Log(L"[HOWAPPR] Engine rows did not bind; feature unavailable\n");
            return;
        }

        g_StockDoAttack = reinterpret_cast<FnProcessVoid>(g_DoAttackAddr);
        g_StockEndAttack = reinterpret_cast<FnProcessVoid>(g_EndAttackAddr);
        g_FnInitGoto = reinterpret_cast<FnProcessVoid>(g_InitGotoAddr);
        g_FnReach = reinterpret_cast<FnBallisticReach>(g_ReachAddr);
        g_FnCraftDeploy = reinterpret_cast<FnCraftVoid>(g_CraftDeployAddr);
        g_FnCraftPackup = reinterpret_cast<FnCraftVoid>(g_CraftPackupAddr);
        g_FnGetObj = reinterpret_cast<FnGetObj>(g_GetObjAddr);
        g_FnGetTime = reinterpret_cast<FnGetTime>(g_GetTimeAddr);

        const SlotPlan plans[] = {
            { L"ArtilleryFriend::EndAttack", g_FriendVtableAddr, ".?AVArtilleryFriend@@",
              kProcessEndAttackSlot, g_EndAttackAddr,
              reinterpret_cast<void*>(&ArtilleryFriendEndAttackHook) },
            { L"ArtilleryFriend::DoAttack", g_FriendVtableAddr, ".?AVArtilleryFriend@@",
              kProcessDoAttackSlot, g_DoAttackAddr,
              reinterpret_cast<void*>(&ArtilleryFriendDoAttackHook) },
        };

        // All or nothing: DoAttack without EndAttack would leak the task.
        for (const SlotPlan& p : plans)
        {
            if (!SlotReady(p))
            {
                Log(L"[HOWAPPR] Feature unavailable: %ls failed its check\n", p.label);
                return;
            }
        }
        bool all = true;
        for (const SlotPlan& p : plans)
            all = InstallSlot(p) && all;
        g_HooksInstalled = all;
        Log(L"[HOWAPPR] Howitzer attack approach %hs\n",
            all ? "installed" : "partially installed; feature stays off");
        RefreshHowitzerAttackApproachState();
    }

    void RefreshHowitzerAttackApproachState()
    {
        InitializeHowitzerAttackApproachConfig();
        const bool want = g_Enabled && g_HooksInstalled && IsSinglePlayerSession();
        if (want != g_Active)
        {
            g_Active = want;
            Log(L"[HOWAPPR] %hs\n", want ? "Active (SP-only)" : "Stood down");
        }
        if (!g_Active)
            g_Tracks.clear();
    }

    void ResetHowitzerAttackApproach()
    {
        // Mission end: the processes (and their tasks) are gone with the world.
        g_Tracks.clear();
        g_LastGates.clear();
        g_LogBudget = 96;
        RefreshHowitzerAttackApproachState();
    }

    bool IsHowitzerApproachProcess(void* process)
    {
        if (!g_Active || g_Tracks.empty())
            return false;
        auto it = g_Tracks.find(reinterpret_cast<uintptr_t>(process));
        if (it == g_Tracks.end())
            return false;
        const ApproachTrack& t = it->second;
        if (t.phase != Phase::Drive && t.phase != Phase::Packup &&
            t.phase != Phase::Hold && t.phase != Phase::Deploy)
            return false;
        const float now = NowSeconds();
        return now >= t.lastTime && now - t.lastTime <= kTrackMaxAgeSeconds;
    }

    void NoteHowitzerApproachRetargetSuppressed(void* process)
    {
        auto it = g_Tracks.find(reinterpret_cast<uintptr_t>(process));
        if (it == g_Tracks.end() || it->second.suppressLogged)
            return;
        it->second.suppressLogged = true;
        if (TakeLogBudget())
            Log(L"[HOWAPPR] process=0x%08X SNIP retaliation retarget suppressed; keeps target=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(process)), it->second.target);
    }
}
