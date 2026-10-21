#pragma once

namespace BZROpenShim::Hooks
{
    // Moves GAS's playing-sound copy pool (stock: 100 entries) to a larger
    // OpenShim-owned array. Must run before the engine's audio init; it skips
    // itself when the stock pool is already initialised.
    // OPENSHIM_STOCK_SOUND_COPY_POOL=1 keeps the stock pool.
    void InstallGasCopyPoolIfPossible();
}
