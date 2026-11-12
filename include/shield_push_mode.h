#pragma once

// Shield tower push modes (OpenShim ODF key `shieldPushMode`).
//
// Kept free of Windows and of the engine so tests/shield_push_mode_tests.cpp
// can exercise it on the host. team_filter_mines.cpp reads the live tower,
// target and ordnance state, asks these functions what to write, and writes
// it back.
//
// Stock ShieldTower::Simulate pushes everything inside the field box along
// the tower's front axis:
//     dv = front * push * dt - vel * drag * dt
// with objPush/objDrag for craft and ordPush/ordDrag for ordnance. A negative
// push therefore pushes toward -front (CR's towers use objPush -160,
// ordPush -300). That is "front" mode and stays the default.
//
// "radial" mode (aliases "outward", "bubble") repels on every side instead:
// the push direction is the horizontal (XZ) vector from the tower to the
// target, and the push magnitude is |push|, so the stock negative values and a
// positive value both repel. The drag term is unchanged.

#include <cmath>
#include <cstddef>

namespace BZROpenShim
{
namespace ShieldPushMode
{
    enum class Mode
    {
        Front,
        Radial,
    };

    // Within this horizontal distance of the tower's vertical axis the
    // tower-to-target direction is meaningless, so the tower front is used.
    constexpr float kAxisTieBreakDistance = 0.5f;

    namespace Detail
    {
        inline bool IsSpace(char c)
        {
            return c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f';
        }

        inline char ToLower(char c)
        {
            return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
        }

        // Case-insensitive compare of [begin, end) against a lowercase word.
        inline bool Equals(const char* begin, const char* end, const char* word)
        {
            for (; begin < end; ++begin, ++word)
            {
                if (*word == '\0' || ToLower(*begin) != *word)
                    return false;
            }
            return *word == '\0';
        }
    }

    // Parses an ODF value: surrounding whitespace and one pair of matching
    // quotes are ignored, case is ignored. Returns false (out untouched) for
    // anything it does not recognise.
    inline bool TryParse(const char* text, Mode& out)
    {
        if (!text)
            return false;

        const char* begin = text;
        while (*begin && Detail::IsSpace(*begin))
            ++begin;
        const char* end = begin;
        while (*end)
            ++end;
        while (end > begin && Detail::IsSpace(end[-1]))
            --end;

        if (end - begin >= 2 && (*begin == '"' || *begin == '\'') && end[-1] == *begin)
        {
            ++begin;
            --end;
        }

        if (Detail::Equals(begin, end, "front") || Detail::Equals(begin, end, "default") ||
            Detail::Equals(begin, end, "stock"))
        {
            out = Mode::Front;
            return true;
        }

        if (Detail::Equals(begin, end, "radial") || Detail::Equals(begin, end, "outward") ||
            Detail::Equals(begin, end, "bubble"))
        {
            out = Mode::Radial;
            return true;
        }

        return false;
    }

    // Unrecognised or missing text is the stock behaviour.
    inline Mode ParseOrFront(const char* text)
    {
        Mode mode = Mode::Front;
        TryParse(text, mode);
        return mode;
    }

    // Unit outward direction for radial mode: the horizontal (XZ) vector from
    // the tower to the target, normalised, with Y = 0. When the target is
    // within kAxisTieBreakDistance of the tower's vertical axis it returns the
    // tower front vector unchanged.
    inline void RadialOutwardDirection(const float (&towerPosition)[3],
                                       const float (&targetPosition)[3],
                                       const float (&towerFront)[3],
                                       float (&outDirection)[3])
    {
        const float dx = targetPosition[0] - towerPosition[0];
        const float dz = targetPosition[2] - towerPosition[2];
        const float lengthSq = dx * dx + dz * dz;
        if (!(lengthSq > kAxisTieBreakDistance * kAxisTieBreakDistance))
        {
            outDirection[0] = towerFront[0];
            outDirection[1] = towerFront[1];
            outDirection[2] = towerFront[2];
            return;
        }

        const float invLength = 1.0f / std::sqrt(lengthSq);
        outDirection[0] = dx * invLength;
        outDirection[1] = 0.0f;
        outDirection[2] = dz * invLength;
    }

    // Velocity change for a craft in radial mode, the radial counterpart of
    // the stock object term:
    //     dv = outward * |push| * dt - vel * drag * dt
    inline void RadialObjectVelocityDelta(const float (&outward)[3],
                                          float push,
                                          float drag,
                                          const float (&velocity)[3],
                                          float dt,
                                          float (&outDelta)[3])
    {
        const float pushStep = std::fabs(push) * dt;
        const float dragStep = drag * dt;
        for (std::size_t i = 0; i < 3; ++i)
            outDelta[i] = outward[i] * pushStep - velocity[i] * dragStep;
    }

    // New ordnance velocity in radial mode, updated in place.
    //
    // A fast shot can cross the whole field in one or two frames, so pushing
    // it outward by |push| * dt alone barely bends it and it tunnels through
    // the bubble. Instead, while the shot is still heading inward
    // (dot(vel, outward) < 0) its inward component is cancelled outright, so
    // the shot slides tangentially off the bubble; then the usual outward push
    // and drag apply. A shot already heading outward is only pushed and
    // damped. A tower with ordPush = 0 does not deflect at all (drag only),
    // matching how a zero push behaves in front mode.
    inline void RadialOrdnanceVelocity(const float (&outward)[3],
                                       float push,
                                       float drag,
                                       float dt,
                                       float (&velocity)[3])
    {
        if (push != 0.0f)
        {
            const float radial =
                velocity[0] * outward[0] + velocity[1] * outward[1] + velocity[2] * outward[2];
            if (radial < 0.0f)
            {
                for (std::size_t i = 0; i < 3; ++i)
                    velocity[i] -= outward[i] * radial;
            }
        }

        const float pushStep = std::fabs(push) * dt;
        const float dragStep = drag * dt;
        for (std::size_t i = 0; i < 3; ++i)
            velocity[i] += outward[i] * pushStep - velocity[i] * dragStep;
    }

    // --- Ricochet (radial mode, ODF key `shieldReflectSpeed`) ---------------
    //
    // Blast cannon and bolt shots cross the whole field box in a frame or two,
    // before the push above can turn them. A shot at least this fast is
    // reflected off the bubble instead: when it is inside the box now, or
    // will be after this frame's step (pos + vel * dt), and is still heading
    // inward, its velocity is mirrored about the outward normal. That keeps
    // its speed exactly. A ricocheted shot gets no push or drag that frame.
    // Slower shots keep RadialOrdnanceVelocity. 0 (or less) turns it off.
    constexpr float kDefaultReflectSpeed = 120.0f;

    inline float Length(const float (&v)[3])
    {
        return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }

    inline float Dot(const float (&a)[3], const float (&b)[3])
    {
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    }

    // Where the shot will be after this frame if nothing deflects it.
    inline void PredictNextPosition(const float (&position)[3],
                                    const float (&velocity)[3],
                                    float dt,
                                    float (&outPosition)[3])
    {
        for (std::size_t i = 0; i < 3; ++i)
            outPosition[i] = position[i] + velocity[i] * dt;
    }

    // Fast enough and heading inward? Cheap; checked before any box test.
    inline bool IsRicochetCandidate(const float (&velocity)[3],
                                    const float (&outward)[3],
                                    float reflectSpeed)
    {
        if (!(reflectSpeed > 0.0f))
            return false;
        if (Length(velocity) < reflectSpeed)
            return false;
        return Dot(velocity, outward) < 0.0f;
    }

    // The full trigger: a candidate that is inside the box now or will be
    // after this frame's step.
    inline bool ShouldRicochet(const float (&velocity)[3],
                               const float (&outward)[3],
                               float reflectSpeed,
                               bool insideNow,
                               bool insideNext)
    {
        return (insideNow || insideNext) && IsRicochetCandidate(velocity, outward, reflectSpeed);
    }

    // v' = v - 2 * dot(v, n) * n, with n the unit outward normal.
    inline void ReflectVelocity(const float (&outward)[3], float (&velocity)[3])
    {
        const float twiceNormal = 2.0f * Dot(velocity, outward);
        for (std::size_t i = 0; i < 3; ++i)
            velocity[i] -= twiceNormal * outward[i];
    }
}
}
