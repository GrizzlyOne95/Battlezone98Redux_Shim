// LaserSight's engine-independent logic: the enable gate, the export mode,
// the selected slot, the terrain march, the ray/box test, the beam transform
// and the generated assets. `--emit <dir>` writes the generated shader and
// material so scripts can compile the shader with fxc.
#include "laser_sight_assets.h"
#include "laser_sight_policy.h"
#include "test_check.h"

#include <cmath>
#include <filesystem>
#include <fstream>
#include <string>

using namespace BZROpenShim::LaserSight;
using OpenShimTest::Check;

namespace
{
    bool Near(float a, float b, float epsilon = 1e-3f)
    {
        return std::fabs(a - b) <= epsilon;
    }

    void GateTests()
    {
        // option x netgame x mode -> on/off, all eight combinations.
        Check(!Enabled(false, false, 0), "option off, single player: off");
        Check(!Enabled(false, false, 1), "option off wins over the override");
        Check(!Enabled(false, true, 0), "option off, network game: off");
        Check(!Enabled(false, true, 1), "option off wins over the override in a network game");
        Check(Enabled(true, false, 0), "option on, single player: on");
        Check(Enabled(true, false, 1), "option on, single player, override: on");
        Check(!Enabled(true, true, 0), "network game closes the gate by default");
        Check(Enabled(true, true, 1), "override allows the beam in a network game");
        Check(!Enabled(true, true, 2) && !Enabled(true, true, -1), "unknown modes never open the gate");

        Check(IsValidMode(0) && IsValidMode(1), "both documented modes are accepted");
        Check(!IsValidMode(-1) && !IsValidMode(2) && !IsValidMode(1000), "other modes are rejected");
    }

    void SlotTests()
    {
        Check(FirstSelectedSlot(0) == -1, "no selection");
        Check(FirstSelectedSlot(1) == 0 && FirstSelectedSlot(4) == 2 && FirstSelectedSlot(16) == 4, "single slot");
        Check(FirstSelectedSlot(0x6) == 1, "linked weapons: lowest selected slot");
        Check(FirstSelectedSlot(0x20) == -1 && FirstSelectedSlot(0x80000000u) == -1, "only slots 0..4 exist");
    }

    void TerrainTests()
    {
        const TerrainMarch march;
        int samples = 0;
        // Flat ground at y = 0, muzzle 2 m up, pointing 1 in 10 down: the
        // ground is met where 2 - 0.1 * d * |dir| reaches 0.
        auto flat = [&](float, float, float& out) {
            ++samples;
            out = 0.0f;
            return true;
        };
        const float l = std::sqrt(1.0f + 0.01f);
        const Vec3 down = {1.0f / l, -0.1f / l, 0.0f};
        float t = 0.0f;
        Check(MarchTerrain(Vec3{0, 2, 0}, down, 500.0f, march, flat, t), "sloping ray meets flat ground");
        const float expected = 20.0f * l;
        Check(std::fabs(t - expected) <= march.coarseStep / 32.0f && t >= expected - 1e-3f,
              "refined crossing within 1/64 of a step, never short of the ground");
        Check(samples <= 1 + static_cast<int>(expected / march.coarseStep) + 1 + march.refineIterations,
              "coarse steps up to the crossing plus the refinement only");

        samples = 0;
        Check(!MarchTerrain(Vec3{0, 2, 0}, Vec3{1, 0, 0}, 500.0f, march, flat, t), "level ray never meets the ground");
        Check(samples == 1 + static_cast<int>(500.0f / march.coarseStep) + 1,
              "a miss costs maxDistance / coarseStep samples");

        Check(MarchTerrain(Vec3{0, -1, 0}, Vec3{1, 0, 0}, 500.0f, march, flat, t) && t == 0.0f,
              "a buried muzzle hits at once");

        // A 4 m ridge at x = 100: met on its face.
        auto ridge = [](float x, float, float& out) {
            out = (x > 100.0f && x < 104.0f) ? 4.0f : 0.0f;
            return true;
        };
        Check(!MarchTerrain(Vec3{0, 2, 0}, Vec3{1, 0, 0}, 500.0f, march, ridge, t),
              "a ridge narrower than the coarse step between samples is missed (documented limit)");
        auto wideRidge = [](float x, float, float& out) {
            out = x > 100.0f ? 4.0f : 0.0f;
            return true;
        };
        Check(MarchTerrain(Vec3{0, 2, 0}, Vec3{1, 0, 0}, 500.0f, march, wideRidge, t) && t > 100.0f &&
                  t < 100.0f + march.coarseStep / 32.0f,
              "a cliff face is located within the refinement");

        auto unsampled = [](float x, float, float& out) {
            out = 0.0f;
            return x < 10.0f; // the slope meets the ground at x = 20
        };
        Check(!MarchTerrain(Vec3{0, 2, 0}, down, 500.0f, march, unsampled, t), "no terrain sample before the crossing: no terrain hit");
        Check(!MarchTerrain(Vec3{0, 2, 0}, down, 0.0f, march, flat, t), "zero length never hits");
    }

    void RayObbTests()
    {
        Obb box;
        box.center = {50, 0, 0};
        box.half = {2, 2, 2};
        float t = 0.0f;
        Check(RayObb({0, 0, 0}, {1, 0, 0}, box, 500.0f, t) && Near(t, 48.0f), "axis-aligned entry distance");
        Check(!RayObb({0, 0, 0}, {1, 0, 0}, box, 40.0f, t), "box beyond the beam length is missed");
        Check(!RayObb({0, 3, 0}, {1, 0, 0}, box, 500.0f, t), "parallel ray outside the slab is missed");
        Check(!RayObb({0, 0, 0}, {-1, 0, 0}, box, 500.0f, t), "box behind the muzzle is missed");
        Check(RayObb({50, 0, 0}, {1, 0, 0}, box, 500.0f, t) && t == 0.0f, "origin inside reports 0");

        // Rotated 45 degrees about Y: the corner points at the muzzle.
        const float c = std::sqrt(0.5f);
        box.axis[0] = {c, 0, -c};
        box.axis[1] = {0, 1, 0};
        box.axis[2] = {c, 0, c};
        Check(RayObb({0, 0, 0}, {1, 0, 0}, box, 500.0f, t) && Near(t, 50.0f - 2.0f * std::sqrt(2.0f)),
              "oriented box entry at its corner");
    }

    void SegmentTests()
    {
        Check(SegmentCount(0.0f) == 0 && SegmentCount(-1.0f) == 0, "no beam, no segments");
        Check(SegmentCount(1.0f) == 1 && SegmentCount(50.0f) == 1 && SegmentCount(50.5f) == 2, "segment rounding");
        Check(SegmentCount(kMaxBeamLength) == 10, "a full beam is ten grid queries at most");
    }

    void TransformTests()
    {
        const BeamTransform t = MakeBeamTransform({1, 2, 3}, {0, 0, 1}, {0, 1, 0}, 120.0f, 0.05f);
        Check(t.position[0] == 1.0f && t.position[1] == 2.0f && t.position[2] == 3.0f, "beam starts at the muzzle");
        Check(Near(t.orientation[0], 1.0f) && Near(t.orientation[1], 0.0f) && Near(t.orientation[2], 0.0f) &&
                  Near(t.orientation[3], 0.0f),
              "local +Z along the beam: identity for a +Z beam");
        Check(t.scale[0] == 0.05f && t.scale[1] == 0.05f && t.scale[2] == 120.0f, "radius across, length along");

        const BeamTransform x = MakeBeamTransform({0, 0, 0}, {1, 0, 0}, {0, 1, 0}, 10.0f, 0.05f);
        const Quat q = {x.orientation[0], x.orientation[1], x.orientation[2], x.orientation[3]};
        const Vec3 axis = BZROpenShim::ShellCasings::Rotate(q, {0, 0, 1});
        Check(Near(axis.x, 1.0f) && Near(axis.y, 0.0f) && Near(axis.z, 0.0f), "mesh +Z maps onto the beam direction");
        Check(MakeBeamTransform({0, 0, 0}, {1, 0, 0}, {0, 1, 0}, 0.0f, 0.05f).scale[2] > 0.0f,
              "never a zero scale");
    }

    void AssetTests()
    {
        const auto rgb = BeamRgb();
        Check(rgb.size() == kTextureWidth * kTextureHeight * 3, "bounded RGB image");
        Check(rgb == BeamRgb(), "deterministic texture");
        const auto at = [](unsigned y, unsigned x) { return (static_cast<size_t>(y) * kTextureWidth + x) * 3; };
        unsigned long long nearSum = 0, farSum = 0;
        for (unsigned x = 0; x < kTextureWidth; ++x)
        {
            nearSum += rgb[at(0, x)];
            farSum += rgb[at(kTextureHeight - 1, x)];
            Check(rgb[at(0, x)] > rgb[at(0, x) + 1] * 4 && rgb[at(0, x)] > rgb[at(0, x) + 2] * 4, "red beam");
        }
        Check(nearSum > farSum * 2 && farSum > 0, "bright at the muzzle, fading but visible at the far end");
        bool seamless = true;
        for (unsigned y = 0; y < kTextureHeight; ++y)
        {
            const int a = rgb[at(y, 0)], b = rgb[at(y, kTextureWidth - 1)];
            seamless = seamless && std::abs(a - b) < 40;
        }
        Check(seamless, "the wrap seam around the tube is continuous");

        const auto tga = BeamTga();
        Check(IsGeneratedTga(tga) && tga.size() == 18 + tga[0] + rgb.size(), "marked, uncompressed 24-bit TGA");
        Check(!IsGeneratedTga(std::vector<uint8_t>(64, 0)), "an unmarked TGA is the user's");

        const std::string material = MaterialScript();
        const std::string shader = ShaderSource();
        Check(IsGeneratedText(material) && IsGeneratedText(shader), "generated text assets carry the marker");
        Check(!IsGeneratedText("material x {}\n"), "unmarked text is the user's");
        const auto count = [](const std::string& text, const std::string& needle) {
            size_t n = 0;
            for (size_t at = text.find(needle); at != std::string::npos; at = text.find(needle, at + 1))
                ++n;
            return n;
        };
        Check(count(material, "    technique\n") == 2, "two techniques");
        const size_t sm4 = material.find("vertex_program_ref openshim_lasersight_vs");
        const size_t ffp = material.find("fog_override true none");
        Check(sm4 != std::string::npos && ffp != std::string::npos && sm4 < ffp,
              "SM4 technique first (DX11), fixed function second (DX9)");
        Check(material.find("target vs_4_0") != std::string::npos &&
                  material.find("target ps_4_0") != std::string::npos,
              "DX11 programs are SM4");
        Check(count(material, "scene_blend add") == 2 && count(material, "depth_write off") == 2 &&
                  count(material, "lighting off") == 2 && count(material, "cull_hardware none") == 2,
              "both techniques: additive, no depth write, unlit, double sided");
        Check(material.find(std::string("material ") + kMaterialName + "\n") != std::string::npos &&
                  material.find(std::string("source ") + kShaderFile) != std::string::npos &&
                  count(material, std::string("texture ") + kTextureFile) == 2,
              "names tie the material, shader and texture together");
        Check(shader.find("void lasersight_vertex(") != std::string::npos &&
                  shader.find("void lasersight_fragment(") != std::string::npos &&
                  shader.find("SV_POSITION") != std::string::npos && shader.find("SV_TARGET") != std::string::npos,
              "both SM4 entry points");
        Check(material.find("entry_point lasersight_vertex") != std::string::npos &&
                  material.find("entry_point lasersight_fragment") != std::string::npos,
              "material entry points exist in the shader");
    }
}

int main(int argc, char** argv)
{
    if (argc == 3 && std::string(argv[1]) == "--emit")
    {
        const std::filesystem::path dir(argv[2]);
        std::filesystem::create_directories(dir);
        std::ofstream(dir / kShaderFile, std::ios::binary) << ShaderSource();
        std::ofstream(dir / kMaterialFile, std::ios::binary) << MaterialScript();
        const auto tga = BeamTga();
        std::ofstream(dir / kTextureFile, std::ios::binary)
            .write(reinterpret_cast<const char*>(tga.data()), static_cast<std::streamsize>(tga.size()));
        return 0;
    }
    GateTests();
    SlotTests();
    TerrainTests();
    RayObbTests();
    SegmentTests();
    TransformTests();
    AssetTests();
    return OpenShimTest::ExitCode();
}
