// shader_source_fingerprint.h
// BZR Open Shim - fingerprint of mod shader sources for the microcode cache
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Engine-independent so the scan can be unit-tested against a temp tree.
#pragma once

#include <cstddef>
#include <cstdint>
#include <cwctype>
#include <filesystem>
#include <string>
#include <system_error>
#include <vector>

namespace BZROpenShim
{
    namespace ShaderSourceFingerprint
    {
        inline bool IsShaderSourceExtension(const std::wstring& extLower)
        {
            return extLower == L".program" || extLower == L".hlsl" ||
                   extLower == L".cg" || extLower == L".glsl" ||
                   extLower == L".glsles" || extLower == L".frag" ||
                   extLower == L".vert";
        }

        // Directories whose shader sources key the cache, relative to the game
        // root. Stock shader sources live inside the game's archives and never
        // change between sessions; mod shaders are the ones users edit.
        //
        // OpenShim's own Enhanced payload is scanned too: it is redeployed
        // whenever the DLL ships new shaders (missing until 2026-09-20).
        // addon/ was missing until 2026-11-01: an edited addon .hlsl kept
        // running the stale microcode until the cache was deleted by hand.
        inline std::vector<std::filesystem::path> ScanRoots(const std::filesystem::path& gameRoot)
        {
            return
            {
                gameRoot / L"mods",
                gameRoot / L"packaged_mods",
                gameRoot / L"addon",
                // Steam install: workshop content sits outside the game root.
                gameRoot / L".." / L".." / L"workshop" / L"content" / L"301650",
                // OpenShim's own Enhanced shader payload.
                gameRoot / L"openshim" / L"renderer" / L"enhanced",
            };
        }

        // FNV-1a over (lower-case file name, size, mtime) of every shader
        // source file under the given roots. Other files are skipped without
        // being stat'ed, so large texture/mesh trees stay cheap to walk.
        inline uint64_t Compute(const std::vector<std::filesystem::path>& scanRoots,
                                size_t* outFilesSeen = nullptr)
        {
            uint64_t hash = 1469598103934665603ull;
            const auto mix = [&hash](const void* data, size_t size)
            {
                const auto* bytes = static_cast<const uint8_t*>(data);
                for (size_t i = 0; i < size; ++i)
                {
                    hash ^= bytes[i];
                    hash *= 1099511628211ull;
                }
            };

            size_t filesSeen = 0;
            for (const auto& scanRoot : scanRoots)
            {
                std::error_code ec;
                if (!std::filesystem::is_directory(scanRoot, ec))
                    continue;
                std::filesystem::recursive_directory_iterator it(
                    scanRoot,
                    std::filesystem::directory_options::skip_permission_denied,
                    ec);
                const std::filesystem::recursive_directory_iterator end;
                for (; !ec && it != end && filesSeen < 50000; it.increment(ec))
                {
                    // Skip .git/.vs and similar: an addon kept as a git checkout
                    // holds tens of thousands of objects and no live shaders.
                    if (it->path().filename().wstring().rfind(L".", 0) == 0)
                    {
                        if (it->is_directory(ec))
                            it.disable_recursion_pending();
                        continue;
                    }

                    std::wstring ext = it->path().extension().wstring();
                    for (auto& ch : ext)
                        ch = static_cast<wchar_t>(::towlower(ch));
                    if (!IsShaderSourceExtension(ext))
                        continue;
                    if (!it->is_regular_file(ec))
                        continue;

                    std::wstring name = it->path().filename().wstring();
                    for (auto& ch : name)
                        ch = static_cast<wchar_t>(::towlower(ch));
                    mix(name.data(), name.size() * sizeof(wchar_t));
                    const uintmax_t size = it->file_size(ec);
                    mix(&size, sizeof(size));
                    const auto mtime = it->last_write_time(ec).time_since_epoch().count();
                    mix(&mtime, sizeof(mtime));
                    ++filesSeen;
                }
            }
            mix(&filesSeen, sizeof(filesSeen));
            if (outFilesSeen)
                *outFilesSeen = filesSeen;
            return hash ? hash : 1ull;
        }
    }
}
