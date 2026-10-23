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
// Triplanar needs the world normal (inverse view, IBL passes only) and native
// world Y, which paint mode carries in openShimTileSlice. Passes without them
// (glow, vertex lighting) keep the top projection: the original XZ mapping.
// This runs before the shader's own #undef of IBL_ENABLED (retro mode, or
// not Enhanced), so it repeats those conditions.
#if OPENSHIM_PAINT_TRIPLANAR_SOURCE && defined(IBL_ENABLED) && defined(ENHANCED_MODE) &&     !defined(OG_RETRO_MODE) && !defined(VERTEX_LIGHTING)
#define OPENSHIM_PAINT_TRIPLANAR 1
#define OPENSHIM_PAINT_GEO OpenShimPaintGeometry(openShimHdUV, openShimTileSlice, mul(inverseViewMatrix, float4(vViewNormal, 0.0)).xyz)
#define OPENSHIM_PAINT_TBN(n) OpenShimPaintTbn(n, inverseViewMatrix)
#else
#define OPENSHIM_PAINT_TRIPLANAR 0
#define OPENSHIM_PAINT_GEO OpenShimPaintGeometry(openShimHdUV, 0.0, float3(0, 1, 0))
#define OPENSHIM_PAINT_TBN(n) cotangent_frame(n, vViewPosition.xyz, openShimHdUV)
#endif
#ifndef OPENSHIM_PAINT_SAMPLE
// Explicit gradients: frac-derived ones choose wrong mips at repeat
// boundaries, and taps inside branches have none. Do not depend on the native
// atlas sampler mode.
#define OPENSHIM_PAINT_SAMPLE(tex, sam, uv, gx, gy) tex.SampleGrad(sam, float3(frac((uv).xy), (uv).z), gx, gy)
#define OPENSHIM_PAINT_DDX(v) ddx(v)
#define OPENSHIM_PAINT_DDY(v) ddy(v)
#endif
struct OpenShimPaintGeo { float3 pos; float3 n; float3 blend; float3 flip; float3 dpdx; float3 dpdy; };
OpenShimPaintGeo OpenShimPaintGeometry(float2 worldXZ, float worldY, float3 worldNormal)
{
    OpenShimPaintGeo g;
    g.pos = float3(worldXZ.x, worldY, worldXZ.y);
    // Every projection is linear in world position, so its gradients, taken
    // here outside any branch, give each tap its own.
    g.dpdx = OPENSHIM_PAINT_DDX(g.pos);
    g.dpdy = OPENSHIM_PAINT_DDY(g.pos);
    g.n = normalize(worldNormal);
    // Sharp blend: ground under about 30 degrees keeps the single top tap and
    // only real slopes pay for side projections.
    float3 b = pow(abs(g.n), 4.0);
    b = max(b / dot(b, 1.0) - 0.03, 0.0);
    g.blend = b / max(dot(b, 1.0), 1e-5);
    // Mirror u on far faces so no face shows the texture mirrored.
    g.flip = float3(g.n.x < 0 ? -1 : 1, g.n.y < 0 ? -1 : 1, g.n.z < 0 ? 1 : -1);
    return g;
}
// X projects (z, y); Y projects (x, z), the original paint mapping with
// tangent +x along world X and +y along world Z; Z projects (x, y).
#define OPENSHIM_PAINT_UV_X(v, g) float2((v).z * (g).flip.x, (v).y)
#define OPENSHIM_PAINT_UV_Y(v, g) float2((v).x * (g).flip.y, (v).z)
#define OPENSHIM_PAINT_UV_Z(v, g) float2((v).x * (g).flip.z, (v).y)
#define OPENSHIM_PAINT_TAP(tex, sam, g, axis, s, slice) OPENSHIM_PAINT_SAMPLE(tex, sam, \
    float3(axis((g).pos, g) * (s), slice), axis((g).dpdx, g) * (s), axis((g).dpdy, g) * (s))
struct OpenShimPaintTaps { float4 x, y, z; };
OpenShimPaintTaps OpenShimPaintSampleTaps(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g, float repeat, float slice)
{
    OpenShimPaintTaps t = (OpenShimPaintTaps)0;
    float s = 1.0 / repeat;
    [branch] if (g.blend.x > 0) t.x = OPENSHIM_PAINT_TAP(tex, sam, g, OPENSHIM_PAINT_UV_X, s, slice);
    [branch] if (g.blend.y > 0) t.y = OPENSHIM_PAINT_TAP(tex, sam, g, OPENSHIM_PAINT_UV_Y, s, slice);
    [branch] if (g.blend.z > 0) t.z = OPENSHIM_PAINT_TAP(tex, sam, g, OPENSHIM_PAINT_UV_Z, s, slice);
    return t;
}
float4 OpenShimPaintTap(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g, float repeat, float slice)
{
    OpenShimPaintTaps t = OpenShimPaintSampleTaps(tex, sam, g, repeat, slice);
    return t.x * g.blend.x + t.y * g.blend.y + t.z * g.blend.z;
}
float4 OpenShimPaintWeights(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g)
{
    uint width, height, slices;
    tex.GetDimensions(width, height, slices);
    float2 paintUV = (g.pos.xz - openShimPaintBounds.xy) / (openShimPaintBounds.zw - openShimPaintBounds.xy);
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
        OpenShimPaintTap(tex, sam, g, openShimPaintRepeats.x, 5).a,
        OpenShimPaintTap(tex, sam, g, openShimPaintRepeats.y, 6).a,
        OpenShimPaintTap(tex, sam, g, openShimPaintRepeats.z, 7).a,
        OpenShimPaintTap(tex, sam, g, openShimPaintRepeats.w, 8).a);
    float4 lifted = weights + heights * openShimPaintHeightBlend;
    float crest = max(max(lifted.x, lifted.y), max(lifted.z, lifted.w));
    float4 kept = max(lifted - (crest - 0.2), 0) * step(0.002, weights);
    float keptTotal = dot(kept, float4(1,1,1,1));
    weights = keptTotal > 0.00001 ? kept / keptTotal : weights;
#endif
    return weights;
}
float4 OpenShimPaintLayers(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g, float4 weights, float base)
{
    return OpenShimPaintTap(tex, sam, g, openShimPaintRepeats.x, base + 0) * weights.x +
        OpenShimPaintTap(tex, sam, g, openShimPaintRepeats.y, base + 1) * weights.y +
        OpenShimPaintTap(tex, sam, g, openShimPaintRepeats.z, base + 2) * weights.z +
        OpenShimPaintTap(tex, sam, g, openShimPaintRepeats.w, base + 3) * weights.w;
}
float4 OpenShimSampleTerrainPaint(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g)
{
    float4 weights = OpenShimPaintWeights(tex, sam, g);
    // The fourth control channel is a weight, never terrain transparency, and
    // diffuse alpha (specular in the material form) is not the detail weight.
    return float4(OpenShimPaintLayers(tex, sam, g, weights, 0).rgb, 1);
}
#if OPENSHIM_PAINT_MATERIAL
// Any orthonormal frame around the geometry normal works: the paint normal is
// expressed in it and the TBN rebuilds it, so the frame only steers the
// shader's sharpening and detail, which stay centred on the geometry normal.
// On flat ground it is exactly the original +X/+Z paint frame.
float3x3 OpenShimPaintWorldFrame(float3 n)
{
    float3 t = normalize(abs(n.x) < 0.99 ? float3(1, 0, 0) - n * n.x : float3(0, 0, 1) - n * n.z);
    return float3x3(t, cross(t, n), n);
}
float3x3 OpenShimPaintTbn(float3 viewNormal, float4x4 invView)
{
    float3x3 world = OpenShimPaintWorldFrame(normalize(mul(invView, float4(viewNormal, 0.0)).xyz));
    float3x3 toView = (float3x3)invView;
    return float3x3(mul(world[0], toView), mul(world[1], toView), mul(world[2], toView));
}
// Whiteout blend per projection (Golus), u unmirrored like the UVs.
float3 OpenShimPaintWorldNormal(OpenShimPaintTaps t, OpenShimPaintGeo g)
{
    float3 n = g.n;
    float3 tx = t.x.rgb * 2 - 1, ty = t.y.rgb * 2 - 1, tz = t.z.rgb * 2 - 1;
    tx.x *= g.flip.x; ty.x *= g.flip.y; tz.x *= g.flip.z;
    tx = float3(tx.xy + n.zy, abs(tx.z) * n.x);
    ty = float3(ty.xy + n.xz, abs(ty.z) * n.y);
    tz = float3(tz.xy + n.xy, abs(tz.z) * n.z);
    return tx.zyx * g.blend.x + ty.xzy * g.blend.y + tz * g.blend.z;
}
// Packed tangent normal (mode 0 RGB) in the paint frame; the lighting path
// renormalizes. Flat ground: +x along world X, +y along world Z.
float4 OpenShimSampleTerrainPaintNormal(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g)
{
    float4 weights = OpenShimPaintWeights(tex, sam, g);
#if OPENSHIM_PAINT_TRIPLANAR
    float3 world =
        OpenShimPaintWorldNormal(OpenShimPaintSampleTaps(tex, sam, g, openShimPaintRepeats.x, 5), g) * weights.x +
        OpenShimPaintWorldNormal(OpenShimPaintSampleTaps(tex, sam, g, openShimPaintRepeats.y, 6), g) * weights.y +
        OpenShimPaintWorldNormal(OpenShimPaintSampleTaps(tex, sam, g, openShimPaintRepeats.z, 7), g) * weights.z +
        OpenShimPaintWorldNormal(OpenShimPaintSampleTaps(tex, sam, g, openShimPaintRepeats.w, 8), g) * weights.w;
    return float4(mul(OpenShimPaintWorldFrame(g.n), normalize(world)) * 0.5 + 0.5, 1);
#else
    return float4(OpenShimPaintLayers(tex, sam, g, weights, 5).rgb, 1);
#endif
}
float3 OpenShimSampleTerrainPaintSpecular(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g)
{
    float4 weights = OpenShimPaintWeights(tex, sam, g);
    return OpenShimPaintLayers(tex, sam, g, weights, 0).aaa;
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
            source.replace(offset, token.size(), "OpenShimSampleTerrainPaint(diffuseMap, diffuseSam, OPENSHIM_PAINT_GEO)");
            if (config.Material())
            {
                // The paint array rides in t0, so normal and specular come from
                // it too; the stock atlas maps would follow the wrong UVs.
                // A pass that never samples a map (the glow pass has colour
                // only) keeps that part unchanged; a pass that samples it in
                // an unknown form declines.
                struct Swap { const char* from; const char* to; const char* use; };
                const Swap swaps[] = {
                    {"normalMap.Sample(normalSam, vTexCoord)", "OpenShimSampleTerrainPaintNormal(diffuseMap, diffuseSam, OPENSHIM_PAINT_GEO)", "normalMap.Sample"},
                    {"specularMap.Sample(specularSam, vTexCoord).xyz", "OpenShimSampleTerrainPaintSpecular(diffuseMap, diffuseSam, OPENSHIM_PAINT_GEO)", "specularMap.Sample"},
                    {"cotangent_frame(geometryNormal, vViewPosition.xyz, vTexCoord)",
                     "OPENSHIM_PAINT_TBN(geometryNormal)", "cotangent_frame(geometryNormal"},
                    // Vertex tangents follow the stock atlas UVs; no terrain
                    // program defines them today, but never mix the frames.
                    {"float3x3 tbn = float3x3(baseTangent, binormal, baseNormal);",
                     "float3x3 tbn = OPENSHIM_PAINT_TBN(geometryNormal);", nullptr},
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
            // Triplanar needs a view normal and the inverse view; the HLSL
            // also checks the #if conditions that declare them.
            const bool triplanar = source.find("in float3 vViewNormal") != std::string::npos &&
                source.find("uniform float4x4 inverseViewMatrix") != std::string::npos;
            constants << "#define OPENSHIM_PAINT_TRIPLANAR_SOURCE " << (triplanar ? 1 : 0) << "\n";
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
            // localUV carries audited native world XZ in paint mode, and the
            // unused atlas rect's x carries native world Y on to the pixel
            // shader in the unused slice index, for triplanar. Auxiliary maps
            // must retain the original packed UV expression verbatim.
            source.replace(begin, end - begin + 1,
                "    openShimHdUV = openShimLocalUV;\n    openShimTileSlice = openShimAtlasRect.x;\n    vTexCoord = openShimStockUV;");
        }
        return true;
    }
}
