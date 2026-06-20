#pragma once
#include <cstdint>

/**
 * BZR Open Shim SDK
 *
 * Public interface for interacting with the Open Shim from mission scripts
 * or other third-party DLLs.
 */

#ifdef BZROPENSHIM_EXPORTS
#define BZRO_API __declspec(dllexport)
#else
#define BZRO_API __declspec(dllimport)
#endif

namespace BZROpenShim
{
    // Current SDK Interface version
    static constexpr uint32_t SDK_VERSION = 1;

    /**
     * Retrieves the internal version of the shim.
     */
    BZRO_API uint32_t GetShimVersion();

    /**
     * Returns true if the shim has successfully detected the target game version.
     */
    BZRO_API bool IsCompatibleGameVersion();

    /**
     * Returns true if the memory patching process has completed.
     */
    BZRO_API bool IsPatchingComplete();

    /**
     * Returns the number of patches successfully applied to the process.
     */
    BZRO_API uint32_t GetAppliedPatchCount();

    /**
     * Explicit initialization entry point for the shim.
     * Normally called automatically by DLL_PROCESS_ATTACH, but can be
     * called manually if late-loading.
     */
    BZRO_API void Initialize();

    /**
     * Explicit shutdown and cleanup entry point.
     */
    BZRO_API void Shutdown();
}
