#pragma once
// Pure policy of single-player player paint (Docs/SP_PLAYER_PAINT.md):
// the variant table, the stock material -> mask table, and the clone naming
// src/patches/sp_player_paint.cpp uses. No Ogre or engine access; host tested.
#include <cstddef>
#include <cstring>
#include <string>
#include <string_view>

namespace BZROpenShim::SpPlayerPaint
{
    // One paint choice. rgba feeds the shader's teamPaint uniform:
    // a > 1.5 turns paint on; rgb is the solid sRGB colour (rgb = 0 would be
    // camo, which OpenShim's single-channel masks cannot carry).
    // Add a row here (and to the Options row values) to offer a new paint.
    struct Variant
    {
        const char* key;    // [SinglePlayer] PlayerPaint value, clone suffix
        float rgba[4];
    };

    // The co-op tints of Campaign Reimagined's CRTeamSkins.lua (t2, t3, t4).
    inline constexpr Variant kVariants[] = {
        { "t2", { 0.80f, 0.18f, 0.12f, 2.0f } },  // red
        { "t3", { 0.20f, 0.38f, 0.85f, 2.0f } },  // blue
        { "t4", { 0.90f, 0.68f, 0.12f, 2.0f } },  // gold
    };

    // Null for "stock", empty, or an unknown key.
    inline const Variant* FindVariant(std::string_view key)
    {
        for (const Variant& v : kVariants)
        {
            const size_t n = std::strlen(v.key);
            if (key.size() != n)
                continue;
            bool same = true;
            for (size_t i = 0; i < n && same; ++i)
            {
                char c = key[i];
                if (c >= 'A' && c <= 'Z')
                    c = static_cast<char>(c - 'A' + 'a');
                same = c == v.key[i];
            }
            if (same)
                return &v;
        }
        return nullptr;
    }

    struct MaskEntry
    {
        const char* material;  // stock material name, lower case
        const char* mask;      // BC4 mask file in openshim/renderer/enhanced
    };

    inline constexpr MaskEntry kMasks[] = {
#include "sp_player_paint_masks.inc"
    };

    // Marks every clone this feature makes: <source>@ospaint_<variant key>.
    inline constexpr std::string_view kCloneTag = "@ospaint_";

    inline bool IsPaintClone(std::string_view name)
    {
        return name.find(kCloneTag) != std::string_view::npos;
    }

    // The material name before any paint suffix.
    inline std::string_view StripPaintSuffix(std::string_view name)
    {
        const size_t at = name.find(kCloneTag);
        return at == std::string_view::npos ? name : name.substr(0, at);
    }

    inline std::string CloneName(std::string_view current, const Variant& variant)
    {
        std::string out(StripPaintSuffix(current));
        out += kCloneTag;
        out += variant.key;
        return out;
    }

    // The clone of `current` for `variant` is already on the sub-entity:
    // ours, or GPU skinning's clone of ours.
    inline bool PaintedWith(std::string_view current, const Variant& variant)
    {
        const size_t at = current.find(kCloneTag);
        return at != std::string_view::npos && current.substr(at + kCloneTag.size()) == variant.key;
    }

    // Stock material name behind a sub-entity's current material: drops the
    // GPU-skinning clone path ("OpenShim/GpuSkin/<gen>/<tag>/<source>"), any
    // paint suffix, and Campaign Reimagined's "_tm" team twin suffix.
    inline std::string_view SourceKey(std::string_view current)
    {
        const size_t slash = current.rfind('/');
        if (slash != std::string_view::npos)
            current = current.substr(slash + 1);
        current = StripPaintSuffix(current);
        if (current.size() > 3 && current.substr(current.size() - 3) == "_tm")
            current = current.substr(0, current.size() - 3);
        return current;
    }

    // The OpenShim mask for a stock material (case-insensitive), or null.
    inline const char* FindMask(std::string_view key)
    {
        for (const MaskEntry& e : kMasks)
        {
            const size_t n = std::strlen(e.material);
            if (key.size() != n)
                continue;
            bool same = true;
            for (size_t i = 0; i < n && same; ++i)
            {
                char c = key[i];
                if (c >= 'A' && c <= 'Z')
                    c = static_cast<char>(c - 'A' + 'a');
                same = c == e.material[i];
            }
            if (same)
                return e.mask;
        }
        return nullptr;
    }

    // Paint applies to en-high techniques only (en-high, en-high-pssm,
    // en-high-noshadow): the only ones whose programs declare teamPaint.
    inline bool IsPaintScheme(std::string_view scheme)
    {
        return scheme.substr(0, 7) == "en-high";
    }
}
