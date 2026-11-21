// nan_transform_guard.h -- engine-independent check/repair logic for the NaN
// transform guard (src/patches/nan_transform_guard.cpp).
//
// GameObject::Simulate (0x004DEEC0, GOG Redux 2.2.301, void __cdecl(obj76*))
// steps one object. obj76+0x20 is its 0x40-byte transform: 9 rotation floats
// (+0x00..+0x23), 4 pad bytes, then the position as doubles at +0x28/+0x30/
// +0x38 (obj76+0x48/+0x50/+0x58). The GameObject (obj76+0x8C) keeps its
// physics block at +0x114: speed float +0x08, velocity float[3] +0x18,
// omega float[3] +0x24. Once any of these is NaN or infinite it spreads to
// everything the object touches and never recovers.
//
// The checks are exponent bit tests (all-ones exponent = NaN or infinity),
// cheap enough for every object every sub-step and free of FPU state.
//
// Header-only and free of Windows and engine dependencies so that
// tests/nan_transform_guard_tests.cpp can drive it.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
namespace NanTransform
{
    constexpr uint32_t kTransformBytes = 0x40;
    constexpr uint32_t kPositionOffset = 0x28;  // within the transform
    constexpr uint32_t kSpeedOffset = 0x08;     // within the physics block
    constexpr uint32_t kVelocityOffset = 0x18;
    constexpr uint32_t kOmegaOffset = 0x24;
    constexpr uint32_t kMotionEnd = kOmegaOffset + 12;

    inline bool FiniteBits32(uint32_t bits) { return (bits & 0x7F800000u) != 0x7F800000u; }
    inline bool FiniteBits64(uint64_t bits) { return (bits & 0x7FF0000000000000ull) != 0x7FF0000000000000ull; }

    inline uint32_t Load32(const uint8_t* p)
    {
        uint32_t v;
        std::memcpy(&v, p, sizeof(v));
        return v;
    }

    inline uint64_t Load64(const uint8_t* p)
    {
        uint64_t v;
        std::memcpy(&v, p, sizeof(v));
        return v;
    }

    inline bool RotationFinite(const uint8_t* transform)
    {
        // Branch-free accumulate: one test at the end.
        uint32_t bad = 0;
        for (uint32_t i = 0; i < 9; ++i)
            bad |= static_cast<uint32_t>(!FiniteBits32(Load32(transform + i * 4)));
        return bad == 0;
    }

    inline bool PositionFinite(const uint8_t* transform)
    {
        const uint8_t* p = transform + kPositionOffset;
        return FiniteBits64(Load64(p)) & FiniteBits64(Load64(p + 8)) & FiniteBits64(Load64(p + 16));
    }

    inline bool TransformFinite(const uint8_t* transform)
    {
        return RotationFinite(transform) & PositionFinite(transform);
    }

    // speed, velocity[3], omega[3] of a physics block.
    inline bool MotionFinite(const uint8_t* physics)
    {
        uint32_t bad = static_cast<uint32_t>(!FiniteBits32(Load32(physics + kSpeedOffset)));
        for (uint32_t i = 0; i < 3; ++i)
        {
            bad |= static_cast<uint32_t>(!FiniteBits32(Load32(physics + kVelocityOffset + i * 4)));
            bad |= static_cast<uint32_t>(!FiniteBits32(Load32(physics + kOmegaOffset + i * 4)));
        }
        return bad == 0;
    }

    inline void ZeroMotion(uint8_t* physics)
    {
        std::memset(physics + kSpeedOffset, 0, 4);
        std::memset(physics + kVelocityOffset, 0, 12);
        std::memset(physics + kOmegaOffset, 0, 12);
    }

    inline void SetIdentityRotation(uint8_t* transform)
    {
        const float identity[9] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        std::memcpy(transform, identity, sizeof(identity));
    }

    enum class Repair
    {
        None,               // transform was finite: nothing changed
        RestoredSnapshot,   // the whole pre-step transform was put back
        IdentityRotation,   // snapshot also bad: rotation reset, position finite and kept
        PositionNotFinite,  // snapshot also bad and the position is not finite: left as is
    };

    inline const char* RepairName(Repair r)
    {
        switch (r)
        {
        case Repair::None: return "none";
        case Repair::RestoredSnapshot: return "restored pre-step transform";
        case Repair::IdentityRotation: return "rotation reset to identity, position kept";
        case Repair::PositionNotFinite: return "position not finite and no finite snapshot; left as is";
        }
        return "?";
    }

    // Post-step repair of `transform` from the pre-step `snapshot`. A finite
    // rotation is kept when only the position is bad; a non-finite rotation
    // becomes identity once no finite snapshot exists.
    inline Repair RepairTransform(uint8_t* transform, const uint8_t* snapshot)
    {
        if (TransformFinite(transform))
            return Repair::None;
        if (TransformFinite(snapshot))
        {
            std::memcpy(transform, snapshot, kTransformBytes);
            return Repair::RestoredSnapshot;
        }
        if (!RotationFinite(transform))
            SetIdentityRotation(transform);
        return PositionFinite(transform) ? Repair::IdentityRotation : Repair::PositionNotFinite;
    }
}
}
