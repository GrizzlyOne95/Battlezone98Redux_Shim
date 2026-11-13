// producer_rally_points.cpp
// BZR Open Shim - producer rally points. [Gameplay] ProducerRallyPoints,
// default ON, single player only. With a Recycler or Factory selected, V
// toggles rally set mode: while it is armed the stock ground reticle and order
// line preview the point exactly like a Go order, the stock confirm key
// (menu_press, "Reticle Command") sets the rally there, and V again cancels.
// Shift+V clears the rally. Without the three command hooks below, V sets the
// rally at once to the ground under the reticle (the original behaviour). Each
// unit that producer finishes afterwards (not scavengers or constructors) gets
// a Go order to the rally point. While a rallied producer is selected, a HUD
// marker labelled "Rally" (and a dotted line from the producer) shows the
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
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "game_state.h"
#include "hook_engine.h"
#include "hud_gauge_overlay.h"
#include "iat_patch.h"
#include "native_chunk_mesh.h"
#include "native_chunk_prune.h"
#include "patcher.h"
#include "producer_rally_policy.h"
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
        constexpr uint32_t kDotArgb = 0xC060FF60;
        constexpr int kMarkerHalf = 4;
        constexpr int kDotHalf = 1;
        constexpr float kDotSpacing = 18.0f;
        constexpr size_t kMaxDots = 48;
        constexpr char kMarkerText[] = "Rally";

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
            if ((msg == Policy::kWmKeyDown || msg == Policy::kWmKeyUp) && w == Policy::kVkV)
            {
                Policy::KeyEvent key;
                key.msg = msg;
                key.vk = static_cast<unsigned>(w);
                key.lParam = static_cast<unsigned long long>(static_cast<uint32_t>(l));
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
                const Policy::KeyDecision decision = Policy::ClassifyRallyKey(key, gate, g_KeyLatch);
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
                Disarm(L"Shift+V");
                int applied = 0;
                ForEachSelectedProducer([&](void* producer, uint32_t) {
                    if (ClearProducerRally(producer))
                        ++applied;
                });
                LogBudgeted(L"[RALLY] Shift+V: rally cleared for %d producer(s)\n", applied);
                return;
            }

            const bool armed = g_Armed.load(std::memory_order_acquire);
            const Policy::SetKeyPlan plan =
                Policy::PlanSetKey(SetModeAvailable(), armed, armed && SelectionMatchesArmed());
            if (plan == Policy::SetKeyPlan::Cancel)
            {
                Disarm(L"V");
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

        void MainLoopTick()
        {
            EnsureSubclass();
            AttachMarkerOnGameThread();
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
        };

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

        void MeshTick()
        {
            if (g_MeshUnavailable)
                return;
            uintptr_t producers[kMeshPoolSize] = {};
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
                if (!slot.entity)
                {
                    slot = RallyMeshSlot{};
                    bool created = false;
                    if (!g_BeaconFallback)
                    {
                        created = CreateShimOwnedMeshObject(kRallyBeaconResource, slot.sceneManager, slot.node, slot.entity);
                        if (created)
                            g_BeaconCreateFailures = 0;
                        else
                        {
                            // A not-yet-ready scene also lands here: retry on
                            // later ticks, and switch to stock only once the
                            // failure repeats.
                            slot = RallyMeshSlot{};
                            if (++g_BeaconCreateFailures < kMaxBeaconCreateFailures)
                                return;
                            g_BeaconFallback = true;
                            Log(L"[RALLY] generated beacon mesh %hs could not be created %d times; using stock %hs\n",
                                kRallyBeaconResource, g_BeaconCreateFailures, kRallyMeshName);
                        }
                    }
                    if (!created)
                        created = CreateShimOwnedStockMeshObject(kRallyMeshName, slot.sceneManager, slot.node, slot.entity);
                    if (created && !g_BeaconInUseLogged)
                    {
                        g_BeaconInUseLogged = true;
                        Log(L"[RALLY] rally beacon mesh in use: %hs\n",
                            g_BeaconFallback ? kRallyMeshName : kRallyBeaconResource);
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

        // Shown only while a rallied producer is selected (BZCC behaviour).
        // With a 3D beacon on the rally the square is left out; the dotted
        // line and the "Rally" label stay, so the beacon reads as this
        // producer's rally rather than a stock nav.
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

                float origin[3] = {};
                float px = 0.0f, py = 0.0f;
                if (TryGetGameObjectWorldPosition(producer, origin) &&
                    Policy::ProjectToScreen(cam, origin, px, py))
                {
                    float dots[kMaxDots][2];
                    const size_t n = Policy::LineDots(px, py, rx, ry, kDotSpacing, kMaxDots, dots);
                    for (size_t i = 0; i < n && ok; ++i)
                    {
                        if (!Policy::OnScreen(dots[i][0], dots[i][1], frame.viewW, frame.viewH))
                            continue;
                        const int x = static_cast<int>(dots[i][0]);
                        const int y = static_cast<int>(dots[i][1]);
                        ok = SafeFill(frame, x - kDotHalf, y - kDotHalf, x + kDotHalf, y + kDotHalf, kDotArgb);
                    }
                }
                if (!ok || !Policy::OnScreen(rx, ry, frame.viewW, frame.viewH))
                    return;
                const int x = static_cast<int>(rx);
                const int y = static_cast<int>(ry);
                if (!beacon)
                    ok = SafeFill(frame, x - kMarkerHalf, y - kMarkerHalf, x + kMarkerHalf, y + kMarkerHalf,
                                  kMarkerArgb);
                if (!ok)
                    return;
                const int textY = y + kMarkerHalf + 2;
                ok = HudGaugeOverlay::DrawPanelText(frame, x - 22, textY - 1, x + 22, textY + 13,
                                                    kMarkerPanelArgb, x, textY, kMarkerText, kMarkerArgb, 1);
            });
            return ok;
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

        bool SlotReady(const SlotPlan& p)
        {
            if (!VtableTypeNameMatches(p.vtable, p.rttiName))
            {
                Log(L"[RALLY] %ls RTTI mismatch vtable=0x%08X; not installed\n", p.label, p.vtable);
                return false;
            }
            void* current = ReadPtr(SlotAddress(p));
            if (current != reinterpret_cast<void*>(&ProducerFinishBuildHook) &&
                current != reinterpret_cast<void*>(static_cast<uintptr_t>(g_FinishBuildAddr)))
            {
                Log(L"[RALLY] %ls slot mismatch slot=0x%08X current=0x%08X expected=0x%08X; not installed\n",
                    p.label, static_cast<uint32_t>(SlotAddress(p)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)), g_FinishBuildAddr);
                return false;
            }
            return true;
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

    void ReloadProducerRallyPointsConfig()
    {
        bool value = true;
        g_Enabled = TryGetUserConfigBool("Gameplay", "ProducerRallyPoints", value) ? value : true;
        if (!g_ConfigRead)
            Log(L"[RALLY] Baseline enabled=%hs (SP-only)\n", g_Enabled ? "yes" : "no");
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
            const NativeChunks::Piece piece = NativeChunks::RallyBeaconMesh();
            const auto meshPath = cacheRoot / std::filesystem::path(kRallyBeaconResource);
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
            all ? "installed (V sets or toggles set mode, Shift+V clears)" : "partially installed; feature stays off");
        if (!all)
            MarkFailed();
        else
            InstallMarker();
        RefreshProducerRallyPointsState();
    }

    void RefreshProducerRallyPointsState()
    {
        const bool want = g_Enabled && g_HooksInstalled && IsSinglePlayerSession();
        if (want != g_Active.load(std::memory_order_acquire))
        {
            g_Active.store(want, std::memory_order_release);
            Log(L"[RALLY] %hs\n", want ? "Active (SP-only)" : "Stood down");
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
        RefreshProducerRallyPointsState();
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
