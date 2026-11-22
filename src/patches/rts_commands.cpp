// rts_commands.cpp
// BZR Open Shim - RTS command extras for the stock unit command menu.
//
//   [Gameplay] RtsRemoteTarget (default OFF)
//     * Shift+T (RtsRemoteTargetKey) sets the player's target to a selected
//       own unit without touching the selection; each press moves to the next
//       selected unit. Stock T (frontal_target) never sees the press.
//     * B (RtsBuildingCycleKey) cycles the target through the player's
//       buildings (Recycler, Factory and Armory included), newest first.
//   [Gameplay] RtsSmartCommandMenu (default OFF)
//     * A mixed selection (a Ctrl+1 group of wingmen, walkers, APCs,
//       howitzers) keeps Hunt, Follow Close (Formation) and Defend in the
//       menu; each is sent only to the units whose own menu offers it.
//   [Gameplay] RtsSmartRepairReload (default OFF)
//     * Get Repair / Get Reload show when any selected unit needs them and
//       go only to the units that do.
//   [Gameplay] RtsAreaSelect (default OFF)
//     * X (RtsAreaSelectKey) adds the player's units of the same family as
//       the reticle object (else the first selected unit) within 100 m;
//       Shift+X within 200 m.
//   [Gameplay] RtsHold (default 2: key and Shift menu; 1 key only; 0 off)
//     * Z (RtsHoldKey) gives the selected units that have a Defend entry
//       Defend(0) plus the native hold. With Shift held the Defend entry
//       reads "Hold" and choosing it does the same. Single player only, like
//       the native hold it uses (ai_native_orders.cpp SetAiHold).
//   [Gameplay] RtsQuickCommands (default OFF)
//     * Numpad 1/2/3/5 (RtsQuickFollowKey / DefendKey / AttackKey / StopKey)
//       order the selected own units: Follow and Defend the player's vehicle,
//       Attack the player's current target (GameObject +0x21C), Stop. The
//       selection is kept. Single player only, like Hold. Needs NumLock on.
//   [Gameplay] RtsBuildAtNav (default OFF)
//     * With a building picked on a selected Construction Rig, the Go To
//       Nav entry reads "Build at Nav"; picking a nav validates the spot
//       with the rig's own GetCommand and gives BUILD there (refused rigs
//       buzz, and an all-refused pick keeps the selection). Other selected
//       units get the stock GO. Local rigs only.
//   Idle units (key: always on once its rows bind)
//     * J (RtsIdleUnitKey) selects the next idle own unit (ascending handle
//       order, one per press); Shift+J selects all of them up to the
//       selection capacity. mnu_buzz when none is idle.
//   [Gameplay] RtsIdleUnitAlert (default OFF)
//     * One short stock sound when an own unit goes from busy to idle, at
//       most once per 5 s, never for a unit's first observed state.
//     * Idle = current and pending command `what` both 0 or 2 (CMD_STOP).
//   [Gameplay] RtsAmmoAlert (default OFF)
//     * The stock "out of ammo" voice line (abetty5/sbetty5 by nation) when
//       an own armed unit drops under 5% ammo, at most once per 30 s.
//   [Gameplay] RtsScrapFullAlert (default OFF)
//     * The stock "scrap full" voice line (avrecyvn/svrecyvn by nation) when
//       the team's scrap reaches its maximum (30+), at most once per 60 s.
//   [Gameplay] RtsFollowCamera (default OFF)
//     * In the satellite view, Shift+C (RtsFollowCameraKey) keeps the view
//       centred on the first selected own unit (else the player's vehicle);
//       Shift+C again stops. Leaving the satellite view or the unit dying
//       stops it too. Each frame calls the stock OverView::SetObject
//       (0x00588970) on the overview, the call the satellite setter makes
//       once on entry. Local camera only; works in multiplayer.
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
#include "hud_visibility.h"
#include "iat_patch.h"
#include "mru_class.h"
#include "mru_class_policy.h"
#include "openshim_l10n_text.h"
#include "patcher.h"
#include "quicksave.h"
#include "quicksave_key_policy.h"
#include "rts_commands_policy.h"
#include "rts_markers.h"
#include "rts_placement.h"
#include "scene_mutation_drain.h"
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
        // GameObject::EnemyP(GameObject*) (row GameObjectEnemyP).
        using FnEnemyP = bool(__thiscall*)(void* self, void* other);
        using FnSetTarget = void(__thiscall*)(void* obj, void* target);
        using FnSelectAdd = void(__thiscall*)(void* panel, void* obj);
        using FnSelectNone = void(__thiscall*)(void* panel);
        // The HUD getters contextual_hud.cpp binds: HudFadeGetTeam (cdecl, the
        // local Team*), and the thiscall GameObject / Team value getters.
        using FnGetLocalTeam = void*(__cdecl*)();
        using FnGetValue = uint32_t(__thiscall*)(void* self);
        using FnLocalize = const char*(__cdecl*)(const char* section, const char* key);
        using FnPlaySound = int(__cdecl*)(const char* filename, uint32_t, uint32_t, uint32_t);
        using FnGetPosition = const float*(__thiscall*)(void* entity);
        using FnRigGetCommand = int(__thiscall*)(void* rig, const float* pos);
        // OverView::SetObject(GameObject* complete): copies the object's
        // position into the view centre (+0x44) the satellite camera matrix
        // reads (FUN_00588a40). No null check: callers pass a live object.
        using FnOverViewSetObject = void(__thiscall*)(void* overview, void* obj);
        using FnSetCommandWhere = void(__thiscall*)(void* obj, int what, const float* where, uint32_t paramLow,
                                                    uint32_t paramHigh);

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
        // GameObject's pending order, as GameObject::SetCommand writes it:
        // +0xC8 = 0, +0xCC = what, +0xD0 = who's handle (0 without one),
        // +0xD4 = a freshly built path object (FUN_004dbd60 lines 20-34;
        // FUN_004dbce0 lines 8-11 for the who-less form). Read only, to
        // see which order a unit-menu pick gave (the ping below).
        constexpr size_t kPendingOrderOffset = 0xC8;
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
        constexpr uint32_t kNavPickCallOffset = 0x11;       // BroadcastCommand, 0x004A4A75
        constexpr uint32_t kNavPickSelectNoneOffset = 0x1C; // SelectNone, 0x004A4A80
        // DistributedObject +0x68: 2 for a remote replica (FUN_004b9830). The
        // DistributedObject base sits at GameObject +0x18, so GameObject +0x80
        // (as kGoObjectTypeOffset in producer_rally_points.cpp).
        constexpr size_t kOwnershipOffset = 0x18 + 0x68;
        // ConstructionRig: +0x228 must be 0 for GetCommand (0x0049D251);
        // +0x370 the drop class SetActiveMode stores (FUN_0049d0e0 line 13).
        constexpr size_t kRigBusyOffset = 0x228;
        constexpr size_t kRigDropClassOffset = 0x370;
        constexpr int kMaxInstallAttempts = 40;
        constexpr size_t kMaxObjects = 4096;
        constexpr ULONGLONG kTickFreshMs = 500;
        constexpr const char* kClickSound = "mnu_clik.wav";
        // The stock "cannot build here" click (FUN_004a08e0.c line 564, a
        // CMD_NO_DROPOFF hover; push at 0x004A1E6F).
        constexpr const char* kRefuseSound = "mnu_buzz.wav";
        // The idle-unit alert: stock bzone.zfs holds ping.wav (listed with the
        // BZ98R toolkit's ZFSReader on the GOG 2.2.301 install, read-only).
        constexpr const char* kIdleAlertSound = "ping.wav";
        constexpr ULONGLONG kIdleScanIntervalMs = 250;

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
        uint32_t g_EnemyPAddr = 0;
        uint32_t g_DefendClickRowAddr = 0;
        uint32_t g_LabelRowAddr = 0;
        uint32_t g_LocalizeAddr = 0;
        // Read by the naked thunks.
        uint32_t g_PlaySoundAddr = 0;
        uint32_t g_DefendClickResumeAddr = 0;
        // Build at Nav (its own copies: a failed bind zeroes every out).
        uint32_t g_NavPickRowAddr = 0;
        uint32_t g_NavBroadcastObjAddr = 0;
        uint32_t g_NavSetCommandObjAddr = 0;
        uint32_t g_NavSetCommandWhereAddr = 0;
        uint32_t g_NavSelectNoneAddr = 0;
        uint32_t g_RigVtableAddr = 0;
        uint32_t g_RigGetCommandAddr = 0;
        // Idle units (its own copies of the select/sound rows).
        uint32_t g_IdleSelectAddAddr = 0;
        uint32_t g_IdleSelectNoneAddr = 0;
        // Ammo-out and scrap-full alerts (its own copies of the HUD getter rows
        // contextual_hud.cpp binds).
        uint32_t g_AlertGetAmmoAddr = 0;
        uint32_t g_AlertMaxAmmoAddr = 0;
        uint32_t g_AlertGetTeamAddr = 0;
        uint32_t g_AlertGetScrapAddr = 0;
        uint32_t g_AlertGetMaxScrapAddr = 0;
        // Follow camera.
        uint32_t g_OverViewSetObjectRowAddr = 0; // OverView_SetObject(handle) wrapper
        uint32_t g_OverViewSetObjectAddr = 0;
        uint32_t g_OverViewAddr = 0; // the global OverView, read from the wrapper

        FnGetObj g_FnGetObj = nullptr;
        FnIntersect g_FnIntersect = nullptr;
        FnDispatchMode g_FnDispatch = nullptr;
        FnBroadcastObj g_FnBroadcastObj = nullptr;
        FnSetCommandObj g_FnSetCommandObj = nullptr;
        FnSetCommand g_FnSetCommand = nullptr;
        FnEnemyP g_FnEnemyP = nullptr;
        FnSetTarget g_FnSetTarget = nullptr;
        FnSelectAdd g_FnSelectAdd = nullptr;
        FnSelectNone g_FnSelectNone = nullptr;
        FnLocalize g_FnLocalize = nullptr;
        FnPlaySound g_FnPlaySound = nullptr;
        FnBroadcastObj g_FnNavBroadcastObj = nullptr;
        FnSetCommandObj g_FnNavSetCommandObj = nullptr;
        FnSetCommandWhere g_FnNavSetCommandWhere = nullptr;
        FnSelectNone g_FnNavSelectNone = nullptr;
        FnRigGetCommand g_FnRigGetCommand = nullptr;
        FnOverViewSetObject g_FnOverViewSetObject = nullptr;
        FnGetValue g_FnGetAmmo = nullptr;
        FnGetValue g_FnMaxAmmo = nullptr;
        FnGetLocalTeam g_FnGetTeam = nullptr;
        FnGetValue g_FnGetScrap = nullptr;
        FnGetValue g_FnGetMaxScrap = nullptr;

        // Config ([Gameplay]); main thread.
        bool g_ConfigRead = false;
        bool g_TargetEnabled = false;
        bool g_SmartMenuEnabled = false;
        bool g_SmartRepairEnabled = false;
        bool g_AreaEnabled = false;
        int g_HoldMode = Policy::kHoldOff;
        bool g_BuildNavEnabled = false;
        bool g_IdleAlertEnabled = false;
        bool g_AmmoAlertEnabled = false;
        bool g_ScrapAlertEnabled = false;
        bool g_FollowEnabled = false;
        bool g_QuickEnabled = false;

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
        bool g_NavSelectNoneReady = false;
        bool g_NavPickReady = false;
        bool g_IdleReady = false;
        bool g_AlertsReady = false; // the ammo-out and scrap-full getters
        bool g_FollowReady = false;

        // Live state.
        std::atomic<unsigned> g_SmartMask{ 0 }; // Policy::SmartSet bits in force
        std::atomic<bool> g_TargetActive{ false };
        std::atomic<bool> g_AreaActive{ false };
        std::atomic<bool> g_HoldKeyActive{ false };
        std::atomic<bool> g_QuickKeyActive{ false };
        std::atomic<bool> g_HoldMenuActive{ false };
        std::atomic<bool> g_BuildNavActive{ false };
        std::atomic<bool> g_IdleKeyActive{ false };
        std::atomic<bool> g_IdleAlertActive{ false };
        std::atomic<bool> g_AmmoAlertActive{ false };
        std::atomic<bool> g_ScrapAlertActive{ false };
        std::atomic<bool> g_FollowActive{ false };
        std::atomic<bool> g_IdleResetPending{ false };
        std::atomic<bool> g_AmmoResetPending{ false };
        std::atomic<bool> g_ScrapResetPending{ false };
        std::atomic<bool> g_IdlePickResetPending{ false };
        // Set by the nav-pick hook for the SelectNone call that follows it
        // (same Render frame, game thread).
        bool g_SkipNavSelectNone = false;
        std::atomic<ULONGLONG> g_LastTickMs{ 0 };
        // Actions queued by the key filter (main thread) for the tick.
        std::atomic<bool> g_PendingRemoteTarget{ false };
        std::atomic<bool> g_PendingBuilding{ false };
        std::atomic<int> g_PendingArea{ 0 }; // 1: 100 m, 2: 200 m
        std::atomic<bool> g_PendingHold{ false };
        std::atomic<unsigned> g_PendingQuick{ 0 }; // bit per quick KeyId
        std::atomic<int> g_PendingIdle{ 0 }; // 1: next idle unit, 2: all idle units
        std::atomic<bool> g_PendingFollow{ false };
        std::atomic<bool> g_FollowResetPending{ false };
        // Game thread: the handle being followed, 0 when off.
        uint32_t g_FollowHandle = 0;
        volatile long g_LogBudget = 48;
        // Idle units: drain thread only (the key action and the alert scan).
        volatile long g_IdleStateLogBudget = 300;
        uint32_t g_LastIdlePick = 0;
        ULONGLONG g_IdleLastScanMs = 0;
        Policy::IdleTracker g_IdleTracker;
        // Ammo-out and scrap-full alerts: drain thread only (the same scan).
        volatile long g_AlertLogBudget = 300;
        Policy::AmmoTracker g_AmmoTracker;
        Policy::ScrapFullDetector g_ScrapDetector;

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

        // EnemyP under SEH; false (not an enemy) when unavailable or faulted.
        bool SafeEnemyP(void* self, void* other)
        {
            if (!g_FnEnemyP || !self || !other)
                return false;
            __try
            {
                return g_FnEnemyP(self, other);
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

        void SafePlaySound(const char* name)
        {
            if (!g_FnPlaySound)
                return;
            __try
            {
                g_FnPlaySound(name, 0, 0, 0);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        // A thiscall value getter (ammo, max ammo, scrap, max scrap) under SEH.
        // False when unavailable, faulted, or out of the sane range
        // contextual_hud.cpp also rejects (over 100000000).
        bool SafeGetValue(FnGetValue fn, void* self, int& out)
        {
            if (!fn || !self)
                return false;
            uint32_t value = 0;
            __try
            {
                value = fn(self);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            if (value > 100000000u)
                return false;
            out = static_cast<int>(value);
            return true;
        }

        void* SafeGetLocalTeam()
        {
            if (!g_FnGetTeam)
                return nullptr;
            __try
            {
                return g_FnGetTeam();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        void SafePlayClick()
        {
            SafePlaySound(kClickSound);
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

        // Copies a NUL-terminated string one byte at a time under SEH; false
        // on a fault or when it does not fit.
        bool CopyCString(uintptr_t address, char* out, size_t capacity)
        {
            if (address < 0x10000 || !out || capacity == 0)
                return false;
            __try
            {
                const char* src = reinterpret_cast<const char*>(address);
                for (size_t i = 0; i < capacity; ++i)
                {
                    out[i] = src[i];
                    if (out[i] == '\0')
                        return true;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            out[0] = '\0';
            return false;
        }

        // A copy of the object's most-derived MSVC RTTI type name
        // (CompleteObjectLocator at vtable[-1], TypeDescriptor at +0xC, name
        // at +8), read fault-safe; null when unreadable. The policy compares
        // the copy, never engine memory.
        struct RttiNameBuffer
        {
            char text[128];
        };

        const char* RttiName(void* obj, RttiNameBuffer& buffer)
        {
            const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(reinterpret_cast<uintptr_t>(obj)));
            if (!vtable)
                return nullptr;
            const uintptr_t col = reinterpret_cast<uintptr_t>(ReadPtr(vtable - sizeof(void*)));
            const uintptr_t td = col ? reinterpret_cast<uintptr_t>(ReadPtr(col + 0x0C)) : 0;
            if (!td || !CopyCString(td + 0x08, buffer.text, sizeof(buffer.text)))
                return nullptr;
            return buffer.text;
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

        struct PendingOrder
        {
            int flag = 0;      // +0xC8
            int what = 0;      // +0xCC
            uint32_t who = 0;  // +0xD0
            uint32_t path = 0; // +0xD4
        };
        static_assert(sizeof(PendingOrder) == 16, "GameObject +0xC8..+0xD7");

        bool ReadPendingOrder(void* obj, PendingOrder& out)
        {
            return obj && ReadBytes(reinterpret_cast<uintptr_t>(obj) + kPendingOrderOffset, &out, sizeof(out));
        }

        // Orders given through ExecuteMode never reach BroadcastCommand, so
        // rts_markers.cpp would draw no ping for them. One ping per pick: the
        // first own selected unit whose pending order changed and names a
        // target object.
        void PingMenuOrder(const uint32_t* handles, int n, const PendingOrder* before, const bool* haveBefore)
        {
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                PendingOrder after;
                if (!haveBefore[i] || !obj || !IsPlayerTeam(obj) || !ReadPendingOrder(obj, after))
                    continue;
                if (std::memcmp(&after, &before[i], sizeof(after)) == 0 || after.who == 0)
                    continue;
                if (void* const target = SafeGetObj(after.who))
                {
                    NotifyRtsMarkersCommand(after.what, target);
                    return;
                }
            }
        }

        // Entered in place of `call ControlPanel::DispatchMode` at 0x004A512A
        // (thiscall: ecx = panel, the chosen mode). A smart mode goes only to
        // the commandable units whose own menu holds it; skipped units count
        // as accepted, so the selection still clears as stock does. Every
        // pick (stock or smart) then gets its command ping.
        bool __fastcall DispatchHook(void* panel, void*, int mode)
        {
            if (reinterpret_cast<uintptr_t>(panel) != g_ControlPanelAddr)
                return g_FnDispatch(panel, mode);
            uint32_t handles[Policy::kSelectCapacity];
            const int n = ReadSelection(handles);
            PendingOrder before[Policy::kSelectCapacity];
            bool haveBefore[Policy::kSelectCapacity] = {};
            for (int i = 0; i < n; ++i)
                haveBefore[i] = ReadPendingOrder(SafeGetObj(handles[i]), before[i]);
            // classLabel = mru (mru_class.cpp): every pick on an MRU unit is
            // logged; an MRU entry (Drop Repair, Drop Ammo, Deploy) is
            // handled and consumed there (Deploy gives Stop, a drop is
            // queued), so the stock dispatch never sees its reused mode id.
            // True deselects, as a stock pick does.
            // Deploy acts on the selection as one: it packs only when every
            // selected MRU is deployed (the entry then reads Undeploy).
            bool anyMru = false;
            bool allDeployed = true;
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                if (!obj || !IsMruMenuObject(obj))
                    continue;
                anyMru = true;
                allDeployed = allDeployed && IsMruDeployed(obj);
            }
            const bool packAll = anyMru && allDeployed;
            bool consumed[Policy::kSelectCapacity] = {};
            uint32_t consumedHandles[Policy::kSelectCapacity];
            int consumedCount = 0;
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                if (obj && SafeCanCommand(obj) && NoteMruMenuPick(obj, handles[i], mode, packAll))
                {
                    consumed[i] = true;
                    consumedHandles[consumedCount++] = handles[i];
                }
            }
            if (consumedCount > 0)
            {
                // The MRU entries reuse stock ids (Go To Geyser, Lay Mines,
                // Drop Off): the other selected units whose own menu holds
                // the mode still get it, unit by unit.
                uint32_t sentHandles[Policy::kSelectCapacity];
                int sentCount = 0;
                for (int i = 0; i < n; ++i)
                {
                    if (consumed[i])
                        continue;
                    void* const obj = SafeGetObj(handles[i]);
                    if (!obj || !SafeCanCommand(obj))
                        continue;
                    Policy::ModeList own;
                    if (!ReadModeList(obj, own) || !Policy::UnitTakesMode(own, mode))
                        continue;
                    bool accepted = true;
                    if (SafeExecuteMode(obj, mode, accepted) && accepted)
                        sentHandles[sentCount++] = handles[i];
                }
                // An MRU pick is a plain order too: it ends any queue, so a
                // queued order cannot follow Deploy's Stop and pack the MRU.
                NoteRtsOrderQueuePlainOrder(consumedHandles, consumedCount);
                if (sentCount > 0)
                {
                    PingMenuOrder(handles, n, before, haveBefore);
                    NoteRtsOrderQueuePlainOrder(sentHandles, sentCount);
                }
                return true;
            }
            const unsigned smart = g_SmartMask.load(std::memory_order_acquire);
            if (!Policy::IsSmartMode(mode, smart))
            {
                const bool accepted = g_FnDispatch(panel, mode);
                PingMenuOrder(handles, n, before, haveBefore);
                // A unit-menu pick is a plain order: it ends any queue.
                if (accepted)
                    NoteRtsOrderQueuePlainOrder(handles, n);
                return accepted;
            }
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
            PingMenuOrder(handles, n, before, haveBefore);
            if (sent > 0)
                NoteRtsOrderQueuePlainOrder(handles, n);
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
            bool ownOrdered = false;
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                if (!obj || !SafeCanCommand(obj))
                    continue;
                Policy::ModeList own;
                if (!ReadModeList(obj, own) || !Policy::UnitTakesMode(own, Policy::kModeDefend))
                    continue;
                if (SafeSetCommandObj(obj, what, target) && IsPlayerTeam(obj))
                    ownOrdered = true;
            }
            // The stock BroadcastCommand this replaces is where rts_markers
            // pings an object order; one ping for the pick.
            if (ownOrdered)
            {
                NotifyRtsMarkersCommand(what, target);
                NoteRtsOrderQueuePlainOrder(handles, n);
            }
        }

        // ---- Build at Nav ----------------------------------------------------

        bool BuildNavPartsReady()
        {
            return g_SharedReady && g_LabelReady && g_NavSelectNoneReady && g_NavPickReady;
        }

        // Reads what PickedBuildClass needs; false when the object is gone.
        bool ReadRigPick(void* obj, Policy::RigPick& out)
        {
            out = Policy::RigPick{};
            if (!obj || g_RigVtableAddr == 0)
                return false;
            const uintptr_t base = reinterpret_cast<uintptr_t>(obj);
            const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(base));
            if (!vtable)
                return false;
            out.isRig = vtable == g_RigVtableAddr;
            if (!out.isRig)
                return true;
            uint8_t ownership = Policy::kReplicaOwnership;
            int busy = 1;
            int dropClass = 0;
            if (!ReadBytes(base + kOwnershipOffset, &ownership, sizeof(ownership)) ||
                !ReadInt(base + kRigBusyOffset, busy) || !ReadInt(base + kRigDropClassOffset, dropClass) ||
                !ReadModeList(obj, out.modes))
                return false;
            out.ownTeam = IsPlayerTeam(obj);
            out.replica = ownership == Policy::kReplicaOwnership;
            out.busy = busy;
            out.dropClass = static_cast<uint32_t>(dropClass);
            return true;
        }

        bool SelectionHasPickedRig()
        {
            uint32_t handles[Policy::kSelectCapacity];
            const int n = ReadSelection(handles);
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                Policy::RigPick pick;
                if (obj && SafeCanCommand(obj) && ReadRigPick(obj, pick) && Policy::PickedBuildClass(pick) != 0)
                    return true;
            }
            return false;
        }

        // An MRU unit in the selection (mru_class.cpp); its slots 7-9 hold
        // the reused ids ModeLabelDecide relabels.
        bool SelectionHasMruMenu()
        {
            uint32_t handles[Policy::kSelectCapacity];
            const int n = ReadSelection(handles);
            for (int i = 0; i < n; ++i)
            {
                if (IsMruMenuObject(SafeGetObj(handles[i])))
                    return true;
            }
            return false;
        }

        // Every MRU in the selection is deployed: the Deploy entry reads
        // Undeploy. A pick toggles each MRU on its own.
        bool SelectionMrusAllDeployed()
        {
            uint32_t handles[Policy::kSelectCapacity];
            const int n = ReadSelection(handles);
            int mrus = 0;
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                if (!IsMruMenuObject(obj))
                    continue;
                if (!IsMruDeployed(obj))
                    return false;
                ++mrus;
            }
            return mrus > 0;
        }

        bool SafeRigGetCommand(void* rig, const float (&pos)[3], int& result)
        {
            if (!g_FnRigGetCommand || !rig)
                return false;
            __try
            {
                result = g_FnRigGetCommand(rig, pos);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeSetCommandWhere(void* obj, int what, const float (&pos)[3], uint32_t param)
        {
            if (!g_FnNavSetCommandWhere || !obj)
                return false;
            __try
            {
                // SetCommand(what, where, param) builds the AiPath from the
                // unit to `where` itself (FUN_004dbe70 lines 26-37), so the
                // BUILD has a destination (RigProcess drops a where-less
                // BUILD, FUN_0049dc90 lines 64-74).
                g_FnNavSetCommandWhere(obj, what, pos, param, 0u);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeNavSetCommandObj(void* obj, int what, void* target)
        {
            if (!g_FnNavSetCommandObj)
                return false;
            __try
            {
                g_FnNavSetCommandObj(obj, what, target);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeNavSelectNone(void* panel)
        {
            if (!g_FnNavSelectNone)
                return false;
            __try
            {
                g_FnNavSelectNone(panel);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Entered in place of `call ControlPanel::BroadcastCommand(obj)` at
        // 0x004A4A75, the Go To Nav submenu's nav pick (CMD_GO, the nav;
        // FUN_004a08e0.c lines 1270-1271).
        // With no picked rig selected it is the stock call. Otherwise each
        // commandable selected unit is ordered as BroadcastCommand would
        // (FUN_004a7050 lines 11-13), except picked rigs: GetCommand at the
        // nav's position (validates the spot, sets the drop matrix with the
        // player's facing) and, on CMD_DROPOFF, BUILD there.
        void __fastcall NavPickHook(void* panel, void*, int what, void* nav)
        {
            g_SkipNavSelectNone = false;
            if (!g_BuildNavActive.load(std::memory_order_acquire) || what != Policy::kCmdGo || !nav ||
                reinterpret_cast<uintptr_t>(panel) != g_ControlPanelAddr)
            {
                g_FnNavBroadcastObj(panel, what, nav);
                return;
            }
            uint32_t handles[Policy::kSelectCapacity];
            const int n = ReadSelection(handles);
            uint32_t classes[Policy::kSelectCapacity] = {};
            bool enabled[Policy::kSelectCapacity] = {};
            bool anyRig = false;
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                Policy::RigPick pick;
                if (!obj || !SafeCanCommand(obj) || !ReadRigPick(obj, pick))
                    continue;
                classes[i] = Policy::PickedBuildClass(pick);
                enabled[i] = Policy::PickedSlotEnabled(pick);
                anyRig = anyRig || classes[i] != 0;
            }
            if (!anyRig)
            {
                g_FnNavBroadcastObj(panel, what, nav);
                return;
            }
            float pos[3] = {};
            const bool havePos = SafeGetPosition(nav, pos);
            int built = 0;
            int ordered = 0;
            int refused = 0;
            bool ownOrdered = false;
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                if (!obj || !SafeCanCommand(obj))
                    continue;
                if (classes[i] == 0)
                {
                    if (SafeNavSetCommandObj(obj, what, nav))
                    {
                        ++ordered;
                        ownOrdered = ownOrdered || IsPlayerTeam(obj);
                    }
                    continue;
                }
                int result = 0;
                // Our own validation call, not the reticle hover: the build
                // ghost must not record it (its matrix is the nav's).
                SuppressRtsGhostRecord(true);
                const bool queried = enabled[i] && havePos && SafeRigGetCommand(obj, pos, result);
                SuppressRtsGhostRecord(false);
                const Policy::BuildAtNavVerdict verdict =
                    Policy::DecideBuildAtNav(enabled[i], havePos, queried, result);
                if (verdict == Policy::BuildAtNavVerdict::Build &&
                    SafeSetCommandWhere(obj, Policy::kCmdBuild, pos, classes[i]))
                {
                    ++built;
                    continue;
                }
                ++refused;
                LogBudgeted(L"[RTS] Build at Nav: rig 0x%08X refused (%hs, GetCommand %d)\n", handles[i],
                            verdict == Policy::BuildAtNavVerdict::Build ? "order failed"
                                                                        : Policy::BuildAtNavVerdictName(verdict),
                            queried ? result : -1);
            }
            if (refused > 0)
                SafePlaySound(kRefuseSound);
            g_SkipNavSelectNone = Policy::KeepSelectionAfterNavPick(built, ordered, refused);
            // The stock BroadcastCommand this replaces is where rts_markers
            // pings an object order; one ping for the pick.
            if (built > 0)
                NotifyRtsMarkersCommand(Policy::kCmdBuild, nav);
            else if (ownOrdered)
                NotifyRtsMarkersCommand(what, nav);
            if (built > 0 || ordered > 0)
                NoteRtsOrderQueuePlainOrder(handles, n);
            LogBudgeted(L"[RTS] Build at Nav: %d rig(s) building, %d unit(s) sent to the nav, %d refused%hs\n", built,
                        ordered, refused, g_SkipNavSelectNone ? "; selection kept" : "");
        }

        // Entered in place of `call ControlPanel::SelectNone` at 0x004A4A80,
        // right after the nav pick above.
        void __fastcall NavPickSelectNoneHook(void* panel, void*)
        {
            if (g_SkipNavSelectNone)
            {
                g_SkipNavSelectNone = false;
                return;
            }
            SafeNavSelectNone(panel);
        }

        // ---- Hold ------------------------------------------------------------

        bool HoldHooksReady()
        {
            return g_SharedReady && g_HoldKeyReady && AiHoldHooksReady();
        }

        bool HoldAvailableNow()
        {
            return IsSinglePlayerSession() && HoldHooksReady();
        }

        // Defend(0) (GameObject::SetCommand(CMD_DEFEND): who = 0 builds the
        // SitTask, FUN_004dbce0) plus the native hold, for each selected own
        // commandable unit whose menu has Defend. Returns how many held. The
        // hold is registered first and the order only after it, so a unit
        // the native hold refuses keeps its orders (none at all when the
        // hold is unavailable).
        int HoldSelection()
        {
            if (!HoldAvailableNow())
                return 0;
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
                bool ok = false;
                try
                {
                    ok = SetAiHold(static_cast<int>(handles[i]), true);
                }
                catch (...)
                {
                    ok = false;
                }
                if (!ok)
                    continue;
                if (!SafeSetCommand(obj, Policy::kCmdDefend))
                {
                    try
                    {
                        SetAiHold(static_cast<int>(handles[i]), false);
                    }
                    catch (...)
                    {
                    }
                    continue;
                }
                ++held;
                NoteRtsOrderQueuePlainOrder(&handles[i], 1); // Hold is a plain order
            }
            return held;
        }

        // ---- Quick commands --------------------------------------------------

        bool QuickHooksReady()
        {
            return g_SharedReady && g_HoldKeyReady && g_FnSetCommandObj != nullptr && g_FnEnemyP != nullptr;
        }

        bool QuickAvailableNow()
        {
            return IsSinglePlayerSession() && QuickHooksReady();
        }

        const char* QuickName(Policy::KeyId id)
        {
            switch (id)
            {
            case Policy::KeyId::QuickFollowMe: return "follow me";
            case Policy::KeyId::QuickDefendMe: return "defend me";
            case Policy::KeyId::QuickAttackTarget: return "attack target";
            case Policy::KeyId::QuickStop: return "stop";
            default: return "?";
            }
        }

        // One quick order for the selected own units (Policy::QuickOrderFor):
        // each unit that can be commanded and, when the order names a mode,
        // holds it in its ModeList gets the stock SetCommand; the player's own
        // vehicle never does. The selection is kept. Returns the ordered count
        // and sets `refused` to the own units that could not take it.
        int QuickOrderSelection(const Policy::QuickOrder& order, void* user, void* target, int& refused)
        {
            refused = 0;
            uint32_t handles[Policy::kSelectCapacity];
            const int n = ReadSelection(handles);
            uint32_t orderedHandles[Policy::kSelectCapacity];
            int ordered = 0;
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                if (!obj || obj == user || !IsPlayerTeam(obj))
                    continue;
                if (obj == target) // a unit cannot attack or follow itself
                {
                    ++refused;
                    continue;
                }
                bool ok = SafeCanCommand(obj);
                if (ok && order.mode != Policy::kModeNone)
                {
                    Policy::ModeList own;
                    ok = ReadModeList(obj, own) && Policy::UnitTakesMode(own, order.mode);
                }
                if (ok)
                    ok = order.needsTarget ? SafeSetCommandObj(obj, order.what, target)
                                           : SafeSetCommand(obj, order.what);
                if (!ok)
                {
                    ++refused;
                    continue;
                }
                orderedHandles[ordered++] = handles[i];
            }
            if (ordered > 0)
            {
                if (order.needsTarget)
                    NotifyRtsMarkersCommand(order.what, target); // Stop gets no ping
                NoteRtsOrderQueuePlainOrder(orderedHandles, ordered);
            }
            return ordered;
        }

        void DoQuickCommand(Policy::KeyId id)
        {
            if (!QuickAvailableNow())
                return;
            const Policy::QuickOrder order = Policy::QuickOrderFor(id);
            void* const user = UserObject();
            if (order.what == 0 || !user)
                return;
            void* target = nullptr;
            if (order.onPlayer)
                target = user;
            else if (order.needsTarget)
            {
                int handle = 0;
                ReadInt(reinterpret_cast<uintptr_t>(user) + kGameObjectTargetHandleOffset, handle);
                target = handle != 0 ? SafeGetObj(static_cast<uint32_t>(handle)) : nullptr;
                // The stock attack rule (ControlPanelEnemyPAttackOrderHook): an
                // enemy, or team 0 under AllowNeutralAttackOrders; never the
                // player's own team, so an ally is refused.
                int targetTeam = -1;
                if (target && user)
                {
                    const bool teamRead =
                        ReadInt(reinterpret_cast<uintptr_t>(target) + kGameObjectActualTeamOffset, targetTeam);
                    if (!teamRead || !Policy::QuickAttackTargetAllowed(IsPlayerTeam(target), SafeEnemyP(user, target),
                                                                       targetTeam, g_AllowNeutralAttackOrders))
                        target = nullptr;
                }
            }
            int refused = 0;
            int ordered = 0;
            if (!order.needsTarget || (target && target != user))
                ordered = QuickOrderSelection(order, user, target, refused);
            if (ordered == 0)
                SafePlaySound(kRefuseSound);
            LogBudgeted(L"[RTS] quick %hs: %d unit(s) ordered, %d refused\n", QuickName(id), ordered, refused);
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
            const MruClassPolicy::Action mru = MruClassPolicy::ActionForMode(mode);
            if (mru != MruClassPolicy::Action::None && SelectionHasMruMenu())
            {
                try
                {
                    const char* text = stock;
                    switch (mru)
                    {
                    case MruClassPolicy::Action::DropRepair:
                        text = ShimText("openshim_ui:mru_drop_repair_label", "Drop Repair");
                        break;
                    case MruClassPolicy::Action::DropAmmo:
                        text = ShimText("openshim_ui:mru_drop_ammo_label", "Drop Ammo");
                        break;
                    default:
                        text = SelectionMrusAllDeployed()
                            ? ShimText("openshim_ui:mru_undeploy_label", "Undeploy")
                            : ShimText("openshim_ui:mru_deploy_label", "Deploy");
                        break;
                    }
                    return text && text[0] ? text : stock;
                }
                catch (...)
                {
                    return stock;
                }
            }
            if (mode == Policy::kModeGoToNav)
            {
                if (!Policy::ShowBuildAtNavLabel(g_BuildNavActive.load(std::memory_order_acquire), mode,
                                                 SelectionHasPickedRig()))
                    return stock;
                try
                {
                    const char* const build = ShimText("openshim_ui:rts_build_at_nav_label", "Build at Nav");
                    return build && build[0] ? build : stock;
                }
                catch (...)
                {
                    return stock;
                }
            }
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

        bool EditorActive();
        bool WorldInteractive();

        // ---- follow camera (satellite view) -----------------------------------

        bool SafeOverViewSetObject(void* obj)
        {
            if (!g_FnOverViewSetObject || !g_OverViewAddr || !obj)
                return false;
            __try
            {
                g_FnOverViewSetObject(reinterpret_cast<void*>(static_cast<uintptr_t>(g_OverViewAddr)), obj);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void StopFollow(const char* why)
        {
            if (g_FollowHandle == 0)
                return;
            LogBudgeted(L"[RTS] follow camera off (%hs) 0x%08X\n", why, g_FollowHandle);
            g_FollowHandle = 0;
        }

        // The key (gate: the option is on and the satellite view is up).
        void DoFollowKey()
        {
            void* const user = UserObject();
            uint32_t handles[Policy::kSelectCapacity];
            const int n = ReadSelection(handles);
            uint32_t firstOwn = 0;
            for (int i = 0; i < n && firstOwn == 0; ++i)
            {
                void* const obj = SafeGetObj(handles[i]);
                if (obj && obj != user && IsPlayerTeam(obj))
                    firstOwn = handles[i];
            }
            const uint32_t userHandle = user ? SafeGetHandle(user) : 0;
            const uint32_t next = Policy::FollowKeyTarget(firstOwn, userHandle, g_FollowHandle);
            if (next == 0)
            {
                StopFollow("key");
                return;
            }
            void* const obj = SafeGetObj(next);
            if (!obj || !SafeOverViewSetObject(obj))
            {
                LogBudgeted(L"[RTS] follow camera: could not centre on 0x%08X\n", next);
                return;
            }
            g_FollowHandle = next;
            LogBudgeted(L"[RTS] follow camera on 0x%08X (%hs)\n", next, next == userHandle ? "player" : "selected unit");
        }

        // Every frame while following (frameStarted drain): re-centre the
        // overview on the unit. Whether this lands before or after the stock
        // pan step is UNVERIFIED live (Docs/RTS_COMMANDS.md).
        void TickFollowCamera()
        {
            if (g_FollowHandle == 0)
                return;
            void* const obj = SafeGetObj(g_FollowHandle);
            const Policy::FollowTick tick = Policy::ClassifyFollowTick(
                g_FollowActive.load(std::memory_order_acquire), IsSatelliteOverviewActive(),
                WorldInteractive() && !EditorActive(), obj != nullptr);
            if (tick == Policy::FollowTick::Hold)
                return;
            if (tick != Policy::FollowTick::Recenter)
            {
                StopFollow(Policy::FollowTickName(tick));
                return;
            }
            if (!SafeOverViewSetObject(obj))
                StopFollow("SetObject faulted");
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
                RttiNameBuffer name;
                if (!vtable ||
                    !Policy::IsBaseStructure(VtableDerivesFrom(vtable, ".?AVBuilding@@"), RttiName(obj, name)))
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
            RttiNameBuffer name;
            if (pickedLive && IsPlayerTeam(picked) && SafeCanCommand(picked))
                family = Policy::ClassifyFamily(RttiName(picked, name));
            void* first = nullptr;
            if (selectedCount > 0)
                first = SafeGetObj(selected[0]);
            if (family == Policy::Family::None && first)
                family = Policy::ClassifyFamily(RttiName(first, name));
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
                const Policy::Family f = Policy::ClassifyFamily(RttiName(obj, name));
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

        // ---- idle units --------------------------------------------------------

        // GameObject::aiProcess (GameObject +0xFC, GetAIProcess 0x0045BDF0);
        // ScavengerProcess curState +0x1C and task +0x58; RecycleTask curState
        // +0x48 (SCAVENGER_RETARGET_RE_20261117.md sections 1 and 5).
        constexpr uintptr_t kAiProcessOffset = 0xFC;
        constexpr uintptr_t kScavProcessStateOffset = 0x1C;
        constexpr uintptr_t kScavProcessTaskOffset = 0x58;
        constexpr uintptr_t kRecycleTaskStateOffset = 0x48;

        struct ScavStateCache
        {
            uint32_t handle;
            int process;
            int recycle;
        };
        ScavStateCache g_ScavStateCache[16] = {};
        volatile LONG g_ScavStateLogBudget = 300;

        // Player-team scavengers run ScavengerFriend, AI-team ones
        // ScavengerEnemy; both derive from ScavengerProcess and add no fields
        // (1.5 decomp: their constructors only swap the vtable).
        bool IsScavengerProcessName(const char* name)
        {
            return std::strcmp(name, ".?AVScavengerFriend@@") == 0 ||
                   std::strcmp(name, ".?AVScavengerEnemy@@") == 0 ||
                   std::strcmp(name, ".?AVScavengerProcess@@") == 0;
        }

        // True while a scavenger's AI process is working on scrap. Logs each
        // change of (process state, recycle state) per scavenger.
        bool ScavengerBusy(void* obj, uint32_t handle)
        {
            int processState = -1;
            int recycleState = -1;
            bool recycleTask = false;
            void* const process = ReadPtr(reinterpret_cast<uintptr_t>(obj) + kAiProcessOffset);
            RttiNameBuffer name;
            const char* processName = process ? RttiName(process, name) : nullptr;
            if (processName && IsScavengerProcessName(processName) &&
                ReadInt(reinterpret_cast<uintptr_t>(process) + kScavProcessStateOffset, processState))
            {
                void* const task = ReadPtr(reinterpret_cast<uintptr_t>(process) + kScavProcessTaskOffset);
                RttiNameBuffer taskName;
                const char* taskRtti = task ? RttiName(task, taskName) : nullptr;
                recycleTask = taskRtti && std::strcmp(taskRtti, ".?AVRecycleTask@@") == 0;
                if (recycleTask && !ReadInt(reinterpret_cast<uintptr_t>(task) + kRecycleTaskStateOffset, recycleState))
                    recycleTask = false;
            }
            ScavStateCache* slot = nullptr;
            for (ScavStateCache& c : g_ScavStateCache)
            {
                if (c.handle == handle)
                {
                    slot = &c;
                    break;
                }
                if (!slot && c.handle == 0)
                    slot = &c;
            }
            if (!slot)
                slot = &g_ScavStateCache[handle % 16];
            if ((slot->handle != handle || slot->process != processState || slot->recycle != recycleState) &&
                InterlockedDecrement(&g_ScavStateLogBudget) >= 0)
                Log(L"[RTS] scav state handle=0x%08X process=%hs/%d recycle=%d\n", handle,
                    processName ? processName : "?", processState, recycleState);
            *slot = { handle, processState, recycleState };
            return Policy::ScavengerGathering(processState, recycleTask, recycleState);
        }

        // The eligibility the idle features and the ammo alert share.
        // False unless it is an alive (in the object list snapshot), own,
        // commandable unit of a known family (so never a building), and not
        // the player's own piloted object (as DoAreaSelect skips it).
        bool EvaluateOwnUnit(void* obj, void* user, uint32_t& handle, Policy::Family& family)
        {
            if (!obj || obj == user || !IsPlayerTeam(obj))
                return false;
            RttiNameBuffer name;
            family = Policy::ClassifyFamily(RttiName(obj, name));
            if (!Policy::IdleTracksFamily(family) || !SafeCanCommand(obj))
                return false;
            handle = SafeGetHandle(obj);
            return handle != 0;
        }

        // The idle state of an EvaluateOwnUnit unit.
        bool ReadIdleState(void* obj, uint32_t handle, Policy::Family family, bool& idle, int& current, int& pending)
        {
            const uintptr_t base = reinterpret_cast<uintptr_t>(obj);
            if (!ReadInt(base + RtsPlacement::kCurrentRecordOffset + RtsPlacement::kRecordWhatOffset, current) ||
                !ReadInt(base + RtsPlacement::kPendingRecordOffset + RtsPlacement::kRecordWhatOffset, pending))
                return false;
            idle = Policy::IsIdle(current, pending);
            if (idle && family == Policy::Family::Scavenger && ScavengerBusy(obj, handle))
                idle = false;
            return true;
        }

        // Reads one object for the idle features (EvaluateOwnUnit, then its
        // idle state).
        bool EvaluateIdleUnit(void* obj, void* user, uint32_t& handle, bool& idle, int& current, int& pending,
                              Policy::Family& family)
        {
            return EvaluateOwnUnit(obj, user, handle, family) &&
                   ReadIdleState(obj, handle, family, idle, current, pending);
        }

        // The first letter of the player's current object's ODF name (BZP
        // GetNation), through engine_flames.cpp's TryGetCraftOdfName; '\0'
        // when unreadable (the policy then picks the American clip).
        char PlayerNation(void* user)
        {
            char odf[16] = {};
            return user && TryGetCraftOdfName(user, odf, sizeof(odf)) ? odf[0] : '\0';
        }

        void DoIdleSelect(bool all)
        {
            void* const panel = reinterpret_cast<void*>(g_ControlPanelAddr);
            void* const user = UserObject();
            static uint32_t idleHandles[Policy::kIdleTrackCapacity];
            int idleCount = 0;
            const size_t n = SnapshotObjects(g_ObjectScratch, kMaxObjects);
            for (size_t i = 0; i < n && idleCount < Policy::kIdleTrackCapacity; ++i)
            {
                uint32_t handle = 0;
                bool idle = false;
                int current = 0;
                int pending = 0;
                Policy::Family family = Policy::Family::None;
                if (EvaluateIdleUnit(g_ObjectScratch[i], user, handle, idle, current, pending, family) && idle)
                    idleHandles[idleCount++] = handle;
            }
            Policy::SortHandlesAscending(idleHandles, idleCount);
            uint32_t pick[Policy::kSelectCapacity];
            const int count =
                Policy::PlanIdleSelect(idleHandles, idleCount, g_LastIdlePick, all, pick, Policy::kSelectCapacity);
            int added = 0;
            if (count > 0 && SafeSelectNone(panel))
            {
                for (int i = 0; i < count; ++i)
                {
                    // Re-read: SelectAdd appends with no room check.
                    int now = 0;
                    if (!ReadInt(g_ControlPanelAddr + kSelectNumOffset, now) || now >= Policy::kSelectCapacity)
                        break;
                    void* const obj = SafeGetObj(pick[i]);
                    if (obj && SafeSelectAdd(panel, obj))
                        ++added;
                }
            }
            const uint32_t first = count > 0 ? pick[0] : 0;
            Log(L"[RTS] idle unit select n=%d picked=0x%08X shift=%d\n", idleCount, first, all ? 1 : 0);
            if (added > 0)
            {
                g_LastIdlePick = pick[count - 1];
                SafePlayClick();
            }
            else
            {
                SafePlaySound(kRefuseSound);
            }
        }

        // The scrap-full alert: the local team's scrap against its maximum
        // (Policy::ScrapFullDetector).
        void ScanScrapAlert(void* user, ULONGLONG now)
        {
            void* const team = SafeGetLocalTeam();
            int scrap = 0;
            int maxScrap = 0;
            if (!team || !SafeGetValue(g_FnGetScrap, team, scrap) || !SafeGetValue(g_FnGetMaxScrap, team, maxScrap))
                return;
            if (!g_ScrapDetector.Observe(scrap, maxScrap, now))
                return;
            SafePlaySound(Policy::ScrapFullAlertSound(PlayerNation(user)));
            if (InterlockedDecrement(&g_AlertLogBudget) >= 0)
                Log(L"[RTS] scrap full alert scrap=%d/%d\n", scrap, maxScrap);
        }

        // Every kIdleScanIntervalMs, while any of the idle, ammo-out or
        // scrap-full alerts is on: one object snapshot per pass tracks each
        // own unit's idle state (Policy::IdleTracker, kIdleAlertSound on an
        // allowed busy->idle flip) and armed units' ammo (Policy::AmmoTracker,
        // the nation's ammo clip on an allowed not-low->low flip).
        void ScanIdleAlerts()
        {
            const bool idleOn = g_IdleAlertActive.load(std::memory_order_acquire);
            const bool ammoOn = g_AmmoAlertActive.load(std::memory_order_acquire);
            const bool scrapOn = g_ScrapAlertActive.load(std::memory_order_acquire);
            if (!idleOn && !ammoOn && !scrapOn)
                return;
            const ULONGLONG now = GetTickCount64();
            if (now - g_IdleLastScanMs < kIdleScanIntervalMs)
                return;
            g_IdleLastScanMs = now;
            if (!WorldInteractive() || EditorActive())
                return;
            void* const user = UserObject();
            if (scrapOn)
                ScanScrapAlert(user, now);
            if (!idleOn && !ammoOn)
                return;
            const size_t n = SnapshotObjects(g_ObjectScratch, kMaxObjects);
            if (n == 0)
                return;
            if (idleOn)
                g_IdleTracker.BeginPass();
            if (ammoOn)
                g_AmmoTracker.BeginPass();
            for (size_t i = 0; i < n; ++i)
            {
                void* const obj = g_ObjectScratch[i];
                uint32_t handle = 0;
                Policy::Family family = Policy::Family::None;
                if (!EvaluateOwnUnit(obj, user, handle, family))
                    continue;
                bool idle = false;
                int current = 0;
                int pending = 0;
                if (idleOn && ReadIdleState(obj, handle, family, idle, current, pending))
                {
                    const Policy::IdleObservation o = g_IdleTracker.Observe(handle, idle, now);
                    if ((o.first || o.changed) && InterlockedDecrement(&g_IdleStateLogBudget) >= 0)
                        Log(L"[RTS] idle state handle=0x%08X idle=%d what=%d/%d family=%hs\n", handle,
                            idle ? 1 : 0, current, pending, Policy::FamilyName(family));
                    if (o.alert)
                    {
                        SafePlaySound(kIdleAlertSound);
                        Log(L"[RTS] idle alert handle=0x%08X what=%d/%d\n", handle, current, pending);
                    }
                }
                int ammo = 0;
                int maxAmmo = 0;
                if (ammoOn && Policy::AmmoTracksFamily(family) && SafeGetValue(g_FnGetAmmo, obj, ammo) &&
                    SafeGetValue(g_FnMaxAmmo, obj, maxAmmo))
                {
                    const Policy::AmmoObservation o = g_AmmoTracker.Observe(handle, ammo, maxAmmo, now);
                    if (o.alert)
                    {
                        SafePlaySound(Policy::AmmoAlertSound(PlayerNation(user)));
                        if (InterlockedDecrement(&g_AlertLogBudget) >= 0)
                            Log(L"[RTS] ammo alert handle=0x%08X ammo=%d/%d\n", handle, ammo, maxAmmo);
                    }
                }
            }
            if (idleOn)
                g_IdleTracker.EndPass();
            if (ammoOn)
                g_AmmoTracker.EndPass();
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
            case Policy::KeyId::QuickFollowMe:
            case Policy::KeyId::QuickDefendMe:
            case Policy::KeyId::QuickAttackTarget:
            case Policy::KeyId::QuickStop:
                return g_QuickKeyActive.load(std::memory_order_acquire) && QuickAvailableNow();
            case Policy::KeyId::IdleUnit:
                return g_IdleKeyActive.load(std::memory_order_acquire);
            case Policy::KeyId::FollowCamera:
                return g_FollowActive.load(std::memory_order_acquire) && IsSatelliteOverviewActive();
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
                    // A focused chat line or ally prompt owns the keyboard
                    // (HudVisibility::TextEditorFocused; unknown = focused).
                    gate = fresh && KeyActionActive(id) && !IsRallyKey(g_Keys[i]) && WorldInteractive() &&
                           !EditorActive() && !HudVisibility::TextEditorFocused();
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
                case Policy::KeyId::QuickFollowMe:
                case Policy::KeyId::QuickDefendMe:
                case Policy::KeyId::QuickAttackTarget:
                case Policy::KeyId::QuickStop:
                    g_PendingQuick.fetch_or(1u << i);
                    break;
                case Policy::KeyId::IdleUnit: g_PendingIdle.store(d.shift ? 2 : 1); break;
                case Policy::KeyId::FollowCamera: g_PendingFollow.store(true); break;
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
            auto keyText = [](Policy::KeyId id) { return g_KeyText[static_cast<int>(id)].c_str(); };
            Log(L"[RTS] key filters on (target %hs, building %hs, area %hs, hold %hs, idle %hs, follow Shift+%hs)\n",
                keyText(Policy::KeyId::RemoteTarget), keyText(Policy::KeyId::BuildingCycle),
                keyText(Policy::KeyId::AreaSelect), keyText(Policy::KeyId::Hold), keyText(Policy::KeyId::IdleUnit),
                keyText(Policy::KeyId::FollowCamera));
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
        // Install-time lines only; retries can hit the same refusal up to
        // kMaxInstallAttempts times, so they share a small budget of their own.
        volatile long g_InstallLogBudget = 12;

        uint32_t RedirectCall(uint32_t site, const void* target, uint32_t expectedCallee, const char* name)
        {
            uint8_t original[5] = {};
            if (!ReadBytes(site, original, sizeof(original)) || original[0] != 0xE8)
            {
                if (InterlockedDecrement(&g_InstallLogBudget) >= 0)
                    Log(L"[RTS] %hs: no call at 0x%08X; left stock\n", name, site);
                return 0;
            }
            int32_t rel = 0;
            std::memcpy(&rel, original + 1, sizeof(rel));
            const uint32_t callee = site + 5 + static_cast<uint32_t>(rel);
            if (callee != expectedCallee)
            {
                if (InterlockedDecrement(&g_InstallLogBudget) >= 0)
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
                if (InterlockedDecrement(&g_InstallLogBudget) >= 0)
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

        // Each part binds its rows once and remembers it: a redirected call
        // site no longer matches its row bytes, so a retry must not re-bind
        // it (offense_overflow.cpp InstallExtended). A retry only re-tries
        // the redirects that have not gone in yet.
        void InstallParts()
        {
#if defined(_M_IX86)
            static bool s_mergeBound = false;
            static bool s_dispatchBound = false;
            static bool s_broadcastBound = false;
            static bool s_holdMenuBound = false;
            static bool s_buildNavBound = false;
            if (!s_mergeBound)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ModeListIntersect", &g_IntersectAddr },
                    { "ControlPanelMergeModeListCall", &g_MergeRowAddr },
                };
                if (HookEngine::BindEngineRows("RTS smart menu merge", rows))
                {
                    s_mergeBound = true;
                    g_FnIntersect = reinterpret_cast<FnIntersect>(g_IntersectAddr);
                }
            }
            if (s_mergeBound && !g_MergeReady)
                g_MergeReady = RedirectCall(g_MergeRowAddr + kMergeCallOffset,
                                            reinterpret_cast<const void*>(&MergeHook), g_IntersectAddr,
                                            "ControlPanel::Render/ModeList merge (rts)") != 0;
            if (!s_dispatchBound)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ControlPanelDispatchMode", &g_DispatchAddr },
                    { "ControlPanelDispatchModeCall", &g_DispatchRowAddr },
                };
                if (HookEngine::BindEngineRows("RTS smart menu dispatch", rows))
                {
                    s_dispatchBound = true;
                    g_FnDispatch = reinterpret_cast<FnDispatchMode>(g_DispatchAddr);
                }
            }
            if (s_dispatchBound && !g_DispatchReady)
                g_DispatchReady = RedirectCall(g_DispatchRowAddr + kDispatchCallOffset,
                                               reinterpret_cast<const void*>(&DispatchHook), g_DispatchAddr,
                                               "ControlPanel::Render/DispatchMode (rts)") != 0;
            if (!s_broadcastBound)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ControlPanelBroadcastCommandObj", &g_BroadcastObjAddr },
                    { "ControlPanelDefendTargetBroadcastCall", &g_BroadcastRowAddr },
                    { "GameObjectSetCommandObj", &g_SetCommandObjAddr },
                };
                if (HookEngine::BindEngineRows("RTS smart menu Defend target", rows))
                {
                    s_broadcastBound = true;
                    g_FnBroadcastObj = reinterpret_cast<FnBroadcastObj>(g_BroadcastObjAddr);
                    g_FnSetCommandObj = reinterpret_cast<FnSetCommandObj>(g_SetCommandObjAddr);
                }
            }
            if (s_broadcastBound && !g_BroadcastReady)
                g_BroadcastReady = RedirectCall(g_BroadcastRowAddr + kBroadcastCallOffset,
                                                reinterpret_cast<const void*>(&BroadcastHook), g_BroadcastObjAddr,
                                                "ControlPanel::Render/Defend target (rts)") != 0;
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
            if (!g_FnEnemyP)
            {
                const HookEngine::EngineRow rows[] = {
                    { "GameObjectEnemyP", &g_EnemyPAddr },
                };
                if (HookEngine::BindEngineRows("RTS quick attack", rows))
                    g_FnEnemyP = reinterpret_cast<FnEnemyP>(g_EnemyPAddr);
            }
            if (g_HoldKeyReady && !s_holdMenuBound)
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
                    s_holdMenuBound = true;
                    g_PlaySoundAddr = sound;
                    g_FnPlaySound = reinterpret_cast<FnPlaySound>(sound);
                    g_FnLocalize = reinterpret_cast<FnLocalize>(g_LocalizeAddr);
                    g_FnSelectNone = reinterpret_cast<FnSelectNone>(g_SelectNoneAddr);
                    g_DefendClickResumeAddr = g_DefendClickRowAddr + kDefendClickResumeOffset;
                }
            }
            if (s_holdMenuBound)
            {
                // The label first: a click that holds without its label
                // would surprise; a label without the click is never set.
                if (!g_LabelReady)
                    g_LabelReady = RedirectCall(g_LabelRowAddr + kLabelCallOffset,
                                                reinterpret_cast<const void*>(&ModeLabelThunk), g_LocalizeAddr,
                                                "ControlPanel::Render/mode label (rts)") != 0;
                if (g_LabelReady && !g_HoldClickReady)
                    g_HoldClickReady = RedirectCall(g_DefendClickRowAddr + kDefendClickCallOffset,
                                                    reinterpret_cast<const void*>(&DefendClickThunk),
                                                    g_PlaySoundAddr, "ControlPanel::Render/Defend click (rts)") != 0;
            }
            if (!s_buildNavBound)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ControlPanelNavPickBroadcastCall", &g_NavPickRowAddr },
                    { "ControlPanelBroadcastCommandObj", &g_NavBroadcastObjAddr },
                    { "GameObjectSetCommandObj", &g_NavSetCommandObjAddr },
                    { "GameObjectSetCommandWhere", &g_NavSetCommandWhereAddr },
                    { "ControlPanelSelectNone", &g_NavSelectNoneAddr },
                    { "ConstructionRigVtable", &g_RigVtableAddr },
                    { "ConstructionRigGetCommandPos", &g_RigGetCommandAddr },
                };
                if (HookEngine::BindEngineRows("RTS Build at Nav", rows))
                {
                    if (VtableTypeNameMatches(g_RigVtableAddr, ".?AVConstructionRig@@"))
                    {
                        s_buildNavBound = true;
                        g_FnNavBroadcastObj = reinterpret_cast<FnBroadcastObj>(g_NavBroadcastObjAddr);
                        g_FnNavSetCommandObj = reinterpret_cast<FnSetCommandObj>(g_NavSetCommandObjAddr);
                        g_FnNavSetCommandWhere = reinterpret_cast<FnSetCommandWhere>(g_NavSetCommandWhereAddr);
                        g_FnNavSelectNone = reinterpret_cast<FnSelectNone>(g_NavSelectNoneAddr);
                        g_FnRigGetCommand = reinterpret_cast<FnRigGetCommand>(g_RigGetCommandAddr);
                    }
                    else
                    {
                        g_RigVtableAddr = 0;
                        LogBudgeted(L"[RTS] ConstructionRigVtable RTTI mismatch; Build at Nav not installed\n");
                    }
                }
            }
            // The label (above) is the visible half; without it the click
            // would build under a "Go To Nav" entry. SelectNone goes in
            // before the pick so a refused pick can always keep the selection.
            if (s_buildNavBound && g_LabelReady)
            {
                if (!g_NavSelectNoneReady)
                    g_NavSelectNoneReady =
                        RedirectCall(g_NavPickRowAddr + kNavPickSelectNoneOffset,
                                     reinterpret_cast<const void*>(&NavPickSelectNoneHook), g_NavSelectNoneAddr,
                                     "ControlPanel::Render/nav pick SelectNone (rts)") != 0;
                if (g_NavSelectNoneReady && !g_NavPickReady)
                    g_NavPickReady = RedirectCall(g_NavPickRowAddr + kNavPickCallOffset,
                                                  reinterpret_cast<const void*>(&NavPickHook), g_NavBroadcastObjAddr,
                                                  "ControlPanel::Render/nav pick (rts)") != 0;
            }
            if (!g_FollowReady)
            {
                // OverView_SetObject(handle) is `GetObj(handle); mov ecx,
                // <overView>; call OverView::SetObject`. Its bytes pin both
                // the global OverView (imm32 at +0x11) and the callee (E8 at
                // +0x15), which must be the separately guarded SetObject row.
                const HookEngine::EngineRow rows[] = {
                    { "OverViewSetObjectByHandle", &g_OverViewSetObjectRowAddr },
                    { "OverViewSetObject", &g_OverViewSetObjectAddr },
                };
                if (HookEngine::BindEngineRows("RTS follow camera", rows))
                {
                    uint8_t site[0x1A] = {};
                    if (ReadBytes(g_OverViewSetObjectRowAddr, site, sizeof(site)) && site[0x10] == 0xB9 &&
                        site[0x15] == 0xE8)
                    {
                        uint32_t overview = 0;
                        int32_t rel = 0;
                        std::memcpy(&overview, site + 0x11, sizeof(overview));
                        std::memcpy(&rel, site + 0x16, sizeof(rel));
                        const uint32_t callee = g_OverViewSetObjectRowAddr + 0x1A + static_cast<uint32_t>(rel);
                        if (callee == g_OverViewSetObjectAddr && overview != 0)
                        {
                            g_OverViewAddr = overview;
                            g_FnOverViewSetObject = reinterpret_cast<FnOverViewSetObject>(g_OverViewSetObjectAddr);
                            g_FollowReady = true;
                        }
                        else if (InterlockedDecrement(&g_InstallLogBudget) >= 0)
                        {
                            Log(L"[RTS] follow camera: wrapper calls 0x%08X, not 0x%08X; left stock\n", callee,
                                g_OverViewSetObjectAddr);
                        }
                    }
                }
            }
            if (!g_IdleReady)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ControlPanelSelectAdd", &g_IdleSelectAddAddr },
                    { "ControlPanelSelectNone", &g_IdleSelectNoneAddr },
                };
                const uint32_t sound = HookEngine::ResolveNamedAddress("PlayGlobalSound");
                if (sound != 0 && HookEngine::BindEngineRows("RTS idle units", rows))
                {
                    // The same engine functions the other parts bind.
                    g_FnSelectAdd = reinterpret_cast<FnSelectAdd>(g_IdleSelectAddAddr);
                    g_FnSelectNone = reinterpret_cast<FnSelectNone>(g_IdleSelectNoneAddr);
                    g_FnPlaySound = reinterpret_cast<FnPlaySound>(sound);
                    g_IdleReady = g_ObjectListGlobal != 0;
                }
            }
            // One bind attempt once the sound row and object list are known:
            // a getter row that fails its guard bytes fails every retry, and
            // each retry would cost the resolver's wait and an [ADDR] log line.
            static bool s_alertsFailLogged = false;
            if (!g_AlertsReady && !s_alertsFailLogged &&
                HookEngine::ResolveNamedAddress("PlayGlobalSound") != 0 && g_ObjectListGlobal != 0)
            {
                // Signatures as contextual_hud.cpp calls them: HudFadeGetTeam
                // cdecl, the rest thiscall with no stack arguments.
                const HookEngine::EngineRow rows[] = {
                    { "HudFadeGetAmmo", &g_AlertGetAmmoAddr },
                    { "HudFadeMaxAmmo", &g_AlertMaxAmmoAddr },
                    { "HudFadeGetTeam", &g_AlertGetTeamAddr },
                    { "HudFadeGetScrap", &g_AlertGetScrapAddr },
                    { "HudFadeGetMaxScrap", &g_AlertGetMaxScrapAddr },
                };
                const uint32_t sound = HookEngine::ResolveNamedAddress("PlayGlobalSound");
                if (sound != 0 && g_ObjectListGlobal != 0 &&
                    HookEngine::BindEngineRows("RTS ammo/scrap alerts", rows))
                {
                    g_FnGetAmmo = reinterpret_cast<FnGetValue>(g_AlertGetAmmoAddr);
                    g_FnMaxAmmo = reinterpret_cast<FnGetValue>(g_AlertMaxAmmoAddr);
                    g_FnGetTeam = reinterpret_cast<FnGetLocalTeam>(g_AlertGetTeamAddr);
                    g_FnGetScrap = reinterpret_cast<FnGetValue>(g_AlertGetScrapAddr);
                    g_FnGetMaxScrap = reinterpret_cast<FnGetValue>(g_AlertGetMaxScrapAddr);
                    g_FnPlaySound = reinterpret_cast<FnPlaySound>(sound); // the same function idle binds
                    g_AlertsReady = true;
                }
                else if (!s_alertsFailLogged)
                {
                    s_alertsFailLogged = true;
                    Log(L"[RTS] ammo/scrap alerts: getter rows did not bind; RtsAmmoAlert and RtsScrapFullAlert "
                        L"disabled\n");
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
                { "RtsBuildAtNav", BuildNavPartsReady(),
                  "Unavailable: Build at Nav did not hook on this game build (see openshim.log)." },
                { "RtsIdleUnitAlert", g_SharedReady && g_IdleReady,
                  "Unavailable: the idle unit alert did not hook on this game build (see openshim.log)." },
                { "RtsAmmoAlert", g_SharedReady && g_AlertsReady,
                  "Unavailable: the ammo alert did not hook on this game build (see openshim.log)." },
                { "RtsScrapFullAlert", g_SharedReady && g_AlertsReady,
                  "Unavailable: the scrap full alert did not hook on this game build (see openshim.log)." },
                { "RtsFollowCamera", g_SharedReady && g_FollowReady,
                  "Unavailable: Satellite Follow did not hook on this game build (see openshim.log)." },
                { "RtsQuickCommands", QuickHooksReady(),
                  "Unavailable: Quick Commands did not hook on this game build (see openshim.log)." },
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
        g_TargetEnabled = ReadBoolOption("RtsRemoteTarget", false);
        g_SmartMenuEnabled = ReadBoolOption("RtsSmartCommandMenu", false);
        g_SmartRepairEnabled = ReadBoolOption("RtsSmartRepairReload", false);
        g_AreaEnabled = ReadBoolOption("RtsAreaSelect", false);
        g_BuildNavEnabled = ReadBoolOption("RtsBuildAtNav", false);
        g_IdleAlertEnabled = ReadBoolOption("RtsIdleUnitAlert", false);
        g_AmmoAlertEnabled = ReadBoolOption("RtsAmmoAlert", false);
        g_ScrapAlertEnabled = ReadBoolOption("RtsScrapFullAlert", false);
        g_FollowEnabled = ReadBoolOption("RtsFollowCamera", false);
        g_QuickEnabled = ReadBoolOption("RtsQuickCommands", false);
        std::string hold;
        g_HoldMode = Policy::kHoldOff;
        if (TryGetUserConfigString("Gameplay", "RtsHold", hold) && !hold.empty())
            g_HoldMode = Policy::ClampHoldMode(std::atoi(hold.c_str()));
        ResolveKeysFromConfig();
        if (!g_ConfigRead)
            Log(L"[RTS] Baseline RtsRemoteTarget=%hs RtsSmartCommandMenu=%hs RtsSmartRepairReload=%hs "
                L"RtsAreaSelect=%hs RtsHold=%d RtsBuildAtNav=%hs RtsIdleUnitAlert=%hs RtsAmmoAlert=%hs "
                L"RtsScrapFullAlert=%hs RtsFollowCamera=%hs\n",
                g_TargetEnabled ? "yes" : "no", g_SmartMenuEnabled ? "yes" : "no", g_SmartRepairEnabled ? "yes" : "no",
                g_AreaEnabled ? "yes" : "no", g_HoldMode, g_BuildNavEnabled ? "yes" : "no",
                g_IdleAlertEnabled ? "yes" : "no", g_AmmoAlertEnabled ? "yes" : "no",
                g_ScrapAlertEnabled ? "yes" : "no", g_FollowEnabled ? "yes" : "no");
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
        const bool all = SmartMenuPartsReady() && g_TargetReady && g_AreaReady && HoldHooksReady() &&
                         g_HoldClickReady && g_LabelReady && BuildNavPartsReady() && g_IdleReady && g_AlertsReady &&
                         g_FollowReady;
        if (all || s_attempts >= kMaxInstallAttempts)
        {
            s_done = true;
            Log(L"[RTS] install %hs after %d attempt(s): merge %hs, dispatch %hs, Defend target %hs, target %hs, "
                L"area %hs, hold %hs, Shift+Defend click %hs, label %hs, Build at Nav %hs, idle %hs, ammo/scrap alerts %hs, "
                L"follow %hs\n",
                all ? "complete" : "gave up", s_attempts, g_MergeReady ? "yes" : "no", g_DispatchReady ? "yes" : "no",
                g_BroadcastReady ? "yes" : "no", g_TargetReady ? "yes" : "no", g_AreaReady ? "yes" : "no",
                HoldHooksReady() ? "yes" : "no", g_HoldClickReady ? "yes" : "no", g_LabelReady ? "yes" : "no",
                BuildNavPartsReady() ? "yes" : "no", g_IdleReady ? "yes" : "no", g_AlertsReady ? "yes" : "no",
                g_FollowReady ? "yes" : "no");
        }
        RefreshRtsCommandsState();
    }

    // The menu, target and area parts run in every session: they only pick
    // which selected units receive a stock order, through the stock calls.
    // Build at Nav too: it orders only local rigs, with the stock BUILD call
    // the human drop uses (multiplayer UNVERIFIED live, Docs/RTS_COMMANDS.md).
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
        g_BuildNavActive.store(g_BuildNavEnabled && BuildNavPartsReady(), std::memory_order_release);
        g_IdleKeyActive.store(g_SharedReady && g_IdleReady, std::memory_order_release);
        // A local camera move on the player's own units: no session gate.
        g_FollowActive.store(g_FollowEnabled && g_SharedReady && g_FollowReady, std::memory_order_release);
        const bool idleAlert = g_IdleAlertEnabled && g_SharedReady && g_IdleReady;
        // This runs every 250 ms from the MP gate reconcile: clear the table only
        // when the alert turns off, so an old table cannot alert later.
        if (g_IdleAlertActive.exchange(idleAlert, std::memory_order_acq_rel) && !idleAlert)
            g_IdleResetPending.store(true, std::memory_order_release);
        const bool ammoAlert = g_AmmoAlertEnabled && g_SharedReady && g_AlertsReady;
        if (g_AmmoAlertActive.exchange(ammoAlert, std::memory_order_acq_rel) && !ammoAlert)
            g_AmmoResetPending.store(true, std::memory_order_release);
        const bool scrapAlert = g_ScrapAlertEnabled && g_SharedReady && g_AlertsReady;
        if (g_ScrapAlertActive.exchange(scrapAlert, std::memory_order_acq_rel) && !scrapAlert)
            g_ScrapResetPending.store(true, std::memory_order_release);
        const bool sp = IsSinglePlayerSession();
        const bool holdKey = Policy::HoldAvailable(g_HoldMode != Policy::kHoldOff, HoldHooksReady(), sp);
        g_HoldKeyActive.store(holdKey, std::memory_order_release);
        g_QuickKeyActive.store(Policy::QuickCommandsAvailable(g_QuickEnabled, QuickHooksReady(), sp),
                               std::memory_order_release);
        // Change-only decision line: the option and the single-player gate.
        static volatile long s_quickState = -1;
        const long quickState = (g_QuickEnabled ? 1 : 0) | (sp ? 2 : 0);
        if (InterlockedExchange(&s_quickState, quickState) != quickState)
            Log(L"[RTS] quick commands enabled=%d sp=%d\n", g_QuickEnabled ? 1 : 0, sp ? 1 : 0);
        g_HoldMenuActive.store(holdKey && g_HoldMode == Policy::kHoldKeyAndShiftMenu && g_HoldClickReady &&
                                   g_LabelReady,
                               std::memory_order_release);
    }

    // Frame/game thread (beside TickOffenseOverflow, inside the world
    // render-queue hook): installs the key filters once a feature with a key
    // is on. The queued key actions change the selection, the player's
    // target and unit orders (SelectAdd calls the object's OnSelect), so they
    // run from the scene-mutation drain at frameStarted, outside the
    // traversal; only while that drain is not installed do they run here,
    // the pre-drain behaviour every other feature keeps.
    void TickRtsCommands()
    {
        const bool anyKey = g_TargetActive.load(std::memory_order_acquire) ||
                            g_AreaActive.load(std::memory_order_acquire) ||
                            g_HoldKeyActive.load(std::memory_order_acquire) ||
                            g_QuickKeyActive.load(std::memory_order_acquire) ||
                            g_IdleKeyActive.load(std::memory_order_acquire) ||
                            g_IdleAlertActive.load(std::memory_order_acquire) ||
                            g_AmmoAlertActive.load(std::memory_order_acquire) ||
                            g_ScrapAlertActive.load(std::memory_order_acquire) ||
                            g_FollowActive.load(std::memory_order_acquire);
        if (!anyKey)
            return;
        g_LastTickMs.store(GetTickCount64(), std::memory_order_relaxed);
        EnsureKeyFilters();
        if (!InsideRenderQueueHookWithDeferral())
            RunRtsCommandsPendingActions();
    }

    // RunDeferredSceneMutations (bzr_hooks.cpp), or the tick above when the
    // drain is not installed: runs the actions the key filter queued.
    void RunRtsCommandsPendingActions() noexcept
    {
        try
        {
            if (g_PendingRemoteTarget.exchange(false))
                DoRemoteTarget();
            if (g_PendingBuilding.exchange(false))
                DoBuildingCycle();
            if (const int area = g_PendingArea.exchange(0))
                DoAreaSelect(area == 2);
            if (g_PendingHold.exchange(false))
                DoHoldKey();
            if (const unsigned quick = g_PendingQuick.exchange(0))
            {
                for (int i = 0; i < Policy::kKeyCount; ++i)
                {
                    if ((quick >> i) & 1u)
                        DoQuickCommand(static_cast<Policy::KeyId>(i));
                }
            }
            if (const int idle = g_PendingIdle.exchange(0))
                DoIdleSelect(idle == 2);
            if (g_IdleResetPending.exchange(false))
            {
                g_IdleTracker.Clear();
                std::memset(g_ScavStateCache, 0, sizeof(g_ScavStateCache));
            }
            if (g_IdlePickResetPending.exchange(false))
                g_LastIdlePick = 0;
            if (g_AmmoResetPending.exchange(false))
                g_AmmoTracker.Clear();
            if (g_ScrapResetPending.exchange(false))
                g_ScrapDetector.Clear();
            if (g_FollowResetPending.exchange(false))
                g_FollowHandle = 0;
            if (g_PendingFollow.exchange(false))
                DoFollowKey();
            TickFollowCamera();
            ScanIdleAlerts();
        }
        catch (...)
        {
            LogBudgeted(L"[RTS] a queued key action threw; dropped\n");
        }
    }

    // Mission end/load: drop queued actions.
    void ResetRtsCommands()
    {
        g_PendingRemoteTarget.store(false);
        g_PendingBuilding.store(false);
        g_PendingArea.store(0);
        g_PendingHold.store(false);
        g_PendingQuick.store(0);
        g_PendingIdle.store(0);
        g_PendingFollow.store(false);
        g_FollowResetPending.store(true); // the drain thread drops the follow
        g_IdleResetPending.store(true); // the drain thread clears the table
        g_IdlePickResetPending.store(true);
        g_AmmoResetPending.store(true); // a new mission's first observation is silent
        g_ScrapResetPending.store(true);
        g_IdleStateLogBudget = 300;
        g_AlertLogBudget = 300;
        g_ScavStateLogBudget = 300;
        g_LogBudget = 48;
        RefreshRtsCommandsState();
    }

    // Game thread: the order queue's idle test (rts_order_queue.cpp), the same
    // record reads as the idle features (current and pending `what` both
    // none, select or stop).
    bool RtsCommandsUnitIdle(void* obj)
    {
        int current = 0;
        int pending = 0;
        const uintptr_t base = reinterpret_cast<uintptr_t>(obj);
        return obj &&
               ReadInt(base + RtsPlacement::kCurrentRecordOffset + RtsPlacement::kRecordWhatOffset, current) &&
               ReadInt(base + RtsPlacement::kPendingRecordOffset + RtsPlacement::kRecordWhatOffset, pending) &&
               Policy::IsIdle(current, pending);
    }

    bool RtsCommandsHelpersReady()
    {
        return g_SharedReady;
    }

    bool RtsCommandsWorldActive()
    {
        return g_SharedReady && WorldInteractive() && !EditorActive();
    }

    // Game thread (the build ghost tick): the first selected commandable
    // rig with a building picked, while Build at Nav is active.
    bool RtsBuildAtNavPickedRig(void*& rig, uint32_t& buildClass)
    {
        rig = nullptr;
        buildClass = 0;
        if (!g_BuildNavActive.load(std::memory_order_acquire))
            return false;
        uint32_t handles[Policy::kSelectCapacity];
        const int n = ReadSelection(handles);
        for (int i = 0; i < n; ++i)
        {
            void* const obj = SafeGetObj(handles[i]);
            Policy::RigPick pick;
            if (!obj || !SafeCanCommand(obj) || !ReadRigPick(obj, pick))
                continue;
            const uint32_t cls = Policy::PickedBuildClass(pick);
            if (cls != 0)
            {
                rig = obj;
                buildClass = cls;
                return true;
            }
        }
        return false;
    }

    const char* RtsCommandActionTakingChord(const QuickSaveKeyPolicy::Chord& chord)
    {
        const Policy::KeyId id =
            Policy::ActionTakingChord(g_Keys, chord.vk, chord.extended, chord.shift, chord.ctrl, chord.alt);
        return id == Policy::KeyId::Count ? nullptr : Policy::GetKeyDef(id).displayText;
    }

    const char* RtsCommandActionUsingKey(unsigned vk, bool extended)
    {
        const Policy::KeyId id = Policy::ActionUsingKey(g_Keys, vk, extended);
        return id == Policy::KeyId::Count ? nullptr : Policy::GetKeyDef(id).displayText;
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
        if (text[0] == '\0')
        {
            // Rollback of a binding that had no key (its default was taken).
            g_Keys[index] = {};
            g_KeyText[index].clear();
            g_Latch[index] = {};
            Log(L"[RTS] %hs unbound\n", Policy::GetKeyDef(id).iniKey);
            return nullptr;
        }
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
