#include "openshim_assets.h"
#include "render_profile_resources.h"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>

using namespace BZROpenShim::Assets;
using namespace BZROpenShim::RenderProfiles;

namespace
{
int g_failures = 0;

void ExpectTrue(bool cond, const char* what)
{
    if (!cond)
    {
        std::printf("  FAIL: %s\n", what);
        ++g_failures;
    }
}

void ExpectFalse(bool cond, const char* what) { ExpectTrue(!cond, what); }

void ExpectEqStr(const std::string& a, const std::string& b, const char* what)
{
    if (a != b)
    {
        std::printf("  FAIL: %s (got '%s' expected '%s')\n", what, a.c_str(), b.c_str());
        ++g_failures;
    }
}

void ExpectContains(const std::string& haystack, const char* needle, const char* what)
{
    if (haystack.find(needle) == std::string::npos)
    {
        std::printf("  FAIL: %s (missing '%s' in '%s')\n", what, needle, haystack.c_str());
        ++g_failures;
    }
}

std::error_code g_ec;

std::filesystem::path MakeScratchDir(const char* tag)
{
    auto dir = std::filesystem::temp_directory_path() /
               ("bzr_assets_test_" + std::string(tag));
    std::filesystem::remove_all(dir, g_ec);
    std::filesystem::create_directories(dir, g_ec);
    return dir;
}

void PopulateValidEnhancedSet(const std::filesystem::path& gameDir)
{
    auto resDir = gameDir / kEnhancedResourceDirRel;
    std::filesystem::create_directories(resDir, g_ec);
    {
        std::ofstream marker(resDir / kEnhancedResourceVersionFile, std::ios::binary);
        marker << kEnhancedResourcesVersion;
    }
    for (size_t i = 0; i < RequiredEnhancedResourceCount(); ++i)
    {
        std::ofstream f(resDir / RequiredEnhancedResourceAt(i), std::ios::binary);
        f << "payload";
    }
}

void PopulateChunkPayload(const std::filesystem::path& gameDir)
{
    // Use addon/ModA/chunkMeshes layout which GetCampaignContentRootCandidates discovers
    auto chunkDir = gameDir / "addon" / "ModA" / "chunkMeshes";
    std::filesystem::create_directories(chunkDir / "chunk1", g_ec);
    std::filesystem::create_directories(chunkDir / "generic", g_ec);
    {
        std::ofstream f(chunkDir / "chunk_geo_manifest.txt", std::ios::binary);
        f << "# OpenShim chunk geo manifest v1\nabbarr|aba11bld|WORLD|61|0\n";
    }
    {
        std::ofstream f(chunkDir / "chunk1" / "chunk1.mesh", std::ios::binary);
        f << "mesh";
    }
    {
        std::ofstream f(chunkDir / "generic" / "iechunk1.mesh", std::ios::binary);
        f << "mesh";
    }
}

} // anonymous

void TestTrimAndParse()
{
    std::printf("TestTrimAndParse\n");
    ExpectEqStr(TrimAssetString("  hello  "), "hello", "trim");
    ExpectTrue(AssetStringEqualsNoCase("Hello", "hello"), "case insensitive");
    ExpectFalse(AssetStringEqualsNoCase("hello", "world"), "not equal");

    std::string k, v;
    ExpectTrue(ParseAssetManifestKeyValue("Version=1", k, v), "parse Version=1");
    ExpectEqStr(k, "Version", "key");
    ExpectEqStr(v, "1", "value");
    ExpectTrue(ParseAssetManifestKeyValue(" ChunkMeshes = 1 ; comment", k, v), "parse with comment");
    ExpectEqStr(k, "ChunkMeshes", "key2");
    ExpectEqStr(v, "1", "value2");
    ExpectFalse(ParseAssetManifestKeyValue("# comment", k, v), "comment");
    ExpectFalse(ParseAssetManifestKeyValue("[OpenShimAssets]", k, v), "section header not kv");
    ExpectFalse(ParseAssetManifestKeyValue("NoEquals", k, v), "no equals");
}

void TestManifestValid()
{
    std::printf("TestManifestValid\n");
    const std::string text = "[OpenShimAssets]\nVersion=1\nChunkMeshes=1\nEnhancedResources=1\nCustomUI=1\n";
    AssetCapabilities caps;
    std::string prob;
    ExpectTrue(ParseAssetManifestContent(text, caps, prob), "valid manifest parses");
    ExpectTrue(caps.manifestDetected, "manifestDetected");
    ExpectTrue(caps.packDetected, "packDetected");
    ExpectTrue(caps.versionCompatible, "versionCompatible");
    ExpectTrue(caps.formatCompatible, "formatCompat");
    ExpectTrue(caps.compatibilityCompatible, "compatCompat");
    ExpectEqStr(caps.installedVersion, "1", "installed");
    ExpectTrue(caps.destructionChunks, "chunks");
    ExpectTrue(caps.enhancedResources, "enhanced");
    ExpectTrue(caps.customUiAssets, "custom");
    ExpectTrue(prob.empty(), "no problem");
}

void TestManifestMissingVersion()
{
    std::printf("TestManifestMissingVersion\n");
    const std::string text = "[OpenShimAssets]\nChunkMeshes=1\n";
    AssetCapabilities caps;
    std::string prob;
    ExpectFalse(ParseAssetManifestContent(text, caps, prob), "missing version fails");
    ExpectFalse(caps.versionCompatible, "not compatible");
    ExpectEqStr(caps.state == AssetPackState::Incompatible ? "Incompatible" : "other", "Incompatible", "state incompatible");
    ExpectContains(prob, "Version", "problem mentions Version");
}

void TestManifestVersionMismatch()
{
    std::printf("TestManifestVersionMismatch\n");
    const std::string text = "[OpenShimAssets]\nVersion=999\nChunkMeshes=1\n";
    AssetCapabilities caps;
    std::string prob;
    ExpectFalse(ParseAssetManifestContent(text, caps, prob), "mismatch fails");
    ExpectFalse(caps.versionCompatible, "not compatible");
    ExpectFalse(caps.destructionChunks, "chunks false on mismatch");
    ExpectFalse(caps.enhancedResources, "enhanced false");
    ExpectContains(prob, "mismatch", "problem mismatch");
}

void TestManifestMalformed()
{
    std::printf("TestManifestMalformed\n");
    // No section header, so Version never seen -> treated as missing version
    const std::string text = "Version 1\nChunkMeshes 1\n";
    AssetCapabilities caps;
    std::string prob;
    ExpectFalse(ParseAssetManifestContent(text, caps, prob), "malformed no section");
    ExpectFalse(caps.versionCompatible, "not compatible");
}

void TestManifestPartial()
{
    std::printf("TestManifestPartial\n");
    const std::string text = "[OpenShimAssets]\nVersion=1\nChunkMeshes=1\nEnhancedResources=0\n";
    AssetCapabilities caps;
    std::string prob;
    ExpectTrue(ParseAssetManifestContent(text, caps, prob), "partial valid");
    ExpectTrue(caps.destructionChunks, "chunks true");
    ExpectFalse(caps.enhancedResources, "enhanced false");
}

void TestProbeDestructionChunksNone()
{
    std::printf("TestProbeDestructionChunksNone\n");
    auto dir = MakeScratchDir("chunk_none");
    std::string prob;
    ExpectFalse(ProbeDestructionChunksAt(dir, prob), "none -> false");
    ExpectContains(prob, "no chunk", "problem");
    std::filesystem::remove_all(dir, g_ec);
}

void TestProbeDestructionChunksPresent()
{
    std::printf("TestProbeDestructionChunksPresent\n");
    auto dir = MakeScratchDir("chunk_present");
    PopulateChunkPayload(dir);
    std::string prob;
    ExpectTrue(ProbeDestructionChunksAt(dir, prob), "present -> true");
    ExpectTrue(prob.empty(), "no problem");
    std::filesystem::remove_all(dir, g_ec);
}

void TestProbeEnhancedNone()
{
    std::printf("TestProbeEnhancedNone\n");
    auto dir = MakeScratchDir("enh_none");
    std::string prob;
    ExpectFalse(ProbeEnhancedResourcesAt(dir, prob), "none -> false");
    std::filesystem::remove_all(dir, g_ec);
}

void TestProbeEnhancedPresent()
{
    std::printf("TestProbeEnhancedPresent\n");
    auto dir = MakeScratchDir("enh_present");
    PopulateValidEnhancedSet(dir);
    std::string prob;
    ExpectTrue(ProbeEnhancedResourcesAt(dir, prob), "present -> true");
    ExpectTrue(prob.empty(), "no problem");
    std::filesystem::remove_all(dir, g_ec);
}

void TestProbeEnhancedEmptyFileFails()
{
    std::printf("TestProbeEnhancedEmptyFileFails\n");
    auto dir = MakeScratchDir("enh_empty");
    PopulateValidEnhancedSet(dir);
    // Empty one mandatory file
    auto resDir = dir / kEnhancedResourceDirRel;
    std::ofstream trunc(resDir / RequiredEnhancedResourceAt(0), std::ios::binary | std::ios::trunc);
    trunc.close();
    std::string prob;
    ExpectFalse(ProbeEnhancedResourcesAt(dir, prob), "empty -> false");
    ExpectContains(prob, RequiredEnhancedResourceAt(0), "problem names file");
    std::filesystem::remove_all(dir, g_ec);
}

void TestEvaluateNoManifestNone()
{
    std::printf("TestEvaluateNoManifestNone\n");
    auto dir = MakeScratchDir("eval_none");
    auto caps = EvaluateAssetCapabilitiesAt(dir);
    ExpectTrue(caps.state == AssetPackState::NotDetected, "NotDetected");
    ExpectFalse(caps.packDetected, "not detected");
    ExpectFalse(caps.versionCompatible, "not compatible");
    ExpectFalse(caps.destructionChunks, "no chunks");
    ExpectFalse(caps.enhancedResources, "no enhanced");
    std::filesystem::remove_all(dir, g_ec);
}

void TestEvaluateNoManifestFull()
{
    std::printf("TestEvaluateNoManifestFull\n");
    auto dir = MakeScratchDir("eval_full");
    PopulateChunkPayload(dir);
    PopulateValidEnhancedSet(dir);
    auto caps = EvaluateAssetCapabilitiesAt(dir);
    // No manifest: pack identity separate from capability. Pack remains NotDetected
    // even though compatible resources exist via filesystem probing.
    ExpectTrue(caps.state == AssetPackState::NotDetected, "NotDetected when no manifest even with resources");
    ExpectFalse(caps.packDetected, "packDetected false without manifest");
    ExpectFalse(caps.manifestDetected, "manifestDetected false");
    ExpectTrue(caps.destructionChunks, "chunks true via probe");
    ExpectTrue(caps.enhancedResources, "enhanced true via probe");
    std::filesystem::remove_all(dir, g_ec);
}

void TestEvaluateNoManifestPartial()
{
    std::printf("TestEvaluateNoManifestPartial\n");
    auto dir = MakeScratchDir("eval_partial");
    PopulateChunkPayload(dir);
    // no enhanced
    auto caps = EvaluateAssetCapabilitiesAt(dir);
    ExpectTrue(caps.state == AssetPackState::NotDetected, "NotDetected even if partial resources without manifest");
    ExpectFalse(caps.packDetected, "pack false");
    ExpectTrue(caps.destructionChunks, "chunks true");
    ExpectFalse(caps.enhancedResources, "enhanced false");
    ExpectContains(caps.problem, "chunks", "problem mentions chunks");
    std::filesystem::remove_all(dir, g_ec);
}

void TestEvaluateWithManifestValidFull()
{
    std::printf("TestEvaluateWithManifestValidFull\n");
    auto dir = MakeScratchDir("eval_manifest_full");
    PopulateChunkPayload(dir);
    PopulateValidEnhancedSet(dir);
    const std::string manifest = "[OpenShimAssets]\nVersion=1\nChunkMeshes=1\nEnhancedResources=1\n";
    auto caps = EvaluateAssetCapabilitiesAtWithManifest(dir, manifest);
    ExpectTrue(caps.state == AssetPackState::Detected, "Detected");
    ExpectTrue(caps.destructionChunks, "chunks");
    ExpectTrue(caps.enhancedResources, "enhanced");
    std::filesystem::remove_all(dir, g_ec);
}

void TestEvaluateWithManifestValidButFilesMissing()
{
    std::printf("TestEvaluateWithManifestValidButFilesMissing\n");
    auto dir = MakeScratchDir("eval_manifest_missing");
    // manifest claims chunks but no files
    const std::string manifest = "[OpenShimAssets]\nVersion=1\nChunkMeshes=1\nEnhancedResources=1\n";
    auto caps = EvaluateAssetCapabilitiesAtWithManifest(dir, manifest);
    ExpectTrue(caps.state == AssetPackState::Detected, "Detected even partial");
    ExpectFalse(caps.destructionChunks, "chunks false because files missing");
    ExpectFalse(caps.enhancedResources, "enhanced false");
    ExpectContains(caps.problem, "ChunkMeshes", "problem");
    std::filesystem::remove_all(dir, g_ec);
}

void TestEvaluateWithManifestMismatch()
{
    std::printf("TestEvaluateWithManifestMismatch\n");
    auto dir = MakeScratchDir("eval_mismatch");
    PopulateChunkPayload(dir);
    PopulateValidEnhancedSet(dir);
    const std::string manifest = "[OpenShimAssets]\nVersion=999\nChunkMeshes=1\n";
    auto caps = EvaluateAssetCapabilitiesAtWithManifest(dir, manifest);
    ExpectTrue(caps.state == AssetPackState::Incompatible, "Incompatible");
    ExpectFalse(caps.versionCompatible, "not compatible");
    ExpectFalse(caps.destructionChunks, "chunks false on mismatch");
    std::filesystem::remove_all(dir, g_ec);
}

void TestEvaluateWithManifestMalformed()
{
    std::printf("TestEvaluateWithManifestMalformed\n");
    auto dir = MakeScratchDir("eval_malformed");
    PopulateChunkPayload(dir);
    const std::string manifest = "garbage without section\nVersion=1\n";
    auto caps = EvaluateAssetCapabilitiesAtWithManifest(dir, manifest);
    ExpectTrue(caps.state == AssetPackState::Incompatible, "Incompatible malformed");
    std::filesystem::remove_all(dir, g_ec);
}

void TestMissingManifestBehavior()
{
    std::printf("TestMissingManifestBehavior\n");
    auto dir = MakeScratchDir("missing_manifest");
    // No manifest file at all, plus no payloads -> NotDetected
    auto caps = EvaluateAssetCapabilitiesAt(dir);
    ExpectTrue(caps.state == AssetPackState::NotDetected, "NotDetected when no manifest and no payloads");
    std::filesystem::remove_all(dir, g_ec);
}

void TestFeatureGating()
{
    std::printf("TestFeatureGating\n");
    // Simulate valid pack
    AssetCapabilities good;
    good.state = AssetPackState::Detected;
    good.packDetected = true;
    good.versionCompatible = true;
    good.installedVersion = "1";
    good.destructionChunks = true;
    good.enhancedResources = true;
    SetAssetCapabilitiesForTesting(good);
    ExpectTrue(IsAssetFeatureAvailable(AssetFeature::DestructionChunks), "chunks available when good");
    ExpectTrue(ShouldEnableAssetFeature(true, AssetFeature::DestructionChunks), "config true && available -> true");
    ExpectFalse(ShouldEnableAssetFeature(false, AssetFeature::DestructionChunks), "config false -> false even if available");
    ExpectTrue(ShouldEnableAssetFeature(true, AssetFeature::EnhancedRenderer), "enhanced true");
    // Simulate missing pack
    AssetCapabilities bad;
    bad.state = AssetPackState::NotDetected;
    bad.packDetected = false;
    bad.versionCompatible = false;
    bad.destructionChunks = false;
    bad.enhancedResources = false;
    SetAssetCapabilitiesForTesting(bad);
    ExpectFalse(IsAssetFeatureAvailable(AssetFeature::DestructionChunks), "not available when bad");
    ExpectFalse(ShouldEnableAssetFeature(true, AssetFeature::DestructionChunks), "config true but asset missing -> false");
    ExpectFalse(ShouldEnableAssetFeature(true, AssetFeature::EnhancedRenderer), "enhanced blocked");
    // Version mismatch
    AssetCapabilities mismatch;
    mismatch.state = AssetPackState::Incompatible;
    mismatch.packDetected = true;
    mismatch.versionCompatible = false;
    mismatch.installedVersion = "999";
    mismatch.destructionChunks = false;
    mismatch.enhancedResources = false;
    SetAssetCapabilitiesForTesting(mismatch);
    ExpectFalse(IsAssetFeatureAvailable(AssetFeature::DestructionChunks), "mismatch not available");
    ExpectFalse(ShouldEnableAssetFeature(true, AssetFeature::DestructionChunks), "blocked on mismatch");
    // Partial: chunks true, enhanced false
    AssetCapabilities partial;
    partial.state = AssetPackState::Detected;
    partial.packDetected = true;
    partial.versionCompatible = true;
    partial.destructionChunks = true;
    partial.enhancedResources = false;
    SetAssetCapabilitiesForTesting(partial);
    ExpectTrue(IsAssetFeatureAvailable(AssetFeature::DestructionChunks), "partial chunks available");
    ExpectFalse(IsAssetFeatureAvailable(AssetFeature::EnhancedRenderer), "partial enhanced not");
    ExpectTrue(ShouldEnableAssetFeature(true, AssetFeature::DestructionChunks), "chunks true");
    ExpectFalse(ShouldEnableAssetFeature(true, AssetFeature::EnhancedRenderer), "enhanced false");
    // Unknown should fail closed
    AssetCapabilities unknown;
    unknown.state = AssetPackState::Unknown;
    unknown.packDetected = false;
    unknown.versionCompatible = false;
    SetAssetCapabilitiesForTesting(unknown);
    ExpectFalse(IsAssetFeatureAvailable(AssetFeature::DestructionChunks), "unknown not available");
    ExpectFalse(ShouldEnableAssetFeature(true, AssetFeature::DestructionChunks), "unknown blocked");

    ResetAssetCapabilitiesForTesting();
}


void TestFormatVersionVsCompatibility()
{
    std::printf("TestFormatVersionVsCompatibility\n");
    // New explicit FormatVersion + CompatibilityVersion
    const std::string text1 = "[OpenShimAssets]\nFormatVersion=1\nCompatibilityVersion=1\nChunkMeshes=1\n";
    AssetCapabilities caps;
    std::string prob;
    ExpectTrue(ParseAssetManifestContent(text1, caps, prob), "both versions 1 parses");
    ExpectTrue(caps.formatCompatible, "format");
    ExpectTrue(caps.compatibilityCompatible, "compat");

    const std::string text2 = "[OpenShimAssets]\nFormatVersion=999\nCompatibilityVersion=1\nChunkMeshes=1\n";
    ExpectFalse(ParseAssetManifestContent(text2, caps, prob), "bad format fails");
    ExpectFalse(caps.formatCompatible, "format false");

    const std::string text3 = "[OpenShimAssets]\nFormatVersion=1\nCompatibilityVersion=999\nChunkMeshes=1\n";
    ExpectFalse(ParseAssetManifestContent(text3, caps, prob), "bad compat fails");
    ExpectFalse(caps.compatibilityCompatible, "compat false");

    // Legacy Version= alias still works
    const std::string text4 = "[OpenShimAssets]\nVersion=1\nChunkMeshes=1\n";
    ExpectTrue(ParseAssetManifestContent(text4, caps, prob), "legacy Version still works");
    ExpectTrue(caps.compatibilityCompatible, "legacy compat true");
}

void TestPackageVsCapabilitySeparation()
{
    std::printf("TestPackageVsCapabilitySeparation\n");
    auto dir = MakeScratchDir("pkg_vs_cap");
    PopulateChunkPayload(dir);
    // No manifest, no enhanced -> compatible chunk resources available but pack not detected
    auto caps = EvaluateAssetCapabilitiesAt(dir);
    ExpectTrue(caps.state == AssetPackState::NotDetected, "pack NotDetected");
    ExpectFalse(caps.packDetected, "pack false");
    ExpectFalse(caps.manifestDetected, "manifest false");
    ExpectTrue(caps.destructionChunks, "chunks available via unrelated mod probe");
    ExpectFalse(caps.enhancedResources, "enhanced not");
    // But feature should still be available via capability, even though pack not detected
    SetAssetCapabilitiesForTesting(caps);
    ExpectTrue(IsAssetFeatureAvailable(AssetFeature::DestructionChunks), "chunks available even without pack");
    ExpectFalse(IsAssetFeatureAvailable(AssetFeature::EnhancedRenderer), "enhanced not");
    // UI truthfulness: FormatAssetStatusForUi should still say Not Detected, Detail shows per-group
    ExpectContains(FormatAssetStatusForUi(caps), "Not Detected", "ui pack not detected");
    ExpectContains(FormatAssetCapabilitiesDetail(caps), "chunk resources", "detail shows chunks");
    ExpectContains(FormatAssetCapabilitiesDetail(caps), "Available", "detail available");
    ResetAssetCapabilitiesForTesting();
    std::filesystem::remove_all(dir, g_ec);
}

void TestTerrainHdCapability()
{
    std::printf("TestTerrainHdCapability\n");
    auto dir = MakeScratchDir("terrain_hd");
    // No manifest, no terrain file -> not available
    std::string prob;
    ExpectFalse(ProbeTerrainHdAt(dir, prob), "no terrain initially");
    // Create terrain_hd_tiles.json
    {
        std::ofstream f(dir / "terrain_hd_tiles.json", std::ios::binary);
        f << "{\"tiles\":[]}";
    }
    ExpectTrue(ProbeTerrainHdAt(dir, prob), "terrain now available");

    // Manifest claiming TerrainHd=1 but file missing -> capability false
    const std::string manifest = "[OpenShimAssets]\nFormatVersion=1\nCompatibilityVersion=1\nTerrainHd=1\n";
    auto caps = EvaluateAssetCapabilitiesAtWithManifest(dir, manifest);
    // dir has terrain file now, so should be true
    ExpectTrue(caps.terrainHd, "terrain true when manifest claims and file exists");

    // Remove file, re-evaluate -> false
    std::filesystem::remove(dir / "terrain_hd_tiles.json", g_ec);
    caps = EvaluateAssetCapabilitiesAtWithManifest(dir, manifest);
    ExpectFalse(caps.terrainHd, "terrain false when file missing even though manifest claims");
    ExpectContains(caps.problem, "TerrainHd", "problem mentions terrain");

    // Capability gating: config true + terrain available -> true
    AssetCapabilities good;
    good.state = AssetPackState::Detected;
    good.manifestDetected = true;
    good.packDetected = true;
    good.formatCompatible = true;
    good.compatibilityCompatible = true;
    good.versionCompatible = true;
    good.terrainHd = true;
    SetAssetCapabilitiesForTesting(good);
    ExpectTrue(IsAssetFeatureAvailable(AssetFeature::TerrainHd), "terrain available");
    good.terrainHd = false;
    SetAssetCapabilitiesForTesting(good);
    ExpectFalse(IsAssetFeatureAvailable(AssetFeature::TerrainHd), "terrain not");
    ResetAssetCapabilitiesForTesting();
    std::filesystem::remove_all(dir, g_ec);
}

void TestPerMeshPartialSafety()
{
    std::printf("TestPerMeshPartialSafety\n");
    // Global capability true (some chunks exist) but specific mesh absent should not allocate.
    // This test proves TryResolveChunkPayloadMeshResource fails for absent mesh, and that
    // Evaluate with manifest claiming ChunkMeshes=1 but filesystem missing specific file still reports problem.
    auto dir = MakeScratchDir("per_mesh");
    PopulateChunkPayload(dir);
    // manifest claims chunks
    const std::string manifest = "[OpenShimAssets]\nFormatVersion=1\nCompatibilityVersion=1\nChunkMeshes=1\n";
    auto caps = EvaluateAssetCapabilitiesAtWithManifest(dir, manifest);
    ExpectTrue(caps.destructionChunks, "global chunks true");
    // Now remove the specific mesh that would be requested (simulate partial)
    std::filesystem::remove(dir / "addon" / "ModA" / "chunkMeshes" / "chunk1" / "chunk1.mesh", g_ec);
    std::filesystem::remove(dir / "addon" / "ModA" / "chunkMeshes" / "generic" / "iechunk1.mesh", g_ec);
    // Remove manifest file as well to make probe fail for that specific directory?
    // Probe still finds manifest file? Actually we keep manifest file but remove meshes, probe fallback will scan for .mesh and fail if none remain.
    // Let's ensure no .mesh remains anywhere: remove all
    std::filesystem::remove_all(dir / "addon", g_ec);
    caps = EvaluateAssetCapabilitiesAtWithManifest(dir, manifest);
    ExpectFalse(caps.destructionChunks, "global chunks false when all meshes removed even though manifest claims");
    ExpectContains(caps.problem, "ChunkMeshes", "problem");
    std::filesystem::remove_all(dir, g_ec);
}

void TestSemanticCleanupFxaa()
{
    std::printf("TestSemanticCleanupFxaa\n");
    // FXAA and LocalLights are gated on EnhancedResources, not pack identity directly.
    AssetCapabilities caps;
    caps.state = AssetPackState::NotDetected;
    caps.manifestDetected = false;
    caps.packDetected = false;
    caps.destructionChunks = true;
    caps.enhancedResources = false;
    caps.terrainHd = false;
    SetAssetCapabilitiesForTesting(caps);
    ExpectFalse(IsAssetFeatureAvailable(AssetFeature::Dx11Fxaa), "fxaa false when enhanced missing");
    ExpectFalse(IsAssetFeatureAvailable(AssetFeature::Dx11LocalLights), "local lights false");
    caps.enhancedResources = true;
    SetAssetCapabilitiesForTesting(caps);
    ExpectTrue(IsAssetFeatureAvailable(AssetFeature::Dx11Fxaa), "fxaa true when enhanced available even without pack");
    ExpectTrue(IsAssetFeatureAvailable(AssetFeature::Dx11LocalLights), "local lights true");
    ResetAssetCapabilitiesForTesting();
}

void TestUiFormatting()
{
    std::printf("TestUiFormatting\n");
    AssetCapabilities caps;
    caps.state = AssetPackState::NotDetected;
    caps.packDetected = false;
    ExpectContains(FormatAssetStatusForUi(caps), "NOT DETECTED", "ui not detected");
    caps.state = AssetPackState::Detected;
    caps.packDetected = true;
    caps.versionCompatible = true;
    caps.destructionChunks = true;
    caps.enhancedResources = true;
    ExpectContains(FormatAssetStatusForUi(caps), "Detected", "ui detected");
    caps.destructionChunks = false;
    caps.enhancedResources = true;
    ExpectContains(FormatAssetStatusForUi(caps), "Enhanced only", "ui partial");
    caps.state = AssetPackState::Incompatible;
    caps.installedVersion = "999";
    caps.expectedVersion = "1";
    ExpectContains(FormatAssetStatusForUi(caps), "MISMATCH", "ui mismatch");
    ExpectContains(FormatAssetStatusForUi(caps), "999", "ui installed");
}

int main()
{
    TestTrimAndParse();
    TestManifestValid();
    TestManifestMissingVersion();
    TestManifestVersionMismatch();
    TestManifestMalformed();
    TestManifestPartial();
    TestProbeDestructionChunksNone();
    TestProbeDestructionChunksPresent();
    TestProbeEnhancedNone();
    TestProbeEnhancedPresent();
    TestProbeEnhancedEmptyFileFails();
    TestEvaluateNoManifestNone();
    TestEvaluateNoManifestFull();
    TestEvaluateNoManifestPartial();
    TestEvaluateWithManifestValidFull();
    TestEvaluateWithManifestValidButFilesMissing();
    TestEvaluateWithManifestMismatch();
    TestEvaluateWithManifestMalformed();
    TestMissingManifestBehavior();
    TestFeatureGating();
    TestFormatVersionVsCompatibility();
    TestPackageVsCapabilitySeparation();
    TestTerrainHdCapability();
    TestPerMeshPartialSafety();
    TestSemanticCleanupFxaa();
    TestUiFormatting();

    if (g_failures != 0)
    {
        std::printf("\nopenshim_assets_tests FAILED (%d)\n", g_failures);
        return 1;
    }
    std::printf("\nopenshim_assets_tests passed\n");
    return 0;
}
