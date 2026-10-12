#pragma once

#include <filesystem>
#include <string>

// Updater helpers that also serve the asset-set sync. Defined in
// openshim_updater.cpp, which keeps the originals in its anonymous namespace.
namespace BZROpenShim::UpdaterDetail
{
    std::filesystem::path GetGameRoot();

    // Newest Workshop item directory (301650/3686673790) that holds an
    // OpenShimManifest.lua, across the Steam libraries.
    bool FindWorkshopItemDirectory(std::filesystem::path& itemDirectory,
                                   std::string& error);

    // "a.b.c.d" from the file's fixed version resource.
    bool ReadFileVersion(const std::filesystem::path& path, std::string& version);
}
