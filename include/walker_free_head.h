#pragma once

namespace BZROpenShim
{
    // Walker free-turning head (Docs/WALKER_FREE_HEAD.md): opt-in per ODF
    // through [WalkerClass] torsoName, player-driven walker in single player
    // only. Wraps the Walker vtable's Simulate (slot 15) and PostSimulate
    // (slot 16) in place. Safe to call from the deferred-hook retry loop;
    // gives up for the session after one failed bind.
    void InstallWalkerFreeHeadIfPossible();
    bool IsWalkerFreeHeadInstalled();
}
