// shell_casing_physics.h
// BZR Open Shim - ShellCasings: the engine-independent part of the casing
// simulation (eject vector, terrain and object contact, class filter), kept
// header-only so the unit tests exercise exactly the code the shim runs.
//
// Everything here works in Ogre render space (right-handed, Y up). The engine
// side converts sim positions and directions into it once per shot, and
// converts back only to sample the terrain (see shell_casings.cpp).
#pragma once

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace BZROpenShim
{
    namespace ShellCasings
    {
        struct Vec3
        {
            float x, y, z;
        };
        // Ogre order: w, x, y, z.
        struct Quat
        {
            float w, x, y, z;
        };

        inline Vec3 Add(Vec3 a, Vec3 b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
        inline Vec3 Sub(Vec3 a, Vec3 b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
        inline Vec3 Scale(Vec3 a, float s) { return {a.x * s, a.y * s, a.z * s}; }
        inline float Dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
        inline Vec3 Cross(Vec3 a, Vec3 b)
        {
            return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
        }
        inline float Length(Vec3 a) { return std::sqrt(Dot(a, a)); }
        inline bool Finite(Vec3 v) { return std::isfinite(v.x) && std::isfinite(v.y) && std::isfinite(v.z); }
        inline Vec3 Normalize(Vec3 a, Vec3 fallback)
        {
            const float length = Length(a);
            if (!(length > 1e-6f) || !std::isfinite(length))
                return fallback;
            return Scale(a, 1.0f / length);
        }

        inline Quat QMul(Quat a, Quat b)
        {
            return {a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
                    a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
                    a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
                    a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w};
        }
        inline Quat QNormalize(Quat q)
        {
            const float n = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
            if (!(n > 1e-8f) || !std::isfinite(n))
                return {1, 0, 0, 0};
            return {q.w / n, q.x / n, q.y / n, q.z / n};
        }
        inline Vec3 Rotate(Quat q, Vec3 v)
        {
            const Quat r = QMul(QMul(q, {0, v.x, v.y, v.z}), {q.w, -q.x, -q.y, -q.z});
            return {r.x, r.y, r.z};
        }
        inline Quat Conjugate(Quat q) { return {q.w, -q.x, -q.y, -q.z}; }

        // Rotation whose local X/Y/Z axes map to the given orthonormal,
        // right-handed world axes (Ogre's Quaternion::FromAxes).
        inline Quat QuatFromAxes(Vec3 x, Vec3 y, Vec3 z)
        {
            const float m00 = x.x, m01 = y.x, m02 = z.x;
            const float m10 = x.y, m11 = y.y, m12 = z.y;
            const float m20 = x.z, m21 = y.z, m22 = z.z;
            const float trace = m00 + m11 + m22;
            Quat q;
            if (trace > 0.0f)
            {
                const float s = std::sqrt(trace + 1.0f) * 2.0f;
                q = {0.25f * s, (m21 - m12) / s, (m02 - m20) / s, (m10 - m01) / s};
            }
            else if (m00 > m11 && m00 > m22)
            {
                const float s = std::sqrt(1.0f + m00 - m11 - m22) * 2.0f;
                q = {(m21 - m12) / s, 0.25f * s, (m01 + m10) / s, (m02 + m20) / s};
            }
            else if (m11 > m22)
            {
                const float s = std::sqrt(1.0f + m11 - m00 - m22) * 2.0f;
                q = {(m02 - m20) / s, (m01 + m10) / s, 0.25f * s, (m12 + m21) / s};
            }
            else
            {
                const float s = std::sqrt(1.0f + m22 - m00 - m11) * 2.0f;
                q = {(m10 - m01) / s, (m02 + m20) / s, (m12 + m21) / s, 0.25f * s};
            }
            return QNormalize(q);
        }

        // Orientation for a casing whose long axis (mesh local +Z) points
        // along `axis`, rolled so local +Y is as close to `up` as possible.
        inline Quat OrientAlong(Vec3 axis, Vec3 up)
        {
            const Vec3 z = Normalize(axis, {0, 0, 1});
            Vec3 y = Sub(up, Scale(z, Dot(up, z)));
            y = Normalize(y, std::fabs(z.y) < 0.9f ? Normalize(Sub(Vec3{0, 1, 0}, Scale(z, z.y)), Vec3{0, 1, 0})
                                                  : Normalize(Sub(Vec3{1, 0, 0}, Scale(z, z.x)), Vec3{1, 0, 0}));
            const Vec3 x = Cross(y, z);
            return QuatFromAxes(x, y, z);
        }

        // World-frame angular velocity applied over dt (first order, renormalised).
        inline Quat IntegrateSpin(Quat q, Vec3 omega, float dt)
        {
            const Quat delta = QMul({0, omega.x, omega.y, omega.z}, q);
            return QNormalize({q.w + 0.5f * dt * delta.w, q.x + 0.5f * dt * delta.x, q.y + 0.5f * dt * delta.y,
                               q.z + 0.5f * dt * delta.z});
        }

        // ---- Sim <-> render space ---------------------------------------------
        // Redux draws around a per-map origin with Z mirrored: render =
        // (x - ox, y - oy, -z - oz). Directions only flip Z.
        inline Vec3 SimToRenderPoint(Vec3 p, Vec3 origin) { return {p.x - origin.x, p.y - origin.y, -p.z - origin.z}; }
        inline Vec3 RenderToSimPoint(Vec3 p, Vec3 origin) { return {p.x + origin.x, p.y + origin.y, -(p.z + origin.z)}; }
        inline Vec3 SimToRenderDir(Vec3 d) { return {d.x, d.y, -d.z}; }

        // ---- Terrain -------------------------------------------------------------
        // Central differences of four height samples taken `step` either side
        // of the point along X and Z (any consistent frame).
        inline Vec3 GroundNormalFromHeights(float hxMinus, float hxPlus, float hzMinus, float hzPlus, float step)
        {
            const Vec3 n = {hxMinus - hxPlus, 2.0f * step, hzMinus - hzPlus};
            return Normalize(n, {0, 1, 0});
        }

        // ---- Contact response ------------------------------------------------------
        struct ContactResponse
        {
            float restitution = 0.35f; // normal speed kept per bounce
            float friction = 0.35f;    // tangential speed lost per bounce
            float spinDamp = 0.6f;     // omega kept per bounce
        };

        // Reflects the velocity relative to a surface moving at surfaceVelocity.
        // Returns the closing speed (>0) when the casing was moving into the
        // surface, else 0 and leaves the velocity untouched.
        inline float Bounce(Vec3& velocity, Vec3& omega, Vec3 normal, Vec3 surfaceVelocity, const ContactResponse& r)
        {
            const Vec3 relative = Sub(velocity, surfaceVelocity);
            const float normalSpeed = Dot(relative, normal);
            if (normalSpeed >= 0.0f)
                return 0.0f;
            const Vec3 normalPart = Scale(normal, normalSpeed);
            const Vec3 tangentPart = Sub(relative, normalPart);
            const Vec3 bounced = Sub(Scale(tangentPart, 1.0f - r.friction), Scale(normalPart, r.restitution));
            velocity = Add(bounced, surfaceVelocity);
            omega = Scale(omega, r.spinDamp);
            return -normalSpeed;
        }

        // ---- Objects ------------------------------------------------------------------
        // An oriented box: centre, three orthonormal axes and half extents.
        struct Obb
        {
            Vec3 center = {0, 0, 0};
            Vec3 axis[3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
            Vec3 half = {0, 0, 0};
        };

        // Box from a local AABB placed by a node (position, orientation,
        // scale), which is how an Ogre entity's mesh bounds reach the world.
        inline Obb ObbFromNode(Vec3 localMin, Vec3 localMax, Vec3 nodePosition, Quat nodeOrientation, Vec3 nodeScale)
        {
            Obb box;
            const Vec3 localCenter = Scale(Add(localMin, localMax), 0.5f);
            const Vec3 scaledCenter = {localCenter.x * nodeScale.x, localCenter.y * nodeScale.y,
                                       localCenter.z * nodeScale.z};
            box.center = Add(nodePosition, Rotate(nodeOrientation, scaledCenter));
            box.axis[0] = Rotate(nodeOrientation, {1, 0, 0});
            box.axis[1] = Rotate(nodeOrientation, {0, 1, 0});
            box.axis[2] = Rotate(nodeOrientation, {0, 0, 1});
            box.half = {std::fabs((localMax.x - localMin.x) * 0.5f * nodeScale.x),
                        std::fabs((localMax.y - localMin.y) * 0.5f * nodeScale.y),
                        std::fabs((localMax.z - localMin.z) * 0.5f * nodeScale.z)};
            return box;
        }

        inline bool PointInsideObb(Vec3 p, const Obb& box, float margin = 0.0f)
        {
            const Vec3 d = Sub(p, box.center);
            return std::fabs(Dot(d, box.axis[0])) <= box.half.x + margin &&
                   std::fabs(Dot(d, box.axis[1])) <= box.half.y + margin &&
                   std::fabs(Dot(d, box.axis[2])) <= box.half.z + margin;
        }

        struct Contact
        {
            bool hit = false;
            Vec3 normal = {0, 1, 0}; // world, pointing out of the box
            float depth = 0.0f;      // how far to move along normal to separate
        };

        // Sphere against oriented box. A centre outside the box is pushed
        // away from the closest surface point; a centre inside leaves through
        // the face of least penetration (for a hull, usually the deck).
        inline Contact SphereVsObb(Vec3 center, float radius, const Obb& box)
        {
            Contact contact;
            const Vec3 d = Sub(center, box.center);
            const float local[3] = {Dot(d, box.axis[0]), Dot(d, box.axis[1]), Dot(d, box.axis[2])};
            const float half[3] = {box.half.x, box.half.y, box.half.z};
            float clamped[3];
            bool inside = true;
            for (int i = 0; i < 3; ++i)
            {
                clamped[i] = std::max(-half[i], std::min(half[i], local[i]));
                if (clamped[i] != local[i])
                    inside = false;
            }
            if (!inside)
            {
                Vec3 closest = box.center;
                for (int i = 0; i < 3; ++i)
                    closest = Add(closest, Scale(box.axis[i], clamped[i]));
                const Vec3 away = Sub(center, closest);
                const float distance = Length(away);
                if (distance >= radius || !(distance > 1e-6f))
                    return contact;
                contact.hit = true;
                contact.normal = Scale(away, 1.0f / distance);
                contact.depth = radius - distance;
                return contact;
            }
            int best = 0;
            float bestDepth = 1e30f;
            for (int i = 0; i < 3; ++i)
            {
                const float depth = half[i] - std::fabs(local[i]);
                // Ties go to Y, the box's up axis: casings settle on decks.
                if (depth < bestDepth - 1e-5f || (i == 1 && depth <= bestDepth + 1e-5f))
                {
                    best = i;
                    bestDepth = depth;
                }
            }
            contact.hit = true;
            contact.normal = Scale(box.axis[best], local[best] < 0.0f ? -1.0f : 1.0f);
            contact.depth = bestDepth + radius;
            return contact;
        }

        // ---- Ejection --------------------------------------------------------------
        // The weapon frame at the moment of the shot, in render space.
        struct MuzzleFrame
        {
            Vec3 position = {0, 0, 0};
            Vec3 right = {1, 0, 0};
            Vec3 up = {0, 1, 0};
            Vec3 front = {0, 0, 1};
        };

        struct EjectParams
        {
            float barrelLength = 2.0f;   // metres from muzzle back to the breech
            float breechFraction = 0.6f; // how far back along it the port sits
            float portUp = 0.15f;        // port height above the barrel axis
            float speed = 3.5f;          // ejection speed (m/s)
            float sideWeight = 1.0f;     // ejection direction in the weapon frame
            float upWeight = 0.7f;
            float backWeight = 0.25f;
            float jitter = 0.2f;         // +- fraction of speed per axis
        };

        struct EjectState
        {
            Vec3 position = {0, 0, 0};
            Vec3 velocity = {0, 0, 0};
            Vec3 direction = {1, 0, 0}; // unit ejection direction (no jitter)
        };

        // r0..r2 are uniform randoms in [-1, 1].
        inline EjectState ComputeEject(const MuzzleFrame& frame, const EjectParams& p, Vec3 shooterVelocity, float r0,
                                       float r1, float r2)
        {
            EjectState out;
            const Vec3 right = Normalize(frame.right, {1, 0, 0});
            const Vec3 up = Normalize(frame.up, {0, 1, 0});
            const Vec3 front = Normalize(frame.front, {0, 0, 1});
            const float back = std::max(0.0f, p.barrelLength) * std::max(0.0f, std::min(1.0f, p.breechFraction));
            out.position = Add(Add(frame.position, Scale(front, -back)), Scale(up, p.portUp));
            out.direction =
                Normalize(Add(Add(Scale(right, p.sideWeight), Scale(up, p.upWeight)), Scale(front, -p.backWeight)), right);
            const float speed = std::max(0.0f, p.speed);
            const Vec3 jitter = {r0 * p.jitter * speed, r1 * p.jitter * speed, r2 * p.jitter * speed};
            out.velocity = Add(Add(Scale(out.direction, speed), jitter), shooterVelocity);
            return out;
        }

        // ---- Weapon kinds and sizes ---------------------------------------------------------
        enum class WeaponKind
        {
            Unknown,
            Cannon,
            Mortar,
            MachineGun,
            SniperGun,
        };

        // Native class -> the ODF classLabel the engine itself maps it from.
        inline WeaponKind WeaponKindFromRtti(const char* rtti)
        {
            if (!rtti)
                return WeaponKind::Unknown;
            const std::string name(rtti);
            if (name == ".?AVCannon@@")
                return WeaponKind::Cannon;
            if (name == ".?AVMortar@@")
                return WeaponKind::Mortar;
            if (name == ".?AVMachineGun@@")
                return WeaponKind::MachineGun;
            if (name == ".?AVSniperGun@@")
                return WeaponKind::SniperGun;
            return WeaponKind::Unknown;
        }

        inline const char* WeaponKindLabel(WeaponKind kind)
        {
            switch (kind)
            {
            case WeaponKind::Cannon:
                return "cannon";
            case WeaponKind::Mortar:
                return "mortar";
            case WeaponKind::MachineGun:
                return "machinegun";
            case WeaponKind::SniperGun:
                return "snipergun";
            default:
                return "unknown";
            }
        }

        struct KindDefaults
        {
            float length;       // casing length in metres before the ammo factor
            float barrelLength; // default muzzle-to-breech distance
            float speed;        // ejection speed
        };

        inline KindDefaults DefaultsFor(WeaponKind kind)
        {
            switch (kind)
            {
            case WeaponKind::MachineGun:
                return {0.12f, 1.0f, 3.0f};
            case WeaponKind::SniperGun:
                return {0.13f, 0.6f, 2.5f};
            case WeaponKind::Mortar:
                return {0.40f, 1.6f, 3.0f};
            case WeaponKind::Cannon:
                return {0.30f, 2.0f, 3.5f};
            default:
                return {0.25f, 1.5f, 3.0f};
            }
        }

        // Mild growth with the ordnance's ammo cost (the engine's own cost of
        // a round, a stable stand-in for its punch): x0.8 at cost 0 up to x1.5.
        inline float AmmoSizeFactor(int ammoCost)
        {
            const float cost = static_cast<float>(std::max(0, std::min(ammoCost, 100000)));
            return std::max(0.8f, std::min(1.5f, 0.8f + 0.12f * std::log(1.0f + cost)));
        }

        inline float CasingLength(WeaponKind kind, int ammoCost)
        {
            return DefaultsFor(kind).length * AmmoSizeFactor(ammoCost);
        }

        // ---- Class filter ---------------------------------------------------------------------------
        // Comma/space separated, case-insensitive. A bare entry enables a
        // class label (cannon, mortar, machinegun, snipergun) or one weapon
        // ODF by name ("gquake" or "gquake.odf"); a "-" entry disables that
        // label or ODF and wins over any enable. "all" enables every class.
        struct ClassFilter
        {
            std::vector<std::string> include;
            std::vector<std::string> exclude;
            bool all = false;
        };

        inline std::string NormalizeToken(std::string token)
        {
            for (char& c : token)
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            const std::string suffix = ".odf";
            if (token.size() > suffix.size() && token.compare(token.size() - suffix.size(), suffix.size(), suffix) == 0)
                token.resize(token.size() - suffix.size());
            return token;
        }

        inline ClassFilter ParseClassFilter(const std::string& text)
        {
            ClassFilter filter;
            std::string token;
            auto flush = [&]() {
                if (token.empty())
                    return;
                const bool negative = token[0] == '-';
                const std::string body = NormalizeToken(negative ? token.substr(1) : token);
                if (!body.empty())
                {
                    if (negative)
                        filter.exclude.push_back(body);
                    else if (body == "all" || body == "*")
                        filter.all = true;
                    else
                        filter.include.push_back(body);
                }
                token.clear();
            };
            for (char c : text)
            {
                if (c == ',' || c == ';' || c == ' ' || c == '\t' || c == '"' || c == '\'')
                    flush();
                else
                    token.push_back(c);
            }
            flush();
            return filter;
        }

        inline bool FilterAllows(const ClassFilter& filter, const char* classLabel, const char* odfName)
        {
            const std::string label = NormalizeToken(classLabel ? classLabel : "");
            const std::string odf = NormalizeToken(odfName ? odfName : "");
            auto listed = [](const std::vector<std::string>& list, const std::string& value) {
                return !value.empty() && std::find(list.begin(), list.end(), value) != list.end();
            };
            if (listed(filter.exclude, label) || listed(filter.exclude, odf))
                return false;
            return filter.all || listed(filter.include, label) || listed(filter.include, odf);
        }

        // Shipped default: the four casing-shaped native classes, minus the
        // stock "cannon" ODFs that fire no shell (seismic wave, sandbag).
        inline const char* DefaultClassList() { return "cannon,mortar,machinegun,snipergun,-gquake,-gsandbag"; }

        // ---- Lifetime --------------------------------------------------------------------------------
        // Sinking casings also shrink to nothing so a small one never pops.
        inline float SinkScale(float elapsed, float duration)
        {
            if (!(duration > 0.0f))
                return 0.0f;
            const float t = std::max(0.0f, std::min(1.0f, elapsed / duration));
            return 1.0f - t * t;
        }
    } // namespace ShellCasings
} // namespace BZROpenShim
