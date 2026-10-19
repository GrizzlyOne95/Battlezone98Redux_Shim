#pragma once

#include <cctype>
#include <cstdlib>
#include <cstdint>
#include <cstring>

namespace BZROpenShim::CameraFovPolicy
{
    // Redux's base angle is horizontal at 4:3, rather than the final
    // horizontal angle at the current display aspect ratio.
    constexpr uint32_t kStockFovBits = 0x3FB2B8C2; // 80 degrees, in radians

    inline int ParseDegrees(const char* text)
    {
        if (!text)
            return 0;
        char* end = nullptr;
        const long degrees = std::strtol(text, &end, 10);
        if (end == text)
            return 0;
        while (*end && std::isspace(static_cast<unsigned char>(*end)))
            ++end;
        return *end == '\0' && degrees >= 60 && degrees <= 120
            ? static_cast<int>(degrees) : 0;
    }

    inline uint32_t SelectFovBits(uint32_t original, int degrees, bool playerView)
    {
        // Unknown callers and nonstandard angles keep the engine's input.
        if (!playerView || original != kStockFovBits || degrees < 60 || degrees > 120)
            return original;
        const float radians = degrees * (3.14159265358979323846f / 180.0f);
        uint32_t bits = 0;
        std::memcpy(&bits, &radians, sizeof(bits));
        return bits;
    }
}
