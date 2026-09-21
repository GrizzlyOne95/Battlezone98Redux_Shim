// bzn_filename_identity_tests.cpp
// Mission filename identity checks.

#include "bzn_filename_identity.h"

#include <cstdio>
#include <string>

namespace
{
    int g_Failures = 0;

    void Check(bool condition, const char* what)
    {
        if (!condition)
        {
            std::printf("FAIL: %s\n", what);
            ++g_Failures;
        }
    }
}

int main()
{
    using BZROpenShim::BznFilenameIdentity::Compare;
    using BZROpenShim::BznFilenameIdentity::CompareTerrainName;

    {
        const auto r = Compare("sample.bzn", "sample.bzn");
        Check(r.comparable && r.matches, "matching basename accepted");
    }
    {
        const auto r = Compare("C:\\mods\\Sample.BZN", "sample.bzn");
        Check(r.comparable && r.matches, "Windows-style case-only difference accepted");
        Check(r.openedBasename == "Sample.BZN", "Windows path basename extracted");
    }
    {
        const auto r = Compare("/mods/sample.bzn", "SAMPLE.BZN");
        Check(r.comparable && r.matches, "forward-slash path and case-only difference accepted");
    }
    {
        const auto r = Compare("newmission.bzn", "oldmission.bzn");
        Check(r.comparable && !r.matches, "stale embedded mission filename detected");
    }
    {
        // Terrain reuse is intentionally absent from this API. A caller may
        // load newmission.bzn with TerrainName=oldterrain and this identity
        // check remains solely about the selected BZN vs msn_filename.
        const auto r = Compare("newmission.bzn", "newmission.bzn");
        Check(r.comparable && r.matches, "terrain reuse does not affect mission identity");
    }
    {
        const auto r = Compare("sample.bzn", "");
        Check(!r.comparable, "missing embedded field is not guessed");
    }

    // Filename/TerrainName is intentionally weaker than filename/msn_filename.
    // A mismatch is useful context, but can be valid terrain reuse.
    {
        const auto r = CompareTerrainName("sample.bzn", "sample");
        Check(r.comparable && r.matches, "terrain: matching mission stem accepted");
    }
    {
        const auto r = CompareTerrainName("C:\\mods\\Sample.BZN", "sample");
        Check(r.comparable && r.matches, "terrain: case-only difference accepted");
        Check(r.openedBasename == "Sample", "terrain: .bzn extension removed before comparison");
    }
    {
        const auto r = CompareTerrainName("pilot.bzn", "lcbench");
        Check(r.comparable && !r.matches,
              "terrain: intentional reuse remains a detectable relationship mismatch");
    }
    {
        const auto r = CompareTerrainName("mission.v2.bzn", "mission.v2");
        Check(r.comparable && r.matches, "terrain: only final .bzn extension stripped");
    }
    {
        const auto r = CompareTerrainName("sample.bzn", "");
        Check(!r.comparable, "terrain: missing TerrainName is not guessed");
    }
    {
        const std::string nonAscii = std::string("mission_") + static_cast<char>(0xE9) + ".bzn";
        const auto r = Compare(nonAscii, nonAscii);
        Check(!r.comparable, "non-ASCII filename comparison fails closed");
    }

    if (g_Failures == 0)
    {
        std::printf("bzn_filename_identity_tests: all checks passed\n");
        return 0;
    }

    std::printf("bzn_filename_identity_tests: %d failure(s)\n", g_Failures);
    return 1;
}
