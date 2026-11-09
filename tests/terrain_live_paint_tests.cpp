// Live terrain paint generator. With no arguments: property checks on a
// synthetic map. With `recipe.json input.bin output.rgba size`: generate the
// control images for terrain_live_paint_parity.py, which compares them with
// the Python builder.
#include "terrain_live_paint.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>

namespace
{
void check(bool ok, const char* message) { if (!ok) throw std::runtime_error(message); }

TerrainLivePaint::Input Synthetic()
{
    TerrainLivePaint::Input input;
    input.zonesX = input.zonesZ = 1;
    input.bounds = {-1270, -1290, 1290, 1270};
    input.plane.resize(256 * 256);
    for (int z = 0; z < 256; ++z)
    for (int x = 0; x < 256; ++x)
        input.plane[std::size_t(z) * 256 + x] = uint16_t(std::abs(x - 100) * std::abs(z - 150) / 4 % 3000 + 2 * x + x * x / 128);
    input.cells.resize(64 * 64);
    for (int z = 0; z < 64; ++z)
    for (int x = 0; x < 64; ++x)
    {
        const int base = (x / 16 + z / 16) % 2 ? 3 : 0, next = ((x + 1) / 16 + z / 16) % 2 ? 3 : 0;
        input.cells[std::size_t(z) * 64 + x] = uint16_t(base << 12 | next << 8 | (x % 2) << 7);
    }
    return input;
}

int Cli(char** argv)
{
    std::ifstream recipeFile(argv[1]);
    const auto recipe = nlohmann::json::parse(recipeFile);
    std::ifstream file(argv[2], std::ios::binary);
    const std::vector<char> raw((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    TerrainLivePaint::Input input;
    int32_t zones[2] = {};
    check(raw.size() >= 28, "input header truncated");
    std::memcpy(zones, raw.data(), 8);
    std::memcpy(input.bounds.data(), raw.data() + 8, 16);
    std::memcpy(&input.seed, raw.data() + 24, 4);
    input.zonesX = zones[0]; input.zonesZ = zones[1];
    const std::size_t cells = std::size_t(zones[0]) * zones[1] * 64 * 64, samples = cells * 16;
    check(raw.size() == 28 + 2 * (cells + samples), "input size does not match its zones");
    input.cells.resize(cells); input.plane.resize(samples);
    std::memcpy(input.cells.data(), raw.data() + 28, cells * 2);
    std::memcpy(input.plane.data(), raw.data() + 28 + cells * 2, samples * 2);
    const auto images = TerrainLivePaint::Generate(recipe, input, std::stoi(argv[4]));
    std::ofstream out(argv[3], std::ios::binary);
    for (const auto& image : images) out.write(reinterpret_cast<const char*>(image.data()), std::streamsize(image.size()));
    return out ? 0 : 1;
}
}

int main(int argc, char** argv)
{
    try
    {
        if (argc == 5) return Cli(argv);
        // Largest remainders: sums to 255, lower layer first among ties.
        const auto normal = TerrainLivePaint::Generator::Normalize({1, 1, 1, 0, 0, 0, 0, 0}, 4);
        check(normal[0] == 85 && normal[1] == 85 && normal[2] == 85 && normal[3] == 0, "three-way split");
        check(normal[4] == 255 && normal[5] == 0, "empty pixel takes layer 0");
        const auto tie = TerrainLivePaint::Generator::Normalize({1, 1, 0, 0}, 4);
        check(tie[0] == 128 && tie[1] == 127, "tie goes to the lower layer");

        const auto recipe = nlohmann::json::parse(R"({
            "typeWeights": {"0": [1,0,0,0], "3": [0,1,0,0]},
            "transition": {"cap": 0.3, "diagonal": 0.5},
            "outsideWeights": [1,0,0,0], "blurMeters": 14, "weightSize": 64,
            "variation": {"meters": 220, "amount": 0.6, "types": {"0": [0,0,1,0], "3": [0,0,0,1]}},
            "shape": [{"radiusMeters": 400, "rangeMeters": 6, "amount": 0.9, "ridge": [0,1,0,0], "from": [0]}],
            "erosion": {"talus": {"weights": [0,0,0,1], "amount": 0.5, "coverage": 0.05},
                        "channel": {"weights": [0,0,1,0], "amount": 0.5, "startHectares": 3, "fullHectares": 30, "types": [3]},
                        "deposit": {"weights": [0,0,1,0], "coverage": 0.1}, "scour": {"weights": [0,1,0,0], "coverage": 0.1}},
            "slope": {"weights": [0,1,0,0], "startDegrees": 24, "fullDegrees": 38},
            "layers": [{}, {}, {}, {}]})");
        const auto input = Synthetic();
        const auto images = TerrainLivePaint::Generate(recipe, input, 128);
        check(images.size() == 1 && images[0].size() == 128 * 128 * 4, "one 128x128 RGBA image");
        std::array<double, 4> mean{};
        for (std::size_t p = 0; p < 128 * 128; ++p)
        {
            int sum = 0;
            for (int k = 0; k < 4; ++k) { sum += images[0][p * 4 + k]; mean[std::size_t(k)] += images[0][p * 4 + k] / (128.0 * 128 * 255); }
            check(sum == 255, "every pixel sums to 255");
        }
        for (const double m : mean) check(m > 0.01, "every layer is used somewhere");
        check(images == TerrainLivePaint::Generate(recipe, input, 128), "generation is deterministic");
        // The skirt outside the file takes outsideWeights (layer 0).
        check(images[0][0] == 255, "skirt corner is the outside layer");

        auto eight = recipe;
        eight["layers"] = nlohmann::json::array({{}, {}, {}, {}, {{"edge", {{"meters", 4}}}}, {}, {}, {}});
        for (auto* key : {"outsideWeights"}) eight[key] = {1, 0, 0, 0, 0, 0, 0, 0};
        eight["typeWeights"] = {{"0", {1, 0, 0, 0, 0, 0, 0, 0}}, {"3", {0, 0, 0, 0, 1, 0, 0, 0}}};
        eight.erase("variation"); eight.erase("shape"); eight.erase("erosion"); eight.erase("slope");
        const auto pair = TerrainLivePaint::Generate(eight, input, 64);
        check(pair.size() == 2, "eight layers make two images");
        for (std::size_t p = 0; p < 64 * 64; ++p)
        {
            int sum = 0;
            for (const auto& image : pair) for (int k = 0; k < 4; ++k) sum += image[p * 4 + k];
            check(sum == 255, "eight layers normalise jointly");
        }
        bool rejected = false;
        try { auto bad = input; bad.cells.pop_back(); TerrainLivePaint::Generate(recipe, bad, 64); } catch (const std::exception&) { rejected = true; }
        check(rejected, "mismatched input accepted");
        check(TerrainLivePaint::Generator(recipe, input).UndefinedShare() == 0, "both synthetic types are mapped");
        auto unmapped = input;
        for (int x = 0; x < 64; ++x) unmapped.cells[std::size_t(x)] = uint16_t(9 << 12);
        check(std::abs(TerrainLivePaint::Generator(recipe, unmapped).UndefinedShare() - 1.0 / 64) < 1e-9, "one unmapped row is 1/64");
        std::cout << "terrain_live_paint_tests passed\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
