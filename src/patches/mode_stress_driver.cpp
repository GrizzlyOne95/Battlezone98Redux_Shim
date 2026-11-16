// mode_stress_driver.cpp
// BZR Open Shim - unattended mode-transition stress driver (release
// qualification only). See include/mode_stress_driver.h.
//
// Off unless OPENSHIM_MODE_STRESS_PLAN names a plan file; then it installs
// one Ogre frame listener and, from frameEnded on the main thread, replays
// the stock shell button handlers of the exact GOG Redux 2.2.301 build:
//
//   launch (Instant Action, FUN_00789b00 at 0x00789BCA; custom campaign,
//   FUN_00790c60): queued name -> 0x00915540, current campaign string set
//   through 0x00482860, SetShellState(5), screen type 0, wrapper End(0),
//   LoadScreenPrep, wrapper Request(0x17 loading).
//
//   leave (in-game abort button FUN_00788fa0): wrapper End(0) when a screen
//   is up, SetShellState(2 QUIT), screen type 0, nMissionStatus
//   (0x0091830C) 0 so do_smain lands on the main menu.
//
//   done (main screen exit button FUN_0078c850): called with the main menu
//   screen, as the button does.
//
// "Ready" is the sim loop running: FUN_006185f0 sets 0x009183DC to 1 just
// before the frame loop and teardown FUN_00618970 clears it. Every guard row
// in scripts/patches.json must match or the driver stays off (fail closed).
//
// mp_host hosts a one-player game in this process, the way a player does it
// from the LAN screen: OpenShim's in-process no-sign-in LAN host
// ([Network] NoAuthLan=1), the LAN host selected as the server, the stock
// Click_MultiPlayer (FUN_0078c6c0) into the lobby, the lobby Create button's
// direct-create branch (FUN_0079e4f0 -> FUN_0079dab0), the map picked in the
// game room, its launch button (FUN_00795c10), then leave and the room and
// lobby Back buttons, and Stop Host. A solo launch needs Sync Join off
// (CanLaunchGame FUN_00573d00 lines 51-56); the harness turns it off. Its
// rows bind separately: without them only mp_host steps fail.

#include "mode_stress_driver.h"

#include "bzr_hooks_internal.h"
#include "bzr_string.h"
#include "game_state.h"
#include "hook_engine.h"
#include "lan_no_auth.h"
#include "lan_session.h"
#include "mode_stress_plan.h"
#include "shell_screens.h"
#include "shim_log.h"
#include "ui_performance.h"

#include <Windows.h>

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

namespace BZROpenShim
{
    // lan_screen.cpp and prelobby_screen.cpp.
    bool SelectLanHost(const std::string& endpoint, std::string& note, bool& recycled);
    bool CallStockClickMultiPlayer(void* mainScreen);

    namespace
    {
        using namespace ModeStress;

        constexpr char kComponent[] = "modestress";
        constexpr uint64_t kStartupTimeoutMs = 300000;  // first main menu
        constexpr uint64_t kMenuTimeoutMs = 120000;     // back to the menu
        constexpr uint64_t kLoadTimeoutMs = 300000;     // launch to sim loop
        constexpr uint64_t kMenuSettleMs = 2000;        // menu stable before acting
        constexpr int kRunStateQuit = 2;
        constexpr uint32_t kScreenTypeMainMenu = 0x01;
        constexpr int kScreenRequestLoading = 0x17;
        constexpr uint32_t kWrapperScreenOffset = 0x14;  // wrapper -> current screen
        constexpr uint32_t kScreenWrapperOffset = 0x138; // screen -> wrapper (stock buttons)

        using FnRootGet = void*(__cdecl*)();
        using FnRootAddFrameListener = void(__thiscall*)(void*, void*);
        using FnMainExitButton = void(__thiscall*)(void* screen);

        // mp_host
        constexpr uint64_t kMpHostStartTimeoutMs = 30000;
        constexpr uint64_t kMpNetworkTimeoutMs = 60000;  // the pre-lobby allows 45 s
        constexpr uint64_t kMpDropGraceMs = 2000;        // as the pre-lobby
        constexpr uint64_t kMpScreenTimeoutMs = 60000;
        constexpr uint64_t kMpScreenSettleMs = 1500;
        constexpr uint64_t kMpMapTimeoutMs = 15000;
        constexpr uint64_t kMpLaunchTimeoutMs = 60000;
        constexpr uint64_t kMpNavIntervalMs = 2000;
        constexpr uint32_t kLobbyObjectOffset = 0x1C4;   // FUN_0079ea90 line 112
        constexpr uint32_t kLobbyPopupOffset = 0x1C0;
        constexpr uint32_t kLobbyCreateFlag = 0x1FC;     // FUN_0079e4f0 lines 13-14
        constexpr uint32_t kLobbyCreateDirect = 0x1FD;
        constexpr uint32_t kLobbyPasswordAsked = 0x1FE;  // FUN_0079ea90 line 116 clears it
        constexpr uint32_t kLobbyStateOffset = 0x50;     // FUN_006cc050
        constexpr uint32_t kLobbyStateInRoom = 4;
        constexpr char kMpGameName[] = "ModeStress";

        using FnVoidCdecl = void(__cdecl*)();
        using FnPopupEnable = void(__thiscall*)(void* popup, uint32_t enable);
        using FnPopupReset = void(__thiscall*)(void* popup);
        using FnLobbyCreateGame = void(__thiscall*)(void* screen, BzrString name);  // ret 0x18

        enum class Phase
        {
            WaitStartupMenu,
            StepStart,
            ShellWaitMenu,
            ShellHold,
            LaunchWaitMenu,
            MpWaitMenu,
            MpWaitHost,
            MpWaitNetwork,
            MpWaitLobby,
            MpWaitRoom,
            MpWaitLaunch,
            WaitReady,
            Hold,
            Leave,
            LeaveWaitMenu,
            ExitWaitMenu,
            Finished,
            Failed,
        };

        // engine_addresses rows; all or nothing.
        uint32_t g_SimLoopRunningAddr = 0;
        uint32_t g_MissionStatusAddr = 0;
        uint32_t g_WrapperGlobalAddr = 0;
        uint32_t g_ScreenTypeAddr = 0;
        uint32_t g_OldMissionModeAddr = 0;
        uint32_t g_MainExitButtonAddr = 0;
        uint32_t g_GuardSimLoopSet = 0;
        uint32_t g_GuardAbortButton = 0;
        uint32_t g_GuardIaLaunch = 0;
        uint32_t g_GuardCampaignLaunch = 0;

        // mp_host rows; bound on their own (all or nothing).
        uint32_t g_LobbySlotAddr = 0;
        uint32_t g_RoomSlotAddr = 0;
        uint32_t g_GuardLobbyState = 0;
        uint32_t g_GuardLobbyCreate = 0;
        uint32_t g_LobbyCreateGameAddr = 0;
        uint32_t g_PopupEnableAddr = 0;
        uint32_t g_PopupResetAddr = 0;
        uint32_t g_RoomLaunchAddr = 0;
        uint32_t g_RoomBackAddr = 0;
        uint32_t g_LobbyBackAddr = 0;
        bool g_MpRowsBound = false;

        // mp_host state
        bool g_MpHostStarted = false;
        bool g_MpAwaitDrop = false;
        bool g_MpMapSelected = false;
        uint64_t g_MpSinceMs = 0;    // the current screen/condition first seen
        uint64_t g_MpLastNavMs = 0;  // last map attempt or Back press (throttle)

        std::atomic<bool> g_Enabled{false};
        std::atomic<bool> g_Shutdown{false};
        bool g_ListenerInstalled = false;
        bool g_ListenerWarned = false;

        std::vector<Step> g_Steps;  // the plan expanded by its loop count
        size_t g_Index = 0;
        Phase g_Phase = Phase::WaitStartupMenu;
        uint64_t g_PhaseStartMs = 0;
        uint64_t g_MenuSinceMs = 0;
        uint64_t g_ReadyMs = 0;

        uint64_t NowMs() { return GetTickCount64(); }

        void SetPhase(Phase phase)
        {
            g_Phase = phase;
            g_PhaseStartMs = NowMs();
        }

        bool BindRows()
        {
            const HookEngine::EngineRow rows[] = {
                { "SimLoopRunning", &g_SimLoopRunningAddr },
                { "MissionStatus", &g_MissionStatusAddr },
                { "UiPerfShellWrapperGlobal", &g_WrapperGlobalAddr },
                { "UiCurrentScreenType", &g_ScreenTypeAddr },
                { "OldMissionMode", &g_OldMissionModeAddr },
                { "MainScreenExitButton", &g_MainExitButtonAddr },
                { "ModeStressSimLoopSet", &g_GuardSimLoopSet },
                { "ModeStressAbortButton", &g_GuardAbortButton },
                { "ModeStressIaLaunchSequence", &g_GuardIaLaunch },
                { "ModeStressCampaignLaunch", &g_GuardCampaignLaunch },
            };
            return HookEngine::BindEngineRows("Mode stress driver", rows) &&
                   Hooks::QueuedLoadNameBufferAddr() != 0;
        }

        bool BindMpRows()
        {
            const HookEngine::EngineRow rows[] = {
                { "ModeStressLobbyScreenSlot", &g_LobbySlotAddr },
                { "MultiCreateScreenSlot", &g_RoomSlotAddr },
                { "ModeStressLobbyState", &g_GuardLobbyState },
                { "ModeStressLobbyCreateButton", &g_GuardLobbyCreate },
                { "ModeStressLobbyCreateGame", &g_LobbyCreateGameAddr },
                { "ModeStressPopupEnable", &g_PopupEnableAddr },
                { "ModeStressPopupReset", &g_PopupResetAddr },
                { "ModeStressRoomLaunchButton", &g_RoomLaunchAddr },
                { "ModeStressRoomBackButton", &g_RoomBackAddr },
                { "ModeStressLobbyBackButton", &g_LobbyBackAddr },
            };
            return HookEngine::BindEngineRows("Mode stress driver (mp_host)", rows);
        }

        const char* MissingEngineFunction()
        {
            if (!g_BzrFn_SetShellState) return "SetShellState";
            if (!g_BzrFn_UiDialogSetEnabled) return "UiDialogSetEnabled";
            if (!g_BzrFn_UiDialogAdvance) return "ShellRequest";
            if (!g_BzrFn_LoadScreenPrep) return "LoadScreenPrep";
            if (!g_BzrFn_BzrStringCtorFromCStr) return "BzrStringCtorFromCStr";
            if (!g_BzrFn_BzrStringDtor) return "BzrStringDtor";
            if (!g_BzrFn_LoadScreenClearSelection) return "LoadScreenClearSelection";
            return nullptr;
        }

        // --- Engine reads and calls (POD only, SEH guarded) -------------------
        struct Snapshot
        {
            bool readable = false;
            int runState = Hooks::kBzrRunStateUnknown;
            uint32_t simLoop = 0;
            uint32_t screenType = 0;
            void* wrapper = nullptr;
            void* screen = nullptr;
            bool screenOwnedByWrapper = false;
        };

        Snapshot ReadSnapshot()
        {
            Snapshot s;
            int run = Hooks::kBzrRunStateUnknown;
            if (!Hooks::TryReadBzrRunState(run))
                return s;
            s.runState = run;
            __try
            {
                s.simLoop = *reinterpret_cast<const volatile uint32_t*>(g_SimLoopRunningAddr);
                s.screenType = *reinterpret_cast<const volatile uint32_t*>(g_ScreenTypeAddr);
                s.wrapper = *reinterpret_cast<void* const volatile*>(g_WrapperGlobalAddr);
                if (s.wrapper)
                {
                    s.screen = *reinterpret_cast<void* const volatile*>(
                        static_cast<uint8_t*>(s.wrapper) + kWrapperScreenOffset);
                    if (s.screen)
                        s.screenOwnedByWrapper = *reinterpret_cast<void* const volatile*>(
                            static_cast<uint8_t*>(s.screen) + kScreenWrapperOffset) == s.wrapper;
                    // UiCurrentScreenType is the shell loop's entry type. After
                    // a multiplayer game the loop enters at the lobby (0xE,
                    // FUN_005d42e0 lines 113-115, 131-134) and the lobby's Back
                    // pops the history to the main menu (FUN_0079dd60 ->
                    // FUN_007c79a0) without changing it, so prefer the id the
                    // screen factory built the current screen with.
                    if (const uint32_t built = ShellScreens::BuiltScreenId(s.screen))
                        s.screenType = built;
                }
                s.readable = true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                s = Snapshot{};
            }
            return s;
        }

        bool AtMainMenu(const Snapshot& s)
        {
            const ShellUiState ui = ReadShellUiState();
            return s.readable && ui.readable && ui.wrapperActive &&
                   s.runState != Hooks::kBzrRunStateStarted && s.simLoop == 0 &&
                   s.screenType == kScreenTypeMainMenu && s.screen && s.screenOwnedByWrapper;
        }

        // The main menu has to stay up kMenuSettleMs before the driver acts on it.
        bool MenuSettled(const Snapshot& s)
        {
            if (!AtMainMenu(s))
            {
                g_MenuSinceMs = 0;
                return false;
            }
            const uint64_t now = NowMs();
            if (!g_MenuSinceMs)
                g_MenuSinceMs = now;
            return now - g_MenuSinceMs >= kMenuSettleMs;
        }

        bool SetCampaign(const char* campaign)
        {
            BzrString text = {};
            __try
            {
                g_BzrFn_BzrStringCtorFromCStr(&text, campaign);
                g_BzrFn_LoadScreenClearSelection(&text);  // 0x00482860: assign 0x0094FEE0
                g_BzrFn_BzrStringDtor(&text);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool CallLaunch(void* wrapper)
        {
            __try
            {
                g_BzrFn_SetShellState(Hooks::kBzrRunStateStarted);
                *reinterpret_cast<volatile uint32_t*>(g_ScreenTypeAddr) = 0;
                g_BzrFn_UiDialogSetEnabled(wrapper, 0);
                g_BzrFn_LoadScreenPrep();
                g_BzrFn_UiDialogAdvance(wrapper, kScreenRequestLoading);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool CallLeave(void* wrapperOrNull)
        {
            __try
            {
                if (wrapperOrNull)
                    g_BzrFn_UiDialogSetEnabled(wrapperOrNull, 0);
                g_BzrFn_SetShellState(kRunStateQuit);
                *reinterpret_cast<volatile uint32_t*>(g_ScreenTypeAddr) = 0;
                *reinterpret_cast<volatile uint32_t*>(g_MissionStatusAddr) = 0;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool CallExit(void* screen)
        {
            __try
            {
                reinterpret_cast<FnMainExitButton>(static_cast<uintptr_t>(g_MainExitButtonAddr))(screen);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool WriteQueuedName(const char* bzn)
        {
            auto* queued = reinterpret_cast<char*>(Hooks::QueuedLoadNameBufferAddr());
            if (!queued)
                return false;
            __try
            {
                return strncpy_s(queued, Hooks::kQueuedLoadNameBufferLen, bzn, _TRUNCATE) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // --- mp_host engine reads and calls (POD only, SEH guarded) --------------
        // A stock shell screen held in `slotAddr`, when it is the wrapper's.
        uint8_t* LiveSlotScreen(uint32_t slotAddr, const Snapshot& s)
        {
            if (!slotAddr || !s.wrapper)
                return nullptr;
            __try
            {
                uint8_t* screen = *reinterpret_cast<uint8_t* const volatile*>(slotAddr);
                if (screen && *reinterpret_cast<void* const volatile*>(screen + kScreenWrapperOffset) == s.wrapper)
                    return screen;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return nullptr;
        }

        bool SlotSet(uint32_t slotAddr)
        {
            __try
            {
                return slotAddr && *reinterpret_cast<void* const volatile*>(slotAddr) != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // FUN_006cc050 on the lobby screen's lobby object; -1 when unreadable.
        int LobbyState(uint8_t* lobbyScreen)
        {
            __try
            {
                const uint8_t* lobby = *reinterpret_cast<uint8_t* const*>(lobbyScreen + kLobbyObjectOffset);
                if (!lobby)
                    return -1;
                return *reinterpret_cast<const volatile int*>(lobby + kLobbyStateOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1;
            }
        }

        // The lobby Create button's direct-create branch (FUN_0079e4f0 lines
        // 11-27) with the driver's game name instead of the profile name.
        // 0 sent, 1 refused (state), 2 faulted.
        int CallLobbyCreate(uint8_t* lobbyScreen)
        {
            __try
            {
                if (LobbyState(lobbyScreen) != static_cast<int>(kLobbyStateInRoom) ||
                    lobbyScreen[kLobbyPasswordAsked] != 0)
                    return 1;
                void* popup = *reinterpret_cast<void**>(lobbyScreen + kLobbyPopupOffset);
                if (!popup)
                    return 1;
                lobbyScreen[kLobbyCreateFlag] = 1;
                lobbyScreen[kLobbyCreateDirect] = 1;
                reinterpret_cast<FnPopupEnable>(static_cast<uintptr_t>(g_PopupEnableAddr))(popup, 1);
                reinterpret_cast<FnPopupReset>(static_cast<uintptr_t>(g_PopupResetAddr))(popup);
                BzrString name = {};
                g_BzrFn_BzrStringCtorFromCStr(&name, kMpGameName);
                // By value: the callee owns and destroys the copy (ret 0x18).
                reinterpret_cast<FnLobbyCreateGame>(static_cast<uintptr_t>(g_LobbyCreateGameAddr))(lobbyScreen, name);
                return 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 2;
            }
        }

        bool CallButton(uint32_t addr)
        {
            __try
            {
                reinterpret_cast<FnVoidCdecl>(static_cast<uintptr_t>(addr))();
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool CallClickMultiPlayer(void* mainScreen)
        {
            __try
            {
                return CallStockClickMultiPlayer(mainScreen);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        std::wstring GameRoot()
        {
            wchar_t path[32768] = {};
            const DWORD size = GetModuleFileNameW(nullptr, path, static_cast<DWORD>(std::size(path)));
            return size && size < std::size(path) ? std::filesystem::path(path).parent_path().wstring() : L"";
        }

        // What the stock readiness gate (0x00764870) answers. With NoAuthLan on,
        // LAN no-auth detours that gate (lan_no_auth.cpp LocalReady), so the
        // IsNetworkInit row no longer matches its bytes and QueryStockIsNetworkInit
        // reports -1; ask the detour's own answer instead.
        int NetworkReady()
        {
            if (LanNoAuth::Requested()) return LanNoAuth::Ready() ? 1 : 0;
            return QueryStockIsNetworkInit();
        }

        // The LAN and pre-lobby screens pump these from their ticks; mp_host
        // drives the shell without them, so it pumps them itself.
        void PumpLan()
        {
            if (ShellScreens::LiveScreen(ShellScreens::kLanScreenId) ||
                ShellScreens::LiveScreen(ShellScreens::kPreLobbyScreenId))
                return;
            LanNoAuth::PumpMainThread();
            LanSession::Tick();
        }

        void StopMpHost()
        {
            if (!g_MpHostStarted)
                return;
            g_MpHostStarted = false;
            LanSession::StopHost();
            LogShimA(LogLevel::Info, kComponent, "[MODESTRESS] mp_host LAN host stopped");
        }

        // --- Logging ------------------------------------------------------------
        const char* StepArg(const Step& step) { return step.arg.empty() ? "-" : step.arg.c_str(); }

        void LogStep(const char* what, const Snapshot& s, const char* extra = "")
        {
            const Step& step = g_Steps[g_Index];
            LogShimA(LogLevel::Info, kComponent, "[MODESTRESS] step %u/%u %s %s %s run=%d screen=%u sim=%u%s%s",
                     static_cast<unsigned>(g_Index + 1), static_cast<unsigned>(g_Steps.size()),
                     KindName(step.kind), StepArg(step), what, s.runState, s.screenType, s.simLoop,
                     extra[0] ? " " : "", extra);
        }

        void Fail(const char* reason, const Snapshot& s)
        {
            if (g_Index < g_Steps.size())
            {
                const Step& step = g_Steps[g_Index];
                // Every mp_host failure is named "mp_host:<stage>".
                const char* prefix =
                    step.kind == StepKind::MpHost && std::strncmp(reason, "mp_host:", 8) != 0 ? "mp_host:" : "";
                LogShimA(LogLevel::Error, kComponent,
                         "[MODESTRESS] FAIL %s%s step=%u/%u kind=%s arg=%s run=%d screen=%u sim=%u",
                         prefix, reason, static_cast<unsigned>(g_Index + 1), static_cast<unsigned>(g_Steps.size()),
                         KindName(step.kind), StepArg(step), s.runState, s.screenType, s.simLoop);
            }
            else
            {
                LogShimA(LogLevel::Error, kComponent, "[MODESTRESS] FAIL %s run=%d screen=%u sim=%u", reason,
                         s.runState, s.screenType, s.simLoop);
            }
            LogShimA(LogLevel::Info, kComponent, "[MODESTRESS] plan stopped; the harness closes the game");
            StopMpHost();
            SetPhase(Phase::Failed);
        }

        bool PhaseTimedOut(uint64_t limitMs) { return NowMs() - g_PhaseStartMs >= limitMs; }

        // --- Step actions -----------------------------------------------------
        void Launch(const Step& step, const Snapshot& s)
        {
            if (!WriteQueuedName(step.arg.c_str()))
                return Fail("launch: queued name write failed", s);
            const char* campaign = nullptr;
            if (step.kind == StepKind::InstantAction)
                campaign = "instant_action";  // FUN_00789b00 sets this literal
            else if (!step.campaign.empty())
                campaign = step.campaign.c_str();
            if (campaign && !SetCampaign(campaign))
                return Fail("launch: campaign set faulted", s);
            if (step.kind == StepKind::Mission)
            {
                // FUN_00790c60 (custom campaign launch) sets the mission mode to 1.
                *reinterpret_cast<volatile uint32_t*>(g_OldMissionModeAddr) = 1;
            }
            if (UiPerf::IsEnabled())
                UiPerf::NotifyShellRequest(kScreenRequestLoading);
            if (!CallLaunch(s.wrapper))
                return Fail("launch: engine call faulted", s);
            LogStep("launched", s);
            SetPhase(Phase::WaitReady);
        }

        // Abort-button semantics (FUN_00788fa0), also used when the mission
        // ended by itself and its success/failure screen is up.
        bool TryLeave(const Snapshot& s)
        {
            void* wrapper = nullptr;
            if (s.screenType != 0 && s.screenType != kScreenTypeMainMenu)
            {
                if (!s.screen || !s.screenOwnedByWrapper)
                    return false;  // a screen is being built; retry next frame
                wrapper = s.wrapper;
            }
            else if (s.runState != Hooks::kBzrRunStateStarted)
            {
                // Mission over, result screen not up yet (or already at the menu).
                return false;
            }
            if (!CallLeave(wrapper))
            {
                Fail("leave: engine call faulted", s);
                return true;
            }
            LogStep("leave-requested", s);
            return true;
        }

        void NextStep()
        {
            ++g_Index;
            g_MenuSinceMs = 0;
            SetPhase(g_Index < g_Steps.size() ? Phase::StepStart : Phase::ExitWaitMenu);
            if (g_Index >= g_Steps.size())
                LogShimA(LogLevel::Info, kComponent, "[MODESTRESS] done steps=%u",
                         static_cast<unsigned>(g_Steps.size()));
        }

        void Tick()
        {
            const Snapshot s = ReadSnapshot();
            switch (g_Phase)
            {
            case Phase::WaitStartupMenu:
                if (MenuSettled(s))
                {
                    if (const char* missing = MissingEngineFunction())
                    {
                        char reason[96];
                        std::snprintf(reason, sizeof(reason), "engine function %s not bound", missing);
                        return Fail(reason, s);
                    }
                    LogShimA(LogLevel::Info, kComponent, "[MODESTRESS] main menu reached; starting %u steps",
                             static_cast<unsigned>(g_Steps.size()));
                    SetPhase(Phase::StepStart);
                }
                else if (PhaseTimedOut(kStartupTimeoutMs))
                {
                    Fail("main menu not reached after startup", s);
                }
                return;

            case Phase::StepStart:
            {
                const Step& step = g_Steps[g_Index];
                LogStep("begin", s);
                switch (step.kind)
                {
                case StepKind::Shell:
                    SetPhase(Phase::ShellWaitMenu);
                    break;
                case StepKind::Mission:
                case StepKind::InstantAction:
                    SetPhase(Phase::LaunchWaitMenu);
                    break;
                case StepKind::MpHost:
                    if (!g_MpRowsBound)
                        return Fail("mp_host:rows engine rows did not bind", s);
                    if (!LanNoAuth::Enabled())
                        return Fail("mp_host:no-auth-lan [Network] NoAuthLan is off", s);
                    g_MpAwaitDrop = false;
                    g_MpMapSelected = false;
                    g_MpSinceMs = 0;
                    SetPhase(Phase::MpWaitMenu);
                    break;
                }
                return;
            }

            case Phase::MpWaitMenu:
                if (MenuSettled(s))
                {
                    const auto before = LanSession::Status();
                    if (before.state != LanSession::HostState::Stopped && before.state != LanSession::HostState::Failed)
                        return Fail("mp_host:host-start a LAN host is already running", s);
                    if (!LanSession::StartHost(GameRoot(), true))
                        return Fail("mp_host:host-start StartHost refused", s);
                    g_MpHostStarted = true;
                    LogStep("host-starting", s);
                    SetPhase(Phase::MpWaitHost);
                }
                else if (PhaseTimedOut(kMenuTimeoutMs))
                {
                    Fail("mp_host:menu main menu not reached", s);
                }
                return;

            case Phase::MpWaitHost:
            {
                PumpLan();
                const auto status = LanSession::Status();
                if (status.state == LanSession::HostState::Running)
                {
                    std::string note;
                    bool recycled = false;
                    if (!SelectLanHost(status.hostAddress, note, recycled))
                    {
                        LogShimA(LogLevel::Error, kComponent, "[MODESTRESS] mp_host select refused: %s", note.c_str());
                        return Fail("mp_host:select the LAN host was not accepted as the server", s);
                    }
                    if (!recycled && NetworkReady() > 0)
                        return Fail("mp_host:select network is up on another server and no socket was recycled", s);
                    g_MpAwaitDrop = recycled;
                    char extra[96];
                    std::snprintf(extra, sizeof(extra), "host=%s recycled=%d", status.hostAddress.c_str(),
                                  recycled ? 1 : 0);
                    LogStep("host-running", s, extra);
                    SetPhase(Phase::MpWaitNetwork);
                }
                else if (status.state == LanSession::HostState::Failed || status.state == LanSession::HostState::Stopped)
                {
                    LogShimA(LogLevel::Error, kComponent, "[MODESTRESS] mp_host host: %s", status.hostMessage.c_str());
                    Fail("mp_host:host-start the LAN host did not start", s);
                }
                else if (PhaseTimedOut(kMpHostStartTimeoutMs))
                {
                    Fail("mp_host:host-start the LAN host is not running after 30 s", s);
                }
                return;
            }

            case Phase::MpWaitNetwork:
            {
                PumpLan();
                if (!AtMainMenu(s))
                    return Fail("mp_host:network left the main menu unexpectedly", s);
                const int ready = NetworkReady();
                if (g_MpAwaitDrop && (ready == 0 || NowMs() - g_PhaseStartMs >= kMpDropGraceMs))
                    g_MpAwaitDrop = false;
                if (!g_MpAwaitDrop && ready > 0)
                {
                    if (!CallClickMultiPlayer(s.screen))
                        return Fail("mp_host:lobby stock Click_MultiPlayer unavailable (pre-lobby click hook)", s);
                    LogStep("multiplayer-clicked", s);
                    g_MpSinceMs = 0;
                    SetPhase(Phase::MpWaitLobby);
                }
                else if (PhaseTimedOut(kMpNetworkTimeoutMs))
                {
                    char reason[96];
                    std::snprintf(reason, sizeof(reason), "mp_host:network isNetworkInit=%d after 60 s", ready);
                    Fail(reason, s);
                }
                return;
            }

            case Phase::MpWaitLobby:
            {
                PumpLan();
                uint8_t* lobby = LiveSlotScreen(g_LobbySlotAddr, s);
                const int state = lobby ? LobbyState(lobby) : -1;
                if (lobby && state == static_cast<int>(kLobbyStateInRoom))
                {
                    const uint64_t now = NowMs();
                    if (!g_MpSinceMs)
                        g_MpSinceMs = now;
                    if (now - g_MpSinceMs < kMpScreenSettleMs)
                        return;
                    const int sent = CallLobbyCreate(lobby);
                    if (sent == 2)
                        return Fail("mp_host:create lobby create faulted", s);
                    if (sent == 0)
                    {
                        LogStep("create-sent", s);
                        g_MpSinceMs = 0;
                        SetPhase(Phase::MpWaitRoom);
                    }
                    return;
                }
                g_MpSinceMs = 0;
                if (PhaseTimedOut(kMpScreenTimeoutMs))
                {
                    char reason[96];
                    std::snprintf(reason, sizeof(reason), "mp_host:lobby lobby screen=%d state=%d after 60 s",
                                  lobby ? 1 : 0, state);
                    Fail(reason, s);
                }
                return;
            }

            case Phase::MpWaitRoom:
            {
                PumpLan();
                if (!LiveSlotScreen(g_RoomSlotAddr, s))
                {
                    g_MpSinceMs = 0;
                    if (PhaseTimedOut(kMpScreenTimeoutMs))
                        Fail("mp_host:create the game room did not open after 60 s", s);
                    return;
                }
                const uint64_t now = NowMs();
                if (!g_MpSinceMs)
                    g_MpSinceMs = now;
                if (now - g_MpSinceMs < kMpScreenSettleMs)
                    return;
                // Each attempt re-runs the room's map-list refresh, so retry
                // at the navigation interval, not every frame.
                if (g_MpLastNavMs && now - g_MpLastNavMs < kMpNavIntervalMs)
                    return;
                g_MpLastNavMs = now;
                const Step& step = g_Steps[g_Index];
                char selected[260] = {};
                if (!Hooks::SelectCreateScreenMapByFile(step.arg.c_str(), selected, sizeof(selected)) ||
                    _stricmp(selected, step.arg.c_str()) != 0)
                {
                    if (now - g_MpSinceMs >= kMpScreenSettleMs + kMpMapTimeoutMs)
                    {
                        LogShimA(LogLevel::Error, kComponent, "[MODESTRESS] mp_host map wanted=%s selected=%s",
                                 step.arg.c_str(), selected[0] ? selected : "-");
                        Fail("mp_host:map the map could not be selected in the game room", s);
                    }
                    return;
                }
                g_MpMapSelected = true;
                char extra[300];
                std::snprintf(extra, sizeof(extra), "map=%s", selected);
                LogStep("map-selected", s, extra);
                if (!CallButton(g_RoomLaunchAddr))
                    return Fail("mp_host:launch room launch button faulted", s);
                LogStep("launch-pressed", s);
                SetPhase(Phase::MpWaitLaunch);
                return;
            }

            case Phase::MpWaitLaunch:
                PumpLan();
                if (s.runState == Hooks::kBzrRunStateStarted)
                {
                    LogStep("launched", s);
                    SetPhase(Phase::WaitReady);
                }
                else if (PhaseTimedOut(kMpLaunchTimeoutMs))
                {
                    Fail("mp_host:launch the game did not start 60 s after the launch button (CanLaunchGame)", s);
                }
                return;

            case Phase::ShellWaitMenu:
                if (MenuSettled(s))
                {
                    LogStep("ready", s);
                    SetPhase(Phase::ShellHold);
                }
                else if (PhaseTimedOut(kMenuTimeoutMs))
                {
                    Fail("shell: main menu not reached", s);
                }
                return;

            case Phase::ShellHold:
                if (!AtMainMenu(s))
                    return Fail("shell: left the main menu unexpectedly", s);
                if (PhaseTimedOut(static_cast<uint64_t>(g_Steps[g_Index].seconds) * 1000))
                {
                    LogStep("end", s);
                    NextStep();
                }
                return;

            case Phase::LaunchWaitMenu:
                if (MenuSettled(s))
                    Launch(g_Steps[g_Index], s);
                else if (PhaseTimedOut(kMenuTimeoutMs))
                    Fail("launch: main menu not reached", s);
                return;

            case Phase::WaitReady:
                if (s.runState == Hooks::kBzrRunStateStarted && s.simLoop == 1)
                {
                    g_ReadyMs = NowMs();
                    LogStep("ready", s);
                    SetPhase(Phase::Hold);
                }
                else if (s.runState != Hooks::kBzrRunStateStarted && s.runState != Hooks::kBzrRunStateUnknown)
                {
                    Fail("load: run state left STARTED before the sim loop ran", s);
                }
                else if (PhaseTimedOut(kLoadTimeoutMs))
                {
                    Fail("load: sim loop not running after the load timeout", s);
                }
                return;

            case Phase::Hold:
                if (s.runState != Hooks::kBzrRunStateStarted || s.simLoop == 0)
                {
                    LogStep("early-end", s);
                    SetPhase(Phase::Leave);
                    return;
                }
                if (NowMs() - g_ReadyMs >= static_cast<uint64_t>(g_Steps[g_Index].seconds) * 1000)
                    SetPhase(Phase::Leave);
                return;

            case Phase::Leave:
                if (AtMainMenu(s))
                {
                    // An ended mission can fall straight back to the menu.
                    g_MenuSinceMs = 0;
                    SetPhase(Phase::LeaveWaitMenu);
                    return;
                }
                if (TryLeave(s))
                {
                    if (g_Phase == Phase::Failed)
                        return;
                    g_MenuSinceMs = 0;
                    SetPhase(Phase::LeaveWaitMenu);
                }
                else if (PhaseTimedOut(kMenuTimeoutMs))
                {
                    Fail("leave: no screen or mission to leave", s);
                }
                return;

            case Phase::LeaveWaitMenu:
                if (g_Steps[g_Index].kind == StepKind::MpHost)
                    PumpLan();
                if (MenuSettled(s))
                {
                    if (g_Steps[g_Index].kind == StepKind::MpHost)
                        StopMpHost();
                    LogStep("end", s);
                    NextStep();
                }
                else if (g_Steps[g_Index].kind == StepKind::MpHost && s.runState != Hooks::kBzrRunStateStarted &&
                         NowMs() - g_MpLastNavMs >= kMpNavIntervalMs &&
                         (LiveSlotScreen(g_RoomSlotAddr, s) || LiveSlotScreen(g_LobbySlotAddr, s)))
                {
                    // A hosted game ends in the game room or the lobby; leave
                    // them with their Back buttons, as a player does.
                    g_MpLastNavMs = NowMs();
                    const bool room = LiveSlotScreen(g_RoomSlotAddr, s) != nullptr;
                    if (!CallButton(room ? g_RoomBackAddr : g_LobbyBackAddr))
                        return Fail(room ? "mp_host:leave room Back faulted" : "mp_host:leave lobby Back faulted", s);
                    LogStep(room ? "room-back" : "lobby-back", s);
                }
                else if (s.runState != kRunStateQuit && s.screenType != 0 &&
                         s.screenType != kScreenTypeMainMenu && s.screenOwnedByWrapper &&
                         NowMs() - g_PhaseStartMs > 5000)
                {
                    // A result screen raised after the leave request: dismiss it too.
                    if (TryLeave(s) && g_Phase != Phase::Failed)
                        SetPhase(Phase::LeaveWaitMenu);
                }
                else if (PhaseTimedOut(kMenuTimeoutMs))
                {
                    Fail("leave: main menu not reached", s);
                }
                return;

            case Phase::ExitWaitMenu:
                if (MenuSettled(s))
                {
                    LogShimA(LogLevel::Info, kComponent,
                             "[MODESTRESS] exit requested through the main screen exit button");
                    SetPhase(Phase::Finished);
                    if (!CallExit(s.screen))
                        Fail("exit: engine call faulted", s);
                }
                else if (PhaseTimedOut(kMenuTimeoutMs))
                {
                    Fail("exit: main menu not reached", s);
                }
                return;

            case Phase::Finished:
            case Phase::Failed:
                return;
            }
        }

        // Ogre::FrameListener, laid out to its 1.10 vtable: frameStarted,
        // frameRenderingQueued, frameEnded, virtual destructor. The driver
        // acts in frameEnded, after the frame's rendering, from the same
        // thread and point the stock UI loop reaches its button handlers.
        class ModeStressFrameListener
        {
        public:
            virtual bool frameStarted(const void*) { return true; }
            virtual bool frameRenderingQueued(const void*) { return true; }
            virtual bool frameEnded(const void*)
            {
                if (!g_Shutdown.load(std::memory_order_relaxed) && g_Phase != Phase::Finished &&
                    g_Phase != Phase::Failed)
                    Tick();
                return true;
            }
            virtual ~ModeStressFrameListener() = default;
        };
        ModeStressFrameListener g_FrameListener;

        bool ReadPlanFile(const char* path, std::string& out)
        {
            FILE* file = nullptr;
            if (fopen_s(&file, path, "rb") != 0 || !file)
                return false;
            char buffer[4096];
            size_t n = 0;
            while ((n = std::fread(buffer, 1, sizeof(buffer), file)) > 0)
            {
                out.append(buffer, n);
                if (out.size() > 65536)
                {
                    std::fclose(file);
                    return false;
                }
            }
            std::fclose(file);
            return true;
        }
    }

    void InitializeModeStressDriver()
    {
        char path[MAX_PATH] = {};
        const DWORD n = GetEnvironmentVariableA("OPENSHIM_MODE_STRESS_PLAN", path, MAX_PATH);
        if (n == 0)
            return;
        if (n >= MAX_PATH)
        {
            LogShimA(LogLevel::Error, kComponent, "[MODESTRESS] FAIL plan path too long");
            return;
        }
        std::string text;
        if (!ReadPlanFile(path, text))
        {
            LogShimA(LogLevel::Error, kComponent, "[MODESTRESS] FAIL plan file unreadable or over 64 KB: %s", path);
            return;
        }
        const ParseResult parsed = ParsePlan(text);
        if (!parsed.ok)
        {
            LogShimA(LogLevel::Error, kComponent, "[MODESTRESS] FAIL plan line %d: %s", parsed.errorLine,
                     parsed.error.c_str());
            return;
        }
        if (!BindRows())
        {
            LogShimA(LogLevel::Error, kComponent,
                     "[MODESTRESS] FAIL engine rows did not bind (not the exact GOG 2.2.301 build?)");
            return;
        }
        bool hasMpHost = false;
        for (const Step& step : parsed.plan.steps)
            hasMpHost = hasMpHost || step.kind == StepKind::MpHost;
        if (hasMpHost)
        {
            g_MpRowsBound = BindMpRows();
            if (!g_MpRowsBound)
                LogShimA(LogLevel::Error, kComponent,
                         "[MODESTRESS] mp_host engine rows did not bind; mp_host steps will fail");
        }
        for (uint32_t pass = 0; pass < parsed.plan.loops; ++pass)
            g_Steps.insert(g_Steps.end(), parsed.plan.steps.begin(), parsed.plan.steps.end());
        SetPhase(Phase::WaitStartupMenu);
        g_Enabled.store(true, std::memory_order_release);
        LogShimA(LogLevel::Info, kComponent, "[MODESTRESS] plan loaded path=%s steps=%u loops=%u total=%u", path,
                 static_cast<unsigned>(parsed.plan.steps.size()), parsed.plan.loops,
                 static_cast<unsigned>(g_Steps.size()));
    }

    void ModeStressRenderTick()
    {
        if (g_ListenerInstalled || !g_Enabled.load(std::memory_order_acquire) ||
            g_Shutdown.load(std::memory_order_acquire))
            return;
        const auto rootGet = Hooks::ResolveOgreProc<FnRootGet>("?getSingletonPtr@Root@Ogre@@SAPAV12@XZ");
        const auto addListener = Hooks::ResolveOgreProc<FnRootAddFrameListener>(
            "?addFrameListener@Root@Ogre@@QAEXPAVFrameListener@2@@Z");
        void* root = nullptr;
        if (rootGet && addListener)
        {
            try
            {
                root = rootGet();
            }
            catch (...)
            {
                root = nullptr;
            }
        }
        if (!root)
        {
            if (!g_ListenerWarned)
                LogShimA(LogLevel::Info, kComponent, "[MODESTRESS] Ogre Root not ready; frame listener will retry");
            g_ListenerWarned = true;
            return;
        }
        g_ListenerInstalled = true;
        // The startup timeout counts from the first frame, not from DLL load.
        SetPhase(Phase::WaitStartupMenu);
        addListener(root, &g_FrameListener);
        LogShimA(LogLevel::Info, kComponent, "[MODESTRESS] frame listener installed");
    }

    void ShutdownModeStressDriver()
    {
        if (g_Shutdown.exchange(true, std::memory_order_acq_rel))
            return;
        if (!g_Enabled.load(std::memory_order_acquire))
            return;
        if (g_Phase == Phase::Finished)
            LogShimA(LogLevel::Info, kComponent, "[MODESTRESS] shutdown after done");
        else if (g_Phase != Phase::Failed)
            LogShimA(LogLevel::Warn, kComponent, "[MODESTRESS] shutdown before the plan finished step=%u/%u",
                     static_cast<unsigned>(g_Index < g_Steps.size() ? g_Index + 1 : g_Steps.size()),
                     static_cast<unsigned>(g_Steps.size()));
    }
}
