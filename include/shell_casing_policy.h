#pragma once
#include <string_view>

namespace BZROpenShim::ShellCasings
{
    enum class CasingType { None, Small, Medium, Large };

    // Explicit presentation choice, never inferred from Cannon/MachineGun RTTI:
    // those classes also implement plasma and other energy weapons.
    inline CasingType ParseCasingType(std::string_view value) noexcept
    {
        const auto begin = value.find_first_not_of(" \t\r\n");
        if (begin == value.npos) return CasingType::None;
        value = value.substr(begin, value.find_last_not_of(" \t\r\n") - begin + 1);
        if (value.size() >= 2 && value.front() == '"' && value.back() == '"')
            value = value.substr(1, value.size() - 2);
        if (value == "small") return CasingType::Small;
        if (value == "medium") return CasingType::Medium;
        if (value == "large") return CasingType::Large;
        return CasingType::None; // malformed/unknown/explicit none all fail closed
    }

    inline CasingType StockCasingType(std::string_view odf) noexcept
    {
        // Only known stock ballistic weapons. Unknown mods opt in through ODF.
        char normalized[20] = {};
        if (odf.size() >= sizeof(normalized)) return CasingType::None;
        for (size_t i = 0; i < odf.size(); ++i)
            normalized[i] = odf[i] >= 'A' && odf[i] <= 'Z' ? static_cast<char>(odf[i] + ('a' - 'A')) : odf[i];
        odf = std::string_view(normalized, odf.size());
        if (odf.size() > 4 && odf.substr(odf.size() - 4) == ".odf") odf.remove_suffix(4);
        if (odf == "gminigun" || odf == "gminigna" || odf == "gminisov" ||
            odf == "gtminig" || odf == "gtminis" || odf == "gtminis2" || odf == "gsnipe")
            return CasingType::Small;
        if (odf == "gatstab") return CasingType::Medium;
        if (odf == "gspstab" || odf == "ghartill") return CasingType::Large;
        return CasingType::None;
    }

    inline float CasingTypeLength(CasingType type) noexcept
    {
        switch (type)
        {
        case CasingType::Small: return 0.12f;
        case CasingType::Medium: return 0.24f;
        case CasingType::Large: return 0.40f;
        default: return 0.0f;
        }
    }
}
