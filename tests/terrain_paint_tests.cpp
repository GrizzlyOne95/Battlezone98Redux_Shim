#include "terrain_paint.h"
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace BZROpenShim;
static void check(bool ok, const char* message) { if (!ok) throw std::runtime_error(message); }
int main()
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
        for (int bad = 0; bad < 3; ++bad)
        {
            TerrainPaint::Config broken = table;
            if (bad == 0) broken.maps[1].control.clear();
            if (bad == 1) broken.maps[1] = broken.maps[0];
            if (bad == 2) broken.maps[1].fingerprint = "FEDCBA9876543210";
            bool rejected = false; try { broken.Validate(); } catch (...) { rejected = true; }
            check(rejected, "invalid multi-map table accepted");
        }
        std::cout << "PASS: map contracts, multi-map selection, native cluster seam and preserved auxiliary UVs\n";
        return 0;
    }
    catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
