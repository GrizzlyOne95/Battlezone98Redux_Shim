#pragma once

#include "openshim_update_manifest.h"
#include <filesystem>
#include <functional>

namespace BZROpenShim
{
    using OpenShimPayloadVerifier = std::function<bool(
        const std::filesystem::path&, const OpenShimUpdatePayloadManifest&, std::string&)>;

    // Repair the two unlocked support files after the caller's suite identity
    // and downgrade checks. Existing player settings are always preserved.
    bool RepairOpenShimUpdateSupport(const std::filesystem::path& itemDirectory,
                                     const std::filesystem::path& gameRoot,
                                     const OpenShimUpdateManifest& manifest,
                                     const OpenShimPayloadVerifier& verify,
                                     bool& changed,
                                     std::string& error);
}
