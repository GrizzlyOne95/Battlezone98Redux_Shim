// lua_callback_alert_defer.cpp
// BZR Open Shim - hold Lua mission callback error alerts until the frame ends
// ([Fixes] DeferLuaCallbackAlert).
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// GOG Redux 2.2.301 (SHA256 8D71F56C...3377413), read in Ghidra and rizin:
//   - Every Lua mission dispatch (FUN_0050a970 Start, FUN_0050aa10 GameKey and
//     Update, FUN_0050ace0 CreateObject, FUN_0050ad90 AddObject, FUN_0050ae40
//     DeleteObject, FUN_0050aef0 CreatePlayer, FUN_0050afd0 AddPlayer,
//     FUN_0050b0b0 DeletePlayer, FUN_0050b310 Receive, and the non-sim Save,
//     Load, Command, package-load and script-load paths) ends with
//     `push fmt; push L; push status; call 0x004FF600; add esp,0xC`.
//   - 0x004FF600 is bool __cdecl(int status, lua_State* L, const char* fmt):
//     status != 0 reads lua_tolstring(L, -1, NULL) (0x0082D377) and calls the
//     engine error alert 0x007D6830(fmt, msg), then returns status == 0.
//   - 0x007D6830 formats into a 1024-byte buffer, logs it, prints it to the
//     console and calls the alert 0x005D4A60(text, 1); a 0 return (game state 9
//     or the player chose to quit) is exit(0x71).
//   - 0x005D4A60 runs a modal UI screen (type 0x1D) whose loop calls the in-game
//     screen update, which calls the frame 0x00618270 -> DoNextFrame 0x00618130
//     -> simulation and render. Raised from inside a sim callback, the world
//     keeps simulating and rendering under the half-run callback: in DeleteObject
//     the object is mid-teardown, and both the render-node sync 0x00680BD0
//     (PR #941) and the GameObject teardown 0x004DAE70 -> 0x0067E550 ->
//     0x0067CFA0 (issue #942) then call through a freed object's vtable.
//   - The top-level game loop 0x00618A40 runs `while (GameState() == 5)
//     FUN_00618270(0)`, calling it at 0x00618A92. The modal's own nested frames
//     reach 0x00618270 through 0x007C7570, not through that call.
//
// Fix: the in-sim dispatch call sites are redirected to DeferredLuaCheckStatus.
// While the top-level frame call at 0x00618A92 is running, a failing status is
// logged to the engine log at once and queued (duplicates collapsed); the
// callback returns false exactly as stock. When the frame returns, the queued
// alerts are shown through the stock 0x007D6830 path, one after another, with
// no sim callback on the stack, and only while the game is still in state 5
// (a frame that ended the mission leaves them logged only). Outside that frame
// (mission load, shutdown, and the frames the shown alert's own modal loop runs)
// the redirect calls the stock function unchanged, as does every dispatch that
// is not redirected. That is safe under the shown alert: 0x005D4A60 sets the
// alert-active byte 0x00918132 before its loop and returns 1 at 0x005D4A8C
// while it is set, so a nested error is logged and no second modal opens.
// Each deferred error is logged twice: once at once (so it survives a crash
// later in the frame) and once by the stock alert when it is shown.
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "lua_alert_queue.h"
#include "shim_log.h"

#include <cstdint>
#include <cstdio>

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            constexpr const char* kComponent = "LuaAlertDefer";
            // 0x005D4A60 refuses to show an alert in this state and 0x007D6830
            // then exits the process; leave such errors to the stock path.
            constexpr int kGameStateNoAlert = 9;
            // The state the top-level loop runs frames in. A deferred alert is
            // only shown if the frame left the game there.
            constexpr int kGameStatePlaying = 5;

            typedef bool(__cdecl* FnLuaCheckStatus)(int status, void* L, const char* fmt);
            typedef const char*(__cdecl* FnLuaToLString)(void* L, int index, size_t* len);
            typedef void(__cdecl* FnEngineErrorAlert)(const char* fmt, ...);
            typedef void(__cdecl* FnEngineLog)(const char* fmt, ...);
            typedef void(__cdecl* FnFrame)(int forceIdle);
            typedef int(__cdecl* FnGameState)();

            FnLuaCheckStatus g_StockCheckStatus = nullptr;
            FnLuaToLString g_LuaToLString = nullptr;
            FnEngineErrorAlert g_EngineErrorAlert = nullptr;
            FnEngineLog g_EngineLog = nullptr;
            FnFrame g_Frame = nullptr;
            FnGameState g_GameState = nullptr;

            // Main thread only, like the Lua state and the game loop.
            bool g_InTopLevelFrame = false;
            bool g_Initialized = false;
            uint32_t g_DeferredTotal = 0;
            LuaAlertQueue::Queue g_Queue;

            struct DispatchSite
            {
                const char* row;
                const char* callback;
            };
            // Mission callbacks the simulation runs. Save, Load, Command and the
            // package/script loaders are left stock: they run from menus or at
            // load time, outside the frame this fix brackets.
            constexpr DispatchSite kDispatchSites[] = {
                {"LuaDispatch::StartCheckCall", "Start"},
                {"LuaDispatch::GameKeyCheckCall", "GameKey"},
                {"LuaDispatch::UpdateCheckCall", "Update"},
                {"LuaDispatch::CreateObjectCheckCall", "CreateObject"},
                {"LuaDispatch::AddObjectCheckCall", "AddObject"},
                {"LuaDispatch::DeleteObjectCheckCall", "DeleteObject"},
                {"LuaDispatch::CreatePlayerCheckCall", "CreatePlayer"},
                {"LuaDispatch::AddPlayerCheckCall", "AddPlayer"},
                {"LuaDispatch::DeletePlayerCheckCall", "DeletePlayer"},
                {"LuaDispatch::ReceiveCheckCall", "Receive"},
            };

            struct FrameScope
            {
                FrameScope() { g_InTopLevelFrame = true; }
                ~FrameScope() { g_InTopLevelFrame = false; }
            };

            bool __cdecl DeferredLuaCheckStatus(int status, void* L, const char* fmt)
            {
                if (status == 0)
                    return true;
                if (!g_InTopLevelFrame || g_GameState() == kGameStateNoAlert)
                    return g_StockCheckStatus(status, L, fmt);

                const char* message = g_LuaToLString(L, -1, nullptr);
                const LuaAlertQueue::PushResult result = g_Queue.Push(fmt, message);

                // What stock logs first, so the error is in BZLogger.txt even if
                // the frame never ends. "%s" keeps a '%' in the Lua text literal.
                char text[1024];
                std::snprintf(text, sizeof(text), fmt, message ? message : "(null)");
                g_EngineLog("%s\n", text);
                ++g_DeferredTotal;
                if (result == LuaAlertQueue::PushResult::Added)
                    LogShimA(LogLevel::Info, kComponent,
                             "[LUAALERT] deferred a Lua callback alert to the end of the frame (total %u)",
                             g_DeferredTotal);
                else if (result == LuaAlertQueue::PushResult::Dropped)
                    LogShimA(LogLevel::Warn, kComponent,
                             "[LUAALERT] alert queue full; this error is logged only");
                return false;
            }

            void FlushDeferredAlerts()
            {
                if (g_Queue.Empty())
                    return;
                uint32_t dropped = 0;
                std::vector<LuaAlertQueue::Entry> entries = g_Queue.Drain(&dropped);
                if (dropped != 0)
                    LogShimA(LogLevel::Warn, kComponent,
                             "[LUAALERT] %u further distinct Lua errors this frame were logged, not shown", dropped);
                for (const LuaAlertQueue::Entry& entry : entries)
                {
                    const int state = g_GameState();
                    if (state != kGameStatePlaying)
                    {
                        LogShimA(LogLevel::Info, kComponent,
                                 "[LUAALERT] frame left the game in state %d; deferred alert logged only", state);
                        continue;
                    }
                    const std::string text = LuaAlertQueue::DisplayMessage(entry);
                    LogShimA(LogLevel::Info, kComponent, "[LUAALERT] showing deferred alert (x%u)", entry.count);
                    // Stock path: log, console, modal; exits if the player quits.
                    g_EngineErrorAlert(entry.format, text.c_str());
                }
            }

            void __cdecl TopLevelFrameHook(int forceIdle)
            {
                {
                    FrameScope scope;
                    g_Frame(forceIdle);
                }
                FlushDeferredAlerts();
            }
        }

        void InitializeDeferLuaCallbackAlertConfig()
        {
            if (g_Initialized)
                return;
            g_Initialized = true;

            if (EnvFlagEnabled("OPENSHIM_NO_DEFER_LUA_CALLBACK_ALERT"))
            {
                LogShimA(LogLevel::Info, kComponent, "[LUAALERT] disabled by OPENSHIM_NO_DEFER_LUA_CALLBACK_ALERT");
                return;
            }
            bool enabled = true;
            if (TryGetUserConfigBool(kUserConfigFixesSection, "DeferLuaCallbackAlert", enabled) && !enabled)
            {
                LogShimA(LogLevel::Info, kComponent, "[LUAALERT] disabled by config");
                return;
            }

            uint32_t checkStatus = 0, toLString = 0, errorAlert = 0, engineLog = 0, frameCall = 0, frame = 0;
            const HookEngine::EngineRow rows[] = {
                {"LuaCheckStatus", &checkStatus},
                {"LuaToLString", &toLString},
                {"EngineErrorAlert", &errorAlert},
                {"BzrNetLogger", &engineLog},
                {"GameLoop::FrameCall", &frameCall},
                {"GameLoop::Frame", &frame},
            };
            if (!HookEngine::BindEngineRows("Lua callback alert deferral", rows))
                return;
            const uint32_t gameState = HookEngine::ResolveNamedAddress("GameState::Get");
            if (gameState == 0)
            {
                LogShimA(LogLevel::Warn, kComponent, "[LUAALERT] stands down: GameState::Get unresolved");
                return;
            }

            g_StockCheckStatus = reinterpret_cast<FnLuaCheckStatus>(static_cast<uintptr_t>(checkStatus));
            g_LuaToLString = reinterpret_cast<FnLuaToLString>(static_cast<uintptr_t>(toLString));
            g_EngineErrorAlert = reinterpret_cast<FnEngineErrorAlert>(static_cast<uintptr_t>(errorAlert));
            g_EngineLog = reinterpret_cast<FnEngineLog>(static_cast<uintptr_t>(engineLog));
            g_Frame = reinterpret_cast<FnFrame>(static_cast<uintptr_t>(frame));
            g_GameState = reinterpret_cast<FnGameState>(static_cast<uintptr_t>(gameState));

            // The frame bracket first: without it every redirect would only
            // ever take the stock path, so there is no point installing them.
            if (!RedirectCallTarget(frameCall, frame, reinterpret_cast<uintptr_t>(&TopLevelFrameHook)))
            {
                LogShimA(LogLevel::Warn, kComponent,
                         "[LUAALERT] stands down: call at 0x%08X does not target the frame 0x%08X", frameCall, frame);
                return;
            }

            unsigned installed = 0;
            for (const DispatchSite& site : kDispatchSites)
            {
                uint32_t call = 0;
                const HookEngine::EngineRow siteRow[] = {{site.row, &call}};
                if (!HookEngine::BindEngineRows("Lua callback alert deferral", siteRow) ||
                    !RedirectCallTarget(call, checkStatus, reinterpret_cast<uintptr_t>(&DeferredLuaCheckStatus)))
                {
                    LogShimA(LogLevel::Warn, kComponent, "[LUAALERT] %s dispatch left stock", site.callback);
                    continue;
                }
                ++installed;
            }
            LogShimA(LogLevel::Info, kComponent,
                     "[LUAALERT] installed: %u of %u sim callback dispatches defer their error alert to the end of the frame",
                     installed, static_cast<unsigned>(sizeof(kDispatchSites) / sizeof(kDispatchSites[0])));
        }
    }
}
