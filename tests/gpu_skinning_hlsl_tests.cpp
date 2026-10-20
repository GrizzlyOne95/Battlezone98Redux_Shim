#include "gpu_skinning_hlsl.h"
#include "test_check.h"

#include <string>

using OpenShimTest::Check;
using namespace BZROpenShim::GpuSkinning;

namespace
{
    bool Contains(const std::string& text, const std::string& needle)
    {
        return text.find(needle) != std::string::npos;
    }

    size_t CountOf(const std::string& text, const std::string& needle)
    {
        size_t count = 0;
        for (size_t pos = text.find(needle); pos != std::string::npos; pos = text.find(needle, pos + 1))
            ++count;
        return count;
    }

    // Shaped like the stock unified craft vertex entry: uniforms first,
    // optional inputs under preprocessor conditionals, outputs after inputs.
    const char* kBaseLike =
        "// base_vertex(...) in a comment must not count\n"
        "void base_vertex(\n"
        "\tuniform float4x4 wvpMat,\n"
        "\tuniform float4x4 worldViewMat,\n"
        "#if SHADOWRECEIVER\n"
        "\tuniform float4x4 texWorldViewProj1,\n"
        "#endif\n"
        "\tin float4 iPosition : POSITION,\n"
        "\tin float2 iTexCoord : TEXCOORD0,\n"
        "\tin float3 iNormal : NORMAL,\n"
        "#if NORMALMAP_ENABLED && VERTEX_TANGENTS\n"
        "\tin float3 iTangent : TANGENT,\n"
        "#endif\n"
        "\tout float4 oPosition : SV_POSITION,\n"
        "\tout float3 vViewNormal : TEXCOORD1)\n"
        "{\n"
        "\toPosition = mul(wvpMat, iPosition);\n"
        "\tvViewNormal = mul(worldViewMat, float4(iNormal.xyz, 0)).xyz;\n"
        "}\n";

    const char* kTexturedLike =
        "void textured_vertex(uniform float4x4 wvpMat, in float4 iPosition : POSITION,\n"
        "                     in float2 iTexCoord : TEXCOORD0, out float4 oPosition : SV_POSITION)\n"
        "{ oPosition = mul(wvpMat, iPosition); }\n";
}

int main()
{
    {
        const SkinnedSourceResult r = MakeSkinnedVertexSource(kBaseLike, "base_vertex", 3, 64);
        Check(r.ok, "base-like entry transforms");
        Check(r.positionParam == "iPosition" && r.normalParam == "iNormal", "finds POSITION and NORMAL inputs");
        Check(Contains(r.source, "uniform float4 osGpuSkinBones[192]"), "palette holds three rows per bone");
        Check(Contains(r.source, "in uint4 osGpuSkinIndices : BLENDINDICES"), "adds blend index input");
        Check(Contains(r.source, "in float4 osGpuSkinWeights : BLENDWEIGHT"), "adds blend weight input");
        Check(Contains(r.source, "osGpuSkinIndices.z") && !Contains(r.source, "osGpuSkinIndices.w"),
              "unrolls exactly the requested weight count");
        Check(Contains(r.source, "iPosition = float4(osGpuSkinPos, 1.0);"), "float4 position is rewritten");
        Check(Contains(r.source, "iNormal.xyz = osGpuSkinNrm;"), "normal is rewritten");
        Check(Contains(r.source, "if (osGpuSkinLen > 0.0)"), "zero-length normals are left unnormalised like Ogre");
        Check(r.source.find("osGpuSkinPos += ") < r.source.find("oPosition = mul(wvpMat, iPosition);"),
              "skinning runs before the original body");
        Check(Contains(r.source, "// base_vertex(...) in a comment must not count"), "comments survive untouched");
        Check(Contains(r.source, "#if NORMALMAP_ENABLED && VERTEX_TANGENTS"),
              "a conditional tangent input is kept as written");
    }
    {
        const SkinnedSourceResult r = MakeSkinnedVertexSource(kTexturedLike, "textured_vertex", 1, 80);
        Check(r.ok, "textured-like entry transforms");
        Check(r.normalParam.empty(), "no NORMAL input means no normal blend");
        Check(!Contains(r.source, "osGpuSkinNrm"), "normal code is omitted without a NORMAL input");
        Check(Contains(r.source, "osGpuSkinBones[240]"), "palette size follows max bones");
        Check(CountOf(r.source, "osGpuSkinPos += ") == 1, "one weight, one accumulate");
    }
    {
        const SkinnedSourceResult r = MakeSkinnedVertexSource(kTexturedLike, "textured_vertex", 4, 8);
        Check(r.ok && CountOf(r.source, "osGpuSkinPos += ") == 4 && Contains(r.source, "osGpuSkinIndices.w"),
              "four weights unroll four blends");
    }
    {
        const std::string float3Pos =
            "void vs(float3 pos : POSITION0, out float4 o : SV_Position) { o = float4(pos, 1); }\n";
        const SkinnedSourceResult r = MakeSkinnedVertexSource(float3Pos, "vs", 2, 4);
        Check(r.ok && Contains(r.source, "pos = osGpuSkinPos;"), "float3 POSITION0 input is rewritten as float3");
    }
    {
        const std::string semanticCase =
            "void vs(in float4 p : position, in float3 n : Normal, out float4 o : SV_POSITION) { o = p; }\n";
        const SkinnedSourceResult r = MakeSkinnedVertexSource(semanticCase, "vs", 2, 4);
        Check(r.ok && r.positionParam == "p" && r.normalParam == "n", "semantics match case-insensitively");
    }

    // Refusals.
    Check(!MakeSkinnedVertexSource(kBaseLike, "missing_vertex", 2, 64).ok, "missing entry is refused");
    Check(!MakeSkinnedVertexSource(kBaseLike, "base_vertex", 0, 64).ok, "zero weights is refused");
    Check(!MakeSkinnedVertexSource(kBaseLike, "base_vertex", 5, 64).ok, "five weights is refused");
    Check(!MakeSkinnedVertexSource(kBaseLike, "base_vertex", 2, 0).ok, "zero bones is refused");
    {
        const std::string twice = std::string(kTexturedLike) +
                                  "#if 0\n" + kTexturedLike + "#endif\n";
        const SkinnedSourceResult r = MakeSkinnedVertexSource(twice, "textured_vertex", 2, 8);
        Check(!r.ok && Contains(r.error, "more than once"), "duplicate entry definitions are refused");
    }
    {
        const std::string nonVoid =
            "float4 vs(float4 p : POSITION) : SV_POSITION { return p; }\n";
        Check(!MakeSkinnedVertexSource(nonVoid, "vs", 2, 8).ok, "non-void entry is refused");
    }
    {
        const std::string structIn =
            "struct VIn { float4 p : POSITION; };\n"
            "void vs(VIn input, out float4 o : SV_POSITION) { o = input.p; }\n";
        Check(!MakeSkinnedVertexSource(structIn, "vs", 2, 8).ok, "struct input is refused");
    }
    {
        const std::string tangent =
            "void vs(float4 p : POSITION, float3 n : NORMAL, float4 t : TANGENT, out float4 o : SV_POSITION) { o = p; }\n";
        const SkinnedSourceResult r = MakeSkinnedVertexSource(tangent, "vs", 2, 8);
        Check(r.ok && !Contains(r.source, "t = "), "tangent input passes through unskinned, as on the CPU path");
    }
    {
        const std::string skinned =
            "void vs(float4 p : POSITION, uint4 i : BLENDINDICES, out float4 o : SV_POSITION) { o = p; }\n";
        Check(!MakeSkinnedVertexSource(skinned, "vs", 2, 8).ok, "already-skinned entry is refused");
    }
    {
        const std::string conditional =
            "void vs(\n#ifdef A\nfloat4 p : POSITION,\n#else\nfloat3 p : POSITION,\n#endif\nout float4 o : SV_POSITION) { o = 0; }\n";
        const SkinnedSourceResult r = MakeSkinnedVertexSource(conditional, "vs", 2, 8);
        Check(!r.ok, "conditional POSITION input is refused");
    }
    {
        const std::string nameInsideOther =
            "void my_vs_helper(float4 p : POSITION) {}\n"
            "void vs(float4 p : POSITION, out float4 o : SV_POSITION) { o = p; }\n";
        const SkinnedSourceResult r = MakeSkinnedVertexSource(nameInsideOther, "vs", 1, 8);
        Check(r.ok && CountOf(r.source, "osGpuSkinIndices : BLENDINDICES") == 1,
              "entry name match respects identifier boundaries");
    }

    Check(HashText("abc") == HashText("abc") && HashText("abc") != HashText("abd"), "hash is stable and source-sensitive");
    Check(HashText("") == 1469598103934665603ULL, "hash is FNV-1a 64");
    return OpenShimTest::ExitCode();
}
