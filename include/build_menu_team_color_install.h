#pragma once
// Installer for the build menu team colour fix. See build_menu_team_color.h.

namespace BZROpenShim
{
    namespace BuildMenuTeamColor
    {
        // Clamps the build menu item team to the 3-entry colour array (max 2
        // instead of 3). Fail-closed on a byte-guard mismatch. Safe to call
        // repeatedly.
        void InstallBuildMenuTeamColorIfPossible();
    }
}
