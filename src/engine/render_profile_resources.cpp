// Mandatory deployed Enhanced renderer-resource set validation core.
// Pure filesystem logic: no Win32 handles, no logging, no process state, so
// tests can drive every failure mode with temporary directories.

#include "render_profile_resources.h"

#include <cctype>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <string>

namespace BZROpenShim::RenderProfiles
{
    namespace
    {
        // Mandatory files of the deployed Enhanced set. The version marker
        // alone cannot prove a deployment is usable (a correct marker can sit
        // next to deleted/empty payloads), so every program, shader source,
        // and texture below must exist non-empty. The list is the single
        // source of truth for both runtime validation and the host tests.
        constexpr const char* kRequiredEnhancedResources[] = {
            "openshim_enhanced_base.program",
            "openshim_enhanced_base-vertex.glsl",
            "openshim_enhanced_base-fragment.glsl",
            "openshim_enhanced_base-sm3.hlsl",
            "openshim_enhanced_base-sm4.hlsl",
            "openshim_enhanced_terrain.program",
            "openshim_enhanced_terrain-vertex.glsl",
            "openshim_enhanced_terrain-fragment.glsl",
            "openshim_enhanced_terrain-sm3.hlsl",
            "openshim_enhanced_terrain-sm4.hlsl",
            "openshim_enhanced_terrain_glow-vertex.glsl",
            "openshim_enhanced_terrain_glow-fragment.glsl",
            "openshim_enhanced_terrain_glow-sm3.hlsl",
            "openshim_enhanced_terrain_glow-sm4.hlsl",
            "openshim_dx11_fixedfunc.program",
            "openshim_dx11_fixedfunc-sm4.hlsl",
            "openshim_ibl_brdf_lut.dds",
            "openshim_ibl_neutral_irradiance.dds",
            "openshim_ibl_neutral_prefilter.dds",
        };
    }

    bool VersionMarkerMatches(const char* marker, const size_t markerLength,
                              const char* expected)
    {
        if (marker == nullptr || expected == nullptr)
        {
            return false;
        }
        const size_t expectedLength = strlen(expected);
        return markerLength == expectedLength &&
               memcmp(marker, expected, expectedLength) == 0;
    }

    size_t RequiredEnhancedResourceCount()
    {
        return sizeof(kRequiredEnhancedResources) /
               sizeof(kRequiredEnhancedResources[0]);
    }

    const char* RequiredEnhancedResourceAt(const size_t index)
    {
        if (index >= RequiredEnhancedResourceCount())
        {
            return nullptr;
        }
        return kRequiredEnhancedResources[index];
    }

    bool ValidateDeployedResourceSetAt(const std::filesystem::path& resourceDir,
                                       std::string& outProblem)
    {
        outProblem.clear();

        if (!std::filesystem::is_directory(resourceDir))
        {
            outProblem = "resource directory absent";
            return false;
        }

        // Portable open: std::ifstream accepts the filesystem path on both
        // Windows (wide) and Linux (narrow), unlike _wfopen_s which is MSVC-only.
        const std::filesystem::path versionFile =
            resourceDir / kEnhancedResourceVersionFile;
        std::ifstream in(versionFile, std::ios::binary);
        if (!in)
        {
            outProblem = "missing resources.version marker";
            return false;
        }

        char actual[32] = {};
        const std::streamsize read =
            in.read(actual, sizeof(actual) - 1).gcount();
        if (read <= 0)
        {
            outProblem = "resources.version mismatch";
            return false;
        }

        if (!VersionMarkerMatches(actual, static_cast<size_t>(read),
                                  kEnhancedResourcesVersion))
        {
            outProblem = "resources.version mismatch";
            return false;
        }

        for (size_t i = 0; i < RequiredEnhancedResourceCount(); ++i)
        {
            std::error_code ec;
            const std::filesystem::path path =
                resourceDir / kRequiredEnhancedResources[i];
            if (!std::filesystem::is_regular_file(path, ec) ||
                ec || std::filesystem::file_size(path, ec) == 0 || ec)
            {
                outProblem = std::string("mandatory resource missing/empty: ") +
                             kRequiredEnhancedResources[i];
                return false;
            }
        }

        // Every file above being present is not the same as nothing else being
        // there. Ogre adds this directory as a recursive resource location and
        // parses every script in it, and the FIRST declaration of a program
        // name wins -- so one leftover script declaring the same names shadows
        // the whole payload, without Ogre reporting a conflict.
        //
        // That is not hypothetical. A v1 payload was once left beside a v3 one
        // as "openshim_enhanced_base (1).program" and friends, courtesy of a
        // Windows copy. "(1)" sorts before "." so the stale scripts parsed
        // first and won, the version marker still read 3 because the canonical
        // file was untouched, and the Enhanced terrain quietly ran a shader
        // with a third fewer normal-mapping paths than the one on disk.
        //
        // Only parsed script types are rejected. A stray .hlsl or .glsl is
        // inert unless a script names it, and failing the whole payload -- which
        // drops the install to Redux -- would be out of proportion to that.
        std::error_code scanEc;
        for (std::filesystem::directory_iterator it(resourceDir, scanEc), end;
             !scanEc && it != end; it.increment(scanEc))
        {
            std::error_code fileEc;
            if (!it->is_regular_file(fileEc) || fileEc)
            {
                continue;
            }

            std::string ext = it->path().extension().string();
            for (char& ch : ext)
            {
                ch = static_cast<char>(
                    ::tolower(static_cast<unsigned char>(ch)));
            }
            if (ext != ".program" && ext != ".material")
            {
                continue;
            }

            const std::string name = it->path().filename().string();
            bool expected = false;
            for (size_t i = 0; i < RequiredEnhancedResourceCount(); ++i)
            {
                if (name == kRequiredEnhancedResources[i])
                {
                    expected = true;
                    break;
                }
            }
            if (!expected)
            {
                outProblem = std::string("unexpected script shadows the "
                                         "payload: ") + name;
                return false;
            }
        }

        return true;
    }
}
