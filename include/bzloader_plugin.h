#pragma once

// BZLoader plugin ABI v1. This header is intentionally C-compatible: no C++
// classes, STL types, exceptions, or allocator ownership cross the DLL edge.
//
// ---------------------------------------------------------------------------
// Compatibility policy: true append-only structures
// ---------------------------------------------------------------------------
// Both shared structures are append-only. Each one has a *mandatory v1 prefix*
// that every conforming participant must provide, followed by optional tail
// fields that a participant may omit because it was compiled against an older
// header. Nothing is ever reordered, resized, or repurposed within ABI v1; a
// change that cannot be expressed as an append is ABI v2.
//
// `structSize` is the only thing that says which fields are really there, and
// it means two different things depending on direction:
//
//   * BZHostApi::structSize is the number of bytes the host actually filled.
//     A plugin must not read a field unless BZLOADER_FIELD_END covers it.
//
//   * BZPluginInfo::structSize is the buffer CAPACITY on the way in and the
//     number of bytes WRITTEN on the way out. A plugin compiled against a
//     newer header must clamp itself to the capacity it was handed instead of
//     refusing to load, and must report what it wrote. The host then reads
//     only the fields that reported size covers.
//
// Use BZLOADER_HAS_FIELD for every optional access on both sides. The host
// implementation reads the BZPluginInfo tail exclusively through the guarded
// accessors in bzloader_catalog.h, and the bundled plugins fill BZPluginInfo
// through the guarded pattern documented on BZPlugin_Query below.

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

// Byte offset one past the end of a struct field. The null-pointer expression
// is never evaluated; it only supplies a type to sizeof.
#define BZLOADER_FIELD_END(type, field) \
    ((uint32_t)(offsetof(type, field) + sizeof(((type*)0)->field)))

// True when a filled structure is large enough to contain an optional field.
#define BZLOADER_HAS_FIELD(instance, type, field) \
    ((instance).structSize >= BZLOADER_FIELD_END(type, field))

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

// Returns the lowercase hex SHA-256 of the host executable, or NULL when it
// could not be computed. The host owns the string and computes it lazily on
// first call, so a plugin that never gates on the exact image never pays the
// file read. Unlike executableBuildHint this is a real image identity and is
// safe to use as a load gate.
typedef const char*(BZLOADER_CALL* BZHostExecutableSha256Fn)(void);

// All pointers in BZHostApi are owned by BZLoader and remain valid until
// BZPlugin_Shutdown returns. Plugins must copy data needed beyond that call.
typedef struct BZHostApi
{
    // -- mandatory v1 prefix; always present -------------------------------
    uint32_t structSize;
    uint32_t abiVersion;
    uint32_t loaderVersion;
    uint32_t gameId;
    const wchar_t* loaderDirectory;
    const wchar_t* executablePath;
    // Coarse, cheap build *hint* of the form "pe-<TimeDateStamp>-<SizeOfImage>",
    // or "unknown". Two different builds can collide here and a relinked build
    // can differ here without any behavioural change, so this is a filter and a
    // log token -- never a patch-safety gate. Use getExecutableSha256 when the
    // answer has to be authoritative.
    const char* executableBuildHint;
    BZHostLogFn log;

    // -- optional appended fields; guard with BZLOADER_HAS_FIELD -----------
    // The raw PE values behind executableBuildHint, so a plugin does not have
    // to parse the hint string back apart. Zero when they could not be read.
    uint32_t executableTimeDateStamp;
    uint32_t executableSizeOfImage;
    BZHostExecutableSha256Fn getExecutableSha256;
} BZHostApi;

// Everything a conforming host must fill.
#define BZLOADER_HOST_API_V1_SIZE BZLOADER_FIELD_END(BZHostApi, log)

// String pointers are owned by the plugin module and must remain valid from a
// successful Query through Shutdown.
typedef struct BZPluginInfo
{
    // -- mandatory v1 prefix; every plugin must fill all of this -----------
    uint32_t structSize;
    uint32_t requiredLoaderAbi;
    const char* pluginId;
    const char* pluginName;
    const char* pluginVersion;
    // Which games this plugin is willing to load into. A plugin that runs
    // anywhere must say so with BZ_GAME_MASK_ANY: in a host whose executable
    // was not recognised, BZLoader loads only plugins that declare exactly
    // that, and rejects anything that enumerated specific games.
    uint32_t supportedGameMask;

    // -- optional appended fields; guard with BZLOADER_HAS_FIELD -----------
    // Optional coarse prefilter matched against BZHostApi::executableBuildHint.
    // Same weakness as the host field: treat a match as "probably the right
    // build", not as permission to write bytes into that image.
    const char* supportedBuildHint;
    // Optional comma-separated plugin IDs. Diagnostic only in ABI v1: BZLoader
    // reports them and infers no load order from them.
    const char* dependencies;
    const char* conflicts;
    int32_t loadPriority;
    uint32_t flags;
    // Optional lowercase hex SHA-256 of the one executable image this plugin
    // will load into. When present it is an exact, authoritative gate: the
    // host computes the real digest and refuses the plugin on any mismatch,
    // including when the digest cannot be computed at all.
    const char* supportedExecutableSha256;
} BZPluginInfo;

// Everything a conforming plugin must fill.
#define BZLOADER_PLUGIN_INFO_V1_SIZE \
    BZLOADER_FIELD_END(BZPluginInfo, supportedGameMask)

typedef int32_t(BZLOADER_CALL* BZPluginQueryFn)(
    uint32_t hostAbiVersion,
    BZPluginInfo* outInfo);
typedef int32_t(BZLOADER_CALL* BZPluginLoadFn)(const BZHostApi* host);
typedef void(BZLOADER_CALL* BZPluginShutdownFn)(void);

// Required exports for every plugin.
//
// BZPlugin_Query receives outInfo->structSize as the host's buffer CAPACITY.
// The conforming shape is:
//
//     const uint32_t capacity = outInfo->structSize;
//     if (capacity < BZLOADER_PLUGIN_INFO_V1_SIZE) return 0;   // pre-v1 host
//     memset(outInfo, 0, capacity < sizeof(*outInfo) ? capacity : sizeof(*outInfo));
//     ... fill the v1 prefix ...
//     if (capacity >= BZLOADER_FIELD_END(BZPluginInfo, loadPriority))
//         outInfo->loadPriority = 1000;                        // optional tail
//     outInfo->structSize =
//         capacity < sizeof(*outInfo) ? capacity : (uint32_t)sizeof(*outInfo);
//     return 1;
//
// Never write past the capacity, and never refuse a host merely for being
// older than the header you compiled against.
//
// A failed BZPlugin_Load must be transactional: return only after undoing any
// partial initialization, because the host does not call BZPlugin_Shutdown for
// a plugin that never became active.
BZLOADER_API int32_t BZLOADER_CALL BZPlugin_Query(
    uint32_t hostAbiVersion,
    BZPluginInfo* outInfo);
BZLOADER_API int32_t BZLOADER_CALL BZPlugin_Load(const BZHostApi* host);
BZLOADER_API void BZLOADER_CALL BZPlugin_Shutdown(void);

#ifdef __cplusplus
}
#endif
