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

    struct MeshFlashFields
    {
        std::optional<std::string_view> mesh, material, duration, scale, endScale, offset, roll;
    };

    inline float Scalar(std::string_view text) noexcept
    {
        text = Trim(text);
        if (!text.empty() && text.front() == '+') text.remove_prefix(1);
        float value = 0;
        if (text.empty()) return std::numeric_limits<float>::quiet_NaN();
        const auto parsed = std::from_chars(text.data(), text.data() + text.size(), value);
        return parsed.ec == std::errc{} && parsed.ptr == text.data() + text.size() && std::isfinite(value)
            ? value : std::numeric_limits<float>::quiet_NaN();
    }

    // No filesystem lookups: names are engine resource names, preserving case.
    // Explicitly empty/invalid mesh disables the flash, including inheritance.
    inline FlashConfig ResolveMeshFlashConfig(const FlashConfig& parent, const MeshFlashFields& fields)
    {
        FlashConfig result = parent.IsMesh() ? parent : FlashConfig{};
        result.effect.clear();
        if (!parent.IsMesh()) result.duration = 0.08f;
        if (fields.mesh)
        {
            auto name = Name(*fields.mesh);
            if (!name || name->empty()) return {};
            result.mesh = *name;
        }
        if (fields.material)
        {
            auto name = Name(*fields.material);
            if (!name) return {};
            result.material = *name;
        }
        if (fields.duration) result.duration = Scalar(*fields.duration);
        if (fields.scale) result.startScale = result.finishScale = Scalar(*fields.scale);
        if (fields.endScale) result.finishScale = Scalar(*fields.endScale);
        if (fields.roll) result.rollDegrees = Scalar(*fields.roll);
        if (fields.offset)
        {
            auto name = Name(*fields.offset);
            if (!name) return {};
            auto remaining = Trim(*name);
            float values[3]{};
            for (float& value : values)
            {
                remaining = Trim(remaining);
                if (!remaining.empty() && remaining.front() == '+') remaining.remove_prefix(1);
                if (remaining.empty()) return {};
                auto parsed = std::from_chars(remaining.data(), remaining.data() + remaining.size(), value);
                if (parsed.ec != std::errc{} || !std::isfinite(value)) return {};
                if (parsed.ptr != remaining.data() + remaining.size() && *parsed.ptr != ' ' && *parsed.ptr != '\t') return {};
                remaining.remove_prefix(static_cast<size_t>(parsed.ptr - remaining.data()));
            }
            if (!Trim(remaining).empty()) return {};
            result.offset = {values[0], values[1], values[2]};
        }
        return result.IsMesh() && result.Valid() ? result : FlashConfig{};
    }
}
