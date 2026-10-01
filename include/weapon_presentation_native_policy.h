#pragma once

#include "weapon_presentation.h"

#include <charconv>
#include <cmath>
#include <limits>
#include <optional>
#include <string_view>

namespace BZROpenShim::WeaponPresentation::NativePolicy
{
    // Native ParameterDB lowercases ASCII and uses FNV-1a/32 separately for
    // section and key (two stack DWORDs), rather than a packed string token.
    constexpr uint32_t Hash(std::string_view value) noexcept
    {
        uint32_t result = 0x811c9dc5u;
        for (unsigned char c : value)
        {
            if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
            result = (result ^ c) * 0x01000193u;
        }
        return result;
    }
    static_assert(Hash("WeaponClass") == 0xacda90abu);
    static_assert(Hash("GameObjectClass") == 0xd3dd9cecu);
    static_assert(Hash("BuildingClass") == 0x91e9360fu);

    inline std::string_view Trim(std::string_view value) noexcept
    {
        while (!value.empty() && (value.front() == ' ' || value.front() == '\t'))
            value.remove_prefix(1);
        while (!value.empty() && (value.back() == ' ' || value.back() == '\t'))
            value.remove_suffix(1);
        return value;
    }

    // Preserve case, accept native quoted ODF strings, reject malformed quotes.
    inline std::optional<std::string_view> Name(std::string_view value) noexcept
    {
        value = Trim(value);
        if (!value.empty() && value.front() == '"')
        {
            if (value.size() < 2 || value.back() != '"') return std::nullopt;
            value.remove_prefix(1);
            value.remove_suffix(1);
        }
        for (unsigned char c : value)
            if (c < 0x20 || c > 0x7e || c == '"') return std::nullopt;
        return value;
    }

    // A malformed present duration must disable, never silently inherit.
    inline float Duration(std::string_view value) noexcept
    {
        value = Trim(value);
        if (!value.empty() && value.front() == '+') value.remove_prefix(1);
        if (value.empty()) return std::numeric_limits<float>::quiet_NaN();
        float parsed = 0;
        const auto result = std::from_chars(value.data(), value.data() + value.size(), parsed);
        if (result.ec != std::errc{} || result.ptr != value.data() + value.size() ||
            !std::isfinite(parsed) || parsed <= 0)
            return std::numeric_limits<float>::quiet_NaN();
        return parsed;
    }
}
