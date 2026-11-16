// rts_commands.cpp
// BZR Open Shim - RTS command extras for the stock unit command menu.
//
//   [Gameplay] RtsRemoteTarget (default ON)
//     * Shift+T (RtsRemoteTargetKey) sets the player's target to a selected
//       own unit without touching the selection; each press moves to the next
//       selected unit. Stock T (frontal_target) never sees the press.
//     * B (RtsBuildingCycleKey) cycles the target through the player's
//       buildings (Recycler, Factory and Armory included), newest first.
//   [Gameplay] RtsSmartCommandMenu (default ON)
//     * A mixed selection (a Ctrl+1 group of wingmen, walkers, APCs,
//       howitzers) keeps Hunt, Follow Close (Formation) and Defend in the
//       menu; each is sent only to the units whose own menu offers it.
//   [Gameplay] RtsSmartRepairReload (default ON)
//     * Get Repair / Get Reload show when any selected unit needs them and
//       go only to the units that do.
//   [Gameplay] RtsAreaSelect (default ON)
//     * X (RtsAreaSelectKey) adds the player's units of the same family as
//       the reticle object (else the first selected unit) within 100 m;
//       Shift+X within 200 m.
//   [Gameplay] RtsHold (default 2: key and Shift menu; 1 key only; 0 off)
//     * Z (RtsHoldKey) gives the selected units that have a Defend entry
//       Defend(0) plus the native hold. With Shift held the Defend entry
//       reads "Hold" and choosing it does the same. Single player only, like
//       the native hold it uses (ai_native_orders.cpp SetAiHold).
// Rules: include/rts_commands_policy.h. Evidence and limits:
// Docs/RTS_COMMANDS.md. Every address is a scripts/patches.json row; each
// part binds its own rows and stays stock (option marked unavailable) when
// they do not match. Orders go through the stock per-unit calls the menu
// itself uses (ExecuteMode, GameObject::SetCommand), never AI state.
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "game_state.h"
#include "hook_engine.h"
#include "iat_patch.h"
#include "openshim_l10n_text.h"
#include "patcher.h"
#include "quicksave.h"
#include "quicksave_key_policy.h"
#include "rts_commands_policy.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

using BZROpenShim::L10n::ShimText;

namespace BZROpenShim::Hooks
{
    namespace
    {
        namespace Policy = RtsCommandsPolicy;

        using FnGetObj = void*(__cdecl*)(uint32_t handle);
        using FnGetHandle = uint32_t(__thiscall*)(void* obj);
        using FnCanCommand = bool(__thiscall*)(void* obj);
        using FnExecuteMode = bool(__thiscall*)(void* obj, int mode);
        using FnIntersect = void(__thiscall*)(void* merged, const void* other);
        using FnDispatchMode = bool(__thiscall*)(void* panel, int mode);
        using FnBroadcastObj = void(__thiscall*)(void* panel, int what, void* target);
        using FnSetCommandObj = void(__thiscall*)(void* obj, int what, void* target);
        using FnSetCommand = void(__thiscall*)(void* obj, int what);
        using FnSetTarget = void(__thiscall*)(void* obj, void* target);
        using FnSelectAdd = void(__thiscall*)(void* panel, void* obj);
        using FnSelectNone = void(__thiscall*)(void* panel);
        using FnLocalize = const char*(__cdecl*)(const char* section, const char* key);
        using FnPlaySound = int(__cdecl*)(const char* filename, uint32_t, uint32_t, uint32_t);
        using FnGetPosition = const float*(__thiscall*)(void* entity);

        // ControlPanel fields (FUN_004a7140, FUN_004a6c70; ControlPanelGlobal row).
        constexpr size_t kSelectListOffset = 0x1C;
        constexpr size_t kSelectNumOffset = 0x188;
        // The merged unit menu ControlPanel::Render builds (FUN_004a08e0 line 798).
        constexpr size_t kMergedModeListOffset = 0x113C;
        // GameObject +0x1A4: its ModeList (FUN_0049f430, GameObjectGetModeList row).
        constexpr size_t kModeListOffset = 0x1A4;
        constexpr size_t kCanCommandSlot = 14;  // vtable +0x38 (FUN_004a7140 line 13)
        constexpr size_t kExecuteModeSlot = 11; // vtable +0x2C (FUN_004a7140 line 15)
        constexpr size_t kPositionSlot = 3;     // Entity at +0x18, vtable +0xC
        constexpr size_t kEntityOffset = 0x18;
        // Reticle (ReticleGlobal): +0xA8 VECTOR_3D* ground hit, +0xAC the
        // GameObject* under the reticle; both zero when nothing is picked
        // (Reticle::Simulate FUN_005ba560 lines 150-179).
        constexpr size_t kReticleGroundPosOffset = 0xA8;
        constexpr size_t kReticleObjectOffset = 0xAC;
        // Call-site rows: the E8 is this far into each row.
        constexpr uint32_t kMergeCallOffset = 0xD;
        constexpr uint32_t kDispatchCallOffset = 0xD;
        constexpr uint32_t kDefendClickCallOffset = 0x14;
        constexpr uint32_t kDefendClickResumeOffset = 0x9C; // the row's `jmp` target, 0x004A5141
        constexpr uint32_t kBroadcastCallOffset = 0xF;
        constexpr uint32_t kLabelCallOffset = 0x13;
        constexpr int kMaxInstallAttempts = 40;
        constexpr size_t kMaxObjects = 4096;
        constexpr ULONGLONG kTickFreshMs = 500;
        constexpr const char* kClickSound = "mnu_clik.wav";

        // Shared rows.
        uint32_t g_ControlPanelAddr = 0;
        uint32_t g_ControlPanelVtableAddr = 0;
        uint32_t g_GetObjAddr = 0;
        uint32_t g_GetModeListAddr = 0;
        uint32_t g_EditModeFlagAddr = 0;
        uint32_t g_ObjectListGlobal = 0;
        // Menu parts.
        uint32_t g_MergeRowAddr = 0;
        uint32_t g_IntersectAddr = 0;
        uint32_t g_DispatchRowAddr = 0;
        uint32_t g_DispatchAddr = 0;
        uint32_t g_BroadcastRowAddr = 0;
        uint32_t g_BroadcastObjAddr = 0;
        uint32_t g_SetCommandObjAddr = 0;
        // Targets / area select / hold.
        uint32_t g_SetTargetAddr = 0;
        uint32_t g_SelectAddAddr = 0;
        uint32_t g_SelectNoneAddr = 0;
        uint32_t g_ReticleAddr = 0;
        uint32_t g_SetCommandAddr = 0;
        uint32_t g_DefendClickRowAddr = 0;
        uint32_t g_LabelRowAddr = 0;
        uint32_t g_LocalizeAddr = 0;
        // Read by the naked thunks.
        uint32_t g_PlaySoundAddr = 0;
        uint32_t g_DefendClickResumeAddr = 0;

        FnGetObj g_FnGetObj = nullptr;
        FnIntersect g_FnIntersect = nullptr;
        FnDispatchMode g_FnDispatch = nullptr;
        FnBroadcastObj g_FnBroadcastObj = nullptr;
        FnSetCommandObj g_FnSetCommandObj = nullptr;
        FnSetCommand g_FnSetCommand = nullptr;
        FnSetTarget g_FnSetTarget = nullptr;
        FnSelectAdd g_FnSelectAdd = nullptr;
        FnSelectNone g_FnSelectNone = nullptr;
        FnLocalize g_FnLocalize = nullptr;
        FnPlaySound g_FnPlaySound = nullptr;

        // Config ([Gameplay]); main thread.
        bool g_ConfigRead = false;
        bool g_TargetEnabled = true;
        bool g_SmartMenuEnabled = true;
        bool g_SmartRepairEnabled = true;
        bool g_AreaEnabled = true;
        int g_HoldMode = Policy::kHoldKeyAndShiftMenu;

        // Part readiness (patch thread, then read-only).
        bool g_SharedReady = false;
        bool g_MergeReady = false;
        bool g_DispatchReady = false;
        bool g_BroadcastReady = false;
        bool g_TargetReady = false;
        bool g_AreaReady = false;
        bool g_HoldKeyReady = false;
        bool g_HoldClickReady = false;
        bool g_LabelReady = false;

        // Live state.
        std::atomic<unsigned> g_SmartMask{ 0 }; // Policy::SmartSet bits in force
        std::atomic<bool> g_TargetActive{ false };
        std::atomic<bool> g_AreaActive{ false };
        std::atomic<bool> g_HoldKeyActive{ false };
        std::atomic<bool> g_HoldMenuActive{ false };
        std::atomic<ULONGLONG> g_LastTickMs{ 0 };
        // Actions queued by the key filter (main thread) for the tick.
        std::atomic<bool> g_PendingRemoteTarget{ false };
        std::atomic<bool> g_PendingBuilding{ false };
        std::atomic<int> g_PendingArea{ 0 }; // 1: 100 m, 2: 200 m
        std::atomic<bool> g_PendingHold{ false };
        volatile long g_LogBudget = 48;

        // Keys (main thread: both filters and the key-binding editor).
        Policy::Key g_Keys[Policy::kKeyCount] = {};
        std::string g_KeyText[Policy::kKeyCount];
        Policy::KeyLatch g_Latch[Policy::kKeyCount] = {};
        HWND g_Window = nullptr;
        WNDPROC g_PrevWndProc = nullptr;
        bool g_SubclassAttempted = false;
        bool g_PeekAttempted = false;
        using PFN_PeekMessageA = BOOL(WINAPI*)(LPMSG, HWND, UINT, UINT, UINT);
        PFN_PeekMessageA g_RealPeekMessageA = nullptr;

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

        // ---- fault-safe engine access (no C++ objects, so __try is legal) ----

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

        bool WriteBytes(uintptr_t address, const void* data, size_t size)
        {
            if (address < 0x10000)
                return false;
            __try
            {
                std::memcpy(reinterpret_cast<void*>(address), data, size);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
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

        void* VirtualSlot(void* obj, size_t slot)
        {
            void* const vtable = ReadPtr(reinterpret_cast<uintptr_t>(obj));
            return vtable ? ReadPtr(reinterpret_cast<uintptr_t>(vtable) + slot * sizeof(void*)) : nullptr;
        }

        bool SafeCanCommand(void* obj)
        {
            void* const fn = VirtualSlot(obj, kCanCommandSlot);
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

        // The unit's own GameObject::ExecuteMode (vtable slot 11), as
        // ControlPanel::DispatchMode (FUN_004a7140 line 15) calls it.
        bool SafeExecuteMode(void* obj, int mode, bool& result)
        {
            void* const fn = VirtualSlot(obj, kExecuteModeSlot);
            if (!fn)
                return false;
            __try
            {
                result = reinterpret_cast<FnExecuteMode>(fn)(obj, mode);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeSetCommandObj(void* obj, int what, void* target)
        {
            if (!g_FnSetCommandObj)
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

        bool SafeSetCommand(void* obj, int what)
        {
            if (!g_FnSetCommand)
                return false;
            __try
            {
                g_FnSetCommand(obj, what);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeSetTarget(void* user, void* target)
        {
            if (!g_FnSetTarget || !user)
                return false;
            __try
            {
                g_FnSetTarget(user, target);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeSelectAdd(void* panel, void* obj)
        {
            if (!g_FnSelectAdd)
                return false;
            __try
            {
                g_FnSelectAdd(panel, obj);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeSelectNone(void* panel)
        {
            if (!g_FnSelectNone)
                return false;
            __try
            {
                g_FnSelectNone(panel);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void SafePlayClick()
        {
            if (!g_FnPlaySound)
                return;
            __try
            {
                g_FnPlaySound(kClickSound, 0, 0, 0);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        bool SafeGetPosition(void* obj, float (&out)[3])
        {
            if (!obj)
                return false;
            void* const entity = reinterpret_cast<uint8_t*>(obj) + kEntityOffset;
            void* const fn = VirtualSlot(entity, kPositionSlot);
            if (!fn)
                return false;
            __try
            {
                const float* pos = reinterpret_cast<FnGetPosition>(fn)(entity);
                if (!pos)
                    return false;
                out[0] = pos[0];
                out[1] = pos[1];
                out[2] = pos[2];
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // The object's most-derived MSVC RTTI type name (CompleteObjectLocator
        // at vtable[-1], TypeDescriptor at +0xC, name at +8), or null.
        const char* RttiName(void* obj)
        {
            const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(reinterpret_cast<uintptr_t>(obj)));
            if (!vtable)
                return nullptr;
            const uintptr_t col = reinterpret_cast<uintptr_t>(ReadPtr(vtable - sizeof(void*)));
            const uintptr_t td = col ? reinterpret_cast<uintptr_t>(ReadPtr(col + 0x0C)) : 0;
            char probe[2] = {};
            if (!td || !ReadBytes(td + 0x08, probe, sizeof(probe)))
                return nullptr;
            return reinterpret_cast<const char*>(td + 0x08);
        }

        bool ReadModeList(void* obj, Policy::ModeList& out)
        {
            return obj && ReadBytes(reinterpret_cast<uintptr_t>(obj) + kModeListOffset, &out, sizeof(out));
        }

        void* UserObject()
        {
            const uintptr_t slot = EngineGlobals::UserObjectSlot();
            return slot ? ReadPtr(slot) : nullptr;
        }

        bool IsPlayerTeam(void* obj)
        {
            void* const player = UserObject();
            int team = -1;
            int playerTeam = -2;
            return obj && player &&
                   ReadInt(reinterpret_cast<uintptr_t>(obj) + kGameObjectActualTeamOffset, team) &&
                   ReadInt(reinterpret_cast<uintptr_t>(player) + kGameObjectActualTeamOffset, playerTeam) &&
                   team == playerTeam;
        }

        bool ControlPanelIdentityOk()
        {
            const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(g_ControlPanelAddr));
            return vtable != 0 && vtable == g_ControlPanelVtableAddr &&
                   VtableTypeNameMatches(vtable, ".?AVControlPanel@@");
        }

        int ReadSelection(uint32_t (&handles)[Policy::kSelectCapacity])
        {
            int n = 0;
            if (!ReadInt(g_ControlPanelAddr + kSelectNumOffset, n) || n <= 0)
                return 0;
            if (n > Policy::kSelectCapacity)
                n = Policy::kSelectCapacity;
            return ReadBytes(g_ControlPanelAddr + kSelectListOffset, handles, static_cast<size_t>(n) * 4) ? n : 0;
        }

        // The engine's object vector (GameObject::objectList: _Myfirst at +0,
        // _Mylast at +4; lua_handle_sync.cpp SnapshotObjects).
        size_t SnapshotObjects(void** out, size_t capacity)
        {
            if (!g_ObjectListGlobal)
                return 0;
            size_t count = 0;
            __try
            {
                const uint8_t* vec = *reinterpret_cast<uint8_t* const*>(g_ObjectListGlobal);
                if (!vec)
                    return 0;
                void* const* first = *reinterpret_cast<void* const* const*>(vec);
                void* const* last = *reinterpret_cast<void* const* const*>(vec + 4);
                if (!first || last < first)
                    return 0;
                const size_t available = static_cast<size_t>(last - first);
                if (available > kMaxObjects)
                    return 0;
                for (size_t i = 0; i < available && count < capacity; ++i)
                {
                    if (first[i])
                        out[count++] = first[i];
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
            return count;
        }

        void* g_ObjectScratch[kMaxObjects] = {};

        // ---- the command menu: merge, dispatch, Defend target ----------------

        // Entered in place of `call ModeList::Intersect` at 0x004A2E33 (thiscall:
        // ecx = the merged list at ControlPanel +0x113C, one stack argument).
        void __fastcall MergeHook(void* merged, void*, const void* other)
        {
            const unsigned smart = g_SmartMask.load(std::memory_order_acquire);
            if (smart == 0 ||
                reinterpret_cast<uintptr_t>(merged) != g_ControlPanelAddr + kMergedModeListOffset)
            {
                g_FnIntersect(merged, other);
                return;
            }
            Policy::ModeList a;
            Policy::ModeList b;
            if (!ReadBytes(reinterpret_cast<uintptr_t>(merged), &a, sizeof(a)) ||
                !ReadBytes(reinterpret_cast<uintptr_t>(other), &b, sizeof(b)))
            {
                g_FnIntersect(merged, other);
                return;
            }
            Policy::SmartIntersect(a, b, smart);
            WriteBytes(reinterpret_cast<uintptr_t>(merged), &a, sizeof(a));
        }

        // Entered in place of `call ControlPanel::DispatchMode` at 0x004A512A
        // (thiscall: ecx = panel, the chosen mode). A smart mode goes only to
        // the commandable units whose own menu holds it; skipped units count
        // as accepted, so the selection still clears as stock does.
        bool __fastcall DispatchHook(void* panel, void*, int mode)
        {
            const unsigned smart = g_SmartMask.load(std::memory_order_acquire);
            if (!Policy::IsSmartMode(mode, smart) || reinterpret_cast<uintptr_t>(panel) != g_ControlPanelAddr)
                return g_FnDispatch(panel, mode);
            uint32_t handles[Policy::kSelectCapacity];
            const int n = ReadSelection(handles);
            bool all = true;
            int sent = 0;
            int skipped = 0;
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                if (!obj || !SafeCanCommand(obj))
                    continue;
                Policy::ModeList own;
                if (!ReadModeList(obj, own) || !Policy::SendModeToUnit(mode, own, smart))
                {
                    ++skipped;
                    continue;
                }
                bool accepted = true;
                if (!SafeExecuteMode(obj, mode, accepted))
                    accepted = false;
                all = all && accepted;
                ++sent;
            }
            if (skipped > 0)
                LogBudgeted(L"[RTS] mode %d sent to %d unit(s), %d skipped (no such entry)\n", mode, sent, skipped);
            return all;
        }

        // Entered in place of `call ControlPanel::BroadcastCommand(obj)` at
        // 0x004A3688, the Defend submenu's target pick (always CMD_DEFEND).
        void __fastcall BroadcastHook(void* panel, void*, int what, void* target)
        {
            const unsigned smart = g_SmartMask.load(std::memory_order_acquire);
            if ((smart & Policy::kSmartCommandMenu) == 0 || what != Policy::kCmdDefend ||
                reinterpret_cast<uintptr_t>(panel) != g_ControlPanelAddr)
            {
                g_FnBroadcastObj(panel, what, target);
                return;
            }
            uint32_t handles[Policy::kSelectCapacity];
            const int n = ReadSelection(handles);
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                if (!obj || !SafeCanCommand(obj))
                    continue;
                Policy::ModeList own;
                if (!ReadModeList(obj, own) || !Policy::UnitTakesMode(own, Policy::kModeDefend))
                    continue;
                SafeSetCommandObj(obj, what, target);
            }
        }

        // ---- Hold ------------------------------------------------------------

        bool HoldAvailableNow()
        {
            return IsSinglePlayerSession();
        }

        // Defend(0) (GameObject::SetCommand(CMD_DEFEND): who = 0 builds the
        // SitTask, FUN_004dbce0) plus the native hold, for each selected own
        // commandable unit whose menu has Defend. Returns how many held.
        int HoldSelection()
        {
            uint32_t handles[Policy::kSelectCapacity];
            const int n = ReadSelection(handles);
            int held = 0;
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                if (!obj || !IsPlayerTeam(obj) || !SafeCanCommand(obj))
                    continue;
                Policy::ModeList own;
                if (!ReadModeList(obj, own) || !Policy::UnitTakesMode(own, Policy::kModeDefend))
                    continue;
                if (!SafeSetCommand(obj, Policy::kCmdDefend))
                    continue;
                bool ok = false;
                try
                {
                    ok = SetAiHold(static_cast<int>(handles[i]), true);
                }
                catch (...)
                {
                    ok = false;
                }
                if (ok)
                    ++held;
            }
            return held;
        }

        // The Defend entry was chosen (mouse or its number key). With Shift
        // held and the alternate on, Hold replaces opening the submenu.
        bool __cdecl DefendClickDecide(void* panel)
        {
            if (!g_HoldMenuActive.load(std::memory_order_acquire) ||
                reinterpret_cast<uintptr_t>(panel) != g_ControlPanelAddr || GetKeyState(VK_SHIFT) >= 0 ||
                !HoldAvailableNow())
                return false;
            const int held = HoldSelection();
            if (held <= 0)
                return false;
            SafePlayClick();
            SafeSelectNone(panel);
            LogBudgeted(L"[RTS] Shift+Defend: %d unit(s) holding\n", held);
            return true;
        }

        const char* __cdecl ModeLabelDecide(const char* section, const char* key, int mode)
        {
            const char* const stock = g_FnLocalize(section, key);
            if (!Policy::ShowHoldLabel(g_HoldMenuActive.load(std::memory_order_acquire),
                                       GetKeyState(VK_SHIFT) < 0, mode) ||
                !HoldAvailableNow())
                return stock;
            try
            {
                const char* const hold = ShimText("openshim_ui:rts_hold_label", "Hold");
                return hold && hold[0] ? hold : stock;
            }
            catch (...)
            {
                return stock;
            }
        }

#if defined(_M_IX86)
        // Entered in place of `call PlayGlobalSound("mnu_next.wav",0,0,0)` at
        // 0x004A50B9, the Defend entry's click (ControlPanel::Render, mode
        // [ebp-0x28C] == 0x11, this [ebp-0x244]; RtsDefendClickSoundCall).
        // Stock: tail-jump to the sound and fall through to opening the
        // submenu. Hold: drop the return address and the four cdecl
        // arguments and resume where the stock branch jumps (0x004A5141).
        __declspec(naked) void DefendClickThunk()
        {
            __asm
            {
                mov eax, dword ptr [ebp - 0x244]
                push eax
                call DefendClickDecide
                add esp, 4
                test al, al
                jnz handled
                jmp dword ptr [g_PlaySoundAddr]
            handled:
                add esp, 0x14
                jmp dword ptr [g_DefendClickResumeAddr]
            }
        }

        // Entered in place of `call UiLocalize("names", modeName)` at
        // 0x004A57BE (cdecl, [esp+4] section, [esp+8] key); the mode is
        // [ebp-0x28C] in ControlPanel::Render's frame (RtsModeLabelLocalizeCall).
        __declspec(naked) void ModeLabelThunk()
        {
            __asm
            {
                mov eax, dword ptr [ebp - 0x28C]
                push eax
                push dword ptr [esp + 0x0C]
                push dword ptr [esp + 0x0C]
                call ModeLabelDecide
                add esp, 0x0C
                ret
            }
        }
#endif

        // ---- key actions (tick, game thread) -----------------------------------

        void DoRemoteTarget()
        {
            void* const user = UserObject();
            if (!user)
                return;
            uint32_t handles[Policy::kSelectCapacity];
            const int n = ReadSelection(handles);
            uint32_t own[Policy::kSelectCapacity];
            int count = 0;
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                if (obj && obj != user && IsPlayerTeam(obj))
                    own[count++] = handles[i];
            }
            int current = 0;
            ReadInt(reinterpret_cast<uintptr_t>(user) + kGameObjectTargetHandleOffset, current);
            const uint32_t next = Policy::NextInCycle(own, count, static_cast<uint32_t>(current));
            void* const target = SafeGetObj(next);
            if (!target)
                return;
            if (SafeSetTarget(user, target))
                LogBudgeted(L"[RTS] target -> selected unit 0x%08X (%d selected)\n", next, count);
        }

        void DoBuildingCycle()
        {
            void* const user = UserObject();
            if (!user)
                return;
            const size_t n = SnapshotObjects(g_ObjectScratch, kMaxObjects);
            uint32_t buildings[512];
            int count = 0;
            for (size_t i = 0; i < n && count < static_cast<int>(sizeof(buildings) / sizeof(buildings[0])); ++i)
            {
                void* const obj = g_ObjectScratch[i];
                if (obj == user || !IsPlayerTeam(obj))
                    continue;
                const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(reinterpret_cast<uintptr_t>(obj)));
                if (!vtable || !Policy::IsBaseStructure(VtableDerivesFrom(vtable, ".?AVBuilding@@"), RttiName(obj)))
                    continue;
                const uint32_t handle = SafeGetHandle(obj);
                if (handle != 0)
                    buildings[count++] = handle;
            }
            Policy::SortNewestFirst(buildings, count);
            int current = 0;
            ReadInt(reinterpret_cast<uintptr_t>(user) + kGameObjectTargetHandleOffset, current);
            const uint32_t next = Policy::NextInCycle(buildings, count, static_cast<uint32_t>(current));
            void* const target = SafeGetObj(next);
            if (!target)
                return;
            if (SafeSetTarget(user, target))
                LogBudgeted(L"[RTS] target -> building 0x%08X (%d buildings)\n", next, count);
        }

        bool IsLiveObject(void* obj, size_t snapshotCount)
        {
            for (size_t i = 0; i < snapshotCount; ++i)
            {
                if (g_ObjectScratch[i] == obj)
                    return true;
            }
            return false;
        }

        void DoAreaSelect(bool wide)
        {
            const size_t n = SnapshotObjects(g_ObjectScratch, kMaxObjects);
            if (n == 0)
                return;
            uint32_t selected[Policy::kSelectCapacity];
            const int selectedCount = ReadSelection(selected);

            // Family: the reticle object when it is an own commandable unit
            // with a family, else the first selected unit.
            void* const picked = ReadPtr(g_ReticleAddr + kReticleObjectOffset);
            const bool pickedLive = picked && IsLiveObject(picked, n);
            Policy::Family family = Policy::Family::None;
            if (pickedLive && IsPlayerTeam(picked) && SafeCanCommand(picked))
                family = Policy::ClassifyFamily(RttiName(picked));
            void* first = nullptr;
            if (selectedCount > 0)
                first = SafeGetObj(selected[0]);
            if (family == Policy::Family::None && first)
                family = Policy::ClassifyFamily(RttiName(first));
            if (family == Policy::Family::None)
            {
                LogBudgeted(L"[RTS] area select: no unit family under the reticle or selected\n");
                return;
            }

            // Centre: the reticle object, else the ground under the reticle,
            // else (satellite view, sky) the first selected unit.
            float centre[3] = {};
            bool haveCentre = pickedLive && SafeGetPosition(picked, centre);
            if (!haveCentre)
            {
                const uintptr_t ground = reinterpret_cast<uintptr_t>(ReadPtr(g_ReticleAddr + kReticleGroundPosOffset));
                haveCentre = ground && ReadBytes(ground, centre, sizeof(centre));
            }
            if (!haveCentre)
                haveCentre = first && SafeGetPosition(first, centre);
            if (!haveCentre)
                return;

            static Policy::AreaCandidate candidates[kMaxObjects];
            int candidateCount = 0;
            for (size_t i = 0; i < n; ++i)
            {
                void* const obj = g_ObjectScratch[i];
                if (!IsPlayerTeam(obj) || obj == UserObject())
                    continue;
                const Policy::Family f = Policy::ClassifyFamily(RttiName(obj));
                if (f != family)
                    continue;
                Policy::AreaCandidate& c = candidates[candidateCount];
                c.handle = SafeGetHandle(obj);
                c.family = f;
                c.ownCommandable = c.handle != 0 && SafeCanCommand(obj) && SafeGetPosition(obj, c.pos);
                if (c.ownCommandable)
                    ++candidateCount;
            }
            uint32_t add[Policy::kSelectCapacity];
            const float radius = wide ? Policy::kAreaRadiusWide : Policy::kAreaRadius;
            const int count = Policy::PlanAreaAdd(selected, selectedCount, candidates, candidateCount, family, centre,
                                                  radius, add, Policy::kSelectCapacity);
            int added = 0;
            for (int i = 0; i < count; ++i)
            {
                // Re-read: SelectAdd appends with no room check.
                int now = 0;
                if (!ReadInt(g_ControlPanelAddr + kSelectNumOffset, now) || now >= Policy::kSelectCapacity)
                    break;
                void* const obj = SafeGetObj(add[i]);
                if (obj && SafeSelectAdd(reinterpret_cast<void*>(g_ControlPanelAddr), obj))
                    ++added;
            }
            LogBudgeted(L"[RTS] area select (%hs, %.0f m): %d added to %d selected\n", Policy::FamilyName(family),
                        radius, added, selectedCount);
        }

        void DoHoldKey()
        {
            if (!HoldAvailableNow())
                return;
            const int held = HoldSelection();
            LogBudgeted(L"[RTS] Hold key: %d unit(s) holding\n", held);
        }

        // ---- keys ----------------------------------------------------------------

        bool EditorActive()
        {
            int flag = 1;
            if (!ReadInt(g_EditModeFlagAddr, flag))
                return true;
            return flag == 1;
        }

        bool WorldInteractive()
        {
            if (!SatelliteWorldIsLive() || !UserObject())
                return false;
            if (IsPauseMenuOpen())
                return false;
            const ShellUiState ui = ReadShellUiState();
            if (!ui.readable)
                return false;
            return !(ui.wrapperActive && ui.screenPresent && IsNonGameplayScreenType(ui.screenType));
        }

        bool SelectionHasOwnUnit()
        {
            uint32_t handles[Policy::kSelectCapacity];
            const int n = ReadSelection(handles);
            for (int i = 0; i < n; ++i)
            {
                if (IsPlayerTeam(SafeGetObj(handles[i])))
                    return true;
            }
            return false;
        }

        bool KeyActionActive(Policy::KeyId id)
        {
            switch (id)
            {
            case Policy::KeyId::RemoteTarget:
            case Policy::KeyId::BuildingCycle:
                return g_TargetActive.load(std::memory_order_acquire);
            case Policy::KeyId::AreaSelect:
                return g_AreaActive.load(std::memory_order_acquire);
            case Policy::KeyId::Hold:
                return g_HoldKeyActive.load(std::memory_order_acquire) && HoldAvailableNow();
            default:
                return false;
            }
        }

        // The rally key wins a shared key (it can be rebound after ours).
        bool IsRallyKey(const Policy::Key& key)
        {
            QuickSaveKeyPolicy::Chord rally;
            return QuickSaveKeyPolicy::ParseChord(RallyKeyText(), rally) && rally.vk == key.vk &&
                   rally.extended == key.extended;
        }

        // True when the message must be dropped.
        bool FilterKeyMessage(UINT msg, WPARAM wParam, LPARAM lParam)
        {
            if (msg != WM_KEYDOWN && msg != WM_KEYUP)
                return false;
            const unsigned vk = static_cast<unsigned>(wParam);
            bool anyMatch = false;
            for (const Policy::Key& key : g_Keys)
                anyMatch = anyMatch || key.vk == vk;
            if (!anyMatch)
                return false;

            Policy::KeyEvent event;
            event.msg = msg;
            event.vk = vk;
            event.lParam = static_cast<unsigned long long>(static_cast<unsigned long>(lParam));
            event.extended = (static_cast<unsigned long>(lParam) & (1UL << 24)) != 0;
            event.shift = GetKeyState(VK_SHIFT) < 0;
            event.ctrl = GetKeyState(VK_CONTROL) < 0;
            event.alt = GetKeyState(VK_MENU) < 0;
            const bool fresh = GetTickCount64() - g_LastTickMs.load(std::memory_order_relaxed) <= kTickFreshMs;

            bool swallow = false;
            for (int i = 0; i < Policy::kKeyCount; ++i)
            {
                const Policy::KeyId id = static_cast<Policy::KeyId>(i);
                if (g_Keys[i].vk != vk)
                    continue;
                bool gate = false;
                // Only a fresh keydown needs the (engine-reading) gate.
                if (msg == WM_KEYDOWN && (static_cast<unsigned long>(lParam) & (1UL << 30)) == 0)
                {
                    gate = fresh && KeyActionActive(id) && !IsRallyKey(g_Keys[i]) && WorldInteractive() &&
                           !EditorActive();
                    if (gate && id == Policy::KeyId::RemoteTarget)
                        gate = SelectionHasOwnUnit();
                }
                const Policy::KeyDecision d = Policy::ClassifyKey(event, id, g_Keys[i], gate, g_Latch[i]);
                swallow = swallow || d.swallow;
                if (!d.act)
                    continue;
                switch (id)
                {
                case Policy::KeyId::RemoteTarget: g_PendingRemoteTarget.store(true); break;
                case Policy::KeyId::BuildingCycle: g_PendingBuilding.store(true); break;
                case Policy::KeyId::AreaSelect: g_PendingArea.store(d.shift ? 2 : 1); break;
                case Policy::KeyId::Hold: g_PendingHold.store(true); break;
                default: break;
                }
            }
            return swallow;
        }

        LRESULT CALLBACK RtsWndProc(HWND h, UINT msg, WPARAM w, LPARAM l)
        {
            if (FilterKeyMessage(msg, w, l))
                return 0;
            return g_PrevWndProc ? CallWindowProcA(g_PrevWndProc, h, msg, w, l) : DefWindowProcA(h, msg, w, l);
        }

        BOOL WINAPI RtsPeekMessageA(LPMSG msg, HWND hwnd, UINT minFilter, UINT maxFilter, UINT remove)
        {
            for (;;)
            {
                const BOOL got =
                    g_RealPeekMessageA ? g_RealPeekMessageA(msg, hwnd, minFilter, maxFilter, remove) : FALSE;
                // Only a removed message can be dropped.
                if (!got || !msg || (remove & PM_REMOVE) == 0 ||
                    !FilterKeyMessage(msg->message, msg->wParam, msg->lParam))
                    return got;
            }
        }

        struct FindCtx
        {
            HWND found = nullptr;
        };

        BOOL CALLBACK FindGameWindowCb(HWND h, LPARAM context)
        {
            char title[256] = {};
            GetWindowTextA(h, title, sizeof(title));
            if (std::strstr(title, "Battlezone 98 Redux"))
            {
                reinterpret_cast<FindCtx*>(context)->found = h;
                return FALSE;
            }
            return TRUE;
        }

        // Both filters, as quicksave.cpp: the keyboard is drained by
        // PeekMessageA(PM_REMOVE) in FUN_00619be0 and also reaches the window
        // procedure; a key hidden from only one of them can still act.
        void EnsureKeyFilters()
        {
            if (!g_PeekAttempted)
            {
                g_PeekAttempted = true;
                const IatPatch::Result result =
                    IatPatch::PatchImportFromAnyDll(GetModuleHandleW(nullptr), "PeekMessageA",
                                                    reinterpret_cast<void*>(&RtsPeekMessageA),
                                                    reinterpret_cast<void**>(&g_RealPeekMessageA));
                if (result != IatPatch::Result::Patched)
                    Log(L"[RTS] PeekMessageA import not patched; a key queued behind another can reach the game\n");
            }
            if (g_Window || g_SubclassAttempted)
                return;
            FindCtx ctx;
            EnumThreadWindows(GetCurrentThreadId(), FindGameWindowCb, reinterpret_cast<LPARAM>(&ctx));
            if (!ctx.found)
                return;
            g_SubclassAttempted = true;
            SetLastError(ERROR_SUCCESS);
            const auto prev = reinterpret_cast<WNDPROC>(
                SetWindowLongPtrA(ctx.found, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&RtsWndProc)));
            if (!prev && GetLastError() != ERROR_SUCCESS)
            {
                Log(L"[RTS] could not subclass the game window (error=%lu)\n", GetLastError());
                return;
            }
            g_PrevWndProc = prev;
            g_Window = ctx.found;
            Log(L"[RTS] key filters on (target %hs, building %hs, area %hs, hold %hs)\n",
                g_KeyText[0].c_str(), g_KeyText[1].c_str(), g_KeyText[2].c_str(), g_KeyText[3].c_str());
        }

        // The QuickSave chords and rally key in force, for the clash checks.
        const char* CheckKey(Policy::KeyId id, const char* text, Policy::Key& out)
        {
            namespace QK = QuickSaveKeyPolicy;
            QK::Chords quick;
            QK::Chord parsed;
            if (QK::ParseChord(QuickSave::ChordText(true), parsed))
                quick.save = parsed;
            if (QK::ParseChord(QuickSave::ChordText(false), parsed))
                quick.load = parsed;
            Policy::Key rally{ 0x56, false };
            if (QK::ParseChord(RallyKeyText(), parsed))
                rally = { parsed.vk, parsed.extended };
            return Policy::CheckKeyText(id, text, g_Keys, rally, quick.save, quick.load, out);
        }

        void ResolveKeysFromConfig()
        {
            for (int i = 0; i < Policy::kKeyCount; ++i)
                g_Keys[i] = {};
            for (int i = 0; i < Policy::kKeyCount; ++i)
            {
                const Policy::KeyId id = static_cast<Policy::KeyId>(i);
                const Policy::KeyDef& def = Policy::GetKeyDef(id);
                std::string text;
                if (!TryGetUserConfigString("Gameplay", def.iniKey, text) || text.empty())
                    text = def.defaultText;
                Policy::Key key;
                if (const char* reason = CheckKey(id, text.c_str(), key))
                {
                    Log(L"[RTS] [Gameplay] %hs=\"%hs\" ignored (%hs); using %hs\n", def.iniKey, text.c_str(), reason,
                        def.defaultText);
                    text = def.defaultText;
                    if (CheckKey(id, text.c_str(), key) != nullptr)
                    {
                        Log(L"[RTS] default %hs for %hs is taken too; that action has no key\n", def.defaultText,
                            def.iniKey);
                        key = {};
                        text.clear();
                    }
                }
                g_Keys[i] = key;
                g_KeyText[i] = text;
                g_Latch[i] = {};
            }
        }

        // ---- install -------------------------------------------------------------

        // Redirects the E8 call at `site` to `target` when it still calls
        // `expectedCallee`. Returns the original callee on success, 0 else.
        uint32_t RedirectCall(uint32_t site, const void* target, uint32_t expectedCallee, const char* name)
        {
            uint8_t original[5] = {};
            if (!ReadBytes(site, original, sizeof(original)) || original[0] != 0xE8)
                return 0;
            int32_t rel = 0;
            std::memcpy(&rel, original + 1, sizeof(rel));
            const uint32_t callee = site + 5 + static_cast<uint32_t>(rel);
            if (callee != expectedCallee)
            {
                Log(L"[RTS] %hs: call at 0x%08X goes to 0x%08X, not 0x%08X; left stock\n", name, site, callee,
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
                Log(L"[RTS] %hs: patch refused\n", name);
                return 0;
            }
            return callee;
        }

        bool InstallShared()
        {
            if (g_SharedReady)
                return true;
            if (reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr)) != 0x00400000)
                return false;
            const HookEngine::EngineRow rows[] = {
                { "ControlPanelGlobal", &g_ControlPanelAddr },
                { "ControlPanelVtable", &g_ControlPanelVtableAddr },
                { "GameObjectHandleGetObj", &g_GetObjAddr },
                // Guard: GameObject::GetModeList is `this + 0x1A4`.
                { "GameObjectGetModeList", &g_GetModeListAddr },
                { "InputEditModeFlag", &g_EditModeFlagAddr },
            };
            if (!HookEngine::BindEngineRows("RTS commands", rows))
                return false;
            g_ObjectListGlobal = HookEngine::ResolveNamedAddress("GameObject::objectList");
            if (g_GameObjectGetHandleAddr == 0 || !ControlPanelIdentityOk())
            {
                LogBudgeted(L"[RTS] GetHandle unresolved or ControlPanel identity failed; not installed\n");
                return false;
            }
            g_FnGetObj = reinterpret_cast<FnGetObj>(g_GetObjAddr);
            g_SharedReady = true;
            return true;
        }

        void InstallParts()
        {
#if defined(_M_IX86)
            if (!g_MergeReady)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ModeListIntersect", &g_IntersectAddr },
                    { "ControlPanelMergeModeListCall", &g_MergeRowAddr },
                };
                if (HookEngine::BindEngineRows("RTS smart menu merge", rows))
                {
                    g_FnIntersect = reinterpret_cast<FnIntersect>(g_IntersectAddr);
                    g_MergeReady = RedirectCall(g_MergeRowAddr + kMergeCallOffset,
                                                reinterpret_cast<const void*>(&MergeHook), g_IntersectAddr,
                                                "ControlPanel::Render/ModeList merge (rts)") != 0;
                }
            }
            if (!g_DispatchReady)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ControlPanelDispatchMode", &g_DispatchAddr },
                    { "ControlPanelDispatchModeCall", &g_DispatchRowAddr },
                };
                if (HookEngine::BindEngineRows("RTS smart menu dispatch", rows))
                {
                    g_FnDispatch = reinterpret_cast<FnDispatchMode>(g_DispatchAddr);
                    g_DispatchReady = RedirectCall(g_DispatchRowAddr + kDispatchCallOffset,
                                                   reinterpret_cast<const void*>(&DispatchHook), g_DispatchAddr,
                                                   "ControlPanel::Render/DispatchMode (rts)") != 0;
                }
            }
            if (!g_BroadcastReady)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ControlPanelBroadcastCommandObj", &g_BroadcastObjAddr },
                    { "ControlPanelDefendTargetBroadcastCall", &g_BroadcastRowAddr },
                    { "GameObjectSetCommandObj", &g_SetCommandObjAddr },
                };
                if (HookEngine::BindEngineRows("RTS smart menu Defend target", rows))
                {
                    g_FnBroadcastObj = reinterpret_cast<FnBroadcastObj>(g_BroadcastObjAddr);
                    g_FnSetCommandObj = reinterpret_cast<FnSetCommandObj>(g_SetCommandObjAddr);
                    g_BroadcastReady = RedirectCall(g_BroadcastRowAddr + kBroadcastCallOffset,
                                                    reinterpret_cast<const void*>(&BroadcastHook), g_BroadcastObjAddr,
                                                    "ControlPanel::Render/Defend target (rts)") != 0;
                }
            }
            if (!g_TargetReady)
            {
                const HookEngine::EngineRow rows[] = {
                    { "GameObjectSetTarget", &g_SetTargetAddr },
                };
                if (HookEngine::BindEngineRows("RTS remote target", rows))
                {
                    g_FnSetTarget = reinterpret_cast<FnSetTarget>(g_SetTargetAddr);
                    g_TargetReady = g_ObjectListGlobal != 0;
                }
            }
            if (!g_AreaReady)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ControlPanelSelectAdd", &g_SelectAddAddr },
                    { "ReticleGlobal", &g_ReticleAddr },
                };
                if (HookEngine::BindEngineRows("RTS area select", rows))
                {
                    g_FnSelectAdd = reinterpret_cast<FnSelectAdd>(g_SelectAddAddr);
                    g_AreaReady = g_ObjectListGlobal != 0;
                }
            }
            if (!g_HoldKeyReady)
            {
                const HookEngine::EngineRow rows[] = {
                    { "GameObjectSetCommand", &g_SetCommandAddr },
                };
                if (HookEngine::BindEngineRows("RTS hold", rows))
                {
                    g_FnSetCommand = reinterpret_cast<FnSetCommand>(g_SetCommandAddr);
                    g_HoldKeyReady = true;
                }
            }
            if (g_HoldKeyReady && (!g_HoldClickReady || !g_LabelReady))
            {
                const HookEngine::EngineRow rows[] = {
                    { "ControlPanelDefendClickSoundCall", &g_DefendClickRowAddr },
                    { "ControlPanelModeLabelLocalizeCall", &g_LabelRowAddr },
                    { "UiLocalize", &g_LocalizeAddr },
                    { "ControlPanelSelectNone", &g_SelectNoneAddr },
                };
                const uint32_t sound = HookEngine::ResolveNamedAddress("PlayGlobalSound");
                if (sound != 0 && HookEngine::BindEngineRows("RTS Shift+Defend hold", rows))
                {
                    g_PlaySoundAddr = sound;
                    g_FnPlaySound = reinterpret_cast<FnPlaySound>(sound);
                    g_FnLocalize = reinterpret_cast<FnLocalize>(g_LocalizeAddr);
                    g_FnSelectNone = reinterpret_cast<FnSelectNone>(g_SelectNoneAddr);
                    g_DefendClickResumeAddr = g_DefendClickRowAddr + kDefendClickResumeOffset;
                    // The label first: a click that holds without its label
                    // would surprise; a label without the click is never set.
                    if (!g_LabelReady)
                        g_LabelReady = RedirectCall(g_LabelRowAddr + kLabelCallOffset,
                                                    reinterpret_cast<const void*>(&ModeLabelThunk), g_LocalizeAddr,
                                                    "ControlPanel::Render/mode label (rts)") != 0;
                    if (g_LabelReady && !g_HoldClickReady)
                        g_HoldClickReady = RedirectCall(g_DefendClickRowAddr + kDefendClickCallOffset,
                                                        reinterpret_cast<const void*>(&DefendClickThunk), sound,
                                                        "ControlPanel::Render/Defend click (rts)") != 0;
                }
            }
#endif
        }

        bool SmartMenuPartsReady()
        {
            return g_SharedReady && g_MergeReady && g_DispatchReady && g_BroadcastReady;
        }

        bool SmartRepairPartsReady()
        {
            return g_SharedReady && g_MergeReady && g_DispatchReady;
        }

        bool HoldHooksReady()
        {
            return g_SharedReady && g_HoldKeyReady;
        }

        void MarkParts()
        {
            struct Mark
            {
                const char* key;
                bool ready;
                const char* reason;
            };
            const Mark marks[] = {
                { "RtsRemoteTarget", g_SharedReady && g_TargetReady,
                  "Unavailable: Remote Target did not hook on this game build (see openshim.log)." },
                { "RtsSmartCommandMenu", SmartMenuPartsReady(),
                  "Unavailable: the mixed-selection menu did not hook on this game build (see openshim.log)." },
                { "RtsSmartRepairReload", SmartRepairPartsReady(),
                  "Unavailable: smart Repair/Reload did not hook on this game build (see openshim.log)." },
                { "RtsAreaSelect", g_SharedReady && g_AreaReady,
                  "Unavailable: Area Select did not hook on this game build (see openshim.log)." },
                { "RtsHold", HoldHooksReady(),
                  "Unavailable: Hold did not hook on this game build (see openshim.log)." },
            };
            for (const Mark& m : marks)
            {
                if (m.ready)
                    ClearOptionHookFailed(m.key);
                else
                    MarkOptionHookFailed(m.key, m.reason);
            }
        }

        bool ReadBoolOption(const char* key, bool fallback)
        {
            bool value = fallback;
            return TryGetUserConfigBool("Gameplay", key, value) ? value : fallback;
        }
    }

    void ReloadRtsCommandsConfig()
    {
        g_TargetEnabled = ReadBoolOption("RtsRemoteTarget", true);
        g_SmartMenuEnabled = ReadBoolOption("RtsSmartCommandMenu", true);
        g_SmartRepairEnabled = ReadBoolOption("RtsSmartRepairReload", true);
        g_AreaEnabled = ReadBoolOption("RtsAreaSelect", true);
        std::string hold;
        g_HoldMode = Policy::kHoldKeyAndShiftMenu;
        if (TryGetUserConfigString("Gameplay", "RtsHold", hold) && !hold.empty())
            g_HoldMode = Policy::ClampHoldMode(std::atoi(hold.c_str()));
        ResolveKeysFromConfig();
        if (!g_ConfigRead)
            Log(L"[RTS] Baseline RtsRemoteTarget=%hs RtsSmartCommandMenu=%hs RtsSmartRepairReload=%hs "
                L"RtsAreaSelect=%hs RtsHold=%d\n",
                g_TargetEnabled ? "yes" : "no", g_SmartMenuEnabled ? "yes" : "no", g_SmartRepairEnabled ? "yes" : "no",
                g_AreaEnabled ? "yes" : "no", g_HoldMode);
        g_ConfigRead = true;
        RefreshRtsCommandsState();
    }

    // Patch thread, from InstallAiTuningHooksIfPossible; retried until every
    // part binds or kMaxInstallAttempts passes have run.
    void InstallRtsCommandsIfPossible()
    {
        static bool s_done = false;
        static int s_attempts = 0;
        if (s_done)
            return;
        if (!g_ConfigRead)
            ReloadRtsCommandsConfig();
        ++s_attempts;
        if (InstallShared())
            InstallParts();
        MarkParts();
        const bool all = SmartMenuPartsReady() && g_TargetReady && g_AreaReady && g_HoldKeyReady && g_HoldClickReady &&
                         g_LabelReady;
        if (all || s_attempts >= kMaxInstallAttempts)
        {
            s_done = true;
            Log(L"[RTS] install %hs after %d attempt(s): merge %hs, dispatch %hs, Defend target %hs, target %hs, "
                L"area %hs, hold %hs, Shift+Defend click %hs, label %hs\n",
                all ? "complete" : "gave up", s_attempts, g_MergeReady ? "yes" : "no", g_DispatchReady ? "yes" : "no",
                g_BroadcastReady ? "yes" : "no", g_TargetReady ? "yes" : "no", g_AreaReady ? "yes" : "no",
                g_HoldKeyReady ? "yes" : "no", g_HoldClickReady ? "yes" : "no", g_LabelReady ? "yes" : "no");
        }
        RefreshRtsCommandsState();
    }

    // The menu, target and area parts run in every session: they only pick
    // which selected units receive a stock order, through the stock calls.
    // Hold uses the single-player native hold, so its parts stand down online.
    void RefreshRtsCommandsState()
    {
        unsigned smart = 0;
        if (g_SmartMenuEnabled && SmartMenuPartsReady())
            smart |= Policy::kSmartCommandMenu;
        if (g_SmartRepairEnabled && SmartRepairPartsReady())
            smart |= Policy::kSmartRepairReload;
        g_SmartMask.store(smart, std::memory_order_release);
        g_TargetActive.store(g_TargetEnabled && g_SharedReady && g_TargetReady, std::memory_order_release);
        g_AreaActive.store(g_AreaEnabled && g_SharedReady && g_AreaReady, std::memory_order_release);
        const bool sp = IsSinglePlayerSession();
        const bool holdKey = Policy::HoldAvailable(g_HoldMode != Policy::kHoldOff, HoldHooksReady(), sp);
        g_HoldKeyActive.store(holdKey, std::memory_order_release);
        g_HoldMenuActive.store(holdKey && g_HoldMode == Policy::kHoldKeyAndShiftMenu && g_HoldClickReady &&
                                   g_LabelReady,
                               std::memory_order_release);
    }

    // Frame/game thread (beside TickOffenseOverflow): installs the key
    // filters once a feature with a key is on, and runs queued key actions.
    void TickRtsCommands()
    {
        const bool anyKey = g_TargetActive.load(std::memory_order_acquire) ||
                            g_AreaActive.load(std::memory_order_acquire) ||
                            g_HoldKeyActive.load(std::memory_order_acquire);
        if (!anyKey)
            return;
        g_LastTickMs.store(GetTickCount64(), std::memory_order_relaxed);
        EnsureKeyFilters();
        if (g_PendingRemoteTarget.exchange(false))
            DoRemoteTarget();
        if (g_PendingBuilding.exchange(false))
            DoBuildingCycle();
        if (const int area = g_PendingArea.exchange(0))
            DoAreaSelect(area == 2);
        if (g_PendingHold.exchange(false))
            DoHoldKey();
    }

    // Mission end/load: drop queued actions.
    void ResetRtsCommands()
    {
        g_PendingRemoteTarget.store(false);
        g_PendingBuilding.store(false);
        g_PendingArea.store(0);
        g_PendingHold.store(false);
        g_LogBudget = 48;
        RefreshRtsCommandsState();
    }

    int RtsCommandKeyCount()
    {
        return Policy::kKeyCount;
    }

    const char* RtsCommandKeyText(int index)
    {
        return index >= 0 && index < Policy::kKeyCount ? g_KeyText[index].c_str() : "";
    }

    const char* SetRtsCommandKeyText(int index, const char* text)
    {
        if (index < 0 || index >= Policy::kKeyCount || !text)
            return "unknown action";
        const Policy::KeyId id = static_cast<Policy::KeyId>(index);
        Policy::Key key;
        if (const char* reason = CheckKey(id, text, key))
            return reason;
        g_Keys[index] = key;
        g_KeyText[index] = text;
        g_Latch[index] = {};
        Log(L"[RTS] %hs rebound to %hs\n", Policy::GetKeyDef(id).iniKey, text);
        return nullptr;
    }
}
