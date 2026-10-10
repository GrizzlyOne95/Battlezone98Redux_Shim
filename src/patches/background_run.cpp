// background_run.cpp
// BZR Open Shim - [Testing] RunInBackground: keeps a single-player game
// simulating while its window is unfocused, without taking the user's mouse.
//
// Stock Redux treats WM_ACTIVATEAPP(FALSE) as "pause everything": the app-active
// flag at 0x008EAAA4 drops to 0, the frame gate (FUN_00618270) idles instead of
// running the frame, and the sim/timer pause. A game launched without focus
// also starts with the flag at 0 (FUN_00435bc0 seeds it from GetActiveWindow)
// and sits on its load screen. This patch:
//
//   1. subclasses the game window and swallows WM_ACTIVATEAPP(FALSE), so the
//      engine never pauses or minimizes;
//   2. raises the flag to 1 if it is 0 while the window is not minimized (no
//      pause function ran, so no resume is needed);
//   3. no-ops ClipCursor / SetCursorPos / SetCursor whenever the game window is
//      not the foreground window. With the flag on, the engine's per-frame
//      mouse code would otherwise clip and warp the user's real cursor.
//
// Default OFF. Single-player and windowed only: it is inert in network games
// (the engine already bypasses its pause there) and in fullscreen.
//
// Installs by chaining: the PeekMessageA IAT slot and the window procedure are
// both saved and called through, so it coexists with ui_performance_hooks.cpp.
#include "bzr_hooks_internal.h"
#include "background_run_policy.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "iat_patch.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            // GOG 2.2.301, image base 0x00400000.
            constexpr uintptr_t kWndProcAddr = 0x00619340;           // main WndProc
            constexpr uintptr_t kActivateBranchAddr = 0x0061992C;    // cmp [flag],0 / jne
            constexpr uintptr_t kDeactivateBranchAddr = 0x0061998E;  // cmp [flag],0 / je
            constexpr uintptr_t kDeactivateClearAddr = 0x00619997;   // mov [flag],0
            constexpr uintptr_t kMultiplayerGetterAddr = 0x00571C40; // FUN_00571c40
            constexpr uintptr_t kAppActiveFlagAddr = 0x008EAAA4;
            constexpr uintptr_t kFullscreenFlagAddr = 0x009183B8;
            constexpr uintptr_t kMultiplayerByteAddr = 0x00917F7B;

            std::atomic<bool> g_Enabled{ false };
            std::atomic<HWND> g_Window{ nullptr };
            std::atomic<WNDPROC> g_PrevWndProc{ nullptr };
            std::atomic<bool> g_ForcedLogged{ false };
            std::atomic<bool> g_SwallowLogged{ false };
            std::atomic<long> g_SwallowCount{ 0 };
            std::atomic<long> g_CursorSuppressCount{ 0 };

            using PFN_PeekMessageA = BOOL(WINAPI*)(LPMSG, HWND, UINT, UINT, UINT);
            using PFN_ClipCursor = BOOL(WINAPI*)(const RECT*);
            using PFN_SetCursorPos = BOOL(WINAPI*)(int, int);
            using PFN_SetCursor = HCURSOR(WINAPI*)(HCURSOR);
            PFN_PeekMessageA g_RealPeekMessageA = nullptr;
            PFN_ClipCursor g_RealClipCursor = nullptr;
            PFN_SetCursorPos g_RealSetCursorPos = nullptr;
            PFN_SetCursor g_RealSetCursor = nullptr;

            template <typename T>
            bool ReadGameValue(uintptr_t address, T& out)
            {
                __try
                {
                    out = *reinterpret_cast<volatile const T*>(address);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool IsMultiplayerSession()
            {
                uint8_t mpByte = 1;
                if (!ReadGameValue(kMultiplayerByteAddr, mpByte))
                    return true; // fail closed
                const uint16_t netId = ReadLocalPlayerNetIdValue();
                return mpByte != 0 || netId != 0;
            }

            bool IsFullscreen()
            {
                int fullscreen = 1;
                if (!ReadGameValue(kFullscreenFlagAddr, fullscreen))
                    return true; // fail closed
                return fullscreen != 0;
            }

            bool PolicyActive()
            {
                return BackgroundRunPolicy::Active(
                    g_Enabled.load(std::memory_order_acquire),
                    IsMultiplayerSession(),
                    IsFullscreen());
            }

            void EnforceActiveFlag(HWND window)
            {
                int flag = 1;
                if (!ReadGameValue(kAppActiveFlagAddr, flag))
                    return;
                if (!BackgroundRunPolicy::ShouldForceActiveFlag(
                        PolicyActive(), flag, IsIconic(window) != FALSE))
                    return;
                __try
                {
                    *reinterpret_cast<volatile int*>(kAppActiveFlagAddr) = 1;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return;
                }
                if (!g_ForcedLogged.exchange(true))
                    Log(L"[BGRUN] app-active flag was 0 while unfocused; forced to 1 (no pause ran)\n");
            }

            bool CursorCallSuppressed()
            {
                const HWND window = g_Window.load(std::memory_order_acquire);
                const bool suppress = BackgroundRunPolicy::ShouldSuppressCursorCall(
                    g_Enabled.load(std::memory_order_acquire),
                    window != nullptr,
                    window != nullptr && GetForegroundWindow() == window);
                if (suppress)
                    g_CursorSuppressCount.fetch_add(1, std::memory_order_relaxed);
                return suppress;
            }

            BOOL WINAPI Hooked_ClipCursor(const RECT* rect)
            {
                if (CursorCallSuppressed())
                    return g_RealClipCursor ? g_RealClipCursor(nullptr) : TRUE; // release any clip
                return g_RealClipCursor ? g_RealClipCursor(rect) : FALSE;
            }

            BOOL WINAPI Hooked_SetCursorPos(int x, int y)
            {
                if (CursorCallSuppressed())
                    return TRUE;
                return g_RealSetCursorPos ? g_RealSetCursorPos(x, y) : FALSE;
            }

            HCURSOR WINAPI Hooked_SetCursor(HCURSOR cursor)
            {
                if (CursorCallSuppressed())
                    return nullptr;
                return g_RealSetCursor ? g_RealSetCursor(cursor) : nullptr;
            }

            LRESULT CALLBACK BackgroundRunWndProc(HWND h, UINT msg, WPARAM w, LPARAM l)
            {
                EnforceActiveFlag(h);
                if (BackgroundRunPolicy::ShouldSwallowMessage(
                        PolicyActive(), msg, static_cast<unsigned long long>(w)))
                {
                    g_SwallowCount.fetch_add(1, std::memory_order_relaxed);
                    if (!g_SwallowLogged.exchange(true))
                        Log(L"[BGRUN] swallowed WM_ACTIVATEAPP(FALSE); simulation stays running\n");
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

            void EnsureSubclassOnMainThread()
            {
                if (HWND existing = g_Window.load(std::memory_order_acquire))
                {
                    EnforceActiveFlag(existing);
                    return;
                }
                FindCtx ctx;
                EnumThreadWindows(GetCurrentThreadId(), FindGameWindowCb,
                                  reinterpret_cast<LPARAM>(&ctx));
                if (!ctx.found)
                    return;

                SetLastError(ERROR_SUCCESS);
                const auto prev = reinterpret_cast<WNDPROC>(
                    SetWindowLongPtrA(ctx.found, GWLP_WNDPROC,
                                      reinterpret_cast<LONG_PTR>(&BackgroundRunWndProc)));
                if (!prev && GetLastError() != ERROR_SUCCESS)
                {
                    Log(L"[BGRUN] failed to subclass game window error=%lu\n", GetLastError());
                    return;
                }
                g_PrevWndProc.store(prev, std::memory_order_release);
                g_Window.store(ctx.found, std::memory_order_release);
                Log(L"[BGRUN] game window subclassed hwnd=0x%p previous=0x%p\n", ctx.found, prev);
                EnforceActiveFlag(ctx.found);
            }

            BOOL WINAPI Hooked_PeekMessageA(LPMSG msg, HWND hwnd, UINT min, UINT max, UINT remove)
            {
                EnsureSubclassOnMainThread();
                return g_RealPeekMessageA ? g_RealPeekMessageA(msg, hwnd, min, max, remove) : FALSE;
            }

            bool PatchMainImport(const char* name, void* replacement, void** original)
            {
                return IatPatch::PatchImportFromAnyDll(
                           GetModuleHandleW(nullptr), name, replacement, original) ==
                       IatPatch::Result::Patched;
            }

            bool SignaturesMatch()
            {
                if (reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr)) != 0x00400000)
                {
                    Log(L"[BGRUN] Executable relocated; RunInBackground unavailable\n");
                    return false;
                }
                static const uint8_t kWndProc[] =
                { 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x88, 0x00, 0x00, 0x00 };
                static const uint8_t kActivateBranch[] =
                { 0x83, 0x3D, 0xA4, 0xAA, 0x8E, 0x00, 0x00, 0x75 };
                static const uint8_t kDeactivateBranch[] =
                { 0x83, 0x3D, 0xA4, 0xAA, 0x8E, 0x00, 0x00, 0x74 };
                static const uint8_t kDeactivateClear[] =
                { 0xC7, 0x05, 0xA4, 0xAA, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00 };
                static const uint8_t kMpGetter[] =
                { 0x55, 0x8B, 0xEC, 0xA0, 0x7B, 0x7F, 0x91, 0x00 };
                struct Site
                {
                    uintptr_t address;
                    const uint8_t* bytes;
                    size_t length;
                    const char* name;
                };
                const Site sites[] =
                {
                    { kWndProcAddr, kWndProc, sizeof(kWndProc), "main WndProc prologue" },
                    { kActivateBranchAddr, kActivateBranch, sizeof(kActivateBranch), "WM_ACTIVATEAPP activate branch" },
                    { kDeactivateBranchAddr, kDeactivateBranch, sizeof(kDeactivateBranch), "WM_ACTIVATEAPP deactivate branch" },
                    { kDeactivateClearAddr, kDeactivateClear, sizeof(kDeactivateClear), "app-active flag clear" },
                    { kMultiplayerGetterAddr, kMpGetter, sizeof(kMpGetter), "multiplayer getter" },
                };
                for (const Site& site : sites)
                {
                    if (!ExpectedBytesMatchAt(site.address, site.bytes, site.length))
                    {
                        Log(L"[BGRUN] Signature mismatch at 0x%08X (%hs); RunInBackground stays off\n",
                            static_cast<uint32_t>(site.address), site.name);
                        return false;
                    }
                }
                return true;
            }
        }

        // [Testing] RunInBackground / OPENSHIM_RUN_IN_BACKGROUND. Default OFF.
        void InstallBackgroundRunIfRequested()
        {
            if (!EnvFlagEnabled("OPENSHIM_RUN_IN_BACKGROUND"))
                return;
            static bool attempted = false;
            if (attempted)
                return;
            attempted = true;

            if (!SignaturesMatch())
                return;

            // Cursor guards first so they are in place before the flag can rise.
            const bool clip = PatchMainImport("ClipCursor",
                reinterpret_cast<void*>(&Hooked_ClipCursor), reinterpret_cast<void**>(&g_RealClipCursor));
            const bool pos = PatchMainImport("SetCursorPos",
                reinterpret_cast<void*>(&Hooked_SetCursorPos), reinterpret_cast<void**>(&g_RealSetCursorPos));
            const bool cur = PatchMainImport("SetCursor",
                reinterpret_cast<void*>(&Hooked_SetCursor), reinterpret_cast<void**>(&g_RealSetCursor));
            if (!clip || !pos)
            {
                // Without the cursor guards the unfocused game would trap the
                // user's mouse, so refuse to enable. (SetCursor is cosmetic.)
                Log(L"[BGRUN] cursor guard import patch failed (ClipCursor=%d SetCursorPos=%d); RunInBackground stays off\n",
                    clip ? 1 : 0, pos ? 1 : 0);
                return;
            }
            const bool peek = PatchMainImport("PeekMessageA",
                reinterpret_cast<void*>(&Hooked_PeekMessageA), reinterpret_cast<void**>(&g_RealPeekMessageA));
            if (!peek)
            {
                Log(L"[BGRUN] PeekMessageA seam not installed; RunInBackground stays off\n");
                return;
            }
            g_Enabled.store(true, std::memory_order_release);
            Log(L"[BGRUN] enabled (single-player, windowed only): WM_ACTIVATEAPP(FALSE) swallowed, "
                L"cursor calls guarded (ClipCursor/SetCursorPos/SetCursor=%d) while unfocused\n",
                cur ? 1 : 0);
        }
    }
}
