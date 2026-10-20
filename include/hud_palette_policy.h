#pragma once
#include "hud_color_policy.h"
#include <array>
#include <algorithm>
#include <cmath>

namespace BZROpenShim::HudPalette
{
    enum class Role : size_t
    {
        RadarGrid, RadarFriendly, RadarEnemy, RadarNeutral,
        HullHigh, HullMedium, HullLow, Ammo,
        UnitHigh, UnitMedium, UnitLow, UnitAmmo, UnitEmpty, Count
    };
    inline constexpr size_t Count = static_cast<size_t>(Role::Count);
    inline constexpr const char* Keys[] = {
        "RadarGridColor", "RadarFriendlyColor", "RadarEnemyColor", "RadarNeutralColor",
        "HullHighColor", "HullMediumColor", "HullLowColor", "AmmoHudColor",
        "UnitHealthHighColor", "UnitHealthMediumColor", "UnitHealthLowColor", "UnitAmmoColor", "UnitEmptyColor"
    };
    static_assert(std::size(Keys) == Count);
    struct Settings
    {
        std::array<std::optional<uint32_t>, Count> colors{};
        int radarBackgroundOpacity = -1; // -1 retains native sprite palette/flags
        auto& operator[](Role role) { return colors[static_cast<size_t>(role)]; }
        const auto& operator[](Role role) const { return colors[static_cast<size_t>(role)]; }
        bool Active() const
        {
            return radarBackgroundOpacity >= 0 || std::any_of(colors.begin(), colors.end(), [](auto c) { return c.has_value(); });
        }
    };
    inline Settings Preset(std::string_view name)
    {
        Settings s;
        const bool contrast = HudColors::Equals(name, "HighContrast");
        if (!contrast && !HudColors::Equals(name, "Classic")) return s;
        const uint32_t high = contrast ? 0xFF40FFFFu : 0xFF00FF00u;
        const uint32_t medium = 0xFFFFC040u;
        const uint32_t low = contrast ? 0xFFFF60FFu : 0xFFFF4040u;
        s.colors = {high, high, low, 0xFFFFFFFFu, high, medium, low,
                    contrast ? 0xFFFFFFFFu : 0xFF4080FFu,
                    high, medium, low, contrast ? 0xFFFFFFFFu : 0xFF4080FFu, 0xFF202020u};
        s.radarBackgroundOpacity = contrast ? 75 : -1;
        return s;
    }
    inline Role HealthRole(float ratio, bool unit)
    {
        const auto offset = ratio < .25f ? 2u : ratio < .5f ? 1u : 0u;
        return static_cast<Role>(static_cast<size_t>(unit ? Role::UnitHigh : Role::HullHigh) + offset);
    }
    inline uint32_t Health(const Settings& s, float ratio, uint32_t stock, bool unit = false)
    {
        if (!std::isfinite(ratio) || ratio < 0) return stock;
        return s[HealthRole(ratio, unit)].value_or(stock);
    }
    inline uint32_t KeepAlpha(uint32_t stock, uint32_t color)
    {
        return (stock & 0xFF000000u) | (color & 0xFFFFFFu);
    }
    // Native radar contacts have dimmed variants as well as a separate alpha
    // animation. Preserve both instead of making a dim contact fully bright.
    inline uint32_t ContactTint(uint32_t stock, uint32_t color)
    {
        const uint32_t brightness = std::max({stock & 255u, (stock >> 8) & 255u, (stock >> 16) & 255u});
        uint32_t result = stock & 0xFF000000u;
        for (unsigned shift : {0u, 8u, 16u})
            result |= (((color >> shift) & 255u) * brightness / 255u) << shift;
        return result;
    }
}
