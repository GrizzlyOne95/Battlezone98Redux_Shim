// Mandatory deployed Enhanced renderer-resource set validation core.
// Pure filesystem logic: no Win32 handles, no logging, no process state, so
// tests can drive every failure mode with temporary directories.

#include "render_profile_resources.h"

#include <cstdio>
#include <cstring>

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
            "openshim_ibl_brdf_lut.dds",
            "openshim_ibl_neutral_irradiance.dds",
            "openshim_ibl_neutral_prefilter.dds",
        };
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

        FILE* file = nullptr;
        const std::filesystem::path versionFile =
            resourceDir / kEnhancedResourceVersionFile;
        if (_wfopen_s(&file, versionFile.c_str(), L"rb") != 0 || file == nullptr)
        {
            outProblem = "missing resources.version marker";
            return false;
        }

        char actual[32] = {};
        const size_t read = fread(actual, 1, sizeof(actual) - 1, file);
        fclose(file);

        if (read == 0 || strncmp(actual, kEnhancedResourcesVersion, read) != 0)
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

        return true;
    }
}
