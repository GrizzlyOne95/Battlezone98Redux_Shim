#include "bzloader_plugin.h"

namespace
{
    const BZHostApi* g_Host = nullptr;
}

extern "C" BZLOADER_API int32_t BZLOADER_CALL BZPlugin_Query(
    uint32_t hostAbiVersion,
    BZPluginInfo* outInfo)
{
    if (!outInfo || hostAbiVersion != BZLOADER_ABI_VERSION ||
        outInfo->structSize < sizeof(BZPluginInfo))
        return 0;

    *outInfo = {
        sizeof(BZPluginInfo),
        BZLOADER_ABI_VERSION,
        "org.bzloader.test",
        "BZLoader lifecycle test plugin",
        "1.0.0",
        BZ_GAME_MASK_ANY,
        nullptr,
        nullptr,
        nullptr,
        1000,
        0};
    return 1;
}

extern "C" BZLOADER_API int32_t BZLOADER_CALL BZPlugin_Load(
    const BZHostApi* host)
{
    if (!host || host->abiVersion != BZLOADER_ABI_VERSION || !host->log)
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
