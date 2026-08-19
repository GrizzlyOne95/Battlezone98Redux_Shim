#pragma once
#include <cstdint>

/**
 * BZR Open Shim SDK
 *
 * Public interface for interacting with OpenShim from companion DLLs such as
 * Extra Utilities. The original v1 exports below remain source/binary stable.
 * SDK v2 adds one versioned function-table entry point so future capabilities
 * do not require every consumer to resolve a growing collection of exports.
 */

#ifdef BZROPENSHIM_EXPORTS
#define BZRO_API __declspec(dllexport)
#else
#define BZRO_API __declspec(dllimport)
#endif

namespace BZROpenShim
{
    // Latest public SDK interface version. v1 was the individual status exports
    // at the bottom of this header; v2 adds OpenShimGetApi().
    static constexpr uint32_t SDK_VERSION = 2;
    static constexpr uint32_t SDK_API_V2 = 2;

    enum OpenShimCapability : uint64_t
    {
        OPENSHIM_CAP_STATUS              = 1ull << 0,
        OPENSHIM_CAP_EVENT_QUEUE         = 1ull << 1,
        OPENSHIM_CAP_DEVELOPER_INSPECTOR = 1ull << 2,
        OPENSHIM_CAP_GAME_DISTRIBUTION   = 1ull << 3,
    };

    // Storefront/provenance classification for a qualified Battlezone build.
    // Unknown is deliberate: callers must fail closed when OpenShim has not
    // qualified the running executable rather than assuming "not Steam" means
    // GOG. The numeric values are part of the public ABI.
    enum class OpenShimGameDistribution : uint32_t
    {
        Unknown = 0,
        GOG     = 1,
        Steam   = 2,
    };

    enum class OpenShimEventType : uint32_t
    {
        None                      = 0,
        ShimInitialized           = 1,
        CompatibilityChanged      = 2,
        PatchingCompleted         = 3,
        ShutdownStarted           = 4,
        DeveloperSnapshotCaptured = 5,
    };

    // ABI-stable copied event record. No pointers into Battlezone/Ogre memory
    // cross this boundary. `sequence` is process-wide and monotonically
    // increasing. `text` is optional diagnostic context and always NUL-ended.
    struct OpenShimEvent
    {
        uint32_t structSize = sizeof(OpenShimEvent);
        uint32_t apiVersion = SDK_API_V2;
        uint32_t type = static_cast<uint32_t>(OpenShimEventType::None);
        uint32_t threadId = 0;
        uint64_t sequence = 0;
        uint64_t qpc = 0;
        uint64_t tickMs = 0;
        uint64_t arg0 = 0;
        uint64_t arg1 = 0;
        char text[64] = {};
    };

    // Read-only developer snapshot. New fields consume reserved storage where
    // possible so existing v2 consumers retain the same record size.
    struct OpenShimDeveloperSnapshot
    {
        uint32_t structSize = sizeof(OpenShimDeveloperSnapshot);
        uint32_t apiVersion = SDK_API_V2;
        uint64_t capabilities = 0;

        uint32_t shimVersion = 0;
        uint32_t sdkVersion = SDK_VERSION;
        uint32_t processId = 0;
        uint32_t captureThreadId = 0;

        uint32_t appliedPatchCount = 0;
        uint32_t pendingEventCount = 0;
        uint64_t droppedEventCount = 0;

        uint8_t compatibleGameVersion = 0;
        uint8_t patchingComplete = 0;
        uint8_t localPlayerResolved = 0;
        uint8_t reservedFlags = 0;

        float localPlayerX = 0.0f;
        float localPlayerY = 0.0f;
        float localPlayerZ = 0.0f;

        uint32_t gameDistribution = static_cast<uint32_t>(OpenShimGameDistribution::Unknown);
        uint32_t reserved[7] = {};
    };

    // All function pointers use cdecl explicitly so companion DLLs do not
    // inherit compiler defaults. Boolean results use uint8_t/int32_t at the
    // public ABI instead of C++ bool. New entries are append-only; consumers
    // must check structSize before calling fields added after their SDK copy.
    struct OpenShimApiV2
    {
        uint32_t structSize = sizeof(OpenShimApiV2);
        uint32_t apiVersion = SDK_API_V2;
        uint64_t capabilities = 0;

        uint32_t (__cdecl* getShimVersion)() = nullptr;
        uint32_t (__cdecl* getSdkVersion)() = nullptr;
        uint64_t (__cdecl* getCapabilities)() = nullptr;
        uint8_t  (__cdecl* isCompatibleGameVersion)() = nullptr;
        uint8_t  (__cdecl* isPatchingComplete)() = nullptr;
        uint32_t (__cdecl* getAppliedPatchCount)() = nullptr;

        int32_t  (__cdecl* pollEvent)(OpenShimEvent* outEvent) = nullptr;
        uint32_t (__cdecl* getPendingEventCount)() = nullptr;
        uint64_t (__cdecl* getDroppedEventCount)() = nullptr;
        void     (__cdecl* clearEventQueue)() = nullptr;

        int32_t  (__cdecl* captureDeveloperSnapshot)(OpenShimDeveloperSnapshot* outSnapshot) = nullptr;
        int32_t  (__cdecl* logDeveloperSnapshot)() = nullptr;

        // Added append-only to SDK v2. Returns OpenShimGameDistribution.
        uint32_t (__cdecl* getGameDistribution)() = nullptr;
    };

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

    /**
     * Versioned SDK entry point. requestedVersion=0 means "latest supported".
     * v2 is the first function-table ABI; requesting unsupported versions
     * returns nullptr rather than returning a partially compatible table.
     */
    extern "C" BZRO_API const OpenShimApiV2* __cdecl OpenShimGetApi(uint32_t requestedVersion);

    /**
     * Convenience exports for tools/companions that only need the read-only
     * developer snapshot and do not want to retain the v2 table pointer.
     */
    extern "C" BZRO_API int32_t __cdecl OpenShimCaptureDeveloperSnapshot(
        OpenShimDeveloperSnapshot* outSnapshot);
    extern "C" BZRO_API int32_t __cdecl OpenShimLogDeveloperSnapshot();
}
