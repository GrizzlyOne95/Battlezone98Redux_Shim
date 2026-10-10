// unfocused_mouse_release.cpp
// BZR Open Shim - stop Redux from clipping and re-centring the OS cursor
// while its window is in the background or minimized.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
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

        bool g_UnfocusedMouseReleaseEnabled = true;
        static bool s_UnfocusedMouseReleaseInstalled = false;
        static volatile long s_UnfocusedMouseReleaseLogBudget = 4;

        using FnSetCursorPos = BOOL(WINAPI*)(int, int);
        using FnClipCursor = BOOL(WINAPI*)(const RECT*);
        static FnSetCursorPos s_OriginalSetCursorPos = nullptr;
        static FnClipCursor s_OriginalClipCursor = nullptr;

        // True when Redux should not own the cursor right now.
        static bool ReduxIsInBackground()
        {
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
                Log(L"[MOUSEFOCUS] Redux is in the background; suppressed %hs\n", what);
        }

        static BOOL WINAPI SetCursorPosHook(int x, int y)
        {
            if (g_UnfocusedMouseReleaseEnabled && ReduxIsInBackground())
            {
                NoteSuppressed("SetCursorPos");
                return TRUE;
            }
            return s_OriginalSetCursorPos ? s_OriginalSetCursorPos(x, y) : SetCursorPos(x, y);
        }

        static BOOL WINAPI ClipCursorHook(const RECT* rect)
        {
            if (rect && g_UnfocusedMouseReleaseEnabled && ReduxIsInBackground())
            {
                NoteSuppressed("ClipCursor");
                rect = nullptr;
            }
            return s_OriginalClipCursor ? s_OriginalClipCursor(rect) : ClipCursor(rect);
        }

        void InstallUnfocusedMouseReleaseIfPossible()
        {
            if (s_UnfocusedMouseReleaseInstalled)
                return;
            if (!g_UnfocusedMouseReleaseEnabled)
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
