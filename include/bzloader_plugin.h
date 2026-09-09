#pragma once

// BZLoader plugin ABI v1. This header is intentionally C-compatible: no C++
// classes, STL types, exceptions, or allocator ownership cross the DLL edge.

#include <stdint.h>
#include <stddef.h>

#if defined(_WIN32)
#define BZLOADER_CALL __cdecl
#if defined(BZLOADER_PLUGIN_BUILD)
#define BZLOADER_API __declspec(dllexport)
#else
#define BZLOADER_API
#endif
#else
#define BZLOADER_CALL
#define BZLOADER_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define BZLOADER_ABI_VERSION 1u
#define BZLOADER_VERSION 1u

enum BZGameId
{
    BZ_GAME_UNKNOWN = 0,
    BZ_GAME_BATTLEZONE_15 = 1,
    BZ_GAME_BATTLEZONE_98_REDUX = 2
};

#define BZ_GAME_MASK_BATTLEZONE_15 UINT32_C(1)
#define BZ_GAME_MASK_BATTLEZONE_98_REDUX UINT32_C(2)
#define BZ_GAME_MASK_ANY UINT32_C(0xffffffff)

enum BZHostLogLevel
{
    BZ_HOST_LOG_DEBUG = 0,
    BZ_HOST_LOG_INFO = 1,
    BZ_HOST_LOG_WARNING = 2,
    BZ_HOST_LOG_ERROR = 3
};

typedef void(BZLOADER_CALL* BZHostLogFn)(
    uint32_t level,
    const char* component,
    const char* message);

// All pointers in BZHostApi are owned by BZLoader and remain valid until
// BZPlugin_Shutdown returns. Plugins must copy data needed beyond that call.
// New fields may only be appended; readers must check structSize first.
typedef struct BZHostApi
{
    uint32_t structSize;
    uint32_t abiVersion;
    uint32_t loaderVersion;
    uint32_t gameId;
    const wchar_t* loaderDirectory;
    const wchar_t* executablePath;
    const char* executableBuildId;
    BZHostLogFn log;
} BZHostApi;

// String pointers are owned by the plugin module and must remain valid from a
// successful Query through Shutdown. dependencies/conflicts are optional,
// comma-separated plugin IDs; Phase 1 reports them but does not resolve them.
// supportedBuildId is optional. When non-empty it must exactly match the host
// build ID. New fields may only be appended.
typedef struct BZPluginInfo
{
    uint32_t structSize;
    uint32_t requiredLoaderAbi;
    const char* pluginId;
    const char* pluginName;
    const char* pluginVersion;
    uint32_t supportedGameMask;
    const char* supportedBuildId;
    const char* dependencies;
    const char* conflicts;
    int32_t loadPriority;
    uint32_t flags;
} BZPluginInfo;

typedef int32_t(BZLOADER_CALL* BZPluginQueryFn)(
    uint32_t hostAbiVersion,
    BZPluginInfo* outInfo);
typedef int32_t(BZLOADER_CALL* BZPluginLoadFn)(const BZHostApi* host);
typedef void(BZLOADER_CALL* BZPluginShutdownFn)(void);

// Required exports for every plugin.
BZLOADER_API int32_t BZLOADER_CALL BZPlugin_Query(
    uint32_t hostAbiVersion,
    BZPluginInfo* outInfo);
BZLOADER_API int32_t BZLOADER_CALL BZPlugin_Load(const BZHostApi* host);
BZLOADER_API void BZLOADER_CALL BZPlugin_Shutdown(void);

#ifdef __cplusplus
}
#endif
