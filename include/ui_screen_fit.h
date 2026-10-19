#pragma once
#include <algorithm>
#include <cmath>

namespace BZROpenShim::UiScreenFit
{
    struct Metrics
    {
        float scale = 1, x = 0, y = 0;
        float RelativeToHeight(float height) const { return height > 0 ? std::min(1.0f, scale * 1080.0f / height) : 1.0f; }
    };
    inline Metrics Calculate(float width, float height)
    {
        if (!std::isfinite(width) || !std::isfinite(height) || width <= 0 || height <= 0) return {};
        const float scale = std::min(width / 1440.0f, height / 1080.0f);
        return {scale, (width - 1440.0f * scale) * .5f, (height - 1080.0f * scale) * .5f};
    }
    inline float TextWidthInDesignSpace(float pixels, float clientHeight, float layoutScale = 1)
    {
        return clientHeight > 0 && layoutScale > 0 ? pixels * 1080.0f / (clientHeight * layoutScale) : pixels;
    }
}
