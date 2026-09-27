#pragma once

// Named colours for the craft headlight and the pilot flashlight. Both
// settings take the same words so they can share one value list on the
// settings page, and both parsers used to carry this table (audit P2-3).
// Values are in the shim's headlight brightness scale, where the engine's own
// headlight is 1,1,1.

#include <cstring>

namespace BZROpenShim
{
namespace LightColourPresets
{
    struct Preset
    {
        const char* name;
        float r;
        float g;
        float b;
    };

    constexpr Preset kPresets[] = {
        { "white",   5.0f, 5.0f, 5.0f },
        { "red",     5.0f, 1.0f, 1.0f },
        { "green",   1.0f, 5.0f, 1.0f },
        { "blue",    1.0f, 1.0f, 5.0f },
        { "yellow",  5.0f, 5.0f, 1.0f },
        { "cyan",    1.0f, 5.0f, 5.0f },
        { "magenta", 5.0f, 1.0f, 5.0f },
        { "orange",  5.0f, 2.5f, 1.0f },
        { "purple",  2.5f, 1.0f, 5.0f },
        { "teal",    1.0f, 5.0f, 2.5f },
    };

    // `lowerName` must already be lower-case. Leaves r/g/b alone on a miss.
    inline bool TryFind(const char* lowerName, float& r, float& g, float& b)
    {
        if (!lowerName)
            return false;
        for (const Preset& preset : kPresets)
        {
            if (std::strcmp(lowerName, preset.name) == 0)
            {
                r = preset.r;
                g = preset.g;
                b = preset.b;
                return true;
            }
        }
        return false;
    }
}
}
