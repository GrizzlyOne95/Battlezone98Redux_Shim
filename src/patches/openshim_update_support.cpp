#include "openshim_update_support.h"

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#endif

namespace BZROpenShim
{
    bool RepairOpenShimUpdateSupport(const std::filesystem::path& itemDirectory,
                                     const std::filesystem::path& gameRoot,
                                     const OpenShimUpdateManifest& manifest,
                                     const OpenShimPayloadVerifier& verify,
                                     bool& changed,
                                     std::string& error)
    {
        changed = false;
        error.clear();
        const auto configSource = itemDirectory / "openshim.ini.payload";
        const auto assetSource = itemDirectory / "OpenShimAssets.ini.payload";
        // Validate both before changing anything, even if player settings exist.
        if (!verify(configSource, manifest.playerConfig, error) ||
            !verify(assetSource, manifest.assetManifest, error))
            return false;

        struct SupportFile
        {
            std::filesystem::path source;
            std::filesystem::path destination;
            const OpenShimUpdatePayloadManifest* metadata;
            bool preserve;
        };
        const SupportFile files[] = {
            { configSource, gameRoot / "openshim.ini", &manifest.playerConfig, true },
            { assetSource, gameRoot / "openshim" / "OpenShimAssets.ini", &manifest.assetManifest, false },
        };
        for (const auto& file : files)
        {
            std::error_code ec;
            const bool exists = std::filesystem::exists(file.destination, ec);
            if (ec) { error = "could not inspect support file: " + ec.message(); return false; }
            std::string ignored;
            if ((file.preserve && exists) || verify(file.destination, *file.metadata, ignored))
                continue;
            std::filesystem::create_directories(file.destination.parent_path(), ec);
            if (ec) { error = "could not create support folder: " + ec.message(); return false; }
            // Verify a private copy before promoting it; a changed Workshop
            // download must not replace installed files with unverified bytes.
            const auto pending = std::filesystem::path(file.destination.wstring() + L".pending");
            std::filesystem::copy_file(file.source, pending,
                                      std::filesystem::copy_options::overwrite_existing, ec);
            if (ec) { error = "could not copy support file: " + ec.message(); return false; }
            if (!verify(pending, *file.metadata, error))
            {
                std::filesystem::remove(pending, ec);
                return false;
            }
#if defined(_WIN32)
            // No overwrite for settings, even if created during the check.
            const DWORD flags = MOVEFILE_WRITE_THROUGH | (file.preserve ? 0 : MOVEFILE_REPLACE_EXISTING);
            if (!MoveFileExW(pending.c_str(), file.destination.c_str(), flags))
                ec = std::error_code(static_cast<int>(GetLastError()), std::system_category());
#else
            if (file.preserve)
            {
                // POSIX rename replaces existing files; link creates exclusively.
                std::filesystem::create_hard_link(pending, file.destination, ec);
                if (!ec) std::filesystem::remove(pending, ec);
            }
            else
                std::filesystem::rename(pending, file.destination, ec);
#endif
            if (ec)
            {
                error = "could not install support file: " + ec.message();
                std::filesystem::remove(pending, ec);
                return false;
            }
            changed = true;
            if (!verify(file.destination, *file.metadata, error))
                return false;
        }
        return true;
    }
}
