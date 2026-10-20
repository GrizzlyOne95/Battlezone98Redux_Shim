#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <string_view>

namespace BZROpenShim::TerrainHdMaterial
{
    inline bool HasDefine(const std::string& defines, std::string_view name)
    {
        const auto identifier = [](char c) { return (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'; };
        size_t at = 0;
        while ((at = defines.find(name, at)) != std::string::npos)
        {
            if ((!at || !identifier(defines[at - 1])) &&
                (at + name.size() == defines.size() || !identifier(defines[at + name.size()]))) return true;
            at += name.size();
        }
        return false;
    }

    inline std::array<uint8_t, 256> IdentityRemap()
    {
        std::array<uint8_t, 256> result{};
        for (unsigned i = 0; i < result.size(); ++i) result[i] = uint8_t(i);
        return result;
    }

    // The stock tile identity stays in CPU semantics. Only uploaded GPU slice
    // indices are remapped, so aliases can share one physical texture layer.
    inline bool Remap(const std::array<uint8_t, 256>& table, unsigned tile,
        unsigned slices, uint8_t& out) noexcept
    {
        if (tile >= table.size() || !slices || slices > 256 || table[tile] >= slices) return false;
        out = table[tile]; return true;
    }

    inline bool ReplaceOnce(std::string& source, std::string_view from, std::string_view to)
    {
        const auto at = source.find(from);
        if (at == std::string::npos || source.find(from, at + from.size()) != std::string::npos) return false;
        source.replace(at, from.size(), to); return true;
    }

    // These are the released per-pixel terrain shader contracts, not a rewrite
    // for arbitrary custom shaders. Failure leaves the caller's source intact.
    inline bool Specialize(std::string& source, const std::array<bool, 3>& enabled)
    {
        auto result = source;
        constexpr const char* names[] = {"normal", "specular", "emissive"};
        constexpr unsigned slots[] = {2, 3, 4};
        for (unsigned i = 0; i < enabled.size(); ++i)
        {
            if (!enabled[i]) continue;
            const std::string name = names[i];
            const std::string decl = "uniform Texture2D " + name + "Map : register(t" + std::to_string(slots[i]) + "),";
            const std::string arrayDecl = "uniform Texture2DArray " + name + "Map : register(t" + std::to_string(slots[i]) + "),";
            const std::string sample = name + "Map.Sample(" + name + "Sam, vTexCoord)";
            const std::string arraySample = name + "Map.Sample(" + name + "Sam, float3(openShimHdUV, openShimTileSlice))";
            if (!ReplaceOnce(result, decl, arrayDecl) || !ReplaceOnce(result, sample, arraySample)) return false;
        }
        if (enabled[0] && !ReplaceOnce(result,
            "cotangent_frame(geometryNormal, vViewPosition.xyz, vTexCoord)",
            "cotangent_frame(geometryNormal, vViewPosition.xyz, openShimHdUV)")) return false;
        source.swap(result); return true;
    }
}
