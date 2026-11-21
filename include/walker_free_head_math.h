#pragma once

// Engine-independent math for the walker free-turning head
// (src/patches/walker_free_head.cpp, Docs/WALKER_FREE_HEAD.md).
//
// Frame swap: the walker's root transform is the head. Around the stock
// Walker::Simulate the root is turned to the legs frame (the head yawed by
// -delta about its up axis), so stock locomotion and the walk clip see the
// legs heading, then turned back to the head. delta is the head's yaw
// relative to the legs, + = head left of the legs (the sense of +omega.y
// and of +ctrl.steer). The head is world-stabilised: turning the legs does
// not drag the aim, except against a yaw limit.
//
// Vectors and the yaw convention are the tracked turret's
// (tracked_vehicle_turret.h): MAT_3D rows (right, up, front), Yaw(a) has
// front = (sin a, 0, cos a), so a positive a turns the front toward +right.

#include "tracked_vehicle_turret.h"

#include <cmath>

namespace BZROpenShim::WalkerFreeHead
{
    using Vec3 = TrackedPhysics::Vec3;
    namespace TU = TrackedTurret;

    // [WalkerClass] defaults (Docs/WALKER_FREE_HEAD.md): slightly faster
    // than the tank turret, since the head carries the aim.
    constexpr float kDefaultYawRate = 2.5f;   // rad/s
    constexpr float kDefaultYawAlpha = 8.0f;  // rad/s^2
    // UserProcess::Execute scales the analog steer axis global by 1/65536.
    constexpr float kAxisScale = 1.0f / 65536.0f;

    inline TU::Config DefaultConfig()
    {
        TU::Config c;
        c.yawRate = kDefaultYawRate;
        c.yawAlpha = kDefaultYawAlpha;
        return c;
    }

    // The tank's sanitising (rate/alpha clamps, limits kept only when
    // yawMin <= 0 <= yawMax inside +-pi), with the walker defaults for a
    // missing or unusable rate/alpha.
    inline TU::Config SanitizeConfig(TU::Config c)
    {
        if (!(std::isfinite(c.yawRate) && c.yawRate > 0.0f))
            c.yawRate = kDefaultYawRate;
        if (!(std::isfinite(c.yawAlpha) && c.yawAlpha > 0.0f))
            c.yawAlpha = kDefaultYawAlpha;
        return TU::Sanitize(c);
    }

    // Head command from the raw analog steer axis (mouse HorizVel, 16.16).
    inline float MouseCommand(int rawAxis)
    {
        const float v = static_cast<float>(rawAxis) * kAxisScale;
        return std::isfinite(v) ? TrackedPhysics::Clamp(v, -1.0f, 1.0f) : 0.0f;
    }

    // Legs turn command, + turns the legs left: the steer arrow keys
    // (left minus right, as UserProcess::Execute builds the digital steer)
    // plus the strafe keys, A turning left (ctrl.strafe is +1 for D).
    inline float LegTurnCommand(int steerLeft, int steerRight, float strafe)
    {
        if (!std::isfinite(strafe))
            strafe = 0.0f;
        const float keys = static_cast<float>((steerLeft ? 1 : 0) - (steerRight ? 1 : 0));
        return TrackedPhysics::Clamp(keys - strafe, -1.0f, 1.0f);
    }

    // Swap in: the legs' right/front from the head's, sharing its up.
    inline void LegsAxes(Vec3 headRight, Vec3 headFront, float delta, Vec3& legsRight, Vec3& legsFront)
    {
        TU::HullAxes(headRight, headFront, delta, legsRight, legsFront);
    }

    // Swap out: the head's right/front from the legs', sharing its up.
    inline void HeadAxes(Vec3 legsRight, Vec3 legsFront, float delta, Vec3& headRight, Vec3& headFront)
    {
        TU::HullAxes(legsRight, legsFront, -delta, headRight, headFront);
    }

    // Signed yaw (+ left) that turns `before` into `after` about `up`; both
    // are projected onto the plane normal to up first. 0 for degenerate input.
    inline float YawChangeLeft(Vec3 before, Vec3 after, Vec3 up)
    {
        namespace TP = TrackedPhysics;
        const Vec3 n = TP::NormalizeOr(up, Vec3{ 0.0f, 1.0f, 0.0f });
        const Vec3 b = TP::Sub(before, TP::Scale(n, TP::Dot(before, n)));
        const Vec3 a = TP::Sub(after, TP::Scale(n, TP::Dot(after, n)));
        const float sinPart = TP::Dot(TP::Cross(b, a), n);  // > 0 turning right
        const float cosPart = TP::Dot(b, a);
        if (!(std::fabs(sinPart) + std::fabs(cosPart) > 1.0e-12f))
            return 0.0f;
        const float yaw = -std::atan2(sinPart, cosPart);
        return std::isfinite(yaw) ? yaw : 0.0f;
    }

    // delta after one Simulate: the head moved by headStep (its own slew),
    // the legs by legsTurn (both + left, radians). Clamped to the limits
    // (the clamp drags the head with the legs), else wrapped to +-pi.
    inline float NextDelta(const TU::Config& c, float delta, float headStep, float legsTurn)
    {
        if (!std::isfinite(delta))
            delta = 0.0f;
        if (!std::isfinite(headStep))
            headStep = 0.0f;
        if (!std::isfinite(legsTurn))
            legsTurn = 0.0f;
        const float next = delta + headStep - legsTurn;
        return c.limited ? TrackedPhysics::Clamp(next, c.yawMin, c.yawMax) : TU::WrapAngle(next);
    }

    // Decision-log helper: with mouse-only input ctrl.steer (the raw axis
    // low-passed at 5/s) and the raw axis must agree in sign, or both sit
    // near zero.
    inline bool SteerTracksMouse(float mouse, float steer, float deadZone = 0.05f)
    {
        if (!std::isfinite(mouse) || !std::isfinite(steer))
            return false;
        const bool mouseIdle = std::fabs(mouse) < deadZone;
        const bool steerIdle = std::fabs(steer) < deadZone;
        if (mouseIdle || steerIdle)
            return mouseIdle == steerIdle || std::fabs(mouse - steer) < 2.0f * deadZone;
        return (mouse > 0.0f) == (steer > 0.0f);
    }
}
