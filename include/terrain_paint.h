#pragma once
#include <array>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <locale>
#include <sstream>
#include <stdexcept>
#include <string>

namespace BZROpenShim::TerrainPaint
{
    struct Config
    {
        bool enabled = false;
        std::string fingerprint;
        // Native world metres: min X, min Z, max X, max Z. PNG row 0 is min Z.
        std::array<float, 4> bounds = {};
        std::array<float, 4> repeatMeters = {};
        void Validate() const
        {
            if (fingerprint.size() != 16 || fingerprint.find_first_not_of("0123456789abcdef") != std::string::npos)
                throw std::runtime_error("paint terrainFingerprint must be 16 lowercase hex digits");
            for (float v : bounds) if (!std::isfinite(v) || std::abs(v) > 1000000)
                throw std::runtime_error("paint bounds must be finite native world metres");
            if (bounds[2] <= bounds[0] || bounds[3] <= bounds[1])
                throw std::runtime_error("paint bounds must have positive extents");
            for (float v : repeatMeters) if (!std::isfinite(v) || v < 1 || v > 4096)
                throw std::runtime_error("paint material repeats must be 1..4096 metres");
        }
    };

    inline void HashU32(std::uint64_t& hash, std::uint32_t value)
    {
        for (unsigned i = 0; i < 4; ++i) { hash ^= (value >> (i * 8)) & 255; hash *= UINT64_C(1099511628211); }
    }
    inline std::string HashString(std::uint64_t hash)
    {
        std::ostringstream out; out << std::hex << std::setfill('0') << std::setw(16) << hash; return out.str();
    }
    inline std::array<float, 2> WorldXZ(float localX, float localZ, float nodeX, float nodeZ)
    {
        const std::array<float, 2> result = {localX + nodeX, localZ + nodeZ};
        for (float v : result) if (!std::isfinite(v) || std::abs(v) > 1000000)
            throw std::runtime_error("paint native vertex coordinates invalid");
        return result;
    }
    inline const char* BlendHlsl()
    {
        return R"HLSL(
#ifndef OPENSHIM_PAINT_SAMPLE
// Preserve derivatives before wrapping: frac-derived gradients choose wrong
// mips at repeat boundaries. Do not depend on the native atlas sampler mode.
#define OPENSHIM_PAINT_SAMPLE(tex, sam, uv) tex.SampleGrad(sam, float3(frac((uv).xy), (uv).z), ddx((uv).xy), ddy((uv).xy))
#endif
float4 OpenShimSampleTerrainPaint(Texture2DArray tex, SamplerState sam, float2 worldXZ)
{
    uint width, height, slices;
    tex.GetDimensions(width, height, slices);
    float2 paintUV = (worldXZ - openShimPaintBounds.xy) / (openShimPaintBounds.zw - openShimPaintBounds.xy);
    float2 inset = 0.5 / float2(width, height);
    // Level zero plus a half-texel clamp prevents the shared wrapping sampler
    // from blending the opposite edge of the map into its border.
    float4 weights = max(tex.SampleLevel(sam, float3(clamp(paintUV, inset, 1.0-inset), 4), 0), 0);
    float total = dot(weights, float4(1,1,1,1));
    weights = total > 0.00001 ? weights / total : float4(1,0,0,0);
    float3 rgb =
        OPENSHIM_PAINT_SAMPLE(tex, sam, float3(worldXZ / openShimPaintRepeats.x, 0)).rgb * weights.x +
        OPENSHIM_PAINT_SAMPLE(tex, sam, float3(worldXZ / openShimPaintRepeats.y, 1)).rgb * weights.y +
        OPENSHIM_PAINT_SAMPLE(tex, sam, float3(worldXZ / openShimPaintRepeats.z, 2)).rgb * weights.z +
        OPENSHIM_PAINT_SAMPLE(tex, sam, float3(worldXZ / openShimPaintRepeats.w, 3)).rgb * weights.w;
    // The fourth control channel is a weight, never terrain transparency.
    return float4(rgb, 1);
}
)HLSL";
    }
    inline bool Specialize(std::string& source, bool pixel, const Config& config)
    {
        config.Validate();
        if (pixel)
        {
            const std::string token = "diffuseMap.Sample(diffuseSam, float3(openShimHdUV, openShimTileSlice))";
            const auto offset = source.find(token);
            if (offset == std::string::npos) return false;
            source.replace(offset, token.size(), "OpenShimSampleTerrainPaint(diffuseMap, diffuseSam, openShimHdUV)");
            std::ostringstream constants; constants.imbue(std::locale::classic()); constants << std::setprecision(9) << std::scientific;
            constants << "static const float4 openShimPaintBounds = float4(";
            for (int i = 0; i < 4; ++i) constants << (i ? "," : "") << config.bounds[i];
            constants << ");\nstatic const float4 openShimPaintRepeats = float4(";
            for (int i = 0; i < 4; ++i) constants << (i ? "," : "") << config.repeatMeters[i];
            source.insert(0, constants.str() + ");\n" + BlendHlsl());
        }
        else
        {
            const auto begin = source.find("    float2 openShimOrientedUV =");
            const auto end = source.find(';', source.find("    vTexCoord =", begin));
            if (begin == std::string::npos || end == std::string::npos) return false;
            // localUV carries audited native world XZ in paint mode. Auxiliary
            // maps must retain the original packed UV expression verbatim.
            source.replace(begin, end - begin + 1,
                "    openShimHdUV = openShimLocalUV;\n    openShimTileSlice = 0;\n    vTexCoord = openShimStockUV;");
        }
        return true;
    }
}
