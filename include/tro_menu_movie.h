#pragma once
#include <cstdint>

namespace BZROpenShim
{
    // Buffer the main-menu banner's movie push is pointed at ("TRO Banner
    // Movie Name"). Holds "bzone.ogv" until the single-player 98/TRO toggle
    // selects TRO, then "odyssey.ogv".
    const char* GetTroBannerMovieName();

    // Takes the rel32 call site of the SP mode refresh (call opcode address)
    // and returns the wrapper to point it at, or nullptr when the call does
    // not reach the expected routine (the site then stays stock).
    void* PrepareTroModeRefreshHook(uint32_t callAddress);

    // Called for each "TRO Banner Mode Refresh N/2" that applied (siteIndex
    // 0 or 1). Once patching is done, RestoreSavedTroMode seeds a saved TRO
    // mode from openshim.ini and enables saving, but only when both sites
    // are hooked.
    void NoteTroModeRefreshHookInstalled(unsigned siteIndex);
    void RestoreSavedTroMode();
}
