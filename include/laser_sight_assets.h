// laser_sight_assets.h
// BZR Open Shim - LaserSight: the generated beam texture, material script and
// SM4 shader, written into the chunk cache root next to the ShellCasings
// assets (laser_sight.cpp). Header-only so the tests check the same text the
// shim writes. See Docs/LASER_SIGHT.md.
//
// The material has two techniques, in this order:
//   0  SM4 programs (vs_4_0/ps_4_0): DX11. D3D11 has no fixed pipeline, so a
//      shaderless pass would throw on every draw.
//   1  Fixed function: DX9, where technique 0's SM4 targets are unsupported
//      and Ogre falls back to it.
// Both draw additively with depth_write off, depth_check on, no culling and no
// lighting, so the beam glows over the scene and is hidden behind terrain and
// hulls without hiding anything itself.
#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

namespace BZROpenShim::LaserSight
{
    inline constexpr const char* kMaterialName = "openshim_lasersight_beam";
    inline constexpr const char* kMaterialFile = "openshim_lasersight.material";
    inline constexpr const char* kShaderFile = "openshim_lasersight-sm4.hlsl";
    inline constexpr const char* kTextureFile = "openshim_lasersight_beam.tga";
    // First line of every generated text asset; the TGA carries kTgaMarker in
    // its image-id field. Only marked files are ever overwritten or removed.
    inline constexpr const char* kAssetMarker = "// OpenShim LaserSight generated asset";
    inline constexpr const char* kTgaMarker = "OpenShim laser sight ";
    // u runs around the tube, v along it (0 = muzzle, 1 = far end).
    inline constexpr unsigned kTextureWidth = 64, kTextureHeight = 128;

    inline uint32_t BeamNoise(uint32_t x, uint32_t y) noexcept
    {
        uint32_t value = x * 374761393u + y * 668265263u + 0x1A5E5u;
        value = (value ^ (value >> 13)) * 1274126177u;
        return value ^ (value >> 16);
    }

    // Value noise in [0, 1], wrapping every `period` cells in x so the seam
    // around the tube is invisible.
    inline float BeamSmoothNoise(float x, float y, uint32_t period) noexcept
    {
        const float fx = std::floor(x), fy = std::floor(y);
        const float tx = x - fx, ty = y - fy;
        const auto cell = [&](float cx, float cy) {
            const uint32_t ix = static_cast<uint32_t>(static_cast<int>(cx) % static_cast<int>(period) + static_cast<int>(period)) % period;
            return static_cast<float>(BeamNoise(ix, static_cast<uint32_t>(static_cast<int>(cy) + 4096)) & 1023u) / 1023.0f;
        };
        const float sx = tx * tx * (3.0f - 2.0f * tx), sy = ty * ty * (3.0f - 2.0f * ty);
        const float a = cell(fx, fy) + (cell(fx + 1, fy) - cell(fx, fy)) * sx;
        const float b = cell(fx, fy + 1) + (cell(fx + 1, fy + 1) - cell(fx, fy + 1)) * sx;
        return a + (b - a) * sy;
    }

    // Cone-smoke style: soft streaks of red haze running along the beam,
    // brightest at the muzzle and thinning towards the far end. RGB only; the
    // material adds it, so black is transparent.
    inline std::vector<uint8_t> BeamRgb()
    {
        std::vector<uint8_t> pixels(kTextureWidth * kTextureHeight * 3);
        for (unsigned y = 0; y < kTextureHeight; ++y)
            for (unsigned x = 0; x < kTextureWidth; ++x)
            {
                const float u = static_cast<float>(x) / kTextureWidth;
                const float v = static_cast<float>(y) / (kTextureHeight - 1);
                const float wisps = 0.55f * BeamSmoothNoise(u * 8.0f, v * 6.0f, 8u) +
                                    0.30f * BeamSmoothNoise(u * 16.0f, v * 14.0f, 16u) + 0.15f;
                const float fade = 0.3f + 0.7f * std::pow(1.0f - v, 1.5f);
                const float i = std::clamp(wisps * fade, 0.0f, 1.0f);
                const size_t at = (static_cast<size_t>(y) * kTextureWidth + x) * 3;
                pixels[at] = static_cast<uint8_t>(std::clamp(i * 1.0f, 0.0f, 1.0f) * 255);
                pixels[at + 1] = static_cast<uint8_t>(std::clamp(i * 0.16f, 0.0f, 1.0f) * 255);
                pixels[at + 2] = static_cast<uint8_t>(std::clamp(i * 0.10f, 0.0f, 1.0f) * 255);
            }
        return pixels;
    }

    inline std::vector<uint8_t> BeamTga()
    {
        const std::string id = std::string(kTgaMarker) + "v1";
        // Uncompressed 24-bit, top-left origin (row 0 = v 0). Both Ogre
        // renderers load TGA.
        std::vector<uint8_t> out(18, 0);
        out[0] = static_cast<uint8_t>(id.size());
        out[2] = 2;
        out[12] = kTextureWidth & 255;
        out[13] = kTextureWidth >> 8;
        out[14] = kTextureHeight & 255;
        out[15] = kTextureHeight >> 8;
        out[16] = 24;
        out[17] = 0x20;
        out.insert(out.end(), id.begin(), id.end());
        const auto rgb = BeamRgb();
        for (size_t i = 0; i < rgb.size(); i += 3)
        {
            out.push_back(rgb[i + 2]);
            out.push_back(rgb[i + 1]);
            out.push_back(rgb[i]);
        }
        return out;
    }

    inline bool IsGeneratedTga(const std::vector<uint8_t>& bytes)
    {
        const std::string marker(kTgaMarker);
        return bytes.size() >= 18 + marker.size() && bytes[0] >= marker.size() &&
               std::equal(marker.begin(), marker.end(), bytes.begin() + 18);
    }

    inline bool IsGeneratedText(const std::string& text)
    {
        return text.rfind(kAssetMarker, 0) == 0;
    }

    // SM4 only; DX9 never compiles it (technique 1 is its path). Matrix
    // convention as openshim_dx11_fixedfunc-sm4.hlsl: mul(matrix, vector).
    inline std::string ShaderSource()
    {
        return std::string(kAssetMarker) + " v1: LaserSight beam, SM4 (generated; do not edit).\n"
            "void lasersight_vertex(\n"
            "    in float4 iPosition : POSITION,\n"
            "    in float3 iNormal : NORMAL,\n"
            "    in float2 iTexCoord : TEXCOORD0,\n"
            "    uniform float4x4 wvpMat,\n"
            "    uniform float4x4 worldMat,\n"
            "    uniform float4 cameraPosition,\n"
            "    out float2 vTexCoord : TEXCOORD0,\n"
            "    out float2 vFacingDepth : TEXCOORD1,\n"
            "    out float4 oPosition : SV_POSITION)\n"
            "{\n"
            "    oPosition = mul(wvpMat, iPosition);\n"
            "    float3 worldPos = mul(worldMat, iPosition).xyz;\n"
            "    // Radial part of the normal only: the node scales the tube by its\n"
            "    // radius across and its length along, so a full normal transform\n"
            "    // would tip it along the beam.\n"
            "    float3 radial = mul((float3x3)worldMat, float3(iNormal.xy, 0.0));\n"
            "    float3 toEye = cameraPosition.xyz - worldPos;\n"
            "    float lr = length(radial);\n"
            "    float le = length(toEye);\n"
            "    float facing = (lr > 1e-6 && le > 1e-6) ? abs(dot(radial / lr, toEye / le)) : 1.0;\n"
            "    vTexCoord = iTexCoord;\n"
            "    vFacingDepth = float2(facing, oPosition.z);\n"
            "}\n"
            "\n"
            "void lasersight_fragment(\n"
            "    uniform Texture2D beamMap : register(t0),\n"
            "    uniform SamplerState beamSam : register(s0),\n"
            "    uniform float4 fogParams,\n"
            "    in float2 vTexCoord : TEXCOORD0,\n"
            "    in float2 vFacingDepth : TEXCOORD1,\n"
            "    out float4 oColor : SV_TARGET)\n"
            "{\n"
            "    float3 colour = beamMap.Sample(beamSam, vTexCoord).rgb;\n"
            "    // Soft edges: the tube's silhouette fades out, the core stays bright.\n"
            "    colour *= vFacingDepth.x * vFacingDepth.x;\n"
            "    // Additive: fog fades the beam out instead of tinting it.\n"
            "    float fog = fogParams.w > 0.0 ? saturate((vFacingDepth.y - fogParams.y) * fogParams.w) : 0.0;\n"
            "    oColor = float4(colour * (1.0 - fog), 1.0);\n"
            "}\n";
    }

    inline std::string MaterialScript()
    {
        const std::string states =
            "            lighting off\n"
            "            scene_blend add\n"
            "            depth_write off\n"
            "            depth_check on\n"
            "            cull_hardware none\n"
            "            cull_software none\n";
        const std::string texture = std::string(
            "            texture_unit\n"
            "            {\n"
            "                texture ") + kTextureFile + "\n"
            "                tex_address_mode wrap clamp\n"
            "                filtering trilinear\n"
            "            }\n";
        return std::string(kAssetMarker) + " v1: LaserSight beam material (generated; do not edit).\n"
            "vertex_program openshim_lasersight_vs hlsl\n"
            "{\n"
            "    source " + kShaderFile + "\n"
            "    target vs_4_0\n"
            "    entry_point lasersight_vertex\n"
            "    default_params\n"
            "    {\n"
            "        param_named_auto wvpMat worldviewproj_matrix\n"
            "        param_named_auto worldMat world_matrix\n"
            "        param_named_auto cameraPosition camera_position\n"
            "    }\n"
            "}\n"
            "\n"
            "fragment_program openshim_lasersight_ps hlsl\n"
            "{\n"
            "    source " + kShaderFile + "\n"
            "    target ps_4_0\n"
            "    entry_point lasersight_fragment\n"
            "    default_params\n"
            "    {\n"
            "        param_named_auto fogParams fog_params\n"
            "    }\n"
            "}\n"
            "\n"
            "material " + kMaterialName + "\n"
            "{\n"
            "    receive_shadows off\n"
            "    // 0: DX11 (SM4 programs).\n"
            "    technique\n"
            "    {\n"
            "        pass\n"
            "        {\n" + states +
            "            vertex_program_ref openshim_lasersight_vs\n"
            "            {\n"
            "            }\n"
            "            fragment_program_ref openshim_lasersight_ps\n"
            "            {\n"
            "            }\n" + texture +
            "        }\n"
            "    }\n"
            "    // 1: DX9 fixed function (technique 0's SM4 targets are unsupported there).\n"
            "    technique\n"
            "    {\n"
            "        pass\n"
            "        {\n" + states +
            "            fog_override true none\n" + texture +
            "        }\n"
            "    }\n"
            "}\n";
    }
}
