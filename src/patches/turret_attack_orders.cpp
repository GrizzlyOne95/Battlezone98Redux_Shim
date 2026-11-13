// turret_attack_orders.cpp
// BZR Open Shim - let the player order a turret tank (class TurretTank, e.g.
// avturr/svturr) to attack, and let it close in on a target it cannot reach
// from where it stands. Single player only; [SinglePlayer]
// TurretAttackOrders, default ON. Addresses and behaviour:
// Docs/TURRET_ATTACK_ORDERS.md.
//
// Stock TurretTank::GetCommand has no enemy -> CMD_ATTACK branch, and
// TurretTank::UpdateModeList leaves menu slot 3 empty, so a turret can never
// be given ATTACK. When it does get one, TurretTankProcess::InitAttack deploys
// at once, and a deployed turret cannot move, so a target out of range is
// never engaged. This borrows the hovercraft answers for the first two and
// manages deploy/pack-up around the stock attack for the third.
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
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
        using FnGetCommand = int(__thiscall*)(void* craft, void* target);
        using FnCraftVoid = void(__thiscall*)(void* craft);
        using FnProcessVoid = void(__thiscall*)(void* process);
        using FnGetObj = void*(__cdecl*)(uint32_t handle);
        using FnGetTime = float(__cdecl*)();

        // Craft vtable slots (TurretTankVtable / HoverCraftVtable).
        constexpr size_t kCraftGetCommandSlot = 13;
        constexpr size_t kCraftUpdateModeListSlot = 23;
        constexpr size_t kCraftDeploySlot = 24;
        constexpr size_t kCraftPackupSlot = 25;
        // TurretTankProcess / Friend / Enemy vtable slots.
        constexpr size_t kProcessInitAttackSlot = 24;
        constexpr size_t kProcessDoAttackSlot = 26;

        constexpr int kCmdAttack = 4;
        constexpr int kModeSlotAttack = 3;
        constexpr int kModeTargetsAttack = 0xE;

        // Craft fields: +0x1A0 weapon carrier (non-zero = has a weapon),
        // +0x1A4 ModeList, +0x228 deploy state.
        constexpr size_t kCraftWeaponOffset = 0x1A0;
        constexpr size_t kCraftModeListOffset = 0x1A4;
        constexpr size_t kCraftDeployStateOffset = 0x228;
        constexpr int kDeployStateUndeployed = 0;
        constexpr int kDeployStateDeploying = 1;
        constexpr int kDeployStateDeployed = 2;

        // AiProcess fields.
        constexpr size_t kProcessCraftOffset = 0x34;
        constexpr size_t kProcessTaskOffset = 0x38;
        constexpr size_t kProcessTargetHandleOffset = 0x3C;
        constexpr size_t kProcessRangeSquaredOffset = 0x6C;

        // TurretAttack task fields.
        constexpr size_t kTaskNextStateOffset = 0x0C;
        constexpr size_t kTaskCraftOffset = 0x10;
        constexpr int kTaskNextStateChoose = 1;

        // Distances are 3D (the stock AbleToHit range test is 3D). Deploy at
        // once inside 0.9 x range, or after kStalledDeploySeconds packed up
        // inside range (the stock blast state can park the craft between 0.9x
        // and 1.0x). Pack up once the target has been beyond range for
        // kPackupDelaySeconds: a deployed turret out of range never fires.
        constexpr float kDeployRangeFactorSq = 0.81f;
        constexpr float kPackupDelaySeconds = 1.5f;
        constexpr float kStalledDeploySeconds = 1.0f;
        // An entry not ticked for this long is not a consecutive attack.
        constexpr float kTrackMaxAgeSeconds = 2.0f;
        constexpr size_t kTrackLimit = 256;

        uint32_t g_TurretTankVtableAddr = 0;
        uint32_t g_TurretTankGetCommandAddr = 0;
        uint32_t g_TurretTankUpdateModeListAddr = 0;
        uint32_t g_CraftGetCommandAddr = 0;
        uint32_t g_CraftDeployAddr = 0;
        uint32_t g_CraftPackupAddr = 0;
        uint32_t g_ModeListSetModeAddr = 0;
        uint32_t g_ProcessVtableAddr = 0;
        uint32_t g_FriendVtableAddr = 0;
        uint32_t g_EnemyVtableAddr = 0;
        uint32_t g_InitAttackAddr = 0;
        uint32_t g_DoAttackAddr = 0;
        uint32_t g_GetObjAddr = 0;
        uint32_t g_GetTimeAddr = 0;

        FnGetCommand g_StockTurretGetCommand = nullptr;
        FnGetCommand g_FnCraftGetCommand = nullptr;
        FnCraftVoid g_StockTurretUpdateModeList = nullptr;
        FnCraftVoid g_FnCraftDeploy = nullptr;
        FnCraftVoid g_FnCraftPackup = nullptr;
        FnModeListSetMode g_FnSetMode = nullptr;
        FnProcessVoid g_StockInitAttack = nullptr;
        FnProcessVoid g_StockDoAttack = nullptr;
        FnGetObj g_FnGetObj = nullptr;
        FnGetTime g_FnGetTime = nullptr;

        bool g_ConfigInitialized = false;
        bool g_Enabled = true;
        bool g_HooksInstalled = false;
        bool g_Active = false;
        volatile long g_ActionLogBudget = 32;

        struct AttackTrack
        {
            void* task = nullptr;
            uint32_t target = 0;
            bool deployRequested = false;
            bool beyondRange = false;
            float beyondRangeSince = 0.0f;
            bool packedInRange = false;
            float packedInRangeSince = 0.0f;
            float lastTime = -1.0e9f;
        };
        std::unordered_map<uintptr_t, AttackTrack> g_Tracks;

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

        // The craft's vtable slot still holds the stock Craft method we bound,
        // so calling the bound address is calling the craft's own override.
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

        bool RequestPackup(void* craft)
        {
            return CraftSlotIs(craft, kCraftPackupSlot, g_CraftPackupAddr) &&
                   CallCraftVoid(g_FnCraftPackup, craft);
        }

        // Writes nextState only when the task belongs to this craft.
        void ForceTaskChooseState(void* task, void* craft)
        {
            if (!task || ReadPtr(task, kTaskCraftOffset) != craft)
                return;
            __try
            {
                *reinterpret_cast<int*>(
                    static_cast<uint8_t*>(task) + kTaskNextStateOffset) = kTaskNextStateChoose;
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

        struct AttackContext
        {
            void* craft = nullptr;
            void* task = nullptr;
            uint32_t target = 0;
            float rangeSq = 0.0f;
            float distSq = 0.0f;
            int deployState = -1;
        };

        // Fills ctx for a player-team turret with a live target and a usable
        // range; false leaves the stock attack alone.
        bool ReadAttackContext(void* process, AttackContext& ctx)
        {
            ctx.craft = ReadPtr(process, kProcessCraftOffset);
            if (!ctx.craft || !IsLocalPlayerTeamCraft(ctx.craft))
                return false;
            int handle = 0;
            if (!ReadInt(process, kProcessTargetHandleOffset, handle) || handle == 0)
                return false;
            ctx.target = static_cast<uint32_t>(handle);
            void* target = SafeGetObj(ctx.target);
            if (!target)
                return false;
            if (!ReadFloat(process, kProcessRangeSquaredOffset, ctx.rangeSq) ||
                !(ctx.rangeSq > 0.0f))
                return false;
            if (!ReadInt(ctx.craft, kCraftDeployStateOffset, ctx.deployState))
                return false;
            float me[3] = {};
            float them[3] = {};
            if (!TryGetGameObjectWorldPosition(ctx.craft, me) ||
                !TryGetGameObjectWorldPosition(target, them))
                return false;
            const float dx = them[0] - me[0];
            const float dy = them[1] - me[1];
            const float dz = them[2] - me[2];
            ctx.distSq = dx * dx + dy * dy + dz * dz;
            ctx.task = ReadPtr(process, kProcessTaskOffset);
            return true;
        }

        void LogAction(const wchar_t* what, void* craft, const AttackContext& ctx)
        {
            if (InterlockedDecrement(&g_ActionLogBudget) < 0)
                return;
            Log(L"[TURRETATK] %ls craft=0x%08X target=0x%08X dist=%.1f range=%.1f state=%d\n",
                what, static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                ctx.target, std::sqrt(ctx.distSq), std::sqrt(ctx.rangeSq), ctx.deployState);
        }

        // ---- craft hooks --------------------------------------------------

        int __fastcall TurretTankGetCommandHook(void* self, void* /*edx*/, void* target)
        {
            const int r = g_StockTurretGetCommand(self, target);
            if (r != 0 || !g_Active || !g_FnCraftGetCommand)
                return r;
            return g_FnCraftGetCommand(self, target) == kCmdAttack ? kCmdAttack : r;
        }

        void __fastcall TurretTankUpdateModeListHook(void* self, void* /*edx*/)
        {
            g_StockTurretUpdateModeList(self);
            if (!g_Active || !g_FnSetMode)
                return;
            void* weapon = nullptr;
            __try
            {
                weapon = *reinterpret_cast<void**>(
                    static_cast<uint8_t*>(self) + kCraftWeaponOffset);
                g_FnSetMode(static_cast<uint8_t*>(self) + kCraftModeListOffset,
                            kModeSlotAttack, kModeTargetsAttack, weapon != nullptr ? 1 : 0);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        // ---- process hooks ------------------------------------------------

        void __fastcall TurretProcessInitAttackHook(void* process, void* /*edx*/)
        {
            g_StockInitAttack(process);
            g_Tracks.erase(reinterpret_cast<uintptr_t>(process));
            if (!g_Active)
                return;
            AttackContext ctx;
            if (!ReadAttackContext(process, ctx))
                return;
            // The stock InitAttack has just asked to deploy. Out of reach,
            // cancel that (or pack up) so the attack task can drive.
            if (ctx.distSq > ctx.rangeSq && RequestPackup(ctx.craft))
                LogAction(L"InitAttack out of range: pack up", ctx.craft, ctx);
        }

        void ManageAttackDeploy(void* process)
        {
            AttackContext ctx;
            const uintptr_t key = reinterpret_cast<uintptr_t>(process);
            if (!ReadAttackContext(process, ctx))
            {
                g_Tracks.erase(key);
                return;
            }

            if (g_Tracks.size() > kTrackLimit)
                g_Tracks.clear();
            const float now = NowSeconds();
            AttackTrack& track = g_Tracks[key];
            if (track.task != ctx.task || track.target != ctx.target ||
                now < track.lastTime || now - track.lastTime > kTrackMaxAgeSeconds)
            {
                track = AttackTrack();
                track.task = ctx.task;
                track.target = ctx.target;
            }
            track.lastTime = now;

            const float deploySq = ctx.rangeSq * kDeployRangeFactorSq;

            if (ctx.deployState == kDeployStateUndeployed)
            {
                track.beyondRange = false;
                bool deployNow = ctx.distSq <= deploySq;
                if (!deployNow && ctx.distSq <= ctx.rangeSq)
                {
                    if (!track.packedInRange)
                    {
                        track.packedInRange = true;
                        track.packedInRangeSince = now;
                    }
                    deployNow = now - track.packedInRangeSince >= kStalledDeploySeconds;
                }
                else if (!deployNow)
                {
                    track.packedInRange = false;
                }
                if (deployNow && RequestDeploy(ctx.craft))
                {
                    track.deployRequested = true;
                    track.packedInRange = false;
                    LogAction(L"in range: deploy", ctx.craft, ctx);
                }
                return;
            }
            track.packedInRange = false;

            if (ctx.deployState == kDeployStateDeployed && track.deployRequested)
            {
                // Our deploy finished: let the task re-choose into blast.
                track.deployRequested = false;
                ForceTaskChooseState(ctx.task, ctx.craft);
            }

            if (ctx.deployState != kDeployStateDeployed &&
                ctx.deployState != kDeployStateDeploying)
                return;

            if (ctx.distSq <= ctx.rangeSq)
            {
                track.beyondRange = false;
                return;
            }
            if (!track.beyondRange)
            {
                track.beyondRange = true;
                track.beyondRangeSince = now;
                return;
            }
            if (now - track.beyondRangeSince < kPackupDelaySeconds)
                return;

            if (RequestPackup(ctx.craft))
            {
                track.beyondRange = false;
                track.deployRequested = false;
                ForceTaskChooseState(ctx.task, ctx.craft);
                LogAction(L"target left range: pack up", ctx.craft, ctx);
            }
        }

        void __fastcall TurretProcessDoAttackHook(void* process, void* /*edx*/)
        {
            if (g_Active)
                ManageAttackDeploy(process);
            g_StockDoAttack(process);
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
                Log(L"[TURRETATK] %ls RTTI mismatch vtable=0x%08X; not installed\n",
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
                Log(L"[TURRETATK] %ls slot mismatch slot=0x%08X current=0x%08X expected=0x%08X; not installed\n",
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
                Log(L"[TURRETATK] Failed installing %ls hook slot=0x%08X\n",
                    p.label, static_cast<uint32_t>(slotAddress));
                return false;
            }
            Log(L"[TURRETATK] %ls hook installed slot=0x%08X\n",
                p.label, static_cast<uint32_t>(slotAddress));
            return true;
        }

        void InitializeTurretAttackOrdersConfig()
        {
            if (g_ConfigInitialized)
                return;
            g_ConfigInitialized = true;
            bool value = true;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "TurretAttackOrders", value))
                g_Enabled = value;
            else
                g_Enabled = true;
            Log(L"[TURRETATK] Baseline enabled=%hs (SP-only)\n", g_Enabled ? "yes" : "no");
        }
    }

    void InstallTurretAttackOrdersHooksIfPossible()
    {
        static bool s_tried = false;
        if (s_tried)
            return;
        s_tried = true;

        InitializeTurretAttackOrdersConfig();
        if (!g_Enabled)
        {
            Log(L"[TURRETATK] Disabled in openshim.ini; hooks not installed\n");
            return;
        }

        const HookEngine::EngineRow rows[] = {
            { "TurretTankVtable", &g_TurretTankVtableAddr },
            { "TurretTankGetCommand", &g_TurretTankGetCommandAddr },
            { "TurretTankUpdateModeList", &g_TurretTankUpdateModeListAddr },
            { "CraftGetCommand", &g_CraftGetCommandAddr },
            { "CraftDeploy", &g_CraftDeployAddr },
            { "CraftPackup", &g_CraftPackupAddr },
            { "ModeListSetMode", &g_ModeListSetModeAddr },
            { "TurretTankProcessVtable", &g_ProcessVtableAddr },
            { "TurretTankFriendVtable", &g_FriendVtableAddr },
            { "TurretTankEnemyVtable", &g_EnemyVtableAddr },
            { "TurretTankProcessInitAttack", &g_InitAttackAddr },
            { "TurretTankProcessDoAttack", &g_DoAttackAddr },
            { "GameObjectHandleGetObj", &g_GetObjAddr },
            { "GetGameTime", &g_GetTimeAddr },
        };
        if (!HookEngine::BindEngineRows("Turret attack orders", rows))
        {
            Log(L"[TURRETATK] Engine rows did not bind; feature unavailable\n");
            return;
        }

        g_StockTurretGetCommand = reinterpret_cast<FnGetCommand>(g_TurretTankGetCommandAddr);
        g_FnCraftGetCommand = reinterpret_cast<FnGetCommand>(g_CraftGetCommandAddr);
        g_StockTurretUpdateModeList = reinterpret_cast<FnCraftVoid>(g_TurretTankUpdateModeListAddr);
        g_FnCraftDeploy = reinterpret_cast<FnCraftVoid>(g_CraftDeployAddr);
        g_FnCraftPackup = reinterpret_cast<FnCraftVoid>(g_CraftPackupAddr);
        g_FnSetMode = reinterpret_cast<FnModeListSetMode>(g_ModeListSetModeAddr);
        g_StockInitAttack = reinterpret_cast<FnProcessVoid>(g_InitAttackAddr);
        g_StockDoAttack = reinterpret_cast<FnProcessVoid>(g_DoAttackAddr);
        g_FnGetObj = reinterpret_cast<FnGetObj>(g_GetObjAddr);
        g_FnGetTime = reinterpret_cast<FnGetTime>(g_GetTimeAddr);

        void* const initHook = reinterpret_cast<void*>(&TurretProcessInitAttackHook);
        void* const doHook = reinterpret_cast<void*>(&TurretProcessDoAttackHook);
        const SlotPlan plans[] = {
            { L"TurretTank::GetCommand", g_TurretTankVtableAddr, ".?AVTurretTank@@",
              kCraftGetCommandSlot, g_TurretTankGetCommandAddr,
              reinterpret_cast<void*>(&TurretTankGetCommandHook) },
            { L"TurretTank::UpdateModeList", g_TurretTankVtableAddr, ".?AVTurretTank@@",
              kCraftUpdateModeListSlot, g_TurretTankUpdateModeListAddr,
              reinterpret_cast<void*>(&TurretTankUpdateModeListHook) },
            { L"TurretTankProcess::InitAttack", g_ProcessVtableAddr, ".?AVTurretTankProcess@@",
              kProcessInitAttackSlot, g_InitAttackAddr, initHook },
            { L"TurretTankFriend::InitAttack", g_FriendVtableAddr, ".?AVTurretTankFriend@@",
              kProcessInitAttackSlot, g_InitAttackAddr, initHook },
            { L"TurretTankEnemy::InitAttack", g_EnemyVtableAddr, ".?AVTurretTankEnemy@@",
              kProcessInitAttackSlot, g_InitAttackAddr, initHook },
            { L"TurretTankProcess::DoAttack", g_ProcessVtableAddr, ".?AVTurretTankProcess@@",
              kProcessDoAttackSlot, g_DoAttackAddr, doHook },
            { L"TurretTankFriend::DoAttack", g_FriendVtableAddr, ".?AVTurretTankFriend@@",
              kProcessDoAttackSlot, g_DoAttackAddr, doHook },
            { L"TurretTankEnemy::DoAttack", g_EnemyVtableAddr, ".?AVTurretTankEnemy@@",
              kProcessDoAttackSlot, g_DoAttackAddr, doHook },
        };

        // All or nothing: an ATTACK order the turret cannot follow through on
        // would be worse than no order at all.
        for (const SlotPlan& p : plans)
        {
            if (!SlotReady(p))
            {
                Log(L"[TURRETATK] Feature unavailable: %ls failed its check\n", p.label);
                return;
            }
        }
        bool all = true;
        for (const SlotPlan& p : plans)
            all = InstallSlot(p) && all;
        g_HooksInstalled = all;
        Log(L"[TURRETATK] Turret attack orders %hs\n",
            all ? "installed" : "partially installed; feature stays off");
        RefreshTurretAttackOrdersState();
    }

    void RefreshTurretAttackOrdersState()
    {
        InitializeTurretAttackOrdersConfig();
        const bool want = g_Enabled && g_HooksInstalled && IsSinglePlayerSession();
        if (want != g_Active)
        {
            g_Active = want;
            Log(L"[TURRETATK] %hs\n", want ? "Active (SP-only)" : "Stood down");
        }
        if (!g_Active)
            g_Tracks.clear();
    }

    void ResetTurretAttackOrders()
    {
        g_Tracks.clear();
        g_ActionLogBudget = 32;
        // The ini key is read once at startup (hooks install once).
        RefreshTurretAttackOrdersState();
    }
}
