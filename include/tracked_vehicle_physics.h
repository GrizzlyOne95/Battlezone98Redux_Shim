#pragma once

// Engine-independent contact model for the ODF-driven `classLabel = "tracked"`
// vehicle class (src/patches/tracked_vehicle_class.cpp, Docs/TRACKED_VEHICLES.md).
//
// A reduced take on BZCC's tracked-vehicle contacts: N contact points per
// side along the bottom of the collision box, each sampling the floor
// height and normal; a spring/damper shared by the grounded contacts along
// the footprint plane's normal; gravity; lateral friction (no strafe); and
// differential tread speeds with a pivot turn at standstill. Pitch and roll
// are steered toward the footprint plane rather than produced by contact
// torque. The step is a pure function of its inputs: no clock, no RNG,
// fixed iteration order.
//
// Frames follow Redux's EULER block: veloc and accel are world frame,
// omega and alpha are body frame (x = pitch about right, y = yaw about up,
// z = roll about front). Redux is left-handed with x right, y up, z front;
// +omega.y turns left, +omega.x raises the nose and +omega.z lowers the
// right side (x and z checked live by the hull settling onto slopes: see
// Docs/TRACKED_VEHICLES.md).

#include <cmath>
#include <cstdint>

namespace BZROpenShim::TrackedPhysics
{
    struct Vec3
    {
        float x;
        float y;
        float z;
    };

    constexpr float kGravity = 9.8f;
    // Pitch/roll alignment toward the footprint plane (1/s) and its alpha cap.
    constexpr float kAlignRate = 6.0f;
    constexpr float kAlignAlphaMax = 40.0f;
    // Angular damping applied to pitch/roll while no contact touches ground.
    constexpr float kAirAngularDamping = 0.5f;
    // Traction fades to zero over this many degrees past maxSlope.
    constexpr float kSlopeFadeDeg = 10.0f;
    constexpr int kMaxContactsPerSide = 8;
    // Velocity caps applied every step, in any state.
    constexpr float kMaxSpeed = 150.0f;
    constexpr float kMaxFallSpeed = 60.0f;

    inline Vec3 Add(Vec3 a, Vec3 b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
    inline Vec3 Sub(Vec3 a, Vec3 b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
    inline Vec3 Scale(Vec3 a, float s) { return { a.x * s, a.y * s, a.z * s }; }
    inline float Dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
    inline Vec3 Cross(Vec3 a, Vec3 b)
    {
        return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
    }
    inline float Length(Vec3 a) { return std::sqrt(Dot(a, a)); }
    inline bool Finite(float v) { return std::isfinite(v); }
    inline bool Finite(Vec3 a) { return Finite(a.x) && Finite(a.y) && Finite(a.z); }
    inline Vec3 NormalizeOr(Vec3 a, Vec3 fallback)
    {
        const float len = Length(a);
        if (!(len > 1.0e-6f) || !Finite(len))
            return fallback;
        return Scale(a, 1.0f / len);
    }
    inline float Clamp(float v, float lo, float hi) { return v < lo ? lo : (v > hi ? hi : v); }

    // ParameterDB section/key hash: FNV-1a/32 over the lowercased name.
    constexpr uint32_t OdfHash(const char* name)
    {
        uint32_t result = 0x811C9DC5u;
        for (; *name; ++name)
        {
            unsigned char c = static_cast<unsigned char>(*name);
            if (c >= 'A' && c <= 'Z')
                c = static_cast<unsigned char>(c + ('a' - 'A'));
            result = (result ^ c) * 0x01000193u;
        }
        return result;
    }

    // [TrackedClass] keys. Stiffness and damping are per unit mass, so the
    // tank's mass does not change how it sits: at rest it sinks g/stiffness.
    struct Config
    {
        float stiffness = 400.0f;       // m/s^2 per metre of penetration
        float damping = 40.0f;          // m/s^2 per m/s of normal speed
        int contactsPerSide = 3;
        float lateralFriction = 1.0f;   // sideways grip as a fraction of g
        float maxSlopeDeg = 40.0f;      // full traction up to this slope
    };

    inline Config Sanitize(Config c)
    {
        const Config d{};
        c.stiffness = Finite(c.stiffness) ? Clamp(c.stiffness, 10.0f, 5000.0f) : d.stiffness;
        c.damping = Finite(c.damping) ? Clamp(c.damping, 0.0f, 500.0f) : d.damping;
        c.contactsPerSide = c.contactsPerSide < 2 ? 2
            : (c.contactsPerSide > kMaxContactsPerSide ? kMaxContactsPerSide : c.contactsPerSide);
        c.lateralFriction = Finite(c.lateralFriction) ? Clamp(c.lateralFriction, 0.0f, 5.0f) : d.lateralFriction;
        c.maxSlopeDeg = Finite(c.maxSlopeDeg) ? Clamp(c.maxSlopeDeg, 5.0f, 85.0f) : d.maxSlopeDeg;
        return c;
    }

    // Where the contacts sit, in body coordinates.
    struct Footprint
    {
        float centerX = 0.0f;
        float halfWidth = 1.7f;   // tread centre line offset from centerX
        float backZ = -2.4f;
        float frontZ = 2.4f;
        float bottomY = 0.0f;
    };

    // Treads sit at 85% of the box half width; the rows are inset 10% from
    // each end. An unusable box (non-finite, or under half a metre on an
    // axis) keeps the defaults above.
    inline Footprint FootprintFromBox(Vec3 boxMin, Vec3 boxMax)
    {
        Footprint f{};
        const Vec3 size = Sub(boxMax, boxMin);
        if (!Finite(boxMin) || !Finite(boxMax) || size.x < 0.5f || size.z < 0.5f ||
            size.y < 0.0f || size.x > 200.0f || size.z > 200.0f)
        {
            return f;
        }
        f.centerX = 0.5f * (boxMin.x + boxMax.x);
        f.halfWidth = 0.85f * 0.5f * size.x;
        f.backZ = boxMin.z + 0.1f * size.z;
        f.frontZ = boxMax.z - 0.1f * size.z;
        f.bottomY = boxMin.y;
        return f;
    }

    // Contact height from the engine's own ground reference: the bottom of
    // the object's collision box (obj76+0xB4), which the engine's terrain
    // collision probes. The contacts sit a skin below it, twice the spring's
    // static sink, so the resting hull keeps that probe just above the floor
    // and the engine never has to clamp it. A non-finite or implausible
    // value keeps the fallback (the class box bottom).
    inline float ContactBottom(float engineBottom, float fallback, const Config& rawConfig)
    {
        const float base = Finite(engineBottom) && engineBottom > -50.0f && engineBottom < 50.0f
            ? engineBottom : fallback;
        const Config config = Sanitize(rawConfig);
        const float skin = Clamp(2.0f * kGravity / config.stiffness, 0.05f, 1.0f);
        return base - skin;
    }

    // Hover keys reused by the tracked class, already scaled by the
    // damage performance curve.
    struct Drive
    {
        float velocForward = 20.0f;
        float velocReverse = 10.0f;
        float omegaSpin = 4.0f;    // turn rate at standstill (pivot)
        float omegaTurn = 1.5f;    // turn rate at full forward speed
        float accelThrust = 25.0f;
        float accelBrake = 75.0f;
        float alphaSteer = 5.0f;
    };

    // HoverCraft::Simulate scales its drive keys by this curve of the
    // object's health ratio: full above one half, 0.75..1 down to a quarter,
    // 0.5..0.75 down to zero.
    inline float PerformanceScale(float ratio)
    {
        if (!(ratio == ratio))
            return 0.0f;
        if (ratio >= 0.5f)
            return 1.0f;
        if (ratio >= 0.25f)
            return ratio * 0.5f + 0.75f;
        if (ratio >= 0.0f)
            return 0.5f + ratio;
        return 0.0f;
    }

    struct Body
    {
        double px = 0.0;
        double py = 0.0;
        double pz = 0.0;
        Vec3 right{ 1.0f, 0.0f, 0.0f };
        Vec3 up{ 0.0f, 1.0f, 0.0f };
        Vec3 front{ 0.0f, 0.0f, 1.0f };
        Vec3 veloc{ 0.0f, 0.0f, 0.0f };
        Vec3 omega{ 0.0f, 0.0f, 0.0f };
    };

    struct Inputs
    {
        float throttle = 0.0f;  // -1 reverse .. +1 forward
        float steer = 0.0f;     // +1 turns left (+omega.y)
    };

    struct Result
    {
        Vec3 accel{ 0.0f, -kGravity, 0.0f };
        Vec3 alpha{ 0.0f, 0.0f, 0.0f };
        Vec3 groundNormal{ 0.0f, 1.0f, 0.0f };
        // body.veloc with the into-ground part removed while grounded and
        // the caps applied; the caller writes it back before integrating.
        Vec3 veloc{ 0.0f, 0.0f, 0.0f };
        float groundedFraction = 0.0f;
        float support = 0.0f;     // contact push / weight along the normal, 0..1
        float traction = 0.0f;
        float slopeDeg = 0.0f;
        float leftTread = 0.0f;   // commanded tread speeds, m/s
        float rightTread = 0.0f;
        float maxPenetration = 0.0f;
        int groundedContacts = 0;
        int contacts = 0;
    };

    // Floor height and unit normal under a world point (x, y, z); false
    // when it cannot be sampled. The engine's floor query also sees object
    // floors just above y.
    using FloorFn = bool (*)(void* context, double x, double y, double z, double& height, Vec3& normal);

    // Removes the part of v that points into the ground (Dot(v, n) < 0),
    // then caps the fall speed and the total speed.
    inline Vec3 CorrectVelocity(Vec3 v, Vec3 n, bool grounded)
    {
        if (!Finite(v))
            return { 0.0f, 0.0f, 0.0f };
        if (grounded)
        {
            const float into = Dot(v, n);
            if (into < 0.0f)
                v = Sub(v, Scale(n, into));
        }
        if (v.y < -kMaxFallSpeed)
            v.y = -kMaxFallSpeed;
        const float speed = Length(v);
        if (speed > kMaxSpeed)
            v = Scale(v, kMaxSpeed / speed);
        return v;
    }

    // Commanded forward speed and turn rate after the tread limits: each
    // tread (v -/+ w * halfWidth) stays inside velocForward/velocReverse;
    // forward speed gives way first so the turn rate is kept.
    inline void TreadCommand(const Drive& drive, float halfWidth, float throttle, float steer,
                             float forwardSpeed, float& vCommand, float& wCommand)
    {
        throttle = Clamp(throttle, -1.0f, 1.0f);
        steer = Clamp(steer, -1.0f, 1.0f);
        const float fwdMax = drive.velocForward > 0.0f ? drive.velocForward : 0.0f;
        const float revMax = drive.velocReverse > 0.0f ? drive.velocReverse : 0.0f;
        const float speedFraction = fwdMax > 0.0f ? Clamp(std::fabs(forwardSpeed) / fwdMax, 0.0f, 1.0f) : 0.0f;
        const float turnRate = drive.omegaSpin + (drive.omegaTurn - drive.omegaSpin) * speedFraction;
        float v = throttle >= 0.0f ? throttle * fwdMax : throttle * revMax;
        float w = steer * turnRate;

        const float hw = halfWidth > 0.1f ? halfWidth : 0.1f;
        const float treadMax = fwdMax < revMax ? fwdMax : revMax;
        const float wMax = treadMax / hw;
        w = Clamp(w, -wMax, wMax);
        const float spin = std::fabs(w) * hw;
        v = Clamp(v, -(revMax - spin), fwdMax - spin);
        vCommand = v;
        wCommand = w;
    }

    inline Result Step(const Config& rawConfig, const Footprint& footprint, const Drive& drive,
                       const Body& body, const Inputs& inputs, float dt,
                       FloorFn floorAt, void* context)
    {
        Result out{};
        out.veloc = CorrectVelocity(body.veloc, out.groundNormal, false);
        const Vec3 gravity{ 0.0f, -kGravity, 0.0f };
        if (!(dt > 0.0f) || !Finite(dt) || !floorAt)
            return out;

        const Config config = Sanitize(rawConfig);
        const int perSide = config.contactsPerSide;
        const int total = perSide * 2;
        out.contacts = total;

        float penetrationSum = 0.0f;
        Vec3 normalSum{ 0.0f, 0.0f, 0.0f };
        // Terrain points under the left/right treads and the back/front rows.
        Vec3 sideSum[2] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        Vec3 rowSum[2] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        int sideCount[2] = { 0, 0 };
        int rowCount[2] = { 0, 0 };
        int sampled = 0;

        for (int side = 0; side < 2; ++side)
        {
            const float lx = footprint.centerX + (side == 0 ? -footprint.halfWidth : footprint.halfWidth);
            for (int i = 0; i < perSide; ++i)
            {
                const float t = static_cast<float>(i) / static_cast<float>(perSide - 1);
                const float lz = footprint.backZ + (footprint.frontZ - footprint.backZ) * t;
                const Vec3 r = Add(Add(Scale(body.right, lx), Scale(body.up, footprint.bottomY)),
                                   Scale(body.front, lz));
                const double wx = body.px + r.x;
                const double wy = body.py + r.y;
                const double wz = body.pz + r.z;

                double h = 0.0;
                Vec3 rawNormal{ 0.0f, 1.0f, 0.0f };
                if (!floorAt(context, wx, wy, wz, h, rawNormal) || !std::isfinite(h))
                    continue;
                ++sampled;
                Vec3 n = NormalizeOr(rawNormal, { 0.0f, 1.0f, 0.0f });
                if (n.y < 0.05f)
                    n = { 0.0f, 1.0f, 0.0f };
                normalSum = Add(normalSum, n);

                const Vec3 ground{ r.x, static_cast<float>(h - body.py), r.z };
                sideSum[side] = Add(sideSum[side], ground);
                ++sideCount[side];
                if (i == 0 || i == perSide - 1)
                {
                    const int row = i == 0 ? 0 : 1;
                    rowSum[row] = Add(rowSum[row], ground);
                    ++rowCount[row];
                }

                const float penetration = static_cast<float>(h - wy) * n.y;
                if (!(penetration > 0.0f))
                    continue;
                ++out.groundedContacts;
                penetrationSum += penetration;
                if (penetration > out.maxPenetration)
                    out.maxPenetration = penetration;
            }
        }

        // Footprint plane from the terrain under the rows and treads.
        Vec3 planeNormal{ 0.0f, 1.0f, 0.0f };
        if (sideCount[0] && sideCount[1] && rowCount[0] && rowCount[1])
        {
            const Vec3 along = Sub(Scale(rowSum[1], 1.0f / rowCount[1]), Scale(rowSum[0], 1.0f / rowCount[0]));
            const Vec3 across = Sub(Scale(sideSum[1], 1.0f / sideCount[1]), Scale(sideSum[0], 1.0f / sideCount[0]));
            planeNormal = NormalizeOr(Cross(along, across), planeNormal);
        }
        else if (sampled)
        {
            planeNormal = NormalizeOr(normalSum, planeNormal);
        }
        if (planeNormal.y < 0.05f)
            planeNormal = NormalizeOr(normalSum, Vec3{ 0.0f, 1.0f, 0.0f });
        out.groundNormal = planeNormal;
        out.slopeDeg = std::acos(Clamp(planeNormal.y, -1.0f, 1.0f)) * 57.2957795f;
        out.groundedFraction = static_cast<float>(out.groundedContacts) / static_cast<float>(total);

        // Each grounded contact carries 1/total of the spring and damper.
        // Their sum acts along the footprint normal and is solved implicitly
        // (backward Euler on the normal speed), so a stiff spring stays
        // stable at any step size and the hull rests at a sink of
        // g / stiffness. The ground pushes but never pulls.
        // While grounded the ground stops any motion into it, so the
        // velocity never builds up against the floor.
        Vec3 veloc = CorrectVelocity(body.veloc, planeNormal, out.groundedContacts > 0);
        out.veloc = veloc;

        Vec3 contactAccel{ 0.0f, 0.0f, 0.0f };
        if (out.groundedContacts)
        {
            const float share = out.groundedFraction;
            const float k = config.stiffness * share;
            const float c = config.damping * share;
            const float penetration = penetrationSum / static_cast<float>(out.groundedContacts);
            const float gravityN = Dot(gravity, planeNormal);
            const float normalSpeed = Dot(veloc, planeNormal);
            const float nextSpeed = (normalSpeed + dt * (gravityN + k * penetration)) /
                (1.0f + c * dt + k * dt * dt);
            float push = (nextSpeed - normalSpeed) / dt - gravityN;
            if (push < 0.0f)
                push = 0.0f;
            contactAccel = Scale(planeNormal, push);
            // Grip follows the load the ground carries, not how many contacts
            // touch: one contact on a crowned slope still holds the hull.
            const float weightN = -gravityN;
            out.support = weightN > 0.01f ? Clamp(push / weightN, 0.0f, 1.0f) : 0.0f;
        }

        float slopeFactor = 1.0f;
        if (out.slopeDeg > config.maxSlopeDeg)
            slopeFactor = Clamp(1.0f - (out.slopeDeg - config.maxSlopeDeg) / kSlopeFadeDeg, 0.0f, 1.0f);
        out.traction = out.support * slopeFactor;

        const Vec3 tangentFront = NormalizeOr(Sub(body.front, Scale(planeNormal, Dot(body.front, planeNormal))),
                                              body.front);
        const Vec3 tangentRight = Cross(planeNormal, tangentFront);
        const float forwardSpeed = Dot(veloc, tangentFront);
        const float lateralSpeed = Dot(veloc, tangentRight);

        float vCommand = 0.0f;
        float wCommand = 0.0f;
        TreadCommand(drive, footprint.halfWidth, inputs.throttle, inputs.steer, forwardSpeed, vCommand, wCommand);
        out.leftTread = vCommand - wCommand * footprint.halfWidth;
        out.rightTread = vCommand + wCommand * footprint.halfWidth;

        Vec3 accel = Add(gravity, contactAccel);
        if (out.traction > 0.0f)
        {
            // Hold the commanded tread speed against the slope's pull; the
            // brake limit applies whenever the treads slow the hull down.
            float forward = (vCommand - forwardSpeed) / dt - Dot(gravity, tangentFront);
            const bool speeding = (forward > 0.0f) == (forwardSpeed >= 0.0f) &&
                std::fabs(vCommand) > std::fabs(forwardSpeed);
            const float forwardLimit = speeding ? drive.accelThrust : drive.accelBrake;
            forward = Clamp(forward, -forwardLimit, forwardLimit) * out.traction;

            const float lateralLimit = config.lateralFriction * kGravity;
            float lateral = -lateralSpeed / dt - Dot(gravity, tangentRight);
            lateral = Clamp(lateral, -lateralLimit, lateralLimit) * out.traction;

            accel = Add(accel, Add(Scale(tangentFront, forward), Scale(tangentRight, lateral)));
        }
        out.accel = accel;

        Vec3 alpha{ 0.0f, 0.0f, 0.0f };
        if (out.groundedContacts)
        {
            const float g = out.groundedFraction;
            const float targetPitch = -kAlignRate * Dot(planeNormal, body.front);
            const float targetRoll = kAlignRate * Dot(planeNormal, body.right);
            alpha.x = Clamp((targetPitch - body.omega.x) / dt, -kAlignAlphaMax, kAlignAlphaMax) * g;
            alpha.z = Clamp((targetRoll - body.omega.z) / dt, -kAlignAlphaMax, kAlignAlphaMax) * g;
            alpha.y = Clamp((wCommand - body.omega.y) / dt, -drive.alphaSteer, drive.alphaSteer) * out.traction;
        }
        else
        {
            alpha.x = -kAirAngularDamping * body.omega.x;
            alpha.z = -kAirAngularDamping * body.omega.z;
            alpha.y = -kAirAngularDamping * body.omega.y;
        }
        out.alpha = alpha;

        if (!Finite(out.accel) || !Finite(out.alpha))
        {
            out.accel = gravity;
            out.alpha = { 0.0f, 0.0f, 0.0f };
        }
        return out;
    }
}
