// Pure source transform for the experimental GPU skinning path. No Win32, no
// Ogre: turns an installed HLSL vertex entry point into a hardware-skinned
// twin so the runtime can build skinned clones of the stock craft programs
// without shipping copies of them. Kept C++14 for the Ogre-header TU.
#pragma once

#include <string>

namespace BZROpenShim
{
    namespace GpuSkinning
    {
        // Name of the bone palette uniform the transform adds. It is a float4
        // array, three rows per bone, so Ogre's world_matrix_array_3x4 auto
        // constant fills it directly and matrix packing does not matter.
        constexpr const char* kBonePaletteUniform = "osGpuSkinBones";

        constexpr int kMinWeightsPerVertex = 1;
        constexpr int kMaxWeightsPerVertex = 4;

        struct SkinnedSourceResult
        {
            bool ok = false;
            std::string source;
            // Why the transform refused; empty on success.
            std::string error;
            // Parameter names the transform skinned, for logging.
            std::string positionParam;
            std::string normalParam;
            // True when the source's #if structure was evaluated with the
            // program's defines (so conditional parameters were decided).
            bool conditionalsResolved = false;
        };

        // Rewrites `void <entryPoint>(...)` so that, before the original body
        // runs, its POSITION input (and NORMAL input, when present) is replaced
        // by the weighted sum of the bone-transformed input. The blend mirrors
        // Ogre's software path: sum_i(w_i * (M_i * p)) for positions, the 3x3
        // part for normals, then the normal is renormalised.
        //
        // `defines` is the program's preprocessor_defines ("A,B=2;C"). The
        // file's #if/#ifdef/#ifndef/#elif/#else structure, with its own
        // #define/#undef lines, is evaluated against them, so the entry point
        // and its signature are read as the compiler will see them. The output
        // keeps every directive: the twin is compiled with the same defines.
        //
        // Refuses (ok == false) rather than guess when the entry point is not
        // found exactly once, does not return void, takes a struct input, or
        // already uses BLENDINDICES/BLENDWEIGHT. A POSITION/NORMAL declared
        // under a conditional is refused only when the conditionals cannot be
        // evaluated: an active #include or #error, a function-like macro or a
        // compiler/Ogre-defined name (__*, OGRE_*, SHADER_MODEL*) in a test.
        // TANGENT/BINORMAL inputs pass through unskinned, because Ogre's
        // software blend leaves them in bind pose too.
        SkinnedSourceResult MakeSkinnedVertexSource(
            const std::string& source,
            const std::string& entryPoint,
            int weightsPerVertex,
            int maxBones,
            const std::string& defines = std::string());

        // FNV-1a over the text, for program names: Ogre's microcode cache is
        // keyed by program name, so a name must change when its source does.
        unsigned long long HashText(const std::string& text);
    }
}
