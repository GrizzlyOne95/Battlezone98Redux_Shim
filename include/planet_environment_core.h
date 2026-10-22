#pragma once

// Pure helpers for the per-world image-based-lighting swap: world-code
// extraction from a terrain detail-atlas path and validation of the optional
// openshim_env_<code>_{prefilter,irradiance}.dds cubemaps. No Win32 or D3D11
// types, so the host tests exercise every rejection path directly.

#include <cstddef>
#include <cstdint>
#include <string>

namespace BZROpenShim::PlanetEnvironment
{
    // Two-letter world prefixes Redux ships a terrain atlas for.
    inline bool IsKnownWorldCode(const std::string& code)
    {
        static const char* const kCodes[] = {
            "mn", "ma", "ve", "io", "eu", "ti", "ga", "ac", "el",
        };
        for (const char* known : kCodes)
            if (code == known)
                return true;
        return false;
    }

    // "<dir>\\MA_Detail_Atlas.csv" -> "ma". Case-insensitive; accepts '/' and
    // '\\'. Returns false for any other leaf or an empty prefix.
    inline bool WorldCodeFromAtlasPath(const std::string& path, std::string& code)
    {
        code.clear();
        const std::size_t slash = path.find_last_of("/\\");
        std::string leaf = slash == std::string::npos ? path : path.substr(slash + 1);
        for (char& ch : leaf)
            if (ch >= 'A' && ch <= 'Z')
                ch = static_cast<char>(ch - 'A' + 'a');
        static const char kSuffix[] = "_detail_atlas.csv";
        constexpr std::size_t kSuffixLength = sizeof(kSuffix) - 1;
        if (leaf.size() <= kSuffixLength ||
            leaf.compare(leaf.size() - kSuffixLength, kSuffixLength, kSuffix) != 0)
            return false;
        code = leaf.substr(0, leaf.size() - kSuffixLength);
        return true;
    }

    // Layout of a legacy (non-DX10) DDS cubemap as the loader needs it.
    struct DdsCubeInfo
    {
        std::uint32_t width = 0;
        std::uint32_t height = 0;
        std::uint32_t mipLevels = 0;
        std::size_t dataOffset = 0;
    };

    inline std::uint32_t ReadLe32(const std::uint8_t* p)
    {
        return std::uint32_t(p[0]) | (std::uint32_t(p[1]) << 8) |
               (std::uint32_t(p[2]) << 16) | (std::uint32_t(p[3]) << 24);
    }

    // BC1 (DXT1) size of one mip: 4x4 blocks of 8 bytes.
    inline std::size_t Bc1MipBytes(std::uint32_t width, std::uint32_t height)
    {
        const std::size_t bx = width > 4 ? (width + 3) / 4 : 1;
        const std::size_t by = height > 4 ? (height + 3) / 4 : 1;
        return bx * by * 8;
    }

    // Bytes of one face's full mip chain.
    inline std::size_t Bc1FaceBytes(std::uint32_t width, std::uint32_t height,
                                    std::uint32_t mipLevels)
    {
        std::size_t total = 0;
        for (std::uint32_t mip = 0; mip < mipLevels; ++mip)
        {
            total += Bc1MipBytes(width > 1 ? width : 1, height > 1 ? height : 1);
            width >>= 1;
            height >>= 1;
        }
        return total;
    }

    // Parses a DXT1 cubemap with all six faces and checks the file size
    // against Bc1FaceBytes * 6. The caller still compares the result with the
    // destination texture (DdsCubeMatchesTexture). On failure returns false
    // with `problem` pointing at a static description.
    inline bool ParseDdsCubeBc1(const std::uint8_t* data, std::size_t size,
                                DdsCubeInfo& info, const char*& problem)
    {
        constexpr std::uint32_t kMagic = 0x20534444;       // "DDS "
        constexpr std::uint32_t kFourccDxt1 = 0x31545844;  // "DXT1"
        constexpr std::uint32_t kPfFourcc = 0x4;
        constexpr std::uint32_t kCapsComplex = 0x8;
        constexpr std::uint32_t kCaps2Cubemap = 0x200;
        constexpr std::uint32_t kCaps2AllFaces = 0xFC00;
        constexpr std::size_t kHeaderBytes = 128;

        info = DdsCubeInfo{};
        problem = nullptr;
        if (!data || size < kHeaderBytes)
        {
            problem = "file too small";
            return false;
        }
        if (ReadLe32(data) != kMagic || ReadLe32(data + 4) != 124 ||
            ReadLe32(data + 76) != 32)
        {
            problem = "not a DDS header";
            return false;
        }
        if ((ReadLe32(data + 80) & kPfFourcc) == 0 || ReadLe32(data + 84) != kFourccDxt1)
        {
            problem = "not DXT1";
            return false;
        }
        const std::uint32_t caps = ReadLe32(data + 108);
        const std::uint32_t caps2 = ReadLe32(data + 112);
        if ((caps & kCapsComplex) == 0 || (caps2 & kCaps2Cubemap) == 0 ||
            (caps2 & kCaps2AllFaces) != kCaps2AllFaces)
        {
            problem = "not a six-face cubemap";
            return false;
        }
        info.height = ReadLe32(data + 12);
        info.width = ReadLe32(data + 16);
        info.mipLevels = ReadLe32(data + 28);
        if (info.mipLevels == 0)
            info.mipLevels = 1;
        if (info.width == 0 || info.height == 0 || info.width != info.height ||
            info.mipLevels > 16)
        {
            problem = "bad cube dimensions";
            return false;
        }
        info.dataOffset = kHeaderBytes;
        if (size - kHeaderBytes !=
            6 * Bc1FaceBytes(info.width, info.height, info.mipLevels))
        {
            problem = "payload size mismatch";
            return false;
        }
        return true;
    }

    // DXGI_FORMAT_BC1_TYPELESS / BC1_UNORM / BC1_UNORM_SRGB.
    inline bool IsBc1DxgiFormat(std::uint32_t format)
    {
        return format >= 70 && format <= 72;
    }

    // True when a parsed file can be copied into a destination with these
    // D3D11 properties: same size, and at least as many mips as the
    // destination. Ogre may load the neutral cubes with fewer mips than the
    // file holds, or expand a single-mip file to a full chain, so the copy
    // goes per subresource for the destination's mip count.
    inline bool DdsCubeMatchesTexture(const DdsCubeInfo& info, std::uint32_t width,
                                      std::uint32_t height, std::uint32_t mipLevels,
                                      std::uint32_t arraySize, std::uint32_t dxgiFormat,
                                      bool isCube)
    {
        return isCube && arraySize == 6 && IsBc1DxgiFormat(dxgiFormat) &&
               info.width == width && info.height == height &&
               mipLevels != 0 && info.mipLevels >= mipLevels;
    }
}
