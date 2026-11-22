#pragma once
// Installer for the sniper kill credit fix. See sniper_kill_credit.h.

namespace BZROpenShim
{
    namespace SniperKillCredit
    {
        // Redirects the IsLocal call at 0x005D6FF7 in SniperShell::Hit so a
        // snipe on a craft this machine owns is credited in a network game.
        // Fail-closed: any byte-guard mismatch leaves the engine untouched.
        // Safe to call repeatedly.
        void InstallSniperKillCreditIfPossible();
    }
}
