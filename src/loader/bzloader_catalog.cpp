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

    bool EqualsIgnoreCaseC(const char* left, const char* right)
    {
        if (!left || !right) return false;
        while (*left && *right)
        {
            const auto a = static_cast<unsigned char>(*left++);
            const auto b = static_cast<unsigned char>(*right++);
            if (std::tolower(a) != std::tolower(b)) return false;
        }
        return *left == *right;
    }
}

namespace BZLoader
{
    const char* PluginBuildHint(const BZPluginInfo& plugin)
    {
        return BZLOADER_HAS_FIELD(plugin, BZPluginInfo, supportedBuildHint)
                   ? plugin.supportedBuildHint
                   : nullptr;
    }

    const char* PluginDependencies(const BZPluginInfo& plugin)
    {
        return BZLOADER_HAS_FIELD(plugin, BZPluginInfo, dependencies)
                   ? plugin.dependencies
                   : nullptr;
    }

    const char* PluginConflicts(const BZPluginInfo& plugin)
    {
        return BZLOADER_HAS_FIELD(plugin, BZPluginInfo, conflicts)
                   ? plugin.conflicts
                   : nullptr;
    }

    int32_t PluginLoadPriority(const BZPluginInfo& plugin)
    {
        return BZLOADER_HAS_FIELD(plugin, BZPluginInfo, loadPriority)
                   ? plugin.loadPriority
                   : 0;
    }

    uint32_t PluginFlags(const BZPluginInfo& plugin)
    {
        return BZLOADER_HAS_FIELD(plugin, BZPluginInfo, flags) ? plugin.flags : 0u;
    }

    const char* PluginExecutableSha256(const BZPluginInfo& plugin)
    {
        return BZLOADER_HAS_FIELD(plugin, BZPluginInfo, supportedExecutableSha256)
                   ? plugin.supportedExecutableSha256
                   : nullptr;
    }

    BZHostExecutableSha256Fn HostExecutableSha256Fn(const BZHostApi& host)
    {
        return BZLOADER_HAS_FIELD(host, BZHostApi, getExecutableSha256)
                   ? host.getExecutableSha256
                   : nullptr;
    }

    MetadataStatus ValidateMetadata(
        const BZHostApi& host,
        const BZPluginInfo& plugin,
        std::string& reason)
    {
        if (host.structSize < BZLOADER_HOST_API_V1_SIZE)
        {
            reason = "host API structure is smaller than the ABI v1 prefix";
            return MetadataStatus::HostTooSmall;
        }
        if (plugin.structSize < BZLOADER_PLUGIN_INFO_V1_SIZE)
        {
            reason = "plugin metadata structure is smaller than the ABI v1 prefix";
            return MetadataStatus::PluginTooSmall;
        }
        // The buffer belongs to the host. A plugin claiming it wrote more than
        // the host offered means one of them is out of contract, and every
        // tail read past this point would be off the end of that buffer.
        if (plugin.structSize > sizeof(BZPluginInfo))
        {
            reason = "plugin reported more metadata than the host buffer holds";
            return MetadataStatus::PluginTooLarge;
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

        // Game gating is fail-closed. A recognised host requires its own bit;
        // an unrecognised host admits only a plugin that explicitly claims
        // every game, because a plugin that enumerated the games it supports
        // has already said this is not one of them.
        const uint32_t gameMask = GameMaskForId(host.gameId);
        if (gameMask != 0)
        {
            if ((plugin.supportedGameMask & gameMask) == 0)
            {
                reason = "plugin does not support the detected game";
                return MetadataStatus::UnsupportedGame;
            }
        }
        else if (plugin.supportedGameMask != BZ_GAME_MASK_ANY)
        {
            reason = "host executable was not recognised and the plugin is "
                     "not declared game-independent";
            return MetadataStatus::UnsupportedGame;
        }

        const char* buildHint = PluginBuildHint(plugin);
        if (buildHint && *buildHint &&
            !EqualsIgnoreCaseC(buildHint, host.executableBuildHint))
        {
            reason = "plugin build hint does not match the executable";
            return MetadataStatus::UnsupportedBuild;
        }

        // An exact-image constraint is authoritative, so it fails closed on
        // every way of not knowing: no host support for the digest, no digest
        // available, or a digest that differs.
        const char* wantedSha = PluginExecutableSha256(plugin);
        if (wantedSha && *wantedSha)
        {
            const BZHostExecutableSha256Fn fn = HostExecutableSha256Fn(host);
            const char* actual = fn ? fn() : nullptr;
            if (!actual)
            {
                reason = "plugin pins an executable SHA-256 the host cannot compute";
                return MetadataStatus::ExecutableIdentityUnavailable;
            }
            if (!EqualsIgnoreCaseC(wantedSha, actual))
            {
                reason = "plugin executable SHA-256 does not match the running image";
                return MetadataStatus::UnsupportedBuild;
            }
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
