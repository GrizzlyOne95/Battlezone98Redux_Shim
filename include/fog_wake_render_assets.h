// fog_wake_render_assets.h
// BZR Open Shim - InteractiveFogWakes render spike: the generated SM4 shader
// and material for the stacked ground-fog layers (fog_wake_render.cpp),
// written into the chunk cache root next to the RtsMarkers assets.
// Header-only so the tests check the same text the shim writes. See
// Docs/INTERACTIVE_FOG_WAKES.md, "Render spike".
//
// One technique: SM4 (vs_4_0/ps_4_0), DX11 only. The layers are never
// created under DX9 (the clearance texture upload is a D3D11 call), so the
// material is parsed there but never loaded.
//
// Vertex layout (ManualObject): position (bank-local, render space), one 2D
// texture coordinate (bank uv: u = sim x, v = sim z, 0..1 across the bank)
// and a colour whose alpha carries the layer fraction (0 = lowest layer).
#pragma once

#include <string>

namespace BZROpenShim::FogWakeRender
{
    inline constexpr const char* kMaterialName = "openshim_fogwake_layer";
    inline constexpr const char* kMaterialFile = "openshim_fogwake.material";
    inline constexpr const char* kShaderFile = "openshim_fogwake-sm4.hlsl";
    // The clearance grid, uploaded each simulation tick (fog_wake_render.cpp).
    inline constexpr const char* kTextureName = "OpenShim/FogWake/Clearance";
    // First line of every generated text asset. Only marked files are ever
    // overwritten or removed.
    inline constexpr const char* kAssetMarker = "// OpenShim FogWake generated asset";

    // Bank side in metres; the shader turns uv into bank-local metres for the
    // noise. Must match fog_wake_feature.cpp (256 cells of 2 m).
    inline constexpr float kBankMetres = 512.0f;

    inline bool IsGeneratedText(const std::string& text)
    {
        return text.rfind(kAssetMarker, 0) == 0;
    }

    // Matrix convention as openshim_dx11_fixedfunc-sm4.hlsl: mul(matrix, vector).
    inline std::string ShaderSource()
    {
        return std::string(kAssetMarker) + " v1: FogWake ground fog layers, SM4 (generated; do not edit).\n"
            "void fogwake_vertex(\n"
            "    in float4 iPosition : POSITION,\n"
            "    in float4 iColour : COLOR0,\n"
            "    in float2 iTexCoord : TEXCOORD0,\n"
            "    uniform float4x4 wvpMat,\n"
            "    uniform float4x4 worldMat,\n"
            "    out float3 vBank : TEXCOORD0,\n"
            "    out float4 vWorldDepth : TEXCOORD1,\n"
            "    out float4 oPosition : SV_POSITION)\n"
            "{\n"
            "    oPosition = mul(wvpMat, iPosition);\n"
            "    vBank = float3(iTexCoord, iColour.a);\n"
            "    vWorldDepth = float4(mul(worldMat, iPosition).xyz, oPosition.z);\n"
            "}\n"
            "\n"
            "float fogwake_hash(float2 p)\n"
            "{\n"
            "    p = frac(p * float2(0.1031, 0.1030));\n"
            "    p += dot(p, p.yx + 33.33);\n"
            "    return frac((p.x + p.y) * p.x);\n"
            "}\n"
            "\n"
            "float fogwake_noise(float2 p)\n"
            "{\n"
            "    float2 i = floor(p);\n"
            "    float2 f = frac(p);\n"
            "    float2 u = f * f * (3.0 - 2.0 * f);\n"
            "    return lerp(lerp(fogwake_hash(i), fogwake_hash(i + float2(1, 0)), u.x),\n"
            "                lerp(fogwake_hash(i + float2(0, 1)), fogwake_hash(i + float2(1, 1)), u.x), u.y);\n"
            "}\n"
            "\n"
            "void fogwake_fragment(\n"
            "    uniform Texture2D clearanceMap : register(t0),\n"
            "    uniform SamplerState clearanceSam : register(s0),\n"
            "    uniform float4 cameraPosition,\n"
            "    uniform float4 fogParams,\n"
            "    uniform float time,\n"
            "    in float3 vBank : TEXCOORD0,\n"
            "    in float4 vWorldDepth : TEXCOORD1,\n"
            "    out float4 oColor : SV_TARGET)\n"
            "{\n"
            "    float clearance = clearanceMap.Sample(clearanceSam, vBank.xy).r;\n"
            "    float layer = vBank.z;\n"
            "    // Two octaves of value noise drifting over bank-local metres; each\n"
            "    // layer is offset so the stack does not line up.\n"
            "    float2 m = vBank.xy * " + std::to_string(kBankMetres) + ";\n"
            "    float n = 0.6 * fogwake_noise(m / 14.0 + time * float2(0.05, 0.02) + layer * 7.3)\n"
            "            + 0.4 * fogwake_noise(m / 5.0 - time * float2(0.03, 0.06) + layer * 3.1);\n"
            "    float mask = saturate(n * 1.4 - 0.15);\n"
            "    // Denser near the ground.\n"
            "    float density = 0.16 * (1.0 - clearance) * mask * lerp(1.0, 0.5, layer);\n"
            "    // A thin slab: the path through it grows as the view grazes it.\n"
            "    float3 toEye = cameraPosition.xyz - vWorldDepth.xyz;\n"
            "    float dist = length(toEye);\n"
            "    float grazing = dist > 1e-3 ? abs(toEye.y) / dist : 1.0;\n"
            "    float path = min(1.0 / max(grazing, 0.1), 6.0);\n"
            "    float alpha = 1.0 - exp(-density * path);\n"
            "    // Fade out at the bank edges, right in front of the camera and\n"
            "    // where the stock distance fog takes over.\n"
            "    float2 edge = min(vBank.xy, 1.0 - vBank.xy);\n"
            "    alpha *= smoothstep(0.0, 0.08, min(edge.x, edge.y));\n"
            "    alpha *= smoothstep(1.5, 8.0, dist);\n"
            "    float stockFog = fogParams.w > 0.0 ? saturate((vWorldDepth.w - fogParams.y) * fogParams.w) : 0.0;\n"
            "    alpha *= 1.0 - stockFog;\n"
            "    oColor = float4(0.72, 0.76, 0.80, alpha);\n"
            "}\n";
    }

    inline std::string MaterialScript()
    {
        return std::string(kAssetMarker) + " v1: FogWake ground fog layer material (generated; do not edit).\n"
            "vertex_program openshim_fogwake_vs hlsl\n"
            "{\n"
            "    source " + kShaderFile + "\n"
            "    target vs_4_0\n"
            "    entry_point fogwake_vertex\n"
            "    default_params\n"
            "    {\n"
            "        param_named_auto wvpMat worldviewproj_matrix\n"
            "        param_named_auto worldMat world_matrix\n"
            "    }\n"
            "}\n"
            "\n"
            "fragment_program openshim_fogwake_ps hlsl\n"
            "{\n"
            "    source " + kShaderFile + "\n"
            "    target ps_4_0\n"
            "    entry_point fogwake_fragment\n"
            "    default_params\n"
            "    {\n"
            "        param_named_auto cameraPosition camera_position\n"
            "        param_named_auto fogParams fog_params\n"
            "        param_named_auto time time_0_x 3600\n"
            "    }\n"
            "}\n"
            "\n"
            "material " + kMaterialName + "\n"
            "{\n"
            "    receive_shadows off\n"
            "    // DX11 only (SM4 programs); never loaded under DX9.\n"
            "    technique\n"
            "    {\n"
            "        pass\n"
            "        {\n"
            "            lighting off\n"
            "            scene_blend alpha_blend\n"
            "            depth_write off\n"
            "            depth_check on\n"
            "            cull_hardware none\n"
            "            cull_software none\n"
            "            vertex_program_ref openshim_fogwake_vs\n"
            "            {\n"
            "            }\n"
            "            fragment_program_ref openshim_fogwake_ps\n"
            "            {\n"
            "            }\n"
            "            texture_unit\n"
            "            {\n"
            "                texture " + kTextureName + "\n"
            "                tex_address_mode clamp\n"
            "                filtering bilinear\n"
            "            }\n"
            "        }\n"
            "    }\n"
            "}\n";
    }
}
