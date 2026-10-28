#pragma once

#include "community_key.h"

#include <array>
#include <filesystem>

namespace BZROpenShim
{
    constexpr wchar_t kCommunitySecretFileName[] = L"openshim_community.key";

    // Reads the 32-byte master secret at path, creating it from the OS RNG if
    // it does not exist yet. Creation is a write to a private temp file and a
    // no-replace rename, so two processes racing both end up with the winner's
    // bytes. Returns false (and leaves secret zeroed) on any failure: a file of
    // the wrong size, an unwritable directory, or no RNG. Callers then send no
    // key at all rather than a weak one.
    bool LoadOrCreateCommunitySecret(const std::filesystem::path& path,
                                     std::array<unsigned char, kCommunitySecretBytes>& secret);
}
