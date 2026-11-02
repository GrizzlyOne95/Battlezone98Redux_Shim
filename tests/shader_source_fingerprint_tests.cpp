// Unit tests for the microcode-cache shader source fingerprint.
#include "shader_source_fingerprint.h"

#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;
using BZROpenShim::ShaderSourceFingerprint::Compute;
using BZROpenShim::ShaderSourceFingerprint::ScanRoots;

static int g_Failures = 0;

static void Check(bool condition, const char* what)
{
    if (!condition)
    {
        std::fprintf(stderr, "FAIL: %s\n", what);
        ++g_Failures;
    }
}

static void WriteFile(const fs::path& path, const std::string& text)
{
    fs::create_directories(path.parent_path());
    std::ofstream(path, std::ios::binary) << text;
}

static void Touch(const fs::path& path)
{
    fs::last_write_time(path, fs::last_write_time(path) + std::chrono::seconds(5));
}

int main()
{
    // Unique per run, and nested two deep so ScanRoots' ../../workshop root
    // stays inside the temp tree.
    const fs::path base = fs::temp_directory_path() /
        ("openshim_shader_fp_tests_" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    const fs::path root = base / "steamapps" / "common" / "game";
    std::error_code ec;

    const fs::path hlsl = root / "addon" / "ISDF Chronicles" / "isdfc_wetglass.hlsl";
    const fs::path texture = root / "addon" / "ISDF Chronicles" / "isdfc_wetglass.dds";
    WriteFile(hlsl, "float4 main() : COLOR { return 0; }\n");
    WriteFile(texture, "DDS ");

    const auto roots = ScanRoots(root);
    size_t seen = 0;
    const uint64_t before = Compute(roots, &seen);
    Check(seen == 1, "addon shader source is scanned");

    Touch(hlsl);
    const uint64_t afterTouch = Compute(roots);
    Check(afterTouch != before, "touching an addon .hlsl changes the fingerprint");

    WriteFile(hlsl, "float4 main() : COLOR { return 1.0; }\n");
    const uint64_t afterEdit = Compute(roots);
    Check(afterEdit != afterTouch, "resizing an addon .hlsl changes the fingerprint");

    Touch(texture);
    Check(Compute(roots) == afterEdit, "non-shader files do not affect the fingerprint");

    WriteFile(root / "addon" / "ISDF Chronicles" / "isdfc_wetglass.program", "vertex_program x hlsl {}\n");
    Check(Compute(roots, &seen) != afterEdit && seen == 2, "adding an addon .program changes the fingerprint");

    const uint64_t withProgram = Compute(roots);
    WriteFile(root / "addon" / "ISDF Chronicles" / ".git" / "objects" / "stale.hlsl", "x");
    Check(Compute(roots) == withProgram, "dot-directories such as .git are not scanned");

    fs::remove_all(base, ec);
    if (g_Failures == 0)
        std::printf("shader_source_fingerprint_tests: all passed\n");
    return g_Failures == 0 ? 0 : 1;
}
