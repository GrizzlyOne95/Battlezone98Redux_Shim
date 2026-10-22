#include "planet_environment_core.h"

#include <cstdio>
#include <cstring>
#include <vector>
#include "test_check.h"

using OpenShimTest::Check;

using namespace BZROpenShim::PlanetEnvironment;

namespace
{
    void Put32(std::vector<std::uint8_t>& bytes, std::size_t offset, std::uint32_t value)
    {
        for (int i = 0; i < 4; ++i)
            bytes[offset + i] = static_cast<std::uint8_t>(value >> (8 * i));
    }

    // Legacy DXT1 cubemap header followed by a zeroed payload of the right size.
    std::vector<std::uint8_t> MakeCube(std::uint32_t size, std::uint32_t mips)
    {
        std::vector<std::uint8_t> bytes(128 + 6 * Bc1FaceBytes(size, size, mips), 0);
        Put32(bytes, 0, 0x20534444);
        Put32(bytes, 4, 124);
        Put32(bytes, 12, size);
        Put32(bytes, 16, size);
        Put32(bytes, 28, mips);
        Put32(bytes, 76, 32);
        Put32(bytes, 80, 0x4);
        std::memcpy(&bytes[84], "DXT1", 4);
        Put32(bytes, 108, 0x401008);
        Put32(bytes, 112, 0xFE00);
        return bytes;
    }
}

int main()
{
    std::string code;
    Check(WorldCodeFromAtlasPath("MA_Detail_Atlas.csv", code) && code == "ma",
        "bare uppercase leaf gives lowercase code");
    Check(WorldCodeFromAtlasPath("C:\\Game\\Terrain\\el_detail_atlas.csv", code) && code == "el",
        "backslash path gives code");
    Check(WorldCodeFromAtlasPath("data/ve_DETAIL_ATLAS.CSV", code) && code == "ve",
        "forward slash path gives code");
    Check(!WorldCodeFromAtlasPath("_detail_atlas.csv", code) && code.empty(),
        "empty prefix rejected");
    Check(!WorldCodeFromAtlasPath("ma_detail_atlas.txt", code), "other extension rejected");
    Check(!WorldCodeFromAtlasPath("ma_detail_atlas.csv\\x", code), "directory leaf rejected");
    Check(IsKnownWorldCode("io") && IsKnownWorldCode("mn") && !IsKnownWorldCode("zz") &&
              !IsKnownWorldCode("") && !IsKnownWorldCode("mac"),
        "known world codes");

    Check(Bc1MipBytes(1, 1) == 8 && Bc1MipBytes(4, 4) == 8 && Bc1MipBytes(8, 8) == 32,
        "BC1 mip sizes");
    Check(Bc1FaceBytes(32, 32, 1) == 512, "irradiance face size");
    Check(Bc1FaceBytes(128, 128, 8) == 8192 + 2048 + 512 + 128 + 32 + 8 + 8 + 8,
        "prefilter face size");

    DdsCubeInfo info;
    const char* problem = nullptr;
    std::vector<std::uint8_t> pre = MakeCube(128, 8);
    Check(ParseDdsCubeBc1(pre.data(), pre.size(), info, problem), "prefilter parses");
    Check(info.width == 128 && info.height == 128 && info.mipLevels == 8 && info.dataOffset == 128,
        "prefilter info");
    Check(DdsCubeMatchesTexture(info, 128, 128, 8, 6, 71, true), "matches BC1_UNORM");
    Check(DdsCubeMatchesTexture(info, 128, 128, 8, 6, 72, true), "matches BC1_UNORM_SRGB");
    Check(!DdsCubeMatchesTexture(info, 128, 128, 8, 6, 77, true), "BC3 destination rejected");
    Check(DdsCubeMatchesTexture(info, 128, 128, 6, 6, 71, true), "fewer destination mips accepted");
    Check(!DdsCubeMatchesTexture(info, 128, 128, 9, 6, 71, true), "more destination mips rejected");
    Check(!DdsCubeMatchesTexture(info, 64, 64, 8, 6, 71, true), "size mismatch rejected");
    Check(!DdsCubeMatchesTexture(info, 128, 128, 8, 1, 71, true), "non-array destination rejected");
    Check(!DdsCubeMatchesTexture(info, 128, 128, 8, 6, 71, false), "non-cube destination rejected");

    std::vector<std::uint8_t> irr = MakeCube(32, 1);
    Check(ParseDdsCubeBc1(irr.data(), irr.size(), info, problem) && info.mipLevels == 1,
        "irradiance parses");

    std::vector<std::uint8_t> bad = pre;
    bad.pop_back();
    Check(!ParseDdsCubeBc1(bad.data(), bad.size(), info, problem), "truncated payload rejected");
    bad = pre;
    bad[84] = 'Y';
    Check(!ParseDdsCubeBc1(bad.data(), bad.size(), info, problem), "non-DXT1 rejected");
    bad = pre;
    Put32(bad, 112, 0x200);
    Check(!ParseDdsCubeBc1(bad.data(), bad.size(), info, problem), "missing faces rejected");
    bad = pre;
    Put32(bad, 0, 0);
    Check(!ParseDdsCubeBc1(bad.data(), bad.size(), info, problem), "bad magic rejected");
    Check(!ParseDdsCubeBc1(pre.data(), 64, info, problem), "short file rejected");

    if (OpenShimTest::FailureCount() == 0)
        std::puts("planet environment tests passed");
    return OpenShimTest::ExitCode();
}
