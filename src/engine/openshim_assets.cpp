#include "openshim_assets.h"
#include "render_profile_resources.h"
#include "shim_log.h"

// Engine- and OS-independent. This translation unit is compiled by the Linux
// CTest workflow as well as by the Win32 DLL, so it must not include
// <Windows.h> or call any Win32 API. Process and openshim.ini lookups live in
// src/engine/openshim_assets_platform.cpp behind ResolveAssetRuntimeEnvironment().

#include <algorithm>
#include <cctype>
#include <chrono>
#include <fstream>
#include <mutex>
#include <shared_mutex>
#include <sstream>
#include <vector>

namespace BZROpenShim::Assets
{

namespace
{
std::shared_mutex g_lock;
AssetCapabilities g_caps = {};
bool g_initialized = false;
bool g_loggedOnce = false;

uint64_t MonotonicMilliseconds()
{
    using namespace std::chrono;
    return static_cast<uint64_t>(
        duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count());
}

void AppendUniquePath(std::vector<std::filesystem::path>& out,
                      const std::filesystem::path& candidate)
{
    if (candidate.empty())
        return;
    if (std::find(out.begin(), out.end(), candidate) != out.end())
        return;
    out.push_back(candidate);
}

std::filesystem::path TryGetWorkshopContentDirectory(
    const std::filesystem::path& gameDir)
{
    if (gameDir.empty())
        return {};
    const auto normalized = gameDir.lexically_normal().string();
    // Match on a separator-agnostic lowercase copy so the same marker works
    // for Windows paths and for the POSIX-style paths the unit tests build.
    std::string lower = normalized;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char ch) {
                       if (ch == '\\')
                           return '/';
                       return static_cast<char>(std::tolower(ch));
                   });
    constexpr const char* kMarker = "/steamapps/common/";
    const size_t pos = lower.find(kMarker);
    if (pos == std::string::npos)
        return {};
    return std::filesystem::path(normalized.substr(0, pos)) /
           "steamapps" / "workshop" / "content" / "301650";
}

void AppendImmediateSubdirectories(
    const std::filesystem::path& parent,
    std::vector<std::filesystem::path>& results)
{
    if (parent.empty())
        return;
    std::error_code ec;
    if (!std::filesystem::exists(parent, ec) || ec)
        return;
    for (std::filesystem::directory_iterator it(parent, ec), end;
         !ec && it != end;
         it.increment(ec))
    {
        if (ec)
            break;
        const auto& entry = *it;
        if (entry.is_directory(ec) && !ec)
            AppendUniquePath(results, entry.path());
    }
}

std::vector<std::filesystem::path> GetCampaignContentRootCandidates(
    const std::filesystem::path& gameDir)
{
    std::vector<std::filesystem::path> candidates;
    if (gameDir.empty())
        return candidates;
    AppendImmediateSubdirectories(gameDir / "addon", candidates);
    AppendImmediateSubdirectories(gameDir / "mods", candidates);
    AppendImmediateSubdirectories(gameDir / "packaged_mods", candidates);
    AppendImmediateSubdirectories(TryGetWorkshopContentDirectory(gameDir), candidates);
    return candidates;
}

bool ReadTextFile(const std::filesystem::path& path, std::string& out)
{
    out.clear();
    std::ifstream file(path, std::ios::binary);
    if (!file)
        return false;
    std::ostringstream ss;
    ss << file.rdbuf();
    out = ss.str();
    return true;
}

bool FileExistsNonEmpty(const std::filesystem::path& path)
{
    std::error_code ec;
    if (!std::filesystem::is_regular_file(path, ec) || ec)
        return false;
    auto sz = std::filesystem::file_size(path, ec);
    return !ec && sz > 0;
}

} // anonymous

const char* AssetPackStateName(AssetPackState state) noexcept
{
    switch (state)
    {
    case AssetPackState::Unknown:
        return "Unknown";
    case AssetPackState::NotDetected:
        return "NotDetected";
    case AssetPackState::Detected:
        return "Detected";
    case AssetPackState::Incompatible:
        return "Incompatible";
    default:
        return "Unknown";
    }
}

std::string TrimAssetString(const std::string& value)
{
    size_t start = 0;
    while (start < value.size() &&
           std::isspace(static_cast<unsigned char>(value[start])))
        ++start;
    size_t end = value.size();
    while (end > start &&
           std::isspace(static_cast<unsigned char>(value[end - 1])))
        --end;
    return value.substr(start, end - start);
}

bool AssetStringEqualsNoCase(const std::string& a, const std::string& b)
{
    if (a.size() != b.size())
        return false;
    for (size_t i = 0; i < a.size(); ++i)
    {
        if (std::tolower(static_cast<unsigned char>(a[i])) !=
            std::tolower(static_cast<unsigned char>(b[i])))
            return false;
    }
    return true;
}

bool ParseAssetManifestKeyValue(const std::string& line,
                                std::string& outKey,
                                std::string& outValue)
{
    outKey.clear();
    outValue.clear();
    std::string trimmed = TrimAssetString(line);
    if (trimmed.empty())
        return false;
    if (trimmed[0] == '#' || trimmed[0] == ';' ||
        trimmed[0] == '/' )
        return false;
    if (trimmed.front() == '[') // section header
        return false;
    const size_t eq = trimmed.find('=');
    if (eq == std::string::npos)
        return false;
    outKey = TrimAssetString(trimmed.substr(0, eq));
    outValue = TrimAssetString(trimmed.substr(eq + 1));
    for (size_t i = 0; i < outValue.size(); ++i)
    {
        if ((outValue[i] == '#' || outValue[i] == ';') &&
            (i == 0 || std::isspace(static_cast<unsigned char>(outValue[i - 1]))))
        {
            outValue = TrimAssetString(outValue.substr(0, i));
            break;
        }
    }
    return !outKey.empty();
}

static bool ParseBoolToken(const std::string& raw, bool& out)
{
    std::string v = TrimAssetString(raw);
    std::transform(v.begin(), v.end(), v.begin(),
                   [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
    if (v == "1" || v == "true" || v == "on" || v == "yes" || v == "enabled")
    {
        out = true;
        return true;
    }
    if (v == "0" || v == "false" || v == "off" || v == "no" || v == "disabled")
    {
        out = false;
        return true;
    }
    return false;
}

bool ParseAssetManifestContent(const std::string& text,
                               AssetCapabilities& out,
                               std::string& outProblem)
{
    out = {};
    outProblem.clear();
    out.expectedVersion = kAssetPackExpectedVersion;
    out.expectedFormatVersion = kAssetManifestExpectedFormatVersion;
    out.expectedCompatibilityVersion = kAssetManifestExpectedCompatibilityVersion;
    out.state = AssetPackState::Detected;
    out.manifestDetected = true;
    out.packDetected = true;

    bool haveSection = false;
    bool haveFormat = false;
    bool haveCompat = false;
    bool haveVersionAlias = false;
    std::string formatVal, compatVal, versionAliasVal;
    bool chunkMeshesFlag = false;
    bool enhancedFlag = false;
    bool customUiFlag = false;
    bool terrainHdFlag = false;
    bool chunkSeen = false;
    bool enhancedSeen = false;
    bool customSeen = false;
    bool terrainSeen = false;

    std::istringstream iss(text);
    std::string line;
    while (std::getline(iss, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        std::string trimmed = TrimAssetString(line);
        if (trimmed.empty() || trimmed[0] == '#' || trimmed[0] == ';')
            continue;
        if (trimmed.front() == '[' && trimmed.back() == ']')
        {
            std::string sec = TrimAssetString(trimmed.substr(1, trimmed.size() - 2));
            if (AssetStringEqualsNoCase(sec, "OpenShimAssets"))
                haveSection = true;
            continue;
        }
        if (!haveSection)
            continue;
        std::string key, value;
        if (!ParseAssetManifestKeyValue(line, key, value))
            continue;
        if (AssetStringEqualsNoCase(key, "FormatVersion"))
        {
            haveFormat = true;
            formatVal = value;
            out.installedFormatVersion = value;
        }
        else if (AssetStringEqualsNoCase(key, "CompatibilityVersion") ||
                 AssetStringEqualsNoCase(key, "CompatVersion"))
        {
            haveCompat = true;
            compatVal = value;
            out.installedCompatibilityVersion = value;
        }
        else if (AssetStringEqualsNoCase(key, "Version"))
        {
            haveVersionAlias = true;
            versionAliasVal = value;
            out.installedVersion = value;
            // Legacy alias: Version= maps to CompatibilityVersion if not already set
            if (!haveCompat)
            {
                haveCompat = true;
                compatVal = value;
                out.installedCompatibilityVersion = value;
            }
        }
        else if (AssetStringEqualsNoCase(key, "ChunkMeshes") ||
                 AssetStringEqualsNoCase(key, "DestructionChunks") ||
                 AssetStringEqualsNoCase(key, "ChunkMeshProxy"))
        {
            bool b = false;
            if (ParseBoolToken(value, b))
            {
                chunkMeshesFlag = b;
                chunkSeen = true;
            }
        }
        else if (AssetStringEqualsNoCase(key, "EnhancedResources") ||
                 AssetStringEqualsNoCase(key, "EnhancedEffects") ||
                 AssetStringEqualsNoCase(key, "EnhancedRenderer"))
        {
            bool b = false;
            if (ParseBoolToken(value, b))
            {
                enhancedFlag = b;
                enhancedSeen = true;
            }
        }
        else if (AssetStringEqualsNoCase(key, "CustomUI") ||
                 AssetStringEqualsNoCase(key, "CustomUiAssets"))
        {
            bool b = false;
            if (ParseBoolToken(value, b))
            {
                customUiFlag = b;
                customSeen = true;
            }
        }
        else if (AssetStringEqualsNoCase(key, "TerrainHd") ||
                 AssetStringEqualsNoCase(key, "TerrainHD") ||
                 AssetStringEqualsNoCase(key, "HdTerrain"))
        {
            bool b = false;
            if (ParseBoolToken(value, b))
            {
                terrainHdFlag = b;
                terrainSeen = true;
            }
        }
    }

    // If no OpenShimAssets section, treat as malformed
    if (!haveSection)
    {
        outProblem = "manifest missing [OpenShimAssets] section";
        out.state = AssetPackState::Incompatible;
        out.manifestDetected = true;
        out.packDetected = false;
        out.formatCompatible = false;
        out.compatibilityCompatible = false;
        out.versionCompatible = false;
        out.destructionChunks = false;
        out.enhancedResources = false;
        out.customUiAssets = false;
        out.terrainHd = false;
        return false;
    }

    // Fill defaults for missing format/compat when only Version alias present
    if (!haveFormat)
    {
        // Old manifests with only Version= are assumed FormatVersion=1
        out.installedFormatVersion = kAssetManifestExpectedFormatVersion;
        haveFormat = true;
        formatVal = out.installedFormatVersion;
    }
    if (!haveCompat && haveVersionAlias)
    {
        // Already handled via alias
    }
    if (!haveFormat || !haveCompat)
    {
        // Missing required version keys
        if (!haveCompat)
        {
            outProblem = "manifest missing CompatibilityVersion (or Version)";
            out.state = AssetPackState::Incompatible;
            out.packDetected = false;
            out.formatCompatible = false;
            out.compatibilityCompatible = false;
            out.versionCompatible = false;
            out.destructionChunks = false;
            out.enhancedResources = false;
            out.customUiAssets = false;
            out.terrainHd = false;
            return false;
        }
    }

    // Keep legacy installedVersion alias in sync
    if (!haveVersionAlias && haveCompat)
        out.installedVersion = compatVal;
    if (out.installedFormatVersion.empty())
        out.installedFormatVersion = formatVal;
    if (out.installedCompatibilityVersion.empty())
        out.installedCompatibilityVersion = compatVal;

    // Compatibility checks
    out.formatCompatible =
        (out.installedFormatVersion == kAssetManifestExpectedFormatVersion ||
         out.installedFormatVersion == "1.0");
    out.compatibilityCompatible =
        (out.installedCompatibilityVersion == kAssetManifestExpectedCompatibilityVersion ||
         out.installedCompatibilityVersion == "1.0" ||
         out.installedCompatibilityVersion == kAssetPackExpectedVersion ||
         out.installedCompatibilityVersion == kAssetPackExpectedVersionAlt);
    // Legacy alias
    out.versionCompatible = out.compatibilityCompatible;
    out.expectedVersion = kAssetPackExpectedVersion;
    out.expectedFormatVersion = kAssetManifestExpectedFormatVersion;
    out.expectedCompatibilityVersion = kAssetManifestExpectedCompatibilityVersion;

    if (!out.formatCompatible)
    {
        outProblem = "format version mismatch installed=" + out.installedFormatVersion +
                     " expected=" + out.expectedFormatVersion;
        out.state = AssetPackState::Incompatible;
        out.packDetected = false;
        out.destructionChunks = false;
        out.enhancedResources = false;
        out.customUiAssets = false;
        out.terrainHd = false;
        return false;
    }
    if (!out.compatibilityCompatible)
    {
        outProblem = "compatibility version mismatch installed=" + out.installedCompatibilityVersion +
                     " expected=" + out.expectedCompatibilityVersion;
        out.state = AssetPackState::Incompatible;
        out.packDetected = false;
        out.destructionChunks = false;
        out.enhancedResources = false;
        out.customUiAssets = false;
        out.terrainHd = false;
        return false;
    }

    // Versions compatible: interpret capability flags
    if (!chunkSeen && !enhancedSeen && !customSeen && !terrainSeen)
    {
        out.destructionChunks = true;
        out.enhancedResources = true;
        out.customUiAssets = true;
        out.terrainHd = false; // HD terrain remains opt-in even when pack present
    }
    else
    {
        out.destructionChunks = chunkSeen ? chunkMeshesFlag : false;
        out.enhancedResources = enhancedSeen ? enhancedFlag : false;
        out.customUiAssets = customSeen ? customUiFlag : false;
        out.terrainHd = terrainSeen ? terrainHdFlag : false;
    }

    out.manifestDetected = true;
    out.packDetected = true;
    out.state = AssetPackState::Detected;
    return true;
}

bool ProbeDestructionChunksAt(const std::filesystem::path& gameDir,
                              std::string& outProblem)
{
    outProblem.clear();
    if (gameDir.empty())
    {
        outProblem = "game directory unavailable";
        return false;
    }
    const char* dirNames[] = {"chunkMeshes", "Chunks"};
    auto candidates = GetCampaignContentRootCandidates(gameDir);
    for (const auto& root : candidates)
    {
        for (const char* dn : dirNames)
        {
            const auto chunkDir = root / dn;
            std::error_code ec;
            if (!std::filesystem::is_directory(chunkDir, ec) || ec)
                continue;
            const auto manifest = chunkDir / "chunk_geo_manifest.txt";
            if (std::filesystem::is_regular_file(manifest, ec) && !ec)
            {
                const auto p1 = chunkDir / "chunk1" / "chunk1.mesh";
                const auto p2 = chunkDir / "generic" / "iechunk1.mesh";
                if (FileExistsNonEmpty(p1) || FileExistsNonEmpty(p2) ||
                    std::filesystem::exists(manifest, ec))
                {
                    return true;
                }
            }
            std::error_code iterEc;
            for (std::filesystem::directory_iterator it(chunkDir, iterEc), end;
                 !iterEc && it != end; it.increment(iterEc))
            {
                if (iterEc) break;
                if (it->is_directory(iterEc) && !iterEc)
                {
                    std::error_code subEc;
                    for (std::filesystem::directory_iterator sub(it->path(), subEc), subEnd;
                         !subEc && sub != subEnd; sub.increment(subEc))
                    {
                        if (subEc) break;
                        const auto& p = sub->path();
                        if (p.extension() == ".mesh" && FileExistsNonEmpty(p))
                            return true;
                    }
                }
                else
                {
                    const auto& p = it->path();
                    if (p.extension() == ".mesh" && FileExistsNonEmpty(p))
                        return true;
                }
            }
        }
    }
    const auto stockDir = gameDir / "BZ_ASSETS" / "common" / "models" / "OpenShimChunkPayloads";
    std::error_code ec;
    if (std::filesystem::is_directory(stockDir, ec) && !ec)
    {
        for (std::filesystem::directory_iterator it(stockDir, ec), end;
             !ec && it != end; it.increment(ec))
        {
            if (ec) break;
            const auto& p = it->path();
            if (p.extension() == ".mesh" && FileExistsNonEmpty(p))
                return true;
        }
    }
    for (const char* dn : dirNames)
    {
        const auto direct = gameDir / dn;
        if (std::filesystem::is_directory(direct, ec) && !ec)
        {
            const auto manifest = direct / "chunk_geo_manifest.txt";
            if (FileExistsNonEmpty(manifest))
                return true;
            for (std::filesystem::directory_iterator it(direct, ec), end;
                 !ec && it != end; it.increment(ec))
            {
                if (ec) break;
                const auto& p = it->path();
                if (p.extension() == ".mesh" && FileExistsNonEmpty(p))
                    return true;
            }
        }
    }
    outProblem = "no chunk payload directories/files found";
    return false;
}

bool ProbeEnhancedResourcesAt(const std::filesystem::path& gameDir,
                              std::string& outProblem)
{
    outProblem.clear();
    if (gameDir.empty())
    {
        outProblem = "game directory unavailable";
        return false;
    }
    const std::filesystem::path resDir =
        gameDir / RenderProfiles::kEnhancedResourceDirRel;
    return RenderProfiles::ValidateDeployedResourceSetAt(resDir, outProblem);
}

std::filesystem::path ResolveTerrainHdManifestPathAt(
    const std::filesystem::path& gameDir,
    const std::string& configuredManifest)
{
    // Mirrors terrain_proxy.cpp ResolveHdManifestPath(): absolute wins, relative
    // is resolved against the game directory, empty means "no manifest".
    const std::string configured = TrimAssetString(configuredManifest);
    if (configured.empty())
        return {};
    std::filesystem::path path(configured);
    if (path.is_absolute())
        return path.lexically_normal();
    if (gameDir.empty())
        return {};
    return (gameDir / path).lexically_normal();
}

bool ProbeTerrainHdAt(const std::filesystem::path& gameDir,
                      const std::string& configuredManifest,
                      std::string& outProblem)
{
    outProblem.clear();
    const std::filesystem::path manifest =
        ResolveTerrainHdManifestPathAt(gameDir, configuredManifest);
    if (manifest.empty())
    {
        outProblem = TrimAssetString(configuredManifest).empty()
                         ? "terrain HD manifest not configured"
                         : "game directory unavailable";
        return false;
    }
    if (FileExistsNonEmpty(manifest))
        return true;
    outProblem = "terrain HD manifest not found at " + manifest.string();
    return false;
}

AssetCapabilities EvaluateAssetCapabilitiesAtWithManifest(
    const std::filesystem::path& gameDir,
    const std::string& manifestText,
    const std::string& configuredTerrainHdManifest)
{
    AssetCapabilities caps;
    caps.expectedVersion = kAssetPackExpectedVersion;
    caps.expectedFormatVersion = kAssetManifestExpectedFormatVersion;
    caps.expectedCompatibilityVersion = kAssetManifestExpectedCompatibilityVersion;
    caps.state = AssetPackState::NotDetected;

    std::string manifestProblem;
    bool manifestPresent = !manifestText.empty();
    AssetCapabilities manifestCaps;
    bool manifestValid = false;
    if (manifestPresent)
    {
        manifestValid = ParseAssetManifestContent(manifestText, manifestCaps, manifestProblem);
        caps.manifestDetected = true;
        caps.installedVersion = manifestCaps.installedVersion;
        caps.installedFormatVersion = manifestCaps.installedFormatVersion;
        caps.installedCompatibilityVersion = manifestCaps.installedCompatibilityVersion;
        caps.expectedVersion = manifestCaps.expectedVersion;
        caps.expectedFormatVersion = manifestCaps.expectedFormatVersion;
        caps.expectedCompatibilityVersion = manifestCaps.expectedCompatibilityVersion;
        if (!manifestValid)
        {
            // Malformed or version-incompatible manifest: do NOT trust filesystem capabilities
            // for pack identity, but still probe for diagnostics.
            caps.state = AssetPackState::Incompatible;
            caps.packDetected = false;
            caps.manifestDetected = true;
            caps.formatCompatible = manifestCaps.formatCompatible;
            caps.compatibilityCompatible = manifestCaps.compatibilityCompatible;
            caps.versionCompatible = false;
            caps.problem = manifestProblem.empty() ? "malformed manifest" : manifestProblem;
            // Probe filesystem only for reporting, but keep pack false and groups false
            // to prevent enabling on stale pack.
            std::string chunkP, enhP, terrainP;
            ProbeDestructionChunksAt(gameDir, chunkP);
            ProbeEnhancedResourcesAt(gameDir, enhP);
            ProbeTerrainHdAt(gameDir, configuredTerrainHdManifest, terrainP);
            caps.destructionChunks = false;
            caps.enhancedResources = false;
            caps.customUiAssets = false;
            caps.terrainHd = false;
            return caps;
        }
        if (!manifestCaps.formatCompatible || !manifestCaps.compatibilityCompatible)
        {
            caps.state = AssetPackState::Incompatible;
            caps.packDetected = false;
            caps.formatCompatible = manifestCaps.formatCompatible;
            caps.compatibilityCompatible = manifestCaps.compatibilityCompatible;
            caps.versionCompatible = false;
            caps.problem = manifestProblem.empty()
                               ? ("version mismatch " + caps.installedVersion)
                               : manifestProblem;
            caps.destructionChunks = false;
            caps.enhancedResources = false;
            caps.customUiAssets = false;
            caps.terrainHd = false;
            return caps;
        }
        // manifest valid and compatible
        caps.manifestDetected = true;
        caps.formatCompatible = true;
        caps.compatibilityCompatible = true;
        caps.versionCompatible = true;
    }
    else
    {
        caps.manifestDetected = false;
        caps.formatCompatible = false;
        caps.compatibilityCompatible = false;
        caps.versionCompatible = false;
    }

    // Instrumented filesystem probes - measure wall time
    uint64_t t0 = MonotonicMilliseconds();
    std::string chunkProblem, enhProblem, terrainProblem;
    const bool haveChunks = ProbeDestructionChunksAt(gameDir, chunkProblem);
    const bool haveEnhanced = ProbeEnhancedResourcesAt(gameDir, enhProblem);
    const bool haveTerrain =
        ProbeTerrainHdAt(gameDir, configuredTerrainHdManifest, terrainProblem);
    uint64_t t1 = MonotonicMilliseconds();
    caps.lastScanDurationMs = (t1 >= t0) ? (t1 - t0) : 0;

    if (manifestPresent && manifestValid)
    {
        // AND manifest declaration with actual filesystem availability
        caps.destructionChunks = manifestCaps.destructionChunks && haveChunks;
        caps.enhancedResources = manifestCaps.enhancedResources && haveEnhanced;
        caps.customUiAssets = manifestCaps.customUiAssets;
        caps.terrainHd = manifestCaps.terrainHd && haveTerrain;
        caps.packDetected = true; // canonical pack identity
        caps.manifestDetected = true;
        caps.state = AssetPackState::Detected;
        if (manifestCaps.destructionChunks && !haveChunks)
            caps.problem = "manifest claims ChunkMeshes but " + chunkProblem;
        else if (manifestCaps.enhancedResources && !haveEnhanced)
            caps.problem = "manifest claims EnhancedResources but " + enhProblem;
        else if (manifestCaps.terrainHd && !haveTerrain)
            caps.problem = "manifest claims TerrainHd but " + terrainProblem;
        else
            caps.problem.clear();
        if (caps.lastScanDurationMs > 200)
        {
            LogShimA(LogLevel::Warn, "assets",
                     "asset scan slow durationMs=%llu chunk=%d enhanced=%d terrain=%d",
                     (unsigned long long)caps.lastScanDurationMs,
                     haveChunks ? 1 : 0, haveEnhanced ? 1 : 0, haveTerrain ? 1 : 0);
        }
        return caps;
    }

    // No manifest: filesystem-only discovery (package identity separate)
    caps.destructionChunks = haveChunks;
    caps.enhancedResources = haveEnhanced;
    caps.terrainHd = haveTerrain;
    caps.customUiAssets = false;
    // packDetected remains false (no canonical pack) even if resources exist
    caps.packDetected = false;
    caps.manifestDetected = false;
    if (haveChunks || haveEnhanced || haveTerrain)
    {
        // Has compatible resources from somewhere (e.g. unrelated mod) but not pack
        caps.state = AssetPackState::NotDetected; // truthful: pack not detected
        // Keep versionCompatible false because no manifest to verify against
        caps.problem = "asset pack not detected; compatible resources: ";
        bool first = true;
        if (haveChunks) { caps.problem += "chunks"; first=false; }
        if (haveEnhanced) { if (!first) caps.problem += ", "; caps.problem += "enhanced"; first=false; }
        if (haveTerrain) { if (!first) caps.problem += ", "; caps.problem += "terrainHd"; }
        if (!haveChunks) { if (!first) caps.problem += ", "; caps.problem += "chunks missing"; first=false; }
        if (!haveEnhanced) { if (!first) caps.problem += ", "; caps.problem += "enhanced missing"; }
    }
    else
    {
        caps.state = AssetPackState::NotDetected;
        caps.problem = "asset pack not detected; " + chunkProblem + "; " + enhProblem;
    }
    if (caps.lastScanDurationMs > 200)
    {
        LogShimA(LogLevel::Warn, "assets",
                 "asset scan slow durationMs=%llu chunk=%d enhanced=%d terrain=%d",
                 (unsigned long long)caps.lastScanDurationMs,
                 haveChunks ? 1 : 0, haveEnhanced ? 1 : 0, haveTerrain ? 1 : 0);
    }
    return caps;
}

AssetCapabilities EvaluateAssetCapabilitiesAt(
    const std::filesystem::path& gameDir,
    const std::string& configuredTerrainHdManifest)
{
    uint64_t t0 = MonotonicMilliseconds();
    std::string manifestText;
    bool manifestFound = false;
    for (const char* rel : {kAssetManifestRelPath, kAssetManifestAltRelPath,
                            "openshim/assets.ini", "openshim/asset_pack.ini"})
    {
        const auto p = gameDir / rel;
        if (ReadTextFile(p, manifestText))
        {
            manifestFound = true;
            break;
        }
    }
    AssetCapabilities caps;
    if (manifestFound)
        caps = EvaluateAssetCapabilitiesAtWithManifest(gameDir, manifestText,
                                                       configuredTerrainHdManifest);
    else
        caps = EvaluateAssetCapabilitiesAtWithManifest(gameDir, std::string(),
                                                       configuredTerrainHdManifest);
    uint64_t t1 = MonotonicMilliseconds();
    // Ensure duration recorded even when manifest path taken
    if (caps.lastScanDurationMs == 0 && t1 >= t0)
        caps.lastScanDurationMs = t1 - t0;
    if (caps.lastScanDurationMs > 200)
    {
        LogShimA(LogLevel::Warn, "assets",
                 "EvaluateAssetCapabilitiesAt slow gameDir=%s durationMs=%llu state=%s",
                 gameDir.string().c_str(),
                 (unsigned long long)caps.lastScanDurationMs,
                 AssetPackStateName(caps.state));
    }
    return caps;
}

AssetCapabilities GetAssetCapabilities()
{
    {
        std::shared_lock<std::shared_mutex> reader(g_lock);
        if (g_initialized)
            return g_caps; // snapshot: a reference would dangle across a refresh
    }

    AssetCapabilities snapshot;
    bool logThis = false;
    {
        std::unique_lock<std::shared_mutex> writer(g_lock);
        if (!g_initialized)
        {
            const AssetRuntimeEnvironment env = ResolveAssetRuntimeEnvironment();
            g_caps = EvaluateAssetCapabilitiesAt(env.gameDir, env.terrainHdManifest);
            g_initialized = true;
            if (!g_loggedOnce)
            {
                g_loggedOnce = true;
                logThis = true;
            }
        }
        snapshot = g_caps;
    }

    if (logThis)
    {
        LogShimA(LogLevel::Info, "assets",
                 "Asset pack state=%s manifestDetected=%d packDetected=%d formatCompat=%d compatCompat=%d installedFmt=%s installedCompat=%s expectedFmt=%s expectedCompat=%s destructionChunks=%d enhancedResources=%d terrainHd=%d problem=%s scanMs=%llu",
                 AssetPackStateName(snapshot.state),
                 snapshot.manifestDetected ? 1 : 0,
                 snapshot.packDetected ? 1 : 0,
                 snapshot.formatCompatible ? 1 : 0,
                 snapshot.compatibilityCompatible ? 1 : 0,
                 snapshot.installedFormatVersion.c_str(),
                 snapshot.installedCompatibilityVersion.c_str(),
                 snapshot.expectedFormatVersion.c_str(),
                 snapshot.expectedCompatibilityVersion.c_str(),
                 snapshot.destructionChunks ? 1 : 0,
                 snapshot.enhancedResources ? 1 : 0,
                 snapshot.terrainHd ? 1 : 0,
                 snapshot.problem.c_str(),
                 (unsigned long long)snapshot.lastScanDurationMs);
    }
    return snapshot;
}

void RefreshAssetCapabilities()
{
    const AssetRuntimeEnvironment env = ResolveAssetRuntimeEnvironment();
    RefreshAssetCapabilitiesAt(env.gameDir, env.terrainHdManifest);
}

void RefreshAssetCapabilitiesAt(const std::filesystem::path& gameDir,
                                const std::string& configuredTerrainHdManifest)
{
    AssetCapabilities fresh =
        EvaluateAssetCapabilitiesAt(gameDir, configuredTerrainHdManifest);
    bool changed = false;
    {
        std::unique_lock<std::shared_mutex> writer(g_lock);
        changed = !g_initialized ||
                  fresh.state != g_caps.state ||
                  fresh.manifestDetected != g_caps.manifestDetected ||
                  fresh.packDetected != g_caps.packDetected ||
                  fresh.formatCompatible != g_caps.formatCompatible ||
                  fresh.compatibilityCompatible != g_caps.compatibilityCompatible ||
                  fresh.destructionChunks != g_caps.destructionChunks ||
                  fresh.enhancedResources != g_caps.enhancedResources ||
                  fresh.terrainHd != g_caps.terrainHd ||
                  fresh.installedCompatibilityVersion != g_caps.installedCompatibilityVersion;
        g_caps = fresh;
        g_initialized = true;
    }
    if (changed)
    {
        LogShimA(LogLevel::Info, "assets",
                 "Asset capabilities refreshed state=%s manifestDetected=%d packDetected=%d formatCompat=%d compatCompat=%d installedFmt=%s installedCompat=%s destructionChunks=%d enhancedResources=%d terrainHd=%d problem=%s scanMs=%llu",
                 AssetPackStateName(fresh.state),
                 fresh.manifestDetected ? 1 : 0,
                 fresh.packDetected ? 1 : 0,
                 fresh.formatCompatible ? 1 : 0,
                 fresh.compatibilityCompatible ? 1 : 0,
                 fresh.installedFormatVersion.c_str(),
                 fresh.installedCompatibilityVersion.c_str(),
                 fresh.destructionChunks ? 1 : 0,
                 fresh.enhancedResources ? 1 : 0,
                 fresh.terrainHd ? 1 : 0,
                 fresh.problem.c_str(),
                 (unsigned long long)fresh.lastScanDurationMs);
    }
}

void ResetAssetCapabilitiesForTesting()
{
    std::unique_lock<std::shared_mutex> writer(g_lock);
    g_caps = {};
    g_caps.state = AssetPackState::Unknown;
    g_initialized = false;
    g_loggedOnce = false;
}

void SetAssetCapabilitiesForTesting(const AssetCapabilities& caps)
{
    std::unique_lock<std::shared_mutex> writer(g_lock);
    g_caps = caps;
    g_initialized = true;
}

bool IsAssetFeatureAvailable(AssetFeature feature)
{
    const AssetCapabilities caps = GetAssetCapabilities();
    if (caps.state == AssetPackState::Unknown)
        return false;
    // If manifest present, require both format and compatibility to be compatible.
    // If no manifest, allow capability based purely on filesystem probes (unrelated mod).
    if (caps.manifestDetected && (!caps.formatCompatible || !caps.compatibilityCompatible))
        return false;
    switch (feature)
    {
    case AssetFeature::DestructionChunks:
        return caps.destructionChunks;
    case AssetFeature::EnhancedRenderer:
        return caps.enhancedResources;
    case AssetFeature::Dx11Fxaa:
        // FXAA embedded but only meaningful when enhanced renderer available
        return caps.enhancedResources;
    case AssetFeature::Dx11LocalLights:
        return caps.enhancedResources;
    case AssetFeature::CustomUiAssets:
        return caps.customUiAssets;
    case AssetFeature::TerrainHd:
        return caps.terrainHd;
    default:
        return false;
    }
}

bool ShouldEnableAssetFeature(bool configEnabled, AssetFeature feature)
{
    if (!configEnabled)
        return false;
    return IsAssetFeatureAvailable(feature);
}

std::string FormatAssetStatusForUi(const AssetCapabilities& caps)
{
    switch (caps.state)
    {
    case AssetPackState::Unknown:
        return "Asset Pack: Checking...";
    case AssetPackState::NotDetected:
        // Distinguish pack not detected vs compatible resources available via unrelated mod
        if (caps.destructionChunks || caps.enhancedResources || caps.terrainHd)
        {
            std::string s = "OpenShim Asset Pack: Not Detected";
            // Detailed per-group availability is shown in footer second line
            return s;
        }
        return "Asset Pack: NOT DETECTED";
    case AssetPackState::Incompatible:
        {
            std::string v;
            if (!caps.installedCompatibilityVersion.empty())
                v = caps.installedCompatibilityVersion;
            else if (!caps.installedFormatVersion.empty())
                v = caps.installedFormatVersion;
            else if (!caps.installedVersion.empty())
                v = caps.installedVersion;
            std::string exp = !caps.expectedCompatibilityVersion.empty() ? caps.expectedCompatibilityVersion : caps.expectedFormatVersion;
            if (!exp.empty() && exp != "1" && !caps.expectedVersion.empty())
                exp = caps.expectedVersion;
            if (!v.empty())
                return "Asset Pack: VERSION MISMATCH (Installed: " + v + " Expected: " + exp + ")";
            return "Asset Pack: VERSION MISMATCH (Expected: " + exp + ")";
        }
    case AssetPackState::Detected:
    {
        if (!caps.destructionChunks && !caps.enhancedResources && !caps.terrainHd && !caps.customUiAssets)
            return "Asset Pack: Detected (partial)";
        if (!caps.destructionChunks && caps.enhancedResources)
            return "Asset Pack: Detected (Enhanced only)";
        if (caps.destructionChunks && !caps.enhancedResources)
            return "Asset Pack: Detected (Chunks only)";
        if (caps.terrainHd)
            return "Asset Pack: Detected (+Terrain HD)";
        return "Asset Pack: Detected";
    }
    default:
        return "Asset Pack: Unknown";
    }
}

std::string FormatAssetCapabilitiesDetail(const AssetCapabilities& caps)
{
    // Used for second footer line when pack identity and capability diverge.
    // e.g. unrelated mod provides chunkMeshes but pack not installed.
    if (caps.state == AssetPackState::NotDetected)
    {
        if (caps.destructionChunks || caps.enhancedResources || caps.terrainHd)
        {
            std::string d;
            d += "Compatible chunk resources: ";
            d += caps.destructionChunks ? "Available" : "Not Available";
            d += " | Enhanced resources: ";
            d += caps.enhancedResources ? "Available" : "Not Available";
            if (caps.terrainHd)
                d += " | Terrain HD: Available";
            else if (caps.state == AssetPackState::NotDetected && caps.destructionChunks)
                d += " | Terrain HD: Not Available";
            return d;
        }
        return "Asset-dependent features are unavailable.";
    }
    if (caps.state == AssetPackState::Incompatible)
    {
        if (!caps.problem.empty())
            return caps.problem;
        return "Update the asset pack.";
    }
    if (caps.state == AssetPackState::Detected)
    {
        if (!caps.destructionChunks && caps.enhancedResources)
            return "Chunk payloads missing — Enhanced only.";
        if (caps.destructionChunks && !caps.enhancedResources)
            return "Enhanced resources missing — Chunks only.";
        if (!caps.problem.empty())
            return caps.problem;
        return "Asset-dependent features available.";
    }
    return caps.problem;
}

std::string FormatAssetStatusForLog(const AssetCapabilities& caps)
{
    return std::string(AssetPackStateName(caps.state)) +
           " manifestDetected=" + (caps.manifestDetected ? "1" : "0") +
           " packDetected=" + (caps.packDetected ? "1" : "0") +
           " formatCompat=" + (caps.formatCompatible ? "1" : "0") +
           " compatCompat=" + (caps.compatibilityCompatible ? "1" : "0") +
           " installedFmt=" + caps.installedFormatVersion +
           " installedCompat=" + caps.installedCompatibilityVersion +
           " expectedFmt=" + caps.expectedFormatVersion +
           " expectedCompat=" + caps.expectedCompatibilityVersion +
           " destructionChunks=" + (caps.destructionChunks ? "1" : "0") +
           " enhancedResources=" + (caps.enhancedResources ? "1" : "0") +
           " terrainHd=" + (caps.terrainHd ? "1" : "0") +
           " problem=" + caps.problem +
           " scanMs=" + std::to_string(caps.lastScanDurationMs);
}

} // namespace BZROpenShim::Assets
