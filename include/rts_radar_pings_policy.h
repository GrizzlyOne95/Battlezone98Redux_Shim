// rts_radar_pings_policy.h
// BZR Open Shim - RTS radar order pings: the engine-independent rules behind
// the expanding ring drawn on the cockpit radar (rts_markers.cpp). Header-only
// and free of Windows, so the unit tests check the math the shim runs. See
// Docs/RTS_MARKERS.md ("Radar pings").
//
//  - Project: world point -> radar pixel, the stock radar's own maths: the
//    offset from the user is clamped to the radar range (native rim clamp),
//    taken onto the radar basis (right/up/front rows) and run through the
//    stock projector s = r*5 / (range*5 + z); x = cx + round(vx*s),
//    y = cy - round(vy*s).
//  - Evaluate: a ping lives 1.5 s; its ring grows from 0.04 to 0.14 of the
//    projection radius while the alpha fades from 1 to 0.
//  - RadarPingQueue: the last few pings; a clock that went backwards (mission
//    restart) drops the ones born "in the future".
#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
    namespace RtsRadarPings
    {
        constexpr size_t kMaxPings = 8;
        constexpr float kDuration = 1.5f;
        constexpr float kStartRadiusFrac = 0.04f; // of the projection radius
        constexpr float kEndRadiusFrac = 0.14f;
        constexpr float kMinRadiusPixels = 3.0f;
        constexpr int kRingSegments = 12;

        struct Ping
        {
            float pos[3] = {};
            uint32_t argb = 0; // colour; the alpha byte is replaced when drawn
            float birth = 0.0f; // game-local clock, seconds
        };

        struct Frame
        {
            bool alive = false;
            float radiusFrac = 0.0f; // of the projection radius
            float alpha = 0.0f;      // 0..1
        };

        inline Frame Evaluate(float age)
        {
            Frame frame;
            if (!std::isfinite(age) || age < 0.0f || age >= kDuration)
                return frame;
            const float t = age / kDuration;
            frame.alive = true;
            frame.radiusFrac = kStartRadiusFrac + (kEndRadiusFrac - kStartRadiusFrac) * t;
            frame.alpha = 1.0f - t;
            return frame;
        }

        // Ring radius in pixels, never below the minimum.
        inline float RadiusPixels(float radiusFrac, int projRadius)
        {
            const float px = radiusFrac * static_cast<float>(projRadius);
            return px < kMinRadiusPixels ? kMinRadiusPixels : px;
        }

        struct Radar
        {
            float userPos[3] = {};
            float range = 0.0f;
            float right[3] = {};
            float up[3] = {};
            float front[3] = {};
            int projRadius = 0;
            int centreX = 0;
            int centreY = 0;
        };

        struct Projected
        {
            bool valid = false;
            bool clamped = false;
            int x = 0;
            int y = 0;
        };

        inline float Dot3(const float a[3], const float b[3])
        {
            return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
        }

        inline Projected Project(const Radar& radar, const float world[3])
        {
            Projected out;
            if (!(radar.range > 0.0f) || !std::isfinite(radar.range))
                return out;
            float d[3] = {world[0] - radar.userPos[0], world[1] - radar.userPos[1], world[2] - radar.userPos[2]};
            const float lenSq = Dot3(d, d);
            if (!std::isfinite(lenSq))
                return out;
            if (lenSq > radar.range * radar.range)
            {
                const float scale = radar.range / std::sqrt(lenSq);
                d[0] *= scale;
                d[1] *= scale;
                d[2] *= scale;
                out.clamped = true;
            }
            const float vx = Dot3(radar.right, d);
            const float vy = Dot3(radar.up, d);
            const float vz = Dot3(radar.front, d);
            const float denom = radar.range * 5.0f + vz;
            if (!(denom > 0.0f))
                return out;
            const float s = static_cast<float>(radar.projRadius) * 5.0f / denom;
            const float px = vx * s;
            const float py = vy * s;
            if (!std::isfinite(px) || !std::isfinite(py) || std::fabs(px) > 1.0e6f || std::fabs(py) > 1.0e6f)
                return out;
            out.x = radar.centreX + static_cast<int>(std::lround(px));
            out.y = radar.centreY - static_cast<int>(std::lround(py));
            out.valid = true;
            return out;
        }

        // Point `i` (0..kRingSegments, the last equals the first) of a ring.
        inline void RingPoint(int centreX, int centreY, float radius, int i, int& x, int& y)
        {
            const float angle = 6.28318530718f * static_cast<float>(i % kRingSegments) / static_cast<float>(kRingSegments);
            x = centreX + static_cast<int>(std::lround(radius * std::cos(angle)));
            y = centreY + static_cast<int>(std::lround(radius * std::sin(angle)));
        }

        class RadarPingQueue
        {
        public:
            // Replaces the oldest ping once full.
            void Push(const Ping& ping)
            {
                pings_[next_] = ping;
                used_[next_] = true;
                logged_[next_] = false;
                next_ = (next_ + 1) % kMaxPings;
            }

            void Clear()
            {
                for (size_t i = 0; i < kMaxPings; ++i)
                    used_[i] = false;
                next_ = 0;
            }

            // Drops what is over (or born after `now`: the clock was reset)
            // and returns how many remain.
            size_t Prune(float now)
            {
                size_t count = 0;
                for (size_t i = 0; i < kMaxPings; ++i)
                {
                    if (!used_[i])
                        continue;
                    if (pings_[i].birth > now || !Evaluate(now - pings_[i].birth).alive)
                        used_[i] = false;
                    else
                        ++count;
                }
                return count;
            }

            // True once per ping: lets the caller log its first drawn frame.
            bool TakeLogToken(size_t i)
            {
                if (i >= kMaxPings || !used_[i] || logged_[i])
                    return false;
                logged_[i] = true;
                return true;
            }

            bool Get(size_t i, Ping& out) const
            {
                if (i >= kMaxPings || !used_[i])
                    return false;
                out = pings_[i];
                return true;
            }

        private:
            std::array<Ping, kMaxPings> pings_{};
            std::array<bool, kMaxPings> used_{};
            std::array<bool, kMaxPings> logged_{};
            size_t next_ = 0;
        };
    }
}
