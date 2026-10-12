#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include "frame_bridge_camera.h"

namespace BZROpenShim::FrameBridge
{
    constexpr std::uint32_t kMagic = 0x3146424f; // OBF1
    constexpr std::uint32_t kVersion = 3;
    constexpr std::uint32_t kMaxDimension = 8192;
    enum class SlotState : std::int32_t { Free = 0, Writing = 1, Ready = 2, Reading = 3 };
    enum class DepthStatus : std::uint32_t { Disabled = 0, Candidate = 1, Missing = 2, Unsupported = 3, Failed = 4 };

    // Cross-process wire ABI: no pointers, size_t, COM interfaces, or std::atomic.
    // Handles belong to producerPid and MUST be duplicated before use. All
    // mutable fields are protected by the slot state, except active/consumerPid/requestedDepthClear,
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
        std::uint64_t depthTextureHandle; // Optional R32_FLOAT surface; handle/dimensions immutable, pixels slot-owned.
        std::uint32_t depthSourceFormat;
        std::uint32_t depthSourceSamples;
        std::uint32_t depthStatus;
        std::uint32_t depthReduction; // 0=min, 1=max; raw device depth, convention unqualified.
        std::uint32_t depthResult; // HRESULT bits for diagnostics, not a feature-enabled flag.
        std::int32_t requestedDepthClear; // Consumer control: 0=Present, 1..8=nth matching pre-clear.
        std::uint32_t depthCapturedOrdinal;
        std::uint32_t depthMatchingClears;
        CameraSnapshot camera;
        std::uint64_t reserved[2]; // Explicit padding preserves the 64-byte wire alignment.
    };
    static_assert(std::is_standard_layout_v<SharedFrame>);
    static_assert(sizeof(SharedFrame) == 384);
    static_assert(offsetof(SharedFrame, camera) == 128);
    static_assert(offsetof(SharedFrame, textureHandle) == 48);
    static_assert(offsetof(SharedFrame, frameId) == 64);
    static_assert(offsetof(SharedFrame, depthTextureHandle) == 88);
    static_assert(offsetof(SharedFrame, depthStatus) == 104);
    static_assert(offsetof(SharedFrame, requestedDepthClear) == 116);

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

    // Per-frame fields may only be read while the consumer owns Reading.
    inline bool ValidDepthFrame(const SharedFrame& frame)
    {
        const bool format = frame.depthSourceFormat == 39 || frame.depthSourceFormat == 40 ||
            frame.depthSourceFormat == 44 || frame.depthSourceFormat == 45;
        const bool samples = frame.depthSourceSamples == 1 || frame.depthSourceSamples == 2 ||
            frame.depthSourceSamples == 4 || frame.depthSourceSamples == 8;
        return frame.depthTextureHandle != 0 && frame.depthStatus == static_cast<std::uint32_t>(DepthStatus::Candidate) &&
            frame.depthResult == 0 && frame.depthReduction <= 1 && format && samples &&
            (frame.depthCapturedOrdinal == 0 || (frame.depthCapturedOrdinal <= 8 &&
                frame.depthCapturedOrdinal <= frame.depthMatchingClears));
    }
    inline bool ValidCameraFrame(const SharedFrame& frame)
    {
        return ValidDepthFrame(frame) && ValidCameraSnapshot(frame.camera) &&
            frame.camera.width == frame.width && frame.camera.height == frame.height &&
            frame.camera.observationQpc <= frame.captureQpc &&
            frame.camera.clearOrdinal == frame.depthCapturedOrdinal &&
            frame.camera.stage == (frame.depthCapturedOrdinal ? 1u : 0u);
    }
}
