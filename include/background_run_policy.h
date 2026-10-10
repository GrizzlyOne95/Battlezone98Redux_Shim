#pragma once
// background_run_policy.h
// Pure decision rules for the [Testing] RunInBackground toggle. No Windows
// calls, so tests/background_run_policy_tests.cpp can exercise them directly.

namespace BZROpenShim
{
    namespace BackgroundRunPolicy
    {
        constexpr unsigned kWmActivateApp = 0x001C;

        // The toggle only ever acts in a windowed, single-player session.
        // Multiplayer already bypasses the engine's pause, and a fullscreen
        // device must keep the stock minimize-on-deactivate behaviour.
        inline bool Active(bool enabled, bool multiplayer, bool fullscreen)
        {
            return enabled && !multiplayer && !fullscreen;
        }

        // WM_ACTIVATEAPP(FALSE) is swallowed so the engine never pauses the
        // simulation or minimizes the window.
        inline bool ShouldSwallowMessage(bool active, unsigned msg, unsigned long long wParam)
        {
            return active && msg == kWmActivateApp && wParam == 0;
        }

        // The app-active flag is forced on only while the window is not
        // minimized (a minimized window cannot render).
        inline bool ShouldForceActiveFlag(bool active, int currentFlag, bool iconic)
        {
            return active && currentFlag == 0 && !iconic;
        }

        // Cursor-affecting calls (ClipCursor, SetCursorPos, SetCursor) become
        // no-ops while the game window is not the foreground window.
        inline bool ShouldSuppressCursorCall(bool enabled, bool gameWindowKnown, bool gameIsForeground)
        {
            return enabled && gameWindowKnown && !gameIsForeground;
        }
    }
}
