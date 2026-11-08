// remote_smoothing_policy.h
// BZR Open Shim - frame-rate-independent display blend for remote objects
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Pure math for [Network] RemoteSmoothingMs (remote_object_smoothing.cpp).
// Stock GameObject::Simulate blends a remote object's displayed transform
// toward its dead-reckoned physics state by a fixed 0.3 (position) and 0.5
// (rotation) per frame, so the smoothing time constant shrinks with frame
// rate. This replaces the factors with 1 - exp(-dt / tau).
// See reverse_engineering/remote_object_smoothing_20261107.md.

#pragma once

#include <cmath>
#include <cstdint>

namespace BZROpenShim
{
    namespace RemoteSmoothing
    {
        // The engine's MAT_3D: three float rows, padding, double position.
        struct Transform
        {
            float m[9];
            float pad;
            double p[3];
        };
        static_assert(sizeof(Transform) == 64, "MAT_3D is 64 bytes");

        // A frame longer than this blends as if it were this long, so a hitch
        // does not turn into a hard snap.
        constexpr double kMaxStepSeconds = 0.1;
        // Rotation settles this many times faster than position, like stock:
        // per-frame 0.5 against 0.3 is ln(0.5) / ln(0.7) = 1.94.
        constexpr double kRotationTauDivisor = 1.94;
        // A correction this large is a respawn or teleport, not jitter.
        constexpr double kSnapDistance = 15.0;
        constexpr int kMinTauMs = 0;
        constexpr int kMaxTauMs = 300;

        enum class Outcome
        {
            Blended,
            Snapped,
            Skipped,  // input not a finite rotation; leave the stock result
        };

        inline int ClampTauMs(int value)
        {
            return value < kMinTauMs ? kMinTauMs : (value > kMaxTauMs ? kMaxTauMs : value);
        }

        inline double BlendAlpha(double dtSeconds, double tauSeconds)
        {
            if (!(tauSeconds > 0.0)) return 1.0;
            if (!(dtSeconds > 0.0)) return 0.0;  // also catches NaN
            if (dtSeconds > kMaxStepSeconds) dtSeconds = kMaxStepSeconds;
            return 1.0 - std::exp(-dtSeconds / tauSeconds);
        }

        // Orthonormal rows with determinant +1, within a loose tolerance:
        // the engine renormalizes on its own schedule.
        inline bool IsRotation(const float (&m)[9])
        {
            for (float v : m)
                if (!std::isfinite(v)) return false;
            const auto dot = [&m](int a, int b) {
                return static_cast<double>(m[a * 3]) * m[b * 3] +
                       static_cast<double>(m[a * 3 + 1]) * m[b * 3 + 1] +
                       static_cast<double>(m[a * 3 + 2]) * m[b * 3 + 2];
            };
            constexpr double kTol = 0.02;
            for (int r = 0; r < 3; ++r)
                if (std::fabs(dot(r, r) - 1.0) > kTol) return false;
            if (std::fabs(dot(0, 1)) > kTol || std::fabs(dot(0, 2)) > kTol || std::fabs(dot(1, 2)) > kTol)
                return false;
            const double det =
                static_cast<double>(m[0]) * (static_cast<double>(m[4]) * m[8] - static_cast<double>(m[5]) * m[7]) -
                static_cast<double>(m[1]) * (static_cast<double>(m[3]) * m[8] - static_cast<double>(m[5]) * m[6]) +
                static_cast<double>(m[2]) * (static_cast<double>(m[3]) * m[7] - static_cast<double>(m[4]) * m[6]);
            return det > 0.0;
        }

        struct Quat
        {
            double w, x, y, z;
        };

        // Row-major m[r*3+c]. MatrixToQuat and QuatToMatrix are exact inverses
        // of each other for a rotation; which way the engine reads its rows
        // does not matter as long as both directions use the same convention.
        inline Quat MatrixToQuat(const float (&m)[9])
        {
            const double m00 = m[0], m01 = m[1], m02 = m[2];
            const double m10 = m[3], m11 = m[4], m12 = m[5];
            const double m20 = m[6], m21 = m[7], m22 = m[8];
            const double trace = m00 + m11 + m22;
            Quat q{};
            if (trace > 0.0)
            {
                const double s = std::sqrt(trace + 1.0) * 2.0;
                q.w = 0.25 * s;
                q.x = (m21 - m12) / s;
                q.y = (m02 - m20) / s;
                q.z = (m10 - m01) / s;
            }
            else if (m00 > m11 && m00 > m22)
            {
                const double s = std::sqrt(1.0 + m00 - m11 - m22) * 2.0;
                q.w = (m21 - m12) / s;
                q.x = 0.25 * s;
                q.y = (m01 + m10) / s;
                q.z = (m02 + m20) / s;
            }
            else if (m11 > m22)
            {
                const double s = std::sqrt(1.0 + m11 - m00 - m22) * 2.0;
                q.w = (m02 - m20) / s;
                q.x = (m01 + m10) / s;
                q.y = 0.25 * s;
                q.z = (m12 + m21) / s;
            }
            else
            {
                const double s = std::sqrt(1.0 + m22 - m00 - m11) * 2.0;
                q.w = (m10 - m01) / s;
                q.x = (m02 + m20) / s;
                q.y = (m12 + m21) / s;
                q.z = 0.25 * s;
            }
            const double n = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
            q.w /= n; q.x /= n; q.y /= n; q.z /= n;
            return q;
        }

        inline void QuatToMatrix(const Quat& q, float (&m)[9])
        {
            const double w = q.w, x = q.x, y = q.y, z = q.z;
            m[0] = static_cast<float>(1.0 - 2.0 * (y * y + z * z));
            m[1] = static_cast<float>(2.0 * (x * y - w * z));
            m[2] = static_cast<float>(2.0 * (x * z + w * y));
            m[3] = static_cast<float>(2.0 * (x * y + w * z));
            m[4] = static_cast<float>(1.0 - 2.0 * (x * x + z * z));
            m[5] = static_cast<float>(2.0 * (y * z - w * x));
            m[6] = static_cast<float>(2.0 * (x * z - w * y));
            m[7] = static_cast<float>(2.0 * (y * z + w * x));
            m[8] = static_cast<float>(1.0 - 2.0 * (x * x + y * y));
        }

        // Shortest-arc slerp; normalized lerp when the two are nearly equal.
        inline Quat Slerp(Quat a, const Quat& b, double t)
        {
            double cosTheta = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
            if (cosTheta < 0.0)
            {
                a = {-a.w, -a.x, -a.y, -a.z};
                cosTheta = -cosTheta;
            }
            double wa = 1.0 - t, wb = t;
            if (cosTheta < 0.9995)
            {
                const double theta = std::acos(cosTheta);
                const double sinTheta = std::sin(theta);
                wa = std::sin((1.0 - t) * theta) / sinTheta;
                wb = std::sin(t * theta) / sinTheta;
            }
            Quat r{wa * a.w + wb * b.w, wa * a.x + wb * b.x, wa * a.y + wb * b.y, wa * a.z + wb * b.z};
            const double n = std::sqrt(r.w * r.w + r.x * r.x + r.y * r.y + r.z * r.z);
            r.w /= n; r.x /= n; r.y /= n; r.z /= n;
            return r;
        }

        // previous: the displayed transform at the start of the frame.
        // target:   the physics state the engine just dead-reckoned.
        inline Outcome Blend(const Transform& previous, const Transform& target,
                             double dtSeconds, double tauSeconds, Transform& out)
        {
            for (int i = 0; i < 3; ++i)
                if (!std::isfinite(previous.p[i]) || !std::isfinite(target.p[i])) return Outcome::Skipped;
            if (!IsRotation(previous.m) || !IsRotation(target.m)) return Outcome::Skipped;

            out = target;
            const double dx = target.p[0] - previous.p[0];
            const double dy = target.p[1] - previous.p[1];
            const double dz = target.p[2] - previous.p[2];
            if (dx * dx + dy * dy + dz * dz > kSnapDistance * kSnapDistance) return Outcome::Snapped;

            const double alpha = BlendAlpha(dtSeconds, tauSeconds);
            const double alphaRot = BlendAlpha(dtSeconds, tauSeconds / kRotationTauDivisor);
            out.p[0] = previous.p[0] + dx * alpha;
            out.p[1] = previous.p[1] + dy * alpha;
            out.p[2] = previous.p[2] + dz * alpha;
            QuatToMatrix(Slerp(MatrixToQuat(previous.m), MatrixToQuat(target.m), alphaRot), out.m);
            return Outcome::Blended;
        }
    }
}
