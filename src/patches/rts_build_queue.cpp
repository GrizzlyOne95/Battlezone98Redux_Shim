// rts_build_queue.cpp
// BZR Open Shim - [Gameplay] RtsBuildQueue (default off, single player):
// a build queue for the Recycler and Factory.
//
// While a Recycler or Factory is building (or already holds a queue), picking
// another item in its build menu appends it to that producer's queue (10
// deep, 16 producers) instead of replacing the build. Shift+pick (Ctrl clear)
// removes the last queued entry of that item; a pick into a full queue plays
// the refuse sound. A 4 Hz drain on the frame thread issues the next entry
// through the stock SetActiveMode when the producer is idle and the team can
// pay (the stock StartBuild test), so scrap is charged when each item
// starts, as stock does. The queue is cleared on mission reset, when the
// option turns off, in a network game and when the producer is gone.
// producer_badges.cpp shows "+N" and "waiting for scrap" through
// RtsBuildQueueBadgeQuery.
//
// Hook point: ProducerSetActiveModeHook (producer_build_menu.cpp) calls
// RtsBuildQueueOnPick between PRODMENU's own mode handling and the stock
// Producer::SetActiveMode 0x005AEAB0. Evidence and limits:
// Docs/RTS_BUILD_QUEUE.md.
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "hook_engine.h"
#include "patcher.h"
#include "rts_build_queue_policy.h"
#include "scene_mutation_drain.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdarg>
#include <cstdint>
#include <cstring>
#include <mutex>

namespace BZROpenShim::Hooks
{
    namespace
    {
        namespace Q = RtsBuildQueuePolicy;

        using FnGetObj = void*(__cdecl*)(uint32_t handle);
        using FnGetHandle = uint32_t(__thiscall*)(void* obj);
        using FnCost = int(__cdecl*)(int teamNumber, void* cls);
        using FnPlaySound = int(__cdecl*)(const char* filename, uint32_t, uint32_t, uint32_t);

        constexpr size_t kBuildClassOffset = 0x300;
        constexpr size_t kClassOdfOffset = 0x30;
        constexpr size_t kTeamNumberOffset = 0x174; // kGameObjectActualTeamOffset
        constexpr size_t kTeamPtrOffset = 0x17C;
        constexpr size_t kTeamScrapOffset = 0x16C;  // xor 0x33333333
        constexpr uint32_t kScrapXor = 0x33333333;
        constexpr size_t kTeamPilotsOffset = 0x174;
        constexpr size_t kOwnershipOffset = 0x80; // == 2: network replica
        constexpr uint8_t kReplicaOwnership = 2;
        constexpr size_t kObj76FlagsOffset = 0x14;
        constexpr uint32_t kObj76DeadFlag = 0x200;
        constexpr size_t kCurrentCommandOffset = 0xCC; // GameObject nextCmd.what (producer_rally_points.cpp)
        constexpr int kCmdBuild = 0x15;
        constexpr size_t kSetActiveModeVtableOffset = 0x2C; // slot 11
        constexpr int kMaxInstallAttempts = 40;
        constexpr const char* kRefuseSound = "mnu_buzz.wav";

        // Engine rows (patch thread, then read-only).
        uint32_t g_GetObjAddr = 0;
        uint32_t g_ScrapCostAddr = 0;
        uint32_t g_PilotCostAddr = 0;
        uint32_t g_FirstEmptySlotAddr = 0; // Team::FirstEmptySlot(min, max), thiscall
        uint32_t g_MultiAddr = 0;    // cmd_multi byte
        uint32_t g_HeldModsAddr = 0; // the game's held-key dword with the modifier bits
        uint32_t g_RecyclerVtable = 0;
        uint32_t g_FactoryVtable = 0;

        FnGetObj g_FnGetObj = nullptr;
        FnCost g_FnScrapCost = nullptr;
        FnCost g_FnPilotCost = nullptr;
        FnPlaySound g_FnPlaySound = nullptr;

        bool g_RowsBound = false;
        bool g_ConfigRead = false;
        bool g_Enabled = false;
        std::atomic<bool> g_Active{ false };
        std::atomic<int> g_QueuedProducers{ 0 };
        ULONGLONG g_LastDrainMs = 0;
        volatile long g_LogBudget = 96;
        volatile long g_InstallLogBudget = 16;

        std::mutex g_TableMutex;
        Q::Table g_Table;

        void LogBudgeted(const wchar_t* fmt, ...)
        {
            if (InterlockedDecrement(&g_LogBudget) < 0)
                return;
            wchar_t buffer[384];
            va_list args;
            va_start(args, fmt);
            _vsnwprintf_s(buffer, _TRUNCATE, fmt, args);
            va_end(args);
            Log(L"%ls", buffer);
        }

        // ---- fault-safe engine access ------------------------------------------

        bool ReadBytes(uintptr_t address, void* out, size_t size)
        {
            if (address < 0x10000)
                return false;
            __try
            {
                std::memcpy(out, reinterpret_cast<const void*>(address), size);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ReadU32(uintptr_t address, uint32_t& out)
        {
            return ReadBytes(address, &out, sizeof(out));
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

        uint32_t SafeGetHandle(void* obj)
        {
            const auto fn = reinterpret_cast<FnGetHandle>(g_GameObjectGetHandleAddr);
            if (!fn || !obj)
                return 0;
            __try
            {
                return fn(obj);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        bool SafeCost(FnCost fn, int team, uint32_t cls, int& out)
        {
            if (!fn)
                return false;
            __try
            {
                out = fn(team, reinterpret_cast<void*>(static_cast<uintptr_t>(cls)));
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeSetActiveMode(void* obj, int mode)
        {
            if (!g_BzrFn_ProducerSetActiveMode || !obj)
                return false;
            __try
            {
                g_BzrFn_ProducerSetActiveMode(obj, mode);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void SafePlayRefuse()
        {
            if (!g_FnPlaySound)
                return;
            __try
            {
                g_FnPlaySound(kRefuseSound, 0, 0, 0);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        // Recycler or Factory (the Armory and the rig are not queued).
        bool IsQueuedProducer(void* obj)
        {
            uint32_t vtable = 0;
            return obj && ReadU32(reinterpret_cast<uintptr_t>(obj), vtable) && vtable != 0 &&
                   (vtable == g_RecyclerVtable || vtable == g_FactoryVtable);
        }

        // The user's team number. False while there is no player object (a
        // load or a transition): callers must then neither queue nor clear.
        bool ReadPlayerTeam(uint32_t& playerTeam)
        {
            const uintptr_t slot = EngineGlobals::UserObjectSlot();
            uint32_t player = 0;
            return slot && ReadU32(slot, player) && player != 0 &&
                   ReadU32(static_cast<uintptr_t>(player) + kGameObjectActualTeamOffset, playerTeam);
        }

        // Live, local and the player's: not a network replica, not flagged
        // dead (obj76 +0xF4 -> +0x14 bit 0x200), team == playerTeam.
        bool IsLiveOwnProducer(void* obj, uint32_t playerTeam)
        {
            if (!IsQueuedProducer(obj))
                return false;
            const uintptr_t base = reinterpret_cast<uintptr_t>(obj);
            uint8_t ownership = 0;
            uint32_t obj76 = 0;
            uint32_t team = 0;
            if (!ReadBytes(base + kOwnershipOffset, &ownership, 1) || ownership == kReplicaOwnership ||
                !ReadU32(base + kGameObjectObjOffset, obj76) || !ReadU32(base + kGameObjectActualTeamOffset, team))
                return false;
            if (obj76 != 0)
            {
                uint32_t flags = 0;
                if (!ReadU32(obj76 + kObj76FlagsOffset, flags) || (flags & kObj76DeadFlag) != 0)
                    return false;
            }
            return team == playerTeam;
        }

        // Shift down (the game's held-key state, bit 0x400000 of the 4th held
        // dword) and the stock multi-select modifier (cmd_multi) clear, as
        // rts_order_queue.cpp.
        constexpr uint32_t kHeldShiftBit = 0x400000;
        bool ModifierHeld()
        {
            uint32_t held = 0;
            if (g_HeldModsAddr == 0 || !ReadU32(g_HeldModsAddr, held) || (held & kHeldShiftBit) == 0)
                return false;
            uint8_t multi = 0;
            return g_MultiAddr != 0 && ReadBytes(g_MultiAddr, &multi, 1) && multi == 0;
        }

        uint32_t BuildClassOf(void* obj)
        {
            uint32_t cls = 0;
            ReadU32(reinterpret_cast<uintptr_t>(obj) + kBuildClassOffset, cls);
            return cls;
        }

        // The stock StartBuild test (0x005AECB0) for `cls` on this producer's
        // team. False when anything is unreadable.
        bool Affordable(void* obj, uint32_t cls)
        {
            const uintptr_t base = reinterpret_cast<uintptr_t>(obj);
            uint32_t teamNumber = 0;
            uint32_t team = 0;
            uint32_t scrapRaw = 0;
            uint32_t pilots = 0;
            int scrapCost = 0;
            int pilotCost = 0;
            if (!ReadU32(base + kTeamNumberOffset, teamNumber) || !ReadU32(base + kTeamPtrOffset, team) || team == 0 ||
                !ReadU32(static_cast<uintptr_t>(team) + kTeamScrapOffset, scrapRaw) ||
                !ReadU32(static_cast<uintptr_t>(team) + kTeamPilotsOffset, pilots) ||
                !SafeCost(g_FnScrapCost, static_cast<int>(teamNumber), cls, scrapCost) ||
                !SafeCost(g_FnPilotCost, static_cast<int>(teamNumber), cls, pilotCost))
                return false;
            return Q::CanAfford(scrapCost, static_cast<int>(scrapRaw ^ kScrapXor), pilotCost,
                                static_cast<int>(pilots));
        }

        // ---- the table (locked) -----------------------------------------------

        void UpdateQueuedProducers()
        {
            g_QueuedProducers.store(g_Table.ProducerCount(), std::memory_order_release);
        }

        void ClearProducer(uint32_t handle, Q::ClearReason reason)
        {
            int dropped = 0;
            {
                std::lock_guard<std::mutex> lock(g_TableMutex);
                dropped = g_Table.Clear(handle);
                UpdateQueuedProducers();
            }
            if (dropped > 0)
                LogBudgeted(L"[BUILDQ] cleared handle=0x%08X entries=%d (%hs)\n", handle, dropped,
                            Q::ReasonName(reason));
        }

        void ClearAllQueues(Q::ClearReason reason)
        {
            int dropped = 0;
            {
                std::lock_guard<std::mutex> lock(g_TableMutex);
                dropped = g_Table.ClearAll();
                UpdateQueuedProducers();
            }
            if (dropped > 0)
                LogBudgeted(L"[BUILDQ] cleared all entries=%d (%hs)\n", dropped, Q::ReasonName(reason));
        }

        // ---- install ----------------------------------------------------------

        // The pick hook is the PRODMENU SetActiveMode vtable hook, installed
        // only with [ProducerBuildMenus] Enabled: both vtables must hold it.
        bool PickHookLive()
        {
            const uint32_t hook = ProducerBuildMenuPatchTarget("Recycler SetActiveMode VTable Hook");
            uint32_t recycler = 0;
            uint32_t factory = 0;
            return hook != 0 && g_RecyclerVtable != 0 && g_FactoryVtable != 0 &&
                   ReadU32(g_RecyclerVtable + kSetActiveModeVtableOffset, recycler) && recycler == hook &&
                   ReadU32(g_FactoryVtable + kSetActiveModeVtableOffset, factory) && factory == hook;
        }

        // The hook also needs the stock SetActiveMode, bound by the PRODMENU
        // install.
        bool PartsReady()
        {
            return g_RowsBound && g_BzrFn_ProducerSetActiveMode != nullptr && PickHookLive();
        }

        void MarkParts()
        {
            if (PartsReady())
                ClearOptionHookFailed("RtsBuildQueue");
            else if (g_RowsBound && !PickHookLive())
                MarkOptionHookFailed("RtsBuildQueue", "Unavailable: needs [ProducerBuildMenus] Enabled = 1");
            else
                MarkOptionHookFailed("RtsBuildQueue",
                                     "Unavailable: the build queue did not hook on this game build (see openshim.log).");
        }

        void InstallParts()
        {
#if defined(_M_IX86)
            if (g_RowsBound)
                return;
            const HookEngine::EngineRow rows[] = {
                { "GameObjectHandleGetObj", &g_GetObjAddr },
                { "BuildScrapCost", &g_ScrapCostAddr },
                { "BuildPilotCost", &g_PilotCostAddr },
                { "TeamFirstEmptySlot", &g_FirstEmptySlotAddr },
                { "CommandMenuUnitBranchInput", &g_MultiAddr },
                { "InputHeldModifierKeys", &g_HeldModsAddr },
                { "RecyclerVtable", &g_RecyclerVtable },
                { "FactoryVtable", &g_FactoryVtable },
            };
            // The refuse sound is optional (SafePlayRefuse tolerates null).
            const uint32_t sound = HookEngine::ResolveNamedAddress("PlayGlobalSound");
            if (g_GameObjectGetHandleAddr != 0 && HookEngine::BindEngineRows("RTS build queue", rows))
            {
                g_RowsBound = true;
                g_FnGetObj = reinterpret_cast<FnGetObj>(g_GetObjAddr);
                g_FnScrapCost = reinterpret_cast<FnCost>(g_ScrapCostAddr);
                g_FnPilotCost = reinterpret_cast<FnCost>(g_PilotCostAddr);
                g_FnPlaySound = sound != 0 ? reinterpret_cast<FnPlaySound>(sound) : nullptr;
                Log(L"[BUILDQ] rows bound (scrap cost 0x%08X, pilot cost 0x%08X)\n", g_ScrapCostAddr, g_PilotCostAddr);
            }
            else if (InterlockedDecrement(&g_InstallLogBudget) >= 0)
                Log(L"[BUILDQ] engine rows did not bind; build queue inert\n");
#endif
        }

        void ReadConfig()
        {
            bool value = false;
            g_Enabled = TryGetUserConfigBool("Gameplay", "RtsBuildQueue", value) ? value : false;
            g_ConfigRead = true;
        }

        // ---- the drain ---------------------------------------------------------

        void DrainOnce(ULONGLONG now)
        {
            // No player object (load/transition): skip the pass, clear nothing.
            uint32_t playerTeam = 0;
            if (!ReadPlayerTeam(playerTeam))
                return;
            uint32_t handles[Q::kMaxProducers];
            int count = 0;
            {
                std::lock_guard<std::mutex> lock(g_TableMutex);
                for (int i = 0; i < Q::kMaxProducers; ++i)
                {
                    const uint32_t h = g_Table.HandleAt(i);
                    if (h == 0)
                        break;
                    handles[count++] = h;
                }
            }
            for (int i = 0; i < count; ++i)
            {
                const uint32_t handle = handles[i];
                void* const obj = SafeGetObj(handle);
                if (!obj || !IsLiveOwnProducer(obj, playerTeam))
                {
                    ClearProducer(handle, Q::ClearReason::Dead);
                    continue;
                }
                int depth = 0;
                uint32_t front = 0;
                bool hasIssued = false;
                uint64_t lastIssue = 0;
                {
                    std::lock_guard<std::mutex> lock(g_TableMutex);
                    depth = g_Table.Depth(handle);
                    front = g_Table.Front(handle);
                    hasIssued = g_Table.Issued(handle, lastIssue);
                }
                if (depth <= 0 || front == 0)
                    continue;
                const uint32_t buildClass = BuildClassOf(obj);
                if (buildClass != 0)
                    continue; // still building; nothing to compute
                // Only on an idle or build command; anything else is another order.
                int command = -1;
                uint32_t rawCommand = 0;
                if (ReadU32(reinterpret_cast<uintptr_t>(obj) + kCurrentCommandOffset, rawCommand))
                    command = static_cast<int>(rawCommand);
                if (command != 0 && command != kCmdBuild)
                    continue;
                if (!Q::DrainDue(depth, buildClass, Affordable(obj, front), hasIssued, lastIssue, now))
                    continue;
                {
                    std::lock_guard<std::mutex> lock(g_TableMutex);
                    g_Table.PopFront(handle, now);
                    UpdateQueuedProducers();
                }
                // The original, not the hook: the entry must not queue again.
                const bool ok = SafeSetActiveMode(obj, static_cast<int>(front));
                LogBudgeted(L"[BUILDQ] issued handle=0x%08X class=0x%08X left=%d%hs\n", handle, front, depth - 1,
                            ok ? "" : " FAILED");
            }
        }
    }

    // ---- public ----------------------------------------------------------------

    void ReloadRtsBuildQueueConfig()
    {
        ReadConfig();
        RefreshRtsBuildQueueState();
    }

    // Patch thread, retried from InstallAiTuningHooksIfPossible.
    void InstallRtsBuildQueueIfPossible()
    {
        static bool s_done = false;
        static int s_attempts = 0;
        if (s_done)
            return;
        if (!g_ConfigRead)
            ReadConfig();
        ++s_attempts;
        InstallParts();
        MarkParts();
        if (PartsReady() || s_attempts >= kMaxInstallAttempts)
        {
            s_done = true;
            Log(L"[BUILDQ] install %hs after %d attempt(s): rows %hs, stock SetActiveMode %hs\n",
                PartsReady() ? "complete" : "gave up", s_attempts, g_RowsBound ? "yes" : "no",
                g_BzrFn_ProducerSetActiveMode ? "yes" : "no");
        }
        RefreshRtsBuildQueueState();
    }

    // Config reload, mission gate reconcile (every 250 ms) and install: active
    // while the option is on, every part is in place and the session is
    // single player; anything else drops the queues.
    void RefreshRtsBuildQueueState()
    {
        if (!g_ConfigRead)
            ReadConfig();
        const bool ready = PartsReady();
        static int s_marked = -1;
        if (s_marked != (ready ? 1 : 0))
        {
            s_marked = ready ? 1 : 0;
            MarkParts();
        }
        const bool sp = IsSinglePlayerSession();
        const bool want = g_Enabled && ready && sp;
        const bool was = g_Active.exchange(want, std::memory_order_acq_rel);
        if (was != want)
            Log(L"[BUILDQ] active=%d (option %d, hooks %d, single player %d)\n", want ? 1 : 0, g_Enabled ? 1 : 0,
                ready ? 1 : 0, sp ? 1 : 0);
        if (!want)
            ClearAllQueues(g_Enabled && ready && !sp ? Q::ClearReason::Multiplayer : Q::ClearReason::OptionOff);
    }

    // Mission end / load: handles of the old world must never reach the next.
    void ResetRtsBuildQueue()
    {
        ClearAllQueues(Q::ClearReason::Reset);
        g_LastDrainMs = 0;
        g_LogBudget = 96;
        RefreshRtsBuildQueueState();
    }

    void TickRtsBuildQueue()
    {
        if (!g_Active.load(std::memory_order_acquire) || g_QueuedProducers.load(std::memory_order_acquire) == 0)
            return;
        if (!InsideRenderQueueHookWithDeferral())
            RunRtsBuildQueue();
    }

    // Frame thread (RunDeferredSceneMutations, or the world render tick when
    // the drain is not installed); the stock SetActiveMode never runs
    // anywhere else.
    void RunRtsBuildQueue() noexcept
    {
        try
        {
            if (!g_Active.load(std::memory_order_acquire) || g_QueuedProducers.load(std::memory_order_acquire) == 0)
                return;
            const ULONGLONG now = GetTickCount64();
            if (now - g_LastDrainMs < Q::kDrainIntervalMs)
                return;
            g_LastDrainMs = now;
            if (!RtsCommandsWorldActive())
                return;
            DrainOnce(now);
        }
        catch (...)
        {
            LogBudgeted(L"[BUILDQ] the drain threw; skipped\n");
        }
    }

    // Called by ProducerSetActiveModeHook for a build pick (mode >= 0x1b, the
    // GameObjectClass pointer) on a Recycler/Factory, after PRODMENU's own
    // modes. True: handled, the stock pick must not run.
    namespace
    {
        using FnFirstEmptySlot = int(__thiscall*)(void* team, int minSlot, int maxSlot);
        constexpr size_t kDeployStateOffset = 0x228; // 2: deployed (Producer::UpdateModeList)
        constexpr size_t kModeListOffset = 0x1A4;
        constexpr size_t kModeListEnabledOffset = 0x2C; // bit per slot (ModeList::SetMode 0x0046FA60)
        constexpr size_t kClassMinSlotOffset = 0x13C;
        constexpr size_t kClassMaxSlotOffset = 0x140;

        // The stock unit-cap part of the build-entry gate (FUN_005ae660.c lines 69-74).
        bool HasFreeUnitSlot(void* obj, uint32_t cls)
        {
            uint32_t minSlot = 0, maxSlot = 0, team = 0;
            if (!ReadU32(cls + kClassMinSlotOffset, minSlot) || !ReadU32(cls + kClassMaxSlotOffset, maxSlot))
                return false;
            if (static_cast<int>(minSlot) == -1 || static_cast<int>(maxSlot) == -1)
                return true;
            if (!ReadU32(reinterpret_cast<uintptr_t>(obj) + kTeamPtrOffset, team) || team < 0x10000)
                return false;
            void* const teamPtr = reinterpret_cast<void*>(static_cast<uintptr_t>(team));
            __try
            {
                // OffenseOverflow's gate, so ExtendedUnitCap opens it as the stock call site sees it.
                const int gate = OffenseOverflowBuildGate(teamPtr, static_cast<int>(minSlot), static_cast<int>(maxSlot),
                                                          reinterpret_cast<void*>(static_cast<uintptr_t>(cls)));
                if (gate != kOffenseOverflowGateUnbound)
                    return gate != -1;
                return g_FirstEmptySlotAddr != 0 &&
                       reinterpret_cast<FnFirstEmptySlot>(g_FirstEmptySlotAddr)(teamPtr, static_cast<int>(minSlot),
                                                                                static_cast<int>(maxSlot)) != -1;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }
    }

    // After Producer::UpdateModeList (ProducerUpdateModeListHook). Stock greys
    // every build entry while the producer is building (FUN_005ae660.c line 68,
    // FUN_004723d0 = +0x300 != 0), so a pick could never reach the queue. While
    // building, enable each class entry that has a free unit slot; the drain
    // waits for scrap and pilots before it issues.
    void RtsBuildQueueAfterUpdateModeList(void* self)
    {
        uint32_t playerTeam = 0, state = 0, enabled = 0;
        if (!g_Active.load(std::memory_order_acquire) || !ReadPlayerTeam(playerTeam) ||
            !IsLiveOwnProducer(self, playerTeam) || BuildClassOf(self) == 0)
            return;
        const uintptr_t modeList = reinterpret_cast<uintptr_t>(self) + kModeListOffset;
        if (!ReadU32(reinterpret_cast<uintptr_t>(self) + kDeployStateOffset, state) || state != 2 ||
            !ReadU32(modeList + kModeListEnabledOffset, enabled))
            return;
        uint32_t updated = enabled;
        for (int slot = 1; slot <= 9; ++slot)
        {
            uint32_t mode = 0;
            if ((updated & (1u << slot)) != 0 || !ReadU32(modeList + slot * 4, mode) || mode < 0x10000 ||
                IsProducerMenuStubMode(mode) || !HasFreeUnitSlot(self, mode))
                continue;
            updated |= 1u << slot;
        }
        if (updated != enabled)
        {
            __try
            {
                *reinterpret_cast<uint32_t*>(modeList + kModeListEnabledOffset) = updated;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }
    }

    bool RtsBuildQueueOnPick(void* self, int mode)
    {
        uint32_t playerTeam = 0;
        if (!g_Active.load(std::memory_order_acquire) || !ReadPlayerTeam(playerTeam) ||
            !IsLiveOwnProducer(self, playerTeam))
            return false;
        const uint32_t cls = static_cast<uint32_t>(mode);
        const uint32_t handle = SafeGetHandle(self);
        if (handle == 0 || cls < 0x10000)
            return false;
        const bool shift = ModifierHeld();
        const uint32_t buildClass = BuildClassOf(self);
        Q::PickAction action = Q::PickAction::Stock;
        int depth = 0;
        int result = 0;
        {
            std::lock_guard<std::mutex> lock(g_TableMutex);
            depth = g_Table.Depth(handle);
            action = Q::PlanPick(true, shift, Q::IsBusy(buildClass, depth, g_Table.RecentlyIssued(handle, GetTickCount64())),
                                 depth, g_Table.Contains(handle, cls));
            if (action == Q::PickAction::Enqueue)
                result = g_Table.Push(handle, cls); // 0: all 16 producer slots taken
            else if (action == Q::PickAction::RemoveLast)
                result = g_Table.RemoveLast(handle, cls);
            UpdateQueuedProducers();
        }
        switch (action)
        {
        case Q::PickAction::Enqueue:
            if (result == 0)
            {
                SafePlayRefuse();
                LogBudgeted(L"[BUILDQ] refused (no free producer slot) handle=0x%08X class=0x%08X\n", handle, cls);
                return true;
            }
            LogBudgeted(L"[BUILDQ] queued handle=0x%08X class=0x%08X depth=%d\n", handle, cls, result);
            return true;
        case Q::PickAction::Refuse:
            SafePlayRefuse();
            LogBudgeted(L"[BUILDQ] refused (full) handle=0x%08X class=0x%08X depth=%d\n", handle, cls, depth);
            return true;
        case Q::PickAction::RemoveLast:
            LogBudgeted(L"[BUILDQ] removed handle=0x%08X class=0x%08X left=%d\n", handle, cls, result);
            return true;
        case Q::PickAction::Stock:
            break;
        }
        return false;
    }

    // Called by ProducerSetActiveModeHook for the non-build orders (Stop,
    // Go, SetCommand modes 0x17, 0x3, 0xB) that passed PRODMENU's own modes: a
    // player order that replaces the build drops that producer's queue.
    void RtsBuildQueueOnPlainOrder(void* self)
    {
        if (!g_Active.load(std::memory_order_acquire) || g_QueuedProducers.load(std::memory_order_acquire) == 0 ||
            !IsQueuedProducer(self))
            return;
        const uint32_t handle = SafeGetHandle(self);
        if (handle != 0)
            ClearProducer(handle, Q::ClearReason::PlainOrder);
    }

    // Game thread (the badge scan and painter). False when the producer has
    // no queue. `waiting`: idle, non-empty queue, the next entry is not
    // affordable (scrap or pilots).
    bool RtsBuildQueueBadgeQuery(uint32_t handle, RtsBuildQueuePolicy::BadgeInfo& out)
    {
        out = RtsBuildQueuePolicy::BadgeInfo{};
        if (!g_Active.load(std::memory_order_acquire) || g_QueuedProducers.load(std::memory_order_acquire) == 0)
            return false;
        uint32_t front = 0;
        {
            std::lock_guard<std::mutex> lock(g_TableMutex);
            out.queued = g_Table.Depth(handle);
            front = g_Table.Front(handle);
        }
        if (out.queued <= 0 || front == 0)
            return false;
        char raw[Q::kOdfChars] = {};
        if (ReadBytes(static_cast<uintptr_t>(front) + kClassOdfOffset, raw, sizeof(raw)))
        {
            size_t i = 0;
            for (; i < Q::kOdfChars && raw[i] != '\0'; ++i)
                out.nextOdf[i] = raw[i];
            out.nextOdf[i] = '\0';
        }
        void* const obj = SafeGetObj(handle);
        out.waiting = obj && IsQueuedProducer(obj) && BuildClassOf(obj) == 0 && !Affordable(obj, front);
        return true;
    }
}
