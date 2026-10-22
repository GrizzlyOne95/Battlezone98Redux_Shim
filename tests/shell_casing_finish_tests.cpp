#include "shell_casing_finish.h"
#include "test_check.h"
#include <filesystem>
#include <fstream>
#include <set>
using namespace BZROpenShim::ShellCasings;
using OpenShimTest::Check;

int main(int argc, char** argv)
{
    const auto diffuse = FinishRgb(false), specular = FinishRgb(true);
    Check(diffuse.size() == kFinishWidth * kFinishHeight * 3, "bounded RGB image");
    Check(diffuse == FinishRgb(false) && specular == FinishRgb(true), "deterministic finish");
    std::set<int> colours;
    for (size_t i = 0; i < diffuse.size(); i += 3)
        colours.insert((diffuse[i] << 16) | (diffuse[i + 1] << 8) | diffuse[i + 2]);
    Check(colours.size() > 300, "surface variation replaces flat colour");
    const auto at = [](unsigned y, unsigned x = 128) { return (y * kFinishWidth + x) * 3; };
    Check(diffuse[at(35)] > diffuse[at(35) + 2] * 3, "warm brass body");
    Check(diffuse[at(80)] > diffuse[at(35)], "machined rim brighter than body");
    Check(diffuse[at(97)] < 20 && specular[at(97)] < 15, "soot stays dark without shiny plastic");
    Check(diffuse[at(115) + 2] > diffuse[at(35) + 2] * 2, "primer has a distinct pale alloy");
    Check(specular[at(58)] < specular[at(35)], "annealed neck is less polished");
    const auto script = FinishMaterialScript();
    Check(script.find(" : BZBase") != std::string::npos && script.find("SpecularMap") != std::string::npos,
        "DX9/DX11 stock shader and textured moving highlights");
    Check(script.find("EmissiveMap") == std::string::npos && script.find("scene_blend") == std::string::npos,
        "no emission or overlay passes");
    for (bool spec : {false, true})
    {
        const auto tga = FinishTga(spec);
        Check(IsGeneratedFinishTga(tga) && tga[2] == 2 && tga[16] == 24 && tga[17] == 0x20,
            "marked top-left RGB TGA");
        Check(tga.size() == 18 + tga[0] + diffuse.size(), "texture size matches declaration");
        const auto rgb = spec ? specular : diffuse;
        const size_t offset = 18 + tga[0];
        Check(tga[offset] == rgb[2] && tga[offset + 2] == rgb[0], "TGA BGR byte order");
        if (argc == 2)
        {
            std::filesystem::create_directories(argv[1]);
            std::ofstream output(std::filesystem::path(argv[1]) / (spec ? kFinishSpecular : kFinishDiffuse), std::ios::binary);
            output.write(reinterpret_cast<const char*>(tga.data()), static_cast<std::streamsize>(tga.size()));
            Check(static_cast<bool>(output), "preview texture write");
        }
    }
    Check(!IsGeneratedFinishTga({}) && !IsGeneratedFinishTga(std::vector<uint8_t>(64, 0)),
        "unmarked user textures are preserved");
    if (argc == 2)
    {
        std::ofstream output(std::filesystem::path(argv[1]) / "openshim_casing.material", std::ios::binary);
        output << script;
        Check(static_cast<bool>(output), "preview material write");
    }
}
