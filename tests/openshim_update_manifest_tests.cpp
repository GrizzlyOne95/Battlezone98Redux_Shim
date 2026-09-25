#include "openshim_update_manifest.h"

#include <cstdio>
#include <string>
#include <vector>

using namespace BZROpenShim;

namespace
{
    int g_Failures = 0;

    void Check(bool condition, const char* message)
    {
        if (condition)
            return;
        std::fprintf(stderr, "FAIL: %s\n", message);
        ++g_Failures;
    }

    const char* const kValidManifest = R"LUA(
return {
    formatVersion = 2,
    version = "1.2.3.4",
    sha256 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
    size = 1234,
    architecture = "x86",
    payloads = {
        winmm = { source = "winmm.dll", destination = "winmm.dll", sha256 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", size = 1234, version = "1.2.3.4", architecture = "x86" },
        network = { source = "openshim_net.ini.payload", destination = "net.ini", sha256 = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", size = 2345 },
        patches = { source = "openshim_patches.json.payload", destination = "scripts\patches.json", sha256 = "cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc", size = 3456 },
        playerConfig = { source = "openshim.ini.payload", destination = "openshim.ini", sha256 = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee", size = 5678, overwrite = false },
        helper = { source = "bzfile_replace_helper.exe", sha256 = "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD", size = 4567 },
    },
}
)LUA";

    const std::string kHelperLine =
        "        helper = { source = \"bzfile_replace_helper.exe\", sha256 = \"DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD\", size = 4567 },";

    std::string Replace(std::string text, const std::string& from, const std::string& to)
    {
        const size_t at = text.find(from);
        Check(at != std::string::npos, "test fixture must contain the text being replaced");
        if (at != std::string::npos)
            text.replace(at, from.size(), to);
        return text;
    }

    void TestManifestShape()
    {
        OpenShimUpdateManifest manifest;
        std::string error;
        Check(ParseOpenShimUpdateManifest(kValidManifest, manifest, error),
              "generated format should parse");
        Check(manifest.version == "1.2.3.4", "version should be preserved");
        Check(manifest.patches.destination == "scripts\\patches.json",
              "escaped destination should be decoded to the expected manifest spelling");
        Check(manifest.helper.source == "bzfile_replace_helper.exe",
              "helper source should be preserved");
        Check(manifest.helper.sha256 == std::string(64, 'd'),
              "helper hash should be lower-cased");
        Check(manifest.helper.size == 4567, "helper size should be preserved");
        Check(manifest.helper.destination.empty(), "helper has no destination");

        Check(!ParseOpenShimUpdateManifest(
                  Replace(kValidManifest, kHelperLine, ""), manifest, error),
              "a manifest that does not attest the helper must be rejected");
        Check(error.find("does not attest bzfile_replace_helper.exe") != std::string::npos,
              "the missing helper attestation must be named in the error");

        Check(!ParseOpenShimUpdateManifest(
                  Replace(kValidManifest, "source = \"bzfile_replace_helper.exe\"",
                          "source = \"other_helper.exe\""), manifest, error),
              "a helper entry naming another executable must be rejected");

        Check(!ParseOpenShimUpdateManifest(
                  Replace(kValidManifest, "size = 4567", "size = 0"), manifest, error),
              "a zero-size helper must be rejected");

        Check(!ParseOpenShimUpdateManifest(
                  Replace(kValidManifest, "helper = { source = \"bzfile_replace_helper.exe\",",
                          "helper = { source = \"bzfile_replace_helper.exe\", destination = \"winmm.dll\","),
                  manifest, error),
              "a helper entry with a destination is not the attested shape");

        std::string wrongItem = Replace(kValidManifest, "openshim_net.ini.payload", "other.ini");
        Check(!ParseOpenShimUpdateManifest(wrongItem, manifest, error),
              "unexpected payload source must be rejected");

        std::string wrongHash = Replace(kValidManifest, std::string(64, 'b'), "not-a-hash");
        Check(!ParseOpenShimUpdateManifest(wrongHash, manifest, error),
              "invalid payload hash must be rejected");

        std::string wrongArchitecture = Replace(kValidManifest, "architecture = \"x86\"",
                                                "architecture = \"x64\"");
        Check(!ParseOpenShimUpdateManifest(wrongArchitecture, manifest, error),
              "non-x86 suite must be rejected");

        // Untrusted text must never escape the parser as an exception, and a
        // rejected parse must leave nothing behind from a previous success.
        std::string pathological;
        for (int line = 0; line < 2048; ++line)
            pathological += "\n   ";
        pathological += "formatVersion";
        Check(!ParseOpenShimUpdateManifest(pathological, manifest, error),
              "pathological whitespace must be rejected, not thrown or hung on");
        Check(manifest.version.empty() && manifest.helper.sha256.empty(),
              "a rejected manifest must be cleared");
        Check(!ParseOpenShimUpdateManifest(std::string(), manifest, error),
              "an empty manifest must be rejected");
    }

    void TestVersionParsing()
    {
        std::vector<uint32_t> parts;
        Check(ParseOpenShimVersion("1.0.0.33", parts) && parts.size() == 4 && parts[3] == 33,
              "a dotted numeric version parses into its components");
        Check(ParseOpenShimVersion("7", parts) && parts.size() == 1 && parts[0] == 7,
              "a single component is a version");
        Check(ParseOpenShimVersion("999999999.0", parts) && parts[0] == 999999999u,
              "nine-digit components are accepted");

        const char* const rejected[] = {
            "", ".", "1.", ".1", "1..2", "1.0.0.33-beta", "1,0,0,33", "v1.0",
            "1.0.0.33 ", " 1.0.0.33", "1.0.0.4294967295", "1e3",
        };
        for (const char* text : rejected)
        {
            const bool parsed = ParseOpenShimVersion(text, parts);
            if (parsed)
                std::fprintf(stderr, "FAIL: '%s' should not parse as a version\n", text);
            Check(!parsed && parts.empty(), "rejected versions leave no components behind");
        }
    }

    void TestVersionComparison()
    {
        int order = 99;
        Check(CompareOpenShimVersions("1.0.0.33", "1.0.0.34", order) && order == -1,
              "an older build compares below a newer one");
        Check(CompareOpenShimVersions("1.0.0.34", "1.0.0.33", order) && order == 1,
              "a newer build compares above an older one");
        Check(CompareOpenShimVersions("1.0", "1.0.0.0", order) && order == 0,
              "missing trailing components compare as zero");
        Check(CompareOpenShimVersions("2", "1.9.9.9", order) && order == 1,
              "a higher leading component wins regardless of length");
        Check(CompareOpenShimVersions("1.0.0.33", "1.0.0.33", order) && order == 0,
              "equal versions compare equal");

        order = 99;
        Check(!CompareOpenShimVersions("1.0.0.33", "1.0.0.33-rc", order) && order == 99,
              "an unparsable side refuses to compare and leaves order untouched");
        Check(!CompareOpenShimVersions("", "1.0.0.33", order) && order == 99,
              "an empty side refuses to compare");
        Check(!CompareOpenShimVersions("99.0.0.0", "", order),
              "a free-form manifest version cannot win by being unparsable");
    }
}

int main()
{
    TestManifestShape();
    TestVersionParsing();
    TestVersionComparison();

    if (g_Failures == 0)
        std::puts("openshim_update_manifest_tests: PASS");
    return g_Failures == 0 ? 0 : 1;
}
