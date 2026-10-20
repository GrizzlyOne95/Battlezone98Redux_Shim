#pragma once
#include <cmath>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

namespace BZROpenShim::TerrainHeight
{
    inline constexpr unsigned kDomainShaderSetterSlot = 64;
    struct Image { uint32_t width, height; std::vector<float> values; };
    // Deliberately narrow interchange: legacy D3DFMT_R32F, one linear mip,
    // signed unit heights. No color conversion, compressed data or DDS arrays.
    inline Image Decode(const std::vector<uint8_t>& bytes)
    {
        auto word = [&](size_t offset) {
            if (offset + 4 > bytes.size()) throw std::runtime_error("truncated height DDS");
            uint32_t value; std::memcpy(&value, bytes.data() + offset, 4); return value;
        };
        if (bytes.size() < 128 || std::memcmp(bytes.data(), "DDS ", 4) ||
            word(4) != 124 || word(76) != 32 || word(80) != 4 || word(84) != 114 ||
            word(24) != 0 || word(28) > 1 || word(112) != 0)
            throw std::runtime_error("height needs one-mip linear R32F 2D DDS");
        Image image{word(16), word(12), {}};
        if (image.width < 16 || image.height < 16 || image.width > 4096 || image.height > 4096 ||
            word(20) != image.width * 4 || bytes.size() != 128ull + image.width * image.height * 4ull)
            throw std::runtime_error("invalid height dimensions or payload");
        image.values.resize(size_t(image.width) * image.height);
        std::memcpy(image.values.data(), bytes.data() + 128, image.values.size() * 4);
        for (float value : image.values)
            if (!std::isfinite(value) || std::abs(value) > 1.0f)
                throw std::runtime_error("height samples must be finite signed units within -1..1");
        return image;
    }
}
