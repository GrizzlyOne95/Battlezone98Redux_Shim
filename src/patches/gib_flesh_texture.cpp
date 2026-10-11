#include "gib_flesh_texture.h"
#include <algorithm>
#include <cmath>
#include <cstring>

namespace BZROpenShim::NativeChunks
{
namespace
{
constexpr const char *kTgaIdPrefix = "OpenShim gib flesh ";

uint32_t hash32(uint32_t x)
{
    x ^= x >> 16;
    x *= 0x7feb352dU;
    x ^= x >> 15;
    x *= 0x846ca68bU;
    x ^= x >> 16;
    return x;
}
float hash01(int x, int y, uint32_t seed)
{
    const uint32_t h = hash32(static_cast<uint32_t>(x) * 0x9e3779b1U ^ hash32(static_cast<uint32_t>(y) + seed * 0x85ebca6bU));
    return static_cast<float>(h >> 8) * (1.0f / 16777216.0f);
}
int wrap(int v, int period)
{
    v %= period;
    return v < 0 ? v + period : v;
}
float smooth(float t)
{
    return t * t * (3.0f - 2.0f * t);
}
float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}
float clamp01(float v)
{
    return v < 0.0f ? 0.0f : (v > 1.0f ? 1.0f : v);
}
// Value noise on a lattice that repeats every px by py cells, so the finished
// image tiles in both directions (cap UVs are planar and unbounded).
float vnoise(float x, float y, int px, int py, uint32_t seed)
{
    const float fx = std::floor(x), fy = std::floor(y);
    const int ix = static_cast<int>(fx), iy = static_cast<int>(fy);
    const float tx = smooth(x - fx), ty = smooth(y - fy);
    const float a = hash01(wrap(ix, px), wrap(iy, py), seed), b = hash01(wrap(ix + 1, px), wrap(iy, py), seed);
    const float c = hash01(wrap(ix, px), wrap(iy + 1, py), seed), d = hash01(wrap(ix + 1, px), wrap(iy + 1, py), seed);
    return lerp(lerp(a, b, tx), lerp(c, d, tx), ty);
}
struct Rgb
{
    float r, g, b;
};
Rgb mix(Rgb a, Rgb b, float t)
{
    return {lerp(a.r, b.r, t), lerp(a.g, b.g, t), lerp(a.b, b.b, t)};
}
// Periodic, jittered cellular noise stretched along x: nearest and second
// nearest feature distance (in texels) and the nearest cell's id hash. Cells
// are cx wide by cy tall across the unit square, so the muscle bundles come out
// as elongated irregular polygons.
struct Cell
{
    float f1, f2, id;
};
Cell cellular(float u, float v, int cx, int cy, uint32_t seed)
{
    const float x = u * cx, y = v * cy;
    const int ix = static_cast<int>(std::floor(x)), iy = static_cast<int>(std::floor(y));
    Cell best{1e9f, 1e9f, 0.0f};
    for (int oy = -1; oy <= 1; ++oy)
        for (int ox = -1; ox <= 1; ++ox)
        {
            const int gx = ix + ox, gy = iy + oy;
            const int wx = wrap(gx, cx), wy = wrap(gy, cy);
            const float fx = static_cast<float>(gx) + 0.15f + 0.7f * hash01(wx, wy, seed);
            const float fy = static_cast<float>(gy) + 0.15f + 0.7f * hash01(wx, wy, seed + 1);
            const float dx = (x - fx) * (kGibFleshTextureSize / static_cast<float>(cx));
            const float dy = (y - fy) * (kGibFleshTextureSize / static_cast<float>(cy));
            const float d = std::sqrt(dx * dx + dy * dy);
            if (d < best.f1)
            {
                best.f2 = best.f1;
                best.f1 = d;
                best.id = hash01(wx, wy, seed + 2);
            }
            else if (d < best.f2)
                best.f2 = d;
        }
    return best;
}
float fbm(float u, float v, int period, uint32_t seed)
{
    return 0.5f * vnoise(u * period, v * period, period, period, seed) +
           0.3f * vnoise(u * period * 2, v * period * 2, period * 2, period * 2, seed + 1) +
           0.2f * vnoise(u * period * 4, v * period * 4, period * 4, period * 4, seed + 2);
}
std::string versionTag()
{
    return std::string(kTgaIdPrefix) + kGibFleshVersion;
}
} // namespace

std::string GibFleshMaterialHeader()
{
    return std::string(kGibFleshMaterialMarker) + " " + kGibFleshVersion + " (generated; do not edit).";
}

std::string GibFleshZoneMaterialHeader()
{
    return std::string(kGibFleshZoneMaterialMarker) + " " + kGibFleshVersion + " (generated; do not edit).";
}

namespace
{
struct ZoneSpec
{
    const char *material, *textureFile;
    // Texture: kind 0 = soft mottled colour (base -> accent), 1 = the muscle
    // image darkened (clotted band).
    int kind;
    float baseR, baseG, baseB, accentR, accentG, accentB;
    int period;          // mottle scale (cells across the 64 px tile)
    const char *specular;
    const char *shininess;
};
std::vector<uint8_t> muscleRgb(float darken, float maroon);
// Fresh wound tissue: a thin dark blood film at the skin edge; pale fat stained
// pink with blood; a dark maroon clotted band where blood pools; desaturated
// ivory bone; dark red-brown spongy marrow. Wet, high specular everywhere but
// the bone.
const ZoneSpec kZones[] = {
    {"openshim_gib_flesh_skin", "openshim_gib_flesh_skin.tga", 0, 0.20f, 0.035f, 0.04f, 0.33f, 0.055f, 0.055f, 5,
     "0.55 0.30 0.30", "90"},
    {"openshim_gib_flesh_fat", "openshim_gib_flesh_fat.tga", 0, 0.82f, 0.68f, 0.60f, 0.74f, 0.46f, 0.43f, 6,
     "0.40 0.32 0.30", "64"},
    {"openshim_gib_flesh_clot", "openshim_gib_flesh_clot.tga", 1, 0, 0, 0, 0, 0, 0, 0, "0.75 0.45 0.45", "110"},
    // Desaturated ivory-grey with a slight yellowing, darker pitting.
    {"openshim_gib_flesh_bone", "openshim_gib_flesh_bone.tga", 0, 0.63f, 0.61f, 0.53f, 0.50f, 0.48f, 0.41f, 5,
     "0.35 0.35 0.30", "48"},
    // Dark, spongy red-brown: mottled, pitted (kind 2).
    {"openshim_gib_flesh_marrow", "openshim_gib_flesh_marrow.tga", 2, 0.31f, 0.09f, 0.07f, 0.15f, 0.035f, 0.03f, 8,
     "0.65 0.38 0.38", "95"}};

// One stock-style material: BZBase with the diffuse texture aliased and the
// scalar parameters set the way the stock pilots set them. NormalMap,
// SpecularMap and EmissiveMap keep BZBase's neutral defaults (flat_n.png,
// white.png, black.png), so there is no emissive glow and no normal detail.
std::string stockMaterial(const std::string &name, const std::string &textureFile, const std::string &specular,
                          const std::string &shininess)
{
    return "material " + name + " : BZBase\n{\n\tset_texture_alias DiffuseMap " + textureFile +
           "\n\n\tset $diffuse \"1 1 1\"\n\tset $ambient \"1 1 1\"\n\tset $specular \"" + specular +
           "\"\n\tset $shininess \"" + shininess + "\"\n\tset $bias \"0\"\n}\n";
}
std::vector<uint8_t> tga24(unsigned width, unsigned height, const std::vector<uint8_t> &rgbTopDown)
{
    const std::string id = versionTag();
    std::vector<uint8_t> out;
    out.reserve(18 + id.size() + rgbTopDown.size());
    const uint8_t header[18] = {static_cast<uint8_t>(id.size()), 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                static_cast<uint8_t>(width & 0xFF), static_cast<uint8_t>(width >> 8),
                                static_cast<uint8_t>(height & 0xFF), static_cast<uint8_t>(height >> 8), 24, 0};
    out.insert(out.end(), header, header + sizeof(header));
    out.insert(out.end(), id.begin(), id.end());
    // Bottom-left origin: rows bottom to top, pixels B,G,R.
    for (unsigned row = 0; row < height; ++row)
    {
        const unsigned y = height - 1 - row;
        for (unsigned x = 0; x < width; ++x)
        {
            const uint8_t *p = &rgbTopDown[(static_cast<size_t>(y) * width + x) * 3];
            out.push_back(p[2]);
            out.push_back(p[1]);
            out.push_back(p[0]);
        }
    }
    return out;
}
} // namespace

std::string GibFleshMaterialScript()
{
    // The muscle: BZBase with the muscle texture as its diffuse map, wet and
    // tight in specular.
    return GibFleshMaterialHeader() + "\n" +
           "// Override it with an openshim_gib_flesh.material at the top of a chunk payload\n"
           "// directory (<mod>/chunkMeshes/ or BZ_ASSETS/common/models/OpenShimChunkPayloads/).\n"
           "// The thin skin edge, fat band, bone and marrow are in openshim_gib_flesh_zones.material.\n"
           "import * from \"BZBase.material\"\n\n" +
           stockMaterial(kGibFleshMaterialName, kGibFleshTextureFile, "0.85 0.60 0.60", "120");
}

std::string GibFleshZoneMaterialScript()
{
    std::string out = GibFleshZoneMaterialHeader() + "\n" +
                      "// Override it with an openshim_gib_flesh_zones.material at the top of a chunk payload directory.\n"
                      "import * from \"BZBase.material\"\n\n";
    for (const ZoneSpec &zone : kZones)
        out += stockMaterial(zone.material, zone.textureFile, zone.specular, zone.shininess) + "\n";
    return out;
}

std::vector<GibFleshTexture> GibFleshTextures()
{
    std::vector<GibFleshTexture> out;
    out.push_back({kGibFleshTextureFile, false, GibFleshTextureTga()});
    constexpr unsigned Z = 64;
    for (const ZoneSpec &zone : kZones)
    {
        if (zone.kind == 1)
        {
            out.push_back({zone.textureFile, true, tga24(kGibFleshTextureSize, kGibFleshTextureSize, muscleRgb(0.7f, 0.55f))});
            continue;
        }
        // Soft tileable mottle with fine grain: no flat colour, no outline.
        std::vector<uint8_t> rgb(static_cast<size_t>(Z) * Z * 3);
        const Rgb base{zone.baseR, zone.baseG, zone.baseB}, accent{zone.accentR, zone.accentG, zone.accentB};
        for (unsigned y = 0; y < Z; ++y)
            for (unsigned x = 0; x < Z; ++x)
            {
                const float u = (static_cast<float>(x) + 0.5f) / Z, v = (static_cast<float>(y) + 0.5f) / Z;
                const float blob = fbm(u, v, zone.period, 90 + static_cast<uint32_t>(zone.period));
                const float grain = vnoise(u * 16.0f, v * 16.0f, 16, 16, 95) - 0.5f;
                Rgb c = mix(base, accent, clamp01((blob - 0.3f) * 1.8f));
                if (zone.kind == 2)
                {
                    // Spongy marrow: dark pores where a cellular field is near a feature point.
                    const Cell pore = cellular(u, v, 9, 9, 120);
                    const float pit = 1.0f - smooth(clamp01(pore.f1 / 5.0f));
                    c = mix(c, Rgb{c.r * 0.35f, c.g * 0.35f, c.b * 0.35f}, 0.8f * pit);
                }
                const float g = 1.0f + grain * 0.12f;
                uint8_t *dst = &rgb[(static_cast<size_t>(y) * Z + x) * 3];
                dst[0] = static_cast<uint8_t>(clamp01(c.r * g) * 255.0f + 0.5f);
                dst[1] = static_cast<uint8_t>(clamp01(c.g * g) * 255.0f + 0.5f);
                dst[2] = static_cast<uint8_t>(clamp01(c.b * g) * 255.0f + 0.5f);
            }
        out.push_back({zone.textureFile, true, tga24(Z, Z, rgb)});
    }
    return out;
}

namespace
{
// The muscle image; `darken` scales it (the clotted band reuses it at 0.55).
std::vector<uint8_t> muscleRgb(float darken, float maroon)
{
    constexpr unsigned N = kGibFleshTextureSize;
    std::vector<uint8_t> out(static_cast<size_t>(N) * N * 3);
    const Rgb muscleLow{0.30f, 0.045f, 0.05f}, muscleHigh{0.60f, 0.10f, 0.08f}; // dark venous to arterial red
    const Rgb perimysium{0.58f, 0.40f, 0.40f}, marbling{0.66f, 0.52f, 0.48f}, vessel{0.15f, 0.02f, 0.03f};
    const Rgb maroonColour{0.20f, 0.028f, 0.045f}, arterialColour{0.70f, 0.09f, 0.07f}, sheenColour{0.62f, 0.46f, 0.47f};
    for (unsigned py = 0; py < N; ++py)
        for (unsigned px = 0; px < N; ++px)
        {
            float u = (static_cast<float>(px) + 0.5f) / N, v = (static_cast<float>(py) + 0.5f) / N;
            // Domain warp so bundle outlines are irregular, not a ruled grid.
            const float wu = vnoise(u * 5.0f, v * 5.0f, 5, 5, 21) - 0.5f, wv = vnoise(u * 5.0f, v * 5.0f, 5, 5, 22) - 0.5f;
            u += wu * 0.10f;
            v += wv * 0.10f;
            // Multi-scale bundles: a coarse cell field (big, elongated along x) and a
            // fine one, blended by low-frequency noise so cell size varies strongly
            // across the image; plus a few very large muscle-group cells.
            const float warpLong = 0.10f * (fbm(u, v, 2, 36) - 0.5f);
            const Cell coarse = cellular(u + warpLong, v, 3, 7, 31);
            const Cell fine = cellular(u, v + 0.5f * warpLong, 8, 26, 33);
            const float useCoarse = smooth(clamp01((fbm(u, v, 2, 45) - 0.42f) / 0.2f));
            const Cell cell{fine.f1 + (coarse.f1 - fine.f1) * useCoarse, fine.f2 + (coarse.f2 - fine.f2) * useCoarse,
                            fine.id + (coarse.id - fine.id) * useCoarse};
            const Cell group = cellular(u, v, 2, 3, 37);
            const float drift = fbm(u, v, 3, 41);
            const float tone = clamp01(0.45f * cell.id + 0.3f * group.id + 0.25f * drift);
            Rgb c = mix(muscleLow, muscleHigh, tone);
            // Fibre striation inside a bundle: fine lines along x.
            const float strand = vnoise(u * 3.0f, v * 190.0f, 3, 190, 51) - 0.5f;
            c = mix(c, Rgb{c.r * 0.62f, c.g * 0.62f, c.b * 0.62f}, clamp01(0.5f + strand * 1.8f) * 0.65f);
            // Perimysium: thin pale lines where two cells meet.
            const float gap = cell.f2 - cell.f1;
            // Thin, low contrast and broken: a noise gate removes stretches of the line.
            const float broken = smooth(clamp01((vnoise(u * 9.0f, v * 24.0f, 9, 24, 77) - 0.35f) / 0.2f));
            const float line = (1.0f - smooth(clamp01(gap / 1.6f))) * broken;
            // A few big separations between muscle groups: wider, softer, still low contrast.
            const float groupLine = (1.0f - smooth(clamp01((group.f2 - group.f1) / 5.0f))) *
                                    smooth(clamp01((vnoise(u * 4.0f, v * 6.0f, 4, 6, 78) - 0.25f) / 0.3f));
            // Fat marbling: sparse irregular patches that favour the cell
            // boundaries (fat runs between bundles).
            const float patch = smooth(clamp01((fbm(u, v, 4, 61) - 0.70f) / 0.12f));
            const float fatAlong = 1.0f - smooth(clamp01(gap / 14.0f));
            const float fat = patch * (0.25f + 0.75f * fatAlong);
            c = mix(c, perimysium, 0.12f * line * (1.0f - 0.5f * fat));
            c = mix(c, perimysium, 0.18f * groupLine);
            // Marbling is only a faint, thin pink-grey hint now.
            c = mix(c, marbling, 0.12f * fat);
            // Glistening fascia/membrane sheen and bright arterial blood patches.
            const float sheen = smooth(clamp01((fbm(u, v, 3, 91) - 0.62f) / 0.14f));
            c = mix(c, sheenColour, 0.30f * sheen);
            const float arterial = smooth(clamp01((fbm(u, v, 4, 95) - 0.55f) / 0.15f));
            c = mix(c, arterialColour, 0.5f * arterial * (1.0f - sheen));
            // Very few thin dark vessels: a ridge of low-frequency noise, kept
            // only where a coarse mask is high.
            const float ridge = std::abs(vnoise(u * 4.0f, v * 4.0f, 4, 4, 71) - 0.5f) * 2.0f;
            const float mask = smooth(clamp01((vnoise(u * 2.0f, v * 2.0f, 2, 2, 72) - 0.62f) / 0.12f));
            c = mix(c, vessel, 0.85f * (1.0f - smooth(clamp01(ridge / 0.035f))) * mask);
            // Darker clotted patches, soft-edged and low frequency.
            const float clot = smooth(clamp01((fbm(u, v, 3, 81) - 0.50f) / 0.18f));
            c = mix(c, maroonColour, 0.75f * clot);
            c = mix(c, maroonColour, maroon);
            c = Rgb{c.r * darken, c.g * darken, c.b * darken};
            uint8_t *dst = &out[(static_cast<size_t>(py) * N + px) * 3];
            dst[0] = static_cast<uint8_t>(clamp01(c.r) * 255.0f + 0.5f);
            dst[1] = static_cast<uint8_t>(clamp01(c.g) * 255.0f + 0.5f);
            dst[2] = static_cast<uint8_t>(clamp01(c.b) * 255.0f + 0.5f);
        }
    return out;
}
} // namespace

std::vector<uint8_t> GibFleshTextureRgb()
{
    return muscleRgb(1.0f, 0.0f);
}

std::vector<uint8_t> GibFleshTextureTga()
{
    return tga24(kGibFleshTextureSize, kGibFleshTextureSize, GibFleshTextureRgb());
}

bool IsGeneratedGibFleshTga(const std::vector<uint8_t> &bytes)
{
    const size_t prefix = std::strlen(kTgaIdPrefix);
    return bytes.size() >= 18 + prefix && bytes[0] >= prefix && bytes[2] == 2 &&
           std::memcmp(bytes.data() + 18, kTgaIdPrefix, prefix) == 0;
}

bool IsCurrentGibFleshTga(const std::vector<uint8_t> &bytes)
{
    const std::string id = versionTag();
    return bytes.size() >= 18 + id.size() && bytes[0] == id.size() && bytes[2] == 2 &&
           std::memcmp(bytes.data() + 18, id.data(), id.size()) == 0;
}
} // namespace BZROpenShim::NativeChunks
