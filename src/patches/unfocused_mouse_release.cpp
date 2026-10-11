// unfocused_mouse_release.cpp
// BZR Open Shim - stop Redux from clipping and re-centring the OS cursor
// while its window is in the background or minimized.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "iat_patch.h"
#include "patcher.h"
#include <Windows.h>

namespace BZROpenShim
{
    namespace Hooks
    {
        // -----------------------------------------------------------------
        // Unfocused mouse release
        // -----------------------------------------------------------------
        //
        // In mouse-look the per-frame look reader (0x00623B20 in GOG 2.2.301)
        // re-applies a ClipCursor rectangle through 0x004351E0 and warps the
        // cursor back to the window centre through 0x004350E0 -> SetCursorPos.
        // Its only focus test is 0x00435160, `GetActiveWindow() == hwnd`, and
        // GetActiveWindow is per-thread: a minimized Redux window, or one
        // behind another process's window, can still be its own thread's
        // active window, so the cursor is pinned to the middle of the screen
        // while the user is working in something else. BZ 1.5's LockMouse
        // guarded its SetCursorPos with a GetFocus() test; Redux lost it.
        //
        // The fix sits on the executable's own user32 imports rather than on
        // a code address, so it carries no build-specific bytes: while the
        // foreground window belongs to another process, or Redux's top-level
        // window is minimized, SetCursorPos becomes a no-op and any clip
        // rectangle is replaced by a release. When focus returns, the look
        // reader's next frame re-clips and re-centres exactly as stock does.
        //
        // OPENSHIM_NEVER_CAPTURE_MOUSE=1 (environment, or [Environment] in
        // openshim.ini) widens that to "always": the game never clips or warps
        // the cursor even in the foreground. That is for automated test
        // clients, which are driven by posted window messages and only ever
        // steal the real cursor from whoever is at the desk. Not for play:
        // mouse-look stops working without the re-centre.

        bool g_UnfocusedMouseReleaseEnabled = true;
        static bool s_NeverCaptureMouse = false;
        static bool s_UnfocusedMouseReleaseInstalled = false;
        static volatile long s_UnfocusedMouseReleaseLogBudget = 4;

        using FnSetCursorPos = BOOL(WINAPI*)(int, int);
        using FnClipCursor = BOOL(WINAPI*)(const RECT*);
        static FnSetCursorPos s_OriginalSetCursorPos = nullptr;
        static FnClipCursor s_OriginalClipCursor = nullptr;

        // True when Redux should not own the cursor right now.
        static bool ReduxIsInBackground()
        {
            if (s_NeverCaptureMouse)
                return true;
            const HWND foreground = GetForegroundWindow();
            if (!foreground)
                return true;

            DWORD foregroundPid = 0;
            GetWindowThreadProcessId(foreground, &foregroundPid);
            if (foregroundPid != GetCurrentProcessId())
                return true;

            // The foreground window is ours, but a minimized top-level
            // window can still hold activation.
            const HWND root = GetAncestor(foreground, GA_ROOTOWNER);
            return IsIconic(root ? root : foreground) != FALSE;
        }

        static void NoteSuppressed(const char* what)
        {
            if (InterlockedDecrement(&s_UnfocusedMouseReleaseLogBudget) >= 0)
                Log(L"[MOUSEFOCUS] %hs; suppressed %hs\n",
                    s_NeverCaptureMouse ? "Never-capture mode" : "Redux is in the background", what);
        }

        static BOOL WINAPI SetCursorPosHook(int x, int y)
        {
            if ((g_UnfocusedMouseReleaseEnabled || s_NeverCaptureMouse) && ReduxIsInBackground())
            {
                NoteSuppressed("SetCursorPos");
                return TRUE;
            }
            return s_OriginalSetCursorPos ? s_OriginalSetCursorPos(x, y) : SetCursorPos(x, y);
        }

        static BOOL WINAPI ClipCursorHook(const RECT* rect)
        {
            if (rect && (g_UnfocusedMouseReleaseEnabled || s_NeverCaptureMouse) && ReduxIsInBackground())
            {
                NoteSuppressed("ClipCursor");
                rect = nullptr;
            }
            return s_OriginalClipCursor ? s_OriginalClipCursor(rect) : ClipCursor(rect);
        }

        // -----------------------------------------------------------------
        // Never-activate (test clients)
        // -----------------------------------------------------------------
        //
        // OPENSHIM_NEVER_ACTIVATE=1 (environment, or [Environment] in
        // openshim.ini) stops the game window taking the foreground or
        // keyboard focus from whoever is at the desk. NEVER_CAPTURE_MOUSE
        // covers the cursor only; the window still activated itself on launch.
        // Hooked on the executable's user32 imports, like the cursor hooks:
        //   ShowWindow        activating show commands -> *NOACTIVATE variants
        //   SetForegroundWindow, BringWindowToTop, SetActiveWindow -> no-op
        //   SetWindowPos      SWP_NOACTIVATE added
        // SetFocus is deliberately left alone: it only moves focus within the
        // calling thread's own queue and cannot steal the foreground from
        // another process, and the engine's own focus bookkeeping
        // (GetFocus/GetActiveWindow checks) keeps working. Off by default;
        // with the flag unset no import is touched.

        static bool s_NeverActivateInstalled = false;
        static volatile long s_NeverActivateLogged[5] = {};

        using FnShowWindow = BOOL(WINAPI*)(HWND, int);
        using FnHwndBool = BOOL(WINAPI*)(HWND);
        using FnSetActiveWindow = HWND(WINAPI*)(HWND);
        using FnSetWindowPos = BOOL(WINAPI*)(HWND, HWND, int, int, int, int, UINT);
        static FnShowWindow s_OriginalShowWindow = nullptr;
        static FnHwndBool s_OriginalSetForegroundWindow = nullptr;
        static FnHwndBool s_OriginalBringWindowToTop = nullptr;
        static FnSetActiveWindow s_OriginalSetActiveWindow = nullptr;
        static FnSetWindowPos s_OriginalSetWindowPos = nullptr;

        // One-shot per API (slot index), not per call.
        static void NoteNoActivate(int slot, const char* what)
        {
            if (InterlockedExchange(&s_NeverActivateLogged[slot], 1) == 0)
                Log(L"[NOACTIVATE] Never-activate mode; suppressed %hs\n", what);
        }

        static int NoActivateShowCommand(int cmd)
        {
            switch (cmd)
            {
            case SW_SHOWNORMAL: // == SW_NORMAL
            case SW_SHOW:
            case SW_RESTORE:
            case SW_SHOWDEFAULT:
            case SW_SHOWMAXIMIZED: // == SW_MAXIMIZE
                return SW_SHOWNOACTIVATE;
            case SW_SHOWMINIMIZED:
            case SW_MINIMIZE:
                return SW_SHOWMINNOACTIVE;
            default: // SW_HIDE and the already-passive commands
                return cmd;
            }
        }

        static BOOL WINAPI ShowWindowHook(HWND hwnd, int cmd)
        {
            const int mapped = NoActivateShowCommand(cmd);
            if (mapped != cmd)
                NoteNoActivate(0, "ShowWindow activation");
            return s_OriginalShowWindow ? s_OriginalShowWindow(hwnd, mapped) : ShowWindow(hwnd, mapped);
        }

        static BOOL WINAPI SetForegroundWindowHook(HWND)
        {
            NoteNoActivate(1, "SetForegroundWindow");
            return TRUE;
        }

        static BOOL WINAPI BringWindowToTopHook(HWND)
        {
            NoteNoActivate(2, "BringWindowToTop");
            return TRUE;
        }

        static HWND WINAPI SetActiveWindowHook(HWND)
        {
            NoteNoActivate(3, "SetActiveWindow");
            return GetActiveWindow(); // SetActiveWindow returns the previous active window
        }

        static BOOL WINAPI SetWindowPosHook(HWND hwnd, HWND after, int x, int y, int cx, int cy, UINT flags)
        {
            if (!(flags & SWP_NOACTIVATE))
                NoteNoActivate(4, "SetWindowPos activation");
            flags |= SWP_NOACTIVATE;
            return s_OriginalSetWindowPos ? s_OriginalSetWindowPos(hwnd, after, x, y, cx, cy, flags)
                                          : SetWindowPos(hwnd, after, x, y, cx, cy, flags);
        }

        static void InstallNeverActivateIfRequested()
        {
            if (s_NeverActivateInstalled)
                return;
            if (!EnvFlagEnabled("OPENSHIM_NEVER_ACTIVATE"))
            {
                s_NeverActivateInstalled = true; // flag unset: no hooks, no retry
                return;
            }
            Log(L"[NOACTIVATE] OPENSHIM_NEVER_ACTIVATE: window never takes foreground or focus (test clients only)\n");

            const HMODULE exe = GetModuleHandleW(nullptr);
            const auto patch = [exe](const char* name, void* hook, void** original) {
                return IatPatch::PatchImport(exe, "user32.dll", name, hook, original);
            };
            const IatPatch::Result results[5] = {
                patch("ShowWindow", reinterpret_cast<void*>(&ShowWindowHook),
                      reinterpret_cast<void**>(&s_OriginalShowWindow)),
                patch("SetForegroundWindow", reinterpret_cast<void*>(&SetForegroundWindowHook),
                      reinterpret_cast<void**>(&s_OriginalSetForegroundWindow)),
                patch("BringWindowToTop", reinterpret_cast<void*>(&BringWindowToTopHook),
                      reinterpret_cast<void**>(&s_OriginalBringWindowToTop)),
                patch("SetActiveWindow", reinterpret_cast<void*>(&SetActiveWindowHook),
                      reinterpret_cast<void**>(&s_OriginalSetActiveWindow)),
                patch("SetWindowPos", reinterpret_cast<void*>(&SetWindowPosHook),
                      reinterpret_cast<void**>(&s_OriginalSetWindowPos)),
            };
            bool faulted = false;
            for (const auto r : results)
                faulted = faulted || r == IatPatch::Result::Faulted;
            Log(L"[NOACTIVATE] Hooks: ShowWindow=%d SetForegroundWindow=%d BringWindowToTop=%d "
                L"SetActiveWindow=%d SetWindowPos=%d (0=hooked)\n",
                static_cast<int>(results[0]), static_cast<int>(results[1]), static_cast<int>(results[2]),
                static_cast<int>(results[3]), static_cast<int>(results[4]));
            // As above: a fault may be transient, NotFound is final.
            s_NeverActivateInstalled = !faulted;
        }

        void InstallUnfocusedMouseReleaseIfPossible()
        {
            InstallNeverActivateIfRequested();
            if (s_UnfocusedMouseReleaseInstalled)
                return;
            s_NeverCaptureMouse = EnvFlagEnabled("OPENSHIM_NEVER_CAPTURE_MOUSE");
            if (s_NeverCaptureMouse)
                Log(L"[MOUSEFOCUS] OPENSHIM_NEVER_CAPTURE_MOUSE: cursor is never clipped or re-centred (test clients only)\n");
            if (!g_UnfocusedMouseReleaseEnabled && !s_NeverCaptureMouse)
            {
                Log(L"[MOUSEFOCUS] Unfocused mouse release disabled\n");
                s_UnfocusedMouseReleaseInstalled = true;
                return;
            }

            const HMODULE exe = GetModuleHandleW(nullptr);
            const IatPatch::Result cursorPos = IatPatch::PatchImport(
                exe, "user32.dll", "SetCursorPos",
                reinterpret_cast<void*>(&SetCursorPosHook),
                reinterpret_cast<void**>(&s_OriginalSetCursorPos));
            const IatPatch::Result clip = IatPatch::PatchImport(
                exe, "user32.dll", "ClipCursor",
                reinterpret_cast<void*>(&ClipCursorHook),
                reinterpret_cast<void**>(&s_OriginalClipCursor));

            const auto describe = [](IatPatch::Result result) {
                switch (result)
                {
                case IatPatch::Result::Patched: return "hooked";
                case IatPatch::Result::NotFound: return "not imported";
                default: return "faulted";
                }
            };
            Log(L"[MOUSEFOCUS] Unfocused mouse release: SetCursorPos=%hs ClipCursor=%hs\n",
                describe(cursorPos), describe(clip));

            // A fault may be a transient race; leave the latch open so the
            // deferred retry can try again. NotFound is final.
            s_UnfocusedMouseReleaseInstalled =
                cursorPos != IatPatch::Result::Faulted && clip != IatPatch::Result::Faulted;
        }
    }
}
