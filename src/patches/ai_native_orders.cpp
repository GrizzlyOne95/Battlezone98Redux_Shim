// ai_native_orders.cpp
// BZR Open Shim - opt-in single-player AI orders driven by a mission/EXU
// script through three SDK exports: Follow with Formation rules, a Defend
// refresh for moving targets, and a native Hold (a BZ2 SitAttack
// equivalent). Evidence and every address: Docs/NATIVE_HOLD_DEFEND_FOLLOW.md.
// All three are off by default, stand down in multiplayer and are reset at
// mission end.
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
        struct Vec3f
        {
            float x, y, z;
        };

        using FnTaskDoState = void(__thiscall*)(void* task);
        using FnGetObj = void*(__cdecl*)(uint32_t handle);
        using FnGetTime = float(__cdecl*)();
        using FnCarrierOf = void*(__thiscall*)(void* craft);
        using FnCarrierMask = uint32_t(__thiscall*)(void* carrier);
        using FnClosestEnemy = void*(__cdecl*)(void* craft, float* range);
        using FnTaskBool = bool(__thiscall*)(void* task);
        using FnTaskVoid = void(__thiscall*)(void* task);
        using FnAimPoint = Vec3f*(__cdecl*)(Vec3f* out, float scale, Vec3f origin);
        using FnLookAt = void(__thiscall*)(void* task, void* state, Vec3f* point);
        using FnMayHitFriends = bool(__cdecl*)(void* craft, float range, float a, float b);
        using FnUpdateWeapon = void(__thiscall*)(void* task, uint32_t fire);

        constexpr size_t kTaskDoStateVtableSlot = 12;

        // UnitTask fields shared by DefendTask, SitTask and FollowTask.
        constexpr size_t kTaskStateOffset = 0x08;
        constexpr size_t kTaskNextStateOffset = 0x0C;
        constexpr size_t kTaskCraftOffset = 0x10;
        constexpr size_t kTaskTargetHandleOffset = 0x14;
        constexpr size_t kTaskTargetObjOffset = 0x18;
        constexpr size_t kDefendGoalOffset = 0x28;

        constexpr int kDefendStateGoto = 2;
        constexpr int kDefendStateWander = 6;

        // GameObject +0xFC is its AiProcess (GetAIProcess 0x0045BDF0). Process
        // +0x20 is the process state, +0x34 its craft, +0x3C the defend "who".
        constexpr size_t kCraftProcessOffset = 0xFC;
        constexpr size_t kProcessStateOffset = 0x20;
        constexpr size_t kProcessCraftOffset = 0x34;
        constexpr size_t kProcessWhoOffset = 0x3C;
        constexpr int kProcessStateDefend = 9;

        // How long a Hold request waits for its queued CMD_DEFEND to apply.
        constexpr float kHoldPendingSeconds = 3.0f;
        constexpr float kDefendRepathPeriodSeconds = 1.0f;
        constexpr float kDefendRepathDistance = 15.0f;
        // A defend track older than this is not a consecutive tick (a
        // reused task address, a pause); do not shift by its position.
        constexpr float kDefendTrackMaxAgeSeconds = 0.5f;
        constexpr size_t kDefendTrackLimit = 256;

        // Follow constant: operand of the movss at 0x005833CA. Stock points at
        // [0x008A2E20] (15625.0), Formation rules at [0x008A2498] (0.0).
        constexpr uint32_t kFollowOperandOffset = 4;
        constexpr uint8_t kFollowStockBytes[4] = { 0x20, 0x2E, 0x8A, 0x00 };
        constexpr uint8_t kFollowFormationBytes[4] = { 0x98, 0x24, 0x8A, 0x00 };

        uint32_t g_FollowInsnAddr = 0; // the movss; its operand is at +4
        uint32_t g_FollowSiteAddr = 0;
        uint32_t g_DefendVtableAddr = 0;
        uint32_t g_DefendDoStateAddr = 0;
        uint32_t g_SitVtableAddr = 0;
        uint32_t g_SitDoStateAddr = 0;
        uint32_t g_FollowDoStateAddr = 0;
        uint32_t g_GetObjAddr = 0;
        uint32_t g_GetTimeAddr = 0;
        uint32_t g_CarrierAddr = 0;
        uint32_t g_LinkableAddr = 0;
        uint32_t g_EnemyAddr = 0;
        uint32_t g_CanFireAddr = 0;
        uint32_t g_AimPointAddr = 0;
        uint32_t g_LookAtAddr = 0;
        uint32_t g_IsAimedAddr = 0;
        uint32_t g_SpecialReadyAddr = 0;
        uint32_t g_SpecialFireAddr = 0;
        uint32_t g_MayHitAddr = 0;
        uint32_t g_UpdateWeaponAddr = 0;

        FnTaskDoState g_StockDefendDoState = nullptr;
        FnTaskDoState g_StockSitDoState = nullptr;
        FnGetObj g_FnGetObj = nullptr;
        FnGetTime g_FnGetTime = nullptr;
        FnCarrierOf g_FnCarrier = nullptr;
        FnCarrierMask g_FnLinkable = nullptr;
        FnClosestEnemy g_FnEnemy = nullptr;
        FnTaskBool g_FnCanFire = nullptr;
        FnAimPoint g_FnAimPoint = nullptr;
        FnLookAt g_FnLookAt = nullptr;
        FnTaskBool g_FnIsAimed = nullptr;
        FnTaskBool g_FnSpecialReady = nullptr;
        FnTaskVoid g_FnSpecialFire = nullptr;
        FnMayHitFriends g_FnMayHit = nullptr;
        FnUpdateWeapon g_FnUpdateWeapon = nullptr;

        bool g_FollowBound = false;
        bool g_DefendHookInstalled = false;
        bool g_SitHookInstalled = false;

        bool g_FollowEnabled = false;
        bool g_DefendEnabled = false;
        bool g_FollowPatched = false;
        bool g_FollowRefusalLogged = false;
        bool g_DefendActive = false;

        struct HeldEntry
        {
            float pendingUntil;
            bool seenHeld;
        };
        std::unordered_map<uint32_t, HeldEntry> g_Held;

        struct DefendTrack
        {
            uint32_t handle = 0;
            float pos[3] = {};
            bool havePos = false;
            int lastState = 0;
            float lastTime = -1.0e9f;
            float lastCheck = -1.0e9f;
        };
        std::unordered_map<uintptr_t, DefendTrack> g_DefendTracks;

        // ---- small fault-safe readers (no C++ objects, so __try is legal) ----

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
            if (!g_FnGetObj)
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

        void* ReadTaskCraft(void* task)
        {
            __try
            {
                return *reinterpret_cast<void**>(
                    static_cast<uint8_t*>(task) + kTaskCraftOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        // True when the craft's own process is a Defend with who == 0 (the
        // SitTask Defend(h, 0) builds), and the process points back at it.
        bool CraftProcessIsHolding(void* craft)
        {
            __try
            {
                uint8_t* process = *reinterpret_cast<uint8_t**>(
                    static_cast<uint8_t*>(craft) + kCraftProcessOffset);
                if (reinterpret_cast<uintptr_t>(process) < 0x10000)
                    return false;
                if (*reinterpret_cast<void**>(process + kProcessCraftOffset) != craft)
                    return false;
                return *reinterpret_cast<int*>(process + kProcessStateOffset) ==
                           kProcessStateDefend &&
                       *reinterpret_cast<int*>(process + kProcessWhoOffset) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        struct DefendFields
        {
            int state;
            int next;
            uint32_t handle;
            void* target;
            float goal[3];
        };

        bool ReadDefendFields(void* task, DefendFields& out)
        {
            __try
            {
                const uint8_t* t = static_cast<const uint8_t*>(task);
                out.state = *reinterpret_cast<const int*>(t + kTaskStateOffset);
                out.next = *reinterpret_cast<const int*>(t + kTaskNextStateOffset);
                out.handle = *reinterpret_cast<const uint32_t*>(t + kTaskTargetHandleOffset);
                out.target = *reinterpret_cast<void* const*>(t + kTaskTargetObjOffset);
                const float* goal = reinterpret_cast<const float*>(t + kDefendGoalOffset);
                out.goal[0] = goal[0];
                out.goal[1] = goal[1];
                out.goal[2] = goal[2];
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void ShiftDefendGoal(void* task, float dx, float dz)
        {
            __try
            {
                float* goal = reinterpret_cast<float*>(
                    static_cast<uint8_t*>(task) + kDefendGoalOffset);
                goal[0] += dx;
                goal[2] += dz;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        void SetDefendNextState(void* task, int next)
        {
            __try
            {
                *reinterpret_cast<int*>(
                    static_cast<uint8_t*>(task) + kTaskNextStateOffset) = next;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        // ---- Follow: Formation rules --------------------------------------

        bool ApplyFollowPatch(bool want)
        {
            if (want == g_FollowPatched)
                return true;
            if (g_FollowSiteAddr == 0)
                return !want;

            if (want)
            {
                if (!ExpectedBytesMatchAt(g_FollowSiteAddr, kFollowStockBytes,
                                          sizeof(kFollowStockBytes)))
                {
                    if (!g_FollowRefusalLogged)
                    {
                        g_FollowRefusalLogged = true;
                        Log(L"[AIORDERS] Follow range site 0x%08X bytes differ from stock; Follow-as-Formation refused\n",
                            g_FollowSiteAddr);
                    }
                    return false;
                }
                if (!WritePatchBytes(g_FollowSiteAddr, kFollowFormationBytes,
                                     sizeof(kFollowFormationBytes)))
                {
                    if (!g_FollowRefusalLogged)
                    {
                        g_FollowRefusalLogged = true;
                        Log(L"[AIORDERS] Failed writing follow range site 0x%08X; Follow-as-Formation refused\n",
                            g_FollowSiteAddr);
                    }
                    return false;
                }
                g_FollowPatched = true;
                Log(L"[AIORDERS] Follow-as-Formation active\n");
                return true;
            }

            if (ExpectedBytesMatchAt(g_FollowSiteAddr, kFollowFormationBytes,
                                     sizeof(kFollowFormationBytes)) &&
                !WritePatchBytes(g_FollowSiteAddr, kFollowStockBytes,
                                 sizeof(kFollowStockBytes)))
            {
                Log(L"[AIORDERS] Failed restoring follow range site 0x%08X\n",
                    g_FollowSiteAddr);
                return false;
            }
            g_FollowPatched = false;
            Log(L"[AIORDERS] Follow-as-Formation restored to stock\n");
            return true;
        }

        // ---- Defend refresh -----------------------------------------------

        void RefreshDefendTask(void* task)
        {
            DefendFields f = {};
            if (!ReadDefendFields(task, f))
                return;

            const uintptr_t key = reinterpret_cast<uintptr_t>(task);
            float targetPos[3] = {};
            if (!f.target || !TryGetGameObjectWorldPosition(f.target, targetPos))
            {
                g_DefendTracks.erase(key);
                return;
            }

            if (g_DefendTracks.size() > kDefendTrackLimit)
                g_DefendTracks.clear();
            DefendTrack& track = g_DefendTracks[key];
            if (track.handle != f.handle)
            {
                track = DefendTrack();
                track.handle = f.handle;
            }

            const float now = NowSeconds();
            const bool consecutive =
                track.havePos && now >= track.lastTime &&
                now - track.lastTime < kDefendTrackMaxAgeSeconds;

            if (f.state == kDefendStateWander)
            {
                // The wander point is fixed for 10 s; carry it along with the
                // target. Not on the first tick of the state, whose point was
                // just picked around the live target.
                if (consecutive && track.lastState == kDefendStateWander)
                {
                    const float dx = targetPos[0] - track.pos[0];
                    const float dz = targetPos[2] - track.pos[2];
                    if (dx != 0.0f || dz != 0.0f)
                        ShiftDefendGoal(task, dx, dz);
                }
            }
            else if (f.state == kDefendStateGoto && f.next == kDefendStateGoto &&
                     (now < track.lastCheck ||
                      now - track.lastCheck >= kDefendRepathPeriodSeconds))
            {
                // The goto path was built once to a snapshot of the target.
                // Far from the live target, go back through state 6, which
                // picks a new point and re-paths.
                track.lastCheck = now;
                const float dx = targetPos[0] - f.goal[0];
                const float dz = targetPos[2] - f.goal[2];
                if (dx * dx + dz * dz >
                    kDefendRepathDistance * kDefendRepathDistance)
                    SetDefendNextState(task, kDefendStateWander);
            }

            track.pos[0] = targetPos[0];
            track.pos[1] = targetPos[1];
            track.pos[2] = targetPos[2];
            track.havePos = true;
            track.lastState = f.state;
            track.lastTime = now;
        }

        void __fastcall DefendTaskDoStateHook(void* task, void* /*edx*/)
        {
            g_StockDefendDoState(task);
            if (g_DefendActive)
                RefreshDefendTask(task);
        }

        // ---- Hold ---------------------------------------------------------

        // FollowTask::DoState's fire block (0x004D3E49..0x004D3FD4) run on a
        // SitTask: aim at and shoot the closest enemy without moving.
        void RunHeldFireBlock(uint8_t* t)
        {
            void* saved = nullptr;
            bool replaced = false;
            __try
            {
                void* me = *reinterpret_cast<void**>(t + kTaskCraftOffset);
                void* carrier = g_FnCarrier(me);
                if (!carrier || !g_FnLinkable(carrier))
                    return;

                const uint8_t* weapon = *reinterpret_cast<uint8_t* const*>(t + 0xB4);
                const uint8_t* weaponInfo = *reinterpret_cast<uint8_t* const*>(weapon + 8);
                if (*reinterpret_cast<const uint32_t*>(weaponInfo + 0xC) == 0x44495350) // 'DISP'
                    return;

                float range = *reinterpret_cast<float*>(t + 0xA0);
                void* enemy = g_FnEnemy(me, &range);
                if (!enemy)
                    return;

                saved = *reinterpret_cast<void**>(t + kTaskTargetObjOffset);
                *reinterpret_cast<void**>(t + kTaskTargetObjOffset) = enemy;
                replaced = true;

                const bool able = g_FnCanFire(t);
                const Vec3f origin = *reinterpret_cast<const Vec3f*>(t + 0xE4);
                Vec3f scratch = {};
                const float scale = *reinterpret_cast<const float*>(t + 0x98) * 0.5f - 0.5f;
                Vec3f point = *g_FnAimPoint(&scratch, scale, origin);
                g_FnLookAt(t, t + 0xC8, &point);
                if (!g_FnIsAimed(t))
                {
                    const bool fire = able && !g_FnMayHit(me, range, 0.3f, 1.0f);
                    g_FnUpdateWeapon(t, fire ? 1u : 0u);
                }
                else if (g_FnSpecialReady(t))
                {
                    g_FnSpecialFire(t);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            if (replaced)
            {
                __try
                {
                    *reinterpret_cast<void**>(t + kTaskTargetObjOffset) = saved;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }
        }

        void __fastcall SitTaskDoStateHook(void* task, void* /*edx*/)
        {
            g_StockSitDoState(task);
            if (g_Held.empty())
                return;
            void* craft = ReadTaskCraft(task);
            if (craft && IsAiHeldCraft(craft))
                RunHeldFireBlock(static_cast<uint8_t*>(task));
        }

        // ---- vtable install -----------------------------------------------

        bool InstallTaskDoStateSlot(const wchar_t* label,
                                    uint32_t vtable,
                                    const char* rttiName,
                                    uint32_t original,
                                    void* hook)
        {
            const uintptr_t slotAddress =
                vtable + kTaskDoStateVtableSlot * sizeof(void*);
            if (!VtableTypeNameMatches(vtable, rttiName))
            {
                Log(L"[AIORDERS] %ls RTTI mismatch vtable=0x%08X; hook not installed\n",
                    label, vtable);
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
            if (current != hook && current != reinterpret_cast<void*>(original))
            {
                Log(L"[AIORDERS] %ls::DoState vtable mismatch slot=0x%08X current=0x%08X expected=0x%08X\n",
                    label, static_cast<uint32_t>(slotAddress),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)), original);
                return false;
            }
            if (current != hook && !WritePointerValue(slotAddress, hook))
            {
                Log(L"[AIORDERS] Failed installing %ls::DoState vtable hook slot=0x%08X\n",
                    label, static_cast<uint32_t>(slotAddress));
                return false;
            }
            Log(L"[AIORDERS] %ls::DoState hook installed slot=0x%08X\n",
                label, static_cast<uint32_t>(slotAddress));
            return true;
        }
    }

    // True while the craft is held: it is in the Hold table, its process is
    // the Defend(h, 0) order, and the entry has not outlived a changed order.
    bool IsAiHeldCraft(void* craft)
    {
        if (!craft || g_Held.empty())
            return false;

        const float now = NowSeconds();
        bool held = false;
        for (auto it = g_Held.begin(); it != g_Held.end();)
        {
            void* obj = SafeGetObj(it->first);
            if (!obj)
            {
                it = g_Held.erase(it);
                continue;
            }
            if (obj != craft)
            {
                ++it;
                continue;
            }
            if (CraftProcessIsHolding(craft))
            {
                it->second.seenHeld = true;
                held = true;
                ++it;
            }
            // A load can rewind game time; a window longer than the pending span is stale.
            else if (!it->second.seenHeld && now < it->second.pendingUntil &&
                     it->second.pendingUntil - now <= kHoldPendingSeconds)
            {
                ++it; // the queued CMD_DEFEND has not been applied yet
            }
            else
            {
                it = g_Held.erase(it); // a new order replaced the hold
            }
        }
        return held;
    }

    // IsAiHeldCraft for an AiProcess: its craft is process +0x34.
    bool IsAiHeldProcess(void* process)
    {
        if (!process || g_Held.empty())
            return false;
        void* craft = nullptr;
        __try
        {
            craft = *reinterpret_cast<void**>(
                static_cast<uint8_t*>(process) + kProcessCraftOffset);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
        return IsAiHeldCraft(craft);
    }

    void InstallAiNativeOrdersHooksIfPossible()
    {
        static bool s_followTried = false;
        static bool s_defendTried = false;
        static bool s_holdTried = false;

        if (!s_followTried)
        {
            s_followTried = true;
            const HookEngine::EngineRow rows[] = {
                { "AiFollowRangeConstantSite", &g_FollowInsnAddr },
            };
            g_FollowBound = HookEngine::BindEngineRows("AI Follow as Formation", rows);
            if (g_FollowBound)
                g_FollowSiteAddr = g_FollowInsnAddr + kFollowOperandOffset;
        }

        if (!s_defendTried)
        {
            s_defendTried = true;
            const HookEngine::EngineRow rows[] = {
                { "DefendTaskVtable", &g_DefendVtableAddr },
                { "DefendTaskDoState", &g_DefendDoStateAddr },
                { "GameObjectHandleGetObj", &g_GetObjAddr },
                { "GetGameTime", &g_GetTimeAddr },
            };
            if (HookEngine::BindEngineRows("AI Defend refresh", rows))
            {
                g_FnGetObj = reinterpret_cast<FnGetObj>(g_GetObjAddr);
                g_FnGetTime = reinterpret_cast<FnGetTime>(g_GetTimeAddr);
                g_StockDefendDoState = reinterpret_cast<FnTaskDoState>(g_DefendDoStateAddr);
                g_DefendHookInstalled = InstallTaskDoStateSlot(
                    L"DefendTask", g_DefendVtableAddr, ".?AVDefendTask@@",
                    g_DefendDoStateAddr, reinterpret_cast<void*>(DefendTaskDoStateHook));
            }
        }

        if (!s_holdTried)
        {
            s_holdTried = true;
            const HookEngine::EngineRow rows[] = {
                { "SitTaskVtable", &g_SitVtableAddr },
                { "SitTaskDoState", &g_SitDoStateAddr },
                { "FollowTaskDoState", &g_FollowDoStateAddr },
                { "GameObjectHandleGetObj", &g_GetObjAddr },
                { "GetGameTime", &g_GetTimeAddr },
                { "HudFadeGetCarrier", &g_CarrierAddr },
                { "HudFadeGetLinkable", &g_LinkableAddr },
                { "AiFireBlockHelperGetEnemyWithin", &g_EnemyAddr },
                { "AiFireBlockHelperCanFire", &g_CanFireAddr },
                { "AiFireBlockHelperAimPoint", &g_AimPointAddr },
                { "AiFireBlockHelperLookAt", &g_LookAtAddr },
                { "AiFireBlockHelperIsAimed", &g_IsAimedAddr },
                { "AiFireBlockHelperSpecialReady", &g_SpecialReadyAddr },
                { "AiFireBlockHelperSpecialFire", &g_SpecialFireAddr },
                { "AiFireBlockHelperMayHitFriends", &g_MayHitAddr },
                { "AiFireBlockHelperUpdateWeapon", &g_UpdateWeaponAddr },
            };
            if (HookEngine::BindEngineRows("AI Hold", rows))
            {
                g_FnGetObj = reinterpret_cast<FnGetObj>(g_GetObjAddr);
                g_FnGetTime = reinterpret_cast<FnGetTime>(g_GetTimeAddr);
                g_FnCarrier = reinterpret_cast<FnCarrierOf>(g_CarrierAddr);
                g_FnLinkable = reinterpret_cast<FnCarrierMask>(g_LinkableAddr);
                g_FnEnemy = reinterpret_cast<FnClosestEnemy>(g_EnemyAddr);
                g_FnCanFire = reinterpret_cast<FnTaskBool>(g_CanFireAddr);
                g_FnAimPoint = reinterpret_cast<FnAimPoint>(g_AimPointAddr);
                g_FnLookAt = reinterpret_cast<FnLookAt>(g_LookAtAddr);
                g_FnIsAimed = reinterpret_cast<FnTaskBool>(g_IsAimedAddr);
                g_FnSpecialReady = reinterpret_cast<FnTaskBool>(g_SpecialReadyAddr);
                g_FnSpecialFire = reinterpret_cast<FnTaskVoid>(g_SpecialFireAddr);
                g_FnMayHit = reinterpret_cast<FnMayHitFriends>(g_MayHitAddr);
                g_FnUpdateWeapon = reinterpret_cast<FnUpdateWeapon>(g_UpdateWeaponAddr);
                g_StockSitDoState = reinterpret_cast<FnTaskDoState>(g_SitDoStateAddr);
                g_SitHookInstalled = InstallTaskDoStateSlot(
                    L"SitTask", g_SitVtableAddr, ".?AVSitTask@@",
                    g_SitDoStateAddr, reinterpret_cast<void*>(SitTaskDoStateHook));
            }
        }
    }

    // Re-evaluate the gates: enabled and single player. Cheap and idempotent;
    // also driven by the registered-feature tick.
    void RefreshAiNativeOrdersState()
    {
        const bool singlePlayer = IsSinglePlayerSession();
        g_DefendActive = g_DefendEnabled && singlePlayer && g_DefendHookInstalled;
        if (!g_DefendActive)
            g_DefendTracks.clear();
        if (!singlePlayer)
            g_Held.clear();
        ApplyFollowPatch(g_FollowEnabled && singlePlayer && g_FollowBound);
    }

    bool SetAiFollowEngageEnabled(bool enabled)
    {
        InstallAiNativeOrdersHooksIfPossible();
        g_FollowEnabled = enabled;
        RefreshAiNativeOrdersState();
        return enabled ? g_FollowPatched : !g_FollowPatched;
    }

    bool SetAiDefendRefreshEnabled(bool enabled)
    {
        InstallAiNativeOrdersHooksIfPossible();
        g_DefendEnabled = enabled;
        RefreshAiNativeOrdersState();
        return enabled ? g_DefendActive : true;
    }

    bool SetAiHold(int handle, bool hold)
    {
        const uint32_t key = static_cast<uint32_t>(handle);
        if (!hold)
        {
            g_Held.erase(key);
            return true;
        }

        InstallAiNativeOrdersHooksIfPossible();
        // Hold needs the SitTask hook to shoot and the DoSubTask hook to stop
        // the chase.
        if (!g_SitHookInstalled || !g_RetargetPeriodHooksInstalled ||
            !IsSinglePlayerSession() || handle == 0 || !SafeGetObj(key))
            return false;

        g_Held[key] = HeldEntry{ NowSeconds() + kHoldPendingSeconds, false };
        return true;
    }

    void ResetAiNativeOrders()
    {
        g_FollowEnabled = false;
        g_DefendEnabled = false;
        g_DefendActive = false;
        ApplyFollowPatch(false);
        g_Held.clear();
        g_DefendTracks.clear();
    }
}
