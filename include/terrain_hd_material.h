#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <cmath>
#include <iomanip>
#include <locale>
#include <sstream>
#include "render_profile.h"

namespace BZROpenShim::TerrainHdMaterial
{
    struct DetailTuning
    {
        float contrast = .55f;
        float normalStrength = 2.2f;
        float nearNormalScale = .55f;
    };

    inline bool ValidDetailTuning(const DetailTuning& value)
    {
        return std::isfinite(value.contrast) && value.contrast >= 0 && value.contrast <= 1 &&
            std::isfinite(value.normalStrength) && value.normalStrength >= 0 && value.normalStrength <= 4 &&
            std::isfinite(value.nearNormalScale) && value.nearNormalScale >= 0 && value.nearNormalScale <= 1;
    }

    inline bool ValidMicroReliefScale(float scale)
    {
        return std::isfinite(scale) && scale >= 0.0f && scale <= 4.0f;
    }

    // Keep the existing one-meter displacement envelope, including when a
    // diagnostic environment override changes the baseline amplitude.
    inline float ScaledMicroReliefAmplitude(float base, float scale)
    {
        if (!std::isfinite(base) || base < 0.0f || base > 1.0f ||
            !ValidMicroReliefScale(scale)) return 0.0f;
        const float amplitude = base * scale;
        return amplitude > 1.0f ? 1.0f : amplitude;
    }

    inline bool ProfileAllowsTiles(uint32_t backend, uint32_t profile)
    {
        return backend == uint32_t(RenderProfiles::ActiveBackend::DX11) &&
            profile == RenderProfiles::Abi::kProfileEnhanced;
    }

    struct RectBinding { std::array<float, 4> rect; uint8_t slice; };
    inline bool ValidRect(const std::array<float, 4>& rect)
    {
        for (float value : rect) if (!std::isfinite(value)) return false;
        return rect[0] >= 0 && rect[1] >= 0 && rect[2] > 0 && rect[3] > 0 &&
            rect[0] + rect[2] <= 1.000001f && rect[1] + rect[3] <= 1.000001f;
    }
    inline bool FindRectSlice(const std::vector<RectBinding>& bindings,
        const std::array<float, 4>& rect, uint8_t& slice)
    {
        if (!ValidRect(rect)) return false;
        bool found = false;
        for (const auto& binding : bindings)
        {
            bool matches = true;
            for (unsigned c = 0; c < 4; ++c)
                matches = matches && std::abs(binding.rect[c] - rect[c]) <= 0.000001f;
            if (!matches) continue;
            if (found && slice != binding.slice) return false;
            slice = binding.slice; found = true;
        }
        return found;
    }

    inline bool HasDefine(const std::string& defines, std::string_view name)
    {
        if (name.empty()) return false;
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

    // SourceHashSuffix includes this output, isolating Ogre's cache per material.
    // Defaults preserve the existing source byte-for-byte; no shared uniform.
    inline bool SpecializeDetail(std::string& source, const DetailTuning& value)
    {
        if (!ValidDetailTuning(value)) return false;
        const DetailTuning defaults;
        if (value.contrast == defaults.contrast && value.normalStrength == defaults.normalStrength &&
            value.nearNormalScale == defaults.nearNormalScale) return true;
        const auto constant = [](const char* name, float number) {
            std::ostringstream text;
            text.imbue(std::locale::classic());
            text << "static const float " << name << " = " << std::setprecision(9) << number << ";";
            return text.str();
        };
        auto result = source;
        if (!ReplaceOnce(result, "static const float OSE_TERRAIN_DETAIL_CONTRAST = 0.55;",
                constant("OSE_TERRAIN_DETAIL_CONTRAST", value.contrast)) ||
            !ReplaceOnce(result, "static const float OSE_TERRAIN_DETAIL_NORMAL_STRENGTH = 2.2;",
                constant("OSE_TERRAIN_DETAIL_NORMAL_STRENGTH", value.normalStrength)) ||
            !ReplaceOnce(result, "static const float OSE_TERRAIN_DETAIL_NORMAL_NEAR_SCALE = 0.55;",
                constant("OSE_TERRAIN_DETAIL_NORMAL_NEAR_SCALE", value.nearNormalScale))) return false;
        source.swap(result);
        return true;
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
