// rts_order_queue.cpp
// BZR Open Shim - [Gameplay] RtsOrderQueue (default off, single player):
// Shift-queued orders for the stock Space and Alt command buttons.
//
// While the stock multi-select modifier byte (cmd_multi, 0x00919875, so a
// rebind is respected) is held with units selected and the context command is
// one of Go / Attack / Follow / Defend / Pickup / Dropoff / Get Repair /
// Get Reload, the Space and Alt labels read "Queue <label>" and the press
// issues the order to each idle selected unit at once and appends it to the
// queue of a busy one (8 per unit, 32 units). A 4 Hz drain on the frame
// thread issues the next entry of each idle unit's queue with the stock
// SetCommand wrappers (never off that thread). A plain order (any stock
// BroadcastCommand, a unit-menu pick), the unit dying, a mission reset, the
// option turning off or a network game clears the queue. rts_markers.cpp
// draws the queued chain (amber).
//
// Hooks (REL32 call redirects, scripts/patches.json engine_addresses
// "ControlPanelCmd*", "ControlPanelAlt*", "CommandMenuAltLabelLocalizeCall";
// each fails closed): the BroadcastCommand calls of the SPACE generic press
// (0x004A1F7A object, 0x004A1FB0 ground) and of the ALT press (0x004A25DB,
// 0x004A2611), the SelectNone after each press (0x004A1FD7, 0x004A2638) and
// the ALT label Localize (0x004A26C1). The SPACE label Localize
// (0x004A207C) is ProducerRallyPoints' redirect; it calls
// RtsOrderQueueSpaceLabel after its own Rally check. Evidence and limits:
// Docs/RTS_ORDER_QUEUE.md.
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "hook_engine.h"
#include "openshim_l10n_text.h"
#include "patcher.h"
#include "rts_commands_policy.h"
#include "rts_markers.h"
#include "rts_order_queue_policy.h"
#include "rts_placement.h"
#include "scene_mutation_drain.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdarg>
#include <cstdint>
#include <cstring>
#include <mutex>

using BZROpenShim::L10n::ShimText;

namespace BZROpenShim::Hooks
{
    namespace
    {
        namespace Q = RtsOrderQueuePolicy;

        using FnGetObj = void*(__cdecl*)(uint32_t handle);
        using FnGetHandle = uint32_t(__thiscall*)(void* obj);
        using FnCanCommand = bool(__thiscall*)(void* obj);
        using FnBroadcastObj = void(__thiscall*)(void* panel, int what, void* target);
        using FnBroadcastWhere = void(__thiscall*)(void* panel, int what, const float* where);
        using FnSetCommandObj = void(__thiscall*)(void* obj, int what, void* target);
        using FnSetCommandWhere = void(__thiscall*)(void* obj, int what, const float* where, uint32_t paramLow,
                                                    uint32_t paramHigh);
        using FnSelectNone = void(__thiscall*)(void* panel);
        using FnLocalize = const char*(__cdecl*)(const char* section, const char* key);
        using FnPlaySound = int(__cdecl*)(const char* filename, uint32_t, uint32_t, uint32_t);

        // ControlPanel fields (ControlPanelGlobal row; FUN_004a08e0.c).
        constexpr size_t kSelectListOffset = 0x1C;
        constexpr size_t kSelectNumOffset = 0x188;
        constexpr size_t kCmdButtonCommandOffset = 0x111C; // SPACE button
        constexpr size_t kAltButtonCommandOffset = 0x112C; // ALT button
        constexpr size_t kCanCommandSlot = 14;             // vtable +0x38
        constexpr size_t kObj76FlagsOffset = 0x14;         // as rts_placement.cpp: 0x200 = dead
        constexpr uint32_t kObj76DeadFlag = 0x200;
        constexpr int kMaxInstallAttempts = 40;
        constexpr const char* kRefuseSound = "mnu_buzz.wav";

        // Engine rows (patch thread, then read-only).
        uint32_t g_ControlPanelAddr = 0;
        uint32_t g_GetObjAddr = 0;
        uint32_t g_SetCommandObjAddr = 0;
        uint32_t g_SetCommandWhereAddr = 0;
        uint32_t g_BroadcastObjAddr = 0;
        uint32_t g_SelectNoneAddr = 0;
        uint32_t g_LocalizeAddr = 0;
        uint32_t g_MultiAddr = 0; // cmd_multi byte
        uint32_t g_ObjPressRow = 0;
        uint32_t g_WherePressRow = 0;
        uint32_t g_SelectNoneRow = 0;
        uint32_t g_AltObjPressRow = 0;
        uint32_t g_AltWherePressRow = 0;
        uint32_t g_AltSelectNoneRow = 0;
        uint32_t g_AltLabelRow = 0;

        FnGetObj g_FnGetObj = nullptr;
        FnBroadcastObj g_FnBroadcastObj = nullptr;
        FnBroadcastWhere g_FnBroadcastWhere = nullptr; // the original callee of the ground sites
        FnSetCommandObj g_FnSetCommandObj = nullptr;
        FnSetCommandWhere g_FnSetCommandWhere = nullptr;
        FnSelectNone g_FnSelectNone = nullptr;
        FnLocalize g_FnLocalize = nullptr;
        FnPlaySound g_FnPlaySound = nullptr;

        // Patch state (patch thread; read through PartsReady).
        bool g_RowsBound = false;
        bool g_SelectNoneReady = false;
        bool g_PressReady = false;
        bool g_AltLabelReady = false;

        // Config and live state.
        bool g_ConfigRead = false;
        bool g_Enabled = false;
        std::atomic<bool> g_Active{ false };
        std::atomic<int> g_QueuedUnits{ 0 };
        bool g_SkipSelectNone = false; // Render frame, game thread
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

        bool ReadInt(uintptr_t address, int& out)
        {
            if (address < 0x10000)
                return false;
            __try
            {
                out = *reinterpret_cast<const int*>(address);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

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

        void* ReadPtr(uintptr_t address)
        {
            if (address < 0x10000)
                return nullptr;
            __try
            {
                return *reinterpret_cast<void* const*>(address);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
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

        bool SafeCanCommand(void* obj)
        {
            void* const vtable = ReadPtr(reinterpret_cast<uintptr_t>(obj));
            void* const fn = vtable ? ReadPtr(reinterpret_cast<uintptr_t>(vtable) + kCanCommandSlot * sizeof(void*)) : nullptr;
            if (!fn)
                return false;
            __try
            {
                return reinterpret_cast<FnCanCommand>(fn)(obj);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Not destroyed and not flagged dead (GameObject +0xF4 -> obj76, +0x14
        // bit 0x200, as rts_placement.cpp / rts_markers.cpp).
        bool ObjectAlive(void* obj)
        {
            if (!obj)
                return false;
            const uintptr_t obj76 = reinterpret_cast<uintptr_t>(ReadPtr(reinterpret_cast<uintptr_t>(obj) + kGameObjectObjOffset));
            int flags = 0;
            if (obj76 && ReadInt(obj76 + kObj76FlagsOffset, flags) && (static_cast<uint32_t>(flags) & kObj76DeadFlag) != 0)
                return false;
            return true;
        }

        bool IsPlayerTeam(void* obj)
        {
            const uintptr_t slot = EngineGlobals::UserObjectSlot();
            void* const player = slot ? ReadPtr(slot) : nullptr;
            int team = -1;
            int playerTeam = -2;
            return obj && player &&
                   ReadInt(reinterpret_cast<uintptr_t>(obj) + kGameObjectActualTeamOffset, team) &&
                   ReadInt(reinterpret_cast<uintptr_t>(player) + kGameObjectActualTeamOffset, playerTeam) &&
                   team == playerTeam;
        }

        int ReadSelection(uint32_t (&handles)[RtsCommandsPolicy::kSelectCapacity])
        {
            int n = 0;
            if (!ReadInt(g_ControlPanelAddr + kSelectNumOffset, n) || n <= 0)
                return 0;
            if (n > RtsCommandsPolicy::kSelectCapacity)
                n = RtsCommandsPolicy::kSelectCapacity;
            return ReadBytes(g_ControlPanelAddr + kSelectListOffset, handles, static_cast<size_t>(n) * 4) ? n : 0;
        }

        bool ModifierHeld()
        {
            uint8_t value = 0;
            return g_MultiAddr != 0 && ReadBytes(g_MultiAddr, &value, 1) && value != 0;
        }

        bool SafeSetCommandObj(void* obj, int what, void* target)
        {
            if (!g_FnSetCommandObj || !obj)
                return false;
            __try
            {
                g_FnSetCommandObj(obj, what, target);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // The stock BroadcastCommand(where) passes selectNum as the int64
        // param (FUN_004a70c0 lines 0x004A7113..0x004A711E).
        bool SafeSetCommandWhere(void* obj, int what, const float (&pos)[3], int param)
        {
            if (!g_FnSetCommandWhere || !obj)
                return false;
            __try
            {
                g_FnSetCommandWhere(obj, what, pos, static_cast<uint32_t>(param), param < 0 ? 0xFFFFFFFFu : 0u);
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

        // ---- the table (locked) -----------------------------------------------

        void UpdateQueuedUnits()
        {
            g_QueuedUnits.store(g_Table.UnitCount(), std::memory_order_release);
        }

        void ClearUnit(uint32_t handle, Q::ClearReason reason)
        {
            int dropped = 0;
            {
                std::lock_guard<std::mutex> lock(g_TableMutex);
                dropped = g_Table.Clear(handle);
                UpdateQueuedUnits();
            }
            if (dropped > 0)
                LogBudgeted(L"[ORDERQ] cleared handle=0x%08X entries=%d (%hs)\n", handle, dropped,
                            Q::ReasonName(reason));
        }

        void ClearAllQueues(Q::ClearReason reason)
        {
            int dropped = 0;
            {
                std::lock_guard<std::mutex> lock(g_TableMutex);
                dropped = g_Table.ClearAll();
                UpdateQueuedUnits();
            }
            if (dropped > 0)
                LogBudgeted(L"[ORDERQ] cleared all entries=%d (%hs)\n", dropped, Q::ReasonName(reason));
        }

        // ---- the press ---------------------------------------------------------

        struct PlannedUnit
        {
            uint32_t handle;
            void* obj;
            Q::UnitAction action;
            int depth;
        };

        // Returns true when the press was queued or refused (the stock
        // broadcast must not run); false leaves it to the stock call.
        bool HandlePress(void* panel, int what, void* target, const float* where)
        {
            g_SkipSelectNone = false;
            if (!g_Active.load(std::memory_order_acquire) ||
                reinterpret_cast<uintptr_t>(panel) != g_ControlPanelAddr)
                return false;
            int selectNum = 0;
            ReadInt(g_ControlPanelAddr + kSelectNumOffset, selectNum);
            if (!Q::ShouldQueuePress(true, ModifierHeld(), selectNum, what, ProducerRallyConfirmPending(),
                                     target != nullptr || where != nullptr))
                return false;

            Q::Entry entry;
            entry.cmd = what;
            entry.param = selectNum;
            if (target)
            {
                entry.kind = Q::Kind::Object;
                entry.target = SafeGetHandle(target);
                if (entry.target == 0)
                    return false;
            }
            else
            {
                entry.kind = Q::Kind::Ground;
                if (!ReadBytes(reinterpret_cast<uintptr_t>(where), entry.where, sizeof(entry.where)))
                    return false;
            }

            uint32_t handles[RtsCommandsPolicy::kSelectCapacity];
            const int n = ReadSelection(handles);
            PlannedUnit plan[RtsCommandsPolicy::kSelectCapacity];
            int planned = 0;
            int newUnits = 0;
            bool roomForAll = true;
            {
                std::lock_guard<std::mutex> lock(g_TableMutex);
                for (int i = 0; i < n; ++i)
                {
                    void* const obj = SafeGetObj(handles[i]);
                    const bool eligible = obj && SafeCanCommand(obj) && IsPlayerTeam(obj);
                    const int depth = g_Table.Depth(handles[i]);
                    const bool idle = eligible && RtsCommandsUnitIdle(obj);
                    const Q::UnitAction action = Q::PlanUnit(eligible, depth, idle);
                    if (action == Q::UnitAction::Skip)
                        continue;
                    plan[planned++] = { handles[i], obj, action, depth };
                    if (action == Q::UnitAction::Append)
                    {
                        if (depth == 0)
                            ++newUnits;
                        else if (depth >= Q::kMaxEntries)
                            roomForAll = false;
                    }
                }
                if (planned == 0)
                    return false;
                if (newUnits > Q::kMaxUnits - g_Table.UnitCount())
                    roomForAll = false;
                if (roomForAll)
                {
                    for (int i = 0; i < planned; ++i)
                    {
                        if (plan[i].action != Q::UnitAction::Append)
                            continue;
                        const int depth = g_Table.Push(plan[i].handle, entry);
                        LogBudgeted(L"[ORDERQ] queued handle=0x%08X cmd=%d depth=%d\n", plan[i].handle, what, depth);
                    }
                    UpdateQueuedUnits();
                }
            }
            g_SkipSelectNone = true; // keep the selection so the player can chain
            if (!roomForAll)
            {
                SafePlayRefuse();
                LogBudgeted(L"[ORDERQ] refused (full) cmd=%d units=%d newQueues=%d\n", what, planned, newUnits);
                return true;
            }
            bool issued = false;
            for (int i = 0; i < planned; ++i)
            {
                if (plan[i].action != Q::UnitAction::IssueNow)
                    continue;
                const bool ok = entry.kind == Q::Kind::Object
                                    ? SafeSetCommandObj(plan[i].obj, what, target)
                                    : SafeSetCommandWhere(plan[i].obj, what, entry.where, entry.param);
                issued = issued || ok;
                LogBudgeted(L"[ORDERQ] issued handle=0x%08X cmd=%d (idle, now)%hs\n", plan[i].handle, what,
                            ok ? "" : " FAILED");
            }
            if (issued && target)
                NotifyRtsMarkersCommand(what, target);
            return true;
        }

        // ---- hooks (REL32 call redirects; thiscall callees, ret 8 / plain) ------

        // Entered in place of `call ControlPanel::BroadcastCommand(what, GameObject*)`
        // at 0x004A1F7A (SPACE) and 0x004A25DB (ALT): ecx = panel, then the
        // object and the command pushed (what first on the stack).
        void __fastcall PressObjectHook(void* panel, void*, int what, void* target)
        {
            if (HandlePress(panel, what, target, nullptr))
                return;
            g_FnBroadcastObj(panel, what, target);
            NoteRtsOrderQueuePlainBroadcast(panel);
        }

        // Same for `call ControlPanel::BroadcastCommand(what, const VECTOR_3D*)`
        // at 0x004A1FB0 (SPACE) and 0x004A2611 (ALT).
        void __fastcall PressWhereHook(void* panel, void*, int what, const float* where)
        {
            if (HandlePress(panel, what, nullptr, where))
                return;
            g_FnBroadcastWhere(panel, what, where);
            NoteRtsOrderQueuePlainBroadcast(panel);
        }

        // Entered in place of `call ControlPanel::SelectNone` at 0x004A1FD7 and
        // 0x004A2638, right after the press: a queued or refused press keeps
        // the selection.
        void __fastcall SelectNoneHook(void* panel, void*)
        {
            if (g_SkipSelectNone)
            {
                g_SkipSelectNone = false;
                return;
            }
            if (g_FnSelectNone)
                g_FnSelectNone(panel);
        }

        // ---- labels -----------------------------------------------------------

        const char* LabelFor(bool alt, const char* stock)
        {
            if (!stock || !g_Active.load(std::memory_order_acquire))
                return stock;
            int cmd = 0;
            int selectNum = 0;
            if (!ReadInt(g_ControlPanelAddr + (alt ? kAltButtonCommandOffset : kCmdButtonCommandOffset), cmd) ||
                !ReadInt(g_ControlPanelAddr + kSelectNumOffset, selectNum))
                return stock;
            if (!Q::QueueArmed(true, ModifierHeld(), selectNum, cmd) || ProducerRallyConfirmPending())
                return stock;
            static char buffers[2][Q::kLabelCapacity];
            const char* prefix = "Queue";
            try
            {
                const char* const text = ShimText("openshim_ui:rts_order_queue_prefix", "Queue");
                if (text && text[0])
                    prefix = text;
            }
            catch (...)
            {
            }
            char* const out = buffers[alt ? 1 : 0];
            return Q::FormatQueueLabel(prefix, stock, out, Q::kLabelCapacity) ? out : stock;
        }

        // Entered in place of `call UiLocalize("names", key)` at 0x004A26C1
        // (cdecl, the ALT row label).
        const char* __cdecl AltLabelLocalize(const char* section, const char* key)
        {
            return LabelFor(true, g_FnLocalize(section, key));
        }

        // ---- install ----------------------------------------------------------

        // Returns the original callee, or 0 (left stock).
        uint32_t RedirectCall(uint32_t site, const void* target, uint32_t expectedCallee, const char* name)
        {
            uint8_t original[5] = {};
            if (!ReadBytes(site, original, sizeof(original)) || original[0] != 0xE8)
            {
                if (InterlockedDecrement(&g_InstallLogBudget) >= 0)
                    Log(L"[ORDERQ] %hs: no call at 0x%08X; left stock\n", name, site);
                return 0;
            }
            int32_t rel = 0;
            std::memcpy(&rel, original + 1, sizeof(rel));
            const uint32_t callee = site + 5 + static_cast<uint32_t>(rel);
            if (expectedCallee != 0 && callee != expectedCallee)
            {
                if (InterlockedDecrement(&g_InstallLogBudget) >= 0)
                    Log(L"[ORDERQ] %hs: call at 0x%08X goes to 0x%08X, not 0x%08X; left stock\n", name, site, callee,
                        expectedCallee);
                return 0;
            }
            HookEngine::PatchDef patch;
            patch.address = site;
            patch.type = HookEngine::PatchType::REL32;
            patch.name = name;
            patch.verified = true;
            patch.expected_original.assign(original, original + sizeof(original));
            const int32_t newRel =
                static_cast<int32_t>(reinterpret_cast<uintptr_t>(target)) - static_cast<int32_t>(site + 5);
            patch.payload.assign(5, 0);
            patch.payload[0] = 0xE8;
            std::memcpy(patch.payload.data() + 1, &newRel, sizeof(newRel));
            if (!HookEngine::ApplyPatch(patch))
            {
                if (InterlockedDecrement(&g_InstallLogBudget) >= 0)
                    Log(L"[ORDERQ] %hs: patch refused\n", name);
                return 0;
            }
            Log(L"[ORDERQ] %hs: redirected 0x%08X (was -> 0x%08X)\n", name, site, callee);
            return callee;
        }

        uint32_t CalleeAt(uint32_t site)
        {
            uint8_t original[5] = {};
            if (!ReadBytes(site, original, sizeof(original)) || original[0] != 0xE8)
                return 0;
            int32_t rel = 0;
            std::memcpy(&rel, original + 1, sizeof(rel));
            return site + 5 + static_cast<uint32_t>(rel);
        }

        // The SPACE label chains on ProducerRallyPoints' redirect and the idle
        // read comes from rts_commands.cpp, so both must be in place too.
        bool PartsReady()
        {
            return g_RowsBound && g_SelectNoneReady && g_PressReady && g_AltLabelReady &&
                   RtsCommandsHelpersReady() && ProducerRallySpaceLabelHooked();
        }

        void MarkParts()
        {
            if (PartsReady())
                ClearOptionHookFailed("RtsOrderQueue");
            else
                MarkOptionHookFailed("RtsOrderQueue",
                                     "Unavailable: queued orders did not hook on this game build (see openshim.log).");
        }

        void InstallParts()
        {
#if defined(_M_IX86)
            if (!g_RowsBound)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ControlPanelGlobal", &g_ControlPanelAddr },
                    { "GameObjectHandleGetObj", &g_GetObjAddr },
                    { "GameObjectSetCommandObj", &g_SetCommandObjAddr },
                    { "GameObjectSetCommandWhere", &g_SetCommandWhereAddr },
                    { "ControlPanelBroadcastCommandObj", &g_BroadcastObjAddr },
                    { "ControlPanelSelectNone", &g_SelectNoneAddr },
                    { "UiLocalize", &g_LocalizeAddr },
                    { "CommandMenuUnitBranchInput", &g_MultiAddr },
                    { "ControlPanelCmdObjBroadcastCall", &g_ObjPressRow },
                    { "ControlPanelCmdWhereBroadcastCall", &g_WherePressRow },
                    { "ControlPanelCmdSelectNoneCall", &g_SelectNoneRow },
                    { "ControlPanelAltObjBroadcastCall", &g_AltObjPressRow },
                    { "ControlPanelAltWhereBroadcastCall", &g_AltWherePressRow },
                    { "ControlPanelAltSelectNoneCall", &g_AltSelectNoneRow },
                    { "CommandMenuAltLabelLocalizeCall", &g_AltLabelRow },
                };
                const uint32_t sound = HookEngine::ResolveNamedAddress("PlayGlobalSound");
                if (sound != 0 && g_GameObjectGetHandleAddr != 0 && HookEngine::BindEngineRows("RTS order queue", rows))
                {
                    g_RowsBound = true;
                    g_FnGetObj = reinterpret_cast<FnGetObj>(g_GetObjAddr);
                    g_FnSetCommandObj = reinterpret_cast<FnSetCommandObj>(g_SetCommandObjAddr);
                    g_FnSetCommandWhere = reinterpret_cast<FnSetCommandWhere>(g_SetCommandWhereAddr);
                    g_FnBroadcastObj = reinterpret_cast<FnBroadcastObj>(g_BroadcastObjAddr);
                    g_FnSelectNone = reinterpret_cast<FnSelectNone>(g_SelectNoneAddr);
                    g_FnLocalize = reinterpret_cast<FnLocalize>(g_LocalizeAddr);
                    g_FnPlaySound = reinterpret_cast<FnPlaySound>(sound);
                    Log(L"[ORDERQ] rows bound (panel 0x%08X, multi modifier 0x%08X)\n", g_ControlPanelAddr, g_MultiAddr);
                }
            }
            if (!g_RowsBound)
                return;
            // The SelectNone redirects first: a press hook that keeps the
            // selection is useless (and the flag unread) without them.
            if (!g_SelectNoneReady)
            {
                g_SelectNoneReady =
                    RedirectCall(g_SelectNoneRow, reinterpret_cast<const void*>(&SelectNoneHook), g_SelectNoneAddr,
                                 "ControlPanel::Render/SPACE SelectNone (orderq)") != 0 &&
                    RedirectCall(g_AltSelectNoneRow, reinterpret_cast<const void*>(&SelectNoneHook), g_SelectNoneAddr,
                                 "ControlPanel::Render/ALT SelectNone (orderq)") != 0;
            }
            if (g_SelectNoneReady && !g_PressReady)
            {
                // The ground sites call BroadcastCommand(where) 0x004A70C0 (its
                // rel32 is part of both rows' verified bytes); both must agree.
                const uint32_t whereCallee = CalleeAt(g_WherePressRow);
                if (whereCallee == 0 || whereCallee != CalleeAt(g_AltWherePressRow))
                {
                    if (InterlockedDecrement(&g_InstallLogBudget) >= 0)
                        Log(L"[ORDERQ] the SPACE and ALT ground calls do not share a callee; left stock\n");
                }
                else
                {
                    g_FnBroadcastWhere = reinterpret_cast<FnBroadcastWhere>(static_cast<uintptr_t>(whereCallee));
                    g_PressReady =
                        RedirectCall(g_ObjPressRow, reinterpret_cast<const void*>(&PressObjectHook), g_BroadcastObjAddr,
                                     "ControlPanel::Render/SPACE press obj (orderq)") != 0 &&
                        RedirectCall(g_WherePressRow, reinterpret_cast<const void*>(&PressWhereHook), whereCallee,
                                     "ControlPanel::Render/SPACE press ground (orderq)") != 0 &&
                        RedirectCall(g_AltObjPressRow, reinterpret_cast<const void*>(&PressObjectHook),
                                     g_BroadcastObjAddr, "ControlPanel::Render/ALT press obj (orderq)") != 0 &&
                        RedirectCall(g_AltWherePressRow, reinterpret_cast<const void*>(&PressWhereHook), whereCallee,
                                     "ControlPanel::Render/ALT press ground (orderq)") != 0;
                }
            }
            if (g_PressReady && !g_AltLabelReady)
                g_AltLabelReady = RedirectCall(g_AltLabelRow, reinterpret_cast<const void*>(&AltLabelLocalize),
                                               g_LocalizeAddr, "ControlPanel::Render/ALT label (orderq)") != 0;
#endif
        }

        void ReadConfig()
        {
            bool value = false;
            g_Enabled = TryGetUserConfigBool("Gameplay", "RtsOrderQueue", value) ? value : false;
            g_ConfigRead = true;
        }

        // The drain: one pass over every unit with a queue.
        void DrainOnce(ULONGLONG now)
        {
            uint32_t handles[Q::kMaxUnits];
            int count = 0;
            {
                std::lock_guard<std::mutex> lock(g_TableMutex);
                for (int i = 0; i < Q::kMaxUnits; ++i)
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
                if (!obj || !ObjectAlive(obj) || !IsPlayerTeam(obj))
                {
                    ClearUnit(handle, Q::ClearReason::Dead);
                    continue;
                }
                const bool idle = RtsCommandsUnitIdle(obj);
                for (;;)
                {
                    Q::Entry entry;
                    {
                        std::lock_guard<std::mutex> lock(g_TableMutex);
                        if (!g_Table.PopDue(handle, idle, now) || !g_Table.PopFront(handle, entry))
                            break;
                        UpdateQueuedUnits();
                    }
                    void* target = nullptr;
                    if (entry.kind == Q::Kind::Object)
                    {
                        target = SafeGetObj(entry.target);
                        if (!target || !ObjectAlive(target))
                        {
                            // Dropped without using the gap: try the next entry.
                            LogBudgeted(L"[ORDERQ] dropped handle=0x%08X cmd=%d target=0x%08X (gone)\n", handle,
                                        entry.cmd, entry.target);
                            continue;
                        }
                    }
                    const bool ok = entry.kind == Q::Kind::Object
                                        ? SafeSetCommandObj(obj, entry.cmd, target)
                                        : SafeSetCommandWhere(obj, entry.cmd, entry.where, entry.param);
                    {
                        std::lock_guard<std::mutex> lock(g_TableMutex);
                        g_Table.NoteIssued(handle, now);
                    }
                    LogBudgeted(L"[ORDERQ] issued handle=0x%08X cmd=%d (from queue)%hs\n", handle, entry.cmd,
                                ok ? "" : " FAILED");
                    break;
                }
            }
        }
    }

    // ---- public ----------------------------------------------------------------

    void ReloadRtsOrderQueueConfig()
    {
        ReadConfig();
        RefreshRtsOrderQueueState();
    }

    // Patch thread, retried from InstallAiTuningHooksIfPossible.
    void InstallRtsOrderQueueIfPossible()
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
            Log(L"[ORDERQ] install %hs after %d attempt(s): rows %hs, SelectNone %hs, press %hs, ALT label %hs, "
                L"SPACE label chain %hs\n",
                PartsReady() ? "complete" : "gave up", s_attempts, g_RowsBound ? "yes" : "no",
                g_SelectNoneReady ? "yes" : "no", g_PressReady ? "yes" : "no", g_AltLabelReady ? "yes" : "no",
                ProducerRallySpaceLabelHooked() ? "yes" : "no");
        }
        RefreshRtsOrderQueueState();
    }

    // Config reload, mission gate reconcile (every 250 ms) and install: the
    // feature is active while it is on, every part is in place and the
    // session is single player; anything else drops the queues.
    void RefreshRtsOrderQueueState()
    {
        if (!g_ConfigRead)
            ReadConfig();
        const bool ready = PartsReady();
        // The SPACE label chain can come up after the install passes end, so
        // the option's availability follows the live answer (change-only).
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
            Log(L"[ORDERQ] active=%d (option %d, hooks %d, single player %d)\n", want ? 1 : 0, g_Enabled ? 1 : 0,
                ready ? 1 : 0, sp ? 1 : 0);
        if (!want)
            ClearAllQueues(g_Enabled && ready && !sp ? Q::ClearReason::Multiplayer : Q::ClearReason::OptionOff);
    }

    // Mission end / load: handles of the old world must never reach the next.
    void ResetRtsOrderQueue()
    {
        ClearAllQueues(Q::ClearReason::Reset);
        g_SkipSelectNone = false;
        g_LastDrainMs = 0;
        g_LogBudget = 96;
        RefreshRtsOrderQueueState();
    }

    void TickRtsOrderQueue()
    {
        if (!g_Active.load(std::memory_order_acquire) || g_QueuedUnits.load(std::memory_order_acquire) == 0)
            return;
        if (!InsideRenderQueueHookWithDeferral())
            RunRtsOrderQueue();
    }

    // Frame thread (RunDeferredSceneMutations, or the world render tick when
    // the drain is not installed), the same thread rts_commands.cpp issues its
    // orders from; SetCommand never runs anywhere else.
    void RunRtsOrderQueue() noexcept
    {
        try
        {
            if (!g_Active.load(std::memory_order_acquire) || g_QueuedUnits.load(std::memory_order_acquire) == 0)
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
            LogBudgeted(L"[ORDERQ] the drain threw; skipped\n");
        }
    }

    bool RtsOrderQueueDrawActive()
    {
        return g_Active.load(std::memory_order_acquire) && g_QueuedUnits.load(std::memory_order_acquire) > 0;
    }

    int RtsOrderQueueSnapshot(uint32_t handle, Q::Entry* out, int capacity)
    {
        std::lock_guard<std::mutex> lock(g_TableMutex);
        return g_Table.Snapshot(handle, out, capacity);
    }

    void NoteRtsOrderQueuePlainOrder(const uint32_t* handles, int count)
    {
        if (!g_Active.load(std::memory_order_acquire) || g_QueuedUnits.load(std::memory_order_acquire) == 0 || !handles)
            return;
        for (int i = 0; i < count; ++i)
            ClearUnit(handles[i], Q::ClearReason::PlainOrder);
    }

    void NoteRtsOrderQueuePlainBroadcast(void* panel)
    {
        if (!g_Active.load(std::memory_order_acquire) || g_QueuedUnits.load(std::memory_order_acquire) == 0 ||
            reinterpret_cast<uintptr_t>(panel) != g_ControlPanelAddr)
            return;
        uint32_t handles[RtsCommandsPolicy::kSelectCapacity];
        const int n = ReadSelection(handles);
        NoteRtsOrderQueuePlainOrder(handles, n);
    }

    const char* RtsOrderQueueSpaceLabel(const char* stockLabel)
    {
        return LabelFor(false, stockLabel);
    }
}
