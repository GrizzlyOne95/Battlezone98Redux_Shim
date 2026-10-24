#include "terrain_paint.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
using namespace BZROpenShim;
static void check(bool ok, const char* message) { if (!ok) throw std::runtime_error(message); }
int main(int argc, char** argv)
{
    try
    {
        TerrainPaint::Config config = {true,"0123456789abcdef",{-320,-640,960,640},{12,16,24,32}};
        config.Validate();
        for (auto invalid : {TerrainPaint::Config{true,"wrong",config.bounds,config.repeatMeters},
            TerrainPaint::Config{true,config.fingerprint,{0,0,0,1},config.repeatMeters},
            TerrainPaint::Config{true,config.fingerprint,config.bounds,{0,16,24,32}},
            TerrainPaint::Config{true,config.fingerprint,{0,0,1,std::numeric_limits<float>::infinity()},config.repeatMeters}})
        {
            bool rejected = false; try { invalid.Validate(); } catch (...) { rejected = true; }
            check(rejected, "invalid paint configuration accepted");
        }
        // Same physical seam point in two translated clusters and no camera input.
        check(TerrainPaint::WorldXZ(320,19,0,-640) == TerrainPaint::WorldXZ(0,19,320,-640), "cluster paint seam differs");
        std::string vertex = "float2 openShimStockUV = nativePackedUV;\n    float2 openShimOrientedUV = orientation;\n"
            "    openShimHdUV = openShimOrientedUV;\n    openShimTileSlice = float(openShimSemantic.x);\n"
            "    vTexCoord = (openShimPackedUV + 0.5) / 160.0;\nuntouched();";
        check(TerrainPaint::Specialize(vertex, false, config), "paint vertex specialization failed");
        check(vertex.find("vTexCoord = openShimStockUV;") != std::string::npos &&
            vertex.find("openShimTileSlice = openShimAtlasRect.x;") != std::string::npos &&
            vertex.find("float2 openShimStockUV = nativePackedUV;") != std::string::npos &&
            vertex.find("untouched();") != std::string::npos && vertex.find("orientation") == std::string::npos,
            "paint specialization corrupted stock auxiliary coordinates");
        std::string missing = "wrong shader";
        check(!TerrainPaint::Specialize(missing, false, config) && !TerrainPaint::Specialize(missing, true, config), "unknown source shape accepted");
        std::uint64_t hash = UINT64_C(14695981039346656037);
        TerrainPaint::HashU32(hash, 0x12345678);
        check(TerrainPaint::HashString(hash) == "cccfd053e47c3365", "map fingerprint byte order changed");
        // Multi-map table: select by fingerprint and bounds, never by position or name.
        TerrainPaint::Config table = config;
        table.maps = {{"0123456789abcdef", {-320,-640,960,640}, "control_a.png"},
                      {"fedcba9876543210", {-320,-640,960,640}, "control_b.png"},
                      {"0123456789abcdef", {-3190,-2570,3210,2550}, "control_c.png"}};
        table.Validate();
        check(TerrainPaint::SelectMap(table, "fedcba9876543210", {-320,-640,960,640})->control == "control_b.png", "multi-map pick failed");
        check(TerrainPaint::SelectMap(table, "0123456789abcdef", {-3190,-2570,3210,2550})->control == "control_c.png", "bounds must disambiguate");
        check(!TerrainPaint::SelectMap(table, "0123456789abcdef", {-320,-640,960,641}), "bounds mismatch selected a map");
        check(!TerrainPaint::SelectMap(table, "0000000000000000", {-320,-640,960,640}), "unknown fingerprint selected a map");
        // A partial zone set (fewer zones built than the map has) waits; a full or larger one declines.
        // The 6400 x 5120 entry is a 5 x 4 grid of 1280 m zones.
        check(TerrainPaint::MapMayGrow(table, {-3190,-2570,650,2550}, 12, 1280), "partial terrain must wait for more zones");
        check(TerrainPaint::MapMayGrow(table, {-3190,-2570,3210,2550}, 19, 1280), "full bounds with missing zones must wait");
        check(!TerrainPaint::MapMayGrow(table, {-3190,-2570,3210,2550}, 20, 1280), "complete terrain must not wait");
        check(!TerrainPaint::MapMayGrow(table, {-3190,-2570,3210,2560}, 12, 1280), "terrain outside every entry must not wait");
        check(!TerrainPaint::MapMayGrow(table, {-3190,-2570,650,2550}, 12, 0), "unknown zone size must not wait");
        for (int bad = 0; bad < 3; ++bad)
        {
            TerrainPaint::Config broken = table;
            if (bad == 0) broken.maps[1].control.clear();
            if (bad == 1) broken.maps[1] = broken.maps[0];
            if (bad == 2) broken.maps[1].fingerprint = "FEDCBA9876543210";
            bool rejected = false; try { broken.Validate(); } catch (...) { rejected = true; }
            check(rejected, "invalid multi-map table accepted");
        }
        // Full material form: 9 slices, normal/specular follow paint UVs.
        TerrainPaint::Config material = config;
        material.sliceCount = 9; material.heightMeters = {0.5f, 0, 2, 0};
        material.Validate();
        TerrainPaint::Config varied = material;
        varied.farScale = {5, 40, 250, 0.6f}; varied.macro = {260, 0.12f, 0.15f, 0.35f};
        varied.craters = {6, 0.2f, 0.5f, 3}; varied.craterLayers = {1, 0, 1, 0};
        varied.Validate();
        check(std::abs(varied.CraterMeters() - 0.75f * 0.2f * 2 * 0.42f * (6 + 0.75f * 18 + 0.5f * 54)) < 1e-4f &&
            material.CraterMeters() == 0, "crater displacement bound wrong");
        varied.detail = {40, 1, 4, 1}; varied.detailLayers = {0, 0, 0.5f, 0};
        varied.Validate();
        check(varied.DetailMeters() == 1 && material.DetailMeters() == 0, "detail displacement bound wrong");
        varied.parallax = {1, 40, 12, 0};
        varied.Validate();
        for (int bad = 0; bad < 22; ++bad)
        {
            TerrainPaint::Config broken = bad == 2 ? config : bad >= 4 ? varied : material;
            if (bad == 0) broken.sliceCount = 7;
            if (bad == 1) broken.heightMeters[0] = 40;
            if (bad == 2) broken.heightMeters[1] = 1;
            if (bad == 3) broken.detile[2] = 0.5f;
            if (bad == 4) broken.farScale[0] = 1;
            if (bad == 5) broken.farScale[2] = 30;
            if (bad == 6) broken.macro[0] = 5;
            if (bad == 7) broken.craters[3] = 4;
            if (bad == 8) broken.craterLayers = {};
            if (bad == 9) broken.sliceCount = 5, broken.heightMeters = {};
            if (bad == 10) broken.craters = {};
            if (bad == 11) broken.macro[3] = 2;
            if (bad == 12) broken.detail[1] = 5;
            if (bad == 13) broken.detail[2] = 2.5f;
            if (bad == 14) broken.detailLayers = {};
            if (bad == 15) broken.detailLayers[3] = 2;
            if (bad == 16) broken.detail = {}, broken.detailLayers = {0, 0, 0.5f, 0};
            if (bad == 17) broken.detailLayers[6] = 0.5f;
            if (bad == 18) broken.parallax[0] = 3;
            if (bad == 19) broken.parallax[2] = 12.5f;
            if (bad == 20) broken.parallax[0] = 0;
            if (bad == 21) broken.parallax[1] = 1;
            bool rejected = false; try { broken.Validate(); } catch (...) { rejected = true; }
            check(rejected, "invalid paint material accepted");
        }
        // Eight layers: 18 slices in two banks, per-layer lists of eight, and
        // a second control per map entry.
        TerrainPaint::Config eight = material;
        eight.sliceCount = 18; eight.repeatMeters = {12,16,24,32,8,10,14,20}; eight.heightMeters[6] = 1;
        eight.Validate();
        check(eight.Layers() == 8 && material.Layers() == 4 && eight.Material(), "layer count wrong");
        TerrainPaint::Config eightTable = eight;
        eightTable.maps = {{"0123456789abcdef", {-320,-640,960,640}, "control_a.png", "control_a2.png"}};
        eightTable.Validate();
        for (int bad = 0; bad < 4; ++bad)
        {
            TerrainPaint::Config broken = bad < 2 ? eight : bad == 2 ? eightTable : table;
            if (bad == 0) broken.repeatMeters[5] = 0;
            if (bad == 1) broken.sliceCount = 9;
            if (bad == 2) broken.maps[0].control2.clear();
            if (bad == 3) broken.maps[0].control2 = "control_x.png";
            bool rejected = false; try { broken.Validate(); } catch (...) { rejected = true; }
            check(rejected, "invalid eight-layer paint accepted");
        }
        const std::string pixelSource =
            "float4 d = diffuseMap.Sample(diffuseSam, float3(openShimHdUV, openShimTileSlice));\n"
            "float3x3 tbn = cotangent_frame(geometryNormal, vViewPosition.xyz, vTexCoord);\n"
            "float3x3 tbn = float3x3(baseTangent, binormal, baseNormal);\n"
            "float4 normalSample = normalMap.Sample(normalSam, vTexCoord);\n"
            "float3 specularTex = specularMap.Sample(specularSam, vTexCoord).xyz;\n"
            "float2 detail = vTexCoord * 8.0;\n";
        std::string plain = pixelSource, full = pixelSource;
        check(TerrainPaint::Specialize(plain, true, config) && TerrainPaint::Specialize(full, true, material), "paint PS specialization failed");
        check(plain.find("normalMap.Sample(normalSam, vTexCoord)") != std::string::npos &&
            plain.find("#define OPENSHIM_PAINT_MATERIAL 0") != std::string::npos, "diffuse-only paint touched stock normals");
        check(full.find("normalMap.Sample") == std::string::npos && full.find("specularMap.Sample") == std::string::npos &&
            full.find("OpenShimSampleTerrainPaintNormal(diffuseMap, diffuseSam, OPENSHIM_PAINT_GEO)") != std::string::npos &&
            full.find("float3x3 tbn = OPENSHIM_PAINT_TBN(geometryNormal);") != std::string::npos &&
            full.find("#define OPENSHIM_PAINT_TRIPLANAR_SOURCE 0") != std::string::npos &&
            full.find("vTexCoord * 8.0") != std::string::npos &&
            full.find("#define OPENSHIM_PAINT_MATERIAL 1") != std::string::npos &&
            full.find("#define OPENSHIM_PAINT_LAYERS 4") != std::string::npos, "material paint specialization incomplete");
        std::string wide = pixelSource;
        check(TerrainPaint::Specialize(wide, true, eight) && wide.find("#define OPENSHIM_PAINT_LAYERS 8") != std::string::npos &&
            wide.find("openShimPaintRepeats[8]") != std::string::npos, "eight-layer specialization failed");
        // A colour-only pass (terrain glow) keeps working; a normal sample in
        // an unknown form must decline rather than follow stock atlas UVs.
        std::string noNormals = "float4 d = diffuseMap.Sample(diffuseSam, float3(openShimHdUV, openShimTileSlice));";
        check(TerrainPaint::Specialize(noNormals, true, material) && noNormals.find("OpenShimSampleTerrainPaint(") != std::string::npos,
            "material paint declined a colour-only pass");
        std::string oddNormals = pixelSource;
        oddNormals.replace(oddNormals.find("normalMap.Sample(normalSam, vTexCoord)"), 38, "normalMap.Sample(normalSam, uv2)");
        check(!TerrainPaint::Specialize(oddNormals, true, material), "material paint accepted an unknown normal sample");
        // The shipping enhanced terrain PS must keep every token the material
        // form rewrites. With an argument, export it for fxc validation.
        std::ifstream file(std::filesystem::path(__FILE__).parent_path().parent_path() /
            "resources/renderer/enhanced/openshim_enhanced_terrain-sm4.hlsl");
        std::string shipping{std::istreambuf_iterator<char>(file), {}};
        const auto rewrite = [&](const std::string& from, const std::string& to) {
            const auto at = shipping.find(from);
            check(at != std::string::npos, "enhanced terrain PS contract missing");
            shipping.replace(at, from.size(), to); };
        rewrite("uniform Texture2D diffuseMap : register(t0),", "uniform Texture2DArray diffuseMap : register(t0),");
        rewrite("in float2 vTexCoord : TEXCOORD0,",
            "in float2 vTexCoord : TEXCOORD0,\n in float2 openShimHdUV : TEXCOORD9,\n in float openShimTileSlice : TEXCOORD10,");
        rewrite("diffuseMap.Sample(diffuseSam, vTexCoord)", "diffuseMap.Sample(diffuseSam, float3(openShimHdUV, openShimTileSlice))");
        check(TerrainPaint::Specialize(shipping, true, material), "shipping terrain PS rejected the material form");
        check(shipping.find("#define OPENSHIM_PAINT_TRIPLANAR_SOURCE 1") != std::string::npos,
            "shipping terrain PS lost the view normal or inverse view triplanar needs");
        if (argc == 2) { std::ofstream out(argv[1]); out << shipping; check(bool(out), "specialized PS export failed"); }
        std::cout << "PASS: material form, triplanar inputs, map contracts, multi-map selection, native cluster seam and preserved auxiliary UVs\n";
        return 0;
    }
    catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
