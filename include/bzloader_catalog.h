#pragma once

#include "bzloader_plugin.h"

#include <string>
#include <vector>

namespace BZLoader
{
    struct CatalogEntry
    {
        std::wstring path;
        std::string pluginId;
        int32_t loadPriority = 0;
    };

    enum class MetadataStatus
    {
        Ok,
        HostTooSmall,
        PluginTooSmall,
        PluginTooLarge,
        AbiMismatch,
        MissingIdentity,
        InvalidPluginId,
        UnsupportedGame,
        UnsupportedBuild,
        ExecutableIdentityUnavailable
    };

    // Guarded reads of the optional BZPluginInfo tail. A plugin compiled
    // against an older header reports a smaller structSize and its missing
    // fields read back as these defaults instead of as whatever the host's
    // own buffer happened to contain. Nothing outside this header may touch
    // a tail field directly.
    const char* PluginBuildHint(const BZPluginInfo& plugin);
    const char* PluginDependencies(const BZPluginInfo& plugin);
    const char* PluginConflicts(const BZPluginInfo& plugin);
    int32_t PluginLoadPriority(const BZPluginInfo& plugin);
    uint32_t PluginFlags(const BZPluginInfo& plugin);
    const char* PluginExecutableSha256(const BZPluginInfo& plugin);

    // Guarded read of the optional BZHostApi tail, for symmetry: an OpenShim
    // build older than the loader it is hosted by must not read these either.
    BZHostExecutableSha256Fn HostExecutableSha256Fn(const BZHostApi& host);

    MetadataStatus ValidateMetadata(
        const BZHostApi& host,
        const BZPluginInfo& plugin,
        std::string& reason);

    bool CatalogLess(const CatalogEntry& left, const CatalogEntry& right);
    bool HasDuplicatePluginId(
        const std::vector<CatalogEntry>& entries,
        const std::string& candidateId);
    std::wstring GetPluginDirectory(const std::wstring& loaderModulePath);
}
