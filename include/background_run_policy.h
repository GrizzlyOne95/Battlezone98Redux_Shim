#pragma once
// background_run_policy.h
// Pure decision rules for the [Testing] RunInBackground toggle. No Windows
// calls, so tests/background_run_policy_tests.cpp can exercise them directly.

namespace BZROpenShim
{
    namespace BackgroundRunPolicy
    {
        constexpr unsigned kWmActivate = 0x0006;
        constexpr unsigned kWmActivateApp = 0x001C;
        constexpr unsigned kWaInactive = 0;

        // The toggle only ever acts in a windowed, single-player session.
        // Multiplayer already bypasses the engine's pause, and a fullscreen
        // device must keep the stock minimize-on-deactivate behaviour.
        inline bool Active(bool enabled, bool multiplayer, bool fullscreen)
        {
            return enabled && !multiplayer && !fullscreen;
        }

        // WM_ACTIVATEAPP(FALSE) is swallowed so the engine never pauses the
        // simulation or minimizes the window. WM_ACTIVATE(WA_INACTIVE) is
        // swallowed too: the engine forwards it to Ogre's window procedure,
        // which marks the RenderWindow inactive, and Ogre then skips that
        // window every frame. The sim keeps running but nothing is drawn.
        inline bool ShouldSwallowMessage(bool active, unsigned msg, unsigned long long wParam)
        {
            if (!active)
                return false;
            if (msg == kWmActivateApp)
                return wParam == 0;
            if (msg == kWmActivate)
                return (wParam & 0xFFFFu) == kWaInactive;
            return false;
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
