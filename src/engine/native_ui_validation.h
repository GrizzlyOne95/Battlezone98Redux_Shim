#pragma once

#include <cstddef>
#include <cstdint>

namespace BZROpenShim::NativeUiValidation
{
    inline constexpr uint32_t kOptionsParentHost = 1;
    inline constexpr uint32_t kMainMenuHost = 2;

    struct HostIdentity
    {
        uint32_t host = 0;
        uintptr_t screen = 0;
        uintptr_t parent = 0;
        ptrdiff_t baselineChildCount = -1;
        ptrdiff_t currentChildCount = -1;
        size_t allocatedWidgetCount = 0;
        uint64_t fingerprint = 0;
        uint64_t generation = 0;
    };

    constexpr bool IsSupportedHost(uint32_t host, bool mainMenuEnabled)
    {
        return host == kOptionsParentHost ||
               (mainMenuEnabled && host == kMainMenuHost);
    }

    constexpr bool IsValidHostIdentity(const HostIdentity& identity,
                                       bool mainMenuEnabled)
    {
        return IsSupportedHost(identity.host, mainMenuEnabled) &&
               identity.screen != 0 && identity.parent != 0 &&
               identity.baselineChildCount >= 0 &&
               identity.currentChildCount >= 0 &&
               identity.fingerprint != 0 &&
               (identity.host != kMainMenuHost || identity.generation != 0) &&
               identity.currentChildCount ==
                   identity.baselineChildCount +
                       static_cast<ptrdiff_t>(identity.allocatedWidgetCount);
    }

    constexpr bool SameHostLifetime(const HostIdentity& expected,
                                    const HostIdentity& current,
                                    bool mainMenuEnabled)
    {
        return IsValidHostIdentity(expected, mainMenuEnabled) &&
               IsValidHostIdentity(current, mainMenuEnabled) &&
               expected.host == current.host &&
               expected.screen == current.screen &&
               expected.parent == current.parent &&
               expected.fingerprint == current.fingerprint &&
               expected.generation == current.generation;
    }

    constexpr bool EffectiveVisibility(bool surfaceLive,
                                       bool surfaceVisible,
                                       bool widgetRequestedVisible)
    {
        return surfaceLive && surfaceVisible && widgetRequestedVisible;
    }

    // Cached widget pointers are valid only while the owning parent still
    // contains that exact child. Pointer non-nullness alone is not lifetime
    // evidence because Redux may destroy the lobby and reuse its heap memory.
    constexpr bool CachedChildAccessAllowed(bool ownerCached,
                                            bool childCached,
                                            bool ownerContainsChild)
    {
        return ownerCached && childCached && ownerContainsChild;
    }
}
