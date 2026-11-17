#pragma once

// Engine-independent turret math for `classLabel = "tracked"` with a
// [TrackedClass] turretName (src/patches/tracked_vehicle_class.cpp,
// Docs/TRACKED_VEHICLES.md "Rotating turret").
//
// The object's root transform is the turret: camera, reticle, stock weapon
// aim and the stock AI steering all act on it. The hull is the root yawed
// by -delta about the root's up axis, where delta is the turret's yaw
// relative to the hull (+ = turret left of the hull, the sense of
// +omega.y). The contact model runs on the hull frame; the root's yaw rate
// is the hull's plus the turret's slew rate.
//
// Matrices are Redux MAT_3D rows (right, up, front) used as row vectors:
// world = local * parent. Yaw(a) is the engine's yaw builder layout,
// right = (c, 0, -s), front = (s, 0, c).

#include "tracked_vehicle_physics.h"

#include <cmath>

namespace BZROpenShim::TrackedTurret
{
    using Vec3 = TrackedPhysics::Vec3;

    constexpr float kPi = 3.14159265358979f;
    constexpr float kDefaultYawRate = 2.0f;   // rad/s, BZCC AssaultTankClass yawRate default
    constexpr float kDefaultYawAlpha = 5.0f;  // rad/s^2, BZCC yawAlpha default
    constexpr float kMinYawRate = 0.05f;
    constexpr float kMaxYawRate = 20.0f;
    constexpr float kMinYawAlpha = 0.1f;
    constexpr float kMaxYawAlpha = 200.0f;
    // AI hull steering: steer per radian of heading error, and the intent
    // length under which the hull holds still.
    constexpr float kAiSteerGain = 2.0f;
    constexpr float kAiDeadZone = 0.05f;

    struct Config
    {
        float yawRate = kDefaultYawRate;
        float yawAlpha = kDefaultYawAlpha;
        // Turret yaw limits relative to the hull, radians; limited only
        // while both are set and yawMin <= 0 <= yawMax.
        float yawMin = -1.0e30f;
        float yawMax = 1.0e30f;
        bool limited = false;
    };

    inline Config Sanitize(Config c)
    {
        Config out;
        out.yawRate = std::isfinite(c.yawRate) && c.yawRate > 0.0f
            ? TrackedPhysics::Clamp(c.yawRate, kMinYawRate, kMaxYawRate) : kDefaultYawRate;
        out.yawAlpha = std::isfinite(c.yawAlpha) && c.yawAlpha > 0.0f
            ? TrackedPhysics::Clamp(c.yawAlpha, kMinYawAlpha, kMaxYawAlpha) : kDefaultYawAlpha;
        const bool minSet = std::isfinite(c.yawMin) && c.yawMin > -kPi;
        const bool maxSet = std::isfinite(c.yawMax) && c.yawMax < kPi;
        if ((minSet || maxSet) && (!minSet || c.yawMin <= 0.0f) && (!maxSet || c.yawMax >= 0.0f))
        {
            out.limited = true;
            out.yawMin = minSet ? c.yawMin : -kPi;
            out.yawMax = maxSet ? c.yawMax : kPi;
        }
        return out;
    }

    inline float WrapAngle(float a)
    {
        if (!std::isfinite(a))
            return 0.0f;
        a = std::fmod(a + kPi, 2.0f * kPi);
        if (a < 0.0f)
            a += 2.0f * kPi;
        return a - kPi;
    }

    // New turret slew rate (rad/s relative to the hull): toward
    // command * yawRate at no more than yawAlpha, and never past a limit
    // within this step.
    inline float SlewRate(const Config& c, float rate, float command, float delta, float dt)
    {
        if (!std::isfinite(rate))
            rate = 0.0f;
        if (!(dt > 0.0f) || !std::isfinite(dt))
            return rate;
        if (!std::isfinite(command))
            command = 0.0f;
        const float target = TrackedPhysics::Clamp(command, -1.0f, 1.0f) * c.yawRate;
        const float step = c.yawAlpha * dt;
        float next = rate + TrackedPhysics::Clamp(target - rate, -step, step);
        if (c.limited)
            next = TrackedPhysics::Clamp(next, (c.yawMin - delta) / dt, (c.yawMax - delta) / dt);
        return next;
    }

    inline float AdvanceDelta(const Config& c, float delta, float rate, float dt)
    {
        const float next = delta + rate * dt;
        if (!std::isfinite(next))
            return 0.0f;
        return c.limited ? TrackedPhysics::Clamp(next, c.yawMin, c.yawMax) : WrapAngle(next);
    }

    // The hull's right and front from the root's, sharing its up.
    inline void HullAxes(Vec3 rootRight, Vec3 rootFront, float delta, Vec3& hullRight, Vec3& hullFront)
    {
        const float c = std::cos(delta);
        const float s = std::sin(delta);
        hullFront = TrackedPhysics::Add(TrackedPhysics::Scale(rootFront, c), TrackedPhysics::Scale(rootRight, s));
        hullRight = TrackedPhysics::Sub(TrackedPhysics::Scale(rootRight, c), TrackedPhysics::Scale(rootFront, s));
    }

    // Root-local omega (x pitch, y yaw, z roll) to the hull's local axes,
    // less the turret's slew.
    inline Vec3 RootToHullOmega(Vec3 omega, float delta, float rate)
    {
        const float c = std::cos(delta);
        const float s = std::sin(delta);
        return { c * omega.x - s * omega.z, omega.y - rate, s * omega.x + c * omega.z };
    }

    // Hull-local alpha back to root-local, plus the slew change over dt.
    inline Vec3 HullToRootAlpha(Vec3 alpha, float delta, float rateChange, float dt)
    {
        const float c = std::cos(delta);
        const float s = std::sin(delta);
        const float slew = dt > 0.0f ? rateChange / dt : 0.0f;
        return { c * alpha.x + s * alpha.z, alpha.y + slew, -s * alpha.x + c * alpha.z };
    }

    struct HullCommand
    {
        float throttle = 0.0f;
        float steer = 0.0f;  // +1 turns the hull left
    };

    // Player: steering (mouse) slews the turret; strafe keys turn the hull
    // (+strafe moves right, so it turns the hull right) and throttle drives it.
    inline HullCommand PlayerHull(float throttle, float strafe)
    {
        HullCommand out;
        out.throttle = std::isfinite(throttle) ? TrackedPhysics::Clamp(throttle, -1.0f, 1.0f) : 0.0f;
        out.steer = std::isfinite(strafe) ? -TrackedPhysics::Clamp(strafe, -1.0f, 1.0f) : 0.0f;
        return out;
    }

    // AI: the stock pilot's throttle/strafe asks to move along
    // throttle * rootFront + strafe * rootRight. The hull turns toward that
    // and drives once it roughly faces it; a reverse request at more than
    // 90 degrees backs up instead.
    inline HullCommand AiHull(float throttle, float strafe, float delta)
    {
        HullCommand out;
        if (!std::isfinite(throttle)) throttle = 0.0f;
        if (!std::isfinite(strafe)) strafe = 0.0f;
        const float c = std::cos(delta);
        const float s = std::sin(delta);
        const float vf = strafe * s + throttle * c;   // along the hull front
        const float vr = strafe * c - throttle * s;   // along the hull right
        const float length = std::sqrt(vf * vf + vr * vr);
        if (!(length >= kAiDeadZone))
            return out;
        const float magnitude = length > 1.0f ? 1.0f : length;
        if (throttle < 0.0f && vf < 0.0f)
        {
            const float error = std::atan2(vr, -vf);  // +: turn left to put the back on it
            out.steer = TrackedPhysics::Clamp(kAiSteerGain * error, -1.0f, 1.0f);
            const float along = std::cos(error);
            out.throttle = -magnitude * (along > 0.0f ? along : 0.0f);
            return out;
        }
        const float error = std::atan2(-vr, vf);      // +: target is to the left
        out.steer = TrackedPhysics::Clamp(kAiSteerGain * error, -1.0f, 1.0f);
        const float along = std::cos(error);
        out.throttle = magnitude * (along > 0.0f ? along : 0.0f);
        return out;
    }

    struct Mat3
    {
        Vec3 right{ 1.0f, 0.0f, 0.0f };
        Vec3 up{ 0.0f, 1.0f, 0.0f };
        Vec3 front{ 0.0f, 0.0f, 1.0f };
    };

    inline Mat3 Yaw(float a)
    {
        const float c = std::cos(a);
        const float s = std::sin(a);
        Mat3 m;
        m.right = { c, 0.0f, -s };
        m.front = { s, 0.0f, c };
        return m;
    }

    // Row vector v * M.
    inline Vec3 Apply(Vec3 v, const Mat3& m)
    {
        return TrackedPhysics::Add(TrackedPhysics::Add(TrackedPhysics::Scale(m.right, v.x),
                                                       TrackedPhysics::Scale(m.up, v.y)),
                                   TrackedPhysics::Scale(m.front, v.z));
    }

    // a * b: a's rows expressed through b.
    inline Mat3 Mul(const Mat3& a, const Mat3& b)
    {
        return { Apply(a.right, b), Apply(a.up, b), Apply(a.front, b) };
    }

    inline Mat3 Transpose(const Mat3& m)
    {
        return { { m.right.x, m.up.x, m.front.x },
                 { m.right.y, m.up.y, m.front.y },
                 { m.right.z, m.up.z, m.front.z } };
    }

    // A root child's local rotation with the hull yawed by delta under the
    // root: rest * Yaw(delta). Its position is rotated the same way.
    inline Mat3 HullChildRotation(const Mat3& rest, float delta)
    {
        return Mul(rest, Yaw(delta));
    }

    // The turret's local rotation that keeps its rest orientation relative
    // to the root while its parent chain (parentRest, parent to root at
    // rest, below a root child yawed by delta) turns with the hull:
    // rest * parentRest * Yaw(delta)^T * parentRest^T.
    inline Mat3 TurretRotation(const Mat3& rest, const Mat3& parentRest, float delta)
    {
        return Mul(Mul(Mul(rest, parentRest), Transpose(Yaw(delta))), Transpose(parentRest));
    }
}
