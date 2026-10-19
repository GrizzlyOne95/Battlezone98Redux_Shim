#pragma once
#include <cstdint>
#include <optional>
#include <string_view>

namespace BZROpenShim::HudColors
{
    inline bool Equals(std::string_view a, std::string_view b)
    {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i)
        {
            const auto lower = [](char c) { return c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c; };
            if (lower(a[i]) != lower(b[i])) return false;
        }
        return true;
    }

    // An absent/invalid choice keeps the selected layout's native palette.
    // Custom values are packed ARGB, independent of the shared engine palette.
    inline std::optional<uint32_t> Parse(std::string_view text)
    {
        if (Equals(text, "White")) return 0xFFFFFFFFu;
        if (Equals(text, "Blue")) return 0xFF4080FFu;
        if (Equals(text, "Green")) return 0xFF40FF40u;
        if (Equals(text, "Cyan")) return 0xFF40FFFFu;
        if (Equals(text, "Amber")) return 0xFFFFC040u;
        if (Equals(text, "Magenta")) return 0xFFFF60FFu;
        if (Equals(text, "Red")) return 0xFFFF4040u;
        if (Equals(text, "Yellow")) return 0xFFFFFF40u;
        if (text.size() > 0 && text[0] == '#') text.remove_prefix(1);
        else if (text.size() > 2 && text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) text.remove_prefix(2);
        else return std::nullopt;
        if (text.size() != 6 && text.size() != 8) return std::nullopt;
        uint32_t color = text.size() == 6 ? 0xFFu : 0u;
        for (char c : text)
        {
            unsigned digit;
            if (c >= '0' && c <= '9') digit = c - '0';
            else if (c >= 'a' && c <= 'f') digit = c - 'a' + 10;
            else if (c >= 'A' && c <= 'F') digit = c - 'A' + 10;
            else return std::nullopt;
            color = (color << 4) | digit;
        }
        return color;
    }
}
