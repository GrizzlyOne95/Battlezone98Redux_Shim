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
        AbiMismatch,
        MissingIdentity,
        InvalidPluginId,
        UnsupportedGame,
        UnsupportedBuild
    };

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
