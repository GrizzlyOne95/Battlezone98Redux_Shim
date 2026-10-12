// odf_search_path.h
// Portable (no engine linkage) ODF search-path construction and file lookup,
// shared by odf_helpers.cpp and its unit test.
#pragma once

#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>

namespace BZROpenShim
{
    namespace OdfSearchPath
    {
        inline void AppendUnique(std::vector<std::filesystem::path>& paths,
                                 const std::filesystem::path& candidate)
        {
            if (candidate.empty())
                return;
            if (std::find(paths.begin(), paths.end(), candidate) != paths.end())
                return;
            paths.push_back(candidate);
        }

        // Directory order: for each content root, its structured ODF folders
        // first (ODF, _Release/ODF, _Source/ODF) and then the root itself, so
        // mods that ship flat (every file at the mod root, e.g. Campaign
        // Reimagined's Workshop deployment) resolve while structured layouts
        // keep precedence. Edit/stock stays last.
        //
        // Known limitation: OpenShim does not track the active mod/mission
        // root, so roots are searched in discovery order (addon, mods,
        // packaged_mods, Workshop). A flat root of an unrelated mod that is
        // discovered earlier and ships the same ODF name can shadow the
        // active mod's copy.
        inline std::vector<std::filesystem::path> BuildOdfDirectoryCandidates(
            const std::vector<std::filesystem::path>& contentRoots,
            const std::filesystem::path& gameDir)
        {
            std::vector<std::filesystem::path> candidates;
            for (const auto& root : contentRoots)
            {
                AppendUnique(candidates, root / "ODF");
                AppendUnique(candidates, root / "_Release" / "ODF");
                AppendUnique(candidates, root / "_Source" / "ODF");
                AppendUnique(candidates, root);
            }
            if (!gameDir.empty())
                candidates.push_back(gameDir / "Edit" / "stock");
            return candidates;
        }

        // Checks <token>_mp.odf then <token>.odf in each directory in order.
        inline bool FindOdfFile(const std::vector<std::filesystem::path>& directories,
                                const std::string& token,
                                std::filesystem::path& outPath)
        {
            outPath.clear();
            for (const auto& directory : directories)
            {
                std::error_code error;
                const auto mpPath = directory / (token + "_mp.odf");
                if (std::filesystem::exists(mpPath, error) && !error)
                {
                    outPath = mpPath;
                    return true;
                }

                error.clear();
                const auto normalPath = directory / (token + ".odf");
                if (std::filesystem::exists(normalPath, error) && !error)
                {
                    outPath = normalPath;
                    return true;
                }
            }
            return false;
        }
    }
}
