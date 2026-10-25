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
        // Per-layer arrays hold Layers() values; the rest stay 0.
        std::array<float, 8> repeatMeters = {};
        // 5 slices: diffuse 0-3, control 4. 9 slices adds the full material:
        // diffuse alpha is specular, slices 5-8 hold tangent normal RGB with
        // height in alpha, used for height-aware blending and displacement.
        // 18 slices are two such banks for eight layers: layers 4-7 take
        // diffuse 9-12, control 13 and normal 14-17.
        unsigned sliceCount = 5;
        float heightBlend = 0.5f;
        std::array<float, 8> heightMeters = {};
        // Per layer, 0 or 1: break up the repeat with noise-chosen tile
        // offsets (diffuse, normal, height and displacement alike).
        std::array<float, 8> detile = {};
        // Two scales by distance: scale, start metres, end metres, amount.
        // Past start every layer cross-fades toward a copy scale times
        // larger, so the repeat stops reading at range. Scale 0 is off.
        std::array<float, 4> farScale = {};
        // Large-scale variation: noise metres, brightness and saturation
        // swing (fractions), hue turn in radians inside patches. Metres 0 is off.
        std::array<float, 4> macro = {};
        // Procedural world-space craters: cell metres, depth to diameter,
        // coverage, octaves (each triples the cell). Cell 0 is off.
        // craterLayers (0..1 per layer) says how strongly each layer carries them.
        std::array<float, 4> craters = {};
        std::array<float, 8> craterLayers = {};
        // Procedural erosion detail height: longest wavelength metres, height
        // metres, octaves (each halves the wavelength) and slope damping
        // (0 plain fbm; higher keeps smooth valleys between sharper ridges).
        // Wavelength 0 is off. detailLayers (0..1) weight it per layer.
        std::array<float, 4> detail = {};
        std::array<float, 8> detailLayers = {};
        // The field is normalised to its height, so this bounds it either way.
        float DetailMeters() const { return detail[0] > 0 ? detail[1] : 0.0f; }
        // Close-up parallax occlusion: depth scale (0..2, of each layer's
        // heightMeters), fade-out view distance in metres and ray steps.
        // It carries only the relief finer than the displaced vertices.
        // Scale 0 is off.
        std::array<float, 4> parallax = {};
        bool Material() const { return sliceCount != 5; }
        unsigned Layers() const { return sliceCount == 18 ? 8 : 4; }
        // Deepest a crater stack can reach, for the displacement clamp.
        float CraterMeters() const
        {
            float total = 0, cell = craters[0];
            for (int o = 0; o < craters[3]; ++o, cell *= 3) total += 0.75f * craters[1] * (1 - 0.25f * o) * 2 * 0.42f * cell;
            return craters[0] > 0 ? total : 0.0f;
        }
        // Optional multi-map table. Several campaign maps share one atlas
        // material, so a single pack lists one entry per terrain shape; the
        // entry matching the live fingerprint and bounds supplies the control
        // image (array slice 4, and slice 13 from control2 for eight layers).
        // Empty means the single-map form above.
        struct MapEntry
        {
            std::string fingerprint;
            std::array<float, 4> bounds = {};
            std::string control;
            std::string control2 = {};
        };
        std::vector<MapEntry> maps = {};
        void Validate() const
        {
            if (fingerprint.size() != 16 || fingerprint.find_first_not_of("0123456789abcdef") != std::string::npos)
                throw std::runtime_error("paint terrainFingerprint must be 16 lowercase hex digits");
            for (float v : bounds) if (!std::isfinite(v) || std::abs(v) > 1000000)
                throw std::runtime_error("paint bounds must be finite native world metres");
            if (bounds[2] <= bounds[0] || bounds[3] <= bounds[1])
                throw std::runtime_error("paint bounds must have positive extents");
            if (sliceCount != 5 && sliceCount != 9 && sliceCount != 18)
                throw std::runtime_error("paint packs have 5, 9 or 18 array slices");
            for (unsigned i = 0; i < 8; ++i)
            {
                const bool used = i < Layers();
                if (used ? !std::isfinite(repeatMeters[i]) || repeatMeters[i] < 1 || repeatMeters[i] > 4096 : repeatMeters[i] != 0)
                    throw std::runtime_error("paint material repeats must be 1..4096 metres");
                if (!used && (heightMeters[i] != 0 || detile[i] != 0 || craterLayers[i] != 0 || detailLayers[i] != 0))
                    throw std::runtime_error("paint per-layer values must match the layer count");
            }
            if (!std::isfinite(heightBlend) || heightBlend < 0 || heightBlend > 4)
                throw std::runtime_error("paint heightBlend must be 0..4");
            for (float v : heightMeters) if (!std::isfinite(v) || v < 0 || v > 32)
                throw std::runtime_error("paint heightMeters must be 0..32 metres");
            if (!Material() && heightMeters != std::array<float, 8>{})
                throw std::runtime_error("paint heightMeters needs the 9-slice material form");
            for (float v : detile) if (v != 0 && v != 1)
                throw std::runtime_error("paint detile must be 0 or 1 per layer");
            for (float v : farScale) if (!std::isfinite(v))
                throw std::runtime_error("paint far must be finite");
            if (farScale[0] != 0 && (farScale[0] < 2 || farScale[0] > 16 || farScale[1] < 0 || farScale[2] <= farScale[1] ||
                farScale[2] > 100000 || farScale[3] < 0 || farScale[3] > 1))
                throw std::runtime_error("paint far needs scale 2..16, 0 <= start < end metres and amount 0..1");
            for (float v : macro) if (!std::isfinite(v))
                throw std::runtime_error("paint macro must be finite");
            if (macro[0] != 0 && (macro[0] < 10 || macro[0] > 10000 || macro[1] < 0 || macro[1] > 0.5f ||
                macro[2] < 0 || macro[2] > 1 || macro[3] < -1 || macro[3] > 1))
                throw std::runtime_error("paint macro needs 10..10000 metres, brightness 0..0.5, saturation 0..1 and hue -1..1");
            for (float v : craters) if (!std::isfinite(v))
                throw std::runtime_error("paint craters must be finite");
            for (float v : craterLayers) if (!(v >= 0 && v <= 1))
                throw std::runtime_error("paint craterLayers must be 0..1 per layer");
            const bool anyCraterLayer = craterLayers != std::array<float, 8>{};
            if (craters[0] != 0)
            {
                if (craters[0] < 1 || craters[0] > 1000 || craters[1] <= 0 || craters[1] > 0.5f ||
                    craters[2] <= 0 || craters[2] > 1 || (craters[3] != 1 && craters[3] != 2 && craters[3] != 3))
                    throw std::runtime_error("paint craters need 1..1000 metre cells, depth 0..0.5, coverage 0..1 and 1..3 octaves");
                if (!Material())
                    throw std::runtime_error("paint craters need the 9-slice material form");
                if (!anyCraterLayer)
                    throw std::runtime_error("paint craters need at least one crater layer");
            }
            else if (craters != std::array<float, 4>{} || anyCraterLayer)
                throw std::runtime_error("paint craters are off; leave every crater value 0");
            for (float v : detail) if (!std::isfinite(v))
                throw std::runtime_error("paint detail must be finite");
            for (float v : detailLayers) if (!(v >= 0 && v <= 1))
                throw std::runtime_error("paint detailLayers must be 0..1 per layer");
            if (detail[0] != 0)
            {
                if (detail[0] < 2 || detail[0] > 1000 || detail[1] <= 0 || detail[1] > 4 ||
                    detail[2] < 1 || detail[2] > 5 || detail[2] != std::floor(detail[2]) || detail[3] < 0 || detail[3] > 4)
                    throw std::runtime_error("paint detail needs 2..1000 metre waves, height 0..4 metres, 1..5 octaves and damping 0..4");
                if (!Material())
                    throw std::runtime_error("paint detail needs the material form");
                if (detailLayers == std::array<float, 8>{})
                    throw std::runtime_error("paint detail needs at least one detail layer");
            }
            else if (detail != std::array<float, 4>{} || detailLayers != std::array<float, 8>{})
                throw std::runtime_error("paint detail is off; leave every detail value 0");
            if (parallax[0] != 0)
            {
                if (!(parallax[0] > 0 && parallax[0] <= 2 && parallax[1] >= 2 && parallax[1] <= 300 &&
                    parallax[2] >= 4 && parallax[2] <= 32 && parallax[2] == std::floor(parallax[2]) && parallax[3] == 0))
                    throw std::runtime_error("paint parallax needs depth scale 0..2, fade 2..300 metres and 4..32 steps");
                if (!Material())
                    throw std::runtime_error("paint parallax needs the material form");
            }
            else if (parallax != std::array<float, 4>{})
                throw std::runtime_error("paint parallax is off; leave every parallax value 0");
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
                if (map.control2.empty() != (Layers() == 4))
                    throw std::runtime_error("paint map needs control2 exactly when it has eight layers");
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

    // True while the live terrain is a partial zone set inside some table
    // entry. The engine builds zones as the camera reaches them, so a partial
    // set can still grow into a match; a complete terrain that matches nothing
    // cannot. zoneMeters is the live zone edge, so an entry's full zone count
    // follows from its bounds.
    inline bool MapMayGrow(const Config& config, const std::array<float, 4>& bounds,
        std::size_t zoneCount, float zoneMeters)
    {
        if (!(zoneMeters > 0)) return false;
        for (const auto& map : config.maps)
        {
            if (bounds[0] < map.bounds[0] || bounds[1] < map.bounds[1] ||
                bounds[2] > map.bounds[2] || bounds[3] > map.bounds[3]) continue;
            const double full = std::round((map.bounds[2] - map.bounds[0]) / zoneMeters) *
                std::round((map.bounds[3] - map.bounds[1]) / zoneMeters);
            if (double(zoneCount) < full) return true;
        }
        return false;
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
    // Shared by the pixel and tessellation shaders so displacement follows
    // the shaded tile. Quilez "texture variation": value noise over tile UV
    // picks one of nine whole-tile offsets and cross-fades to the next; only
    // the fade bands pay for a second tap. Gradients stay unoffset.
    inline const char* DetileHlsl()
    {
        return R"HLSL(
float OpenShimDetileHash(float2 p)
{
    float3 q = frac(float3(p.xyx) * 0.1031);
    q += dot(q, q.yzx + 33.33);
    return frac((q.x + q.y) * q.z);
}
float OpenShimDetileNoise(float2 p)
{
    float2 i = floor(p), f = p - i;
    f = f * f * (3.0 - 2.0 * f);
    return lerp(lerp(OpenShimDetileHash(i), OpenShimDetileHash(i + float2(1, 0)), f.x),
        lerp(OpenShimDetileHash(i + float2(0, 1)), OpenShimDetileHash(i + float2(1, 1)), f.x), f.y);
}
struct OpenShimDetile { float2 a; float2 b; float t; };
OpenShimDetile OpenShimDetileAt(float2 uv)
{
    // Regions about three tiles across.
    float l = OpenShimDetileNoise(uv * 0.35) * 8.0;
    float i = floor(l);
    OpenShimDetile d;
    d.a = sin(float2(3, 7) * i);
    d.b = sin(float2(3, 7) * (i + 1.0));
    // Only the band pays for both taps; 0.35..0.65 still hides the seam.
    d.t = smoothstep(0.35, 0.65, l - i);
    return d;
}
// dt/duv of OpenShimDetileAt's band, for the domain shader's analytic slope.
float2 OpenShimDetileSlope(float2 uv)
{
    float2 i = floor(uv * 0.35), f = uv * 0.35 - i;
    float2 u = f * f * (3.0 - 2.0 * f), du = 6.0 * f * (1.0 - f);
    float a = OpenShimDetileHash(i), b = OpenShimDetileHash(i + float2(1, 0));
    float c = OpenShimDetileHash(i + float2(0, 1)), d = OpenShimDetileHash(i + float2(1, 1));
    float l = lerp(lerp(a, b, u.x), lerp(c, d, u.x), u.y) * 8.0;
    float s = saturate((l - floor(l) - 0.35) / 0.3);
    return (6.0 * s * (1.0 - s) / 0.3) * 8.0 * 0.35 * du * (float2(b - a, c - a) + (a - b - c + d) * u.yx);
}
)HLSL";
    }
    // Shared like DetileHlsl, after it (it reuses the hash), so the shaded
    // bowls and the displaced ones agree. Jittered cells, one crater at most
    // per cell; foot is the sample spacing in metres, and craters too small
    // to resolve fade out instead of aliasing. slope is dh/dx, dh/dz.
    inline const char* CraterHlsl()
    {
        return R"HLSL(
struct OpenShimCrater { float h; float2 slope; };
OpenShimCrater OpenShimCraterField(float2 p, float4 params, float foot)
{
    OpenShimCrater c = (OpenShimCrater)0;
    float cell = params.x;
    [unroll] for (int o = 0; o < 3; ++o)
    {
        if (o >= params.w) break;
        float fade = 1.0 - smoothstep(0.08, 0.2, foot / cell);
        // Bigger craters are shallower for their size.
        float ratio = params.y * (1.0 - 0.25 * o) * fade;
        float2 q = p / cell + 7.31 * o;
        float2 id = floor(q);
        [branch] if (fade > 0)
        [unroll] for (int j = -1; j <= 1; ++j)
        [unroll] for (int i = -1; i <= 1; ++i)
        {
            float2 k = id + float2(i, j);
            float2 key = k + 57.0 * o;
            if (OpenShimDetileHash(key + 0.5) >= params.z) continue;
            float size = OpenShimDetileHash(key + 19.19);
            float2 v = q - (k + 0.15 + 0.7 * float2(OpenShimDetileHash(key + 47.7), OpenShimDetileHash(key + 83.3)));
            float radius = lerp(0.12, 0.42, size * size);
            float dist = length(v), d = dist / radius;
            if (d >= 1.9) continue;
            // Bowl that eases into the rim (no crease at the lip), flat
            // floor, low wide Gaussian rim; weathered rather than fresh.
            float lip = 1.0 - d * d;
            float bowl = d < 1.0 ? -min(lip * lip, 0.75) : 0.0;
            float dBowl = d < 1.0 && lip * lip < 0.75 ? 4.0 * d * lip : 0.0;
            float rim = 0.2 * exp(-8.0 * (d - 1.0) * (d - 1.0));
            float dRim = -16.0 * (d - 1.0) * rim;
            c.h += (bowl + rim) * ratio * 2.0 * radius * cell;
            c.slope += (dBowl + dRim) * ratio * 2.0 * v / max(dist, 1e-5);
        }
        cell *= 3.0;
    }
    return c;
}
// Value noise in -1..1 with its analytic gradient (Quilez).
float3 OpenShimNoiseGrad(float2 p)
{
    float2 i = floor(p), f = p - i;
    float2 u = f * f * (3.0 - 2.0 * f), du = 6.0 * f * (1.0 - f);
    float a = OpenShimDetileHash(i), b = OpenShimDetileHash(i + float2(1, 0));
    float c = OpenShimDetileHash(i + float2(0, 1)), d = OpenShimDetileHash(i + float2(1, 1));
    float k = a - b - c + d;
    return 2.0 * float3(a + (b - a) * u.x + (c - a) * u.y + k * u.x * u.y - 0.5,
        du * (float2(b - a, c - a) + k * u.yx));
}
// Erosion detail: fbm whose octaves are damped where the octaves above are
// steep, so ridges stay crisp and valleys smooth. Normalised to params.y
// metres; octaves too fine for foot fade out. The slope leaves out the
// damping term's own derivative, close enough for a normal. Shares OpenShimCrater.
OpenShimCrater OpenShimDetailField(float2 p, float4 params, float foot)
{
    OpenShimCrater r = (OpenShimCrater)0;
    float wave = params.x, amp = 1.0, norm = 0.0;
    float2 steep = 0;
    [unroll] for (int o = 0; o < 5; ++o)
    {
        if (o >= params.z) break;
        float3 n = OpenShimNoiseGrad(p / wave + 31.7 * o);
        steep += n.yz * amp;
        float k = amp * (1.0 - smoothstep(0.25, 0.5, foot / wave)) / (1.0 + params.w * dot(steep, steep));
        r.h += n.x * k;
        r.slope += n.yz / wave * k;
        norm += amp; amp *= 0.5; wave *= 0.5;
    }
    r.h *= params.y / norm;
    r.slope *= params.y / norm;
    return r;
}
)HLSL";
    }
    // Per-layer constants and the height-aware layer selection, shared by
    // the pixel and domain shaders so the shaded and displaced layer agree.
    inline std::string LayerHlsl(const Config& config)
    {
        std::ostringstream out; out.imbue(std::locale::classic()); out << std::setprecision(9) << std::scientific;
        const unsigned layers = config.Layers();
        out << "#define OPENSHIM_PAINT_LAYERS " << layers << "\n";
        const auto list = [&](const char* name, const std::array<float, 8>& v) {
            out << "static const float " << name << "[" << layers << "] = {";
            for (unsigned i = 0; i < layers; ++i) out << (i ? "," : "") << v[i];
            out << "};\n"; };
        list("openShimPaintRepeats", config.repeatMeters);
        list("openShimPaintHeightMeters", config.heightMeters);
        list("openShimPaintDetile", config.detile);
        list("openShimPaintCraterLayers", config.craterLayers);
        list("openShimPaintDetailLayers", config.detailLayers);
        out << "static const float openShimPaintHeightBlend = " << config.heightBlend << ";\n";
        return out.str() + R"HLSL(
struct OpenShimPaintMix { float w[OPENSHIM_PAINT_LAYERS]; };
// Layer i lives in bank i / 4; part 0 is diffuse, 4 control, 5 normal+height.
float OpenShimPaintSlice(int layer, int part) { return (layer / 4) * 9 + part + (part == 4 ? 0 : layer % 4); }
// Raw control texels, one float4 per bank, normalised; an all-zero map
// falls back to layer zero.
OpenShimPaintMix OpenShimPaintNormalize(float4 banks[OPENSHIM_PAINT_LAYERS / 4])
{
    OpenShimPaintMix m;
    float total = 0;
    [unroll] for (int b = 0; b < OPENSHIM_PAINT_LAYERS / 4; ++b)
    {
        float4 c = max(banks[b], 0);
        m.w[b * 4 + 0] = c.x; m.w[b * 4 + 1] = c.y; m.w[b * 4 + 2] = c.z; m.w[b * 4 + 3] = c.w;
        total += dot(c, 1);
    }
    [unroll] for (int i = 0; i < OPENSHIM_PAINT_LAYERS; ++i)
        m.w[i] = total > 0.00001 ? m.w[i] / total : (i == 0 ? 1.0 : 0.0);
    return m;
}
// Below this weight a layer is absent: callers skip its height tap.
bool OpenShimPaintPresent(OpenShimPaintMix m, int i) { return m.w[i] >= 0.002; }
// Height-aware blend: the taller present layer wins inside a transition, so
// rock pokes through sand at its crests instead of cross-fading.
OpenShimPaintMix OpenShimPaintSelect(OpenShimPaintMix m, float heights[OPENSHIM_PAINT_LAYERS])
{
    float lifted[OPENSHIM_PAINT_LAYERS];
    float crest = 0;
    [unroll] for (int i = 0; i < OPENSHIM_PAINT_LAYERS; ++i)
    {
        lifted[i] = OpenShimPaintPresent(m, i) ? m.w[i] + heights[i] * openShimPaintHeightBlend : 0.0;
        crest = max(crest, lifted[i]);
    }
    OpenShimPaintMix kept;
    float keptTotal = 0;
    [unroll] for (int j = 0; j < OPENSHIM_PAINT_LAYERS; ++j)
    {
        kept.w[j] = OpenShimPaintPresent(m, j) ? max(lifted[j] - (crest - 0.2), 0) : 0.0;
        keptTotal += kept.w[j];
    }
    [unroll] for (int k = 0; k < OPENSHIM_PAINT_LAYERS; ++k)
        kept.w[k] = keptTotal > 0.00001 ? kept.w[k] / keptTotal : m.w[k];
    return kept;
}
float OpenShimPaintDot(OpenShimPaintMix m, float v[OPENSHIM_PAINT_LAYERS])
{
    float sum = 0;
    [unroll] for (int i = 0; i < OPENSHIM_PAINT_LAYERS; ++i) sum += m.w[i] * v[i];
    return sum;
}
)HLSL";
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
#if OPENSHIM_PAINT_MATERIAL && OPENSHIM_PAINT_PARALLAX
#define OPENSHIM_PAINT_GEO OpenShimPaintParallax(diffuseMap, diffuseSam, \
    OpenShimPaintGeometryAt(openShimHdUV, openShimTileSlice, mul(inverseViewMatrix, float4(vViewNormal, 0.0)).xyz, OPENSHIM_PAINT_VIEW_DEPTH), \
    mul(inverseViewMatrix, float4(vViewPosition.xyz, 0.0)).xyz, OPENSHIM_PAINT_VIEW_DEPTH)
#else
#define OPENSHIM_PAINT_GEO OpenShimPaintGeometryAt(openShimHdUV, openShimTileSlice, mul(inverseViewMatrix, float4(vViewNormal, 0.0)).xyz, OPENSHIM_PAINT_VIEW_DEPTH)
#endif
#define OPENSHIM_PAINT_TBN(n) OpenShimPaintTbn(n, inverseViewMatrix)
#else
#define OPENSHIM_PAINT_TRIPLANAR 0
#define OPENSHIM_PAINT_GEO OpenShimPaintGeometryAt(openShimHdUV, 0.0, float3(0, 1, 0), OPENSHIM_PAINT_VIEW_DEPTH)
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
// farMix is the share of the larger copy; foot is metres per pixel.
struct OpenShimPaintGeo { float3 pos; float3 n; float3 blend; float3 flip; float3 dpdx; float3 dpdy; float farMix; float foot; };
OpenShimPaintGeo OpenShimPaintGeometryAt(float2 worldXZ, float worldY, float3 worldNormal, float viewDepth)
{
    OpenShimPaintGeo g;
    g.pos = float3(worldXZ.x, worldY, worldXZ.y);
    // Every projection is linear in world position, so its gradients, taken
    // here outside any branch, give each tap its own.
    g.dpdx = OPENSHIM_PAINT_DDX(g.pos);
    g.dpdy = OPENSHIM_PAINT_DDY(g.pos);
    g.foot = max(length(g.dpdx), length(g.dpdy));
    g.farMix = openShimPaintFar.x > 0 ?
        saturate((viewDepth - openShimPaintFar.y) / (openShimPaintFar.z - openShimPaintFar.y)) * openShimPaintFar.w : 0.0;
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
OpenShimPaintGeo OpenShimPaintGeometry(float2 worldXZ, float worldY, float3 worldNormal)
{
    return OpenShimPaintGeometryAt(worldXZ, worldY, worldNormal, 0.0);
}
// X projects (z, y); Y projects (x, z), the original paint mapping with
// tangent +x along world X and +y along world Z; Z projects (x, y).
#define OPENSHIM_PAINT_UV_X(v, g) float2((v).z * (g).flip.x, (v).y)
#define OPENSHIM_PAINT_UV_Y(v, g) float2((v).x * (g).flip.y, (v).z)
#define OPENSHIM_PAINT_UV_Z(v, g) float2((v).x * (g).flip.z, (v).y)
// detile is a compile-time constant per layer, so plain layers keep one tap.
float4 OpenShimPaintProjected(Texture2DArray tex, SamplerState sam, float2 uv, float2 gx, float2 gy, float slice, bool detile)
{
    if (detile)
    {
        OpenShimDetile d = OpenShimDetileAt(uv);
        float4 a = 0, b = 0;
        [branch] if (d.t < 1) a = OPENSHIM_PAINT_SAMPLE(tex, sam, float3(uv + d.a, slice), gx, gy);
        [branch] if (d.t > 0) b = OPENSHIM_PAINT_SAMPLE(tex, sam, float3(uv + d.b, slice), gx, gy);
        return lerp(a, b, d.t);
    }
    return OPENSHIM_PAINT_SAMPLE(tex, sam, float3(uv, slice), gx, gy);
}
#define OPENSHIM_PAINT_TAP(tex, sam, g, axis, s, slice, detile) OpenShimPaintProjected(tex, sam, \
    axis((g).pos, g) * (s), axis((g).dpdx, g) * (s), axis((g).dpdy, g) * (s), slice, detile)
struct OpenShimPaintTaps { float4 x, y, z; };
OpenShimPaintTaps OpenShimPaintSampleScale(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g, float s, float slice, bool detile)
{
    OpenShimPaintTaps t = (OpenShimPaintTaps)0;
    [branch] if (g.blend.x > 0) t.x = OPENSHIM_PAINT_TAP(tex, sam, g, OPENSHIM_PAINT_UV_X, s, slice, detile);
    [branch] if (g.blend.y > 0) t.y = OPENSHIM_PAINT_TAP(tex, sam, g, OPENSHIM_PAINT_UV_Y, s, slice, detile);
    [branch] if (g.blend.z > 0) t.z = OPENSHIM_PAINT_TAP(tex, sam, g, OPENSHIM_PAINT_UV_Z, s, slice, detile);
    return t;
}
// Near and far copies; only the cross-fade pays for both.
OpenShimPaintTaps OpenShimPaintSampleTaps(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g, float repeat, float slice, bool detile)
{
    float s = 1.0 / repeat;
    OpenShimPaintTaps nearTaps = (OpenShimPaintTaps)0, farTaps = (OpenShimPaintTaps)0;
    [branch] if (g.farMix < 1) nearTaps = OpenShimPaintSampleScale(tex, sam, g, s, slice, detile);
    [branch] if (g.farMix > 0) farTaps = OpenShimPaintSampleScale(tex, sam, g, s / openShimPaintFar.x, slice, detile);
    nearTaps.x = lerp(nearTaps.x, farTaps.x, g.farMix);
    nearTaps.y = lerp(nearTaps.y, farTaps.y, g.farMix);
    nearTaps.z = lerp(nearTaps.z, farTaps.z, g.farMix);
    return nearTaps;
}
float4 OpenShimPaintTap(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g, float repeat, float slice, bool detile)
{
    OpenShimPaintTaps t = OpenShimPaintSampleTaps(tex, sam, g, repeat, slice, detile);
    return t.x * g.blend.x + t.y * g.blend.y + t.z * g.blend.z;
}
OpenShimPaintMix OpenShimPaintControl(Texture2DArray tex, SamplerState sam, float2 worldXZ)
{
    uint width, height, slices;
    tex.GetDimensions(width, height, slices);
    float2 paintUV = (worldXZ - openShimPaintBounds.xy) / (openShimPaintBounds.zw - openShimPaintBounds.xy);
    float2 inset = 0.5 / float2(width, height);
    // Level zero plus a half-texel clamp prevents the shared wrapping sampler
    // from blending the opposite edge of the map into its border.
    float4 banks[OPENSHIM_PAINT_LAYERS / 4];
    [unroll] for (int b = 0; b < OPENSHIM_PAINT_LAYERS / 4; ++b)
        banks[b] = tex.SampleLevel(sam, float3(clamp(paintUV, inset, 1.0-inset), OpenShimPaintSlice(b * 4, 4)), 0);
    return OpenShimPaintNormalize(banks);
}
#if OPENSHIM_PAINT_MATERIAL
// The height taps read the normal+height slice at the near scale, which is
// exactly the normal's near tap, so the normal reuses each present layer's
// top projection (the only one flat ground pays for). Written with the
// weights cache and keyed on it.
static bool openShimPaintNearValid[OPENSHIM_PAINT_LAYERS];
static float4 openShimPaintNearTop[OPENSHIM_PAINT_LAYERS];
#endif
OpenShimPaintMix OpenShimPaintWeightsAt(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g)
{
    OpenShimPaintMix m = OpenShimPaintControl(tex, sam, g.pos.xz);
#if OPENSHIM_PAINT_MATERIAL
    // Heights stay at the near scale, as in the domain shader, so
    // displacement agrees.
    float heights[OPENSHIM_PAINT_LAYERS];
    [unroll] for (int i = 0; i < OPENSHIM_PAINT_LAYERS; ++i)
    {
        heights[i] = 0;
        openShimPaintNearValid[i] = OpenShimPaintPresent(m, i);
        openShimPaintNearTop[i] = 0;
        [branch] if (openShimPaintNearValid[i])
        {
            OpenShimPaintTaps t = OpenShimPaintSampleScale(tex, sam, g, 1.0 / openShimPaintRepeats[i],
                OpenShimPaintSlice(i, 5), openShimPaintDetile[i] > 0);
            openShimPaintNearTop[i] = t.y;
            heights[i] = (t.x * g.blend.x + t.y * g.blend.y + t.z * g.blend.z).a;
        }
    }
    m = OpenShimPaintSelect(m, heights);
#endif
    return m;
}
// The diffuse, normal and specular reads each start from the same geometry,
// so the weights (control tap plus a height tap per present layer) and the
// diffuse sum, whose alpha is specular, are worked out once per pixel. Keyed
// on the geometry, so a caller passing another one still gets its own.
bool OpenShimPaintSameGeo(OpenShimPaintGeo a, OpenShimPaintGeo b)
{
    return all(a.pos == b.pos) && all(a.n == b.n) && all(a.dpdx == b.dpdx) && all(a.dpdy == b.dpdy) && a.farMix == b.farMix;
}
static bool openShimPaintWeightsReady = false;
static OpenShimPaintGeo openShimPaintWeightsGeo;
static OpenShimPaintMix openShimPaintWeightsCache;
OpenShimPaintMix OpenShimPaintWeights(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g)
{
    [branch] if (!(openShimPaintWeightsReady && OpenShimPaintSameGeo(g, openShimPaintWeightsGeo)))
    {
        openShimPaintWeightsCache = OpenShimPaintWeightsAt(tex, sam, g);
        openShimPaintWeightsGeo = g;
        openShimPaintWeightsReady = true;
    }
    return openShimPaintWeightsCache;
}
)HLSL" R"HLSL(
#if OPENSHIM_PAINT_MATERIAL && OPENSHIM_PAINT_PARALLAX
// Close-up parallax. The domain shader displaces each layer's height at the
// mip of its factor-4 vertex spacing (1.25 m), so the ray is marched through
// the fine height minus that coarse one: geometry carries the large shapes
// and parallax only the relief between vertices. Top projection only.
float OpenShimPaintFineHeight(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g, OpenShimPaintMix m, float2 xz)
{
    float sum = 0;
    [unroll] for (int i = 0; i < OPENSHIM_PAINT_LAYERS; ++i)
        [branch] if (OpenShimPaintPresent(m, i) && openShimPaintHeightMeters[i] > 0)
        {
            float s = 1.0 / openShimPaintRepeats[i];
            float2 uv = OPENSHIM_PAINT_UV_Y(float3(xz.x, 0, xz.y), g) * s, coarse = float2(1.25 * s, 0);
            bool detile = openShimPaintDetile[i] > 0;
            float fine = OpenShimPaintProjected(tex, sam, uv, OPENSHIM_PAINT_UV_Y(g.dpdx, g) * s,
                OPENSHIM_PAINT_UV_Y(g.dpdy, g) * s, OpenShimPaintSlice(i, 5), detile).a;
            float base = OpenShimPaintProjected(tex, sam, uv, coarse, coarse.yx, OpenShimPaintSlice(i, 5), detile).a;
            sum += m.w[i] * (fine - base) * openShimPaintHeightMeters[i];
        }
    return sum * openShimPaintParallax.x;
}
// view is camera to pixel in world space. Fades out with distance and slope.
OpenShimPaintGeo OpenShimPaintParallaxAt(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g, float3 view, float viewDepth)
{
    float fade = saturate(1.0 - viewDepth / openShimPaintParallax.y) * g.blend.y;
    float3 d = normalize(view);
    [branch] if (!(fade > 0.001 && d.y < -0.01)) return g;
    OpenShimPaintMix m = OpenShimPaintControl(tex, sam, g.pos.xz);
    float top = 0.5 * fade * openShimPaintParallax.x * OpenShimPaintDot(m, openShimPaintHeightMeters);
    // Ray XZ per metre of descent, held off grazing angles; at relief y
    // above the surface the ray is over pos.xz - run * y.
    float2 run = d.xz / max(-d.y, 0.3);
    float stepY = 2.0 * top / openShimPaintParallax.z;
    float y = top, prevY = top, h = OpenShimPaintFineHeight(tex, sam, g, m, g.pos.xz - run * top) * fade, prevH = top;
    [loop] for (int k = 0; k < int(openShimPaintParallax.z) && h < y; ++k)
    {
        prevY = y; prevH = h; y -= stepY;
        h = OpenShimPaintFineHeight(tex, sam, g, m, g.pos.xz - run * y) * fade;
    }
    // Secant between the last sample above the relief and the first below.
    float above = prevY - prevH, below = h - y;
    float hit = above + below > 1e-5 ? lerp(prevY, y, saturate(above / (above + below))) : y;
    g.pos.xz -= run * hit;
    return g;
}
// The diffuse, normal and specular reads share one march per pixel.
static bool openShimPaintParallaxReady = false;
static float2 openShimPaintParallaxXZ = 0;
OpenShimPaintGeo OpenShimPaintParallax(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g, float3 view, float viewDepth)
{
    if (!openShimPaintParallaxReady)
    {
        openShimPaintParallaxXZ = OpenShimPaintParallaxAt(tex, sam, g, view, viewDepth).pos.xz;
        openShimPaintParallaxReady = true;
    }
    g.pos.xz = openShimPaintParallaxXZ;
    return g;
}
#endif
// Layers the blend left out cost nothing.
float4 OpenShimPaintLayers(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g, OpenShimPaintMix m, int part)
{
    float4 sum = 0;
    [unroll] for (int i = 0; i < OPENSHIM_PAINT_LAYERS; ++i)
        [branch] if (m.w[i] > 0)
            sum += OpenShimPaintTap(tex, sam, g, openShimPaintRepeats[i], OpenShimPaintSlice(i, part), openShimPaintDetile[i] > 0) * m.w[i];
    return sum;
}
static bool openShimPaintDiffuseReady = false;
static OpenShimPaintGeo openShimPaintDiffuseGeo;
static float4 openShimPaintDiffuseCache;
float4 OpenShimPaintDiffuse(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g)
{
    [branch] if (!(openShimPaintDiffuseReady && OpenShimPaintSameGeo(g, openShimPaintDiffuseGeo)))
    {
        openShimPaintDiffuseCache = OpenShimPaintLayers(tex, sam, g, OpenShimPaintWeights(tex, sam, g), 0);
        openShimPaintDiffuseGeo = g;
        openShimPaintDiffuseReady = true;
    }
    return openShimPaintDiffuseCache;
}
float4 OpenShimSampleTerrainPaint(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g)
{
    // The fourth control channel is a weight, never terrain transparency, and
    // diffuse alpha (specular in the material form) is not the detail weight.
    float3 colour = OpenShimPaintDiffuse(tex, sam, g).rgb;
    if (openShimPaintMacro.x > 0)
    {
        // Two octaves of soft noise per channel, roughly -1..1.
        float2 m = g.pos.xz / max(openShimPaintMacro.x, 1.0);
        float bright = OpenShimDetileNoise(m) * 1.3 + OpenShimDetileNoise(m * 2.7 + 17.0) * 0.7 - 1.0;
        float sat = OpenShimDetileNoise(m * 0.8 + 41.0) * 1.3 + OpenShimDetileNoise(m * 2.3 + 73.0) * 0.7 - 1.0;
        float luma = dot(colour, float3(0.299, 0.587, 0.114));
        colour = max(lerp(luma, colour, 1.0 + sat * openShimPaintMacro.z) * (1.0 + bright * openShimPaintMacro.y), 0.0);
        if (openShimPaintMacro.w != 0)
        {
            // Patches (about half the ground) turn the chroma in YIQ; positive turns green toward yellow.
            float patch = saturate(OpenShimDetileNoise(m * 0.7 + 113.0) * 1.3 + OpenShimDetileNoise(m * 1.9 + 151.0) * 0.7 - 1.0);
            float angle = patch * openShimPaintMacro.w, c = cos(angle), s = sin(angle);
            float y = dot(colour, float3(0.299, 0.587, 0.114));
            float2 iq = float2(dot(colour, float3(0.596, -0.274, -0.322)), dot(colour, float3(0.211, -0.523, 0.312)));
            iq = float2(iq.x * c - iq.y * s, iq.x * s + iq.y * c);
            colour = max(y + float3(0.956 * iq.x + 0.621 * iq.y, -0.272 * iq.x - 0.647 * iq.y, -1.106 * iq.x + 1.703 * iq.y), 0.0);
        }
    }
    return float4(colour, 1);
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
// OpenShimPaintSampleTaps on the normal slice, taking the near top
// projection from the height pass when the layer had one. Call after
// OpenShimPaintWeights with the same geometry.
OpenShimPaintTaps OpenShimPaintNormalTaps(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g, int i)
{
    float s = 1.0 / openShimPaintRepeats[i], slice = OpenShimPaintSlice(i, 5);
    bool detile = openShimPaintDetile[i] > 0;
    OpenShimPaintTaps nearTaps = (OpenShimPaintTaps)0, farTaps = (OpenShimPaintTaps)0;
    [branch] if (g.farMix < 1)
    {
        [branch] if (g.blend.x > 0) nearTaps.x = OPENSHIM_PAINT_TAP(tex, sam, g, OPENSHIM_PAINT_UV_X, s, slice, detile);
        if (openShimPaintNearValid[i]) nearTaps.y = openShimPaintNearTop[i];
        else
        {
            [branch] if (g.blend.y > 0) nearTaps.y = OPENSHIM_PAINT_TAP(tex, sam, g, OPENSHIM_PAINT_UV_Y, s, slice, detile);
        }
        [branch] if (g.blend.z > 0) nearTaps.z = OPENSHIM_PAINT_TAP(tex, sam, g, OPENSHIM_PAINT_UV_Z, s, slice, detile);
    }
    [branch] if (g.farMix > 0) farTaps = OpenShimPaintSampleScale(tex, sam, g, s / openShimPaintFar.x, slice, detile);
    nearTaps.x = lerp(nearTaps.x, farTaps.x, g.farMix);
    nearTaps.y = lerp(nearTaps.y, farTaps.y, g.farMix);
    nearTaps.z = lerp(nearTaps.z, farTaps.z, g.farMix);
    return nearTaps;
}
// Packed tangent normal (mode 0 RGB) in the paint frame; the lighting path
// renormalizes. Flat ground: +x along world X, +y along world Z.
float4 OpenShimSampleTerrainPaintNormal(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g)
{
    OpenShimPaintMix weights = OpenShimPaintWeights(tex, sam, g);
    // Crater slopes tilt the blended normal like a height field, on the
    // crater layers only; the domain shader displaces the same bowls.
    // Ground without those layers skips the field.
    float2 slope = 0;
#if OPENSHIM_PAINT_CRATERS
    float craterWeight = OpenShimPaintDot(weights, openShimPaintCraterLayers);
    [branch] if (craterWeight > 0)
        slope = OpenShimCraterField(g.pos.xz, openShimPaintCraters, g.foot).slope * craterWeight;
#endif
#if OPENSHIM_PAINT_DETAIL
    float detailWeight = OpenShimPaintDot(weights, openShimPaintDetailLayers);
    [branch] if (detailWeight > 0)
        slope += OpenShimDetailField(g.pos.xz, openShimPaintDetail, g.foot).slope * detailWeight;
#endif
#if OPENSHIM_PAINT_TRIPLANAR
    float3 world = 0;
    [unroll] for (int i = 0; i < OPENSHIM_PAINT_LAYERS; ++i)
        [branch] if (weights.w[i] > 0)
            world += OpenShimPaintWorldNormal(OpenShimPaintNormalTaps(tex, sam, g, i), g) * weights.w[i];
    world.xz -= world.y * slope;
    return float4(mul(OpenShimPaintWorldFrame(g.n), normalize(world)) * 0.5 + 0.5, 1);
#else
    float4 sum = 0;
    [unroll] for (int i = 0; i < OPENSHIM_PAINT_LAYERS; ++i)
        [branch] if (weights.w[i] > 0)
        {
            OpenShimPaintTaps t = OpenShimPaintNormalTaps(tex, sam, g, i);
            sum += (t.x * g.blend.x + t.y * g.blend.y + t.z * g.blend.z) * weights.w[i];
        }
#if OPENSHIM_PAINT_CRATERS || OPENSHIM_PAINT_DETAIL
    float3 n = sum.rgb * 2 - 1;
    n.xy -= n.z * slope;
    return float4(normalize(n) * 0.5 + 0.5, 1);
#else
    return float4(sum.rgb, 1);
#endif
#endif
}
float3 OpenShimSampleTerrainPaintSpecular(Texture2DArray tex, SamplerState sam, OpenShimPaintGeo g)
{
    return OpenShimPaintDiffuse(tex, sam, g).aaa;
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
            // The far scale fades by view depth; a pass without it stays near.
            constants << "#define OPENSHIM_PAINT_VIEW_DEPTH " <<
                (source.find("in float vDepth") != std::string::npos ? "vDepth" : "0.0") << "\n";
            constants << "#define OPENSHIM_PAINT_CRATERS " << (config.craters[0] > 0 ? 1 : 0) << "\n";
            constants << "#define OPENSHIM_PAINT_DETAIL " << (config.detail[0] > 0 ? 1 : 0) << "\n";
            // Parallax needs the view position, and view depth for its fade.
            const bool parallax = config.parallax[0] > 0 && source.find("in float3 vViewPosition") != std::string::npos &&
                source.find("in float vDepth") != std::string::npos;
            constants << "#define OPENSHIM_PAINT_PARALLAX " << (parallax ? 1 : 0) << "\n";
            const auto vector = [&](const char* name, const float* v, int n) {
                constants << "static const float" << n << " " << name << " = float" << n << "(";
                for (int i = 0; i < n; ++i) constants << (i ? "," : "") << v[i];
                constants << ");\n"; };
            vector("openShimPaintFar", config.farScale.data(), 4);
            vector("openShimPaintMacro", config.macro.data(), 4);
            vector("openShimPaintCraters", config.craters.data(), 4);
            vector("openShimPaintDetail", config.detail.data(), 4);
            vector("openShimPaintParallax", config.parallax.data(), 4);
            vector("openShimPaintBounds", config.bounds.data(), 4);
            source.insert(0, constants.str() + LayerHlsl(config) + DetileHlsl() + CraterHlsl() + BlendHlsl());
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
