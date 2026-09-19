#pragma once

// Mandatory deployed Enhanced renderer-resource set validation.
//
// Split out of src/patches/ogre_render_profile.cpp so the file-set contract
// is unit-testable without the game (tests/render_profile_resources_tests.cpp
// builds real directory trees and removes/invalidates single files). The
// runtime wrapper only adds the game-directory join and log formatting.

#include <filesystem>
#include <string>

namespace BZROpenShim::RenderProfiles
{
    // Compiled expectation for the deployed renderer-resource set. Bump
    // whenever resources/renderer/** changes in a way that must not pair with
    // an older DLL (winmm.dll+patches.json rule, extended to renderer assets).
    // 2: Enhanced payload became canonical (PSSM v2, the N.V diffuse repair,
    //    detail-map modulation, detail-derived normals). A v1 deployment next
    //    to a v2 DLL renders the superseded lighting, so the pairing must fail.
    // 3: DX11 legacy material compatibility payload
    //    (openshim_dx11_fixedfunc.program/.hlsl: OSE_FixedFunc_* SM4
    //    emulation plus OSE_Compat_* family adapters). A v2 deployment next
    //    to a v3 DLL would enable the compat probe with missing shader
    //    assets, so the pairing must fail closed instead.
    constexpr char kEnhancedResourcesVersion[] = "3";

    // Repository-relative name of the mandatory resource directory, as laid
    // out under the game install.
    constexpr const char* kEnhancedResourceDirRel = "openshim\\renderer\\enhanced";
    constexpr const char* kEnhancedResourceVersionFile = "resources.version";

    // True when `marker` (the raw bytes of resources.version, no trimming)
    // is exactly `expected`. Exposed so the comparison can be tested with
    // multi-character versions: a length-insensitive compare accepts any
    // marker that is a prefix of the expectation, which would let a stale
    // "1" deployment validate against a "12" DLL.
    bool VersionMarkerMatches(const char* marker, size_t markerLength,
                              const char* expected);

    // Number of mandatory payload files verified by ValidateDeployedResourceSetAt.
    size_t RequiredEnhancedResourceCount();

    // Mandatory file name at [0, RequiredEnhancedResourceCount()).
    const char* RequiredEnhancedResourceAt(size_t index);

    // Validates the version marker plus every mandatory payload file in
    // `resourceDir` (the openshim\renderer\enhanced directory itself):
    // marker must match kEnhancedResourcesVersion exactly, every listed file
    // must exist as a non-empty regular file. On failure returns false and
    // fills `outProblem` with a short ASCII description naming the first
    // offending item; on success returns true and clears `outProblem`.
    bool ValidateDeployedResourceSetAt(const std::filesystem::path& resourceDir,
                                       std::string& outProblem);
}
