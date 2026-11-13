// producer_rally_points.cpp
// BZR Open Shim - producer rally points. [Gameplay] ProducerRallyPoints,
// default ON, single player only. With a Recycler or Factory selected, V
// toggles rally set mode: while it is armed the stock ground reticle and order
// line preview the point exactly like a Go order, the stock confirm key
// (menu_press, "Reticle Command") sets the rally there, and V again cancels.
// Shift+V clears the rally. V is the default of [Gameplay] RallyKey, which the
// key-binding editor rebinds live (Policy::CheckRallyKeyText). Without the three command hooks below, V sets the
// rally at once to the ground under the reticle (the original behaviour). Each
// unit that producer finishes afterwards (not scavengers or constructors) gets
// a Go order to the rally point. While a rallied producer is selected, a HUD
// marker labelled "Rally" shows the
// point; it is drawn only, never a game object, so nothing is saved and no nav
// slot is used. Addresses, evidence and limits: Docs/PRODUCER_RALLY_POINTS.md.
//
// A 3D beacon (the stock nav beacon mesh on a shim-owned Ogre node) marks
// the same rally; without it the HUD square is drawn instead.
//
// Engine touch points:
//   * Recycler/Factory vtable slot 42 (Producer::FinishBuild, which returns the
//     new GameObject*): after the stock call, a Go order for the new unit.
//   * The game window procedure, subclassed: V/Shift+V become a request.
//   * Entry detours (scripts/patches.json "Producer Rally * Command Hook",
//     installed by the patcher) of the ground-aim GetCommand 0x0045BD80, the
//     object-aim GetCommand 0x0045BBE0 and ControlPanel::BroadcastCommand
//     0x004A70C0: pass-throughs unless set mode is armed and the selection is
//     unchanged; then ground aim yields Go, object aim yields nothing, and the
//     confirmed Go sets the rally instead of issuing an order.
//   * PeekMessageA (main-module IAT): the per-frame main-loop tick. It also
//     runs inside nested modal loops (pause menu, dialogs), so it touches game
//     state only while the world is interactive.
//   * The shared HUD gauge overlay (hud_gauge_overlay.h) draws the marker.
//   * The command panel's post-draw seam (ContextualHud::
//     RegisterCommandPanelPostDraw; contextual_hud.cpp owns the render slot)
//     adds a V "Rally" row ("Cancel" while set mode is armed) on the TAB line.
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "contextual_hud.h"
#include "engine_globals.h"
#include "game_state.h"
#include "hook_engine.h"
#include "hud_gauge_overlay.h"
#include "iat_patch.h"
#include "kill_ticker.h"
#include "native_chunk_mesh.h"
#include "native_chunk_prune.h"
#include "patcher.h"
#include "producer_rally_policy.h"
#include "quicksave.h"
#include "quicksave_key_policy.h"
#include "rally_beacon_assets.h"
#include "shell_casing_physics.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <utility>

namespace BZROpenShim::Hooks
{
    namespace
    {
        namespace Policy = ProducerRallyPolicy;

        using FnFinishBuild = void*(__thiscall*)(void* producer);
        using FnSetCommandWhere = void(__thiscall*)(void* obj, int what, const float* where,
                                                    uint32_t paramLow, uint32_t paramHigh);
        using FnCanCommand = bool(__thiscall*)(void* obj);
        using FnGetObj = void*(__cdecl*)(uint32_t handle);
        using FnGetHandle = uint32_t(__thiscall*)(void* obj);
        using FnCameraRecord = const uint8_t*(__cdecl*)();
        using PFN_PeekMessageA = BOOL(WINAPI*)(LPMSG, HWND, UINT, UINT, UINT);
        // The three set-mode detour targets (thiscall; see scripts/patches.json).
        using FnAimGroundCommand = int(__thiscall*)(void* self, const float* where);
        using FnAimObjectCommand = int(__thiscall*)(void* self, void* target);
        using FnBroadcastCommand = void(__thiscall*)(void* panel, int what, const float* where);

        constexpr size_t kFinishBuildSlot = 42;
        constexpr size_t kCanCommandSlot = 14;
        constexpr int kCmdGo = 3;
        // GameObject::nextCmd.what (GameObject::SetCommand writes it).
        constexpr size_t kNextCmdWhatOffset = 0xCC;
        // ControlPanel selection: handles at +0x1C, count at +0x188.
        constexpr size_t kSelectHandlesOffset = 0x1C;
        constexpr size_t kSelectCountOffset = 0x188;
        constexpr int kSelectMax = static_cast<int>((kSelectCountOffset - kSelectHandlesOffset) / 4);
        // Reticle::groundPos: VECTOR_3D* to its gPos, non-null only on a
        // terrain hit this frame; the pointer Reticle::Simulate hands to the
        // ControlPanel for a ground command (0x005BAA8A).
        constexpr size_t kReticleGroundPosOffset = 0xA8;
        constexpr size_t kTableCapacity = 32;
        constexpr ULONGLONG kLivenessCheckMs = 250;

        // Main camera record (GetCameraRecord row, FUN_00439e60): centre and
        // focal scale at +0x00..+0x0C, world-to-view MAT_3D at +0x40 whose
        // translation doubles sit at matrix +0x28.
        constexpr size_t kCameraMatrixOffset = 0x40;
        constexpr size_t kCameraTranslationOffset = kCameraMatrixOffset + 0x28;
        // ViewRecord +8 is Current_View; the stock reticle draws only in views
        // 0, 1, 2 and 7 (FUN_005bc170 line 54), and so does the marker.
        constexpr size_t kViewRecordCurrentViewOffset = 8;
        // DAT_008eaab0, 0x20 below the ViewRecord row (0x008EAAD0): the stock
        // reticle projects only while it is non-zero (FUN_005bc170 line 60),
        // so the camera record is not trusted while it is zero.
        constexpr size_t kViewRecordCameraValidBackOffset = 0x20;

        // Marker look.
        constexpr uint32_t kMarkerArgb = 0xFF60FF60;
        constexpr uint32_t kMarkerPanelArgb = 0x90000000;
        constexpr int kMarkerHalf = 4;

        uint32_t g_RecyclerVtableAddr = 0;
        uint32_t g_FactoryVtableAddr = 0;
        uint32_t g_FinishBuildAddr = 0;
        uint32_t g_SetCommandAddr = 0;
        uint32_t g_GetObjAddr = 0;
        uint32_t g_ControlPanelAddr = 0;
        uint32_t g_ReticleAddr = 0;
        uint32_t g_EditModeFlagAddr = 0;
        uint32_t g_CameraRecordAddr = 0;
        uint32_t g_ViewRecordAddr = 0;

        FnFinishBuild g_StockFinishBuild = nullptr;
        FnSetCommandWhere g_FnSetCommand = nullptr;
        FnGetObj g_FnGetObj = nullptr;
        PFN_PeekMessageA g_RealPeekMessageA = nullptr;

        bool g_ConfigRead = false;
        bool g_Enabled = true;
        bool g_HooksInstalled = false;
        std::atomic<bool> g_Active{ false };
        // Mission-scoped network opt-in (EXU AllowRallyPoints); cleared by
        // ResetProducerRallyPoints, i.e. on leaving the simulation and on
        // the mission-reset bridge.
        std::atomic<bool> g_MissionAllowsNetwork{ false };
        // DistributedObject::IsRemote 0x004B9830 tests the byte at
        // DistributedObject+0x68 == 2 (row DistributedObjectIsRemote, whose
        // expected bytes include `0F B6 48 68 83 F9 02`); DistributedObject
        // sits at GameObject+0x18, guarded by row GameObjectSimulateRemoteCopy
        // (`83 C1 18`, as in remote_object_smoothing.cpp). Bound on the first
        // opt-in; without both rows the opt-in is refused, and a failed bind is
        // not retried (on Steam each bind attempt can wait up to a second).
        enum class RemoteCheck : int { Untried, Bound, Failed };
        std::atomic<RemoteCheck> g_RemoteCheck{ RemoteCheck::Untried };
        constexpr uint32_t kGoObjectTypeOffset = 0x18 + 0x68;
        // Set by the install (patch thread) once the camera rows bind; the
        // overlay is attached later from the game thread, the only thread
        // HudGaugeOverlay::Ensure() may run on.
        std::atomic<bool> g_MarkerPending{ false };

        // Written by the main-loop tick and FinishBuild, read by the HUD
        // painter; the lock keeps a painter from seeing a half-moved row.
        SRWLOCK g_TableLock = SRWLOCK_INIT;
        Policy::RallyTable<kTableCapacity> g_Table;

        // Set by the window procedure, consumed by the PeekMessageA tick.
        std::atomic<int> g_PendingAction{ 0 };
        Policy::KeyLatch g_KeyLatch;
        // The bound rally key ([Gameplay] RallyKey): vk in the low 16 bits,
        // the extended flag in bit 16. Written by the config reload and the
        // key-binding editor, read by the window procedure and the panel row.
        std::atomic<uint32_t> g_RallyKeyPacked{ Policy::kVkV };
        std::string g_RallyKeyText = Policy::kDefaultRallyKeyText; // key-binding editor thread only

        Policy::RallyKey CurrentRallyKey()
        {
            const uint32_t packed = g_RallyKeyPacked.load(std::memory_order_acquire);
            Policy::RallyKey key;
            key.vk = packed & 0xFFFFu;
            key.extended = (packed & 0x10000u) != 0;
            return key;
        }

        void StoreRallyKey(const Policy::RallyKey& key)
        {
            g_RallyKeyPacked.store(key.vk | (key.extended ? 0x10000u : 0u), std::memory_order_release);
        }
        std::atomic<HWND> g_Window{ nullptr };
        std::atomic<WNDPROC> g_PrevWndProc{ nullptr };
        ULONGLONG g_LastLivenessCheck = 0;
        volatile long g_LogBudget = 48;

        // Rally set mode. The detours, the window procedure and the tick all
        // run on the game thread; g_Armed is atomic only so a stray caller
        // reads a whole value. g_ArmedSelection is written with g_Armed false.
        enum CommandHook
        {
            kHookAimGround = 0,
            kHookAimObject = 1,
            kHookBroadcast = 2,
            kCommandHookCount = 3,
        };
        constexpr unsigned kAllCommandHooks = (1u << kCommandHookCount) - 1u;
        constexpr char const* kCommandHookNames[kCommandHookCount] = {
            "Producer Rally Ground Command Hook",
            "Producer Rally Object Command Hook",
            "Producer Rally Broadcast Command Hook",
        };
        // push ebp; mov ebp,esp; sub esp,imm8 (no relative operands).
        constexpr size_t kPrologueLength = 6;
        constexpr uint8_t kCommandHookPrologues[kCommandHookCount][kPrologueLength] = {
            { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C },
            { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x10 },
            { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C },
        };
        FnAimGroundCommand g_OrigAimGround = nullptr;
        FnAimObjectCommand g_OrigAimObject = nullptr;
        FnBroadcastCommand g_OrigBroadcast = nullptr;
        std::atomic<unsigned> g_CommandHooksInstalled{ 0 };
        bool g_SetModeFallbackLogged = false;
        std::atomic<bool> g_Armed{ false };
        Policy::ArmedSelection<static_cast<size_t>(kSelectMax)> g_ArmedSelection;

        struct TableShared
        {
            TableShared() { AcquireSRWLockShared(&g_TableLock); }
            ~TableShared() { ReleaseSRWLockShared(&g_TableLock); }
        };
        struct TableExclusive
        {
            TableExclusive() { AcquireSRWLockExclusive(&g_TableLock); }
            ~TableExclusive() { ReleaseSRWLockExclusive(&g_TableLock); }
        };

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

        bool ReadVector(uintptr_t address, float out[3])
        {
            if (address < 0x10000)
                return false;
            __try
            {
                const float* v = reinterpret_cast<const float*>(address);
                out[0] = v[0];
                out[1] = v[1];
                out[2] = v[2];
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return std::isfinite(out[0]) && std::isfinite(out[1]) && std::isfinite(out[2]);
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

        // Network games only (single-player objects are all ours). Fails
        // closed: a null or unreadable object, or no bound ownership check,
        // is foreign. See Policy::IsForeignObject for mustBeLocal.
        bool IsForeignObject(void* obj, bool mustBeLocal)
        {
            if (!obj || g_RemoteCheck.load(std::memory_order_acquire) != RemoteCheck::Bound)
                return true;
            uint8_t type = 0;
            bool readable = true;
            __try
            {
                type = *reinterpret_cast<const volatile uint8_t*>(
                    reinterpret_cast<uintptr_t>(obj) + kGoObjectTypeOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                readable = false;
            }
            return Policy::IsForeignObject(readable, type, mustBeLocal);
        }

        bool SafeCanCommand(void* obj)
        {
            void* vtable = ReadPtr(reinterpret_cast<uintptr_t>(obj));
            void* fn = vtable ? ReadPtr(reinterpret_cast<uintptr_t>(vtable) + kCanCommandSlot * sizeof(void*)) : nullptr;
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

        bool SafeSetGoCommand(void* obj, const float pos[3])
        {
            if (!g_FnSetCommand || !obj)
                return false;
            __try
            {
                // param = 1: what ControlPanel::BroadcastCommand passes for a
                // one-unit selection (selection count, sign-extended).
                g_FnSetCommand(obj, kCmdGo, pos, 1u, 0u);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Copies the main camera's projection out of the stock camera record.
        bool ReadCameraProjection(Policy::CameraProjection& cam)
        {
            if (!g_CameraRecordAddr || !g_ViewRecordAddr)
                return false;
            __try
            {
                const int view = *reinterpret_cast<const int*>(g_ViewRecordAddr + kViewRecordCurrentViewOffset);
                if (view != 0 && view != 1 && view != 2 && view != 7)
                    return false;
                if (*reinterpret_cast<const int*>(g_ViewRecordAddr - kViewRecordCameraValidBackOffset) == 0)
                    return false;
                const uint8_t* record = reinterpret_cast<FnCameraRecord>(g_CameraRecordAddr)();
                if (!record)
                    return false;
                const float* head = reinterpret_cast<const float*>(record);
                cam.centerX = head[0];
                cam.centerY = head[1];
                cam.scaleX = head[2];
                cam.scaleY = head[3];
                std::memcpy(cam.rot, record + kCameraMatrixOffset, sizeof(cam.rot));
                std::memcpy(cam.trans, record + kCameraTranslationOffset, sizeof(cam.trans));
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeFill(const HudGaugeOverlay::Frame& frame, int x1, int y1, int x2, int y2, uint32_t argb)
        {
            __try
            {
                frame.fill(frame.pane, x1, y1, x2, y2, argb, 0);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool IsHookedProducer(void* obj)
        {
            const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(reinterpret_cast<uintptr_t>(obj)));
            return vtable != 0 && (vtable == g_RecyclerVtableAddr || vtable == g_FactoryVtableAddr);
        }

        // The same vtable test as IsHookedProducer, kept as a kind: the
        // Recycler and Factory vtables are the only two producers hooked.
        Policy::ProducerKind ProducerKindOf(void* obj)
        {
            const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(reinterpret_cast<uintptr_t>(obj)));
            if (vtable == 0)
                return Policy::ProducerKind::Unknown;
            if (vtable == g_RecyclerVtableAddr)
                return Policy::ProducerKind::Recycler;
            if (vtable == g_FactoryVtableAddr)
                return Policy::ProducerKind::Factory;
            return Policy::ProducerKind::Unknown;
        }

        void* UserObject()
        {
            const uintptr_t slot = EngineGlobals::UserObjectSlot();
            return slot ? ReadPtr(slot) : nullptr;
        }

        bool IsPlayerTeam(void* obj, void* player)
        {
            int team = -1;
            int playerTeam = -2;
            return obj && player &&
                   ReadInt(reinterpret_cast<uintptr_t>(obj) + kGameObjectActualTeamOffset, team) &&
                   ReadInt(reinterpret_cast<uintptr_t>(player) + kGameObjectActualTeamOffset, playerTeam) &&
                   team == playerTeam;
        }

        // ---- the input side ------------------------------------------------

        bool EditorActive()
        {
            int flag = 1;
            // Unreadable reads as "editor on": V then stays the editor's key.
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

        // Calls visit(producer, handle) for each selected Recycler/Factory of
        // the player's team; returns how many there were.
        template <typename Visit>
        int ForEachSelectedProducer(Visit&& visit)
        {
            if (g_ControlPanelAddr == 0)
                return 0;
            int count = 0;
            if (!ReadInt(g_ControlPanelAddr + kSelectCountOffset, count) || count <= 0)
                return 0;
            if (count > kSelectMax)
                count = kSelectMax;
            void* const player = UserObject();
            int found = 0;
            for (int i = 0; i < count; ++i)
            {
                int handle = 0;
                if (!ReadInt(g_ControlPanelAddr + kSelectHandlesOffset + 4 * static_cast<size_t>(i), handle) ||
                    handle == 0)
                    continue;
                void* obj = SafeGetObj(static_cast<uint32_t>(handle));
                if (!obj || !IsHookedProducer(obj) || !IsPlayerTeam(obj, player))
                    continue;
                ++found;
                visit(obj, static_cast<uint32_t>(handle));
            }
            return found;
        }

        bool EligibleProducerSelected()
        {
            return ForEachSelectedProducer([](void*, uint32_t) {}) > 0;
        }

        // ---- rally set mode ------------------------------------------------

        // Copies the live selection's handles; false when unreadable.
        bool ReadSelectionHandles(uint32_t (&out)[kSelectMax], size_t& count)
        {
            count = 0;
            int n = 0;
            if (g_ControlPanelAddr == 0 || !ReadInt(g_ControlPanelAddr + kSelectCountOffset, n) || n < 0 ||
                n > kSelectMax)
                return false;
            for (int i = 0; i < n; ++i)
            {
                int handle = 0;
                if (!ReadInt(g_ControlPanelAddr + kSelectHandlesOffset + 4 * static_cast<size_t>(i), handle))
                    return false;
                out[i] = static_cast<uint32_t>(handle);
            }
            count = static_cast<size_t>(n);
            return true;
        }

        bool SelectionMatchesArmed()
        {
            uint32_t handles[kSelectMax];
            size_t count = 0;
            return ReadSelectionHandles(handles, count) && g_ArmedSelection.Matches(handles, count);
        }

        bool SetModeAvailable()
        {
            return g_CommandHooksInstalled.load(std::memory_order_acquire) == kAllCommandHooks &&
                   g_OrigAimGround && g_OrigAimObject && g_OrigBroadcast;
        }

        // Armed, the feature active and the selection still the armed one.
        bool ArmedAndMatching()
        {
            return g_Armed.load(std::memory_order_acquire) && g_Active.load(std::memory_order_acquire) &&
                   SelectionMatchesArmed();
        }

        void Disarm(const wchar_t* reason)
        {
            if (!g_Armed.exchange(false, std::memory_order_acq_rel))
                return;
            g_ArmedSelection.Reset();
            if (reason)
                LogBudgeted(L"[RALLY] set mode cancelled (%ls)\n", reason);
        }

        // Caller has checked WorldInteractive() and that an eligible producer
        // is selected (the V key gate).
        void Arm()
        {
            uint32_t handles[kSelectMax];
            size_t count = 0;
            g_Armed.store(false, std::memory_order_release);
            if (!ReadSelectionHandles(handles, count) || !g_ArmedSelection.Capture(handles, count))
            {
                g_ArmedSelection.Reset();
                LogBudgeted(L"[RALLY] V: selection unreadable; set mode not armed\n");
                return;
            }
            const int producers = ForEachSelectedProducer([](void*, uint32_t) {});
            if (producers == 0)
            {
                // The selection changed between the V press and this tick.
                g_ArmedSelection.Reset();
                LogBudgeted(L"[RALLY] V: no producer selected; set mode not armed\n");
                return;
            }
            g_Armed.store(true, std::memory_order_release);
            LogBudgeted(L"[RALLY] set mode armed (%d producers)\n", producers);
        }

        int SetRallyForSelection(const float pos[3]);

        // Ground-aim GetCommand (0x0045BD80): thiscall, one stack argument.
        int __fastcall AimGroundCommandDetour(void* self, void* /*edx*/, const float* where)
        {
            if (Policy::OverrideAimCommand(g_Armed.load(std::memory_order_acquire), ArmedAndMatching()))
                return Policy::kCmdGoCommand;
            return g_OrigAimGround(self, where);
        }

        // Object-aim GetCommand (0x0045BBE0): thiscall, one stack argument.
        int __fastcall AimObjectCommandDetour(void* self, void* /*edx*/, void* target)
        {
            if (Policy::OverrideAimCommand(g_Armed.load(std::memory_order_acquire), ArmedAndMatching()))
                return Policy::kCmdNone;
            return g_OrigAimObject(self, target);
        }

        // ControlPanel::BroadcastCommand (0x004A70C0): thiscall, two stack
        // arguments. The armed confirm sets the rally and issues no order.
        void __fastcall BroadcastCommandDetour(void* panel, void* /*edx*/, int what, const float* where)
        {
            const bool armed = g_Armed.load(std::memory_order_acquire);
            if (armed &&
                Policy::BroadcastIsRallyConfirm(armed, ArmedAndMatching(),
                                                reinterpret_cast<uintptr_t>(panel) == g_ControlPanelAddr, what,
                                                where != nullptr))
            {
                float pos[3] = {};
                if (!ReadVector(reinterpret_cast<uintptr_t>(where), pos))
                {
                    LogBudgeted(L"[RALLY] confirm: no readable ground point; set mode stays armed\n");
                    return;
                }
                const int applied = SetRallyForSelection(pos);
                Disarm(nullptr);
                LogBudgeted(L"[RALLY] rally set via reticle at %.1f,%.1f for %d producer(s)\n", pos[0], pos[2],
                            applied);
                return;
            }
            g_OrigBroadcast(panel, what, where);
        }

        LRESULT CALLBACK RallyWndProc(HWND h, UINT msg, WPARAM w, LPARAM l)
        {
            const Policy::RallyKey bound = CurrentRallyKey();
            if ((msg == Policy::kWmKeyDown || msg == Policy::kWmKeyUp) && w == bound.vk &&
                ((static_cast<uint32_t>(l) >> 24) & 1u) == (bound.extended ? 1u : 0u))
            {
                Policy::KeyEvent key;
                key.msg = msg;
                key.vk = static_cast<unsigned>(w);
                key.lParam = static_cast<unsigned long long>(static_cast<uint32_t>(l));
                key.extended = bound.extended;
                key.shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
                key.ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
                key.alt = (GetKeyState(VK_MENU) & 0x8000) != 0;

                Policy::KeyGate gate;
                const bool freshDown = msg == Policy::kWmKeyDown &&
                                       (key.lParam & Policy::kLParamPreviousStateBit) == 0;
                // The game-state reads only matter for a fresh keydown.
                if (freshDown && !key.ctrl && !key.alt)
                {
                    gate.featureActive = g_Active.load(std::memory_order_acquire);
                    if (gate.featureActive)
                    {
                        gate.editorActive = EditorActive();
                        gate.worldInteractive = !gate.editorActive && WorldInteractive();
                        gate.eligibleProducerSelected = gate.worldInteractive && EligibleProducerSelected();
                    }
                }
                const Policy::KeyDecision decision = Policy::ClassifyRallyKey(key, gate, g_KeyLatch, bound);
                if (decision.action != Policy::KeyAction::None)
                    g_PendingAction.store(static_cast<int>(decision.action), std::memory_order_release);
                if (decision.swallow)
                    return 0;
            }
            const WNDPROC prev = g_PrevWndProc.load(std::memory_order_acquire);
            return prev ? CallWindowProcA(prev, h, msg, w, l) : DefWindowProcA(h, msg, w, l);
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

        // Its own subclass, chained to whatever procedure was there before (the
        // stock one, or another OpenShim subclass such as RunInBackground's).
        // Never unhooked, so the chain cannot be broken out of order.
        void EnsureSubclass()
        {
            HWND existing = g_Window.load(std::memory_order_acquire);
            if (existing && IsWindow(existing))
                return;
            FindCtx ctx;
            EnumThreadWindows(GetCurrentThreadId(), FindGameWindowCb, reinterpret_cast<LPARAM>(&ctx));
            if (!ctx.found)
                return;
            SetLastError(ERROR_SUCCESS);
            const auto prev = reinterpret_cast<WNDPROC>(
                SetWindowLongPtrA(ctx.found, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&RallyWndProc)));
            if (!prev && GetLastError() != ERROR_SUCCESS)
            {
                Log(L"[RALLY] failed to subclass game window error=%lu\n", GetLastError());
                return;
            }
            g_PrevWndProc.store(prev, std::memory_order_release);
            g_Window.store(ctx.found, std::memory_order_release);
            g_KeyLatch = {};
            Log(L"[RALLY] game window subclassed hwnd=0x%p previous=0x%p\n", ctx.found, prev);
        }

        // ---- the per-frame main-loop tick ------------------------------------

        int SetRallyForSelection(const float pos[3])
        {
            int applied = 0;
            ForEachSelectedProducer([&](void* producer, uint32_t) {
                if (SetProducerRally(producer, pos))
                    ++applied;
            });
            return applied;
        }

        // Caller has checked WorldInteractive().
        void ApplyToSelection(Policy::KeyAction action)
        {
            if (EditorActive())
                return;
            if (action == Policy::KeyAction::ClearRally)
            {
                Disarm(L"Shift+rally key");
                int applied = 0;
                ForEachSelectedProducer([&](void* producer, uint32_t) {
                    if (ClearProducerRally(producer))
                        ++applied;
                });
                LogBudgeted(L"[RALLY] Shift+rally key: rally cleared for %d producer(s)\n", applied);
                return;
            }

            const bool armed = g_Armed.load(std::memory_order_acquire);
            const Policy::SetKeyPlan plan =
                Policy::PlanSetKey(SetModeAvailable(), armed, armed && SelectionMatchesArmed());
            if (plan == Policy::SetKeyPlan::Cancel)
            {
                Disarm(L"rally key");
                return;
            }
            if (plan == Policy::SetKeyPlan::Arm)
            {
                Arm();
                return;
            }
            if (!g_SetModeFallbackLogged)
            {
                g_SetModeFallbackLogged = true;
                Log(L"[RALLY] set mode unavailable (command hooks installed mask=0x%X of 0x%X); "
                    L"V sets the rally at once\n",
                    g_CommandHooksInstalled.load(std::memory_order_acquire), kAllCommandHooks);
            }
            float pos[3] = {};
            const uintptr_t groundPos = reinterpret_cast<uintptr_t>(
                ReadPtr(g_ReticleAddr + kReticleGroundPosOffset));
            if (!groundPos || !ReadVector(groundPos, pos))
            {
                LogBudgeted(L"[RALLY] V: no ground under the reticle; nothing set\n");
                return;
            }
            const int applied = SetRallyForSelection(pos);
            LogBudgeted(L"[RALLY] V: rally set for %d producer(s) at (%.1f, %.1f, %.1f)\n",
                        applied, pos[0], pos[1], pos[2]);
        }

        // A producer that died (or whose slot was reused) loses its rally.
        // Caller has checked WorldInteractive().
        void DropDeadProducers()
        {
            TableExclusive lock;
            for (size_t i = g_Table.Size(); i-- > 0;)
            {
                const Policy::RallyEntry entry = g_Table.At(i);
                if (reinterpret_cast<uintptr_t>(SafeGetObj(entry.producerHandle)) == entry.producer)
                    continue;
                g_Table.Clear(entry.producer);
                LogBudgeted(L"[RALLY] producer 0x%08X gone; rally removed\n",
                            static_cast<uint32_t>(entry.producer));
            }
        }

        size_t TableSize()
        {
            TableShared lock;
            return g_Table.Size();
        }

        void AttachMarkerOnGameThread();
        void AttachPanelRowOnGameThread();

        void MainLoopTick()
        {
            EnsureSubclass();
            AttachMarkerOnGameThread();
            AttachPanelRowOnGameThread();
            const int pending = g_PendingAction.load(std::memory_order_acquire);
            const size_t tableSize = TableSize();
            const bool active = g_Active.load(std::memory_order_acquire);
            const bool armed = g_Armed.load(std::memory_order_acquire);
            // Nothing queued, stored or armed: skip the shell-state reads.
            if (pending == 0 && tableSize == 0 && !armed)
                return;

            const ULONGLONG now = GetTickCount64();
            const bool interactive = WorldInteractive();
            // Before the queued press, so a V after a selection change arms
            // the new selection instead of cancelling the old one.
            if (armed && EditorActive())
                Disarm(L"editor opened");
            else if (armed && !Policy::KeepArmed(active, interactive, interactive && SelectionMatchesArmed()))
                Disarm(active ? L"selection changed" : L"stood down");
            const Policy::TickPlan plan = Policy::PlanTick(interactive, active, pending != 0,
                                                           tableSize != 0,
                                                           now - g_LastLivenessCheck >= kLivenessCheckMs);
            if (plan.dropPending || plan.applyPending)
                g_PendingAction.store(0, std::memory_order_release);
            if (plan.standDownClear)
            {
                TableExclusive lock;
                g_Table.ClearAll();
                Log(L"[RALLY] stood down; rallies cleared\n");
            }
            if (plan.applyPending)
                ApplyToSelection(static_cast<Policy::KeyAction>(pending));
            if (plan.livenessCheck)
            {
                g_LastLivenessCheck = now;
                DropDeadProducers();
            }
        }

        BOOL WINAPI Hooked_PeekMessageA(LPMSG msg, HWND hwnd, UINT min, UINT max, UINT remove)
        {
            MainLoopTick();
            return g_RealPeekMessageA ? g_RealPeekMessageA(msg, hwnd, min, max, remove) : FALSE;
        }

        // ---- the 3D rally beacon ------------------------------------------
        // A generated "drop-off beacon" (after BZ2's ipdrop): a hex plinth,
        // mast and braces in dark gunmetal under an emissive green octahedron
        // lamp, ringed by four inward chevrons on the ground, ~5.9 m tall.
        // NativeChunks::RallyBeaconMesh writes it to the chunk cache
        // (rally/v1/openshim_rally_beacon.mesh, materials at the cache root)
        // before the payload resource group initialises, so the DLL ships no
        // asset. If that mesh cannot be created the stock nav beacon's mesh
        // (apcamr.odf baseName "apcamr"; BZ_ASSETS/common/models/apcamr.mesh)
        // is used instead, and if that fails too the HUD square stays alone.
        // Either way it is a shim-owned Ogre node:
        // no game object, no collision, nothing saved. Both meshes have their
        // origin at the base (generated: min y = 0; apcamr: AABB min y =
        // 0.0015), so the node sits at the rally
        // point, which is already ground height. Same visibility rule as the
        // HUD marker. Every function here runs on the game thread: the tick
        // from ChunkEffect::Simulate (the shell casings' point), the rest
        // from SetRunning, the Lua mission reset and Ogre's scene teardown.
        // A producer whose rally has no beacon (mesh unavailable, pool full)
        // keeps the HUD square.

        constexpr char kRallyBeaconResource[] = OPENSHIM_CHUNK_CACHE_RALLY_DIR "openshim_rally_beacon.mesh";
        // Factory variant: same geometry, amber lamp material.
        constexpr char kRallyBeaconFactoryResource[] = OPENSHIM_CHUNK_CACHE_RALLY_DIR "openshim_rally_beacon_fac.mesh";
        constexpr char kRallyMeshName[] = "apcamr.mesh"; // stock fallback
        bool g_BeaconFallback = false;                  // generated mesh failed: stock mesh from then on
        bool g_BeaconInUseLogged = false;
        constexpr int kMaxBeaconCreateFailures = 3;
        int g_BeaconCreateFailures = 0;
        constexpr size_t kMeshPoolSize = 8;
        // apcamr.odf [CameraPodClass] omegaSpin = 1.0 (rad/s).
        constexpr double kMeshSpinRadPerSec = 1.0;

        struct RallyMeshSlot
        {
            void* sceneManager = nullptr;
            void* node = nullptr;
            void* entity = nullptr;
            bool visible = false;
            bool amber = false;     // the lamp variant this entity was made with
            bool generated = false; // made from the generated mesh, not the stock fallback
        };

        // HUD label cache: filled by MeshTick (EnsureLabel), read by the HUD
        // painter (LabelFor, no lookup, no allocation); both under g_TableLock.
        // Cleared with the beacon slots.
        struct LabelEntry
        {
            char odf[kGameObjectClassOdfNameMax + 1];
            char text[Policy::kLabelMax];
            size_t length;
        };
        constexpr size_t kLabelCacheSize = 8;
        LabelEntry g_Labels[kLabelCacheSize];
        size_t g_LabelCount = 0; // under g_TableLock

        LabelEntry GenericLabel()
        {
            LabelEntry entry = {};
            entry.length = Policy::FormatRallyLabel(nullptr, entry.text, sizeof(entry.text));
            return entry;
        }

        RallyMeshSlot g_MeshSlots[kMeshPoolSize];
        bool g_MeshUnavailable = false; // creation failed once: HUD square from then on
        bool g_MeshUnavailableLogged = false;
        constexpr int kMaxMeshTransformFailures = 3;
        int g_MeshTransformFailures = 0;
        bool g_AnyMeshVisible = false;
        // Producers whose rally a beacon shows; the painter skips their
        // square. Under g_TableLock.
        uintptr_t g_MeshShown[kMeshPoolSize] = {};
        size_t g_MeshShownCount = 0;

        // Caller holds g_TableLock (shared or exclusive).
        bool MeshShownLocked(uintptr_t producer)
        {
            for (size_t i = 0; i < g_MeshShownCount; ++i)
                if (g_MeshShown[i] == producer)
                    return true;
            return false;
        }

        void SetMeshShown(const uintptr_t* producers, size_t count)
        {
            TableExclusive lock;
            g_MeshShownCount = count < kMeshPoolSize ? count : kMeshPoolSize;
            for (size_t i = 0; i < g_MeshShownCount; ++i)
                g_MeshShown[i] = producers[i];
        }

        bool ReadRenderOrigin(ShellCasings::Vec3& out)
        {
            const uintptr_t originAddr = WorldRenderOriginAddr();
            if (!originAddr)
                return false;
            __try
            {
                const float* origin = reinterpret_cast<const float*>(originAddr);
                out = { origin[0], origin[1], origin[2] };
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return std::isfinite(out.x) && std::isfinite(out.y) && std::isfinite(out.z);
        }

        void HideAllMeshes()
        {
            for (RallyMeshSlot& slot : g_MeshSlots)
            {
                if (slot.visible)
                    HideShimOwnedEntity(slot.entity);
                slot.visible = false;
            }
            g_AnyMeshVisible = false;
            SetMeshShown(nullptr, 0);
        }

        // Drops the pointers without an Ogre call: the scene that made them
        // is gone or is being torn down (Ogre frees the objects).
        void ForgetMeshSlots(const wchar_t* reason)
        {
            size_t held = 0;
            for (RallyMeshSlot& slot : g_MeshSlots)
            {
                if (slot.node || slot.entity)
                    ++held;
                slot = RallyMeshSlot{};
            }
            g_AnyMeshVisible = false;
            SetMeshShown(nullptr, 0);
            {
                TableExclusive lock; // the next mission may carry other ODFs
                g_LabelCount = 0;
            }
            if (held)
                Log(L"[RALLY] forgot %zu rally beacon(s) (%ls)\n", held, reason ? reason : L"unspecified");
        }

        // Destroys the beacons made by sceneManager (DestroyShimOwnedMeshObject
        // does nothing unless it is the live scene), then forgets them all.
        void DestroyMeshSlots(void* sceneManager, const wchar_t* reason)
        {
            for (const RallyMeshSlot& slot : g_MeshSlots)
            {
                if (slot.sceneManager && slot.sceneManager == sceneManager)
                    DestroyShimOwnedMeshObject(slot.sceneManager, slot.node, slot.entity);
            }
            ForgetMeshSlots(reason);
        }

        // Resolves the "<unitName> rally" label of a producer's ODF into the
        // cache, once per ODF per mission (MeshTick, game thread: the engine
        // file read and the allocations happen here, never in the painter). A
        // failed read is cached as the generic label so it is not retried
        // every tick.
        void EnsureLabel(void* producer)
        {
            char odf[kGameObjectClassOdfNameMax + 1] = {};
            if (!TryGetCraftOdfName(producer, odf, sizeof(odf)) || !odf[0])
                return;
            {
                TableShared lock;
                if (g_LabelCount >= kLabelCacheSize)
                    return;
                for (size_t i = 0; i < g_LabelCount; ++i)
                    if (_stricmp(g_Labels[i].odf, odf) == 0)
                        return;
            }
            LabelEntry entry = {};
            std::memcpy(entry.odf, odf, sizeof(entry.odf));
            try
            {
                const std::string unitName = KillTicker::LookupUnitName(odf);
                entry.length = Policy::FormatRallyLabel(unitName.c_str(), entry.text, sizeof(entry.text));
            }
            catch (...)
            {
                entry.length = Policy::FormatRallyLabel(nullptr, entry.text, sizeof(entry.text));
            }
            TableExclusive lock;
            if (g_LabelCount < kLabelCacheSize)
                g_Labels[g_LabelCount++] = entry;
        }

        void MeshTick()
        {
            if (g_MeshUnavailable)
                return;
            uintptr_t producers[kMeshPoolSize] = {};
            bool amber[kMeshPoolSize] = {};
            float positions[kMeshPoolSize][3] = {};
            size_t wanted = 0;
            if (g_Active.load(std::memory_order_acquire) && TableSize() != 0)
            {
                ForEachSelectedProducer([&](void* producer, uint32_t) {
                    if (wanted >= kMeshPoolSize)
                        return; // the rest keep the HUD square
                    TableShared lock;
                    const Policy::RallyEntry* entry = g_Table.Find(reinterpret_cast<uintptr_t>(producer));
                    if (!entry)
                        return;
                    producers[wanted] = reinterpret_cast<uintptr_t>(producer);
                    amber[wanted] = Policy::UseAmberLamp(ProducerKindOf(producer));
                    positions[wanted][0] = entry->pos[0];
                    positions[wanted][1] = entry->pos[1];
                    positions[wanted][2] = entry->pos[2];
                    ++wanted;
                });
            }
            if (wanted == 0)
            {
                if (g_AnyMeshVisible)
                    HideAllMeshes();
                return;
            }

            void* const sceneManager = GetOgreSceneManagerRuntime();
            ShellCasings::Vec3 origin = {};
            if (!sceneManager || !ReadRenderOrigin(origin))
            {
                HideAllMeshes();
                return;
            }
            for (const RallyMeshSlot& slot : g_MeshSlots)
            {
                if (slot.sceneManager && slot.sceneManager != sceneManager)
                {
                    ForgetMeshSlots(L"scene manager changed");
                    break;
                }
            }

            // Frozen while the pause menu is up, like the shell casings
            // (shell_casings.cpp, TickShellCasings): the beacon stays put.
            if (IsPauseMenuOpen())
                return;
            const double angle = std::fmod(static_cast<double>(GetTickCount64()) * 0.001 * kMeshSpinRadPerSec,
                                           6.283185307179586);
            const float quat[4] = { static_cast<float>(std::cos(angle * 0.5)), 0.0f,
                                    static_cast<float>(std::sin(angle * 0.5)), 0.0f };
            // The labels are resolved here, on the game thread; the painter
            // only reads the cache.
            for (size_t i = 0; i < wanted; ++i)
                EnsureLabel(reinterpret_cast<void*>(producers[i]));

            // A slot follows the selection order, so it can be handed a
            // producer of the other colour. Before destroying anything, swap
            // it with another made slot that already has the wanted colour and
            // is not needed in its own colour (the stock fallback mesh has
            // one look and is skipped).
            if (!g_BeaconFallback)
            {
                for (size_t i = 0; i < wanted; ++i)
                {
                    if (!g_MeshSlots[i].entity || g_MeshSlots[i].amber == amber[i])
                        continue;
                    for (size_t j = 0; j < kMeshPoolSize; ++j)
                    {
                        if (j == i || !g_MeshSlots[j].entity || g_MeshSlots[j].amber != amber[i])
                            continue;
                        if (j < wanted && g_MeshSlots[j].amber == amber[j])
                            continue; // already right for its own producer
                        std::swap(g_MeshSlots[i], g_MeshSlots[j]);
                        break;
                    }
                }
            }

            uintptr_t shown[kMeshPoolSize] = {};
            size_t shownCount = 0;
            for (size_t i = 0; i < kMeshPoolSize; ++i)
            {
                RallyMeshSlot& slot = g_MeshSlots[i];
                if (i >= wanted)
                {
                    if (slot.visible)
                        HideShimOwnedEntity(slot.entity);
                    slot.visible = false;
                    continue;
                }
                // A slot holding the wrong mesh is destroyed and re-made: the
                // other lamp colour, or (once the generated mesh has failed)
                // any generated mesh, so the stock one replaces it.
                const char* const resource = amber[i] ? kRallyBeaconFactoryResource : kRallyBeaconResource;
                if (slot.entity && (g_BeaconFallback ? slot.generated : slot.amber != amber[i]))
                {
                    DestroyShimOwnedMeshObject(slot.sceneManager, slot.node, slot.entity);
                    slot = RallyMeshSlot{};
                }
                if (!slot.entity)
                {
                    slot = RallyMeshSlot{};
                    bool created = false;
                    if (!g_BeaconFallback)
                    {
                        created = CreateShimOwnedMeshObject(resource, slot.sceneManager, slot.node, slot.entity);
                        if (created)
                        {
                            g_BeaconCreateFailures = 0;
                            slot.generated = true;
                        }
                        else
                        {
                            // A not-yet-ready scene also lands here: retry on
                            // later ticks, and switch to stock only once the
                            // failure repeats.
                            slot = RallyMeshSlot{};
                            if (++g_BeaconCreateFailures < kMaxBeaconCreateFailures)
                            {
                                // Nothing may claim a beacon that is gone.
                                HideAllMeshes();
                                return;
                            }
                            g_BeaconFallback = true;
                            Log(L"[RALLY] generated beacon mesh %hs could not be created %d times; using stock %hs\n",
                                resource, g_BeaconCreateFailures, kRallyMeshName);
                        }
                    }
                    if (!created)
                        created = CreateShimOwnedStockMeshObject(kRallyMeshName, slot.sceneManager, slot.node, slot.entity);
                    if (created)
                        slot.amber = amber[i];
                    if (created && !g_BeaconInUseLogged)
                    {
                        g_BeaconInUseLogged = true;
                        Log(L"[RALLY] rally beacon mesh in use: %hs\n",
                            g_BeaconFallback ? kRallyMeshName : resource);
                    }
                    if (!created)
                    {
                        slot = RallyMeshSlot{};
                        g_MeshUnavailable = true;
                        if (!g_MeshUnavailableLogged)
                        {
                            g_MeshUnavailableLogged = true;
                            Log(L"[RALLY] rally beacon mesh %hs could not be created; HUD marker only\n",
                                kRallyMeshName);
                        }
                        HideAllMeshes();
                        return;
                    }
                }
                const ShellCasings::Vec3 render = ShellCasings::SimToRenderPoint(
                    { positions[i][0], positions[i][1], positions[i][2] }, origin);
                const float at[3] = { render.x, render.y, render.z };
                if (!SetShimOwnedObjectTransform(slot.node, slot.entity, at, quat, nullptr))
                {
                    // Destroy rather than forget, so a stale beacon is not left
                    // on screen and a failure that repeats every tick does not
                    // build a new pair each time. A few failures end the mesh.
                    DestroyShimOwnedMeshObject(slot.sceneManager, slot.node, slot.entity);
                    slot = RallyMeshSlot{};
                    if (++g_MeshTransformFailures >= kMaxMeshTransformFailures)
                    {
                        g_MeshUnavailable = true;
                        Log(L"[RALLY] rally beacon transform failed %d times; HUD marker only\n",
                            g_MeshTransformFailures);
                        HideAllMeshes();
                        return;
                    }
                    continue;
                }
                slot.visible = true;
                shown[shownCount++] = producers[i];
            }
            g_AnyMeshVisible = shownCount != 0;
            SetMeshShown(shown, shownCount);
        }

        // ---- the HUD marker ------------------------------------------------

        // Copy of the cached label for this producer's ODF; "Rally" on a miss.
        // No lookup and no allocation: the painter must not block or throw.
        // EnsureLabel (MeshTick) fills the cache.
        LabelEntry LabelFor(void* producer)
        {
            char odf[kGameObjectClassOdfNameMax + 1] = {};
            if (TryGetCraftOdfName(producer, odf, sizeof(odf)) && odf[0])
            {
                TableShared lock;
                for (size_t i = 0; i < g_LabelCount; ++i)
                    if (_stricmp(g_Labels[i].odf, odf) == 0)
                        return g_Labels[i];
            }
            return GenericLabel();
        }

        // Backing-panel half width: the measured text when the frame offers a
        // sane measure, else the per-glyph estimate.
        int LabelPanelHalfWidth(const HudGaugeOverlay::Frame& frame, const LabelEntry& label) noexcept
        {
            float w = 0.0f, h = 0.0f;
            if (frame.measure && frame.style)
            {
                __try
                {
                    frame.measure(frame.style, label.text, &w, &h);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    w = 0.0f;
                }
            }
            if (std::isfinite(w) && w > 0.0f && w < 400.0f)
                return static_cast<int>(w * 0.5f) + 6;
            return Policy::LabelHalfWidth(label.length);
        }

        // Shown only while a rallied producer is selected (BZCC behaviour).
        // With a 3D beacon on the rally the square is left out; the "Rally"
        // label stays, so the beacon reads as this producer's rally rather
        // than a stock nav.
        // Reads only: the camera record, the selection and the table.
        bool PaintRally(const HudGaugeOverlay::Frame& frame) noexcept
        {
            if (!g_Active.load(std::memory_order_acquire) || TableSize() == 0)
                return true;
            Policy::CameraProjection cam;
            if (!ReadCameraProjection(cam))
                return true;

            bool ok = true;
            ForEachSelectedProducer([&](void* producer, uint32_t) {
                if (!ok)
                    return;
                float rally[3] = {};
                bool beacon = false;
                {
                    TableShared lock;
                    const Policy::RallyEntry* entry = g_Table.Find(reinterpret_cast<uintptr_t>(producer));
                    if (!entry)
                        return;
                    rally[0] = entry->pos[0];
                    rally[1] = entry->pos[1];
                    rally[2] = entry->pos[2];
                    beacon = MeshShownLocked(reinterpret_cast<uintptr_t>(producer));
                }
                float rx = 0.0f, ry = 0.0f;
                if (!Policy::ProjectToScreen(cam, rally, rx, ry))
                    return; // behind the camera

                if (!Policy::OnScreen(rx, ry, frame.viewW, frame.viewH))
                    return;
                const int x = static_cast<int>(rx);
                const int y = static_cast<int>(ry);
                if (!beacon)
                    ok = SafeFill(frame, x - kMarkerHalf, y - kMarkerHalf, x + kMarkerHalf, y + kMarkerHalf,
                                  kMarkerArgb);
                if (!ok)
                    return;
                const int textY = y + kMarkerHalf + 2;
                const LabelEntry label = LabelFor(producer);
                const int half = LabelPanelHalfWidth(frame, label);
                ok = HudGaugeOverlay::DrawPanelText(frame, x - half, textY - 1, x + half, textY + 13,
                                                    kMarkerPanelArgb, x, textY, label.text, kMarkerArgb, 1);
            });
            return ok;
        }

        // ---- the SPACE row label -------------------------------------------
        // ControlPanel::Render localizes the SPACE row label with
        // Localize("names", table[cmd * 2]) (FUN_004a08e0.c line 604). That
        // one call site is redirected (CommandMenuSpaceLabelLocalizeCall), so
        // while set mode is armed for the current selection (the state in
        // which the confirm sets the rally, ArmedAndMatching) "Go To" reads
        // "Rally"; every other key, and every other moment, goes to the
        // original. No bind: stock "Go To".

        using FnLocalize = const char*(__cdecl*)(const char* section, const char* key);
        FnLocalize g_OrigSpaceLocalize = nullptr;

        const char* __cdecl SpaceRowLocalize(const char* section, const char* key)
        {
            if (Policy::SpaceRowLabelOverride(ArmedAndMatching(), key))
                return Policy::kSpaceRowArmedLabel;
            return g_OrigSpaceLocalize(section, key);
        }

        // Patch thread, beside InstallPanelRow. Optional: the label stays stock
        // when the row does not bind or the patch is refused.
        void InstallSpaceLabel()
        {
            const uint32_t site = HookEngine::EngineAddress("CommandMenuSpaceLabelLocalizeCall");
            if (site == 0)
            {
                Log(L"[RALLY] SPACE label call site does not bind; the SPACE row keeps Go To\n");
                return;
            }
            uint8_t original[5] = {};
            std::memcpy(original, reinterpret_cast<const void*>(static_cast<uintptr_t>(site)), sizeof(original));
            int32_t origRel = 0;
            std::memcpy(&origRel, original + 1, sizeof(origRel));
            g_OrigSpaceLocalize =
                reinterpret_cast<FnLocalize>(static_cast<uintptr_t>(site + 5 + static_cast<uint32_t>(origRel)));

            HookEngine::PatchDef patch;
            patch.address = site;
            patch.type = HookEngine::PatchType::REL32;
            patch.name = "ControlPanel::Render/SPACE label (rally)";
            patch.verified = true;
            patch.expected_original.assign(original, original + sizeof(original));
            const int32_t rel = static_cast<int32_t>(reinterpret_cast<uintptr_t>(&SpaceRowLocalize)) -
                                static_cast<int32_t>(site + 5);
            patch.payload.assign(5, 0);
            patch.payload[0] = 0xE8;
            std::memcpy(patch.payload.data() + 1, &rel, sizeof(rel));
            if (HookEngine::ApplyPatch(patch))
                Log(L"[RALLY] SPACE row reads Rally while set mode is armed\n");
            else
                Log(L"[RALLY] SPACE label patch refused; the SPACE row keeps Go To\n");
        }

        // ---- the command-panel row -----------------------------------------
        // A V key and "Rally" ("Cancel" while set mode is armed for the
        // selection) while a Recycler/Factory is selected, on the
        // TAB row's line right-aligned to the scrap-cost column, or under the
        // menu underlay when the TAB label is too long to leave room
        // (Policy::ChoosePanelRowLayout). Drawn with the stock row calls of
        // ControlPanel::Render (FUN_004a08e0.c lines 698-711). Display only:
        // the engine hit-tests rows 0-12 alone. Evidence:
        // Docs/PRODUCER_RALLY_POINTS.md.

        using FnFontDraw = void(__cdecl*)(void* font, void* pane, int x, int y, const char* text);
        using FnTextHeight = float(__cdecl*)(void* font);
        using FnTextMeasure = void(__cdecl*)(void* font, const char* text, float* width, float* height);
        using FnSpriteDraw = void(__cdecl*)(void* pane, int sprite, int x, int y, uint32_t flags, float scale);
        using FnFillRect = void(__cdecl*)(void* pane, int x1, int y1, int x2, int y2, uint32_t colour, uint32_t mode);
        using FnUiScale = uint64_t(__cdecl*)(); // EAX = x, EDX = y (float bits)

        // ControlPanel +0x11A0: the branch Render took this frame.
        constexpr size_t kPanelStateOffset = 0x11A0;
        // CommandMenuRowAnchors rows: 11 ALT, 12 TAB ({x, y} ints).
        constexpr size_t kAltAnchorOffset = 11 * 8;
        constexpr size_t kTabAnchorOffset = 12 * 8;
        // CommandMenuRowRects row 12 .right ({left, top, right, bottom}).
        constexpr size_t kTabRectRightOffset = 12 * 16 + 8;
        // CommandUI bounds {left, top, right, bottom} (FUN_0049f9e0.c line 101).
        constexpr size_t kBoundsTopOffset = 4;
        // HudSpriteMaterialTable record stride (FUN_0068c560.c line 50).
        constexpr size_t kSpriteRecordStride = 0x24;
        // The stock key sprite flags (right-align x, centre y, colour mode 1).
        constexpr uint32_t kKeySpriteFlags = 0x60001;
        // The drawn cap: the stock key sheet's caps are opaque white with a
        // black glyph (BZ_ASSETS sprite_n). Colours are ARGB, as
        // HudColorWhite/HudColorBlue hold them.
        constexpr uint32_t kKeyCapArgb = 0xFFFFFFFFu;
        constexpr uint32_t kKeyGlyphArgb = 0xFF000000u;
        // HudSpriteZ step that puts a fill behind the text drawn on it, as
        // the stock text call does around its own background fill.
        constexpr float kKeyCapZStep = 0.01f;
        // The stock TAB label key (PTR_s_Cancel_008e7bec, FUN_004a08e0.c line
        // 707) and a two-digit cost ("%02ld", line 1430).
        constexpr char kTabLabelKey[] = "Cancel";
        // Two digits: no stock ODF costs over 99, and a wider cost would run
        // into the stock "P" at right - scaleX * 6 (lines 1464-1480) anyway.
        constexpr char kCostSample[] = "00";
        // The ALT row's label while no command is aimed (the Clear row's fit
        // test measures this; the live ALT label can differ, UNVERIFIED).
        constexpr char kAltLabelKey[] = "No Action";
        // A mod's key_V sprite wins; otherwise the cap is drawn at key_0's
        // size (the stock single-character cap).
        constexpr char kKeyVSpriteName[] = "key_V";
        constexpr char kKeyCapSizeSprite[] = "key_0";

        uint32_t g_PanelPaneAddr = 0;      // HudPaneBuffer
        uint32_t g_PanelFontAddr = 0;      // UiFontContext
        uint32_t g_PanelColourAddr = 0;    // HudColorWhite
        uint32_t g_PanelAltLayoutAddr = 0; // CommandMenuAltLayoutFlag
        uint32_t g_PanelBranchInputAddr = 0; // CommandMenuUnitBranchInput
        uint32_t g_PanelAnchorsAddr = 0;   // CommandMenuRowAnchors
        uint32_t g_PanelKeyInsetAddr = 0;  // CommandMenuKeyInset
        uint32_t g_PanelFontDrawAddr = 0;  // HudFadeFont
        uint32_t g_PanelTextHeightAddr = 0;
        uint32_t g_PanelTextMeasureAddr = 0;
        uint32_t g_PanelSpriteAddr = 0;    // HudFeedbackSprite
        uint32_t g_PanelFillAddr = 0;      // HudFillRect
        uint32_t g_PanelScaleAddr = 0;     // HudFeedbackScale
        uint32_t g_PanelRowRectsAddr = 0;  // CommandMenuRowRects
        uint32_t g_PanelBoundsAddr = 0;    // CommandUiBoundsLeft
        uint32_t g_PanelUnderlayIdAddr = 0; // CommandUiUnderlaySpriteId
        uint32_t g_PanelViewportWAddr = 0; // HudViewportWidth
        uint32_t g_PanelViewportHAddr = 0; // HudViewportHeight
        uint32_t g_SpriteMaterialsAddr = 0; // HudSpriteMaterialTable
        uint32_t g_SpriteZAddr = 0;        // HudSpriteZ
        uint32_t g_UiLocalizeAddr = 0;     // UiLocalize, optional (TAB width)
        // Set once the rows bind (patch thread); the seam is registered from
        // the game thread the first time the feature is active, so with
        // rally off the stock render slot is never touched.
        std::atomic<bool> g_PanelRowPending{ false };

        // Game thread only (the post-draw callback). A miss is retried at
        // most once a second, so an early first draw does not hide the row
        // for the rest of the process.
        constexpr ULONGLONG kKeySpriteRetryMs = 1000;
        bool g_KeySpritesResolved = false;
        ULONGLONG g_KeySpriteLastTry = 0;
        bool g_KeySpriteMissLogged = false;
        int g_KeyVSprite = 0;   // a usable key_V sprite, else 0
        int g_KeyVW = 0;        // its atlas size
        int g_KeyVH = 0;
        int g_KeyZeroW = 0;     // key_0's atlas size, the single-character cap
        int g_KeyZeroH = 0;
        bool g_PanelRowFaultLogged = false;
        Policy::PanelRowPlacement g_LastPlacement = Policy::PanelRowPlacement::Hidden;
        Policy::ClearRowPlacement g_LastClearPlacement = Policy::ClearRowPlacement::Hidden;

        struct PanelRowInputs
        {
            int panelState = 0;
            int selectionCount = 0;
            bool altLayout = true;
            bool branchInputHeld = true;
            int tabX = 0;
            int tabY = 0;
            int altY = 0;
            int inset = 0;
            int rowRight = 0;
            int boundsTop = 0;
            int underlaySprite = 0;
            int viewportW = 0;
            int viewportH = 0;
            void* pane = nullptr;
            void* font = nullptr;
            uint32_t colour = 0;
        };

        bool ReadPanelRowInputs(uintptr_t panel, PanelRowInputs& in)
        {
            __try
            {
                in.panelState = *reinterpret_cast<const int*>(panel + kPanelStateOffset);
                in.selectionCount = *reinterpret_cast<const int*>(panel + kSelectCountOffset);
                in.altLayout = *reinterpret_cast<const uint8_t*>(g_PanelAltLayoutAddr) != 0;
                in.branchInputHeld = *reinterpret_cast<const uint8_t*>(g_PanelBranchInputAddr) != 0;
                in.tabX = *reinterpret_cast<const int*>(g_PanelAnchorsAddr + kTabAnchorOffset);
                in.tabY = *reinterpret_cast<const int*>(g_PanelAnchorsAddr + kTabAnchorOffset + 4);
                in.altY = *reinterpret_cast<const int*>(g_PanelAnchorsAddr + kAltAnchorOffset + 4);
                in.inset = *reinterpret_cast<const int*>(g_PanelKeyInsetAddr);
                in.rowRight = *reinterpret_cast<const int*>(g_PanelRowRectsAddr + kTabRectRightOffset);
                in.boundsTop = *reinterpret_cast<const int*>(g_PanelBoundsAddr + kBoundsTopOffset);
                in.underlaySprite = *reinterpret_cast<const int*>(g_PanelUnderlayIdAddr);
                in.viewportW = *reinterpret_cast<const int*>(g_PanelViewportWAddr);
                in.viewportH = *reinterpret_cast<const int*>(g_PanelViewportHAddr);
                in.pane = *reinterpret_cast<void* const*>(g_PanelPaneAddr);
                in.font = *reinterpret_cast<void* const*>(g_PanelFontAddr);
                in.colour = *reinterpret_cast<const uint32_t*>(g_PanelColourAddr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return in.pane && in.font;
        }

        int SafeSpriteLookup(const char* name)
        {
            if (!g_BzrFn_HudSpriteLookup)
                return 0;
            __try
            {
                return g_BzrFn_HudSpriteLookup(name);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        // A sprite row whose material did not resolve keeps a null MaterialPtr
        // (HudSpriteMaterialTable); what the draw does with one is unverified,
        // so such a row is never drawn.
        bool SpriteMaterialResolved(int id)
        {
            if (id <= 0 || g_SpriteMaterialsAddr == 0)
                return false;
            __try
            {
                return *reinterpret_cast<const uint32_t*>(g_SpriteMaterialsAddr +
                                                          static_cast<uint32_t>(id) * kSpriteRecordStride) != 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // A mod's key_V sprite is used when the bound key is V and its row and
        // material resolved; every other key (and V without that sprite) is
        // drawn as a cap at key_0's size. Both are looked up together and
        // cached once either is found; a miss retries at most once a second.
        void ResolveKeySprites()
        {
            if (g_KeySpritesResolved)
                return;
            const ULONGLONG now = GetTickCount64();
            if (g_KeySpriteLastTry != 0 && now - g_KeySpriteLastTry < kKeySpriteRetryMs)
                return;
            g_KeySpriteLastTry = now;
            const int id = SafeSpriteLookup(kKeyVSpriteName);
            HudSpriteRectRecord rec = {};
            g_KeyVSprite = 0;
            if (id > 0 && SpriteMaterialResolved(id) && TryGetHudSpriteCurrentRecord(id, rec) && rec.w > 0 &&
                rec.h > 0)
            {
                g_KeyVSprite = id;
                g_KeyVW = rec.w;
                g_KeyVH = rec.h;
                Log(L"[RALLY] key_V sprite found (id %d, %dx%d); used while the rally key is V\n", id, g_KeyVW,
                    g_KeyVH);
            }
            else if (id > 0 && !g_KeySpriteMissLogged)
            {
                Log(L"[RALLY] key_V sprite (id %d) has no material or size; not drawn\n", id);
            }
            HudSpriteRectRecord cap = {};
            const int capId = SafeSpriteLookup(kKeyCapSizeSprite);
            if (capId > 0 && TryGetHudSpriteCurrentRecord(capId, cap) && cap.w > 0 && cap.h > 0)
            {
                g_KeyZeroW = cap.w;
                g_KeyZeroH = cap.h;
                Log(L"[RALLY] command panel row can draw its own key cap (key_0 size %dx%d)\n", g_KeyZeroW,
                    g_KeyZeroH);
            }
            if (g_KeyVSprite > 0 || g_KeyZeroW > 0)
            {
                g_KeySpritesResolved = true;
                return;
            }
            if (!g_KeySpriteMissLogged)
            {
                g_KeySpriteMissLogged = true;
                Log(L"[RALLY] no key_V sprite and key_0 size unreadable (id %d); panel row hidden, retrying\n",
                    capId);
            }
        }

        // What the row draws for the bound key: the mod's key_V sprite only
        // when the key is V, else a drawn cap carrying the key's name (at
        // key_0's size, or key_V's when key_0 is unreadable).
        struct KeyCapSpec
        {
            bool valid = false;
            bool sprite = false;
            int atlasW = 0;
            int atlasH = 0;
            char name[12] = {};
            size_t nameLen = 0;
        };

        KeyCapSpec ChooseKeyCap(const Policy::RallyKey& key)
        {
            KeyCapSpec spec;
            if (key == Policy::RallyKey{} && g_KeyVSprite > 0)
            {
                spec.valid = true;
                spec.sprite = true;
                spec.atlasW = g_KeyVW;
                spec.atlasH = g_KeyVH;
                return spec;
            }
            spec.nameLen = Policy::RallyKeyCapName(key, spec.name, sizeof(spec.name));
            if (spec.nameLen == 0)
                return spec;
            spec.atlasW = g_KeyZeroW > 0 ? g_KeyZeroW : g_KeyVW;
            spec.atlasH = g_KeyZeroW > 0 ? g_KeyZeroH : g_KeyVH;
            spec.valid = spec.atlasW > 0 && spec.atlasH > 0;
            return spec;
        }

        bool ReadUiScale(float& sx, float& sy)
        {
            __try
            {
                const uint64_t scale = reinterpret_cast<FnUiScale>(g_PanelScaleAddr)();
                const uint32_t sxBits = static_cast<uint32_t>(scale);
                const uint32_t syBits = static_cast<uint32_t>(scale >> 32);
                std::memcpy(&sx, &sxBits, sizeof(sx));
                std::memcpy(&sy, &syBits, sizeof(sy));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return std::isfinite(sx) && std::isfinite(sy) && sx > 0.0f && sy > 0.0f;
        }

        // The text widths the layout needs, with the stock font calls. The row
        // label is the wider of its two forms (Policy::PanelRowLabel), so the
        // placement does not change when set mode arms. The TAB label is
        // measured as the engine localizes it (UiLocalize); without that row
        // the width is unknown and the layout takes the safe place under the
        // underlay.
        bool MeasurePanelRowSeh(const PanelRowInputs& in, const KeyCapSpec& cap, float& capTextW,
                                Policy::PanelRowLayoutInput& layout)
        {
            const auto measure = reinterpret_cast<FnTextMeasure>(g_PanelTextMeasureAddr);
            __try
            {
                float w = 0.0f, h = 0.0f;
                capTextW = 0.0f;
                if (!cap.sprite && cap.nameLen > 1)
                {
                    measure(in.font, cap.name, &capTextW, &h);
                    h = 0.0f;
                }
                measure(in.font, Policy::PanelRowLabel(false), &w, &h);
                float armedW = 0.0f;
                h = 0.0f;
                measure(in.font, Policy::PanelRowLabel(true), &armedW, &h);
                layout.labelW = armedW > w ? armedW : w;
                layout.labelH = reinterpret_cast<FnTextHeight>(g_PanelTextHeightAddr)(in.font);
                w = h = 0.0f;
                measure(in.font, kCostSample, &w, &h);
                layout.costW = w;
                layout.cancelKnown = false;
                if (g_UiLocalizeAddr)
                {
                    const char* tab = reinterpret_cast<FnLocalize>(g_UiLocalizeAddr)("names", kTabLabelKey);
                    if (tab)
                    {
                        w = h = 0.0f;
                        measure(in.font, tab, &w, &h);
                        layout.cancelW = w;
                        layout.cancelKnown = true;
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return true;
        }

        // The key goes where the stock rows put theirs: right-aligned at
        // anchor x - CommandMenuKeyInset, centred on the row y (the stock
        // call passes flags 0x60001, FUN_004a08e0.c lines 698-701), and the
        // label at anchor x, y - height / 2 (lines 707-712).
        // One key cap right-aligned at anchorX - inset, centred on y. Must be
        // called inside the caller's __try, which restores spriteZ and the
        // font colour from savedZ / zRaised and its own saved colour.
        void DrawKeyCapUnsafe(const PanelRowInputs& in, const KeyCapSpec& capSpec, int capWidthPx, int anchorX, int y,
                              float sx, float sy, float& savedZ, bool& zRaised)
        {
            const auto fontDraw = reinterpret_cast<FnFontDraw>(g_PanelFontDrawAddr);
            const auto textHeight = reinterpret_cast<FnTextHeight>(g_PanelTextHeightAddr);
            float* const spriteZ = reinterpret_cast<float*>(g_SpriteZAddr);
            uint32_t* const fontColour = reinterpret_cast<uint32_t*>(in.font);
            if (capSpec.sprite)
            {
                reinterpret_cast<FnSpriteDraw>(g_PanelSpriteAddr)(in.pane, g_KeyVSprite, anchorX - in.inset, y,
                                                                  kKeySpriteFlags, 0.0f);
                return;
            }
            Policy::PixelRect box;
            Policy::FillRect cap[2];
            const int bands = Policy::KeyBoxRect(anchorX, y, in.inset, capSpec.atlasW, capSpec.atlasH, sx, sy, box,
                                                 capWidthPx)
                                  ? Policy::KeyCapFillRects(box, sx, cap)
                                  : 0;
            if (bands <= 0)
                return;
            // The cap one depth step behind the glyph drawn on it.
            const auto fill = reinterpret_cast<FnFillRect>(g_PanelFillAddr);
            savedZ = *spriteZ;
            *spriteZ = savedZ + kKeyCapZStep;
            zRaised = true;
            for (int i = 0; i < bands; ++i)
                fill(in.pane, cap[i].x1, cap[i].y1, cap[i].x2, cap[i].y2, kKeyCapArgb, 0);
            *spriteZ = savedZ;
            zRaised = false;
            float w = 0.0f, h = 0.0f;
            reinterpret_cast<FnTextMeasure>(g_PanelTextMeasureAddr)(in.font, capSpec.name, &w, &h);
            *fontColour = kKeyGlyphArgb;
            const int cx = (box.left + box.right) / 2 - static_cast<int>(w / 2.0f);
            const int cy = (box.top + box.bottom) / 2;
            fontDraw(in.font, in.pane, cx, Policy::CenteredTextY(cy, textHeight(in.font)), capSpec.name);
        }

        // shiftCap != null (the Clear row) draws a second cap one inset left
        // of the key cap, whose pixel width is keyWidthPx.
        bool DrawPanelRowSeh(const PanelRowInputs& in, const KeyCapSpec& capSpec, int capWidthPx, int x, int y, float sx,
                             float sy, const char* label, const KeyCapSpec* shiftCap = nullptr, int shiftWidthPx = 0,
                             int keyWidthPx = 0)
        {
            const auto fontDraw = reinterpret_cast<FnFontDraw>(g_PanelFontDrawAddr);
            const auto textHeight = reinterpret_cast<FnTextHeight>(g_PanelTextHeightAddr);
            float* const spriteZ = reinterpret_cast<float*>(g_SpriteZAddr);
            uint32_t* const fontColour = reinterpret_cast<uint32_t*>(in.font);
            float savedZ = 0.0f;
            bool zRaised = false;
            uint32_t savedColour = 0;
            bool colourSaved = false;
            __try
            {
                // FUN_00689950: the font's first dword is its colour. Saved
                // here and restored on both paths.
                savedColour = *fontColour;
                colourSaved = true;
                DrawKeyCapUnsafe(in, capSpec, capWidthPx, x, y, sx, sy, savedZ, zRaised);
                if (shiftCap)
                    DrawKeyCapUnsafe(in, *shiftCap, shiftWidthPx, x - in.inset - keyWidthPx, y, sx, sy, savedZ,
                                     zRaised);
                *fontColour = in.colour;
                fontDraw(in.font, in.pane, x, Policy::CenteredTextY(y, textHeight(in.font)), label);
                *fontColour = savedColour;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                __try
                {
                    if (zRaised)
                        *spriteZ = savedZ;
                    if (colourSaved)
                        *fontColour = savedColour;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
                return false;
            }
        }

        // Widths for the Clear row: its Shift cap text, "Clear", and the
        // ALT label (altKnown false without UiLocalize).
        bool MeasureClearRowSeh(const PanelRowInputs& in, float& shiftTextW, float& clearW, bool& altKnown,
                                float& altW)
        {
            const auto measure = reinterpret_cast<FnTextMeasure>(g_PanelTextMeasureAddr);
            __try
            {
                float h = 0.0f;
                shiftTextW = clearW = altW = 0.0f;
                altKnown = false;
                measure(in.font, Policy::kClearRowShiftCap, &shiftTextW, &h);
                h = 0.0f;
                measure(in.font, Policy::kClearRowLabel, &clearW, &h);
                if (g_UiLocalizeAddr)
                {
                    const char* alt = reinterpret_cast<FnLocalize>(g_UiLocalizeAddr)("names", kAltLabelKey);
                    if (alt)
                    {
                        h = 0.0f;
                        measure(in.font, alt, &altW, &h);
                        altKnown = true;
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return true;
        }

        // True when any selected eligible producer has a rally stored.
        bool SelectedProducerHasRally()
        {
            if (TableSize() == 0)
                return false;
            bool any = false;
            ForEachSelectedProducer([&](void* producer, uint32_t) {
                if (any)
                    return;
                TableShared lock;
                any = g_Table.Find(reinterpret_cast<uintptr_t>(producer)) != nullptr;
            });
            return any;
        }

        const wchar_t* ClearPlacementName(Policy::ClearRowPlacement p)
        {
            switch (p)
            {
            case Policy::ClearRowPlacement::AltLine:
                return L"on the ALT line";
            case Policy::ClearRowPlacement::BelowRally:
                return L"one row under the Rally row";
            default:
                return L"hidden (layout unreadable or off screen)";
            }
        }

        const wchar_t* PlacementName(Policy::PanelRowPlacement p)
        {
            switch (p)
            {
            case Policy::PanelRowPlacement::TabLine:
                return L"on the TAB line";
            case Policy::PanelRowPlacement::BelowUnderlay:
                return L"under the menu underlay (TAB label too long)";
            case Policy::PanelRowPlacement::BelowTab:
                return L"one row under TAB (no underlay at this width)";
            default:
                return L"hidden (layout unreadable or off screen)";
            }
        }

        void PanelRowFault()
        {
            if (!g_PanelRowFaultLogged)
            {
                g_PanelRowFaultLogged = true;
                Log(L"[RALLY] command panel row draw faulted\n");
            }
        }

        // ContextualHud post-draw callback: frame thread, right after the
        // stock render, inside the fade scope (the native sprite, fill and
        // text colours are already scaled, so `opacity` is not applied
        // again) and never while EXU owns the command presentation.
        void PanelRowPostDraw(void* panel, float /*opacity*/)
        {
            if (!g_Active.load(std::memory_order_acquire) ||
                reinterpret_cast<uintptr_t>(panel) != g_ControlPanelAddr)
                return;
            PanelRowInputs in;
            if (!ReadPanelRowInputs(reinterpret_cast<uintptr_t>(panel), in))
                return;
            Policy::PanelRowGate gate;
            gate.active = true;
            // Render writes +0x11A0 only while there is a user object
            // (FUN_004a08e0.c:367-368) and takes the unit branch only while
            // DAT_00919875 is 0 (:1313).
            gate.userObject = UserObject() != nullptr;
            gate.branchInputHeld = in.branchInputHeld;
            gate.panelState = in.panelState;
            gate.selectionCount = in.selectionCount;
            gate.altLayout = in.altLayout;
            // Cheap checks first; the producer walk only when they pass.
            gate.eligibleProducer = true;
            if (!Policy::PanelRowVisible(gate))
                return;
            gate.eligibleProducer = !EditorActive() && EligibleProducerSelected();
            if (!Policy::PanelRowVisible(gate))
                return;
            ResolveKeySprites();
            const KeyCapSpec capSpec = ChooseKeyCap(CurrentRallyKey());
            if (!capSpec.valid)
                return;
            float sx = 0.0f, sy = 0.0f;
            if (!ReadUiScale(sx, sy))
                return;

            Policy::PanelRowLayoutInput layout;
            layout.tabX = in.tabX;
            layout.tabY = in.tabY;
            layout.altY = in.altY;
            layout.rowRight = in.rowRight;
            layout.scaleX = sx;
            layout.scaleY = sy;
            layout.inset = in.inset;
            layout.keyW = capSpec.atlasW;
            layout.keyH = capSpec.atlasH;
            layout.viewportW = in.viewportW;
            layout.viewportH = in.viewportH;
            // The underlay sprite FUN_004a08e0.c lines 360-365 picked this
            // frame, sized as FUN_0068f0c0 reads it (record +0xE).
            HudSpriteRectRecord underlay = {};
            layout.underlayKnown = in.underlaySprite > 0 && TryGetHudSpriteCurrentRecord(in.underlaySprite, underlay);
            layout.underlayTop = in.boundsTop;
            layout.underlaySpriteH = underlay.h;
            float capTextW = 0.0f;
            if (!MeasurePanelRowSeh(in, capSpec, capTextW, layout))
            {
                PanelRowFault();
                return;
            }
            // A drawn cap widens for a multi-character name; the sprite keeps
            // its atlas size.
            const int capWidthPx =
                capSpec.sprite ? 0 : Policy::KeyCapWidthPx(capSpec.atlasW, sx, capSpec.nameLen, capTextW);
            layout.keyWidthPx = capWidthPx;
            const Policy::PanelRowLayout placed = Policy::ChoosePanelRowLayout(layout);
            if (placed.placement != g_LastPlacement)
            {
                g_LastPlacement = placed.placement;
                Log(L"[RALLY] command panel row %ls\n", PlacementName(placed.placement));
            }
            if (placed.placement == Policy::PanelRowPlacement::Hidden)
                return;
            const bool armed = ArmedAndMatching();
            if (!DrawPanelRowSeh(in, capSpec, capWidthPx, placed.labelX, placed.rowY, sx, sy,
                                 Policy::PanelRowLabel(armed)))
                PanelRowFault();
            if (armed || !SelectedProducerHasRally())
                return;

            // The Clear row: "[Shift] [key] Clear".
            KeyCapSpec shiftSpec;
            shiftSpec.valid = true;
            std::memcpy(shiftSpec.name, Policy::kClearRowShiftCap, sizeof(Policy::kClearRowShiftCap));
            shiftSpec.nameLen = sizeof(Policy::kClearRowShiftCap) - 1;
            shiftSpec.atlasW = g_KeyZeroW > 0 ? g_KeyZeroW : capSpec.atlasW;
            shiftSpec.atlasH = g_KeyZeroW > 0 ? g_KeyZeroH : capSpec.atlasH;
            float shiftTextW = 0.0f, clearW = 0.0f, altW = 0.0f;
            bool altKnown = false;
            if (!MeasureClearRowSeh(in, shiftTextW, clearW, altKnown, altW))
            {
                PanelRowFault();
                return;
            }
            const int shiftWidthPx = Policy::KeyCapWidthPx(shiftSpec.atlasW, sx, shiftSpec.nameLen, shiftTextW);
            const int keyWidthPx = capWidthPx > 0 ? capWidthPx
                                                  : static_cast<int>(static_cast<float>(capSpec.atlasW) * sx);
            Policy::ClearRowLayoutInput clearIn;
            clearIn.rally = placed;
            clearIn.rallyLabelW = layout.labelW;
            clearIn.tabX = in.tabX;
            clearIn.tabY = in.tabY;
            clearIn.altY = in.altY;
            clearIn.inset = in.inset;
            clearIn.shiftWidthPx = shiftWidthPx;
            clearIn.keyWidthPx = keyWidthPx;
            clearIn.keyHeightPx = static_cast<int>(static_cast<float>(capSpec.atlasH) * sy);
            clearIn.clearW = clearW;
            clearIn.labelH = layout.labelH;
            clearIn.altKnown = altKnown;
            clearIn.altW = altW;
            clearIn.viewportW = in.viewportW;
            clearIn.viewportH = in.viewportH;
            clearIn.underlayKnown = layout.underlayKnown;
            clearIn.underlayTop = layout.underlayTop;
            clearIn.underlaySpriteH = layout.underlaySpriteH;
            clearIn.scaleY = layout.scaleY;
            clearIn.costW = layout.costW;
            const Policy::ClearRowLayout clearPlaced = Policy::ChooseClearRowLayout(clearIn);
            if (clearPlaced.placement != g_LastClearPlacement)
            {
                g_LastClearPlacement = clearPlaced.placement;
                Log(L"[RALLY] command panel Clear row %ls\n", ClearPlacementName(clearPlaced.placement));
            }
            if (clearPlaced.placement == Policy::ClearRowPlacement::Hidden)
                return;
            if (!DrawPanelRowSeh(in, capSpec, capWidthPx, clearPlaced.labelX, clearPlaced.rowY, sx, sy,
                                 Policy::kClearRowLabel, &shiftSpec, shiftWidthPx, keyWidthPx))
                PanelRowFault();
        }

        // Patch thread, after the hooks are in. Optional like the marker.
        void InstallPanelRow()
        {
            const HookEngine::EngineRow rows[] = {
                { "HudPaneBuffer", &g_PanelPaneAddr },
                { "UiFontContext", &g_PanelFontAddr },
                { "HudColorWhite", &g_PanelColourAddr },
                { "CommandMenuAltLayoutFlag", &g_PanelAltLayoutAddr },
                { "CommandMenuUnitBranchInput", &g_PanelBranchInputAddr },
                { "CommandMenuRowAnchors", &g_PanelAnchorsAddr },
                { "CommandMenuKeyInset", &g_PanelKeyInsetAddr },
                { "HudFadeFont", &g_PanelFontDrawAddr },
                { "CommandMenuTextHeight", &g_PanelTextHeightAddr },
                { "CommandMenuTextMeasure", &g_PanelTextMeasureAddr },
                { "HudFeedbackSprite", &g_PanelSpriteAddr },
                { "HudFillRect", &g_PanelFillAddr },
                { "HudFeedbackScale", &g_PanelScaleAddr },
                { "CommandMenuRowRects", &g_PanelRowRectsAddr },
                { "CommandUiBoundsLeft", &g_PanelBoundsAddr },
                { "CommandUiUnderlaySpriteId", &g_PanelUnderlayIdAddr },
                { "HudViewportWidth", &g_PanelViewportWAddr },
                { "HudViewportHeight", &g_PanelViewportHAddr },
                { "HudSpriteMaterialTable", &g_SpriteMaterialsAddr },
                { "HudSpriteZ", &g_SpriteZAddr },
            };
            if (!HookEngine::BindEngineRows("Producer rally panel row", rows) || !EngineGlobals::UserObjectSlot())
            {
                Log(L"[RALLY] command panel rows did not bind; panel row hidden\n");
                return;
            }
            // Optional on its own: without it only the TAB label width is
            // unknown, and the row goes under the underlay.
            const HookEngine::EngineRow localizeRow[] = { { "UiLocalize", &g_UiLocalizeAddr } };
            if (!HookEngine::BindEngineRows("Producer rally TAB label measure", localizeRow))
            {
                g_UiLocalizeAddr = 0;
                Log(L"[RALLY] UiLocalize did not bind; the panel row goes under the underlay\n");
            }
            g_PanelRowPending.store(true, std::memory_order_release);
        }

        // Game thread (main-loop tick). One attempt, the first time the
        // feature is active: a refusal (slot not stock, another callback,
        // incompatible build) would repeat.
        void AttachPanelRowOnGameThread()
        {
            if (!g_PanelRowPending.load(std::memory_order_acquire) || !g_Active.load(std::memory_order_acquire))
                return;
            if (!g_PanelRowPending.exchange(false, std::memory_order_acq_rel))
                return;
            if (ContextualHud::RegisterCommandPanelPostDraw(&PanelRowPostDraw))
                Log(L"[RALLY] command panel row registered\n");
            else
                Log(L"[RALLY] command panel post-draw seam unavailable; panel row hidden\n");
        }

        // ---- the build side ------------------------------------------------

        void OnUnitBuilt(void* producer, void* built)
        {
            float pos[3] = {};
            uint32_t producerHandle = 0;
            {
                TableShared lock;
                const Policy::RallyEntry* entry = g_Table.Find(reinterpret_cast<uintptr_t>(producer));
                if (!entry)
                    return;
                producerHandle = entry->producerHandle;
                pos[0] = entry->pos[0];
                pos[1] = entry->pos[1];
                pos[2] = entry->pos[2];
            }
            if (SafeGetObj(producerHandle) != producer)
            {
                // A new producer at a dead one's address: the rally was not its.
                TableExclusive lock;
                g_Table.Clear(reinterpret_cast<uintptr_t>(producer));
                return;
            }

            Policy::BuiltUnit unit;
            unit.present = built != nullptr;
            if (unit.present && !IsSinglePlayerSession())
                unit.remote = IsForeignObject(producer, true) || IsForeignObject(built, false);
            if (unit.present)
            {
                const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(reinterpret_cast<uintptr_t>(built)));
                unit.isScavenger = VtableTypeNameMatches(vtable, ".?AVScavenger@@");
                unit.isConstructor = VtableTypeNameMatches(vtable, ".?AVConstructionRig@@");
                unit.canCommand = SafeCanCommand(built);
                if (!ReadInt(reinterpret_cast<uintptr_t>(built) + kNextCmdWhatOffset, unit.pendingCommand))
                    unit.pendingCommand = -1;
            }
            const Policy::BuiltUnitVerdict verdict = Policy::ClassifyBuiltUnit(true, unit);
            bool ordered = false;
            if (verdict == Policy::BuiltUnitVerdict::Rally)
                ordered = SafeSetGoCommand(built, pos);
            LogBudgeted(L"[RALLY] producer 0x%08X built 0x%08X: %hs%hs\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(producer)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(built)),
                        Policy::DescribeVerdict(verdict),
                        verdict == Policy::BuiltUnitVerdict::Rally ? (ordered ? " (Go issued)" : " (Go faulted)") : "");
        }

        // Slot 42 of Recycler and Factory. thiscall, no stack arguments,
        // returns the new GameObject* (or 0).
        void* __fastcall ProducerFinishBuildHook(void* producer, void* /*edx*/)
        {
            void* built = g_StockFinishBuild(producer);
            if (g_Active.load(std::memory_order_acquire) && TableSize() != 0)
                OnUnitBuilt(producer, built);
            // Shared with AutoGroupNewUnits (auto_group_new_units.cpp), which
            // checks its own setting.
            AutoGroupOnUnitBuilt(producer, built);
            return built;
        }

        // ---- install -------------------------------------------------------

        struct SlotPlan
        {
            const wchar_t* label;
            uint32_t vtable;
            const char* rttiName;
        };

        uintptr_t SlotAddress(const SlotPlan& p)
        {
            return p.vtable + kFinishBuildSlot * sizeof(void*);
        }

        bool SlotReadyFor(const SlotPlan& p, uint32_t stockFinishBuild)
        {
            if (!VtableTypeNameMatches(p.vtable, p.rttiName))
            {
                Log(L"[RALLY] %ls RTTI mismatch vtable=0x%08X; not installed\n", p.label, p.vtable);
                return false;
            }
            void* current = ReadPtr(SlotAddress(p));
            if (current != reinterpret_cast<void*>(&ProducerFinishBuildHook) &&
                current != reinterpret_cast<void*>(static_cast<uintptr_t>(stockFinishBuild)))
            {
                Log(L"[RALLY] %ls slot mismatch slot=0x%08X current=0x%08X expected=0x%08X; not installed\n",
                    p.label, static_cast<uint32_t>(SlotAddress(p)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)), stockFinishBuild);
                return false;
            }
            return true;
        }

        bool SlotReady(const SlotPlan& p)
        {
            return SlotReadyFor(p, g_FinishBuildAddr);
        }

        bool InstallSlot(const SlotPlan& p)
        {
            void* hook = reinterpret_cast<void*>(&ProducerFinishBuildHook);
            if (ReadPtr(SlotAddress(p)) == hook)
                return true;
            if (!WritePointerValue(SlotAddress(p), hook))
            {
                Log(L"[RALLY] Failed installing %ls hook slot=0x%08X\n", p.label,
                    static_cast<uint32_t>(SlotAddress(p)));
                return false;
            }
            Log(L"[RALLY] %ls hook installed slot=0x%08X\n", p.label, static_cast<uint32_t>(SlotAddress(p)));
            return true;
        }

        // The marker is optional: without the overlay or the camera rows the
        // rally still works, it just is not drawn.
        void InstallMarker()
        {
            const HookEngine::EngineRow rows[] = {
                { "GetCameraRecord", &g_CameraRecordAddr },
                { "ViewRecord", &g_ViewRecordAddr },
            };
            if (!HookEngine::BindEngineRows("Producer rally marker", rows))
            {
                g_CameraRecordAddr = 0;
                g_ViewRecordAddr = 0;
                Log(L"[RALLY] camera rows did not bind; rally marker hidden\n");
                return;
            }
            g_MarkerPending.store(true, std::memory_order_release);
        }

        // Game thread (main-loop tick). One attempt: Ensure() failing means
        // the overlay rows do not match this build, which a retry repeats.
        void AttachMarkerOnGameThread()
        {
            if (!g_MarkerPending.exchange(false, std::memory_order_acq_rel))
                return;
            if (!HudGaugeOverlay::Ensure())
            {
                Log(L"[RALLY] HUD overlay unavailable; rally marker hidden\n");
                return;
            }
            HudGaugeOverlay::SetPainter(HudGaugeOverlay::Slot::RallyMarker, &PaintRally);
            Log(L"[RALLY] rally marker drawn on the HUD overlay\n");
        }

        void MarkFailed()
        {
            MarkOptionHookFailed("ProducerRallyPoints",
                                 "Unavailable: Rally points did not hook on this game build (see openshim.log).");
        }
    }

    bool SetProducerRally(void* producer, const float pos[3])
    {
        if (!g_Active.load(std::memory_order_acquire) || !producer || !pos || !IsHookedProducer(producer))
            return false;
        // Network game: only this machine's own producers.
        if (!IsSinglePlayerSession() && IsForeignObject(producer, true))
            return false;
        // Kept beside the pointer so a dead producer whose memory is reused
        // is recognised (GetObj(handle) no longer returns this pointer).
        const uint32_t handle = SafeGetHandle(producer);
        if (handle == 0 || SafeGetObj(handle) != producer)
            return false;
        bool stored = false;
        {
            TableExclusive lock;
            stored = g_Table.Set(reinterpret_cast<uintptr_t>(producer), handle, pos);
        }
        if (!stored)
            LogBudgeted(L"[RALLY] rally table full (%u); not set\n", static_cast<unsigned>(kTableCapacity));
        return stored;
    }

    bool ClearProducerRally(void* producer)
    {
        TableExclusive lock;
        return g_Table.Clear(reinterpret_cast<uintptr_t>(producer));
    }

    // The FinishBuild slot hook on its own, for a consumer other than the
    // rally (AutoGroupNewUnits). It binds its own copy of the shared rows, so
    // it does not depend on the rally's key path or rally-only rows, and it
    // leaves the rally's state alone; the rally's install accepts a slot that
    // already holds the hook. True once both slots hold the hook.
    bool EnsureProducerFinishBuildHook()
    {
        static std::atomic<bool> s_installed{ false };
        if (s_installed.load(std::memory_order_acquire))
            return true;
        if (reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr)) != 0x00400000)
            return false;
        uint32_t recycler = 0;
        uint32_t factory = 0;
        uint32_t finishBuild = 0;
        const HookEngine::EngineRow rows[] = {
            { "RecyclerVtable", &recycler },
            { "FactoryVtable", &factory },
            { "ProducerFinishBuild", &finishBuild },
        };
        if (!HookEngine::BindEngineRows("Producer FinishBuild hook", rows))
            return false;
        const SlotPlan plans[] = {
            { L"Recycler::FinishBuild", recycler, ".?AVRecycler@@" },
            { L"Factory::FinishBuild", factory, ".?AVFactory@@" },
        };
        for (const SlotPlan& p : plans)
        {
            if (!SlotReadyFor(p, finishBuild))
                return false;
        }
        // The stock pointer must be set before a slot points at the hook.
        if (!g_StockFinishBuild)
            g_StockFinishBuild = reinterpret_cast<FnFinishBuild>(finishBuild);
        bool all = true;
        for (const SlotPlan& p : plans)
            all = InstallSlot(p) && all;
        if (all)
            s_installed.store(true, std::memory_order_release);
        return all;
    }

    namespace
    {
        // The QuickSave and QuickLoad chords in force (defaults if either text
        // does not parse), for the rally key's collision check.
        const char* CheckRallyKey(const char* text, Policy::RallyKey& out)
        {
            namespace QK = QuickSaveKeyPolicy;
            QK::Chords quick; // defaults
            QK::Chord parsed;
            if (QK::ParseChord(QuickSave::ChordText(true), parsed))
                quick.save = parsed;
            if (QK::ParseChord(QuickSave::ChordText(false), parsed))
                quick.load = parsed;
            return Policy::CheckRallyKeyText(text, quick.save, quick.load, out);
        }
    }

    const char* RallyKeyText()
    {
        return g_RallyKeyText.c_str();
    }

    const char* SetRallyKeyText(const char* text)
    {
        Policy::RallyKey key;
        if (const char* reason = CheckRallyKey(text, key))
            return reason;
        StoreRallyKey(key);
        g_RallyKeyText = text;
        // A mark left by the old key could never be cleared by its key-up.
        g_KeyLatch = Policy::KeyLatch{};
        Log(L"[RALLY] rally key rebound to %hs\n", text);
        return nullptr;
    }

    bool RallyKeyClashesWithChord(const QuickSaveKeyPolicy::Chord& chord)
    {
        // Same rule as CheckRallyKeyText: the rally filter ignores Ctrl and
        // Alt chords, so only a Shift-only chord on the rally key clashes.
        const Policy::RallyKey key = CurrentRallyKey();
        return chord.vk == key.vk && chord.extended == key.extended && !chord.ctrl && !chord.alt;
    }

    void ResolveRallyKeyFromConfig()
    {
        std::string keyText;
        Policy::RallyKey key;
        if (!TryGetUserConfigString("Gameplay", "RallyKey", keyText) || keyText.empty())
            keyText = Policy::kDefaultRallyKeyText;
        if (const char* reason = CheckRallyKey(keyText.c_str(), key))
        {
            Log(L"[RALLY] [Gameplay] RallyKey=\"%hs\" ignored (%hs); using %hs\n", keyText.c_str(), reason,
                Policy::kDefaultRallyKeyText);
            keyText = Policy::kDefaultRallyKeyText;
            key = Policy::RallyKey{};
        }
        StoreRallyKey(key);
        g_RallyKeyText = keyText;
        g_KeyLatch = Policy::KeyLatch{};
    }

    void ReloadProducerRallyPointsConfig()
    {
        ResolveRallyKeyFromConfig();

        bool value = true;
        g_Enabled = TryGetUserConfigBool("Gameplay", "ProducerRallyPoints", value) ? value : true;
        if (!g_ConfigRead)
            Log(L"[RALLY] Baseline enabled=%hs (single-player; co-op missions can opt in)\n", g_Enabled ? "yes" : "no");
        g_ConfigRead = true;
        RefreshProducerRallyPointsState();
    }

    // The generated beacon mesh and materials, written into the chunk cache
    // root before the payload resource group initialises. Same rules as
    // EnsureShellCasingAssets: the mesh is rewritten only when its bytes
    // differ; a same-named material in another payload directory wins (our
    // marked copies are removed); unmarked files belong to the user.
    void EnsureRallyBeaconAssets(
        const std::filesystem::path& cacheRoot,
        const std::vector<std::filesystem::path>& payloadDirectories)
    {
        // Not gated on [Gameplay] ProducerRallyPoints: the Options row turns
        // the feature on live, after the payload group is initialised, so
        // the few KB must already be on disk.
        if (cacheRoot.empty())
            return;
        try
        {
            namespace RB = BZROpenShim::RallyBeacon;
            std::error_code ec;
            // Recycler (green lamp) and Factory (amber lamp) variants.
            for (const bool amberLamp : { false, true })
            {
                const NativeChunks::Piece piece = NativeChunks::RallyBeaconMesh(amberLamp);
                const auto meshPath = cacheRoot / std::filesystem::path(
                    amberLamp ? kRallyBeaconFactoryResource : kRallyBeaconResource);
                bool current = false;
                if (std::filesystem::file_size(meshPath, ec) == piece.mesh.size() && !ec)
                {
                    std::ifstream existing(meshPath, std::ios::binary);
                    std::vector<uint8_t> bytes(piece.mesh.size());
                    current = existing.read(reinterpret_cast<char*>(bytes.data()),
                                            static_cast<std::streamsize>(bytes.size())) &&
                              bytes == piece.mesh;
                }
                ec.clear();
                if (!current && !piece.mesh.empty())
                {
                    std::filesystem::create_directories(meshPath.parent_path(), ec);
                    std::ofstream output(meshPath, std::ios::binary | std::ios::trunc);
                    output.write(reinterpret_cast<const char*>(piece.mesh.data()),
                                 static_cast<std::streamsize>(piece.mesh.size()));
                    output.close();
                    Log(L"[RALLY] wrote beacon mesh %hs triangles=%u ok=%u\n", meshPath.string().c_str(),
                        piece.triangles, output ? 1u : 0u);
                }
            }

            const auto ours = cacheRoot / RB::kMaterialFile;
            for (const auto& directory : payloadDirectories)
            {
                if (std::filesystem::equivalent(directory, cacheRoot, ec) && !ec)
                    continue;
                ec.clear();
                if (!std::filesystem::is_regular_file(directory / RB::kMaterialFile, ec) || ec)
                {
                    ec.clear();
                    continue;
                }
                std::ifstream existing(ours);
                std::string first;
                if (existing && std::getline(existing, first) && first.rfind(RB::kMarker, 0) == 0)
                {
                    existing.close();
                    std::filesystem::remove(ours, ec);
                }
                for (const auto* file : RB::kTextureFiles)
                {
                    const auto path = cacheRoot / file;
                    std::ifstream texture(path, std::ios::binary);
                    std::vector<uint8_t> header(64);
                    texture.read(reinterpret_cast<char*>(header.data()), static_cast<std::streamsize>(header.size()));
                    header.resize(static_cast<size_t>(texture.gcount()));
                    texture.close();
                    if (RB::IsGeneratedTga(header))
                        std::filesystem::remove(path, ec);
                }
                Log(L"[RALLY] beacon materials overridden by %hs\n",
                    (directory / RB::kMaterialFile).string().c_str());
                return;
            }
            // Upgrade only marked generated materials.
            if (std::filesystem::exists(ours, ec))
            {
                std::ifstream existing(ours);
                std::string first;
                if (!existing || !std::getline(existing, first) || first.rfind(RB::kMarker, 0) != 0)
                    return;
            }
            std::filesystem::create_directories(cacheRoot, ec);
            for (const auto* file : RB::kTextureFiles)
            {
                const auto path = cacheRoot / file;
                const auto data = RB::TextureTga(file);
                std::ifstream input(path, std::ios::binary);
                const std::vector<uint8_t> existing((std::istreambuf_iterator<char>(input)), {});
                input.close();
                if (!existing.empty() && !RB::IsGeneratedTga(existing))
                    continue;
                if (existing == data)
                    continue;
                std::ofstream texture(path, std::ios::binary | std::ios::trunc);
                texture.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));
                if (!texture)
                    return; // do not publish a material with incomplete textures
            }
            const std::string script = RB::MaterialScript();
            std::ifstream input(ours, std::ios::binary);
            const std::string existing((std::istreambuf_iterator<char>(input)), {});
            if (existing == script)
                return;
            input.close();
            std::ofstream output(ours, std::ios::binary | std::ios::trunc);
            output << script;
            output.close();
            Log(L"[RALLY] wrote beacon materials %hs ok=%u\n", ours.string().c_str(), output ? 1u : 0u);
        }
        catch (...)
        {
            // Optional: the beacon falls back to the stock mesh.
        }
    }

    // Installed regardless of the ini value, so the Options row can turn the
    // feature on live; while it is off every hook is a pass-through.
    // The caller (InstallAiTuningHooksIfPossible) runs on every patcher pass.
    // A row or vtable check can fail only because the code pages have not
    // settled yet (Steam), so those failures are retried on later passes, up
    // to kMaxInstallAttempts; every other failure ends the attempts.
    void InstallProducerRallyPointsIfPossible()
    {
        constexpr int kMaxInstallAttempts = 40;
        static bool s_done = false;
        static int s_attempts = 0;
        if (s_done)
            return;
        if (++s_attempts >= kMaxInstallAttempts)
            s_done = true;
        if (!g_ConfigRead)
            ReloadProducerRallyPointsConfig();

        if (reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr)) != 0x00400000)
        {
            Log(L"[RALLY] Executable relocated; feature unavailable\n");
            MarkFailed();
            s_done = true;
            return;
        }

        const HookEngine::EngineRow rows[] = {
            { "RecyclerVtable", &g_RecyclerVtableAddr },
            { "FactoryVtable", &g_FactoryVtableAddr },
            { "ProducerFinishBuild", &g_FinishBuildAddr },
            { "GameObjectSetCommandWhere", &g_SetCommandAddr },
            { "GameObjectHandleGetObj", &g_GetObjAddr },
            { "ControlPanelGlobal", &g_ControlPanelAddr },
            { "ReticleGlobal", &g_ReticleAddr },
            { "InputEditModeFlag", &g_EditModeFlagAddr },
        };
        if (!HookEngine::BindEngineRows("Producer rally points", rows))
        {
            Log(L"[RALLY] Engine rows did not bind (attempt %d); feature unavailable\n", s_attempts);
            MarkFailed();
            return;
        }
        g_StockFinishBuild = reinterpret_cast<FnFinishBuild>(g_FinishBuildAddr);
        g_FnSetCommand = reinterpret_cast<FnSetCommandWhere>(g_SetCommandAddr);
        g_FnGetObj = reinterpret_cast<FnGetObj>(g_GetObjAddr);

        // Recycler and Factory only. The Producer base and ConstructionRig
        // vtables hold the same function in slot 42 and are left stock.
        const SlotPlan plans[] = {
            { L"Recycler::FinishBuild", g_RecyclerVtableAddr, ".?AVRecycler@@" },
            { L"Factory::FinishBuild", g_FactoryVtableAddr, ".?AVFactory@@" },
        };
        for (const SlotPlan& p : plans)
        {
            if (!SlotReady(p))
            {
                MarkFailed();
                return;
            }
        }
        // From here every failure is permanent, or a retry would patch a
        // half-patched process, so this is the last attempt.
        s_done = true;
        ClearOptionHookFailed("ProducerRallyPoints");

        // The key path first: without it nothing can set a rally, so a
        // FinishBuild hook alone would be dead weight.
        if (IatPatch::PatchImportFromAnyDll(GetModuleHandleW(nullptr), "PeekMessageA",
                reinterpret_cast<void*>(&Hooked_PeekMessageA),
                reinterpret_cast<void**>(&g_RealPeekMessageA)) != IatPatch::Result::Patched)
        {
            Log(L"[RALLY] PeekMessageA seam not installed; feature unavailable\n");
            MarkFailed();
            return;
        }

        bool all = true;
        for (const SlotPlan& p : plans)
            all = InstallSlot(p) && all;
        g_HooksInstalled = all;
        Log(L"[RALLY] Producer rally points %hs\n",
            all ? "installed (the rally key sets or toggles set mode, Shift+key clears)" : "partially installed; feature stays off");
        if (!all)
            MarkFailed();
        else
        {
            InstallMarker();
            InstallPanelRow();
            InstallSpaceLabel();
        }
        RefreshProducerRallyPointsState();
    }

    void RefreshProducerRallyPointsState()
    {
        const bool singlePlayer = IsSinglePlayerSession();
        const bool want = Policy::ShouldBeActive(g_Enabled, g_HooksInstalled, singlePlayer,
                                                 g_MissionAllowsNetwork.load(std::memory_order_acquire));
        if (want != g_Active.load(std::memory_order_acquire))
        {
            g_Active.store(want, std::memory_order_release);
            Log(L"[RALLY] %hs\n", !want ? "Stood down"
                                 : singlePlayer ? "Active (single-player)"
                                                : "Active (network game, mission opt-in)");
            if (!want)
                Disarm(L"stood down");
            // A stood-down feature's rallies are dropped by the next
            // interactive main-loop tick (MainLoopTick).
        }
    }

    // Mission end/load. Rallies are not persisted, and there is no game
    // object to clean up: the marker is drawn only, and the beacons are
    // shim-owned Ogre objects, destroyed here and rebuilt on demand.
    void ResetProducerRallyPoints()
    {
        DestroyMeshSlots(GetOgreSceneManagerRuntime(), L"rally reset");
        Disarm(L"rally reset");
        {
            TableExclusive lock;
            g_Table.ClearAll();
        }
        g_PendingAction.store(0, std::memory_order_release);
        g_LastLivenessCheck = 0;
        g_LogBudget = 48;
        if (g_MissionAllowsNetwork.exchange(false, std::memory_order_acq_rel))
            Log(L"[RALLY] network-game opt-in cleared (mission reset)\n");
        RefreshProducerRallyPointsState();
    }

    // EXU AllowRallyPoints: lets the running mission use rally points in a
    // network game (co-op). Mission-scoped: cleared on mission reset. The
    // user's [Gameplay] ProducerRallyPoints still decides. Returns true when
    // the opt-in is recorded, not that the feature is active (the log line
    // says that). Refused (false) when the ownership check is unavailable,
    // since without it a machine could order another machine's units.
    bool SetProducerRallyPointsNetworkAllowed(bool allowed)
    {
        if (allowed && g_RemoteCheck.load(std::memory_order_acquire) == RemoteCheck::Untried)
        {
            // Both rows are layout guards: IsRemote pins DistributedObject+0x68,
            // SimulateRemoteCopy pins DistributedObject at GameObject+0x18.
            uint32_t isRemote = 0;
            uint32_t remoteCopy = 0;
            const HookEngine::EngineRow rows[] = {
                { "DistributedObjectIsRemote", &isRemote },
                { "GameObjectSimulateRemoteCopy", &remoteCopy },
            };
            const bool bound = HookEngine::BindEngineRows("Producer rally network check", rows) &&
                               isRemote != 0 && remoteCopy != 0;
            g_RemoteCheck.store(bound ? RemoteCheck::Bound : RemoteCheck::Failed, std::memory_order_release);
        }
        if (allowed && g_RemoteCheck.load(std::memory_order_acquire) != RemoteCheck::Bound)
        {
            Log(L"[RALLY] network-game opt-in refused: ownership check rows not bound\n");
            return false;
        }
        g_MissionAllowsNetwork.store(allowed, std::memory_order_release);
        RefreshProducerRallyPointsState();
        Log(L"[RALLY] network-game opt-in %hs by the mission (enabled=%hs installed=%hs active=%hs)\n",
            allowed ? "set" : "cleared", g_Enabled ? "yes" : "no", g_HooksInstalled ? "yes" : "no",
            g_Active.load(std::memory_order_acquire) ? "yes" : "no");
        return true;
    }

    int ProducerRallyCommandHookIndex(const char* patchName)
    {
        if (!patchName)
            return -1;
        for (int i = 0; i < kCommandHookCount; ++i)
        {
            if (std::strcmp(patchName, kCommandHookNames[i]) == 0)
                return i;
        }
        return -1;
    }

    // Patcher thread, before the JMP5 is written. Relocates the 6-byte
    // prologue (no relative operands) into a trampoline that jumps back to
    // site + 6 and returns the detour for the JMP5. Null leaves the site stock.
    void* PrepareProducerRallyCommandHook(int index, uint32_t site)
    {
        if (index < 0 || index >= kCommandHookCount)
            return nullptr;
        void* const detours[kCommandHookCount] = {
            reinterpret_cast<void*>(&AimGroundCommandDetour),
            reinterpret_cast<void*>(&AimObjectCommandDetour),
            reinterpret_cast<void*>(&BroadcastCommandDetour),
        };
        void** const originals[kCommandHookCount] = {
            reinterpret_cast<void**>(&g_OrigAimGround),
            reinterpret_cast<void**>(&g_OrigAimObject),
            reinterpret_cast<void**>(&g_OrigBroadcast),
        };
        if (*originals[index])
            return detours[index];

        uint8_t prologue[kPrologueLength] = {};
        if (!site || !HookEngine::ReadMemory(site, prologue, kPrologueLength) ||
            std::memcmp(prologue, kCommandHookPrologues[index], kPrologueLength) != 0)
        {
            Log(L"[RALLY] %hs: prologue mismatch at 0x%08X (%02X %02X %02X %02X %02X %02X); "
                L"set mode unavailable, V sets the rally at once\n",
                kCommandHookNames[index], site, prologue[0], prologue[1], prologue[2], prologue[3], prologue[4],
                prologue[5]);
            return nullptr;
        }
        auto* tramp = static_cast<uint8_t*>(
            VirtualAlloc(nullptr, 32, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
        if (!tramp)
        {
            Log(L"[RALLY] %hs: trampoline allocation failed; set mode unavailable\n", kCommandHookNames[index]);
            return nullptr;
        }
        std::memcpy(tramp, prologue, kPrologueLength);
        tramp[kPrologueLength] = 0xE9;
        const int32_t rel = static_cast<int32_t>(site + kPrologueLength) -
                            static_cast<int32_t>(reinterpret_cast<uintptr_t>(tramp) + kPrologueLength + 5);
        std::memcpy(tramp + kPrologueLength + 1, &rel, sizeof(rel));
        FlushInstructionCache(GetCurrentProcess(), tramp, kPrologueLength + 5);
        *originals[index] = tramp;
        return detours[index];
    }

    void NoteProducerRallyCommandHookInstalled(int index)
    {
        if (index < 0 || index >= kCommandHookCount)
            return;
        const unsigned bit = 1u << index;
        const unsigned mask = g_CommandHooksInstalled.fetch_or(bit, std::memory_order_acq_rel) | bit;
        Log(L"[RALLY] %hs installed%hs\n", kCommandHookNames[index],
            mask == kAllCommandHooks ? "; rally set mode available (V arms, menu_press confirms)" : "");
    }

    void TickProducerRallyMeshes()
    {
        MeshTick();
    }

    void ForgetProducerRallyMeshes(const wchar_t* reason)
    {
        ForgetMeshSlots(reason);
    }

    void DestroyProducerRallySceneObjects(void* sceneManager, const wchar_t* reason)
    {
        DestroyMeshSlots(sceneManager, reason);
    }
}
