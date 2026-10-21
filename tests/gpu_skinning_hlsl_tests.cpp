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
        const std::string twice = std::string(kTexturedLike) + kTexturedLike;
        const SkinnedSourceResult r = MakeSkinnedVertexSource(twice, "textured_vertex", 2, 8);
        Check(!r.ok && Contains(r.error, "more than once"), "duplicate entry definitions are refused");
    }
    {
        const std::string disabledCopy = std::string(kTexturedLike) +
                                         "#if 0\n" + kTexturedLike + "#endif\n";
        const SkinnedSourceResult r = MakeSkinnedVertexSource(disabledCopy, "textured_vertex", 2, 8);
        Check(r.ok && r.conditionalsResolved && CountOf(r.source, "osGpuSkinIndices : BLENDINDICES") == 1,
              "a copy under #if 0 is not a second entry");
    }
    {
        const std::string unknowable = std::string(kTexturedLike) +
                                       "#if __SHADER_TARGET_MAJOR > 4\n" + kTexturedLike + "#endif\n";
        const SkinnedSourceResult r = MakeSkinnedVertexSource(unknowable, "textured_vertex", 2, 8);
        Check(!r.ok && !r.conditionalsResolved && Contains(r.error, "more than once"),
              "a compiler-defined test leaves the conditionals unresolved");
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
        SkinnedSourceResult r = MakeSkinnedVertexSource(conditional, "vs", 2, 8);
        Check(r.ok && Contains(r.source, "p = osGpuSkinPos;"), "undefined A selects the float3 POSITION");
        r = MakeSkinnedVertexSource(conditional, "vs", 2, 8, "A");
        Check(r.ok && Contains(r.source, "p = float4(osGpuSkinPos, 1.0);"), "defined A selects the float4 POSITION");
        Check(Contains(r.source, "#ifdef A") && Contains(r.source, "#else"), "directives stay in the output");
    }
    {
        const std::string unresolved =
            "#include \"common.hlsl\"\n"
            "void vs(\n#ifdef A\nfloat4 p : POSITION,\n#endif\nout float4 o : SV_POSITION) { o = 0; }\n";
        const SkinnedSourceResult r = MakeSkinnedVertexSource(unresolved, "vs", 2, 8, "A");
        Check(!r.ok && Contains(r.error, "conditional"), "an #include leaves a conditional POSITION refused");
    }
    {
        // The fixed-function stand-in shape: NORMAL exists only for LIT && !LIT_FLAT.
        const std::string ff =
            "float4x4 wvpMat;\n"
            "void ff_vertex(\n"
            "    in float4 iPosition : POSITION,\n"
            "#if defined(LIT) && !defined(LIT_FLAT)\n"
            "    in float3 iNormal : NORMAL,\n"
            "#endif\n"
            "#ifdef VERTEX_COLOUR\n"
            "    in float4 iColor : COLOR0,\n"
            "#endif\n"
            "    in float2 iTexCoord : TEXCOORD0,\n"
            "    out float4 oPosition : SV_POSITION)\n"
            "{\n    oPosition = mul(wvpMat, iPosition);\n}\n";
        SkinnedSourceResult r = MakeSkinnedVertexSource(ff, "ff_vertex", 4, 64, "LIT=1");
        Check(r.ok && r.normalParam == "iNormal", "LIT=1 skins the conditional NORMAL");
        r = MakeSkinnedVertexSource(ff, "ff_vertex", 4, 64, "LIT=1,LIT_FLAT");
        Check(r.ok && r.normalParam.empty(), "LIT_FLAT drops the NORMAL input");
        r = MakeSkinnedVertexSource(ff, "ff_vertex", 4, 64);
        Check(r.ok && r.normalParam.empty(), "unlit variant skins position only");
    }
    {
        // The surface shape: in-file #defines derived from program defines, a
        // COLOR0/NORMAL #if/#else, a struct output and a macro semantic.
        const std::string surface =
            "#if defined(SM4)\n#define POSITION_OUT SV_POSITION\n#else\n#define POSITION_OUT POSITION\n#endif\n"
            "#ifndef MAX_LIGHTS\n#define MAX_LIGHTS 8\n#endif\n"
            "#if defined(GLASS) || defined(CUTOUT)\n#if !defined(GLOW)\n#define LIT_SURFACE\n#endif\n#endif\n"
            "#if MAX_LIGHTS >= 4 && SM4 == 1\n#define MANY \\\n    1\n#endif\n"
            "#if MANY != 1\n#error continuation lost\n#endif\n"
            "struct SurfaceV2F { float2 uv : TEXCOORD0; };\n"
            "float4x4 wvpMat;\n"
            "void surface_vertex(\n"
            "\tin float4 iPosition : POSITION,\n"
            "#if defined(PARTICLE_COLOUR)\n"
            "\tin float4 iColour : COLOR0,\n"
            "#else\n"
            "\tin float3 iNormal : NORMAL,\n"
            "#endif\n"
            "\tin float2 iTexCoord : TEXCOORD0,\n"
            "\tout SurfaceV2F o,\n"
            "\tout float4 oPosition : POSITION_OUT\n"
            ")\n{\n\toPosition = mul(wvpMat, iPosition);\n\to.uv = iTexCoord;\n}\n";
        SkinnedSourceResult r = MakeSkinnedVertexSource(surface, "surface_vertex", 4, 64,
                                                        "SM4=1,SHADOWRECEIVER=1,PSSM_ENABLED=1");
        Check(r.ok && r.conditionalsResolved && r.normalParam == "iNormal", "surface variant skins NORMAL");
        r = MakeSkinnedVertexSource(surface, "surface_vertex", 4, 64, "SM4=1;PARTICLE_COLOUR");
        Check(r.ok && r.normalParam.empty(), "particle variant has no NORMAL");
    }
    {
        const char* bad[] = {
            "#if FN(1)\n#endif\n",
            "#define FN(x) x\n#if FN\n#endif\n",
            "#define EMPTY\n#if EMPTY\n#endif\n",
            "#if 1 +\n#endif\n",
            "#if 1\n",
            "#endif\n",
            "#if 1 / 0\n#endif\n",
            "#error stop\n",
        };
        for (const char* prefix : bad)
        {
            const SkinnedSourceResult r =
                MakeSkinnedVertexSource(std::string(prefix) + kTexturedLike, "textured_vertex", 2, 8);
            Check(r.ok && !r.conditionalsResolved, "malformed or unknowable structure falls back unresolved");
        }
        const SkinnedSourceResult inactive = MakeSkinnedVertexSource(
            std::string("#if 0\n#error never\n#include \"x\"\n#if FN(1)\n#endif\n#endif\n") + kTexturedLike,
            "textured_vertex", 2, 8);
        Check(inactive.ok && inactive.conditionalsResolved, "inactive branches are not evaluated");
        Check(!MakeSkinnedVertexSource(kTexturedLike, "textured_vertex", 2, 8, "1BAD").conditionalsResolved,
              "an invalid program define is not resolved");
    }
    {
        const std::string nameInsideOther =
            "void my_vs_helper(float4 p : POSITION) {}\n"
            "void vs(float4 p : POSITION, out float4 o : SV_POSITION) { o = p; }\n";
        const SkinnedSourceResult r = MakeSkinnedVertexSource(nameInsideOther, "vs", 1, 8);
        Check(r.ok && CountOf(r.source, "osGpuSkinIndices : BLENDINDICES") == 1,
              "entry name match respects identifier boundaries");
    }

    // Instanced twins of skinned output.
    {
        const SkinnedSourceResult skinned = MakeSkinnedVertexSource(kBaseLike, "base_vertex", 3, 64);
        const SkinnedSourceResult r = MakeInstancedSkinnedVertexSource(skinned.source, 256);
        Check(r.ok, "skinned source gets an instanced twin");
        Check(Contains(r.source, "uniform float4 osGpuSkinBones[768]") && !Contains(r.source, "[192]"),
              "instanced palette is widened");
        Check(Contains(r.source, "in float osGpuInstBase : TEXCOORD15,"), "adds the per-instance base input");
        Check(CountOf(r.source, "(osGpuSkinIndices.") == 3 &&
              Contains(r.source, "uint osGpuSkinRow = (osGpuSkinIndices.z + (uint)osGpuInstBase) * 3;"),
              "every blend index is offset by the instance base");
        Check(!Contains(r.source, "osGpuSkinRow = osGpuSkinIndices."), "no row is left unoffset");
        Check(r.source.find("osGpuInstBase : TEXCOORD15") < r.source.find("out float4 oPosition"),
              "instance input stays in the parameter list");
    }
    {
        const SkinnedSourceResult skinned = MakeSkinnedVertexSource(kTexturedLike, "textured_vertex", 4, 64);
        const SkinnedSourceResult r = MakeInstancedSkinnedVertexSource(skinned.source, 128);
        Check(r.ok && Contains(r.source, "osGpuSkinBones[384]") && CountOf(r.source, "+ (uint)osGpuInstBase") == 4,
              "four weights offset four rows");
    }
    {
        const std::string texcoord15 =
            "void vs(float4 p : POSITION, float2 t : texcoord15, out float4 o : SV_POSITION) { o = p; }\n";
        const SkinnedSourceResult skinned = MakeSkinnedVertexSource(texcoord15, "vs", 2, 8);
        Check(skinned.ok && !MakeInstancedSkinnedVertexSource(skinned.source, 256).ok,
              "an existing TEXCOORD15 input refuses instancing");
    }
    Check(!MakeInstancedSkinnedVertexSource(kTexturedLike, 256).ok, "unskinned source is refused");
    Check(!MakeInstancedSkinnedVertexSource(
              MakeSkinnedVertexSource(kTexturedLike, "textured_vertex", 1, 8).source, 257).ok,
          "palette over 256 bones is refused");

    Check(HashText("abc") == HashText("abc") && HashText("abc") != HashText("abd"), "hash is stable and source-sensitive");
    Check(HashText("") == 1469598103934665603ULL, "hash is FNV-1a 64");
    return OpenShimTest::ExitCode();
}
