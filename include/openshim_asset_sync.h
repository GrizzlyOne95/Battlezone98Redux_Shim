#pragma once

namespace BZROpenShim
{
    // Starts a worker that syncs the Workshop item's asset sets (Enhanced
    // renderer resources, custom UI tiles) into the game folder when the
    // manifest declares them and describes this exact build. See
    // Docs/UPDATE_ASSET_SETS.md.
    void StartOpenShimAssetSync();

    // Joins the worker with a bounded wait.
    void ShutdownOpenShimAssetSync();
}
