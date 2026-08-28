#include "openshim_update_manifest.h"

#include <cstdio>
#include <string>

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
    },
}
)LUA";
}

int main()
{
    OpenShimUpdateManifest manifest;
    std::string error;
    Check(ParseOpenShimUpdateManifest(kValidManifest, manifest, error),
          "generated format should parse");
    Check(manifest.version == "1.2.3.4", "version should be preserved");
    Check(manifest.patches.destination == "scripts\\patches.json",
          "escaped destination should be decoded to the expected manifest spelling");

    std::string wrongItem = kValidManifest;
    wrongItem.replace(wrongItem.find("openshim_net.ini.payload"),
                      std::string("openshim_net.ini.payload").size(), "other.ini");
    Check(!ParseOpenShimUpdateManifest(wrongItem, manifest, error),
          "unexpected payload source must be rejected");

    std::string wrongHash = kValidManifest;
    wrongHash.replace(wrongHash.find(std::string(64, 'b')), 64, "not-a-hash");
    Check(!ParseOpenShimUpdateManifest(wrongHash, manifest, error),
          "invalid payload hash must be rejected");

    std::string wrongArchitecture = kValidManifest;
    wrongArchitecture.replace(wrongArchitecture.find("architecture = \"x86\""),
                              std::string("architecture = \"x86\"").size(),
                              "architecture = \"x64\"");
    Check(!ParseOpenShimUpdateManifest(wrongArchitecture, manifest, error),
          "non-x86 suite must be rejected");

    if (g_Failures == 0)
        std::puts("openshim_update_manifest_tests: PASS");
    return g_Failures == 0 ? 0 : 1;
}
