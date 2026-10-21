// odf_search_path.h
// Portable (no engine linkage) ODF search-path construction and file lookup,
// shared by odf_helpers.cpp and its unit test.
#pragma once

#include <algorithm>
#include <filesystem>
#include <string>
#include <unordered_map>
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

        // A snapshot of the .odf files in each candidate directory, so a lookup
        // is hash probes instead of two filesystem stats per directory. Names
        // are folded to lower case: Windows (and Wine's default mapping) match
        // ODF names case-insensitively, which is what the stat-based lookup
        // relied on. Files added after the snapshot are not seen until it is
        // rebuilt.
        struct OdfDirectoryIndex
        {
            struct Directory
            {
                std::filesystem::path path;
                std::unordered_map<std::string, std::filesystem::path> files;
            };

            std::vector<Directory> directories;
        };

        inline std::string LowerAscii(std::string value)
        {
            for (char& ch : value)
            {
                if (ch >= 'A' && ch <= 'Z')
                    ch = static_cast<char>(ch - 'A' + 'a');
            }
            return value;
        }

        inline OdfDirectoryIndex BuildOdfDirectoryIndex(
            const std::vector<std::filesystem::path>& directories)
        {
            OdfDirectoryIndex index;
            index.directories.reserve(directories.size());
            for (const auto& directory : directories)
            {
                OdfDirectoryIndex::Directory entry;
                entry.path = directory;

                std::error_code error;
                for (std::filesystem::directory_iterator it(directory, error), end;
                     !error && it != end;
                     it.increment(error))
                {
                    // A name the narrow encoding cannot represent throws from
                    // string(); such a file was unreachable by token anyway.
                    try
                    {
                        std::error_code typeError;
                        if (!it->is_regular_file(typeError) || typeError)
                            continue;
                        std::string name = LowerAscii(it->path().filename().string());
                        if (name.size() <= 4 || name.compare(name.size() - 4, 4, ".odf") != 0)
                            continue;
                        entry.files.emplace(std::move(name), it->path());
                    }
                    catch (...)
                    {
                    }
                }

                index.directories.push_back(std::move(entry));
            }
            return index;
        }

        // Same order and preference as FindOdfFile.
        inline bool FindOdfFileInIndex(const OdfDirectoryIndex& index,
                                       const std::string& token,
                                       std::filesystem::path& outPath)
        {
            outPath.clear();
            const std::string lowerToken = LowerAscii(token);
            const std::string mpName = lowerToken + "_mp.odf";
            const std::string normalName = lowerToken + ".odf";
            for (const auto& directory : index.directories)
            {
                auto found = directory.files.find(mpName);
                if (found == directory.files.end())
                    found = directory.files.find(normalName);
                if (found != directory.files.end())
                {
                    outPath = found->second;
                    return true;
                }
            }
            return false;
        }
    }
}
