#pragma once

#include <cstddef>
#include <cstdint>

namespace BZROpenShim::CampaignManifestId
{
    // An absent or malformed author-supplied ID retains Redux's folder key.
    // These are registry identities, never resource paths.
    inline bool ValidId(const char* id, std::size_t size)
    {
        if (!id || size == 0 || size > 63) return false;
        for (std::size_t i = 0; i < size; ++i)
        {
            const unsigned char c = static_cast<unsigned char>(id[i]);
            const bool alnum = (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
            if (!alnum && (i == 0 || (c != '_' && c != '-'))) return false;
        }
        return true;
    }

    void* PrepareThunk(std::uint32_t callSite);
}
