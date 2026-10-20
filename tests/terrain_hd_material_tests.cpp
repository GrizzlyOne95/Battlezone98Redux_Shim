#include "terrain_hd_material.h"
#include "test_check.h"
#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>
#include <limits>

namespace HD = BZROpenShim::TerrainHdMaterial;
using OpenShimTest::Require;

int main(int argc, char** argv)
{
    Require(HD::ProfileAllowsTiles(1, 3) && !HD::ProfileAllowsTiles(0, 3) &&
        !HD::ProfileAllowsTiles(1, 2) && !HD::ProfileAllowsTiles(1, 1) && !HD::ProfileAllowsTiles(1, 0),
        "HD tiles escaped the effective DX11 Enhanced profile gate");
    std::vector<HD::RectBinding> rects = {{{0, 0, .125f, .125f}, 3}, {{.125f, 0, .125f, .125f}, 7}};
    uint8_t mapped = 0;
    Require(HD::FindRectSlice(rects, {.125f, 0, .125f, .125f}, mapped) && mapped == 7,
        "native rectangle mapping depended on numeric tile ID");
    Require(!HD::FindRectSlice(rects, {.5f, 0, .125f, .125f}, mapped), "unknown rectangle accepted");
    rects.push_back({{0, 0, .125f, .125f}, 4});
    Require(!HD::FindRectSlice(rects, {0, 0, .125f, .125f}, mapped), "ambiguous rectangle accepted");
    Require(!HD::ValidRect({0, 0, 0, 1}) && !HD::ValidRect({.9f, 0, .2f, 1}) &&
        !HD::ValidRect({std::numeric_limits<float>::quiet_NaN(), 0, 1, 1}) &&
        HD::ValidRect({0, 0, 1, 1}), "malformed source rectangles accepted");
    Require(!HD::HasDefine("NORMALMAP_ENABLED", ""), "empty define lookup did not terminate");
    Require(HD::HasDefine("MAX_LIGHTS=1,NORMALMAP_ENABLED,SPECULARMAP_ENABLED=1", "NORMALMAP_ENABLED") &&
        !HD::HasDefine("NO_NORMALMAP_ENABLED,NORMALMAP_ENABLED_DEBUG", "NORMALMAP_ENABLED"),
        "per-pass channel defines were confused with unrelated flags");
    auto remap = HD::IdentityRemap();
    uint8_t slice = 0;
    Require(HD::Remap(remap, 255, 256, slice) && slice == 255, "last identity slice failed");
    Require(!HD::Remap(remap, 255, 19, slice), "out-of-range physical slice accepted");
    for (unsigned i = 0; i < 256; ++i) remap[i] = uint8_t(i % 19);
    for (unsigned i = 0; i < 256; ++i)
        Require(HD::Remap(remap, i, 19, slice) && slice == i % 19, "compact alias mapping failed");
    Require(!HD::Remap(remap, 256, 19, slice) && !HD::Remap(remap, 0, 0, slice) &&
        !HD::Remap(remap, 0, 257, slice), "invalid table extent accepted");

    const auto path = std::filesystem::path(__FILE__).parent_path().parent_path() /
        "resources/renderer/enhanced/openshim_enhanced_terrain-sm4.hlsl";
    std::ifstream file(path);
    const std::string original{std::istreambuf_iterator<char>(file), {}};
    Require(!original.empty(), "authoritative terrain shader missing");
    auto shader = original;
    Require(HD::Specialize(shader, {true, true, true}), "authoritative shader contract declined");
    Require(shader.find("Texture2DArray normalMap") != std::string::npos &&
        shader.find("Texture2DArray specularMap") != std::string::npos &&
        shader.find("Texture2DArray emissiveMap") != std::string::npos, "channel declarations not specialized");
    Require(shader.find("cotangent_frame(geometryNormal, vViewPosition.xyz, openShimHdUV)") != std::string::npos,
        "HD normals retained quantized atlas derivatives");
    auto diffuseOnly = original;
    Require(HD::Specialize(diffuseOnly, {}) && diffuseOnly == original, "v1 diffuse-only shader changed");
    auto incomplete = original;
    const auto token = incomplete.find("normalMap.Sample");
    incomplete.erase(token, 1);
    const auto unchanged = incomplete;
    Require(!HD::Specialize(incomplete, {true, true, false}) && incomplete == unchanged,
        "unsupported shader was partly mutated");
    Require(!HD::Specialize(shader, {true, true, true}), "already specialized shader accepted");

    // Export the real specialized PS for fxc interface/variant validation.
    if (argc == 2)
    {
        shader = original;
        Require(HD::ReplaceOnce(shader, "uniform Texture2D diffuseMap : register(t0),",
            "uniform Texture2DArray diffuseMap : register(t0),"), "diffuse contract missing");
        Require(HD::ReplaceOnce(shader, "in float2 vTexCoord : TEXCOORD0,",
            "in float2 vTexCoord : TEXCOORD0,\n in float2 openShimHdUV : TEXCOORD9,\n in float openShimTileSlice : TEXCOORD10,"), "fragment interface missing");
        Require(HD::ReplaceOnce(shader, "diffuseMap.Sample(diffuseSam, vTexCoord)",
            "diffuseMap.Sample(diffuseSam, float3(openShimHdUV, openShimTileSlice))"), "diffuse sample missing");
        Require(HD::Specialize(shader, {true, true, true}), "full PS specialization failed");
        std::ofstream out(argv[1]); out << shader;
        Require(bool(out), "specialized PS output failed");
    }
    std::cout << "terrain_hd_material_tests: all checks passed\n";
}
