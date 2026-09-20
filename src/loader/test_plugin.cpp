// Reference plugin for the BZLoader host lifecycle test. It is also the
// worked example of the append-only Query contract: it clamps itself to the
// capacity the host offered instead of refusing an older host, and reports
// how much it actually wrote.

#include "bzloader_plugin.h"

#include <string.h>

namespace
{
    const BZHostApi* g_Host = nullptr;
}

extern "C" BZLOADER_API int32_t BZLOADER_CALL BZPlugin_Query(
    uint32_t hostAbiVersion,
    BZPluginInfo* outInfo)
{
    if (!outInfo || hostAbiVersion != BZLOADER_ABI_VERSION) return 0;

    const uint32_t capacity = outInfo->structSize;
    if (capacity < BZLOADER_PLUGIN_INFO_V1_SIZE) return 0;

    const uint32_t written =
        capacity < sizeof(BZPluginInfo) ? capacity : (uint32_t)sizeof(BZPluginInfo);
    memset(outInfo, 0, written);

    outInfo->requiredLoaderAbi = BZLOADER_ABI_VERSION;
    outInfo->pluginId = "org.bzloader.test";
    outInfo->pluginName = "BZLoader lifecycle test plugin";
    outInfo->pluginVersion = "1.0.0";
    // Genuinely game-independent: it patches nothing and only exercises the
    // host. This is also what lets it load in an unrecognised host, which is
    // how the standalone integration test runs at all.
    outInfo->supportedGameMask = BZ_GAME_MASK_ANY;

    if (written >= BZLOADER_FIELD_END(BZPluginInfo, loadPriority))
        outInfo->loadPriority = 1000;

    outInfo->structSize = written;
    return 1;
}

extern "C" BZLOADER_API int32_t BZLOADER_CALL BZPlugin_Load(
    const BZHostApi* host)
{
    if (!host || host->structSize < BZLOADER_HOST_API_V1_SIZE ||
        host->abiVersion != BZLOADER_ABI_VERSION || !host->log)
        return 0;
    g_Host = host;
    g_Host->log(BZ_HOST_LOG_INFO, "org.bzloader.test", "Lifecycle test plugin loaded");
    return 1;
}

extern "C" BZLOADER_API void BZLOADER_CALL BZPlugin_Shutdown(void)
{
    if (g_Host && g_Host->log)
        g_Host->log(BZ_HOST_LOG_INFO, "org.bzloader.test", "Lifecycle test plugin shut down");
    g_Host = nullptr;
}
