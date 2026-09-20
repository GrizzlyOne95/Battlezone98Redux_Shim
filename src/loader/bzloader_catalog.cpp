#include "bzloader_catalog.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cwctype>

namespace
{
    bool EqualsIgnoreCase(const std::string& left, const std::string& right)
    {
        if (left.size() != right.size()) return false;
        for (size_t i = 0; i < left.size(); ++i)
        {
            const auto a = static_cast<unsigned char>(left[i]);
            const auto b = static_cast<unsigned char>(right[i]);
            if (std::tolower(a) != std::tolower(b)) return false;
        }
        return true;
    }

    bool IsValidPluginId(const char* id)
    {
        if (!id || !*id) return false;
        for (const unsigned char* cursor =
                 reinterpret_cast<const unsigned char*>(id);
             *cursor;
             ++cursor)
        {
            if (!std::isalnum(*cursor) && *cursor != '.' && *cursor != '_' &&
                *cursor != '-')
                return false;
        }
        return true;
    }

    uint32_t GameMaskForId(uint32_t gameId)
    {
        switch (gameId)
        {
        case BZ_GAME_BATTLEZONE_15:
            return BZ_GAME_MASK_BATTLEZONE_15;
        case BZ_GAME_BATTLEZONE_98_REDUX:
            return BZ_GAME_MASK_BATTLEZONE_98_REDUX;
        default:
            return 0;
        }
    }
}

namespace BZLoader
{
    MetadataStatus ValidateMetadata(
        const BZHostApi& host,
        const BZPluginInfo& plugin,
        std::string& reason)
    {
        constexpr size_t minimumHostSize =
            offsetof(BZHostApi, log) + sizeof(BZHostApi::log);
        constexpr size_t minimumPluginSize =
            offsetof(BZPluginInfo, flags) + sizeof(BZPluginInfo::flags);

        if (host.structSize < minimumHostSize)
        {
            reason = "host API structure is smaller than ABI v1";
            return MetadataStatus::HostTooSmall;
        }
        if (plugin.structSize < minimumPluginSize)
        {
            reason = "plugin metadata structure is smaller than ABI v1";
            return MetadataStatus::PluginTooSmall;
        }
        if (plugin.requiredLoaderAbi != host.abiVersion)
        {
            reason = "required loader ABI does not match host ABI";
            return MetadataStatus::AbiMismatch;
        }
        if (!plugin.pluginId || !*plugin.pluginId || !plugin.pluginName ||
            !*plugin.pluginName || !plugin.pluginVersion || !*plugin.pluginVersion)
        {
            reason = "plugin ID, name, and version are required";
            return MetadataStatus::MissingIdentity;
        }
        if (!IsValidPluginId(plugin.pluginId))
        {
            reason = "plugin ID contains unsupported characters";
            return MetadataStatus::InvalidPluginId;
        }

        const uint32_t gameMask = GameMaskForId(host.gameId);
        if (gameMask != 0 && (plugin.supportedGameMask & gameMask) == 0)
        {
            reason = "plugin does not support the detected game";
            return MetadataStatus::UnsupportedGame;
        }
        if (plugin.supportedBuildId && *plugin.supportedBuildId &&
            (!host.executableBuildId ||
             std::string(plugin.supportedBuildId) != host.executableBuildId))
        {
            reason = "plugin build constraint does not match the executable";
            return MetadataStatus::UnsupportedBuild;
        }

        reason.clear();
        return MetadataStatus::Ok;
    }

    bool CatalogLess(const CatalogEntry& left, const CatalogEntry& right)
    {
        if (left.loadPriority != right.loadPriority)
            return left.loadPriority < right.loadPriority;

        std::string leftId = left.pluginId;
        std::string rightId = right.pluginId;
        std::transform(leftId.begin(), leftId.end(), leftId.begin(),
                       [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
        std::transform(rightId.begin(), rightId.end(), rightId.begin(),
                       [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
        if (leftId != rightId) return leftId < rightId;

        std::wstring leftPath = left.path;
        std::wstring rightPath = right.path;
        std::transform(leftPath.begin(), leftPath.end(), leftPath.begin(), towlower);
        std::transform(rightPath.begin(), rightPath.end(), rightPath.begin(), towlower);
        return leftPath < rightPath;
    }

    bool HasDuplicatePluginId(
        const std::vector<CatalogEntry>& entries,
        const std::string& candidateId)
    {
        return std::any_of(entries.begin(), entries.end(), [&](const CatalogEntry& entry) {
            return EqualsIgnoreCase(entry.pluginId, candidateId);
        });
    }

    std::wstring GetPluginDirectory(const std::wstring& loaderModulePath)
    {
        const size_t slash = loaderModulePath.find_last_of(L"\\/");
        if (slash == std::wstring::npos) return L"plugins";
        return loaderModulePath.substr(0, slash + 1) + L"plugins";
    }
}
