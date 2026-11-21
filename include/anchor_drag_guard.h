// anchor_drag_guard.h -- engine-independent logic for the AnchorRocket drag
// guard (src/patches/anchor_drag_guard.cpp).
//
// AnchorRocket::Simulate (0x0046D8C0, GOG Redux 2.2.301) brakes the latched
// target once per frame, first its velocity, then its spin:
//   drag = class->accelDrag (or alphaDrag) * dt
//   if (speed <= drag) v = 0; else v *= 1 - drag / speed;
// A custom ODF with a negative drag turns the brake into a boost, and then:
//   - speed 0 (a building), a denormal speed (Redux flushes denormals, so the
//     divide sees 0) or a tiny normal speed gives a factor of +inf or a huge
//     finite one; 0 * inf = NaN lands in the target's velocity or omega;
//   - any real speed is multiplied every frame without bound while the
//     anchor holds, which flings the unit off the map or breaks the rotation
//     integration.
// The guard keeps the stock result for every positive drag and for every
// real speed, takes the zero branch for a non-real speed, and caps a boost.
//
// Header-only and free of Windows and engine dependencies so that
// tests/anchor_drag_guard_tests.cpp can drive it.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
namespace AnchorDrag
{
    // Below this a speed (m/s) or spin (rad/s) is treated as zero: the
    // divide by it would give an infinite or meaningless factor.
    constexpr float kMinSpeed = 1e-4f;

    // A negative-drag boost may raise a speed to at most max(speed, cap).
    // Without a cap the linear boost compounds every frame while the anchor
    // holds and flings units off the map or breaks the rotation integration.
    constexpr float kLinearBoostCap = 100.0f;  // m/s
    constexpr float kAngularBoostCap = 10.0f;  // rad/s

    struct Decision
    {
        bool zero;   // take the stock "v = 0" branch
        float drag;  // drag value the stock "v *= 1 - drag / speed" branch uses
    };

    // speed: the magnitude the stock code compares; drag: the per-frame drag
    // it computed; cap: kLinearBoostCap or kAngularBoostCap.
    inline Decision Decide(float speed, float drag, float cap)
    {
        // Stock: comiss speed, drag; jbe zero. Unordered (NaN) also jumps.
        if (!(speed > drag))
            return { true, drag };
        // Positive drag keeps the stock result: speed > drag > 0 already
        // gives a finite factor in [0, 1). Only a non-positive drag can
        // divide by a zero (flushed denormal) or tiny speed.
        // Zero drag: 0 / flushed-denormal is 0/0 = NaN; a normal speed is fine.
        if (drag == 0.0f && !(speed >= 1.17549435e-38f))  // FLT_MIN
            return { true, drag };
        // Negative drag (boost): speed 0, denormal or tiny gives an infinite
        // or meaningless factor.
        if (drag < 0.0f && !(speed > kMinSpeed))
            return { true, drag };
        if (drag < 0.0f)
        {
            // Stock factor 1 - drag / speed > 1. Result speed * factor =
            // speed - drag; limit it to max(speed, cap). Rewriting drag as
            // speed - limit makes the stock divide yield limit / speed.
            const float limit = speed > cap ? speed : cap;
            if (speed - drag > limit)
                return { false, speed - limit };
        }
        return { false, drag };
    }
}
}
