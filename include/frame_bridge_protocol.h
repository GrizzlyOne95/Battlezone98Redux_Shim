#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace BZROpenShim::FrameBridge
{
    constexpr std::uint32_t kMagic = 0x3146424f; // OBF1
    constexpr std::uint32_t kVersion = 1;
    constexpr std::uint32_t kMaxDimension = 8192;
    enum class SlotState : std::int32_t { Free = 0, Writing = 1, Ready = 2, Reading = 3 };

    // Cross-process wire ABI: no pointers, size_t, COM interfaces, or std::atomic.
    // Handles belong to producerPid and MUST be duplicated before use. All
    // mutable fields are protected by the slot state, except active/consumerPid,
    // which use Win32 interlocked operations. Interlocked publication supplies
    // CPU ordering; the shared fence supplies GPU ordering.
    struct alignas(64) SharedFrame
    {
        std::uint32_t magic;
        std::uint32_t version;
        std::uint32_t byteSize;
        std::uint32_t producerPid;
        std::uint32_t width;
        std::uint32_t height;
        std::uint32_t format;
        std::uint32_t adapterLuidLow;
        std::int32_t adapterLuidHigh;
        std::int32_t active;
        std::int32_t consumerPid;
        std::int32_t slotState;
        std::uint64_t textureHandle;
        std::uint64_t readyFenceHandle;
        std::uint64_t frameId;
        std::uint64_t captureQpc;
        std::uint64_t qpcFrequency;
        std::uint64_t reserved[5];
    };
    static_assert(std::is_standard_layout_v<SharedFrame>);
    static_assert(sizeof(SharedFrame) == 128);
    static_assert(offsetof(SharedFrame, textureHandle) == 48);
    static_assert(offsetof(SharedFrame, frameId) == 64);

    inline bool ValidDescriptor(const SharedFrame& frame, std::uint32_t pid)
    {
        // Only SDR, uncompressed, single-sample color in the initial bridge.
        constexpr std::uint32_t rgba8 = 28;
        constexpr std::uint32_t bgra8 = 87;
        return frame.magic == kMagic && frame.version == kVersion &&
            frame.byteSize == sizeof(SharedFrame) && frame.producerPid == pid &&
            frame.width > 0 && frame.width <= kMaxDimension &&
            frame.height > 0 && frame.height <= kMaxDimension &&
            (frame.format == rgba8 || frame.format == bgra8) &&
            frame.textureHandle != 0 && frame.readyFenceHandle != 0 &&
            frame.qpcFrequency != 0;
    }
}
