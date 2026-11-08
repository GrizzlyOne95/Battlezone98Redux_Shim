#pragma once
#include <cstdint>

namespace BZROpenShim::MenuTheme
{
    // Called only by the existing, guarded UI image-material owner, on the UI thread.
    void ImageMaterialReady(const char* name, void* materialSlot) noexcept;
    bool RegisterScreen();
    bool ImageAdapterNeeded();
    // Redirects the shell label colour apply call; idempotent, fails closed.
    void InstallTextRecolor();
    constexpr uint32_t ScreenId = 0x4F530004;
}
