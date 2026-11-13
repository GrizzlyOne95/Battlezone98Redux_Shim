// producer_rally_points.cpp
// BZR Open Shim - producer rally points. [Gameplay] ProducerRallyPoints,
// default ON, single player only. With a Recycler or Factory selected, V sets
// its rally point to the ground under the reticle; Shift+V clears it. Each
// unit that producer finishes afterwards (not scavengers or constructors) gets
// a Go order to the rally point. While a rallied producer is selected, a HUD
// marker labelled "Rally" (and a dotted line from the producer) shows the
// point; it is drawn only, never a game object, so nothing is saved and no nav
// slot is used. Addresses, evidence and limits: Docs/PRODUCER_RALLY_POINTS.md.
//
// Engine touch points:
//   * Recycler/Factory vtable slot 42 (Producer::FinishBuild, which returns the
//     new GameObject*): after the stock call, a Go order for the new unit.
//   * The game window procedure, subclassed: V/Shift+V become a request.
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
#include "patcher.h"
#include "producer_rally_policy.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>

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

        // Caller has checked WorldInteractive().
        void ApplyToSelection(Policy::KeyAction action)
        {
            if (EditorActive())
                return;
            float pos[3] = {};
            if (action == Policy::KeyAction::SetRally)
            {
                const uintptr_t groundPos = reinterpret_cast<uintptr_t>(
                    ReadPtr(g_ReticleAddr + kReticleGroundPosOffset));
                if (!groundPos || !ReadVector(groundPos, pos))
                {
                    LogBudgeted(L"[RALLY] V: no ground under the reticle; nothing set\n");
                    return;
                }
            }
            int applied = 0;
            ForEachSelectedProducer([&](void* producer, uint32_t) {
                const bool ok = action == Policy::KeyAction::SetRally
                    ? SetProducerRally(producer, pos)
                    : ClearProducerRally(producer);
                if (ok)
                    ++applied;
            });
            if (action == Policy::KeyAction::SetRally)
                LogBudgeted(L"[RALLY] V: rally set for %d producer(s) at (%.1f, %.1f, %.1f)\n",
                            applied, pos[0], pos[1], pos[2]);
            else
                LogBudgeted(L"[RALLY] Shift+V: rally cleared for %d producer(s)\n", applied);
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
            // Nothing queued and nothing stored: skip the shell-state reads.
            if (pending == 0 && tableSize == 0)
                return;

            const ULONGLONG now = GetTickCount64();
            const Policy::TickPlan plan = Policy::PlanTick(WorldInteractive(), active, pending != 0,
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

        // ---- the HUD marker ------------------------------------------------

        // Shown only while a rallied producer is selected (BZCC behaviour).
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
                {
                    TableShared lock;
                    const Policy::RallyEntry* entry = g_Table.Find(reinterpret_cast<uintptr_t>(producer));
                    if (!entry)
                        return;
                    rally[0] = entry->pos[0];
                    rally[1] = entry->pos[1];
                    rally[2] = entry->pos[2];
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
            all ? "installed (V sets, Shift+V clears)" : "partially installed; feature stays off");
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
            // A stood-down feature's rallies are dropped by the next
            // interactive main-loop tick (MainLoopTick).
        }
    }

    // Mission end/load. Rallies are not persisted, and there is no game
    // object to clean up: the marker is drawn only.
    void ResetProducerRallyPoints()
    {
        {
            TableExclusive lock;
            g_Table.ClearAll();
        }
        g_PendingAction.store(0, std::memory_order_release);
        g_LastLivenessCheck = 0;
        g_LogBudget = 48;
        RefreshProducerRallyPointsState();
    }
}
