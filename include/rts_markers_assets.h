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
    }
}
