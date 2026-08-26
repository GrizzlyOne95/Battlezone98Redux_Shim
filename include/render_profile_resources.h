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
    constexpr char kEnhancedResourcesVersion[] = "1";

    // Repository-relative name of the mandatory resource directory, as laid
    // out under the game install.
    constexpr const char* kEnhancedResourceDirRel = "openshim\\renderer\\enhanced";
    constexpr const char* kEnhancedResourceVersionFile = "resources.version";

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
