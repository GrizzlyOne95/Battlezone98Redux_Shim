#pragma once
// Producer rally beacon: generated materials and textures (the mesh is
// NativeChunks::RallyBeaconMesh). Same rules as shell_casing_finish.h: the
// first line of the material and the TGA id field carry a marker, and only
// marked files are ever upgraded or removed; unmarked files belong to the user.
#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

namespace BZROpenShim::RallyBeacon
{
    inline constexpr const char* kMarker = "// OpenShim ProducerRallyPoints beacon materials";
    inline constexpr const char* kTgaMarker = "OpenShim rally beacon ";
    inline constexpr const char* kMaterialFile = "openshim_rally_beacon.material";
    inline constexpr const char* kFrameMaterial = "openshim_rally_beacon_frame";
    inline constexpr const char* kLampMaterial = "openshim_rally_beacon_lamp";
    inline constexpr const char* kFrameDiffuse = "openshim_rally_beacon_frame_d.tga";
    inline constexpr const char* kFrameSpecular = "openshim_rally_beacon_frame_s.tga";
    inline constexpr const char* kLampDiffuse = "openshim_rally_beacon_lamp_d.tga";
    inline constexpr const char* kLampSpecular = "openshim_rally_beacon_lamp_s.tga";
    inline constexpr const char* kLampEmissive = "openshim_rally_beacon_lamp_e.tga";
    // Factory variant: amber lamp, same frame and specular.
    inline constexpr const char* kLampAmberMaterial = "openshim_rally_beacon_lamp_fac";
    inline constexpr const char* kLampAmberDiffuse = "openshim_rally_beacon_lamp_fac_d.tga";
    inline constexpr const char* kLampAmberEmissive = "openshim_rally_beacon_lamp_fac_e.tga";
    inline constexpr unsigned kTextureSize = 8;

    inline constexpr const char* kTextureFiles[] = {kFrameDiffuse, kFrameSpecular, kLampDiffuse,
                                                    kLampSpecular, kLampEmissive,
                                                    kLampAmberDiffuse, kLampAmberEmissive};

    // 8x8, 24-bit top-left TGA. The mesh maps v = y / 6, so a vertical
    // gradient from `bottom` (row 0, ground) to `top` shades the beacon.
    inline std::vector<uint8_t> Tga(const float bottom[3], const float top[3])
    {
        const std::string id = std::string(kTgaMarker) + "v1";
        std::vector<uint8_t> out(18, 0);
        out[0] = static_cast<uint8_t>(id.size()); out[2] = 2;
        out[12] = kTextureSize; out[14] = kTextureSize;
        out[16] = 24; out[17] = 0x20;
        out.insert(out.end(), id.begin(), id.end());
        for (unsigned y = 0; y < kTextureSize; ++y)
        {
            const float t = static_cast<float>(y) / (kTextureSize - 1);
            uint8_t bgr[3];
            for (int c = 0; c < 3; ++c)
                bgr[2 - c] = static_cast<uint8_t>(std::clamp(bottom[c] + (top[c] - bottom[c]) * t, 0.0f, 1.0f) * 255.0f + 0.5f);
            for (unsigned x = 0; x < kTextureSize; ++x)
                out.insert(out.end(), bgr, bgr + 3);
        }
        return out;
    }

    // `file` is one of kTextureFiles; empty for any other name.
    inline std::vector<uint8_t> TextureTga(const std::string& file)
    {
        if (file == kFrameDiffuse)
        {   // dark gunmetal, a touch lighter towards the top
            const float lo[3] = {0.16f, 0.18f, 0.21f}, hi[3] = {0.30f, 0.33f, 0.38f};
            return Tga(lo, hi);
        }
        if (file == kFrameSpecular)
        {
            const float lo[3] = {0.45f, 0.47f, 0.52f}, hi[3] = {0.60f, 0.62f, 0.68f};
            return Tga(lo, hi);
        }
        if (file == kLampDiffuse)
        {
            const float lo[3] = {0.20f, 0.90f, 0.38f}, hi[3] = {0.35f, 1.00f, 0.55f};
            return Tga(lo, hi);
        }
        if (file == kLampSpecular)
        {
            const float lo[3] = {0.60f, 0.60f, 0.60f}, hi[3] = {0.60f, 0.60f, 0.60f};
            return Tga(lo, hi);
        }
        if (file == kLampEmissive)
        {   // bright nav green so the beacon blooms
            const float lo[3] = {0.20f, 1.00f, 0.40f}, hi[3] = {0.20f, 1.00f, 0.40f};
            return Tga(lo, hi);
        }
        if (file == kLampAmberDiffuse)
        {
            const float lo[3] = {0.90f, 0.55f, 0.08f}, hi[3] = {1.00f, 0.72f, 0.20f};
            return Tga(lo, hi);
        }
        if (file == kLampAmberEmissive)
        {   // amber, same strength as the green lamp's glow
            const float lo[3] = {1.00f, 0.60f, 0.05f}, hi[3] = {1.00f, 0.60f, 0.05f};
            return Tga(lo, hi);
        }
        return {};
    }

    inline bool IsGeneratedTga(const std::vector<uint8_t>& bytes)
    {
        const std::string marker(kTgaMarker);
        return bytes.size() >= 18 + marker.size() && bytes[0] >= marker.size() &&
            std::equal(marker.begin(), marker.end(), bytes.begin() + 18);
    }

    inline std::string MaterialScript()
    {
        std::string script = std::string(kMarker) + " v3 (generated; do not edit).\n"
            // Without this import the script only compiles when it is parsed
            // after BZBase.material; resource-group init parses an existing
            // file first and every material fails. Same as the gib scripts.
            "import * from \"BZBase.material\"\n\n";
        const struct { const char* name; const char* diffuse; const char* specular; const char* emissive; } materials[] = {
            {kFrameMaterial, kFrameDiffuse, kFrameSpecular, "black.dds"},
            {kLampMaterial, kLampDiffuse, kLampSpecular, kLampEmissive},
            {kLampAmberMaterial, kLampAmberDiffuse, kLampSpecular, kLampAmberEmissive}};
        for (const auto& m : materials)
            script += std::string("material ") + m.name + " : BZBase\n{\n"
                "    set_texture_alias DiffuseMap " + m.diffuse + "\n"
                "    set_texture_alias SpecularMap " + m.specular + "\n"
                "    set_texture_alias EmissiveMap " + m.emissive + "\n"
                "    set $diffuse \"1 1 1\"\n    set $ambient \"1 1 1\"\n"
                "    set $specular \"1 1 1\"\n    set $shininess \"32\"\n"
                "    set $bias \"0\"\n}\n";
        return script;
    }
}
