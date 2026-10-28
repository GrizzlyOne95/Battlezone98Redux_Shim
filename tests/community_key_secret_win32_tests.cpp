#include "community_key_secret.h"

#include <windows.h>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>

using namespace BZROpenShim;

namespace
{
    int g_failures = 0;

    void Check(bool condition, const char* what)
    {
        if (!condition)
        {
            std::printf("FAIL: %s\n", what);
            ++g_failures;
        }
    }

    bool AllZero(const std::array<unsigned char, kCommunitySecretBytes>& bytes)
    {
        for (const unsigned char byte : bytes)
        {
            if (byte != 0)
                return false;
        }
        return true;
    }
}

int main()
{
    namespace fs = std::filesystem;
    const fs::path dir = fs::temp_directory_path() /
                         ("community_key_secret_tests_" + std::to_string(GetCurrentProcessId()));
    fs::remove_all(dir);
    fs::create_directories(dir);
    const fs::path secretPath = dir / kCommunitySecretFileName;

    std::array<unsigned char, kCommunitySecretBytes> first = {};
    Check(LoadOrCreateCommunitySecret(secretPath, first), "creates a missing secret");
    Check(!AllZero(first), "created secret is random, not zero");
    Check(fs::exists(secretPath) && fs::file_size(secretPath) == kCommunitySecretBytes, "file is 32 bytes");

    std::array<unsigned char, kCommunitySecretBytes> second = {};
    Check(LoadOrCreateCommunitySecret(secretPath, second), "reloads an existing secret");
    Check(first == second, "reload returns the same bytes");

    size_t leftovers = 0;
    for (const auto& entry : fs::directory_iterator(dir))
    {
        if (entry.path() != secretPath)
            ++leftovers;
    }
    Check(leftovers == 0, "no temp files left behind");

    const fs::path shortPath = dir / "short.key";
    {
        std::ofstream out(shortPath, std::ios::binary);
        out << "too short";
    }
    std::array<unsigned char, kCommunitySecretBytes> bad = {};
    Check(!LoadOrCreateCommunitySecret(shortPath, bad), "wrong-size file is refused");
    Check(AllZero(bad), "refused secret is zeroed");
    Check(fs::file_size(shortPath) == 9, "wrong-size file is not overwritten");

    std::array<unsigned char, kCommunitySecretBytes> missingDir = {};
    Check(!LoadOrCreateCommunitySecret(dir / "no_such_dir" / "x.key", missingDir), "missing directory fails closed");

    fs::remove_all(dir);
    if (g_failures == 0)
        std::printf("community_key_secret_win32_tests: all passed\n");
    return g_failures == 0 ? 0 : 1;
}
