// Mandatory Enhanced renderer-resource set validation tests. Builds real
// temporary directory trees and removes/invalidates individual files to prove
// the deployment contract. No engine, no game.
// Build+run via scripts/run_render_profile_tests.ps1.

#include "render_profile_resources.h"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>

using namespace BZROpenShim::RenderProfiles;

namespace
{
    int g_failures = 0;

    void ExpectTrue(bool condition, const char* what)
    {
        if (!condition)
        {
            std::printf("  FAIL: %s\n", what);
            ++g_failures;
        }
    }

    void ExpectContains(const std::string& haystack, const char* needle, const char* what)
    {
        if (haystack.find(needle) == std::string::npos)
        {
            std::printf("  FAIL: %s ('%s' missing '%s')\n", what, haystack.c_str(), needle);
            ++g_failures;
        }
    }

    std::error_code g_errc;

    std::filesystem::path MakeScratchDir(const char* tag)
    {
        std::filesystem::path dir = std::filesystem::temp_directory_path() /
                                    ("bzr_render_profile_resources_" + std::string(tag));
        std::filesystem::remove_all(dir, g_errc);
        std::filesystem::create_directories(dir);
        return dir;
    }

    // Populates a complete, valid deployment into `dir`.
    void PopulateValidSet(const std::filesystem::path& dir)
    {
        std::ofstream marker(dir / kEnhancedResourceVersionFile, std::ios::binary);
        marker << kEnhancedResourcesVersion;
        marker.close();
        for (size_t i = 0; i < RequiredEnhancedResourceCount(); ++i)
        {
            std::ofstream file(dir / RequiredEnhancedResourceAt(i), std::ios::binary);
            file << "payload";
        }
    }

    bool Validate(const std::filesystem::path& dir, std::string& problem)
    {
        return ValidateDeployedResourceSetAt(dir, problem);
    }
}

void TestCompleteSetValidates()
{
    std::printf("TestCompleteSetValidates\n");
    const auto dir = MakeScratchDir("valid");
    PopulateValidSet(dir);
    std::string problem;
    ExpectTrue(Validate(dir, problem), "complete valid set passes");
    ExpectTrue(problem.empty(), "no problem reported");
    std::filesystem::remove_all(dir, g_errc);
}

void TestSingleRemovedMandatoryFileFails()
{
    std::printf("TestSingleRemovedMandatoryFileFails\n");
    // Review requirement: deliberately remove ONE mandatory Enhanced resource
    // and prove validation fails (which the resolver turns into a clean
    // Redux fallback via CapEnhancedResources).
    for (size_t victim = 0; victim < RequiredEnhancedResourceCount(); ++victim)
    {
        const auto dir = MakeScratchDir("missing");
        PopulateValidSet(dir);
        std::filesystem::remove(dir / RequiredEnhancedResourceAt(victim), g_errc);
        std::string problem;
        const bool ok = Validate(dir, problem);
        if (ok)
        {
            std::printf("  FAIL: removal of %s not detected\n",
                        RequiredEnhancedResourceAt(victim));
            ++g_failures;
        }
        else
        {
            ExpectContains(problem, RequiredEnhancedResourceAt(victim),
                           "problem names the removed file");
        }
        std::filesystem::remove_all(dir, g_errc);
    }
}

void TestEmptiedMandatoryFileFails()
{
    std::printf("TestEmptiedMandatoryFileFails\n");
    const auto dir = MakeScratchDir("empty");
    PopulateValidSet(dir);
    // Zero-byte payloads are the realistic corruption mode (interrupted
    // deploy); they must fail exactly like a missing file.
    std::ofstream truncate(dir / RequiredEnhancedResourceAt(0),
                           std::ios::binary | std::ios::trunc);
    truncate.close();
    std::string problem;
    ExpectTrue(!Validate(dir, problem), "empty payload rejected");
    ExpectContains(problem, RequiredEnhancedResourceAt(0), "problem names emptied file");
    std::filesystem::remove_all(dir, g_errc);
}

void TestVersionMarkerContract()
{
    std::printf("TestVersionMarkerContract\n");
    const auto dir = MakeScratchDir("version");
    PopulateValidSet(dir);

    {
        std::ofstream marker(dir / kEnhancedResourceVersionFile, std::ios::binary | std::ios::trunc);
        marker << "999";
        marker.close();
        std::string problem;
        ExpectTrue(!Validate(dir, problem), "stale version rejected");
        ExpectContains(problem, "version", "problem mentions version");
    }
    {
        std::filesystem::remove(dir / kEnhancedResourceVersionFile, g_errc);
        std::string problem;
        ExpectTrue(!Validate(dir, problem), "missing marker rejected");
    }
    std::filesystem::remove_all(dir, g_errc);
}

void TestAbsentDirectoryFails()
{
    std::printf("TestAbsentDirectoryFails\n");
    const auto dir = MakeScratchDir("absent");
    std::filesystem::remove_all(dir, g_errc); // guarantee absence
    std::string problem;
    ExpectTrue(!Validate(dir, problem), "absent directory rejected");
    std::filesystem::remove_all(dir, g_errc);
}

int main()
{
    TestCompleteSetValidates();
    TestSingleRemovedMandatoryFileFails();
    TestEmptiedMandatoryFileFails();
    TestVersionMarkerContract();
    TestAbsentDirectoryFails();

    if (g_failures != 0)
    {
        std::printf("\nrender_profile_resources_tests FAILED (%d)\n", g_failures);
        return 1;
    }
    std::printf("\nrender_profile_resources_tests passed\n");
    return 0;
}
