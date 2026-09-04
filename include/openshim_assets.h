#pragma once

// Centralized OpenShim asset-capability system.
// Replaces scattered FileExists() checks with one explicit capability service.
// Detects whether the separate OpenShim/Campaign Reimagined asset package is
// present, its version compatibility, and which resource groups are usable.
// All filesystem probes are pure functions taking a game directory so the core
// is unit-testable without the game (see tests/openshim_assets_tests.cpp).
// src/engine/openshim_assets.cpp contains no OS-specific code and is built by
// the Linux CTest workflow; the Win32 pieces live in
// src/engine/openshim_assets_platform.cpp behind ResolveAssetRuntimeEnvironment().
// Runtime state is Unknown until the first successful filesystem observation;
// Unknown never masquerades as NotDetected.

#include <cstdint>
#include <filesystem>
#include <string>

namespace BZROpenShim::Assets
{

constexpr const char* kAssetManifestRelPath = "openshim/OpenShimAssets.ini";
constexpr const char* kAssetManifestAltRelPath = "openshim/assets.manifest";
constexpr const char* kAssetPackExpectedVersion = "1";
constexpr const char* kAssetPackExpectedVersionAlt = "1.0";
// New explicit versioning (FormatVersion = INI schema, CompatibilityVersion = asset DLL compat).
// Both expected to be "1" initially; Version= remains accepted as alias for CompatibilityVersion.
constexpr const char* kAssetManifestExpectedFormatVersion = "1";
constexpr const char* kAssetManifestExpectedCompatibilityVersion = "1";
// Default value of openshim.ini [Terrain] TerrainHdManifest. Kept in sync with
// terrain_proxy.cpp's ReadConfig() default so the capability probe and the
// loader resolve the same file.
constexpr const char* kDefaultTerrainHdManifest = "terrain_hd_tiles.json";

enum class AssetPackState : uint8_t
{
    Unknown = 0,
    NotDetected = 1,
    Detected = 2,
    Incompatible = 3,
};

const char* AssetPackStateName(AssetPackState state) noexcept;

struct AssetCapabilities
{
    AssetPackState state = AssetPackState::Unknown;
    // Package identity (manifest present) — distinct from capability discovery.
    // An unrelated mod supplying chunkMeshes must not cause "Asset Pack: Detected".
    bool manifestDetected = false;
    // Canonical pack identity: manifest present + both versions compatible.
    bool packDetected = false; // manifestDetected && formatCompatible && compatibilityCompatible
    bool versionCompatible = false; // alias for compatibilityCompatible (kept for compat)
    bool formatCompatible = false;
    bool compatibilityCompatible = false;
    std::string installedVersion; // legacy alias = installedCompatibilityVersion
    std::string expectedVersion = kAssetPackExpectedVersion;
    std::string installedFormatVersion;
    std::string expectedFormatVersion = kAssetManifestExpectedFormatVersion;
    std::string installedCompatibilityVersion;
    std::string expectedCompatibilityVersion = kAssetManifestExpectedCompatibilityVersion;

    // Individual resource groups, independently verified. Each can be false
    // while others true (partial package). These reflect filesystem probes,
    // even when packDetected is false (unrelated mod).
    bool destructionChunks = false;
    bool enhancedResources = false;
    bool customUiAssets = false;
    bool terrainHd = false; // explicit disposition for HD terrain payload

    // One-line diagnostic for logging / UI
    std::string problem; // first blocking reason, ASCII
    // Instrumentation: milliseconds spent in last filesystem scan
    uint64_t lastScanDurationMs = 0;
};

enum class AssetFeature : uint8_t
{
    DestructionChunks = 0,
    EnhancedRenderer = 1,
    Dx11Fxaa = 2,
    Dx11LocalLights = 3,
    CustomUiAssets = 4,
    TerrainHd = 5,
};

// --- Pure helpers (testable without Windows/process state) -----------------

// Trim ASCII whitespace (space, tab, CR, LF). Returns trimmed copy.
std::string TrimAssetString(const std::string& value);

// Case-insensitive ASCII compare.
bool AssetStringEqualsNoCase(const std::string& a, const std::string& b);

// Parse "key = value" line ignoring comments (#, ;). Returns false for
// comment/blank/malformed lines.
bool ParseAssetManifestKeyValue(const std::string& line,
                                std::string& outKey,
                                std::string& outValue);

// Parse total manifest text (ini-style) into capabilities. The caller must
// have already probed filesystem for individual groups; this only interprets
// the manifest-declared version/capabilities. Returns true when manifest
// was syntactically valid (even if version mismatched).
bool ParseAssetManifestContent(const std::string& text,
                               AssetCapabilities& out,
                               std::string& outProblem);

// Filesystem probes (gameDir = ParentPath of BZR.exe/battlezone98redux.exe)
// ProbeDestructionChunksAt mirrors bzr_hooks' chunk-payload discovery:
//   gameDir/addon/*/chunkMeshes , gameDir/mods/*/chunkMeshes, etc,
//   workshop/content/301650/*/chunkMeshes, and BZ_ASSETS/common/models/...
// It succeeds when at least one candidate directory exists and contains
// either chunk_geo_manifest.txt or at least one *.mesh file.
// Exposed for tests.
bool ProbeDestructionChunksAt(const std::filesystem::path& gameDir,
                              std::string& outProblem);

// Reuses RenderProfiles::ValidateDeployedResourceSetAt on
// gameDir/openshim/renderer/enhanced .
bool ProbeEnhancedResourcesAt(const std::filesystem::path& gameDir,
                              std::string& outProblem);

// Resolves the HD terrain manifest exactly as terrain_proxy.cpp's
// ResolveHdManifestPath() does, so the capability probe and the loader always
// agree on which file is authoritative: an absolute configuredManifest is used
// verbatim, a relative one is taken against gameDir, and an empty one yields an
// empty path (HD terrain has no manifest to load).
std::filesystem::path ResolveTerrainHdManifestPathAt(
    const std::filesystem::path& gameDir,
    const std::string& configuredManifest);

// HD terrain payload probe. Succeeds when the manifest named by
// configuredManifest ([Terrain] TerrainHdManifest, default
// kDefaultTerrainHdManifest) resolves to a non-empty regular file. This is the
// same path LoadTerrainHdManifest() opens, so a custom manifest location is
// reported accurately. No Ogre interaction and no JSON schema validation --
// LoadTerrainHdManifest() remains the complete gate.
bool ProbeTerrainHdAt(const std::filesystem::path& gameDir,
                      const std::string& configuredManifest,
                      std::string& outProblem);

// Full evaluation at gameDir (manifest + per-group probes). Pure.
// configuredTerrainHdManifest carries the runtime's [Terrain] TerrainHdManifest
// value; callers without config access pass the default.
AssetCapabilities EvaluateAssetCapabilitiesAt(
    const std::filesystem::path& gameDir,
    const std::string& configuredTerrainHdManifest = kDefaultTerrainHdManifest);

// Helper for tests: evaluate at gameDir with an already-read manifest text.
// Pass empty manifestText to skip manifest step and use filesystem probes only.
AssetCapabilities EvaluateAssetCapabilitiesAtWithManifest(
    const std::filesystem::path& gameDir,
    const std::string& manifestText,
    const std::string& configuredTerrainHdManifest = kDefaultTerrainHdManifest);

// --- Platform adapter ------------------------------------------------------

// Everything above is engine- and OS-independent and is compiled into the
// Linux CTest suite. The two facts the core cannot discover on its own -- where
// the game is installed and what openshim.ini configured -- are supplied by the
// platform adapter (src/engine/openshim_assets_platform.cpp on Win32; the test
// harness links its own trivial implementation).
struct AssetRuntimeEnvironment
{
    std::filesystem::path gameDir;
    std::string terrainHdManifest = kDefaultTerrainHdManifest;
};

AssetRuntimeEnvironment ResolveAssetRuntimeEnvironment();

// --- Runtime singleton (thread-safe, Unknown-aware) ------------------------

// Returns a snapshot by value. Refresh may replace the cached capabilities
// (including their std::string storage) from another thread at any time, so a
// reference into the cache would dangle; callers get their own consistent copy.
AssetCapabilities GetAssetCapabilities();
void RefreshAssetCapabilities();
void RefreshAssetCapabilitiesAt(
    const std::filesystem::path& gameDir,
    const std::string& configuredTerrainHdManifest = kDefaultTerrainHdManifest);

// Test seam only.
void ResetAssetCapabilitiesForTesting();
void SetAssetCapabilitiesForTesting(const AssetCapabilities& caps);

// Feature gating: configEnabled && capabilityAvailable && versionCompatible
bool IsAssetFeatureAvailable(AssetFeature feature);
bool ShouldEnableAssetFeature(bool configEnabled, AssetFeature feature);

// Convenience for UI
std::string FormatAssetStatusForUi(const AssetCapabilities& caps);
std::string FormatAssetCapabilitiesDetail(const AssetCapabilities& caps);
std::string FormatAssetStatusForLog(const AssetCapabilities& caps);

} // namespace BZROpenShim::Assets
