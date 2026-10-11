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
    float r, g, b;
    const char *specular;
    const char *shininess;
};
// Thin dark dermis edge, pale yellow subcutaneous fat (matte), ivory bone, dark
// red marrow.
const ZoneSpec kZones[] = {
    {"openshim_gib_flesh_skin", "openshim_gib_flesh_skin.tga", 0.20f, 0.045f, 0.04f, "0.10 0.07 0.07", "24"},
    {"openshim_gib_flesh_fat", "openshim_gib_flesh_fat.tga", 0.90f, 0.78f, 0.48f, "0.10 0.09 0.06", "16"},
    {"openshim_gib_flesh_bone", "openshim_gib_flesh_bone.tga", 0.86f, 0.80f, 0.58f, "0.25 0.25 0.20", "32"},
    {"openshim_gib_flesh_marrow", "openshim_gib_flesh_marrow.tga", 0.30f, 0.04f, 0.04f, "0.30 0.15 0.15", "40"}};

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
           stockMaterial(kGibFleshMaterialName, kGibFleshTextureFile, "0.35 0.25 0.25", "48");
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
    for (const ZoneSpec &zone : kZones)
    {
        // 4x4 solid colour: the base programs sample a texture and ignore the
        // pass colour for hue.
        std::vector<uint8_t> rgb(4u * 4u * 3u);
        for (size_t i = 0; i < rgb.size(); i += 3)
        {
            rgb[i] = static_cast<uint8_t>(clamp01(zone.r) * 255.0f + 0.5f);
            rgb[i + 1] = static_cast<uint8_t>(clamp01(zone.g) * 255.0f + 0.5f);
            rgb[i + 2] = static_cast<uint8_t>(clamp01(zone.b) * 255.0f + 0.5f);
        }
        out.push_back({zone.textureFile, true, tga24(4, 4, rgb)});
    }
    return out;
}

std::vector<uint8_t> GibFleshTextureRgb()
{
    constexpr unsigned N = kGibFleshTextureSize;
    std::vector<uint8_t> out(static_cast<size_t>(N) * N * 3);
    const Rgb muscleLow{0.29f, 0.04f, 0.04f}, muscleHigh{0.48f, 0.10f, 0.08f}; // ~#4a0a0a .. #7a1a14
    const Rgb perimysium{0.64f, 0.36f, 0.31f}, marbling{0.86f, 0.72f, 0.55f}, vessel{0.15f, 0.02f, 0.03f};
    for (unsigned py = 0; py < N; ++py)
        for (unsigned px = 0; px < N; ++px)
        {
            float u = (static_cast<float>(px) + 0.5f) / N, v = (static_cast<float>(py) + 0.5f) / N;
            // Domain warp so bundle outlines are irregular, not a ruled grid.
            const float wu = vnoise(u * 5.0f, v * 5.0f, 5, 5, 21) - 0.5f, wv = vnoise(u * 5.0f, v * 5.0f, 5, 5, 22) - 0.5f;
            u += wu * 0.05f;
            v += wv * 0.06f;
            // Bundles: elongated cells; each gets its own tone, drifting slowly
            // across the image so neighbouring regions differ.
            const Cell cell = cellular(u, v, 5, 14, 31);
            const float drift = fbm(u, v, 3, 41);
            const float tone = clamp01(0.55f * cell.id + 0.45f * drift);
            Rgb c = mix(muscleLow, muscleHigh, tone);
            // Fibre striation inside a bundle: fine lines along x.
            const float strand = vnoise(u * 3.0f, v * 190.0f, 3, 190, 51) - 0.5f;
            c = mix(c, Rgb{c.r * 0.72f, c.g * 0.72f, c.b * 0.72f}, clamp01(0.5f + strand * 1.4f) * 0.55f);
            // Perimysium: thin pale lines where two cells meet.
            const float gap = cell.f2 - cell.f1;
            const float line = 1.0f - smooth(clamp01(gap / 2.8f));
            // Fat marbling: sparse irregular patches that favour the cell
            // boundaries (fat runs between bundles).
            const float patch = smooth(clamp01((fbm(u, v, 4, 61) - 0.60f) / 0.16f));
            const float fatAlong = 1.0f - smooth(clamp01(gap / 14.0f));
            const float fat = patch * (0.25f + 0.75f * fatAlong);
            c = mix(c, perimysium, 0.5f * line * (1.0f - 0.5f * fat));
            c = mix(c, marbling, 0.9f * fat);
            // Very few thin dark vessels: a ridge of low-frequency noise, kept
            // only where a coarse mask is high.
            const float ridge = std::abs(vnoise(u * 4.0f, v * 4.0f, 4, 4, 71) - 0.5f) * 2.0f;
            const float mask = smooth(clamp01((vnoise(u * 2.0f, v * 2.0f, 2, 2, 72) - 0.62f) / 0.12f));
            c = mix(c, vessel, 0.85f * (1.0f - smooth(clamp01(ridge / 0.035f))) * mask);
            uint8_t *dst = &out[(static_cast<size_t>(py) * N + px) * 3];
            dst[0] = static_cast<uint8_t>(clamp01(c.r) * 255.0f + 0.5f);
            dst[1] = static_cast<uint8_t>(clamp01(c.g) * 255.0f + 0.5f);
            dst[2] = static_cast<uint8_t>(clamp01(c.b) * 255.0f + 0.5f);
        }
    return out;
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
