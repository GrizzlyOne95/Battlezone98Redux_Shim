#pragma once

#include <cstdint>
#include <filesystem>
#include <functional>
#include <string>
#include <vector>

namespace BZROpenShim
{
    struct OpenShimAssetFile
    {
        std::string path;   // relative to the set, backslash-separated
        std::string sha256; // lowercase hex
        uint64_t size = 0;
    };

    struct OpenShimAssetSet
    {
        std::string name;        // "renderer" or "customWidgets"
        std::string source;      // relative to the Workshop item directory
        std::string destination; // relative to the game directory
        std::string sha256;      // set hash, see ComputeOpenShimAssetSetHash
        uint32_t files = 0;
        std::vector<OpenShimAssetFile> entries;
    };

    struct OpenShimAssetSets
    {
        std::vector<OpenShimAssetSet> sets;
        // Names found in the manifest that this build does not know. Logged
        // by the caller; never an error.
        std::vector<std::string> ignored;
    };

    // Parses the optional assetSets/assetFiles sections of OpenShimManifest.lua
    // (one entry per line, as emitted by Campaign Reimagined). Neither section
    // present is success with no sets. A present but malformed section, an
    // unsafe path, a count mismatch or a bad hash fails the whole parse so a
    // half-trusted description is never acted on.
    bool ParseOpenShimAssetSets(const std::string& text,
                                OpenShimAssetSets& out,
                                std::string& error);

    // Lowercase hex SHA-256 of "<lowercased path>|<sha256>|<size>\n" per
    // entry, entries sorted by lowercased path (byte order).
    std::string ComputeOpenShimAssetSetHash(const std::vector<OpenShimAssetFile>& entries);

    // Portable SHA-256 (lowercase hex). The file overload streams the file.
    std::string Sha256Hex(const void* data, size_t length);
    bool Sha256HexOfFile(const std::filesystem::path& path,
                         std::string& hex,
                         uint64_t& size);

    // Marker file the sync keeps in the destination: "openshim_set.sha256"
    // for renderer, "openshim_widgets.sha256" for customWidgets, empty for an
    // unknown set.
    const char* OpenShimAssetSetMarkerName(const std::string& setName);

    // Where OpenShim's UI images lived before they moved to openshim\ui,
    // relative to the game directory. Still read as a fallback for one
    // release, and cleaned up by the installers and the customWidgets sync.
    constexpr char kOpenShimLegacyWidgetsDir[] = "BZ_ASSETS_CORE\\common\\ui\\CustomWidgets";

    // Removes from `legacyDir` only the files OpenShim owns there: each name
    // in `ownedNames` (relative, as in the manifest) plus the
    // openshim_widgets.sha256 marker. Every other file stays. The folder
    // itself goes only when it is then empty. A file that cannot be removed
    // (locked) is skipped and left for the next run. Returns the number of
    // files removed.
    uint32_t RemoveOpenShimLegacyWidgetFiles(const std::filesystem::path& legacyDir,
                                             const std::vector<std::string>& ownedNames);

    enum class OpenShimAssetSyncResult
    {
        Current,   // marker already matches; game files were not hashed
        Installed, // destination now matches the set
        Refused,   // source or validation failed; destination untouched
        Deferred,  // a destination file was locked; retried next start
    };

    struct OpenShimAssetSyncOutcome
    {
        OpenShimAssetSyncResult result = OpenShimAssetSyncResult::Refused;
        uint32_t filesInstalled = 0;
        // customWidgets only: OpenShim files removed from the legacy folder.
        uint32_t legacyFilesRemoved = 0;
        std::string detail;
    };

    // Checks a directory (the source or a freshly built copy) is usable.
    // Receives the directory and fills `problem` on failure.
    using OpenShimAssetSetValidator =
        std::function<bool(const std::filesystem::path&, std::string&)>;

    // Syncs one set from `itemDir` into `gameDir`. Each listed file is read
    // from "<path>.payload" in the Workshop item when that exists, else from
    // "<path>", and is always installed as "<path>". renderer swaps the whole
    // destination directory atomically (and runs `validator` on the pending
    // copy before the swap); customWidgets replaces only the listed files and
    // never removes anything else in the folder. Once customWidgets is
    // current at a destination other than kOpenShimLegacyWidgetsDir, its
    // listed files are also removed from the legacy folder
    // (RemoveOpenShimLegacyWidgetFiles), so a CR update migrates old installs.
    OpenShimAssetSyncOutcome SyncOpenShimAssetSet(
        const std::filesystem::path& itemDir,
        const std::filesystem::path& gameDir,
        const OpenShimAssetSet& set,
        const OpenShimAssetSetValidator& validator);
}
