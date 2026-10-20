#pragma once
#include <cstdint>

namespace BZROpenShim::MenuTheme
{
    // Called only by the existing, guarded UI image-material owner, on the UI thread.
    void ImageMaterialReady(const char* name, void* materialSlot) noexcept;
    bool RegisterScreen();
    bool ImageAdapterNeeded();
    constexpr uint32_t ScreenId = 0x4F530004;
}
