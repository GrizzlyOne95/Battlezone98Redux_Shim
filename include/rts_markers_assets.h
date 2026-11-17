// rts_markers_assets.h
// BZR Open Shim - RTS markers: the generated ring material and its SM4
// shader, written into the chunk cache root next to the LaserSight assets
// (rts_markers.cpp). Header-only so the tests check the same text the shim
// writes. See Docs/RTS_MARKERS.md.
//
// The rings are ManualObjects carrying position and a per-vertex colour with
// alpha; there is no texture. The material has two techniques, in this order:
//   0  SM4 programs (vs_4_0/ps_4_0): DX11. D3D11 has no fixed pipeline, so a
//      shaderless pass would throw on every draw.
//   1  Fixed function: DX9, where technique 0's SM4 targets are unsupported
//      and Ogre falls back to it. With lighting off, D3D9 takes the vertex
//      colour (and its alpha) as the diffuse colour.
// Both alpha-blend with depth_write off, depth_check on, no culling, no
// lighting and no fog, so a ring is hidden behind hulls and hills but never
// hides anything itself, and reads the same in the cockpit and from the
// satellite view.
#pragma once

#include "rts_placement_policy.h"

#include <algorithm>
#include <cstdio>
#include <string>

namespace BZROpenShim
{
    namespace RtsMarkers
    {
        constexpr const char* kMaterialName = "openshim_rtsmarker_ring";
        constexpr const char* kMaterialFile = "openshim_rtsmarker.material";
        constexpr const char* kShaderFile = "openshim_rtsmarker-sm4.hlsl";
        // First line of every generated asset. Only marked files are ever
        // overwritten or removed.
        constexpr const char* kAssetMarker = "// OpenShim RtsMarkers generated asset";

        inline bool IsGeneratedText(const std::string& text)
        {
            return text.rfind(kAssetMarker, 0) == 0;
        }

        // SM4 only; DX9 never compiles it (technique 1 is its path). Matrix
        // convention as openshim_dx11_fixedfunc-sm4.hlsl: mul(matrix, vector).
        inline std::string ShaderSource()
        {
            return std::string(kAssetMarker) + " v1: RTS marker ring, SM4 (generated; do not edit).\n"
                "void rtsmarker_vertex(\n"
                "    in float4 iPosition : POSITION,\n"
                "    in float4 iColour : COLOR0,\n"
                "    uniform float4x4 wvpMat,\n"
                "    out float4 vColour : COLOR0,\n"
                "    out float4 oPosition : SV_POSITION)\n"
                "{\n"
                "    oPosition = mul(wvpMat, iPosition);\n"
                "    vColour = iColour;\n"
                "}\n"
                "\n"
                "void rtsmarker_fragment(\n"
                "    in float4 vColour : COLOR0,\n"
                "    out float4 oColor : SV_TARGET)\n"
                "{\n"
                "    oColor = vColour;\n"
                "}\n";
        }

        inline std::string MaterialScript()
        {
            const std::string states =
                "            lighting off\n"
                "            scene_blend alpha_blend\n"
                "            depth_write off\n"
                "            depth_check on\n"
                "            cull_hardware none\n"
                "            cull_software none\n";
            return std::string(kAssetMarker) + " v1: RTS marker ring material (generated; do not edit).\n"
                "vertex_program openshim_rtsmarker_vs hlsl\n"
                "{\n"
                "    source " + kShaderFile + "\n"
                "    target vs_4_0\n"
                "    entry_point rtsmarker_vertex\n"
                "    default_params\n"
                "    {\n"
                "        param_named_auto wvpMat worldviewproj_matrix\n"
                "    }\n"
                "}\n"
                "\n"
                "fragment_program openshim_rtsmarker_ps hlsl\n"
                "{\n"
                "    source " + kShaderFile + "\n"
                "    target ps_4_0\n"
                "    entry_point rtsmarker_fragment\n"
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
                "            vertex_program_ref openshim_rtsmarker_vs\n"
                "            {\n"
                "            }\n"
                "            fragment_program_ref openshim_rtsmarker_ps\n"
                "            {\n"
                "            }\n"
                "        }\n"
                "    }\n"
                "    // 1: DX9 fixed function (technique 0's SM4 targets are unsupported there).\n"
                "    technique\n"
                "    {\n"
                "        pass\n"
                "        {\n" + states +
                "            fog_override true none\n"
                "        }\n"
                "    }\n"
                "}\n";
        }

        // ---- Build ghost (rts_placement.cpp) ---------------------------------
        // A see-through copy of a building's own mesh. The mesh carries no
        // vertex colour, so the tint is a per-material constant: four
        // materials (valid / no power / blocked / nav), set on the ghost
        // entity with Entity::setMaterialName (the mesh's own materials are
        // never touched). Techniques, in this order:
        //   0  SM4 programs: DX11. The pixel shader returns the material's
        //      `tint` constant, brightened slightly (the glow).
        //   1  Fixed function: DX9. D3D9 has no constant-colour stage without
        //      a texture, so this pass keeps lighting on with ambient,
        //      diffuse and specular black: the colour is the emissive term
        //      alone (the same glow) and the alpha is the diffuse alpha, so
        //      no scene light changes it.
        // Both alpha-blend with depth_write off, depth_check on, back faces
        // culled (a closed hull reads cleaner) and no fog.
        constexpr const char* kGhostMaterialFile = "openshim_rtsghost.material";
        constexpr const char* kGhostShaderFile = "openshim_rtsghost-sm4.hlsl";
        constexpr float kGhostGlowScale = 1.15f;
        constexpr float kGhostGlowLift = 0.05f;

        struct GhostTint
        {
            const char* material;
            float r, g, b, a;
        };

        // Valid green, no-power yellow, blocked red (the stock quad's
        // ground.G / .Y / .R), and the nav ghost's neutral blue-white.
        constexpr GhostTint kGhostTints[] = {
            {RtsPlacement::kGhostMaterialValid, 0.30f, 1.00f, 0.40f, 0.38f},
            {RtsPlacement::kGhostMaterialNoPower, 1.00f, 0.85f, 0.20f, 0.38f},
            {RtsPlacement::kGhostMaterialBlocked, 1.00f, 0.25f, 0.20f, 0.38f},
            {RtsPlacement::kGhostMaterialNeutral, 0.70f, 0.85f, 1.00f, 0.32f},
        };

        // The colour both techniques end up drawing: the tint, lifted.
        inline float GhostGlow(float channel)
        {
            return std::min(1.0f, channel * kGhostGlowScale + kGhostGlowLift);
        }

        inline std::string GhostShaderSource()
        {
            return std::string(kAssetMarker) + " v1: RTS build ghost, SM4 (generated; do not edit).\n"
                "void rtsghost_vertex(\n"
                "    in float4 iPosition : POSITION,\n"
                "    uniform float4x4 wvpMat,\n"
                "    out float4 oPosition : SV_POSITION)\n"
                "{\n"
                "    oPosition = mul(wvpMat, iPosition);\n"
                "}\n"
                "\n"
                "void rtsghost_fragment(\n"
                "    uniform float4 tint,\n"
                "    out float4 oColor : SV_TARGET)\n"
                "{\n"
                "    oColor = float4(saturate(tint.rgb * 1.15 + 0.05), tint.a);\n"
                "}\n";
        }

        inline std::string GhostMaterialScript()
        {
            const auto number = [](float value) {
                char buffer[32] = {};
                std::snprintf(buffer, sizeof(buffer), "%.3f", value);
                return std::string(buffer);
            };
            const std::string states =
                "            scene_blend alpha_blend\n"
                "            depth_write off\n"
                "            depth_check on\n";
            std::string out = std::string(kAssetMarker) + " v1: RTS build ghost materials (generated; do not edit).\n"
                "vertex_program openshim_rtsghost_vs hlsl\n"
                "{\n"
                "    source " + kGhostShaderFile + "\n"
                "    target vs_4_0\n"
                "    entry_point rtsghost_vertex\n"
                "    default_params\n"
                "    {\n"
                "        param_named_auto wvpMat worldviewproj_matrix\n"
                "    }\n"
                "}\n"
                "\n"
                "fragment_program openshim_rtsghost_ps hlsl\n"
                "{\n"
                "    source " + kGhostShaderFile + "\n"
                "    target ps_4_0\n"
                "    entry_point rtsghost_fragment\n"
                "}\n";
            for (const GhostTint& tint : kGhostTints)
            {
                const std::string rgba =
                    number(tint.r) + " " + number(tint.g) + " " + number(tint.b) + " " + number(tint.a);
                const std::string glow =
                    number(GhostGlow(tint.r)) + " " + number(GhostGlow(tint.g)) + " " + number(GhostGlow(tint.b));
                out += "\n"
                    "material " + std::string(tint.material) + "\n"
                    "{\n"
                    "    receive_shadows off\n"
                    "    // 0: DX11 (SM4 programs).\n"
                    "    technique\n"
                    "    {\n"
                    "        pass\n"
                    "        {\n"
                    "            lighting off\n" + states +
                    "            vertex_program_ref openshim_rtsghost_vs\n"
                    "            {\n"
                    "            }\n"
                    "            fragment_program_ref openshim_rtsghost_ps\n"
                    "            {\n"
                    "                param_named tint float4 " + rgba + "\n"
                    "            }\n"
                    "        }\n"
                    "    }\n"
                    "    // 1: DX9 fixed function: emissive colour, diffuse alpha, nothing lit.\n"
                    "    technique\n"
                    "    {\n"
                    "        pass\n"
                    "        {\n"
                    "            lighting on\n"
                    "            ambient 0 0 0 1\n"
                    "            diffuse 0 0 0 " + number(tint.a) + "\n"
                    "            specular 0 0 0 1 0\n"
                    "            emissive " + glow + " 1\n" + states +
                    "            fog_override true none\n"
                    "        }\n"
                    "    }\n"
                    "}\n";
            }
            return out;
        }
    }
}
