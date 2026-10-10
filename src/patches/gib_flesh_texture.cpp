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
// Sparse pale flecks (fat, sinew): one candidate per cell of a periodic grid,
// stretched along the fibre (x) axis. Returns coverage 0..1.
float flecks(float u, float v)
{
    constexpr int kCells = 14;
    const float x = u * kCells, y = v * kCells;
    const int cx = static_cast<int>(std::floor(x)), cy = static_cast<int>(std::floor(y));
    float best = 0.0f;
    for (int oy = -1; oy <= 1; ++oy)
        for (int ox = -1; ox <= 1; ++ox)
        {
            const int gx = cx + ox, gy = cy + oy;
            const int wx = wrap(gx, kCells), wy = wrap(gy, kCells);
            if (hash01(wx, wy, 71) < 0.8f)
                continue;
            const float px = static_cast<float>(gx) + 0.2f + 0.6f * hash01(wx, wy, 72);
            const float py = static_cast<float>(gy) + 0.2f + 0.6f * hash01(wx, wy, 73);
            const float dx = (x - px) * 0.42f, dy = (y - py) * 1.7f;
            const float d = std::sqrt(dx * dx + dy * dy);
            best = std::max(best, 1.0f - smooth(clamp01((d - 0.07f) / 0.16f)));
        }
    return best;
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

std::string GibFleshMaterialScript()
{
    // Vertex colours carry the gore (clotted rim, red muscle, ivory bone); the
    // texture supplies fibre, fat and veins and is mid-tone so the colours
    // modulate it. Tight, low specular for a wet look. Plain fixed-function
    // state on purpose: the same pass DX9 draws natively and the DX11
    // compatibility layer instantiates (one texture unit, modulate).
    return GibFleshMaterialHeader() + "\n" +
           "// Override it with an openshim_gib_flesh.material at the top of a chunk payload\n"
           "// directory (<mod>/chunkMeshes/ or BZ_ASSETS/common/models/OpenShimChunkPayloads/).\n"
           "material " +
           kGibFleshMaterialName +
           "\n"
           "{\n"
           "    technique\n"
           "    {\n"
           "        pass\n"
           "        {\n"
           "            ambient vertexcolour\n"
           "            diffuse vertexcolour\n"
           "            specular 0.35 0.25 0.25 48\n"
           "            cull_hardware none\n"
           "            texture_unit\n"
           "            {\n"
           "                texture " +
           kGibFleshTextureFile +
           "\n"
           "            }\n"
           "        }\n"
           "    }\n"
           "}\n";
}

std::vector<uint8_t> GibFleshTextureRgb()
{
    constexpr unsigned N = kGibFleshTextureSize;
    std::vector<uint8_t> out(static_cast<size_t>(N) * N * 3);
    const Rgb muscleDark{0.56f, 0.40f, 0.40f}, muscleLight{0.93f, 0.80f, 0.78f};
    const Rgb fat{1.0f, 0.95f, 0.84f}, vein{0.42f, 0.16f, 0.19f};
    for (unsigned py = 0; py < N; ++py)
        for (unsigned px = 0; px < N; ++px)
        {
            const float u = (static_cast<float>(px) + 0.5f) / N, v = (static_cast<float>(py) + 0.5f) / N;
            // Low-frequency warp wobbles the fibres so they are not ruled lines.
            const float warp = vnoise(u * 4.0f, v * 8.0f, 4, 8, 11) - 0.5f;
            // Fibres run along u: slow across, fast down the image.
            const float fibre = 0.6f * vnoise(u * 2.0f + warp * 0.9f, v * 48.0f + warp * 3.0f, 2, 48, 1) +
                                0.4f * vnoise(u * 4.0f + warp * 0.5f, v * 112.0f, 4, 112, 2);
            const float cloud = 0.5f * vnoise(u * 4.0f, v * 4.0f, 4, 4, 3) + 0.3f * vnoise(u * 8.0f, v * 8.0f, 8, 8, 4) +
                                0.2f * vnoise(u * 16.0f, v * 16.0f, 16, 16, 5);
            Rgb c = mix(muscleDark, muscleLight, clamp01(0.15f + 0.65f * fibre + 0.35f * cloud));
            // Pale fat and sinew flecks.
            c = mix(c, fat, 0.85f * flecks(u, v));
            // Veins: thin dark ridges where a smooth field crosses its midline,
            // only where a coarser mask allows them.
            const float ridge = std::abs(vnoise(u * 5.0f + warp, v * 5.0f, 5, 5, 6) - 0.5f) * 2.0f;
            const float ridge2 = std::abs(vnoise(u * 9.0f, v * 9.0f + warp, 9, 9, 7) - 0.5f) * 2.0f;
            const float mask = smooth(clamp01((vnoise(u * 3.0f, v * 3.0f, 3, 3, 8) - 0.42f) / 0.2f));
            const float veinAmount = std::max(1.0f - smooth(clamp01(ridge / 0.07f)),
                                              0.6f * (1.0f - smooth(clamp01(ridge2 / 0.05f)))) *
                                     mask;
            c = mix(c, vein, 0.8f * veinAmount);
            uint8_t *dst = &out[(static_cast<size_t>(py) * N + px) * 3];
            dst[0] = static_cast<uint8_t>(clamp01(c.r) * 255.0f + 0.5f);
            dst[1] = static_cast<uint8_t>(clamp01(c.g) * 255.0f + 0.5f);
            dst[2] = static_cast<uint8_t>(clamp01(c.b) * 255.0f + 0.5f);
        }
    return out;
}

std::vector<uint8_t> GibFleshTextureTga()
{
    constexpr unsigned N = kGibFleshTextureSize;
    const std::string id = versionTag();
    const auto rgb = GibFleshTextureRgb();
    std::vector<uint8_t> out;
    out.reserve(18 + id.size() + static_cast<size_t>(N) * N * 3);
    const uint8_t header[18] = {static_cast<uint8_t>(id.size()), 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                static_cast<uint8_t>(N & 0xFF), static_cast<uint8_t>(N >> 8),
                                static_cast<uint8_t>(N & 0xFF), static_cast<uint8_t>(N >> 8), 24, 0};
    out.insert(out.end(), header, header + sizeof(header));
    out.insert(out.end(), id.begin(), id.end());
    // Bottom-left origin: rows bottom to top, pixels B,G,R.
    for (unsigned row = 0; row < N; ++row)
    {
        const unsigned y = N - 1 - row;
        for (unsigned x = 0; x < N; ++x)
        {
            const uint8_t *s = &rgb[(static_cast<size_t>(y) * N + x) * 3];
            out.push_back(s[2]);
            out.push_back(s[1]);
            out.push_back(s[0]);
        }
    }
    return out;
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
