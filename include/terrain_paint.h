#pragma once
#include <array>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <locale>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace BZROpenShim::TerrainPaint
{
    struct Config
    {
        bool enabled = false;
        std::string fingerprint;
        // Native world metres: min X, min Z, max X, max Z. PNG row 0 is min Z.
        std::array<float, 4> bounds = {};
        std::array<float, 4> repeatMeters = {};
        // 5 slices: diffuse 0-3, control 4. 9 slices adds the full material:
        // diffuse alpha is specular, slices 5-8 hold tangent normal RGB with
        // height in alpha, used for height-aware blending and displacement.
        unsigned sliceCount = 5;
        float heightBlend = 0.5f;
        std::array<float, 4> heightMeters = {};
        bool Material() const { return sliceCount == 9; }
        // Optional multi-map table. Several campaign maps share one atlas
        // material, so a single pack lists one entry per terrain shape; the
        // entry matching the live fingerprint and bounds supplies the control
        // image (array slice 4). Empty means the single-map form above.
        struct MapEntry
        {
            std::string fingerprint;
            std::array<float, 4> bounds = {};
            std::string control;
        };
        std::vector<MapEntry> maps;
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
            if (sliceCount != 5 && sliceCount != 9)
                throw std::runtime_error("paint packs have 5 or 9 array slices");
            if (!std::isfinite(heightBlend) || heightBlend < 0 || heightBlend > 4)
                throw std::runtime_error("paint heightBlend must be 0..4");
            for (float v : heightMeters) if (!std::isfinite(v) || v < 0 || v > 32)
                throw std::runtime_error("paint heightMeters must be 0..32 metres");
            if (!Material() && heightMeters != std::array<float, 4>{})
                throw std::runtime_error("paint heightMeters needs the 9-slice material form");
            for (std::size_t i = 0; i < maps.size(); ++i)
            {
                const auto& map = maps[i];
                if (map.fingerprint.size() != 16 || map.fingerprint.find_first_not_of("0123456789abcdef") != std::string::npos)
                    throw std::runtime_error("paint map fingerprint must be 16 lowercase hex digits");
                for (float v : map.bounds) if (!std::isfinite(v) || std::abs(v) > 1000000)
                    throw std::runtime_error("paint map bounds must be finite native world metres");
                if (map.bounds[2] <= map.bounds[0] || map.bounds[3] <= map.bounds[1])
                    throw std::runtime_error("paint map bounds must have positive extents");
                if (map.control.empty())
                    throw std::runtime_error("paint map needs a control image resource");
                for (std::size_t j = 0; j < i; ++j)
                    if (maps[j].fingerprint == map.fingerprint && maps[j].bounds == map.bounds)
                        throw std::runtime_error("paint map table lists the same terrain twice");
            }
        }
    };

    // Picks the table entry for the live terrain. A fingerprint or bounds
    // mismatch selects nothing, so a pack never paints the wrong mission.
    inline const Config::MapEntry* SelectMap(const Config& config, const std::string& fingerprint,
        const std::array<float, 4>& bounds)
    {
        for (const auto& map : config.maps)
            if (map.fingerprint == fingerprint && map.bounds == bounds) return &map;
        return nullptr;
    }

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
float4 OpenShimPaintWeights(Texture2DArray tex, SamplerState sam, float2 worldXZ)
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
#if OPENSHIM_PAINT_MATERIAL
    // Height-aware blend: the taller layer wins inside a transition, so rock
    // pokes through sand at its crests instead of cross-fading.
    float4 heights = float4(
        OPENSHIM_PAINT_SAMPLE(tex, sam, float3(worldXZ / openShimPaintRepeats.x, 5)).a,
        OPENSHIM_PAINT_SAMPLE(tex, sam, float3(worldXZ / openShimPaintRepeats.y, 6)).a,
        OPENSHIM_PAINT_SAMPLE(tex, sam, float3(worldXZ / openShimPaintRepeats.z, 7)).a,
        OPENSHIM_PAINT_SAMPLE(tex, sam, float3(worldXZ / openShimPaintRepeats.w, 8)).a);
    float4 lifted = weights + heights * openShimPaintHeightBlend;
    float crest = max(max(lifted.x, lifted.y), max(lifted.z, lifted.w));
    float4 kept = max(lifted - (crest - 0.2), 0) * step(0.002, weights);
    float keptTotal = dot(kept, float4(1,1,1,1));
    weights = keptTotal > 0.00001 ? kept / keptTotal : weights;
#endif
    return weights;
}
#define OPENSHIM_PAINT_LAYERS(tex, sam, worldXZ, weights, base) ( \
    OPENSHIM_PAINT_SAMPLE(tex, sam, float3((worldXZ) / openShimPaintRepeats.x, (base) + 0)) * (weights).x + \
    OPENSHIM_PAINT_SAMPLE(tex, sam, float3((worldXZ) / openShimPaintRepeats.y, (base) + 1)) * (weights).y + \
    OPENSHIM_PAINT_SAMPLE(tex, sam, float3((worldXZ) / openShimPaintRepeats.z, (base) + 2)) * (weights).z + \
    OPENSHIM_PAINT_SAMPLE(tex, sam, float3((worldXZ) / openShimPaintRepeats.w, (base) + 3)) * (weights).w)
float4 OpenShimSampleTerrainPaint(Texture2DArray tex, SamplerState sam, float2 worldXZ)
{
    float4 weights = OpenShimPaintWeights(tex, sam, worldXZ);
    // The fourth control channel is a weight, never terrain transparency, and
    // diffuse alpha (specular in the material form) is not the detail weight.
    return float4(OPENSHIM_PAINT_LAYERS(tex, sam, worldXZ, weights, 0).rgb, 1);
}
#if OPENSHIM_PAINT_MATERIAL
// Packed tangent normal (mode 0 RGB: +x along world X, +y along world Z),
// blended before unpacking; the lighting path renormalizes.
float4 OpenShimSampleTerrainPaintNormal(Texture2DArray tex, SamplerState sam, float2 worldXZ)
{
    float4 weights = OpenShimPaintWeights(tex, sam, worldXZ);
    return float4(OPENSHIM_PAINT_LAYERS(tex, sam, worldXZ, weights, 5).rgb, 1);
}
float3 OpenShimSampleTerrainPaintSpecular(Texture2DArray tex, SamplerState sam, float2 worldXZ)
{
    float4 weights = OpenShimPaintWeights(tex, sam, worldXZ);
    return OPENSHIM_PAINT_LAYERS(tex, sam, worldXZ, weights, 0).aaa;
}
#endif
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
            if (config.Material())
            {
                // The paint array rides in t0, so normal and specular come from
                // it too; the stock atlas maps would follow the wrong UVs.
                // A pass that never samples a map (the glow pass has colour
                // only) keeps that part unchanged; a pass that samples it in
                // an unknown form declines.
                struct Swap { const char* from; const char* to; const char* use; };
                const Swap swaps[] = {
                    {"normalMap.Sample(normalSam, vTexCoord)", "OpenShimSampleTerrainPaintNormal(diffuseMap, diffuseSam, openShimHdUV)", "normalMap.Sample"},
                    {"specularMap.Sample(specularSam, vTexCoord).xyz", "OpenShimSampleTerrainPaintSpecular(diffuseMap, diffuseSam, openShimHdUV)", "specularMap.Sample"},
                    {"cotangent_frame(geometryNormal, vViewPosition.xyz, vTexCoord)",
                     "cotangent_frame(geometryNormal, vViewPosition.xyz, openShimHdUV)", "cotangent_frame(geometryNormal"},
                    // Vertex tangents follow the stock atlas UVs; no terrain
                    // program defines them today, but never mix the frames.
                    {"float3x3 tbn = float3x3(baseTangent, binormal, baseNormal);",
                     "float3x3 tbn = cotangent_frame(geometryNormal, vViewPosition.xyz, openShimHdUV);", nullptr},
                };
                for (const auto& swap : swaps)
                {
                    const auto at = source.find(swap.from);
                    if (at == std::string::npos) { if (swap.use && source.find(swap.use) != std::string::npos) return false; continue; }
                    source.replace(at, std::strlen(swap.from), swap.to);
                }
            }
            std::ostringstream constants; constants.imbue(std::locale::classic()); constants << std::setprecision(9) << std::scientific;
            constants << "#define OPENSHIM_PAINT_MATERIAL " << (config.Material() ? 1 : 0) << "\n";
            constants << "static const float4 openShimPaintBounds = float4(";
            for (int i = 0; i < 4; ++i) constants << (i ? "," : "") << config.bounds[i];
            constants << ");\nstatic const float4 openShimPaintRepeats = float4(";
            for (int i = 0; i < 4; ++i) constants << (i ? "," : "") << config.repeatMeters[i];
            constants << ");\nstatic const float openShimPaintHeightBlend = " << config.heightBlend;
            source.insert(0, constants.str() + ";\n" + BlendHlsl());
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
