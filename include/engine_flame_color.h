#pragma once

#include <string_view>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstdint>

namespace BZROpenShim::EngineFlameColor
{
    // Keep EXU's public 0..3 ABI; 4 and 5 are local texture variants.
    inline constexpr int Unspecified = -1;
    inline constexpr int RgbTag = 0x01000000;

    inline bool IsRgb(int color) { return (color & ~0x00FFFFFF) == RgbTag; }

    inline uint32_t TintVertex(uint32_t stock, uint32_t rgb)
    {
        return (stock & 0xFF000000u) | (rgb & 0x00FFFFFFu);
    }

    inline std::string_view Trim(std::string_view text)
    {
        const auto first = text.find_first_not_of(" \t\r\n");
        if (first == text.npos)
            return {};
        return text.substr(first, text.find_last_not_of(" \t\r\n") - first + 1);
    }

    inline bool Equal(std::string_view a, std::string_view b)
    {
        if (a.size() != b.size())
            return false;
        for (size_t i = 0; i < a.size(); ++i)
        {
            char c = a[i];
            if (c >= 'A' && c <= 'Z')
                c = static_cast<char>(c + ('a' - 'A'));
            if (c != b[i])
                return false;
        }
        return true;
    }

    inline int Parse(std::string_view value)
    {
        value = Trim(value);
        if (value.size() >= 2 && (value.front() == '"' || value.front() == '\'') &&
            value.back() == value.front())
            value = value.substr(1, value.size() - 2);
        constexpr std::string_view names[] = { "default", "blue", "red", "green", "orange", "blackdog" };
        for (int i = 0; i < 6; ++i)
            if (Equal(value, names[i]))
                return i;
        // Exact three-component normalized RGB. Never clamp typos into colors.
        const std::string numbers(value);
        const char* cursor = numbers.c_str();
        int rgb = RgbTag;
        for (int shift : {16, 8, 0})
        {
            char* end = nullptr;
            const float component = std::strtof(cursor, &end);
            if (end == cursor || !std::isfinite(component) || component < 0 || component > 1)
                return Unspecified;
            rgb |= static_cast<int>(component * 255.0f + 0.5f) << shift;
            if (shift && *end != ' ' && *end != '\t')
                return Unspecified;
            cursor = end;
        }
        if (!Trim(cursor).empty())
            return Unspecified;
        return rgb;
    }

    inline int ReadOdf(std::string_view text)
    {
        text = text.substr(0, text.find('\0'));
        bool hoverCraft = false;
        int color = Unspecified;
        while (!text.empty())
        {
            const auto end = text.find('\n');
            auto line = text.substr(0, end);
            text = end == text.npos ? std::string_view{} : text.substr(end + 1);
            // ODF comments may follow quoted values; ignore markers in quotes.
            char quote = 0;
            for (size_t i = 0; i < line.size(); ++i)
            {
                const char c = line[i];
                if (quote)
                {
                    if (c == quote)
                        quote = 0;
                }
                else if (c == '"' || c == '\'')
                    quote = c;
                else if (c == ';' || c == '#' ||
                         (c == '/' && i + 1 < line.size() && line[i + 1] == '/'))
                {
                    line = line.substr(0, i);
                    break;
                }
            }
            line = Trim(line);
            if (line.empty())
                continue;
            if (line.front() == '[')
            {
                const auto section = Trim(line.substr(1, line.size() - 2));
                hoverCraft = line.back() == ']' &&
                    (Equal(section, "hovercraftclass") || Equal(section, "hovercraft"));
                continue;
            }
            const auto equals = line.find('=');
            if (hoverCraft && equals != line.npos && Equal(Trim(line.substr(0, equals)), "flamecolor"))
                color = Parse(line.substr(equals + 1));
        }
        return color;
    }

    inline int Select(int exu, int odf, bool factionEnabled, char faction)
    {
        if (exu > 0 && exu <= 3)
            return exu;
        if ((odf >= 0 && odf <= 5) || IsRgb(odf))
            return odf;
        if (factionEnabled)
        {
            switch (faction)
            {
            case 'a': return 1;
            case 's': return 4;
            case 'c': return 3;
            case 'b': return 5;
            }
        }
        return 0;
    }
}
