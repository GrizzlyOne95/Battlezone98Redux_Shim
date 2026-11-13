// Generated rally beacon materials and textures (include/rally_beacon_assets.h).
// With one argument, also exports the mesh, material and textures there for
// inspection in a modelling tool.
#include "native_chunk_mesh.h"
#include "rally_beacon_assets.h"
#include "test_check.h"
#include <filesystem>
#include <fstream>
#include <string>
using namespace BZROpenShim::RallyBeacon;
using OpenShimTest::Check;

int main(int argc, char** argv)
{
    const auto script = MaterialScript();
    Check(script.rfind(kMarker, 0) == 0, "material script starts with the generated marker");
    Check(script == MaterialScript(), "material script is deterministic");
    const auto importAt = script.find("import * from \"BZBase.material\"");
    Check(importAt != std::string::npos && importAt < script.find("material "),
          "script imports BZBase before the first material (parse-order independent)");
    for (const auto* name : {kFrameMaterial, kLampMaterial, kLampAmberMaterial})
        Check(script.find(std::string("material ") + name + " : BZBase") != std::string::npos,
              "material names match the mesh submeshes");
    for (const auto* file : kTextureFiles)
        Check(script.find(file) != std::string::npos, "every generated texture is referenced");
    Check(script.find("EmissiveMap black.dds") != std::string::npos &&
              script.find(std::string("EmissiveMap ") + kLampEmissive) != std::string::npos,
          "frame has no glow, lamp has the generated emissive");

    const auto mesh = BZROpenShim::NativeChunks::RallyBeaconMesh();
    const std::string meshData(mesh.mesh.begin(), mesh.mesh.end());
    Check(meshData.find(kFrameMaterial) != std::string::npos && meshData.find(kLampMaterial) != std::string::npos,
          "mesh submesh material names match the script");

    const auto amberMesh = BZROpenShim::NativeChunks::RallyBeaconMesh(true);
    const std::string amberData(amberMesh.mesh.begin(), amberMesh.mesh.end());
    Check(amberData.find(kLampAmberMaterial) != std::string::npos &&
              amberData.find(kFrameMaterial) != std::string::npos,
          "Factory mesh uses the frame and the amber lamp material");
    Check(meshData.find(kLampAmberMaterial) == std::string::npos &&
              amberMesh.triangles == mesh.triangles && amberMesh.mesh.size() > mesh.mesh.size() &&
              amberMesh.name != mesh.name && amberMesh.mesh == BZROpenShim::NativeChunks::RallyBeaconMesh(true).mesh,
          "Recycler mesh stays green; the amber one has the same geometry and its own deterministic name");
    Check(TextureTga(kLampAmberDiffuse) != TextureTga(kLampDiffuse) &&
              TextureTga(kLampAmberEmissive) != TextureTga(kLampEmissive),
          "amber lamp textures differ from the green ones");

    for (const auto* file : kTextureFiles)
    {
        const auto tga = TextureTga(file);
        Check(IsGeneratedTga(tga) && tga[2] == 2 && tga[16] == 24 && tga[17] == 0x20 && tga[12] == kTextureSize &&
                  tga[14] == kTextureSize,
              "marked top-left 8x8 RGB TGA");
        Check(tga.size() == 18 + tga[0] + kTextureSize * kTextureSize * 3, "texture size matches declaration");
        Check(tga == TextureTga(file), "texture is deterministic");
        if (argc == 2)
        {
            std::filesystem::create_directories(argv[1]);
            std::ofstream output(std::filesystem::path(argv[1]) / file, std::ios::binary);
            output.write(reinterpret_cast<const char*>(tga.data()), static_cast<std::streamsize>(tga.size()));
            Check(static_cast<bool>(output), "preview texture write");
        }
    }
    Check(TextureTga("other.tga").empty(), "unknown texture name yields nothing");
    Check(!IsGeneratedTga({}) && !IsGeneratedTga(std::vector<uint8_t>(64, 0)), "unmarked user textures are preserved");
    if (argc == 2)
    {
        std::ofstream output(std::filesystem::path(argv[1]) / kMaterialFile, std::ios::binary);
        output << script;
        Check(static_cast<bool>(output), "preview material write");
        std::ofstream meshOut(std::filesystem::path(argv[1]) / "openshim_rally_beacon.mesh", std::ios::binary);
        meshOut.write(reinterpret_cast<const char*>(mesh.mesh.data()), static_cast<std::streamsize>(mesh.mesh.size()));
        Check(static_cast<bool>(meshOut), "preview mesh write");
    }
}
